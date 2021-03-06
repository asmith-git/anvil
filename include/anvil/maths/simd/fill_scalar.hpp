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

#ifdef _simd_f64x2_splitlo_
	#define _simd_f64x2_splitlo(X) _simd_f64x2_splitlo_(X)
	#define _simd_f64x2_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_splitlo_instruction_set>()
#else
	#define _simd_f64x2_splitlo(X) _simd_f64x2_splitlo_safe(X)
	#define _simd_f64x2_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_fill_scalar_safe(_simd_f64x1 s) {
	_simd_f64x2 tmp;
	for(int i = 0; i < 2; ++i) reinterpret_cast<_simd_f64x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_f64x2_fill_scalar_
	#define _simd_f64x2_fill_scalar(X) _simd_f64x2_fill_scalar_(X)
	#define _simd_f64x2_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_fill_scalar_instruction_set>()
#elif defined(_simd_f64x1_fill_scalar_)
	#define _simd_f64x2_fill_scalar_(X) _simd_f64x2_combine(_simd_f64x1_fill_scalar_(X), _simd_f64x1_fill_scalar_(X))
	#define _simd_f64x2_fill_scalar(X) _simd_f64x2_fill_scalar_(X)
	#define _simd_f64x2_fill_scalar_enable() (_simd_f64x1_fill_scalar_enable() && _simd_f64x2_combine_enable())
#else
	#define _simd_f64x2_fill_scalar(X) _simd_f64x2_fill_scalar_safe(X)
	#define _simd_f64x2_fill_scalar_enable() true
#endif

#ifdef _simd_f64x4_splitlo_
	#define _simd_f64x4_splitlo(X) _simd_f64x4_splitlo_(X)
	#define _simd_f64x4_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_splitlo_instruction_set>()
#else
	#define _simd_f64x4_splitlo(X) _simd_f64x4_splitlo_safe(X)
	#define _simd_f64x4_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_fill_scalar_safe(_simd_f64x1 s) {
	_simd_f64x4 tmp;
	for(int i = 0; i < 4; ++i) reinterpret_cast<_simd_f64x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_f64x4_fill_scalar_
	#define _simd_f64x4_fill_scalar(X) _simd_f64x4_fill_scalar_(X)
	#define _simd_f64x4_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_fill_scalar_instruction_set>()
#elif defined(_simd_f64x2_fill_scalar_)
	#define _simd_f64x4_fill_scalar_(X) _simd_f64x4_combine(_simd_f64x2_fill_scalar_(X), _simd_f64x2_fill_scalar_(X))
	#define _simd_f64x4_fill_scalar(X) _simd_f64x4_fill_scalar_(X)
	#define _simd_f64x4_fill_scalar_enable() (_simd_f64x2_fill_scalar_enable() && _simd_f64x4_combine_enable())
#else
	#define _simd_f64x4_fill_scalar(X) _simd_f64x4_fill_scalar_safe(X)
	#define _simd_f64x4_fill_scalar_enable() true
#endif

#ifdef _simd_f64x8_splitlo_
	#define _simd_f64x8_splitlo(X) _simd_f64x8_splitlo_(X)
	#define _simd_f64x8_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_splitlo_instruction_set>()
#else
	#define _simd_f64x8_splitlo(X) _simd_f64x8_splitlo_safe(X)
	#define _simd_f64x8_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_f64x8 ANVIL_SIMD_CALL _simd_f64x8_fill_scalar_safe(_simd_f64x1 s) {
	_simd_f64x8 tmp;
	for(int i = 0; i < 8; ++i) reinterpret_cast<_simd_f64x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_f64x8_fill_scalar_
	#define _simd_f64x8_fill_scalar(X) _simd_f64x8_fill_scalar_(X)
	#define _simd_f64x8_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_fill_scalar_instruction_set>()
#elif defined(_simd_f64x4_fill_scalar_)
	#define _simd_f64x8_fill_scalar_(X) _simd_f64x8_combine(_simd_f64x4_fill_scalar_(X), _simd_f64x4_fill_scalar_(X))
	#define _simd_f64x8_fill_scalar(X) _simd_f64x8_fill_scalar_(X)
	#define _simd_f64x8_fill_scalar_enable() (_simd_f64x4_fill_scalar_enable() && _simd_f64x8_combine_enable())
#else
	#define _simd_f64x8_fill_scalar(X) _simd_f64x8_fill_scalar_safe(X)
	#define _simd_f64x8_fill_scalar_enable() true
#endif

#ifdef _simd_f64x16_splitlo_
	#define _simd_f64x16_splitlo(X) _simd_f64x16_splitlo_(X)
	#define _simd_f64x16_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_splitlo_instruction_set>()
#else
	#define _simd_f64x16_splitlo(X) _simd_f64x16_splitlo_safe(X)
	#define _simd_f64x16_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_f64x16 ANVIL_SIMD_CALL _simd_f64x16_fill_scalar_safe(_simd_f64x1 s) {
	_simd_f64x16 tmp;
	for(int i = 0; i < 16; ++i) reinterpret_cast<_simd_f64x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_f64x16_fill_scalar_
	#define _simd_f64x16_fill_scalar(X) _simd_f64x16_fill_scalar_(X)
	#define _simd_f64x16_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_fill_scalar_instruction_set>()
#elif defined(_simd_f64x8_fill_scalar_)
	#define _simd_f64x16_fill_scalar_(X) _simd_f64x16_combine(_simd_f64x8_fill_scalar_(X), _simd_f64x8_fill_scalar_(X))
	#define _simd_f64x16_fill_scalar(X) _simd_f64x16_fill_scalar_(X)
	#define _simd_f64x16_fill_scalar_enable() (_simd_f64x8_fill_scalar_enable() && _simd_f64x16_combine_enable())
#else
	#define _simd_f64x16_fill_scalar(X) _simd_f64x16_fill_scalar_safe(X)
	#define _simd_f64x16_fill_scalar_enable() true
#endif

#ifdef _simd_f64x32_splitlo_
	#define _simd_f64x32_splitlo(X) _simd_f64x32_splitlo_(X)
	#define _simd_f64x32_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_splitlo_instruction_set>()
#else
	#define _simd_f64x32_splitlo(X) _simd_f64x32_splitlo_safe(X)
	#define _simd_f64x32_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_f64x32 ANVIL_SIMD_CALL _simd_f64x32_fill_scalar_safe(_simd_f64x1 s) {
	_simd_f64x32 tmp;
	for(int i = 0; i < 32; ++i) reinterpret_cast<_simd_f64x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_f64x32_fill_scalar_
	#define _simd_f64x32_fill_scalar(X) _simd_f64x32_fill_scalar_(X)
	#define _simd_f64x32_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_fill_scalar_instruction_set>()
#elif defined(_simd_f64x16_fill_scalar_)
	#define _simd_f64x32_fill_scalar_(X) _simd_f64x32_combine(_simd_f64x16_fill_scalar_(X), _simd_f64x16_fill_scalar_(X))
	#define _simd_f64x32_fill_scalar(X) _simd_f64x32_fill_scalar_(X)
	#define _simd_f64x32_fill_scalar_enable() (_simd_f64x16_fill_scalar_enable() && _simd_f64x32_combine_enable())
#else
	#define _simd_f64x32_fill_scalar(X) _simd_f64x32_fill_scalar_safe(X)
	#define _simd_f64x32_fill_scalar_enable() true
#endif

#ifdef _simd_f64x64_splitlo_
	#define _simd_f64x64_splitlo(X) _simd_f64x64_splitlo_(X)
	#define _simd_f64x64_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_splitlo_instruction_set>()
#else
	#define _simd_f64x64_splitlo(X) _simd_f64x64_splitlo_safe(X)
	#define _simd_f64x64_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_f64x64 ANVIL_SIMD_CALL _simd_f64x64_fill_scalar_safe(_simd_f64x1 s) {
	_simd_f64x64 tmp;
	for(int i = 0; i < 64; ++i) reinterpret_cast<_simd_f64x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_f64x64_fill_scalar_
	#define _simd_f64x64_fill_scalar(X) _simd_f64x64_fill_scalar_(X)
	#define _simd_f64x64_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_fill_scalar_instruction_set>()
#elif defined(_simd_f64x32_fill_scalar_)
	#define _simd_f64x64_fill_scalar_(X) _simd_f64x64_combine(_simd_f64x32_fill_scalar_(X), _simd_f64x32_fill_scalar_(X))
	#define _simd_f64x64_fill_scalar(X) _simd_f64x64_fill_scalar_(X)
	#define _simd_f64x64_fill_scalar_enable() (_simd_f64x32_fill_scalar_enable() && _simd_f64x64_combine_enable())
#else
	#define _simd_f64x64_fill_scalar(X) _simd_f64x64_fill_scalar_safe(X)
	#define _simd_f64x64_fill_scalar_enable() true
#endif

#ifdef _simd_f32x2_splitlo_
	#define _simd_f32x2_splitlo(X) _simd_f32x2_splitlo_(X)
	#define _simd_f32x2_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_splitlo_instruction_set>()
#else
	#define _simd_f32x2_splitlo(X) _simd_f32x2_splitlo_safe(X)
	#define _simd_f32x2_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_fill_scalar_safe(_simd_f32x1 s) {
	_simd_f32x2 tmp;
	for(int i = 0; i < 2; ++i) reinterpret_cast<_simd_f32x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_f32x2_fill_scalar_
	#define _simd_f32x2_fill_scalar(X) _simd_f32x2_fill_scalar_(X)
	#define _simd_f32x2_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_fill_scalar_instruction_set>()
#elif defined(_simd_f32x1_fill_scalar_)
	#define _simd_f32x2_fill_scalar_(X) _simd_f32x2_combine(_simd_f32x1_fill_scalar_(X), _simd_f32x1_fill_scalar_(X))
	#define _simd_f32x2_fill_scalar(X) _simd_f32x2_fill_scalar_(X)
	#define _simd_f32x2_fill_scalar_enable() (_simd_f32x1_fill_scalar_enable() && _simd_f32x2_combine_enable())
#else
	#define _simd_f32x2_fill_scalar(X) _simd_f32x2_fill_scalar_safe(X)
	#define _simd_f32x2_fill_scalar_enable() true
#endif

#ifdef _simd_f32x4_splitlo_
	#define _simd_f32x4_splitlo(X) _simd_f32x4_splitlo_(X)
	#define _simd_f32x4_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_splitlo_instruction_set>()
#else
	#define _simd_f32x4_splitlo(X) _simd_f32x4_splitlo_safe(X)
	#define _simd_f32x4_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_fill_scalar_safe(_simd_f32x1 s) {
	_simd_f32x4 tmp;
	for(int i = 0; i < 4; ++i) reinterpret_cast<_simd_f32x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_f32x4_fill_scalar_
	#define _simd_f32x4_fill_scalar(X) _simd_f32x4_fill_scalar_(X)
	#define _simd_f32x4_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_fill_scalar_instruction_set>()
