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

#include <array>

// Types

#ifndef __AVX__
typedef std::array<__m128, 2> __m256;
typedef std::array<__m128i, 2> __m256i;
typedef std::array<__m128d, 2> __m256d;
#endif

// Set ones

static __forceinline __m128 __vectorcall _mm_setone_ps() throw() {
	return _mm_cmpeq_ps(_mm_setzero_ps(), _mm_setzero_ps());
}

static __forceinline __m128d __vectorcall _mm_setone_pd() throw() {
	return _mm_cmpeq_d(_mm_setzero_pd(), _mm_setzero_pd());
}

static __forceinline __m128i __vectorcall _mm_setone_si128() throw() {
	return _mm_cmpeq_epi32(_mm_setzero_si128(), _mm_setzero_si128());
}

// Not

static __forceinline __m128 __vectorcall _mm_not_ps(const register __m128 xmm0) throw() {
	return _mm_xor_ps(_xmm0, _mm_setone_ps());
}

static __forceinline __m128d __vectorcall _mm_not_pd(const register __m128d xmm0) throw() {
	return _mm_xor_pd(_xmm0, _mm_setone_pd());
}

static __forceinline __m128i __vectorcall _mm_not_si128(const register __m128i xmm0) throw() {
	return _mm_xor_si128(_xmm0, _mm_setone_si128());
}

// Compare ==

#ifndef __SSE4_1__ 
static __forceinline __m128i __vectorcall _mm_cmpeq_epi64(const register __m128i xmm0, const register __m128i xmm1) throw() {
	return _mm_castpd_si128 (_mm_cmpeq_pd(_mm_castsi128_pd (_xmm0), _mm_castsi128_pd (xmm1)));
}
#endif

static __forceinline __m128i __vectorcall _mm_cmpeq_epu8(const register __m128i xmm0, const register __m128i xmm1) throw() {
	return _mm_cmpeq_epi8(_xmm0, xmm1);
}

static __forceinline __m128i __vectorcall _mm_cmpeq_epu16(const register __m128i xmm0, const register __m128i xmm1) throw() {
	return _mm_cmpeq_epi16(_xmm0, xmm1);
}

static __forceinline __m128i __vectorcall _mm_cmpeq_epu32(const register __m128i xmm0, const register __m128i xmm1) throw() {
	return _mm_cmpeq_epi32(_xmm0, xmm1);
}

static __forceinline __m128i __vectorcall _mm_cmpeq_epu64(const register __m128i xmm0, const register __m128i xmm1) throw() {
	return _mm_cmpeq_epi64(_xmm0, xmm1);
}

// Compare !=

static __forceinline __m128i __vectorcall _mm_cmpneq_epi8(const register __m128i xmm0, const register __m128i xmm1) throw() {
	return _mm_not_si128(_mm_cmpeq_epi8(_xmm0, xmm1));
}

static __forceinline __m128i __vectorcall _mm_cmpneq_epi16(const register __m128i xmm0, const register __m128i xmm1) throw() {
	return _mm_not_si128(_mm_cmpeq_epi16(_xmm0, xmm1));
}

static __forceinline __m128i __vectorcall _mm_cmpneq_epi32(const register __m128i xmm0, const register __m128i xmm1) throw() {
	return _mm_not_si128(_mm_cmpeq_epi32(_xmm0, xmm1));
}

static __forceinline __m128i __vectorcall _mm_cmpneq_epi64(const register __m128i xmm0, const register __m128i xmm1) throw() {
	return _mm_not_si128(_mm_cmpeq_epi64(_xmm0, xmm1));
}

static __forceinline __m128i __vectorcall _mm_cmpneq_epu8(const register __m128i xmm0, const register __m128i xmm1) throw() {
	return _mm_cmpneq_epi8(_xmm0, xmm1);
}

static __forceinline __m128i __vectorcall _mm_cmpneq_epu16(const register __m128i xmm0, const register __m128i xmm1) throw() {
	return _mm_cmpneq_epi16(_xmm0, xmm1);
}

static __forceinline __m128i __vectorcall _mm_cmpneq_epu32(const register __m128i xmm0, const register __m128i xmm1) throw() {
	return _mm_cmpneq_epi32(_xmm0, xmm1);
}

static __forceinline __m128i __vectorcall _mm_cmpneq_epu64(const register __m128i xmm0, const register __m128i xmm1) throw() {
	return _mm_cmpneq_epi64(_xmm0, xmm1);
}

// Compare <=

static __forceinline __m128i __vectorcall _mm_cmple_epi8(const register __m128i xmm0, const register __m128i xmm1) throw() {
	return _mm_cmpgt_epi8(_xmm1, xmm0);
}

