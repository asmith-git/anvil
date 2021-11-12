//Copyright 2019 Adam G. Smith
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

#ifndef ANVIL_CORE_ARITHMETIC_HPP
#define ANVIL_CORE_ARITHMETIC_HPP

#include <cstdint>
#include "anvil/core/Assert.hpp"
#include "anvil/core/CpuRuntime.hpp"
#include "anvil/core/Keywords.hpp"

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
#include <nmmintrin.h>
#include <immintrin.h>
#include <ammintrin.h>
#include <intrin.h>
#endif

namespace anvil {

	// BitAnd

	template<class T>
	static ANVIL_STRONG_INLINE T BitAnd(const T lhs, const T rhs) throw() {
		return lhs & rhs;
	}

	template<>
	static ANVIL_STRONG_INLINE float BitAnd(const float lhs, const float rhs) throw() {
		union Union {
			uint32_t u;
			float f;
		};
		Union a, b;
		a.f = lhs;
		b.f = rhs;
		a.u &= b.u;
		return a.f;
	}

	template<>
	static ANVIL_STRONG_INLINE double BitAnd(const double lhs, const double rhs) throw() {
		union Union {
			uint64_t u;
			double f;
		};
		Union a, b;
		a.f = lhs;
		b.f = rhs;
		a.u &= b.u;
		return a.f;
	}

	// BitOr

	template<class T>
	static ANVIL_STRONG_INLINE T BitOr(const T lhs, const T rhs) throw() {
		return lhs | rhs;
	}

	template<>
	static ANVIL_STRONG_INLINE float BitOr(const float lhs, const float rhs) throw() {
		union Union {
			uint32_t u;
			float f;
		};
		Union a, b;
		a.f = lhs;
		b.f = rhs;
		a.u |= b.u;
		return a.f;
	}

	template<>
	static ANVIL_STRONG_INLINE double BitOr(const double lhs, const double rhs) throw() {
		union Union {
			uint64_t u;
			double f;
		};
		Union a, b;
		a.f = lhs;
		b.f = rhs;
		a.u |= b.u;
		return a.f;
	}

	// BitXor

	template<class T>
	static ANVIL_STRONG_INLINE T BitXor(const T lhs, const T rhs) throw() {
		return lhs | rhs;
	}

	template<>
	static ANVIL_STRONG_INLINE float BitXor(const float lhs, const float rhs) throw() {
		union Union {
			uint32_t u;
			float f;
		};
		Union a, b;
		a.f = lhs;
		b.f = rhs;
		a.u ^= b.u;
		return a.f;
	}

	template<>
	static ANVIL_STRONG_INLINE double BitXor(const double lhs, const double rhs) throw() {
		union Union {
			uint64_t u;
			double f;
		};
		Union a, b;
		a.f = lhs;
		b.f = rhs;
		a.u ^= b.u;
		return a.f;
	}

	// BitNot

	template<class T>
	static ANVIL_STRONG_INLINE T BitNot(const T value) throw() {
		return ~value;
	}

	template<>
	static ANVIL_STRONG_INLINE float BitNot(const float value) throw() {
		union {
			uint32_t u;
			float f;
		};
		f = value;
		u = ~u;
		return f;
	}

	template<>
	static ANVIL_STRONG_INLINE double BitNot(const double value) throw() {
		union {
			uint64_t u;
			double f;
		};
		f = value;
		u = ~u;
		return f;
	}

	// IsOdd

	static ANVIL_STRONG_INLINE bool IsOdd(const uint64_t value) throw() {
		return (value & 1ull) == 1ull;
	}

	static ANVIL_STRONG_INLINE bool IsOdd(const uint32_t value) throw() {
		return (value & 1u) == 1u;
	}

	static ANVIL_STRONG_INLINE bool IsOdd(const uint16_t value) throw() {
		return (value & 1u) == 1u;
	}

	static ANVIL_STRONG_INLINE bool IsOdd(const uint8_t value) throw() {
		return (value & 1u) == 1u;
	}

	static ANVIL_STRONG_INLINE bool IsOdd(const int64_t value) throw() {
		return (value & 1ll) == 1ll;
	}

	static ANVIL_STRONG_INLINE bool IsOdd(const int32_t value) throw() {
		return (value & 1) == 1;
	}

	static ANVIL_STRONG_INLINE bool IsOdd(const int16_t value) throw() {
		return (value & 1) == 1;
	}

	static ANVIL_STRONG_INLINE bool IsOdd(const int8_t value) throw() {
		return (value & 1) == 1;
	}

	static ANVIL_STRONG_INLINE bool IsOdd(const float value) throw() {
		return IsOdd(static_cast<NativeSigned>(value));
	}

	static ANVIL_STRONG_INLINE bool IsOdd(const double value) throw() {
		return IsOdd(static_cast<NativeSigned>(value));
	}

	// IsEven

	static ANVIL_STRONG_INLINE bool IsEvent(const uint64_t value) throw() {
		return (value & 1ull) == 0ull;
	}

	static ANVIL_STRONG_INLINE bool IsEvent(const uint32_t value) throw() {
		return (value & 1u) == 0u;
	}

	static ANVIL_STRONG_INLINE bool IsEvent(const uint16_t value) throw() {
		return (value & 1u) == 0u;
	}

	static ANVIL_STRONG_INLINE bool IsEven(const uint8_t value) throw() {
		return (value & 1u) == 0u;
	}

	static ANVIL_STRONG_INLINE bool IsEven(const int64_t value) throw() {
		return (value & 1ll) == 0ll;
	}

	static ANVIL_STRONG_INLINE bool IsEven(const int32_t value) throw() {
		return (value & 1) == 0;
	}

	static ANVIL_STRONG_INLINE bool IsEven(const int16_t value) throw() {
		return (value & 1) == 0;
	}

