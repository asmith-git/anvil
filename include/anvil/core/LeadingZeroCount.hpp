//Copyright 2022 Adam G. Smith
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

#ifndef ANVIL_CORE_LZCOUNT_HPP
#define ANVIL_CORE_LZCOUNT_HPP

/*
	lzcount Count then number of leading zero bits
*/

#include "anvil/core/Keywords.hpp"

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
	#include <immintrin.h>
	#include <intrin.h>
#endif

#include "CpuRuntime.hpp"

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
	static_assert(anvil::ASM_BMI1 == (1ull << 62ul), "BMI1 check is using the wrong value");
	#if ANVIL_MIN_INSTRUCTION_SET & (1ull << 62ul)
		#define ANVIL_HW_LZCNTA false
		#define ANVIL_HW_LZCNTB true
	#else
		#define ANVIL_HW_LZCNTA true
		#define ANVIL_HW_LZCNTB anvil::AreInstructionSetSupported(anvil::ASM_BMI1)
	#endif
#else
	#define ANVIL_HW_LZCNTA false
	#define ANVIL_HW_LZCNTB false
#endif

namespace anvil { namespace detail {

	// Using BSR instruction

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount8_hwa(uint8_t aValue) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		if (aValue == 0u) return 8u;
		unsigned long idx = 0;

		// Mask so only the least signficant bit remains
		uint32_t val32 = aValue;
		val32 &= val32 ^ (val32 - 1u);

		// Find the most significant bit
		_BitScanReverse(&idx, val32);

		return idx;
#else
		return 0;
#endif
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount16_hwa(uint16_t aValue) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		if (aValue == 0u) return 16u;
		unsigned long idx = 0;

		// Mask so only the least signficant bit remains
		uint32_t val32 = aValue;
		val32 &= val32 ^ (val32 - 1u);

		// Find the most significant bit
		_BitScanReverse(&idx, val32);

		return idx;
#else
		return 0;
#endif
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount32_hwa(uint32_t aValue) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		if (aValue == 0u) return 32u;
		unsigned long idx = 0;
		
		// Mask so only the least signficant bit remains
		aValue &= aValue ^ (aValue - 1u);

		// Find the most significant bit
		_BitScanReverse(&idx, aValue);

		return idx;
#else
		return 0;
#endif
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount64_hwa(uint64_t aValue) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		if (aValue == 0u) return 64u;
		unsigned long idx = 0;

		// Mask so only the least signficant bit remains
		aValue &= aValue ^ (aValue - 1ull);

		// Find the most significant bit
		_BitScanReverse64(&idx, aValue);

		return idx;
#elif ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86
		size_t count = lzcount32_hwa(static_cast<uint32_t>(aValue & UINT32_MAX));
		if (count == 32u) count += lzcount32_hwa(static_cast<uint32_t>(aValue >> 32ull));
		return count;
#else
		return 0;
#endif
	}

	// Using LZCNT instruction

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount8_hwb(uint8_t aValue) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		if (aValue == 0u) return 8u;
		return __lzcnt16(aValue);
#else
		return 0;
#endif
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount16_hwb(uint16_t aValue) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		if (aValue == 0u) return 16u;
		return __lzcnt16(aValue);
#else
		return 0;
#endif
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount32_hwb(uint32_t aValue) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		if (aValue == 0u) return 32u;
        #if ANVIL_COMPILER == ANVIL_MSVC
            return __lzcnt(aValue);
        #else
            return _lzcnt_u32(aValue);
		#endif
#else
		return 0;
#endif
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount64_hwb(uint64_t aValue) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		if (aValue == 0u) return 64u;
		return __lzcnt64(aValue);
#elif ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86
		size_t count = lzcount32_hw(static_cast<uint32_t>(aValue & UINT32_MAX));
		if (count == 32u) count += lzcount32_hw(static_cast<uint32_t>(aValue >> 32ull));
		return count;
#else
		return 0;
#endif
	}

	static size_t ANVIL_CALL lzcount8_c(uint8_t aValue) throw() {
		uint32_t x = aValue;
		uint32_t found1;
		uint32_t count = 0u;

		found1 = x & 1u;
		count += found1 ^ 1u;
		x >>= 1u;

		found1 = found1 | (x & 1u);
		count += found1 ^ 1u;
		x >>= 1u;

		found1 = found1 | (x & 1u);
		count += found1 ^ 1u;
		x >>= 1u;

		found1 = found1 | (x & 1u);
		count += found1 ^ 1u;
		x >>= 1u;

		found1 = found1 | (x & 1u);
		count += found1 ^ 1u;
		x >>= 1u;

		found1 = found1 | (x & 1u);
		count += found1 ^ 1u;
		x >>= 1u;

		found1 = found1 | (x & 1u);
		count += found1 ^ 1u;
		x >>= 1u;

		found1 = found1 | (x & 1u);
		count += found1 ^ 1u;

		return count;

		//if (aValue == 0u) return 8u;

		//size_t count = 0u;
		//while (true) {
		//	if (aValue & 1u) break;
		//	aValue >>= 1u;
		//	++count;
		//}
		//return count;
	}

	static size_t ANVIL_CALL lzcount16_c(uint16_t aValue) throw() {
		size_t count = lzcount8_c(static_cast<uint8_t>(aValue & UINT8_MAX));
		if (count == 8u) count += lzcount8_c(static_cast<uint8_t>(aValue >> 8ull));
		return count;
	}

	static size_t ANVIL_CALL lzcount32_c(uint32_t aValue) throw() {
		size_t count = lzcount16_c(static_cast<uint16_t>(aValue & UINT16_MAX));
		if (count == 16u) count += lzcount16_c(static_cast<uint16_t>(aValue >> 16ull));
		return count;
	}

	static size_t ANVIL_CALL lzcount64_c(uint64_t aValue) throw() {
		size_t count = lzcount32_c(static_cast<uint32_t>(aValue & UINT32_MAX));
		if (count == 32u) count += lzcount32_c(static_cast<uint32_t>(aValue >> 32ull));
		return count;
	}

	static size_t(*lzcount8_fn)(uint8_t) = ANVIL_HW_LZCNTB ? detail::lzcount8_hwb : ANVIL_HW_LZCNTA ? detail::lzcount8_hwa : detail::lzcount8_c;
	static size_t(*lzcount16_fn)(uint16_t) = ANVIL_HW_LZCNTB ? detail::lzcount16_hwb : ANVIL_HW_LZCNTA ? detail::lzcount16_hwa : detail::lzcount16_c;
	static size_t(*lzcount32_fn)(uint32_t) = ANVIL_HW_LZCNTB ? detail::lzcount32_hwb : ANVIL_HW_LZCNTA ? detail::lzcount32_hwa : detail::lzcount32_c;
	static size_t(*lzcount64_fn)(uint64_t) = ANVIL_HW_LZCNTB ? detail::lzcount64_hwb : ANVIL_HW_LZCNTA ? detail::lzcount64_hwa : detail::lzcount64_c;

}}


