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

#ifndef ANVIL_CORE_LEADING_ZEROS_HPP
#define ANVIL_CORE_LEADING_ZEROS_HPP

#include <cstdint>
#include "anvil/core/Cpu.hpp"
#include "anvil/core/Compiler.hpp"
#include "anvil/core/Keywords.hpp"

#if ANVIL_COMPILER == ANVIL_MSVC
#include  <intrin.h>
#endif

namespace anvil {
#if ANVIL_COMPILER == ANVIL_MSVC
	static ANVIL_STRONG_INLINE size_t ANVIL_CALL leading_zeros(const uint8_t a_value) throw() {
		return __lzcnt16(a_value) - 8;
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL leading_zeros(const uint16_t a_value) throw() {
		return __lzcnt16(a_value);
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL leading_zeros(const uint32_t a_value) throw() {
		return __lzcnt(a_value);
	}

	#if ANVIL_CPU_ARCHITECTURE_BITS >= 64
		static ANVIL_STRONG_INLINE size_t ANVIL_CALL leading_zeros(const uint64_t a_value) throw() {
			return __lzcnt64(a_value);
		}
	#else
		#define ANVIL_NO_LZ_64
	#endif
#elif ANVIL_COMPILER == ANVIL_GCC || ANVIL_COMPILER == ANVIL_CLANG
	static ANVIL_STRONG_INLINE size_t ANVIL_CALL leading_zeros(const uint8_t a_value) throw() {
		return __builtin_clz(a_value) - 24;
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL leading_zeros(const uint16_t a_value) throw() {
		return __builtin_clz(a_value) - 16;
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL leading_zeros(const uint32_t a_value) throw() {
		return __builtin_clz(a_value);
	}

	#define ANVIL_NO_LZ_64
#else
	// Default implementation, using a lookup table to save on processing
	namespace detail {
		static ANVIL_CONSTEXPR_VAR const uint8_t g_leading_zeros_lookup[256] = { 
			8, 7, 6, 6, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4,
			3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
			2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
			2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		};
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL leading_zeros(const uint8_t a_value) throw() {
		return detail::g_leading_zeros_lookup[a_value];
	}

	#define ANVIL_NO_LZ_16
	#define ANVIL_NO_LZ_32
	#define ANVIL_NO_LZ_64
#endif

	#ifdef ANVIL_NO_LZ_16 // Leading zero count was not implemented for 16-bit
		#undef ANVIL_NO_LZ_16
		static ANVIL_STRONG_INLINE size_t ANVIL_CALL leading_zeros(const uint16_t a_value) throw() {
			const uint8_t low = static_cast<uint8_t>(a_value & static_cast<uint16_t>(UINT8_MAX));
			const uint8_t high = static_cast<uint8_t>(a_value >> 8u);
			const size_t tmp = leading_zeros(low);
			if (tmp == 8u) return 8u;

			return 8u + leading_zeros(high);
		}
	#endif

	#ifdef ANVIL_NO_LZ_32 // Leading zero count was not implemented for 32-bit
		#undef ANVIL_NO_LZ_32
		static ANVIL_STRONG_INLINE size_t ANVIL_CALL leading_zeros(const uint32_t a_value) throw() {
			const uint16_t low = static_cast<uint16_t>(a_value & static_cast<uint32_t>(UINT16_MAX));
			const uint16_t high = static_cast<uint16_t>(a_value >> 16u);
			const size_t tmp = leading_zeros(low);
			if (tmp == 16u) return 16u;

			return 16u + leading_zeros(high);
		}
	#endif

	#ifdef ANVIL_NO_LZ_64 // Leading zero count was not implemented for 64-bit
		#undef ANVIL_NO_LZ_64
		static ANVIL_STRONG_INLINE size_t ANVIL_CALL leading_zeros(const uint64_t a_value) throw() {
	#if ANVIL_CPU_ARCHITECTURE_BITS >= 64
			const uint32_t low = static_cast<uint32_t>(a_value & static_cast<uint64_t>(UINT32_MAX));
			const uint32_t high = static_cast<uint32_t>(a_value >> 32ull);
	#else
			const uint32_t low = reinterpret_cast<const uint32_t*>(&a_value)[0u];
			const uint32_t high = reinterpret_cast<const uint32_t*>(&a_value)[1u];
	#endif
			const size_t tmp = leading_zeros(low);
			if (tmp == 32u) return 32u;

			return 32u + leading_zeros(high);
		}
	#endif

	// For signed integers reinterpret the binary data as unsigned and call that implementation instead

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL leading_zeros(const int8_t a_value) throw() {
		union {
			int8_t signed_;
			uint8_t unsigned_;
		};
		signed_ = a_value;
		return leading_zeros(unsigned_);
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL leading_zeros(const int16_t a_value) throw() {
		union {
			int16_t signed_;
			uint16_t unsigned_;
		};
		signed_ = a_value;
		return leading_zeros(unsigned_);
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL leading_zeros(const int32_t a_value) throw() {
		union {
			int32_t signed_;
			uint32_t unsigned_;
		};
		signed_ = a_value;
		return leading_zeros(unsigned_);
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL leading_zeros(const int64_t a_value) throw() {
		union {
			int64_t signed_;
			uint64_t unsigned_;
		};
		signed_ = a_value;
		return leading_zeros(unsigned_);
	}
}

#endif