	static ANVIL_STRONG_INLINE bool IsEven(const int8_t value) throw() {
		return (value & 1) == 0;
	}

	static ANVIL_STRONG_INLINE bool IsEven(const float value) throw() {
		return IsEven(static_cast<NativeSigned>(value));
	}

	static ANVIL_STRONG_INLINE bool IsEven(const double value) throw() {
		return IsEven(static_cast<NativeSigned>(value));
	}

	// RoundUpOdd

	static ANVIL_STRONG_INLINE uint64_t RoundUpOdd(const uint64_t value) throw() {
		return value | 1ull;
	}

	static ANVIL_STRONG_INLINE uint32_t RoundUpOdd(const uint32_t value) throw() {
		return value | 1u;
	}

	static ANVIL_STRONG_INLINE uint16_t RoundUpOdd(const uint16_t value) throw() {
		return value | 1u;
	}

	static ANVIL_STRONG_INLINE uint8_t RoundUpOdd(const uint8_t value) throw() {
		return value | 1u;
	}

	static ANVIL_STRONG_INLINE int64_t RoundUpOdd(const int64_t value) throw() {
		return value | 1ll;
	}

	static ANVIL_STRONG_INLINE int32_t RoundUpOdd(const int32_t value) throw() {
		return value | 1;
	}

	static ANVIL_STRONG_INLINE int16_t RoundUpOdd(const int16_t value) throw() {
		return value | 1;
	}

	static ANVIL_STRONG_INLINE int8_t RoundUpOdd(const int8_t value) throw() {
		return value | 1;
	}

	static ANVIL_STRONG_INLINE float RoundUpOdd(const float value) throw() {
		return static_cast<float>(RoundUpOdd(static_cast<NativeSigned>(value)));
	}

	static ANVIL_STRONG_INLINE double RoundUpOdd(const double value) throw() {
		return static_cast<double>(RoundUpOdd(static_cast<NativeSigned>(value)));
	}

	// RoundDownOdd

	static ANVIL_STRONG_INLINE uint64_t RoundDownOdd(const uint64_t value) throw() {
		enum : uint64_t { MASK = ~1ull };
		return value & MASK;
	}

	static ANVIL_STRONG_INLINE uint32_t RoundDownOdd(const uint32_t value) throw() {
		enum : uint32_t { MASK = ~1u };
		return value & MASK;
	}

	static ANVIL_STRONG_INLINE uint16_t RoundDownOdd(const uint16_t value) throw() {
		enum : uint16_t { MASK = static_cast<uint16_t>(~1u) };
		return value & MASK;
	}

	static ANVIL_STRONG_INLINE uint8_t RoundDownOdd(const uint8_t value) throw() {
		enum : uint8_t { MASK = static_cast<uint8_t>(~1u) };
		return value & MASK;
	}

	static ANVIL_STRONG_INLINE int64_t RoundDownOdd(const int64_t value) throw() {
		enum : int64_t { MASK = ~1ll };
		return value & MASK;
	}

	static ANVIL_STRONG_INLINE int32_t RoundDownOdd(const int32_t value) throw() {
		enum : int32_t { MASK = ~1 };
		return value & MASK;
	}

	static ANVIL_STRONG_INLINE int16_t RoundDownOdd(const int16_t value) throw() {
		enum : int16_t { MASK = ~1 };
		return value & MASK;
	}

	static ANVIL_STRONG_INLINE int8_t RoundDownOdd(const int8_t value) throw() {
		enum : int8_t { MASK = ~1 };
		return value & MASK;
	}

	static ANVIL_STRONG_INLINE float RoundDownOdd(const float value) throw() {
		return static_cast<float>(RoundDownOdd(static_cast<NativeSigned>(value)));
	}

	static ANVIL_STRONG_INLINE double RoundDownOdd(const double value) throw() {
		return static_cast<double>(RoundDownOdd(static_cast<NativeSigned>(value)));
	}

	// RoundUpEven

	static ANVIL_STRONG_INLINE uint64_t RoundUpEven(const uint64_t value) throw() {
		return value + (value & 1ull);
	}

	static ANVIL_STRONG_INLINE uint32_t RoundUpEven(const uint32_t value) throw() {
		return value + (value & 1u);
	}

	static ANVIL_STRONG_INLINE uint16_t RoundUpEven(const uint16_t value) throw() {
		return value + (value & 1u);
	}

	static ANVIL_STRONG_INLINE uint8_t RoundUpEven(const uint8_t value) throw() {
		return value + (value & 1u);
	}

	static ANVIL_STRONG_INLINE int64_t RoundUpEven(const int64_t value) throw() {
		return value + (value & 1ll);
	}

	static ANVIL_STRONG_INLINE int32_t RoundUpEven(const int32_t value) throw() {
		return value + (value & 1);
	}

	static ANVIL_STRONG_INLINE int16_t RoundUpEven(const int16_t value) throw() {
		return value + (value & 1);
	}

	static ANVIL_STRONG_INLINE int8_t RoundUpEven(const int8_t value) throw() {
		return value + (value & 1);
	}

	static ANVIL_STRONG_INLINE float RoundUpEven(const float value) throw() {
		return static_cast<float>(RoundUpEven(static_cast<NativeSigned>(value)));
	}

	static ANVIL_STRONG_INLINE double RoundUpEven(const double value) throw() {
		return static_cast<double>(RoundUpEven(static_cast<NativeSigned>(value)));
	}

	// RoundDownEven

	static ANVIL_STRONG_INLINE uint64_t RoundDownEven(const uint64_t value) throw() {
		return value - (value & 1ull);
	}

	static ANVIL_STRONG_INLINE uint32_t RoundDownEven(const uint32_t value) throw() {
		return value - (value & 1u);
	}

	static ANVIL_STRONG_INLINE uint16_t RoundDownEven(const uint16_t value) throw() {
		return value - (value & 1u);
	}

