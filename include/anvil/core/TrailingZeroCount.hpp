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

namespace anvil
{

	enum TZCountImplementation
	{
		TZCNT_TEST,			//!< Unoptimised reference C++ implementation, for testing the output of the more optimised implementations.
		TZCNT_CPP,			//!< Optimised C++ implementation.
		TZCNT_CONSTEXPR,	//!< This implementation can be run at compile-time.
		TZCNT_BSR,			//!< This implementation uses the x86 BSR instruction, better compatibility with older CPUs than TZCNT.
		TZCNT_X86,			//!< This implementation uses the x86 TZCNT instruction, should be the fastest way to do this calculation.

		TZCNT_DEFAULT = ANVIL_HW_TZCNTB ? TZCNT_X86 : ANVIL_HW_TZCNTA ? TZCNT_BSR : TZCNT_CPP
	};

	namespace detail 
	{

		template<class T, TZCountImplementation IMPLEMENTATION>
		struct TZCountHelper
		{
			static ANVIL_STRONG_INLINE size_t Execute(const T a_value) throw()
			{
				if constexpr (std::is_unsigned<T>::value)
				{
					if constexpr (sizeof(T) == 1u)
					{
						// Call the 32-bit implementation
						return TZCountHelper<uint32_t, IMPLEMENTATION>::Execute(static_cast<uint32_t>(a_value)) - 24u;
					}
					else if constexpr (sizeof(T) == 2u)
					{
						// Call the 32-bit implementation
						return TZCountHelper<uint32_t, IMPLEMENTATION>::Execute(static_cast<uint32_t>(a_value)) - 16u;
					}
					else if constexpr (sizeof(T) == 8u)
					{
						// Call the 32-bit implementation
						size_t count = TZCountHelper<uint32_t, IMPLEMENTATION>::Execute(static_cast<uint32_t>(a_value >> 32ull));
						if (count == 32u) count += TZCountHelper<uint32_t, IMPLEMENTATION>::Execute(static_cast<uint32_t>(a_value & UINT32_MAX));
						return count;
					}
					else
					{
						// Call the C++ implementation
						return TZCountHelper<T, TZCNT_CPP>::Execute(a_value);
					}
				}
				else
				{
					// Call the unsigned version of this implementation
					typedef UnsignedType<T> UT;
					return TZCountHelper<UT, IMPLEMENTATION>::Execute(numeric_reinterpret_cast<UT>(a_value));
				}
			}
		};

		// TZCNT_TEST

		template<>
		struct TZCountHelper<uint32_t, TZCNT_TEST>
		{
			static ANVIL_STRONG_INLINE size_t Execute(uint32_t a_value) throw()
			{
				enum : uint64_t 
				{
					FLAG = 1ull << 31ull
				};

				if (a_value == 0u) return 32u;

				size_t result = 0u;
				for (int i = 0; i < 64; ++i) {
					if (a_value & FLAG) break;
					a_value <<= 1ull;
					++result;
				}

				return result;
			}
		};

		// TZCNT_CONSTEXPR

		template<>
		struct TZCountHelper<uint8_t, TZCNT_CONSTEXPR>
		{
			static ANVIL_CONSTEXPR_FN size_t Execute(const uint8_t a_value) throw()
			{
				uint32_t x = a_value;

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
		};

		template<>
		struct TZCountHelper<uint16_t, TZCNT_CONSTEXPR>
		{
			static ANVIL_CONSTEXPR_FN size_t Execute(const uint16_t a_value) throw()
			{
				size_t count = TZCountHelper<uint8_t, TZCNT_CONSTEXPR>::Execute(static_cast<uint8_t>(a_value >> 8ull));
				if (count == 8u) count += TZCountHelper<uint8_t, TZCNT_CONSTEXPR>::Execute(static_cast<uint8_t>(a_value & UINT8_MAX));
				return count;
			}
		};

		template<>
		struct TZCountHelper<uint32_t, TZCNT_CONSTEXPR>
		{
			static ANVIL_CONSTEXPR_FN size_t Execute(const uint32_t a_value) throw()
			{
				size_t count = TZCountHelper<uint16_t, TZCNT_CONSTEXPR>::Execute(static_cast<uint16_t>(a_value >> 16ull));
				if (count == 16u) count += TZCountHelper<uint16_t, TZCNT_CONSTEXPR>::Execute(static_cast<uint16_t>(a_value & UINT16_MAX));
				return count;
			}
		};

		template<>
		struct TZCountHelper<uint64_t, TZCNT_CONSTEXPR>
		{
			static ANVIL_CONSTEXPR_FN size_t Execute(const uint64_t a_value) throw()
			{
				size_t count = TZCountHelper<uint32_t, TZCNT_CONSTEXPR>::Execute(static_cast<uint32_t>(a_value >> 32ull));
				if (count == 32u) count += TZCountHelper<uint32_t, TZCNT_CONSTEXPR>::Execute(static_cast<uint32_t>(a_value & UINT32_MAX));
				return count;
			}
		};

		// TZCNT_CPP

