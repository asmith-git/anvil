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
		mContext(NULL)
	{}

	ANVIL_CALL Context::Context(Context&& aOther) throw() :
		mContext(NULL)
	{
		swap(aOther);
	}

	ANVIL_CALL Context::~Context() throw() {
		destroy();
	}

	ANVIL_CALL Context::operator bool() const throw() {
		return mContext != NULL;
	}

	bool Context::create(Device aDevice, ErrorCallback aCallback) throw() {
		return create(&aDevice, 1, aCallback);
	}

	bool Context::create(const Device* aDevices, size_t aCount, ErrorCallback aCallback) throw() {
		if (mContext) if (!destroy()) return false;

		cl_int error = CL_SUCCESS;
		mContext = clCreateContext(NULL, aCount, reinterpret_cast<const cl_device_id*>(aDevices), aCallback, this, &error);
		if (error != CL_SUCCESS) {
			mContext = NULL;
			return oclError("clCreateContext", error, false);
		}
		return true;
	}

	bool Context::create(const std::vector<Device>& aDevices, ErrorCallback aCallback) throw() {
		const size_t s = aDevices.size();
		return create(s == 0 ? NULL : &aDevices[0], s, aCallback);
	}

	bool Context::destroy() throw() {
		if (mContext) {
			cl_int error = clReleaseContext(mContext);
			if (error != CL_SUCCESS) return oclError("clReleaseContext", error, false);
			mContext = NULL;
			return true;
		}
		return false;
	}

	void ANVIL_CALL Context::swap(Context& aOther) throw() {
		std::swap(mContext, aOther.mContext);
	}

	std::vector<Device> ANVIL_CALL Context::devices() const throw() {
		return devices(mContext);
	}

	std::vector<Device> ANVIL_CALL Context::devices(cl_context aContext) throw() {
		cl_uint count;
		clGetContextInfo(aContext, CL_CONTEXT_NUM_DEVICES, sizeof(cl_uint), &count, NULL);
		if (count == 0) return std::vector<Device>(0);
		std::vector<Device> devices(count, Device());
		clGetContextInfo(aContext, CL_CONTEXT_NUM_DEVICES, sizeof(cl_device_id) * count, &devices[0], NULL);
		return devices;
	}

}}