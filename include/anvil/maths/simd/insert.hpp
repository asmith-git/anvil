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

static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_insert(const register _simd_f64x2 x, const register int i, const register _simd_f64x1 s) {
#ifdef _simd_f64x2_insert_
	return _simd_f64x2_insert_(x,i,s);
	#define _simd_f64x2_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_insert_instruction_set>()
#else
	return _simd_f64x2_insert_safe(x,i,s);
	#define _simd_f64x2_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_insert(const register _simd_f64x4 x, const register int i, const register _simd_f64x1 s) {
#ifdef _simd_f64x4_insert_
	return _simd_f64x4_insert_(x,i,s);
	#define _simd_f64x4_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_insert_instruction_set>()
#else
	return _simd_f64x4_insert_safe(x,i,s);
	#define _simd_f64x4_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f64x8 ANVIL_SIMD_CALL _simd_f64x8_insert(const register _simd_f64x8 x, const register int i, const register _simd_f64x1 s) {
#ifdef _simd_f64x8_insert_
	return _simd_f64x8_insert_(x,i,s);
	#define _simd_f64x8_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_insert_instruction_set>()
#else
	return _simd_f64x8_insert_safe(x,i,s);
	#define _simd_f64x8_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f64x16 ANVIL_SIMD_CALL _simd_f64x16_insert(const register _simd_f64x16 x, const register int i, const register _simd_f64x1 s) {
#ifdef _simd_f64x16_insert_
	return _simd_f64x16_insert_(x,i,s);
	#define _simd_f64x16_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_insert_instruction_set>()
#else
	return _simd_f64x16_insert_safe(x,i,s);
	#define _simd_f64x16_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f64x32 ANVIL_SIMD_CALL _simd_f64x32_insert(const register _simd_f64x32 x, const register int i, const register _simd_f64x1 s) {
#ifdef _simd_f64x32_insert_
	return _simd_f64x32_insert_(x,i,s);
	#define _simd_f64x32_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_insert_instruction_set>()
#else
	return _simd_f64x32_insert_safe(x,i,s);
	#define _simd_f64x32_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f64x64 ANVIL_SIMD_CALL _simd_f64x64_insert(const register _simd_f64x64 x, const register int i, const register _simd_f64x1 s) {
#ifdef _simd_f64x64_insert_
	return _simd_f64x64_insert_(x,i,s);
	#define _simd_f64x64_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_insert_instruction_set>()
#else
	return _simd_f64x64_insert_safe(x,i,s);
	#define _simd_f64x64_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_insert(const register _simd_f32x2 x, const register int i, const register _simd_f32x1 s) {
#ifdef _simd_f32x2_insert_
	return _simd_f32x2_insert_(x,i,s);
	#define _simd_f32x2_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_insert_instruction_set>()
#else
	return _simd_f32x2_insert_safe(x,i,s);
	#define _simd_f32x2_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_insert(const register _simd_f32x4 x, const register int i, const register _simd_f32x1 s) {
#ifdef _simd_f32x4_insert_
	return _simd_f32x4_insert_(x,i,s);
	#define _simd_f32x4_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_insert_instruction_set>()
#else
	return _simd_f32x4_insert_safe(x,i,s);
	#define _simd_f32x4_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f32x8 ANVIL_SIMD_CALL _simd_f32x8_insert(const register _simd_f32x8 x, const register int i, const register _simd_f32x1 s) {
#ifdef _simd_f32x8_insert_
	return _simd_f32x8_insert_(x,i,s);
	#define _simd_f32x8_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_insert_instruction_set>()
#else
	return _simd_f32x8_insert_safe(x,i,s);
	#define _simd_f32x8_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f32x16 ANVIL_SIMD_CALL _simd_f32x16_insert(const register _simd_f32x16 x, const register int i, const register _simd_f32x1 s) {
#ifdef _simd_f32x16_insert_
	return _simd_f32x16_insert_(x,i,s);
	#define _simd_f32x16_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_insert_instruction_set>()
#else
	return _simd_f32x16_insert_safe(x,i,s);
	#define _simd_f32x16_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f32x32 ANVIL_SIMD_CALL _simd_f32x32_insert(const register _simd_f32x32 x, const register int i, const register _simd_f32x1 s) {
#ifdef _simd_f32x32_insert_
	return _simd_f32x32_insert_(x,i,s);
	#define _simd_f32x32_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_insert_instruction_set>()
#else
	return _simd_f32x32_insert_safe(x,i,s);
	#define _simd_f32x32_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_f32x64 ANVIL_SIMD_CALL _simd_f32x64_insert(const register _simd_f32x64 x, const register int i, const register _simd_f32x1 s) {
#ifdef _simd_f32x64_insert_
	return _simd_f32x64_insert_(x,i,s);
	#define _simd_f32x64_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_insert_instruction_set>()
#else
	return _simd_f32x64_insert_safe(x,i,s);
	#define _simd_f32x64_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_insert(const register _simd_s64x2 x, const register int i, const register _simd_s64x1 s) {
#ifdef _simd_s64x2_insert_
	return _simd_s64x2_insert_(x,i,s);
	#define _simd_s64x2_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_insert_instruction_set>()
#else
	return _simd_s64x2_insert_safe(x,i,s);
	#define _simd_s64x2_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_insert(const register _simd_s64x4 x, const register int i, const register _simd_s64x1 s) {
#ifdef _simd_s64x4_insert_
	return _simd_s64x4_insert_(x,i,s);
	#define _simd_s64x4_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_insert_instruction_set>()
#else
	return _simd_s64x4_insert_safe(x,i,s);
	#define _simd_s64x4_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s64x8 ANVIL_SIMD_CALL _simd_s64x8_insert(const register _simd_s64x8 x, const register int i, const register _simd_s64x1 s) {
#ifdef _simd_s64x8_insert_
	return _simd_s64x8_insert_(x,i,s);
	#define _simd_s64x8_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_insert_instruction_set>()
#else
	return _simd_s64x8_insert_safe(x,i,s);
	#define _simd_s64x8_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s64x16 ANVIL_SIMD_CALL _simd_s64x16_insert(const register _simd_s64x16 x, const register int i, const register _simd_s64x1 s) {
#ifdef _simd_s64x16_insert_
	return _simd_s64x16_insert_(x,i,s);
	#define _simd_s64x16_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_insert_instruction_set>()
#else
	return _simd_s64x16_insert_safe(x,i,s);
	#define _simd_s64x16_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s64x32 ANVIL_SIMD_CALL _simd_s64x32_insert(const register _simd_s64x32 x, const register int i, const register _simd_s64x1 s) {
#ifdef _simd_s64x32_insert_
	return _simd_s64x32_insert_(x,i,s);
	#define _simd_s64x32_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_insert_instruction_set>()
#else
	return _simd_s64x32_insert_safe(x,i,s);
	#define _simd_s64x32_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s64x64 ANVIL_SIMD_CALL _simd_s64x64_insert(const register _simd_s64x64 x, const register int i, const register _simd_s64x1 s) {
#ifdef _simd_s64x64_insert_
	return _simd_s64x64_insert_(x,i,s);
	#define _simd_s64x64_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_insert_instruction_set>()
#else
	return _simd_s64x64_insert_safe(x,i,s);
	#define _simd_s64x64_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_insert(const register _simd_u64x2 x, const register int i, const register _simd_u64x1 s) {
#ifdef _simd_u64x2_insert_
	return _simd_u64x2_insert_(x,i,s);
	#define _simd_u64x2_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_insert_instruction_set>()
#else
	return _simd_u64x2_insert_safe(x,i,s);
	#define _simd_u64x2_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_insert(const register _simd_u64x4 x, const register int i, const register _simd_u64x1 s) {
#ifdef _simd_u64x4_insert_
	return _simd_u64x4_insert_(x,i,s);
	#define _simd_u64x4_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_insert_instruction_set>()
#else
	return _simd_u64x4_insert_safe(x,i,s);
	#define _simd_u64x4_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u64x8 ANVIL_SIMD_CALL _simd_u64x8_insert(const register _simd_u64x8 x, const register int i, const register _simd_u64x1 s) {
#ifdef _simd_u64x8_insert_
	return _simd_u64x8_insert_(x,i,s);
	#define _simd_u64x8_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_insert_instruction_set>()
#else
	return _simd_u64x8_insert_safe(x,i,s);
	#define _simd_u64x8_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u64x16 ANVIL_SIMD_CALL _simd_u64x16_insert(const register _simd_u64x16 x, const register int i, const register _simd_u64x1 s) {
#ifdef _simd_u64x16_insert_
	return _simd_u64x16_insert_(x,i,s);
	#define _simd_u64x16_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_insert_instruction_set>()
#else
	return _simd_u64x16_insert_safe(x,i,s);
	#define _simd_u64x16_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u64x32 ANVIL_SIMD_CALL _simd_u64x32_insert(const register _simd_u64x32 x, const register int i, const register _simd_u64x1 s) {
#ifdef _simd_u64x32_insert_
	return _simd_u64x32_insert_(x,i,s);
	#define _simd_u64x32_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_insert_instruction_set>()
#else
	return _simd_u64x32_insert_safe(x,i,s);
	#define _simd_u64x32_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u64x64 ANVIL_SIMD_CALL _simd_u64x64_insert(const register _simd_u64x64 x, const register int i, const register _simd_u64x1 s) {
#ifdef _simd_u64x64_insert_
	return _simd_u64x64_insert_(x,i,s);
	#define _simd_u64x64_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_insert_instruction_set>()
#else
	return _simd_u64x64_insert_safe(x,i,s);
	#define _simd_u64x64_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_insert(const register _simd_s32x2 x, const register int i, const register _simd_s32x1 s) {
#ifdef _simd_s32x2_insert_
	return _simd_s32x2_insert_(x,i,s);
	#define _simd_s32x2_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_insert_instruction_set>()
#else
	return _simd_s32x2_insert_safe(x,i,s);
	#define _simd_s32x2_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_insert(const register _simd_s32x4 x, const register int i, const register _simd_s32x1 s) {
#ifdef _simd_s32x4_insert_
	return _simd_s32x4_insert_(x,i,s);
	#define _simd_s32x4_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_insert_instruction_set>()
#else
	return _simd_s32x4_insert_safe(x,i,s);
	#define _simd_s32x4_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s32x8 ANVIL_SIMD_CALL _simd_s32x8_insert(const register _simd_s32x8 x, const register int i, const register _simd_s32x1 s) {
#ifdef _simd_s32x8_insert_
	return _simd_s32x8_insert_(x,i,s);
	#define _simd_s32x8_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_insert_instruction_set>()
#else
	return _simd_s32x8_insert_safe(x,i,s);
	#define _simd_s32x8_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s32x16 ANVIL_SIMD_CALL _simd_s32x16_insert(const register _simd_s32x16 x, const register int i, const register _simd_s32x1 s) {
#ifdef _simd_s32x16_insert_
	return _simd_s32x16_insert_(x,i,s);
	#define _simd_s32x16_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_insert_instruction_set>()
#else
	return _simd_s32x16_insert_safe(x,i,s);
	#define _simd_s32x16_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s32x32 ANVIL_SIMD_CALL _simd_s32x32_insert(const register _simd_s32x32 x, const register int i, const register _simd_s32x1 s) {
#ifdef _simd_s32x32_insert_
	return _simd_s32x32_insert_(x,i,s);
	#define _simd_s32x32_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_insert_instruction_set>()
#else
	return _simd_s32x32_insert_safe(x,i,s);
	#define _simd_s32x32_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s32x64 ANVIL_SIMD_CALL _simd_s32x64_insert(const register _simd_s32x64 x, const register int i, const register _simd_s32x1 s) {
#ifdef _simd_s32x64_insert_
	return _simd_s32x64_insert_(x,i,s);
	#define _simd_s32x64_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_insert_instruction_set>()
#else
	return _simd_s32x64_insert_safe(x,i,s);
	#define _simd_s32x64_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_insert(const register _simd_u32x2 x, const register int i, const register _simd_u32x1 s) {
#ifdef _simd_u32x2_insert_
	return _simd_u32x2_insert_(x,i,s);
	#define _simd_u32x2_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_insert_instruction_set>()
#else
	return _simd_u32x2_insert_safe(x,i,s);
	#define _simd_u32x2_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_insert(const register _simd_u32x4 x, const register int i, const register _simd_u32x1 s) {
#ifdef _simd_u32x4_insert_
	return _simd_u32x4_insert_(x,i,s);
	#define _simd_u32x4_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_insert_instruction_set>()
#else
	return _simd_u32x4_insert_safe(x,i,s);
	#define _simd_u32x4_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u32x8 ANVIL_SIMD_CALL _simd_u32x8_insert(const register _simd_u32x8 x, const register int i, const register _simd_u32x1 s) {
#ifdef _simd_u32x8_insert_
	return _simd_u32x8_insert_(x,i,s);
	#define _simd_u32x8_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_insert_instruction_set>()
#else
	return _simd_u32x8_insert_safe(x,i,s);
	#define _simd_u32x8_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u32x16 ANVIL_SIMD_CALL _simd_u32x16_insert(const register _simd_u32x16 x, const register int i, const register _simd_u32x1 s) {
#ifdef _simd_u32x16_insert_
	return _simd_u32x16_insert_(x,i,s);
	#define _simd_u32x16_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_insert_instruction_set>()
#else
	return _simd_u32x16_insert_safe(x,i,s);
	#define _simd_u32x16_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u32x32 ANVIL_SIMD_CALL _simd_u32x32_insert(const register _simd_u32x32 x, const register int i, const register _simd_u32x1 s) {
#ifdef _simd_u32x32_insert_
	return _simd_u32x32_insert_(x,i,s);
	#define _simd_u32x32_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_insert_instruction_set>()
#else
	return _simd_u32x32_insert_safe(x,i,s);
	#define _simd_u32x32_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u32x64 ANVIL_SIMD_CALL _simd_u32x64_insert(const register _simd_u32x64 x, const register int i, const register _simd_u32x1 s) {
#ifdef _simd_u32x64_insert_
	return _simd_u32x64_insert_(x,i,s);
	#define _simd_u32x64_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_insert_instruction_set>()
#else
	return _simd_u32x64_insert_safe(x,i,s);
	#define _simd_u32x64_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_insert(const register _simd_s16x2 x, const register int i, const register _simd_s16x1 s) {
#ifdef _simd_s16x2_insert_
	return _simd_s16x2_insert_(x,i,s);
	#define _simd_s16x2_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_insert_instruction_set>()
#else
	return _simd_s16x2_insert_safe(x,i,s);
	#define _simd_s16x2_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_insert(const register _simd_s16x4 x, const register int i, const register _simd_s16x1 s) {
#ifdef _simd_s16x4_insert_
	return _simd_s16x4_insert_(x,i,s);
	#define _simd_s16x4_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_insert_instruction_set>()
#else
	return _simd_s16x4_insert_safe(x,i,s);
	#define _simd_s16x4_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s16x8 ANVIL_SIMD_CALL _simd_s16x8_insert(const register _simd_s16x8 x, const register int i, const register _simd_s16x1 s) {
#ifdef _simd_s16x8_insert_
	return _simd_s16x8_insert_(x,i,s);
	#define _simd_s16x8_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_insert_instruction_set>()
#else
	return _simd_s16x8_insert_safe(x,i,s);
	#define _simd_s16x8_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s16x16 ANVIL_SIMD_CALL _simd_s16x16_insert(const register _simd_s16x16 x, const register int i, const register _simd_s16x1 s) {
#ifdef _simd_s16x16_insert_
	return _simd_s16x16_insert_(x,i,s);
	#define _simd_s16x16_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_insert_instruction_set>()
#else
	return _simd_s16x16_insert_safe(x,i,s);
	#define _simd_s16x16_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s16x32 ANVIL_SIMD_CALL _simd_s16x32_insert(const register _simd_s16x32 x, const register int i, const register _simd_s16x1 s) {
#ifdef _simd_s16x32_insert_
	return _simd_s16x32_insert_(x,i,s);
	#define _simd_s16x32_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_insert_instruction_set>()
#else
	return _simd_s16x32_insert_safe(x,i,s);
	#define _simd_s16x32_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s16x64 ANVIL_SIMD_CALL _simd_s16x64_insert(const register _simd_s16x64 x, const register int i, const register _simd_s16x1 s) {
#ifdef _simd_s16x64_insert_
	return _simd_s16x64_insert_(x,i,s);
	#define _simd_s16x64_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_insert_instruction_set>()
#else
	return _simd_s16x64_insert_safe(x,i,s);
	#define _simd_s16x64_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_insert(const register _simd_u16x2 x, const register int i, const register _simd_u16x1 s) {
#ifdef _simd_u16x2_insert_
	return _simd_u16x2_insert_(x,i,s);
	#define _simd_u16x2_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_insert_instruction_set>()
#else
	return _simd_u16x2_insert_safe(x,i,s);
	#define _simd_u16x2_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_insert(const register _simd_u16x4 x, const register int i, const register _simd_u16x1 s) {
#ifdef _simd_u16x4_insert_
	return _simd_u16x4_insert_(x,i,s);
	#define _simd_u16x4_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_insert_instruction_set>()
#else
	return _simd_u16x4_insert_safe(x,i,s);
	#define _simd_u16x4_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u16x8 ANVIL_SIMD_CALL _simd_u16x8_insert(const register _simd_u16x8 x, const register int i, const register _simd_u16x1 s) {
#ifdef _simd_u16x8_insert_
	return _simd_u16x8_insert_(x,i,s);
	#define _simd_u16x8_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_insert_instruction_set>()
#else
	return _simd_u16x8_insert_safe(x,i,s);
	#define _simd_u16x8_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u16x16 ANVIL_SIMD_CALL _simd_u16x16_insert(const register _simd_u16x16 x, const register int i, const register _simd_u16x1 s) {
#ifdef _simd_u16x16_insert_
	return _simd_u16x16_insert_(x,i,s);
	#define _simd_u16x16_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_insert_instruction_set>()
#else
	return _simd_u16x16_insert_safe(x,i,s);
	#define _simd_u16x16_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u16x32 ANVIL_SIMD_CALL _simd_u16x32_insert(const register _simd_u16x32 x, const register int i, const register _simd_u16x1 s) {
#ifdef _simd_u16x32_insert_
	return _simd_u16x32_insert_(x,i,s);
	#define _simd_u16x32_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_insert_instruction_set>()
#else
	return _simd_u16x32_insert_safe(x,i,s);
	#define _simd_u16x32_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u16x64 ANVIL_SIMD_CALL _simd_u16x64_insert(const register _simd_u16x64 x, const register int i, const register _simd_u16x1 s) {
#ifdef _simd_u16x64_insert_
	return _simd_u16x64_insert_(x,i,s);
	#define _simd_u16x64_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_insert_instruction_set>()
#else
	return _simd_u16x64_insert_safe(x,i,s);
	#define _simd_u16x64_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_insert(const register _simd_s8x2 x, const register int i, const register _simd_s8x1 s) {
#ifdef _simd_s8x2_insert_
	return _simd_s8x2_insert_(x,i,s);
	#define _simd_s8x2_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_insert_instruction_set>()
#else
	return _simd_s8x2_insert_safe(x,i,s);
	#define _simd_s8x2_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_insert(const register _simd_s8x4 x, const register int i, const register _simd_s8x1 s) {
#ifdef _simd_s8x4_insert_
	return _simd_s8x4_insert_(x,i,s);
	#define _simd_s8x4_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_insert_instruction_set>()
#else
	return _simd_s8x4_insert_safe(x,i,s);
	#define _simd_s8x4_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s8x8 ANVIL_SIMD_CALL _simd_s8x8_insert(const register _simd_s8x8 x, const register int i, const register _simd_s8x1 s) {
#ifdef _simd_s8x8_insert_
	return _simd_s8x8_insert_(x,i,s);
	#define _simd_s8x8_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_insert_instruction_set>()
#else
	return _simd_s8x8_insert_safe(x,i,s);
	#define _simd_s8x8_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s8x16 ANVIL_SIMD_CALL _simd_s8x16_insert(const register _simd_s8x16 x, const register int i, const register _simd_s8x1 s) {
#ifdef _simd_s8x16_insert_
	return _simd_s8x16_insert_(x,i,s);
	#define _simd_s8x16_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_insert_instruction_set>()
#else
	return _simd_s8x16_insert_safe(x,i,s);
	#define _simd_s8x16_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s8x32 ANVIL_SIMD_CALL _simd_s8x32_insert(const register _simd_s8x32 x, const register int i, const register _simd_s8x1 s) {
#ifdef _simd_s8x32_insert_
	return _simd_s8x32_insert_(x,i,s);
	#define _simd_s8x32_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_insert_instruction_set>()
#else
	return _simd_s8x32_insert_safe(x,i,s);
	#define _simd_s8x32_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_s8x64 ANVIL_SIMD_CALL _simd_s8x64_insert(const register _simd_s8x64 x, const register int i, const register _simd_s8x1 s) {
#ifdef _simd_s8x64_insert_
	return _simd_s8x64_insert_(x,i,s);
	#define _simd_s8x64_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_insert_instruction_set>()
#else
	return _simd_s8x64_insert_safe(x,i,s);
	#define _simd_s8x64_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_insert(const register _simd_u8x2 x, const register int i, const register _simd_u8x1 s) {
#ifdef _simd_u8x2_insert_
	return _simd_u8x2_insert_(x,i,s);
	#define _simd_u8x2_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_insert_instruction_set>()
#else
	return _simd_u8x2_insert_safe(x,i,s);
	#define _simd_u8x2_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_insert(const register _simd_u8x4 x, const register int i, const register _simd_u8x1 s) {
#ifdef _simd_u8x4_insert_
	return _simd_u8x4_insert_(x,i,s);
	#define _simd_u8x4_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_insert_instruction_set>()
#else
	return _simd_u8x4_insert_safe(x,i,s);
	#define _simd_u8x4_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u8x8 ANVIL_SIMD_CALL _simd_u8x8_insert(const register _simd_u8x8 x, const register int i, const register _simd_u8x1 s) {
#ifdef _simd_u8x8_insert_
	return _simd_u8x8_insert_(x,i,s);
	#define _simd_u8x8_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_insert_instruction_set>()
#else
	return _simd_u8x8_insert_safe(x,i,s);
	#define _simd_u8x8_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u8x16 ANVIL_SIMD_CALL _simd_u8x16_insert(const register _simd_u8x16 x, const register int i, const register _simd_u8x1 s) {
#ifdef _simd_u8x16_insert_
	return _simd_u8x16_insert_(x,i,s);
	#define _simd_u8x16_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_insert_instruction_set>()
#else
	return _simd_u8x16_insert_safe(x,i,s);
	#define _simd_u8x16_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u8x32 ANVIL_SIMD_CALL _simd_u8x32_insert(const register _simd_u8x32 x, const register int i, const register _simd_u8x1 s) {
#ifdef _simd_u8x32_insert_
	return _simd_u8x32_insert_(x,i,s);
	#define _simd_u8x32_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_insert_instruction_set>()
#else
	return _simd_u8x32_insert_safe(x,i,s);
	#define _simd_u8x32_insert_enable() true
#endif
}
static ANVIL_STRONG_INLINE _simd_u8x64 ANVIL_SIMD_CALL _simd_u8x64_insert(const register _simd_u8x64 x, const register int i, const register _simd_u8x1 s) {
#ifdef _simd_u8x64_insert_
	return _simd_u8x64_insert_(x,i,s);
	#define _simd_u8x64_insert_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_insert_instruction_set>()
#else
	return _simd_u8x64_insert_safe(x,i,s);
	#define _simd_u8x64_insert_enable() true
#endif
}