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

#ifndef ANVIL_CORE_TZCOUNT_HPP
#define ANVIL_CORE_TZCOUNT_HPP

/*
	tzcount Count then number of trailing zero bits
*/

#include "anvil/core/LeadingZeroCount.hpp"

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
	#if ANVIL_MIN_INSTRUCTION_SET & ANVIL_ASM_BMI1
		#define ANVIL_HW_TZCNTA false
		#define ANVIL_HW_TZCNTB true
		#define ANVIL_HW_TZCNT_COMPILETIME true
	#else
		#define ANVIL_HW_TZCNTA ANVIL_HW_LZCNTA
		#define ANVIL_HW_TZCNTB ANVIL_HW_LZCNTB
		#define ANVIL_HW_TZCNT_COMPILETIME ANVIL_HW_LZCNT_COMPILETIME
	#endif
#else
	#define ANVIL_HW_TZCNTA false
	#define ANVIL_HW_TZCNTB false
	#define ANVIL_HW_TZCNT_COMPILETIME true
#endif

namespace anvil { namespace detail {

	// Using BSR instruction

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount32_hwa(uint32_t aValue) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		if (aValue == 0u) return 32u;
		unsigned long idx = 0;

		// Find the most significant bit
		_BitScanReverse(&idx, aValue);

		return 31 - idx;
#else
		return 0;
#endif
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount8_hwa(uint8_t aValue) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		return tzcount32_hwa(aValue) - 24u;
#else
		return 0;
#endif
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount16_hwa(uint16_t aValue) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		return tzcount32_hwa(aValue) - 16u;
#else
		return 0;
#endif
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount64_hwa(uint64_t aValue) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		if (aValue == 0u) return 64u;
		unsigned long idx = 0;

		// Find the most significant bit
		_BitScanReverse64(&idx, aValue);

		return 63 - idx;
#elif ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86
		size_t count = tzcount32_hwa(static_cast<uint32_t>(aValue >> 32ull));
		if (count == 32u) count += tzcount32_hwa(static_cast<uint32_t>(aValue & UINT32_MAX));
		return count;
#else
		return 0;
#endif
	}

	// Using TZCNT instruction

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount8_hwb(uint8_t aValue) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		if (aValue == 0u) return 8u;
		return _tzcnt_u32(static_cast<uint32_t>(aValue) << 24u);
#else
		return 0;
#endif
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount16_hwb(uint16_t aValue) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		if (aValue == 0u) return 16u;
		return _tzcnt_u32(static_cast<uint32_t>(aValue) << 16u);
#else
		return 0;
#endif
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount32_hwb(uint32_t aValue) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		if (aValue == 0u) return 32u;
		//return _tzcnt_u32(aValue);
		return _tzcnt_u32(aValue);
#else
		return 0;
#endif
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount64_hwb(uint64_t aValue) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		if (aValue == 0u) return 64u;
		return _tzcnt_u64(aValue);
#elif ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86
		size_t count = tzcount32_hwb(static_cast<uint32_t>(aValue >> 32ull));
		if (count == 32u) count += tzcount32_hwb(static_cast<uint32_t>(aValue & UINT32_MAX));
		return count;
#else
		return 0;
#endif
	}

	static size_t ANVIL_CALL tzcount8_c(uint8_t aValue) throw() {
		uint32_t x = aValue;

		if (x & 128u) return 0u;
		x <<= 1u;

		if (x & 128u) return 1u;
		x <<= 1u;

		if (x & 128u) return 2u;
		x <<= 1u;

		if (x & 128u) return 3u;
		x <<= 1u;

		if (x & 128u) return 4u;
		x <<= 1u;

		if (x & 128u) return 5u;
		x <<= 1u;

		if (x & 128u) return 6u;
		x <<= 1u;

		if (x & 128u) return 7u;
		return 8u;
	}

	static size_t ANVIL_CALL tzcount16_c(uint16_t aValue) throw() {
		size_t count = tzcount8_c(static_cast<uint8_t>(aValue >> 8ull));
		if (count == 8u) count += tzcount8_c(static_cast<uint8_t>(aValue & UINT8_MAX));
		return count;
	}	
	
	static size_t ANVIL_CALL tzcount32_c(uint32_t aValue) throw() {
		size_t count = tzcount16_c(static_cast<uint16_t>(aValue >> 16ull));
		if (count == 16u) count += tzcount16_c(static_cast<uint16_t>(aValue & UINT16_MAX));
		return count;
	}

	static size_t ANVIL_CALL tzcount64_c(uint64_t aValue) throw() {
		size_t count = tzcount32_c(static_cast<uint32_t>(aValue >> 32ull));
		if (count == 32u) count += tzcount32_c(static_cast<uint32_t>(aValue & UINT32_MAX));
		return count;
	}

	static size_t(*tzcount8_fn)(uint8_t) = ANVIL_HW_TZCNTB ? detail::tzcount8_hwb : ANVIL_HW_TZCNTA ? detail::tzcount8_hwa : detail::tzcount8_c;
	static size_t(*tzcount16_fn)(uint16_t) = ANVIL_HW_TZCNTB ? detail::tzcount16_hwb : ANVIL_HW_TZCNTA ? detail::tzcount16_hwa : detail::tzcount16_c;
	static size_t(*tzcount32_fn)(uint32_t) = ANVIL_HW_TZCNTB ? detail::tzcount32_hwb : ANVIL_HW_TZCNTA ? detail::tzcount32_hwa : detail::tzcount32_c;
	static size_t(*tzcount64_fn)(uint64_t) = ANVIL_HW_TZCNTB ? detail::tzcount64_hwb : ANVIL_HW_TZCNTA ? detail::tzcount64_hwa : detail::tzcount64_c;

}}


