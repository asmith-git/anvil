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
	#if ANVIL_MIN_INSTRUCTION_SET & ANVIL_ASM_BMI1
		#define ANVIL_HW_LZCNTA false
		#define ANVIL_HW_LZCNTB true
		#define ANVIL_HW_LZCNT_COMPILETIME true
	#else
		#define ANVIL_HW_LZCNTA true
		#define ANVIL_HW_LZCNTB false //anvil::AreInstructionSetSupported(anvil::ASM_BMI1)
		#define ANVIL_HW_LZCNT_COMPILETIME false
	#endif
#else
	#define ANVIL_HW_LZCNTA false
	#define ANVIL_HW_LZCNTB false
	#define ANVIL_HW_LZCNT_COMPILETIME true
#endif

namespace anvil
{

	enum LZCountImplementation
	{
		LZCNT_TEST,			//!< Unoptimised reference C++ implementation, for testing the output of the more optimised implementations.
		LZCNT_CPP,			//!< Optimised C++ implementation.
		LZCNT_CONSTEXPR,	//!< This implementation can be run at compile-time.
		LZCNT_BSR,			//!< This implementation uses the x86 BSR instruction, better compatibility with older CPUs than LZCNT.
		LZCNT_X86,			//!< This implementation uses the x86 LZCNT instruction, should be the fastest way to do this calculation.

		LZCNT_DEFAULT = ANVIL_HW_LZCNTB ? LZCNT_X86 : ANVIL_HW_LZCNTA ? LZCNT_BSR : LZCNT_CPP
	};

	namespace detail 
	{

		template<class T, LZCountImplementation IMPLEMENTATION>
		struct LZCountHelper
		{
			static ANVIL_STRONG_INLINE size_t Execute(const T a_value) throw()
			{
				if constexpr (std::is_unsigned<T>::value)
				{
					// Call the C++ implementation
					return LZCountHelper<T, LZCNT_CPP>::Execute(a_value);
				}
				else
				{
					// Call the unsigned version of this implementation
					typedef UnsignedType<T> UT;
					return LZCountHelper<UT, IMPLEMENTATION>::Execute(numeric_reinterpret_cast<UT>(a_value));
				}
			}
		};

		// LZCNT_TEST

		template<>
		struct LZCountHelper<uint8_t, LZCNT_TEST>
		{
			static inline size_t Execute(uint8_t a_value) throw()
			{
				if (a_value == 0u) return 8u;

				size_t count = 0u;
				while (true) {
					if (a_value & 1u) break;
					a_value >>= 1u;
					++count;
				}
				return count;
			}
		};

		template<>
		struct LZCountHelper<uint16_t, LZCNT_TEST>
		{
			static ANVIL_STRONG_INLINE size_t Execute(const uint16_t a_value) throw()
			{
				size_t count = LZCountHelper<uint8_t, LZCNT_TEST>::Execute(static_cast<uint8_t>(a_value & UINT8_MAX));
				if (count == 8u) count += LZCountHelper<uint8_t, LZCNT_TEST>::Execute(static_cast<uint8_t>(a_value >> 8u));
				return count;
			}
		};

		template<>
		struct LZCountHelper<uint32_t, LZCNT_TEST>
		{
			static ANVIL_STRONG_INLINE size_t Execute(const uint32_t a_value) throw()
			{
				size_t count = LZCountHelper<uint16_t, LZCNT_TEST>::Execute(static_cast<uint16_t>(a_value & UINT16_MAX));
				if (count == 16u) count += LZCountHelper<uint16_t, LZCNT_TEST>::Execute(static_cast<uint16_t>(a_value >> 16u));
				return count;
			}
		};

		template<>
		struct LZCountHelper<uint64_t, LZCNT_TEST>
		{
			static ANVIL_STRONG_INLINE size_t Execute(const uint64_t a_value) throw()
			{
				size_t count = LZCountHelper<uint32_t, LZCNT_TEST>::Execute(static_cast<uint32_t>(a_value & UINT32_MAX));
				if (count == 32u) count += LZCountHelper<uint32_t, LZCNT_TEST>::Execute(static_cast<uint32_t>(a_value >> 32ull));
				return count;
			}
		};

		// LZCNT_CONSTEXPR

