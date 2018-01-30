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

#ifdef _simd_f64x2_combine_
	#define _simd_f64x2_combine(X,Y)  _simd_f64x2_combine_(X,Y)
	#define _simd_f64x2_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_combine_instruction_set>()
#else
	#define _simd_f64x2_combine(X,Y) _simd_f64x2_combine_safe(X,Y)
	#define _simd_f64x2_combine_enable() true
#endif
#ifdef _simd_f64x4_combine_
	#define _simd_f64x4_combine(X,Y)  _simd_f64x4_combine_(X,Y)
	#define _simd_f64x4_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_combine_instruction_set>()
#else
	#define _simd_f64x4_combine(X,Y) _simd_f64x4_combine_safe(X,Y)
	#define _simd_f64x4_combine_enable() true
#endif
#ifdef _simd_f64x8_combine_
	#define _simd_f64x8_combine(X,Y)  _simd_f64x8_combine_(X,Y)
	#define _simd_f64x8_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_combine_instruction_set>()
#else
	#define _simd_f64x8_combine(X,Y) _simd_f64x8_combine_safe(X,Y)
	#define _simd_f64x8_combine_enable() true
#endif
#ifdef _simd_f64x16_combine_
	#define _simd_f64x16_combine(X,Y)  _simd_f64x16_combine_(X,Y)
	#define _simd_f64x16_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_combine_instruction_set>()
#else
	#define _simd_f64x16_combine(X,Y) _simd_f64x16_combine_safe(X,Y)
	#define _simd_f64x16_combine_enable() true
#endif
#ifdef _simd_f64x32_combine_
	#define _simd_f64x32_combine(X,Y)  _simd_f64x32_combine_(X,Y)
	#define _simd_f64x32_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_combine_instruction_set>()
#else
	#define _simd_f64x32_combine(X,Y) _simd_f64x32_combine_safe(X,Y)
	#define _simd_f64x32_combine_enable() true
#endif
#ifdef _simd_f64x64_combine_
	#define _simd_f64x64_combine(X,Y)  _simd_f64x64_combine_(X,Y)
	#define _simd_f64x64_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_combine_instruction_set>()
#else
	#define _simd_f64x64_combine(X,Y) _simd_f64x64_combine_safe(X,Y)
	#define _simd_f64x64_combine_enable() true
#endif
#ifdef _simd_f32x2_combine_
	#define _simd_f32x2_combine(X,Y)  _simd_f32x2_combine_(X,Y)
	#define _simd_f32x2_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_combine_instruction_set>()
#else
	#define _simd_f32x2_combine(X,Y) _simd_f32x2_combine_safe(X,Y)
	#define _simd_f32x2_combine_enable() true
#endif
#ifdef _simd_f32x4_combine_
	#define _simd_f32x4_combine(X,Y)  _simd_f32x4_combine_(X,Y)
	#define _simd_f32x4_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_combine_instruction_set>()
#else
	#define _simd_f32x4_combine(X,Y) _simd_f32x4_combine_safe(X,Y)
	#define _simd_f32x4_combine_enable() true
#endif
#ifdef _simd_f32x8_combine_
	#define _simd_f32x8_combine(X,Y)  _simd_f32x8_combine_(X,Y)
	#define _simd_f32x8_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_combine_instruction_set>()
#else
	#define _simd_f32x8_combine(X,Y) _simd_f32x8_combine_safe(X,Y)
	#define _simd_f32x8_combine_enable() true
#endif
#ifdef _simd_f32x16_combine_
	#define _simd_f32x16_combine(X,Y)  _simd_f32x16_combine_(X,Y)
	#define _simd_f32x16_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_combine_instruction_set>()
#else
	#define _simd_f32x16_combine(X,Y) _simd_f32x16_combine_safe(X,Y)
	#define _simd_f32x16_combine_enable() true
#endif
#ifdef _simd_f32x32_combine_
	#define _simd_f32x32_combine(X,Y)  _simd_f32x32_combine_(X,Y)
	#define _simd_f32x32_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_combine_instruction_set>()
#else
	#define _simd_f32x32_combine(X,Y) _simd_f32x32_combine_safe(X,Y)
	#define _simd_f32x32_combine_enable() true
#endif
#ifdef _simd_f32x64_combine_
	#define _simd_f32x64_combine(X,Y)  _simd_f32x64_combine_(X,Y)
	#define _simd_f32x64_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_combine_instruction_set>()
#else
	#define _simd_f32x64_combine(X,Y) _simd_f32x64_combine_safe(X,Y)
	#define _simd_f32x64_combine_enable() true