		template<>
		struct TZCountHelper<uint8_t, TZCNT_CPP>
		{
			static inline size_t Execute(const uint8_t a_value) throw()
			{
				uint32_t x = a_value;

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
		};

		template<>
		struct TZCountHelper<uint16_t, TZCNT_CPP>
		{
			static ANVIL_STRONG_INLINE size_t Execute(const uint16_t a_value) throw()
			{
				size_t count = TZCountHelper<uint8_t, TZCNT_CPP>::Execute(static_cast<uint8_t>(a_value >> 8ull));
				if (count == 8u) count += TZCountHelper<uint8_t, TZCNT_CPP>::Execute(static_cast<uint8_t>(a_value & UINT8_MAX));
				return count;
			}
		};

		template<>
		struct TZCountHelper<uint32_t, TZCNT_CPP>
		{
			static ANVIL_STRONG_INLINE size_t Execute(const uint32_t a_value) throw()
			{
				size_t count = TZCountHelper<uint16_t, TZCNT_CPP>::Execute(static_cast<uint16_t>(a_value >> 16ull));
				if (count == 16u) count += TZCountHelper<uint16_t, TZCNT_CPP>::Execute(static_cast<uint16_t>(a_value & UINT16_MAX));
				return count;
			}
		};

		template<>
		struct TZCountHelper<uint64_t, TZCNT_CPP>
		{
			static ANVIL_STRONG_INLINE size_t Execute(const uint64_t a_value) throw()
			{
				size_t count = TZCountHelper<uint32_t, TZCNT_CPP>::Execute(static_cast<uint32_t>(a_value >> 32ull));
				if (count == 32u) count += TZCountHelper<uint32_t, TZCNT_CPP>::Execute(static_cast<uint32_t>(a_value & UINT32_MAX));
				return count;
			}
		};

		
		// TZCNT_BSR

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64

		template<>
		struct TZCountHelper<uint32_t, TZCNT_BSR>
		{
			static ANVIL_STRONG_INLINE size_t Execute(uint32_t a_value) throw()
			{
				if (a_value == 0u) return 32u;
				unsigned long idx = 0;

				// Find the most significant bit
				_BitScanReverse(&idx, a_value);

				return 31 - idx;
			}
		};

		template<>
		struct TZCountHelper<uint64_t, TZCNT_BSR>
		{
			static ANVIL_STRONG_INLINE size_t Execute(uint64_t a_value) throw()
			{
				#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
					if (a_value == 0u) return 64u;
					unsigned long idx = 0;

					// Find the most significant bit
					_BitScanReverse64(&idx, a_value);

					return 63 - idx;
				#else
					size_t count = TZCountHelper<uint32_t, TZCNT_BSR>::Execute(static_cast<uint32_t>(a_value >> 32ull));
					if (count == 32u) count += TZCountHelper<uint32_t, TZCNT_BSR>::Execute(static_cast<uint32_t>(a_value & UINT32_MAX));
					return count;
				#endif
			}
		};

		// TZCNT_X86

		template<>
		struct TZCountHelper<uint8_t, TZCNT_X86>
		{
			static ANVIL_STRONG_INLINE size_t Execute(const uint8_t a_value) throw()
			{
				if (a_value == 0u) return 8u;
				return _tzcnt_u32(static_cast<uint32_t>(a_value) << 24u);
			}
		};

		template<>
		struct TZCountHelper<uint16_t, TZCNT_X86>
		{
			static ANVIL_STRONG_INLINE size_t Execute(const uint16_t a_value) throw()
			{
				if (a_value == 0u) return 16u;
				return _tzcnt_u32(static_cast<uint32_t>(a_value) << 16u);
			}
		};

		template<>
		struct TZCountHelper<uint32_t, TZCNT_X86>
		{
			static ANVIL_STRONG_INLINE size_t Execute(const uint32_t a_value) throw()
			{
				if (a_value == 0u) return 32u;
				//return _tzcnt_u32(a_value);
				return _tzcnt_u32(a_value);
			}
		};

		template<>
		struct TZCountHelper<uint64_t, TZCNT_X86>
		{
			static ANVIL_STRONG_INLINE size_t Execute(const uint64_t a_value) throw()
			{
				#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
					if (a_value == 0u) return 64u;
					return _tzcnt_u64(a_value);
				#else
					size_t count = TZCountHelper<uint32_t, TZCNT_X86>::Execute(static_cast<uint32_t>(a_value >> 32ull));
					if (count == 32u) count += TZCountHelper<uint32_t, TZCNT_X86>::Execute(static_cast<uint32_t>(a_value & UINT32_MAX));
					return count;
				#endif
			}
		};

#endif

	}

	/*!
	*	\brief Count the number of trailing bits set to 0
	*	\tparam T The data type
	*	\tparam BRANCHING True if function should be inlined with a conditional branch, false for a function pointer call.
	*	\tparam IMPLEMENTATION Which implementation to use
	*/
	template<class T, TZCountImplementation IMPLEMENTATION = TZCNT_DEFAULT>
	static ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount(T a_value) throw()
	{
		return detail::TZCountHelper<T, IMPLEMENTATION>::Execute(a_value);
	}

}

#endif