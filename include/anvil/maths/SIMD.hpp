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

#ifndef ANVIL_MATHS_SIMD_HPP
#define ANVIL_MATHS_SIMD_HPP

	//! \todo Specialise OP_CAST
	//! \todo Implement OP_POPCN
	//! \todo Implement OP_REFLECT

#include <cmath>
#include "anvil/core/Cpu.hpp"
#include "anvil/core/Keywords.hpp"

#if ANVIL_ARCHITECTURE == ANVIL_X86 || ANVIL_ARCHITECTURE == ANVIL_X64
	#define ANVIL_USE_INTEL_SIMD_INTRINSICS
	#if ANVIL_COMPILER == ANVIL_MSVC
		#include <immintrin.h>
		#include <intrin.h>
	#else
		#include <x86intrin.h>
	#endif
	#define ANVIL_SIMD_CALL __vectorcall 
#elif ANVIL_ARCHITECTURE == ANVIL_ARM
	#define ANVIL_USE_NEON_SIMD_INTRINSICS
	#include <arm_neon.h>
#endif

#ifndef ANVIL_SIMD_CALL
	#define ANVIL_SIMD_CALL ANVIL_CALL
#endif

#ifdef ANVIL_USE_INTEL_SIMD_INTRINSICS

#define _simd_f64x2 __m128d

#define _simd_f64x4 __m256d

#define _simd_f64x4_splitlo_(X) _mm256_extractf128_pd(X,0)
#define _simd_f64x4_splitlo_instruction_set anvil::simd::AVX
#define _simd_f64x4_splithi_(X) _mm256_extractf128_pd(X,1)
#define _simd_f64x4_splithi_instruction_set anvil::simd::AVX
#define _simd_f64x4_combine_(X,Y) _mm256_insertf128_pd(_mm256_insertf128_pd(_mm256_undefined_pd(),X,0),Y,1)
#define _simd_f64x4_combine_instruction_set anvil::simd::AVX

#define _simd_f32x4 __m128
#define _simd_f32x8 __m256

#define _simd_f32x8_splitlo_(X) _mm256_extractf128_ps(X,0)
#define _simd_f32x8_splitlo_instruction_set anvil::simd::AVX
#define _simd_f32x8_splithi_(X) _mm256_extractf128_ps(X,1)
#define _simd_f32x8_splithi_instruction_set anvil::simd::AVX
#define _simd_f32x8_combine_(X,Y) _mm256_insertf128_ps(_mm256_insertf128_ps(_mm256_undefined_ps(),X,0),Y,1)
#define _simd_f32x8_combine_instruction_set anvil::simd::AVX

#define _simd_s64x2 __m128i
#define _simd_s64x4 __m256i

#define _simd_s64x4_splitlo_(X) _mm256_extractf128_si256(X,0)
#define _simd_s64x4_splitlo_instruction_set anvil::simd::AVX
#define _simd_s64x4_splithi_(X) _mm256_extractf128_si256(X,1)
#define _simd_s64x4_splithi_instruction_set anvil::simd::AVX
#define _simd_s64x4_combine_(X,Y) _mm256_insertf128_si256(_mm256_insertf128_si256(_mm256_undefined_si256(),X,0),Y,1)
#define _simd_s64x4_combine_instruction_set anvil::simd::AVX

#define _simd_u64x2 __m128i
#define _simd_u64x4 __m256i

#define _simd_u64x4_splitlo_(X)             _simd_s64x4_splitlo_(X)
#define _simd_u64x4_splitlo_instruction_set _simd_s64x4_splitlo_instruction_set
#define _simd_u64x4_splithi_(X)             _simd_s64x4_splithi_(X)
#define _simd_u64x4_splithi_instruction_set _simd_s64x4_splithi_instruction_set
#define _simd_u64x4_combine_(X,Y)           _simd_s64x4_combine_(X,Y)
#define _simd_u64x4_combine_instruction_set _simd_s64x4_combine_instruction_set

#define _simd_s32x4 __m128i
#define _simd_s32x8 __m256i

#define _simd_s32x8_splitlo_(X)             _simd_s64x4_splitlo_(X)
#define _simd_s32x8_splitlo_instruction_set _simd_s64x4_splitlo_instruction_set
#define _simd_s32x8_splithi_(X)             _simd_s64x4_splithi_(X)
#define _simd_s32x8_splithi_instruction_set _simd_s64x4_splithi_instruction_set
#define _simd_s32x8_combine_(X,Y)           _simd_s64x4_combine_(X,Y)
#define _simd_s32x8_combine_instruction_set _simd_s64x4_combine_instruction_set

#define _simd_u32x4 __m128i
#define _simd_u32x8 __m256i

#define _simd_u32x8_splitlo_(X)             _simd_s64x4_splitlo_(X)
#define _simd_u32x8_splitlo_instruction_set _simd_s64x4_splitlo_instruction_set
#define _simd_u32x8_splithi_(X)             _simd_s64x4_splithi_(X)
#define _simd_u32x8_splithi_instruction_set _simd_s64x4_splithi_instruction_set
#define _simd_u32x8_combine_(X,Y)           _simd_s64x4_combine_(X,Y)
#define _simd_u32x8_combine_instruction_set _simd_s64x4_combine_instruction_set

#define _simd_s16x8 __m128i
#define _simd_s16x16 __m256i

#define _simd_s16x16_splitlo_(X)             _simd_s64x4_splitlo_(X)
#define _simd_s16x16_splitlo_instruction_set _simd_s64x4_splitlo_instruction_set
#define _simd_s16x16_splithi_(X)             _simd_s64x4_splithi_(X)
#define _simd_s16x16_splithi_instruction_set _simd_s64x4_splithi_instruction_set
#define _simd_s16x16_combine_(X,Y)           _simd_s64x4_combine_(X,Y)
#define _simd_s16x16_combine_instruction_set _simd_s64x4_combine_instruction_set

#define _simd_u16x8 __m128i
#define _simd_u16x16 __m256i

#define _simd_u16x16_splitlo_(X)             _simd_s64x4_splitlo_(X)
#define _simd_u16x16_splitlo_instruction_set _simd_s64x4_splitlo_instruction_set
#define _simd_u16x16_splithi_(X)             _simd_s64x4_splithi_(X)
#define _simd_u16x16_splithi_instruction_set _simd_s64x4_splithi_instruction_set
#define _simd_u16x16_combine_(X,Y)           _simd_s64x4_combine_(X,Y)
#define _simd_u16x16_combine_instruction_set _simd_s64x4_combine_instruction_set

#define _simd_s8x16 __m128i
#define _simd_s8x32 __m256i

#define _simd_s8x32_splitlo_(X)             _simd_s64x4_splitlo_(X)
#define _simd_s8x32_splitlo_instruction_set _simd_s64x4_splitlo_instruction_set
#define _simd_s8x32_splithi_(X)             _simd_s64x4_splithi_(X)
#define _simd_s8x32_splithi_instruction_set _simd_s64x4_splithi_instruction_set
#define _simd_s8x32_combine_(X,Y)           _simd_s64x4_combine_(X,Y)
#define _simd_s8x32_combine_instruction_set _simd_s64x4_combine_instruction_set

#define _simd_u8x16 __m128i
#define _simd_u8x32 __m256i

#define _simd_u8x32_splitlo_(X)             _simd_s64x4_splitlo_(X)
#define _simd_u8x32_splitlo_instruction_set _simd_s64x4_splitlo_instruction_set
#define _simd_u8x32_splithi_(X)             _simd_s64x4_splithi_(X)
#define _simd_u8x32_splithi_instruction_set _simd_s64x4_splithi_instruction_set
#define _simd_u8x32_combine_(X,Y)           _simd_s64x4_combine_(X,Y)
#define _simd_u8x32_combine_instruction_set _simd_s64x4_combine_instruction_set

#define _simd_f64x2_load_(X) _mm_load_pd(X)
#define _simd_f64x2_load_instruction_set anvil::simd::IS_SSE

#define _simd_f64x4_load_(X) _mm256_load_pd(X)
#define _simd_f64x4_load_instruction_set anvil::simd::IS_AVX

#define _simd_f32x4_load_(X) _mm_load_ps(X)
#define _simd_f32x4_load_instruction_set anvil::simd::IS_SSE

#define _simd_f32x8_load_(X) _mm256_load_ps(X)
#define _simd_f32x8_load_instruction_set anvil::simd::IS_AVX

#define _simd_s64x2_load_(X) _mm_load_si128(reinterpret_cast<const __m128i*>(X))
#define _simd_s64x2_load_instruction_set anvil::simd::IS_SSE

#define _simd_s64x4_load_(X) _mm256_load_si256(reinterpret_cast<const __m256i*>(X))
#define _simd_s64x4_load_instruction_set anvil::simd::IS_AVX

#define _simd_s32x4_load_(X) _mm_load_si128(reinterpret_cast<const __m128i*>(X))
#define _simd_s32x4_load_instruction_set anvil::simd::IS_SSE

#define _simd_s32x8_load_(X) _mm256_load_si256(reinterpret_cast<const __m256i*>(X))
#define _simd_s32x8_load_instruction_set anvil::simd::IS_AVX

#define _simd_s16x8_load_(X) _mm_load_si128(reinterpret_cast<const __m128i*>(X))
#define _simd_s16x8_load_instruction_set anvil::simd::IS_SSE

#define _simd_s16x16_load_(X) _mm256_load_si256(reinterpret_cast<const __m256i*>(X))
#define _simd_s16x16_load_instruction_set anvil::simd::IS_AVX

#define _simd_s8x16_load_(X) _mm_load_si128(reinterpret_cast<const __m128i*>(X))
#define _simd_s8x16_load_instruction_set anvil::simd::IS_SSE

#define _simd_s8x32_load_(X) _mm256_load_si256(reinterpret_cast<const __m256i*>(X))
#define _simd_s8x32_load_instruction_set anvil::simd::IS_AVX

#define _simd_u64x2_load_(X) _mm_load_si128(reinterpret_cast<const __m128i*>(X))
#define _simd_u64x2_load_instruction_set anvil::simd::IS_SSE

#define _simd_u64x4_load_(X) _mm256_load_si256(reinterpret_cast<const __m256i*>(X))
#define _simd_u64x4_load_instruction_set anvil::simd::IS_AVX

#define _simd_u32x4_load_(X) _mm_load_si128(reinterpret_cast<const __m128i*>(X))
#define _simd_u32x4_load_instruction_set anvil::simd::IS_SSE

#define _simd_u32x8_load_(X) _mm256_load_si256(reinterpret_cast<const __m256i*>(X))
#define _simd_u32x8_load_instruction_set anvil::simd::IS_AVX

#define _simd_u16x8_load_(X) _mm_load_si128(reinterpret_cast<const __m128i*>(X))
#define _simd_u16x8_load_instruction_set anvil::simd::IS_SSE

#define _simd_u16x16_load_(X) _mm256_load_si256(reinterpret_cast<const __m256i*>(X))
#define _simd_u16x16_load_instruction_set anvil::simd::IS_AVX

#define _simd_u8x16_load_(X) _mm_load_si128(reinterpret_cast<const __m128i*>(X))
#define _simd_u8x16_load_instruction_set anvil::simd::IS_SSE

#define _simd_u8x32_load_(X) _mm256_load_si256(reinterpret_cast<const __m256i*>(X))
#define _simd_u8x32_load_instruction_set anvil::simd::IS_AVX

#define _simd_f64x2_add_(X,Y) _mm_add_pd(X,Y)
#define _simd_f64x2_add_instruction_set anvil::simd::IS_SSE_2

#define _simd_f64x4_add_(X,Y) _mm256_add_pd(X,Y)
#define _simd_f64x4_add_instruction_set anvil::simd::IS_AVX

#define _simd_f32x4_add_(X,Y) _mm_add_ps(X,Y)
#define _simd_f32x4_add_instruction_set anvil::simd::IS_SSE

#define _simd_f32x8_add_(X,Y) _mm256_add_ps(X,Y)
#define _simd_f32x8_add_instruction_set anvil::simd::IS_AVX

#define _simd_s32x4_add_(X,Y) _mm_add_epi32(X,Y)
#define _simd_s32x4_add_instruction_set anvil::simd::IS_SSE_2

#define _simd_s32x8_add_(X,Y) _mm256_add_epi32(X,Y)
#define _simd_s32x8_add_instruction_set anvil::simd::IS_AVX_2

#define _simd_s16x8_add_(X,Y) _mm_add_epi16(X,Y)
#define _simd_s16x8_add_instruction_set anvil::simd::IS_SSE_2

#define _simd_s16x16_add_(X,Y) _mm256_add_epi16(X,Y)
#define _simd_s16x16_add_instruction_set anvil::simd::IS_AVX_2

#define _simd_s8x16_add_(X,Y) _mm_add_epi8(X,Y)
#define _simd_s8x16_add_instruction_set anvil::simd::IS_SSE_2

#define _simd_s8x32_add_(X,Y) _mm256_add_epi8(X,Y)
#define _simd_s8x32_add_instruction_set anvil::simd::IS_AVX_2

#define _simd_u16x8_add_(X,Y) _mm_adds_epu16(X,Y)
#define _simd_u16x8_add_instruction_set anvil::simd::IS_SSE_2

