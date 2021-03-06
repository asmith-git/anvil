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

#include <cmath>
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
typedef uint8_t uint8x1_t;

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

#define anvil_reinterpret_f64x1_as_s64x1(X) *reinterpret_cast<const int64x1_t*(&X)
#define anvil_reinterpret_f64x1_as_u64x1(X) *reinterpret_cast<const uint64x1_t*(&X)
#define anvil_reinterpret_f64x1_as_f32x2(X) *reinterpret_cast<const float32x2_t*(&X)
#define anvil_reinterpret_f64x2_as_f32x4(X) *reinterpret_cast<const float32x4_t*(&X)
#define anvil_reinterpret_f64x4_as_f32x8(X) *reinterpret_cast<const float32x8_t*(&X)
#define anvil_reinterpret_f64x1_as_s64x1(X) *reinterpret_cast<const int64x1_t*(&X)
#define anvil_reinterpret_f64x2_as_s64x2(X) *reinterpret_cast<const int64x2_t*(&X)
#define anvil_reinterpret_f64x4_as_s64x4(X) *reinterpret_cast<const int64x4_t*(&X)
#define anvil_reinterpret_f64x1_as_u64x1(X) *reinterpret_cast<const uint64x1_t*(&X)
#define anvil_reinterpret_f64x2_as_u64x2(X) *reinterpret_cast<const uint64x2_t*(&X)
#define anvil_reinterpret_f64x4_as_u64x4(X) *reinterpret_cast<const uint64x4_t*(&X)
#define anvil_reinterpret_f64x1_as_s32x2(X) *reinterpret_cast<const int32x2_t*(&X)
#define anvil_reinterpret_f64x2_as_s32x4(X) *reinterpret_cast<const int32x4_t*(&X)
#define anvil_reinterpret_f64x4_as_s32x8(X) *reinterpret_cast<const int32x8_t*(&X)
#define anvil_reinterpret_f64x1_as_u32x2(X) *reinterpret_cast<const uint32x2_t*(&X)
#define anvil_reinterpret_f64x2_as_u32x4(X) *reinterpret_cast<const uint32x4_t*(&X)
#define anvil_reinterpret_f64x4_as_u32x8(X) *reinterpret_cast<const uint32x8_t*(&X)
#define anvil_reinterpret_f64x1_as_s16x4(X) *reinterpret_cast<const int16x4_t*(&X)
#define anvil_reinterpret_f64x2_as_s16x8(X) *reinterpret_cast<const int16x8_t*(&X)
#define anvil_reinterpret_f64x4_as_s16x16(X) *reinterpret_cast<const int16x16_t*(&X)
#define anvil_reinterpret_f64x1_as_u16x4(X) *reinterpret_cast<const uint16x4_t*(&X)
#define anvil_reinterpret_f64x2_as_u16x8(X) *reinterpret_cast<const uint16x8_t*(&X)
#define anvil_reinterpret_f64x4_as_u16x16(X) *reinterpret_cast<const uint16x16_t*(&X)
#define anvil_reinterpret_f64x1_as_s8x8(X) *reinterpret_cast<const int8x8_t*(&X)
#define anvil_reinterpret_f64x2_as_s8x16(X) *reinterpret_cast<const int8x16_t*(&X)
#define anvil_reinterpret_f64x4_as_s8x32(X) *reinterpret_cast<const int8x32_t*(&X)
#define anvil_reinterpret_f64x1_as_u8x8(X) *reinterpret_cast<const uint8x8_t*(&X)
#define anvil_reinterpret_f64x2_as_u8x16(X) *reinterpret_cast<const uint8x16_t*(&X)
#define anvil_reinterpret_f64x4_as_u8x32(X) *reinterpret_cast<const uint8x32_t*(&X)
#define anvil_reinterpret_f32x1_as_s32x1(X) *reinterpret_cast<const int32x1_t*(&X)
#define anvil_reinterpret_f32x1_as_u32x1(X) *reinterpret_cast<const uint32x1_t*(&X)
#define anvil_reinterpret_f32x2_as_f64x1(X) *reinterpret_cast<const float64x1_t*(&X)
#define anvil_reinterpret_f32x4_as_f64x2(X) *reinterpret_cast<const float64x2_t*(&X)
#define anvil_reinterpret_f32x8_as_f64x4(X) *reinterpret_cast<const float64x4_t*(&X)
#define anvil_reinterpret_f32x2_as_s64x1(X) *reinterpret_cast<const int64x1_t*(&X)
#define anvil_reinterpret_f32x4_as_s64x2(X) *reinterpret_cast<const int64x2_t*(&X)
#define anvil_reinterpret_f32x8_as_s64x4(X) *reinterpret_cast<const int64x4_t*(&X)
#define anvil_reinterpret_f32x2_as_u64x1(X) *reinterpret_cast<const uint64x1_t*(&X)
#define anvil_reinterpret_f32x4_as_u64x2(X) *reinterpret_cast<const uint64x2_t*(&X)
#define anvil_reinterpret_f32x8_as_u64x4(X) *reinterpret_cast<const uint64x4_t*(&X)
#define anvil_reinterpret_f32x2_as_s32x2(X) *reinterpret_cast<const int32x2_t*(&X)
#define anvil_reinterpret_f32x4_as_s32x4(X) *reinterpret_cast<const int32x4_t*(&X)
#define anvil_reinterpret_f32x8_as_s32x8(X) *reinterpret_cast<const int32x8_t*(&X)
#define anvil_reinterpret_f32x2_as_u32x2(X) *reinterpret_cast<const uint32x2_t*(&X)
#define anvil_reinterpret_f32x4_as_u32x4(X) *reinterpret_cast<const uint32x4_t*(&X)
#define anvil_reinterpret_f32x8_as_u32x8(X) *reinterpret_cast<const uint32x8_t*(&X)
#define anvil_reinterpret_f32x2_as_s16x4(X) *reinterpret_cast<const int16x4_t*(&X)
#define anvil_reinterpret_f32x4_as_s16x8(X) *reinterpret_cast<const int16x8_t*(&X)
#define anvil_reinterpret_f32x8_as_s16x16(X) *reinterpret_cast<const int16x16_t*(&X)
#define anvil_reinterpret_f32x2_as_u16x4(X) *reinterpret_cast<const uint16x4_t*(&X)
#define anvil_reinterpret_f32x4_as_u16x8(X) *reinterpret_cast<const uint16x8_t*(&X)
#define anvil_reinterpret_f32x8_as_u16x16(X) *reinterpret_cast<const uint16x16_t*(&X)
#define anvil_reinterpret_f32x2_as_s8x8(X) *reinterpret_cast<const int8x8_t*(&X)
#define anvil_reinterpret_f32x4_as_s8x16(X) *reinterpret_cast<const int8x16_t*(&X)
#define anvil_reinterpret_f32x8_as_s8x32(X) *reinterpret_cast<const int8x32_t*(&X)
#define anvil_reinterpret_f32x2_as_u8x8(X) *reinterpret_cast<const uint8x8_t*(&X)
#define anvil_reinterpret_f32x4_as_u8x16(X) *reinterpret_cast<const uint8x16_t*(&X)
#define anvil_reinterpret_f32x8_as_u8x32(X) *reinterpret_cast<const uint8x32_t*(&X)
#define anvil_reinterpret_s64x1_as_f64x1(X) *reinterpret_cast<const float64x1_t*(&X)
#define anvil_reinterpret_s64x1_as_u64x1(X) *reinterpret_cast<const uint64x1_t*(&X)
#define anvil_reinterpret_s64x1_as_f64x1(X) *reinterpret_cast<const float64x1_t*(&X)
#define anvil_reinterpret_s64x2_as_f64x2(X) *reinterpret_cast<const float64x2_t*(&X)
#define anvil_reinterpret_s64x4_as_f64x4(X) *reinterpret_cast<const float64x4_t*(&X)
#define anvil_reinterpret_s64x1_as_f32x2(X) *reinterpret_cast<const float32x2_t*(&X)
#define anvil_reinterpret_s64x2_as_f32x4(X) *reinterpret_cast<const float32x4_t*(&X)
#define anvil_reinterpret_s64x4_as_f32x8(X) *reinterpret_cast<const float32x8_t*(&X)
#define anvil_reinterpret_s64x1_as_u64x1(X) *reinterpret_cast<const uint64x1_t*(&X)
#define anvil_reinterpret_s64x2_as_u64x2(X) *reinterpret_cast<const uint64x2_t*(&X)
#define anvil_reinterpret_s64x4_as_u64x4(X) *reinterpret_cast<const uint64x4_t*(&X)
#define anvil_reinterpret_s64x1_as_s32x2(X) *reinterpret_cast<const int32x2_t*(&X)
#define anvil_reinterpret_s64x2_as_s32x4(X) *reinterpret_cast<const int32x4_t*(&X)
#define anvil_reinterpret_s64x4_as_s32x8(X) *reinterpret_cast<const int32x8_t*(&X)
#define anvil_reinterpret_s64x1_as_u32x2(X) *reinterpret_cast<const uint32x2_t*(&X)
#define anvil_reinterpret_s64x2_as_u32x4(X) *reinterpret_cast<const uint32x4_t*(&X)
#define anvil_reinterpret_s64x4_as_u32x8(X) *reinterpret_cast<const uint32x8_t*(&X)
#define anvil_reinterpret_s64x1_as_s16x4(X) *reinterpret_cast<const int16x4_t*(&X)
#define anvil_reinterpret_s64x2_as_s16x8(X) *reinterpret_cast<const int16x8_t*(&X)
#define anvil_reinterpret_s64x4_as_s16x16(X) *reinterpret_cast<const int16x16_t*(&X)
#define anvil_reinterpret_s64x1_as_u16x4(X) *reinterpret_cast<const uint16x4_t*(&X)
#define anvil_reinterpret_s64x2_as_u16x8(X) *reinterpret_cast<const uint16x8_t*(&X)
#define anvil_reinterpret_s64x4_as_u16x16(X) *reinterpret_cast<const uint16x16_t*(&X)
#define anvil_reinterpret_s64x1_as_s8x8(X) *reinterpret_cast<const int8x8_t*(&X)
#define anvil_reinterpret_s64x2_as_s8x16(X) *reinterpret_cast<const int8x16_t*(&X)
#define anvil_reinterpret_s64x4_as_s8x32(X) *reinterpret_cast<const int8x32_t*(&X)
#define anvil_reinterpret_s64x1_as_u8x8(X) *reinterpret_cast<const uint8x8_t*(&X)
#define anvil_reinterpret_s64x2_as_u8x16(X) *reinterpret_cast<const uint8x16_t*(&X)
#define anvil_reinterpret_s64x4_as_u8x32(X) *reinterpret_cast<const uint8x32_t*(&X)
#define anvil_reinterpret_u64x1_as_f64x1(X) *reinterpret_cast<const float64x1_t*(&X)
#define anvil_reinterpret_u64x1_as_s64x1(X) *reinterpret_cast<const int64x1_t*(&X)
#define anvil_reinterpret_u64x1_as_f64x1(X) *reinterpret_cast<const float64x1_t*(&X)
#define anvil_reinterpret_u64x2_as_f64x2(X) *reinterpret_cast<const float64x2_t*(&X)
#define anvil_reinterpret_u64x4_as_f64x4(X) *reinterpret_cast<const float64x4_t*(&X)
#define anvil_reinterpret_u64x1_as_f32x2(X) *reinterpret_cast<const float32x2_t*(&X)
#define anvil_reinterpret_u64x2_as_f32x4(X) *reinterpret_cast<const float32x4_t*(&X)
#define anvil_reinterpret_u64x4_as_f32x8(X) *reinterpret_cast<const float32x8_t*(&X)
#define anvil_reinterpret_u64x1_as_s64x1(X) *reinterpret_cast<const int64x1_t*(&X)
#define anvil_reinterpret_u64x2_as_s64x2(X) *reinterpret_cast<const int64x2_t*(&X)
#define anvil_reinterpret_u64x4_as_s64x4(X) *reinterpret_cast<const int64x4_t*(&X)
#define anvil_reinterpret_u64x1_as_s32x2(X) *reinterpret_cast<const int32x2_t*(&X)
#define anvil_reinterpret_u64x2_as_s32x4(X) *reinterpret_cast<const int32x4_t*(&X)
#define anvil_reinterpret_u64x4_as_s32x8(X) *reinterpret_cast<const int32x8_t*(&X)
#define anvil_reinterpret_u64x1_as_u32x2(X) *reinterpret_cast<const uint32x2_t*(&X)
#define anvil_reinterpret_u64x2_as_u32x4(X) *reinterpret_cast<const uint32x4_t*(&X)
#define anvil_reinterpret_u64x4_as_u32x8(X) *reinterpret_cast<const uint32x8_t*(&X)
#define anvil_reinterpret_u64x1_as_s16x4(X) *reinterpret_cast<const int16x4_t*(&X)
#define anvil_reinterpret_u64x2_as_s16x8(X) *reinterpret_cast<const int16x8_t*(&X)
#define anvil_reinterpret_u64x4_as_s16x16(X) *reinterpret_cast<const int16x16_t*(&X)
#define anvil_reinterpret_u64x1_as_u16x4(X) *reinterpret_cast<const uint16x4_t*(&X)
#define anvil_reinterpret_u64x2_as_u16x8(X) *reinterpret_cast<const uint16x8_t*(&X)
#define anvil_reinterpret_u64x4_as_u16x16(X) *reinterpret_cast<const uint16x16_t*(&X)
#define anvil_reinterpret_u64x1_as_s8x8(X) *reinterpret_cast<const int8x8_t*(&X)
#define anvil_reinterpret_u64x2_as_s8x16(X) *reinterpret_cast<const int8x16_t*(&X)
#define anvil_reinterpret_u64x4_as_s8x32(X) *reinterpret_cast<const int8x32_t*(&X)
#define anvil_reinterpret_u64x1_as_u8x8(X) *reinterpret_cast<const uint8x8_t*(&X)
#define anvil_reinterpret_u64x2_as_u8x16(X) *reinterpret_cast<const uint8x16_t*(&X)
#define anvil_reinterpret_u64x4_as_u8x32(X) *reinterpret_cast<const uint8x32_t*(&X)
#define anvil_reinterpret_s32x1_as_f32x1(X) *reinterpret_cast<const float32x1_t*(&X)
#define anvil_reinterpret_s32x1_as_u32x1(X) *reinterpret_cast<const uint32x1_t*(&X)
#define anvil_reinterpret_s32x2_as_f64x1(X) *reinterpret_cast<const float64x1_t*(&X)
#define anvil_reinterpret_s32x4_as_f64x2(X) *reinterpret_cast<const float64x2_t*(&X)
#define anvil_reinterpret_s32x8_as_f64x4(X) *reinterpret_cast<const float64x4_t*(&X)
#define anvil_reinterpret_s32x2_as_f32x2(X) *reinterpret_cast<const float32x2_t*(&X)
#define anvil_reinterpret_s32x4_as_f32x4(X) *reinterpret_cast<const float32x4_t*(&X)
#define anvil_reinterpret_s32x8_as_f32x8(X) *reinterpret_cast<const float32x8_t*(&X)
#define anvil_reinterpret_s32x2_as_s64x1(X) *reinterpret_cast<const int64x1_t*(&X)
#define anvil_reinterpret_s32x4_as_s64x2(X) *reinterpret_cast<const int64x2_t*(&X)
#define anvil_reinterpret_s32x8_as_s64x4(X) *reinterpret_cast<const int64x4_t*(&X)
#define anvil_reinterpret_s32x2_as_u64x1(X) *reinterpret_cast<const uint64x1_t*(&X)
#define anvil_reinterpret_s32x4_as_u64x2(X) *reinterpret_cast<const uint64x2_t*(&X)
#define anvil_reinterpret_s32x8_as_u64x4(X) *reinterpret_cast<const uint64x4_t*(&X)
#define anvil_reinterpret_s32x2_as_u32x2(X) *reinterpret_cast<const uint32x2_t*(&X)
#define anvil_reinterpret_s32x4_as_u32x4(X) *reinterpret_cast<const uint32x4_t*(&X)
#define anvil_reinterpret_s32x8_as_u32x8(X) *reinterpret_cast<const uint32x8_t*(&X)
#define anvil_reinterpret_s32x2_as_s16x4(X) *reinterpret_cast<const int16x4_t*(&X)
#define anvil_reinterpret_s32x4_as_s16x8(X) *reinterpret_cast<const int16x8_t*(&X)
#define anvil_reinterpret_s32x8_as_s16x16(X) *reinterpret_cast<const int16x16_t*(&X)
#define anvil_reinterpret_s32x2_as_u16x4(X) *reinterpret_cast<const uint16x4_t*(&X)
#define anvil_reinterpret_s32x4_as_u16x8(X) *reinterpret_cast<const uint16x8_t*(&X)
#define anvil_reinterpret_s32x8_as_u16x16(X) *reinterpret_cast<const uint16x16_t*(&X)
#define anvil_reinterpret_s32x2_as_s8x8(X) *reinterpret_cast<const int8x8_t*(&X)
#define anvil_reinterpret_s32x4_as_s8x16(X) *reinterpret_cast<const int8x16_t*(&X)
#define anvil_reinterpret_s32x8_as_s8x32(X) *reinterpret_cast<const int8x32_t*(&X)
#define anvil_reinterpret_s32x2_as_u8x8(X) *reinterpret_cast<const uint8x8_t*(&X)
#define anvil_reinterpret_s32x4_as_u8x16(X) *reinterpret_cast<const uint8x16_t*(&X)
#define anvil_reinterpret_s32x8_as_u8x32(X) *reinterpret_cast<const uint8x32_t*(&X)
#define anvil_reinterpret_u32x1_as_f32x1(X) *reinterpret_cast<const float32x1_t*(&X)
#define anvil_reinterpret_u32x1_as_s32x1(X) *reinterpret_cast<const int32x1_t*(&X)
#define anvil_reinterpret_u32x2_as_f64x1(X) *reinterpret_cast<const float64x1_t*(&X)
#define anvil_reinterpret_u32x4_as_f64x2(X) *reinterpret_cast<const float64x2_t*(&X)
#define anvil_reinterpret_u32x8_as_f64x4(X) *reinterpret_cast<const float64x4_t*(&X)
#define anvil_reinterpret_u32x2_as_f32x2(X) *reinterpret_cast<const float32x2_t*(&X)
#define anvil_reinterpret_u32x4_as_f32x4(X) *reinterpret_cast<const float32x4_t*(&X)
#define anvil_reinterpret_u32x8_as_f32x8(X) *reinterpret_cast<const float32x8_t*(&X)
#define anvil_reinterpret_u32x2_as_s64x1(X) *reinterpret_cast<const int64x1_t*(&X)
#define anvil_reinterpret_u32x4_as_s64x2(X) *reinterpret_cast<const int64x2_t*(&X)
#define anvil_reinterpret_u32x8_as_s64x4(X) *reinterpret_cast<const int64x4_t*(&X)
#define anvil_reinterpret_u32x2_as_u64x1(X) *reinterpret_cast<const uint64x1_t*(&X)
#define anvil_reinterpret_u32x4_as_u64x2(X) *reinterpret_cast<const uint64x2_t*(&X)
#define anvil_reinterpret_u32x8_as_u64x4(X) *reinterpret_cast<const uint64x4_t*(&X)
#define anvil_reinterpret_u32x2_as_s32x2(X) *reinterpret_cast<const int32x2_t*(&X)
#define anvil_reinterpret_u32x4_as_s32x4(X) *reinterpret_cast<const int32x4_t*(&X)
#define anvil_reinterpret_u32x8_as_s32x8(X) *reinterpret_cast<const int32x8_t*(&X)
#define anvil_reinterpret_u32x2_as_s16x4(X) *reinterpret_cast<const int16x4_t*(&X)
#define anvil_reinterpret_u32x4_as_s16x8(X) *reinterpret_cast<const int16x8_t*(&X)
#define anvil_reinterpret_u32x8_as_s16x16(X) *reinterpret_cast<const int16x16_t*(&X)
#define anvil_reinterpret_u32x2_as_u16x4(X) *reinterpret_cast<const uint16x4_t*(&X)
#define anvil_reinterpret_u32x4_as_u16x8(X) *reinterpret_cast<const uint16x8_t*(&X)
#define anvil_reinterpret_u32x8_as_u16x16(X) *reinterpret_cast<const uint16x16_t*(&X)
#define anvil_reinterpret_u32x2_as_s8x8(X) *reinterpret_cast<const int8x8_t*(&X)
#define anvil_reinterpret_u32x4_as_s8x16(X) *reinterpret_cast<const int8x16_t*(&X)
#define anvil_reinterpret_u32x8_as_s8x32(X) *reinterpret_cast<const int8x32_t*(&X)
#define anvil_reinterpret_u32x2_as_u8x8(X) *reinterpret_cast<const uint8x8_t*(&X)
#define anvil_reinterpret_u32x4_as_u8x16(X) *reinterpret_cast<const uint8x16_t*(&X)
#define anvil_reinterpret_u32x8_as_u8x32(X) *reinterpret_cast<const uint8x32_t*(&X)
#define anvil_reinterpret_s16x1_as_u16x1(X) *reinterpret_cast<const uint16x1_t*(&X)
#define anvil_reinterpret_s16x4_as_f64x1(X) *reinterpret_cast<const float64x1_t*(&X)
#define anvil_reinterpret_s16x8_as_f64x2(X) *reinterpret_cast<const float64x2_t*(&X)
#define anvil_reinterpret_s16x16_as_f64x4(X) *reinterpret_cast<const float64x4_t*(&X)
#define anvil_reinterpret_s16x4_as_f32x2(X) *reinterpret_cast<const float32x2_t*(&X)
#define anvil_reinterpret_s16x8_as_f32x4(X) *reinterpret_cast<const float32x4_t*(&X)
#define anvil_reinterpret_s16x16_as_f32x8(X) *reinterpret_cast<const float32x8_t*(&X)
#define anvil_reinterpret_s16x4_as_s64x1(X) *reinterpret_cast<const int64x1_t*(&X)
#define anvil_reinterpret_s16x8_as_s64x2(X) *reinterpret_cast<const int64x2_t*(&X)
#define anvil_reinterpret_s16x16_as_s64x4(X) *reinterpret_cast<const int64x4_t*(&X)
#define anvil_reinterpret_s16x4_as_u64x1(X) *reinterpret_cast<const uint64x1_t*(&X)
#define anvil_reinterpret_s16x8_as_u64x2(X) *reinterpret_cast<const uint64x2_t*(&X)
#define anvil_reinterpret_s16x16_as_u64x4(X) *reinterpret_cast<const uint64x4_t*(&X)
#define anvil_reinterpret_s16x4_as_s32x2(X) *reinterpret_cast<const int32x2_t*(&X)
#define anvil_reinterpret_s16x8_as_s32x4(X) *reinterpret_cast<const int32x4_t*(&X)
#define anvil_reinterpret_s16x16_as_s32x8(X) *reinterpret_cast<const int32x8_t*(&X)
#define anvil_reinterpret_s16x4_as_u32x2(X) *reinterpret_cast<const uint32x2_t*(&X)
#define anvil_reinterpret_s16x8_as_u32x4(X) *reinterpret_cast<const uint32x4_t*(&X)
#define anvil_reinterpret_s16x16_as_u32x8(X) *reinterpret_cast<const uint32x8_t*(&X)
#define anvil_reinterpret_s16x4_as_u16x4(X) *reinterpret_cast<const uint16x4_t*(&X)
#define anvil_reinterpret_s16x8_as_u16x8(X) *reinterpret_cast<const uint16x8_t*(&X)
#define anvil_reinterpret_s16x16_as_u16x16(X) *reinterpret_cast<const uint16x16_t*(&X)
#define anvil_reinterpret_s16x4_as_s8x8(X) *reinterpret_cast<const int8x8_t*(&X)
#define anvil_reinterpret_s16x8_as_s8x16(X) *reinterpret_cast<const int8x16_t*(&X)
#define anvil_reinterpret_s16x16_as_s8x32(X) *reinterpret_cast<const int8x32_t*(&X)
#define anvil_reinterpret_s16x4_as_u8x8(X) *reinterpret_cast<const uint8x8_t*(&X)
#define anvil_reinterpret_s16x8_as_u8x16(X) *reinterpret_cast<const uint8x16_t*(&X)
#define anvil_reinterpret_s16x16_as_u8x32(X) *reinterpret_cast<const uint8x32_t*(&X)
#define anvil_reinterpret_u16x1_as_s16x1(X) *reinterpret_cast<const int16x1_t*(&X)
#define anvil_reinterpret_u16x4_as_f64x1(X) *reinterpret_cast<const float64x1_t*(&X)
#define anvil_reinterpret_u16x8_as_f64x2(X) *reinterpret_cast<const float64x2_t*(&X)
#define anvil_reinterpret_u16x16_as_f64x4(X) *reinterpret_cast<const float64x4_t*(&X)
#define anvil_reinterpret_u16x4_as_f32x2(X) *reinterpret_cast<const float32x2_t*(&X)
#define anvil_reinterpret_u16x8_as_f32x4(X) *reinterpret_cast<const float32x4_t*(&X)
#define anvil_reinterpret_u16x16_as_f32x8(X) *reinterpret_cast<const float32x8_t*(&X)
#define anvil_reinterpret_u16x4_as_s64x1(X) *reinterpret_cast<const int64x1_t*(&X)
#define anvil_reinterpret_u16x8_as_s64x2(X) *reinterpret_cast<const int64x2_t*(&X)
#define anvil_reinterpret_u16x16_as_s64x4(X) *reinterpret_cast<const int64x4_t*(&X)
#define anvil_reinterpret_u16x4_as_u64x1(X) *reinterpret_cast<const uint64x1_t*(&X)
#define anvil_reinterpret_u16x8_as_u64x2(X) *reinterpret_cast<const uint64x2_t*(&X)
#define anvil_reinterpret_u16x16_as_u64x4(X) *reinterpret_cast<const uint64x4_t*(&X)
#define anvil_reinterpret_u16x4_as_s32x2(X) *reinterpret_cast<const int32x2_t*(&X)
#define anvil_reinterpret_u16x8_as_s32x4(X) *reinterpret_cast<const int32x4_t*(&X)
#define anvil_reinterpret_u16x16_as_s32x8(X) *reinterpret_cast<const int32x8_t*(&X)
#define anvil_reinterpret_u16x4_as_u32x2(X) *reinterpret_cast<const uint32x2_t*(&X)
#define anvil_reinterpret_u16x8_as_u32x4(X) *reinterpret_cast<const uint32x4_t*(&X)
#define anvil_reinterpret_u16x16_as_u32x8(X) *reinterpret_cast<const uint32x8_t*(&X)
#define anvil_reinterpret_u16x4_as_s16x4(X) *reinterpret_cast<const int16x4_t*(&X)
#define anvil_reinterpret_u16x8_as_s16x8(X) *reinterpret_cast<const int16x8_t*(&X)
#define anvil_reinterpret_u16x16_as_s16x16(X) *reinterpret_cast<const int16x16_t*(&X)
#define anvil_reinterpret_u16x4_as_s8x8(X) *reinterpret_cast<const int8x8_t*(&X)
#define anvil_reinterpret_u16x8_as_s8x16(X) *reinterpret_cast<const int8x16_t*(&X)
#define anvil_reinterpret_u16x16_as_s8x32(X) *reinterpret_cast<const int8x32_t*(&X)
#define anvil_reinterpret_u16x4_as_u8x8(X) *reinterpret_cast<const uint8x8_t*(&X)
#define anvil_reinterpret_u16x8_as_u8x16(X) *reinterpret_cast<const uint8x16_t*(&X)
#define anvil_reinterpret_u16x16_as_u8x32(X) *reinterpret_cast<const uint8x32_t*(&X)
#define anvil_reinterpret_s8x1_as_u8x1(X) *reinterpret_cast<const uint8x1_t*(&X)
#define anvil_reinterpret_s8x8_as_f64x1(X) *reinterpret_cast<const float64x1_t*(&X)
#define anvil_reinterpret_s8x16_as_f64x2(X) *reinterpret_cast<const float64x2_t*(&X)
#define anvil_reinterpret_s8x32_as_f64x4(X) *reinterpret_cast<const float64x4_t*(&X)
#define anvil_reinterpret_s8x8_as_f32x2(X) *reinterpret_cast<const float32x2_t*(&X)
#define anvil_reinterpret_s8x16_as_f32x4(X) *reinterpret_cast<const float32x4_t*(&X)
#define anvil_reinterpret_s8x32_as_f32x8(X) *reinterpret_cast<const float32x8_t*(&X)
#define anvil_reinterpret_s8x8_as_s64x1(X) *reinterpret_cast<const int64x1_t*(&X)
#define anvil_reinterpret_s8x16_as_s64x2(X) *reinterpret_cast<const int64x2_t*(&X)
#define anvil_reinterpret_s8x32_as_s64x4(X) *reinterpret_cast<const int64x4_t*(&X)
#define anvil_reinterpret_s8x8_as_u64x1(X) *reinterpret_cast<const uint64x1_t*(&X)
#define anvil_reinterpret_s8x16_as_u64x2(X) *reinterpret_cast<const uint64x2_t*(&X)
#define anvil_reinterpret_s8x32_as_u64x4(X) *reinterpret_cast<const uint64x4_t*(&X)
#define anvil_reinterpret_s8x8_as_s32x2(X) *reinterpret_cast<const int32x2_t*(&X)
#define anvil_reinterpret_s8x16_as_s32x4(X) *reinterpret_cast<const int32x4_t*(&X)
#define anvil_reinterpret_s8x32_as_s32x8(X) *reinterpret_cast<const int32x8_t*(&X)
#define anvil_reinterpret_s8x8_as_u32x2(X) *reinterpret_cast<const uint32x2_t*(&X)
#define anvil_reinterpret_s8x16_as_u32x4(X) *reinterpret_cast<const uint32x4_t*(&X)
#define anvil_reinterpret_s8x32_as_u32x8(X) *reinterpret_cast<const uint32x8_t*(&X)
#define anvil_reinterpret_s8x8_as_s16x4(X) *reinterpret_cast<const int16x4_t*(&X)
#define anvil_reinterpret_s8x16_as_s16x8(X) *reinterpret_cast<const int16x8_t*(&X)
#define anvil_reinterpret_s8x32_as_s16x16(X) *reinterpret_cast<const int16x16_t*(&X)
#define anvil_reinterpret_s8x8_as_u16x4(X) *reinterpret_cast<const uint16x4_t*(&X)
#define anvil_reinterpret_s8x16_as_u16x8(X) *reinterpret_cast<const uint16x8_t*(&X)
#define anvil_reinterpret_s8x32_as_u16x16(X) *reinterpret_cast<const uint16x16_t*(&X)
#define anvil_reinterpret_s8x8_as_u8x8(X) *reinterpret_cast<const uint8x8_t*(&X)
#define anvil_reinterpret_s8x16_as_u8x16(X) *reinterpret_cast<const uint8x16_t*(&X)
#define anvil_reinterpret_s8x32_as_u8x32(X) *reinterpret_cast<const uint8x32_t*(&X)
#define anvil_reinterpret_u8x1_as_s8x1(X) *reinterpret_cast<const int8x1_t*(&X)
#define anvil_reinterpret_u8x8_as_f64x1(X) *reinterpret_cast<const float64x1_t*(&X)
#define anvil_reinterpret_u8x16_as_f64x2(X) *reinterpret_cast<const float64x2_t*(&X)
#define anvil_reinterpret_u8x32_as_f64x4(X) *reinterpret_cast<const float64x4_t*(&X)
#define anvil_reinterpret_u8x8_as_f32x2(X) *reinterpret_cast<const float32x2_t*(&X)
#define anvil_reinterpret_u8x16_as_f32x4(X) *reinterpret_cast<const float32x4_t*(&X)
#define anvil_reinterpret_u8x32_as_f32x8(X) *reinterpret_cast<const float32x8_t*(&X)
#define anvil_reinterpret_u8x8_as_s64x1(X) *reinterpret_cast<const int64x1_t*(&X)
#define anvil_reinterpret_u8x16_as_s64x2(X) *reinterpret_cast<const int64x2_t*(&X)
#define anvil_reinterpret_u8x32_as_s64x4(X) *reinterpret_cast<const int64x4_t*(&X)
#define anvil_reinterpret_u8x8_as_u64x1(X) *reinterpret_cast<const uint64x1_t*(&X)
#define anvil_reinterpret_u8x16_as_u64x2(X) *reinterpret_cast<const uint64x2_t*(&X)
#define anvil_reinterpret_u8x32_as_u64x4(X) *reinterpret_cast<const uint64x4_t*(&X)
#define anvil_reinterpret_u8x8_as_s32x2(X) *reinterpret_cast<const int32x2_t*(&X)
#define anvil_reinterpret_u8x16_as_s32x4(X) *reinterpret_cast<const int32x4_t*(&X)
#define anvil_reinterpret_u8x32_as_s32x8(X) *reinterpret_cast<const int32x8_t*(&X)
#define anvil_reinterpret_u8x8_as_u32x2(X) *reinterpret_cast<const uint32x2_t*(&X)
#define anvil_reinterpret_u8x16_as_u32x4(X) *reinterpret_cast<const uint32x4_t*(&X)
#define anvil_reinterpret_u8x32_as_u32x8(X) *reinterpret_cast<const uint32x8_t*(&X)
#define anvil_reinterpret_u8x8_as_s16x4(X) *reinterpret_cast<const int16x4_t*(&X)
#define anvil_reinterpret_u8x16_as_s16x8(X) *reinterpret_cast<const int16x8_t*(&X)
#define anvil_reinterpret_u8x32_as_s16x16(X) *reinterpret_cast<const int16x16_t*(&X)
#define anvil_reinterpret_u8x8_as_u16x4(X) *reinterpret_cast<const uint16x4_t*(&X)
#define anvil_reinterpret_u8x16_as_u16x8(X) *reinterpret_cast<const uint16x8_t*(&X)
#define anvil_reinterpret_u8x32_as_u16x16(X) *reinterpret_cast<const uint16x16_t*(&X)
#define anvil_reinterpret_u8x8_as_s8x8(X) *reinterpret_cast<const int8x8_t*(&X)
#define anvil_reinterpret_u8x16_as_s8x16(X) *reinterpret_cast<const int8x16_t*(&X)
#define anvil_reinterpret_u8x32_as_s8x32(X) *reinterpret_cast<const int8x32_t*(&X)

