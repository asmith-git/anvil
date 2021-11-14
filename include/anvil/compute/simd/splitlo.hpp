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

#define _simd_f64x2_splitlo_safe(X) reinterpret_cast<const _simd_f64x1*>(&X)[0]
#ifdef _simd_f64x2_splitlo_
	#define _simd_f64x2_splitlo(X) _simd_f64x2_splitlo_(X)
	#define _simd_f64x2_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_splitlo_instruction_set>()
#else
	#define _simd_f64x2_splitlo(X) _simd_f64x2_splitlo_safe(X)
	#define _simd_f64x2_splitlo_enable() true
#endif

#define _simd_f64x4_splitlo_safe(X) reinterpret_cast<const _simd_f64x2*>(&X)[0]
#ifdef _simd_f64x4_splitlo_
	#define _simd_f64x4_splitlo(X) _simd_f64x4_splitlo_(X)
	#define _simd_f64x4_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_splitlo_instruction_set>()
#else
	#define _simd_f64x4_splitlo(X) _simd_f64x4_splitlo_safe(X)
	#define _simd_f64x4_splitlo_enable() true
#endif

#define _simd_f64x8_splitlo_safe(X) reinterpret_cast<const _simd_f64x4*>(&X)[0]
#ifdef _simd_f64x8_splitlo_
	#define _simd_f64x8_splitlo(X) _simd_f64x8_splitlo_(X)
	#define _simd_f64x8_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_splitlo_instruction_set>()
#else
	#define _simd_f64x8_splitlo(X) _simd_f64x8_splitlo_safe(X)
	#define _simd_f64x8_splitlo_enable() true
#endif

#define _simd_f64x16_splitlo_safe(X) reinterpret_cast<const _simd_f64x8*>(&X)[0]
#ifdef _simd_f64x16_splitlo_
	#define _simd_f64x16_splitlo(X) _simd_f64x16_splitlo_(X)
	#define _simd_f64x16_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_splitlo_instruction_set>()
#else
	#define _simd_f64x16_splitlo(X) _simd_f64x16_splitlo_safe(X)
	#define _simd_f64x16_splitlo_enable() true
#endif

#define _simd_f64x32_splitlo_safe(X) reinterpret_cast<const _simd_f64x16*>(&X)[0]
#ifdef _simd_f64x32_splitlo_
	#define _simd_f64x32_splitlo(X) _simd_f64x32_splitlo_(X)
	#define _simd_f64x32_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_splitlo_instruction_set>()
#else
	#define _simd_f64x32_splitlo(X) _simd_f64x32_splitlo_safe(X)
	#define _simd_f64x32_splitlo_enable() true
#endif

#define _simd_f64x64_splitlo_safe(X) reinterpret_cast<const _simd_f64x32*>(&X)[0]
#ifdef _simd_f64x64_splitlo_
	#define _simd_f64x64_splitlo(X) _simd_f64x64_splitlo_(X)
	#define _simd_f64x64_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_splitlo_instruction_set>()
#else
	#define _simd_f64x64_splitlo(X) _simd_f64x64_splitlo_safe(X)
	#define _simd_f64x64_splitlo_enable() true
#endif

#define _simd_f32x2_splitlo_safe(X) reinterpret_cast<const _simd_f32x1*>(&X)[0]
#ifdef _simd_f32x2_splitlo_
	#define _simd_f32x2_splitlo(X) _simd_f32x2_splitlo_(X)
	#define _simd_f32x2_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_splitlo_instruction_set>()
#else
	#define _simd_f32x2_splitlo(X) _simd_f32x2_splitlo_safe(X)
	#define _simd_f32x2_splitlo_enable() true
#endif

#define _simd_f32x4_splitlo_safe(X) reinterpret_cast<const _simd_f32x2*>(&X)[0]
#ifdef _simd_f32x4_splitlo_
	#define _simd_f32x4_splitlo(X) _simd_f32x4_splitlo_(X)
	#define _simd_f32x4_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_splitlo_instruction_set>()
#else
	#define _simd_f32x4_splitlo(X) _simd_f32x4_splitlo_safe(X)
	#define _simd_f32x4_splitlo_enable() true
#endif

#define _simd_f32x8_splitlo_safe(X) reinterpret_cast<const _simd_f32x4*>(&X)[0]
#ifdef _simd_f32x8_splitlo_
	#define _simd_f32x8_splitlo(X) _simd_f32x8_splitlo_(X)
	#define _simd_f32x8_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_splitlo_instruction_set>()
