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

#ifndef ANVIL_COMPUTE_SIMD_OR_HPP
#define ANVIL_COMPUTE_SIMD_OR_HPP

#include "anvil/core/CpuRuntime.hpp"
#include "anvil/compute/Vector.hpp"

namespace anvil { namespace detail {

	template<class T>
	struct OptimisedVectorOr {
		typedef T type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(const type a, const type b) throw() {
			return a | b;
		}
	};

	template<class T>
	struct VectorOr {
		typedef T type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(const type& a, const type& b) throw() {
			return OptimisedVectorOr<T>::Execute< instruction_set>(a, b);
		}
	};

	// Optimised types

	template<>
	struct OptimisedVectorOr<float32_t> {
		typedef float32_t type;
		typedef uint32_t utype;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			union {
				type fa;
				utype ua;
			};
			union {
				type fb;
				utype ub;
			};
			fa = a;
			fb = b;
			ua |= ub;
			return fa;
		}
	};

	template<>
	struct OptimisedVectorOr<float64_t> {
		typedef float64_t type;
		typedef uint64_t utype;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			union {
				type fa;
				utype ua;
			};
			union {
				type fb;
				utype ub;
			};
			fa = a;
			fb = b;
			ua |= ub;
			return fa;
		}
	};

	template<class T, size_t S>
	struct OptimisedVectorOr<UnoptimisedNativeType<T,S>> {
		typedef UnoptimisedNativeType<T, S> type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, const type& b) throw() {
			for (size_t i = 0u; i < S; ++i) a[i] = OptimisedVectorOr<T>::Execute<instruction_set>(a[i], b[i]);
		}
	};


#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64

	template<uint64_t instruction_set>
	static ANVIL_STRONG_INLINE void OptimisedOr128(const void* a, const void* b, void* dst) {
		if constexpr ((instruction_set & ASM_SSE) != 0ull) {
			_mm_storeu_ps(static_cast<float*>(dst), _mm_and_ps(
				_mm_loadu_ps(static_cast<const float*>(a)),
				_mm_loadu_ps(static_cast<const float*>(b))
			));
		} else {
			const NativeUnsigned* ua = static_cast<const NativeUnsigned*>(a);
			const NativeUnsigned* ub = static_cast<const NativeUnsigned*>(b);
			NativeUnsigned* udst = static_cast<NativeUnsigned*>(dst);

			udst[0u] = ua[0u] | ub[0u];
			udst[1u] = ua[1u] | ub[1u];
			if constexpr (sizeof(NativeUnsigned) == 4u) {
				udst[2u] = ua[2u] | ub[2u];
				udst[3u] = ua[3u] | ub[3u];
			}
		}
	}

	template<uint64_t instruction_set>
	static ANVIL_STRONG_INLINE void OptimisedOr256(const void* a, const void* b, void* dst) {
		if constexpr ((instruction_set & ASM_AVX) != 0ull) {
			_mm256_storeu_ps(static_cast<float*>(dst), _mm_and_ps(
				_mm256_loadu_ps(static_cast<const float*>(a)),
				_mm256_loadu_ps(static_cast<const float*>(b))
			));
		} else {
			OptimisedOr128<instruction_set>(a, b, dst);
			OptimisedOr128<instruction_set>(static_cast<const uint8_t*>(a) + 16u, static_cast<const uint8_t*>(b) + 16u, static_cast<uint8_t*>(dst) + 16u);
		}
	}

	template<uint64_t instruction_set>
	static ANVIL_STRONG_INLINE void OptimisedOr512(const void* a, const void* b, void* dst) {
		if constexpr ((instruction_set & ASM_AVX512F) != 0ull) {
			_mm512_storeu_ps(static_cast<float*>(dst), _mm_and_ps(
				_mm512_loadu_ps(static_cast<const float*>(a)),
				_mm512_loadu_ps(static_cast<const float*>(b))
			));
		} else {
			OptimisedOr256<instruction_set>(a, b, dst);
			OptimisedOr256<instruction_set>(static_cast<const uint8_t*>(a) + 32u, static_cast<const uint8_t*>(b) + 32u, static_cast<uint8_t*>(dst) + 32u);
		}
	}

	template<>
	struct OptimisedVectorOr<__m128> {
		typedef __m128 type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			if constexpr ((instruction_set & ASM_SSE) != 0ull) {
				return _mm_and_ps(a, b);
			} else {
				OptimisedOr128<instruction_set>(&a, &b, &a);
				return a;
			}
		}
	};

	template<>
	struct OptimisedVectorOr<__m128i> {
		typedef __m128i type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			if constexpr ((instruction_set & ASM_SSE2) != 0ull) {
				return _mm_and_si128(a, b);
			} else {
				OptimisedOr128<instruction_set>(&a, &b, &a);
				return a;
			}
		}
	};

	template<>
	struct OptimisedVectorOr<__m128d> {
		typedef __m128d type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			if constexpr ((instruction_set & ASM_SSE2) != 0ull) {
				return _mm_and_pd(a, b);
			} else {
				OptimisedOr128<instruction_set>(&a, &b, &a);
				return a;
			}
		}
	};

	template<>
	struct OptimisedVectorOr<__m256> {
		typedef __m256 type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			if constexpr ((instruction_set & ASM_AVX) != 0ull) {
				return _mm256_and_ps(a, b);
			} else {
				OptimisedOr256<instruction_set>(&a, &b, &a);
				return a;
			}
		}
	};

	template<>
	struct OptimisedVectorOr<__m256i> {
		typedef __m256i type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			if constexpr ((instruction_set & ASM_AVX2) != 0ull) {
				return _mm256_and_si256(a, b);
			} else {
				OptimisedOr256<instruction_set>(&a, &b, &a);
				return a;
			}
		}
	};

	template<>
	struct OptimisedVectorOr<__m256d> {
		typedef __m256d type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			if constexpr ((instruction_set & ASM_AVX) != 0ull) {
				return _mm256_and_pd(a, b);
			} else {
				OptimisedOr256<instruction_set>(&a, &b, &a);
				return a;
			}
		}
	};

	template<>
	struct OptimisedVectorOr<__m512> {
		typedef __m512 type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			if constexpr ((instruction_set & ASM_AVX512F) != 0ull) {
				return _mm512_and_ps(a, b);
			} else {
				OptimisedOr512<instruction_set>(&a, &b, &a);
				return a;
			}
		}
	};

	template<>
	struct OptimisedVectorOr<__m512i> {
		typedef __m512i type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			if constexpr ((instruction_set & ASM_AVX512BW) != 0ull) {
				return _mm512_and_si512(a, b);
			} else {
				OptimisedOr512<instruction_set>(&a, &b, &a);
				return a;
			}
		}
	};

	template<>
	struct OptimisedVectorOr<__m512d> {
		typedef __m512d type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			if constexpr ((instruction_set & ASM_AVX512F) != 0ull) {
				return _mm512_and_pd(a, b);
			} else {
				OptimisedOr512<instruction_set>(&a, &b, &a);
				return a;
			}
		}
	};

#endif

	// Unoptimised vectors

	template<class T, size_t size>
	struct VectorOr<detail::BasicVector<T, size>> {
		typedef detail::BasicVector<T, size> type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, const type& b) throw() {
			a.native = OptimisedVectorOr<type::native_t>::Execute<instruction_set>(a.native, b.native);
			return a;
		}
	};
}}

namespace anvil {

	template<uint64_t instruction_set = ASM_MINIMUM, class T>
	static inline T VectorOr(const T& a, const T& b) throw() {
		return detail::VectorOr<T>::Execute<instruction_set>(a, b);
	}
}


template<class T, size_t size>
ANVIL_STRONG_INLINE anvil::detail::BasicVector<T, size> operator|(const anvil::detail::BasicVector<T, size>& a, const anvil::detail::BasicVector<T, size>& b) throw() {
	return anvil::VectorOr<anvil::ASM_MINIMUM, anvil::detail::BasicVector<T, size>>(a, b);
}

#endif