#define _simd_u16x16_add_(X,Y) _mm256_adds_epu16(X,Y)
#define _simd_u16x16_add_instruction_set anvil::simd::IS_AVX_2

#define _simd_u8x16_add_(X,Y) _mm_adds_epu8(X,Y)
#define _simd_u8x16_add_instruction_set anvil::simd::IS_SSE_2

#define _simd_u8x32_add_(X,Y) _mm256_adds_epu8(X,Y)
#define _simd_u8x32_add_instruction_set anvil::simd::IS_AVX_2

#define _simd_f64x2_sub_(X,Y) _mm_sub_pd(X,Y)
#define _simd_f64x2_sub_instruction_set anvil::simd::IS_SSE_2

#define _simd_f64x4_sub_(X,Y) _mm256_sub_pd(X,Y)
#define _simd_f64x4_sub_instruction_set anvil::simd::IS_AVX

#define _simd_f32x4_sub_(X,Y) _mm_sub_ps(X,Y)
#define _simd_f32x4_sub_instruction_set anvil::simd::IS_SSE

#define _simd_f32x8_sub_(X,Y) _mm256_sub_ps(X,Y)
#define _simd_f32x8_sub_instruction_set anvil::simd::IS_AVX

#define _simd_s32x4_sub_(X,Y) _mm_sub_epi32(X,Y)
#define _simd_s32x4_sub_instruction_set anvil::simd::IS_SSE_2

#define _simd_s32x8_sub_(X,Y) _mm256_sub_epi32(X,Y)
#define _simd_s32x8_sub_instruction_set anvil::simd::IS_AVX_2

#define _simd_s16x8_sub_(X,Y) _mm_sub_epi16(X,Y)
#define _simd_s16x8_sub_instruction_set anvil::simd::IS_SSE_2

#define _simd_s16x16_sub_(X,Y) _mm256_sub_epi16(X,Y)
#define _simd_s16x16_sub_instruction_set anvil::simd::IS_AVX_2

#define _simd_s8x16_sub_(X,Y) _mm_sub_epi8(X,Y)
#define _simd_s8x16_sub_instruction_set anvil::simd::IS_SSE_2

#define _simd_s8x32_sub_(X,Y) _mm256_sub_epi8(X,Y)
#define _simd_s8x32_sub_instruction_set anvil::simd::IS_AVX_2

#define _simd_u16x8_sub_(X,Y) _mm_subs_epu16(X,Y)
#define _simd_u16x8_sub_instruction_set anvil::simd::IS_SSE_2

#define _simd_u16x16_sub_(X,Y) _mm256_subs_epu16(X,Y)
#define _simd_u16x16_sub_instruction_set anvil::simd::IS_AVX_2

#define _simd_u8x16_sub_(X,Y) _mm_subs_epu8(X,Y)
#define _simd_u8x16_sub_instruction_set anvil::simd::IS_SSE_2

#define _simd_u8x32_sub_(X,Y) _mm256_subs_epu8(X,Y)
#define _simd_u8x32_sub_instruction_set anvil::simd::IS_AVX_2

#define _simd_f64x2_mul_(X,Y) _mm_mul_pd(X,Y)
#define _simd_f64x2_mul_instruction_set anvil::simd::IS_SSE_2

#define _simd_f64x4_mul_(X,Y) _mm256_mul_pd(X,Y)
#define _simd_f64x4_mul_instruction_set anvil::simd::IS_AVX

#define _simd_f32x4_mul_(X,Y) _mm_mul_ps(X,Y)
#define _simd_f32x4_mul_instruction_set anvil::simd::IS_SSE

#define _simd_f32x8_mul_(X,Y) _mm256_mul_ps(X,Y)
#define _simd_f32x8_mul_instruction_set anvil::simd::IS_AVX

#define _simd_s16x8_mul_(X,Y) _mm_mullo_epi16 (X,Y)
#define _simd_s16x8_mul_instruction_set anvil::simd::IS_SSE_2

#define _simd_s16x16_mul_(X,Y) _mm256_mullo_epi16(X,Y)
#define _simd_s16x16_mul_instruction_set anvil::simd::IS_AVX_2

#define _simd_f64x2_div_(X,Y) _mm_div_pd(X,Y)
#define _simd_f64x2_div_instruction_set anvil::simd::IS_SSE_2

#define _simd_f64x4_div_(X,Y) _mm256_div_pd(X,Y)
#define _simd_f64x4_div_instruction_set anvil::simd::IS_AVX

#define _simd_f32x4_div_(X,Y) _mm_div_ps(X,Y)
#define _simd_f32x4_div_instruction_set anvil::simd::IS_SSE

#define _simd_f32x8_div_(X,Y) _mm256_div_ps(X,Y)
#define _simd_f32x8_div_instruction_set anvil::simd::IS_AVX

#define _simd_f64x2_min_(X,Y) _mm_min_pd(X,Y)
#define _simd_f64x2_min_instruction_set anvil::simd::IS_SSE_2

#define _simd_f64x4_min_(X,Y) _mm256_min_pd(X,Y)
#define _simd_f64x4_min_instruction_set anvil::simd::IS_AVX

#define _simd_f32x4_min_(X,Y) _mm_min_ps(X,Y)
#define _simd_f32x4_min_instruction_set anvil::simd::IS_SSE

#define _simd_f32x8_min_(X,Y) _mm256_min_ps(X,Y)
#define _simd_f32x8_min_instruction_set anvil::simd::IS_AVX

#define _simd_s32x4_min_(X,Y) _mm_min_epi32(X,Y)
#define _simd_s32x4_min_instruction_set anvil::simd::IS_SSE_4_1

#define _simd_s32x8_min_(X,Y) _mm256_min_epi32(X,Y)
#define _simd_s32x8_min_instruction_set anvil::simd::IS_AVX_2

#define _simd_s16x8_min_(X,Y) _mm_min_epi16(X,Y)
#define _simd_s16x8_min_instruction_set anvil::simd::IS_SSE_2

#define _simd_s16x16_min_(X,Y) _mm256_min_epi16(X,Y)
#define _simd_s16x16_min_instruction_set anvil::simd::IS_AVX_2

#define _simd_s8x16_min_(X,Y) _mm_min_epi8(X,Y)
#define _simd_s8x16_min_instruction_set anvil::simd::IS_SSE_4_1

#define _simd_s8x32_min_(X,Y) _mm256_min_epi8(X,Y)
#define _simd_s8x32_min_instruction_set anvil::simd::IS_AVX_2

#define _simd_u32x4_min_(X,Y) _mm_min_epu32(X,Y)
#define _simd_u32x4_min_instruction_set anvil::simd::IS_SSE_4_1

#define _simd_u32x8_min_(X,Y) _mm256_min_epu32(X,Y)
#define _simd_u32x8_min_instruction_set anvil::simd::IS_SSE_4_1

#define _simd_u16x8_min_(X,Y) _mm_min_epu16(X,Y)
#define _simd_u16x8_min_instruction_set anvil::simd::IS_AVX_2

#define _simd_u16x16_min_(X,Y) _mm256_min_epu16(X,Y)
#define _simd_u16x16_min_instruction_set anvil::simd::IS_AVX_2

#define _simd_u8x16_min_(X,Y) _mm_min_epu8(X,Y)
#define _simd_u8x16_min_instruction_set anvil::simd::IS_SSE_2

#define _simd_u8x32_min_(X,Y) _mm256_min_epu8(X,Y)
#define _simd_u8x32_min_instruction_set anvil::simd::IS_AVX_2

#define _simd_f64x2_max_(X,Y) _mm_max_pd(X,Y)
#define _simd_f64x2_max_instruction_set anvil::simd::IS_SSE_2

#define _simd_f64x4_max_(X,Y) _mm256_max_pd(X,Y)
#define _simd_f64x4_max_instruction_set anvil::simd::IS_AVX

#define _simd_f32x4_max_(X,Y) _mm_max_ps(X,Y)
#define _simd_f32x4_max_instruction_set anvil::simd::IS_SSE

#define _simd_f32x8_max_(X,Y) _mm256_max_ps(X,Y)
#define _simd_f32x8_max_instruction_set anvil::simd::IS_AVX

#define _simd_s32x4_max_(X,Y) _mm_max_epi32(X,Y)
#define _simd_s32x4_max_instruction_set anvil::simd::IS_SSE_4_1

#define _simd_s32x8_max_(X,Y) _mm256_max_epi32(X,Y)
#define _simd_s32x8_max_instruction_set anvil::simd::IS_AVX_2

#define _simd_s16x8_max_(X,Y) _mm_max_epi16(X,Y)
#define _simd_s16x8_max_instruction_set anvil::simd::IS_SSE_2

#define _simd_s16x16_max_(X,Y) _mm256_max_epi16(X,Y)
#define _simd_s16x16_max_instruction_set anvil::simd::IS_AVX_2

#define _simd_s8x16_max_(X,Y) _mm_max_epi8(X,Y)
#define _simd_s8x16_max_instruction_set anvil::simd::IS_SSE_4_1

#define _simd_s8x32_max_(X,Y) _mm256_max_epi8(X,Y)
#define _simd_s8x32_max_instruction_set anvil::simd::IS_AVX_2

#define _simd_u32x4_max_(X,Y) _mm_max_epu32(X,Y)
#define _simd_u32x4_max_instruction_set anvil::simd::IS_SSE_4_1

#define _simd_u32x8_max_(X,Y) _mm256_max_epu32(X,Y)
#define _simd_u32x8_max_instruction_set anvil::simd::IS_SSE_4_1

#define _simd_u16x8_max_(X,Y) _mm_max_epu16(X,Y)
#define _simd_u16x8_max_instruction_set anvil::simd::IS_AVX_2

#define _simd_u16x16_max_(X,Y) _mm256_max_epu16(X,Y)
#define _simd_u16x16_max_instruction_set anvil::simd::IS_AVX_2

#define _simd_u8x16_max_(X,Y) _mm_max_epu8(X,Y)
#define _simd_u8x16_max_instruction_set anvil::simd::IS_SSE_2

#define _simd_u8x32_max_(X,Y) _mm256_max_epu8(X,Y)
#define _simd_u8x32_max_instruction_set anvil::simd::IS_AVX_2

#define _simd_f64x2_fill_undefined_() _mm_undefined_pd()
#define _simd_f64x2_fill_undefined_instruction_set anvil::simd::IS_SSE_2

#define _simd_f64x4_fill_undefined_() _mm256_undefined_pd()
#define _simd_f64x4_fill_undefined_instruction_set anvil::simd::IS_AVX

#define _simd_f32x4_fill_undefined_() _mm_undefined_ps()
#define _simd_f32x4_fill_undefined_instruction_set anvil::simd::IS_SSE

#define _simd_f32x8_fill_undefined_() _mm256_undefined_ps()
#define _simd_f32x8_fill_undefined_instruction_set anvil::simd::IS_AVX

#define _simd_s32x4_fill_undefined_() _mm_undefined_si128()
#define _simd_s32x4_fill_undefined_instruction_set anvil::simd::IS_SSE_2

#define _simd_s32x8_fill_undefined_() _mm256_undefined_si256()
#define _simd_s32x8_fill_undefined_instruction_set anvil::simd::IS_AVX

#define _simd_s16x8_fill_undefined_() _mm_undefined_si128()
#define _simd_s16x8_fill_undefined_instruction_set anvil::simd::IS_SSE_2

#define _simd_s16x16_fill_undefined_() _mm256_undefined_si256()
#define _simd_s16x16_fill_undefined_instruction_set anvil::simd::IS_AVX

#define _simd_s8x16_fill_undefined_() _mm_undefined_si128()
#define _simd_s8x16_fill_undefined_instruction_set anvil::simd::IS_SSE_2

#define _simd_s8x32_fill_undefined_() _mm256_undefined_si256()
#define _simd_s8x32_fill_undefined_instruction_set anvil::simd::IS_AVX

#define _simd_u16x8_fill_undefined_() _mm_undefined_si128()
#define _simd_u16x8_fill_undefined_instruction_set anvil::simd::IS_SSE_2

#define _simd_u16x16_fill_undefined_() _mm256_undefined_si256()
#define _simd_u16x16_fill_undefined_instruction_set anvil::simd::IS_AVX

#define _simd_u8x16_fill_undefined_() _mm_undefined_si128()
#define _simd_u8x16_fill_undefined_instruction_set anvil::simd::IS_SSE_2

#define _simd_u8x32_fill_undefined_() _mm256_undefined_si256()
#define _simd_u8x32_fill_undefined_instruction_set anvil::simd::IS_AVX

#define _simd_f64x2_fill_zero_() _mm_setzero_pd()
#define _simd_f64x2_fill_zero_instruction_set anvil::simd::IS_SSE_2

#define _simd_f64x4_fill_zero_() _mm256_setzero_pd()
#define _simd_f64x4_fill_zero_instruction_set anvil::simd::IS_AVX

#define _simd_f32x4_fill_zero_() _mm_setzero_ps()
#define _simd_f32x4_fill_zero_instruction_set anvil::simd::IS_SSE

#define _simd_f32x8_fill_zero_() _mm256_setzero_ps()
#define _simd_f32x8_fill_zero_instruction_set anvil::simd::IS_AVX