static __forceinline __m128i __vectorcall _mm_cmple_epi16(const register __m128i xmm0, const register __m128i xmm1) throw() {
	return _mm_cmpgt_epi16(_xmm1, xmm0);
}

static __forceinline __m128i __vectorcall _mm_cmple_epi32(const register __m128i xmm0, const register __m128i xmm1) throw() {
	return _mm_cmpgt_epi32(_xmm1, xmm0);
}

static __forceinline __m128i __vectorcall _mm_cmple_epi64(const register __m128i xmm0, const register __m128i xmm1) throw() {
	__declspec(align(16)) int64_t buffer0[2];
	__declspec(align(16)) int64_t buffer1[2];
	_mm_store_si128(reinterpret_cast<__m128i*>(buffer0), xmm0);
	_mm_store_si128(reinterpret_cast<__m128i*>(buffer1), xmm1);
	buffer0[0] = buffer0[0] <= buffer1[0];
	buffer0[1] = buffer0[1] <= buffer1[1];
	return _mm_load_si128(reinterpret_cast<__m128i*>(buffer0));
}

static __forceinline __m128i __vectorcall _mm_cmple_epu8(const register __m128i xmm0, const register __m128i xmm1) throw() {
	return _mm_cmple_epi8(_xmm0, xmm1);
}

static __forceinline __m128i __vectorcall _mm_cmple_epu16(const register __m128i xmm0, const register __m128i xmm1) throw() {
	return _mm_cmple_epi16(_xmm0, xmm1);
}

static __forceinline __m128i __vectorcall _mm_cmple_epu32(const register __m128i xmm0, const register __m128i xmm1) throw() {
	return _mm_cmple_epi32(_xmm0, xmm1);
}

static __forceinline __m128i __vectorcall _mm_cmple_epu64(const register __m128i xmm0, const register __m128i xmm1) throw() {
	return _mm_cmple_epi64(_xmm0, xmm1);
}

// Compare >=

static __forceinline __m128i __vectorcall _mm_cmpge_epi8(const register __m128i xmm0, const register __m128i xmm1) throw() {
	return _mm_cmplt_epi8(_xmm1, xmm0);
}

static __forceinline __m128i __vectorcall _mm_cmpge_epi16(const register __m128i xmm0, const register __m128i xmm1) throw() {
	return _mm_cmplt_epi16(_xmm1, xmm0);
}

static __forceinline __m128i __vectorcall _mm_cmpge_epi32(const register __m128i xmm0, const register __m128i xmm1) throw() {
	return _mm_cmplt_epi32(_xmm1, xmm0);
}

static __forceinline __m128i __vectorcall _mm_cmpge_epi64(const register __m128i xmm0, const register __m128i xmm1) throw() {
	__declspec(align(16)) int64_t buffer0[2];
	__declspec(align(16)) int64_t buffer1[2];
	_mm_store_si128(reinterpret_cast<__m128i*>(buffer0), xmm0);
	_mm_store_si128(reinterpret_cast<__m128i*>(buffer1), xmm1);
	buffer0[0] = buffer0[0] >= buffer1[0];
	buffer0[1] = buffer0[1] >= buffer1[1];
	return _mm_load_si128(reinterpret_cast<__m128i*>(buffer0));
}

static __forceinline __m128i __vectorcall _mm_cmpge_epu8(const register __m128i xmm0, const register __m128i xmm1) throw() {
	return _mm_cmpge_epi8(_xmm0, xmm1);
}

static __forceinline __m128i __vectorcall _mm_cmpge_epu16(const register __m128i xmm0, const register __m128i xmm1) throw() {
	return _mm_cmpge_epi16(_xmm0, xmm1);
}

static __forceinline __m128i __vectorcall _mm_cmpge_epu32(const register __m128i xmm0, const register __m128i xmm1) throw() {
	return _mm_cmpge_epi32(_xmm0, xmm1);
}

static __forceinline __m128i __vectorcall _mm_cmpge_epu64(const register __m128i xmm0, const register __m128i xmm1) throw() {
	return _mm_cmpge_epi64(_xmm0, xmm1);
}

// Compare < 

static __forceinline __m128i __vectorcall _mm_cmplt_epi64(const register __m128i xmm0, const register __m128i xmm1) throw() {
	return _mm_cmpge_epi64(xmm1, xmm0);
}

// _mm_cmplt_epu8
// _mm_cmplt_epu16
// _mm_cmplt_epu32
// _mm_cmplt_epu64

// Compare >

static __forceinline __m128i __vectorcall _mm_cmpgt_epi64(const register __m128i xmm0, const register __m128i xmm1) throw() {
	return _mm_cmple_epi64(xmm1, xmm0);
}

