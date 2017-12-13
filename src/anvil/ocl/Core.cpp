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

#include "anvil/ocl/Core.hpp"
#include <mutex>
#include <map>

namespace anvil { namespace ocl {

	static std::string gErrorMessage;


	std::string ANVIL_CALL getOclError() throw() {
		std::string tmp = gErrorMessage;
		gErrorMessage.clear();
		return tmp;
	}

	bool ANVIL_CALL oclError(const char* aFunction, cl_int aCode, const char* aExtraMsg) {
		std::string msg = aFunction;
		msg += " returned ";

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

		if (aExtraMsg) {
			msg += " (";
			msg += aExtraMsg;
			msg += ")";
		}

		if (! gErrorMessage.empty()) {
			gErrorMessage += '\n';
		}
		gErrorMessage += msg;
		std::cerr << msg << std::endl;
		return false;
	}

	// Object

	ANVIL_CALL Object::Object(Type aType) throw() {
		mHandle.context = NULL;
		mHandle.type = aType;
	}

	ANVIL_CALL Object::~Object() throw() {

	}

	Object::Handle ANVIL_CALL  Object::handle() const throw() {
		return mHandle;
	}

	ANVIL_CALL Object::operator bool() const throw() {
		return mHandle.context != NULL;
	}

	struct HandleKey {
		Object::Handle handle;

		inline bool ANVIL_CALL operator<(const HandleKey aOther) const throw() {
			return handle.type < aOther.handle.type && handle.context < aOther.handle.context;
		}
	};

	static std::mutex gHandleDataLock;
	static std::map<HandleKey, void*> gHandleData;

	void* ANVIL_CALL Object::getAssociatedData(Handle aHandle) throw() {
		const HandleKey h = { aHandle };
		if (h.handle.context == NULL) return nullptr;
		std::lock_guard<std::mutex> lock(gHandleDataLock);
		const auto i = gHandleData.find(h);
		if (i != gHandleData.end()) return nullptr;
		return i->second;
	}

	bool ANVIL_CALL Object::associateData(Handle aHandle, void* aData) throw() {
		const HandleKey h = { aHandle };
		if (h.handle.context == NULL) return false;
		std::lock_guard<std::mutex> lock(gHandleDataLock);
		const auto i = gHandleData.find(h);
		if (i != gHandleData.end()) return false;
		gHandleData.emplace(h, aData);
		return true;
	}

	void* ANVIL_CALL Object::disassociateData(Handle aHandle) throw() {
		const HandleKey h = { aHandle };
		if (h.handle.context == NULL) return nullptr;
		std::lock_guard<std::mutex> lock(gHandleDataLock);
		const auto i = gHandleData.find(h);
		if (i != gHandleData.end()) {
			void* const tmp = i->second;
			gHandleData.erase(i);
			return tmp;
		}
		return nullptr;
	}
}}