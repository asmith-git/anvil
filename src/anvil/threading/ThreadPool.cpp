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

#include <algorithm>
#include "anvil/threading/ThreadPool.hpp"

namespace anvil {

	struct ThreadPoolHandle {
		std::condition_variable wait_condition;
		std::atomic_bool complete;
		std::exception_ptr exception;
		Task task;
		void* param;
		uint64_t index;
		uint8_t priority;
	};

	// WorkerThread
	
	ANVIL_CALL ThreadPool::WorkerThread::WorkerThread(ThreadPool* aPool) :
		mPool(aPool)
	{
		mLock = false;
		mThread = std::thread(&WorkerThread::worker, this);
	}

	void ANVIL_CALL ThreadPool::WorkerThread::lock() const throw() {
		bool expected = false;
		while (! mLock.compare_exchange_strong(expected, true)) {
			expected = false;
		}
	}

	void ANVIL_CALL ThreadPool::WorkerThread::unlock() const throw() {
		bool expected = true;
		mLock.compare_exchange_strong(expected, false);
	}

	bool ANVIL_CALL ThreadPool::WorkerThread::try_lock() const throw() {
		bool expected = true;
		return mLock.compare_exchange_strong(expected, false);
	}

	size_t ANVIL_CALL ThreadPool::WorkerThread::threadCount() const throw() {
		return 1;
	}

	size_t ANVIL_CALL ThreadPool::WorkerThread::activeThreads() const throw() {
		return mCurrent ? 1 : 0;
	}

	size_t ANVIL_CALL ThreadPool::WorkerThread::queuedTasks() const throw() {
		size_t tmp = 0;
		lock();
		tmp = mQueued.size() + (mCurrent ? 1 : 0);
		unlock();
		return tmp;
	}

	void ANVIL_CALL ThreadPool::WorkerThread::join() throw() {
		mTaskAdded.notify_all();
		mThread.join();
	}

	TaskHandle ANVIL_CALL ThreadPool::WorkerThread::enqueue(uint8_t aPriority, Task aTask, void* aParam) throw() {
		ThreadPoolHandle* handle = new ThreadPoolHandle();
		handle->complete = false;
		handle->task = aTask;
		handle->param = aParam;
		handle->priority = aPriority;
		handle->index = ++mPool->mIndex;

		lock();
		mQueued.push_back(handle);
		std::sort(mQueued.begin(), mQueued.end(), [](TaskHandle a, TaskHandle b)->bool {
			return static_cast<ThreadPoolHandle*>(a)->priority > static_cast<ThreadPoolHandle*>(b)->priority ?
				true : static_cast<ThreadPoolHandle*>(a)->index > static_cast<ThreadPoolHandle*>(b)->index;
		});
		unlock();
		mTaskAdded.notify_all();
		return handle;
	}

	bool ANVIL_CALL ThreadPool::WorkerThread::wait(TaskHandle aTask, std::exception_ptr* aException) const throw() {
		return mPool->wait(aTask, aException);
	}

	bool ANVIL_CALL ThreadPool::WorkerThread::cancel(TaskHandle aTask) throw() {
		lock();
		auto end = mQueued.end();
		auto i = std::find(mQueued.begin(), end, aTask);
		if (i == end) {
			unlock();
			return false;
		} else {
			mQueued.erase(i);
			unlock();
			ThreadPoolHandle* const h = static_cast<ThreadPoolHandle*>(aTask);
			h->complete = true;
			h->wait_condition.notify_all();
			return true;
		}
	}

	uint8_t ANVIL_CALL ThreadPool::WorkerThread::getPriority(TaskHandle aTask) const throw() {
		return mPool->getPriority(aTask);
	}

	bool ANVIL_CALL ThreadPool::WorkerThread::setPriority(TaskHandle aTask, uint8_t aPriority) throw() {
		lock();
		auto end = mQueued.end();
		auto i = std::find(mQueued.begin(), end, aTask);
		if (i == end) {
			unlock();
			return false;
		} else {
			ThreadPoolHandle* const h = static_cast<ThreadPoolHandle*>(aTask);
			h->priority = aPriority;
			std::sort(mQueued.begin(), mQueued.end(), [](TaskHandle a, TaskHandle b)->bool {
				return static_cast<ThreadPoolHandle*>(a)->priority > static_cast<ThreadPoolHandle*>(b)->priority ?
					true : static_cast<ThreadPoolHandle*>(a)->index > static_cast<ThreadPoolHandle*>(b)->index;
			});
			unlock();
			return true;
		}
	}

	bool ANVIL_CALL ThreadPool::WorkerThread::waitAll() const throw() {
		std::vector<TaskHandle> tmp;
		lock();
		tmp = mQueued;
		unlock();

		bool return_value = true;
		for (TaskHandle i : tmp) {
			return_value = return_value && wait(i, nullptr);
		}
		return true;
	}

