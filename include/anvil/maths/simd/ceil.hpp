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

#ifndef _simd_f64x1_ceil_safe
	#define _simd_f64x1_ceil_safe(X) std::ceil(X)
	#define _simd_f64x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_f64x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_f64x1_ceil_enabled() true
#endif

#define _simd_f64x2_ceil_safe(X)_simd_f64x2_combine_safe(\
	_simd_f64x1_ceil_safe(_simd_f64x2_splitlo_safe(X)),\
	_simd_f64x1_ceil_safe(_simd_f64x2_splithi_safe(X)))
#ifdef _simd_f64x2_ceil_
	#define _simd_f64x2_ceil(X) _simd_f64x2_ceil_(X)
	#define _simd_f64x2_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_ceil_instruction_set>()
#elif defined(_simd_f64x4_ceil_)
	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_ceil(const register _simd_f64x2 x) {
		union { _simd_f64x2 v1; _simd_f64x4 v2; };
		v1 = x;
		v2 = _simd_f64x4_ceil_(v2);
		return v1;
	}
	#define _simd_f64x2_ceil_enable() _simd_f64x4_ceil_enable()
#elif defined(_simd_f64x8_ceil_)
	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_ceil(const register _simd_f64x2 x) {
		union { _simd_f64x2 v1; _simd_f64x8 v2; };
		v1 = x;
		v2 = _simd_f64x8_ceil_(v2);
		return v1;
	}
	#define _simd_f64x2_ceil_enable() _simd_f64x8_ceil_enable()
#elif defined(_simd_f64x16_ceil_)
	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_ceil(const register _simd_f64x2 x) {
		union { _simd_f64x2 v1; _simd_f64x16 v2; };
		v1 = x;
		v2 = _simd_f64x16_ceil_(v2);
		return v1;
	}
	#define _simd_f64x2_ceil_enable() _simd_f64x16_ceil_enable()
#elif defined(_simd_f64x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_ceil(const register _simd_f64x2 x) {
		union { _simd_f64x2 v1; _simd_f64x32 v2; };
		v1 = x;
		v2 = _simd_f64x32_ceil_(v2);
		return v1;
	}
	#define _simd_f64x2_ceil_enable() _simd_f64x32_ceil_enable()
#elif defined(_simd_f64x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_ceil(const register _simd_f64x2 x) {
		union { _simd_f64x2 v1; _simd_f64x64 v2; };
		v1 = x;
		v2 = _simd_f64x64_ceil_(v2);
		return v1;
	}
	#define _simd_f64x2_ceil_enable() _simd_f64x64_ceil_enable()
#else
	#define _simd_f64x2_ceil(X) _simd_f64x2_combine(\
		_simd_f64x1_ceil(_simd_f64x2_splitlo(X)),\
		_simd_f64x1_ceil(_simd_f64x2_splithi(X)))
	#define _simd_f64x2_ceil_enable() (_simd_f64x1_ceil_enable() && _simd_f64x2_combine_enable() && _simd_f64x2_splitlo_enable()  && _simd_f64x2_splithi_enable())
#endif

#ifndef _simd_f64x1_ceil_safe
	#define _simd_f64x1_ceil_safe(X) std::ceil(X)
	#define _simd_f64x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_f64x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_f64x1_ceil_enabled() true
#endif

#define _simd_f64x4_ceil_safe(X)_simd_f64x4_combine_safe(\
	_simd_f64x2_ceil_safe(_simd_f64x4_splitlo_safe(X)),\
	_simd_f64x2_ceil_safe(_simd_f64x4_splithi_safe(X)))
#ifdef _simd_f64x4_ceil_
	#define _simd_f64x4_ceil(X) _simd_f64x4_ceil_(X)
	#define _simd_f64x4_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_ceil_instruction_set>()
#elif defined(_simd_f64x8_ceil_)
	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_ceil(const register _simd_f64x4 x) {
		union { _simd_f64x4 v1; _simd_f64x8 v2; };
		v1 = x;
		v2 = _simd_f64x8_ceil_(v2);
		return v1;
	}
	#define _simd_f64x4_ceil_enable() _simd_f64x8_ceil_enable()
#elif defined(_simd_f64x16_ceil_)
	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_ceil(const register _simd_f64x4 x) {
		union { _simd_f64x4 v1; _simd_f64x16 v2; };
		v1 = x;
		v2 = _simd_f64x16_ceil_(v2);
		return v1;
	}
	#define _simd_f64x4_ceil_enable() _simd_f64x16_ceil_enable()
#elif defined(_simd_f64x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_ceil(const register _simd_f64x4 x) {
		union { _simd_f64x4 v1; _simd_f64x32 v2; };
		v1 = x;
		v2 = _simd_f64x32_ceil_(v2);
		return v1;
	}
	#define _simd_f64x4_ceil_enable() _simd_f64x32_ceil_enable()
#elif defined(_simd_f64x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_ceil(const register _simd_f64x4 x) {
		union { _simd_f64x4 v1; _simd_f64x64 v2; };
		v1 = x;
		v2 = _simd_f64x64_ceil_(v2);
		return v1;
	}
	#define _simd_f64x4_ceil_enable() _simd_f64x64_ceil_enable()
#else
	#define _simd_f64x4_ceil(X) _simd_f64x4_combine(\
		_simd_f64x2_ceil(_simd_f64x4_splitlo(X)),\
		_simd_f64x2_ceil(_simd_f64x4_splithi(X)))
	#define _simd_f64x4_ceil_enable() (_simd_f64x2_ceil_enable() && _simd_f64x4_combine_enable() && _simd_f64x4_splitlo_enable()  && _simd_f64x4_splithi_enable())
#endif

#ifndef _simd_f64x1_ceil_safe
	#define _simd_f64x1_ceil_safe(X) std::ceil(X)
	#define _simd_f64x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_f64x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_f64x1_ceil_enabled() true
#endif

#define _simd_f64x8_ceil_safe(X)_simd_f64x8_combine_safe(\
	_simd_f64x4_ceil_safe(_simd_f64x8_splitlo_safe(X)),\
	_simd_f64x4_ceil_safe(_simd_f64x8_splithi_safe(X)))
#ifdef _simd_f64x8_ceil_
	#define _simd_f64x8_ceil(X) _simd_f64x8_ceil_(X)
	#define _simd_f64x8_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_ceil_instruction_set>()
#elif defined(_simd_f64x16_ceil_)
	static ANVIL_STRONG_INLINE _simd_f64x8 ANVIL_SIMD_CALL _simd_f64x8_ceil(const register _simd_f64x8 x) {
		union { _simd_f64x8 v1; _simd_f64x16 v2; };
		v1 = x;
		v2 = _simd_f64x16_ceil_(v2);
		return v1;
	}
	#define _simd_f64x8_ceil_enable() _simd_f64x16_ceil_enable()
#elif defined(_simd_f64x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_f64x8 ANVIL_SIMD_CALL _simd_f64x8_ceil(const register _simd_f64x8 x) {
		union { _simd_f64x8 v1; _simd_f64x32 v2; };
		v1 = x;
		v2 = _simd_f64x32_ceil_(v2);
		return v1;
	}
	#define _simd_f64x8_ceil_enable() _simd_f64x32_ceil_enable()
#elif defined(_simd_f64x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_f64x8 ANVIL_SIMD_CALL _simd_f64x8_ceil(const register _simd_f64x8 x) {
		union { _simd_f64x8 v1; _simd_f64x64 v2; };
		v1 = x;
		v2 = _simd_f64x64_ceil_(v2);
		return v1;
	}
	#define _simd_f64x8_ceil_enable() _simd_f64x64_ceil_enable()
#else
	#define _simd_f64x8_ceil(X) _simd_f64x8_combine(\
		_simd_f64x4_ceil(_simd_f64x8_splitlo(X)),\
		_simd_f64x4_ceil(_simd_f64x8_splithi(X)))
	#define _simd_f64x8_ceil_enable() (_simd_f64x4_ceil_enable() && _simd_f64x8_combine_enable() && _simd_f64x8_splitlo_enable()  && _simd_f64x8_splithi_enable())
#endif

#ifndef _simd_f64x1_ceil_safe
	#define _simd_f64x1_ceil_safe(X) std::ceil(X)
	#define _simd_f64x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_f64x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_f64x1_ceil_enabled() true
#endif

#define _simd_f64x16_ceil_safe(X)_simd_f64x16_combine_safe(\
	_simd_f64x8_ceil_safe(_simd_f64x16_splitlo_safe(X)),\
	_simd_f64x8_ceil_safe(_simd_f64x16_splithi_safe(X)))
#ifdef _simd_f64x16_ceil_
	#define _simd_f64x16_ceil(X) _simd_f64x16_ceil_(X)
	#define _simd_f64x16_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_ceil_instruction_set>()
#elif defined(_simd_f64x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_f64x16 ANVIL_SIMD_CALL _simd_f64x16_ceil(const register _simd_f64x16 x) {
		union { _simd_f64x16 v1; _simd_f64x32 v2; };
		v1 = x;
		v2 = _simd_f64x32_ceil_(v2);
		return v1;
	}
	#define _simd_f64x16_ceil_enable() _simd_f64x32_ceil_enable()
#elif defined(_simd_f64x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_f64x16 ANVIL_SIMD_CALL _simd_f64x16_ceil(const register _simd_f64x16 x) {
		union { _simd_f64x16 v1; _simd_f64x64 v2; };
		v1 = x;
		v2 = _simd_f64x64_ceil_(v2);
		return v1;
	}
	#define _simd_f64x16_ceil_enable() _simd_f64x64_ceil_enable()
#else
	#define _simd_f64x16_ceil(X) _simd_f64x16_combine(\
		_simd_f64x8_ceil(_simd_f64x16_splitlo(X)),\
		_simd_f64x8_ceil(_simd_f64x16_splithi(X)))
	#define _simd_f64x16_ceil_enable() (_simd_f64x8_ceil_enable() && _simd_f64x16_combine_enable() && _simd_f64x16_splitlo_enable()  && _simd_f64x16_splithi_enable())
#endif

#ifndef _simd_f64x1_ceil_safe
	#define _simd_f64x1_ceil_safe(X) std::ceil(X)
	#define _simd_f64x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_f64x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_f64x1_ceil_enabled() true
#endif

#define _simd_f64x32_ceil_safe(X)_simd_f64x32_combine_safe(\
	_simd_f64x16_ceil_safe(_simd_f64x32_splitlo_safe(X)),\
	_simd_f64x16_ceil_safe(_simd_f64x32_splithi_safe(X)))
#ifdef _simd_f64x32_ceil_
	#define _simd_f64x32_ceil(X) _simd_f64x32_ceil_(X)
	#define _simd_f64x32_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_ceil_instruction_set>()
#elif defined(_simd_f64x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_f64x32 ANVIL_SIMD_CALL _simd_f64x32_ceil(const register _simd_f64x32 x) {
		union { _simd_f64x32 v1; _simd_f64x64 v2; };
		v1 = x;
		v2 = _simd_f64x64_ceil_(v2);
		return v1;
	}
	#define _simd_f64x32_ceil_enable() _simd_f64x64_ceil_enable()
#else
	#define _simd_f64x32_ceil(X) _simd_f64x32_combine(\
		_simd_f64x16_ceil(_simd_f64x32_splitlo(X)),\
		_simd_f64x16_ceil(_simd_f64x32_splithi(X)))
	#define _simd_f64x32_ceil_enable() (_simd_f64x16_ceil_enable() && _simd_f64x32_combine_enable() && _simd_f64x32_splitlo_enable()  && _simd_f64x32_splithi_enable())
#endif

#ifndef _simd_f64x1_ceil_safe
	#define _simd_f64x1_ceil_safe(X) std::ceil(X)
	#define _simd_f64x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_f64x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_f64x1_ceil_enabled() true
#endif

#define _simd_f64x64_ceil_safe(X)_simd_f64x64_combine_safe(\
	_simd_f64x32_ceil_safe(_simd_f64x64_splitlo_safe(X)),\
	_simd_f64x32_ceil_safe(_simd_f64x64_splithi_safe(X)))
#ifdef _simd_f64x64_ceil_
	#define _simd_f64x64_ceil(X) _simd_f64x64_ceil_(X)
	#define _simd_f64x64_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_ceil_instruction_set>()
#else
	#define _simd_f64x64_ceil(X) _simd_f64x64_combine(\
		_simd_f64x32_ceil(_simd_f64x64_splitlo(X)),\
		_simd_f64x32_ceil(_simd_f64x64_splithi(X)))
	#define _simd_f64x64_ceil_enable() (_simd_f64x32_ceil_enable() && _simd_f64x64_combine_enable() && _simd_f64x64_splitlo_enable()  && _simd_f64x64_splithi_enable())
#endif

#ifndef _simd_f32x1_ceil_safe
	#define _simd_f32x1_ceil_safe(X) std::ceil(X)
	#define _simd_f32x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_f32x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_f32x1_ceil_enabled() true
#endif

#define _simd_f32x2_ceil_safe(X)_simd_f32x2_combine_safe(\
	_simd_f32x1_ceil_safe(_simd_f32x2_splitlo_safe(X)),\
	_simd_f32x1_ceil_safe(_simd_f32x2_splithi_safe(X)))
#ifdef _simd_f32x2_ceil_
	#define _simd_f32x2_ceil(X) _simd_f32x2_ceil_(X)
	#define _simd_f32x2_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_ceil_instruction_set>()
#elif defined(_simd_f32x4_ceil_)
	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_ceil(const register _simd_f32x2 x) {
		union { _simd_f32x2 v1; _simd_f32x4 v2; };
		v1 = x;
		v2 = _simd_f32x4_ceil_(v2);
		return v1;
	}
	#define _simd_f32x2_ceil_enable() _simd_f32x4_ceil_enable()
#elif defined(_simd_f32x8_ceil_)
	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_ceil(const register _simd_f32x2 x) {
		union { _simd_f32x2 v1; _simd_f32x8 v2; };
		v1 = x;
		v2 = _simd_f32x8_ceil_(v2);
		return v1;
	}
	#define _simd_f32x2_ceil_enable() _simd_f32x8_ceil_enable()
#elif defined(_simd_f32x16_ceil_)
	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_ceil(const register _simd_f32x2 x) {
		union { _simd_f32x2 v1; _simd_f32x16 v2; };
		v1 = x;
		v2 = _simd_f32x16_ceil_(v2);
		return v1;
	}
	#define _simd_f32x2_ceil_enable() _simd_f32x16_ceil_enable()
#elif defined(_simd_f32x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_ceil(const register _simd_f32x2 x) {
		union { _simd_f32x2 v1; _simd_f32x32 v2; };
		v1 = x;
		v2 = _simd_f32x32_ceil_(v2);
		return v1;
	}
	#define _simd_f32x2_ceil_enable() _simd_f32x32_ceil_enable()
#elif defined(_simd_f32x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_ceil(const register _simd_f32x2 x) {
		union { _simd_f32x2 v1; _simd_f32x64 v2; };
		v1 = x;
		v2 = _simd_f32x64_ceil_(v2);
		return v1;
	}
	#define _simd_f32x2_ceil_enable() _simd_f32x64_ceil_enable()
#else
	#define _simd_f32x2_ceil(X) _simd_f32x2_combine(\
		_simd_f32x1_ceil(_simd_f32x2_splitlo(X)),\
		_simd_f32x1_ceil(_simd_f32x2_splithi(X)))
	#define _simd_f32x2_ceil_enable() (_simd_f32x1_ceil_enable() && _simd_f32x2_combine_enable() && _simd_f32x2_splitlo_enable()  && _simd_f32x2_splithi_enable())
#endif

#ifndef _simd_f32x1_ceil_safe
	#define _simd_f32x1_ceil_safe(X) std::ceil(X)
	#define _simd_f32x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_f32x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_f32x1_ceil_enabled() true