#else
	#define _simd_f32x8_splitlo(X) _simd_f32x8_splitlo_safe(X)
	#define _simd_f32x8_splitlo_enable() true
#endif

#define _simd_f32x16_splitlo_safe(X) reinterpret_cast<const _simd_f32x8*>(&X)[0]
#ifdef _simd_f32x16_splitlo_
	#define _simd_f32x16_splitlo(X) _simd_f32x16_splitlo_(X)
	#define _simd_f32x16_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_splitlo_instruction_set>()
#else
	#define _simd_f32x16_splitlo(X) _simd_f32x16_splitlo_safe(X)
	#define _simd_f32x16_splitlo_enable() true
#endif

#define _simd_f32x32_splitlo_safe(X) reinterpret_cast<const _simd_f32x16*>(&X)[0]
#ifdef _simd_f32x32_splitlo_
	#define _simd_f32x32_splitlo(X) _simd_f32x32_splitlo_(X)
	#define _simd_f32x32_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_splitlo_instruction_set>()
#else
	#define _simd_f32x32_splitlo(X) _simd_f32x32_splitlo_safe(X)
	#define _simd_f32x32_splitlo_enable() true
#endif

#define _simd_f32x64_splitlo_safe(X) reinterpret_cast<const _simd_f32x32*>(&X)[0]
#ifdef _simd_f32x64_splitlo_
	#define _simd_f32x64_splitlo(X) _simd_f32x64_splitlo_(X)
	#define _simd_f32x64_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_splitlo_instruction_set>()
#else
	#define _simd_f32x64_splitlo(X) _simd_f32x64_splitlo_safe(X)
	#define _simd_f32x64_splitlo_enable() true
#endif

#define _simd_s64x2_splitlo_safe(X) reinterpret_cast<const _simd_s64x1*>(&X)[0]
#ifdef _simd_s64x2_splitlo_
	#define _simd_s64x2_splitlo(X) _simd_s64x2_splitlo_(X)
	#define _simd_s64x2_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_splitlo_instruction_set>()
#else
	#define _simd_s64x2_splitlo(X) _simd_s64x2_splitlo_safe(X)
	#define _simd_s64x2_splitlo_enable() true
#endif

#define _simd_s64x4_splitlo_safe(X) reinterpret_cast<const _simd_s64x2*>(&X)[0]
#ifdef _simd_s64x4_splitlo_
	#define _simd_s64x4_splitlo(X) _simd_s64x4_splitlo_(X)
	#define _simd_s64x4_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_splitlo_instruction_set>()
#else
	#define _simd_s64x4_splitlo(X) _simd_s64x4_splitlo_safe(X)
	#define _simd_s64x4_splitlo_enable() true
#endif

#define _simd_s64x8_splitlo_safe(X) reinterpret_cast<const _simd_s64x4*>(&X)[0]
#ifdef _simd_s64x8_splitlo_
	#define _simd_s64x8_splitlo(X) _simd_s64x8_splitlo_(X)
	#define _simd_s64x8_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_splitlo_instruction_set>()
#else
	#define _simd_s64x8_splitlo(X) _simd_s64x8_splitlo_safe(X)
	#define _simd_s64x8_splitlo_enable() true
#endif

#define _simd_s64x16_splitlo_safe(X) reinterpret_cast<const _simd_s64x8*>(&X)[0]
#ifdef _simd_s64x16_splitlo_
	#define _simd_s64x16_splitlo(X) _simd_s64x16_splitlo_(X)
	#define _simd_s64x16_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_splitlo_instruction_set>()
#else
	#define _simd_s64x16_splitlo(X) _simd_s64x16_splitlo_safe(X)
	#define _simd_s64x16_splitlo_enable() true
#endif

#define _simd_s64x32_splitlo_safe(X) reinterpret_cast<const _simd_s64x16*>(&X)[0]
#ifdef _simd_s64x32_splitlo_
	#define _simd_s64x32_splitlo(X) _simd_s64x32_splitlo_(X)
	#define _simd_s64x32_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_splitlo_instruction_set>()
#else
	#define _simd_s64x32_splitlo(X) _simd_s64x32_splitlo_safe(X)
	#define _simd_s64x32_splitlo_enable() true
