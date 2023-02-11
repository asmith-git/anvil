//Copyright 2017 Adam G. Smith
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

#ifndef ANVIL_CORE_REFLECTION_HPP
#define ANVIL_CORE_REFLECTION_HPP

/*
	Reflect reverses the order of bits
*/

#include "anvil/core/Keywords.hpp"
#include "anvil/core/BitwiseLUT.hpp"

namespace anvil {

	ANVIL_DLL_EXPORT void ANVIL_CALL reflect(void*, const void*, size_t) throw();

	static ANVIL_STRONG_INLINE uint8_t ANVIL_CALL reflect(uint8_t aValue) throw() {
		return detail::g_reflect_lut[aValue];
	}

	static ANVIL_STRONG_INLINE uint16_t ANVIL_CALL reflect(uint16_t aValue) throw() {
		uint32_t a = aValue & 255u;
		uint32_t b = aValue >> 8u;
		a = detail::g_reflect_lut[a];
		b = detail::g_reflect_lut[b];
		return (a << 8u) | b;
	}

	static ANVIL_STRONG_INLINE uint32_t ANVIL_CALL reflect(uint32_t aValue) throw() {
		uint32_t a = aValue & static_cast<uint32_t>(UINT16_MAX);
		uint32_t b = aValue >> 16u;
		a = reflect(static_cast<uint16_t>(a));
		b = reflect(static_cast<uint16_t>(b));
		return (a << 16u) | b;
	}

	static ANVIL_STRONG_INLINE uint64_t ANVIL_CALL reflect(uint64_t aValue) throw() {
		uint64_t a = aValue & static_cast<uint64_t>(UINT32_MAX);
		uint64_t b = aValue >> 32ull;
		a = reflect(static_cast<uint32_t>(a));
		b = reflect(static_cast<uint32_t>(b));
		return (a << 16ull) | b;
	}

	static ANVIL_STRONG_INLINE int8_t ANVIL_CALL reflect(int8_t aValue) throw() {
		return numeric_reinterpret_cast<int8_t>(reflect(numeric_reinterpret_cast<uint8_t>(aValue)));
	}

	static ANVIL_STRONG_INLINE int16_t ANVIL_CALL reflect(int16_t aValue) throw() {
		return numeric_reinterpret_cast<int16_t>(reflect(numeric_reinterpret_cast<uint16_t>(aValue)));
	}

	static ANVIL_STRONG_INLINE int32_t ANVIL_CALL reflect(int32_t aValue) throw() {
		return numeric_reinterpret_cast<int32_t>(reflect(numeric_reinterpret_cast<uint32_t>(aValue)));
	}

	static ANVIL_STRONG_INLINE int64_t ANVIL_CALL reflect(int64_t aValue) throw() {
		return numeric_reinterpret_cast<int64_t>(reflect(numeric_reinterpret_cast<uint64_t>(aValue)));
	}

	static ANVIL_STRONG_INLINE float ANVIL_CALL reflect(float aValue) throw() {
		return numeric_reinterpret_cast<float>(reflect(numeric_reinterpret_cast<uint32_t>(aValue)));
	}

	static ANVIL_STRONG_INLINE double ANVIL_CALL reflect(double aValue) throw() {
		return numeric_reinterpret_cast<double>(reflect(numeric_reinterpret_cast<uint64_t>(aValue)));
	}

}

#endif