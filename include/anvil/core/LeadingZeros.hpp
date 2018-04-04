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

#if ANVIL_ARCHITECTURE_BITS == 64
	static ANVIL_STRONG_INLINE size_t ANVIL_CALL leading_zeros(const uint64_t a_value) throw() {
		return __lzcnt64(a_value);
	}
#else
	static ANVIL_STRONG_INLINE size_t ANVIL_CALL leading_zeros(const uint64_t a_value) throw() {
		union {
			uint64_t value;
			uint32_t split[2];
		};
		value = a_value;
		const size_t tmp = __lzcnt(split[0]);
		return tmp == 32 ? 32 + __lzcnt(split[1]) : tmp;
	}
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

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL leading_zeros(const uint64_t a_value) throw() {
		union {
			uint64_t value;
			uint32_t split[2];
		};
		value = a_value;
		const size_t tmp = __builtin_clz(split[0]);
		return tmp == 32 ? 32 + __builtin_clz(split[1]) : tmp;
	}
#else
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

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL leading_zeros(const uint16_t a_value) throw() {
		union {
			uint16_t value;
			uint8_t split[2];
		};
		value = a_value;
		const size_t tmp = detail::g_leading_zeros_lookup[split[0]];
		return tmp == 8 ? 8 + detail::g_leading_zeros_lookup[split[1]] : tmp;
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL leading_zeros(const uint32_t a_value) throw() {
		union {
			uint32_t value;
			uint8_t split[4];
		};
		value = a_value;
		size_t tmp = detail::g_leading_zeros_lookup[split[0]];
		if (tmp != 8) return tmp;
		tmp = detail::g_leading_zeros_lookup[split[1]];
		if (tmp != 8) return 8 + tmp;
		tmp = detail::g_leading_zeros_lookup[split[2]];
		if (tmp != 8) return 16 + tmp;
		tmp = detail::g_leading_zeros_lookup[split[3]];
		return 24 + tmp;
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL leading_zeros(const uint64_t a_value) throw() {
		union {
			uint64_t value;
			uint8_t split[8];
		};
		value = a_value;
		size_t tmp = detail::g_leading_zeros_lookup[split[0]];
		if (tmp != 8) return tmp;
		tmp = detail::g_leading_zeros_lookup[split[1]];
		if (tmp != 8) return 8 + tmp;
		tmp = detail::g_leading_zeros_lookup[split[2]];
		if (tmp != 8) return 16 + tmp;
		tmp = detail::g_leading_zeros_lookup[split[3]];
		if (tmp != 8) return 24 + tmp;
		tmp = detail::g_leading_zeros_lookup[split[4]];
		if (tmp != 8) return 32 + tmp;
		tmp = detail::g_leading_zeros_lookup[split[5]];
		if (tmp != 8) return 40 + tmp;
		tmp = detail::g_leading_zeros_lookup[split[6]];
		if (tmp != 8) return 48 + tmp;
		tmp = detail::g_leading_zeros_lookup[split[7]];
		return 56 + tmp;
	}
#endif

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

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL leading_zeros(const float a_value) throw() {
		union {
			float float_;
			uint32_t unsigned_;
		};
		float_ = a_value;
		return leading_zeros(unsigned_);
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL leading_zeros(const double a_value) throw() {
		union {
			double float_;
			uint64_t unsigned_;
		};
		float_ = a_value;
		return leading_zeros(unsigned_);
	}
}

#endif