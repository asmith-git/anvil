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

#ifndef ANVIL_OCL_BUFFER_HPP
#define ANVIL_OCL_BUFFER_HPP

#include "anvil/ocl/Context.hpp"

namespace anvil { namespace ocl {
	class Buffer {
	private:
		Context& mContext;
		cl_mem mBuffer;
		cl_mem_flags mFlags;
		size_t mSize;
		void* mHostPtr;
	public:
		enum AccessMode : cl_mem_flags {
			READ_ONLY = CL_MEM_READ_ONLY,
			WRITE_ONLY = CL_MEM_WRITE_ONLY,
			READ_WRITE = CL_MEM_READ_WRITE,
		};

		Buffer(Context& aContext, size_t aSize, AccessMode aMode = READ_WRITE) :
			mContext(aContext),
			mBuffer(),
			mFlags(aMode),
			mSize(aSize),
			mHostPtr(nullptr)
		{
			cl_int error = CL_SUCCESS;
			mBuffer = clCreateBuffer(mContext.mContext, mFlags, mSize, mHostPtr, &error);
			if(error != CL_SUCCESS) {
				mSize = 0;
				throwException("clCreateBuffer", error);
			}
		}

		Buffer(Context& aContext, size_t aSize, AccessMode aMode = READ_WRITE, void* aHostPtr) :
			mContext(aContext),
			mBuffer(),
			mFlags(aMode | CL_MEM_USE_HOST_PTR),
			mSize(aSize),
			mHostPtr(aHostPtr)
		{
			cl_int error = CL_SUCCESS;
			mBuffer = clCreateBuffer(mContext.mContext, mFlags, mSize, mHostPtr, &error);
			if(error != CL_SUCCESS) {
				mSize = 0;
				throwException("clCreateBuffer", error);
			}
		}
			
		~Buffer() {
			if(mSize != 0) {
				cl_int error = clReleaseMemObject(mBuffer);
				if(error != CL_SUCCESS) throwException("clReleaseMemObject", error);
			}
		}
		
		inline operator bool() const throw() {
			return mSize != 0;
		}
		
		inline AccessMode accessMode() const throw() {
			return 
				mFlags & READ_ONLY ? READ_ONLY :
				mFlags & WRITE_ONLY ?  WRITE_ONLY :
				READ_WRITE;
		}
		
		inline size_t size() const throw() {
			return mSize;
		}
		
		inline void* hostPtr() throw() {
			return mHostPtr;
		}
		
		inline const void* hostPtr() const throw() {
			return mHostPtr;
		}
	};
}}
