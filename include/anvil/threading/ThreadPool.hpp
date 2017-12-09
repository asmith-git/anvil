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
		mutable std::mutex mLock;
		std::vector<std::thread> mThreads;
		std::vector<TaskHandle> mTasks;
		std::condition_variable mTaskAdded;
		std::atomic_uint32_t mActiveThreads;
		std::atomic_bool mExitFlag;
		uint64_t mIndex;

		void worker(size_t) throw();

		ThreadPool(ThreadPool&&) = delete;
		ThreadPool(const ThreadPool&) = delete;
		ThreadPool& operator=(ThreadPool&&) = delete;
		ThreadPool& operator=(const ThreadPool&) = delete;
	public:
		ThreadPool(size_t) throw();
		~ThreadPool() throw();

		// Inherited from TaskDispatcher

		size_t threadCount() const throw() override;
		size_t activeThreads() const throw() override;
		size_t queuedTasks() const throw() override;

		TaskHandle enqueue(uint8_t, Task, void*) throw() override;
		bool wait(TaskHandle, std::exception_ptr*) const throw() override;
		bool cancel(TaskHandle) throw() override;
		uint8_t getPriority(TaskHandle) const throw() override;
		bool setPriority(TaskHandle, uint8_t) throw() override;
		bool waitAll() const throw() override;
		bool cancelAll() throw() override;
	};
}

#endif