#elif defined(_simd_f32x2_fill_scalar_)
	#define _simd_f32x4_fill_scalar_(X) _simd_f32x4_combine(_simd_f32x2_fill_scalar_(X), _simd_f32x2_fill_scalar_(X))
	#define _simd_f32x4_fill_scalar(X) _simd_f32x4_fill_scalar_(X)
	#define _simd_f32x4_fill_scalar_enable() (_simd_f32x2_fill_scalar_enable() && _simd_f32x4_combine_enable())
#else
	#define _simd_f32x4_fill_scalar(X) _simd_f32x4_fill_scalar_safe(X)
	#define _simd_f32x4_fill_scalar_enable() true
#endif

#ifdef _simd_f32x8_splitlo_
	#define _simd_f32x8_splitlo(X) _simd_f32x8_splitlo_(X)
	#define _simd_f32x8_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_splitlo_instruction_set>()
#else
	#define _simd_f32x8_splitlo(X) _simd_f32x8_splitlo_safe(X)
	#define _simd_f32x8_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_f32x8 ANVIL_SIMD_CALL _simd_f32x8_fill_scalar_safe(_simd_f32x1 s) {
	_simd_f32x8 tmp;
	for(int i = 0; i < 8; ++i) reinterpret_cast<_simd_f32x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_f32x8_fill_scalar_
	#define _simd_f32x8_fill_scalar(X) _simd_f32x8_fill_scalar_(X)
	#define _simd_f32x8_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_fill_scalar_instruction_set>()
#elif defined(_simd_f32x4_fill_scalar_)
	#define _simd_f32x8_fill_scalar_(X) _simd_f32x8_combine(_simd_f32x4_fill_scalar_(X), _simd_f32x4_fill_scalar_(X))
	#define _simd_f32x8_fill_scalar(X) _simd_f32x8_fill_scalar_(X)
	#define _simd_f32x8_fill_scalar_enable() (_simd_f32x4_fill_scalar_enable() && _simd_f32x8_combine_enable())
#else
	#define _simd_f32x8_fill_scalar(X) _simd_f32x8_fill_scalar_safe(X)
	#define _simd_f32x8_fill_scalar_enable() true
#endif

#ifdef _simd_f32x16_splitlo_
	#define _simd_f32x16_splitlo(X) _simd_f32x16_splitlo_(X)
	#define _simd_f32x16_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_splitlo_instruction_set>()
#else
	#define _simd_f32x16_splitlo(X) _simd_f32x16_splitlo_safe(X)
	#define _simd_f32x16_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_f32x16 ANVIL_SIMD_CALL _simd_f32x16_fill_scalar_safe(_simd_f32x1 s) {
	_simd_f32x16 tmp;
	for(int i = 0; i < 16; ++i) reinterpret_cast<_simd_f32x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_f32x16_fill_scalar_
	#define _simd_f32x16_fill_scalar(X) _simd_f32x16_fill_scalar_(X)
	#define _simd_f32x16_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_fill_scalar_instruction_set>()
#elif defined(_simd_f32x8_fill_scalar_)
	#define _simd_f32x16_fill_scalar_(X) _simd_f32x16_combine(_simd_f32x8_fill_scalar_(X), _simd_f32x8_fill_scalar_(X))
	#define _simd_f32x16_fill_scalar(X) _simd_f32x16_fill_scalar_(X)
	#define _simd_f32x16_fill_scalar_enable() (_simd_f32x8_fill_scalar_enable() && _simd_f32x16_combine_enable())
#else
	#define _simd_f32x16_fill_scalar(X) _simd_f32x16_fill_scalar_safe(X)
	#define _simd_f32x16_fill_scalar_enable() true
#endif

#ifdef _simd_f32x32_splitlo_
	#define _simd_f32x32_splitlo(X) _simd_f32x32_splitlo_(X)
	#define _simd_f32x32_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_splitlo_instruction_set>()
#else
	#define _simd_f32x32_splitlo(X) _simd_f32x32_splitlo_safe(X)
	#define _simd_f32x32_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_f32x32 ANVIL_SIMD_CALL _simd_f32x32_fill_scalar_safe(_simd_f32x1 s) {
	_simd_f32x32 tmp;
	for(int i = 0; i < 32; ++i) reinterpret_cast<_simd_f32x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_f32x32_fill_scalar_
	#define _simd_f32x32_fill_scalar(X) _simd_f32x32_fill_scalar_(X)
	#define _simd_f32x32_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_fill_scalar_instruction_set>()
#elif defined(_simd_f32x16_fill_scalar_)
	#define _simd_f32x32_fill_scalar_(X) _simd_f32x32_combine(_simd_f32x16_fill_scalar_(X), _simd_f32x16_fill_scalar_(X))
	#define _simd_f32x32_fill_scalar(X) _simd_f32x32_fill_scalar_(X)
	#define _simd_f32x32_fill_scalar_enable() (_simd_f32x16_fill_scalar_enable() && _simd_f32x32_combine_enable())
#else
	#define _simd_f32x32_fill_scalar(X) _simd_f32x32_fill_scalar_safe(X)
	#define _simd_f32x32_fill_scalar_enable() true
#endif

#ifdef _simd_f32x64_splitlo_
	#define _simd_f32x64_splitlo(X) _simd_f32x64_splitlo_(X)
	#define _simd_f32x64_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_splitlo_instruction_set>()
#else
	#define _simd_f32x64_splitlo(X) _simd_f32x64_splitlo_safe(X)
	#define _simd_f32x64_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_f32x64 ANVIL_SIMD_CALL _simd_f32x64_fill_scalar_safe(_simd_f32x1 s) {
	_simd_f32x64 tmp;
	for(int i = 0; i < 64; ++i) reinterpret_cast<_simd_f32x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_f32x64_fill_scalar_
	#define _simd_f32x64_fill_scalar(X) _simd_f32x64_fill_scalar_(X)
	#define _simd_f32x64_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_fill_scalar_instruction_set>()
#elif defined(_simd_f32x32_fill_scalar_)
	#define _simd_f32x64_fill_scalar_(X) _simd_f32x64_combine(_simd_f32x32_fill_scalar_(X), _simd_f32x32_fill_scalar_(X))
	#define _simd_f32x64_fill_scalar(X) _simd_f32x64_fill_scalar_(X)
	#define _simd_f32x64_fill_scalar_enable() (_simd_f32x32_fill_scalar_enable() && _simd_f32x64_combine_enable())
#else
	#define _simd_f32x64_fill_scalar(X) _simd_f32x64_fill_scalar_safe(X)
	#define _simd_f32x64_fill_scalar_enable() true
#endif

#ifdef _simd_s64x2_splitlo_
	#define _simd_s64x2_splitlo(X) _simd_s64x2_splitlo_(X)
	#define _simd_s64x2_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_splitlo_instruction_set>()
#else
	#define _simd_s64x2_splitlo(X) _simd_s64x2_splitlo_safe(X)
	#define _simd_s64x2_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_fill_scalar_safe(_simd_s64x1 s) {
	_simd_s64x2 tmp;
	for(int i = 0; i < 2; ++i) reinterpret_cast<_simd_s64x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_s64x2_fill_scalar_
	#define _simd_s64x2_fill_scalar(X) _simd_s64x2_fill_scalar_(X)
	#define _simd_s64x2_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_fill_scalar_instruction_set>()
#elif defined(_simd_s64x1_fill_scalar_)
	#define _simd_s64x2_fill_scalar_(X) _simd_s64x2_combine(_simd_s64x1_fill_scalar_(X), _simd_s64x1_fill_scalar_(X))
	#define _simd_s64x2_fill_scalar(X) _simd_s64x2_fill_scalar_(X)
	#define _simd_s64x2_fill_scalar_enable() (_simd_s64x1_fill_scalar_enable() && _simd_s64x2_combine_enable())
#else
	#define _simd_s64x2_fill_scalar(X) _simd_s64x2_fill_scalar_safe(X)
	#define _simd_s64x2_fill_scalar_enable() true
#endif

#ifdef _simd_s64x4_splitlo_
	#define _simd_s64x4_splitlo(X) _simd_s64x4_splitlo_(X)
	#define _simd_s64x4_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_splitlo_instruction_set>()
#else
	#define _simd_s64x4_splitlo(X) _simd_s64x4_splitlo_safe(X)
	#define _simd_s64x4_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_fill_scalar_safe(_simd_s64x1 s) {
	_simd_s64x4 tmp;
	for(int i = 0; i < 4; ++i) reinterpret_cast<_simd_s64x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_s64x4_fill_scalar_
	#define _simd_s64x4_fill_scalar(X) _simd_s64x4_fill_scalar_(X)
	#define _simd_s64x4_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_fill_scalar_instruction_set>()
#elif defined(_simd_s64x2_fill_scalar_)
	#define _simd_s64x4_fill_scalar_(X) _simd_s64x4_combine(_simd_s64x2_fill_scalar_(X), _simd_s64x2_fill_scalar_(X))
	#define _simd_s64x4_fill_scalar(X) _simd_s64x4_fill_scalar_(X)
	#define _simd_s64x4_fill_scalar_enable() (_simd_s64x2_fill_scalar_enable() && _simd_s64x4_combine_enable())
#else
	#define _simd_s64x4_fill_scalar(X) _simd_s64x4_fill_scalar_safe(X)
	#define _simd_s64x4_fill_scalar_enable() true
#endif

#ifdef _simd_s64x8_splitlo_
	#define _simd_s64x8_splitlo(X) _simd_s64x8_splitlo_(X)
	#define _simd_s64x8_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_splitlo_instruction_set>()
#else
	#define _simd_s64x8_splitlo(X) _simd_s64x8_splitlo_safe(X)
	#define _simd_s64x8_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s64x8 ANVIL_SIMD_CALL _simd_s64x8_fill_scalar_safe(_simd_s64x1 s) {
	_simd_s64x8 tmp;
	for(int i = 0; i < 8; ++i) reinterpret_cast<_simd_s64x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_s64x8_fill_scalar_
	#define _simd_s64x8_fill_scalar(X) _simd_s64x8_fill_scalar_(X)
	#define _simd_s64x8_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_fill_scalar_instruction_set>()
#elif defined(_simd_s64x4_fill_scalar_)
	#define _simd_s64x8_fill_scalar_(X) _simd_s64x8_combine(_simd_s64x4_fill_scalar_(X), _simd_s64x4_fill_scalar_(X))
	#define _simd_s64x8_fill_scalar(X) _simd_s64x8_fill_scalar_(X)
	#define _simd_s64x8_fill_scalar_enable() (_simd_s64x4_fill_scalar_enable() && _simd_s64x8_combine_enable())
#else
	#define _simd_s64x8_fill_scalar(X) _simd_s64x8_fill_scalar_safe(X)
	#define _simd_s64x8_fill_scalar_enable() true
