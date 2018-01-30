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

static _simd_f64x1 ANVIL_SIMD_CALL _simd_f64x2_sum_safe(const register _simd_f64x2 x) {
	_simd_f64x1 tmp = static_cast<_simd_f64x1>(0);
	for(int i = 0; i < 2; ++i) tmp += reinterpret_cast<_simd_f64x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_f64x2_sum_
	#define _simd_f64x2_sum(X) _simd_f64x2_sum_(X);
	#define _simd_f64x2_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_sum_instruction_set>()
#elif defined(_simd_f64x1_add_)
	#define _simd_f64x2_sum(X) _simd_f64x2_sum(X) _simd_f64x1_sum(_simd_f64x1_add_(\
		_simd_f64x2_splitlo(X), _simd_f64x2_splithi(X)))d
	#define _simd_f64x2_sum_enable() (_simd_f64x1_add_enable() && _simd_f64x1_sum_enable() && _simd_f64x2_splitlo_enable() && _simd_f64x2_splithi_enable())
#else
	#define _simd_f64x2_sum(X) _simd_f64x2_sum_safe(X);
	#define _simd_f64x2_sum_enable() true
#endif

static _simd_f64x1 ANVIL_SIMD_CALL _simd_f64x4_sum_safe(const register _simd_f64x4 x) {
	_simd_f64x1 tmp = static_cast<_simd_f64x1>(0);
	for(int i = 0; i < 4; ++i) tmp += reinterpret_cast<_simd_f64x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_f64x4_sum_
	#define _simd_f64x4_sum(X) _simd_f64x4_sum_(X);
	#define _simd_f64x4_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_sum_instruction_set>()
#elif defined(_simd_f64x2_add_)
	#define _simd_f64x4_sum(X) _simd_f64x4_sum(X) _simd_f64x2_sum(_simd_f64x2_add_(\
		_simd_f64x4_splitlo(X), _simd_f64x4_splithi(X)))d
	#define _simd_f64x4_sum_enable() (_simd_f64x2_add_enable() && _simd_f64x2_sum_enable() && _simd_f64x2_splitlo_enable() && _simd_f64x2_splithi_enable())
#else
	#define _simd_f64x4_sum(X) _simd_f64x4_sum_safe(X);
	#define _simd_f64x4_sum_enable() true
#endif

static _simd_f64x1 ANVIL_SIMD_CALL _simd_f64x8_sum_safe(const register _simd_f64x8 x) {
	_simd_f64x1 tmp = static_cast<_simd_f64x1>(0);
	for(int i = 0; i < 8; ++i) tmp += reinterpret_cast<_simd_f64x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_f64x8_sum_
	#define _simd_f64x8_sum(X) _simd_f64x8_sum_(X);
	#define _simd_f64x8_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_sum_instruction_set>()
#elif defined(_simd_f64x4_add_)
	#define _simd_f64x8_sum(X) _simd_f64x8_sum(X) _simd_f64x4_sum(_simd_f64x4_add_(\
		_simd_f64x8_splitlo(X), _simd_f64x8_splithi(X)))d
	#define _simd_f64x8_sum_enable() (_simd_f64x4_add_enable() && _simd_f64x4_sum_enable() && _simd_f64x2_splitlo_enable() && _simd_f64x2_splithi_enable())
#else
	#define _simd_f64x8_sum(X) _simd_f64x8_sum_safe(X);
	#define _simd_f64x8_sum_enable() true
#endif

static _simd_f64x1 ANVIL_SIMD_CALL _simd_f64x16_sum_safe(const register _simd_f64x16 x) {
	_simd_f64x1 tmp = static_cast<_simd_f64x1>(0);
	for(int i = 0; i < 16; ++i) tmp += reinterpret_cast<_simd_f64x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_f64x16_sum_
	#define _simd_f64x16_sum(X) _simd_f64x16_sum_(X);
	#define _simd_f64x16_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_sum_instruction_set>()
#elif defined(_simd_f64x8_add_)
	#define _simd_f64x16_sum(X) _simd_f64x16_sum(X) _simd_f64x8_sum(_simd_f64x8_add_(\
		_simd_f64x16_splitlo(X), _simd_f64x16_splithi(X)))d
	#define _simd_f64x16_sum_enable() (_simd_f64x8_add_enable() && _simd_f64x8_sum_enable() && _simd_f64x2_splitlo_enable() && _simd_f64x2_splithi_enable())
#else
	#define _simd_f64x16_sum(X) _simd_f64x16_sum_safe(X);
	#define _simd_f64x16_sum_enable() true
#endif

static _simd_f64x1 ANVIL_SIMD_CALL _simd_f64x32_sum_safe(const register _simd_f64x32 x) {
	_simd_f64x1 tmp = static_cast<_simd_f64x1>(0);
	for(int i = 0; i < 32; ++i) tmp += reinterpret_cast<_simd_f64x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_f64x32_sum_
	#define _simd_f64x32_sum(X) _simd_f64x32_sum_(X);
	#define _simd_f64x32_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_sum_instruction_set>()
#elif defined(_simd_f64x16_add_)
	#define _simd_f64x32_sum(X) _simd_f64x32_sum(X) _simd_f64x16_sum(_simd_f64x16_add_(\
		_simd_f64x32_splitlo(X), _simd_f64x32_splithi(X)))d
	#define _simd_f64x32_sum_enable() (_simd_f64x16_add_enable() && _simd_f64x16_sum_enable() && _simd_f64x2_splitlo_enable() && _simd_f64x2_splithi_enable())
#else
	#define _simd_f64x32_sum(X) _simd_f64x32_sum_safe(X);
	#define _simd_f64x32_sum_enable() true
#endif

static _simd_f64x1 ANVIL_SIMD_CALL _simd_f64x64_sum_safe(const register _simd_f64x64 x) {
	_simd_f64x1 tmp = static_cast<_simd_f64x1>(0);
	for(int i = 0; i < 64; ++i) tmp += reinterpret_cast<_simd_f64x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_f64x64_sum_
	#define _simd_f64x64_sum(X) _simd_f64x64_sum_(X);
	#define _simd_f64x64_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_sum_instruction_set>()
#elif defined(_simd_f64x32_add_)
	#define _simd_f64x64_sum(X) _simd_f64x64_sum(X) _simd_f64x32_sum(_simd_f64x32_add_(\
		_simd_f64x64_splitlo(X), _simd_f64x64_splithi(X)))d
	#define _simd_f64x64_sum_enable() (_simd_f64x32_add_enable() && _simd_f64x32_sum_enable() && _simd_f64x2_splitlo_enable() && _simd_f64x2_splithi_enable())
#else
	#define _simd_f64x64_sum(X) _simd_f64x64_sum_safe(X);
	#define _simd_f64x64_sum_enable() true
#endif

static _simd_f32x1 ANVIL_SIMD_CALL _simd_f32x2_sum_safe(const register _simd_f32x2 x) {
	_simd_f32x1 tmp = static_cast<_simd_f32x1>(0);
	for(int i = 0; i < 2; ++i) tmp += reinterpret_cast<_simd_f32x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_f32x2_sum_
	#define _simd_f32x2_sum(X) _simd_f32x2_sum_(X);
	#define _simd_f32x2_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_sum_instruction_set>()
#elif defined(_simd_f32x1_add_)
	#define _simd_f32x2_sum(X) _simd_f32x2_sum(X) _simd_f32x1_sum(_simd_f32x1_add_(\
		_simd_f32x2_splitlo(X), _simd_f32x2_splithi(X)))d
	#define _simd_f32x2_sum_enable() (_simd_f32x1_add_enable() && _simd_f32x1_sum_enable() && _simd_f32x2_splitlo_enable() && _simd_f32x2_splithi_enable())
#else
	#define _simd_f32x2_sum(X) _simd_f32x2_sum_safe(X);
	#define _simd_f32x2_sum_enable() true
#endif

static _simd_f32x1 ANVIL_SIMD_CALL _simd_f32x4_sum_safe(const register _simd_f32x4 x) {
	_simd_f32x1 tmp = static_cast<_simd_f32x1>(0);
	for(int i = 0; i < 4; ++i) tmp += reinterpret_cast<_simd_f32x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_f32x4_sum_
	#define _simd_f32x4_sum(X) _simd_f32x4_sum_(X);
	#define _simd_f32x4_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_sum_instruction_set>()
#elif defined(_simd_f32x2_add_)
	#define _simd_f32x4_sum(X) _simd_f32x4_sum(X) _simd_f32x2_sum(_simd_f32x2_add_(\
		_simd_f32x4_splitlo(X), _simd_f32x4_splithi(X)))d
	#define _simd_f32x4_sum_enable() (_simd_f32x2_add_enable() && _simd_f32x2_sum_enable() && _simd_f32x2_splitlo_enable() && _simd_f32x2_splithi_enable())
