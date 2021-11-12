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

#define _simd_f64x2_fill_undefined_safe() _simd_f64x2()
#ifdef _simd_f64x2_fill_undefined_
	#define _simd_f64x2_fill_undefined() _simd_f64x2_fill_undefined_()
	#define _simd_f64x2_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_fill_undefined_instruction_set>()
#elif defined(_simd_f64x1_fill_undefined_)
	#define _simd_f64x2_fill_undefined_() _simd_f64x2_combine(_simd_f64x1_fill_undefined_(), _simd_f64x1_fill_undefined_())
	#define _simd_f64x2_fill_undefined() _simd_f64x2_fill_undefined_()
	#define _simd_f64x2_fill_undefined_enable() (_simd_f64x1_fill_undefined_enable() && _simd_f64x2_combine_enable())
#else
	#define _simd_f64x2_fill_undefined() _simd_f64x2_fill_undefined_safe()
	#define _simd_f64x2_fill_undefined_enable() true
#endif

#define _simd_f64x4_fill_undefined_safe() _simd_f64x4()
#ifdef _simd_f64x4_fill_undefined_
	#define _simd_f64x4_fill_undefined() _simd_f64x4_fill_undefined_()
	#define _simd_f64x4_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_fill_undefined_instruction_set>()
#elif defined(_simd_f64x2_fill_undefined_)
	#define _simd_f64x4_fill_undefined_() _simd_f64x4_combine(_simd_f64x2_fill_undefined_(), _simd_f64x2_fill_undefined_())
	#define _simd_f64x4_fill_undefined() _simd_f64x4_fill_undefined_()
	#define _simd_f64x4_fill_undefined_enable() (_simd_f64x2_fill_undefined_enable() && _simd_f64x4_combine_enable())
#else
	#define _simd_f64x4_fill_undefined() _simd_f64x4_fill_undefined_safe()
	#define _simd_f64x4_fill_undefined_enable() true
#endif

#define _simd_f64x8_fill_undefined_safe() _simd_f64x8()
#ifdef _simd_f64x8_fill_undefined_
	#define _simd_f64x8_fill_undefined() _simd_f64x8_fill_undefined_()
	#define _simd_f64x8_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_fill_undefined_instruction_set>()
#elif defined(_simd_f64x4_fill_undefined_)
	#define _simd_f64x8_fill_undefined_() _simd_f64x8_combine(_simd_f64x4_fill_undefined_(), _simd_f64x4_fill_undefined_())
	#define _simd_f64x8_fill_undefined() _simd_f64x8_fill_undefined_()
	#define _simd_f64x8_fill_undefined_enable() (_simd_f64x4_fill_undefined_enable() && _simd_f64x8_combine_enable())
#else
	#define _simd_f64x8_fill_undefined() _simd_f64x8_fill_undefined_safe()
	#define _simd_f64x8_fill_undefined_enable() true
#endif

#define _simd_f64x16_fill_undefined_safe() _simd_f64x16()
#ifdef _simd_f64x16_fill_undefined_
	#define _simd_f64x16_fill_undefined() _simd_f64x16_fill_undefined_()
	#define _simd_f64x16_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_fill_undefined_instruction_set>()
#elif defined(_simd_f64x8_fill_undefined_)
	#define _simd_f64x16_fill_undefined_() _simd_f64x16_combine(_simd_f64x8_fill_undefined_(), _simd_f64x8_fill_undefined_())
	#define _simd_f64x16_fill_undefined() _simd_f64x16_fill_undefined_()
	#define _simd_f64x16_fill_undefined_enable() (_simd_f64x8_fill_undefined_enable() && _simd_f64x16_combine_enable())
#else
	#define _simd_f64x16_fill_undefined() _simd_f64x16_fill_undefined_safe()
	#define _simd_f64x16_fill_undefined_enable() true
#endif

#define _simd_f64x32_fill_undefined_safe() _simd_f64x32()
#ifdef _simd_f64x32_fill_undefined_
	#define _simd_f64x32_fill_undefined() _simd_f64x32_fill_undefined_()
	#define _simd_f64x32_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_fill_undefined_instruction_set>()
#elif defined(_simd_f64x16_fill_undefined_)
	#define _simd_f64x32_fill_undefined_() _simd_f64x32_combine(_simd_f64x16_fill_undefined_(), _simd_f64x16_fill_undefined_())
	#define _simd_f64x32_fill_undefined() _simd_f64x32_fill_undefined_()
	#define _simd_f64x32_fill_undefined_enable() (_simd_f64x16_fill_undefined_enable() && _simd_f64x32_combine_enable())
#else
	#define _simd_f64x32_fill_undefined() _simd_f64x32_fill_undefined_safe()
	#define _simd_f64x32_fill_undefined_enable() true
#endif

#define _simd_f64x64_fill_undefined_safe() _simd_f64x64()
#ifdef _simd_f64x64_fill_undefined_
	#define _simd_f64x64_fill_undefined() _simd_f64x64_fill_undefined_()
	#define _simd_f64x64_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_fill_undefined_instruction_set>()
#elif defined(_simd_f64x32_fill_undefined_)
	#define _simd_f64x64_fill_undefined_() _simd_f64x64_combine(_simd_f64x32_fill_undefined_(), _simd_f64x32_fill_undefined_())
	#define _simd_f64x64_fill_undefined() _simd_f64x64_fill_undefined_()
	#define _simd_f64x64_fill_undefined_enable() (_simd_f64x32_fill_undefined_enable() && _simd_f64x64_combine_enable())
#else
	#define _simd_f64x64_fill_undefined() _simd_f64x64_fill_undefined_safe()
	#define _simd_f64x64_fill_undefined_enable() true
#endif

#define _simd_f32x2_fill_undefined_safe() _simd_f32x2()
#ifdef _simd_f32x2_fill_undefined_
	#define _simd_f32x2_fill_undefined() _simd_f32x2_fill_undefined_()
	#define _simd_f32x2_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_fill_undefined_instruction_set>()
#elif defined(_simd_f32x1_fill_undefined_)
	#define _simd_f32x2_fill_undefined_() _simd_f32x2_combine(_simd_f32x1_fill_undefined_(), _simd_f32x1_fill_undefined_())
	#define _simd_f32x2_fill_undefined() _simd_f32x2_fill_undefined_()
	#define _simd_f32x2_fill_undefined_enable() (_simd_f32x1_fill_undefined_enable() && _simd_f32x2_combine_enable())
#else
	#define _simd_f32x2_fill_undefined() _simd_f32x2_fill_undefined_safe()
	#define _simd_f32x2_fill_undefined_enable() true
#endif

#define _simd_f32x4_fill_undefined_safe() _simd_f32x4()
#ifdef _simd_f32x4_fill_undefined_
	#define _simd_f32x4_fill_undefined() _simd_f32x4_fill_undefined_()
	#define _simd_f32x4_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_fill_undefined_instruction_set>()
