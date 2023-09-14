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
#include "anvil/scheduling/Task.hpp"
#include <atomic>

namespace anvil { namespace details {

	static std::atomic_uint32_t g_next_thread_index = UINT32_MAX;
	thread_local TaskThreadLocalData g_thread_additional_data;

	// TaskThreadLocalData

	TaskThreadLocalData::TaskThreadLocalData() :
		_scheduler(nullptr),
		_current_fiber(nullptr),
		_main_fiber(nullptr),
		_scheduler_index(g_next_thread_index--),
		_is_worker_thread(false),
		_using_fibers(static_cast<bool>(ANVIL_TASK_FIBERS))
	{}

	TaskThreadLocalData::~TaskThreadLocalData() {
		// Delete old fibers
		for (FiberData* fiber : _fiber_list) {
			DeleteFiber(fiber->fiber);
			delete fiber;
		}
		_fiber_list.clear();
	}

	bool TaskThreadLocalData::AreAnyFibersReady() const {
		if (!_fiber_list.empty()) {
			auto end = _fiber_list.end();
			auto i = std::find_if(_fiber_list.begin(), end, [this](FiberData* fiber)->bool {
				return fiber != _current_fiber && fiber->task != nullptr && (fiber->yield_condition == nullptr || (*fiber->yield_condition)());
				});
			return i != end;
		}

		return false;
	}

	bool TaskThreadLocalData::SwitchToTask(FiberData& fiber) {
		if (&fiber == _current_fiber) return false;

		// If the task is able to execute
		if (fiber.task != nullptr) {
			if (fiber.yield_condition == nullptr || (*fiber.yield_condition)()) {
				_current_fiber = &fiber;
				SwitchToFiber(fiber.fiber);
				return true;
			}
		}

		return false;
	}

	bool TaskThreadLocalData::SwitchToAnyTask() {
		// Try to execute a task that is ready to resume
	RETRY:
		if (!_fiber_list.empty()) {
			auto end = _fiber_list.end();
			auto i = std::find_if(_fiber_list.begin(), end, [this](FiberData* fiber)->bool {
				return fiber != _current_fiber && fiber->task != nullptr && (fiber->yield_condition == nullptr || (*fiber->yield_condition)());
				});
			if (i != end) {
				FiberData* fiber = *i;

				if (fiber->task && fiber->task->_data->scheduler == nullptr) {
					fiber->task = nullptr;
					goto RETRY;
				}

				// Move fiber to the back of the list
				_fiber_list.erase(i);
				_fiber_list.push_back(fiber);

				// Switch to the fiber
				_current_fiber = fiber;
				SwitchToFiber(fiber->fiber);
				return true;
			}
		}

		return false;
	}