	static ANVIL_STRONG_INLINE uint8_t RoundDownEven(const uint8_t value) throw() {
		return value - (value & 1u);
	}

	static ANVIL_STRONG_INLINE int64_t RoundDownEven(const int64_t value) throw() {
		return value - (value & 1ll);
	}

	static ANVIL_STRONG_INLINE int32_t RoundDownEven(const int32_t value) throw() {
		return value - (value & 1);
	}

	static ANVIL_STRONG_INLINE int16_t RoundDownEven(const int16_t value) throw() {
		return value - (value & 1);
	}

	static ANVIL_STRONG_INLINE int8_t RoundDownEven(const int8_t value) throw() {
		return value - (value & 1);
	}

	static ANVIL_STRONG_INLINE float RoundDownEven(const float value) throw() {
		return static_cast<float>(RoundDownEven(static_cast<NativeSigned>(value)));
	}

	static ANVIL_STRONG_INLINE double RoundDownEven(const double value) throw() {
		return static_cast<double>(RoundDownEven(static_cast<NativeSigned>(value)));
	}

	// PopulationCount

	namespace detail {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		static ANVIL_STRONG_INLINE size_t PopulationCount64_X86(const uint64_t value) throw() {
			return static_cast<size_t>(_mm_popcnt_u64(value));
		}
#endif


#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		static ANVIL_STRONG_INLINE size_t PopulationCount32_X86(const uint32_t value) throw() {
			return static_cast<size_t>(_mm_popcnt_u32(value));
		}
#endif
	}

	static size_t PopulationCount(const uint64_t value) throw() {
#if ANVIL_CPU_ARCHITECTURE_BITS >= 64
	#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
			// Technically POPCNT flag on Intel and ABM flag on AMD CPUs, but SSE 4.2 is a close approximation
			if constexpr ((ASM_MINIMUM & ASM_POPCNT) != 0ull) {
				return detail::PopulationCount64_X86(value);
			} 
	#endif
			uint64_t b = value;
			// Based on implementation : https://rosettacode.org/wiki/Population_count#C
			b -= (b >> 1) & 0x5555555555555555ull;
			b = (b & 0x3333333333333333ull) + ((b >> 2ull) & 0x3333333333333333ull);
			b = (b + (b >> 4ull)) & 0x0f0f0f0f0f0f0f0full;
			b = (b * 0x0101010101010101ull) >> 56ull;
			ANVIL_ASSUME(b <= 64ull);
			return static_cast<size_t>(b);
#else
		const uint32_t low = reinterpret_cast<const uint32_t*>(&value)[0u];
		const uint32_t high = reinterpret_cast<const uint32_t*>(&value)[1u];
		return PopulationCount(static_cast<uint32_t>(low)) + PopulationCount(static_cast<uint32_t>(high));
#endif
	}

	static size_t PopulationCount(const uint32_t value) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		// Technically POPCNT flag on Intel and ABM flag on AMD CPUs, but SSE 4.2 is a close approximation
		if constexpr ((ASM_MINIMUM & ASM_POPCNT) != 0ull) {
			return detail::PopulationCount32_X86(value);
		}
