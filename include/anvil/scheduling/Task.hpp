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

#ifndef ANVIL_SCHEDULER_TASK_HPP
#define ANVIL_SCHEDULER_TASK_HPP

#include <atomic>
#include <stdexcept>
#include <memory>
#include <shared_mutex>
#include "anvil/core/Keywords.hpp"
#include "anvil/scheduling/Scheduler.hpp"
#include "anvil/scheduling/details/ThreadLocal.hpp"

#if ANVIL_TASK_FIBERS
	#define NOMINMAX
	#include <windows.h>
	#undef Yield
#endif

namespace anvil {
#if ANVIL_DEBUG_TASKS
	struct ANVIL_DLL_EXPORT SchedulerDebugEvent {
		enum Type : uint8_t {
			EVENT_CREATE,
			EVENT_PAUSE,
			EVENT_RESUME,
			EVENT_DESTROY
		};

		float time;
		uint32_t thread_id;
		uint32_t scheduler_id;
		Type type;

		static SchedulerDebugEvent CreateEvent(uint32_t scheduler_id);
		static SchedulerDebugEvent PauseEvent(uint32_t scheduler_id);
		static SchedulerDebugEvent ResumeEvent(uint32_t scheduler_id);
		static SchedulerDebugEvent DestroyEvent(uint32_t scheduler_id);
	};

	struct ANVIL_DLL_EXPORT TaskDebugEvent {
		enum Type : uint8_t {
			EVENT_CREATE,
			EVENT_SCHEDULE,
			EVENT_CANCEL,
			EVENT_EXECUTE_BEGIN,
			EVENT_PAUSE,
			EVENT_RESUME,
			EVENT_EXECUTE_END,
			EVENT_DESTROY
		};

		float time;
		uint32_t thread_id;
		uint32_t task_id;
		union {
			Task* task; // EVENT_CREATE 
			struct {
				uint32_t parent_id;
				uint32_t scheduler_id;
			}; // EVENT_SCHEDULE
			bool will_yield; // EVENT_PAUSE
		};
		Type type;

		static TaskDebugEvent CreateEvent(uint32_t task_id, Task* task);
		static TaskDebugEvent ScheduleEvent(uint32_t task_id, uint32_t parent_id, uint32_t scheduler_id);
		static TaskDebugEvent CancelEvent(uint32_t task_id);
		static TaskDebugEvent ExecuteBeginEvent(uint32_t task_id);
		static TaskDebugEvent PauseEvent(uint32_t task_id, bool will_yield);
		static TaskDebugEvent ResumeEvent(uint32_t task_id);
		static TaskDebugEvent ExecuteEndEvent(uint32_t task_id);
		static TaskDebugEvent DestroyEvent(uint32_t task_id);

		typedef void(*DebugEventHandler)(SchedulerDebugEvent* scheduler_event, TaskDebugEvent* task_event);
		static void SetDebugEventHandler(DebugEventHandler handler);
	};
#endif

	/*!
		\class TaskSchedulingData
		\author Adam G. Smith
		\date December 2022
		\copyright MIT License
		\brief This structure contains the information that a Scheduler knows about a Task
	*/
	struct ANVIL_DLL_EXPORT TaskSchedulingData {
		typedef Scheduler::Priority Priority;

		mutable std::shared_mutex lock;
		Task* task;
		Scheduler* scheduler;			//!< Points to the scheduler handling this task, otherwise null
		TaskSchedulingData* parent;
		std::vector<TaskSchedulingData*> children;
		std::exception_ptr exception;	//!< Holds an exception that is caught during execution, thrown when wait is called
#if ANVIL_DEBUG_TASKS
		uint32_t debug_id;
#endif
		std::atomic_uint32_t reference_counter;
		uintptr_t priority;			//!< Stores the scheduling priority of the task
		uint8_t state;

		TaskSchedulingData();
		void Reset();

		bool AddChild(TaskSchedulingData*);
		bool RemoveChild(TaskSchedulingData*);
		bool DetachFromParent();
		bool DetachFromChildren();

		void SetExtendedPriority(uintptr_t value);
		void SetRegularPriority(Priority value);
		uintptr_t GetExtendedPriority() const;
		Priority GetRegularPriority() const;
	};

	struct ANVIL_DLL_EXPORT TaskDataLock {
		TaskSchedulingData& task_data;

		TaskDataLock(TaskSchedulingData& task_data_ref) :
			task_data(task_data_ref)
		{
			std::lock_guard<std::shared_mutex>lock(task_data.lock);
			++task_data.reference_counter;
		}

		~TaskDataLock() {
			std::lock_guard<std::shared_mutex>lock(task_data.lock);
			--task_data.reference_counter;
		}
	};