// convert

#define anvil_convert_f64x1_to_f32x1(X) static_cast<float32x1_t>(X)
#define anvil_convert_f64x1_to_s64x1(X) static_cast<int64x1_t>(X)
#define anvil_convert_f64x1_to_u64x1(X) static_cast<uint64x1_t>(X)
#define anvil_convert_f64x1_to_s32x1(X) static_cast<int32x1_t>(X)
#define anvil_convert_f64x1_to_u32x1(X) static_cast<uint32x1_t>(X)
#define anvil_convert_f64x1_to_s16x1(X) static_cast<int16x1_t>(X)
#define anvil_convert_f64x1_to_u16x1(X) static_cast<uint16x1_t>(X)
#define anvil_convert_f64x1_to_s8x1(X) static_cast<int8x1_t>(X)
#define anvil_convert_f64x1_to_u8x1(X) static_cast<uint8x1_t>(X)
#define anvil_convert_f32x1_to_f64x1(X) static_cast<float64x1_t>(X)
#define anvil_convert_f32x1_to_s64x1(X) static_cast<int64x1_t>(X)
#define anvil_convert_f32x1_to_u64x1(X) static_cast<uint64x1_t>(X)
#define anvil_convert_f32x1_to_s32x1(X) static_cast<int32x1_t>(X)
#define anvil_convert_f32x1_to_u32x1(X) static_cast<uint32x1_t>(X)
#define anvil_convert_f32x1_to_s16x1(X) static_cast<int16x1_t>(X)
#define anvil_convert_f32x1_to_u16x1(X) static_cast<uint16x1_t>(X)
#define anvil_convert_f32x1_to_s8x1(X) static_cast<int8x1_t>(X)
#define anvil_convert_f32x1_to_u8x1(X) static_cast<uint8x1_t>(X)
#define anvil_convert_s64x1_to_f64x1(X) static_cast<float64x1_t>(X)
#define anvil_convert_s64x1_to_f32x1(X) static_cast<float32x1_t>(X)
#define anvil_convert_s64x1_to_u64x1(X) static_cast<uint64x1_t>(X)
#define anvil_convert_s64x1_to_s32x1(X) static_cast<int32x1_t>(X)
#define anvil_convert_s64x1_to_u32x1(X) static_cast<uint32x1_t>(X)
#define anvil_convert_s64x1_to_s16x1(X) static_cast<int16x1_t>(X)
#define anvil_convert_s64x1_to_u16x1(X) static_cast<uint16x1_t>(X)
#define anvil_convert_s64x1_to_s8x1(X) static_cast<int8x1_t>(X)
#define anvil_convert_s64x1_to_u8x1(X) static_cast<uint8x1_t>(X)
#define anvil_convert_u64x1_to_f64x1(X) static_cast<float64x1_t>(X)
#define anvil_convert_u64x1_to_f32x1(X) static_cast<float32x1_t>(X)
#define anvil_convert_u64x1_to_s64x1(X) static_cast<int64x1_t>(X)
#define anvil_convert_u64x1_to_s32x1(X) static_cast<int32x1_t>(X)
#define anvil_convert_u64x1_to_u32x1(X) static_cast<uint32x1_t>(X)
#define anvil_convert_u64x1_to_s16x1(X) static_cast<int16x1_t>(X)
#define anvil_convert_u64x1_to_u16x1(X) static_cast<uint16x1_t>(X)
#define anvil_convert_u64x1_to_s8x1(X) static_cast<int8x1_t>(X)
#define anvil_convert_u64x1_to_u8x1(X) static_cast<uint8x1_t>(X)
#define anvil_convert_s32x1_to_f64x1(X) static_cast<float64x1_t>(X)
#define anvil_convert_s32x1_to_f32x1(X) static_cast<float32x1_t>(X)
#define anvil_convert_s32x1_to_s64x1(X) static_cast<int64x1_t>(X)
#define anvil_convert_s32x1_to_u64x1(X) static_cast<uint64x1_t>(X)
#define anvil_convert_s32x1_to_u32x1(X) static_cast<uint32x1_t>(X)
#define anvil_convert_s32x1_to_s16x1(X) static_cast<int16x1_t>(X)
#define anvil_convert_s32x1_to_u16x1(X) static_cast<uint16x1_t>(X)
#define anvil_convert_s32x1_to_s8x1(X) static_cast<int8x1_t>(X)
#define anvil_convert_s32x1_to_u8x1(X) static_cast<uint8x1_t>(X)
#define anvil_convert_u32x1_to_f64x1(X) static_cast<float64x1_t>(X)
#define anvil_convert_u32x1_to_f32x1(X) static_cast<float32x1_t>(X)
#define anvil_convert_u32x1_to_s64x1(X) static_cast<int64x1_t>(X)
#define anvil_convert_u32x1_to_u64x1(X) static_cast<uint64x1_t>(X)
#define anvil_convert_u32x1_to_s32x1(X) static_cast<int32x1_t>(X)
#define anvil_convert_u32x1_to_s16x1(X) static_cast<int16x1_t>(X)
#define anvil_convert_u32x1_to_u16x1(X) static_cast<uint16x1_t>(X)
#define anvil_convert_u32x1_to_s8x1(X) static_cast<int8x1_t>(X)
#define anvil_convert_u32x1_to_u8x1(X) static_cast<uint8x1_t>(X)
#define anvil_convert_s16x1_to_f64x1(X) static_cast<float64x1_t>(X)
#define anvil_convert_s16x1_to_f32x1(X) static_cast<float32x1_t>(X)
#define anvil_convert_s16x1_to_s64x1(X) static_cast<int64x1_t>(X)
#define anvil_convert_s16x1_to_u64x1(X) static_cast<uint64x1_t>(X)
#define anvil_convert_s16x1_to_s32x1(X) static_cast<int32x1_t>(X)
#define anvil_convert_s16x1_to_u32x1(X) static_cast<uint32x1_t>(X)
#define anvil_convert_s16x1_to_u16x1(X) static_cast<uint16x1_t>(X)
#define anvil_convert_s16x1_to_s8x1(X) static_cast<int8x1_t>(X)
#define anvil_convert_s16x1_to_u8x1(X) static_cast<uint8x1_t>(X)
#define anvil_convert_u16x1_to_f64x1(X) static_cast<float64x1_t>(X)
#define anvil_convert_u16x1_to_f32x1(X) static_cast<float32x1_t>(X)
#define anvil_convert_u16x1_to_s64x1(X) static_cast<int64x1_t>(X)
#define anvil_convert_u16x1_to_u64x1(X) static_cast<uint64x1_t>(X)
#define anvil_convert_u16x1_to_s32x1(X) static_cast<int32x1_t>(X)
#define anvil_convert_u16x1_to_u32x1(X) static_cast<uint32x1_t>(X)
#define anvil_convert_u16x1_to_s16x1(X) static_cast<int16x1_t>(X)
#define anvil_convert_u16x1_to_s8x1(X) static_cast<int8x1_t>(X)
#define anvil_convert_u16x1_to_u8x1(X) static_cast<uint8x1_t>(X)
#define anvil_convert_s8x1_to_f64x1(X) static_cast<float64x1_t>(X)
#define anvil_convert_s8x1_to_f32x1(X) static_cast<float32x1_t>(X)
#define anvil_convert_s8x1_to_s64x1(X) static_cast<int64x1_t>(X)
#define anvil_convert_s8x1_to_u64x1(X) static_cast<uint64x1_t>(X)
#define anvil_convert_s8x1_to_s32x1(X) static_cast<int32x1_t>(X)
#define anvil_convert_s8x1_to_u32x1(X) static_cast<uint32x1_t>(X)
#define anvil_convert_s8x1_to_s16x1(X) static_cast<int16x1_t>(X)
#define anvil_convert_s8x1_to_u16x1(X) static_cast<uint16x1_t>(X)
#define anvil_convert_s8x1_to_u8x1(X) static_cast<uint8x1_t>(X)
#define anvil_convert_u8x1_to_f64x1(X) static_cast<float64x1_t>(X)
#define anvil_convert_u8x1_to_f32x1(X) static_cast<float32x1_t>(X)
#define anvil_convert_u8x1_to_s64x1(X) static_cast<int64x1_t>(X)
#define anvil_convert_u8x1_to_u64x1(X) static_cast<uint64x1_t>(X)
#define anvil_convert_u8x1_to_s32x1(X) static_cast<int32x1_t>(X)
#define anvil_convert_u8x1_to_u32x1(X) static_cast<uint32x1_t>(X)
#define anvil_convert_u8x1_to_s16x1(X) static_cast<int16x1_t>(X)
#define anvil_convert_u8x1_to_u16x1(X) static_cast<uint16x1_t>(X)
#define anvil_convert_u8x1_to_s8x1(X) static_cast<int8x1_t>(X)

#define anvil_convert_f32x4_to_s32x4(X) _mm_cvtpd_epi32
#define anvil_convert_s32x4_to_f32x4(X) _mm_cvtepi32_pd 
#define anvil_convert_f32x8_to_s32x8(X) _mm256_cvtpd_epi32
#define anvil_convert_s32x8_to_f32x8(X) _mm256_cvtepi32_pd 
#define anvil_convert_f32x4_to_f64x4(X) _mm256_cvtps_pd
#define anvil_convert_f64x4_to_f32x4(X) _mm256_cvtpd_ps 
//! \todo Remaining conversions

// Load / store / set

#define anvil_load_undefined_f64x2() _mm_undefined_pd()
#define anvil_load_undefined_f64x4() _mm256_undefined_pd()
#define anvil_load_zero_f64x2() _mm_setzero_pd()
#define anvil_load_zero_f64x4() _mm256_setzero_pd()
#define anvil_load_scalar_f64x2(X) _mm_set1_pd(X)
#define anvil_load_scalar_f64x4(X) _mm256_set1_pd(X)
#define anvil_load_f64x2(P) _mm_loadu_pd(P)
#define anvil_load_f64x4(P) _mm256_loadu_pd(P)
#define anvil_store_f64x2(P,X) _mm_storeu_pd(P,X)
#define anvil_store_f64x4(P,X) _mm256_storeu_pd(P,X)
#define anvil_load_undefined_f32x4() _mm_undefined_ps()
#define anvil_load_undefined_f32x8() _mm256_undefined_ps()
#define anvil_load_zero_f32x4() _mm_setzero_ps()
#define anvil_load_zero_f32x8() _mm256_setzero_ps()
#define anvil_load_scalar_f32x4(X) _mm_set1_ps(X)
#define anvil_load_scalar_f32x8(X) _mm256_set1_ps(X)
#define anvil_load_f32x4(P) _mm_loadu_ps(P)
#define anvil_load_f32x8(P) _mm256_loadu_ps(P)
#define anvil_store_f32x4(P,X) _mm_storeu_ps(P,X)
#define anvil_store_f32x8(P,X) _mm256_storeu_ps(P,X)
#define anvil_load_undefined_s64x2() _mm_undefined_si128()
#define anvil_load_undefined_s64x4() _mm256_undefined_si256()
#define anvil_load_zero_s64x2() _mm_setzero_si128()
#define anvil_load_zero_s64x4() _mm256_setzero_si256()
#define anvil_load_scalar_s64x2(X) _mm_set1_epi64x(X)
#define anvil_load_scalar_s64x4(X) _mm256_set1_epi64x(X)
#define anvil_load_s64x2(P) _mm_loadu_si128(reinterpret_cast<const __m128i*>(P))
#define anvil_load_s64x4(P) _mm256_loadu_si256(reinterpret_cast<const __m256i*>(P))
#define anvil_store_s64x2(P,X) _mm_storeu_si128(reinterpret_cast<__m128i*>(P),X)
#define anvil_store_s64x4(P,X) _mm256_storeu_si256(reinterpret_cast<__m256i*>(P),X)
#define anvil_load_undefined_u64x2() _mm_undefined_si128()
#define anvil_load_undefined_u64x4() _mm256_undefined_si256()
#define anvil_load_zero_u64x2() _mm_setzero_si128()
#define anvil_load_zero_u64x4() _mm256_setzero_si256()
#define anvil_load_scalar_u64x2(X) anvil_load_scalar_s64x2(*reinterpret_cast<const int64x1_t*>(&X))
#define anvil_load_scalar_u64x4(X) anvil_load_scalar_s64x4(*reinterpret_cast<const int64x1_t*>(&X))
#define anvil_load_u64x2(P) _mm_loadu_si128(reinterpret_cast<const __m128i*>(P))
#define anvil_load_u64x4(P) _mm256_loadu_si256(reinterpret_cast<const __m256i*>(P))
#define anvil_store_u64x2(P,X) _mm_storeu_si128(reinterpret_cast<__m128i*>(P),X)
#define anvil_store_u64x4(P,X) _mm256_storeu_si256(reinterpret_cast<__m256i*>(P),X)
#define anvil_load_undefined_s32x4() _mm_undefined_si128()
#define anvil_load_undefined_s32x8() _mm256_undefined_si256()
#define anvil_load_zero_s32x4() _mm_setzero_si128()
#define anvil_load_zero_s32x8() _mm256_setzero_si256()
#define anvil_load_scalar_s32x4(X) _mm_set1_epi32(X)
#define anvil_load_scalar_s32x8(X) _mm256_set1_epi32(X)
#define anvil_load_s32x4(P) _mm_loadu_si128(reinterpret_cast<const __m128i*>(P))
#define anvil_load_s32x8(P) _mm256_loadu_si256(reinterpret_cast<const __m256i*>(P))
#define anvil_store_s32x4(P,X) _mm_storeu_si128(reinterpret_cast<__m128i*>(P),X)
#define anvil_store_s32x8(P,X) _mm256_storeu_si256(reinterpret_cast<__m256i*>(P),X)
#define anvil_load_undefined_u32x4() _mm_undefined_si128()
#define anvil_load_undefined_u32x8() _mm256_undefined_si256()
#define anvil_load_zero_u32x4() _mm_setzero_si128()
#define anvil_load_zero_u32x8() _mm256_setzero_si256()
#define anvil_load_scalar_u32x4(X) anvil_load_scalar_s32x4(*reinterpret_cast<const int32x1_t*>(&X))
#define anvil_load_scalar_u32x8(X) anvil_load_scalar_s32x8(*reinterpret_cast<const int32x1_t*>(&X))
#define anvil_load_u32x4(P) _mm_loadu_si128(reinterpret_cast<const __m128i*>(P))
#define anvil_load_u32x8(P) _mm256_loadu_si256(reinterpret_cast<const __m256i*>(P))
#define anvil_store_u32x4(P,X) _mm_storeu_si128(reinterpret_cast<__m128i*>(P),X)
#define anvil_store_u32x8(P,X) _mm256_storeu_si256(reinterpret_cast<__m256i*>(P),X)
#define anvil_load_undefined_s16x8() _mm_undefined_si128()
#define anvil_load_undefined_s16x16() _mm256_undefined_si256()
#define anvil_load_zero_s16x8() _mm_setzero_si128()
#define anvil_load_zero_s16x16() _mm256_setzero_si256()
#define anvil_load_scalar_s16x8(X) _mm_set1_epi16(X)
#define anvil_load_scalar_s16x16(X) _mm256_set1_epi16(X)
#define anvil_load_s16x8(P) _mm_loadu_si128(reinterpret_cast<const __m128i*>(P))
#define anvil_load_s16x16(P) _mm256_loadu_si256(reinterpret_cast<const __m256i*>(P))
#define anvil_store_s16x8(P,X) _mm_storeu_si128(reinterpret_cast<__m128i*>(P),X)
#define anvil_store_s16x16(P,X) _mm256_storeu_si256(reinterpret_cast<__m256i*>(P),X)
#define anvil_load_undefined_u16x8() _mm_undefined_si128()
#define anvil_load_undefined_u16x16() _mm256_undefined_si256()
#define anvil_load_zero_u16x8() _mm_setzero_si128()
#define anvil_load_zero_u16x16() _mm256_setzero_si256()
#define anvil_load_scalar_u16x8(X) anvil_load_scalar_s16x8(*reinterpret_cast<const int16x1_t*>(&X))
#define anvil_load_scalar_u16x16(X) anvil_load_scalar_s16x16(*reinterpret_cast<const int16x1_t*>(&X))
#define anvil_load_u16x8(P) _mm_loadu_si128(reinterpret_cast<const __m128i*>(P))
#define anvil_load_u16x16(P) _mm256_loadu_si256(reinterpret_cast<const __m256i*>(P))
#define anvil_store_u16x8(P,X) _mm_storeu_si128(reinterpret_cast<__m128i*>(P),X)
#define anvil_store_u16x16(P,X) _mm256_storeu_si256(reinterpret_cast<__m256i*>(P),X)
#define anvil_load_undefined_s8x16() _mm_undefined_si128()
#define anvil_load_undefined_s8x32() _mm256_undefined_si256()
#define anvil_load_zero_s8x16() _mm_setzero_si128()
#define anvil_load_zero_s8x32() _mm256_setzero_si256()
#define anvil_load_scalar_s8x16(X) _mm_set1_epi8(X)
#define anvil_load_scalar_s8x32(X) _mm256_set1_epi8(X)
#define anvil_load_s8x16(P) _mm_loadu_si128(reinterpret_cast<const __m128i*>(P))
#define anvil_load_s8x32(P) _mm256_loadu_si256(reinterpret_cast<const __m256i*>(P))
#define anvil_store_s8x16(P,X) _mm_storeu_si128(reinterpret_cast<__m128i*>(P),X)
#define anvil_store_s8x32(P,X) _mm256_storeu_si256(reinterpret_cast<__m256i*>(P),X)
#define anvil_load_undefined_u8x16() _mm_undefined_si128()
#define anvil_load_undefined_u8x32() _mm256_undefined_si256()
#define anvil_load_zero_u8x16() _mm_setzero_si128()
#define anvil_load_zero_u8x32() _mm256_setzero_si256()
#define anvil_load_scalar_u8x16(X) anvil_load_scalar_s8x16(*reinterpret_cast<const int8x1_t*>(&X))
#define anvil_load_scalar_u8x32(X) anvil_load_scalar_s8x32(*reinterpret_cast<const int8x1_t*>(&X))
#define anvil_load_u8x16(P) _mm_loadu_si128(reinterpret_cast<const __m128i*>(P))
#define anvil_load_u8x32(P) _mm256_loadu_si256(reinterpret_cast<const __m256i*>(P))
#define anvil_store_u8x16(P,X) _mm_storeu_si128(reinterpret_cast<__m128i*>(P),X)
#define anvil_store_u8x32(P,X) _mm256_storeu_si256(reinterpret_cast<__m256i*>(P),X)

// Split

#define anvil_halflo_f64x4(X) _mm256_extractf128_pd(X, 0)
#define anvil_halfhi_f64x4(X) _mm256_extractf128_pd(X, 1)

#define anvil_halflo_f32x4(X) _mm256_extractf128_ps(X, 0)
#define anvil_halfhi_f32x4(X) _mm256_extractf128_ps(X, 1)

#define anvil_halflo_s64x4(X) _mm256_extractf128_si256(X, 0)
#define anvil_halfhi_s64x4(X) _mm256_extractf128_si256(X, 1)

#define anvil_halflo_u64x4(X) _mm256_extractf128_si256(X, 0)
#define anvil_halfhi_u64x4(X) _mm256_extractf128_si256(X, 1)

#define anvil_halflo_s32x8(X) _mm256_extractf128_si256(X, 0)
#define anvil_halfhi_s32x8(X) _mm256_extractf128_si256(X, 1)

#define anvil_halflo_u32x8(X) _mm256_extractf128_si256(X, 0)
#define anvil_halfhi_u32x8(X) _mm256_extractf128_si256(X, 1)

#define anvil_halflo_s16x16(X) _mm256_extractf128_si256(X, 0)
#define anvil_halfhi_s16x16(X) _mm256_extractf128_si256(X, 1)

#define anvil_halflo_u16x16(X) _mm256_extractf128_si256(X, 0)
#define anvil_halfhi_u16x16(X) _mm256_extractf128_si256(X, 1)

#define anvil_halflo_s8x32(X) _mm256_extractf128_si256(X, 0)
#define anvil_halfhi_s8x32(X) _mm256_extractf128_si256(X, 1)