// _mm_cmpgt_epu8
// _mm_cmpgt_epu16
// _mm_cmpgt_epu32
// _mm_cmpgt_epu64

// Add

// _mm_add_epu32
// _mm_add_epu64

// Subtract

// _mm_sub_epu32
// _mm_sub_epu64

// Multiply

// _mm_mul_epi8
// _mm_mul_epi16
#ifndef __SSE4_1__
// _mm_mul_epi32
#endif
// _mm_mul_epi64
// _mm_mul_epu8
// _mm_mul_epu16
// _mm_mul_epu64

// Divide

// _mm_div_epi8
// _mm_div_epi16
// _mm_div_epi32
// _mm_div_epi64
// _mm_div_epu8
// _mm_div_epu16
// _mm_div_epu32
// _mm_div_epu64

// Square root

// _mm_sqrt_epi64

static __forceinline __m128i __vectorcall _mm_sqrt_epi32(const register __m128i xmm0) throw() {
	return _mm_cvtps_epi32(_mm_sqrt_ps(_mm_cvtepi32_ps(xmm0)));
}

static __forceinline __m128i __vectorcall _mm_sqrt_epi16(const register __m128i xmm0) throw() {
#ifdef __AVX2__
	register __m256i xmm1 = _mm256_cvtepi16_epi32(xmm0);
	xmm1 = _mm256_cvtps_epi32(_mm256_sqrt_ps (_mm256_cvtepi32_ps(xmm0)));
	return _mm256_extractf128_si256(_mm256_packs_epi32(xmm1, xmm1), 0);
#else
	//! \todo Optimise
	__declspec(align(32)) int16_t buffer0[8];
	__declspec(align(32)) int32_t buffer1[8];
	_mm_store_si128(reinterpret_cast<__m128i*>(buffer0), xmm0));
	buffer1[0] = buffer0[0];
	buffer1[1] = buffer0[1];
	buffer1[2] = buffer0[2];
	buffer1[3] = buffer0[3];
	buffer1[4] = buffer0[4];
	buffer1[5] = buffer0[5];
	buffer1[6] = buffer0[6];
	buffer1[7] = buffer0[7];
	register __m128i xmm1 = _mm_load_si128(reinterpret_cast<__m128i*>(buffer1));
	register __m128i xmm2 = _mm_load_si128(reinterpret_cast<__m128i*>(buffer1 + 4));
	xmm1 = _mm_sqrt_epi32(xmm1);
	xmm1 = _mm_sqrt_epi32(xmm2);
	return _mm_packs_epi32(xmm1, xmm2);
#endif
}

static __forceinline __m128i __vectorcall _mm_sqrt_epi8(const register __m128i xmm0) throw() {
#ifdef __AVX2__
	const register __m256i xmm1 = _mm256_cvtepi8_epi16(xmm0);
	const register __m128i xmm2 = _mm_sqrt_epi16(_mm256_extractf128_si256(xmm1,0));
	const register __m128i xmm3 = _mm_sqrt_epi16(_mm256_extractf128_si256(xmm1,1));
	return _mm_packs_epi16(xmm2, xmm3);
#else
	//! \todo Optimise
	__declspec(align(32)) int8_t buffer0[16];
	__declspec(align(32)) int16_t buffer1[8];
	_mm_store_si128(reinterpret_cast<__m128i*>(buffer0), xmm0));
	buffer1[0] = buffer0[0];
	buffer1[1] = buffer0[1];
	buffer1[2] = buffer0[2];
	buffer1[3] = buffer0[3];
	buffer1[4] = buffer0[4];
	buffer1[5] = buffer0[5];
	buffer1[6] = buffer0[6];
	buffer1[7] = buffer0[7];
	buffer1[8] = buffer0[8];
	buffer1[9] = buffer0[9];
	buffer1[10] = buffer0[10];
	buffer1[11] = buffer0[11];
	buffer1[12] = buffer0[12];
	buffer1[13] = buffer0[13];
	buffer1[14] = buffer0[14];
	buffer1[15] = buffer0[15];
	register __m128i xmm1 = _mm_load_si128(reinterpret_cast<__m128i*>(buffer1));
	register __m128i xmm2 = _mm_load_si128(reinterpret_cast<__m128i*>(buffer1 + 8));
	xmm1 = _mm_sqrt_epi16(xmm1);
	xmm1 = _mm_sqrt_epi16(xmm2);
	return _mm_packs_epi16(xmm1, xmm2);
#endif
}

// _mm_sqrt_epu64
// _mm_sqrt_epu32
// _mm_sqrt_epu16
// _mm_sqrt_epu8