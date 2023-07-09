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
		#define ANVIL_HW_LZCNT true
	#else
		#define ANVIL_HW_LZCNT anvil::AreInstructionSetSupported(anvil::ASM_BMI1)
	#endif
#else
	#define ANVIL_HW_LZCNT false
#endif

namespace anvil { namespace detail {

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount8_hw(uint8_t aValue) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		if (aValue == 0u) return 8u;
		return __lzcnt16(aValue);
#else
		return 0;
#endif
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount16_hw(uint16_t aValue) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		if (aValue == 0u) return 16u;
		return __lzcnt16(aValue);
#else
		return 0;
#endif
	}

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount32_hw(uint32_t aValue) throw() {
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

	static ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount64_hw(uint64_t aValue) throw() {
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

	static size_t(*lzcount8_fn)(uint8_t) = ANVIL_HW_LZCNT ? detail::lzcount8_hw : detail::lzcount8_c;
	static size_t(*lzcount16_fn)(uint16_t) = ANVIL_HW_LZCNT ? detail::lzcount16_hw : detail::lzcount16_c;
	static size_t(*lzcount32_fn)(uint32_t) = ANVIL_HW_LZCNT ? detail::lzcount32_hw : detail::lzcount32_c;
	static size_t(*lzcount64_fn)(uint64_t) = ANVIL_HW_LZCNT ? detail::lzcount64_hw : detail::lzcount64_c;

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
		return ANVIL_HW_LZCNT ? detail::lzcount8_hw(aValue) : detail::lzcount8_c(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount<uint16_t, true>(uint16_t aValue) throw() {
		return ANVIL_HW_LZCNT ? detail::lzcount16_hw(aValue) : detail::lzcount16_c(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount<uint32_t, true>(uint32_t aValue) throw() {
		return ANVIL_HW_LZCNT ? detail::lzcount32_hw(aValue) : detail::lzcount32_c(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount<uint64_t, true>(uint64_t aValue) throw() {
		return ANVIL_HW_LZCNT ? detail::lzcount64_hw(aValue) : detail::lzcount64_c(aValue);
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