#endif
		// Based on implementation : https://rosettacode.org/wiki/Population_count#C
		uint32_t b = value;
		b -= (b >> 1) & 0x55555555u;
		b = (b & 0x33333333u) + ((b >> 2u) & 0x33333333u);
		b = (b + (b >> 4u)) & 0x0f0f0f0fu;
		b = (b * 0x01010101u) >> 24u;
		ANVIL_ASSUME(b <= 32u);
		return static_cast<size_t>(b);
	}

	static ANVIL_STRONG_INLINE size_t PopulationCount(const uint16_t value) throw() {
		const size_t tmp = PopulationCount(static_cast<uint32_t>(value));
		ANVIL_ASSUME(tmp <= 16u);
		return tmp;
	}

	static ANVIL_STRONG_INLINE size_t PopulationCount(const uint8_t value) throw() {
		const size_t tmp = PopulationCount(static_cast<uint32_t>(value));
		ANVIL_ASSUME(tmp <= 8u);
		return tmp;
	}

	static ANVIL_STRONG_INLINE size_t PopulationCount(const int64_t value) throw() {
		union {
			uint64_t u;
			int64_t s;
		};
		s = value;
		return PopulationCount(u);
	}

	static ANVIL_STRONG_INLINE size_t PopulationCount(const int32_t value) throw() {
		union {
			uint32_t u;
			int32_t s;
		};
		s = value;
		return PopulationCount(u);
	}

	static ANVIL_STRONG_INLINE size_t PopulationCount(const int16_t value) throw() {
		union {
			uint16_t u;
			int16_t s;
		};
		s = value;
		return PopulationCount(u);
	}

	static ANVIL_STRONG_INLINE size_t PopulationCount(const int8_t value) throw() {
		union {
			uint8_t u;
			int8_t s;
		};
		s = value;
		return PopulationCount(u);
	}

	static ANVIL_STRONG_INLINE size_t PopulationCount(const float value) throw() {
		union {
			uint32_t u;
			float f;
		};
		f = value;
		return PopulationCount(u);
	}

	static ANVIL_STRONG_INLINE size_t PopulationCount(const double value) throw() {
		union {
			uint64_t u;
			double f;
		};
		f = value;
		return PopulationCount(u);
	}

	static size_t PopulationCount(const void* src, const size_t bytes) throw() {
		size_t count = 0u;

		const size_t aligned_size = bytes / sizeof(NativeUnsigned);
		const NativeUnsigned* src1 = static_cast<const NativeUnsigned*>(src);
		const NativeUnsigned* const end1 = src1 + aligned_size;
		while (src1 != end1) {
			count += PopulationCount(*src1);
			++src1;
		}

		const size_t aligned_size_bytes = aligned_size * sizeof(NativeUnsigned);
		if (aligned_size_bytes != bytes) {
			const size_t unaligned_size_bytes = (bytes - aligned_size_bytes);
			const uint8_t* src2 = reinterpret_cast<const uint8_t*>(end1);
			const uint8_t* const end2 = src2 + unaligned_size_bytes;
			while (src2 != end2) {
				count += PopulationCount(*src2);
				++src2;
			}
		}

		return count;
	}

	// CountOnes

	template<class T>
	static ANVIL_STRONG_INLINE size_t CountOnes(const T value) throw() {
		return PopulationCount(value);
	}

	static ANVIL_STRONG_INLINE size_t CountOnes(const void* src, const size_t bytes) throw() {
		return PopulationCount(src, bytes);
	}

	// CountZeros

	template<class T>
	static ANVIL_STRONG_INLINE size_t CountZeros(const T value) throw() {
		return PopulationCount(BitNot<T>(value));
	}

	static size_t CountZeros(const void* src, const size_t bytes) throw() {
		size_t count = 0u;

		const size_t aligned_size = bytes / sizeof(NativeUnsigned);
		const NativeUnsigned* src1 = static_cast<const NativeUnsigned*>(src);
		const NativeUnsigned* const end1 = src1 + aligned_size;
		while (src1 != end1) {
			count += CountZeros<NativeUnsigned>(*src1);
			++src1;
		}

		const size_t aligned_size_bytes = aligned_size * sizeof(NativeUnsigned);
		if (aligned_size_bytes != bytes) {
			const size_t unaligned_size_bytes = (bytes - aligned_size_bytes);
			const uint8_t* src2 = reinterpret_cast<const uint8_t*>(end1);
			const uint8_t* const end2 = src2 + unaligned_size_bytes;
			while (src2 != end2) {
				count += CountZeros<uint8_t>(*src2);
				++src2;
			}
		}

		return count;
	}

	// AllZeros

	static ANVIL_STRONG_INLINE bool AllZeros(const uint64_t value) throw() {
		return value == 0u;
	}

	static ANVIL_STRONG_INLINE bool AllZeros(const uint32_t value) throw() {
		return value == 0u;
	}

	static ANVIL_STRONG_INLINE bool AllZeros(const uint16_t value) throw() {
		return value == 0u;
	}

	static ANVIL_STRONG_INLINE bool AllZeros(const uint8_t value) throw() {
		return value == 0u;
	}

	static ANVIL_STRONG_INLINE bool AllZeros(const int64_t value) throw() {
		return value == 0;
	}

	static ANVIL_STRONG_INLINE bool AllZeros(const int32_t value) throw() {
		return value == 0;
	}

	static ANVIL_STRONG_INLINE bool AllZeros(const int16_t value) throw() {
		return value == 0;
	}

	static ANVIL_STRONG_INLINE bool AllZeros(const int8_t value) throw() {
		return value == 0;
	}

	static ANVIL_STRONG_INLINE bool AllZeros(const float value) throw() {
		return value == 0.f;
	}

	static ANVIL_STRONG_INLINE bool AllZeros(const double value) throw() {
		return value == 0.0;
	}

	static bool AllZeros(const void* src, const size_t bytes) throw() {
		const size_t aligned_size = bytes / sizeof(NativeUnsigned);
		const NativeUnsigned* src1 = static_cast<const NativeUnsigned*>(src);
		const NativeUnsigned* const end1 = src1 + aligned_size;
		while (src1 != end1) {
			if(!AllZeros(*src1)) return false;
			++src1;
		}

		const size_t aligned_size_bytes = aligned_size * sizeof(NativeUnsigned);
		if (aligned_size_bytes != bytes) {
			const size_t unaligned_size_bytes = (bytes - aligned_size_bytes);
			const uint8_t* src2 = reinterpret_cast<const uint8_t*>(end1);
			const uint8_t* const end2 = src2 + unaligned_size_bytes;
			while (src2 != end2) {
				if (!AllZeros(*src2)) return false;
				++src2;
			}
		}

		return true;
	}

	// AllOnes

	static ANVIL_STRONG_INLINE bool AllOnes(const uint64_t value) throw() {
		return value == UINT64_MAX;
	}

	static ANVIL_STRONG_INLINE bool AllOnes(const uint32_t value) throw() {
		return value == UINT32_MAX;
	}

	static ANVIL_STRONG_INLINE bool AllOnes(const uint16_t value) throw() {
		return value == UINT16_MAX;
	}

	static ANVIL_STRONG_INLINE bool AllOnes(const uint8_t value) throw() {
		return value == UINT8_MAX;
	}

	static ANVIL_STRONG_INLINE bool AllOnes(const int64_t value) throw() {
		return value == -1;
	}

	static ANVIL_STRONG_INLINE bool AllOnes(const int32_t value) throw() {
		return value == -1;
	}

	static ANVIL_STRONG_INLINE bool AllOnes(const int16_t value) throw() {
		return value == -1;
	}

	static ANVIL_STRONG_INLINE bool AllOnes(const int8_t value) throw() {
		return value == -1;
	}

	static ANVIL_STRONG_INLINE bool AllOnes(const float value) throw() {
		union {
			uint32_t u;
			float f;
		};
		f = value;
		return AllOnes(u);
	}

	static ANVIL_STRONG_INLINE bool AllOnes(const double value) throw() {
		union {
			uint64_t u;
			double f;
		};
		f = value;
		return AllOnes(u);
	}

	static bool AllOnes(const void* src, const size_t bytes) throw() {
		const size_t aligned_size = bytes / sizeof(NativeUnsigned);
		const NativeUnsigned* src1 = static_cast<const NativeUnsigned*>(src);
		const NativeUnsigned* const end1 = src1 + aligned_size;
		while (src1 != end1) {
			if(!AllOnes(*src1)) return false;
			++src1;
		}

		const size_t aligned_size_bytes = aligned_size * sizeof(NativeUnsigned);
		if (aligned_size_bytes != bytes) {
			const size_t unaligned_size_bytes = (bytes - aligned_size_bytes);
			const uint8_t* src2 = reinterpret_cast<const uint8_t*>(end1);
			const uint8_t* const end2 = src2 + unaligned_size_bytes;
			while (src2 != end2) {
				if (!AllOnes(*src2)) return false;
				++src2;
			}
		}

		return true;
	}

	// BitOrN

	template<class T>
	static ANVIL_STRONG_INLINE T BitOrN(const T lhs, const T rhs) throw() {
		return BitOr<T>(BitNot<T>(lhs), rhs);
	}

	// BitXorN

	template<class T>
	static ANVIL_STRONG_INLINE T BitXorN(const T lhs, const T rhs) throw() {
		return BitXor<T>(BitNot<T>(lhs), rhs);
	}

	// BitAndN

	template<class T>
	static ANVIL_STRONG_INLINE T BitAndN(const T lhs, const T rhs) throw() {
		return BitAnd<T>(BitNot<T>(lhs), rhs);
	}

	namespace detail {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		static ANVIL_STRONG_INLINE uint64_t BitAndN_BMI(const uint64_t lhs, const uint64_t rhs) throw() {
			return _andn_u64(lhs, rhs);
		}
#endif
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		static ANVIL_STRONG_INLINE uint64_t BitAndN_BMI(const uint32_t lhs, const uint32_t rhs) throw() {
			return _andn_u32(lhs, rhs);
		}
#endif
	}
	
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64

	template<>
	static ANVIL_STRONG_INLINE uint64_t BitAndN(const uint64_t lhs, const uint64_t rhs) throw() {
		if constexpr ((ASM_MINIMUM & ASM_BMI1) != 0u) {
			return detail::BitAndN_BMI(lhs, rhs);
		} else {
			return (~lhs) & rhs;
		}
	}

