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

static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_add(const register _simd_f64x2, const register _simd_f64x2 y) {
#ifdef _simd_f64x2_add_
	return _simd_f64x2_add_(x, y);
	#define _simd_f64x2_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_add_instruction_set>()
#elif defined(_simd_f64x4_add_)
	union SIMDUnion { _simd_f64x2 v1; _simd_f64x4 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_f64x4_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_f64x2_add_enable() _simd_f64x4_add_enable()
#elif defined(_simd_f64x8_add_)
	union SIMDUnion { _simd_f64x2 v1; _simd_f64x8 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_f64x8_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_f64x2_add_enable() _simd_f64x8_add_enable()
#elif defined(_simd_f64x16_add_)
	union SIMDUnion { _simd_f64x2 v1; _simd_f64x16 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_f64x16_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_f64x2_add_enable() _simd_f64x16_add_enable()
#elif defined(_simd_f64x32_add_)
	union SIMDUnion { _simd_f64x2 v1; _simd_f64x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_f64x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_f64x2_add_enable() _simd_f64x32_add_enable()
#elif defined(_simd_f64x64_add_)
	union SIMDUnion { _simd_f64x2 v1; _simd_f64x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_f64x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_f64x2_add_enable() _simd_f64x64_add_enable()
#else
	return _simd_f64x2_add_safe(x, y);
	#define _simd_f64x2_add_enable() true
#endif
}

static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_add(const register _simd_f64x4, const register _simd_f64x4 y) {
#ifdef _simd_f64x4_add_
	return _simd_f64x4_add_(x, y);
	#define _simd_f64x4_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_add_instruction_set>()
#elif defined(_simd_f64x8_add_)
	union SIMDUnion { _simd_f64x4 v1; _simd_f64x8 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_f64x8_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_f64x4_add_enable() _simd_f64x8_add_enable()
#elif defined(_simd_f64x16_add_)
	union SIMDUnion { _simd_f64x4 v1; _simd_f64x16 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_f64x16_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_f64x4_add_enable() _simd_f64x16_add_enable()
#elif defined(_simd_f64x32_add_)
	union SIMDUnion { _simd_f64x4 v1; _simd_f64x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_f64x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_f64x4_add_enable() _simd_f64x32_add_enable()
#elif defined(_simd_f64x64_add_)
	union SIMDUnion { _simd_f64x4 v1; _simd_f64x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_f64x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_f64x4_add_enable() _simd_f64x64_add_enable()
#else
	return _simd_f64x4_combine(
		_simd_f64x2_add(_simd_f64x4_splitlo(x), _simd_f64x4_splitlo(y)),
		_simd_f64x2_add(_simd_f64x4_splithi(x), _simd_f64x4_splithi(y)));
	#define _simd_f64x4_add_enable() _simd_f64x2_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_f64x8 ANVIL_SIMD_CALL _simd_f64x8_add(const register _simd_f64x8, const register _simd_f64x8 y) {
#ifdef _simd_f64x8_add_
	return _simd_f64x8_add_(x, y);
	#define _simd_f64x8_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_add_instruction_set>()
#elif defined(_simd_f64x16_add_)
	union SIMDUnion { _simd_f64x8 v1; _simd_f64x16 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_f64x16_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_f64x8_add_enable() _simd_f64x16_add_enable()
#elif defined(_simd_f64x32_add_)
	union SIMDUnion { _simd_f64x8 v1; _simd_f64x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_f64x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_f64x8_add_enable() _simd_f64x32_add_enable()
#elif defined(_simd_f64x64_add_)
	union SIMDUnion { _simd_f64x8 v1; _simd_f64x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_f64x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_f64x8_add_enable() _simd_f64x64_add_enable()
#else
	return _simd_f64x8_combine(
		_simd_f64x4_add(_simd_f64x8_splitlo(x), _simd_f64x8_splitlo(y)),
		_simd_f64x4_add(_simd_f64x8_splithi(x), _simd_f64x8_splithi(y)));
	#define _simd_f64x8_add_enable() _simd_f64x4_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_f64x16 ANVIL_SIMD_CALL _simd_f64x16_add(const register _simd_f64x16, const register _simd_f64x16 y) {
#ifdef _simd_f64x16_add_
	return _simd_f64x16_add_(x, y);
	#define _simd_f64x16_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_add_instruction_set>()
#elif defined(_simd_f64x32_add_)
	union SIMDUnion { _simd_f64x16 v1; _simd_f64x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_f64x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_f64x16_add_enable() _simd_f64x32_add_enable()
#elif defined(_simd_f64x64_add_)
	union SIMDUnion { _simd_f64x16 v1; _simd_f64x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_f64x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_f64x16_add_enable() _simd_f64x64_add_enable()
#else
	return _simd_f64x16_combine(
		_simd_f64x8_add(_simd_f64x16_splitlo(x), _simd_f64x16_splitlo(y)),
		_simd_f64x8_add(_simd_f64x16_splithi(x), _simd_f64x16_splithi(y)));
	#define _simd_f64x16_add_enable() _simd_f64x8_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_f64x32 ANVIL_SIMD_CALL _simd_f64x32_add(const register _simd_f64x32, const register _simd_f64x32 y) {
#ifdef _simd_f64x32_add_
	return _simd_f64x32_add_(x, y);
	#define _simd_f64x32_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_add_instruction_set>()
#elif defined(_simd_f64x64_add_)
	union SIMDUnion { _simd_f64x32 v1; _simd_f64x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_f64x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_f64x32_add_enable() _simd_f64x64_add_enable()
#else
	return _simd_f64x32_combine(
		_simd_f64x16_add(_simd_f64x32_splitlo(x), _simd_f64x32_splitlo(y)),
		_simd_f64x16_add(_simd_f64x32_splithi(x), _simd_f64x32_splithi(y)));
	#define _simd_f64x32_add_enable() _simd_f64x16_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_f64x64 ANVIL_SIMD_CALL _simd_f64x64_add(const register _simd_f64x64, const register _simd_f64x64 y) {
#ifdef _simd_f64x64_add_
	return _simd_f64x64_add_(x, y);
	#define _simd_f64x64_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_add_instruction_set>()
#else
	return _simd_f64x64_combine(
		_simd_f64x32_add(_simd_f64x64_splitlo(x), _simd_f64x64_splitlo(y)),
		_simd_f64x32_add(_simd_f64x64_splithi(x), _simd_f64x64_splithi(y)));
	#define _simd_f64x64_add_enable() _simd_f64x32_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_add(const register _simd_f32x2, const register _simd_f32x2 y) {
#ifdef _simd_f32x2_add_
	return _simd_f32x2_add_(x, y);
	#define _simd_f32x2_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_add_instruction_set>()
#elif defined(_simd_f32x4_add_)
	union SIMDUnion { _simd_f32x2 v1; _simd_f32x4 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_f32x4_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_f32x2_add_enable() _simd_f32x4_add_enable()
#elif defined(_simd_f32x8_add_)
	union SIMDUnion { _simd_f32x2 v1; _simd_f32x8 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_f32x8_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_f32x2_add_enable() _simd_f32x8_add_enable()
#elif defined(_simd_f32x16_add_)
	union SIMDUnion { _simd_f32x2 v1; _simd_f32x16 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_f32x16_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_f32x2_add_enable() _simd_f32x16_add_enable()
#elif defined(_simd_f32x32_add_)
	union SIMDUnion { _simd_f32x2 v1; _simd_f32x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_f32x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_f32x2_add_enable() _simd_f32x32_add_enable()
#elif defined(_simd_f32x64_add_)
	union SIMDUnion { _simd_f32x2 v1; _simd_f32x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_f32x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_f32x2_add_enable() _simd_f32x64_add_enable()
#else
	return _simd_f32x2_add_safe(x, y);
	#define _simd_f32x2_add_enable() true
#endif
}

static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_add(const register _simd_f32x4, const register _simd_f32x4 y) {
#ifdef _simd_f32x4_add_
	return _simd_f32x4_add_(x, y);
	#define _simd_f32x4_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_add_instruction_set>()
#elif defined(_simd_f32x8_add_)
	union SIMDUnion { _simd_f32x4 v1; _simd_f32x8 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_f32x8_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_f32x4_add_enable() _simd_f32x8_add_enable()
#elif defined(_simd_f32x16_add_)
	union SIMDUnion { _simd_f32x4 v1; _simd_f32x16 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_f32x16_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_f32x4_add_enable() _simd_f32x16_add_enable()
#elif defined(_simd_f32x32_add_)
	union SIMDUnion { _simd_f32x4 v1; _simd_f32x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_f32x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_f32x4_add_enable() _simd_f32x32_add_enable()
#elif defined(_simd_f32x64_add_)
	union SIMDUnion { _simd_f32x4 v1; _simd_f32x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_f32x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_f32x4_add_enable() _simd_f32x64_add_enable()
#else
	return _simd_f32x4_combine(
		_simd_f32x2_add(_simd_f32x4_splitlo(x), _simd_f32x4_splitlo(y)),
		_simd_f32x2_add(_simd_f32x4_splithi(x), _simd_f32x4_splithi(y)));
	#define _simd_f32x4_add_enable() _simd_f32x2_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_f32x8 ANVIL_SIMD_CALL _simd_f32x8_add(const register _simd_f32x8, const register _simd_f32x8 y) {
#ifdef _simd_f32x8_add_
	return _simd_f32x8_add_(x, y);
	#define _simd_f32x8_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_add_instruction_set>()
#elif defined(_simd_f32x16_add_)
	union SIMDUnion { _simd_f32x8 v1; _simd_f32x16 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_f32x16_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_f32x8_add_enable() _simd_f32x16_add_enable()
#elif defined(_simd_f32x32_add_)
	union SIMDUnion { _simd_f32x8 v1; _simd_f32x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_f32x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_f32x8_add_enable() _simd_f32x32_add_enable()
#elif defined(_simd_f32x64_add_)
	union SIMDUnion { _simd_f32x8 v1; _simd_f32x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_f32x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_f32x8_add_enable() _simd_f32x64_add_enable()
#else
	return _simd_f32x8_combine(
		_simd_f32x4_add(_simd_f32x8_splitlo(x), _simd_f32x8_splitlo(y)),
		_simd_f32x4_add(_simd_f32x8_splithi(x), _simd_f32x8_splithi(y)));
	#define _simd_f32x8_add_enable() _simd_f32x4_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_f32x16 ANVIL_SIMD_CALL _simd_f32x16_add(const register _simd_f32x16, const register _simd_f32x16 y) {
#ifdef _simd_f32x16_add_
	return _simd_f32x16_add_(x, y);
	#define _simd_f32x16_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_add_instruction_set>()
#elif defined(_simd_f32x32_add_)
	union SIMDUnion { _simd_f32x16 v1; _simd_f32x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_f32x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_f32x16_add_enable() _simd_f32x32_add_enable()
#elif defined(_simd_f32x64_add_)
	union SIMDUnion { _simd_f32x16 v1; _simd_f32x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_f32x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_f32x16_add_enable() _simd_f32x64_add_enable()
#else
	return _simd_f32x16_combine(
		_simd_f32x8_add(_simd_f32x16_splitlo(x), _simd_f32x16_splitlo(y)),
		_simd_f32x8_add(_simd_f32x16_splithi(x), _simd_f32x16_splithi(y)));
	#define _simd_f32x16_add_enable() _simd_f32x8_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_f32x32 ANVIL_SIMD_CALL _simd_f32x32_add(const register _simd_f32x32, const register _simd_f32x32 y) {
#ifdef _simd_f32x32_add_
	return _simd_f32x32_add_(x, y);
	#define _simd_f32x32_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_add_instruction_set>()
#elif defined(_simd_f32x64_add_)
	union SIMDUnion { _simd_f32x32 v1; _simd_f32x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_f32x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_f32x32_add_enable() _simd_f32x64_add_enable()
#else
	return _simd_f32x32_combine(
		_simd_f32x16_add(_simd_f32x32_splitlo(x), _simd_f32x32_splitlo(y)),
		_simd_f32x16_add(_simd_f32x32_splithi(x), _simd_f32x32_splithi(y)));
	#define _simd_f32x32_add_enable() _simd_f32x16_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_f32x64 ANVIL_SIMD_CALL _simd_f32x64_add(const register _simd_f32x64, const register _simd_f32x64 y) {
#ifdef _simd_f32x64_add_
	return _simd_f32x64_add_(x, y);
	#define _simd_f32x64_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_add_instruction_set>()
#else
	return _simd_f32x64_combine(
		_simd_f32x32_add(_simd_f32x64_splitlo(x), _simd_f32x64_splitlo(y)),
		_simd_f32x32_add(_simd_f32x64_splithi(x), _simd_f32x64_splithi(y)));
	#define _simd_f32x64_add_enable() _simd_f32x32_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_add(const register _simd_s64x2, const register _simd_s64x2 y) {
#ifdef _simd_s64x2_add_
	return _simd_s64x2_add_(x, y);
	#define _simd_s64x2_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_add_instruction_set>()
#elif defined(_simd_s64x4_add_)
	union SIMDUnion { _simd_s64x2 v1; _simd_s64x4 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s64x4_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s64x2_add_enable() _simd_s64x4_add_enable()
#elif defined(_simd_s64x8_add_)
	union SIMDUnion { _simd_s64x2 v1; _simd_s64x8 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s64x8_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s64x2_add_enable() _simd_s64x8_add_enable()
#elif defined(_simd_s64x16_add_)
	union SIMDUnion { _simd_s64x2 v1; _simd_s64x16 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s64x16_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s64x2_add_enable() _simd_s64x16_add_enable()
#elif defined(_simd_s64x32_add_)
	union SIMDUnion { _simd_s64x2 v1; _simd_s64x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s64x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s64x2_add_enable() _simd_s64x32_add_enable()
#elif defined(_simd_s64x64_add_)
	union SIMDUnion { _simd_s64x2 v1; _simd_s64x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s64x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s64x2_add_enable() _simd_s64x64_add_enable()
#else
	return _simd_s64x2_add_safe(x, y);
	#define _simd_s64x2_add_enable() true
#endif
}

static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_add(const register _simd_s64x4, const register _simd_s64x4 y) {
#ifdef _simd_s64x4_add_
	return _simd_s64x4_add_(x, y);
	#define _simd_s64x4_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_add_instruction_set>()
#elif defined(_simd_s64x8_add_)
	union SIMDUnion { _simd_s64x4 v1; _simd_s64x8 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s64x8_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s64x4_add_enable() _simd_s64x8_add_enable()
#elif defined(_simd_s64x16_add_)
	union SIMDUnion { _simd_s64x4 v1; _simd_s64x16 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s64x16_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s64x4_add_enable() _simd_s64x16_add_enable()
#elif defined(_simd_s64x32_add_)
	union SIMDUnion { _simd_s64x4 v1; _simd_s64x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s64x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s64x4_add_enable() _simd_s64x32_add_enable()
#elif defined(_simd_s64x64_add_)
	union SIMDUnion { _simd_s64x4 v1; _simd_s64x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s64x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s64x4_add_enable() _simd_s64x64_add_enable()
#else
	return _simd_s64x4_combine(
		_simd_s64x2_add(_simd_s64x4_splitlo(x), _simd_s64x4_splitlo(y)),
		_simd_s64x2_add(_simd_s64x4_splithi(x), _simd_s64x4_splithi(y)));
	#define _simd_s64x4_add_enable() _simd_s64x2_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_s64x8 ANVIL_SIMD_CALL _simd_s64x8_add(const register _simd_s64x8, const register _simd_s64x8 y) {
#ifdef _simd_s64x8_add_
	return _simd_s64x8_add_(x, y);
	#define _simd_s64x8_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_add_instruction_set>()
#elif defined(_simd_s64x16_add_)
	union SIMDUnion { _simd_s64x8 v1; _simd_s64x16 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s64x16_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s64x8_add_enable() _simd_s64x16_add_enable()
#elif defined(_simd_s64x32_add_)
	union SIMDUnion { _simd_s64x8 v1; _simd_s64x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s64x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s64x8_add_enable() _simd_s64x32_add_enable()
#elif defined(_simd_s64x64_add_)
	union SIMDUnion { _simd_s64x8 v1; _simd_s64x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s64x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s64x8_add_enable() _simd_s64x64_add_enable()
#else
	return _simd_s64x8_combine(
		_simd_s64x4_add(_simd_s64x8_splitlo(x), _simd_s64x8_splitlo(y)),
		_simd_s64x4_add(_simd_s64x8_splithi(x), _simd_s64x8_splithi(y)));
	#define _simd_s64x8_add_enable() _simd_s64x4_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_s64x16 ANVIL_SIMD_CALL _simd_s64x16_add(const register _simd_s64x16, const register _simd_s64x16 y) {
#ifdef _simd_s64x16_add_
	return _simd_s64x16_add_(x, y);
	#define _simd_s64x16_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_add_instruction_set>()
#elif defined(_simd_s64x32_add_)
	union SIMDUnion { _simd_s64x16 v1; _simd_s64x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s64x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s64x16_add_enable() _simd_s64x32_add_enable()
#elif defined(_simd_s64x64_add_)
	union SIMDUnion { _simd_s64x16 v1; _simd_s64x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s64x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s64x16_add_enable() _simd_s64x64_add_enable()
#else
	return _simd_s64x16_combine(
		_simd_s64x8_add(_simd_s64x16_splitlo(x), _simd_s64x16_splitlo(y)),
		_simd_s64x8_add(_simd_s64x16_splithi(x), _simd_s64x16_splithi(y)));
	#define _simd_s64x16_add_enable() _simd_s64x8_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_s64x32 ANVIL_SIMD_CALL _simd_s64x32_add(const register _simd_s64x32, const register _simd_s64x32 y) {
#ifdef _simd_s64x32_add_
	return _simd_s64x32_add_(x, y);
	#define _simd_s64x32_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_add_instruction_set>()
#elif defined(_simd_s64x64_add_)
	union SIMDUnion { _simd_s64x32 v1; _simd_s64x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s64x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s64x32_add_enable() _simd_s64x64_add_enable()
#else
	return _simd_s64x32_combine(
		_simd_s64x16_add(_simd_s64x32_splitlo(x), _simd_s64x32_splitlo(y)),
		_simd_s64x16_add(_simd_s64x32_splithi(x), _simd_s64x32_splithi(y)));
	#define _simd_s64x32_add_enable() _simd_s64x16_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_s64x64 ANVIL_SIMD_CALL _simd_s64x64_add(const register _simd_s64x64, const register _simd_s64x64 y) {
#ifdef _simd_s64x64_add_
	return _simd_s64x64_add_(x, y);
	#define _simd_s64x64_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_add_instruction_set>()
#else
	return _simd_s64x64_combine(
		_simd_s64x32_add(_simd_s64x64_splitlo(x), _simd_s64x64_splitlo(y)),
		_simd_s64x32_add(_simd_s64x64_splithi(x), _simd_s64x64_splithi(y)));
	#define _simd_s64x64_add_enable() _simd_s64x32_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_add(const register _simd_u64x2, const register _simd_u64x2 y) {
#ifdef _simd_u64x2_add_
	return _simd_u64x2_add_(x, y);
	#define _simd_u64x2_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_add_instruction_set>()
#elif defined(_simd_u64x4_add_)
	union SIMDUnion { _simd_u64x2 v1; _simd_u64x4 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u64x4_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u64x2_add_enable() _simd_u64x4_add_enable()
#elif defined(_simd_u64x8_add_)
	union SIMDUnion { _simd_u64x2 v1; _simd_u64x8 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u64x8_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u64x2_add_enable() _simd_u64x8_add_enable()
#elif defined(_simd_u64x16_add_)
	union SIMDUnion { _simd_u64x2 v1; _simd_u64x16 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u64x16_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u64x2_add_enable() _simd_u64x16_add_enable()
#elif defined(_simd_u64x32_add_)
	union SIMDUnion { _simd_u64x2 v1; _simd_u64x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u64x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u64x2_add_enable() _simd_u64x32_add_enable()
#elif defined(_simd_u64x64_add_)
	union SIMDUnion { _simd_u64x2 v1; _simd_u64x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u64x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u64x2_add_enable() _simd_u64x64_add_enable()
#else
	return _simd_u64x2_add_safe(x, y);
	#define _simd_u64x2_add_enable() true
#endif
}

static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_add(const register _simd_u64x4, const register _simd_u64x4 y) {
#ifdef _simd_u64x4_add_
	return _simd_u64x4_add_(x, y);
	#define _simd_u64x4_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_add_instruction_set>()
#elif defined(_simd_u64x8_add_)
	union SIMDUnion { _simd_u64x4 v1; _simd_u64x8 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u64x8_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u64x4_add_enable() _simd_u64x8_add_enable()
#elif defined(_simd_u64x16_add_)
	union SIMDUnion { _simd_u64x4 v1; _simd_u64x16 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u64x16_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u64x4_add_enable() _simd_u64x16_add_enable()
#elif defined(_simd_u64x32_add_)
	union SIMDUnion { _simd_u64x4 v1; _simd_u64x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u64x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u64x4_add_enable() _simd_u64x32_add_enable()
#elif defined(_simd_u64x64_add_)
	union SIMDUnion { _simd_u64x4 v1; _simd_u64x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u64x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u64x4_add_enable() _simd_u64x64_add_enable()
#else
	return _simd_u64x4_combine(
		_simd_u64x2_add(_simd_u64x4_splitlo(x), _simd_u64x4_splitlo(y)),
		_simd_u64x2_add(_simd_u64x4_splithi(x), _simd_u64x4_splithi(y)));
	#define _simd_u64x4_add_enable() _simd_u64x2_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_u64x8 ANVIL_SIMD_CALL _simd_u64x8_add(const register _simd_u64x8, const register _simd_u64x8 y) {
#ifdef _simd_u64x8_add_
	return _simd_u64x8_add_(x, y);
	#define _simd_u64x8_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_add_instruction_set>()
#elif defined(_simd_u64x16_add_)
	union SIMDUnion { _simd_u64x8 v1; _simd_u64x16 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u64x16_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u64x8_add_enable() _simd_u64x16_add_enable()
#elif defined(_simd_u64x32_add_)
	union SIMDUnion { _simd_u64x8 v1; _simd_u64x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u64x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u64x8_add_enable() _simd_u64x32_add_enable()
#elif defined(_simd_u64x64_add_)
	union SIMDUnion { _simd_u64x8 v1; _simd_u64x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u64x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u64x8_add_enable() _simd_u64x64_add_enable()
#else
	return _simd_u64x8_combine(
		_simd_u64x4_add(_simd_u64x8_splitlo(x), _simd_u64x8_splitlo(y)),
		_simd_u64x4_add(_simd_u64x8_splithi(x), _simd_u64x8_splithi(y)));
	#define _simd_u64x8_add_enable() _simd_u64x4_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_u64x16 ANVIL_SIMD_CALL _simd_u64x16_add(const register _simd_u64x16, const register _simd_u64x16 y) {
#ifdef _simd_u64x16_add_
	return _simd_u64x16_add_(x, y);
	#define _simd_u64x16_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_add_instruction_set>()
#elif defined(_simd_u64x32_add_)
	union SIMDUnion { _simd_u64x16 v1; _simd_u64x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u64x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u64x16_add_enable() _simd_u64x32_add_enable()
#elif defined(_simd_u64x64_add_)
	union SIMDUnion { _simd_u64x16 v1; _simd_u64x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u64x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u64x16_add_enable() _simd_u64x64_add_enable()
#else
	return _simd_u64x16_combine(
		_simd_u64x8_add(_simd_u64x16_splitlo(x), _simd_u64x16_splitlo(y)),
		_simd_u64x8_add(_simd_u64x16_splithi(x), _simd_u64x16_splithi(y)));
	#define _simd_u64x16_add_enable() _simd_u64x8_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_u64x32 ANVIL_SIMD_CALL _simd_u64x32_add(const register _simd_u64x32, const register _simd_u64x32 y) {
#ifdef _simd_u64x32_add_
	return _simd_u64x32_add_(x, y);
	#define _simd_u64x32_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_add_instruction_set>()
#elif defined(_simd_u64x64_add_)
	union SIMDUnion { _simd_u64x32 v1; _simd_u64x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u64x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u64x32_add_enable() _simd_u64x64_add_enable()
#else
	return _simd_u64x32_combine(
		_simd_u64x16_add(_simd_u64x32_splitlo(x), _simd_u64x32_splitlo(y)),
		_simd_u64x16_add(_simd_u64x32_splithi(x), _simd_u64x32_splithi(y)));
	#define _simd_u64x32_add_enable() _simd_u64x16_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_u64x64 ANVIL_SIMD_CALL _simd_u64x64_add(const register _simd_u64x64, const register _simd_u64x64 y) {
#ifdef _simd_u64x64_add_
	return _simd_u64x64_add_(x, y);
	#define _simd_u64x64_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_add_instruction_set>()
#else
	return _simd_u64x64_combine(
		_simd_u64x32_add(_simd_u64x64_splitlo(x), _simd_u64x64_splitlo(y)),
		_simd_u64x32_add(_simd_u64x64_splithi(x), _simd_u64x64_splithi(y)));
	#define _simd_u64x64_add_enable() _simd_u64x32_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_add(const register _simd_s32x2, const register _simd_s32x2 y) {
#ifdef _simd_s32x2_add_
	return _simd_s32x2_add_(x, y);
	#define _simd_s32x2_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_add_instruction_set>()
#elif defined(_simd_s32x4_add_)
	union SIMDUnion { _simd_s32x2 v1; _simd_s32x4 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s32x4_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s32x2_add_enable() _simd_s32x4_add_enable()
#elif defined(_simd_s32x8_add_)
	union SIMDUnion { _simd_s32x2 v1; _simd_s32x8 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s32x8_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s32x2_add_enable() _simd_s32x8_add_enable()
#elif defined(_simd_s32x16_add_)
	union SIMDUnion { _simd_s32x2 v1; _simd_s32x16 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s32x16_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s32x2_add_enable() _simd_s32x16_add_enable()
#elif defined(_simd_s32x32_add_)
	union SIMDUnion { _simd_s32x2 v1; _simd_s32x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s32x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s32x2_add_enable() _simd_s32x32_add_enable()
#elif defined(_simd_s32x64_add_)
	union SIMDUnion { _simd_s32x2 v1; _simd_s32x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s32x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s32x2_add_enable() _simd_s32x64_add_enable()
#else
	return _simd_s32x2_add_safe(x, y);
	#define _simd_s32x2_add_enable() true
#endif
}

static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_add(const register _simd_s32x4, const register _simd_s32x4 y) {
#ifdef _simd_s32x4_add_
	return _simd_s32x4_add_(x, y);
	#define _simd_s32x4_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_add_instruction_set>()
#elif defined(_simd_s32x8_add_)
	union SIMDUnion { _simd_s32x4 v1; _simd_s32x8 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s32x8_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s32x4_add_enable() _simd_s32x8_add_enable()
#elif defined(_simd_s32x16_add_)
	union SIMDUnion { _simd_s32x4 v1; _simd_s32x16 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s32x16_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s32x4_add_enable() _simd_s32x16_add_enable()
#elif defined(_simd_s32x32_add_)
	union SIMDUnion { _simd_s32x4 v1; _simd_s32x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s32x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s32x4_add_enable() _simd_s32x32_add_enable()
#elif defined(_simd_s32x64_add_)
	union SIMDUnion { _simd_s32x4 v1; _simd_s32x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s32x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s32x4_add_enable() _simd_s32x64_add_enable()
#else
	return _simd_s32x4_combine(
		_simd_s32x2_add(_simd_s32x4_splitlo(x), _simd_s32x4_splitlo(y)),
		_simd_s32x2_add(_simd_s32x4_splithi(x), _simd_s32x4_splithi(y)));
	#define _simd_s32x4_add_enable() _simd_s32x2_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_s32x8 ANVIL_SIMD_CALL _simd_s32x8_add(const register _simd_s32x8, const register _simd_s32x8 y) {
#ifdef _simd_s32x8_add_
	return _simd_s32x8_add_(x, y);
	#define _simd_s32x8_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_add_instruction_set>()
#elif defined(_simd_s32x16_add_)
	union SIMDUnion { _simd_s32x8 v1; _simd_s32x16 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s32x16_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s32x8_add_enable() _simd_s32x16_add_enable()
#elif defined(_simd_s32x32_add_)
	union SIMDUnion { _simd_s32x8 v1; _simd_s32x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s32x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s32x8_add_enable() _simd_s32x32_add_enable()
#elif defined(_simd_s32x64_add_)
	union SIMDUnion { _simd_s32x8 v1; _simd_s32x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s32x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s32x8_add_enable() _simd_s32x64_add_enable()
#else
	return _simd_s32x8_combine(
		_simd_s32x4_add(_simd_s32x8_splitlo(x), _simd_s32x8_splitlo(y)),
		_simd_s32x4_add(_simd_s32x8_splithi(x), _simd_s32x8_splithi(y)));
	#define _simd_s32x8_add_enable() _simd_s32x4_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_s32x16 ANVIL_SIMD_CALL _simd_s32x16_add(const register _simd_s32x16, const register _simd_s32x16 y) {
#ifdef _simd_s32x16_add_
	return _simd_s32x16_add_(x, y);
	#define _simd_s32x16_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_add_instruction_set>()
#elif defined(_simd_s32x32_add_)
	union SIMDUnion { _simd_s32x16 v1; _simd_s32x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s32x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s32x16_add_enable() _simd_s32x32_add_enable()
#elif defined(_simd_s32x64_add_)
	union SIMDUnion { _simd_s32x16 v1; _simd_s32x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s32x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s32x16_add_enable() _simd_s32x64_add_enable()
#else
	return _simd_s32x16_combine(
		_simd_s32x8_add(_simd_s32x16_splitlo(x), _simd_s32x16_splitlo(y)),
		_simd_s32x8_add(_simd_s32x16_splithi(x), _simd_s32x16_splithi(y)));
	#define _simd_s32x16_add_enable() _simd_s32x8_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_s32x32 ANVIL_SIMD_CALL _simd_s32x32_add(const register _simd_s32x32, const register _simd_s32x32 y) {
#ifdef _simd_s32x32_add_
	return _simd_s32x32_add_(x, y);
	#define _simd_s32x32_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_add_instruction_set>()
#elif defined(_simd_s32x64_add_)
	union SIMDUnion { _simd_s32x32 v1; _simd_s32x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s32x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s32x32_add_enable() _simd_s32x64_add_enable()
#else
	return _simd_s32x32_combine(
		_simd_s32x16_add(_simd_s32x32_splitlo(x), _simd_s32x32_splitlo(y)),
		_simd_s32x16_add(_simd_s32x32_splithi(x), _simd_s32x32_splithi(y)));
	#define _simd_s32x32_add_enable() _simd_s32x16_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_s32x64 ANVIL_SIMD_CALL _simd_s32x64_add(const register _simd_s32x64, const register _simd_s32x64 y) {
#ifdef _simd_s32x64_add_
	return _simd_s32x64_add_(x, y);
	#define _simd_s32x64_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_add_instruction_set>()
#else
	return _simd_s32x64_combine(
		_simd_s32x32_add(_simd_s32x64_splitlo(x), _simd_s32x64_splitlo(y)),
		_simd_s32x32_add(_simd_s32x64_splithi(x), _simd_s32x64_splithi(y)));
	#define _simd_s32x64_add_enable() _simd_s32x32_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_add(const register _simd_u32x2, const register _simd_u32x2 y) {
#ifdef _simd_u32x2_add_
	return _simd_u32x2_add_(x, y);
	#define _simd_u32x2_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_add_instruction_set>()
#elif defined(_simd_u32x4_add_)
	union SIMDUnion { _simd_u32x2 v1; _simd_u32x4 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u32x4_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u32x2_add_enable() _simd_u32x4_add_enable()
#elif defined(_simd_u32x8_add_)
	union SIMDUnion { _simd_u32x2 v1; _simd_u32x8 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u32x8_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u32x2_add_enable() _simd_u32x8_add_enable()
#elif defined(_simd_u32x16_add_)
	union SIMDUnion { _simd_u32x2 v1; _simd_u32x16 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u32x16_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u32x2_add_enable() _simd_u32x16_add_enable()
#elif defined(_simd_u32x32_add_)
	union SIMDUnion { _simd_u32x2 v1; _simd_u32x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u32x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u32x2_add_enable() _simd_u32x32_add_enable()
#elif defined(_simd_u32x64_add_)
	union SIMDUnion { _simd_u32x2 v1; _simd_u32x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u32x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u32x2_add_enable() _simd_u32x64_add_enable()
#else
	return _simd_u32x2_add_safe(x, y);
	#define _simd_u32x2_add_enable() true
#endif
}

static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_add(const register _simd_u32x4, const register _simd_u32x4 y) {
#ifdef _simd_u32x4_add_
	return _simd_u32x4_add_(x, y);
	#define _simd_u32x4_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_add_instruction_set>()
#elif defined(_simd_u32x8_add_)
	union SIMDUnion { _simd_u32x4 v1; _simd_u32x8 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u32x8_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u32x4_add_enable() _simd_u32x8_add_enable()
#elif defined(_simd_u32x16_add_)
	union SIMDUnion { _simd_u32x4 v1; _simd_u32x16 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u32x16_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u32x4_add_enable() _simd_u32x16_add_enable()
#elif defined(_simd_u32x32_add_)
	union SIMDUnion { _simd_u32x4 v1; _simd_u32x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u32x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u32x4_add_enable() _simd_u32x32_add_enable()
#elif defined(_simd_u32x64_add_)
	union SIMDUnion { _simd_u32x4 v1; _simd_u32x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u32x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u32x4_add_enable() _simd_u32x64_add_enable()
#else
	return _simd_u32x4_combine(
		_simd_u32x2_add(_simd_u32x4_splitlo(x), _simd_u32x4_splitlo(y)),
		_simd_u32x2_add(_simd_u32x4_splithi(x), _simd_u32x4_splithi(y)));
	#define _simd_u32x4_add_enable() _simd_u32x2_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_u32x8 ANVIL_SIMD_CALL _simd_u32x8_add(const register _simd_u32x8, const register _simd_u32x8 y) {
#ifdef _simd_u32x8_add_
	return _simd_u32x8_add_(x, y);
	#define _simd_u32x8_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_add_instruction_set>()
#elif defined(_simd_u32x16_add_)
	union SIMDUnion { _simd_u32x8 v1; _simd_u32x16 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u32x16_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u32x8_add_enable() _simd_u32x16_add_enable()
#elif defined(_simd_u32x32_add_)
	union SIMDUnion { _simd_u32x8 v1; _simd_u32x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u32x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u32x8_add_enable() _simd_u32x32_add_enable()
#elif defined(_simd_u32x64_add_)
	union SIMDUnion { _simd_u32x8 v1; _simd_u32x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u32x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u32x8_add_enable() _simd_u32x64_add_enable()
#else
	return _simd_u32x8_combine(
		_simd_u32x4_add(_simd_u32x8_splitlo(x), _simd_u32x8_splitlo(y)),
		_simd_u32x4_add(_simd_u32x8_splithi(x), _simd_u32x8_splithi(y)));
	#define _simd_u32x8_add_enable() _simd_u32x4_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_u32x16 ANVIL_SIMD_CALL _simd_u32x16_add(const register _simd_u32x16, const register _simd_u32x16 y) {
#ifdef _simd_u32x16_add_
	return _simd_u32x16_add_(x, y);
	#define _simd_u32x16_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_add_instruction_set>()
#elif defined(_simd_u32x32_add_)
	union SIMDUnion { _simd_u32x16 v1; _simd_u32x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u32x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u32x16_add_enable() _simd_u32x32_add_enable()
#elif defined(_simd_u32x64_add_)
	union SIMDUnion { _simd_u32x16 v1; _simd_u32x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u32x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u32x16_add_enable() _simd_u32x64_add_enable()
#else
	return _simd_u32x16_combine(
		_simd_u32x8_add(_simd_u32x16_splitlo(x), _simd_u32x16_splitlo(y)),
		_simd_u32x8_add(_simd_u32x16_splithi(x), _simd_u32x16_splithi(y)));
	#define _simd_u32x16_add_enable() _simd_u32x8_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_u32x32 ANVIL_SIMD_CALL _simd_u32x32_add(const register _simd_u32x32, const register _simd_u32x32 y) {
#ifdef _simd_u32x32_add_
	return _simd_u32x32_add_(x, y);
	#define _simd_u32x32_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_add_instruction_set>()
#elif defined(_simd_u32x64_add_)
	union SIMDUnion { _simd_u32x32 v1; _simd_u32x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u32x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u32x32_add_enable() _simd_u32x64_add_enable()
#else
	return _simd_u32x32_combine(
		_simd_u32x16_add(_simd_u32x32_splitlo(x), _simd_u32x32_splitlo(y)),
		_simd_u32x16_add(_simd_u32x32_splithi(x), _simd_u32x32_splithi(y)));
	#define _simd_u32x32_add_enable() _simd_u32x16_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_u32x64 ANVIL_SIMD_CALL _simd_u32x64_add(const register _simd_u32x64, const register _simd_u32x64 y) {
#ifdef _simd_u32x64_add_
	return _simd_u32x64_add_(x, y);
	#define _simd_u32x64_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_add_instruction_set>()
#else
	return _simd_u32x64_combine(
		_simd_u32x32_add(_simd_u32x64_splitlo(x), _simd_u32x64_splitlo(y)),
		_simd_u32x32_add(_simd_u32x64_splithi(x), _simd_u32x64_splithi(y)));
	#define _simd_u32x64_add_enable() _simd_u32x32_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_add(const register _simd_s16x2, const register _simd_s16x2 y) {
#ifdef _simd_s16x2_add_
	return _simd_s16x2_add_(x, y);
	#define _simd_s16x2_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_add_instruction_set>()
#elif defined(_simd_s16x4_add_)
	union SIMDUnion { _simd_s16x2 v1; _simd_s16x4 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s16x4_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s16x2_add_enable() _simd_s16x4_add_enable()
#elif defined(_simd_s16x8_add_)
	union SIMDUnion { _simd_s16x2 v1; _simd_s16x8 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s16x8_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s16x2_add_enable() _simd_s16x8_add_enable()
#elif defined(_simd_s16x16_add_)
	union SIMDUnion { _simd_s16x2 v1; _simd_s16x16 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s16x16_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s16x2_add_enable() _simd_s16x16_add_enable()
#elif defined(_simd_s16x32_add_)
	union SIMDUnion { _simd_s16x2 v1; _simd_s16x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s16x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s16x2_add_enable() _simd_s16x32_add_enable()
#elif defined(_simd_s16x64_add_)
	union SIMDUnion { _simd_s16x2 v1; _simd_s16x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s16x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s16x2_add_enable() _simd_s16x64_add_enable()
#else
	return _simd_s16x2_add_safe(x, y);
	#define _simd_s16x2_add_enable() true
#endif
}

static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_add(const register _simd_s16x4, const register _simd_s16x4 y) {
#ifdef _simd_s16x4_add_
	return _simd_s16x4_add_(x, y);
	#define _simd_s16x4_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_add_instruction_set>()
#elif defined(_simd_s16x8_add_)
	union SIMDUnion { _simd_s16x4 v1; _simd_s16x8 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s16x8_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s16x4_add_enable() _simd_s16x8_add_enable()
#elif defined(_simd_s16x16_add_)
	union SIMDUnion { _simd_s16x4 v1; _simd_s16x16 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s16x16_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s16x4_add_enable() _simd_s16x16_add_enable()
#elif defined(_simd_s16x32_add_)
	union SIMDUnion { _simd_s16x4 v1; _simd_s16x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s16x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s16x4_add_enable() _simd_s16x32_add_enable()
#elif defined(_simd_s16x64_add_)
	union SIMDUnion { _simd_s16x4 v1; _simd_s16x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s16x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s16x4_add_enable() _simd_s16x64_add_enable()
#else
	return _simd_s16x4_combine(
		_simd_s16x2_add(_simd_s16x4_splitlo(x), _simd_s16x4_splitlo(y)),
		_simd_s16x2_add(_simd_s16x4_splithi(x), _simd_s16x4_splithi(y)));
	#define _simd_s16x4_add_enable() _simd_s16x2_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_s16x8 ANVIL_SIMD_CALL _simd_s16x8_add(const register _simd_s16x8, const register _simd_s16x8 y) {
#ifdef _simd_s16x8_add_
	return _simd_s16x8_add_(x, y);
	#define _simd_s16x8_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_add_instruction_set>()
#elif defined(_simd_s16x16_add_)
	union SIMDUnion { _simd_s16x8 v1; _simd_s16x16 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s16x16_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s16x8_add_enable() _simd_s16x16_add_enable()
#elif defined(_simd_s16x32_add_)
	union SIMDUnion { _simd_s16x8 v1; _simd_s16x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s16x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s16x8_add_enable() _simd_s16x32_add_enable()
#elif defined(_simd_s16x64_add_)
	union SIMDUnion { _simd_s16x8 v1; _simd_s16x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s16x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s16x8_add_enable() _simd_s16x64_add_enable()
#else
	return _simd_s16x8_combine(
		_simd_s16x4_add(_simd_s16x8_splitlo(x), _simd_s16x8_splitlo(y)),
		_simd_s16x4_add(_simd_s16x8_splithi(x), _simd_s16x8_splithi(y)));
	#define _simd_s16x8_add_enable() _simd_s16x4_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_s16x16 ANVIL_SIMD_CALL _simd_s16x16_add(const register _simd_s16x16, const register _simd_s16x16 y) {
#ifdef _simd_s16x16_add_
	return _simd_s16x16_add_(x, y);
	#define _simd_s16x16_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_add_instruction_set>()
#elif defined(_simd_s16x32_add_)
	union SIMDUnion { _simd_s16x16 v1; _simd_s16x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s16x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s16x16_add_enable() _simd_s16x32_add_enable()
#elif defined(_simd_s16x64_add_)
	union SIMDUnion { _simd_s16x16 v1; _simd_s16x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s16x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s16x16_add_enable() _simd_s16x64_add_enable()
#else
	return _simd_s16x16_combine(
		_simd_s16x8_add(_simd_s16x16_splitlo(x), _simd_s16x16_splitlo(y)),
		_simd_s16x8_add(_simd_s16x16_splithi(x), _simd_s16x16_splithi(y)));
	#define _simd_s16x16_add_enable() _simd_s16x8_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_s16x32 ANVIL_SIMD_CALL _simd_s16x32_add(const register _simd_s16x32, const register _simd_s16x32 y) {
#ifdef _simd_s16x32_add_
	return _simd_s16x32_add_(x, y);
	#define _simd_s16x32_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_add_instruction_set>()
#elif defined(_simd_s16x64_add_)
	union SIMDUnion { _simd_s16x32 v1; _simd_s16x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s16x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s16x32_add_enable() _simd_s16x64_add_enable()
#else
	return _simd_s16x32_combine(
		_simd_s16x16_add(_simd_s16x32_splitlo(x), _simd_s16x32_splitlo(y)),
		_simd_s16x16_add(_simd_s16x32_splithi(x), _simd_s16x32_splithi(y)));
	#define _simd_s16x32_add_enable() _simd_s16x16_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_s16x64 ANVIL_SIMD_CALL _simd_s16x64_add(const register _simd_s16x64, const register _simd_s16x64 y) {
#ifdef _simd_s16x64_add_
	return _simd_s16x64_add_(x, y);
	#define _simd_s16x64_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_add_instruction_set>()
#else
	return _simd_s16x64_combine(
		_simd_s16x32_add(_simd_s16x64_splitlo(x), _simd_s16x64_splitlo(y)),
		_simd_s16x32_add(_simd_s16x64_splithi(x), _simd_s16x64_splithi(y)));
	#define _simd_s16x64_add_enable() _simd_s16x32_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_add(const register _simd_u16x2, const register _simd_u16x2 y) {
#ifdef _simd_u16x2_add_
	return _simd_u16x2_add_(x, y);
	#define _simd_u16x2_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_add_instruction_set>()
#elif defined(_simd_u16x4_add_)
	union SIMDUnion { _simd_u16x2 v1; _simd_u16x4 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u16x4_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u16x2_add_enable() _simd_u16x4_add_enable()
#elif defined(_simd_u16x8_add_)
	union SIMDUnion { _simd_u16x2 v1; _simd_u16x8 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u16x8_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u16x2_add_enable() _simd_u16x8_add_enable()
#elif defined(_simd_u16x16_add_)
	union SIMDUnion { _simd_u16x2 v1; _simd_u16x16 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u16x16_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u16x2_add_enable() _simd_u16x16_add_enable()
#elif defined(_simd_u16x32_add_)
	union SIMDUnion { _simd_u16x2 v1; _simd_u16x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u16x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u16x2_add_enable() _simd_u16x32_add_enable()
#elif defined(_simd_u16x64_add_)
	union SIMDUnion { _simd_u16x2 v1; _simd_u16x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u16x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u16x2_add_enable() _simd_u16x64_add_enable()
#else
	return _simd_u16x2_add_safe(x, y);
	#define _simd_u16x2_add_enable() true
#endif
}

static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_add(const register _simd_u16x4, const register _simd_u16x4 y) {
#ifdef _simd_u16x4_add_
	return _simd_u16x4_add_(x, y);
	#define _simd_u16x4_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_add_instruction_set>()
#elif defined(_simd_u16x8_add_)
	union SIMDUnion { _simd_u16x4 v1; _simd_u16x8 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u16x8_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u16x4_add_enable() _simd_u16x8_add_enable()
#elif defined(_simd_u16x16_add_)
	union SIMDUnion { _simd_u16x4 v1; _simd_u16x16 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u16x16_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u16x4_add_enable() _simd_u16x16_add_enable()
#elif defined(_simd_u16x32_add_)
	union SIMDUnion { _simd_u16x4 v1; _simd_u16x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u16x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u16x4_add_enable() _simd_u16x32_add_enable()
#elif defined(_simd_u16x64_add_)
	union SIMDUnion { _simd_u16x4 v1; _simd_u16x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u16x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u16x4_add_enable() _simd_u16x64_add_enable()
#else
	return _simd_u16x4_combine(
		_simd_u16x2_add(_simd_u16x4_splitlo(x), _simd_u16x4_splitlo(y)),
		_simd_u16x2_add(_simd_u16x4_splithi(x), _simd_u16x4_splithi(y)));
	#define _simd_u16x4_add_enable() _simd_u16x2_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_u16x8 ANVIL_SIMD_CALL _simd_u16x8_add(const register _simd_u16x8, const register _simd_u16x8 y) {
#ifdef _simd_u16x8_add_
	return _simd_u16x8_add_(x, y);
	#define _simd_u16x8_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_add_instruction_set>()
#elif defined(_simd_u16x16_add_)
	union SIMDUnion { _simd_u16x8 v1; _simd_u16x16 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u16x16_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u16x8_add_enable() _simd_u16x16_add_enable()
#elif defined(_simd_u16x32_add_)
	union SIMDUnion { _simd_u16x8 v1; _simd_u16x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u16x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u16x8_add_enable() _simd_u16x32_add_enable()
#elif defined(_simd_u16x64_add_)
	union SIMDUnion { _simd_u16x8 v1; _simd_u16x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u16x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u16x8_add_enable() _simd_u16x64_add_enable()
#else
	return _simd_u16x8_combine(
		_simd_u16x4_add(_simd_u16x8_splitlo(x), _simd_u16x8_splitlo(y)),
		_simd_u16x4_add(_simd_u16x8_splithi(x), _simd_u16x8_splithi(y)));
	#define _simd_u16x8_add_enable() _simd_u16x4_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_u16x16 ANVIL_SIMD_CALL _simd_u16x16_add(const register _simd_u16x16, const register _simd_u16x16 y) {
#ifdef _simd_u16x16_add_
	return _simd_u16x16_add_(x, y);
	#define _simd_u16x16_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_add_instruction_set>()
#elif defined(_simd_u16x32_add_)
	union SIMDUnion { _simd_u16x16 v1; _simd_u16x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u16x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u16x16_add_enable() _simd_u16x32_add_enable()
#elif defined(_simd_u16x64_add_)
	union SIMDUnion { _simd_u16x16 v1; _simd_u16x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u16x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u16x16_add_enable() _simd_u16x64_add_enable()
#else
	return _simd_u16x16_combine(
		_simd_u16x8_add(_simd_u16x16_splitlo(x), _simd_u16x16_splitlo(y)),
		_simd_u16x8_add(_simd_u16x16_splithi(x), _simd_u16x16_splithi(y)));
	#define _simd_u16x16_add_enable() _simd_u16x8_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_u16x32 ANVIL_SIMD_CALL _simd_u16x32_add(const register _simd_u16x32, const register _simd_u16x32 y) {
#ifdef _simd_u16x32_add_
	return _simd_u16x32_add_(x, y);
	#define _simd_u16x32_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_add_instruction_set>()
#elif defined(_simd_u16x64_add_)
	union SIMDUnion { _simd_u16x32 v1; _simd_u16x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u16x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u16x32_add_enable() _simd_u16x64_add_enable()
#else
	return _simd_u16x32_combine(
		_simd_u16x16_add(_simd_u16x32_splitlo(x), _simd_u16x32_splitlo(y)),
		_simd_u16x16_add(_simd_u16x32_splithi(x), _simd_u16x32_splithi(y)));
	#define _simd_u16x32_add_enable() _simd_u16x16_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_u16x64 ANVIL_SIMD_CALL _simd_u16x64_add(const register _simd_u16x64, const register _simd_u16x64 y) {
#ifdef _simd_u16x64_add_
	return _simd_u16x64_add_(x, y);
	#define _simd_u16x64_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_add_instruction_set>()
#else
	return _simd_u16x64_combine(
		_simd_u16x32_add(_simd_u16x64_splitlo(x), _simd_u16x64_splitlo(y)),
		_simd_u16x32_add(_simd_u16x64_splithi(x), _simd_u16x64_splithi(y)));
	#define _simd_u16x64_add_enable() _simd_u16x32_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_add(const register _simd_s8x2, const register _simd_s8x2 y) {
#ifdef _simd_s8x2_add_
	return _simd_s8x2_add_(x, y);
	#define _simd_s8x2_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_add_instruction_set>()
#elif defined(_simd_s8x4_add_)
	union SIMDUnion { _simd_s8x2 v1; _simd_s8x4 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s8x4_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s8x2_add_enable() _simd_s8x4_add_enable()
#elif defined(_simd_s8x8_add_)
	union SIMDUnion { _simd_s8x2 v1; _simd_s8x8 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s8x8_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s8x2_add_enable() _simd_s8x8_add_enable()
#elif defined(_simd_s8x16_add_)
	union SIMDUnion { _simd_s8x2 v1; _simd_s8x16 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s8x16_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s8x2_add_enable() _simd_s8x16_add_enable()
#elif defined(_simd_s8x32_add_)
	union SIMDUnion { _simd_s8x2 v1; _simd_s8x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s8x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s8x2_add_enable() _simd_s8x32_add_enable()
#elif defined(_simd_s8x64_add_)
	union SIMDUnion { _simd_s8x2 v1; _simd_s8x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s8x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s8x2_add_enable() _simd_s8x64_add_enable()
#else
	return _simd_s8x2_add_safe(x, y);
	#define _simd_s8x2_add_enable() true
#endif
}

static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_add(const register _simd_s8x4, const register _simd_s8x4 y) {
#ifdef _simd_s8x4_add_
	return _simd_s8x4_add_(x, y);
	#define _simd_s8x4_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_add_instruction_set>()
#elif defined(_simd_s8x8_add_)
	union SIMDUnion { _simd_s8x4 v1; _simd_s8x8 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s8x8_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s8x4_add_enable() _simd_s8x8_add_enable()
#elif defined(_simd_s8x16_add_)
	union SIMDUnion { _simd_s8x4 v1; _simd_s8x16 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s8x16_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s8x4_add_enable() _simd_s8x16_add_enable()
#elif defined(_simd_s8x32_add_)
	union SIMDUnion { _simd_s8x4 v1; _simd_s8x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s8x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s8x4_add_enable() _simd_s8x32_add_enable()
#elif defined(_simd_s8x64_add_)
	union SIMDUnion { _simd_s8x4 v1; _simd_s8x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s8x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s8x4_add_enable() _simd_s8x64_add_enable()
#else
	return _simd_s8x4_combine(
		_simd_s8x2_add(_simd_s8x4_splitlo(x), _simd_s8x4_splitlo(y)),
		_simd_s8x2_add(_simd_s8x4_splithi(x), _simd_s8x4_splithi(y)));
	#define _simd_s8x4_add_enable() _simd_s8x2_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_s8x8 ANVIL_SIMD_CALL _simd_s8x8_add(const register _simd_s8x8, const register _simd_s8x8 y) {
#ifdef _simd_s8x8_add_
	return _simd_s8x8_add_(x, y);
	#define _simd_s8x8_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_add_instruction_set>()
#elif defined(_simd_s8x16_add_)
	union SIMDUnion { _simd_s8x8 v1; _simd_s8x16 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s8x16_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s8x8_add_enable() _simd_s8x16_add_enable()
#elif defined(_simd_s8x32_add_)
	union SIMDUnion { _simd_s8x8 v1; _simd_s8x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s8x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s8x8_add_enable() _simd_s8x32_add_enable()
#elif defined(_simd_s8x64_add_)
	union SIMDUnion { _simd_s8x8 v1; _simd_s8x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s8x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s8x8_add_enable() _simd_s8x64_add_enable()
#else
	return _simd_s8x8_combine(
		_simd_s8x4_add(_simd_s8x8_splitlo(x), _simd_s8x8_splitlo(y)),
		_simd_s8x4_add(_simd_s8x8_splithi(x), _simd_s8x8_splithi(y)));
	#define _simd_s8x8_add_enable() _simd_s8x4_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_s8x16 ANVIL_SIMD_CALL _simd_s8x16_add(const register _simd_s8x16, const register _simd_s8x16 y) {
#ifdef _simd_s8x16_add_
	return _simd_s8x16_add_(x, y);
	#define _simd_s8x16_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_add_instruction_set>()
#elif defined(_simd_s8x32_add_)
	union SIMDUnion { _simd_s8x16 v1; _simd_s8x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s8x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s8x16_add_enable() _simd_s8x32_add_enable()
#elif defined(_simd_s8x64_add_)
	union SIMDUnion { _simd_s8x16 v1; _simd_s8x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s8x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s8x16_add_enable() _simd_s8x64_add_enable()
#else
	return _simd_s8x16_combine(
		_simd_s8x8_add(_simd_s8x16_splitlo(x), _simd_s8x16_splitlo(y)),
		_simd_s8x8_add(_simd_s8x16_splithi(x), _simd_s8x16_splithi(y)));
	#define _simd_s8x16_add_enable() _simd_s8x8_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_s8x32 ANVIL_SIMD_CALL _simd_s8x32_add(const register _simd_s8x32, const register _simd_s8x32 y) {
#ifdef _simd_s8x32_add_
	return _simd_s8x32_add_(x, y);
	#define _simd_s8x32_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_add_instruction_set>()
#elif defined(_simd_s8x64_add_)
	union SIMDUnion { _simd_s8x32 v1; _simd_s8x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_s8x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_s8x32_add_enable() _simd_s8x64_add_enable()
#else
	return _simd_s8x32_combine(
		_simd_s8x16_add(_simd_s8x32_splitlo(x), _simd_s8x32_splitlo(y)),
		_simd_s8x16_add(_simd_s8x32_splithi(x), _simd_s8x32_splithi(y)));
	#define _simd_s8x32_add_enable() _simd_s8x16_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_s8x64 ANVIL_SIMD_CALL _simd_s8x64_add(const register _simd_s8x64, const register _simd_s8x64 y) {
#ifdef _simd_s8x64_add_
	return _simd_s8x64_add_(x, y);
	#define _simd_s8x64_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_add_instruction_set>()
#else
	return _simd_s8x64_combine(
		_simd_s8x32_add(_simd_s8x64_splitlo(x), _simd_s8x64_splitlo(y)),
		_simd_s8x32_add(_simd_s8x64_splithi(x), _simd_s8x64_splithi(y)));
	#define _simd_s8x64_add_enable() _simd_s8x32_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_add(const register _simd_u8x2, const register _simd_u8x2 y) {
#ifdef _simd_u8x2_add_
	return _simd_u8x2_add_(x, y);
	#define _simd_u8x2_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_add_instruction_set>()
#elif defined(_simd_u8x4_add_)
	union SIMDUnion { _simd_u8x2 v1; _simd_u8x4 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u8x4_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u8x2_add_enable() _simd_u8x4_add_enable()
#elif defined(_simd_u8x8_add_)
	union SIMDUnion { _simd_u8x2 v1; _simd_u8x8 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u8x8_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u8x2_add_enable() _simd_u8x8_add_enable()
#elif defined(_simd_u8x16_add_)
	union SIMDUnion { _simd_u8x2 v1; _simd_u8x16 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u8x16_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u8x2_add_enable() _simd_u8x16_add_enable()
#elif defined(_simd_u8x32_add_)
	union SIMDUnion { _simd_u8x2 v1; _simd_u8x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u8x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u8x2_add_enable() _simd_u8x32_add_enable()
#elif defined(_simd_u8x64_add_)
	union SIMDUnion { _simd_u8x2 v1; _simd_u8x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u8x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u8x2_add_enable() _simd_u8x64_add_enable()
#else
	return _simd_u8x2_add_safe(x, y);
	#define _simd_u8x2_add_enable() true
#endif
}

static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_add(const register _simd_u8x4, const register _simd_u8x4 y) {
#ifdef _simd_u8x4_add_
	return _simd_u8x4_add_(x, y);
	#define _simd_u8x4_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_add_instruction_set>()
#elif defined(_simd_u8x8_add_)
	union SIMDUnion { _simd_u8x4 v1; _simd_u8x8 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u8x8_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u8x4_add_enable() _simd_u8x8_add_enable()
#elif defined(_simd_u8x16_add_)
	union SIMDUnion { _simd_u8x4 v1; _simd_u8x16 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u8x16_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u8x4_add_enable() _simd_u8x16_add_enable()
#elif defined(_simd_u8x32_add_)
	union SIMDUnion { _simd_u8x4 v1; _simd_u8x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u8x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u8x4_add_enable() _simd_u8x32_add_enable()
#elif defined(_simd_u8x64_add_)
	union SIMDUnion { _simd_u8x4 v1; _simd_u8x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u8x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u8x4_add_enable() _simd_u8x64_add_enable()
#else
	return _simd_u8x4_combine(
		_simd_u8x2_add(_simd_u8x4_splitlo(x), _simd_u8x4_splitlo(y)),
		_simd_u8x2_add(_simd_u8x4_splithi(x), _simd_u8x4_splithi(y)));
	#define _simd_u8x4_add_enable() _simd_u8x2_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_u8x8 ANVIL_SIMD_CALL _simd_u8x8_add(const register _simd_u8x8, const register _simd_u8x8 y) {
#ifdef _simd_u8x8_add_
	return _simd_u8x8_add_(x, y);
	#define _simd_u8x8_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_add_instruction_set>()
#elif defined(_simd_u8x16_add_)
	union SIMDUnion { _simd_u8x8 v1; _simd_u8x16 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u8x16_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u8x8_add_enable() _simd_u8x16_add_enable()
#elif defined(_simd_u8x32_add_)
	union SIMDUnion { _simd_u8x8 v1; _simd_u8x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u8x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u8x8_add_enable() _simd_u8x32_add_enable()
#elif defined(_simd_u8x64_add_)
	union SIMDUnion { _simd_u8x8 v1; _simd_u8x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u8x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u8x8_add_enable() _simd_u8x64_add_enable()
#else
	return _simd_u8x8_combine(
		_simd_u8x4_add(_simd_u8x8_splitlo(x), _simd_u8x8_splitlo(y)),
		_simd_u8x4_add(_simd_u8x8_splithi(x), _simd_u8x8_splithi(y)));
	#define _simd_u8x8_add_enable() _simd_u8x4_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_u8x16 ANVIL_SIMD_CALL _simd_u8x16_add(const register _simd_u8x16, const register _simd_u8x16 y) {
#ifdef _simd_u8x16_add_
	return _simd_u8x16_add_(x, y);
	#define _simd_u8x16_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_add_instruction_set>()
#elif defined(_simd_u8x32_add_)
	union SIMDUnion { _simd_u8x16 v1; _simd_u8x32 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u8x32_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u8x16_add_enable() _simd_u8x32_add_enable()
#elif defined(_simd_u8x64_add_)
	union SIMDUnion { _simd_u8x16 v1; _simd_u8x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u8x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u8x16_add_enable() _simd_u8x64_add_enable()
#else
	return _simd_u8x16_combine(
		_simd_u8x8_add(_simd_u8x16_splitlo(x), _simd_u8x16_splitlo(y)),
		_simd_u8x8_add(_simd_u8x16_splithi(x), _simd_u8x16_splithi(y)));
	#define _simd_u8x16_add_enable() _simd_u8x8_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_u8x32 ANVIL_SIMD_CALL _simd_u8x32_add(const register _simd_u8x32, const register _simd_u8x32 y) {
#ifdef _simd_u8x32_add_
	return _simd_u8x32_add_(x, y);
	#define _simd_u8x32_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_add_instruction_set>()
#elif defined(_simd_u8x64_add_)
	union SIMDUnion { _simd_u8x32 v1; _simd_u8x64 v2; };
	SIMDUnion x, y;
	x_.v1 = x;
	y_.v1 = y;
	x_.v2 = _simd_u8x64_add_(x_.v2, y_.v2);
	return x_.v1;
	#define _simd_u8x32_add_enable() _simd_u8x64_add_enable()
#else
	return _simd_u8x32_combine(
		_simd_u8x16_add(_simd_u8x32_splitlo(x), _simd_u8x32_splitlo(y)),
		_simd_u8x16_add(_simd_u8x32_splithi(x), _simd_u8x32_splithi(y)));
	#define _simd_u8x32_add_enable() _simd_u8x16_add_enable()
#endif
}

static ANVIL_STRONG_INLINE _simd_u8x64 ANVIL_SIMD_CALL _simd_u8x64_add(const register _simd_u8x64, const register _simd_u8x64 y) {
#ifdef _simd_u8x64_add_
	return _simd_u8x64_add_(x, y);
	#define _simd_u8x64_splitlo_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_add_instruction_set>()
#else
	return _simd_u8x64_combine(
		_simd_u8x32_add(_simd_u8x64_splitlo(x), _simd_u8x64_splitlo(y)),
		_simd_u8x32_add(_simd_u8x64_splithi(x), _simd_u8x64_splithi(y)));
	#define _simd_u8x64_add_enable() _simd_u8x32_add_enable()
#endif
}

