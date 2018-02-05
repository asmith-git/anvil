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

#include "anvil/core/Cpu.hpp"
#include "anvil/core/Keywords.hpp"

#if (ANVIL_ARCHITECTURE == ANVIL_X86) || (ANVIL_ARCHITECTURE == ANVIL_X64)
	#if ANVIL_COMPILER == ANVIL_MSVC
		#include <immintrin.h>
		#include <intrin.h>
	#else
		#include <x86intrin.h>
#endif
#define ANVIL_SIMD_CALL __vectorcall 

// Types
typedef double float64x1_t;
typedef float float32x1_t;
typedef int64_t int64x1_t;
typedef uint64_t uint64x1_t;
typedef int32_t int32x1_t;
typedef uint32_t uint32x1_t;
typedef int16_t int16x1_t;
typedef uint16_t uint16x1_t;
typedef int8_t int8x1_t;
typedef uint8_t uint16x8_t;

typedef __m128d float64x2_t;
typedef __m256d float64x4_t;
typedef __m128 float32x4_t;
typedef __m256 float32x8_t;
typedef __m128i int64x2_t;
typedef __m256i int64x4_t;
typedef __m128i uint64x2_t;
typedef __m256i uint64x4_t;
typedef __m128i int32x4_t;
typedef __m256i int32x8_t;
typedef __m128i uint32x4_t;
typedef __m256i uint32x8_t;
typedef __m128i int16x8_t;
typedef __m256i int16x16_t;
typedef __m128i uint16x8_t;
typedef __m256i uint16x16_t;
typedef __m128i int8x16_t;
typedef __m256i int8x32_t;
typedef __m128i uint8x16_t;
typedef __m256i uint8x32_t;

typedef float32x4_t float32x2_t;
typedef int32x4_t int32x2_t;
typedef uint32x4_t uint32x2_t;
typedef int16x8_t int16x4_t;
typedef uint16x8_t uint16x4_t;
typedef int8x16_t int8x8_t;
typedef uint8x16_t uint8x8_t;

// Reinterpret

