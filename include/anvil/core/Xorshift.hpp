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
		seed ^= seed << 13u;
		seed ^= seed >> 17u;
		seed ^= seed << 5u;
		return seed;
	}

	static ANVIL_STRONG_INLINE uint64_t xorshift_64(uint64_t& seed) {
		seed ^= seed << 13ull;
		seed ^= seed >> 7ull;
		seed ^= seed << 17ull;
		return seed;
	}

	static ANVIL_STRONG_INLINE uint64_t xorshift_star(uint64_t& seed) {
		seed ^= seed >> 12ull;
		seed ^= seed << 25ull;
		seed ^= seed >> 27ull;
		return seed * 2685821657736338717ull;
	}

	static ANVIL_STRONG_INLINE uint64_t xorshift_plus(uint64_t* seed) {
		uint64_t x = seed[0];
		uint64_t const y = seed[1];
		seed[0] = y;
		x ^= x << 23ull;
		seed[1] = x ^ y ^ (x >> 17ull) ^ (y >> 26ull);
		return seed[1] + y;
	}
}

#endif