#endif

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
	template<>
	static ANVIL_STRONG_INLINE int64_t BitAndN(const int64_t lhs, const int64_t rhs) throw() {
		union Union {
			uint64_t u;
			int64_t s;
		};
		Union a, b;
		a.s = lhs;
		b.s = rhs;
		a.u = BitAndN(a.u, b.u);
		return a.s;
	}

#endif

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64

	template<>
	static ANVIL_STRONG_INLINE uint32_t BitAndN(const uint32_t lhs, const uint32_t rhs) throw() {
		if constexpr ((ASM_MINIMUM & ASM_BMI1) != 0u) {
			return detail::BitAndN_BMI(lhs, rhs);
		} else {
			return (~lhs) & rhs;
		}
	}

	template<>
	static ANVIL_STRONG_INLINE int32_t BitAndN(const int32_t lhs, const int32_t rhs) throw() {
		union Union {
			uint32_t u;
			int32_t s;
		};
		Union a, b;
		a.s = lhs;
		b.s = rhs;
		a.u = BitAndN(a.u, b.u);
		return a.s;
	}

#endif

	// Blend

	template<class T>
	static ANVIL_STRONG_INLINE T Blend(const T ifOne, const T ifZero, const T mask) throw() {
		return BitOr<T>(BitAnd<T>(mask, ifOne),  BitAndN<T>(mask, ifZero));
	}

	// BitTest

	static ANVIL_STRONG_INLINE bool BitTest(const uint64_t value, const size_t index) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		static_assert(sizeof(long long) == sizeof(int64_t), "Expected sizeof(long) == sizeof(int32_t)");
		static_cast<bool>(_bittest64(reinterpret_cast<const long long*>(&value), static_cast<long long>(index)));
#else
		return (value & (1ull << index)) != 0ull;
#endif
	}

	static ANVIL_STRONG_INLINE bool BitTest(const uint32_t value, const size_t index) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		static_assert(sizeof(long) == sizeof(int32_t), "Expected sizeof(long) == sizeof(int32_t)");
		static_cast<bool>(_bittest(reinterpret_cast<const long*>(&value), static_cast<int32_t>(index)));
#else
		return (value & (1u << index)) != 0u;
#endif
	}

	static ANVIL_STRONG_INLINE bool BitTest(const uint16_t value, const size_t index) throw() {
		return BitTest(static_cast<uint32_t>(value), static_cast<uint32_t>(index));
	}

	static ANVIL_STRONG_INLINE bool BitTest(const uint8_t value, const size_t index) throw() {
		return BitTest(static_cast<uint32_t>(value), static_cast<uint32_t>(index));
	}

	static ANVIL_STRONG_INLINE bool BitTest(const int64_t value, const size_t index) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		static_assert(sizeof(long long) == sizeof(int64_t), "Expected sizeof(long) == sizeof(int32_t)");
		static_cast<bool>(_bittest64(reinterpret_cast<const long long*>(&value), static_cast<long long>(index)));
#else
		return (value & (1ll << index)) != 0ll;
#endif
	}

	static ANVIL_STRONG_INLINE bool BitTest(const int32_t value, const size_t index) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		static_assert(sizeof(long) == sizeof(int32_t), "Expected sizeof(long) == sizeof(int32_t)");
		static_cast<bool>(_bittest(reinterpret_cast<const long*>(&value), static_cast<int32_t>(index)));
#else
		return (value & (1 << index)) != 0;
