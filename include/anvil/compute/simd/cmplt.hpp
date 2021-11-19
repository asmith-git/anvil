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

#ifndef ANVIL_COMPUTE_SIMD_CMPLT_HPP
#define ANVIL_COMPUTE_SIMD_CMPLT_HPP

#include "anvil/compute/simd/Add.hpp"

namespace anvil {
	namespace detail {
		template<class T>
		using VectorCmpLt = VectorArith<ANVIL_VECTOR_ARITH_CMPLT, T>;
	}
}

namespace anvil {

	template<uint64_t instruction_set = ASM_MINIMUM, class T>
	static inline T VectorCmpLt(const T& a, const T& b) throw() {
		return detail::VectorCmpLt<T>::Execute<instruction_set>(a, b);
	}

	template<uint64_t instruction_set = ASM_MINIMUM, class T>
	static inline T VectorCmpLt(const T& a, const T& b, const T& src, const uint64_t mask) throw() {
		return detail::VectorCmpLt<T>::ExecuteRuntimeMask<instruction_set>(a, b, src, mask);
	}

	template<uint64_t instruction_set = ASM_MINIMUM, class T>
	static inline T VectorCmpLt(const T& a, const T& b, const T& src, const Bitfield128 mask) throw() {
		return detail::VectorCmpLt<T>::ExecuteRuntimeMask<instruction_set>(a, b, src, mask);
	}

	template<uint64_t instruction_set = ASM_MINIMUM, class T>
	static inline T VectorCmpLt(const T& a, const T& b, const T& src, const Bitfield256 mask) throw() {
		return detail::VectorCmpLt<T>::ExecuteRuntimeMask<instruction_set>(a, b, src, mask);
	}

	template<uint64_t mask, uint64_t instruction_set = ASM_MINIMUM, class T>
	static inline T VectorCmpLt(const T& a, const T& b, const T& src) throw() {
		return detail::VectorCmpLts<T>::ExecuteCompiletimeMask<mask, instruction_set>(a, b, src);
	}
}

#endif