#elif defined(_simd_f32x2_fill_undefined_)
	#define _simd_f32x4_fill_undefined_() _simd_f32x4_combine(_simd_f32x2_fill_undefined_(), _simd_f32x2_fill_undefined_())
	#define _simd_f32x4_fill_undefined() _simd_f32x4_fill_undefined_()
	#define _simd_f32x4_fill_undefined_enable() (_simd_f32x2_fill_undefined_enable() && _simd_f32x4_combine_enable())
#else
	#define _simd_f32x4_fill_undefined() _simd_f32x4_fill_undefined_safe()
	#define _simd_f32x4_fill_undefined_enable() true
#endif

#define _simd_f32x8_fill_undefined_safe() _simd_f32x8()
#ifdef _simd_f32x8_fill_undefined_
	#define _simd_f32x8_fill_undefined() _simd_f32x8_fill_undefined_()
	#define _simd_f32x8_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_fill_undefined_instruction_set>()
#elif defined(_simd_f32x4_fill_undefined_)
	#define _simd_f32x8_fill_undefined_() _simd_f32x8_combine(_simd_f32x4_fill_undefined_(), _simd_f32x4_fill_undefined_())
	#define _simd_f32x8_fill_undefined() _simd_f32x8_fill_undefined_()
	#define _simd_f32x8_fill_undefined_enable() (_simd_f32x4_fill_undefined_enable() && _simd_f32x8_combine_enable())
#else
	#define _simd_f32x8_fill_undefined() _simd_f32x8_fill_undefined_safe()
	#define _simd_f32x8_fill_undefined_enable() true
#endif

#define _simd_f32x16_fill_undefined_safe() _simd_f32x16()
#ifdef _simd_f32x16_fill_undefined_
	#define _simd_f32x16_fill_undefined() _simd_f32x16_fill_undefined_()
	#define _simd_f32x16_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_fill_undefined_instruction_set>()
#elif defined(_simd_f32x8_fill_undefined_)
	#define _simd_f32x16_fill_undefined_() _simd_f32x16_combine(_simd_f32x8_fill_undefined_(), _simd_f32x8_fill_undefined_())
	#define _simd_f32x16_fill_undefined() _simd_f32x16_fill_undefined_()
	#define _simd_f32x16_fill_undefined_enable() (_simd_f32x8_fill_undefined_enable() && _simd_f32x16_combine_enable())
#else
	#define _simd_f32x16_fill_undefined() _simd_f32x16_fill_undefined_safe()
	#define _simd_f32x16_fill_undefined_enable() true
#endif

#define _simd_f32x32_fill_undefined_safe() _simd_f32x32()
#ifdef _simd_f32x32_fill_undefined_
	#define _simd_f32x32_fill_undefined() _simd_f32x32_fill_undefined_()
	#define _simd_f32x32_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_fill_undefined_instruction_set>()
#elif defined(_simd_f32x16_fill_undefined_)
	#define _simd_f32x32_fill_undefined_() _simd_f32x32_combine(_simd_f32x16_fill_undefined_(), _simd_f32x16_fill_undefined_())
	#define _simd_f32x32_fill_undefined() _simd_f32x32_fill_undefined_()
	#define _simd_f32x32_fill_undefined_enable() (_simd_f32x16_fill_undefined_enable() && _simd_f32x32_combine_enable())
#else
	#define _simd_f32x32_fill_undefined() _simd_f32x32_fill_undefined_safe()
	#define _simd_f32x32_fill_undefined_enable() true
#endif

#define _simd_f32x64_fill_undefined_safe() _simd_f32x64()
#ifdef _simd_f32x64_fill_undefined_
	#define _simd_f32x64_fill_undefined() _simd_f32x64_fill_undefined_()
	#define _simd_f32x64_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_fill_undefined_instruction_set>()
#elif defined(_simd_f32x32_fill_undefined_)
	#define _simd_f32x64_fill_undefined_() _simd_f32x64_combine(_simd_f32x32_fill_undefined_(), _simd_f32x32_fill_undefined_())
	#define _simd_f32x64_fill_undefined() _simd_f32x64_fill_undefined_()
	#define _simd_f32x64_fill_undefined_enable() (_simd_f32x32_fill_undefined_enable() && _simd_f32x64_combine_enable())
#else
	#define _simd_f32x64_fill_undefined() _simd_f32x64_fill_undefined_safe()
	#define _simd_f32x64_fill_undefined_enable() true
#endif

#define _simd_s64x2_fill_undefined_safe() _simd_s64x2()
#ifdef _simd_s64x2_fill_undefined_
	#define _simd_s64x2_fill_undefined() _simd_s64x2_fill_undefined_()
	#define _simd_s64x2_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_fill_undefined_instruction_set>()
#elif defined(_simd_s64x1_fill_undefined_)
	#define _simd_s64x2_fill_undefined_() _simd_s64x2_combine(_simd_s64x1_fill_undefined_(), _simd_s64x1_fill_undefined_())
	#define _simd_s64x2_fill_undefined() _simd_s64x2_fill_undefined_()
	#define _simd_s64x2_fill_undefined_enable() (_simd_s64x1_fill_undefined_enable() && _simd_s64x2_combine_enable())
#else
	#define _simd_s64x2_fill_undefined() _simd_s64x2_fill_undefined_safe()
	#define _simd_s64x2_fill_undefined_enable() true
#endif

#define _simd_s64x4_fill_undefined_safe() _simd_s64x4()
#ifdef _simd_s64x4_fill_undefined_
	#define _simd_s64x4_fill_undefined() _simd_s64x4_fill_undefined_()
	#define _simd_s64x4_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_fill_undefined_instruction_set>()
#elif defined(_simd_s64x2_fill_undefined_)
	#define _simd_s64x4_fill_undefined_() _simd_s64x4_combine(_simd_s64x2_fill_undefined_(), _simd_s64x2_fill_undefined_())
	#define _simd_s64x4_fill_undefined() _simd_s64x4_fill_undefined_()
	#define _simd_s64x4_fill_undefined_enable() (_simd_s64x2_fill_undefined_enable() && _simd_s64x4_combine_enable())
#else
	#define _simd_s64x4_fill_undefined() _simd_s64x4_fill_undefined_safe()
	#define _simd_s64x4_fill_undefined_enable() true
#endif

#define _simd_s64x8_fill_undefined_safe() _simd_s64x8()
#ifdef _simd_s64x8_fill_undefined_
	#define _simd_s64x8_fill_undefined() _simd_s64x8_fill_undefined_()
	#define _simd_s64x8_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_fill_undefined_instruction_set>()
#elif defined(_simd_s64x4_fill_undefined_)
	#define _simd_s64x8_fill_undefined_() _simd_s64x8_combine(_simd_s64x4_fill_undefined_(), _simd_s64x4_fill_undefined_())
	#define _simd_s64x8_fill_undefined() _simd_s64x8_fill_undefined_()
	#define _simd_s64x8_fill_undefined_enable() (_simd_s64x4_fill_undefined_enable() && _simd_s64x8_combine_enable())
#else
	#define _simd_s64x8_fill_undefined() _simd_s64x8_fill_undefined_safe()
	#define _simd_s64x8_fill_undefined_enable() true
