//Copyright 2021 Adam G. Smith
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

#ifndef ANVIL_CORE_BITSET_256_HPP
#define ANVIL_CORE_BITSET_256_HPP

#include "anvil/core/Bitset128.hpp"

// Constexpr code for 256-bit bitfields

namespace anvil {

	struct Bitfield256 {
		Bitfield128 low;
		Bitfield128 high;

		ANVIL_CONSTEXPR_FN Bitfield256() throw() :
			low(),
			high()
		{}

		ANVIL_CONSTEXPR_FN Bitfield256(const uint64_t aLow) throw() :
			low(aLow),
			high()
		{}

		ANVIL_CONSTEXPR_FN Bitfield256(const Bitfield128 aLow) throw() :
			low(aLow),
			high()
		{}

		ANVIL_CONSTEXPR_FN Bitfield256(const uint64_t aLow, const uint64_t aHigh) throw() :
			low(aLow, aHigh),
			high()
		{}

		ANVIL_CONSTEXPR_FN Bitfield256(const Bitfield128 aLow, const Bitfield128 aHigh) throw() :
			low(aLow),
			high(aHigh)
		{}

		ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE Bitfield256 operator&(const uint64_t aLow) const throw() {
			return Bitfield256(low & aLow, high);
		}

		ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE Bitfield256 operator|(const uint64_t aLow) const throw() {
			return Bitfield256(low | aLow, high);
		}

		ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE Bitfield256 operator^(const uint64_t aLow) const throw() {
			return Bitfield256(low ^ aLow, high);
		}

		ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE Bitfield256 operator&(const Bitfield128 aLow) const throw() {
			return Bitfield256(low & aLow, high);
		}

		ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE Bitfield256 operator|(const Bitfield128 aLow) const throw() {
			return Bitfield256(low | aLow, high);
		}

		ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE Bitfield256 operator^(const Bitfield128 aLow) const throw() {
			return Bitfield256(low ^ aLow, high);
		}

		ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE Bitfield256 operator&(const Bitfield256 other) const throw() {
			return Bitfield256(low & other.low, high & other.high);
		}

		ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE Bitfield256 operator|(const Bitfield256 other) const throw() {
			return Bitfield256(low | other.low, high | other.high);
		}

		ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE Bitfield256 operator^(const Bitfield256 other) const throw() {
			return Bitfield256(low ^ other.low, high ^ other.high);
		}

		ANVIL_STRONG_INLINE Bitfield256& operator&=(const uint64_t aLow) throw() {
			low &= aLow;
			return *this;
		}

		ANVIL_STRONG_INLINE Bitfield256& operator|=(const uint64_t aLow) throw() {
			low |= aLow;
			return *this;
		}

		ANVIL_STRONG_INLINE Bitfield256& operator^=(const uint64_t aLow) throw() {
			low ^= aLow;
			return *this;
		}

		ANVIL_STRONG_INLINE Bitfield256& operator&=(const Bitfield128 aLow) throw() {
			low &= aLow;
			return *this;
		}

		ANVIL_STRONG_INLINE Bitfield256& operator|=(const Bitfield128 aLow) throw() {
			low |= aLow;
			return *this;
		}

		ANVIL_STRONG_INLINE Bitfield256& operator^=(const Bitfield128 aLow) throw() {
			low ^= aLow;
			return *this;
		}

		ANVIL_STRONG_INLINE Bitfield256& operator&=(const Bitfield256 other) throw() {
			low &= other.low;
			high &= other.high;
			return *this;
		}

		ANVIL_STRONG_INLINE Bitfield256& operator|=(const Bitfield256 other) throw() {
			low |= other.low;
			high |= other.high;
			return *this;
		}

		ANVIL_STRONG_INLINE Bitfield256& operator^=(const Bitfield256 other) throw() {
			low ^= other.low;
			high ^= other.high;
			return *this;
		}

		ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE bool operator==(const uint64_t aLow) const throw() {
			return low == aLow && high == 0ull;
		}

		ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE bool operator!=(const uint64_t aLow) const throw() {
			return low != aLow || high != 0ull;
		}

		ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE bool operator==(const Bitfield128 aLow) const throw() {
			return low == aLow && high == 0ull;
		}

		ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE bool operator!=(const Bitfield128 aLow) const throw() {
			return low != aLow || high != 0ull;
		}

		ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE bool operator==(const Bitfield256 other) const throw() {
			return low == other.low && high == other.high;
		}

		ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE bool operator!=(const Bitfield256 other) const throw() {
			return low != other.low || high != other.high;
		}

		ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE bool CheckBit(const size_t bit) const throw() {
			return bit < 128u ? low.CheckBit(bit) : high.CheckBit(bit - 64u);
		}
	};

}

#endif