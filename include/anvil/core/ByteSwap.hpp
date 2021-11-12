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

#ifndef ANVIL_CORE_BSWAP_HPP
#define ANVIL_CORE_BSWAP_HPP

/*
	bswap reverses the order of bytes
*/

//! \todo CPU acceleration

#include "anvil/core/Keywords.hpp"

namespace anvil {

	ANVIL_STRONG_INLINE uint8_t ANVIL_CALL bswap(uint8_t aValue) throw() {
		return aValue;
	}

	ANVIL_STRONG_INLINE uint16_t ANVIL_CALL bswap(uint16_t aValue) throw() {
		const uint16_t low = aValue & 255u;
		const uint8_t high = aValue << 8u;
		return (low << 8u) | high;
	}

	ANVIL_STRONG_INLINE uint32_t ANVIL_CALL bswap(uint32_t aValue) throw() {
		uint32_t low = aValue & static_cast<uint32_t>(UINT16_MAX);
		uint32_t high = aValue << 16u;

		low = bswap(static_cast<uint16_t>(low));
		high = bswap(static_cast<uint16_t>(high));

		return (low << 16u) | high;
	}

	ANVIL_STRONG_INLINE uint64_t ANVIL_CALL bswap(uint64_t aValue) throw() {
		uint64_t low = aValue & static_cast<uint64_t>(UINT32_MAX);
		uint64_t high = aValue << 32ull;

		low = bswap(static_cast<uint32_t>(low));
		high = bswap(static_cast<uint32_t>(high));

		return (low << 32ull) | high;
	}

	ANVIL_STRONG_INLINE int8_t ANVIL_CALL bswap(int8_t aValue) throw() {
		return aValue;
	}

	ANVIL_STRONG_INLINE int16_t ANVIL_CALL bswap(int16_t aValue) throw() {
		union {
			uint16_t u;
			int16_t s;
		};
		s = aValue;
		u = bswap(u);
		return s;
	}

	ANVIL_STRONG_INLINE int32_t ANVIL_CALL bswap(int32_t aValue) throw() {
		union {
			uint32_t u;
			int32_t s;
		};
		s = aValue;
		u = bswap(u);
		return s;
	}

	ANVIL_STRONG_INLINE int64_t ANVIL_CALL bswap(int64_t aValue) throw() {
		union {
			uint64_t u;
			int64_t s;
		};
		s = aValue;
		u = bswap(u);
		return s;
	}

}

#endif