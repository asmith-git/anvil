//MIT License
//
//Copyright(c) 2020 Adam G. Smith
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

// For the latest version, please visit https://github.com/asmith-git/anvil-scheduling

#include "anvil/scheduling/Core.hpp"
#if ANVIL_DEBUG_TASKS
	#include <cctype>
	#include <chrono>
	#include <sstream>
	#include <iostream>
	#include <map>
#endif
#include <string>
#include <atomic>
#include <algorithm>
#include <deque>
#include <list>
#include "anvil/scheduling/Scheduler.hpp"
#include "anvil/scheduling/Task.hpp"
#include "anvil/scheduling/details/Fibers.hpp"
#include "anvil/scheduling/details/ThreadLocal.hpp"
#include <emmintrin.h>

#define g_thread_additional_data anvil::details::TaskThreadLocalData::Get()

namespace anvil {

	std::deque<TaskSchedulingData*> g_task_scheduling_data;
	std::vector<TaskSchedulingData*> g_free_task_scheduling_data;
	std::mutex g_task_scheduling_data_lock;

	// Scheduler

	Scheduler::Scheduler(size_t thread_count, uint32_t feature_flags) :
		_feature_flags(feature_flags)

	{
		_scheduler_debug.thread_debug_data = thread_count == 0u ? nullptr : new ThreadDebugData[thread_count];
		_scheduler_debug.total_thread_count = 0u;
		_scheduler_debug.executing_thread_count = 0u;
		_scheduler_debug.sleeping_thread_count = 0u;
		_scheduler_debug.total_tasks_executing = 0u;
		_scheduler_debug.total_tasks_queued = 0u;

#if ANVIL_TASK_FIBERS
		_feature_flags |= FEATURE_ONLY_EXECUTE_ON_WORKER_THREADS; // Simplify fiber creation & management
#endif

#if ANVIL_DEBUG_TASKS
		_debug_id = g_scheduler_debug_id++;
		{
			SchedulerDebugEvent e = SchedulerDebugEvent::CreateEvent(_debug_id);
			g_debug_event_handler(&e, nullptr);
		}
#endif
	}

	Scheduler::~Scheduler() {
		//! \bug Scheduled tasks are left in an undefined state
#if ANVIL_DEBUG_TASKS
		{
			SchedulerDebugEvent e = SchedulerDebugEvent::DestroyEvent(_debug_id);
			g_debug_event_handler(&e, nullptr);
		}
#endif
		if (_scheduler_debug.thread_debug_data) {
			delete[] _scheduler_debug.thread_debug_data;
			_scheduler_debug.thread_debug_data = nullptr;
		}
	}


	void Scheduler::TaskQueueNotify() {
		_task_queue_update.notify_all();
	}

	void Scheduler::RemoveNextTaskFromQueue(TaskSchedulingData** tasks, uint32_t& count) throw() {
		if ((_feature_flags & FEATURE_DELAYED_SCHEDULING) != 0u) {
			// Check if there are tasks before locking the queue
			// Avoids overhead of locking during periods of low activity
			if (_task_queue.empty()) {
				// If there are no active tasks, check if an innactive one has now become ready
				if (_unready_task_queue.empty()) {
					count = 0u;
					return;
				}

				std::lock_guard<std::shared_mutex> lock(_task_queue_mutex);
				SortTaskQueue(false, true);

				if (_task_queue.empty()) {
					count = 0u;
					return;
				}
			}

			TaskSchedulingData* task = nullptr;
			bool notify = false;
			{
				// Lock the task queue so that other threads cannot access it
				std::lock_guard<std::shared_mutex> lock(_task_queue_mutex);

				while (task == nullptr) {
					// Check again that another thread hasn't emptied the queue while locking
					if (_task_queue.empty()) {
						count = 0u;
						return;
					}

					// Remove the task at the back of the queue
					task = _task_queue.back();
					_task_queue.pop_back();
					
					if (task == nullptr) continue; // A null task shouldn't exist in the queue but if it somehow does then remove it
					if (!task->task->IsReadyToExecute()) {
						// Add the task to the unready list
						_unready_task_queue.push_back(task);
						task = nullptr;
						notify = true;
						continue;
					}
				}
			}

			// If something has happened to the task queue then notify yielding tasks
			if (notify) TaskQueueNotify();

			// Return the task if one was found
			tasks[0u] = task;
			count = 1u;

		} else {
			// Check if there are tasks before locking the queue
			// Avoids overhead of locking during periods of low activity
			if (_task_queue.empty()) {
				count = 0u;
				return;
			}

			{
				// Acquire the queue lock
				std::lock_guard<std::shared_mutex> lock(_task_queue_mutex);

				// Remove the last task(s) in the queue
				uint32_t count2 = 0u;
				while (count2 < count && !_task_queue.empty()) {
					tasks[count2++] = _task_queue.back();
					_task_queue.pop_back();
				}

				count = count2;
			}
		}
	}

