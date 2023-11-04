//MIT LicenseStrongSchedulingPtr
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

#ifndef ANVIL_SCHEDULER_SCHEDULER_HPP
#define ANVIL_SCHEDULER_SCHEDULER_HPP

#include <shared_mutex>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <functional>
#include <memory>
#include "anvil/core/CPU.hpp"
#include "anvil/scheduling/Core.hpp"
#include "anvil/scheduling/details/ThreadLocal.hpp"

namespace anvil {

	struct TaskThreadLocalData;

	class ANVIL_DLL_EXPORT Scheduler {
	public:
		enum FeatureFlag : uint32_t {
			FEATURE_ONLY_EXECUTE_ON_WORKER_THREADS	= 1u << 0u, //!< Previously known as ANVIL_NO_EXECUTE_ON_WAIT
			FEATURE_TASK_CALLBACKS					= 1u << 1u, //!< Previously known as ANVIL_TASK_CALLBACKS
			FEATURE_DELAYED_SCHEDULING				= 1u << 2u, //!< Previously known as ANVIL_TASK_DELAY_SCHEDULING
			FEATURE_EXTENDED_PRIORITY				= 1u << 3u, //!< Previously known as ANVIL_TASK_EXTENDED_PRIORITY

			DEFAULT_FEATURES = 0u
				// Backwards compatibility with old versions
#if ANVIL_TASK_DELAY_SCHEDULING
				| FEATURE_DELAYED_SCHEDULING
#endif
#if ANVIL_TASK_CALLBACKS
				| FEATURE_TASK_CALLBACKS
#endif
#if ANVIL_NO_EXECUTE_ON_WAIT
				| FEATURE_ONLY_EXECUTE_ON_WORKER_THREADS
#endif
#if FEATURE_EXTENDED_PRIORITY
				| FEATURE_EXTENDED_PRIORITY
#endif
		};

		struct ThreadDebugData {
			details::TaskThreadLocalData* thread_local_data;
			std::atomic_uint32_t tasks_executing;
			std::atomic_uint32_t sleeping;
			std::atomic_uint32_t enabled;

			ThreadDebugData();
		};

		struct SchedulerDebugData {
			ThreadDebugData* thread_debug_data;
			std::atomic_uint32_t total_thread_count;
			std::atomic_uint32_t executing_thread_count;
			std::atomic_uint32_t sleeping_thread_count;
			std::atomic_uint32_t total_tasks_executing;
			std::atomic_uint32_t total_tasks_queued;

			SchedulerDebugData();
		};
	private:
		static TaskSchedulingData* AllocateTaskSchedulingData();
		static void FreeTaskSchedulingData(TaskSchedulingData*);

		Scheduler(Scheduler&&) = delete;
		Scheduler(const Scheduler&) = delete;
		Scheduler& operator=(Scheduler&&) = delete;
		Scheduler& operator=(const Scheduler&) = delete;

		std::vector<TaskSchedulingData*> _unready_task_queue;	//!< Contains tasks that have been scheduled but are not yet ready to execute
		std::vector<TaskSchedulingData*> _task_queue;			//!< Contains tasks that have been scheduled and are ready to execute
		void SortTaskQueue(bool recalculate_extended_priority, bool check_delayed_tasks) throw();

		void RemoveNextTaskFromQueue(TaskSchedulingData** tasks, uint32_t& count) throw();

		/*!
			\brief Called when a Task has been added or removed from the queue
			\details Wakes up threads that were sleeping and performs some additional scheduling logic
		*/
		void TaskQueueNotify();
	protected:
		SchedulerDebugData _scheduler_debug;
		std::condition_variable _task_queue_update;
		std::shared_mutex _task_queue_mutex;
		std::mutex _condition_mutex;
#if ANVIL_DEBUG_TASKS
		uint32_t _debug_id;
#endif
		uint32_t _feature_flags;

		bool TryToExecuteTask() throw();

	public:
		enum : uintptr_t {
			MAIN_PRIORITY_BITS = 8u,
			EXTENDED_PRIORITY_BITS = ANVIL_CPU_ARCHITECTURE_BITS - MAIN_PRIORITY_BITS,
			EXTENDED_PRIORITY_MASK = static_cast<uintptr_t>((1ull << EXTENDED_PRIORITY_BITS) - 1ull)
		};

		enum Priority : uint8_t {
			PRIORITY_LOWEST = 0u,										//!< The lowest prority level supported by the Scheduler.
			PRIORITY_HIGHEST = (1 << MAIN_PRIORITY_BITS) - 1,			//!< The highest prority level supported by the Scheduler.
			PRIORITY_MIDDLE = PRIORITY_HIGHEST / 2u,					//!< The default priority level.
			PRIORITY_HIGH = PRIORITY_MIDDLE + (PRIORITY_MIDDLE / 2u),	//!< Halfway between PRIORITY_MIDDLE and PRIORITY_HIGHEST.
			PRIORITY_LOW = PRIORITY_MIDDLE - (PRIORITY_MIDDLE / 2u)		//!< Halfway between PRIORITY_MIDDLE and PRIORITY_LOWEST.
		};//!< Defines the order in which Tasks are executed.

