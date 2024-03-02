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

// Disable warnings for unreferenced functions and use of static on a specialised template functions
// - This is a library, so we don't know what functions the und user will use or not
// - There is no particular reason why a template function can't be specialsied in a header, compilers handle it just fine
// (These functions are implemented in the header file so they can be inlined into user code for performance gains)
#pragma warning(disable:4499 4505)

namespace anvil { namespace detail {

	// Unoptimised functions for testing the output of the optimsied versions

	template<class T>
	static size_t ANVIL_CALL popcount_test(T aValue) throw()
	{
		return popcount_test<UnsignedType<T>>(numeric_reinterpret_cast<UnsignedType<T>>(aValue));
	}

	template<>
	static size_t ANVIL_CALL popcount_test<uint8_t>(uint8_t aValue) throw()
	{
		uint32_t value_word = aValue;
		size_t count = 0u;
		uint32_t bit = 1u;
		
		for (size_t i = 0u; i < 8u; ++i)
		{
			count += value_word & bit ? 1u : 0u;
			bit <<= 1ul;
		}

		return count;
	}

	template<>
	static size_t ANVIL_CALL popcount_test<uint16_t>(uint16_t aValue) throw()
	{
		uint32_t value_word = aValue;
		size_t count = 0u;
		uint32_t bit = 1u;

		for (size_t i = 0u; i < 16u; ++i)
		{
			count += value_word & bit ? 1u : 0u;
			bit <<= 1ul;
		}

		return count;
	}

	template<>
	static size_t ANVIL_CALL popcount_test<uint32_t>(uint32_t aValue) throw()
	{
		uint32_t value_word = aValue;
		size_t count = 0u;
		uint32_t bit = 1u;

		for (size_t i = 0u; i < 32u; ++i)
		{
			count += value_word & bit ? 1u : 0u;
			bit <<= 1ul;
		}

		return count;
	}

	template<>
	static size_t ANVIL_CALL popcount_test<uint64_t>(uint64_t aValue) throw()
	{
		uint64_t value_word = aValue;
		size_t count = 0u;
		uint64_t bit = 1ull;

		for (size_t i = 0u; i < 64u; ++i)
		{
			count += value_word & bit ? 1u : 0u;
			bit <<= 1ull;
		}

		return count;
	}

	// Optimised C++ implementation

	template<class T>
	static size_t ANVIL_CALL popcount_c(T aValue) throw()
	{
		return popcount_c<UnsignedType<T>>(numeric_reinterpret_cast<UnsignedType<T>>(aValue));
	}

	template<>
	static size_t ANVIL_CALL popcount_c<uint8_t>(uint8_t aValue) throw()
	{
		uint32_t val = aValue;
		uint32_t bit0 = val & 1u;
		uint32_t bit1 = (val & 2u) >> 1u;
		uint32_t bit2 = (val & 4u) >> 2u;
		uint32_t bit3 = (val & 8u) >> 3u;
		uint32_t bit4 = (val & 16u) >> 4u;
		uint32_t bit5 = (val & 32u) >> 5u;
		uint32_t bit6 = (val & 64u) >> 6u;
		uint32_t bit7 = (val & 128u) >> 7u;

		bit0 += bit1;
		bit2 += bit3;
		bit4 += bit5;
		bit6 += bit7;

		bit0 += bit2;
		bit4 += bit6;

		return bit0 + bit4;
	}

	template<>
	static size_t ANVIL_CALL popcount_c<uint16_t>(uint16_t aValue) throw()
	{
		return 
			popcount_c<uint8_t>(static_cast<uint8_t>(aValue & UINT8_MAX)) + 
			popcount_c<uint8_t>(static_cast<uint8_t>(aValue >> 8u))
		;
	}

	template<>
	static size_t ANVIL_CALL popcount_c<uint32_t>(uint32_t aValue) throw()
	{
		return 
			popcount_c<uint16_t>(static_cast<uint16_t>(aValue & UINT16_MAX)) + 
			popcount_c<uint16_t>(static_cast<uint16_t>(aValue >> 16u))
		;
	}

	template<>
	static size_t ANVIL_CALL popcount_c<uint64_t>(uint64_t aValue) throw()
	{
		return 
			popcount_c<uint32_t>(static_cast<uint32_t>(aValue & UINT32_MAX)) + 
			popcount_c<uint32_t>(static_cast<uint32_t>(aValue >> 32ull))
		;
	}

	// Optimised using the x86 POPCNT instruction


	template<class T>
	static size_t ANVIL_CALL popcount_hw(T aValue) throw()
	{
		return popcount_hw<UnsignedType<T>>(numeric_reinterpret_cast<UnsignedType<T>>(aValue));
	}

	template<>
	static size_t ANVIL_CALL popcount_hw<uint8_t>(uint8_t aValue) throw()
	{
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		return _mm_popcnt_u32(aValue);
#else
		return popcount_c<decltype(aValue)>(aValue);
#endif
	}

	template<>
	static size_t ANVIL_CALL popcount_hw<uint16_t>(uint16_t aValue) throw()
	{
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		return _mm_popcnt_u32(aValue);
#else
		return popcount_c<decltype(aValue)>(aValue);
#endif
	}

	template<>
	static size_t ANVIL_CALL popcount_hw<uint32_t>(uint32_t aValue) throw()
	{
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		return _mm_popcnt_u32(aValue);
#else
		return popcount_c<decltype(aValue)>(aValue);
#endif
	}

	template<>
	static size_t ANVIL_CALL popcount_hw<uint64_t>(uint64_t aValue) throw()
	{
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		return _mm_popcnt_u64(aValue);
#elif ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86
		return 
			_mm_popcnt_u32(static_cast<uint32_t>(aValue & UINT32_MAX)) + 
			_mm_popcnt_u32(static_cast<uint32_t>(aValue >> 32ull))
		;
#else
		return popcount_c<decltype(aValue)>(aValue);
#endif
	}
}}


namespace anvil 
{
	/*!
	*	\brief Count the number of bits set to 1 in a primative numeric value.
	*	\tparam T The data type
	*	\tparam USE_HARDWARE_OPTIMISATION True if the x86 POPCNT instruction should be used, otherwise a C++ implementation is used.
	*/
	template<class T, bool USE_HARDWARE_OPTIMISATION = ANVIL_HW_POPCNT_COMPILETIME>
	static ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount(T aValue) throw()
	{
		if constexpr (USE_HARDWARE_OPTIMISATION)
		{
			return detail::popcount_hw<T>(aValue);
		}
		else
		{
			return detail::popcount_c<T>(aValue);
		}
	}

	/*!
	*	\brief Count the number of bits set to 0 in a primative numeric value.
	*	\tparam T The data type
	*	\tparam USE_HARDWARE_OPTIMISATION True if the x86 POPCNT instruction should be used, otherwise a C++ implementation is used.
	*/
	template<class T, bool USE_HARDWARE_OPTIMISATION = ANVIL_HW_POPCNT_COMPILETIME>
	static ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount_inverse(T aValue) throw()
	{
		enum 
		{
			SIZE_BITS = sizeof(T) * 8u	//!< Number of bits in data type T.
		};
		
		return SIZE_BITS - popcount<T, USE_HARDWARE_OPTIMISATION>(aValue);
	}

}

// Renable warnings diabled earlier in this header file
#pragma warning(default:4499 4505)

#endif