#else
	#define _simd_f32x4_sum(X) _simd_f32x4_sum_safe(X);
	#define _simd_f32x4_sum_enable() true
#endif

static _simd_f32x1 ANVIL_SIMD_CALL _simd_f32x8_sum_safe(const register _simd_f32x8 x) {
	_simd_f32x1 tmp = static_cast<_simd_f32x1>(0);
	for(int i = 0; i < 8; ++i) tmp += reinterpret_cast<_simd_f32x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_f32x8_sum_
	#define _simd_f32x8_sum(X) _simd_f32x8_sum_(X);
	#define _simd_f32x8_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_sum_instruction_set>()
#elif defined(_simd_f32x4_add_)
	#define _simd_f32x8_sum(X) _simd_f32x8_sum(X) _simd_f32x4_sum(_simd_f32x4_add_(\
		_simd_f32x8_splitlo(X), _simd_f32x8_splithi(X)))d
	#define _simd_f32x8_sum_enable() (_simd_f32x4_add_enable() && _simd_f32x4_sum_enable() && _simd_f32x2_splitlo_enable() && _simd_f32x2_splithi_enable())
#else
	#define _simd_f32x8_sum(X) _simd_f32x8_sum_safe(X);
	#define _simd_f32x8_sum_enable() true
#endif

static _simd_f32x1 ANVIL_SIMD_CALL _simd_f32x16_sum_safe(const register _simd_f32x16 x) {
	_simd_f32x1 tmp = static_cast<_simd_f32x1>(0);
	for(int i = 0; i < 16; ++i) tmp += reinterpret_cast<_simd_f32x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_f32x16_sum_
	#define _simd_f32x16_sum(X) _simd_f32x16_sum_(X);
	#define _simd_f32x16_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_sum_instruction_set>()
#elif defined(_simd_f32x8_add_)
	#define _simd_f32x16_sum(X) _simd_f32x16_sum(X) _simd_f32x8_sum(_simd_f32x8_add_(\
		_simd_f32x16_splitlo(X), _simd_f32x16_splithi(X)))d
	#define _simd_f32x16_sum_enable() (_simd_f32x8_add_enable() && _simd_f32x8_sum_enable() && _simd_f32x2_splitlo_enable() && _simd_f32x2_splithi_enable())
#else
	#define _simd_f32x16_sum(X) _simd_f32x16_sum_safe(X);
	#define _simd_f32x16_sum_enable() true
#endif

static _simd_f32x1 ANVIL_SIMD_CALL _simd_f32x32_sum_safe(const register _simd_f32x32 x) {
	_simd_f32x1 tmp = static_cast<_simd_f32x1>(0);
	for(int i = 0; i < 32; ++i) tmp += reinterpret_cast<_simd_f32x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_f32x32_sum_
	#define _simd_f32x32_sum(X) _simd_f32x32_sum_(X);
	#define _simd_f32x32_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_sum_instruction_set>()
#elif defined(_simd_f32x16_add_)
	#define _simd_f32x32_sum(X) _simd_f32x32_sum(X) _simd_f32x16_sum(_simd_f32x16_add_(\
		_simd_f32x32_splitlo(X), _simd_f32x32_splithi(X)))d
	#define _simd_f32x32_sum_enable() (_simd_f32x16_add_enable() && _simd_f32x16_sum_enable() && _simd_f32x2_splitlo_enable() && _simd_f32x2_splithi_enable())
#else
	#define _simd_f32x32_sum(X) _simd_f32x32_sum_safe(X);
	#define _simd_f32x32_sum_enable() true
#endif

static _simd_f32x1 ANVIL_SIMD_CALL _simd_f32x64_sum_safe(const register _simd_f32x64 x) {
	_simd_f32x1 tmp = static_cast<_simd_f32x1>(0);
	for(int i = 0; i < 64; ++i) tmp += reinterpret_cast<_simd_f32x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_f32x64_sum_
	#define _simd_f32x64_sum(X) _simd_f32x64_sum_(X);
	#define _simd_f32x64_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_sum_instruction_set>()
#elif defined(_simd_f32x32_add_)
	#define _simd_f32x64_sum(X) _simd_f32x64_sum(X) _simd_f32x32_sum(_simd_f32x32_add_(\
		_simd_f32x64_splitlo(X), _simd_f32x64_splithi(X)))d
	#define _simd_f32x64_sum_enable() (_simd_f32x32_add_enable() && _simd_f32x32_sum_enable() && _simd_f32x2_splitlo_enable() && _simd_f32x2_splithi_enable())
#else
	#define _simd_f32x64_sum(X) _simd_f32x64_sum_safe(X);
	#define _simd_f32x64_sum_enable() true
#endif

static _simd_s64x1 ANVIL_SIMD_CALL _simd_s64x2_sum_safe(const register _simd_s64x2 x) {
	_simd_s64x1 tmp = static_cast<_simd_s64x1>(0);
	for(int i = 0; i < 2; ++i) tmp += reinterpret_cast<_simd_s64x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_s64x2_sum_
	#define _simd_s64x2_sum(X) _simd_s64x2_sum_(X);
	#define _simd_s64x2_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_sum_instruction_set>()
#elif defined(_simd_s64x1_add_)
	#define _simd_s64x2_sum(X) _simd_s64x2_sum(X) _simd_s64x1_sum(_simd_s64x1_add_(\
		_simd_s64x2_splitlo(X), _simd_s64x2_splithi(X)))d
	#define _simd_s64x2_sum_enable() (_simd_s64x1_add_enable() && _simd_s64x1_sum_enable() && _simd_s64x2_splitlo_enable() && _simd_s64x2_splithi_enable())
#else
	#define _simd_s64x2_sum(X) _simd_s64x2_sum_safe(X);
	#define _simd_s64x2_sum_enable() true
#endif

static _simd_s64x1 ANVIL_SIMD_CALL _simd_s64x4_sum_safe(const register _simd_s64x4 x) {
	_simd_s64x1 tmp = static_cast<_simd_s64x1>(0);
	for(int i = 0; i < 4; ++i) tmp += reinterpret_cast<_simd_s64x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_s64x4_sum_
	#define _simd_s64x4_sum(X) _simd_s64x4_sum_(X);
	#define _simd_s64x4_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_sum_instruction_set>()
#elif defined(_simd_s64x2_add_)
	#define _simd_s64x4_sum(X) _simd_s64x4_sum(X) _simd_s64x2_sum(_simd_s64x2_add_(\
		_simd_s64x4_splitlo(X), _simd_s64x4_splithi(X)))d
	#define _simd_s64x4_sum_enable() (_simd_s64x2_add_enable() && _simd_s64x2_sum_enable() && _simd_s64x2_splitlo_enable() && _simd_s64x2_splithi_enable())
#else
	#define _simd_s64x4_sum(X) _simd_s64x4_sum_safe(X);
	#define _simd_s64x4_sum_enable() true
#endif

static _simd_s64x1 ANVIL_SIMD_CALL _simd_s64x8_sum_safe(const register _simd_s64x8 x) {
	_simd_s64x1 tmp = static_cast<_simd_s64x1>(0);
	for(int i = 0; i < 8; ++i) tmp += reinterpret_cast<_simd_s64x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_s64x8_sum_
	#define _simd_s64x8_sum(X) _simd_s64x8_sum_(X);
	#define _simd_s64x8_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_sum_instruction_set>()
#elif defined(_simd_s64x4_add_)
	#define _simd_s64x8_sum(X) _simd_s64x8_sum(X) _simd_s64x4_sum(_simd_s64x4_add_(\
		_simd_s64x8_splitlo(X), _simd_s64x8_splithi(X)))d
	#define _simd_s64x8_sum_enable() (_simd_s64x4_add_enable() && _simd_s64x4_sum_enable() && _simd_s64x2_splitlo_enable() && _simd_s64x2_splithi_enable())
#else
	#define _simd_s64x8_sum(X) _simd_s64x8_sum_safe(X);
	#define _simd_s64x8_sum_enable() true
#endif

