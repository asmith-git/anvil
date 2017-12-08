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
		mBuffer(NULL),
		mIsSubBuffer(false)
	{}

	ANVIL_CALL Buffer::Buffer(Context& aContext, size_t aSize, AccessMode aMode) throw() :
		mBuffer(NULL),
		mIsSubBuffer(false)
	{
		cl_int error = CL_SUCCESS;
		mBuffer = clCreateBuffer(aContext.mContext, aMode, aSize, NULL, &error);
		if (error != CL_SUCCESS) {
			mBuffer = NULL;
			oclError("clCreateBuffer", error);
		}
	}

	ANVIL_CALL Buffer::Buffer(Context& aContext, size_t aSize, void* aHostPtr, AccessMode aMode) throw() :
		mBuffer(NULL),
		mIsSubBuffer(false)
	{
		cl_int error = CL_SUCCESS;
		mBuffer = clCreateBuffer(aContext.mContext, aMode | CL_MEM_USE_HOST_PTR, aSize, aHostPtr, &error);
		if (error != CL_SUCCESS) {
			mBuffer = NULL;
			oclError("clCreateBuffer", error);
		}
	}

	ANVIL_CALL Buffer::Buffer(Buffer&& aOther) throw() :
		mBuffer(NULL),
		mIsSubBuffer(false)
	{
		swap(aOther);
	}

	ANVIL_CALL Buffer::~Buffer() throw() {
		if (mBuffer) {
			cl_int error = clReleaseMemObject(mBuffer);
			mBuffer = NULL;
			if (error != CL_SUCCESS) oclError("clReleaseMemObject", error);
		}
	}

	Buffer& ANVIL_CALL Buffer::operator=(Buffer&& aOther) throw() {
		swap(aOther);
		return *this;
	}

	void ANVIL_CALL Buffer::swap(Buffer& aOther) throw() {
		std::swap(mBuffer, aOther.mBuffer);
		std::swap(mBuffer, aOther.mBuffer);
		std::swap(mIsSubBuffer, aOther.mIsSubBuffer);
	}

	ANVIL_CALL Buffer::operator bool() const throw() {
		return mBuffer != NULL;
	}

	cl_mem ANVIL_CALL Buffer::data() throw() {
		return mBuffer;
	}

	cl_mem_flags ANVIL_CALL Buffer::flags() const throw() {
		return mBuffer ? getInfo<cl_mem_flags>(CL_MEM_FLAGS) : 0;
	}

	cl_context ANVIL_CALL Buffer::context() const throw() {
		return mBuffer ? getInfo<cl_context>(CL_MEM_CONTEXT) : NULL;
	}

	Buffer::AccessMode ANVIL_CALL Buffer::accessMode() const throw() {
		return static_cast<AccessMode>(flags() & (READ_ONLY | WRITE_ONLY | READ_WRITE));
	}

	size_t ANVIL_CALL Buffer::size() const throw() {
		return mBuffer ? getInfo<size_t>(CL_MEM_SIZE) : 0;
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
		if (mBuffer == NULL) return Event();
		Event event;
		cl_int error = clEnqueueReadBuffer(aQueue.mQueue, mBuffer, CL_FALSE, aOffset, aBytes, 
			aDst, 0, NULL, event.mEvent == NULL ? NULL : &event.mEvent);
		if (error != CL_SUCCESS) {
			oclError("clEnqueueReadBuffer", error);
			return Event();
		}
		return event;
	}

	Event ANVIL_CALL Buffer::write(CommandQueue& aQueue, size_t aOffset, const void* aSrc, size_t aBytes) throw() {
		if (mBuffer == NULL) return Event();
		Event event;
		cl_int error = clEnqueueWriteBuffer(aQueue.mQueue, mBuffer, CL_FALSE, aOffset, aBytes, 
			aSrc, 0, NULL, event.mEvent == NULL ? NULL : &event.mEvent);
		if (error != CL_SUCCESS) {
			oclError("clEnqueueWriteBuffer", error);
			return Event();
		}
		return event;
	}

	Event ANVIL_CALL Buffer::copy(CommandQueue& aQueue, Buffer& aOther, size_t aThisOffset, size_t aOtherOffset, size_t aBytes) const throw() {
		if (mBuffer == NULL || aOther.mBuffer == NULL) return Event();
		Event event;
		cl_int error = clEnqueueCopyBuffer(aQueue.mQueue, mBuffer, aOther.mBuffer, aThisOffset, 
			aOtherOffset + aOther, aBytes, 0, NULL, event.mEvent == NULL ? NULL : &event.mEvent);
		if (error != CL_SUCCESS) {
			oclError("clEnqueueCopyBuffer", error);
			return Event();
		}
		return event;
	}

	Buffer ANVIL_CALL Buffer::createSubBuffer(size_t aOrigin, size_t aSize) throw() {
		Buffer tmp;
		cl_int error = CL_SUCCESS;
		const size_t region[2] { aOrigin, aSize };
		tmp.mBuffer = clCreateSubBuffer(mBuffer, accessMode() | (hostPtr() ? CL_MEM_USE_HOST_PTR : 0), 
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
}}