#endif

#define _simd_s64x16_fill_undefined_safe() _simd_s64x16()
#ifdef _simd_s64x16_fill_undefined_
	#define _simd_s64x16_fill_undefined() _simd_s64x16_fill_undefined_()
	#define _simd_s64x16_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_fill_undefined_instruction_set>()
#elif defined(_simd_s64x8_fill_undefined_)
	#define _simd_s64x16_fill_undefined_() _simd_s64x16_combine(_simd_s64x8_fill_undefined_(), _simd_s64x8_fill_undefined_())
	#define _simd_s64x16_fill_undefined() _simd_s64x16_fill_undefined_()
	#define _simd_s64x16_fill_undefined_enable() (_simd_s64x8_fill_undefined_enable() && _simd_s64x16_combine_enable())
#else
	#define _simd_s64x16_fill_undefined() _simd_s64x16_fill_undefined_safe()
	#define _simd_s64x16_fill_undefined_enable() true
#endif

#define _simd_s64x32_fill_undefined_safe() _simd_s64x32()
#ifdef _simd_s64x32_fill_undefined_
	#define _simd_s64x32_fill_undefined() _simd_s64x32_fill_undefined_()
	#define _simd_s64x32_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_fill_undefined_instruction_set>()
#elif defined(_simd_s64x16_fill_undefined_)
	#define _simd_s64x32_fill_undefined_() _simd_s64x32_combine(_simd_s64x16_fill_undefined_(), _simd_s64x16_fill_undefined_())
	#define _simd_s64x32_fill_undefined() _simd_s64x32_fill_undefined_()
	#define _simd_s64x32_fill_undefined_enable() (_simd_s64x16_fill_undefined_enable() && _simd_s64x32_combine_enable())
#else
	#define _simd_s64x32_fill_undefined() _simd_s64x32_fill_undefined_safe()
	#define _simd_s64x32_fill_undefined_enable() true
#endif

#define _simd_s64x64_fill_undefined_safe() _simd_s64x64()
#ifdef _simd_s64x64_fill_undefined_
	#define _simd_s64x64_fill_undefined() _simd_s64x64_fill_undefined_()
	#define _simd_s64x64_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_fill_undefined_instruction_set>()
#elif defined(_simd_s64x32_fill_undefined_)
	#define _simd_s64x64_fill_undefined_() _simd_s64x64_combine(_simd_s64x32_fill_undefined_(), _simd_s64x32_fill_undefined_())
	#define _simd_s64x64_fill_undefined() _simd_s64x64_fill_undefined_()
	#define _simd_s64x64_fill_undefined_enable() (_simd_s64x32_fill_undefined_enable() && _simd_s64x64_combine_enable())
#else
	#define _simd_s64x64_fill_undefined() _simd_s64x64_fill_undefined_safe()
	#define _simd_s64x64_fill_undefined_enable() true
#endif

#define _simd_u64x2_fill_undefined_safe() _simd_u64x2()
#ifdef _simd_u64x2_fill_undefined_
	#define _simd_u64x2_fill_undefined() _simd_u64x2_fill_undefined_()
	#define _simd_u64x2_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_fill_undefined_instruction_set>()
#elif defined(_simd_u64x1_fill_undefined_)
	#define _simd_u64x2_fill_undefined_() _simd_u64x2_combine(_simd_u64x1_fill_undefined_(), _simd_u64x1_fill_undefined_())
	#define _simd_u64x2_fill_undefined() _simd_u64x2_fill_undefined_()
	#define _simd_u64x2_fill_undefined_enable() (_simd_u64x1_fill_undefined_enable() && _simd_u64x2_combine_enable())
#else
	#define _simd_u64x2_fill_undefined() _simd_u64x2_fill_undefined_safe()
	#define _simd_u64x2_fill_undefined_enable() true
#endif

#define _simd_u64x4_fill_undefined_safe() _simd_u64x4()
#ifdef _simd_u64x4_fill_undefined_
	#define _simd_u64x4_fill_undefined() _simd_u64x4_fill_undefined_()
	#define _simd_u64x4_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_fill_undefined_instruction_set>()
#elif defined(_simd_u64x2_fill_undefined_)
	#define _simd_u64x4_fill_undefined_() _simd_u64x4_combine(_simd_u64x2_fill_undefined_(), _simd_u64x2_fill_undefined_())
	#define _simd_u64x4_fill_undefined() _simd_u64x4_fill_undefined_()
	#define _simd_u64x4_fill_undefined_enable() (_simd_u64x2_fill_undefined_enable() && _simd_u64x4_combine_enable())
#else
	#define _simd_u64x4_fill_undefined() _simd_u64x4_fill_undefined_safe()
	#define _simd_u64x4_fill_undefined_enable() true
#endif

#define _simd_u64x8_fill_undefined_safe() _simd_u64x8()
#ifdef _simd_u64x8_fill_undefined_
	#define _simd_u64x8_fill_undefined() _simd_u64x8_fill_undefined_()
	#define _simd_u64x8_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_fill_undefined_instruction_set>()
#elif defined(_simd_u64x4_fill_undefined_)
	#define _simd_u64x8_fill_undefined_() _simd_u64x8_combine(_simd_u64x4_fill_undefined_(), _simd_u64x4_fill_undefined_())
	#define _simd_u64x8_fill_undefined() _simd_u64x8_fill_undefined_()
	#define _simd_u64x8_fill_undefined_enable() (_simd_u64x4_fill_undefined_enable() && _simd_u64x8_combine_enable())
#else
	#define _simd_u64x8_fill_undefined() _simd_u64x8_fill_undefined_safe()
	#define _simd_u64x8_fill_undefined_enable() true
#endif

#define _simd_u64x16_fill_undefined_safe() _simd_u64x16()
#ifdef _simd_u64x16_fill_undefined_
	#define _simd_u64x16_fill_undefined() _simd_u64x16_fill_undefined_()
	#define _simd_u64x16_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_fill_undefined_instruction_set>()
#elif defined(_simd_u64x8_fill_undefined_)
	#define _simd_u64x16_fill_undefined_() _simd_u64x16_combine(_simd_u64x8_fill_undefined_(), _simd_u64x8_fill_undefined_())
	#define _simd_u64x16_fill_undefined() _simd_u64x16_fill_undefined_()
	#define _simd_u64x16_fill_undefined_enable() (_simd_u64x8_fill_undefined_enable() && _simd_u64x16_combine_enable())
#else
	#define _simd_u64x16_fill_undefined() _simd_u64x16_fill_undefined_safe()
	#define _simd_u64x16_fill_undefined_enable() true
#endif

#define _simd_u64x32_fill_undefined_safe() _simd_u64x32()
#ifdef _simd_u64x32_fill_undefined_
	#define _simd_u64x32_fill_undefined() _simd_u64x32_fill_undefined_()
	#define _simd_u64x32_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_fill_undefined_instruction_set>()
