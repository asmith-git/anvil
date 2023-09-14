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

	//static float GetTimeMS() {
	//	static const uint64_t g_reference_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	//	return static_cast<float>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - g_reference_time) / 1000000.f;
	//}


#if ANVIL_DEBUG_TASKS
	static std::string FormatClassName(std::string name) {
		// Visual studio appends class to the start of the name, we dont need this
		auto i = name.find("class ");
		while (i != std::string::npos) {
			name.erase(i, 6);
			i = name.find("class ");
		}

		// Erase whitepace from name
		for (auto j = name.begin(); j != name.end(); ++j) {
			if (std::isspace(*j)) {
				name.erase(j);
				j = name.begin();
			}
		}

		return name;
	}

	static std::string GetLongName(const Task* task) {
		return FormatClassName(typeid(*task).name());
	}

	static void DefaultEventHandler(SchedulerDebugEvent* scheduler_event, TaskDebugEvent* task_event) {
		struct TaskDebugData {
			Task* task;
			float schedule_time;
			float execution_start_time;
			float execution_end_time;
			float pause_time;

			TaskDebugData() :
				task(nullptr),
				schedule_time(0.f),
				execution_start_time(0.f),
				execution_end_time(0.f),
				pause_time(0.f)
			{}
		};
		struct SchedulerDebugData {
			float pause_time;
		};
		static std::mutex g_debug_lock;
		static std::map<uint32_t, TaskDebugData> g_task_debug_data;
		static std::map<uint32_t, SchedulerDebugData> g_scheduler_debug_data;

		std::stringstream ss;

		if (scheduler_event) {
			std::lock_guard<std::mutex> lock(g_debug_lock);
			//ss << scheduler_event->time << " ms : ";

			switch (scheduler_event->type) {
			case SchedulerDebugEvent::EVENT_CREATE:
				g_scheduler_debug_data.emplace(scheduler_event->scheduler_id, SchedulerDebugData{ 0.f });
				ss << "Scheduler " << scheduler_event->scheduler_id << " was created";
				break;

			case SchedulerDebugEvent::EVENT_PAUSE:
				{
					SchedulerDebugData& debug = g_scheduler_debug_data[scheduler_event->scheduler_id];
					debug.pause_time = scheduler_event->time;
					ss << "Scheduler " << scheduler_event->scheduler_id << " pauses execution";
				}
				break;

			case SchedulerDebugEvent::EVENT_RESUME:
				{
					SchedulerDebugData& debug = g_scheduler_debug_data[scheduler_event->scheduler_id];
					ss << "Scheduler " << scheduler_event->scheduler_id << " resumes execution after sleeping for " << (scheduler_event->time - debug.pause_time) << " ms";
				}
				break;

			case SchedulerDebugEvent::EVENT_DESTROY:
				g_scheduler_debug_data.erase(g_scheduler_debug_data.find(scheduler_event->scheduler_id));
				ss << "Scheduler " << scheduler_event->scheduler_id << " is destroyed";
				break;
			};

			ss << " on thread " << scheduler_event->thread_id;
		}

		if(task_event) {
			std::lock_guard<std::mutex> lock(g_debug_lock);
			ss << task_event->time << " ms : ";

			switch(task_event->type) {
			case TaskDebugEvent::EVENT_CREATE:
				{
					TaskDebugData debug;
					debug.task = task_event->task;
					g_task_debug_data.emplace(task_event->task_id, debug);
				}
				ss << "Task " << task_event->task_id << " was created, type is " << GetLongName(task_event->task);
				break;

			case TaskDebugEvent::EVENT_SCHEDULE:
				{
					TaskDebugData& debug = g_task_debug_data[task_event->task_id];
					debug.schedule_time = task_event->time;
				}
				ss << "Task " << task_event->task_id;
				if (task_event->parent_id != 0u) ss << " (is a child of task " << task_event->parent_id << ")";
				ss << " was scheduled on scheduler " << task_event->scheduler_id;
				break;

			case TaskDebugEvent::EVENT_CANCEL:
				g_task_debug_data.erase(g_task_debug_data.find(task_event->task_id));
				ss << "Task " << task_event->task_id << " was canceled";
				break;

			case TaskDebugEvent::EVENT_EXECUTE_BEGIN:
				{
					TaskDebugData& debug = g_task_debug_data[task_event->task_id];
					debug.execution_start_time = task_event->time;

					ss << "Task " << task_event->task_id << " begins execution after being scheduled for " << (task_event->time - debug.schedule_time) << " ms";
				}
				break;

			case TaskDebugEvent::EVENT_PAUSE:
				{
					TaskDebugData& debug = g_task_debug_data[task_event->task_id];
					debug.pause_time = task_event->time;

					ss << "Task " << task_event->task_id << " pauses after executing for " << (task_event->time - debug.execution_start_time) << " ms";
					if (task_event->will_yield) ss << " and will yield";
					else ss << " without yielding";
				}
				break;

			case TaskDebugEvent::EVENT_RESUME:
				{
					TaskDebugData& debug = g_task_debug_data[task_event->task_id];
					debug.pause_time = task_event->time;

					ss << "Task " << task_event->task_id << " resumes execution after being paused for " << (task_event->time - debug.pause_time) << " ms";
				}
				break;

			case TaskDebugEvent::EVENT_EXECUTE_END:
				{
					TaskDebugData& debug = g_task_debug_data[task_event->task_id];
					debug.execution_end_time = task_event->time;

					ss << "Task " << task_event->task_id << " completes execution after " << (task_event->time - debug.execution_start_time) << " ms";
				}
				break;

			case TaskDebugEvent::EVENT_DESTROY:
				{
					TaskDebugData& debug = g_task_debug_data[task_event->task_id];
				}
				g_task_debug_data.erase(g_task_debug_data.find(task_event->task_id));
				ss << "Task " << task_event->task_id << " is destroyed";
				break;
			};

			ss << " on thread " << task_event->thread_id;
		}

		ss << "\n";
		std::cerr << ss.str();
	}

	static TaskDebugEvent::DebugEventHandler g_debug_event_handler = DefaultEventHandler;