#endif

#define _simd_f32x4_ceil_safe(X)_simd_f32x4_combine_safe(\
	_simd_f32x2_ceil_safe(_simd_f32x4_splitlo_safe(X)),\
	_simd_f32x2_ceil_safe(_simd_f32x4_splithi_safe(X)))
#ifdef _simd_f32x4_ceil_
	#define _simd_f32x4_ceil(X) _simd_f32x4_ceil_(X)
	#define _simd_f32x4_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_ceil_instruction_set>()
#elif defined(_simd_f32x8_ceil_)
	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_ceil(const register _simd_f32x4 x) {
		union { _simd_f32x4 v1; _simd_f32x8 v2; };
		v1 = x;
		v2 = _simd_f32x8_ceil_(v2);
		return v1;
	}
	#define _simd_f32x4_ceil_enable() _simd_f32x8_ceil_enable()
#elif defined(_simd_f32x16_ceil_)
	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_ceil(const register _simd_f32x4 x) {
		union { _simd_f32x4 v1; _simd_f32x16 v2; };
		v1 = x;
		v2 = _simd_f32x16_ceil_(v2);
		return v1;
	}
	#define _simd_f32x4_ceil_enable() _simd_f32x16_ceil_enable()
#elif defined(_simd_f32x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_ceil(const register _simd_f32x4 x) {
		union { _simd_f32x4 v1; _simd_f32x32 v2; };
		v1 = x;
		v2 = _simd_f32x32_ceil_(v2);
		return v1;
	}
	#define _simd_f32x4_ceil_enable() _simd_f32x32_ceil_enable()
#elif defined(_simd_f32x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_ceil(const register _simd_f32x4 x) {
		union { _simd_f32x4 v1; _simd_f32x64 v2; };
		v1 = x;
		v2 = _simd_f32x64_ceil_(v2);
		return v1;
	}
	#define _simd_f32x4_ceil_enable() _simd_f32x64_ceil_enable()
#else
	#define _simd_f32x4_ceil(X) _simd_f32x4_combine(\
		_simd_f32x2_ceil(_simd_f32x4_splitlo(X)),\
		_simd_f32x2_ceil(_simd_f32x4_splithi(X)))
	#define _simd_f32x4_ceil_enable() (_simd_f32x2_ceil_enable() && _simd_f32x4_combine_enable() && _simd_f32x4_splitlo_enable()  && _simd_f32x4_splithi_enable())
#endif

#ifndef _simd_f32x1_ceil_safe
	#define _simd_f32x1_ceil_safe(X) std::ceil(X)
	#define _simd_f32x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_f32x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_f32x1_ceil_enabled() true
#endif

#define _simd_f32x8_ceil_safe(X)_simd_f32x8_combine_safe(\
	_simd_f32x4_ceil_safe(_simd_f32x8_splitlo_safe(X)),\
	_simd_f32x4_ceil_safe(_simd_f32x8_splithi_safe(X)))
#ifdef _simd_f32x8_ceil_
	#define _simd_f32x8_ceil(X) _simd_f32x8_ceil_(X)
	#define _simd_f32x8_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_ceil_instruction_set>()
#elif defined(_simd_f32x16_ceil_)
	static ANVIL_STRONG_INLINE _simd_f32x8 ANVIL_SIMD_CALL _simd_f32x8_ceil(const register _simd_f32x8 x) {
		union { _simd_f32x8 v1; _simd_f32x16 v2; };
		v1 = x;
		v2 = _simd_f32x16_ceil_(v2);
		return v1;
	}
	#define _simd_f32x8_ceil_enable() _simd_f32x16_ceil_enable()
#elif defined(_simd_f32x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_f32x8 ANVIL_SIMD_CALL _simd_f32x8_ceil(const register _simd_f32x8 x) {
		union { _simd_f32x8 v1; _simd_f32x32 v2; };
		v1 = x;
		v2 = _simd_f32x32_ceil_(v2);
		return v1;
	}
	#define _simd_f32x8_ceil_enable() _simd_f32x32_ceil_enable()
#elif defined(_simd_f32x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_f32x8 ANVIL_SIMD_CALL _simd_f32x8_ceil(const register _simd_f32x8 x) {
		union { _simd_f32x8 v1; _simd_f32x64 v2; };
		v1 = x;
		v2 = _simd_f32x64_ceil_(v2);
		return v1;
	}
	#define _simd_f32x8_ceil_enable() _simd_f32x64_ceil_enable()
#else
	#define _simd_f32x8_ceil(X) _simd_f32x8_combine(\
		_simd_f32x4_ceil(_simd_f32x8_splitlo(X)),\
		_simd_f32x4_ceil(_simd_f32x8_splithi(X)))
	#define _simd_f32x8_ceil_enable() (_simd_f32x4_ceil_enable() && _simd_f32x8_combine_enable() && _simd_f32x8_splitlo_enable()  && _simd_f32x8_splithi_enable())
#endif

#ifndef _simd_f32x1_ceil_safe
	#define _simd_f32x1_ceil_safe(X) std::ceil(X)
	#define _simd_f32x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_f32x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_f32x1_ceil_enabled() true
#endif

#define _simd_f32x16_ceil_safe(X)_simd_f32x16_combine_safe(\
	_simd_f32x8_ceil_safe(_simd_f32x16_splitlo_safe(X)),\
	_simd_f32x8_ceil_safe(_simd_f32x16_splithi_safe(X)))
#ifdef _simd_f32x16_ceil_
	#define _simd_f32x16_ceil(X) _simd_f32x16_ceil_(X)
	#define _simd_f32x16_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_ceil_instruction_set>()
#elif defined(_simd_f32x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_f32x16 ANVIL_SIMD_CALL _simd_f32x16_ceil(const register _simd_f32x16 x) {
		union { _simd_f32x16 v1; _simd_f32x32 v2; };
		v1 = x;
		v2 = _simd_f32x32_ceil_(v2);
		return v1;
	}
	#define _simd_f32x16_ceil_enable() _simd_f32x32_ceil_enable()
#elif defined(_simd_f32x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_f32x16 ANVIL_SIMD_CALL _simd_f32x16_ceil(const register _simd_f32x16 x) {
		union { _simd_f32x16 v1; _simd_f32x64 v2; };
		v1 = x;
		v2 = _simd_f32x64_ceil_(v2);
		return v1;
	}
	#define _simd_f32x16_ceil_enable() _simd_f32x64_ceil_enable()
#else
	#define _simd_f32x16_ceil(X) _simd_f32x16_combine(\
		_simd_f32x8_ceil(_simd_f32x16_splitlo(X)),\
		_simd_f32x8_ceil(_simd_f32x16_splithi(X)))
	#define _simd_f32x16_ceil_enable() (_simd_f32x8_ceil_enable() && _simd_f32x16_combine_enable() && _simd_f32x16_splitlo_enable()  && _simd_f32x16_splithi_enable())
#endif

#ifndef _simd_f32x1_ceil_safe
	#define _simd_f32x1_ceil_safe(X) std::ceil(X)
	#define _simd_f32x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_f32x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_f32x1_ceil_enabled() true
#endif

#define _simd_f32x32_ceil_safe(X)_simd_f32x32_combine_safe(\
	_simd_f32x16_ceil_safe(_simd_f32x32_splitlo_safe(X)),\
	_simd_f32x16_ceil_safe(_simd_f32x32_splithi_safe(X)))
#ifdef _simd_f32x32_ceil_
	#define _simd_f32x32_ceil(X) _simd_f32x32_ceil_(X)
	#define _simd_f32x32_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_ceil_instruction_set>()
#elif defined(_simd_f32x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_f32x32 ANVIL_SIMD_CALL _simd_f32x32_ceil(const register _simd_f32x32 x) {
		union { _simd_f32x32 v1; _simd_f32x64 v2; };
		v1 = x;
		v2 = _simd_f32x64_ceil_(v2);
		return v1;
	}
	#define _simd_f32x32_ceil_enable() _simd_f32x64_ceil_enable()
#else
	#define _simd_f32x32_ceil(X) _simd_f32x32_combine(\
		_simd_f32x16_ceil(_simd_f32x32_splitlo(X)),\
		_simd_f32x16_ceil(_simd_f32x32_splithi(X)))
	#define _simd_f32x32_ceil_enable() (_simd_f32x16_ceil_enable() && _simd_f32x32_combine_enable() && _simd_f32x32_splitlo_enable()  && _simd_f32x32_splithi_enable())
#endif

#ifndef _simd_f32x1_ceil_safe
	#define _simd_f32x1_ceil_safe(X) std::ceil(X)
	#define _simd_f32x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_f32x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_f32x1_ceil_enabled() true
#endif

#define _simd_f32x64_ceil_safe(X)_simd_f32x64_combine_safe(\
	_simd_f32x32_ceil_safe(_simd_f32x64_splitlo_safe(X)),\
	_simd_f32x32_ceil_safe(_simd_f32x64_splithi_safe(X)))
#ifdef _simd_f32x64_ceil_
	#define _simd_f32x64_ceil(X) _simd_f32x64_ceil_(X)
	#define _simd_f32x64_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_ceil_instruction_set>()
#else
	#define _simd_f32x64_ceil(X) _simd_f32x64_combine(\
		_simd_f32x32_ceil(_simd_f32x64_splitlo(X)),\
		_simd_f32x32_ceil(_simd_f32x64_splithi(X)))
	#define _simd_f32x64_ceil_enable() (_simd_f32x32_ceil_enable() && _simd_f32x64_combine_enable() && _simd_f32x64_splitlo_enable()  && _simd_f32x64_splithi_enable())
#endif

#ifndef _simd_s64x1_ceil_safe
	#define _simd_s64x1_ceil_safe(X) X
	#define _simd_s64x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_s64x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_s64x1_ceil_enabled() true
#endif

#define _simd_s64x2_ceil_safe(X)_simd_s64x2_combine_safe(\
	_simd_s64x1_ceil_safe(_simd_s64x2_splitlo_safe(X)),\
	_simd_s64x1_ceil_safe(_simd_s64x2_splithi_safe(X)))
#ifdef _simd_s64x2_ceil_
	#define _simd_s64x2_ceil(X) _simd_s64x2_ceil_(X)
	#define _simd_s64x2_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_ceil_instruction_set>()
#elif defined(_simd_s64x4_ceil_)
	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_ceil(const register _simd_s64x2 x) {
		union { _simd_s64x2 v1; _simd_s64x4 v2; };
		v1 = x;
		v2 = _simd_s64x4_ceil_(v2);
		return v1;
	}
	#define _simd_s64x2_ceil_enable() _simd_s64x4_ceil_enable()
#elif defined(_simd_s64x8_ceil_)
	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_ceil(const register _simd_s64x2 x) {
		union { _simd_s64x2 v1; _simd_s64x8 v2; };
		v1 = x;
		v2 = _simd_s64x8_ceil_(v2);
		return v1;
	}
	#define _simd_s64x2_ceil_enable() _simd_s64x8_ceil_enable()
#elif defined(_simd_s64x16_ceil_)
	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_ceil(const register _simd_s64x2 x) {
		union { _simd_s64x2 v1; _simd_s64x16 v2; };
		v1 = x;
		v2 = _simd_s64x16_ceil_(v2);
		return v1;
	}
	#define _simd_s64x2_ceil_enable() _simd_s64x16_ceil_enable()
#elif defined(_simd_s64x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_ceil(const register _simd_s64x2 x) {
		union { _simd_s64x2 v1; _simd_s64x32 v2; };
		v1 = x;
		v2 = _simd_s64x32_ceil_(v2);
		return v1;
	}
	#define _simd_s64x2_ceil_enable() _simd_s64x32_ceil_enable()
#elif defined(_simd_s64x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_ceil(const register _simd_s64x2 x) {
		union { _simd_s64x2 v1; _simd_s64x64 v2; };
		v1 = x;
		v2 = _simd_s64x64_ceil_(v2);
		return v1;
	}
	#define _simd_s64x2_ceil_enable() _simd_s64x64_ceil_enable()
#else
	#define _simd_s64x2_ceil(X) _simd_s64x2_combine(\
		_simd_s64x1_ceil(_simd_s64x2_splitlo(X)),\
		_simd_s64x1_ceil(_simd_s64x2_splithi(X)))
	#define _simd_s64x2_ceil_enable() (_simd_s64x1_ceil_enable() && _simd_s64x2_combine_enable() && _simd_s64x2_splitlo_enable()  && _simd_s64x2_splithi_enable())
#endif

#ifndef _simd_s64x1_ceil_safe
	#define _simd_s64x1_ceil_safe(X) X
	#define _simd_s64x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_s64x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_s64x1_ceil_enabled() true
#endif

#define _simd_s64x4_ceil_safe(X)_simd_s64x4_combine_safe(\
	_simd_s64x2_ceil_safe(_simd_s64x4_splitlo_safe(X)),\
	_simd_s64x2_ceil_safe(_simd_s64x4_splithi_safe(X)))
#ifdef _simd_s64x4_ceil_
	#define _simd_s64x4_ceil(X) _simd_s64x4_ceil_(X)
	#define _simd_s64x4_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_ceil_instruction_set>()
#elif defined(_simd_s64x8_ceil_)
	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_ceil(const register _simd_s64x4 x) {
		union { _simd_s64x4 v1; _simd_s64x8 v2; };
		v1 = x;
		v2 = _simd_s64x8_ceil_(v2);
		return v1;
	}
	#define _simd_s64x4_ceil_enable() _simd_s64x8_ceil_enable()
#elif defined(_simd_s64x16_ceil_)
	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_ceil(const register _simd_s64x4 x) {
		union { _simd_s64x4 v1; _simd_s64x16 v2; };
		v1 = x;
		v2 = _simd_s64x16_ceil_(v2);
		return v1;
	}
	#define _simd_s64x4_ceil_enable() _simd_s64x16_ceil_enable()
#elif defined(_simd_s64x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_ceil(const register _simd_s64x4 x) {
		union { _simd_s64x4 v1; _simd_s64x32 v2; };
		v1 = x;
		v2 = _simd_s64x32_ceil_(v2);
		return v1;
	}
	#define _simd_s64x4_ceil_enable() _simd_s64x32_ceil_enable()
#elif defined(_simd_s64x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_ceil(const register _simd_s64x4 x) {
		union { _simd_s64x4 v1; _simd_s64x64 v2; };
		v1 = x;
		v2 = _simd_s64x64_ceil_(v2);
		return v1;
	}
	#define _simd_s64x4_ceil_enable() _simd_s64x64_ceil_enable()
#else
	#define _simd_s64x4_ceil(X) _simd_s64x4_combine(\
		_simd_s64x2_ceil(_simd_s64x4_splitlo(X)),\
		_simd_s64x2_ceil(_simd_s64x4_splithi(X)))
	#define _simd_s64x4_ceil_enable() (_simd_s64x2_ceil_enable() && _simd_s64x4_combine_enable() && _simd_s64x4_splitlo_enable()  && _simd_s64x4_splithi_enable())
#endif

#ifndef _simd_s64x1_ceil_safe
	#define _simd_s64x1_ceil_safe(X) X
	#define _simd_s64x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_s64x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_s64x1_ceil_enabled() true
#endif

#define _simd_s64x8_ceil_safe(X)_simd_s64x8_combine_safe(\
	_simd_s64x4_ceil_safe(_simd_s64x8_splitlo_safe(X)),\
	_simd_s64x4_ceil_safe(_simd_s64x8_splithi_safe(X)))
#ifdef _simd_s64x8_ceil_
	#define _simd_s64x8_ceil(X) _simd_s64x8_ceil_(X)
	#define _simd_s64x8_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_ceil_instruction_set>()