	/*!
		\class Task
		\author Adam G. Smith
		\date December 2020
		\copyright MIT License
		\brief Base structure for implementing Task based parallel programming.
		\details There are currently three optional compiler constants that can be defined (> 0) to enable extension features:
		These features are disabled by default to avoid any overheads that would be added to scheduling systems that don't need them.
	*/
	class ANVIL_DLL_EXPORT Task {
	public:
		/*!
			\brief Describes which point in the execution cycle a Task is in.
		*/
		enum State : uint8_t {
			STATE_INITIALISED,	//!< The task has been created and is ready to be scheduled.
			STATE_SCHEDULED,	//!< The task has been scheduled and is awaiting execution.
			STATE_EXECUTING,	//!< The task is currently running.
			STATE_BLOCKED,		//!< Execution was started but the Task is currently suspended.
			STATE_COMPLETE,		//!< The execution has finished
			STATE_CANCELED		//!< The task was canceled due to user request or an exception being thrown
		};

		typedef Scheduler::Priority Priority;
		typedef TaskSchedulingData Data;
	private:
		Task(Task&&) = delete;
		Task(const Task&) = delete;
		Task& operator=(Task&&) = delete;
		Task& operator=(const Task&) = delete; 

#if ANVIL_TASK_FIBERS
		static void WINAPI FiberFunction(LPVOID param);
#else
		static void FiberFunction(Task& param);
#endif

		/*!
			\brief Calls Task::OnExecution() with proper state changes and exception handling
		*/
		void ExecuteInScheduler() throw();

		void SetException(std::exception_ptr exception);

		void CatchException(std::exception_ptr&& exception, bool set_exception);

		TaskSchedulingData* _data;
	protected:
		/*!
			\brief Return control to the scheduler while the task is waiting for something.
			\details Should only be called during Task::Wait or Task::OnExecution.
			If the scheduler has tasks then it will execute them, otherwise the thread will be put to sleep.
			\param condition Returns true when the task is no longer waiting for something.
			\param max_sleep_milliseconds The longest period of time the thread should sleep for before checking the wait condition again.
		*/
		inline void Yield(const std::function<bool()>& condition, uint32_t max_sleep_milliseconds = 33u) {
			TaskDataLock task_lock(*_data);
			Scheduler* scheduler = _data->scheduler;
			if (scheduler) {
				scheduler->Yield(condition, max_sleep_milliseconds);
			} else {
				throw std::runtime_error("anvil::Task::Yield : Cannot yield without a scheduler");
			}
		}

		/*!
			\brief Implements the work payload of the task.
			\details Called by the scheduler when it is ready.
			An exception thrown by this call can be retrieved when Task::Wait() is called.
		*/
		virtual void OnExecution();

		/*!
			\brief Called when the task is being added to the scheduler's work queue.
			\details If an exception is thrown then the task goes into OnScheduled and the task will not be scheduled.
			The exception can be retrieved by calling Task::Wait().
		*/
		virtual void OnScheduled();

		/*!
			\brief Called when the task is being suspended by the scheduler (because Task::Yield() was called).
			\details Exceptions thrown are handled the same way as if thrown by the wait condition function.
		*/
		virtual void OnBlock();

		/*!
			\brief Called when a suspended task is about to resume execution.
			\details Exceptions thrown are handled the same way as if thrown by Task::Execute().
		*/
		virtual void OnResume();

		/*!
			\brief Called a task is canceled.
			\see Cancel
		*/
		virtual void OnCancel();

		/*!
			\brief Decide which order tasks scheduled with the same priority will execute
			\detail For 64-bit systems the lowest 56 bits will be used.
			\detail For 32-bit systems the lowest 24 bits will be used.
			\return Tasks returning a higher value will execute first
		*/
		virtual uintptr_t CalculateExtendedPriorty() const;

		virtual bool IsReadyToExecute() const throw();
	public:
		friend Scheduler;
		friend details::TaskThreadLocalData;

		/*!
			\brief Create a new task.
			\details State will be set to STATE_INITIALISED
		*/
		Task();

		/*!
			\brief Destroy the task
			\details Undefined behaviour if state is not STATE_INITIALISED, STATE_COMPLETE or STATE_CANCELED
		*/
		virtual ~Task();

		/*!
		*	\brief Execute the task immediately.
		*	\detail If called from a parent Task then this is the same as calling Scheduler::Schedule and Task::Wait.
		*	Otherwise executes on the current thread using a temporary scheduler, this possibly is not very efficient.
		*/
		void Execute();

		/*!
			\brief Wait for the task to complete.
			\detail If the task is not complete then Task::Yield will be called.
			If the task threw an exception during execution then it will be rethrown here.
			Subsequent calls to this function will have no effect.
		*/
		void Wait();