#elif defined(_simd_u64x16_fill_undefined_)
	#define _simd_u64x32_fill_undefined_() _simd_u64x32_combine(_simd_u64x16_fill_undefined_(), _simd_u64x16_fill_undefined_())
	#define _simd_u64x32_fill_undefined() _simd_u64x32_fill_undefined_()
	#define _simd_u64x32_fill_undefined_enable() (_simd_u64x16_fill_undefined_enable() && _simd_u64x32_combine_enable())
#else
	#define _simd_u64x32_fill_undefined() _simd_u64x32_fill_undefined_safe()
	#define _simd_u64x32_fill_undefined_enable() true
#endif

#define _simd_u64x64_fill_undefined_safe() _simd_u64x64()
#ifdef _simd_u64x64_fill_undefined_
	#define _simd_u64x64_fill_undefined() _simd_u64x64_fill_undefined_()
	#define _simd_u64x64_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_fill_undefined_instruction_set>()
#elif defined(_simd_u64x32_fill_undefined_)
	#define _simd_u64x64_fill_undefined_() _simd_u64x64_combine(_simd_u64x32_fill_undefined_(), _simd_u64x32_fill_undefined_())
	#define _simd_u64x64_fill_undefined() _simd_u64x64_fill_undefined_()
	#define _simd_u64x64_fill_undefined_enable() (_simd_u64x32_fill_undefined_enable() && _simd_u64x64_combine_enable())
#else
	#define _simd_u64x64_fill_undefined() _simd_u64x64_fill_undefined_safe()
	#define _simd_u64x64_fill_undefined_enable() true
#endif

#define _simd_s32x2_fill_undefined_safe() _simd_s32x2()
#ifdef _simd_s32x2_fill_undefined_
	#define _simd_s32x2_fill_undefined() _simd_s32x2_fill_undefined_()
	#define _simd_s32x2_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_fill_undefined_instruction_set>()
#elif defined(_simd_s32x1_fill_undefined_)
	#define _simd_s32x2_fill_undefined_() _simd_s32x2_combine(_simd_s32x1_fill_undefined_(), _simd_s32x1_fill_undefined_())
	#define _simd_s32x2_fill_undefined() _simd_s32x2_fill_undefined_()
	#define _simd_s32x2_fill_undefined_enable() (_simd_s32x1_fill_undefined_enable() && _simd_s32x2_combine_enable())
#else
	#define _simd_s32x2_fill_undefined() _simd_s32x2_fill_undefined_safe()
	#define _simd_s32x2_fill_undefined_enable() true
#endif

#define _simd_s32x4_fill_undefined_safe() _simd_s32x4()
#ifdef _simd_s32x4_fill_undefined_
	#define _simd_s32x4_fill_undefined() _simd_s32x4_fill_undefined_()
	#define _simd_s32x4_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_fill_undefined_instruction_set>()
#elif defined(_simd_s32x2_fill_undefined_)
	#define _simd_s32x4_fill_undefined_() _simd_s32x4_combine(_simd_s32x2_fill_undefined_(), _simd_s32x2_fill_undefined_())
	#define _simd_s32x4_fill_undefined() _simd_s32x4_fill_undefined_()
	#define _simd_s32x4_fill_undefined_enable() (_simd_s32x2_fill_undefined_enable() && _simd_s32x4_combine_enable())
#else
	#define _simd_s32x4_fill_undefined() _simd_s32x4_fill_undefined_safe()
	#define _simd_s32x4_fill_undefined_enable() true
#endif

#define _simd_s32x8_fill_undefined_safe() _simd_s32x8()
#ifdef _simd_s32x8_fill_undefined_
	#define _simd_s32x8_fill_undefined() _simd_s32x8_fill_undefined_()
	#define _simd_s32x8_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_fill_undefined_instruction_set>()
#elif defined(_simd_s32x4_fill_undefined_)
	#define _simd_s32x8_fill_undefined_() _simd_s32x8_combine(_simd_s32x4_fill_undefined_(), _simd_s32x4_fill_undefined_())
	#define _simd_s32x8_fill_undefined() _simd_s32x8_fill_undefined_()
	#define _simd_s32x8_fill_undefined_enable() (_simd_s32x4_fill_undefined_enable() && _simd_s32x8_combine_enable())
#else
	#define _simd_s32x8_fill_undefined() _simd_s32x8_fill_undefined_safe()
	#define _simd_s32x8_fill_undefined_enable() true
#endif

#define _simd_s32x16_fill_undefined_safe() _simd_s32x16()
#ifdef _simd_s32x16_fill_undefined_
	#define _simd_s32x16_fill_undefined() _simd_s32x16_fill_undefined_()
	#define _simd_s32x16_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_fill_undefined_instruction_set>()
#elif defined(_simd_s32x8_fill_undefined_)
	#define _simd_s32x16_fill_undefined_() _simd_s32x16_combine(_simd_s32x8_fill_undefined_(), _simd_s32x8_fill_undefined_())
	#define _simd_s32x16_fill_undefined() _simd_s32x16_fill_undefined_()
	#define _simd_s32x16_fill_undefined_enable() (_simd_s32x8_fill_undefined_enable() && _simd_s32x16_combine_enable())
#else
	#define _simd_s32x16_fill_undefined() _simd_s32x16_fill_undefined_safe()
	#define _simd_s32x16_fill_undefined_enable() true
#endif

#define _simd_s32x32_fill_undefined_safe() _simd_s32x32()
#ifdef _simd_s32x32_fill_undefined_
	#define _simd_s32x32_fill_undefined() _simd_s32x32_fill_undefined_()
	#define _simd_s32x32_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_fill_undefined_instruction_set>()
#elif defined(_simd_s32x16_fill_undefined_)
	#define _simd_s32x32_fill_undefined_() _simd_s32x32_combine(_simd_s32x16_fill_undefined_(), _simd_s32x16_fill_undefined_())
	#define _simd_s32x32_fill_undefined() _simd_s32x32_fill_undefined_()
	#define _simd_s32x32_fill_undefined_enable() (_simd_s32x16_fill_undefined_enable() && _simd_s32x32_combine_enable())
#else
	#define _simd_s32x32_fill_undefined() _simd_s32x32_fill_undefined_safe()
	#define _simd_s32x32_fill_undefined_enable() true
#endif

#define _simd_s32x64_fill_undefined_safe() _simd_s32x64()
#ifdef _simd_s32x64_fill_undefined_
	#define _simd_s32x64_fill_undefined() _simd_s32x64_fill_undefined_()
	#define _simd_s32x64_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_fill_undefined_instruction_set>()
#elif defined(_simd_s32x32_fill_undefined_)
	#define _simd_s32x64_fill_undefined_() _simd_s32x64_combine(_simd_s32x32_fill_undefined_(), _simd_s32x32_fill_undefined_())
	#define _simd_s32x64_fill_undefined() _simd_s32x64_fill_undefined_()
	#define _simd_s32x64_fill_undefined_enable() (_simd_s32x32_fill_undefined_enable() && _simd_s32x64_combine_enable())
#else
	#define _simd_s32x64_fill_undefined() _simd_s32x64_fill_undefined_safe()
	#define _simd_s32x64_fill_undefined_enable() true
