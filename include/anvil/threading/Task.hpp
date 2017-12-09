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

#ifndef ANVIL_THREADING_TASK_HPP
#define ANVIL_THREADING_TASK_HPP

#include <cstdint>
#include <exception>

namespace anvil {

	typedef void(*Task)(void*);

	struct TaskHandle_;

	typedef TaskHandle_* TaskHandle;

	class TaskDispatcher {
	public:
		enum {
			HIGHEST_PRIORITY = UINT8_MAX,
			DEFAULT_PRIORITY = HIGHEST_PRIORITY / 2,
			LOWEST_PRIORITY = 0
		};
		virtual ~TaskDispatcher() throw() {}

		virtual size_t threadCount() const throw() = 0;
		virtual size_t activeThreads() const throw() = 0;
		virtual size_t queuedTasks() const throw() = 0;

		virtual TaskHandle enqueue(uint8_t, Task, void*) throw() = 0;
		virtual bool wait(TaskHandle, std::exception_ptr*) const throw() = 0;
		virtual bool cancel(TaskHandle) throw() = 0;
		virtual uint8_t getPriority(TaskHandle) const throw() = 0;
		virtual bool setPriority(TaskHandle, uint8_t) throw() = 0;
		virtual bool waitAll() const throw() = 0;
		virtual bool cancelAll() throw() = 0;
	};
}

#endif