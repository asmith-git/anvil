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

#if ANVIL_ARCHITECTURE_BITS == 64
	static ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount(const uint64_t a_value) throw() {
		return __popcnt64(a_value);
	}
#else
	static ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount(const uint64_t a_value) throw() {
		union {
			uint64_t value;
			uint32_t split[2];
		};
		value = a_value;
		return __popcnt(split[0]) + __popcnt(split[1]);
	}
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

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount(const uint64_t a_value) throw() {
		union {
			uint64_t value;
			uint32_t split[2];
		};
		value = a_value;
		return __builtin_popcount(split[0]) + __builtin_popcount(split[1]);
	}
#else
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

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount(const uint16_t a_value) throw() {
		union {
			uint16_t value;
			uint8_t split[2];
		};
		value = a_value;
		return detail::g_popcount_lookup[split[0]] + detail::g_popcount_lookup[split[1]];
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount(const uint32_t a_value) throw() {
		union {
			uint32_t value;
			uint8_t split[4];
		};
		value = a_value;
		return detail::g_popcount_lookup[split[0]] + detail::g_popcount_lookup[split[1]] + detail::g_popcount_lookup[split[2]] +detail::g_popcount_lookup[split[3]];
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount(const uint64_t a_value) throw() {
		union {
			uint64_t value;
			uint8_t split[8];
		};
		value = a_value;
		return detail::g_popcount_lookup[split[0]] + detail::g_popcount_lookup[split[1]] + detail::g_popcount_lookup[split[2]] + detail::g_popcount_lookup[split[3]] +
			detail::g_popcount_lookup[split[4]] + detail::g_popcount_lookup[split[5]] + detail::g_popcount_lookup[split[6]] + detail::g_popcount_lookup[split[7]];
	}
#endif

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

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount(const float a_value) throw() {
		union {
			float float_;
			uint32_t unsigned_;
		};
		float_ = a_value;
		return popcount(unsigned_);
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount(const double a_value) throw() {
		union {
			double float_;
			uint64_t unsigned_;
		};
		float_ = a_value;
		return popcount(unsigned_);
	}
}

#endif