#define _simd_s32x4_fill_zero_() _mm_setzero_si128()
#define _simd_s32x4_fill_zero_instruction_set anvil::simd::IS_SSE_2

#define _simd_s32x8_fill_zero_() _mm256_setzero_si256()
#define _simd_s32x8_fill_zero_instruction_set anvil::simd::IS_AVX

#define _simd_s16x8_fill_zero_() _mm_setzero_si128()
#define _simd_s16x8_fill_zero_instruction_set anvil::simd::IS_SSE_2

#define _simd_s16x16_fill_zero_() _mm256_setzero_si256()
#define _simd_s16x16_fill_zero_instruction_set anvil::simd::IS_AVX

#define _simd_s8x16_fill_zero_() _mm_setzero_si128()
#define _simd_s8x16_fill_zero_instruction_set anvil::simd::IS_SSE_2

#define _simd_s8x32_fill_zero_() _mm256_setzero_si256()
#define _simd_s8x32_fill_zero_instruction_set anvil::simd::IS_AVX

#define _simd_u16x8_fill_zero_() _mm_setzero_si128()
#define _simd_u16x8_fill_zero_instruction_set anvil::simd::IS_SSE_2

#define _simd_u16x16_fill_zero_() _mm256_setzero_si256()
#define _simd_u16x16_fill_zero_instruction_set anvil::simd::IS_AVX

#define _simd_u8x16_fill_zero_() _mm_setzero_si128()
#define _simd_u8x16_fill_zero_instruction_set anvil::simd::IS_SSE_2

#define _simd_u8x32_fill_zero_() _mm256_setzero_si256()
#define _simd_u8x32_fill_zero_instruction_set anvil::simd::IS_AVX

#define _simd_f64x2_fill_scalar_(X) _mm_set1_pd(X)
#define _simd_f64x2_fill_scalar_instruction_set anvil::simd::IS_SSE_2

#define _simd_f64x4_fill_scalar_(X) _mm256_set1_pd(X)
#define _simd_f64x4_fill_scalar_instruction_set anvil::simd::IS_AVX

#define _simd_f32x4_fill_scalar_(X) _mm_set1_ps(X)
#define _simd_f32x4_fill_scalar_instruction_set anvil::simd::IS_SSE

#define _simd_f32x8_fill_scalar_(X) _mm256_set1_ps(X)
#define _simd_f32x8_fill_scalar_instruction_set anvil::simd::IS_AVX

#define _simd_s64x2_fill_scalar_(X) _mm_set1_epi64x(X)
#define _simd_s64x2_fill_scalar_instruction_set anvil::simd::IS_SSE_2

#define _simd_s64x4_fill_scalar_(X) _mm256_set1_epi64x(X)
#define _simd_s64x4_fill_scalar_instruction_set anvil::simd::IS_AVX_2

#define _simd_s32x4_fill_scalar_(X) _mm_set1_epi32(X)
#define _simd_s32x4_fill_scalar_instruction_set anvil::simd::IS_SSE_2

#define _simd_s32x8_fill_scalar_(X) _mm256_set1_epi32(X)
#define _simd_s32x8_fill_scalar_instruction_set anvil::simd::IS_AVX_2

#define _simd_s16x8_fill_scalar_(X) _mm_set1_epi16(X)
#define _simd_s16x8_fill_scalar_instruction_set anvil::simd::IS_SSE_2

#define _simd_s16x16_fill_scalar_(X) _mm256_set1_epi16(X)
#define _simd_s16x16_fill_scalar_instruction_set anvil::simd::IS_AVX_2

#define _simd_s8x16_fill_scalar_(X) _mm_set1_epi8(X)
#define _simd_s8x16_fill_scalar_instruction_set anvil::simd::IS_SSE_2

#define _simd_s8x32_fill_scalar_(X) _mm256_set1_epi8(X)
#define _simd_s8x32_fill_scalar_instruction_set anvil::simd::IS_AVX_2

#define _simd_u64x2_fill_scalar_(X) _simd_s64x2_fill_scalar_(X)
#define _simd_u64x2_fill_scalar_instruction_set _simd_s64x2_fill_scalar_instruction_set

#define _simd_u64x4_fill_scalar_(X) _simd_s64x4_fill_scalar_(X)
#define _simd_u64x4_fill_scalar_instruction_set _simd_s64x4_fill_scalar_instruction_set

#define _simd_u32x4_fill_scalar_(X) _simd_s32x4_fill_scalar_(X)
#define _simd_u32x4_fill_scalar_instruction_set _simd_s32x4_fill_scalar_instruction_set

#define _simd_u32x8_fill_scalar_(X) _simd_s32x8_fill_scalar_(X)
#define _simd_u32x8_fill_scalar_instruction_set _simd_s32x8_fill_scalar_instruction_set

#define _simd_u16x8_fill_scalar_(X) _simd_s16x8_fill_scalar_(X)
#define _simd_u16x8_fill_scalar_instruction_set _simd_s16x8_fill_scalar_instruction_set

#define _simd_u16x16_fill_scalar_(X) _simd_s16x16_fill_scalar_(X)
#define _simd_u16x16_fill_scalar_instruction_set _simd_s16x16_fill_scalar_instruction_set

#define _simd_u8x16_fill_scalar_(X) _simd_s8x16_fill_scalar_(X)
#define _simd_u8x16_fill_scalar_instruction_set _simd_s8x16_fill_scalar_instruction_set

#define _simd_u8x32_fill_scalar_(X) _simd_s8x32_fill_scalar_(X)
#define _simd_u8x32_fill_scalar_instruction_set _simd_s8x32_fill_scalar_instruction_set

#define _simd_f64x2_set_(X,Y) _mm_set_pd(X,Y)
#define _simd_f64x2_set_instruction_set anvil::simd::IS_SSE_2

#define _simd_f64x4_set_(X,Y,Z,W) _mm256_set_pd(X,Y,Z,W)
#define _simd_f64x4_set_instruction_set anvil::simd::IS_AVX

#define _simd_f32x4_set_(X,Y,Z,W) _mm_set_ps(X,Y,Z,W)
#define _simd_f32x4_set_instruction_set anvil::simd::IS_SSE

#define _simd_f32x8_set_(X,Y,Z,W,A,B,C,D) _mm256_set_ps(X,Y,Z,W,A,B,C,D)
#define _simd_f32x8_set_instruction_set anvil::simd::IS_AVX

#define _simd_s64x2_set_(X,Y) _mm_set_epi64x(X,Y)
#define _simd_s64x2_set_instruction_set anvil::simd::IS_SSE_2

#define _simd_s64x4_set_(X,Y,Z,W) _mm256_set_epi64x(X,Y,Z,W)
#define _simd_s64x4_set_instruction_set anvil::simd::IS_AVX_2

#define _simd_s32x4_set_(X,Y,Z,W) _mm_set_epi32(X,Y,Z,W)
#define _simd_s32x4_set_instruction_set anvil::simd::IS_SSE_2

#define _simd_s32x8_set_(X,Y,Z,W,A,B,C,D) _mm256_set_epi32(X,Y,Z,W,A,B,C,D)
#define _simd_s32x8_set_instruction_set anvil::simd::IS_AVX_2

#define _simd_s16x8_set_(X,Y,Z,W,A,B,C,D) _mm_set1_epi16(X,Y,Z,W,A,B,C,D)
#define _simd_s16x8_set_instruction_set anvil::simd::IS_SSE_2

#define _simd_s16x16_set_(X,Y,Z,W,A,B,C,D,E,F,G,H,I,J,K,L) _mm256_set1_epi16(X,Y,Z,W,A,B,C,D,E,F,G,H,I,J,K,L)
#define _simd_s16x16_set_instruction_set anvil::simd::IS_AVX_2

#define _simd_s8x16_set_(X,Y,Z,W,A,B,C,D,E,F,G,H,I,J,K,L) _mm_set1_epi8(X,Y,Z,W,A,B,C,D,E,F,G,H,I,J,K,L)
#define _simd_s8x16_set_instruction_set anvil::simd::IS_SSE_2

#define _simd_s8x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _mm256_set1_epi8(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
#define _simd_s8x32_set_instruction_set anvil::simd::IS_AVX_2

#define _simd_u64x2_set_(X,Y) _simd_s64x2_set_(X,Y)
#define _simd_u64x2_set_instruction_set _simd_s64x2_set_instruction_set

#define _simd_u64x4_set_(X,Y,Z,W) _simd_s64x4_set_(X,Y,Z,W)
#define _simd_u64x4_set_instruction_set _simd_s64x4_set_instruction_set

#define _simd_u32x4_set_(X,Y,Z,W) _simd_s32x4_set_(X,Y,Z,W)
#define _simd_u32x4_set_instruction_set _simd_s32x4_set_instruction_set

#define _simd_u32x8_set_(X,Y,Z,W,A,B,C,D) _simd_s32x8_set_(X,Y,Z,W,A,B,C,D)
#define _simd_u32x8_set_instruction_set _simd_s32x8_set_instruction_set

#define _simd_u16x8_set_(X,Y,Z,W,A,B,C,D) _simd_s16x8_set_(X,Y,Z,W,A,B,C,D)
#define _simd_u16x8_set_instruction_set _simd_s16x8_set_instruction_set

#define _simd_u16x16_set_(X,Y,Z,W,A,B,C,D,E,F,G,H,I,J,K,L) _simd_s16x16_set_(X,Y,Z,W,A,B,C,D,E,F,G,H,I,J,K,L)
#define _simd_u16x16_set_instruction_set _simd_s16x16_set_instruction_set

#define _simd_u8x16_set_(X,Y,Z,W,A,B,C,D,E,F,G,H,I,J,K,L) _simd_s8x16_set_(X,Y,Z,W,A,B,C,D,E,F,G,H,I,J,K,L)
#define _simd_u8x16_set_instruction_set _simd_s8x16_set_instruction_set

#define _simd_u8x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_s8x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
#define _simd_u8x32_set_instruction_set _simd_s8x32_set_instruction_set

#define _simd_f64x2_cmpeq_(X,Y) _mm_cmpeq_pd(X,Y)
#define _simd_f64x2_cmpeq_instruction_set anvil::simd::IS_SSE_2

//#define _simd_f64x4_cmpeq_(X,Y) _mm256_cmpeq_pd(X,Y)
//#define _simd_f64x4_cmpeq_instruction_set anvil::simd::IS_AVX

#define _simd_f32x4_cmpeq_(X,Y) _mm_cmpeq_ps(X,Y)
#define _simd_f32x4_cmpeq_instruction_set anvil::simd::IS_SSE

//#define _simd_f32x8_cmpeq_(X,Y) _mm256_cmpeq_ps(X,Y)
//#define _simd_f32x8_cmpeq_instruction_set anvil::simd::IS_AVX

#define _simd_s32x4_cmpeq_(X,Y) _mm_cmpeq_epi32(X,Y)
#define _simd_s32x4_cmpeq_instruction_set anvil::simd::IS_SSE_2

//#define _simd_s32x8_cmpeq_(X,Y) _mm256_cmpeq_epi32(X,Y)
//#define _simd_s32x8_cmpeq_instruction_set anvil::simd::IS_AVX_2

#define _simd_s16x8_cmpeq_(X,Y) _mm_cmpeq_epi16(X,Y)
#define _simd_s16x8_cmpeq_instruction_set anvil::simd::IS_SSE_2

//#define _simd_s16x16_cmpeq_(X,Y) _mm256_cmpeq_epi16(X,Y)
//#define _simd_s16x16_cmpeq_instruction_set anvil::simd::IS_AVX_2

#define _simd_s8x16_cmpeq_(X,Y) _mm_cmpeq_epi8(X,Y)
#define _simd_s8x16_cmpeq_instruction_set anvil::simd::IS_SSE_2

//#define _simd_s8x32_cmpeq_(X,Y) _mm256_cmpeq_epi8(X,Y)
//#define _simd_s8x32_cmpeq_instruction_set anvil::simd::IS_AVX_2

#define _simd_u32x4_cmpeq_(X,Y) _simd_s32x4_cmpeq_(X,Y)
#define _simd_u32x4_cmpeq_instruction_set _simd_s32x4_cmpeq_instruction_set

//#define _simd_u32x8_cmpeq_(X,Y) _simd_s32x8_cmpeq_(X,Y)
//#define _simd_u32x8_cmpeq_instruction_set _simd_s32x8_cmpeq_instruction_set

#define _simd_u16x8_cmpeq_(X,Y) _simd_s16x8_cmpeq_(X,Y)
#define _simd_u16x8_cmpeq_instruction_set _simd_s16x8_cmpeq_instruction_set

//#define _simd_u16x16_cmpeq_(X,Y) _simd_s16x16_cmpeq_(X,Y)
//#define _simd_u16x16_cmpeq_instruction_set _simd_s16x16_cmpeq_instruction_set

#define _simd_u8x16_cmpeq_(X,Y) _simd_s8x16_cmpeq_(X,Y)
#define _simd_u8x16_cmpeq_instruction_set _simd_s8x16_cmpeq_instruction_set

//#define _simd_u8x32_cmpeq_(X,Y) _simd_s8x32_cmpeq_(X,Y)
//#define _simd_u8x32_cmpeq_instruction_set _simd_s8x32_cmpeq_instruction_set