#elif defined(_simd_s64x16_ceil_)
	static ANVIL_STRONG_INLINE _simd_s64x8 ANVIL_SIMD_CALL _simd_s64x8_ceil(const register _simd_s64x8 x) {
		union { _simd_s64x8 v1; _simd_s64x16 v2; };
		v1 = x;
		v2 = _simd_s64x16_ceil_(v2);
		return v1;
	}
	#define _simd_s64x8_ceil_enable() _simd_s64x16_ceil_enable()
#elif defined(_simd_s64x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_s64x8 ANVIL_SIMD_CALL _simd_s64x8_ceil(const register _simd_s64x8 x) {
		union { _simd_s64x8 v1; _simd_s64x32 v2; };
		v1 = x;
		v2 = _simd_s64x32_ceil_(v2);
		return v1;
	}
	#define _simd_s64x8_ceil_enable() _simd_s64x32_ceil_enable()
#elif defined(_simd_s64x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_s64x8 ANVIL_SIMD_CALL _simd_s64x8_ceil(const register _simd_s64x8 x) {
		union { _simd_s64x8 v1; _simd_s64x64 v2; };
		v1 = x;
		v2 = _simd_s64x64_ceil_(v2);
		return v1;
	}
	#define _simd_s64x8_ceil_enable() _simd_s64x64_ceil_enable()
#else
	#define _simd_s64x8_ceil(X) _simd_s64x8_combine(\
		_simd_s64x4_ceil(_simd_s64x8_splitlo(X)),\
		_simd_s64x4_ceil(_simd_s64x8_splithi(X)))
	#define _simd_s64x8_ceil_enable() (_simd_s64x4_ceil_enable() && _simd_s64x8_combine_enable() && _simd_s64x8_splitlo_enable()  && _simd_s64x8_splithi_enable())
#endif

#ifndef _simd_s64x1_ceil_safe
	#define _simd_s64x1_ceil_safe(X) X
	#define _simd_s64x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_s64x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_s64x1_ceil_enabled() true
#endif

#define _simd_s64x16_ceil_safe(X)_simd_s64x16_combine_safe(\
	_simd_s64x8_ceil_safe(_simd_s64x16_splitlo_safe(X)),\
	_simd_s64x8_ceil_safe(_simd_s64x16_splithi_safe(X)))
#ifdef _simd_s64x16_ceil_
	#define _simd_s64x16_ceil(X) _simd_s64x16_ceil_(X)
	#define _simd_s64x16_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_ceil_instruction_set>()
#elif defined(_simd_s64x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_s64x16 ANVIL_SIMD_CALL _simd_s64x16_ceil(const register _simd_s64x16 x) {
		union { _simd_s64x16 v1; _simd_s64x32 v2; };
		v1 = x;
		v2 = _simd_s64x32_ceil_(v2);
		return v1;
	}
	#define _simd_s64x16_ceil_enable() _simd_s64x32_ceil_enable()
#elif defined(_simd_s64x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_s64x16 ANVIL_SIMD_CALL _simd_s64x16_ceil(const register _simd_s64x16 x) {
		union { _simd_s64x16 v1; _simd_s64x64 v2; };
		v1 = x;
		v2 = _simd_s64x64_ceil_(v2);
		return v1;
	}
	#define _simd_s64x16_ceil_enable() _simd_s64x64_ceil_enable()
#else
	#define _simd_s64x16_ceil(X) _simd_s64x16_combine(\
		_simd_s64x8_ceil(_simd_s64x16_splitlo(X)),\
		_simd_s64x8_ceil(_simd_s64x16_splithi(X)))
	#define _simd_s64x16_ceil_enable() (_simd_s64x8_ceil_enable() && _simd_s64x16_combine_enable() && _simd_s64x16_splitlo_enable()  && _simd_s64x16_splithi_enable())
#endif

#ifndef _simd_s64x1_ceil_safe
	#define _simd_s64x1_ceil_safe(X) X
	#define _simd_s64x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_s64x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_s64x1_ceil_enabled() true
#endif

#define _simd_s64x32_ceil_safe(X)_simd_s64x32_combine_safe(\
	_simd_s64x16_ceil_safe(_simd_s64x32_splitlo_safe(X)),\
	_simd_s64x16_ceil_safe(_simd_s64x32_splithi_safe(X)))
#ifdef _simd_s64x32_ceil_
	#define _simd_s64x32_ceil(X) _simd_s64x32_ceil_(X)
	#define _simd_s64x32_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_ceil_instruction_set>()
#elif defined(_simd_s64x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_s64x32 ANVIL_SIMD_CALL _simd_s64x32_ceil(const register _simd_s64x32 x) {
		union { _simd_s64x32 v1; _simd_s64x64 v2; };
		v1 = x;
		v2 = _simd_s64x64_ceil_(v2);
		return v1;
	}
	#define _simd_s64x32_ceil_enable() _simd_s64x64_ceil_enable()
#else
	#define _simd_s64x32_ceil(X) _simd_s64x32_combine(\
		_simd_s64x16_ceil(_simd_s64x32_splitlo(X)),\
		_simd_s64x16_ceil(_simd_s64x32_splithi(X)))
	#define _simd_s64x32_ceil_enable() (_simd_s64x16_ceil_enable() && _simd_s64x32_combine_enable() && _simd_s64x32_splitlo_enable()  && _simd_s64x32_splithi_enable())
#endif

#ifndef _simd_s64x1_ceil_safe
	#define _simd_s64x1_ceil_safe(X) X
	#define _simd_s64x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_s64x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_s64x1_ceil_enabled() true
#endif

#define _simd_s64x64_ceil_safe(X)_simd_s64x64_combine_safe(\
	_simd_s64x32_ceil_safe(_simd_s64x64_splitlo_safe(X)),\
	_simd_s64x32_ceil_safe(_simd_s64x64_splithi_safe(X)))
#ifdef _simd_s64x64_ceil_
	#define _simd_s64x64_ceil(X) _simd_s64x64_ceil_(X)
	#define _simd_s64x64_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_ceil_instruction_set>()
#else
	#define _simd_s64x64_ceil(X) _simd_s64x64_combine(\
		_simd_s64x32_ceil(_simd_s64x64_splitlo(X)),\
		_simd_s64x32_ceil(_simd_s64x64_splithi(X)))
	#define _simd_s64x64_ceil_enable() (_simd_s64x32_ceil_enable() && _simd_s64x64_combine_enable() && _simd_s64x64_splitlo_enable()  && _simd_s64x64_splithi_enable())
#endif

#ifndef _simd_u64x1_ceil_safe
	#define _simd_u64x1_ceil_safe(X) X
	#define _simd_u64x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_u64x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_u64x1_ceil_enabled() true
#endif

#define _simd_u64x2_ceil_safe(X)_simd_u64x2_combine_safe(\
	_simd_u64x1_ceil_safe(_simd_u64x2_splitlo_safe(X)),\
	_simd_u64x1_ceil_safe(_simd_u64x2_splithi_safe(X)))
#ifdef _simd_u64x2_ceil_
	#define _simd_u64x2_ceil(X) _simd_u64x2_ceil_(X)
	#define _simd_u64x2_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_ceil_instruction_set>()
#elif defined(_simd_u64x4_ceil_)
	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_ceil(const register _simd_u64x2 x) {
		union { _simd_u64x2 v1; _simd_u64x4 v2; };
		v1 = x;
		v2 = _simd_u64x4_ceil_(v2);
		return v1;
	}
	#define _simd_u64x2_ceil_enable() _simd_u64x4_ceil_enable()
#elif defined(_simd_u64x8_ceil_)
	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_ceil(const register _simd_u64x2 x) {
		union { _simd_u64x2 v1; _simd_u64x8 v2; };
		v1 = x;
		v2 = _simd_u64x8_ceil_(v2);
		return v1;
	}
	#define _simd_u64x2_ceil_enable() _simd_u64x8_ceil_enable()
#elif defined(_simd_u64x16_ceil_)
	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_ceil(const register _simd_u64x2 x) {
		union { _simd_u64x2 v1; _simd_u64x16 v2; };
		v1 = x;
		v2 = _simd_u64x16_ceil_(v2);
		return v1;
	}
	#define _simd_u64x2_ceil_enable() _simd_u64x16_ceil_enable()
#elif defined(_simd_u64x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_ceil(const register _simd_u64x2 x) {
		union { _simd_u64x2 v1; _simd_u64x32 v2; };
		v1 = x;
		v2 = _simd_u64x32_ceil_(v2);
		return v1;
	}
	#define _simd_u64x2_ceil_enable() _simd_u64x32_ceil_enable()
#elif defined(_simd_u64x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_ceil(const register _simd_u64x2 x) {
		union { _simd_u64x2 v1; _simd_u64x64 v2; };
		v1 = x;
		v2 = _simd_u64x64_ceil_(v2);
		return v1;
	}
	#define _simd_u64x2_ceil_enable() _simd_u64x64_ceil_enable()
#else
	#define _simd_u64x2_ceil(X) _simd_u64x2_combine(\
		_simd_u64x1_ceil(_simd_u64x2_splitlo(X)),\
		_simd_u64x1_ceil(_simd_u64x2_splithi(X)))
	#define _simd_u64x2_ceil_enable() (_simd_u64x1_ceil_enable() && _simd_u64x2_combine_enable() && _simd_u64x2_splitlo_enable()  && _simd_u64x2_splithi_enable())
#endif

#ifndef _simd_u64x1_ceil_safe
	#define _simd_u64x1_ceil_safe(X) X
	#define _simd_u64x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_u64x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_u64x1_ceil_enabled() true
#endif

#define _simd_u64x4_ceil_safe(X)_simd_u64x4_combine_safe(\
	_simd_u64x2_ceil_safe(_simd_u64x4_splitlo_safe(X)),\
	_simd_u64x2_ceil_safe(_simd_u64x4_splithi_safe(X)))
#ifdef _simd_u64x4_ceil_
	#define _simd_u64x4_ceil(X) _simd_u64x4_ceil_(X)
	#define _simd_u64x4_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_ceil_instruction_set>()
#elif defined(_simd_u64x8_ceil_)
	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_ceil(const register _simd_u64x4 x) {
		union { _simd_u64x4 v1; _simd_u64x8 v2; };
		v1 = x;
		v2 = _simd_u64x8_ceil_(v2);
		return v1;
	}
	#define _simd_u64x4_ceil_enable() _simd_u64x8_ceil_enable()
#elif defined(_simd_u64x16_ceil_)
	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_ceil(const register _simd_u64x4 x) {
		union { _simd_u64x4 v1; _simd_u64x16 v2; };
		v1 = x;
		v2 = _simd_u64x16_ceil_(v2);
		return v1;
	}
	#define _simd_u64x4_ceil_enable() _simd_u64x16_ceil_enable()
#elif defined(_simd_u64x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_ceil(const register _simd_u64x4 x) {
		union { _simd_u64x4 v1; _simd_u64x32 v2; };
		v1 = x;
		v2 = _simd_u64x32_ceil_(v2);
		return v1;
	}
	#define _simd_u64x4_ceil_enable() _simd_u64x32_ceil_enable()
#elif defined(_simd_u64x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_ceil(const register _simd_u64x4 x) {
		union { _simd_u64x4 v1; _simd_u64x64 v2; };
		v1 = x;
		v2 = _simd_u64x64_ceil_(v2);
		return v1;
	}
	#define _simd_u64x4_ceil_enable() _simd_u64x64_ceil_enable()
#else
	#define _simd_u64x4_ceil(X) _simd_u64x4_combine(\
		_simd_u64x2_ceil(_simd_u64x4_splitlo(X)),\
		_simd_u64x2_ceil(_simd_u64x4_splithi(X)))
	#define _simd_u64x4_ceil_enable() (_simd_u64x2_ceil_enable() && _simd_u64x4_combine_enable() && _simd_u64x4_splitlo_enable()  && _simd_u64x4_splithi_enable())
#endif

#ifndef _simd_u64x1_ceil_safe
	#define _simd_u64x1_ceil_safe(X) X
	#define _simd_u64x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_u64x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_u64x1_ceil_enabled() true
#endif

#define _simd_u64x8_ceil_safe(X)_simd_u64x8_combine_safe(\
	_simd_u64x4_ceil_safe(_simd_u64x8_splitlo_safe(X)),\
	_simd_u64x4_ceil_safe(_simd_u64x8_splithi_safe(X)))
#ifdef _simd_u64x8_ceil_
	#define _simd_u64x8_ceil(X) _simd_u64x8_ceil_(X)
	#define _simd_u64x8_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_ceil_instruction_set>()
#elif defined(_simd_u64x16_ceil_)
	static ANVIL_STRONG_INLINE _simd_u64x8 ANVIL_SIMD_CALL _simd_u64x8_ceil(const register _simd_u64x8 x) {
		union { _simd_u64x8 v1; _simd_u64x16 v2; };
		v1 = x;
		v2 = _simd_u64x16_ceil_(v2);
		return v1;
	}
	#define _simd_u64x8_ceil_enable() _simd_u64x16_ceil_enable()
#elif defined(_simd_u64x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_u64x8 ANVIL_SIMD_CALL _simd_u64x8_ceil(const register _simd_u64x8 x) {
		union { _simd_u64x8 v1; _simd_u64x32 v2; };
		v1 = x;
		v2 = _simd_u64x32_ceil_(v2);
		return v1;
	}
	#define _simd_u64x8_ceil_enable() _simd_u64x32_ceil_enable()
#elif defined(_simd_u64x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_u64x8 ANVIL_SIMD_CALL _simd_u64x8_ceil(const register _simd_u64x8 x) {
		union { _simd_u64x8 v1; _simd_u64x64 v2; };
		v1 = x;
		v2 = _simd_u64x64_ceil_(v2);
		return v1;
	}
	#define _simd_u64x8_ceil_enable() _simd_u64x64_ceil_enable()
#else
	#define _simd_u64x8_ceil(X) _simd_u64x8_combine(\
		_simd_u64x4_ceil(_simd_u64x8_splitlo(X)),\
		_simd_u64x4_ceil(_simd_u64x8_splithi(X)))
	#define _simd_u64x8_ceil_enable() (_simd_u64x4_ceil_enable() && _simd_u64x8_combine_enable() && _simd_u64x8_splitlo_enable()  && _simd_u64x8_splithi_enable())
#endif

#ifndef _simd_u64x1_ceil_safe
	#define _simd_u64x1_ceil_safe(X) X
	#define _simd_u64x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_u64x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_u64x1_ceil_enabled() true
#endif

#define _simd_u64x16_ceil_safe(X)_simd_u64x16_combine_safe(\
	_simd_u64x8_ceil_safe(_simd_u64x16_splitlo_safe(X)),\
	_simd_u64x8_ceil_safe(_simd_u64x16_splithi_safe(X)))
#ifdef _simd_u64x16_ceil_
	#define _simd_u64x16_ceil(X) _simd_u64x16_ceil_(X)
	#define _simd_u64x16_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_ceil_instruction_set>()
#elif defined(_simd_u64x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_u64x16 ANVIL_SIMD_CALL _simd_u64x16_ceil(const register _simd_u64x16 x) {
		union { _simd_u64x16 v1; _simd_u64x32 v2; };
		v1 = x;
		v2 = _simd_u64x32_ceil_(v2);
		return v1;
	}
	#define _simd_u64x16_ceil_enable() _simd_u64x32_ceil_enable()
#elif defined(_simd_u64x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_u64x16 ANVIL_SIMD_CALL _simd_u64x16_ceil(const register _simd_u64x16 x) {
		union { _simd_u64x16 v1; _simd_u64x64 v2; };
		v1 = x;
		v2 = _simd_u64x64_ceil_(v2);
		return v1;
	}
	#define _simd_u64x16_ceil_enable() _simd_u64x64_ceil_enable()