static _simd_s64x1 ANVIL_SIMD_CALL _simd_s64x16_sum_safe(const register _simd_s64x16 x) {
	_simd_s64x1 tmp = static_cast<_simd_s64x1>(0);
	for(int i = 0; i < 16; ++i) tmp += reinterpret_cast<_simd_s64x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_s64x16_sum_
	#define _simd_s64x16_sum(X) _simd_s64x16_sum_(X);
	#define _simd_s64x16_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_sum_instruction_set>()
#elif defined(_simd_s64x8_add_)
	#define _simd_s64x16_sum(X) _simd_s64x16_sum(X) _simd_s64x8_sum(_simd_s64x8_add_(\
		_simd_s64x16_splitlo(X), _simd_s64x16_splithi(X)))d
	#define _simd_s64x16_sum_enable() (_simd_s64x8_add_enable() && _simd_s64x8_sum_enable() && _simd_s64x2_splitlo_enable() && _simd_s64x2_splithi_enable())
#else
	#define _simd_s64x16_sum(X) _simd_s64x16_sum_safe(X);
	#define _simd_s64x16_sum_enable() true
#endif

static _simd_s64x1 ANVIL_SIMD_CALL _simd_s64x32_sum_safe(const register _simd_s64x32 x) {
	_simd_s64x1 tmp = static_cast<_simd_s64x1>(0);
	for(int i = 0; i < 32; ++i) tmp += reinterpret_cast<_simd_s64x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_s64x32_sum_
	#define _simd_s64x32_sum(X) _simd_s64x32_sum_(X);
	#define _simd_s64x32_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_sum_instruction_set>()
#elif defined(_simd_s64x16_add_)
	#define _simd_s64x32_sum(X) _simd_s64x32_sum(X) _simd_s64x16_sum(_simd_s64x16_add_(\
		_simd_s64x32_splitlo(X), _simd_s64x32_splithi(X)))d
	#define _simd_s64x32_sum_enable() (_simd_s64x16_add_enable() && _simd_s64x16_sum_enable() && _simd_s64x2_splitlo_enable() && _simd_s64x2_splithi_enable())
#else
	#define _simd_s64x32_sum(X) _simd_s64x32_sum_safe(X);
	#define _simd_s64x32_sum_enable() true
#endif

static _simd_s64x1 ANVIL_SIMD_CALL _simd_s64x64_sum_safe(const register _simd_s64x64 x) {
	_simd_s64x1 tmp = static_cast<_simd_s64x1>(0);
	for(int i = 0; i < 64; ++i) tmp += reinterpret_cast<_simd_s64x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_s64x64_sum_
	#define _simd_s64x64_sum(X) _simd_s64x64_sum_(X);
	#define _simd_s64x64_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_sum_instruction_set>()
#elif defined(_simd_s64x32_add_)
	#define _simd_s64x64_sum(X) _simd_s64x64_sum(X) _simd_s64x32_sum(_simd_s64x32_add_(\
		_simd_s64x64_splitlo(X), _simd_s64x64_splithi(X)))d
	#define _simd_s64x64_sum_enable() (_simd_s64x32_add_enable() && _simd_s64x32_sum_enable() && _simd_s64x2_splitlo_enable() && _simd_s64x2_splithi_enable())
#else
	#define _simd_s64x64_sum(X) _simd_s64x64_sum_safe(X);
	#define _simd_s64x64_sum_enable() true
#endif

static _simd_u64x1 ANVIL_SIMD_CALL _simd_u64x2_sum_safe(const register _simd_u64x2 x) {
	_simd_u64x1 tmp = static_cast<_simd_u64x1>(0);
	for(int i = 0; i < 2; ++i) tmp += reinterpret_cast<_simd_u64x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_u64x2_sum_
	#define _simd_u64x2_sum(X) _simd_u64x2_sum_(X);
	#define _simd_u64x2_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_sum_instruction_set>()
#elif defined(_simd_u64x1_add_)
	#define _simd_u64x2_sum(X) _simd_u64x2_sum(X) _simd_u64x1_sum(_simd_u64x1_add_(\
		_simd_u64x2_splitlo(X), _simd_u64x2_splithi(X)))d
	#define _simd_u64x2_sum_enable() (_simd_u64x1_add_enable() && _simd_u64x1_sum_enable() && _simd_u64x2_splitlo_enable() && _simd_u64x2_splithi_enable())
#else
	#define _simd_u64x2_sum(X) _simd_u64x2_sum_safe(X);
	#define _simd_u64x2_sum_enable() true
#endif

static _simd_u64x1 ANVIL_SIMD_CALL _simd_u64x4_sum_safe(const register _simd_u64x4 x) {
	_simd_u64x1 tmp = static_cast<_simd_u64x1>(0);
	for(int i = 0; i < 4; ++i) tmp += reinterpret_cast<_simd_u64x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_u64x4_sum_
	#define _simd_u64x4_sum(X) _simd_u64x4_sum_(X);
	#define _simd_u64x4_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_sum_instruction_set>()
#elif defined(_simd_u64x2_add_)
	#define _simd_u64x4_sum(X) _simd_u64x4_sum(X) _simd_u64x2_sum(_simd_u64x2_add_(\
		_simd_u64x4_splitlo(X), _simd_u64x4_splithi(X)))d
	#define _simd_u64x4_sum_enable() (_simd_u64x2_add_enable() && _simd_u64x2_sum_enable() && _simd_u64x2_splitlo_enable() && _simd_u64x2_splithi_enable())
#else
	#define _simd_u64x4_sum(X) _simd_u64x4_sum_safe(X);
	#define _simd_u64x4_sum_enable() true
#endif

static _simd_u64x1 ANVIL_SIMD_CALL _simd_u64x8_sum_safe(const register _simd_u64x8 x) {
	_simd_u64x1 tmp = static_cast<_simd_u64x1>(0);
	for(int i = 0; i < 8; ++i) tmp += reinterpret_cast<_simd_u64x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_u64x8_sum_
	#define _simd_u64x8_sum(X) _simd_u64x8_sum_(X);
	#define _simd_u64x8_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_sum_instruction_set>()
#elif defined(_simd_u64x4_add_)
	#define _simd_u64x8_sum(X) _simd_u64x8_sum(X) _simd_u64x4_sum(_simd_u64x4_add_(\
		_simd_u64x8_splitlo(X), _simd_u64x8_splithi(X)))d
	#define _simd_u64x8_sum_enable() (_simd_u64x4_add_enable() && _simd_u64x4_sum_enable() && _simd_u64x2_splitlo_enable() && _simd_u64x2_splithi_enable())
#else
	#define _simd_u64x8_sum(X) _simd_u64x8_sum_safe(X);
	#define _simd_u64x8_sum_enable() true
#endif

static _simd_u64x1 ANVIL_SIMD_CALL _simd_u64x16_sum_safe(const register _simd_u64x16 x) {
	_simd_u64x1 tmp = static_cast<_simd_u64x1>(0);
	for(int i = 0; i < 16; ++i) tmp += reinterpret_cast<_simd_u64x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_u64x16_sum_
	#define _simd_u64x16_sum(X) _simd_u64x16_sum_(X);
	#define _simd_u64x16_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_sum_instruction_set>()
#elif defined(_simd_u64x8_add_)
	#define _simd_u64x16_sum(X) _simd_u64x16_sum(X) _simd_u64x8_sum(_simd_u64x8_add_(\
		_simd_u64x16_splitlo(X), _simd_u64x16_splithi(X)))d
	#define _simd_u64x16_sum_enable() (_simd_u64x8_add_enable() && _simd_u64x8_sum_enable() && _simd_u64x2_splitlo_enable() && _simd_u64x2_splithi_enable())
#else
	#define _simd_u64x16_sum(X) _simd_u64x16_sum_safe(X);
	#define _simd_u64x16_sum_enable() true
#endif

static _simd_u64x1 ANVIL_SIMD_CALL _simd_u64x32_sum_safe(const register _simd_u64x32 x) {
	_simd_u64x1 tmp = static_cast<_simd_u64x1>(0);
	for(int i = 0; i < 32; ++i) tmp += reinterpret_cast<_simd_u64x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_u64x32_sum_
	#define _simd_u64x32_sum(X) _simd_u64x32_sum_(X);
	#define _simd_u64x32_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_sum_instruction_set>()
#elif defined(_simd_u64x16_add_)
	#define _simd_u64x32_sum(X) _simd_u64x32_sum(X) _simd_u64x16_sum(_simd_u64x16_add_(\
		_simd_u64x32_splitlo(X), _simd_u64x32_splithi(X)))d
	#define _simd_u64x32_sum_enable() (_simd_u64x16_add_enable() && _simd_u64x16_sum_enable() && _simd_u64x2_splitlo_enable() && _simd_u64x2_splithi_enable())