#define _simd_f64x2_cmpne_(X,Y) _mm_cmpneq_pd(X,Y)
#define _simd_f64x2_cmpne_instruction_set anvil::simd::IS_SSE_2

//#define _simd_f64x4_cmpne_(X,Y) _mm256_cmpneq_pd(X,Y)
//#define _simd_f64x4_cmpne_instruction_set anvil::simd::IS_AVX

#define _simd_f32x4_cmpne_(X,Y) _mm_cmpneq_ps(X,Y)
#define _simd_f32x4_cmpne_instruction_set anvil::simd::IS_SSE

//#define _simd_f32x8_cmpne_(X,Y) _mm256_cmpneq_ps(X,Y)
//#define _simd_f32x8_cmpne_instruction_set anvil::simd::IS_AVX

#define _simd_f64x2_cmple_(X,Y) _mm_cmple_pd(X,Y)
#define _simd_f64x2_cmple_instruction_set anvil::simd::IS_SSE_2

//#define _simd_f64x4_cmple_(X,Y) _mm256_cmple_pd(X,Y)
//#define _simd_f64x4_cmple_instruction_set anvil::simd::IS_AVX

#define _simd_f32x4_cmple_(X,Y) _mm_cmple_ps(X,Y)
#define _simd_f32x4_cmple_instruction_set anvil::simd::IS_SSE

//#define _simd_f32x8_cmple_(X,Y) _mm256_cmple_ps(X,Y)
//#define _simd_f32x8_cmple_instruction_set anvil::simd::IS_AVX

#define _simd_f64x2_cmpge_(X,Y) _mm_cmpge_pd(X,Y)
#define _simd_f64x2_cmpge_instruction_set anvil::simd::IS_SSE_2

//#define _simd_f64x4_cmpge_(X,Y) _mm256_cmpge_pd(X,Y)
//#define _simd_f64x4_cmpge_instruction_set anvil::simd::IS_AVX

#define _simd_f32x4_cmpge_(X,Y) _mm_cmpge_ps(X,Y)
#define _simd_f32x4_cmpge_instruction_set anvil::simd::IS_SSE

//#define _simd_f32x8_cmpge_(X,Y) _mm256_cmpge_ps(X,Y)
//#define _simd_f32x8_cmpge_instruction_set anvil::simd::IS_AVX

#define _simd_f64x2_cmplt_(X,Y) _mm_cmplt_pd(X,Y)
#define _simd_f64x2_cmplt_instruction_set anvil::simd::IS_SSE_2

//#define _simd_f64x4_cmplt_(X,Y) _mm256_cmplt_pd(X,Y)
//#define _simd_f64x4_cmplt_instruction_set anvil::simd::IS_AVX

#define _simd_f32x4_cmplt_(X,Y) _mm_cmplt_ps(X,Y)
#define _simd_f32x4_cmplt_instruction_set anvil::simd::IS_SSE

//#define _simd_f32x8_cmplt_(X,Y) _mm256_cmplt_ps(X,Y)
//#define _simd_f32x8_cmplt_instruction_set anvil::simd::IS_AVX

#define _simd_s32x4_cmplt_(X,Y) _mm_cmplt_epi32(X,Y)
#define _simd_s32x4_cmplt_instruction_set anvil::simd::IS_SSE_2

//#define _simd_s32x8_cmplt_(X,Y) _mm256_cmplt_epi32(X,Y)
//#define _simd_s32x8_cmplt_instruction_set anvil::simd::IS_AVX_2

#define _simd_s16x8_cmplt_(X,Y) _mm_cmplt_epi16(X,Y)
#define _simd_s16x8_cmplt_instruction_set anvil::simd::IS_SSE_2

#define _simd_s8x16_cmplt_(X,Y) _mm_cmplt_epi8(X,Y)
#define _simd_s8x16_cmplt_instruction_set anvil::simd::IS_SSE_2

#define _simd_f64x2_cmpgt_(X,Y) _mm_cmpgt_pd(X,Y)
#define _simd_f64x2_cmpgt_instruction_set anvil::simd::IS_SSE_2

//#define _simd_f64x4_cmpgt_(X,Y) _mm256_cmpgt_pd(X,Y)
//#define _simd_f64x4_cmpgt_instruction_set anvil::simd::IS_AVX

#define _simd_f32x4_cmpgt_(X,Y) _mm_cmpgt_ps(X,Y)
#define _simd_f32x4_cmpgt_instruction_set anvil::simd::IS_SSE

//#define _simd_f32x8_cmpgt_(X,Y) _mm256_cmpgt_ps(X,Y)
//#define _simd_f32x8_cmpgt_instruction_set anvil::simd::IS_AVX

#define _simd_s32x4_cmpgt_(X,Y) _mm_cmpgt_epi32(X,Y)
#define _simd_s32x4_cmpgt_instruction_set anvil::simd::IS_SSE_2

//#define _simd_s32x8_cmpgt_(X,Y) _mm256_cmpgt_epi32(X,Y)
//#define _simd_s32x8_cmpgt_instruction_set anvil::simd::IS_AVX_2

#define _simd_s32x8_cmpgt_(X,Y) _mm256_cmpgt_epi32(X,Y)
#define _simd_s32x8_cmpgt_instruction_set anvil::simd::IS_AVX_2

#define _simd_s16x8_cmpgt_(X,Y) _mm_cmpgt_epi16(X,Y)
#define _simd_s16x8_cmpgt_instruction_set anvil::simd::IS_SSE_2

//#define _simd_s16x16_cmpgt_(X,Y) _mm256_cmpgt_epi16(X,Y)
//#define _simd_s16x16_cmpgt_instruction_set anvil::simd::IS_AVX_2

#define _simd_s8x16_cmpgt_(X,Y) _mm_cmpgt_epi8(X,Y)
#define _simd_s8x16_cmpgt_instruction_set anvil::simd::IS_SSE_2

//#define _simd_s8x32_cmpgt_(X,Y) _mm256_cmpgt_epi8(X,Y)
//#define _simd_s8x32_cmpgt_instruction_set anvil::simd::IS_AVX_2

#define _simd_f64x2_and_(X,Y) _mm_and_pd(X,Y)
#define _simd_f64x2_and_instruction_set anvil::simd::IS_SSE_2

#define _simd_f64x4_and_(X,Y) _mm256_and_pd(X,Y)
#define _simd_f64x4_and_instruction_set anvil::simd::IS_AVX

#define _simd_f32x4_and_(X,Y) _mm_and_ps(X,Y)
#define _simd_f32x4_and_instruction_set anvil::simd::IS_SSE

#define _simd_f32x8_and_(X,Y) _mm256_and_ps(X,Y)
#define _simd_f32x8_and_instruction_set anvil::simd::IS_AVX

#define _simd_s32x4_and_(X,Y) _mm_and_si128(X,Y)
#define _simd_s32x4_and_instruction_set anvil::simd::IS_SSE_2

#define _simd_s32x8_and_(X,Y) _mm256_and_si256(X,Y)
#define _simd_s32x8_and_instruction_set anvil::simd::IS_AVX

#define _simd_s16x8_and_(X,Y) _mm_and_si128(X,Y)
#define _simd_s16x8_and_instruction_set anvil::simd::IS_SSE_2

#define _simd_s16x16_and_(X,Y) _mm256_and_si256(X,Y)
#define _simd_s16x16_and_instruction_set anvil::simd::IS_AVX

#define _simd_s8x16_and_(X,Y) _mm_and_si128(X,Y)
#define _simd_s8x16_and_instruction_set anvil::simd::IS_SSE_2

#define _simd_s8x32_and_(X,Y) _mm256_and_si256(X,Y)
#define _simd_s8x32_and_instruction_set anvil::simd::IS_AVX

#define _simd_u16x8_and_(X,Y) _mm_and_si128(X,Y)
#define _simd_u16x8_and_instruction_set anvil::simd::IS_SSE_2

#define _simd_u16x16_and_(X,Y) _mm256_and_si256(X,Y)
#define _simd_u16x16_and_instruction_set anvil::simd::IS_AVX

#define _simd_u8x16_and_(X,Y) _mm_and_si128(X,Y)
#define _simd_u8x16_and_instruction_set anvil::simd::IS_SSE_2

#define _simd_u8x32_and_(X,Y) _mm256_and_si256(X,Y)
#define _simd_u8x32_and_instruction_set anvil::simd::IS_AVX

#define _simd_f64x2_or_(X,Y) _mm_or_pd(X,Y)
#define _simd_f64x2_or_instruction_set anvil::simd::IS_SSE_2

#define _simd_f64x4_or_(X,Y) _mm256_or_pd(X,Y)
#define _simd_f64x4_or_instruction_set anvil::simd::IS_AVX

#define _simd_f32x4_or_(X,Y) _mm_or_ps(X,Y)
#define _simd_f32x4_or_instruction_set anvil::simd::IS_SSE

#define _simd_f32x8_or_(X,Y) _mm256_or_ps(X,Y)
#define _simd_f32x8_or_instruction_set anvil::simd::IS_AVX

#define _simd_s32x4_or_(X,Y) _mm_or_si128(X,Y)
#define _simd_s32x4_or_instruction_set anvil::simd::IS_SSE_2

#define _simd_s32x8_or_(X,Y) _mm256_or_si256(X,Y)
#define _simd_s32x8_or_instruction_set anvil::simd::IS_AVX

#define _simd_s16x8_or_(X,Y) _mm_or_si128(X,Y)
#define _simd_s16x8_or_instruction_set anvil::simd::IS_SSE_2

#define _simd_s16x16_or_(X,Y) _mm256_or_si256(X,Y)
#define _simd_s16x16_or_instruction_set anvil::simd::IS_AVX

#define _simd_s8x16_or_(X,Y) _mm_or_si128(X,Y)
#define _simd_s8x16_or_instruction_set anvil::simd::IS_SSE_2

#define _simd_s8x32_or_(X,Y) _mm256_or_si256(X,Y)
#define _simd_s8x32_or_instruction_set anvil::simd::IS_AVX

#define _simd_u16x8_or_(X,Y) _mm_or_si128(X,Y)
#define _simd_u16x8_or_instruction_set anvil::simd::IS_SSE_2

#define _simd_u16x16_or_(X,Y) _mm256_or_si256(X,Y)
#define _simd_u16x16_or_instruction_set anvil::simd::IS_AVX

#define _simd_u8x16_or_(X,Y) _mm_or_si128(X,Y)
#define _simd_u8x16_or_instruction_set anvil::simd::IS_SSE_2

#define _simd_u8x32_or_(X,Y) _mm256_or_si256(X,Y)
#define _simd_u8x32_or_instruction_set anvil::simd::IS_AVX

#define _simd_f64x2_xor_(X,Y) _mm_xor_pd(X,Y)
#define _simd_f64x2_xor_instruction_set anvil::simd::IS_SSE_2

#define _simd_f64x4_xor_(X,Y) _mm256_xor_pd(X,Y)
#define _simd_f64x4_xor_instruction_set anvil::simd::IS_AVX

#define _simd_f32x4_xor_(X,Y) _mm_xor_ps(X,Y)
#define _simd_f32x4_xor_instruction_set anvil::simd::IS_SSE

#define _simd_f32x8_xor_(X,Y) _mm256_xor_ps(X,Y)
#define _simd_f32x8_xor_instruction_set anvil::simd::IS_AVX

#define _simd_s32x4_xor_(X,Y) _mm_xor_si128(X,Y)
#define _simd_s32x4_xor_instruction_set anvil::simd::IS_SSE_2

#define _simd_s32x8_xor_(X,Y) _mm256_xor_si256(X,Y)
#define _simd_s32x8_xor_instruction_set anvil::simd::IS_AVX

#define _simd_s16x8_xor_(X,Y) _mm_xor_si128(X,Y)
#define _simd_s16x8_xor_instruction_set anvil::simd::IS_SSE_2

#define _simd_s16x16_xor_(X,Y) _mm256_xor_si256(X,Y)
#define _simd_s16x16_xor_instruction_set anvil::simd::IS_AVX

#define _simd_s8x16_xor_(X,Y) _mm_xor_si128(X,Y)
#define _simd_s8x16_xor_instruction_set anvil::simd::IS_SSE_2

#define _simd_s8x32_xor_(X,Y) _mm256_xor_si256(X,Y)
#define _simd_s8x32_xor_instruction_set anvil::simd::IS_AVX

#define _simd_u16x8_xor_(X,Y) _mm_xor_si128(X,Y)
#define _simd_u16x8_xor_instruction_set anvil::simd::IS_SSE_2

#define _simd_u16x16_xor_(X,Y) _mm256_xor_si256(X,Y)
#define _simd_u16x16_xor_instruction_set anvil::simd::IS_AVX

#define _simd_u8x16_xor_(X,Y) _mm_xor_si128(X,Y)
#define _simd_u8x16_xor_instruction_set anvil::simd::IS_SSE_2

#define _simd_u8x32_xor_(X,Y) _mm256_xor_si256(X,Y)
#define _simd_u8x32_xor_instruction_set anvil::simd::IS_AVX

#define _simd_s32x4_abs_(X) _mm_abs_epi32(X)
#define _simd_s32x4_abs_instruction_set anvil::simd::IS_SSSE_3

