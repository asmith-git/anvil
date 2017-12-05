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
#include "anvil/ocl/Kernel.hpp"

namespace anvil { namespace ocl {

	// Kernel

	ANVIL_CALL Kernel::Kernel(const Program& aProgram, const char* aName) :
		mProgram(aProgram),
		mKernel(NULL)
	{
		cl_int error = CL_SUCCESS;
		mKernel = clCreateKernel(aProgram.mProgram, aName, &error);
		if (error != CL_SUCCESS) oclError("clCreateKernel", error);
	}

	ANVIL_CALL Kernel::~Kernel() {
		if (mKernel) {
			clReleaseKernel(mKernel);
		}
	}

	Event ANVIL_CALL Kernel::execute(CommandQueue& aQueue) {
		Event event(mProgram.mContext);

		cl_int error = clEnqueueTask(aQueue.mQueue, mKernel, 0, NULL, &event.mEvent);
		if (error != CL_SUCCESS) oclError("clEnqueueTask", error);

		return event;
	}

	void ANVIL_CALL Kernel::setArg(cl_uint aIndex, const void* aSrc, size_t aBytes) {
		cl_int error = clSetKernelArg(mKernel, aIndex, aBytes, aSrc);
	}

	// NativeKernel

	void __stdcall NativeKernel::execute_(void* aArgs) throw() {
		reinterpret_cast<NativeKernel*>(aArgs)->onExecute();
	}

	ANVIL_CALL NativeKernel::NativeKernel(const Context& aContext) :
		mContext(aContext)
	{}

	ANVIL_CALL NativeKernel::~NativeKernel() {

	}

	Event ANVIL_CALL NativeKernel::execute(CommandQueue& aQueue) {
		Event event(mContext);

		NativeKernel* args = this;
		cl_int error = clEnqueueNativeKernel(aQueue.mQueue, NativeKernel::execute_, &args, sizeof(void*), 0, NULL, NULL, 0, NULL, &event.mEvent);
		if (error != CL_SUCCESS) oclError("clEnqueueTask", error);

		return event;
	}

}}