#else
	#define _simd_u64x32_sum(X) _simd_u64x32_sum_safe(X);
	#define _simd_u64x32_sum_enable() true
#endif

static _simd_u64x1 ANVIL_SIMD_CALL _simd_u64x64_sum_safe(const register _simd_u64x64 x) {
	_simd_u64x1 tmp = static_cast<_simd_u64x1>(0);
	for(int i = 0; i < 64; ++i) tmp += reinterpret_cast<_simd_u64x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_u64x64_sum_
	#define _simd_u64x64_sum(X) _simd_u64x64_sum_(X);
	#define _simd_u64x64_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_sum_instruction_set>()
#elif defined(_simd_u64x32_add_)
	#define _simd_u64x64_sum(X) _simd_u64x64_sum(X) _simd_u64x32_sum(_simd_u64x32_add_(\
		_simd_u64x64_splitlo(X), _simd_u64x64_splithi(X)))d
	#define _simd_u64x64_sum_enable() (_simd_u64x32_add_enable() && _simd_u64x32_sum_enable() && _simd_u64x2_splitlo_enable() && _simd_u64x2_splithi_enable())
#else
	#define _simd_u64x64_sum(X) _simd_u64x64_sum_safe(X);
	#define _simd_u64x64_sum_enable() true
#endif

static _simd_s32x1 ANVIL_SIMD_CALL _simd_s32x2_sum_safe(const register _simd_s32x2 x) {
	_simd_s32x1 tmp = static_cast<_simd_s32x1>(0);
	for(int i = 0; i < 2; ++i) tmp += reinterpret_cast<_simd_s32x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_s32x2_sum_
	#define _simd_s32x2_sum(X) _simd_s32x2_sum_(X);
	#define _simd_s32x2_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_sum_instruction_set>()
#elif defined(_simd_s32x1_add_)
	#define _simd_s32x2_sum(X) _simd_s32x2_sum(X) _simd_s32x1_sum(_simd_s32x1_add_(\
		_simd_s32x2_splitlo(X), _simd_s32x2_splithi(X)))d
	#define _simd_s32x2_sum_enable() (_simd_s32x1_add_enable() && _simd_s32x1_sum_enable() && _simd_s32x2_splitlo_enable() && _simd_s32x2_splithi_enable())
#else
	#define _simd_s32x2_sum(X) _simd_s32x2_sum_safe(X);
	#define _simd_s32x2_sum_enable() true
#endif

static _simd_s32x1 ANVIL_SIMD_CALL _simd_s32x4_sum_safe(const register _simd_s32x4 x) {
	_simd_s32x1 tmp = static_cast<_simd_s32x1>(0);
	for(int i = 0; i < 4; ++i) tmp += reinterpret_cast<_simd_s32x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_s32x4_sum_
	#define _simd_s32x4_sum(X) _simd_s32x4_sum_(X);
	#define _simd_s32x4_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_sum_instruction_set>()
#elif defined(_simd_s32x2_add_)
	#define _simd_s32x4_sum(X) _simd_s32x4_sum(X) _simd_s32x2_sum(_simd_s32x2_add_(\
		_simd_s32x4_splitlo(X), _simd_s32x4_splithi(X)))d
	#define _simd_s32x4_sum_enable() (_simd_s32x2_add_enable() && _simd_s32x2_sum_enable() && _simd_s32x2_splitlo_enable() && _simd_s32x2_splithi_enable())
#else
	#define _simd_s32x4_sum(X) _simd_s32x4_sum_safe(X);
	#define _simd_s32x4_sum_enable() true
#endif

static _simd_s32x1 ANVIL_SIMD_CALL _simd_s32x8_sum_safe(const register _simd_s32x8 x) {
	_simd_s32x1 tmp = static_cast<_simd_s32x1>(0);
	for(int i = 0; i < 8; ++i) tmp += reinterpret_cast<_simd_s32x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_s32x8_sum_
	#define _simd_s32x8_sum(X) _simd_s32x8_sum_(X);
	#define _simd_s32x8_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_sum_instruction_set>()
#elif defined(_simd_s32x4_add_)
	#define _simd_s32x8_sum(X) _simd_s32x8_sum(X) _simd_s32x4_sum(_simd_s32x4_add_(\
		_simd_s32x8_splitlo(X), _simd_s32x8_splithi(X)))d
	#define _simd_s32x8_sum_enable() (_simd_s32x4_add_enable() && _simd_s32x4_sum_enable() && _simd_s32x2_splitlo_enable() && _simd_s32x2_splithi_enable())
#else
	#define _simd_s32x8_sum(X) _simd_s32x8_sum_safe(X);
	#define _simd_s32x8_sum_enable() true
#endif

static _simd_s32x1 ANVIL_SIMD_CALL _simd_s32x16_sum_safe(const register _simd_s32x16 x) {
	_simd_s32x1 tmp = static_cast<_simd_s32x1>(0);
	for(int i = 0; i < 16; ++i) tmp += reinterpret_cast<_simd_s32x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_s32x16_sum_
	#define _simd_s32x16_sum(X) _simd_s32x16_sum_(X);
	#define _simd_s32x16_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_sum_instruction_set>()
#elif defined(_simd_s32x8_add_)
	#define _simd_s32x16_sum(X) _simd_s32x16_sum(X) _simd_s32x8_sum(_simd_s32x8_add_(\
		_simd_s32x16_splitlo(X), _simd_s32x16_splithi(X)))d
	#define _simd_s32x16_sum_enable() (_simd_s32x8_add_enable() && _simd_s32x8_sum_enable() && _simd_s32x2_splitlo_enable() && _simd_s32x2_splithi_enable())
#else
	#define _simd_s32x16_sum(X) _simd_s32x16_sum_safe(X);
	#define _simd_s32x16_sum_enable() true
#endif

static _simd_s32x1 ANVIL_SIMD_CALL _simd_s32x32_sum_safe(const register _simd_s32x32 x) {
	_simd_s32x1 tmp = static_cast<_simd_s32x1>(0);
	for(int i = 0; i < 32; ++i) tmp += reinterpret_cast<_simd_s32x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_s32x32_sum_
	#define _simd_s32x32_sum(X) _simd_s32x32_sum_(X);
	#define _simd_s32x32_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_sum_instruction_set>()
#elif defined(_simd_s32x16_add_)
	#define _simd_s32x32_sum(X) _simd_s32x32_sum(X) _simd_s32x16_sum(_simd_s32x16_add_(\
		_simd_s32x32_splitlo(X), _simd_s32x32_splithi(X)))d
	#define _simd_s32x32_sum_enable() (_simd_s32x16_add_enable() && _simd_s32x16_sum_enable() && _simd_s32x2_splitlo_enable() && _simd_s32x2_splithi_enable())
#else
	#define _simd_s32x32_sum(X) _simd_s32x32_sum_safe(X);
	#define _simd_s32x32_sum_enable() true
#endif

static _simd_s32x1 ANVIL_SIMD_CALL _simd_s32x64_sum_safe(const register _simd_s32x64 x) {
	_simd_s32x1 tmp = static_cast<_simd_s32x1>(0);
	for(int i = 0; i < 64; ++i) tmp += reinterpret_cast<_simd_s32x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_s32x64_sum_
	#define _simd_s32x64_sum(X) _simd_s32x64_sum_(X);
	#define _simd_s32x64_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_sum_instruction_set>()
#elif defined(_simd_s32x32_add_)
	#define _simd_s32x64_sum(X) _simd_s32x64_sum(X) _simd_s32x32_sum(_simd_s32x32_add_(\
		_simd_s32x64_splitlo(X), _simd_s32x64_splithi(X)))d
	#define _simd_s32x64_sum_enable() (_simd_s32x32_add_enable() && _simd_s32x32_sum_enable() && _simd_s32x2_splitlo_enable() && _simd_s32x2_splithi_enable())
#else
	#define _simd_s32x64_sum(X) _simd_s32x64_sum_safe(X);
	#define _simd_s32x64_sum_enable() true
#endif