		/*!
			\brief Set the priority of this task.
			\details The scheduler will execute the task with the highest priority first.
			Will throw exception if the task's state is STATE_EXECUTING or STATE_BLOCKED.
		*/
		void SetPriority(Priority priority);

		/*!
			\brief Stop the task from being executed
			\details Called when an exception is thrown during scheduling or execution.
		*/
		bool Cancel() throw();

		/*!
			\return True if Task::Wait() can be called.
		*/
		inline bool IsWaitable() const throw() {
			return GetState() != STATE_INITIALISED;
		}

		/*!
			\return The current state of the Task.
		*/
		inline State GetState() const throw() {
			return static_cast<State>(_data->state);
		}

		/*!
			\return The current priority of the Task.
		*/
		inline Priority GetPriority() const throw() {
			return _data->GetRegularPriority();
		}

		/*!
			\return The parent of this task or null if there is no known parent
		*/
		inline Task* GetParent() const throw() {
			if (_data) {
				std::shared_lock<std::shared_mutex> lock(_data->lock);
				if (_data->parent) return _data->parent->task;
			}
			return nullptr;
		}

		/*!
			\return The a children of this task
		*/
		inline std::vector<Task*> GetChildren() const throw() {
			std::vector<Task*> children;
			std::lock_guard<std::shared_mutex> lock(_data->lock);
			if (_data) {
				for (TaskSchedulingData* tmp : _data->children) {
					Task* t = tmp->task;
					if (t) children.push_back(t);
				}
			}
			return children;
		}
		
		#pragma warning( disable : 4100) // Approximate child count no longer implemented, name is retained to improve code readability
		/*!
			\param aproximate If true then count will include children that previously existed but have since been destroyed (this is faster)
			\return The number of children this task has
		*/
		inline size_t GetChildCount(bool aproximate = false) const throw() {
			std::lock_guard<std::shared_mutex> lock(_data->lock);
			return _data->children.size();
		}

		inline size_t GetRecursiveChildCount(bool aproximate = false) const throw() {
			std::vector<Task*> children = GetChildren();
			size_t count = children.size();
			for (Task* i : children) count += i->GetRecursiveChildCount(aproximate); //! \bug Small chance of task completing and being destroyed while this is executing
			return count;
		}

		/*!
			\return Return the size of the inheritance tree for this task
		*/
		inline size_t GetNestingDepth() const throw() {
			size_t depth = 0u;
			Task* parent = GetParent();
			if (parent) depth += parent->GetNestingDepth() + 1u; //! \bug Small chance of task completing and being destroyed while this is executing
			return depth;
		}

		/*!
			\details Will thrown an exception if no scheduler is attached to this Task.
			\return The scheduler handling this Task.
		*/
		inline Scheduler& GetScheduler() const {
			Scheduler* const tmp = _data->scheduler;
			if (tmp == nullptr) throw std::runtime_error("Task is not attached to a scheduler");
			return *tmp;
		}

		/*!
			\brief Return the Task that is currently executing on this thread.
			\details Returns nullptr if there is no task executing on this thread.
		*/
		static ANVIL_STRONG_INLINE Task* GetCurrentlyExecutingTask() { return details::TaskThreadLocalData::Get().GetCurrentlyExecutingTask(); }

		/*!
			\brief Return a Task that is executing on this thread.
			\param Index the index in the execution stack, 0u is the first Task that started executing.
			\see GetNumberOfTasksExecutingOnThisThread()
		*/
		static ANVIL_STRONG_INLINE Task* GetCurrentlyExecutingTask(size_t index) { return details::TaskThreadLocalData::Get().GetCurrentlyExecutingTask(index); }

		/*!
			\brief Return the number of Tasks that are currently executing on this thread.
		*/
		static ANVIL_STRONG_INLINE size_t GetNumberOfTasksExecutingOnThisThread() { return details::TaskThreadLocalData::Get().GetNumberOfTasksExecutingOnThisThread(); }

#if ANVIL_DEBUG_TASKS
		void PrintDebugMessage(const char* message) const;

		inline uint64_t GetDebugID() const { return _data->debug_id; }
#endif

	};

	/*!
		\class Task
		\author Adam G. Smith
		\date December 2020
		\copyright MIT License
		\brief Extends the Task structure to allow for a return values.
		\details Call TaskWithReturn::Get() instead of Task::Wait() to obtain the result.
		\see Task
	*/
	template<class R>
	class TaskWithReturn : public Task {
	public:
		typedef R Result;
	private:
		Result _result;
	protected:
		inline void SetResult(Result result) {
			_result = result;
		}
	public:
		TaskWithReturn() :
			Task()
		{}

		virtual ~TaskWithReturn() {

		}

		/*!
			\brief Wait for the task to complete then return the result.
			\return The value returned by task execution.
			\see Wait
		*/
		Result& Get() {
			Wait();
			return _result;
		}

	};

}

#endif