#endif

#ifdef _simd_s64x16_splitlo_
	#define _simd_s64x16_splitlo(X) _simd_s64x16_splitlo_(X)
	#define _simd_s64x16_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_splitlo_instruction_set>()
#else
	#define _simd_s64x16_splitlo(X) _simd_s64x16_splitlo_safe(X)
	#define _simd_s64x16_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s64x16 ANVIL_SIMD_CALL _simd_s64x16_fill_scalar_safe(_simd_s64x1 s) {
	_simd_s64x16 tmp;
	for(int i = 0; i < 16; ++i) reinterpret_cast<_simd_s64x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_s64x16_fill_scalar_
	#define _simd_s64x16_fill_scalar(X) _simd_s64x16_fill_scalar_(X)
	#define _simd_s64x16_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_fill_scalar_instruction_set>()
#elif defined(_simd_s64x8_fill_scalar_)
	#define _simd_s64x16_fill_scalar_(X) _simd_s64x16_combine(_simd_s64x8_fill_scalar_(X), _simd_s64x8_fill_scalar_(X))
	#define _simd_s64x16_fill_scalar(X) _simd_s64x16_fill_scalar_(X)
	#define _simd_s64x16_fill_scalar_enable() (_simd_s64x8_fill_scalar_enable() && _simd_s64x16_combine_enable())
#else
	#define _simd_s64x16_fill_scalar(X) _simd_s64x16_fill_scalar_safe(X)
	#define _simd_s64x16_fill_scalar_enable() true
#endif

#ifdef _simd_s64x32_splitlo_
	#define _simd_s64x32_splitlo(X) _simd_s64x32_splitlo_(X)
	#define _simd_s64x32_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_splitlo_instruction_set>()
#else
	#define _simd_s64x32_splitlo(X) _simd_s64x32_splitlo_safe(X)
	#define _simd_s64x32_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s64x32 ANVIL_SIMD_CALL _simd_s64x32_fill_scalar_safe(_simd_s64x1 s) {
	_simd_s64x32 tmp;
	for(int i = 0; i < 32; ++i) reinterpret_cast<_simd_s64x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_s64x32_fill_scalar_
	#define _simd_s64x32_fill_scalar(X) _simd_s64x32_fill_scalar_(X)
	#define _simd_s64x32_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_fill_scalar_instruction_set>()
#elif defined(_simd_s64x16_fill_scalar_)
	#define _simd_s64x32_fill_scalar_(X) _simd_s64x32_combine(_simd_s64x16_fill_scalar_(X), _simd_s64x16_fill_scalar_(X))
	#define _simd_s64x32_fill_scalar(X) _simd_s64x32_fill_scalar_(X)
	#define _simd_s64x32_fill_scalar_enable() (_simd_s64x16_fill_scalar_enable() && _simd_s64x32_combine_enable())
#else
	#define _simd_s64x32_fill_scalar(X) _simd_s64x32_fill_scalar_safe(X)
	#define _simd_s64x32_fill_scalar_enable() true
#endif

#ifdef _simd_s64x64_splitlo_
	#define _simd_s64x64_splitlo(X) _simd_s64x64_splitlo_(X)
	#define _simd_s64x64_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_splitlo_instruction_set>()
#else
	#define _simd_s64x64_splitlo(X) _simd_s64x64_splitlo_safe(X)
	#define _simd_s64x64_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s64x64 ANVIL_SIMD_CALL _simd_s64x64_fill_scalar_safe(_simd_s64x1 s) {
	_simd_s64x64 tmp;
	for(int i = 0; i < 64; ++i) reinterpret_cast<_simd_s64x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_s64x64_fill_scalar_
	#define _simd_s64x64_fill_scalar(X) _simd_s64x64_fill_scalar_(X)
	#define _simd_s64x64_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_fill_scalar_instruction_set>()
#elif defined(_simd_s64x32_fill_scalar_)
	#define _simd_s64x64_fill_scalar_(X) _simd_s64x64_combine(_simd_s64x32_fill_scalar_(X), _simd_s64x32_fill_scalar_(X))
	#define _simd_s64x64_fill_scalar(X) _simd_s64x64_fill_scalar_(X)
	#define _simd_s64x64_fill_scalar_enable() (_simd_s64x32_fill_scalar_enable() && _simd_s64x64_combine_enable())
#else
	#define _simd_s64x64_fill_scalar(X) _simd_s64x64_fill_scalar_safe(X)
	#define _simd_s64x64_fill_scalar_enable() true
#endif

#ifdef _simd_u64x2_splitlo_
	#define _simd_u64x2_splitlo(X) _simd_u64x2_splitlo_(X)
	#define _simd_u64x2_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_splitlo_instruction_set>()
#else
	#define _simd_u64x2_splitlo(X) _simd_u64x2_splitlo_safe(X)
	#define _simd_u64x2_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_fill_scalar_safe(_simd_u64x1 s) {
	_simd_u64x2 tmp;
	for(int i = 0; i < 2; ++i) reinterpret_cast<_simd_u64x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_u64x2_fill_scalar_
	#define _simd_u64x2_fill_scalar(X) _simd_u64x2_fill_scalar_(X)
	#define _simd_u64x2_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_fill_scalar_instruction_set>()
#elif defined(_simd_u64x1_fill_scalar_)
	#define _simd_u64x2_fill_scalar_(X) _simd_u64x2_combine(_simd_u64x1_fill_scalar_(X), _simd_u64x1_fill_scalar_(X))
	#define _simd_u64x2_fill_scalar(X) _simd_u64x2_fill_scalar_(X)
	#define _simd_u64x2_fill_scalar_enable() (_simd_u64x1_fill_scalar_enable() && _simd_u64x2_combine_enable())
#else
	#define _simd_u64x2_fill_scalar(X) _simd_u64x2_fill_scalar_safe(X)
	#define _simd_u64x2_fill_scalar_enable() true
#endif

#ifdef _simd_u64x4_splitlo_
	#define _simd_u64x4_splitlo(X) _simd_u64x4_splitlo_(X)
	#define _simd_u64x4_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_splitlo_instruction_set>()
#else
	#define _simd_u64x4_splitlo(X) _simd_u64x4_splitlo_safe(X)
	#define _simd_u64x4_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_fill_scalar_safe(_simd_u64x1 s) {
	_simd_u64x4 tmp;
	for(int i = 0; i < 4; ++i) reinterpret_cast<_simd_u64x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_u64x4_fill_scalar_
	#define _simd_u64x4_fill_scalar(X) _simd_u64x4_fill_scalar_(X)
	#define _simd_u64x4_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_fill_scalar_instruction_set>()
#elif defined(_simd_u64x2_fill_scalar_)
	#define _simd_u64x4_fill_scalar_(X) _simd_u64x4_combine(_simd_u64x2_fill_scalar_(X), _simd_u64x2_fill_scalar_(X))
	#define _simd_u64x4_fill_scalar(X) _simd_u64x4_fill_scalar_(X)
	#define _simd_u64x4_fill_scalar_enable() (_simd_u64x2_fill_scalar_enable() && _simd_u64x4_combine_enable())
#else
	#define _simd_u64x4_fill_scalar(X) _simd_u64x4_fill_scalar_safe(X)
	#define _simd_u64x4_fill_scalar_enable() true
#endif

#ifdef _simd_u64x8_splitlo_
	#define _simd_u64x8_splitlo(X) _simd_u64x8_splitlo_(X)
	#define _simd_u64x8_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_splitlo_instruction_set>()
#else
	#define _simd_u64x8_splitlo(X) _simd_u64x8_splitlo_safe(X)
	#define _simd_u64x8_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u64x8 ANVIL_SIMD_CALL _simd_u64x8_fill_scalar_safe(_simd_u64x1 s) {
	_simd_u64x8 tmp;
	for(int i = 0; i < 8; ++i) reinterpret_cast<_simd_u64x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_u64x8_fill_scalar_
	#define _simd_u64x8_fill_scalar(X) _simd_u64x8_fill_scalar_(X)
	#define _simd_u64x8_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_fill_scalar_instruction_set>()
#elif defined(_simd_u64x4_fill_scalar_)
	#define _simd_u64x8_fill_scalar_(X) _simd_u64x8_combine(_simd_u64x4_fill_scalar_(X), _simd_u64x4_fill_scalar_(X))
	#define _simd_u64x8_fill_scalar(X) _simd_u64x8_fill_scalar_(X)
	#define _simd_u64x8_fill_scalar_enable() (_simd_u64x4_fill_scalar_enable() && _simd_u64x8_combine_enable())
#else
	#define _simd_u64x8_fill_scalar(X) _simd_u64x8_fill_scalar_safe(X)
	#define _simd_u64x8_fill_scalar_enable() true
#endif

#ifdef _simd_u64x16_splitlo_
	#define _simd_u64x16_splitlo(X) _simd_u64x16_splitlo_(X)
	#define _simd_u64x16_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_splitlo_instruction_set>()
#else
	#define _simd_u64x16_splitlo(X) _simd_u64x16_splitlo_safe(X)
	#define _simd_u64x16_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u64x16 ANVIL_SIMD_CALL _simd_u64x16_fill_scalar_safe(_simd_u64x1 s) {
	_simd_u64x16 tmp;
	for(int i = 0; i < 16; ++i) reinterpret_cast<_simd_u64x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_u64x16_fill_scalar_
	#define _simd_u64x16_fill_scalar(X) _simd_u64x16_fill_scalar_(X)
	#define _simd_u64x16_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_fill_scalar_instruction_set>()
#elif defined(_simd_u64x8_fill_scalar_)
	#define _simd_u64x16_fill_scalar_(X) _simd_u64x16_combine(_simd_u64x8_fill_scalar_(X), _simd_u64x8_fill_scalar_(X))
	#define _simd_u64x16_fill_scalar(X) _simd_u64x16_fill_scalar_(X)
	#define _simd_u64x16_fill_scalar_enable() (_simd_u64x8_fill_scalar_enable() && _simd_u64x16_combine_enable())
#else
	#define _simd_u64x16_fill_scalar(X) _simd_u64x16_fill_scalar_safe(X)
	#define _simd_u64x16_fill_scalar_enable() true
#endif

#ifdef _simd_u64x32_splitlo_
	#define _simd_u64x32_splitlo(X) _simd_u64x32_splitlo_(X)
	#define _simd_u64x32_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_splitlo_instruction_set>()
#else
	#define _simd_u64x32_splitlo(X) _simd_u64x32_splitlo_safe(X)
	#define _simd_u64x32_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u64x32 ANVIL_SIMD_CALL _simd_u64x32_fill_scalar_safe(_simd_u64x1 s) {
	_simd_u64x32 tmp;
	for(int i = 0; i < 32; ++i) reinterpret_cast<_simd_u64x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_u64x32_fill_scalar_
	#define _simd_u64x32_fill_scalar(X) _simd_u64x32_fill_scalar_(X)
	#define _simd_u64x32_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_fill_scalar_instruction_set>()
