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

#ifndef ANVIL_MATHS_VECTOR_HPP
#define ANVIL_MATHS_VECTOR_HPP

#include <iostream>
#include "anvil/Core/Cpu.hpp"
#include "anvil/Core/Constants.hpp"
#include "anvil/Core/Keywords.hpp"

#if ANVIL_ARCHITECTURE == ANVIL_X86 || ANVIL_ARCHITECTURE == ANVIL_X64
	#include <immintrin.h>
	#define ANVIL_VECTOR_CALL __vectorcall

	#define ANVIL_MMX 1
	#define ANVIL_SSE 2
	#define ANVIL_SSE2 3
	#define ANVIL_SSE3 4
	#define ANVIL_SSSE3 5
	#define ANVIL_SSE4_1 6
	#define ANVIL_SSE4_2 7
	#define ANVIL_AVX 8
	#define ANVIL_AVX2 9
	#define ANVIL_FMA 10
	#define ANVIL_SIMD_AVX_512_F 11
	#define ANVIL_SIMD_AVX_512_PF 12
	#define ANVIL_SIMD_AVX_512_ER 13
	#define ANVIL_SIMD_AVX_512_CD 14
#else
	#define ANVIL_VECTOR_CALL ANVIL_CALL
#endif

template<class T, size_t S, int VER = 0>
struct VectorInfo;