#else
	#define _simd_u64x16_ceil(X) _simd_u64x16_combine(\
		_simd_u64x8_ceil(_simd_u64x16_splitlo(X)),\
		_simd_u64x8_ceil(_simd_u64x16_splithi(X)))
	#define _simd_u64x16_ceil_enable() (_simd_u64x8_ceil_enable() && _simd_u64x16_combine_enable() && _simd_u64x16_splitlo_enable()  && _simd_u64x16_splithi_enable())
#endif

#ifndef _simd_u64x1_ceil_safe
	#define _simd_u64x1_ceil_safe(X) X
	#define _simd_u64x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_u64x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_u64x1_ceil_enabled() true
#endif

#define _simd_u64x32_ceil_safe(X)_simd_u64x32_combine_safe(\
	_simd_u64x16_ceil_safe(_simd_u64x32_splitlo_safe(X)),\
	_simd_u64x16_ceil_safe(_simd_u64x32_splithi_safe(X)))
#ifdef _simd_u64x32_ceil_
	#define _simd_u64x32_ceil(X) _simd_u64x32_ceil_(X)
	#define _simd_u64x32_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_ceil_instruction_set>()
#elif defined(_simd_u64x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_u64x32 ANVIL_SIMD_CALL _simd_u64x32_ceil(const register _simd_u64x32 x) {
		union { _simd_u64x32 v1; _simd_u64x64 v2; };
		v1 = x;
		v2 = _simd_u64x64_ceil_(v2);
		return v1;
	}
	#define _simd_u64x32_ceil_enable() _simd_u64x64_ceil_enable()
#else
	#define _simd_u64x32_ceil(X) _simd_u64x32_combine(\
		_simd_u64x16_ceil(_simd_u64x32_splitlo(X)),\
		_simd_u64x16_ceil(_simd_u64x32_splithi(X)))
	#define _simd_u64x32_ceil_enable() (_simd_u64x16_ceil_enable() && _simd_u64x32_combine_enable() && _simd_u64x32_splitlo_enable()  && _simd_u64x32_splithi_enable())
#endif

#ifndef _simd_u64x1_ceil_safe
	#define _simd_u64x1_ceil_safe(X) X
	#define _simd_u64x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_u64x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_u64x1_ceil_enabled() true
#endif

#define _simd_u64x64_ceil_safe(X)_simd_u64x64_combine_safe(\
	_simd_u64x32_ceil_safe(_simd_u64x64_splitlo_safe(X)),\
	_simd_u64x32_ceil_safe(_simd_u64x64_splithi_safe(X)))
#ifdef _simd_u64x64_ceil_
	#define _simd_u64x64_ceil(X) _simd_u64x64_ceil_(X)
	#define _simd_u64x64_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_ceil_instruction_set>()
#else
	#define _simd_u64x64_ceil(X) _simd_u64x64_combine(\
		_simd_u64x32_ceil(_simd_u64x64_splitlo(X)),\
		_simd_u64x32_ceil(_simd_u64x64_splithi(X)))
	#define _simd_u64x64_ceil_enable() (_simd_u64x32_ceil_enable() && _simd_u64x64_combine_enable() && _simd_u64x64_splitlo_enable()  && _simd_u64x64_splithi_enable())
#endif

#ifndef _simd_s32x1_ceil_safe
	#define _simd_s32x1_ceil_safe(X) X
	#define _simd_s32x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_s32x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_s32x1_ceil_enabled() true
#endif

#define _simd_s32x2_ceil_safe(X)_simd_s32x2_combine_safe(\
	_simd_s32x1_ceil_safe(_simd_s32x2_splitlo_safe(X)),\
	_simd_s32x1_ceil_safe(_simd_s32x2_splithi_safe(X)))
#ifdef _simd_s32x2_ceil_
	#define _simd_s32x2_ceil(X) _simd_s32x2_ceil_(X)
	#define _simd_s32x2_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_ceil_instruction_set>()
#elif defined(_simd_s32x4_ceil_)
	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_ceil(const register _simd_s32x2 x) {
		union { _simd_s32x2 v1; _simd_s32x4 v2; };
		v1 = x;
		v2 = _simd_s32x4_ceil_(v2);
		return v1;
	}
	#define _simd_s32x2_ceil_enable() _simd_s32x4_ceil_enable()
#elif defined(_simd_s32x8_ceil_)
	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_ceil(const register _simd_s32x2 x) {
		union { _simd_s32x2 v1; _simd_s32x8 v2; };
		v1 = x;
		v2 = _simd_s32x8_ceil_(v2);
		return v1;
	}
	#define _simd_s32x2_ceil_enable() _simd_s32x8_ceil_enable()
#elif defined(_simd_s32x16_ceil_)
	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_ceil(const register _simd_s32x2 x) {
		union { _simd_s32x2 v1; _simd_s32x16 v2; };
		v1 = x;
		v2 = _simd_s32x16_ceil_(v2);
		return v1;
	}
	#define _simd_s32x2_ceil_enable() _simd_s32x16_ceil_enable()
#elif defined(_simd_s32x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_ceil(const register _simd_s32x2 x) {
		union { _simd_s32x2 v1; _simd_s32x32 v2; };
		v1 = x;
		v2 = _simd_s32x32_ceil_(v2);
		return v1;
	}
	#define _simd_s32x2_ceil_enable() _simd_s32x32_ceil_enable()
#elif defined(_simd_s32x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_ceil(const register _simd_s32x2 x) {
		union { _simd_s32x2 v1; _simd_s32x64 v2; };
		v1 = x;
		v2 = _simd_s32x64_ceil_(v2);
		return v1;
	}
	#define _simd_s32x2_ceil_enable() _simd_s32x64_ceil_enable()
#else
	#define _simd_s32x2_ceil(X) _simd_s32x2_combine(\
		_simd_s32x1_ceil(_simd_s32x2_splitlo(X)),\
		_simd_s32x1_ceil(_simd_s32x2_splithi(X)))
	#define _simd_s32x2_ceil_enable() (_simd_s32x1_ceil_enable() && _simd_s32x2_combine_enable() && _simd_s32x2_splitlo_enable()  && _simd_s32x2_splithi_enable())
#endif

#ifndef _simd_s32x1_ceil_safe
	#define _simd_s32x1_ceil_safe(X) X
	#define _simd_s32x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_s32x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_s32x1_ceil_enabled() true
#endif

#define _simd_s32x4_ceil_safe(X)_simd_s32x4_combine_safe(\
	_simd_s32x2_ceil_safe(_simd_s32x4_splitlo_safe(X)),\
	_simd_s32x2_ceil_safe(_simd_s32x4_splithi_safe(X)))
#ifdef _simd_s32x4_ceil_
	#define _simd_s32x4_ceil(X) _simd_s32x4_ceil_(X)
	#define _simd_s32x4_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_ceil_instruction_set>()
#elif defined(_simd_s32x8_ceil_)
	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_ceil(const register _simd_s32x4 x) {
		union { _simd_s32x4 v1; _simd_s32x8 v2; };
		v1 = x;
		v2 = _simd_s32x8_ceil_(v2);
		return v1;
	}
	#define _simd_s32x4_ceil_enable() _simd_s32x8_ceil_enable()
#elif defined(_simd_s32x16_ceil_)
	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_ceil(const register _simd_s32x4 x) {
		union { _simd_s32x4 v1; _simd_s32x16 v2; };
		v1 = x;
		v2 = _simd_s32x16_ceil_(v2);
		return v1;
	}
	#define _simd_s32x4_ceil_enable() _simd_s32x16_ceil_enable()
#elif defined(_simd_s32x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_ceil(const register _simd_s32x4 x) {
		union { _simd_s32x4 v1; _simd_s32x32 v2; };
		v1 = x;
		v2 = _simd_s32x32_ceil_(v2);
		return v1;
	}
	#define _simd_s32x4_ceil_enable() _simd_s32x32_ceil_enable()
#elif defined(_simd_s32x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_ceil(const register _simd_s32x4 x) {
		union { _simd_s32x4 v1; _simd_s32x64 v2; };
		v1 = x;
		v2 = _simd_s32x64_ceil_(v2);
		return v1;
	}
	#define _simd_s32x4_ceil_enable() _simd_s32x64_ceil_enable()
#else
	#define _simd_s32x4_ceil(X) _simd_s32x4_combine(\
		_simd_s32x2_ceil(_simd_s32x4_splitlo(X)),\
		_simd_s32x2_ceil(_simd_s32x4_splithi(X)))
	#define _simd_s32x4_ceil_enable() (_simd_s32x2_ceil_enable() && _simd_s32x4_combine_enable() && _simd_s32x4_splitlo_enable()  && _simd_s32x4_splithi_enable())
#endif

#ifndef _simd_s32x1_ceil_safe
	#define _simd_s32x1_ceil_safe(X) X
	#define _simd_s32x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_s32x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_s32x1_ceil_enabled() true
#endif

#define _simd_s32x8_ceil_safe(X)_simd_s32x8_combine_safe(\
	_simd_s32x4_ceil_safe(_simd_s32x8_splitlo_safe(X)),\
	_simd_s32x4_ceil_safe(_simd_s32x8_splithi_safe(X)))
#ifdef _simd_s32x8_ceil_
	#define _simd_s32x8_ceil(X) _simd_s32x8_ceil_(X)
	#define _simd_s32x8_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_ceil_instruction_set>()
#elif defined(_simd_s32x16_ceil_)
	static ANVIL_STRONG_INLINE _simd_s32x8 ANVIL_SIMD_CALL _simd_s32x8_ceil(const register _simd_s32x8 x) {
		union { _simd_s32x8 v1; _simd_s32x16 v2; };
		v1 = x;
		v2 = _simd_s32x16_ceil_(v2);
		return v1;
	}
	#define _simd_s32x8_ceil_enable() _simd_s32x16_ceil_enable()
#elif defined(_simd_s32x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_s32x8 ANVIL_SIMD_CALL _simd_s32x8_ceil(const register _simd_s32x8 x) {
		union { _simd_s32x8 v1; _simd_s32x32 v2; };
		v1 = x;
		v2 = _simd_s32x32_ceil_(v2);
		return v1;
	}
	#define _simd_s32x8_ceil_enable() _simd_s32x32_ceil_enable()
#elif defined(_simd_s32x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_s32x8 ANVIL_SIMD_CALL _simd_s32x8_ceil(const register _simd_s32x8 x) {
		union { _simd_s32x8 v1; _simd_s32x64 v2; };
		v1 = x;
		v2 = _simd_s32x64_ceil_(v2);
		return v1;
	}
	#define _simd_s32x8_ceil_enable() _simd_s32x64_ceil_enable()
#else
	#define _simd_s32x8_ceil(X) _simd_s32x8_combine(\
		_simd_s32x4_ceil(_simd_s32x8_splitlo(X)),\
		_simd_s32x4_ceil(_simd_s32x8_splithi(X)))
	#define _simd_s32x8_ceil_enable() (_simd_s32x4_ceil_enable() && _simd_s32x8_combine_enable() && _simd_s32x8_splitlo_enable()  && _simd_s32x8_splithi_enable())
#endif

#ifndef _simd_s32x1_ceil_safe
	#define _simd_s32x1_ceil_safe(X) X
	#define _simd_s32x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_s32x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_s32x1_ceil_enabled() true
#endif

#define _simd_s32x16_ceil_safe(X)_simd_s32x16_combine_safe(\
	_simd_s32x8_ceil_safe(_simd_s32x16_splitlo_safe(X)),\
	_simd_s32x8_ceil_safe(_simd_s32x16_splithi_safe(X)))
#ifdef _simd_s32x16_ceil_
	#define _simd_s32x16_ceil(X) _simd_s32x16_ceil_(X)
	#define _simd_s32x16_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_ceil_instruction_set>()
#elif defined(_simd_s32x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_s32x16 ANVIL_SIMD_CALL _simd_s32x16_ceil(const register _simd_s32x16 x) {
		union { _simd_s32x16 v1; _simd_s32x32 v2; };
		v1 = x;
		v2 = _simd_s32x32_ceil_(v2);
		return v1;
	}
	#define _simd_s32x16_ceil_enable() _simd_s32x32_ceil_enable()
#elif defined(_simd_s32x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_s32x16 ANVIL_SIMD_CALL _simd_s32x16_ceil(const register _simd_s32x16 x) {
		union { _simd_s32x16 v1; _simd_s32x64 v2; };
		v1 = x;
		v2 = _simd_s32x64_ceil_(v2);
		return v1;
	}
	#define _simd_s32x16_ceil_enable() _simd_s32x64_ceil_enable()
#else
	#define _simd_s32x16_ceil(X) _simd_s32x16_combine(\
		_simd_s32x8_ceil(_simd_s32x16_splitlo(X)),\
		_simd_s32x8_ceil(_simd_s32x16_splithi(X)))
	#define _simd_s32x16_ceil_enable() (_simd_s32x8_ceil_enable() && _simd_s32x16_combine_enable() && _simd_s32x16_splitlo_enable()  && _simd_s32x16_splithi_enable())
#endif

#ifndef _simd_s32x1_ceil_safe
	#define _simd_s32x1_ceil_safe(X) X
	#define _simd_s32x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_s32x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_s32x1_ceil_enabled() true
#endif

#define _simd_s32x32_ceil_safe(X)_simd_s32x32_combine_safe(\
	_simd_s32x16_ceil_safe(_simd_s32x32_splitlo_safe(X)),\
	_simd_s32x16_ceil_safe(_simd_s32x32_splithi_safe(X)))
#ifdef _simd_s32x32_ceil_
	#define _simd_s32x32_ceil(X) _simd_s32x32_ceil_(X)
	#define _simd_s32x32_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_ceil_instruction_set>()
#elif defined(_simd_s32x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_s32x32 ANVIL_SIMD_CALL _simd_s32x32_ceil(const register _simd_s32x32 x) {
		union { _simd_s32x32 v1; _simd_s32x64 v2; };
		v1 = x;
		v2 = _simd_s32x64_ceil_(v2);
		return v1;
	}
	#define _simd_s32x32_ceil_enable() _simd_s32x64_ceil_enable()
#else
	#define _simd_s32x32_ceil(X) _simd_s32x32_combine(\
		_simd_s32x16_ceil(_simd_s32x32_splitlo(X)),\
		_simd_s32x16_ceil(_simd_s32x32_splithi(X)))
	#define _simd_s32x32_ceil_enable() (_simd_s32x16_ceil_enable() && _simd_s32x32_combine_enable() && _simd_s32x32_splitlo_enable()  && _simd_s32x32_splithi_enable())
#endif

#ifndef _simd_s32x1_ceil_safe
	#define _simd_s32x1_ceil_safe(X) X
	#define _simd_s32x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_s32x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_s32x1_ceil_enabled() true
#endif

#define _simd_s32x64_ceil_safe(X)_simd_s32x64_combine_safe(\
	_simd_s32x32_ceil_safe(_simd_s32x64_splitlo_safe(X)),\
	_simd_s32x32_ceil_safe(_simd_s32x64_splithi_safe(X)))
#ifdef _simd_s32x64_ceil_
	#define _simd_s32x64_ceil(X) _simd_s32x64_ceil_(X)
	#define _simd_s32x64_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_ceil_instruction_set>()
#else
	#define _simd_s32x64_ceil(X) _simd_s32x64_combine(\
		_simd_s32x32_ceil(_simd_s32x64_splitlo(X)),\
		_simd_s32x32_ceil(_simd_s32x64_splithi(X)))
	#define _simd_s32x64_ceil_enable() (_simd_s32x32_ceil_enable() && _simd_s32x64_combine_enable() && _simd_s32x64_splitlo_enable()  && _simd_s32x64_splithi_enable())
#endif

