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

#include "anvil/ocl/Event.hpp"

namespace anvil { namespace ocl {

	class CommandQueue;

	class Buffer {
	private:
		Context* mContext;
		cl_mem mBuffer;
		cl_mem_flags mFlags;
		size_t mOrigin;
		size_t mSize;
		void* mHostPtr;
		bool mIsSubBuffer;

		Buffer(const Buffer&) = delete;
		Buffer& operator=(const Buffer&) = delete;
	public:
		enum AccessMode : cl_mem_flags {
			READ_ONLY = CL_MEM_READ_ONLY,
			WRITE_ONLY = CL_MEM_WRITE_ONLY,
			READ_WRITE = CL_MEM_READ_WRITE,
		};

		ANVIL_CALL Buffer() throw();
		ANVIL_CALL Buffer(Context&, size_t, AccessMode aMode = READ_WRITE);
		ANVIL_CALL Buffer(Context&, size_t, void*, AccessMode aMode = READ_WRITE);
		ANVIL_CALL Buffer(Buffer&&) throw();
		ANVIL_CALL ~Buffer();

		Buffer& ANVIL_CALL operator=(Buffer&&) throw();
		void ANVIL_CALL swap(Buffer& aOther) throw();

		Buffer ANVIL_CALL createSubBuffer(size_t, size_t) throw();
		bool ANVIL_CALL isSubBuffer() const throw();
		Context& ANVIL_CALL context() const throw();
		ANVIL_CALL operator bool() const throw();
		AccessMode ANVIL_CALL accessMode() const throw();
		size_t ANVIL_CALL origin() const throw();
		size_t ANVIL_CALL size() const throw();
		void* ANVIL_CALL hostPtr() throw();
		const void* ANVIL_CALL hostPtr() const throw();
		Event ANVIL_CALL read(CommandQueue&, size_t, void*, size_t) const;
		Event ANVIL_CALL write(CommandQueue&, size_t, const void*, size_t);
		Event ANVIL_CALL copy(CommandQueue&, Buffer&, size_t, size_t, size_t) const;
	};
}}

#endif