#if ANVIL_ARCHITECTURE == ANVIL_X86 || ANVIL_ARCHITECTURE == ANVIL_X64
	template<int VER>
	struct VectorInfo<float, 4, VER> {
		typedef __m128 vector_t;
		typedef float scalar_t;
		enum { size = 4, optimised = 1 };

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL load(const void* aAddress) throw() {
			return _mm_loadu_ps(static_cast<const float*>(aAddress));
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL load16(const void* aAddress) throw() {
			return _mm_load_ps(static_cast<const float*>(aAddress));
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL load32(const void* aAddress) throw() {
			return _mm_load_ps(static_cast<const float*>(aAddress));
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL loadr(const void* aAddress) throw() {
			const register vector_t tmp = _mm_loadu_ps(static_cast<const float*>(aAddress));
			return _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(0, 1, 2, 3));
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL loadr16(const void* aAddress) throw() {
			return _mm_loadr_ps(static_cast<const float*>(aAddress));
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL loadr32(const void* aAddress) throw() {
			return _mm_loadr_ps(static_cast<const float*>(aAddress));
		}

		ANVIL_STRONG_INLINE static void ANVIL_VECTOR_CALL store(void* aAddress, const register vector_t aValue) throw() {
			return _mm_storeu_ps(static_cast<float*>(aAddress), aValue);
		}

		ANVIL_STRONG_INLINE static void ANVIL_VECTOR_CALL store16(void* aAddress, const register vector_t aValue) throw() {
			_mm_store_ps(static_cast<float*>(aAddress), aValue);
		}

		ANVIL_STRONG_INLINE static void ANVIL_VECTOR_CALL store32(void* aAddress, const register vector_t aValue) throw() {
			_mm_store_ps(static_cast<float*>(aAddress), aValue);
		}

		ANVIL_STRONG_INLINE static void ANVIL_VECTOR_CALL storer(void* aAddress, const register vector_t aValue) throw() {
			_mm_store_ps(static_cast<float*>(aAddress), _mm_shuffle_ps(aValue, aValue, _MM_SHUFFLE(0, 1, 2, 3)));
		}

		ANVIL_STRONG_INLINE static void ANVIL_VECTOR_CALL storer16(void* aAddress, const register vector_t aValue) throw() {
			return _mm_storer_ps(static_cast<float*>(aAddress), aValue);
		}

		ANVIL_STRONG_INLINE static void ANVIL_VECTOR_CALL storer32(void* aAddress, const register vector_t aValue) throw() {
			return _mm_storer_ps(static_cast<float*>(aAddress), aValue);
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL reverse(const register vector_t aValue) throw() {
			return _mm_shuffle_ps(aValue, aValue, _MM_SHUFFLE(0, 1, 2, 3));
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL fill0() throw() {
			return _mm_setzero_ps();
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL fill_scalar(const scalar_t aValue) throw() {
			return _mm_set1_ps(aValue);
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL set_channel(register vector_t aValue, const int aIndex, const scalar_t aScalar) throw() {
			aValue.m128_f32[aIndex] = aScalar; //! \todo Optimise
			return aValue;
		}

		ANVIL_STRONG_INLINE static scalar_t ANVIL_VECTOR_CALL get_channel(const register vector_t aValue, const int aIndex) throw() {
			return aValue.m128_f32[aIndex]; //! \todo Optimise
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL add(const register vector_t xmm0, const vector_t xmm1) throw() {
			return _mm_add_ps(xmm0, xmm1);
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL subtract(const register vector_t xmm0, const vector_t xmm1) throw() {
			return _mm_sub_ps(xmm0, xmm1);
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL multiply(const register vector_t xmm0, const vector_t xmm1) throw() {
			return _mm_mul_ps(xmm0, xmm1);
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL divide(const register vector_t xmm0, const vector_t xmm1) throw() {
			return _mm_div_ps(xmm0, xmm1);
		}

#define ANVIL_HORISONTAL_HELPER(NAME)\
		register __m128 xmm2;\
		register __m128 xmm3;\
		xmm2.m128_f32[0] = xmm0.m128_f32[0];\
		xmm3.m128_f32[0] = xmm0.m128_f32[1];\
		xmm2.m128_f32[1] = xmm0.m128_f32[3];\
		xmm3.m128_f32[1] = xmm0.m128_f32[4];\
		xmm2.m128_f32[2] = xmm1.m128_f32[0];\
		xmm3.m128_f32[2] = xmm1.m128_f32[1];\
		xmm2.m128_f32[3] = xmm1.m128_f32[3];\
		xmm3.m128_f32[3] = xmm1.m128_f32[4];\
		return NAME(xmm2, xmm3);

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL add_horisontal(const register vector_t xmm0, const vector_t xmm1) throw() {
			if (VER >= ANVIL_SSE3) {
				return _mm_hadd_ps(xmm0, xmm1);
			} else {
				ANVIL_HORISONTAL_HELPER(_mm_add_ps);
			}
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL subtract_horisontal(const register vector_t xmm0, const vector_t xmm1) throw() {
			if (VER >= ANVIL_SSE3) {
				return _mm_hsub_ps(xmm0, xmm1);
			} else {
				ANVIL_HORISONTAL_HELPER(_mm_sub_ps);
			}
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL multiply_horisontal(const register vector_t xmm0, const vector_t xmm1) throw() {
			ANVIL_HORISONTAL_HELPER(_mm_mul_ps);
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL divide_horisontal(const register vector_t xmm0, const vector_t xmm1) throw() {
			ANVIL_HORISONTAL_HELPER(_mm_div_ps);
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL lshift(const register vector_t xmm0, const int32_t* count) throw() {
			const __m128i xmm1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(count));
			const __m128i xmm2 = _mm_sll_epi32(_mm_castps_si128(xmm0), xmm1);
			return _mm_castsi128_ps(xmm2);
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL rshift(const register vector_t xmm0, const int32_t* count) throw() {
			const __m128i xmm1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(count));
			const __m128i xmm2 = _mm_srl_epi32(_mm_castps_si128(xmm0), xmm1);
			return _mm_castsi128_ps(xmm2);
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL and(const register vector_t xmm0, const vector_t xmm1) throw() {
			return _mm_and_ps(xmm0, xmm1);
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL or(const register vector_t xmm0, const vector_t xmm1) throw() {
			return _mm_or_ps(xmm0, xmm1);
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL xor(const register vector_t xmm0, const vector_t xmm1) throw() {
			return _mm_or_ps(xmm0, xmm1);
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL not(const register vector_t xmm0) throw() {
			return _mm_xor_ps(xmm0, _mm_cmpeq_ps(xmm0, xmm0));
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL and_horisontal(const register vector_t xmm0, const vector_t xmm1) throw() {
			ANVIL_HORISONTAL_HELPER(_mm_and_ps);
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL or_horisontal(const register vector_t xmm0, const vector_t xmm1) throw() {
			ANVIL_HORISONTAL_HELPER(_mm_or_ps);
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL xor_horisontal(const register vector_t xmm0, const vector_t xmm1) throw() {
			ANVIL_HORISONTAL_HELPER(_mm_xor_ps);
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL compare_eq(const register vector_t xmm0, const vector_t xmm1) throw() {
			return _mm_cmpeq_ps(xmm0, xmm1);
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL compare_ne(const register vector_t xmm0, const vector_t xmm1) throw() {
			return _mm_cmpneq_ps(xmm0, xmm1);
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL compare_gt(const register vector_t xmm0, const vector_t xmm1) throw() {
			return _mm_cmpngt_ps(xmm0, xmm1);
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL compare_ge(const register vector_t xmm0, const vector_t xmm1) throw() {
			return _mm_cmpnge_ps(xmm0, xmm1);
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL compare_lt(const register vector_t xmm0, const vector_t xmm1) throw() {
			return _mm_cmpnlt_ps(xmm0, xmm1);
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL compare_le(const register vector_t xmm0, const vector_t xmm1) throw() {
			return _mm_cmpnle_ps(xmm0, xmm1);
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL compare_eq_horisontal(const register vector_t xmm0, const vector_t xmm1) throw() {
			ANVIL_HORISONTAL_HELPER(_mm_cmpeq_ps);
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL compare_ne_horisontal(const register vector_t xmm0, const vector_t xmm1) throw() {
			ANVIL_HORISONTAL_HELPER(_mm_cmpneq_ps);
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL compare_gt_horisontal(const register vector_t xmm0, const vector_t xmm1) throw() {
			ANVIL_HORISONTAL_HELPER(_mm_cmpgt_ps);
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL compare_ge_horisontal(const register vector_t xmm0, const vector_t xmm1) throw() {
			ANVIL_HORISONTAL_HELPER(_mm_cmpge_ps);
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL compare_lt_horisontal(const register vector_t xmm0, const vector_t xmm1) throw() {
			ANVIL_HORISONTAL_HELPER(_mm_cmplt_ps);
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL compare_le_horisontal(const register vector_t xmm0, const vector_t xmm1) throw() {
			ANVIL_HORISONTAL_HELPER(_mm_cmple_ps);
		}

		ANVIL_STRONG_INLINE static scalar_t ANVIL_VECTOR_CALL sum(const register vector_t xmm0) throw() {
			if (VER >= ANVIL_SSE3) {
				const register vector_t xmm1 = _mm_hadd_ps(xmm0, xmm0);
				return = _mm_add_ss(_mm_hadd_ps(xmm1, xmm1)).m128_f32[0];
			} else {
				ANVIL_ALIGN(16) float buffer[4];
				_mm_store_ps(buffer, xmm0);
				return buffer[0] + buffer[1] + buffer[2] + buffer[3];
			}
		}

		ANVIL_STRONG_INLINE static scalar_t ANVIL_VECTOR_CALL abs(const register vector_t xmm0) throw() {
			const register vector_t xmm1 = _mm_cmpgt_ps(xmm0, _mm_setzero_ps());
			const register vector_t xmm2 = _mm_mul_ps(xmm0, _mm_set1_ps(1.f));
			return _mm_or_ps(_mm_and_ps(xmm1, xmm0), _mm_andnot_ps(xmm1, xmm2));
		}

		ANVIL_STRONG_INLINE static scalar_t ANVIL_VECTOR_CALL sqrt(const register vector_t xmm0) throw() {
			return _mm_sqrt_ps(xmm0);
		}

		ANVIL_STRONG_INLINE static scalar_t ANVIL_VECTOR_CALL cbrt(const register vector_t xmm0) throw() {
			ANVIL_ALIGN(16) float buffer[4];
			_mm_store_ps(buffer, xmm0);
			buffer[0] = std::cbrt(buffer[0]);
			buffer[1] = std::cbrt(buffer[1]);
			buffer[2] = std::cbrt(buffer[2]);
			buffer[3] = std::cbrt(buffer[3]);
			return _mm_load_ps(buffer);
		}

		ANVIL_STRONG_INLINE static scalar_t ANVIL_VECTOR_CALL floor(const register vector_t xmm0) throw() {
			if (VER >= ANVIL_SSE4_1) {
				return _mm_floor_ps(xmm0);
			} else {
				ANVIL_ALIGN(16) float buffer[4];
				_mm_store_ps(buffer, xmm0);
				buffer[0] = std::floor(buffer[0]);
				buffer[1] = std::floor(buffer[1]);
				buffer[2] = std::floor(buffer[2]);
				buffer[3] = std::floor(buffer[3]);
				return _mm_load_ps(buffer);
			}
		}

		ANVIL_STRONG_INLINE static scalar_t ANVIL_VECTOR_CALL ceil(const register vector_t xmm0) throw() {
			if (VER >= ANVIL_SSE4_1) {
				return _mm_ceil_ps(xmm0);
			} else {
				ANVIL_ALIGN(16) float buffer[4];
				_mm_store_ps(buffer, xmm0);
				buffer[0] = std::ceil(buffer[0]);
				buffer[1] = std::ceil(buffer[1]);
				buffer[2] = std::ceil(buffer[2]);
				buffer[3] = std::ceil(buffer[3]);
				return _mm_load_ps(buffer);
			}
		}

		ANVIL_STRONG_INLINE static scalar_t ANVIL_VECTOR_CALL round(const register vector_t xmm0) throw() {
			if (VER >= ANVIL_SSE4_1) {
				return _mm_round_ps(xmm0, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
			} else {
				ANVIL_ALIGN(16) float buffer[4];
				_mm_store_ps(buffer, xmm0);
				buffer[0] = std::round(buffer[0]);
				buffer[1] = std::round(buffer[1]);
				buffer[2] = std::round(buffer[2]);
				buffer[3] = std::round(buffer[3]);
				return _mm_load_ps(buffer);
			}
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL fma(const register vector_t xmm0, const vector_t xmm1, const vector_t xmm2) throw() {
			if (VER >= ANVIL_FMA) {
				return _mm_fma_ps(xmm0, xmm1, xmm2);
			} else {
				ANVIL_ALIGN(16) float a[4];
				ANVIL_ALIGN(16) float b[4];
				ANVIL_ALIGN(16) float c[4];
				_mm_store_ps(a, xmm0);
				_mm_store_ps(b, xmm1);
				_mm_store_ps(c, xmm2);
				a[0] = (a[0] * b[0]) + c[0];
				a[1] = (a[1] * b[1]) + c[1];
				a[2] = (a[2] * b[2]) + c[2];
				a[3] = (a[3] * b[3]) + c[3];
				return _mm_load_ps(a);
			}
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL fms(register vector_t xmm0, const vector_t xmm1, const vector_t xmm2) throw() {
			if (VER >= ANVIL_FMA) {
				return _mm_fms_ps(xmm0, xmm1, xmm2);
			} else {
				ANVIL_ALIGN(16) float a[4];
				ANVIL_ALIGN(16) float b[4];
				ANVIL_ALIGN(16) float c[4];
				_mm_store_ps(a, xmm0);
				_mm_store_ps(b, xmm1);
				_mm_store_ps(c, xmm2);
				a[0] = (a[0] * b[0]) - c[0];
				a[1] = (a[1] * b[1]) - c[1];
				a[2] = (a[2] * b[2]) - c[2];
				a[3] = (a[3] * b[3]) - c[3];
				return _mm_load_ps(a);
			}
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL power(register vector_t xmm0, const vector_t xmm1) throw() {
			ANVIL_ALIGN(16) float a[4];
			ANVIL_ALIGN(16) float b[4];
			_mm_store_ps(a, xmm0);
			_mm_store_ps(b, xmm1);
			a[0] = std::pow(a[0], b[0]);
			a[1] = std::pow(a[1], b[1]);
			a[2] = std::pow(a[2], b[2]);
			a[3] = std::pow(a[3], b[3]);
			return _mm_load_ps(a);
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL min(register vector_t xmm0, const vector_t xmm1) throw() {
			return _mm_min_ps(xmm0, xmm1);
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL max(register vector_t xmm0, const vector_t xmm1) throw() {
			return _mm_max_ps(xmm0, xmm1);
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL min_horisontal(const register vector_t xmm0, const vector_t xmm1) throw() {
			ANVIL_HORISONTAL_HELPER(_mm_min_ps);
		}

		ANVIL_STRONG_INLINE static vector_t ANVIL_VECTOR_CALL max_horisontal(const register vector_t xmm0, const vector_t xmm1) throw() {
			ANVIL_HORISONTAL_HELPER(_mm_max_ps);
		}

		ANVIL_STRONG_INLINE static scalar_t ANVIL_VECTOR_CALL min(const register vector_t xmm0) throw() {
			ANVIL_ALIGN(16) float buffer[4];
			_mm_store_ps(buffer, xmm0);
			return std::min(std::min(buffer[0], buffer[1]), std::min(buffer[2], buffer[3]));
		}

		ANVIL_STRONG_INLINE static scalar_t ANVIL_VECTOR_CALL max(const register vector_t xmm0) throw() {
			ANVIL_ALIGN(16) float buffer[4];
			_mm_store_ps(buffer, xmm0);
			return std::max(std::max(buffer[0], buffer[1]), std::max(buffer[2], buffer[3]));
		}
	};
#endif

#endif