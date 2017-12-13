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
		Object(KERNEL) 
	{}

	ANVIL_CALL Kernel::Kernel(Kernel&& aOther) throw():
		Object(KERNEL) 
	{
		swap(aOther);
	}

	ANVIL_CALL Kernel::~Kernel() throw()  {
		destroy();
	}

	Kernel& ANVIL_CALL Kernel::operator=(Kernel&& aOther) throw() {
		swap(aOther);
		return *this;
	}

	void ANVIL_CALL Kernel::swap(Kernel& aOther) throw() {
		std::swap(mHandle, aOther.mHandle);
	}

	bool ANVIL_CALL Kernel::create(const Program& aProgram, const char* aName) throw() {
		cl_int error = CL_SUCCESS;
		mHandle.kernel = clCreateKernel(const_cast<Program&>(aProgram).handle().program, aName, &error);
		if (error != CL_SUCCESS) {
			mHandle.kernel = NULL;
			return oclError("clCreateKernel", error, aName);
		}
		return true;
	}

	bool ANVIL_CALL Kernel::destroy() throw() {
		if (mHandle.kernel) {
			cl_int error = clReleaseKernel(mHandle.kernel);
			if (error != CL_SUCCESS) return oclError("clReleaseKernel", error);
			mHandle.kernel = NULL;
			return true;
		}
		return false;
	}

	bool ANVIL_CALL Kernel::create(Handle aHandle) throw() {
		if (aHandle.type != KERNEL) return false;
		if (mHandle.kernel != NULL) if (!destroy()) return false;
		if (aHandle.kernel) {
			mHandle = aHandle;
			cl_int error = clRetainKernel(mHandle.kernel);
			if (error != CL_SUCCESS) {
				mHandle.kernel = NULL;
				return oclError("clRetainKernel", error);
			}
		}
		return true;
	}

	Event ANVIL_CALL Kernel::execute(CommandQueue& aQueue, cl_uint aDimensions, const size_t *aGlobalOffset, const size_t *aGlobalWorkSize, const size_t *aLocalWorkSize) {
		Event event;
		cl_int error = clEnqueueNDRangeKernel(aQueue.handle().queue, mHandle.kernel, aDimensions, aGlobalOffset, aGlobalWorkSize, aLocalWorkSize, 0, NULL, &event.mHandle.event);
		if (error != CL_SUCCESS) {
			oclError("clEnqueueNDRangeKernel", error, name());
			return Event();
		}
		return event;
	}

	bool ANVIL_CALL Kernel::setArgument(cl_uint aIndex, const void* aSrc, size_t aBytes) {
		cl_int error = clSetKernelArg(mHandle.kernel, aIndex, aBytes, aSrc);
		if (error != CL_SUCCESS) return oclError("clSetKernelArg", error, std::to_string(aIndex).c_str());
		return true;
	}

	Context ANVIL_CALL Kernel::context() const throw() {
		Context tmp;
		Handle h;
		h.context = getInfo<cl_context>(CL_KERNEL_CONTEXT);
		tmp.create(h);
		return std::move(tmp);
	}

	Program ANVIL_CALL Kernel::program() const throw() {
		Program tmp;
		Handle h;
		h.program = getInfo<cl_program>(CL_KERNEL_PROGRAM);
		tmp.create(h);
		return tmp;
	}

	cl_uint ANVIL_CALL Kernel::arguments() const throw() {
		return mHandle.kernel ? getInfo<cl_uint>(CL_KERNEL_NUM_ARGS) : 0;
	}

	size_t ANVIL_CALL Kernel::workGroupSize(const Device& aDevice) const throw() {
		size_t tmp;
		cl_int error = clGetKernelWorkGroupInfo(mHandle.kernel, aDevice.handle().device, CL_KERNEL_WORK_GROUP_SIZE, sizeof(tmp), &tmp, NULL);
		if (error != CL_SUCCESS) oclError("clGetKernelWorkGroupInfo", error, (name() + std::string(", CL_KERNEL_WORK_GROUP_SIZE")).c_str());
		return tmp;
	}

	Device::WorkItemCount ANVIL_CALL Kernel::compileWorkGroupSize(const Device& aDevice) const throw() {
		Device::WorkItemCount tmp;
		cl_int error = clGetKernelWorkGroupInfo(mHandle.kernel, aDevice.handle().device, CL_KERNEL_COMPILE_WORK_GROUP_SIZE, sizeof(tmp), &tmp, NULL);
		if (error != CL_SUCCESS) oclError("clGetKernelWorkGroupInfo", error, (name() + std::string(", CL_KERNEL_COMPILE_WORK_GROUP_SIZE")).c_str());
		return tmp;
	}

	cl_ulong ANVIL_CALL Kernel::localMemorySize(const Device& aDevice) const throw() {
		cl_ulong tmp;
		cl_int error = clGetKernelWorkGroupInfo(mHandle.kernel, aDevice.handle().device, CL_KERNEL_LOCAL_MEM_SIZE, sizeof(tmp), &tmp, NULL);
		if (error != CL_SUCCESS) oclError("clGetKernelWorkGroupInfo", error, (name() + std::string(", CL_KERNEL_LOCAL_MEM_SIZE")).c_str());
		return tmp;
	}

	const char* Kernel::name() const throw() {
		enum { MAX_KERNEL_NAME = 1024 };
		static char gNameBuffer[MAX_KERNEL_NAME];
		cl_int error = clGetKernelInfo(mHandle.kernel, CL_KERNEL_FUNCTION_NAME, MAX_KERNEL_NAME, gNameBuffer, NULL);
		if (error != CL_SUCCESS) oclError("clGetKernelInfo ", error, "CL_KERNEL_FUNCTION_NAME");
		return gNameBuffer;
	}

	cl_uint ANVIL_CALL Kernel::referenceCount() const throw() {
		cl_uint count;
		cl_uint error = clGetKernelInfo(mHandle.kernel, CL_KERNEL_REFERENCE_COUNT, sizeof(count), &count, NULL);
		if (error == CL_SUCCESS) return count;
		oclError("clGetKernelInfo", error, "CL_KERNEL_REFERENCE_COUNT");
		return 0;
	}

	// NativeKernel

	void __stdcall NativeKernel::execute_(void* aArgs) throw() {
		reinterpret_cast<NativeKernel*>(aArgs)->onExecute();
	}

	ANVIL_CALL NativeKernel::NativeKernel(Context& aContext) :
		mContext(reinterpret_cast<cl_context&>(aContext))
	{}

	ANVIL_CALL NativeKernel::~NativeKernel() {

	}

	Event ANVIL_CALL NativeKernel::execute(CommandQueue& aQueue) {
		Event event;

		NativeKernel* args = this;
		cl_event& event_ref = *reinterpret_cast<cl_event*>(&event);
		cl_int error = clEnqueueNativeKernel(reinterpret_cast<cl_command_queue&>(aQueue), NativeKernel::execute_, &args, sizeof(void*), 0, NULL, NULL, 0, NULL, &event_ref);
		if (error != CL_SUCCESS) {
			oclError("clEnqueueNativeKernel", error);
			return Event();
		}

		return event;
	}

}}