#endif
	}

	static ANVIL_STRONG_INLINE bool BitTest(const int16_t value, const size_t index) throw() {
		return BitTest(static_cast<int32_t>(value), static_cast<int32_t>(index));
	}

	static ANVIL_STRONG_INLINE bool BitTest(const int8_t value, const size_t index) throw() {
		return BitTest(static_cast<int32_t>(value), static_cast<int32_t>(index));
	}

	static ANVIL_STRONG_INLINE bool BitTest(const float value, const size_t index) throw() {
		union {
			int32_t s;
			float f;
		};
		f = value;
		return BitTest(s, index);
	}

	static ANVIL_STRONG_INLINE bool BitTest(const double value, const size_t index) throw() {
		union {
			int64_t s;
			double f;
		};
		f = value;
		return BitTest(s, index);
	}

	// Leading zero count

	namespace detail {

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		static size_t CountLeadingZeros_LZCNT(const uint64_t value) throw() {
			return _lzcnt_u64(value);
		}
#endif

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		static size_t CountLeadingZeros_LZCNT(const uint32_t value) throw() {
			return _lzcnt_u32(value);
		}
#endif
	}

	static size_t CountLeadingZeros(const uint32_t value) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		if constexpr ((ASM_MINIMUM & ASM_LZCNT) != 0ull) {
			return detail::CountLeadingZeros_LZCNT(value);
		}
#endif
		// Based on implementation : https://en.wikipedia.org/wiki/Find_first_set#cite_ref-hackersdelight-clz_43-0
		uint32_t n = 0u;
		uint32_t x = value;
		if (x == 0u) return 32u;
		if ((x & 0xFFFF0000u) == 0) { n = 16u; x <<= 16u; }
		if ((x & 0xFF000000u) == 0) { n += 8u; x <<= 8u; }
		if ((x & 0xF0000000u) == 0) { n += 4u; x <<= 4u; }
		if ((x & 0xC0000000u) == 0) { n += 2u; x <<= 2u; }
		if ((x & 0x80000000u) == 0) { n += 1u; }
		ANVIL_ASSUME(n <= 32u);
		return n;
	}

	static size_t CountLeadingZeros(const uint64_t value) throw() {
		size_t count;
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		if constexpr ((ASM_MINIMUM & ASM_LZCNT) != 0ull) {
			return detail::CountLeadingZeros_LZCNT(value);
		}
#endif
		const uint32_t low = reinterpret_cast<const uint64_t*>(&value)[0u];
		const uint32_t high = reinterpret_cast<const uint64_t*>(&value)[1u];
		count = CountLeadingZeros(low);
		if (count == 32u) count += CountLeadingZeros(high);

		ANVIL_ASSUME(count <= 64u);
		return count;
	}

	static ANVIL_STRONG_INLINE size_t CountLeadingZeros(const uint16_t value) throw() {
		const size_t count = CountLeadingZeros(static_cast<uint32_t>(value));
		ANVIL_ASSUME(count <= 16u);
		return count;
	}

	static ANVIL_STRONG_INLINE size_t CountLeadingZeros(const uint8_t value) throw() {
		const size_t count = CountLeadingZeros(static_cast<uint32_t>(value));
		ANVIL_ASSUME(count <= 8u);
		return count;
	}

	static ANVIL_STRONG_INLINE size_t CountLeadingZeros(const int64_t value) throw() {
		union {
			uint64_t u;
			int64_t s;
		};
		s = value;
		return CountLeadingZeros(u);
	}

	static ANVIL_STRONG_INLINE size_t CountLeadingZeros(const int32_t value) throw() {
		union {
			uint32_t u;
			int32_t s;
		};
		s = value;
		return CountLeadingZeros(u);
	}

	static ANVIL_STRONG_INLINE size_t CountLeadingZeros(const int16_t value) throw() {
		union {
			uint16_t u;
			int16_t s;
		};
		s = value;
		return CountLeadingZeros(u);
	}

	static ANVIL_STRONG_INLINE size_t CountLeadingZeros(const int8_t value) throw() {
		union {
			uint8_t u;
			int8_t s;
		};
		s = value;
		return CountLeadingZeros(u);
	}

	static ANVIL_STRONG_INLINE size_t CountLeadingZeros(const float value) throw() {
		union {
			float f;
			uint32_t u;
		};
		f = value;
		return CountLeadingZeros(u);
	}

	static ANVIL_STRONG_INLINE size_t CountLeadingZeros(const double value) throw() {
		union {
			double f;
			uint64_t u;
		};
		f = value;
		return CountLeadingZeros(u);
	}

	// CountTrailingZeros

	namespace detail {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		static ANVIL_STRONG_INLINE size_t CountTrailingZeros_BMI(const uint32_t value) throw() {
			return _tzcnt_u32(value);
		}
#endif
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		static ANVIL_STRONG_INLINE size_t CountTrailingZeros_BMI(const uint64_t value) throw() {
			return _tzcnt_u64(value);
		}
#endif
	}

	static size_t CountTrailingZeros(const uint32_t value) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		if constexpr ((ASM_MINIMUM & ASM_BMI1) != 0ull) {
			return detail::CountTrailingZeros_BMI(value);
		}
#endif
		// Based on implementation : https://en.wikipedia.org/wiki/Find_first_set#cite_ref-hackersdelight-clz_43-0
		uint32_t n = 0u;
		uint32_t x = value;
		if (x == 0u) return 32u;
		if ((x & 0x0000FFFFu) == 0u) { n += 16u; x >>= 16u; }
		if ((x & 0x000000FFu) == 0u) { n +=  8u; x >>=  8u; }
		if ((x & 0x0000000Fu) == 0u) { n +=  4u; x >>=  4u; }
		if ((x & 0x00000003u) == 0u) { n +=  2u; x >>=  2u; }
		if ((x & 0x00000001u) == 0u) { n += 1u; }
		ANVIL_ASSUME(n <= 32u);
		return n;
	}

	static size_t CountTrailingZeros(const uint64_t value) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		if constexpr ((ASM_MINIMUM & ASM_BMI1) != 0ull) {
			return detail::CountTrailingZeros_BMI(value);
		}
