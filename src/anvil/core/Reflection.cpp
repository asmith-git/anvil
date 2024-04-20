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

#include "anvil/core/Reflection.hpp"

namespace anvil {

	void ANVIL_CALL reflect_bytes(void* aDst, const void* aSrc, size_t aBytes) throw() {
		if (aDst == aSrc)
		{
			uint8_t* src = static_cast<uint8_t*>(aDst);
			uint8_t* dst = src + aBytes - 1;

#if ANVIL_USE_SSE_REFLECT_BYTES
			const size_t sse_count = aBytes / 32u;
			for(size_t i = 0u; i < sse_count; ++i)
			{
				__m128i xmm0 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(src));
				__m128i xmm1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(dst - 15u));
				xmm0 = _mm_shuffle_epi8(xmm0, details::g_reflect_bytes_mask_16);
				xmm1 = _mm_shuffle_epi8(xmm1, details::g_reflect_bytes_mask_16);
				_mm_storeu_si128(reinterpret_cast<__m128i*>(src), xmm1);
				_mm_storeu_si128(reinterpret_cast<__m128i*>(dst - 15u), xmm0);
				src += 16u;
				dst -= 16u;
			}
#endif
			while (src < dst) {
				uint8_t tmp = *src;
				*src = *dst;
				*dst = tmp;
				++src;
				--dst;
			}
		}
		else
		{
			const uint8_t* src = static_cast<const uint8_t*>(aSrc);
			const uint8_t* const end = src + aBytes;
			uint8_t* dst = static_cast<uint8_t*>(aDst) + aBytes - 1;
			while (src != end) {
				*dst = *src;
				++src;
				--dst;
			}
		}
	}

	void ANVIL_CALL reflect_bits(void* aDst, const void* aSrc, size_t aBytes) throw() {

		uint8_t* dst = static_cast<uint8_t*>(aDst);
		if (aSrc == dst)
		{
			for (size_t i = 0u; i < aBytes; ++i) dst[i] = reflect_bits(dst[i]);
		}
		else
		{
			const uint8_t* src = static_cast<const uint8_t*>(aSrc);
			for (size_t i = 0u; i < aBytes; ++i) dst[i] = reflect_bits(src[i]);

		}

		reflect_bytes(aDst, aDst, aBytes);
	}

}