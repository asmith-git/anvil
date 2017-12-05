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

#include "anvil/ocl/Core.hpp"

namespace anvil { namespace ocl {
	class Context {
	private:
		cl_context mContext;
	public:
		friend class Buffer;
		
		Context() {
			cl_int error = CL_SUCCESS;
			mContext = clCreateContext(nullptr, 0, nullptr, nullptr, nullptr, nullptr, &error); //! \todo Devices
			if(error != CL_SUCCESS) {
				mContext = 0;
				throwException("clCreateContext", error);
			}
		}
		
		~Context() {
			if(mContext != 0) {
				cl_int error = clReleaseContext(mContext);
				if(error != CL_SUCCESS) throwException("clReleaseContext", error);
			}
		}
	};
}}
