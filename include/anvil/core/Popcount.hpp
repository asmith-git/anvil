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



namespace anvil 
{ 

	enum PopcountImplementation
	{
		POPCOUNT_TEST,			//!< Unoptimised reference C++ implementation, for testing the output of the more optimised implementations.
		POPCOUNT_CPP,			//!< Optimised C++ implementation.
		POPCOUNT_CONSTEXPR,		//!< This implementation can be run at compile-time.
		POPCOUNT_LUT4,			//!< Uses a 4-bit look-up table (LUT), may be faster than the C++ implementation on some architectures.
		POPCOUNT_LUT8,			//!< Uses a 8-bit look-up table (LUT), may be faster than the C++ implementation on some architectures.
		POPCOUNT_X86,			//!< This implementation uses the x86 POPCNT instruction, should be the fastest way to do this calculation.

		POPCOUNT_DEFAULT = ANVIL_HW_POPCNT_COMPILETIME ? POPCOUNT_X86 : POPCOUNT_CPP
	};

	namespace detail
	{
		template<class T, PopcountImplementation IMPLEMENTATION>
		struct PopcountHelper
		{
			static ANVIL_STRONG_INLINE size_t Execute(const T a_value) throw()
			{
				if constexpr (std::is_unsigned<T>::value)
				{
					// Call the C++ implementation
					return PopcountHelper<T, POPCOUNT_CPP>::Execute(a_value);
				}
				else
				{
					// Call the unsigned version of this implementation
					typedef UnsignedType<T> UT;
					return PopcountHelper<UT, IMPLEMENTATION>::Execute(numeric_reinterpret_cast<UT>(a_value));
				}
			}
		};

		// POPCOUNT_TEST

		template<>
		struct PopcountHelper<uint8_t, POPCOUNT_TEST>
		{
			static ANVIL_STRONG_INLINE size_t Execute(const uint8_t a_value) throw()
			{
				uint32_t value_word = a_value;
				size_t count = 0u;
				uint32_t bit = 1u;

				for (size_t i = 0u; i < 8u; ++i)
				{
					count += value_word & bit ? 1u : 0u;
					bit <<= 1ul;
				}

				return count;
			}
		};

		template<>
		struct PopcountHelper<uint16_t, POPCOUNT_TEST>
		{
			static ANVIL_STRONG_INLINE size_t Execute(const uint16_t a_value) throw()
			{
				uint32_t value_word = a_value;
				size_t count = 0u;
				uint32_t bit = 1u;

				for (size_t i = 0u; i < 16u; ++i)
				{
					count += value_word & bit ? 1u : 0u;
					bit <<= 1ul;
				}

				return count;
			}
		};

		template<>
		struct PopcountHelper<uint32_t, POPCOUNT_TEST>
		{
			static ANVIL_STRONG_INLINE size_t Execute(const uint32_t a_value) throw()
			{
				uint32_t value_word = a_value;
				size_t count = 0u;
				uint32_t bit = 1u;

				for (size_t i = 0u; i < 32u; ++i)
				{
					count += value_word & bit ? 1u : 0u;
					bit <<= 1ul;
				}

				return count;
			}
		};

		template<>
		struct PopcountHelper<uint64_t, POPCOUNT_TEST>
		{
			static ANVIL_STRONG_INLINE size_t Execute(const uint64_t a_value) throw()
			{
				uint64_t value_word = a_value;
				size_t count = 0u;
				uint64_t bit = 1ull;

				for (size_t i = 0u; i < 64u; ++i)
				{
					count += value_word & bit ? 1u : 0u;
					bit <<= 1ull;
				}

				return count;
			}
		};

		// POPCOUNT_CPP

		template<>
		struct PopcountHelper<uint8_t, POPCOUNT_CPP>
		{
			static ANVIL_STRONG_INLINE size_t Execute(const uint8_t a_value) throw()
			{
				uint32_t val = a_value;
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
		};

		template<>
		struct PopcountHelper<uint16_t, POPCOUNT_CPP>
		{
			static inline size_t Execute(const uint16_t a_value) throw()
			{
				return
					PopcountHelper<uint8_t, POPCOUNT_CPP>::Execute(static_cast<uint8_t>(a_value & UINT8_MAX)) +
					PopcountHelper<uint8_t, POPCOUNT_CPP>::Execute(static_cast<uint8_t>(a_value >> 8u))
				;
			}
		};