#endif

#define _simd_s64x64_splitlo_safe(X) reinterpret_cast<const _simd_s64x32*>(&X)[0]
#ifdef _simd_s64x64_splitlo_
	#define _simd_s64x64_splitlo(X) _simd_s64x64_splitlo_(X)
	#define _simd_s64x64_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_splitlo_instruction_set>()
#else
	#define _simd_s64x64_splitlo(X) _simd_s64x64_splitlo_safe(X)
	#define _simd_s64x64_splitlo_enable() true
#endif

#define _simd_u64x2_splitlo_safe(X) reinterpret_cast<const _simd_u64x1*>(&X)[0]
#ifdef _simd_u64x2_splitlo_
	#define _simd_u64x2_splitlo(X) _simd_u64x2_splitlo_(X)
	#define _simd_u64x2_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_splitlo_instruction_set>()
#else
	#define _simd_u64x2_splitlo(X) _simd_u64x2_splitlo_safe(X)
	#define _simd_u64x2_splitlo_enable() true
#endif

#define _simd_u64x4_splitlo_safe(X) reinterpret_cast<const _simd_u64x2*>(&X)[0]
#ifdef _simd_u64x4_splitlo_
	#define _simd_u64x4_splitlo(X) _simd_u64x4_splitlo_(X)
	#define _simd_u64x4_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_splitlo_instruction_set>()
#else
	#define _simd_u64x4_splitlo(X) _simd_u64x4_splitlo_safe(X)
	#define _simd_u64x4_splitlo_enable() true
#endif

#define _simd_u64x8_splitlo_safe(X) reinterpret_cast<const _simd_u64x4*>(&X)[0]
#ifdef _simd_u64x8_splitlo_
	#define _simd_u64x8_splitlo(X) _simd_u64x8_splitlo_(X)
	#define _simd_u64x8_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_splitlo_instruction_set>()
#else
	#define _simd_u64x8_splitlo(X) _simd_u64x8_splitlo_safe(X)
	#define _simd_u64x8_splitlo_enable() true
#endif

#define _simd_u64x16_splitlo_safe(X) reinterpret_cast<const _simd_u64x8*>(&X)[0]
#ifdef _simd_u64x16_splitlo_
	#define _simd_u64x16_splitlo(X) _simd_u64x16_splitlo_(X)
	#define _simd_u64x16_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_splitlo_instruction_set>()
#else
	#define _simd_u64x16_splitlo(X) _simd_u64x16_splitlo_safe(X)
	#define _simd_u64x16_splitlo_enable() true
#endif

#define _simd_u64x32_splitlo_safe(X) reinterpret_cast<const _simd_u64x16*>(&X)[0]
#ifdef _simd_u64x32_splitlo_
	#define _simd_u64x32_splitlo(X) _simd_u64x32_splitlo_(X)
	#define _simd_u64x32_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_splitlo_instruction_set>()
#else
	#define _simd_u64x32_splitlo(X) _simd_u64x32_splitlo_safe(X)
	#define _simd_u64x32_splitlo_enable() true
#endif

#define _simd_u64x64_splitlo_safe(X) reinterpret_cast<const _simd_u64x32*>(&X)[0]
#ifdef _simd_u64x64_splitlo_
	#define _simd_u64x64_splitlo(X) _simd_u64x64_splitlo_(X)
	#define _simd_u64x64_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_splitlo_instruction_set>()
#else
	#define _simd_u64x64_splitlo(X) _simd_u64x64_splitlo_safe(X)
	#define _simd_u64x64_splitlo_enable() true
#endif

#define _simd_s32x2_splitlo_safe(X) reinterpret_cast<const _simd_s32x1*>(&X)[0]
#ifdef _simd_s32x2_splitlo_
	#define _simd_s32x2_splitlo(X) _simd_s32x2_splitlo_(X)
	#define _simd_s32x2_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_splitlo_instruction_set>()
#else
	#define _simd_s32x2_splitlo(X) _simd_s32x2_splitlo_safe(X)
	#define _simd_s32x2_splitlo_enable() true
#endif

#define _simd_s32x4_splitlo_safe(X) reinterpret_cast<const _simd_s32x2*>(&X)[0]
#ifdef _simd_s32x4_splitlo_
	#define _simd_s32x4_splitlo(X) _simd_s32x4_splitlo_(X)
	#define _simd_s32x4_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_splitlo_instruction_set>()
