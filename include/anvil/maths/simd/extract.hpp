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

static ANVIL_STRONG_INLINE _simd_f64x1 ANVIL_SIMD_CALL _simd_f64x2_extract(const register _simd_f64x2 x, const register int i) {
#ifdef _simd_f64x2_extract_
	return _simd_f64x2_extract_(x,i);
	#define _simd_f64x2_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_extract_instruction_set>()
#else
	return _simd_f64x2_extract_safe(x,i);
	#define _simd_f64x2_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f64x1 ANVIL_SIMD_CALL _simd_f64x4_extract(const register _simd_f64x4 x, const register int i) {
#ifdef _simd_f64x4_extract_
	return _simd_f64x4_extract_(x,i);
	#define _simd_f64x4_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_extract_instruction_set>()
#else
	return _simd_f64x4_extract_safe(x,i);
	#define _simd_f64x4_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f64x1 ANVIL_SIMD_CALL _simd_f64x8_extract(const register _simd_f64x8 x, const register int i) {
#ifdef _simd_f64x8_extract_
	return _simd_f64x8_extract_(x,i);
	#define _simd_f64x8_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_extract_instruction_set>()
#else
	return _simd_f64x8_extract_safe(x,i);
	#define _simd_f64x8_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f64x1 ANVIL_SIMD_CALL _simd_f64x16_extract(const register _simd_f64x16 x, const register int i) {
#ifdef _simd_f64x16_extract_
	return _simd_f64x16_extract_(x,i);
	#define _simd_f64x16_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_extract_instruction_set>()
#else
	return _simd_f64x16_extract_safe(x,i);
	#define _simd_f64x16_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f64x1 ANVIL_SIMD_CALL _simd_f64x32_extract(const register _simd_f64x32 x, const register int i) {
#ifdef _simd_f64x32_extract_
	return _simd_f64x32_extract_(x,i);
	#define _simd_f64x32_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_extract_instruction_set>()
#else
	return _simd_f64x32_extract_safe(x,i);
	#define _simd_f64x32_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f64x1 ANVIL_SIMD_CALL _simd_f64x64_extract(const register _simd_f64x64 x, const register int i) {
#ifdef _simd_f64x64_extract_
	return _simd_f64x64_extract_(x,i);
	#define _simd_f64x64_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_extract_instruction_set>()
#else
	return _simd_f64x64_extract_safe(x,i);
	#define _simd_f64x64_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f32x1 ANVIL_SIMD_CALL _simd_f32x2_extract(const register _simd_f32x2 x, const register int i) {
#ifdef _simd_f32x2_extract_
	return _simd_f32x2_extract_(x,i);
	#define _simd_f32x2_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_extract_instruction_set>()
#else
	return _simd_f32x2_extract_safe(x,i);
	#define _simd_f32x2_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f32x1 ANVIL_SIMD_CALL _simd_f32x4_extract(const register _simd_f32x4 x, const register int i) {
#ifdef _simd_f32x4_extract_
	return _simd_f32x4_extract_(x,i);
	#define _simd_f32x4_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_extract_instruction_set>()
#else
	return _simd_f32x4_extract_safe(x,i);
	#define _simd_f32x4_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f32x1 ANVIL_SIMD_CALL _simd_f32x8_extract(const register _simd_f32x8 x, const register int i) {
#ifdef _simd_f32x8_extract_
	return _simd_f32x8_extract_(x,i);
	#define _simd_f32x8_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_extract_instruction_set>()
#else
	return _simd_f32x8_extract_safe(x,i);
	#define _simd_f32x8_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f32x1 ANVIL_SIMD_CALL _simd_f32x16_extract(const register _simd_f32x16 x, const register int i) {
#ifdef _simd_f32x16_extract_
	return _simd_f32x16_extract_(x,i);
	#define _simd_f32x16_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_extract_instruction_set>()
#else
	return _simd_f32x16_extract_safe(x,i);
	#define _simd_f32x16_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f32x1 ANVIL_SIMD_CALL _simd_f32x32_extract(const register _simd_f32x32 x, const register int i) {
#ifdef _simd_f32x32_extract_
	return _simd_f32x32_extract_(x,i);
	#define _simd_f32x32_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_extract_instruction_set>()
#else
	return _simd_f32x32_extract_safe(x,i);
	#define _simd_f32x32_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f32x1 ANVIL_SIMD_CALL _simd_f32x64_extract(const register _simd_f32x64 x, const register int i) {
#ifdef _simd_f32x64_extract_
	return _simd_f32x64_extract_(x,i);
	#define _simd_f32x64_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_extract_instruction_set>()
#else
	return _simd_f32x64_extract_safe(x,i);
	#define _simd_f32x64_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s64x1 ANVIL_SIMD_CALL _simd_s64x2_extract(const register _simd_s64x2 x, const register int i) {
#ifdef _simd_s64x2_extract_
	return _simd_s64x2_extract_(x,i);
	#define _simd_s64x2_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_extract_instruction_set>()
#else
	return _simd_s64x2_extract_safe(x,i);
	#define _simd_s64x2_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s64x1 ANVIL_SIMD_CALL _simd_s64x4_extract(const register _simd_s64x4 x, const register int i) {
#ifdef _simd_s64x4_extract_
	return _simd_s64x4_extract_(x,i);
	#define _simd_s64x4_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_extract_instruction_set>()
#else
	return _simd_s64x4_extract_safe(x,i);
	#define _simd_s64x4_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s64x1 ANVIL_SIMD_CALL _simd_s64x8_extract(const register _simd_s64x8 x, const register int i) {
#ifdef _simd_s64x8_extract_
	return _simd_s64x8_extract_(x,i);
	#define _simd_s64x8_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_extract_instruction_set>()
#else
	return _simd_s64x8_extract_safe(x,i);
	#define _simd_s64x8_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s64x1 ANVIL_SIMD_CALL _simd_s64x16_extract(const register _simd_s64x16 x, const register int i) {
#ifdef _simd_s64x16_extract_
	return _simd_s64x16_extract_(x,i);
	#define _simd_s64x16_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_extract_instruction_set>()
#else
	return _simd_s64x16_extract_safe(x,i);
	#define _simd_s64x16_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s64x1 ANVIL_SIMD_CALL _simd_s64x32_extract(const register _simd_s64x32 x, const register int i) {
#ifdef _simd_s64x32_extract_
	return _simd_s64x32_extract_(x,i);
	#define _simd_s64x32_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_extract_instruction_set>()
#else
	return _simd_s64x32_extract_safe(x,i);
	#define _simd_s64x32_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s64x1 ANVIL_SIMD_CALL _simd_s64x64_extract(const register _simd_s64x64 x, const register int i) {
#ifdef _simd_s64x64_extract_
	return _simd_s64x64_extract_(x,i);
	#define _simd_s64x64_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_extract_instruction_set>()
#else
	return _simd_s64x64_extract_safe(x,i);
	#define _simd_s64x64_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u64x1 ANVIL_SIMD_CALL _simd_u64x2_extract(const register _simd_u64x2 x, const register int i) {
#ifdef _simd_u64x2_extract_
	return _simd_u64x2_extract_(x,i);
	#define _simd_u64x2_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_extract_instruction_set>()
#else
	return _simd_u64x2_extract_safe(x,i);
	#define _simd_u64x2_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u64x1 ANVIL_SIMD_CALL _simd_u64x4_extract(const register _simd_u64x4 x, const register int i) {
#ifdef _simd_u64x4_extract_
	return _simd_u64x4_extract_(x,i);
	#define _simd_u64x4_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_extract_instruction_set>()
#else
	return _simd_u64x4_extract_safe(x,i);
	#define _simd_u64x4_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u64x1 ANVIL_SIMD_CALL _simd_u64x8_extract(const register _simd_u64x8 x, const register int i) {
#ifdef _simd_u64x8_extract_
	return _simd_u64x8_extract_(x,i);
	#define _simd_u64x8_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_extract_instruction_set>()
#else
	return _simd_u64x8_extract_safe(x,i);
	#define _simd_u64x8_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u64x1 ANVIL_SIMD_CALL _simd_u64x16_extract(const register _simd_u64x16 x, const register int i) {
#ifdef _simd_u64x16_extract_
	return _simd_u64x16_extract_(x,i);
	#define _simd_u64x16_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_extract_instruction_set>()
#else
	return _simd_u64x16_extract_safe(x,i);
	#define _simd_u64x16_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u64x1 ANVIL_SIMD_CALL _simd_u64x32_extract(const register _simd_u64x32 x, const register int i) {
#ifdef _simd_u64x32_extract_
	return _simd_u64x32_extract_(x,i);
	#define _simd_u64x32_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_extract_instruction_set>()
#else
	return _simd_u64x32_extract_safe(x,i);
	#define _simd_u64x32_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u64x1 ANVIL_SIMD_CALL _simd_u64x64_extract(const register _simd_u64x64 x, const register int i) {
#ifdef _simd_u64x64_extract_
	return _simd_u64x64_extract_(x,i);
	#define _simd_u64x64_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_extract_instruction_set>()
#else
	return _simd_u64x64_extract_safe(x,i);
	#define _simd_u64x64_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s32x1 ANVIL_SIMD_CALL _simd_s32x2_extract(const register _simd_s32x2 x, const register int i) {
#ifdef _simd_s32x2_extract_
	return _simd_s32x2_extract_(x,i);
	#define _simd_s32x2_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_extract_instruction_set>()
#else
	return _simd_s32x2_extract_safe(x,i);
	#define _simd_s32x2_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s32x1 ANVIL_SIMD_CALL _simd_s32x4_extract(const register _simd_s32x4 x, const register int i) {
#ifdef _simd_s32x4_extract_
	return _simd_s32x4_extract_(x,i);
	#define _simd_s32x4_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_extract_instruction_set>()
#else
	return _simd_s32x4_extract_safe(x,i);
	#define _simd_s32x4_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s32x1 ANVIL_SIMD_CALL _simd_s32x8_extract(const register _simd_s32x8 x, const register int i) {
#ifdef _simd_s32x8_extract_
	return _simd_s32x8_extract_(x,i);
	#define _simd_s32x8_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_extract_instruction_set>()
#else
	return _simd_s32x8_extract_safe(x,i);
	#define _simd_s32x8_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s32x1 ANVIL_SIMD_CALL _simd_s32x16_extract(const register _simd_s32x16 x, const register int i) {
#ifdef _simd_s32x16_extract_
	return _simd_s32x16_extract_(x,i);
	#define _simd_s32x16_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_extract_instruction_set>()
#else
	return _simd_s32x16_extract_safe(x,i);
	#define _simd_s32x16_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s32x1 ANVIL_SIMD_CALL _simd_s32x32_extract(const register _simd_s32x32 x, const register int i) {
#ifdef _simd_s32x32_extract_
	return _simd_s32x32_extract_(x,i);
	#define _simd_s32x32_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_extract_instruction_set>()
#else
	return _simd_s32x32_extract_safe(x,i);
	#define _simd_s32x32_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s32x1 ANVIL_SIMD_CALL _simd_s32x64_extract(const register _simd_s32x64 x, const register int i) {
#ifdef _simd_s32x64_extract_
	return _simd_s32x64_extract_(x,i);
	#define _simd_s32x64_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_extract_instruction_set>()
#else
	return _simd_s32x64_extract_safe(x,i);
	#define _simd_s32x64_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u32x1 ANVIL_SIMD_CALL _simd_u32x2_extract(const register _simd_u32x2 x, const register int i) {
#ifdef _simd_u32x2_extract_
	return _simd_u32x2_extract_(x,i);
	#define _simd_u32x2_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_extract_instruction_set>()
#else
	return _simd_u32x2_extract_safe(x,i);
	#define _simd_u32x2_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u32x1 ANVIL_SIMD_CALL _simd_u32x4_extract(const register _simd_u32x4 x, const register int i) {
#ifdef _simd_u32x4_extract_
	return _simd_u32x4_extract_(x,i);
	#define _simd_u32x4_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_extract_instruction_set>()
#else
	return _simd_u32x4_extract_safe(x,i);
	#define _simd_u32x4_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u32x1 ANVIL_SIMD_CALL _simd_u32x8_extract(const register _simd_u32x8 x, const register int i) {
#ifdef _simd_u32x8_extract_
	return _simd_u32x8_extract_(x,i);
	#define _simd_u32x8_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_extract_instruction_set>()
#else
	return _simd_u32x8_extract_safe(x,i);
	#define _simd_u32x8_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u32x1 ANVIL_SIMD_CALL _simd_u32x16_extract(const register _simd_u32x16 x, const register int i) {
#ifdef _simd_u32x16_extract_
	return _simd_u32x16_extract_(x,i);
	#define _simd_u32x16_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_extract_instruction_set>()
#else
	return _simd_u32x16_extract_safe(x,i);
	#define _simd_u32x16_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u32x1 ANVIL_SIMD_CALL _simd_u32x32_extract(const register _simd_u32x32 x, const register int i) {
#ifdef _simd_u32x32_extract_
	return _simd_u32x32_extract_(x,i);
	#define _simd_u32x32_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_extract_instruction_set>()
#else
	return _simd_u32x32_extract_safe(x,i);
	#define _simd_u32x32_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u32x1 ANVIL_SIMD_CALL _simd_u32x64_extract(const register _simd_u32x64 x, const register int i) {
#ifdef _simd_u32x64_extract_
	return _simd_u32x64_extract_(x,i);
	#define _simd_u32x64_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_extract_instruction_set>()
#else
	return _simd_u32x64_extract_safe(x,i);
	#define _simd_u32x64_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s16x1 ANVIL_SIMD_CALL _simd_s16x2_extract(const register _simd_s16x2 x, const register int i) {
#ifdef _simd_s16x2_extract_
	return _simd_s16x2_extract_(x,i);
	#define _simd_s16x2_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_extract_instruction_set>()
#else
	return _simd_s16x2_extract_safe(x,i);
	#define _simd_s16x2_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s16x1 ANVIL_SIMD_CALL _simd_s16x4_extract(const register _simd_s16x4 x, const register int i) {
#ifdef _simd_s16x4_extract_
	return _simd_s16x4_extract_(x,i);
	#define _simd_s16x4_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_extract_instruction_set>()
#else
	return _simd_s16x4_extract_safe(x,i);
	#define _simd_s16x4_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s16x1 ANVIL_SIMD_CALL _simd_s16x8_extract(const register _simd_s16x8 x, const register int i) {
#ifdef _simd_s16x8_extract_
	return _simd_s16x8_extract_(x,i);
	#define _simd_s16x8_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_extract_instruction_set>()
#else
	return _simd_s16x8_extract_safe(x,i);
	#define _simd_s16x8_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s16x1 ANVIL_SIMD_CALL _simd_s16x16_extract(const register _simd_s16x16 x, const register int i) {
#ifdef _simd_s16x16_extract_
	return _simd_s16x16_extract_(x,i);
	#define _simd_s16x16_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_extract_instruction_set>()
#else
	return _simd_s16x16_extract_safe(x,i);
	#define _simd_s16x16_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s16x1 ANVIL_SIMD_CALL _simd_s16x32_extract(const register _simd_s16x32 x, const register int i) {
#ifdef _simd_s16x32_extract_
	return _simd_s16x32_extract_(x,i);
	#define _simd_s16x32_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_extract_instruction_set>()
#else
	return _simd_s16x32_extract_safe(x,i);
	#define _simd_s16x32_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s16x1 ANVIL_SIMD_CALL _simd_s16x64_extract(const register _simd_s16x64 x, const register int i) {
#ifdef _simd_s16x64_extract_
	return _simd_s16x64_extract_(x,i);
	#define _simd_s16x64_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_extract_instruction_set>()
#else
	return _simd_s16x64_extract_safe(x,i);
	#define _simd_s16x64_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u16x1 ANVIL_SIMD_CALL _simd_u16x2_extract(const register _simd_u16x2 x, const register int i) {
#ifdef _simd_u16x2_extract_
	return _simd_u16x2_extract_(x,i);
	#define _simd_u16x2_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_extract_instruction_set>()
#else
	return _simd_u16x2_extract_safe(x,i);
	#define _simd_u16x2_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u16x1 ANVIL_SIMD_CALL _simd_u16x4_extract(const register _simd_u16x4 x, const register int i) {
#ifdef _simd_u16x4_extract_
	return _simd_u16x4_extract_(x,i);
	#define _simd_u16x4_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_extract_instruction_set>()
#else
	return _simd_u16x4_extract_safe(x,i);
	#define _simd_u16x4_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u16x1 ANVIL_SIMD_CALL _simd_u16x8_extract(const register _simd_u16x8 x, const register int i) {
#ifdef _simd_u16x8_extract_
	return _simd_u16x8_extract_(x,i);
	#define _simd_u16x8_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_extract_instruction_set>()
#else
	return _simd_u16x8_extract_safe(x,i);
	#define _simd_u16x8_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u16x1 ANVIL_SIMD_CALL _simd_u16x16_extract(const register _simd_u16x16 x, const register int i) {
#ifdef _simd_u16x16_extract_
	return _simd_u16x16_extract_(x,i);
	#define _simd_u16x16_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_extract_instruction_set>()
#else
	return _simd_u16x16_extract_safe(x,i);
	#define _simd_u16x16_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u16x1 ANVIL_SIMD_CALL _simd_u16x32_extract(const register _simd_u16x32 x, const register int i) {
#ifdef _simd_u16x32_extract_
	return _simd_u16x32_extract_(x,i);
	#define _simd_u16x32_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_extract_instruction_set>()
#else
	return _simd_u16x32_extract_safe(x,i);
	#define _simd_u16x32_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u16x1 ANVIL_SIMD_CALL _simd_u16x64_extract(const register _simd_u16x64 x, const register int i) {
#ifdef _simd_u16x64_extract_
	return _simd_u16x64_extract_(x,i);
	#define _simd_u16x64_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_extract_instruction_set>()
#else
	return _simd_u16x64_extract_safe(x,i);
	#define _simd_u16x64_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s8x1 ANVIL_SIMD_CALL _simd_s8x2_extract(const register _simd_s8x2 x, const register int i) {
#ifdef _simd_s8x2_extract_
	return _simd_s8x2_extract_(x,i);
	#define _simd_s8x2_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_extract_instruction_set>()
#else
	return _simd_s8x2_extract_safe(x,i);
	#define _simd_s8x2_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s8x1 ANVIL_SIMD_CALL _simd_s8x4_extract(const register _simd_s8x4 x, const register int i) {
#ifdef _simd_s8x4_extract_
	return _simd_s8x4_extract_(x,i);
	#define _simd_s8x4_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_extract_instruction_set>()
#else
	return _simd_s8x4_extract_safe(x,i);
	#define _simd_s8x4_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s8x1 ANVIL_SIMD_CALL _simd_s8x8_extract(const register _simd_s8x8 x, const register int i) {
#ifdef _simd_s8x8_extract_
	return _simd_s8x8_extract_(x,i);
	#define _simd_s8x8_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_extract_instruction_set>()
#else
	return _simd_s8x8_extract_safe(x,i);
	#define _simd_s8x8_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s8x1 ANVIL_SIMD_CALL _simd_s8x16_extract(const register _simd_s8x16 x, const register int i) {
#ifdef _simd_s8x16_extract_
	return _simd_s8x16_extract_(x,i);
	#define _simd_s8x16_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_extract_instruction_set>()
#else
	return _simd_s8x16_extract_safe(x,i);
	#define _simd_s8x16_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s8x1 ANVIL_SIMD_CALL _simd_s8x32_extract(const register _simd_s8x32 x, const register int i) {
#ifdef _simd_s8x32_extract_
	return _simd_s8x32_extract_(x,i);
	#define _simd_s8x32_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_extract_instruction_set>()
#else
	return _simd_s8x32_extract_safe(x,i);
	#define _simd_s8x32_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s8x1 ANVIL_SIMD_CALL _simd_s8x64_extract(const register _simd_s8x64 x, const register int i) {
#ifdef _simd_s8x64_extract_
	return _simd_s8x64_extract_(x,i);
	#define _simd_s8x64_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_extract_instruction_set>()
#else
	return _simd_s8x64_extract_safe(x,i);
	#define _simd_s8x64_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u8x1 ANVIL_SIMD_CALL _simd_u8x2_extract(const register _simd_u8x2 x, const register int i) {
#ifdef _simd_u8x2_extract_
	return _simd_u8x2_extract_(x,i);
	#define _simd_u8x2_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_extract_instruction_set>()
#else
	return _simd_u8x2_extract_safe(x,i);
	#define _simd_u8x2_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u8x1 ANVIL_SIMD_CALL _simd_u8x4_extract(const register _simd_u8x4 x, const register int i) {
#ifdef _simd_u8x4_extract_
	return _simd_u8x4_extract_(x,i);
	#define _simd_u8x4_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_extract_instruction_set>()
#else
	return _simd_u8x4_extract_safe(x,i);
	#define _simd_u8x4_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u8x1 ANVIL_SIMD_CALL _simd_u8x8_extract(const register _simd_u8x8 x, const register int i) {
#ifdef _simd_u8x8_extract_
	return _simd_u8x8_extract_(x,i);
	#define _simd_u8x8_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_extract_instruction_set>()
#else
	return _simd_u8x8_extract_safe(x,i);
	#define _simd_u8x8_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u8x1 ANVIL_SIMD_CALL _simd_u8x16_extract(const register _simd_u8x16 x, const register int i) {
#ifdef _simd_u8x16_extract_
	return _simd_u8x16_extract_(x,i);
	#define _simd_u8x16_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_extract_instruction_set>()
#else
	return _simd_u8x16_extract_safe(x,i);
	#define _simd_u8x16_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u8x1 ANVIL_SIMD_CALL _simd_u8x32_extract(const register _simd_u8x32 x, const register int i) {
#ifdef _simd_u8x32_extract_
	return _simd_u8x32_extract_(x,i);
	#define _simd_u8x32_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_extract_instruction_set>()
#else
	return _simd_u8x32_extract_safe(x,i);
	#define _simd_u8x32_extract_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u8x1 ANVIL_SIMD_CALL _simd_u8x64_extract(const register _simd_u8x64 x, const register int i) {
#ifdef _simd_u8x64_extract_
	return _simd_u8x64_extract_(x,i);
	#define _simd_u8x64_extract_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_extract_instruction_set>()
#else
	return _simd_u8x64_extract_safe(x,i);
	#define _simd_u8x64_extract_enable() true
#endif
}
