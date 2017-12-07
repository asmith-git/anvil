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

	ANVIL_CALL Context::Context() throw() :
		mContext(NULL)
	{}

	ANVIL_CALL Context::Context(Context&& aOther) throw() :
		mContext(NULL)
	{
		swap(aOther);
	}

	ANVIL_CALL Context::Context(Device aDevice) throw() :
		mContext(NULL)
	{
		cl_int error = CL_SUCCESS;
		const cl_device_id* const devices = reinterpret_cast<const cl_device_id*>(&aDevice);
		mContext = clCreateContext(NULL, 1, devices, Context::errorCallback_, this, &error);
		if (error != CL_SUCCESS) {
			mContext = NULL;
			oclError("clCreateContext", error);
		}
	}

	ANVIL_CALL Context::Context(const std::vector<Device>& aDevices) throw() :
		mContext(NULL)
	{
		const cl_uint s = aDevices.size();
		cl_int error = CL_SUCCESS;
		const cl_device_id* const devices = s == 0 ? NULL : reinterpret_cast<const cl_device_id*>(&aDevices[0]);
		mContext = clCreateContext(NULL, s, devices, Context::errorCallback_, this, &error);
		if (error != CL_SUCCESS) {
			mContext = NULL;
			oclError("clCreateContext", error);
		}
	}

	ANVIL_CALL Context::~Context() throw() {
		if (mContext) {
			cl_int error = clReleaseContext(mContext);
			if (error != CL_SUCCESS) oclError("clReleaseContext", error);
		}
	}

	void ANVIL_CALL Context::swap(Context& aOther) throw() {
		std::swap(mContext, aOther.mContext);
	}

	void ANVIL_CALL Context::errorCallback(const char* aMessage, const void*, size_t) throw() {
		std::cerr << aMessage << std::endl;
	}

	std::vector<Device> ANVIL_CALL Context::devices() const throw() {
		return devices(mContext);
	}

	std::vector<Device> ANVIL_CALL Context::devices(cl_context aContext) throw() {
		cl_uint count;
		clGetContextInfo(aContext, CL_CONTEXT_NUM_DEVICES, sizeof(cl_uint), &count, NULL);
		if (count == 0) return std::vector<Device>(0);
		std::vector<Device> devices(count, NULL);
		clGetContextInfo(aContext, CL_CONTEXT_NUM_DEVICES, sizeof(cl_device_id) * count, &devices[0], NULL);
		return devices;
	}

}}