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
#include <emmintrin.h>

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

#if ANVIL_TASK_FIBERS
	struct FiberData {
		LPVOID fiber;
		Task* task;
		const std::function<bool(void)>* yield_condition;
		
		FiberData() :
			fiber(nullptr),
			task(nullptr),
			yield_condition(nullptr)
		{}

		FiberData(Task* task) :
			fiber(nullptr),
			task(task),
			yield_condition(nullptr)
		{}
	};
#endif

	static std::atomic_uint32_t g_next_thread_index = UINT32_MAX;

	struct TaskThreadLocalData {
#if ANVIL_TASK_FIBERS
		std::deque<FiberData*> fiber_list;
		FiberData* current_fiber;
		LPVOID main_fiber;
#else
		std::vector<Task*> task_stack;
#endif
		Scheduler* scheduler;
		uint32_t scheduler_index;
		bool is_worker_thread;

		TaskThreadLocalData() :
			scheduler(nullptr),
#if ANVIL_TASK_FIBERS
			current_fiber(nullptr),
			main_fiber(nullptr),
#endif
			scheduler_index(g_next_thread_index--),
			is_worker_thread(false)
		{}
		
		~TaskThreadLocalData() {
#if ANVIL_TASK_FIBERS
			// Delete old fibers
			for (FiberData* fiber : fiber_list) {
				DeleteFiber(fiber->fiber);
				delete fiber;
			}
			fiber_list.clear();
#endif
		}

#if ANVIL_TASK_FIBERS

	bool AreAnyFibersReady() const {
		if (!fiber_list.empty()) {
			auto end = fiber_list.end();
			auto i = std::find_if(fiber_list.begin(), end, [this](FiberData* fiber)->bool {
				return fiber != current_fiber && fiber->task != nullptr && (fiber->yield_condition == nullptr || (*fiber->yield_condition)());
			});
			return i != end;
		}

		return false;
	}

	bool SwitchToTask(FiberData& fiber) {
		if (&fiber == current_fiber) return false;
	
		// If the task is able to execute
		if (fiber.task != nullptr) {
			if (fiber.yield_condition == nullptr || (*fiber.yield_condition)()) {
				current_fiber = &fiber;
				SwitchToFiber(fiber.fiber);
				return true;
			}
		}
	
		return false;
	}
	
	bool SwitchToAnyTask() {
		// Try to execute a task that is ready to resume
RETRY:
		if (! fiber_list.empty()) {
			auto end = fiber_list.end();
			auto i = std::find_if(fiber_list.begin(), end, [this](FiberData* fiber)->bool {
				return fiber != current_fiber && fiber->task != nullptr && (fiber->yield_condition == nullptr || (*fiber->yield_condition)());
			});
			if (i != end) {
				FiberData* fiber = *i;

				if (fiber->task && fiber->task->_data->scheduler == nullptr) {
					fiber->task = nullptr;
					goto RETRY;
				}

				// Move fiber to the back of the list
				fiber_list.erase(i);
				fiber_list.push_back(fiber);

				// Switch to the fiber
				current_fiber = fiber;
				SwitchToFiber(fiber->fiber);
				return true;
			}
		}
	
		return false;
	}

	void SwitchToMainFiber2() {
		// Only switch to the main fiber if there are no other fibers
		const auto HasOtherFiber = [this]()->bool {
			for (FiberData* fiber : fiber_list) {
				if (fiber == current_fiber) continue;
				if (fiber->task == nullptr) continue;
				return true;
			}

			return false;
		};

		while (HasOtherFiber()) {
			SwitchToAnyTask();
		}

		SwitchToMainFiber();
	}
		
	void SwitchToMainFiber() {
		// Are we currently executing the main fiber?
		if (current_fiber == nullptr) return;
		
		// Switch to it
		current_fiber = nullptr;
		SwitchToFiber(main_fiber);
	}
#endif
	};
	
	thread_local TaskThreadLocalData g_thread_additional_data;

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
				Scheduler* scheduler = _data->scheduler ? _data->scheduler : g_thread_additional_data.scheduler;
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

	Task* Task::GetCurrentlyExecutingTask() {
#if ANVIL_TASK_FIBERS
		if (g_thread_additional_data.current_fiber == nullptr) {
			return nullptr;
		} else {
			return g_thread_additional_data.current_fiber->task;
		}
#else
		if (g_thread_additional_data.task_stack.empty()) {
			return nullptr;
		} else {
			return g_thread_additional_data.task_stack.back();
		}
#endif
	}

	size_t Task::GetNumberOfTasksExecutingOnThisThread() {
#if ANVIL_TASK_FIBERS
		size_t count = 0u;
		for (const FiberData* fiber : g_thread_additional_data.fiber_list) {
			if (fiber->task != nullptr) ++count;
		}
		return count;
#else
		return g_thread_additional_data.task_stack.size();
#endif
	}

	Task* Task::GetCurrentlyExecutingTask(size_t index) {
#if ANVIL_TASK_FIBERS
		size_t count = 0u;
		for (const FiberData* fiber : g_thread_additional_data.fiber_list) {
			if (fiber->task != nullptr) {
				if (count == index) return fiber->task;
				++count;
			}
		}
		return nullptr;
#else
		if (index >= g_thread_additional_data.task_stack.size()) return nullptr;
		return g_thread_additional_data.task_stack[index];
#endif
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

	void Task::Execute() throw() {
		// Remember the scheduler for later
		TaskDataLock task_lock(*_data);
	
#if ANVIL_TASK_FIBERS
		FiberData* fiber = nullptr;
		try {
			// Check if an existing fiber is unused
			for (FiberData* f : g_thread_additional_data.fiber_list) {
				if (f->task == nullptr) {
					fiber = f;
					break;
				}
			}

			if (fiber == nullptr) {
				// Allocate a new fiber
				g_thread_additional_data.fiber_list.push_back(new FiberData());
				fiber = g_thread_additional_data.fiber_list.back();
				fiber->fiber = CreateFiber(0u, Task::FiberFunction, fiber);
			}

			fiber->task = this;
			fiber->yield_condition = nullptr;
		}
		catch (std::exception& e) {
			CatchException(std::move(std::current_exception()), false);
		}

#else
		g_thread_additional_data.task_stack.push_back(this);
#endif
		Scheduler::ThreadDebugData* debug_data = _data->scheduler->GetDebugDataForThread(g_thread_additional_data.scheduler_index);
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

		// Switch control to the task's fiber
#if ANVIL_TASK_FIBERS
		g_thread_additional_data.SwitchToTask(*fiber);
#else
		FiberFunction(*g_thread_additional_data.task_stack.back());
#endif

		{
			// Post-execution cleanup
			std::lock_guard<std::shared_mutex> new_task_lock(_data->lock);
			_data->state = Task::STATE_COMPLETE;
			_data->scheduler = nullptr;
		}
	}

#if ANVIL_TASK_FIBERS
	void WINAPI Task::FiberFunction(LPVOID param) {
		FiberData& fiber = *static_cast<FiberData*>(param);
		while (true) {
			Task& task = *fiber.task;
			if (task._data == nullptr || task._data->scheduler == nullptr) {
				// fiber.task hasn't been set to null somehow
				throw 0;
			} else {
#else
	void Task::FiberFunction(Task& task) {
#endif
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

#if ANVIL_TASK_FIBERS
				fiber.task = nullptr;
				if (task._data->scheduler == nullptr) throw 0; // Main fiber has been switched to before this one somehow
#else
				g_thread_additional_data.task_stack.pop_back();
#endif

				Scheduler::ThreadDebugData* debug_data = task._data->scheduler->GetDebugDataForThread(g_thread_additional_data.scheduler_index);
				if (debug_data) {
					--debug_data->tasks_executing;
					--task._data->scheduler->_scheduler_debug.total_tasks_executing;
				}

#if ANVIL_DEBUG_TASKS
				{ TaskDebugEvent e = TaskDebugEvent::ExecuteEndEvent(task._data->debug_id); g_debug_event_handler(nullptr, &e); }
#endif
				if((scheduler._feature_flags & Scheduler::FEATURE_DELAYED_SCHEDULING) != 0u){
					std::lock_guard<std::shared_mutex> lock(scheduler._task_queue_mutex);
					scheduler.SortTaskQueue(false, true);
				}
				scheduler.TaskQueueNotify();

				// Return control to the main thread
#if ANVIL_TASK_FIBERS
			}
			if(fiber.task != nullptr) throw 0;
			g_thread_additional_data.SwitchToMainFiber2();
		}
#endif
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
				tasks[i]->task->Execute(); 
			}

			return true;
		}

		return false;
	}


	void Scheduler::RegisterAsWorkerThread() {
		TaskThreadLocalData& local_data = g_thread_additional_data;
		local_data.is_worker_thread = true;

#if ANVIL_TASK_FIBERS
		local_data.main_fiber = ConvertThreadToFiber(nullptr);
#endif

		if(_scheduler_debug.thread_debug_data != nullptr) {
			local_data.scheduler = this;
			local_data.scheduler_index = _scheduler_debug.total_thread_count++;
			ThreadDebugData& debug_data = _scheduler_debug.thread_debug_data[local_data.scheduler_index];
			debug_data.tasks_executing = 0u;
			debug_data.sleeping = 0u;
			debug_data.enabled = 1u;
			debug_data.thread_local_data = &local_data;
			++_scheduler_debug.executing_thread_count; // Default state is executing
		}
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
		const TaskThreadLocalData& local_data = g_thread_additional_data;
#if ANVIL_TASK_FIBERS
		FiberData* fiber = local_data.current_fiber;
		Task* t = fiber == nullptr ? nullptr : fiber->task;
#else
		Task* const t = local_data.task_stack.empty() ? nullptr : local_data.task_stack.back();
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

		if (count == 0u) return;

#if ANVIL_TASK_FIBERS
		Task* const parent = g_thread_additional_data.current_fiber == nullptr ? nullptr : g_thread_additional_data.current_fiber->task;
#else
		Task* const parent = g_thread_additional_data.task_stack.empty() ? nullptr : g_thread_additional_data.task_stack.back();
#endif

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

			// Update the child / parent relationship between tasks
			if (parent) parent->_data->AddChild(t._data);

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
			if(false){
HANDLE_EXCEPTION:
				t.SetException(exception);
				t.Cancel();
			} else {
TASK_SCHEDULED:
#if ANVIL_DEBUG_TASKS
				uint32_t parent_id = 0u;
				if (parent) parent_id = parent->_data->debug_id;
				TaskDebugEvent e = TaskDebugEvent::ScheduleEvent(t._data->debug_id, parent_id, _debug_id);
				g_debug_event_handler(nullptr, &e);
#else
				;
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

	uint32_t Scheduler::GetThisThreadIndex() const {
		return g_thread_additional_data.scheduler_index;
	}

	bool Scheduler::IsWorkerThread() const {
		return g_thread_additional_data.scheduler == this;
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

	std::deque<TaskSchedulingData*> g_task_scheduling_data;
	std::vector<TaskSchedulingData*> g_free_task_scheduling_data;
	std::mutex g_task_scheduling_data_lock;

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