		template<>
		struct LZCountHelper<uint8_t, LZCNT_CONSTEXPR>
		{
			static ANVIL_CONSTEXPR_FN size_t Execute(uint8_t a_value) throw()
			{
				if (a_value == 0u) return 8u;

				size_t count = 0u;
				while (true) {
					if (a_value & 1u) break;
					a_value >>= 1u;
					++count;
				}
				return count;
			}
		};

		template<>
		struct LZCountHelper<uint16_t, LZCNT_CONSTEXPR>
		{
			static ANVIL_CONSTEXPR_FN size_t Execute(const uint16_t a_value) throw()
			{
				size_t count = LZCountHelper<uint8_t, LZCNT_CONSTEXPR>::Execute(static_cast<uint8_t>(a_value & UINT8_MAX));
				if (count == 8u) count += LZCountHelper<uint8_t, LZCNT_CONSTEXPR>::Execute(static_cast<uint8_t>(a_value >> 8u));
				return count;
			}
		};

		template<>
		struct LZCountHelper<uint32_t, LZCNT_CONSTEXPR>
		{
			static ANVIL_CONSTEXPR_FN size_t Execute(const uint32_t a_value) throw()
			{
				size_t count = LZCountHelper<uint16_t, LZCNT_CONSTEXPR>::Execute(static_cast<uint16_t>(a_value & UINT16_MAX));
				if (count == 16u) count += LZCountHelper<uint16_t, LZCNT_CONSTEXPR>::Execute(static_cast<uint16_t>(a_value >> 16u));
				return count;
			}
		};

		template<>
		struct LZCountHelper<uint64_t, LZCNT_CONSTEXPR>
		{
			static ANVIL_CONSTEXPR_FN size_t Execute(const uint64_t a_value) throw()
			{
				size_t count = LZCountHelper<uint32_t, LZCNT_CONSTEXPR>::Execute(static_cast<uint32_t>(a_value & UINT32_MAX));
				if (count == 32u) count += LZCountHelper<uint32_t, LZCNT_CONSTEXPR>::Execute(static_cast<uint32_t>(a_value >> 32ull));
				return count;
			}
		};

		// LZCNT_CPP

		template<>
		struct LZCountHelper<uint8_t, LZCNT_CPP>
		{
			static inline size_t Execute(const uint8_t a_value) throw()
			{
				uint32_t x = a_value;
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
			}
		};

		template<>
		struct LZCountHelper<uint16_t, LZCNT_CPP>
		{
			static ANVIL_STRONG_INLINE size_t Execute(const uint16_t a_value) throw()
			{
				size_t count = LZCountHelper<uint8_t, LZCNT_CPP>::Execute(static_cast<uint8_t>(a_value & UINT8_MAX));
				if (count == 8u) count += LZCountHelper<uint8_t, LZCNT_CPP>::Execute(static_cast<uint8_t>(a_value >> 8u));
				return count;
			}
		};

		template<>
		struct LZCountHelper<uint32_t, LZCNT_CPP>
		{
			static ANVIL_STRONG_INLINE size_t Execute(const uint32_t a_value) throw()
			{
				size_t count = LZCountHelper<uint16_t, LZCNT_CPP>::Execute(static_cast<uint16_t>(a_value & UINT16_MAX));
				if (count == 16u) count += LZCountHelper<uint16_t, LZCNT_CPP>::Execute(static_cast<uint16_t>(a_value >> 16u));
				return count;
			}
		};

		template<>
		struct LZCountHelper<uint64_t, LZCNT_CPP>
		{
			static ANVIL_STRONG_INLINE size_t Execute(const uint64_t a_value) throw()
			{
				size_t count = LZCountHelper<uint32_t, LZCNT_CPP>::Execute(static_cast<uint32_t>(a_value & UINT32_MAX));
				if (count == 32u) count += LZCountHelper<uint32_t, LZCNT_CPP>::Execute(static_cast<uint32_t>(a_value >> 32ull));
				return count;
			}
		};

		
		// LZCNT_BSR

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64

		template<>
		struct LZCountHelper<uint8_t, LZCNT_BSR>
		{
			static ANVIL_STRONG_INLINE size_t Execute(const uint8_t a_value) throw()
			{
				if (a_value == 0u) return 8u;
				unsigned long idx = 0;

				// Mask so only the least signficant bit remains
				uint32_t val32 = a_value;
				val32 &= val32 ^ (val32 - 1u);

				// Find the most significant bit
				_BitScanReverse(&idx, val32);

				return idx;
			}
		};

