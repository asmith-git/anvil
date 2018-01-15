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

	static std::string gErrorMessageA;
	static std::string gErrorMessageB;
	static std::string* gErrorMessage = &gErrorMessageA;


	const char* ANVIL_CALL getOclError() throw() {
		if (gErrorMessage->empty()) return nullptr;
		const char* tmp = gErrorMessage->c_str();
		gErrorMessage = gErrorMessage == &gErrorMessageA ? &gErrorMessageB : &gErrorMessageA;
		gErrorMessage->clear();
		return tmp;
	}

	const char* ANVIL_CALL getErrorName(cl_int aCode) {
#define ANVIL_OCL_CASE(code) case code : return #code;

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
			return nullptr;
		}

#undef ANVIL_OCL_CASE
	}

	bool ANVIL_CALL oclError(const char* aFunction, cl_int aCode, const char* aExtraMsg) {
		std::string msg = aFunction;
		msg += " returned ";
		const char* const name = getErrorName(aCode);
		if (name) {
			msg += name;
		} else {
			msg += std::to_string(aCode);
		}

		if (aExtraMsg) {
			msg += " (";
			msg += aExtraMsg;
			msg += ")";
		}

		if (! gErrorMessage->empty()) {
			*gErrorMessage += '\n';
		}
		*gErrorMessage += msg;
		//std::cerr << msg << std::endl;
		return false;
	}

	const char* ANVIL_CALL typeName(Handle::Type aType) throw() {
		switch (aType) {
			case Handle::CONTEXT:
				return "cl_context";
			case Handle::PLATFORM:
				return "cl_platform_id";
			case Handle::DEVICE:
				return "cl_device";
			case Handle::PROGRAM:
				return "cl_program";
			case Handle::KERNEL:
				return "cl_kernel";
			case Handle::BUFFER:
				return "cl_mem";
			case Handle::COMMAND_QUEUE:
				return "cl_command_queue";
			case Handle::EVENT:
				return "cl_event";
			default:
				return nullptr;
		};
	};

	const char* ANVIL_CALL typeName(Type aType) throw() {
		static ANVIL_CONSTEXPR_VAR const char gNames[28][8] = {
			"uchar",  "uchar2",  "uchar3",  "uchar4",
			"ushort", "ushort2", "ushort3", "ushort4",
			"uint",   "uint2",   "uint3",   "uint4",
			"ulong",  "ulong2",  "ulong3",  "ulong4",
			"float",  "float2",  "float3",  "float4",
			"double", "double2", "double3", "double4",
			"bool",   "bool2",   "bool3",   "bool4"
		};
		
		switch (GetPrimativeType(aType)) {
		case ANVIL_8U:
			return gNames[0 + GetChannels(aType) - 1];
		case ANVIL_8S:
			return gNames[0 + GetChannels(aType) - 1] + 1;
		case ANVIL_16U:
			return gNames[4 + GetChannels(aType) - 1];
		case ANVIL_16S:
			return gNames[4 + GetChannels(aType) - 1] + 1;
#ifndef ANVIL_OCV_COMPATIBILITY
		case ANVIL_32U:
			return gNames[8 + GetChannels(aType) - 1];
#endif
		case ANVIL_32S:
			return gNames[8 + GetChannels(aType) - 1] + 1;
#ifndef ANVIL_OCV_COMPATIBILITY
		case ANVIL_64U:
			return gNames[12 + GetChannels(aType) - 1];
		case ANVIL_64S:
			return gNames[12 + GetChannels(aType) - 1] + 1;
#endif
		case ANVIL_32F:
			return gNames[16 + GetChannels(aType) - 1];
		case ANVIL_64F:
			return gNames[20 + GetChannels(aType) - 1];
#ifndef ANVIL_OCV_COMPATIBILITY
		case ANVIL_8B:
			return gNames[24 + GetChannels(aType) - 1];
#endif
		default:
			return nullptr;
		}
	}

	// Handle

	ANVIL_CALL Handle::Handle() :
		type(UNKNOWN),
		context(NULL)
	{}

	ANVIL_CALL Handle::Handle(Type aType) :
		type(aType),
		context(NULL)
	{}


	ANVIL_CALL Handle::Handle(cl_context aValue) :
		type(CONTEXT),
		context(aValue)
	{}

	ANVIL_CALL Handle::Handle(cl_platform_id aValue) :
		type(PLATFORM),
		platform(aValue)
	{}

	ANVIL_CALL Handle::Handle(cl_device_id aValue) :
		type(DEVICE),
		device(aValue)
	{}

	ANVIL_CALL Handle::Handle(cl_program aValue) :
		type(PROGRAM),
		program(aValue)
	{}

	ANVIL_CALL Handle::Handle(cl_kernel aValue) :
		type(KERNEL),
		kernel(aValue)
	{}

	ANVIL_CALL Handle::Handle(cl_mem aValue) :
		type(BUFFER),
		buffer(aValue)
	{}

	ANVIL_CALL Handle::Handle(cl_command_queue aValue) :
		type(COMMAND_QUEUE),
		queue(aValue)
	{}

	ANVIL_CALL Handle::Handle(cl_event aValue) :
		type(EVENT),
		event(aValue)
	{}

	ANVIL_CALL Handle::operator cl_context() throw() {
		return type == CONTEXT ? context : NULL;
	}

	ANVIL_CALL Handle::operator cl_platform_id() throw() {
		return type == PLATFORM ? platform : NULL;
	}

	ANVIL_CALL Handle::operator cl_device_id() throw() {
		return type == DEVICE ? device : NULL;
	}

	ANVIL_CALL Handle::operator cl_program() throw() {
		return type == PROGRAM ? program : NULL;
	}

	ANVIL_CALL Handle::operator cl_kernel() throw() {
		return type == KERNEL ? kernel : NULL;
	}

	ANVIL_CALL Handle::operator cl_mem() throw() {
		return type == BUFFER ? buffer : NULL;
	}

	ANVIL_CALL Handle::operator cl_command_queue() throw() {
		return type == COMMAND_QUEUE ? queue : NULL;
	}

	ANVIL_CALL Handle::operator cl_event() throw() {
		return type == EVENT ? event : NULL;
	}

	// Object

	ANVIL_CALL Object::Object(Handle::Type aType) throw() {
		mHandle.context = NULL;
		mHandle.type = aType;
	}

	ANVIL_CALL Object::~Object() throw() {

	}

	Handle ANVIL_CALL  Object::handle() const throw() {
		return mHandle;
	}

	ANVIL_CALL Object::operator bool() const throw() {
		return mHandle.context != NULL;
	}

	struct HandleKey {
		Handle handle;

		inline bool ANVIL_CALL operator<(const HandleKey aOther) const throw() {
			return handle.type < aOther.handle.type && handle.context < aOther.handle.context;
		}
	};

	static std::mutex gHandleDataLock;
	static std::map<HandleKey, std::weak_ptr<void>> gHandleData;

	void ANVIL_CALL Object::onCreate() throw() {
		std::lock_guard<std::mutex> lock(gHandleDataLock);
		const auto i = gHandleData.find({ mHandle });
		if (i != gHandleData.end()) {
			std::shared_ptr<void> tmp = i->second.lock();
			if (tmp) {
				mExtraData = tmp;
			} else {
				gHandleData.erase(i);
			}
		}
	}

	void ANVIL_CALL Object::onDestroy() throw() {
		if (!mHandle.context) return;
		if (mExtraData) {
			if (mExtraData.use_count() == 1) {
				std::lock_guard<std::mutex> lock(gHandleDataLock);
				const auto i = gHandleData.find({ mHandle });
				gHandleData.erase(i);
			}
			mExtraData.swap(std::shared_ptr<void>());
		}
	}

	std::shared_ptr<void> ANVIL_CALL Object::getExtraData() throw() {
		return mExtraData;
	}

	bool ANVIL_CALL Object::setExtraData(std::shared_ptr<void> aData) throw() {
		if (mExtraData || ! mHandle.context) return false;
		std::lock_guard<std::mutex> lock(gHandleDataLock);
		HandleKey key = { mHandle };
		gHandleData.emplace(key, aData);
		mExtraData = aData;
		return true;
	}

	bool ANVIL_CALL Object::createNoRetain(Handle aHandle) throw() {
		if (aHandle.type != type()) return false;
		if (mHandle.context != NULL) if (!destroy()) return false;
		if (aHandle.context) {
			mHandle = aHandle;
			onCreate();
		}
		return true;
	}

	bool ANVIL_CALL Object::create(Handle aHandle) throw() {
		if (!createNoRetain(aHandle)) return false;
		return retain();
	}
}}