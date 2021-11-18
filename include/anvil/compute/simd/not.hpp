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

#include "anvil/core/CpuRuntime.hpp"
#include "anvil/core/Keywords.hpp"
#include "anvil/compute/Vector.hpp"

namespace anvil { namespace detail {
	template<class T>
	struct VectorNotNative{
		enum { optimised = 0u };
		enum : uint64_t { recommended_instruction_set = 0u };

		static ANVIL_STRONG_INLINE void Execute(T& a) {
			a = ~a;
		}
	};

	template<>
	struct VectorNotNative<float32_t> {
		typedef float32_t T;
		typedef UnsignedType<T> UT;

		enum { optimised = 0u };
		enum : uint64_t { recommended_instruction_set = 0u };

		static ANVIL_STRONG_INLINE void Execute(T& a) {
			union { T t; UT ut; };
			t = a;
			ut = ~ut;
			a = t;
		}
	};

	template<>
	struct VectorNotNative<float64_t> {
		typedef float64_t T;
		typedef UnsignedType<T> UT;

		enum { optimised = 0u };
		enum : uint64_t { recommended_instruction_set = 0u };

		static ANVIL_STRONG_INLINE void Execute(T& a) {
			union { T t; UT ut; };
			t = a;
			ut = ~ut;
			a = t;
		}
	};

	template<class T, size_t S>
	struct VectorNotNative<detail::BasicVector<T,S>> {
		typedef detail::BasicVector<T, S> type;
		enum { optimised = 0u };
		enum : uint64_t { recommended_instruction_set = 0u };

		static inline void Execute(type& a) {
			for (size_t i = 0u; i < S; ++i) VectorNotNative<T>::Execute(a.data[i]);
		}
	};

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64

	template<>
	struct VectorNotNative<__m128> {
		typedef __m128 T;

		enum { optimised = 1u };
		enum : uint64_t { recommended_instruction_set = ASM_SSE };

		static ANVIL_STRONG_INLINE void Execute(T& a) {
			a = _mm_xor_ps(a, _mm_cmpeq_ps(a, a));
		}
	};

	template<>
	struct VectorNotNative<__m128d> {
		typedef __m128d T;

		enum { optimised = 1u };
		enum : uint64_t { recommended_instruction_set = ASM_SSE2 };

		static ANVIL_STRONG_INLINE void Execute(T& a) {
			a = _mm_xor_pd(a, _mm_cmpeq_pd(a, a));
		}
	};

	template<>
	struct VectorNotNative<__m128i> {
		typedef __m128i T;

		enum { optimised = 1u };
		enum : uint64_t { recommended_instruction_set = ASM_SSE2 };

		static ANVIL_STRONG_INLINE void Execute(T& a) {
			a = _mm_xor_si128(a, _mm_cmpeq_epi32(a, a));
		}
	};

	template<>
	struct VectorNotNative<__m256> {
		typedef __m256 T;

		enum { optimised = 1u };
		enum : uint64_t { recommended_instruction_set = ASM_AVX };

		static ANVIL_STRONG_INLINE void Execute(T& a) {
			a = _mm256_xor_ps(a, _mm256_cmp_ps(a, a, _CMP_EQ_OQ));
		}
	};

	template<>
	struct VectorNotNative<__m256d> {
		typedef __m256d T;

		enum { optimised = 1u };
		enum : uint64_t { recommended_instruction_set = ASM_AVX };

		static ANVIL_STRONG_INLINE void Execute(T& a) {
			a = _mm256_xor_pd(a, _mm256_cmp_pd(a, a, _CMP_EQ_OQ));
		}
	};

	template<>
	struct VectorNotNative<__m256i> {
		typedef __m256i T;

		enum { optimised = 1u };
		enum : uint64_t { recommended_instruction_set = ASM_AVX2 };

		static ANVIL_STRONG_INLINE void Execute(T& a) {
			a = _mm256_xor_si256(a, _mm256_cmpeq_epi32(a, a));
		}
	};

	template<>
	struct VectorNotNative<__m512> {
		typedef __m512 T;

		enum { optimised = 1u };
		enum : uint64_t { recommended_instruction_set = ASM_AVX512F };

		static ANVIL_STRONG_INLINE void Execute(T& a) {
			a = _mm512_xor_ps(a, _mm512_castsi512_ps(_mm512_set1_epi32(-1)));
		}
	};

	template<>
	struct VectorNotNative<__m512d> {
		typedef __m512d T;

		enum { optimised = 1u };
		enum : uint64_t { recommended_instruction_set = ASM_AVX512F };

		static ANVIL_STRONG_INLINE void Execute(T& a) {
			a = _mm512_xor_pd(a, _mm512_castsi512_pd(_mm512_set1_epi32(-1)));
		}
	};

	template<>
	struct VectorNotNative<__m512i> {
		typedef __m512i T;

		enum { optimised = 1u };
		enum : uint64_t { recommended_instruction_set = ASM_AVX512F };

		static ANVIL_STRONG_INLINE void Execute(T& a) {
			a = _mm512_xor_si512(a, _mm512_set1_epi32(-1));
		}
	};

#endif

	template<class T>
	struct VectorNot {
		typedef T type;
		typedef VectorNotNative<type> Implementation;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a) throw() {
			Implementation::Execute(a);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type ExecuteRuntimeMask(type a, const type& src, const uint64_t mask) throw() {
			return anvil::VectorBlendRuntimeMask<instruction_set>(Execute<instruction_set>(a), src, mask);
		}

		template<uint64_t mask, uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type ExecuteCompiletimeMask(type a, const type& src) throw() {
			return anvil::VectorBlendRuntimeMask<mask, instruction_set>(Execute<instruction_set>(a), src);
		}
	};

	

	template<class T, size_t size>
	struct VectorNot<detail::BasicVector<T, size>> {
		typedef detail::BasicVector<T, size> type;
		typedef typename type::native_t native_t;
		typedef VectorNotNative<native_t> Implementation;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a) throw() {
			if constexpr (Implementation::optimised && (instruction_set & Implementation::recommended_instruction_set) == Implementation::recommended_instruction_set) {
				Implementation::Execute(a.native);
			} else {
				a.lower_half = VectorNot<type::lower_t>::Execute<instruction_set>(a.lower_half);
				a.upper_half = VectorNot<type::upper_t>::Execute<instruction_set>(a.upper_half);
			}

			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type ExecuteRuntimeMask(type a, const type& src, const uint64_t mask) throw() {
			if constexpr (Implementation::optimised && (instruction_set & Implementation::recommended_instruction_set) == Implementation::recommended_instruction_set) {
				return anvil::VectorBlendRuntimeMask<instruction_set>(Execute<instruction_set>(a), src, mask);
			} else {
				a.lower_half = VectorNot<type::lower_t>::ExecuteRuntimeMask<instruction_set>(a.lower_half, src.lower_half, mask);
				a.upper_half = VectorNot<type::upper_t>::ExecuteRuntimeMask<instruction_set>(a.upper_half, src.upper_half, mask >> type::lower_size);
				return a;
			}
		}

		template<uint64_t mask, uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type ExecuteCompiletimeMask(type a, const type& src) throw() {
			if constexpr (Implementation::optimised && (instruction_set & Implementation::recommended_instruction_set) == Implementation::recommended_instruction_set) {
				return anvil::VectorBlendCompiletimeMask<mask, instruction_set>(Execute<instruction_set>(a), src);
			} else {
				enum : uint64_t { mask1 = mask >> type::lower_size };
				a.lower_half = VectorNot<type::lower_t>::ExecuteCompiletimeMask<mask, instruction_set>(a.lower_half, src.lower_half);
				a.upper_half = VectorNot<type::upper_t>::ExecuteCompiletimeMask<mask1, instruction_set>(a.upper_half, src.upper_half);
				return a;
			}
		}
	};

}}

namespace anvil {

	template<uint64_t instruction_set = ASM_MINIMUM, class T>
	static inline T VectorNot(const T& a) throw() {
		return detail::VectorNot<T>::Execute<instruction_set>(a);
	}

	// Run-time blend mask
	template<uint64_t instruction_set = ASM_MINIMUM, class T>
	static inline T VectorNot(const T& a, const T& src, const uint64_t mask) throw() {
		return detail::VectorNot<T>::ExecuteRuntimeMask<instruction_set>(a, src, mask);
	}

	// Compile-time blend mask
	template<uint64_t mask, uint64_t instruction_set = ASM_MINIMUM, class T>
	static inline T VectorNot(const T& a, const T& src) throw() {
		return detail::VectorNot<T>::ExecuteCompiletimeMask<mask, instruction_set>(a, src);
	}
}

