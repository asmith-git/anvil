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

#include <memory>
#include <string>
#include <stdexcept>
#include <iostream>
#include <cstdint>
#include <CL/CL.h>
#include "anvil/core/Keywords.hpp"
#include "anvil/maths/Type.hpp"

namespace anvil { namespace ocl {

	//! \todo Time of creation

	struct Handle {
		enum Type : uint8_t {
			UNKNOWN,
			CONTEXT,
			PLATFORM,
			DEVICE,
			PROGRAM,
			KERNEL,
			BUFFER,
			COMMAND_QUEUE,
			EVENT
		};

		union {
			cl_context context;
			cl_platform_id platform;
			cl_device_id device;
			cl_program program;
			cl_kernel kernel;
			cl_mem buffer;
			cl_command_queue queue;
			cl_event event;
			void* user;
		};
		Type type;

		ANVIL_CALL Handle();
		ANVIL_CALL Handle(Type);
		ANVIL_CALL Handle(cl_context);
		ANVIL_CALL Handle(cl_platform_id);
		ANVIL_CALL Handle(cl_device_id);
		ANVIL_CALL Handle(cl_program);
		ANVIL_CALL Handle(cl_kernel);
		ANVIL_CALL Handle(cl_mem);
		ANVIL_CALL Handle(cl_command_queue);
		ANVIL_CALL Handle(cl_event);

		ANVIL_CALL operator cl_context() throw();
		ANVIL_CALL operator cl_platform_id() throw();
		ANVIL_CALL operator cl_device_id() throw();
		ANVIL_CALL operator cl_program() throw();
		ANVIL_CALL operator cl_kernel() throw();
		ANVIL_CALL operator cl_mem() throw();
		ANVIL_CALL operator cl_command_queue() throw();
		ANVIL_CALL operator cl_event() throw();
	};

	class Object {
	private:
		std::shared_ptr<void> mExtraData;
	protected:
		Handle mHandle;

		bool ANVIL_CALL setExtraData(std::shared_ptr<void>) throw();
		virtual void ANVIL_CALL onCreate() throw();
		virtual void ANVIL_CALL onDestroy() throw();
		std::shared_ptr<void> ANVIL_CALL getExtraData() throw();

		virtual bool retain() throw() = 0;
	public:
		ANVIL_CALL Object(Handle::Type) throw();
		virtual ANVIL_CALL ~Object() throw();

		Handle ANVIL_CALL handle() const throw();
		ANVIL_CALL operator bool() const throw();

		virtual bool ANVIL_CALL createNoRetain(Handle) throw();
		virtual bool ANVIL_CALL create(Handle) throw();
		virtual bool ANVIL_CALL destroy() throw() = 0;
		virtual cl_uint ANVIL_CALL referenceCount() const throw() = 0;
		virtual Handle::Type ANVIL_CALL type() const throw() = 0;
	};


	const char* ANVIL_CALL typeName(Handle::Type) throw();
	const char* ANVIL_CALL typeName(anvil::Type) throw();
	const char* ANVIL_CALL getOclError() throw();
	bool ANVIL_CALL oclError(const char*, cl_int, const char* aExtraMsg = NULL)  throw();
}}

#endif