#define _simd_s32x8_abs_(X) _mm256_abs_epi32(X)
#define _simd_s32x8_abs_instruction_set anvil::simd::IS_AVX

#define _simd_s16x8_abs_(X) _mm_abs_epi16(X)
#define _simd_s16x8_abs_instruction_set anvil::simd::IS_SSSE_3

#define _simd_s16x16_abs_(X) _mm256_abs_epi16(X)
#define _simd_s16x16_abs_instruction_set anvil::simd::IS_AVX

#define _simd_s8x16_abs_(X) _mm_abs_epi8(X)
#define _simd_s8x16_abs_instruction_set anvil::simd::IS_SSSE_3

#define _simd_s8x32_abs_(X) _mm256_abs_epi32(X)
#define _simd_s8x32_abs_instruction_set anvil::simd::IS_AVX

#define _simd_f64x2_ceil_(X) _mm_ceil_pd(X)
#define _simd_f64x2_ceil_instruction_set anvil::simd::IS_SSE_4_1

#define _simd_f64x4_ceil_(X) _mm256_ceil_pd(X)
#define _simd_f64x4_ceil_instruction_set anvil::simd::IS_AVX

#define _simd_f32x4_ceil_(X) _mm_ceil_ps(X)
#define _simd_f32x4_ceil_instruction_set anvil::simd::IS_SSE_4_1

#define _simd_f32x8_ceil_(X) _mm256_ceil_ps(X)
#define _simd_f32x8_ceil_instruction_set anvil::simd::IS_AVX

#define _simd_f64x2_floor_(X) _mm_floor_pd(X)
#define _simd_f64x2_floor_instruction_set anvil::simd::IS_SSE_4_1

#define _simd_f64x4_floor_(X) _mm256_floor_pd(X)
#define _simd_f64x4_floor_instruction_set anvil::simd::IS_AVX

#define _simd_f32x4_floor_(X) _mm_floor_ps(X)
#define _simd_f32x4_floor_instruction_set anvil::simd::IS_SSE_4_1

#define _simd_f32x8_floor_(X) _mm256_floor_ps(X)
#define _simd_f32x8_floor_instruction_set anvil::simd::IS_AVX

#define _simd_f64x2_round_(X) _mm_round_pd(X, _MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC)
#define _simd_f64x2_round_instruction_set anvil::simd::IS_SSE_4_1

#define _simd_f64x4_round_(X) _mm256_round_pd(X, _MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC)
#define _simd_f64x4_round_instruction_set anvil::simd::IS_AVX

#define _simd_f32x4_round_(X) _mm_round_ps(X, _MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC)
#define _simd_f32x4_round_instruction_set anvil::simd::IS_SSE_4_1

#define _simd_f32x8_round_(X) _mm256_round_ps(X, _MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC)
#define _simd_f32x8_round_instruction_set anvil::simd::IS_AVX

#define _simd_f64x2_sqrt_(X) _mm_sqrt_pd(X)
#define _simd_f64x2_sqrt_instruction_set anvil::simd::IS_SSE_2 

#define _simd_f64x4_sqrt_(X) _mm256_sqrt_pd(X)
#define _simd_f64x4_sqrt_instruction_set anvil::simd::IS_AVX 

#define _simd_f32x4_sqrt_(X) _mm_sqrt_ps(X)
#define _simd_f32x4_sqrt_instruction_set anvil::simd::IS_SSE 

#define _simd_f32x8_sqrt_(X) _mm256_sqrt_ps(X)
#define _simd_f32x8_sqrt_instruction_set anvil::simd::IS_AVX 

#define _simd_f64x2_fma_(X,Y,Z) _mm_fmadd_pd(X,Y,Z)
#define _simd_f64x2_fma_instruction_set anvil::simd::IS_FMA

#define _simd_f64x4_fma_(X,Y,Z) _mm256_fmadd_pd(X,Y,Z)
#define _simd_f64x4_fma_instruction_set anvil::simd::IS_FMA

#define _simd_f32x4_fma_(X,Y,Z) _mm_fmadd_ps(X,Y,Z)
#define _simd_f32x4_fma_instruction_set anvil::simd::IS_FMA

#define _simd_f32x8_fma_(X,Y,Z) _mm256_fmadd_ps(X,Y,Z)
#define _simd_f32x8_fma_instruction_set anvil::simd::IS_FMA

#define _simd_f64x2_fms_(X,Y,Z) _mm_fmsub_pd(X,Y,Z)
#define _simd_f64x2_fms_instruction_set anvil::simd::IS_FMA

#define _simd_f64x4_fms_(X,Y,Z) _mm256_fmsub_pd(X,Y,Z)
#define _simd_f64x4_fms_instruction_set anvil::simd::IS_FMA

#define _simd_f32x4_fms_(X,Y,Z) _mm_fmsub_ps(X,Y,Z)
#define _simd_f32x4_fms_instruction_set anvil::simd::IS_FMA

#define _simd_f32x8_fms_(X,Y,Z) _mm256_fmsub_ps(X,Y,Z)
#define _simd_f32x8_fms_instruction_set anvil::simd::IS_FMA

#define _simd_s32x4_cast_f64_(X) _mm256_cvtepi32_pd(X)
#define _simd_s32x4_cast_f64_instruction_set anvil::simd::IS_AVX

#define _simd_f64x4_cast_s32_(X) _mm256_cvttpd_epi32(X)
#define _simd_f64x4_cast_s32_instruction_set anvil::simd::IS_AVX

#define _simd_s32x4_cast_f32_(X) _mm_cvtepi32_ps(X)
#define _simd_s32x4_cast_f32_instruction_set anvil::simd::IS_SSE_2

#define _simd_f32x4_cast_s32_(X) _mm_cvtps_epi32(X)
#define _simd_f32x4_cast_s32_instruction_set anvil::simd::IS_SSE_2

#define _simd_f64x4_cast_f32_(X) _mm256_cvtpd_ps(X)
#define _simd_f64x4_cast_f32_instruction_set anvil::simd::IS_AVX

#define _simd_f32x4_cast_f64_(X) _mm256_cvtps_pd(X)
#define _simd_f32x4_cast_f64_instruction_set anvil::simd::IS_SSE_2 

#define _simd_s32x8_cast_f32_(X) _mm256_cvtepi32_ps(X)
#define _simd_s32x8_cast_f32_instruction_set anvil::simd::IS_AVX

#define _simd_f32x8_cast_s32_(X) _mm256_cvtps_epi32(X)
#define _simd_f32x8_cast_s32_instruction_set anvil::simd::IS_AVX

#endif

// Types
typedef double	 _simd_f64x1;
typedef float	 _simd_f32x1;
typedef int64_t	 _simd_s64x1;
typedef uint64_t _simd_u64x1;
typedef int32_t	 _simd_s32x1;
typedef uint32_t _simd_u32x1;
typedef int16_t	 _simd_s16x1;
typedef uint16_t _simd_u16x1;
typedef int8_t	 _simd_s8x1;
typedef uint8_t	 _simd_u8x1;

