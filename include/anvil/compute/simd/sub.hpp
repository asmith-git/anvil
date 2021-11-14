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


#ifndef ANVIL_COMPUTE_SIMD_SUB_HPP
#define ANVIL_COMPUTE_SIMD_SUB_HPP

#include "anvil/core/CpuRuntime.hpp"
#include "anvil/compute/Vector.hpp"

namespace anvil { namespace detail {
	template<class T>
	struct VectorSub;

	// Scalar types

	template<>
	struct VectorSub<uint8_t> {
		typedef uint8_t type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			return a - b;
		}
	};

	template<>
	struct VectorSub<uint16_t> {
		typedef uint16_t type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			return a - b;
		}
	};

	template<>
	struct VectorSub<uint32_t> {
		typedef uint32_t type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			return a - b;
		}
	};

	template<>
	struct VectorSub<uint64_t> {
		typedef uint64_t type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			return a - b;
		}
	};

	template<>
	struct VectorSub<int8_t> {
		typedef int8_t type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			return a - b;
		}
	};

	template<>
	struct VectorSub<int16_t> {
		typedef int16_t type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			return a - b;
		}
	};

	template<>
	struct VectorSub<int32_t> {
		typedef int32_t type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			return a - b;
		}
	};

	template<>
	struct VectorSub<int64_t> {
		typedef int64_t type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			return a - b;
		}
	};

	template<>
	struct VectorSub<float32_t> {
		typedef float32_t type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			return a - b;
		}
	};

	template<>
	struct VectorSub<float64_t> {
		typedef float64_t type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			return a - b;
		}
	};

	// Optimised vectors


#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64

	template<>
	struct VectorSub<detail::BasicVector<float32_t, 4u>> {
		typedef detail::BasicVector<float32_t, 4u> type;

		static ANVIL_STRONG_INLINE type Execute_SSE(type a, const type& b) throw() {
			a.native = _mm_sub_ps(a.native, b.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(const type& a, const type& b) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_SSE) != 0ull) {
				return Execute_SSE(a, b);
			} else {
				a.lower_half = VectorSub<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorSub<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
				return a;
			}
		}
	};

	template<>
	struct VectorSub<detail::BasicVector<float32_t, 8u>> {
		typedef detail::BasicVector<float32_t, 8u> type;

		static ANVIL_STRONG_INLINE type Execute_AVX(type a, const type& b) throw() {
			a.native = _mm256_sub_ps(a.native, b.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, const type& b) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_AVX) != 0ull) {
				return Execute_AVX(a, b);
			} else {
				a.lower_half = VectorSub<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorSub<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
				return a;
			}
		}
	};

	template<>
	struct VectorSub<detail::BasicVector<float32_t, 16u>> {
		typedef detail::BasicVector<float32_t, 16u> type;

		static ANVIL_STRONG_INLINE type Execute_AVX512F(type a, const type& b) throw() {
			a.native = _mm512_sub_ps(a.native, b.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, const type& b) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_AVX512F) != 0ull) {
				return Execute_AVX512F(a, b);
			} else {
				a.lower_half = VectorSub<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorSub<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
				return a;
			}
		}
	};

	template<>
	struct VectorSub<detail::BasicVector<float64_t, 2u>> {
		typedef detail::BasicVector<float64_t, 2u> type;

		static ANVIL_STRONG_INLINE type Execute_SSE2(type a, const type& b) throw() {
			a.native = _mm_sub_pd(a.native, b.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(const type& a, const type& b) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_SSE2) != 0ull) {
				return Execute_SSE2(a, b);
			} else {
				a.lower_half = VectorSub<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorSub<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
				return a;
			}
		}
	};

	template<>
	struct VectorSub<detail::BasicVector<float64_t, 4u>> {
		typedef detail::BasicVector<float64_t, 4u> type;

		static ANVIL_STRONG_INLINE type Execute_AVX(type a, const type& b) throw() {
			a.native = _mm256_sub_pd(a.native, b.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, const type& b) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_AVX) != 0ull) {
				return Execute_AVX(a, b);
			} else {
				a.lower_half = VectorSub<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorSub<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
				return a;
			}
		}
	};

	template<>
	struct VectorSub<detail::BasicVector<float64_t, 8u>> {
		typedef detail::BasicVector<float64_t, 8u> type;

		static ANVIL_STRONG_INLINE type Execute_AVX512F(type a, const type& b) throw() {
			a.native = _mm512_sub_pd(a.native, b.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, const type& b) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_AVX512F) != 0ull) {
				return Execute_AVX512F(a, b);
			} else {
				a.lower_half = VectorSub<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorSub<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
				return a;
			}
		}
	};

	template<>
	struct VectorSub<detail::BasicVector<int8_t, 16u>> {
		typedef detail::BasicVector<int8_t, 16u> type;

		static ANVIL_STRONG_INLINE type Execute_SSE2(type a, const type& b) throw() {
			a.native = _mm_subs_epi8(a.native, b.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(const type& a, const type& b) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_SSE2) != 0ull) {
				return Execute_SSE2(a, b);
			} else {
				a.lower_half = VectorSub<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorSub<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
				return a;
			}
		}
	};

	template<>
	struct VectorSub<detail::BasicVector<int8_t, 32u>> {
		typedef detail::BasicVector<int8_t, 32u> type;

		static ANVIL_STRONG_INLINE type Execute_AVX2(type a, const type& b) throw() {
			a.native = _mm256_subs_epi8(a.native, b.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(const type& a, const type& b) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_AVX2) != 0ull) {
				return Execute_AVX2(a, b);
			} else {
				a.lower_half = VectorSub<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorSub<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
				return a;
			}
		}
	};

	template<>
	struct VectorSub<detail::BasicVector<int8_t, 64u>> {
		typedef detail::BasicVector<int8_t, 64u> type;

		static ANVIL_STRONG_INLINE type Execute_AVX512BW(type a, const type& b) throw() {
			a.native = _mm512_subs_epi8(a.native, b.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(const type& a, const type& b) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_AVX512BW) != 0ull) {
				return Execute_AVX512BW(a, b);
			} else {
				a.lower_half = VectorSub<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorSub<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
				return a;
			}
		}
	};

	template<>
	struct VectorSub<detail::BasicVector<int16_t, 8u>> {
		typedef detail::BasicVector<int16_t, 8u> type;

		static ANVIL_STRONG_INLINE type Execute_SSE2(type a, const type& b) throw() {
			a.native = _mm_subs_epi16(a.native, b.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(const type& a, const type& b) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_SSE2) != 0ull) {
				return Execute_SSE2(a, b);
			} else {
				a.lower_half = VectorSub<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorSub<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
				return a;
			}
		}
	};

	template<>
	struct VectorSub<detail::BasicVector<int16_t, 16u>> {
		typedef detail::BasicVector<int16_t, 16u> type;

		static ANVIL_STRONG_INLINE type Execute_AVX2(type a, const type& b) throw() {
			a.native = _mm256_subs_epi16(a.native, b.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(const type& a, const type& b) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_AVX2) != 0ull) {
				return Execute_AVX2(a, b);
			} else {
				a.lower_half = VectorSub<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorSub<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
				return a;
			}
		}
	};

	template<>
	struct VectorSub<detail::BasicVector<int16_t, 32u>> {
		typedef detail::BasicVector<int16_t, 32u> type;

		static ANVIL_STRONG_INLINE type Execute_AVX512BW(type a, const type& b) throw() {
			a.native = _mm512_subs_epi16(a.native, b.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(const type& a, const type& b) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_AVX512BW) != 0ull) {
				return Execute_AVX512BW(a, b);
			} else {
				a.lower_half = VectorSub<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorSub<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
				return a;
			}
		}
	};

	template<>
	struct VectorSub<detail::BasicVector<int32_t, 4u>> {
		typedef detail::BasicVector<int32_t, 4u> type;

		static ANVIL_STRONG_INLINE type Execute_SSE2(type a, const type& b) throw() {
			a.native = _mm_sub_epi32(a.native, b.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(const type& a, const type& b) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_SSE2) != 0ull) {
				return Execute_SSE2(a, b);
			} else {
				a.lower_half = VectorSub<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorSub<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
				return a;
			}
		}
	};

	template<>
	struct VectorSub<detail::BasicVector<int32_t, 8u>> {
		typedef detail::BasicVector<int32_t, 8u> type;

		static ANVIL_STRONG_INLINE type Execute_AVX2(type a, const type& b) throw() {
			a.native = _mm256_sub_epi32(a.native, b.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(const type& a, const type& b) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_AVX2) != 0ull) {
				return Execute_AVX2(a, b);
			} else {
				a.lower_half = VectorSub<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorSub<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
				return a;
			}
		}
	};

	template<>
	struct VectorSub<detail::BasicVector<int32_t, 16u>> {
		typedef detail::BasicVector<int32_t, 16u> type;

		static ANVIL_STRONG_INLINE type Execute_AVX512BW(type a, const type& b) throw() {
			a.native = _mm512_sub_epi32(a.native, b.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(const type& a, const type& b) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_AVX512BW) != 0ull) {
				return Execute_AVX512BW(a, b);
			} else {
				a.lower_half = VectorSub<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorSub<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
				return a;
			}
		}
	};

#endif

	// Unoptimised vectors

	template<class T, size_t size>
	struct VectorSub<detail::BasicVector<T, size>> {
		typedef detail::BasicVector<T, size> type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, const type& b) throw() {
			a.lower_half = VectorSub<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
			a.upper_half = VectorSub<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
			return a;
		}
	};
}}

namespace anvil {

	template<uint64_t instruction_set = ASM_MINIMUM, class T>
	static inline T VectorSub(const T& a, const T& b) throw() {
		return detail::VectorSub<T>::Execute<instruction_set>(a, b);
	}


	template<class T, size_t size>
	ANVIL_STRONG_INLINE detail::BasicVector<T, size> operator-(const detail::BasicVector<T, size>& a, const detail::BasicVector<T, size>& b) throw() {
		return anvil::VectorSub<ASM_MINIMUM, detail::BasicVector<T, size>>(a, b);
	}
}

#endif

