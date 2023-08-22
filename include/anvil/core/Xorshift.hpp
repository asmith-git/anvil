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

	struct Xorwow {
		uint32_t x_0;
		uint32_t x_1;
		uint32_t x_2;
		uint32_t x_3;
		uint32_t x_4;
		uint32_t counter;

		Xorwow(uint32_t seed) :
			x_0(seed),
			x_1(xorshift_32(seed)),
			x_2(xorshift_32(seed)),
			x_3(xorshift_32(seed)),
			x_4(xorshift_32(seed)),
			counter(0u)
		{}

		Xorwow() :
			Xorwow(static_cast<uint32_t>(rand()))
		{}

		ANVIL_STRONG_INLINE uint32_t operator()() {
			uint32_t t = x_4;

			uint32_t s = x_0;
			x_4 = x_3;
			x_3 = x_2;
			x_2 = x_1;
			x_1 = s;

			t ^= t >> 2u;
			t ^= t << 1u;
			t ^= s ^ (s << 4u);
			x_0 = t;
			counter += 362437u;
			return t + counter;
		}
	};
}

#endif