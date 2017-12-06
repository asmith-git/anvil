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

	class BufferInterface {
	public:
		enum AccessMode : cl_mem_flags {
			READ_ONLY = CL_MEM_READ_ONLY,
			WRITE_ONLY = CL_MEM_WRITE_ONLY,
			READ_WRITE = CL_MEM_READ_WRITE,
		};

		virtual ANVIL_CALL ~BufferInterface() {}

		virtual const Context& ANVIL_CALL context() const throw() = 0;
		virtual ANVIL_CALL operator bool() const throw() = 0;
		virtual AccessMode ANVIL_CALL accessMode() const throw() = 0;
		virtual size_t ANVIL_CALL origin() const throw() = 0;
		virtual size_t ANVIL_CALL size() const throw() = 0;
		virtual void* ANVIL_CALL hostPtr() throw() = 0;
		virtual const void* ANVIL_CALL hostPtr() const throw() = 0;
		virtual Event ANVIL_CALL read(CommandQueue&, size_t, void*, size_t) const = 0;
		virtual Event ANVIL_CALL write(CommandQueue&, size_t, const void*, size_t) = 0;
		virtual Event ANVIL_CALL copy(CommandQueue&, BufferInterface&, size_t, size_t, size_t) const = 0;

		//! \todo readRect, writeRect, copy
	};

	class Buffer : public BufferInterface {
	private:
		const Context& mContext;
		cl_mem mBuffer;
		cl_mem_flags mFlags;
		size_t mSize;
		void* mHostPtr;

		Buffer(const Buffer&) = delete;
		Buffer& operator=(const Buffer&) = delete;
	public:
		friend class SubBuffer;

		ANVIL_CALL Buffer(const Context&);
		ANVIL_CALL Buffer(const Context&, size_t, AccessMode aMode = READ_WRITE);
		ANVIL_CALL Buffer(const Context&, size_t, void*, AccessMode aMode = READ_WRITE);
		ANVIL_CALL Buffer(Buffer&&);
		ANVIL_CALL ~Buffer();

		Buffer& ANVIL_CALL operator=(Buffer&&);

		void ANVIL_CALL swap(Buffer& aOther);
		
		// Inherited from BufferInterface

		const Context& ANVIL_CALL context() const throw() override;
		ANVIL_CALL operator bool() const throw() override;
		AccessMode ANVIL_CALL accessMode() const throw() override;
		size_t ANVIL_CALL origin() const throw() override;
		size_t ANVIL_CALL size() const throw() override;
		void* ANVIL_CALL hostPtr() throw() override;
		const void* ANVIL_CALL hostPtr() const throw() override;
		Event ANVIL_CALL read(CommandQueue&, size_t, void*, size_t) const override;
		Event ANVIL_CALL write(CommandQueue&, size_t, const void*, size_t) override;
		Event ANVIL_CALL copy(CommandQueue&, BufferInterface&, size_t, size_t, size_t) const override;
	};

	class SubBuffer : public BufferInterface {
	private:
		Buffer& mBuffer;
		cl_mem mSubBuffer;
		size_t mOrigin;
		size_t mSize;

		SubBuffer(SubBuffer&&) = delete;
		SubBuffer(const SubBuffer&) = delete;
		SubBuffer& operator=(SubBuffer&&) = delete;
		SubBuffer& operator=(const SubBuffer&) = delete;
	public:
		ANVIL_CALL SubBuffer(Buffer&, size_t, size_t);
		ANVIL_CALL ~SubBuffer();

		Buffer& ANVIL_CALL buffer() throw();

		// Inherited from BufferInterface

		const Context& ANVIL_CALL context() const throw() override;
		ANVIL_CALL operator bool() const throw() override;
		Buffer::AccessMode ANVIL_CALL accessMode() const throw() override;
		size_t ANVIL_CALL origin() const throw() override;
		size_t ANVIL_CALL size() const throw() override;
		void* ANVIL_CALL hostPtr() throw() override;
		const void* ANVIL_CALL hostPtr() const throw() override;
		Event ANVIL_CALL read(CommandQueue&, size_t, void*, size_t) const override;
		Event ANVIL_CALL write(CommandQueue&, size_t, const void*, size_t) override;
		Event ANVIL_CALL copy(CommandQueue&, BufferInterface&, size_t, size_t, size_t) const override;
	};
}}

#endif