#ifndef _simd_f64x2
	struct _simd_f64x2 {
		_simd_f64x1 lo;
		_simd_f64x1 hi;
	};
	#define _simd_f64x2_splitlo_(X) X.lo
	#define _simd_f64x2_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_f64x2_splithi_(X) X.hi
	#define _simd_f64x2_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_f64x2_combine_(X,Y) _simd_f64x2({X,Y})
	#define _simd_f64x2_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_f64x4
	struct _simd_f64x4 {
		_simd_f64x2 lo;
		_simd_f64x2 hi;
	};
	#define _simd_f64x4_splitlo_(X) X.lo
	#define _simd_f64x4_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_f64x4_splithi_(X) X.hi
	#define _simd_f64x4_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_f64x4_combine_(X,Y) _simd_f64x4({X,Y})
	#define _simd_f64x4_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_f64x8
	struct _simd_f64x8 {
		_simd_f64x4 lo;
		_simd_f64x4 hi;
	};
	#define _simd_f64x8_splitlo_(X) X.lo
	#define _simd_f64x8_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_f64x8_splithi_(X) X.hi
	#define _simd_f64x8_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_f64x8_combine_(X,Y) _simd_f64x8({X,Y})
	#define _simd_f64x8_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_f64x16
	struct _simd_f64x16 {
		_simd_f64x8 lo;
		_simd_f64x8 hi;
	};
	#define _simd_f64x16_splitlo_(X) X.lo
	#define _simd_f64x16_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_f64x16_splithi_(X) X.hi
	#define _simd_f64x16_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_f64x16_combine_(X,Y) _simd_f64x16({X,Y})
	#define _simd_f64x16_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_f64x32
	struct _simd_f64x32 {
		_simd_f64x16 lo;
		_simd_f64x16 hi;
	};
	#define _simd_f64x32_splitlo_(X) X.lo
	#define _simd_f64x32_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_f64x32_splithi_(X) X.hi
	#define _simd_f64x32_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_f64x32_combine_(X,Y) _simd_f64x32({X,Y})
	#define _simd_f64x32_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_f64x64
	struct _simd_f64x64 {
		_simd_f64x32 lo;
		_simd_f64x32 hi;
	};
	#define _simd_f64x64_splitlo_(X) X.lo
	#define _simd_f64x64_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_f64x64_splithi_(X) X.hi
	#define _simd_f64x64_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_f64x64_combine_(X,Y) _simd_f64x64({X,Y})
	#define _simd_f64x64_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_f32x2
	struct _simd_f32x2 {
		_simd_f32x1 lo;
		_simd_f32x1 hi;
	};
	#define _simd_f32x2_splitlo_(X) X.lo
	#define _simd_f32x2_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_f32x2_splithi_(X) X.hi
	#define _simd_f32x2_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_f32x2_combine_(X,Y) _simd_f32x2({X,Y})
	#define _simd_f32x2_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_f32x4
	struct _simd_f32x4 {
		_simd_f32x2 lo;
		_simd_f32x2 hi;
	};
	#define _simd_f32x4_splitlo_(X) X.lo
	#define _simd_f32x4_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_f32x4_splithi_(X) X.hi
	#define _simd_f32x4_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_f32x4_combine_(X,Y) _simd_f32x4({X,Y})
	#define _simd_f32x4_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_f32x8
	struct _simd_f32x8 {
		_simd_f32x4 lo;
		_simd_f32x4 hi;
	};
	#define _simd_f32x8_splitlo_(X) X.lo
	#define _simd_f32x8_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_f32x8_splithi_(X) X.hi
	#define _simd_f32x8_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_f32x8_combine_(X,Y) _simd_f32x8({X,Y})
	#define _simd_f32x8_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_f32x16
	struct _simd_f32x16 {
		_simd_f32x8 lo;
		_simd_f32x8 hi;
	};
	#define _simd_f32x16_splitlo_(X) X.lo
	#define _simd_f32x16_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_f32x16_splithi_(X) X.hi
	#define _simd_f32x16_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_f32x16_combine_(X,Y) _simd_f32x16({X,Y})
	#define _simd_f32x16_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_f32x32
	struct _simd_f32x32 {
		_simd_f32x16 lo;
		_simd_f32x16 hi;
	};
	#define _simd_f32x32_splitlo_(X) X.lo
	#define _simd_f32x32_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_f32x32_splithi_(X) X.hi
	#define _simd_f32x32_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_f32x32_combine_(X,Y) _simd_f32x32({X,Y})
	#define _simd_f32x32_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_f32x64
	struct _simd_f32x64 {
		_simd_f32x32 lo;
		_simd_f32x32 hi;
	};
	#define _simd_f32x64_splitlo_(X) X.lo
	#define _simd_f32x64_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_f32x64_splithi_(X) X.hi
	#define _simd_f32x64_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_f32x64_combine_(X,Y) _simd_f32x64({X,Y})
	#define _simd_f32x64_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_s64x2
	struct _simd_s64x2 {
		_simd_s64x1 lo;
		_simd_s64x1 hi;
	};
	#define _simd_s64x2_splitlo_(X) X.lo
	#define _simd_s64x2_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_s64x2_splithi_(X) X.hi
	#define _simd_s64x2_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_s64x2_combine_(X,Y) _simd_s64x2({X,Y})
	#define _simd_s64x2_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_s64x4
	struct _simd_s64x4 {
		_simd_s64x2 lo;
		_simd_s64x2 hi;
	};
	#define _simd_s64x4_splitlo_(X) X.lo
	#define _simd_s64x4_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_s64x4_splithi_(X) X.hi
	#define _simd_s64x4_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_s64x4_combine_(X,Y) _simd_s64x4({X,Y})
	#define _simd_s64x4_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_s64x8
	struct _simd_s64x8 {
		_simd_s64x4 lo;
		_simd_s64x4 hi;
	};
	#define _simd_s64x8_splitlo_(X) X.lo
	#define _simd_s64x8_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_s64x8_splithi_(X) X.hi
	#define _simd_s64x8_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_s64x8_combine_(X,Y) _simd_s64x8({X,Y})
	#define _simd_s64x8_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_s64x16
	struct _simd_s64x16 {
		_simd_s64x8 lo;
		_simd_s64x8 hi;
	};
	#define _simd_s64x16_splitlo_(X) X.lo
	#define _simd_s64x16_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_s64x16_splithi_(X) X.hi
	#define _simd_s64x16_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_s64x16_combine_(X,Y) _simd_s64x16({X,Y})
	#define _simd_s64x16_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_s64x32
	struct _simd_s64x32 {
		_simd_s64x16 lo;
		_simd_s64x16 hi;
	};
	#define _simd_s64x32_splitlo_(X) X.lo
	#define _simd_s64x32_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_s64x32_splithi_(X) X.hi
	#define _simd_s64x32_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_s64x32_combine_(X,Y) _simd_s64x32({X,Y})
	#define _simd_s64x32_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_s64x64
	struct _simd_s64x64 {
		_simd_s64x32 lo;
		_simd_s64x32 hi;
	};
	#define _simd_s64x64_splitlo_(X) X.lo
	#define _simd_s64x64_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_s64x64_splithi_(X) X.hi
	#define _simd_s64x64_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_s64x64_combine_(X,Y) _simd_s64x64({X,Y})
	#define _simd_s64x64_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_u64x2
	struct _simd_u64x2 {
		_simd_u64x1 lo;
		_simd_u64x1 hi;
	};
	#define _simd_u64x2_splitlo_(X) X.lo
	#define _simd_u64x2_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_u64x2_splithi_(X) X.hi
	#define _simd_u64x2_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_u64x2_combine_(X,Y) _simd_u64x2({X,Y})
	#define _simd_u64x2_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_u64x4
	struct _simd_u64x4 {
		_simd_u64x2 lo;
		_simd_u64x2 hi;
	};
	#define _simd_u64x4_splitlo_(X) X.lo
	#define _simd_u64x4_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_u64x4_splithi_(X) X.hi
	#define _simd_u64x4_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_u64x4_combine_(X,Y) _simd_u64x4({X,Y})
	#define _simd_u64x4_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_u64x8
	struct _simd_u64x8 {
		_simd_u64x4 lo;
		_simd_u64x4 hi;
	};
	#define _simd_u64x8_splitlo_(X) X.lo
	#define _simd_u64x8_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_u64x8_splithi_(X) X.hi
	#define _simd_u64x8_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_u64x8_combine_(X,Y) _simd_u64x8({X,Y})
	#define _simd_u64x8_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_u64x16
	struct _simd_u64x16 {
		_simd_u64x8 lo;
		_simd_u64x8 hi;
	};
	#define _simd_u64x16_splitlo_(X) X.lo
	#define _simd_u64x16_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_u64x16_splithi_(X) X.hi
	#define _simd_u64x16_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_u64x16_combine_(X,Y) _simd_u64x16({X,Y})
	#define _simd_u64x16_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_u64x32
	struct _simd_u64x32 {
		_simd_u64x16 lo;
		_simd_u64x16 hi;
	};
	#define _simd_u64x32_splitlo_(X) X.lo
	#define _simd_u64x32_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_u64x32_splithi_(X) X.hi
	#define _simd_u64x32_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_u64x32_combine_(X,Y) _simd_u64x32({X,Y})
	#define _simd_u64x32_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_u64x64
	struct _simd_u64x64 {
		_simd_u64x32 lo;
		_simd_u64x32 hi;
	};
	#define _simd_u64x64_splitlo_(X) X.lo
	#define _simd_u64x64_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_u64x64_splithi_(X) X.hi
	#define _simd_u64x64_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_u64x64_combine_(X,Y) _simd_u64x64({X,Y})
	#define _simd_u64x64_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_s32x2
	struct _simd_s32x2 {
		_simd_s32x1 lo;
		_simd_s32x1 hi;
	};
	#define _simd_s32x2_splitlo_(X) X.lo
	#define _simd_s32x2_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_s32x2_splithi_(X) X.hi
	#define _simd_s32x2_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_s32x2_combine_(X,Y) _simd_s32x2({X,Y})
	#define _simd_s32x2_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_s32x4
	struct _simd_s32x4 {
		_simd_s32x2 lo;
		_simd_s32x2 hi;
	};
	#define _simd_s32x4_splitlo_(X) X.lo
	#define _simd_s32x4_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_s32x4_splithi_(X) X.hi
	#define _simd_s32x4_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_s32x4_combine_(X,Y) _simd_s32x4({X,Y})
	#define _simd_s32x4_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_s32x8
	struct _simd_s32x8 {
		_simd_s32x4 lo;
		_simd_s32x4 hi;
	};
	#define _simd_s32x8_splitlo_(X) X.lo
	#define _simd_s32x8_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_s32x8_splithi_(X) X.hi
	#define _simd_s32x8_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_s32x8_combine_(X,Y) _simd_s32x8({X,Y})
	#define _simd_s32x8_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_s32x16
	struct _simd_s32x16 {
		_simd_s32x8 lo;
		_simd_s32x8 hi;
	};
	#define _simd_s32x16_splitlo_(X) X.lo
	#define _simd_s32x16_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_s32x16_splithi_(X) X.hi
	#define _simd_s32x16_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_s32x16_combine_(X,Y) _simd_s32x16({X,Y})
	#define _simd_s32x16_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_s32x32
	struct _simd_s32x32 {
		_simd_s32x16 lo;
		_simd_s32x16 hi;
	};
	#define _simd_s32x32_splitlo_(X) X.lo
	#define _simd_s32x32_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_s32x32_splithi_(X) X.hi
	#define _simd_s32x32_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_s32x32_combine_(X,Y) _simd_s32x32({X,Y})
	#define _simd_s32x32_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_s32x64
	struct _simd_s32x64 {
		_simd_s32x32 lo;
		_simd_s32x32 hi;
	};
	#define _simd_s32x64_splitlo_(X) X.lo
	#define _simd_s32x64_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_s32x64_splithi_(X) X.hi
	#define _simd_s32x64_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_s32x64_combine_(X,Y) _simd_s32x64({X,Y})
	#define _simd_s32x64_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_u32x2
	struct _simd_u32x2 {
		_simd_u32x1 lo;
		_simd_u32x1 hi;
	};
	#define _simd_u32x2_splitlo_(X) X.lo
	#define _simd_u32x2_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_u32x2_splithi_(X) X.hi
	#define _simd_u32x2_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_u32x2_combine_(X,Y) _simd_u32x2({X,Y})
	#define _simd_u32x2_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_u32x4
	struct _simd_u32x4 {
		_simd_u32x2 lo;
		_simd_u32x2 hi;
	};
	#define _simd_u32x4_splitlo_(X) X.lo
	#define _simd_u32x4_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_u32x4_splithi_(X) X.hi
	#define _simd_u32x4_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_u32x4_combine_(X,Y) _simd_u32x4({X,Y})
	#define _simd_u32x4_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_u32x8
	struct _simd_u32x8 {
		_simd_u32x4 lo;
		_simd_u32x4 hi;
	};
	#define _simd_u32x8_splitlo_(X) X.lo
	#define _simd_u32x8_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_u32x8_splithi_(X) X.hi
	#define _simd_u32x8_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_u32x8_combine_(X,Y) _simd_u32x8({X,Y})
	#define _simd_u32x8_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_u32x16
	struct _simd_u32x16 {
		_simd_u32x8 lo;
		_simd_u32x8 hi;
	};
	#define _simd_u32x16_splitlo_(X) X.lo
	#define _simd_u32x16_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_u32x16_splithi_(X) X.hi
	#define _simd_u32x16_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_u32x16_combine_(X,Y) _simd_u32x16({X,Y})
	#define _simd_u32x16_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_u32x32
	struct _simd_u32x32 {
		_simd_u32x16 lo;
		_simd_u32x16 hi;
	};
	#define _simd_u32x32_splitlo_(X) X.lo
	#define _simd_u32x32_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_u32x32_splithi_(X) X.hi
	#define _simd_u32x32_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_u32x32_combine_(X,Y) _simd_u32x32({X,Y})
	#define _simd_u32x32_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_u32x64
	struct _simd_u32x64 {
		_simd_u32x32 lo;
		_simd_u32x32 hi;
	};
	#define _simd_u32x64_splitlo_(X) X.lo
	#define _simd_u32x64_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_u32x64_splithi_(X) X.hi
	#define _simd_u32x64_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_u32x64_combine_(X,Y) _simd_u32x64({X,Y})
	#define _simd_u32x64_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_s16x2
	struct _simd_s16x2 {
		_simd_s16x1 lo;
		_simd_s16x1 hi;
	};
	#define _simd_s16x2_splitlo_(X) X.lo
	#define _simd_s16x2_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_s16x2_splithi_(X) X.hi
	#define _simd_s16x2_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_s16x2_combine_(X,Y) _simd_s16x2({X,Y})
	#define _simd_s16x2_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_s16x4
	struct _simd_s16x4 {
		_simd_s16x2 lo;
		_simd_s16x2 hi;
	};
	#define _simd_s16x4_splitlo_(X) X.lo
	#define _simd_s16x4_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_s16x4_splithi_(X) X.hi
	#define _simd_s16x4_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_s16x4_combine_(X,Y) _simd_s16x4({X,Y})
	#define _simd_s16x4_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_s16x8
	struct _simd_s16x8 {
		_simd_s16x4 lo;
		_simd_s16x4 hi;
	};
	#define _simd_s16x8_splitlo_(X) X.lo
	#define _simd_s16x8_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_s16x8_splithi_(X) X.hi
	#define _simd_s16x8_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_s16x8_combine_(X,Y) _simd_s16x8({X,Y})
	#define _simd_s16x8_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_s16x16
	struct _simd_s16x16 {
		_simd_s16x8 lo;
		_simd_s16x8 hi;
	};
	#define _simd_s16x16_splitlo_(X) X.lo
	#define _simd_s16x16_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_s16x16_splithi_(X) X.hi
	#define _simd_s16x16_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_s16x16_combine_(X,Y) _simd_s16x16({X,Y})
	#define _simd_s16x16_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_s16x32
	struct _simd_s16x32 {
		_simd_s16x16 lo;
		_simd_s16x16 hi;
	};
	#define _simd_s16x32_splitlo_(X) X.lo
	#define _simd_s16x32_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_s16x32_splithi_(X) X.hi
	#define _simd_s16x32_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_s16x32_combine_(X,Y) _simd_s16x32({X,Y})
	#define _simd_s16x32_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_s16x64
	struct _simd_s16x64 {
		_simd_s16x32 lo;
		_simd_s16x32 hi;
	};
	#define _simd_s16x64_splitlo_(X) X.lo
	#define _simd_s16x64_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_s16x64_splithi_(X) X.hi
	#define _simd_s16x64_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_s16x64_combine_(X,Y) _simd_s16x64({X,Y})
	#define _simd_s16x64_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_u16x2
	struct _simd_u16x2 {
		_simd_u16x1 lo;
		_simd_u16x1 hi;
	};
	#define _simd_u16x2_splitlo_(X) X.lo
	#define _simd_u16x2_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_u16x2_splithi_(X) X.hi
	#define _simd_u16x2_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_u16x2_combine_(X,Y) _simd_u16x2({X,Y})
	#define _simd_u16x2_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_u16x4
	struct _simd_u16x4 {
		_simd_u16x2 lo;
		_simd_u16x2 hi;
	};
	#define _simd_u16x4_splitlo_(X) X.lo
	#define _simd_u16x4_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_u16x4_splithi_(X) X.hi
	#define _simd_u16x4_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_u16x4_combine_(X,Y) _simd_u16x4({X,Y})
	#define _simd_u16x4_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_u16x8
	struct _simd_u16x8 {
		_simd_u16x4 lo;
		_simd_u16x4 hi;
	};
	#define _simd_u16x8_splitlo_(X) X.lo
	#define _simd_u16x8_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_u16x8_splithi_(X) X.hi
	#define _simd_u16x8_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_u16x8_combine_(X,Y) _simd_u16x8({X,Y})
	#define _simd_u16x8_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_u16x16
	struct _simd_u16x16 {
		_simd_u16x8 lo;
		_simd_u16x8 hi;
	};
	#define _simd_u16x16_splitlo_(X) X.lo
	#define _simd_u16x16_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_u16x16_splithi_(X) X.hi
	#define _simd_u16x16_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_u16x16_combine_(X,Y) _simd_u16x16({X,Y})
	#define _simd_u16x16_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_u16x32
	struct _simd_u16x32 {
		_simd_u16x16 lo;
		_simd_u16x16 hi;
	};
	#define _simd_u16x32_splitlo_(X) X.lo
	#define _simd_u16x32_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_u16x32_splithi_(X) X.hi
	#define _simd_u16x32_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_u16x32_combine_(X,Y) _simd_u16x32({X,Y})
	#define _simd_u16x32_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_u16x64
	struct _simd_u16x64 {
		_simd_u16x32 lo;
		_simd_u16x32 hi;
	};
	#define _simd_u16x64_splitlo_(X) X.lo
	#define _simd_u16x64_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_u16x64_splithi_(X) X.hi
	#define _simd_u16x64_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_u16x64_combine_(X,Y) _simd_u16x64({X,Y})
	#define _simd_u16x64_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_s8x2
	struct _simd_s8x2 {
		_simd_s8x1 lo;
		_simd_s8x1 hi;
	};
	#define _simd_s8x2_splitlo_(X) X.lo
	#define _simd_s8x2_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_s8x2_splithi_(X) X.hi
	#define _simd_s8x2_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_s8x2_combine_(X,Y) _simd_s8x2({X,Y})
	#define _simd_s8x2_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_s8x4
	struct _simd_s8x4 {
		_simd_s8x2 lo;
		_simd_s8x2 hi;
	};
	#define _simd_s8x4_splitlo_(X) X.lo
	#define _simd_s8x4_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_s8x4_splithi_(X) X.hi
	#define _simd_s8x4_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_s8x4_combine_(X,Y) _simd_s8x4({X,Y})
	#define _simd_s8x4_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_s8x8
	struct _simd_s8x8 {
		_simd_s8x4 lo;
		_simd_s8x4 hi;
	};
	#define _simd_s8x8_splitlo_(X) X.lo
	#define _simd_s8x8_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_s8x8_splithi_(X) X.hi
	#define _simd_s8x8_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_s8x8_combine_(X,Y) _simd_s8x8({X,Y})
	#define _simd_s8x8_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_s8x16
	struct _simd_s8x16 {
		_simd_s8x8 lo;
		_simd_s8x8 hi;
	};
	#define _simd_s8x16_splitlo_(X) X.lo
	#define _simd_s8x16_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_s8x16_splithi_(X) X.hi
	#define _simd_s8x16_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_s8x16_combine_(X,Y) _simd_s8x16({X,Y})
	#define _simd_s8x16_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_s8x32
	struct _simd_s8x32 {
		_simd_s8x16 lo;
		_simd_s8x16 hi;
	};
	#define _simd_s8x32_splitlo_(X) X.lo
	#define _simd_s8x32_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_s8x32_splithi_(X) X.hi
	#define _simd_s8x32_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_s8x32_combine_(X,Y) _simd_s8x32({X,Y})
	#define _simd_s8x32_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_s8x64
	struct _simd_s8x64 {
		_simd_s8x32 lo;
		_simd_s8x32 hi;
	};
	#define _simd_s8x64_splitlo_(X) X.lo
	#define _simd_s8x64_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_s8x64_splithi_(X) X.hi
	#define _simd_s8x64_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_s8x64_combine_(X,Y) _simd_s8x64({X,Y})
	#define _simd_s8x64_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_u8x2
	struct _simd_u8x2 {
		_simd_u8x1 lo;
		_simd_u8x1 hi;
	};
	#define _simd_u8x2_splitlo_(X) X.lo
	#define _simd_u8x2_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_u8x2_splithi_(X) X.hi
	#define _simd_u8x2_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_u8x2_combine_(X,Y) _simd_u8x2({X,Y})
	#define _simd_u8x2_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_u8x4
	struct _simd_u8x4 {
		_simd_u8x2 lo;
		_simd_u8x2 hi;
	};
	#define _simd_u8x4_splitlo_(X) X.lo
	#define _simd_u8x4_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_u8x4_splithi_(X) X.hi
	#define _simd_u8x4_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_u8x4_combine_(X,Y) _simd_u8x4({X,Y})
	#define _simd_u8x4_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_u8x8
	struct _simd_u8x8 {
		_simd_u8x4 lo;
		_simd_u8x4 hi;
	};
	#define _simd_u8x8_splitlo_(X) X.lo
	#define _simd_u8x8_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_u8x8_splithi_(X) X.hi
	#define _simd_u8x8_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_u8x8_combine_(X,Y) _simd_u8x8({X,Y})
	#define _simd_u8x8_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_u8x16
	struct _simd_u8x16 {
		_simd_u8x8 lo;
		_simd_u8x8 hi;
	};
	#define _simd_u8x16_splitlo_(X) X.lo
	#define _simd_u8x16_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_u8x16_splithi_(X) X.hi
	#define _simd_u8x16_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_u8x16_combine_(X,Y) _simd_u8x16({X,Y})
	#define _simd_u8x16_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_u8x32
	struct _simd_u8x32 {
		_simd_u8x16 lo;
		_simd_u8x16 hi;
	};
	#define _simd_u8x32_splitlo_(X) X.lo
	#define _simd_u8x32_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_u8x32_splithi_(X) X.hi
	#define _simd_u8x32_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_u8x32_combine_(X,Y) _simd_u8x32({X,Y})
	#define _simd_u8x32_combine_instruction_set anvil::simd::IS_NONE
