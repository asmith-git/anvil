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

#ifndef ANVIL_OCL_CORE_HPP
#define ANVIL_OCL_CORE_HPP

#include <CL/CL.h>
#include "anvil/core/Keywords.hpp"

namespace anvil { namespace ocl {
	static void ANVIL_CALL throwException(const char* aFunction, cl_int aCode) {
		std::string msg = "OpenCL reports error in call ";
		msg	+= aFunction;
		msg	+= " with code ";
		
		switch(aCode) {
		case CL_INVALID_VALUE   :
			msg += "CL_INVALID_VALUE";
			break;
		case CL_INVALID_MEM_OBJECT  :
			msg += "CL_INVALID_MEM_OBJECT";
			break;
		case CL_INVALID_CONTEXT :
			msg += "CL_INVALID_CONTEXT";
			break;
		case CL_INVALID_VALUE  :
			msg += "CL_INVALID_VALUE";
			break;
		case CL_INVALID_BUFFER_SIZE  :
			msg += "CL_INVALID_BUFFER_SIZE";
			break;
		case CL_DEVICE_MAX_MEM_ALLOC_SIZE  :
			msg += "CL_DEVICE_MAX_MEM_ALLOC_SIZE";
			break;
		case CL_INVALID_HOST_PTR  :
			msg += "CL_INVALID_HOST_PTR";
			break;
		case CL_MEM_OBJECT_ALLOCATION_FAILURE   :
			msg += "CL_MEM_OBJECT_ALLOCATION_FAILURE";
			break;
		case CL_OUT_OF_RESOURCES  :
			msg += "CL_OUT_OF_RESOURCES";
			break;
		case CL_OUT_OF_HOST_MEMORY   :
			msg += "CL_OUT_OF_HOST_MEMORY";
			break;
		default:
			msg += std::to_string(aCode);
			break;
		}
		
		ANVIL_RUNTIME_ASSERT(false, msg);
	}
	
	struct StringCast {
		inline operator const char*() const throw() {
			return reinterpret_cast<const char*>(this);
		}
	};
}}