static _simd_u32x1 ANVIL_SIMD_CALL _simd_u32x2_sum_safe(const register _simd_u32x2 x) {
	_simd_u32x1 tmp = static_cast<_simd_u32x1>(0);
	for(int i = 0; i < 2; ++i) tmp += reinterpret_cast<_simd_u32x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_u32x2_sum_
	#define _simd_u32x2_sum(X) _simd_u32x2_sum_(X);
	#define _simd_u32x2_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_sum_instruction_set>()
#elif defined(_simd_u32x1_add_)
	#define _simd_u32x2_sum(X) _simd_u32x2_sum(X) _simd_u32x1_sum(_simd_u32x1_add_(\
		_simd_u32x2_splitlo(X), _simd_u32x2_splithi(X)))d
	#define _simd_u32x2_sum_enable() (_simd_u32x1_add_enable() && _simd_u32x1_sum_enable() && _simd_u32x2_splitlo_enable() && _simd_u32x2_splithi_enable())
#else
	#define _simd_u32x2_sum(X) _simd_u32x2_sum_safe(X);
	#define _simd_u32x2_sum_enable() true
#endif

static _simd_u32x1 ANVIL_SIMD_CALL _simd_u32x4_sum_safe(const register _simd_u32x4 x) {
	_simd_u32x1 tmp = static_cast<_simd_u32x1>(0);
	for(int i = 0; i < 4; ++i) tmp += reinterpret_cast<_simd_u32x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_u32x4_sum_
	#define _simd_u32x4_sum(X) _simd_u32x4_sum_(X);
	#define _simd_u32x4_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_sum_instruction_set>()
#elif defined(_simd_u32x2_add_)
	#define _simd_u32x4_sum(X) _simd_u32x4_sum(X) _simd_u32x2_sum(_simd_u32x2_add_(\
		_simd_u32x4_splitlo(X), _simd_u32x4_splithi(X)))d
	#define _simd_u32x4_sum_enable() (_simd_u32x2_add_enable() && _simd_u32x2_sum_enable() && _simd_u32x2_splitlo_enable() && _simd_u32x2_splithi_enable())
#else
	#define _simd_u32x4_sum(X) _simd_u32x4_sum_safe(X);
	#define _simd_u32x4_sum_enable() true
#endif

static _simd_u32x1 ANVIL_SIMD_CALL _simd_u32x8_sum_safe(const register _simd_u32x8 x) {
	_simd_u32x1 tmp = static_cast<_simd_u32x1>(0);
	for(int i = 0; i < 8; ++i) tmp += reinterpret_cast<_simd_u32x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_u32x8_sum_
	#define _simd_u32x8_sum(X) _simd_u32x8_sum_(X);
	#define _simd_u32x8_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_sum_instruction_set>()
#elif defined(_simd_u32x4_add_)
	#define _simd_u32x8_sum(X) _simd_u32x8_sum(X) _simd_u32x4_sum(_simd_u32x4_add_(\
		_simd_u32x8_splitlo(X), _simd_u32x8_splithi(X)))d
	#define _simd_u32x8_sum_enable() (_simd_u32x4_add_enable() && _simd_u32x4_sum_enable() && _simd_u32x2_splitlo_enable() && _simd_u32x2_splithi_enable())
#else
	#define _simd_u32x8_sum(X) _simd_u32x8_sum_safe(X);
	#define _simd_u32x8_sum_enable() true
#endif

static _simd_u32x1 ANVIL_SIMD_CALL _simd_u32x16_sum_safe(const register _simd_u32x16 x) {
	_simd_u32x1 tmp = static_cast<_simd_u32x1>(0);
	for(int i = 0; i < 16; ++i) tmp += reinterpret_cast<_simd_u32x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_u32x16_sum_
	#define _simd_u32x16_sum(X) _simd_u32x16_sum_(X);
	#define _simd_u32x16_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_sum_instruction_set>()
#elif defined(_simd_u32x8_add_)
	#define _simd_u32x16_sum(X) _simd_u32x16_sum(X) _simd_u32x8_sum(_simd_u32x8_add_(\
		_simd_u32x16_splitlo(X), _simd_u32x16_splithi(X)))d
	#define _simd_u32x16_sum_enable() (_simd_u32x8_add_enable() && _simd_u32x8_sum_enable() && _simd_u32x2_splitlo_enable() && _simd_u32x2_splithi_enable())
#else
	#define _simd_u32x16_sum(X) _simd_u32x16_sum_safe(X);
	#define _simd_u32x16_sum_enable() true
#endif

static _simd_u32x1 ANVIL_SIMD_CALL _simd_u32x32_sum_safe(const register _simd_u32x32 x) {
	_simd_u32x1 tmp = static_cast<_simd_u32x1>(0);
	for(int i = 0; i < 32; ++i) tmp += reinterpret_cast<_simd_u32x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_u32x32_sum_
	#define _simd_u32x32_sum(X) _simd_u32x32_sum_(X);
	#define _simd_u32x32_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_sum_instruction_set>()
#elif defined(_simd_u32x16_add_)
	#define _simd_u32x32_sum(X) _simd_u32x32_sum(X) _simd_u32x16_sum(_simd_u32x16_add_(\
		_simd_u32x32_splitlo(X), _simd_u32x32_splithi(X)))d
	#define _simd_u32x32_sum_enable() (_simd_u32x16_add_enable() && _simd_u32x16_sum_enable() && _simd_u32x2_splitlo_enable() && _simd_u32x2_splithi_enable())
#else
	#define _simd_u32x32_sum(X) _simd_u32x32_sum_safe(X);
	#define _simd_u32x32_sum_enable() true
#endif

static _simd_u32x1 ANVIL_SIMD_CALL _simd_u32x64_sum_safe(const register _simd_u32x64 x) {
	_simd_u32x1 tmp = static_cast<_simd_u32x1>(0);
	for(int i = 0; i < 64; ++i) tmp += reinterpret_cast<_simd_u32x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_u32x64_sum_
	#define _simd_u32x64_sum(X) _simd_u32x64_sum_(X);
	#define _simd_u32x64_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_sum_instruction_set>()
#elif defined(_simd_u32x32_add_)
	#define _simd_u32x64_sum(X) _simd_u32x64_sum(X) _simd_u32x32_sum(_simd_u32x32_add_(\
		_simd_u32x64_splitlo(X), _simd_u32x64_splithi(X)))d
	#define _simd_u32x64_sum_enable() (_simd_u32x32_add_enable() && _simd_u32x32_sum_enable() && _simd_u32x2_splitlo_enable() && _simd_u32x2_splithi_enable())
#else
	#define _simd_u32x64_sum(X) _simd_u32x64_sum_safe(X);
	#define _simd_u32x64_sum_enable() true
#endif

static _simd_s16x1 ANVIL_SIMD_CALL _simd_s16x2_sum_safe(const register _simd_s16x2 x) {
	_simd_s16x1 tmp = static_cast<_simd_s16x1>(0);
	for(int i = 0; i < 2; ++i) tmp += reinterpret_cast<_simd_s16x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_s16x2_sum_
	#define _simd_s16x2_sum(X) _simd_s16x2_sum_(X);
	#define _simd_s16x2_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_sum_instruction_set>()
#elif defined(_simd_s16x1_add_)
	#define _simd_s16x2_sum(X) _simd_s16x2_sum(X) _simd_s16x1_sum(_simd_s16x1_add_(\
		_simd_s16x2_splitlo(X), _simd_s16x2_splithi(X)))d
	#define _simd_s16x2_sum_enable() (_simd_s16x1_add_enable() && _simd_s16x1_sum_enable() && _simd_s16x2_splitlo_enable() && _simd_s16x2_splithi_enable())
#else
	#define _simd_s16x2_sum(X) _simd_s16x2_sum_safe(X);
	#define _simd_s16x2_sum_enable() true
#endif

static _simd_s16x1 ANVIL_SIMD_CALL _simd_s16x4_sum_safe(const register _simd_s16x4 x) {
	_simd_s16x1 tmp = static_cast<_simd_s16x1>(0);
	for(int i = 0; i < 4; ++i) tmp += reinterpret_cast<_simd_s16x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_s16x4_sum_
	#define _simd_s16x4_sum(X) _simd_s16x4_sum_(X);
	#define _simd_s16x4_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_sum_instruction_set>()
#elif defined(_simd_s16x2_add_)
	#define _simd_s16x4_sum(X) _simd_s16x4_sum(X) _simd_s16x2_sum(_simd_s16x2_add_(\
		_simd_s16x4_splitlo(X), _simd_s16x4_splithi(X)))d
	#define _simd_s16x4_sum_enable() (_simd_s16x2_add_enable() && _simd_s16x2_sum_enable() && _simd_s16x2_splitlo_enable() && _simd_s16x2_splithi_enable())
