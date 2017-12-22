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
	#define ANVIL_POPCOUNT8 __popcnt16
	#define ANVIL_POPCOUNT16 __popcnt16
	#define ANVIL_POPCOUNT32 __popcnt
	#if ANVIL_ARCHITECTURE_BITS >= 64
		#define ANVIL_POPCOUNT64 __popcnt64
	#endif
#elif ANVIL_COMPILER == ANVIL_GCC ||  ANVIL_COMPILER == ANVIL_CLANG
	#define ANVIL_POPCOUNT8 __builtin_popcount
	#define ANVIL_POPCOUNT16 __builtin_popcount
	#define ANVIL_POPCOUNT32 __builtin_popcount
	#if ANVIL_ARCHITECTURE_BITS >= 64
		#define ANVIL_POPCOUNT64 __builtin_popcountll
	#endif
#endif

#ifndef ANVIL_POPCOUNT8
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

	size_t ANVIL_CALL popcount1(const uint8_t aValue) throw() {
		return ANVIL_POPCOUNT8(aValue);
	}

	size_t ANVIL_CALL popcount2(const uint16_t aValue) throw() {
#ifdef ANVIL_POPCOUNT16
		return ANVIL_POPCOUNT16(aValue);
#else
		return popcount(&aValue, sizeof(aValue));
#endif
	}

	size_t ANVIL_CALL popcount4(const uint32_t aValue) throw() {
#ifdef ANVIL_POPCOUNT32
		return ANVIL_POPCOUNT32(aValue);
#else
		return popcount(&aValue, sizeof(aValue));
#endif
	}

	size_t ANVIL_CALL popcount8(const uint64_t aValue) throw() {
#ifdef ANVIL_POPCOUNT64
		return ANVIL_POPCOUNT64(aValue);
#else
		return popcount(&aValue, sizeof(aValue));
#endif
	}

	}

	size_t ANVIL_CALL popcount(const void* aSrc, size_t aBytes) throw() {
		size_t count = 0;

#ifdef ANVIL_POPCOUNT64
		{
			const uint64_t* src64 = static_cast<const uint64_t*>(aSrc);
			while (aBytes >= 8) {
				count += ANVIL_POPCOUNT64(*src64);
				aBytes -= 8;
				++src64;
			}
			aSrc = src64;
		}
#endif
#ifdef ANVIL_POPCOUNT32
		{
			const uint32_t* src32 = static_cast<const uint32_t*>(aSrc);
			while (aBytes >= 4) {
				count += ANVIL_POPCOUNT32(*src32);
				aBytes -= 4;
				++src32;
			}
			aSrc = src32;
		}
#endif
#ifdef ANVIL_POPCOUNT16
		{
			const uint16_t* src16 = static_cast<const uint16_t*>(aSrc);
			while (aBytes >= 2) {
				count += ANVIL_POPCOUNT16(*src16);
				aBytes -= 2;
				++src16;
			}
			aSrc = src16;
		}
#endif
		const uint8_t* src8 = static_cast<const uint8_t*>(aSrc);
		while (aBytes > 0) {
			count += ANVIL_POPCOUNT8(*src8);
			--aBytes;
			++src8;
		}
		aSrc = src8;
		return count;
	}

}