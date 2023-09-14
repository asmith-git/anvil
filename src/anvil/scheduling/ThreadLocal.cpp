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

#include "anvil/scheduling/details/ThreadLocal.hpp"
#include <atomic>

namespace anvil {

	static std::atomic_uint32_t g_next_thread_index = UINT32_MAX;
	thread_local TaskThreadLocalData g_thread_additional_data;

	// TaskThreadLocalData

	TaskThreadLocalData::TaskThreadLocalData() :
		scheduler(nullptr),
#if ANVIL_TASK_FIBERS
		current_fiber(nullptr),
		main_fiber(nullptr),
#endif
		scheduler_index(g_next_thread_index--),
		is_worker_thread(false)
	{}

	TaskThreadLocalData::~TaskThreadLocalData() {
#if ANVIL_TASK_FIBERS
		// Delete old fibers
		for (FiberData* fiber : fiber_list) {
			DeleteFiber(fiber->fiber);
			delete fiber;
		}
		fiber_list.clear();
#endif
	}

	bool TaskThreadLocalData::AreAnyFibersReady() const {
		if (!fiber_list.empty()) {
			auto end = fiber_list.end();
			auto i = std::find_if(fiber_list.begin(), end, [this](FiberData* fiber)->bool {
				return fiber != current_fiber && fiber->task != nullptr && (fiber->yield_condition == nullptr || (*fiber->yield_condition)());
				});
			return i != end;
		}

		return false;
	}

	bool TaskThreadLocalData::SwitchToTask(FiberData& fiber) {
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

	bool TaskThreadLocalData::SwitchToAnyTask() {
		// Try to execute a task that is ready to resume
	RETRY:
		if (!fiber_list.empty()) {
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

	void TaskThreadLocalData::SwitchToMainFiber2() {
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

	void TaskThreadLocalData::SwitchToMainFiber() {
		// Are we currently executing the main fiber?
		if (current_fiber == nullptr) return;

		// Switch to it
		current_fiber = nullptr;
		SwitchToFiber(main_fiber);
	}

	TaskThreadLocalData& TaskThreadLocalData::Get() {
		return g_thread_additional_data;
	}


	Task* TaskThreadLocalData::GetCurrentlyExecutingTask() const {
		if (current_fiber) return current_fiber->task;
		if (!task_stack.empty()) return task_stack.back();
		return nullptr;
	}

	Task* TaskThreadLocalData::GetCurrentlyExecutingTask(size_t index) const {
		size_t count = 0u;
		for (const FiberData* fiber : g_thread_additional_data.fiber_list) {
			if (fiber->task != nullptr) {
				if (count == index) return fiber->task;
				++count;
			}
		}

		if (index >= g_thread_additional_data.task_stack.size()) return nullptr;
		return g_thread_additional_data.task_stack[index];
	}

	size_t TaskThreadLocalData::GetNumberOfTasksExecutingOnThisThread() const {
		size_t count = 0u;

		for (const FiberData* fiber : fiber_list) {
			if (fiber->task != nullptr) ++count;
		}

		count += g_thread_additional_data.task_stack.size();

		return count;
	}
}