#endif
#ifndef _simd_u8x64
	struct _simd_u8x64 {
		_simd_u8x32 lo;
		_simd_u8x32 hi;
	};
	#define _simd_u8x64_splitlo_(X) X.lo
	#define _simd_u8x64_splitlo_instruction_set anvil::simd::IS_NONE
	#define _simd_u8x64_splithi_(X) X.hi
	#define _simd_u8x64_splithi_instruction_set anvil::simd::IS_NONE
	#define _simd_u8x64_combine_(X,Y) _simd_u8x64({X,Y})
	#define _simd_u8x64_combine_instruction_set anvil::simd::IS_NONE
#endif

// Split / Combine

#include "anvil/maths/simd/splitlo.hpp"
#include "anvil/maths/simd/splithi.hpp"
#include "anvil/maths/simd/combine.hpp"


// Fill undefined

#include "anvil/maths/simd/fill_undefined.hpp"

// Fill zero

#include "anvil/maths/simd/fill_zero.hpp"

// Fill scalar

#include "anvil/maths/simd/fill_scalar.hpp"

// Set

#include "anvil/maths/simd/set.hpp"
// Insert

#define _simd_insert_(A,S)\
	static ANVIL_STRONG_INLINE _simd_ ## A  ANVIL_SIMD_CALL _simd_ ## A ## _insert_safe(register _simd_ ## A x, int i, const register S s)  { reinterpret_cast<S*>(&x)[i] = s;  return x; }