#else
	#define _simd_s32x4_splitlo(X) _simd_s32x4_splitlo_safe(X)
	#define _simd_s32x4_splitlo_enable() true
#endif

#define _simd_s32x8_splitlo_safe(X) reinterpret_cast<const _simd_s32x4*>(&X)[0]
#ifdef _simd_s32x8_splitlo_
	#define _simd_s32x8_splitlo(X) _simd_s32x8_splitlo_(X)
	#define _simd_s32x8_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_splitlo_instruction_set>()
#else
	#define _simd_s32x8_splitlo(X) _simd_s32x8_splitlo_safe(X)
	#define _simd_s32x8_splitlo_enable() true
#endif

#define _simd_s32x16_splitlo_safe(X) reinterpret_cast<const _simd_s32x8*>(&X)[0]
#ifdef _simd_s32x16_splitlo_
	#define _simd_s32x16_splitlo(X) _simd_s32x16_splitlo_(X)
	#define _simd_s32x16_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_splitlo_instruction_set>()
#else
	#define _simd_s32x16_splitlo(X) _simd_s32x16_splitlo_safe(X)
	#define _simd_s32x16_splitlo_enable() true
#endif

#define _simd_s32x32_splitlo_safe(X) reinterpret_cast<const _simd_s32x16*>(&X)[0]
#ifdef _simd_s32x32_splitlo_
	#define _simd_s32x32_splitlo(X) _simd_s32x32_splitlo_(X)
	#define _simd_s32x32_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_splitlo_instruction_set>()
#else
	#define _simd_s32x32_splitlo(X) _simd_s32x32_splitlo_safe(X)
	#define _simd_s32x32_splitlo_enable() true
#endif

#define _simd_s32x64_splitlo_safe(X) reinterpret_cast<const _simd_s32x32*>(&X)[0]
#ifdef _simd_s32x64_splitlo_
	#define _simd_s32x64_splitlo(X) _simd_s32x64_splitlo_(X)
	#define _simd_s32x64_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_splitlo_instruction_set>()
#else
	#define _simd_s32x64_splitlo(X) _simd_s32x64_splitlo_safe(X)
	#define _simd_s32x64_splitlo_enable() true
#endif

#define _simd_u32x2_splitlo_safe(X) reinterpret_cast<const _simd_u32x1*>(&X)[0]
#ifdef _simd_u32x2_splitlo_
	#define _simd_u32x2_splitlo(X) _simd_u32x2_splitlo_(X)
	#define _simd_u32x2_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_splitlo_instruction_set>()
#else
	#define _simd_u32x2_splitlo(X) _simd_u32x2_splitlo_safe(X)
	#define _simd_u32x2_splitlo_enable() true
#endif

#define _simd_u32x4_splitlo_safe(X) reinterpret_cast<const _simd_u32x2*>(&X)[0]
#ifdef _simd_u32x4_splitlo_
	#define _simd_u32x4_splitlo(X) _simd_u32x4_splitlo_(X)
	#define _simd_u32x4_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_splitlo_instruction_set>()
#else
	#define _simd_u32x4_splitlo(X) _simd_u32x4_splitlo_safe(X)
	#define _simd_u32x4_splitlo_enable() true
#endif

#define _simd_u32x8_splitlo_safe(X) reinterpret_cast<const _simd_u32x4*>(&X)[0]
#ifdef _simd_u32x8_splitlo_
	#define _simd_u32x8_splitlo(X) _simd_u32x8_splitlo_(X)
	#define _simd_u32x8_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_splitlo_instruction_set>()
#else
	#define _simd_u32x8_splitlo(X) _simd_u32x8_splitlo_safe(X)
	#define _simd_u32x8_splitlo_enable() true
#endif

#define _simd_u32x16_splitlo_safe(X) reinterpret_cast<const _simd_u32x8*>(&X)[0]
#ifdef _simd_u32x16_splitlo_
	#define _simd_u32x16_splitlo(X) _simd_u32x16_splitlo_(X)
	#define _simd_u32x16_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_splitlo_instruction_set>()
#else
	#define _simd_u32x16_splitlo(X) _simd_u32x16_splitlo_safe(X)
	#define _simd_u32x16_splitlo_enable() true
#endif

