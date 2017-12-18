//Copyright 2017 Adam G. Smith
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//http ://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.

#ifndef ANVIL_THREADING_THREAD_POOL_HPP
#define ANVIL_THREADING_THREAD_POOL_HPP

#include <vector>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>
#include "anvil/threading/Task.hpp"

namespace anvil {

	class ThreadPool : public TaskDispatcher {
	private:
		class WorkerThread : public TaskDispatcher {
		private:
			TaskHandle mCurrent;
			std::vector<TaskHandle> mQueued;
			ThreadPool* mPool;
			std::thread mThread;
			mutable std::atomic_bool mLock;
			std::condition_variable mTaskAdded;

			void ANVIL_CALL worker() throw();
		public:
			ANVIL_CALL WorkerThread(ThreadPool*);

			void ANVIL_CALL lock() const throw();
			void ANVIL_CALL unlock() const throw();
			bool ANVIL_CALL try_lock() const throw();

			void ANVIL_CALL join() throw();

			// Inherited from TaskDispatcher

			size_t ANVIL_CALL threadCount() const throw() override;
			size_t ANVIL_CALL activeThreads() const throw() override;
			size_t ANVIL_CALL queuedTasks() const throw() override;

			TaskHandle ANVIL_CALL enqueue(uint8_t, Task, void*) throw() override;
			bool ANVIL_CALL wait(TaskHandle, std::exception_ptr*) const throw() override;
			bool ANVIL_CALL cancel(TaskHandle) throw() override;
			uint8_t ANVIL_CALL getPriority(TaskHandle) const throw() override;
			bool ANVIL_CALL setPriority(TaskHandle, uint8_t) throw() override;
			bool ANVIL_CALL waitAll() const throw() override;
			bool ANVIL_CALL cancelAll() throw() override;
		};

		std::vector<WorkerThread> mThreads;
		std::atomic_bool mExitFlag;
		uint64_t mIndex;

		ThreadPool(ThreadPool&&) = delete;
		ThreadPool(const ThreadPool&) = delete;
		ThreadPool& operator=(ThreadPool&&) = delete;
		ThreadPool& operator=(const ThreadPool&) = delete;
	public:
		ANVIL_CALL ThreadPool(size_t) throw();
		ANVIL_CALL ~ThreadPool() throw();

		// Inherited from TaskDispatcher

		size_t ANVIL_CALL threadCount() const throw() override;
		size_t ANVIL_CALL activeThreads() const throw() override;
		size_t ANVIL_CALL queuedTasks() const throw() override;

		TaskHandle ANVIL_CALL enqueue(uint8_t, Task, void*) throw() override;
		bool ANVIL_CALL wait(TaskHandle, std::exception_ptr*) const throw() override;
		bool ANVIL_CALL cancel(TaskHandle) throw() override;
		uint8_t ANVIL_CALL getPriority(TaskHandle) const throw() override;
		bool ANVIL_CALL setPriority(TaskHandle, uint8_t) throw() override;
		bool ANVIL_CALL waitAll() const throw() override;
		bool ANVIL_CALL cancelAll() throw() override;
	};
}

#endif