#define anvil_halflo_u8x32(X) _mm256_extractf128_si256(X, 0)
#define anvil_halfhi_u8x32(X) _mm256_extractf128_si256(X, 1)

// Combine

#define anvil_combine_f64x4(X,Y) _mm256_set_m128d(Y,X)
#define anvil_combine_f32x8(X,Y) _mm256_set_m128(Y,X)
#define anvil_combine_s64x4(X,Y) _mm256_set_m128i(Y,X)
#define anvil_combine_u64x4(X,Y) _mm256_set_m128i(Y,X)
#define anvil_combine_s32x8(X,Y) _mm256_set_m128i(Y,X)
#define anvil_combine_u32x8(X,Y) _mm256_set_m128i(Y,X)
#define anvil_combine_s16x16(X,Y) _mm256_set_m128i(Y,X)
#define anvil_combine_u16x16(X,Y) _mm256_set_m128i(Y,X)
#define anvil_combine_s8x32(X,Y) _mm256_set_m128i(Y,X)
#define anvil_combine_u8x32(X,Y) _mm256_set_m128i(Y,X)

// Not

#define anvil_not_f64x1(X) anvil_reinterpret_s64x1_as_f64x1(~(anvil_reinterpret_f64x1_as_s64x1(X)))
static ANVIL_STRONG_INLINE float64x2_t ANVIL_SIMD_CALL anvil_not_f64x2(const register float64x2_t x) { return _mm_xor_pd(x, _mm_cmpeq_pd(x, x)); }
static ANVIL_STRONG_INLINE float64x4_t ANVIL_SIMD_CALL anvil_not_f64x4(const register float64x4_t x) { return _mm256_xor_pd(x, _mm256_cmp_pd(x, x, _CMP_EQ_OQ)); }

#define anvil_not_f32x1(X) anvil_reinterpret_s32x1_as_f32x1(~(anvil_reinterpret_f32x1_as_s32x1(X)))
#define anvil_not_f32x2(X) anvil_not_f32x4(X)
static ANVIL_STRONG_INLINE float32x4_t ANVIL_SIMD_CALL anvil_not_f32x4(const register float32x4_t x) { return _mm_xor_ps(x, _mm_cmpeq_ps(x, x)); }
static ANVIL_STRONG_INLINE float32x8_t ANVIL_SIMD_CALL anvil_not_f32x8(const register float32x8_t x) { return _mm256_xor_ps(x, _mm256_cmp_ps(x, x, _CMP_EQ_OQ)); }

#define anvil_not_s64x1(X) (~X)
static ANVIL_STRONG_INLINE int64x2_t ANVIL_SIMD_CALL anvil_not_s64x2(const register int64x2_t x) { return _mm_castpd_si128(_mm_xor_pd(_mm_castsi128_pd(x), _mm_cmpeq_pd(_mm_castsi128_pd(x), _mm_castsi128_pd(x)))); }
static ANVIL_STRONG_INLINE int64x4_t ANVIL_SIMD_CALL anvil_not_s64x4(const register int64x4_t x) { return _mm256_castpd_si256(_mm256_xor_pd(_mm256_castsi256_pd(x), _mm256_cmp_pd(_mm256_castsi256_pd(x), _mm256_castsi256_pd(x), _CMP_EQ_OQ))); }

#define anvil_not_u64x1(X) (~X)
#define anvil_not_u64x2(X) anvil_not_s64x2(X)
#define anvil_not_u64x4(X) anvil_not_s64x4(X)

#define anvil_not_s32x1(X) (~X)
#define anvil_not_s32x2(X) anvil_not_s32x4(X)
static ANVIL_STRONG_INLINE int32x4_t ANVIL_SIMD_CALL anvil_not_s32x4(const register int32x4_t x) { return _mm_xor_si128(x, _mm_cmpeq_epi32(x, x)); }
static ANVIL_STRONG_INLINE int32x8_t ANVIL_SIMD_CALL anvil_not_s32x8(const register int32x8_t x) { return _mm256_xor_si256(x, _mm256_cmpeq_epi32(x, x)); }

#define anvil_not_u32x1(X) (~X)
#define anvil_not_u32x2(X) anvil_not_u32x4(X)
#define anvil_not_u32x4(X) anvil_not_s32x4(X)
#define anvil_not_u32x8(X) anvil_not_s32x8(X)

#define anvil_not_s16x1(X) (~X)
#define anvil_not_16x4(X) anvil_not_16x8(X)
static ANVIL_STRONG_INLINE int16x8_t ANVIL_SIMD_CALL anvil_not_s16x8(const register int16x8_t x) { return _mm_xor_si128(x, _mm_cmpeq_epi16(x, x)); }
static ANVIL_STRONG_INLINE int16x16_t ANVIL_SIMD_CALL anvil_not_s16x16(const register int16x16_t x) { return _mm256_xor_si256(x, _mm256_cmpeq_epi16(x, x)); }

#define anvil_not_u16x1(X) (~X)
#define anvil_not_u16x4(X) anvil_not_u16x8(X)
#define anvil_not_u16x8(X) anvil_not_16x8(X)
#define anvil_not_u16x16(X) anvil_not_16x16(X)

#define anvil_not_sx1(X) (~X)
#define anvil_not_s8x8(X) anvil_not_s8x16(X)
static ANVIL_STRONG_INLINE int8x16_t ANVIL_SIMD_CALL anvil_not_s8x16(const register int8x16_t x) { return _mm_xor_si128(x, _mm_cmpeq_epi8(x, x)); }
static ANVIL_STRONG_INLINE int8x32_t ANVIL_SIMD_CALL anvil_not_s8x32(const register int8x32_t x) { return _mm256_xor_si256(x, _mm256_cmpeq_epi8(x, x)); }

#define anvil_not_u8x1(X) (~X)
#define anvil_not_u8x8(X) anvil_not_u8x16(X)
#define anvil_not_u8x16(X) anvil_not_s8x16(X)
#define anvil_not_u8x32(X) anvil_not_s8x32(X)

// Cmp

#define anvil_cmpeq_s32x4(X,Y) _mm_cmpeq_epi32(X,Y)
#define anvil_cmpneq_s32x4(X,Y) anvil_not_s32x4(_mm_cmpeq_epi32(X,Y))
#define anvil_cmpgt_s32x4(X,Y) _mm_cmpgt_epi32(X,Y)
#define anvil_cmplt_s32x4(X,Y) _mm_cmpgt_epi32(Y,X)
#define anvil_cmpge_s32x4(X,Y) anvil_not_s32x4(_mm_cmpgt_epi32(Y,X))
#define anvil_cmple_s32x4(X,Y) anvil_not_s32x4(_mm_cmpgt_epi32(Y,X))

#define anvil_cmpeq_s32x8(X,Y) _mm256_cmpeq_epi32(X,Y)
#define anvil_cmpneq_s32x8(X,Y) anvil_not_s32x4(_mm256_cmpeq_epi32(X,Y))
#define anvil_cmpgt_s32x8(X,Y) _mm256_cmpgt_epi32(X,Y)
#define anvil_cmplt_s32x8(X,Y) _mm256_cmpgt_epi32(Y,X)
#define anvil_cmpge_s32x8(X,Y) anvil_not_s32x8(_mm256_cmpgt_epi32(Y,X))
#define anvil_cmple_s32x8(X,Y) anvil_not_s32x8(_mm256_cmpgt_epi32(X,Y))

// Add

#define anvil_add_f64x1(X,Y) (X + Y)
#define anvil_add_f64x2(X,Y) _mm_add_pd(X,Y)
#define anvil_add_f64x4(X,Y) _mm256_add_pd(X,Y)

#define anvil_add_f32x1(X,Y) (X + Y)
#define anvil_add_f32x2(X,Y) anvil_add_f32x4(X + Y)
#define anvil_add_f32x4(X,Y) _mm_add_ps(X,Y)
#define anvil_add_f32x8(X,Y) _mm256_add_ps(X,Y)

#define anvil_add_s64x1(X,Y) (X + Y)
#define anvil_add_s64x2(X,Y) _mm_add_epi64(X,Y)
#define anvil_add_s64x4(X,Y) _mm256_add_epi64(X,Y)

#define anvil_add_u64x1(X,Y) (X + Y)
#define anvil_add_u64x2(X,Y) _mm_add_epi64(X,Y)
#define anvil_add_u64x4(X,Y) _mm256_add_epi64(X,Y)

#define anvil_add_s32x1(X,Y) (X + Y)
#define anvil_add_s32x2(X,Y) anvil_add_s32x4(X + Y)
#define anvil_add_s32x4(X,Y) _mm_add_epi32(X,Y)
#define anvil_add_s32x8(X,Y) _mm256_add_epi32(X,Y)

#define anvil_add_u32x1(X,Y) (X + Y)
#define anvil_add_u32x2(X,Y) anvil_add_u32x4(X + Y)
#define anvil_add_u32x4(X,Y) _mm_add_epi32(X,Y)
#define anvil_add_u32x8(X,Y) _mm256_add_epi32(X,Y)

#define anvil_add_s16x1(X,Y) (X + Y)
#define anvil_add_s16x4(X,Y) anvil_add_s16x8(X + Y)
#define anvil_add_s16x8(X,Y) _mm_add_epi16(X,Y)
#define anvil_add_s16x16(X,Y) _mm256_add_epi16(X,Y)

#define anvil_add_u16x1(X,Y) (X + Y)
#define anvil_add_u16x4(X,Y) anvil_add_u16x8(X + Y)
#define anvil_add_u16x8(X,Y) _mm_add_epi16(X,Y)
#define anvil_add_u16x16(X,Y) _mm256_add_epi16(X,Y)

#define anvil_add_s8x1(X,Y) (X + Y)
#define anvil_add_s8x8(X,Y) anvil_add_s8x16(X + Y)
#define anvil_add_s8x16(X,Y) _mm_add_epi8(X,Y)
#define anvil_add_s8x32(X,Y) _mm256_add_epi8(X,Y)

#define anvil_add_u8x1(X,Y) (X + Y)
#define anvil_add_u8x8(X,Y) anvil_add_u8x16(X + Y)
#define anvil_add_u8x16(X,Y) _mm_add_epi8(X,Y)
#define anvil_add_u8x32(X,Y) _mm256_add_epi8(X,Y)

// Sub

#define anvil_sub_f64x1(X,Y) (X + Y)
#define anvil_sub_f64x2(X,Y) _mm_sub_pd(X,Y)
#define anvil_sub_f64x4(X,Y) _mm256_sub_pd(X,Y)

#define anvil_sub_f32x1(X,Y) (X + Y)
#define anvil_sub_f32x2(X,Y) anvil_sub_f32x4(X + Y)
#define anvil_sub_f32x4(X,Y) _mm_sub_ps(X,Y)
#define anvil_sub_f32x8(X,Y) _mm256_sub_ps(X,Y)

#define anvil_sub_s64x1(X,Y) (X + Y)
#define anvil_sub_s64x2(X,Y) _mm_sub_epi64(X,Y)
#define anvil_sub_s64x4(X,Y) _mm256_sub_epi64(X,Y)

#define anvil_sub_u64x1(X,Y) (X + Y)
#define anvil_sub_u64x2(X,Y) _mm_sub_epi64(X,Y)
#define anvil_sub_u64x4(X,Y) _mm256_sub_epi64(X,Y)

#define anvil_sub_s32x1(X,Y) (X + Y)
#define anvil_sub_s32x2(X,Y) anvil_sub_s32x4(X + Y)
#define anvil_sub_s32x4(X,Y) _mm_sub_epi32(X,Y)
#define anvil_sub_s32x8(X,Y) _mm256_sub_epi32(X,Y)

#define anvil_sub_u32x1(X,Y) (X + Y)
#define anvil_sub_u32x2(X,Y) anvil_sub_u32x4(X + Y)
#define anvil_sub_u32x4(X,Y) _mm_sub_epi32(X,Y)
#define anvil_sub_u32x8(X,Y) _mm256_sub_epi32(X,Y)

#define anvil_sub_s16x1(X,Y) (X + Y)
#define anvil_sub_s16x4(X,Y) anvil_sub_s16x8(X + Y)
#define anvil_sub_s16x8(X,Y) _mm_sub_epi16(X,Y)
#define anvil_sub_s16x16(X,Y) _mm256_sub_epi16(X,Y)

#define anvil_sub_u16x1(X,Y) (X + Y)
#define anvil_sub_u16x4(X,Y) anvil_sub_u16x8(X + Y)
#define anvil_sub_u16x8(X,Y) _mm_sub_epi16(X,Y)
#define anvil_sub_u16x16(X,Y) _mm256_sub_epi16(X,Y)

#define anvil_sub_s8x1(X,Y) (X + Y)
#define anvil_sub_s8x8(X,Y) anvil_sub_s8x16(X + Y)
#define anvil_sub_s8x16(X,Y) _mm_sub_epi8(X,Y)
#define anvil_sub_s8x32(X,Y) _mm256_sub_epi8(X,Y)

#define anvil_sub_u8x1(X,Y) (X + Y)
#define anvil_sub_u8x8(X,Y) anvil_sub_u8x16(X + Y)
#define anvil_sub_u8x16(X,Y) _mm_sub_epi8(X,Y)
#define anvil_sub_u8x32(X,Y) _mm256_sub_epi8(X,Y)

// Multiply

#define anvil_mul_f64x1(X,Y) (X * Y)
#define anvil_mul_f64x2(X,Y) _mm_mul_pdX,Y)
#define anvil_mul_f64x4(X,Y) _mm256_mul_pd(X,Y)

#define anvil_mul_f32x1(X,Y) (X * Y)
#define anvil_mul_f32x4(X,Y) _mm_mul_ps(X,Y)
#define anvil_mul_f32x8(X,Y) _mm256_mul_ps(X,Y)

#define anvil_mul_s64x1(X,Y) (X * Y)