#ifndef _simd_u32x1_ceil_safe
	#define _simd_u32x1_ceil_safe(X) X
	#define _simd_u32x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_u32x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_u32x1_ceil_enabled() true
#endif

#define _simd_u32x2_ceil_safe(X)_simd_u32x2_combine_safe(\
	_simd_u32x1_ceil_safe(_simd_u32x2_splitlo_safe(X)),\
	_simd_u32x1_ceil_safe(_simd_u32x2_splithi_safe(X)))
#ifdef _simd_u32x2_ceil_
	#define _simd_u32x2_ceil(X) _simd_u32x2_ceil_(X)
	#define _simd_u32x2_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_ceil_instruction_set>()
#elif defined(_simd_u32x4_ceil_)
	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_ceil(const register _simd_u32x2 x) {
		union { _simd_u32x2 v1; _simd_u32x4 v2; };
		v1 = x;
		v2 = _simd_u32x4_ceil_(v2);
		return v1;
	}
	#define _simd_u32x2_ceil_enable() _simd_u32x4_ceil_enable()
#elif defined(_simd_u32x8_ceil_)
	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_ceil(const register _simd_u32x2 x) {
		union { _simd_u32x2 v1; _simd_u32x8 v2; };
		v1 = x;
		v2 = _simd_u32x8_ceil_(v2);
		return v1;
	}
	#define _simd_u32x2_ceil_enable() _simd_u32x8_ceil_enable()
#elif defined(_simd_u32x16_ceil_)
	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_ceil(const register _simd_u32x2 x) {
		union { _simd_u32x2 v1; _simd_u32x16 v2; };
		v1 = x;
		v2 = _simd_u32x16_ceil_(v2);
		return v1;
	}
	#define _simd_u32x2_ceil_enable() _simd_u32x16_ceil_enable()
#elif defined(_simd_u32x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_ceil(const register _simd_u32x2 x) {
		union { _simd_u32x2 v1; _simd_u32x32 v2; };
		v1 = x;
		v2 = _simd_u32x32_ceil_(v2);
		return v1;
	}
	#define _simd_u32x2_ceil_enable() _simd_u32x32_ceil_enable()
#elif defined(_simd_u32x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_ceil(const register _simd_u32x2 x) {
		union { _simd_u32x2 v1; _simd_u32x64 v2; };
		v1 = x;
		v2 = _simd_u32x64_ceil_(v2);
		return v1;
	}
	#define _simd_u32x2_ceil_enable() _simd_u32x64_ceil_enable()
#else
	#define _simd_u32x2_ceil(X) _simd_u32x2_combine(\
		_simd_u32x1_ceil(_simd_u32x2_splitlo(X)),\
		_simd_u32x1_ceil(_simd_u32x2_splithi(X)))
	#define _simd_u32x2_ceil_enable() (_simd_u32x1_ceil_enable() && _simd_u32x2_combine_enable() && _simd_u32x2_splitlo_enable()  && _simd_u32x2_splithi_enable())
#endif

#ifndef _simd_u32x1_ceil_safe
	#define _simd_u32x1_ceil_safe(X) X
	#define _simd_u32x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_u32x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_u32x1_ceil_enabled() true
#endif

#define _simd_u32x4_ceil_safe(X)_simd_u32x4_combine_safe(\
	_simd_u32x2_ceil_safe(_simd_u32x4_splitlo_safe(X)),\
	_simd_u32x2_ceil_safe(_simd_u32x4_splithi_safe(X)))
#ifdef _simd_u32x4_ceil_
	#define _simd_u32x4_ceil(X) _simd_u32x4_ceil_(X)
	#define _simd_u32x4_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_ceil_instruction_set>()
#elif defined(_simd_u32x8_ceil_)
	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_ceil(const register _simd_u32x4 x) {
		union { _simd_u32x4 v1; _simd_u32x8 v2; };
		v1 = x;
		v2 = _simd_u32x8_ceil_(v2);
		return v1;
	}
	#define _simd_u32x4_ceil_enable() _simd_u32x8_ceil_enable()
#elif defined(_simd_u32x16_ceil_)
	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_ceil(const register _simd_u32x4 x) {
		union { _simd_u32x4 v1; _simd_u32x16 v2; };
		v1 = x;
		v2 = _simd_u32x16_ceil_(v2);
		return v1;
	}
	#define _simd_u32x4_ceil_enable() _simd_u32x16_ceil_enable()
#elif defined(_simd_u32x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_ceil(const register _simd_u32x4 x) {
		union { _simd_u32x4 v1; _simd_u32x32 v2; };
		v1 = x;
		v2 = _simd_u32x32_ceil_(v2);
		return v1;
	}
	#define _simd_u32x4_ceil_enable() _simd_u32x32_ceil_enable()
#elif defined(_simd_u32x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_ceil(const register _simd_u32x4 x) {
		union { _simd_u32x4 v1; _simd_u32x64 v2; };
		v1 = x;
		v2 = _simd_u32x64_ceil_(v2);
		return v1;
	}
	#define _simd_u32x4_ceil_enable() _simd_u32x64_ceil_enable()
#else
	#define _simd_u32x4_ceil(X) _simd_u32x4_combine(\
		_simd_u32x2_ceil(_simd_u32x4_splitlo(X)),\
		_simd_u32x2_ceil(_simd_u32x4_splithi(X)))
	#define _simd_u32x4_ceil_enable() (_simd_u32x2_ceil_enable() && _simd_u32x4_combine_enable() && _simd_u32x4_splitlo_enable()  && _simd_u32x4_splithi_enable())
#endif

#ifndef _simd_u32x1_ceil_safe
	#define _simd_u32x1_ceil_safe(X) X
	#define _simd_u32x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_u32x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_u32x1_ceil_enabled() true
#endif

#define _simd_u32x8_ceil_safe(X)_simd_u32x8_combine_safe(\
	_simd_u32x4_ceil_safe(_simd_u32x8_splitlo_safe(X)),\
	_simd_u32x4_ceil_safe(_simd_u32x8_splithi_safe(X)))
#ifdef _simd_u32x8_ceil_
	#define _simd_u32x8_ceil(X) _simd_u32x8_ceil_(X)
	#define _simd_u32x8_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_ceil_instruction_set>()
#elif defined(_simd_u32x16_ceil_)
	static ANVIL_STRONG_INLINE _simd_u32x8 ANVIL_SIMD_CALL _simd_u32x8_ceil(const register _simd_u32x8 x) {
		union { _simd_u32x8 v1; _simd_u32x16 v2; };
		v1 = x;
		v2 = _simd_u32x16_ceil_(v2);
		return v1;
	}
	#define _simd_u32x8_ceil_enable() _simd_u32x16_ceil_enable()
#elif defined(_simd_u32x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_u32x8 ANVIL_SIMD_CALL _simd_u32x8_ceil(const register _simd_u32x8 x) {
		union { _simd_u32x8 v1; _simd_u32x32 v2; };
		v1 = x;
		v2 = _simd_u32x32_ceil_(v2);
		return v1;
	}
	#define _simd_u32x8_ceil_enable() _simd_u32x32_ceil_enable()
#elif defined(_simd_u32x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_u32x8 ANVIL_SIMD_CALL _simd_u32x8_ceil(const register _simd_u32x8 x) {
		union { _simd_u32x8 v1; _simd_u32x64 v2; };
		v1 = x;
		v2 = _simd_u32x64_ceil_(v2);
		return v1;
	}
	#define _simd_u32x8_ceil_enable() _simd_u32x64_ceil_enable()
#else
	#define _simd_u32x8_ceil(X) _simd_u32x8_combine(\
		_simd_u32x4_ceil(_simd_u32x8_splitlo(X)),\
		_simd_u32x4_ceil(_simd_u32x8_splithi(X)))
	#define _simd_u32x8_ceil_enable() (_simd_u32x4_ceil_enable() && _simd_u32x8_combine_enable() && _simd_u32x8_splitlo_enable()  && _simd_u32x8_splithi_enable())
#endif

#ifndef _simd_u32x1_ceil_safe
	#define _simd_u32x1_ceil_safe(X) X
	#define _simd_u32x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_u32x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_u32x1_ceil_enabled() true
#endif

#define _simd_u32x16_ceil_safe(X)_simd_u32x16_combine_safe(\
	_simd_u32x8_ceil_safe(_simd_u32x16_splitlo_safe(X)),\
	_simd_u32x8_ceil_safe(_simd_u32x16_splithi_safe(X)))
#ifdef _simd_u32x16_ceil_
	#define _simd_u32x16_ceil(X) _simd_u32x16_ceil_(X)
	#define _simd_u32x16_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_ceil_instruction_set>()
#elif defined(_simd_u32x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_u32x16 ANVIL_SIMD_CALL _simd_u32x16_ceil(const register _simd_u32x16 x) {
		union { _simd_u32x16 v1; _simd_u32x32 v2; };
		v1 = x;
		v2 = _simd_u32x32_ceil_(v2);
		return v1;
	}
	#define _simd_u32x16_ceil_enable() _simd_u32x32_ceil_enable()
#elif defined(_simd_u32x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_u32x16 ANVIL_SIMD_CALL _simd_u32x16_ceil(const register _simd_u32x16 x) {
		union { _simd_u32x16 v1; _simd_u32x64 v2; };
		v1 = x;
		v2 = _simd_u32x64_ceil_(v2);
		return v1;
	}
	#define _simd_u32x16_ceil_enable() _simd_u32x64_ceil_enable()
#else
	#define _simd_u32x16_ceil(X) _simd_u32x16_combine(\
		_simd_u32x8_ceil(_simd_u32x16_splitlo(X)),\
		_simd_u32x8_ceil(_simd_u32x16_splithi(X)))
	#define _simd_u32x16_ceil_enable() (_simd_u32x8_ceil_enable() && _simd_u32x16_combine_enable() && _simd_u32x16_splitlo_enable()  && _simd_u32x16_splithi_enable())
#endif

#ifndef _simd_u32x1_ceil_safe
	#define _simd_u32x1_ceil_safe(X) X
	#define _simd_u32x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_u32x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_u32x1_ceil_enabled() true
#endif

#define _simd_u32x32_ceil_safe(X)_simd_u32x32_combine_safe(\
	_simd_u32x16_ceil_safe(_simd_u32x32_splitlo_safe(X)),\
	_simd_u32x16_ceil_safe(_simd_u32x32_splithi_safe(X)))
#ifdef _simd_u32x32_ceil_
	#define _simd_u32x32_ceil(X) _simd_u32x32_ceil_(X)
	#define _simd_u32x32_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_ceil_instruction_set>()
#elif defined(_simd_u32x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_u32x32 ANVIL_SIMD_CALL _simd_u32x32_ceil(const register _simd_u32x32 x) {
		union { _simd_u32x32 v1; _simd_u32x64 v2; };
		v1 = x;
		v2 = _simd_u32x64_ceil_(v2);
		return v1;
	}
	#define _simd_u32x32_ceil_enable() _simd_u32x64_ceil_enable()
#else
	#define _simd_u32x32_ceil(X) _simd_u32x32_combine(\
		_simd_u32x16_ceil(_simd_u32x32_splitlo(X)),\
		_simd_u32x16_ceil(_simd_u32x32_splithi(X)))
	#define _simd_u32x32_ceil_enable() (_simd_u32x16_ceil_enable() && _simd_u32x32_combine_enable() && _simd_u32x32_splitlo_enable()  && _simd_u32x32_splithi_enable())
#endif

#ifndef _simd_u32x1_ceil_safe
	#define _simd_u32x1_ceil_safe(X) X
	#define _simd_u32x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_u32x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_u32x1_ceil_enabled() true
#endif

#define _simd_u32x64_ceil_safe(X)_simd_u32x64_combine_safe(\
	_simd_u32x32_ceil_safe(_simd_u32x64_splitlo_safe(X)),\
	_simd_u32x32_ceil_safe(_simd_u32x64_splithi_safe(X)))
#ifdef _simd_u32x64_ceil_
	#define _simd_u32x64_ceil(X) _simd_u32x64_ceil_(X)
	#define _simd_u32x64_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_ceil_instruction_set>()
#else
	#define _simd_u32x64_ceil(X) _simd_u32x64_combine(\
		_simd_u32x32_ceil(_simd_u32x64_splitlo(X)),\
		_simd_u32x32_ceil(_simd_u32x64_splithi(X)))
	#define _simd_u32x64_ceil_enable() (_simd_u32x32_ceil_enable() && _simd_u32x64_combine_enable() && _simd_u32x64_splitlo_enable()  && _simd_u32x64_splithi_enable())
#endif

#ifndef _simd_s16x1_ceil_safe
	#define _simd_s16x1_ceil_safe(X) X
	#define _simd_s16x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_s16x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_s16x1_ceil_enabled() true
#endif

#define _simd_s16x2_ceil_safe(X)_simd_s16x2_combine_safe(\
	_simd_s16x1_ceil_safe(_simd_s16x2_splitlo_safe(X)),\
	_simd_s16x1_ceil_safe(_simd_s16x2_splithi_safe(X)))
#ifdef _simd_s16x2_ceil_
	#define _simd_s16x2_ceil(X) _simd_s16x2_ceil_(X)
	#define _simd_s16x2_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_ceil_instruction_set>()
#elif defined(_simd_s16x4_ceil_)
	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_ceil(const register _simd_s16x2 x) {
		union { _simd_s16x2 v1; _simd_s16x4 v2; };
		v1 = x;
		v2 = _simd_s16x4_ceil_(v2);
		return v1;
	}
	#define _simd_s16x2_ceil_enable() _simd_s16x4_ceil_enable()
#elif defined(_simd_s16x8_ceil_)
	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_ceil(const register _simd_s16x2 x) {
		union { _simd_s16x2 v1; _simd_s16x8 v2; };
		v1 = x;
		v2 = _simd_s16x8_ceil_(v2);
		return v1;
	}
	#define _simd_s16x2_ceil_enable() _simd_s16x8_ceil_enable()
#elif defined(_simd_s16x16_ceil_)
	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_ceil(const register _simd_s16x2 x) {
		union { _simd_s16x2 v1; _simd_s16x16 v2; };
		v1 = x;
		v2 = _simd_s16x16_ceil_(v2);
		return v1;
	}
	#define _simd_s16x2_ceil_enable() _simd_s16x16_ceil_enable()
#elif defined(_simd_s16x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_ceil(const register _simd_s16x2 x) {
		union { _simd_s16x2 v1; _simd_s16x32 v2; };
		v1 = x;
		v2 = _simd_s16x32_ceil_(v2);
		return v1;
	}
	#define _simd_s16x2_ceil_enable() _simd_s16x32_ceil_enable()
#elif defined(_simd_s16x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_ceil(const register _simd_s16x2 x) {
		union { _simd_s16x2 v1; _simd_s16x64 v2; };
		v1 = x;
		v2 = _simd_s16x64_ceil_(v2);
		return v1;
	}
	#define _simd_s16x2_ceil_enable() _simd_s16x64_ceil_enable()
#else
	#define _simd_s16x2_ceil(X) _simd_s16x2_combine(\
		_simd_s16x1_ceil(_simd_s16x2_splitlo(X)),\
		_simd_s16x1_ceil(_simd_s16x2_splithi(X)))
	#define _simd_s16x2_ceil_enable() (_simd_s16x1_ceil_enable() && _simd_s16x2_combine_enable() && _simd_s16x2_splitlo_enable()  && _simd_s16x2_splithi_enable())
#endif

#ifndef _simd_s16x1_ceil_safe
	#define _simd_s16x1_ceil_safe(X) X
	#define _simd_s16x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_s16x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_s16x1_ceil_enabled() true
#endif