#endif

#if ANVIL_USE_NEST_COUNTER
	thread_local int32_t g_tasks_nested_on_this_thread = 0; //!< Tracks if Task::Execute is being called on this thread (and how many tasks are nested)
#endif

#if ANVIL_DEBUG_TASKS

	static float GetDebugTime() {
		static const uint64_t g_reference_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		return static_cast<float>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - g_reference_time) / 1000000.f;
	}

	static std::atomic_uint32_t g_task_debug_id = 0u;
	static std::atomic_uint32_t g_scheduler_debug_id = 0u;
#endif

#define INVALID_SCHEDULER nullptr

	// Task::TaskSchedulingData

	TaskSchedulingData::TaskSchedulingData() :
		task(nullptr),
		scheduler(nullptr),
		parent(nullptr),
		reference_counter(0u),
		priority(static_cast<uintptr_t>(Priority::PRIORITY_MIDDLE) << Scheduler::EXTENDED_PRIORITY_BITS),
		state(Task::STATE_INITIALISED)
	{}


	void TaskSchedulingData::Reset() {
		task = nullptr;
		scheduler = nullptr;
		reference_counter = 0u;
		priority = static_cast<uintptr_t>(Priority::PRIORITY_MIDDLE) << Scheduler::EXTENDED_PRIORITY_BITS;
		state = Task::STATE_INITIALISED;
		parent = nullptr;
		children.clear();
		exception = nullptr;
	}

	bool TaskSchedulingData::AddChild(TaskSchedulingData* c) {
		if (c->parent != nullptr) return false;

		std::lock_guard<std::shared_mutex> lockguard(lock);

		for (TaskSchedulingData* c2 : children) if (c == c2) return false;
		++reference_counter;
		children.push_back(c);
		++c->reference_counter;
		c->parent = this;
		return true;
	}

	bool TaskSchedulingData::RemoveChild(TaskSchedulingData* c) {
		if (c->parent != this) return false;

		std::lock_guard<std::shared_mutex> lockguard(lock);
		auto i = std::find(children.begin(), children.end(), c);
		children.erase(i);
		--reference_counter;
		--c->reference_counter;
		c->parent = nullptr;
		return true;
	}

	bool TaskSchedulingData::DetachFromParent() {
		if (parent == nullptr) return true;
		return parent->RemoveChild(this);
	}

	bool TaskSchedulingData::DetachFromChildren() {
		TaskDataLock dataguard(*this);
		{
			std::lock_guard<std::shared_mutex> lockguard(lock);
			if (parent) {
				TaskDataLock dataguard2(*parent);
				{
					std::lock_guard<std::shared_mutex> lockguard2(parent->lock);

					while (!children.empty()) {
						TaskSchedulingData* c = children.back();
						TaskDataLock dataguard3(*c);
						{
							std::lock_guard<std::shared_mutex> lockguard3(c->lock);
							if (!RemoveChild(c)) continue;
							parent->AddChild(c); 	// Transfer children to grandparent
						}
					}
				}

			}
			else {
				while (!children.empty()) {
					TaskSchedulingData* c = children.back();
					TaskDataLock dataguard3(*c);
					{
						std::lock_guard<std::shared_mutex> lockguard3(c->lock);
						RemoveChild(c);
					}
				}
			}
		}

		return children.size() == 0;
	}

	void TaskSchedulingData::SetExtendedPriority(uintptr_t value) {
		priority &= ~Scheduler::EXTENDED_PRIORITY_MASK;
		value &= Scheduler::EXTENDED_PRIORITY_MASK;
		priority |= value;
	}

	void TaskSchedulingData::SetRegularPriority(Priority value) {
		uintptr_t tmp = value;
		priority &= Scheduler::EXTENDED_PRIORITY_MASK;
		tmp <<= Scheduler::EXTENDED_PRIORITY_BITS;
		priority |= tmp;
	}

	uintptr_t TaskSchedulingData::GetExtendedPriority() const {
		return priority & Scheduler::EXTENDED_PRIORITY_MASK;
	}

	Scheduler::Priority TaskSchedulingData::GetRegularPriority() const {
		return static_cast<Priority>(priority >> Scheduler::EXTENDED_PRIORITY_BITS);
	}

	// Task

	Task::Task()  {
		_data = Scheduler::AllocateTaskSchedulingData();
		_data->task = this;
		_data->reference_counter = 1u;
#if ANVIL_DEBUG_TASKS
		_data->debug_id = g_task_debug_id++;
		{
			TaskDebugEvent e = TaskDebugEvent::CreateEvent(_data->debug_id, this);
			g_debug_event_handler(nullptr, &e);
		}
#endif
	}

	Task::~Task() {

		if(_data) {
			Wait();

	#if ANVIL_DEBUG_TASKS
			{
				TaskDebugEvent e = TaskDebugEvent::DestroyEvent(_data->debug_id);
				g_debug_event_handler(nullptr, &e);
			}
	#endif

			_data->DetachFromChildren();
			_data->DetachFromParent();

			bool still_has_references;
			{
				std::lock_guard<std::shared_mutex> task_lock(_data->lock);
				--_data->reference_counter;
				still_has_references = _data->reference_counter > 0;
			}
			if (still_has_references) {
				Scheduler* scheduler = _data->scheduler ? _data->scheduler : g_thread_additional_data._scheduler;
				if (scheduler) {
					scheduler->Yield([this]()->bool {
						std::shared_lock<std::shared_mutex> task_lock(_data->lock);
						return _data->reference_counter == 0u;
					});

				} else {
					{
						std::shared_lock<std::shared_mutex> task_lock(_data->lock);
						still_has_references = _data->reference_counter > 0; 
					}
					while (still_has_references) {
						std::this_thread::sleep_for(std::chrono::milliseconds(1));

						std::shared_lock<std::shared_mutex> task_lock(_data->lock);
						still_has_references = _data->reference_counter > 0;
					}
				}
			}
			Scheduler::FreeTaskSchedulingData(_data);
			_data = nullptr;
		}
		//! \bug If the task is scheduled it must be removed from the scheduler
	}

	void Task::SetException(std::exception_ptr exception) {
		_data->exception = exception;
	}

	bool Task::Cancel() throw() {
		TaskDataLock task_lock(*_data);

		// If no scheduler is attached to this task then it cannot be canceled
		Scheduler* scheduler = _data->scheduler;
		if (scheduler == nullptr) return false;

		// Lock the scheduler's task queue
		bool notify = false;
		{
			std::lock_guard<std::shared_mutex> lock(scheduler->_task_queue_mutex);

			// If the state is not scheduled then it cannot be canceled
			if (GetState() != STATE_SCHEDULED) return false;

			// Remove the task from the queue
			for (auto i = scheduler->_task_queue.begin(); i < scheduler->_task_queue.end(); ++i) {
				if ((*i)->task == this) {
					scheduler->_task_queue.erase(i);
					notify = true;
					break;
				}
			}
			if ((scheduler->_feature_flags & Scheduler::FEATURE_DELAYED_SCHEDULING) != 0u) {
				for (auto i = scheduler->_unready_task_queue.begin(); i < scheduler->_unready_task_queue.end(); ++i) {
					if (*i == _data) {
						scheduler->_unready_task_queue.erase(i);
						notify = true;
						break;
					}
				}
			}
		}
		{
			std::lock_guard<std::shared_mutex> new_task_lock(_data->lock);
#if ANVIL_DEBUG_TASKS
			{
				TaskDebugEvent e = TaskDebugEvent::CancelEvent(_data->debug_id);
				g_debug_event_handler(nullptr, &e);
			}
#endif

			if ((scheduler->_feature_flags & Scheduler::FEATURE_TASK_CALLBACKS) != 0u) {
				// Call the cancelation callback
				try {
					OnCancel();
				} catch (...) {
					SetException(std::current_exception());
				}
			}
			// State change and cleanup
			std::lock_guard<std::shared_mutex> lock(_data->lock);
			_data->state = Task::STATE_CANCELED;
			_data->scheduler = nullptr;
		}

		// Notify anythign waiting for changes to the task queue
		if (notify) scheduler->TaskQueueNotify();
		return true;
	}

	void Task::Wait() {
		TaskDataLock task_lock(*_data);

		Scheduler* const scheduler = _data->scheduler;
		if (_data->state >= Task::STATE_COMPLETE || _data->state == Task::STATE_INITIALISED || scheduler == nullptr) return;

		const bool will_yield = (scheduler->_feature_flags & Scheduler::FEATURE_ONLY_EXECUTE_ON_WORKER_THREADS) == 0 ?
			true :											// Always yield
			GetNumberOfTasksExecutingOnThisThread() > 0;	// Only call yield if Wait is called from inside of a Task					

#if ANVIL_DEBUG_TASKS
		{
			TaskDebugEvent e = TaskDebugEvent::PauseEvent(_data->debug_id, will_yield);
			g_debug_event_handler(nullptr, &e);
		}
#endif

		const auto YieldCondition = [this]()->bool {
			std::shared_lock<std::shared_mutex> task_lock(_data->lock);
#if ANVIL_TASK_FIBERS
			//if (!_data->children.empty()) return false; // Wait for all children to execute
#endif
			return _data->state >= STATE_COMPLETE && _data->scheduler == nullptr;
		};

		if (will_yield) {
			scheduler->Yield(YieldCondition);
		} else {
			while (!YieldCondition()) {
				// Wait for 1ms then check again
				std::unique_lock<std::mutex> lock(scheduler->_condition_mutex);
				if (YieldCondition()) break; // If the condition was met while acquiring the lock
				scheduler->_task_queue_update.wait_for(lock, std::chrono::milliseconds(1));
			}
		}

#if ANVIL_DEBUG_TASKS
		{
			TaskDebugEvent e = TaskDebugEvent::ResumeEvent(_data->debug_id);
			g_debug_event_handler(nullptr, &e);
		}
#endif

		// Rethrow a caught exception
		if (_data->exception) {
			std::exception_ptr tmp = _data->exception;
			_data->exception = std::exception_ptr();
			std::rethrow_exception(tmp);
		}
	}


	void Task::SetPriority(Priority priority) {
		TaskDataLock task_lock(*_data);

		// Set the priority
		Scheduler* scheduler;
		{
			std::shared_lock<std::shared_mutex> lock(_data->lock);
			_data->SetRegularPriority(priority);
			scheduler = _data->scheduler;
		}

		// Update the scheduler
		if (scheduler) {
			if (_data->state == STATE_SCHEDULED) {
				std::lock_guard<std::shared_mutex> lock(scheduler->_task_queue_mutex);
				scheduler->SortTaskQueue(false, false);
			}
		}
	}

	void Task::CatchException(std::exception_ptr&& exception, bool set_exception) {
		// Handle the exception
		if (set_exception) SetException(std::move(exception));

		// If the exception was caught after the task finished execution
		if (_data->state == Task::STATE_COMPLETE || _data->state == Task::STATE_CANCELED) {
			// Do nothing

		// If the exception was caught before or during execution
		} else {
			// Cancel the Task
			_data->state = Task::STATE_CANCELED;
			if ((_data->scheduler->_feature_flags & Scheduler::FEATURE_TASK_CALLBACKS) != 0u) {
				// Call the cancelation callback
				try {
					OnCancel();

				} catch (std::exception&) {
					// Task caught during execution takes priority as it probably has more useful debugging information
					if (!set_exception) this->SetException(std::current_exception());

				} catch (...) {
					// Task caught during execution takes priority as it probably has more useful debugging information
					if (!set_exception) this->SetException(std::make_exception_ptr(std::runtime_error("Thrown value was not a C++ exception")));
				}
			}
		}
	};

	void Task::Execute() {
		// Select which scheduler should be used
		Task* parent = Task::GetCurrentlyExecutingTask();
		Scheduler* scheduler = parent ? &parent->GetScheduler() : &g_thread_additional_data.GetUnthreadedScheduler();

		// Schedule this task for execution
		scheduler->Schedule(*this);

		// Wait for the task to execute
		Wait();
	}

	void Task::ExecuteInScheduler() throw() {
		// Prevent the task data from being deleted during execution
		TaskDataLock task_lock(*_data);

		// Initialise contextual data required for execution
		details::TaskThreadLocalData& thread_data = g_thread_additional_data;
		details::FiberData* const fiber = thread_data.OnTaskExecuteBegin(*this);

		// Update debugging data
		Scheduler::ThreadDebugData* debug_data = _data->scheduler->GetDebugDataForThread(thread_data._scheduler_index);
		if (debug_data) {
			++debug_data->tasks_executing;
			++_data->scheduler->_scheduler_debug.total_tasks_executing;
		}

#if ANVIL_DEBUG_TASKS
		{
			TaskDebugEvent e = TaskDebugEvent::ExecuteBeginEvent(_data->debug_id);
			g_debug_event_handler(nullptr, &e);
		}
#endif

		// Execute the task
		thread_data.LaunchTaskFiber(*this, fiber);

		// Post-execution cleanup
		{
			std::lock_guard<std::shared_mutex> new_task_lock(_data->lock);
			_data->state = Task::STATE_COMPLETE;
			_data->scheduler = nullptr;
		}
	}

