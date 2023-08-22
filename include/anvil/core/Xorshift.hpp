//Copyright 2016 Adam G. Smith
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

#ifndef ANVIL_CORE_XORSHIFt_HPP
#define ANVIL_CORE_XORSHIFt_HPP

#include "Keywords.hpp"

namespace anvil {

	static ANVIL_STRONG_INLINE uint32_t xorshift_32(uint32_t& seed) {
		seed ^= seed << 13;
		seed ^= seed >> 17;
		seed ^= seed << 5;
		return seed;
	}

	static ANVIL_STRONG_INLINE uint64_t xorshift_star(uint64_t& seed) {
		seed ^= seed >> 12L;
		seed ^= seed << 25L;
		seed ^= seed >> 27L;
		return seed * 2685821657736338717L;
	}

	static ANVIL_STRONG_INLINE uint64_t xorshift_plus(uint64_t* seed) {
		uint64_t x = seed[0];
		uint64_t const y = seed[1];
		seed[0] = y;
		x ^= x << 23L;
		seed[1] = x ^ y ^ (x >> 17L) ^ (y >> 26L);
		return seed[1] + y;
	}
}

#endif