#elif defined(_simd_u64x16_fill_scalar_)
	#define _simd_u64x32_fill_scalar_(X) _simd_u64x32_combine(_simd_u64x16_fill_scalar_(X), _simd_u64x16_fill_scalar_(X))
	#define _simd_u64x32_fill_scalar(X) _simd_u64x32_fill_scalar_(X)
	#define _simd_u64x32_fill_scalar_enable() (_simd_u64x16_fill_scalar_enable() && _simd_u64x32_combine_enable())
#else
	#define _simd_u64x32_fill_scalar(X) _simd_u64x32_fill_scalar_safe(X)
	#define _simd_u64x32_fill_scalar_enable() true
#endif

#ifdef _simd_u64x64_splitlo_
	#define _simd_u64x64_splitlo(X) _simd_u64x64_splitlo_(X)
	#define _simd_u64x64_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_splitlo_instruction_set>()
#else
	#define _simd_u64x64_splitlo(X) _simd_u64x64_splitlo_safe(X)
	#define _simd_u64x64_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u64x64 ANVIL_SIMD_CALL _simd_u64x64_fill_scalar_safe(_simd_u64x1 s) {
	_simd_u64x64 tmp;
	for(int i = 0; i < 64; ++i) reinterpret_cast<_simd_u64x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_u64x64_fill_scalar_
	#define _simd_u64x64_fill_scalar(X) _simd_u64x64_fill_scalar_(X)
	#define _simd_u64x64_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_fill_scalar_instruction_set>()
#elif defined(_simd_u64x32_fill_scalar_)
	#define _simd_u64x64_fill_scalar_(X) _simd_u64x64_combine(_simd_u64x32_fill_scalar_(X), _simd_u64x32_fill_scalar_(X))
	#define _simd_u64x64_fill_scalar(X) _simd_u64x64_fill_scalar_(X)
	#define _simd_u64x64_fill_scalar_enable() (_simd_u64x32_fill_scalar_enable() && _simd_u64x64_combine_enable())
#else
	#define _simd_u64x64_fill_scalar(X) _simd_u64x64_fill_scalar_safe(X)
	#define _simd_u64x64_fill_scalar_enable() true
#endif

#ifdef _simd_s32x2_splitlo_
	#define _simd_s32x2_splitlo(X) _simd_s32x2_splitlo_(X)
	#define _simd_s32x2_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_splitlo_instruction_set>()
#else
	#define _simd_s32x2_splitlo(X) _simd_s32x2_splitlo_safe(X)
	#define _simd_s32x2_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_fill_scalar_safe(_simd_s32x1 s) {
	_simd_s32x2 tmp;
	for(int i = 0; i < 2; ++i) reinterpret_cast<_simd_s32x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_s32x2_fill_scalar_
	#define _simd_s32x2_fill_scalar(X) _simd_s32x2_fill_scalar_(X)
	#define _simd_s32x2_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_fill_scalar_instruction_set>()
#elif defined(_simd_s32x1_fill_scalar_)
	#define _simd_s32x2_fill_scalar_(X) _simd_s32x2_combine(_simd_s32x1_fill_scalar_(X), _simd_s32x1_fill_scalar_(X))
	#define _simd_s32x2_fill_scalar(X) _simd_s32x2_fill_scalar_(X)
	#define _simd_s32x2_fill_scalar_enable() (_simd_s32x1_fill_scalar_enable() && _simd_s32x2_combine_enable())
#else
	#define _simd_s32x2_fill_scalar(X) _simd_s32x2_fill_scalar_safe(X)
	#define _simd_s32x2_fill_scalar_enable() true
#endif

#ifdef _simd_s32x4_splitlo_
	#define _simd_s32x4_splitlo(X) _simd_s32x4_splitlo_(X)
	#define _simd_s32x4_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_splitlo_instruction_set>()
#else
	#define _simd_s32x4_splitlo(X) _simd_s32x4_splitlo_safe(X)
	#define _simd_s32x4_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_fill_scalar_safe(_simd_s32x1 s) {
	_simd_s32x4 tmp;
	for(int i = 0; i < 4; ++i) reinterpret_cast<_simd_s32x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_s32x4_fill_scalar_
	#define _simd_s32x4_fill_scalar(X) _simd_s32x4_fill_scalar_(X)
	#define _simd_s32x4_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_fill_scalar_instruction_set>()
#elif defined(_simd_s32x2_fill_scalar_)
	#define _simd_s32x4_fill_scalar_(X) _simd_s32x4_combine(_simd_s32x2_fill_scalar_(X), _simd_s32x2_fill_scalar_(X))
	#define _simd_s32x4_fill_scalar(X) _simd_s32x4_fill_scalar_(X)
	#define _simd_s32x4_fill_scalar_enable() (_simd_s32x2_fill_scalar_enable() && _simd_s32x4_combine_enable())
#else
	#define _simd_s32x4_fill_scalar(X) _simd_s32x4_fill_scalar_safe(X)
	#define _simd_s32x4_fill_scalar_enable() true
#endif

#ifdef _simd_s32x8_splitlo_
	#define _simd_s32x8_splitlo(X) _simd_s32x8_splitlo_(X)
	#define _simd_s32x8_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_splitlo_instruction_set>()
#else
	#define _simd_s32x8_splitlo(X) _simd_s32x8_splitlo_safe(X)
	#define _simd_s32x8_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s32x8 ANVIL_SIMD_CALL _simd_s32x8_fill_scalar_safe(_simd_s32x1 s) {
	_simd_s32x8 tmp;
	for(int i = 0; i < 8; ++i) reinterpret_cast<_simd_s32x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_s32x8_fill_scalar_
	#define _simd_s32x8_fill_scalar(X) _simd_s32x8_fill_scalar_(X)
	#define _simd_s32x8_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_fill_scalar_instruction_set>()
#elif defined(_simd_s32x4_fill_scalar_)
	#define _simd_s32x8_fill_scalar_(X) _simd_s32x8_combine(_simd_s32x4_fill_scalar_(X), _simd_s32x4_fill_scalar_(X))
	#define _simd_s32x8_fill_scalar(X) _simd_s32x8_fill_scalar_(X)
	#define _simd_s32x8_fill_scalar_enable() (_simd_s32x4_fill_scalar_enable() && _simd_s32x8_combine_enable())
#else
	#define _simd_s32x8_fill_scalar(X) _simd_s32x8_fill_scalar_safe(X)
	#define _simd_s32x8_fill_scalar_enable() true
#endif

#ifdef _simd_s32x16_splitlo_
	#define _simd_s32x16_splitlo(X) _simd_s32x16_splitlo_(X)
	#define _simd_s32x16_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_splitlo_instruction_set>()
#else
	#define _simd_s32x16_splitlo(X) _simd_s32x16_splitlo_safe(X)
	#define _simd_s32x16_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s32x16 ANVIL_SIMD_CALL _simd_s32x16_fill_scalar_safe(_simd_s32x1 s) {
	_simd_s32x16 tmp;
	for(int i = 0; i < 16; ++i) reinterpret_cast<_simd_s32x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_s32x16_fill_scalar_
	#define _simd_s32x16_fill_scalar(X) _simd_s32x16_fill_scalar_(X)
	#define _simd_s32x16_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_fill_scalar_instruction_set>()
#elif defined(_simd_s32x8_fill_scalar_)
	#define _simd_s32x16_fill_scalar_(X) _simd_s32x16_combine(_simd_s32x8_fill_scalar_(X), _simd_s32x8_fill_scalar_(X))
	#define _simd_s32x16_fill_scalar(X) _simd_s32x16_fill_scalar_(X)
	#define _simd_s32x16_fill_scalar_enable() (_simd_s32x8_fill_scalar_enable() && _simd_s32x16_combine_enable())
#else
	#define _simd_s32x16_fill_scalar(X) _simd_s32x16_fill_scalar_safe(X)
	#define _simd_s32x16_fill_scalar_enable() true
#endif

#ifdef _simd_s32x32_splitlo_
	#define _simd_s32x32_splitlo(X) _simd_s32x32_splitlo_(X)
	#define _simd_s32x32_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_splitlo_instruction_set>()
#else
	#define _simd_s32x32_splitlo(X) _simd_s32x32_splitlo_safe(X)
	#define _simd_s32x32_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s32x32 ANVIL_SIMD_CALL _simd_s32x32_fill_scalar_safe(_simd_s32x1 s) {
	_simd_s32x32 tmp;
	for(int i = 0; i < 32; ++i) reinterpret_cast<_simd_s32x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_s32x32_fill_scalar_
	#define _simd_s32x32_fill_scalar(X) _simd_s32x32_fill_scalar_(X)
	#define _simd_s32x32_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_fill_scalar_instruction_set>()
#elif defined(_simd_s32x16_fill_scalar_)
	#define _simd_s32x32_fill_scalar_(X) _simd_s32x32_combine(_simd_s32x16_fill_scalar_(X), _simd_s32x16_fill_scalar_(X))
	#define _simd_s32x32_fill_scalar(X) _simd_s32x32_fill_scalar_(X)
	#define _simd_s32x32_fill_scalar_enable() (_simd_s32x16_fill_scalar_enable() && _simd_s32x32_combine_enable())
#else
	#define _simd_s32x32_fill_scalar(X) _simd_s32x32_fill_scalar_safe(X)
	#define _simd_s32x32_fill_scalar_enable() true
#endif

#ifdef _simd_s32x64_splitlo_
	#define _simd_s32x64_splitlo(X) _simd_s32x64_splitlo_(X)
	#define _simd_s32x64_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_splitlo_instruction_set>()
#else
	#define _simd_s32x64_splitlo(X) _simd_s32x64_splitlo_safe(X)
	#define _simd_s32x64_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s32x64 ANVIL_SIMD_CALL _simd_s32x64_fill_scalar_safe(_simd_s32x1 s) {
	_simd_s32x64 tmp;
	for(int i = 0; i < 64; ++i) reinterpret_cast<_simd_s32x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_s32x64_fill_scalar_
	#define _simd_s32x64_fill_scalar(X) _simd_s32x64_fill_scalar_(X)
	#define _simd_s32x64_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_fill_scalar_instruction_set>()
#elif defined(_simd_s32x32_fill_scalar_)
	#define _simd_s32x64_fill_scalar_(X) _simd_s32x64_combine(_simd_s32x32_fill_scalar_(X), _simd_s32x32_fill_scalar_(X))
	#define _simd_s32x64_fill_scalar(X) _simd_s32x64_fill_scalar_(X)
	#define _simd_s32x64_fill_scalar_enable() (_simd_s32x32_fill_scalar_enable() && _simd_s32x64_combine_enable())
#else
	#define _simd_s32x64_fill_scalar(X) _simd_s32x64_fill_scalar_safe(X)
	#define _simd_s32x64_fill_scalar_enable() true