	bool Scheduler::TryToExecuteTask() throw() {
#if ANVIL_TASK_FIBERS
		// Try to resume execution of an existing task
		if(g_thread_additional_data.SwitchToAnyTask()) return true;

		enum { MAX_TASKS = 1u };
#else
		enum { MAX_TASKS = 1u };
#endif
		// Try to start the execution of a new task
		TaskSchedulingData* tasks[MAX_TASKS];
		uint32_t task_count = 1u;
		if constexpr (MAX_TASKS > 1u) {
			// If all threads are executing tasks
			if (_scheduler_debug.sleeping_thread_count == 0u) {
				// Take only a small proportion of the availbile tasks
				task_count = static_cast<uint32_t>(_task_queue.size()) / (_scheduler_debug.total_thread_count * 4);
				if (task_count < 1) task_count = 1u;
				if (task_count > MAX_TASKS) task_count = MAX_TASKS;
			}
		}
		RemoveNextTaskFromQueue(tasks, task_count);

		// If there is a task available then execute it
		if (task_count > 0) {

			for (uint32_t i = 0u; i < task_count; ++i) {
				tasks[i]->task->ExecuteInScheduler();
			}

			return true;
		}

		return false;
	}

	void Scheduler::Yield(const std::function<bool()>& condition, uint32_t max_sleep_milliseconds) {
		// If the condition is already met then avoid the overheads of suspending the thread / task
		if (condition()) return;

		max_sleep_milliseconds = std::max(1u, max_sleep_milliseconds);

		Scheduler::ThreadDebugData* const debug_data = GetDebugDataForThisThread();

#if ANVIL_DEBUG_TASKS
		const float debug_time = GetDebugTime();
#endif
		// If this function is being called by a task
#if ANVIL_TASK_FIBERS
		FiberData* fiber = g_thread_additional_data.current_fiber;
		Task* t = fiber == nullptr ? nullptr : fiber->task;
#else
		Task* const t = Task::GetCurrentlyExecutingTask();
#endif

		if (t) {
			std::lock_guard<std::shared_mutex> lock(t->_data->lock);

			// State change
#if _DEBUG
			if (t->_data->state != Task::STATE_EXECUTING) throw std::runtime_error("anvil::Scheduler::Yield : Task cannot yield unless it is in STATE_EXECUTING");
#endif
			t->_data->state = Task::STATE_BLOCKED;
			if ((_feature_flags & Scheduler::FEATURE_TASK_CALLBACKS) != 0u) {
				t->OnBlock();
			}
		}

#if ANVIL_TASK_FIBERS
		// Remember how the task should be resumed
		if (fiber) fiber->yield_condition = &condition;
#endif


		// While the condition is not met
		while (! condition()) {

			// If the thread is enabled
			bool thread_enabled = true;
			if (debug_data) thread_enabled = debug_data->enabled;

			// Try to execute a task
			if (thread_enabled && TryToExecuteTask()) {

			} else {
				const auto predicate = [this, &condition, thread_enabled]()->bool {
					if (thread_enabled) {
#if ANVIL_TASK_FIBERS
						if (g_thread_additional_data.AreAnyFibersReady()) return true;
#endif
						if (!_task_queue.empty()) return true;
					}
					return condition();
				};

				// Block until there is a queue update
				std::unique_lock<std::mutex> lock(_condition_mutex);

				// Check if something has changed while the mutex was being acquired
				if (!predicate()) {
#if ANVIL_DEBUG_TASKS
					{ SchedulerDebugEvent e = SchedulerDebugEvent::PauseEvent(_debug_id); g_debug_event_handler(&e, nullptr); }
#endif

					// Update that thread is sleeping
					if (debug_data) {
						debug_data->sleeping = 1u;
						--_scheduler_debug.executing_thread_count;
					}

					// Put the thread to sleep
					if (max_sleep_milliseconds == UINT32_MAX) { // Special behaviour, only wake when task updates happen (useful for implementing a thread pool)
						_task_queue_update.wait(lock);
					} else {
						_task_queue_update.wait_for(lock, std::chrono::milliseconds(max_sleep_milliseconds));
					}

					// Update that the thread is running
					if (debug_data) {
						debug_data->sleeping = 0u;
						++_scheduler_debug.executing_thread_count;
					}

#if ANVIL_DEBUG_TASKS
					{ SchedulerDebugEvent e = SchedulerDebugEvent::ResumeEvent(_debug_id); g_debug_event_handler(&e, nullptr); }
#endif
				}

			}
		}

#if ANVIL_TASK_FIBERS
		// The task can no longer be resumed
		if(fiber) fiber->yield_condition = nullptr;
#endif

		// If this function is being called by a task
		if (t) {
			std::lock_guard<std::shared_mutex> lock(t->_data->lock);

			// State change
			t->_data->state = Task::STATE_EXECUTING;

			if ((_feature_flags & Scheduler::FEATURE_TASK_CALLBACKS) != 0u) {
				t->OnResume();
			}
		}
	}