#define _simd_s16x4_ceil_safe(X)_simd_s16x4_combine_safe(\
	_simd_s16x2_ceil_safe(_simd_s16x4_splitlo_safe(X)),\
	_simd_s16x2_ceil_safe(_simd_s16x4_splithi_safe(X)))
#ifdef _simd_s16x4_ceil_
	#define _simd_s16x4_ceil(X) _simd_s16x4_ceil_(X)
	#define _simd_s16x4_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_ceil_instruction_set>()
#elif defined(_simd_s16x8_ceil_)
	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_ceil(const register _simd_s16x4 x) {
		union { _simd_s16x4 v1; _simd_s16x8 v2; };
		v1 = x;
		v2 = _simd_s16x8_ceil_(v2);
		return v1;
	}
	#define _simd_s16x4_ceil_enable() _simd_s16x8_ceil_enable()
#elif defined(_simd_s16x16_ceil_)
	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_ceil(const register _simd_s16x4 x) {
		union { _simd_s16x4 v1; _simd_s16x16 v2; };
		v1 = x;
		v2 = _simd_s16x16_ceil_(v2);
		return v1;
	}
	#define _simd_s16x4_ceil_enable() _simd_s16x16_ceil_enable()
#elif defined(_simd_s16x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_ceil(const register _simd_s16x4 x) {
		union { _simd_s16x4 v1; _simd_s16x32 v2; };
		v1 = x;
		v2 = _simd_s16x32_ceil_(v2);
		return v1;
	}
	#define _simd_s16x4_ceil_enable() _simd_s16x32_ceil_enable()
#elif defined(_simd_s16x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_ceil(const register _simd_s16x4 x) {
		union { _simd_s16x4 v1; _simd_s16x64 v2; };
		v1 = x;
		v2 = _simd_s16x64_ceil_(v2);
		return v1;
	}
	#define _simd_s16x4_ceil_enable() _simd_s16x64_ceil_enable()
#else
	#define _simd_s16x4_ceil(X) _simd_s16x4_combine(\
		_simd_s16x2_ceil(_simd_s16x4_splitlo(X)),\
		_simd_s16x2_ceil(_simd_s16x4_splithi(X)))
	#define _simd_s16x4_ceil_enable() (_simd_s16x2_ceil_enable() && _simd_s16x4_combine_enable() && _simd_s16x4_splitlo_enable()  && _simd_s16x4_splithi_enable())
#endif

#ifndef _simd_s16x1_ceil_safe
	#define _simd_s16x1_ceil_safe(X) X
	#define _simd_s16x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_s16x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_s16x1_ceil_enabled() true
#endif

#define _simd_s16x8_ceil_safe(X)_simd_s16x8_combine_safe(\
	_simd_s16x4_ceil_safe(_simd_s16x8_splitlo_safe(X)),\
	_simd_s16x4_ceil_safe(_simd_s16x8_splithi_safe(X)))
#ifdef _simd_s16x8_ceil_
	#define _simd_s16x8_ceil(X) _simd_s16x8_ceil_(X)
	#define _simd_s16x8_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_ceil_instruction_set>()
#elif defined(_simd_s16x16_ceil_)
	static ANVIL_STRONG_INLINE _simd_s16x8 ANVIL_SIMD_CALL _simd_s16x8_ceil(const register _simd_s16x8 x) {
		union { _simd_s16x8 v1; _simd_s16x16 v2; };
		v1 = x;
		v2 = _simd_s16x16_ceil_(v2);
		return v1;
	}
	#define _simd_s16x8_ceil_enable() _simd_s16x16_ceil_enable()
#elif defined(_simd_s16x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_s16x8 ANVIL_SIMD_CALL _simd_s16x8_ceil(const register _simd_s16x8 x) {
		union { _simd_s16x8 v1; _simd_s16x32 v2; };
		v1 = x;
		v2 = _simd_s16x32_ceil_(v2);
		return v1;
	}
	#define _simd_s16x8_ceil_enable() _simd_s16x32_ceil_enable()
#elif defined(_simd_s16x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_s16x8 ANVIL_SIMD_CALL _simd_s16x8_ceil(const register _simd_s16x8 x) {
		union { _simd_s16x8 v1; _simd_s16x64 v2; };
		v1 = x;
		v2 = _simd_s16x64_ceil_(v2);
		return v1;
	}
	#define _simd_s16x8_ceil_enable() _simd_s16x64_ceil_enable()
#else
	#define _simd_s16x8_ceil(X) _simd_s16x8_combine(\
		_simd_s16x4_ceil(_simd_s16x8_splitlo(X)),\
		_simd_s16x4_ceil(_simd_s16x8_splithi(X)))
	#define _simd_s16x8_ceil_enable() (_simd_s16x4_ceil_enable() && _simd_s16x8_combine_enable() && _simd_s16x8_splitlo_enable()  && _simd_s16x8_splithi_enable())
#endif

#ifndef _simd_s16x1_ceil_safe
	#define _simd_s16x1_ceil_safe(X) X
	#define _simd_s16x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_s16x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_s16x1_ceil_enabled() true
#endif

#define _simd_s16x16_ceil_safe(X)_simd_s16x16_combine_safe(\
	_simd_s16x8_ceil_safe(_simd_s16x16_splitlo_safe(X)),\
	_simd_s16x8_ceil_safe(_simd_s16x16_splithi_safe(X)))
#ifdef _simd_s16x16_ceil_
	#define _simd_s16x16_ceil(X) _simd_s16x16_ceil_(X)
	#define _simd_s16x16_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_ceil_instruction_set>()
#elif defined(_simd_s16x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_s16x16 ANVIL_SIMD_CALL _simd_s16x16_ceil(const register _simd_s16x16 x) {
		union { _simd_s16x16 v1; _simd_s16x32 v2; };
		v1 = x;
		v2 = _simd_s16x32_ceil_(v2);
		return v1;
	}
	#define _simd_s16x16_ceil_enable() _simd_s16x32_ceil_enable()
#elif defined(_simd_s16x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_s16x16 ANVIL_SIMD_CALL _simd_s16x16_ceil(const register _simd_s16x16 x) {
		union { _simd_s16x16 v1; _simd_s16x64 v2; };
		v1 = x;
		v2 = _simd_s16x64_ceil_(v2);
		return v1;
	}
	#define _simd_s16x16_ceil_enable() _simd_s16x64_ceil_enable()
#else
	#define _simd_s16x16_ceil(X) _simd_s16x16_combine(\
		_simd_s16x8_ceil(_simd_s16x16_splitlo(X)),\
		_simd_s16x8_ceil(_simd_s16x16_splithi(X)))
	#define _simd_s16x16_ceil_enable() (_simd_s16x8_ceil_enable() && _simd_s16x16_combine_enable() && _simd_s16x16_splitlo_enable()  && _simd_s16x16_splithi_enable())
#endif

#ifndef _simd_s16x1_ceil_safe
	#define _simd_s16x1_ceil_safe(X) X
	#define _simd_s16x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_s16x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_s16x1_ceil_enabled() true
#endif

#define _simd_s16x32_ceil_safe(X)_simd_s16x32_combine_safe(\
	_simd_s16x16_ceil_safe(_simd_s16x32_splitlo_safe(X)),\
	_simd_s16x16_ceil_safe(_simd_s16x32_splithi_safe(X)))
#ifdef _simd_s16x32_ceil_
	#define _simd_s16x32_ceil(X) _simd_s16x32_ceil_(X)
	#define _simd_s16x32_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_ceil_instruction_set>()
#elif defined(_simd_s16x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_s16x32 ANVIL_SIMD_CALL _simd_s16x32_ceil(const register _simd_s16x32 x) {
		union { _simd_s16x32 v1; _simd_s16x64 v2; };
		v1 = x;
		v2 = _simd_s16x64_ceil_(v2);
		return v1;
	}
	#define _simd_s16x32_ceil_enable() _simd_s16x64_ceil_enable()
#else
	#define _simd_s16x32_ceil(X) _simd_s16x32_combine(\
		_simd_s16x16_ceil(_simd_s16x32_splitlo(X)),\
		_simd_s16x16_ceil(_simd_s16x32_splithi(X)))
	#define _simd_s16x32_ceil_enable() (_simd_s16x16_ceil_enable() && _simd_s16x32_combine_enable() && _simd_s16x32_splitlo_enable()  && _simd_s16x32_splithi_enable())
#endif

#ifndef _simd_s16x1_ceil_safe
	#define _simd_s16x1_ceil_safe(X) X
	#define _simd_s16x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_s16x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_s16x1_ceil_enabled() true
#endif

#define _simd_s16x64_ceil_safe(X)_simd_s16x64_combine_safe(\
	_simd_s16x32_ceil_safe(_simd_s16x64_splitlo_safe(X)),\
	_simd_s16x32_ceil_safe(_simd_s16x64_splithi_safe(X)))
#ifdef _simd_s16x64_ceil_
	#define _simd_s16x64_ceil(X) _simd_s16x64_ceil_(X)
	#define _simd_s16x64_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_ceil_instruction_set>()
#else
	#define _simd_s16x64_ceil(X) _simd_s16x64_combine(\
		_simd_s16x32_ceil(_simd_s16x64_splitlo(X)),\
		_simd_s16x32_ceil(_simd_s16x64_splithi(X)))
	#define _simd_s16x64_ceil_enable() (_simd_s16x32_ceil_enable() && _simd_s16x64_combine_enable() && _simd_s16x64_splitlo_enable()  && _simd_s16x64_splithi_enable())
#endif

#ifndef _simd_u16x1_ceil_safe
	#define _simd_u16x1_ceil_safe(X) X
	#define _simd_u16x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_u16x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_u16x1_ceil_enabled() true
#endif

#define _simd_u16x2_ceil_safe(X)_simd_u16x2_combine_safe(\
	_simd_u16x1_ceil_safe(_simd_u16x2_splitlo_safe(X)),\
	_simd_u16x1_ceil_safe(_simd_u16x2_splithi_safe(X)))
#ifdef _simd_u16x2_ceil_
	#define _simd_u16x2_ceil(X) _simd_u16x2_ceil_(X)
	#define _simd_u16x2_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_ceil_instruction_set>()
#elif defined(_simd_u16x4_ceil_)
	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_ceil(const register _simd_u16x2 x) {
		union { _simd_u16x2 v1; _simd_u16x4 v2; };
		v1 = x;
		v2 = _simd_u16x4_ceil_(v2);
		return v1;
	}
	#define _simd_u16x2_ceil_enable() _simd_u16x4_ceil_enable()
#elif defined(_simd_u16x8_ceil_)
	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_ceil(const register _simd_u16x2 x) {
		union { _simd_u16x2 v1; _simd_u16x8 v2; };
		v1 = x;
		v2 = _simd_u16x8_ceil_(v2);
		return v1;
	}
	#define _simd_u16x2_ceil_enable() _simd_u16x8_ceil_enable()
#elif defined(_simd_u16x16_ceil_)
	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_ceil(const register _simd_u16x2 x) {
		union { _simd_u16x2 v1; _simd_u16x16 v2; };
		v1 = x;
		v2 = _simd_u16x16_ceil_(v2);
		return v1;
	}
	#define _simd_u16x2_ceil_enable() _simd_u16x16_ceil_enable()
#elif defined(_simd_u16x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_ceil(const register _simd_u16x2 x) {
		union { _simd_u16x2 v1; _simd_u16x32 v2; };
		v1 = x;
		v2 = _simd_u16x32_ceil_(v2);
		return v1;
	}
	#define _simd_u16x2_ceil_enable() _simd_u16x32_ceil_enable()
#elif defined(_simd_u16x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_ceil(const register _simd_u16x2 x) {
		union { _simd_u16x2 v1; _simd_u16x64 v2; };
		v1 = x;
		v2 = _simd_u16x64_ceil_(v2);
		return v1;
	}
	#define _simd_u16x2_ceil_enable() _simd_u16x64_ceil_enable()
#else
	#define _simd_u16x2_ceil(X) _simd_u16x2_combine(\
		_simd_u16x1_ceil(_simd_u16x2_splitlo(X)),\
		_simd_u16x1_ceil(_simd_u16x2_splithi(X)))
	#define _simd_u16x2_ceil_enable() (_simd_u16x1_ceil_enable() && _simd_u16x2_combine_enable() && _simd_u16x2_splitlo_enable()  && _simd_u16x2_splithi_enable())
#endif

#ifndef _simd_u16x1_ceil_safe
	#define _simd_u16x1_ceil_safe(X) X
	#define _simd_u16x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_u16x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_u16x1_ceil_enabled() true
#endif

#define _simd_u16x4_ceil_safe(X)_simd_u16x4_combine_safe(\
	_simd_u16x2_ceil_safe(_simd_u16x4_splitlo_safe(X)),\
	_simd_u16x2_ceil_safe(_simd_u16x4_splithi_safe(X)))
#ifdef _simd_u16x4_ceil_
	#define _simd_u16x4_ceil(X) _simd_u16x4_ceil_(X)
	#define _simd_u16x4_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_ceil_instruction_set>()
#elif defined(_simd_u16x8_ceil_)
	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_ceil(const register _simd_u16x4 x) {
		union { _simd_u16x4 v1; _simd_u16x8 v2; };
		v1 = x;
		v2 = _simd_u16x8_ceil_(v2);
		return v1;
	}
	#define _simd_u16x4_ceil_enable() _simd_u16x8_ceil_enable()
#elif defined(_simd_u16x16_ceil_)
	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_ceil(const register _simd_u16x4 x) {
		union { _simd_u16x4 v1; _simd_u16x16 v2; };
		v1 = x;
		v2 = _simd_u16x16_ceil_(v2);
		return v1;
	}
	#define _simd_u16x4_ceil_enable() _simd_u16x16_ceil_enable()
#elif defined(_simd_u16x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_ceil(const register _simd_u16x4 x) {
		union { _simd_u16x4 v1; _simd_u16x32 v2; };
		v1 = x;
		v2 = _simd_u16x32_ceil_(v2);
		return v1;
	}
	#define _simd_u16x4_ceil_enable() _simd_u16x32_ceil_enable()
#elif defined(_simd_u16x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_ceil(const register _simd_u16x4 x) {
		union { _simd_u16x4 v1; _simd_u16x64 v2; };
		v1 = x;
		v2 = _simd_u16x64_ceil_(v2);
		return v1;
	}
	#define _simd_u16x4_ceil_enable() _simd_u16x64_ceil_enable()
#else
	#define _simd_u16x4_ceil(X) _simd_u16x4_combine(\
		_simd_u16x2_ceil(_simd_u16x4_splitlo(X)),\
		_simd_u16x2_ceil(_simd_u16x4_splithi(X)))
	#define _simd_u16x4_ceil_enable() (_simd_u16x2_ceil_enable() && _simd_u16x4_combine_enable() && _simd_u16x4_splitlo_enable()  && _simd_u16x4_splithi_enable())
#endif

#ifndef _simd_u16x1_ceil_safe
	#define _simd_u16x1_ceil_safe(X) X
	#define _simd_u16x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_u16x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_u16x1_ceil_enabled() true
#endif

#define _simd_u16x8_ceil_safe(X)_simd_u16x8_combine_safe(\
	_simd_u16x4_ceil_safe(_simd_u16x8_splitlo_safe(X)),\
	_simd_u16x4_ceil_safe(_simd_u16x8_splithi_safe(X)))
#ifdef _simd_u16x8_ceil_
	#define _simd_u16x8_ceil(X) _simd_u16x8_ceil_(X)
	#define _simd_u16x8_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_ceil_instruction_set>()
#elif defined(_simd_u16x16_ceil_)
	static ANVIL_STRONG_INLINE _simd_u16x8 ANVIL_SIMD_CALL _simd_u16x8_ceil(const register _simd_u16x8 x) {
		union { _simd_u16x8 v1; _simd_u16x16 v2; };
		v1 = x;
		v2 = _simd_u16x16_ceil_(v2);
		return v1;
	}
	#define _simd_u16x8_ceil_enable() _simd_u16x16_ceil_enable()
