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
#endif

namespace anvil {

#if ANVIL_COMPILER == ANVIL_MSVC
	#define ANVIL_POPCOUNT __popcnt
	#define ANVIL_POPCOUNT_TYPE int32_t
#elif ANVIL_COMPILER == ANVIL_GCC ||  ANVIL_COMPILER == ANVIL_CLANG
#define ANVIL_POPCOUNT __builtin_popcount
#define ANVIL_POPCOUNT_TYPE uint32_t
#else
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

	typedef uint8_t ANVIL_POPCOUNT_TYPE;

	ANVIL_STRONG_INLINE size_t ANVIL_CALL ANVIL_POPCOUNT(ANVIL_POPCOUNT_TYPE aByte) throw() {
		return gPopcountLookup[aByte];
	}
#endif

	size_t ANVIL_CALL popcount(const uint8_t aValue) throw() {
		return ANVIL_POPCOUNT(aValue);
	}

	size_t ANVIL_CALL popcount(const uint16_t aValue) throw() {
		if (sizeof(ANVIL_POPCOUNT_TYPE) >= 2) {
			return ANVIL_POPCOUNT(aValue);
		} else {
			return popcount(static_cast<uint8_t>(aValue >> 8)) + (popcount(static_cast<uint8_t>(aValue & UINT8_MAX)) << 8);
		}
	}

	size_t ANVIL_CALL popcount(const uint32_t aValue) throw() {
		if (sizeof(ANVIL_POPCOUNT_TYPE) >= 4) {
			return ANVIL_POPCOUNT(aValue);
		} else {
			return popcount(static_cast<uint16_t>(aValue >> 16)) + (popcount(static_cast<uint16_t>(aValue & UINT16_MAX)) << 16);
		}
	}

	size_t ANVIL_CALL popcount(const uint64_t aValue) throw() {
		return uint64_t(popcount(static_cast<uint32_t>(aValue >> 32ULL))) + (uint64_t(popcount(static_cast<uint32_t>(aValue & UINT32_MAX))) << 32ULL);
	}

	size_t ANVIL_CALL popcount(const int8_t aValue) throw() {
		return static_cast<int8_t>(popcount(static_cast<uint8_t>(aValue)));
	}

	size_t ANVIL_CALL popcount(const int16_t aValue) throw() {
		return static_cast<int16_t>(popcount(static_cast<uint16_t>(aValue)));
	}

	size_t ANVIL_CALL popcount(const int32_t aValue) throw() {
		return static_cast<int32_t>(popcount(static_cast<uint32_t>(aValue)));
	}

	size_t ANVIL_CALL popcount(const int64_t aValue) throw() {
		return static_cast<int64_t>(popcount(static_cast<uint64_t>(aValue)));
	}

	size_t ANVIL_CALL popcount(const void* aSrc, size_t aBytes) throw() {
		size_t count = 0;
		
		const ANVIL_POPCOUNT_TYPE* src = static_cast<const ANVIL_POPCOUNT_TYPE*>(aSrc);
		while (aBytes >= sizeof(ANVIL_POPCOUNT_TYPE)) {
			count += ANVIL_POPCOUNT(*src);
			aBytes -= sizeof(ANVIL_POPCOUNT_TYPE);
			++src;
		}

		const uint8_t* src8 = reinterpret_cast<const uint8_t*>(src);
		while (aBytes > 0) {
			count += ANVIL_POPCOUNT(*src8);
			--aBytes;
			++src8;
		}
		return count;
	}

}