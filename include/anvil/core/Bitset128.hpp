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

#ifndef ANVIL_CORE_BITSET_128_HPP
#define ANVIL_CORE_BITSET_128_HPP

#include "anvil/core/Keywords.hpp"

// Constexpr code for 128-bit bitfields

namespace anvil {

	static ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint64_t BitShiftRightWithRemainder(uint64_t value, uint64_t bits, uint64_t& remainder) throw() {
		const uint64_t mask = (1ull << bits) - 1ull;
		remainder = value & mask;
		return value >> bits;
	}

	static ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint64_t BitShiftLeftWithRemainder(uint64_t value, uint64_t bits, uint64_t& remainder) throw() {
		const uint64_t mask = ~(1ull << bits) - 1ull;
		uint64_t tmp = value & mask;
		remainder = tmp >> (64ull - bits);
		return value << bits;
	}

	struct Bitfield128 {
		uint64_t low;
		uint64_t high;

		ANVIL_CONSTEXPR_FN Bitfield128() throw() :
			low(0ull),
			high(0ull)
		{}

		ANVIL_CONSTEXPR_FN Bitfield128(const uint64_t aLow) throw() :
			low(aLow),
			high(0ull)
		{}

		ANVIL_CONSTEXPR_FN Bitfield128(const uint64_t aLow, const uint64_t aHigh) throw() :
			low(aLow),
			high(aHigh)
		{}

		ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE Bitfield128 operator&(const uint64_t aLow) const throw() {
			return Bitfield128(low & aLow, high);
		}

		ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE Bitfield128 operator|(const uint64_t aLow) const throw() {
			return Bitfield128(low | aLow, high);
		}

		ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE Bitfield128 operator^(const uint64_t aLow) const throw() {
			return Bitfield128(low ^ aLow, high);
		}

		ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE Bitfield128 operator&(const Bitfield128 other) const throw() {
			return Bitfield128(low & other.low, high & other.high);
		}

		ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE Bitfield128 operator|(const Bitfield128 other) const throw() {
			return Bitfield128(low | other.low, high | other.high);
		}

		ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE Bitfield128 operator^(const Bitfield128 other) const throw() {
			return Bitfield128(low ^ other.low, high ^ other.high);
		}

		ANVIL_STRONG_INLINE Bitfield128& operator&=(const uint64_t aLow) throw() {
			low &= aLow;
			return *this;
		}

		ANVIL_STRONG_INLINE Bitfield128& operator|=(const uint64_t aLow) throw() {
			low |= aLow;
			return *this;
		}

		ANVIL_STRONG_INLINE Bitfield128& operator^=(const uint64_t aLow) throw() {
			low ^= aLow;
			return *this;
		}

		ANVIL_STRONG_INLINE Bitfield128& operator&=(const Bitfield128 other) throw() {
			low &= other.low;
			high &= other.high;
			return *this;
		}

		ANVIL_STRONG_INLINE Bitfield128& operator|=(const Bitfield128 other) throw() {
			low |= other.low;
			high |= other.high;
			return *this;
		}

		ANVIL_STRONG_INLINE Bitfield128& operator^=(const Bitfield128 other) throw() {
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

		ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE bool operator==(const Bitfield128 other) const throw() {
			return low == other.low && high == other.high;
		}

		ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE bool operator!=(const Bitfield128 other) const throw() {
			return low != other.low || high != other.high;
		}

		ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE bool CheckBit(const size_t bit) const throw() {
			return bit < 64u ?
				static_cast<bool>(low & (1ull << static_cast<uint64_t>(bit))) :
				static_cast<bool>(high & (1ull << static_cast<uint64_t>(bit - 64u))
			);
		}

		ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE Bitfield128 operator>>(uint64_t bits) const throw() {
			uint64_t l = low >> bits;
			uint64_t remainder = 0ull;
			uint64_t h = BitShiftRightWithRemainder(high, bits, remainder);
			l |= remainder << (64ull - bits);

			return Bitfield128(l, h);
		}

		ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE Bitfield128 operator<<(uint64_t bits) const throw() {
			uint64_t h = high << bits;
			uint64_t remainder = 0ull;
			uint64_t l = BitShiftLeftWithRemainder(low, bits, remainder);
			h |= remainder;

			return Bitfield128(l, h);
		}

		ANVIL_STRONG_INLINE Bitfield128& operator>>=(uint64_t bits) throw() {
			return *this = *this >> bits;
		}

		ANVIL_STRONG_INLINE Bitfield128& operator<<=(uint64_t bits) throw() {
			return *this = *this << bits;
		}
	};

}

#endif