#endif

#ifdef _simd_u32x2_splitlo_
	#define _simd_u32x2_splitlo(X) _simd_u32x2_splitlo_(X)
	#define _simd_u32x2_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_splitlo_instruction_set>()
#else
	#define _simd_u32x2_splitlo(X) _simd_u32x2_splitlo_safe(X)
	#define _simd_u32x2_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_fill_scalar_safe(_simd_u32x1 s) {
	_simd_u32x2 tmp;
	for(int i = 0; i < 2; ++i) reinterpret_cast<_simd_u32x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_u32x2_fill_scalar_
	#define _simd_u32x2_fill_scalar(X) _simd_u32x2_fill_scalar_(X)
	#define _simd_u32x2_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_fill_scalar_instruction_set>()
#elif defined(_simd_u32x1_fill_scalar_)
	#define _simd_u32x2_fill_scalar_(X) _simd_u32x2_combine(_simd_u32x1_fill_scalar_(X), _simd_u32x1_fill_scalar_(X))
	#define _simd_u32x2_fill_scalar(X) _simd_u32x2_fill_scalar_(X)
	#define _simd_u32x2_fill_scalar_enable() (_simd_u32x1_fill_scalar_enable() && _simd_u32x2_combine_enable())
#else
	#define _simd_u32x2_fill_scalar(X) _simd_u32x2_fill_scalar_safe(X)
	#define _simd_u32x2_fill_scalar_enable() true
#endif

#ifdef _simd_u32x4_splitlo_
	#define _simd_u32x4_splitlo(X) _simd_u32x4_splitlo_(X)
	#define _simd_u32x4_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_splitlo_instruction_set>()
#else
	#define _simd_u32x4_splitlo(X) _simd_u32x4_splitlo_safe(X)
	#define _simd_u32x4_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_fill_scalar_safe(_simd_u32x1 s) {
	_simd_u32x4 tmp;
	for(int i = 0; i < 4; ++i) reinterpret_cast<_simd_u32x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_u32x4_fill_scalar_
	#define _simd_u32x4_fill_scalar(X) _simd_u32x4_fill_scalar_(X)
	#define _simd_u32x4_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_fill_scalar_instruction_set>()
#elif defined(_simd_u32x2_fill_scalar_)
	#define _simd_u32x4_fill_scalar_(X) _simd_u32x4_combine(_simd_u32x2_fill_scalar_(X), _simd_u32x2_fill_scalar_(X))
	#define _simd_u32x4_fill_scalar(X) _simd_u32x4_fill_scalar_(X)
	#define _simd_u32x4_fill_scalar_enable() (_simd_u32x2_fill_scalar_enable() && _simd_u32x4_combine_enable())
#else
	#define _simd_u32x4_fill_scalar(X) _simd_u32x4_fill_scalar_safe(X)
	#define _simd_u32x4_fill_scalar_enable() true
#endif

#ifdef _simd_u32x8_splitlo_
	#define _simd_u32x8_splitlo(X) _simd_u32x8_splitlo_(X)
	#define _simd_u32x8_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_splitlo_instruction_set>()
#else
	#define _simd_u32x8_splitlo(X) _simd_u32x8_splitlo_safe(X)
	#define _simd_u32x8_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u32x8 ANVIL_SIMD_CALL _simd_u32x8_fill_scalar_safe(_simd_u32x1 s) {
	_simd_u32x8 tmp;
	for(int i = 0; i < 8; ++i) reinterpret_cast<_simd_u32x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_u32x8_fill_scalar_
	#define _simd_u32x8_fill_scalar(X) _simd_u32x8_fill_scalar_(X)
	#define _simd_u32x8_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_fill_scalar_instruction_set>()
#elif defined(_simd_u32x4_fill_scalar_)
	#define _simd_u32x8_fill_scalar_(X) _simd_u32x8_combine(_simd_u32x4_fill_scalar_(X), _simd_u32x4_fill_scalar_(X))
	#define _simd_u32x8_fill_scalar(X) _simd_u32x8_fill_scalar_(X)
	#define _simd_u32x8_fill_scalar_enable() (_simd_u32x4_fill_scalar_enable() && _simd_u32x8_combine_enable())
#else
	#define _simd_u32x8_fill_scalar(X) _simd_u32x8_fill_scalar_safe(X)
	#define _simd_u32x8_fill_scalar_enable() true
#endif

#ifdef _simd_u32x16_splitlo_
	#define _simd_u32x16_splitlo(X) _simd_u32x16_splitlo_(X)
	#define _simd_u32x16_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_splitlo_instruction_set>()
#else
	#define _simd_u32x16_splitlo(X) _simd_u32x16_splitlo_safe(X)
	#define _simd_u32x16_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u32x16 ANVIL_SIMD_CALL _simd_u32x16_fill_scalar_safe(_simd_u32x1 s) {
	_simd_u32x16 tmp;
	for(int i = 0; i < 16; ++i) reinterpret_cast<_simd_u32x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_u32x16_fill_scalar_
	#define _simd_u32x16_fill_scalar(X) _simd_u32x16_fill_scalar_(X)
	#define _simd_u32x16_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_fill_scalar_instruction_set>()
#elif defined(_simd_u32x8_fill_scalar_)
	#define _simd_u32x16_fill_scalar_(X) _simd_u32x16_combine(_simd_u32x8_fill_scalar_(X), _simd_u32x8_fill_scalar_(X))
	#define _simd_u32x16_fill_scalar(X) _simd_u32x16_fill_scalar_(X)
	#define _simd_u32x16_fill_scalar_enable() (_simd_u32x8_fill_scalar_enable() && _simd_u32x16_combine_enable())
#else
	#define _simd_u32x16_fill_scalar(X) _simd_u32x16_fill_scalar_safe(X)
	#define _simd_u32x16_fill_scalar_enable() true
#endif

#ifdef _simd_u32x32_splitlo_
	#define _simd_u32x32_splitlo(X) _simd_u32x32_splitlo_(X)
	#define _simd_u32x32_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_splitlo_instruction_set>()
#else
	#define _simd_u32x32_splitlo(X) _simd_u32x32_splitlo_safe(X)
	#define _simd_u32x32_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u32x32 ANVIL_SIMD_CALL _simd_u32x32_fill_scalar_safe(_simd_u32x1 s) {
	_simd_u32x32 tmp;
	for(int i = 0; i < 32; ++i) reinterpret_cast<_simd_u32x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_u32x32_fill_scalar_
	#define _simd_u32x32_fill_scalar(X) _simd_u32x32_fill_scalar_(X)
	#define _simd_u32x32_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_fill_scalar_instruction_set>()
#elif defined(_simd_u32x16_fill_scalar_)
	#define _simd_u32x32_fill_scalar_(X) _simd_u32x32_combine(_simd_u32x16_fill_scalar_(X), _simd_u32x16_fill_scalar_(X))
	#define _simd_u32x32_fill_scalar(X) _simd_u32x32_fill_scalar_(X)
	#define _simd_u32x32_fill_scalar_enable() (_simd_u32x16_fill_scalar_enable() && _simd_u32x32_combine_enable())
#else
	#define _simd_u32x32_fill_scalar(X) _simd_u32x32_fill_scalar_safe(X)
	#define _simd_u32x32_fill_scalar_enable() true
#endif

#ifdef _simd_u32x64_splitlo_
	#define _simd_u32x64_splitlo(X) _simd_u32x64_splitlo_(X)
	#define _simd_u32x64_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_splitlo_instruction_set>()
#else
	#define _simd_u32x64_splitlo(X) _simd_u32x64_splitlo_safe(X)
	#define _simd_u32x64_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u32x64 ANVIL_SIMD_CALL _simd_u32x64_fill_scalar_safe(_simd_u32x1 s) {
	_simd_u32x64 tmp;
	for(int i = 0; i < 64; ++i) reinterpret_cast<_simd_u32x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_u32x64_fill_scalar_
	#define _simd_u32x64_fill_scalar(X) _simd_u32x64_fill_scalar_(X)
	#define _simd_u32x64_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_fill_scalar_instruction_set>()
#elif defined(_simd_u32x32_fill_scalar_)
	#define _simd_u32x64_fill_scalar_(X) _simd_u32x64_combine(_simd_u32x32_fill_scalar_(X), _simd_u32x32_fill_scalar_(X))
	#define _simd_u32x64_fill_scalar(X) _simd_u32x64_fill_scalar_(X)
	#define _simd_u32x64_fill_scalar_enable() (_simd_u32x32_fill_scalar_enable() && _simd_u32x64_combine_enable())
#else
	#define _simd_u32x64_fill_scalar(X) _simd_u32x64_fill_scalar_safe(X)
	#define _simd_u32x64_fill_scalar_enable() true
#endif

#ifdef _simd_s16x2_splitlo_
	#define _simd_s16x2_splitlo(X) _simd_s16x2_splitlo_(X)
	#define _simd_s16x2_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_splitlo_instruction_set>()
#else
	#define _simd_s16x2_splitlo(X) _simd_s16x2_splitlo_safe(X)
	#define _simd_s16x2_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_fill_scalar_safe(_simd_s16x1 s) {
	_simd_s16x2 tmp;
	for(int i = 0; i < 2; ++i) reinterpret_cast<_simd_s16x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_s16x2_fill_scalar_
	#define _simd_s16x2_fill_scalar(X) _simd_s16x2_fill_scalar_(X)
	#define _simd_s16x2_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_fill_scalar_instruction_set>()
#elif defined(_simd_s16x1_fill_scalar_)
	#define _simd_s16x2_fill_scalar_(X) _simd_s16x2_combine(_simd_s16x1_fill_scalar_(X), _simd_s16x1_fill_scalar_(X))
	#define _simd_s16x2_fill_scalar(X) _simd_s16x2_fill_scalar_(X)
	#define _simd_s16x2_fill_scalar_enable() (_simd_s16x1_fill_scalar_enable() && _simd_s16x2_combine_enable())
#else
	#define _simd_s16x2_fill_scalar(X) _simd_s16x2_fill_scalar_safe(X)
	#define _simd_s16x2_fill_scalar_enable() true
#endif

#ifdef _simd_s16x4_splitlo_
	#define _simd_s16x4_splitlo(X) _simd_s16x4_splitlo_(X)
	#define _simd_s16x4_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_splitlo_instruction_set>()
#else
	#define _simd_s16x4_splitlo(X) _simd_s16x4_splitlo_safe(X)
	#define _simd_s16x4_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_fill_scalar_safe(_simd_s16x1 s) {
	_simd_s16x4 tmp;
	for(int i = 0; i < 4; ++i) reinterpret_cast<_simd_s16x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_s16x4_fill_scalar_
	#define _simd_s16x4_fill_scalar(X) _simd_s16x4_fill_scalar_(X)
	#define _simd_s16x4_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_fill_scalar_instruction_set>()