namespace anvil {

	/*!
	*	\tparam T The data type
	*	\tparam BRANCHING True if function should be inlined with a conditional branch, false for a function pointer call.
	*/
	template<class T, bool BRANCHING = false>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount(T aValue) throw();

	// unsigned

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount<uint8_t, false>(uint8_t aValue) throw() {
		return detail::lzcount8_fn(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount<uint16_t, false>(uint16_t aValue) throw() {
		return detail::lzcount16_fn(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount<uint32_t, false>(uint32_t aValue) throw() {
		return detail::lzcount32_fn(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount<uint64_t, false>(uint64_t aValue) throw() {
		return detail::lzcount64_fn(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount<uint8_t, true>(uint8_t aValue) throw() {
		return ANVIL_HW_LZCNTB ? detail::lzcount8_hwb(aValue) : ANVIL_HW_LZCNTA ? detail::lzcount8_hwa(aValue) : detail::lzcount8_c(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount<uint16_t, true>(uint16_t aValue) throw() {
		return ANVIL_HW_LZCNTB ? detail::lzcount16_hwb(aValue) : ANVIL_HW_LZCNTA ? detail::lzcount16_hwa(aValue) : detail::lzcount16_c(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount<uint32_t, true>(uint32_t aValue) throw() {
		return ANVIL_HW_LZCNTB ? detail::lzcount32_hwb(aValue) : ANVIL_HW_LZCNTA ? detail::lzcount32_hwa(aValue) : detail::lzcount32_c(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount<uint64_t, true>(uint64_t aValue) throw() {
		return ANVIL_HW_LZCNTB ? detail::lzcount64_hwb(aValue) : ANVIL_HW_LZCNTA ? detail::lzcount64_hwa(aValue) : detail::lzcount64_c(aValue);
	}

	// signed

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount<int8_t, false>(int8_t aValue) throw() {
		return lzcount<uint8_t, false>(numeric_reinterpret_cast<uint8_t>(aValue));
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount<int8_t, true>(int8_t aValue) throw() {
		return lzcount<uint8_t, true>(numeric_reinterpret_cast<uint8_t>(aValue));
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount<int16_t, false>(int16_t aValue) throw() {
		return lzcount<uint16_t, false>(numeric_reinterpret_cast<uint16_t>(aValue));
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount<int16_t, true>(int16_t aValue) throw() {
		return lzcount<uint16_t, true>(numeric_reinterpret_cast<uint16_t>(aValue));
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount<int32_t, false>(int32_t aValue) throw() {
		return lzcount<uint32_t, false>(numeric_reinterpret_cast<uint32_t>(aValue));
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount<int32_t, true>(int32_t aValue) throw() {
		return lzcount<uint32_t, true>(numeric_reinterpret_cast<uint32_t>(aValue));
	}

	// other types

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount<float, false>(float aValue) throw() {
		return lzcount<uint32_t, false>(numeric_reinterpret_cast<uint32_t>(aValue));
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount<float, true>(float aValue) throw() {
		return lzcount<uint32_t, true>(numeric_reinterpret_cast<uint32_t>(aValue));
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount<double, false>(double aValue) throw() {
		return lzcount<uint64_t, false>(numeric_reinterpret_cast<uint64_t>(aValue));
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount<double, true>(double aValue) throw() {
		return lzcount<uint64_t, true>(numeric_reinterpret_cast<uint64_t>(aValue));
	}

}

#endif