#else
	#define _simd_s16x4_sum(X) _simd_s16x4_sum_safe(X);
	#define _simd_s16x4_sum_enable() true
#endif

static _simd_s16x1 ANVIL_SIMD_CALL _simd_s16x8_sum_safe(const register _simd_s16x8 x) {
	_simd_s16x1 tmp = static_cast<_simd_s16x1>(0);
	for(int i = 0; i < 8; ++i) tmp += reinterpret_cast<_simd_s16x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_s16x8_sum_
	#define _simd_s16x8_sum(X) _simd_s16x8_sum_(X);
	#define _simd_s16x8_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_sum_instruction_set>()
#elif defined(_simd_s16x4_add_)
	#define _simd_s16x8_sum(X) _simd_s16x8_sum(X) _simd_s16x4_sum(_simd_s16x4_add_(\
		_simd_s16x8_splitlo(X), _simd_s16x8_splithi(X)))d
	#define _simd_s16x8_sum_enable() (_simd_s16x4_add_enable() && _simd_s16x4_sum_enable() && _simd_s16x2_splitlo_enable() && _simd_s16x2_splithi_enable())
#else
	#define _simd_s16x8_sum(X) _simd_s16x8_sum_safe(X);
	#define _simd_s16x8_sum_enable() true
#endif

static _simd_s16x1 ANVIL_SIMD_CALL _simd_s16x16_sum_safe(const register _simd_s16x16 x) {
	_simd_s16x1 tmp = static_cast<_simd_s16x1>(0);
	for(int i = 0; i < 16; ++i) tmp += reinterpret_cast<_simd_s16x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_s16x16_sum_
	#define _simd_s16x16_sum(X) _simd_s16x16_sum_(X);
	#define _simd_s16x16_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_sum_instruction_set>()
#elif defined(_simd_s16x8_add_)
	#define _simd_s16x16_sum(X) _simd_s16x16_sum(X) _simd_s16x8_sum(_simd_s16x8_add_(\
		_simd_s16x16_splitlo(X), _simd_s16x16_splithi(X)))d
	#define _simd_s16x16_sum_enable() (_simd_s16x8_add_enable() && _simd_s16x8_sum_enable() && _simd_s16x2_splitlo_enable() && _simd_s16x2_splithi_enable())
#else
	#define _simd_s16x16_sum(X) _simd_s16x16_sum_safe(X);
	#define _simd_s16x16_sum_enable() true
#endif

static _simd_s16x1 ANVIL_SIMD_CALL _simd_s16x32_sum_safe(const register _simd_s16x32 x) {
	_simd_s16x1 tmp = static_cast<_simd_s16x1>(0);
	for(int i = 0; i < 32; ++i) tmp += reinterpret_cast<_simd_s16x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_s16x32_sum_
	#define _simd_s16x32_sum(X) _simd_s16x32_sum_(X);
	#define _simd_s16x32_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_sum_instruction_set>()
#elif defined(_simd_s16x16_add_)
	#define _simd_s16x32_sum(X) _simd_s16x32_sum(X) _simd_s16x16_sum(_simd_s16x16_add_(\
		_simd_s16x32_splitlo(X), _simd_s16x32_splithi(X)))d
	#define _simd_s16x32_sum_enable() (_simd_s16x16_add_enable() && _simd_s16x16_sum_enable() && _simd_s16x2_splitlo_enable() && _simd_s16x2_splithi_enable())
#else
	#define _simd_s16x32_sum(X) _simd_s16x32_sum_safe(X);
	#define _simd_s16x32_sum_enable() true
#endif

static _simd_s16x1 ANVIL_SIMD_CALL _simd_s16x64_sum_safe(const register _simd_s16x64 x) {
	_simd_s16x1 tmp = static_cast<_simd_s16x1>(0);
	for(int i = 0; i < 64; ++i) tmp += reinterpret_cast<_simd_s16x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_s16x64_sum_
	#define _simd_s16x64_sum(X) _simd_s16x64_sum_(X);
	#define _simd_s16x64_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_sum_instruction_set>()
#elif defined(_simd_s16x32_add_)
	#define _simd_s16x64_sum(X) _simd_s16x64_sum(X) _simd_s16x32_sum(_simd_s16x32_add_(\
		_simd_s16x64_splitlo(X), _simd_s16x64_splithi(X)))d
	#define _simd_s16x64_sum_enable() (_simd_s16x32_add_enable() && _simd_s16x32_sum_enable() && _simd_s16x2_splitlo_enable() && _simd_s16x2_splithi_enable())
#else
	#define _simd_s16x64_sum(X) _simd_s16x64_sum_safe(X);
	#define _simd_s16x64_sum_enable() true
#endif

static _simd_u16x1 ANVIL_SIMD_CALL _simd_u16x2_sum_safe(const register _simd_u16x2 x) {
	_simd_u16x1 tmp = static_cast<_simd_u16x1>(0);
	for(int i = 0; i < 2; ++i) tmp += reinterpret_cast<_simd_u16x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_u16x2_sum_
	#define _simd_u16x2_sum(X) _simd_u16x2_sum_(X);
	#define _simd_u16x2_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_sum_instruction_set>()
#elif defined(_simd_u16x1_add_)
	#define _simd_u16x2_sum(X) _simd_u16x2_sum(X) _simd_u16x1_sum(_simd_u16x1_add_(\
		_simd_u16x2_splitlo(X), _simd_u16x2_splithi(X)))d
	#define _simd_u16x2_sum_enable() (_simd_u16x1_add_enable() && _simd_u16x1_sum_enable() && _simd_u16x2_splitlo_enable() && _simd_u16x2_splithi_enable())
#else
	#define _simd_u16x2_sum(X) _simd_u16x2_sum_safe(X);
	#define _simd_u16x2_sum_enable() true
#endif

static _simd_u16x1 ANVIL_SIMD_CALL _simd_u16x4_sum_safe(const register _simd_u16x4 x) {
	_simd_u16x1 tmp = static_cast<_simd_u16x1>(0);
	for(int i = 0; i < 4; ++i) tmp += reinterpret_cast<_simd_u16x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_u16x4_sum_
	#define _simd_u16x4_sum(X) _simd_u16x4_sum_(X);
	#define _simd_u16x4_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_sum_instruction_set>()
#elif defined(_simd_u16x2_add_)
	#define _simd_u16x4_sum(X) _simd_u16x4_sum(X) _simd_u16x2_sum(_simd_u16x2_add_(\
		_simd_u16x4_splitlo(X), _simd_u16x4_splithi(X)))d
	#define _simd_u16x4_sum_enable() (_simd_u16x2_add_enable() && _simd_u16x2_sum_enable() && _simd_u16x2_splitlo_enable() && _simd_u16x2_splithi_enable())
#else
	#define _simd_u16x4_sum(X) _simd_u16x4_sum_safe(X);
	#define _simd_u16x4_sum_enable() true
#endif

static _simd_u16x1 ANVIL_SIMD_CALL _simd_u16x8_sum_safe(const register _simd_u16x8 x) {
	_simd_u16x1 tmp = static_cast<_simd_u16x1>(0);
	for(int i = 0; i < 8; ++i) tmp += reinterpret_cast<_simd_u16x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_u16x8_sum_
	#define _simd_u16x8_sum(X) _simd_u16x8_sum_(X);
	#define _simd_u16x8_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_sum_instruction_set>()
#elif defined(_simd_u16x4_add_)
	#define _simd_u16x8_sum(X) _simd_u16x8_sum(X) _simd_u16x4_sum(_simd_u16x4_add_(\
		_simd_u16x8_splitlo(X), _simd_u16x8_splithi(X)))d
	#define _simd_u16x8_sum_enable() (_simd_u16x4_add_enable() && _simd_u16x4_sum_enable() && _simd_u16x2_splitlo_enable() && _simd_u16x2_splithi_enable())
#else
	#define _simd_u16x8_sum(X) _simd_u16x8_sum_safe(X);
	#define _simd_u16x8_sum_enable() true
#endif

