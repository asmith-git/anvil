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
		mContext(NULL),
		mBuffer(NULL),
		mFlags(0),
		mOrigin(0),
		mSize(0),
		mHostPtr(NULL),
		mIsSubBuffer(false)
	{}

	ANVIL_CALL Buffer::Buffer(Context& aContext, size_t aSize, AccessMode aMode) :
		mContext(&aContext),
		mBuffer(NULL),
		mFlags(aMode),
		mOrigin(0),
		mSize(aSize),
		mHostPtr(NULL),
		mIsSubBuffer(false)
	{
		cl_int error = CL_SUCCESS;
		mBuffer = clCreateBuffer(mContext->mContext, mFlags, mSize, mHostPtr, &error);
		if (error != CL_SUCCESS) {
			mSize = 0;
			oclError("clCreateBuffer", error);
		}
	}

	ANVIL_CALL Buffer::Buffer(Context& aContext, size_t aSize, void* aHostPtr, AccessMode aMode) :
		mContext(&aContext),
		mBuffer(NULL),
		mFlags(aMode | CL_MEM_USE_HOST_PTR),
		mOrigin(0),
		mSize(aSize),
		mHostPtr(aHostPtr),
		mIsSubBuffer(false)
	{
		cl_int error = CL_SUCCESS;
		mBuffer = clCreateBuffer(mContext->mContext, mFlags, mSize, mHostPtr, &error);
		if (error != CL_SUCCESS) {
			mSize = 0;
			oclError("clCreateBuffer", error);
		}
	}

	ANVIL_CALL Buffer::Buffer(Buffer&& aOther) throw() :
		mContext(aOther.mContext),
		mBuffer(aOther.mBuffer),
		mOrigin(aOther.mOrigin),
		mFlags(aOther.mFlags),
		mSize(aOther.mSize),
		mHostPtr(aOther.mHostPtr),
		mIsSubBuffer(aOther.mIsSubBuffer)
	{
		aOther.mBuffer = NULL;
		aOther.mFlags = 0;
		aOther.mOrigin = 0;
		aOther.mSize = 0;
		aOther.mHostPtr = NULL;
		aOther.mIsSubBuffer = false;
	}

	ANVIL_CALL Buffer::~Buffer() {
		if (mBuffer && ! isSubBuffer()) {
			cl_int error = clReleaseMemObject(mBuffer);
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
		std::swap(mFlags, aOther.mFlags);
		std::swap(mOrigin, aOther.mOrigin);
		std::swap(mSize, aOther.mSize);
		std::swap(mHostPtr, aOther.mHostPtr);
		std::swap(mIsSubBuffer, aOther.mIsSubBuffer);
	}

	ANVIL_CALL Buffer::operator bool() const throw() {
		return mBuffer != NULL;
	}

	Buffer::AccessMode ANVIL_CALL Buffer::accessMode() const throw() {
		return
			mFlags & READ_ONLY ? READ_ONLY :
			mFlags & WRITE_ONLY ? WRITE_ONLY :
			READ_WRITE;
	}

	size_t ANVIL_CALL Buffer::origin() const throw() {
		return isSubBuffer() ? mOrigin : 0;
	}

	size_t ANVIL_CALL Buffer::size() const throw() {
		return mSize;
	}

	void* ANVIL_CALL Buffer::hostPtr() throw() {
		return static_cast<uint8_t*>(mHostPtr) + origin();
	}

	const void* ANVIL_CALL Buffer::hostPtr() const throw() {
		return static_cast<const uint8_t*>(mHostPtr) + origin();
	}

	Context& ANVIL_CALL Buffer::context() const throw() {
		return *mContext;
	}

	Event ANVIL_CALL Buffer::read(CommandQueue& aQueue, size_t aOffset, void* aDst, size_t aBytes) const {
		Event event(context());
		cl_int error = clEnqueueReadBuffer(aQueue.mQueue, mBuffer, CL_FALSE, aOffset + origin(), aBytes, aDst, 0, NULL, &event.mEvent);
		if (error != CL_SUCCESS) oclError("clEnqueueReadBuffer", error);
		return event;
	}

	Event ANVIL_CALL Buffer::write(CommandQueue& aQueue, size_t aOffset, const void* aSrc, size_t aBytes) {
		Event event(context());
		cl_int error = clEnqueueWriteBuffer(aQueue.mQueue, mBuffer, CL_FALSE, aOffset + origin(), aBytes, aSrc, 0, NULL, &event.mEvent);
		if (error != CL_SUCCESS) oclError("clEnqueueWriteBuffer", error);
		return event;
	}

	Event ANVIL_CALL Buffer::copy(CommandQueue& aQueue, Buffer& aOther, size_t aThisOffset, size_t aOtherOffset, size_t aBytes) const {
		Event event(context());
		aOtherOffset += aOther.origin();
		cl_int error = clEnqueueCopyBuffer(aQueue.mQueue, mBuffer, aOther.mBuffer, aThisOffset + origin(), aOtherOffset + aOther.origin(), aBytes, 0, NULL, &event.mEvent);
		if (error != CL_SUCCESS) oclError("clEnqueueCopyBuffer ", error);
		return event;
	}

	Buffer ANVIL_CALL Buffer::createSubBuffer(size_t aOrigin, size_t aSize) throw() {
		Buffer tmp;
		tmp.mContext = mContext;
		tmp.mBuffer = mBuffer;
		tmp.mFlags = mFlags;
		tmp.mOrigin = mOrigin + aOrigin;
		tmp.mSize = aSize;
		tmp.mHostPtr = mHostPtr;
		tmp.mIsSubBuffer = true;
		return tmp;
	}

	bool ANVIL_CALL Buffer::isSubBuffer() const throw() {
		return mIsSubBuffer;
	}
}}