namespace anvil {

	/*!
	*	\tparam T The data type
	*	\tparam BRANCHING True if function should be inlined with a conditional branch, false for a function pointer call.
	*/
	template<class T, bool BRANCHING = ANVIL_HW_TZCNT_COMPILETIME>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount(T aValue) throw();

	// unsigned

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount<uint8_t, false>(uint8_t aValue) throw() {
		return detail::tzcount8_fn(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount<uint16_t, false>(uint16_t aValue) throw() {
		return detail::tzcount16_fn(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount<uint32_t, false>(uint32_t aValue) throw() {
		return detail::tzcount32_fn(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount<uint64_t, false>(uint64_t aValue) throw() {
		return detail::tzcount64_fn(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount<uint8_t, true>(uint8_t aValue) throw() {
		return ANVIL_HW_TZCNTB ? detail::tzcount8_hwb(aValue) : ANVIL_HW_TZCNTA ? detail::tzcount8_hwa(aValue) : detail::tzcount8_c(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount<uint16_t, true>(uint16_t aValue) throw() {
		return ANVIL_HW_TZCNTB ? detail::tzcount16_hwb(aValue) : ANVIL_HW_TZCNTA ? detail::tzcount16_hwa(aValue) : detail::tzcount16_c(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount<uint32_t, true>(uint32_t aValue) throw() {
		return ANVIL_HW_TZCNTB ? detail::tzcount32_hwb(aValue) : ANVIL_HW_TZCNTA ? detail::tzcount32_hwa(aValue) : detail::tzcount32_c(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount<uint64_t, true>(uint64_t aValue) throw() {
		return ANVIL_HW_TZCNTB ? detail::tzcount64_hwb(aValue) : ANVIL_HW_TZCNTA ? detail::tzcount64_hwa(aValue) : detail::tzcount64_c(aValue);
	}

	// signed

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount<int8_t, false>(int8_t aValue) throw() {
		return tzcount<uint8_t, false>(numeric_reinterpret_cast<uint8_t>(aValue));
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount<int8_t, true>(int8_t aValue) throw() {
		return tzcount<uint8_t, true>(numeric_reinterpret_cast<uint8_t>(aValue));
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount<int16_t, false>(int16_t aValue) throw() {
		return tzcount<uint16_t, false>(numeric_reinterpret_cast<uint16_t>(aValue));
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount<int16_t, true>(int16_t aValue) throw() {
		return tzcount<uint16_t, true>(numeric_reinterpret_cast<uint16_t>(aValue));
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount<int32_t, false>(int32_t aValue) throw() {
		return tzcount<uint32_t, false>(numeric_reinterpret_cast<uint32_t>(aValue));
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount<int32_t, true>(int32_t aValue) throw() {
		return tzcount<uint32_t, true>(numeric_reinterpret_cast<uint32_t>(aValue));
	}

	// other types

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount<float, false>(float aValue) throw() {
		return tzcount<uint32_t, false>(numeric_reinterpret_cast<uint32_t>(aValue));
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount<float, true>(float aValue) throw() {
		return tzcount<uint32_t, true>(numeric_reinterpret_cast<uint32_t>(aValue));
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount<double, false>(double aValue) throw() {
		return tzcount<uint64_t, false>(numeric_reinterpret_cast<uint64_t>(aValue));
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount<double, true>(double aValue) throw() {
		return tzcount<uint64_t, true>(numeric_reinterpret_cast<uint64_t>(aValue));
	}

}

#endif