#endif
		size_t count;
		union {
			uint64_t u64;
			uint32_t u32[2u];
		};
		u64 = value;
		count = CountTrailingZeros(u32[0u]);
		if (count == 32u) count += CountTrailingZeros(u32[1u]);
		ANVIL_ASSUME(count <= 64u);
		return count;
	}

	static ANVIL_STRONG_INLINE size_t CountTrailingZeros(const uint16_t value) throw() {
		const size_t count = CountTrailingZeros(static_cast<uint32_t>(value));
		ANVIL_ASSUME(count <= 16u);
		return count;
	}

	static ANVIL_STRONG_INLINE size_t CountTrailingZeros(const uint8_t value) throw() {
		const size_t count = CountTrailingZeros(static_cast<uint32_t>(value));
		ANVIL_ASSUME(count <= 8u);
		return count;
	}

	static ANVIL_STRONG_INLINE size_t CountTrailingZeros(const int64_t value) throw() {
		union {
			uint64_t u;
			int64_t s;
		};
		s = value;
		return CountTrailingZeros(u);
	}

	static ANVIL_STRONG_INLINE size_t CountTrailingZeros(const int32_t value) throw() {
		union {
			uint32_t u;
			int32_t s;
		};
		s = value;
		return CountTrailingZeros(u);
	}

	static ANVIL_STRONG_INLINE size_t CountTrailingZeros(const int16_t value) throw() {
		union {
			uint16_t u;
			int16_t s;
		};
		s = value;
		return CountTrailingZeros(u);
	}

	static ANVIL_STRONG_INLINE size_t CountTrailingZeros(const int8_t value) throw() {
		union {
			uint8_t u;
			int8_t s;
		};
		s = value;
		return CountTrailingZeros(u);
	}

	static ANVIL_STRONG_INLINE size_t CountTrailingZeros(const float value) throw() {
		union {
			float f;
			uint32_t u;
		};
		f = value;
		return CountTrailingZeros(u);
	}

	static ANVIL_STRONG_INLINE size_t CountTrailingZeros(const double value) throw() {
		union {
			double f;
			uint64_t u;
		};
		f = value;
		return CountTrailingZeros(u);
	}

	// MaskUpToLowestBit

	namespace detail {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		static uint32_t MaskUpToLowestBit_BMI(const uint32_t value) throw() {
			return _blsmsk_u32(value);
		}
#endif
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		static uint64_t MaskUpToLowestBit_BMI(const uint64_t value) throw() {
			return _blsmsk_u64(value);
		}
#endif
	}

	static ANVIL_STRONG_INLINE uint64_t MaskUpToLowestBit(const uint64_t value) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		if constexpr ((ASM_MINIMUM & ASM_BMI1) != 0ull) {
			return detail::MaskUpToLowestBit_BMI(value);
		}
#endif
		return value ^ (value - 1u);
	}

	static uint32_t MaskUpToLowestBit(const uint32_t value) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		if constexpr ((ASM_MINIMUM & ASM_BMI1) != 0ull) {
			return detail::MaskUpToLowestBit_BMI(value);
		}
