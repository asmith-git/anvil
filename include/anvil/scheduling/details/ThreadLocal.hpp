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

#ifndef ANVIL_SCHEDULER_THREAD_LOCAL_HPP
#define ANVIL_SCHEDULER_THREAD_LOCAL_HPP

#include "anvil/scheduling/details/Fibers.hpp"
#include <vector>
#include <deque>

namespace anvil { namespace details {

	class ANVIL_DLL_EXPORT TaskThreadLocalData {
	private:
		std::deque<FiberData*> _fiber_list;
		FiberData* _current_fiber;
		LPVOID _main_fiber;

		std::vector<Task*> _task_stack;

		Scheduler* _scheduler;
		uint32_t _scheduler_index;
		bool _is_worker_thread;

		bool _using_fibers;

	public:
		friend Scheduler;
		friend Task;

		static TaskThreadLocalData& Get();

		TaskThreadLocalData();
		~TaskThreadLocalData();

		FiberData* OnTaskExecuteBegin(Task& task);
		void LaunchTaskFiber(Task& task, FiberData* fiber);
		void OnTaskExecuteReturn(Task& task, FiberData* fiber);
		void OnTaskExecuteEnd(Task& task, FiberData* fiber);

		// Fiber controls
		bool AreAnyFibersReady() const;
		bool SwitchToTask(FiberData& fiber);
		bool SwitchToAnyTask();
		void SwitchToMainFiber2();
		void SwitchToMainFiber();

		// Functions moved from Task
		Task* GetCurrentlyExecutingTask() const;
		Task* GetCurrentlyExecutingTask(size_t index) const;
		size_t GetNumberOfTasksExecutingOnThisThread() const;


		// Functions moved from Scheduler
		void RegisterAsWorkerThread(Scheduler& scheduler);

	};

}}

#endif