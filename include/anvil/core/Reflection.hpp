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
#include "anvil/core/ByteManipulation.hpp"
#include "anvil/core/BitwiseLUT.hpp"

namespace anvil {

#ifndef ANVIL_USE_SSE_REFLECT_BYTES
	#define ANVIL_USE_SSE_REFLECT_BYTES (ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64)
#endif

#if ANVIL_USE_SSE_REFLECT_BYTES
	namespace details
	{
		static const __m128i g_reflect_bytes_mask_16 = _mm_set_epi8(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
		static const __m128i g_reflect_bytes_mask_8 = _mm_set_epi8(8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7);
		static const __m128i g_reflect_bytes_mask_4 = _mm_set_epi8(12, 13, 14, 15, 8, 9, 10, 11, 4, 5, 6, 7, 0, 1, 2, 3);
		static const __m128i g_reflect_bytes_mask_2 = _mm_set_epi8(14, 15, 12, 13, 10, 11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1);
	}
#endif

	ANVIL_DLL_EXPORT void ANVIL_CALL reflect_bytes(void*, const void*, size_t) throw();

	static ANVIL_STRONG_INLINE uint8_t ANVIL_CALL reflect_bytes(uint8_t aValue) throw() {
		return aValue;
	}

	static ANVIL_STRONG_INLINE uint16_t ANVIL_CALL reflect_bytes(uint16_t aValue) throw() {
#ifdef ANVIL_USE_SSE_REFLECT_BYTES
		return static_cast<uint16_t>(_mm_extract_epi16(_mm_shuffle_epi8(_mm_cvtsi32_si128(aValue), details::g_reflect_bytes_mask_2), 0));
#else
		const uint8_t a = ExtractByte<0>(aValue);
		const uint8_t b = ExtractByte<1>(aValue);
		return ConcatenateBytes<uint16_t>(b, a);
#endif
	}

	static ANVIL_STRONG_INLINE uint32_t ANVIL_CALL reflect_bytes(uint32_t aValue) throw() {
#ifdef ANVIL_USE_SSE_REFLECT_BYTES
		return numeric_reinterpret_cast<uint32_t>(_mm_cvtsi128_si32(_mm_shuffle_epi8(_mm_cvtsi32_si128(numeric_reinterpret_cast<int32_t>(aValue)), details::g_reflect_bytes_mask_4)));
#else
		const uint8_t a = ExtractByte<0>(aValue);
		const uint8_t b = ExtractByte<1>(aValue);
		const uint8_t c = ExtractByte<2>(aValue);
		const uint8_t d = ExtractByte<3>(aValue);
		return ConcatenateBytes<uint32_t>(d, c, b, a);
#endif
	}

	static ANVIL_STRONG_INLINE uint64_t ANVIL_CALL reflect_bytes(uint64_t aValue) throw() {
#ifdef ANVIL_USE_SSE_REFLECT_BYTES
		_mm_storel_epi64(reinterpret_cast<__m128i*>(&aValue), _mm_shuffle_epi8(_mm_loadl_epi64(reinterpret_cast<__m128i*>(&aValue)), details::g_reflect_bytes_mask_8));
		return aValue;
#else
		const uint8_t a = ExtractByte<0>(aValue);
		const uint8_t b = ExtractByte<1>(aValue);
		const uint8_t c = ExtractByte<2>(aValue);
		const uint8_t d = ExtractByte<3>(aValue);
		const uint8_t e = ExtractByte<4>(aValue);
		const uint8_t f = ExtractByte<5>(aValue);
		const uint8_t g = ExtractByte<6>(aValue);
		const uint8_t h = ExtractByte<7>(aValue);
		return ConcatenateBytes<uint64_t>(h, g, f, e, d, c, b, a);
#endif
	}

	static ANVIL_STRONG_INLINE int8_t ANVIL_CALL reflect_bytes(int8_t aValue) throw() {
		return numeric_reinterpret_cast<int8_t>(reflect_bytes(numeric_reinterpret_cast<uint8_t>(aValue)));
	}

	static ANVIL_STRONG_INLINE int16_t ANVIL_CALL reflect_bytes(int16_t aValue) throw() {
		return numeric_reinterpret_cast<int16_t>(reflect_bytes(numeric_reinterpret_cast<uint16_t>(aValue)));
	}

	static ANVIL_STRONG_INLINE int32_t ANVIL_CALL reflect_bytes(int32_t aValue) throw() {
		return numeric_reinterpret_cast<int32_t>(reflect_bytes(numeric_reinterpret_cast<uint32_t>(aValue)));
	}

	static ANVIL_STRONG_INLINE int64_t ANVIL_CALL reflect_bytes(int64_t aValue) throw() {
		return numeric_reinterpret_cast<int64_t>(reflect_bytes(numeric_reinterpret_cast<uint64_t>(aValue)));
	}

