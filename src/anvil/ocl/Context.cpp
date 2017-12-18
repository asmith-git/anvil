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

#include <iostream>
#include "anvil/ocl/Context.hpp"

namespace anvil { namespace ocl {

	// Context

	ANVIL_CALL Context::Context() throw() :
		Object(Handle::CONTEXT)
	{}

	ANVIL_CALL Context::Context(Context&& aOther) throw() :
		Object(Handle::CONTEXT)
	{
		swap(aOther);
	}

	ANVIL_CALL Context::~Context() throw() {
		destroy();
	}

	Context& ANVIL_CALL Context::operator=(Context&& aOther) throw() {
		swap(aOther);
		return *this;
	}

	void ANVIL_CALL Context::onError(const char* aErrorInfo, const void* aPrivateInfo, size_t aPrivateInfoSize) throw() {

	}

	bool ANVIL_CALL Context::create(Device& aDevice) throw() {
		return create(&aDevice, 1);
	}

	bool ANVIL_CALL Context::create(cl_platform_id aPlatform, cl_device_id* aDevices, size_t aCount) throw() {
		if (mHandle.context) if (!destroy()) return false;

		const cl_context_properties properties[3] = {
			CL_CONTEXT_PLATFORM,
			reinterpret_cast<cl_context_properties>(aPlatform),
			0
		};

		void(__stdcall *function)(const char*, const void*, size_t, void*) = [](const char* aErrorInfo, const void* aPrivateInfo, size_t aPrivateInfoSize, void* aUserData)->void {
			static_cast<Context*>(aUserData)->onError(aErrorInfo, aPrivateInfo, aPrivateInfoSize);
		};

		cl_int error = CL_SUCCESS;
		mHandle.context = clCreateContext(aPlatform == NULL ? NULL : properties, aCount, aCount == 0 ? NULL : aDevices,
			function, this, &error);
#ifdef ANVIL_LOG_OCL
		std::cerr << getErrorName(error) << " <- clCreateContext (" << (aPlatform == NULL ? NULL : properties) << ", " << aCount << ", " << (aCount == 0 ? NULL : aDevices) << ", " <<
			function << ", " << this << ", " << &error << ")" << std::endl;
#endif
		if (error != CL_SUCCESS) {
			mHandle.context = NULL;
			return oclError("clCreateContext", error);
		}
		onCreate();
		return true;
	}

	bool ANVIL_CALL Context::create(Device* aDevices, size_t aCount) throw() {
		if (mHandle.context) if (!destroy()) return false;

		cl_device_id devices[Platform::MAX_DEVICES];
		cl_platform_id platform = aCount == 0 ? NULL : aDevices[0].platform();
		devices[0] = aDevices[0].handle();
		for (size_t i = 1; i < aCount; ++i) {
			devices[i] = aDevices[i].handle();
			if (aDevices[i].platform() != platform) return oclError("anvil::ocl::Context::create", CL_INVALID_PLATFORM, "Devices are not on the same platform");
		}
		return create(platform, devices, aCount);
	}

	bool ANVIL_CALL Context::create(std::vector<std::shared_ptr<Device>>& aDevices) throw() {
		if (mHandle.context) if (!destroy()) return false;

		cl_device_id devices[Platform::MAX_DEVICES];
		const size_t size = aDevices.size();
		cl_platform_id platform = size == 0 ? NULL : aDevices[0]->platform();
		devices[0] = aDevices[0]->handle();
		for (size_t i = 1; i < size; ++i) {
			devices[i] = aDevices[i]->handle();
			if (aDevices[i]->platform() != platform) return oclError("anvil::ocl::Context::create", CL_INVALID_PLATFORM, "Devices are not on the same platform");
		}
		return create(platform, devices, size);
	}

	bool ANVIL_CALL Context::destroy() throw() {
		if (mHandle.context) {
			cl_int error = clReleaseContext(mHandle.context);
#ifdef ANVIL_LOG_OCL
			std::cerr << getErrorName(error) << " <- clReleaseContext (" << mHandle.context << ")" << std::endl;
#endif
			if (error != CL_SUCCESS) return oclError("clReleaseContext", error);
			onDestroy();
			mHandle.context = NULL;
			return true;
		}
		return false;
	}

	bool ANVIL_CALL Context::retain() throw() {
		if (mHandle.context) {
			cl_int error = clRetainContext(mHandle.context);
#ifdef ANVIL_LOG_OCL
			std::cerr << getErrorName(error) << " <- clRetainContext (" << mHandle.context << ")" << std::endl;
#endif
			return error == CL_SUCCESS ? true : oclError("clRetainContext", error);
		}
		return false;
	}
	
	void ANVIL_CALL Context::swap(Context& aOther) throw() {
		std::swap(mHandle, aOther.mHandle);
	}

	std::vector<std::shared_ptr<Device>> ANVIL_CALL Context::devices() const throw() {
		cl_uint count = 0;
		cl_int error = clGetContextInfo(mHandle.context, CL_CONTEXT_NUM_DEVICES, sizeof(cl_uint), &count, NULL);
#ifdef ANVIL_LOG_OCL
		std::cerr << getErrorName(error) << " <- clGetContextInfo (" << mHandle.context << ", " << "CL_CONTEXT_NUM_DEVICES" << ", " << sizeof(cl_uint) <<
			", " << &count << ", " << "NULL" << ")" << std::endl;
#endif
		if (count == 0) return std::vector<std::shared_ptr<Device>>();
		cl_device_id deviceIDs[Platform::MAX_DEVICES];
		error = clGetContextInfo(mHandle.context, CL_CONTEXT_DEVICES, sizeof(cl_device_id) * count, deviceIDs, NULL);
#ifdef ANVIL_LOG_OCL
		std::cerr << getErrorName(error) << " <- clGetContextInfo (" << mHandle.context << ", " << "CL_CONTEXT_DEVICES" << ", " << sizeof(cl_device_id) * count <<
			", " << deviceIDs << ", " << "NULL" << ")" << std::endl;
#endif
		std::vector<std::shared_ptr<Device>> devices(count, std::shared_ptr<Device>());
		for (cl_uint i = 0; i < count; ++i) {
			devices[i].swap(std::shared_ptr<Device>(new Device()));
			devices[i]->create(deviceIDs[i]);
		}
		return devices;
	}

	cl_uint ANVIL_CALL Context::referenceCount() const throw() {
		cl_uint count;
		cl_uint error = clGetContextInfo(mHandle.context, CL_CONTEXT_REFERENCE_COUNT, sizeof(count), &count, NULL);
#ifdef ANVIL_LOG_OCL
		std::cerr << getErrorName(error) << " <- clGetContextInfo (" << mHandle.context << ", " << "CL_CONTEXT_REFERENCE_COUNT" << ", " << sizeof(count) <<
			", " << &count << ", " << "NULL" << ")" << std::endl;
#endif
		if (error == CL_SUCCESS) return count;
		oclError("clGetContextInfo", error, "CL_CONTEXT_REFERENCE_COUNT");
		return 0;
	}

	Handle::Type ANVIL_CALL Context::type() const throw() {
		return Handle::CONTEXT;
	}

}}