#define _simd_reinterpret_f64x1_as_s64x1(X) *reinterpret_cast<const int64x1_t*(&X)
#define _simd_reinterpret_f64x1_as_u64x1(X) *reinterpret_cast<const uint64x1_t*(&X)
#define _simd_reinterpret_f64x1_as_f32x2(X) *reinterpret_cast<const float32x2_t*(&X)
#define _simd_reinterpret_f64x2_as_f32x4(X) *reinterpret_cast<const float32x4_t*(&X)
#define _simd_reinterpret_f64x4_as_f32x8(X) *reinterpret_cast<const float32x8_t*(&X)
#define _simd_reinterpret_f64x1_as_s64x1(X) *reinterpret_cast<const int64x1_t*(&X)
#define _simd_reinterpret_f64x2_as_s64x2(X) *reinterpret_cast<const int64x2_t*(&X)
#define _simd_reinterpret_f64x4_as_s64x4(X) *reinterpret_cast<const int64x4_t*(&X)
#define _simd_reinterpret_f64x1_as_u64x1(X) *reinterpret_cast<const uint64x1_t*(&X)
#define _simd_reinterpret_f64x2_as_u64x2(X) *reinterpret_cast<const uint64x2_t*(&X)
#define _simd_reinterpret_f64x4_as_u64x4(X) *reinterpret_cast<const uint64x4_t*(&X)
#define _simd_reinterpret_f64x1_as_s32x2(X) *reinterpret_cast<const int32x2_t*(&X)
#define _simd_reinterpret_f64x2_as_s32x4(X) *reinterpret_cast<const int32x4_t*(&X)
#define _simd_reinterpret_f64x4_as_s32x8(X) *reinterpret_cast<const int32x8_t*(&X)
#define _simd_reinterpret_f64x1_as_u32x2(X) *reinterpret_cast<const uint32x2_t*(&X)
#define _simd_reinterpret_f64x2_as_u32x4(X) *reinterpret_cast<const uint32x4_t*(&X)
#define _simd_reinterpret_f64x4_as_u32x8(X) *reinterpret_cast<const uint32x8_t*(&X)
#define _simd_reinterpret_f64x1_as_s16x4(X) *reinterpret_cast<const int16x4_t*(&X)
#define _simd_reinterpret_f64x2_as_s16x8(X) *reinterpret_cast<const int16x8_t*(&X)
#define _simd_reinterpret_f64x4_as_s16x16(X) *reinterpret_cast<const int16x16_t*(&X)
#define _simd_reinterpret_f64x1_as_u16x4(X) *reinterpret_cast<const uint16x4_t*(&X)
#define _simd_reinterpret_f64x2_as_u16x8(X) *reinterpret_cast<const uint16x8_t*(&X)
#define _simd_reinterpret_f64x4_as_u16x16(X) *reinterpret_cast<const uint16x16_t*(&X)
#define _simd_reinterpret_f64x1_as_s8x8(X) *reinterpret_cast<const int8x8_t*(&X)
#define _simd_reinterpret_f64x2_as_s8x16(X) *reinterpret_cast<const int8x16_t*(&X)
#define _simd_reinterpret_f64x4_as_s8x32(X) *reinterpret_cast<const int8x32_t*(&X)
#define _simd_reinterpret_f64x1_as_u8x8(X) *reinterpret_cast<const uint8x8_t*(&X)
#define _simd_reinterpret_f64x2_as_u8x16(X) *reinterpret_cast<const uint8x16_t*(&X)
#define _simd_reinterpret_f64x4_as_u8x32(X) *reinterpret_cast<const uint8x32_t*(&X)
#define _simd_reinterpret_f32x1_as_s32x1(X) *reinterpret_cast<const int32x1_t*(&X)
#define _simd_reinterpret_f32x1_as_u32x1(X) *reinterpret_cast<const uint32x1_t*(&X)
#define _simd_reinterpret_f32x2_as_f64x1(X) *reinterpret_cast<const float64x1_t*(&X)
#define _simd_reinterpret_f32x4_as_f64x2(X) *reinterpret_cast<const float64x2_t*(&X)
#define _simd_reinterpret_f32x8_as_f64x4(X) *reinterpret_cast<const float64x4_t*(&X)
#define _simd_reinterpret_f32x2_as_s64x1(X) *reinterpret_cast<const int64x1_t*(&X)
#define _simd_reinterpret_f32x4_as_s64x2(X) *reinterpret_cast<const int64x2_t*(&X)
#define _simd_reinterpret_f32x8_as_s64x4(X) *reinterpret_cast<const int64x4_t*(&X)
#define _simd_reinterpret_f32x2_as_u64x1(X) *reinterpret_cast<const uint64x1_t*(&X)
#define _simd_reinterpret_f32x4_as_u64x2(X) *reinterpret_cast<const uint64x2_t*(&X)
#define _simd_reinterpret_f32x8_as_u64x4(X) *reinterpret_cast<const uint64x4_t*(&X)
#define _simd_reinterpret_f32x2_as_s32x2(X) *reinterpret_cast<const int32x2_t*(&X)
#define _simd_reinterpret_f32x4_as_s32x4(X) *reinterpret_cast<const int32x4_t*(&X)
#define _simd_reinterpret_f32x8_as_s32x8(X) *reinterpret_cast<const int32x8_t*(&X)
#define _simd_reinterpret_f32x2_as_u32x2(X) *reinterpret_cast<const uint32x2_t*(&X)
#define _simd_reinterpret_f32x4_as_u32x4(X) *reinterpret_cast<const uint32x4_t*(&X)
#define _simd_reinterpret_f32x8_as_u32x8(X) *reinterpret_cast<const uint32x8_t*(&X)
#define _simd_reinterpret_f32x2_as_s16x4(X) *reinterpret_cast<const int16x4_t*(&X)
#define _simd_reinterpret_f32x4_as_s16x8(X) *reinterpret_cast<const int16x8_t*(&X)
#define _simd_reinterpret_f32x8_as_s16x16(X) *reinterpret_cast<const int16x16_t*(&X)
#define _simd_reinterpret_f32x2_as_u16x4(X) *reinterpret_cast<const uint16x4_t*(&X)
#define _simd_reinterpret_f32x4_as_u16x8(X) *reinterpret_cast<const uint16x8_t*(&X)
#define _simd_reinterpret_f32x8_as_u16x16(X) *reinterpret_cast<const uint16x16_t*(&X)
#define _simd_reinterpret_f32x2_as_s8x8(X) *reinterpret_cast<const int8x8_t*(&X)
#define _simd_reinterpret_f32x4_as_s8x16(X) *reinterpret_cast<const int8x16_t*(&X)
#define _simd_reinterpret_f32x8_as_s8x32(X) *reinterpret_cast<const int8x32_t*(&X)
#define _simd_reinterpret_f32x2_as_u8x8(X) *reinterpret_cast<const uint8x8_t*(&X)
#define _simd_reinterpret_f32x4_as_u8x16(X) *reinterpret_cast<const uint8x16_t*(&X)
#define _simd_reinterpret_f32x8_as_u8x32(X) *reinterpret_cast<const uint8x32_t*(&X)
#define _simd_reinterpret_s64x1_as_f64x1(X) *reinterpret_cast<const float64x1_t*(&X)
#define _simd_reinterpret_s64x1_as_u64x1(X) *reinterpret_cast<const uint64x1_t*(&X)
#define _simd_reinterpret_s64x1_as_f64x1(X) *reinterpret_cast<const float64x1_t*(&X)
#define _simd_reinterpret_s64x2_as_f64x2(X) *reinterpret_cast<const float64x2_t*(&X)
#define _simd_reinterpret_s64x4_as_f64x4(X) *reinterpret_cast<const float64x4_t*(&X)
#define _simd_reinterpret_s64x1_as_f32x2(X) *reinterpret_cast<const float32x2_t*(&X)
#define _simd_reinterpret_s64x2_as_f32x4(X) *reinterpret_cast<const float32x4_t*(&X)
#define _simd_reinterpret_s64x4_as_f32x8(X) *reinterpret_cast<const float32x8_t*(&X)
#define _simd_reinterpret_s64x1_as_u64x1(X) *reinterpret_cast<const uint64x1_t*(&X)
#define _simd_reinterpret_s64x2_as_u64x2(X) *reinterpret_cast<const uint64x2_t*(&X)
#define _simd_reinterpret_s64x4_as_u64x4(X) *reinterpret_cast<const uint64x4_t*(&X)
#define _simd_reinterpret_s64x1_as_s32x2(X) *reinterpret_cast<const int32x2_t*(&X)
#define _simd_reinterpret_s64x2_as_s32x4(X) *reinterpret_cast<const int32x4_t*(&X)
#define _simd_reinterpret_s64x4_as_s32x8(X) *reinterpret_cast<const int32x8_t*(&X)
#define _simd_reinterpret_s64x1_as_u32x2(X) *reinterpret_cast<const uint32x2_t*(&X)
#define _simd_reinterpret_s64x2_as_u32x4(X) *reinterpret_cast<const uint32x4_t*(&X)
#define _simd_reinterpret_s64x4_as_u32x8(X) *reinterpret_cast<const uint32x8_t*(&X)
#define _simd_reinterpret_s64x1_as_s16x4(X) *reinterpret_cast<const int16x4_t*(&X)
#define _simd_reinterpret_s64x2_as_s16x8(X) *reinterpret_cast<const int16x8_t*(&X)
#define _simd_reinterpret_s64x4_as_s16x16(X) *reinterpret_cast<const int16x16_t*(&X)
#define _simd_reinterpret_s64x1_as_u16x4(X) *reinterpret_cast<const uint16x4_t*(&X)
#define _simd_reinterpret_s64x2_as_u16x8(X) *reinterpret_cast<const uint16x8_t*(&X)
#define _simd_reinterpret_s64x4_as_u16x16(X) *reinterpret_cast<const uint16x16_t*(&X)
#define _simd_reinterpret_s64x1_as_s8x8(X) *reinterpret_cast<const int8x8_t*(&X)
#define _simd_reinterpret_s64x2_as_s8x16(X) *reinterpret_cast<const int8x16_t*(&X)
#define _simd_reinterpret_s64x4_as_s8x32(X) *reinterpret_cast<const int8x32_t*(&X)
#define _simd_reinterpret_s64x1_as_u8x8(X) *reinterpret_cast<const uint8x8_t*(&X)
#define _simd_reinterpret_s64x2_as_u8x16(X) *reinterpret_cast<const uint8x16_t*(&X)
#define _simd_reinterpret_s64x4_as_u8x32(X) *reinterpret_cast<const uint8x32_t*(&X)
#define _simd_reinterpret_u64x1_as_f64x1(X) *reinterpret_cast<const float64x1_t*(&X)
#define _simd_reinterpret_u64x1_as_s64x1(X) *reinterpret_cast<const int64x1_t*(&X)
#define _simd_reinterpret_u64x1_as_f64x1(X) *reinterpret_cast<const float64x1_t*(&X)
#define _simd_reinterpret_u64x2_as_f64x2(X) *reinterpret_cast<const float64x2_t*(&X)
#define _simd_reinterpret_u64x4_as_f64x4(X) *reinterpret_cast<const float64x4_t*(&X)
#define _simd_reinterpret_u64x1_as_f32x2(X) *reinterpret_cast<const float32x2_t*(&X)
#define _simd_reinterpret_u64x2_as_f32x4(X) *reinterpret_cast<const float32x4_t*(&X)
#define _simd_reinterpret_u64x4_as_f32x8(X) *reinterpret_cast<const float32x8_t*(&X)
#define _simd_reinterpret_u64x1_as_s64x1(X) *reinterpret_cast<const int64x1_t*(&X)
#define _simd_reinterpret_u64x2_as_s64x2(X) *reinterpret_cast<const int64x2_t*(&X)
#define _simd_reinterpret_u64x4_as_s64x4(X) *reinterpret_cast<const int64x4_t*(&X)
#define _simd_reinterpret_u64x1_as_s32x2(X) *reinterpret_cast<const int32x2_t*(&X)
#define _simd_reinterpret_u64x2_as_s32x4(X) *reinterpret_cast<const int32x4_t*(&X)
#define _simd_reinterpret_u64x4_as_s32x8(X) *reinterpret_cast<const int32x8_t*(&X)
#define _simd_reinterpret_u64x1_as_u32x2(X) *reinterpret_cast<const uint32x2_t*(&X)
#define _simd_reinterpret_u64x2_as_u32x4(X) *reinterpret_cast<const uint32x4_t*(&X)
#define _simd_reinterpret_u64x4_as_u32x8(X) *reinterpret_cast<const uint32x8_t*(&X)
#define _simd_reinterpret_u64x1_as_s16x4(X) *reinterpret_cast<const int16x4_t*(&X)
#define _simd_reinterpret_u64x2_as_s16x8(X) *reinterpret_cast<const int16x8_t*(&X)
#define _simd_reinterpret_u64x4_as_s16x16(X) *reinterpret_cast<const int16x16_t*(&X)
#define _simd_reinterpret_u64x1_as_u16x4(X) *reinterpret_cast<const uint16x4_t*(&X)
#define _simd_reinterpret_u64x2_as_u16x8(X) *reinterpret_cast<const uint16x8_t*(&X)
#define _simd_reinterpret_u64x4_as_u16x16(X) *reinterpret_cast<const uint16x16_t*(&X)
#define _simd_reinterpret_u64x1_as_s8x8(X) *reinterpret_cast<const int8x8_t*(&X)
#define _simd_reinterpret_u64x2_as_s8x16(X) *reinterpret_cast<const int8x16_t*(&X)
#define _simd_reinterpret_u64x4_as_s8x32(X) *reinterpret_cast<const int8x32_t*(&X)
#define _simd_reinterpret_u64x1_as_u8x8(X) *reinterpret_cast<const uint8x8_t*(&X)
#define _simd_reinterpret_u64x2_as_u8x16(X) *reinterpret_cast<const uint8x16_t*(&X)
#define _simd_reinterpret_u64x4_as_u8x32(X) *reinterpret_cast<const uint8x32_t*(&X)
#define _simd_reinterpret_s32x1_as_f32x1(X) *reinterpret_cast<const float32x1_t*(&X)
#define _simd_reinterpret_s32x1_as_u32x1(X) *reinterpret_cast<const uint32x1_t*(&X)
#define _simd_reinterpret_s32x2_as_f64x1(X) *reinterpret_cast<const float64x1_t*(&X)
#define _simd_reinterpret_s32x4_as_f64x2(X) *reinterpret_cast<const float64x2_t*(&X)
#define _simd_reinterpret_s32x8_as_f64x4(X) *reinterpret_cast<const float64x4_t*(&X)
#define _simd_reinterpret_s32x2_as_f32x2(X) *reinterpret_cast<const float32x2_t*(&X)
#define _simd_reinterpret_s32x4_as_f32x4(X) *reinterpret_cast<const float32x4_t*(&X)
#define _simd_reinterpret_s32x8_as_f32x8(X) *reinterpret_cast<const float32x8_t*(&X)
#define _simd_reinterpret_s32x2_as_s64x1(X) *reinterpret_cast<const int64x1_t*(&X)
#define _simd_reinterpret_s32x4_as_s64x2(X) *reinterpret_cast<const int64x2_t*(&X)
#define _simd_reinterpret_s32x8_as_s64x4(X) *reinterpret_cast<const int64x4_t*(&X)
#define _simd_reinterpret_s32x2_as_u64x1(X) *reinterpret_cast<const uint64x1_t*(&X)
#define _simd_reinterpret_s32x4_as_u64x2(X) *reinterpret_cast<const uint64x2_t*(&X)
#define _simd_reinterpret_s32x8_as_u64x4(X) *reinterpret_cast<const uint64x4_t*(&X)
#define _simd_reinterpret_s32x2_as_u32x2(X) *reinterpret_cast<const uint32x2_t*(&X)
#define _simd_reinterpret_s32x4_as_u32x4(X) *reinterpret_cast<const uint32x4_t*(&X)
#define _simd_reinterpret_s32x8_as_u32x8(X) *reinterpret_cast<const uint32x8_t*(&X)
#define _simd_reinterpret_s32x2_as_s16x4(X) *reinterpret_cast<const int16x4_t*(&X)
#define _simd_reinterpret_s32x4_as_s16x8(X) *reinterpret_cast<const int16x8_t*(&X)
#define _simd_reinterpret_s32x8_as_s16x16(X) *reinterpret_cast<const int16x16_t*(&X)
#define _simd_reinterpret_s32x2_as_u16x4(X) *reinterpret_cast<const uint16x4_t*(&X)
#define _simd_reinterpret_s32x4_as_u16x8(X) *reinterpret_cast<const uint16x8_t*(&X)
#define _simd_reinterpret_s32x8_as_u16x16(X) *reinterpret_cast<const uint16x16_t*(&X)
#define _simd_reinterpret_s32x2_as_s8x8(X) *reinterpret_cast<const int8x8_t*(&X)
#define _simd_reinterpret_s32x4_as_s8x16(X) *reinterpret_cast<const int8x16_t*(&X)
#define _simd_reinterpret_s32x8_as_s8x32(X) *reinterpret_cast<const int8x32_t*(&X)
#define _simd_reinterpret_s32x2_as_u8x8(X) *reinterpret_cast<const uint8x8_t*(&X)
#define _simd_reinterpret_s32x4_as_u8x16(X) *reinterpret_cast<const uint8x16_t*(&X)
#define _simd_reinterpret_s32x8_as_u8x32(X) *reinterpret_cast<const uint8x32_t*(&X)
#define _simd_reinterpret_u32x1_as_f32x1(X) *reinterpret_cast<const float32x1_t*(&X)
#define _simd_reinterpret_u32x1_as_s32x1(X) *reinterpret_cast<const int32x1_t*(&X)
#define _simd_reinterpret_u32x2_as_f64x1(X) *reinterpret_cast<const float64x1_t*(&X)
#define _simd_reinterpret_u32x4_as_f64x2(X) *reinterpret_cast<const float64x2_t*(&X)
#define _simd_reinterpret_u32x8_as_f64x4(X) *reinterpret_cast<const float64x4_t*(&X)
#define _simd_reinterpret_u32x2_as_f32x2(X) *reinterpret_cast<const float32x2_t*(&X)
#define _simd_reinterpret_u32x4_as_f32x4(X) *reinterpret_cast<const float32x4_t*(&X)
#define _simd_reinterpret_u32x8_as_f32x8(X) *reinterpret_cast<const float32x8_t*(&X)
#define _simd_reinterpret_u32x2_as_s64x1(X) *reinterpret_cast<const int64x1_t*(&X)
#define _simd_reinterpret_u32x4_as_s64x2(X) *reinterpret_cast<const int64x2_t*(&X)
#define _simd_reinterpret_u32x8_as_s64x4(X) *reinterpret_cast<const int64x4_t*(&X)
#define _simd_reinterpret_u32x2_as_u64x1(X) *reinterpret_cast<const uint64x1_t*(&X)
#define _simd_reinterpret_u32x4_as_u64x2(X) *reinterpret_cast<const uint64x2_t*(&X)
#define _simd_reinterpret_u32x8_as_u64x4(X) *reinterpret_cast<const uint64x4_t*(&X)
#define _simd_reinterpret_u32x2_as_s32x2(X) *reinterpret_cast<const int32x2_t*(&X)
#define _simd_reinterpret_u32x4_as_s32x4(X) *reinterpret_cast<const int32x4_t*(&X)
#define _simd_reinterpret_u32x8_as_s32x8(X) *reinterpret_cast<const int32x8_t*(&X)
#define _simd_reinterpret_u32x2_as_s16x4(X) *reinterpret_cast<const int16x4_t*(&X)
#define _simd_reinterpret_u32x4_as_s16x8(X) *reinterpret_cast<const int16x8_t*(&X)
#define _simd_reinterpret_u32x8_as_s16x16(X) *reinterpret_cast<const int16x16_t*(&X)
#define _simd_reinterpret_u32x2_as_u16x4(X) *reinterpret_cast<const uint16x4_t*(&X)
#define _simd_reinterpret_u32x4_as_u16x8(X) *reinterpret_cast<const uint16x8_t*(&X)
#define _simd_reinterpret_u32x8_as_u16x16(X) *reinterpret_cast<const uint16x16_t*(&X)
#define _simd_reinterpret_u32x2_as_s8x8(X) *reinterpret_cast<const int8x8_t*(&X)
#define _simd_reinterpret_u32x4_as_s8x16(X) *reinterpret_cast<const int8x16_t*(&X)
#define _simd_reinterpret_u32x8_as_s8x32(X) *reinterpret_cast<const int8x32_t*(&X)
#define _simd_reinterpret_u32x2_as_u8x8(X) *reinterpret_cast<const uint8x8_t*(&X)
#define _simd_reinterpret_u32x4_as_u8x16(X) *reinterpret_cast<const uint8x16_t*(&X)
#define _simd_reinterpret_u32x8_as_u8x32(X) *reinterpret_cast<const uint8x32_t*(&X)
#define _simd_reinterpret_s16x1_as_u16x1(X) *reinterpret_cast<const uint16x1_t*(&X)
#define _simd_reinterpret_s16x4_as_f64x1(X) *reinterpret_cast<const float64x1_t*(&X)
#define _simd_reinterpret_s16x8_as_f64x2(X) *reinterpret_cast<const float64x2_t*(&X)
#define _simd_reinterpret_s16x16_as_f64x4(X) *reinterpret_cast<const float64x4_t*(&X)
#define _simd_reinterpret_s16x4_as_f32x2(X) *reinterpret_cast<const float32x2_t*(&X)
#define _simd_reinterpret_s16x8_as_f32x4(X) *reinterpret_cast<const float32x4_t*(&X)
#define _simd_reinterpret_s16x16_as_f32x8(X) *reinterpret_cast<const float32x8_t*(&X)
#define _simd_reinterpret_s16x4_as_s64x1(X) *reinterpret_cast<const int64x1_t*(&X)
#define _simd_reinterpret_s16x8_as_s64x2(X) *reinterpret_cast<const int64x2_t*(&X)
#define _simd_reinterpret_s16x16_as_s64x4(X) *reinterpret_cast<const int64x4_t*(&X)
#define _simd_reinterpret_s16x4_as_u64x1(X) *reinterpret_cast<const uint64x1_t*(&X)
#define _simd_reinterpret_s16x8_as_u64x2(X) *reinterpret_cast<const uint64x2_t*(&X)
#define _simd_reinterpret_s16x16_as_u64x4(X) *reinterpret_cast<const uint64x4_t*(&X)
#define _simd_reinterpret_s16x4_as_s32x2(X) *reinterpret_cast<const int32x2_t*(&X)
#define _simd_reinterpret_s16x8_as_s32x4(X) *reinterpret_cast<const int32x4_t*(&X)
#define _simd_reinterpret_s16x16_as_s32x8(X) *reinterpret_cast<const int32x8_t*(&X)
#define _simd_reinterpret_s16x4_as_u32x2(X) *reinterpret_cast<const uint32x2_t*(&X)
#define _simd_reinterpret_s16x8_as_u32x4(X) *reinterpret_cast<const uint32x4_t*(&X)
#define _simd_reinterpret_s16x16_as_u32x8(X) *reinterpret_cast<const uint32x8_t*(&X)
#define _simd_reinterpret_s16x4_as_u16x4(X) *reinterpret_cast<const uint16x4_t*(&X)
#define _simd_reinterpret_s16x8_as_u16x8(X) *reinterpret_cast<const uint16x8_t*(&X)
#define _simd_reinterpret_s16x16_as_u16x16(X) *reinterpret_cast<const uint16x16_t*(&X)
#define _simd_reinterpret_s16x4_as_s8x8(X) *reinterpret_cast<const int8x8_t*(&X)
#define _simd_reinterpret_s16x8_as_s8x16(X) *reinterpret_cast<const int8x16_t*(&X)
#define _simd_reinterpret_s16x16_as_s8x32(X) *reinterpret_cast<const int8x32_t*(&X)
#define _simd_reinterpret_s16x4_as_u8x8(X) *reinterpret_cast<const uint8x8_t*(&X)
#define _simd_reinterpret_s16x8_as_u8x16(X) *reinterpret_cast<const uint8x16_t*(&X)
#define _simd_reinterpret_s16x16_as_u8x32(X) *reinterpret_cast<const uint8x32_t*(&X)
#define _simd_reinterpret_u16x1_as_s16x1(X) *reinterpret_cast<const int16x1_t*(&X)
#define _simd_reinterpret_u16x4_as_f64x1(X) *reinterpret_cast<const float64x1_t*(&X)
#define _simd_reinterpret_u16x8_as_f64x2(X) *reinterpret_cast<const float64x2_t*(&X)
#define _simd_reinterpret_u16x16_as_f64x4(X) *reinterpret_cast<const float64x4_t*(&X)
#define _simd_reinterpret_u16x4_as_f32x2(X) *reinterpret_cast<const float32x2_t*(&X)
#define _simd_reinterpret_u16x8_as_f32x4(X) *reinterpret_cast<const float32x4_t*(&X)
#define _simd_reinterpret_u16x16_as_f32x8(X) *reinterpret_cast<const float32x8_t*(&X)
#define _simd_reinterpret_u16x4_as_s64x1(X) *reinterpret_cast<const int64x1_t*(&X)
#define _simd_reinterpret_u16x8_as_s64x2(X) *reinterpret_cast<const int64x2_t*(&X)
#define _simd_reinterpret_u16x16_as_s64x4(X) *reinterpret_cast<const int64x4_t*(&X)
#define _simd_reinterpret_u16x4_as_u64x1(X) *reinterpret_cast<const uint64x1_t*(&X)
#define _simd_reinterpret_u16x8_as_u64x2(X) *reinterpret_cast<const uint64x2_t*(&X)
#define _simd_reinterpret_u16x16_as_u64x4(X) *reinterpret_cast<const uint64x4_t*(&X)
#define _simd_reinterpret_u16x4_as_s32x2(X) *reinterpret_cast<const int32x2_t*(&X)
#define _simd_reinterpret_u16x8_as_s32x4(X) *reinterpret_cast<const int32x4_t*(&X)
#define _simd_reinterpret_u16x16_as_s32x8(X) *reinterpret_cast<const int32x8_t*(&X)
#define _simd_reinterpret_u16x4_as_u32x2(X) *reinterpret_cast<const uint32x2_t*(&X)
#define _simd_reinterpret_u16x8_as_u32x4(X) *reinterpret_cast<const uint32x4_t*(&X)
#define _simd_reinterpret_u16x16_as_u32x8(X) *reinterpret_cast<const uint32x8_t*(&X)
#define _simd_reinterpret_u16x4_as_s16x4(X) *reinterpret_cast<const int16x4_t*(&X)
#define _simd_reinterpret_u16x8_as_s16x8(X) *reinterpret_cast<const int16x8_t*(&X)
#define _simd_reinterpret_u16x16_as_s16x16(X) *reinterpret_cast<const int16x16_t*(&X)
#define _simd_reinterpret_u16x4_as_s8x8(X) *reinterpret_cast<const int8x8_t*(&X)
#define _simd_reinterpret_u16x8_as_s8x16(X) *reinterpret_cast<const int8x16_t*(&X)
#define _simd_reinterpret_u16x16_as_s8x32(X) *reinterpret_cast<const int8x32_t*(&X)
#define _simd_reinterpret_u16x4_as_u8x8(X) *reinterpret_cast<const uint8x8_t*(&X)
#define _simd_reinterpret_u16x8_as_u8x16(X) *reinterpret_cast<const uint8x16_t*(&X)
#define _simd_reinterpret_u16x16_as_u8x32(X) *reinterpret_cast<const uint8x32_t*(&X)
#define _simd_reinterpret_s8x1_as_u8x1(X) *reinterpret_cast<const uint8x1_t*(&X)
#define _simd_reinterpret_s8x8_as_f64x1(X) *reinterpret_cast<const float64x1_t*(&X)
#define _simd_reinterpret_s8x16_as_f64x2(X) *reinterpret_cast<const float64x2_t*(&X)
#define _simd_reinterpret_s8x32_as_f64x4(X) *reinterpret_cast<const float64x4_t*(&X)
#define _simd_reinterpret_s8x8_as_f32x2(X) *reinterpret_cast<const float32x2_t*(&X)
#define _simd_reinterpret_s8x16_as_f32x4(X) *reinterpret_cast<const float32x4_t*(&X)
#define _simd_reinterpret_s8x32_as_f32x8(X) *reinterpret_cast<const float32x8_t*(&X)
#define _simd_reinterpret_s8x8_as_s64x1(X) *reinterpret_cast<const int64x1_t*(&X)
#define _simd_reinterpret_s8x16_as_s64x2(X) *reinterpret_cast<const int64x2_t*(&X)
#define _simd_reinterpret_s8x32_as_s64x4(X) *reinterpret_cast<const int64x4_t*(&X)
#define _simd_reinterpret_s8x8_as_u64x1(X) *reinterpret_cast<const uint64x1_t*(&X)
#define _simd_reinterpret_s8x16_as_u64x2(X) *reinterpret_cast<const uint64x2_t*(&X)
#define _simd_reinterpret_s8x32_as_u64x4(X) *reinterpret_cast<const uint64x4_t*(&X)
#define _simd_reinterpret_s8x8_as_s32x2(X) *reinterpret_cast<const int32x2_t*(&X)
#define _simd_reinterpret_s8x16_as_s32x4(X) *reinterpret_cast<const int32x4_t*(&X)
#define _simd_reinterpret_s8x32_as_s32x8(X) *reinterpret_cast<const int32x8_t*(&X)
#define _simd_reinterpret_s8x8_as_u32x2(X) *reinterpret_cast<const uint32x2_t*(&X)
#define _simd_reinterpret_s8x16_as_u32x4(X) *reinterpret_cast<const uint32x4_t*(&X)
#define _simd_reinterpret_s8x32_as_u32x8(X) *reinterpret_cast<const uint32x8_t*(&X)
#define _simd_reinterpret_s8x8_as_s16x4(X) *reinterpret_cast<const int16x4_t*(&X)
#define _simd_reinterpret_s8x16_as_s16x8(X) *reinterpret_cast<const int16x8_t*(&X)
#define _simd_reinterpret_s8x32_as_s16x16(X) *reinterpret_cast<const int16x16_t*(&X)
#define _simd_reinterpret_s8x8_as_u16x4(X) *reinterpret_cast<const uint16x4_t*(&X)
#define _simd_reinterpret_s8x16_as_u16x8(X) *reinterpret_cast<const uint16x8_t*(&X)
#define _simd_reinterpret_s8x32_as_u16x16(X) *reinterpret_cast<const uint16x16_t*(&X)
#define _simd_reinterpret_s8x8_as_u8x8(X) *reinterpret_cast<const uint8x8_t*(&X)
#define _simd_reinterpret_s8x16_as_u8x16(X) *reinterpret_cast<const uint8x16_t*(&X)
#define _simd_reinterpret_s8x32_as_u8x32(X) *reinterpret_cast<const uint8x32_t*(&X)
#define _simd_reinterpret_u8x1_as_s8x1(X) *reinterpret_cast<const int8x1_t*(&X)
#define _simd_reinterpret_u8x8_as_f64x1(X) *reinterpret_cast<const float64x1_t*(&X)
#define _simd_reinterpret_u8x16_as_f64x2(X) *reinterpret_cast<const float64x2_t*(&X)
#define _simd_reinterpret_u8x32_as_f64x4(X) *reinterpret_cast<const float64x4_t*(&X)
#define _simd_reinterpret_u8x8_as_f32x2(X) *reinterpret_cast<const float32x2_t*(&X)
#define _simd_reinterpret_u8x16_as_f32x4(X) *reinterpret_cast<const float32x4_t*(&X)
#define _simd_reinterpret_u8x32_as_f32x8(X) *reinterpret_cast<const float32x8_t*(&X)
#define _simd_reinterpret_u8x8_as_s64x1(X) *reinterpret_cast<const int64x1_t*(&X)
#define _simd_reinterpret_u8x16_as_s64x2(X) *reinterpret_cast<const int64x2_t*(&X)
#define _simd_reinterpret_u8x32_as_s64x4(X) *reinterpret_cast<const int64x4_t*(&X)
#define _simd_reinterpret_u8x8_as_u64x1(X) *reinterpret_cast<const uint64x1_t*(&X)
#define _simd_reinterpret_u8x16_as_u64x2(X) *reinterpret_cast<const uint64x2_t*(&X)
#define _simd_reinterpret_u8x32_as_u64x4(X) *reinterpret_cast<const uint64x4_t*(&X)
#define _simd_reinterpret_u8x8_as_s32x2(X) *reinterpret_cast<const int32x2_t*(&X)
#define _simd_reinterpret_u8x16_as_s32x4(X) *reinterpret_cast<const int32x4_t*(&X)
#define _simd_reinterpret_u8x32_as_s32x8(X) *reinterpret_cast<const int32x8_t*(&X)
#define _simd_reinterpret_u8x8_as_u32x2(X) *reinterpret_cast<const uint32x2_t*(&X)
#define _simd_reinterpret_u8x16_as_u32x4(X) *reinterpret_cast<const uint32x4_t*(&X)
#define _simd_reinterpret_u8x32_as_u32x8(X) *reinterpret_cast<const uint32x8_t*(&X)
#define _simd_reinterpret_u8x8_as_s16x4(X) *reinterpret_cast<const int16x4_t*(&X)
#define _simd_reinterpret_u8x16_as_s16x8(X) *reinterpret_cast<const int16x8_t*(&X)
#define _simd_reinterpret_u8x32_as_s16x16(X) *reinterpret_cast<const int16x16_t*(&X)
#define _simd_reinterpret_u8x8_as_u16x4(X) *reinterpret_cast<const uint16x4_t*(&X)
#define _simd_reinterpret_u8x16_as_u16x8(X) *reinterpret_cast<const uint16x8_t*(&X)
#define _simd_reinterpret_u8x32_as_u16x16(X) *reinterpret_cast<const uint16x16_t*(&X)
#define _simd_reinterpret_u8x8_as_s8x8(X) *reinterpret_cast<const int8x8_t*(&X)
#define _simd_reinterpret_u8x16_as_s8x16(X) *reinterpret_cast<const int8x16_t*(&X)
#define _simd_reinterpret_u8x32_as_s8x32(X) *reinterpret_cast<const int8x32_t*(&X)


