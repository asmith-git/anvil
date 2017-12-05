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

namespace anvil { namespace ocl {

	// Buffer

	ANVIL_CALL Buffer::Buffer(const Context& aContext, size_t aSize, AccessMode aMode) :
		mContext(aContext),
		mBuffer(),
		mFlags(aMode),
		mSize(aSize),
		mHostPtr(nullptr)
	{
		cl_int error = CL_SUCCESS;
		mBuffer = clCreateBuffer(mContext.mContext, mFlags, mSize, mHostPtr, &error);
		if (error != CL_SUCCESS) {
			mSize = 0;
			oclError("clCreateBuffer", error);
		}
	}

	ANVIL_CALL Buffer::Buffer(const Context& aContext, size_t aSize, void* aHostPtr, AccessMode aMode) :
		mContext(aContext),
		mBuffer(),
		mFlags(aMode | CL_MEM_USE_HOST_PTR),
		mSize(aSize),
		mHostPtr(aHostPtr)
	{
		cl_int error = CL_SUCCESS;
		mBuffer = clCreateBuffer(mContext.mContext, mFlags, mSize, mHostPtr, &error);
		if (error != CL_SUCCESS) {
			mSize = 0;
			oclError("clCreateBuffer", error);
		}
	}

	ANVIL_CALL Buffer::~Buffer() {
		if (mSize != 0) {
			cl_int error = clReleaseMemObject(mBuffer);
			if (error != CL_SUCCESS) oclError("clReleaseMemObject", error);
		}
	}

	ANVIL_CALL Buffer::operator bool() const throw() {
		return mSize != 0;
	}

	Buffer::AccessMode ANVIL_CALL Buffer::accessMode() const throw() {
		return
			mFlags & READ_ONLY ? READ_ONLY :
			mFlags & WRITE_ONLY ? WRITE_ONLY :
			READ_WRITE;
	}

	size_t ANVIL_CALL Buffer::origin() const throw() {
		return 0;
	}

	size_t ANVIL_CALL Buffer::size() const throw() {
		return mSize;
	}

	void* ANVIL_CALL Buffer::hostPtr() throw() {
		return mHostPtr;
	}

	const void* ANVIL_CALL Buffer::hostPtr() const throw() {
		return mHostPtr;
	}

	const Context& ANVIL_CALL Buffer::context() const throw() {
		return mContext;
	}

	// SubBuffer

	ANVIL_CALL SubBuffer::SubBuffer(Buffer& aBuffer, size_t aOrigin, size_t aSize) :
		mBuffer(aBuffer),
		mOrigin(aOrigin),
		mSize(aSize)
	{
		cl_int error = CL_SUCCESS;
		mSubBuffer = clCreateSubBuffer(aBuffer.mBuffer, aBuffer.mFlags, CL_BUFFER_CREATE_TYPE_REGION, &mOrigin, &error);
		if (error != CL_SUCCESS) {
			mSize = 0;
			oclError("clCreateSubBuffer", error);
		}
	}

	ANVIL_CALL SubBuffer::~SubBuffer() {
		if (mSize != 0) {
			cl_int error = clReleaseMemObject(mSubBuffer);
			if (error != CL_SUCCESS) oclError("clReleaseMemObject", error);
		}
	}

	const Context& ANVIL_CALL SubBuffer::context() const throw() {
		return mBuffer.context();
	}

	ANVIL_CALL SubBuffer::operator bool() const throw() {
		return mSize != 0 && mBuffer;
	}

	Buffer::AccessMode ANVIL_CALL SubBuffer::accessMode() const throw() {
		return mBuffer.accessMode();
	}

	size_t ANVIL_CALL SubBuffer::origin() const throw() {
		return mOrigin;
	}

	size_t ANVIL_CALL SubBuffer::size() const throw() {
		return mSize;
	}

	void* ANVIL_CALL SubBuffer::hostPtr() throw() {
		uint8_t* ptr = static_cast<uint8_t*>(mBuffer.hostPtr());
		if (ptr != nullptr) {
			ptr += mOrigin;
		}
		return ptr;
	}

	const void* ANVIL_CALL SubBuffer::hostPtr() const throw() {
		const uint8_t* ptr = static_cast<const uint8_t*>(mBuffer.hostPtr());
		if (ptr != nullptr) {
			ptr += mOrigin;
		}
		return ptr;
	}

	Buffer& ANVIL_CALL SubBuffer::buffer() throw() {
		return mBuffer;
	}

}}