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

#include <cstdint>
#include "anvil/ocl/Buffer.hpp"
#include "anvil/ocl/CommandQueue.hpp"

namespace anvil { namespace ocl {

	// CommandQueue

	ANVIL_CALL CommandQueue::CommandQueue(const Context& aContext, const Device& aDevice, bool aOutOfOrder) :
		mContext(aContext),
		mDevice(aDevice),
		mOutOfOrder(aOutOfOrder)
	{
		cl_int error = CL_SUCCESS;
		mQueue = clCreateCommandQueue(aContext.mContext, aDevice.mDevice, aOutOfOrder ? 1 : 0, &error);
		if (error != CL_SUCCESS) oclError("clFlush", error);
	}

	ANVIL_CALL CommandQueue::~CommandQueue() {
		cl_int error = clReleaseCommandQueue(mQueue);
		if (error != CL_SUCCESS) oclError("clReleaseCommandQueue", error);
	}

	void ANVIL_CALL CommandQueue::flush() {
		cl_int error = clFlush(mQueue);
		if (error != CL_SUCCESS) oclError("clFlush", error);
	}

	void ANVIL_CALL CommandQueue::flush() {
		cl_int error = clFinish(mQueue);
		if (error != CL_SUCCESS) oclError("clFinish", error);
	}

	bool ANVIL_CALL CommandQueue::outOfOrder() const throw() {
		return mOutOfOrder;
	}

	const Context& ANVIL_CALL CommandQueue::context() const throw() {
		return mContext;
	}

	const Device& ANVIL_CALL CommandQueue::device() const throw() {
		return mDevice;
	}

}}