static _simd_u16x1 ANVIL_SIMD_CALL _simd_u16x16_sum_safe(const register _simd_u16x16 x) {
	_simd_u16x1 tmp = static_cast<_simd_u16x1>(0);
	for(int i = 0; i < 16; ++i) tmp += reinterpret_cast<_simd_u16x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_u16x16_sum_
	#define _simd_u16x16_sum(X) _simd_u16x16_sum_(X);
	#define _simd_u16x16_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_sum_instruction_set>()
#elif defined(_simd_u16x8_add_)
	#define _simd_u16x16_sum(X) _simd_u16x16_sum(X) _simd_u16x8_sum(_simd_u16x8_add_(\
		_simd_u16x16_splitlo(X), _simd_u16x16_splithi(X)))d
	#define _simd_u16x16_sum_enable() (_simd_u16x8_add_enable() && _simd_u16x8_sum_enable() && _simd_u16x2_splitlo_enable() && _simd_u16x2_splithi_enable())
#else
	#define _simd_u16x16_sum(X) _simd_u16x16_sum_safe(X);
	#define _simd_u16x16_sum_enable() true
#endif

static _simd_u16x1 ANVIL_SIMD_CALL _simd_u16x32_sum_safe(const register _simd_u16x32 x) {
	_simd_u16x1 tmp = static_cast<_simd_u16x1>(0);
	for(int i = 0; i < 32; ++i) tmp += reinterpret_cast<_simd_u16x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_u16x32_sum_
	#define _simd_u16x32_sum(X) _simd_u16x32_sum_(X);
	#define _simd_u16x32_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_sum_instruction_set>()
#elif defined(_simd_u16x16_add_)
	#define _simd_u16x32_sum(X) _simd_u16x32_sum(X) _simd_u16x16_sum(_simd_u16x16_add_(\
		_simd_u16x32_splitlo(X), _simd_u16x32_splithi(X)))d
	#define _simd_u16x32_sum_enable() (_simd_u16x16_add_enable() && _simd_u16x16_sum_enable() && _simd_u16x2_splitlo_enable() && _simd_u16x2_splithi_enable())
#else
	#define _simd_u16x32_sum(X) _simd_u16x32_sum_safe(X);
	#define _simd_u16x32_sum_enable() true
#endif

static _simd_u16x1 ANVIL_SIMD_CALL _simd_u16x64_sum_safe(const register _simd_u16x64 x) {
	_simd_u16x1 tmp = static_cast<_simd_u16x1>(0);
	for(int i = 0; i < 64; ++i) tmp += reinterpret_cast<_simd_u16x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_u16x64_sum_
	#define _simd_u16x64_sum(X) _simd_u16x64_sum_(X);
	#define _simd_u16x64_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_sum_instruction_set>()
#elif defined(_simd_u16x32_add_)
	#define _simd_u16x64_sum(X) _simd_u16x64_sum(X) _simd_u16x32_sum(_simd_u16x32_add_(\
		_simd_u16x64_splitlo(X), _simd_u16x64_splithi(X)))d
	#define _simd_u16x64_sum_enable() (_simd_u16x32_add_enable() && _simd_u16x32_sum_enable() && _simd_u16x2_splitlo_enable() && _simd_u16x2_splithi_enable())
#else
	#define _simd_u16x64_sum(X) _simd_u16x64_sum_safe(X);
	#define _simd_u16x64_sum_enable() true
#endif

static _simd_s8x1 ANVIL_SIMD_CALL _simd_s8x2_sum_safe(const register _simd_s8x2 x) {
	_simd_s8x1 tmp = static_cast<_simd_s8x1>(0);
	for(int i = 0; i < 2; ++i) tmp += reinterpret_cast<_simd_s8x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_s8x2_sum_
	#define _simd_s8x2_sum(X) _simd_s8x2_sum_(X);
	#define _simd_s8x2_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_sum_instruction_set>()
#elif defined(_simd_s8x1_add_)
	#define _simd_s8x2_sum(X) _simd_s8x2_sum(X) _simd_s8x1_sum(_simd_s8x1_add_(\
		_simd_s8x2_splitlo(X), _simd_s8x2_splithi(X)))d
	#define _simd_s8x2_sum_enable() (_simd_s8x1_add_enable() && _simd_s8x1_sum_enable() && _simd_s8x2_splitlo_enable() && _simd_s8x2_splithi_enable())
#else
	#define _simd_s8x2_sum(X) _simd_s8x2_sum_safe(X);
	#define _simd_s8x2_sum_enable() true
#endif

static _simd_s8x1 ANVIL_SIMD_CALL _simd_s8x4_sum_safe(const register _simd_s8x4 x) {
	_simd_s8x1 tmp = static_cast<_simd_s8x1>(0);
	for(int i = 0; i < 4; ++i) tmp += reinterpret_cast<_simd_s8x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_s8x4_sum_
	#define _simd_s8x4_sum(X) _simd_s8x4_sum_(X);
	#define _simd_s8x4_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_sum_instruction_set>()
#elif defined(_simd_s8x2_add_)
	#define _simd_s8x4_sum(X) _simd_s8x4_sum(X) _simd_s8x2_sum(_simd_s8x2_add_(\
		_simd_s8x4_splitlo(X), _simd_s8x4_splithi(X)))d
	#define _simd_s8x4_sum_enable() (_simd_s8x2_add_enable() && _simd_s8x2_sum_enable() && _simd_s8x2_splitlo_enable() && _simd_s8x2_splithi_enable())
#else
	#define _simd_s8x4_sum(X) _simd_s8x4_sum_safe(X);
	#define _simd_s8x4_sum_enable() true
#endif

static _simd_s8x1 ANVIL_SIMD_CALL _simd_s8x8_sum_safe(const register _simd_s8x8 x) {
	_simd_s8x1 tmp = static_cast<_simd_s8x1>(0);
	for(int i = 0; i < 8; ++i) tmp += reinterpret_cast<_simd_s8x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_s8x8_sum_
	#define _simd_s8x8_sum(X) _simd_s8x8_sum_(X);
	#define _simd_s8x8_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_sum_instruction_set>()
#elif defined(_simd_s8x4_add_)
	#define _simd_s8x8_sum(X) _simd_s8x8_sum(X) _simd_s8x4_sum(_simd_s8x4_add_(\
		_simd_s8x8_splitlo(X), _simd_s8x8_splithi(X)))d
	#define _simd_s8x8_sum_enable() (_simd_s8x4_add_enable() && _simd_s8x4_sum_enable() && _simd_s8x2_splitlo_enable() && _simd_s8x2_splithi_enable())
#else
	#define _simd_s8x8_sum(X) _simd_s8x8_sum_safe(X);
	#define _simd_s8x8_sum_enable() true
#endif

static _simd_s8x1 ANVIL_SIMD_CALL _simd_s8x16_sum_safe(const register _simd_s8x16 x) {
	_simd_s8x1 tmp = static_cast<_simd_s8x1>(0);
	for(int i = 0; i < 16; ++i) tmp += reinterpret_cast<_simd_s8x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_s8x16_sum_
	#define _simd_s8x16_sum(X) _simd_s8x16_sum_(X);
	#define _simd_s8x16_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_sum_instruction_set>()
#elif defined(_simd_s8x8_add_)
	#define _simd_s8x16_sum(X) _simd_s8x16_sum(X) _simd_s8x8_sum(_simd_s8x8_add_(\
		_simd_s8x16_splitlo(X), _simd_s8x16_splithi(X)))d
	#define _simd_s8x16_sum_enable() (_simd_s8x8_add_enable() && _simd_s8x8_sum_enable() && _simd_s8x2_splitlo_enable() && _simd_s8x2_splithi_enable())
#else
	#define _simd_s8x16_sum(X) _simd_s8x16_sum_safe(X);
	#define _simd_s8x16_sum_enable() true
#endif

static _simd_s8x1 ANVIL_SIMD_CALL _simd_s8x32_sum_safe(const register _simd_s8x32 x) {
	_simd_s8x1 tmp = static_cast<_simd_s8x1>(0);
	for(int i = 0; i < 32; ++i) tmp += reinterpret_cast<_simd_s8x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_s8x32_sum_
	#define _simd_s8x32_sum(X) _simd_s8x32_sum_(X);
	#define _simd_s8x32_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_sum_instruction_set>()
#elif defined(_simd_s8x16_add_)
	#define _simd_s8x32_sum(X) _simd_s8x32_sum(X) _simd_s8x16_sum(_simd_s8x16_add_(\
		_simd_s8x32_splitlo(X), _simd_s8x32_splithi(X)))d
	#define _simd_s8x32_sum_enable() (_simd_s8x16_add_enable() && _simd_s8x16_sum_enable() && _simd_s8x2_splitlo_enable() && _simd_s8x2_splithi_enable())
