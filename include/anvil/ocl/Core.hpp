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

#include <string>
#include <stdexcept>
#include <iostream>
#include <cstdint>
#include <CL/CL.h>
#include "anvil/core/Keywords.hpp"

namespace anvil { namespace ocl {

	class NativeKernel;

	class Object {
	public:
		enum Type : uint8_t {
			UNKNOWN,
			CONTEXT,
			PLATFORM,
			DEVICE,
			PROGRAM,
			KERNEL,
			NATIVE_KERNEL,
			BUFFER,
			COMMAND_QUEUE,
			EVENT
		};
		struct Handle {
			union {
				cl_context context;
				cl_platform_id platform;
				cl_device_id device;
				cl_program program;
				cl_kernel kernel;
				cl_mem buffer;
				cl_command_queue queue;
				cl_event event;
				NativeKernel* native;
			};
			Type type;
		};
	protected:
		Handle mHandle;
	public:
		friend class Context;
		friend class Platform;
		friend class Device;
		friend class Program;
		friend class Kernel;
		friend class Buffer;
		friend class CommandQueue;
		friend class Event;

		ANVIL_CALL Object(Type) throw();
		virtual ANVIL_CALL ~Object() throw();

		Handle ANVIL_CALL handle() const throw();
		ANVIL_CALL operator bool() const throw();
		virtual bool ANVIL_CALL create(Handle) throw() = 0;
		virtual bool ANVIL_CALL destroy() throw() = 0;
	};

	static bool ANVIL_CALL oclError(const char* aFunction, cl_int aCode, bool aReturnValue = false) {
		std::string msg = "OpenCL reports error in call ";
		msg	+= aFunction;
		msg	+= " with code ";

#define ANVIL_OCL_CASE(code) case code : msg += #code; break;
		
		switch (aCode) {
		ANVIL_OCL_CASE(CL_SUCCESS)
		ANVIL_OCL_CASE(CL_DEVICE_NOT_FOUND)
		ANVIL_OCL_CASE(CL_DEVICE_NOT_AVAILABLE)
		ANVIL_OCL_CASE(CL_COMPILER_NOT_AVAILABLE)
		ANVIL_OCL_CASE(CL_MEM_OBJECT_ALLOCATION_FAILURE)
		ANVIL_OCL_CASE(CL_OUT_OF_RESOURCES)
		ANVIL_OCL_CASE(CL_OUT_OF_HOST_MEMORY)
		ANVIL_OCL_CASE(CL_PROFILING_INFO_NOT_AVAILABLE)
		ANVIL_OCL_CASE(CL_MEM_COPY_OVERLAP)
		ANVIL_OCL_CASE(CL_IMAGE_FORMAT_MISMATCH)
		ANVIL_OCL_CASE(CL_IMAGE_FORMAT_NOT_SUPPORTED)
		ANVIL_OCL_CASE(CL_BUILD_PROGRAM_FAILURE)
		ANVIL_OCL_CASE(CL_MAP_FAILURE)
		ANVIL_OCL_CASE(CL_MISALIGNED_SUB_BUFFER_OFFSET)
		ANVIL_OCL_CASE(CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST)
		ANVIL_OCL_CASE(CL_COMPILE_PROGRAM_FAILURE)
		ANVIL_OCL_CASE(CL_LINKER_NOT_AVAILABLE)
		ANVIL_OCL_CASE(CL_LINK_PROGRAM_FAILURE)
		ANVIL_OCL_CASE(CL_DEVICE_PARTITION_FAILED)
		ANVIL_OCL_CASE(CL_KERNEL_ARG_INFO_NOT_AVAILABLE)
		ANVIL_OCL_CASE(CL_INVALID_VALUE)
		ANVIL_OCL_CASE(CL_INVALID_DEVICE_TYPE)
		ANVIL_OCL_CASE(CL_INVALID_PLATFORM)
		ANVIL_OCL_CASE(CL_INVALID_DEVICE)
		ANVIL_OCL_CASE(CL_INVALID_CONTEXT)
		ANVIL_OCL_CASE(CL_INVALID_QUEUE_PROPERTIES)
		ANVIL_OCL_CASE(CL_INVALID_COMMAND_QUEUE)
		ANVIL_OCL_CASE(CL_INVALID_HOST_PTR)
		ANVIL_OCL_CASE(CL_INVALID_MEM_OBJECT)
		ANVIL_OCL_CASE(CL_INVALID_IMAGE_FORMAT_DESCRIPTOR)
		ANVIL_OCL_CASE(CL_INVALID_IMAGE_SIZE)
		ANVIL_OCL_CASE(CL_INVALID_SAMPLER)
		ANVIL_OCL_CASE(CL_INVALID_BINARY)
		ANVIL_OCL_CASE(CL_INVALID_BUILD_OPTIONS)
		ANVIL_OCL_CASE(CL_INVALID_PROGRAM)
		ANVIL_OCL_CASE(CL_INVALID_PROGRAM_EXECUTABLE)
		ANVIL_OCL_CASE(CL_INVALID_KERNEL_NAME)
		ANVIL_OCL_CASE(CL_INVALID_KERNEL_DEFINITION)
		ANVIL_OCL_CASE(CL_INVALID_KERNEL)
		ANVIL_OCL_CASE(CL_INVALID_ARG_INDEX)
		ANVIL_OCL_CASE(CL_INVALID_ARG_VALUE)
		ANVIL_OCL_CASE(CL_INVALID_ARG_SIZE)
		ANVIL_OCL_CASE(CL_INVALID_KERNEL_ARGS)
		ANVIL_OCL_CASE(CL_INVALID_WORK_DIMENSION)
		ANVIL_OCL_CASE(CL_INVALID_WORK_GROUP_SIZE)
		ANVIL_OCL_CASE(CL_INVALID_WORK_ITEM_SIZE)
		ANVIL_OCL_CASE(CL_INVALID_GLOBAL_OFFSET)
		ANVIL_OCL_CASE(CL_INVALID_EVENT_WAIT_LIST)
		ANVIL_OCL_CASE(CL_INVALID_EVENT)
		ANVIL_OCL_CASE(CL_INVALID_OPERATION)
		ANVIL_OCL_CASE(CL_INVALID_GL_OBJECT)
		ANVIL_OCL_CASE(CL_INVALID_BUFFER_SIZE)
		ANVIL_OCL_CASE(CL_INVALID_MIP_LEVEL)
		ANVIL_OCL_CASE(CL_INVALID_GLOBAL_WORK_SIZE)
		ANVIL_OCL_CASE(CL_INVALID_PROPERTY)
		ANVIL_OCL_CASE(CL_INVALID_IMAGE_DESCRIPTOR)
		ANVIL_OCL_CASE(CL_INVALID_COMPILER_OPTIONS)
		ANVIL_OCL_CASE(CL_INVALID_LINKER_OPTIONS)
		ANVIL_OCL_CASE(CL_INVALID_DEVICE_PARTITION_COUNT)
		default:
			msg += std::to_string(aCode);
			break;
		}

#undef ANVIL_OCL_CASE
		
		std::cerr << msg << std::endl;
		return aReturnValue;
	}
}}

#endif