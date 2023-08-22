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

	class Xorwow {
	private:
		uint32_t _seed_0;
		uint32_t _seed_1;
		uint32_t _seed_2;
		uint32_t _seed_3;
		uint32_t _seed_4;
		uint32_t _counter;

	public:
		Xorwow(uint32_t seed0, uint32_t seed1, uint32_t seed2, uint32_t seed3) :
			_seed_0(seed0),
			_seed_1(seed1),
			_seed_2(seed2),
			_seed_3(seed3),
			_seed_4(0u),
			_counter(0u)
		{}

		Xorwow(uint32_t seed) :
			Xorwow(xorshift_32(seed), xorshift_32(seed), xorshift_32(seed), xorshift_32(seed))
		{}

		Xorwow() :
			Xorwow(static_cast<uint32_t>(rand()))
		{}

		ANVIL_STRONG_INLINE uint32_t operator()() {
			uint32_t t = _seed_4;

			uint32_t s = _seed_0;
			_seed_4 = _seed_3;
			_seed_3 = _seed_2;
			_seed_2 = _seed_1;
			_seed_1 = s;

			t ^= t >> 2u;
			t ^= t << 1u;
			t ^= s ^ (s << 4u);
			_seed_0 = t;
			_counter += 362437u;
			return t + _counter;
		}
	};

	class Xorshift32 {
	private:
		uint32_t _seed;
	public:
		Xorshift32(uint32_t seed) :
			_seed(seed)
		{}

		Xorshift32() :
			Xorshift32(static_cast<uint32_t>(rand()))
		{}

		ANVIL_STRONG_INLINE uint32_t operator()() {
			return xorshift_32(_seed);
		}
	};

	class Xorshift64 {
	private:
		uint64_t _seed;
	public:
		Xorshift64(uint64_t seed) :
			_seed(seed)
		{}

		Xorshift64() :
			Xorshift64(static_cast<uint64_t>(rand()) | (static_cast<uint64_t>(rand()) << 32ull))
		{}

		ANVIL_STRONG_INLINE uint64_t operator()() {
			return xorshift_64(_seed);
		}
	};

	class XorshiftStar {
	private:
		uint64_t _seed;
	public:
		XorshiftStar(uint64_t seed) :
			_seed(seed)
		{}

		XorshiftStar() :
			XorshiftStar(static_cast<uint64_t>(rand()) | (static_cast<uint64_t>(rand()) << 32ull))
		{}

		ANVIL_STRONG_INLINE uint64_t operator()() {
			return xorshift_star(_seed);
		}
	};

	class XorshiftPlus {
	private:
		uint64_t _seed[2];
	public:
		XorshiftPlus(uint64_t seed0, uint64_t seed1) :
			_seed{seed0, seed1}
		{}

		XorshiftPlus(uint64_t seed) :
			XorshiftPlus(xorshift_64(seed), xorshift_64(seed))
		{}

		XorshiftPlus() :
			XorshiftPlus(static_cast<uint64_t>(rand()) | (static_cast<uint64_t>(rand()) << 32ull))
		{}

		ANVIL_STRONG_INLINE uint64_t operator()() {
			return xorshift_plus(_seed);
		}
	};
}

#endif