		friend Task;
		friend TaskSchedulingData;
		friend details::TaskThreadLocalData;

		Scheduler(size_t thread_count, uint32_t feature_flags);
		virtual ~Scheduler();

		inline void RegisterAsWorkerThread() { details::TaskThreadLocalData::Get().RegisterAsWorkerThread(*this); }

		void Yield(const std::function<bool()>& condition, uint32_t max_sleep_milliseconds = 1u);

		void Schedule(Task** tasks, uint32_t count);
		void Schedule(std::shared_ptr<Task>* tasks, uint32_t count);

		void Schedule(Task* task, Priority priority);

		inline void Schedule(std::shared_ptr<Task> task, Priority priority) {
			Schedule(task.get(), priority);
		}

		inline void Schedule(Task& task) {
			Task* t = &task;
			Schedule(&t, 1u);
		}

		template<class T>
		inline void Schedule(const std::unique_ptr<T>& task) {
			static_assert(std::is_base_of<Task, T>::value, "Class T is not a Task");
			Schedule(*task);
		}

		template<class T>
		inline void Schedule(const std::shared_ptr<T>& task) {
			static_assert(std::is_base_of<Task, T>::value, "Class T is not a Task");
			Schedule(*task);
		}

		template<>
		inline void Schedule<Task>(const std::unique_ptr<Task>& task) {
			Schedule(*task);
		}

		template<>
		inline void Schedule<Task>(const std::shared_ptr<Task>& task) {
			Schedule(*task);
		}

		template<class T>
		inline void Schedule(std::shared_ptr<T>* tasks, uint32_t count) {
			static_assert(std::is_base_of<Task, T>::value, "Class T is not a Task");
			Schedule(reinterpret_cast<std::shared_ptr<Task>*>(tasks), count);
		}

		template<class T>
		void Schedule(std::unique_ptr<T>* tasks, uint32_t count) {
			static_assert(std::is_base_of<Task, T>::value, "Class T is not a Task");
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

		template<class T>
		void Schedule(T* tasks, uint32_t count) {
			static_assert(std::is_base_of<Task, T>::value, "Class T is not a Task");
			enum { TASK_BLOCK = 1024 };
			Task* tasks2[TASK_BLOCK];
			while (count > 0) {
				const uint32_t tasks_to_add = count > TASK_BLOCK ? TASK_BLOCK : count;

				for (uint32_t i = 0u; i < tasks_to_add; ++i) tasks2[i] = &tasks[i];
				Schedule(tasks2, tasks_to_add);

				tasks += tasks_to_add;
				count -= tasks_to_add;
			}
		}

		template<class T>
		inline void Schedule(const std::vector<T>& tasks) {
			Schedule(tasks.data(), static_cast<uint32_t>(tasks.size()));
		}

#if ANVIL_DEBUG_TASKS
		void PrintDebugMessage(const char* message) const;
#endif

		inline uint32_t GetThisThreadIndex() const {
			return details::TaskThreadLocalData::Get()._scheduler_index;
		}

		inline bool IsWorkerThread() const {
			return details::TaskThreadLocalData::Get()._scheduler == this;
		}

		inline ThreadDebugData* GetDebugDataForThread(const uint32_t index) {
			return index > _scheduler_debug.total_thread_count ? nullptr : _scheduler_debug.thread_debug_data + index;
		}

		inline ThreadDebugData* GetDebugDataForThisThread() { 
			return IsWorkerThread() ? GetDebugDataForThread(GetThisThreadIndex()) : nullptr;
		}


		inline SchedulerDebugData& GetDebugData() {
			_scheduler_debug.sleeping_thread_count = _scheduler_debug.total_thread_count - _scheduler_debug.executing_thread_count;
			_scheduler_debug.total_tasks_queued = static_cast<uint32_t>(_task_queue.size());
			return _scheduler_debug;
		}

		/*!
			\brief Return the total number of threads.
		*/
		inline size_t GetThreadCount() const throw() { return const_cast<Scheduler*>(this)->GetDebugData().total_thread_count; }

		/*!
			\brief Return the number of threads that are currently executing tasks.
		*/
		inline size_t GetExecutingThreadCount() const throw() { return const_cast<Scheduler*>(this)->GetDebugData().executing_thread_count; }

		/*!
			\brief Return the number of threads that are currently not executing tasks.
		*/
		inline size_t GetSleepingThreadCount() const throw() { return const_cast<Scheduler*>(this)->GetDebugData().sleeping_thread_count; }
	};
}

#endif