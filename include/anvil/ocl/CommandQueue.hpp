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

#ifndef ANVIL_OCL_COMMAND_QUEUE_HPP
#define ANVIL_OCL_COMMAND_QUEUE_HPP

#include "anvil/ocl/Event.hpp"

namespace anvil { namespace ocl {

	class CommandQueue : public Object {
	private:
		CommandQueue(const CommandQueue&) = delete;
		CommandQueue& operator=(const CommandQueue&) = delete;
	public:
		ANVIL_CALL CommandQueue() throw();
		ANVIL_CALL CommandQueue(CommandQueue&&);
		ANVIL_CALL ~CommandQueue() throw();
		ANVIL_CALL CommandQueue& operator=(CommandQueue&&);

		bool ANVIL_CALL create(Context&, Device&, bool aOutOfOrder = false, bool aProfiling = false) throw();

#ifndef CL_VERSION_1_2
		bool ANVIL_CALL barrier() throw();
		Event ANVIL_CALL pushMarker() throw();
#endif
		bool ANVIL_CALL flush() throw();
		bool ANVIL_CALL finish() throw();
		void ANVIL_CALL swap(CommandQueue&) throw();

		// Inherited from Object

		bool ANVIL_CALL destroy() throw() override;
	};
}}

#endif
