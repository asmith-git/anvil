//Copyright 2023 Adam G. Smith
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
	popcount Count then number of leading zero bits
*/

#include "anvil/core/Keywords.hpp"

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
	#include <immintrin.h>
	#include <intrin.h>
#endif

#include "CpuRuntime.hpp"

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
	#if ANVIL_MIN_INSTRUCTION_SET & ANVIL_ASM_POPCNT
		#define ANVIL_HW_POPCNT true
		#define ANVIL_HW_POPCNT_COMPILETIME true
	#else
		#define ANVIL_HW_POPCNT anvil::AreInstructionSetSupported(anvil::ASM_POPCNT)
		#define ANVIL_HW_POPCNT_COMPILETIME false
	#endif
#else
	#define ANVIL_HW_POPCNT false
	#define ANVIL_HW_POPCNT_COMPILETIME true
#endif

namespace anvil { namespace detail {

	// Using POPCNT instruction

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount8_hw(uint8_t aValue) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		return _mm_popcnt_u32(aValue);
#else
		return 0;
#endif
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount16_hw(uint16_t aValue) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		return _mm_popcnt_u32(aValue);
#else
		return 0;
#endif
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount32_hw(uint32_t aValue) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		return _mm_popcnt_u32(aValue);
#else
		return 0;
#endif
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount64_hw(uint64_t aValue) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		return _mm_popcnt_u64(aValue);
#elif ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86
		return _mm_popcnt_u32(static_cast<uint32_t>(aValue & UINT32_MAX)) + _mm_popcnt_u32(static_cast<uint32_t>(aValue >> 32ull));
#else
		return 0;
#endif
	}

	static size_t ANVIL_CALL popcount8_c(uint8_t aValue) throw() {
		uint32_t val = aValue;
		uint32_t bit0 = val & 1u;
		uint32_t bit1 = val & 2u;
		uint32_t bit2 = val & 4u;
		uint32_t bit3 = val & 8u;
		uint32_t bit4 = val & 16u;
		uint32_t bit5 = val & 32u;
		uint32_t bit6 = val & 64u;
		uint32_t bit7 = val & 128u;

		bit1 >>= 1u;
		bit2 >>= 2u;
		bit3 >>= 3u;
		bit4 >>= 4u;
		bit5 >>= 5u;
		bit6 >>= 6u;
		bit7 >>= 7u;

		bit0 += bit1;
		bit2 += bit3;
		bit4 += bit5;
		bit6 += bit7;

		bit0 += bit2;
		bit4 += bit6;

		return bit0 + bit4;
	}

	static size_t ANVIL_CALL popcount16_c(uint16_t aValue) throw() {
		return popcount8_c(static_cast<uint8_t>(aValue & UINT8_MAX)) + popcount8_c(static_cast<uint8_t>(aValue >> 8ull));
	}

	static size_t ANVIL_CALL popcount32_c(uint32_t aValue) throw() {
		return popcount16_c(static_cast<uint16_t>(aValue & UINT16_MAX)) + popcount16_c(static_cast<uint16_t>(aValue >> 16ull));
	}

	static size_t ANVIL_CALL popcount64_c(uint64_t aValue) throw() {
		return popcount32_c(static_cast<uint32_t>(aValue & UINT32_MAX)) + popcount32_c(static_cast<uint32_t>(aValue >> 32ull));
	}

	static size_t(*popcount8_fn)(uint8_t) = ANVIL_HW_POPCNT ? detail::popcount8_hw : detail::popcount8_c;
	static size_t(*popcount16_fn)(uint16_t) = ANVIL_HW_POPCNT ? detail::popcount16_hw : detail::popcount16_c;
	static size_t(*popcount32_fn)(uint32_t) = ANVIL_HW_POPCNT ? detail::popcount32_hw : detail::popcount32_c;
	static size_t(*popcount64_fn)(uint64_t) = ANVIL_HW_POPCNT ? detail::popcount64_hw : detail::popcount64_c;

}}


namespace anvil {

	/*!
	*	\tparam T The data type
	*	\tparam BRANCHING True if function should be inlined with a conditional branch, false for a function pointer call.
	*/
	template<class T, bool BRANCHING = ANVIL_HW_TZCNT_COMPILETIME>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount(T aValue) throw();

	// unsigned

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<uint8_t, false>(uint8_t aValue) throw() {
		return detail::popcount8_fn(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<uint16_t, false>(uint16_t aValue) throw() {
		return detail::popcount16_fn(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<uint32_t, false>(uint32_t aValue) throw() {
		return detail::popcount32_fn(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<uint64_t, false>(uint64_t aValue) throw() {
		return detail::popcount64_fn(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<uint8_t, true>(uint8_t aValue) throw() {
		return ANVIL_HW_POPCNT ? detail::popcount8_hw(aValue) : detail::popcount8_c(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<uint16_t, true>(uint16_t aValue) throw() {
		return ANVIL_HW_POPCNT ? detail::popcount16_hw(aValue) : detail::popcount16_c(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<uint32_t, true>(uint32_t aValue) throw() {
		return ANVIL_HW_POPCNT ? detail::popcount32_hw(aValue) : detail::popcount32_c(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<uint64_t, true>(uint64_t aValue) throw() {
		return ANVIL_HW_POPCNT ? detail::popcount64_hw(aValue) : detail::popcount64_c(aValue);
	}

	// signed

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<int8_t, false>(int8_t aValue) throw() {
		return popcount<uint8_t, false>(numeric_reinterpret_cast<uint8_t>(aValue));
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<int8_t, true>(int8_t aValue) throw() {
		return popcount<uint8_t, true>(numeric_reinterpret_cast<uint8_t>(aValue));
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<int16_t, false>(int16_t aValue) throw() {
		return popcount<uint16_t, false>(numeric_reinterpret_cast<uint16_t>(aValue));
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<int16_t, true>(int16_t aValue) throw() {
		return popcount<uint16_t, true>(numeric_reinterpret_cast<uint16_t>(aValue));
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<int32_t, false>(int32_t aValue) throw() {
		return popcount<uint32_t, false>(numeric_reinterpret_cast<uint32_t>(aValue));
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<int32_t, true>(int32_t aValue) throw() {
		return popcount<uint32_t, true>(numeric_reinterpret_cast<uint32_t>(aValue));
	}

	// other types

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<float, false>(float aValue) throw() {
		return popcount<uint32_t, false>(numeric_reinterpret_cast<uint32_t>(aValue));
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<float, true>(float aValue) throw() {
		return popcount<uint32_t, true>(numeric_reinterpret_cast<uint32_t>(aValue));
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<double, false>(double aValue) throw() {
		return popcount<uint64_t, false>(numeric_reinterpret_cast<uint64_t>(aValue));
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<double, true>(double aValue) throw() {
		return popcount<uint64_t, true>(numeric_reinterpret_cast<uint64_t>(aValue));
	}

}

#endif
