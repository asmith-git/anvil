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

	void ANVIL_CALL Context::onError(const char* aErrorInfo, const void* aPrivateInfo, size_t aPrivateInfoSize) throw() {

	}

	bool ANVIL_CALL Context::create(Device aDevice) throw() {
		return create(&aDevice, 1);
	}

	bool ANVIL_CALL Context::create(const Device* aDevices, size_t aCount) throw() {
		if (mHandle.context) if (!destroy()) return false;

		cl_device_id devices[Platform::MAX_DEVICES];
		cl_platform_id platform = aCount == 0 ? NULL : aDevices[0].platform();
		devices[0] = aDevices[0].handle();
		for (size_t i = 1; i < aCount; ++i) {
			devices[i] = aDevices[i].handle();
			if (aDevices[i].platform() != platform) return oclError("anvil::ocl::Context::create", CL_INVALID_PLATFORM, "Devices are not on the same platform");
		}

		const cl_context_properties properties[3] = {
			CL_CONTEXT_PLATFORM,
			reinterpret_cast<cl_context_properties>(platform),
			0
		};

		cl_int error = CL_SUCCESS;
		mHandle.context = clCreateContext(platform == NULL ? NULL : properties, aCount, aCount == 0 ? NULL : devices,
			[](const char* aErrorInfo, const void* aPrivateInfo, size_t aPrivateInfoSize, void* aUserData)->void {
				static_cast<Context*>(aUserData)->onError(aErrorInfo, aPrivateInfo, aPrivateInfoSize);
			}, this, &error);
		if (error != CL_SUCCESS) {
			mHandle.context = NULL;
			return oclError("clCreateContext", error);
		}
		onCreate();
		return true;
	}

	bool ANVIL_CALL Context::create(const std::vector<Device>& aDevices) throw() {
		const size_t s = aDevices.size();
		return create(s == 0 ? NULL : &aDevices[0], s);
	}

	bool ANVIL_CALL Context::destroy() throw() {
		if (mHandle.context) {
			cl_int error = clReleaseContext(mHandle.context);
			if (error != CL_SUCCESS) return oclError("clReleaseContext", error);
			onDestroy();
			mHandle.context = NULL;
			return true;
		}
		return false;
	}

	bool ANVIL_CALL Context::create(Handle aHandle) throw() {
		if (aHandle.type != Handle::CONTEXT) return false;
		if (mHandle.context != NULL) if (!destroy()) return false;
		if (aHandle.context) {
			mHandle = aHandle;
			cl_int error = clRetainContext(mHandle.context);
			if (error != CL_SUCCESS) return oclError("clRetainContext", error);
			onCreate();
		}
		return true;
	}
	
	void ANVIL_CALL Context::swap(Context& aOther) throw() {
		std::swap(mHandle, aOther.mHandle);
	}

	std::vector<Device> ANVIL_CALL Context::devices() const throw() {
		cl_uint count = 0;
		clGetContextInfo(mHandle.context, CL_CONTEXT_NUM_DEVICES, sizeof(cl_uint), &count, NULL);
		if (count == 0) return std::vector<Device>();
		cl_device_id deviceIDs[Platform::MAX_DEVICES];
		clGetContextInfo(mHandle.context, CL_CONTEXT_DEVICES, sizeof(cl_device_id) * count, deviceIDs, NULL);
		std::vector<Device> devices(count, Device());
		for (cl_uint i = 0; i < count; ++i) devices[i].create(deviceIDs[i]);
		return devices;
	}

	cl_uint ANVIL_CALL Context::referenceCount() const throw() {
		cl_uint count;
		cl_uint error = clGetContextInfo(mHandle.context, CL_CONTEXT_REFERENCE_COUNT, sizeof(count), &count, NULL);
		if (error == CL_SUCCESS) return count;
		oclError("clGetContextInfo", error, "CL_CONTEXT_REFERENCE_COUNT");
		return 0;
	}

	Handle::Type ANVIL_CALL Context::type() const throw() {
		return Handle::CONTEXT;
	}

}}