#elif defined(_simd_u16x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_u16x8 ANVIL_SIMD_CALL _simd_u16x8_ceil(const register _simd_u16x8 x) {
		union { _simd_u16x8 v1; _simd_u16x32 v2; };
		v1 = x;
		v2 = _simd_u16x32_ceil_(v2);
		return v1;
	}
	#define _simd_u16x8_ceil_enable() _simd_u16x32_ceil_enable()
#elif defined(_simd_u16x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_u16x8 ANVIL_SIMD_CALL _simd_u16x8_ceil(const register _simd_u16x8 x) {
		union { _simd_u16x8 v1; _simd_u16x64 v2; };
		v1 = x;
		v2 = _simd_u16x64_ceil_(v2);
		return v1;
	}
	#define _simd_u16x8_ceil_enable() _simd_u16x64_ceil_enable()
#else
	#define _simd_u16x8_ceil(X) _simd_u16x8_combine(\
		_simd_u16x4_ceil(_simd_u16x8_splitlo(X)),\
		_simd_u16x4_ceil(_simd_u16x8_splithi(X)))
	#define _simd_u16x8_ceil_enable() (_simd_u16x4_ceil_enable() && _simd_u16x8_combine_enable() && _simd_u16x8_splitlo_enable()  && _simd_u16x8_splithi_enable())
#endif

#ifndef _simd_u16x1_ceil_safe
	#define _simd_u16x1_ceil_safe(X) X
	#define _simd_u16x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_u16x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_u16x1_ceil_enabled() true
#endif

#define _simd_u16x16_ceil_safe(X)_simd_u16x16_combine_safe(\
	_simd_u16x8_ceil_safe(_simd_u16x16_splitlo_safe(X)),\
	_simd_u16x8_ceil_safe(_simd_u16x16_splithi_safe(X)))
#ifdef _simd_u16x16_ceil_
	#define _simd_u16x16_ceil(X) _simd_u16x16_ceil_(X)
	#define _simd_u16x16_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_ceil_instruction_set>()
#elif defined(_simd_u16x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_u16x16 ANVIL_SIMD_CALL _simd_u16x16_ceil(const register _simd_u16x16 x) {
		union { _simd_u16x16 v1; _simd_u16x32 v2; };
		v1 = x;
		v2 = _simd_u16x32_ceil_(v2);
		return v1;
	}
	#define _simd_u16x16_ceil_enable() _simd_u16x32_ceil_enable()
#elif defined(_simd_u16x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_u16x16 ANVIL_SIMD_CALL _simd_u16x16_ceil(const register _simd_u16x16 x) {
		union { _simd_u16x16 v1; _simd_u16x64 v2; };
		v1 = x;
		v2 = _simd_u16x64_ceil_(v2);
		return v1;
	}
	#define _simd_u16x16_ceil_enable() _simd_u16x64_ceil_enable()
#else
	#define _simd_u16x16_ceil(X) _simd_u16x16_combine(\
		_simd_u16x8_ceil(_simd_u16x16_splitlo(X)),\
		_simd_u16x8_ceil(_simd_u16x16_splithi(X)))
	#define _simd_u16x16_ceil_enable() (_simd_u16x8_ceil_enable() && _simd_u16x16_combine_enable() && _simd_u16x16_splitlo_enable()  && _simd_u16x16_splithi_enable())
#endif

#ifndef _simd_u16x1_ceil_safe
	#define _simd_u16x1_ceil_safe(X) X
	#define _simd_u16x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_u16x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_u16x1_ceil_enabled() true
#endif

#define _simd_u16x32_ceil_safe(X)_simd_u16x32_combine_safe(\
	_simd_u16x16_ceil_safe(_simd_u16x32_splitlo_safe(X)),\
	_simd_u16x16_ceil_safe(_simd_u16x32_splithi_safe(X)))
#ifdef _simd_u16x32_ceil_
	#define _simd_u16x32_ceil(X) _simd_u16x32_ceil_(X)
	#define _simd_u16x32_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_ceil_instruction_set>()
#elif defined(_simd_u16x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_u16x32 ANVIL_SIMD_CALL _simd_u16x32_ceil(const register _simd_u16x32 x) {
		union { _simd_u16x32 v1; _simd_u16x64 v2; };
		v1 = x;
		v2 = _simd_u16x64_ceil_(v2);
		return v1;
	}
	#define _simd_u16x32_ceil_enable() _simd_u16x64_ceil_enable()
#else
	#define _simd_u16x32_ceil(X) _simd_u16x32_combine(\
		_simd_u16x16_ceil(_simd_u16x32_splitlo(X)),\
		_simd_u16x16_ceil(_simd_u16x32_splithi(X)))
	#define _simd_u16x32_ceil_enable() (_simd_u16x16_ceil_enable() && _simd_u16x32_combine_enable() && _simd_u16x32_splitlo_enable()  && _simd_u16x32_splithi_enable())
#endif

#ifndef _simd_u16x1_ceil_safe
	#define _simd_u16x1_ceil_safe(X) X
	#define _simd_u16x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_u16x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_u16x1_ceil_enabled() true
#endif

#define _simd_u16x64_ceil_safe(X)_simd_u16x64_combine_safe(\
	_simd_u16x32_ceil_safe(_simd_u16x64_splitlo_safe(X)),\
	_simd_u16x32_ceil_safe(_simd_u16x64_splithi_safe(X)))
#ifdef _simd_u16x64_ceil_
	#define _simd_u16x64_ceil(X) _simd_u16x64_ceil_(X)
	#define _simd_u16x64_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_ceil_instruction_set>()
#else
	#define _simd_u16x64_ceil(X) _simd_u16x64_combine(\
		_simd_u16x32_ceil(_simd_u16x64_splitlo(X)),\
		_simd_u16x32_ceil(_simd_u16x64_splithi(X)))
	#define _simd_u16x64_ceil_enable() (_simd_u16x32_ceil_enable() && _simd_u16x64_combine_enable() && _simd_u16x64_splitlo_enable()  && _simd_u16x64_splithi_enable())
#endif

#ifndef _simd_s8x1_ceil_safe
	#define _simd_s8x1_ceil_safe(X) X
	#define _simd_s8x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_s8x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_s8x1_ceil_enabled() true
#endif

#define _simd_s8x2_ceil_safe(X)_simd_s8x2_combine_safe(\
	_simd_s8x1_ceil_safe(_simd_s8x2_splitlo_safe(X)),\
	_simd_s8x1_ceil_safe(_simd_s8x2_splithi_safe(X)))
#ifdef _simd_s8x2_ceil_
	#define _simd_s8x2_ceil(X) _simd_s8x2_ceil_(X)
	#define _simd_s8x2_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_ceil_instruction_set>()
#elif defined(_simd_s8x4_ceil_)
	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_ceil(const register _simd_s8x2 x) {
		union { _simd_s8x2 v1; _simd_s8x4 v2; };
		v1 = x;
		v2 = _simd_s8x4_ceil_(v2);
		return v1;
	}
	#define _simd_s8x2_ceil_enable() _simd_s8x4_ceil_enable()
#elif defined(_simd_s8x8_ceil_)
	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_ceil(const register _simd_s8x2 x) {
		union { _simd_s8x2 v1; _simd_s8x8 v2; };
		v1 = x;
		v2 = _simd_s8x8_ceil_(v2);
		return v1;
	}
	#define _simd_s8x2_ceil_enable() _simd_s8x8_ceil_enable()
#elif defined(_simd_s8x16_ceil_)
	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_ceil(const register _simd_s8x2 x) {
		union { _simd_s8x2 v1; _simd_s8x16 v2; };
		v1 = x;
		v2 = _simd_s8x16_ceil_(v2);
		return v1;
	}
	#define _simd_s8x2_ceil_enable() _simd_s8x16_ceil_enable()
#elif defined(_simd_s8x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_ceil(const register _simd_s8x2 x) {
		union { _simd_s8x2 v1; _simd_s8x32 v2; };
		v1 = x;
		v2 = _simd_s8x32_ceil_(v2);
		return v1;
	}
	#define _simd_s8x2_ceil_enable() _simd_s8x32_ceil_enable()
#elif defined(_simd_s8x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_ceil(const register _simd_s8x2 x) {
		union { _simd_s8x2 v1; _simd_s8x64 v2; };
		v1 = x;
		v2 = _simd_s8x64_ceil_(v2);
		return v1;
	}
	#define _simd_s8x2_ceil_enable() _simd_s8x64_ceil_enable()
#else
	#define _simd_s8x2_ceil(X) _simd_s8x2_combine(\
		_simd_s8x1_ceil(_simd_s8x2_splitlo(X)),\
		_simd_s8x1_ceil(_simd_s8x2_splithi(X)))
	#define _simd_s8x2_ceil_enable() (_simd_s8x1_ceil_enable() && _simd_s8x2_combine_enable() && _simd_s8x2_splitlo_enable()  && _simd_s8x2_splithi_enable())
#endif

#ifndef _simd_s8x1_ceil_safe
	#define _simd_s8x1_ceil_safe(X) X
	#define _simd_s8x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_s8x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_s8x1_ceil_enabled() true
#endif

#define _simd_s8x4_ceil_safe(X)_simd_s8x4_combine_safe(\
	_simd_s8x2_ceil_safe(_simd_s8x4_splitlo_safe(X)),\
	_simd_s8x2_ceil_safe(_simd_s8x4_splithi_safe(X)))
#ifdef _simd_s8x4_ceil_
	#define _simd_s8x4_ceil(X) _simd_s8x4_ceil_(X)
	#define _simd_s8x4_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_ceil_instruction_set>()
#elif defined(_simd_s8x8_ceil_)
	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_ceil(const register _simd_s8x4 x) {
		union { _simd_s8x4 v1; _simd_s8x8 v2; };
		v1 = x;
		v2 = _simd_s8x8_ceil_(v2);
		return v1;
	}
	#define _simd_s8x4_ceil_enable() _simd_s8x8_ceil_enable()
#elif defined(_simd_s8x16_ceil_)
	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_ceil(const register _simd_s8x4 x) {
		union { _simd_s8x4 v1; _simd_s8x16 v2; };
		v1 = x;
		v2 = _simd_s8x16_ceil_(v2);
		return v1;
	}
	#define _simd_s8x4_ceil_enable() _simd_s8x16_ceil_enable()
#elif defined(_simd_s8x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_ceil(const register _simd_s8x4 x) {
		union { _simd_s8x4 v1; _simd_s8x32 v2; };
		v1 = x;
		v2 = _simd_s8x32_ceil_(v2);
		return v1;
	}
	#define _simd_s8x4_ceil_enable() _simd_s8x32_ceil_enable()
#elif defined(_simd_s8x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_ceil(const register _simd_s8x4 x) {
		union { _simd_s8x4 v1; _simd_s8x64 v2; };
		v1 = x;
		v2 = _simd_s8x64_ceil_(v2);
		return v1;
	}
	#define _simd_s8x4_ceil_enable() _simd_s8x64_ceil_enable()
#else
	#define _simd_s8x4_ceil(X) _simd_s8x4_combine(\
		_simd_s8x2_ceil(_simd_s8x4_splitlo(X)),\
		_simd_s8x2_ceil(_simd_s8x4_splithi(X)))
	#define _simd_s8x4_ceil_enable() (_simd_s8x2_ceil_enable() && _simd_s8x4_combine_enable() && _simd_s8x4_splitlo_enable()  && _simd_s8x4_splithi_enable())
#endif

#ifndef _simd_s8x1_ceil_safe
	#define _simd_s8x1_ceil_safe(X) X
	#define _simd_s8x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_s8x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_s8x1_ceil_enabled() true
#endif

#define _simd_s8x8_ceil_safe(X)_simd_s8x8_combine_safe(\
	_simd_s8x4_ceil_safe(_simd_s8x8_splitlo_safe(X)),\
	_simd_s8x4_ceil_safe(_simd_s8x8_splithi_safe(X)))
#ifdef _simd_s8x8_ceil_
	#define _simd_s8x8_ceil(X) _simd_s8x8_ceil_(X)
	#define _simd_s8x8_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_ceil_instruction_set>()
#elif defined(_simd_s8x16_ceil_)
	static ANVIL_STRONG_INLINE _simd_s8x8 ANVIL_SIMD_CALL _simd_s8x8_ceil(const register _simd_s8x8 x) {
		union { _simd_s8x8 v1; _simd_s8x16 v2; };
		v1 = x;
		v2 = _simd_s8x16_ceil_(v2);
		return v1;
	}
	#define _simd_s8x8_ceil_enable() _simd_s8x16_ceil_enable()
#elif defined(_simd_s8x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_s8x8 ANVIL_SIMD_CALL _simd_s8x8_ceil(const register _simd_s8x8 x) {
		union { _simd_s8x8 v1; _simd_s8x32 v2; };
		v1 = x;
		v2 = _simd_s8x32_ceil_(v2);
		return v1;
	}
	#define _simd_s8x8_ceil_enable() _simd_s8x32_ceil_enable()
#elif defined(_simd_s8x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_s8x8 ANVIL_SIMD_CALL _simd_s8x8_ceil(const register _simd_s8x8 x) {
		union { _simd_s8x8 v1; _simd_s8x64 v2; };
		v1 = x;
		v2 = _simd_s8x64_ceil_(v2);
		return v1;
	}
	#define _simd_s8x8_ceil_enable() _simd_s8x64_ceil_enable()
#else
	#define _simd_s8x8_ceil(X) _simd_s8x8_combine(\
		_simd_s8x4_ceil(_simd_s8x8_splitlo(X)),\
		_simd_s8x4_ceil(_simd_s8x8_splithi(X)))
	#define _simd_s8x8_ceil_enable() (_simd_s8x4_ceil_enable() && _simd_s8x8_combine_enable() && _simd_s8x8_splitlo_enable()  && _simd_s8x8_splithi_enable())
#endif

#ifndef _simd_s8x1_ceil_safe
	#define _simd_s8x1_ceil_safe(X) X
	#define _simd_s8x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_s8x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_s8x1_ceil_enabled() true
#endif

#define _simd_s8x16_ceil_safe(X)_simd_s8x16_combine_safe(\
	_simd_s8x8_ceil_safe(_simd_s8x16_splitlo_safe(X)),\
	_simd_s8x8_ceil_safe(_simd_s8x16_splithi_safe(X)))
#ifdef _simd_s8x16_ceil_
	#define _simd_s8x16_ceil(X) _simd_s8x16_ceil_(X)
	#define _simd_s8x16_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_ceil_instruction_set>()
#elif defined(_simd_s8x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_s8x16 ANVIL_SIMD_CALL _simd_s8x16_ceil(const register _simd_s8x16 x) {
		union { _simd_s8x16 v1; _simd_s8x32 v2; };
		v1 = x;
		v2 = _simd_s8x32_ceil_(v2);
		return v1;
	}
	#define _simd_s8x16_ceil_enable() _simd_s8x32_ceil_enable()
#elif defined(_simd_s8x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_s8x16 ANVIL_SIMD_CALL _simd_s8x16_ceil(const register _simd_s8x16 x) {
		union { _simd_s8x16 v1; _simd_s8x64 v2; };
		v1 = x;
		v2 = _simd_s8x64_ceil_(v2);
		return v1;
	}
	#define _simd_s8x16_ceil_enable() _simd_s8x64_ceil_enable()
#else
	#define _simd_s8x16_ceil(X) _simd_s8x16_combine(\
		_simd_s8x8_ceil(_simd_s8x16_splitlo(X)),\
		_simd_s8x8_ceil(_simd_s8x16_splithi(X)))
	#define _simd_s8x16_ceil_enable() (_simd_s8x8_ceil_enable() && _simd_s8x16_combine_enable() && _simd_s8x16_splitlo_enable()  && _simd_s8x16_splithi_enable())