#elif defined(_simd_s16x2_fill_scalar_)
	#define _simd_s16x4_fill_scalar_(X) _simd_s16x4_combine(_simd_s16x2_fill_scalar_(X), _simd_s16x2_fill_scalar_(X))
	#define _simd_s16x4_fill_scalar(X) _simd_s16x4_fill_scalar_(X)
	#define _simd_s16x4_fill_scalar_enable() (_simd_s16x2_fill_scalar_enable() && _simd_s16x4_combine_enable())
#else
	#define _simd_s16x4_fill_scalar(X) _simd_s16x4_fill_scalar_safe(X)
	#define _simd_s16x4_fill_scalar_enable() true
#endif

#ifdef _simd_s16x8_splitlo_
	#define _simd_s16x8_splitlo(X) _simd_s16x8_splitlo_(X)
	#define _simd_s16x8_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_splitlo_instruction_set>()
#else
	#define _simd_s16x8_splitlo(X) _simd_s16x8_splitlo_safe(X)
	#define _simd_s16x8_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s16x8 ANVIL_SIMD_CALL _simd_s16x8_fill_scalar_safe(_simd_s16x1 s) {
	_simd_s16x8 tmp;
	for(int i = 0; i < 8; ++i) reinterpret_cast<_simd_s16x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_s16x8_fill_scalar_
	#define _simd_s16x8_fill_scalar(X) _simd_s16x8_fill_scalar_(X)
	#define _simd_s16x8_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_fill_scalar_instruction_set>()
#elif defined(_simd_s16x4_fill_scalar_)
	#define _simd_s16x8_fill_scalar_(X) _simd_s16x8_combine(_simd_s16x4_fill_scalar_(X), _simd_s16x4_fill_scalar_(X))
	#define _simd_s16x8_fill_scalar(X) _simd_s16x8_fill_scalar_(X)
	#define _simd_s16x8_fill_scalar_enable() (_simd_s16x4_fill_scalar_enable() && _simd_s16x8_combine_enable())
#else
	#define _simd_s16x8_fill_scalar(X) _simd_s16x8_fill_scalar_safe(X)
	#define _simd_s16x8_fill_scalar_enable() true
#endif

#ifdef _simd_s16x16_splitlo_
	#define _simd_s16x16_splitlo(X) _simd_s16x16_splitlo_(X)
	#define _simd_s16x16_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_splitlo_instruction_set>()
#else
	#define _simd_s16x16_splitlo(X) _simd_s16x16_splitlo_safe(X)
	#define _simd_s16x16_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s16x16 ANVIL_SIMD_CALL _simd_s16x16_fill_scalar_safe(_simd_s16x1 s) {
	_simd_s16x16 tmp;
	for(int i = 0; i < 16; ++i) reinterpret_cast<_simd_s16x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_s16x16_fill_scalar_
	#define _simd_s16x16_fill_scalar(X) _simd_s16x16_fill_scalar_(X)
	#define _simd_s16x16_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_fill_scalar_instruction_set>()
#elif defined(_simd_s16x8_fill_scalar_)
	#define _simd_s16x16_fill_scalar_(X) _simd_s16x16_combine(_simd_s16x8_fill_scalar_(X), _simd_s16x8_fill_scalar_(X))
	#define _simd_s16x16_fill_scalar(X) _simd_s16x16_fill_scalar_(X)
	#define _simd_s16x16_fill_scalar_enable() (_simd_s16x8_fill_scalar_enable() && _simd_s16x16_combine_enable())
#else
	#define _simd_s16x16_fill_scalar(X) _simd_s16x16_fill_scalar_safe(X)
	#define _simd_s16x16_fill_scalar_enable() true
#endif

#ifdef _simd_s16x32_splitlo_
	#define _simd_s16x32_splitlo(X) _simd_s16x32_splitlo_(X)
	#define _simd_s16x32_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_splitlo_instruction_set>()
#else
	#define _simd_s16x32_splitlo(X) _simd_s16x32_splitlo_safe(X)
	#define _simd_s16x32_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s16x32 ANVIL_SIMD_CALL _simd_s16x32_fill_scalar_safe(_simd_s16x1 s) {
	_simd_s16x32 tmp;
	for(int i = 0; i < 32; ++i) reinterpret_cast<_simd_s16x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_s16x32_fill_scalar_
	#define _simd_s16x32_fill_scalar(X) _simd_s16x32_fill_scalar_(X)
	#define _simd_s16x32_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_fill_scalar_instruction_set>()
#elif defined(_simd_s16x16_fill_scalar_)
	#define _simd_s16x32_fill_scalar_(X) _simd_s16x32_combine(_simd_s16x16_fill_scalar_(X), _simd_s16x16_fill_scalar_(X))
	#define _simd_s16x32_fill_scalar(X) _simd_s16x32_fill_scalar_(X)
	#define _simd_s16x32_fill_scalar_enable() (_simd_s16x16_fill_scalar_enable() && _simd_s16x32_combine_enable())
#else
	#define _simd_s16x32_fill_scalar(X) _simd_s16x32_fill_scalar_safe(X)
	#define _simd_s16x32_fill_scalar_enable() true
#endif

#ifdef _simd_s16x64_splitlo_
	#define _simd_s16x64_splitlo(X) _simd_s16x64_splitlo_(X)
	#define _simd_s16x64_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_splitlo_instruction_set>()
#else
	#define _simd_s16x64_splitlo(X) _simd_s16x64_splitlo_safe(X)
	#define _simd_s16x64_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s16x64 ANVIL_SIMD_CALL _simd_s16x64_fill_scalar_safe(_simd_s16x1 s) {
	_simd_s16x64 tmp;
	for(int i = 0; i < 64; ++i) reinterpret_cast<_simd_s16x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_s16x64_fill_scalar_
	#define _simd_s16x64_fill_scalar(X) _simd_s16x64_fill_scalar_(X)
	#define _simd_s16x64_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_fill_scalar_instruction_set>()
#elif defined(_simd_s16x32_fill_scalar_)
	#define _simd_s16x64_fill_scalar_(X) _simd_s16x64_combine(_simd_s16x32_fill_scalar_(X), _simd_s16x32_fill_scalar_(X))
	#define _simd_s16x64_fill_scalar(X) _simd_s16x64_fill_scalar_(X)
	#define _simd_s16x64_fill_scalar_enable() (_simd_s16x32_fill_scalar_enable() && _simd_s16x64_combine_enable())
#else
	#define _simd_s16x64_fill_scalar(X) _simd_s16x64_fill_scalar_safe(X)
	#define _simd_s16x64_fill_scalar_enable() true
#endif

#ifdef _simd_u16x2_splitlo_
	#define _simd_u16x2_splitlo(X) _simd_u16x2_splitlo_(X)
	#define _simd_u16x2_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_splitlo_instruction_set>()
#else
	#define _simd_u16x2_splitlo(X) _simd_u16x2_splitlo_safe(X)
	#define _simd_u16x2_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_fill_scalar_safe(_simd_u16x1 s) {
	_simd_u16x2 tmp;
	for(int i = 0; i < 2; ++i) reinterpret_cast<_simd_u16x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_u16x2_fill_scalar_
	#define _simd_u16x2_fill_scalar(X) _simd_u16x2_fill_scalar_(X)
	#define _simd_u16x2_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_fill_scalar_instruction_set>()
#elif defined(_simd_u16x1_fill_scalar_)
	#define _simd_u16x2_fill_scalar_(X) _simd_u16x2_combine(_simd_u16x1_fill_scalar_(X), _simd_u16x1_fill_scalar_(X))
	#define _simd_u16x2_fill_scalar(X) _simd_u16x2_fill_scalar_(X)
	#define _simd_u16x2_fill_scalar_enable() (_simd_u16x1_fill_scalar_enable() && _simd_u16x2_combine_enable())
#else
	#define _simd_u16x2_fill_scalar(X) _simd_u16x2_fill_scalar_safe(X)
	#define _simd_u16x2_fill_scalar_enable() true
#endif

#ifdef _simd_u16x4_splitlo_
	#define _simd_u16x4_splitlo(X) _simd_u16x4_splitlo_(X)
	#define _simd_u16x4_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_splitlo_instruction_set>()
#else
	#define _simd_u16x4_splitlo(X) _simd_u16x4_splitlo_safe(X)
	#define _simd_u16x4_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_fill_scalar_safe(_simd_u16x1 s) {
	_simd_u16x4 tmp;
	for(int i = 0; i < 4; ++i) reinterpret_cast<_simd_u16x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_u16x4_fill_scalar_
	#define _simd_u16x4_fill_scalar(X) _simd_u16x4_fill_scalar_(X)
	#define _simd_u16x4_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_fill_scalar_instruction_set>()
#elif defined(_simd_u16x2_fill_scalar_)
	#define _simd_u16x4_fill_scalar_(X) _simd_u16x4_combine(_simd_u16x2_fill_scalar_(X), _simd_u16x2_fill_scalar_(X))
	#define _simd_u16x4_fill_scalar(X) _simd_u16x4_fill_scalar_(X)
	#define _simd_u16x4_fill_scalar_enable() (_simd_u16x2_fill_scalar_enable() && _simd_u16x4_combine_enable())
#else
	#define _simd_u16x4_fill_scalar(X) _simd_u16x4_fill_scalar_safe(X)
	#define _simd_u16x4_fill_scalar_enable() true
#endif

#ifdef _simd_u16x8_splitlo_
	#define _simd_u16x8_splitlo(X) _simd_u16x8_splitlo_(X)
	#define _simd_u16x8_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_splitlo_instruction_set>()
#else
	#define _simd_u16x8_splitlo(X) _simd_u16x8_splitlo_safe(X)
	#define _simd_u16x8_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u16x8 ANVIL_SIMD_CALL _simd_u16x8_fill_scalar_safe(_simd_u16x1 s) {
	_simd_u16x8 tmp;
	for(int i = 0; i < 8; ++i) reinterpret_cast<_simd_u16x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_u16x8_fill_scalar_
	#define _simd_u16x8_fill_scalar(X) _simd_u16x8_fill_scalar_(X)
	#define _simd_u16x8_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_fill_scalar_instruction_set>()
#elif defined(_simd_u16x4_fill_scalar_)
	#define _simd_u16x8_fill_scalar_(X) _simd_u16x8_combine(_simd_u16x4_fill_scalar_(X), _simd_u16x4_fill_scalar_(X))
	#define _simd_u16x8_fill_scalar(X) _simd_u16x8_fill_scalar_(X)
	#define _simd_u16x8_fill_scalar_enable() (_simd_u16x4_fill_scalar_enable() && _simd_u16x8_combine_enable())
#else
	#define _simd_u16x8_fill_scalar(X) _simd_u16x8_fill_scalar_safe(X)
	#define _simd_u16x8_fill_scalar_enable() true
#endif

#ifdef _simd_u16x16_splitlo_
	#define _simd_u16x16_splitlo(X) _simd_u16x16_splitlo_(X)
	#define _simd_u16x16_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_splitlo_instruction_set>()