#endif

#define _simd_u32x2_fill_undefined_safe() _simd_u32x2()
#ifdef _simd_u32x2_fill_undefined_
	#define _simd_u32x2_fill_undefined() _simd_u32x2_fill_undefined_()
	#define _simd_u32x2_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_fill_undefined_instruction_set>()
#elif defined(_simd_u32x1_fill_undefined_)
	#define _simd_u32x2_fill_undefined_() _simd_u32x2_combine(_simd_u32x1_fill_undefined_(), _simd_u32x1_fill_undefined_())
	#define _simd_u32x2_fill_undefined() _simd_u32x2_fill_undefined_()
	#define _simd_u32x2_fill_undefined_enable() (_simd_u32x1_fill_undefined_enable() && _simd_u32x2_combine_enable())
#else
	#define _simd_u32x2_fill_undefined() _simd_u32x2_fill_undefined_safe()
	#define _simd_u32x2_fill_undefined_enable() true
#endif

#define _simd_u32x4_fill_undefined_safe() _simd_u32x4()
#ifdef _simd_u32x4_fill_undefined_
	#define _simd_u32x4_fill_undefined() _simd_u32x4_fill_undefined_()
	#define _simd_u32x4_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_fill_undefined_instruction_set>()
#elif defined(_simd_u32x2_fill_undefined_)
	#define _simd_u32x4_fill_undefined_() _simd_u32x4_combine(_simd_u32x2_fill_undefined_(), _simd_u32x2_fill_undefined_())
	#define _simd_u32x4_fill_undefined() _simd_u32x4_fill_undefined_()
	#define _simd_u32x4_fill_undefined_enable() (_simd_u32x2_fill_undefined_enable() && _simd_u32x4_combine_enable())
#else
	#define _simd_u32x4_fill_undefined() _simd_u32x4_fill_undefined_safe()
	#define _simd_u32x4_fill_undefined_enable() true
#endif

#define _simd_u32x8_fill_undefined_safe() _simd_u32x8()
#ifdef _simd_u32x8_fill_undefined_
	#define _simd_u32x8_fill_undefined() _simd_u32x8_fill_undefined_()
	#define _simd_u32x8_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_fill_undefined_instruction_set>()
#elif defined(_simd_u32x4_fill_undefined_)
	#define _simd_u32x8_fill_undefined_() _simd_u32x8_combine(_simd_u32x4_fill_undefined_(), _simd_u32x4_fill_undefined_())
	#define _simd_u32x8_fill_undefined() _simd_u32x8_fill_undefined_()
	#define _simd_u32x8_fill_undefined_enable() (_simd_u32x4_fill_undefined_enable() && _simd_u32x8_combine_enable())
#else
	#define _simd_u32x8_fill_undefined() _simd_u32x8_fill_undefined_safe()
	#define _simd_u32x8_fill_undefined_enable() true
#endif

#define _simd_u32x16_fill_undefined_safe() _simd_u32x16()
#ifdef _simd_u32x16_fill_undefined_
	#define _simd_u32x16_fill_undefined() _simd_u32x16_fill_undefined_()
	#define _simd_u32x16_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_fill_undefined_instruction_set>()
#elif defined(_simd_u32x8_fill_undefined_)
	#define _simd_u32x16_fill_undefined_() _simd_u32x16_combine(_simd_u32x8_fill_undefined_(), _simd_u32x8_fill_undefined_())
	#define _simd_u32x16_fill_undefined() _simd_u32x16_fill_undefined_()
	#define _simd_u32x16_fill_undefined_enable() (_simd_u32x8_fill_undefined_enable() && _simd_u32x16_combine_enable())
#else
	#define _simd_u32x16_fill_undefined() _simd_u32x16_fill_undefined_safe()
	#define _simd_u32x16_fill_undefined_enable() true
#endif

#define _simd_u32x32_fill_undefined_safe() _simd_u32x32()
#ifdef _simd_u32x32_fill_undefined_
	#define _simd_u32x32_fill_undefined() _simd_u32x32_fill_undefined_()
	#define _simd_u32x32_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_fill_undefined_instruction_set>()
#elif defined(_simd_u32x16_fill_undefined_)
	#define _simd_u32x32_fill_undefined_() _simd_u32x32_combine(_simd_u32x16_fill_undefined_(), _simd_u32x16_fill_undefined_())
	#define _simd_u32x32_fill_undefined() _simd_u32x32_fill_undefined_()
	#define _simd_u32x32_fill_undefined_enable() (_simd_u32x16_fill_undefined_enable() && _simd_u32x32_combine_enable())
#else
	#define _simd_u32x32_fill_undefined() _simd_u32x32_fill_undefined_safe()
	#define _simd_u32x32_fill_undefined_enable() true
#endif

#define _simd_u32x64_fill_undefined_safe() _simd_u32x64()
#ifdef _simd_u32x64_fill_undefined_
	#define _simd_u32x64_fill_undefined() _simd_u32x64_fill_undefined_()
	#define _simd_u32x64_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_fill_undefined_instruction_set>()
#elif defined(_simd_u32x32_fill_undefined_)
	#define _simd_u32x64_fill_undefined_() _simd_u32x64_combine(_simd_u32x32_fill_undefined_(), _simd_u32x32_fill_undefined_())
	#define _simd_u32x64_fill_undefined() _simd_u32x64_fill_undefined_()
	#define _simd_u32x64_fill_undefined_enable() (_simd_u32x32_fill_undefined_enable() && _simd_u32x64_combine_enable())
#else
	#define _simd_u32x64_fill_undefined() _simd_u32x64_fill_undefined_safe()
	#define _simd_u32x64_fill_undefined_enable() true
#endif

#define _simd_s16x2_fill_undefined_safe() _simd_s16x2()
#ifdef _simd_s16x2_fill_undefined_
	#define _simd_s16x2_fill_undefined() _simd_s16x2_fill_undefined_()
	#define _simd_s16x2_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_fill_undefined_instruction_set>()
#elif defined(_simd_s16x1_fill_undefined_)
	#define _simd_s16x2_fill_undefined_() _simd_s16x2_combine(_simd_s16x1_fill_undefined_(), _simd_s16x1_fill_undefined_())
	#define _simd_s16x2_fill_undefined() _simd_s16x2_fill_undefined_()
	#define _simd_s16x2_fill_undefined_enable() (_simd_s16x1_fill_undefined_enable() && _simd_s16x2_combine_enable())
#else
	#define _simd_s16x2_fill_undefined() _simd_s16x2_fill_undefined_safe()
	#define _simd_s16x2_fill_undefined_enable() true
#endif

#define _simd_s16x4_fill_undefined_safe() _simd_s16x4()
#ifdef _simd_s16x4_fill_undefined_
	#define _simd_s16x4_fill_undefined() _simd_s16x4_fill_undefined_()
	#define _simd_s16x4_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_fill_undefined_instruction_set>()