	void Scheduler::SortTaskQueue(bool recalculate_extended_priority, bool check_delayed_tasks) throw() {

		if (check_delayed_tasks && (_feature_flags & FEATURE_DELAYED_SCHEDULING) != 0u) {
			// If the status of the task queue has changed then tasks may now be able to execute that couldn't before
			if (!_unready_task_queue.empty()) {
				size_t count = 0u;
				for (auto i = _unready_task_queue.begin(); i != _unready_task_queue.end(); ++i) {
					Task& t = *(**i).task;

					// If the task is now ready then add it to the ready queue
					if (t.IsReadyToExecute()) {
						_task_queue.push_back(t._data);
						++count;
						_unready_task_queue.erase(i);
						i = _unready_task_queue.begin();
					}
				}

				if(count > 0) recalculate_extended_priority = true;
			}
		}

		if (recalculate_extended_priority && (_feature_flags & FEATURE_EXTENDED_PRIORITY) != 0u) {
			for (TaskSchedulingData* t : _task_queue) {
				try {
					std::shared_lock<std::shared_mutex> lock(t->lock);
					t->SetExtendedPriority(t->task->CalculateExtendedPriorty());
				} catch (...) {
					t->task->SetException(std::current_exception());
				}
			}
		}

		std::sort(_task_queue.begin(), _task_queue.end(), [](const TaskSchedulingData* lhs, const TaskSchedulingData* rhs)->bool {
			return lhs->task->_data->priority < rhs->task->_data->priority;
		});
	}


	void Scheduler::Schedule(std::shared_ptr<Task>* tasks, uint32_t count) {
		enum { TASK_BLOCK = 1024 };
		Task* tasks2[TASK_BLOCK];
		while (count > 0) {
			const uint32_t tasks_to_add = count > TASK_BLOCK ? TASK_BLOCK : count;

			for (uint32_t i = 0u; i < tasks_to_add; ++i) tasks2[i] = tasks[i].get();
			Schedule(tasks2, tasks_to_add);

			tasks += tasks_to_add;
			count -= tasks_to_add;
		}
	}