#define _simd_u32x32_splitlo_safe(X) reinterpret_cast<const _simd_u32x16*>(&X)[0]
#ifdef _simd_u32x32_splitlo_
	#define _simd_u32x32_splitlo(X) _simd_u32x32_splitlo_(X)
	#define _simd_u32x32_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_splitlo_instruction_set>()
#else
	#define _simd_u32x32_splitlo(X) _simd_u32x32_splitlo_safe(X)
	#define _simd_u32x32_splitlo_enable() true
#endif

#define _simd_u32x64_splitlo_safe(X) reinterpret_cast<const _simd_u32x32*>(&X)[0]
#ifdef _simd_u32x64_splitlo_
	#define _simd_u32x64_splitlo(X) _simd_u32x64_splitlo_(X)
	#define _simd_u32x64_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_splitlo_instruction_set>()
#else
	#define _simd_u32x64_splitlo(X) _simd_u32x64_splitlo_safe(X)
	#define _simd_u32x64_splitlo_enable() true
#endif

#define _simd_s16x2_splitlo_safe(X) reinterpret_cast<const _simd_s16x1*>(&X)[0]
#ifdef _simd_s16x2_splitlo_
	#define _simd_s16x2_splitlo(X) _simd_s16x2_splitlo_(X)
	#define _simd_s16x2_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_splitlo_instruction_set>()
#else
	#define _simd_s16x2_splitlo(X) _simd_s16x2_splitlo_safe(X)
	#define _simd_s16x2_splitlo_enable() true
#endif

#define _simd_s16x4_splitlo_safe(X) reinterpret_cast<const _simd_s16x2*>(&X)[0]
#ifdef _simd_s16x4_splitlo_
	#define _simd_s16x4_splitlo(X) _simd_s16x4_splitlo_(X)
	#define _simd_s16x4_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_splitlo_instruction_set>()
#else
	#define _simd_s16x4_splitlo(X) _simd_s16x4_splitlo_safe(X)
	#define _simd_s16x4_splitlo_enable() true
#endif

#define _simd_s16x8_splitlo_safe(X) reinterpret_cast<const _simd_s16x4*>(&X)[0]
#ifdef _simd_s16x8_splitlo_
	#define _simd_s16x8_splitlo(X) _simd_s16x8_splitlo_(X)
	#define _simd_s16x8_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_splitlo_instruction_set>()
#else
	#define _simd_s16x8_splitlo(X) _simd_s16x8_splitlo_safe(X)
	#define _simd_s16x8_splitlo_enable() true
#endif

#define _simd_s16x16_splitlo_safe(X) reinterpret_cast<const _simd_s16x8*>(&X)[0]
#ifdef _simd_s16x16_splitlo_
	#define _simd_s16x16_splitlo(X) _simd_s16x16_splitlo_(X)
	#define _simd_s16x16_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_splitlo_instruction_set>()
#else
	#define _simd_s16x16_splitlo(X) _simd_s16x16_splitlo_safe(X)
	#define _simd_s16x16_splitlo_enable() true
#endif

#define _simd_s16x32_splitlo_safe(X) reinterpret_cast<const _simd_s16x16*>(&X)[0]
#ifdef _simd_s16x32_splitlo_
	#define _simd_s16x32_splitlo(X) _simd_s16x32_splitlo_(X)
	#define _simd_s16x32_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_splitlo_instruction_set>()
#else
	#define _simd_s16x32_splitlo(X) _simd_s16x32_splitlo_safe(X)
	#define _simd_s16x32_splitlo_enable() true
#endif

#define _simd_s16x64_splitlo_safe(X) reinterpret_cast<const _simd_s16x32*>(&X)[0]
#ifdef _simd_s16x64_splitlo_
	#define _simd_s16x64_splitlo(X) _simd_s16x64_splitlo_(X)
	#define _simd_s16x64_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_splitlo_instruction_set>()
#else
	#define _simd_s16x64_splitlo(X) _simd_s16x64_splitlo_safe(X)
	#define _simd_s16x64_splitlo_enable() true
#endif

#define _simd_u16x2_splitlo_safe(X) reinterpret_cast<const _simd_u16x1*>(&X)[0]
#ifdef _simd_u16x2_splitlo_
	#define _simd_u16x2_splitlo(X) _simd_u16x2_splitlo_(X)
	#define _simd_u16x2_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_splitlo_instruction_set>()
