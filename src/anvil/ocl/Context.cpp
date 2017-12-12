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

	ANVIL_CALL Context::Context() throw() {

	}

	ANVIL_CALL Context::Context(Context&& aOther) throw() {
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
		for (size_t i = 0; i < aCount; ++i) devices[i] = const_cast<Device*>(aDevices)[i].handle().device;

		const cl_context_properties properties[3] = {
			CL_CONTEXT_PLATFORM,
			reinterpret_cast<cl_context_properties>(aCount == 0 ? NULL : aDevices[0].platform()),
			0
		};

		cl_int error = CL_SUCCESS;
		mHandle.context = clCreateContext(aCount == 0 ? NULL : properties, aCount, aCount == 0 ? NULL : devices,
			[](const char* aErrorInfo, const void* aPrivateInfo, size_t aPrivateInfoSize, void* aUserData)->void {
				static_cast<Context*>(aUserData)->onError(aErrorInfo, aPrivateInfo, aPrivateInfoSize);
			}, this, &error);
		if (error != CL_SUCCESS) {
			mHandle.context = NULL;
			return oclError("clCreateContext", error, false);
		}
		return true;
	}

	bool ANVIL_CALL Context::create(const std::vector<Device>& aDevices) throw() {
		const size_t s = aDevices.size();
		return create(s == 0 ? NULL : &aDevices[0], s);
	}

	bool ANVIL_CALL Context::destroy() throw() {
		if (mHandle.context) {
			cl_int error = clReleaseContext(mHandle.context);
			if (error != CL_SUCCESS) return oclError("clReleaseContext", error, false);
			mHandle.context = NULL;
			return true;
		}
		return false;
	}
	
	void ANVIL_CALL Context::swap(Context& aOther) throw() {
		std::swap(mHandle, aOther.mHandle);
	}

	std::vector<Device> ANVIL_CALL Context::devices() const throw() {
		cl_uint count = 0;
		clGetContextInfo(mHandle.context, CL_CONTEXT_NUM_DEVICES, sizeof(cl_uint), &count, NULL);
		if (count == 0) return std::vector<Device>();
		cl_device_id deviceIDs[Platform::MAX_DEVICES];
		clGetContextInfo(mHandle.context, CL_CONTEXT_NUM_DEVICES, sizeof(cl_device_id) * count, deviceIDs, NULL);
		std::vector<Device> devices(count, Device());
		for (cl_uint i = 0; i < count; ++i) devices[i].mHandle.device = deviceIDs[i];
		return devices;
	}

}}