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

#include "anvil/byte-pipe/BytePipeBits.hpp"

namespace anvil { namespace BytePipe {

	// BitOutputStream

	BitOutputStream::BitOutputStream(uint8_t* o) :
		_out(o),
		_buffer(0u),
		_buffered_bits(0u)
	{}

	void BitOutputStream::Flush() {
		if (_buffered_bits > 0u) {
			*_out = static_cast<uint8_t>(_buffer);
			++_out;
			_buffer = 0u;
			_buffered_bits = 0u;
		}
	}

	void BitOutputStream::_WriteBits(uint32_t bits, size_t bit_count2) {
		ANVIL_DEBUG_ASSERT(bit_count2 <= 32u, "anvil::BytePipe::BitOutputStream::_WriteBits : Bit count is too high");

		uint32_t bit_count = static_cast<uint32_t>(bit_count2);
		while(bit_count > 0u) {
			if (_buffered_bits == 0u) {
				// Write directly to the output
				while (bit_count >= 8u) {
					*_out = static_cast<uint8_t>(bits >> (bit_count - 8u));
					++_out;
					bit_count -= 8u;
					bits &= (1u << bit_count) - 1u;
				}

				// Buffer the remaining bits
				_buffer = bits;
				_buffered_bits = bit_count;
				//bit_count = 0u;
				return;
			} else {
				// We will write as many bits into the buffer as possible
				uint32_t bits_to_write = 8u - _buffered_bits;
				if (bit_count < bits_to_write) bits_to_write = bit_count;

				// Extract the left most bits of the data and add them to the buffer
				uint32_t extracted = bits >> (bit_count - bits_to_write);
				extracted <<= _buffered_bits;
				_buffer |= extracted;
				_buffered_bits += bits_to_write;

				// Flush the buffer
				if (_buffered_bits == 8u) {
					*_out = static_cast<uint8_t>(_buffer);
					++_out;
					_buffer = 0u;
					_buffered_bits = 0u;
				}

				// Remove bits from the data
				bit_count -= bits_to_write;
				bits &= (1u << bit_count) - 1u;
			}
		}
	}

	void BitOutputStream::WriteBits(const uint8_t* src, size_t bit_count) {
		if (_buffered_bits == 0u) {
			enum { WORD_BITS = sizeof(uintptr_t) * 8 };

			while (bit_count >= WORD_BITS) {
				*reinterpret_cast<uintptr_t*>(_out) = *reinterpret_cast<const uintptr_t*>(src);
				src += sizeof(uintptr_t);
				_out += sizeof(uintptr_t);
				bit_count -= WORD_BITS;
			}
			while (bit_count >= 8u) {
				*_out = *src;
				++src;
				++_out;
				bit_count -= 8u;
			}
		}

		while (bit_count >= 32u) {
			_WriteBits(*reinterpret_cast<const uint32_t*>(src), 32u);
			src += 4u;
			bit_count -= 32u;
		}

		while (bit_count >= 8u) {
			_WriteBits(*src, 8u);
			++src;
			bit_count -= 8u;
		}

		if (bit_count > 0u) _WriteBits(*src, bit_count);
	}

	void BitOutputStream::WriteBits(const uintptr_t bits, size_t bit_count) {
		_WriteBits(static_cast<uint32_t>(bits), bit_count);
		if ANVIL_CONSTEXPR_VAR(sizeof(uintptr_t) > sizeof(uint32_t)) {
			if (bit_count > 32u) {
				_WriteBits(static_cast<uint32_t>(static_cast<uint64_t>(bits) >> 32ull), bit_count - 32u);
			}
		}
	}

	// BitInputStream

	void BitInputStream::BufferNextByte() {
		_buffer <<= 8u;
		_buffer |= *_in;
		++_in;
		_buffered_bits += 8u;
	}

	uint32_t BitInputStream::_ReadBits(size_t bit_count) {
		uint32_t bits = 0u;
		uint32_t offset = 0u;

		while (bit_count > 0u) {
			if (_buffered_bits == 0u) BufferNextByte();

			if (bit_count >= _buffered_bits) {
				bits |= _buffer << offset;
				bit_count -= _buffered_bits;
				offset += _buffered_bits;
				_buffer = 0u;
				_buffered_bits = 0u;
			} else {
				// Extract the right most bits from the buffer
				uint32_t extracted = _buffer & ((1u << bit_count) - 1u);
				bits |= extracted << offset;
				_buffer >>= bit_count;
				_buffered_bits -= static_cast<uint32_t>(bit_count);
				bit_count = 0u;
			}
		}

		return bits;
	}

	BitInputStream::BitInputStream(const uint8_t* i) :
		_in(i),
		_buffer(0u),
		_buffered_bits(0u)
	{}

	void BitInputStream::ReadBits(uint8_t* dst, size_t bit_count) {
		if (_buffered_bits == 0u) {
			enum { WORD_BITS = sizeof(uintptr_t) * 8 };
			while (bit_count >= WORD_BITS) {
				*reinterpret_cast<uintptr_t*>(dst) = *reinterpret_cast<const uintptr_t*>(_in);
				bit_count -= WORD_BITS;
				dst += sizeof(uintptr_t);
				_in += sizeof(uintptr_t);
			}

			while (bit_count >= 8u) {
				*dst = *_in;
				bit_count -= 8u;
				++dst;
				++_in;
			}
		}

		while (bit_count >= 32u) {
			*dst = static_cast<uint8_t>(_ReadBits(32u));
			dst += 4u;
			bit_count -= 32u;
		}

		while (bit_count >= 8u) {
			*dst = static_cast<uint8_t>(_ReadBits(8u));
			++dst;
			bit_count -= 8u;
		}

		if (bit_count > 0u) {
			*dst = static_cast<uint8_t>(_ReadBits(bit_count));
			++dst;
		}
	}

}}