#else
	#define _simd_u16x16_splitlo(X) _simd_u16x16_splitlo_safe(X)
	#define _simd_u16x16_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u16x16 ANVIL_SIMD_CALL _simd_u16x16_fill_scalar_safe(_simd_u16x1 s) {
	_simd_u16x16 tmp;
	for(int i = 0; i < 16; ++i) reinterpret_cast<_simd_u16x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_u16x16_fill_scalar_
	#define _simd_u16x16_fill_scalar(X) _simd_u16x16_fill_scalar_(X)
	#define _simd_u16x16_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_fill_scalar_instruction_set>()
#elif defined(_simd_u16x8_fill_scalar_)
	#define _simd_u16x16_fill_scalar_(X) _simd_u16x16_combine(_simd_u16x8_fill_scalar_(X), _simd_u16x8_fill_scalar_(X))
	#define _simd_u16x16_fill_scalar(X) _simd_u16x16_fill_scalar_(X)
	#define _simd_u16x16_fill_scalar_enable() (_simd_u16x8_fill_scalar_enable() && _simd_u16x16_combine_enable())
#else
	#define _simd_u16x16_fill_scalar(X) _simd_u16x16_fill_scalar_safe(X)
	#define _simd_u16x16_fill_scalar_enable() true
#endif

#ifdef _simd_u16x32_splitlo_
	#define _simd_u16x32_splitlo(X) _simd_u16x32_splitlo_(X)
	#define _simd_u16x32_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_splitlo_instruction_set>()
#else
	#define _simd_u16x32_splitlo(X) _simd_u16x32_splitlo_safe(X)
	#define _simd_u16x32_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u16x32 ANVIL_SIMD_CALL _simd_u16x32_fill_scalar_safe(_simd_u16x1 s) {
	_simd_u16x32 tmp;
	for(int i = 0; i < 32; ++i) reinterpret_cast<_simd_u16x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_u16x32_fill_scalar_
	#define _simd_u16x32_fill_scalar(X) _simd_u16x32_fill_scalar_(X)
	#define _simd_u16x32_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_fill_scalar_instruction_set>()
#elif defined(_simd_u16x16_fill_scalar_)
	#define _simd_u16x32_fill_scalar_(X) _simd_u16x32_combine(_simd_u16x16_fill_scalar_(X), _simd_u16x16_fill_scalar_(X))
	#define _simd_u16x32_fill_scalar(X) _simd_u16x32_fill_scalar_(X)
	#define _simd_u16x32_fill_scalar_enable() (_simd_u16x16_fill_scalar_enable() && _simd_u16x32_combine_enable())
#else
	#define _simd_u16x32_fill_scalar(X) _simd_u16x32_fill_scalar_safe(X)
	#define _simd_u16x32_fill_scalar_enable() true
#endif

#ifdef _simd_u16x64_splitlo_
	#define _simd_u16x64_splitlo(X) _simd_u16x64_splitlo_(X)
	#define _simd_u16x64_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_splitlo_instruction_set>()
#else
	#define _simd_u16x64_splitlo(X) _simd_u16x64_splitlo_safe(X)
	#define _simd_u16x64_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u16x64 ANVIL_SIMD_CALL _simd_u16x64_fill_scalar_safe(_simd_u16x1 s) {
	_simd_u16x64 tmp;
	for(int i = 0; i < 64; ++i) reinterpret_cast<_simd_u16x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_u16x64_fill_scalar_
	#define _simd_u16x64_fill_scalar(X) _simd_u16x64_fill_scalar_(X)
	#define _simd_u16x64_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_fill_scalar_instruction_set>()
#elif defined(_simd_u16x32_fill_scalar_)
	#define _simd_u16x64_fill_scalar_(X) _simd_u16x64_combine(_simd_u16x32_fill_scalar_(X), _simd_u16x32_fill_scalar_(X))
	#define _simd_u16x64_fill_scalar(X) _simd_u16x64_fill_scalar_(X)
	#define _simd_u16x64_fill_scalar_enable() (_simd_u16x32_fill_scalar_enable() && _simd_u16x64_combine_enable())
#else
	#define _simd_u16x64_fill_scalar(X) _simd_u16x64_fill_scalar_safe(X)
	#define _simd_u16x64_fill_scalar_enable() true
#endif

#ifdef _simd_s8x2_splitlo_
	#define _simd_s8x2_splitlo(X) _simd_s8x2_splitlo_(X)
	#define _simd_s8x2_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_splitlo_instruction_set>()
#else
	#define _simd_s8x2_splitlo(X) _simd_s8x2_splitlo_safe(X)
	#define _simd_s8x2_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_fill_scalar_safe(_simd_s8x1 s) {
	_simd_s8x2 tmp;
	for(int i = 0; i < 2; ++i) reinterpret_cast<_simd_s8x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_s8x2_fill_scalar_
	#define _simd_s8x2_fill_scalar(X) _simd_s8x2_fill_scalar_(X)
	#define _simd_s8x2_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_fill_scalar_instruction_set>()
#elif defined(_simd_s8x1_fill_scalar_)
	#define _simd_s8x2_fill_scalar_(X) _simd_s8x2_combine(_simd_s8x1_fill_scalar_(X), _simd_s8x1_fill_scalar_(X))
	#define _simd_s8x2_fill_scalar(X) _simd_s8x2_fill_scalar_(X)
	#define _simd_s8x2_fill_scalar_enable() (_simd_s8x1_fill_scalar_enable() && _simd_s8x2_combine_enable())
#else
	#define _simd_s8x2_fill_scalar(X) _simd_s8x2_fill_scalar_safe(X)
	#define _simd_s8x2_fill_scalar_enable() true
#endif

#ifdef _simd_s8x4_splitlo_
	#define _simd_s8x4_splitlo(X) _simd_s8x4_splitlo_(X)
	#define _simd_s8x4_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_splitlo_instruction_set>()
#else
	#define _simd_s8x4_splitlo(X) _simd_s8x4_splitlo_safe(X)
	#define _simd_s8x4_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_fill_scalar_safe(_simd_s8x1 s) {
	_simd_s8x4 tmp;
	for(int i = 0; i < 4; ++i) reinterpret_cast<_simd_s8x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_s8x4_fill_scalar_
	#define _simd_s8x4_fill_scalar(X) _simd_s8x4_fill_scalar_(X)
	#define _simd_s8x4_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_fill_scalar_instruction_set>()
#elif defined(_simd_s8x2_fill_scalar_)
	#define _simd_s8x4_fill_scalar_(X) _simd_s8x4_combine(_simd_s8x2_fill_scalar_(X), _simd_s8x2_fill_scalar_(X))
	#define _simd_s8x4_fill_scalar(X) _simd_s8x4_fill_scalar_(X)
	#define _simd_s8x4_fill_scalar_enable() (_simd_s8x2_fill_scalar_enable() && _simd_s8x4_combine_enable())
#else
	#define _simd_s8x4_fill_scalar(X) _simd_s8x4_fill_scalar_safe(X)
	#define _simd_s8x4_fill_scalar_enable() true
#endif

#ifdef _simd_s8x8_splitlo_
	#define _simd_s8x8_splitlo(X) _simd_s8x8_splitlo_(X)
	#define _simd_s8x8_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_splitlo_instruction_set>()
#else
	#define _simd_s8x8_splitlo(X) _simd_s8x8_splitlo_safe(X)
	#define _simd_s8x8_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s8x8 ANVIL_SIMD_CALL _simd_s8x8_fill_scalar_safe(_simd_s8x1 s) {
	_simd_s8x8 tmp;
	for(int i = 0; i < 8; ++i) reinterpret_cast<_simd_s8x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_s8x8_fill_scalar_
	#define _simd_s8x8_fill_scalar(X) _simd_s8x8_fill_scalar_(X)
	#define _simd_s8x8_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_fill_scalar_instruction_set>()
#elif defined(_simd_s8x4_fill_scalar_)
	#define _simd_s8x8_fill_scalar_(X) _simd_s8x8_combine(_simd_s8x4_fill_scalar_(X), _simd_s8x4_fill_scalar_(X))
	#define _simd_s8x8_fill_scalar(X) _simd_s8x8_fill_scalar_(X)
	#define _simd_s8x8_fill_scalar_enable() (_simd_s8x4_fill_scalar_enable() && _simd_s8x8_combine_enable())
#else
	#define _simd_s8x8_fill_scalar(X) _simd_s8x8_fill_scalar_safe(X)
	#define _simd_s8x8_fill_scalar_enable() true
#endif

#ifdef _simd_s8x16_splitlo_
	#define _simd_s8x16_splitlo(X) _simd_s8x16_splitlo_(X)
	#define _simd_s8x16_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_splitlo_instruction_set>()
#else
	#define _simd_s8x16_splitlo(X) _simd_s8x16_splitlo_safe(X)
	#define _simd_s8x16_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s8x16 ANVIL_SIMD_CALL _simd_s8x16_fill_scalar_safe(_simd_s8x1 s) {
	_simd_s8x16 tmp;
	for(int i = 0; i < 16; ++i) reinterpret_cast<_simd_s8x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_s8x16_fill_scalar_
	#define _simd_s8x16_fill_scalar(X) _simd_s8x16_fill_scalar_(X)
	#define _simd_s8x16_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_fill_scalar_instruction_set>()
#elif defined(_simd_s8x8_fill_scalar_)
	#define _simd_s8x16_fill_scalar_(X) _simd_s8x16_combine(_simd_s8x8_fill_scalar_(X), _simd_s8x8_fill_scalar_(X))
	#define _simd_s8x16_fill_scalar(X) _simd_s8x16_fill_scalar_(X)
	#define _simd_s8x16_fill_scalar_enable() (_simd_s8x8_fill_scalar_enable() && _simd_s8x16_combine_enable())
#else
	#define _simd_s8x16_fill_scalar(X) _simd_s8x16_fill_scalar_safe(X)
	#define _simd_s8x16_fill_scalar_enable() true
#endif

#ifdef _simd_s8x32_splitlo_
	#define _simd_s8x32_splitlo(X) _simd_s8x32_splitlo_(X)
	#define _simd_s8x32_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_splitlo_instruction_set>()
#else
	#define _simd_s8x32_splitlo(X) _simd_s8x32_splitlo_safe(X)
	#define _simd_s8x32_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s8x32 ANVIL_SIMD_CALL _simd_s8x32_fill_scalar_safe(_simd_s8x1 s) {
	_simd_s8x32 tmp;
	for(int i = 0; i < 32; ++i) reinterpret_cast<_simd_s8x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_s8x32_fill_scalar_
	#define _simd_s8x32_fill_scalar(X) _simd_s8x32_fill_scalar_(X)
	#define _simd_s8x32_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_fill_scalar_instruction_set>()