#else
	#define _simd_u16x2_splitlo(X) _simd_u16x2_splitlo_safe(X)
	#define _simd_u16x2_splitlo_enable() true
#endif

#define _simd_u16x4_splitlo_safe(X) reinterpret_cast<const _simd_u16x2*>(&X)[0]
#ifdef _simd_u16x4_splitlo_
	#define _simd_u16x4_splitlo(X) _simd_u16x4_splitlo_(X)
	#define _simd_u16x4_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_splitlo_instruction_set>()
#else
	#define _simd_u16x4_splitlo(X) _simd_u16x4_splitlo_safe(X)
	#define _simd_u16x4_splitlo_enable() true
#endif

#define _simd_u16x8_splitlo_safe(X) reinterpret_cast<const _simd_u16x4*>(&X)[0]
#ifdef _simd_u16x8_splitlo_
	#define _simd_u16x8_splitlo(X) _simd_u16x8_splitlo_(X)
	#define _simd_u16x8_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_splitlo_instruction_set>()
#else
	#define _simd_u16x8_splitlo(X) _simd_u16x8_splitlo_safe(X)
	#define _simd_u16x8_splitlo_enable() true
#endif

#define _simd_u16x16_splitlo_safe(X) reinterpret_cast<const _simd_u16x8*>(&X)[0]
#ifdef _simd_u16x16_splitlo_
	#define _simd_u16x16_splitlo(X) _simd_u16x16_splitlo_(X)
	#define _simd_u16x16_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_splitlo_instruction_set>()
#else
	#define _simd_u16x16_splitlo(X) _simd_u16x16_splitlo_safe(X)
	#define _simd_u16x16_splitlo_enable() true
#endif

#define _simd_u16x32_splitlo_safe(X) reinterpret_cast<const _simd_u16x16*>(&X)[0]
#ifdef _simd_u16x32_splitlo_
	#define _simd_u16x32_splitlo(X) _simd_u16x32_splitlo_(X)
	#define _simd_u16x32_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_splitlo_instruction_set>()
#else
	#define _simd_u16x32_splitlo(X) _simd_u16x32_splitlo_safe(X)
	#define _simd_u16x32_splitlo_enable() true
#endif

#define _simd_u16x64_splitlo_safe(X) reinterpret_cast<const _simd_u16x32*>(&X)[0]
#ifdef _simd_u16x64_splitlo_
	#define _simd_u16x64_splitlo(X) _simd_u16x64_splitlo_(X)
	#define _simd_u16x64_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_splitlo_instruction_set>()
#else
	#define _simd_u16x64_splitlo(X) _simd_u16x64_splitlo_safe(X)
	#define _simd_u16x64_splitlo_enable() true
#endif

#define _simd_s8x2_splitlo_safe(X) reinterpret_cast<const _simd_s8x1*>(&X)[0]
#ifdef _simd_s8x2_splitlo_
	#define _simd_s8x2_splitlo(X) _simd_s8x2_splitlo_(X)
	#define _simd_s8x2_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_splitlo_instruction_set>()
#else
	#define _simd_s8x2_splitlo(X) _simd_s8x2_splitlo_safe(X)
	#define _simd_s8x2_splitlo_enable() true
#endif

#define _simd_s8x4_splitlo_safe(X) reinterpret_cast<const _simd_s8x2*>(&X)[0]
#ifdef _simd_s8x4_splitlo_
	#define _simd_s8x4_splitlo(X) _simd_s8x4_splitlo_(X)
	#define _simd_s8x4_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_splitlo_instruction_set>()
#else
	#define _simd_s8x4_splitlo(X) _simd_s8x4_splitlo_safe(X)
	#define _simd_s8x4_splitlo_enable() true
#endif

#define _simd_s8x8_splitlo_safe(X) reinterpret_cast<const _simd_s8x4*>(&X)[0]
#ifdef _simd_s8x8_splitlo_
	#define _simd_s8x8_splitlo(X) _simd_s8x8_splitlo_(X)
	#define _simd_s8x8_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_splitlo_instruction_set>()
#else
	#define _simd_s8x8_splitlo(X) _simd_s8x8_splitlo_safe(X)
	#define _simd_s8x8_splitlo_enable() true
#endif

#define _simd_s8x16_splitlo_safe(X) reinterpret_cast<const _simd_s8x8*>(&X)[0]
#ifdef _simd_s8x16_splitlo_
	#define _simd_s8x16_splitlo(X) _simd_s8x16_splitlo_(X)
	#define _simd_s8x16_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_splitlo_instruction_set>()