	bool ANVIL_CALL ThreadPool::WorkerThread::cancelAll() throw() {
		std::vector<TaskHandle> tmp;
		lock();
		mQueued.swap(tmp);
		unlock();
		for (TaskHandle i : tmp) {
			ThreadPoolHandle* const h = static_cast<ThreadPoolHandle*>(i);
			h->complete = true;
			h->wait_condition.notify_all();
		}
		mTaskAdded.notify_all();
		return true;
	}

	void ANVIL_CALL ThreadPool::WorkerThread::worker() throw() {
		//! \todo Implement work stealing 

		std::mutex mutex;
		while (! mPool->mExitFlag) {
		{
				std::unique_lock<std::mutex> lock(mutex);
				mTaskAdded.wait(lock);
		}
		if (mPool->mExitFlag) break;
			lock();
CHECK_TASKS:
			if (mQueued.empty()) {
				unlock();
			} else {
				ThreadPoolHandle* task = static_cast<ThreadPoolHandle*>(mQueued.back());
				mQueued.pop_back();
				unlock();
				try {
					task->task(task->param);
				} catch (std::exception& e) {
					task->exception = std::make_exception_ptr(e);
				}
				task->complete = true;
				mCompleted.push_back(task);
				task->wait_condition.notify_all();
				lock();
				goto CHECK_TASKS;
			}
		}

		for (TaskHandle i : mCompleted) {
			delete static_cast<ThreadPoolHandle*>(i);
		}
	}

	// ThreadPool

	ANVIL_CALL ThreadPool::ThreadPool(size_t aSize) throw() {
		mExitFlag = false;
		mIndex = 0;
		for (size_t i = 0; i < aSize; ++i) {
			mThreads.push_back(std::shared_ptr<WorkerThread>(new WorkerThread(this)));
		}
	}

	ANVIL_CALL ThreadPool::~ThreadPool() throw() {
		mExitFlag = true;
		for (std::shared_ptr<WorkerThread>& i : mThreads) {
			i->cancelAll();
			i->join();
		}
	}

	size_t ANVIL_CALL ThreadPool::threadCount() const throw() {
		return mThreads.size();
	}

	size_t ANVIL_CALL ThreadPool::activeThreads() const throw() {
		size_t count = 0;
		for (const std::shared_ptr<WorkerThread>& i : mThreads) {
			if (i->queuedTasks() > 0) ++count;
		}
		return count;
	}

	size_t ANVIL_CALL ThreadPool::queuedTasks() const throw() {
		size_t count = 0;
		for (const std::shared_ptr<WorkerThread>& i : mThreads) {
			count += i->queuedTasks();
		}
		return count;
	}

	TaskHandle ANVIL_CALL ThreadPool::enqueue(uint8_t aPriority, Task aTask, void* aParam) throw() {
		if (! aTask) return nullptr;

		const size_t count = mThreads.size();
		std::shared_ptr<WorkerThread> low = mThreads[0];
		size_t tasks = low->queuedTasks();
		for (size_t i = 1; i < count; ++i)  {
			size_t tmp = mThreads[i]->queuedTasks();
			if (tmp < tasks) {
				low = mThreads[i];
				tasks = tmp;
			}
		}

		return low->enqueue(aPriority, aTask, aParam);
	}

	bool ANVIL_CALL ThreadPool::wait(TaskHandle aTask, std::exception_ptr* aException) const throw() {
		ThreadPoolHandle* const handle = static_cast<ThreadPoolHandle*>(aTask);
		if (!handle) return false;
		if (handle->complete) {
			if (aException && handle->exception) *aException = handle->exception;
			return true;
		}
		std::mutex lock_;
		std::unique_lock<std::mutex> lock(lock_);
		handle->wait_condition.wait(lock);
		return false;
	}

	bool ANVIL_CALL ThreadPool::cancel(TaskHandle aHandle) throw() {
		for (std::shared_ptr<WorkerThread>& i : mThreads) {
			if (i->cancel(aHandle)) return true;
		}
		return false;
	}

	uint8_t ANVIL_CALL ThreadPool::getPriority(TaskHandle aHandle) const throw() {
		ThreadPoolHandle* const handle = static_cast<ThreadPoolHandle*>(aHandle);
		return handle == nullptr ? 0 : handle->priority;
	}

	bool ANVIL_CALL ThreadPool::setPriority(TaskHandle aHandle, uint8_t aPriority) throw() {
		for (std::shared_ptr<WorkerThread>& i : mThreads) {
			if (i->setPriority(aHandle, aPriority)) return true;
		}
		return false;
	}

	bool ANVIL_CALL ThreadPool::waitAll() const throw() {
		bool return_value = true;
		for (const std::shared_ptr<WorkerThread>& i : mThreads) {
			return_value = return_value && i->waitAll();
		}
		return false;
	}

	bool ANVIL_CALL ThreadPool::cancelAll() throw() {
		bool return_value = true;
		for (std::shared_ptr<WorkerThread>& i : mThreads) {
			return_value = return_value && i->cancelAll();
		}
		return false;
	}
}