#elif defined(_simd_s16x2_fill_undefined_)
	#define _simd_s16x4_fill_undefined_() _simd_s16x4_combine(_simd_s16x2_fill_undefined_(), _simd_s16x2_fill_undefined_())
	#define _simd_s16x4_fill_undefined() _simd_s16x4_fill_undefined_()
	#define _simd_s16x4_fill_undefined_enable() (_simd_s16x2_fill_undefined_enable() && _simd_s16x4_combine_enable())
#else
	#define _simd_s16x4_fill_undefined() _simd_s16x4_fill_undefined_safe()
	#define _simd_s16x4_fill_undefined_enable() true
#endif

#define _simd_s16x8_fill_undefined_safe() _simd_s16x8()
#ifdef _simd_s16x8_fill_undefined_
	#define _simd_s16x8_fill_undefined() _simd_s16x8_fill_undefined_()
	#define _simd_s16x8_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_fill_undefined_instruction_set>()
#elif defined(_simd_s16x4_fill_undefined_)
	#define _simd_s16x8_fill_undefined_() _simd_s16x8_combine(_simd_s16x4_fill_undefined_(), _simd_s16x4_fill_undefined_())
	#define _simd_s16x8_fill_undefined() _simd_s16x8_fill_undefined_()
	#define _simd_s16x8_fill_undefined_enable() (_simd_s16x4_fill_undefined_enable() && _simd_s16x8_combine_enable())
#else
	#define _simd_s16x8_fill_undefined() _simd_s16x8_fill_undefined_safe()
	#define _simd_s16x8_fill_undefined_enable() true
#endif

#define _simd_s16x16_fill_undefined_safe() _simd_s16x16()
#ifdef _simd_s16x16_fill_undefined_
	#define _simd_s16x16_fill_undefined() _simd_s16x16_fill_undefined_()
	#define _simd_s16x16_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_fill_undefined_instruction_set>()
#elif defined(_simd_s16x8_fill_undefined_)
	#define _simd_s16x16_fill_undefined_() _simd_s16x16_combine(_simd_s16x8_fill_undefined_(), _simd_s16x8_fill_undefined_())
	#define _simd_s16x16_fill_undefined() _simd_s16x16_fill_undefined_()
	#define _simd_s16x16_fill_undefined_enable() (_simd_s16x8_fill_undefined_enable() && _simd_s16x16_combine_enable())
#else
	#define _simd_s16x16_fill_undefined() _simd_s16x16_fill_undefined_safe()
	#define _simd_s16x16_fill_undefined_enable() true
#endif

#define _simd_s16x32_fill_undefined_safe() _simd_s16x32()
#ifdef _simd_s16x32_fill_undefined_
	#define _simd_s16x32_fill_undefined() _simd_s16x32_fill_undefined_()
	#define _simd_s16x32_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_fill_undefined_instruction_set>()
#elif defined(_simd_s16x16_fill_undefined_)
	#define _simd_s16x32_fill_undefined_() _simd_s16x32_combine(_simd_s16x16_fill_undefined_(), _simd_s16x16_fill_undefined_())
	#define _simd_s16x32_fill_undefined() _simd_s16x32_fill_undefined_()
	#define _simd_s16x32_fill_undefined_enable() (_simd_s16x16_fill_undefined_enable() && _simd_s16x32_combine_enable())
#else
	#define _simd_s16x32_fill_undefined() _simd_s16x32_fill_undefined_safe()
	#define _simd_s16x32_fill_undefined_enable() true
#endif

#define _simd_s16x64_fill_undefined_safe() _simd_s16x64()
#ifdef _simd_s16x64_fill_undefined_
	#define _simd_s16x64_fill_undefined() _simd_s16x64_fill_undefined_()
	#define _simd_s16x64_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_fill_undefined_instruction_set>()
#elif defined(_simd_s16x32_fill_undefined_)
	#define _simd_s16x64_fill_undefined_() _simd_s16x64_combine(_simd_s16x32_fill_undefined_(), _simd_s16x32_fill_undefined_())
	#define _simd_s16x64_fill_undefined() _simd_s16x64_fill_undefined_()
	#define _simd_s16x64_fill_undefined_enable() (_simd_s16x32_fill_undefined_enable() && _simd_s16x64_combine_enable())
#else
	#define _simd_s16x64_fill_undefined() _simd_s16x64_fill_undefined_safe()
	#define _simd_s16x64_fill_undefined_enable() true
#endif

#define _simd_u16x2_fill_undefined_safe() _simd_u16x2()
#ifdef _simd_u16x2_fill_undefined_
	#define _simd_u16x2_fill_undefined() _simd_u16x2_fill_undefined_()
	#define _simd_u16x2_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_fill_undefined_instruction_set>()
#elif defined(_simd_u16x1_fill_undefined_)
	#define _simd_u16x2_fill_undefined_() _simd_u16x2_combine(_simd_u16x1_fill_undefined_(), _simd_u16x1_fill_undefined_())
	#define _simd_u16x2_fill_undefined() _simd_u16x2_fill_undefined_()
	#define _simd_u16x2_fill_undefined_enable() (_simd_u16x1_fill_undefined_enable() && _simd_u16x2_combine_enable())
#else
	#define _simd_u16x2_fill_undefined() _simd_u16x2_fill_undefined_safe()
	#define _simd_u16x2_fill_undefined_enable() true
#endif

#define _simd_u16x4_fill_undefined_safe() _simd_u16x4()
#ifdef _simd_u16x4_fill_undefined_
	#define _simd_u16x4_fill_undefined() _simd_u16x4_fill_undefined_()
	#define _simd_u16x4_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_fill_undefined_instruction_set>()
#elif defined(_simd_u16x2_fill_undefined_)
	#define _simd_u16x4_fill_undefined_() _simd_u16x4_combine(_simd_u16x2_fill_undefined_(), _simd_u16x2_fill_undefined_())
	#define _simd_u16x4_fill_undefined() _simd_u16x4_fill_undefined_()
	#define _simd_u16x4_fill_undefined_enable() (_simd_u16x2_fill_undefined_enable() && _simd_u16x4_combine_enable())
#else
	#define _simd_u16x4_fill_undefined() _simd_u16x4_fill_undefined_safe()
	#define _simd_u16x4_fill_undefined_enable() true
#endif

#define _simd_u16x8_fill_undefined_safe() _simd_u16x8()
#ifdef _simd_u16x8_fill_undefined_
	#define _simd_u16x8_fill_undefined() _simd_u16x8_fill_undefined_()
	#define _simd_u16x8_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_fill_undefined_instruction_set>()
#elif defined(_simd_u16x4_fill_undefined_)
	#define _simd_u16x8_fill_undefined_() _simd_u16x8_combine(_simd_u16x4_fill_undefined_(), _simd_u16x4_fill_undefined_())
	#define _simd_u16x8_fill_undefined() _simd_u16x8_fill_undefined_()
	#define _simd_u16x8_fill_undefined_enable() (_simd_u16x4_fill_undefined_enable() && _simd_u16x8_combine_enable())
#else
	#define _simd_u16x8_fill_undefined() _simd_u16x8_fill_undefined_safe()
	#define _simd_u16x8_fill_undefined_enable() true
#endif