static ANVIL_STRONG_INLINE int64x2_t ANVIL_SIMD_CALL anvil_mul_s64x2(const register int64x2_t x, const register int64x2_t y) {
	ANVIL_ALIGN(16) int64_t a[2];
	ANVIL_ALIGN(16) int64_t b[2];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	_mm_store_si128(reinterpret_cast<__m128i*>(b), y);
	a[0] *= b[0];
	a[1] *= b[1];
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE int64x4_t ANVIL_SIMD_CALL anvil_mul_s64x4(const register int64x4_t x, const register int64x4_t y) {
	ANVIL_ALIGN(32) int64_t a[4];
	ANVIL_ALIGN(32) int64_t b[4];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	_mm256_store_si256(reinterpret_cast<__m256i*>(b), y);
	a[0] *= b[0];
	a[1] *= b[1];
	a[2] *= b[2];
	a[3] *= b[3];
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

#define anvil_mul_u64x1(X,Y) (X * Y)

static ANVIL_STRONG_INLINE uint64x2_t ANVIL_SIMD_CALL anvil_mul_u64x2(const register uint64x2_t x, const register uint64x2_t y) {
	ANVIL_ALIGN(16) uint64_t a[2];
	ANVIL_ALIGN(16) uint64_t b[2];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	_mm_store_si128(reinterpret_cast<__m128i*>(b), y);
	a[0] *= b[0];
	a[1] *= b[1];
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE uint64x4_t ANVIL_SIMD_CALL anvil_mul_u64x4(const register uint64x4_t x, const register uint64x4_t y) {
	ANVIL_ALIGN(32) uint64_t a[4];
	ANVIL_ALIGN(32) uint64_t b[4];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	_mm256_store_si256(reinterpret_cast<__m256i*>(b), y);
	a[0] *= b[0];
	a[1] *= b[1];
	a[2] *= b[2];
	a[3] *= b[3];
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

#define anvil_mul_s32x1(X,Y) (X * Y)
#define anvil_mul_s32x4(X,Y) _mm_mullo_epi32(X,Y)
#define anvil_mul_s32x8(X,Y) _mm256_mullo_epi32(X,Y)

#define anvil_mul_u32x1(X,Y) (X * Y)
#define anvil_mul_u32x4(X,Y) anvil_mul_s32x4(X,Y)
#define anvil_mul_u32x8(X,Y) anvil_mul_s32x8(X,Y)

#define anvil_mul_s16x1(X,Y) (X * Y)
#define anvil_mul_s16x8(X,Y) _mm_mullo_epi16(X,Y)
#define anvil_mul_s16x16(X,Y) _mm256_mullo_epi16(X,Y)

#define anvil_mul_u16x1(X,Y) (X * Y)
#define anvil_mul_u16x8(X,Y) anvil_mul_s16x8(X,Y)
#define anvil_mul_u16x16(X,Y) anvil_mul_s16x16(X,Y)

#define anvil_mul_s8x1(X,Y) (X * Y)

static ANVIL_STRONG_INLINE int8x16_t ANVIL_SIMD_CALL anvil_mul_s8x16(const register int8x16_t x, const register int8x16_t y) {
	const register __m128i dst_even = _mm_mullo_epi16(x, y);
	const register __m128i dst_odd = _mm_mullo_epi16(_mm_srli_epi16(x, 8),_mm_srli_epi16(y, 8));
	return _mm_or_si128(_mm_slli_epi16(dst_odd, 8), _mm_srli_epi16(_mm_slli_epi16(dst_even,8), 8));
}

static ANVIL_STRONG_INLINE int8x32_t ANVIL_SIMD_CALL anvil_mul_s8x16(const register int8x32_t x, const register int8x32_t y) {
	register __m128i x_hi = _mm256_extractf128_si256(x, 0);
	register __m128i x_lo = _mm256_extractf128_si256(x, 1);
	const register __m128i y_hi = _mm256_extractf128_si256(y, 0);
	const register __m128i y_lo = _mm256_extractf128_si256(y, 1);
	x_hi = anvil_mul_s8x16(x_hi, y_hi);
	x_lo = anvil_mul_s8x16(x_lo, y_lo);
	return _mm256_set_m128i(x_hi, x_lo);
}

#define anvil_mul_u8x1(X,Y) (X * Y)
#define anvil_mul_u8x16(X,Y) anvil_mul_s8x16(X,Y)
#define anvil_mul_u8x32(X,Y) anvil_mul_s8x32(X,Y)

// Div

#define anvil_div_float64x1(X,Y) (X / Y)
#define anvil_div_float64x2(X,Y) _mm_div_pd(X,Y)
#define anvil_div_float64x4(X,Y) _mm256_div_pd(X,Y)

#define anvil_div_float32x1(X,Y) (X / Y)
#define anvil_div_float32x4(X,Y) _mm_div_ps(X,Y)
#define anvil_div_float32x8(X,Y) _mm256_div_ps(X,Y)

#define anvil_div_s64x1(X,Y) (X / Y)

static ANVIL_STRONG_INLINE int64x2_t ANVIL_SIMD_CALL anvil_div_s64x2(const register int64x2_t x, const register int64x2_t y) {
	ANVIL_ALIGN(16) int64x1_t a[2];
	ANVIL_ALIGN(16) int64x1_t b[2];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	_mm_store_si128(reinterpret_cast<__m128i*>(b), y);
	a[0] /= b[0];
	a[1] /= b[1];
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE int64x4_t ANVIL_SIMD_CALL anvil_div_s64x4(const register int64x4_t x, const register int64x4_t y) {
	ANVIL_ALIGN(16) int64x1_t a[4];
	ANVIL_ALIGN(16) int64x1_t b[4];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	_mm256_store_si256(reinterpret_cast<__m256i*>(b), y);
	a[0] /= b[0];
	a[1] /= b[1];
	a[2] /= b[2];
	a[3] /= b[3];
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}
#define anvil_div_u64x1(X,Y) (X / Y)

static ANVIL_STRONG_INLINE uint64x2_t ANVIL_SIMD_CALL anvil_div_u64x2(const register uint64x2_t x, const register uint64x2_t y) {
	ANVIL_ALIGN(16) uint64x1_t a[2];
	ANVIL_ALIGN(16) uint64x1_t b[2];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	_mm_store_si128(reinterpret_cast<__m128i*>(b), y);
	a[0] /= b[0];
	a[1] /= b[1];
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE uint64x4_t ANVIL_SIMD_CALL anvil_div_u64x4(const register uint64x4_t x, const register uint64x4_t y) {
	ANVIL_ALIGN(16) uint64x1_t a[4];
	ANVIL_ALIGN(16) uint64x1_t b[4];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	_mm256_store_si256(reinterpret_cast<__m256i*>(b), y);
	a[0] /= b[0];
	a[1] /= b[1];
	a[2] /= b[2];
	a[3] /= b[3];
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}
#define anvil_div_s32x1(X,Y) (X / Y)

static ANVIL_STRONG_INLINE int32x4_t ANVIL_SIMD_CALL anvil_div_s32x4(const register int32x4_t x, const register int32x4_t y) {
	ANVIL_ALIGN(16) int32x1_t a[4];
	ANVIL_ALIGN(16) int32x1_t b[4];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	_mm_store_si128(reinterpret_cast<__m128i*>(b), y);
	a[0] /= b[0];
	a[1] /= b[1];
	a[2] /= b[2];
	a[3] /= b[3];
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE int32x8_t ANVIL_SIMD_CALL anvil_div_s32x8(const register int32x8_t x, const register int32x8_t y) {
	ANVIL_ALIGN(16) int32x1_t a[8];
	ANVIL_ALIGN(16) int32x1_t b[8];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	_mm256_store_si256(reinterpret_cast<__m256i*>(b), y);
	a[0] /= b[0];
	a[1] /= b[1];
	a[2] /= b[2];
	a[3] /= b[3];
	a[4] /= b[4];
	a[5] /= b[5];
	a[6] /= b[6];
	a[7] /= b[7];
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}
#define anvil_div_u32x1(X,Y) (X / Y)

static ANVIL_STRONG_INLINE uint32x4_t ANVIL_SIMD_CALL anvil_div_u32x4(const register uint32x4_t x, const register uint32x4_t y) {
	ANVIL_ALIGN(16) uint32x1_t a[4];
	ANVIL_ALIGN(16) uint32x1_t b[4];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	_mm_store_si128(reinterpret_cast<__m128i*>(b), y);
	a[0] /= b[0];
	a[1] /= b[1];
	a[2] /= b[2];
	a[3] /= b[3];
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE uint32x8_t ANVIL_SIMD_CALL anvil_div_u32x8(const register uint32x8_t x, const register uint32x8_t y) {
	ANVIL_ALIGN(16) uint32x1_t a[8];
	ANVIL_ALIGN(16) uint32x1_t b[8];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	_mm256_store_si256(reinterpret_cast<__m256i*>(b), y);
	a[0] /= b[0];
	a[1] /= b[1];
	a[2] /= b[2];
	a[3] /= b[3];
	a[4] /= b[4];
	a[5] /= b[5];
	a[6] /= b[6];
	a[7] /= b[7];
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}
#define anvil_div_s16x1(X,Y) (X / Y)

static ANVIL_STRONG_INLINE int16x8_t ANVIL_SIMD_CALL anvil_div_s16x8(const register int16x8_t x, const register int16x8_t y) {
	ANVIL_ALIGN(16) int16x1_t a[8];
	ANVIL_ALIGN(16) int16x1_t b[8];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	_mm_store_si128(reinterpret_cast<__m128i*>(b), y);
	a[0] /= b[0];
	a[1] /= b[1];
	a[2] /= b[2];
	a[3] /= b[3];
	a[4] /= b[4];
	a[5] /= b[5];
	a[6] /= b[6];
	a[7] /= b[7];
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE int16x16_t ANVIL_SIMD_CALL anvil_div_s16x16(const register int16x16_t x, const register int16x16_t y) {
	ANVIL_ALIGN(16) int16x1_t a[16];
	ANVIL_ALIGN(16) int16x1_t b[16];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	_mm256_store_si256(reinterpret_cast<__m256i*>(b), y);
	a[0] /= b[0];
	a[1] /= b[1];
	a[2] /= b[2];
	a[3] /= b[3];
	a[4] /= b[4];
	a[5] /= b[5];
	a[6] /= b[6];
	a[7] /= b[7];
	a[8] /= b[8];
	a[9] /= b[9];
	a[10] /= b[10];
	a[11] /= b[11];
	a[12] /= b[12];
	a[13] /= b[13];
	a[14] /= b[14];
	a[15] /= b[15];
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}
#define anvil_div_u16x1(X,Y) (X / Y)

static ANVIL_STRONG_INLINE uint16x8_t ANVIL_SIMD_CALL anvil_div_u16x8(const register uint16x8_t x, const register uint16x8_t y) {
	ANVIL_ALIGN(16) uint16x1_t a[8];
	ANVIL_ALIGN(16) uint16x1_t b[8];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	_mm_store_si128(reinterpret_cast<__m128i*>(b), y);
	a[0] /= b[0];
	a[1] /= b[1];
	a[2] /= b[2];
	a[3] /= b[3];
	a[4] /= b[4];
	a[5] /= b[5];
	a[6] /= b[6];
	a[7] /= b[7];
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE uint16x16_t ANVIL_SIMD_CALL anvil_div_u16x16(const register uint16x16_t x, const register uint16x16_t y) {
	ANVIL_ALIGN(16) uint16x1_t a[16];
	ANVIL_ALIGN(16) uint16x1_t b[16];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	_mm256_store_si256(reinterpret_cast<__m256i*>(b), y);
	a[0] /= b[0];
	a[1] /= b[1];
	a[2] /= b[2];
	a[3] /= b[3];
	a[4] /= b[4];
	a[5] /= b[5];
	a[6] /= b[6];
	a[7] /= b[7];
	a[8] /= b[8];
	a[9] /= b[9];
	a[10] /= b[10];
	a[11] /= b[11];
	a[12] /= b[12];
	a[13] /= b[13];
	a[14] /= b[14];
	a[15] /= b[15];
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}
#define anvil_div_s8x1(X,Y) (X / Y)

static ANVIL_STRONG_INLINE int8x16_t ANVIL_SIMD_CALL anvil_div_s8x16(const register int8x16_t x, const register int8x16_t y) {
	ANVIL_ALIGN(16) int8x1_t a[16];
	ANVIL_ALIGN(16) int8x1_t b[16];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	_mm_store_si128(reinterpret_cast<__m128i*>(b), y);
	a[0] /= b[0];
	a[1] /= b[1];
	a[2] /= b[2];
	a[3] /= b[3];
	a[4] /= b[4];
	a[5] /= b[5];
	a[6] /= b[6];
	a[7] /= b[7];
	a[8] /= b[8];
	a[9] /= b[9];
	a[10] /= b[10];
	a[11] /= b[11];
	a[12] /= b[12];
	a[13] /= b[13];
	a[14] /= b[14];
	a[15] /= b[15];
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE int8x32_t ANVIL_SIMD_CALL anvil_div_s8x32(const register int8x32_t x, const register int8x32_t y) {
	ANVIL_ALIGN(16) int8x1_t a[32];
	ANVIL_ALIGN(16) int8x1_t b[32];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	_mm256_store_si256(reinterpret_cast<__m256i*>(b), y);
	a[0] /= b[0];
	a[1] /= b[1];
	a[2] /= b[2];
	a[3] /= b[3];
	a[4] /= b[4];
	a[5] /= b[5];
	a[6] /= b[6];
	a[7] /= b[7];
	a[8] /= b[8];
	a[9] /= b[9];
	a[10] /= b[10];
	a[11] /= b[11];
	a[12] /= b[12];
	a[13] /= b[13];
	a[14] /= b[14];
	a[15] /= b[15];
	a[16] /= b[16];
	a[17] /= b[17];
	a[18] /= b[18];
	a[19] /= b[19];
	a[20] /= b[20];
	a[21] /= b[21];
	a[22] /= b[22];
	a[23] /= b[23];
	a[24] /= b[24];
	a[25] /= b[25];
	a[26] /= b[26];
	a[27] /= b[27];
	a[28] /= b[28];
	a[29] /= b[29];
	a[30] /= b[30];
	a[31] /= b[31];
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}
#define anvil_div_u8x1(X,Y) (X / Y)

static ANVIL_STRONG_INLINE uint8x16_t ANVIL_SIMD_CALL anvil_div_u8x16(const register uint8x16_t x, const register uint8x16_t y) {
	ANVIL_ALIGN(16) uint8x1_t a[16];
	ANVIL_ALIGN(16) uint8x1_t b[16];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	_mm_store_si128(reinterpret_cast<__m128i*>(b), y);
	a[0] /= b[0];
	a[1] /= b[1];
	a[2] /= b[2];
	a[3] /= b[3];
	a[4] /= b[4];
	a[5] /= b[5];
	a[6] /= b[6];
	a[7] /= b[7];
	a[8] /= b[8];
	a[9] /= b[9];
	a[10] /= b[10];
	a[11] /= b[11];
	a[12] /= b[12];
	a[13] /= b[13];
	a[14] /= b[14];
	a[15] /= b[15];
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE uint8x32_t ANVIL_SIMD_CALL anvil_div_u8x32(const register uint8x32_t x, const register uint8x32_t y) {
	ANVIL_ALIGN(16) uint8x1_t a[32];
	ANVIL_ALIGN(16) uint8x1_t b[32];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	_mm256_store_si256(reinterpret_cast<__m256i*>(b), y);
	a[0] /= b[0];
	a[1] /= b[1];
	a[2] /= b[2];
	a[3] /= b[3];
	a[4] /= b[4];
	a[5] /= b[5];
	a[6] /= b[6];
	a[7] /= b[7];
	a[8] /= b[8];
	a[9] /= b[9];
	a[10] /= b[10];
	a[11] /= b[11];
	a[12] /= b[12];
	a[13] /= b[13];
	a[14] /= b[14];
	a[15] /= b[15];
	a[16] /= b[16];
	a[17] /= b[17];
	a[18] /= b[18];
	a[19] /= b[19];
	a[20] /= b[20];
	a[21] /= b[21];
	a[22] /= b[22];
	a[23] /= b[23];
	a[24] /= b[24];
	a[25] /= b[25];
	a[26] /= b[26];
	a[27] /= b[27];
	a[28] /= b[28];
	a[29] /= b[29];
	a[30] /= b[30];
	a[31] /= b[31];
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

// cos

#define anvil_cos_f64x1(X) std::cos(X)

static ANVIL_STRONG_INLINE float64x2_t ANVIL_SIMD_CALL anvil_cos_f64x2(const register float64x2_t x) {
	ANVIL_ALIGN(16) float64x1_t a[2];
	_mm_store_pd(a, x);
	a[0] = anvil_cos_f64x1(a[0]);
	a[1] = anvil_cos_f64x1(a[1]);
	return _mm_load_pd(a); 
}

static ANVIL_STRONG_INLINE float64x4_t ANVIL_SIMD_CALL anvil_cos_f64x4(const register float64x4_t x) {
	ANVIL_ALIGN(16) float64x1_t a[4];
	_mm256_store_pd(a, x);
	a[0] = anvil_cos_f64x1(a[0]);
	a[1] = anvil_cos_f64x1(a[1]);
	a[2] = anvil_cos_f64x1(a[2]);
	a[3] = anvil_cos_f64x1(a[3]);
	return _mm256_load_pd(a); 
}

#define anvil_cos_f32x1(X) std::cos(X)

static ANVIL_STRONG_INLINE float32x4_t ANVIL_SIMD_CALL anvil_cos_f32x4(const register float32x4_t x) {
	ANVIL_ALIGN(16) float32x1_t a[4];
	_mm_store_ps(a, x);
	a[0] = anvil_cos_f32x1(a[0]);
	a[1] = anvil_cos_f32x1(a[1]);
	a[2] = anvil_cos_f32x1(a[2]);
	a[3] = anvil_cos_f32x1(a[3]);
	return _mm_load_ps(a); 
}

static ANVIL_STRONG_INLINE float32x8_t ANVIL_SIMD_CALL anvil_cos_f32x8(const register float32x8_t x) {
	ANVIL_ALIGN(16) float32x1_t a[8];
	_mm256_store_ps(a, x);
	a[0] = anvil_cos_f32x1(a[0]);
	a[1] = anvil_cos_f32x1(a[1]);
	a[2] = anvil_cos_f32x1(a[2]);
	a[3] = anvil_cos_f32x1(a[3]);
	a[4] = anvil_cos_f32x1(a[4]);
	a[5] = anvil_cos_f32x1(a[5]);
	a[6] = anvil_cos_f32x1(a[6]);
	a[7] = anvil_cos_f32x1(a[7]);
	return _mm256_load_ps(a); 
}

#define anvil_cos_s64x1(X) anvil_convert_f64x1_to_s64x1(anvil_cos_f64x1(anvil_convert_s64x1_to_f64x1(X)))
#define anvil_cos_s64x2(X) anvil_convert_f64x2_to_s64x2(anvil_cos_f64x2(anvil_convert_s64x2_to_f64x2(X)))
#define anvil_cos_s64x4(X) anvil_convert_f64x4_to_s64x4(anvil_cos_f64x4(anvil_convert_s64x4_to_f64x4(X)))

#define anvil_cos_u64x1(X) anvil_convert_f64x1_to_u64x1(anvil_cos_f64x1(anvil_convert_u64x1_to_f64x1(X)))
#define anvil_cos_u64x2(X) anvil_convert_f64x2_to_u64x2(anvil_cos_f64x2(anvil_convert_u64x2_to_f64x2(X)))
#define anvil_cos_u64x4(X) anvil_convert_f64x4_to_u64x4(anvil_cos_f64x4(anvil_convert_u64x4_to_f64x4(X)))

#define anvil_cos_s32x1(X) anvil_convert_f32x1_to_s32x1(anvil_cos_f32x1(anvil_convert_s32x1_to_f32x1(X)))
#define anvil_cos_s32x4(X) anvil_convert_f32x4_to_s32x4(anvil_cos_f32x4(anvil_convert_s32x4_to_f32x4(X)))
#define anvil_cos_s32x8(X) anvil_convert_f32x8_to_s32x8(anvil_cos_f32x8(anvil_convert_s32x8_to_f32x8(X)))

#define anvil_cos_u32x1(X) anvil_convert_f32x1_to_u32x1(anvil_cos_f32x1(anvil_convert_u32x1_to_f32x1(X)))
#define anvil_cos_u32x4(X) anvil_convert_f32x4_to_u32x4(anvil_cos_f32x4(anvil_convert_u32x4_to_f32x4(X)))
#define anvil_cos_u32x8(X) anvil_convert_f32x8_to_u32x8(anvil_cos_f32x8(anvil_convert_u32x8_to_f32x8(X)))

#define anvil_cos_s16x1(X) anvil_convert_f32x1_to_s16x1(anvil_cos_f32x1(anvil_convert_s16x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE int16x8_t ANVIL_SIMD_CALL anvil_cos_s16x8(const register int16x8_t x) {
	ANVIL_ALIGN(16) int16x1_t a[8];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_cos_s16x1(a[0]);
	a[1] = anvil_cos_s16x1(a[1]);
	a[2] = anvil_cos_s16x1(a[2]);
	a[3] = anvil_cos_s16x1(a[3]);
	a[4] = anvil_cos_s16x1(a[4]);
	a[5] = anvil_cos_s16x1(a[5]);
	a[6] = anvil_cos_s16x1(a[6]);
	a[7] = anvil_cos_s16x1(a[7]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE int16x16_t ANVIL_SIMD_CALL anvil_cos_s16x16(const register int16x16_t x) {
	ANVIL_ALIGN(16) int16x1_t a[16];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_cos_s16x1(a[0]);
	a[1] = anvil_cos_s16x1(a[1]);
	a[2] = anvil_cos_s16x1(a[2]);
	a[3] = anvil_cos_s16x1(a[3]);
	a[4] = anvil_cos_s16x1(a[4]);
	a[5] = anvil_cos_s16x1(a[5]);
	a[6] = anvil_cos_s16x1(a[6]);
	a[7] = anvil_cos_s16x1(a[7]);
	a[8] = anvil_cos_s16x1(a[8]);
	a[9] = anvil_cos_s16x1(a[9]);
	a[10] = anvil_cos_s16x1(a[10]);
	a[11] = anvil_cos_s16x1(a[11]);
	a[12] = anvil_cos_s16x1(a[12]);
	a[13] = anvil_cos_s16x1(a[13]);
	a[14] = anvil_cos_s16x1(a[14]);
	a[15] = anvil_cos_s16x1(a[15]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

#define anvil_cos_u16x1(X) anvil_convert_f32x1_to_u16x1(anvil_cos_f32x1(anvil_convert_u16x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE uint16x8_t ANVIL_SIMD_CALL anvil_cos_u16x8(const register uint16x8_t x) {
	ANVIL_ALIGN(16) uint16x1_t a[8];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_cos_u16x1(a[0]);
	a[1] = anvil_cos_u16x1(a[1]);
	a[2] = anvil_cos_u16x1(a[2]);
	a[3] = anvil_cos_u16x1(a[3]);
	a[4] = anvil_cos_u16x1(a[4]);
	a[5] = anvil_cos_u16x1(a[5]);
	a[6] = anvil_cos_u16x1(a[6]);
	a[7] = anvil_cos_u16x1(a[7]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE uint16x16_t ANVIL_SIMD_CALL anvil_cos_u16x16(const register uint16x16_t x) {
	ANVIL_ALIGN(16) uint16x1_t a[16];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_cos_u16x1(a[0]);
	a[1] = anvil_cos_u16x1(a[1]);
	a[2] = anvil_cos_u16x1(a[2]);
	a[3] = anvil_cos_u16x1(a[3]);
	a[4] = anvil_cos_u16x1(a[4]);
	a[5] = anvil_cos_u16x1(a[5]);
	a[6] = anvil_cos_u16x1(a[6]);
	a[7] = anvil_cos_u16x1(a[7]);
	a[8] = anvil_cos_u16x1(a[8]);
	a[9] = anvil_cos_u16x1(a[9]);
	a[10] = anvil_cos_u16x1(a[10]);
	a[11] = anvil_cos_u16x1(a[11]);
	a[12] = anvil_cos_u16x1(a[12]);
	a[13] = anvil_cos_u16x1(a[13]);
	a[14] = anvil_cos_u16x1(a[14]);
	a[15] = anvil_cos_u16x1(a[15]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

#define anvil_cos_s8x1(X) anvil_convert_f32x1_to_s8x1(anvil_cos_f32x1(anvil_convert_s8x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE int8x16_t ANVIL_SIMD_CALL anvil_cos_s8x16(const register int8x16_t x) {
	ANVIL_ALIGN(16) int8x1_t a[16];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_cos_s8x1(a[0]);
	a[1] = anvil_cos_s8x1(a[1]);
	a[2] = anvil_cos_s8x1(a[2]);
	a[3] = anvil_cos_s8x1(a[3]);
	a[4] = anvil_cos_s8x1(a[4]);
	a[5] = anvil_cos_s8x1(a[5]);
	a[6] = anvil_cos_s8x1(a[6]);
	a[7] = anvil_cos_s8x1(a[7]);
	a[8] = anvil_cos_s8x1(a[8]);
	a[9] = anvil_cos_s8x1(a[9]);
	a[10] = anvil_cos_s8x1(a[10]);
	a[11] = anvil_cos_s8x1(a[11]);
	a[12] = anvil_cos_s8x1(a[12]);
	a[13] = anvil_cos_s8x1(a[13]);
	a[14] = anvil_cos_s8x1(a[14]);
	a[15] = anvil_cos_s8x1(a[15]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE int8x32_t ANVIL_SIMD_CALL anvil_cos_s8x32(const register int8x32_t x) {
	ANVIL_ALIGN(16) int8x1_t a[32];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_cos_s8x1(a[0]);
	a[1] = anvil_cos_s8x1(a[1]);
	a[2] = anvil_cos_s8x1(a[2]);
	a[3] = anvil_cos_s8x1(a[3]);
	a[4] = anvil_cos_s8x1(a[4]);
	a[5] = anvil_cos_s8x1(a[5]);
	a[6] = anvil_cos_s8x1(a[6]);
	a[7] = anvil_cos_s8x1(a[7]);
	a[8] = anvil_cos_s8x1(a[8]);
	a[9] = anvil_cos_s8x1(a[9]);
	a[10] = anvil_cos_s8x1(a[10]);
	a[11] = anvil_cos_s8x1(a[11]);
	a[12] = anvil_cos_s8x1(a[12]);
	a[13] = anvil_cos_s8x1(a[13]);
	a[14] = anvil_cos_s8x1(a[14]);
	a[15] = anvil_cos_s8x1(a[15]);
	a[16] = anvil_cos_s8x1(a[16]);
	a[17] = anvil_cos_s8x1(a[17]);
	a[18] = anvil_cos_s8x1(a[18]);
	a[19] = anvil_cos_s8x1(a[19]);
	a[20] = anvil_cos_s8x1(a[20]);
	a[21] = anvil_cos_s8x1(a[21]);
	a[22] = anvil_cos_s8x1(a[22]);
	a[23] = anvil_cos_s8x1(a[23]);
	a[24] = anvil_cos_s8x1(a[24]);
	a[25] = anvil_cos_s8x1(a[25]);
	a[26] = anvil_cos_s8x1(a[26]);
	a[27] = anvil_cos_s8x1(a[27]);
	a[28] = anvil_cos_s8x1(a[28]);
	a[29] = anvil_cos_s8x1(a[29]);
	a[30] = anvil_cos_s8x1(a[30]);
	a[31] = anvil_cos_s8x1(a[31]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

#define anvil_cos_u8x1(X) anvil_convert_f32x1_to_u8x1(anvil_cos_f32x1(anvil_convert_u8x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE uint8x16_t ANVIL_SIMD_CALL anvil_cos_u8x16(const register uint8x16_t x) {
	ANVIL_ALIGN(16) uint8x1_t a[16];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_cos_u8x1(a[0]);
	a[1] = anvil_cos_u8x1(a[1]);
	a[2] = anvil_cos_u8x1(a[2]);
	a[3] = anvil_cos_u8x1(a[3]);
	a[4] = anvil_cos_u8x1(a[4]);
	a[5] = anvil_cos_u8x1(a[5]);
	a[6] = anvil_cos_u8x1(a[6]);
	a[7] = anvil_cos_u8x1(a[7]);
	a[8] = anvil_cos_u8x1(a[8]);
	a[9] = anvil_cos_u8x1(a[9]);
	a[10] = anvil_cos_u8x1(a[10]);
	a[11] = anvil_cos_u8x1(a[11]);
	a[12] = anvil_cos_u8x1(a[12]);
	a[13] = anvil_cos_u8x1(a[13]);
	a[14] = anvil_cos_u8x1(a[14]);
	a[15] = anvil_cos_u8x1(a[15]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE uint8x32_t ANVIL_SIMD_CALL anvil_cos_u8x32(const register uint8x32_t x) {
	ANVIL_ALIGN(16) uint8x1_t a[32];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_cos_u8x1(a[0]);
	a[1] = anvil_cos_u8x1(a[1]);
	a[2] = anvil_cos_u8x1(a[2]);
	a[3] = anvil_cos_u8x1(a[3]);
	a[4] = anvil_cos_u8x1(a[4]);
	a[5] = anvil_cos_u8x1(a[5]);
	a[6] = anvil_cos_u8x1(a[6]);
	a[7] = anvil_cos_u8x1(a[7]);
	a[8] = anvil_cos_u8x1(a[8]);
	a[9] = anvil_cos_u8x1(a[9]);
	a[10] = anvil_cos_u8x1(a[10]);
	a[11] = anvil_cos_u8x1(a[11]);
	a[12] = anvil_cos_u8x1(a[12]);
	a[13] = anvil_cos_u8x1(a[13]);
	a[14] = anvil_cos_u8x1(a[14]);
	a[15] = anvil_cos_u8x1(a[15]);
	a[16] = anvil_cos_u8x1(a[16]);
	a[17] = anvil_cos_u8x1(a[17]);
	a[18] = anvil_cos_u8x1(a[18]);
	a[19] = anvil_cos_u8x1(a[19]);
	a[20] = anvil_cos_u8x1(a[20]);
	a[21] = anvil_cos_u8x1(a[21]);
	a[22] = anvil_cos_u8x1(a[22]);
	a[23] = anvil_cos_u8x1(a[23]);
	a[24] = anvil_cos_u8x1(a[24]);
	a[25] = anvil_cos_u8x1(a[25]);
	a[26] = anvil_cos_u8x1(a[26]);
	a[27] = anvil_cos_u8x1(a[27]);
	a[28] = anvil_cos_u8x1(a[28]);
	a[29] = anvil_cos_u8x1(a[29]);
	a[30] = anvil_cos_u8x1(a[30]);
	a[31] = anvil_cos_u8x1(a[31]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

// sin

#define anvil_sin_f64x1(X) std::sin(X)

static ANVIL_STRONG_INLINE float64x2_t ANVIL_SIMD_CALL anvil_sin_f64x2(const register float64x2_t x) {
	ANVIL_ALIGN(16) float64x1_t a[2];
	_mm_store_pd(a, x);
	a[0] = anvil_sin_f64x1(a[0]);
	a[1] = anvil_sin_f64x1(a[1]);
	return _mm_load_pd(a); 
}

static ANVIL_STRONG_INLINE float64x4_t ANVIL_SIMD_CALL anvil_sin_f64x4(const register float64x4_t x) {
	ANVIL_ALIGN(16) float64x1_t a[4];
	_mm256_store_pd(a, x);
	a[0] = anvil_sin_f64x1(a[0]);
	a[1] = anvil_sin_f64x1(a[1]);
	a[2] = anvil_sin_f64x1(a[2]);
	a[3] = anvil_sin_f64x1(a[3]);
	return _mm256_load_pd(a); 
}

#define anvil_sin_f32x1(X) std::sin(X)

static ANVIL_STRONG_INLINE float32x4_t ANVIL_SIMD_CALL anvil_sin_f32x4(const register float32x4_t x) {
	ANVIL_ALIGN(16) float32x1_t a[4];
	_mm_store_ps(a, x);
	a[0] = anvil_sin_f32x1(a[0]);
	a[1] = anvil_sin_f32x1(a[1]);
	a[2] = anvil_sin_f32x1(a[2]);
	a[3] = anvil_sin_f32x1(a[3]);
	return _mm_load_ps(a); 
}

static ANVIL_STRONG_INLINE float32x8_t ANVIL_SIMD_CALL anvil_sin_f32x8(const register float32x8_t x) {
	ANVIL_ALIGN(16) float32x1_t a[8];
	_mm256_store_ps(a, x);
	a[0] = anvil_sin_f32x1(a[0]);
	a[1] = anvil_sin_f32x1(a[1]);
	a[2] = anvil_sin_f32x1(a[2]);
	a[3] = anvil_sin_f32x1(a[3]);
	a[4] = anvil_sin_f32x1(a[4]);
	a[5] = anvil_sin_f32x1(a[5]);
	a[6] = anvil_sin_f32x1(a[6]);
	a[7] = anvil_sin_f32x1(a[7]);
	return _mm256_load_ps(a); 
}

#define anvil_sin_s64x1(X) anvil_convert_f64x1_to_s64x1(anvil_sin_f64x1(anvil_convert_s64x1_to_f64x1(X)))
#define anvil_sin_s64x2(X) anvil_convert_f64x2_to_s64x2(anvil_sin_f64x2(anvil_convert_s64x2_to_f64x2(X)))
#define anvil_sin_s64x4(X) anvil_convert_f64x4_to_s64x4(anvil_sin_f64x4(anvil_convert_s64x4_to_f64x4(X)))

#define anvil_sin_u64x1(X) anvil_convert_f64x1_to_u64x1(anvil_sin_f64x1(anvil_convert_u64x1_to_f64x1(X)))
#define anvil_sin_u64x2(X) anvil_convert_f64x2_to_u64x2(anvil_sin_f64x2(anvil_convert_u64x2_to_f64x2(X)))
#define anvil_sin_u64x4(X) anvil_convert_f64x4_to_u64x4(anvil_sin_f64x4(anvil_convert_u64x4_to_f64x4(X)))

#define anvil_sin_s32x1(X) anvil_convert_f32x1_to_s32x1(anvil_sin_f32x1(anvil_convert_s32x1_to_f32x1(X)))
#define anvil_sin_s32x4(X) anvil_convert_f32x4_to_s32x4(anvil_sin_f32x4(anvil_convert_s32x4_to_f32x4(X)))
#define anvil_sin_s32x8(X) anvil_convert_f32x8_to_s32x8(anvil_sin_f32x8(anvil_convert_s32x8_to_f32x8(X)))

#define anvil_sin_u32x1(X) anvil_convert_f32x1_to_u32x1(anvil_sin_f32x1(anvil_convert_u32x1_to_f32x1(X)))
#define anvil_sin_u32x4(X) anvil_convert_f32x4_to_u32x4(anvil_sin_f32x4(anvil_convert_u32x4_to_f32x4(X)))
#define anvil_sin_u32x8(X) anvil_convert_f32x8_to_u32x8(anvil_sin_f32x8(anvil_convert_u32x8_to_f32x8(X)))

#define anvil_sin_s16x1(X) anvil_convert_f32x1_to_s16x1(anvil_sin_f32x1(anvil_convert_s16x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE int16x8_t ANVIL_SIMD_CALL anvil_sin_s16x8(const register int16x8_t x) {
	ANVIL_ALIGN(16) int16x1_t a[8];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_sin_s16x1(a[0]);
	a[1] = anvil_sin_s16x1(a[1]);
	a[2] = anvil_sin_s16x1(a[2]);
	a[3] = anvil_sin_s16x1(a[3]);
	a[4] = anvil_sin_s16x1(a[4]);
	a[5] = anvil_sin_s16x1(a[5]);
	a[6] = anvil_sin_s16x1(a[6]);
	a[7] = anvil_sin_s16x1(a[7]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE int16x16_t ANVIL_SIMD_CALL anvil_sin_s16x16(const register int16x16_t x) {
	ANVIL_ALIGN(16) int16x1_t a[16];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_sin_s16x1(a[0]);
	a[1] = anvil_sin_s16x1(a[1]);
	a[2] = anvil_sin_s16x1(a[2]);
	a[3] = anvil_sin_s16x1(a[3]);
	a[4] = anvil_sin_s16x1(a[4]);
	a[5] = anvil_sin_s16x1(a[5]);
	a[6] = anvil_sin_s16x1(a[6]);
	a[7] = anvil_sin_s16x1(a[7]);
	a[8] = anvil_sin_s16x1(a[8]);
	a[9] = anvil_sin_s16x1(a[9]);
	a[10] = anvil_sin_s16x1(a[10]);
	a[11] = anvil_sin_s16x1(a[11]);
	a[12] = anvil_sin_s16x1(a[12]);
	a[13] = anvil_sin_s16x1(a[13]);
	a[14] = anvil_sin_s16x1(a[14]);
	a[15] = anvil_sin_s16x1(a[15]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

#define anvil_sin_u16x1(X) anvil_convert_f32x1_to_u16x1(anvil_sin_f32x1(anvil_convert_u16x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE uint16x8_t ANVIL_SIMD_CALL anvil_sin_u16x8(const register uint16x8_t x) {
	ANVIL_ALIGN(16) uint16x1_t a[8];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_sin_u16x1(a[0]);
	a[1] = anvil_sin_u16x1(a[1]);
	a[2] = anvil_sin_u16x1(a[2]);
	a[3] = anvil_sin_u16x1(a[3]);
	a[4] = anvil_sin_u16x1(a[4]);
	a[5] = anvil_sin_u16x1(a[5]);
	a[6] = anvil_sin_u16x1(a[6]);
	a[7] = anvil_sin_u16x1(a[7]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE uint16x16_t ANVIL_SIMD_CALL anvil_sin_u16x16(const register uint16x16_t x) {
	ANVIL_ALIGN(16) uint16x1_t a[16];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_sin_u16x1(a[0]);
	a[1] = anvil_sin_u16x1(a[1]);
	a[2] = anvil_sin_u16x1(a[2]);
	a[3] = anvil_sin_u16x1(a[3]);
	a[4] = anvil_sin_u16x1(a[4]);
	a[5] = anvil_sin_u16x1(a[5]);
	a[6] = anvil_sin_u16x1(a[6]);
	a[7] = anvil_sin_u16x1(a[7]);
	a[8] = anvil_sin_u16x1(a[8]);
	a[9] = anvil_sin_u16x1(a[9]);
	a[10] = anvil_sin_u16x1(a[10]);
	a[11] = anvil_sin_u16x1(a[11]);
	a[12] = anvil_sin_u16x1(a[12]);
	a[13] = anvil_sin_u16x1(a[13]);
	a[14] = anvil_sin_u16x1(a[14]);
	a[15] = anvil_sin_u16x1(a[15]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

#define anvil_sin_s8x1(X) anvil_convert_f32x1_to_s8x1(anvil_sin_f32x1(anvil_convert_s8x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE int8x16_t ANVIL_SIMD_CALL anvil_sin_s8x16(const register int8x16_t x) {
	ANVIL_ALIGN(16) int8x1_t a[16];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_sin_s8x1(a[0]);
	a[1] = anvil_sin_s8x1(a[1]);
	a[2] = anvil_sin_s8x1(a[2]);
	a[3] = anvil_sin_s8x1(a[3]);
	a[4] = anvil_sin_s8x1(a[4]);
	a[5] = anvil_sin_s8x1(a[5]);
	a[6] = anvil_sin_s8x1(a[6]);
	a[7] = anvil_sin_s8x1(a[7]);
	a[8] = anvil_sin_s8x1(a[8]);
	a[9] = anvil_sin_s8x1(a[9]);
	a[10] = anvil_sin_s8x1(a[10]);
	a[11] = anvil_sin_s8x1(a[11]);
	a[12] = anvil_sin_s8x1(a[12]);
	a[13] = anvil_sin_s8x1(a[13]);
	a[14] = anvil_sin_s8x1(a[14]);
	a[15] = anvil_sin_s8x1(a[15]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE int8x32_t ANVIL_SIMD_CALL anvil_sin_s8x32(const register int8x32_t x) {
	ANVIL_ALIGN(16) int8x1_t a[32];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_sin_s8x1(a[0]);
	a[1] = anvil_sin_s8x1(a[1]);
	a[2] = anvil_sin_s8x1(a[2]);
	a[3] = anvil_sin_s8x1(a[3]);
	a[4] = anvil_sin_s8x1(a[4]);
	a[5] = anvil_sin_s8x1(a[5]);
	a[6] = anvil_sin_s8x1(a[6]);
	a[7] = anvil_sin_s8x1(a[7]);
	a[8] = anvil_sin_s8x1(a[8]);
	a[9] = anvil_sin_s8x1(a[9]);
	a[10] = anvil_sin_s8x1(a[10]);
	a[11] = anvil_sin_s8x1(a[11]);
	a[12] = anvil_sin_s8x1(a[12]);
	a[13] = anvil_sin_s8x1(a[13]);
	a[14] = anvil_sin_s8x1(a[14]);
	a[15] = anvil_sin_s8x1(a[15]);
	a[16] = anvil_sin_s8x1(a[16]);
	a[17] = anvil_sin_s8x1(a[17]);
	a[18] = anvil_sin_s8x1(a[18]);
	a[19] = anvil_sin_s8x1(a[19]);
	a[20] = anvil_sin_s8x1(a[20]);
	a[21] = anvil_sin_s8x1(a[21]);
	a[22] = anvil_sin_s8x1(a[22]);
	a[23] = anvil_sin_s8x1(a[23]);
	a[24] = anvil_sin_s8x1(a[24]);
	a[25] = anvil_sin_s8x1(a[25]);
	a[26] = anvil_sin_s8x1(a[26]);
	a[27] = anvil_sin_s8x1(a[27]);
	a[28] = anvil_sin_s8x1(a[28]);
	a[29] = anvil_sin_s8x1(a[29]);
	a[30] = anvil_sin_s8x1(a[30]);
	a[31] = anvil_sin_s8x1(a[31]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

#define anvil_sin_u8x1(X) anvil_convert_f32x1_to_u8x1(anvil_sin_f32x1(anvil_convert_u8x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE uint8x16_t ANVIL_SIMD_CALL anvil_sin_u8x16(const register uint8x16_t x) {
	ANVIL_ALIGN(16) uint8x1_t a[16];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_sin_u8x1(a[0]);
	a[1] = anvil_sin_u8x1(a[1]);
	a[2] = anvil_sin_u8x1(a[2]);
	a[3] = anvil_sin_u8x1(a[3]);
	a[4] = anvil_sin_u8x1(a[4]);
	a[5] = anvil_sin_u8x1(a[5]);
	a[6] = anvil_sin_u8x1(a[6]);
	a[7] = anvil_sin_u8x1(a[7]);
	a[8] = anvil_sin_u8x1(a[8]);
	a[9] = anvil_sin_u8x1(a[9]);
	a[10] = anvil_sin_u8x1(a[10]);
	a[11] = anvil_sin_u8x1(a[11]);
	a[12] = anvil_sin_u8x1(a[12]);
	a[13] = anvil_sin_u8x1(a[13]);
	a[14] = anvil_sin_u8x1(a[14]);
	a[15] = anvil_sin_u8x1(a[15]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE uint8x32_t ANVIL_SIMD_CALL anvil_sin_u8x32(const register uint8x32_t x) {
	ANVIL_ALIGN(16) uint8x1_t a[32];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_sin_u8x1(a[0]);
	a[1] = anvil_sin_u8x1(a[1]);
	a[2] = anvil_sin_u8x1(a[2]);
	a[3] = anvil_sin_u8x1(a[3]);
	a[4] = anvil_sin_u8x1(a[4]);
	a[5] = anvil_sin_u8x1(a[5]);
	a[6] = anvil_sin_u8x1(a[6]);
	a[7] = anvil_sin_u8x1(a[7]);
	a[8] = anvil_sin_u8x1(a[8]);
	a[9] = anvil_sin_u8x1(a[9]);
	a[10] = anvil_sin_u8x1(a[10]);
	a[11] = anvil_sin_u8x1(a[11]);
	a[12] = anvil_sin_u8x1(a[12]);
	a[13] = anvil_sin_u8x1(a[13]);
	a[14] = anvil_sin_u8x1(a[14]);
	a[15] = anvil_sin_u8x1(a[15]);
	a[16] = anvil_sin_u8x1(a[16]);
	a[17] = anvil_sin_u8x1(a[17]);
	a[18] = anvil_sin_u8x1(a[18]);
	a[19] = anvil_sin_u8x1(a[19]);
	a[20] = anvil_sin_u8x1(a[20]);
	a[21] = anvil_sin_u8x1(a[21]);
	a[22] = anvil_sin_u8x1(a[22]);
	a[23] = anvil_sin_u8x1(a[23]);
	a[24] = anvil_sin_u8x1(a[24]);
	a[25] = anvil_sin_u8x1(a[25]);
	a[26] = anvil_sin_u8x1(a[26]);
	a[27] = anvil_sin_u8x1(a[27]);
	a[28] = anvil_sin_u8x1(a[28]);
	a[29] = anvil_sin_u8x1(a[29]);
	a[30] = anvil_sin_u8x1(a[30]);
	a[31] = anvil_sin_u8x1(a[31]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

// tan

#define anvil_tan_f64x1(X) std::tan(X)

static ANVIL_STRONG_INLINE float64x2_t ANVIL_SIMD_CALL anvil_tan_f64x2(const register float64x2_t x) {
	ANVIL_ALIGN(16) float64x1_t a[2];
	_mm_store_pd(a, x);
	a[0] = anvil_tan_f64x1(a[0]);
	a[1] = anvil_tan_f64x1(a[1]);
	return _mm_load_pd(a); 
}

static ANVIL_STRONG_INLINE float64x4_t ANVIL_SIMD_CALL anvil_tan_f64x4(const register float64x4_t x) {
	ANVIL_ALIGN(16) float64x1_t a[4];
	_mm256_store_pd(a, x);
	a[0] = anvil_tan_f64x1(a[0]);
	a[1] = anvil_tan_f64x1(a[1]);
	a[2] = anvil_tan_f64x1(a[2]);
	a[3] = anvil_tan_f64x1(a[3]);
	return _mm256_load_pd(a); 
}

#define anvil_tan_f32x1(X) std::tan(X)

static ANVIL_STRONG_INLINE float32x4_t ANVIL_SIMD_CALL anvil_tan_f32x4(const register float32x4_t x) {
	ANVIL_ALIGN(16) float32x1_t a[4];
	_mm_store_ps(a, x);
	a[0] = anvil_tan_f32x1(a[0]);
	a[1] = anvil_tan_f32x1(a[1]);
	a[2] = anvil_tan_f32x1(a[2]);
	a[3] = anvil_tan_f32x1(a[3]);
	return _mm_load_ps(a); 
}

static ANVIL_STRONG_INLINE float32x8_t ANVIL_SIMD_CALL anvil_tan_f32x8(const register float32x8_t x) {
	ANVIL_ALIGN(16) float32x1_t a[8];
	_mm256_store_ps(a, x);
	a[0] = anvil_tan_f32x1(a[0]);
	a[1] = anvil_tan_f32x1(a[1]);
	a[2] = anvil_tan_f32x1(a[2]);
	a[3] = anvil_tan_f32x1(a[3]);
	a[4] = anvil_tan_f32x1(a[4]);
	a[5] = anvil_tan_f32x1(a[5]);
	a[6] = anvil_tan_f32x1(a[6]);
	a[7] = anvil_tan_f32x1(a[7]);
	return _mm256_load_ps(a); 
}

#define anvil_tan_s64x1(X) anvil_convert_f64x1_to_s64x1(anvil_tan_f64x1(anvil_convert_s64x1_to_f64x1(X)))
#define anvil_tan_s64x2(X) anvil_convert_f64x2_to_s64x2(anvil_tan_f64x2(anvil_convert_s64x2_to_f64x2(X)))
#define anvil_tan_s64x4(X) anvil_convert_f64x4_to_s64x4(anvil_tan_f64x4(anvil_convert_s64x4_to_f64x4(X)))

#define anvil_tan_u64x1(X) anvil_convert_f64x1_to_u64x1(anvil_tan_f64x1(anvil_convert_u64x1_to_f64x1(X)))
#define anvil_tan_u64x2(X) anvil_convert_f64x2_to_u64x2(anvil_tan_f64x2(anvil_convert_u64x2_to_f64x2(X)))
#define anvil_tan_u64x4(X) anvil_convert_f64x4_to_u64x4(anvil_tan_f64x4(anvil_convert_u64x4_to_f64x4(X)))

#define anvil_tan_s32x1(X) anvil_convert_f32x1_to_s32x1(anvil_tan_f32x1(anvil_convert_s32x1_to_f32x1(X)))
#define anvil_tan_s32x4(X) anvil_convert_f32x4_to_s32x4(anvil_tan_f32x4(anvil_convert_s32x4_to_f32x4(X)))
#define anvil_tan_s32x8(X) anvil_convert_f32x8_to_s32x8(anvil_tan_f32x8(anvil_convert_s32x8_to_f32x8(X)))

#define anvil_tan_u32x1(X) anvil_convert_f32x1_to_u32x1(anvil_tan_f32x1(anvil_convert_u32x1_to_f32x1(X)))
#define anvil_tan_u32x4(X) anvil_convert_f32x4_to_u32x4(anvil_tan_f32x4(anvil_convert_u32x4_to_f32x4(X)))
#define anvil_tan_u32x8(X) anvil_convert_f32x8_to_u32x8(anvil_tan_f32x8(anvil_convert_u32x8_to_f32x8(X)))

#define anvil_tan_s16x1(X) anvil_convert_f32x1_to_s16x1(anvil_tan_f32x1(anvil_convert_s16x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE int16x8_t ANVIL_SIMD_CALL anvil_tan_s16x8(const register int16x8_t x) {
	ANVIL_ALIGN(16) int16x1_t a[8];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_tan_s16x1(a[0]);
	a[1] = anvil_tan_s16x1(a[1]);
	a[2] = anvil_tan_s16x1(a[2]);
	a[3] = anvil_tan_s16x1(a[3]);
	a[4] = anvil_tan_s16x1(a[4]);
	a[5] = anvil_tan_s16x1(a[5]);
	a[6] = anvil_tan_s16x1(a[6]);
	a[7] = anvil_tan_s16x1(a[7]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE int16x16_t ANVIL_SIMD_CALL anvil_tan_s16x16(const register int16x16_t x) {
	ANVIL_ALIGN(16) int16x1_t a[16];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_tan_s16x1(a[0]);
	a[1] = anvil_tan_s16x1(a[1]);
	a[2] = anvil_tan_s16x1(a[2]);
	a[3] = anvil_tan_s16x1(a[3]);
	a[4] = anvil_tan_s16x1(a[4]);
	a[5] = anvil_tan_s16x1(a[5]);
	a[6] = anvil_tan_s16x1(a[6]);
	a[7] = anvil_tan_s16x1(a[7]);
	a[8] = anvil_tan_s16x1(a[8]);
	a[9] = anvil_tan_s16x1(a[9]);
	a[10] = anvil_tan_s16x1(a[10]);
	a[11] = anvil_tan_s16x1(a[11]);
	a[12] = anvil_tan_s16x1(a[12]);
	a[13] = anvil_tan_s16x1(a[13]);
	a[14] = anvil_tan_s16x1(a[14]);
	a[15] = anvil_tan_s16x1(a[15]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

#define anvil_tan_u16x1(X) anvil_convert_f32x1_to_u16x1(anvil_tan_f32x1(anvil_convert_u16x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE uint16x8_t ANVIL_SIMD_CALL anvil_tan_u16x8(const register uint16x8_t x) {
	ANVIL_ALIGN(16) uint16x1_t a[8];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_tan_u16x1(a[0]);
	a[1] = anvil_tan_u16x1(a[1]);
	a[2] = anvil_tan_u16x1(a[2]);
	a[3] = anvil_tan_u16x1(a[3]);
	a[4] = anvil_tan_u16x1(a[4]);
	a[5] = anvil_tan_u16x1(a[5]);
	a[6] = anvil_tan_u16x1(a[6]);
	a[7] = anvil_tan_u16x1(a[7]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE uint16x16_t ANVIL_SIMD_CALL anvil_tan_u16x16(const register uint16x16_t x) {
	ANVIL_ALIGN(16) uint16x1_t a[16];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_tan_u16x1(a[0]);
	a[1] = anvil_tan_u16x1(a[1]);
	a[2] = anvil_tan_u16x1(a[2]);
	a[3] = anvil_tan_u16x1(a[3]);
	a[4] = anvil_tan_u16x1(a[4]);
	a[5] = anvil_tan_u16x1(a[5]);
	a[6] = anvil_tan_u16x1(a[6]);
	a[7] = anvil_tan_u16x1(a[7]);
	a[8] = anvil_tan_u16x1(a[8]);
	a[9] = anvil_tan_u16x1(a[9]);
	a[10] = anvil_tan_u16x1(a[10]);
	a[11] = anvil_tan_u16x1(a[11]);
	a[12] = anvil_tan_u16x1(a[12]);
	a[13] = anvil_tan_u16x1(a[13]);
	a[14] = anvil_tan_u16x1(a[14]);
	a[15] = anvil_tan_u16x1(a[15]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

#define anvil_tan_s8x1(X) anvil_convert_f32x1_to_s8x1(anvil_tan_f32x1(anvil_convert_s8x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE int8x16_t ANVIL_SIMD_CALL anvil_tan_s8x16(const register int8x16_t x) {
	ANVIL_ALIGN(16) int8x1_t a[16];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_tan_s8x1(a[0]);
	a[1] = anvil_tan_s8x1(a[1]);
	a[2] = anvil_tan_s8x1(a[2]);
	a[3] = anvil_tan_s8x1(a[3]);
	a[4] = anvil_tan_s8x1(a[4]);
	a[5] = anvil_tan_s8x1(a[5]);
	a[6] = anvil_tan_s8x1(a[6]);
	a[7] = anvil_tan_s8x1(a[7]);
	a[8] = anvil_tan_s8x1(a[8]);
	a[9] = anvil_tan_s8x1(a[9]);
	a[10] = anvil_tan_s8x1(a[10]);
	a[11] = anvil_tan_s8x1(a[11]);
	a[12] = anvil_tan_s8x1(a[12]);
	a[13] = anvil_tan_s8x1(a[13]);
	a[14] = anvil_tan_s8x1(a[14]);
	a[15] = anvil_tan_s8x1(a[15]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE int8x32_t ANVIL_SIMD_CALL anvil_tan_s8x32(const register int8x32_t x) {
	ANVIL_ALIGN(16) int8x1_t a[32];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_tan_s8x1(a[0]);
	a[1] = anvil_tan_s8x1(a[1]);
	a[2] = anvil_tan_s8x1(a[2]);
	a[3] = anvil_tan_s8x1(a[3]);
	a[4] = anvil_tan_s8x1(a[4]);
	a[5] = anvil_tan_s8x1(a[5]);
	a[6] = anvil_tan_s8x1(a[6]);
	a[7] = anvil_tan_s8x1(a[7]);
	a[8] = anvil_tan_s8x1(a[8]);
	a[9] = anvil_tan_s8x1(a[9]);
	a[10] = anvil_tan_s8x1(a[10]);
	a[11] = anvil_tan_s8x1(a[11]);
	a[12] = anvil_tan_s8x1(a[12]);
	a[13] = anvil_tan_s8x1(a[13]);
	a[14] = anvil_tan_s8x1(a[14]);
	a[15] = anvil_tan_s8x1(a[15]);
	a[16] = anvil_tan_s8x1(a[16]);
	a[17] = anvil_tan_s8x1(a[17]);
	a[18] = anvil_tan_s8x1(a[18]);
	a[19] = anvil_tan_s8x1(a[19]);
	a[20] = anvil_tan_s8x1(a[20]);
	a[21] = anvil_tan_s8x1(a[21]);
	a[22] = anvil_tan_s8x1(a[22]);
	a[23] = anvil_tan_s8x1(a[23]);
	a[24] = anvil_tan_s8x1(a[24]);
	a[25] = anvil_tan_s8x1(a[25]);
	a[26] = anvil_tan_s8x1(a[26]);
	a[27] = anvil_tan_s8x1(a[27]);
	a[28] = anvil_tan_s8x1(a[28]);
	a[29] = anvil_tan_s8x1(a[29]);
	a[30] = anvil_tan_s8x1(a[30]);
	a[31] = anvil_tan_s8x1(a[31]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

#define anvil_tan_u8x1(X) anvil_convert_f32x1_to_u8x1(anvil_tan_f32x1(anvil_convert_u8x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE uint8x16_t ANVIL_SIMD_CALL anvil_tan_u8x16(const register uint8x16_t x) {
	ANVIL_ALIGN(16) uint8x1_t a[16];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_tan_u8x1(a[0]);
	a[1] = anvil_tan_u8x1(a[1]);
	a[2] = anvil_tan_u8x1(a[2]);
	a[3] = anvil_tan_u8x1(a[3]);
	a[4] = anvil_tan_u8x1(a[4]);
	a[5] = anvil_tan_u8x1(a[5]);
	a[6] = anvil_tan_u8x1(a[6]);
	a[7] = anvil_tan_u8x1(a[7]);
	a[8] = anvil_tan_u8x1(a[8]);
	a[9] = anvil_tan_u8x1(a[9]);
	a[10] = anvil_tan_u8x1(a[10]);
	a[11] = anvil_tan_u8x1(a[11]);
	a[12] = anvil_tan_u8x1(a[12]);
	a[13] = anvil_tan_u8x1(a[13]);
	a[14] = anvil_tan_u8x1(a[14]);
	a[15] = anvil_tan_u8x1(a[15]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE uint8x32_t ANVIL_SIMD_CALL anvil_tan_u8x32(const register uint8x32_t x) {
	ANVIL_ALIGN(16) uint8x1_t a[32];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_tan_u8x1(a[0]);
	a[1] = anvil_tan_u8x1(a[1]);
	a[2] = anvil_tan_u8x1(a[2]);
	a[3] = anvil_tan_u8x1(a[3]);
	a[4] = anvil_tan_u8x1(a[4]);
	a[5] = anvil_tan_u8x1(a[5]);
	a[6] = anvil_tan_u8x1(a[6]);
	a[7] = anvil_tan_u8x1(a[7]);
	a[8] = anvil_tan_u8x1(a[8]);
	a[9] = anvil_tan_u8x1(a[9]);
	a[10] = anvil_tan_u8x1(a[10]);
	a[11] = anvil_tan_u8x1(a[11]);
	a[12] = anvil_tan_u8x1(a[12]);
	a[13] = anvil_tan_u8x1(a[13]);
	a[14] = anvil_tan_u8x1(a[14]);
	a[15] = anvil_tan_u8x1(a[15]);
	a[16] = anvil_tan_u8x1(a[16]);
	a[17] = anvil_tan_u8x1(a[17]);
	a[18] = anvil_tan_u8x1(a[18]);
	a[19] = anvil_tan_u8x1(a[19]);
	a[20] = anvil_tan_u8x1(a[20]);
	a[21] = anvil_tan_u8x1(a[21]);
	a[22] = anvil_tan_u8x1(a[22]);
	a[23] = anvil_tan_u8x1(a[23]);
	a[24] = anvil_tan_u8x1(a[24]);
	a[25] = anvil_tan_u8x1(a[25]);
	a[26] = anvil_tan_u8x1(a[26]);
	a[27] = anvil_tan_u8x1(a[27]);
	a[28] = anvil_tan_u8x1(a[28]);
	a[29] = anvil_tan_u8x1(a[29]);
	a[30] = anvil_tan_u8x1(a[30]);
	a[31] = anvil_tan_u8x1(a[31]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

// acos

#define anvil_acos_f64x1(X) std::acos(X)

static ANVIL_STRONG_INLINE float64x2_t ANVIL_SIMD_CALL anvil_acos_f64x2(const register float64x2_t x) {
	ANVIL_ALIGN(16) float64x1_t a[2];
	_mm_store_pd(a, x);
	a[0] = anvil_acos_f64x1(a[0]);
	a[1] = anvil_acos_f64x1(a[1]);
	return _mm_load_pd(a); 
}

static ANVIL_STRONG_INLINE float64x4_t ANVIL_SIMD_CALL anvil_acos_f64x4(const register float64x4_t x) {
	ANVIL_ALIGN(16) float64x1_t a[4];
	_mm256_store_pd(a, x);
	a[0] = anvil_acos_f64x1(a[0]);
	a[1] = anvil_acos_f64x1(a[1]);
	a[2] = anvil_acos_f64x1(a[2]);
	a[3] = anvil_acos_f64x1(a[3]);
	return _mm256_load_pd(a); 
}

#define anvil_acos_f32x1(X) std::acos(X)

static ANVIL_STRONG_INLINE float32x4_t ANVIL_SIMD_CALL anvil_acos_f32x4(const register float32x4_t x) {
	ANVIL_ALIGN(16) float32x1_t a[4];
	_mm_store_ps(a, x);
	a[0] = anvil_acos_f32x1(a[0]);
	a[1] = anvil_acos_f32x1(a[1]);
	a[2] = anvil_acos_f32x1(a[2]);
	a[3] = anvil_acos_f32x1(a[3]);
	return _mm_load_ps(a); 
}

static ANVIL_STRONG_INLINE float32x8_t ANVIL_SIMD_CALL anvil_acos_f32x8(const register float32x8_t x) {
	ANVIL_ALIGN(16) float32x1_t a[8];
	_mm256_store_ps(a, x);
	a[0] = anvil_acos_f32x1(a[0]);
	a[1] = anvil_acos_f32x1(a[1]);
	a[2] = anvil_acos_f32x1(a[2]);
	a[3] = anvil_acos_f32x1(a[3]);
	a[4] = anvil_acos_f32x1(a[4]);
	a[5] = anvil_acos_f32x1(a[5]);
	a[6] = anvil_acos_f32x1(a[6]);
	a[7] = anvil_acos_f32x1(a[7]);
	return _mm256_load_ps(a); 
}

#define anvil_acos_s64x1(X) anvil_convert_f64x1_to_s64x1(anvil_acos_f64x1(anvil_convert_s64x1_to_f64x1(X)))
#define anvil_acos_s64x2(X) anvil_convert_f64x2_to_s64x2(anvil_acos_f64x2(anvil_convert_s64x2_to_f64x2(X)))
#define anvil_acos_s64x4(X) anvil_convert_f64x4_to_s64x4(anvil_acos_f64x4(anvil_convert_s64x4_to_f64x4(X)))

#define anvil_acos_u64x1(X) anvil_convert_f64x1_to_u64x1(anvil_acos_f64x1(anvil_convert_u64x1_to_f64x1(X)))
#define anvil_acos_u64x2(X) anvil_convert_f64x2_to_u64x2(anvil_acos_f64x2(anvil_convert_u64x2_to_f64x2(X)))
#define anvil_acos_u64x4(X) anvil_convert_f64x4_to_u64x4(anvil_acos_f64x4(anvil_convert_u64x4_to_f64x4(X)))

#define anvil_acos_s32x1(X) anvil_convert_f32x1_to_s32x1(anvil_acos_f32x1(anvil_convert_s32x1_to_f32x1(X)))
#define anvil_acos_s32x4(X) anvil_convert_f32x4_to_s32x4(anvil_acos_f32x4(anvil_convert_s32x4_to_f32x4(X)))
#define anvil_acos_s32x8(X) anvil_convert_f32x8_to_s32x8(anvil_acos_f32x8(anvil_convert_s32x8_to_f32x8(X)))

#define anvil_acos_u32x1(X) anvil_convert_f32x1_to_u32x1(anvil_acos_f32x1(anvil_convert_u32x1_to_f32x1(X)))
#define anvil_acos_u32x4(X) anvil_convert_f32x4_to_u32x4(anvil_acos_f32x4(anvil_convert_u32x4_to_f32x4(X)))
#define anvil_acos_u32x8(X) anvil_convert_f32x8_to_u32x8(anvil_acos_f32x8(anvil_convert_u32x8_to_f32x8(X)))

#define anvil_acos_s16x1(X) anvil_convert_f32x1_to_s16x1(anvil_acos_f32x1(anvil_convert_s16x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE int16x8_t ANVIL_SIMD_CALL anvil_acos_s16x8(const register int16x8_t x) {
	ANVIL_ALIGN(16) int16x1_t a[8];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_acos_s16x1(a[0]);
	a[1] = anvil_acos_s16x1(a[1]);
	a[2] = anvil_acos_s16x1(a[2]);
	a[3] = anvil_acos_s16x1(a[3]);
	a[4] = anvil_acos_s16x1(a[4]);
	a[5] = anvil_acos_s16x1(a[5]);
	a[6] = anvil_acos_s16x1(a[6]);
	a[7] = anvil_acos_s16x1(a[7]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE int16x16_t ANVIL_SIMD_CALL anvil_acos_s16x16(const register int16x16_t x) {
	ANVIL_ALIGN(16) int16x1_t a[16];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_acos_s16x1(a[0]);
	a[1] = anvil_acos_s16x1(a[1]);
	a[2] = anvil_acos_s16x1(a[2]);
	a[3] = anvil_acos_s16x1(a[3]);
	a[4] = anvil_acos_s16x1(a[4]);
	a[5] = anvil_acos_s16x1(a[5]);
	a[6] = anvil_acos_s16x1(a[6]);
	a[7] = anvil_acos_s16x1(a[7]);
	a[8] = anvil_acos_s16x1(a[8]);
	a[9] = anvil_acos_s16x1(a[9]);
	a[10] = anvil_acos_s16x1(a[10]);
	a[11] = anvil_acos_s16x1(a[11]);
	a[12] = anvil_acos_s16x1(a[12]);
	a[13] = anvil_acos_s16x1(a[13]);
	a[14] = anvil_acos_s16x1(a[14]);
	a[15] = anvil_acos_s16x1(a[15]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

#define anvil_acos_u16x1(X) anvil_convert_f32x1_to_u16x1(anvil_acos_f32x1(anvil_convert_u16x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE uint16x8_t ANVIL_SIMD_CALL anvil_acos_u16x8(const register uint16x8_t x) {
	ANVIL_ALIGN(16) uint16x1_t a[8];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_acos_u16x1(a[0]);
	a[1] = anvil_acos_u16x1(a[1]);
	a[2] = anvil_acos_u16x1(a[2]);
	a[3] = anvil_acos_u16x1(a[3]);
	a[4] = anvil_acos_u16x1(a[4]);
	a[5] = anvil_acos_u16x1(a[5]);
	a[6] = anvil_acos_u16x1(a[6]);
	a[7] = anvil_acos_u16x1(a[7]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE uint16x16_t ANVIL_SIMD_CALL anvil_acos_u16x16(const register uint16x16_t x) {
	ANVIL_ALIGN(16) uint16x1_t a[16];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_acos_u16x1(a[0]);
	a[1] = anvil_acos_u16x1(a[1]);
	a[2] = anvil_acos_u16x1(a[2]);
	a[3] = anvil_acos_u16x1(a[3]);
	a[4] = anvil_acos_u16x1(a[4]);
	a[5] = anvil_acos_u16x1(a[5]);
	a[6] = anvil_acos_u16x1(a[6]);
	a[7] = anvil_acos_u16x1(a[7]);
	a[8] = anvil_acos_u16x1(a[8]);
	a[9] = anvil_acos_u16x1(a[9]);
	a[10] = anvil_acos_u16x1(a[10]);
	a[11] = anvil_acos_u16x1(a[11]);
	a[12] = anvil_acos_u16x1(a[12]);
	a[13] = anvil_acos_u16x1(a[13]);
	a[14] = anvil_acos_u16x1(a[14]);
	a[15] = anvil_acos_u16x1(a[15]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

#define anvil_acos_s8x1(X) anvil_convert_f32x1_to_s8x1(anvil_acos_f32x1(anvil_convert_s8x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE int8x16_t ANVIL_SIMD_CALL anvil_acos_s8x16(const register int8x16_t x) {
	ANVIL_ALIGN(16) int8x1_t a[16];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_acos_s8x1(a[0]);
	a[1] = anvil_acos_s8x1(a[1]);
	a[2] = anvil_acos_s8x1(a[2]);
	a[3] = anvil_acos_s8x1(a[3]);
	a[4] = anvil_acos_s8x1(a[4]);
	a[5] = anvil_acos_s8x1(a[5]);
	a[6] = anvil_acos_s8x1(a[6]);
	a[7] = anvil_acos_s8x1(a[7]);
	a[8] = anvil_acos_s8x1(a[8]);
	a[9] = anvil_acos_s8x1(a[9]);
	a[10] = anvil_acos_s8x1(a[10]);
	a[11] = anvil_acos_s8x1(a[11]);
	a[12] = anvil_acos_s8x1(a[12]);
	a[13] = anvil_acos_s8x1(a[13]);
	a[14] = anvil_acos_s8x1(a[14]);
	a[15] = anvil_acos_s8x1(a[15]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE int8x32_t ANVIL_SIMD_CALL anvil_acos_s8x32(const register int8x32_t x) {
	ANVIL_ALIGN(16) int8x1_t a[32];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_acos_s8x1(a[0]);
	a[1] = anvil_acos_s8x1(a[1]);
	a[2] = anvil_acos_s8x1(a[2]);
	a[3] = anvil_acos_s8x1(a[3]);
	a[4] = anvil_acos_s8x1(a[4]);
	a[5] = anvil_acos_s8x1(a[5]);
	a[6] = anvil_acos_s8x1(a[6]);
	a[7] = anvil_acos_s8x1(a[7]);
	a[8] = anvil_acos_s8x1(a[8]);
	a[9] = anvil_acos_s8x1(a[9]);
	a[10] = anvil_acos_s8x1(a[10]);
	a[11] = anvil_acos_s8x1(a[11]);
	a[12] = anvil_acos_s8x1(a[12]);
	a[13] = anvil_acos_s8x1(a[13]);
	a[14] = anvil_acos_s8x1(a[14]);
	a[15] = anvil_acos_s8x1(a[15]);
	a[16] = anvil_acos_s8x1(a[16]);
	a[17] = anvil_acos_s8x1(a[17]);
	a[18] = anvil_acos_s8x1(a[18]);
	a[19] = anvil_acos_s8x1(a[19]);
	a[20] = anvil_acos_s8x1(a[20]);
	a[21] = anvil_acos_s8x1(a[21]);
	a[22] = anvil_acos_s8x1(a[22]);
	a[23] = anvil_acos_s8x1(a[23]);
	a[24] = anvil_acos_s8x1(a[24]);
	a[25] = anvil_acos_s8x1(a[25]);
	a[26] = anvil_acos_s8x1(a[26]);
	a[27] = anvil_acos_s8x1(a[27]);
	a[28] = anvil_acos_s8x1(a[28]);
	a[29] = anvil_acos_s8x1(a[29]);
	a[30] = anvil_acos_s8x1(a[30]);
	a[31] = anvil_acos_s8x1(a[31]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

#define anvil_acos_u8x1(X) anvil_convert_f32x1_to_u8x1(anvil_acos_f32x1(anvil_convert_u8x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE uint8x16_t ANVIL_SIMD_CALL anvil_acos_u8x16(const register uint8x16_t x) {
	ANVIL_ALIGN(16) uint8x1_t a[16];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_acos_u8x1(a[0]);
	a[1] = anvil_acos_u8x1(a[1]);
	a[2] = anvil_acos_u8x1(a[2]);
	a[3] = anvil_acos_u8x1(a[3]);
	a[4] = anvil_acos_u8x1(a[4]);
	a[5] = anvil_acos_u8x1(a[5]);
	a[6] = anvil_acos_u8x1(a[6]);
	a[7] = anvil_acos_u8x1(a[7]);
	a[8] = anvil_acos_u8x1(a[8]);
	a[9] = anvil_acos_u8x1(a[9]);
	a[10] = anvil_acos_u8x1(a[10]);
	a[11] = anvil_acos_u8x1(a[11]);
	a[12] = anvil_acos_u8x1(a[12]);
	a[13] = anvil_acos_u8x1(a[13]);
	a[14] = anvil_acos_u8x1(a[14]);
	a[15] = anvil_acos_u8x1(a[15]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE uint8x32_t ANVIL_SIMD_CALL anvil_acos_u8x32(const register uint8x32_t x) {
	ANVIL_ALIGN(16) uint8x1_t a[32];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_acos_u8x1(a[0]);
	a[1] = anvil_acos_u8x1(a[1]);
	a[2] = anvil_acos_u8x1(a[2]);
	a[3] = anvil_acos_u8x1(a[3]);
	a[4] = anvil_acos_u8x1(a[4]);
	a[5] = anvil_acos_u8x1(a[5]);
	a[6] = anvil_acos_u8x1(a[6]);
	a[7] = anvil_acos_u8x1(a[7]);
	a[8] = anvil_acos_u8x1(a[8]);
	a[9] = anvil_acos_u8x1(a[9]);
	a[10] = anvil_acos_u8x1(a[10]);
	a[11] = anvil_acos_u8x1(a[11]);
	a[12] = anvil_acos_u8x1(a[12]);
	a[13] = anvil_acos_u8x1(a[13]);
	a[14] = anvil_acos_u8x1(a[14]);
	a[15] = anvil_acos_u8x1(a[15]);
	a[16] = anvil_acos_u8x1(a[16]);
	a[17] = anvil_acos_u8x1(a[17]);
	a[18] = anvil_acos_u8x1(a[18]);
	a[19] = anvil_acos_u8x1(a[19]);
	a[20] = anvil_acos_u8x1(a[20]);
	a[21] = anvil_acos_u8x1(a[21]);
	a[22] = anvil_acos_u8x1(a[22]);
	a[23] = anvil_acos_u8x1(a[23]);
	a[24] = anvil_acos_u8x1(a[24]);
	a[25] = anvil_acos_u8x1(a[25]);
	a[26] = anvil_acos_u8x1(a[26]);
	a[27] = anvil_acos_u8x1(a[27]);
	a[28] = anvil_acos_u8x1(a[28]);
	a[29] = anvil_acos_u8x1(a[29]);
	a[30] = anvil_acos_u8x1(a[30]);
	a[31] = anvil_acos_u8x1(a[31]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

// asin

#define anvil_asin_f64x1(X) std::asin(X)

static ANVIL_STRONG_INLINE float64x2_t ANVIL_SIMD_CALL anvil_asin_f64x2(const register float64x2_t x) {
	ANVIL_ALIGN(16) float64x1_t a[2];
	_mm_store_pd(a, x);
	a[0] = anvil_asin_f64x1(a[0]);
	a[1] = anvil_asin_f64x1(a[1]);
	return _mm_load_pd(a); 
}

static ANVIL_STRONG_INLINE float64x4_t ANVIL_SIMD_CALL anvil_asin_f64x4(const register float64x4_t x) {
	ANVIL_ALIGN(16) float64x1_t a[4];
	_mm256_store_pd(a, x);
	a[0] = anvil_asin_f64x1(a[0]);
	a[1] = anvil_asin_f64x1(a[1]);
	a[2] = anvil_asin_f64x1(a[2]);
	a[3] = anvil_asin_f64x1(a[3]);
	return _mm256_load_pd(a); 
}

#define anvil_asin_f32x1(X) std::asin(X)

static ANVIL_STRONG_INLINE float32x4_t ANVIL_SIMD_CALL anvil_asin_f32x4(const register float32x4_t x) {
	ANVIL_ALIGN(16) float32x1_t a[4];
	_mm_store_ps(a, x);
	a[0] = anvil_asin_f32x1(a[0]);
	a[1] = anvil_asin_f32x1(a[1]);
	a[2] = anvil_asin_f32x1(a[2]);
	a[3] = anvil_asin_f32x1(a[3]);
	return _mm_load_ps(a); 
}

static ANVIL_STRONG_INLINE float32x8_t ANVIL_SIMD_CALL anvil_asin_f32x8(const register float32x8_t x) {
	ANVIL_ALIGN(16) float32x1_t a[8];
	_mm256_store_ps(a, x);
	a[0] = anvil_asin_f32x1(a[0]);
	a[1] = anvil_asin_f32x1(a[1]);
	a[2] = anvil_asin_f32x1(a[2]);
	a[3] = anvil_asin_f32x1(a[3]);
	a[4] = anvil_asin_f32x1(a[4]);
	a[5] = anvil_asin_f32x1(a[5]);
	a[6] = anvil_asin_f32x1(a[6]);
	a[7] = anvil_asin_f32x1(a[7]);
	return _mm256_load_ps(a); 
}

#define anvil_asin_s64x1(X) anvil_convert_f64x1_to_s64x1(anvil_asin_f64x1(anvil_convert_s64x1_to_f64x1(X)))
#define anvil_asin_s64x2(X) anvil_convert_f64x2_to_s64x2(anvil_asin_f64x2(anvil_convert_s64x2_to_f64x2(X)))
#define anvil_asin_s64x4(X) anvil_convert_f64x4_to_s64x4(anvil_asin_f64x4(anvil_convert_s64x4_to_f64x4(X)))

#define anvil_asin_u64x1(X) anvil_convert_f64x1_to_u64x1(anvil_asin_f64x1(anvil_convert_u64x1_to_f64x1(X)))
#define anvil_asin_u64x2(X) anvil_convert_f64x2_to_u64x2(anvil_asin_f64x2(anvil_convert_u64x2_to_f64x2(X)))
#define anvil_asin_u64x4(X) anvil_convert_f64x4_to_u64x4(anvil_asin_f64x4(anvil_convert_u64x4_to_f64x4(X)))

#define anvil_asin_s32x1(X) anvil_convert_f32x1_to_s32x1(anvil_asin_f32x1(anvil_convert_s32x1_to_f32x1(X)))
#define anvil_asin_s32x4(X) anvil_convert_f32x4_to_s32x4(anvil_asin_f32x4(anvil_convert_s32x4_to_f32x4(X)))
#define anvil_asin_s32x8(X) anvil_convert_f32x8_to_s32x8(anvil_asin_f32x8(anvil_convert_s32x8_to_f32x8(X)))

#define anvil_asin_u32x1(X) anvil_convert_f32x1_to_u32x1(anvil_asin_f32x1(anvil_convert_u32x1_to_f32x1(X)))
#define anvil_asin_u32x4(X) anvil_convert_f32x4_to_u32x4(anvil_asin_f32x4(anvil_convert_u32x4_to_f32x4(X)))
#define anvil_asin_u32x8(X) anvil_convert_f32x8_to_u32x8(anvil_asin_f32x8(anvil_convert_u32x8_to_f32x8(X)))

#define anvil_asin_s16x1(X) anvil_convert_f32x1_to_s16x1(anvil_asin_f32x1(anvil_convert_s16x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE int16x8_t ANVIL_SIMD_CALL anvil_asin_s16x8(const register int16x8_t x) {
	ANVIL_ALIGN(16) int16x1_t a[8];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_asin_s16x1(a[0]);
	a[1] = anvil_asin_s16x1(a[1]);
	a[2] = anvil_asin_s16x1(a[2]);
	a[3] = anvil_asin_s16x1(a[3]);
	a[4] = anvil_asin_s16x1(a[4]);
	a[5] = anvil_asin_s16x1(a[5]);
	a[6] = anvil_asin_s16x1(a[6]);
	a[7] = anvil_asin_s16x1(a[7]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE int16x16_t ANVIL_SIMD_CALL anvil_asin_s16x16(const register int16x16_t x) {
	ANVIL_ALIGN(16) int16x1_t a[16];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_asin_s16x1(a[0]);
	a[1] = anvil_asin_s16x1(a[1]);
	a[2] = anvil_asin_s16x1(a[2]);
	a[3] = anvil_asin_s16x1(a[3]);
	a[4] = anvil_asin_s16x1(a[4]);
	a[5] = anvil_asin_s16x1(a[5]);
	a[6] = anvil_asin_s16x1(a[6]);
	a[7] = anvil_asin_s16x1(a[7]);
	a[8] = anvil_asin_s16x1(a[8]);
	a[9] = anvil_asin_s16x1(a[9]);
	a[10] = anvil_asin_s16x1(a[10]);
	a[11] = anvil_asin_s16x1(a[11]);
	a[12] = anvil_asin_s16x1(a[12]);
	a[13] = anvil_asin_s16x1(a[13]);
	a[14] = anvil_asin_s16x1(a[14]);
	a[15] = anvil_asin_s16x1(a[15]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

#define anvil_asin_u16x1(X) anvil_convert_f32x1_to_u16x1(anvil_asin_f32x1(anvil_convert_u16x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE uint16x8_t ANVIL_SIMD_CALL anvil_asin_u16x8(const register uint16x8_t x) {
	ANVIL_ALIGN(16) uint16x1_t a[8];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_asin_u16x1(a[0]);
	a[1] = anvil_asin_u16x1(a[1]);
	a[2] = anvil_asin_u16x1(a[2]);
	a[3] = anvil_asin_u16x1(a[3]);
	a[4] = anvil_asin_u16x1(a[4]);
	a[5] = anvil_asin_u16x1(a[5]);
	a[6] = anvil_asin_u16x1(a[6]);
	a[7] = anvil_asin_u16x1(a[7]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE uint16x16_t ANVIL_SIMD_CALL anvil_asin_u16x16(const register uint16x16_t x) {
	ANVIL_ALIGN(16) uint16x1_t a[16];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_asin_u16x1(a[0]);
	a[1] = anvil_asin_u16x1(a[1]);
	a[2] = anvil_asin_u16x1(a[2]);
	a[3] = anvil_asin_u16x1(a[3]);
	a[4] = anvil_asin_u16x1(a[4]);
	a[5] = anvil_asin_u16x1(a[5]);
	a[6] = anvil_asin_u16x1(a[6]);
	a[7] = anvil_asin_u16x1(a[7]);
	a[8] = anvil_asin_u16x1(a[8]);
	a[9] = anvil_asin_u16x1(a[9]);
	a[10] = anvil_asin_u16x1(a[10]);
	a[11] = anvil_asin_u16x1(a[11]);
	a[12] = anvil_asin_u16x1(a[12]);
	a[13] = anvil_asin_u16x1(a[13]);
	a[14] = anvil_asin_u16x1(a[14]);
	a[15] = anvil_asin_u16x1(a[15]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

#define anvil_asin_s8x1(X) anvil_convert_f32x1_to_s8x1(anvil_asin_f32x1(anvil_convert_s8x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE int8x16_t ANVIL_SIMD_CALL anvil_asin_s8x16(const register int8x16_t x) {
	ANVIL_ALIGN(16) int8x1_t a[16];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_asin_s8x1(a[0]);
	a[1] = anvil_asin_s8x1(a[1]);
	a[2] = anvil_asin_s8x1(a[2]);
	a[3] = anvil_asin_s8x1(a[3]);
	a[4] = anvil_asin_s8x1(a[4]);
	a[5] = anvil_asin_s8x1(a[5]);
	a[6] = anvil_asin_s8x1(a[6]);
	a[7] = anvil_asin_s8x1(a[7]);
	a[8] = anvil_asin_s8x1(a[8]);
	a[9] = anvil_asin_s8x1(a[9]);
	a[10] = anvil_asin_s8x1(a[10]);
	a[11] = anvil_asin_s8x1(a[11]);
	a[12] = anvil_asin_s8x1(a[12]);
	a[13] = anvil_asin_s8x1(a[13]);
	a[14] = anvil_asin_s8x1(a[14]);
	a[15] = anvil_asin_s8x1(a[15]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE int8x32_t ANVIL_SIMD_CALL anvil_asin_s8x32(const register int8x32_t x) {
	ANVIL_ALIGN(16) int8x1_t a[32];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_asin_s8x1(a[0]);
	a[1] = anvil_asin_s8x1(a[1]);
	a[2] = anvil_asin_s8x1(a[2]);
	a[3] = anvil_asin_s8x1(a[3]);
	a[4] = anvil_asin_s8x1(a[4]);
	a[5] = anvil_asin_s8x1(a[5]);
	a[6] = anvil_asin_s8x1(a[6]);
	a[7] = anvil_asin_s8x1(a[7]);
	a[8] = anvil_asin_s8x1(a[8]);
	a[9] = anvil_asin_s8x1(a[9]);
	a[10] = anvil_asin_s8x1(a[10]);
	a[11] = anvil_asin_s8x1(a[11]);
	a[12] = anvil_asin_s8x1(a[12]);
	a[13] = anvil_asin_s8x1(a[13]);
	a[14] = anvil_asin_s8x1(a[14]);
	a[15] = anvil_asin_s8x1(a[15]);
	a[16] = anvil_asin_s8x1(a[16]);
	a[17] = anvil_asin_s8x1(a[17]);
	a[18] = anvil_asin_s8x1(a[18]);
	a[19] = anvil_asin_s8x1(a[19]);
	a[20] = anvil_asin_s8x1(a[20]);
	a[21] = anvil_asin_s8x1(a[21]);
	a[22] = anvil_asin_s8x1(a[22]);
	a[23] = anvil_asin_s8x1(a[23]);
	a[24] = anvil_asin_s8x1(a[24]);
	a[25] = anvil_asin_s8x1(a[25]);
	a[26] = anvil_asin_s8x1(a[26]);
	a[27] = anvil_asin_s8x1(a[27]);
	a[28] = anvil_asin_s8x1(a[28]);
	a[29] = anvil_asin_s8x1(a[29]);
	a[30] = anvil_asin_s8x1(a[30]);
	a[31] = anvil_asin_s8x1(a[31]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

#define anvil_asin_u8x1(X) anvil_convert_f32x1_to_u8x1(anvil_asin_f32x1(anvil_convert_u8x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE uint8x16_t ANVIL_SIMD_CALL anvil_asin_u8x16(const register uint8x16_t x) {
	ANVIL_ALIGN(16) uint8x1_t a[16];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_asin_u8x1(a[0]);
	a[1] = anvil_asin_u8x1(a[1]);
	a[2] = anvil_asin_u8x1(a[2]);
	a[3] = anvil_asin_u8x1(a[3]);
	a[4] = anvil_asin_u8x1(a[4]);
	a[5] = anvil_asin_u8x1(a[5]);
	a[6] = anvil_asin_u8x1(a[6]);
	a[7] = anvil_asin_u8x1(a[7]);
	a[8] = anvil_asin_u8x1(a[8]);
	a[9] = anvil_asin_u8x1(a[9]);
	a[10] = anvil_asin_u8x1(a[10]);
	a[11] = anvil_asin_u8x1(a[11]);
	a[12] = anvil_asin_u8x1(a[12]);
	a[13] = anvil_asin_u8x1(a[13]);
	a[14] = anvil_asin_u8x1(a[14]);
	a[15] = anvil_asin_u8x1(a[15]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE uint8x32_t ANVIL_SIMD_CALL anvil_asin_u8x32(const register uint8x32_t x) {
	ANVIL_ALIGN(16) uint8x1_t a[32];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_asin_u8x1(a[0]);
	a[1] = anvil_asin_u8x1(a[1]);
	a[2] = anvil_asin_u8x1(a[2]);
	a[3] = anvil_asin_u8x1(a[3]);
	a[4] = anvil_asin_u8x1(a[4]);
	a[5] = anvil_asin_u8x1(a[5]);
	a[6] = anvil_asin_u8x1(a[6]);
	a[7] = anvil_asin_u8x1(a[7]);
	a[8] = anvil_asin_u8x1(a[8]);
	a[9] = anvil_asin_u8x1(a[9]);
	a[10] = anvil_asin_u8x1(a[10]);
	a[11] = anvil_asin_u8x1(a[11]);
	a[12] = anvil_asin_u8x1(a[12]);
	a[13] = anvil_asin_u8x1(a[13]);
	a[14] = anvil_asin_u8x1(a[14]);
	a[15] = anvil_asin_u8x1(a[15]);
	a[16] = anvil_asin_u8x1(a[16]);
	a[17] = anvil_asin_u8x1(a[17]);
	a[18] = anvil_asin_u8x1(a[18]);
	a[19] = anvil_asin_u8x1(a[19]);
	a[20] = anvil_asin_u8x1(a[20]);
	a[21] = anvil_asin_u8x1(a[21]);
	a[22] = anvil_asin_u8x1(a[22]);
	a[23] = anvil_asin_u8x1(a[23]);
	a[24] = anvil_asin_u8x1(a[24]);
	a[25] = anvil_asin_u8x1(a[25]);
	a[26] = anvil_asin_u8x1(a[26]);
	a[27] = anvil_asin_u8x1(a[27]);
	a[28] = anvil_asin_u8x1(a[28]);
	a[29] = anvil_asin_u8x1(a[29]);
	a[30] = anvil_asin_u8x1(a[30]);
	a[31] = anvil_asin_u8x1(a[31]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

// atan

#define anvil_atan_f64x1(X) std::atan(X)

static ANVIL_STRONG_INLINE float64x2_t ANVIL_SIMD_CALL anvil_atan_f64x2(const register float64x2_t x) {
	ANVIL_ALIGN(16) float64x1_t a[2];
	_mm_store_pd(a, x);
	a[0] = anvil_atan_f64x1(a[0]);
	a[1] = anvil_atan_f64x1(a[1]);
	return _mm_load_pd(a); 
}

static ANVIL_STRONG_INLINE float64x4_t ANVIL_SIMD_CALL anvil_atan_f64x4(const register float64x4_t x) {
	ANVIL_ALIGN(16) float64x1_t a[4];
	_mm256_store_pd(a, x);
	a[0] = anvil_atan_f64x1(a[0]);
	a[1] = anvil_atan_f64x1(a[1]);
	a[2] = anvil_atan_f64x1(a[2]);
	a[3] = anvil_atan_f64x1(a[3]);
	return _mm256_load_pd(a); 
}

#define anvil_atan_f32x1(X) std::atan(X)

static ANVIL_STRONG_INLINE float32x4_t ANVIL_SIMD_CALL anvil_atan_f32x4(const register float32x4_t x) {
	ANVIL_ALIGN(16) float32x1_t a[4];
	_mm_store_ps(a, x);
	a[0] = anvil_atan_f32x1(a[0]);
	a[1] = anvil_atan_f32x1(a[1]);
	a[2] = anvil_atan_f32x1(a[2]);
	a[3] = anvil_atan_f32x1(a[3]);
	return _mm_load_ps(a); 
}

static ANVIL_STRONG_INLINE float32x8_t ANVIL_SIMD_CALL anvil_atan_f32x8(const register float32x8_t x) {
	ANVIL_ALIGN(16) float32x1_t a[8];
	_mm256_store_ps(a, x);
	a[0] = anvil_atan_f32x1(a[0]);
	a[1] = anvil_atan_f32x1(a[1]);
	a[2] = anvil_atan_f32x1(a[2]);
	a[3] = anvil_atan_f32x1(a[3]);
	a[4] = anvil_atan_f32x1(a[4]);
	a[5] = anvil_atan_f32x1(a[5]);
	a[6] = anvil_atan_f32x1(a[6]);
	a[7] = anvil_atan_f32x1(a[7]);
	return _mm256_load_ps(a); 
}

#define anvil_atan_s64x1(X) anvil_convert_f64x1_to_s64x1(anvil_atan_f64x1(anvil_convert_s64x1_to_f64x1(X)))
#define anvil_atan_s64x2(X) anvil_convert_f64x2_to_s64x2(anvil_atan_f64x2(anvil_convert_s64x2_to_f64x2(X)))
#define anvil_atan_s64x4(X) anvil_convert_f64x4_to_s64x4(anvil_atan_f64x4(anvil_convert_s64x4_to_f64x4(X)))

#define anvil_atan_u64x1(X) anvil_convert_f64x1_to_u64x1(anvil_atan_f64x1(anvil_convert_u64x1_to_f64x1(X)))
#define anvil_atan_u64x2(X) anvil_convert_f64x2_to_u64x2(anvil_atan_f64x2(anvil_convert_u64x2_to_f64x2(X)))
#define anvil_atan_u64x4(X) anvil_convert_f64x4_to_u64x4(anvil_atan_f64x4(anvil_convert_u64x4_to_f64x4(X)))

#define anvil_atan_s32x1(X) anvil_convert_f32x1_to_s32x1(anvil_atan_f32x1(anvil_convert_s32x1_to_f32x1(X)))
#define anvil_atan_s32x4(X) anvil_convert_f32x4_to_s32x4(anvil_atan_f32x4(anvil_convert_s32x4_to_f32x4(X)))
#define anvil_atan_s32x8(X) anvil_convert_f32x8_to_s32x8(anvil_atan_f32x8(anvil_convert_s32x8_to_f32x8(X)))

#define anvil_atan_u32x1(X) anvil_convert_f32x1_to_u32x1(anvil_atan_f32x1(anvil_convert_u32x1_to_f32x1(X)))
#define anvil_atan_u32x4(X) anvil_convert_f32x4_to_u32x4(anvil_atan_f32x4(anvil_convert_u32x4_to_f32x4(X)))
#define anvil_atan_u32x8(X) anvil_convert_f32x8_to_u32x8(anvil_atan_f32x8(anvil_convert_u32x8_to_f32x8(X)))

#define anvil_atan_s16x1(X) anvil_convert_f32x1_to_s16x1(anvil_atan_f32x1(anvil_convert_s16x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE int16x8_t ANVIL_SIMD_CALL anvil_atan_s16x8(const register int16x8_t x) {
	ANVIL_ALIGN(16) int16x1_t a[8];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_atan_s16x1(a[0]);
	a[1] = anvil_atan_s16x1(a[1]);
	a[2] = anvil_atan_s16x1(a[2]);
	a[3] = anvil_atan_s16x1(a[3]);
	a[4] = anvil_atan_s16x1(a[4]);
	a[5] = anvil_atan_s16x1(a[5]);
	a[6] = anvil_atan_s16x1(a[6]);
	a[7] = anvil_atan_s16x1(a[7]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE int16x16_t ANVIL_SIMD_CALL anvil_atan_s16x16(const register int16x16_t x) {
	ANVIL_ALIGN(16) int16x1_t a[16];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_atan_s16x1(a[0]);
	a[1] = anvil_atan_s16x1(a[1]);
	a[2] = anvil_atan_s16x1(a[2]);
	a[3] = anvil_atan_s16x1(a[3]);
	a[4] = anvil_atan_s16x1(a[4]);
	a[5] = anvil_atan_s16x1(a[5]);
	a[6] = anvil_atan_s16x1(a[6]);
	a[7] = anvil_atan_s16x1(a[7]);
	a[8] = anvil_atan_s16x1(a[8]);
	a[9] = anvil_atan_s16x1(a[9]);
	a[10] = anvil_atan_s16x1(a[10]);
	a[11] = anvil_atan_s16x1(a[11]);
	a[12] = anvil_atan_s16x1(a[12]);
	a[13] = anvil_atan_s16x1(a[13]);
	a[14] = anvil_atan_s16x1(a[14]);
	a[15] = anvil_atan_s16x1(a[15]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

#define anvil_atan_u16x1(X) anvil_convert_f32x1_to_u16x1(anvil_atan_f32x1(anvil_convert_u16x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE uint16x8_t ANVIL_SIMD_CALL anvil_atan_u16x8(const register uint16x8_t x) {
	ANVIL_ALIGN(16) uint16x1_t a[8];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_atan_u16x1(a[0]);
	a[1] = anvil_atan_u16x1(a[1]);
	a[2] = anvil_atan_u16x1(a[2]);
	a[3] = anvil_atan_u16x1(a[3]);
	a[4] = anvil_atan_u16x1(a[4]);
	a[5] = anvil_atan_u16x1(a[5]);
	a[6] = anvil_atan_u16x1(a[6]);
	a[7] = anvil_atan_u16x1(a[7]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE uint16x16_t ANVIL_SIMD_CALL anvil_atan_u16x16(const register uint16x16_t x) {
	ANVIL_ALIGN(16) uint16x1_t a[16];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_atan_u16x1(a[0]);
	a[1] = anvil_atan_u16x1(a[1]);
	a[2] = anvil_atan_u16x1(a[2]);
	a[3] = anvil_atan_u16x1(a[3]);
	a[4] = anvil_atan_u16x1(a[4]);
	a[5] = anvil_atan_u16x1(a[5]);
	a[6] = anvil_atan_u16x1(a[6]);
	a[7] = anvil_atan_u16x1(a[7]);
	a[8] = anvil_atan_u16x1(a[8]);
	a[9] = anvil_atan_u16x1(a[9]);
	a[10] = anvil_atan_u16x1(a[10]);
	a[11] = anvil_atan_u16x1(a[11]);
	a[12] = anvil_atan_u16x1(a[12]);
	a[13] = anvil_atan_u16x1(a[13]);
	a[14] = anvil_atan_u16x1(a[14]);
	a[15] = anvil_atan_u16x1(a[15]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

#define anvil_atan_s8x1(X) anvil_convert_f32x1_to_s8x1(anvil_atan_f32x1(anvil_convert_s8x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE int8x16_t ANVIL_SIMD_CALL anvil_atan_s8x16(const register int8x16_t x) {
	ANVIL_ALIGN(16) int8x1_t a[16];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_atan_s8x1(a[0]);
	a[1] = anvil_atan_s8x1(a[1]);
	a[2] = anvil_atan_s8x1(a[2]);
	a[3] = anvil_atan_s8x1(a[3]);
	a[4] = anvil_atan_s8x1(a[4]);
	a[5] = anvil_atan_s8x1(a[5]);
	a[6] = anvil_atan_s8x1(a[6]);
	a[7] = anvil_atan_s8x1(a[7]);
	a[8] = anvil_atan_s8x1(a[8]);
	a[9] = anvil_atan_s8x1(a[9]);
	a[10] = anvil_atan_s8x1(a[10]);
	a[11] = anvil_atan_s8x1(a[11]);
	a[12] = anvil_atan_s8x1(a[12]);
	a[13] = anvil_atan_s8x1(a[13]);
	a[14] = anvil_atan_s8x1(a[14]);
	a[15] = anvil_atan_s8x1(a[15]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE int8x32_t ANVIL_SIMD_CALL anvil_atan_s8x32(const register int8x32_t x) {
	ANVIL_ALIGN(16) int8x1_t a[32];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_atan_s8x1(a[0]);
	a[1] = anvil_atan_s8x1(a[1]);
	a[2] = anvil_atan_s8x1(a[2]);
	a[3] = anvil_atan_s8x1(a[3]);
	a[4] = anvil_atan_s8x1(a[4]);
	a[5] = anvil_atan_s8x1(a[5]);
	a[6] = anvil_atan_s8x1(a[6]);
	a[7] = anvil_atan_s8x1(a[7]);
	a[8] = anvil_atan_s8x1(a[8]);
	a[9] = anvil_atan_s8x1(a[9]);
	a[10] = anvil_atan_s8x1(a[10]);
	a[11] = anvil_atan_s8x1(a[11]);
	a[12] = anvil_atan_s8x1(a[12]);
	a[13] = anvil_atan_s8x1(a[13]);
	a[14] = anvil_atan_s8x1(a[14]);
	a[15] = anvil_atan_s8x1(a[15]);
	a[16] = anvil_atan_s8x1(a[16]);
	a[17] = anvil_atan_s8x1(a[17]);
	a[18] = anvil_atan_s8x1(a[18]);
	a[19] = anvil_atan_s8x1(a[19]);
	a[20] = anvil_atan_s8x1(a[20]);
	a[21] = anvil_atan_s8x1(a[21]);
	a[22] = anvil_atan_s8x1(a[22]);
	a[23] = anvil_atan_s8x1(a[23]);
	a[24] = anvil_atan_s8x1(a[24]);
	a[25] = anvil_atan_s8x1(a[25]);
	a[26] = anvil_atan_s8x1(a[26]);
	a[27] = anvil_atan_s8x1(a[27]);
	a[28] = anvil_atan_s8x1(a[28]);
	a[29] = anvil_atan_s8x1(a[29]);
	a[30] = anvil_atan_s8x1(a[30]);
	a[31] = anvil_atan_s8x1(a[31]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

#define anvil_atan_u8x1(X) anvil_convert_f32x1_to_u8x1(anvil_atan_f32x1(anvil_convert_u8x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE uint8x16_t ANVIL_SIMD_CALL anvil_atan_u8x16(const register uint8x16_t x) {
	ANVIL_ALIGN(16) uint8x1_t a[16];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_atan_u8x1(a[0]);
	a[1] = anvil_atan_u8x1(a[1]);
	a[2] = anvil_atan_u8x1(a[2]);
	a[3] = anvil_atan_u8x1(a[3]);
	a[4] = anvil_atan_u8x1(a[4]);
	a[5] = anvil_atan_u8x1(a[5]);
	a[6] = anvil_atan_u8x1(a[6]);
	a[7] = anvil_atan_u8x1(a[7]);
	a[8] = anvil_atan_u8x1(a[8]);
	a[9] = anvil_atan_u8x1(a[9]);
	a[10] = anvil_atan_u8x1(a[10]);
	a[11] = anvil_atan_u8x1(a[11]);
	a[12] = anvil_atan_u8x1(a[12]);
	a[13] = anvil_atan_u8x1(a[13]);
	a[14] = anvil_atan_u8x1(a[14]);
	a[15] = anvil_atan_u8x1(a[15]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE uint8x32_t ANVIL_SIMD_CALL anvil_atan_u8x32(const register uint8x32_t x) {
	ANVIL_ALIGN(16) uint8x1_t a[32];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_atan_u8x1(a[0]);
	a[1] = anvil_atan_u8x1(a[1]);
	a[2] = anvil_atan_u8x1(a[2]);
	a[3] = anvil_atan_u8x1(a[3]);
	a[4] = anvil_atan_u8x1(a[4]);
	a[5] = anvil_atan_u8x1(a[5]);
	a[6] = anvil_atan_u8x1(a[6]);
	a[7] = anvil_atan_u8x1(a[7]);
	a[8] = anvil_atan_u8x1(a[8]);
	a[9] = anvil_atan_u8x1(a[9]);
	a[10] = anvil_atan_u8x1(a[10]);
	a[11] = anvil_atan_u8x1(a[11]);
	a[12] = anvil_atan_u8x1(a[12]);
	a[13] = anvil_atan_u8x1(a[13]);
	a[14] = anvil_atan_u8x1(a[14]);
	a[15] = anvil_atan_u8x1(a[15]);
	a[16] = anvil_atan_u8x1(a[16]);
	a[17] = anvil_atan_u8x1(a[17]);
	a[18] = anvil_atan_u8x1(a[18]);
	a[19] = anvil_atan_u8x1(a[19]);
	a[20] = anvil_atan_u8x1(a[20]);
	a[21] = anvil_atan_u8x1(a[21]);
	a[22] = anvil_atan_u8x1(a[22]);
	a[23] = anvil_atan_u8x1(a[23]);
	a[24] = anvil_atan_u8x1(a[24]);
	a[25] = anvil_atan_u8x1(a[25]);
	a[26] = anvil_atan_u8x1(a[26]);
	a[27] = anvil_atan_u8x1(a[27]);
	a[28] = anvil_atan_u8x1(a[28]);
	a[29] = anvil_atan_u8x1(a[29]);
	a[30] = anvil_atan_u8x1(a[30]);
	a[31] = anvil_atan_u8x1(a[31]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

// cosh

#define anvil_cosh_f64x1(X) std::cosh(X)

static ANVIL_STRONG_INLINE float64x2_t ANVIL_SIMD_CALL anvil_cosh_f64x2(const register float64x2_t x) {
	ANVIL_ALIGN(16) float64x1_t a[2];
	_mm_store_pd(a, x);
	a[0] = anvil_cosh_f64x1(a[0]);
	a[1] = anvil_cosh_f64x1(a[1]);
	return _mm_load_pd(a); 
}

static ANVIL_STRONG_INLINE float64x4_t ANVIL_SIMD_CALL anvil_cosh_f64x4(const register float64x4_t x) {
	ANVIL_ALIGN(16) float64x1_t a[4];
	_mm256_store_pd(a, x);
	a[0] = anvil_cosh_f64x1(a[0]);
	a[1] = anvil_cosh_f64x1(a[1]);
	a[2] = anvil_cosh_f64x1(a[2]);
	a[3] = anvil_cosh_f64x1(a[3]);
	return _mm256_load_pd(a); 
}

#define anvil_cosh_f32x1(X) std::cosh(X)

static ANVIL_STRONG_INLINE float32x4_t ANVIL_SIMD_CALL anvil_cosh_f32x4(const register float32x4_t x) {
	ANVIL_ALIGN(16) float32x1_t a[4];
	_mm_store_ps(a, x);
	a[0] = anvil_cosh_f32x1(a[0]);
	a[1] = anvil_cosh_f32x1(a[1]);
	a[2] = anvil_cosh_f32x1(a[2]);
	a[3] = anvil_cosh_f32x1(a[3]);
	return _mm_load_ps(a); 
}

static ANVIL_STRONG_INLINE float32x8_t ANVIL_SIMD_CALL anvil_cosh_f32x8(const register float32x8_t x) {
	ANVIL_ALIGN(16) float32x1_t a[8];
	_mm256_store_ps(a, x);
	a[0] = anvil_cosh_f32x1(a[0]);
	a[1] = anvil_cosh_f32x1(a[1]);
	a[2] = anvil_cosh_f32x1(a[2]);
	a[3] = anvil_cosh_f32x1(a[3]);
	a[4] = anvil_cosh_f32x1(a[4]);
	a[5] = anvil_cosh_f32x1(a[5]);
	a[6] = anvil_cosh_f32x1(a[6]);
	a[7] = anvil_cosh_f32x1(a[7]);
	return _mm256_load_ps(a); 
}

#define anvil_cosh_s64x1(X) anvil_convert_f64x1_to_s64x1(anvil_cosh_f64x1(anvil_convert_s64x1_to_f64x1(X)))
#define anvil_cosh_s64x2(X) anvil_convert_f64x2_to_s64x2(anvil_cosh_f64x2(anvil_convert_s64x2_to_f64x2(X)))
#define anvil_cosh_s64x4(X) anvil_convert_f64x4_to_s64x4(anvil_cosh_f64x4(anvil_convert_s64x4_to_f64x4(X)))

#define anvil_cosh_u64x1(X) anvil_convert_f64x1_to_u64x1(anvil_cosh_f64x1(anvil_convert_u64x1_to_f64x1(X)))
#define anvil_cosh_u64x2(X) anvil_convert_f64x2_to_u64x2(anvil_cosh_f64x2(anvil_convert_u64x2_to_f64x2(X)))
#define anvil_cosh_u64x4(X) anvil_convert_f64x4_to_u64x4(anvil_cosh_f64x4(anvil_convert_u64x4_to_f64x4(X)))

#define anvil_cosh_s32x1(X) anvil_convert_f32x1_to_s32x1(anvil_cosh_f32x1(anvil_convert_s32x1_to_f32x1(X)))
#define anvil_cosh_s32x4(X) anvil_convert_f32x4_to_s32x4(anvil_cosh_f32x4(anvil_convert_s32x4_to_f32x4(X)))
#define anvil_cosh_s32x8(X) anvil_convert_f32x8_to_s32x8(anvil_cosh_f32x8(anvil_convert_s32x8_to_f32x8(X)))

#define anvil_cosh_u32x1(X) anvil_convert_f32x1_to_u32x1(anvil_cosh_f32x1(anvil_convert_u32x1_to_f32x1(X)))
#define anvil_cosh_u32x4(X) anvil_convert_f32x4_to_u32x4(anvil_cosh_f32x4(anvil_convert_u32x4_to_f32x4(X)))
#define anvil_cosh_u32x8(X) anvil_convert_f32x8_to_u32x8(anvil_cosh_f32x8(anvil_convert_u32x8_to_f32x8(X)))

#define anvil_cosh_s16x1(X) anvil_convert_f32x1_to_s16x1(anvil_cosh_f32x1(anvil_convert_s16x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE int16x8_t ANVIL_SIMD_CALL anvil_cosh_s16x8(const register int16x8_t x) {
	ANVIL_ALIGN(16) int16x1_t a[8];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_cosh_s16x1(a[0]);
	a[1] = anvil_cosh_s16x1(a[1]);
	a[2] = anvil_cosh_s16x1(a[2]);
	a[3] = anvil_cosh_s16x1(a[3]);
	a[4] = anvil_cosh_s16x1(a[4]);
	a[5] = anvil_cosh_s16x1(a[5]);
	a[6] = anvil_cosh_s16x1(a[6]);
	a[7] = anvil_cosh_s16x1(a[7]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE int16x16_t ANVIL_SIMD_CALL anvil_cosh_s16x16(const register int16x16_t x) {
	ANVIL_ALIGN(16) int16x1_t a[16];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_cosh_s16x1(a[0]);
	a[1] = anvil_cosh_s16x1(a[1]);
	a[2] = anvil_cosh_s16x1(a[2]);
	a[3] = anvil_cosh_s16x1(a[3]);
	a[4] = anvil_cosh_s16x1(a[4]);
	a[5] = anvil_cosh_s16x1(a[5]);
	a[6] = anvil_cosh_s16x1(a[6]);
	a[7] = anvil_cosh_s16x1(a[7]);
	a[8] = anvil_cosh_s16x1(a[8]);
	a[9] = anvil_cosh_s16x1(a[9]);
	a[10] = anvil_cosh_s16x1(a[10]);
	a[11] = anvil_cosh_s16x1(a[11]);
	a[12] = anvil_cosh_s16x1(a[12]);
	a[13] = anvil_cosh_s16x1(a[13]);
	a[14] = anvil_cosh_s16x1(a[14]);
	a[15] = anvil_cosh_s16x1(a[15]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

#define anvil_cosh_u16x1(X) anvil_convert_f32x1_to_u16x1(anvil_cosh_f32x1(anvil_convert_u16x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE uint16x8_t ANVIL_SIMD_CALL anvil_cosh_u16x8(const register uint16x8_t x) {
	ANVIL_ALIGN(16) uint16x1_t a[8];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_cosh_u16x1(a[0]);
	a[1] = anvil_cosh_u16x1(a[1]);
	a[2] = anvil_cosh_u16x1(a[2]);
	a[3] = anvil_cosh_u16x1(a[3]);
	a[4] = anvil_cosh_u16x1(a[4]);
	a[5] = anvil_cosh_u16x1(a[5]);
	a[6] = anvil_cosh_u16x1(a[6]);
	a[7] = anvil_cosh_u16x1(a[7]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE uint16x16_t ANVIL_SIMD_CALL anvil_cosh_u16x16(const register uint16x16_t x) {
	ANVIL_ALIGN(16) uint16x1_t a[16];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_cosh_u16x1(a[0]);
	a[1] = anvil_cosh_u16x1(a[1]);
	a[2] = anvil_cosh_u16x1(a[2]);
	a[3] = anvil_cosh_u16x1(a[3]);
	a[4] = anvil_cosh_u16x1(a[4]);
	a[5] = anvil_cosh_u16x1(a[5]);
	a[6] = anvil_cosh_u16x1(a[6]);
	a[7] = anvil_cosh_u16x1(a[7]);
	a[8] = anvil_cosh_u16x1(a[8]);
	a[9] = anvil_cosh_u16x1(a[9]);
	a[10] = anvil_cosh_u16x1(a[10]);
	a[11] = anvil_cosh_u16x1(a[11]);
	a[12] = anvil_cosh_u16x1(a[12]);
	a[13] = anvil_cosh_u16x1(a[13]);
	a[14] = anvil_cosh_u16x1(a[14]);
	a[15] = anvil_cosh_u16x1(a[15]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

#define anvil_cosh_s8x1(X) anvil_convert_f32x1_to_s8x1(anvil_cosh_f32x1(anvil_convert_s8x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE int8x16_t ANVIL_SIMD_CALL anvil_cosh_s8x16(const register int8x16_t x) {
	ANVIL_ALIGN(16) int8x1_t a[16];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_cosh_s8x1(a[0]);
	a[1] = anvil_cosh_s8x1(a[1]);
	a[2] = anvil_cosh_s8x1(a[2]);
	a[3] = anvil_cosh_s8x1(a[3]);
	a[4] = anvil_cosh_s8x1(a[4]);
	a[5] = anvil_cosh_s8x1(a[5]);
	a[6] = anvil_cosh_s8x1(a[6]);
	a[7] = anvil_cosh_s8x1(a[7]);
	a[8] = anvil_cosh_s8x1(a[8]);
	a[9] = anvil_cosh_s8x1(a[9]);
	a[10] = anvil_cosh_s8x1(a[10]);
	a[11] = anvil_cosh_s8x1(a[11]);
	a[12] = anvil_cosh_s8x1(a[12]);
	a[13] = anvil_cosh_s8x1(a[13]);
	a[14] = anvil_cosh_s8x1(a[14]);
	a[15] = anvil_cosh_s8x1(a[15]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE int8x32_t ANVIL_SIMD_CALL anvil_cosh_s8x32(const register int8x32_t x) {
	ANVIL_ALIGN(16) int8x1_t a[32];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_cosh_s8x1(a[0]);
	a[1] = anvil_cosh_s8x1(a[1]);
	a[2] = anvil_cosh_s8x1(a[2]);
	a[3] = anvil_cosh_s8x1(a[3]);
	a[4] = anvil_cosh_s8x1(a[4]);
	a[5] = anvil_cosh_s8x1(a[5]);
	a[6] = anvil_cosh_s8x1(a[6]);
	a[7] = anvil_cosh_s8x1(a[7]);
	a[8] = anvil_cosh_s8x1(a[8]);
	a[9] = anvil_cosh_s8x1(a[9]);
	a[10] = anvil_cosh_s8x1(a[10]);
	a[11] = anvil_cosh_s8x1(a[11]);
	a[12] = anvil_cosh_s8x1(a[12]);
	a[13] = anvil_cosh_s8x1(a[13]);
	a[14] = anvil_cosh_s8x1(a[14]);
	a[15] = anvil_cosh_s8x1(a[15]);
	a[16] = anvil_cosh_s8x1(a[16]);
	a[17] = anvil_cosh_s8x1(a[17]);
	a[18] = anvil_cosh_s8x1(a[18]);
	a[19] = anvil_cosh_s8x1(a[19]);
	a[20] = anvil_cosh_s8x1(a[20]);
	a[21] = anvil_cosh_s8x1(a[21]);
	a[22] = anvil_cosh_s8x1(a[22]);
	a[23] = anvil_cosh_s8x1(a[23]);
	a[24] = anvil_cosh_s8x1(a[24]);
	a[25] = anvil_cosh_s8x1(a[25]);
	a[26] = anvil_cosh_s8x1(a[26]);
	a[27] = anvil_cosh_s8x1(a[27]);
	a[28] = anvil_cosh_s8x1(a[28]);
	a[29] = anvil_cosh_s8x1(a[29]);
	a[30] = anvil_cosh_s8x1(a[30]);
	a[31] = anvil_cosh_s8x1(a[31]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

#define anvil_cosh_u8x1(X) anvil_convert_f32x1_to_u8x1(anvil_cosh_f32x1(anvil_convert_u8x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE uint8x16_t ANVIL_SIMD_CALL anvil_cosh_u8x16(const register uint8x16_t x) {
	ANVIL_ALIGN(16) uint8x1_t a[16];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_cosh_u8x1(a[0]);
	a[1] = anvil_cosh_u8x1(a[1]);
	a[2] = anvil_cosh_u8x1(a[2]);
	a[3] = anvil_cosh_u8x1(a[3]);
	a[4] = anvil_cosh_u8x1(a[4]);
	a[5] = anvil_cosh_u8x1(a[5]);
	a[6] = anvil_cosh_u8x1(a[6]);
	a[7] = anvil_cosh_u8x1(a[7]);
	a[8] = anvil_cosh_u8x1(a[8]);
	a[9] = anvil_cosh_u8x1(a[9]);
	a[10] = anvil_cosh_u8x1(a[10]);
	a[11] = anvil_cosh_u8x1(a[11]);
	a[12] = anvil_cosh_u8x1(a[12]);
	a[13] = anvil_cosh_u8x1(a[13]);
	a[14] = anvil_cosh_u8x1(a[14]);
	a[15] = anvil_cosh_u8x1(a[15]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE uint8x32_t ANVIL_SIMD_CALL anvil_cosh_u8x32(const register uint8x32_t x) {
	ANVIL_ALIGN(16) uint8x1_t a[32];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_cosh_u8x1(a[0]);
	a[1] = anvil_cosh_u8x1(a[1]);
	a[2] = anvil_cosh_u8x1(a[2]);
	a[3] = anvil_cosh_u8x1(a[3]);
	a[4] = anvil_cosh_u8x1(a[4]);
	a[5] = anvil_cosh_u8x1(a[5]);
	a[6] = anvil_cosh_u8x1(a[6]);
	a[7] = anvil_cosh_u8x1(a[7]);
	a[8] = anvil_cosh_u8x1(a[8]);
	a[9] = anvil_cosh_u8x1(a[9]);
	a[10] = anvil_cosh_u8x1(a[10]);
	a[11] = anvil_cosh_u8x1(a[11]);
	a[12] = anvil_cosh_u8x1(a[12]);
	a[13] = anvil_cosh_u8x1(a[13]);
	a[14] = anvil_cosh_u8x1(a[14]);
	a[15] = anvil_cosh_u8x1(a[15]);
	a[16] = anvil_cosh_u8x1(a[16]);
	a[17] = anvil_cosh_u8x1(a[17]);
	a[18] = anvil_cosh_u8x1(a[18]);
	a[19] = anvil_cosh_u8x1(a[19]);
	a[20] = anvil_cosh_u8x1(a[20]);
	a[21] = anvil_cosh_u8x1(a[21]);
	a[22] = anvil_cosh_u8x1(a[22]);
	a[23] = anvil_cosh_u8x1(a[23]);
	a[24] = anvil_cosh_u8x1(a[24]);
	a[25] = anvil_cosh_u8x1(a[25]);
	a[26] = anvil_cosh_u8x1(a[26]);
	a[27] = anvil_cosh_u8x1(a[27]);
	a[28] = anvil_cosh_u8x1(a[28]);
	a[29] = anvil_cosh_u8x1(a[29]);
	a[30] = anvil_cosh_u8x1(a[30]);
	a[31] = anvil_cosh_u8x1(a[31]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

// sinh

#define anvil_sinh_f64x1(X) std::sinh(X)

static ANVIL_STRONG_INLINE float64x2_t ANVIL_SIMD_CALL anvil_sinh_f64x2(const register float64x2_t x) {
	ANVIL_ALIGN(16) float64x1_t a[2];
	_mm_store_pd(a, x);
	a[0] = anvil_sinh_f64x1(a[0]);
	a[1] = anvil_sinh_f64x1(a[1]);
	return _mm_load_pd(a); 
}

static ANVIL_STRONG_INLINE float64x4_t ANVIL_SIMD_CALL anvil_sinh_f64x4(const register float64x4_t x) {
	ANVIL_ALIGN(16) float64x1_t a[4];
	_mm256_store_pd(a, x);
	a[0] = anvil_sinh_f64x1(a[0]);
	a[1] = anvil_sinh_f64x1(a[1]);
	a[2] = anvil_sinh_f64x1(a[2]);
	a[3] = anvil_sinh_f64x1(a[3]);
	return _mm256_load_pd(a); 
}

#define anvil_sinh_f32x1(X) std::sinh(X)

static ANVIL_STRONG_INLINE float32x4_t ANVIL_SIMD_CALL anvil_sinh_f32x4(const register float32x4_t x) {
	ANVIL_ALIGN(16) float32x1_t a[4];
	_mm_store_ps(a, x);
	a[0] = anvil_sinh_f32x1(a[0]);
	a[1] = anvil_sinh_f32x1(a[1]);
	a[2] = anvil_sinh_f32x1(a[2]);
	a[3] = anvil_sinh_f32x1(a[3]);
	return _mm_load_ps(a); 
}

static ANVIL_STRONG_INLINE float32x8_t ANVIL_SIMD_CALL anvil_sinh_f32x8(const register float32x8_t x) {
	ANVIL_ALIGN(16) float32x1_t a[8];
	_mm256_store_ps(a, x);
	a[0] = anvil_sinh_f32x1(a[0]);
	a[1] = anvil_sinh_f32x1(a[1]);
	a[2] = anvil_sinh_f32x1(a[2]);
	a[3] = anvil_sinh_f32x1(a[3]);
	a[4] = anvil_sinh_f32x1(a[4]);
	a[5] = anvil_sinh_f32x1(a[5]);
	a[6] = anvil_sinh_f32x1(a[6]);
	a[7] = anvil_sinh_f32x1(a[7]);
	return _mm256_load_ps(a); 
}

#define anvil_sinh_s64x1(X) anvil_convert_f64x1_to_s64x1(anvil_sinh_f64x1(anvil_convert_s64x1_to_f64x1(X)))
#define anvil_sinh_s64x2(X) anvil_convert_f64x2_to_s64x2(anvil_sinh_f64x2(anvil_convert_s64x2_to_f64x2(X)))
#define anvil_sinh_s64x4(X) anvil_convert_f64x4_to_s64x4(anvil_sinh_f64x4(anvil_convert_s64x4_to_f64x4(X)))

#define anvil_sinh_u64x1(X) anvil_convert_f64x1_to_u64x1(anvil_sinh_f64x1(anvil_convert_u64x1_to_f64x1(X)))
#define anvil_sinh_u64x2(X) anvil_convert_f64x2_to_u64x2(anvil_sinh_f64x2(anvil_convert_u64x2_to_f64x2(X)))
#define anvil_sinh_u64x4(X) anvil_convert_f64x4_to_u64x4(anvil_sinh_f64x4(anvil_convert_u64x4_to_f64x4(X)))

#define anvil_sinh_s32x1(X) anvil_convert_f32x1_to_s32x1(anvil_sinh_f32x1(anvil_convert_s32x1_to_f32x1(X)))
#define anvil_sinh_s32x4(X) anvil_convert_f32x4_to_s32x4(anvil_sinh_f32x4(anvil_convert_s32x4_to_f32x4(X)))
#define anvil_sinh_s32x8(X) anvil_convert_f32x8_to_s32x8(anvil_sinh_f32x8(anvil_convert_s32x8_to_f32x8(X)))

#define anvil_sinh_u32x1(X) anvil_convert_f32x1_to_u32x1(anvil_sinh_f32x1(anvil_convert_u32x1_to_f32x1(X)))
#define anvil_sinh_u32x4(X) anvil_convert_f32x4_to_u32x4(anvil_sinh_f32x4(anvil_convert_u32x4_to_f32x4(X)))
#define anvil_sinh_u32x8(X) anvil_convert_f32x8_to_u32x8(anvil_sinh_f32x8(anvil_convert_u32x8_to_f32x8(X)))

#define anvil_sinh_s16x1(X) anvil_convert_f32x1_to_s16x1(anvil_sinh_f32x1(anvil_convert_s16x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE int16x8_t ANVIL_SIMD_CALL anvil_sinh_s16x8(const register int16x8_t x) {
	ANVIL_ALIGN(16) int16x1_t a[8];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_sinh_s16x1(a[0]);
	a[1] = anvil_sinh_s16x1(a[1]);
	a[2] = anvil_sinh_s16x1(a[2]);
	a[3] = anvil_sinh_s16x1(a[3]);
	a[4] = anvil_sinh_s16x1(a[4]);
	a[5] = anvil_sinh_s16x1(a[5]);
	a[6] = anvil_sinh_s16x1(a[6]);
	a[7] = anvil_sinh_s16x1(a[7]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE int16x16_t ANVIL_SIMD_CALL anvil_sinh_s16x16(const register int16x16_t x) {
	ANVIL_ALIGN(16) int16x1_t a[16];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_sinh_s16x1(a[0]);
	a[1] = anvil_sinh_s16x1(a[1]);
	a[2] = anvil_sinh_s16x1(a[2]);
	a[3] = anvil_sinh_s16x1(a[3]);
	a[4] = anvil_sinh_s16x1(a[4]);
	a[5] = anvil_sinh_s16x1(a[5]);
	a[6] = anvil_sinh_s16x1(a[6]);
	a[7] = anvil_sinh_s16x1(a[7]);
	a[8] = anvil_sinh_s16x1(a[8]);
	a[9] = anvil_sinh_s16x1(a[9]);
	a[10] = anvil_sinh_s16x1(a[10]);
	a[11] = anvil_sinh_s16x1(a[11]);
	a[12] = anvil_sinh_s16x1(a[12]);
	a[13] = anvil_sinh_s16x1(a[13]);
	a[14] = anvil_sinh_s16x1(a[14]);
	a[15] = anvil_sinh_s16x1(a[15]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

#define anvil_sinh_u16x1(X) anvil_convert_f32x1_to_u16x1(anvil_sinh_f32x1(anvil_convert_u16x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE uint16x8_t ANVIL_SIMD_CALL anvil_sinh_u16x8(const register uint16x8_t x) {
	ANVIL_ALIGN(16) uint16x1_t a[8];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_sinh_u16x1(a[0]);
	a[1] = anvil_sinh_u16x1(a[1]);
	a[2] = anvil_sinh_u16x1(a[2]);
	a[3] = anvil_sinh_u16x1(a[3]);
	a[4] = anvil_sinh_u16x1(a[4]);
	a[5] = anvil_sinh_u16x1(a[5]);
	a[6] = anvil_sinh_u16x1(a[6]);
	a[7] = anvil_sinh_u16x1(a[7]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE uint16x16_t ANVIL_SIMD_CALL anvil_sinh_u16x16(const register uint16x16_t x) {
	ANVIL_ALIGN(16) uint16x1_t a[16];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_sinh_u16x1(a[0]);
	a[1] = anvil_sinh_u16x1(a[1]);
	a[2] = anvil_sinh_u16x1(a[2]);
	a[3] = anvil_sinh_u16x1(a[3]);
	a[4] = anvil_sinh_u16x1(a[4]);
	a[5] = anvil_sinh_u16x1(a[5]);
	a[6] = anvil_sinh_u16x1(a[6]);
	a[7] = anvil_sinh_u16x1(a[7]);
	a[8] = anvil_sinh_u16x1(a[8]);
	a[9] = anvil_sinh_u16x1(a[9]);
	a[10] = anvil_sinh_u16x1(a[10]);
	a[11] = anvil_sinh_u16x1(a[11]);
	a[12] = anvil_sinh_u16x1(a[12]);
	a[13] = anvil_sinh_u16x1(a[13]);
	a[14] = anvil_sinh_u16x1(a[14]);
	a[15] = anvil_sinh_u16x1(a[15]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

#define anvil_sinh_s8x1(X) anvil_convert_f32x1_to_s8x1(anvil_sinh_f32x1(anvil_convert_s8x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE int8x16_t ANVIL_SIMD_CALL anvil_sinh_s8x16(const register int8x16_t x) {
	ANVIL_ALIGN(16) int8x1_t a[16];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_sinh_s8x1(a[0]);
	a[1] = anvil_sinh_s8x1(a[1]);
	a[2] = anvil_sinh_s8x1(a[2]);
	a[3] = anvil_sinh_s8x1(a[3]);
	a[4] = anvil_sinh_s8x1(a[4]);
	a[5] = anvil_sinh_s8x1(a[5]);
	a[6] = anvil_sinh_s8x1(a[6]);
	a[7] = anvil_sinh_s8x1(a[7]);
	a[8] = anvil_sinh_s8x1(a[8]);
	a[9] = anvil_sinh_s8x1(a[9]);
	a[10] = anvil_sinh_s8x1(a[10]);
	a[11] = anvil_sinh_s8x1(a[11]);
	a[12] = anvil_sinh_s8x1(a[12]);
	a[13] = anvil_sinh_s8x1(a[13]);
	a[14] = anvil_sinh_s8x1(a[14]);
	a[15] = anvil_sinh_s8x1(a[15]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE int8x32_t ANVIL_SIMD_CALL anvil_sinh_s8x32(const register int8x32_t x) {
	ANVIL_ALIGN(16) int8x1_t a[32];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_sinh_s8x1(a[0]);
	a[1] = anvil_sinh_s8x1(a[1]);
	a[2] = anvil_sinh_s8x1(a[2]);
	a[3] = anvil_sinh_s8x1(a[3]);
	a[4] = anvil_sinh_s8x1(a[4]);
	a[5] = anvil_sinh_s8x1(a[5]);
	a[6] = anvil_sinh_s8x1(a[6]);
	a[7] = anvil_sinh_s8x1(a[7]);
	a[8] = anvil_sinh_s8x1(a[8]);
	a[9] = anvil_sinh_s8x1(a[9]);
	a[10] = anvil_sinh_s8x1(a[10]);
	a[11] = anvil_sinh_s8x1(a[11]);
	a[12] = anvil_sinh_s8x1(a[12]);
	a[13] = anvil_sinh_s8x1(a[13]);
	a[14] = anvil_sinh_s8x1(a[14]);
	a[15] = anvil_sinh_s8x1(a[15]);
	a[16] = anvil_sinh_s8x1(a[16]);
	a[17] = anvil_sinh_s8x1(a[17]);
	a[18] = anvil_sinh_s8x1(a[18]);
	a[19] = anvil_sinh_s8x1(a[19]);
	a[20] = anvil_sinh_s8x1(a[20]);
	a[21] = anvil_sinh_s8x1(a[21]);
	a[22] = anvil_sinh_s8x1(a[22]);
	a[23] = anvil_sinh_s8x1(a[23]);
	a[24] = anvil_sinh_s8x1(a[24]);
	a[25] = anvil_sinh_s8x1(a[25]);
	a[26] = anvil_sinh_s8x1(a[26]);
	a[27] = anvil_sinh_s8x1(a[27]);
	a[28] = anvil_sinh_s8x1(a[28]);
	a[29] = anvil_sinh_s8x1(a[29]);
	a[30] = anvil_sinh_s8x1(a[30]);
	a[31] = anvil_sinh_s8x1(a[31]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

#define anvil_sinh_u8x1(X) anvil_convert_f32x1_to_u8x1(anvil_sinh_f32x1(anvil_convert_u8x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE uint8x16_t ANVIL_SIMD_CALL anvil_sinh_u8x16(const register uint8x16_t x) {
	ANVIL_ALIGN(16) uint8x1_t a[16];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_sinh_u8x1(a[0]);
	a[1] = anvil_sinh_u8x1(a[1]);
	a[2] = anvil_sinh_u8x1(a[2]);
	a[3] = anvil_sinh_u8x1(a[3]);
	a[4] = anvil_sinh_u8x1(a[4]);
	a[5] = anvil_sinh_u8x1(a[5]);
	a[6] = anvil_sinh_u8x1(a[6]);
	a[7] = anvil_sinh_u8x1(a[7]);
	a[8] = anvil_sinh_u8x1(a[8]);
	a[9] = anvil_sinh_u8x1(a[9]);
	a[10] = anvil_sinh_u8x1(a[10]);
	a[11] = anvil_sinh_u8x1(a[11]);
	a[12] = anvil_sinh_u8x1(a[12]);
	a[13] = anvil_sinh_u8x1(a[13]);
	a[14] = anvil_sinh_u8x1(a[14]);
	a[15] = anvil_sinh_u8x1(a[15]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE uint8x32_t ANVIL_SIMD_CALL anvil_sinh_u8x32(const register uint8x32_t x) {
	ANVIL_ALIGN(16) uint8x1_t a[32];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_sinh_u8x1(a[0]);
	a[1] = anvil_sinh_u8x1(a[1]);
	a[2] = anvil_sinh_u8x1(a[2]);
	a[3] = anvil_sinh_u8x1(a[3]);
	a[4] = anvil_sinh_u8x1(a[4]);
	a[5] = anvil_sinh_u8x1(a[5]);
	a[6] = anvil_sinh_u8x1(a[6]);
	a[7] = anvil_sinh_u8x1(a[7]);
	a[8] = anvil_sinh_u8x1(a[8]);
	a[9] = anvil_sinh_u8x1(a[9]);
	a[10] = anvil_sinh_u8x1(a[10]);
	a[11] = anvil_sinh_u8x1(a[11]);
	a[12] = anvil_sinh_u8x1(a[12]);
	a[13] = anvil_sinh_u8x1(a[13]);
	a[14] = anvil_sinh_u8x1(a[14]);
	a[15] = anvil_sinh_u8x1(a[15]);
	a[16] = anvil_sinh_u8x1(a[16]);
	a[17] = anvil_sinh_u8x1(a[17]);
	a[18] = anvil_sinh_u8x1(a[18]);
	a[19] = anvil_sinh_u8x1(a[19]);
	a[20] = anvil_sinh_u8x1(a[20]);
	a[21] = anvil_sinh_u8x1(a[21]);
	a[22] = anvil_sinh_u8x1(a[22]);
	a[23] = anvil_sinh_u8x1(a[23]);
	a[24] = anvil_sinh_u8x1(a[24]);
	a[25] = anvil_sinh_u8x1(a[25]);
	a[26] = anvil_sinh_u8x1(a[26]);
	a[27] = anvil_sinh_u8x1(a[27]);
	a[28] = anvil_sinh_u8x1(a[28]);
	a[29] = anvil_sinh_u8x1(a[29]);
	a[30] = anvil_sinh_u8x1(a[30]);
	a[31] = anvil_sinh_u8x1(a[31]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

// tanh

#define anvil_tanh_f64x1(X) std::tanh(X)

static ANVIL_STRONG_INLINE float64x2_t ANVIL_SIMD_CALL anvil_tanh_f64x2(const register float64x2_t x) {
	ANVIL_ALIGN(16) float64x1_t a[2];
	_mm_store_pd(a, x);
	a[0] = anvil_tanh_f64x1(a[0]);
	a[1] = anvil_tanh_f64x1(a[1]);
	return _mm_load_pd(a); 
}

static ANVIL_STRONG_INLINE float64x4_t ANVIL_SIMD_CALL anvil_tanh_f64x4(const register float64x4_t x) {
	ANVIL_ALIGN(16) float64x1_t a[4];
	_mm256_store_pd(a, x);
	a[0] = anvil_tanh_f64x1(a[0]);
	a[1] = anvil_tanh_f64x1(a[1]);
	a[2] = anvil_tanh_f64x1(a[2]);
	a[3] = anvil_tanh_f64x1(a[3]);
	return _mm256_load_pd(a); 
}

#define anvil_tanh_f32x1(X) std::tanh(X)

static ANVIL_STRONG_INLINE float32x4_t ANVIL_SIMD_CALL anvil_tanh_f32x4(const register float32x4_t x) {
	ANVIL_ALIGN(16) float32x1_t a[4];
	_mm_store_ps(a, x);
	a[0] = anvil_tanh_f32x1(a[0]);
	a[1] = anvil_tanh_f32x1(a[1]);
	a[2] = anvil_tanh_f32x1(a[2]);
	a[3] = anvil_tanh_f32x1(a[3]);
	return _mm_load_ps(a); 
}

static ANVIL_STRONG_INLINE float32x8_t ANVIL_SIMD_CALL anvil_tanh_f32x8(const register float32x8_t x) {
	ANVIL_ALIGN(16) float32x1_t a[8];
	_mm256_store_ps(a, x);
	a[0] = anvil_tanh_f32x1(a[0]);
	a[1] = anvil_tanh_f32x1(a[1]);
	a[2] = anvil_tanh_f32x1(a[2]);
	a[3] = anvil_tanh_f32x1(a[3]);
	a[4] = anvil_tanh_f32x1(a[4]);
	a[5] = anvil_tanh_f32x1(a[5]);
	a[6] = anvil_tanh_f32x1(a[6]);
	a[7] = anvil_tanh_f32x1(a[7]);
	return _mm256_load_ps(a); 
}

#define anvil_tanh_s64x1(X) anvil_convert_f64x1_to_s64x1(anvil_tanh_f64x1(anvil_convert_s64x1_to_f64x1(X)))
#define anvil_tanh_s64x2(X) anvil_convert_f64x2_to_s64x2(anvil_tanh_f64x2(anvil_convert_s64x2_to_f64x2(X)))
#define anvil_tanh_s64x4(X) anvil_convert_f64x4_to_s64x4(anvil_tanh_f64x4(anvil_convert_s64x4_to_f64x4(X)))

#define anvil_tanh_u64x1(X) anvil_convert_f64x1_to_u64x1(anvil_tanh_f64x1(anvil_convert_u64x1_to_f64x1(X)))
#define anvil_tanh_u64x2(X) anvil_convert_f64x2_to_u64x2(anvil_tanh_f64x2(anvil_convert_u64x2_to_f64x2(X)))
#define anvil_tanh_u64x4(X) anvil_convert_f64x4_to_u64x4(anvil_tanh_f64x4(anvil_convert_u64x4_to_f64x4(X)))

#define anvil_tanh_s32x1(X) anvil_convert_f32x1_to_s32x1(anvil_tanh_f32x1(anvil_convert_s32x1_to_f32x1(X)))
#define anvil_tanh_s32x4(X) anvil_convert_f32x4_to_s32x4(anvil_tanh_f32x4(anvil_convert_s32x4_to_f32x4(X)))
#define anvil_tanh_s32x8(X) anvil_convert_f32x8_to_s32x8(anvil_tanh_f32x8(anvil_convert_s32x8_to_f32x8(X)))

#define anvil_tanh_u32x1(X) anvil_convert_f32x1_to_u32x1(anvil_tanh_f32x1(anvil_convert_u32x1_to_f32x1(X)))
#define anvil_tanh_u32x4(X) anvil_convert_f32x4_to_u32x4(anvil_tanh_f32x4(anvil_convert_u32x4_to_f32x4(X)))
#define anvil_tanh_u32x8(X) anvil_convert_f32x8_to_u32x8(anvil_tanh_f32x8(anvil_convert_u32x8_to_f32x8(X)))

#define anvil_tanh_s16x1(X) anvil_convert_f32x1_to_s16x1(anvil_tanh_f32x1(anvil_convert_s16x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE int16x8_t ANVIL_SIMD_CALL anvil_tanh_s16x8(const register int16x8_t x) {
	ANVIL_ALIGN(16) int16x1_t a[8];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_tanh_s16x1(a[0]);
	a[1] = anvil_tanh_s16x1(a[1]);
	a[2] = anvil_tanh_s16x1(a[2]);
	a[3] = anvil_tanh_s16x1(a[3]);
	a[4] = anvil_tanh_s16x1(a[4]);
	a[5] = anvil_tanh_s16x1(a[5]);
	a[6] = anvil_tanh_s16x1(a[6]);
	a[7] = anvil_tanh_s16x1(a[7]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE int16x16_t ANVIL_SIMD_CALL anvil_tanh_s16x16(const register int16x16_t x) {
	ANVIL_ALIGN(16) int16x1_t a[16];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_tanh_s16x1(a[0]);
	a[1] = anvil_tanh_s16x1(a[1]);
	a[2] = anvil_tanh_s16x1(a[2]);
	a[3] = anvil_tanh_s16x1(a[3]);
	a[4] = anvil_tanh_s16x1(a[4]);
	a[5] = anvil_tanh_s16x1(a[5]);
	a[6] = anvil_tanh_s16x1(a[6]);
	a[7] = anvil_tanh_s16x1(a[7]);
	a[8] = anvil_tanh_s16x1(a[8]);
	a[9] = anvil_tanh_s16x1(a[9]);
	a[10] = anvil_tanh_s16x1(a[10]);
	a[11] = anvil_tanh_s16x1(a[11]);
	a[12] = anvil_tanh_s16x1(a[12]);
	a[13] = anvil_tanh_s16x1(a[13]);
	a[14] = anvil_tanh_s16x1(a[14]);
	a[15] = anvil_tanh_s16x1(a[15]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

#define anvil_tanh_u16x1(X) anvil_convert_f32x1_to_u16x1(anvil_tanh_f32x1(anvil_convert_u16x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE uint16x8_t ANVIL_SIMD_CALL anvil_tanh_u16x8(const register uint16x8_t x) {
	ANVIL_ALIGN(16) uint16x1_t a[8];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_tanh_u16x1(a[0]);
	a[1] = anvil_tanh_u16x1(a[1]);
	a[2] = anvil_tanh_u16x1(a[2]);
	a[3] = anvil_tanh_u16x1(a[3]);
	a[4] = anvil_tanh_u16x1(a[4]);
	a[5] = anvil_tanh_u16x1(a[5]);
	a[6] = anvil_tanh_u16x1(a[6]);
	a[7] = anvil_tanh_u16x1(a[7]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE uint16x16_t ANVIL_SIMD_CALL anvil_tanh_u16x16(const register uint16x16_t x) {
	ANVIL_ALIGN(16) uint16x1_t a[16];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_tanh_u16x1(a[0]);
	a[1] = anvil_tanh_u16x1(a[1]);
	a[2] = anvil_tanh_u16x1(a[2]);
	a[3] = anvil_tanh_u16x1(a[3]);
	a[4] = anvil_tanh_u16x1(a[4]);
	a[5] = anvil_tanh_u16x1(a[5]);
	a[6] = anvil_tanh_u16x1(a[6]);
	a[7] = anvil_tanh_u16x1(a[7]);
	a[8] = anvil_tanh_u16x1(a[8]);
	a[9] = anvil_tanh_u16x1(a[9]);
	a[10] = anvil_tanh_u16x1(a[10]);
	a[11] = anvil_tanh_u16x1(a[11]);
	a[12] = anvil_tanh_u16x1(a[12]);
	a[13] = anvil_tanh_u16x1(a[13]);
	a[14] = anvil_tanh_u16x1(a[14]);
	a[15] = anvil_tanh_u16x1(a[15]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

#define anvil_tanh_s8x1(X) anvil_convert_f32x1_to_s8x1(anvil_tanh_f32x1(anvil_convert_s8x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE int8x16_t ANVIL_SIMD_CALL anvil_tanh_s8x16(const register int8x16_t x) {
	ANVIL_ALIGN(16) int8x1_t a[16];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_tanh_s8x1(a[0]);
	a[1] = anvil_tanh_s8x1(a[1]);
	a[2] = anvil_tanh_s8x1(a[2]);
	a[3] = anvil_tanh_s8x1(a[3]);
	a[4] = anvil_tanh_s8x1(a[4]);
	a[5] = anvil_tanh_s8x1(a[5]);
	a[6] = anvil_tanh_s8x1(a[6]);
	a[7] = anvil_tanh_s8x1(a[7]);
	a[8] = anvil_tanh_s8x1(a[8]);
	a[9] = anvil_tanh_s8x1(a[9]);
	a[10] = anvil_tanh_s8x1(a[10]);
	a[11] = anvil_tanh_s8x1(a[11]);
	a[12] = anvil_tanh_s8x1(a[12]);
	a[13] = anvil_tanh_s8x1(a[13]);
	a[14] = anvil_tanh_s8x1(a[14]);
	a[15] = anvil_tanh_s8x1(a[15]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE int8x32_t ANVIL_SIMD_CALL anvil_tanh_s8x32(const register int8x32_t x) {
	ANVIL_ALIGN(16) int8x1_t a[32];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_tanh_s8x1(a[0]);
	a[1] = anvil_tanh_s8x1(a[1]);
	a[2] = anvil_tanh_s8x1(a[2]);
	a[3] = anvil_tanh_s8x1(a[3]);
	a[4] = anvil_tanh_s8x1(a[4]);
	a[5] = anvil_tanh_s8x1(a[5]);
	a[6] = anvil_tanh_s8x1(a[6]);
	a[7] = anvil_tanh_s8x1(a[7]);
	a[8] = anvil_tanh_s8x1(a[8]);
	a[9] = anvil_tanh_s8x1(a[9]);
	a[10] = anvil_tanh_s8x1(a[10]);
	a[11] = anvil_tanh_s8x1(a[11]);
	a[12] = anvil_tanh_s8x1(a[12]);
	a[13] = anvil_tanh_s8x1(a[13]);
	a[14] = anvil_tanh_s8x1(a[14]);
	a[15] = anvil_tanh_s8x1(a[15]);
	a[16] = anvil_tanh_s8x1(a[16]);
	a[17] = anvil_tanh_s8x1(a[17]);
	a[18] = anvil_tanh_s8x1(a[18]);
	a[19] = anvil_tanh_s8x1(a[19]);
	a[20] = anvil_tanh_s8x1(a[20]);
	a[21] = anvil_tanh_s8x1(a[21]);
	a[22] = anvil_tanh_s8x1(a[22]);
	a[23] = anvil_tanh_s8x1(a[23]);
	a[24] = anvil_tanh_s8x1(a[24]);
	a[25] = anvil_tanh_s8x1(a[25]);
	a[26] = anvil_tanh_s8x1(a[26]);
	a[27] = anvil_tanh_s8x1(a[27]);
	a[28] = anvil_tanh_s8x1(a[28]);
	a[29] = anvil_tanh_s8x1(a[29]);
	a[30] = anvil_tanh_s8x1(a[30]);
	a[31] = anvil_tanh_s8x1(a[31]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

#define anvil_tanh_u8x1(X) anvil_convert_f32x1_to_u8x1(anvil_tanh_f32x1(anvil_convert_u8x1_to_f32x1(X)))
static ANVIL_STRONG_INLINE uint8x16_t ANVIL_SIMD_CALL anvil_tanh_u8x16(const register uint8x16_t x) {
	ANVIL_ALIGN(16) uint8x1_t a[16];
	_mm_store_si128(reinterpret_cast<__m128i*>(a), x);
	a[0] = anvil_tanh_u8x1(a[0]);
	a[1] = anvil_tanh_u8x1(a[1]);
	a[2] = anvil_tanh_u8x1(a[2]);
	a[3] = anvil_tanh_u8x1(a[3]);
	a[4] = anvil_tanh_u8x1(a[4]);
	a[5] = anvil_tanh_u8x1(a[5]);
	a[6] = anvil_tanh_u8x1(a[6]);
	a[7] = anvil_tanh_u8x1(a[7]);
	a[8] = anvil_tanh_u8x1(a[8]);
	a[9] = anvil_tanh_u8x1(a[9]);
	a[10] = anvil_tanh_u8x1(a[10]);
	a[11] = anvil_tanh_u8x1(a[11]);
	a[12] = anvil_tanh_u8x1(a[12]);
	a[13] = anvil_tanh_u8x1(a[13]);
	a[14] = anvil_tanh_u8x1(a[14]);
	a[15] = anvil_tanh_u8x1(a[15]);
	return _mm_load_si128(reinterpret_cast<__m128i*>(a));
}

static ANVIL_STRONG_INLINE uint8x32_t ANVIL_SIMD_CALL anvil_tanh_u8x32(const register uint8x32_t x) {
	ANVIL_ALIGN(16) uint8x1_t a[32];
	_mm256_store_si256(reinterpret_cast<__m256i*>(a), x);
	a[0] = anvil_tanh_u8x1(a[0]);
	a[1] = anvil_tanh_u8x1(a[1]);
	a[2] = anvil_tanh_u8x1(a[2]);
	a[3] = anvil_tanh_u8x1(a[3]);
	a[4] = anvil_tanh_u8x1(a[4]);
	a[5] = anvil_tanh_u8x1(a[5]);
	a[6] = anvil_tanh_u8x1(a[6]);
	a[7] = anvil_tanh_u8x1(a[7]);
	a[8] = anvil_tanh_u8x1(a[8]);
	a[9] = anvil_tanh_u8x1(a[9]);
	a[10] = anvil_tanh_u8x1(a[10]);
	a[11] = anvil_tanh_u8x1(a[11]);
	a[12] = anvil_tanh_u8x1(a[12]);
	a[13] = anvil_tanh_u8x1(a[13]);
	a[14] = anvil_tanh_u8x1(a[14]);
	a[15] = anvil_tanh_u8x1(a[15]);
	a[16] = anvil_tanh_u8x1(a[16]);
	a[17] = anvil_tanh_u8x1(a[17]);
	a[18] = anvil_tanh_u8x1(a[18]);
	a[19] = anvil_tanh_u8x1(a[19]);
	a[20] = anvil_tanh_u8x1(a[20]);
	a[21] = anvil_tanh_u8x1(a[21]);
	a[22] = anvil_tanh_u8x1(a[22]);
	a[23] = anvil_tanh_u8x1(a[23]);
	a[24] = anvil_tanh_u8x1(a[24]);
	a[25] = anvil_tanh_u8x1(a[25]);
	a[26] = anvil_tanh_u8x1(a[26]);
	a[27] = anvil_tanh_u8x1(a[27]);
	a[28] = anvil_tanh_u8x1(a[28]);
	a[29] = anvil_tanh_u8x1(a[29]);
	a[30] = anvil_tanh_u8x1(a[30]);
	a[31] = anvil_tanh_u8x1(a[31]);
	return _mm256_load_si256(reinterpret_cast<__m256i*>(a));
}

// Sum

static ANVIL_STRONG_INLINE int32x1_t ANVIL_SIMD_CALL anvil_sum_s32x4(const register int32x4_t x) {
	const register __m128i tmp = _mm_add_epi32(_mm_unpackhi_epi32(x, x), _mm_unpacklo_epi32(x, x));
	int32x1_t buffer[2];
	_mm_storel_epi64(reinterpret_cast<__m128i*>(buffer), tmp);
	return buffer[0] + buffer[1];
}

#define anvil_sum_s8x16(X) anvil_sum_s32x4(_mm_madd_epi16(X, _mm_set1_epi16(1)))

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