// Not

#define _simd_not_f64x1(X) _simd_reinterpret_s64x1_as_f64x1(~(_simd_reinterpret_f64x1_as_s64x1(X)))
#define _simd_not_f64x2(X) _mm_xor_pd(X, _mm_cmpeq_pd(X,X))
#define _simd_not_f64x4(X) _mm256_xor_pd(X, _mm256_cmpeq_pd(X,X))

#define _simd_not_f32x1(X) _simd_reinterpret_s32x1_as_f32x1(~(_simd_reinterpret_f32x1_as_s32x1(X)))
#define _simd_not_f32x2(X) _simd_not_f32x4(X)
#define _simd_not_f32x4(X) _mm_xor_ps(X, _mm_cmpeq_ps(X,X))
#define _simd_not_f32x8(X) _mm256_xor_ps(X, _mm256_cmpeq_ps(X,X))

//#define _simd_not_s64x1(X) (~X)
//#define _simd_not_s64x2(X) _mm_xor_si128(X, _mm_cmpeq_ps(X,X))
//#define _simd_not_s64x4(X) _mm256_andnot_si256(X, _mm256_set1_epi32(~0i32))
//
//#define _simd_not_u64x1(X) (~X)
//#define _simd_not_u64x2(X) _simd_not_s64x2(X)
//#define _simd_not_u64x4(X) _simd_not_s64x4(X)