#define _simd_u16x16_fill_undefined_safe() _simd_u16x16()
#ifdef _simd_u16x16_fill_undefined_
	#define _simd_u16x16_fill_undefined() _simd_u16x16_fill_undefined_()
	#define _simd_u16x16_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_fill_undefined_instruction_set>()
#elif defined(_simd_u16x8_fill_undefined_)
	#define _simd_u16x16_fill_undefined_() _simd_u16x16_combine(_simd_u16x8_fill_undefined_(), _simd_u16x8_fill_undefined_())
	#define _simd_u16x16_fill_undefined() _simd_u16x16_fill_undefined_()
	#define _simd_u16x16_fill_undefined_enable() (_simd_u16x8_fill_undefined_enable() && _simd_u16x16_combine_enable())
#else
	#define _simd_u16x16_fill_undefined() _simd_u16x16_fill_undefined_safe()
	#define _simd_u16x16_fill_undefined_enable() true
#endif

#define _simd_u16x32_fill_undefined_safe() _simd_u16x32()
#ifdef _simd_u16x32_fill_undefined_
	#define _simd_u16x32_fill_undefined() _simd_u16x32_fill_undefined_()
	#define _simd_u16x32_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_fill_undefined_instruction_set>()
#elif defined(_simd_u16x16_fill_undefined_)
	#define _simd_u16x32_fill_undefined_() _simd_u16x32_combine(_simd_u16x16_fill_undefined_(), _simd_u16x16_fill_undefined_())
	#define _simd_u16x32_fill_undefined() _simd_u16x32_fill_undefined_()
	#define _simd_u16x32_fill_undefined_enable() (_simd_u16x16_fill_undefined_enable() && _simd_u16x32_combine_enable())
#else
	#define _simd_u16x32_fill_undefined() _simd_u16x32_fill_undefined_safe()
	#define _simd_u16x32_fill_undefined_enable() true
#endif

#define _simd_u16x64_fill_undefined_safe() _simd_u16x64()
#ifdef _simd_u16x64_fill_undefined_
	#define _simd_u16x64_fill_undefined() _simd_u16x64_fill_undefined_()
	#define _simd_u16x64_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_fill_undefined_instruction_set>()
#elif defined(_simd_u16x32_fill_undefined_)
	#define _simd_u16x64_fill_undefined_() _simd_u16x64_combine(_simd_u16x32_fill_undefined_(), _simd_u16x32_fill_undefined_())
	#define _simd_u16x64_fill_undefined() _simd_u16x64_fill_undefined_()
	#define _simd_u16x64_fill_undefined_enable() (_simd_u16x32_fill_undefined_enable() && _simd_u16x64_combine_enable())
#else
	#define _simd_u16x64_fill_undefined() _simd_u16x64_fill_undefined_safe()
	#define _simd_u16x64_fill_undefined_enable() true
#endif

#define _simd_s8x2_fill_undefined_safe() _simd_s8x2()
#ifdef _simd_s8x2_fill_undefined_
	#define _simd_s8x2_fill_undefined() _simd_s8x2_fill_undefined_()
	#define _simd_s8x2_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_fill_undefined_instruction_set>()
#elif defined(_simd_s8x1_fill_undefined_)
	#define _simd_s8x2_fill_undefined_() _simd_s8x2_combine(_simd_s8x1_fill_undefined_(), _simd_s8x1_fill_undefined_())
	#define _simd_s8x2_fill_undefined() _simd_s8x2_fill_undefined_()
	#define _simd_s8x2_fill_undefined_enable() (_simd_s8x1_fill_undefined_enable() && _simd_s8x2_combine_enable())
#else
	#define _simd_s8x2_fill_undefined() _simd_s8x2_fill_undefined_safe()
	#define _simd_s8x2_fill_undefined_enable() true
#endif

#define _simd_s8x4_fill_undefined_safe() _simd_s8x4()
#ifdef _simd_s8x4_fill_undefined_
	#define _simd_s8x4_fill_undefined() _simd_s8x4_fill_undefined_()
	#define _simd_s8x4_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_fill_undefined_instruction_set>()
#elif defined(_simd_s8x2_fill_undefined_)
	#define _simd_s8x4_fill_undefined_() _simd_s8x4_combine(_simd_s8x2_fill_undefined_(), _simd_s8x2_fill_undefined_())
	#define _simd_s8x4_fill_undefined() _simd_s8x4_fill_undefined_()
	#define _simd_s8x4_fill_undefined_enable() (_simd_s8x2_fill_undefined_enable() && _simd_s8x4_combine_enable())
#else
	#define _simd_s8x4_fill_undefined() _simd_s8x4_fill_undefined_safe()
	#define _simd_s8x4_fill_undefined_enable() true
#endif

#define _simd_s8x8_fill_undefined_safe() _simd_s8x8()
#ifdef _simd_s8x8_fill_undefined_
	#define _simd_s8x8_fill_undefined() _simd_s8x8_fill_undefined_()
	#define _simd_s8x8_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_fill_undefined_instruction_set>()
#elif defined(_simd_s8x4_fill_undefined_)
	#define _simd_s8x8_fill_undefined_() _simd_s8x8_combine(_simd_s8x4_fill_undefined_(), _simd_s8x4_fill_undefined_())
	#define _simd_s8x8_fill_undefined() _simd_s8x8_fill_undefined_()
	#define _simd_s8x8_fill_undefined_enable() (_simd_s8x4_fill_undefined_enable() && _simd_s8x8_combine_enable())
#else
	#define _simd_s8x8_fill_undefined() _simd_s8x8_fill_undefined_safe()
	#define _simd_s8x8_fill_undefined_enable() true
#endif

#define _simd_s8x16_fill_undefined_safe() _simd_s8x16()
#ifdef _simd_s8x16_fill_undefined_
	#define _simd_s8x16_fill_undefined() _simd_s8x16_fill_undefined_()
	#define _simd_s8x16_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_fill_undefined_instruction_set>()
#elif defined(_simd_s8x8_fill_undefined_)
	#define _simd_s8x16_fill_undefined_() _simd_s8x16_combine(_simd_s8x8_fill_undefined_(), _simd_s8x8_fill_undefined_())
	#define _simd_s8x16_fill_undefined() _simd_s8x16_fill_undefined_()
	#define _simd_s8x16_fill_undefined_enable() (_simd_s8x8_fill_undefined_enable() && _simd_s8x16_combine_enable())
#else
	#define _simd_s8x16_fill_undefined() _simd_s8x16_fill_undefined_safe()
	#define _simd_s8x16_fill_undefined_enable() true
#endif

#define _simd_s8x32_fill_undefined_safe() _simd_s8x32()
#ifdef _simd_s8x32_fill_undefined_
	#define _simd_s8x32_fill_undefined() _simd_s8x32_fill_undefined_()
	#define _simd_s8x32_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_fill_undefined_instruction_set>()
