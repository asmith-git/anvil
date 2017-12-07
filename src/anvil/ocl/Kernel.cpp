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

	ANVIL_CALL Kernel::Kernel() throw() :
		mKernel(NULL)
	{}

	ANVIL_CALL Kernel::Kernel(Kernel&& aOther) throw() :
		mKernel(NULL)
	{
		swap(aOther);
	}

	ANVIL_CALL Kernel::Kernel(const Program& aProgram, const char* aName) :
		mKernel(NULL)
	{
		cl_int error = CL_SUCCESS;
		mKernel = clCreateKernel(aProgram.mProgram, aName, &error);
		if (error != CL_SUCCESS) {
			mKernel = NULL;
			oclError("clCreateKernel", error);
		}
	}

	ANVIL_CALL Kernel::~Kernel() {
		if (mKernel) {
			cl_int error = clReleaseKernel(mKernel);
			if (error != CL_SUCCESS) oclError("clReleaseKernel", error);
		}
	}

	Kernel& ANVIL_CALL Kernel::operator=(Kernel&& aOther) throw() {
		swap(aOther);
		return *this;
	}

	ANVIL_CALL Kernel::operator bool() const throw() {
		return mKernel != NULL;
	}

	void ANVIL_CALL Kernel::swap(Kernel& aOther) throw() {
		std::swap(mKernel, aOther.mKernel);
	}

	Event ANVIL_CALL Kernel::execute(CommandQueue& aQueue) {
		Event event;
		cl_int error = clEnqueueTask(aQueue.mQueue, mKernel, 0, NULL, &event.mEvent);
		if (error != CL_SUCCESS) {
			oclError("clEnqueueTask", error);
			return Event();
		}
		return event;
	}

	bool ANVIL_CALL Kernel::setArgument(cl_uint aIndex, const void* aSrc, size_t aBytes) {
		cl_int error = clSetKernelArg(mKernel, aIndex, aBytes, aSrc);
		if (error != CL_SUCCESS) return oclError("clSetKernelArg", error, false);
		return true;
	}

	cl_context Kernel::context() const throw() {
		return mKernel ? getInfo<cl_context>(CL_KERNEL_CONTEXT) : NULL;
	}

	cl_program Kernel::program() const throw() {
		return mKernel ? getInfo<cl_program>(CL_KERNEL_PROGRAM) : NULL;
	}

	cl_uint Kernel::arguments() const throw() {
		return mKernel ? getInfo<cl_uint>(CL_KERNEL_NUM_ARGS) : 0;
	}

	const char* Kernel::name() const throw() {
		enum { MAX_KERNEL_NAME = 1024 };
		static char gNameBuffer[MAX_KERNEL_NAME];
		cl_int error = clGetKernelInfo(mKernel, CL_KERNEL_FUNCTION_NAME, MAX_KERNEL_NAME, gNameBuffer, NULL);
		if (error != CL_SUCCESS) oclError("clGetKernelInfo ", error);
		return gNameBuffer;
	}

	// NativeKernel

	void __stdcall NativeKernel::execute_(void* aArgs) throw() {
		reinterpret_cast<NativeKernel*>(aArgs)->onExecute();
	}

	ANVIL_CALL NativeKernel::NativeKernel(Context& aContext) :
		mContext(aContext.mContext)
	{}

	ANVIL_CALL NativeKernel::~NativeKernel() {

	}

	Event ANVIL_CALL NativeKernel::execute(CommandQueue& aQueue) {
		Event event;

		NativeKernel* args = this;
		cl_int error = clEnqueueNativeKernel(aQueue.mQueue, NativeKernel::execute_, &args, sizeof(void*), 0, NULL, NULL, 0, NULL, &event.mEvent);
		if (error != CL_SUCCESS) {
			oclError("clEnqueueNativeKernel", error);
			return Event();
		}

		return event;
	}

}}