	void Scheduler::Schedule(Task** tasks, uint32_t count) {
		// Limit number of tasks that can be added in one call to prevent stack overflow
		enum {MAX_TASKS = 512};
		while (count > MAX_TASKS) {
			Schedule(tasks, MAX_TASKS);
			tasks += MAX_TASKS;
			count -= MAX_TASKS;
		}

		// If all tasks have been added then reutn early
		if (count == 0u) return;

		// If there is a task currently executing on this thread then it becomes the parent
		Task* parent = Task::GetCurrentlyExecutingTask();

		// Ready tasks are placed at the start of this array, undready tasks are added to the end
		TaskSchedulingData* ready_tasks[MAX_TASKS];
		TaskSchedulingData** unready_tasks = ready_tasks + (count - 1u);
		size_t ready_count = 0u;
		size_t unready_count = 0u;

		std::exception_ptr exception;
		// Initial error checking and initialisation
		for (uint32_t i = 0u; i < count; ++i) {
			Task& t = *tasks[i];

			TaskDataLock task_data_lock(*t._data);
			std::lock_guard<std::shared_mutex> task_lock(t._data->lock);

			if ((_feature_flags & Scheduler::FEATURE_TASK_CALLBACKS) != 0u) {
				// Task callback
				try {
					t.OnScheduled();
				} catch (std::exception&) {
					exception = std::current_exception();
					goto HANDLE_EXCEPTION;
				} catch (...) {
					exception = std::make_exception_ptr(std::runtime_error("Thrown value was not a C++ exception"));
					goto HANDLE_EXCEPTION;
				}
			}

			// Change state
			t._data->state = Task::STATE_SCHEDULED;

			// Initialise scheduling data
			t._data->scheduler = this;

			// If an exception was caught then pass it to the task then cancel it
			if(exception){
HANDLE_EXCEPTION:
				t.SetException(exception);
				exception = nullptr;
				t.Cancel();

			} else {

				// Check if the task is ready to execute now and add it to the appropriate queue
				if ((_feature_flags & FEATURE_DELAYED_SCHEDULING) != 0u) {
					// If the task isn't ready to execute yet push it to the innactive queue
					if (!t.IsReadyToExecute()) {
						*unready_tasks = t._data;
						--unready_tasks;
						++unready_count;
						goto TASK_SCHEDULED;
					}
				}
				ready_tasks[ready_count++] = t._data;

TASK_SCHEDULED:
				// Update the child / parent relationship between tasks
				if (parent) parent->_data->AddChild(t._data);

#if ANVIL_DEBUG_TASKS
				uint32_t parent_id = 0u;
				if (parent) parent_id = parent->_data->debug_id;
				TaskDebugEvent e = TaskDebugEvent::ScheduleEvent(t._data->debug_id, parent_id, _debug_id);
				g_debug_event_handler(nullptr, &e);
#endif
			}
		}

		if ((ready_count | unready_count) > 0u) {
			{
				// Lock the task queue
				std::lock_guard<std::shared_mutex> lock(_task_queue_mutex);

				if (unready_count > 0u) {
					// Add to the inactive queue
					++unready_tasks;
					_unready_task_queue.insert(_unready_task_queue.end(), unready_tasks, unready_tasks + unready_count);
				}

				if (ready_count > 0u) {
					// Add to the active queue
					_task_queue.insert(_task_queue.end(), ready_tasks, ready_tasks + ready_count);

					// Sort task list by priority
					SortTaskQueue(true, false);
				}
			}

			// Notify waiting threads
			TaskQueueNotify();
		}
	}
	
	void Scheduler::Schedule(Task* task, Priority priority) {
		task->_data->SetRegularPriority(priority);
		Schedule(&task, 1u);
	}

	TaskSchedulingData* Scheduler::AllocateTaskSchedulingData() {
		std::lock_guard<std::mutex> lock(g_task_scheduling_data_lock);

		if (g_free_task_scheduling_data.empty()) {
			enum { BLOCK_SIZE = 128 };
			TaskSchedulingData* tmp = new TaskSchedulingData[BLOCK_SIZE];
			for (size_t i = 0u; i < BLOCK_SIZE; ++i) {
				g_task_scheduling_data.push_back(tmp + i);
				g_free_task_scheduling_data.push_back(tmp + i);
			}
		}

		TaskSchedulingData* tmp = g_free_task_scheduling_data.back();
		g_free_task_scheduling_data.pop_back();
		return tmp;
	}

	void Scheduler::FreeTaskSchedulingData(TaskSchedulingData* data) {
		data->Reset();

		std::lock_guard<std::mutex> lock(g_task_scheduling_data_lock);
		g_free_task_scheduling_data.push_back(data);
	}

	Scheduler::ThreadDebugData::ThreadDebugData() :
		thread_local_data(nullptr),
		tasks_executing(0),
		sleeping(0),
		enabled(0)
	{}

	Scheduler::SchedulerDebugData::SchedulerDebugData() :
		thread_debug_data(nullptr),
		total_thread_count(0),
		executing_thread_count(0),
		sleeping_thread_count(0),
		total_tasks_executing(0),
		total_tasks_queued(0)
	{}
}