#elif defined(_simd_s8x16_fill_undefined_)
	#define _simd_s8x32_fill_undefined_() _simd_s8x32_combine(_simd_s8x16_fill_undefined_(), _simd_s8x16_fill_undefined_())
	#define _simd_s8x32_fill_undefined() _simd_s8x32_fill_undefined_()
	#define _simd_s8x32_fill_undefined_enable() (_simd_s8x16_fill_undefined_enable() && _simd_s8x32_combine_enable())
#else
	#define _simd_s8x32_fill_undefined() _simd_s8x32_fill_undefined_safe()
	#define _simd_s8x32_fill_undefined_enable() true
#endif

#define _simd_s8x64_fill_undefined_safe() _simd_s8x64()
#ifdef _simd_s8x64_fill_undefined_
	#define _simd_s8x64_fill_undefined() _simd_s8x64_fill_undefined_()
	#define _simd_s8x64_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_fill_undefined_instruction_set>()
#elif defined(_simd_s8x32_fill_undefined_)
	#define _simd_s8x64_fill_undefined_() _simd_s8x64_combine(_simd_s8x32_fill_undefined_(), _simd_s8x32_fill_undefined_())
	#define _simd_s8x64_fill_undefined() _simd_s8x64_fill_undefined_()
	#define _simd_s8x64_fill_undefined_enable() (_simd_s8x32_fill_undefined_enable() && _simd_s8x64_combine_enable())
#else
	#define _simd_s8x64_fill_undefined() _simd_s8x64_fill_undefined_safe()
	#define _simd_s8x64_fill_undefined_enable() true
#endif

#define _simd_u8x2_fill_undefined_safe() _simd_u8x2()
#ifdef _simd_u8x2_fill_undefined_
	#define _simd_u8x2_fill_undefined() _simd_u8x2_fill_undefined_()
	#define _simd_u8x2_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_fill_undefined_instruction_set>()
#elif defined(_simd_u8x1_fill_undefined_)
	#define _simd_u8x2_fill_undefined_() _simd_u8x2_combine(_simd_u8x1_fill_undefined_(), _simd_u8x1_fill_undefined_())
	#define _simd_u8x2_fill_undefined() _simd_u8x2_fill_undefined_()
	#define _simd_u8x2_fill_undefined_enable() (_simd_u8x1_fill_undefined_enable() && _simd_u8x2_combine_enable())
#else
	#define _simd_u8x2_fill_undefined() _simd_u8x2_fill_undefined_safe()
	#define _simd_u8x2_fill_undefined_enable() true
#endif

#define _simd_u8x4_fill_undefined_safe() _simd_u8x4()
#ifdef _simd_u8x4_fill_undefined_
	#define _simd_u8x4_fill_undefined() _simd_u8x4_fill_undefined_()
	#define _simd_u8x4_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_fill_undefined_instruction_set>()
#elif defined(_simd_u8x2_fill_undefined_)
	#define _simd_u8x4_fill_undefined_() _simd_u8x4_combine(_simd_u8x2_fill_undefined_(), _simd_u8x2_fill_undefined_())
	#define _simd_u8x4_fill_undefined() _simd_u8x4_fill_undefined_()
	#define _simd_u8x4_fill_undefined_enable() (_simd_u8x2_fill_undefined_enable() && _simd_u8x4_combine_enable())
#else
	#define _simd_u8x4_fill_undefined() _simd_u8x4_fill_undefined_safe()
	#define _simd_u8x4_fill_undefined_enable() true
#endif

#define _simd_u8x8_fill_undefined_safe() _simd_u8x8()
#ifdef _simd_u8x8_fill_undefined_
	#define _simd_u8x8_fill_undefined() _simd_u8x8_fill_undefined_()
	#define _simd_u8x8_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_fill_undefined_instruction_set>()
#elif defined(_simd_u8x4_fill_undefined_)
	#define _simd_u8x8_fill_undefined_() _simd_u8x8_combine(_simd_u8x4_fill_undefined_(), _simd_u8x4_fill_undefined_())
	#define _simd_u8x8_fill_undefined() _simd_u8x8_fill_undefined_()
	#define _simd_u8x8_fill_undefined_enable() (_simd_u8x4_fill_undefined_enable() && _simd_u8x8_combine_enable())
#else
	#define _simd_u8x8_fill_undefined() _simd_u8x8_fill_undefined_safe()
	#define _simd_u8x8_fill_undefined_enable() true
#endif

#define _simd_u8x16_fill_undefined_safe() _simd_u8x16()
#ifdef _simd_u8x16_fill_undefined_
	#define _simd_u8x16_fill_undefined() _simd_u8x16_fill_undefined_()
	#define _simd_u8x16_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_fill_undefined_instruction_set>()
#elif defined(_simd_u8x8_fill_undefined_)
	#define _simd_u8x16_fill_undefined_() _simd_u8x16_combine(_simd_u8x8_fill_undefined_(), _simd_u8x8_fill_undefined_())
	#define _simd_u8x16_fill_undefined() _simd_u8x16_fill_undefined_()
	#define _simd_u8x16_fill_undefined_enable() (_simd_u8x8_fill_undefined_enable() && _simd_u8x16_combine_enable())
#else
	#define _simd_u8x16_fill_undefined() _simd_u8x16_fill_undefined_safe()
	#define _simd_u8x16_fill_undefined_enable() true
#endif

#define _simd_u8x32_fill_undefined_safe() _simd_u8x32()
#ifdef _simd_u8x32_fill_undefined_
	#define _simd_u8x32_fill_undefined() _simd_u8x32_fill_undefined_()
	#define _simd_u8x32_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_fill_undefined_instruction_set>()
#elif defined(_simd_u8x16_fill_undefined_)
	#define _simd_u8x32_fill_undefined_() _simd_u8x32_combine(_simd_u8x16_fill_undefined_(), _simd_u8x16_fill_undefined_())
	#define _simd_u8x32_fill_undefined() _simd_u8x32_fill_undefined_()
	#define _simd_u8x32_fill_undefined_enable() (_simd_u8x16_fill_undefined_enable() && _simd_u8x32_combine_enable())
#else
	#define _simd_u8x32_fill_undefined() _simd_u8x32_fill_undefined_safe()
	#define _simd_u8x32_fill_undefined_enable() true
#endif

#define _simd_u8x64_fill_undefined_safe() _simd_u8x64()
#ifdef _simd_u8x64_fill_undefined_
	#define _simd_u8x64_fill_undefined() _simd_u8x64_fill_undefined_()
	#define _simd_u8x64_fill_undefined_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_fill_undefined_instruction_set>()
#elif defined(_simd_u8x32_fill_undefined_)
	#define _simd_u8x64_fill_undefined_() _simd_u8x64_combine(_simd_u8x32_fill_undefined_(), _simd_u8x32_fill_undefined_())
	#define _simd_u8x64_fill_undefined() _simd_u8x64_fill_undefined_()
	#define _simd_u8x64_fill_undefined_enable() (_simd_u8x32_fill_undefined_enable() && _simd_u8x64_combine_enable())
#else
	#define _simd_u8x64_fill_undefined() _simd_u8x64_fill_undefined_safe()
	#define _simd_u8x64_fill_undefined_enable() true
#endif

