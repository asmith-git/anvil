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
#include "anvil/core/Keywords.hpp"

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
		virtual ANVIL_CALL ~TaskDispatcher() throw() {}

		virtual size_t ANVIL_CALL threadCount() const throw() = 0;
		virtual size_t ANVIL_CALL activeThreads() const throw() = 0;
		virtual size_t ANVIL_CALL queuedTasks() const throw() = 0;

		virtual TaskHandle ANVIL_CALL enqueue(uint8_t, Task, void*) throw() = 0;
		virtual bool ANVIL_CALL wait(TaskHandle, std::exception_ptr*) const throw() = 0;
		virtual bool ANVIL_CALL cancel(TaskHandle) throw() = 0;
		virtual uint8_t ANVIL_CALL getPriority(TaskHandle) const throw() = 0;
		virtual bool ANVIL_CALL setPriority(TaskHandle, uint8_t) throw() = 0;
		virtual bool ANVIL_CALL waitAll() const throw() = 0;
		virtual bool ANVIL_CALL cancelAll() throw() = 0;
	};
}

#endif