//// -- f64 --
//
//#ifndef _simd_f64x1_sub_safe
//	#define _simd_f64x1_sub_safe(X,Y) (X - Y)
//	#define _simd_f64x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_f64x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_sub_enabled() true
//#endif
//
//#define _simd_f64x2_sub_safe(X,Y)_simd_f64x2_combine_safe(\
//	_simd_f64x1_sub_safe(_simd_f64x2_splitlo_safe(X), _simd_ f64x2_splitlo_safe(Y)),\
//	_simd_f64x1_sub_safe(_simd_f64x2_splithi_safe(X), _simd_ f64x2_splithi_safe(Y)))
//#ifdef _simd_f64x2_sub_
//	#define _simd_f64x2_sub(X,Y) _simd_f64x2_sub_(X, Y)
//	#define _simd_f64x2_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_sub_instruction_set>()
//#elif defined(_simd_f64x4_sub_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_sub(const register _simd_f64x2 x, const register _simd_f64x2 y) {
//		union SIMDUnion { _simd_f64x2 v1; _simd_f64x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x4_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x2_sub_enable() _simd_f64x4_sub_enable()
//#elif defined(_simd_f64x8_sub_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_sub(const register _simd_f64x2 x, const register _simd_f64x2 y) {
//		union SIMDUnion { _simd_f64x2 v1; _simd_f64x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x8_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x2_sub_enable() _simd_f64x8_sub_enable()
//#elif defined(_simd_f64x16_sub_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_sub(const register _simd_f64x2 x, const register _simd_f64x2 y) {
//		union SIMDUnion { _simd_f64x2 v1; _simd_f64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x16_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x2_sub_enable() _simd_f64x16_sub_enable()
//#elif defined(_simd_f64x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_sub(const register _simd_f64x2 x, const register _simd_f64x2 y) {
//		union SIMDUnion { _simd_f64x2 v1; _simd_f64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x2_sub_enable() _simd_f64x32_sub_enable()
//#elif defined(_simd_f64x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_sub(const register _simd_f64x2 x, const register _simd_f64x2 y) {
//		union SIMDUnion { _simd_f64x2 v1; _simd_f64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x2_sub_enable() _simd_f64x64_sub_enable()
//#else
//	#define _simd_f64x2_sub(X,Y) _simd_f64x2_combine(\
//		_simd_f64x1_sub(_simd_f64x2_splitlo(X), _simd_f64x2_splitlo(Y)),\
//		_simd_f64x1_sub(_simd_f64x2_splithi(X), _simd_f64x2_splithi(Y)))
//	#define _simd_f64x2_sub_enable() (_simd_f64x1_sub_enable() && _simd_f64x2_combine_enable() && _simd_f64x2_splitlo_enable()  && _simd_f64x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x2_sub_) && ! defined(_simd_f64x2_sub_scalar_)
//	#define _simd_f64x2_sub_scalar_(X,Y) _simd_f64x2_sub_(X,_simd_f64x2_fill_scalar_(Y))
//	#define _simd_f64x2_sub_scalar_instruction_set _simd_f64x2_sub_instruction_set
//#endif
//#ifdef _simd_f64x2_sub_scalar_
//	#define _simd_f64x2_sub_scalar(X,Y) _simd_f64x2_sub_scalar_(X,Y)
//	#define _simd_f64x2_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_sub_scalar_instruction_set>()
//#else
//	#define _simd_f64x2_sub_scalar(X,Y) _simd_f64x2_sub_safe(X,_simd_f64x2_fill_scalar_safe(Y))
//	#define _simd_f64x2_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_f64x1_sub_safe
//	#define _simd_f64x1_sub_safe(X,Y) (X - Y)
//	#define _simd_f64x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_f64x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_sub_enabled() true
//#endif
//
//#define _simd_f64x4_sub_safe(X,Y)_simd_f64x4_combine_safe(\
//	_simd_f64x2_sub_safe(_simd_f64x4_splitlo_safe(X), _simd_ f64x4_splitlo_safe(Y)),\
//	_simd_f64x2_sub_safe(_simd_f64x4_splithi_safe(X), _simd_ f64x4_splithi_safe(Y)))
//#ifdef _simd_f64x4_sub_
//	#define _simd_f64x4_sub(X,Y) _simd_f64x4_sub_(X, Y)
//	#define _simd_f64x4_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_sub_instruction_set>()
//#elif defined(_simd_f64x8_sub_)
//	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_sub(const register _simd_f64x4 x, const register _simd_f64x4 y) {
//		union SIMDUnion { _simd_f64x4 v1; _simd_f64x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x8_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x4_sub_enable() _simd_f64x8_sub_enable()
//#elif defined(_simd_f64x16_sub_)
//	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_sub(const register _simd_f64x4 x, const register _simd_f64x4 y) {
//		union SIMDUnion { _simd_f64x4 v1; _simd_f64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x16_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x4_sub_enable() _simd_f64x16_sub_enable()
//#elif defined(_simd_f64x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_sub(const register _simd_f64x4 x, const register _simd_f64x4 y) {
//		union SIMDUnion { _simd_f64x4 v1; _simd_f64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x4_sub_enable() _simd_f64x32_sub_enable()
//#elif defined(_simd_f64x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_sub(const register _simd_f64x4 x, const register _simd_f64x4 y) {
//		union SIMDUnion { _simd_f64x4 v1; _simd_f64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x4_sub_enable() _simd_f64x64_sub_enable()
//#else
//	#define _simd_f64x4_sub(X,Y) _simd_f64x4_combine(\
//		_simd_f64x2_sub(_simd_f64x4_splitlo(X), _simd_f64x4_splitlo(Y)),\
//		_simd_f64x2_sub(_simd_f64x4_splithi(X), _simd_f64x4_splithi(Y)))
//	#define _simd_f64x4_sub_enable() (_simd_f64x2_sub_enable() && _simd_f64x4_combine_enable() && _simd_f64x4_splitlo_enable()  && _simd_f64x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x4_sub_) && ! defined(_simd_f64x4_sub_scalar_)
//	#define _simd_f64x4_sub_scalar_(X,Y) _simd_f64x4_sub_(X,_simd_f64x4_fill_scalar_(Y))
//	#define _simd_f64x4_sub_scalar_instruction_set _simd_f64x4_sub_instruction_set
//#endif
//#ifdef _simd_f64x4_sub_scalar_
//	#define _simd_f64x4_sub_scalar(X,Y) _simd_f64x4_sub_scalar_(X,Y)
//	#define _simd_f64x4_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_sub_scalar_instruction_set>()
//#else
//	#define _simd_f64x4_sub_scalar(X,Y) _simd_f64x4_sub_safe(X,_simd_f64x4_fill_scalar_safe(Y))
//	#define _simd_f64x4_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_f64x1_sub_safe
//	#define _simd_f64x1_sub_safe(X,Y) (X - Y)
//	#define _simd_f64x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_f64x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_sub_enabled() true
//#endif
//
//#define _simd_f64x8_sub_safe(X,Y)_simd_f64x8_combine_safe(\
//	_simd_f64x4_sub_safe(_simd_f64x8_splitlo_safe(X), _simd_ f64x8_splitlo_safe(Y)),\
//	_simd_f64x4_sub_safe(_simd_f64x8_splithi_safe(X), _simd_ f64x8_splithi_safe(Y)))
//#ifdef _simd_f64x8_sub_
//	#define _simd_f64x8_sub(X,Y) _simd_f64x8_sub_(X, Y)
//	#define _simd_f64x8_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_sub_instruction_set>()
//#elif defined(_simd_f64x16_sub_)
//	static ANVIL_STRONG_INLINE _simd_f64x8 ANVIL_SIMD_CALL _simd_f64x8_sub(const register _simd_f64x8 x, const register _simd_f64x8 y) {
//		union SIMDUnion { _simd_f64x8 v1; _simd_f64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x16_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x8_sub_enable() _simd_f64x16_sub_enable()
//#elif defined(_simd_f64x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_f64x8 ANVIL_SIMD_CALL _simd_f64x8_sub(const register _simd_f64x8 x, const register _simd_f64x8 y) {
//		union SIMDUnion { _simd_f64x8 v1; _simd_f64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x8_sub_enable() _simd_f64x32_sub_enable()
//#elif defined(_simd_f64x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_f64x8 ANVIL_SIMD_CALL _simd_f64x8_sub(const register _simd_f64x8 x, const register _simd_f64x8 y) {
//		union SIMDUnion { _simd_f64x8 v1; _simd_f64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x8_sub_enable() _simd_f64x64_sub_enable()
//#else
//	#define _simd_f64x8_sub(X,Y) _simd_f64x8_combine(\
//		_simd_f64x4_sub(_simd_f64x8_splitlo(X), _simd_f64x8_splitlo(Y)),\
//		_simd_f64x4_sub(_simd_f64x8_splithi(X), _simd_f64x8_splithi(Y)))
//	#define _simd_f64x8_sub_enable() (_simd_f64x4_sub_enable() && _simd_f64x8_combine_enable() && _simd_f64x8_splitlo_enable()  && _simd_f64x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x8_sub_) && ! defined(_simd_f64x8_sub_scalar_)
//	#define _simd_f64x8_sub_scalar_(X,Y) _simd_f64x8_sub_(X,_simd_f64x8_fill_scalar_(Y))
//	#define _simd_f64x8_sub_scalar_instruction_set _simd_f64x8_sub_instruction_set
//#endif
//#ifdef _simd_f64x8_sub_scalar_
//	#define _simd_f64x8_sub_scalar(X,Y) _simd_f64x8_sub_scalar_(X,Y)
//	#define _simd_f64x8_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_sub_scalar_instruction_set>()
//#else
//	#define _simd_f64x8_sub_scalar(X,Y) _simd_f64x8_sub_safe(X,_simd_f64x8_fill_scalar_safe(Y))
//	#define _simd_f64x8_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_f64x1_sub_safe
//	#define _simd_f64x1_sub_safe(X,Y) (X - Y)
//	#define _simd_f64x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_f64x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_sub_enabled() true
//#endif
//
//#define _simd_f64x16_sub_safe(X,Y)_simd_f64x16_combine_safe(\
//	_simd_f64x8_sub_safe(_simd_f64x16_splitlo_safe(X), _simd_ f64x16_splitlo_safe(Y)),\
//	_simd_f64x8_sub_safe(_simd_f64x16_splithi_safe(X), _simd_ f64x16_splithi_safe(Y)))
//#ifdef _simd_f64x16_sub_
//	#define _simd_f64x16_sub(X,Y) _simd_f64x16_sub_(X, Y)
//	#define _simd_f64x16_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_sub_instruction_set>()
//#elif defined(_simd_f64x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_f64x16 ANVIL_SIMD_CALL _simd_f64x16_sub(const register _simd_f64x16 x, const register _simd_f64x16 y) {
//		union SIMDUnion { _simd_f64x16 v1; _simd_f64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x16_sub_enable() _simd_f64x32_sub_enable()
//#elif defined(_simd_f64x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_f64x16 ANVIL_SIMD_CALL _simd_f64x16_sub(const register _simd_f64x16 x, const register _simd_f64x16 y) {
//		union SIMDUnion { _simd_f64x16 v1; _simd_f64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x16_sub_enable() _simd_f64x64_sub_enable()
//#else
//	#define _simd_f64x16_sub(X,Y) _simd_f64x16_combine(\
//		_simd_f64x8_sub(_simd_f64x16_splitlo(X), _simd_f64x16_splitlo(Y)),\
//		_simd_f64x8_sub(_simd_f64x16_splithi(X), _simd_f64x16_splithi(Y)))
//	#define _simd_f64x16_sub_enable() (_simd_f64x8_sub_enable() && _simd_f64x16_combine_enable() && _simd_f64x16_splitlo_enable()  && _simd_f64x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x16_sub_) && ! defined(_simd_f64x16_sub_scalar_)
//	#define _simd_f64x16_sub_scalar_(X,Y) _simd_f64x16_sub_(X,_simd_f64x16_fill_scalar_(Y))
//	#define _simd_f64x16_sub_scalar_instruction_set _simd_f64x16_sub_instruction_set
//#endif
//#ifdef _simd_f64x16_sub_scalar_
//	#define _simd_f64x16_sub_scalar(X,Y) _simd_f64x16_sub_scalar_(X,Y)
//	#define _simd_f64x16_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_sub_scalar_instruction_set>()
//#else
//	#define _simd_f64x16_sub_scalar(X,Y) _simd_f64x16_sub_safe(X,_simd_f64x16_fill_scalar_safe(Y))
//	#define _simd_f64x16_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_f64x1_sub_safe
//	#define _simd_f64x1_sub_safe(X,Y) (X - Y)
//	#define _simd_f64x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_f64x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_sub_enabled() true
//#endif
//
//#define _simd_f64x32_sub_safe(X,Y)_simd_f64x32_combine_safe(\
//	_simd_f64x16_sub_safe(_simd_f64x32_splitlo_safe(X), _simd_ f64x32_splitlo_safe(Y)),\
//	_simd_f64x16_sub_safe(_simd_f64x32_splithi_safe(X), _simd_ f64x32_splithi_safe(Y)))
//#ifdef _simd_f64x32_sub_
//	#define _simd_f64x32_sub(X,Y) _simd_f64x32_sub_(X, Y)
//	#define _simd_f64x32_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_sub_instruction_set>()
//#elif defined(_simd_f64x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_f64x32 ANVIL_SIMD_CALL _simd_f64x32_sub(const register _simd_f64x32 x, const register _simd_f64x32 y) {
//		union SIMDUnion { _simd_f64x32 v1; _simd_f64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x32_sub_enable() _simd_f64x64_sub_enable()
//#else
//	#define _simd_f64x32_sub(X,Y) _simd_f64x32_combine(\
//		_simd_f64x16_sub(_simd_f64x32_splitlo(X), _simd_f64x32_splitlo(Y)),\
//		_simd_f64x16_sub(_simd_f64x32_splithi(X), _simd_f64x32_splithi(Y)))
//	#define _simd_f64x32_sub_enable() (_simd_f64x16_sub_enable() && _simd_f64x32_combine_enable() && _simd_f64x32_splitlo_enable()  && _simd_f64x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x32_sub_) && ! defined(_simd_f64x32_sub_scalar_)
//	#define _simd_f64x32_sub_scalar_(X,Y) _simd_f64x32_sub_(X,_simd_f64x32_fill_scalar_(Y))
//	#define _simd_f64x32_sub_scalar_instruction_set _simd_f64x32_sub_instruction_set
//#endif
//#ifdef _simd_f64x32_sub_scalar_
//	#define _simd_f64x32_sub_scalar(X,Y) _simd_f64x32_sub_scalar_(X,Y)
//	#define _simd_f64x32_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_sub_scalar_instruction_set>()
//#else
//	#define _simd_f64x32_sub_scalar(X,Y) _simd_f64x32_sub_safe(X,_simd_f64x32_fill_scalar_safe(Y))
//	#define _simd_f64x32_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_f64x1_sub_safe
//	#define _simd_f64x1_sub_safe(X,Y) (X - Y)
//	#define _simd_f64x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_f64x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_sub_enabled() true
//#endif
//
//#define _simd_f64x64_sub_safe(X,Y)_simd_f64x64_combine_safe(\
//	_simd_f64x32_sub_safe(_simd_f64x64_splitlo_safe(X), _simd_ f64x64_splitlo_safe(Y)),\
//	_simd_f64x32_sub_safe(_simd_f64x64_splithi_safe(X), _simd_ f64x64_splithi_safe(Y)))
//#ifdef _simd_f64x64_sub_
//	#define _simd_f64x64_sub(X,Y) _simd_f64x64_sub_(X, Y)
//	#define _simd_f64x64_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_sub_instruction_set>()
//#else
//	#define _simd_f64x64_sub(X,Y) _simd_f64x64_combine(\
//		_simd_f64x32_sub(_simd_f64x64_splitlo(X), _simd_f64x64_splitlo(Y)),\
//		_simd_f64x32_sub(_simd_f64x64_splithi(X), _simd_f64x64_splithi(Y)))
//	#define _simd_f64x64_sub_enable() (_simd_f64x32_sub_enable() && _simd_f64x64_combine_enable() && _simd_f64x64_splitlo_enable()  && _simd_f64x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x64_sub_) && ! defined(_simd_f64x64_sub_scalar_)
//	#define _simd_f64x64_sub_scalar_(X,Y) _simd_f64x64_sub_(X,_simd_f64x64_fill_scalar_(Y))
//	#define _simd_f64x64_sub_scalar_instruction_set _simd_f64x64_sub_instruction_set
//#endif
//#ifdef _simd_f64x64_sub_scalar_
//	#define _simd_f64x64_sub_scalar(X,Y) _simd_f64x64_sub_scalar_(X,Y)
//	#define _simd_f64x64_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_sub_scalar_instruction_set>()
//#else
//	#define _simd_f64x64_sub_scalar(X,Y) _simd_f64x64_sub_safe(X,_simd_f64x64_fill_scalar_safe(Y))
//	#define _simd_f64x64_sub_scalar_enabled() true
//#endif
//
//// -- f32 --
//
//#ifndef _simd_f32x1_sub_safe
//	#define _simd_f32x1_sub_safe(X,Y) (X - Y)
//	#define _simd_f32x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_f32x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_sub_enabled() true
//#endif
//
//#define _simd_f32x2_sub_safe(X,Y)_simd_f32x2_combine_safe(\
//	_simd_f32x1_sub_safe(_simd_f32x2_splitlo_safe(X), _simd_ f32x2_splitlo_safe(Y)),\
//	_simd_f32x1_sub_safe(_simd_f32x2_splithi_safe(X), _simd_ f32x2_splithi_safe(Y)))
//#ifdef _simd_f32x2_sub_
//	#define _simd_f32x2_sub(X,Y) _simd_f32x2_sub_(X, Y)
//	#define _simd_f32x2_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_sub_instruction_set>()
//#elif defined(_simd_f32x4_sub_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_sub(const register _simd_f32x2 x, const register _simd_f32x2 y) {
//		union SIMDUnion { _simd_f32x2 v1; _simd_f32x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x4_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x2_sub_enable() _simd_f32x4_sub_enable()
//#elif defined(_simd_f32x8_sub_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_sub(const register _simd_f32x2 x, const register _simd_f32x2 y) {
//		union SIMDUnion { _simd_f32x2 v1; _simd_f32x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x8_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x2_sub_enable() _simd_f32x8_sub_enable()
//#elif defined(_simd_f32x16_sub_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_sub(const register _simd_f32x2 x, const register _simd_f32x2 y) {
//		union SIMDUnion { _simd_f32x2 v1; _simd_f32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x16_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x2_sub_enable() _simd_f32x16_sub_enable()
//#elif defined(_simd_f32x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_sub(const register _simd_f32x2 x, const register _simd_f32x2 y) {
//		union SIMDUnion { _simd_f32x2 v1; _simd_f32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x2_sub_enable() _simd_f32x32_sub_enable()
//#elif defined(_simd_f32x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_sub(const register _simd_f32x2 x, const register _simd_f32x2 y) {
//		union SIMDUnion { _simd_f32x2 v1; _simd_f32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x2_sub_enable() _simd_f32x64_sub_enable()
//#else
//	#define _simd_f32x2_sub(X,Y) _simd_f32x2_combine(\
//		_simd_f32x1_sub(_simd_f32x2_splitlo(X), _simd_f32x2_splitlo(Y)),\
//		_simd_f32x1_sub(_simd_f32x2_splithi(X), _simd_f32x2_splithi(Y)))
//	#define _simd_f32x2_sub_enable() (_simd_f32x1_sub_enable() && _simd_f32x2_combine_enable() && _simd_f32x2_splitlo_enable()  && _simd_f32x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x2_sub_) && ! defined(_simd_f32x2_sub_scalar_)
//	#define _simd_f32x2_sub_scalar_(X,Y) _simd_f32x2_sub_(X,_simd_f32x2_fill_scalar_(Y))
//	#define _simd_f32x2_sub_scalar_instruction_set _simd_f32x2_sub_instruction_set
//#endif
//#ifdef _simd_f32x2_sub_scalar_
//	#define _simd_f32x2_sub_scalar(X,Y) _simd_f32x2_sub_scalar_(X,Y)
//	#define _simd_f32x2_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_sub_scalar_instruction_set>()
//#else
//	#define _simd_f32x2_sub_scalar(X,Y) _simd_f32x2_sub_safe(X,_simd_f32x2_fill_scalar_safe(Y))
//	#define _simd_f32x2_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_f32x1_sub_safe
//	#define _simd_f32x1_sub_safe(X,Y) (X - Y)
//	#define _simd_f32x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_f32x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_sub_enabled() true
//#endif
//
//#define _simd_f32x4_sub_safe(X,Y)_simd_f32x4_combine_safe(\
//	_simd_f32x2_sub_safe(_simd_f32x4_splitlo_safe(X), _simd_ f32x4_splitlo_safe(Y)),\
//	_simd_f32x2_sub_safe(_simd_f32x4_splithi_safe(X), _simd_ f32x4_splithi_safe(Y)))
//#ifdef _simd_f32x4_sub_
//	#define _simd_f32x4_sub(X,Y) _simd_f32x4_sub_(X, Y)
//	#define _simd_f32x4_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_sub_instruction_set>()
//#elif defined(_simd_f32x8_sub_)
//	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_sub(const register _simd_f32x4 x, const register _simd_f32x4 y) {
//		union SIMDUnion { _simd_f32x4 v1; _simd_f32x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x8_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x4_sub_enable() _simd_f32x8_sub_enable()
//#elif defined(_simd_f32x16_sub_)
//	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_sub(const register _simd_f32x4 x, const register _simd_f32x4 y) {
//		union SIMDUnion { _simd_f32x4 v1; _simd_f32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x16_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x4_sub_enable() _simd_f32x16_sub_enable()
//#elif defined(_simd_f32x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_sub(const register _simd_f32x4 x, const register _simd_f32x4 y) {
//		union SIMDUnion { _simd_f32x4 v1; _simd_f32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x4_sub_enable() _simd_f32x32_sub_enable()
//#elif defined(_simd_f32x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_sub(const register _simd_f32x4 x, const register _simd_f32x4 y) {
//		union SIMDUnion { _simd_f32x4 v1; _simd_f32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x4_sub_enable() _simd_f32x64_sub_enable()
//#else
//	#define _simd_f32x4_sub(X,Y) _simd_f32x4_combine(\
//		_simd_f32x2_sub(_simd_f32x4_splitlo(X), _simd_f32x4_splitlo(Y)),\
//		_simd_f32x2_sub(_simd_f32x4_splithi(X), _simd_f32x4_splithi(Y)))
//	#define _simd_f32x4_sub_enable() (_simd_f32x2_sub_enable() && _simd_f32x4_combine_enable() && _simd_f32x4_splitlo_enable()  && _simd_f32x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x4_sub_) && ! defined(_simd_f32x4_sub_scalar_)
//	#define _simd_f32x4_sub_scalar_(X,Y) _simd_f32x4_sub_(X,_simd_f32x4_fill_scalar_(Y))
//	#define _simd_f32x4_sub_scalar_instruction_set _simd_f32x4_sub_instruction_set
//#endif
//#ifdef _simd_f32x4_sub_scalar_
//	#define _simd_f32x4_sub_scalar(X,Y) _simd_f32x4_sub_scalar_(X,Y)
//	#define _simd_f32x4_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_sub_scalar_instruction_set>()
//#else
//	#define _simd_f32x4_sub_scalar(X,Y) _simd_f32x4_sub_safe(X,_simd_f32x4_fill_scalar_safe(Y))
//	#define _simd_f32x4_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_f32x1_sub_safe
//	#define _simd_f32x1_sub_safe(X,Y) (X - Y)
//	#define _simd_f32x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_f32x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_sub_enabled() true
//#endif
//
//#define _simd_f32x8_sub_safe(X,Y)_simd_f32x8_combine_safe(\
//	_simd_f32x4_sub_safe(_simd_f32x8_splitlo_safe(X), _simd_ f32x8_splitlo_safe(Y)),\
//	_simd_f32x4_sub_safe(_simd_f32x8_splithi_safe(X), _simd_ f32x8_splithi_safe(Y)))
//#ifdef _simd_f32x8_sub_
//	#define _simd_f32x8_sub(X,Y) _simd_f32x8_sub_(X, Y)
//	#define _simd_f32x8_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_sub_instruction_set>()
//#elif defined(_simd_f32x16_sub_)
//	static ANVIL_STRONG_INLINE _simd_f32x8 ANVIL_SIMD_CALL _simd_f32x8_sub(const register _simd_f32x8 x, const register _simd_f32x8 y) {
//		union SIMDUnion { _simd_f32x8 v1; _simd_f32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x16_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x8_sub_enable() _simd_f32x16_sub_enable()
//#elif defined(_simd_f32x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_f32x8 ANVIL_SIMD_CALL _simd_f32x8_sub(const register _simd_f32x8 x, const register _simd_f32x8 y) {
//		union SIMDUnion { _simd_f32x8 v1; _simd_f32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x8_sub_enable() _simd_f32x32_sub_enable()
//#elif defined(_simd_f32x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_f32x8 ANVIL_SIMD_CALL _simd_f32x8_sub(const register _simd_f32x8 x, const register _simd_f32x8 y) {
//		union SIMDUnion { _simd_f32x8 v1; _simd_f32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x8_sub_enable() _simd_f32x64_sub_enable()
//#else
//	#define _simd_f32x8_sub(X,Y) _simd_f32x8_combine(\
//		_simd_f32x4_sub(_simd_f32x8_splitlo(X), _simd_f32x8_splitlo(Y)),\
//		_simd_f32x4_sub(_simd_f32x8_splithi(X), _simd_f32x8_splithi(Y)))
//	#define _simd_f32x8_sub_enable() (_simd_f32x4_sub_enable() && _simd_f32x8_combine_enable() && _simd_f32x8_splitlo_enable()  && _simd_f32x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x8_sub_) && ! defined(_simd_f32x8_sub_scalar_)
//	#define _simd_f32x8_sub_scalar_(X,Y) _simd_f32x8_sub_(X,_simd_f32x8_fill_scalar_(Y))
//	#define _simd_f32x8_sub_scalar_instruction_set _simd_f32x8_sub_instruction_set
//#endif
//#ifdef _simd_f32x8_sub_scalar_
//	#define _simd_f32x8_sub_scalar(X,Y) _simd_f32x8_sub_scalar_(X,Y)
//	#define _simd_f32x8_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_sub_scalar_instruction_set>()
//#else
//	#define _simd_f32x8_sub_scalar(X,Y) _simd_f32x8_sub_safe(X,_simd_f32x8_fill_scalar_safe(Y))
//	#define _simd_f32x8_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_f32x1_sub_safe
//	#define _simd_f32x1_sub_safe(X,Y) (X - Y)
//	#define _simd_f32x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_f32x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_sub_enabled() true
//#endif
//
//#define _simd_f32x16_sub_safe(X,Y)_simd_f32x16_combine_safe(\
//	_simd_f32x8_sub_safe(_simd_f32x16_splitlo_safe(X), _simd_ f32x16_splitlo_safe(Y)),\
//	_simd_f32x8_sub_safe(_simd_f32x16_splithi_safe(X), _simd_ f32x16_splithi_safe(Y)))
//#ifdef _simd_f32x16_sub_
//	#define _simd_f32x16_sub(X,Y) _simd_f32x16_sub_(X, Y)
//	#define _simd_f32x16_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_sub_instruction_set>()
//#elif defined(_simd_f32x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_f32x16 ANVIL_SIMD_CALL _simd_f32x16_sub(const register _simd_f32x16 x, const register _simd_f32x16 y) {
//		union SIMDUnion { _simd_f32x16 v1; _simd_f32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x16_sub_enable() _simd_f32x32_sub_enable()
//#elif defined(_simd_f32x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_f32x16 ANVIL_SIMD_CALL _simd_f32x16_sub(const register _simd_f32x16 x, const register _simd_f32x16 y) {
//		union SIMDUnion { _simd_f32x16 v1; _simd_f32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x16_sub_enable() _simd_f32x64_sub_enable()
//#else
//	#define _simd_f32x16_sub(X,Y) _simd_f32x16_combine(\
//		_simd_f32x8_sub(_simd_f32x16_splitlo(X), _simd_f32x16_splitlo(Y)),\
//		_simd_f32x8_sub(_simd_f32x16_splithi(X), _simd_f32x16_splithi(Y)))
//	#define _simd_f32x16_sub_enable() (_simd_f32x8_sub_enable() && _simd_f32x16_combine_enable() && _simd_f32x16_splitlo_enable()  && _simd_f32x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x16_sub_) && ! defined(_simd_f32x16_sub_scalar_)
//	#define _simd_f32x16_sub_scalar_(X,Y) _simd_f32x16_sub_(X,_simd_f32x16_fill_scalar_(Y))
//	#define _simd_f32x16_sub_scalar_instruction_set _simd_f32x16_sub_instruction_set
//#endif
//#ifdef _simd_f32x16_sub_scalar_
//	#define _simd_f32x16_sub_scalar(X,Y) _simd_f32x16_sub_scalar_(X,Y)
//	#define _simd_f32x16_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_sub_scalar_instruction_set>()
//#else
//	#define _simd_f32x16_sub_scalar(X,Y) _simd_f32x16_sub_safe(X,_simd_f32x16_fill_scalar_safe(Y))
//	#define _simd_f32x16_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_f32x1_sub_safe
//	#define _simd_f32x1_sub_safe(X,Y) (X - Y)
//	#define _simd_f32x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_f32x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_sub_enabled() true
//#endif
//
//#define _simd_f32x32_sub_safe(X,Y)_simd_f32x32_combine_safe(\
//	_simd_f32x16_sub_safe(_simd_f32x32_splitlo_safe(X), _simd_ f32x32_splitlo_safe(Y)),\
//	_simd_f32x16_sub_safe(_simd_f32x32_splithi_safe(X), _simd_ f32x32_splithi_safe(Y)))
//#ifdef _simd_f32x32_sub_
//	#define _simd_f32x32_sub(X,Y) _simd_f32x32_sub_(X, Y)
//	#define _simd_f32x32_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_sub_instruction_set>()
//#elif defined(_simd_f32x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_f32x32 ANVIL_SIMD_CALL _simd_f32x32_sub(const register _simd_f32x32 x, const register _simd_f32x32 y) {
//		union SIMDUnion { _simd_f32x32 v1; _simd_f32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x32_sub_enable() _simd_f32x64_sub_enable()
//#else
//	#define _simd_f32x32_sub(X,Y) _simd_f32x32_combine(\
//		_simd_f32x16_sub(_simd_f32x32_splitlo(X), _simd_f32x32_splitlo(Y)),\
//		_simd_f32x16_sub(_simd_f32x32_splithi(X), _simd_f32x32_splithi(Y)))
//	#define _simd_f32x32_sub_enable() (_simd_f32x16_sub_enable() && _simd_f32x32_combine_enable() && _simd_f32x32_splitlo_enable()  && _simd_f32x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x32_sub_) && ! defined(_simd_f32x32_sub_scalar_)
//	#define _simd_f32x32_sub_scalar_(X,Y) _simd_f32x32_sub_(X,_simd_f32x32_fill_scalar_(Y))
//	#define _simd_f32x32_sub_scalar_instruction_set _simd_f32x32_sub_instruction_set
//#endif
//#ifdef _simd_f32x32_sub_scalar_
//	#define _simd_f32x32_sub_scalar(X,Y) _simd_f32x32_sub_scalar_(X,Y)
//	#define _simd_f32x32_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_sub_scalar_instruction_set>()
//#else
//	#define _simd_f32x32_sub_scalar(X,Y) _simd_f32x32_sub_safe(X,_simd_f32x32_fill_scalar_safe(Y))
//	#define _simd_f32x32_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_f32x1_sub_safe
//	#define _simd_f32x1_sub_safe(X,Y) (X - Y)
//	#define _simd_f32x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_f32x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_sub_enabled() true
//#endif
//
//#define _simd_f32x64_sub_safe(X,Y)_simd_f32x64_combine_safe(\
//	_simd_f32x32_sub_safe(_simd_f32x64_splitlo_safe(X), _simd_ f32x64_splitlo_safe(Y)),\
//	_simd_f32x32_sub_safe(_simd_f32x64_splithi_safe(X), _simd_ f32x64_splithi_safe(Y)))
//#ifdef _simd_f32x64_sub_
//	#define _simd_f32x64_sub(X,Y) _simd_f32x64_sub_(X, Y)
//	#define _simd_f32x64_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_sub_instruction_set>()
//#else
//	#define _simd_f32x64_sub(X,Y) _simd_f32x64_combine(\
//		_simd_f32x32_sub(_simd_f32x64_splitlo(X), _simd_f32x64_splitlo(Y)),\
//		_simd_f32x32_sub(_simd_f32x64_splithi(X), _simd_f32x64_splithi(Y)))
//	#define _simd_f32x64_sub_enable() (_simd_f32x32_sub_enable() && _simd_f32x64_combine_enable() && _simd_f32x64_splitlo_enable()  && _simd_f32x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x64_sub_) && ! defined(_simd_f32x64_sub_scalar_)
//	#define _simd_f32x64_sub_scalar_(X,Y) _simd_f32x64_sub_(X,_simd_f32x64_fill_scalar_(Y))
//	#define _simd_f32x64_sub_scalar_instruction_set _simd_f32x64_sub_instruction_set
//#endif
//#ifdef _simd_f32x64_sub_scalar_
//	#define _simd_f32x64_sub_scalar(X,Y) _simd_f32x64_sub_scalar_(X,Y)
//	#define _simd_f32x64_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_sub_scalar_instruction_set>()
//#else
//	#define _simd_f32x64_sub_scalar(X,Y) _simd_f32x64_sub_safe(X,_simd_f32x64_fill_scalar_safe(Y))
//	#define _simd_f32x64_sub_scalar_enabled() true
//#endif
//
//// -- s64 --
//
//#ifndef _simd_s64x1_sub_safe
//	#define _simd_s64x1_sub_safe(X,Y) (X - Y)
//	#define _simd_s64x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_s64x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_sub_enabled() true
//#endif
//
//#define _simd_s64x2_sub_safe(X,Y)_simd_s64x2_combine_safe(\
//	_simd_s64x1_sub_safe(_simd_s64x2_splitlo_safe(X), _simd_ s64x2_splitlo_safe(Y)),\
//	_simd_s64x1_sub_safe(_simd_s64x2_splithi_safe(X), _simd_ s64x2_splithi_safe(Y)))
//#ifdef _simd_s64x2_sub_
//	#define _simd_s64x2_sub(X,Y) _simd_s64x2_sub_(X, Y)
//	#define _simd_s64x2_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_sub_instruction_set>()
//#elif defined(_simd_s64x4_sub_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_sub(const register _simd_s64x2 x, const register _simd_s64x2 y) {
//		union SIMDUnion { _simd_s64x2 v1; _simd_s64x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x4_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x2_sub_enable() _simd_s64x4_sub_enable()
//#elif defined(_simd_s64x8_sub_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_sub(const register _simd_s64x2 x, const register _simd_s64x2 y) {
//		union SIMDUnion { _simd_s64x2 v1; _simd_s64x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x8_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x2_sub_enable() _simd_s64x8_sub_enable()
//#elif defined(_simd_s64x16_sub_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_sub(const register _simd_s64x2 x, const register _simd_s64x2 y) {
//		union SIMDUnion { _simd_s64x2 v1; _simd_s64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x16_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x2_sub_enable() _simd_s64x16_sub_enable()
//#elif defined(_simd_s64x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_sub(const register _simd_s64x2 x, const register _simd_s64x2 y) {
//		union SIMDUnion { _simd_s64x2 v1; _simd_s64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x2_sub_enable() _simd_s64x32_sub_enable()
//#elif defined(_simd_s64x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_sub(const register _simd_s64x2 x, const register _simd_s64x2 y) {
//		union SIMDUnion { _simd_s64x2 v1; _simd_s64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x2_sub_enable() _simd_s64x64_sub_enable()
//#else
//	#define _simd_s64x2_sub(X,Y) _simd_s64x2_combine(\
//		_simd_s64x1_sub(_simd_s64x2_splitlo(X), _simd_s64x2_splitlo(Y)),\
//		_simd_s64x1_sub(_simd_s64x2_splithi(X), _simd_s64x2_splithi(Y)))
//	#define _simd_s64x2_sub_enable() (_simd_s64x1_sub_enable() && _simd_s64x2_combine_enable() && _simd_s64x2_splitlo_enable()  && _simd_s64x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x2_sub_) && ! defined(_simd_s64x2_sub_scalar_)
//	#define _simd_s64x2_sub_scalar_(X,Y) _simd_s64x2_sub_(X,_simd_s64x2_fill_scalar_(Y))
//	#define _simd_s64x2_sub_scalar_instruction_set _simd_s64x2_sub_instruction_set
//#endif
//#ifdef _simd_s64x2_sub_scalar_
//	#define _simd_s64x2_sub_scalar(X,Y) _simd_s64x2_sub_scalar_(X,Y)
//	#define _simd_s64x2_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_sub_scalar_instruction_set>()
//#else
//	#define _simd_s64x2_sub_scalar(X,Y) _simd_s64x2_sub_safe(X,_simd_s64x2_fill_scalar_safe(Y))
//	#define _simd_s64x2_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_s64x1_sub_safe
//	#define _simd_s64x1_sub_safe(X,Y) (X - Y)
//	#define _simd_s64x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_s64x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_sub_enabled() true
//#endif
//
//#define _simd_s64x4_sub_safe(X,Y)_simd_s64x4_combine_safe(\
//	_simd_s64x2_sub_safe(_simd_s64x4_splitlo_safe(X), _simd_ s64x4_splitlo_safe(Y)),\
//	_simd_s64x2_sub_safe(_simd_s64x4_splithi_safe(X), _simd_ s64x4_splithi_safe(Y)))
//#ifdef _simd_s64x4_sub_
//	#define _simd_s64x4_sub(X,Y) _simd_s64x4_sub_(X, Y)
//	#define _simd_s64x4_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_sub_instruction_set>()
//#elif defined(_simd_s64x8_sub_)
//	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_sub(const register _simd_s64x4 x, const register _simd_s64x4 y) {
//		union SIMDUnion { _simd_s64x4 v1; _simd_s64x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x8_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x4_sub_enable() _simd_s64x8_sub_enable()
//#elif defined(_simd_s64x16_sub_)
//	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_sub(const register _simd_s64x4 x, const register _simd_s64x4 y) {
//		union SIMDUnion { _simd_s64x4 v1; _simd_s64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x16_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x4_sub_enable() _simd_s64x16_sub_enable()
//#elif defined(_simd_s64x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_sub(const register _simd_s64x4 x, const register _simd_s64x4 y) {
//		union SIMDUnion { _simd_s64x4 v1; _simd_s64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x4_sub_enable() _simd_s64x32_sub_enable()
//#elif defined(_simd_s64x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_sub(const register _simd_s64x4 x, const register _simd_s64x4 y) {
//		union SIMDUnion { _simd_s64x4 v1; _simd_s64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x4_sub_enable() _simd_s64x64_sub_enable()
//#else
//	#define _simd_s64x4_sub(X,Y) _simd_s64x4_combine(\
//		_simd_s64x2_sub(_simd_s64x4_splitlo(X), _simd_s64x4_splitlo(Y)),\
//		_simd_s64x2_sub(_simd_s64x4_splithi(X), _simd_s64x4_splithi(Y)))
//	#define _simd_s64x4_sub_enable() (_simd_s64x2_sub_enable() && _simd_s64x4_combine_enable() && _simd_s64x4_splitlo_enable()  && _simd_s64x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x4_sub_) && ! defined(_simd_s64x4_sub_scalar_)
//	#define _simd_s64x4_sub_scalar_(X,Y) _simd_s64x4_sub_(X,_simd_s64x4_fill_scalar_(Y))
//	#define _simd_s64x4_sub_scalar_instruction_set _simd_s64x4_sub_instruction_set
//#endif
//#ifdef _simd_s64x4_sub_scalar_
//	#define _simd_s64x4_sub_scalar(X,Y) _simd_s64x4_sub_scalar_(X,Y)
//	#define _simd_s64x4_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_sub_scalar_instruction_set>()
//#else
//	#define _simd_s64x4_sub_scalar(X,Y) _simd_s64x4_sub_safe(X,_simd_s64x4_fill_scalar_safe(Y))
//	#define _simd_s64x4_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_s64x1_sub_safe
//	#define _simd_s64x1_sub_safe(X,Y) (X - Y)
//	#define _simd_s64x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_s64x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_sub_enabled() true
//#endif
//
//#define _simd_s64x8_sub_safe(X,Y)_simd_s64x8_combine_safe(\
//	_simd_s64x4_sub_safe(_simd_s64x8_splitlo_safe(X), _simd_ s64x8_splitlo_safe(Y)),\
//	_simd_s64x4_sub_safe(_simd_s64x8_splithi_safe(X), _simd_ s64x8_splithi_safe(Y)))
//#ifdef _simd_s64x8_sub_
//	#define _simd_s64x8_sub(X,Y) _simd_s64x8_sub_(X, Y)
//	#define _simd_s64x8_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_sub_instruction_set>()
//#elif defined(_simd_s64x16_sub_)
//	static ANVIL_STRONG_INLINE _simd_s64x8 ANVIL_SIMD_CALL _simd_s64x8_sub(const register _simd_s64x8 x, const register _simd_s64x8 y) {
//		union SIMDUnion { _simd_s64x8 v1; _simd_s64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x16_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x8_sub_enable() _simd_s64x16_sub_enable()
//#elif defined(_simd_s64x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_s64x8 ANVIL_SIMD_CALL _simd_s64x8_sub(const register _simd_s64x8 x, const register _simd_s64x8 y) {
//		union SIMDUnion { _simd_s64x8 v1; _simd_s64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x8_sub_enable() _simd_s64x32_sub_enable()
//#elif defined(_simd_s64x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_s64x8 ANVIL_SIMD_CALL _simd_s64x8_sub(const register _simd_s64x8 x, const register _simd_s64x8 y) {
//		union SIMDUnion { _simd_s64x8 v1; _simd_s64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x8_sub_enable() _simd_s64x64_sub_enable()
//#else
//	#define _simd_s64x8_sub(X,Y) _simd_s64x8_combine(\
//		_simd_s64x4_sub(_simd_s64x8_splitlo(X), _simd_s64x8_splitlo(Y)),\
//		_simd_s64x4_sub(_simd_s64x8_splithi(X), _simd_s64x8_splithi(Y)))
//	#define _simd_s64x8_sub_enable() (_simd_s64x4_sub_enable() && _simd_s64x8_combine_enable() && _simd_s64x8_splitlo_enable()  && _simd_s64x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x8_sub_) && ! defined(_simd_s64x8_sub_scalar_)
//	#define _simd_s64x8_sub_scalar_(X,Y) _simd_s64x8_sub_(X,_simd_s64x8_fill_scalar_(Y))
//	#define _simd_s64x8_sub_scalar_instruction_set _simd_s64x8_sub_instruction_set
//#endif
//#ifdef _simd_s64x8_sub_scalar_
//	#define _simd_s64x8_sub_scalar(X,Y) _simd_s64x8_sub_scalar_(X,Y)
//	#define _simd_s64x8_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_sub_scalar_instruction_set>()
//#else
//	#define _simd_s64x8_sub_scalar(X,Y) _simd_s64x8_sub_safe(X,_simd_s64x8_fill_scalar_safe(Y))
//	#define _simd_s64x8_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_s64x1_sub_safe
//	#define _simd_s64x1_sub_safe(X,Y) (X - Y)
//	#define _simd_s64x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_s64x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_sub_enabled() true
//#endif
//
//#define _simd_s64x16_sub_safe(X,Y)_simd_s64x16_combine_safe(\
//	_simd_s64x8_sub_safe(_simd_s64x16_splitlo_safe(X), _simd_ s64x16_splitlo_safe(Y)),\
//	_simd_s64x8_sub_safe(_simd_s64x16_splithi_safe(X), _simd_ s64x16_splithi_safe(Y)))
//#ifdef _simd_s64x16_sub_
//	#define _simd_s64x16_sub(X,Y) _simd_s64x16_sub_(X, Y)
//	#define _simd_s64x16_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_sub_instruction_set>()
//#elif defined(_simd_s64x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_s64x16 ANVIL_SIMD_CALL _simd_s64x16_sub(const register _simd_s64x16 x, const register _simd_s64x16 y) {
//		union SIMDUnion { _simd_s64x16 v1; _simd_s64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x16_sub_enable() _simd_s64x32_sub_enable()
//#elif defined(_simd_s64x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_s64x16 ANVIL_SIMD_CALL _simd_s64x16_sub(const register _simd_s64x16 x, const register _simd_s64x16 y) {
//		union SIMDUnion { _simd_s64x16 v1; _simd_s64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x16_sub_enable() _simd_s64x64_sub_enable()
//#else
//	#define _simd_s64x16_sub(X,Y) _simd_s64x16_combine(\
//		_simd_s64x8_sub(_simd_s64x16_splitlo(X), _simd_s64x16_splitlo(Y)),\
//		_simd_s64x8_sub(_simd_s64x16_splithi(X), _simd_s64x16_splithi(Y)))
//	#define _simd_s64x16_sub_enable() (_simd_s64x8_sub_enable() && _simd_s64x16_combine_enable() && _simd_s64x16_splitlo_enable()  && _simd_s64x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x16_sub_) && ! defined(_simd_s64x16_sub_scalar_)
//	#define _simd_s64x16_sub_scalar_(X,Y) _simd_s64x16_sub_(X,_simd_s64x16_fill_scalar_(Y))
//	#define _simd_s64x16_sub_scalar_instruction_set _simd_s64x16_sub_instruction_set
//#endif
//#ifdef _simd_s64x16_sub_scalar_
//	#define _simd_s64x16_sub_scalar(X,Y) _simd_s64x16_sub_scalar_(X,Y)
//	#define _simd_s64x16_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_sub_scalar_instruction_set>()
//#else
//	#define _simd_s64x16_sub_scalar(X,Y) _simd_s64x16_sub_safe(X,_simd_s64x16_fill_scalar_safe(Y))
//	#define _simd_s64x16_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_s64x1_sub_safe
//	#define _simd_s64x1_sub_safe(X,Y) (X - Y)
//	#define _simd_s64x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_s64x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_sub_enabled() true
//#endif
//
//#define _simd_s64x32_sub_safe(X,Y)_simd_s64x32_combine_safe(\
//	_simd_s64x16_sub_safe(_simd_s64x32_splitlo_safe(X), _simd_ s64x32_splitlo_safe(Y)),\
//	_simd_s64x16_sub_safe(_simd_s64x32_splithi_safe(X), _simd_ s64x32_splithi_safe(Y)))
//#ifdef _simd_s64x32_sub_
//	#define _simd_s64x32_sub(X,Y) _simd_s64x32_sub_(X, Y)
//	#define _simd_s64x32_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_sub_instruction_set>()
//#elif defined(_simd_s64x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_s64x32 ANVIL_SIMD_CALL _simd_s64x32_sub(const register _simd_s64x32 x, const register _simd_s64x32 y) {
//		union SIMDUnion { _simd_s64x32 v1; _simd_s64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x32_sub_enable() _simd_s64x64_sub_enable()
//#else
//	#define _simd_s64x32_sub(X,Y) _simd_s64x32_combine(\
//		_simd_s64x16_sub(_simd_s64x32_splitlo(X), _simd_s64x32_splitlo(Y)),\
//		_simd_s64x16_sub(_simd_s64x32_splithi(X), _simd_s64x32_splithi(Y)))
//	#define _simd_s64x32_sub_enable() (_simd_s64x16_sub_enable() && _simd_s64x32_combine_enable() && _simd_s64x32_splitlo_enable()  && _simd_s64x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x32_sub_) && ! defined(_simd_s64x32_sub_scalar_)
//	#define _simd_s64x32_sub_scalar_(X,Y) _simd_s64x32_sub_(X,_simd_s64x32_fill_scalar_(Y))
//	#define _simd_s64x32_sub_scalar_instruction_set _simd_s64x32_sub_instruction_set
//#endif
//#ifdef _simd_s64x32_sub_scalar_
//	#define _simd_s64x32_sub_scalar(X,Y) _simd_s64x32_sub_scalar_(X,Y)
//	#define _simd_s64x32_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_sub_scalar_instruction_set>()
//#else
//	#define _simd_s64x32_sub_scalar(X,Y) _simd_s64x32_sub_safe(X,_simd_s64x32_fill_scalar_safe(Y))
//	#define _simd_s64x32_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_s64x1_sub_safe
//	#define _simd_s64x1_sub_safe(X,Y) (X - Y)
//	#define _simd_s64x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_s64x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_sub_enabled() true
//#endif
//
//#define _simd_s64x64_sub_safe(X,Y)_simd_s64x64_combine_safe(\
//	_simd_s64x32_sub_safe(_simd_s64x64_splitlo_safe(X), _simd_ s64x64_splitlo_safe(Y)),\
//	_simd_s64x32_sub_safe(_simd_s64x64_splithi_safe(X), _simd_ s64x64_splithi_safe(Y)))
//#ifdef _simd_s64x64_sub_
//	#define _simd_s64x64_sub(X,Y) _simd_s64x64_sub_(X, Y)
//	#define _simd_s64x64_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_sub_instruction_set>()
//#else
//	#define _simd_s64x64_sub(X,Y) _simd_s64x64_combine(\
//		_simd_s64x32_sub(_simd_s64x64_splitlo(X), _simd_s64x64_splitlo(Y)),\
//		_simd_s64x32_sub(_simd_s64x64_splithi(X), _simd_s64x64_splithi(Y)))
//	#define _simd_s64x64_sub_enable() (_simd_s64x32_sub_enable() && _simd_s64x64_combine_enable() && _simd_s64x64_splitlo_enable()  && _simd_s64x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x64_sub_) && ! defined(_simd_s64x64_sub_scalar_)
//	#define _simd_s64x64_sub_scalar_(X,Y) _simd_s64x64_sub_(X,_simd_s64x64_fill_scalar_(Y))
//	#define _simd_s64x64_sub_scalar_instruction_set _simd_s64x64_sub_instruction_set
//#endif
//#ifdef _simd_s64x64_sub_scalar_
//	#define _simd_s64x64_sub_scalar(X,Y) _simd_s64x64_sub_scalar_(X,Y)
//	#define _simd_s64x64_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_sub_scalar_instruction_set>()
//#else
//	#define _simd_s64x64_sub_scalar(X,Y) _simd_s64x64_sub_safe(X,_simd_s64x64_fill_scalar_safe(Y))
//	#define _simd_s64x64_sub_scalar_enabled() true
//#endif
//
//// -- u64 --
//
//#ifndef _simd_u64x1_sub_safe
//	#define _simd_u64x1_sub_safe(X,Y) (X - Y)
//	#define _simd_u64x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_u64x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_sub_enabled() true
//#endif
//
//#define _simd_u64x2_sub_safe(X,Y)_simd_u64x2_combine_safe(\
//	_simd_u64x1_sub_safe(_simd_u64x2_splitlo_safe(X), _simd_ u64x2_splitlo_safe(Y)),\
//	_simd_u64x1_sub_safe(_simd_u64x2_splithi_safe(X), _simd_ u64x2_splithi_safe(Y)))
//#ifdef _simd_u64x2_sub_
//	#define _simd_u64x2_sub(X,Y) _simd_u64x2_sub_(X, Y)
//	#define _simd_u64x2_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_sub_instruction_set>()
//#elif defined(_simd_u64x4_sub_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_sub(const register _simd_u64x2 x, const register _simd_u64x2 y) {
//		union SIMDUnion { _simd_u64x2 v1; _simd_u64x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x4_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x2_sub_enable() _simd_u64x4_sub_enable()
//#elif defined(_simd_u64x8_sub_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_sub(const register _simd_u64x2 x, const register _simd_u64x2 y) {
//		union SIMDUnion { _simd_u64x2 v1; _simd_u64x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x8_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x2_sub_enable() _simd_u64x8_sub_enable()
//#elif defined(_simd_u64x16_sub_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_sub(const register _simd_u64x2 x, const register _simd_u64x2 y) {
//		union SIMDUnion { _simd_u64x2 v1; _simd_u64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x16_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x2_sub_enable() _simd_u64x16_sub_enable()
//#elif defined(_simd_u64x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_sub(const register _simd_u64x2 x, const register _simd_u64x2 y) {
//		union SIMDUnion { _simd_u64x2 v1; _simd_u64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x2_sub_enable() _simd_u64x32_sub_enable()
//#elif defined(_simd_u64x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_sub(const register _simd_u64x2 x, const register _simd_u64x2 y) {
//		union SIMDUnion { _simd_u64x2 v1; _simd_u64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x2_sub_enable() _simd_u64x64_sub_enable()
//#else
//	#define _simd_u64x2_sub(X,Y) _simd_u64x2_combine(\
//		_simd_u64x1_sub(_simd_u64x2_splitlo(X), _simd_u64x2_splitlo(Y)),\
//		_simd_u64x1_sub(_simd_u64x2_splithi(X), _simd_u64x2_splithi(Y)))
//	#define _simd_u64x2_sub_enable() (_simd_u64x1_sub_enable() && _simd_u64x2_combine_enable() && _simd_u64x2_splitlo_enable()  && _simd_u64x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x2_sub_) && ! defined(_simd_u64x2_sub_scalar_)
//	#define _simd_u64x2_sub_scalar_(X,Y) _simd_u64x2_sub_(X,_simd_u64x2_fill_scalar_(Y))
//	#define _simd_u64x2_sub_scalar_instruction_set _simd_u64x2_sub_instruction_set
//#endif
//#ifdef _simd_u64x2_sub_scalar_
//	#define _simd_u64x2_sub_scalar(X,Y) _simd_u64x2_sub_scalar_(X,Y)
//	#define _simd_u64x2_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_sub_scalar_instruction_set>()
//#else
//	#define _simd_u64x2_sub_scalar(X,Y) _simd_u64x2_sub_safe(X,_simd_u64x2_fill_scalar_safe(Y))
//	#define _simd_u64x2_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_u64x1_sub_safe
//	#define _simd_u64x1_sub_safe(X,Y) (X - Y)
//	#define _simd_u64x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_u64x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_sub_enabled() true
//#endif
//
//#define _simd_u64x4_sub_safe(X,Y)_simd_u64x4_combine_safe(\
//	_simd_u64x2_sub_safe(_simd_u64x4_splitlo_safe(X), _simd_ u64x4_splitlo_safe(Y)),\
//	_simd_u64x2_sub_safe(_simd_u64x4_splithi_safe(X), _simd_ u64x4_splithi_safe(Y)))
//#ifdef _simd_u64x4_sub_
//	#define _simd_u64x4_sub(X,Y) _simd_u64x4_sub_(X, Y)
//	#define _simd_u64x4_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_sub_instruction_set>()
//#elif defined(_simd_u64x8_sub_)
//	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_sub(const register _simd_u64x4 x, const register _simd_u64x4 y) {
//		union SIMDUnion { _simd_u64x4 v1; _simd_u64x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x8_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x4_sub_enable() _simd_u64x8_sub_enable()
//#elif defined(_simd_u64x16_sub_)
//	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_sub(const register _simd_u64x4 x, const register _simd_u64x4 y) {
//		union SIMDUnion { _simd_u64x4 v1; _simd_u64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x16_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x4_sub_enable() _simd_u64x16_sub_enable()
//#elif defined(_simd_u64x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_sub(const register _simd_u64x4 x, const register _simd_u64x4 y) {
//		union SIMDUnion { _simd_u64x4 v1; _simd_u64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x4_sub_enable() _simd_u64x32_sub_enable()
//#elif defined(_simd_u64x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_sub(const register _simd_u64x4 x, const register _simd_u64x4 y) {
//		union SIMDUnion { _simd_u64x4 v1; _simd_u64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x4_sub_enable() _simd_u64x64_sub_enable()
//#else
//	#define _simd_u64x4_sub(X,Y) _simd_u64x4_combine(\
//		_simd_u64x2_sub(_simd_u64x4_splitlo(X), _simd_u64x4_splitlo(Y)),\
//		_simd_u64x2_sub(_simd_u64x4_splithi(X), _simd_u64x4_splithi(Y)))
//	#define _simd_u64x4_sub_enable() (_simd_u64x2_sub_enable() && _simd_u64x4_combine_enable() && _simd_u64x4_splitlo_enable()  && _simd_u64x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x4_sub_) && ! defined(_simd_u64x4_sub_scalar_)
//	#define _simd_u64x4_sub_scalar_(X,Y) _simd_u64x4_sub_(X,_simd_u64x4_fill_scalar_(Y))
//	#define _simd_u64x4_sub_scalar_instruction_set _simd_u64x4_sub_instruction_set
//#endif
//#ifdef _simd_u64x4_sub_scalar_
//	#define _simd_u64x4_sub_scalar(X,Y) _simd_u64x4_sub_scalar_(X,Y)
//	#define _simd_u64x4_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_sub_scalar_instruction_set>()
//#else
//	#define _simd_u64x4_sub_scalar(X,Y) _simd_u64x4_sub_safe(X,_simd_u64x4_fill_scalar_safe(Y))
//	#define _simd_u64x4_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_u64x1_sub_safe
//	#define _simd_u64x1_sub_safe(X,Y) (X - Y)
//	#define _simd_u64x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_u64x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_sub_enabled() true
//#endif
//
//#define _simd_u64x8_sub_safe(X,Y)_simd_u64x8_combine_safe(\
//	_simd_u64x4_sub_safe(_simd_u64x8_splitlo_safe(X), _simd_ u64x8_splitlo_safe(Y)),\
//	_simd_u64x4_sub_safe(_simd_u64x8_splithi_safe(X), _simd_ u64x8_splithi_safe(Y)))
//#ifdef _simd_u64x8_sub_
//	#define _simd_u64x8_sub(X,Y) _simd_u64x8_sub_(X, Y)
//	#define _simd_u64x8_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_sub_instruction_set>()
//#elif defined(_simd_u64x16_sub_)
//	static ANVIL_STRONG_INLINE _simd_u64x8 ANVIL_SIMD_CALL _simd_u64x8_sub(const register _simd_u64x8 x, const register _simd_u64x8 y) {
//		union SIMDUnion { _simd_u64x8 v1; _simd_u64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x16_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x8_sub_enable() _simd_u64x16_sub_enable()
//#elif defined(_simd_u64x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_u64x8 ANVIL_SIMD_CALL _simd_u64x8_sub(const register _simd_u64x8 x, const register _simd_u64x8 y) {
//		union SIMDUnion { _simd_u64x8 v1; _simd_u64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x8_sub_enable() _simd_u64x32_sub_enable()
//#elif defined(_simd_u64x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_u64x8 ANVIL_SIMD_CALL _simd_u64x8_sub(const register _simd_u64x8 x, const register _simd_u64x8 y) {
//		union SIMDUnion { _simd_u64x8 v1; _simd_u64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x8_sub_enable() _simd_u64x64_sub_enable()
//#else
//	#define _simd_u64x8_sub(X,Y) _simd_u64x8_combine(\
//		_simd_u64x4_sub(_simd_u64x8_splitlo(X), _simd_u64x8_splitlo(Y)),\
//		_simd_u64x4_sub(_simd_u64x8_splithi(X), _simd_u64x8_splithi(Y)))
//	#define _simd_u64x8_sub_enable() (_simd_u64x4_sub_enable() && _simd_u64x8_combine_enable() && _simd_u64x8_splitlo_enable()  && _simd_u64x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x8_sub_) && ! defined(_simd_u64x8_sub_scalar_)
//	#define _simd_u64x8_sub_scalar_(X,Y) _simd_u64x8_sub_(X,_simd_u64x8_fill_scalar_(Y))
//	#define _simd_u64x8_sub_scalar_instruction_set _simd_u64x8_sub_instruction_set
//#endif
//#ifdef _simd_u64x8_sub_scalar_
//	#define _simd_u64x8_sub_scalar(X,Y) _simd_u64x8_sub_scalar_(X,Y)
//	#define _simd_u64x8_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_sub_scalar_instruction_set>()
//#else
//	#define _simd_u64x8_sub_scalar(X,Y) _simd_u64x8_sub_safe(X,_simd_u64x8_fill_scalar_safe(Y))
//	#define _simd_u64x8_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_u64x1_sub_safe
//	#define _simd_u64x1_sub_safe(X,Y) (X - Y)
//	#define _simd_u64x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_u64x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_sub_enabled() true
//#endif
//
//#define _simd_u64x16_sub_safe(X,Y)_simd_u64x16_combine_safe(\
//	_simd_u64x8_sub_safe(_simd_u64x16_splitlo_safe(X), _simd_ u64x16_splitlo_safe(Y)),\
//	_simd_u64x8_sub_safe(_simd_u64x16_splithi_safe(X), _simd_ u64x16_splithi_safe(Y)))
//#ifdef _simd_u64x16_sub_
//	#define _simd_u64x16_sub(X,Y) _simd_u64x16_sub_(X, Y)
//	#define _simd_u64x16_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_sub_instruction_set>()
//#elif defined(_simd_u64x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_u64x16 ANVIL_SIMD_CALL _simd_u64x16_sub(const register _simd_u64x16 x, const register _simd_u64x16 y) {
//		union SIMDUnion { _simd_u64x16 v1; _simd_u64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x16_sub_enable() _simd_u64x32_sub_enable()
//#elif defined(_simd_u64x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_u64x16 ANVIL_SIMD_CALL _simd_u64x16_sub(const register _simd_u64x16 x, const register _simd_u64x16 y) {
//		union SIMDUnion { _simd_u64x16 v1; _simd_u64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x16_sub_enable() _simd_u64x64_sub_enable()
//#else
//	#define _simd_u64x16_sub(X,Y) _simd_u64x16_combine(\
//		_simd_u64x8_sub(_simd_u64x16_splitlo(X), _simd_u64x16_splitlo(Y)),\
//		_simd_u64x8_sub(_simd_u64x16_splithi(X), _simd_u64x16_splithi(Y)))
//	#define _simd_u64x16_sub_enable() (_simd_u64x8_sub_enable() && _simd_u64x16_combine_enable() && _simd_u64x16_splitlo_enable()  && _simd_u64x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x16_sub_) && ! defined(_simd_u64x16_sub_scalar_)
//	#define _simd_u64x16_sub_scalar_(X,Y) _simd_u64x16_sub_(X,_simd_u64x16_fill_scalar_(Y))
//	#define _simd_u64x16_sub_scalar_instruction_set _simd_u64x16_sub_instruction_set
//#endif
//#ifdef _simd_u64x16_sub_scalar_
//	#define _simd_u64x16_sub_scalar(X,Y) _simd_u64x16_sub_scalar_(X,Y)
//	#define _simd_u64x16_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_sub_scalar_instruction_set>()
//#else
//	#define _simd_u64x16_sub_scalar(X,Y) _simd_u64x16_sub_safe(X,_simd_u64x16_fill_scalar_safe(Y))
//	#define _simd_u64x16_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_u64x1_sub_safe
//	#define _simd_u64x1_sub_safe(X,Y) (X - Y)
//	#define _simd_u64x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_u64x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_sub_enabled() true
//#endif
//
//#define _simd_u64x32_sub_safe(X,Y)_simd_u64x32_combine_safe(\
//	_simd_u64x16_sub_safe(_simd_u64x32_splitlo_safe(X), _simd_ u64x32_splitlo_safe(Y)),\
//	_simd_u64x16_sub_safe(_simd_u64x32_splithi_safe(X), _simd_ u64x32_splithi_safe(Y)))
//#ifdef _simd_u64x32_sub_
//	#define _simd_u64x32_sub(X,Y) _simd_u64x32_sub_(X, Y)
//	#define _simd_u64x32_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_sub_instruction_set>()
//#elif defined(_simd_u64x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_u64x32 ANVIL_SIMD_CALL _simd_u64x32_sub(const register _simd_u64x32 x, const register _simd_u64x32 y) {
//		union SIMDUnion { _simd_u64x32 v1; _simd_u64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x32_sub_enable() _simd_u64x64_sub_enable()
//#else
//	#define _simd_u64x32_sub(X,Y) _simd_u64x32_combine(\
//		_simd_u64x16_sub(_simd_u64x32_splitlo(X), _simd_u64x32_splitlo(Y)),\
//		_simd_u64x16_sub(_simd_u64x32_splithi(X), _simd_u64x32_splithi(Y)))
//	#define _simd_u64x32_sub_enable() (_simd_u64x16_sub_enable() && _simd_u64x32_combine_enable() && _simd_u64x32_splitlo_enable()  && _simd_u64x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x32_sub_) && ! defined(_simd_u64x32_sub_scalar_)
//	#define _simd_u64x32_sub_scalar_(X,Y) _simd_u64x32_sub_(X,_simd_u64x32_fill_scalar_(Y))
//	#define _simd_u64x32_sub_scalar_instruction_set _simd_u64x32_sub_instruction_set
//#endif
//#ifdef _simd_u64x32_sub_scalar_
//	#define _simd_u64x32_sub_scalar(X,Y) _simd_u64x32_sub_scalar_(X,Y)
//	#define _simd_u64x32_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_sub_scalar_instruction_set>()
//#else
//	#define _simd_u64x32_sub_scalar(X,Y) _simd_u64x32_sub_safe(X,_simd_u64x32_fill_scalar_safe(Y))
//	#define _simd_u64x32_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_u64x1_sub_safe
//	#define _simd_u64x1_sub_safe(X,Y) (X - Y)
//	#define _simd_u64x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_u64x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_sub_enabled() true
//#endif
//
//#define _simd_u64x64_sub_safe(X,Y)_simd_u64x64_combine_safe(\
//	_simd_u64x32_sub_safe(_simd_u64x64_splitlo_safe(X), _simd_ u64x64_splitlo_safe(Y)),\
//	_simd_u64x32_sub_safe(_simd_u64x64_splithi_safe(X), _simd_ u64x64_splithi_safe(Y)))
//#ifdef _simd_u64x64_sub_
//	#define _simd_u64x64_sub(X,Y) _simd_u64x64_sub_(X, Y)
//	#define _simd_u64x64_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_sub_instruction_set>()
//#else
//	#define _simd_u64x64_sub(X,Y) _simd_u64x64_combine(\
//		_simd_u64x32_sub(_simd_u64x64_splitlo(X), _simd_u64x64_splitlo(Y)),\
//		_simd_u64x32_sub(_simd_u64x64_splithi(X), _simd_u64x64_splithi(Y)))
//	#define _simd_u64x64_sub_enable() (_simd_u64x32_sub_enable() && _simd_u64x64_combine_enable() && _simd_u64x64_splitlo_enable()  && _simd_u64x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x64_sub_) && ! defined(_simd_u64x64_sub_scalar_)
//	#define _simd_u64x64_sub_scalar_(X,Y) _simd_u64x64_sub_(X,_simd_u64x64_fill_scalar_(Y))
//	#define _simd_u64x64_sub_scalar_instruction_set _simd_u64x64_sub_instruction_set
//#endif
//#ifdef _simd_u64x64_sub_scalar_
//	#define _simd_u64x64_sub_scalar(X,Y) _simd_u64x64_sub_scalar_(X,Y)
//	#define _simd_u64x64_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_sub_scalar_instruction_set>()
//#else
//	#define _simd_u64x64_sub_scalar(X,Y) _simd_u64x64_sub_safe(X,_simd_u64x64_fill_scalar_safe(Y))
//	#define _simd_u64x64_sub_scalar_enabled() true
//#endif
//
//// -- s32 --
//
//#ifndef _simd_s32x1_sub_safe
//	#define _simd_s32x1_sub_safe(X,Y) (X - Y)
//	#define _simd_s32x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_s32x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_sub_enabled() true
//#endif
//
//#define _simd_s32x2_sub_safe(X,Y)_simd_s32x2_combine_safe(\
//	_simd_s32x1_sub_safe(_simd_s32x2_splitlo_safe(X), _simd_ s32x2_splitlo_safe(Y)),\
//	_simd_s32x1_sub_safe(_simd_s32x2_splithi_safe(X), _simd_ s32x2_splithi_safe(Y)))
//#ifdef _simd_s32x2_sub_
//	#define _simd_s32x2_sub(X,Y) _simd_s32x2_sub_(X, Y)
//	#define _simd_s32x2_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_sub_instruction_set>()
//#elif defined(_simd_s32x4_sub_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_sub(const register _simd_s32x2 x, const register _simd_s32x2 y) {
//		union SIMDUnion { _simd_s32x2 v1; _simd_s32x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x4_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x2_sub_enable() _simd_s32x4_sub_enable()
//#elif defined(_simd_s32x8_sub_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_sub(const register _simd_s32x2 x, const register _simd_s32x2 y) {
//		union SIMDUnion { _simd_s32x2 v1; _simd_s32x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x8_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x2_sub_enable() _simd_s32x8_sub_enable()
//#elif defined(_simd_s32x16_sub_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_sub(const register _simd_s32x2 x, const register _simd_s32x2 y) {
//		union SIMDUnion { _simd_s32x2 v1; _simd_s32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x16_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x2_sub_enable() _simd_s32x16_sub_enable()
//#elif defined(_simd_s32x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_sub(const register _simd_s32x2 x, const register _simd_s32x2 y) {
//		union SIMDUnion { _simd_s32x2 v1; _simd_s32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x2_sub_enable() _simd_s32x32_sub_enable()
//#elif defined(_simd_s32x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_sub(const register _simd_s32x2 x, const register _simd_s32x2 y) {
//		union SIMDUnion { _simd_s32x2 v1; _simd_s32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x2_sub_enable() _simd_s32x64_sub_enable()
//#else
//	#define _simd_s32x2_sub(X,Y) _simd_s32x2_combine(\
//		_simd_s32x1_sub(_simd_s32x2_splitlo(X), _simd_s32x2_splitlo(Y)),\
//		_simd_s32x1_sub(_simd_s32x2_splithi(X), _simd_s32x2_splithi(Y)))
//	#define _simd_s32x2_sub_enable() (_simd_s32x1_sub_enable() && _simd_s32x2_combine_enable() && _simd_s32x2_splitlo_enable()  && _simd_s32x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x2_sub_) && ! defined(_simd_s32x2_sub_scalar_)
//	#define _simd_s32x2_sub_scalar_(X,Y) _simd_s32x2_sub_(X,_simd_s32x2_fill_scalar_(Y))
//	#define _simd_s32x2_sub_scalar_instruction_set _simd_s32x2_sub_instruction_set
//#endif
//#ifdef _simd_s32x2_sub_scalar_
//	#define _simd_s32x2_sub_scalar(X,Y) _simd_s32x2_sub_scalar_(X,Y)
//	#define _simd_s32x2_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_sub_scalar_instruction_set>()
//#else
//	#define _simd_s32x2_sub_scalar(X,Y) _simd_s32x2_sub_safe(X,_simd_s32x2_fill_scalar_safe(Y))
//	#define _simd_s32x2_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_s32x1_sub_safe
//	#define _simd_s32x1_sub_safe(X,Y) (X - Y)
//	#define _simd_s32x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_s32x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_sub_enabled() true
//#endif
//
//#define _simd_s32x4_sub_safe(X,Y)_simd_s32x4_combine_safe(\
//	_simd_s32x2_sub_safe(_simd_s32x4_splitlo_safe(X), _simd_ s32x4_splitlo_safe(Y)),\
//	_simd_s32x2_sub_safe(_simd_s32x4_splithi_safe(X), _simd_ s32x4_splithi_safe(Y)))
//#ifdef _simd_s32x4_sub_
//	#define _simd_s32x4_sub(X,Y) _simd_s32x4_sub_(X, Y)
//	#define _simd_s32x4_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_sub_instruction_set>()
//#elif defined(_simd_s32x8_sub_)
//	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_sub(const register _simd_s32x4 x, const register _simd_s32x4 y) {
//		union SIMDUnion { _simd_s32x4 v1; _simd_s32x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x8_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x4_sub_enable() _simd_s32x8_sub_enable()
//#elif defined(_simd_s32x16_sub_)
//	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_sub(const register _simd_s32x4 x, const register _simd_s32x4 y) {
//		union SIMDUnion { _simd_s32x4 v1; _simd_s32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x16_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x4_sub_enable() _simd_s32x16_sub_enable()
//#elif defined(_simd_s32x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_sub(const register _simd_s32x4 x, const register _simd_s32x4 y) {
//		union SIMDUnion { _simd_s32x4 v1; _simd_s32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x4_sub_enable() _simd_s32x32_sub_enable()
//#elif defined(_simd_s32x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_sub(const register _simd_s32x4 x, const register _simd_s32x4 y) {
//		union SIMDUnion { _simd_s32x4 v1; _simd_s32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x4_sub_enable() _simd_s32x64_sub_enable()
//#else
//	#define _simd_s32x4_sub(X,Y) _simd_s32x4_combine(\
//		_simd_s32x2_sub(_simd_s32x4_splitlo(X), _simd_s32x4_splitlo(Y)),\
//		_simd_s32x2_sub(_simd_s32x4_splithi(X), _simd_s32x4_splithi(Y)))
//	#define _simd_s32x4_sub_enable() (_simd_s32x2_sub_enable() && _simd_s32x4_combine_enable() && _simd_s32x4_splitlo_enable()  && _simd_s32x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x4_sub_) && ! defined(_simd_s32x4_sub_scalar_)
//	#define _simd_s32x4_sub_scalar_(X,Y) _simd_s32x4_sub_(X,_simd_s32x4_fill_scalar_(Y))
//	#define _simd_s32x4_sub_scalar_instruction_set _simd_s32x4_sub_instruction_set
//#endif
//#ifdef _simd_s32x4_sub_scalar_
//	#define _simd_s32x4_sub_scalar(X,Y) _simd_s32x4_sub_scalar_(X,Y)
//	#define _simd_s32x4_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_sub_scalar_instruction_set>()
//#else
//	#define _simd_s32x4_sub_scalar(X,Y) _simd_s32x4_sub_safe(X,_simd_s32x4_fill_scalar_safe(Y))
//	#define _simd_s32x4_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_s32x1_sub_safe
//	#define _simd_s32x1_sub_safe(X,Y) (X - Y)
//	#define _simd_s32x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_s32x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_sub_enabled() true
//#endif
//
//#define _simd_s32x8_sub_safe(X,Y)_simd_s32x8_combine_safe(\
//	_simd_s32x4_sub_safe(_simd_s32x8_splitlo_safe(X), _simd_ s32x8_splitlo_safe(Y)),\
//	_simd_s32x4_sub_safe(_simd_s32x8_splithi_safe(X), _simd_ s32x8_splithi_safe(Y)))
//#ifdef _simd_s32x8_sub_
//	#define _simd_s32x8_sub(X,Y) _simd_s32x8_sub_(X, Y)
//	#define _simd_s32x8_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_sub_instruction_set>()
//#elif defined(_simd_s32x16_sub_)
//	static ANVIL_STRONG_INLINE _simd_s32x8 ANVIL_SIMD_CALL _simd_s32x8_sub(const register _simd_s32x8 x, const register _simd_s32x8 y) {
//		union SIMDUnion { _simd_s32x8 v1; _simd_s32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x16_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x8_sub_enable() _simd_s32x16_sub_enable()
//#elif defined(_simd_s32x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_s32x8 ANVIL_SIMD_CALL _simd_s32x8_sub(const register _simd_s32x8 x, const register _simd_s32x8 y) {
//		union SIMDUnion { _simd_s32x8 v1; _simd_s32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x8_sub_enable() _simd_s32x32_sub_enable()
//#elif defined(_simd_s32x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_s32x8 ANVIL_SIMD_CALL _simd_s32x8_sub(const register _simd_s32x8 x, const register _simd_s32x8 y) {
//		union SIMDUnion { _simd_s32x8 v1; _simd_s32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x8_sub_enable() _simd_s32x64_sub_enable()
//#else
//	#define _simd_s32x8_sub(X,Y) _simd_s32x8_combine(\
//		_simd_s32x4_sub(_simd_s32x8_splitlo(X), _simd_s32x8_splitlo(Y)),\
//		_simd_s32x4_sub(_simd_s32x8_splithi(X), _simd_s32x8_splithi(Y)))
//	#define _simd_s32x8_sub_enable() (_simd_s32x4_sub_enable() && _simd_s32x8_combine_enable() && _simd_s32x8_splitlo_enable()  && _simd_s32x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x8_sub_) && ! defined(_simd_s32x8_sub_scalar_)
//	#define _simd_s32x8_sub_scalar_(X,Y) _simd_s32x8_sub_(X,_simd_s32x8_fill_scalar_(Y))
//	#define _simd_s32x8_sub_scalar_instruction_set _simd_s32x8_sub_instruction_set
//#endif
//#ifdef _simd_s32x8_sub_scalar_
//	#define _simd_s32x8_sub_scalar(X,Y) _simd_s32x8_sub_scalar_(X,Y)
//	#define _simd_s32x8_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_sub_scalar_instruction_set>()
//#else
//	#define _simd_s32x8_sub_scalar(X,Y) _simd_s32x8_sub_safe(X,_simd_s32x8_fill_scalar_safe(Y))
//	#define _simd_s32x8_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_s32x1_sub_safe
//	#define _simd_s32x1_sub_safe(X,Y) (X - Y)
//	#define _simd_s32x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_s32x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_sub_enabled() true
//#endif
//
//#define _simd_s32x16_sub_safe(X,Y)_simd_s32x16_combine_safe(\
//	_simd_s32x8_sub_safe(_simd_s32x16_splitlo_safe(X), _simd_ s32x16_splitlo_safe(Y)),\
//	_simd_s32x8_sub_safe(_simd_s32x16_splithi_safe(X), _simd_ s32x16_splithi_safe(Y)))
//#ifdef _simd_s32x16_sub_
//	#define _simd_s32x16_sub(X,Y) _simd_s32x16_sub_(X, Y)
//	#define _simd_s32x16_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_sub_instruction_set>()
//#elif defined(_simd_s32x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_s32x16 ANVIL_SIMD_CALL _simd_s32x16_sub(const register _simd_s32x16 x, const register _simd_s32x16 y) {
//		union SIMDUnion { _simd_s32x16 v1; _simd_s32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x16_sub_enable() _simd_s32x32_sub_enable()
//#elif defined(_simd_s32x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_s32x16 ANVIL_SIMD_CALL _simd_s32x16_sub(const register _simd_s32x16 x, const register _simd_s32x16 y) {
//		union SIMDUnion { _simd_s32x16 v1; _simd_s32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x16_sub_enable() _simd_s32x64_sub_enable()
//#else
//	#define _simd_s32x16_sub(X,Y) _simd_s32x16_combine(\
//		_simd_s32x8_sub(_simd_s32x16_splitlo(X), _simd_s32x16_splitlo(Y)),\
//		_simd_s32x8_sub(_simd_s32x16_splithi(X), _simd_s32x16_splithi(Y)))
//	#define _simd_s32x16_sub_enable() (_simd_s32x8_sub_enable() && _simd_s32x16_combine_enable() && _simd_s32x16_splitlo_enable()  && _simd_s32x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x16_sub_) && ! defined(_simd_s32x16_sub_scalar_)
//	#define _simd_s32x16_sub_scalar_(X,Y) _simd_s32x16_sub_(X,_simd_s32x16_fill_scalar_(Y))
//	#define _simd_s32x16_sub_scalar_instruction_set _simd_s32x16_sub_instruction_set
//#endif
//#ifdef _simd_s32x16_sub_scalar_
//	#define _simd_s32x16_sub_scalar(X,Y) _simd_s32x16_sub_scalar_(X,Y)
//	#define _simd_s32x16_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_sub_scalar_instruction_set>()
//#else
//	#define _simd_s32x16_sub_scalar(X,Y) _simd_s32x16_sub_safe(X,_simd_s32x16_fill_scalar_safe(Y))
//	#define _simd_s32x16_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_s32x1_sub_safe
//	#define _simd_s32x1_sub_safe(X,Y) (X - Y)
//	#define _simd_s32x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_s32x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_sub_enabled() true
//#endif
//
//#define _simd_s32x32_sub_safe(X,Y)_simd_s32x32_combine_safe(\
//	_simd_s32x16_sub_safe(_simd_s32x32_splitlo_safe(X), _simd_ s32x32_splitlo_safe(Y)),\
//	_simd_s32x16_sub_safe(_simd_s32x32_splithi_safe(X), _simd_ s32x32_splithi_safe(Y)))
//#ifdef _simd_s32x32_sub_
//	#define _simd_s32x32_sub(X,Y) _simd_s32x32_sub_(X, Y)
//	#define _simd_s32x32_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_sub_instruction_set>()
//#elif defined(_simd_s32x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_s32x32 ANVIL_SIMD_CALL _simd_s32x32_sub(const register _simd_s32x32 x, const register _simd_s32x32 y) {
//		union SIMDUnion { _simd_s32x32 v1; _simd_s32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x32_sub_enable() _simd_s32x64_sub_enable()
//#else
//	#define _simd_s32x32_sub(X,Y) _simd_s32x32_combine(\
//		_simd_s32x16_sub(_simd_s32x32_splitlo(X), _simd_s32x32_splitlo(Y)),\
//		_simd_s32x16_sub(_simd_s32x32_splithi(X), _simd_s32x32_splithi(Y)))
//	#define _simd_s32x32_sub_enable() (_simd_s32x16_sub_enable() && _simd_s32x32_combine_enable() && _simd_s32x32_splitlo_enable()  && _simd_s32x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x32_sub_) && ! defined(_simd_s32x32_sub_scalar_)
//	#define _simd_s32x32_sub_scalar_(X,Y) _simd_s32x32_sub_(X,_simd_s32x32_fill_scalar_(Y))
//	#define _simd_s32x32_sub_scalar_instruction_set _simd_s32x32_sub_instruction_set
//#endif
//#ifdef _simd_s32x32_sub_scalar_
//	#define _simd_s32x32_sub_scalar(X,Y) _simd_s32x32_sub_scalar_(X,Y)
//	#define _simd_s32x32_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_sub_scalar_instruction_set>()
//#else
//	#define _simd_s32x32_sub_scalar(X,Y) _simd_s32x32_sub_safe(X,_simd_s32x32_fill_scalar_safe(Y))
//	#define _simd_s32x32_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_s32x1_sub_safe
//	#define _simd_s32x1_sub_safe(X,Y) (X - Y)
//	#define _simd_s32x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_s32x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_sub_enabled() true
//#endif
//
//#define _simd_s32x64_sub_safe(X,Y)_simd_s32x64_combine_safe(\
//	_simd_s32x32_sub_safe(_simd_s32x64_splitlo_safe(X), _simd_ s32x64_splitlo_safe(Y)),\
//	_simd_s32x32_sub_safe(_simd_s32x64_splithi_safe(X), _simd_ s32x64_splithi_safe(Y)))
//#ifdef _simd_s32x64_sub_
//	#define _simd_s32x64_sub(X,Y) _simd_s32x64_sub_(X, Y)
//	#define _simd_s32x64_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_sub_instruction_set>()
//#else
//	#define _simd_s32x64_sub(X,Y) _simd_s32x64_combine(\
//		_simd_s32x32_sub(_simd_s32x64_splitlo(X), _simd_s32x64_splitlo(Y)),\
//		_simd_s32x32_sub(_simd_s32x64_splithi(X), _simd_s32x64_splithi(Y)))
//	#define _simd_s32x64_sub_enable() (_simd_s32x32_sub_enable() && _simd_s32x64_combine_enable() && _simd_s32x64_splitlo_enable()  && _simd_s32x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x64_sub_) && ! defined(_simd_s32x64_sub_scalar_)
//	#define _simd_s32x64_sub_scalar_(X,Y) _simd_s32x64_sub_(X,_simd_s32x64_fill_scalar_(Y))
//	#define _simd_s32x64_sub_scalar_instruction_set _simd_s32x64_sub_instruction_set
//#endif
//#ifdef _simd_s32x64_sub_scalar_
//	#define _simd_s32x64_sub_scalar(X,Y) _simd_s32x64_sub_scalar_(X,Y)
//	#define _simd_s32x64_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_sub_scalar_instruction_set>()
//#else
//	#define _simd_s32x64_sub_scalar(X,Y) _simd_s32x64_sub_safe(X,_simd_s32x64_fill_scalar_safe(Y))
//	#define _simd_s32x64_sub_scalar_enabled() true
//#endif
//
//// -- u32 --
//
//#ifndef _simd_u32x1_sub_safe
//	#define _simd_u32x1_sub_safe(X,Y) (X - Y)
//	#define _simd_u32x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_u32x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_sub_enabled() true
//#endif
//
//#define _simd_u32x2_sub_safe(X,Y)_simd_u32x2_combine_safe(\
//	_simd_u32x1_sub_safe(_simd_u32x2_splitlo_safe(X), _simd_ u32x2_splitlo_safe(Y)),\
//	_simd_u32x1_sub_safe(_simd_u32x2_splithi_safe(X), _simd_ u32x2_splithi_safe(Y)))
//#ifdef _simd_u32x2_sub_
//	#define _simd_u32x2_sub(X,Y) _simd_u32x2_sub_(X, Y)
//	#define _simd_u32x2_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_sub_instruction_set>()
//#elif defined(_simd_u32x4_sub_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_sub(const register _simd_u32x2 x, const register _simd_u32x2 y) {
//		union SIMDUnion { _simd_u32x2 v1; _simd_u32x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x4_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x2_sub_enable() _simd_u32x4_sub_enable()
//#elif defined(_simd_u32x8_sub_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_sub(const register _simd_u32x2 x, const register _simd_u32x2 y) {
//		union SIMDUnion { _simd_u32x2 v1; _simd_u32x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x8_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x2_sub_enable() _simd_u32x8_sub_enable()
//#elif defined(_simd_u32x16_sub_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_sub(const register _simd_u32x2 x, const register _simd_u32x2 y) {
//		union SIMDUnion { _simd_u32x2 v1; _simd_u32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x16_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x2_sub_enable() _simd_u32x16_sub_enable()
//#elif defined(_simd_u32x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_sub(const register _simd_u32x2 x, const register _simd_u32x2 y) {
//		union SIMDUnion { _simd_u32x2 v1; _simd_u32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x2_sub_enable() _simd_u32x32_sub_enable()
//#elif defined(_simd_u32x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_sub(const register _simd_u32x2 x, const register _simd_u32x2 y) {
//		union SIMDUnion { _simd_u32x2 v1; _simd_u32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x2_sub_enable() _simd_u32x64_sub_enable()
//#else
//	#define _simd_u32x2_sub(X,Y) _simd_u32x2_combine(\
//		_simd_u32x1_sub(_simd_u32x2_splitlo(X), _simd_u32x2_splitlo(Y)),\
//		_simd_u32x1_sub(_simd_u32x2_splithi(X), _simd_u32x2_splithi(Y)))
//	#define _simd_u32x2_sub_enable() (_simd_u32x1_sub_enable() && _simd_u32x2_combine_enable() && _simd_u32x2_splitlo_enable()  && _simd_u32x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x2_sub_) && ! defined(_simd_u32x2_sub_scalar_)
//	#define _simd_u32x2_sub_scalar_(X,Y) _simd_u32x2_sub_(X,_simd_u32x2_fill_scalar_(Y))
//	#define _simd_u32x2_sub_scalar_instruction_set _simd_u32x2_sub_instruction_set
//#endif
//#ifdef _simd_u32x2_sub_scalar_
//	#define _simd_u32x2_sub_scalar(X,Y) _simd_u32x2_sub_scalar_(X,Y)
//	#define _simd_u32x2_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_sub_scalar_instruction_set>()
//#else
//	#define _simd_u32x2_sub_scalar(X,Y) _simd_u32x2_sub_safe(X,_simd_u32x2_fill_scalar_safe(Y))
//	#define _simd_u32x2_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_u32x1_sub_safe
//	#define _simd_u32x1_sub_safe(X,Y) (X - Y)
//	#define _simd_u32x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_u32x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_sub_enabled() true
//#endif
//
//#define _simd_u32x4_sub_safe(X,Y)_simd_u32x4_combine_safe(\
//	_simd_u32x2_sub_safe(_simd_u32x4_splitlo_safe(X), _simd_ u32x4_splitlo_safe(Y)),\
//	_simd_u32x2_sub_safe(_simd_u32x4_splithi_safe(X), _simd_ u32x4_splithi_safe(Y)))
//#ifdef _simd_u32x4_sub_
//	#define _simd_u32x4_sub(X,Y) _simd_u32x4_sub_(X, Y)
//	#define _simd_u32x4_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_sub_instruction_set>()
//#elif defined(_simd_u32x8_sub_)
//	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_sub(const register _simd_u32x4 x, const register _simd_u32x4 y) {
//		union SIMDUnion { _simd_u32x4 v1; _simd_u32x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x8_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x4_sub_enable() _simd_u32x8_sub_enable()
//#elif defined(_simd_u32x16_sub_)
//	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_sub(const register _simd_u32x4 x, const register _simd_u32x4 y) {
//		union SIMDUnion { _simd_u32x4 v1; _simd_u32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x16_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x4_sub_enable() _simd_u32x16_sub_enable()
//#elif defined(_simd_u32x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_sub(const register _simd_u32x4 x, const register _simd_u32x4 y) {
//		union SIMDUnion { _simd_u32x4 v1; _simd_u32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x4_sub_enable() _simd_u32x32_sub_enable()
//#elif defined(_simd_u32x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_sub(const register _simd_u32x4 x, const register _simd_u32x4 y) {
//		union SIMDUnion { _simd_u32x4 v1; _simd_u32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x4_sub_enable() _simd_u32x64_sub_enable()
//#else
//	#define _simd_u32x4_sub(X,Y) _simd_u32x4_combine(\
//		_simd_u32x2_sub(_simd_u32x4_splitlo(X), _simd_u32x4_splitlo(Y)),\
//		_simd_u32x2_sub(_simd_u32x4_splithi(X), _simd_u32x4_splithi(Y)))
//	#define _simd_u32x4_sub_enable() (_simd_u32x2_sub_enable() && _simd_u32x4_combine_enable() && _simd_u32x4_splitlo_enable()  && _simd_u32x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x4_sub_) && ! defined(_simd_u32x4_sub_scalar_)
//	#define _simd_u32x4_sub_scalar_(X,Y) _simd_u32x4_sub_(X,_simd_u32x4_fill_scalar_(Y))
//	#define _simd_u32x4_sub_scalar_instruction_set _simd_u32x4_sub_instruction_set
//#endif
//#ifdef _simd_u32x4_sub_scalar_
//	#define _simd_u32x4_sub_scalar(X,Y) _simd_u32x4_sub_scalar_(X,Y)
//	#define _simd_u32x4_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_sub_scalar_instruction_set>()
//#else
//	#define _simd_u32x4_sub_scalar(X,Y) _simd_u32x4_sub_safe(X,_simd_u32x4_fill_scalar_safe(Y))
//	#define _simd_u32x4_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_u32x1_sub_safe
//	#define _simd_u32x1_sub_safe(X,Y) (X - Y)
//	#define _simd_u32x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_u32x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_sub_enabled() true
//#endif
//
//#define _simd_u32x8_sub_safe(X,Y)_simd_u32x8_combine_safe(\
//	_simd_u32x4_sub_safe(_simd_u32x8_splitlo_safe(X), _simd_ u32x8_splitlo_safe(Y)),\
//	_simd_u32x4_sub_safe(_simd_u32x8_splithi_safe(X), _simd_ u32x8_splithi_safe(Y)))
//#ifdef _simd_u32x8_sub_
//	#define _simd_u32x8_sub(X,Y) _simd_u32x8_sub_(X, Y)
//	#define _simd_u32x8_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_sub_instruction_set>()
//#elif defined(_simd_u32x16_sub_)
//	static ANVIL_STRONG_INLINE _simd_u32x8 ANVIL_SIMD_CALL _simd_u32x8_sub(const register _simd_u32x8 x, const register _simd_u32x8 y) {
//		union SIMDUnion { _simd_u32x8 v1; _simd_u32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x16_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x8_sub_enable() _simd_u32x16_sub_enable()
//#elif defined(_simd_u32x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_u32x8 ANVIL_SIMD_CALL _simd_u32x8_sub(const register _simd_u32x8 x, const register _simd_u32x8 y) {
//		union SIMDUnion { _simd_u32x8 v1; _simd_u32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x8_sub_enable() _simd_u32x32_sub_enable()
//#elif defined(_simd_u32x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_u32x8 ANVIL_SIMD_CALL _simd_u32x8_sub(const register _simd_u32x8 x, const register _simd_u32x8 y) {
//		union SIMDUnion { _simd_u32x8 v1; _simd_u32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x8_sub_enable() _simd_u32x64_sub_enable()
//#else
//	#define _simd_u32x8_sub(X,Y) _simd_u32x8_combine(\
//		_simd_u32x4_sub(_simd_u32x8_splitlo(X), _simd_u32x8_splitlo(Y)),\
//		_simd_u32x4_sub(_simd_u32x8_splithi(X), _simd_u32x8_splithi(Y)))
//	#define _simd_u32x8_sub_enable() (_simd_u32x4_sub_enable() && _simd_u32x8_combine_enable() && _simd_u32x8_splitlo_enable()  && _simd_u32x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x8_sub_) && ! defined(_simd_u32x8_sub_scalar_)
//	#define _simd_u32x8_sub_scalar_(X,Y) _simd_u32x8_sub_(X,_simd_u32x8_fill_scalar_(Y))
//	#define _simd_u32x8_sub_scalar_instruction_set _simd_u32x8_sub_instruction_set
//#endif
//#ifdef _simd_u32x8_sub_scalar_
//	#define _simd_u32x8_sub_scalar(X,Y) _simd_u32x8_sub_scalar_(X,Y)
//	#define _simd_u32x8_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_sub_scalar_instruction_set>()
//#else
//	#define _simd_u32x8_sub_scalar(X,Y) _simd_u32x8_sub_safe(X,_simd_u32x8_fill_scalar_safe(Y))
//	#define _simd_u32x8_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_u32x1_sub_safe
//	#define _simd_u32x1_sub_safe(X,Y) (X - Y)
//	#define _simd_u32x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_u32x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_sub_enabled() true
//#endif
//
//#define _simd_u32x16_sub_safe(X,Y)_simd_u32x16_combine_safe(\
//	_simd_u32x8_sub_safe(_simd_u32x16_splitlo_safe(X), _simd_ u32x16_splitlo_safe(Y)),\
//	_simd_u32x8_sub_safe(_simd_u32x16_splithi_safe(X), _simd_ u32x16_splithi_safe(Y)))
//#ifdef _simd_u32x16_sub_
//	#define _simd_u32x16_sub(X,Y) _simd_u32x16_sub_(X, Y)
//	#define _simd_u32x16_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_sub_instruction_set>()
//#elif defined(_simd_u32x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_u32x16 ANVIL_SIMD_CALL _simd_u32x16_sub(const register _simd_u32x16 x, const register _simd_u32x16 y) {
//		union SIMDUnion { _simd_u32x16 v1; _simd_u32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x16_sub_enable() _simd_u32x32_sub_enable()
//#elif defined(_simd_u32x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_u32x16 ANVIL_SIMD_CALL _simd_u32x16_sub(const register _simd_u32x16 x, const register _simd_u32x16 y) {
//		union SIMDUnion { _simd_u32x16 v1; _simd_u32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x16_sub_enable() _simd_u32x64_sub_enable()
//#else
//	#define _simd_u32x16_sub(X,Y) _simd_u32x16_combine(\
//		_simd_u32x8_sub(_simd_u32x16_splitlo(X), _simd_u32x16_splitlo(Y)),\
//		_simd_u32x8_sub(_simd_u32x16_splithi(X), _simd_u32x16_splithi(Y)))
//	#define _simd_u32x16_sub_enable() (_simd_u32x8_sub_enable() && _simd_u32x16_combine_enable() && _simd_u32x16_splitlo_enable()  && _simd_u32x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x16_sub_) && ! defined(_simd_u32x16_sub_scalar_)
//	#define _simd_u32x16_sub_scalar_(X,Y) _simd_u32x16_sub_(X,_simd_u32x16_fill_scalar_(Y))
//	#define _simd_u32x16_sub_scalar_instruction_set _simd_u32x16_sub_instruction_set
//#endif
//#ifdef _simd_u32x16_sub_scalar_
//	#define _simd_u32x16_sub_scalar(X,Y) _simd_u32x16_sub_scalar_(X,Y)
//	#define _simd_u32x16_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_sub_scalar_instruction_set>()
//#else
//	#define _simd_u32x16_sub_scalar(X,Y) _simd_u32x16_sub_safe(X,_simd_u32x16_fill_scalar_safe(Y))
//	#define _simd_u32x16_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_u32x1_sub_safe
//	#define _simd_u32x1_sub_safe(X,Y) (X - Y)
//	#define _simd_u32x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_u32x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_sub_enabled() true
//#endif
//
//#define _simd_u32x32_sub_safe(X,Y)_simd_u32x32_combine_safe(\
//	_simd_u32x16_sub_safe(_simd_u32x32_splitlo_safe(X), _simd_ u32x32_splitlo_safe(Y)),\
//	_simd_u32x16_sub_safe(_simd_u32x32_splithi_safe(X), _simd_ u32x32_splithi_safe(Y)))
//#ifdef _simd_u32x32_sub_
//	#define _simd_u32x32_sub(X,Y) _simd_u32x32_sub_(X, Y)
//	#define _simd_u32x32_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_sub_instruction_set>()
//#elif defined(_simd_u32x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_u32x32 ANVIL_SIMD_CALL _simd_u32x32_sub(const register _simd_u32x32 x, const register _simd_u32x32 y) {
//		union SIMDUnion { _simd_u32x32 v1; _simd_u32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x32_sub_enable() _simd_u32x64_sub_enable()
//#else
//	#define _simd_u32x32_sub(X,Y) _simd_u32x32_combine(\
//		_simd_u32x16_sub(_simd_u32x32_splitlo(X), _simd_u32x32_splitlo(Y)),\
//		_simd_u32x16_sub(_simd_u32x32_splithi(X), _simd_u32x32_splithi(Y)))
//	#define _simd_u32x32_sub_enable() (_simd_u32x16_sub_enable() && _simd_u32x32_combine_enable() && _simd_u32x32_splitlo_enable()  && _simd_u32x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x32_sub_) && ! defined(_simd_u32x32_sub_scalar_)
//	#define _simd_u32x32_sub_scalar_(X,Y) _simd_u32x32_sub_(X,_simd_u32x32_fill_scalar_(Y))
//	#define _simd_u32x32_sub_scalar_instruction_set _simd_u32x32_sub_instruction_set
//#endif
//#ifdef _simd_u32x32_sub_scalar_
//	#define _simd_u32x32_sub_scalar(X,Y) _simd_u32x32_sub_scalar_(X,Y)
//	#define _simd_u32x32_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_sub_scalar_instruction_set>()
//#else
//	#define _simd_u32x32_sub_scalar(X,Y) _simd_u32x32_sub_safe(X,_simd_u32x32_fill_scalar_safe(Y))
//	#define _simd_u32x32_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_u32x1_sub_safe
//	#define _simd_u32x1_sub_safe(X,Y) (X - Y)
//	#define _simd_u32x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_u32x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_sub_enabled() true
//#endif
//
//#define _simd_u32x64_sub_safe(X,Y)_simd_u32x64_combine_safe(\
//	_simd_u32x32_sub_safe(_simd_u32x64_splitlo_safe(X), _simd_ u32x64_splitlo_safe(Y)),\
//	_simd_u32x32_sub_safe(_simd_u32x64_splithi_safe(X), _simd_ u32x64_splithi_safe(Y)))
//#ifdef _simd_u32x64_sub_
//	#define _simd_u32x64_sub(X,Y) _simd_u32x64_sub_(X, Y)
//	#define _simd_u32x64_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_sub_instruction_set>()
//#else
//	#define _simd_u32x64_sub(X,Y) _simd_u32x64_combine(\
//		_simd_u32x32_sub(_simd_u32x64_splitlo(X), _simd_u32x64_splitlo(Y)),\
//		_simd_u32x32_sub(_simd_u32x64_splithi(X), _simd_u32x64_splithi(Y)))
//	#define _simd_u32x64_sub_enable() (_simd_u32x32_sub_enable() && _simd_u32x64_combine_enable() && _simd_u32x64_splitlo_enable()  && _simd_u32x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x64_sub_) && ! defined(_simd_u32x64_sub_scalar_)
//	#define _simd_u32x64_sub_scalar_(X,Y) _simd_u32x64_sub_(X,_simd_u32x64_fill_scalar_(Y))
//	#define _simd_u32x64_sub_scalar_instruction_set _simd_u32x64_sub_instruction_set
//#endif
//#ifdef _simd_u32x64_sub_scalar_
//	#define _simd_u32x64_sub_scalar(X,Y) _simd_u32x64_sub_scalar_(X,Y)
//	#define _simd_u32x64_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_sub_scalar_instruction_set>()
//#else
//	#define _simd_u32x64_sub_scalar(X,Y) _simd_u32x64_sub_safe(X,_simd_u32x64_fill_scalar_safe(Y))
//	#define _simd_u32x64_sub_scalar_enabled() true
//#endif
//
//// -- s16 --
//
//#ifndef _simd_s16x1_sub_safe
//	#define _simd_s16x1_sub_safe(X,Y) (X - Y)
//	#define _simd_s16x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_s16x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_sub_enabled() true
//#endif
//
//#define _simd_s16x2_sub_safe(X,Y)_simd_s16x2_combine_safe(\
//	_simd_s16x1_sub_safe(_simd_s16x2_splitlo_safe(X), _simd_ s16x2_splitlo_safe(Y)),\
//	_simd_s16x1_sub_safe(_simd_s16x2_splithi_safe(X), _simd_ s16x2_splithi_safe(Y)))
//#ifdef _simd_s16x2_sub_
//	#define _simd_s16x2_sub(X,Y) _simd_s16x2_sub_(X, Y)
//	#define _simd_s16x2_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_sub_instruction_set>()
//#elif defined(_simd_s16x4_sub_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_sub(const register _simd_s16x2 x, const register _simd_s16x2 y) {
//		union SIMDUnion { _simd_s16x2 v1; _simd_s16x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x4_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x2_sub_enable() _simd_s16x4_sub_enable()
//#elif defined(_simd_s16x8_sub_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_sub(const register _simd_s16x2 x, const register _simd_s16x2 y) {
//		union SIMDUnion { _simd_s16x2 v1; _simd_s16x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x8_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x2_sub_enable() _simd_s16x8_sub_enable()
//#elif defined(_simd_s16x16_sub_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_sub(const register _simd_s16x2 x, const register _simd_s16x2 y) {
//		union SIMDUnion { _simd_s16x2 v1; _simd_s16x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x16_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x2_sub_enable() _simd_s16x16_sub_enable()
//#elif defined(_simd_s16x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_sub(const register _simd_s16x2 x, const register _simd_s16x2 y) {
//		union SIMDUnion { _simd_s16x2 v1; _simd_s16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x2_sub_enable() _simd_s16x32_sub_enable()
//#elif defined(_simd_s16x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_sub(const register _simd_s16x2 x, const register _simd_s16x2 y) {
//		union SIMDUnion { _simd_s16x2 v1; _simd_s16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x2_sub_enable() _simd_s16x64_sub_enable()
//#else
//	#define _simd_s16x2_sub(X,Y) _simd_s16x2_combine(\
//		_simd_s16x1_sub(_simd_s16x2_splitlo(X), _simd_s16x2_splitlo(Y)),\
//		_simd_s16x1_sub(_simd_s16x2_splithi(X), _simd_s16x2_splithi(Y)))
//	#define _simd_s16x2_sub_enable() (_simd_s16x1_sub_enable() && _simd_s16x2_combine_enable() && _simd_s16x2_splitlo_enable()  && _simd_s16x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x2_sub_) && ! defined(_simd_s16x2_sub_scalar_)
//	#define _simd_s16x2_sub_scalar_(X,Y) _simd_s16x2_sub_(X,_simd_s16x2_fill_scalar_(Y))
//	#define _simd_s16x2_sub_scalar_instruction_set _simd_s16x2_sub_instruction_set
//#endif
//#ifdef _simd_s16x2_sub_scalar_
//	#define _simd_s16x2_sub_scalar(X,Y) _simd_s16x2_sub_scalar_(X,Y)
//	#define _simd_s16x2_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_sub_scalar_instruction_set>()
//#else
//	#define _simd_s16x2_sub_scalar(X,Y) _simd_s16x2_sub_safe(X,_simd_s16x2_fill_scalar_safe(Y))
//	#define _simd_s16x2_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_s16x1_sub_safe
//	#define _simd_s16x1_sub_safe(X,Y) (X - Y)
//	#define _simd_s16x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_s16x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_sub_enabled() true
//#endif
//
//#define _simd_s16x4_sub_safe(X,Y)_simd_s16x4_combine_safe(\
//	_simd_s16x2_sub_safe(_simd_s16x4_splitlo_safe(X), _simd_ s16x4_splitlo_safe(Y)),\
//	_simd_s16x2_sub_safe(_simd_s16x4_splithi_safe(X), _simd_ s16x4_splithi_safe(Y)))
//#ifdef _simd_s16x4_sub_
//	#define _simd_s16x4_sub(X,Y) _simd_s16x4_sub_(X, Y)
//	#define _simd_s16x4_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_sub_instruction_set>()
//#elif defined(_simd_s16x8_sub_)
//	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_sub(const register _simd_s16x4 x, const register _simd_s16x4 y) {
//		union SIMDUnion { _simd_s16x4 v1; _simd_s16x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x8_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x4_sub_enable() _simd_s16x8_sub_enable()
//#elif defined(_simd_s16x16_sub_)
//	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_sub(const register _simd_s16x4 x, const register _simd_s16x4 y) {
//		union SIMDUnion { _simd_s16x4 v1; _simd_s16x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x16_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x4_sub_enable() _simd_s16x16_sub_enable()
//#elif defined(_simd_s16x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_sub(const register _simd_s16x4 x, const register _simd_s16x4 y) {
//		union SIMDUnion { _simd_s16x4 v1; _simd_s16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x4_sub_enable() _simd_s16x32_sub_enable()
//#elif defined(_simd_s16x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_sub(const register _simd_s16x4 x, const register _simd_s16x4 y) {
//		union SIMDUnion { _simd_s16x4 v1; _simd_s16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x4_sub_enable() _simd_s16x64_sub_enable()
//#else
//	#define _simd_s16x4_sub(X,Y) _simd_s16x4_combine(\
//		_simd_s16x2_sub(_simd_s16x4_splitlo(X), _simd_s16x4_splitlo(Y)),\
//		_simd_s16x2_sub(_simd_s16x4_splithi(X), _simd_s16x4_splithi(Y)))
//	#define _simd_s16x4_sub_enable() (_simd_s16x2_sub_enable() && _simd_s16x4_combine_enable() && _simd_s16x4_splitlo_enable()  && _simd_s16x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x4_sub_) && ! defined(_simd_s16x4_sub_scalar_)
//	#define _simd_s16x4_sub_scalar_(X,Y) _simd_s16x4_sub_(X,_simd_s16x4_fill_scalar_(Y))
//	#define _simd_s16x4_sub_scalar_instruction_set _simd_s16x4_sub_instruction_set
//#endif
//#ifdef _simd_s16x4_sub_scalar_
//	#define _simd_s16x4_sub_scalar(X,Y) _simd_s16x4_sub_scalar_(X,Y)
//	#define _simd_s16x4_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_sub_scalar_instruction_set>()
//#else
//	#define _simd_s16x4_sub_scalar(X,Y) _simd_s16x4_sub_safe(X,_simd_s16x4_fill_scalar_safe(Y))
//	#define _simd_s16x4_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_s16x1_sub_safe
//	#define _simd_s16x1_sub_safe(X,Y) (X - Y)
//	#define _simd_s16x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_s16x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_sub_enabled() true
//#endif
//
//#define _simd_s16x8_sub_safe(X,Y)_simd_s16x8_combine_safe(\
//	_simd_s16x4_sub_safe(_simd_s16x8_splitlo_safe(X), _simd_ s16x8_splitlo_safe(Y)),\
//	_simd_s16x4_sub_safe(_simd_s16x8_splithi_safe(X), _simd_ s16x8_splithi_safe(Y)))
//#ifdef _simd_s16x8_sub_
//	#define _simd_s16x8_sub(X,Y) _simd_s16x8_sub_(X, Y)
//	#define _simd_s16x8_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_sub_instruction_set>()
//#elif defined(_simd_s16x16_sub_)
//	static ANVIL_STRONG_INLINE _simd_s16x8 ANVIL_SIMD_CALL _simd_s16x8_sub(const register _simd_s16x8 x, const register _simd_s16x8 y) {
//		union SIMDUnion { _simd_s16x8 v1; _simd_s16x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x16_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x8_sub_enable() _simd_s16x16_sub_enable()
//#elif defined(_simd_s16x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_s16x8 ANVIL_SIMD_CALL _simd_s16x8_sub(const register _simd_s16x8 x, const register _simd_s16x8 y) {
//		union SIMDUnion { _simd_s16x8 v1; _simd_s16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x8_sub_enable() _simd_s16x32_sub_enable()
//#elif defined(_simd_s16x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_s16x8 ANVIL_SIMD_CALL _simd_s16x8_sub(const register _simd_s16x8 x, const register _simd_s16x8 y) {
//		union SIMDUnion { _simd_s16x8 v1; _simd_s16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x8_sub_enable() _simd_s16x64_sub_enable()
//#else
//	#define _simd_s16x8_sub(X,Y) _simd_s16x8_combine(\
//		_simd_s16x4_sub(_simd_s16x8_splitlo(X), _simd_s16x8_splitlo(Y)),\
//		_simd_s16x4_sub(_simd_s16x8_splithi(X), _simd_s16x8_splithi(Y)))
//	#define _simd_s16x8_sub_enable() (_simd_s16x4_sub_enable() && _simd_s16x8_combine_enable() && _simd_s16x8_splitlo_enable()  && _simd_s16x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x8_sub_) && ! defined(_simd_s16x8_sub_scalar_)
//	#define _simd_s16x8_sub_scalar_(X,Y) _simd_s16x8_sub_(X,_simd_s16x8_fill_scalar_(Y))
//	#define _simd_s16x8_sub_scalar_instruction_set _simd_s16x8_sub_instruction_set
//#endif
//#ifdef _simd_s16x8_sub_scalar_
//	#define _simd_s16x8_sub_scalar(X,Y) _simd_s16x8_sub_scalar_(X,Y)
//	#define _simd_s16x8_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_sub_scalar_instruction_set>()
//#else
//	#define _simd_s16x8_sub_scalar(X,Y) _simd_s16x8_sub_safe(X,_simd_s16x8_fill_scalar_safe(Y))
//	#define _simd_s16x8_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_s16x1_sub_safe
//	#define _simd_s16x1_sub_safe(X,Y) (X - Y)
//	#define _simd_s16x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_s16x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_sub_enabled() true
//#endif
//
//#define _simd_s16x16_sub_safe(X,Y)_simd_s16x16_combine_safe(\
//	_simd_s16x8_sub_safe(_simd_s16x16_splitlo_safe(X), _simd_ s16x16_splitlo_safe(Y)),\
//	_simd_s16x8_sub_safe(_simd_s16x16_splithi_safe(X), _simd_ s16x16_splithi_safe(Y)))
//#ifdef _simd_s16x16_sub_
//	#define _simd_s16x16_sub(X,Y) _simd_s16x16_sub_(X, Y)
//	#define _simd_s16x16_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_sub_instruction_set>()
//#elif defined(_simd_s16x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_s16x16 ANVIL_SIMD_CALL _simd_s16x16_sub(const register _simd_s16x16 x, const register _simd_s16x16 y) {
//		union SIMDUnion { _simd_s16x16 v1; _simd_s16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x16_sub_enable() _simd_s16x32_sub_enable()
//#elif defined(_simd_s16x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_s16x16 ANVIL_SIMD_CALL _simd_s16x16_sub(const register _simd_s16x16 x, const register _simd_s16x16 y) {
//		union SIMDUnion { _simd_s16x16 v1; _simd_s16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x16_sub_enable() _simd_s16x64_sub_enable()
//#else
//	#define _simd_s16x16_sub(X,Y) _simd_s16x16_combine(\
//		_simd_s16x8_sub(_simd_s16x16_splitlo(X), _simd_s16x16_splitlo(Y)),\
//		_simd_s16x8_sub(_simd_s16x16_splithi(X), _simd_s16x16_splithi(Y)))
//	#define _simd_s16x16_sub_enable() (_simd_s16x8_sub_enable() && _simd_s16x16_combine_enable() && _simd_s16x16_splitlo_enable()  && _simd_s16x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x16_sub_) && ! defined(_simd_s16x16_sub_scalar_)
//	#define _simd_s16x16_sub_scalar_(X,Y) _simd_s16x16_sub_(X,_simd_s16x16_fill_scalar_(Y))
//	#define _simd_s16x16_sub_scalar_instruction_set _simd_s16x16_sub_instruction_set
//#endif
//#ifdef _simd_s16x16_sub_scalar_
//	#define _simd_s16x16_sub_scalar(X,Y) _simd_s16x16_sub_scalar_(X,Y)
//	#define _simd_s16x16_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_sub_scalar_instruction_set>()
//#else
//	#define _simd_s16x16_sub_scalar(X,Y) _simd_s16x16_sub_safe(X,_simd_s16x16_fill_scalar_safe(Y))
//	#define _simd_s16x16_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_s16x1_sub_safe
//	#define _simd_s16x1_sub_safe(X,Y) (X - Y)
//	#define _simd_s16x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_s16x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_sub_enabled() true
//#endif
//
//#define _simd_s16x32_sub_safe(X,Y)_simd_s16x32_combine_safe(\
//	_simd_s16x16_sub_safe(_simd_s16x32_splitlo_safe(X), _simd_ s16x32_splitlo_safe(Y)),\
//	_simd_s16x16_sub_safe(_simd_s16x32_splithi_safe(X), _simd_ s16x32_splithi_safe(Y)))
//#ifdef _simd_s16x32_sub_
//	#define _simd_s16x32_sub(X,Y) _simd_s16x32_sub_(X, Y)
//	#define _simd_s16x32_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_sub_instruction_set>()
//#elif defined(_simd_s16x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_s16x32 ANVIL_SIMD_CALL _simd_s16x32_sub(const register _simd_s16x32 x, const register _simd_s16x32 y) {
//		union SIMDUnion { _simd_s16x32 v1; _simd_s16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x32_sub_enable() _simd_s16x64_sub_enable()
//#else
//	#define _simd_s16x32_sub(X,Y) _simd_s16x32_combine(\
//		_simd_s16x16_sub(_simd_s16x32_splitlo(X), _simd_s16x32_splitlo(Y)),\
//		_simd_s16x16_sub(_simd_s16x32_splithi(X), _simd_s16x32_splithi(Y)))
//	#define _simd_s16x32_sub_enable() (_simd_s16x16_sub_enable() && _simd_s16x32_combine_enable() && _simd_s16x32_splitlo_enable()  && _simd_s16x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x32_sub_) && ! defined(_simd_s16x32_sub_scalar_)
//	#define _simd_s16x32_sub_scalar_(X,Y) _simd_s16x32_sub_(X,_simd_s16x32_fill_scalar_(Y))
//	#define _simd_s16x32_sub_scalar_instruction_set _simd_s16x32_sub_instruction_set
//#endif
//#ifdef _simd_s16x32_sub_scalar_
//	#define _simd_s16x32_sub_scalar(X,Y) _simd_s16x32_sub_scalar_(X,Y)
//	#define _simd_s16x32_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_sub_scalar_instruction_set>()
//#else
//	#define _simd_s16x32_sub_scalar(X,Y) _simd_s16x32_sub_safe(X,_simd_s16x32_fill_scalar_safe(Y))
//	#define _simd_s16x32_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_s16x1_sub_safe
//	#define _simd_s16x1_sub_safe(X,Y) (X - Y)
//	#define _simd_s16x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_s16x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_sub_enabled() true
//#endif
//
//#define _simd_s16x64_sub_safe(X,Y)_simd_s16x64_combine_safe(\
//	_simd_s16x32_sub_safe(_simd_s16x64_splitlo_safe(X), _simd_ s16x64_splitlo_safe(Y)),\
//	_simd_s16x32_sub_safe(_simd_s16x64_splithi_safe(X), _simd_ s16x64_splithi_safe(Y)))
//#ifdef _simd_s16x64_sub_
//	#define _simd_s16x64_sub(X,Y) _simd_s16x64_sub_(X, Y)
//	#define _simd_s16x64_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_sub_instruction_set>()
//#else
//	#define _simd_s16x64_sub(X,Y) _simd_s16x64_combine(\
//		_simd_s16x32_sub(_simd_s16x64_splitlo(X), _simd_s16x64_splitlo(Y)),\
//		_simd_s16x32_sub(_simd_s16x64_splithi(X), _simd_s16x64_splithi(Y)))
//	#define _simd_s16x64_sub_enable() (_simd_s16x32_sub_enable() && _simd_s16x64_combine_enable() && _simd_s16x64_splitlo_enable()  && _simd_s16x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x64_sub_) && ! defined(_simd_s16x64_sub_scalar_)
//	#define _simd_s16x64_sub_scalar_(X,Y) _simd_s16x64_sub_(X,_simd_s16x64_fill_scalar_(Y))
//	#define _simd_s16x64_sub_scalar_instruction_set _simd_s16x64_sub_instruction_set
//#endif
//#ifdef _simd_s16x64_sub_scalar_
//	#define _simd_s16x64_sub_scalar(X,Y) _simd_s16x64_sub_scalar_(X,Y)
//	#define _simd_s16x64_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_sub_scalar_instruction_set>()
//#else
//	#define _simd_s16x64_sub_scalar(X,Y) _simd_s16x64_sub_safe(X,_simd_s16x64_fill_scalar_safe(Y))
//	#define _simd_s16x64_sub_scalar_enabled() true
//#endif
//
//// -- u16 --
//
//#ifndef _simd_u16x1_sub_safe
//	#define _simd_u16x1_sub_safe(X,Y) (X - Y)
//	#define _simd_u16x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_u16x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_sub_enabled() true
//#endif
//
//#define _simd_u16x2_sub_safe(X,Y)_simd_u16x2_combine_safe(\
//	_simd_u16x1_sub_safe(_simd_u16x2_splitlo_safe(X), _simd_ u16x2_splitlo_safe(Y)),\
//	_simd_u16x1_sub_safe(_simd_u16x2_splithi_safe(X), _simd_ u16x2_splithi_safe(Y)))
//#ifdef _simd_u16x2_sub_
//	#define _simd_u16x2_sub(X,Y) _simd_u16x2_sub_(X, Y)
//	#define _simd_u16x2_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_sub_instruction_set>()
//#elif defined(_simd_u16x4_sub_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_sub(const register _simd_u16x2 x, const register _simd_u16x2 y) {
//		union SIMDUnion { _simd_u16x2 v1; _simd_u16x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x4_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x2_sub_enable() _simd_u16x4_sub_enable()
//#elif defined(_simd_u16x8_sub_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_sub(const register _simd_u16x2 x, const register _simd_u16x2 y) {
//		union SIMDUnion { _simd_u16x2 v1; _simd_u16x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x8_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x2_sub_enable() _simd_u16x8_sub_enable()
//#elif defined(_simd_u16x16_sub_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_sub(const register _simd_u16x2 x, const register _simd_u16x2 y) {
//		union SIMDUnion { _simd_u16x2 v1; _simd_u16x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x16_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x2_sub_enable() _simd_u16x16_sub_enable()
//#elif defined(_simd_u16x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_sub(const register _simd_u16x2 x, const register _simd_u16x2 y) {
//		union SIMDUnion { _simd_u16x2 v1; _simd_u16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x2_sub_enable() _simd_u16x32_sub_enable()
//#elif defined(_simd_u16x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_sub(const register _simd_u16x2 x, const register _simd_u16x2 y) {
//		union SIMDUnion { _simd_u16x2 v1; _simd_u16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x2_sub_enable() _simd_u16x64_sub_enable()
//#else
//	#define _simd_u16x2_sub(X,Y) _simd_u16x2_combine(\
//		_simd_u16x1_sub(_simd_u16x2_splitlo(X), _simd_u16x2_splitlo(Y)),\
//		_simd_u16x1_sub(_simd_u16x2_splithi(X), _simd_u16x2_splithi(Y)))
//	#define _simd_u16x2_sub_enable() (_simd_u16x1_sub_enable() && _simd_u16x2_combine_enable() && _simd_u16x2_splitlo_enable()  && _simd_u16x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x2_sub_) && ! defined(_simd_u16x2_sub_scalar_)
//	#define _simd_u16x2_sub_scalar_(X,Y) _simd_u16x2_sub_(X,_simd_u16x2_fill_scalar_(Y))
//	#define _simd_u16x2_sub_scalar_instruction_set _simd_u16x2_sub_instruction_set
//#endif
//#ifdef _simd_u16x2_sub_scalar_
//	#define _simd_u16x2_sub_scalar(X,Y) _simd_u16x2_sub_scalar_(X,Y)
//	#define _simd_u16x2_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_sub_scalar_instruction_set>()
//#else
//	#define _simd_u16x2_sub_scalar(X,Y) _simd_u16x2_sub_safe(X,_simd_u16x2_fill_scalar_safe(Y))
//	#define _simd_u16x2_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_u16x1_sub_safe
//	#define _simd_u16x1_sub_safe(X,Y) (X - Y)
//	#define _simd_u16x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_u16x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_sub_enabled() true
//#endif
//
//#define _simd_u16x4_sub_safe(X,Y)_simd_u16x4_combine_safe(\
//	_simd_u16x2_sub_safe(_simd_u16x4_splitlo_safe(X), _simd_ u16x4_splitlo_safe(Y)),\
//	_simd_u16x2_sub_safe(_simd_u16x4_splithi_safe(X), _simd_ u16x4_splithi_safe(Y)))
//#ifdef _simd_u16x4_sub_
//	#define _simd_u16x4_sub(X,Y) _simd_u16x4_sub_(X, Y)
//	#define _simd_u16x4_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_sub_instruction_set>()
//#elif defined(_simd_u16x8_sub_)
//	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_sub(const register _simd_u16x4 x, const register _simd_u16x4 y) {
//		union SIMDUnion { _simd_u16x4 v1; _simd_u16x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x8_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x4_sub_enable() _simd_u16x8_sub_enable()
//#elif defined(_simd_u16x16_sub_)
//	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_sub(const register _simd_u16x4 x, const register _simd_u16x4 y) {
//		union SIMDUnion { _simd_u16x4 v1; _simd_u16x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x16_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x4_sub_enable() _simd_u16x16_sub_enable()
//#elif defined(_simd_u16x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_sub(const register _simd_u16x4 x, const register _simd_u16x4 y) {
//		union SIMDUnion { _simd_u16x4 v1; _simd_u16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x4_sub_enable() _simd_u16x32_sub_enable()
//#elif defined(_simd_u16x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_sub(const register _simd_u16x4 x, const register _simd_u16x4 y) {
//		union SIMDUnion { _simd_u16x4 v1; _simd_u16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x4_sub_enable() _simd_u16x64_sub_enable()
//#else
//	#define _simd_u16x4_sub(X,Y) _simd_u16x4_combine(\
//		_simd_u16x2_sub(_simd_u16x4_splitlo(X), _simd_u16x4_splitlo(Y)),\
//		_simd_u16x2_sub(_simd_u16x4_splithi(X), _simd_u16x4_splithi(Y)))
//	#define _simd_u16x4_sub_enable() (_simd_u16x2_sub_enable() && _simd_u16x4_combine_enable() && _simd_u16x4_splitlo_enable()  && _simd_u16x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x4_sub_) && ! defined(_simd_u16x4_sub_scalar_)
//	#define _simd_u16x4_sub_scalar_(X,Y) _simd_u16x4_sub_(X,_simd_u16x4_fill_scalar_(Y))
//	#define _simd_u16x4_sub_scalar_instruction_set _simd_u16x4_sub_instruction_set
//#endif
//#ifdef _simd_u16x4_sub_scalar_
//	#define _simd_u16x4_sub_scalar(X,Y) _simd_u16x4_sub_scalar_(X,Y)
//	#define _simd_u16x4_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_sub_scalar_instruction_set>()
//#else
//	#define _simd_u16x4_sub_scalar(X,Y) _simd_u16x4_sub_safe(X,_simd_u16x4_fill_scalar_safe(Y))
//	#define _simd_u16x4_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_u16x1_sub_safe
//	#define _simd_u16x1_sub_safe(X,Y) (X - Y)
//	#define _simd_u16x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_u16x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_sub_enabled() true
//#endif
//
//#define _simd_u16x8_sub_safe(X,Y)_simd_u16x8_combine_safe(\
//	_simd_u16x4_sub_safe(_simd_u16x8_splitlo_safe(X), _simd_ u16x8_splitlo_safe(Y)),\
//	_simd_u16x4_sub_safe(_simd_u16x8_splithi_safe(X), _simd_ u16x8_splithi_safe(Y)))
//#ifdef _simd_u16x8_sub_
//	#define _simd_u16x8_sub(X,Y) _simd_u16x8_sub_(X, Y)
//	#define _simd_u16x8_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_sub_instruction_set>()
//#elif defined(_simd_u16x16_sub_)
//	static ANVIL_STRONG_INLINE _simd_u16x8 ANVIL_SIMD_CALL _simd_u16x8_sub(const register _simd_u16x8 x, const register _simd_u16x8 y) {
//		union SIMDUnion { _simd_u16x8 v1; _simd_u16x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x16_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x8_sub_enable() _simd_u16x16_sub_enable()
//#elif defined(_simd_u16x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_u16x8 ANVIL_SIMD_CALL _simd_u16x8_sub(const register _simd_u16x8 x, const register _simd_u16x8 y) {
//		union SIMDUnion { _simd_u16x8 v1; _simd_u16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x8_sub_enable() _simd_u16x32_sub_enable()
//#elif defined(_simd_u16x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_u16x8 ANVIL_SIMD_CALL _simd_u16x8_sub(const register _simd_u16x8 x, const register _simd_u16x8 y) {
//		union SIMDUnion { _simd_u16x8 v1; _simd_u16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x8_sub_enable() _simd_u16x64_sub_enable()
//#else
//	#define _simd_u16x8_sub(X,Y) _simd_u16x8_combine(\
//		_simd_u16x4_sub(_simd_u16x8_splitlo(X), _simd_u16x8_splitlo(Y)),\
//		_simd_u16x4_sub(_simd_u16x8_splithi(X), _simd_u16x8_splithi(Y)))
//	#define _simd_u16x8_sub_enable() (_simd_u16x4_sub_enable() && _simd_u16x8_combine_enable() && _simd_u16x8_splitlo_enable()  && _simd_u16x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x8_sub_) && ! defined(_simd_u16x8_sub_scalar_)
//	#define _simd_u16x8_sub_scalar_(X,Y) _simd_u16x8_sub_(X,_simd_u16x8_fill_scalar_(Y))
//	#define _simd_u16x8_sub_scalar_instruction_set _simd_u16x8_sub_instruction_set
//#endif
//#ifdef _simd_u16x8_sub_scalar_
//	#define _simd_u16x8_sub_scalar(X,Y) _simd_u16x8_sub_scalar_(X,Y)
//	#define _simd_u16x8_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_sub_scalar_instruction_set>()
//#else
//	#define _simd_u16x8_sub_scalar(X,Y) _simd_u16x8_sub_safe(X,_simd_u16x8_fill_scalar_safe(Y))
//	#define _simd_u16x8_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_u16x1_sub_safe
//	#define _simd_u16x1_sub_safe(X,Y) (X - Y)
//	#define _simd_u16x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_u16x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_sub_enabled() true
//#endif
//
//#define _simd_u16x16_sub_safe(X,Y)_simd_u16x16_combine_safe(\
//	_simd_u16x8_sub_safe(_simd_u16x16_splitlo_safe(X), _simd_ u16x16_splitlo_safe(Y)),\
//	_simd_u16x8_sub_safe(_simd_u16x16_splithi_safe(X), _simd_ u16x16_splithi_safe(Y)))
//#ifdef _simd_u16x16_sub_
//	#define _simd_u16x16_sub(X,Y) _simd_u16x16_sub_(X, Y)
//	#define _simd_u16x16_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_sub_instruction_set>()
//#elif defined(_simd_u16x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_u16x16 ANVIL_SIMD_CALL _simd_u16x16_sub(const register _simd_u16x16 x, const register _simd_u16x16 y) {
//		union SIMDUnion { _simd_u16x16 v1; _simd_u16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x16_sub_enable() _simd_u16x32_sub_enable()
//#elif defined(_simd_u16x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_u16x16 ANVIL_SIMD_CALL _simd_u16x16_sub(const register _simd_u16x16 x, const register _simd_u16x16 y) {
//		union SIMDUnion { _simd_u16x16 v1; _simd_u16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x16_sub_enable() _simd_u16x64_sub_enable()
//#else
//	#define _simd_u16x16_sub(X,Y) _simd_u16x16_combine(\
//		_simd_u16x8_sub(_simd_u16x16_splitlo(X), _simd_u16x16_splitlo(Y)),\
//		_simd_u16x8_sub(_simd_u16x16_splithi(X), _simd_u16x16_splithi(Y)))
//	#define _simd_u16x16_sub_enable() (_simd_u16x8_sub_enable() && _simd_u16x16_combine_enable() && _simd_u16x16_splitlo_enable()  && _simd_u16x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x16_sub_) && ! defined(_simd_u16x16_sub_scalar_)
//	#define _simd_u16x16_sub_scalar_(X,Y) _simd_u16x16_sub_(X,_simd_u16x16_fill_scalar_(Y))
//	#define _simd_u16x16_sub_scalar_instruction_set _simd_u16x16_sub_instruction_set
//#endif
//#ifdef _simd_u16x16_sub_scalar_
//	#define _simd_u16x16_sub_scalar(X,Y) _simd_u16x16_sub_scalar_(X,Y)
//	#define _simd_u16x16_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_sub_scalar_instruction_set>()
//#else
//	#define _simd_u16x16_sub_scalar(X,Y) _simd_u16x16_sub_safe(X,_simd_u16x16_fill_scalar_safe(Y))
//	#define _simd_u16x16_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_u16x1_sub_safe
//	#define _simd_u16x1_sub_safe(X,Y) (X - Y)
//	#define _simd_u16x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_u16x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_sub_enabled() true
//#endif
//
//#define _simd_u16x32_sub_safe(X,Y)_simd_u16x32_combine_safe(\
//	_simd_u16x16_sub_safe(_simd_u16x32_splitlo_safe(X), _simd_ u16x32_splitlo_safe(Y)),\
//	_simd_u16x16_sub_safe(_simd_u16x32_splithi_safe(X), _simd_ u16x32_splithi_safe(Y)))
//#ifdef _simd_u16x32_sub_
//	#define _simd_u16x32_sub(X,Y) _simd_u16x32_sub_(X, Y)
//	#define _simd_u16x32_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_sub_instruction_set>()
//#elif defined(_simd_u16x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_u16x32 ANVIL_SIMD_CALL _simd_u16x32_sub(const register _simd_u16x32 x, const register _simd_u16x32 y) {
//		union SIMDUnion { _simd_u16x32 v1; _simd_u16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x32_sub_enable() _simd_u16x64_sub_enable()
//#else
//	#define _simd_u16x32_sub(X,Y) _simd_u16x32_combine(\
//		_simd_u16x16_sub(_simd_u16x32_splitlo(X), _simd_u16x32_splitlo(Y)),\
//		_simd_u16x16_sub(_simd_u16x32_splithi(X), _simd_u16x32_splithi(Y)))
//	#define _simd_u16x32_sub_enable() (_simd_u16x16_sub_enable() && _simd_u16x32_combine_enable() && _simd_u16x32_splitlo_enable()  && _simd_u16x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x32_sub_) && ! defined(_simd_u16x32_sub_scalar_)
//	#define _simd_u16x32_sub_scalar_(X,Y) _simd_u16x32_sub_(X,_simd_u16x32_fill_scalar_(Y))
//	#define _simd_u16x32_sub_scalar_instruction_set _simd_u16x32_sub_instruction_set
//#endif
//#ifdef _simd_u16x32_sub_scalar_
//	#define _simd_u16x32_sub_scalar(X,Y) _simd_u16x32_sub_scalar_(X,Y)
//	#define _simd_u16x32_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_sub_scalar_instruction_set>()
//#else
//	#define _simd_u16x32_sub_scalar(X,Y) _simd_u16x32_sub_safe(X,_simd_u16x32_fill_scalar_safe(Y))
//	#define _simd_u16x32_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_u16x1_sub_safe
//	#define _simd_u16x1_sub_safe(X,Y) (X - Y)
//	#define _simd_u16x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_u16x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_sub_enabled() true
//#endif
//
//#define _simd_u16x64_sub_safe(X,Y)_simd_u16x64_combine_safe(\
//	_simd_u16x32_sub_safe(_simd_u16x64_splitlo_safe(X), _simd_ u16x64_splitlo_safe(Y)),\
//	_simd_u16x32_sub_safe(_simd_u16x64_splithi_safe(X), _simd_ u16x64_splithi_safe(Y)))
//#ifdef _simd_u16x64_sub_
//	#define _simd_u16x64_sub(X,Y) _simd_u16x64_sub_(X, Y)
//	#define _simd_u16x64_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_sub_instruction_set>()
//#else
//	#define _simd_u16x64_sub(X,Y) _simd_u16x64_combine(\
//		_simd_u16x32_sub(_simd_u16x64_splitlo(X), _simd_u16x64_splitlo(Y)),\
//		_simd_u16x32_sub(_simd_u16x64_splithi(X), _simd_u16x64_splithi(Y)))
//	#define _simd_u16x64_sub_enable() (_simd_u16x32_sub_enable() && _simd_u16x64_combine_enable() && _simd_u16x64_splitlo_enable()  && _simd_u16x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x64_sub_) && ! defined(_simd_u16x64_sub_scalar_)
//	#define _simd_u16x64_sub_scalar_(X,Y) _simd_u16x64_sub_(X,_simd_u16x64_fill_scalar_(Y))
//	#define _simd_u16x64_sub_scalar_instruction_set _simd_u16x64_sub_instruction_set
//#endif
//#ifdef _simd_u16x64_sub_scalar_
//	#define _simd_u16x64_sub_scalar(X,Y) _simd_u16x64_sub_scalar_(X,Y)
//	#define _simd_u16x64_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_sub_scalar_instruction_set>()
//#else
//	#define _simd_u16x64_sub_scalar(X,Y) _simd_u16x64_sub_safe(X,_simd_u16x64_fill_scalar_safe(Y))
//	#define _simd_u16x64_sub_scalar_enabled() true
//#endif
//
//// -- s8 --
//
//#ifndef _simd_s8x1_sub_safe
//	#define _simd_s8x1_sub_safe(X,Y) (X - Y)
//	#define _simd_s8x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_s8x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_sub_enabled() true
//#endif
//
//#define _simd_s8x2_sub_safe(X,Y)_simd_s8x2_combine_safe(\
//	_simd_s8x1_sub_safe(_simd_s8x2_splitlo_safe(X), _simd_ s8x2_splitlo_safe(Y)),\
//	_simd_s8x1_sub_safe(_simd_s8x2_splithi_safe(X), _simd_ s8x2_splithi_safe(Y)))
//#ifdef _simd_s8x2_sub_
//	#define _simd_s8x2_sub(X,Y) _simd_s8x2_sub_(X, Y)
//	#define _simd_s8x2_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_sub_instruction_set>()
//#elif defined(_simd_s8x4_sub_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_sub(const register _simd_s8x2 x, const register _simd_s8x2 y) {
//		union SIMDUnion { _simd_s8x2 v1; _simd_s8x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x4_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x2_sub_enable() _simd_s8x4_sub_enable()
//#elif defined(_simd_s8x8_sub_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_sub(const register _simd_s8x2 x, const register _simd_s8x2 y) {
//		union SIMDUnion { _simd_s8x2 v1; _simd_s8x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x8_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x2_sub_enable() _simd_s8x8_sub_enable()
//#elif defined(_simd_s8x16_sub_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_sub(const register _simd_s8x2 x, const register _simd_s8x2 y) {
//		union SIMDUnion { _simd_s8x2 v1; _simd_s8x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x16_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x2_sub_enable() _simd_s8x16_sub_enable()
//#elif defined(_simd_s8x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_sub(const register _simd_s8x2 x, const register _simd_s8x2 y) {
//		union SIMDUnion { _simd_s8x2 v1; _simd_s8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x2_sub_enable() _simd_s8x32_sub_enable()
//#elif defined(_simd_s8x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_sub(const register _simd_s8x2 x, const register _simd_s8x2 y) {
//		union SIMDUnion { _simd_s8x2 v1; _simd_s8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x2_sub_enable() _simd_s8x64_sub_enable()
//#else
//	#define _simd_s8x2_sub(X,Y) _simd_s8x2_combine(\
//		_simd_s8x1_sub(_simd_s8x2_splitlo(X), _simd_s8x2_splitlo(Y)),\
//		_simd_s8x1_sub(_simd_s8x2_splithi(X), _simd_s8x2_splithi(Y)))
//	#define _simd_s8x2_sub_enable() (_simd_s8x1_sub_enable() && _simd_s8x2_combine_enable() && _simd_s8x2_splitlo_enable()  && _simd_s8x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x2_sub_) && ! defined(_simd_s8x2_sub_scalar_)
//	#define _simd_s8x2_sub_scalar_(X,Y) _simd_s8x2_sub_(X,_simd_s8x2_fill_scalar_(Y))
//	#define _simd_s8x2_sub_scalar_instruction_set _simd_s8x2_sub_instruction_set
//#endif
//#ifdef _simd_s8x2_sub_scalar_
//	#define _simd_s8x2_sub_scalar(X,Y) _simd_s8x2_sub_scalar_(X,Y)
//	#define _simd_s8x2_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_sub_scalar_instruction_set>()
//#else
//	#define _simd_s8x2_sub_scalar(X,Y) _simd_s8x2_sub_safe(X,_simd_s8x2_fill_scalar_safe(Y))
//	#define _simd_s8x2_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_s8x1_sub_safe
//	#define _simd_s8x1_sub_safe(X,Y) (X - Y)
//	#define _simd_s8x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_s8x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_sub_enabled() true
//#endif
//
//#define _simd_s8x4_sub_safe(X,Y)_simd_s8x4_combine_safe(\
//	_simd_s8x2_sub_safe(_simd_s8x4_splitlo_safe(X), _simd_ s8x4_splitlo_safe(Y)),\
//	_simd_s8x2_sub_safe(_simd_s8x4_splithi_safe(X), _simd_ s8x4_splithi_safe(Y)))
//#ifdef _simd_s8x4_sub_
//	#define _simd_s8x4_sub(X,Y) _simd_s8x4_sub_(X, Y)
//	#define _simd_s8x4_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_sub_instruction_set>()
//#elif defined(_simd_s8x8_sub_)
//	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_sub(const register _simd_s8x4 x, const register _simd_s8x4 y) {
//		union SIMDUnion { _simd_s8x4 v1; _simd_s8x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x8_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x4_sub_enable() _simd_s8x8_sub_enable()
//#elif defined(_simd_s8x16_sub_)
//	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_sub(const register _simd_s8x4 x, const register _simd_s8x4 y) {
//		union SIMDUnion { _simd_s8x4 v1; _simd_s8x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x16_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x4_sub_enable() _simd_s8x16_sub_enable()
//#elif defined(_simd_s8x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_sub(const register _simd_s8x4 x, const register _simd_s8x4 y) {
//		union SIMDUnion { _simd_s8x4 v1; _simd_s8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x4_sub_enable() _simd_s8x32_sub_enable()
//#elif defined(_simd_s8x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_sub(const register _simd_s8x4 x, const register _simd_s8x4 y) {
//		union SIMDUnion { _simd_s8x4 v1; _simd_s8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x4_sub_enable() _simd_s8x64_sub_enable()
//#else
//	#define _simd_s8x4_sub(X,Y) _simd_s8x4_combine(\
//		_simd_s8x2_sub(_simd_s8x4_splitlo(X), _simd_s8x4_splitlo(Y)),\
//		_simd_s8x2_sub(_simd_s8x4_splithi(X), _simd_s8x4_splithi(Y)))
//	#define _simd_s8x4_sub_enable() (_simd_s8x2_sub_enable() && _simd_s8x4_combine_enable() && _simd_s8x4_splitlo_enable()  && _simd_s8x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x4_sub_) && ! defined(_simd_s8x4_sub_scalar_)
//	#define _simd_s8x4_sub_scalar_(X,Y) _simd_s8x4_sub_(X,_simd_s8x4_fill_scalar_(Y))
//	#define _simd_s8x4_sub_scalar_instruction_set _simd_s8x4_sub_instruction_set
//#endif
//#ifdef _simd_s8x4_sub_scalar_
//	#define _simd_s8x4_sub_scalar(X,Y) _simd_s8x4_sub_scalar_(X,Y)
//	#define _simd_s8x4_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_sub_scalar_instruction_set>()
//#else
//	#define _simd_s8x4_sub_scalar(X,Y) _simd_s8x4_sub_safe(X,_simd_s8x4_fill_scalar_safe(Y))
//	#define _simd_s8x4_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_s8x1_sub_safe
//	#define _simd_s8x1_sub_safe(X,Y) (X - Y)
//	#define _simd_s8x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_s8x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_sub_enabled() true
//#endif
//
//#define _simd_s8x8_sub_safe(X,Y)_simd_s8x8_combine_safe(\
//	_simd_s8x4_sub_safe(_simd_s8x8_splitlo_safe(X), _simd_ s8x8_splitlo_safe(Y)),\
//	_simd_s8x4_sub_safe(_simd_s8x8_splithi_safe(X), _simd_ s8x8_splithi_safe(Y)))
//#ifdef _simd_s8x8_sub_
//	#define _simd_s8x8_sub(X,Y) _simd_s8x8_sub_(X, Y)
//	#define _simd_s8x8_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_sub_instruction_set>()
//#elif defined(_simd_s8x16_sub_)
//	static ANVIL_STRONG_INLINE _simd_s8x8 ANVIL_SIMD_CALL _simd_s8x8_sub(const register _simd_s8x8 x, const register _simd_s8x8 y) {
//		union SIMDUnion { _simd_s8x8 v1; _simd_s8x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x16_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x8_sub_enable() _simd_s8x16_sub_enable()
//#elif defined(_simd_s8x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_s8x8 ANVIL_SIMD_CALL _simd_s8x8_sub(const register _simd_s8x8 x, const register _simd_s8x8 y) {
//		union SIMDUnion { _simd_s8x8 v1; _simd_s8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x8_sub_enable() _simd_s8x32_sub_enable()
//#elif defined(_simd_s8x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_s8x8 ANVIL_SIMD_CALL _simd_s8x8_sub(const register _simd_s8x8 x, const register _simd_s8x8 y) {
//		union SIMDUnion { _simd_s8x8 v1; _simd_s8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x8_sub_enable() _simd_s8x64_sub_enable()
//#else
//	#define _simd_s8x8_sub(X,Y) _simd_s8x8_combine(\
//		_simd_s8x4_sub(_simd_s8x8_splitlo(X), _simd_s8x8_splitlo(Y)),\
//		_simd_s8x4_sub(_simd_s8x8_splithi(X), _simd_s8x8_splithi(Y)))
//	#define _simd_s8x8_sub_enable() (_simd_s8x4_sub_enable() && _simd_s8x8_combine_enable() && _simd_s8x8_splitlo_enable()  && _simd_s8x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x8_sub_) && ! defined(_simd_s8x8_sub_scalar_)
//	#define _simd_s8x8_sub_scalar_(X,Y) _simd_s8x8_sub_(X,_simd_s8x8_fill_scalar_(Y))
//	#define _simd_s8x8_sub_scalar_instruction_set _simd_s8x8_sub_instruction_set
//#endif
//#ifdef _simd_s8x8_sub_scalar_
//	#define _simd_s8x8_sub_scalar(X,Y) _simd_s8x8_sub_scalar_(X,Y)
//	#define _simd_s8x8_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_sub_scalar_instruction_set>()
//#else
//	#define _simd_s8x8_sub_scalar(X,Y) _simd_s8x8_sub_safe(X,_simd_s8x8_fill_scalar_safe(Y))
//	#define _simd_s8x8_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_s8x1_sub_safe
//	#define _simd_s8x1_sub_safe(X,Y) (X - Y)
//	#define _simd_s8x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_s8x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_sub_enabled() true
//#endif
//
//#define _simd_s8x16_sub_safe(X,Y)_simd_s8x16_combine_safe(\
//	_simd_s8x8_sub_safe(_simd_s8x16_splitlo_safe(X), _simd_ s8x16_splitlo_safe(Y)),\
//	_simd_s8x8_sub_safe(_simd_s8x16_splithi_safe(X), _simd_ s8x16_splithi_safe(Y)))
//#ifdef _simd_s8x16_sub_
//	#define _simd_s8x16_sub(X,Y) _simd_s8x16_sub_(X, Y)
//	#define _simd_s8x16_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_sub_instruction_set>()
//#elif defined(_simd_s8x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_s8x16 ANVIL_SIMD_CALL _simd_s8x16_sub(const register _simd_s8x16 x, const register _simd_s8x16 y) {
//		union SIMDUnion { _simd_s8x16 v1; _simd_s8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x16_sub_enable() _simd_s8x32_sub_enable()
//#elif defined(_simd_s8x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_s8x16 ANVIL_SIMD_CALL _simd_s8x16_sub(const register _simd_s8x16 x, const register _simd_s8x16 y) {
//		union SIMDUnion { _simd_s8x16 v1; _simd_s8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x16_sub_enable() _simd_s8x64_sub_enable()
//#else
//	#define _simd_s8x16_sub(X,Y) _simd_s8x16_combine(\
//		_simd_s8x8_sub(_simd_s8x16_splitlo(X), _simd_s8x16_splitlo(Y)),\
//		_simd_s8x8_sub(_simd_s8x16_splithi(X), _simd_s8x16_splithi(Y)))
//	#define _simd_s8x16_sub_enable() (_simd_s8x8_sub_enable() && _simd_s8x16_combine_enable() && _simd_s8x16_splitlo_enable()  && _simd_s8x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x16_sub_) && ! defined(_simd_s8x16_sub_scalar_)
//	#define _simd_s8x16_sub_scalar_(X,Y) _simd_s8x16_sub_(X,_simd_s8x16_fill_scalar_(Y))
//	#define _simd_s8x16_sub_scalar_instruction_set _simd_s8x16_sub_instruction_set
//#endif
//#ifdef _simd_s8x16_sub_scalar_
//	#define _simd_s8x16_sub_scalar(X,Y) _simd_s8x16_sub_scalar_(X,Y)
//	#define _simd_s8x16_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_sub_scalar_instruction_set>()
//#else
//	#define _simd_s8x16_sub_scalar(X,Y) _simd_s8x16_sub_safe(X,_simd_s8x16_fill_scalar_safe(Y))
//	#define _simd_s8x16_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_s8x1_sub_safe
//	#define _simd_s8x1_sub_safe(X,Y) (X - Y)
//	#define _simd_s8x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_s8x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_sub_enabled() true
//#endif
//
//#define _simd_s8x32_sub_safe(X,Y)_simd_s8x32_combine_safe(\
//	_simd_s8x16_sub_safe(_simd_s8x32_splitlo_safe(X), _simd_ s8x32_splitlo_safe(Y)),\
//	_simd_s8x16_sub_safe(_simd_s8x32_splithi_safe(X), _simd_ s8x32_splithi_safe(Y)))
//#ifdef _simd_s8x32_sub_
//	#define _simd_s8x32_sub(X,Y) _simd_s8x32_sub_(X, Y)
//	#define _simd_s8x32_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_sub_instruction_set>()
//#elif defined(_simd_s8x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_s8x32 ANVIL_SIMD_CALL _simd_s8x32_sub(const register _simd_s8x32 x, const register _simd_s8x32 y) {
//		union SIMDUnion { _simd_s8x32 v1; _simd_s8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x32_sub_enable() _simd_s8x64_sub_enable()
//#else
//	#define _simd_s8x32_sub(X,Y) _simd_s8x32_combine(\
//		_simd_s8x16_sub(_simd_s8x32_splitlo(X), _simd_s8x32_splitlo(Y)),\
//		_simd_s8x16_sub(_simd_s8x32_splithi(X), _simd_s8x32_splithi(Y)))
//	#define _simd_s8x32_sub_enable() (_simd_s8x16_sub_enable() && _simd_s8x32_combine_enable() && _simd_s8x32_splitlo_enable()  && _simd_s8x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x32_sub_) && ! defined(_simd_s8x32_sub_scalar_)
//	#define _simd_s8x32_sub_scalar_(X,Y) _simd_s8x32_sub_(X,_simd_s8x32_fill_scalar_(Y))
//	#define _simd_s8x32_sub_scalar_instruction_set _simd_s8x32_sub_instruction_set
//#endif
//#ifdef _simd_s8x32_sub_scalar_
//	#define _simd_s8x32_sub_scalar(X,Y) _simd_s8x32_sub_scalar_(X,Y)
//	#define _simd_s8x32_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_sub_scalar_instruction_set>()
//#else
//	#define _simd_s8x32_sub_scalar(X,Y) _simd_s8x32_sub_safe(X,_simd_s8x32_fill_scalar_safe(Y))
//	#define _simd_s8x32_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_s8x1_sub_safe
//	#define _simd_s8x1_sub_safe(X,Y) (X - Y)
//	#define _simd_s8x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_s8x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_sub_enabled() true
//#endif
//
//#define _simd_s8x64_sub_safe(X,Y)_simd_s8x64_combine_safe(\
//	_simd_s8x32_sub_safe(_simd_s8x64_splitlo_safe(X), _simd_ s8x64_splitlo_safe(Y)),\
//	_simd_s8x32_sub_safe(_simd_s8x64_splithi_safe(X), _simd_ s8x64_splithi_safe(Y)))
//#ifdef _simd_s8x64_sub_
//	#define _simd_s8x64_sub(X,Y) _simd_s8x64_sub_(X, Y)
//	#define _simd_s8x64_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_sub_instruction_set>()
//#else
//	#define _simd_s8x64_sub(X,Y) _simd_s8x64_combine(\
//		_simd_s8x32_sub(_simd_s8x64_splitlo(X), _simd_s8x64_splitlo(Y)),\
//		_simd_s8x32_sub(_simd_s8x64_splithi(X), _simd_s8x64_splithi(Y)))
//	#define _simd_s8x64_sub_enable() (_simd_s8x32_sub_enable() && _simd_s8x64_combine_enable() && _simd_s8x64_splitlo_enable()  && _simd_s8x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x64_sub_) && ! defined(_simd_s8x64_sub_scalar_)
//	#define _simd_s8x64_sub_scalar_(X,Y) _simd_s8x64_sub_(X,_simd_s8x64_fill_scalar_(Y))
//	#define _simd_s8x64_sub_scalar_instruction_set _simd_s8x64_sub_instruction_set
//#endif
//#ifdef _simd_s8x64_sub_scalar_
//	#define _simd_s8x64_sub_scalar(X,Y) _simd_s8x64_sub_scalar_(X,Y)
//	#define _simd_s8x64_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_sub_scalar_instruction_set>()
//#else
//	#define _simd_s8x64_sub_scalar(X,Y) _simd_s8x64_sub_safe(X,_simd_s8x64_fill_scalar_safe(Y))
//	#define _simd_s8x64_sub_scalar_enabled() true
//#endif
//
//// -- u8 --
//
//#ifndef _simd_u8x1_sub_safe
//	#define _simd_u8x1_sub_safe(X,Y) (X - Y)
//	#define _simd_u8x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_u8x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_sub_enabled() true
//#endif
//
//#define _simd_u8x2_sub_safe(X,Y)_simd_u8x2_combine_safe(\
//	_simd_u8x1_sub_safe(_simd_u8x2_splitlo_safe(X), _simd_ u8x2_splitlo_safe(Y)),\
//	_simd_u8x1_sub_safe(_simd_u8x2_splithi_safe(X), _simd_ u8x2_splithi_safe(Y)))
//#ifdef _simd_u8x2_sub_
//	#define _simd_u8x2_sub(X,Y) _simd_u8x2_sub_(X, Y)
//	#define _simd_u8x2_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_sub_instruction_set>()
//#elif defined(_simd_u8x4_sub_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_sub(const register _simd_u8x2 x, const register _simd_u8x2 y) {
//		union SIMDUnion { _simd_u8x2 v1; _simd_u8x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x4_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x2_sub_enable() _simd_u8x4_sub_enable()
//#elif defined(_simd_u8x8_sub_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_sub(const register _simd_u8x2 x, const register _simd_u8x2 y) {
//		union SIMDUnion { _simd_u8x2 v1; _simd_u8x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x8_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x2_sub_enable() _simd_u8x8_sub_enable()
//#elif defined(_simd_u8x16_sub_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_sub(const register _simd_u8x2 x, const register _simd_u8x2 y) {
//		union SIMDUnion { _simd_u8x2 v1; _simd_u8x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x16_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x2_sub_enable() _simd_u8x16_sub_enable()
//#elif defined(_simd_u8x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_sub(const register _simd_u8x2 x, const register _simd_u8x2 y) {
//		union SIMDUnion { _simd_u8x2 v1; _simd_u8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x2_sub_enable() _simd_u8x32_sub_enable()
//#elif defined(_simd_u8x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_sub(const register _simd_u8x2 x, const register _simd_u8x2 y) {
//		union SIMDUnion { _simd_u8x2 v1; _simd_u8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x2_sub_enable() _simd_u8x64_sub_enable()
//#else
//	#define _simd_u8x2_sub(X,Y) _simd_u8x2_combine(\
//		_simd_u8x1_sub(_simd_u8x2_splitlo(X), _simd_u8x2_splitlo(Y)),\
//		_simd_u8x1_sub(_simd_u8x2_splithi(X), _simd_u8x2_splithi(Y)))
//	#define _simd_u8x2_sub_enable() (_simd_u8x1_sub_enable() && _simd_u8x2_combine_enable() && _simd_u8x2_splitlo_enable()  && _simd_u8x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x2_sub_) && ! defined(_simd_u8x2_sub_scalar_)
//	#define _simd_u8x2_sub_scalar_(X,Y) _simd_u8x2_sub_(X,_simd_u8x2_fill_scalar_(Y))
//	#define _simd_u8x2_sub_scalar_instruction_set _simd_u8x2_sub_instruction_set
//#endif
//#ifdef _simd_u8x2_sub_scalar_
//	#define _simd_u8x2_sub_scalar(X,Y) _simd_u8x2_sub_scalar_(X,Y)
//	#define _simd_u8x2_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_sub_scalar_instruction_set>()
//#else
//	#define _simd_u8x2_sub_scalar(X,Y) _simd_u8x2_sub_safe(X,_simd_u8x2_fill_scalar_safe(Y))
//	#define _simd_u8x2_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_u8x1_sub_safe
//	#define _simd_u8x1_sub_safe(X,Y) (X - Y)
//	#define _simd_u8x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_u8x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_sub_enabled() true
//#endif
//
//#define _simd_u8x4_sub_safe(X,Y)_simd_u8x4_combine_safe(\
//	_simd_u8x2_sub_safe(_simd_u8x4_splitlo_safe(X), _simd_ u8x4_splitlo_safe(Y)),\
//	_simd_u8x2_sub_safe(_simd_u8x4_splithi_safe(X), _simd_ u8x4_splithi_safe(Y)))
//#ifdef _simd_u8x4_sub_
//	#define _simd_u8x4_sub(X,Y) _simd_u8x4_sub_(X, Y)
//	#define _simd_u8x4_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_sub_instruction_set>()
//#elif defined(_simd_u8x8_sub_)
//	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_sub(const register _simd_u8x4 x, const register _simd_u8x4 y) {
//		union SIMDUnion { _simd_u8x4 v1; _simd_u8x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x8_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x4_sub_enable() _simd_u8x8_sub_enable()
//#elif defined(_simd_u8x16_sub_)
//	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_sub(const register _simd_u8x4 x, const register _simd_u8x4 y) {
//		union SIMDUnion { _simd_u8x4 v1; _simd_u8x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x16_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x4_sub_enable() _simd_u8x16_sub_enable()
//#elif defined(_simd_u8x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_sub(const register _simd_u8x4 x, const register _simd_u8x4 y) {
//		union SIMDUnion { _simd_u8x4 v1; _simd_u8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x4_sub_enable() _simd_u8x32_sub_enable()
//#elif defined(_simd_u8x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_sub(const register _simd_u8x4 x, const register _simd_u8x4 y) {
//		union SIMDUnion { _simd_u8x4 v1; _simd_u8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x4_sub_enable() _simd_u8x64_sub_enable()
//#else
//	#define _simd_u8x4_sub(X,Y) _simd_u8x4_combine(\
//		_simd_u8x2_sub(_simd_u8x4_splitlo(X), _simd_u8x4_splitlo(Y)),\
//		_simd_u8x2_sub(_simd_u8x4_splithi(X), _simd_u8x4_splithi(Y)))
//	#define _simd_u8x4_sub_enable() (_simd_u8x2_sub_enable() && _simd_u8x4_combine_enable() && _simd_u8x4_splitlo_enable()  && _simd_u8x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x4_sub_) && ! defined(_simd_u8x4_sub_scalar_)
//	#define _simd_u8x4_sub_scalar_(X,Y) _simd_u8x4_sub_(X,_simd_u8x4_fill_scalar_(Y))
//	#define _simd_u8x4_sub_scalar_instruction_set _simd_u8x4_sub_instruction_set
//#endif
//#ifdef _simd_u8x4_sub_scalar_
//	#define _simd_u8x4_sub_scalar(X,Y) _simd_u8x4_sub_scalar_(X,Y)
//	#define _simd_u8x4_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_sub_scalar_instruction_set>()
//#else
//	#define _simd_u8x4_sub_scalar(X,Y) _simd_u8x4_sub_safe(X,_simd_u8x4_fill_scalar_safe(Y))
//	#define _simd_u8x4_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_u8x1_sub_safe
//	#define _simd_u8x1_sub_safe(X,Y) (X - Y)
//	#define _simd_u8x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_u8x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_sub_enabled() true
//#endif
//
//#define _simd_u8x8_sub_safe(X,Y)_simd_u8x8_combine_safe(\
//	_simd_u8x4_sub_safe(_simd_u8x8_splitlo_safe(X), _simd_ u8x8_splitlo_safe(Y)),\
//	_simd_u8x4_sub_safe(_simd_u8x8_splithi_safe(X), _simd_ u8x8_splithi_safe(Y)))
//#ifdef _simd_u8x8_sub_
//	#define _simd_u8x8_sub(X,Y) _simd_u8x8_sub_(X, Y)
//	#define _simd_u8x8_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_sub_instruction_set>()
//#elif defined(_simd_u8x16_sub_)
//	static ANVIL_STRONG_INLINE _simd_u8x8 ANVIL_SIMD_CALL _simd_u8x8_sub(const register _simd_u8x8 x, const register _simd_u8x8 y) {
//		union SIMDUnion { _simd_u8x8 v1; _simd_u8x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x16_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x8_sub_enable() _simd_u8x16_sub_enable()
//#elif defined(_simd_u8x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_u8x8 ANVIL_SIMD_CALL _simd_u8x8_sub(const register _simd_u8x8 x, const register _simd_u8x8 y) {
//		union SIMDUnion { _simd_u8x8 v1; _simd_u8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x8_sub_enable() _simd_u8x32_sub_enable()
//#elif defined(_simd_u8x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_u8x8 ANVIL_SIMD_CALL _simd_u8x8_sub(const register _simd_u8x8 x, const register _simd_u8x8 y) {
//		union SIMDUnion { _simd_u8x8 v1; _simd_u8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x8_sub_enable() _simd_u8x64_sub_enable()
//#else
//	#define _simd_u8x8_sub(X,Y) _simd_u8x8_combine(\
//		_simd_u8x4_sub(_simd_u8x8_splitlo(X), _simd_u8x8_splitlo(Y)),\
//		_simd_u8x4_sub(_simd_u8x8_splithi(X), _simd_u8x8_splithi(Y)))
//	#define _simd_u8x8_sub_enable() (_simd_u8x4_sub_enable() && _simd_u8x8_combine_enable() && _simd_u8x8_splitlo_enable()  && _simd_u8x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x8_sub_) && ! defined(_simd_u8x8_sub_scalar_)
//	#define _simd_u8x8_sub_scalar_(X,Y) _simd_u8x8_sub_(X,_simd_u8x8_fill_scalar_(Y))
//	#define _simd_u8x8_sub_scalar_instruction_set _simd_u8x8_sub_instruction_set
//#endif
//#ifdef _simd_u8x8_sub_scalar_
//	#define _simd_u8x8_sub_scalar(X,Y) _simd_u8x8_sub_scalar_(X,Y)
//	#define _simd_u8x8_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_sub_scalar_instruction_set>()
//#else
//	#define _simd_u8x8_sub_scalar(X,Y) _simd_u8x8_sub_safe(X,_simd_u8x8_fill_scalar_safe(Y))
//	#define _simd_u8x8_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_u8x1_sub_safe
//	#define _simd_u8x1_sub_safe(X,Y) (X - Y)
//	#define _simd_u8x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_u8x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_sub_enabled() true
//#endif
//
//#define _simd_u8x16_sub_safe(X,Y)_simd_u8x16_combine_safe(\
//	_simd_u8x8_sub_safe(_simd_u8x16_splitlo_safe(X), _simd_ u8x16_splitlo_safe(Y)),\
//	_simd_u8x8_sub_safe(_simd_u8x16_splithi_safe(X), _simd_ u8x16_splithi_safe(Y)))
//#ifdef _simd_u8x16_sub_
//	#define _simd_u8x16_sub(X,Y) _simd_u8x16_sub_(X, Y)
//	#define _simd_u8x16_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_sub_instruction_set>()
//#elif defined(_simd_u8x32_sub_)
//	static ANVIL_STRONG_INLINE _simd_u8x16 ANVIL_SIMD_CALL _simd_u8x16_sub(const register _simd_u8x16 x, const register _simd_u8x16 y) {
//		union SIMDUnion { _simd_u8x16 v1; _simd_u8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x32_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x16_sub_enable() _simd_u8x32_sub_enable()
//#elif defined(_simd_u8x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_u8x16 ANVIL_SIMD_CALL _simd_u8x16_sub(const register _simd_u8x16 x, const register _simd_u8x16 y) {
//		union SIMDUnion { _simd_u8x16 v1; _simd_u8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x16_sub_enable() _simd_u8x64_sub_enable()
//#else
//	#define _simd_u8x16_sub(X,Y) _simd_u8x16_combine(\
//		_simd_u8x8_sub(_simd_u8x16_splitlo(X), _simd_u8x16_splitlo(Y)),\
//		_simd_u8x8_sub(_simd_u8x16_splithi(X), _simd_u8x16_splithi(Y)))
//	#define _simd_u8x16_sub_enable() (_simd_u8x8_sub_enable() && _simd_u8x16_combine_enable() && _simd_u8x16_splitlo_enable()  && _simd_u8x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x16_sub_) && ! defined(_simd_u8x16_sub_scalar_)
//	#define _simd_u8x16_sub_scalar_(X,Y) _simd_u8x16_sub_(X,_simd_u8x16_fill_scalar_(Y))
//	#define _simd_u8x16_sub_scalar_instruction_set _simd_u8x16_sub_instruction_set
//#endif
//#ifdef _simd_u8x16_sub_scalar_
//	#define _simd_u8x16_sub_scalar(X,Y) _simd_u8x16_sub_scalar_(X,Y)
//	#define _simd_u8x16_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_sub_scalar_instruction_set>()
//#else
//	#define _simd_u8x16_sub_scalar(X,Y) _simd_u8x16_sub_safe(X,_simd_u8x16_fill_scalar_safe(Y))
//	#define _simd_u8x16_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_u8x1_sub_safe
//	#define _simd_u8x1_sub_safe(X,Y) (X - Y)
//	#define _simd_u8x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_u8x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_sub_enabled() true
//#endif
//
//#define _simd_u8x32_sub_safe(X,Y)_simd_u8x32_combine_safe(\
//	_simd_u8x16_sub_safe(_simd_u8x32_splitlo_safe(X), _simd_ u8x32_splitlo_safe(Y)),\
//	_simd_u8x16_sub_safe(_simd_u8x32_splithi_safe(X), _simd_ u8x32_splithi_safe(Y)))
//#ifdef _simd_u8x32_sub_
//	#define _simd_u8x32_sub(X,Y) _simd_u8x32_sub_(X, Y)
//	#define _simd_u8x32_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_sub_instruction_set>()
//#elif defined(_simd_u8x64_sub_)
//	static ANVIL_STRONG_INLINE _simd_u8x32 ANVIL_SIMD_CALL _simd_u8x32_sub(const register _simd_u8x32 x, const register _simd_u8x32 y) {
//		union SIMDUnion { _simd_u8x32 v1; _simd_u8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x64_sub_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x32_sub_enable() _simd_u8x64_sub_enable()
//#else
//	#define _simd_u8x32_sub(X,Y) _simd_u8x32_combine(\
//		_simd_u8x16_sub(_simd_u8x32_splitlo(X), _simd_u8x32_splitlo(Y)),\
//		_simd_u8x16_sub(_simd_u8x32_splithi(X), _simd_u8x32_splithi(Y)))
//	#define _simd_u8x32_sub_enable() (_simd_u8x16_sub_enable() && _simd_u8x32_combine_enable() && _simd_u8x32_splitlo_enable()  && _simd_u8x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x32_sub_) && ! defined(_simd_u8x32_sub_scalar_)
//	#define _simd_u8x32_sub_scalar_(X,Y) _simd_u8x32_sub_(X,_simd_u8x32_fill_scalar_(Y))
//	#define _simd_u8x32_sub_scalar_instruction_set _simd_u8x32_sub_instruction_set
//#endif
//#ifdef _simd_u8x32_sub_scalar_
//	#define _simd_u8x32_sub_scalar(X,Y) _simd_u8x32_sub_scalar_(X,Y)
//	#define _simd_u8x32_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_sub_scalar_instruction_set>()
//#else
//	#define _simd_u8x32_sub_scalar(X,Y) _simd_u8x32_sub_safe(X,_simd_u8x32_fill_scalar_safe(Y))
//	#define _simd_u8x32_sub_scalar_enabled() true
//#endif
//
//#ifndef _simd_u8x1_sub_safe
//	#define _simd_u8x1_sub_safe(X,Y) (X - Y)
//	#define _simd_u8x1_sub_(X,Y) x1_sub_safe(X,Y)
//	#define _simd_u8x1_sub_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_sub_enabled() true
//#endif
//
//#define _simd_u8x64_sub_safe(X,Y)_simd_u8x64_combine_safe(\
//	_simd_u8x32_sub_safe(_simd_u8x64_splitlo_safe(X), _simd_ u8x64_splitlo_safe(Y)),\
//	_simd_u8x32_sub_safe(_simd_u8x64_splithi_safe(X), _simd_ u8x64_splithi_safe(Y)))
//#ifdef _simd_u8x64_sub_
//	#define _simd_u8x64_sub(X,Y) _simd_u8x64_sub_(X, Y)
//	#define _simd_u8x64_sub_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_sub_instruction_set>()
//#else
//	#define _simd_u8x64_sub(X,Y) _simd_u8x64_combine(\
//		_simd_u8x32_sub(_simd_u8x64_splitlo(X), _simd_u8x64_splitlo(Y)),\
//		_simd_u8x32_sub(_simd_u8x64_splithi(X), _simd_u8x64_splithi(Y)))
//	#define _simd_u8x64_sub_enable() (_simd_u8x32_sub_enable() && _simd_u8x64_combine_enable() && _simd_u8x64_splitlo_enable()  && _simd_u8x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x64_sub_) && ! defined(_simd_u8x64_sub_scalar_)
//	#define _simd_u8x64_sub_scalar_(X,Y) _simd_u8x64_sub_(X,_simd_u8x64_fill_scalar_(Y))
//	#define _simd_u8x64_sub_scalar_instruction_set _simd_u8x64_sub_instruction_set
//#endif
//#ifdef _simd_u8x64_sub_scalar_
//	#define _simd_u8x64_sub_scalar(X,Y) _simd_u8x64_sub_scalar_(X,Y)
//	#define _simd_u8x64_sub_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_sub_scalar_instruction_set>()
//#else
//	#define _simd_u8x64_sub_scalar(X,Y) _simd_u8x64_sub_safe(X,_simd_u8x64_fill_scalar_safe(Y))
//	#define _simd_u8x64_sub_scalar_enabled() true
//#endif
//