#if ANVIL_TASK_FIBERS
	void WINAPI Task::FiberFunction(LPVOID param) {
		details::FiberData* const fiber = *static_cast<FiberData*>(param);
		details::TaskThreadLocalData& thread_data = g_thread_additional_data;
		while (true) {
			Task& task = *fiber->task;
			if (task._data == nullptr || task._data->scheduler == nullptr) {
				// fiber.task hasn't been set to null somehow
				throw 0;
			} else  {
#else
	void Task::FiberFunction(Task& task) {
		details::FiberData* const fiber = nullptr;
		details::TaskThreadLocalData& thread_data = g_thread_additional_data;
		if(true) {
			{
#endif	
				// Prevent the task data from being deleted during execution
				TaskDataLock task_lock(*task._data);


				Scheduler& scheduler = task.GetScheduler();

				// If an error hasn't been detected yet
				if (task._data->state != Task::STATE_CANCELED) {

					// Execute the task
					{
						std::lock_guard<std::shared_mutex> new_task_lock(task._data->lock); //! \bug Not sure this lock is required now, task is already locked at this point
						task._data->state = Task::STATE_EXECUTING;
					}
					try {
						task.OnExecution();
					} catch (std::exception&) {
						task.CatchException(std::move(std::current_exception()), true);
					} catch (...) {
						task.CatchException(std::exception_ptr(std::make_exception_ptr(std::runtime_error("Thrown value was not a C++ exception"))), true);
					}
				}

				// Begin cleanup of task execution data
				thread_data.TerminateTaskFiber(task, fiber);

				// Update debugging data
				Scheduler::ThreadDebugData* debug_data = task._data->scheduler->GetDebugDataForThread(thread_data._scheduler_index);
				if (debug_data) {
					--debug_data->tasks_executing;
					--task._data->scheduler->_scheduler_debug.total_tasks_executing;
				}

#if ANVIL_DEBUG_TASKS
				{ TaskDebugEvent e = TaskDebugEvent::ExecuteEndEvent(task._data->debug_id); g_debug_event_handler(nullptr, &e); }
#endif

				// Schedule any tasks that were waiting for this task to finish
				if((scheduler._feature_flags & Scheduler::FEATURE_DELAYED_SCHEDULING) != 0u){
					std::lock_guard<std::shared_mutex> lock(scheduler._task_queue_mutex);
					scheduler.SortTaskQueue(false, true);
				}
				scheduler.TaskQueueNotify();
			}

			// Return control to the main thread
			thread_data.OnTaskExecuteEnd(task, fiber);
		}
	}

	void Task::OnExecution() {
		// Does nothing
	}

	void Task::OnScheduled() {
		// Does nothing
	}

	void Task::OnBlock() {
		// Does nothing
	}

	void Task::OnResume() {
		// Does nothing
	}

	void Task::OnCancel() {
		// Does nothing
	}
	
	bool Task::IsReadyToExecute() const throw() {
		return true;
	}

	uintptr_t Task::CalculateExtendedPriorty() const {
		return 0u;
	}

#if ANVIL_DEBUG_TASKS
	// TaskDebugEvent

	static uint32_t GetDebugThreadID() {
		std::stringstream ss;
		ss << std::this_thread::get_id();
		uint32_t id;
		ss >> id;
		return id;
	}

	thread_local const uint32_t g_debug_thread_id = GetDebugThreadID();

	TaskDebugEvent TaskDebugEvent::CreateEvent(uint32_t task_id, Task* task) {
		TaskDebugEvent e;
		e.time = GetDebugTime();
		e.task = task;
		e.thread_id = g_debug_thread_id;
		e.task_id = task_id;
		e.type = EVENT_CREATE;
		return e;
	}

	TaskDebugEvent TaskDebugEvent::ScheduleEvent(uint32_t task_id, uint32_t parent_id, uint32_t scheduler_id) {
		TaskDebugEvent e;
		e.time = GetDebugTime();
		e.thread_id = g_debug_thread_id;
		e.task_id = task_id;
		e.parent_id = parent_id;
		e.scheduler_id = scheduler_id;
		e.type = EVENT_SCHEDULE;
		return e;
	}

	TaskDebugEvent TaskDebugEvent::CancelEvent(uint32_t task_id) {
		TaskDebugEvent e;
		e.time = GetDebugTime();
		e.thread_id = g_debug_thread_id;
		e.task_id = task_id;
		e.type = EVENT_CANCEL;
		return e;
	}

	TaskDebugEvent TaskDebugEvent::ExecuteBeginEvent(uint32_t task_id) {
		TaskDebugEvent e;
		e.time = GetDebugTime();
		e.thread_id = g_debug_thread_id;
		e.task_id = task_id;
		e.type = EVENT_EXECUTE_BEGIN;
		return e;
	}

	TaskDebugEvent TaskDebugEvent::PauseEvent(uint32_t task_id, bool will_yield) {
		TaskDebugEvent e;
		e.time = GetDebugTime();
		e.thread_id = g_debug_thread_id;
		e.task_id = task_id;
		e.will_yield = will_yield;
		e.type = EVENT_PAUSE;
		return e;
	}

	TaskDebugEvent TaskDebugEvent::ResumeEvent(uint32_t task_id) {
		TaskDebugEvent e;
		e.time = GetDebugTime();
		e.thread_id = g_debug_thread_id;
		e.task_id = task_id;
		e.type = EVENT_RESUME;
		return e;
	}

	TaskDebugEvent TaskDebugEvent::ExecuteEndEvent(uint32_t task_id) {
		TaskDebugEvent e;
		e.time = GetDebugTime();
		e.thread_id = g_debug_thread_id;
		e.task_id = task_id;
		e.type = EVENT_EXECUTE_END;
		return e;
	}

	TaskDebugEvent TaskDebugEvent::DestroyEvent(uint32_t task_id) {
		TaskDebugEvent e;
		e.time = GetDebugTime();
		e.thread_id = g_debug_thread_id;
		e.task_id = task_id;
		e.type = EVENT_DESTROY;
		return e;
	}

	void TaskDebugEvent::SetDebugEventHandler(DebugEventHandler handler) {
		if (handler == nullptr) handler = DefaultEventHandler;
		g_debug_event_handler = handler;
	}
	// SchedulerDebugEvent

	SchedulerDebugEvent SchedulerDebugEvent::CreateEvent(uint32_t scheduler_id) {
		SchedulerDebugEvent e;
		e.time = GetDebugTime();
		e.thread_id = g_debug_thread_id;
		e.scheduler_id = scheduler_id;
		e.type = EVENT_CREATE;
		return e;
	}

	SchedulerDebugEvent SchedulerDebugEvent::PauseEvent(uint32_t scheduler_id) {
		SchedulerDebugEvent e;
		e.time = GetDebugTime();
		e.thread_id = g_debug_thread_id;
		e.scheduler_id = scheduler_id;
		e.type = EVENT_PAUSE;
		return e;
	}

	SchedulerDebugEvent SchedulerDebugEvent::ResumeEvent(uint32_t scheduler_id) {
		SchedulerDebugEvent e;
		e.time = GetDebugTime();
		e.thread_id = g_debug_thread_id;
		e.scheduler_id = scheduler_id;
		e.type = EVENT_RESUME;
		return e;
	}

	SchedulerDebugEvent SchedulerDebugEvent::DestroyEvent(uint32_t scheduler_id) {
		SchedulerDebugEvent e;
		e.time = GetDebugTime();
		e.thread_id = g_debug_thread_id;
		e.scheduler_id = scheduler_id;
		e.type = EVENT_DESTROY;
		return e;
	}

#endif
}