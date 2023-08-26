//Copyright 2023 Adam G. Smith
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

#include "anvil/core/Hash.hpp"

namespace anvil { namespace hash {
	
	enum {
		MURMUR3_32_DEFAULT = static_cast<uint32_t>(('A' << 28ull) | ('N' << 21ull) | ('V' << 14ull) | ('I' << 7ull) | 'L')
	};

	// DJB2

	Murmur3_32::Murmur3_32() :
		_hash(MURMUR3_32_DEFAULT)
	{}

	Murmur3_32::~Murmur3_32() {

	}
	
	static inline uint32_t Murmur32Scramble(uint32_t k) {
		// Adapted from code found @ https://en.wikipedia.org/wiki/MurmurHash
		k *= 0xcc9e2d51u;
		k = (k << 15u) | (k >> 17u);
		k *= 0x1b873593u;
		return k;
	}

	Murmur3_32::hash_t Murmur3_32::Hash(const void* src, size_t bytes) {
		const uint8_t* src8 = static_cast<const uint8_t*>(src);

		// Adapted from code found @ https://en.wikipedia.org/wiki/MurmurHash
		uint32_t k;

		// Read in groups of 4
		for (size_t i = bytes >> 2u; i; i--) {
			// Here is a source of differing results across endiannesses.
			// A swap here has no effects on hash properties though.
			k = *reinterpret_cast<const uint32_t*>(src8);
			src8 += sizeof(uint32_t);
			_hash ^= Murmur32Scramble(k);
			_hash = (_hash << 13u) | (_hash >> 19u);
			_hash = _hash * 5 + 0xe6546b6u;
		}

		// Read the rest
		k = 0;
		for (size_t i = bytes & 3u; i; i--) {
			k <<= 8u;
			k |= src8[i - 1u];
		}

		// A swap is *not* necessary here because the preceding loop already
		// places the low bytes in the low places according to whatever endianness
		// we use. Swaps only apply when the memory is copied in a chunk
		_hash ^= Murmur32Scramble(k);

		// Finalize
		_hash ^= bytes;
		_hash ^= _hash >> 16u;
		_hash *= 0x85ebca6bu;
		_hash ^= _hash >> 13u;
		_hash *= 0xc2b2ae35u;
		_hash ^= _hash >> 16u;

		return _hash;
	}

	void Murmur3_32::Reset() {
		_hash = MURMUR3_32_DEFAULT;
	}

}}