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

	// Buffer

	ANVIL_CALL Buffer::Buffer() throw() :
		Object(Handle::BUFFER),
		mIsSubBuffer(false)
	{}

	ANVIL_CALL Buffer::Buffer(Buffer&& aOther) throw() :
		Object(Handle::BUFFER),
		mIsSubBuffer(false)
	{
		swap(aOther);
	}

	ANVIL_CALL Buffer::~Buffer() throw() {
		destroy();
	}

	Buffer& ANVIL_CALL Buffer::operator=(Buffer&& aOther) throw() {
		swap(aOther);
		return *this;
	}

	void ANVIL_CALL Buffer::swap(Buffer& aOther) throw() {
		std::swap(mHandle, aOther.mHandle);
		std::swap(mIsSubBuffer, aOther.mIsSubBuffer);
	}
	
	bool ANVIL_CALL Buffer::create(Context& aContext, size_t aSize, AccessMode aMode) throw() {
		return create(aContext, aSize, NULL, aMode);
	}

	bool ANVIL_CALL Buffer::create(Context& aContext, size_t aSize, void* aHostPtr, AccessMode aMode) throw() {
		if (mHandle.buffer) if (!destroy()) return false;

		const cl_mem_flags flags = aMode | (aHostPtr ? CL_MEM_USE_HOST_PTR : 0);
		cl_int error = CL_SUCCESS;
#ifdef ANVIL_LOG_OCL
		std::cerr << "clCreateBuffer (" << aContext.handle().context << ", " << flags << ", " << aSize << ", " << aHostPtr << ", " << &error << ")" << std::endl;
#endif
		mHandle.buffer = clCreateBuffer(aContext.handle(), flags, aSize, aHostPtr, &error);
		if (error != CL_SUCCESS) {
			mHandle.buffer = NULL;
			return oclError("clCreateBuffer", error);
		}
		onCreate();
		return true;
	}

	bool Buffer::destroy() throw() {
		if (mHandle.buffer) {
#ifdef ANVIL_LOG_OCL
			std::cerr << "clReleaseMemObject (" << mHandle.buffer << ")" << std::endl;
#endif
			cl_int error = clReleaseMemObject(mHandle.buffer);
			if (error != CL_SUCCESS) return oclError("clReleaseMemObject", error);
			onDestroy();
			mHandle.buffer = NULL;
			return true;
		}
		return false;
	}

	bool ANVIL_CALL Buffer::createNoRetain(Handle aHandle) throw() {
		if (aHandle.type != Handle::BUFFER) return false;
		if (mHandle.buffer != NULL) if (!destroy()) return false;
		if (aHandle.buffer) {
			mHandle = aHandle;
			onCreate();
		}
		return true;
	}

	bool ANVIL_CALL Buffer::create(Handle aHandle) throw() {
		if (!createNoRetain(aHandle)) return false;
		if (aHandle.buffer) {
			mHandle = aHandle;
			onCreate();
		}
		return true;
	}

	cl_mem_flags ANVIL_CALL Buffer::flags() const throw() {
		return mHandle.buffer ? getInfo<cl_mem_flags>(CL_MEM_FLAGS) : 0;
	}

	Context ANVIL_CALL Buffer::context() const throw() {
		Context tmp;
		tmp.create(getInfo<cl_context>(CL_MEM_CONTEXT));
		return std::move(tmp);
	}

	Buffer::AccessMode ANVIL_CALL Buffer::accessMode() const throw() {
		return static_cast<AccessMode>(flags() & (READ_ONLY | WRITE_ONLY | READ_WRITE));
	}

	size_t ANVIL_CALL Buffer::size() const throw() {
		return mHandle.buffer ? getInfo<size_t>(CL_MEM_SIZE) : 0;
	}

	void* ANVIL_CALL Buffer::hostPtr() throw() {
		return flags() & CL_MEM_USE_HOST_PTR ?
			getInfo<void*>(CL_MEM_HOST_PTR) : nullptr;

	}

	const void* ANVIL_CALL Buffer::hostPtr() const throw() {
		return flags() & CL_MEM_USE_HOST_PTR ?
			getInfo<void*>(CL_MEM_HOST_PTR) : nullptr;
	}

	Event ANVIL_CALL Buffer::read(CommandQueue& aQueue, size_t aOffset, void* aDst, size_t aBytes) const throw() {
		if (mHandle.buffer == NULL) return Event();
		Handle handle(Handle::EVENT);
#ifdef ANVIL_LOG_OCL
		std::cerr << "clEnqueueReadBuffer (" << aQueue.handle().buffer << ", " << mHandle.buffer << ", " << "CL_FALSE" << ", " << aOffset << ", " << aBytes << ", " <<
			aDst << ", " << 0 << ", " << "NULL" << ", " << &handle.event << ")" << std::endl;
#endif
		cl_int error = clEnqueueReadBuffer(aQueue.handle(), mHandle.buffer, CL_FALSE, aOffset, aBytes,
			aDst, 0, NULL, &handle.event);
		if (error != CL_SUCCESS) {
			oclError("clEnqueueReadBuffer", error);
			return Event();
		}
		Event event;
		event.create(handle);
		return event;
	}

	Event ANVIL_CALL Buffer::write(CommandQueue& aQueue, size_t aOffset, const void* aSrc, size_t aBytes) throw() {
		if (mHandle.buffer == NULL) return Event();
		Handle handle(Handle::EVENT);
#ifdef ANVIL_LOG_OCL
		std::cerr << "clEnqueueReadBuffer (" << aQueue.handle().queue << ", " << mHandle.buffer << ", " << "CL_FALSE" << ", " << aOffset << ", " << aBytes << ", " <<
			aSrc << ", " << 0 << ", " << "NULL" << ", " << &handle.event << ")" << std::endl;
#endif
		cl_int error = clEnqueueWriteBuffer(aQueue.handle(), mHandle.buffer, CL_FALSE, aOffset, aBytes,
			aSrc, 0, NULL, &handle.event);
		if (error != CL_SUCCESS) {
			oclError("clEnqueueWriteBuffer", error);
			return Event();
		}
		Event event;
		event.create(handle);
		return event;
	}

	Event ANVIL_CALL Buffer::copy(CommandQueue& aQueue, Buffer& aOther, size_t aThisOffset, size_t aOtherOffset, size_t aBytes) const throw() {
		if (mHandle.buffer == NULL || aOther.mHandle.buffer == NULL) return Event();
		Handle handle(Handle::EVENT);
#ifdef ANVIL_LOG_OCL
		std::cerr << "clEnqueueCopyBuffer (" << aQueue.handle().queue << ", " << mHandle.buffer << ", " << aOther.mHandle.buffer << ", " << aThisOffset << ", " <<
			aOtherOffset + aOther << ", " << aBytes << ", " << 0 << ", " << "NULL" << ", " << &handle.event << ")" << std::endl;
#endif
		cl_int error = clEnqueueCopyBuffer(aQueue.handle(), mHandle.buffer, aOther.mHandle.buffer, aThisOffset,
			aOtherOffset + aOther, aBytes, 0, NULL, &handle.event);
		if (error != CL_SUCCESS) {
			oclError("clEnqueueCopyBuffer", error);
			return Event();
		}
		Event event;
		event.create(handle);
		return event;
	}

	Buffer ANVIL_CALL Buffer::createSubBuffer(size_t aOrigin, size_t aSize) throw() {
		Buffer tmp;
		cl_int error = CL_SUCCESS;
		const size_t region[2] { aOrigin, aSize };
#ifdef ANVIL_LOG_OCL
		std::cerr << "clCreateSubBuffer (" << mHandle.buffer << ", " << (accessMode() | (hostPtr() ? CL_MEM_USE_HOST_PTR : 0)) << ", " <<
			"CL_BUFFER_CREATE_TYPE_REGION" << ", " << region << ", " << &error << ")" << std::endl;
#endif
		tmp.mHandle.buffer = clCreateSubBuffer(mHandle.buffer, accessMode() | (hostPtr() ? CL_MEM_USE_HOST_PTR : 0),
			CL_BUFFER_CREATE_TYPE_REGION, region, &error);
		if (error == CL_SUCCESS) {
			tmp.mIsSubBuffer = true;
		} else {
			oclError("clCreateSubBuffer ", error);
		}
		return tmp;
	}

	bool ANVIL_CALL Buffer::isSubBuffer() const throw() {
		return mIsSubBuffer;
	}

	cl_uint ANVIL_CALL Buffer::referenceCount() const throw() {
		cl_uint count;
#ifdef ANVIL_LOG_OCL
		std::cerr << "clGetMemObjectInfo (" << mHandle.buffer << ", " << "CL_MEM_REFERENCE_COUNT" << ", " << 
			sizeof(count) << ", " << &count << ", " << "NULL" << std::endl;
#endif
		cl_uint error = clGetMemObjectInfo(mHandle.buffer, CL_MEM_REFERENCE_COUNT, sizeof(count), &count, NULL);
		if (error == CL_SUCCESS) return count;
		oclError("clGetMemObjectInfo", error, "CL_MEM_REFERENCE_COUNT");
		return 0;
	}

	Handle::Type ANVIL_CALL Buffer::type() const throw() {
		return Handle::BUFFER;
	}
}}