		template<>
		struct PopcountHelper<uint32_t, POPCOUNT_CPP>
		{
			static inline size_t Execute(const uint32_t a_value) throw()
			{
				return
					PopcountHelper<uint16_t, POPCOUNT_CPP>::Execute(static_cast<uint16_t>(a_value & UINT16_MAX)) +
					PopcountHelper<uint16_t, POPCOUNT_CPP>::Execute(static_cast<uint16_t>(a_value >> 16u))
				;
			}
		};

		template<>
		struct PopcountHelper<uint64_t, POPCOUNT_CPP>
		{
			static inline size_t Execute(const uint64_t a_value) throw()
			{
				return
					PopcountHelper<uint32_t, POPCOUNT_CPP>::Execute(static_cast<uint32_t>(a_value & UINT32_MAX)) +
					PopcountHelper<uint32_t, POPCOUNT_CPP>::Execute(static_cast<uint32_t>(a_value >> 32ull))
				;
			}
		};

		// POPCOUNT_X86

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64

		template<>
		struct PopcountHelper<uint8_t, POPCOUNT_X86>
		{
			static ANVIL_STRONG_INLINE size_t Execute(const uint8_t a_value) throw()
			{
				return static_cast<size_t>(_mm_popcnt_u32(a_value));
			}
		};

		template<>
		struct PopcountHelper<uint16_t, POPCOUNT_X86>
		{
			static ANVIL_STRONG_INLINE size_t Execute(const uint16_t a_value) throw()
			{
				return static_cast<size_t>(_mm_popcnt_u32(a_value));
			}
		};

		template<>
		struct PopcountHelper<uint32_t, POPCOUNT_X86>
		{
			static ANVIL_STRONG_INLINE size_t Execute(const uint32_t a_value) throw()
			{
				return static_cast<size_t>(_mm_popcnt_u32(a_value));
			}
		};

		template<>
		struct PopcountHelper<uint64_t, POPCOUNT_X86>
		{
			static ANVIL_STRONG_INLINE size_t Execute(const uint64_t a_value) throw()
			{
				#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
					return _mm_popcnt_u64(a_value);
				#else
					return
						_mm_popcnt_u32(static_cast<uint32_t>(a_value & UINT32_MAX)) +
						_mm_popcnt_u32(static_cast<uint32_t>(a_value >> 32ull))
					;
				#endif
			}
		};

#endif

		// POPCOUNT_CONSTEXPR

		template<class T>
		struct PopcountHelper<T, POPCOUNT_CONSTEXPR>
		{
			static ANVIL_CONSTEXPR_FN size_t Execute(const T a_value) throw()
			{
				if constexpr (std::is_unsigned<T>::value)
				{
					enum { BIT_COUNT = sizeof(T) * 8u };

					uint64_t value_word = a_value;
					size_t count = 0u;
					uint64_t bit = 1ull;

					for (size_t i = 0u; i < BIT_COUNT; ++i)
					{
						count += value_word & bit ? 1u : 0u;
						bit <<= 1ull;
					}

					return count;
				}
				else
				{
					// Call the unsigned version of this implementation
					typedef UnsignedType<T> UT;
					return PopcountHelper<UT, POPCOUNT_CONSTEXPR>::Execute(numeric_reinterpret_cast<UT>(a_value));
				}
			}
		};

		// POPCOUNT_LUT4

		ANVIL_DLL_EXPORT const uint8_t* ANVIL_CALL GetPopcountLUT() throw();

		template<>
		struct PopcountHelper<uint8_t, POPCOUNT_LUT4>
		{
			static inline size_t Execute(const uint8_t a_value) throw()
			{
				const uint8_t* const table = GetPopcountLUT();
				size_t count = table[a_value & 15u];
				count += table[a_value >> 4u];
				return count;
			}
		};

		template<>
		struct PopcountHelper<uint16_t, POPCOUNT_LUT4>
		{
			static inline size_t Execute(const uint16_t a_value) throw()
			{
				const uint8_t* const table = GetPopcountLUT();
				size_t count = table[a_value & 15u];
				count += table[(a_value >> 4u) & 15u];
				count += table[(a_value >> 8u) & 15u];
				count += table[(a_value >> 12u) & 15u];
				return count;
			}
		};