#define _simd_insert(T)\
	_simd_insert_(T ## x2, _simd_ ## T ## x1)\
	_simd_insert_(T ## x4, _simd_ ## T ## x1)\
	_simd_insert_(T ## x8, _simd_ ## T ## x1)\
	_simd_insert_(T ## x16, _simd_ ## T ## x1)\
	_simd_insert_(T ## x32, _simd_ ## T ## x1)\
	_simd_insert_(T ## x64, _simd_ ## T ## x1)

_simd_insert(f64)
_simd_insert(f32)
_simd_insert(s64)
_simd_insert(u64)
_simd_insert(s32)
_simd_insert(u32)
_simd_insert(s16)
_simd_insert(u16)
_simd_insert(s8)
_simd_insert(u8)

#undef _simd_insert
#undef _simd_insert_

#include "anvil/maths/simd/insert.hpp"

// Extract

#define _simd_extract_(A,S)\
	static ANVIL_STRONG_INLINE S ANVIL_SIMD_CALL _simd_ ## A ## _extract_safe(const register _simd_ ## A x, int i)  { return reinterpret_cast<const S*>(&x)[i]; }

#define _simd_extract(T)\
	_simd_extract_(T ## x2, _simd_ ## T ## x1)\
	_simd_extract_(T ## x4, _simd_ ## T ## x1)\
	_simd_extract_(T ## x8, _simd_ ## T ## x1)\
	_simd_extract_(T ## x16, _simd_ ## T ## x1)\
	_simd_extract_(T ## x32, _simd_ ## T ## x1)\
	_simd_extract_(T ## x64, _simd_ ## T ## x1)

_simd_extract(f64)
_simd_extract(f32)
_simd_extract(s64)
_simd_extract(u64)
_simd_extract(s32)
_simd_extract(u32)
_simd_extract(s16)
_simd_extract(u16)
_simd_extract(s8)
_simd_extract(u8)

#undef _simd_extract
#undef _simd_extract_

#include "anvil/maths/simd/extract.hpp"

// Numeric Operators

#include "anvil/maths/simd/add.hpp"
#include "anvil/maths/simd/sub.hpp"
#include "anvil/maths/simd/mul.hpp"
#include "anvil/maths/simd/div.hpp"

// Bitwise Operators

#include "anvil/maths/simd/and.hpp"
#include "anvil/maths/simd/or.hpp"
#include "anvil/maths/simd/xor.hpp"
#include "anvil/maths/simd/lshift.hpp"
#include "anvil/maths/simd/rshift.hpp"
#include "anvil/maths/simd/not.hpp"

// Min/Max

#include "anvil/maths/simd/min.hpp"
#include "anvil/maths/simd/max.hpp"

// Comparisons

#include "anvil/maths/simd/cmpeq.hpp"
#include "anvil/maths/simd/cmpne.hpp"
#include "anvil/maths/simd/cmplt.hpp"
#include "anvil/maths/simd/cmpgt.hpp"
#include "anvil/maths/simd/cmple.hpp"
#include "anvil/maths/simd/cmpge.hpp"

// Abs
#include "anvil/maths/simd/abs.hpp"

// Ceil, Floor, Round
#include "anvil/maths/simd/ceil.hpp"
#include "anvil/maths/simd/floor.hpp"
#include "anvil/maths/simd/round.hpp"

// Fma, Fms
#include "anvil/maths/simd/fma.hpp"
#include "anvil/maths/simd/fms.hpp"

// Trigonometric
#include "anvil/maths/simd/cos.hpp"
#include "anvil/maths/simd/sin.hpp"
#include "anvil/maths/simd/tan.hpp"
#include "anvil/maths/simd/acos.hpp"
#include "anvil/maths/simd/asin.hpp"
#include "anvil/maths/simd/atan.hpp"
#include "anvil/maths/simd/cosh.hpp"
#include "anvil/maths/simd/sinh.hpp"
#include "anvil/maths/simd/tanh.hpp"
#include "anvil/maths/simd/atan2.hpp"
#include "anvil/maths/simd/hypot.hpp"

// Log
#include "anvil/maths/simd/log.hpp"
#include "anvil/maths/simd/log2.hpp"
#include "anvil/maths/simd/log10.hpp"

// Pow, Sqrt
#include "anvil/maths/simd/pow.hpp"
#include "anvil/maths/simd/sqrt.hpp"
#include "anvil/maths/simd/cbrt.hpp"

// Misc
#include "anvil/maths/simd/sum.hpp"
#include "anvil/maths/simd/mod.hpp"
#include "anvil/maths/simd/dim.hpp"
#include "anvil/maths/simd/exp.hpp"
#include "anvil/maths/simd/cast.hpp"

namespace anvil { namespace simd {

	// Instruction set definitions

	enum InstructionSet : int16_t {
		IS_NONE,
#ifdef ANVIL_USE_INTEL_SIMD_INTRINSICS
#define ANVIL_SIMD_MMX        (1 << 0)
#define ANVIL_SIMD_SSE        (1 << 1)
#define ANVIL_SIMD_SSE_2      (1 << 2)
#define ANVIL_SIMD_SSE_3      (1 << 3)
#define ANVIL_SIMD_SSSE_3     (1 << 4)
#define ANVIL_SIMD_SSE_4_1    (1 << 5)
#define ANVIL_SIMD_SSE_4_2    (1 << 6)
#define ANVIL_SIMD_AVX        (1 << 7)
#define ANVIL_SIMD_FMA        (1 << 8)
#define ANVIL_SIMD_AVX_2      (1 << 9)
#define ANVIL_SIMD_KNC        (1 << 10)
#define ANVIL_SIMD_AVX_512_F  (1 << 11)
#define ANVIL_SIMD_AVX_512_PF (1 << 12)
#define ANVIL_SIMD_AVX_512_ER (1 << 13)
#define ANVIL_SIMD_AVX_512_CD (1 << 14)

		IS_MMX        = ANVIL_SIMD_MMX,
		IS_SSE        = ANVIL_SIMD_SSE,      
		IS_SSE_2      = ANVIL_SIMD_SSE_2,    
		IS_SSE_3      = ANVIL_SIMD_SSE_3,   
		IS_SSSE_3     = ANVIL_SIMD_SSSE_3,   
		IS_SSE_4_1    = ANVIL_SIMD_SSE_4_1,   
		IS_SSE_4_2    = ANVIL_SIMD_SSE_4_2,   
		IS_AVX        = ANVIL_SIMD_AVX,       
		IS_FMA        = ANVIL_SIMD_FMA,      
		IS_AVX_2      = ANVIL_SIMD_AVX_2,     
		IS_KNC        = ANVIL_SIMD_KNC,       
		IS_AVX_512_F  = ANVIL_SIMD_AVX_512_F, 
		IS_AVX_512_PF = ANVIL_SIMD_AVX_512_PF,
		IS_AVX_512_ER = ANVIL_SIMD_AVX_512_ER,
		IS_AVX_512_CD = ANVIL_SIMD_AVX_512_CD,

		IS_AVX_512    = IS_AVX_512_F | IS_AVX_512_PF | IS_AVX_512_ER | IS_AVX_512_CD
#endif
	};

#if ANVIL_ARCHITECTURE == ANVIL_X86
	#ifndef ANVIL_ASSUME_SIMD_SUPPORT
		#define ANVIL_ASSUME_SIMD_SUPPORT ANVIL_SIMD__MMX
	#elif ANVIL_ASSUME_SIMD_SUPPORT < ANVIL_SIMD_MMX
		#undef ANVIL_ASSUME_SIMD_SUPPORT
		#define ANVIL_ASSUME_SIMD_SUPPORT ANVIL_SIMD_MMX
	#endif
#elif ANVIL_ARCHITECTURE == ANVIL_X64
	#ifndef ANVIL_ASSUME_SIMD_SUPPORT
		#define ANVIL_ASSUME_SIMD_SUPPORT ANVIL_SIMD_SSE_2
	#elif ANVIL_ASSUME_SIMD_SUPPORT < ANVIL_SIMD_SSE_2
		#undef ANVIL_ASSUME_SIMD_SUPPORT
		#define ANVIL_ASSUME_SIMD_SUPPORT ANVIL_SIMD_SSE_2
	#endif
#endif

	namespace detail {
	static int16_t ANVIL_SIMD_CALL CheckInstructionSetSupport() {
		int16_t flags = 0;
	#ifdef ANVIL_USE_INTEL_SIMD_INTRINSICS
			int data[2][4];
			__cpuid(data[0], 0);
			const int ids = data[0][0];
			if (ids < 7) {
				if (ids < 1) {
					return false;
				}else {
					__cpuidex(data[0], 1, 0);
					memset(data[1], 0, sizeof(int) * 4);
				}
			}else {
				__cpuidex(data[0], 1, 0);
				__cpuidex(data[1], 7, 0);
			}
			enum {
				EAX_,
				EBX_,
				ECX_,
				EDX_
			};

			if (data[0][EDX_] & (1 << 23)) {
				flags |= IS_MMX;
			} if (data[0][EDX_] & (1 << 25)) {
				flags |= IS_SSE;
			} if (data[0][EDX_] & (1 << 26)) {
				flags |= IS_SSE_2;
			} if (data[0][ECX_] & (1 << 0)) {
				flags |= IS_SSE_3;
			} if (data[0][ECX_] & (1 << 9)) {
				flags |= IS_SSSE_3;
			} if (data[0][ECX_] & (1 << 19)) {
				flags |= IS_SSE_4_1;
			} if (data[0][ECX_] & (1 << 20)) {
				flags |= IS_SSE_4_2;
			} if (data[0][ECX_] & (1 << 28)) {
				flags |= IS_AVX;
			} if (data[0][EBX_] & (1 << 5)) {
				flags |= IS_AVX_2;
			} if (false) { //! \todo Implement
				flags |= IS_KNC;
			} if (data[1][EBX_] & (1 << 16)) {
				flags |= IS_AVX_512_F;
			} if (data[1][EBX_] & (1 << 26)) {
				flags |= IS_AVX_512_PF;
			} if (data[1][EBX_] & (1 << 27)) {
				flags |= IS_AVX_512_ER;
			} if (data[1][EBX_] & (1 << 28)) {
				flags |= IS_AVX_512_CD;
			}
	#endif
			return flags;
		}
	}


	static ANVIL_STRONG_INLINE bool ANVIL_SIMD_CALL IsInstructionSetSupported(InstructionSet aSet) {
		static const int64_t g_enabled_sets = detail::CheckInstructionSetSupport();
		return (g_enabled_sets & aSet) == aSet;
	}

	template<InstructionSet IS>
	static ANVIL_STRONG_INLINE bool IsInstructionSetSupported() {
		return IsInstructionSetSupported(IS);
	}

	template<>
	ANVIL_CONSTEXPR_FN static ANVIL_STRONG_INLINE bool IsInstructionSetSupported<IS_NONE>() {
		return true;
	}

//#ifdef ANVIL_USE_INTEL_SIMD_INTRINSICS
	#if ANVIL_ASSUME_SIMD_SUPPORT >= ANVIL_SIMD_MMX
	template<>
	ANVIL_CONSTEXPR_FN static ANVIL_STRONG_INLINE bool IsInstructionSetSupported<IS_MMX>() {
		return true;
	}
	#endif
	#if ANVIL_ASSUME_SIMD_SUPPORT >= ANVIL_SIMD_SSE
	template<>
	ANVIL_CONSTEXPR_FN static ANVIL_STRONG_INLINE bool IsInstructionSetSupported<IS_SSE>() {
		return true;
	}
	#endif
	#if ANVIL_ASSUME_SIMD_SUPPORT >= ANVIL_SIMD_SSE_2
	template<>
	ANVIL_CONSTEXPR_FN static ANVIL_STRONG_INLINE bool IsInstructionSetSupported<IS_SSE_2>() {
		return true;
	}
	#endif
	#if ANVIL_ASSUME_SIMD_SUPPORT >= ANVIL_SIMD_SSE_3
	template<>
	ANVIL_CONSTEXPR_FN static ANVIL_STRONG_INLINE bool IsInstructionSetSupported<IS_SSE_3>() {
		return true;
	}
	#endif
	#if ANVIL_ASSUME_SIMD_SUPPORT >= ANVIL_SIMD_SSSE_3
	template<>
	ANVIL_CONSTEXPR_FN static ANVIL_STRONG_INLINE bool IsInstructionSetSupported<IS_SSSE_3>() {
		return true;
	}
	#endif
	#if ANVIL_ASSUME_SIMD_SUPPORT >= ANVIL_SIMD_SSE_4_1
	template<>
	ANVIL_CONSTEXPR_FN static ANVIL_STRONG_INLINE bool IsInstructionSetSupported<IS_SSE_4_1>() {
		return true;
	}
	#endif
	#if ANVIL_ASSUME_SIMD_SUPPORT >= ANVIL_SIMD_SSE_4_2
	template<>
	ANVIL_CONSTEXPR_FN static ANVIL_STRONG_INLINE bool IsInstructionSetSupported<IS_SSE_4_2>() {
		return true;
	}
	#endif
	#if ANVIL_ASSUME_SIMD_SUPPORT >= ANVIL_SIMD_AVX
	template<>
	ANVIL_CONSTEXPR_FN static ANVIL_STRONG_INLINE bool IsInstructionSetSupported<IS_AVX>() {
		return true;
	}
	#endif
	#if ANVIL_ASSUME_SIMD_SUPPORT >= ANVIL_SIMD_FMA
	template<>
	ANVIL_CONSTEXPR_FN static ANVIL_STRONG_INLINE bool IsInstructionSetSupported<IS_FMA>() {
		return true;
	}
	#endif
	#if ANVIL_ASSUME_SIMD_SUPPORT >= ANVIL_SIMD_AVX_2
	template<>
	ANVIL_CONSTEXPR_FN static ANVIL_STRONG_INLINE bool IsInstructionSetSupported<IS_AVX_2>() {
		return true;
	}
	#endif
//	#if ANVIL_ASSUME_SIMD_SUPPORT >= ANVIL_SIMD_KNC
//	template<>
//	ANVIL_CONSTEXPR_FN static ANVIL_STRONG_INLINE bool IsInstructionSetSupported<IS_KNC>() {
//		return true;
//	}
//	#endif
	#if ANVIL_ASSUME_SIMD_SUPPORT >= ANVIL_SIMD_AVX_512_F
	template<>
	ANVIL_CONSTEXPR_FN static ANVIL_STRONG_INLINE bool IsInstructionSetSupported<IS_AVX_512_F>() {
		return true;
	}
	#endif
	#if ANVIL_ASSUME_SIMD_SUPPORT >= ANVIL_SIMD_AVX_512_PF
	template<>
	ANVIL_CONSTEXPR_FN static ANVIL_STRONG_INLINE bool IsInstructionSetSupported<IS_AVX_512_PF>() {
		return true;
	}
	#endif
	#if ANVIL_ASSUME_SIMD_SUPPORT >= ANVIL_SIMD_AVX_512_ER
	template<>
	ANVIL_CONSTEXPR_FN static ANVIL_STRONG_INLINE bool IsInstructionSetSupported<IS_AVX_512_ER>() {
		return true;
	}
	#endif
	#if ANVIL_ASSUME_SIMD_SUPPORT >= ANVIL_SIMD_AVX_512_CD
	template<>
	ANVIL_CONSTEXPR_FN static ANVIL_STRONG_INLINE bool IsInstructionSetSupported<IS_AVX_512_CD>() {
		return true;
	}
	#endif
//#endif

	// Operation definitions

	enum Operation : int64_t {
		// Misc operations
		OP_FILLU,
		OP_FILL0,
		OP_FILLS,
		OP_CAST,
		OP_RESIZE ,
		OP_SHUFF,
		// 3 parameters
		OP_FMA,
		OP_FMS,
		// 2 parameters
		OP_ADD,
		OP_SUB,
		OP_MUL,
		OP_DIV,
		OP_MIN,
		OP_MAX,
		OP_AND,
		OP_OR,
		OP_XOR,
		OP_LSHIFT , 
		OP_RSHIFT , 
		OP_MOD, 
		OP_DIM, 
		OP_CMPEQ, 
		OP_CMPNE, 
		OP_CMPLT, 
		OP_CMPGT, 
		OP_CMPLE, 
		OP_CMPGE, 
		OP_ATAN2, 
		OP_REFLECT,
		OP_POW,
		OP_HYPOT,
		// 1 parameter
		OP_NOT, 
		OP_ABS, 
		OP_EXP, 
		OP_LOG, 
		OP_LOG2,
		OP_LOG10,
		OP_CEIL,
		OP_FLOOR, 
		OP_ROUND, 
		OP_SIN, 
		OP_COS, 
		OP_TAN, 
		OP_ASIN, 
		OP_ACOS, 
		OP_ATAN, 
		OP_COSH, 
		OP_SINH, 
		OP_TANH, 
		OP_SQRT, 
		OP_CBRT,
		// 1 Parameter, scalar output
		OP_AVG, 
		OP_SUM, 
		OP_POPCN,
	};

	namespace detail {
		template<Operation O>
		struct OperationParams {
			enum { value = 0 };
		};

		template<Operation O, class T, size_t S>
		struct OperationInstructionSet {
			enum : int64_t { value = IS_NONE };
		};
		
		template<> struct OperationParams<OP_FILLU>{ enum { value = 0 }; };
		template<> struct OperationParams<OP_FILL0>{ enum { value = 0 }; };
		template<> struct OperationParams<OP_FILLS>{ enum { value = 0 }; };
		template<> struct OperationParams<OP_CAST>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_RESIZE>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_SHUFF>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_FMA>{ enum { value = 3 }; };
		template<> struct OperationParams<OP_FMS>{ enum { value = 3 }; };
		template<> struct OperationParams<OP_ADD>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_SUB>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_MUL>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_DIV>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_MIN>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_MAX>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_OR>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_LSHIFT>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_RSHIFT>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_MOD>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_DIM>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_CMPEQ>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_CMPNE>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_CMPLT>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_CMPGT>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_CMPLE>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_CMPGE>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_ATAN2>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_REFLECT>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_NOT>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_ABS>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_EXP>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_LOG>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_LOG2>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_LOG10>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_CEIL>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_FLOOR>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_ROUND>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_SIN>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_COS>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_TAN>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_ASIN>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_ACOS>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_ATAN>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_COSH>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_SINH>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_TANH>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_SQRT>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_CBRT>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_AVG>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_SUM>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_POPCN>{ enum { value = 1 }; };

#include "anvil/maths/simd/OperationInstructionSet.hpp"
	}

	template<Operation O, class T>
	struct OperationInfo {
		enum : int64_t { 
			instruction_set_64 = detail::OperationInstructionSet<O, T, 64>::value,
			instruction_set_32 = detail::OperationInstructionSet<O, T, 32>::value,
			instruction_set_16 = detail::OperationInstructionSet<O, T, 16>::value,
			instruction_set_8 = detail::OperationInstructionSet<O, T, 8>::value,
			instruction_set_4 = detail::OperationInstructionSet<O, T, 4>::value,
			instruction_set_2 = detail::OperationInstructionSet<O, T, 2>::value,
			instruction_set_max = 
				instruction_set_64 ? instruction_set_64 :
				instruction_set_32 ? instruction_set_32 :
				instruction_set_16 ? instruction_set_16 :
				instruction_set_8 ? instruction_set_8 :
				instruction_set_4 ? instruction_set_4 :
				IS_NONE
		};
		enum {
			params = detail::OperationParams<O>::value,
			size_max = 
				instruction_set_64 ? 64 :
				instruction_set_32 ? 32 :
				instruction_set_16 ? 16 :
				instruction_set_8 ? 8 :
				instruction_set_4 ? 4 :
				2
		};

		template<size_t S>
		struct LoopInfo {
			enum {
				size = 
					instruction_set_64 && S >= 64 ? 64 :
					instruction_set_32 && S >= 32 ? 32 :
					instruction_set_16 && S >= 16 ? 16 :
					instruction_set_8 && S >= 8 ? 8 :
					instruction_set_4 && S >= 4 ? 4 :
					S >= 2 ? 2 :
					1,
				loops = S / size,
				remainder = S % S
			};
			enum : int64_t {
				instruction_set =
					size == 64 ? instruction_set_64 :
					size == 32 ? instruction_set_32 :
					size == 16 ? instruction_set_16 :
					size == 8 ? instruction_set_8  :
					size == 4 ? instruction_set_4  :
					IS_NONE
			};
		};
	};

	// Data Helpers

	template<class T, size_t S, Operation O>
	struct OperationDispatcher;

	template<class T, Operation O>
	struct DynamicOperationDispatcher;

#include "anvil/maths/simd/OperationDispatcher.hpp"
}}

#endif