	void TaskThreadLocalData::SwitchToMainFiber2() {
		// Only switch to the main fiber if there are no other fibers
		const auto HasOtherFiber = [this]()->bool {
			for (FiberData* fiber : _fiber_list) {
				if (fiber == _current_fiber) continue;
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
		if (_current_fiber == nullptr) return;

		// Switch to it
		_current_fiber = nullptr;
		SwitchToFiber(_main_fiber);
	}

	TaskThreadLocalData& TaskThreadLocalData::Get() {
		return g_thread_additional_data;
	}


	Task* TaskThreadLocalData::GetCurrentlyExecutingTask() const {
		if (_current_fiber) return _current_fiber->task;
		if (!_task_stack.empty()) return _task_stack.back();
		return nullptr;
	}

	Task* TaskThreadLocalData::GetCurrentlyExecutingTask(size_t index) const {
		size_t count = 0u;
		for (const FiberData* fiber : _fiber_list) {
			if (fiber->task != nullptr) {
				if (count == index) return fiber->task;
				++count;
			}
		}

		if (index >= _task_stack.size()) return nullptr;
		return _task_stack[index];
	}

	size_t TaskThreadLocalData::GetNumberOfTasksExecutingOnThisThread() const {
		size_t count = 0u;

		for (const FiberData* fiber : _fiber_list) {
			if (fiber->task != nullptr) ++count;
		}

		count += _task_stack.size();

		return count;
	}
	
	void TaskThreadLocalData::RegisterAsWorkerThread(Scheduler& scheduler) {
		_is_worker_thread = true;

		if (_using_fibers) {
			_main_fiber = ConvertThreadToFiber(nullptr);

		} else if (scheduler._scheduler_debug.thread_debug_data != nullptr) {
			_scheduler = &scheduler;
			_scheduler_index = scheduler._scheduler_debug.total_thread_count++;
			auto& debug_data = scheduler._scheduler_debug.thread_debug_data[_scheduler_index];
			debug_data.tasks_executing = 0u;
			debug_data.sleeping = 0u;
			debug_data.enabled = 1u;
			debug_data.thread_local_data = this;
			++scheduler._scheduler_debug.executing_thread_count; // Default state is executing
		}
	}

	/*!
	*	\brief Begin tracking the nessersary information needed for the execution of a Task.
	*	\param task The task that is about to execute.
	*	\param The fiber for this task or nullptr if fibers are disabled.
	*/
	FiberData* TaskThreadLocalData::OnTaskExecuteBegin(Task& task) {
		if (_using_fibers) {
			FiberData* fiber = nullptr;
			try {
				// Check if an existing fiber is unused
				for (FiberData* f : _fiber_list) {
					if (f->task == nullptr) {
						fiber = f;
						break;
					}
				}

				if (fiber == nullptr) {
					// Allocate a new fiber
					_fiber_list.push_back(new FiberData());
					fiber = _fiber_list.back();
					fiber->fiber = CreateFiber(0u, (LPFIBER_START_ROUTINE) Task::FiberFunction, fiber);
				}

				fiber->task = &task;
				fiber->yield_condition = nullptr;

			} catch (std::exception&) {
				task.CatchException(std::move(std::current_exception()), false);
			}

			return fiber;

		} else {
			_task_stack.push_back(&task);
			return nullptr;
		}
	}

	/*!
	*	\brief Call Task::FiberFunction() and switch control to another fiber if enabled
	*	\param task The Task to call.
	*	\param fiber The fiber to switch control to, nullptr if fibers are disabled.
	*	\see TaskThreadLocalData::TerminateTaskFiber
	*/
	void TaskThreadLocalData::TaskThreadLocalData::LaunchTaskFiber(Task& task, FiberData* fiber) {
		if (_using_fibers) {
			g_thread_additional_data.SwitchToTask(*fiber);
		} else {
			Task::FiberFunction(task);
		}
	}

	/*!
	*	\brief Called when Task::OnExecute returns. Releases data that was tracked by call to LaunchTaskFiber
	*	\param task The Task that was executed.
	*	\param fiber The fiber of the task or nullptr if fibers are disabled.
	*	\see TaskThreadLocalData::TerminateTaskFiber
	*/
	void TaskThreadLocalData::TerminateTaskFiber(Task& task, FiberData* fiber) {
		if(fiber) {
			fiber->task = nullptr;
			if (task._data->scheduler == nullptr) throw 0; // Main fiber has been switched to before this one somehow

		} else {
			_task_stack.pop_back();
		}
	}

	void TaskThreadLocalData::OnTaskExecuteEnd(Task& task, FiberData* fiber) {
		if (fiber) {
			if (fiber->task != nullptr) throw 0;
			g_thread_additional_data.SwitchToMainFiber2();
		}
	}


	Scheduler& TaskThreadLocalData::GetUnthreadedScheduler() {
		if (!_unthreaded_scheduler) {
			if ANVIL_CONSTEXPR_VAR(Scheduler::DEFAULT_FEATURES & Scheduler::FEATURE_ONLY_EXECUTE_ON_WORKER_THREADS) throw std::runtime_error("anvil::details::TaskThreadLocalData::GetUnthreadedScheduler : Default (unthreaded) scheduler will not work correctly when FEATURE_ONLY_EXECUTE_ON_WORKER_THREADS is enabled");
			_unthreaded_scheduler.reset(new Scheduler(0u, Scheduler::DEFAULT_FEATURES));
		}

		return *_unthreaded_scheduler;
	}
}}