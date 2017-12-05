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

#ifndef ANVIL_OCL_CONTEXT_HPP
#define ANVIL_OCL_CONTEXT_HPP

#include <vector>
#include "anvil/ocl/Platform.hpp"

namespace anvil { namespace ocl {
	class Context {
	private:
		const std::vector<Device> mDevices;
		cl_context mContext;

		Context(Context&&) = delete;
		Context(const Context&) = delete;
		Context& operator=(Context&&) = delete;
		Context& operator=(const Context&) = delete;

		static void __stdcall errorCallback_(const char *, const void *, size_t, void*);
	protected:
		virtual void ANVIL_CALL errorCallback(const char*, const void*, size_t) throw();
	public:
		friend class Buffer;
		
		ANVIL_CALL Context(const std::vector<Device>&);
		virtual ANVIL_CALL ~Context();

		std::vector<Device> ANVIL_CALL devices() const throw();
	};
}}

#endif