#endif
		return value ^ (value - 1u);
	}

	static ANVIL_STRONG_INLINE uint16_t MaskUpToLowestBit(const uint16_t value) throw() {
		return static_cast<uint16_t>(MaskUpToLowestBit(value));
	}

	static ANVIL_STRONG_INLINE uint8_t MaskUpToLowestBit(const uint8_t value) throw() {
		return static_cast<uint8_t>(MaskUpToLowestBit(value));
	}

	static ANVIL_STRONG_INLINE int64_t MaskUpToLowestBit(const int64_t value) throw() {
		union {
			uint64_t u;
			int64_t s;
		};
		s = value;
		u = MaskUpToLowestBit(u);
		return s;
	}

	static ANVIL_STRONG_INLINE int32_t MaskUpToLowestBit(const int32_t value) throw() {
		union {
			uint32_t u;
			int32_t s;
		};
		s = value;
		u = MaskUpToLowestBit(u);
		return s;
	}

	static ANVIL_STRONG_INLINE int16_t MaskUpToLowestBit(const int16_t value) throw() {
		union {
			uint16_t u;
			int16_t s;
		};
		s = value;
		u = MaskUpToLowestBit(u);
		return s;
	}

	static ANVIL_STRONG_INLINE int8_t MaskUpToLowestBit(const int8_t value) throw() {
		union {
			uint8_t u;
			int8_t s;
		};
		s = value;
		u = MaskUpToLowestBit(u);
		return s;
	}

	static ANVIL_STRONG_INLINE float MaskUpToLowestBit(const float value) throw() {
		union {
			float f;
			uint32_t u;
		};
		f = value;
		u = MaskUpToLowestBit(u);
		return f;
	}

	static ANVIL_STRONG_INLINE double MaskUpToLowestBit(const double value) throw() {
		union {
			double f;
			uint64_t u;
		};
		f = value;
		u = MaskUpToLowestBit(u);
		return f;
	}

	// MaskBits

	template<class T>
	static T MaskBits(const size_t count) throw();

	template<>
	static ANVIL_STRONG_INLINE uint64_t MaskBits<uint64_t>(const size_t count) throw() {
		return MaskUpToLowestBit(1ull << static_cast<uint64_t>(count));
	}

	template<>
	static uint32_t MaskBits<uint32_t>(const size_t count) throw() {
		return MaskUpToLowestBit(1u << static_cast<uint32_t>(count));
	}

	template<>
	static ANVIL_STRONG_INLINE uint16_t MaskBits<uint16_t>(const size_t count) throw() {
		return static_cast<uint16_t>(MaskBits<uint32_t>(count));
	}

	template<>
	static ANVIL_STRONG_INLINE uint8_t MaskBits<uint8_t>(const size_t count) throw() {
		return static_cast<uint8_t>(MaskBits<uint32_t>(count));
	}

	template<>
	static ANVIL_STRONG_INLINE int64_t MaskBits<int64_t>(const size_t count) throw() {
		return MaskUpToLowestBit(1ll << static_cast<int64_t>(count));
	}

	template<>
	static ANVIL_STRONG_INLINE int32_t MaskBits<int32_t>(const size_t count) throw() {
		return MaskUpToLowestBit(1 << static_cast<int32_t>(count));
	}

	template<>
	static ANVIL_STRONG_INLINE int16_t MaskBits<int16_t>(const size_t count) throw() {
		union {
			uint16_t u;
			int16_t s;
		};
		u = MaskBits<uint16_t>(count);
		return s;
	}

	template<>
	static ANVIL_STRONG_INLINE int8_t MaskBits<int8_t>(const size_t count) throw() {
		union {
			uint8_t u;
			int8_t s;
		};
		u = MaskBits<uint8_t>(count);
		return s;
	}

	template<>
	static ANVIL_STRONG_INLINE float MaskBits<float>(const size_t count) throw() {
		union {
			float f;
			uint32_t u;
		};
		u = MaskBits<uint32_t>(count);
		return f;
	}

	template<>
	static ANVIL_STRONG_INLINE double MaskBits<double>(const size_t count) throw() {
		union {
			double f;
			uint64_t u;
		};
		u = MaskBits<uint64_t>(count);
		return f;
	}

	// ExtractBitField

	namespace detail {

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		static uint32_t ExtractBitField_BMI(const uint32_t src, const size_t start_bit, const size_t bit_count) throw() {
			return _bextr_u32(src, static_cast<uint32_t>(start_bit), static_cast<uint32_t>(bit_count));
		}
#endif

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		static uint64_t ExtractBitField_BMI(const uint64_t src, const size_t start_bit, const size_t bit_count) throw() {
			return _bextr_u64(src, static_cast<uint64_t>(start_bit), static_cast<uint64_t>(bit_count));
		}
#endif

	}

	static ANVIL_STRONG_INLINE uint64_t ExtractBitField(const uint64_t src, const size_t start_bit, const size_t bit_count) throw() {
		ANVIL_ASSUME(start_bit <= 64u);
		ANVIL_ASSUME(bit_count <= 64u);

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		if constexpr ((ASM_MINIMUM & ASM_BMI1) != 0ull) {
			return detail::ExtractBitField_BMI(src, start_bit, bit_count);
		}
#endif
		return (src >> static_cast<uint64_t>(start_bit)) & ((1ull << static_cast<uint64_t>(bit_count)) - 1ull);
	}

	static uint32_t ExtractBitField(const uint32_t src, const size_t start_bit, const size_t bit_count) throw() {
		ANVIL_ASSUME(start_bit <= 32u);
		ANVIL_ASSUME(bit_count <= 32u);

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		if constexpr ((ASM_MINIMUM & ASM_BMI1) != 0ull) {
			return detail::ExtractBitField_BMI(src, start_bit, bit_count);
		}
#endif
		return (src >> static_cast<uint32_t>(start_bit)) & ((1u << static_cast<uint32_t>(bit_count)) - 1u);
	}

	static ANVIL_STRONG_INLINE uint16_t ExtractBitField(const uint16_t src, const size_t start_bit, const size_t bit_count) throw() {
		ANVIL_ASSUME(start_bit <= 16u);
		ANVIL_ASSUME(bit_count <= 16u);

		return static_cast<uint16_t>(ExtractBitField(static_cast<uint32_t>(src), start_bit, bit_count));
	}

	static ANVIL_STRONG_INLINE uint8_t ExtractBitField(const uint8_t src, const size_t start_bit, const size_t bit_count) throw() {
		ANVIL_ASSUME(start_bit <= 8u);
		ANVIL_ASSUME(bit_count <= 8u);

		return static_cast<uint8_t>(ExtractBitField(static_cast<uint32_t>(src), start_bit, bit_count));
	}

	static ANVIL_STRONG_INLINE int64_t ExtractBitField(const int64_t src, const size_t start_bit, const size_t bit_count) throw() {
		union {
			uint64_t u;
			int64_t s;
		};
		s = src;
		u = ExtractBitField(u, start_bit, bit_count);
		return s;
	}

	static ANVIL_STRONG_INLINE int32_t ExtractBitField(const int32_t src, const size_t start_bit, const size_t bit_count) throw() {
		union {
			uint32_t u;
			int32_t s;
		};
		s = src;
		u = ExtractBitField(u, start_bit, bit_count);
		return s;
	}

	static ANVIL_STRONG_INLINE int16_t ExtractBitField(const int16_t src, const size_t start_bit, const size_t bit_count) throw() {
		union {
			uint16_t u;
			int16_t s;
		};
		s = src;
		u = ExtractBitField(u, start_bit, bit_count);
		return s;
	}

	static ANVIL_STRONG_INLINE int8_t ExtractBitField(const int8_t src, const size_t start_bit, const size_t bit_count) throw() {
		union {
			uint8_t u;
			int8_t s;
		};
		s = src;
		u = ExtractBitField(u, start_bit, bit_count);
		return s;
	}

	static ANVIL_STRONG_INLINE float ExtractBitField(const float src, const size_t start_bit, const size_t bit_count) throw() {
		union {
			float f;
			uint32_t u;
		};
		f = src;
		u = ExtractBitField(u, start_bit, bit_count);
		return f;
	}

	static ANVIL_STRONG_INLINE double ExtractBitField(const double src, const size_t start_bit, const size_t bit_count) throw() {
		union {
			double f;
			uint64_t u;
		};
		f = src;
		u = ExtractBitField(u, start_bit, bit_count);
		return f;
	}
}

#endif
