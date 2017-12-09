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

	struct TaskHandle_ {
		std::condition_variable wait_condition;
		std::atomic_bool complete;
		std::exception_ptr exception;
		Task task;
		void* param;
		uint64_t index;
		uint8_t priority;
	};

	// ThreadPool

	void ThreadPool::worker(size_t aIndex) throw() {
		std::vector<TaskHandle> completed;
		while (!mExitFlag) {
			{
				std::unique_lock<std::mutex> lock(mLock);
				mTaskAdded.wait(lock);
			}
			if (mExitFlag) break;
			mLock.lock();
		CHECK_TASKS:
			if (mTasks.empty()) {
				mLock.unlock();
			} else {
				++mActiveThreads;
				TaskHandle task = mTasks.back();
				mTasks.pop_back();
				mLock.unlock();
				try {
					task->task(task->param);
				} catch (std::exception& e) {
					task->exception = std::make_exception_ptr(e);
				}
				task->complete = true;
				completed.push_back(task);
				task->wait_condition.notify_all();
				mLock.lock();
				--mActiveThreads;
				goto CHECK_TASKS;
			}
		}
		for (TaskHandle i : completed) delete i;
	}

	ThreadPool::ThreadPool(size_t aSize) throw() {
		mExitFlag = false;
		mActiveThreads = 0;
		mIndex = 0;
		for (size_t i = 0; i < aSize; ++i) {
			mThreads.push_back(std::thread(&ThreadPool::worker, this, i));
		}
	}

	ThreadPool::~ThreadPool() throw() {
		mExitFlag = true;
		mTaskAdded.notify_all();
		for (std::thread& i : mThreads) i.join();
	}

	size_t ThreadPool::threadCount() const throw() {
		return mThreads.size();
	}

	size_t ThreadPool::activeThreads() const throw() {
		return mActiveThreads;
	}

	size_t ThreadPool::queuedTasks() const throw() {
		mLock.lock();
		const size_t tmp = mTasks.size();
		mLock.unlock();
		return tmp;
	}

	TaskHandle ThreadPool::enqueue(uint8_t aPriority, Task aTask, void* aParam) throw() {
		if (! aTask) return nullptr;
		TaskHandle handle = new TaskHandle_();
		handle->complete = false;
		handle->task = aTask;
		handle->param = aParam;
		handle->priority = aPriority;
		mLock.lock();
		handle->index = ++mIndex;
		mTasks.push_back(handle);
		std::sort(mTasks.begin(), mTasks.end(), [](TaskHandle a, TaskHandle b)->bool {
			return a->priority > b->priority ? true : a->index > b->index;
		});
		mLock.unlock();
		mTaskAdded.notify_one();
		return handle;
	}

	bool ThreadPool::wait(TaskHandle aTask, std::exception_ptr* aException) const throw() {
		if (!aTask) return false;
		if (aTask->complete) {
			if (aException && aTask->exception) *aException = aTask->exception;
			return true;
		}
		std::unique_lock<std::mutex> lock(mLock);
		aTask->wait_condition.wait(lock);
		return true;
	}

	bool ThreadPool::cancel(TaskHandle aHandle) throw() {
		mLock.lock();
		const auto end = mTasks.end();
		const auto i = std::find(mTasks.begin(), mTasks.end(), aHandle);
		if (i == end) {
			mLock.unlock();
			return false;
		} else {
			mTasks.erase(i);
			mLock.unlock();
			TaskHandle task = *i;
			task->complete = true;
			task->wait_condition.notify_all();
			return true;
		}
	}

	uint8_t ThreadPool::getPriority(TaskHandle aHandle) const throw() {
		return aHandle == nullptr ? 0 : aHandle->priority;
	}

	bool ThreadPool::setPriority(TaskHandle aHandle, uint8_t aPriority) throw() {
		if (aHandle == nullptr || aHandle->complete) return false;
		mLock.lock();
		const auto end = mTasks.end();
		const auto i = std::find(mTasks.begin(), mTasks.end(), aHandle);
		if (i == end) {
			mLock.unlock();
			return false;
		} else {
			mTasks.erase(i);
			aHandle->priority = aPriority;
			mTasks.push_back(aHandle);
			std::sort(mTasks.begin(), mTasks.end(), [](TaskHandle a, TaskHandle b)->bool {
				return a->priority > b->priority ? true : a->index > b->index;
			});
			mLock.unlock();
			return true;
		}
		return true;
	}

	bool ThreadPool::waitAll() const throw() {
		mLock.lock();
		if (mTasks.empty()) {
			mLock.unlock();
			return false;
		}
		std::vector<TaskHandle> tasks = mTasks;
		mLock.unlock();
		for (TaskHandle i : tasks) if (! wait(i, nullptr)) return false;
		return true;
	}

	bool ThreadPool::cancelAll() throw() {
		mLock.lock();
		for (TaskHandle i : mTasks) {
			i->complete = true;
			i->wait_condition.notify_all();
		}
		mTasks.clear();
		mLock.unlock();
		return true;
	}
}