#endif
#ifdef _simd_s64x2_combine_
	#define _simd_s64x2_combine(X,Y)  _simd_s64x2_combine_(X,Y)
	#define _simd_s64x2_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_combine_instruction_set>()
#else
	#define _simd_s64x2_combine(X,Y) _simd_s64x2_combine_safe(X,Y)
	#define _simd_s64x2_combine_enable() true
#endif
#ifdef _simd_s64x4_combine_
	#define _simd_s64x4_combine(X,Y)  _simd_s64x4_combine_(X,Y)
	#define _simd_s64x4_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_combine_instruction_set>()
#else
	#define _simd_s64x4_combine(X,Y) _simd_s64x4_combine_safe(X,Y)
	#define _simd_s64x4_combine_enable() true
#endif
#ifdef _simd_s64x8_combine_
	#define _simd_s64x8_combine(X,Y)  _simd_s64x8_combine_(X,Y)
	#define _simd_s64x8_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_combine_instruction_set>()
#else
	#define _simd_s64x8_combine(X,Y) _simd_s64x8_combine_safe(X,Y)
	#define _simd_s64x8_combine_enable() true
#endif
#ifdef _simd_s64x16_combine_
	#define _simd_s64x16_combine(X,Y)  _simd_s64x16_combine_(X,Y)
	#define _simd_s64x16_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_combine_instruction_set>()
#else
	#define _simd_s64x16_combine(X,Y) _simd_s64x16_combine_safe(X,Y)
	#define _simd_s64x16_combine_enable() true
#endif
#ifdef _simd_s64x32_combine_
	#define _simd_s64x32_combine(X,Y)  _simd_s64x32_combine_(X,Y)
	#define _simd_s64x32_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_combine_instruction_set>()
#else
	#define _simd_s64x32_combine(X,Y) _simd_s64x32_combine_safe(X,Y)
	#define _simd_s64x32_combine_enable() true
#endif
#ifdef _simd_s64x64_combine_
	#define _simd_s64x64_combine(X,Y)  _simd_s64x64_combine_(X,Y)
	#define _simd_s64x64_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_combine_instruction_set>()
#else
	#define _simd_s64x64_combine(X,Y) _simd_s64x64_combine_safe(X,Y)
	#define _simd_s64x64_combine_enable() true
#endif
#ifdef _simd_u64x2_combine_
	#define _simd_u64x2_combine(X,Y)  _simd_u64x2_combine_(X,Y)
	#define _simd_u64x2_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_combine_instruction_set>()
#else
	#define _simd_u64x2_combine(X,Y) _simd_u64x2_combine_safe(X,Y)
	#define _simd_u64x2_combine_enable() true
#endif
#ifdef _simd_u64x4_combine_
	#define _simd_u64x4_combine(X,Y)  _simd_u64x4_combine_(X,Y)
	#define _simd_u64x4_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_combine_instruction_set>()
#else
	#define _simd_u64x4_combine(X,Y) _simd_u64x4_combine_safe(X,Y)
	#define _simd_u64x4_combine_enable() true
#endif
#ifdef _simd_u64x8_combine_
	#define _simd_u64x8_combine(X,Y)  _simd_u64x8_combine_(X,Y)
	#define _simd_u64x8_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_combine_instruction_set>()
#else
	#define _simd_u64x8_combine(X,Y) _simd_u64x8_combine_safe(X,Y)
	#define _simd_u64x8_combine_enable() true
#endif
#ifdef _simd_u64x16_combine_
	#define _simd_u64x16_combine(X,Y)  _simd_u64x16_combine_(X,Y)
	#define _simd_u64x16_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_combine_instruction_set>()
#else
	#define _simd_u64x16_combine(X,Y) _simd_u64x16_combine_safe(X,Y)
	#define _simd_u64x16_combine_enable() true
#endif
#ifdef _simd_u64x32_combine_
	#define _simd_u64x32_combine(X,Y)  _simd_u64x32_combine_(X,Y)
	#define _simd_u64x32_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_combine_instruction_set>()
#else
	#define _simd_u64x32_combine(X,Y) _simd_u64x32_combine_safe(X,Y)
	#define _simd_u64x32_combine_enable() true
#endif
#ifdef _simd_u64x64_combine_
	#define _simd_u64x64_combine(X,Y)  _simd_u64x64_combine_(X,Y)
	#define _simd_u64x64_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_combine_instruction_set>()
#else
	#define _simd_u64x64_combine(X,Y) _simd_u64x64_combine_safe(X,Y)
	#define _simd_u64x64_combine_enable() true