#define _simd_not_s32x1(X) (~X)
#define _simd_not_s32x2(X) _simd_not_s32x4(X)
#define _simd_not_s32x4(X) _mm_xor_si128(X, _mm_cmpeq_epi32(X,X))
#define _simd_not_s32x8(X) _mm256_xor_si256(X, _mm256_cmpeq_epi32(X,X))

#define _simd_not_u32x1(X) (~X)
#define _simd_not_u32x2(X) _simd_not_u32x4(X)
#define _simd_not_u32x4(X) _simd_not_s32x4(X)
#define _simd_not_u32x8(X) _simd_not_s32x8(X)

#define _simd_not_s16x1(X) (~X)
#define _simd_not_16x4(X) _simd_not_16x8(X)
#define _simd_not_16x8(X) _mm_xor_si128(X, _mm_cmpeq_epi16(X,X))
#define _simd_not_16x16(X) _mm256_xor_si256(X, _mm256_cmpeq_epi16(X,X))

#define _simd_not_u16x1(X) (~X)
#define _simd_not_u16x4(X) _simd_not_u16x8(X)
#define _simd_not_u16x8(X) _simd_not_16x8(X)
#define _simd_not_u16x16(X) _simd_not_16x16(X)

#define _simd_not_sx1(X) (~X)
#define _simd_not_s8x8(X) _simd_not_s8x16(X)
#define _simd_not_s8x16(X) _mm_xor_si128(X, _mm_cmpeq_epi8(X,X))
#define _simd_not_s8x32(X) _mm256_xor_si256(X, _mm256_cmpeq_epi8(X,X))

#define _simd_not_u8x1(X) (~X)
#define _simd_not_u8x8(X) _simd_not_u8x16(X)
#define _simd_not_u8x16(X) _simd_not_s8x16(X)
#define _simd_not_u8x32(X) _simd_not_s8x32(X)

// Add

#define _simd_add_f64x1(X,Y) (X + Y)
#define _simd_add_f64x2(X,Y) _mm_add_pd(X,Y)
#define _simd_add_f64x4(X,Y) _mm256_add_pd(X,Y)

#define _simd_add_f32x1(X,Y) (X + Y)
#define _simd_add_f32x2(X,Y) _simd_add_f32x4(X + Y)
#define _simd_add_f32x4(X,Y) _mm_add_ps(X,Y)
#define _simd_add_f32x8(X,Y) _mm256_add_ps(X,Y)

#define _simd_add_s64x1(X,Y) (X + Y)
#define _simd_add_s64x2(X,Y) _mm_add_epi64(X,Y)
#define _simd_add_s64x4(X,Y) _mm256_add_epi64(X,Y)

#define _simd_add_u64x1(X,Y) (X + Y)
#define _simd_add_u64x2(X,Y) _mm_add_epi64(X,Y)
#define _simd_add_u64x4(X,Y) _mm256_add_epi64(X,Y)

#define _simd_add_s32x1(X,Y) (X + Y)
#define _simd_add_s32x2(X,Y) _simd_add_s32x4(X + Y)
#define _simd_add_s32x4(X,Y) _mm_add_epi32(X,Y)
#define _simd_add_s32x8(X,Y) _mm256_add_epi32(X,Y)

#define _simd_add_u32x1(X,Y) (X + Y)
#define _simd_add_u32x2(X,Y) _simd_add_u32x4(X + Y)
#define _simd_add_u32x4(X,Y) _mm_add_epi32(X,Y)
#define _simd_add_u32x8(X,Y) _mm256_add_epi32(X,Y)

#define _simd_add_s16x1(X,Y) (X + Y)
#define _simd_add_s16x4(X,Y) _simd_add_s16x8(X + Y)
#define _simd_add_s16x8(X,Y) _mm_add_epi16(X,Y)
#define _simd_add_s16x16(X,Y) _mm256_add_epi16(X,Y)

#define _simd_add_u16x1(X,Y) (X + Y)
#define _simd_add_u16x4(X,Y) _simd_add_u16x8(X + Y)
#define _simd_add_u16x8(X,Y) _mm_add_epi16(X,Y)
#define _simd_add_u16x16(X,Y) _mm256_add_epi16(X,Y)

#define _simd_add_s8x1(X,Y) (X + Y)
#define _simd_add_s8x8(X,Y) _simd_add_s8x16(X + Y)
#define _simd_add_s8x16(X,Y) _mm_add_epi8(X,Y)
#define _simd_add_s8x32(X,Y) _mm256_add_epi8(X,Y)

#define _simd_add_u8x1(X,Y) (X + Y)
#define _simd_add_u8x8(X,Y) _simd_add_u8x16(X + Y)
#define _simd_add_u8x16(X,Y) _mm_add_epi8(X,Y)
#define _simd_add_u8x32(X,Y) _mm256_add_epi8(X,Y)

// Sub

#define _simd_sub_f64x1(X,Y) (X + Y)
#define _simd_sub_f64x2(X,Y) _mm_sub_pd(X,Y)
#define _simd_sub_f64x4(X,Y) _mm256_sub_pd(X,Y)

#define _simd_sub_f32x1(X,Y) (X + Y)
#define _simd_sub_f32x2(X,Y) _simd_sub_f32x4(X + Y)
#define _simd_sub_f32x4(X,Y) _mm_sub_ps(X,Y)
#define _simd_sub_f32x8(X,Y) _mm256_sub_ps(X,Y)

#define _simd_sub_s64x1(X,Y) (X + Y)
#define _simd_sub_s64x2(X,Y) _mm_sub_epi64(X,Y)
#define _simd_sub_s64x4(X,Y) _mm256_sub_epi64(X,Y)

#define _simd_sub_u64x1(X,Y) (X + Y)
#define _simd_sub_u64x2(X,Y) _mm_sub_epi64(X,Y)
#define _simd_sub_u64x4(X,Y) _mm256_sub_epi64(X,Y)

#define _simd_sub_s32x1(X,Y) (X + Y)
#define _simd_sub_s32x2(X,Y) _simd_sub_s32x4(X + Y)
#define _simd_sub_s32x4(X,Y) _mm_sub_epi32(X,Y)
#define _simd_sub_s32x8(X,Y) _mm256_sub_epi32(X,Y)

#define _simd_sub_u32x1(X,Y) (X + Y)
#define _simd_sub_u32x2(X,Y) _simd_sub_u32x4(X + Y)
#define _simd_sub_u32x4(X,Y) _mm_sub_epi32(X,Y)
#define _simd_sub_u32x8(X,Y) _mm256_sub_epi32(X,Y)

#define _simd_sub_s16x1(X,Y) (X + Y)
#define _simd_sub_s16x4(X,Y) _simd_sub_s16x8(X + Y)
#define _simd_sub_s16x8(X,Y) _mm_sub_epi16(X,Y)
#define _simd_sub_s16x16(X,Y) _mm256_sub_epi16(X,Y)

#define _simd_sub_u16x1(X,Y) (X + Y)
#define _simd_sub_u16x4(X,Y) _simd_sub_u16x8(X + Y)
#define _simd_sub_u16x8(X,Y) _mm_sub_epi16(X,Y)
#define _simd_sub_u16x16(X,Y) _mm256_sub_epi16(X,Y)

#define _simd_sub_s8x1(X,Y) (X + Y)
#define _simd_sub_s8x8(X,Y) _simd_sub_s8x16(X + Y)
#define _simd_sub_s8x16(X,Y) _mm_sub_epi8(X,Y)
#define _simd_sub_s8x32(X,Y) _mm256_sub_epi8(X,Y)

#define _simd_sub_u8x1(X,Y) (X + Y)
#define _simd_sub_u8x8(X,Y) _simd_sub_u8x16(X + Y)
#define _simd_sub_u8x16(X,Y) _mm_sub_epi8(X,Y)
#define _simd_sub_u8x32(X,Y) _mm256_sub_epi8(X,Y)

// Multiply

static ANVIL_STRONG_INLINE int8x16_t ANVIL_SIMD_CALL _simd_mul_s8x16(const register int8x16_t x, const register int8x16_t y) {
	const register __m128i dst_even = _mm_mullo_epi16(x, y);
	const register __m128i dst_odd = _mm_mullo_epi16(_mm_srli_epi16(x, 8),_mm_srli_epi16(y, 8));
	return _mm_or_si128(_mm_slli_epi16(dst_odd, 8), _mm_srli_epi16(_mm_slli_epi16(dst_even,8), 8));
}

// Sum

static ANVIL_STRONG_INLINE int32x1_t ANVIL_SIMD_CALL _simd_sum_s32x4(const register int32x4_t x) {
	const register __m128i tmp = _mm_add_epi32(_mm_unpackhi_epi32(x, x), _mm_unpacklo_epi32(x, x));
	int32x1_t buffer[2];
	_mm_storel_epi64(reinterpret_cast<__m128i*>(buffer), tmp);
	return buffer[0] + buffer[1];
}

#define _simd_sum_s8x16(X) _simd_sum_s32x4(_mm_madd_epi16(X, _mm_set1_epi16(1)))

