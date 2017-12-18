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

	enum {
		NATIVE_FLAG = 1
	};

	struct KernelData {
		Kernel::NativeFunction function;
		std::vector<uint8_t> args;
		cl_uint arg_count;
		cl_uint current_arg;
	};

	// Kernel

	ANVIL_CALL Kernel::Kernel() throw() :
		Object(Handle::KERNEL)
	{}

	ANVIL_CALL Kernel::Kernel(Kernel&& aOther) throw():
		Object(Handle::KERNEL)
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

	bool ANVIL_CALL Kernel::create(NativeFunction aFunction, cl_uint aArgCount) throw() {
		if (mHandle.kernel != NULL) if (!destroy()) return false;
		mHandle.user = aFunction;
		std::shared_ptr<KernelData> data(new KernelData());
		data->function = aFunction;
		data->arg_count = aArgCount;
		data->current_arg = 0;
		if (!setExtraData(data)) {
			mHandle.user = NULL;
			return false;
		}
		onCreate();
		return true;
	}

	bool ANVIL_CALL Kernel::create(const Program& aProgram, const char* aName) throw() {
		cl_int error = CL_SUCCESS;
		mHandle.kernel = clCreateKernel(const_cast<Program&>(aProgram).handle(), aName, &error);
#ifdef ANVIL_LOG_OCL
		std::cerr << getErrorName(error) << " <- clCreateKernel (" << const_cast<Program&>(aProgram).handle().program << ", " << aName << ", " << (void*)&error << ")" << std::endl;
#endif
		if (error != CL_SUCCESS) {
			mHandle.kernel = NULL;
			return oclError("clCreateKernel", error, aName);
		}
		onCreate();
		return true;
	}

	bool ANVIL_CALL Kernel::destroy() throw() {
		if (mHandle.kernel) {
			if (isNative()) {
				onDestroy();
				mHandle.kernel = NULL;
			}else {
				cl_int error = clReleaseKernel(mHandle.kernel);
#ifdef ANVIL_LOG_OCL
				std::cerr << getErrorName(error) << " <- clReleaseKernel (" << mHandle.kernel << ")" << std::endl;
#endif
				if (error != CL_SUCCESS) return oclError("clReleaseKernel", error);
				onDestroy();
				mHandle.kernel = NULL;
			}
			return true;
		}
		return false;
	}

	bool ANVIL_CALL Kernel::retain() throw() {
		if (mHandle.kernel) {
			cl_int error = clRetainKernel(mHandle.kernel);
#ifdef ANVIL_LOG_OCL
			std::cerr << getErrorName(error) << " <- clRetainKernel (" << mHandle.kernel << ")" << std::endl;
#endif
			return error == CL_SUCCESS ? true : oclError("clRetainKernel", error);
		}
		return false;
	}

	Event ANVIL_CALL Kernel::operator()(CommandQueue& aQueue) {
		Handle handle(Handle::EVENT);
		if (isNative()) {
			std::shared_ptr<KernelData> data = std::static_pointer_cast<KernelData>(getExtraData());
			if (!data) {
				oclError("clEnqueueNativeKernel  ", CL_INVALID_VALUE);
				return Event();
			}
			const size_t size = data->args.size();
			cl_int error = clEnqueueNativeKernel(aQueue.handle(), data->function, size == 0 ? NULL : &data->args[0], size, 0, NULL, NULL, 0, NULL, &mHandle.event);
#ifdef ANVIL_LOG_OCL
			std::cerr << getErrorName(error) << " <- clEnqueueNativeKernel (" << aQueue.handle().kernel << ", " << data->function << ", " << (void*)(size == 0 ? NULL : &data->args[0]) <<
				", " << size << ", " << 0 << ", " << "NULL" << ", " << "NULL" << ", " << 0 << ", " << "NULL" << ", " << &mHandle.event << ")" << std::endl;
#endif
			data->args.clear();
			data->current_arg = 0;
			if (error != CL_SUCCESS) {
				oclError("clEnqueueNativeKernel  ", error);
				return Event();
			}
		} else {
#ifdef CL_VERSION_1_2
			oclError("clEnqueueNDRangeKernel", CL_INVALID_WORK_GROUP_SIZE, name());
			return Event();
#else
#ifdef ANVIL_LOG_OCL
			cl_int error = clEnqueueTask (aQueue.handle(), mHandle.kernel, 0, NULL, &mHandle.event);
			std::cerr << getErrorName(error) << " <- clEnqueueTask (" << aQueue.handle().queue<< ", " << mHandle.kernel<< ", " << 0<< ", " << "NULL"<< ", " << &mHandle.event << ")" << std::endl;
#endif
			if (error != CL_SUCCESS) {
				oclError("clEnqueueTask ", error, name());
				return Event();
			}
#endif
		}
		Event event;
		event.createNoRetain(handle);
		return event;
	}

	Event ANVIL_CALL Kernel::operator()(CommandQueue& aQueue, cl_uint aDimensions, const size_t *aGlobalOffset, const size_t *aGlobalWorkSize, const size_t *aLocalWorkSize) {
		if (isNative()) return operator()(aQueue);
		Handle handle(Handle::EVENT);
		cl_int error = clEnqueueNDRangeKernel(aQueue.handle(), mHandle.kernel, aDimensions, aGlobalOffset, aGlobalWorkSize, aLocalWorkSize, 0, NULL, &mHandle.event);
#ifdef ANVIL_LOG_OCL
		std::cerr << getErrorName(error) << " <- clEnqueueNDRangeKernel (" << aQueue.handle().queue << ", " << mHandle.kernel << ", " << aDimensions << ", " <<
			aGlobalOffset<< ", " << aGlobalWorkSize<< ", " << aLocalWorkSize<< ", " << 0<< ", " << "NULL"<< ", " << &mHandle.event << ")" << std::endl;
#endif
		if (error != CL_SUCCESS) {
			oclError("clEnqueueNDRangeKernel", error, name());
			return Event();
		}
		Event event;
		event.createNoRetain(handle);
		return event;
	}

	bool ANVIL_CALL Kernel::setArgument(cl_uint aIndex, const void* aSrc, size_t aBytes) {
		if (isNative()) {
			std::shared_ptr<KernelData> data = std::static_pointer_cast<KernelData>(getExtraData());
			if (aIndex != data->current_arg) return oclError("clSetKernelArg", CL_INVALID_ARG_INDEX, std::to_string(aIndex).c_str());
			const uint8_t* const ptr = static_cast<const uint8_t*>(aSrc);
			for (size_t i = 0; i < aBytes; ++i) {
				data->args.push_back(ptr[i]);
			}
			++data->current_arg;
		} else {
			cl_int error = clSetKernelArg(mHandle.kernel, aIndex, aBytes, aSrc);
#ifdef ANVIL_LOG_OCL
			std::cerr << getErrorName(error) << " <- clSetKernelArg (" << mHandle.kernel << ", " << aIndex << ", " << aBytes << ", " << aSrc << ")" << std::endl;
#endif
			if (error != CL_SUCCESS) return oclError("clSetKernelArg", error, std::to_string(aIndex).c_str());
		}
		return true;
	}

	Context ANVIL_CALL Kernel::context() const throw() {
		Context tmp;
		tmp.Object::create(getInfo<cl_context>(CL_KERNEL_CONTEXT));
		return std::move(tmp);
	}

	Program ANVIL_CALL Kernel::program() const throw() {
		Program tmp;
		tmp.Object::create(getInfo<cl_program>(CL_KERNEL_PROGRAM));
		return tmp;
	}

	cl_uint ANVIL_CALL Kernel::arguments() const throw() {
		return mHandle.kernel ? isNative() ? 1 : getInfo<cl_uint>(CL_KERNEL_NUM_ARGS) : 0;
	}

	size_t ANVIL_CALL Kernel::workGroupSize(const Device& aDevice) const throw() {
		if (isNative()) {
			oclError("anvil::ocl::Kernel::workGroupSize", CL_INVALID_KERNEL, "Kernel is native");
			return 0;
		}
		size_t tmp;
		cl_int error = clGetKernelWorkGroupInfo(mHandle.kernel, aDevice.handle(), CL_KERNEL_WORK_GROUP_SIZE, sizeof(tmp), &tmp, NULL);
#ifdef ANVIL_LOG_OCL
		std::cerr << getErrorName(error) << " <- clGetKernelWorkGroupInfo (" << mHandle.kernel << ", " << aDevice.handle().device << ", " <<
			"CL_KERNEL_WORK_GROUP_SIZE" << ", " << sizeof(tmp) << ", " << &tmp << ", " << "NULL" << ")" << std::endl;
#endif
		if (error != CL_SUCCESS) oclError("clGetKernelWorkGroupInfo", error, (name() + std::string(", CL_KERNEL_WORK_GROUP_SIZE")).c_str());
		return tmp;
	}

	Device::WorkItemCount ANVIL_CALL Kernel::compileWorkGroupSize(const Device& aDevice) const throw() {
		if (isNative()) {
			oclError("anvil::ocl::Kernel::compileWorkGroupSize", CL_INVALID_KERNEL, "Kernel is native");
			return { 0, 0, 0 };
		}
		Device::WorkItemCount tmp;
		cl_int error = clGetKernelWorkGroupInfo(mHandle.kernel, aDevice.handle(), CL_KERNEL_COMPILE_WORK_GROUP_SIZE, sizeof(tmp), &tmp, NULL);
#ifdef ANVIL_LOG_OCL
		std::cerr << getErrorName(error) << " <- clGetKernelWorkGroupInfo (" << mHandle.kernel << ", " << aDevice.handle().device << ", " <<
			"CL_KERNEL_COMPILE_WORK_GROUP_SIZE" << ", " << sizeof(tmp) << ", " << &tmp << ", " << "NULL" << ")" << std::endl;
#endif
		if (error != CL_SUCCESS) oclError("clGetKernelWorkGroupInfo", error, (name() + std::string(", CL_KERNEL_COMPILE_WORK_GROUP_SIZE")).c_str());
		return tmp;
	}

	cl_ulong ANVIL_CALL Kernel::localMemorySize(const Device& aDevice) const throw() {
		if (isNative()) {
			oclError("anvil::ocl::Kernel::localMemorySize", CL_INVALID_KERNEL, "Kernel is native");
			return 0;
		}
		cl_ulong tmp;
		cl_int error = clGetKernelWorkGroupInfo(mHandle.kernel, aDevice.handle(), CL_KERNEL_LOCAL_MEM_SIZE, sizeof(tmp), &tmp, NULL);
#ifdef ANVIL_LOG_OCL
		std::cerr << getErrorName(error) << " <- clGetKernelWorkGroupInfo (" << mHandle.kernel << ", " << aDevice.handle().device << ", " <<
			"CL_KERNEL_LOCAL_MEM_SIZE" << ", " << sizeof(tmp) << ", " << &tmp << ", " << "NULL" << ")" << std::endl;
#endif
		if (error != CL_SUCCESS) oclError("clGetKernelWorkGroupInfo", error, (name() + std::string(", CL_KERNEL_LOCAL_MEM_SIZE")).c_str());
		return tmp;
	}

	const char* Kernel::name() const throw() {
		if (isNative()) {
			oclError("anvil::ocl::Kernel::name", CL_INVALID_KERNEL, "Kernel is native");
			return NULL;
		}
		enum { MAX_KERNEL_NAME = 1024 };
		static char gNameBuffer[MAX_KERNEL_NAME];
		cl_int error = clGetKernelInfo(mHandle.kernel, CL_KERNEL_FUNCTION_NAME, MAX_KERNEL_NAME, gNameBuffer, NULL);
#ifdef ANVIL_LOG_OCL
		std::cerr << getErrorName(error) << " <- clGetKernelInfo (" << mHandle.kernel << ", " << mHandle.kernel << ", " <<
			"CL_KERNEL_FUNCTION_NAME" << ", " << MAX_KERNEL_NAME << ", " << gNameBuffer << ", " << "NULL" << ")" << std::endl;
#endif
		if (error != CL_SUCCESS) oclError("clGetKernelInfo ", error, "CL_KERNEL_FUNCTION_NAME");
		return gNameBuffer;
	}

	cl_uint ANVIL_CALL Kernel::referenceCount() const throw() {
		if (isNative()) return const_cast<Kernel*>(this)->getExtraData().use_count() - 1;
		cl_uint count;
		cl_uint error = clGetKernelInfo(mHandle.kernel, CL_KERNEL_REFERENCE_COUNT, sizeof(count), &count, NULL);
#ifdef ANVIL_LOG_OCL
		std::cerr << getErrorName(error) << " <- clGetKernelInfo (" << mHandle.kernel << ", " << mHandle.kernel << ", " <<
			"CL_KERNEL_REFERENCE_COUNT" << ", " << sizeof(count) << ", " << &count << ", " << "NULL" << ")" << std::endl;
#endif
		if (error == CL_SUCCESS) return count;
		oclError("clGetKernelInfo", error, "CL_KERNEL_REFERENCE_COUNT");
		return 0;
	}

	Handle::Type Kernel::type() const throw() {
		return Handle::KERNEL;
	}

	bool ANVIL_CALL Kernel::isNative() const throw() {
		return const_cast<Kernel*>(this)->getExtraData() ? true : false;
	}

}}