#else
	#define _simd_s8x16_splitlo(X) _simd_s8x16_splitlo_safe(X)
	#define _simd_s8x16_splitlo_enable() true
#endif

#define _simd_s8x32_splitlo_safe(X) reinterpret_cast<const _simd_s8x16*>(&X)[0]
#ifdef _simd_s8x32_splitlo_
	#define _simd_s8x32_splitlo(X) _simd_s8x32_splitlo_(X)
	#define _simd_s8x32_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_splitlo_instruction_set>()
#else
	#define _simd_s8x32_splitlo(X) _simd_s8x32_splitlo_safe(X)
	#define _simd_s8x32_splitlo_enable() true
#endif

#define _simd_s8x64_splitlo_safe(X) reinterpret_cast<const _simd_s8x32*>(&X)[0]
#ifdef _simd_s8x64_splitlo_
	#define _simd_s8x64_splitlo(X) _simd_s8x64_splitlo_(X)
	#define _simd_s8x64_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_splitlo_instruction_set>()
#else
	#define _simd_s8x64_splitlo(X) _simd_s8x64_splitlo_safe(X)
	#define _simd_s8x64_splitlo_enable() true
#endif

#define _simd_u8x2_splitlo_safe(X) reinterpret_cast<const _simd_u8x1*>(&X)[0]
#ifdef _simd_u8x2_splitlo_
	#define _simd_u8x2_splitlo(X) _simd_u8x2_splitlo_(X)
	#define _simd_u8x2_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_splitlo_instruction_set>()
#else
	#define _simd_u8x2_splitlo(X) _simd_u8x2_splitlo_safe(X)
	#define _simd_u8x2_splitlo_enable() true
#endif

#define _simd_u8x4_splitlo_safe(X) reinterpret_cast<const _simd_u8x2*>(&X)[0]
#ifdef _simd_u8x4_splitlo_
	#define _simd_u8x4_splitlo(X) _simd_u8x4_splitlo_(X)
	#define _simd_u8x4_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_splitlo_instruction_set>()
#else
	#define _simd_u8x4_splitlo(X) _simd_u8x4_splitlo_safe(X)
	#define _simd_u8x4_splitlo_enable() true
#endif

#define _simd_u8x8_splitlo_safe(X) reinterpret_cast<const _simd_u8x4*>(&X)[0]
#ifdef _simd_u8x8_splitlo_
	#define _simd_u8x8_splitlo(X) _simd_u8x8_splitlo_(X)
	#define _simd_u8x8_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_splitlo_instruction_set>()
#else
	#define _simd_u8x8_splitlo(X) _simd_u8x8_splitlo_safe(X)
	#define _simd_u8x8_splitlo_enable() true
#endif

#define _simd_u8x16_splitlo_safe(X) reinterpret_cast<const _simd_u8x8*>(&X)[0]
#ifdef _simd_u8x16_splitlo_
	#define _simd_u8x16_splitlo(X) _simd_u8x16_splitlo_(X)
	#define _simd_u8x16_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_splitlo_instruction_set>()
#else
	#define _simd_u8x16_splitlo(X) _simd_u8x16_splitlo_safe(X)
	#define _simd_u8x16_splitlo_enable() true
#endif

#define _simd_u8x32_splitlo_safe(X) reinterpret_cast<const _simd_u8x16*>(&X)[0]
#ifdef _simd_u8x32_splitlo_
	#define _simd_u8x32_splitlo(X) _simd_u8x32_splitlo_(X)
	#define _simd_u8x32_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_splitlo_instruction_set>()
#else
	#define _simd_u8x32_splitlo(X) _simd_u8x32_splitlo_safe(X)
	#define _simd_u8x32_splitlo_enable() true
#endif

#define _simd_u8x64_splitlo_safe(X) reinterpret_cast<const _simd_u8x32*>(&X)[0]
#ifdef _simd_u8x64_splitlo_
	#define _simd_u8x64_splitlo(X) _simd_u8x64_splitlo_(X)
	#define _simd_u8x64_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_splitlo_instruction_set>()
#else
	#define _simd_u8x64_splitlo(X) _simd_u8x64_splitlo_safe(X)
	#define _simd_u8x64_splitlo_enable() true
#endif

