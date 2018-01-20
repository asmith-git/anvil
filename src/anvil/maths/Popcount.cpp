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

#include "anvil/maths/Popcount.hpp"
#include "anvil/Core/Compiler.hpp"
#if ANVIL_COMPILER == ANVIL_MSVC
#include <intrin.h>  
#include "anvil/Core/Cpu.hpp"
#endif

namespace anvil {
	namespace detail {
#if ANVIL_COMPILER == ANVIL_MSVC
	#define ANVIL_POPCOUNT16 __popcnt16
	#define ANVIL_POPCOUNT32 __popcnt
	#if ANVIL_ARCHITECTURE_BITS >= 64
		#define ANVIL_POPCOUNT64 __popcnt64
	#endif
#elif ANVIL_COMPILER == ANVIL_GCC ||  ANVIL_COMPILER == ANVIL_CLANG
	#define ANVIL_POPCOUNT32 __builtin_popcount
	#if ANVIL_ARCHITECTURE_BITS >= 64
		#define ANVIL_POPCOUNT64 __builtin_popcountll
	#endif
#endif

#if !(defined(ANVIL_POPCOUNT64) || defined(ANVIL_POPCOUNT32) || defined(ANVIL_POPCOUNT16) || defined(ANVIL_POPCOUNT8))
	ANVIL_CONSTEXPR_VAR const uint8_t gPopcountLookup[256]{
		0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,
		1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
		1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
		2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
		1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
		2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
		2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
		3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
		1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
		2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
		2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
		3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
		2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
		3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
		3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
		4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8
	};
	#define ANVIL_POPCOUNT8(aByte) gPopcountLookup[aByte]
#endif

	size_t ANVIL_CALL popcount8(const uint8_t aValue) throw() {
#if defined(ANVIL_POPCOUNT8)
	return ANVIL_POPCOUNT8(aValue);
#elif defined(ANVIL_POPCOUNT16)
	return ANVIL_POPCOUNT16(aValue);
#elif defined(ANVIL_POPCOUNT32)
	return ANVIL_POPCOUNT32(aValue);
#elif defined(ANVIL_POPCOUNT64)
	return ANVIL_POPCOUNT64(aValue);
#else
	#error No popcount implementation defined
#endif
	}

	union PopcountHelper {
		struct {
			uint8_t u8_0;
			uint8_t u8_1;
			uint8_t u8_2;
			uint8_t u8_3;
			uint8_t u8_4;
			uint8_t u8_5;
			uint8_t u8_6;
			uint8_t u8_7;
		};
		struct {
			uint16_t u16_0;
			uint16_t u16_1;
			uint16_t u16_2;
			uint16_t u16_3;
		};
		struct {
			uint32_t u32_0;
			uint32_t u32_1;
		};
		uint64_t u64;
	};

	size_t ANVIL_CALL popcount16(const uint16_t aValue) throw() {
#if defined(ANVIL_POPCOUNT8)
		detail::PopcountHelper tmp;
		tmp.u16_0 = aValue;
		return ANVIL_POPCOUNT8(tmp.u8_0) + ANVIL_POPCOUNT8(tmp.u8_1);
#elif defined(ANVIL_POPCOUNT16)
		return ANVIL_POPCOUNT16(aValue);
#elif defined(ANVIL_POPCOUNT32)
		return ANVIL_POPCOUNT32(aValue);
#elif defined(ANVIL_POPCOUNT64)
		return ANVIL_POPCOUNT64(aValue);
#else
	#error No popcount implementation defined
#endif
	}

	size_t ANVIL_CALL popcount32(const uint32_t aValue) throw() {
#if defined(ANVIL_POPCOUNT32)
		return ANVIL_POPCOUNT32(aValue);
#elif defined(ANVIL_POPCOUNT64)
		return ANVIL_POPCOUNT64(aValue);
#elif defined(ANVIL_POPCOUNT16)
		detail::PopcountHelper tmp;
		tmp.u32_0 = aValue;
		return ANVIL_POPCOUNT16(tmp.u16_0) + ANVIL_POPCOUNT8(tmp.u16_1);
#elif defined(ANVIL_POPCOUNT8)
		detail::PopcountHelper tmp;
		tmp.u64 = 0;
		tmp.u32_0 = aValue;
		return ANVIL_POPCOUNT8(tmp.u8_0) + ANVIL_POPCOUNT8(tmp.u8_1) + ANVIL_POPCOUNT8(tmp.u8_3) + ANVIL_POPCOUNT8(tmp.u8_4);
#else
	#error No popcount implementation defined
#endif
	}

	size_t ANVIL_CALL popcount64(const uint64_t aValue) throw() {
#if defined(ANVIL_POPCOUNT64)
	return ANVIL_POPCOUNT64(aValue);
#elif defined(ANVIL_POPCOUNT32)
		detail::PopcountHelper tmp;
		tmp.u64 = aValue;
		return ANVIL_POPCOUNT32(tmp.u32_0) + ANVIL_POPCOUNT32(tmp.u32_1);
#elif defined(ANVIL_POPCOUNT16)
		detail::PopcountHelper tmp;
		tmp.u64 = aValue;
		return ANVIL_POPCOUNT16(tmp.u16_0) + ANVIL_POPCOUNT16(tmp.u16_1) + ANVIL_POPCOUNT16(tmp.u16_2) + ANVIL_POPCOUNT16(tmp.u16_3);
#elif defined(ANVIL_POPCOUNT8)
		detail::PopcountHelper tmp;
		tmp.u64 = aValue;
		return ANVIL_POPCOUNT8(tmp.u8_0) + ANVIL_POPCOUNT8(tmp.u8_1) + ANVIL_POPCOUNT8(tmp.u8_2) + ANVIL_POPCOUNT8(tmp.u8_3) +
			ANVIL_POPCOUNT8(tmp.u8_4) + ANVIL_POPCOUNT8(tmp.u8_5) + ANVIL_POPCOUNT8(tmp.u8_6) + ANVIL_POPCOUNT8(tmp.u8_7);
#else
	#error No popcount implementation defined
#endif
	}

	}

	size_t ANVIL_CALL popcount(const void* aSrc, size_t aBytes) throw() {
		union {
			const void* ptr;
			const uint8_t* ptr8;
			const uint16_t* ptr16;
			const uint32_t* ptr32;
			const uint64_t* ptr64;
		};
		ptr = aSrc;

		size_t count = 0;
		size_t remainder;
		
#ifdef ANVIL_POPCOUNT64
		remainder = aBytes & 7;
		aBytes /= 8;
		for (size_t i = 0; i < aBytes; ++i) count += ANVIL_POPCOUNT64(ptr64[i]);
		ptr64 += aBytes;
		if (remainder == 0) return count;
		aBytes = remainder;
#endif
#ifdef ANVIL_POPCOUNT32
		remainder = aBytes & 3;
		aBytes /= 4;
		for (size_t i = 0; i < aBytes; ++i) count += ANVIL_POPCOUNT32(ptr32[i]);
		ptr32 += aBytes;
		if (remainder == 0) return count;
		aBytes = remainder;
#endif
#ifdef ANVIL_POPCOUNT16
		remainder = aBytes & 1;
		aBytes /= 2;
		for (size_t i = 0; i < aBytes; ++i) count += ANVIL_POPCOUNT16(ptr16[i]);
		ptr16 += aBytes;
		if (remainder == 0) return count;
		aBytes = remainder;
#endif
		for(size_t i = 0; i < aBytes; ++i) {
			count += detail::popcount8(ptr8[i]);
		}
		return count;
	}

}