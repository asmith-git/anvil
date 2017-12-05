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

#include "anvil/ocl/Buffer.hpp"

namespace anvil { namespace ocl {

	class CommandQueue {
	private:
		const Context& mContext;
		const Device& mDevice;
		cl_command_queue mQueue;
		bool mOutOfOrder;

		CommandQueue(CommandQueue&&) = delete;
		CommandQueue(const CommandQueue&) = delete;
		CommandQueue& operator=(CommandQueue&&) = delete;
		CommandQueue& operator=(const CommandQueue&) = delete;
	public:
		friend class Buffer;
		friend class Kernel;
		friend class NativeKernel;

		ANVIL_CALL CommandQueue(const Context&, const Device&, bool aOutOfOrder = false);
		ANVIL_CALL ~CommandQueue();

		void ANVIL_CALL flush();
		void ANVIL_CALL finish();

		bool ANVIL_CALL outOfOrder() const throw();
		const Context& ANVIL_CALL context() const throw();
		const Device& ANVIL_CALL device() const throw();
	};
}}

#endif