#else
	#define _simd_s8x32_sum(X) _simd_s8x32_sum_safe(X);
	#define _simd_s8x32_sum_enable() true
#endif

static _simd_s8x1 ANVIL_SIMD_CALL _simd_s8x64_sum_safe(const register _simd_s8x64 x) {
	_simd_s8x1 tmp = static_cast<_simd_s8x1>(0);
	for(int i = 0; i < 64; ++i) tmp += reinterpret_cast<_simd_s8x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_s8x64_sum_
	#define _simd_s8x64_sum(X) _simd_s8x64_sum_(X);
	#define _simd_s8x64_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_sum_instruction_set>()
#elif defined(_simd_s8x32_add_)
	#define _simd_s8x64_sum(X) _simd_s8x64_sum(X) _simd_s8x32_sum(_simd_s8x32_add_(\
		_simd_s8x64_splitlo(X), _simd_s8x64_splithi(X)))d
	#define _simd_s8x64_sum_enable() (_simd_s8x32_add_enable() && _simd_s8x32_sum_enable() && _simd_s8x2_splitlo_enable() && _simd_s8x2_splithi_enable())
#else
	#define _simd_s8x64_sum(X) _simd_s8x64_sum_safe(X);
	#define _simd_s8x64_sum_enable() true
#endif

static _simd_u8x1 ANVIL_SIMD_CALL _simd_u8x2_sum_safe(const register _simd_u8x2 x) {
	_simd_u8x1 tmp = static_cast<_simd_u8x1>(0);
	for(int i = 0; i < 2; ++i) tmp += reinterpret_cast<_simd_u8x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_u8x2_sum_
	#define _simd_u8x2_sum(X) _simd_u8x2_sum_(X);
	#define _simd_u8x2_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_sum_instruction_set>()
#elif defined(_simd_u8x1_add_)
	#define _simd_u8x2_sum(X) _simd_u8x2_sum(X) _simd_u8x1_sum(_simd_u8x1_add_(\
		_simd_u8x2_splitlo(X), _simd_u8x2_splithi(X)))d
	#define _simd_u8x2_sum_enable() (_simd_u8x1_add_enable() && _simd_u8x1_sum_enable() && _simd_u8x2_splitlo_enable() && _simd_u8x2_splithi_enable())
#else
	#define _simd_u8x2_sum(X) _simd_u8x2_sum_safe(X);
	#define _simd_u8x2_sum_enable() true
#endif

static _simd_u8x1 ANVIL_SIMD_CALL _simd_u8x4_sum_safe(const register _simd_u8x4 x) {
	_simd_u8x1 tmp = static_cast<_simd_u8x1>(0);
	for(int i = 0; i < 4; ++i) tmp += reinterpret_cast<_simd_u8x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_u8x4_sum_
	#define _simd_u8x4_sum(X) _simd_u8x4_sum_(X);
	#define _simd_u8x4_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_sum_instruction_set>()
#elif defined(_simd_u8x2_add_)
	#define _simd_u8x4_sum(X) _simd_u8x4_sum(X) _simd_u8x2_sum(_simd_u8x2_add_(\
		_simd_u8x4_splitlo(X), _simd_u8x4_splithi(X)))d
	#define _simd_u8x4_sum_enable() (_simd_u8x2_add_enable() && _simd_u8x2_sum_enable() && _simd_u8x2_splitlo_enable() && _simd_u8x2_splithi_enable())
#else
	#define _simd_u8x4_sum(X) _simd_u8x4_sum_safe(X);
	#define _simd_u8x4_sum_enable() true
#endif

static _simd_u8x1 ANVIL_SIMD_CALL _simd_u8x8_sum_safe(const register _simd_u8x8 x) {
	_simd_u8x1 tmp = static_cast<_simd_u8x1>(0);
	for(int i = 0; i < 8; ++i) tmp += reinterpret_cast<_simd_u8x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_u8x8_sum_
	#define _simd_u8x8_sum(X) _simd_u8x8_sum_(X);
	#define _simd_u8x8_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_sum_instruction_set>()
#elif defined(_simd_u8x4_add_)
	#define _simd_u8x8_sum(X) _simd_u8x8_sum(X) _simd_u8x4_sum(_simd_u8x4_add_(\
		_simd_u8x8_splitlo(X), _simd_u8x8_splithi(X)))d
	#define _simd_u8x8_sum_enable() (_simd_u8x4_add_enable() && _simd_u8x4_sum_enable() && _simd_u8x2_splitlo_enable() && _simd_u8x2_splithi_enable())
#else
	#define _simd_u8x8_sum(X) _simd_u8x8_sum_safe(X);
	#define _simd_u8x8_sum_enable() true
#endif

static _simd_u8x1 ANVIL_SIMD_CALL _simd_u8x16_sum_safe(const register _simd_u8x16 x) {
	_simd_u8x1 tmp = static_cast<_simd_u8x1>(0);
	for(int i = 0; i < 16; ++i) tmp += reinterpret_cast<_simd_u8x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_u8x16_sum_
	#define _simd_u8x16_sum(X) _simd_u8x16_sum_(X);
	#define _simd_u8x16_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_sum_instruction_set>()
#elif defined(_simd_u8x8_add_)
	#define _simd_u8x16_sum(X) _simd_u8x16_sum(X) _simd_u8x8_sum(_simd_u8x8_add_(\
		_simd_u8x16_splitlo(X), _simd_u8x16_splithi(X)))d
	#define _simd_u8x16_sum_enable() (_simd_u8x8_add_enable() && _simd_u8x8_sum_enable() && _simd_u8x2_splitlo_enable() && _simd_u8x2_splithi_enable())
#else
	#define _simd_u8x16_sum(X) _simd_u8x16_sum_safe(X);
	#define _simd_u8x16_sum_enable() true
#endif

static _simd_u8x1 ANVIL_SIMD_CALL _simd_u8x32_sum_safe(const register _simd_u8x32 x) {
	_simd_u8x1 tmp = static_cast<_simd_u8x1>(0);
	for(int i = 0; i < 32; ++i) tmp += reinterpret_cast<_simd_u8x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_u8x32_sum_
	#define _simd_u8x32_sum(X) _simd_u8x32_sum_(X);
	#define _simd_u8x32_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_sum_instruction_set>()
#elif defined(_simd_u8x16_add_)
	#define _simd_u8x32_sum(X) _simd_u8x32_sum(X) _simd_u8x16_sum(_simd_u8x16_add_(\
		_simd_u8x32_splitlo(X), _simd_u8x32_splithi(X)))d
	#define _simd_u8x32_sum_enable() (_simd_u8x16_add_enable() && _simd_u8x16_sum_enable() && _simd_u8x2_splitlo_enable() && _simd_u8x2_splithi_enable())
#else
	#define _simd_u8x32_sum(X) _simd_u8x32_sum_safe(X);
	#define _simd_u8x32_sum_enable() true
#endif

static _simd_u8x1 ANVIL_SIMD_CALL _simd_u8x64_sum_safe(const register _simd_u8x64 x) {
	_simd_u8x1 tmp = static_cast<_simd_u8x1>(0);
	for(int i = 0; i < 64; ++i) tmp += reinterpret_cast<_simd_u8x1*>(&tmp)[i];
	return tmp;
}
#ifdef _simd_u8x64_sum_
	#define _simd_u8x64_sum(X) _simd_u8x64_sum_(X);
	#define _simd_u8x64_sum_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_sum_instruction_set>()
#elif defined(_simd_u8x32_add_)
	#define _simd_u8x64_sum(X) _simd_u8x64_sum(X) _simd_u8x32_sum(_simd_u8x32_add_(\
		_simd_u8x64_splitlo(X), _simd_u8x64_splithi(X)))d
	#define _simd_u8x64_sum_enable() (_simd_u8x32_add_enable() && _simd_u8x32_sum_enable() && _simd_u8x2_splitlo_enable() && _simd_u8x2_splithi_enable())
#else
	#define _simd_u8x64_sum(X) _simd_u8x64_sum_safe(X);
	#define _simd_u8x64_sum_enable() true
#endif