#elif defined(_simd_s8x16_fill_scalar_)
	#define _simd_s8x32_fill_scalar_(X) _simd_s8x32_combine(_simd_s8x16_fill_scalar_(X), _simd_s8x16_fill_scalar_(X))
	#define _simd_s8x32_fill_scalar(X) _simd_s8x32_fill_scalar_(X)
	#define _simd_s8x32_fill_scalar_enable() (_simd_s8x16_fill_scalar_enable() && _simd_s8x32_combine_enable())
#else
	#define _simd_s8x32_fill_scalar(X) _simd_s8x32_fill_scalar_safe(X)
	#define _simd_s8x32_fill_scalar_enable() true
#endif

#ifdef _simd_s8x64_splitlo_
	#define _simd_s8x64_splitlo(X) _simd_s8x64_splitlo_(X)
	#define _simd_s8x64_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_splitlo_instruction_set>()
#else
	#define _simd_s8x64_splitlo(X) _simd_s8x64_splitlo_safe(X)
	#define _simd_s8x64_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s8x64 ANVIL_SIMD_CALL _simd_s8x64_fill_scalar_safe(_simd_s8x1 s) {
	_simd_s8x64 tmp;
	for(int i = 0; i < 64; ++i) reinterpret_cast<_simd_s8x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_s8x64_fill_scalar_
	#define _simd_s8x64_fill_scalar(X) _simd_s8x64_fill_scalar_(X)
	#define _simd_s8x64_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_fill_scalar_instruction_set>()
#elif defined(_simd_s8x32_fill_scalar_)
	#define _simd_s8x64_fill_scalar_(X) _simd_s8x64_combine(_simd_s8x32_fill_scalar_(X), _simd_s8x32_fill_scalar_(X))
	#define _simd_s8x64_fill_scalar(X) _simd_s8x64_fill_scalar_(X)
	#define _simd_s8x64_fill_scalar_enable() (_simd_s8x32_fill_scalar_enable() && _simd_s8x64_combine_enable())
#else
	#define _simd_s8x64_fill_scalar(X) _simd_s8x64_fill_scalar_safe(X)
	#define _simd_s8x64_fill_scalar_enable() true
#endif

#ifdef _simd_u8x2_splitlo_
	#define _simd_u8x2_splitlo(X) _simd_u8x2_splitlo_(X)
	#define _simd_u8x2_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_splitlo_instruction_set>()
#else
	#define _simd_u8x2_splitlo(X) _simd_u8x2_splitlo_safe(X)
	#define _simd_u8x2_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_fill_scalar_safe(_simd_u8x1 s) {
	_simd_u8x2 tmp;
	for(int i = 0; i < 2; ++i) reinterpret_cast<_simd_u8x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_u8x2_fill_scalar_
	#define _simd_u8x2_fill_scalar(X) _simd_u8x2_fill_scalar_(X)
	#define _simd_u8x2_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_fill_scalar_instruction_set>()
#elif defined(_simd_u8x1_fill_scalar_)
	#define _simd_u8x2_fill_scalar_(X) _simd_u8x2_combine(_simd_u8x1_fill_scalar_(X), _simd_u8x1_fill_scalar_(X))
	#define _simd_u8x2_fill_scalar(X) _simd_u8x2_fill_scalar_(X)
	#define _simd_u8x2_fill_scalar_enable() (_simd_u8x1_fill_scalar_enable() && _simd_u8x2_combine_enable())
#else
	#define _simd_u8x2_fill_scalar(X) _simd_u8x2_fill_scalar_safe(X)
	#define _simd_u8x2_fill_scalar_enable() true
#endif

#ifdef _simd_u8x4_splitlo_
	#define _simd_u8x4_splitlo(X) _simd_u8x4_splitlo_(X)
	#define _simd_u8x4_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_splitlo_instruction_set>()
#else
	#define _simd_u8x4_splitlo(X) _simd_u8x4_splitlo_safe(X)
	#define _simd_u8x4_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_fill_scalar_safe(_simd_u8x1 s) {
	_simd_u8x4 tmp;
	for(int i = 0; i < 4; ++i) reinterpret_cast<_simd_u8x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_u8x4_fill_scalar_
	#define _simd_u8x4_fill_scalar(X) _simd_u8x4_fill_scalar_(X)
	#define _simd_u8x4_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_fill_scalar_instruction_set>()
#elif defined(_simd_u8x2_fill_scalar_)
	#define _simd_u8x4_fill_scalar_(X) _simd_u8x4_combine(_simd_u8x2_fill_scalar_(X), _simd_u8x2_fill_scalar_(X))
	#define _simd_u8x4_fill_scalar(X) _simd_u8x4_fill_scalar_(X)
	#define _simd_u8x4_fill_scalar_enable() (_simd_u8x2_fill_scalar_enable() && _simd_u8x4_combine_enable())
#else
	#define _simd_u8x4_fill_scalar(X) _simd_u8x4_fill_scalar_safe(X)
	#define _simd_u8x4_fill_scalar_enable() true
#endif

#ifdef _simd_u8x8_splitlo_
	#define _simd_u8x8_splitlo(X) _simd_u8x8_splitlo_(X)
	#define _simd_u8x8_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_splitlo_instruction_set>()
#else
	#define _simd_u8x8_splitlo(X) _simd_u8x8_splitlo_safe(X)
	#define _simd_u8x8_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u8x8 ANVIL_SIMD_CALL _simd_u8x8_fill_scalar_safe(_simd_u8x1 s) {
	_simd_u8x8 tmp;
	for(int i = 0; i < 8; ++i) reinterpret_cast<_simd_u8x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_u8x8_fill_scalar_
	#define _simd_u8x8_fill_scalar(X) _simd_u8x8_fill_scalar_(X)
	#define _simd_u8x8_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_fill_scalar_instruction_set>()
#elif defined(_simd_u8x4_fill_scalar_)
	#define _simd_u8x8_fill_scalar_(X) _simd_u8x8_combine(_simd_u8x4_fill_scalar_(X), _simd_u8x4_fill_scalar_(X))
	#define _simd_u8x8_fill_scalar(X) _simd_u8x8_fill_scalar_(X)
	#define _simd_u8x8_fill_scalar_enable() (_simd_u8x4_fill_scalar_enable() && _simd_u8x8_combine_enable())
#else
	#define _simd_u8x8_fill_scalar(X) _simd_u8x8_fill_scalar_safe(X)
	#define _simd_u8x8_fill_scalar_enable() true
#endif

#ifdef _simd_u8x16_splitlo_
	#define _simd_u8x16_splitlo(X) _simd_u8x16_splitlo_(X)
	#define _simd_u8x16_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_splitlo_instruction_set>()
#else
	#define _simd_u8x16_splitlo(X) _simd_u8x16_splitlo_safe(X)
	#define _simd_u8x16_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u8x16 ANVIL_SIMD_CALL _simd_u8x16_fill_scalar_safe(_simd_u8x1 s) {
	_simd_u8x16 tmp;
	for(int i = 0; i < 16; ++i) reinterpret_cast<_simd_u8x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_u8x16_fill_scalar_
	#define _simd_u8x16_fill_scalar(X) _simd_u8x16_fill_scalar_(X)
	#define _simd_u8x16_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_fill_scalar_instruction_set>()
#elif defined(_simd_u8x8_fill_scalar_)
	#define _simd_u8x16_fill_scalar_(X) _simd_u8x16_combine(_simd_u8x8_fill_scalar_(X), _simd_u8x8_fill_scalar_(X))
	#define _simd_u8x16_fill_scalar(X) _simd_u8x16_fill_scalar_(X)
	#define _simd_u8x16_fill_scalar_enable() (_simd_u8x8_fill_scalar_enable() && _simd_u8x16_combine_enable())
#else
	#define _simd_u8x16_fill_scalar(X) _simd_u8x16_fill_scalar_safe(X)
	#define _simd_u8x16_fill_scalar_enable() true
#endif

#ifdef _simd_u8x32_splitlo_
	#define _simd_u8x32_splitlo(X) _simd_u8x32_splitlo_(X)
	#define _simd_u8x32_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_splitlo_instruction_set>()
#else
	#define _simd_u8x32_splitlo(X) _simd_u8x32_splitlo_safe(X)
	#define _simd_u8x32_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u8x32 ANVIL_SIMD_CALL _simd_u8x32_fill_scalar_safe(_simd_u8x1 s) {
	_simd_u8x32 tmp;
	for(int i = 0; i < 32; ++i) reinterpret_cast<_simd_u8x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_u8x32_fill_scalar_
	#define _simd_u8x32_fill_scalar(X) _simd_u8x32_fill_scalar_(X)
	#define _simd_u8x32_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_fill_scalar_instruction_set>()
#elif defined(_simd_u8x16_fill_scalar_)
	#define _simd_u8x32_fill_scalar_(X) _simd_u8x32_combine(_simd_u8x16_fill_scalar_(X), _simd_u8x16_fill_scalar_(X))
	#define _simd_u8x32_fill_scalar(X) _simd_u8x32_fill_scalar_(X)
	#define _simd_u8x32_fill_scalar_enable() (_simd_u8x16_fill_scalar_enable() && _simd_u8x32_combine_enable())
#else
	#define _simd_u8x32_fill_scalar(X) _simd_u8x32_fill_scalar_safe(X)
	#define _simd_u8x32_fill_scalar_enable() true
#endif

#ifdef _simd_u8x64_splitlo_
	#define _simd_u8x64_splitlo(X) _simd_u8x64_splitlo_(X)
	#define _simd_u8x64_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_splitlo_instruction_set>()
#else
	#define _simd_u8x64_splitlo(X) _simd_u8x64_splitlo_safe(X)
	#define _simd_u8x64_splitlo_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u8x64 ANVIL_SIMD_CALL _simd_u8x64_fill_scalar_safe(_simd_u8x1 s) {
	_simd_u8x64 tmp;
	for(int i = 0; i < 64; ++i) reinterpret_cast<_simd_u8x1*>(&tmp)[i] = s;
	return tmp;
}
#ifdef _simd_u8x64_fill_scalar_
	#define _simd_u8x64_fill_scalar(X) _simd_u8x64_fill_scalar_(X)
	#define _simd_u8x64_fill_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_fill_scalar_instruction_set>()
#elif defined(_simd_u8x32_fill_scalar_)
	#define _simd_u8x64_fill_scalar_(X) _simd_u8x64_combine(_simd_u8x32_fill_scalar_(X), _simd_u8x32_fill_scalar_(X))
	#define _simd_u8x64_fill_scalar(X) _simd_u8x64_fill_scalar_(X)
	#define _simd_u8x64_fill_scalar_enable() (_simd_u8x32_fill_scalar_enable() && _simd_u8x64_combine_enable())
#else
	#define _simd_u8x64_fill_scalar(X) _simd_u8x64_fill_scalar_safe(X)
	#define _simd_u8x64_fill_scalar_enable() true
#endif

