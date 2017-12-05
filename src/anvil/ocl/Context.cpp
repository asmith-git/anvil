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

	void __stdcall Context::errorCallback_(const char *errinfo, const void *private_info, size_t cb, void *user_data) {
		static_cast<Context*>(user_data)->errorCallback(errinfo, private_info, cb);
	}

	ANVIL_CALL Context::Context(const std::vector<Device>& aDevices) :
		mDevices(aDevices)
	{
		enum { MAX_DEVICES = 128 };
		const cl_uint s = aDevices.size();

		ANVIL_RUNTIME_ASSERT(s <= MAX_DEVICES, "Too many devices in context constructor");
		cl_device_id devices[MAX_DEVICES];
		for (size_t i = 0; i < s; ++i) devices[i] = aDevices[i].mDevice;

		cl_int error = CL_SUCCESS;
		mContext = clCreateContext(NULL, s, devices, Context::errorCallback_, this, &error);
		if (error != CL_SUCCESS) {
			mContext = 0;
			throwException("clCreateContext", error);
		}
	}

	ANVIL_CALL Context::~Context() {
		if (mContext != 0) {
			cl_int error = clReleaseContext(mContext);
			if (error != CL_SUCCESS) throwException("clReleaseContext", error);
		}
	}

	void ANVIL_CALL Context::errorCallback(const char* aMessage, const void*, size_t) throw() {
		std::cerr << aMessage << std::endl;
	}

	std::vector<Device> ANVIL_CALL Context::devices() const throw() {
		return mDevices;
	}

}}