#else
	#include <arm_neon.h>
	#include "anvil/core/Keywords.hpp"

	#define ANVIL_SIMD_CALL ANVIL_CALL

	typedef float32x4_t __m128;
	typedef __m128 __m128d;
	typedef uint32x4_t __m128i;
	struct __m256 {
		__m128 lo;
		__m128 hi;
	};
	typedef __m256 __m256d;
	struct __m256i {
		__m128i lo;
		__m128i hi;
	};
	struct __m512 {
		__m256 lo;
		__m256 hi;
	};
	typedef __m512 __m512d;
	struct __m512i {
		__m256i lo;
		__m256i hi;
	};

	// -- LOAD / STORE -- 

	static ANVIL_STRONG_INLINE __m128d ANVIL_SIMD_CALL _mm_loadu_pd(const double* p) {
		const float buf[4] = { static_cast<float>(p[0]), static_cast<float>(p[1]), 0.f, 0.f };
		return vld1q_f32(buf);
	}
	#define _mm_load_pd(P) _mm_loadu_pd(P)
	#define _mm_loadr_pd(P) vrev64q_f32(_mm_loadu_pd(P)) //! \bug Vector is wrong length for reverse
	#define _mm_loadu_ps(P) vld1q_f32(reinterpret_cast<const float*>(P))
	#define _mm_load_ps(P) _mm_loadu_ps(P)
	#define _mm_loadr_ps(P) vrev64q_f32(_mm_loadu_ps(P))
	#define _mm_loadu_si128(P) vld1q_u32(reinterpret_cast<const uint32_t*>(P))
	#define _mm_load_si128(P) _mm_loadu_si128(P)
	#define _mm_loadr_si128(P) vrev64q_u32(_mm_loadu_si128(P))


	static ANVIL_STRONG_INLINE void _mm_storeu_pd(double* p, const __m128d x) {
		float buf[4];
		vst1q_f32(buf, x);
		p[0] = static_cast<double>(buf[0]);
		p[1] = static_cast<double>(buf[1]);
	}
	#define _mm_store_pd(P,X) _mm_storeu_pd(P,X)
	#define _mm_storer_pd(P,X) _mm_storeu_pd(P,vrev64q_u32(X)) //! \bug Vector is wrong length for reverse
	#define _mm_storeu_ps(P,X) vst1q_f32(reinterpret_cast<float*>(P),X)
	#define _mm_store_ps(P,X) _mm_storeu_ps(P,X)
	#define _mm_storer_ps(P,X) _mm_storeu_ps(P,vrev64q_f32(X))
	#define _mm_storeu_si128(P,X) vst1q_u32(reinterpret_cast<uint32_t*>(P),X)
	#define _mm_store_si128(P,X) _mm_storeu_si128(P,X)
	#define _mm_storer_si128(P,X) _mm_storeu_si128(P,vrev64q_u32(X))

	static ANVIL_STRONG_INLINE __m256d ANVIL_SIMD_CALL _mm256_loadu_pd(const double* const p) {
		__m256d tmp;
		tmp.lo = _mm_loadu_pd(p);
		tmp.hi = _mm_loadu_pd(p + 2);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m256d ANVIL_SIMD_CALL _mm256_loadr_pd(const double* const p) {
		__m256d tmp;
		tmp.hi = _mm_loadr_pd(p);
		tmp.lo = _mm_loadr_pd(p + 2);
		return tmp;
	}
	#define _mm256_load_pd(P) _mm256_loadu_pd(P)
	static ANVIL_STRONG_INLINE void ANVIL_SIMD_CALL _mm256_storeu_pd(double* const p, __m256d x) {
		_mm_storeu_pd(p, x.lo);
		_mm_storeu_pd(p + 2, x.hi);
	}
	static ANVIL_STRONG_INLINE void ANVIL_SIMD_CALL _mm256_storer_pd(double* const p, __m256d x) {
		_mm_storeu_pd(p, x.hi);
		_mm_storeu_pd(p + 2, x.lo);
	}
	#define _mm256_store_pd(P,X) _mm256_storeu_pd(P,X)
	static ANVIL_STRONG_INLINE __m256 ANVIL_SIMD_CALL _mm256_loadu_ps(const float* const p) {
		__m256 tmp;
		tmp.lo = _mm_loadu_ps(p);
		tmp.hi = _mm_loadu_ps(p + 4);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m256 ANVIL_SIMD_CALL _mm256_loadr_ps(const float* const p) {
		__m256 tmp;
		tmp.hi = _mm_loadr_ps(p);
		tmp.lo = _mm_loadr_ps(p + 4);
		return tmp;
	}
	#define _mm256_load_ps(P) _mm256_loadu_ps(P)
	static ANVIL_STRONG_INLINE void ANVIL_SIMD_CALL _mm256_storeu_ps(float* const p, __m256 x) {
		_mm_storeu_ps(p, x.lo);
		_mm_storeu_ps(p + 4, x.hi);
	}
	static ANVIL_STRONG_INLINE void ANVIL_SIMD_CALL _mm256_storer_ps(float* const p, __m256 x) {
		_mm_storeu_ps(p, x.hi);
		_mm_storeu_ps(p + 4, x.lo);
	}
	#define _mm256_store_ps(P,X) _mm256_storeu_ps(P,X)
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_loadu_si256(const uint32_t* const p) {
		__m256i tmp;
		tmp.lo = _mm_loadu_si128(p);
		tmp.hi = _mm_loadu_si128(p + 4);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_loadr_si256(const uint32_t* const p) {
		__m256i tmp;
		tmp.hi = _mm_loadr_si128(p);
		tmp.lo = _mm_loadr_si128(p + 4);
		return tmp;
	}
	#define _mm256_load_si256(P) _mm256_loadu_si256(P)
	static ANVIL_STRONG_INLINE void ANVIL_SIMD_CALL _mm256_storeu_si256(uint32_t* const p, __m256i x) {
		_mm_storeu_si128(p, x.lo);
		_mm_storeu_si128(p + 4, x.hi);
	}
	static ANVIL_STRONG_INLINE void ANVIL_SIMD_CALL _mm256_storer_si256(uint32_t* const p, __m256i x) {
		_mm_storeu_si128(p, x.hi);
		_mm_storeu_si128(p + 4, x.lo);
	}
	#define _mm256_store_si256(P,X) _mm256_storeu_si256(P,X)
	static ANVIL_STRONG_INLINE __m512d ANVIL_SIMD_CALL _mm512_loadu_pd(const double* const p) {
		__m512d tmp;
		tmp.lo = _mm256_loadu_pd(p);
		tmp.hi = _mm256_loadu_pd(p + 4);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512d ANVIL_SIMD_CALL _mm512_loadr_pd(const double* const p) {
		__m512d tmp;
		tmp.hi = _mm256_loadr_pd(p);
		tmp.lo = _mm256_loadr_pd(p + 4);
		return tmp;
	}
	#define _mm512_load_pd(P) _mm512_loadu_pd(P)
	static ANVIL_STRONG_INLINE void ANVIL_SIMD_CALL _mm512_storeu_pd(double* const p, __m512d x) {
		_mm256_storeu_pd(p, x.lo);
		_mm256_storeu_pd(p + 4, x.hi);
	}
	static ANVIL_STRONG_INLINE void ANVIL_SIMD_CALL _mm512_storer_pd(double* const p, __m512d x) {
		_mm256_storeu_pd(p, x.hi);
		_mm256_storeu_pd(p + 4, x.lo);
	}
	#define _mm512_store_pd(P,X) _mm512_storeu_pd(P,X)
	static ANVIL_STRONG_INLINE __m512 ANVIL_SIMD_CALL _mm512_loadu_ps(const float* const p) {
		__m512 tmp;
		tmp.lo = _mm256_loadu_ps(p);
		tmp.hi = _mm256_loadu_ps(p + 8);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512 ANVIL_SIMD_CALL _mm512_loadr_ps(const float* const p) {
		__m512 tmp;
		tmp.hi = _mm256_loadr_ps(p);
		tmp.lo = _mm256_loadr_ps(p + 8);
		return tmp;
	}
	#define _mm512_load_ps(P) _mm512_loadu_ps(P)
	static ANVIL_STRONG_INLINE void ANVIL_SIMD_CALL _mm512_storeu_ps(float* const p, __m512 x) {
		_mm256_storeu_ps(p, x.lo);
		_mm256_storeu_ps(p + 8, x.hi);
	}
	static ANVIL_STRONG_INLINE void ANVIL_SIMD_CALL _mm512_storer_ps(float* const p, __m512 x) {
		_mm256_storeu_ps(p, x.hi);
		_mm256_storeu_ps(p + 8, x.lo);
	}
	#define _mm512_store_ps(P,X) _mm512_storeu_ps(P,X)
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_loadu_si512(const uint32_t* const p) {
		__m512i tmp;
		tmp.lo = _mm256_loadu_si256(p);
		tmp.hi = _mm256_loadu_si256(p + 8);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_loadr_si512(const uint32_t* const p) {
		__m512i tmp;
		tmp.hi = _mm256_loadr_si256(p);
		tmp.lo = _mm256_loadr_si256(p + 8);
		return tmp;
	}
	#define _mm512_load_si512(P) _mm512_loadu_si512(P)
	static ANVIL_STRONG_INLINE void ANVIL_SIMD_CALL _mm512_storeu_si512(uint32_t* const p, __m512i x) {
		_mm256_storeu_si256(p, x.lo);
		_mm256_storeu_si256(p + 8, x.hi);
	}
	static ANVIL_STRONG_INLINE void ANVIL_SIMD_CALL _mm512_storer_si512(uint32_t* const p, __m512i x) {
		_mm256_storeu_si256(p, x.hi);
		_mm256_storeu_si256(p + 8, x.lo);
	}
	#define _mm512_store_si512(P,X) _mm512_storeu_si512(P,X)


	// -- ADD / SUB / MUL / DIV / MIN / MAX --

	#define _mm_add_pd(X, Y) (vaddq_f32(X, Y))
	static ANVIL_STRONG_INLINE __m256d ANVIL_SIMD_CALL _mm256_add_pd(const __m256d x, const __m256d y) {
		__m256d tmp;
		_mm_add_pd(x.lo, y.lo);
		_mm_add_pd(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512d ANVIL_SIMD_CALL _mm512_add_pd(const __m512d x, const __m512d y) {
		__m512d tmp;
		_mm256_add_pd(x.lo, y.lo);
		_mm256_add_pd(x.hi, y.hi);
		return tmp;
	}
	#define _mm_sub_pd(X, Y) (vsubq_f32(X, Y))
	static ANVIL_STRONG_INLINE __m256d ANVIL_SIMD_CALL _mm256_sub_pd(const __m256d x, const __m256d y) {
		__m256d tmp;
		_mm_sub_pd(x.lo, y.lo);
		_mm_sub_pd(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512d ANVIL_SIMD_CALL _mm512_sub_pd(const __m512d x, const __m512d y) {
		__m512d tmp;
		_mm256_sub_pd(x.lo, y.lo);
		_mm256_sub_pd(x.hi, y.hi);
		return tmp;
	}
	#define _mm_mul_pd(X, Y) (vmulq_f32(X, Y))
	static ANVIL_STRONG_INLINE __m256d ANVIL_SIMD_CALL _mm256_mul_pd(const __m256d x, const __m256d y) {
		__m256d tmp;
		_mm_mul_pd(x.lo, y.lo);
		_mm_mul_pd(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512d ANVIL_SIMD_CALL _mm512_mul_pd(const __m512d x, const __m512d y) {
		__m512d tmp;
		_mm256_mul_pd(x.lo, y.lo);
		_mm256_mul_pd(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m128d ANVIL_SIMD_CALL _mm_div_pd(const __m128d x, const __m128d y) {
		double bufA[2];
		double bufB[2];
		_mm_storeu_pd(bufA, x);
		_mm_storeu_pd(bufB, y);
		for (int i = 0; i < 2; ++i) bufA[i] = bufA[i] / bufB[i];
		return _mm_loadu_pd(bufA);
	}
	static ANVIL_STRONG_INLINE __m256d ANVIL_SIMD_CALL _mm256_div_pd(const __m256d x, const __m256d y) {
		__m256d tmp;
		_mm_div_pd(x.lo, y.lo);
		_mm_div_pd(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512d ANVIL_SIMD_CALL _mm512_div_pd(const __m512d x, const __m512d y) {
		__m512d tmp;
		_mm256_div_pd(x.lo, y.lo);
		_mm256_div_pd(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m128d ANVIL_SIMD_CALL _mm_min_pd(const __m128d x, const __m128d y) {
		double bufA[2];
		double bufB[2];
		_mm_storeu_pd(bufA, x);
		_mm_storeu_pd(bufB, y);
		for (int i = 0; i < 2; ++i) bufA[i] = std::min(bufA[i], bufB[i]);;
		return _mm_loadu_pd(bufA);
	}
	static ANVIL_STRONG_INLINE __m256d ANVIL_SIMD_CALL _mm256_min_pd(const __m256d x, const __m256d y) {
		__m256d tmp;
		_mm_min_pd(x.lo, y.lo);
		_mm_min_pd(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512d ANVIL_SIMD_CALL _mm512_min_pd(const __m512d x, const __m512d y) {
		__m512d tmp;
		_mm256_min_pd(x.lo, y.lo);
		_mm256_min_pd(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m128d ANVIL_SIMD_CALL _mm_max_pd(const __m128d x, const __m128d y) {
		double bufA[2];
		double bufB[2];
		_mm_storeu_pd(bufA, x);
		_mm_storeu_pd(bufB, y);
		for (int i = 0; i < 2; ++i) bufA[i] = std::max(bufA[i], bufB[i]);;
		return _mm_loadu_pd(bufA);
	}
	static ANVIL_STRONG_INLINE __m256d ANVIL_SIMD_CALL _mm256_max_pd(const __m256d x, const __m256d y) {
		__m256d tmp;
		_mm_max_pd(x.lo, y.lo);
		_mm_max_pd(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512d ANVIL_SIMD_CALL _mm512_max_pd(const __m512d x, const __m512d y) {
		__m512d tmp;
		_mm256_max_pd(x.lo, y.lo);
		_mm256_max_pd(x.hi, y.hi);
		return tmp;
	}
	#define _mm_add_ps(X, Y) (vaddq_f32(X, Y))
	static ANVIL_STRONG_INLINE __m256 ANVIL_SIMD_CALL _mm256_add_ps(const __m256 x, const __m256 y) {
		__m256 tmp;
		_mm_add_ps(x.lo, y.lo);
		_mm_add_ps(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512 ANVIL_SIMD_CALL _mm512_add_ps(const __m512 x, const __m512 y) {
		__m512 tmp;
		_mm256_add_ps(x.lo, y.lo);
		_mm256_add_ps(x.hi, y.hi);
		return tmp;
	}
	#define _mm_sub_ps(X, Y) (vsubq_f32(X, Y))
	static ANVIL_STRONG_INLINE __m256 ANVIL_SIMD_CALL _mm256_sub_ps(const __m256 x, const __m256 y) {
		__m256 tmp;
		_mm_sub_ps(x.lo, y.lo);
		_mm_sub_ps(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512 ANVIL_SIMD_CALL _mm512_sub_ps(const __m512 x, const __m512 y) {
		__m512 tmp;
		_mm256_sub_ps(x.lo, y.lo);
		_mm256_sub_ps(x.hi, y.hi);
		return tmp;
	}
	#define _mm_mul_ps(X, Y) (vmulq_f32(X, Y))
	static ANVIL_STRONG_INLINE __m256 ANVIL_SIMD_CALL _mm256_mul_ps(const __m256 x, const __m256 y) {
		__m256 tmp;
		_mm_mul_ps(x.lo, y.lo);
		_mm_mul_ps(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512 ANVIL_SIMD_CALL _mm512_mul_ps(const __m512 x, const __m512 y) {
		__m512 tmp;
		_mm256_mul_ps(x.lo, y.lo);
		_mm256_mul_ps(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m128 ANVIL_SIMD_CALL _mm_div_ps(const __m128 x, const __m128 y) {
		float bufA[4];
		float bufB[4];
		_mm_storeu_ps(bufA, x);
		_mm_storeu_ps(bufB, y);
		for (int i = 0; i < 4; ++i) bufA[i] = bufA[i] / bufB[i];
		return _mm_loadu_ps(bufA);
	}
	static ANVIL_STRONG_INLINE __m256 ANVIL_SIMD_CALL _mm256_div_ps(const __m256 x, const __m256 y) {
		__m256 tmp;
		_mm_div_ps(x.lo, y.lo);
		_mm_div_ps(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512 ANVIL_SIMD_CALL _mm512_div_ps(const __m512 x, const __m512 y) {
		__m512 tmp;
		_mm256_div_ps(x.lo, y.lo);
		_mm256_div_ps(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m128 ANVIL_SIMD_CALL _mm_min_ps(const __m128 x, const __m128 y) {
		float bufA[4];
		float bufB[4];
		_mm_storeu_ps(bufA, x);
		_mm_storeu_ps(bufB, y);
		for (int i = 0; i < 4; ++i) bufA[i] = std::min(bufA[i], bufB[i]);;
		return _mm_loadu_ps(bufA);
	}
	static ANVIL_STRONG_INLINE __m256 ANVIL_SIMD_CALL _mm256_min_ps(const __m256 x, const __m256 y) {
		__m256 tmp;
		_mm_min_ps(x.lo, y.lo);
		_mm_min_ps(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512 ANVIL_SIMD_CALL _mm512_min_ps(const __m512 x, const __m512 y) {
		__m512 tmp;
		_mm256_min_ps(x.lo, y.lo);
		_mm256_min_ps(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m128 ANVIL_SIMD_CALL _mm_max_ps(const __m128 x, const __m128 y) {
		float bufA[4];
		float bufB[4];
		_mm_storeu_ps(bufA, x);
		_mm_storeu_ps(bufB, y);
		for (int i = 0; i < 4; ++i) bufA[i] = std::max(bufA[i], bufB[i]);;
		return _mm_loadu_ps(bufA);
	}
	static ANVIL_STRONG_INLINE __m256 ANVIL_SIMD_CALL _mm256_max_ps(const __m256 x, const __m256 y) {
		__m256 tmp;
		_mm_max_ps(x.lo, y.lo);
		_mm_max_ps(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512 ANVIL_SIMD_CALL _mm512_max_ps(const __m512 x, const __m512 y) {
		__m512 tmp;
		_mm256_max_ps(x.lo, y.lo);
		_mm256_max_ps(x.hi, y.hi);
		return tmp;
	}
	#define _mm_add_epi64(X, Y) vreinterpretq_u32_s32(vaddq_s32(vreinterpretq_s32_u32(X), vreinterpretq_s32_u32(Y)))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_add_epi64(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_add_epi64(x.lo, y.lo);
		_mm_add_epi64(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_add_epi64(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_add_epi64(x.lo, y.lo);
		_mm256_add_epi64(x.hi, y.hi);
		return tmp;
	}
	#define _mm_sub_epi64(X, Y) vreinterpretq_u32_s32(vsubq_s32(vreinterpretq_s32_u32(X), vreinterpretq_s32_u32(Y)))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_sub_epi64(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_sub_epi64(x.lo, y.lo);
		_mm_sub_epi64(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_sub_epi64(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_sub_epi64(x.lo, y.lo);
		_mm256_sub_epi64(x.hi, y.hi);
		return tmp;
	}
	#define _mm_mul_epi64(X, Y) vreinterpretq_u32_s32(vmulq_s32(vreinterpretq_s32_u32(X), vreinterpretq_s32_u32(Y)))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_mul_epi64(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_mul_epi64(x.lo, y.lo);
		_mm_mul_epi64(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_mul_epi64(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_mul_epi64(x.lo, y.lo);
		_mm256_mul_epi64(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m128i ANVIL_SIMD_CALL _mm_div_epi64(const __m128i x, const __m128i y) {
		int64_t bufA[2];
		int64_t bufB[2];
		_mm_storeu_si128(bufA, x);
		_mm_storeu_si128(bufB, y);
		for (int i = 0; i < 2; ++i) bufA[i] = bufA[i] / bufB[i];
		return _mm_loadu_si128(bufA);
	}
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_div_epi64(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_div_epi64(x.lo, y.lo);
		_mm_div_epi64(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_div_epi64(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_div_epi64(x.lo, y.lo);
		_mm256_div_epi64(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m128i ANVIL_SIMD_CALL _mm_min_epi64(const __m128i x, const __m128i y) {
		int64_t bufA[2];
		int64_t bufB[2];
		_mm_storeu_si128(bufA, x);
		_mm_storeu_si128(bufB, y);
		for (int i = 0; i < 2; ++i) bufA[i] = std::min(bufA[i], bufB[i]);;
		return _mm_loadu_si128(bufA);
	}
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_min_epi64(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_min_epi64(x.lo, y.lo);
		_mm_min_epi64(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_min_epi64(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_min_epi64(x.lo, y.lo);
		_mm256_min_epi64(x.hi, y.hi);
		return tmp;
	}
	#define _mm_max_epi64(X, Y) vreinterpretq_u32_s32(maxq_s32(vreinterpretq_s32_u32(X), vreinterpretq_s32_u32(Y)))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_max_epi64(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_max_epi64(x.lo, y.lo);
		_mm_max_epi64(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_max_epi64(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_max_epi64(x.lo, y.lo);
		_mm256_max_epi64(x.hi, y.hi);
		return tmp;
	}
	#define _mm_add_epu64(X, Y) (vaddq_u32(X, Y))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_add_epu64(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_add_epu64(x.lo, y.lo);
		_mm_add_epu64(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_add_epu64(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_add_epu64(x.lo, y.lo);
		_mm256_add_epu64(x.hi, y.hi);
		return tmp;
	}
	#define _mm_sub_epu64(X, Y) (vsubq_u32(X, Y))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_sub_epu64(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_sub_epu64(x.lo, y.lo);
		_mm_sub_epu64(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_sub_epu64(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_sub_epu64(x.lo, y.lo);
		_mm256_sub_epu64(x.hi, y.hi);
		return tmp;
	}
	#define _mm_mul_epu64(X, Y) (vmulq_u32(X, Y))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_mul_epu64(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_mul_epu64(x.lo, y.lo);
		_mm_mul_epu64(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_mul_epu64(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_mul_epu64(x.lo, y.lo);
		_mm256_mul_epu64(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m128i ANVIL_SIMD_CALL _mm_div_epu64(const __m128i x, const __m128i y) {
		uint64_t bufA[2];
		uint64_t bufB[2];
		_mm_storeu_si128(bufA, x);
		_mm_storeu_si128(bufB, y);
		for (int i = 0; i < 2; ++i) bufA[i] = bufA[i] / bufB[i];
		return _mm_loadu_si128(bufA);
	}
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_div_epu64(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_div_epu64(x.lo, y.lo);
		_mm_div_epu64(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_div_epu64(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_div_epu64(x.lo, y.lo);
		_mm256_div_epu64(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m128i ANVIL_SIMD_CALL _mm_min_epu64(const __m128i x, const __m128i y) {
		uint64_t bufA[2];
		uint64_t bufB[2];
		_mm_storeu_si128(bufA, x);
		_mm_storeu_si128(bufB, y);
		for (int i = 0; i < 2; ++i) bufA[i] = std::min(bufA[i], bufB[i]);;
		return _mm_loadu_si128(bufA);
	}
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_min_epu64(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_min_epu64(x.lo, y.lo);
		_mm_min_epu64(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_min_epu64(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_min_epu64(x.lo, y.lo);
		_mm256_min_epu64(x.hi, y.hi);
		return tmp;
	}
	#define _mm_max_epu64(X, Y) (maxq_u32(X, Y))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_max_epu64(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_max_epu64(x.lo, y.lo);
		_mm_max_epu64(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_max_epu64(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_max_epu64(x.lo, y.lo);
		_mm256_max_epu64(x.hi, y.hi);
		return tmp;
	}
	#define _mm_add_epi32(X, Y) vreinterpretq_u32_s32(vaddq_s32(vreinterpretq_s32_u32(X), vreinterpretq_s32_u32(Y)))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_add_epi32(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_add_epi32(x.lo, y.lo);
		_mm_add_epi32(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_add_epi32(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_add_epi32(x.lo, y.lo);
		_mm256_add_epi32(x.hi, y.hi);
		return tmp;
	}
	#define _mm_sub_epi32(X, Y) vreinterpretq_u32_s32(vsubq_s32(vreinterpretq_s32_u32(X), vreinterpretq_s32_u32(Y)))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_sub_epi32(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_sub_epi32(x.lo, y.lo);
		_mm_sub_epi32(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_sub_epi32(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_sub_epi32(x.lo, y.lo);
		_mm256_sub_epi32(x.hi, y.hi);
		return tmp;
	}
	#define _mm_mul_epi32(X, Y) vreinterpretq_u32_s32(vmulq_s32(vreinterpretq_s32_u32(X), vreinterpretq_s32_u32(Y)))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_mul_epi32(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_mul_epi32(x.lo, y.lo);
		_mm_mul_epi32(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_mul_epi32(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_mul_epi32(x.lo, y.lo);
		_mm256_mul_epi32(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m128i ANVIL_SIMD_CALL _mm_div_epi32(const __m128i x, const __m128i y) {
		int32_t bufA[4];
		int32_t bufB[4];
		_mm_storeu_si128(bufA, x);
		_mm_storeu_si128(bufB, y);
		for (int i = 0; i < 4; ++i) bufA[i] = bufA[i] / bufB[i];
		return _mm_loadu_si128(bufA);
	}
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_div_epi32(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_div_epi32(x.lo, y.lo);
		_mm_div_epi32(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_div_epi32(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_div_epi32(x.lo, y.lo);
		_mm256_div_epi32(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m128i ANVIL_SIMD_CALL _mm_min_epi32(const __m128i x, const __m128i y) {
		int32_t bufA[4];
		int32_t bufB[4];
		_mm_storeu_si128(bufA, x);
		_mm_storeu_si128(bufB, y);
		for (int i = 0; i < 4; ++i) bufA[i] = std::min(bufA[i], bufB[i]);;
		return _mm_loadu_si128(bufA);
	}
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_min_epi32(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_min_epi32(x.lo, y.lo);
		_mm_min_epi32(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_min_epi32(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_min_epi32(x.lo, y.lo);
		_mm256_min_epi32(x.hi, y.hi);
		return tmp;
	}
	#define _mm_max_epi32(X, Y) vreinterpretq_u32_s32(maxq_s32(vreinterpretq_s32_u32(X), vreinterpretq_s32_u32(Y)))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_max_epi32(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_max_epi32(x.lo, y.lo);
		_mm_max_epi32(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_max_epi32(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_max_epi32(x.lo, y.lo);
		_mm256_max_epi32(x.hi, y.hi);
		return tmp;
	}
	#define _mm_add_epu32(X, Y) (vaddq_u32(X, Y))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_add_epu32(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_add_epu32(x.lo, y.lo);
		_mm_add_epu32(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_add_epu32(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_add_epu32(x.lo, y.lo);
		_mm256_add_epu32(x.hi, y.hi);
		return tmp;
	}
	#define _mm_sub_epu32(X, Y) (vsubq_u32(X, Y))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_sub_epu32(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_sub_epu32(x.lo, y.lo);
		_mm_sub_epu32(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_sub_epu32(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_sub_epu32(x.lo, y.lo);
		_mm256_sub_epu32(x.hi, y.hi);
		return tmp;
	}
	#define _mm_mul_epu32(X, Y) (vmulq_u32(X, Y))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_mul_epu32(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_mul_epu32(x.lo, y.lo);
		_mm_mul_epu32(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_mul_epu32(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_mul_epu32(x.lo, y.lo);
		_mm256_mul_epu32(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m128i ANVIL_SIMD_CALL _mm_div_epu32(const __m128i x, const __m128i y) {
		uint32_t bufA[4];
		uint32_t bufB[4];
		_mm_storeu_si128(bufA, x);
		_mm_storeu_si128(bufB, y);
		for (int i = 0; i < 4; ++i) bufA[i] = bufA[i] / bufB[i];
		return _mm_loadu_si128(bufA);
	}
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_div_epu32(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_div_epu32(x.lo, y.lo);
		_mm_div_epu32(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_div_epu32(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_div_epu32(x.lo, y.lo);
		_mm256_div_epu32(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m128i ANVIL_SIMD_CALL _mm_min_epu32(const __m128i x, const __m128i y) {
		uint32_t bufA[4];
		uint32_t bufB[4];
		_mm_storeu_si128(bufA, x);
		_mm_storeu_si128(bufB, y);
		for (int i = 0; i < 4; ++i) bufA[i] = std::min(bufA[i], bufB[i]);;
		return _mm_loadu_si128(bufA);
	}
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_min_epu32(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_min_epu32(x.lo, y.lo);
		_mm_min_epu32(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_min_epu32(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_min_epu32(x.lo, y.lo);
		_mm256_min_epu32(x.hi, y.hi);
		return tmp;
	}
	#define _mm_max_epu32(X, Y) (maxq_u32(X, Y))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_max_epu32(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_max_epu32(x.lo, y.lo);
		_mm_max_epu32(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_max_epu32(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_max_epu32(x.lo, y.lo);
		_mm256_max_epu32(x.hi, y.hi);
		return tmp;
	}
	#define _mm_add_epi16(X, Y) vreinterpretq_u32_s16(vaddq_s16(vreinterpretq_s16_u32(X), vreinterpretq_s16_u32(Y)))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_add_epi16(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_add_epi16(x.lo, y.lo);
		_mm_add_epi16(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_add_epi16(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_add_epi16(x.lo, y.lo);
		_mm256_add_epi16(x.hi, y.hi);
		return tmp;
	}
	#define _mm_sub_epi16(X, Y) vreinterpretq_u32_s16(vsubq_s16(vreinterpretq_s16_u32(X), vreinterpretq_s16_u32(Y)))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_sub_epi16(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_sub_epi16(x.lo, y.lo);
		_mm_sub_epi16(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_sub_epi16(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_sub_epi16(x.lo, y.lo);
		_mm256_sub_epi16(x.hi, y.hi);
		return tmp;
	}
	#define _mm_mul_epi16(X, Y) vreinterpretq_u32_s16(vmulq_s16(vreinterpretq_s16_u32(X), vreinterpretq_s16_u32(Y)))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_mul_epi16(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_mul_epi16(x.lo, y.lo);
		_mm_mul_epi16(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_mul_epi16(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_mul_epi16(x.lo, y.lo);
		_mm256_mul_epi16(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m128i ANVIL_SIMD_CALL _mm_div_epi16(const __m128i x, const __m128i y) {
		int16_t bufA[8];
		int16_t bufB[8];
		_mm_storeu_si128(bufA, x);
		_mm_storeu_si128(bufB, y);
		for (int i = 0; i < 8; ++i) bufA[i] = bufA[i] / bufB[i];
		return _mm_loadu_si128(bufA);
	}
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_div_epi16(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_div_epi16(x.lo, y.lo);
		_mm_div_epi16(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_div_epi16(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_div_epi16(x.lo, y.lo);
		_mm256_div_epi16(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m128i ANVIL_SIMD_CALL _mm_min_epi16(const __m128i x, const __m128i y) {
		int16_t bufA[8];
		int16_t bufB[8];
		_mm_storeu_si128(bufA, x);
		_mm_storeu_si128(bufB, y);
		for (int i = 0; i < 8; ++i) bufA[i] = std::min(bufA[i], bufB[i]);;
		return _mm_loadu_si128(bufA);
	}
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_min_epi16(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_min_epi16(x.lo, y.lo);
		_mm_min_epi16(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_min_epi16(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_min_epi16(x.lo, y.lo);
		_mm256_min_epi16(x.hi, y.hi);
		return tmp;
	}
	#define _mm_max_epi16(X, Y) vreinterpretq_u32_s16(maxq_s16(vreinterpretq_s16_u32(X), vreinterpretq_s16_u32(Y)))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_max_epi16(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_max_epi16(x.lo, y.lo);
		_mm_max_epi16(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_max_epi16(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_max_epi16(x.lo, y.lo);
		_mm256_max_epi16(x.hi, y.hi);
		return tmp;
	}
	#define _mm_add_epu16(X, Y) vreinterpretq_u32_u16(vaddq_u16(vreinterpretq_u16_u32(X), vreinterpretq_u16_u32(Y)))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_add_epu16(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_add_epu16(x.lo, y.lo);
		_mm_add_epu16(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_add_epu16(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_add_epu16(x.lo, y.lo);
		_mm256_add_epu16(x.hi, y.hi);
		return tmp;
	}
	#define _mm_sub_epu16(X, Y) vreinterpretq_u32_u16(vsubq_u16(vreinterpretq_u16_u32(X), vreinterpretq_u16_u32(Y)))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_sub_epu16(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_sub_epu16(x.lo, y.lo);
		_mm_sub_epu16(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_sub_epu16(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_sub_epu16(x.lo, y.lo);
		_mm256_sub_epu16(x.hi, y.hi);
		return tmp;
	}
	#define _mm_mul_epu16(X, Y) vreinterpretq_u32_u16(vmulq_u16(vreinterpretq_u16_u32(X), vreinterpretq_u16_u32(Y)))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_mul_epu16(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_mul_epu16(x.lo, y.lo);
		_mm_mul_epu16(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_mul_epu16(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_mul_epu16(x.lo, y.lo);
		_mm256_mul_epu16(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m128i ANVIL_SIMD_CALL _mm_div_epu16(const __m128i x, const __m128i y) {
		uint16_t bufA[8];
		uint16_t bufB[8];
		_mm_storeu_si128(bufA, x);
		_mm_storeu_si128(bufB, y);
		for (int i = 0; i < 8; ++i) bufA[i] = bufA[i] / bufB[i];
		return _mm_loadu_si128(bufA);
	}
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_div_epu16(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_div_epu16(x.lo, y.lo);
		_mm_div_epu16(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_div_epu16(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_div_epu16(x.lo, y.lo);
		_mm256_div_epu16(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m128i ANVIL_SIMD_CALL _mm_min_epu16(const __m128i x, const __m128i y) {
		uint16_t bufA[8];
		uint16_t bufB[8];
		_mm_storeu_si128(bufA, x);
		_mm_storeu_si128(bufB, y);
		for (int i = 0; i < 8; ++i) bufA[i] = std::min(bufA[i], bufB[i]);;
		return _mm_loadu_si128(bufA);
	}
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_min_epu16(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_min_epu16(x.lo, y.lo);
		_mm_min_epu16(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_min_epu16(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_min_epu16(x.lo, y.lo);
		_mm256_min_epu16(x.hi, y.hi);
		return tmp;
	}
	#define _mm_max_epu16(X, Y) vreinterpretq_u32_u16(maxq_u16(vreinterpretq_u16_u32(X), vreinterpretq_u16_u32(Y)))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_max_epu16(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_max_epu16(x.lo, y.lo);
		_mm_max_epu16(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_max_epu16(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_max_epu16(x.lo, y.lo);
		_mm256_max_epu16(x.hi, y.hi);
		return tmp;
	}
	#define _mm_add_epi8(X, Y) vreinterpretq_u32_s8(vaddq_s8(vreinterpretq_s8_u32(X), vreinterpretq_s8_u32(Y)))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_add_epi8(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_add_epi8(x.lo, y.lo);
		_mm_add_epi8(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_add_epi8(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_add_epi8(x.lo, y.lo);
		_mm256_add_epi8(x.hi, y.hi);
		return tmp;
	}
	#define _mm_sub_epi8(X, Y) vreinterpretq_u32_s8(vsubq_s8(vreinterpretq_s8_u32(X), vreinterpretq_s8_u32(Y)))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_sub_epi8(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_sub_epi8(x.lo, y.lo);
		_mm_sub_epi8(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_sub_epi8(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_sub_epi8(x.lo, y.lo);
		_mm256_sub_epi8(x.hi, y.hi);
		return tmp;
	}
	#define _mm_mul_epi8(X, Y) vreinterpretq_u32_s8(vmulq_s8(vreinterpretq_s8_u32(X), vreinterpretq_s8_u32(Y)))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_mul_epi8(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_mul_epi8(x.lo, y.lo);
		_mm_mul_epi8(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_mul_epi8(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_mul_epi8(x.lo, y.lo);
		_mm256_mul_epi8(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m128i ANVIL_SIMD_CALL _mm_div_epi8(const __m128i x, const __m128i y) {
		int8_t bufA[16];
		int8_t bufB[16];
		_mm_storeu_si128(bufA, x);
		_mm_storeu_si128(bufB, y);
		for (int i = 0; i < 16; ++i) bufA[i] = bufA[i] / bufB[i];
		return _mm_loadu_si128(bufA);
	}
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_div_epi8(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_div_epi8(x.lo, y.lo);
		_mm_div_epi8(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_div_epi8(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_div_epi8(x.lo, y.lo);
		_mm256_div_epi8(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m128i ANVIL_SIMD_CALL _mm_min_epi8(const __m128i x, const __m128i y) {
		int8_t bufA[16];
		int8_t bufB[16];
		_mm_storeu_si128(bufA, x);
		_mm_storeu_si128(bufB, y);
		for (int i = 0; i < 16; ++i) bufA[i] = std::min(bufA[i], bufB[i]);;
		return _mm_loadu_si128(bufA);
	}
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_min_epi8(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_min_epi8(x.lo, y.lo);
		_mm_min_epi8(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_min_epi8(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_min_epi8(x.lo, y.lo);
		_mm256_min_epi8(x.hi, y.hi);
		return tmp;
	}
	#define _mm_max_epi8(X, Y) vreinterpretq_u32_s8(maxq_s8(vreinterpretq_s8_u32(X), vreinterpretq_s8_u32(Y)))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_max_epi8(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_max_epi8(x.lo, y.lo);
		_mm_max_epi8(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_max_epi8(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_max_epi8(x.lo, y.lo);
		_mm256_max_epi8(x.hi, y.hi);
		return tmp;
	}
	#define _mm_add_epu8(X, Y) vreinterpretq_u32_u8(vaddq_u8(vreinterpretq_u8_u32(X), vreinterpretq_u8_u32(Y)))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_add_epu8(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_add_epu8(x.lo, y.lo);
		_mm_add_epu8(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_add_epu8(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_add_epu8(x.lo, y.lo);
		_mm256_add_epu8(x.hi, y.hi);
		return tmp;
	}
	#define _mm_sub_epu8(X, Y) vreinterpretq_u32_u8(vsubq_u8(vreinterpretq_u8_u32(X), vreinterpretq_u8_u32(Y)))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_sub_epu8(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_sub_epu8(x.lo, y.lo);
		_mm_sub_epu8(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_sub_epu8(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_sub_epu8(x.lo, y.lo);
		_mm256_sub_epu8(x.hi, y.hi);
		return tmp;
	}
	#define _mm_mul_epu8(X, Y) vreinterpretq_u32_u8(vmulq_u8(vreinterpretq_u8_u32(X), vreinterpretq_u8_u32(Y)))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_mul_epu8(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_mul_epu8(x.lo, y.lo);
		_mm_mul_epu8(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_mul_epu8(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_mul_epu8(x.lo, y.lo);
		_mm256_mul_epu8(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m128i ANVIL_SIMD_CALL _mm_div_epu8(const __m128i x, const __m128i y) {
		uint8_t bufA[16];
		uint8_t bufB[16];
		_mm_storeu_si128(bufA, x);
		_mm_storeu_si128(bufB, y);
		for (int i = 0; i < 16; ++i) bufA[i] = bufA[i] / bufB[i];
		return _mm_loadu_si128(bufA);
	}
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_div_epu8(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_div_epu8(x.lo, y.lo);
		_mm_div_epu8(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_div_epu8(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_div_epu8(x.lo, y.lo);
		_mm256_div_epu8(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m128i ANVIL_SIMD_CALL _mm_min_epu8(const __m128i x, const __m128i y) {
		uint8_t bufA[16];
		uint8_t bufB[16];
		_mm_storeu_si128(bufA, x);
		_mm_storeu_si128(bufB, y);
		for (int i = 0; i < 16; ++i) bufA[i] = std::min(bufA[i], bufB[i]);;
		return _mm_loadu_si128(bufA);
	}
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_min_epu8(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_min_epu8(x.lo, y.lo);
		_mm_min_epu8(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_min_epu8(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_min_epu8(x.lo, y.lo);
		_mm256_min_epu8(x.hi, y.hi);
		return tmp;
	}
	#define _mm_max_epu8(X, Y) vreinterpretq_u32_u8(maxq_u8(vreinterpretq_u8_u32(X), vreinterpretq_u8_u32(Y)))
	static ANVIL_STRONG_INLINE __m256i ANVIL_SIMD_CALL _mm256_max_epu8(const __m256i x, const __m256i y) {
		__m256i tmp;
		_mm_max_epu8(x.lo, y.lo);
		_mm_max_epu8(x.hi, y.hi);
		return tmp;
	}
	static ANVIL_STRONG_INLINE __m512i ANVIL_SIMD_CALL _mm512_max_epu8(const __m512i x, const __m512i y) {
		__m512i tmp;
		_mm256_max_epu8(x.lo, y.lo);
		_mm256_max_epu8(x.hi, y.hi);
		return tmp;
	}


	//
	//typedef float32x4_t __m128;
	//
	//// Non-SSE Helpers
	//
	//#define _mm_not_ps(X) vreinterpretq_f32_s32(vmvnq_s32(vreinterpretq_s32_f32(X)))
	//#define _mm_setone_ps(X) vreinterpretq_f32_u32(vdupq_n_u32(UINT32_MAX))
	//#define _mm_helper_ss(F,X) vsetq_lane_f32(vget_lane_f32(F(vget_low_f32(X)),0), Y, 0)
	//#define _mm_helper2_ss(F,X,Y) vsetq_lane_f32(vget_lane_f32(F(vget_low_f32(X), vget_low_f32(Y)),0), Y, 0)
	//#define _mm_bitwise_helper_ps(F,X) vreinterpretq_f32_s32(F(vreinterpretq_s32_f32(X)))
	//#define _mm_bitwise_helper2_ps(F,X,Y) vreinterpretq_f32_s32(F(vreinterpretq_s32_f32(X),vreinterpretq_s32_f32(Y)))
	//
	//// SSE Intrinsics
	//
	//#define _mm_add_ps(X,Y) vaddq_f32(X,Y)
	//#define _mm_add_ss(X,Y) _mm_helper2_ss(vadd_f32,X,Y)
	//#define _mm_and_ps(X,Y)_mm_bitwise_helper2_ps(vandq_s32,X,Y)
	//#define _mm_andnot_ps(X,Y) _mm_and_ps(_mm_not_ps(X),Y)
	//#define _mm_cmpneq_ps(X,Y) vreinterpretq_f32_u32(vmvnq_u32(vceqq_f32(X,Y)))
	//#define _mm_cmpneq_ss_(X,Y) vreinterpret_f32_u32(vmvn_u32(vceq_f32(X,Y)))
	//#define _mm_cmpneq_ss(X,Y) _mm_helper2_ss(_mm_cmpneq_ss_,X,Y)
	//#define _mm_cmpeq_ps(X,Y) vreinterpretq_f32_u32(vceqq_f32(X,Y))
	//#define _mm_cmpeq_ss_(X,Y) vreinterpret_f32_u32(vceq_f32(X,Y))
	//#define _mm_cmpeq_ss(X,Y) _mm_helper2_ss(_mm_cmpeq_ss_,X,Y)
	//#define _mm_cmpge_ps(X,Y) vreinterpretq_f32_u32(vcgeq_f32(X,Y))
	//#define _mm_cmpge_ss_(X,Y) vreinterpret_f32_u32(vcge_f32(X,Y))
	//#define _mm_cmpge_ss(X,Y) _mm_helper2_ss(_mm_cmpge_ss_,X,Y)
	//#define _mm_cmpgt_ps(X,Y) vreinterpretq_f32_u32(vcgtq_f32(X,Y))
	//#define _mm_cmpgt_ss_(X,Y) vreinterpret_f32_u32(vcgt_f32(X,Y))
	//#define _mm_cmpgt_ss(X,Y) _mm_helper2_ss(_mm_cmpgt_ss_,X,Y)
	//#define _mm_cmple_ps(X,Y) vreinterpretq_f32_u32(vcleq_f32(X,Y))
	//#define _mm_cmple_ss_(X,Y) vreinterpret_f32_u32(vcle_f32(X,Y))
	//#define _mm_cmple_ss(X,Y) _mm_helper2_ss(_mm_cmple_ss_,X,Y)
	//#define _mm_cmplt_ps(X,Y) vreinterpretq_f32_u32(vcltq_f32(X,Y))
	//#define _mm_cmplt_ss_(X,Y) vreinterpret_f32_u32(vclt_f32(X,Y))
	//#define _mm_cmplt_ss(X,Y) _mm_helper2_ss(_mm_cmplt_ss_,X,Y)
	//#define _mm_cmpord_ps_(X) vmvnq_u32(vceqq_f32(X,_mm_set1_ps(NAN)))
	//#define _mm_cmpord_ps(X,Y) vreinterpretq_f32_u32(vandq_u32(_mm_cmpord_ps_(X), _mm_cmpord_ps_(Y)))
	////! \todo __m128 _mm_cmpord_ss (__m128 a, __m128 b)
	////! \todo __m128 _mm_cmpunord_ps (__m128 a, __m128 b)
	////! \todo __m128 _mm_cmpunord_ss (__m128 a, __m128 b)
	////! \todo int _mm_comieq_ss (__m128 a, __m128 b)
	////! \todo int _mm_comige_ss (__m128 a, __m128 b)
	////! \todo int _mm_comigt_ss (__m128 a, __m128 b)
	////! \todo int _mm_comile_ss (__m128 a, __m128 b)
	////! \todo int _mm_comilt_ss (__m128 a, __m128 b)
	////! \todo int _mm_comineq_ss (__m128 a, __m128 b)
	////! \todo __m128 _mm_cvt_si2ss (__m128 a, int b)
	////! \todo int _mm_cvt_ss2si (__m128 a)
	////! \todo __m128 _mm_cvtsi32_ss (__m128 a, int b)
	////! \todo float _mm_cvtss_f32 (__m128 a)
	////! \todo int _mm_cvtss_si32 (__m128 a)
	////! \todo __int64 _mm_cvtss_si64 (__m128 a)
	////! \todo int _mm_cvtt_ss2si (__m128 a)
	////! \todo int _mm_cvttss_si32 (__m128 a)
	////! \todo __int64 _mm_cvttss_si64 (__m128 a)
	//static ANVIL_STRONG_INLINE __m128 ANVIL_SIMD_CALL _mm_div_ps(const __m128 a, const __m128 b) throw() {
	//	float bufA[4];
	//	float bufB[4];
	//	_mm_store_ps(bufA, a);
	//	_mm_store_ps(bufB, b);
	//	for(int i = 0; i < 4; ++i) bufA[i] /= bufB[i];
	//	return _mm_load_ps(bufA);
	//}
	//#define _mm_div_ss(X,Y) vsetq_lane_f32(vgetq_lane_f32(X,0) / vgetq_lane_f32(Y,0), Y, 0)
	////! \todo unsigned int _MM_GET_EXCEPTION_MASK ()
	////! \todo unsigned int _MM_GET_EXCEPTION_STATE ()
	////! \todo unsigned int _MM_GET_FLUSH_ZERO_MODE ()
	////! \todo unsigned int _MM_GET_ROUNDING_MODE ()
	////! \todo unsigned int _mm_getcsr (void)
	//#define _mm_load_ps(X) _mm_loadu_ps(X)
	//#define _mm_load_ps1(X) _mm_load1_ps(X)
	//#define _mm_load_ss(X) _mm_set_ss(*X)
	//#define _mm_load1_ps(X) _mm_set1_ps(*X)
	//#define _mm_loadr_ps(X) _mm_set_ps(X[3],X[2],X[1],X[0])
	//#define _mm_loadu_ps(X) vld1q_f32(X)
	//#define _mm_max_ps(X,Y) vmaxq_f32(X,Y)
	//#define _mm_max_ss(X,Y) _mm_helper2_ss(vmax_f32,X,Y)
	//#define _mm_min_ps(X,Y) vminq_f32(X,Y)
	//#define _mm_min_ss(X,Y) _mm_helper2_ss(vmin_f32,X,Y)
	//#define _mm_move_ss(X,Y)  vsetq_lane_f32(vgetq_lane_f32(X,0),Y,0)
	//#define _mm_movehl_ps(X,Y) vcombine_f32(vget_high_f32(Y),vget_high_f32(X))
	//#define _mm_movelh_ps(X,Y) vcombine_f32(vget_low_f32(X),vget_low_f32(Y))
	////! \todo int _mm_movemask_ps (__m128 a)
	//#define _mm_mul_ps(X,Y) vmulq_f32(X,Y)
	//#define _mm_mul_ss(X,Y) _mm_helper2_ss(vmul_f32,X,Y)
	//#define _mm_or_ps(X,Y)_mm_bitwise_helper2_ps(vorrq_s32,X,Y)
	////! \todo void _mm_prefetch (char const* p, int i)
	////! \todo __m128 _mm_rcp_ps (__m128 a)
	////! \todo __m128 _mm_rcp_ss (__m128 a)
	////! \todo __m128 _mm_rsqrt_ps (__m128 a)
	////! \todo __m128 _mm_rsqrt_ss (__m128 a)
	////! \todo void _MM_SET_EXCEPTION_MASK (unsigned int a)
	////! \todo void _MM_SET_EXCEPTION_STATE (unsigned int a)
	////! \todo void _MM_SET_FLUSH_ZERO_MODE (unsigned int a)
	//static ANVIL_STRONG_INLINE __m128 ANVIL_SIMD_CALL _mm_set_ps(const float a, const float b, const float c, const float d) throw() {
	//	const float buf[4] = { a, b, c, d };
	//	return _mm_load_ps(buf);
	//}
	//#define _mm_set_ps1(X) _mm_set1_ps(X)
	////! \todo void _MM_SET_ROUNDING_MODE (unsigned int a)
	//#define _mm_set_ss(X) vsetq_lane_f32(X,_mm_setzero_ps(),0)
	//#define _mm_set1_ps(X) vdupq_n_f32(X)
	//#define _mm_setcsr(X)
	//#define _mm_setr_ps(X,Y,Z,W) vrev64q_f32(_mm_setr_ps(X,Y,Z,W))
	//#define _mm_setzero_ps() _mm_set1_ps(0.f)
	//#define _mm_sfence()
	////! \todo __m128 _mm_shuffle_ps (__m128 a, __m128 b, unsigned int imm8)
	////! \todo __m128 _mm_sqrt_ps (__m128 a)
	////! \todo __m128 _mm_sqrt_ss (__m128 a)
	//#define _mm_store_ps(X,Y) _mm_storeu_ps(X,Y)
	//#define _mm_store_ps1(X,Y) _mm_store1_ps(X,Y)
	//#define _mm_store_ss(X,Y) _mm_store1_ps(X,Y)
	//static ANVIL_STRONG_INLINE void ANVIL_SIMD_CALL _mm_store1_ps(float* ptr, __m128 a) throw() {
	//	float tmp;
	//	vst1q_lane_f32(&tmp, a, 0);
	//	for (int i = 0; i < 4; ++i) ptr[i] = tmp;
	//}
	//#define _mm_storer_ps(X,Y) _mm_store_ps(X,vrev64q_f32(Y))
	//#define _mm_storeu_ps(X,Y) vst1q_f32(X,Y)
	//#define _mm_stream_ps(X,Y) _mm_storeu_ps(X,Y)
	//#define _mm_sub_ps(X,Y) vsubq_f32(X,Y)
	//#define _mm_sub_ss(X,Y) _mm_helper2_ss(vsub_f32,X,Y)
	////! \todo _MM_TRANSPOSE4_PS (__m128 row0, __m128 row1, __m128 row2, __m128 row3)
	//#define _mm_ucomieq_ss(X,Y) (vgetq_lane_f32(X,0) == vgetq_lane_f32(Y,0))
	//#define _mm_ucomige_ss(X,Y) (vgetq_lane_f32(X,0) >= vgetq_lane_f32(Y,0))
	//#define _mm_ucomigt_ss(X,Y) (vgetq_lane_f32(X,0) > vgetq_lane_f32(Y,0))
	//#define _mm_ucomile_ss(X,Y) (vgetq_lane_f32(X,0) <= vgetq_lane_f32(Y,0))
	//#define _mm_ucomilt_ss(X,Y) (vgetq_lane_f32(X,0) < vgetq_lane_f32(Y,0))
	//#define _mm_ucomineq_ss(X,Y) (vgetq_lane_f32(X,0) != vgetq_lane_f32(Y,0))
	//#define _mm_undefined_ps() __m128()
	//#define _mm_unpackhi_ps(X,Y) vcombine_f32(vget_high_f32(X),vget_high_f32(Y))
	//#define _mm_unpacklo_ps(X,Y) vcombine_f32(vget_low_f32(X),vget_low_f32(Y))
	//#define _mm_xor_ps(X,Y)_mm_bitwise_helper2_ps(veorq_s32,X,Y)
#endif