#endif
#ifdef _simd_s32x2_combine_
	#define _simd_s32x2_combine(X,Y)  _simd_s32x2_combine_(X,Y)
	#define _simd_s32x2_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_combine_instruction_set>()
#else
	#define _simd_s32x2_combine(X,Y) _simd_s32x2_combine_safe(X,Y)
	#define _simd_s32x2_combine_enable() true
#endif
#ifdef _simd_s32x4_combine_
	#define _simd_s32x4_combine(X,Y)  _simd_s32x4_combine_(X,Y)
	#define _simd_s32x4_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_combine_instruction_set>()
#else
	#define _simd_s32x4_combine(X,Y) _simd_s32x4_combine_safe(X,Y)
	#define _simd_s32x4_combine_enable() true
#endif
#ifdef _simd_s32x8_combine_
	#define _simd_s32x8_combine(X,Y)  _simd_s32x8_combine_(X,Y)
	#define _simd_s32x8_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_combine_instruction_set>()
#else
	#define _simd_s32x8_combine(X,Y) _simd_s32x8_combine_safe(X,Y)
	#define _simd_s32x8_combine_enable() true
#endif
#ifdef _simd_s32x16_combine_
	#define _simd_s32x16_combine(X,Y)  _simd_s32x16_combine_(X,Y)
	#define _simd_s32x16_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_combine_instruction_set>()
#else
	#define _simd_s32x16_combine(X,Y) _simd_s32x16_combine_safe(X,Y)
	#define _simd_s32x16_combine_enable() true
#endif
#ifdef _simd_s32x32_combine_
	#define _simd_s32x32_combine(X,Y)  _simd_s32x32_combine_(X,Y)
	#define _simd_s32x32_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_combine_instruction_set>()
#else
	#define _simd_s32x32_combine(X,Y) _simd_s32x32_combine_safe(X,Y)
	#define _simd_s32x32_combine_enable() true
#endif
#ifdef _simd_s32x64_combine_
	#define _simd_s32x64_combine(X,Y)  _simd_s32x64_combine_(X,Y)
	#define _simd_s32x64_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_combine_instruction_set>()
#else
	#define _simd_s32x64_combine(X,Y) _simd_s32x64_combine_safe(X,Y)
	#define _simd_s32x64_combine_enable() true
#endif
#ifdef _simd_u32x2_combine_
	#define _simd_u32x2_combine(X,Y)  _simd_u32x2_combine_(X,Y)
	#define _simd_u32x2_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_combine_instruction_set>()
#else
	#define _simd_u32x2_combine(X,Y) _simd_u32x2_combine_safe(X,Y)
	#define _simd_u32x2_combine_enable() true
#endif
#ifdef _simd_u32x4_combine_
	#define _simd_u32x4_combine(X,Y)  _simd_u32x4_combine_(X,Y)
	#define _simd_u32x4_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_combine_instruction_set>()
#else
	#define _simd_u32x4_combine(X,Y) _simd_u32x4_combine_safe(X,Y)
	#define _simd_u32x4_combine_enable() true
#endif
#ifdef _simd_u32x8_combine_
	#define _simd_u32x8_combine(X,Y)  _simd_u32x8_combine_(X,Y)
	#define _simd_u32x8_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_combine_instruction_set>()
#else
	#define _simd_u32x8_combine(X,Y) _simd_u32x8_combine_safe(X,Y)
	#define _simd_u32x8_combine_enable() true
#endif
#ifdef _simd_u32x16_combine_
	#define _simd_u32x16_combine(X,Y)  _simd_u32x16_combine_(X,Y)
	#define _simd_u32x16_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_combine_instruction_set>()
#else
	#define _simd_u32x16_combine(X,Y) _simd_u32x16_combine_safe(X,Y)
	#define _simd_u32x16_combine_enable() true
#endif
#ifdef _simd_u32x32_combine_
	#define _simd_u32x32_combine(X,Y)  _simd_u32x32_combine_(X,Y)
	#define _simd_u32x32_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_combine_instruction_set>()
#else
	#define _simd_u32x32_combine(X,Y) _simd_u32x32_combine_safe(X,Y)
	#define _simd_u32x32_combine_enable() true
#endif
#ifdef _simd_u32x64_combine_
	#define _simd_u32x64_combine(X,Y)  _simd_u32x64_combine_(X,Y)
	#define _simd_u32x64_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_combine_instruction_set>()
#else
	#define _simd_u32x64_combine(X,Y) _simd_u32x64_combine_safe(X,Y)
	#define _simd_u32x64_combine_enable() true
