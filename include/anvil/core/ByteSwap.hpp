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

#include "anvil/core/Keywords.hpp"
#if (ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64) && ANVIL_COMPILER != ANVIL_MSVC
	#include <immintrin.h>
#endif

namespace anvil {

	// 8-bit (unsigned)

	ANVIL_STRONG_INLINE uint8_t ANVIL_CALL bswap(uint8_t aValue) throw() {
		return aValue;
	}
	
	// 16-bit (unsigned)

	ANVIL_STRONG_INLINE uint16_t ANVIL_CALL bswap(uint16_t aValue) throw() {
		#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
			#if ANVIL_COMPILER == ANVIL_MSVC
				return _byteswap_ushort(aValue);
			#else
				return numeric_reinterpret_cast<uint16_t>(_bswap(numeric_reinterpret_cast<int16_t>(aValue)));
			#endif
		#else
			const uint16_t low = aValue & 255u;
			const uint8_t high = aValue >> 8u;
			return (low << 8u) | high;
		#endif
	}

	// 32-bit (unsigned)

	ANVIL_STRONG_INLINE uint32_t ANVIL_CALL bswap(uint32_t aValue) throw() {
		#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
			#if ANVIL_COMPILER == ANVIL_MSVC
				return _byteswap_ulong(aValue);
			#else
				return numeric_reinterpret_cast<uint32_t>(_bswap(numeric_reinterpret_cast<int32_t>(aValue)));
			#endif
		#else
			const uint32_t a = (aValue & 255u) << 24u;
			const uint32_t b = (aValue & 65280u) << 8u;
			const uint32_t c = (aValue & 16711680u) >> 8u;
			const uint32_t d = (aValue & 4278190080u) >> 24u;

			return (a | b) | (c | d);
		#endif
	}

	// 64-bit (unsigned)

	ANVIL_STRONG_INLINE uint64_t ANVIL_CALL bswap(uint64_t aValue) throw() {
		#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
			#if ANVIL_COMPILER == ANVIL_MSVC
				return _byteswap_uint64(aValue);
			#else
				return numeric_reinterpret_cast<uint64_t>(_bswap64(numeric_reinterpret_cast<int64_t>(aValue)));
			#endif
		#else
			uint64_t a = aValue & static_cast<uint64_t>(UINT32_MAX);
			uint64_t b = aValue >>= 32ull;

			a = bswap(static_cast<uint32_t>(a));
			b = bswap(static_cast<uint32_t>(b));

			return (a << 32ull) | b;
		#endif
	}

	// signed

	ANVIL_STRONG_INLINE int8_t ANVIL_CALL bswap(int8_t aValue) throw() {
		return aValue;
	}

	ANVIL_STRONG_INLINE int16_t ANVIL_CALL bswap(int16_t aValue) throw() {
		return numeric_reinterpret_cast<int16_t>(bswap(numeric_reinterpret_cast<uint16_t>(aValue)));
	}

	ANVIL_STRONG_INLINE int32_t ANVIL_CALL bswap(int32_t aValue) throw() {
		return numeric_reinterpret_cast<int32_t>(bswap(numeric_reinterpret_cast<uint32_t>(aValue)));
	}

	ANVIL_STRONG_INLINE int64_t ANVIL_CALL bswap(int64_t aValue) throw() {
		return numeric_reinterpret_cast<int64_t>(bswap(numeric_reinterpret_cast<uint64_t>(aValue)));
	}

}

#endif