//// -- f64 --
//
//#ifndef _simd_f64x1_or_safe
//	#define _simd_f64x1_or_safe(X,Y) X
//	#define _simd_f64x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_f64x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_or_enabled() true
//#endif
//
//#define _simd_f64x2_or_safe(X,Y)_simd_f64x2_combine_safe(\
//	_simd_f64x1_or_safe(_simd_f64x2_splitlo_safe(X), _simd_ f64x2_splitlo_safe(Y)),\
//	_simd_f64x1_or_safe(_simd_f64x2_splithi_safe(X), _simd_ f64x2_splithi_safe(Y)))
//#ifdef _simd_f64x2_or_
//	#define _simd_f64x2_or(X,Y) _simd_f64x2_or_(X, Y)
//	#define _simd_f64x2_or_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_or_instruction_set>()
//#elif defined(_simd_f64x4_or_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_or(const register _simd_f64x2 x, const register _simd_f64x2 y) {
//		union SIMDUnion { _simd_f64x2 v1; _simd_f64x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x4_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x2_or_enable() _simd_f64x4_or_enable()
//#elif defined(_simd_f64x8_or_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_or(const register _simd_f64x2 x, const register _simd_f64x2 y) {
//		union SIMDUnion { _simd_f64x2 v1; _simd_f64x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x8_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x2_or_enable() _simd_f64x8_or_enable()
//#elif defined(_simd_f64x16_or_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_or(const register _simd_f64x2 x, const register _simd_f64x2 y) {
//		union SIMDUnion { _simd_f64x2 v1; _simd_f64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x16_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x2_or_enable() _simd_f64x16_or_enable()
//#elif defined(_simd_f64x32_or_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_or(const register _simd_f64x2 x, const register _simd_f64x2 y) {
//		union SIMDUnion { _simd_f64x2 v1; _simd_f64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x2_or_enable() _simd_f64x32_or_enable()
//#elif defined(_simd_f64x64_or_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_or(const register _simd_f64x2 x, const register _simd_f64x2 y) {
//		union SIMDUnion { _simd_f64x2 v1; _simd_f64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x2_or_enable() _simd_f64x64_or_enable()
//#else
//	#define _simd_f64x2_or(X,Y) _simd_f64x2_combine(\
//		_simd_f64x1_or(_simd_f64x2_splitlo(X), _simd_f64x2_splitlo(Y)),\
//		_simd_f64x1_or(_simd_f64x2_splithi(X), _simd_f64x2_splithi(Y)))
//	#define _simd_f64x2_or_enable() (_simd_f64x1_or_enable() && _simd_f64x2_combine_enable() && _simd_f64x2_splitlo_enable()  && _simd_f64x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x2_or_) && ! defined(_simd_f64x2_or_scalar_)
//	#define _simd_f64x2_or_scalar_(X,Y) _simd_f64x2_or_(X,_simd_f64x2_fill_scalar_(Y))
//	#define _simd_f64x2_or_scalar_instruction_set _simd_f64x2_or_instruction_set
//#endif
//#ifdef _simd_f64x2_or_scalar_
//	#define _simd_f64x2_or_scalar(X,Y) _simd_f64x2_or_scalar_(X,Y)
//	#define _simd_f64x2_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_or_scalar_instruction_set>()
//#else
//	#define _simd_f64x2_or_scalar(X,Y) _simd_f64x2_or_safe(X,_simd_f64x2_fill_scalar_safe(Y))
//	#define _simd_f64x2_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_f64x1_or_safe
//	#define _simd_f64x1_or_safe(X,Y) X
//	#define _simd_f64x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_f64x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_or_enabled() true
//#endif
//
//#define _simd_f64x4_or_safe(X,Y)_simd_f64x4_combine_safe(\
//	_simd_f64x2_or_safe(_simd_f64x4_splitlo_safe(X), _simd_ f64x4_splitlo_safe(Y)),\
//	_simd_f64x2_or_safe(_simd_f64x4_splithi_safe(X), _simd_ f64x4_splithi_safe(Y)))
//#ifdef _simd_f64x4_or_
//	#define _simd_f64x4_or(X,Y) _simd_f64x4_or_(X, Y)
//	#define _simd_f64x4_or_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_or_instruction_set>()
//#elif defined(_simd_f64x8_or_)
//	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_or(const register _simd_f64x4 x, const register _simd_f64x4 y) {
//		union SIMDUnion { _simd_f64x4 v1; _simd_f64x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x8_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x4_or_enable() _simd_f64x8_or_enable()
//#elif defined(_simd_f64x16_or_)
//	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_or(const register _simd_f64x4 x, const register _simd_f64x4 y) {
//		union SIMDUnion { _simd_f64x4 v1; _simd_f64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x16_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x4_or_enable() _simd_f64x16_or_enable()
//#elif defined(_simd_f64x32_or_)
//	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_or(const register _simd_f64x4 x, const register _simd_f64x4 y) {
//		union SIMDUnion { _simd_f64x4 v1; _simd_f64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x4_or_enable() _simd_f64x32_or_enable()
//#elif defined(_simd_f64x64_or_)
//	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_or(const register _simd_f64x4 x, const register _simd_f64x4 y) {
//		union SIMDUnion { _simd_f64x4 v1; _simd_f64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x4_or_enable() _simd_f64x64_or_enable()
//#else
//	#define _simd_f64x4_or(X,Y) _simd_f64x4_combine(\
//		_simd_f64x2_or(_simd_f64x4_splitlo(X), _simd_f64x4_splitlo(Y)),\
//		_simd_f64x2_or(_simd_f64x4_splithi(X), _simd_f64x4_splithi(Y)))
//	#define _simd_f64x4_or_enable() (_simd_f64x2_or_enable() && _simd_f64x4_combine_enable() && _simd_f64x4_splitlo_enable()  && _simd_f64x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x4_or_) && ! defined(_simd_f64x4_or_scalar_)
//	#define _simd_f64x4_or_scalar_(X,Y) _simd_f64x4_or_(X,_simd_f64x4_fill_scalar_(Y))
//	#define _simd_f64x4_or_scalar_instruction_set _simd_f64x4_or_instruction_set
//#endif
//#ifdef _simd_f64x4_or_scalar_
//	#define _simd_f64x4_or_scalar(X,Y) _simd_f64x4_or_scalar_(X,Y)
//	#define _simd_f64x4_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_or_scalar_instruction_set>()
//#else
//	#define _simd_f64x4_or_scalar(X,Y) _simd_f64x4_or_safe(X,_simd_f64x4_fill_scalar_safe(Y))
//	#define _simd_f64x4_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_f64x1_or_safe
//	#define _simd_f64x1_or_safe(X,Y) X
//	#define _simd_f64x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_f64x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_or_enabled() true
//#endif
//
//#define _simd_f64x8_or_safe(X,Y)_simd_f64x8_combine_safe(\
//	_simd_f64x4_or_safe(_simd_f64x8_splitlo_safe(X), _simd_ f64x8_splitlo_safe(Y)),\
//	_simd_f64x4_or_safe(_simd_f64x8_splithi_safe(X), _simd_ f64x8_splithi_safe(Y)))
//#ifdef _simd_f64x8_or_
//	#define _simd_f64x8_or(X,Y) _simd_f64x8_or_(X, Y)
//	#define _simd_f64x8_or_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_or_instruction_set>()
//#elif defined(_simd_f64x16_or_)
//	static ANVIL_STRONG_INLINE _simd_f64x8 ANVIL_SIMD_CALL _simd_f64x8_or(const register _simd_f64x8 x, const register _simd_f64x8 y) {
//		union SIMDUnion { _simd_f64x8 v1; _simd_f64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x16_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x8_or_enable() _simd_f64x16_or_enable()
//#elif defined(_simd_f64x32_or_)
//	static ANVIL_STRONG_INLINE _simd_f64x8 ANVIL_SIMD_CALL _simd_f64x8_or(const register _simd_f64x8 x, const register _simd_f64x8 y) {
//		union SIMDUnion { _simd_f64x8 v1; _simd_f64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x8_or_enable() _simd_f64x32_or_enable()
//#elif defined(_simd_f64x64_or_)
//	static ANVIL_STRONG_INLINE _simd_f64x8 ANVIL_SIMD_CALL _simd_f64x8_or(const register _simd_f64x8 x, const register _simd_f64x8 y) {
//		union SIMDUnion { _simd_f64x8 v1; _simd_f64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x8_or_enable() _simd_f64x64_or_enable()
//#else
//	#define _simd_f64x8_or(X,Y) _simd_f64x8_combine(\
//		_simd_f64x4_or(_simd_f64x8_splitlo(X), _simd_f64x8_splitlo(Y)),\
//		_simd_f64x4_or(_simd_f64x8_splithi(X), _simd_f64x8_splithi(Y)))
//	#define _simd_f64x8_or_enable() (_simd_f64x4_or_enable() && _simd_f64x8_combine_enable() && _simd_f64x8_splitlo_enable()  && _simd_f64x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x8_or_) && ! defined(_simd_f64x8_or_scalar_)
//	#define _simd_f64x8_or_scalar_(X,Y) _simd_f64x8_or_(X,_simd_f64x8_fill_scalar_(Y))
//	#define _simd_f64x8_or_scalar_instruction_set _simd_f64x8_or_instruction_set
//#endif
//#ifdef _simd_f64x8_or_scalar_
//	#define _simd_f64x8_or_scalar(X,Y) _simd_f64x8_or_scalar_(X,Y)
//	#define _simd_f64x8_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_or_scalar_instruction_set>()
//#else
//	#define _simd_f64x8_or_scalar(X,Y) _simd_f64x8_or_safe(X,_simd_f64x8_fill_scalar_safe(Y))
//	#define _simd_f64x8_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_f64x1_or_safe
//	#define _simd_f64x1_or_safe(X,Y) X
//	#define _simd_f64x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_f64x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_or_enabled() true
//#endif
//
//#define _simd_f64x16_or_safe(X,Y)_simd_f64x16_combine_safe(\
//	_simd_f64x8_or_safe(_simd_f64x16_splitlo_safe(X), _simd_ f64x16_splitlo_safe(Y)),\
//	_simd_f64x8_or_safe(_simd_f64x16_splithi_safe(X), _simd_ f64x16_splithi_safe(Y)))
//#ifdef _simd_f64x16_or_
//	#define _simd_f64x16_or(X,Y) _simd_f64x16_or_(X, Y)
//	#define _simd_f64x16_or_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_or_instruction_set>()
//#elif defined(_simd_f64x32_or_)
//	static ANVIL_STRONG_INLINE _simd_f64x16 ANVIL_SIMD_CALL _simd_f64x16_or(const register _simd_f64x16 x, const register _simd_f64x16 y) {
//		union SIMDUnion { _simd_f64x16 v1; _simd_f64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x16_or_enable() _simd_f64x32_or_enable()
//#elif defined(_simd_f64x64_or_)
//	static ANVIL_STRONG_INLINE _simd_f64x16 ANVIL_SIMD_CALL _simd_f64x16_or(const register _simd_f64x16 x, const register _simd_f64x16 y) {
//		union SIMDUnion { _simd_f64x16 v1; _simd_f64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x16_or_enable() _simd_f64x64_or_enable()
//#else
//	#define _simd_f64x16_or(X,Y) _simd_f64x16_combine(\
//		_simd_f64x8_or(_simd_f64x16_splitlo(X), _simd_f64x16_splitlo(Y)),\
//		_simd_f64x8_or(_simd_f64x16_splithi(X), _simd_f64x16_splithi(Y)))
//	#define _simd_f64x16_or_enable() (_simd_f64x8_or_enable() && _simd_f64x16_combine_enable() && _simd_f64x16_splitlo_enable()  && _simd_f64x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x16_or_) && ! defined(_simd_f64x16_or_scalar_)
//	#define _simd_f64x16_or_scalar_(X,Y) _simd_f64x16_or_(X,_simd_f64x16_fill_scalar_(Y))
//	#define _simd_f64x16_or_scalar_instruction_set _simd_f64x16_or_instruction_set
//#endif
//#ifdef _simd_f64x16_or_scalar_
//	#define _simd_f64x16_or_scalar(X,Y) _simd_f64x16_or_scalar_(X,Y)
//	#define _simd_f64x16_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_or_scalar_instruction_set>()
//#else
//	#define _simd_f64x16_or_scalar(X,Y) _simd_f64x16_or_safe(X,_simd_f64x16_fill_scalar_safe(Y))
//	#define _simd_f64x16_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_f64x1_or_safe
//	#define _simd_f64x1_or_safe(X,Y) X
//	#define _simd_f64x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_f64x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_or_enabled() true
//#endif
//
//#define _simd_f64x32_or_safe(X,Y)_simd_f64x32_combine_safe(\
//	_simd_f64x16_or_safe(_simd_f64x32_splitlo_safe(X), _simd_ f64x32_splitlo_safe(Y)),\
//	_simd_f64x16_or_safe(_simd_f64x32_splithi_safe(X), _simd_ f64x32_splithi_safe(Y)))
//#ifdef _simd_f64x32_or_
//	#define _simd_f64x32_or(X,Y) _simd_f64x32_or_(X, Y)
//	#define _simd_f64x32_or_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_or_instruction_set>()
//#elif defined(_simd_f64x64_or_)
//	static ANVIL_STRONG_INLINE _simd_f64x32 ANVIL_SIMD_CALL _simd_f64x32_or(const register _simd_f64x32 x, const register _simd_f64x32 y) {
//		union SIMDUnion { _simd_f64x32 v1; _simd_f64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x32_or_enable() _simd_f64x64_or_enable()
//#else
//	#define _simd_f64x32_or(X,Y) _simd_f64x32_combine(\
//		_simd_f64x16_or(_simd_f64x32_splitlo(X), _simd_f64x32_splitlo(Y)),\
//		_simd_f64x16_or(_simd_f64x32_splithi(X), _simd_f64x32_splithi(Y)))
//	#define _simd_f64x32_or_enable() (_simd_f64x16_or_enable() && _simd_f64x32_combine_enable() && _simd_f64x32_splitlo_enable()  && _simd_f64x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x32_or_) && ! defined(_simd_f64x32_or_scalar_)
//	#define _simd_f64x32_or_scalar_(X,Y) _simd_f64x32_or_(X,_simd_f64x32_fill_scalar_(Y))
//	#define _simd_f64x32_or_scalar_instruction_set _simd_f64x32_or_instruction_set
//#endif
//#ifdef _simd_f64x32_or_scalar_
//	#define _simd_f64x32_or_scalar(X,Y) _simd_f64x32_or_scalar_(X,Y)
//	#define _simd_f64x32_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_or_scalar_instruction_set>()
//#else
//	#define _simd_f64x32_or_scalar(X,Y) _simd_f64x32_or_safe(X,_simd_f64x32_fill_scalar_safe(Y))
//	#define _simd_f64x32_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_f64x1_or_safe
//	#define _simd_f64x1_or_safe(X,Y) X
//	#define _simd_f64x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_f64x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_or_enabled() true
//#endif
//
//#define _simd_f64x64_or_safe(X,Y)_simd_f64x64_combine_safe(\
//	_simd_f64x32_or_safe(_simd_f64x64_splitlo_safe(X), _simd_ f64x64_splitlo_safe(Y)),\
//	_simd_f64x32_or_safe(_simd_f64x64_splithi_safe(X), _simd_ f64x64_splithi_safe(Y)))
//#ifdef _simd_f64x64_or_
//	#define _simd_f64x64_or(X,Y) _simd_f64x64_or_(X, Y)
//	#define _simd_f64x64_or_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_or_instruction_set>()
//#else
//	#define _simd_f64x64_or(X,Y) _simd_f64x64_combine(\
//		_simd_f64x32_or(_simd_f64x64_splitlo(X), _simd_f64x64_splitlo(Y)),\
//		_simd_f64x32_or(_simd_f64x64_splithi(X), _simd_f64x64_splithi(Y)))
//	#define _simd_f64x64_or_enable() (_simd_f64x32_or_enable() && _simd_f64x64_combine_enable() && _simd_f64x64_splitlo_enable()  && _simd_f64x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x64_or_) && ! defined(_simd_f64x64_or_scalar_)
//	#define _simd_f64x64_or_scalar_(X,Y) _simd_f64x64_or_(X,_simd_f64x64_fill_scalar_(Y))
//	#define _simd_f64x64_or_scalar_instruction_set _simd_f64x64_or_instruction_set
//#endif
//#ifdef _simd_f64x64_or_scalar_
//	#define _simd_f64x64_or_scalar(X,Y) _simd_f64x64_or_scalar_(X,Y)
//	#define _simd_f64x64_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_or_scalar_instruction_set>()
//#else
//	#define _simd_f64x64_or_scalar(X,Y) _simd_f64x64_or_safe(X,_simd_f64x64_fill_scalar_safe(Y))
//	#define _simd_f64x64_or_scalar_enabled() true
//#endif
//
//// -- f32 --
//
//#ifndef _simd_f32x1_or_safe
//	#define _simd_f32x1_or_safe(X,Y) X
//	#define _simd_f32x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_f32x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_or_enabled() true
//#endif
//
//#define _simd_f32x2_or_safe(X,Y)_simd_f32x2_combine_safe(\
//	_simd_f32x1_or_safe(_simd_f32x2_splitlo_safe(X), _simd_ f32x2_splitlo_safe(Y)),\
//	_simd_f32x1_or_safe(_simd_f32x2_splithi_safe(X), _simd_ f32x2_splithi_safe(Y)))
//#ifdef _simd_f32x2_or_
//	#define _simd_f32x2_or(X,Y) _simd_f32x2_or_(X, Y)
//	#define _simd_f32x2_or_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_or_instruction_set>()
//#elif defined(_simd_f32x4_or_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_or(const register _simd_f32x2 x, const register _simd_f32x2 y) {
//		union SIMDUnion { _simd_f32x2 v1; _simd_f32x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x4_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x2_or_enable() _simd_f32x4_or_enable()
//#elif defined(_simd_f32x8_or_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_or(const register _simd_f32x2 x, const register _simd_f32x2 y) {
//		union SIMDUnion { _simd_f32x2 v1; _simd_f32x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x8_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x2_or_enable() _simd_f32x8_or_enable()
//#elif defined(_simd_f32x16_or_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_or(const register _simd_f32x2 x, const register _simd_f32x2 y) {
//		union SIMDUnion { _simd_f32x2 v1; _simd_f32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x16_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x2_or_enable() _simd_f32x16_or_enable()
//#elif defined(_simd_f32x32_or_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_or(const register _simd_f32x2 x, const register _simd_f32x2 y) {
//		union SIMDUnion { _simd_f32x2 v1; _simd_f32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x2_or_enable() _simd_f32x32_or_enable()
//#elif defined(_simd_f32x64_or_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_or(const register _simd_f32x2 x, const register _simd_f32x2 y) {
//		union SIMDUnion { _simd_f32x2 v1; _simd_f32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x2_or_enable() _simd_f32x64_or_enable()
//#else
//	#define _simd_f32x2_or(X,Y) _simd_f32x2_combine(\
//		_simd_f32x1_or(_simd_f32x2_splitlo(X), _simd_f32x2_splitlo(Y)),\
//		_simd_f32x1_or(_simd_f32x2_splithi(X), _simd_f32x2_splithi(Y)))
//	#define _simd_f32x2_or_enable() (_simd_f32x1_or_enable() && _simd_f32x2_combine_enable() && _simd_f32x2_splitlo_enable()  && _simd_f32x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x2_or_) && ! defined(_simd_f32x2_or_scalar_)
//	#define _simd_f32x2_or_scalar_(X,Y) _simd_f32x2_or_(X,_simd_f32x2_fill_scalar_(Y))
//	#define _simd_f32x2_or_scalar_instruction_set _simd_f32x2_or_instruction_set
//#endif
//#ifdef _simd_f32x2_or_scalar_
//	#define _simd_f32x2_or_scalar(X,Y) _simd_f32x2_or_scalar_(X,Y)
//	#define _simd_f32x2_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_or_scalar_instruction_set>()
//#else
//	#define _simd_f32x2_or_scalar(X,Y) _simd_f32x2_or_safe(X,_simd_f32x2_fill_scalar_safe(Y))
//	#define _simd_f32x2_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_f32x1_or_safe
//	#define _simd_f32x1_or_safe(X,Y) X
//	#define _simd_f32x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_f32x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_or_enabled() true
//#endif
//
//#define _simd_f32x4_or_safe(X,Y)_simd_f32x4_combine_safe(\
//	_simd_f32x2_or_safe(_simd_f32x4_splitlo_safe(X), _simd_ f32x4_splitlo_safe(Y)),\
//	_simd_f32x2_or_safe(_simd_f32x4_splithi_safe(X), _simd_ f32x4_splithi_safe(Y)))
//#ifdef _simd_f32x4_or_
//	#define _simd_f32x4_or(X,Y) _simd_f32x4_or_(X, Y)
//	#define _simd_f32x4_or_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_or_instruction_set>()
//#elif defined(_simd_f32x8_or_)
//	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_or(const register _simd_f32x4 x, const register _simd_f32x4 y) {
//		union SIMDUnion { _simd_f32x4 v1; _simd_f32x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x8_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x4_or_enable() _simd_f32x8_or_enable()
//#elif defined(_simd_f32x16_or_)
//	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_or(const register _simd_f32x4 x, const register _simd_f32x4 y) {
//		union SIMDUnion { _simd_f32x4 v1; _simd_f32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x16_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x4_or_enable() _simd_f32x16_or_enable()
//#elif defined(_simd_f32x32_or_)
//	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_or(const register _simd_f32x4 x, const register _simd_f32x4 y) {
//		union SIMDUnion { _simd_f32x4 v1; _simd_f32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x4_or_enable() _simd_f32x32_or_enable()
//#elif defined(_simd_f32x64_or_)
//	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_or(const register _simd_f32x4 x, const register _simd_f32x4 y) {
//		union SIMDUnion { _simd_f32x4 v1; _simd_f32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x4_or_enable() _simd_f32x64_or_enable()
//#else
//	#define _simd_f32x4_or(X,Y) _simd_f32x4_combine(\
//		_simd_f32x2_or(_simd_f32x4_splitlo(X), _simd_f32x4_splitlo(Y)),\
//		_simd_f32x2_or(_simd_f32x4_splithi(X), _simd_f32x4_splithi(Y)))
//	#define _simd_f32x4_or_enable() (_simd_f32x2_or_enable() && _simd_f32x4_combine_enable() && _simd_f32x4_splitlo_enable()  && _simd_f32x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x4_or_) && ! defined(_simd_f32x4_or_scalar_)
//	#define _simd_f32x4_or_scalar_(X,Y) _simd_f32x4_or_(X,_simd_f32x4_fill_scalar_(Y))
//	#define _simd_f32x4_or_scalar_instruction_set _simd_f32x4_or_instruction_set
//#endif
//#ifdef _simd_f32x4_or_scalar_
//	#define _simd_f32x4_or_scalar(X,Y) _simd_f32x4_or_scalar_(X,Y)
//	#define _simd_f32x4_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_or_scalar_instruction_set>()
//#else
//	#define _simd_f32x4_or_scalar(X,Y) _simd_f32x4_or_safe(X,_simd_f32x4_fill_scalar_safe(Y))
//	#define _simd_f32x4_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_f32x1_or_safe
//	#define _simd_f32x1_or_safe(X,Y) X
//	#define _simd_f32x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_f32x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_or_enabled() true
//#endif
//
//#define _simd_f32x8_or_safe(X,Y)_simd_f32x8_combine_safe(\
//	_simd_f32x4_or_safe(_simd_f32x8_splitlo_safe(X), _simd_ f32x8_splitlo_safe(Y)),\
//	_simd_f32x4_or_safe(_simd_f32x8_splithi_safe(X), _simd_ f32x8_splithi_safe(Y)))
//#ifdef _simd_f32x8_or_
//	#define _simd_f32x8_or(X,Y) _simd_f32x8_or_(X, Y)
//	#define _simd_f32x8_or_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_or_instruction_set>()
//#elif defined(_simd_f32x16_or_)
//	static ANVIL_STRONG_INLINE _simd_f32x8 ANVIL_SIMD_CALL _simd_f32x8_or(const register _simd_f32x8 x, const register _simd_f32x8 y) {
//		union SIMDUnion { _simd_f32x8 v1; _simd_f32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x16_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x8_or_enable() _simd_f32x16_or_enable()
//#elif defined(_simd_f32x32_or_)
//	static ANVIL_STRONG_INLINE _simd_f32x8 ANVIL_SIMD_CALL _simd_f32x8_or(const register _simd_f32x8 x, const register _simd_f32x8 y) {
//		union SIMDUnion { _simd_f32x8 v1; _simd_f32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x8_or_enable() _simd_f32x32_or_enable()
//#elif defined(_simd_f32x64_or_)
//	static ANVIL_STRONG_INLINE _simd_f32x8 ANVIL_SIMD_CALL _simd_f32x8_or(const register _simd_f32x8 x, const register _simd_f32x8 y) {
//		union SIMDUnion { _simd_f32x8 v1; _simd_f32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x8_or_enable() _simd_f32x64_or_enable()
//#else
//	#define _simd_f32x8_or(X,Y) _simd_f32x8_combine(\
//		_simd_f32x4_or(_simd_f32x8_splitlo(X), _simd_f32x8_splitlo(Y)),\
//		_simd_f32x4_or(_simd_f32x8_splithi(X), _simd_f32x8_splithi(Y)))
//	#define _simd_f32x8_or_enable() (_simd_f32x4_or_enable() && _simd_f32x8_combine_enable() && _simd_f32x8_splitlo_enable()  && _simd_f32x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x8_or_) && ! defined(_simd_f32x8_or_scalar_)
//	#define _simd_f32x8_or_scalar_(X,Y) _simd_f32x8_or_(X,_simd_f32x8_fill_scalar_(Y))
//	#define _simd_f32x8_or_scalar_instruction_set _simd_f32x8_or_instruction_set
//#endif
//#ifdef _simd_f32x8_or_scalar_
//	#define _simd_f32x8_or_scalar(X,Y) _simd_f32x8_or_scalar_(X,Y)
//	#define _simd_f32x8_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_or_scalar_instruction_set>()
//#else
//	#define _simd_f32x8_or_scalar(X,Y) _simd_f32x8_or_safe(X,_simd_f32x8_fill_scalar_safe(Y))
//	#define _simd_f32x8_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_f32x1_or_safe
//	#define _simd_f32x1_or_safe(X,Y) X
//	#define _simd_f32x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_f32x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_or_enabled() true
//#endif
//
//#define _simd_f32x16_or_safe(X,Y)_simd_f32x16_combine_safe(\
//	_simd_f32x8_or_safe(_simd_f32x16_splitlo_safe(X), _simd_ f32x16_splitlo_safe(Y)),\
//	_simd_f32x8_or_safe(_simd_f32x16_splithi_safe(X), _simd_ f32x16_splithi_safe(Y)))
//#ifdef _simd_f32x16_or_
//	#define _simd_f32x16_or(X,Y) _simd_f32x16_or_(X, Y)
//	#define _simd_f32x16_or_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_or_instruction_set>()
//#elif defined(_simd_f32x32_or_)
//	static ANVIL_STRONG_INLINE _simd_f32x16 ANVIL_SIMD_CALL _simd_f32x16_or(const register _simd_f32x16 x, const register _simd_f32x16 y) {
//		union SIMDUnion { _simd_f32x16 v1; _simd_f32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x16_or_enable() _simd_f32x32_or_enable()
//#elif defined(_simd_f32x64_or_)
//	static ANVIL_STRONG_INLINE _simd_f32x16 ANVIL_SIMD_CALL _simd_f32x16_or(const register _simd_f32x16 x, const register _simd_f32x16 y) {
//		union SIMDUnion { _simd_f32x16 v1; _simd_f32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x16_or_enable() _simd_f32x64_or_enable()
//#else
//	#define _simd_f32x16_or(X,Y) _simd_f32x16_combine(\
//		_simd_f32x8_or(_simd_f32x16_splitlo(X), _simd_f32x16_splitlo(Y)),\
//		_simd_f32x8_or(_simd_f32x16_splithi(X), _simd_f32x16_splithi(Y)))
//	#define _simd_f32x16_or_enable() (_simd_f32x8_or_enable() && _simd_f32x16_combine_enable() && _simd_f32x16_splitlo_enable()  && _simd_f32x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x16_or_) && ! defined(_simd_f32x16_or_scalar_)
//	#define _simd_f32x16_or_scalar_(X,Y) _simd_f32x16_or_(X,_simd_f32x16_fill_scalar_(Y))
//	#define _simd_f32x16_or_scalar_instruction_set _simd_f32x16_or_instruction_set
//#endif
//#ifdef _simd_f32x16_or_scalar_
//	#define _simd_f32x16_or_scalar(X,Y) _simd_f32x16_or_scalar_(X,Y)
//	#define _simd_f32x16_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_or_scalar_instruction_set>()
//#else
//	#define _simd_f32x16_or_scalar(X,Y) _simd_f32x16_or_safe(X,_simd_f32x16_fill_scalar_safe(Y))
//	#define _simd_f32x16_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_f32x1_or_safe
//	#define _simd_f32x1_or_safe(X,Y) X
//	#define _simd_f32x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_f32x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_or_enabled() true
//#endif
//
//#define _simd_f32x32_or_safe(X,Y)_simd_f32x32_combine_safe(\
//	_simd_f32x16_or_safe(_simd_f32x32_splitlo_safe(X), _simd_ f32x32_splitlo_safe(Y)),\
//	_simd_f32x16_or_safe(_simd_f32x32_splithi_safe(X), _simd_ f32x32_splithi_safe(Y)))
//#ifdef _simd_f32x32_or_
//	#define _simd_f32x32_or(X,Y) _simd_f32x32_or_(X, Y)
//	#define _simd_f32x32_or_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_or_instruction_set>()
//#elif defined(_simd_f32x64_or_)
//	static ANVIL_STRONG_INLINE _simd_f32x32 ANVIL_SIMD_CALL _simd_f32x32_or(const register _simd_f32x32 x, const register _simd_f32x32 y) {
//		union SIMDUnion { _simd_f32x32 v1; _simd_f32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x32_or_enable() _simd_f32x64_or_enable()
//#else
//	#define _simd_f32x32_or(X,Y) _simd_f32x32_combine(\
//		_simd_f32x16_or(_simd_f32x32_splitlo(X), _simd_f32x32_splitlo(Y)),\
//		_simd_f32x16_or(_simd_f32x32_splithi(X), _simd_f32x32_splithi(Y)))
//	#define _simd_f32x32_or_enable() (_simd_f32x16_or_enable() && _simd_f32x32_combine_enable() && _simd_f32x32_splitlo_enable()  && _simd_f32x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x32_or_) && ! defined(_simd_f32x32_or_scalar_)
//	#define _simd_f32x32_or_scalar_(X,Y) _simd_f32x32_or_(X,_simd_f32x32_fill_scalar_(Y))
//	#define _simd_f32x32_or_scalar_instruction_set _simd_f32x32_or_instruction_set
//#endif
//#ifdef _simd_f32x32_or_scalar_
//	#define _simd_f32x32_or_scalar(X,Y) _simd_f32x32_or_scalar_(X,Y)
//	#define _simd_f32x32_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_or_scalar_instruction_set>()
//#else
//	#define _simd_f32x32_or_scalar(X,Y) _simd_f32x32_or_safe(X,_simd_f32x32_fill_scalar_safe(Y))
//	#define _simd_f32x32_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_f32x1_or_safe
//	#define _simd_f32x1_or_safe(X,Y) X
//	#define _simd_f32x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_f32x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_or_enabled() true
//#endif
//
//#define _simd_f32x64_or_safe(X,Y)_simd_f32x64_combine_safe(\
//	_simd_f32x32_or_safe(_simd_f32x64_splitlo_safe(X), _simd_ f32x64_splitlo_safe(Y)),\
//	_simd_f32x32_or_safe(_simd_f32x64_splithi_safe(X), _simd_ f32x64_splithi_safe(Y)))
//#ifdef _simd_f32x64_or_
//	#define _simd_f32x64_or(X,Y) _simd_f32x64_or_(X, Y)
//	#define _simd_f32x64_or_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_or_instruction_set>()
//#else
//	#define _simd_f32x64_or(X,Y) _simd_f32x64_combine(\
//		_simd_f32x32_or(_simd_f32x64_splitlo(X), _simd_f32x64_splitlo(Y)),\
//		_simd_f32x32_or(_simd_f32x64_splithi(X), _simd_f32x64_splithi(Y)))
//	#define _simd_f32x64_or_enable() (_simd_f32x32_or_enable() && _simd_f32x64_combine_enable() && _simd_f32x64_splitlo_enable()  && _simd_f32x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x64_or_) && ! defined(_simd_f32x64_or_scalar_)
//	#define _simd_f32x64_or_scalar_(X,Y) _simd_f32x64_or_(X,_simd_f32x64_fill_scalar_(Y))
//	#define _simd_f32x64_or_scalar_instruction_set _simd_f32x64_or_instruction_set
//#endif
//#ifdef _simd_f32x64_or_scalar_
//	#define _simd_f32x64_or_scalar(X,Y) _simd_f32x64_or_scalar_(X,Y)
//	#define _simd_f32x64_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_or_scalar_instruction_set>()
//#else
//	#define _simd_f32x64_or_scalar(X,Y) _simd_f32x64_or_safe(X,_simd_f32x64_fill_scalar_safe(Y))
//	#define _simd_f32x64_or_scalar_enabled() true
//#endif
//
//// -- s64 --
//
//#ifndef _simd_s64x1_or_safe
//	#define _simd_s64x1_or_safe(X,Y) (X | Y)
//	#define _simd_s64x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_s64x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_or_enabled() true
//#endif
//
//#define _simd_s64x2_or_safe(X,Y)_simd_s64x2_combine_safe(\
//	_simd_s64x1_or_safe(_simd_s64x2_splitlo_safe(X), _simd_ s64x2_splitlo_safe(Y)),\
//	_simd_s64x1_or_safe(_simd_s64x2_splithi_safe(X), _simd_ s64x2_splithi_safe(Y)))
//#ifdef _simd_s64x2_or_
//	#define _simd_s64x2_or(X,Y) _simd_s64x2_or_(X, Y)
//	#define _simd_s64x2_or_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_or_instruction_set>()
//#elif defined(_simd_s64x4_or_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_or(const register _simd_s64x2 x, const register _simd_s64x2 y) {
//		union SIMDUnion { _simd_s64x2 v1; _simd_s64x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x4_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x2_or_enable() _simd_s64x4_or_enable()
//#elif defined(_simd_s64x8_or_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_or(const register _simd_s64x2 x, const register _simd_s64x2 y) {
//		union SIMDUnion { _simd_s64x2 v1; _simd_s64x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x8_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x2_or_enable() _simd_s64x8_or_enable()
//#elif defined(_simd_s64x16_or_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_or(const register _simd_s64x2 x, const register _simd_s64x2 y) {
//		union SIMDUnion { _simd_s64x2 v1; _simd_s64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x16_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x2_or_enable() _simd_s64x16_or_enable()
//#elif defined(_simd_s64x32_or_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_or(const register _simd_s64x2 x, const register _simd_s64x2 y) {
//		union SIMDUnion { _simd_s64x2 v1; _simd_s64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x2_or_enable() _simd_s64x32_or_enable()
//#elif defined(_simd_s64x64_or_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_or(const register _simd_s64x2 x, const register _simd_s64x2 y) {
//		union SIMDUnion { _simd_s64x2 v1; _simd_s64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x2_or_enable() _simd_s64x64_or_enable()
//#else
//	#define _simd_s64x2_or(X,Y) _simd_s64x2_combine(\
//		_simd_s64x1_or(_simd_s64x2_splitlo(X), _simd_s64x2_splitlo(Y)),\
//		_simd_s64x1_or(_simd_s64x2_splithi(X), _simd_s64x2_splithi(Y)))
//	#define _simd_s64x2_or_enable() (_simd_s64x1_or_enable() && _simd_s64x2_combine_enable() && _simd_s64x2_splitlo_enable()  && _simd_s64x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x2_or_) && ! defined(_simd_s64x2_or_scalar_)
//	#define _simd_s64x2_or_scalar_(X,Y) _simd_s64x2_or_(X,_simd_s64x2_fill_scalar_(Y))
//	#define _simd_s64x2_or_scalar_instruction_set _simd_s64x2_or_instruction_set
//#endif
//#ifdef _simd_s64x2_or_scalar_
//	#define _simd_s64x2_or_scalar(X,Y) _simd_s64x2_or_scalar_(X,Y)
//	#define _simd_s64x2_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_or_scalar_instruction_set>()
//#else
//	#define _simd_s64x2_or_scalar(X,Y) _simd_s64x2_or_safe(X,_simd_s64x2_fill_scalar_safe(Y))
//	#define _simd_s64x2_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_s64x1_or_safe
//	#define _simd_s64x1_or_safe(X,Y) (X | Y)
//	#define _simd_s64x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_s64x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_or_enabled() true
//#endif
//
//#define _simd_s64x4_or_safe(X,Y)_simd_s64x4_combine_safe(\
//	_simd_s64x2_or_safe(_simd_s64x4_splitlo_safe(X), _simd_ s64x4_splitlo_safe(Y)),\
//	_simd_s64x2_or_safe(_simd_s64x4_splithi_safe(X), _simd_ s64x4_splithi_safe(Y)))
//#ifdef _simd_s64x4_or_
//	#define _simd_s64x4_or(X,Y) _simd_s64x4_or_(X, Y)
//	#define _simd_s64x4_or_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_or_instruction_set>()
//#elif defined(_simd_s64x8_or_)
//	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_or(const register _simd_s64x4 x, const register _simd_s64x4 y) {
//		union SIMDUnion { _simd_s64x4 v1; _simd_s64x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x8_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x4_or_enable() _simd_s64x8_or_enable()
//#elif defined(_simd_s64x16_or_)
//	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_or(const register _simd_s64x4 x, const register _simd_s64x4 y) {
//		union SIMDUnion { _simd_s64x4 v1; _simd_s64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x16_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x4_or_enable() _simd_s64x16_or_enable()
//#elif defined(_simd_s64x32_or_)
//	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_or(const register _simd_s64x4 x, const register _simd_s64x4 y) {
//		union SIMDUnion { _simd_s64x4 v1; _simd_s64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x4_or_enable() _simd_s64x32_or_enable()
//#elif defined(_simd_s64x64_or_)
//	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_or(const register _simd_s64x4 x, const register _simd_s64x4 y) {
//		union SIMDUnion { _simd_s64x4 v1; _simd_s64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x4_or_enable() _simd_s64x64_or_enable()
//#else
//	#define _simd_s64x4_or(X,Y) _simd_s64x4_combine(\
//		_simd_s64x2_or(_simd_s64x4_splitlo(X), _simd_s64x4_splitlo(Y)),\
//		_simd_s64x2_or(_simd_s64x4_splithi(X), _simd_s64x4_splithi(Y)))
//	#define _simd_s64x4_or_enable() (_simd_s64x2_or_enable() && _simd_s64x4_combine_enable() && _simd_s64x4_splitlo_enable()  && _simd_s64x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x4_or_) && ! defined(_simd_s64x4_or_scalar_)
//	#define _simd_s64x4_or_scalar_(X,Y) _simd_s64x4_or_(X,_simd_s64x4_fill_scalar_(Y))
//	#define _simd_s64x4_or_scalar_instruction_set _simd_s64x4_or_instruction_set
//#endif
//#ifdef _simd_s64x4_or_scalar_
//	#define _simd_s64x4_or_scalar(X,Y) _simd_s64x4_or_scalar_(X,Y)
//	#define _simd_s64x4_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_or_scalar_instruction_set>()
//#else
//	#define _simd_s64x4_or_scalar(X,Y) _simd_s64x4_or_safe(X,_simd_s64x4_fill_scalar_safe(Y))
//	#define _simd_s64x4_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_s64x1_or_safe
//	#define _simd_s64x1_or_safe(X,Y) (X | Y)
//	#define _simd_s64x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_s64x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_or_enabled() true
//#endif
//
//#define _simd_s64x8_or_safe(X,Y)_simd_s64x8_combine_safe(\
//	_simd_s64x4_or_safe(_simd_s64x8_splitlo_safe(X), _simd_ s64x8_splitlo_safe(Y)),\
//	_simd_s64x4_or_safe(_simd_s64x8_splithi_safe(X), _simd_ s64x8_splithi_safe(Y)))
//#ifdef _simd_s64x8_or_
//	#define _simd_s64x8_or(X,Y) _simd_s64x8_or_(X, Y)
//	#define _simd_s64x8_or_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_or_instruction_set>()
//#elif defined(_simd_s64x16_or_)
//	static ANVIL_STRONG_INLINE _simd_s64x8 ANVIL_SIMD_CALL _simd_s64x8_or(const register _simd_s64x8 x, const register _simd_s64x8 y) {
//		union SIMDUnion { _simd_s64x8 v1; _simd_s64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x16_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x8_or_enable() _simd_s64x16_or_enable()
//#elif defined(_simd_s64x32_or_)
//	static ANVIL_STRONG_INLINE _simd_s64x8 ANVIL_SIMD_CALL _simd_s64x8_or(const register _simd_s64x8 x, const register _simd_s64x8 y) {
//		union SIMDUnion { _simd_s64x8 v1; _simd_s64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x8_or_enable() _simd_s64x32_or_enable()
//#elif defined(_simd_s64x64_or_)
//	static ANVIL_STRONG_INLINE _simd_s64x8 ANVIL_SIMD_CALL _simd_s64x8_or(const register _simd_s64x8 x, const register _simd_s64x8 y) {
//		union SIMDUnion { _simd_s64x8 v1; _simd_s64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x8_or_enable() _simd_s64x64_or_enable()
//#else
//	#define _simd_s64x8_or(X,Y) _simd_s64x8_combine(\
//		_simd_s64x4_or(_simd_s64x8_splitlo(X), _simd_s64x8_splitlo(Y)),\
//		_simd_s64x4_or(_simd_s64x8_splithi(X), _simd_s64x8_splithi(Y)))
//	#define _simd_s64x8_or_enable() (_simd_s64x4_or_enable() && _simd_s64x8_combine_enable() && _simd_s64x8_splitlo_enable()  && _simd_s64x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x8_or_) && ! defined(_simd_s64x8_or_scalar_)
//	#define _simd_s64x8_or_scalar_(X,Y) _simd_s64x8_or_(X,_simd_s64x8_fill_scalar_(Y))
//	#define _simd_s64x8_or_scalar_instruction_set _simd_s64x8_or_instruction_set
//#endif
//#ifdef _simd_s64x8_or_scalar_
//	#define _simd_s64x8_or_scalar(X,Y) _simd_s64x8_or_scalar_(X,Y)
//	#define _simd_s64x8_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_or_scalar_instruction_set>()
//#else
//	#define _simd_s64x8_or_scalar(X,Y) _simd_s64x8_or_safe(X,_simd_s64x8_fill_scalar_safe(Y))
//	#define _simd_s64x8_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_s64x1_or_safe
//	#define _simd_s64x1_or_safe(X,Y) (X | Y)
//	#define _simd_s64x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_s64x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_or_enabled() true
//#endif
//
//#define _simd_s64x16_or_safe(X,Y)_simd_s64x16_combine_safe(\
//	_simd_s64x8_or_safe(_simd_s64x16_splitlo_safe(X), _simd_ s64x16_splitlo_safe(Y)),\
//	_simd_s64x8_or_safe(_simd_s64x16_splithi_safe(X), _simd_ s64x16_splithi_safe(Y)))
//#ifdef _simd_s64x16_or_
//	#define _simd_s64x16_or(X,Y) _simd_s64x16_or_(X, Y)
//	#define _simd_s64x16_or_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_or_instruction_set>()
//#elif defined(_simd_s64x32_or_)
//	static ANVIL_STRONG_INLINE _simd_s64x16 ANVIL_SIMD_CALL _simd_s64x16_or(const register _simd_s64x16 x, const register _simd_s64x16 y) {
//		union SIMDUnion { _simd_s64x16 v1; _simd_s64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x16_or_enable() _simd_s64x32_or_enable()
//#elif defined(_simd_s64x64_or_)
//	static ANVIL_STRONG_INLINE _simd_s64x16 ANVIL_SIMD_CALL _simd_s64x16_or(const register _simd_s64x16 x, const register _simd_s64x16 y) {
//		union SIMDUnion { _simd_s64x16 v1; _simd_s64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x16_or_enable() _simd_s64x64_or_enable()
//#else
//	#define _simd_s64x16_or(X,Y) _simd_s64x16_combine(\
//		_simd_s64x8_or(_simd_s64x16_splitlo(X), _simd_s64x16_splitlo(Y)),\
//		_simd_s64x8_or(_simd_s64x16_splithi(X), _simd_s64x16_splithi(Y)))
//	#define _simd_s64x16_or_enable() (_simd_s64x8_or_enable() && _simd_s64x16_combine_enable() && _simd_s64x16_splitlo_enable()  && _simd_s64x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x16_or_) && ! defined(_simd_s64x16_or_scalar_)
//	#define _simd_s64x16_or_scalar_(X,Y) _simd_s64x16_or_(X,_simd_s64x16_fill_scalar_(Y))
//	#define _simd_s64x16_or_scalar_instruction_set _simd_s64x16_or_instruction_set
//#endif
//#ifdef _simd_s64x16_or_scalar_
//	#define _simd_s64x16_or_scalar(X,Y) _simd_s64x16_or_scalar_(X,Y)
//	#define _simd_s64x16_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_or_scalar_instruction_set>()
//#else
//	#define _simd_s64x16_or_scalar(X,Y) _simd_s64x16_or_safe(X,_simd_s64x16_fill_scalar_safe(Y))
//	#define _simd_s64x16_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_s64x1_or_safe
//	#define _simd_s64x1_or_safe(X,Y) (X | Y)
//	#define _simd_s64x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_s64x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_or_enabled() true
//#endif
//
//#define _simd_s64x32_or_safe(X,Y)_simd_s64x32_combine_safe(\
//	_simd_s64x16_or_safe(_simd_s64x32_splitlo_safe(X), _simd_ s64x32_splitlo_safe(Y)),\
//	_simd_s64x16_or_safe(_simd_s64x32_splithi_safe(X), _simd_ s64x32_splithi_safe(Y)))
//#ifdef _simd_s64x32_or_
//	#define _simd_s64x32_or(X,Y) _simd_s64x32_or_(X, Y)
//	#define _simd_s64x32_or_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_or_instruction_set>()
//#elif defined(_simd_s64x64_or_)
//	static ANVIL_STRONG_INLINE _simd_s64x32 ANVIL_SIMD_CALL _simd_s64x32_or(const register _simd_s64x32 x, const register _simd_s64x32 y) {
//		union SIMDUnion { _simd_s64x32 v1; _simd_s64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x32_or_enable() _simd_s64x64_or_enable()
//#else
//	#define _simd_s64x32_or(X,Y) _simd_s64x32_combine(\
//		_simd_s64x16_or(_simd_s64x32_splitlo(X), _simd_s64x32_splitlo(Y)),\
//		_simd_s64x16_or(_simd_s64x32_splithi(X), _simd_s64x32_splithi(Y)))
//	#define _simd_s64x32_or_enable() (_simd_s64x16_or_enable() && _simd_s64x32_combine_enable() && _simd_s64x32_splitlo_enable()  && _simd_s64x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x32_or_) && ! defined(_simd_s64x32_or_scalar_)
//	#define _simd_s64x32_or_scalar_(X,Y) _simd_s64x32_or_(X,_simd_s64x32_fill_scalar_(Y))
//	#define _simd_s64x32_or_scalar_instruction_set _simd_s64x32_or_instruction_set
//#endif
//#ifdef _simd_s64x32_or_scalar_
//	#define _simd_s64x32_or_scalar(X,Y) _simd_s64x32_or_scalar_(X,Y)
//	#define _simd_s64x32_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_or_scalar_instruction_set>()
//#else
//	#define _simd_s64x32_or_scalar(X,Y) _simd_s64x32_or_safe(X,_simd_s64x32_fill_scalar_safe(Y))
//	#define _simd_s64x32_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_s64x1_or_safe
//	#define _simd_s64x1_or_safe(X,Y) (X | Y)
//	#define _simd_s64x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_s64x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_or_enabled() true
//#endif
//
//#define _simd_s64x64_or_safe(X,Y)_simd_s64x64_combine_safe(\
//	_simd_s64x32_or_safe(_simd_s64x64_splitlo_safe(X), _simd_ s64x64_splitlo_safe(Y)),\
//	_simd_s64x32_or_safe(_simd_s64x64_splithi_safe(X), _simd_ s64x64_splithi_safe(Y)))
//#ifdef _simd_s64x64_or_
//	#define _simd_s64x64_or(X,Y) _simd_s64x64_or_(X, Y)
//	#define _simd_s64x64_or_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_or_instruction_set>()
//#else
//	#define _simd_s64x64_or(X,Y) _simd_s64x64_combine(\
//		_simd_s64x32_or(_simd_s64x64_splitlo(X), _simd_s64x64_splitlo(Y)),\
//		_simd_s64x32_or(_simd_s64x64_splithi(X), _simd_s64x64_splithi(Y)))
//	#define _simd_s64x64_or_enable() (_simd_s64x32_or_enable() && _simd_s64x64_combine_enable() && _simd_s64x64_splitlo_enable()  && _simd_s64x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x64_or_) && ! defined(_simd_s64x64_or_scalar_)
//	#define _simd_s64x64_or_scalar_(X,Y) _simd_s64x64_or_(X,_simd_s64x64_fill_scalar_(Y))
//	#define _simd_s64x64_or_scalar_instruction_set _simd_s64x64_or_instruction_set
//#endif
//#ifdef _simd_s64x64_or_scalar_
//	#define _simd_s64x64_or_scalar(X,Y) _simd_s64x64_or_scalar_(X,Y)
//	#define _simd_s64x64_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_or_scalar_instruction_set>()
//#else
//	#define _simd_s64x64_or_scalar(X,Y) _simd_s64x64_or_safe(X,_simd_s64x64_fill_scalar_safe(Y))
//	#define _simd_s64x64_or_scalar_enabled() true
//#endif
//
//// -- u64 --
//
//#ifndef _simd_u64x1_or_safe
//	#define _simd_u64x1_or_safe(X,Y) (X | Y)
//	#define _simd_u64x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_u64x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_or_enabled() true
//#endif
//
//#define _simd_u64x2_or_safe(X,Y)_simd_u64x2_combine_safe(\
//	_simd_u64x1_or_safe(_simd_u64x2_splitlo_safe(X), _simd_ u64x2_splitlo_safe(Y)),\
//	_simd_u64x1_or_safe(_simd_u64x2_splithi_safe(X), _simd_ u64x2_splithi_safe(Y)))
//#ifdef _simd_u64x2_or_
//	#define _simd_u64x2_or(X,Y) _simd_u64x2_or_(X, Y)
//	#define _simd_u64x2_or_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_or_instruction_set>()
//#elif defined(_simd_u64x4_or_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_or(const register _simd_u64x2 x, const register _simd_u64x2 y) {
//		union SIMDUnion { _simd_u64x2 v1; _simd_u64x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x4_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x2_or_enable() _simd_u64x4_or_enable()
//#elif defined(_simd_u64x8_or_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_or(const register _simd_u64x2 x, const register _simd_u64x2 y) {
//		union SIMDUnion { _simd_u64x2 v1; _simd_u64x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x8_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x2_or_enable() _simd_u64x8_or_enable()
//#elif defined(_simd_u64x16_or_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_or(const register _simd_u64x2 x, const register _simd_u64x2 y) {
//		union SIMDUnion { _simd_u64x2 v1; _simd_u64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x16_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x2_or_enable() _simd_u64x16_or_enable()
//#elif defined(_simd_u64x32_or_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_or(const register _simd_u64x2 x, const register _simd_u64x2 y) {
//		union SIMDUnion { _simd_u64x2 v1; _simd_u64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x2_or_enable() _simd_u64x32_or_enable()
//#elif defined(_simd_u64x64_or_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_or(const register _simd_u64x2 x, const register _simd_u64x2 y) {
//		union SIMDUnion { _simd_u64x2 v1; _simd_u64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x2_or_enable() _simd_u64x64_or_enable()
//#else
//	#define _simd_u64x2_or(X,Y) _simd_u64x2_combine(\
//		_simd_u64x1_or(_simd_u64x2_splitlo(X), _simd_u64x2_splitlo(Y)),\
//		_simd_u64x1_or(_simd_u64x2_splithi(X), _simd_u64x2_splithi(Y)))
//	#define _simd_u64x2_or_enable() (_simd_u64x1_or_enable() && _simd_u64x2_combine_enable() && _simd_u64x2_splitlo_enable()  && _simd_u64x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x2_or_) && ! defined(_simd_u64x2_or_scalar_)
//	#define _simd_u64x2_or_scalar_(X,Y) _simd_u64x2_or_(X,_simd_u64x2_fill_scalar_(Y))
//	#define _simd_u64x2_or_scalar_instruction_set _simd_u64x2_or_instruction_set
//#endif
//#ifdef _simd_u64x2_or_scalar_
//	#define _simd_u64x2_or_scalar(X,Y) _simd_u64x2_or_scalar_(X,Y)
//	#define _simd_u64x2_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_or_scalar_instruction_set>()
//#else
//	#define _simd_u64x2_or_scalar(X,Y) _simd_u64x2_or_safe(X,_simd_u64x2_fill_scalar_safe(Y))
//	#define _simd_u64x2_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_u64x1_or_safe
//	#define _simd_u64x1_or_safe(X,Y) (X | Y)
//	#define _simd_u64x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_u64x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_or_enabled() true
//#endif
//
//#define _simd_u64x4_or_safe(X,Y)_simd_u64x4_combine_safe(\
//	_simd_u64x2_or_safe(_simd_u64x4_splitlo_safe(X), _simd_ u64x4_splitlo_safe(Y)),\
//	_simd_u64x2_or_safe(_simd_u64x4_splithi_safe(X), _simd_ u64x4_splithi_safe(Y)))
//#ifdef _simd_u64x4_or_
//	#define _simd_u64x4_or(X,Y) _simd_u64x4_or_(X, Y)
//	#define _simd_u64x4_or_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_or_instruction_set>()
//#elif defined(_simd_u64x8_or_)
//	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_or(const register _simd_u64x4 x, const register _simd_u64x4 y) {
//		union SIMDUnion { _simd_u64x4 v1; _simd_u64x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x8_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x4_or_enable() _simd_u64x8_or_enable()
//#elif defined(_simd_u64x16_or_)
//	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_or(const register _simd_u64x4 x, const register _simd_u64x4 y) {
//		union SIMDUnion { _simd_u64x4 v1; _simd_u64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x16_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x4_or_enable() _simd_u64x16_or_enable()
//#elif defined(_simd_u64x32_or_)
//	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_or(const register _simd_u64x4 x, const register _simd_u64x4 y) {
//		union SIMDUnion { _simd_u64x4 v1; _simd_u64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x4_or_enable() _simd_u64x32_or_enable()
//#elif defined(_simd_u64x64_or_)
//	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_or(const register _simd_u64x4 x, const register _simd_u64x4 y) {
//		union SIMDUnion { _simd_u64x4 v1; _simd_u64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x4_or_enable() _simd_u64x64_or_enable()
//#else
//	#define _simd_u64x4_or(X,Y) _simd_u64x4_combine(\
//		_simd_u64x2_or(_simd_u64x4_splitlo(X), _simd_u64x4_splitlo(Y)),\
//		_simd_u64x2_or(_simd_u64x4_splithi(X), _simd_u64x4_splithi(Y)))
//	#define _simd_u64x4_or_enable() (_simd_u64x2_or_enable() && _simd_u64x4_combine_enable() && _simd_u64x4_splitlo_enable()  && _simd_u64x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x4_or_) && ! defined(_simd_u64x4_or_scalar_)
//	#define _simd_u64x4_or_scalar_(X,Y) _simd_u64x4_or_(X,_simd_u64x4_fill_scalar_(Y))
//	#define _simd_u64x4_or_scalar_instruction_set _simd_u64x4_or_instruction_set
//#endif
//#ifdef _simd_u64x4_or_scalar_
//	#define _simd_u64x4_or_scalar(X,Y) _simd_u64x4_or_scalar_(X,Y)
//	#define _simd_u64x4_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_or_scalar_instruction_set>()
//#else
//	#define _simd_u64x4_or_scalar(X,Y) _simd_u64x4_or_safe(X,_simd_u64x4_fill_scalar_safe(Y))
//	#define _simd_u64x4_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_u64x1_or_safe
//	#define _simd_u64x1_or_safe(X,Y) (X | Y)
//	#define _simd_u64x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_u64x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_or_enabled() true
//#endif
//
//#define _simd_u64x8_or_safe(X,Y)_simd_u64x8_combine_safe(\
//	_simd_u64x4_or_safe(_simd_u64x8_splitlo_safe(X), _simd_ u64x8_splitlo_safe(Y)),\
//	_simd_u64x4_or_safe(_simd_u64x8_splithi_safe(X), _simd_ u64x8_splithi_safe(Y)))
//#ifdef _simd_u64x8_or_
//	#define _simd_u64x8_or(X,Y) _simd_u64x8_or_(X, Y)
//	#define _simd_u64x8_or_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_or_instruction_set>()
//#elif defined(_simd_u64x16_or_)
//	static ANVIL_STRONG_INLINE _simd_u64x8 ANVIL_SIMD_CALL _simd_u64x8_or(const register _simd_u64x8 x, const register _simd_u64x8 y) {
//		union SIMDUnion { _simd_u64x8 v1; _simd_u64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x16_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x8_or_enable() _simd_u64x16_or_enable()
//#elif defined(_simd_u64x32_or_)
//	static ANVIL_STRONG_INLINE _simd_u64x8 ANVIL_SIMD_CALL _simd_u64x8_or(const register _simd_u64x8 x, const register _simd_u64x8 y) {
//		union SIMDUnion { _simd_u64x8 v1; _simd_u64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x8_or_enable() _simd_u64x32_or_enable()
//#elif defined(_simd_u64x64_or_)
//	static ANVIL_STRONG_INLINE _simd_u64x8 ANVIL_SIMD_CALL _simd_u64x8_or(const register _simd_u64x8 x, const register _simd_u64x8 y) {
//		union SIMDUnion { _simd_u64x8 v1; _simd_u64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x8_or_enable() _simd_u64x64_or_enable()
//#else
//	#define _simd_u64x8_or(X,Y) _simd_u64x8_combine(\
//		_simd_u64x4_or(_simd_u64x8_splitlo(X), _simd_u64x8_splitlo(Y)),\
//		_simd_u64x4_or(_simd_u64x8_splithi(X), _simd_u64x8_splithi(Y)))
//	#define _simd_u64x8_or_enable() (_simd_u64x4_or_enable() && _simd_u64x8_combine_enable() && _simd_u64x8_splitlo_enable()  && _simd_u64x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x8_or_) && ! defined(_simd_u64x8_or_scalar_)
//	#define _simd_u64x8_or_scalar_(X,Y) _simd_u64x8_or_(X,_simd_u64x8_fill_scalar_(Y))
//	#define _simd_u64x8_or_scalar_instruction_set _simd_u64x8_or_instruction_set
//#endif
//#ifdef _simd_u64x8_or_scalar_
//	#define _simd_u64x8_or_scalar(X,Y) _simd_u64x8_or_scalar_(X,Y)
//	#define _simd_u64x8_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_or_scalar_instruction_set>()
//#else
//	#define _simd_u64x8_or_scalar(X,Y) _simd_u64x8_or_safe(X,_simd_u64x8_fill_scalar_safe(Y))
//	#define _simd_u64x8_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_u64x1_or_safe
//	#define _simd_u64x1_or_safe(X,Y) (X | Y)
//	#define _simd_u64x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_u64x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_or_enabled() true
//#endif
//
//#define _simd_u64x16_or_safe(X,Y)_simd_u64x16_combine_safe(\
//	_simd_u64x8_or_safe(_simd_u64x16_splitlo_safe(X), _simd_ u64x16_splitlo_safe(Y)),\
//	_simd_u64x8_or_safe(_simd_u64x16_splithi_safe(X), _simd_ u64x16_splithi_safe(Y)))
//#ifdef _simd_u64x16_or_
//	#define _simd_u64x16_or(X,Y) _simd_u64x16_or_(X, Y)
//	#define _simd_u64x16_or_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_or_instruction_set>()
//#elif defined(_simd_u64x32_or_)
//	static ANVIL_STRONG_INLINE _simd_u64x16 ANVIL_SIMD_CALL _simd_u64x16_or(const register _simd_u64x16 x, const register _simd_u64x16 y) {
//		union SIMDUnion { _simd_u64x16 v1; _simd_u64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x16_or_enable() _simd_u64x32_or_enable()
//#elif defined(_simd_u64x64_or_)
//	static ANVIL_STRONG_INLINE _simd_u64x16 ANVIL_SIMD_CALL _simd_u64x16_or(const register _simd_u64x16 x, const register _simd_u64x16 y) {
//		union SIMDUnion { _simd_u64x16 v1; _simd_u64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x16_or_enable() _simd_u64x64_or_enable()
//#else
//	#define _simd_u64x16_or(X,Y) _simd_u64x16_combine(\
//		_simd_u64x8_or(_simd_u64x16_splitlo(X), _simd_u64x16_splitlo(Y)),\
//		_simd_u64x8_or(_simd_u64x16_splithi(X), _simd_u64x16_splithi(Y)))
//	#define _simd_u64x16_or_enable() (_simd_u64x8_or_enable() && _simd_u64x16_combine_enable() && _simd_u64x16_splitlo_enable()  && _simd_u64x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x16_or_) && ! defined(_simd_u64x16_or_scalar_)
//	#define _simd_u64x16_or_scalar_(X,Y) _simd_u64x16_or_(X,_simd_u64x16_fill_scalar_(Y))
//	#define _simd_u64x16_or_scalar_instruction_set _simd_u64x16_or_instruction_set
//#endif
//#ifdef _simd_u64x16_or_scalar_
//	#define _simd_u64x16_or_scalar(X,Y) _simd_u64x16_or_scalar_(X,Y)
//	#define _simd_u64x16_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_or_scalar_instruction_set>()
//#else
//	#define _simd_u64x16_or_scalar(X,Y) _simd_u64x16_or_safe(X,_simd_u64x16_fill_scalar_safe(Y))
//	#define _simd_u64x16_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_u64x1_or_safe
//	#define _simd_u64x1_or_safe(X,Y) (X | Y)
//	#define _simd_u64x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_u64x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_or_enabled() true
//#endif
//
//#define _simd_u64x32_or_safe(X,Y)_simd_u64x32_combine_safe(\
//	_simd_u64x16_or_safe(_simd_u64x32_splitlo_safe(X), _simd_ u64x32_splitlo_safe(Y)),\
//	_simd_u64x16_or_safe(_simd_u64x32_splithi_safe(X), _simd_ u64x32_splithi_safe(Y)))
//#ifdef _simd_u64x32_or_
//	#define _simd_u64x32_or(X,Y) _simd_u64x32_or_(X, Y)
//	#define _simd_u64x32_or_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_or_instruction_set>()
//#elif defined(_simd_u64x64_or_)
//	static ANVIL_STRONG_INLINE _simd_u64x32 ANVIL_SIMD_CALL _simd_u64x32_or(const register _simd_u64x32 x, const register _simd_u64x32 y) {
//		union SIMDUnion { _simd_u64x32 v1; _simd_u64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x32_or_enable() _simd_u64x64_or_enable()
//#else
//	#define _simd_u64x32_or(X,Y) _simd_u64x32_combine(\
//		_simd_u64x16_or(_simd_u64x32_splitlo(X), _simd_u64x32_splitlo(Y)),\
//		_simd_u64x16_or(_simd_u64x32_splithi(X), _simd_u64x32_splithi(Y)))
//	#define _simd_u64x32_or_enable() (_simd_u64x16_or_enable() && _simd_u64x32_combine_enable() && _simd_u64x32_splitlo_enable()  && _simd_u64x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x32_or_) && ! defined(_simd_u64x32_or_scalar_)
//	#define _simd_u64x32_or_scalar_(X,Y) _simd_u64x32_or_(X,_simd_u64x32_fill_scalar_(Y))
//	#define _simd_u64x32_or_scalar_instruction_set _simd_u64x32_or_instruction_set
//#endif
//#ifdef _simd_u64x32_or_scalar_
//	#define _simd_u64x32_or_scalar(X,Y) _simd_u64x32_or_scalar_(X,Y)
//	#define _simd_u64x32_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_or_scalar_instruction_set>()
//#else
//	#define _simd_u64x32_or_scalar(X,Y) _simd_u64x32_or_safe(X,_simd_u64x32_fill_scalar_safe(Y))
//	#define _simd_u64x32_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_u64x1_or_safe
//	#define _simd_u64x1_or_safe(X,Y) (X | Y)
//	#define _simd_u64x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_u64x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_or_enabled() true
//#endif
//
//#define _simd_u64x64_or_safe(X,Y)_simd_u64x64_combine_safe(\
//	_simd_u64x32_or_safe(_simd_u64x64_splitlo_safe(X), _simd_ u64x64_splitlo_safe(Y)),\
//	_simd_u64x32_or_safe(_simd_u64x64_splithi_safe(X), _simd_ u64x64_splithi_safe(Y)))
//#ifdef _simd_u64x64_or_
//	#define _simd_u64x64_or(X,Y) _simd_u64x64_or_(X, Y)
//	#define _simd_u64x64_or_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_or_instruction_set>()
//#else
//	#define _simd_u64x64_or(X,Y) _simd_u64x64_combine(\
//		_simd_u64x32_or(_simd_u64x64_splitlo(X), _simd_u64x64_splitlo(Y)),\
//		_simd_u64x32_or(_simd_u64x64_splithi(X), _simd_u64x64_splithi(Y)))
//	#define _simd_u64x64_or_enable() (_simd_u64x32_or_enable() && _simd_u64x64_combine_enable() && _simd_u64x64_splitlo_enable()  && _simd_u64x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x64_or_) && ! defined(_simd_u64x64_or_scalar_)
//	#define _simd_u64x64_or_scalar_(X,Y) _simd_u64x64_or_(X,_simd_u64x64_fill_scalar_(Y))
//	#define _simd_u64x64_or_scalar_instruction_set _simd_u64x64_or_instruction_set
//#endif
//#ifdef _simd_u64x64_or_scalar_
//	#define _simd_u64x64_or_scalar(X,Y) _simd_u64x64_or_scalar_(X,Y)
//	#define _simd_u64x64_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_or_scalar_instruction_set>()
//#else
//	#define _simd_u64x64_or_scalar(X,Y) _simd_u64x64_or_safe(X,_simd_u64x64_fill_scalar_safe(Y))
//	#define _simd_u64x64_or_scalar_enabled() true
//#endif
//
//// -- s32 --
//
//#ifndef _simd_s32x1_or_safe
//	#define _simd_s32x1_or_safe(X,Y) (X | Y)
//	#define _simd_s32x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_s32x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_or_enabled() true
//#endif
//
//#define _simd_s32x2_or_safe(X,Y)_simd_s32x2_combine_safe(\
//	_simd_s32x1_or_safe(_simd_s32x2_splitlo_safe(X), _simd_ s32x2_splitlo_safe(Y)),\
//	_simd_s32x1_or_safe(_simd_s32x2_splithi_safe(X), _simd_ s32x2_splithi_safe(Y)))
//#ifdef _simd_s32x2_or_
//	#define _simd_s32x2_or(X,Y) _simd_s32x2_or_(X, Y)
//	#define _simd_s32x2_or_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_or_instruction_set>()
//#elif defined(_simd_s32x4_or_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_or(const register _simd_s32x2 x, const register _simd_s32x2 y) {
//		union SIMDUnion { _simd_s32x2 v1; _simd_s32x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x4_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x2_or_enable() _simd_s32x4_or_enable()
//#elif defined(_simd_s32x8_or_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_or(const register _simd_s32x2 x, const register _simd_s32x2 y) {
//		union SIMDUnion { _simd_s32x2 v1; _simd_s32x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x8_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x2_or_enable() _simd_s32x8_or_enable()
//#elif defined(_simd_s32x16_or_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_or(const register _simd_s32x2 x, const register _simd_s32x2 y) {
//		union SIMDUnion { _simd_s32x2 v1; _simd_s32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x16_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x2_or_enable() _simd_s32x16_or_enable()
//#elif defined(_simd_s32x32_or_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_or(const register _simd_s32x2 x, const register _simd_s32x2 y) {
//		union SIMDUnion { _simd_s32x2 v1; _simd_s32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x2_or_enable() _simd_s32x32_or_enable()
//#elif defined(_simd_s32x64_or_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_or(const register _simd_s32x2 x, const register _simd_s32x2 y) {
//		union SIMDUnion { _simd_s32x2 v1; _simd_s32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x2_or_enable() _simd_s32x64_or_enable()
//#else
//	#define _simd_s32x2_or(X,Y) _simd_s32x2_combine(\
//		_simd_s32x1_or(_simd_s32x2_splitlo(X), _simd_s32x2_splitlo(Y)),\
//		_simd_s32x1_or(_simd_s32x2_splithi(X), _simd_s32x2_splithi(Y)))
//	#define _simd_s32x2_or_enable() (_simd_s32x1_or_enable() && _simd_s32x2_combine_enable() && _simd_s32x2_splitlo_enable()  && _simd_s32x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x2_or_) && ! defined(_simd_s32x2_or_scalar_)
//	#define _simd_s32x2_or_scalar_(X,Y) _simd_s32x2_or_(X,_simd_s32x2_fill_scalar_(Y))
//	#define _simd_s32x2_or_scalar_instruction_set _simd_s32x2_or_instruction_set
//#endif
//#ifdef _simd_s32x2_or_scalar_
//	#define _simd_s32x2_or_scalar(X,Y) _simd_s32x2_or_scalar_(X,Y)
//	#define _simd_s32x2_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_or_scalar_instruction_set>()
//#else
//	#define _simd_s32x2_or_scalar(X,Y) _simd_s32x2_or_safe(X,_simd_s32x2_fill_scalar_safe(Y))
//	#define _simd_s32x2_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_s32x1_or_safe
//	#define _simd_s32x1_or_safe(X,Y) (X | Y)
//	#define _simd_s32x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_s32x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_or_enabled() true
//#endif
//
//#define _simd_s32x4_or_safe(X,Y)_simd_s32x4_combine_safe(\
//	_simd_s32x2_or_safe(_simd_s32x4_splitlo_safe(X), _simd_ s32x4_splitlo_safe(Y)),\
//	_simd_s32x2_or_safe(_simd_s32x4_splithi_safe(X), _simd_ s32x4_splithi_safe(Y)))
//#ifdef _simd_s32x4_or_
//	#define _simd_s32x4_or(X,Y) _simd_s32x4_or_(X, Y)
//	#define _simd_s32x4_or_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_or_instruction_set>()
//#elif defined(_simd_s32x8_or_)
//	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_or(const register _simd_s32x4 x, const register _simd_s32x4 y) {
//		union SIMDUnion { _simd_s32x4 v1; _simd_s32x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x8_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x4_or_enable() _simd_s32x8_or_enable()
//#elif defined(_simd_s32x16_or_)
//	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_or(const register _simd_s32x4 x, const register _simd_s32x4 y) {
//		union SIMDUnion { _simd_s32x4 v1; _simd_s32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x16_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x4_or_enable() _simd_s32x16_or_enable()
//#elif defined(_simd_s32x32_or_)
//	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_or(const register _simd_s32x4 x, const register _simd_s32x4 y) {
//		union SIMDUnion { _simd_s32x4 v1; _simd_s32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x4_or_enable() _simd_s32x32_or_enable()
//#elif defined(_simd_s32x64_or_)
//	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_or(const register _simd_s32x4 x, const register _simd_s32x4 y) {
//		union SIMDUnion { _simd_s32x4 v1; _simd_s32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x4_or_enable() _simd_s32x64_or_enable()
//#else
//	#define _simd_s32x4_or(X,Y) _simd_s32x4_combine(\
//		_simd_s32x2_or(_simd_s32x4_splitlo(X), _simd_s32x4_splitlo(Y)),\
//		_simd_s32x2_or(_simd_s32x4_splithi(X), _simd_s32x4_splithi(Y)))
//	#define _simd_s32x4_or_enable() (_simd_s32x2_or_enable() && _simd_s32x4_combine_enable() && _simd_s32x4_splitlo_enable()  && _simd_s32x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x4_or_) && ! defined(_simd_s32x4_or_scalar_)
//	#define _simd_s32x4_or_scalar_(X,Y) _simd_s32x4_or_(X,_simd_s32x4_fill_scalar_(Y))
//	#define _simd_s32x4_or_scalar_instruction_set _simd_s32x4_or_instruction_set
//#endif
//#ifdef _simd_s32x4_or_scalar_
//	#define _simd_s32x4_or_scalar(X,Y) _simd_s32x4_or_scalar_(X,Y)
//	#define _simd_s32x4_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_or_scalar_instruction_set>()
//#else
//	#define _simd_s32x4_or_scalar(X,Y) _simd_s32x4_or_safe(X,_simd_s32x4_fill_scalar_safe(Y))
//	#define _simd_s32x4_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_s32x1_or_safe
//	#define _simd_s32x1_or_safe(X,Y) (X | Y)
//	#define _simd_s32x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_s32x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_or_enabled() true
//#endif
//
//#define _simd_s32x8_or_safe(X,Y)_simd_s32x8_combine_safe(\
//	_simd_s32x4_or_safe(_simd_s32x8_splitlo_safe(X), _simd_ s32x8_splitlo_safe(Y)),\
//	_simd_s32x4_or_safe(_simd_s32x8_splithi_safe(X), _simd_ s32x8_splithi_safe(Y)))
//#ifdef _simd_s32x8_or_
//	#define _simd_s32x8_or(X,Y) _simd_s32x8_or_(X, Y)
//	#define _simd_s32x8_or_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_or_instruction_set>()
//#elif defined(_simd_s32x16_or_)
//	static ANVIL_STRONG_INLINE _simd_s32x8 ANVIL_SIMD_CALL _simd_s32x8_or(const register _simd_s32x8 x, const register _simd_s32x8 y) {
//		union SIMDUnion { _simd_s32x8 v1; _simd_s32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x16_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x8_or_enable() _simd_s32x16_or_enable()
//#elif defined(_simd_s32x32_or_)
//	static ANVIL_STRONG_INLINE _simd_s32x8 ANVIL_SIMD_CALL _simd_s32x8_or(const register _simd_s32x8 x, const register _simd_s32x8 y) {
//		union SIMDUnion { _simd_s32x8 v1; _simd_s32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x8_or_enable() _simd_s32x32_or_enable()
//#elif defined(_simd_s32x64_or_)
//	static ANVIL_STRONG_INLINE _simd_s32x8 ANVIL_SIMD_CALL _simd_s32x8_or(const register _simd_s32x8 x, const register _simd_s32x8 y) {
//		union SIMDUnion { _simd_s32x8 v1; _simd_s32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x8_or_enable() _simd_s32x64_or_enable()
//#else
//	#define _simd_s32x8_or(X,Y) _simd_s32x8_combine(\
//		_simd_s32x4_or(_simd_s32x8_splitlo(X), _simd_s32x8_splitlo(Y)),\
//		_simd_s32x4_or(_simd_s32x8_splithi(X), _simd_s32x8_splithi(Y)))
//	#define _simd_s32x8_or_enable() (_simd_s32x4_or_enable() && _simd_s32x8_combine_enable() && _simd_s32x8_splitlo_enable()  && _simd_s32x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x8_or_) && ! defined(_simd_s32x8_or_scalar_)
//	#define _simd_s32x8_or_scalar_(X,Y) _simd_s32x8_or_(X,_simd_s32x8_fill_scalar_(Y))
//	#define _simd_s32x8_or_scalar_instruction_set _simd_s32x8_or_instruction_set
//#endif
//#ifdef _simd_s32x8_or_scalar_
//	#define _simd_s32x8_or_scalar(X,Y) _simd_s32x8_or_scalar_(X,Y)
//	#define _simd_s32x8_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_or_scalar_instruction_set>()
//#else
//	#define _simd_s32x8_or_scalar(X,Y) _simd_s32x8_or_safe(X,_simd_s32x8_fill_scalar_safe(Y))
//	#define _simd_s32x8_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_s32x1_or_safe
//	#define _simd_s32x1_or_safe(X,Y) (X | Y)
//	#define _simd_s32x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_s32x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_or_enabled() true
//#endif
//
//#define _simd_s32x16_or_safe(X,Y)_simd_s32x16_combine_safe(\
//	_simd_s32x8_or_safe(_simd_s32x16_splitlo_safe(X), _simd_ s32x16_splitlo_safe(Y)),\
//	_simd_s32x8_or_safe(_simd_s32x16_splithi_safe(X), _simd_ s32x16_splithi_safe(Y)))
//#ifdef _simd_s32x16_or_
//	#define _simd_s32x16_or(X,Y) _simd_s32x16_or_(X, Y)
//	#define _simd_s32x16_or_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_or_instruction_set>()
//#elif defined(_simd_s32x32_or_)
//	static ANVIL_STRONG_INLINE _simd_s32x16 ANVIL_SIMD_CALL _simd_s32x16_or(const register _simd_s32x16 x, const register _simd_s32x16 y) {
//		union SIMDUnion { _simd_s32x16 v1; _simd_s32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x16_or_enable() _simd_s32x32_or_enable()
//#elif defined(_simd_s32x64_or_)
//	static ANVIL_STRONG_INLINE _simd_s32x16 ANVIL_SIMD_CALL _simd_s32x16_or(const register _simd_s32x16 x, const register _simd_s32x16 y) {
//		union SIMDUnion { _simd_s32x16 v1; _simd_s32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x16_or_enable() _simd_s32x64_or_enable()
//#else
//	#define _simd_s32x16_or(X,Y) _simd_s32x16_combine(\
//		_simd_s32x8_or(_simd_s32x16_splitlo(X), _simd_s32x16_splitlo(Y)),\
//		_simd_s32x8_or(_simd_s32x16_splithi(X), _simd_s32x16_splithi(Y)))
//	#define _simd_s32x16_or_enable() (_simd_s32x8_or_enable() && _simd_s32x16_combine_enable() && _simd_s32x16_splitlo_enable()  && _simd_s32x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x16_or_) && ! defined(_simd_s32x16_or_scalar_)
//	#define _simd_s32x16_or_scalar_(X,Y) _simd_s32x16_or_(X,_simd_s32x16_fill_scalar_(Y))
//	#define _simd_s32x16_or_scalar_instruction_set _simd_s32x16_or_instruction_set
//#endif
//#ifdef _simd_s32x16_or_scalar_
//	#define _simd_s32x16_or_scalar(X,Y) _simd_s32x16_or_scalar_(X,Y)
//	#define _simd_s32x16_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_or_scalar_instruction_set>()
//#else
//	#define _simd_s32x16_or_scalar(X,Y) _simd_s32x16_or_safe(X,_simd_s32x16_fill_scalar_safe(Y))
//	#define _simd_s32x16_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_s32x1_or_safe
//	#define _simd_s32x1_or_safe(X,Y) (X | Y)
//	#define _simd_s32x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_s32x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_or_enabled() true
//#endif
//
//#define _simd_s32x32_or_safe(X,Y)_simd_s32x32_combine_safe(\
//	_simd_s32x16_or_safe(_simd_s32x32_splitlo_safe(X), _simd_ s32x32_splitlo_safe(Y)),\
//	_simd_s32x16_or_safe(_simd_s32x32_splithi_safe(X), _simd_ s32x32_splithi_safe(Y)))
//#ifdef _simd_s32x32_or_
//	#define _simd_s32x32_or(X,Y) _simd_s32x32_or_(X, Y)
//	#define _simd_s32x32_or_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_or_instruction_set>()
//#elif defined(_simd_s32x64_or_)
//	static ANVIL_STRONG_INLINE _simd_s32x32 ANVIL_SIMD_CALL _simd_s32x32_or(const register _simd_s32x32 x, const register _simd_s32x32 y) {
//		union SIMDUnion { _simd_s32x32 v1; _simd_s32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x32_or_enable() _simd_s32x64_or_enable()
//#else
//	#define _simd_s32x32_or(X,Y) _simd_s32x32_combine(\
//		_simd_s32x16_or(_simd_s32x32_splitlo(X), _simd_s32x32_splitlo(Y)),\
//		_simd_s32x16_or(_simd_s32x32_splithi(X), _simd_s32x32_splithi(Y)))
//	#define _simd_s32x32_or_enable() (_simd_s32x16_or_enable() && _simd_s32x32_combine_enable() && _simd_s32x32_splitlo_enable()  && _simd_s32x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x32_or_) && ! defined(_simd_s32x32_or_scalar_)
//	#define _simd_s32x32_or_scalar_(X,Y) _simd_s32x32_or_(X,_simd_s32x32_fill_scalar_(Y))
//	#define _simd_s32x32_or_scalar_instruction_set _simd_s32x32_or_instruction_set
//#endif
//#ifdef _simd_s32x32_or_scalar_
//	#define _simd_s32x32_or_scalar(X,Y) _simd_s32x32_or_scalar_(X,Y)
//	#define _simd_s32x32_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_or_scalar_instruction_set>()
//#else
//	#define _simd_s32x32_or_scalar(X,Y) _simd_s32x32_or_safe(X,_simd_s32x32_fill_scalar_safe(Y))
//	#define _simd_s32x32_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_s32x1_or_safe
//	#define _simd_s32x1_or_safe(X,Y) (X | Y)
//	#define _simd_s32x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_s32x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_or_enabled() true
//#endif
//
//#define _simd_s32x64_or_safe(X,Y)_simd_s32x64_combine_safe(\
//	_simd_s32x32_or_safe(_simd_s32x64_splitlo_safe(X), _simd_ s32x64_splitlo_safe(Y)),\
//	_simd_s32x32_or_safe(_simd_s32x64_splithi_safe(X), _simd_ s32x64_splithi_safe(Y)))
//#ifdef _simd_s32x64_or_
//	#define _simd_s32x64_or(X,Y) _simd_s32x64_or_(X, Y)
//	#define _simd_s32x64_or_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_or_instruction_set>()
//#else
//	#define _simd_s32x64_or(X,Y) _simd_s32x64_combine(\
//		_simd_s32x32_or(_simd_s32x64_splitlo(X), _simd_s32x64_splitlo(Y)),\
//		_simd_s32x32_or(_simd_s32x64_splithi(X), _simd_s32x64_splithi(Y)))
//	#define _simd_s32x64_or_enable() (_simd_s32x32_or_enable() && _simd_s32x64_combine_enable() && _simd_s32x64_splitlo_enable()  && _simd_s32x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x64_or_) && ! defined(_simd_s32x64_or_scalar_)
//	#define _simd_s32x64_or_scalar_(X,Y) _simd_s32x64_or_(X,_simd_s32x64_fill_scalar_(Y))
//	#define _simd_s32x64_or_scalar_instruction_set _simd_s32x64_or_instruction_set
//#endif
//#ifdef _simd_s32x64_or_scalar_
//	#define _simd_s32x64_or_scalar(X,Y) _simd_s32x64_or_scalar_(X,Y)
//	#define _simd_s32x64_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_or_scalar_instruction_set>()
//#else
//	#define _simd_s32x64_or_scalar(X,Y) _simd_s32x64_or_safe(X,_simd_s32x64_fill_scalar_safe(Y))
//	#define _simd_s32x64_or_scalar_enabled() true
//#endif
//
//// -- u32 --
//
//#ifndef _simd_u32x1_or_safe
//	#define _simd_u32x1_or_safe(X,Y) (X | Y)
//	#define _simd_u32x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_u32x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_or_enabled() true
//#endif
//
//#define _simd_u32x2_or_safe(X,Y)_simd_u32x2_combine_safe(\
//	_simd_u32x1_or_safe(_simd_u32x2_splitlo_safe(X), _simd_ u32x2_splitlo_safe(Y)),\
//	_simd_u32x1_or_safe(_simd_u32x2_splithi_safe(X), _simd_ u32x2_splithi_safe(Y)))
//#ifdef _simd_u32x2_or_
//	#define _simd_u32x2_or(X,Y) _simd_u32x2_or_(X, Y)
//	#define _simd_u32x2_or_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_or_instruction_set>()
//#elif defined(_simd_u32x4_or_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_or(const register _simd_u32x2 x, const register _simd_u32x2 y) {
//		union SIMDUnion { _simd_u32x2 v1; _simd_u32x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x4_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x2_or_enable() _simd_u32x4_or_enable()
//#elif defined(_simd_u32x8_or_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_or(const register _simd_u32x2 x, const register _simd_u32x2 y) {
//		union SIMDUnion { _simd_u32x2 v1; _simd_u32x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x8_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x2_or_enable() _simd_u32x8_or_enable()
//#elif defined(_simd_u32x16_or_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_or(const register _simd_u32x2 x, const register _simd_u32x2 y) {
//		union SIMDUnion { _simd_u32x2 v1; _simd_u32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x16_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x2_or_enable() _simd_u32x16_or_enable()
//#elif defined(_simd_u32x32_or_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_or(const register _simd_u32x2 x, const register _simd_u32x2 y) {
//		union SIMDUnion { _simd_u32x2 v1; _simd_u32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x2_or_enable() _simd_u32x32_or_enable()
//#elif defined(_simd_u32x64_or_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_or(const register _simd_u32x2 x, const register _simd_u32x2 y) {
//		union SIMDUnion { _simd_u32x2 v1; _simd_u32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x2_or_enable() _simd_u32x64_or_enable()
//#else
//	#define _simd_u32x2_or(X,Y) _simd_u32x2_combine(\
//		_simd_u32x1_or(_simd_u32x2_splitlo(X), _simd_u32x2_splitlo(Y)),\
//		_simd_u32x1_or(_simd_u32x2_splithi(X), _simd_u32x2_splithi(Y)))
//	#define _simd_u32x2_or_enable() (_simd_u32x1_or_enable() && _simd_u32x2_combine_enable() && _simd_u32x2_splitlo_enable()  && _simd_u32x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x2_or_) && ! defined(_simd_u32x2_or_scalar_)
//	#define _simd_u32x2_or_scalar_(X,Y) _simd_u32x2_or_(X,_simd_u32x2_fill_scalar_(Y))
//	#define _simd_u32x2_or_scalar_instruction_set _simd_u32x2_or_instruction_set
//#endif
//#ifdef _simd_u32x2_or_scalar_
//	#define _simd_u32x2_or_scalar(X,Y) _simd_u32x2_or_scalar_(X,Y)
//	#define _simd_u32x2_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_or_scalar_instruction_set>()
//#else
//	#define _simd_u32x2_or_scalar(X,Y) _simd_u32x2_or_safe(X,_simd_u32x2_fill_scalar_safe(Y))
//	#define _simd_u32x2_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_u32x1_or_safe
//	#define _simd_u32x1_or_safe(X,Y) (X | Y)
//	#define _simd_u32x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_u32x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_or_enabled() true
//#endif
//
//#define _simd_u32x4_or_safe(X,Y)_simd_u32x4_combine_safe(\
//	_simd_u32x2_or_safe(_simd_u32x4_splitlo_safe(X), _simd_ u32x4_splitlo_safe(Y)),\
//	_simd_u32x2_or_safe(_simd_u32x4_splithi_safe(X), _simd_ u32x4_splithi_safe(Y)))
//#ifdef _simd_u32x4_or_
//	#define _simd_u32x4_or(X,Y) _simd_u32x4_or_(X, Y)
//	#define _simd_u32x4_or_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_or_instruction_set>()
//#elif defined(_simd_u32x8_or_)
//	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_or(const register _simd_u32x4 x, const register _simd_u32x4 y) {
//		union SIMDUnion { _simd_u32x4 v1; _simd_u32x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x8_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x4_or_enable() _simd_u32x8_or_enable()
//#elif defined(_simd_u32x16_or_)
//	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_or(const register _simd_u32x4 x, const register _simd_u32x4 y) {
//		union SIMDUnion { _simd_u32x4 v1; _simd_u32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x16_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x4_or_enable() _simd_u32x16_or_enable()
//#elif defined(_simd_u32x32_or_)
//	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_or(const register _simd_u32x4 x, const register _simd_u32x4 y) {
//		union SIMDUnion { _simd_u32x4 v1; _simd_u32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x4_or_enable() _simd_u32x32_or_enable()
//#elif defined(_simd_u32x64_or_)
//	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_or(const register _simd_u32x4 x, const register _simd_u32x4 y) {
//		union SIMDUnion { _simd_u32x4 v1; _simd_u32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x4_or_enable() _simd_u32x64_or_enable()
//#else
//	#define _simd_u32x4_or(X,Y) _simd_u32x4_combine(\
//		_simd_u32x2_or(_simd_u32x4_splitlo(X), _simd_u32x4_splitlo(Y)),\
//		_simd_u32x2_or(_simd_u32x4_splithi(X), _simd_u32x4_splithi(Y)))
//	#define _simd_u32x4_or_enable() (_simd_u32x2_or_enable() && _simd_u32x4_combine_enable() && _simd_u32x4_splitlo_enable()  && _simd_u32x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x4_or_) && ! defined(_simd_u32x4_or_scalar_)
//	#define _simd_u32x4_or_scalar_(X,Y) _simd_u32x4_or_(X,_simd_u32x4_fill_scalar_(Y))
//	#define _simd_u32x4_or_scalar_instruction_set _simd_u32x4_or_instruction_set
//#endif
//#ifdef _simd_u32x4_or_scalar_
//	#define _simd_u32x4_or_scalar(X,Y) _simd_u32x4_or_scalar_(X,Y)
//	#define _simd_u32x4_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_or_scalar_instruction_set>()
//#else
//	#define _simd_u32x4_or_scalar(X,Y) _simd_u32x4_or_safe(X,_simd_u32x4_fill_scalar_safe(Y))
//	#define _simd_u32x4_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_u32x1_or_safe
//	#define _simd_u32x1_or_safe(X,Y) (X | Y)
//	#define _simd_u32x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_u32x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_or_enabled() true
//#endif
//
//#define _simd_u32x8_or_safe(X,Y)_simd_u32x8_combine_safe(\
//	_simd_u32x4_or_safe(_simd_u32x8_splitlo_safe(X), _simd_ u32x8_splitlo_safe(Y)),\
//	_simd_u32x4_or_safe(_simd_u32x8_splithi_safe(X), _simd_ u32x8_splithi_safe(Y)))
//#ifdef _simd_u32x8_or_
//	#define _simd_u32x8_or(X,Y) _simd_u32x8_or_(X, Y)
//	#define _simd_u32x8_or_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_or_instruction_set>()
//#elif defined(_simd_u32x16_or_)
//	static ANVIL_STRONG_INLINE _simd_u32x8 ANVIL_SIMD_CALL _simd_u32x8_or(const register _simd_u32x8 x, const register _simd_u32x8 y) {
//		union SIMDUnion { _simd_u32x8 v1; _simd_u32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x16_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x8_or_enable() _simd_u32x16_or_enable()
//#elif defined(_simd_u32x32_or_)
//	static ANVIL_STRONG_INLINE _simd_u32x8 ANVIL_SIMD_CALL _simd_u32x8_or(const register _simd_u32x8 x, const register _simd_u32x8 y) {
//		union SIMDUnion { _simd_u32x8 v1; _simd_u32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x8_or_enable() _simd_u32x32_or_enable()
//#elif defined(_simd_u32x64_or_)
//	static ANVIL_STRONG_INLINE _simd_u32x8 ANVIL_SIMD_CALL _simd_u32x8_or(const register _simd_u32x8 x, const register _simd_u32x8 y) {
//		union SIMDUnion { _simd_u32x8 v1; _simd_u32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x8_or_enable() _simd_u32x64_or_enable()
//#else
//	#define _simd_u32x8_or(X,Y) _simd_u32x8_combine(\
//		_simd_u32x4_or(_simd_u32x8_splitlo(X), _simd_u32x8_splitlo(Y)),\
//		_simd_u32x4_or(_simd_u32x8_splithi(X), _simd_u32x8_splithi(Y)))
//	#define _simd_u32x8_or_enable() (_simd_u32x4_or_enable() && _simd_u32x8_combine_enable() && _simd_u32x8_splitlo_enable()  && _simd_u32x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x8_or_) && ! defined(_simd_u32x8_or_scalar_)
//	#define _simd_u32x8_or_scalar_(X,Y) _simd_u32x8_or_(X,_simd_u32x8_fill_scalar_(Y))
//	#define _simd_u32x8_or_scalar_instruction_set _simd_u32x8_or_instruction_set
//#endif
//#ifdef _simd_u32x8_or_scalar_
//	#define _simd_u32x8_or_scalar(X,Y) _simd_u32x8_or_scalar_(X,Y)
//	#define _simd_u32x8_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_or_scalar_instruction_set>()
//#else
//	#define _simd_u32x8_or_scalar(X,Y) _simd_u32x8_or_safe(X,_simd_u32x8_fill_scalar_safe(Y))
//	#define _simd_u32x8_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_u32x1_or_safe
//	#define _simd_u32x1_or_safe(X,Y) (X | Y)
//	#define _simd_u32x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_u32x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_or_enabled() true
//#endif
//
//#define _simd_u32x16_or_safe(X,Y)_simd_u32x16_combine_safe(\
//	_simd_u32x8_or_safe(_simd_u32x16_splitlo_safe(X), _simd_ u32x16_splitlo_safe(Y)),\
//	_simd_u32x8_or_safe(_simd_u32x16_splithi_safe(X), _simd_ u32x16_splithi_safe(Y)))
//#ifdef _simd_u32x16_or_
//	#define _simd_u32x16_or(X,Y) _simd_u32x16_or_(X, Y)
//	#define _simd_u32x16_or_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_or_instruction_set>()
//#elif defined(_simd_u32x32_or_)
//	static ANVIL_STRONG_INLINE _simd_u32x16 ANVIL_SIMD_CALL _simd_u32x16_or(const register _simd_u32x16 x, const register _simd_u32x16 y) {
//		union SIMDUnion { _simd_u32x16 v1; _simd_u32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x16_or_enable() _simd_u32x32_or_enable()
//#elif defined(_simd_u32x64_or_)
//	static ANVIL_STRONG_INLINE _simd_u32x16 ANVIL_SIMD_CALL _simd_u32x16_or(const register _simd_u32x16 x, const register _simd_u32x16 y) {
//		union SIMDUnion { _simd_u32x16 v1; _simd_u32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x16_or_enable() _simd_u32x64_or_enable()
//#else
//	#define _simd_u32x16_or(X,Y) _simd_u32x16_combine(\
//		_simd_u32x8_or(_simd_u32x16_splitlo(X), _simd_u32x16_splitlo(Y)),\
//		_simd_u32x8_or(_simd_u32x16_splithi(X), _simd_u32x16_splithi(Y)))
//	#define _simd_u32x16_or_enable() (_simd_u32x8_or_enable() && _simd_u32x16_combine_enable() && _simd_u32x16_splitlo_enable()  && _simd_u32x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x16_or_) && ! defined(_simd_u32x16_or_scalar_)
//	#define _simd_u32x16_or_scalar_(X,Y) _simd_u32x16_or_(X,_simd_u32x16_fill_scalar_(Y))
//	#define _simd_u32x16_or_scalar_instruction_set _simd_u32x16_or_instruction_set
//#endif
//#ifdef _simd_u32x16_or_scalar_
//	#define _simd_u32x16_or_scalar(X,Y) _simd_u32x16_or_scalar_(X,Y)
//	#define _simd_u32x16_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_or_scalar_instruction_set>()
//#else
//	#define _simd_u32x16_or_scalar(X,Y) _simd_u32x16_or_safe(X,_simd_u32x16_fill_scalar_safe(Y))
//	#define _simd_u32x16_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_u32x1_or_safe
//	#define _simd_u32x1_or_safe(X,Y) (X | Y)
//	#define _simd_u32x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_u32x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_or_enabled() true
//#endif
//
//#define _simd_u32x32_or_safe(X,Y)_simd_u32x32_combine_safe(\
//	_simd_u32x16_or_safe(_simd_u32x32_splitlo_safe(X), _simd_ u32x32_splitlo_safe(Y)),\
//	_simd_u32x16_or_safe(_simd_u32x32_splithi_safe(X), _simd_ u32x32_splithi_safe(Y)))
//#ifdef _simd_u32x32_or_
//	#define _simd_u32x32_or(X,Y) _simd_u32x32_or_(X, Y)
//	#define _simd_u32x32_or_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_or_instruction_set>()
//#elif defined(_simd_u32x64_or_)
//	static ANVIL_STRONG_INLINE _simd_u32x32 ANVIL_SIMD_CALL _simd_u32x32_or(const register _simd_u32x32 x, const register _simd_u32x32 y) {
//		union SIMDUnion { _simd_u32x32 v1; _simd_u32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x32_or_enable() _simd_u32x64_or_enable()
//#else
//	#define _simd_u32x32_or(X,Y) _simd_u32x32_combine(\
//		_simd_u32x16_or(_simd_u32x32_splitlo(X), _simd_u32x32_splitlo(Y)),\
//		_simd_u32x16_or(_simd_u32x32_splithi(X), _simd_u32x32_splithi(Y)))
//	#define _simd_u32x32_or_enable() (_simd_u32x16_or_enable() && _simd_u32x32_combine_enable() && _simd_u32x32_splitlo_enable()  && _simd_u32x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x32_or_) && ! defined(_simd_u32x32_or_scalar_)
//	#define _simd_u32x32_or_scalar_(X,Y) _simd_u32x32_or_(X,_simd_u32x32_fill_scalar_(Y))
//	#define _simd_u32x32_or_scalar_instruction_set _simd_u32x32_or_instruction_set
//#endif
//#ifdef _simd_u32x32_or_scalar_
//	#define _simd_u32x32_or_scalar(X,Y) _simd_u32x32_or_scalar_(X,Y)
//	#define _simd_u32x32_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_or_scalar_instruction_set>()
//#else
//	#define _simd_u32x32_or_scalar(X,Y) _simd_u32x32_or_safe(X,_simd_u32x32_fill_scalar_safe(Y))
//	#define _simd_u32x32_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_u32x1_or_safe
//	#define _simd_u32x1_or_safe(X,Y) (X | Y)
//	#define _simd_u32x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_u32x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_or_enabled() true
//#endif
//
//#define _simd_u32x64_or_safe(X,Y)_simd_u32x64_combine_safe(\
//	_simd_u32x32_or_safe(_simd_u32x64_splitlo_safe(X), _simd_ u32x64_splitlo_safe(Y)),\
//	_simd_u32x32_or_safe(_simd_u32x64_splithi_safe(X), _simd_ u32x64_splithi_safe(Y)))
//#ifdef _simd_u32x64_or_
//	#define _simd_u32x64_or(X,Y) _simd_u32x64_or_(X, Y)
//	#define _simd_u32x64_or_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_or_instruction_set>()
//#else
//	#define _simd_u32x64_or(X,Y) _simd_u32x64_combine(\
//		_simd_u32x32_or(_simd_u32x64_splitlo(X), _simd_u32x64_splitlo(Y)),\
//		_simd_u32x32_or(_simd_u32x64_splithi(X), _simd_u32x64_splithi(Y)))
//	#define _simd_u32x64_or_enable() (_simd_u32x32_or_enable() && _simd_u32x64_combine_enable() && _simd_u32x64_splitlo_enable()  && _simd_u32x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x64_or_) && ! defined(_simd_u32x64_or_scalar_)
//	#define _simd_u32x64_or_scalar_(X,Y) _simd_u32x64_or_(X,_simd_u32x64_fill_scalar_(Y))
//	#define _simd_u32x64_or_scalar_instruction_set _simd_u32x64_or_instruction_set
//#endif
//#ifdef _simd_u32x64_or_scalar_
//	#define _simd_u32x64_or_scalar(X,Y) _simd_u32x64_or_scalar_(X,Y)
//	#define _simd_u32x64_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_or_scalar_instruction_set>()
//#else
//	#define _simd_u32x64_or_scalar(X,Y) _simd_u32x64_or_safe(X,_simd_u32x64_fill_scalar_safe(Y))
//	#define _simd_u32x64_or_scalar_enabled() true
//#endif
//
//// -- s16 --
//
//#ifndef _simd_s16x1_or_safe
//	#define _simd_s16x1_or_safe(X,Y) (X | Y)
//	#define _simd_s16x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_s16x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_or_enabled() true
//#endif
//
//#define _simd_s16x2_or_safe(X,Y)_simd_s16x2_combine_safe(\
//	_simd_s16x1_or_safe(_simd_s16x2_splitlo_safe(X), _simd_ s16x2_splitlo_safe(Y)),\
//	_simd_s16x1_or_safe(_simd_s16x2_splithi_safe(X), _simd_ s16x2_splithi_safe(Y)))
//#ifdef _simd_s16x2_or_
//	#define _simd_s16x2_or(X,Y) _simd_s16x2_or_(X, Y)
//	#define _simd_s16x2_or_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_or_instruction_set>()
//#elif defined(_simd_s16x4_or_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_or(const register _simd_s16x2 x, const register _simd_s16x2 y) {
//		union SIMDUnion { _simd_s16x2 v1; _simd_s16x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x4_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x2_or_enable() _simd_s16x4_or_enable()
//#elif defined(_simd_s16x8_or_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_or(const register _simd_s16x2 x, const register _simd_s16x2 y) {
//		union SIMDUnion { _simd_s16x2 v1; _simd_s16x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x8_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x2_or_enable() _simd_s16x8_or_enable()
//#elif defined(_simd_s16x16_or_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_or(const register _simd_s16x2 x, const register _simd_s16x2 y) {
//		union SIMDUnion { _simd_s16x2 v1; _simd_s16x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x16_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x2_or_enable() _simd_s16x16_or_enable()
//#elif defined(_simd_s16x32_or_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_or(const register _simd_s16x2 x, const register _simd_s16x2 y) {
//		union SIMDUnion { _simd_s16x2 v1; _simd_s16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x2_or_enable() _simd_s16x32_or_enable()
//#elif defined(_simd_s16x64_or_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_or(const register _simd_s16x2 x, const register _simd_s16x2 y) {
//		union SIMDUnion { _simd_s16x2 v1; _simd_s16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x2_or_enable() _simd_s16x64_or_enable()
//#else
//	#define _simd_s16x2_or(X,Y) _simd_s16x2_combine(\
//		_simd_s16x1_or(_simd_s16x2_splitlo(X), _simd_s16x2_splitlo(Y)),\
//		_simd_s16x1_or(_simd_s16x2_splithi(X), _simd_s16x2_splithi(Y)))
//	#define _simd_s16x2_or_enable() (_simd_s16x1_or_enable() && _simd_s16x2_combine_enable() && _simd_s16x2_splitlo_enable()  && _simd_s16x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x2_or_) && ! defined(_simd_s16x2_or_scalar_)
//	#define _simd_s16x2_or_scalar_(X,Y) _simd_s16x2_or_(X,_simd_s16x2_fill_scalar_(Y))
//	#define _simd_s16x2_or_scalar_instruction_set _simd_s16x2_or_instruction_set
//#endif
//#ifdef _simd_s16x2_or_scalar_
//	#define _simd_s16x2_or_scalar(X,Y) _simd_s16x2_or_scalar_(X,Y)
//	#define _simd_s16x2_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_or_scalar_instruction_set>()
//#else
//	#define _simd_s16x2_or_scalar(X,Y) _simd_s16x2_or_safe(X,_simd_s16x2_fill_scalar_safe(Y))
//	#define _simd_s16x2_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_s16x1_or_safe
//	#define _simd_s16x1_or_safe(X,Y) (X | Y)
//	#define _simd_s16x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_s16x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_or_enabled() true
//#endif
//
//#define _simd_s16x4_or_safe(X,Y)_simd_s16x4_combine_safe(\
//	_simd_s16x2_or_safe(_simd_s16x4_splitlo_safe(X), _simd_ s16x4_splitlo_safe(Y)),\
//	_simd_s16x2_or_safe(_simd_s16x4_splithi_safe(X), _simd_ s16x4_splithi_safe(Y)))
//#ifdef _simd_s16x4_or_
//	#define _simd_s16x4_or(X,Y) _simd_s16x4_or_(X, Y)
//	#define _simd_s16x4_or_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_or_instruction_set>()
//#elif defined(_simd_s16x8_or_)
//	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_or(const register _simd_s16x4 x, const register _simd_s16x4 y) {
//		union SIMDUnion { _simd_s16x4 v1; _simd_s16x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x8_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x4_or_enable() _simd_s16x8_or_enable()
//#elif defined(_simd_s16x16_or_)
//	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_or(const register _simd_s16x4 x, const register _simd_s16x4 y) {
//		union SIMDUnion { _simd_s16x4 v1; _simd_s16x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x16_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x4_or_enable() _simd_s16x16_or_enable()
//#elif defined(_simd_s16x32_or_)
//	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_or(const register _simd_s16x4 x, const register _simd_s16x4 y) {
//		union SIMDUnion { _simd_s16x4 v1; _simd_s16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x4_or_enable() _simd_s16x32_or_enable()
//#elif defined(_simd_s16x64_or_)
//	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_or(const register _simd_s16x4 x, const register _simd_s16x4 y) {
//		union SIMDUnion { _simd_s16x4 v1; _simd_s16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x4_or_enable() _simd_s16x64_or_enable()
//#else
//	#define _simd_s16x4_or(X,Y) _simd_s16x4_combine(\
//		_simd_s16x2_or(_simd_s16x4_splitlo(X), _simd_s16x4_splitlo(Y)),\
//		_simd_s16x2_or(_simd_s16x4_splithi(X), _simd_s16x4_splithi(Y)))
//	#define _simd_s16x4_or_enable() (_simd_s16x2_or_enable() && _simd_s16x4_combine_enable() && _simd_s16x4_splitlo_enable()  && _simd_s16x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x4_or_) && ! defined(_simd_s16x4_or_scalar_)
//	#define _simd_s16x4_or_scalar_(X,Y) _simd_s16x4_or_(X,_simd_s16x4_fill_scalar_(Y))
//	#define _simd_s16x4_or_scalar_instruction_set _simd_s16x4_or_instruction_set
//#endif
//#ifdef _simd_s16x4_or_scalar_
//	#define _simd_s16x4_or_scalar(X,Y) _simd_s16x4_or_scalar_(X,Y)
//	#define _simd_s16x4_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_or_scalar_instruction_set>()
//#else
//	#define _simd_s16x4_or_scalar(X,Y) _simd_s16x4_or_safe(X,_simd_s16x4_fill_scalar_safe(Y))
//	#define _simd_s16x4_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_s16x1_or_safe
//	#define _simd_s16x1_or_safe(X,Y) (X | Y)
//	#define _simd_s16x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_s16x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_or_enabled() true
//#endif
//
//#define _simd_s16x8_or_safe(X,Y)_simd_s16x8_combine_safe(\
//	_simd_s16x4_or_safe(_simd_s16x8_splitlo_safe(X), _simd_ s16x8_splitlo_safe(Y)),\
//	_simd_s16x4_or_safe(_simd_s16x8_splithi_safe(X), _simd_ s16x8_splithi_safe(Y)))
//#ifdef _simd_s16x8_or_
//	#define _simd_s16x8_or(X,Y) _simd_s16x8_or_(X, Y)
//	#define _simd_s16x8_or_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_or_instruction_set>()
//#elif defined(_simd_s16x16_or_)
//	static ANVIL_STRONG_INLINE _simd_s16x8 ANVIL_SIMD_CALL _simd_s16x8_or(const register _simd_s16x8 x, const register _simd_s16x8 y) {
//		union SIMDUnion { _simd_s16x8 v1; _simd_s16x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x16_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x8_or_enable() _simd_s16x16_or_enable()
//#elif defined(_simd_s16x32_or_)
//	static ANVIL_STRONG_INLINE _simd_s16x8 ANVIL_SIMD_CALL _simd_s16x8_or(const register _simd_s16x8 x, const register _simd_s16x8 y) {
//		union SIMDUnion { _simd_s16x8 v1; _simd_s16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x8_or_enable() _simd_s16x32_or_enable()
//#elif defined(_simd_s16x64_or_)
//	static ANVIL_STRONG_INLINE _simd_s16x8 ANVIL_SIMD_CALL _simd_s16x8_or(const register _simd_s16x8 x, const register _simd_s16x8 y) {
//		union SIMDUnion { _simd_s16x8 v1; _simd_s16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x8_or_enable() _simd_s16x64_or_enable()
//#else
//	#define _simd_s16x8_or(X,Y) _simd_s16x8_combine(\
//		_simd_s16x4_or(_simd_s16x8_splitlo(X), _simd_s16x8_splitlo(Y)),\
//		_simd_s16x4_or(_simd_s16x8_splithi(X), _simd_s16x8_splithi(Y)))
//	#define _simd_s16x8_or_enable() (_simd_s16x4_or_enable() && _simd_s16x8_combine_enable() && _simd_s16x8_splitlo_enable()  && _simd_s16x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x8_or_) && ! defined(_simd_s16x8_or_scalar_)
//	#define _simd_s16x8_or_scalar_(X,Y) _simd_s16x8_or_(X,_simd_s16x8_fill_scalar_(Y))
//	#define _simd_s16x8_or_scalar_instruction_set _simd_s16x8_or_instruction_set
//#endif
//#ifdef _simd_s16x8_or_scalar_
//	#define _simd_s16x8_or_scalar(X,Y) _simd_s16x8_or_scalar_(X,Y)
//	#define _simd_s16x8_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_or_scalar_instruction_set>()
//#else
//	#define _simd_s16x8_or_scalar(X,Y) _simd_s16x8_or_safe(X,_simd_s16x8_fill_scalar_safe(Y))
//	#define _simd_s16x8_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_s16x1_or_safe
//	#define _simd_s16x1_or_safe(X,Y) (X | Y)
//	#define _simd_s16x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_s16x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_or_enabled() true
//#endif
//
//#define _simd_s16x16_or_safe(X,Y)_simd_s16x16_combine_safe(\
//	_simd_s16x8_or_safe(_simd_s16x16_splitlo_safe(X), _simd_ s16x16_splitlo_safe(Y)),\
//	_simd_s16x8_or_safe(_simd_s16x16_splithi_safe(X), _simd_ s16x16_splithi_safe(Y)))
//#ifdef _simd_s16x16_or_
//	#define _simd_s16x16_or(X,Y) _simd_s16x16_or_(X, Y)
//	#define _simd_s16x16_or_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_or_instruction_set>()
//#elif defined(_simd_s16x32_or_)
//	static ANVIL_STRONG_INLINE _simd_s16x16 ANVIL_SIMD_CALL _simd_s16x16_or(const register _simd_s16x16 x, const register _simd_s16x16 y) {
//		union SIMDUnion { _simd_s16x16 v1; _simd_s16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x16_or_enable() _simd_s16x32_or_enable()
//#elif defined(_simd_s16x64_or_)
//	static ANVIL_STRONG_INLINE _simd_s16x16 ANVIL_SIMD_CALL _simd_s16x16_or(const register _simd_s16x16 x, const register _simd_s16x16 y) {
//		union SIMDUnion { _simd_s16x16 v1; _simd_s16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x16_or_enable() _simd_s16x64_or_enable()
//#else
//	#define _simd_s16x16_or(X,Y) _simd_s16x16_combine(\
//		_simd_s16x8_or(_simd_s16x16_splitlo(X), _simd_s16x16_splitlo(Y)),\
//		_simd_s16x8_or(_simd_s16x16_splithi(X), _simd_s16x16_splithi(Y)))
//	#define _simd_s16x16_or_enable() (_simd_s16x8_or_enable() && _simd_s16x16_combine_enable() && _simd_s16x16_splitlo_enable()  && _simd_s16x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x16_or_) && ! defined(_simd_s16x16_or_scalar_)
//	#define _simd_s16x16_or_scalar_(X,Y) _simd_s16x16_or_(X,_simd_s16x16_fill_scalar_(Y))
//	#define _simd_s16x16_or_scalar_instruction_set _simd_s16x16_or_instruction_set
//#endif
//#ifdef _simd_s16x16_or_scalar_
//	#define _simd_s16x16_or_scalar(X,Y) _simd_s16x16_or_scalar_(X,Y)
//	#define _simd_s16x16_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_or_scalar_instruction_set>()
//#else
//	#define _simd_s16x16_or_scalar(X,Y) _simd_s16x16_or_safe(X,_simd_s16x16_fill_scalar_safe(Y))
//	#define _simd_s16x16_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_s16x1_or_safe
//	#define _simd_s16x1_or_safe(X,Y) (X | Y)
//	#define _simd_s16x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_s16x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_or_enabled() true
//#endif
//
//#define _simd_s16x32_or_safe(X,Y)_simd_s16x32_combine_safe(\
//	_simd_s16x16_or_safe(_simd_s16x32_splitlo_safe(X), _simd_ s16x32_splitlo_safe(Y)),\
//	_simd_s16x16_or_safe(_simd_s16x32_splithi_safe(X), _simd_ s16x32_splithi_safe(Y)))
//#ifdef _simd_s16x32_or_
//	#define _simd_s16x32_or(X,Y) _simd_s16x32_or_(X, Y)
//	#define _simd_s16x32_or_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_or_instruction_set>()
//#elif defined(_simd_s16x64_or_)
//	static ANVIL_STRONG_INLINE _simd_s16x32 ANVIL_SIMD_CALL _simd_s16x32_or(const register _simd_s16x32 x, const register _simd_s16x32 y) {
//		union SIMDUnion { _simd_s16x32 v1; _simd_s16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x32_or_enable() _simd_s16x64_or_enable()
//#else
//	#define _simd_s16x32_or(X,Y) _simd_s16x32_combine(\
//		_simd_s16x16_or(_simd_s16x32_splitlo(X), _simd_s16x32_splitlo(Y)),\
//		_simd_s16x16_or(_simd_s16x32_splithi(X), _simd_s16x32_splithi(Y)))
//	#define _simd_s16x32_or_enable() (_simd_s16x16_or_enable() && _simd_s16x32_combine_enable() && _simd_s16x32_splitlo_enable()  && _simd_s16x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x32_or_) && ! defined(_simd_s16x32_or_scalar_)
//	#define _simd_s16x32_or_scalar_(X,Y) _simd_s16x32_or_(X,_simd_s16x32_fill_scalar_(Y))
//	#define _simd_s16x32_or_scalar_instruction_set _simd_s16x32_or_instruction_set
//#endif
//#ifdef _simd_s16x32_or_scalar_
//	#define _simd_s16x32_or_scalar(X,Y) _simd_s16x32_or_scalar_(X,Y)
//	#define _simd_s16x32_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_or_scalar_instruction_set>()
//#else
//	#define _simd_s16x32_or_scalar(X,Y) _simd_s16x32_or_safe(X,_simd_s16x32_fill_scalar_safe(Y))
//	#define _simd_s16x32_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_s16x1_or_safe
//	#define _simd_s16x1_or_safe(X,Y) (X | Y)
//	#define _simd_s16x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_s16x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_or_enabled() true
//#endif
//
//#define _simd_s16x64_or_safe(X,Y)_simd_s16x64_combine_safe(\
//	_simd_s16x32_or_safe(_simd_s16x64_splitlo_safe(X), _simd_ s16x64_splitlo_safe(Y)),\
//	_simd_s16x32_or_safe(_simd_s16x64_splithi_safe(X), _simd_ s16x64_splithi_safe(Y)))
//#ifdef _simd_s16x64_or_
//	#define _simd_s16x64_or(X,Y) _simd_s16x64_or_(X, Y)
//	#define _simd_s16x64_or_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_or_instruction_set>()
//#else
//	#define _simd_s16x64_or(X,Y) _simd_s16x64_combine(\
//		_simd_s16x32_or(_simd_s16x64_splitlo(X), _simd_s16x64_splitlo(Y)),\
//		_simd_s16x32_or(_simd_s16x64_splithi(X), _simd_s16x64_splithi(Y)))
//	#define _simd_s16x64_or_enable() (_simd_s16x32_or_enable() && _simd_s16x64_combine_enable() && _simd_s16x64_splitlo_enable()  && _simd_s16x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x64_or_) && ! defined(_simd_s16x64_or_scalar_)
//	#define _simd_s16x64_or_scalar_(X,Y) _simd_s16x64_or_(X,_simd_s16x64_fill_scalar_(Y))
//	#define _simd_s16x64_or_scalar_instruction_set _simd_s16x64_or_instruction_set
//#endif
//#ifdef _simd_s16x64_or_scalar_
//	#define _simd_s16x64_or_scalar(X,Y) _simd_s16x64_or_scalar_(X,Y)
//	#define _simd_s16x64_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_or_scalar_instruction_set>()
//#else
//	#define _simd_s16x64_or_scalar(X,Y) _simd_s16x64_or_safe(X,_simd_s16x64_fill_scalar_safe(Y))
//	#define _simd_s16x64_or_scalar_enabled() true
//#endif
//
//// -- u16 --
//
//#ifndef _simd_u16x1_or_safe
//	#define _simd_u16x1_or_safe(X,Y) (X | Y)
//	#define _simd_u16x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_u16x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_or_enabled() true
//#endif
//
//#define _simd_u16x2_or_safe(X,Y)_simd_u16x2_combine_safe(\
//	_simd_u16x1_or_safe(_simd_u16x2_splitlo_safe(X), _simd_ u16x2_splitlo_safe(Y)),\
//	_simd_u16x1_or_safe(_simd_u16x2_splithi_safe(X), _simd_ u16x2_splithi_safe(Y)))
//#ifdef _simd_u16x2_or_
//	#define _simd_u16x2_or(X,Y) _simd_u16x2_or_(X, Y)
//	#define _simd_u16x2_or_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_or_instruction_set>()
//#elif defined(_simd_u16x4_or_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_or(const register _simd_u16x2 x, const register _simd_u16x2 y) {
//		union SIMDUnion { _simd_u16x2 v1; _simd_u16x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x4_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x2_or_enable() _simd_u16x4_or_enable()
//#elif defined(_simd_u16x8_or_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_or(const register _simd_u16x2 x, const register _simd_u16x2 y) {
//		union SIMDUnion { _simd_u16x2 v1; _simd_u16x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x8_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x2_or_enable() _simd_u16x8_or_enable()
//#elif defined(_simd_u16x16_or_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_or(const register _simd_u16x2 x, const register _simd_u16x2 y) {
//		union SIMDUnion { _simd_u16x2 v1; _simd_u16x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x16_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x2_or_enable() _simd_u16x16_or_enable()
//#elif defined(_simd_u16x32_or_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_or(const register _simd_u16x2 x, const register _simd_u16x2 y) {
//		union SIMDUnion { _simd_u16x2 v1; _simd_u16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x2_or_enable() _simd_u16x32_or_enable()
//#elif defined(_simd_u16x64_or_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_or(const register _simd_u16x2 x, const register _simd_u16x2 y) {
//		union SIMDUnion { _simd_u16x2 v1; _simd_u16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x2_or_enable() _simd_u16x64_or_enable()
//#else
//	#define _simd_u16x2_or(X,Y) _simd_u16x2_combine(\
//		_simd_u16x1_or(_simd_u16x2_splitlo(X), _simd_u16x2_splitlo(Y)),\
//		_simd_u16x1_or(_simd_u16x2_splithi(X), _simd_u16x2_splithi(Y)))
//	#define _simd_u16x2_or_enable() (_simd_u16x1_or_enable() && _simd_u16x2_combine_enable() && _simd_u16x2_splitlo_enable()  && _simd_u16x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x2_or_) && ! defined(_simd_u16x2_or_scalar_)
//	#define _simd_u16x2_or_scalar_(X,Y) _simd_u16x2_or_(X,_simd_u16x2_fill_scalar_(Y))
//	#define _simd_u16x2_or_scalar_instruction_set _simd_u16x2_or_instruction_set
//#endif
//#ifdef _simd_u16x2_or_scalar_
//	#define _simd_u16x2_or_scalar(X,Y) _simd_u16x2_or_scalar_(X,Y)
//	#define _simd_u16x2_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_or_scalar_instruction_set>()
//#else
//	#define _simd_u16x2_or_scalar(X,Y) _simd_u16x2_or_safe(X,_simd_u16x2_fill_scalar_safe(Y))
//	#define _simd_u16x2_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_u16x1_or_safe
//	#define _simd_u16x1_or_safe(X,Y) (X | Y)
//	#define _simd_u16x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_u16x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_or_enabled() true
//#endif
//
//#define _simd_u16x4_or_safe(X,Y)_simd_u16x4_combine_safe(\
//	_simd_u16x2_or_safe(_simd_u16x4_splitlo_safe(X), _simd_ u16x4_splitlo_safe(Y)),\
//	_simd_u16x2_or_safe(_simd_u16x4_splithi_safe(X), _simd_ u16x4_splithi_safe(Y)))
//#ifdef _simd_u16x4_or_
//	#define _simd_u16x4_or(X,Y) _simd_u16x4_or_(X, Y)
//	#define _simd_u16x4_or_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_or_instruction_set>()
//#elif defined(_simd_u16x8_or_)
//	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_or(const register _simd_u16x4 x, const register _simd_u16x4 y) {
//		union SIMDUnion { _simd_u16x4 v1; _simd_u16x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x8_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x4_or_enable() _simd_u16x8_or_enable()
//#elif defined(_simd_u16x16_or_)
//	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_or(const register _simd_u16x4 x, const register _simd_u16x4 y) {
//		union SIMDUnion { _simd_u16x4 v1; _simd_u16x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x16_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x4_or_enable() _simd_u16x16_or_enable()
//#elif defined(_simd_u16x32_or_)
//	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_or(const register _simd_u16x4 x, const register _simd_u16x4 y) {
//		union SIMDUnion { _simd_u16x4 v1; _simd_u16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x4_or_enable() _simd_u16x32_or_enable()
//#elif defined(_simd_u16x64_or_)
//	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_or(const register _simd_u16x4 x, const register _simd_u16x4 y) {
//		union SIMDUnion { _simd_u16x4 v1; _simd_u16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x4_or_enable() _simd_u16x64_or_enable()
//#else
//	#define _simd_u16x4_or(X,Y) _simd_u16x4_combine(\
//		_simd_u16x2_or(_simd_u16x4_splitlo(X), _simd_u16x4_splitlo(Y)),\
//		_simd_u16x2_or(_simd_u16x4_splithi(X), _simd_u16x4_splithi(Y)))
//	#define _simd_u16x4_or_enable() (_simd_u16x2_or_enable() && _simd_u16x4_combine_enable() && _simd_u16x4_splitlo_enable()  && _simd_u16x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x4_or_) && ! defined(_simd_u16x4_or_scalar_)
//	#define _simd_u16x4_or_scalar_(X,Y) _simd_u16x4_or_(X,_simd_u16x4_fill_scalar_(Y))
//	#define _simd_u16x4_or_scalar_instruction_set _simd_u16x4_or_instruction_set
//#endif
//#ifdef _simd_u16x4_or_scalar_
//	#define _simd_u16x4_or_scalar(X,Y) _simd_u16x4_or_scalar_(X,Y)
//	#define _simd_u16x4_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_or_scalar_instruction_set>()
//#else
//	#define _simd_u16x4_or_scalar(X,Y) _simd_u16x4_or_safe(X,_simd_u16x4_fill_scalar_safe(Y))
//	#define _simd_u16x4_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_u16x1_or_safe
//	#define _simd_u16x1_or_safe(X,Y) (X | Y)
//	#define _simd_u16x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_u16x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_or_enabled() true
//#endif
//
//#define _simd_u16x8_or_safe(X,Y)_simd_u16x8_combine_safe(\
//	_simd_u16x4_or_safe(_simd_u16x8_splitlo_safe(X), _simd_ u16x8_splitlo_safe(Y)),\
//	_simd_u16x4_or_safe(_simd_u16x8_splithi_safe(X), _simd_ u16x8_splithi_safe(Y)))
//#ifdef _simd_u16x8_or_
//	#define _simd_u16x8_or(X,Y) _simd_u16x8_or_(X, Y)
//	#define _simd_u16x8_or_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_or_instruction_set>()
//#elif defined(_simd_u16x16_or_)
//	static ANVIL_STRONG_INLINE _simd_u16x8 ANVIL_SIMD_CALL _simd_u16x8_or(const register _simd_u16x8 x, const register _simd_u16x8 y) {
//		union SIMDUnion { _simd_u16x8 v1; _simd_u16x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x16_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x8_or_enable() _simd_u16x16_or_enable()
//#elif defined(_simd_u16x32_or_)
//	static ANVIL_STRONG_INLINE _simd_u16x8 ANVIL_SIMD_CALL _simd_u16x8_or(const register _simd_u16x8 x, const register _simd_u16x8 y) {
//		union SIMDUnion { _simd_u16x8 v1; _simd_u16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x8_or_enable() _simd_u16x32_or_enable()
//#elif defined(_simd_u16x64_or_)
//	static ANVIL_STRONG_INLINE _simd_u16x8 ANVIL_SIMD_CALL _simd_u16x8_or(const register _simd_u16x8 x, const register _simd_u16x8 y) {
//		union SIMDUnion { _simd_u16x8 v1; _simd_u16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x8_or_enable() _simd_u16x64_or_enable()
//#else
//	#define _simd_u16x8_or(X,Y) _simd_u16x8_combine(\
//		_simd_u16x4_or(_simd_u16x8_splitlo(X), _simd_u16x8_splitlo(Y)),\
//		_simd_u16x4_or(_simd_u16x8_splithi(X), _simd_u16x8_splithi(Y)))
//	#define _simd_u16x8_or_enable() (_simd_u16x4_or_enable() && _simd_u16x8_combine_enable() && _simd_u16x8_splitlo_enable()  && _simd_u16x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x8_or_) && ! defined(_simd_u16x8_or_scalar_)
//	#define _simd_u16x8_or_scalar_(X,Y) _simd_u16x8_or_(X,_simd_u16x8_fill_scalar_(Y))
//	#define _simd_u16x8_or_scalar_instruction_set _simd_u16x8_or_instruction_set
//#endif
//#ifdef _simd_u16x8_or_scalar_
//	#define _simd_u16x8_or_scalar(X,Y) _simd_u16x8_or_scalar_(X,Y)
//	#define _simd_u16x8_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_or_scalar_instruction_set>()
//#else
//	#define _simd_u16x8_or_scalar(X,Y) _simd_u16x8_or_safe(X,_simd_u16x8_fill_scalar_safe(Y))
//	#define _simd_u16x8_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_u16x1_or_safe
//	#define _simd_u16x1_or_safe(X,Y) (X | Y)
//	#define _simd_u16x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_u16x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_or_enabled() true
//#endif
//
//#define _simd_u16x16_or_safe(X,Y)_simd_u16x16_combine_safe(\
//	_simd_u16x8_or_safe(_simd_u16x16_splitlo_safe(X), _simd_ u16x16_splitlo_safe(Y)),\
//	_simd_u16x8_or_safe(_simd_u16x16_splithi_safe(X), _simd_ u16x16_splithi_safe(Y)))
//#ifdef _simd_u16x16_or_
//	#define _simd_u16x16_or(X,Y) _simd_u16x16_or_(X, Y)
//	#define _simd_u16x16_or_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_or_instruction_set>()
//#elif defined(_simd_u16x32_or_)
//	static ANVIL_STRONG_INLINE _simd_u16x16 ANVIL_SIMD_CALL _simd_u16x16_or(const register _simd_u16x16 x, const register _simd_u16x16 y) {
//		union SIMDUnion { _simd_u16x16 v1; _simd_u16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x16_or_enable() _simd_u16x32_or_enable()
//#elif defined(_simd_u16x64_or_)
//	static ANVIL_STRONG_INLINE _simd_u16x16 ANVIL_SIMD_CALL _simd_u16x16_or(const register _simd_u16x16 x, const register _simd_u16x16 y) {
//		union SIMDUnion { _simd_u16x16 v1; _simd_u16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x16_or_enable() _simd_u16x64_or_enable()
//#else
//	#define _simd_u16x16_or(X,Y) _simd_u16x16_combine(\
//		_simd_u16x8_or(_simd_u16x16_splitlo(X), _simd_u16x16_splitlo(Y)),\
//		_simd_u16x8_or(_simd_u16x16_splithi(X), _simd_u16x16_splithi(Y)))
//	#define _simd_u16x16_or_enable() (_simd_u16x8_or_enable() && _simd_u16x16_combine_enable() && _simd_u16x16_splitlo_enable()  && _simd_u16x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x16_or_) && ! defined(_simd_u16x16_or_scalar_)
//	#define _simd_u16x16_or_scalar_(X,Y) _simd_u16x16_or_(X,_simd_u16x16_fill_scalar_(Y))
//	#define _simd_u16x16_or_scalar_instruction_set _simd_u16x16_or_instruction_set
//#endif
//#ifdef _simd_u16x16_or_scalar_
//	#define _simd_u16x16_or_scalar(X,Y) _simd_u16x16_or_scalar_(X,Y)
//	#define _simd_u16x16_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_or_scalar_instruction_set>()
//#else
//	#define _simd_u16x16_or_scalar(X,Y) _simd_u16x16_or_safe(X,_simd_u16x16_fill_scalar_safe(Y))
//	#define _simd_u16x16_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_u16x1_or_safe
//	#define _simd_u16x1_or_safe(X,Y) (X | Y)
//	#define _simd_u16x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_u16x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_or_enabled() true
//#endif
//
//#define _simd_u16x32_or_safe(X,Y)_simd_u16x32_combine_safe(\
//	_simd_u16x16_or_safe(_simd_u16x32_splitlo_safe(X), _simd_ u16x32_splitlo_safe(Y)),\
//	_simd_u16x16_or_safe(_simd_u16x32_splithi_safe(X), _simd_ u16x32_splithi_safe(Y)))
//#ifdef _simd_u16x32_or_
//	#define _simd_u16x32_or(X,Y) _simd_u16x32_or_(X, Y)
//	#define _simd_u16x32_or_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_or_instruction_set>()
//#elif defined(_simd_u16x64_or_)
//	static ANVIL_STRONG_INLINE _simd_u16x32 ANVIL_SIMD_CALL _simd_u16x32_or(const register _simd_u16x32 x, const register _simd_u16x32 y) {
//		union SIMDUnion { _simd_u16x32 v1; _simd_u16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x32_or_enable() _simd_u16x64_or_enable()
//#else
//	#define _simd_u16x32_or(X,Y) _simd_u16x32_combine(\
//		_simd_u16x16_or(_simd_u16x32_splitlo(X), _simd_u16x32_splitlo(Y)),\
//		_simd_u16x16_or(_simd_u16x32_splithi(X), _simd_u16x32_splithi(Y)))
//	#define _simd_u16x32_or_enable() (_simd_u16x16_or_enable() && _simd_u16x32_combine_enable() && _simd_u16x32_splitlo_enable()  && _simd_u16x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x32_or_) && ! defined(_simd_u16x32_or_scalar_)
//	#define _simd_u16x32_or_scalar_(X,Y) _simd_u16x32_or_(X,_simd_u16x32_fill_scalar_(Y))
//	#define _simd_u16x32_or_scalar_instruction_set _simd_u16x32_or_instruction_set
//#endif
//#ifdef _simd_u16x32_or_scalar_
//	#define _simd_u16x32_or_scalar(X,Y) _simd_u16x32_or_scalar_(X,Y)
//	#define _simd_u16x32_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_or_scalar_instruction_set>()
//#else
//	#define _simd_u16x32_or_scalar(X,Y) _simd_u16x32_or_safe(X,_simd_u16x32_fill_scalar_safe(Y))
//	#define _simd_u16x32_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_u16x1_or_safe
//	#define _simd_u16x1_or_safe(X,Y) (X | Y)
//	#define _simd_u16x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_u16x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_or_enabled() true
//#endif
//
//#define _simd_u16x64_or_safe(X,Y)_simd_u16x64_combine_safe(\
//	_simd_u16x32_or_safe(_simd_u16x64_splitlo_safe(X), _simd_ u16x64_splitlo_safe(Y)),\
//	_simd_u16x32_or_safe(_simd_u16x64_splithi_safe(X), _simd_ u16x64_splithi_safe(Y)))
//#ifdef _simd_u16x64_or_
//	#define _simd_u16x64_or(X,Y) _simd_u16x64_or_(X, Y)
//	#define _simd_u16x64_or_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_or_instruction_set>()
//#else
//	#define _simd_u16x64_or(X,Y) _simd_u16x64_combine(\
//		_simd_u16x32_or(_simd_u16x64_splitlo(X), _simd_u16x64_splitlo(Y)),\
//		_simd_u16x32_or(_simd_u16x64_splithi(X), _simd_u16x64_splithi(Y)))
//	#define _simd_u16x64_or_enable() (_simd_u16x32_or_enable() && _simd_u16x64_combine_enable() && _simd_u16x64_splitlo_enable()  && _simd_u16x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x64_or_) && ! defined(_simd_u16x64_or_scalar_)
//	#define _simd_u16x64_or_scalar_(X,Y) _simd_u16x64_or_(X,_simd_u16x64_fill_scalar_(Y))
//	#define _simd_u16x64_or_scalar_instruction_set _simd_u16x64_or_instruction_set
//#endif
//#ifdef _simd_u16x64_or_scalar_
//	#define _simd_u16x64_or_scalar(X,Y) _simd_u16x64_or_scalar_(X,Y)
//	#define _simd_u16x64_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_or_scalar_instruction_set>()
//#else
//	#define _simd_u16x64_or_scalar(X,Y) _simd_u16x64_or_safe(X,_simd_u16x64_fill_scalar_safe(Y))
//	#define _simd_u16x64_or_scalar_enabled() true
//#endif
//
//// -- s8 --
//
//#ifndef _simd_s8x1_or_safe
//	#define _simd_s8x1_or_safe(X,Y) (X | Y)
//	#define _simd_s8x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_s8x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_or_enabled() true
//#endif
//
//#define _simd_s8x2_or_safe(X,Y)_simd_s8x2_combine_safe(\
//	_simd_s8x1_or_safe(_simd_s8x2_splitlo_safe(X), _simd_ s8x2_splitlo_safe(Y)),\
//	_simd_s8x1_or_safe(_simd_s8x2_splithi_safe(X), _simd_ s8x2_splithi_safe(Y)))
//#ifdef _simd_s8x2_or_
//	#define _simd_s8x2_or(X,Y) _simd_s8x2_or_(X, Y)
//	#define _simd_s8x2_or_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_or_instruction_set>()
//#elif defined(_simd_s8x4_or_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_or(const register _simd_s8x2 x, const register _simd_s8x2 y) {
//		union SIMDUnion { _simd_s8x2 v1; _simd_s8x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x4_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x2_or_enable() _simd_s8x4_or_enable()
//#elif defined(_simd_s8x8_or_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_or(const register _simd_s8x2 x, const register _simd_s8x2 y) {
//		union SIMDUnion { _simd_s8x2 v1; _simd_s8x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x8_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x2_or_enable() _simd_s8x8_or_enable()
//#elif defined(_simd_s8x16_or_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_or(const register _simd_s8x2 x, const register _simd_s8x2 y) {
//		union SIMDUnion { _simd_s8x2 v1; _simd_s8x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x16_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x2_or_enable() _simd_s8x16_or_enable()
//#elif defined(_simd_s8x32_or_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_or(const register _simd_s8x2 x, const register _simd_s8x2 y) {
//		union SIMDUnion { _simd_s8x2 v1; _simd_s8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x2_or_enable() _simd_s8x32_or_enable()
//#elif defined(_simd_s8x64_or_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_or(const register _simd_s8x2 x, const register _simd_s8x2 y) {
//		union SIMDUnion { _simd_s8x2 v1; _simd_s8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x2_or_enable() _simd_s8x64_or_enable()
//#else
//	#define _simd_s8x2_or(X,Y) _simd_s8x2_combine(\
//		_simd_s8x1_or(_simd_s8x2_splitlo(X), _simd_s8x2_splitlo(Y)),\
//		_simd_s8x1_or(_simd_s8x2_splithi(X), _simd_s8x2_splithi(Y)))
//	#define _simd_s8x2_or_enable() (_simd_s8x1_or_enable() && _simd_s8x2_combine_enable() && _simd_s8x2_splitlo_enable()  && _simd_s8x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x2_or_) && ! defined(_simd_s8x2_or_scalar_)
//	#define _simd_s8x2_or_scalar_(X,Y) _simd_s8x2_or_(X,_simd_s8x2_fill_scalar_(Y))
//	#define _simd_s8x2_or_scalar_instruction_set _simd_s8x2_or_instruction_set
//#endif
//#ifdef _simd_s8x2_or_scalar_
//	#define _simd_s8x2_or_scalar(X,Y) _simd_s8x2_or_scalar_(X,Y)
//	#define _simd_s8x2_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_or_scalar_instruction_set>()
//#else
//	#define _simd_s8x2_or_scalar(X,Y) _simd_s8x2_or_safe(X,_simd_s8x2_fill_scalar_safe(Y))
//	#define _simd_s8x2_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_s8x1_or_safe
//	#define _simd_s8x1_or_safe(X,Y) (X | Y)
//	#define _simd_s8x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_s8x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_or_enabled() true
//#endif
//
//#define _simd_s8x4_or_safe(X,Y)_simd_s8x4_combine_safe(\
//	_simd_s8x2_or_safe(_simd_s8x4_splitlo_safe(X), _simd_ s8x4_splitlo_safe(Y)),\
//	_simd_s8x2_or_safe(_simd_s8x4_splithi_safe(X), _simd_ s8x4_splithi_safe(Y)))
//#ifdef _simd_s8x4_or_
//	#define _simd_s8x4_or(X,Y) _simd_s8x4_or_(X, Y)
//	#define _simd_s8x4_or_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_or_instruction_set>()
//#elif defined(_simd_s8x8_or_)
//	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_or(const register _simd_s8x4 x, const register _simd_s8x4 y) {
//		union SIMDUnion { _simd_s8x4 v1; _simd_s8x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x8_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x4_or_enable() _simd_s8x8_or_enable()
//#elif defined(_simd_s8x16_or_)
//	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_or(const register _simd_s8x4 x, const register _simd_s8x4 y) {
//		union SIMDUnion { _simd_s8x4 v1; _simd_s8x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x16_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x4_or_enable() _simd_s8x16_or_enable()
//#elif defined(_simd_s8x32_or_)
//	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_or(const register _simd_s8x4 x, const register _simd_s8x4 y) {
//		union SIMDUnion { _simd_s8x4 v1; _simd_s8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x4_or_enable() _simd_s8x32_or_enable()
//#elif defined(_simd_s8x64_or_)
//	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_or(const register _simd_s8x4 x, const register _simd_s8x4 y) {
//		union SIMDUnion { _simd_s8x4 v1; _simd_s8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x4_or_enable() _simd_s8x64_or_enable()
//#else
//	#define _simd_s8x4_or(X,Y) _simd_s8x4_combine(\
//		_simd_s8x2_or(_simd_s8x4_splitlo(X), _simd_s8x4_splitlo(Y)),\
//		_simd_s8x2_or(_simd_s8x4_splithi(X), _simd_s8x4_splithi(Y)))
//	#define _simd_s8x4_or_enable() (_simd_s8x2_or_enable() && _simd_s8x4_combine_enable() && _simd_s8x4_splitlo_enable()  && _simd_s8x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x4_or_) && ! defined(_simd_s8x4_or_scalar_)
//	#define _simd_s8x4_or_scalar_(X,Y) _simd_s8x4_or_(X,_simd_s8x4_fill_scalar_(Y))
//	#define _simd_s8x4_or_scalar_instruction_set _simd_s8x4_or_instruction_set
//#endif
//#ifdef _simd_s8x4_or_scalar_
//	#define _simd_s8x4_or_scalar(X,Y) _simd_s8x4_or_scalar_(X,Y)
//	#define _simd_s8x4_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_or_scalar_instruction_set>()
//#else
//	#define _simd_s8x4_or_scalar(X,Y) _simd_s8x4_or_safe(X,_simd_s8x4_fill_scalar_safe(Y))
//	#define _simd_s8x4_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_s8x1_or_safe
//	#define _simd_s8x1_or_safe(X,Y) (X | Y)
//	#define _simd_s8x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_s8x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_or_enabled() true
//#endif
//
//#define _simd_s8x8_or_safe(X,Y)_simd_s8x8_combine_safe(\
//	_simd_s8x4_or_safe(_simd_s8x8_splitlo_safe(X), _simd_ s8x8_splitlo_safe(Y)),\
//	_simd_s8x4_or_safe(_simd_s8x8_splithi_safe(X), _simd_ s8x8_splithi_safe(Y)))
//#ifdef _simd_s8x8_or_
//	#define _simd_s8x8_or(X,Y) _simd_s8x8_or_(X, Y)
//	#define _simd_s8x8_or_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_or_instruction_set>()
//#elif defined(_simd_s8x16_or_)
//	static ANVIL_STRONG_INLINE _simd_s8x8 ANVIL_SIMD_CALL _simd_s8x8_or(const register _simd_s8x8 x, const register _simd_s8x8 y) {
//		union SIMDUnion { _simd_s8x8 v1; _simd_s8x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x16_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x8_or_enable() _simd_s8x16_or_enable()
//#elif defined(_simd_s8x32_or_)
//	static ANVIL_STRONG_INLINE _simd_s8x8 ANVIL_SIMD_CALL _simd_s8x8_or(const register _simd_s8x8 x, const register _simd_s8x8 y) {
//		union SIMDUnion { _simd_s8x8 v1; _simd_s8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x8_or_enable() _simd_s8x32_or_enable()
//#elif defined(_simd_s8x64_or_)
//	static ANVIL_STRONG_INLINE _simd_s8x8 ANVIL_SIMD_CALL _simd_s8x8_or(const register _simd_s8x8 x, const register _simd_s8x8 y) {
//		union SIMDUnion { _simd_s8x8 v1; _simd_s8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x8_or_enable() _simd_s8x64_or_enable()
//#else
//	#define _simd_s8x8_or(X,Y) _simd_s8x8_combine(\
//		_simd_s8x4_or(_simd_s8x8_splitlo(X), _simd_s8x8_splitlo(Y)),\
//		_simd_s8x4_or(_simd_s8x8_splithi(X), _simd_s8x8_splithi(Y)))
//	#define _simd_s8x8_or_enable() (_simd_s8x4_or_enable() && _simd_s8x8_combine_enable() && _simd_s8x8_splitlo_enable()  && _simd_s8x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x8_or_) && ! defined(_simd_s8x8_or_scalar_)
//	#define _simd_s8x8_or_scalar_(X,Y) _simd_s8x8_or_(X,_simd_s8x8_fill_scalar_(Y))
//	#define _simd_s8x8_or_scalar_instruction_set _simd_s8x8_or_instruction_set
//#endif
//#ifdef _simd_s8x8_or_scalar_
//	#define _simd_s8x8_or_scalar(X,Y) _simd_s8x8_or_scalar_(X,Y)
//	#define _simd_s8x8_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_or_scalar_instruction_set>()
//#else
//	#define _simd_s8x8_or_scalar(X,Y) _simd_s8x8_or_safe(X,_simd_s8x8_fill_scalar_safe(Y))
//	#define _simd_s8x8_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_s8x1_or_safe
//	#define _simd_s8x1_or_safe(X,Y) (X | Y)
//	#define _simd_s8x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_s8x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_or_enabled() true
//#endif
//
//#define _simd_s8x16_or_safe(X,Y)_simd_s8x16_combine_safe(\
//	_simd_s8x8_or_safe(_simd_s8x16_splitlo_safe(X), _simd_ s8x16_splitlo_safe(Y)),\
//	_simd_s8x8_or_safe(_simd_s8x16_splithi_safe(X), _simd_ s8x16_splithi_safe(Y)))
//#ifdef _simd_s8x16_or_
//	#define _simd_s8x16_or(X,Y) _simd_s8x16_or_(X, Y)
//	#define _simd_s8x16_or_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_or_instruction_set>()
//#elif defined(_simd_s8x32_or_)
//	static ANVIL_STRONG_INLINE _simd_s8x16 ANVIL_SIMD_CALL _simd_s8x16_or(const register _simd_s8x16 x, const register _simd_s8x16 y) {
//		union SIMDUnion { _simd_s8x16 v1; _simd_s8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x16_or_enable() _simd_s8x32_or_enable()
//#elif defined(_simd_s8x64_or_)
//	static ANVIL_STRONG_INLINE _simd_s8x16 ANVIL_SIMD_CALL _simd_s8x16_or(const register _simd_s8x16 x, const register _simd_s8x16 y) {
//		union SIMDUnion { _simd_s8x16 v1; _simd_s8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x16_or_enable() _simd_s8x64_or_enable()
//#else
//	#define _simd_s8x16_or(X,Y) _simd_s8x16_combine(\
//		_simd_s8x8_or(_simd_s8x16_splitlo(X), _simd_s8x16_splitlo(Y)),\
//		_simd_s8x8_or(_simd_s8x16_splithi(X), _simd_s8x16_splithi(Y)))
//	#define _simd_s8x16_or_enable() (_simd_s8x8_or_enable() && _simd_s8x16_combine_enable() && _simd_s8x16_splitlo_enable()  && _simd_s8x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x16_or_) && ! defined(_simd_s8x16_or_scalar_)
//	#define _simd_s8x16_or_scalar_(X,Y) _simd_s8x16_or_(X,_simd_s8x16_fill_scalar_(Y))
//	#define _simd_s8x16_or_scalar_instruction_set _simd_s8x16_or_instruction_set
//#endif
//#ifdef _simd_s8x16_or_scalar_
//	#define _simd_s8x16_or_scalar(X,Y) _simd_s8x16_or_scalar_(X,Y)
//	#define _simd_s8x16_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_or_scalar_instruction_set>()
//#else
//	#define _simd_s8x16_or_scalar(X,Y) _simd_s8x16_or_safe(X,_simd_s8x16_fill_scalar_safe(Y))
//	#define _simd_s8x16_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_s8x1_or_safe
//	#define _simd_s8x1_or_safe(X,Y) (X | Y)
//	#define _simd_s8x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_s8x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_or_enabled() true
//#endif
//
//#define _simd_s8x32_or_safe(X,Y)_simd_s8x32_combine_safe(\
//	_simd_s8x16_or_safe(_simd_s8x32_splitlo_safe(X), _simd_ s8x32_splitlo_safe(Y)),\
//	_simd_s8x16_or_safe(_simd_s8x32_splithi_safe(X), _simd_ s8x32_splithi_safe(Y)))
//#ifdef _simd_s8x32_or_
//	#define _simd_s8x32_or(X,Y) _simd_s8x32_or_(X, Y)
//	#define _simd_s8x32_or_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_or_instruction_set>()
//#elif defined(_simd_s8x64_or_)
//	static ANVIL_STRONG_INLINE _simd_s8x32 ANVIL_SIMD_CALL _simd_s8x32_or(const register _simd_s8x32 x, const register _simd_s8x32 y) {
//		union SIMDUnion { _simd_s8x32 v1; _simd_s8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x32_or_enable() _simd_s8x64_or_enable()
//#else
//	#define _simd_s8x32_or(X,Y) _simd_s8x32_combine(\
//		_simd_s8x16_or(_simd_s8x32_splitlo(X), _simd_s8x32_splitlo(Y)),\
//		_simd_s8x16_or(_simd_s8x32_splithi(X), _simd_s8x32_splithi(Y)))
//	#define _simd_s8x32_or_enable() (_simd_s8x16_or_enable() && _simd_s8x32_combine_enable() && _simd_s8x32_splitlo_enable()  && _simd_s8x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x32_or_) && ! defined(_simd_s8x32_or_scalar_)
//	#define _simd_s8x32_or_scalar_(X,Y) _simd_s8x32_or_(X,_simd_s8x32_fill_scalar_(Y))
//	#define _simd_s8x32_or_scalar_instruction_set _simd_s8x32_or_instruction_set
//#endif
//#ifdef _simd_s8x32_or_scalar_
//	#define _simd_s8x32_or_scalar(X,Y) _simd_s8x32_or_scalar_(X,Y)
//	#define _simd_s8x32_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_or_scalar_instruction_set>()
//#else
//	#define _simd_s8x32_or_scalar(X,Y) _simd_s8x32_or_safe(X,_simd_s8x32_fill_scalar_safe(Y))
//	#define _simd_s8x32_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_s8x1_or_safe
//	#define _simd_s8x1_or_safe(X,Y) (X | Y)
//	#define _simd_s8x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_s8x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_or_enabled() true
//#endif
//
//#define _simd_s8x64_or_safe(X,Y)_simd_s8x64_combine_safe(\
//	_simd_s8x32_or_safe(_simd_s8x64_splitlo_safe(X), _simd_ s8x64_splitlo_safe(Y)),\
//	_simd_s8x32_or_safe(_simd_s8x64_splithi_safe(X), _simd_ s8x64_splithi_safe(Y)))
//#ifdef _simd_s8x64_or_
//	#define _simd_s8x64_or(X,Y) _simd_s8x64_or_(X, Y)
//	#define _simd_s8x64_or_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_or_instruction_set>()
//#else
//	#define _simd_s8x64_or(X,Y) _simd_s8x64_combine(\
//		_simd_s8x32_or(_simd_s8x64_splitlo(X), _simd_s8x64_splitlo(Y)),\
//		_simd_s8x32_or(_simd_s8x64_splithi(X), _simd_s8x64_splithi(Y)))
//	#define _simd_s8x64_or_enable() (_simd_s8x32_or_enable() && _simd_s8x64_combine_enable() && _simd_s8x64_splitlo_enable()  && _simd_s8x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x64_or_) && ! defined(_simd_s8x64_or_scalar_)
//	#define _simd_s8x64_or_scalar_(X,Y) _simd_s8x64_or_(X,_simd_s8x64_fill_scalar_(Y))
//	#define _simd_s8x64_or_scalar_instruction_set _simd_s8x64_or_instruction_set
//#endif
//#ifdef _simd_s8x64_or_scalar_
//	#define _simd_s8x64_or_scalar(X,Y) _simd_s8x64_or_scalar_(X,Y)
//	#define _simd_s8x64_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_or_scalar_instruction_set>()
//#else
//	#define _simd_s8x64_or_scalar(X,Y) _simd_s8x64_or_safe(X,_simd_s8x64_fill_scalar_safe(Y))
//	#define _simd_s8x64_or_scalar_enabled() true
//#endif
//
//// -- u8 --
//
//#ifndef _simd_u8x1_or_safe
//	#define _simd_u8x1_or_safe(X,Y) (X | Y)
//	#define _simd_u8x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_u8x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_or_enabled() true
//#endif
//
//#define _simd_u8x2_or_safe(X,Y)_simd_u8x2_combine_safe(\
//	_simd_u8x1_or_safe(_simd_u8x2_splitlo_safe(X), _simd_ u8x2_splitlo_safe(Y)),\
//	_simd_u8x1_or_safe(_simd_u8x2_splithi_safe(X), _simd_ u8x2_splithi_safe(Y)))
//#ifdef _simd_u8x2_or_
//	#define _simd_u8x2_or(X,Y) _simd_u8x2_or_(X, Y)
//	#define _simd_u8x2_or_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_or_instruction_set>()
//#elif defined(_simd_u8x4_or_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_or(const register _simd_u8x2 x, const register _simd_u8x2 y) {
//		union SIMDUnion { _simd_u8x2 v1; _simd_u8x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x4_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x2_or_enable() _simd_u8x4_or_enable()
//#elif defined(_simd_u8x8_or_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_or(const register _simd_u8x2 x, const register _simd_u8x2 y) {
//		union SIMDUnion { _simd_u8x2 v1; _simd_u8x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x8_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x2_or_enable() _simd_u8x8_or_enable()
//#elif defined(_simd_u8x16_or_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_or(const register _simd_u8x2 x, const register _simd_u8x2 y) {
//		union SIMDUnion { _simd_u8x2 v1; _simd_u8x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x16_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x2_or_enable() _simd_u8x16_or_enable()
//#elif defined(_simd_u8x32_or_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_or(const register _simd_u8x2 x, const register _simd_u8x2 y) {
//		union SIMDUnion { _simd_u8x2 v1; _simd_u8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x2_or_enable() _simd_u8x32_or_enable()
//#elif defined(_simd_u8x64_or_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_or(const register _simd_u8x2 x, const register _simd_u8x2 y) {
//		union SIMDUnion { _simd_u8x2 v1; _simd_u8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x2_or_enable() _simd_u8x64_or_enable()
//#else
//	#define _simd_u8x2_or(X,Y) _simd_u8x2_combine(\
//		_simd_u8x1_or(_simd_u8x2_splitlo(X), _simd_u8x2_splitlo(Y)),\
//		_simd_u8x1_or(_simd_u8x2_splithi(X), _simd_u8x2_splithi(Y)))
//	#define _simd_u8x2_or_enable() (_simd_u8x1_or_enable() && _simd_u8x2_combine_enable() && _simd_u8x2_splitlo_enable()  && _simd_u8x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x2_or_) && ! defined(_simd_u8x2_or_scalar_)
//	#define _simd_u8x2_or_scalar_(X,Y) _simd_u8x2_or_(X,_simd_u8x2_fill_scalar_(Y))
//	#define _simd_u8x2_or_scalar_instruction_set _simd_u8x2_or_instruction_set
//#endif
//#ifdef _simd_u8x2_or_scalar_
//	#define _simd_u8x2_or_scalar(X,Y) _simd_u8x2_or_scalar_(X,Y)
//	#define _simd_u8x2_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_or_scalar_instruction_set>()
//#else
//	#define _simd_u8x2_or_scalar(X,Y) _simd_u8x2_or_safe(X,_simd_u8x2_fill_scalar_safe(Y))
//	#define _simd_u8x2_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_u8x1_or_safe
//	#define _simd_u8x1_or_safe(X,Y) (X | Y)
//	#define _simd_u8x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_u8x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_or_enabled() true
//#endif
//
//#define _simd_u8x4_or_safe(X,Y)_simd_u8x4_combine_safe(\
//	_simd_u8x2_or_safe(_simd_u8x4_splitlo_safe(X), _simd_ u8x4_splitlo_safe(Y)),\
//	_simd_u8x2_or_safe(_simd_u8x4_splithi_safe(X), _simd_ u8x4_splithi_safe(Y)))
//#ifdef _simd_u8x4_or_
//	#define _simd_u8x4_or(X,Y) _simd_u8x4_or_(X, Y)
//	#define _simd_u8x4_or_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_or_instruction_set>()
//#elif defined(_simd_u8x8_or_)
//	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_or(const register _simd_u8x4 x, const register _simd_u8x4 y) {
//		union SIMDUnion { _simd_u8x4 v1; _simd_u8x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x8_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x4_or_enable() _simd_u8x8_or_enable()
//#elif defined(_simd_u8x16_or_)
//	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_or(const register _simd_u8x4 x, const register _simd_u8x4 y) {
//		union SIMDUnion { _simd_u8x4 v1; _simd_u8x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x16_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x4_or_enable() _simd_u8x16_or_enable()
//#elif defined(_simd_u8x32_or_)
//	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_or(const register _simd_u8x4 x, const register _simd_u8x4 y) {
//		union SIMDUnion { _simd_u8x4 v1; _simd_u8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x4_or_enable() _simd_u8x32_or_enable()
//#elif defined(_simd_u8x64_or_)
//	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_or(const register _simd_u8x4 x, const register _simd_u8x4 y) {
//		union SIMDUnion { _simd_u8x4 v1; _simd_u8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x4_or_enable() _simd_u8x64_or_enable()
//#else
//	#define _simd_u8x4_or(X,Y) _simd_u8x4_combine(\
//		_simd_u8x2_or(_simd_u8x4_splitlo(X), _simd_u8x4_splitlo(Y)),\
//		_simd_u8x2_or(_simd_u8x4_splithi(X), _simd_u8x4_splithi(Y)))
//	#define _simd_u8x4_or_enable() (_simd_u8x2_or_enable() && _simd_u8x4_combine_enable() && _simd_u8x4_splitlo_enable()  && _simd_u8x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x4_or_) && ! defined(_simd_u8x4_or_scalar_)
//	#define _simd_u8x4_or_scalar_(X,Y) _simd_u8x4_or_(X,_simd_u8x4_fill_scalar_(Y))
//	#define _simd_u8x4_or_scalar_instruction_set _simd_u8x4_or_instruction_set
//#endif
//#ifdef _simd_u8x4_or_scalar_
//	#define _simd_u8x4_or_scalar(X,Y) _simd_u8x4_or_scalar_(X,Y)
//	#define _simd_u8x4_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_or_scalar_instruction_set>()
//#else
//	#define _simd_u8x4_or_scalar(X,Y) _simd_u8x4_or_safe(X,_simd_u8x4_fill_scalar_safe(Y))
//	#define _simd_u8x4_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_u8x1_or_safe
//	#define _simd_u8x1_or_safe(X,Y) (X | Y)
//	#define _simd_u8x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_u8x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_or_enabled() true
//#endif
//
//#define _simd_u8x8_or_safe(X,Y)_simd_u8x8_combine_safe(\
//	_simd_u8x4_or_safe(_simd_u8x8_splitlo_safe(X), _simd_ u8x8_splitlo_safe(Y)),\
//	_simd_u8x4_or_safe(_simd_u8x8_splithi_safe(X), _simd_ u8x8_splithi_safe(Y)))
//#ifdef _simd_u8x8_or_
//	#define _simd_u8x8_or(X,Y) _simd_u8x8_or_(X, Y)
//	#define _simd_u8x8_or_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_or_instruction_set>()
//#elif defined(_simd_u8x16_or_)
//	static ANVIL_STRONG_INLINE _simd_u8x8 ANVIL_SIMD_CALL _simd_u8x8_or(const register _simd_u8x8 x, const register _simd_u8x8 y) {
//		union SIMDUnion { _simd_u8x8 v1; _simd_u8x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x16_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x8_or_enable() _simd_u8x16_or_enable()
//#elif defined(_simd_u8x32_or_)
//	static ANVIL_STRONG_INLINE _simd_u8x8 ANVIL_SIMD_CALL _simd_u8x8_or(const register _simd_u8x8 x, const register _simd_u8x8 y) {
//		union SIMDUnion { _simd_u8x8 v1; _simd_u8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x8_or_enable() _simd_u8x32_or_enable()
//#elif defined(_simd_u8x64_or_)
//	static ANVIL_STRONG_INLINE _simd_u8x8 ANVIL_SIMD_CALL _simd_u8x8_or(const register _simd_u8x8 x, const register _simd_u8x8 y) {
//		union SIMDUnion { _simd_u8x8 v1; _simd_u8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x8_or_enable() _simd_u8x64_or_enable()
//#else
//	#define _simd_u8x8_or(X,Y) _simd_u8x8_combine(\
//		_simd_u8x4_or(_simd_u8x8_splitlo(X), _simd_u8x8_splitlo(Y)),\
//		_simd_u8x4_or(_simd_u8x8_splithi(X), _simd_u8x8_splithi(Y)))
//	#define _simd_u8x8_or_enable() (_simd_u8x4_or_enable() && _simd_u8x8_combine_enable() && _simd_u8x8_splitlo_enable()  && _simd_u8x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x8_or_) && ! defined(_simd_u8x8_or_scalar_)
//	#define _simd_u8x8_or_scalar_(X,Y) _simd_u8x8_or_(X,_simd_u8x8_fill_scalar_(Y))
//	#define _simd_u8x8_or_scalar_instruction_set _simd_u8x8_or_instruction_set
//#endif
//#ifdef _simd_u8x8_or_scalar_
//	#define _simd_u8x8_or_scalar(X,Y) _simd_u8x8_or_scalar_(X,Y)
//	#define _simd_u8x8_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_or_scalar_instruction_set>()
//#else
//	#define _simd_u8x8_or_scalar(X,Y) _simd_u8x8_or_safe(X,_simd_u8x8_fill_scalar_safe(Y))
//	#define _simd_u8x8_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_u8x1_or_safe
//	#define _simd_u8x1_or_safe(X,Y) (X | Y)
//	#define _simd_u8x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_u8x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_or_enabled() true
//#endif
//
//#define _simd_u8x16_or_safe(X,Y)_simd_u8x16_combine_safe(\
//	_simd_u8x8_or_safe(_simd_u8x16_splitlo_safe(X), _simd_ u8x16_splitlo_safe(Y)),\
//	_simd_u8x8_or_safe(_simd_u8x16_splithi_safe(X), _simd_ u8x16_splithi_safe(Y)))
//#ifdef _simd_u8x16_or_
//	#define _simd_u8x16_or(X,Y) _simd_u8x16_or_(X, Y)
//	#define _simd_u8x16_or_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_or_instruction_set>()
//#elif defined(_simd_u8x32_or_)
//	static ANVIL_STRONG_INLINE _simd_u8x16 ANVIL_SIMD_CALL _simd_u8x16_or(const register _simd_u8x16 x, const register _simd_u8x16 y) {
//		union SIMDUnion { _simd_u8x16 v1; _simd_u8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x32_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x16_or_enable() _simd_u8x32_or_enable()
//#elif defined(_simd_u8x64_or_)
//	static ANVIL_STRONG_INLINE _simd_u8x16 ANVIL_SIMD_CALL _simd_u8x16_or(const register _simd_u8x16 x, const register _simd_u8x16 y) {
//		union SIMDUnion { _simd_u8x16 v1; _simd_u8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x16_or_enable() _simd_u8x64_or_enable()
//#else
//	#define _simd_u8x16_or(X,Y) _simd_u8x16_combine(\
//		_simd_u8x8_or(_simd_u8x16_splitlo(X), _simd_u8x16_splitlo(Y)),\
//		_simd_u8x8_or(_simd_u8x16_splithi(X), _simd_u8x16_splithi(Y)))
//	#define _simd_u8x16_or_enable() (_simd_u8x8_or_enable() && _simd_u8x16_combine_enable() && _simd_u8x16_splitlo_enable()  && _simd_u8x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x16_or_) && ! defined(_simd_u8x16_or_scalar_)
//	#define _simd_u8x16_or_scalar_(X,Y) _simd_u8x16_or_(X,_simd_u8x16_fill_scalar_(Y))
//	#define _simd_u8x16_or_scalar_instruction_set _simd_u8x16_or_instruction_set
//#endif
//#ifdef _simd_u8x16_or_scalar_
//	#define _simd_u8x16_or_scalar(X,Y) _simd_u8x16_or_scalar_(X,Y)
//	#define _simd_u8x16_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_or_scalar_instruction_set>()
//#else
//	#define _simd_u8x16_or_scalar(X,Y) _simd_u8x16_or_safe(X,_simd_u8x16_fill_scalar_safe(Y))
//	#define _simd_u8x16_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_u8x1_or_safe
//	#define _simd_u8x1_or_safe(X,Y) (X | Y)
//	#define _simd_u8x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_u8x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_or_enabled() true
//#endif
//
//#define _simd_u8x32_or_safe(X,Y)_simd_u8x32_combine_safe(\
//	_simd_u8x16_or_safe(_simd_u8x32_splitlo_safe(X), _simd_ u8x32_splitlo_safe(Y)),\
//	_simd_u8x16_or_safe(_simd_u8x32_splithi_safe(X), _simd_ u8x32_splithi_safe(Y)))
//#ifdef _simd_u8x32_or_
//	#define _simd_u8x32_or(X,Y) _simd_u8x32_or_(X, Y)
//	#define _simd_u8x32_or_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_or_instruction_set>()
//#elif defined(_simd_u8x64_or_)
//	static ANVIL_STRONG_INLINE _simd_u8x32 ANVIL_SIMD_CALL _simd_u8x32_or(const register _simd_u8x32 x, const register _simd_u8x32 y) {
//		union SIMDUnion { _simd_u8x32 v1; _simd_u8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x64_or_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x32_or_enable() _simd_u8x64_or_enable()
//#else
//	#define _simd_u8x32_or(X,Y) _simd_u8x32_combine(\
//		_simd_u8x16_or(_simd_u8x32_splitlo(X), _simd_u8x32_splitlo(Y)),\
//		_simd_u8x16_or(_simd_u8x32_splithi(X), _simd_u8x32_splithi(Y)))
//	#define _simd_u8x32_or_enable() (_simd_u8x16_or_enable() && _simd_u8x32_combine_enable() && _simd_u8x32_splitlo_enable()  && _simd_u8x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x32_or_) && ! defined(_simd_u8x32_or_scalar_)
//	#define _simd_u8x32_or_scalar_(X,Y) _simd_u8x32_or_(X,_simd_u8x32_fill_scalar_(Y))
//	#define _simd_u8x32_or_scalar_instruction_set _simd_u8x32_or_instruction_set
//#endif
//#ifdef _simd_u8x32_or_scalar_
//	#define _simd_u8x32_or_scalar(X,Y) _simd_u8x32_or_scalar_(X,Y)
//	#define _simd_u8x32_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_or_scalar_instruction_set>()
//#else
//	#define _simd_u8x32_or_scalar(X,Y) _simd_u8x32_or_safe(X,_simd_u8x32_fill_scalar_safe(Y))
//	#define _simd_u8x32_or_scalar_enabled() true
//#endif
//
//#ifndef _simd_u8x1_or_safe
//	#define _simd_u8x1_or_safe(X,Y) (X | Y)
//	#define _simd_u8x1_or_(X,Y) x1_or_safe(X,Y)
//	#define _simd_u8x1_or_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_or_enabled() true
//#endif
//
//#define _simd_u8x64_or_safe(X,Y)_simd_u8x64_combine_safe(\
//	_simd_u8x32_or_safe(_simd_u8x64_splitlo_safe(X), _simd_ u8x64_splitlo_safe(Y)),\
//	_simd_u8x32_or_safe(_simd_u8x64_splithi_safe(X), _simd_ u8x64_splithi_safe(Y)))
//#ifdef _simd_u8x64_or_
//	#define _simd_u8x64_or(X,Y) _simd_u8x64_or_(X, Y)
//	#define _simd_u8x64_or_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_or_instruction_set>()
//#else
//	#define _simd_u8x64_or(X,Y) _simd_u8x64_combine(\
//		_simd_u8x32_or(_simd_u8x64_splitlo(X), _simd_u8x64_splitlo(Y)),\
//		_simd_u8x32_or(_simd_u8x64_splithi(X), _simd_u8x64_splithi(Y)))
//	#define _simd_u8x64_or_enable() (_simd_u8x32_or_enable() && _simd_u8x64_combine_enable() && _simd_u8x64_splitlo_enable()  && _simd_u8x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x64_or_) && ! defined(_simd_u8x64_or_scalar_)
//	#define _simd_u8x64_or_scalar_(X,Y) _simd_u8x64_or_(X,_simd_u8x64_fill_scalar_(Y))
//	#define _simd_u8x64_or_scalar_instruction_set _simd_u8x64_or_instruction_set
//#endif
//#ifdef _simd_u8x64_or_scalar_
//	#define _simd_u8x64_or_scalar(X,Y) _simd_u8x64_or_scalar_(X,Y)
//	#define _simd_u8x64_or_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_or_scalar_instruction_set>()
//#else
//	#define _simd_u8x64_or_scalar(X,Y) _simd_u8x64_or_safe(X,_simd_u8x64_fill_scalar_safe(Y))
//	#define _simd_u8x64_or_scalar_enabled() true
//#endif
//