//// -- f64 --
//
//#ifndef _simd_f64x1_cmplt_safe
//	#define _simd_f64x1_cmplt_safe(X,Y) static_cast<_simd_f64x1>(X < Y)
//	#define _simd_f64x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_f64x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_cmplt_enabled() true
//#endif
//
//#define _simd_f64x2_cmplt_safe(X,Y)_simd_f64x2_combine_safe(\
//	_simd_f64x1_cmplt_safe(_simd_f64x2_splitlo_safe(X), _simd_ f64x2_splitlo_safe(Y)),\
//	_simd_f64x1_cmplt_safe(_simd_f64x2_splithi_safe(X), _simd_ f64x2_splithi_safe(Y)))
//#ifdef _simd_f64x2_cmplt_
//	#define _simd_f64x2_cmplt(X,Y) _simd_f64x2_cmplt_(X, Y)
//	#define _simd_f64x2_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_cmplt_instruction_set>()
//#elif defined(_simd_f64x4_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_cmplt(const register _simd_f64x2 x, const register _simd_f64x2 y) {
//		union SIMDUnion { _simd_f64x2 v1; _simd_f64x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x4_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x2_cmplt_enable() _simd_f64x4_cmplt_enable()
//#elif defined(_simd_f64x8_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_cmplt(const register _simd_f64x2 x, const register _simd_f64x2 y) {
//		union SIMDUnion { _simd_f64x2 v1; _simd_f64x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x8_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x2_cmplt_enable() _simd_f64x8_cmplt_enable()
//#elif defined(_simd_f64x16_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_cmplt(const register _simd_f64x2 x, const register _simd_f64x2 y) {
//		union SIMDUnion { _simd_f64x2 v1; _simd_f64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x16_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x2_cmplt_enable() _simd_f64x16_cmplt_enable()
//#elif defined(_simd_f64x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_cmplt(const register _simd_f64x2 x, const register _simd_f64x2 y) {
//		union SIMDUnion { _simd_f64x2 v1; _simd_f64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x2_cmplt_enable() _simd_f64x32_cmplt_enable()
//#elif defined(_simd_f64x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_cmplt(const register _simd_f64x2 x, const register _simd_f64x2 y) {
//		union SIMDUnion { _simd_f64x2 v1; _simd_f64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x2_cmplt_enable() _simd_f64x64_cmplt_enable()
//#else
//	#define _simd_f64x2_cmplt(X,Y) _simd_f64x2_combine(\
//		_simd_f64x1_cmplt(_simd_f64x2_splitlo(X), _simd_f64x2_splitlo(Y)),\
//		_simd_f64x1_cmplt(_simd_f64x2_splithi(X), _simd_f64x2_splithi(Y)))
//	#define _simd_f64x2_cmplt_enable() (_simd_f64x1_cmplt_enable() && _simd_f64x2_combine_enable() && _simd_f64x2_splitlo_enable()  && _simd_f64x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x2_cmplt_) && ! defined(_simd_f64x2_cmplt_scalar_)
//	#define _simd_f64x2_cmplt_scalar_(X,Y) _simd_f64x2_cmplt_(X,_simd_f64x2_fill_scalar_(Y))
//	#define _simd_f64x2_cmplt_scalar_instruction_set _simd_f64x2_cmplt_instruction_set
//#endif
//#ifdef _simd_f64x2_cmplt_scalar_
//	#define _simd_f64x2_cmplt_scalar(X,Y) _simd_f64x2_cmplt_scalar_(X,Y)
//	#define _simd_f64x2_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_f64x2_cmplt_scalar(X,Y) _simd_f64x2_cmplt_safe(X,_simd_f64x2_fill_scalar_safe(Y))
//	#define _simd_f64x2_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_f64x1_cmplt_safe
//	#define _simd_f64x1_cmplt_safe(X,Y) static_cast<_simd_f64x1>(X < Y)
//	#define _simd_f64x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_f64x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_cmplt_enabled() true
//#endif
//
//#define _simd_f64x4_cmplt_safe(X,Y)_simd_f64x4_combine_safe(\
//	_simd_f64x2_cmplt_safe(_simd_f64x4_splitlo_safe(X), _simd_ f64x4_splitlo_safe(Y)),\
//	_simd_f64x2_cmplt_safe(_simd_f64x4_splithi_safe(X), _simd_ f64x4_splithi_safe(Y)))
//#ifdef _simd_f64x4_cmplt_
//	#define _simd_f64x4_cmplt(X,Y) _simd_f64x4_cmplt_(X, Y)
//	#define _simd_f64x4_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_cmplt_instruction_set>()
//#elif defined(_simd_f64x8_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_cmplt(const register _simd_f64x4 x, const register _simd_f64x4 y) {
//		union SIMDUnion { _simd_f64x4 v1; _simd_f64x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x8_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x4_cmplt_enable() _simd_f64x8_cmplt_enable()
//#elif defined(_simd_f64x16_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_cmplt(const register _simd_f64x4 x, const register _simd_f64x4 y) {
//		union SIMDUnion { _simd_f64x4 v1; _simd_f64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x16_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x4_cmplt_enable() _simd_f64x16_cmplt_enable()
//#elif defined(_simd_f64x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_cmplt(const register _simd_f64x4 x, const register _simd_f64x4 y) {
//		union SIMDUnion { _simd_f64x4 v1; _simd_f64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x4_cmplt_enable() _simd_f64x32_cmplt_enable()
//#elif defined(_simd_f64x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_cmplt(const register _simd_f64x4 x, const register _simd_f64x4 y) {
//		union SIMDUnion { _simd_f64x4 v1; _simd_f64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x4_cmplt_enable() _simd_f64x64_cmplt_enable()
//#else
//	#define _simd_f64x4_cmplt(X,Y) _simd_f64x4_combine(\
//		_simd_f64x2_cmplt(_simd_f64x4_splitlo(X), _simd_f64x4_splitlo(Y)),\
//		_simd_f64x2_cmplt(_simd_f64x4_splithi(X), _simd_f64x4_splithi(Y)))
//	#define _simd_f64x4_cmplt_enable() (_simd_f64x2_cmplt_enable() && _simd_f64x4_combine_enable() && _simd_f64x4_splitlo_enable()  && _simd_f64x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x4_cmplt_) && ! defined(_simd_f64x4_cmplt_scalar_)
//	#define _simd_f64x4_cmplt_scalar_(X,Y) _simd_f64x4_cmplt_(X,_simd_f64x4_fill_scalar_(Y))
//	#define _simd_f64x4_cmplt_scalar_instruction_set _simd_f64x4_cmplt_instruction_set
//#endif
//#ifdef _simd_f64x4_cmplt_scalar_
//	#define _simd_f64x4_cmplt_scalar(X,Y) _simd_f64x4_cmplt_scalar_(X,Y)
//	#define _simd_f64x4_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_f64x4_cmplt_scalar(X,Y) _simd_f64x4_cmplt_safe(X,_simd_f64x4_fill_scalar_safe(Y))
//	#define _simd_f64x4_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_f64x1_cmplt_safe
//	#define _simd_f64x1_cmplt_safe(X,Y) static_cast<_simd_f64x1>(X < Y)
//	#define _simd_f64x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_f64x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_cmplt_enabled() true
//#endif
//
//#define _simd_f64x8_cmplt_safe(X,Y)_simd_f64x8_combine_safe(\
//	_simd_f64x4_cmplt_safe(_simd_f64x8_splitlo_safe(X), _simd_ f64x8_splitlo_safe(Y)),\
//	_simd_f64x4_cmplt_safe(_simd_f64x8_splithi_safe(X), _simd_ f64x8_splithi_safe(Y)))
//#ifdef _simd_f64x8_cmplt_
//	#define _simd_f64x8_cmplt(X,Y) _simd_f64x8_cmplt_(X, Y)
//	#define _simd_f64x8_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_cmplt_instruction_set>()
//#elif defined(_simd_f64x16_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_f64x8 ANVIL_SIMD_CALL _simd_f64x8_cmplt(const register _simd_f64x8 x, const register _simd_f64x8 y) {
//		union SIMDUnion { _simd_f64x8 v1; _simd_f64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x16_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x8_cmplt_enable() _simd_f64x16_cmplt_enable()
//#elif defined(_simd_f64x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_f64x8 ANVIL_SIMD_CALL _simd_f64x8_cmplt(const register _simd_f64x8 x, const register _simd_f64x8 y) {
//		union SIMDUnion { _simd_f64x8 v1; _simd_f64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x8_cmplt_enable() _simd_f64x32_cmplt_enable()
//#elif defined(_simd_f64x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_f64x8 ANVIL_SIMD_CALL _simd_f64x8_cmplt(const register _simd_f64x8 x, const register _simd_f64x8 y) {
//		union SIMDUnion { _simd_f64x8 v1; _simd_f64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x8_cmplt_enable() _simd_f64x64_cmplt_enable()
//#else
//	#define _simd_f64x8_cmplt(X,Y) _simd_f64x8_combine(\
//		_simd_f64x4_cmplt(_simd_f64x8_splitlo(X), _simd_f64x8_splitlo(Y)),\
//		_simd_f64x4_cmplt(_simd_f64x8_splithi(X), _simd_f64x8_splithi(Y)))
//	#define _simd_f64x8_cmplt_enable() (_simd_f64x4_cmplt_enable() && _simd_f64x8_combine_enable() && _simd_f64x8_splitlo_enable()  && _simd_f64x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x8_cmplt_) && ! defined(_simd_f64x8_cmplt_scalar_)
//	#define _simd_f64x8_cmplt_scalar_(X,Y) _simd_f64x8_cmplt_(X,_simd_f64x8_fill_scalar_(Y))
//	#define _simd_f64x8_cmplt_scalar_instruction_set _simd_f64x8_cmplt_instruction_set
//#endif
//#ifdef _simd_f64x8_cmplt_scalar_
//	#define _simd_f64x8_cmplt_scalar(X,Y) _simd_f64x8_cmplt_scalar_(X,Y)
//	#define _simd_f64x8_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_f64x8_cmplt_scalar(X,Y) _simd_f64x8_cmplt_safe(X,_simd_f64x8_fill_scalar_safe(Y))
//	#define _simd_f64x8_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_f64x1_cmplt_safe
//	#define _simd_f64x1_cmplt_safe(X,Y) static_cast<_simd_f64x1>(X < Y)
//	#define _simd_f64x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_f64x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_cmplt_enabled() true
//#endif
//
//#define _simd_f64x16_cmplt_safe(X,Y)_simd_f64x16_combine_safe(\
//	_simd_f64x8_cmplt_safe(_simd_f64x16_splitlo_safe(X), _simd_ f64x16_splitlo_safe(Y)),\
//	_simd_f64x8_cmplt_safe(_simd_f64x16_splithi_safe(X), _simd_ f64x16_splithi_safe(Y)))
//#ifdef _simd_f64x16_cmplt_
//	#define _simd_f64x16_cmplt(X,Y) _simd_f64x16_cmplt_(X, Y)
//	#define _simd_f64x16_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_cmplt_instruction_set>()
//#elif defined(_simd_f64x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_f64x16 ANVIL_SIMD_CALL _simd_f64x16_cmplt(const register _simd_f64x16 x, const register _simd_f64x16 y) {
//		union SIMDUnion { _simd_f64x16 v1; _simd_f64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x16_cmplt_enable() _simd_f64x32_cmplt_enable()
//#elif defined(_simd_f64x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_f64x16 ANVIL_SIMD_CALL _simd_f64x16_cmplt(const register _simd_f64x16 x, const register _simd_f64x16 y) {
//		union SIMDUnion { _simd_f64x16 v1; _simd_f64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x16_cmplt_enable() _simd_f64x64_cmplt_enable()
//#else
//	#define _simd_f64x16_cmplt(X,Y) _simd_f64x16_combine(\
//		_simd_f64x8_cmplt(_simd_f64x16_splitlo(X), _simd_f64x16_splitlo(Y)),\
//		_simd_f64x8_cmplt(_simd_f64x16_splithi(X), _simd_f64x16_splithi(Y)))
//	#define _simd_f64x16_cmplt_enable() (_simd_f64x8_cmplt_enable() && _simd_f64x16_combine_enable() && _simd_f64x16_splitlo_enable()  && _simd_f64x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x16_cmplt_) && ! defined(_simd_f64x16_cmplt_scalar_)
//	#define _simd_f64x16_cmplt_scalar_(X,Y) _simd_f64x16_cmplt_(X,_simd_f64x16_fill_scalar_(Y))
//	#define _simd_f64x16_cmplt_scalar_instruction_set _simd_f64x16_cmplt_instruction_set
//#endif
//#ifdef _simd_f64x16_cmplt_scalar_
//	#define _simd_f64x16_cmplt_scalar(X,Y) _simd_f64x16_cmplt_scalar_(X,Y)
//	#define _simd_f64x16_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_f64x16_cmplt_scalar(X,Y) _simd_f64x16_cmplt_safe(X,_simd_f64x16_fill_scalar_safe(Y))
//	#define _simd_f64x16_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_f64x1_cmplt_safe
//	#define _simd_f64x1_cmplt_safe(X,Y) static_cast<_simd_f64x1>(X < Y)
//	#define _simd_f64x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_f64x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_cmplt_enabled() true
//#endif
//
//#define _simd_f64x32_cmplt_safe(X,Y)_simd_f64x32_combine_safe(\
//	_simd_f64x16_cmplt_safe(_simd_f64x32_splitlo_safe(X), _simd_ f64x32_splitlo_safe(Y)),\
//	_simd_f64x16_cmplt_safe(_simd_f64x32_splithi_safe(X), _simd_ f64x32_splithi_safe(Y)))
//#ifdef _simd_f64x32_cmplt_
//	#define _simd_f64x32_cmplt(X,Y) _simd_f64x32_cmplt_(X, Y)
//	#define _simd_f64x32_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_cmplt_instruction_set>()
//#elif defined(_simd_f64x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_f64x32 ANVIL_SIMD_CALL _simd_f64x32_cmplt(const register _simd_f64x32 x, const register _simd_f64x32 y) {
//		union SIMDUnion { _simd_f64x32 v1; _simd_f64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x32_cmplt_enable() _simd_f64x64_cmplt_enable()
//#else
//	#define _simd_f64x32_cmplt(X,Y) _simd_f64x32_combine(\
//		_simd_f64x16_cmplt(_simd_f64x32_splitlo(X), _simd_f64x32_splitlo(Y)),\
//		_simd_f64x16_cmplt(_simd_f64x32_splithi(X), _simd_f64x32_splithi(Y)))
//	#define _simd_f64x32_cmplt_enable() (_simd_f64x16_cmplt_enable() && _simd_f64x32_combine_enable() && _simd_f64x32_splitlo_enable()  && _simd_f64x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x32_cmplt_) && ! defined(_simd_f64x32_cmplt_scalar_)
//	#define _simd_f64x32_cmplt_scalar_(X,Y) _simd_f64x32_cmplt_(X,_simd_f64x32_fill_scalar_(Y))
//	#define _simd_f64x32_cmplt_scalar_instruction_set _simd_f64x32_cmplt_instruction_set
//#endif
//#ifdef _simd_f64x32_cmplt_scalar_
//	#define _simd_f64x32_cmplt_scalar(X,Y) _simd_f64x32_cmplt_scalar_(X,Y)
//	#define _simd_f64x32_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_f64x32_cmplt_scalar(X,Y) _simd_f64x32_cmplt_safe(X,_simd_f64x32_fill_scalar_safe(Y))
//	#define _simd_f64x32_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_f64x1_cmplt_safe
//	#define _simd_f64x1_cmplt_safe(X,Y) static_cast<_simd_f64x1>(X < Y)
//	#define _simd_f64x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_f64x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_cmplt_enabled() true
//#endif
//
//#define _simd_f64x64_cmplt_safe(X,Y)_simd_f64x64_combine_safe(\
//	_simd_f64x32_cmplt_safe(_simd_f64x64_splitlo_safe(X), _simd_ f64x64_splitlo_safe(Y)),\
//	_simd_f64x32_cmplt_safe(_simd_f64x64_splithi_safe(X), _simd_ f64x64_splithi_safe(Y)))
//#ifdef _simd_f64x64_cmplt_
//	#define _simd_f64x64_cmplt(X,Y) _simd_f64x64_cmplt_(X, Y)
//	#define _simd_f64x64_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_cmplt_instruction_set>()
//#else
//	#define _simd_f64x64_cmplt(X,Y) _simd_f64x64_combine(\
//		_simd_f64x32_cmplt(_simd_f64x64_splitlo(X), _simd_f64x64_splitlo(Y)),\
//		_simd_f64x32_cmplt(_simd_f64x64_splithi(X), _simd_f64x64_splithi(Y)))
//	#define _simd_f64x64_cmplt_enable() (_simd_f64x32_cmplt_enable() && _simd_f64x64_combine_enable() && _simd_f64x64_splitlo_enable()  && _simd_f64x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x64_cmplt_) && ! defined(_simd_f64x64_cmplt_scalar_)
//	#define _simd_f64x64_cmplt_scalar_(X,Y) _simd_f64x64_cmplt_(X,_simd_f64x64_fill_scalar_(Y))
//	#define _simd_f64x64_cmplt_scalar_instruction_set _simd_f64x64_cmplt_instruction_set
//#endif
//#ifdef _simd_f64x64_cmplt_scalar_
//	#define _simd_f64x64_cmplt_scalar(X,Y) _simd_f64x64_cmplt_scalar_(X,Y)
//	#define _simd_f64x64_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_f64x64_cmplt_scalar(X,Y) _simd_f64x64_cmplt_safe(X,_simd_f64x64_fill_scalar_safe(Y))
//	#define _simd_f64x64_cmplt_scalar_enabled() true
//#endif
//
//// -- f32 --
//
//#ifndef _simd_f32x1_cmplt_safe
//	#define _simd_f32x1_cmplt_safe(X,Y) static_cast<_simd_f32x1>(X < Y)
//	#define _simd_f32x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_f32x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_cmplt_enabled() true
//#endif
//
//#define _simd_f32x2_cmplt_safe(X,Y)_simd_f32x2_combine_safe(\
//	_simd_f32x1_cmplt_safe(_simd_f32x2_splitlo_safe(X), _simd_ f32x2_splitlo_safe(Y)),\
//	_simd_f32x1_cmplt_safe(_simd_f32x2_splithi_safe(X), _simd_ f32x2_splithi_safe(Y)))
//#ifdef _simd_f32x2_cmplt_
//	#define _simd_f32x2_cmplt(X,Y) _simd_f32x2_cmplt_(X, Y)
//	#define _simd_f32x2_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_cmplt_instruction_set>()
//#elif defined(_simd_f32x4_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_cmplt(const register _simd_f32x2 x, const register _simd_f32x2 y) {
//		union SIMDUnion { _simd_f32x2 v1; _simd_f32x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x4_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x2_cmplt_enable() _simd_f32x4_cmplt_enable()
//#elif defined(_simd_f32x8_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_cmplt(const register _simd_f32x2 x, const register _simd_f32x2 y) {
//		union SIMDUnion { _simd_f32x2 v1; _simd_f32x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x8_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x2_cmplt_enable() _simd_f32x8_cmplt_enable()
//#elif defined(_simd_f32x16_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_cmplt(const register _simd_f32x2 x, const register _simd_f32x2 y) {
//		union SIMDUnion { _simd_f32x2 v1; _simd_f32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x16_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x2_cmplt_enable() _simd_f32x16_cmplt_enable()
//#elif defined(_simd_f32x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_cmplt(const register _simd_f32x2 x, const register _simd_f32x2 y) {
//		union SIMDUnion { _simd_f32x2 v1; _simd_f32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x2_cmplt_enable() _simd_f32x32_cmplt_enable()
//#elif defined(_simd_f32x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_cmplt(const register _simd_f32x2 x, const register _simd_f32x2 y) {
//		union SIMDUnion { _simd_f32x2 v1; _simd_f32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x2_cmplt_enable() _simd_f32x64_cmplt_enable()
//#else
//	#define _simd_f32x2_cmplt(X,Y) _simd_f32x2_combine(\
//		_simd_f32x1_cmplt(_simd_f32x2_splitlo(X), _simd_f32x2_splitlo(Y)),\
//		_simd_f32x1_cmplt(_simd_f32x2_splithi(X), _simd_f32x2_splithi(Y)))
//	#define _simd_f32x2_cmplt_enable() (_simd_f32x1_cmplt_enable() && _simd_f32x2_combine_enable() && _simd_f32x2_splitlo_enable()  && _simd_f32x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x2_cmplt_) && ! defined(_simd_f32x2_cmplt_scalar_)
//	#define _simd_f32x2_cmplt_scalar_(X,Y) _simd_f32x2_cmplt_(X,_simd_f32x2_fill_scalar_(Y))
//	#define _simd_f32x2_cmplt_scalar_instruction_set _simd_f32x2_cmplt_instruction_set
//#endif
//#ifdef _simd_f32x2_cmplt_scalar_
//	#define _simd_f32x2_cmplt_scalar(X,Y) _simd_f32x2_cmplt_scalar_(X,Y)
//	#define _simd_f32x2_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_f32x2_cmplt_scalar(X,Y) _simd_f32x2_cmplt_safe(X,_simd_f32x2_fill_scalar_safe(Y))
//	#define _simd_f32x2_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_f32x1_cmplt_safe
//	#define _simd_f32x1_cmplt_safe(X,Y) static_cast<_simd_f32x1>(X < Y)
//	#define _simd_f32x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_f32x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_cmplt_enabled() true
//#endif
//
//#define _simd_f32x4_cmplt_safe(X,Y)_simd_f32x4_combine_safe(\
//	_simd_f32x2_cmplt_safe(_simd_f32x4_splitlo_safe(X), _simd_ f32x4_splitlo_safe(Y)),\
//	_simd_f32x2_cmplt_safe(_simd_f32x4_splithi_safe(X), _simd_ f32x4_splithi_safe(Y)))
//#ifdef _simd_f32x4_cmplt_
//	#define _simd_f32x4_cmplt(X,Y) _simd_f32x4_cmplt_(X, Y)
//	#define _simd_f32x4_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_cmplt_instruction_set>()
//#elif defined(_simd_f32x8_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_cmplt(const register _simd_f32x4 x, const register _simd_f32x4 y) {
//		union SIMDUnion { _simd_f32x4 v1; _simd_f32x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x8_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x4_cmplt_enable() _simd_f32x8_cmplt_enable()
//#elif defined(_simd_f32x16_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_cmplt(const register _simd_f32x4 x, const register _simd_f32x4 y) {
//		union SIMDUnion { _simd_f32x4 v1; _simd_f32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x16_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x4_cmplt_enable() _simd_f32x16_cmplt_enable()
//#elif defined(_simd_f32x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_cmplt(const register _simd_f32x4 x, const register _simd_f32x4 y) {
//		union SIMDUnion { _simd_f32x4 v1; _simd_f32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x4_cmplt_enable() _simd_f32x32_cmplt_enable()
//#elif defined(_simd_f32x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_cmplt(const register _simd_f32x4 x, const register _simd_f32x4 y) {
//		union SIMDUnion { _simd_f32x4 v1; _simd_f32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x4_cmplt_enable() _simd_f32x64_cmplt_enable()
//#else
//	#define _simd_f32x4_cmplt(X,Y) _simd_f32x4_combine(\
//		_simd_f32x2_cmplt(_simd_f32x4_splitlo(X), _simd_f32x4_splitlo(Y)),\
//		_simd_f32x2_cmplt(_simd_f32x4_splithi(X), _simd_f32x4_splithi(Y)))
//	#define _simd_f32x4_cmplt_enable() (_simd_f32x2_cmplt_enable() && _simd_f32x4_combine_enable() && _simd_f32x4_splitlo_enable()  && _simd_f32x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x4_cmplt_) && ! defined(_simd_f32x4_cmplt_scalar_)
//	#define _simd_f32x4_cmplt_scalar_(X,Y) _simd_f32x4_cmplt_(X,_simd_f32x4_fill_scalar_(Y))
//	#define _simd_f32x4_cmplt_scalar_instruction_set _simd_f32x4_cmplt_instruction_set
//#endif
//#ifdef _simd_f32x4_cmplt_scalar_
//	#define _simd_f32x4_cmplt_scalar(X,Y) _simd_f32x4_cmplt_scalar_(X,Y)
//	#define _simd_f32x4_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_f32x4_cmplt_scalar(X,Y) _simd_f32x4_cmplt_safe(X,_simd_f32x4_fill_scalar_safe(Y))
//	#define _simd_f32x4_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_f32x1_cmplt_safe
//	#define _simd_f32x1_cmplt_safe(X,Y) static_cast<_simd_f32x1>(X < Y)
//	#define _simd_f32x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_f32x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_cmplt_enabled() true
//#endif
//
//#define _simd_f32x8_cmplt_safe(X,Y)_simd_f32x8_combine_safe(\
//	_simd_f32x4_cmplt_safe(_simd_f32x8_splitlo_safe(X), _simd_ f32x8_splitlo_safe(Y)),\
//	_simd_f32x4_cmplt_safe(_simd_f32x8_splithi_safe(X), _simd_ f32x8_splithi_safe(Y)))
//#ifdef _simd_f32x8_cmplt_
//	#define _simd_f32x8_cmplt(X,Y) _simd_f32x8_cmplt_(X, Y)
//	#define _simd_f32x8_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_cmplt_instruction_set>()
//#elif defined(_simd_f32x16_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_f32x8 ANVIL_SIMD_CALL _simd_f32x8_cmplt(const register _simd_f32x8 x, const register _simd_f32x8 y) {
//		union SIMDUnion { _simd_f32x8 v1; _simd_f32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x16_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x8_cmplt_enable() _simd_f32x16_cmplt_enable()
//#elif defined(_simd_f32x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_f32x8 ANVIL_SIMD_CALL _simd_f32x8_cmplt(const register _simd_f32x8 x, const register _simd_f32x8 y) {
//		union SIMDUnion { _simd_f32x8 v1; _simd_f32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x8_cmplt_enable() _simd_f32x32_cmplt_enable()
//#elif defined(_simd_f32x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_f32x8 ANVIL_SIMD_CALL _simd_f32x8_cmplt(const register _simd_f32x8 x, const register _simd_f32x8 y) {
//		union SIMDUnion { _simd_f32x8 v1; _simd_f32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x8_cmplt_enable() _simd_f32x64_cmplt_enable()
//#else
//	#define _simd_f32x8_cmplt(X,Y) _simd_f32x8_combine(\
//		_simd_f32x4_cmplt(_simd_f32x8_splitlo(X), _simd_f32x8_splitlo(Y)),\
//		_simd_f32x4_cmplt(_simd_f32x8_splithi(X), _simd_f32x8_splithi(Y)))
//	#define _simd_f32x8_cmplt_enable() (_simd_f32x4_cmplt_enable() && _simd_f32x8_combine_enable() && _simd_f32x8_splitlo_enable()  && _simd_f32x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x8_cmplt_) && ! defined(_simd_f32x8_cmplt_scalar_)
//	#define _simd_f32x8_cmplt_scalar_(X,Y) _simd_f32x8_cmplt_(X,_simd_f32x8_fill_scalar_(Y))
//	#define _simd_f32x8_cmplt_scalar_instruction_set _simd_f32x8_cmplt_instruction_set
//#endif
//#ifdef _simd_f32x8_cmplt_scalar_
//	#define _simd_f32x8_cmplt_scalar(X,Y) _simd_f32x8_cmplt_scalar_(X,Y)
//	#define _simd_f32x8_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_f32x8_cmplt_scalar(X,Y) _simd_f32x8_cmplt_safe(X,_simd_f32x8_fill_scalar_safe(Y))
//	#define _simd_f32x8_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_f32x1_cmplt_safe
//	#define _simd_f32x1_cmplt_safe(X,Y) static_cast<_simd_f32x1>(X < Y)
//	#define _simd_f32x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_f32x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_cmplt_enabled() true
//#endif
//
//#define _simd_f32x16_cmplt_safe(X,Y)_simd_f32x16_combine_safe(\
//	_simd_f32x8_cmplt_safe(_simd_f32x16_splitlo_safe(X), _simd_ f32x16_splitlo_safe(Y)),\
//	_simd_f32x8_cmplt_safe(_simd_f32x16_splithi_safe(X), _simd_ f32x16_splithi_safe(Y)))
//#ifdef _simd_f32x16_cmplt_
//	#define _simd_f32x16_cmplt(X,Y) _simd_f32x16_cmplt_(X, Y)
//	#define _simd_f32x16_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_cmplt_instruction_set>()
//#elif defined(_simd_f32x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_f32x16 ANVIL_SIMD_CALL _simd_f32x16_cmplt(const register _simd_f32x16 x, const register _simd_f32x16 y) {
//		union SIMDUnion { _simd_f32x16 v1; _simd_f32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x16_cmplt_enable() _simd_f32x32_cmplt_enable()
//#elif defined(_simd_f32x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_f32x16 ANVIL_SIMD_CALL _simd_f32x16_cmplt(const register _simd_f32x16 x, const register _simd_f32x16 y) {
//		union SIMDUnion { _simd_f32x16 v1; _simd_f32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x16_cmplt_enable() _simd_f32x64_cmplt_enable()
//#else
//	#define _simd_f32x16_cmplt(X,Y) _simd_f32x16_combine(\
//		_simd_f32x8_cmplt(_simd_f32x16_splitlo(X), _simd_f32x16_splitlo(Y)),\
//		_simd_f32x8_cmplt(_simd_f32x16_splithi(X), _simd_f32x16_splithi(Y)))
//	#define _simd_f32x16_cmplt_enable() (_simd_f32x8_cmplt_enable() && _simd_f32x16_combine_enable() && _simd_f32x16_splitlo_enable()  && _simd_f32x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x16_cmplt_) && ! defined(_simd_f32x16_cmplt_scalar_)
//	#define _simd_f32x16_cmplt_scalar_(X,Y) _simd_f32x16_cmplt_(X,_simd_f32x16_fill_scalar_(Y))
//	#define _simd_f32x16_cmplt_scalar_instruction_set _simd_f32x16_cmplt_instruction_set
//#endif
//#ifdef _simd_f32x16_cmplt_scalar_
//	#define _simd_f32x16_cmplt_scalar(X,Y) _simd_f32x16_cmplt_scalar_(X,Y)
//	#define _simd_f32x16_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_f32x16_cmplt_scalar(X,Y) _simd_f32x16_cmplt_safe(X,_simd_f32x16_fill_scalar_safe(Y))
//	#define _simd_f32x16_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_f32x1_cmplt_safe
//	#define _simd_f32x1_cmplt_safe(X,Y) static_cast<_simd_f32x1>(X < Y)
//	#define _simd_f32x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_f32x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_cmplt_enabled() true
//#endif
//
//#define _simd_f32x32_cmplt_safe(X,Y)_simd_f32x32_combine_safe(\
//	_simd_f32x16_cmplt_safe(_simd_f32x32_splitlo_safe(X), _simd_ f32x32_splitlo_safe(Y)),\
//	_simd_f32x16_cmplt_safe(_simd_f32x32_splithi_safe(X), _simd_ f32x32_splithi_safe(Y)))
//#ifdef _simd_f32x32_cmplt_
//	#define _simd_f32x32_cmplt(X,Y) _simd_f32x32_cmplt_(X, Y)
//	#define _simd_f32x32_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_cmplt_instruction_set>()
//#elif defined(_simd_f32x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_f32x32 ANVIL_SIMD_CALL _simd_f32x32_cmplt(const register _simd_f32x32 x, const register _simd_f32x32 y) {
//		union SIMDUnion { _simd_f32x32 v1; _simd_f32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x32_cmplt_enable() _simd_f32x64_cmplt_enable()
//#else
//	#define _simd_f32x32_cmplt(X,Y) _simd_f32x32_combine(\
//		_simd_f32x16_cmplt(_simd_f32x32_splitlo(X), _simd_f32x32_splitlo(Y)),\
//		_simd_f32x16_cmplt(_simd_f32x32_splithi(X), _simd_f32x32_splithi(Y)))
//	#define _simd_f32x32_cmplt_enable() (_simd_f32x16_cmplt_enable() && _simd_f32x32_combine_enable() && _simd_f32x32_splitlo_enable()  && _simd_f32x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x32_cmplt_) && ! defined(_simd_f32x32_cmplt_scalar_)
//	#define _simd_f32x32_cmplt_scalar_(X,Y) _simd_f32x32_cmplt_(X,_simd_f32x32_fill_scalar_(Y))
//	#define _simd_f32x32_cmplt_scalar_instruction_set _simd_f32x32_cmplt_instruction_set
//#endif
//#ifdef _simd_f32x32_cmplt_scalar_
//	#define _simd_f32x32_cmplt_scalar(X,Y) _simd_f32x32_cmplt_scalar_(X,Y)
//	#define _simd_f32x32_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_f32x32_cmplt_scalar(X,Y) _simd_f32x32_cmplt_safe(X,_simd_f32x32_fill_scalar_safe(Y))
//	#define _simd_f32x32_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_f32x1_cmplt_safe
//	#define _simd_f32x1_cmplt_safe(X,Y) static_cast<_simd_f32x1>(X < Y)
//	#define _simd_f32x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_f32x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_cmplt_enabled() true
//#endif
//
//#define _simd_f32x64_cmplt_safe(X,Y)_simd_f32x64_combine_safe(\
//	_simd_f32x32_cmplt_safe(_simd_f32x64_splitlo_safe(X), _simd_ f32x64_splitlo_safe(Y)),\
//	_simd_f32x32_cmplt_safe(_simd_f32x64_splithi_safe(X), _simd_ f32x64_splithi_safe(Y)))
//#ifdef _simd_f32x64_cmplt_
//	#define _simd_f32x64_cmplt(X,Y) _simd_f32x64_cmplt_(X, Y)
//	#define _simd_f32x64_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_cmplt_instruction_set>()
//#else
//	#define _simd_f32x64_cmplt(X,Y) _simd_f32x64_combine(\
//		_simd_f32x32_cmplt(_simd_f32x64_splitlo(X), _simd_f32x64_splitlo(Y)),\
//		_simd_f32x32_cmplt(_simd_f32x64_splithi(X), _simd_f32x64_splithi(Y)))
//	#define _simd_f32x64_cmplt_enable() (_simd_f32x32_cmplt_enable() && _simd_f32x64_combine_enable() && _simd_f32x64_splitlo_enable()  && _simd_f32x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x64_cmplt_) && ! defined(_simd_f32x64_cmplt_scalar_)
//	#define _simd_f32x64_cmplt_scalar_(X,Y) _simd_f32x64_cmplt_(X,_simd_f32x64_fill_scalar_(Y))
//	#define _simd_f32x64_cmplt_scalar_instruction_set _simd_f32x64_cmplt_instruction_set
//#endif
//#ifdef _simd_f32x64_cmplt_scalar_
//	#define _simd_f32x64_cmplt_scalar(X,Y) _simd_f32x64_cmplt_scalar_(X,Y)
//	#define _simd_f32x64_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_f32x64_cmplt_scalar(X,Y) _simd_f32x64_cmplt_safe(X,_simd_f32x64_fill_scalar_safe(Y))
//	#define _simd_f32x64_cmplt_scalar_enabled() true
//#endif
//
//// -- s64 --
//
//#ifndef _simd_s64x1_cmplt_safe
//	#define _simd_s64x1_cmplt_safe(X,Y) static_cast<_simd_s64x1>(X < Y)
//	#define _simd_s64x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_s64x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_cmplt_enabled() true
//#endif
//
//#define _simd_s64x2_cmplt_safe(X,Y)_simd_s64x2_combine_safe(\
//	_simd_s64x1_cmplt_safe(_simd_s64x2_splitlo_safe(X), _simd_ s64x2_splitlo_safe(Y)),\
//	_simd_s64x1_cmplt_safe(_simd_s64x2_splithi_safe(X), _simd_ s64x2_splithi_safe(Y)))
//#ifdef _simd_s64x2_cmplt_
//	#define _simd_s64x2_cmplt(X,Y) _simd_s64x2_cmplt_(X, Y)
//	#define _simd_s64x2_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_cmplt_instruction_set>()
//#elif defined(_simd_s64x4_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_cmplt(const register _simd_s64x2 x, const register _simd_s64x2 y) {
//		union SIMDUnion { _simd_s64x2 v1; _simd_s64x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x4_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x2_cmplt_enable() _simd_s64x4_cmplt_enable()
//#elif defined(_simd_s64x8_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_cmplt(const register _simd_s64x2 x, const register _simd_s64x2 y) {
//		union SIMDUnion { _simd_s64x2 v1; _simd_s64x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x8_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x2_cmplt_enable() _simd_s64x8_cmplt_enable()
//#elif defined(_simd_s64x16_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_cmplt(const register _simd_s64x2 x, const register _simd_s64x2 y) {
//		union SIMDUnion { _simd_s64x2 v1; _simd_s64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x16_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x2_cmplt_enable() _simd_s64x16_cmplt_enable()
//#elif defined(_simd_s64x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_cmplt(const register _simd_s64x2 x, const register _simd_s64x2 y) {
//		union SIMDUnion { _simd_s64x2 v1; _simd_s64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x2_cmplt_enable() _simd_s64x32_cmplt_enable()
//#elif defined(_simd_s64x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_cmplt(const register _simd_s64x2 x, const register _simd_s64x2 y) {
//		union SIMDUnion { _simd_s64x2 v1; _simd_s64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x2_cmplt_enable() _simd_s64x64_cmplt_enable()
//#else
//	#define _simd_s64x2_cmplt(X,Y) _simd_s64x2_combine(\
//		_simd_s64x1_cmplt(_simd_s64x2_splitlo(X), _simd_s64x2_splitlo(Y)),\
//		_simd_s64x1_cmplt(_simd_s64x2_splithi(X), _simd_s64x2_splithi(Y)))
//	#define _simd_s64x2_cmplt_enable() (_simd_s64x1_cmplt_enable() && _simd_s64x2_combine_enable() && _simd_s64x2_splitlo_enable()  && _simd_s64x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x2_cmplt_) && ! defined(_simd_s64x2_cmplt_scalar_)
//	#define _simd_s64x2_cmplt_scalar_(X,Y) _simd_s64x2_cmplt_(X,_simd_s64x2_fill_scalar_(Y))
//	#define _simd_s64x2_cmplt_scalar_instruction_set _simd_s64x2_cmplt_instruction_set
//#endif
//#ifdef _simd_s64x2_cmplt_scalar_
//	#define _simd_s64x2_cmplt_scalar(X,Y) _simd_s64x2_cmplt_scalar_(X,Y)
//	#define _simd_s64x2_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_s64x2_cmplt_scalar(X,Y) _simd_s64x2_cmplt_safe(X,_simd_s64x2_fill_scalar_safe(Y))
//	#define _simd_s64x2_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_s64x1_cmplt_safe
//	#define _simd_s64x1_cmplt_safe(X,Y) static_cast<_simd_s64x1>(X < Y)
//	#define _simd_s64x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_s64x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_cmplt_enabled() true
//#endif
//
//#define _simd_s64x4_cmplt_safe(X,Y)_simd_s64x4_combine_safe(\
//	_simd_s64x2_cmplt_safe(_simd_s64x4_splitlo_safe(X), _simd_ s64x4_splitlo_safe(Y)),\
//	_simd_s64x2_cmplt_safe(_simd_s64x4_splithi_safe(X), _simd_ s64x4_splithi_safe(Y)))
//#ifdef _simd_s64x4_cmplt_
//	#define _simd_s64x4_cmplt(X,Y) _simd_s64x4_cmplt_(X, Y)
//	#define _simd_s64x4_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_cmplt_instruction_set>()
//#elif defined(_simd_s64x8_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_cmplt(const register _simd_s64x4 x, const register _simd_s64x4 y) {
//		union SIMDUnion { _simd_s64x4 v1; _simd_s64x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x8_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x4_cmplt_enable() _simd_s64x8_cmplt_enable()
//#elif defined(_simd_s64x16_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_cmplt(const register _simd_s64x4 x, const register _simd_s64x4 y) {
//		union SIMDUnion { _simd_s64x4 v1; _simd_s64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x16_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x4_cmplt_enable() _simd_s64x16_cmplt_enable()
//#elif defined(_simd_s64x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_cmplt(const register _simd_s64x4 x, const register _simd_s64x4 y) {
//		union SIMDUnion { _simd_s64x4 v1; _simd_s64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x4_cmplt_enable() _simd_s64x32_cmplt_enable()
//#elif defined(_simd_s64x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_cmplt(const register _simd_s64x4 x, const register _simd_s64x4 y) {
//		union SIMDUnion { _simd_s64x4 v1; _simd_s64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x4_cmplt_enable() _simd_s64x64_cmplt_enable()
//#else
//	#define _simd_s64x4_cmplt(X,Y) _simd_s64x4_combine(\
//		_simd_s64x2_cmplt(_simd_s64x4_splitlo(X), _simd_s64x4_splitlo(Y)),\
//		_simd_s64x2_cmplt(_simd_s64x4_splithi(X), _simd_s64x4_splithi(Y)))
//	#define _simd_s64x4_cmplt_enable() (_simd_s64x2_cmplt_enable() && _simd_s64x4_combine_enable() && _simd_s64x4_splitlo_enable()  && _simd_s64x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x4_cmplt_) && ! defined(_simd_s64x4_cmplt_scalar_)
//	#define _simd_s64x4_cmplt_scalar_(X,Y) _simd_s64x4_cmplt_(X,_simd_s64x4_fill_scalar_(Y))
//	#define _simd_s64x4_cmplt_scalar_instruction_set _simd_s64x4_cmplt_instruction_set
//#endif
//#ifdef _simd_s64x4_cmplt_scalar_
//	#define _simd_s64x4_cmplt_scalar(X,Y) _simd_s64x4_cmplt_scalar_(X,Y)
//	#define _simd_s64x4_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_s64x4_cmplt_scalar(X,Y) _simd_s64x4_cmplt_safe(X,_simd_s64x4_fill_scalar_safe(Y))
//	#define _simd_s64x4_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_s64x1_cmplt_safe
//	#define _simd_s64x1_cmplt_safe(X,Y) static_cast<_simd_s64x1>(X < Y)
//	#define _simd_s64x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_s64x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_cmplt_enabled() true
//#endif
//
//#define _simd_s64x8_cmplt_safe(X,Y)_simd_s64x8_combine_safe(\
//	_simd_s64x4_cmplt_safe(_simd_s64x8_splitlo_safe(X), _simd_ s64x8_splitlo_safe(Y)),\
//	_simd_s64x4_cmplt_safe(_simd_s64x8_splithi_safe(X), _simd_ s64x8_splithi_safe(Y)))
//#ifdef _simd_s64x8_cmplt_
//	#define _simd_s64x8_cmplt(X,Y) _simd_s64x8_cmplt_(X, Y)
//	#define _simd_s64x8_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_cmplt_instruction_set>()
//#elif defined(_simd_s64x16_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s64x8 ANVIL_SIMD_CALL _simd_s64x8_cmplt(const register _simd_s64x8 x, const register _simd_s64x8 y) {
//		union SIMDUnion { _simd_s64x8 v1; _simd_s64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x16_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x8_cmplt_enable() _simd_s64x16_cmplt_enable()
//#elif defined(_simd_s64x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s64x8 ANVIL_SIMD_CALL _simd_s64x8_cmplt(const register _simd_s64x8 x, const register _simd_s64x8 y) {
//		union SIMDUnion { _simd_s64x8 v1; _simd_s64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x8_cmplt_enable() _simd_s64x32_cmplt_enable()
//#elif defined(_simd_s64x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s64x8 ANVIL_SIMD_CALL _simd_s64x8_cmplt(const register _simd_s64x8 x, const register _simd_s64x8 y) {
//		union SIMDUnion { _simd_s64x8 v1; _simd_s64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x8_cmplt_enable() _simd_s64x64_cmplt_enable()
//#else
//	#define _simd_s64x8_cmplt(X,Y) _simd_s64x8_combine(\
//		_simd_s64x4_cmplt(_simd_s64x8_splitlo(X), _simd_s64x8_splitlo(Y)),\
//		_simd_s64x4_cmplt(_simd_s64x8_splithi(X), _simd_s64x8_splithi(Y)))
//	#define _simd_s64x8_cmplt_enable() (_simd_s64x4_cmplt_enable() && _simd_s64x8_combine_enable() && _simd_s64x8_splitlo_enable()  && _simd_s64x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x8_cmplt_) && ! defined(_simd_s64x8_cmplt_scalar_)
//	#define _simd_s64x8_cmplt_scalar_(X,Y) _simd_s64x8_cmplt_(X,_simd_s64x8_fill_scalar_(Y))
//	#define _simd_s64x8_cmplt_scalar_instruction_set _simd_s64x8_cmplt_instruction_set
//#endif
//#ifdef _simd_s64x8_cmplt_scalar_
//	#define _simd_s64x8_cmplt_scalar(X,Y) _simd_s64x8_cmplt_scalar_(X,Y)
//	#define _simd_s64x8_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_s64x8_cmplt_scalar(X,Y) _simd_s64x8_cmplt_safe(X,_simd_s64x8_fill_scalar_safe(Y))
//	#define _simd_s64x8_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_s64x1_cmplt_safe
//	#define _simd_s64x1_cmplt_safe(X,Y) static_cast<_simd_s64x1>(X < Y)
//	#define _simd_s64x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_s64x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_cmplt_enabled() true
//#endif
//
//#define _simd_s64x16_cmplt_safe(X,Y)_simd_s64x16_combine_safe(\
//	_simd_s64x8_cmplt_safe(_simd_s64x16_splitlo_safe(X), _simd_ s64x16_splitlo_safe(Y)),\
//	_simd_s64x8_cmplt_safe(_simd_s64x16_splithi_safe(X), _simd_ s64x16_splithi_safe(Y)))
//#ifdef _simd_s64x16_cmplt_
//	#define _simd_s64x16_cmplt(X,Y) _simd_s64x16_cmplt_(X, Y)
//	#define _simd_s64x16_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_cmplt_instruction_set>()
//#elif defined(_simd_s64x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s64x16 ANVIL_SIMD_CALL _simd_s64x16_cmplt(const register _simd_s64x16 x, const register _simd_s64x16 y) {
//		union SIMDUnion { _simd_s64x16 v1; _simd_s64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x16_cmplt_enable() _simd_s64x32_cmplt_enable()
//#elif defined(_simd_s64x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s64x16 ANVIL_SIMD_CALL _simd_s64x16_cmplt(const register _simd_s64x16 x, const register _simd_s64x16 y) {
//		union SIMDUnion { _simd_s64x16 v1; _simd_s64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x16_cmplt_enable() _simd_s64x64_cmplt_enable()
//#else
//	#define _simd_s64x16_cmplt(X,Y) _simd_s64x16_combine(\
//		_simd_s64x8_cmplt(_simd_s64x16_splitlo(X), _simd_s64x16_splitlo(Y)),\
//		_simd_s64x8_cmplt(_simd_s64x16_splithi(X), _simd_s64x16_splithi(Y)))
//	#define _simd_s64x16_cmplt_enable() (_simd_s64x8_cmplt_enable() && _simd_s64x16_combine_enable() && _simd_s64x16_splitlo_enable()  && _simd_s64x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x16_cmplt_) && ! defined(_simd_s64x16_cmplt_scalar_)
//	#define _simd_s64x16_cmplt_scalar_(X,Y) _simd_s64x16_cmplt_(X,_simd_s64x16_fill_scalar_(Y))
//	#define _simd_s64x16_cmplt_scalar_instruction_set _simd_s64x16_cmplt_instruction_set
//#endif
//#ifdef _simd_s64x16_cmplt_scalar_
//	#define _simd_s64x16_cmplt_scalar(X,Y) _simd_s64x16_cmplt_scalar_(X,Y)
//	#define _simd_s64x16_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_s64x16_cmplt_scalar(X,Y) _simd_s64x16_cmplt_safe(X,_simd_s64x16_fill_scalar_safe(Y))
//	#define _simd_s64x16_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_s64x1_cmplt_safe
//	#define _simd_s64x1_cmplt_safe(X,Y) static_cast<_simd_s64x1>(X < Y)
//	#define _simd_s64x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_s64x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_cmplt_enabled() true
//#endif
//
//#define _simd_s64x32_cmplt_safe(X,Y)_simd_s64x32_combine_safe(\
//	_simd_s64x16_cmplt_safe(_simd_s64x32_splitlo_safe(X), _simd_ s64x32_splitlo_safe(Y)),\
//	_simd_s64x16_cmplt_safe(_simd_s64x32_splithi_safe(X), _simd_ s64x32_splithi_safe(Y)))
//#ifdef _simd_s64x32_cmplt_
//	#define _simd_s64x32_cmplt(X,Y) _simd_s64x32_cmplt_(X, Y)
//	#define _simd_s64x32_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_cmplt_instruction_set>()
//#elif defined(_simd_s64x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s64x32 ANVIL_SIMD_CALL _simd_s64x32_cmplt(const register _simd_s64x32 x, const register _simd_s64x32 y) {
//		union SIMDUnion { _simd_s64x32 v1; _simd_s64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x32_cmplt_enable() _simd_s64x64_cmplt_enable()
//#else
//	#define _simd_s64x32_cmplt(X,Y) _simd_s64x32_combine(\
//		_simd_s64x16_cmplt(_simd_s64x32_splitlo(X), _simd_s64x32_splitlo(Y)),\
//		_simd_s64x16_cmplt(_simd_s64x32_splithi(X), _simd_s64x32_splithi(Y)))
//	#define _simd_s64x32_cmplt_enable() (_simd_s64x16_cmplt_enable() && _simd_s64x32_combine_enable() && _simd_s64x32_splitlo_enable()  && _simd_s64x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x32_cmplt_) && ! defined(_simd_s64x32_cmplt_scalar_)
//	#define _simd_s64x32_cmplt_scalar_(X,Y) _simd_s64x32_cmplt_(X,_simd_s64x32_fill_scalar_(Y))
//	#define _simd_s64x32_cmplt_scalar_instruction_set _simd_s64x32_cmplt_instruction_set
//#endif
//#ifdef _simd_s64x32_cmplt_scalar_
//	#define _simd_s64x32_cmplt_scalar(X,Y) _simd_s64x32_cmplt_scalar_(X,Y)
//	#define _simd_s64x32_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_s64x32_cmplt_scalar(X,Y) _simd_s64x32_cmplt_safe(X,_simd_s64x32_fill_scalar_safe(Y))
//	#define _simd_s64x32_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_s64x1_cmplt_safe
//	#define _simd_s64x1_cmplt_safe(X,Y) static_cast<_simd_s64x1>(X < Y)
//	#define _simd_s64x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_s64x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_cmplt_enabled() true
//#endif
//
//#define _simd_s64x64_cmplt_safe(X,Y)_simd_s64x64_combine_safe(\
//	_simd_s64x32_cmplt_safe(_simd_s64x64_splitlo_safe(X), _simd_ s64x64_splitlo_safe(Y)),\
//	_simd_s64x32_cmplt_safe(_simd_s64x64_splithi_safe(X), _simd_ s64x64_splithi_safe(Y)))
//#ifdef _simd_s64x64_cmplt_
//	#define _simd_s64x64_cmplt(X,Y) _simd_s64x64_cmplt_(X, Y)
//	#define _simd_s64x64_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_cmplt_instruction_set>()
//#else
//	#define _simd_s64x64_cmplt(X,Y) _simd_s64x64_combine(\
//		_simd_s64x32_cmplt(_simd_s64x64_splitlo(X), _simd_s64x64_splitlo(Y)),\
//		_simd_s64x32_cmplt(_simd_s64x64_splithi(X), _simd_s64x64_splithi(Y)))
//	#define _simd_s64x64_cmplt_enable() (_simd_s64x32_cmplt_enable() && _simd_s64x64_combine_enable() && _simd_s64x64_splitlo_enable()  && _simd_s64x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x64_cmplt_) && ! defined(_simd_s64x64_cmplt_scalar_)
//	#define _simd_s64x64_cmplt_scalar_(X,Y) _simd_s64x64_cmplt_(X,_simd_s64x64_fill_scalar_(Y))
//	#define _simd_s64x64_cmplt_scalar_instruction_set _simd_s64x64_cmplt_instruction_set
//#endif
//#ifdef _simd_s64x64_cmplt_scalar_
//	#define _simd_s64x64_cmplt_scalar(X,Y) _simd_s64x64_cmplt_scalar_(X,Y)
//	#define _simd_s64x64_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_s64x64_cmplt_scalar(X,Y) _simd_s64x64_cmplt_safe(X,_simd_s64x64_fill_scalar_safe(Y))
//	#define _simd_s64x64_cmplt_scalar_enabled() true
//#endif
//
//// -- u64 --
//
//#ifndef _simd_u64x1_cmplt_safe
//	#define _simd_u64x1_cmplt_safe(X,Y) static_cast<_simd_u64x1>(X < Y)
//	#define _simd_u64x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_u64x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_cmplt_enabled() true
//#endif
//
//#define _simd_u64x2_cmplt_safe(X,Y)_simd_u64x2_combine_safe(\
//	_simd_u64x1_cmplt_safe(_simd_u64x2_splitlo_safe(X), _simd_ u64x2_splitlo_safe(Y)),\
//	_simd_u64x1_cmplt_safe(_simd_u64x2_splithi_safe(X), _simd_ u64x2_splithi_safe(Y)))
//#ifdef _simd_u64x2_cmplt_
//	#define _simd_u64x2_cmplt(X,Y) _simd_u64x2_cmplt_(X, Y)
//	#define _simd_u64x2_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_cmplt_instruction_set>()
//#elif defined(_simd_u64x4_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_cmplt(const register _simd_u64x2 x, const register _simd_u64x2 y) {
//		union SIMDUnion { _simd_u64x2 v1; _simd_u64x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x4_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x2_cmplt_enable() _simd_u64x4_cmplt_enable()
//#elif defined(_simd_u64x8_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_cmplt(const register _simd_u64x2 x, const register _simd_u64x2 y) {
//		union SIMDUnion { _simd_u64x2 v1; _simd_u64x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x8_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x2_cmplt_enable() _simd_u64x8_cmplt_enable()
//#elif defined(_simd_u64x16_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_cmplt(const register _simd_u64x2 x, const register _simd_u64x2 y) {
//		union SIMDUnion { _simd_u64x2 v1; _simd_u64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x16_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x2_cmplt_enable() _simd_u64x16_cmplt_enable()
//#elif defined(_simd_u64x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_cmplt(const register _simd_u64x2 x, const register _simd_u64x2 y) {
//		union SIMDUnion { _simd_u64x2 v1; _simd_u64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x2_cmplt_enable() _simd_u64x32_cmplt_enable()
//#elif defined(_simd_u64x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_cmplt(const register _simd_u64x2 x, const register _simd_u64x2 y) {
//		union SIMDUnion { _simd_u64x2 v1; _simd_u64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x2_cmplt_enable() _simd_u64x64_cmplt_enable()
//#else
//	#define _simd_u64x2_cmplt(X,Y) _simd_u64x2_combine(\
//		_simd_u64x1_cmplt(_simd_u64x2_splitlo(X), _simd_u64x2_splitlo(Y)),\
//		_simd_u64x1_cmplt(_simd_u64x2_splithi(X), _simd_u64x2_splithi(Y)))
//	#define _simd_u64x2_cmplt_enable() (_simd_u64x1_cmplt_enable() && _simd_u64x2_combine_enable() && _simd_u64x2_splitlo_enable()  && _simd_u64x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x2_cmplt_) && ! defined(_simd_u64x2_cmplt_scalar_)
//	#define _simd_u64x2_cmplt_scalar_(X,Y) _simd_u64x2_cmplt_(X,_simd_u64x2_fill_scalar_(Y))
//	#define _simd_u64x2_cmplt_scalar_instruction_set _simd_u64x2_cmplt_instruction_set
//#endif
//#ifdef _simd_u64x2_cmplt_scalar_
//	#define _simd_u64x2_cmplt_scalar(X,Y) _simd_u64x2_cmplt_scalar_(X,Y)
//	#define _simd_u64x2_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_u64x2_cmplt_scalar(X,Y) _simd_u64x2_cmplt_safe(X,_simd_u64x2_fill_scalar_safe(Y))
//	#define _simd_u64x2_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_u64x1_cmplt_safe
//	#define _simd_u64x1_cmplt_safe(X,Y) static_cast<_simd_u64x1>(X < Y)
//	#define _simd_u64x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_u64x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_cmplt_enabled() true
//#endif
//
//#define _simd_u64x4_cmplt_safe(X,Y)_simd_u64x4_combine_safe(\
//	_simd_u64x2_cmplt_safe(_simd_u64x4_splitlo_safe(X), _simd_ u64x4_splitlo_safe(Y)),\
//	_simd_u64x2_cmplt_safe(_simd_u64x4_splithi_safe(X), _simd_ u64x4_splithi_safe(Y)))
//#ifdef _simd_u64x4_cmplt_
//	#define _simd_u64x4_cmplt(X,Y) _simd_u64x4_cmplt_(X, Y)
//	#define _simd_u64x4_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_cmplt_instruction_set>()
//#elif defined(_simd_u64x8_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_cmplt(const register _simd_u64x4 x, const register _simd_u64x4 y) {
//		union SIMDUnion { _simd_u64x4 v1; _simd_u64x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x8_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x4_cmplt_enable() _simd_u64x8_cmplt_enable()
//#elif defined(_simd_u64x16_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_cmplt(const register _simd_u64x4 x, const register _simd_u64x4 y) {
//		union SIMDUnion { _simd_u64x4 v1; _simd_u64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x16_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x4_cmplt_enable() _simd_u64x16_cmplt_enable()
//#elif defined(_simd_u64x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_cmplt(const register _simd_u64x4 x, const register _simd_u64x4 y) {
//		union SIMDUnion { _simd_u64x4 v1; _simd_u64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x4_cmplt_enable() _simd_u64x32_cmplt_enable()
//#elif defined(_simd_u64x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_cmplt(const register _simd_u64x4 x, const register _simd_u64x4 y) {
//		union SIMDUnion { _simd_u64x4 v1; _simd_u64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x4_cmplt_enable() _simd_u64x64_cmplt_enable()
//#else
//	#define _simd_u64x4_cmplt(X,Y) _simd_u64x4_combine(\
//		_simd_u64x2_cmplt(_simd_u64x4_splitlo(X), _simd_u64x4_splitlo(Y)),\
//		_simd_u64x2_cmplt(_simd_u64x4_splithi(X), _simd_u64x4_splithi(Y)))
//	#define _simd_u64x4_cmplt_enable() (_simd_u64x2_cmplt_enable() && _simd_u64x4_combine_enable() && _simd_u64x4_splitlo_enable()  && _simd_u64x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x4_cmplt_) && ! defined(_simd_u64x4_cmplt_scalar_)
//	#define _simd_u64x4_cmplt_scalar_(X,Y) _simd_u64x4_cmplt_(X,_simd_u64x4_fill_scalar_(Y))
//	#define _simd_u64x4_cmplt_scalar_instruction_set _simd_u64x4_cmplt_instruction_set
//#endif
//#ifdef _simd_u64x4_cmplt_scalar_
//	#define _simd_u64x4_cmplt_scalar(X,Y) _simd_u64x4_cmplt_scalar_(X,Y)
//	#define _simd_u64x4_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_u64x4_cmplt_scalar(X,Y) _simd_u64x4_cmplt_safe(X,_simd_u64x4_fill_scalar_safe(Y))
//	#define _simd_u64x4_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_u64x1_cmplt_safe
//	#define _simd_u64x1_cmplt_safe(X,Y) static_cast<_simd_u64x1>(X < Y)
//	#define _simd_u64x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_u64x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_cmplt_enabled() true
//#endif
//
//#define _simd_u64x8_cmplt_safe(X,Y)_simd_u64x8_combine_safe(\
//	_simd_u64x4_cmplt_safe(_simd_u64x8_splitlo_safe(X), _simd_ u64x8_splitlo_safe(Y)),\
//	_simd_u64x4_cmplt_safe(_simd_u64x8_splithi_safe(X), _simd_ u64x8_splithi_safe(Y)))
//#ifdef _simd_u64x8_cmplt_
//	#define _simd_u64x8_cmplt(X,Y) _simd_u64x8_cmplt_(X, Y)
//	#define _simd_u64x8_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_cmplt_instruction_set>()
//#elif defined(_simd_u64x16_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u64x8 ANVIL_SIMD_CALL _simd_u64x8_cmplt(const register _simd_u64x8 x, const register _simd_u64x8 y) {
//		union SIMDUnion { _simd_u64x8 v1; _simd_u64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x16_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x8_cmplt_enable() _simd_u64x16_cmplt_enable()
//#elif defined(_simd_u64x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u64x8 ANVIL_SIMD_CALL _simd_u64x8_cmplt(const register _simd_u64x8 x, const register _simd_u64x8 y) {
//		union SIMDUnion { _simd_u64x8 v1; _simd_u64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x8_cmplt_enable() _simd_u64x32_cmplt_enable()
//#elif defined(_simd_u64x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u64x8 ANVIL_SIMD_CALL _simd_u64x8_cmplt(const register _simd_u64x8 x, const register _simd_u64x8 y) {
//		union SIMDUnion { _simd_u64x8 v1; _simd_u64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x8_cmplt_enable() _simd_u64x64_cmplt_enable()
//#else
//	#define _simd_u64x8_cmplt(X,Y) _simd_u64x8_combine(\
//		_simd_u64x4_cmplt(_simd_u64x8_splitlo(X), _simd_u64x8_splitlo(Y)),\
//		_simd_u64x4_cmplt(_simd_u64x8_splithi(X), _simd_u64x8_splithi(Y)))
//	#define _simd_u64x8_cmplt_enable() (_simd_u64x4_cmplt_enable() && _simd_u64x8_combine_enable() && _simd_u64x8_splitlo_enable()  && _simd_u64x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x8_cmplt_) && ! defined(_simd_u64x8_cmplt_scalar_)
//	#define _simd_u64x8_cmplt_scalar_(X,Y) _simd_u64x8_cmplt_(X,_simd_u64x8_fill_scalar_(Y))
//	#define _simd_u64x8_cmplt_scalar_instruction_set _simd_u64x8_cmplt_instruction_set
//#endif
//#ifdef _simd_u64x8_cmplt_scalar_
//	#define _simd_u64x8_cmplt_scalar(X,Y) _simd_u64x8_cmplt_scalar_(X,Y)
//	#define _simd_u64x8_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_u64x8_cmplt_scalar(X,Y) _simd_u64x8_cmplt_safe(X,_simd_u64x8_fill_scalar_safe(Y))
//	#define _simd_u64x8_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_u64x1_cmplt_safe
//	#define _simd_u64x1_cmplt_safe(X,Y) static_cast<_simd_u64x1>(X < Y)
//	#define _simd_u64x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_u64x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_cmplt_enabled() true
//#endif
//
//#define _simd_u64x16_cmplt_safe(X,Y)_simd_u64x16_combine_safe(\
//	_simd_u64x8_cmplt_safe(_simd_u64x16_splitlo_safe(X), _simd_ u64x16_splitlo_safe(Y)),\
//	_simd_u64x8_cmplt_safe(_simd_u64x16_splithi_safe(X), _simd_ u64x16_splithi_safe(Y)))
//#ifdef _simd_u64x16_cmplt_
//	#define _simd_u64x16_cmplt(X,Y) _simd_u64x16_cmplt_(X, Y)
//	#define _simd_u64x16_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_cmplt_instruction_set>()
//#elif defined(_simd_u64x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u64x16 ANVIL_SIMD_CALL _simd_u64x16_cmplt(const register _simd_u64x16 x, const register _simd_u64x16 y) {
//		union SIMDUnion { _simd_u64x16 v1; _simd_u64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x16_cmplt_enable() _simd_u64x32_cmplt_enable()
//#elif defined(_simd_u64x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u64x16 ANVIL_SIMD_CALL _simd_u64x16_cmplt(const register _simd_u64x16 x, const register _simd_u64x16 y) {
//		union SIMDUnion { _simd_u64x16 v1; _simd_u64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x16_cmplt_enable() _simd_u64x64_cmplt_enable()
//#else
//	#define _simd_u64x16_cmplt(X,Y) _simd_u64x16_combine(\
//		_simd_u64x8_cmplt(_simd_u64x16_splitlo(X), _simd_u64x16_splitlo(Y)),\
//		_simd_u64x8_cmplt(_simd_u64x16_splithi(X), _simd_u64x16_splithi(Y)))
//	#define _simd_u64x16_cmplt_enable() (_simd_u64x8_cmplt_enable() && _simd_u64x16_combine_enable() && _simd_u64x16_splitlo_enable()  && _simd_u64x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x16_cmplt_) && ! defined(_simd_u64x16_cmplt_scalar_)
//	#define _simd_u64x16_cmplt_scalar_(X,Y) _simd_u64x16_cmplt_(X,_simd_u64x16_fill_scalar_(Y))
//	#define _simd_u64x16_cmplt_scalar_instruction_set _simd_u64x16_cmplt_instruction_set
//#endif
//#ifdef _simd_u64x16_cmplt_scalar_
//	#define _simd_u64x16_cmplt_scalar(X,Y) _simd_u64x16_cmplt_scalar_(X,Y)
//	#define _simd_u64x16_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_u64x16_cmplt_scalar(X,Y) _simd_u64x16_cmplt_safe(X,_simd_u64x16_fill_scalar_safe(Y))
//	#define _simd_u64x16_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_u64x1_cmplt_safe
//	#define _simd_u64x1_cmplt_safe(X,Y) static_cast<_simd_u64x1>(X < Y)
//	#define _simd_u64x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_u64x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_cmplt_enabled() true
//#endif
//
//#define _simd_u64x32_cmplt_safe(X,Y)_simd_u64x32_combine_safe(\
//	_simd_u64x16_cmplt_safe(_simd_u64x32_splitlo_safe(X), _simd_ u64x32_splitlo_safe(Y)),\
//	_simd_u64x16_cmplt_safe(_simd_u64x32_splithi_safe(X), _simd_ u64x32_splithi_safe(Y)))
//#ifdef _simd_u64x32_cmplt_
//	#define _simd_u64x32_cmplt(X,Y) _simd_u64x32_cmplt_(X, Y)
//	#define _simd_u64x32_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_cmplt_instruction_set>()
//#elif defined(_simd_u64x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u64x32 ANVIL_SIMD_CALL _simd_u64x32_cmplt(const register _simd_u64x32 x, const register _simd_u64x32 y) {
//		union SIMDUnion { _simd_u64x32 v1; _simd_u64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x32_cmplt_enable() _simd_u64x64_cmplt_enable()
//#else
//	#define _simd_u64x32_cmplt(X,Y) _simd_u64x32_combine(\
//		_simd_u64x16_cmplt(_simd_u64x32_splitlo(X), _simd_u64x32_splitlo(Y)),\
//		_simd_u64x16_cmplt(_simd_u64x32_splithi(X), _simd_u64x32_splithi(Y)))
//	#define _simd_u64x32_cmplt_enable() (_simd_u64x16_cmplt_enable() && _simd_u64x32_combine_enable() && _simd_u64x32_splitlo_enable()  && _simd_u64x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x32_cmplt_) && ! defined(_simd_u64x32_cmplt_scalar_)
//	#define _simd_u64x32_cmplt_scalar_(X,Y) _simd_u64x32_cmplt_(X,_simd_u64x32_fill_scalar_(Y))
//	#define _simd_u64x32_cmplt_scalar_instruction_set _simd_u64x32_cmplt_instruction_set
//#endif
//#ifdef _simd_u64x32_cmplt_scalar_
//	#define _simd_u64x32_cmplt_scalar(X,Y) _simd_u64x32_cmplt_scalar_(X,Y)
//	#define _simd_u64x32_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_u64x32_cmplt_scalar(X,Y) _simd_u64x32_cmplt_safe(X,_simd_u64x32_fill_scalar_safe(Y))
//	#define _simd_u64x32_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_u64x1_cmplt_safe
//	#define _simd_u64x1_cmplt_safe(X,Y) static_cast<_simd_u64x1>(X < Y)
//	#define _simd_u64x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_u64x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_cmplt_enabled() true
//#endif
//
//#define _simd_u64x64_cmplt_safe(X,Y)_simd_u64x64_combine_safe(\
//	_simd_u64x32_cmplt_safe(_simd_u64x64_splitlo_safe(X), _simd_ u64x64_splitlo_safe(Y)),\
//	_simd_u64x32_cmplt_safe(_simd_u64x64_splithi_safe(X), _simd_ u64x64_splithi_safe(Y)))
//#ifdef _simd_u64x64_cmplt_
//	#define _simd_u64x64_cmplt(X,Y) _simd_u64x64_cmplt_(X, Y)
//	#define _simd_u64x64_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_cmplt_instruction_set>()
//#else
//	#define _simd_u64x64_cmplt(X,Y) _simd_u64x64_combine(\
//		_simd_u64x32_cmplt(_simd_u64x64_splitlo(X), _simd_u64x64_splitlo(Y)),\
//		_simd_u64x32_cmplt(_simd_u64x64_splithi(X), _simd_u64x64_splithi(Y)))
//	#define _simd_u64x64_cmplt_enable() (_simd_u64x32_cmplt_enable() && _simd_u64x64_combine_enable() && _simd_u64x64_splitlo_enable()  && _simd_u64x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x64_cmplt_) && ! defined(_simd_u64x64_cmplt_scalar_)
//	#define _simd_u64x64_cmplt_scalar_(X,Y) _simd_u64x64_cmplt_(X,_simd_u64x64_fill_scalar_(Y))
//	#define _simd_u64x64_cmplt_scalar_instruction_set _simd_u64x64_cmplt_instruction_set
//#endif
//#ifdef _simd_u64x64_cmplt_scalar_
//	#define _simd_u64x64_cmplt_scalar(X,Y) _simd_u64x64_cmplt_scalar_(X,Y)
//	#define _simd_u64x64_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_u64x64_cmplt_scalar(X,Y) _simd_u64x64_cmplt_safe(X,_simd_u64x64_fill_scalar_safe(Y))
//	#define _simd_u64x64_cmplt_scalar_enabled() true
//#endif
//
//// -- s32 --
//
//#ifndef _simd_s32x1_cmplt_safe
//	#define _simd_s32x1_cmplt_safe(X,Y) static_cast<_simd_s32x1>(X < Y)
//	#define _simd_s32x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_s32x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_cmplt_enabled() true
//#endif
//
//#define _simd_s32x2_cmplt_safe(X,Y)_simd_s32x2_combine_safe(\
//	_simd_s32x1_cmplt_safe(_simd_s32x2_splitlo_safe(X), _simd_ s32x2_splitlo_safe(Y)),\
//	_simd_s32x1_cmplt_safe(_simd_s32x2_splithi_safe(X), _simd_ s32x2_splithi_safe(Y)))
//#ifdef _simd_s32x2_cmplt_
//	#define _simd_s32x2_cmplt(X,Y) _simd_s32x2_cmplt_(X, Y)
//	#define _simd_s32x2_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_cmplt_instruction_set>()
//#elif defined(_simd_s32x4_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_cmplt(const register _simd_s32x2 x, const register _simd_s32x2 y) {
//		union SIMDUnion { _simd_s32x2 v1; _simd_s32x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x4_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x2_cmplt_enable() _simd_s32x4_cmplt_enable()
//#elif defined(_simd_s32x8_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_cmplt(const register _simd_s32x2 x, const register _simd_s32x2 y) {
//		union SIMDUnion { _simd_s32x2 v1; _simd_s32x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x8_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x2_cmplt_enable() _simd_s32x8_cmplt_enable()
//#elif defined(_simd_s32x16_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_cmplt(const register _simd_s32x2 x, const register _simd_s32x2 y) {
//		union SIMDUnion { _simd_s32x2 v1; _simd_s32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x16_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x2_cmplt_enable() _simd_s32x16_cmplt_enable()
//#elif defined(_simd_s32x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_cmplt(const register _simd_s32x2 x, const register _simd_s32x2 y) {
//		union SIMDUnion { _simd_s32x2 v1; _simd_s32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x2_cmplt_enable() _simd_s32x32_cmplt_enable()
//#elif defined(_simd_s32x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_cmplt(const register _simd_s32x2 x, const register _simd_s32x2 y) {
//		union SIMDUnion { _simd_s32x2 v1; _simd_s32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x2_cmplt_enable() _simd_s32x64_cmplt_enable()
//#else
//	#define _simd_s32x2_cmplt(X,Y) _simd_s32x2_combine(\
//		_simd_s32x1_cmplt(_simd_s32x2_splitlo(X), _simd_s32x2_splitlo(Y)),\
//		_simd_s32x1_cmplt(_simd_s32x2_splithi(X), _simd_s32x2_splithi(Y)))
//	#define _simd_s32x2_cmplt_enable() (_simd_s32x1_cmplt_enable() && _simd_s32x2_combine_enable() && _simd_s32x2_splitlo_enable()  && _simd_s32x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x2_cmplt_) && ! defined(_simd_s32x2_cmplt_scalar_)
//	#define _simd_s32x2_cmplt_scalar_(X,Y) _simd_s32x2_cmplt_(X,_simd_s32x2_fill_scalar_(Y))
//	#define _simd_s32x2_cmplt_scalar_instruction_set _simd_s32x2_cmplt_instruction_set
//#endif
//#ifdef _simd_s32x2_cmplt_scalar_
//	#define _simd_s32x2_cmplt_scalar(X,Y) _simd_s32x2_cmplt_scalar_(X,Y)
//	#define _simd_s32x2_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_s32x2_cmplt_scalar(X,Y) _simd_s32x2_cmplt_safe(X,_simd_s32x2_fill_scalar_safe(Y))
//	#define _simd_s32x2_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_s32x1_cmplt_safe
//	#define _simd_s32x1_cmplt_safe(X,Y) static_cast<_simd_s32x1>(X < Y)
//	#define _simd_s32x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_s32x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_cmplt_enabled() true
//#endif
//
//#define _simd_s32x4_cmplt_safe(X,Y)_simd_s32x4_combine_safe(\
//	_simd_s32x2_cmplt_safe(_simd_s32x4_splitlo_safe(X), _simd_ s32x4_splitlo_safe(Y)),\
//	_simd_s32x2_cmplt_safe(_simd_s32x4_splithi_safe(X), _simd_ s32x4_splithi_safe(Y)))
//#ifdef _simd_s32x4_cmplt_
//	#define _simd_s32x4_cmplt(X,Y) _simd_s32x4_cmplt_(X, Y)
//	#define _simd_s32x4_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_cmplt_instruction_set>()
//#elif defined(_simd_s32x8_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_cmplt(const register _simd_s32x4 x, const register _simd_s32x4 y) {
//		union SIMDUnion { _simd_s32x4 v1; _simd_s32x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x8_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x4_cmplt_enable() _simd_s32x8_cmplt_enable()
//#elif defined(_simd_s32x16_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_cmplt(const register _simd_s32x4 x, const register _simd_s32x4 y) {
//		union SIMDUnion { _simd_s32x4 v1; _simd_s32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x16_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x4_cmplt_enable() _simd_s32x16_cmplt_enable()
//#elif defined(_simd_s32x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_cmplt(const register _simd_s32x4 x, const register _simd_s32x4 y) {
//		union SIMDUnion { _simd_s32x4 v1; _simd_s32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x4_cmplt_enable() _simd_s32x32_cmplt_enable()
//#elif defined(_simd_s32x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_cmplt(const register _simd_s32x4 x, const register _simd_s32x4 y) {
//		union SIMDUnion { _simd_s32x4 v1; _simd_s32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x4_cmplt_enable() _simd_s32x64_cmplt_enable()
//#else
//	#define _simd_s32x4_cmplt(X,Y) _simd_s32x4_combine(\
//		_simd_s32x2_cmplt(_simd_s32x4_splitlo(X), _simd_s32x4_splitlo(Y)),\
//		_simd_s32x2_cmplt(_simd_s32x4_splithi(X), _simd_s32x4_splithi(Y)))
//	#define _simd_s32x4_cmplt_enable() (_simd_s32x2_cmplt_enable() && _simd_s32x4_combine_enable() && _simd_s32x4_splitlo_enable()  && _simd_s32x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x4_cmplt_) && ! defined(_simd_s32x4_cmplt_scalar_)
//	#define _simd_s32x4_cmplt_scalar_(X,Y) _simd_s32x4_cmplt_(X,_simd_s32x4_fill_scalar_(Y))
//	#define _simd_s32x4_cmplt_scalar_instruction_set _simd_s32x4_cmplt_instruction_set
//#endif
//#ifdef _simd_s32x4_cmplt_scalar_
//	#define _simd_s32x4_cmplt_scalar(X,Y) _simd_s32x4_cmplt_scalar_(X,Y)
//	#define _simd_s32x4_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_s32x4_cmplt_scalar(X,Y) _simd_s32x4_cmplt_safe(X,_simd_s32x4_fill_scalar_safe(Y))
//	#define _simd_s32x4_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_s32x1_cmplt_safe
//	#define _simd_s32x1_cmplt_safe(X,Y) static_cast<_simd_s32x1>(X < Y)
//	#define _simd_s32x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_s32x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_cmplt_enabled() true
//#endif
//
//#define _simd_s32x8_cmplt_safe(X,Y)_simd_s32x8_combine_safe(\
//	_simd_s32x4_cmplt_safe(_simd_s32x8_splitlo_safe(X), _simd_ s32x8_splitlo_safe(Y)),\
//	_simd_s32x4_cmplt_safe(_simd_s32x8_splithi_safe(X), _simd_ s32x8_splithi_safe(Y)))
//#ifdef _simd_s32x8_cmplt_
//	#define _simd_s32x8_cmplt(X,Y) _simd_s32x8_cmplt_(X, Y)
//	#define _simd_s32x8_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_cmplt_instruction_set>()
//#elif defined(_simd_s32x16_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s32x8 ANVIL_SIMD_CALL _simd_s32x8_cmplt(const register _simd_s32x8 x, const register _simd_s32x8 y) {
//		union SIMDUnion { _simd_s32x8 v1; _simd_s32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x16_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x8_cmplt_enable() _simd_s32x16_cmplt_enable()
//#elif defined(_simd_s32x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s32x8 ANVIL_SIMD_CALL _simd_s32x8_cmplt(const register _simd_s32x8 x, const register _simd_s32x8 y) {
//		union SIMDUnion { _simd_s32x8 v1; _simd_s32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x8_cmplt_enable() _simd_s32x32_cmplt_enable()
//#elif defined(_simd_s32x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s32x8 ANVIL_SIMD_CALL _simd_s32x8_cmplt(const register _simd_s32x8 x, const register _simd_s32x8 y) {
//		union SIMDUnion { _simd_s32x8 v1; _simd_s32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x8_cmplt_enable() _simd_s32x64_cmplt_enable()
//#else
//	#define _simd_s32x8_cmplt(X,Y) _simd_s32x8_combine(\
//		_simd_s32x4_cmplt(_simd_s32x8_splitlo(X), _simd_s32x8_splitlo(Y)),\
//		_simd_s32x4_cmplt(_simd_s32x8_splithi(X), _simd_s32x8_splithi(Y)))
//	#define _simd_s32x8_cmplt_enable() (_simd_s32x4_cmplt_enable() && _simd_s32x8_combine_enable() && _simd_s32x8_splitlo_enable()  && _simd_s32x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x8_cmplt_) && ! defined(_simd_s32x8_cmplt_scalar_)
//	#define _simd_s32x8_cmplt_scalar_(X,Y) _simd_s32x8_cmplt_(X,_simd_s32x8_fill_scalar_(Y))
//	#define _simd_s32x8_cmplt_scalar_instruction_set _simd_s32x8_cmplt_instruction_set
//#endif
//#ifdef _simd_s32x8_cmplt_scalar_
//	#define _simd_s32x8_cmplt_scalar(X,Y) _simd_s32x8_cmplt_scalar_(X,Y)
//	#define _simd_s32x8_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_s32x8_cmplt_scalar(X,Y) _simd_s32x8_cmplt_safe(X,_simd_s32x8_fill_scalar_safe(Y))
//	#define _simd_s32x8_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_s32x1_cmplt_safe
//	#define _simd_s32x1_cmplt_safe(X,Y) static_cast<_simd_s32x1>(X < Y)
//	#define _simd_s32x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_s32x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_cmplt_enabled() true
//#endif
//
//#define _simd_s32x16_cmplt_safe(X,Y)_simd_s32x16_combine_safe(\
//	_simd_s32x8_cmplt_safe(_simd_s32x16_splitlo_safe(X), _simd_ s32x16_splitlo_safe(Y)),\
//	_simd_s32x8_cmplt_safe(_simd_s32x16_splithi_safe(X), _simd_ s32x16_splithi_safe(Y)))
//#ifdef _simd_s32x16_cmplt_
//	#define _simd_s32x16_cmplt(X,Y) _simd_s32x16_cmplt_(X, Y)
//	#define _simd_s32x16_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_cmplt_instruction_set>()
//#elif defined(_simd_s32x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s32x16 ANVIL_SIMD_CALL _simd_s32x16_cmplt(const register _simd_s32x16 x, const register _simd_s32x16 y) {
//		union SIMDUnion { _simd_s32x16 v1; _simd_s32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x16_cmplt_enable() _simd_s32x32_cmplt_enable()
//#elif defined(_simd_s32x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s32x16 ANVIL_SIMD_CALL _simd_s32x16_cmplt(const register _simd_s32x16 x, const register _simd_s32x16 y) {
//		union SIMDUnion { _simd_s32x16 v1; _simd_s32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x16_cmplt_enable() _simd_s32x64_cmplt_enable()
//#else
//	#define _simd_s32x16_cmplt(X,Y) _simd_s32x16_combine(\
//		_simd_s32x8_cmplt(_simd_s32x16_splitlo(X), _simd_s32x16_splitlo(Y)),\
//		_simd_s32x8_cmplt(_simd_s32x16_splithi(X), _simd_s32x16_splithi(Y)))
//	#define _simd_s32x16_cmplt_enable() (_simd_s32x8_cmplt_enable() && _simd_s32x16_combine_enable() && _simd_s32x16_splitlo_enable()  && _simd_s32x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x16_cmplt_) && ! defined(_simd_s32x16_cmplt_scalar_)
//	#define _simd_s32x16_cmplt_scalar_(X,Y) _simd_s32x16_cmplt_(X,_simd_s32x16_fill_scalar_(Y))
//	#define _simd_s32x16_cmplt_scalar_instruction_set _simd_s32x16_cmplt_instruction_set
//#endif
//#ifdef _simd_s32x16_cmplt_scalar_
//	#define _simd_s32x16_cmplt_scalar(X,Y) _simd_s32x16_cmplt_scalar_(X,Y)
//	#define _simd_s32x16_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_s32x16_cmplt_scalar(X,Y) _simd_s32x16_cmplt_safe(X,_simd_s32x16_fill_scalar_safe(Y))
//	#define _simd_s32x16_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_s32x1_cmplt_safe
//	#define _simd_s32x1_cmplt_safe(X,Y) static_cast<_simd_s32x1>(X < Y)
//	#define _simd_s32x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_s32x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_cmplt_enabled() true
//#endif
//
//#define _simd_s32x32_cmplt_safe(X,Y)_simd_s32x32_combine_safe(\
//	_simd_s32x16_cmplt_safe(_simd_s32x32_splitlo_safe(X), _simd_ s32x32_splitlo_safe(Y)),\
//	_simd_s32x16_cmplt_safe(_simd_s32x32_splithi_safe(X), _simd_ s32x32_splithi_safe(Y)))
//#ifdef _simd_s32x32_cmplt_
//	#define _simd_s32x32_cmplt(X,Y) _simd_s32x32_cmplt_(X, Y)
//	#define _simd_s32x32_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_cmplt_instruction_set>()
//#elif defined(_simd_s32x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s32x32 ANVIL_SIMD_CALL _simd_s32x32_cmplt(const register _simd_s32x32 x, const register _simd_s32x32 y) {
//		union SIMDUnion { _simd_s32x32 v1; _simd_s32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x32_cmplt_enable() _simd_s32x64_cmplt_enable()
//#else
//	#define _simd_s32x32_cmplt(X,Y) _simd_s32x32_combine(\
//		_simd_s32x16_cmplt(_simd_s32x32_splitlo(X), _simd_s32x32_splitlo(Y)),\
//		_simd_s32x16_cmplt(_simd_s32x32_splithi(X), _simd_s32x32_splithi(Y)))
//	#define _simd_s32x32_cmplt_enable() (_simd_s32x16_cmplt_enable() && _simd_s32x32_combine_enable() && _simd_s32x32_splitlo_enable()  && _simd_s32x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x32_cmplt_) && ! defined(_simd_s32x32_cmplt_scalar_)
//	#define _simd_s32x32_cmplt_scalar_(X,Y) _simd_s32x32_cmplt_(X,_simd_s32x32_fill_scalar_(Y))
//	#define _simd_s32x32_cmplt_scalar_instruction_set _simd_s32x32_cmplt_instruction_set
//#endif
//#ifdef _simd_s32x32_cmplt_scalar_
//	#define _simd_s32x32_cmplt_scalar(X,Y) _simd_s32x32_cmplt_scalar_(X,Y)
//	#define _simd_s32x32_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_s32x32_cmplt_scalar(X,Y) _simd_s32x32_cmplt_safe(X,_simd_s32x32_fill_scalar_safe(Y))
//	#define _simd_s32x32_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_s32x1_cmplt_safe
//	#define _simd_s32x1_cmplt_safe(X,Y) static_cast<_simd_s32x1>(X < Y)
//	#define _simd_s32x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_s32x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_cmplt_enabled() true
//#endif
//
//#define _simd_s32x64_cmplt_safe(X,Y)_simd_s32x64_combine_safe(\
//	_simd_s32x32_cmplt_safe(_simd_s32x64_splitlo_safe(X), _simd_ s32x64_splitlo_safe(Y)),\
//	_simd_s32x32_cmplt_safe(_simd_s32x64_splithi_safe(X), _simd_ s32x64_splithi_safe(Y)))
//#ifdef _simd_s32x64_cmplt_
//	#define _simd_s32x64_cmplt(X,Y) _simd_s32x64_cmplt_(X, Y)
//	#define _simd_s32x64_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_cmplt_instruction_set>()
//#else
//	#define _simd_s32x64_cmplt(X,Y) _simd_s32x64_combine(\
//		_simd_s32x32_cmplt(_simd_s32x64_splitlo(X), _simd_s32x64_splitlo(Y)),\
//		_simd_s32x32_cmplt(_simd_s32x64_splithi(X), _simd_s32x64_splithi(Y)))
//	#define _simd_s32x64_cmplt_enable() (_simd_s32x32_cmplt_enable() && _simd_s32x64_combine_enable() && _simd_s32x64_splitlo_enable()  && _simd_s32x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x64_cmplt_) && ! defined(_simd_s32x64_cmplt_scalar_)
//	#define _simd_s32x64_cmplt_scalar_(X,Y) _simd_s32x64_cmplt_(X,_simd_s32x64_fill_scalar_(Y))
//	#define _simd_s32x64_cmplt_scalar_instruction_set _simd_s32x64_cmplt_instruction_set
//#endif
//#ifdef _simd_s32x64_cmplt_scalar_
//	#define _simd_s32x64_cmplt_scalar(X,Y) _simd_s32x64_cmplt_scalar_(X,Y)
//	#define _simd_s32x64_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_s32x64_cmplt_scalar(X,Y) _simd_s32x64_cmplt_safe(X,_simd_s32x64_fill_scalar_safe(Y))
//	#define _simd_s32x64_cmplt_scalar_enabled() true
//#endif
//
//// -- u32 --
//
//#ifndef _simd_u32x1_cmplt_safe
//	#define _simd_u32x1_cmplt_safe(X,Y) static_cast<_simd_u32x1>(X < Y)
//	#define _simd_u32x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_u32x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_cmplt_enabled() true
//#endif
//
//#define _simd_u32x2_cmplt_safe(X,Y)_simd_u32x2_combine_safe(\
//	_simd_u32x1_cmplt_safe(_simd_u32x2_splitlo_safe(X), _simd_ u32x2_splitlo_safe(Y)),\
//	_simd_u32x1_cmplt_safe(_simd_u32x2_splithi_safe(X), _simd_ u32x2_splithi_safe(Y)))
//#ifdef _simd_u32x2_cmplt_
//	#define _simd_u32x2_cmplt(X,Y) _simd_u32x2_cmplt_(X, Y)
//	#define _simd_u32x2_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_cmplt_instruction_set>()
//#elif defined(_simd_u32x4_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_cmplt(const register _simd_u32x2 x, const register _simd_u32x2 y) {
//		union SIMDUnion { _simd_u32x2 v1; _simd_u32x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x4_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x2_cmplt_enable() _simd_u32x4_cmplt_enable()
//#elif defined(_simd_u32x8_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_cmplt(const register _simd_u32x2 x, const register _simd_u32x2 y) {
//		union SIMDUnion { _simd_u32x2 v1; _simd_u32x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x8_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x2_cmplt_enable() _simd_u32x8_cmplt_enable()
//#elif defined(_simd_u32x16_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_cmplt(const register _simd_u32x2 x, const register _simd_u32x2 y) {
//		union SIMDUnion { _simd_u32x2 v1; _simd_u32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x16_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x2_cmplt_enable() _simd_u32x16_cmplt_enable()
//#elif defined(_simd_u32x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_cmplt(const register _simd_u32x2 x, const register _simd_u32x2 y) {
//		union SIMDUnion { _simd_u32x2 v1; _simd_u32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x2_cmplt_enable() _simd_u32x32_cmplt_enable()
//#elif defined(_simd_u32x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_cmplt(const register _simd_u32x2 x, const register _simd_u32x2 y) {
//		union SIMDUnion { _simd_u32x2 v1; _simd_u32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x2_cmplt_enable() _simd_u32x64_cmplt_enable()
//#else
//	#define _simd_u32x2_cmplt(X,Y) _simd_u32x2_combine(\
//		_simd_u32x1_cmplt(_simd_u32x2_splitlo(X), _simd_u32x2_splitlo(Y)),\
//		_simd_u32x1_cmplt(_simd_u32x2_splithi(X), _simd_u32x2_splithi(Y)))
//	#define _simd_u32x2_cmplt_enable() (_simd_u32x1_cmplt_enable() && _simd_u32x2_combine_enable() && _simd_u32x2_splitlo_enable()  && _simd_u32x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x2_cmplt_) && ! defined(_simd_u32x2_cmplt_scalar_)
//	#define _simd_u32x2_cmplt_scalar_(X,Y) _simd_u32x2_cmplt_(X,_simd_u32x2_fill_scalar_(Y))
//	#define _simd_u32x2_cmplt_scalar_instruction_set _simd_u32x2_cmplt_instruction_set
//#endif
//#ifdef _simd_u32x2_cmplt_scalar_
//	#define _simd_u32x2_cmplt_scalar(X,Y) _simd_u32x2_cmplt_scalar_(X,Y)
//	#define _simd_u32x2_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_u32x2_cmplt_scalar(X,Y) _simd_u32x2_cmplt_safe(X,_simd_u32x2_fill_scalar_safe(Y))
//	#define _simd_u32x2_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_u32x1_cmplt_safe
//	#define _simd_u32x1_cmplt_safe(X,Y) static_cast<_simd_u32x1>(X < Y)
//	#define _simd_u32x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_u32x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_cmplt_enabled() true
//#endif
//
//#define _simd_u32x4_cmplt_safe(X,Y)_simd_u32x4_combine_safe(\
//	_simd_u32x2_cmplt_safe(_simd_u32x4_splitlo_safe(X), _simd_ u32x4_splitlo_safe(Y)),\
//	_simd_u32x2_cmplt_safe(_simd_u32x4_splithi_safe(X), _simd_ u32x4_splithi_safe(Y)))
//#ifdef _simd_u32x4_cmplt_
//	#define _simd_u32x4_cmplt(X,Y) _simd_u32x4_cmplt_(X, Y)
//	#define _simd_u32x4_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_cmplt_instruction_set>()
//#elif defined(_simd_u32x8_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_cmplt(const register _simd_u32x4 x, const register _simd_u32x4 y) {
//		union SIMDUnion { _simd_u32x4 v1; _simd_u32x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x8_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x4_cmplt_enable() _simd_u32x8_cmplt_enable()
//#elif defined(_simd_u32x16_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_cmplt(const register _simd_u32x4 x, const register _simd_u32x4 y) {
//		union SIMDUnion { _simd_u32x4 v1; _simd_u32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x16_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x4_cmplt_enable() _simd_u32x16_cmplt_enable()
//#elif defined(_simd_u32x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_cmplt(const register _simd_u32x4 x, const register _simd_u32x4 y) {
//		union SIMDUnion { _simd_u32x4 v1; _simd_u32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x4_cmplt_enable() _simd_u32x32_cmplt_enable()
//#elif defined(_simd_u32x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_cmplt(const register _simd_u32x4 x, const register _simd_u32x4 y) {
//		union SIMDUnion { _simd_u32x4 v1; _simd_u32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x4_cmplt_enable() _simd_u32x64_cmplt_enable()
//#else
//	#define _simd_u32x4_cmplt(X,Y) _simd_u32x4_combine(\
//		_simd_u32x2_cmplt(_simd_u32x4_splitlo(X), _simd_u32x4_splitlo(Y)),\
//		_simd_u32x2_cmplt(_simd_u32x4_splithi(X), _simd_u32x4_splithi(Y)))
//	#define _simd_u32x4_cmplt_enable() (_simd_u32x2_cmplt_enable() && _simd_u32x4_combine_enable() && _simd_u32x4_splitlo_enable()  && _simd_u32x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x4_cmplt_) && ! defined(_simd_u32x4_cmplt_scalar_)
//	#define _simd_u32x4_cmplt_scalar_(X,Y) _simd_u32x4_cmplt_(X,_simd_u32x4_fill_scalar_(Y))
//	#define _simd_u32x4_cmplt_scalar_instruction_set _simd_u32x4_cmplt_instruction_set
//#endif
//#ifdef _simd_u32x4_cmplt_scalar_
//	#define _simd_u32x4_cmplt_scalar(X,Y) _simd_u32x4_cmplt_scalar_(X,Y)
//	#define _simd_u32x4_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_u32x4_cmplt_scalar(X,Y) _simd_u32x4_cmplt_safe(X,_simd_u32x4_fill_scalar_safe(Y))
//	#define _simd_u32x4_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_u32x1_cmplt_safe
//	#define _simd_u32x1_cmplt_safe(X,Y) static_cast<_simd_u32x1>(X < Y)
//	#define _simd_u32x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_u32x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_cmplt_enabled() true
//#endif
//
//#define _simd_u32x8_cmplt_safe(X,Y)_simd_u32x8_combine_safe(\
//	_simd_u32x4_cmplt_safe(_simd_u32x8_splitlo_safe(X), _simd_ u32x8_splitlo_safe(Y)),\
//	_simd_u32x4_cmplt_safe(_simd_u32x8_splithi_safe(X), _simd_ u32x8_splithi_safe(Y)))
//#ifdef _simd_u32x8_cmplt_
//	#define _simd_u32x8_cmplt(X,Y) _simd_u32x8_cmplt_(X, Y)
//	#define _simd_u32x8_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_cmplt_instruction_set>()
//#elif defined(_simd_u32x16_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u32x8 ANVIL_SIMD_CALL _simd_u32x8_cmplt(const register _simd_u32x8 x, const register _simd_u32x8 y) {
//		union SIMDUnion { _simd_u32x8 v1; _simd_u32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x16_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x8_cmplt_enable() _simd_u32x16_cmplt_enable()
//#elif defined(_simd_u32x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u32x8 ANVIL_SIMD_CALL _simd_u32x8_cmplt(const register _simd_u32x8 x, const register _simd_u32x8 y) {
//		union SIMDUnion { _simd_u32x8 v1; _simd_u32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x8_cmplt_enable() _simd_u32x32_cmplt_enable()
//#elif defined(_simd_u32x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u32x8 ANVIL_SIMD_CALL _simd_u32x8_cmplt(const register _simd_u32x8 x, const register _simd_u32x8 y) {
//		union SIMDUnion { _simd_u32x8 v1; _simd_u32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x8_cmplt_enable() _simd_u32x64_cmplt_enable()
//#else
//	#define _simd_u32x8_cmplt(X,Y) _simd_u32x8_combine(\
//		_simd_u32x4_cmplt(_simd_u32x8_splitlo(X), _simd_u32x8_splitlo(Y)),\
//		_simd_u32x4_cmplt(_simd_u32x8_splithi(X), _simd_u32x8_splithi(Y)))
//	#define _simd_u32x8_cmplt_enable() (_simd_u32x4_cmplt_enable() && _simd_u32x8_combine_enable() && _simd_u32x8_splitlo_enable()  && _simd_u32x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x8_cmplt_) && ! defined(_simd_u32x8_cmplt_scalar_)
//	#define _simd_u32x8_cmplt_scalar_(X,Y) _simd_u32x8_cmplt_(X,_simd_u32x8_fill_scalar_(Y))
//	#define _simd_u32x8_cmplt_scalar_instruction_set _simd_u32x8_cmplt_instruction_set
//#endif
//#ifdef _simd_u32x8_cmplt_scalar_
//	#define _simd_u32x8_cmplt_scalar(X,Y) _simd_u32x8_cmplt_scalar_(X,Y)
//	#define _simd_u32x8_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_u32x8_cmplt_scalar(X,Y) _simd_u32x8_cmplt_safe(X,_simd_u32x8_fill_scalar_safe(Y))
//	#define _simd_u32x8_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_u32x1_cmplt_safe
//	#define _simd_u32x1_cmplt_safe(X,Y) static_cast<_simd_u32x1>(X < Y)
//	#define _simd_u32x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_u32x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_cmplt_enabled() true
//#endif
//
//#define _simd_u32x16_cmplt_safe(X,Y)_simd_u32x16_combine_safe(\
//	_simd_u32x8_cmplt_safe(_simd_u32x16_splitlo_safe(X), _simd_ u32x16_splitlo_safe(Y)),\
//	_simd_u32x8_cmplt_safe(_simd_u32x16_splithi_safe(X), _simd_ u32x16_splithi_safe(Y)))
//#ifdef _simd_u32x16_cmplt_
//	#define _simd_u32x16_cmplt(X,Y) _simd_u32x16_cmplt_(X, Y)
//	#define _simd_u32x16_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_cmplt_instruction_set>()
//#elif defined(_simd_u32x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u32x16 ANVIL_SIMD_CALL _simd_u32x16_cmplt(const register _simd_u32x16 x, const register _simd_u32x16 y) {
//		union SIMDUnion { _simd_u32x16 v1; _simd_u32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x16_cmplt_enable() _simd_u32x32_cmplt_enable()
//#elif defined(_simd_u32x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u32x16 ANVIL_SIMD_CALL _simd_u32x16_cmplt(const register _simd_u32x16 x, const register _simd_u32x16 y) {
//		union SIMDUnion { _simd_u32x16 v1; _simd_u32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x16_cmplt_enable() _simd_u32x64_cmplt_enable()
//#else
//	#define _simd_u32x16_cmplt(X,Y) _simd_u32x16_combine(\
//		_simd_u32x8_cmplt(_simd_u32x16_splitlo(X), _simd_u32x16_splitlo(Y)),\
//		_simd_u32x8_cmplt(_simd_u32x16_splithi(X), _simd_u32x16_splithi(Y)))
//	#define _simd_u32x16_cmplt_enable() (_simd_u32x8_cmplt_enable() && _simd_u32x16_combine_enable() && _simd_u32x16_splitlo_enable()  && _simd_u32x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x16_cmplt_) && ! defined(_simd_u32x16_cmplt_scalar_)
//	#define _simd_u32x16_cmplt_scalar_(X,Y) _simd_u32x16_cmplt_(X,_simd_u32x16_fill_scalar_(Y))
//	#define _simd_u32x16_cmplt_scalar_instruction_set _simd_u32x16_cmplt_instruction_set
//#endif
//#ifdef _simd_u32x16_cmplt_scalar_
//	#define _simd_u32x16_cmplt_scalar(X,Y) _simd_u32x16_cmplt_scalar_(X,Y)
//	#define _simd_u32x16_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_u32x16_cmplt_scalar(X,Y) _simd_u32x16_cmplt_safe(X,_simd_u32x16_fill_scalar_safe(Y))
//	#define _simd_u32x16_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_u32x1_cmplt_safe
//	#define _simd_u32x1_cmplt_safe(X,Y) static_cast<_simd_u32x1>(X < Y)
//	#define _simd_u32x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_u32x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_cmplt_enabled() true
//#endif
//
//#define _simd_u32x32_cmplt_safe(X,Y)_simd_u32x32_combine_safe(\
//	_simd_u32x16_cmplt_safe(_simd_u32x32_splitlo_safe(X), _simd_ u32x32_splitlo_safe(Y)),\
//	_simd_u32x16_cmplt_safe(_simd_u32x32_splithi_safe(X), _simd_ u32x32_splithi_safe(Y)))
//#ifdef _simd_u32x32_cmplt_
//	#define _simd_u32x32_cmplt(X,Y) _simd_u32x32_cmplt_(X, Y)
//	#define _simd_u32x32_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_cmplt_instruction_set>()
//#elif defined(_simd_u32x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u32x32 ANVIL_SIMD_CALL _simd_u32x32_cmplt(const register _simd_u32x32 x, const register _simd_u32x32 y) {
//		union SIMDUnion { _simd_u32x32 v1; _simd_u32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x32_cmplt_enable() _simd_u32x64_cmplt_enable()
//#else
//	#define _simd_u32x32_cmplt(X,Y) _simd_u32x32_combine(\
//		_simd_u32x16_cmplt(_simd_u32x32_splitlo(X), _simd_u32x32_splitlo(Y)),\
//		_simd_u32x16_cmplt(_simd_u32x32_splithi(X), _simd_u32x32_splithi(Y)))
//	#define _simd_u32x32_cmplt_enable() (_simd_u32x16_cmplt_enable() && _simd_u32x32_combine_enable() && _simd_u32x32_splitlo_enable()  && _simd_u32x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x32_cmplt_) && ! defined(_simd_u32x32_cmplt_scalar_)
//	#define _simd_u32x32_cmplt_scalar_(X,Y) _simd_u32x32_cmplt_(X,_simd_u32x32_fill_scalar_(Y))
//	#define _simd_u32x32_cmplt_scalar_instruction_set _simd_u32x32_cmplt_instruction_set
//#endif
//#ifdef _simd_u32x32_cmplt_scalar_
//	#define _simd_u32x32_cmplt_scalar(X,Y) _simd_u32x32_cmplt_scalar_(X,Y)
//	#define _simd_u32x32_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_u32x32_cmplt_scalar(X,Y) _simd_u32x32_cmplt_safe(X,_simd_u32x32_fill_scalar_safe(Y))
//	#define _simd_u32x32_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_u32x1_cmplt_safe
//	#define _simd_u32x1_cmplt_safe(X,Y) static_cast<_simd_u32x1>(X < Y)
//	#define _simd_u32x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_u32x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_cmplt_enabled() true
//#endif
//
//#define _simd_u32x64_cmplt_safe(X,Y)_simd_u32x64_combine_safe(\
//	_simd_u32x32_cmplt_safe(_simd_u32x64_splitlo_safe(X), _simd_ u32x64_splitlo_safe(Y)),\
//	_simd_u32x32_cmplt_safe(_simd_u32x64_splithi_safe(X), _simd_ u32x64_splithi_safe(Y)))
//#ifdef _simd_u32x64_cmplt_
//	#define _simd_u32x64_cmplt(X,Y) _simd_u32x64_cmplt_(X, Y)
//	#define _simd_u32x64_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_cmplt_instruction_set>()
//#else
//	#define _simd_u32x64_cmplt(X,Y) _simd_u32x64_combine(\
//		_simd_u32x32_cmplt(_simd_u32x64_splitlo(X), _simd_u32x64_splitlo(Y)),\
//		_simd_u32x32_cmplt(_simd_u32x64_splithi(X), _simd_u32x64_splithi(Y)))
//	#define _simd_u32x64_cmplt_enable() (_simd_u32x32_cmplt_enable() && _simd_u32x64_combine_enable() && _simd_u32x64_splitlo_enable()  && _simd_u32x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x64_cmplt_) && ! defined(_simd_u32x64_cmplt_scalar_)
//	#define _simd_u32x64_cmplt_scalar_(X,Y) _simd_u32x64_cmplt_(X,_simd_u32x64_fill_scalar_(Y))
//	#define _simd_u32x64_cmplt_scalar_instruction_set _simd_u32x64_cmplt_instruction_set
//#endif
//#ifdef _simd_u32x64_cmplt_scalar_
//	#define _simd_u32x64_cmplt_scalar(X,Y) _simd_u32x64_cmplt_scalar_(X,Y)
//	#define _simd_u32x64_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_u32x64_cmplt_scalar(X,Y) _simd_u32x64_cmplt_safe(X,_simd_u32x64_fill_scalar_safe(Y))
//	#define _simd_u32x64_cmplt_scalar_enabled() true
//#endif
//
//// -- s16 --
//
//#ifndef _simd_s16x1_cmplt_safe
//	#define _simd_s16x1_cmplt_safe(X,Y) static_cast<_simd_s16x1>(X < Y)
//	#define _simd_s16x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_s16x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_cmplt_enabled() true
//#endif
//
//#define _simd_s16x2_cmplt_safe(X,Y)_simd_s16x2_combine_safe(\
//	_simd_s16x1_cmplt_safe(_simd_s16x2_splitlo_safe(X), _simd_ s16x2_splitlo_safe(Y)),\
//	_simd_s16x1_cmplt_safe(_simd_s16x2_splithi_safe(X), _simd_ s16x2_splithi_safe(Y)))
//#ifdef _simd_s16x2_cmplt_
//	#define _simd_s16x2_cmplt(X,Y) _simd_s16x2_cmplt_(X, Y)
//	#define _simd_s16x2_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_cmplt_instruction_set>()
//#elif defined(_simd_s16x4_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_cmplt(const register _simd_s16x2 x, const register _simd_s16x2 y) {
//		union SIMDUnion { _simd_s16x2 v1; _simd_s16x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x4_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x2_cmplt_enable() _simd_s16x4_cmplt_enable()
//#elif defined(_simd_s16x8_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_cmplt(const register _simd_s16x2 x, const register _simd_s16x2 y) {
//		union SIMDUnion { _simd_s16x2 v1; _simd_s16x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x8_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x2_cmplt_enable() _simd_s16x8_cmplt_enable()
//#elif defined(_simd_s16x16_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_cmplt(const register _simd_s16x2 x, const register _simd_s16x2 y) {
//		union SIMDUnion { _simd_s16x2 v1; _simd_s16x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x16_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x2_cmplt_enable() _simd_s16x16_cmplt_enable()
//#elif defined(_simd_s16x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_cmplt(const register _simd_s16x2 x, const register _simd_s16x2 y) {
//		union SIMDUnion { _simd_s16x2 v1; _simd_s16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x2_cmplt_enable() _simd_s16x32_cmplt_enable()
//#elif defined(_simd_s16x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_cmplt(const register _simd_s16x2 x, const register _simd_s16x2 y) {
//		union SIMDUnion { _simd_s16x2 v1; _simd_s16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x2_cmplt_enable() _simd_s16x64_cmplt_enable()
//#else
//	#define _simd_s16x2_cmplt(X,Y) _simd_s16x2_combine(\
//		_simd_s16x1_cmplt(_simd_s16x2_splitlo(X), _simd_s16x2_splitlo(Y)),\
//		_simd_s16x1_cmplt(_simd_s16x2_splithi(X), _simd_s16x2_splithi(Y)))
//	#define _simd_s16x2_cmplt_enable() (_simd_s16x1_cmplt_enable() && _simd_s16x2_combine_enable() && _simd_s16x2_splitlo_enable()  && _simd_s16x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x2_cmplt_) && ! defined(_simd_s16x2_cmplt_scalar_)
//	#define _simd_s16x2_cmplt_scalar_(X,Y) _simd_s16x2_cmplt_(X,_simd_s16x2_fill_scalar_(Y))
//	#define _simd_s16x2_cmplt_scalar_instruction_set _simd_s16x2_cmplt_instruction_set
//#endif
//#ifdef _simd_s16x2_cmplt_scalar_
//	#define _simd_s16x2_cmplt_scalar(X,Y) _simd_s16x2_cmplt_scalar_(X,Y)
//	#define _simd_s16x2_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_s16x2_cmplt_scalar(X,Y) _simd_s16x2_cmplt_safe(X,_simd_s16x2_fill_scalar_safe(Y))
//	#define _simd_s16x2_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_s16x1_cmplt_safe
//	#define _simd_s16x1_cmplt_safe(X,Y) static_cast<_simd_s16x1>(X < Y)
//	#define _simd_s16x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_s16x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_cmplt_enabled() true
//#endif
//
//#define _simd_s16x4_cmplt_safe(X,Y)_simd_s16x4_combine_safe(\
//	_simd_s16x2_cmplt_safe(_simd_s16x4_splitlo_safe(X), _simd_ s16x4_splitlo_safe(Y)),\
//	_simd_s16x2_cmplt_safe(_simd_s16x4_splithi_safe(X), _simd_ s16x4_splithi_safe(Y)))
//#ifdef _simd_s16x4_cmplt_
//	#define _simd_s16x4_cmplt(X,Y) _simd_s16x4_cmplt_(X, Y)
//	#define _simd_s16x4_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_cmplt_instruction_set>()
//#elif defined(_simd_s16x8_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_cmplt(const register _simd_s16x4 x, const register _simd_s16x4 y) {
//		union SIMDUnion { _simd_s16x4 v1; _simd_s16x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x8_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x4_cmplt_enable() _simd_s16x8_cmplt_enable()
//#elif defined(_simd_s16x16_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_cmplt(const register _simd_s16x4 x, const register _simd_s16x4 y) {
//		union SIMDUnion { _simd_s16x4 v1; _simd_s16x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x16_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x4_cmplt_enable() _simd_s16x16_cmplt_enable()
//#elif defined(_simd_s16x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_cmplt(const register _simd_s16x4 x, const register _simd_s16x4 y) {
//		union SIMDUnion { _simd_s16x4 v1; _simd_s16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x4_cmplt_enable() _simd_s16x32_cmplt_enable()
//#elif defined(_simd_s16x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_cmplt(const register _simd_s16x4 x, const register _simd_s16x4 y) {
//		union SIMDUnion { _simd_s16x4 v1; _simd_s16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x4_cmplt_enable() _simd_s16x64_cmplt_enable()
//#else
//	#define _simd_s16x4_cmplt(X,Y) _simd_s16x4_combine(\
//		_simd_s16x2_cmplt(_simd_s16x4_splitlo(X), _simd_s16x4_splitlo(Y)),\
//		_simd_s16x2_cmplt(_simd_s16x4_splithi(X), _simd_s16x4_splithi(Y)))
//	#define _simd_s16x4_cmplt_enable() (_simd_s16x2_cmplt_enable() && _simd_s16x4_combine_enable() && _simd_s16x4_splitlo_enable()  && _simd_s16x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x4_cmplt_) && ! defined(_simd_s16x4_cmplt_scalar_)
//	#define _simd_s16x4_cmplt_scalar_(X,Y) _simd_s16x4_cmplt_(X,_simd_s16x4_fill_scalar_(Y))
//	#define _simd_s16x4_cmplt_scalar_instruction_set _simd_s16x4_cmplt_instruction_set
//#endif
//#ifdef _simd_s16x4_cmplt_scalar_
//	#define _simd_s16x4_cmplt_scalar(X,Y) _simd_s16x4_cmplt_scalar_(X,Y)
//	#define _simd_s16x4_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_s16x4_cmplt_scalar(X,Y) _simd_s16x4_cmplt_safe(X,_simd_s16x4_fill_scalar_safe(Y))
//	#define _simd_s16x4_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_s16x1_cmplt_safe
//	#define _simd_s16x1_cmplt_safe(X,Y) static_cast<_simd_s16x1>(X < Y)
//	#define _simd_s16x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_s16x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_cmplt_enabled() true
//#endif
//
//#define _simd_s16x8_cmplt_safe(X,Y)_simd_s16x8_combine_safe(\
//	_simd_s16x4_cmplt_safe(_simd_s16x8_splitlo_safe(X), _simd_ s16x8_splitlo_safe(Y)),\
//	_simd_s16x4_cmplt_safe(_simd_s16x8_splithi_safe(X), _simd_ s16x8_splithi_safe(Y)))
//#ifdef _simd_s16x8_cmplt_
//	#define _simd_s16x8_cmplt(X,Y) _simd_s16x8_cmplt_(X, Y)
//	#define _simd_s16x8_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_cmplt_instruction_set>()
//#elif defined(_simd_s16x16_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s16x8 ANVIL_SIMD_CALL _simd_s16x8_cmplt(const register _simd_s16x8 x, const register _simd_s16x8 y) {
//		union SIMDUnion { _simd_s16x8 v1; _simd_s16x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x16_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x8_cmplt_enable() _simd_s16x16_cmplt_enable()
//#elif defined(_simd_s16x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s16x8 ANVIL_SIMD_CALL _simd_s16x8_cmplt(const register _simd_s16x8 x, const register _simd_s16x8 y) {
//		union SIMDUnion { _simd_s16x8 v1; _simd_s16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x8_cmplt_enable() _simd_s16x32_cmplt_enable()
//#elif defined(_simd_s16x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s16x8 ANVIL_SIMD_CALL _simd_s16x8_cmplt(const register _simd_s16x8 x, const register _simd_s16x8 y) {
//		union SIMDUnion { _simd_s16x8 v1; _simd_s16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x8_cmplt_enable() _simd_s16x64_cmplt_enable()
//#else
//	#define _simd_s16x8_cmplt(X,Y) _simd_s16x8_combine(\
//		_simd_s16x4_cmplt(_simd_s16x8_splitlo(X), _simd_s16x8_splitlo(Y)),\
//		_simd_s16x4_cmplt(_simd_s16x8_splithi(X), _simd_s16x8_splithi(Y)))
//	#define _simd_s16x8_cmplt_enable() (_simd_s16x4_cmplt_enable() && _simd_s16x8_combine_enable() && _simd_s16x8_splitlo_enable()  && _simd_s16x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x8_cmplt_) && ! defined(_simd_s16x8_cmplt_scalar_)
//	#define _simd_s16x8_cmplt_scalar_(X,Y) _simd_s16x8_cmplt_(X,_simd_s16x8_fill_scalar_(Y))
//	#define _simd_s16x8_cmplt_scalar_instruction_set _simd_s16x8_cmplt_instruction_set
//#endif
//#ifdef _simd_s16x8_cmplt_scalar_
//	#define _simd_s16x8_cmplt_scalar(X,Y) _simd_s16x8_cmplt_scalar_(X,Y)
//	#define _simd_s16x8_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_s16x8_cmplt_scalar(X,Y) _simd_s16x8_cmplt_safe(X,_simd_s16x8_fill_scalar_safe(Y))
//	#define _simd_s16x8_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_s16x1_cmplt_safe
//	#define _simd_s16x1_cmplt_safe(X,Y) static_cast<_simd_s16x1>(X < Y)
//	#define _simd_s16x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_s16x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_cmplt_enabled() true
//#endif
//
//#define _simd_s16x16_cmplt_safe(X,Y)_simd_s16x16_combine_safe(\
//	_simd_s16x8_cmplt_safe(_simd_s16x16_splitlo_safe(X), _simd_ s16x16_splitlo_safe(Y)),\
//	_simd_s16x8_cmplt_safe(_simd_s16x16_splithi_safe(X), _simd_ s16x16_splithi_safe(Y)))
//#ifdef _simd_s16x16_cmplt_
//	#define _simd_s16x16_cmplt(X,Y) _simd_s16x16_cmplt_(X, Y)
//	#define _simd_s16x16_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_cmplt_instruction_set>()
//#elif defined(_simd_s16x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s16x16 ANVIL_SIMD_CALL _simd_s16x16_cmplt(const register _simd_s16x16 x, const register _simd_s16x16 y) {
//		union SIMDUnion { _simd_s16x16 v1; _simd_s16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x16_cmplt_enable() _simd_s16x32_cmplt_enable()
//#elif defined(_simd_s16x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s16x16 ANVIL_SIMD_CALL _simd_s16x16_cmplt(const register _simd_s16x16 x, const register _simd_s16x16 y) {
//		union SIMDUnion { _simd_s16x16 v1; _simd_s16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x16_cmplt_enable() _simd_s16x64_cmplt_enable()
//#else
//	#define _simd_s16x16_cmplt(X,Y) _simd_s16x16_combine(\
//		_simd_s16x8_cmplt(_simd_s16x16_splitlo(X), _simd_s16x16_splitlo(Y)),\
//		_simd_s16x8_cmplt(_simd_s16x16_splithi(X), _simd_s16x16_splithi(Y)))
//	#define _simd_s16x16_cmplt_enable() (_simd_s16x8_cmplt_enable() && _simd_s16x16_combine_enable() && _simd_s16x16_splitlo_enable()  && _simd_s16x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x16_cmplt_) && ! defined(_simd_s16x16_cmplt_scalar_)
//	#define _simd_s16x16_cmplt_scalar_(X,Y) _simd_s16x16_cmplt_(X,_simd_s16x16_fill_scalar_(Y))
//	#define _simd_s16x16_cmplt_scalar_instruction_set _simd_s16x16_cmplt_instruction_set
//#endif
//#ifdef _simd_s16x16_cmplt_scalar_
//	#define _simd_s16x16_cmplt_scalar(X,Y) _simd_s16x16_cmplt_scalar_(X,Y)
//	#define _simd_s16x16_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_s16x16_cmplt_scalar(X,Y) _simd_s16x16_cmplt_safe(X,_simd_s16x16_fill_scalar_safe(Y))
//	#define _simd_s16x16_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_s16x1_cmplt_safe
//	#define _simd_s16x1_cmplt_safe(X,Y) static_cast<_simd_s16x1>(X < Y)
//	#define _simd_s16x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_s16x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_cmplt_enabled() true
//#endif
//
//#define _simd_s16x32_cmplt_safe(X,Y)_simd_s16x32_combine_safe(\
//	_simd_s16x16_cmplt_safe(_simd_s16x32_splitlo_safe(X), _simd_ s16x32_splitlo_safe(Y)),\
//	_simd_s16x16_cmplt_safe(_simd_s16x32_splithi_safe(X), _simd_ s16x32_splithi_safe(Y)))
//#ifdef _simd_s16x32_cmplt_
//	#define _simd_s16x32_cmplt(X,Y) _simd_s16x32_cmplt_(X, Y)
//	#define _simd_s16x32_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_cmplt_instruction_set>()
//#elif defined(_simd_s16x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s16x32 ANVIL_SIMD_CALL _simd_s16x32_cmplt(const register _simd_s16x32 x, const register _simd_s16x32 y) {
//		union SIMDUnion { _simd_s16x32 v1; _simd_s16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x32_cmplt_enable() _simd_s16x64_cmplt_enable()
//#else
//	#define _simd_s16x32_cmplt(X,Y) _simd_s16x32_combine(\
//		_simd_s16x16_cmplt(_simd_s16x32_splitlo(X), _simd_s16x32_splitlo(Y)),\
//		_simd_s16x16_cmplt(_simd_s16x32_splithi(X), _simd_s16x32_splithi(Y)))
//	#define _simd_s16x32_cmplt_enable() (_simd_s16x16_cmplt_enable() && _simd_s16x32_combine_enable() && _simd_s16x32_splitlo_enable()  && _simd_s16x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x32_cmplt_) && ! defined(_simd_s16x32_cmplt_scalar_)
//	#define _simd_s16x32_cmplt_scalar_(X,Y) _simd_s16x32_cmplt_(X,_simd_s16x32_fill_scalar_(Y))
//	#define _simd_s16x32_cmplt_scalar_instruction_set _simd_s16x32_cmplt_instruction_set
//#endif
//#ifdef _simd_s16x32_cmplt_scalar_
//	#define _simd_s16x32_cmplt_scalar(X,Y) _simd_s16x32_cmplt_scalar_(X,Y)
//	#define _simd_s16x32_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_s16x32_cmplt_scalar(X,Y) _simd_s16x32_cmplt_safe(X,_simd_s16x32_fill_scalar_safe(Y))
//	#define _simd_s16x32_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_s16x1_cmplt_safe
//	#define _simd_s16x1_cmplt_safe(X,Y) static_cast<_simd_s16x1>(X < Y)
//	#define _simd_s16x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_s16x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_cmplt_enabled() true
//#endif
//
//#define _simd_s16x64_cmplt_safe(X,Y)_simd_s16x64_combine_safe(\
//	_simd_s16x32_cmplt_safe(_simd_s16x64_splitlo_safe(X), _simd_ s16x64_splitlo_safe(Y)),\
//	_simd_s16x32_cmplt_safe(_simd_s16x64_splithi_safe(X), _simd_ s16x64_splithi_safe(Y)))
//#ifdef _simd_s16x64_cmplt_
//	#define _simd_s16x64_cmplt(X,Y) _simd_s16x64_cmplt_(X, Y)
//	#define _simd_s16x64_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_cmplt_instruction_set>()
//#else
//	#define _simd_s16x64_cmplt(X,Y) _simd_s16x64_combine(\
//		_simd_s16x32_cmplt(_simd_s16x64_splitlo(X), _simd_s16x64_splitlo(Y)),\
//		_simd_s16x32_cmplt(_simd_s16x64_splithi(X), _simd_s16x64_splithi(Y)))
//	#define _simd_s16x64_cmplt_enable() (_simd_s16x32_cmplt_enable() && _simd_s16x64_combine_enable() && _simd_s16x64_splitlo_enable()  && _simd_s16x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x64_cmplt_) && ! defined(_simd_s16x64_cmplt_scalar_)
//	#define _simd_s16x64_cmplt_scalar_(X,Y) _simd_s16x64_cmplt_(X,_simd_s16x64_fill_scalar_(Y))
//	#define _simd_s16x64_cmplt_scalar_instruction_set _simd_s16x64_cmplt_instruction_set
//#endif
//#ifdef _simd_s16x64_cmplt_scalar_
//	#define _simd_s16x64_cmplt_scalar(X,Y) _simd_s16x64_cmplt_scalar_(X,Y)
//	#define _simd_s16x64_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_s16x64_cmplt_scalar(X,Y) _simd_s16x64_cmplt_safe(X,_simd_s16x64_fill_scalar_safe(Y))
//	#define _simd_s16x64_cmplt_scalar_enabled() true
//#endif
//
//// -- u16 --
//
//#ifndef _simd_u16x1_cmplt_safe
//	#define _simd_u16x1_cmplt_safe(X,Y) static_cast<_simd_u16x1>(X < Y)
//	#define _simd_u16x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_u16x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_cmplt_enabled() true
//#endif
//
//#define _simd_u16x2_cmplt_safe(X,Y)_simd_u16x2_combine_safe(\
//	_simd_u16x1_cmplt_safe(_simd_u16x2_splitlo_safe(X), _simd_ u16x2_splitlo_safe(Y)),\
//	_simd_u16x1_cmplt_safe(_simd_u16x2_splithi_safe(X), _simd_ u16x2_splithi_safe(Y)))
//#ifdef _simd_u16x2_cmplt_
//	#define _simd_u16x2_cmplt(X,Y) _simd_u16x2_cmplt_(X, Y)
//	#define _simd_u16x2_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_cmplt_instruction_set>()
//#elif defined(_simd_u16x4_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_cmplt(const register _simd_u16x2 x, const register _simd_u16x2 y) {
//		union SIMDUnion { _simd_u16x2 v1; _simd_u16x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x4_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x2_cmplt_enable() _simd_u16x4_cmplt_enable()
//#elif defined(_simd_u16x8_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_cmplt(const register _simd_u16x2 x, const register _simd_u16x2 y) {
//		union SIMDUnion { _simd_u16x2 v1; _simd_u16x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x8_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x2_cmplt_enable() _simd_u16x8_cmplt_enable()
//#elif defined(_simd_u16x16_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_cmplt(const register _simd_u16x2 x, const register _simd_u16x2 y) {
//		union SIMDUnion { _simd_u16x2 v1; _simd_u16x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x16_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x2_cmplt_enable() _simd_u16x16_cmplt_enable()
//#elif defined(_simd_u16x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_cmplt(const register _simd_u16x2 x, const register _simd_u16x2 y) {
//		union SIMDUnion { _simd_u16x2 v1; _simd_u16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x2_cmplt_enable() _simd_u16x32_cmplt_enable()
//#elif defined(_simd_u16x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_cmplt(const register _simd_u16x2 x, const register _simd_u16x2 y) {
//		union SIMDUnion { _simd_u16x2 v1; _simd_u16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x2_cmplt_enable() _simd_u16x64_cmplt_enable()
//#else
//	#define _simd_u16x2_cmplt(X,Y) _simd_u16x2_combine(\
//		_simd_u16x1_cmplt(_simd_u16x2_splitlo(X), _simd_u16x2_splitlo(Y)),\
//		_simd_u16x1_cmplt(_simd_u16x2_splithi(X), _simd_u16x2_splithi(Y)))
//	#define _simd_u16x2_cmplt_enable() (_simd_u16x1_cmplt_enable() && _simd_u16x2_combine_enable() && _simd_u16x2_splitlo_enable()  && _simd_u16x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x2_cmplt_) && ! defined(_simd_u16x2_cmplt_scalar_)
//	#define _simd_u16x2_cmplt_scalar_(X,Y) _simd_u16x2_cmplt_(X,_simd_u16x2_fill_scalar_(Y))
//	#define _simd_u16x2_cmplt_scalar_instruction_set _simd_u16x2_cmplt_instruction_set
//#endif
//#ifdef _simd_u16x2_cmplt_scalar_
//	#define _simd_u16x2_cmplt_scalar(X,Y) _simd_u16x2_cmplt_scalar_(X,Y)
//	#define _simd_u16x2_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_u16x2_cmplt_scalar(X,Y) _simd_u16x2_cmplt_safe(X,_simd_u16x2_fill_scalar_safe(Y))
//	#define _simd_u16x2_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_u16x1_cmplt_safe
//	#define _simd_u16x1_cmplt_safe(X,Y) static_cast<_simd_u16x1>(X < Y)
//	#define _simd_u16x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_u16x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_cmplt_enabled() true
//#endif
//
//#define _simd_u16x4_cmplt_safe(X,Y)_simd_u16x4_combine_safe(\
//	_simd_u16x2_cmplt_safe(_simd_u16x4_splitlo_safe(X), _simd_ u16x4_splitlo_safe(Y)),\
//	_simd_u16x2_cmplt_safe(_simd_u16x4_splithi_safe(X), _simd_ u16x4_splithi_safe(Y)))
//#ifdef _simd_u16x4_cmplt_
//	#define _simd_u16x4_cmplt(X,Y) _simd_u16x4_cmplt_(X, Y)
//	#define _simd_u16x4_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_cmplt_instruction_set>()
//#elif defined(_simd_u16x8_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_cmplt(const register _simd_u16x4 x, const register _simd_u16x4 y) {
//		union SIMDUnion { _simd_u16x4 v1; _simd_u16x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x8_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x4_cmplt_enable() _simd_u16x8_cmplt_enable()
//#elif defined(_simd_u16x16_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_cmplt(const register _simd_u16x4 x, const register _simd_u16x4 y) {
//		union SIMDUnion { _simd_u16x4 v1; _simd_u16x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x16_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x4_cmplt_enable() _simd_u16x16_cmplt_enable()
//#elif defined(_simd_u16x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_cmplt(const register _simd_u16x4 x, const register _simd_u16x4 y) {
//		union SIMDUnion { _simd_u16x4 v1; _simd_u16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x4_cmplt_enable() _simd_u16x32_cmplt_enable()
//#elif defined(_simd_u16x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_cmplt(const register _simd_u16x4 x, const register _simd_u16x4 y) {
//		union SIMDUnion { _simd_u16x4 v1; _simd_u16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x4_cmplt_enable() _simd_u16x64_cmplt_enable()
//#else
//	#define _simd_u16x4_cmplt(X,Y) _simd_u16x4_combine(\
//		_simd_u16x2_cmplt(_simd_u16x4_splitlo(X), _simd_u16x4_splitlo(Y)),\
//		_simd_u16x2_cmplt(_simd_u16x4_splithi(X), _simd_u16x4_splithi(Y)))
//	#define _simd_u16x4_cmplt_enable() (_simd_u16x2_cmplt_enable() && _simd_u16x4_combine_enable() && _simd_u16x4_splitlo_enable()  && _simd_u16x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x4_cmplt_) && ! defined(_simd_u16x4_cmplt_scalar_)
//	#define _simd_u16x4_cmplt_scalar_(X,Y) _simd_u16x4_cmplt_(X,_simd_u16x4_fill_scalar_(Y))
//	#define _simd_u16x4_cmplt_scalar_instruction_set _simd_u16x4_cmplt_instruction_set
//#endif
//#ifdef _simd_u16x4_cmplt_scalar_
//	#define _simd_u16x4_cmplt_scalar(X,Y) _simd_u16x4_cmplt_scalar_(X,Y)
//	#define _simd_u16x4_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_u16x4_cmplt_scalar(X,Y) _simd_u16x4_cmplt_safe(X,_simd_u16x4_fill_scalar_safe(Y))
//	#define _simd_u16x4_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_u16x1_cmplt_safe
//	#define _simd_u16x1_cmplt_safe(X,Y) static_cast<_simd_u16x1>(X < Y)
//	#define _simd_u16x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_u16x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_cmplt_enabled() true
//#endif
//
//#define _simd_u16x8_cmplt_safe(X,Y)_simd_u16x8_combine_safe(\
//	_simd_u16x4_cmplt_safe(_simd_u16x8_splitlo_safe(X), _simd_ u16x8_splitlo_safe(Y)),\
//	_simd_u16x4_cmplt_safe(_simd_u16x8_splithi_safe(X), _simd_ u16x8_splithi_safe(Y)))
//#ifdef _simd_u16x8_cmplt_
//	#define _simd_u16x8_cmplt(X,Y) _simd_u16x8_cmplt_(X, Y)
//	#define _simd_u16x8_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_cmplt_instruction_set>()
//#elif defined(_simd_u16x16_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u16x8 ANVIL_SIMD_CALL _simd_u16x8_cmplt(const register _simd_u16x8 x, const register _simd_u16x8 y) {
//		union SIMDUnion { _simd_u16x8 v1; _simd_u16x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x16_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x8_cmplt_enable() _simd_u16x16_cmplt_enable()
//#elif defined(_simd_u16x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u16x8 ANVIL_SIMD_CALL _simd_u16x8_cmplt(const register _simd_u16x8 x, const register _simd_u16x8 y) {
//		union SIMDUnion { _simd_u16x8 v1; _simd_u16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x8_cmplt_enable() _simd_u16x32_cmplt_enable()
//#elif defined(_simd_u16x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u16x8 ANVIL_SIMD_CALL _simd_u16x8_cmplt(const register _simd_u16x8 x, const register _simd_u16x8 y) {
//		union SIMDUnion { _simd_u16x8 v1; _simd_u16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x8_cmplt_enable() _simd_u16x64_cmplt_enable()
//#else
//	#define _simd_u16x8_cmplt(X,Y) _simd_u16x8_combine(\
//		_simd_u16x4_cmplt(_simd_u16x8_splitlo(X), _simd_u16x8_splitlo(Y)),\
//		_simd_u16x4_cmplt(_simd_u16x8_splithi(X), _simd_u16x8_splithi(Y)))
//	#define _simd_u16x8_cmplt_enable() (_simd_u16x4_cmplt_enable() && _simd_u16x8_combine_enable() && _simd_u16x8_splitlo_enable()  && _simd_u16x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x8_cmplt_) && ! defined(_simd_u16x8_cmplt_scalar_)
//	#define _simd_u16x8_cmplt_scalar_(X,Y) _simd_u16x8_cmplt_(X,_simd_u16x8_fill_scalar_(Y))
//	#define _simd_u16x8_cmplt_scalar_instruction_set _simd_u16x8_cmplt_instruction_set
//#endif
//#ifdef _simd_u16x8_cmplt_scalar_
//	#define _simd_u16x8_cmplt_scalar(X,Y) _simd_u16x8_cmplt_scalar_(X,Y)
//	#define _simd_u16x8_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_u16x8_cmplt_scalar(X,Y) _simd_u16x8_cmplt_safe(X,_simd_u16x8_fill_scalar_safe(Y))
//	#define _simd_u16x8_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_u16x1_cmplt_safe
//	#define _simd_u16x1_cmplt_safe(X,Y) static_cast<_simd_u16x1>(X < Y)
//	#define _simd_u16x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_u16x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_cmplt_enabled() true
//#endif
//
//#define _simd_u16x16_cmplt_safe(X,Y)_simd_u16x16_combine_safe(\
//	_simd_u16x8_cmplt_safe(_simd_u16x16_splitlo_safe(X), _simd_ u16x16_splitlo_safe(Y)),\
//	_simd_u16x8_cmplt_safe(_simd_u16x16_splithi_safe(X), _simd_ u16x16_splithi_safe(Y)))
//#ifdef _simd_u16x16_cmplt_
//	#define _simd_u16x16_cmplt(X,Y) _simd_u16x16_cmplt_(X, Y)
//	#define _simd_u16x16_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_cmplt_instruction_set>()
//#elif defined(_simd_u16x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u16x16 ANVIL_SIMD_CALL _simd_u16x16_cmplt(const register _simd_u16x16 x, const register _simd_u16x16 y) {
//		union SIMDUnion { _simd_u16x16 v1; _simd_u16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x16_cmplt_enable() _simd_u16x32_cmplt_enable()
//#elif defined(_simd_u16x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u16x16 ANVIL_SIMD_CALL _simd_u16x16_cmplt(const register _simd_u16x16 x, const register _simd_u16x16 y) {
//		union SIMDUnion { _simd_u16x16 v1; _simd_u16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x16_cmplt_enable() _simd_u16x64_cmplt_enable()
//#else
//	#define _simd_u16x16_cmplt(X,Y) _simd_u16x16_combine(\
//		_simd_u16x8_cmplt(_simd_u16x16_splitlo(X), _simd_u16x16_splitlo(Y)),\
//		_simd_u16x8_cmplt(_simd_u16x16_splithi(X), _simd_u16x16_splithi(Y)))
//	#define _simd_u16x16_cmplt_enable() (_simd_u16x8_cmplt_enable() && _simd_u16x16_combine_enable() && _simd_u16x16_splitlo_enable()  && _simd_u16x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x16_cmplt_) && ! defined(_simd_u16x16_cmplt_scalar_)
//	#define _simd_u16x16_cmplt_scalar_(X,Y) _simd_u16x16_cmplt_(X,_simd_u16x16_fill_scalar_(Y))
//	#define _simd_u16x16_cmplt_scalar_instruction_set _simd_u16x16_cmplt_instruction_set
//#endif
//#ifdef _simd_u16x16_cmplt_scalar_
//	#define _simd_u16x16_cmplt_scalar(X,Y) _simd_u16x16_cmplt_scalar_(X,Y)
//	#define _simd_u16x16_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_u16x16_cmplt_scalar(X,Y) _simd_u16x16_cmplt_safe(X,_simd_u16x16_fill_scalar_safe(Y))
//	#define _simd_u16x16_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_u16x1_cmplt_safe
//	#define _simd_u16x1_cmplt_safe(X,Y) static_cast<_simd_u16x1>(X < Y)
//	#define _simd_u16x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_u16x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_cmplt_enabled() true
//#endif
//
//#define _simd_u16x32_cmplt_safe(X,Y)_simd_u16x32_combine_safe(\
//	_simd_u16x16_cmplt_safe(_simd_u16x32_splitlo_safe(X), _simd_ u16x32_splitlo_safe(Y)),\
//	_simd_u16x16_cmplt_safe(_simd_u16x32_splithi_safe(X), _simd_ u16x32_splithi_safe(Y)))
//#ifdef _simd_u16x32_cmplt_
//	#define _simd_u16x32_cmplt(X,Y) _simd_u16x32_cmplt_(X, Y)
//	#define _simd_u16x32_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_cmplt_instruction_set>()
//#elif defined(_simd_u16x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u16x32 ANVIL_SIMD_CALL _simd_u16x32_cmplt(const register _simd_u16x32 x, const register _simd_u16x32 y) {
//		union SIMDUnion { _simd_u16x32 v1; _simd_u16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x32_cmplt_enable() _simd_u16x64_cmplt_enable()
//#else
//	#define _simd_u16x32_cmplt(X,Y) _simd_u16x32_combine(\
//		_simd_u16x16_cmplt(_simd_u16x32_splitlo(X), _simd_u16x32_splitlo(Y)),\
//		_simd_u16x16_cmplt(_simd_u16x32_splithi(X), _simd_u16x32_splithi(Y)))
//	#define _simd_u16x32_cmplt_enable() (_simd_u16x16_cmplt_enable() && _simd_u16x32_combine_enable() && _simd_u16x32_splitlo_enable()  && _simd_u16x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x32_cmplt_) && ! defined(_simd_u16x32_cmplt_scalar_)
//	#define _simd_u16x32_cmplt_scalar_(X,Y) _simd_u16x32_cmplt_(X,_simd_u16x32_fill_scalar_(Y))
//	#define _simd_u16x32_cmplt_scalar_instruction_set _simd_u16x32_cmplt_instruction_set
//#endif
//#ifdef _simd_u16x32_cmplt_scalar_
//	#define _simd_u16x32_cmplt_scalar(X,Y) _simd_u16x32_cmplt_scalar_(X,Y)
//	#define _simd_u16x32_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_u16x32_cmplt_scalar(X,Y) _simd_u16x32_cmplt_safe(X,_simd_u16x32_fill_scalar_safe(Y))
//	#define _simd_u16x32_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_u16x1_cmplt_safe
//	#define _simd_u16x1_cmplt_safe(X,Y) static_cast<_simd_u16x1>(X < Y)
//	#define _simd_u16x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_u16x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_cmplt_enabled() true
//#endif
//
//#define _simd_u16x64_cmplt_safe(X,Y)_simd_u16x64_combine_safe(\
//	_simd_u16x32_cmplt_safe(_simd_u16x64_splitlo_safe(X), _simd_ u16x64_splitlo_safe(Y)),\
//	_simd_u16x32_cmplt_safe(_simd_u16x64_splithi_safe(X), _simd_ u16x64_splithi_safe(Y)))
//#ifdef _simd_u16x64_cmplt_
//	#define _simd_u16x64_cmplt(X,Y) _simd_u16x64_cmplt_(X, Y)
//	#define _simd_u16x64_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_cmplt_instruction_set>()
//#else
//	#define _simd_u16x64_cmplt(X,Y) _simd_u16x64_combine(\
//		_simd_u16x32_cmplt(_simd_u16x64_splitlo(X), _simd_u16x64_splitlo(Y)),\
//		_simd_u16x32_cmplt(_simd_u16x64_splithi(X), _simd_u16x64_splithi(Y)))
//	#define _simd_u16x64_cmplt_enable() (_simd_u16x32_cmplt_enable() && _simd_u16x64_combine_enable() && _simd_u16x64_splitlo_enable()  && _simd_u16x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x64_cmplt_) && ! defined(_simd_u16x64_cmplt_scalar_)
//	#define _simd_u16x64_cmplt_scalar_(X,Y) _simd_u16x64_cmplt_(X,_simd_u16x64_fill_scalar_(Y))
//	#define _simd_u16x64_cmplt_scalar_instruction_set _simd_u16x64_cmplt_instruction_set
//#endif
//#ifdef _simd_u16x64_cmplt_scalar_
//	#define _simd_u16x64_cmplt_scalar(X,Y) _simd_u16x64_cmplt_scalar_(X,Y)
//	#define _simd_u16x64_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_u16x64_cmplt_scalar(X,Y) _simd_u16x64_cmplt_safe(X,_simd_u16x64_fill_scalar_safe(Y))
//	#define _simd_u16x64_cmplt_scalar_enabled() true
//#endif
//
//// -- s8 --
//
//#ifndef _simd_s8x1_cmplt_safe
//	#define _simd_s8x1_cmplt_safe(X,Y) static_cast<_simd_s8x1>(X < Y)
//	#define _simd_s8x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_s8x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_cmplt_enabled() true
//#endif
//
//#define _simd_s8x2_cmplt_safe(X,Y)_simd_s8x2_combine_safe(\
//	_simd_s8x1_cmplt_safe(_simd_s8x2_splitlo_safe(X), _simd_ s8x2_splitlo_safe(Y)),\
//	_simd_s8x1_cmplt_safe(_simd_s8x2_splithi_safe(X), _simd_ s8x2_splithi_safe(Y)))
//#ifdef _simd_s8x2_cmplt_
//	#define _simd_s8x2_cmplt(X,Y) _simd_s8x2_cmplt_(X, Y)
//	#define _simd_s8x2_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_cmplt_instruction_set>()
//#elif defined(_simd_s8x4_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_cmplt(const register _simd_s8x2 x, const register _simd_s8x2 y) {
//		union SIMDUnion { _simd_s8x2 v1; _simd_s8x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x4_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x2_cmplt_enable() _simd_s8x4_cmplt_enable()
//#elif defined(_simd_s8x8_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_cmplt(const register _simd_s8x2 x, const register _simd_s8x2 y) {
//		union SIMDUnion { _simd_s8x2 v1; _simd_s8x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x8_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x2_cmplt_enable() _simd_s8x8_cmplt_enable()
//#elif defined(_simd_s8x16_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_cmplt(const register _simd_s8x2 x, const register _simd_s8x2 y) {
//		union SIMDUnion { _simd_s8x2 v1; _simd_s8x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x16_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x2_cmplt_enable() _simd_s8x16_cmplt_enable()
//#elif defined(_simd_s8x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_cmplt(const register _simd_s8x2 x, const register _simd_s8x2 y) {
//		union SIMDUnion { _simd_s8x2 v1; _simd_s8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x2_cmplt_enable() _simd_s8x32_cmplt_enable()
//#elif defined(_simd_s8x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_cmplt(const register _simd_s8x2 x, const register _simd_s8x2 y) {
//		union SIMDUnion { _simd_s8x2 v1; _simd_s8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x2_cmplt_enable() _simd_s8x64_cmplt_enable()
//#else
//	#define _simd_s8x2_cmplt(X,Y) _simd_s8x2_combine(\
//		_simd_s8x1_cmplt(_simd_s8x2_splitlo(X), _simd_s8x2_splitlo(Y)),\
//		_simd_s8x1_cmplt(_simd_s8x2_splithi(X), _simd_s8x2_splithi(Y)))
//	#define _simd_s8x2_cmplt_enable() (_simd_s8x1_cmplt_enable() && _simd_s8x2_combine_enable() && _simd_s8x2_splitlo_enable()  && _simd_s8x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x2_cmplt_) && ! defined(_simd_s8x2_cmplt_scalar_)
//	#define _simd_s8x2_cmplt_scalar_(X,Y) _simd_s8x2_cmplt_(X,_simd_s8x2_fill_scalar_(Y))
//	#define _simd_s8x2_cmplt_scalar_instruction_set _simd_s8x2_cmplt_instruction_set
//#endif
//#ifdef _simd_s8x2_cmplt_scalar_
//	#define _simd_s8x2_cmplt_scalar(X,Y) _simd_s8x2_cmplt_scalar_(X,Y)
//	#define _simd_s8x2_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_s8x2_cmplt_scalar(X,Y) _simd_s8x2_cmplt_safe(X,_simd_s8x2_fill_scalar_safe(Y))
//	#define _simd_s8x2_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_s8x1_cmplt_safe
//	#define _simd_s8x1_cmplt_safe(X,Y) static_cast<_simd_s8x1>(X < Y)
//	#define _simd_s8x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_s8x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_cmplt_enabled() true
//#endif
//
//#define _simd_s8x4_cmplt_safe(X,Y)_simd_s8x4_combine_safe(\
//	_simd_s8x2_cmplt_safe(_simd_s8x4_splitlo_safe(X), _simd_ s8x4_splitlo_safe(Y)),\
//	_simd_s8x2_cmplt_safe(_simd_s8x4_splithi_safe(X), _simd_ s8x4_splithi_safe(Y)))
//#ifdef _simd_s8x4_cmplt_
//	#define _simd_s8x4_cmplt(X,Y) _simd_s8x4_cmplt_(X, Y)
//	#define _simd_s8x4_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_cmplt_instruction_set>()
//#elif defined(_simd_s8x8_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_cmplt(const register _simd_s8x4 x, const register _simd_s8x4 y) {
//		union SIMDUnion { _simd_s8x4 v1; _simd_s8x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x8_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x4_cmplt_enable() _simd_s8x8_cmplt_enable()
//#elif defined(_simd_s8x16_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_cmplt(const register _simd_s8x4 x, const register _simd_s8x4 y) {
//		union SIMDUnion { _simd_s8x4 v1; _simd_s8x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x16_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x4_cmplt_enable() _simd_s8x16_cmplt_enable()
//#elif defined(_simd_s8x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_cmplt(const register _simd_s8x4 x, const register _simd_s8x4 y) {
//		union SIMDUnion { _simd_s8x4 v1; _simd_s8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x4_cmplt_enable() _simd_s8x32_cmplt_enable()
//#elif defined(_simd_s8x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_cmplt(const register _simd_s8x4 x, const register _simd_s8x4 y) {
//		union SIMDUnion { _simd_s8x4 v1; _simd_s8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x4_cmplt_enable() _simd_s8x64_cmplt_enable()
//#else
//	#define _simd_s8x4_cmplt(X,Y) _simd_s8x4_combine(\
//		_simd_s8x2_cmplt(_simd_s8x4_splitlo(X), _simd_s8x4_splitlo(Y)),\
//		_simd_s8x2_cmplt(_simd_s8x4_splithi(X), _simd_s8x4_splithi(Y)))
//	#define _simd_s8x4_cmplt_enable() (_simd_s8x2_cmplt_enable() && _simd_s8x4_combine_enable() && _simd_s8x4_splitlo_enable()  && _simd_s8x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x4_cmplt_) && ! defined(_simd_s8x4_cmplt_scalar_)
//	#define _simd_s8x4_cmplt_scalar_(X,Y) _simd_s8x4_cmplt_(X,_simd_s8x4_fill_scalar_(Y))
//	#define _simd_s8x4_cmplt_scalar_instruction_set _simd_s8x4_cmplt_instruction_set
//#endif
//#ifdef _simd_s8x4_cmplt_scalar_
//	#define _simd_s8x4_cmplt_scalar(X,Y) _simd_s8x4_cmplt_scalar_(X,Y)
//	#define _simd_s8x4_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_s8x4_cmplt_scalar(X,Y) _simd_s8x4_cmplt_safe(X,_simd_s8x4_fill_scalar_safe(Y))
//	#define _simd_s8x4_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_s8x1_cmplt_safe
//	#define _simd_s8x1_cmplt_safe(X,Y) static_cast<_simd_s8x1>(X < Y)
//	#define _simd_s8x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_s8x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_cmplt_enabled() true
//#endif
//
//#define _simd_s8x8_cmplt_safe(X,Y)_simd_s8x8_combine_safe(\
//	_simd_s8x4_cmplt_safe(_simd_s8x8_splitlo_safe(X), _simd_ s8x8_splitlo_safe(Y)),\
//	_simd_s8x4_cmplt_safe(_simd_s8x8_splithi_safe(X), _simd_ s8x8_splithi_safe(Y)))
//#ifdef _simd_s8x8_cmplt_
//	#define _simd_s8x8_cmplt(X,Y) _simd_s8x8_cmplt_(X, Y)
//	#define _simd_s8x8_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_cmplt_instruction_set>()
//#elif defined(_simd_s8x16_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s8x8 ANVIL_SIMD_CALL _simd_s8x8_cmplt(const register _simd_s8x8 x, const register _simd_s8x8 y) {
//		union SIMDUnion { _simd_s8x8 v1; _simd_s8x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x16_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x8_cmplt_enable() _simd_s8x16_cmplt_enable()
//#elif defined(_simd_s8x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s8x8 ANVIL_SIMD_CALL _simd_s8x8_cmplt(const register _simd_s8x8 x, const register _simd_s8x8 y) {
//		union SIMDUnion { _simd_s8x8 v1; _simd_s8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x8_cmplt_enable() _simd_s8x32_cmplt_enable()
//#elif defined(_simd_s8x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s8x8 ANVIL_SIMD_CALL _simd_s8x8_cmplt(const register _simd_s8x8 x, const register _simd_s8x8 y) {
//		union SIMDUnion { _simd_s8x8 v1; _simd_s8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x8_cmplt_enable() _simd_s8x64_cmplt_enable()
//#else
//	#define _simd_s8x8_cmplt(X,Y) _simd_s8x8_combine(\
//		_simd_s8x4_cmplt(_simd_s8x8_splitlo(X), _simd_s8x8_splitlo(Y)),\
//		_simd_s8x4_cmplt(_simd_s8x8_splithi(X), _simd_s8x8_splithi(Y)))
//	#define _simd_s8x8_cmplt_enable() (_simd_s8x4_cmplt_enable() && _simd_s8x8_combine_enable() && _simd_s8x8_splitlo_enable()  && _simd_s8x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x8_cmplt_) && ! defined(_simd_s8x8_cmplt_scalar_)
//	#define _simd_s8x8_cmplt_scalar_(X,Y) _simd_s8x8_cmplt_(X,_simd_s8x8_fill_scalar_(Y))
//	#define _simd_s8x8_cmplt_scalar_instruction_set _simd_s8x8_cmplt_instruction_set
//#endif
//#ifdef _simd_s8x8_cmplt_scalar_
//	#define _simd_s8x8_cmplt_scalar(X,Y) _simd_s8x8_cmplt_scalar_(X,Y)
//	#define _simd_s8x8_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_s8x8_cmplt_scalar(X,Y) _simd_s8x8_cmplt_safe(X,_simd_s8x8_fill_scalar_safe(Y))
//	#define _simd_s8x8_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_s8x1_cmplt_safe
//	#define _simd_s8x1_cmplt_safe(X,Y) static_cast<_simd_s8x1>(X < Y)
//	#define _simd_s8x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_s8x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_cmplt_enabled() true
//#endif
//
//#define _simd_s8x16_cmplt_safe(X,Y)_simd_s8x16_combine_safe(\
//	_simd_s8x8_cmplt_safe(_simd_s8x16_splitlo_safe(X), _simd_ s8x16_splitlo_safe(Y)),\
//	_simd_s8x8_cmplt_safe(_simd_s8x16_splithi_safe(X), _simd_ s8x16_splithi_safe(Y)))
//#ifdef _simd_s8x16_cmplt_
//	#define _simd_s8x16_cmplt(X,Y) _simd_s8x16_cmplt_(X, Y)
//	#define _simd_s8x16_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_cmplt_instruction_set>()
//#elif defined(_simd_s8x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s8x16 ANVIL_SIMD_CALL _simd_s8x16_cmplt(const register _simd_s8x16 x, const register _simd_s8x16 y) {
//		union SIMDUnion { _simd_s8x16 v1; _simd_s8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x16_cmplt_enable() _simd_s8x32_cmplt_enable()
//#elif defined(_simd_s8x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s8x16 ANVIL_SIMD_CALL _simd_s8x16_cmplt(const register _simd_s8x16 x, const register _simd_s8x16 y) {
//		union SIMDUnion { _simd_s8x16 v1; _simd_s8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x16_cmplt_enable() _simd_s8x64_cmplt_enable()
//#else
//	#define _simd_s8x16_cmplt(X,Y) _simd_s8x16_combine(\
//		_simd_s8x8_cmplt(_simd_s8x16_splitlo(X), _simd_s8x16_splitlo(Y)),\
//		_simd_s8x8_cmplt(_simd_s8x16_splithi(X), _simd_s8x16_splithi(Y)))
//	#define _simd_s8x16_cmplt_enable() (_simd_s8x8_cmplt_enable() && _simd_s8x16_combine_enable() && _simd_s8x16_splitlo_enable()  && _simd_s8x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x16_cmplt_) && ! defined(_simd_s8x16_cmplt_scalar_)
//	#define _simd_s8x16_cmplt_scalar_(X,Y) _simd_s8x16_cmplt_(X,_simd_s8x16_fill_scalar_(Y))
//	#define _simd_s8x16_cmplt_scalar_instruction_set _simd_s8x16_cmplt_instruction_set
//#endif
//#ifdef _simd_s8x16_cmplt_scalar_
//	#define _simd_s8x16_cmplt_scalar(X,Y) _simd_s8x16_cmplt_scalar_(X,Y)
//	#define _simd_s8x16_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_s8x16_cmplt_scalar(X,Y) _simd_s8x16_cmplt_safe(X,_simd_s8x16_fill_scalar_safe(Y))
//	#define _simd_s8x16_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_s8x1_cmplt_safe
//	#define _simd_s8x1_cmplt_safe(X,Y) static_cast<_simd_s8x1>(X < Y)
//	#define _simd_s8x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_s8x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_cmplt_enabled() true
//#endif
//
//#define _simd_s8x32_cmplt_safe(X,Y)_simd_s8x32_combine_safe(\
//	_simd_s8x16_cmplt_safe(_simd_s8x32_splitlo_safe(X), _simd_ s8x32_splitlo_safe(Y)),\
//	_simd_s8x16_cmplt_safe(_simd_s8x32_splithi_safe(X), _simd_ s8x32_splithi_safe(Y)))
//#ifdef _simd_s8x32_cmplt_
//	#define _simd_s8x32_cmplt(X,Y) _simd_s8x32_cmplt_(X, Y)
//	#define _simd_s8x32_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_cmplt_instruction_set>()
//#elif defined(_simd_s8x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_s8x32 ANVIL_SIMD_CALL _simd_s8x32_cmplt(const register _simd_s8x32 x, const register _simd_s8x32 y) {
//		union SIMDUnion { _simd_s8x32 v1; _simd_s8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x32_cmplt_enable() _simd_s8x64_cmplt_enable()
//#else
//	#define _simd_s8x32_cmplt(X,Y) _simd_s8x32_combine(\
//		_simd_s8x16_cmplt(_simd_s8x32_splitlo(X), _simd_s8x32_splitlo(Y)),\
//		_simd_s8x16_cmplt(_simd_s8x32_splithi(X), _simd_s8x32_splithi(Y)))
//	#define _simd_s8x32_cmplt_enable() (_simd_s8x16_cmplt_enable() && _simd_s8x32_combine_enable() && _simd_s8x32_splitlo_enable()  && _simd_s8x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x32_cmplt_) && ! defined(_simd_s8x32_cmplt_scalar_)
//	#define _simd_s8x32_cmplt_scalar_(X,Y) _simd_s8x32_cmplt_(X,_simd_s8x32_fill_scalar_(Y))
//	#define _simd_s8x32_cmplt_scalar_instruction_set _simd_s8x32_cmplt_instruction_set
//#endif
//#ifdef _simd_s8x32_cmplt_scalar_
//	#define _simd_s8x32_cmplt_scalar(X,Y) _simd_s8x32_cmplt_scalar_(X,Y)
//	#define _simd_s8x32_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_s8x32_cmplt_scalar(X,Y) _simd_s8x32_cmplt_safe(X,_simd_s8x32_fill_scalar_safe(Y))
//	#define _simd_s8x32_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_s8x1_cmplt_safe
//	#define _simd_s8x1_cmplt_safe(X,Y) static_cast<_simd_s8x1>(X < Y)
//	#define _simd_s8x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_s8x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_cmplt_enabled() true
//#endif
//
//#define _simd_s8x64_cmplt_safe(X,Y)_simd_s8x64_combine_safe(\
//	_simd_s8x32_cmplt_safe(_simd_s8x64_splitlo_safe(X), _simd_ s8x64_splitlo_safe(Y)),\
//	_simd_s8x32_cmplt_safe(_simd_s8x64_splithi_safe(X), _simd_ s8x64_splithi_safe(Y)))
//#ifdef _simd_s8x64_cmplt_
//	#define _simd_s8x64_cmplt(X,Y) _simd_s8x64_cmplt_(X, Y)
//	#define _simd_s8x64_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_cmplt_instruction_set>()
//#else
//	#define _simd_s8x64_cmplt(X,Y) _simd_s8x64_combine(\
//		_simd_s8x32_cmplt(_simd_s8x64_splitlo(X), _simd_s8x64_splitlo(Y)),\
//		_simd_s8x32_cmplt(_simd_s8x64_splithi(X), _simd_s8x64_splithi(Y)))
//	#define _simd_s8x64_cmplt_enable() (_simd_s8x32_cmplt_enable() && _simd_s8x64_combine_enable() && _simd_s8x64_splitlo_enable()  && _simd_s8x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x64_cmplt_) && ! defined(_simd_s8x64_cmplt_scalar_)
//	#define _simd_s8x64_cmplt_scalar_(X,Y) _simd_s8x64_cmplt_(X,_simd_s8x64_fill_scalar_(Y))
//	#define _simd_s8x64_cmplt_scalar_instruction_set _simd_s8x64_cmplt_instruction_set
//#endif
//#ifdef _simd_s8x64_cmplt_scalar_
//	#define _simd_s8x64_cmplt_scalar(X,Y) _simd_s8x64_cmplt_scalar_(X,Y)
//	#define _simd_s8x64_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_s8x64_cmplt_scalar(X,Y) _simd_s8x64_cmplt_safe(X,_simd_s8x64_fill_scalar_safe(Y))
//	#define _simd_s8x64_cmplt_scalar_enabled() true
//#endif
//
//// -- u8 --
//
//#ifndef _simd_u8x1_cmplt_safe
//	#define _simd_u8x1_cmplt_safe(X,Y) static_cast<_simd_u8x1>(X < Y)
//	#define _simd_u8x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_u8x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_cmplt_enabled() true
//#endif
//
//#define _simd_u8x2_cmplt_safe(X,Y)_simd_u8x2_combine_safe(\
//	_simd_u8x1_cmplt_safe(_simd_u8x2_splitlo_safe(X), _simd_ u8x2_splitlo_safe(Y)),\
//	_simd_u8x1_cmplt_safe(_simd_u8x2_splithi_safe(X), _simd_ u8x2_splithi_safe(Y)))
//#ifdef _simd_u8x2_cmplt_
//	#define _simd_u8x2_cmplt(X,Y) _simd_u8x2_cmplt_(X, Y)
//	#define _simd_u8x2_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_cmplt_instruction_set>()
//#elif defined(_simd_u8x4_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_cmplt(const register _simd_u8x2 x, const register _simd_u8x2 y) {
//		union SIMDUnion { _simd_u8x2 v1; _simd_u8x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x4_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x2_cmplt_enable() _simd_u8x4_cmplt_enable()
//#elif defined(_simd_u8x8_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_cmplt(const register _simd_u8x2 x, const register _simd_u8x2 y) {
//		union SIMDUnion { _simd_u8x2 v1; _simd_u8x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x8_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x2_cmplt_enable() _simd_u8x8_cmplt_enable()
//#elif defined(_simd_u8x16_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_cmplt(const register _simd_u8x2 x, const register _simd_u8x2 y) {
//		union SIMDUnion { _simd_u8x2 v1; _simd_u8x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x16_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x2_cmplt_enable() _simd_u8x16_cmplt_enable()
//#elif defined(_simd_u8x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_cmplt(const register _simd_u8x2 x, const register _simd_u8x2 y) {
//		union SIMDUnion { _simd_u8x2 v1; _simd_u8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x2_cmplt_enable() _simd_u8x32_cmplt_enable()
//#elif defined(_simd_u8x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_cmplt(const register _simd_u8x2 x, const register _simd_u8x2 y) {
//		union SIMDUnion { _simd_u8x2 v1; _simd_u8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x2_cmplt_enable() _simd_u8x64_cmplt_enable()
//#else
//	#define _simd_u8x2_cmplt(X,Y) _simd_u8x2_combine(\
//		_simd_u8x1_cmplt(_simd_u8x2_splitlo(X), _simd_u8x2_splitlo(Y)),\
//		_simd_u8x1_cmplt(_simd_u8x2_splithi(X), _simd_u8x2_splithi(Y)))
//	#define _simd_u8x2_cmplt_enable() (_simd_u8x1_cmplt_enable() && _simd_u8x2_combine_enable() && _simd_u8x2_splitlo_enable()  && _simd_u8x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x2_cmplt_) && ! defined(_simd_u8x2_cmplt_scalar_)
//	#define _simd_u8x2_cmplt_scalar_(X,Y) _simd_u8x2_cmplt_(X,_simd_u8x2_fill_scalar_(Y))
//	#define _simd_u8x2_cmplt_scalar_instruction_set _simd_u8x2_cmplt_instruction_set
//#endif
//#ifdef _simd_u8x2_cmplt_scalar_
//	#define _simd_u8x2_cmplt_scalar(X,Y) _simd_u8x2_cmplt_scalar_(X,Y)
//	#define _simd_u8x2_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_u8x2_cmplt_scalar(X,Y) _simd_u8x2_cmplt_safe(X,_simd_u8x2_fill_scalar_safe(Y))
//	#define _simd_u8x2_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_u8x1_cmplt_safe
//	#define _simd_u8x1_cmplt_safe(X,Y) static_cast<_simd_u8x1>(X < Y)
//	#define _simd_u8x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_u8x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_cmplt_enabled() true
//#endif
//
//#define _simd_u8x4_cmplt_safe(X,Y)_simd_u8x4_combine_safe(\
//	_simd_u8x2_cmplt_safe(_simd_u8x4_splitlo_safe(X), _simd_ u8x4_splitlo_safe(Y)),\
//	_simd_u8x2_cmplt_safe(_simd_u8x4_splithi_safe(X), _simd_ u8x4_splithi_safe(Y)))
//#ifdef _simd_u8x4_cmplt_
//	#define _simd_u8x4_cmplt(X,Y) _simd_u8x4_cmplt_(X, Y)
//	#define _simd_u8x4_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_cmplt_instruction_set>()
//#elif defined(_simd_u8x8_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_cmplt(const register _simd_u8x4 x, const register _simd_u8x4 y) {
//		union SIMDUnion { _simd_u8x4 v1; _simd_u8x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x8_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x4_cmplt_enable() _simd_u8x8_cmplt_enable()
//#elif defined(_simd_u8x16_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_cmplt(const register _simd_u8x4 x, const register _simd_u8x4 y) {
//		union SIMDUnion { _simd_u8x4 v1; _simd_u8x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x16_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x4_cmplt_enable() _simd_u8x16_cmplt_enable()
//#elif defined(_simd_u8x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_cmplt(const register _simd_u8x4 x, const register _simd_u8x4 y) {
//		union SIMDUnion { _simd_u8x4 v1; _simd_u8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x4_cmplt_enable() _simd_u8x32_cmplt_enable()
//#elif defined(_simd_u8x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_cmplt(const register _simd_u8x4 x, const register _simd_u8x4 y) {
//		union SIMDUnion { _simd_u8x4 v1; _simd_u8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x4_cmplt_enable() _simd_u8x64_cmplt_enable()
//#else
//	#define _simd_u8x4_cmplt(X,Y) _simd_u8x4_combine(\
//		_simd_u8x2_cmplt(_simd_u8x4_splitlo(X), _simd_u8x4_splitlo(Y)),\
//		_simd_u8x2_cmplt(_simd_u8x4_splithi(X), _simd_u8x4_splithi(Y)))
//	#define _simd_u8x4_cmplt_enable() (_simd_u8x2_cmplt_enable() && _simd_u8x4_combine_enable() && _simd_u8x4_splitlo_enable()  && _simd_u8x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x4_cmplt_) && ! defined(_simd_u8x4_cmplt_scalar_)
//	#define _simd_u8x4_cmplt_scalar_(X,Y) _simd_u8x4_cmplt_(X,_simd_u8x4_fill_scalar_(Y))
//	#define _simd_u8x4_cmplt_scalar_instruction_set _simd_u8x4_cmplt_instruction_set
//#endif
//#ifdef _simd_u8x4_cmplt_scalar_
//	#define _simd_u8x4_cmplt_scalar(X,Y) _simd_u8x4_cmplt_scalar_(X,Y)
//	#define _simd_u8x4_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_u8x4_cmplt_scalar(X,Y) _simd_u8x4_cmplt_safe(X,_simd_u8x4_fill_scalar_safe(Y))
//	#define _simd_u8x4_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_u8x1_cmplt_safe
//	#define _simd_u8x1_cmplt_safe(X,Y) static_cast<_simd_u8x1>(X < Y)
//	#define _simd_u8x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_u8x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_cmplt_enabled() true
//#endif
//
//#define _simd_u8x8_cmplt_safe(X,Y)_simd_u8x8_combine_safe(\
//	_simd_u8x4_cmplt_safe(_simd_u8x8_splitlo_safe(X), _simd_ u8x8_splitlo_safe(Y)),\
//	_simd_u8x4_cmplt_safe(_simd_u8x8_splithi_safe(X), _simd_ u8x8_splithi_safe(Y)))
//#ifdef _simd_u8x8_cmplt_
//	#define _simd_u8x8_cmplt(X,Y) _simd_u8x8_cmplt_(X, Y)
//	#define _simd_u8x8_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_cmplt_instruction_set>()
//#elif defined(_simd_u8x16_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u8x8 ANVIL_SIMD_CALL _simd_u8x8_cmplt(const register _simd_u8x8 x, const register _simd_u8x8 y) {
//		union SIMDUnion { _simd_u8x8 v1; _simd_u8x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x16_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x8_cmplt_enable() _simd_u8x16_cmplt_enable()
//#elif defined(_simd_u8x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u8x8 ANVIL_SIMD_CALL _simd_u8x8_cmplt(const register _simd_u8x8 x, const register _simd_u8x8 y) {
//		union SIMDUnion { _simd_u8x8 v1; _simd_u8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x8_cmplt_enable() _simd_u8x32_cmplt_enable()
//#elif defined(_simd_u8x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u8x8 ANVIL_SIMD_CALL _simd_u8x8_cmplt(const register _simd_u8x8 x, const register _simd_u8x8 y) {
//		union SIMDUnion { _simd_u8x8 v1; _simd_u8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x8_cmplt_enable() _simd_u8x64_cmplt_enable()
//#else
//	#define _simd_u8x8_cmplt(X,Y) _simd_u8x8_combine(\
//		_simd_u8x4_cmplt(_simd_u8x8_splitlo(X), _simd_u8x8_splitlo(Y)),\
//		_simd_u8x4_cmplt(_simd_u8x8_splithi(X), _simd_u8x8_splithi(Y)))
//	#define _simd_u8x8_cmplt_enable() (_simd_u8x4_cmplt_enable() && _simd_u8x8_combine_enable() && _simd_u8x8_splitlo_enable()  && _simd_u8x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x8_cmplt_) && ! defined(_simd_u8x8_cmplt_scalar_)
//	#define _simd_u8x8_cmplt_scalar_(X,Y) _simd_u8x8_cmplt_(X,_simd_u8x8_fill_scalar_(Y))
//	#define _simd_u8x8_cmplt_scalar_instruction_set _simd_u8x8_cmplt_instruction_set
//#endif
//#ifdef _simd_u8x8_cmplt_scalar_
//	#define _simd_u8x8_cmplt_scalar(X,Y) _simd_u8x8_cmplt_scalar_(X,Y)
//	#define _simd_u8x8_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_u8x8_cmplt_scalar(X,Y) _simd_u8x8_cmplt_safe(X,_simd_u8x8_fill_scalar_safe(Y))
//	#define _simd_u8x8_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_u8x1_cmplt_safe
//	#define _simd_u8x1_cmplt_safe(X,Y) static_cast<_simd_u8x1>(X < Y)
//	#define _simd_u8x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_u8x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_cmplt_enabled() true
//#endif
//
//#define _simd_u8x16_cmplt_safe(X,Y)_simd_u8x16_combine_safe(\
//	_simd_u8x8_cmplt_safe(_simd_u8x16_splitlo_safe(X), _simd_ u8x16_splitlo_safe(Y)),\
//	_simd_u8x8_cmplt_safe(_simd_u8x16_splithi_safe(X), _simd_ u8x16_splithi_safe(Y)))
//#ifdef _simd_u8x16_cmplt_
//	#define _simd_u8x16_cmplt(X,Y) _simd_u8x16_cmplt_(X, Y)
//	#define _simd_u8x16_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_cmplt_instruction_set>()
//#elif defined(_simd_u8x32_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u8x16 ANVIL_SIMD_CALL _simd_u8x16_cmplt(const register _simd_u8x16 x, const register _simd_u8x16 y) {
//		union SIMDUnion { _simd_u8x16 v1; _simd_u8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x32_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x16_cmplt_enable() _simd_u8x32_cmplt_enable()
//#elif defined(_simd_u8x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u8x16 ANVIL_SIMD_CALL _simd_u8x16_cmplt(const register _simd_u8x16 x, const register _simd_u8x16 y) {
//		union SIMDUnion { _simd_u8x16 v1; _simd_u8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x16_cmplt_enable() _simd_u8x64_cmplt_enable()
//#else
//	#define _simd_u8x16_cmplt(X,Y) _simd_u8x16_combine(\
//		_simd_u8x8_cmplt(_simd_u8x16_splitlo(X), _simd_u8x16_splitlo(Y)),\
//		_simd_u8x8_cmplt(_simd_u8x16_splithi(X), _simd_u8x16_splithi(Y)))
//	#define _simd_u8x16_cmplt_enable() (_simd_u8x8_cmplt_enable() && _simd_u8x16_combine_enable() && _simd_u8x16_splitlo_enable()  && _simd_u8x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x16_cmplt_) && ! defined(_simd_u8x16_cmplt_scalar_)
//	#define _simd_u8x16_cmplt_scalar_(X,Y) _simd_u8x16_cmplt_(X,_simd_u8x16_fill_scalar_(Y))
//	#define _simd_u8x16_cmplt_scalar_instruction_set _simd_u8x16_cmplt_instruction_set
//#endif
//#ifdef _simd_u8x16_cmplt_scalar_
//	#define _simd_u8x16_cmplt_scalar(X,Y) _simd_u8x16_cmplt_scalar_(X,Y)
//	#define _simd_u8x16_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_u8x16_cmplt_scalar(X,Y) _simd_u8x16_cmplt_safe(X,_simd_u8x16_fill_scalar_safe(Y))
//	#define _simd_u8x16_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_u8x1_cmplt_safe
//	#define _simd_u8x1_cmplt_safe(X,Y) static_cast<_simd_u8x1>(X < Y)
//	#define _simd_u8x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_u8x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_cmplt_enabled() true
//#endif
//
//#define _simd_u8x32_cmplt_safe(X,Y)_simd_u8x32_combine_safe(\
//	_simd_u8x16_cmplt_safe(_simd_u8x32_splitlo_safe(X), _simd_ u8x32_splitlo_safe(Y)),\
//	_simd_u8x16_cmplt_safe(_simd_u8x32_splithi_safe(X), _simd_ u8x32_splithi_safe(Y)))
//#ifdef _simd_u8x32_cmplt_
//	#define _simd_u8x32_cmplt(X,Y) _simd_u8x32_cmplt_(X, Y)
//	#define _simd_u8x32_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_cmplt_instruction_set>()
//#elif defined(_simd_u8x64_cmplt_)
//	static ANVIL_STRONG_INLINE _simd_u8x32 ANVIL_SIMD_CALL _simd_u8x32_cmplt(const register _simd_u8x32 x, const register _simd_u8x32 y) {
//		union SIMDUnion { _simd_u8x32 v1; _simd_u8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x64_cmplt_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x32_cmplt_enable() _simd_u8x64_cmplt_enable()
//#else
//	#define _simd_u8x32_cmplt(X,Y) _simd_u8x32_combine(\
//		_simd_u8x16_cmplt(_simd_u8x32_splitlo(X), _simd_u8x32_splitlo(Y)),\
//		_simd_u8x16_cmplt(_simd_u8x32_splithi(X), _simd_u8x32_splithi(Y)))
//	#define _simd_u8x32_cmplt_enable() (_simd_u8x16_cmplt_enable() && _simd_u8x32_combine_enable() && _simd_u8x32_splitlo_enable()  && _simd_u8x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x32_cmplt_) && ! defined(_simd_u8x32_cmplt_scalar_)
//	#define _simd_u8x32_cmplt_scalar_(X,Y) _simd_u8x32_cmplt_(X,_simd_u8x32_fill_scalar_(Y))
//	#define _simd_u8x32_cmplt_scalar_instruction_set _simd_u8x32_cmplt_instruction_set
//#endif
//#ifdef _simd_u8x32_cmplt_scalar_
//	#define _simd_u8x32_cmplt_scalar(X,Y) _simd_u8x32_cmplt_scalar_(X,Y)
//	#define _simd_u8x32_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_u8x32_cmplt_scalar(X,Y) _simd_u8x32_cmplt_safe(X,_simd_u8x32_fill_scalar_safe(Y))
//	#define _simd_u8x32_cmplt_scalar_enabled() true
//#endif
//
//#ifndef _simd_u8x1_cmplt_safe
//	#define _simd_u8x1_cmplt_safe(X,Y) static_cast<_simd_u8x1>(X < Y)
//	#define _simd_u8x1_cmplt_(X,Y) x1_cmplt_safe(X,Y)
//	#define _simd_u8x1_cmplt_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_cmplt_enabled() true
//#endif
//
//#define _simd_u8x64_cmplt_safe(X,Y)_simd_u8x64_combine_safe(\
//	_simd_u8x32_cmplt_safe(_simd_u8x64_splitlo_safe(X), _simd_ u8x64_splitlo_safe(Y)),\
//	_simd_u8x32_cmplt_safe(_simd_u8x64_splithi_safe(X), _simd_ u8x64_splithi_safe(Y)))
//#ifdef _simd_u8x64_cmplt_
//	#define _simd_u8x64_cmplt(X,Y) _simd_u8x64_cmplt_(X, Y)
//	#define _simd_u8x64_cmplt_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_cmplt_instruction_set>()
//#else
//	#define _simd_u8x64_cmplt(X,Y) _simd_u8x64_combine(\
//		_simd_u8x32_cmplt(_simd_u8x64_splitlo(X), _simd_u8x64_splitlo(Y)),\
//		_simd_u8x32_cmplt(_simd_u8x64_splithi(X), _simd_u8x64_splithi(Y)))
//	#define _simd_u8x64_cmplt_enable() (_simd_u8x32_cmplt_enable() && _simd_u8x64_combine_enable() && _simd_u8x64_splitlo_enable()  && _simd_u8x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x64_cmplt_) && ! defined(_simd_u8x64_cmplt_scalar_)
//	#define _simd_u8x64_cmplt_scalar_(X,Y) _simd_u8x64_cmplt_(X,_simd_u8x64_fill_scalar_(Y))
//	#define _simd_u8x64_cmplt_scalar_instruction_set _simd_u8x64_cmplt_instruction_set
//#endif
//#ifdef _simd_u8x64_cmplt_scalar_
//	#define _simd_u8x64_cmplt_scalar(X,Y) _simd_u8x64_cmplt_scalar_(X,Y)
//	#define _simd_u8x64_cmplt_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_cmplt_scalar_instruction_set>()
//#else
//	#define _simd_u8x64_cmplt_scalar(X,Y) _simd_u8x64_cmplt_safe(X,_simd_u8x64_fill_scalar_safe(Y))
//	#define _simd_u8x64_cmplt_scalar_enabled() true
//#endif
//