#endif
#ifdef _simd_s16x2_combine_
	#define _simd_s16x2_combine(X,Y)  _simd_s16x2_combine_(X,Y)
	#define _simd_s16x2_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_combine_instruction_set>()
#else
	#define _simd_s16x2_combine(X,Y) _simd_s16x2_combine_safe(X,Y)
	#define _simd_s16x2_combine_enable() true
#endif
#ifdef _simd_s16x4_combine_
	#define _simd_s16x4_combine(X,Y)  _simd_s16x4_combine_(X,Y)
	#define _simd_s16x4_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_combine_instruction_set>()
#else
	#define _simd_s16x4_combine(X,Y) _simd_s16x4_combine_safe(X,Y)
	#define _simd_s16x4_combine_enable() true
#endif
#ifdef _simd_s16x8_combine_
	#define _simd_s16x8_combine(X,Y)  _simd_s16x8_combine_(X,Y)
	#define _simd_s16x8_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_combine_instruction_set>()
#else
	#define _simd_s16x8_combine(X,Y) _simd_s16x8_combine_safe(X,Y)
	#define _simd_s16x8_combine_enable() true
#endif
#ifdef _simd_s16x16_combine_
	#define _simd_s16x16_combine(X,Y)  _simd_s16x16_combine_(X,Y)
	#define _simd_s16x16_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_combine_instruction_set>()
#else
	#define _simd_s16x16_combine(X,Y) _simd_s16x16_combine_safe(X,Y)
	#define _simd_s16x16_combine_enable() true
#endif
#ifdef _simd_s16x32_combine_
	#define _simd_s16x32_combine(X,Y)  _simd_s16x32_combine_(X,Y)
	#define _simd_s16x32_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_combine_instruction_set>()
#else
	#define _simd_s16x32_combine(X,Y) _simd_s16x32_combine_safe(X,Y)
	#define _simd_s16x32_combine_enable() true
#endif
#ifdef _simd_s16x64_combine_
	#define _simd_s16x64_combine(X,Y)  _simd_s16x64_combine_(X,Y)
	#define _simd_s16x64_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_combine_instruction_set>()
#else
	#define _simd_s16x64_combine(X,Y) _simd_s16x64_combine_safe(X,Y)
	#define _simd_s16x64_combine_enable() true
#endif
#ifdef _simd_u16x2_combine_
	#define _simd_u16x2_combine(X,Y)  _simd_u16x2_combine_(X,Y)
	#define _simd_u16x2_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_combine_instruction_set>()
#else
	#define _simd_u16x2_combine(X,Y) _simd_u16x2_combine_safe(X,Y)
	#define _simd_u16x2_combine_enable() true
#endif
#ifdef _simd_u16x4_combine_
	#define _simd_u16x4_combine(X,Y)  _simd_u16x4_combine_(X,Y)
	#define _simd_u16x4_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_combine_instruction_set>()
#else
	#define _simd_u16x4_combine(X,Y) _simd_u16x4_combine_safe(X,Y)
	#define _simd_u16x4_combine_enable() true
#endif
#ifdef _simd_u16x8_combine_
	#define _simd_u16x8_combine(X,Y)  _simd_u16x8_combine_(X,Y)
	#define _simd_u16x8_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_combine_instruction_set>()
#else
	#define _simd_u16x8_combine(X,Y) _simd_u16x8_combine_safe(X,Y)
	#define _simd_u16x8_combine_enable() true
#endif
#ifdef _simd_u16x16_combine_
	#define _simd_u16x16_combine(X,Y)  _simd_u16x16_combine_(X,Y)
	#define _simd_u16x16_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_combine_instruction_set>()
#else
	#define _simd_u16x16_combine(X,Y) _simd_u16x16_combine_safe(X,Y)
	#define _simd_u16x16_combine_enable() true
#endif
#ifdef _simd_u16x32_combine_
	#define _simd_u16x32_combine(X,Y)  _simd_u16x32_combine_(X,Y)
	#define _simd_u16x32_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_combine_instruction_set>()
#else
	#define _simd_u16x32_combine(X,Y) _simd_u16x32_combine_safe(X,Y)
	#define _simd_u16x32_combine_enable() true
#endif
#ifdef _simd_u16x64_combine_
	#define _simd_u16x64_combine(X,Y)  _simd_u16x64_combine_(X,Y)
	#define _simd_u16x64_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_combine_instruction_set>()
#else
	#define _simd_u16x64_combine(X,Y) _simd_u16x64_combine_safe(X,Y)
	#define _simd_u16x64_combine_enable() true
