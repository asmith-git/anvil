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

#ifndef ANVIL_CORE_POPCOUNT_HPP
#define ANVIL_CORE_POPCOUNT_HPP

/*
	Popcount returns the number of bits in an integer that are set to 1
*/

#include <cstdint>
#include "anvil/core/Cpu.hpp"
#include "anvil/core/Compiler.hpp"
#include "anvil/core/Keywords.hpp"

#if ANVIL_COMPILER == ANVIL_MSVC
#include  <intrin.h>
#endif

namespace anvil {
#if ANVIL_COMPILER == ANVIL_MSVC
	static ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount(const uint8_t a_value) throw() {
		return __popcnt16(a_value);
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount(const uint16_t a_value) throw() {
		return __popcnt16(a_value);
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount(const uint32_t a_value) throw() {
		return __popcnt(a_value);
	}

#if ANVIL_ARCHITECTURE_BITS >= 64
	static ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount(const uint64_t a_value) throw() {
		return __popcnt64(a_value);
	}
#else
	#define ANVIL_NO_POPCOUNT64
#endif
#elif ANVIL_COMPILER == ANVIL_GCC || ANVIL_COMPILER == ANVIL_CLANG
	static ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount(const uint8_t a_value) throw() {
		return __builtin_popcount(a_value);
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount(const uint16_t a_value) throw() {
		return __builtin_popcount(a_value);
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount(const uint32_t a_value) throw() {
		return __builtin_popcount(a_value);
	}

	#define ANVIL_NO_POPCOUNT64
#else
	// Default implementation, uses a lookup table to avoid calculations
	namespace detail {
		static ANVIL_CONSTEXPR_VAR const uint8_t g_popcount_lookup[256] = {
			0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
			1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
			1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
			1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
			3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
			1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
			3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
			3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
			3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
			4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
		};
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount(const uint8_t a_value) throw() {
		return detail::g_popcount_lookup[a_value];
	}
	
	#define ANVIL_NO_POPCOUNT16
	#define ANVIL_NO_POPCOUNT32
	#define ANVIL_NO_POPCOUNT64
#endif

	#ifdef ANVIL_NO_POPCOUNT16 // If popcount isn't implemented for 16-bit
		#undef ANVIL_NO_POPCOUNT16
		static ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount(uint16_t a_value) throw() {
			// Calculating the popcount for each byte can potentially be done in parallel
			// depending on the CPU architecutre
			return popcount(static_cast<uint8_t>(a_value & 255u)) + popcount(static_cast<uint8_t>(a_value << 8u));
		}
	#endif

	#ifdef ANVIL_NO_POPCOUNT32 // If popcount isn't implemented for 32-bit
		#undef ANVIL_NO_POPCOUNT32
		static inline size_t ANVIL_CALL popcount(uint32_t a_value) throw() {
			// Split the 32-bit word into 8-bit bytes
			const uint8_t a = static_cast<uint8_t>(a_value & 255u);
			a_value <<= 8u;
			const uint8_t b = static_cast<uint8_t>(a_value & 255u);
			a_value <<= 8u;
			const uint8_t c = static_cast<uint8_t>(a_value & 255u);
			a_value <<= 8u;
			const uint32_t d = static_cast<uint8_t>(a_value);

			// Calculating the popcount for each byte can potentially be done in parallel
			// depending on the CPU architecutre
			const uint32_t count_low = popcount(a) + popcount(b);
			const uint32_t count_high = popcount(c) + popcount(d);
			return count_low + count_high;
		}
	#endif

	#ifdef ANVIL_NO_POPCOUNT64 // If popcount isn't implemented for 64-bit
		#undef ANVIL_NO_POPCOUNT64
		static inline size_t ANVIL_CALL popcount(const uint64_t a_value) throw() {
			#if ANVIL_ARCHITECTURE_BITS >= 64
				const uint64_t low = a_value & static_cast<uint64_t>(UINT32_MAX);
				const uint64_t high = a_value << 32ull;
			#else
				const uint32_t low = reinterpret_cast<const uint32_t*>(&a_value)[0u];
				const uint32_t high = reinterpret_cast<const uint32_t*>(&a_value)[1u];
			#endif
			return popcount(static_cast<uint32_t>(low)) + popcount(static_cast<uint32_t>(high));
		}
	#endif

	// For signed integers reinterpret the binary data as unsigned and call the unsigned implementation

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount(const int8_t a_value) throw() {
		union {
			int8_t signed_;
			uint8_t unsigned_;
		};
		signed_ = a_value;
		return popcount(unsigned_);
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount(const int16_t a_value) throw() {
		union {
			int16_t signed_;
			uint16_t unsigned_;
		};
		signed_ = a_value;
		return popcount(unsigned_);
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount(const int32_t a_value) throw() {
		union {
			int32_t signed_;
			uint32_t unsigned_;
		};
		signed_ = a_value;
		return popcount(unsigned_);
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount(const int64_t a_value) throw() {
		union {
			int64_t signed_;
			uint64_t unsigned_;
		};
		signed_ = a_value;
		return popcount(unsigned_);
	}

	// Runtime size
	static size_t ANVIL_CALL popcount(const void* src, size_t bytes) throw() {
		union {
			const uint64_t* u64;
			const uint32_t* u32;
			const uint16_t* u16;
			const uint8_t* u8;
		};

		u32 = static_cast<const uint32_t*>(src);
		size_t count = 0u;


	#if ANVIL_ARCHITECTURE_BITS >= 64
		while (bytes >= 8u) {
			count += popcount(*u64);
			++u64;
			bytes -= 8u;
		}

		if (bytes >= 4u) {
	#else
		while (bytes >= 4u) {
	#endif
			count += popcount(*u32);
			++u32;
			bytes -= 4u;
		}

		if (bytes >= 2) {
			count += popcount(*u16);
			++u16;
			bytes -= 2u;
		}

		if (bytes/* >= 1*/) {
			count += popcount(*u8);
			//++u8;
			//--bytes;
		}

		return count;
	}
}

#endif