		template<>
		struct PopcountHelper<uint32_t, POPCOUNT_LUT4>
		{
			static inline size_t Execute(const uint32_t a_value) throw()
			{
				const uint8_t* const table = GetPopcountLUT();
				size_t count = table[a_value & 15u];
				count += table[(a_value >> 4u) & 15u];
				count += table[(a_value >> 8u) & 15u];
				count += table[(a_value >> 12u) & 15u];
				count += table[(a_value >> 16u) & 15u];
				count += table[(a_value >> 20u) & 15u];
				count += table[(a_value >> 24u) & 15u];
				count += table[(a_value >> 28u) & 15u];
				return count;
			}
		};

		template<>
		struct PopcountHelper<uint64_t, POPCOUNT_LUT4>
		{
			static inline size_t Execute(const uint64_t a_value) throw()
			{
				const uint8_t* const table = GetPopcountLUT();
				size_t count = table[a_value & 15ull];
				count += table[(a_value >> 4ull) & 15ull];
				count += table[(a_value >> 8ull) & 15ull];
				count += table[(a_value >> 12ull) & 15ull];
				count += table[(a_value >> 16ull) & 15ull];
				count += table[(a_value >> 20ull) & 15ull];
				count += table[(a_value >> 24ull) & 15ull];
				count += table[(a_value >> 28ull) & 15ull];
				count += table[(a_value >> 32ull) & 15ull];
				count += table[(a_value >> 36ull) & 15ull];
				count += table[(a_value >> 40ull) & 15ull];
				count += table[(a_value >> 44ull) & 15ull];
				count += table[(a_value >> 48ull) & 15ull];
				count += table[(a_value >> 52ull) & 15ull];
				count += table[(a_value >> 56ull) & 15ull];
				count += table[(a_value >> 60ull) & 15ull];
				return count;
			}
		};

		// POPCOUNT_LUT8

		template<>
		struct PopcountHelper<uint8_t, POPCOUNT_LUT8>
		{
			static inline size_t Execute(const uint8_t a_value) throw()
			{
				return GetPopcountLUT()[a_value];
			}
		};

		template<>
		struct PopcountHelper<uint16_t, POPCOUNT_LUT8>
		{
			static inline size_t Execute(const uint16_t a_value) throw()
			{
				const uint8_t* const table = GetPopcountLUT();
				size_t count = table[a_value & 255u];
				count += table[a_value >> 8u];
				return count;
			}
		};

		template<>
		struct PopcountHelper<uint32_t, POPCOUNT_LUT8>
		{
			static inline size_t Execute(const uint32_t a_value) throw()
			{
				const uint8_t* const table = GetPopcountLUT();
				size_t count = table[a_value & 255u];
				count += table[(a_value >> 8u) & 255u];
				count += table[(a_value >> 16u) & 255u];
				count += table[(a_value >> 24u) & 255u];
				return count;
			}
		};

		template<>
		struct PopcountHelper<uint64_t, POPCOUNT_LUT8>
		{
			static inline size_t Execute(const uint64_t a_value) throw()
			{
				const uint8_t* const table = GetPopcountLUT();
				size_t count = table[a_value & 255u];
				count += table[(a_value >> 8u) & 255u];
				count += table[(a_value >> 16u) & 255u];
				count += table[(a_value >> 24u) & 255u];
				count += table[(a_value >> 32u) & 255u];
				count += table[(a_value >> 40u) & 255u];
				count += table[(a_value >> 48u) & 255u];
				count += table[(a_value >> 56u) & 255u];
				return count;
			}
		};
	}

	/*!
	*	\brief Count the number of bits set to 1 in a primative numeric value.
	*	\tparam T The data type
	*	\tparam IMPLEMENTATION The implementation to use.
	*/
	template<class T, PopcountImplementation IMPLEMENTATION = POPCOUNT_DEFAULT>
	static ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount(T a_value) throw()
	{
		return detail::PopcountHelper<T, IMPLEMENTATION>::Execute(a_value);
	}

	/*!
	*	\brief Count the number of bits set to 0 in a primative numeric value.
	*	\tparam T The data type
	*	\tparam IMPLEMENTATION The implementation to use.
	*/
	template<class T, PopcountImplementation IMPLEMENTATION = POPCOUNT_DEFAULT>
	static ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount_inverse(T a_value) throw()
	{
		enum 
		{
			SIZE_BITS = sizeof(T) * 8u	//!< Number of bits in data type T.
		};
		
		return SIZE_BITS - detail::PopcountHelper<T, IMPLEMENTATION>::Execute(a_value);
	}

}

#endif
