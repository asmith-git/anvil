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

static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_combine(const register _simd_f64x1 x, const register _simd_f64x1 y) {
#ifdef _simd_f64x2_combine_
	return _simd_f64x2_combine_(x,y);
	#define _simd_f64x2_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_combine_instruction_set>()
#else
	return _simd_f64x2_combine_safe(x,y);
	#define _simd_f64x2_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_combine(const register _simd_f64x2 x, const register _simd_f64x2 y) {
#ifdef _simd_f64x4_combine_
	return _simd_f64x4_combine_(x,y);
	#define _simd_f64x4_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_combine_instruction_set>()
#else
	return _simd_f64x4_combine_safe(x,y);
	#define _simd_f64x4_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f64x8 ANVIL_SIMD_CALL _simd_f64x8_combine(const register _simd_f64x4 x, const register _simd_f64x4 y) {
#ifdef _simd_f64x8_combine_
	return _simd_f64x8_combine_(x,y);
	#define _simd_f64x8_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_combine_instruction_set>()
#else
	return _simd_f64x8_combine_safe(x,y);
	#define _simd_f64x8_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f64x16 ANVIL_SIMD_CALL _simd_f64x16_combine(const register _simd_f64x8 x, const register _simd_f64x8 y) {
#ifdef _simd_f64x16_combine_
	return _simd_f64x16_combine_(x,y);
	#define _simd_f64x16_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_combine_instruction_set>()
#else
	return _simd_f64x16_combine_safe(x,y);
	#define _simd_f64x16_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f64x32 ANVIL_SIMD_CALL _simd_f64x32_combine(const register _simd_f64x16 x, const register _simd_f64x16 y) {
#ifdef _simd_f64x32_combine_
	return _simd_f64x32_combine_(x,y);
	#define _simd_f64x32_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_combine_instruction_set>()
#else
	return _simd_f64x32_combine_safe(x,y);
	#define _simd_f64x32_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f64x64 ANVIL_SIMD_CALL _simd_f64x64_combine(const register _simd_f64x32 x, const register _simd_f64x32 y) {
#ifdef _simd_f64x64_combine_
	return _simd_f64x64_combine_(x,y);
	#define _simd_f64x64_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_combine_instruction_set>()
#else
	return _simd_f64x64_combine_safe(x,y);
	#define _simd_f64x64_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_combine(const register _simd_f32x1 x, const register _simd_f32x1 y) {
#ifdef _simd_f32x2_combine_
	return _simd_f32x2_combine_(x,y);
	#define _simd_f32x2_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_combine_instruction_set>()
#else
	return _simd_f32x2_combine_safe(x,y);
	#define _simd_f32x2_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_combine(const register _simd_f32x2 x, const register _simd_f32x2 y) {
#ifdef _simd_f32x4_combine_
	return _simd_f32x4_combine_(x,y);
	#define _simd_f32x4_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_combine_instruction_set>()
#else
	return _simd_f32x4_combine_safe(x,y);
	#define _simd_f32x4_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f32x8 ANVIL_SIMD_CALL _simd_f32x8_combine(const register _simd_f32x4 x, const register _simd_f32x4 y) {
#ifdef _simd_f32x8_combine_
	return _simd_f32x8_combine_(x,y);
	#define _simd_f32x8_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_combine_instruction_set>()
#else
	return _simd_f32x8_combine_safe(x,y);
	#define _simd_f32x8_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f32x16 ANVIL_SIMD_CALL _simd_f32x16_combine(const register _simd_f32x8 x, const register _simd_f32x8 y) {
#ifdef _simd_f32x16_combine_
	return _simd_f32x16_combine_(x,y);
	#define _simd_f32x16_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_combine_instruction_set>()
#else
	return _simd_f32x16_combine_safe(x,y);
	#define _simd_f32x16_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f32x32 ANVIL_SIMD_CALL _simd_f32x32_combine(const register _simd_f32x16 x, const register _simd_f32x16 y) {
#ifdef _simd_f32x32_combine_
	return _simd_f32x32_combine_(x,y);
	#define _simd_f32x32_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_combine_instruction_set>()
#else
	return _simd_f32x32_combine_safe(x,y);
	#define _simd_f32x32_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f32x64 ANVIL_SIMD_CALL _simd_f32x64_combine(const register _simd_f32x32 x, const register _simd_f32x32 y) {
#ifdef _simd_f32x64_combine_
	return _simd_f32x64_combine_(x,y);
	#define _simd_f32x64_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_combine_instruction_set>()
#else
	return _simd_f32x64_combine_safe(x,y);
	#define _simd_f32x64_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_combine(const register _simd_s64x1 x, const register _simd_s64x1 y) {
#ifdef _simd_s64x2_combine_
	return _simd_s64x2_combine_(x,y);
	#define _simd_s64x2_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_combine_instruction_set>()
#else
	return _simd_s64x2_combine_safe(x,y);
	#define _simd_s64x2_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_combine(const register _simd_s64x2 x, const register _simd_s64x2 y) {
#ifdef _simd_s64x4_combine_
	return _simd_s64x4_combine_(x,y);
	#define _simd_s64x4_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_combine_instruction_set>()
#else
	return _simd_s64x4_combine_safe(x,y);
	#define _simd_s64x4_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s64x8 ANVIL_SIMD_CALL _simd_s64x8_combine(const register _simd_s64x4 x, const register _simd_s64x4 y) {
#ifdef _simd_s64x8_combine_
	return _simd_s64x8_combine_(x,y);
	#define _simd_s64x8_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_combine_instruction_set>()
#else
	return _simd_s64x8_combine_safe(x,y);
	#define _simd_s64x8_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s64x16 ANVIL_SIMD_CALL _simd_s64x16_combine(const register _simd_s64x8 x, const register _simd_s64x8 y) {
#ifdef _simd_s64x16_combine_
	return _simd_s64x16_combine_(x,y);
	#define _simd_s64x16_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_combine_instruction_set>()
#else
	return _simd_s64x16_combine_safe(x,y);
	#define _simd_s64x16_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s64x32 ANVIL_SIMD_CALL _simd_s64x32_combine(const register _simd_s64x16 x, const register _simd_s64x16 y) {
#ifdef _simd_s64x32_combine_
	return _simd_s64x32_combine_(x,y);
	#define _simd_s64x32_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_combine_instruction_set>()
#else
	return _simd_s64x32_combine_safe(x,y);
	#define _simd_s64x32_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s64x64 ANVIL_SIMD_CALL _simd_s64x64_combine(const register _simd_s64x32 x, const register _simd_s64x32 y) {
#ifdef _simd_s64x64_combine_
	return _simd_s64x64_combine_(x,y);
	#define _simd_s64x64_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_combine_instruction_set>()
#else
	return _simd_s64x64_combine_safe(x,y);
	#define _simd_s64x64_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_combine(const register _simd_u64x1 x, const register _simd_u64x1 y) {
#ifdef _simd_u64x2_combine_
	return _simd_u64x2_combine_(x,y);
	#define _simd_u64x2_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_combine_instruction_set>()
#else
	return _simd_u64x2_combine_safe(x,y);
	#define _simd_u64x2_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_combine(const register _simd_u64x2 x, const register _simd_u64x2 y) {
#ifdef _simd_u64x4_combine_
	return _simd_u64x4_combine_(x,y);
	#define _simd_u64x4_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_combine_instruction_set>()
#else
	return _simd_u64x4_combine_safe(x,y);
	#define _simd_u64x4_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u64x8 ANVIL_SIMD_CALL _simd_u64x8_combine(const register _simd_u64x4 x, const register _simd_u64x4 y) {
#ifdef _simd_u64x8_combine_
	return _simd_u64x8_combine_(x,y);
	#define _simd_u64x8_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_combine_instruction_set>()
#else
	return _simd_u64x8_combine_safe(x,y);
	#define _simd_u64x8_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u64x16 ANVIL_SIMD_CALL _simd_u64x16_combine(const register _simd_u64x8 x, const register _simd_u64x8 y) {
#ifdef _simd_u64x16_combine_
	return _simd_u64x16_combine_(x,y);
	#define _simd_u64x16_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_combine_instruction_set>()
#else
	return _simd_u64x16_combine_safe(x,y);
	#define _simd_u64x16_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u64x32 ANVIL_SIMD_CALL _simd_u64x32_combine(const register _simd_u64x16 x, const register _simd_u64x16 y) {
#ifdef _simd_u64x32_combine_
	return _simd_u64x32_combine_(x,y);
	#define _simd_u64x32_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_combine_instruction_set>()
#else
	return _simd_u64x32_combine_safe(x,y);
	#define _simd_u64x32_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u64x64 ANVIL_SIMD_CALL _simd_u64x64_combine(const register _simd_u64x32 x, const register _simd_u64x32 y) {
#ifdef _simd_u64x64_combine_
	return _simd_u64x64_combine_(x,y);
	#define _simd_u64x64_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_combine_instruction_set>()
#else
	return _simd_u64x64_combine_safe(x,y);
	#define _simd_u64x64_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_combine(const register _simd_s32x1 x, const register _simd_s32x1 y) {
#ifdef _simd_s32x2_combine_
	return _simd_s32x2_combine_(x,y);
	#define _simd_s32x2_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_combine_instruction_set>()
#else
	return _simd_s32x2_combine_safe(x,y);
	#define _simd_s32x2_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_combine(const register _simd_s32x2 x, const register _simd_s32x2 y) {
#ifdef _simd_s32x4_combine_
	return _simd_s32x4_combine_(x,y);
	#define _simd_s32x4_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_combine_instruction_set>()
#else
	return _simd_s32x4_combine_safe(x,y);
	#define _simd_s32x4_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s32x8 ANVIL_SIMD_CALL _simd_s32x8_combine(const register _simd_s32x4 x, const register _simd_s32x4 y) {
#ifdef _simd_s32x8_combine_
	return _simd_s32x8_combine_(x,y);
	#define _simd_s32x8_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_combine_instruction_set>()
#else
	return _simd_s32x8_combine_safe(x,y);
	#define _simd_s32x8_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s32x16 ANVIL_SIMD_CALL _simd_s32x16_combine(const register _simd_s32x8 x, const register _simd_s32x8 y) {
#ifdef _simd_s32x16_combine_
	return _simd_s32x16_combine_(x,y);
	#define _simd_s32x16_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_combine_instruction_set>()
#else
	return _simd_s32x16_combine_safe(x,y);
	#define _simd_s32x16_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s32x32 ANVIL_SIMD_CALL _simd_s32x32_combine(const register _simd_s32x16 x, const register _simd_s32x16 y) {
#ifdef _simd_s32x32_combine_
	return _simd_s32x32_combine_(x,y);
	#define _simd_s32x32_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_combine_instruction_set>()
#else
	return _simd_s32x32_combine_safe(x,y);
	#define _simd_s32x32_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s32x64 ANVIL_SIMD_CALL _simd_s32x64_combine(const register _simd_s32x32 x, const register _simd_s32x32 y) {
#ifdef _simd_s32x64_combine_
	return _simd_s32x64_combine_(x,y);
	#define _simd_s32x64_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_combine_instruction_set>()
#else
	return _simd_s32x64_combine_safe(x,y);
	#define _simd_s32x64_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_combine(const register _simd_u32x1 x, const register _simd_u32x1 y) {
#ifdef _simd_u32x2_combine_
	return _simd_u32x2_combine_(x,y);
	#define _simd_u32x2_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_combine_instruction_set>()
#else
	return _simd_u32x2_combine_safe(x,y);
	#define _simd_u32x2_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_combine(const register _simd_u32x2 x, const register _simd_u32x2 y) {
#ifdef _simd_u32x4_combine_
	return _simd_u32x4_combine_(x,y);
	#define _simd_u32x4_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_combine_instruction_set>()
#else
	return _simd_u32x4_combine_safe(x,y);
	#define _simd_u32x4_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u32x8 ANVIL_SIMD_CALL _simd_u32x8_combine(const register _simd_u32x4 x, const register _simd_u32x4 y) {
#ifdef _simd_u32x8_combine_
	return _simd_u32x8_combine_(x,y);
	#define _simd_u32x8_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_combine_instruction_set>()
#else
	return _simd_u32x8_combine_safe(x,y);
	#define _simd_u32x8_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u32x16 ANVIL_SIMD_CALL _simd_u32x16_combine(const register _simd_u32x8 x, const register _simd_u32x8 y) {
#ifdef _simd_u32x16_combine_
	return _simd_u32x16_combine_(x,y);
	#define _simd_u32x16_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_combine_instruction_set>()
#else
	return _simd_u32x16_combine_safe(x,y);
	#define _simd_u32x16_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u32x32 ANVIL_SIMD_CALL _simd_u32x32_combine(const register _simd_u32x16 x, const register _simd_u32x16 y) {
#ifdef _simd_u32x32_combine_
	return _simd_u32x32_combine_(x,y);
	#define _simd_u32x32_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_combine_instruction_set>()
#else
	return _simd_u32x32_combine_safe(x,y);
	#define _simd_u32x32_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u32x64 ANVIL_SIMD_CALL _simd_u32x64_combine(const register _simd_u32x32 x, const register _simd_u32x32 y) {
#ifdef _simd_u32x64_combine_
	return _simd_u32x64_combine_(x,y);
	#define _simd_u32x64_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_combine_instruction_set>()
#else
	return _simd_u32x64_combine_safe(x,y);
	#define _simd_u32x64_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_combine(const register _simd_s16x1 x, const register _simd_s16x1 y) {
#ifdef _simd_s16x2_combine_
	return _simd_s16x2_combine_(x,y);
	#define _simd_s16x2_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_combine_instruction_set>()
#else
	return _simd_s16x2_combine_safe(x,y);
	#define _simd_s16x2_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_combine(const register _simd_s16x2 x, const register _simd_s16x2 y) {
#ifdef _simd_s16x4_combine_
	return _simd_s16x4_combine_(x,y);
	#define _simd_s16x4_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_combine_instruction_set>()
#else
	return _simd_s16x4_combine_safe(x,y);
	#define _simd_s16x4_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s16x8 ANVIL_SIMD_CALL _simd_s16x8_combine(const register _simd_s16x4 x, const register _simd_s16x4 y) {
#ifdef _simd_s16x8_combine_
	return _simd_s16x8_combine_(x,y);
	#define _simd_s16x8_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_combine_instruction_set>()
#else
	return _simd_s16x8_combine_safe(x,y);
	#define _simd_s16x8_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s16x16 ANVIL_SIMD_CALL _simd_s16x16_combine(const register _simd_s16x8 x, const register _simd_s16x8 y) {
#ifdef _simd_s16x16_combine_
	return _simd_s16x16_combine_(x,y);
	#define _simd_s16x16_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_combine_instruction_set>()
#else
	return _simd_s16x16_combine_safe(x,y);
	#define _simd_s16x16_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s16x32 ANVIL_SIMD_CALL _simd_s16x32_combine(const register _simd_s16x16 x, const register _simd_s16x16 y) {
#ifdef _simd_s16x32_combine_
	return _simd_s16x32_combine_(x,y);
	#define _simd_s16x32_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_combine_instruction_set>()
#else
	return _simd_s16x32_combine_safe(x,y);
	#define _simd_s16x32_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s16x64 ANVIL_SIMD_CALL _simd_s16x64_combine(const register _simd_s16x32 x, const register _simd_s16x32 y) {
#ifdef _simd_s16x64_combine_
	return _simd_s16x64_combine_(x,y);
	#define _simd_s16x64_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_combine_instruction_set>()
#else
	return _simd_s16x64_combine_safe(x,y);
	#define _simd_s16x64_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_combine(const register _simd_u16x1 x, const register _simd_u16x1 y) {
#ifdef _simd_u16x2_combine_
	return _simd_u16x2_combine_(x,y);
	#define _simd_u16x2_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_combine_instruction_set>()
#else
	return _simd_u16x2_combine_safe(x,y);
	#define _simd_u16x2_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_combine(const register _simd_u16x2 x, const register _simd_u16x2 y) {
#ifdef _simd_u16x4_combine_
	return _simd_u16x4_combine_(x,y);
	#define _simd_u16x4_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_combine_instruction_set>()
#else
	return _simd_u16x4_combine_safe(x,y);
	#define _simd_u16x4_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u16x8 ANVIL_SIMD_CALL _simd_u16x8_combine(const register _simd_u16x4 x, const register _simd_u16x4 y) {
#ifdef _simd_u16x8_combine_
	return _simd_u16x8_combine_(x,y);
	#define _simd_u16x8_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_combine_instruction_set>()
#else
	return _simd_u16x8_combine_safe(x,y);
	#define _simd_u16x8_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u16x16 ANVIL_SIMD_CALL _simd_u16x16_combine(const register _simd_u16x8 x, const register _simd_u16x8 y) {
#ifdef _simd_u16x16_combine_
	return _simd_u16x16_combine_(x,y);
	#define _simd_u16x16_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_combine_instruction_set>()
#else
	return _simd_u16x16_combine_safe(x,y);
	#define _simd_u16x16_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u16x32 ANVIL_SIMD_CALL _simd_u16x32_combine(const register _simd_u16x16 x, const register _simd_u16x16 y) {
#ifdef _simd_u16x32_combine_
	return _simd_u16x32_combine_(x,y);
	#define _simd_u16x32_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_combine_instruction_set>()
#else
	return _simd_u16x32_combine_safe(x,y);
	#define _simd_u16x32_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u16x64 ANVIL_SIMD_CALL _simd_u16x64_combine(const register _simd_u16x32 x, const register _simd_u16x32 y) {
#ifdef _simd_u16x64_combine_
	return _simd_u16x64_combine_(x,y);
	#define _simd_u16x64_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_combine_instruction_set>()
#else
	return _simd_u16x64_combine_safe(x,y);
	#define _simd_u16x64_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_combine(const register _simd_s8x1 x, const register _simd_s8x1 y) {
#ifdef _simd_s8x2_combine_
	return _simd_s8x2_combine_(x,y);
	#define _simd_s8x2_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_combine_instruction_set>()
#else
	return _simd_s8x2_combine_safe(x,y);
	#define _simd_s8x2_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_combine(const register _simd_s8x2 x, const register _simd_s8x2 y) {
#ifdef _simd_s8x4_combine_
	return _simd_s8x4_combine_(x,y);
	#define _simd_s8x4_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_combine_instruction_set>()
#else
	return _simd_s8x4_combine_safe(x,y);
	#define _simd_s8x4_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s8x8 ANVIL_SIMD_CALL _simd_s8x8_combine(const register _simd_s8x4 x, const register _simd_s8x4 y) {
#ifdef _simd_s8x8_combine_
	return _simd_s8x8_combine_(x,y);
	#define _simd_s8x8_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_combine_instruction_set>()
#else
	return _simd_s8x8_combine_safe(x,y);
	#define _simd_s8x8_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s8x16 ANVIL_SIMD_CALL _simd_s8x16_combine(const register _simd_s8x8 x, const register _simd_s8x8 y) {
#ifdef _simd_s8x16_combine_
	return _simd_s8x16_combine_(x,y);
	#define _simd_s8x16_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_combine_instruction_set>()
#else
	return _simd_s8x16_combine_safe(x,y);
	#define _simd_s8x16_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s8x32 ANVIL_SIMD_CALL _simd_s8x32_combine(const register _simd_s8x16 x, const register _simd_s8x16 y) {
#ifdef _simd_s8x32_combine_
	return _simd_s8x32_combine_(x,y);
	#define _simd_s8x32_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_combine_instruction_set>()
#else
	return _simd_s8x32_combine_safe(x,y);
	#define _simd_s8x32_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s8x64 ANVIL_SIMD_CALL _simd_s8x64_combine(const register _simd_s8x32 x, const register _simd_s8x32 y) {
#ifdef _simd_s8x64_combine_
	return _simd_s8x64_combine_(x,y);
	#define _simd_s8x64_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_combine_instruction_set>()
#else
	return _simd_s8x64_combine_safe(x,y);
	#define _simd_s8x64_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_combine(const register _simd_u8x1 x, const register _simd_u8x1 y) {
#ifdef _simd_u8x2_combine_
	return _simd_u8x2_combine_(x,y);
	#define _simd_u8x2_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_combine_instruction_set>()
#else
	return _simd_u8x2_combine_safe(x,y);
	#define _simd_u8x2_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_combine(const register _simd_u8x2 x, const register _simd_u8x2 y) {
#ifdef _simd_u8x4_combine_
	return _simd_u8x4_combine_(x,y);
	#define _simd_u8x4_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_combine_instruction_set>()
#else
	return _simd_u8x4_combine_safe(x,y);
	#define _simd_u8x4_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u8x8 ANVIL_SIMD_CALL _simd_u8x8_combine(const register _simd_u8x4 x, const register _simd_u8x4 y) {
#ifdef _simd_u8x8_combine_
	return _simd_u8x8_combine_(x,y);
	#define _simd_u8x8_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_combine_instruction_set>()
#else
	return _simd_u8x8_combine_safe(x,y);
	#define _simd_u8x8_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u8x16 ANVIL_SIMD_CALL _simd_u8x16_combine(const register _simd_u8x8 x, const register _simd_u8x8 y) {
#ifdef _simd_u8x16_combine_
	return _simd_u8x16_combine_(x,y);
	#define _simd_u8x16_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_combine_instruction_set>()
#else
	return _simd_u8x16_combine_safe(x,y);
	#define _simd_u8x16_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u8x32 ANVIL_SIMD_CALL _simd_u8x32_combine(const register _simd_u8x16 x, const register _simd_u8x16 y) {
#ifdef _simd_u8x32_combine_
	return _simd_u8x32_combine_(x,y);
	#define _simd_u8x32_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_combine_instruction_set>()
#else
	return _simd_u8x32_combine_safe(x,y);
	#define _simd_u8x32_combine_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u8x64 ANVIL_SIMD_CALL _simd_u8x64_combine(const register _simd_u8x32 x, const register _simd_u8x32 y) {
#ifdef _simd_u8x64_combine_
	return _simd_u8x64_combine_(x,y);
	#define _simd_u8x64_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_combine_instruction_set>()
#else
	return _simd_u8x64_combine_safe(x,y);
	#define _simd_u8x64_combine_enable() true
#endif
}
