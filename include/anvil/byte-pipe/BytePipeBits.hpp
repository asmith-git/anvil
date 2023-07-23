//Copyright 2021 Adam G. Smith
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

#ifndef ANVIL_LUTILS_BYTEPIPE_BITSTREAM_HPP
#define ANVIL_LUTILS_BYTEPIPE_BITSTREAM_HPP

#include "anvil/byte-pipe/BytePipeCore.hpp"

namespace anvil { namespace BytePipe {

	struct ANVIL_DLL_EXPORT BitOutputStream {
	private:
		uint8_t* _out;				//!< The location that the next complete byte will be written to
		uint32_t _buffer;			//!< The bits that were leftover from the last write
		uint32_t _buffered_bits;	//!< How many bits were leftover from the last write
	private:
		void _WriteBits(const uint32_t bits, size_t bit_count);
	public:
		BitOutputStream(uint8_t* o);

		void WriteBits(const uint8_t* src, size_t bit_count);
		void WriteBits(const uintptr_t bits, size_t bit_count);

		void Flush();
	};

	struct ANVIL_DLL_EXPORT BitInputStream {
	private:
		const uint8_t* _in;			//!< The location that the next byte will be read from
		uint32_t _buffer;			//!< The bits that were leftover from the last read
		uint32_t _buffered_bits;	//!< How many bits were leftover from the last read

		void BufferNextByte();
		uint32_t _ReadBits(size_t bit_count);
	public:
		BitInputStream(const uint8_t* i);
		void ReadBits(uint8_t* dst, size_t bit_count);

		ANVIL_STRONG_INLINE uintptr_t ReadBits(size_t bit_count) {
			ANVIL_DEBUG_ASSERT(bit_count <= (sizeof(uintptr_t) * 8u), "anvil::BytePipe::BitInputStream::ReadBits : Bit count is too high");
			uintptr_t tmp = 0u;
			ReadBits(reinterpret_cast<uint8_t*>(&tmp), bit_count);
			return tmp;
		}
	};


}}

#endif