//// -- f64 --
//
//#ifndef _simd_f64x1_not_safe
//	#define _simd_f64x1_not_safe(X) X
//	#define _simd_f64x1_not_(X) x1_not_safe(X)
//	#define _simd_f64x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_not_enabled() true
//#endif
//
//#define _simd_f64x2_not_safe(X)_simd_f64x2_combine_safe(\
//	_simd_f64x1_not_safe(_simd_f64x2_splitlo_safe(X)),\
//	_simd_f64x1_not_safe(_simd_f64x2_splithi_safe(X)))
//#ifdef _simd_f64x2_not_
//	#define _simd_f64x2_not(X) _simd_f64x2_not_(X)
//	#define _simd_f64x2_not_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_not_instruction_set>()
//#elif defined(_simd_f64x4_not_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_not(const register _simd_f64x2 x) {
//		union { _simd_f64x2 v1; _simd_f64x4 v2; };
//		v1 = x;
//		v2 = _simd_f64x4_not_(v2);
//		return v1;
//	}
//	#define _simd_f64x2_not_enable() _simd_f64x4_not_enable()
//#elif defined(_simd_f64x8_not_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_not(const register _simd_f64x2 x) {
//		union { _simd_f64x2 v1; _simd_f64x8 v2; };
//		v1 = x;
//		v2 = _simd_f64x8_not_(v2);
//		return v1;
//	}
//	#define _simd_f64x2_not_enable() _simd_f64x8_not_enable()
//#elif defined(_simd_f64x16_not_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_not(const register _simd_f64x2 x) {
//		union { _simd_f64x2 v1; _simd_f64x16 v2; };
//		v1 = x;
//		v2 = _simd_f64x16_not_(v2);
//		return v1;
//	}
//	#define _simd_f64x2_not_enable() _simd_f64x16_not_enable()
//#elif defined(_simd_f64x32_not_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_not(const register _simd_f64x2 x) {
//		union { _simd_f64x2 v1; _simd_f64x32 v2; };
//		v1 = x;
//		v2 = _simd_f64x32_not_(v2);
//		return v1;
//	}
//	#define _simd_f64x2_not_enable() _simd_f64x32_not_enable()
//#elif defined(_simd_f64x64_not_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_not(const register _simd_f64x2 x) {
//		union { _simd_f64x2 v1; _simd_f64x64 v2; };
//		v1 = x;
//		v2 = _simd_f64x64_not_(v2);
//		return v1;
//	}
//	#define _simd_f64x2_not_enable() _simd_f64x64_not_enable()
//#else
//	#define _simd_f64x2_not(X) _simd_f64x2_combine(\
//		_simd_f64x1_not(_simd_f64x2_splitlo(X)),\
//		_simd_f64x1_not(_simd_f64x2_splithi(X)))
//	#define _simd_f64x2_not_enable() (_simd_f64x1_not_enable() && _simd_f64x2_combine_enable() && _simd_f64x2_splitlo_enable()  && _simd_f64x2_splithi_enable())
//#endif
//
//#ifndef _simd_f64x1_not_safe
//	#define _simd_f64x1_not_safe(X) X
//	#define _simd_f64x1_not_(X) x1_not_safe(X)
//	#define _simd_f64x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_not_enabled() true
//#endif
//
//#define _simd_f64x4_not_safe(X)_simd_f64x4_combine_safe(\
//	_simd_f64x2_not_safe(_simd_f64x4_splitlo_safe(X)),\
//	_simd_f64x2_not_safe(_simd_f64x4_splithi_safe(X)))
//#ifdef _simd_f64x4_not_
//	#define _simd_f64x4_not(X) _simd_f64x4_not_(X)
//	#define _simd_f64x4_not_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_not_instruction_set>()
//#elif defined(_simd_f64x8_not_)
//	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_not(const register _simd_f64x4 x) {
//		union { _simd_f64x4 v1; _simd_f64x8 v2; };
//		v1 = x;
//		v2 = _simd_f64x8_not_(v2);
//		return v1;
//	}
//	#define _simd_f64x4_not_enable() _simd_f64x8_not_enable()
//#elif defined(_simd_f64x16_not_)
//	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_not(const register _simd_f64x4 x) {
//		union { _simd_f64x4 v1; _simd_f64x16 v2; };
//		v1 = x;
//		v2 = _simd_f64x16_not_(v2);
//		return v1;
//	}
//	#define _simd_f64x4_not_enable() _simd_f64x16_not_enable()
//#elif defined(_simd_f64x32_not_)
//	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_not(const register _simd_f64x4 x) {
//		union { _simd_f64x4 v1; _simd_f64x32 v2; };
//		v1 = x;
//		v2 = _simd_f64x32_not_(v2);
//		return v1;
//	}
//	#define _simd_f64x4_not_enable() _simd_f64x32_not_enable()
//#elif defined(_simd_f64x64_not_)
//	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_not(const register _simd_f64x4 x) {
//		union { _simd_f64x4 v1; _simd_f64x64 v2; };
//		v1 = x;
//		v2 = _simd_f64x64_not_(v2);
//		return v1;
//	}
//	#define _simd_f64x4_not_enable() _simd_f64x64_not_enable()
//#else
//	#define _simd_f64x4_not(X) _simd_f64x4_combine(\
//		_simd_f64x2_not(_simd_f64x4_splitlo(X)),\
//		_simd_f64x2_not(_simd_f64x4_splithi(X)))
//	#define _simd_f64x4_not_enable() (_simd_f64x2_not_enable() && _simd_f64x4_combine_enable() && _simd_f64x4_splitlo_enable()  && _simd_f64x4_splithi_enable())
//#endif
//
//#ifndef _simd_f64x1_not_safe
//	#define _simd_f64x1_not_safe(X) X
//	#define _simd_f64x1_not_(X) x1_not_safe(X)
//	#define _simd_f64x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_not_enabled() true
//#endif
//
//#define _simd_f64x8_not_safe(X)_simd_f64x8_combine_safe(\
//	_simd_f64x4_not_safe(_simd_f64x8_splitlo_safe(X)),\
//	_simd_f64x4_not_safe(_simd_f64x8_splithi_safe(X)))
//#ifdef _simd_f64x8_not_
//	#define _simd_f64x8_not(X) _simd_f64x8_not_(X)
//	#define _simd_f64x8_not_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_not_instruction_set>()
//#elif defined(_simd_f64x16_not_)
//	static ANVIL_STRONG_INLINE _simd_f64x8 ANVIL_SIMD_CALL _simd_f64x8_not(const register _simd_f64x8 x) {
//		union { _simd_f64x8 v1; _simd_f64x16 v2; };
//		v1 = x;
//		v2 = _simd_f64x16_not_(v2);
//		return v1;
//	}
//	#define _simd_f64x8_not_enable() _simd_f64x16_not_enable()
//#elif defined(_simd_f64x32_not_)
//	static ANVIL_STRONG_INLINE _simd_f64x8 ANVIL_SIMD_CALL _simd_f64x8_not(const register _simd_f64x8 x) {
//		union { _simd_f64x8 v1; _simd_f64x32 v2; };
//		v1 = x;
//		v2 = _simd_f64x32_not_(v2);
//		return v1;
//	}
//	#define _simd_f64x8_not_enable() _simd_f64x32_not_enable()
//#elif defined(_simd_f64x64_not_)
//	static ANVIL_STRONG_INLINE _simd_f64x8 ANVIL_SIMD_CALL _simd_f64x8_not(const register _simd_f64x8 x) {
//		union { _simd_f64x8 v1; _simd_f64x64 v2; };
//		v1 = x;
//		v2 = _simd_f64x64_not_(v2);
//		return v1;
//	}
//	#define _simd_f64x8_not_enable() _simd_f64x64_not_enable()
//#else
//	#define _simd_f64x8_not(X) _simd_f64x8_combine(\
//		_simd_f64x4_not(_simd_f64x8_splitlo(X)),\
//		_simd_f64x4_not(_simd_f64x8_splithi(X)))
//	#define _simd_f64x8_not_enable() (_simd_f64x4_not_enable() && _simd_f64x8_combine_enable() && _simd_f64x8_splitlo_enable()  && _simd_f64x8_splithi_enable())
//#endif
//
//#ifndef _simd_f64x1_not_safe
//	#define _simd_f64x1_not_safe(X) X
//	#define _simd_f64x1_not_(X) x1_not_safe(X)
//	#define _simd_f64x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_not_enabled() true
//#endif
//
//#define _simd_f64x16_not_safe(X)_simd_f64x16_combine_safe(\
//	_simd_f64x8_not_safe(_simd_f64x16_splitlo_safe(X)),\
//	_simd_f64x8_not_safe(_simd_f64x16_splithi_safe(X)))
//#ifdef _simd_f64x16_not_
//	#define _simd_f64x16_not(X) _simd_f64x16_not_(X)
//	#define _simd_f64x16_not_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_not_instruction_set>()
//#elif defined(_simd_f64x32_not_)
//	static ANVIL_STRONG_INLINE _simd_f64x16 ANVIL_SIMD_CALL _simd_f64x16_not(const register _simd_f64x16 x) {
//		union { _simd_f64x16 v1; _simd_f64x32 v2; };
//		v1 = x;
//		v2 = _simd_f64x32_not_(v2);
//		return v1;
//	}
//	#define _simd_f64x16_not_enable() _simd_f64x32_not_enable()
//#elif defined(_simd_f64x64_not_)
//	static ANVIL_STRONG_INLINE _simd_f64x16 ANVIL_SIMD_CALL _simd_f64x16_not(const register _simd_f64x16 x) {
//		union { _simd_f64x16 v1; _simd_f64x64 v2; };
//		v1 = x;
//		v2 = _simd_f64x64_not_(v2);
//		return v1;
//	}
//	#define _simd_f64x16_not_enable() _simd_f64x64_not_enable()
//#else
//	#define _simd_f64x16_not(X) _simd_f64x16_combine(\
//		_simd_f64x8_not(_simd_f64x16_splitlo(X)),\
//		_simd_f64x8_not(_simd_f64x16_splithi(X)))
//	#define _simd_f64x16_not_enable() (_simd_f64x8_not_enable() && _simd_f64x16_combine_enable() && _simd_f64x16_splitlo_enable()  && _simd_f64x16_splithi_enable())
//#endif
//
//#ifndef _simd_f64x1_not_safe
//	#define _simd_f64x1_not_safe(X) X
//	#define _simd_f64x1_not_(X) x1_not_safe(X)
//	#define _simd_f64x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_not_enabled() true
//#endif
//
//#define _simd_f64x32_not_safe(X)_simd_f64x32_combine_safe(\
//	_simd_f64x16_not_safe(_simd_f64x32_splitlo_safe(X)),\
//	_simd_f64x16_not_safe(_simd_f64x32_splithi_safe(X)))
//#ifdef _simd_f64x32_not_
//	#define _simd_f64x32_not(X) _simd_f64x32_not_(X)
//	#define _simd_f64x32_not_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_not_instruction_set>()
//#elif defined(_simd_f64x64_not_)
//	static ANVIL_STRONG_INLINE _simd_f64x32 ANVIL_SIMD_CALL _simd_f64x32_not(const register _simd_f64x32 x) {
//		union { _simd_f64x32 v1; _simd_f64x64 v2; };
//		v1 = x;
//		v2 = _simd_f64x64_not_(v2);
//		return v1;
//	}
//	#define _simd_f64x32_not_enable() _simd_f64x64_not_enable()
//#else
//	#define _simd_f64x32_not(X) _simd_f64x32_combine(\
//		_simd_f64x16_not(_simd_f64x32_splitlo(X)),\
//		_simd_f64x16_not(_simd_f64x32_splithi(X)))
//	#define _simd_f64x32_not_enable() (_simd_f64x16_not_enable() && _simd_f64x32_combine_enable() && _simd_f64x32_splitlo_enable()  && _simd_f64x32_splithi_enable())
//#endif
//
//#ifndef _simd_f64x1_not_safe
//	#define _simd_f64x1_not_safe(X) X
//	#define _simd_f64x1_not_(X) x1_not_safe(X)
//	#define _simd_f64x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_not_enabled() true
//#endif
//
//#define _simd_f64x64_not_safe(X)_simd_f64x64_combine_safe(\
//	_simd_f64x32_not_safe(_simd_f64x64_splitlo_safe(X)),\
//	_simd_f64x32_not_safe(_simd_f64x64_splithi_safe(X)))
//#ifdef _simd_f64x64_not_
//	#define _simd_f64x64_not(X) _simd_f64x64_not_(X)
//	#define _simd_f64x64_not_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_not_instruction_set>()
//#else
//	#define _simd_f64x64_not(X) _simd_f64x64_combine(\
//		_simd_f64x32_not(_simd_f64x64_splitlo(X)),\
//		_simd_f64x32_not(_simd_f64x64_splithi(X)))
//	#define _simd_f64x64_not_enable() (_simd_f64x32_not_enable() && _simd_f64x64_combine_enable() && _simd_f64x64_splitlo_enable()  && _simd_f64x64_splithi_enable())
//#endif
//
//// -- f32 --
//
//#ifndef _simd_f32x1_not_safe
//	#define _simd_f32x1_not_safe(X) X
//	#define _simd_f32x1_not_(X) x1_not_safe(X)
//	#define _simd_f32x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_not_enabled() true
//#endif
//
//#define _simd_f32x2_not_safe(X)_simd_f32x2_combine_safe(\
//	_simd_f32x1_not_safe(_simd_f32x2_splitlo_safe(X)),\
//	_simd_f32x1_not_safe(_simd_f32x2_splithi_safe(X)))
//#ifdef _simd_f32x2_not_
//	#define _simd_f32x2_not(X) _simd_f32x2_not_(X)
//	#define _simd_f32x2_not_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_not_instruction_set>()
//#elif defined(_simd_f32x4_not_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_not(const register _simd_f32x2 x) {
//		union { _simd_f32x2 v1; _simd_f32x4 v2; };
//		v1 = x;
//		v2 = _simd_f32x4_not_(v2);
//		return v1;
//	}
//	#define _simd_f32x2_not_enable() _simd_f32x4_not_enable()
//#elif defined(_simd_f32x8_not_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_not(const register _simd_f32x2 x) {
//		union { _simd_f32x2 v1; _simd_f32x8 v2; };
//		v1 = x;
//		v2 = _simd_f32x8_not_(v2);
//		return v1;
//	}
//	#define _simd_f32x2_not_enable() _simd_f32x8_not_enable()
//#elif defined(_simd_f32x16_not_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_not(const register _simd_f32x2 x) {
//		union { _simd_f32x2 v1; _simd_f32x16 v2; };
//		v1 = x;
//		v2 = _simd_f32x16_not_(v2);
//		return v1;
//	}
//	#define _simd_f32x2_not_enable() _simd_f32x16_not_enable()
//#elif defined(_simd_f32x32_not_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_not(const register _simd_f32x2 x) {
//		union { _simd_f32x2 v1; _simd_f32x32 v2; };
//		v1 = x;
//		v2 = _simd_f32x32_not_(v2);
//		return v1;
//	}
//	#define _simd_f32x2_not_enable() _simd_f32x32_not_enable()
//#elif defined(_simd_f32x64_not_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_not(const register _simd_f32x2 x) {
//		union { _simd_f32x2 v1; _simd_f32x64 v2; };
//		v1 = x;
//		v2 = _simd_f32x64_not_(v2);
//		return v1;
//	}
//	#define _simd_f32x2_not_enable() _simd_f32x64_not_enable()
//#else
//	#define _simd_f32x2_not(X) _simd_f32x2_combine(\
//		_simd_f32x1_not(_simd_f32x2_splitlo(X)),\
//		_simd_f32x1_not(_simd_f32x2_splithi(X)))
//	#define _simd_f32x2_not_enable() (_simd_f32x1_not_enable() && _simd_f32x2_combine_enable() && _simd_f32x2_splitlo_enable()  && _simd_f32x2_splithi_enable())
//#endif
//
//#ifndef _simd_f32x1_not_safe
//	#define _simd_f32x1_not_safe(X) X
//	#define _simd_f32x1_not_(X) x1_not_safe(X)
//	#define _simd_f32x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_not_enabled() true
//#endif
//
//#define _simd_f32x4_not_safe(X)_simd_f32x4_combine_safe(\
//	_simd_f32x2_not_safe(_simd_f32x4_splitlo_safe(X)),\
//	_simd_f32x2_not_safe(_simd_f32x4_splithi_safe(X)))
//#ifdef _simd_f32x4_not_
//	#define _simd_f32x4_not(X) _simd_f32x4_not_(X)
//	#define _simd_f32x4_not_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_not_instruction_set>()
//#elif defined(_simd_f32x8_not_)
//	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_not(const register _simd_f32x4 x) {
//		union { _simd_f32x4 v1; _simd_f32x8 v2; };
//		v1 = x;
//		v2 = _simd_f32x8_not_(v2);
//		return v1;
//	}
//	#define _simd_f32x4_not_enable() _simd_f32x8_not_enable()
//#elif defined(_simd_f32x16_not_)
//	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_not(const register _simd_f32x4 x) {
//		union { _simd_f32x4 v1; _simd_f32x16 v2; };
//		v1 = x;
//		v2 = _simd_f32x16_not_(v2);
//		return v1;
//	}
//	#define _simd_f32x4_not_enable() _simd_f32x16_not_enable()
//#elif defined(_simd_f32x32_not_)
//	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_not(const register _simd_f32x4 x) {
//		union { _simd_f32x4 v1; _simd_f32x32 v2; };
//		v1 = x;
//		v2 = _simd_f32x32_not_(v2);
//		return v1;
//	}
//	#define _simd_f32x4_not_enable() _simd_f32x32_not_enable()
//#elif defined(_simd_f32x64_not_)
//	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_not(const register _simd_f32x4 x) {
//		union { _simd_f32x4 v1; _simd_f32x64 v2; };
//		v1 = x;
//		v2 = _simd_f32x64_not_(v2);
//		return v1;
//	}
//	#define _simd_f32x4_not_enable() _simd_f32x64_not_enable()
//#else
//	#define _simd_f32x4_not(X) _simd_f32x4_combine(\
//		_simd_f32x2_not(_simd_f32x4_splitlo(X)),\
//		_simd_f32x2_not(_simd_f32x4_splithi(X)))
//	#define _simd_f32x4_not_enable() (_simd_f32x2_not_enable() && _simd_f32x4_combine_enable() && _simd_f32x4_splitlo_enable()  && _simd_f32x4_splithi_enable())
//#endif
//
//#ifndef _simd_f32x1_not_safe
//	#define _simd_f32x1_not_safe(X) X
//	#define _simd_f32x1_not_(X) x1_not_safe(X)
//	#define _simd_f32x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_not_enabled() true
//#endif
//
//#define _simd_f32x8_not_safe(X)_simd_f32x8_combine_safe(\
//	_simd_f32x4_not_safe(_simd_f32x8_splitlo_safe(X)),\
//	_simd_f32x4_not_safe(_simd_f32x8_splithi_safe(X)))
//#ifdef _simd_f32x8_not_
//	#define _simd_f32x8_not(X) _simd_f32x8_not_(X)
//	#define _simd_f32x8_not_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_not_instruction_set>()
//#elif defined(_simd_f32x16_not_)
//	static ANVIL_STRONG_INLINE _simd_f32x8 ANVIL_SIMD_CALL _simd_f32x8_not(const register _simd_f32x8 x) {
//		union { _simd_f32x8 v1; _simd_f32x16 v2; };
//		v1 = x;
//		v2 = _simd_f32x16_not_(v2);
//		return v1;
//	}
//	#define _simd_f32x8_not_enable() _simd_f32x16_not_enable()
//#elif defined(_simd_f32x32_not_)
//	static ANVIL_STRONG_INLINE _simd_f32x8 ANVIL_SIMD_CALL _simd_f32x8_not(const register _simd_f32x8 x) {
//		union { _simd_f32x8 v1; _simd_f32x32 v2; };
//		v1 = x;
//		v2 = _simd_f32x32_not_(v2);
//		return v1;
//	}
//	#define _simd_f32x8_not_enable() _simd_f32x32_not_enable()
//#elif defined(_simd_f32x64_not_)
//	static ANVIL_STRONG_INLINE _simd_f32x8 ANVIL_SIMD_CALL _simd_f32x8_not(const register _simd_f32x8 x) {
//		union { _simd_f32x8 v1; _simd_f32x64 v2; };
//		v1 = x;
//		v2 = _simd_f32x64_not_(v2);
//		return v1;
//	}
//	#define _simd_f32x8_not_enable() _simd_f32x64_not_enable()
//#else
//	#define _simd_f32x8_not(X) _simd_f32x8_combine(\
//		_simd_f32x4_not(_simd_f32x8_splitlo(X)),\
//		_simd_f32x4_not(_simd_f32x8_splithi(X)))
//	#define _simd_f32x8_not_enable() (_simd_f32x4_not_enable() && _simd_f32x8_combine_enable() && _simd_f32x8_splitlo_enable()  && _simd_f32x8_splithi_enable())
//#endif
//
//#ifndef _simd_f32x1_not_safe
//	#define _simd_f32x1_not_safe(X) X
//	#define _simd_f32x1_not_(X) x1_not_safe(X)
//	#define _simd_f32x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_not_enabled() true
//#endif
//
//#define _simd_f32x16_not_safe(X)_simd_f32x16_combine_safe(\
//	_simd_f32x8_not_safe(_simd_f32x16_splitlo_safe(X)),\
//	_simd_f32x8_not_safe(_simd_f32x16_splithi_safe(X)))
//#ifdef _simd_f32x16_not_
//	#define _simd_f32x16_not(X) _simd_f32x16_not_(X)
//	#define _simd_f32x16_not_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_not_instruction_set>()
//#elif defined(_simd_f32x32_not_)
//	static ANVIL_STRONG_INLINE _simd_f32x16 ANVIL_SIMD_CALL _simd_f32x16_not(const register _simd_f32x16 x) {
//		union { _simd_f32x16 v1; _simd_f32x32 v2; };
//		v1 = x;
//		v2 = _simd_f32x32_not_(v2);
//		return v1;
//	}
//	#define _simd_f32x16_not_enable() _simd_f32x32_not_enable()
//#elif defined(_simd_f32x64_not_)
//	static ANVIL_STRONG_INLINE _simd_f32x16 ANVIL_SIMD_CALL _simd_f32x16_not(const register _simd_f32x16 x) {
//		union { _simd_f32x16 v1; _simd_f32x64 v2; };
//		v1 = x;
//		v2 = _simd_f32x64_not_(v2);
//		return v1;
//	}
//	#define _simd_f32x16_not_enable() _simd_f32x64_not_enable()
//#else
//	#define _simd_f32x16_not(X) _simd_f32x16_combine(\
//		_simd_f32x8_not(_simd_f32x16_splitlo(X)),\
//		_simd_f32x8_not(_simd_f32x16_splithi(X)))
//	#define _simd_f32x16_not_enable() (_simd_f32x8_not_enable() && _simd_f32x16_combine_enable() && _simd_f32x16_splitlo_enable()  && _simd_f32x16_splithi_enable())
//#endif
//
//#ifndef _simd_f32x1_not_safe
//	#define _simd_f32x1_not_safe(X) X
//	#define _simd_f32x1_not_(X) x1_not_safe(X)
//	#define _simd_f32x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_not_enabled() true
//#endif
//
//#define _simd_f32x32_not_safe(X)_simd_f32x32_combine_safe(\
//	_simd_f32x16_not_safe(_simd_f32x32_splitlo_safe(X)),\
//	_simd_f32x16_not_safe(_simd_f32x32_splithi_safe(X)))
//#ifdef _simd_f32x32_not_
//	#define _simd_f32x32_not(X) _simd_f32x32_not_(X)
//	#define _simd_f32x32_not_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_not_instruction_set>()
//#elif defined(_simd_f32x64_not_)
//	static ANVIL_STRONG_INLINE _simd_f32x32 ANVIL_SIMD_CALL _simd_f32x32_not(const register _simd_f32x32 x) {
//		union { _simd_f32x32 v1; _simd_f32x64 v2; };
//		v1 = x;
//		v2 = _simd_f32x64_not_(v2);
//		return v1;
//	}
//	#define _simd_f32x32_not_enable() _simd_f32x64_not_enable()
//#else
//	#define _simd_f32x32_not(X) _simd_f32x32_combine(\
//		_simd_f32x16_not(_simd_f32x32_splitlo(X)),\
//		_simd_f32x16_not(_simd_f32x32_splithi(X)))
//	#define _simd_f32x32_not_enable() (_simd_f32x16_not_enable() && _simd_f32x32_combine_enable() && _simd_f32x32_splitlo_enable()  && _simd_f32x32_splithi_enable())
//#endif
//
//#ifndef _simd_f32x1_not_safe
//	#define _simd_f32x1_not_safe(X) X
//	#define _simd_f32x1_not_(X) x1_not_safe(X)
//	#define _simd_f32x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_not_enabled() true
//#endif
//
//#define _simd_f32x64_not_safe(X)_simd_f32x64_combine_safe(\
//	_simd_f32x32_not_safe(_simd_f32x64_splitlo_safe(X)),\
//	_simd_f32x32_not_safe(_simd_f32x64_splithi_safe(X)))
//#ifdef _simd_f32x64_not_
//	#define _simd_f32x64_not(X) _simd_f32x64_not_(X)
//	#define _simd_f32x64_not_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_not_instruction_set>()
//#else
//	#define _simd_f32x64_not(X) _simd_f32x64_combine(\
//		_simd_f32x32_not(_simd_f32x64_splitlo(X)),\
//		_simd_f32x32_not(_simd_f32x64_splithi(X)))
//	#define _simd_f32x64_not_enable() (_simd_f32x32_not_enable() && _simd_f32x64_combine_enable() && _simd_f32x64_splitlo_enable()  && _simd_f32x64_splithi_enable())
//#endif
//
//// -- s64 --
//
//#ifndef _simd_s64x1_not_safe
//	#define _simd_s64x1_not_safe(X) (~X)
//	#define _simd_s64x1_not_(X) x1_not_safe(X)
//	#define _simd_s64x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_not_enabled() true
//#endif
//
//#define _simd_s64x2_not_safe(X)_simd_s64x2_combine_safe(\
//	_simd_s64x1_not_safe(_simd_s64x2_splitlo_safe(X)),\
//	_simd_s64x1_not_safe(_simd_s64x2_splithi_safe(X)))
//#ifdef _simd_s64x2_not_
//	#define _simd_s64x2_not(X) _simd_s64x2_not_(X)
//	#define _simd_s64x2_not_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_not_instruction_set>()
//#elif defined(_simd_s64x4_not_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_not(const register _simd_s64x2 x) {
//		union { _simd_s64x2 v1; _simd_s64x4 v2; };
//		v1 = x;
//		v2 = _simd_s64x4_not_(v2);
//		return v1;
//	}
//	#define _simd_s64x2_not_enable() _simd_s64x4_not_enable()
//#elif defined(_simd_s64x8_not_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_not(const register _simd_s64x2 x) {
//		union { _simd_s64x2 v1; _simd_s64x8 v2; };
//		v1 = x;
//		v2 = _simd_s64x8_not_(v2);
//		return v1;
//	}
//	#define _simd_s64x2_not_enable() _simd_s64x8_not_enable()
//#elif defined(_simd_s64x16_not_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_not(const register _simd_s64x2 x) {
//		union { _simd_s64x2 v1; _simd_s64x16 v2; };
//		v1 = x;
//		v2 = _simd_s64x16_not_(v2);
//		return v1;
//	}
//	#define _simd_s64x2_not_enable() _simd_s64x16_not_enable()
//#elif defined(_simd_s64x32_not_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_not(const register _simd_s64x2 x) {
//		union { _simd_s64x2 v1; _simd_s64x32 v2; };
//		v1 = x;
//		v2 = _simd_s64x32_not_(v2);
//		return v1;
//	}
//	#define _simd_s64x2_not_enable() _simd_s64x32_not_enable()
//#elif defined(_simd_s64x64_not_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_not(const register _simd_s64x2 x) {
//		union { _simd_s64x2 v1; _simd_s64x64 v2; };
//		v1 = x;
//		v2 = _simd_s64x64_not_(v2);
//		return v1;
//	}
//	#define _simd_s64x2_not_enable() _simd_s64x64_not_enable()
//#else
//	#define _simd_s64x2_not(X) _simd_s64x2_combine(\
//		_simd_s64x1_not(_simd_s64x2_splitlo(X)),\
//		_simd_s64x1_not(_simd_s64x2_splithi(X)))
//	#define _simd_s64x2_not_enable() (_simd_s64x1_not_enable() && _simd_s64x2_combine_enable() && _simd_s64x2_splitlo_enable()  && _simd_s64x2_splithi_enable())
//#endif
//
//#ifndef _simd_s64x1_not_safe
//	#define _simd_s64x1_not_safe(X) (~X)
//	#define _simd_s64x1_not_(X) x1_not_safe(X)
//	#define _simd_s64x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_not_enabled() true
//#endif
//
//#define _simd_s64x4_not_safe(X)_simd_s64x4_combine_safe(\
//	_simd_s64x2_not_safe(_simd_s64x4_splitlo_safe(X)),\
//	_simd_s64x2_not_safe(_simd_s64x4_splithi_safe(X)))
//#ifdef _simd_s64x4_not_
//	#define _simd_s64x4_not(X) _simd_s64x4_not_(X)
//	#define _simd_s64x4_not_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_not_instruction_set>()
//#elif defined(_simd_s64x8_not_)
//	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_not(const register _simd_s64x4 x) {
//		union { _simd_s64x4 v1; _simd_s64x8 v2; };
//		v1 = x;
//		v2 = _simd_s64x8_not_(v2);
//		return v1;
//	}
//	#define _simd_s64x4_not_enable() _simd_s64x8_not_enable()
//#elif defined(_simd_s64x16_not_)
//	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_not(const register _simd_s64x4 x) {
//		union { _simd_s64x4 v1; _simd_s64x16 v2; };
//		v1 = x;
//		v2 = _simd_s64x16_not_(v2);
//		return v1;
//	}
//	#define _simd_s64x4_not_enable() _simd_s64x16_not_enable()
//#elif defined(_simd_s64x32_not_)
//	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_not(const register _simd_s64x4 x) {
//		union { _simd_s64x4 v1; _simd_s64x32 v2; };
//		v1 = x;
//		v2 = _simd_s64x32_not_(v2);
//		return v1;
//	}
//	#define _simd_s64x4_not_enable() _simd_s64x32_not_enable()
//#elif defined(_simd_s64x64_not_)
//	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_not(const register _simd_s64x4 x) {
//		union { _simd_s64x4 v1; _simd_s64x64 v2; };
//		v1 = x;
//		v2 = _simd_s64x64_not_(v2);
//		return v1;
//	}
//	#define _simd_s64x4_not_enable() _simd_s64x64_not_enable()
//#else
//	#define _simd_s64x4_not(X) _simd_s64x4_combine(\
//		_simd_s64x2_not(_simd_s64x4_splitlo(X)),\
//		_simd_s64x2_not(_simd_s64x4_splithi(X)))
//	#define _simd_s64x4_not_enable() (_simd_s64x2_not_enable() && _simd_s64x4_combine_enable() && _simd_s64x4_splitlo_enable()  && _simd_s64x4_splithi_enable())
//#endif
//
//#ifndef _simd_s64x1_not_safe
//	#define _simd_s64x1_not_safe(X) (~X)
//	#define _simd_s64x1_not_(X) x1_not_safe(X)
//	#define _simd_s64x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_not_enabled() true
//#endif
//
//#define _simd_s64x8_not_safe(X)_simd_s64x8_combine_safe(\
//	_simd_s64x4_not_safe(_simd_s64x8_splitlo_safe(X)),\
//	_simd_s64x4_not_safe(_simd_s64x8_splithi_safe(X)))
//#ifdef _simd_s64x8_not_
//	#define _simd_s64x8_not(X) _simd_s64x8_not_(X)
//	#define _simd_s64x8_not_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_not_instruction_set>()
//#elif defined(_simd_s64x16_not_)
//	static ANVIL_STRONG_INLINE _simd_s64x8 ANVIL_SIMD_CALL _simd_s64x8_not(const register _simd_s64x8 x) {
//		union { _simd_s64x8 v1; _simd_s64x16 v2; };
//		v1 = x;
//		v2 = _simd_s64x16_not_(v2);
//		return v1;
//	}
//	#define _simd_s64x8_not_enable() _simd_s64x16_not_enable()
//#elif defined(_simd_s64x32_not_)
//	static ANVIL_STRONG_INLINE _simd_s64x8 ANVIL_SIMD_CALL _simd_s64x8_not(const register _simd_s64x8 x) {
//		union { _simd_s64x8 v1; _simd_s64x32 v2; };
//		v1 = x;
//		v2 = _simd_s64x32_not_(v2);
//		return v1;
//	}
//	#define _simd_s64x8_not_enable() _simd_s64x32_not_enable()
//#elif defined(_simd_s64x64_not_)
//	static ANVIL_STRONG_INLINE _simd_s64x8 ANVIL_SIMD_CALL _simd_s64x8_not(const register _simd_s64x8 x) {
//		union { _simd_s64x8 v1; _simd_s64x64 v2; };
//		v1 = x;
//		v2 = _simd_s64x64_not_(v2);
//		return v1;
//	}
//	#define _simd_s64x8_not_enable() _simd_s64x64_not_enable()
//#else
//	#define _simd_s64x8_not(X) _simd_s64x8_combine(\
//		_simd_s64x4_not(_simd_s64x8_splitlo(X)),\
//		_simd_s64x4_not(_simd_s64x8_splithi(X)))
//	#define _simd_s64x8_not_enable() (_simd_s64x4_not_enable() && _simd_s64x8_combine_enable() && _simd_s64x8_splitlo_enable()  && _simd_s64x8_splithi_enable())
//#endif
//
//#ifndef _simd_s64x1_not_safe
//	#define _simd_s64x1_not_safe(X) (~X)
//	#define _simd_s64x1_not_(X) x1_not_safe(X)
//	#define _simd_s64x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_not_enabled() true
//#endif
//
//#define _simd_s64x16_not_safe(X)_simd_s64x16_combine_safe(\
//	_simd_s64x8_not_safe(_simd_s64x16_splitlo_safe(X)),\
//	_simd_s64x8_not_safe(_simd_s64x16_splithi_safe(X)))
//#ifdef _simd_s64x16_not_
//	#define _simd_s64x16_not(X) _simd_s64x16_not_(X)
//	#define _simd_s64x16_not_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_not_instruction_set>()
//#elif defined(_simd_s64x32_not_)
//	static ANVIL_STRONG_INLINE _simd_s64x16 ANVIL_SIMD_CALL _simd_s64x16_not(const register _simd_s64x16 x) {
//		union { _simd_s64x16 v1; _simd_s64x32 v2; };
//		v1 = x;
//		v2 = _simd_s64x32_not_(v2);
//		return v1;
//	}
//	#define _simd_s64x16_not_enable() _simd_s64x32_not_enable()
//#elif defined(_simd_s64x64_not_)
//	static ANVIL_STRONG_INLINE _simd_s64x16 ANVIL_SIMD_CALL _simd_s64x16_not(const register _simd_s64x16 x) {
//		union { _simd_s64x16 v1; _simd_s64x64 v2; };
//		v1 = x;
//		v2 = _simd_s64x64_not_(v2);
//		return v1;
//	}
//	#define _simd_s64x16_not_enable() _simd_s64x64_not_enable()
//#else
//	#define _simd_s64x16_not(X) _simd_s64x16_combine(\
//		_simd_s64x8_not(_simd_s64x16_splitlo(X)),\
//		_simd_s64x8_not(_simd_s64x16_splithi(X)))
//	#define _simd_s64x16_not_enable() (_simd_s64x8_not_enable() && _simd_s64x16_combine_enable() && _simd_s64x16_splitlo_enable()  && _simd_s64x16_splithi_enable())
//#endif
//
//#ifndef _simd_s64x1_not_safe
//	#define _simd_s64x1_not_safe(X) (~X)
//	#define _simd_s64x1_not_(X) x1_not_safe(X)
//	#define _simd_s64x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_not_enabled() true
//#endif
//
//#define _simd_s64x32_not_safe(X)_simd_s64x32_combine_safe(\
//	_simd_s64x16_not_safe(_simd_s64x32_splitlo_safe(X)),\
//	_simd_s64x16_not_safe(_simd_s64x32_splithi_safe(X)))
//#ifdef _simd_s64x32_not_
//	#define _simd_s64x32_not(X) _simd_s64x32_not_(X)
//	#define _simd_s64x32_not_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_not_instruction_set>()
//#elif defined(_simd_s64x64_not_)
//	static ANVIL_STRONG_INLINE _simd_s64x32 ANVIL_SIMD_CALL _simd_s64x32_not(const register _simd_s64x32 x) {
//		union { _simd_s64x32 v1; _simd_s64x64 v2; };
//		v1 = x;
//		v2 = _simd_s64x64_not_(v2);
//		return v1;
//	}
//	#define _simd_s64x32_not_enable() _simd_s64x64_not_enable()
//#else
//	#define _simd_s64x32_not(X) _simd_s64x32_combine(\
//		_simd_s64x16_not(_simd_s64x32_splitlo(X)),\
//		_simd_s64x16_not(_simd_s64x32_splithi(X)))
//	#define _simd_s64x32_not_enable() (_simd_s64x16_not_enable() && _simd_s64x32_combine_enable() && _simd_s64x32_splitlo_enable()  && _simd_s64x32_splithi_enable())
//#endif
//
//#ifndef _simd_s64x1_not_safe
//	#define _simd_s64x1_not_safe(X) (~X)
//	#define _simd_s64x1_not_(X) x1_not_safe(X)
//	#define _simd_s64x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_not_enabled() true
//#endif
//
//#define _simd_s64x64_not_safe(X)_simd_s64x64_combine_safe(\
//	_simd_s64x32_not_safe(_simd_s64x64_splitlo_safe(X)),\
//	_simd_s64x32_not_safe(_simd_s64x64_splithi_safe(X)))
//#ifdef _simd_s64x64_not_
//	#define _simd_s64x64_not(X) _simd_s64x64_not_(X)
//	#define _simd_s64x64_not_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_not_instruction_set>()
//#else
//	#define _simd_s64x64_not(X) _simd_s64x64_combine(\
//		_simd_s64x32_not(_simd_s64x64_splitlo(X)),\
//		_simd_s64x32_not(_simd_s64x64_splithi(X)))
//	#define _simd_s64x64_not_enable() (_simd_s64x32_not_enable() && _simd_s64x64_combine_enable() && _simd_s64x64_splitlo_enable()  && _simd_s64x64_splithi_enable())
//#endif
//
//// -- u64 --
//
//#ifndef _simd_u64x1_not_safe
//	#define _simd_u64x1_not_safe(X) (~X)
//	#define _simd_u64x1_not_(X) x1_not_safe(X)
//	#define _simd_u64x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_not_enabled() true
//#endif
//
//#define _simd_u64x2_not_safe(X)_simd_u64x2_combine_safe(\
//	_simd_u64x1_not_safe(_simd_u64x2_splitlo_safe(X)),\
//	_simd_u64x1_not_safe(_simd_u64x2_splithi_safe(X)))
//#ifdef _simd_u64x2_not_
//	#define _simd_u64x2_not(X) _simd_u64x2_not_(X)
//	#define _simd_u64x2_not_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_not_instruction_set>()
//#elif defined(_simd_u64x4_not_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_not(const register _simd_u64x2 x) {
//		union { _simd_u64x2 v1; _simd_u64x4 v2; };
//		v1 = x;
//		v2 = _simd_u64x4_not_(v2);
//		return v1;
//	}
//	#define _simd_u64x2_not_enable() _simd_u64x4_not_enable()
//#elif defined(_simd_u64x8_not_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_not(const register _simd_u64x2 x) {
//		union { _simd_u64x2 v1; _simd_u64x8 v2; };
//		v1 = x;
//		v2 = _simd_u64x8_not_(v2);
//		return v1;
//	}
//	#define _simd_u64x2_not_enable() _simd_u64x8_not_enable()
//#elif defined(_simd_u64x16_not_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_not(const register _simd_u64x2 x) {
//		union { _simd_u64x2 v1; _simd_u64x16 v2; };
//		v1 = x;
//		v2 = _simd_u64x16_not_(v2);
//		return v1;
//	}
//	#define _simd_u64x2_not_enable() _simd_u64x16_not_enable()
//#elif defined(_simd_u64x32_not_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_not(const register _simd_u64x2 x) {
//		union { _simd_u64x2 v1; _simd_u64x32 v2; };
//		v1 = x;
//		v2 = _simd_u64x32_not_(v2);
//		return v1;
//	}
//	#define _simd_u64x2_not_enable() _simd_u64x32_not_enable()
//#elif defined(_simd_u64x64_not_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_not(const register _simd_u64x2 x) {
//		union { _simd_u64x2 v1; _simd_u64x64 v2; };
//		v1 = x;
//		v2 = _simd_u64x64_not_(v2);
//		return v1;
//	}
//	#define _simd_u64x2_not_enable() _simd_u64x64_not_enable()
//#else
//	#define _simd_u64x2_not(X) _simd_u64x2_combine(\
//		_simd_u64x1_not(_simd_u64x2_splitlo(X)),\
//		_simd_u64x1_not(_simd_u64x2_splithi(X)))
//	#define _simd_u64x2_not_enable() (_simd_u64x1_not_enable() && _simd_u64x2_combine_enable() && _simd_u64x2_splitlo_enable()  && _simd_u64x2_splithi_enable())
//#endif
//
//#ifndef _simd_u64x1_not_safe
//	#define _simd_u64x1_not_safe(X) (~X)
//	#define _simd_u64x1_not_(X) x1_not_safe(X)
//	#define _simd_u64x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_not_enabled() true
//#endif
//
//#define _simd_u64x4_not_safe(X)_simd_u64x4_combine_safe(\
//	_simd_u64x2_not_safe(_simd_u64x4_splitlo_safe(X)),\
//	_simd_u64x2_not_safe(_simd_u64x4_splithi_safe(X)))
//#ifdef _simd_u64x4_not_
//	#define _simd_u64x4_not(X) _simd_u64x4_not_(X)
//	#define _simd_u64x4_not_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_not_instruction_set>()
//#elif defined(_simd_u64x8_not_)
//	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_not(const register _simd_u64x4 x) {
//		union { _simd_u64x4 v1; _simd_u64x8 v2; };
//		v1 = x;
//		v2 = _simd_u64x8_not_(v2);
//		return v1;
//	}
//	#define _simd_u64x4_not_enable() _simd_u64x8_not_enable()
//#elif defined(_simd_u64x16_not_)
//	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_not(const register _simd_u64x4 x) {
//		union { _simd_u64x4 v1; _simd_u64x16 v2; };
//		v1 = x;
//		v2 = _simd_u64x16_not_(v2);
//		return v1;
//	}
//	#define _simd_u64x4_not_enable() _simd_u64x16_not_enable()
//#elif defined(_simd_u64x32_not_)
//	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_not(const register _simd_u64x4 x) {
//		union { _simd_u64x4 v1; _simd_u64x32 v2; };
//		v1 = x;
//		v2 = _simd_u64x32_not_(v2);
//		return v1;
//	}
//	#define _simd_u64x4_not_enable() _simd_u64x32_not_enable()
//#elif defined(_simd_u64x64_not_)
//	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_not(const register _simd_u64x4 x) {
//		union { _simd_u64x4 v1; _simd_u64x64 v2; };
//		v1 = x;
//		v2 = _simd_u64x64_not_(v2);
//		return v1;
//	}
//	#define _simd_u64x4_not_enable() _simd_u64x64_not_enable()
//#else
//	#define _simd_u64x4_not(X) _simd_u64x4_combine(\
//		_simd_u64x2_not(_simd_u64x4_splitlo(X)),\
//		_simd_u64x2_not(_simd_u64x4_splithi(X)))
//	#define _simd_u64x4_not_enable() (_simd_u64x2_not_enable() && _simd_u64x4_combine_enable() && _simd_u64x4_splitlo_enable()  && _simd_u64x4_splithi_enable())
//#endif
//
//#ifndef _simd_u64x1_not_safe
//	#define _simd_u64x1_not_safe(X) (~X)
//	#define _simd_u64x1_not_(X) x1_not_safe(X)
//	#define _simd_u64x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_not_enabled() true
//#endif
//
//#define _simd_u64x8_not_safe(X)_simd_u64x8_combine_safe(\
//	_simd_u64x4_not_safe(_simd_u64x8_splitlo_safe(X)),\
//	_simd_u64x4_not_safe(_simd_u64x8_splithi_safe(X)))
//#ifdef _simd_u64x8_not_
//	#define _simd_u64x8_not(X) _simd_u64x8_not_(X)
//	#define _simd_u64x8_not_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_not_instruction_set>()
//#elif defined(_simd_u64x16_not_)
//	static ANVIL_STRONG_INLINE _simd_u64x8 ANVIL_SIMD_CALL _simd_u64x8_not(const register _simd_u64x8 x) {
//		union { _simd_u64x8 v1; _simd_u64x16 v2; };
//		v1 = x;
//		v2 = _simd_u64x16_not_(v2);
//		return v1;
//	}
//	#define _simd_u64x8_not_enable() _simd_u64x16_not_enable()
//#elif defined(_simd_u64x32_not_)
//	static ANVIL_STRONG_INLINE _simd_u64x8 ANVIL_SIMD_CALL _simd_u64x8_not(const register _simd_u64x8 x) {
//		union { _simd_u64x8 v1; _simd_u64x32 v2; };
//		v1 = x;
//		v2 = _simd_u64x32_not_(v2);
//		return v1;
//	}
//	#define _simd_u64x8_not_enable() _simd_u64x32_not_enable()
//#elif defined(_simd_u64x64_not_)
//	static ANVIL_STRONG_INLINE _simd_u64x8 ANVIL_SIMD_CALL _simd_u64x8_not(const register _simd_u64x8 x) {
//		union { _simd_u64x8 v1; _simd_u64x64 v2; };
//		v1 = x;
//		v2 = _simd_u64x64_not_(v2);
//		return v1;
//	}
//	#define _simd_u64x8_not_enable() _simd_u64x64_not_enable()
//#else
//	#define _simd_u64x8_not(X) _simd_u64x8_combine(\
//		_simd_u64x4_not(_simd_u64x8_splitlo(X)),\
//		_simd_u64x4_not(_simd_u64x8_splithi(X)))
//	#define _simd_u64x8_not_enable() (_simd_u64x4_not_enable() && _simd_u64x8_combine_enable() && _simd_u64x8_splitlo_enable()  && _simd_u64x8_splithi_enable())
//#endif
//
//#ifndef _simd_u64x1_not_safe
//	#define _simd_u64x1_not_safe(X) (~X)
//	#define _simd_u64x1_not_(X) x1_not_safe(X)
//	#define _simd_u64x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_not_enabled() true
//#endif
//
//#define _simd_u64x16_not_safe(X)_simd_u64x16_combine_safe(\
//	_simd_u64x8_not_safe(_simd_u64x16_splitlo_safe(X)),\
//	_simd_u64x8_not_safe(_simd_u64x16_splithi_safe(X)))
//#ifdef _simd_u64x16_not_
//	#define _simd_u64x16_not(X) _simd_u64x16_not_(X)
//	#define _simd_u64x16_not_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_not_instruction_set>()
//#elif defined(_simd_u64x32_not_)
//	static ANVIL_STRONG_INLINE _simd_u64x16 ANVIL_SIMD_CALL _simd_u64x16_not(const register _simd_u64x16 x) {
//		union { _simd_u64x16 v1; _simd_u64x32 v2; };
//		v1 = x;
//		v2 = _simd_u64x32_not_(v2);
//		return v1;
//	}
//	#define _simd_u64x16_not_enable() _simd_u64x32_not_enable()
//#elif defined(_simd_u64x64_not_)
//	static ANVIL_STRONG_INLINE _simd_u64x16 ANVIL_SIMD_CALL _simd_u64x16_not(const register _simd_u64x16 x) {
//		union { _simd_u64x16 v1; _simd_u64x64 v2; };
//		v1 = x;
//		v2 = _simd_u64x64_not_(v2);
//		return v1;
//	}
//	#define _simd_u64x16_not_enable() _simd_u64x64_not_enable()
//#else
//	#define _simd_u64x16_not(X) _simd_u64x16_combine(\
//		_simd_u64x8_not(_simd_u64x16_splitlo(X)),\
//		_simd_u64x8_not(_simd_u64x16_splithi(X)))
//	#define _simd_u64x16_not_enable() (_simd_u64x8_not_enable() && _simd_u64x16_combine_enable() && _simd_u64x16_splitlo_enable()  && _simd_u64x16_splithi_enable())
//#endif
//
//#ifndef _simd_u64x1_not_safe
//	#define _simd_u64x1_not_safe(X) (~X)
//	#define _simd_u64x1_not_(X) x1_not_safe(X)
//	#define _simd_u64x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_not_enabled() true
//#endif
//
//#define _simd_u64x32_not_safe(X)_simd_u64x32_combine_safe(\
//	_simd_u64x16_not_safe(_simd_u64x32_splitlo_safe(X)),\
//	_simd_u64x16_not_safe(_simd_u64x32_splithi_safe(X)))
//#ifdef _simd_u64x32_not_
//	#define _simd_u64x32_not(X) _simd_u64x32_not_(X)
//	#define _simd_u64x32_not_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_not_instruction_set>()
//#elif defined(_simd_u64x64_not_)
//	static ANVIL_STRONG_INLINE _simd_u64x32 ANVIL_SIMD_CALL _simd_u64x32_not(const register _simd_u64x32 x) {
//		union { _simd_u64x32 v1; _simd_u64x64 v2; };
//		v1 = x;
//		v2 = _simd_u64x64_not_(v2);
//		return v1;
//	}
//	#define _simd_u64x32_not_enable() _simd_u64x64_not_enable()
//#else
//	#define _simd_u64x32_not(X) _simd_u64x32_combine(\
//		_simd_u64x16_not(_simd_u64x32_splitlo(X)),\
//		_simd_u64x16_not(_simd_u64x32_splithi(X)))
//	#define _simd_u64x32_not_enable() (_simd_u64x16_not_enable() && _simd_u64x32_combine_enable() && _simd_u64x32_splitlo_enable()  && _simd_u64x32_splithi_enable())
//#endif
//
//#ifndef _simd_u64x1_not_safe
//	#define _simd_u64x1_not_safe(X) (~X)
//	#define _simd_u64x1_not_(X) x1_not_safe(X)
//	#define _simd_u64x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_not_enabled() true
//#endif
//
//#define _simd_u64x64_not_safe(X)_simd_u64x64_combine_safe(\
//	_simd_u64x32_not_safe(_simd_u64x64_splitlo_safe(X)),\
//	_simd_u64x32_not_safe(_simd_u64x64_splithi_safe(X)))
//#ifdef _simd_u64x64_not_
//	#define _simd_u64x64_not(X) _simd_u64x64_not_(X)
//	#define _simd_u64x64_not_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_not_instruction_set>()
//#else
//	#define _simd_u64x64_not(X) _simd_u64x64_combine(\
//		_simd_u64x32_not(_simd_u64x64_splitlo(X)),\
//		_simd_u64x32_not(_simd_u64x64_splithi(X)))
//	#define _simd_u64x64_not_enable() (_simd_u64x32_not_enable() && _simd_u64x64_combine_enable() && _simd_u64x64_splitlo_enable()  && _simd_u64x64_splithi_enable())
//#endif
//
//// -- s32 --
//
//#ifndef _simd_s32x1_not_safe
//	#define _simd_s32x1_not_safe(X) (~X)
//	#define _simd_s32x1_not_(X) x1_not_safe(X)
//	#define _simd_s32x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_not_enabled() true
//#endif
//
//#define _simd_s32x2_not_safe(X)_simd_s32x2_combine_safe(\
//	_simd_s32x1_not_safe(_simd_s32x2_splitlo_safe(X)),\
//	_simd_s32x1_not_safe(_simd_s32x2_splithi_safe(X)))
//#ifdef _simd_s32x2_not_
//	#define _simd_s32x2_not(X) _simd_s32x2_not_(X)
//	#define _simd_s32x2_not_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_not_instruction_set>()
//#elif defined(_simd_s32x4_not_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_not(const register _simd_s32x2 x) {
//		union { _simd_s32x2 v1; _simd_s32x4 v2; };
//		v1 = x;
//		v2 = _simd_s32x4_not_(v2);
//		return v1;
//	}
//	#define _simd_s32x2_not_enable() _simd_s32x4_not_enable()
//#elif defined(_simd_s32x8_not_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_not(const register _simd_s32x2 x) {
//		union { _simd_s32x2 v1; _simd_s32x8 v2; };
//		v1 = x;
//		v2 = _simd_s32x8_not_(v2);
//		return v1;
//	}
//	#define _simd_s32x2_not_enable() _simd_s32x8_not_enable()
//#elif defined(_simd_s32x16_not_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_not(const register _simd_s32x2 x) {
//		union { _simd_s32x2 v1; _simd_s32x16 v2; };
//		v1 = x;
//		v2 = _simd_s32x16_not_(v2);
//		return v1;
//	}
//	#define _simd_s32x2_not_enable() _simd_s32x16_not_enable()
//#elif defined(_simd_s32x32_not_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_not(const register _simd_s32x2 x) {
//		union { _simd_s32x2 v1; _simd_s32x32 v2; };
//		v1 = x;
//		v2 = _simd_s32x32_not_(v2);
//		return v1;
//	}
//	#define _simd_s32x2_not_enable() _simd_s32x32_not_enable()
//#elif defined(_simd_s32x64_not_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_not(const register _simd_s32x2 x) {
//		union { _simd_s32x2 v1; _simd_s32x64 v2; };
//		v1 = x;
//		v2 = _simd_s32x64_not_(v2);
//		return v1;
//	}
//	#define _simd_s32x2_not_enable() _simd_s32x64_not_enable()
//#else
//	#define _simd_s32x2_not(X) _simd_s32x2_combine(\
//		_simd_s32x1_not(_simd_s32x2_splitlo(X)),\
//		_simd_s32x1_not(_simd_s32x2_splithi(X)))
//	#define _simd_s32x2_not_enable() (_simd_s32x1_not_enable() && _simd_s32x2_combine_enable() && _simd_s32x2_splitlo_enable()  && _simd_s32x2_splithi_enable())
//#endif
//
//#ifndef _simd_s32x1_not_safe
//	#define _simd_s32x1_not_safe(X) (~X)
//	#define _simd_s32x1_not_(X) x1_not_safe(X)
//	#define _simd_s32x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_not_enabled() true
//#endif
//
//#define _simd_s32x4_not_safe(X)_simd_s32x4_combine_safe(\
//	_simd_s32x2_not_safe(_simd_s32x4_splitlo_safe(X)),\
//	_simd_s32x2_not_safe(_simd_s32x4_splithi_safe(X)))
//#ifdef _simd_s32x4_not_
//	#define _simd_s32x4_not(X) _simd_s32x4_not_(X)
//	#define _simd_s32x4_not_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_not_instruction_set>()
//#elif defined(_simd_s32x8_not_)
//	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_not(const register _simd_s32x4 x) {
//		union { _simd_s32x4 v1; _simd_s32x8 v2; };
//		v1 = x;
//		v2 = _simd_s32x8_not_(v2);
//		return v1;
//	}
//	#define _simd_s32x4_not_enable() _simd_s32x8_not_enable()
//#elif defined(_simd_s32x16_not_)
//	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_not(const register _simd_s32x4 x) {
//		union { _simd_s32x4 v1; _simd_s32x16 v2; };
//		v1 = x;
//		v2 = _simd_s32x16_not_(v2);
//		return v1;
//	}
//	#define _simd_s32x4_not_enable() _simd_s32x16_not_enable()
//#elif defined(_simd_s32x32_not_)
//	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_not(const register _simd_s32x4 x) {
//		union { _simd_s32x4 v1; _simd_s32x32 v2; };
//		v1 = x;
//		v2 = _simd_s32x32_not_(v2);
//		return v1;
//	}
//	#define _simd_s32x4_not_enable() _simd_s32x32_not_enable()
//#elif defined(_simd_s32x64_not_)
//	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_not(const register _simd_s32x4 x) {
//		union { _simd_s32x4 v1; _simd_s32x64 v2; };
//		v1 = x;
//		v2 = _simd_s32x64_not_(v2);
//		return v1;
//	}
//	#define _simd_s32x4_not_enable() _simd_s32x64_not_enable()
//#else
//	#define _simd_s32x4_not(X) _simd_s32x4_combine(\
//		_simd_s32x2_not(_simd_s32x4_splitlo(X)),\
//		_simd_s32x2_not(_simd_s32x4_splithi(X)))
//	#define _simd_s32x4_not_enable() (_simd_s32x2_not_enable() && _simd_s32x4_combine_enable() && _simd_s32x4_splitlo_enable()  && _simd_s32x4_splithi_enable())
//#endif
//
//#ifndef _simd_s32x1_not_safe
//	#define _simd_s32x1_not_safe(X) (~X)
//	#define _simd_s32x1_not_(X) x1_not_safe(X)
//	#define _simd_s32x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_not_enabled() true
//#endif
//
//#define _simd_s32x8_not_safe(X)_simd_s32x8_combine_safe(\
//	_simd_s32x4_not_safe(_simd_s32x8_splitlo_safe(X)),\
//	_simd_s32x4_not_safe(_simd_s32x8_splithi_safe(X)))
//#ifdef _simd_s32x8_not_
//	#define _simd_s32x8_not(X) _simd_s32x8_not_(X)
//	#define _simd_s32x8_not_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_not_instruction_set>()
//#elif defined(_simd_s32x16_not_)
//	static ANVIL_STRONG_INLINE _simd_s32x8 ANVIL_SIMD_CALL _simd_s32x8_not(const register _simd_s32x8 x) {
//		union { _simd_s32x8 v1; _simd_s32x16 v2; };
//		v1 = x;
//		v2 = _simd_s32x16_not_(v2);
//		return v1;
//	}
//	#define _simd_s32x8_not_enable() _simd_s32x16_not_enable()
//#elif defined(_simd_s32x32_not_)
//	static ANVIL_STRONG_INLINE _simd_s32x8 ANVIL_SIMD_CALL _simd_s32x8_not(const register _simd_s32x8 x) {
//		union { _simd_s32x8 v1; _simd_s32x32 v2; };
//		v1 = x;
//		v2 = _simd_s32x32_not_(v2);
//		return v1;
//	}
//	#define _simd_s32x8_not_enable() _simd_s32x32_not_enable()
//#elif defined(_simd_s32x64_not_)
//	static ANVIL_STRONG_INLINE _simd_s32x8 ANVIL_SIMD_CALL _simd_s32x8_not(const register _simd_s32x8 x) {
//		union { _simd_s32x8 v1; _simd_s32x64 v2; };
//		v1 = x;
//		v2 = _simd_s32x64_not_(v2);
//		return v1;
//	}
//	#define _simd_s32x8_not_enable() _simd_s32x64_not_enable()
//#else
//	#define _simd_s32x8_not(X) _simd_s32x8_combine(\
//		_simd_s32x4_not(_simd_s32x8_splitlo(X)),\
//		_simd_s32x4_not(_simd_s32x8_splithi(X)))
//	#define _simd_s32x8_not_enable() (_simd_s32x4_not_enable() && _simd_s32x8_combine_enable() && _simd_s32x8_splitlo_enable()  && _simd_s32x8_splithi_enable())
//#endif
//
//#ifndef _simd_s32x1_not_safe
//	#define _simd_s32x1_not_safe(X) (~X)
//	#define _simd_s32x1_not_(X) x1_not_safe(X)
//	#define _simd_s32x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_not_enabled() true
//#endif
//
//#define _simd_s32x16_not_safe(X)_simd_s32x16_combine_safe(\
//	_simd_s32x8_not_safe(_simd_s32x16_splitlo_safe(X)),\
//	_simd_s32x8_not_safe(_simd_s32x16_splithi_safe(X)))
//#ifdef _simd_s32x16_not_
//	#define _simd_s32x16_not(X) _simd_s32x16_not_(X)
//	#define _simd_s32x16_not_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_not_instruction_set>()
//#elif defined(_simd_s32x32_not_)
//	static ANVIL_STRONG_INLINE _simd_s32x16 ANVIL_SIMD_CALL _simd_s32x16_not(const register _simd_s32x16 x) {
//		union { _simd_s32x16 v1; _simd_s32x32 v2; };
//		v1 = x;
//		v2 = _simd_s32x32_not_(v2);
//		return v1;
//	}
//	#define _simd_s32x16_not_enable() _simd_s32x32_not_enable()
//#elif defined(_simd_s32x64_not_)
//	static ANVIL_STRONG_INLINE _simd_s32x16 ANVIL_SIMD_CALL _simd_s32x16_not(const register _simd_s32x16 x) {
//		union { _simd_s32x16 v1; _simd_s32x64 v2; };
//		v1 = x;
//		v2 = _simd_s32x64_not_(v2);
//		return v1;
//	}
//	#define _simd_s32x16_not_enable() _simd_s32x64_not_enable()
//#else
//	#define _simd_s32x16_not(X) _simd_s32x16_combine(\
//		_simd_s32x8_not(_simd_s32x16_splitlo(X)),\
//		_simd_s32x8_not(_simd_s32x16_splithi(X)))
//	#define _simd_s32x16_not_enable() (_simd_s32x8_not_enable() && _simd_s32x16_combine_enable() && _simd_s32x16_splitlo_enable()  && _simd_s32x16_splithi_enable())
//#endif
//
//#ifndef _simd_s32x1_not_safe
//	#define _simd_s32x1_not_safe(X) (~X)
//	#define _simd_s32x1_not_(X) x1_not_safe(X)
//	#define _simd_s32x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_not_enabled() true
//#endif
//
//#define _simd_s32x32_not_safe(X)_simd_s32x32_combine_safe(\
//	_simd_s32x16_not_safe(_simd_s32x32_splitlo_safe(X)),\
//	_simd_s32x16_not_safe(_simd_s32x32_splithi_safe(X)))
//#ifdef _simd_s32x32_not_
//	#define _simd_s32x32_not(X) _simd_s32x32_not_(X)
//	#define _simd_s32x32_not_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_not_instruction_set>()
//#elif defined(_simd_s32x64_not_)
//	static ANVIL_STRONG_INLINE _simd_s32x32 ANVIL_SIMD_CALL _simd_s32x32_not(const register _simd_s32x32 x) {
//		union { _simd_s32x32 v1; _simd_s32x64 v2; };
//		v1 = x;
//		v2 = _simd_s32x64_not_(v2);
//		return v1;
//	}
//	#define _simd_s32x32_not_enable() _simd_s32x64_not_enable()
//#else
//	#define _simd_s32x32_not(X) _simd_s32x32_combine(\
//		_simd_s32x16_not(_simd_s32x32_splitlo(X)),\
//		_simd_s32x16_not(_simd_s32x32_splithi(X)))
//	#define _simd_s32x32_not_enable() (_simd_s32x16_not_enable() && _simd_s32x32_combine_enable() && _simd_s32x32_splitlo_enable()  && _simd_s32x32_splithi_enable())
//#endif
//
//#ifndef _simd_s32x1_not_safe
//	#define _simd_s32x1_not_safe(X) (~X)
//	#define _simd_s32x1_not_(X) x1_not_safe(X)
//	#define _simd_s32x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_not_enabled() true
//#endif
//
//#define _simd_s32x64_not_safe(X)_simd_s32x64_combine_safe(\
//	_simd_s32x32_not_safe(_simd_s32x64_splitlo_safe(X)),\
//	_simd_s32x32_not_safe(_simd_s32x64_splithi_safe(X)))
//#ifdef _simd_s32x64_not_
//	#define _simd_s32x64_not(X) _simd_s32x64_not_(X)
//	#define _simd_s32x64_not_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_not_instruction_set>()
//#else
//	#define _simd_s32x64_not(X) _simd_s32x64_combine(\
//		_simd_s32x32_not(_simd_s32x64_splitlo(X)),\
//		_simd_s32x32_not(_simd_s32x64_splithi(X)))
//	#define _simd_s32x64_not_enable() (_simd_s32x32_not_enable() && _simd_s32x64_combine_enable() && _simd_s32x64_splitlo_enable()  && _simd_s32x64_splithi_enable())
//#endif
//
//// -- u32 --
//
//#ifndef _simd_u32x1_not_safe
//	#define _simd_u32x1_not_safe(X) (~X)
//	#define _simd_u32x1_not_(X) x1_not_safe(X)
//	#define _simd_u32x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_not_enabled() true
//#endif
//
//#define _simd_u32x2_not_safe(X)_simd_u32x2_combine_safe(\
//	_simd_u32x1_not_safe(_simd_u32x2_splitlo_safe(X)),\
//	_simd_u32x1_not_safe(_simd_u32x2_splithi_safe(X)))
//#ifdef _simd_u32x2_not_
//	#define _simd_u32x2_not(X) _simd_u32x2_not_(X)
//	#define _simd_u32x2_not_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_not_instruction_set>()
//#elif defined(_simd_u32x4_not_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_not(const register _simd_u32x2 x) {
//		union { _simd_u32x2 v1; _simd_u32x4 v2; };
//		v1 = x;
//		v2 = _simd_u32x4_not_(v2);
//		return v1;
//	}
//	#define _simd_u32x2_not_enable() _simd_u32x4_not_enable()
//#elif defined(_simd_u32x8_not_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_not(const register _simd_u32x2 x) {
//		union { _simd_u32x2 v1; _simd_u32x8 v2; };
//		v1 = x;
//		v2 = _simd_u32x8_not_(v2);
//		return v1;
//	}
//	#define _simd_u32x2_not_enable() _simd_u32x8_not_enable()
//#elif defined(_simd_u32x16_not_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_not(const register _simd_u32x2 x) {
//		union { _simd_u32x2 v1; _simd_u32x16 v2; };
//		v1 = x;
//		v2 = _simd_u32x16_not_(v2);
//		return v1;
//	}
//	#define _simd_u32x2_not_enable() _simd_u32x16_not_enable()
//#elif defined(_simd_u32x32_not_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_not(const register _simd_u32x2 x) {
//		union { _simd_u32x2 v1; _simd_u32x32 v2; };
//		v1 = x;
//		v2 = _simd_u32x32_not_(v2);
//		return v1;
//	}
//	#define _simd_u32x2_not_enable() _simd_u32x32_not_enable()
//#elif defined(_simd_u32x64_not_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_not(const register _simd_u32x2 x) {
//		union { _simd_u32x2 v1; _simd_u32x64 v2; };
//		v1 = x;
//		v2 = _simd_u32x64_not_(v2);
//		return v1;
//	}
//	#define _simd_u32x2_not_enable() _simd_u32x64_not_enable()
//#else
//	#define _simd_u32x2_not(X) _simd_u32x2_combine(\
//		_simd_u32x1_not(_simd_u32x2_splitlo(X)),\
//		_simd_u32x1_not(_simd_u32x2_splithi(X)))
//	#define _simd_u32x2_not_enable() (_simd_u32x1_not_enable() && _simd_u32x2_combine_enable() && _simd_u32x2_splitlo_enable()  && _simd_u32x2_splithi_enable())
//#endif
//
//#ifndef _simd_u32x1_not_safe
//	#define _simd_u32x1_not_safe(X) (~X)
//	#define _simd_u32x1_not_(X) x1_not_safe(X)
//	#define _simd_u32x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_not_enabled() true
//#endif
//
//#define _simd_u32x4_not_safe(X)_simd_u32x4_combine_safe(\
//	_simd_u32x2_not_safe(_simd_u32x4_splitlo_safe(X)),\
//	_simd_u32x2_not_safe(_simd_u32x4_splithi_safe(X)))
//#ifdef _simd_u32x4_not_
//	#define _simd_u32x4_not(X) _simd_u32x4_not_(X)
//	#define _simd_u32x4_not_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_not_instruction_set>()
//#elif defined(_simd_u32x8_not_)
//	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_not(const register _simd_u32x4 x) {
//		union { _simd_u32x4 v1; _simd_u32x8 v2; };
//		v1 = x;
//		v2 = _simd_u32x8_not_(v2);
//		return v1;
//	}
//	#define _simd_u32x4_not_enable() _simd_u32x8_not_enable()
//#elif defined(_simd_u32x16_not_)
//	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_not(const register _simd_u32x4 x) {
//		union { _simd_u32x4 v1; _simd_u32x16 v2; };
//		v1 = x;
//		v2 = _simd_u32x16_not_(v2);
//		return v1;
//	}
//	#define _simd_u32x4_not_enable() _simd_u32x16_not_enable()
//#elif defined(_simd_u32x32_not_)
//	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_not(const register _simd_u32x4 x) {
//		union { _simd_u32x4 v1; _simd_u32x32 v2; };
//		v1 = x;
//		v2 = _simd_u32x32_not_(v2);
//		return v1;
//	}
//	#define _simd_u32x4_not_enable() _simd_u32x32_not_enable()
//#elif defined(_simd_u32x64_not_)
//	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_not(const register _simd_u32x4 x) {
//		union { _simd_u32x4 v1; _simd_u32x64 v2; };
//		v1 = x;
//		v2 = _simd_u32x64_not_(v2);
//		return v1;
//	}
//	#define _simd_u32x4_not_enable() _simd_u32x64_not_enable()
//#else
//	#define _simd_u32x4_not(X) _simd_u32x4_combine(\
//		_simd_u32x2_not(_simd_u32x4_splitlo(X)),\
//		_simd_u32x2_not(_simd_u32x4_splithi(X)))
//	#define _simd_u32x4_not_enable() (_simd_u32x2_not_enable() && _simd_u32x4_combine_enable() && _simd_u32x4_splitlo_enable()  && _simd_u32x4_splithi_enable())
//#endif
//
//#ifndef _simd_u32x1_not_safe
//	#define _simd_u32x1_not_safe(X) (~X)
//	#define _simd_u32x1_not_(X) x1_not_safe(X)
//	#define _simd_u32x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_not_enabled() true
//#endif
//
//#define _simd_u32x8_not_safe(X)_simd_u32x8_combine_safe(\
//	_simd_u32x4_not_safe(_simd_u32x8_splitlo_safe(X)),\
//	_simd_u32x4_not_safe(_simd_u32x8_splithi_safe(X)))
//#ifdef _simd_u32x8_not_
//	#define _simd_u32x8_not(X) _simd_u32x8_not_(X)
//	#define _simd_u32x8_not_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_not_instruction_set>()
//#elif defined(_simd_u32x16_not_)
//	static ANVIL_STRONG_INLINE _simd_u32x8 ANVIL_SIMD_CALL _simd_u32x8_not(const register _simd_u32x8 x) {
//		union { _simd_u32x8 v1; _simd_u32x16 v2; };
//		v1 = x;
//		v2 = _simd_u32x16_not_(v2);
//		return v1;
//	}
//	#define _simd_u32x8_not_enable() _simd_u32x16_not_enable()
//#elif defined(_simd_u32x32_not_)
//	static ANVIL_STRONG_INLINE _simd_u32x8 ANVIL_SIMD_CALL _simd_u32x8_not(const register _simd_u32x8 x) {
//		union { _simd_u32x8 v1; _simd_u32x32 v2; };
//		v1 = x;
//		v2 = _simd_u32x32_not_(v2);
//		return v1;
//	}
//	#define _simd_u32x8_not_enable() _simd_u32x32_not_enable()
//#elif defined(_simd_u32x64_not_)
//	static ANVIL_STRONG_INLINE _simd_u32x8 ANVIL_SIMD_CALL _simd_u32x8_not(const register _simd_u32x8 x) {
//		union { _simd_u32x8 v1; _simd_u32x64 v2; };
//		v1 = x;
//		v2 = _simd_u32x64_not_(v2);
//		return v1;
//	}
//	#define _simd_u32x8_not_enable() _simd_u32x64_not_enable()
//#else
//	#define _simd_u32x8_not(X) _simd_u32x8_combine(\
//		_simd_u32x4_not(_simd_u32x8_splitlo(X)),\
//		_simd_u32x4_not(_simd_u32x8_splithi(X)))
//	#define _simd_u32x8_not_enable() (_simd_u32x4_not_enable() && _simd_u32x8_combine_enable() && _simd_u32x8_splitlo_enable()  && _simd_u32x8_splithi_enable())
//#endif
//
//#ifndef _simd_u32x1_not_safe
//	#define _simd_u32x1_not_safe(X) (~X)
//	#define _simd_u32x1_not_(X) x1_not_safe(X)
//	#define _simd_u32x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_not_enabled() true
//#endif
//
//#define _simd_u32x16_not_safe(X)_simd_u32x16_combine_safe(\
//	_simd_u32x8_not_safe(_simd_u32x16_splitlo_safe(X)),\
//	_simd_u32x8_not_safe(_simd_u32x16_splithi_safe(X)))
//#ifdef _simd_u32x16_not_
//	#define _simd_u32x16_not(X) _simd_u32x16_not_(X)
//	#define _simd_u32x16_not_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_not_instruction_set>()
//#elif defined(_simd_u32x32_not_)
//	static ANVIL_STRONG_INLINE _simd_u32x16 ANVIL_SIMD_CALL _simd_u32x16_not(const register _simd_u32x16 x) {
//		union { _simd_u32x16 v1; _simd_u32x32 v2; };
//		v1 = x;
//		v2 = _simd_u32x32_not_(v2);
//		return v1;
//	}
//	#define _simd_u32x16_not_enable() _simd_u32x32_not_enable()
//#elif defined(_simd_u32x64_not_)
//	static ANVIL_STRONG_INLINE _simd_u32x16 ANVIL_SIMD_CALL _simd_u32x16_not(const register _simd_u32x16 x) {
//		union { _simd_u32x16 v1; _simd_u32x64 v2; };
//		v1 = x;
//		v2 = _simd_u32x64_not_(v2);
//		return v1;
//	}
//	#define _simd_u32x16_not_enable() _simd_u32x64_not_enable()
//#else
//	#define _simd_u32x16_not(X) _simd_u32x16_combine(\
//		_simd_u32x8_not(_simd_u32x16_splitlo(X)),\
//		_simd_u32x8_not(_simd_u32x16_splithi(X)))
//	#define _simd_u32x16_not_enable() (_simd_u32x8_not_enable() && _simd_u32x16_combine_enable() && _simd_u32x16_splitlo_enable()  && _simd_u32x16_splithi_enable())
//#endif
//
//#ifndef _simd_u32x1_not_safe
//	#define _simd_u32x1_not_safe(X) (~X)
//	#define _simd_u32x1_not_(X) x1_not_safe(X)
//	#define _simd_u32x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_not_enabled() true
//#endif
//
//#define _simd_u32x32_not_safe(X)_simd_u32x32_combine_safe(\
//	_simd_u32x16_not_safe(_simd_u32x32_splitlo_safe(X)),\
//	_simd_u32x16_not_safe(_simd_u32x32_splithi_safe(X)))
//#ifdef _simd_u32x32_not_
//	#define _simd_u32x32_not(X) _simd_u32x32_not_(X)
//	#define _simd_u32x32_not_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_not_instruction_set>()
//#elif defined(_simd_u32x64_not_)
//	static ANVIL_STRONG_INLINE _simd_u32x32 ANVIL_SIMD_CALL _simd_u32x32_not(const register _simd_u32x32 x) {
//		union { _simd_u32x32 v1; _simd_u32x64 v2; };
//		v1 = x;
//		v2 = _simd_u32x64_not_(v2);
//		return v1;
//	}
//	#define _simd_u32x32_not_enable() _simd_u32x64_not_enable()
//#else
//	#define _simd_u32x32_not(X) _simd_u32x32_combine(\
//		_simd_u32x16_not(_simd_u32x32_splitlo(X)),\
//		_simd_u32x16_not(_simd_u32x32_splithi(X)))
//	#define _simd_u32x32_not_enable() (_simd_u32x16_not_enable() && _simd_u32x32_combine_enable() && _simd_u32x32_splitlo_enable()  && _simd_u32x32_splithi_enable())
//#endif
//
//#ifndef _simd_u32x1_not_safe
//	#define _simd_u32x1_not_safe(X) (~X)
//	#define _simd_u32x1_not_(X) x1_not_safe(X)
//	#define _simd_u32x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_not_enabled() true
//#endif
//
//#define _simd_u32x64_not_safe(X)_simd_u32x64_combine_safe(\
//	_simd_u32x32_not_safe(_simd_u32x64_splitlo_safe(X)),\
//	_simd_u32x32_not_safe(_simd_u32x64_splithi_safe(X)))
//#ifdef _simd_u32x64_not_
//	#define _simd_u32x64_not(X) _simd_u32x64_not_(X)
//	#define _simd_u32x64_not_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_not_instruction_set>()
//#else
//	#define _simd_u32x64_not(X) _simd_u32x64_combine(\
//		_simd_u32x32_not(_simd_u32x64_splitlo(X)),\
//		_simd_u32x32_not(_simd_u32x64_splithi(X)))
//	#define _simd_u32x64_not_enable() (_simd_u32x32_not_enable() && _simd_u32x64_combine_enable() && _simd_u32x64_splitlo_enable()  && _simd_u32x64_splithi_enable())
//#endif
//
//// -- s16 --
//
//#ifndef _simd_s16x1_not_safe
//	#define _simd_s16x1_not_safe(X) (~X)
//	#define _simd_s16x1_not_(X) x1_not_safe(X)
//	#define _simd_s16x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_not_enabled() true
//#endif
//
//#define _simd_s16x2_not_safe(X)_simd_s16x2_combine_safe(\
//	_simd_s16x1_not_safe(_simd_s16x2_splitlo_safe(X)),\
//	_simd_s16x1_not_safe(_simd_s16x2_splithi_safe(X)))
//#ifdef _simd_s16x2_not_
//	#define _simd_s16x2_not(X) _simd_s16x2_not_(X)
//	#define _simd_s16x2_not_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_not_instruction_set>()
//#elif defined(_simd_s16x4_not_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_not(const register _simd_s16x2 x) {
//		union { _simd_s16x2 v1; _simd_s16x4 v2; };
//		v1 = x;
//		v2 = _simd_s16x4_not_(v2);
//		return v1;
//	}
//	#define _simd_s16x2_not_enable() _simd_s16x4_not_enable()
//#elif defined(_simd_s16x8_not_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_not(const register _simd_s16x2 x) {
//		union { _simd_s16x2 v1; _simd_s16x8 v2; };
//		v1 = x;
//		v2 = _simd_s16x8_not_(v2);
//		return v1;
//	}
//	#define _simd_s16x2_not_enable() _simd_s16x8_not_enable()
//#elif defined(_simd_s16x16_not_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_not(const register _simd_s16x2 x) {
//		union { _simd_s16x2 v1; _simd_s16x16 v2; };
//		v1 = x;
//		v2 = _simd_s16x16_not_(v2);
//		return v1;
//	}
//	#define _simd_s16x2_not_enable() _simd_s16x16_not_enable()
//#elif defined(_simd_s16x32_not_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_not(const register _simd_s16x2 x) {
//		union { _simd_s16x2 v1; _simd_s16x32 v2; };
//		v1 = x;
//		v2 = _simd_s16x32_not_(v2);
//		return v1;
//	}
//	#define _simd_s16x2_not_enable() _simd_s16x32_not_enable()
//#elif defined(_simd_s16x64_not_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_not(const register _simd_s16x2 x) {
//		union { _simd_s16x2 v1; _simd_s16x64 v2; };
//		v1 = x;
//		v2 = _simd_s16x64_not_(v2);
//		return v1;
//	}
//	#define _simd_s16x2_not_enable() _simd_s16x64_not_enable()
//#else
//	#define _simd_s16x2_not(X) _simd_s16x2_combine(\
//		_simd_s16x1_not(_simd_s16x2_splitlo(X)),\
//		_simd_s16x1_not(_simd_s16x2_splithi(X)))
//	#define _simd_s16x2_not_enable() (_simd_s16x1_not_enable() && _simd_s16x2_combine_enable() && _simd_s16x2_splitlo_enable()  && _simd_s16x2_splithi_enable())
//#endif
//
//#ifndef _simd_s16x1_not_safe
//	#define _simd_s16x1_not_safe(X) (~X)
//	#define _simd_s16x1_not_(X) x1_not_safe(X)
//	#define _simd_s16x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_not_enabled() true
//#endif
//
//#define _simd_s16x4_not_safe(X)_simd_s16x4_combine_safe(\
//	_simd_s16x2_not_safe(_simd_s16x4_splitlo_safe(X)),\
//	_simd_s16x2_not_safe(_simd_s16x4_splithi_safe(X)))
//#ifdef _simd_s16x4_not_
//	#define _simd_s16x4_not(X) _simd_s16x4_not_(X)
//	#define _simd_s16x4_not_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_not_instruction_set>()
//#elif defined(_simd_s16x8_not_)
//	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_not(const register _simd_s16x4 x) {
//		union { _simd_s16x4 v1; _simd_s16x8 v2; };
//		v1 = x;
//		v2 = _simd_s16x8_not_(v2);
//		return v1;
//	}
//	#define _simd_s16x4_not_enable() _simd_s16x8_not_enable()
//#elif defined(_simd_s16x16_not_)
//	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_not(const register _simd_s16x4 x) {
//		union { _simd_s16x4 v1; _simd_s16x16 v2; };
//		v1 = x;
//		v2 = _simd_s16x16_not_(v2);
//		return v1;
//	}
//	#define _simd_s16x4_not_enable() _simd_s16x16_not_enable()
//#elif defined(_simd_s16x32_not_)
//	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_not(const register _simd_s16x4 x) {
//		union { _simd_s16x4 v1; _simd_s16x32 v2; };
//		v1 = x;
//		v2 = _simd_s16x32_not_(v2);
//		return v1;
//	}
//	#define _simd_s16x4_not_enable() _simd_s16x32_not_enable()
//#elif defined(_simd_s16x64_not_)
//	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_not(const register _simd_s16x4 x) {
//		union { _simd_s16x4 v1; _simd_s16x64 v2; };
//		v1 = x;
//		v2 = _simd_s16x64_not_(v2);
//		return v1;
//	}
//	#define _simd_s16x4_not_enable() _simd_s16x64_not_enable()
//#else
//	#define _simd_s16x4_not(X) _simd_s16x4_combine(\
//		_simd_s16x2_not(_simd_s16x4_splitlo(X)),\
//		_simd_s16x2_not(_simd_s16x4_splithi(X)))
//	#define _simd_s16x4_not_enable() (_simd_s16x2_not_enable() && _simd_s16x4_combine_enable() && _simd_s16x4_splitlo_enable()  && _simd_s16x4_splithi_enable())
//#endif
//
//#ifndef _simd_s16x1_not_safe
//	#define _simd_s16x1_not_safe(X) (~X)
//	#define _simd_s16x1_not_(X) x1_not_safe(X)
//	#define _simd_s16x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_not_enabled() true
//#endif
//
//#define _simd_s16x8_not_safe(X)_simd_s16x8_combine_safe(\
//	_simd_s16x4_not_safe(_simd_s16x8_splitlo_safe(X)),\
//	_simd_s16x4_not_safe(_simd_s16x8_splithi_safe(X)))
//#ifdef _simd_s16x8_not_
//	#define _simd_s16x8_not(X) _simd_s16x8_not_(X)
//	#define _simd_s16x8_not_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_not_instruction_set>()
//#elif defined(_simd_s16x16_not_)
//	static ANVIL_STRONG_INLINE _simd_s16x8 ANVIL_SIMD_CALL _simd_s16x8_not(const register _simd_s16x8 x) {
//		union { _simd_s16x8 v1; _simd_s16x16 v2; };
//		v1 = x;
//		v2 = _simd_s16x16_not_(v2);
//		return v1;
//	}
//	#define _simd_s16x8_not_enable() _simd_s16x16_not_enable()
//#elif defined(_simd_s16x32_not_)
//	static ANVIL_STRONG_INLINE _simd_s16x8 ANVIL_SIMD_CALL _simd_s16x8_not(const register _simd_s16x8 x) {
//		union { _simd_s16x8 v1; _simd_s16x32 v2; };
//		v1 = x;
//		v2 = _simd_s16x32_not_(v2);
//		return v1;
//	}
//	#define _simd_s16x8_not_enable() _simd_s16x32_not_enable()
//#elif defined(_simd_s16x64_not_)
//	static ANVIL_STRONG_INLINE _simd_s16x8 ANVIL_SIMD_CALL _simd_s16x8_not(const register _simd_s16x8 x) {
//		union { _simd_s16x8 v1; _simd_s16x64 v2; };
//		v1 = x;
//		v2 = _simd_s16x64_not_(v2);
//		return v1;
//	}
//	#define _simd_s16x8_not_enable() _simd_s16x64_not_enable()
//#else
//	#define _simd_s16x8_not(X) _simd_s16x8_combine(\
//		_simd_s16x4_not(_simd_s16x8_splitlo(X)),\
//		_simd_s16x4_not(_simd_s16x8_splithi(X)))
//	#define _simd_s16x8_not_enable() (_simd_s16x4_not_enable() && _simd_s16x8_combine_enable() && _simd_s16x8_splitlo_enable()  && _simd_s16x8_splithi_enable())
//#endif
//
//#ifndef _simd_s16x1_not_safe
//	#define _simd_s16x1_not_safe(X) (~X)
//	#define _simd_s16x1_not_(X) x1_not_safe(X)
//	#define _simd_s16x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_not_enabled() true
//#endif
//
//#define _simd_s16x16_not_safe(X)_simd_s16x16_combine_safe(\
//	_simd_s16x8_not_safe(_simd_s16x16_splitlo_safe(X)),\
//	_simd_s16x8_not_safe(_simd_s16x16_splithi_safe(X)))
//#ifdef _simd_s16x16_not_
//	#define _simd_s16x16_not(X) _simd_s16x16_not_(X)
//	#define _simd_s16x16_not_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_not_instruction_set>()
//#elif defined(_simd_s16x32_not_)
//	static ANVIL_STRONG_INLINE _simd_s16x16 ANVIL_SIMD_CALL _simd_s16x16_not(const register _simd_s16x16 x) {
//		union { _simd_s16x16 v1; _simd_s16x32 v2; };
//		v1 = x;
//		v2 = _simd_s16x32_not_(v2);
//		return v1;
//	}
//	#define _simd_s16x16_not_enable() _simd_s16x32_not_enable()
//#elif defined(_simd_s16x64_not_)
//	static ANVIL_STRONG_INLINE _simd_s16x16 ANVIL_SIMD_CALL _simd_s16x16_not(const register _simd_s16x16 x) {
//		union { _simd_s16x16 v1; _simd_s16x64 v2; };
//		v1 = x;
//		v2 = _simd_s16x64_not_(v2);
//		return v1;
//	}
//	#define _simd_s16x16_not_enable() _simd_s16x64_not_enable()
//#else
//	#define _simd_s16x16_not(X) _simd_s16x16_combine(\
//		_simd_s16x8_not(_simd_s16x16_splitlo(X)),\
//		_simd_s16x8_not(_simd_s16x16_splithi(X)))
//	#define _simd_s16x16_not_enable() (_simd_s16x8_not_enable() && _simd_s16x16_combine_enable() && _simd_s16x16_splitlo_enable()  && _simd_s16x16_splithi_enable())
//#endif
//
//#ifndef _simd_s16x1_not_safe
//	#define _simd_s16x1_not_safe(X) (~X)
//	#define _simd_s16x1_not_(X) x1_not_safe(X)
//	#define _simd_s16x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_not_enabled() true
//#endif
//
//#define _simd_s16x32_not_safe(X)_simd_s16x32_combine_safe(\
//	_simd_s16x16_not_safe(_simd_s16x32_splitlo_safe(X)),\
//	_simd_s16x16_not_safe(_simd_s16x32_splithi_safe(X)))
//#ifdef _simd_s16x32_not_
//	#define _simd_s16x32_not(X) _simd_s16x32_not_(X)
//	#define _simd_s16x32_not_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_not_instruction_set>()
//#elif defined(_simd_s16x64_not_)
//	static ANVIL_STRONG_INLINE _simd_s16x32 ANVIL_SIMD_CALL _simd_s16x32_not(const register _simd_s16x32 x) {
//		union { _simd_s16x32 v1; _simd_s16x64 v2; };
//		v1 = x;
//		v2 = _simd_s16x64_not_(v2);
//		return v1;
//	}
//	#define _simd_s16x32_not_enable() _simd_s16x64_not_enable()
//#else
//	#define _simd_s16x32_not(X) _simd_s16x32_combine(\
//		_simd_s16x16_not(_simd_s16x32_splitlo(X)),\
//		_simd_s16x16_not(_simd_s16x32_splithi(X)))
//	#define _simd_s16x32_not_enable() (_simd_s16x16_not_enable() && _simd_s16x32_combine_enable() && _simd_s16x32_splitlo_enable()  && _simd_s16x32_splithi_enable())
//#endif
//
//#ifndef _simd_s16x1_not_safe
//	#define _simd_s16x1_not_safe(X) (~X)
//	#define _simd_s16x1_not_(X) x1_not_safe(X)
//	#define _simd_s16x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_not_enabled() true
//#endif
//
//#define _simd_s16x64_not_safe(X)_simd_s16x64_combine_safe(\
//	_simd_s16x32_not_safe(_simd_s16x64_splitlo_safe(X)),\
//	_simd_s16x32_not_safe(_simd_s16x64_splithi_safe(X)))
//#ifdef _simd_s16x64_not_
//	#define _simd_s16x64_not(X) _simd_s16x64_not_(X)
//	#define _simd_s16x64_not_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_not_instruction_set>()
//#else
//	#define _simd_s16x64_not(X) _simd_s16x64_combine(\
//		_simd_s16x32_not(_simd_s16x64_splitlo(X)),\
//		_simd_s16x32_not(_simd_s16x64_splithi(X)))
//	#define _simd_s16x64_not_enable() (_simd_s16x32_not_enable() && _simd_s16x64_combine_enable() && _simd_s16x64_splitlo_enable()  && _simd_s16x64_splithi_enable())
//#endif
//
//// -- u16 --
//
//#ifndef _simd_u16x1_not_safe
//	#define _simd_u16x1_not_safe(X) (~X)
//	#define _simd_u16x1_not_(X) x1_not_safe(X)
//	#define _simd_u16x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_not_enabled() true
//#endif
//
//#define _simd_u16x2_not_safe(X)_simd_u16x2_combine_safe(\
//	_simd_u16x1_not_safe(_simd_u16x2_splitlo_safe(X)),\
//	_simd_u16x1_not_safe(_simd_u16x2_splithi_safe(X)))
//#ifdef _simd_u16x2_not_
//	#define _simd_u16x2_not(X) _simd_u16x2_not_(X)
//	#define _simd_u16x2_not_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_not_instruction_set>()
//#elif defined(_simd_u16x4_not_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_not(const register _simd_u16x2 x) {
//		union { _simd_u16x2 v1; _simd_u16x4 v2; };
//		v1 = x;
//		v2 = _simd_u16x4_not_(v2);
//		return v1;
//	}
//	#define _simd_u16x2_not_enable() _simd_u16x4_not_enable()
//#elif defined(_simd_u16x8_not_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_not(const register _simd_u16x2 x) {
//		union { _simd_u16x2 v1; _simd_u16x8 v2; };
//		v1 = x;
//		v2 = _simd_u16x8_not_(v2);
//		return v1;
//	}
//	#define _simd_u16x2_not_enable() _simd_u16x8_not_enable()
//#elif defined(_simd_u16x16_not_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_not(const register _simd_u16x2 x) {
//		union { _simd_u16x2 v1; _simd_u16x16 v2; };
//		v1 = x;
//		v2 = _simd_u16x16_not_(v2);
//		return v1;
//	}
//	#define _simd_u16x2_not_enable() _simd_u16x16_not_enable()
//#elif defined(_simd_u16x32_not_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_not(const register _simd_u16x2 x) {
//		union { _simd_u16x2 v1; _simd_u16x32 v2; };
//		v1 = x;
//		v2 = _simd_u16x32_not_(v2);
//		return v1;
//	}
//	#define _simd_u16x2_not_enable() _simd_u16x32_not_enable()
//#elif defined(_simd_u16x64_not_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_not(const register _simd_u16x2 x) {
//		union { _simd_u16x2 v1; _simd_u16x64 v2; };
//		v1 = x;
//		v2 = _simd_u16x64_not_(v2);
//		return v1;
//	}
//	#define _simd_u16x2_not_enable() _simd_u16x64_not_enable()
//#else
//	#define _simd_u16x2_not(X) _simd_u16x2_combine(\
//		_simd_u16x1_not(_simd_u16x2_splitlo(X)),\
//		_simd_u16x1_not(_simd_u16x2_splithi(X)))
//	#define _simd_u16x2_not_enable() (_simd_u16x1_not_enable() && _simd_u16x2_combine_enable() && _simd_u16x2_splitlo_enable()  && _simd_u16x2_splithi_enable())
//#endif
//
//#ifndef _simd_u16x1_not_safe
//	#define _simd_u16x1_not_safe(X) (~X)
//	#define _simd_u16x1_not_(X) x1_not_safe(X)
//	#define _simd_u16x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_not_enabled() true
//#endif
//
//#define _simd_u16x4_not_safe(X)_simd_u16x4_combine_safe(\
//	_simd_u16x2_not_safe(_simd_u16x4_splitlo_safe(X)),\
//	_simd_u16x2_not_safe(_simd_u16x4_splithi_safe(X)))
//#ifdef _simd_u16x4_not_
//	#define _simd_u16x4_not(X) _simd_u16x4_not_(X)
//	#define _simd_u16x4_not_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_not_instruction_set>()
//#elif defined(_simd_u16x8_not_)
//	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_not(const register _simd_u16x4 x) {
//		union { _simd_u16x4 v1; _simd_u16x8 v2; };
//		v1 = x;
//		v2 = _simd_u16x8_not_(v2);
//		return v1;
//	}
//	#define _simd_u16x4_not_enable() _simd_u16x8_not_enable()
//#elif defined(_simd_u16x16_not_)
//	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_not(const register _simd_u16x4 x) {
//		union { _simd_u16x4 v1; _simd_u16x16 v2; };
//		v1 = x;
//		v2 = _simd_u16x16_not_(v2);
//		return v1;
//	}
//	#define _simd_u16x4_not_enable() _simd_u16x16_not_enable()
//#elif defined(_simd_u16x32_not_)
//	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_not(const register _simd_u16x4 x) {
//		union { _simd_u16x4 v1; _simd_u16x32 v2; };
//		v1 = x;
//		v2 = _simd_u16x32_not_(v2);
//		return v1;
//	}
//	#define _simd_u16x4_not_enable() _simd_u16x32_not_enable()
//#elif defined(_simd_u16x64_not_)
//	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_not(const register _simd_u16x4 x) {
//		union { _simd_u16x4 v1; _simd_u16x64 v2; };
//		v1 = x;
//		v2 = _simd_u16x64_not_(v2);
//		return v1;
//	}
//	#define _simd_u16x4_not_enable() _simd_u16x64_not_enable()
//#else
//	#define _simd_u16x4_not(X) _simd_u16x4_combine(\
//		_simd_u16x2_not(_simd_u16x4_splitlo(X)),\
//		_simd_u16x2_not(_simd_u16x4_splithi(X)))
//	#define _simd_u16x4_not_enable() (_simd_u16x2_not_enable() && _simd_u16x4_combine_enable() && _simd_u16x4_splitlo_enable()  && _simd_u16x4_splithi_enable())
//#endif
//
//#ifndef _simd_u16x1_not_safe
//	#define _simd_u16x1_not_safe(X) (~X)
//	#define _simd_u16x1_not_(X) x1_not_safe(X)
//	#define _simd_u16x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_not_enabled() true
//#endif
//
//#define _simd_u16x8_not_safe(X)_simd_u16x8_combine_safe(\
//	_simd_u16x4_not_safe(_simd_u16x8_splitlo_safe(X)),\
//	_simd_u16x4_not_safe(_simd_u16x8_splithi_safe(X)))
//#ifdef _simd_u16x8_not_
//	#define _simd_u16x8_not(X) _simd_u16x8_not_(X)
//	#define _simd_u16x8_not_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_not_instruction_set>()
//#elif defined(_simd_u16x16_not_)
//	static ANVIL_STRONG_INLINE _simd_u16x8 ANVIL_SIMD_CALL _simd_u16x8_not(const register _simd_u16x8 x) {
//		union { _simd_u16x8 v1; _simd_u16x16 v2; };
//		v1 = x;
//		v2 = _simd_u16x16_not_(v2);
//		return v1;
//	}
//	#define _simd_u16x8_not_enable() _simd_u16x16_not_enable()
//#elif defined(_simd_u16x32_not_)
//	static ANVIL_STRONG_INLINE _simd_u16x8 ANVIL_SIMD_CALL _simd_u16x8_not(const register _simd_u16x8 x) {
//		union { _simd_u16x8 v1; _simd_u16x32 v2; };
//		v1 = x;
//		v2 = _simd_u16x32_not_(v2);
//		return v1;
//	}
//	#define _simd_u16x8_not_enable() _simd_u16x32_not_enable()
//#elif defined(_simd_u16x64_not_)
//	static ANVIL_STRONG_INLINE _simd_u16x8 ANVIL_SIMD_CALL _simd_u16x8_not(const register _simd_u16x8 x) {
//		union { _simd_u16x8 v1; _simd_u16x64 v2; };
//		v1 = x;
//		v2 = _simd_u16x64_not_(v2);
//		return v1;
//	}
//	#define _simd_u16x8_not_enable() _simd_u16x64_not_enable()
//#else
//	#define _simd_u16x8_not(X) _simd_u16x8_combine(\
//		_simd_u16x4_not(_simd_u16x8_splitlo(X)),\
//		_simd_u16x4_not(_simd_u16x8_splithi(X)))
//	#define _simd_u16x8_not_enable() (_simd_u16x4_not_enable() && _simd_u16x8_combine_enable() && _simd_u16x8_splitlo_enable()  && _simd_u16x8_splithi_enable())
//#endif
//
//#ifndef _simd_u16x1_not_safe
//	#define _simd_u16x1_not_safe(X) (~X)
//	#define _simd_u16x1_not_(X) x1_not_safe(X)
//	#define _simd_u16x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_not_enabled() true
//#endif
//
//#define _simd_u16x16_not_safe(X)_simd_u16x16_combine_safe(\
//	_simd_u16x8_not_safe(_simd_u16x16_splitlo_safe(X)),\
//	_simd_u16x8_not_safe(_simd_u16x16_splithi_safe(X)))
//#ifdef _simd_u16x16_not_
//	#define _simd_u16x16_not(X) _simd_u16x16_not_(X)
//	#define _simd_u16x16_not_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_not_instruction_set>()
//#elif defined(_simd_u16x32_not_)
//	static ANVIL_STRONG_INLINE _simd_u16x16 ANVIL_SIMD_CALL _simd_u16x16_not(const register _simd_u16x16 x) {
//		union { _simd_u16x16 v1; _simd_u16x32 v2; };
//		v1 = x;
//		v2 = _simd_u16x32_not_(v2);
//		return v1;
//	}
//	#define _simd_u16x16_not_enable() _simd_u16x32_not_enable()
//#elif defined(_simd_u16x64_not_)
//	static ANVIL_STRONG_INLINE _simd_u16x16 ANVIL_SIMD_CALL _simd_u16x16_not(const register _simd_u16x16 x) {
//		union { _simd_u16x16 v1; _simd_u16x64 v2; };
//		v1 = x;
//		v2 = _simd_u16x64_not_(v2);
//		return v1;
//	}
//	#define _simd_u16x16_not_enable() _simd_u16x64_not_enable()
//#else
//	#define _simd_u16x16_not(X) _simd_u16x16_combine(\
//		_simd_u16x8_not(_simd_u16x16_splitlo(X)),\
//		_simd_u16x8_not(_simd_u16x16_splithi(X)))
//	#define _simd_u16x16_not_enable() (_simd_u16x8_not_enable() && _simd_u16x16_combine_enable() && _simd_u16x16_splitlo_enable()  && _simd_u16x16_splithi_enable())
//#endif
//
//#ifndef _simd_u16x1_not_safe
//	#define _simd_u16x1_not_safe(X) (~X)
//	#define _simd_u16x1_not_(X) x1_not_safe(X)
//	#define _simd_u16x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_not_enabled() true
//#endif
//
//#define _simd_u16x32_not_safe(X)_simd_u16x32_combine_safe(\
//	_simd_u16x16_not_safe(_simd_u16x32_splitlo_safe(X)),\
//	_simd_u16x16_not_safe(_simd_u16x32_splithi_safe(X)))
//#ifdef _simd_u16x32_not_
//	#define _simd_u16x32_not(X) _simd_u16x32_not_(X)
//	#define _simd_u16x32_not_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_not_instruction_set>()
//#elif defined(_simd_u16x64_not_)
//	static ANVIL_STRONG_INLINE _simd_u16x32 ANVIL_SIMD_CALL _simd_u16x32_not(const register _simd_u16x32 x) {
//		union { _simd_u16x32 v1; _simd_u16x64 v2; };
//		v1 = x;
//		v2 = _simd_u16x64_not_(v2);
//		return v1;
//	}
//	#define _simd_u16x32_not_enable() _simd_u16x64_not_enable()
//#else
//	#define _simd_u16x32_not(X) _simd_u16x32_combine(\
//		_simd_u16x16_not(_simd_u16x32_splitlo(X)),\
//		_simd_u16x16_not(_simd_u16x32_splithi(X)))
//	#define _simd_u16x32_not_enable() (_simd_u16x16_not_enable() && _simd_u16x32_combine_enable() && _simd_u16x32_splitlo_enable()  && _simd_u16x32_splithi_enable())
//#endif
//
//#ifndef _simd_u16x1_not_safe
//	#define _simd_u16x1_not_safe(X) (~X)
//	#define _simd_u16x1_not_(X) x1_not_safe(X)
//	#define _simd_u16x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_not_enabled() true
//#endif
//
//#define _simd_u16x64_not_safe(X)_simd_u16x64_combine_safe(\
//	_simd_u16x32_not_safe(_simd_u16x64_splitlo_safe(X)),\
//	_simd_u16x32_not_safe(_simd_u16x64_splithi_safe(X)))
//#ifdef _simd_u16x64_not_
//	#define _simd_u16x64_not(X) _simd_u16x64_not_(X)
//	#define _simd_u16x64_not_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_not_instruction_set>()
//#else
//	#define _simd_u16x64_not(X) _simd_u16x64_combine(\
//		_simd_u16x32_not(_simd_u16x64_splitlo(X)),\
//		_simd_u16x32_not(_simd_u16x64_splithi(X)))
//	#define _simd_u16x64_not_enable() (_simd_u16x32_not_enable() && _simd_u16x64_combine_enable() && _simd_u16x64_splitlo_enable()  && _simd_u16x64_splithi_enable())
//#endif
//
//// -- s8 --
//
//#ifndef _simd_s8x1_not_safe
//	#define _simd_s8x1_not_safe(X) (~X)
//	#define _simd_s8x1_not_(X) x1_not_safe(X)
//	#define _simd_s8x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_not_enabled() true
//#endif
//
//#define _simd_s8x2_not_safe(X)_simd_s8x2_combine_safe(\
//	_simd_s8x1_not_safe(_simd_s8x2_splitlo_safe(X)),\
//	_simd_s8x1_not_safe(_simd_s8x2_splithi_safe(X)))
//#ifdef _simd_s8x2_not_
//	#define _simd_s8x2_not(X) _simd_s8x2_not_(X)
//	#define _simd_s8x2_not_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_not_instruction_set>()
//#elif defined(_simd_s8x4_not_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_not(const register _simd_s8x2 x) {
//		union { _simd_s8x2 v1; _simd_s8x4 v2; };
//		v1 = x;
//		v2 = _simd_s8x4_not_(v2);
//		return v1;
//	}
//	#define _simd_s8x2_not_enable() _simd_s8x4_not_enable()
//#elif defined(_simd_s8x8_not_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_not(const register _simd_s8x2 x) {
//		union { _simd_s8x2 v1; _simd_s8x8 v2; };
//		v1 = x;
//		v2 = _simd_s8x8_not_(v2);
//		return v1;
//	}
//	#define _simd_s8x2_not_enable() _simd_s8x8_not_enable()
//#elif defined(_simd_s8x16_not_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_not(const register _simd_s8x2 x) {
//		union { _simd_s8x2 v1; _simd_s8x16 v2; };
//		v1 = x;
//		v2 = _simd_s8x16_not_(v2);
//		return v1;
//	}
//	#define _simd_s8x2_not_enable() _simd_s8x16_not_enable()
//#elif defined(_simd_s8x32_not_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_not(const register _simd_s8x2 x) {
//		union { _simd_s8x2 v1; _simd_s8x32 v2; };
//		v1 = x;
//		v2 = _simd_s8x32_not_(v2);
//		return v1;
//	}
//	#define _simd_s8x2_not_enable() _simd_s8x32_not_enable()
//#elif defined(_simd_s8x64_not_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_not(const register _simd_s8x2 x) {
//		union { _simd_s8x2 v1; _simd_s8x64 v2; };
//		v1 = x;
//		v2 = _simd_s8x64_not_(v2);
//		return v1;
//	}
//	#define _simd_s8x2_not_enable() _simd_s8x64_not_enable()
//#else
//	#define _simd_s8x2_not(X) _simd_s8x2_combine(\
//		_simd_s8x1_not(_simd_s8x2_splitlo(X)),\
//		_simd_s8x1_not(_simd_s8x2_splithi(X)))
//	#define _simd_s8x2_not_enable() (_simd_s8x1_not_enable() && _simd_s8x2_combine_enable() && _simd_s8x2_splitlo_enable()  && _simd_s8x2_splithi_enable())
//#endif
//
//#ifndef _simd_s8x1_not_safe
//	#define _simd_s8x1_not_safe(X) (~X)
//	#define _simd_s8x1_not_(X) x1_not_safe(X)
//	#define _simd_s8x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_not_enabled() true
//#endif
//
//#define _simd_s8x4_not_safe(X)_simd_s8x4_combine_safe(\
//	_simd_s8x2_not_safe(_simd_s8x4_splitlo_safe(X)),\
//	_simd_s8x2_not_safe(_simd_s8x4_splithi_safe(X)))
//#ifdef _simd_s8x4_not_
//	#define _simd_s8x4_not(X) _simd_s8x4_not_(X)
//	#define _simd_s8x4_not_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_not_instruction_set>()
//#elif defined(_simd_s8x8_not_)
//	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_not(const register _simd_s8x4 x) {
//		union { _simd_s8x4 v1; _simd_s8x8 v2; };
//		v1 = x;
//		v2 = _simd_s8x8_not_(v2);
//		return v1;
//	}
//	#define _simd_s8x4_not_enable() _simd_s8x8_not_enable()
//#elif defined(_simd_s8x16_not_)
//	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_not(const register _simd_s8x4 x) {
//		union { _simd_s8x4 v1; _simd_s8x16 v2; };
//		v1 = x;
//		v2 = _simd_s8x16_not_(v2);
//		return v1;
//	}
//	#define _simd_s8x4_not_enable() _simd_s8x16_not_enable()
//#elif defined(_simd_s8x32_not_)
//	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_not(const register _simd_s8x4 x) {
//		union { _simd_s8x4 v1; _simd_s8x32 v2; };
//		v1 = x;
//		v2 = _simd_s8x32_not_(v2);
//		return v1;
//	}
//	#define _simd_s8x4_not_enable() _simd_s8x32_not_enable()
//#elif defined(_simd_s8x64_not_)
//	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_not(const register _simd_s8x4 x) {
//		union { _simd_s8x4 v1; _simd_s8x64 v2; };
//		v1 = x;
//		v2 = _simd_s8x64_not_(v2);
//		return v1;
//	}
//	#define _simd_s8x4_not_enable() _simd_s8x64_not_enable()
//#else
//	#define _simd_s8x4_not(X) _simd_s8x4_combine(\
//		_simd_s8x2_not(_simd_s8x4_splitlo(X)),\
//		_simd_s8x2_not(_simd_s8x4_splithi(X)))
//	#define _simd_s8x4_not_enable() (_simd_s8x2_not_enable() && _simd_s8x4_combine_enable() && _simd_s8x4_splitlo_enable()  && _simd_s8x4_splithi_enable())
//#endif
//
//#ifndef _simd_s8x1_not_safe
//	#define _simd_s8x1_not_safe(X) (~X)
//	#define _simd_s8x1_not_(X) x1_not_safe(X)
//	#define _simd_s8x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_not_enabled() true
//#endif
//
//#define _simd_s8x8_not_safe(X)_simd_s8x8_combine_safe(\
//	_simd_s8x4_not_safe(_simd_s8x8_splitlo_safe(X)),\
//	_simd_s8x4_not_safe(_simd_s8x8_splithi_safe(X)))
//#ifdef _simd_s8x8_not_
//	#define _simd_s8x8_not(X) _simd_s8x8_not_(X)
//	#define _simd_s8x8_not_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_not_instruction_set>()
//#elif defined(_simd_s8x16_not_)
//	static ANVIL_STRONG_INLINE _simd_s8x8 ANVIL_SIMD_CALL _simd_s8x8_not(const register _simd_s8x8 x) {
//		union { _simd_s8x8 v1; _simd_s8x16 v2; };
//		v1 = x;
//		v2 = _simd_s8x16_not_(v2);
//		return v1;
//	}
//	#define _simd_s8x8_not_enable() _simd_s8x16_not_enable()
//#elif defined(_simd_s8x32_not_)
//	static ANVIL_STRONG_INLINE _simd_s8x8 ANVIL_SIMD_CALL _simd_s8x8_not(const register _simd_s8x8 x) {
//		union { _simd_s8x8 v1; _simd_s8x32 v2; };
//		v1 = x;
//		v2 = _simd_s8x32_not_(v2);
//		return v1;
//	}
//	#define _simd_s8x8_not_enable() _simd_s8x32_not_enable()
//#elif defined(_simd_s8x64_not_)
//	static ANVIL_STRONG_INLINE _simd_s8x8 ANVIL_SIMD_CALL _simd_s8x8_not(const register _simd_s8x8 x) {
//		union { _simd_s8x8 v1; _simd_s8x64 v2; };
//		v1 = x;
//		v2 = _simd_s8x64_not_(v2);
//		return v1;
//	}
//	#define _simd_s8x8_not_enable() _simd_s8x64_not_enable()
//#else
//	#define _simd_s8x8_not(X) _simd_s8x8_combine(\
//		_simd_s8x4_not(_simd_s8x8_splitlo(X)),\
//		_simd_s8x4_not(_simd_s8x8_splithi(X)))
//	#define _simd_s8x8_not_enable() (_simd_s8x4_not_enable() && _simd_s8x8_combine_enable() && _simd_s8x8_splitlo_enable()  && _simd_s8x8_splithi_enable())
//#endif
//
//#ifndef _simd_s8x1_not_safe
//	#define _simd_s8x1_not_safe(X) (~X)
//	#define _simd_s8x1_not_(X) x1_not_safe(X)
//	#define _simd_s8x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_not_enabled() true
//#endif
//
//#define _simd_s8x16_not_safe(X)_simd_s8x16_combine_safe(\
//	_simd_s8x8_not_safe(_simd_s8x16_splitlo_safe(X)),\
//	_simd_s8x8_not_safe(_simd_s8x16_splithi_safe(X)))
//#ifdef _simd_s8x16_not_
//	#define _simd_s8x16_not(X) _simd_s8x16_not_(X)
//	#define _simd_s8x16_not_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_not_instruction_set>()
//#elif defined(_simd_s8x32_not_)
//	static ANVIL_STRONG_INLINE _simd_s8x16 ANVIL_SIMD_CALL _simd_s8x16_not(const register _simd_s8x16 x) {
//		union { _simd_s8x16 v1; _simd_s8x32 v2; };
//		v1 = x;
//		v2 = _simd_s8x32_not_(v2);
//		return v1;
//	}
//	#define _simd_s8x16_not_enable() _simd_s8x32_not_enable()
//#elif defined(_simd_s8x64_not_)
//	static ANVIL_STRONG_INLINE _simd_s8x16 ANVIL_SIMD_CALL _simd_s8x16_not(const register _simd_s8x16 x) {
//		union { _simd_s8x16 v1; _simd_s8x64 v2; };
//		v1 = x;
//		v2 = _simd_s8x64_not_(v2);
//		return v1;
//	}
//	#define _simd_s8x16_not_enable() _simd_s8x64_not_enable()
//#else
//	#define _simd_s8x16_not(X) _simd_s8x16_combine(\
//		_simd_s8x8_not(_simd_s8x16_splitlo(X)),\
//		_simd_s8x8_not(_simd_s8x16_splithi(X)))
//	#define _simd_s8x16_not_enable() (_simd_s8x8_not_enable() && _simd_s8x16_combine_enable() && _simd_s8x16_splitlo_enable()  && _simd_s8x16_splithi_enable())
//#endif
//
//#ifndef _simd_s8x1_not_safe
//	#define _simd_s8x1_not_safe(X) (~X)
//	#define _simd_s8x1_not_(X) x1_not_safe(X)
//	#define _simd_s8x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_not_enabled() true
//#endif
//
//#define _simd_s8x32_not_safe(X)_simd_s8x32_combine_safe(\
//	_simd_s8x16_not_safe(_simd_s8x32_splitlo_safe(X)),\
//	_simd_s8x16_not_safe(_simd_s8x32_splithi_safe(X)))
//#ifdef _simd_s8x32_not_
//	#define _simd_s8x32_not(X) _simd_s8x32_not_(X)
//	#define _simd_s8x32_not_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_not_instruction_set>()
//#elif defined(_simd_s8x64_not_)
//	static ANVIL_STRONG_INLINE _simd_s8x32 ANVIL_SIMD_CALL _simd_s8x32_not(const register _simd_s8x32 x) {
//		union { _simd_s8x32 v1; _simd_s8x64 v2; };
//		v1 = x;
//		v2 = _simd_s8x64_not_(v2);
//		return v1;
//	}
//	#define _simd_s8x32_not_enable() _simd_s8x64_not_enable()
//#else
//	#define _simd_s8x32_not(X) _simd_s8x32_combine(\
//		_simd_s8x16_not(_simd_s8x32_splitlo(X)),\
//		_simd_s8x16_not(_simd_s8x32_splithi(X)))
//	#define _simd_s8x32_not_enable() (_simd_s8x16_not_enable() && _simd_s8x32_combine_enable() && _simd_s8x32_splitlo_enable()  && _simd_s8x32_splithi_enable())
//#endif
//
//#ifndef _simd_s8x1_not_safe
//	#define _simd_s8x1_not_safe(X) (~X)
//	#define _simd_s8x1_not_(X) x1_not_safe(X)
//	#define _simd_s8x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_not_enabled() true
//#endif
//
//#define _simd_s8x64_not_safe(X)_simd_s8x64_combine_safe(\
//	_simd_s8x32_not_safe(_simd_s8x64_splitlo_safe(X)),\
//	_simd_s8x32_not_safe(_simd_s8x64_splithi_safe(X)))
//#ifdef _simd_s8x64_not_
//	#define _simd_s8x64_not(X) _simd_s8x64_not_(X)
//	#define _simd_s8x64_not_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_not_instruction_set>()
//#else
//	#define _simd_s8x64_not(X) _simd_s8x64_combine(\
//		_simd_s8x32_not(_simd_s8x64_splitlo(X)),\
//		_simd_s8x32_not(_simd_s8x64_splithi(X)))
//	#define _simd_s8x64_not_enable() (_simd_s8x32_not_enable() && _simd_s8x64_combine_enable() && _simd_s8x64_splitlo_enable()  && _simd_s8x64_splithi_enable())
//#endif
//
//// -- u8 --
//
//#ifndef _simd_u8x1_not_safe
//	#define _simd_u8x1_not_safe(X) (~X)
//	#define _simd_u8x1_not_(X) x1_not_safe(X)
//	#define _simd_u8x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_not_enabled() true
//#endif
//
//#define _simd_u8x2_not_safe(X)_simd_u8x2_combine_safe(\
//	_simd_u8x1_not_safe(_simd_u8x2_splitlo_safe(X)),\
//	_simd_u8x1_not_safe(_simd_u8x2_splithi_safe(X)))
//#ifdef _simd_u8x2_not_
//	#define _simd_u8x2_not(X) _simd_u8x2_not_(X)
//	#define _simd_u8x2_not_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_not_instruction_set>()
//#elif defined(_simd_u8x4_not_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_not(const register _simd_u8x2 x) {
//		union { _simd_u8x2 v1; _simd_u8x4 v2; };
//		v1 = x;
//		v2 = _simd_u8x4_not_(v2);
//		return v1;
//	}
//	#define _simd_u8x2_not_enable() _simd_u8x4_not_enable()
//#elif defined(_simd_u8x8_not_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_not(const register _simd_u8x2 x) {
//		union { _simd_u8x2 v1; _simd_u8x8 v2; };
//		v1 = x;
//		v2 = _simd_u8x8_not_(v2);
//		return v1;
//	}
//	#define _simd_u8x2_not_enable() _simd_u8x8_not_enable()
//#elif defined(_simd_u8x16_not_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_not(const register _simd_u8x2 x) {
//		union { _simd_u8x2 v1; _simd_u8x16 v2; };
//		v1 = x;
//		v2 = _simd_u8x16_not_(v2);
//		return v1;
//	}
//	#define _simd_u8x2_not_enable() _simd_u8x16_not_enable()
//#elif defined(_simd_u8x32_not_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_not(const register _simd_u8x2 x) {
//		union { _simd_u8x2 v1; _simd_u8x32 v2; };
//		v1 = x;
//		v2 = _simd_u8x32_not_(v2);
//		return v1;
//	}
//	#define _simd_u8x2_not_enable() _simd_u8x32_not_enable()
//#elif defined(_simd_u8x64_not_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_not(const register _simd_u8x2 x) {
//		union { _simd_u8x2 v1; _simd_u8x64 v2; };
//		v1 = x;
//		v2 = _simd_u8x64_not_(v2);
//		return v1;
//	}
//	#define _simd_u8x2_not_enable() _simd_u8x64_not_enable()
//#else
//	#define _simd_u8x2_not(X) _simd_u8x2_combine(\
//		_simd_u8x1_not(_simd_u8x2_splitlo(X)),\
//		_simd_u8x1_not(_simd_u8x2_splithi(X)))
//	#define _simd_u8x2_not_enable() (_simd_u8x1_not_enable() && _simd_u8x2_combine_enable() && _simd_u8x2_splitlo_enable()  && _simd_u8x2_splithi_enable())
//#endif
//
//#ifndef _simd_u8x1_not_safe
//	#define _simd_u8x1_not_safe(X) (~X)
//	#define _simd_u8x1_not_(X) x1_not_safe(X)
//	#define _simd_u8x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_not_enabled() true
//#endif
//
//#define _simd_u8x4_not_safe(X)_simd_u8x4_combine_safe(\
//	_simd_u8x2_not_safe(_simd_u8x4_splitlo_safe(X)),\
//	_simd_u8x2_not_safe(_simd_u8x4_splithi_safe(X)))
//#ifdef _simd_u8x4_not_
//	#define _simd_u8x4_not(X) _simd_u8x4_not_(X)
//	#define _simd_u8x4_not_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_not_instruction_set>()
//#elif defined(_simd_u8x8_not_)
//	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_not(const register _simd_u8x4 x) {
//		union { _simd_u8x4 v1; _simd_u8x8 v2; };
//		v1 = x;
//		v2 = _simd_u8x8_not_(v2);
//		return v1;
//	}
//	#define _simd_u8x4_not_enable() _simd_u8x8_not_enable()
//#elif defined(_simd_u8x16_not_)
//	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_not(const register _simd_u8x4 x) {
//		union { _simd_u8x4 v1; _simd_u8x16 v2; };
//		v1 = x;
//		v2 = _simd_u8x16_not_(v2);
//		return v1;
//	}
//	#define _simd_u8x4_not_enable() _simd_u8x16_not_enable()
//#elif defined(_simd_u8x32_not_)
//	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_not(const register _simd_u8x4 x) {
//		union { _simd_u8x4 v1; _simd_u8x32 v2; };
//		v1 = x;
//		v2 = _simd_u8x32_not_(v2);
//		return v1;
//	}
//	#define _simd_u8x4_not_enable() _simd_u8x32_not_enable()
//#elif defined(_simd_u8x64_not_)
//	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_not(const register _simd_u8x4 x) {
//		union { _simd_u8x4 v1; _simd_u8x64 v2; };
//		v1 = x;
//		v2 = _simd_u8x64_not_(v2);
//		return v1;
//	}
//	#define _simd_u8x4_not_enable() _simd_u8x64_not_enable()
//#else
//	#define _simd_u8x4_not(X) _simd_u8x4_combine(\
//		_simd_u8x2_not(_simd_u8x4_splitlo(X)),\
//		_simd_u8x2_not(_simd_u8x4_splithi(X)))
//	#define _simd_u8x4_not_enable() (_simd_u8x2_not_enable() && _simd_u8x4_combine_enable() && _simd_u8x4_splitlo_enable()  && _simd_u8x4_splithi_enable())
//#endif
//
//#ifndef _simd_u8x1_not_safe
//	#define _simd_u8x1_not_safe(X) (~X)
//	#define _simd_u8x1_not_(X) x1_not_safe(X)
//	#define _simd_u8x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_not_enabled() true
//#endif
//
//#define _simd_u8x8_not_safe(X)_simd_u8x8_combine_safe(\
//	_simd_u8x4_not_safe(_simd_u8x8_splitlo_safe(X)),\
//	_simd_u8x4_not_safe(_simd_u8x8_splithi_safe(X)))
//#ifdef _simd_u8x8_not_
//	#define _simd_u8x8_not(X) _simd_u8x8_not_(X)
//	#define _simd_u8x8_not_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_not_instruction_set>()
//#elif defined(_simd_u8x16_not_)
//	static ANVIL_STRONG_INLINE _simd_u8x8 ANVIL_SIMD_CALL _simd_u8x8_not(const register _simd_u8x8 x) {
//		union { _simd_u8x8 v1; _simd_u8x16 v2; };
//		v1 = x;
//		v2 = _simd_u8x16_not_(v2);
//		return v1;
//	}
//	#define _simd_u8x8_not_enable() _simd_u8x16_not_enable()
//#elif defined(_simd_u8x32_not_)
//	static ANVIL_STRONG_INLINE _simd_u8x8 ANVIL_SIMD_CALL _simd_u8x8_not(const register _simd_u8x8 x) {
//		union { _simd_u8x8 v1; _simd_u8x32 v2; };
//		v1 = x;
//		v2 = _simd_u8x32_not_(v2);
//		return v1;
//	}
//	#define _simd_u8x8_not_enable() _simd_u8x32_not_enable()
//#elif defined(_simd_u8x64_not_)
//	static ANVIL_STRONG_INLINE _simd_u8x8 ANVIL_SIMD_CALL _simd_u8x8_not(const register _simd_u8x8 x) {
//		union { _simd_u8x8 v1; _simd_u8x64 v2; };
//		v1 = x;
//		v2 = _simd_u8x64_not_(v2);
//		return v1;
//	}
//	#define _simd_u8x8_not_enable() _simd_u8x64_not_enable()
//#else
//	#define _simd_u8x8_not(X) _simd_u8x8_combine(\
//		_simd_u8x4_not(_simd_u8x8_splitlo(X)),\
//		_simd_u8x4_not(_simd_u8x8_splithi(X)))
//	#define _simd_u8x8_not_enable() (_simd_u8x4_not_enable() && _simd_u8x8_combine_enable() && _simd_u8x8_splitlo_enable()  && _simd_u8x8_splithi_enable())
//#endif
//
//#ifndef _simd_u8x1_not_safe
//	#define _simd_u8x1_not_safe(X) (~X)
//	#define _simd_u8x1_not_(X) x1_not_safe(X)
//	#define _simd_u8x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_not_enabled() true
//#endif
//
//#define _simd_u8x16_not_safe(X)_simd_u8x16_combine_safe(\
//	_simd_u8x8_not_safe(_simd_u8x16_splitlo_safe(X)),\
//	_simd_u8x8_not_safe(_simd_u8x16_splithi_safe(X)))
//#ifdef _simd_u8x16_not_
//	#define _simd_u8x16_not(X) _simd_u8x16_not_(X)
//	#define _simd_u8x16_not_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_not_instruction_set>()
//#elif defined(_simd_u8x32_not_)
//	static ANVIL_STRONG_INLINE _simd_u8x16 ANVIL_SIMD_CALL _simd_u8x16_not(const register _simd_u8x16 x) {
//		union { _simd_u8x16 v1; _simd_u8x32 v2; };
//		v1 = x;
//		v2 = _simd_u8x32_not_(v2);
//		return v1;
//	}
//	#define _simd_u8x16_not_enable() _simd_u8x32_not_enable()
//#elif defined(_simd_u8x64_not_)
//	static ANVIL_STRONG_INLINE _simd_u8x16 ANVIL_SIMD_CALL _simd_u8x16_not(const register _simd_u8x16 x) {
//		union { _simd_u8x16 v1; _simd_u8x64 v2; };
//		v1 = x;
//		v2 = _simd_u8x64_not_(v2);
//		return v1;
//	}
//	#define _simd_u8x16_not_enable() _simd_u8x64_not_enable()
//#else
//	#define _simd_u8x16_not(X) _simd_u8x16_combine(\
//		_simd_u8x8_not(_simd_u8x16_splitlo(X)),\
//		_simd_u8x8_not(_simd_u8x16_splithi(X)))
//	#define _simd_u8x16_not_enable() (_simd_u8x8_not_enable() && _simd_u8x16_combine_enable() && _simd_u8x16_splitlo_enable()  && _simd_u8x16_splithi_enable())
//#endif
//
//#ifndef _simd_u8x1_not_safe
//	#define _simd_u8x1_not_safe(X) (~X)
//	#define _simd_u8x1_not_(X) x1_not_safe(X)
//	#define _simd_u8x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_not_enabled() true
//#endif
//
//#define _simd_u8x32_not_safe(X)_simd_u8x32_combine_safe(\
//	_simd_u8x16_not_safe(_simd_u8x32_splitlo_safe(X)),\
//	_simd_u8x16_not_safe(_simd_u8x32_splithi_safe(X)))
//#ifdef _simd_u8x32_not_
//	#define _simd_u8x32_not(X) _simd_u8x32_not_(X)
//	#define _simd_u8x32_not_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_not_instruction_set>()
//#elif defined(_simd_u8x64_not_)
//	static ANVIL_STRONG_INLINE _simd_u8x32 ANVIL_SIMD_CALL _simd_u8x32_not(const register _simd_u8x32 x) {
//		union { _simd_u8x32 v1; _simd_u8x64 v2; };
//		v1 = x;
//		v2 = _simd_u8x64_not_(v2);
//		return v1;
//	}
//	#define _simd_u8x32_not_enable() _simd_u8x64_not_enable()
//#else
//	#define _simd_u8x32_not(X) _simd_u8x32_combine(\
//		_simd_u8x16_not(_simd_u8x32_splitlo(X)),\
//		_simd_u8x16_not(_simd_u8x32_splithi(X)))
//	#define _simd_u8x32_not_enable() (_simd_u8x16_not_enable() && _simd_u8x32_combine_enable() && _simd_u8x32_splitlo_enable()  && _simd_u8x32_splithi_enable())
//#endif
//
//#ifndef _simd_u8x1_not_safe
//	#define _simd_u8x1_not_safe(X) (~X)
//	#define _simd_u8x1_not_(X) x1_not_safe(X)
//	#define _simd_u8x1_not_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_not_enabled() true
//#endif
//
//#define _simd_u8x64_not_safe(X)_simd_u8x64_combine_safe(\
//	_simd_u8x32_not_safe(_simd_u8x64_splitlo_safe(X)),\
//	_simd_u8x32_not_safe(_simd_u8x64_splithi_safe(X)))
//#ifdef _simd_u8x64_not_
//	#define _simd_u8x64_not(X) _simd_u8x64_not_(X)
//	#define _simd_u8x64_not_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_not_instruction_set>()
//#else
//	#define _simd_u8x64_not(X) _simd_u8x64_combine(\
//		_simd_u8x32_not(_simd_u8x64_splitlo(X)),\
//		_simd_u8x32_not(_simd_u8x64_splithi(X)))
//	#define _simd_u8x64_not_enable() (_simd_u8x32_not_enable() && _simd_u8x64_combine_enable() && _simd_u8x64_splitlo_enable()  && _simd_u8x64_splithi_enable())
//#endif
//