#endif

#ifndef _simd_s8x1_ceil_safe
	#define _simd_s8x1_ceil_safe(X) X
	#define _simd_s8x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_s8x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_s8x1_ceil_enabled() true
#endif

#define _simd_s8x32_ceil_safe(X)_simd_s8x32_combine_safe(\
	_simd_s8x16_ceil_safe(_simd_s8x32_splitlo_safe(X)),\
	_simd_s8x16_ceil_safe(_simd_s8x32_splithi_safe(X)))
#ifdef _simd_s8x32_ceil_
	#define _simd_s8x32_ceil(X) _simd_s8x32_ceil_(X)
	#define _simd_s8x32_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_ceil_instruction_set>()
#elif defined(_simd_s8x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_s8x32 ANVIL_SIMD_CALL _simd_s8x32_ceil(const register _simd_s8x32 x) {
		union { _simd_s8x32 v1; _simd_s8x64 v2; };
		v1 = x;
		v2 = _simd_s8x64_ceil_(v2);
		return v1;
	}
	#define _simd_s8x32_ceil_enable() _simd_s8x64_ceil_enable()
#else
	#define _simd_s8x32_ceil(X) _simd_s8x32_combine(\
		_simd_s8x16_ceil(_simd_s8x32_splitlo(X)),\
		_simd_s8x16_ceil(_simd_s8x32_splithi(X)))
	#define _simd_s8x32_ceil_enable() (_simd_s8x16_ceil_enable() && _simd_s8x32_combine_enable() && _simd_s8x32_splitlo_enable()  && _simd_s8x32_splithi_enable())
#endif

#ifndef _simd_s8x1_ceil_safe
	#define _simd_s8x1_ceil_safe(X) X
	#define _simd_s8x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_s8x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_s8x1_ceil_enabled() true
#endif

#define _simd_s8x64_ceil_safe(X)_simd_s8x64_combine_safe(\
	_simd_s8x32_ceil_safe(_simd_s8x64_splitlo_safe(X)),\
	_simd_s8x32_ceil_safe(_simd_s8x64_splithi_safe(X)))
#ifdef _simd_s8x64_ceil_
	#define _simd_s8x64_ceil(X) _simd_s8x64_ceil_(X)
	#define _simd_s8x64_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_ceil_instruction_set>()
#else
	#define _simd_s8x64_ceil(X) _simd_s8x64_combine(\
		_simd_s8x32_ceil(_simd_s8x64_splitlo(X)),\
		_simd_s8x32_ceil(_simd_s8x64_splithi(X)))
	#define _simd_s8x64_ceil_enable() (_simd_s8x32_ceil_enable() && _simd_s8x64_combine_enable() && _simd_s8x64_splitlo_enable()  && _simd_s8x64_splithi_enable())
#endif

#ifndef _simd_u8x1_ceil_safe
	#define _simd_u8x1_ceil_safe(X) X
	#define _simd_u8x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_u8x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_u8x1_ceil_enabled() true
#endif

#define _simd_u8x2_ceil_safe(X)_simd_u8x2_combine_safe(\
	_simd_u8x1_ceil_safe(_simd_u8x2_splitlo_safe(X)),\
	_simd_u8x1_ceil_safe(_simd_u8x2_splithi_safe(X)))
#ifdef _simd_u8x2_ceil_
	#define _simd_u8x2_ceil(X) _simd_u8x2_ceil_(X)
	#define _simd_u8x2_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_ceil_instruction_set>()
#elif defined(_simd_u8x4_ceil_)
	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_ceil(const register _simd_u8x2 x) {
		union { _simd_u8x2 v1; _simd_u8x4 v2; };
		v1 = x;
		v2 = _simd_u8x4_ceil_(v2);
		return v1;
	}
	#define _simd_u8x2_ceil_enable() _simd_u8x4_ceil_enable()
#elif defined(_simd_u8x8_ceil_)
	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_ceil(const register _simd_u8x2 x) {
		union { _simd_u8x2 v1; _simd_u8x8 v2; };
		v1 = x;
		v2 = _simd_u8x8_ceil_(v2);
		return v1;
	}
	#define _simd_u8x2_ceil_enable() _simd_u8x8_ceil_enable()
#elif defined(_simd_u8x16_ceil_)
	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_ceil(const register _simd_u8x2 x) {
		union { _simd_u8x2 v1; _simd_u8x16 v2; };
		v1 = x;
		v2 = _simd_u8x16_ceil_(v2);
		return v1;
	}
	#define _simd_u8x2_ceil_enable() _simd_u8x16_ceil_enable()
#elif defined(_simd_u8x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_ceil(const register _simd_u8x2 x) {
		union { _simd_u8x2 v1; _simd_u8x32 v2; };
		v1 = x;
		v2 = _simd_u8x32_ceil_(v2);
		return v1;
	}
	#define _simd_u8x2_ceil_enable() _simd_u8x32_ceil_enable()
#elif defined(_simd_u8x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_ceil(const register _simd_u8x2 x) {
		union { _simd_u8x2 v1; _simd_u8x64 v2; };
		v1 = x;
		v2 = _simd_u8x64_ceil_(v2);
		return v1;
	}
	#define _simd_u8x2_ceil_enable() _simd_u8x64_ceil_enable()
#else
	#define _simd_u8x2_ceil(X) _simd_u8x2_combine(\
		_simd_u8x1_ceil(_simd_u8x2_splitlo(X)),\
		_simd_u8x1_ceil(_simd_u8x2_splithi(X)))
	#define _simd_u8x2_ceil_enable() (_simd_u8x1_ceil_enable() && _simd_u8x2_combine_enable() && _simd_u8x2_splitlo_enable()  && _simd_u8x2_splithi_enable())
#endif

#ifndef _simd_u8x1_ceil_safe
	#define _simd_u8x1_ceil_safe(X) X
	#define _simd_u8x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_u8x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_u8x1_ceil_enabled() true
#endif

#define _simd_u8x4_ceil_safe(X)_simd_u8x4_combine_safe(\
	_simd_u8x2_ceil_safe(_simd_u8x4_splitlo_safe(X)),\
	_simd_u8x2_ceil_safe(_simd_u8x4_splithi_safe(X)))
#ifdef _simd_u8x4_ceil_
	#define _simd_u8x4_ceil(X) _simd_u8x4_ceil_(X)
	#define _simd_u8x4_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_ceil_instruction_set>()
#elif defined(_simd_u8x8_ceil_)
	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_ceil(const register _simd_u8x4 x) {
		union { _simd_u8x4 v1; _simd_u8x8 v2; };
		v1 = x;
		v2 = _simd_u8x8_ceil_(v2);
		return v1;
	}
	#define _simd_u8x4_ceil_enable() _simd_u8x8_ceil_enable()
#elif defined(_simd_u8x16_ceil_)
	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_ceil(const register _simd_u8x4 x) {
		union { _simd_u8x4 v1; _simd_u8x16 v2; };
		v1 = x;
		v2 = _simd_u8x16_ceil_(v2);
		return v1;
	}
	#define _simd_u8x4_ceil_enable() _simd_u8x16_ceil_enable()
#elif defined(_simd_u8x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_ceil(const register _simd_u8x4 x) {
		union { _simd_u8x4 v1; _simd_u8x32 v2; };
		v1 = x;
		v2 = _simd_u8x32_ceil_(v2);
		return v1;
	}
	#define _simd_u8x4_ceil_enable() _simd_u8x32_ceil_enable()
#elif defined(_simd_u8x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_ceil(const register _simd_u8x4 x) {
		union { _simd_u8x4 v1; _simd_u8x64 v2; };
		v1 = x;
		v2 = _simd_u8x64_ceil_(v2);
		return v1;
	}
	#define _simd_u8x4_ceil_enable() _simd_u8x64_ceil_enable()
#else
	#define _simd_u8x4_ceil(X) _simd_u8x4_combine(\
		_simd_u8x2_ceil(_simd_u8x4_splitlo(X)),\
		_simd_u8x2_ceil(_simd_u8x4_splithi(X)))
	#define _simd_u8x4_ceil_enable() (_simd_u8x2_ceil_enable() && _simd_u8x4_combine_enable() && _simd_u8x4_splitlo_enable()  && _simd_u8x4_splithi_enable())
#endif

#ifndef _simd_u8x1_ceil_safe
	#define _simd_u8x1_ceil_safe(X) X
	#define _simd_u8x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_u8x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_u8x1_ceil_enabled() true
#endif

#define _simd_u8x8_ceil_safe(X)_simd_u8x8_combine_safe(\
	_simd_u8x4_ceil_safe(_simd_u8x8_splitlo_safe(X)),\
	_simd_u8x4_ceil_safe(_simd_u8x8_splithi_safe(X)))
#ifdef _simd_u8x8_ceil_
	#define _simd_u8x8_ceil(X) _simd_u8x8_ceil_(X)
	#define _simd_u8x8_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_ceil_instruction_set>()
#elif defined(_simd_u8x16_ceil_)
	static ANVIL_STRONG_INLINE _simd_u8x8 ANVIL_SIMD_CALL _simd_u8x8_ceil(const register _simd_u8x8 x) {
		union { _simd_u8x8 v1; _simd_u8x16 v2; };
		v1 = x;
		v2 = _simd_u8x16_ceil_(v2);
		return v1;
	}
	#define _simd_u8x8_ceil_enable() _simd_u8x16_ceil_enable()
#elif defined(_simd_u8x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_u8x8 ANVIL_SIMD_CALL _simd_u8x8_ceil(const register _simd_u8x8 x) {
		union { _simd_u8x8 v1; _simd_u8x32 v2; };
		v1 = x;
		v2 = _simd_u8x32_ceil_(v2);
		return v1;
	}
	#define _simd_u8x8_ceil_enable() _simd_u8x32_ceil_enable()
#elif defined(_simd_u8x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_u8x8 ANVIL_SIMD_CALL _simd_u8x8_ceil(const register _simd_u8x8 x) {
		union { _simd_u8x8 v1; _simd_u8x64 v2; };
		v1 = x;
		v2 = _simd_u8x64_ceil_(v2);
		return v1;
	}
	#define _simd_u8x8_ceil_enable() _simd_u8x64_ceil_enable()
#else
	#define _simd_u8x8_ceil(X) _simd_u8x8_combine(\
		_simd_u8x4_ceil(_simd_u8x8_splitlo(X)),\
		_simd_u8x4_ceil(_simd_u8x8_splithi(X)))
	#define _simd_u8x8_ceil_enable() (_simd_u8x4_ceil_enable() && _simd_u8x8_combine_enable() && _simd_u8x8_splitlo_enable()  && _simd_u8x8_splithi_enable())
#endif

#ifndef _simd_u8x1_ceil_safe
	#define _simd_u8x1_ceil_safe(X) X
	#define _simd_u8x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_u8x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_u8x1_ceil_enabled() true
#endif

#define _simd_u8x16_ceil_safe(X)_simd_u8x16_combine_safe(\
	_simd_u8x8_ceil_safe(_simd_u8x16_splitlo_safe(X)),\
	_simd_u8x8_ceil_safe(_simd_u8x16_splithi_safe(X)))
#ifdef _simd_u8x16_ceil_
	#define _simd_u8x16_ceil(X) _simd_u8x16_ceil_(X)
	#define _simd_u8x16_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_ceil_instruction_set>()
#elif defined(_simd_u8x32_ceil_)
	static ANVIL_STRONG_INLINE _simd_u8x16 ANVIL_SIMD_CALL _simd_u8x16_ceil(const register _simd_u8x16 x) {
		union { _simd_u8x16 v1; _simd_u8x32 v2; };
		v1 = x;
		v2 = _simd_u8x32_ceil_(v2);
		return v1;
	}
	#define _simd_u8x16_ceil_enable() _simd_u8x32_ceil_enable()
#elif defined(_simd_u8x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_u8x16 ANVIL_SIMD_CALL _simd_u8x16_ceil(const register _simd_u8x16 x) {
		union { _simd_u8x16 v1; _simd_u8x64 v2; };
		v1 = x;
		v2 = _simd_u8x64_ceil_(v2);
		return v1;
	}
	#define _simd_u8x16_ceil_enable() _simd_u8x64_ceil_enable()
#else
	#define _simd_u8x16_ceil(X) _simd_u8x16_combine(\
		_simd_u8x8_ceil(_simd_u8x16_splitlo(X)),\
		_simd_u8x8_ceil(_simd_u8x16_splithi(X)))
	#define _simd_u8x16_ceil_enable() (_simd_u8x8_ceil_enable() && _simd_u8x16_combine_enable() && _simd_u8x16_splitlo_enable()  && _simd_u8x16_splithi_enable())
#endif

#ifndef _simd_u8x1_ceil_safe
	#define _simd_u8x1_ceil_safe(X) X
	#define _simd_u8x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_u8x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_u8x1_ceil_enabled() true
#endif

#define _simd_u8x32_ceil_safe(X)_simd_u8x32_combine_safe(\
	_simd_u8x16_ceil_safe(_simd_u8x32_splitlo_safe(X)),\
	_simd_u8x16_ceil_safe(_simd_u8x32_splithi_safe(X)))
#ifdef _simd_u8x32_ceil_
	#define _simd_u8x32_ceil(X) _simd_u8x32_ceil_(X)
	#define _simd_u8x32_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_ceil_instruction_set>()
#elif defined(_simd_u8x64_ceil_)
	static ANVIL_STRONG_INLINE _simd_u8x32 ANVIL_SIMD_CALL _simd_u8x32_ceil(const register _simd_u8x32 x) {
		union { _simd_u8x32 v1; _simd_u8x64 v2; };
		v1 = x;
		v2 = _simd_u8x64_ceil_(v2);
		return v1;
	}
	#define _simd_u8x32_ceil_enable() _simd_u8x64_ceil_enable()
#else
	#define _simd_u8x32_ceil(X) _simd_u8x32_combine(\
		_simd_u8x16_ceil(_simd_u8x32_splitlo(X)),\
		_simd_u8x16_ceil(_simd_u8x32_splithi(X)))
	#define _simd_u8x32_ceil_enable() (_simd_u8x16_ceil_enable() && _simd_u8x32_combine_enable() && _simd_u8x32_splitlo_enable()  && _simd_u8x32_splithi_enable())
#endif

#ifndef _simd_u8x1_ceil_safe
	#define _simd_u8x1_ceil_safe(X) X
	#define _simd_u8x1_ceil_(X) x1_ceil_safe(X)
	#define _simd_u8x1_ceil_instruction_set() anvil::simd::IS_NONE
	#define _simd_u8x1_ceil_enabled() true
#endif

#define _simd_u8x64_ceil_safe(X)_simd_u8x64_combine_safe(\
	_simd_u8x32_ceil_safe(_simd_u8x64_splitlo_safe(X)),\
	_simd_u8x32_ceil_safe(_simd_u8x64_splithi_safe(X)))
#ifdef _simd_u8x64_ceil_
	#define _simd_u8x64_ceil(X) _simd_u8x64_ceil_(X)
	#define _simd_u8x64_ceil_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_ceil_instruction_set>()
#else
	#define _simd_u8x64_ceil(X) _simd_u8x64_combine(\
		_simd_u8x32_ceil(_simd_u8x64_splitlo(X)),\
		_simd_u8x32_ceil(_simd_u8x64_splithi(X)))
	#define _simd_u8x64_ceil_enable() (_simd_u8x32_ceil_enable() && _simd_u8x64_combine_enable() && _simd_u8x64_splitlo_enable()  && _simd_u8x64_splithi_enable())
#endif