		template<>
		struct LZCountHelper<uint16_t, LZCNT_BSR>
		{
			static ANVIL_STRONG_INLINE size_t Execute(const uint16_t a_value) throw()
			{
				if (a_value == 0u) return 16u;
				unsigned long idx = 0;

				// Mask so only the least signficant bit remains
				uint32_t val32 = a_value;
				val32 &= val32 ^ (val32 - 1u);

				// Find the most significant bit
				_BitScanReverse(&idx, val32);

				return idx;
			}
		};

		template<>
		struct LZCountHelper<uint32_t, LZCNT_BSR>
		{
			static ANVIL_STRONG_INLINE size_t Execute(uint32_t a_value) throw()
			{
				if (a_value == 0u) return 32u;
				unsigned long idx = 0;

				// Mask so only the least signficant bit remains
				a_value &= a_value ^ (a_value - 1u);

				// Find the most significant bit
				_BitScanReverse(&idx, a_value);

				return idx;
			}
		};

		template<>
		struct LZCountHelper<uint64_t, LZCNT_BSR>
		{
			static ANVIL_STRONG_INLINE size_t Execute(uint64_t a_value) throw()
			{
				#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
					if (a_value == 0u) return 64u;
					unsigned long idx = 0;

					// Mask so only the least signficant bit remains
					a_value &= a_value ^ (a_value - 1ull);

					// Find the most significant bit
					_BitScanReverse64(&idx, a_value);

					return idx;
				#else
					size_t count = LZCountHelper<uint32_t, LZCNT_BSR>::Execute(static_cast<uint32_t>(a_value & UINT32_MAX));
					if (count == 32u) count += LZCountHelper<uint32_t, LZCNT_BSR>::Execute(static_cast<uint32_t>(a_value >> 32ull));
					return count;
				#endif
			}
		};

		// LZCNT_X86

		template<>
		struct LZCountHelper<uint8_t, LZCNT_X86>
		{
			static ANVIL_STRONG_INLINE size_t Execute(const uint8_t a_value) throw()
			{
				if (a_value == 0u) return 8u;
				return __lzcnt16(a_value);
			}
		};

		template<>
		struct LZCountHelper<uint16_t, LZCNT_X86>
		{
			static ANVIL_STRONG_INLINE size_t Execute(const uint16_t a_value) throw()
			{
				if (a_value == 0u) return 16u;
				return __lzcnt16(a_value);
			}
		};

		template<>
		struct LZCountHelper<uint32_t, LZCNT_X86>
		{
			static ANVIL_STRONG_INLINE size_t Execute(const uint32_t a_value) throw()
			{
				if (a_value == 0u) return 32u;
				#if ANVIL_COMPILER == ANVIL_MSVC
					return __lzcnt(a_value);
				#else
					return _lzcnt_u32(a_value);
				#endif
			}
		};

		template<>
		struct LZCountHelper<uint64_t, LZCNT_X86>
		{
			static ANVIL_STRONG_INLINE size_t Execute(const uint64_t a_value) throw()
			{
				#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
					if (a_value == 0u) return 64u;
					return __lzcnt64(a_value);
				#else
					size_t count = LZCountHelper<uint32_t, LZCNT_X86>::Execute(static_cast<uint32_t>(a_value & UINT32_MAX));
					if (count == 32u) count += LZCountHelper<uint32_t, LZCNT_X86>::Execute(static_cast<uint32_t>(a_value >> 32ull));
					return count;
				#endif
			}
		};

#endif

	}

	/*!
	*	\brief Count the number of leading bits set to 0
	*	\tparam T The data type
	*	\tparam BRANCHING True if function should be inlined with a conditional branch, false for a function pointer call.
	*	\tparam IMPLEMENTATION Which implementation to use
	*/
	template<class T, LZCountImplementation IMPLEMENTATION = LZCNT_DEFAULT>
	static ANVIL_STRONG_INLINE size_t ANVIL_CALL lzcount(T a_value) throw()
	{
		return detail::LZCountHelper<T, IMPLEMENTATION>::Execute(a_value);
	}

}

#endif