#endif
#ifdef _simd_s8x2_combine_
	#define _simd_s8x2_combine(X,Y)  _simd_s8x2_combine_(X,Y)
	#define _simd_s8x2_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_combine_instruction_set>()
#else
	#define _simd_s8x2_combine(X,Y) _simd_s8x2_combine_safe(X,Y)
	#define _simd_s8x2_combine_enable() true
#endif
#ifdef _simd_s8x4_combine_
	#define _simd_s8x4_combine(X,Y)  _simd_s8x4_combine_(X,Y)
	#define _simd_s8x4_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_combine_instruction_set>()
#else
	#define _simd_s8x4_combine(X,Y) _simd_s8x4_combine_safe(X,Y)
	#define _simd_s8x4_combine_enable() true
#endif
#ifdef _simd_s8x8_combine_
	#define _simd_s8x8_combine(X,Y)  _simd_s8x8_combine_(X,Y)
	#define _simd_s8x8_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_combine_instruction_set>()
#else
	#define _simd_s8x8_combine(X,Y) _simd_s8x8_combine_safe(X,Y)
	#define _simd_s8x8_combine_enable() true
#endif
#ifdef _simd_s8x16_combine_
	#define _simd_s8x16_combine(X,Y)  _simd_s8x16_combine_(X,Y)
	#define _simd_s8x16_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_combine_instruction_set>()
#else
	#define _simd_s8x16_combine(X,Y) _simd_s8x16_combine_safe(X,Y)
	#define _simd_s8x16_combine_enable() true
#endif
#ifdef _simd_s8x32_combine_
	#define _simd_s8x32_combine(X,Y)  _simd_s8x32_combine_(X,Y)
	#define _simd_s8x32_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_combine_instruction_set>()
#else
	#define _simd_s8x32_combine(X,Y) _simd_s8x32_combine_safe(X,Y)
	#define _simd_s8x32_combine_enable() true
#endif
#ifdef _simd_s8x64_combine_
	#define _simd_s8x64_combine(X,Y)  _simd_s8x64_combine_(X,Y)
	#define _simd_s8x64_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_combine_instruction_set>()
#else
	#define _simd_s8x64_combine(X,Y) _simd_s8x64_combine_safe(X,Y)
	#define _simd_s8x64_combine_enable() true
#endif
#ifdef _simd_u8x2_combine_
	#define _simd_u8x2_combine(X,Y)  _simd_u8x2_combine_(X,Y)
	#define _simd_u8x2_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_combine_instruction_set>()
#else
	#define _simd_u8x2_combine(X,Y) _simd_u8x2_combine_safe(X,Y)
	#define _simd_u8x2_combine_enable() true
#endif
#ifdef _simd_u8x4_combine_
	#define _simd_u8x4_combine(X,Y)  _simd_u8x4_combine_(X,Y)
	#define _simd_u8x4_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_combine_instruction_set>()
#else
	#define _simd_u8x4_combine(X,Y) _simd_u8x4_combine_safe(X,Y)
	#define _simd_u8x4_combine_enable() true
#endif
#ifdef _simd_u8x8_combine_
	#define _simd_u8x8_combine(X,Y)  _simd_u8x8_combine_(X,Y)
	#define _simd_u8x8_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_combine_instruction_set>()
#else
	#define _simd_u8x8_combine(X,Y) _simd_u8x8_combine_safe(X,Y)
	#define _simd_u8x8_combine_enable() true
#endif
#ifdef _simd_u8x16_combine_
	#define _simd_u8x16_combine(X,Y)  _simd_u8x16_combine_(X,Y)
	#define _simd_u8x16_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_combine_instruction_set>()
#else
	#define _simd_u8x16_combine(X,Y) _simd_u8x16_combine_safe(X,Y)
	#define _simd_u8x16_combine_enable() true
#endif
#ifdef _simd_u8x32_combine_
	#define _simd_u8x32_combine(X,Y)  _simd_u8x32_combine_(X,Y)
	#define _simd_u8x32_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_combine_instruction_set>()
#else
	#define _simd_u8x32_combine(X,Y) _simd_u8x32_combine_safe(X,Y)
	#define _simd_u8x32_combine_enable() true
#endif
#ifdef _simd_u8x64_combine_
	#define _simd_u8x64_combine(X,Y)  _simd_u8x64_combine_(X,Y)
	#define _simd_u8x64_combine_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_combine_instruction_set>()
#else
	#define _simd_u8x64_combine(X,Y) _simd_u8x64_combine_safe(X,Y)
	#define _simd_u8x64_combine_enable() true
#endif
