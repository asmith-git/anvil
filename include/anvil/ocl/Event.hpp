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

#ifndef ANVIL_OCL_EVENT_HPP
#define ANVIL_OCL_EVENT_HPP

#include <memory>
#include "anvil/ocl/Context.hpp"

namespace anvil { namespace ocl {

	class Event {
	private:
		cl_event mEvent;

		Event(const Event&) = delete;
		Event& operator=(const Event&) = delete;

		ANVIL_CALL Event(cl_context) throw();
	public:
		friend class Buffer;
		friend class Kernel;
		friend class NativeKernel;

		ANVIL_CALL Event() throw();
		ANVIL_CALL Event(Context&) throw();
		ANVIL_CALL Event(Event&&) throw();
		ANVIL_CALL ~Event() throw();

		Event& ANVIL_CALL operator=(Event&&) throw();
		ANVIL_CALL operator bool() const throw();

		bool ANVIL_CALL wait() throw();

		static bool ANVIL_CALL wait(const std::vector<Event>&) throw();
	};
}}

#endif