	static ANVIL_STRONG_INLINE float ANVIL_CALL reflect_bytes(float aValue) throw() {
		return numeric_reinterpret_cast<float>(reflect_bytes(numeric_reinterpret_cast<uint32_t>(aValue)));
	}

	static ANVIL_STRONG_INLINE double ANVIL_CALL reflect_bytes(double aValue) throw() {
		return numeric_reinterpret_cast<double>(reflect_bytes(numeric_reinterpret_cast<uint64_t>(aValue)));
	}

	// ---- reflect_bits ----

	ANVIL_DLL_EXPORT void ANVIL_CALL reflect_bits(void*, const void*, size_t) throw();

	static ANVIL_STRONG_INLINE uint8_t ANVIL_CALL reflect_bits(uint8_t aValue) throw() {
		return detail::g_reflect_bits_lut[aValue];
	}

	static ANVIL_STRONG_INLINE uint16_t ANVIL_CALL reflect_bits(uint16_t aValue) throw() {
		uint8_t buffer[2u];
		buffer[0] = detail::g_reflect_bits_lut[ExtractByte<0>(aValue)];
		buffer[1] = detail::g_reflect_bits_lut[ExtractByte<1>(aValue)];
		return reflect_bytes(*reinterpret_cast<uint16_t*>(buffer));
	}

	static ANVIL_STRONG_INLINE uint32_t ANVIL_CALL reflect_bits(uint32_t aValue) throw() {
		uint8_t buffer[4u];
		buffer[0] = detail::g_reflect_bits_lut[ExtractByte<0>(aValue)];
		buffer[1] = detail::g_reflect_bits_lut[ExtractByte<1>(aValue)];
		buffer[2] = detail::g_reflect_bits_lut[ExtractByte<2>(aValue)];
		buffer[3] = detail::g_reflect_bits_lut[ExtractByte<3>(aValue)];
		return reflect_bytes(*reinterpret_cast<uint32_t*>(buffer));
	}

	static ANVIL_STRONG_INLINE uint64_t ANVIL_CALL reflect_bits(uint64_t aValue) throw() {
		uint8_t buffer[8u];
		buffer[0]= detail::g_reflect_bits_lut[ExtractByte<0>(aValue)];
		buffer[1]= detail::g_reflect_bits_lut[ExtractByte<1>(aValue)];
		buffer[2]= detail::g_reflect_bits_lut[ExtractByte<2>(aValue)];
		buffer[3]= detail::g_reflect_bits_lut[ExtractByte<3>(aValue)];
		buffer[4]= detail::g_reflect_bits_lut[ExtractByte<4>(aValue)];
		buffer[5]= detail::g_reflect_bits_lut[ExtractByte<5>(aValue)];
		buffer[6]= detail::g_reflect_bits_lut[ExtractByte<6>(aValue)];
		buffer[7]= detail::g_reflect_bits_lut[ExtractByte<7>(aValue)];
		return reflect_bytes(*reinterpret_cast<uint64_t*>(buffer));
	}

	static ANVIL_STRONG_INLINE int8_t ANVIL_CALL reflect_bits(int8_t aValue) throw() {
		return numeric_reinterpret_cast<int8_t>(reflect_bits(numeric_reinterpret_cast<uint8_t>(aValue)));
	}

	static ANVIL_STRONG_INLINE int16_t ANVIL_CALL reflect_bits(int16_t aValue) throw() {
		return numeric_reinterpret_cast<int16_t>(reflect_bits(numeric_reinterpret_cast<uint16_t>(aValue)));
	}

	static ANVIL_STRONG_INLINE int32_t ANVIL_CALL reflect_bits(int32_t aValue) throw() {
		return numeric_reinterpret_cast<int32_t>(reflect_bits(numeric_reinterpret_cast<uint32_t>(aValue)));
	}

	static ANVIL_STRONG_INLINE int64_t ANVIL_CALL reflect_bits(int64_t aValue) throw() {
		return numeric_reinterpret_cast<int64_t>(reflect_bits(numeric_reinterpret_cast<uint64_t>(aValue)));
	}

	static ANVIL_STRONG_INLINE float ANVIL_CALL reflect_bits(float aValue) throw() {
		return numeric_reinterpret_cast<float>(reflect_bits(numeric_reinterpret_cast<uint32_t>(aValue)));
	}

	static ANVIL_STRONG_INLINE double ANVIL_CALL reflect_bits(double aValue) throw() {
		return numeric_reinterpret_cast<double>(reflect_bits(numeric_reinterpret_cast<uint64_t>(aValue)));
	}

}

#endif