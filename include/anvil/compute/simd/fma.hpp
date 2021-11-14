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

#ifndef ANVIL_COMPUTE_SIMD_FMA_HPP
#define ANVIL_COMPUTE_SIMD_FMA_HPP

#include "anvil/core/CpuRuntime.hpp"
#include "anvil/compute/Vector.hpp"
#include "anvil/compute/SIMD/Add.hpp"
#include "anvil/compute/SIMD/Mul.hpp"

namespace anvil { namespace detail {
	template<class T>
	struct VectorMultiplyAdd;

	// Scalar types

	template<>
	struct VectorMultiplyAdd<uint8_t> {
		typedef uint8_t type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b, type c) throw() {
			return (a * b) + c;
		}
	};

	template<>
	struct VectorMultiplyAdd<uint16_t> {
		typedef uint16_t type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b, type c) throw() {
			return (a * b) + c;
		}
	};

	template<>
	struct VectorMultiplyAdd<uint32_t> {
		typedef uint32_t type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b, type c) throw() {
			return (a * b) + c;
		}
	};

	template<>
	struct VectorMultiplyAdd<uint64_t> {
		typedef uint64_t type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b, type c) throw() {
			return (a * b) + c;
		}
	};

	template<>
	struct VectorMultiplyAdd<int8_t> {
		typedef int8_t type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b, type c) throw() {
			return (a * b) + c;
		}
	};

	template<>
	struct VectorMultiplyAdd<int16_t> {
		typedef int16_t type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b, type c) throw() {
			return (a * b) + c;
		}
	};

	template<>
	struct VectorMultiplyAdd<int32_t> {
		typedef int32_t type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b, type c) throw() {
			return (a * b) + c;
		}
	};

	template<>
	struct VectorMultiplyAdd<int64_t> {
		typedef int64_t type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b, type c) throw() {
			return (a * b) + c;
		}
	};

	template<>
	struct VectorMultiplyAdd<float32_t> {
		typedef float32_t type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b, type c) throw() {
			return (a * b) + c;
		}
	};

	template<>
	struct VectorMultiplyAdd<float64_t> {
		typedef float64_t type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b, type c) throw() {
			return (a * b) + c;
		}
	};

	// Optimised vectors


#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64

	template<>
	struct VectorMultiplyAdd<detail::BasicVector<float32_t, 4u>> {
		typedef detail::BasicVector<float32_t, 4u> type;

		static ANVIL_STRONG_INLINE type Execute_SSE(type a, const type& b, const type& c) throw() {
			a.native = _mm_add_ps(_mm_mul_ps(a.native, b.native), c.native);
			return a;
		}

		static ANVIL_STRONG_INLINE type Execute_FMA(type a, const type& b, const type& c) throw() {
			a.native = _mm_fmadd_ps(a.native, b.native, c.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(const type& a, const type& b, const type& c) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_FMA) != 0ull) {
				return Execute_FMA(a, b, c);
			} else if constexpr ((instruction_set & ASM_SSE) != 0ull) {
				return Execute_SSE(a, b, c);
			} else {
				return type(
					VectorMultiplyAdd<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half, c.lower_half),
					VectorMultiplyAdd<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half, c.upper_half)
				);
			}
		}
	};

	template<>
	struct VectorMultiplyAdd<detail::BasicVector<float32_t, 8u>> {
		typedef detail::BasicVector<float32_t, 8u> type;

		static ANVIL_STRONG_INLINE type Execute_AVX(type a, const type& b, const type& c) throw() {
			a.native = _mm256_add_ps(_mm256_mul_ps(a.native, b.native), c.native);
			return a;
		}

		static ANVIL_STRONG_INLINE type Execute_FMA(type a, const type& b, const type& c) throw() {
			a.native = _mm256_fmadd_ps(a.native, b.native, c.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(const type& a, const type& b, const type& c) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_FMA) != 0ull) {
				return Execute_FMA(a, b, c);
			} else if constexpr ((instruction_set & ASM_AVX) != 0ull) {
				return Execute_AVX(a, b, c);
			} else {
				return type(
					VectorMultiplyAdd<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half, c.lower_half),
					VectorMultiplyAdd<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half, c.upper_half)
				);
			}
		}
	};

	template<>
	struct VectorMultiplyAdd<detail::BasicVector<float32_t, 16u>> {
		typedef detail::BasicVector<float32_t, 16u> type;

		static ANVIL_STRONG_INLINE type Execute_AVX512F(type a, const type& b, const type& c) throw() {
			a.native = _mm512_fmadd_ps(a.native, b.native, c.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(const type& a, const type& b, const type& c) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_AVX512F) != 0ull) {
				return Execute_AVX512F(a, b, c);
			} else {
				return type(
					VectorMultiplyAdd<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half, c.lower_half),
					VectorMultiplyAdd<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half, c.upper_half)
				);
			}
		}
	};

	template<>
	struct VectorMultiplyAdd<detail::BasicVector<float64_t, 2u>> {
		typedef detail::BasicVector<float64_t, 2u> type;

		static ANVIL_STRONG_INLINE type Execute_SSE2(type a, const type& b, const type& c) throw() {
			a.native = _mm_add_pd(_mm_mul_pd(a.native, b.native), c.native);
			return a;
		}

		static ANVIL_STRONG_INLINE type Execute_FMA(type a, const type& b, const type& c) throw() {
			a.native = _mm_fmadd_pd(a.native, b.native, c.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(const type& a, const type& b, const type& c) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_FMA) != 0ull) {
				return Execute_FMA(a, b, c);
			} else if constexpr ((instruction_set & ASM_SSE2) != 0ull) {
				return Execute_SSE2(a, b, c);
			} else {
				return type(
					VectorMultiplyAdd<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half, c.lower_half),
					VectorMultiplyAdd<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half, c.upper_half)
				);
			}
		}
	};

	template<>
	struct VectorMultiplyAdd<detail::BasicVector<float64_t, 4u>> {
		typedef detail::BasicVector<float64_t, 4u> type;

		static ANVIL_STRONG_INLINE type Execute_AVX(type a, const type& b, const type& c) throw() {
			a.native = _mm256_add_pd(_mm256_mul_pd(a.native, b.native), c.native);
			return a;
		}

		static ANVIL_STRONG_INLINE type Execute_FMA(type a, const type& b, const type& c) throw() {
			a.native = _mm256_fmadd_pd(a.native, b.native, c.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(const type& a, const type& b, const type& c) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_FMA) != 0ull) {
				return Execute_FMA(a, b, c);
			} else if constexpr ((instruction_set & ASM_AVX) != 0ull) {
				return Execute_AVX(a, b, c);
			} else {
				return type(
					VectorMultiplyAdd<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half, c.lower_half),
					VectorMultiplyAdd<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half, c.upper_half)
				);
			}
		}
	};

	template<>
	struct VectorMultiplyAdd<detail::BasicVector<float64_t, 8u>> {
		typedef detail::BasicVector<float64_t, 8u> type;

		static ANVIL_STRONG_INLINE type Execute_AVX512F(type a, const type& b, const type& c) throw() {
			a.native = _mm512_fmadd_pd(a.native, b.native, c.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(const type& a, const type& b, const type& c) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_AVX512F) != 0ull) {
				return Execute_AVX512F(a, b, c);
			} else {
				return type(
					VectorMultiplyAdd<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half, c.lower_half),
					VectorMultiplyAdd<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half, c.upper_half)
				);
			}
		}
	};

#endif

	// Unoptimised vectors

	template<class T, size_t size>
	struct VectorMultiplyAdd<detail::BasicVector<T, size>> {
		typedef detail::BasicVector<T, size> type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, const type& b, const type& c) throw() {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
			// If the vector fits into an SSE / AVX register then break the calculation down
			// into smaller operations that are likely to have optimised implementations
			if constexpr (
				(sizeof(T) * size == 64 && (instruction_set & ASM_AVX512BW) != 0ull) ||
				(sizeof(T) * size == 32 && (instruction_set & ASM_AVX2) != 0ull) || 
				(sizeof(T) * size == 16 && (instruction_set & ASM_SSE2) != 0ull)
			) {
				return  anvil::VectorAdd<instruction_set>(anvil::VectorMul<instruction_set>(a, b), c);
			}
#endif
			return type(
				VectorMultiplyAdd<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half, c.lower_half),
				VectorMultiplyAdd<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half, c.upper_half)
			);
		}
	};
}}

namespace anvil {

	template<uint64_t instruction_set = ASM_MINIMUM, class T>
	static inline T VectorMultiplyAdd(const T& a, const T& b, const T& c) throw() {
		return detail::VectorMultiplyAdd<T>::Execute<instruction_set>(a, b, c);
	}
}

#endif


//// -- f64 --
//
//#ifndef _simd_f64x1_fma_safe
//	#define _simd_f64x1_fma_safe(X,Y,Z) std::fma(X,Y,Z)
//	#define _simd_f64x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_f64x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_fma_enabled() true
//#endif
//
//#define _simd_f64x2_fma_safe(X,Y,Z)_simd_f64x2_combine_safe(\
//	_simd_f64x1_fma_safe(_simd_f64x2_splitlo_safe(X), _simd_ f64x2_splitlo_safe(Y), _simd_ f64x2_splitlo_safe(Z)),\
//	_simd_f64x1_fma_safe(_simd_f64x2_splithi_safe(X), _simd_ f64x2_splithi_safe(Y), _simd_ f64x2_splithi_safe(Z)))
//#ifdef _simd_f64x2_fma_
//	#define _simd_f64x2_fma(X,Y,Z) _simd_f64x2_fma_(X,Y,Z)
//	#define _simd_f64x2_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_fma_instruction_set>()
//#elif defined(_simd_f64x4_fma_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_fma(const register _simd_f64x2 x, const register _simd_f64x2 y, const register _simd_f64x2 z) {
//		union SIMDUnion { _simd_f64x2 v1; _simd_f64x4 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_f64x4_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x2_fma_enable() _simd_f64x4_fma_enable()
//#elif defined(_simd_f64x8_fma_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_fma(const register _simd_f64x2 x, const register _simd_f64x2 y, const register _simd_f64x2 z) {
//		union SIMDUnion { _simd_f64x2 v1; _simd_f64x8 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_f64x8_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x2_fma_enable() _simd_f64x8_fma_enable()
//#elif defined(_simd_f64x16_fma_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_fma(const register _simd_f64x2 x, const register _simd_f64x2 y, const register _simd_f64x2 z) {
//		union SIMDUnion { _simd_f64x2 v1; _simd_f64x16 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_f64x16_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x2_fma_enable() _simd_f64x16_fma_enable()
//#elif defined(_simd_f64x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_fma(const register _simd_f64x2 x, const register _simd_f64x2 y, const register _simd_f64x2 z) {
//		union SIMDUnion { _simd_f64x2 v1; _simd_f64x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_f64x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x2_fma_enable() _simd_f64x32_fma_enable()
//#elif defined(_simd_f64x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_fma(const register _simd_f64x2 x, const register _simd_f64x2 y, const register _simd_f64x2 z) {
//		union SIMDUnion { _simd_f64x2 v1; _simd_f64x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_f64x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x2_fma_enable() _simd_f64x64_fma_enable()
//#else
//	#define _simd_f64x2_fma(X,Y,Z) _simd_f64x2_combine(\
//		_simd_f64x1_fma(_simd_f64x2_splitlo(X), _simd_f64x2_splitlo(Y), _simd_f64x2_splitlo(Z)),\
//		_simd_f64x1_fma(_simd_f64x2_splithi(X), _simd_f64x2_splithi(Y), _simd_f64x2_splithi(Z)))
//	#define _simd_f64x2_fma_enable() (_simd_f64x1_fma_enable() && _simd_f64x2_combine_enable() && _simd_f64x2_splitlo_enable()  && _simd_f64x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x2_fma_) && ! defined(_simd_f64x2_fma_scalar_)
//	#define _simd_f64x2_fma_scalar_(X,Y,Z) _simd_f64x2_fma_(X,_simd_f64x2_fill_scalar_(Y),_simd_f64x2_fill_scalar_(Z))
//	#define _simd_f64x2_fma_scalar_instruction_set _simd_f64x2_fma_instruction_set
//#endif
//#ifdef _simd_f64x2_fma_scalar_
//	#define _simd_f64x2_fma_scalar(X,Y,Z) _simd_f64x2_fma_scalar_(X,Y,Z)
//	#define _simd_f64x2_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_fma_scalar_instruction_set>()
//#else
//	#define _simd_f64x2_fma_scalar(X,Y,Z) _simd_f64x2_fma_safe(X,_simd_f64x2_fill_scalar_safe(Y),_simd_f64x2_fill_scalar_safe(Z))
//	#define _simd_f64x2_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_f64x1_fma_safe
//	#define _simd_f64x1_fma_safe(X,Y,Z) std::fma(X,Y,Z)
//	#define _simd_f64x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_f64x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_fma_enabled() true
//#endif
//
//#define _simd_f64x4_fma_safe(X,Y,Z)_simd_f64x4_combine_safe(\
//	_simd_f64x2_fma_safe(_simd_f64x4_splitlo_safe(X), _simd_ f64x4_splitlo_safe(Y), _simd_ f64x4_splitlo_safe(Z)),\
//	_simd_f64x2_fma_safe(_simd_f64x4_splithi_safe(X), _simd_ f64x4_splithi_safe(Y), _simd_ f64x4_splithi_safe(Z)))
//#ifdef _simd_f64x4_fma_
//	#define _simd_f64x4_fma(X,Y,Z) _simd_f64x4_fma_(X,Y,Z)
//	#define _simd_f64x4_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_fma_instruction_set>()
//#elif defined(_simd_f64x8_fma_)
//	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_fma(const register _simd_f64x4 x, const register _simd_f64x4 y, const register _simd_f64x4 z) {
//		union SIMDUnion { _simd_f64x4 v1; _simd_f64x8 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_f64x8_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x4_fma_enable() _simd_f64x8_fma_enable()
//#elif defined(_simd_f64x16_fma_)
//	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_fma(const register _simd_f64x4 x, const register _simd_f64x4 y, const register _simd_f64x4 z) {
//		union SIMDUnion { _simd_f64x4 v1; _simd_f64x16 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_f64x16_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x4_fma_enable() _simd_f64x16_fma_enable()
//#elif defined(_simd_f64x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_fma(const register _simd_f64x4 x, const register _simd_f64x4 y, const register _simd_f64x4 z) {
//		union SIMDUnion { _simd_f64x4 v1; _simd_f64x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_f64x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x4_fma_enable() _simd_f64x32_fma_enable()
//#elif defined(_simd_f64x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_fma(const register _simd_f64x4 x, const register _simd_f64x4 y, const register _simd_f64x4 z) {
//		union SIMDUnion { _simd_f64x4 v1; _simd_f64x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_f64x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x4_fma_enable() _simd_f64x64_fma_enable()
//#else
//	#define _simd_f64x4_fma(X,Y,Z) _simd_f64x4_combine(\
//		_simd_f64x2_fma(_simd_f64x4_splitlo(X), _simd_f64x4_splitlo(Y), _simd_f64x4_splitlo(Z)),\
//		_simd_f64x2_fma(_simd_f64x4_splithi(X), _simd_f64x4_splithi(Y), _simd_f64x4_splithi(Z)))
//	#define _simd_f64x4_fma_enable() (_simd_f64x2_fma_enable() && _simd_f64x4_combine_enable() && _simd_f64x4_splitlo_enable()  && _simd_f64x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x4_fma_) && ! defined(_simd_f64x4_fma_scalar_)
//	#define _simd_f64x4_fma_scalar_(X,Y,Z) _simd_f64x4_fma_(X,_simd_f64x4_fill_scalar_(Y),_simd_f64x4_fill_scalar_(Z))
//	#define _simd_f64x4_fma_scalar_instruction_set _simd_f64x4_fma_instruction_set
//#endif
//#ifdef _simd_f64x4_fma_scalar_
//	#define _simd_f64x4_fma_scalar(X,Y,Z) _simd_f64x4_fma_scalar_(X,Y,Z)
//	#define _simd_f64x4_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_fma_scalar_instruction_set>()
//#else
//	#define _simd_f64x4_fma_scalar(X,Y,Z) _simd_f64x4_fma_safe(X,_simd_f64x4_fill_scalar_safe(Y),_simd_f64x4_fill_scalar_safe(Z))
//	#define _simd_f64x4_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_f64x1_fma_safe
//	#define _simd_f64x1_fma_safe(X,Y,Z) std::fma(X,Y,Z)
//	#define _simd_f64x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_f64x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_fma_enabled() true
//#endif
//
//#define _simd_f64x8_fma_safe(X,Y,Z)_simd_f64x8_combine_safe(\
//	_simd_f64x4_fma_safe(_simd_f64x8_splitlo_safe(X), _simd_ f64x8_splitlo_safe(Y), _simd_ f64x8_splitlo_safe(Z)),\
//	_simd_f64x4_fma_safe(_simd_f64x8_splithi_safe(X), _simd_ f64x8_splithi_safe(Y), _simd_ f64x8_splithi_safe(Z)))
//#ifdef _simd_f64x8_fma_
//	#define _simd_f64x8_fma(X,Y,Z) _simd_f64x8_fma_(X,Y,Z)
//	#define _simd_f64x8_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_fma_instruction_set>()
//#elif defined(_simd_f64x16_fma_)
//	static ANVIL_STRONG_INLINE _simd_f64x8 ANVIL_SIMD_CALL _simd_f64x8_fma(const register _simd_f64x8 x, const register _simd_f64x8 y, const register _simd_f64x8 z) {
//		union SIMDUnion { _simd_f64x8 v1; _simd_f64x16 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_f64x16_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x8_fma_enable() _simd_f64x16_fma_enable()
//#elif defined(_simd_f64x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_f64x8 ANVIL_SIMD_CALL _simd_f64x8_fma(const register _simd_f64x8 x, const register _simd_f64x8 y, const register _simd_f64x8 z) {
//		union SIMDUnion { _simd_f64x8 v1; _simd_f64x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_f64x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x8_fma_enable() _simd_f64x32_fma_enable()
//#elif defined(_simd_f64x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_f64x8 ANVIL_SIMD_CALL _simd_f64x8_fma(const register _simd_f64x8 x, const register _simd_f64x8 y, const register _simd_f64x8 z) {
//		union SIMDUnion { _simd_f64x8 v1; _simd_f64x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_f64x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x8_fma_enable() _simd_f64x64_fma_enable()
//#else
//	#define _simd_f64x8_fma(X,Y,Z) _simd_f64x8_combine(\
//		_simd_f64x4_fma(_simd_f64x8_splitlo(X), _simd_f64x8_splitlo(Y), _simd_f64x8_splitlo(Z)),\
//		_simd_f64x4_fma(_simd_f64x8_splithi(X), _simd_f64x8_splithi(Y), _simd_f64x8_splithi(Z)))
//	#define _simd_f64x8_fma_enable() (_simd_f64x4_fma_enable() && _simd_f64x8_combine_enable() && _simd_f64x8_splitlo_enable()  && _simd_f64x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x8_fma_) && ! defined(_simd_f64x8_fma_scalar_)
//	#define _simd_f64x8_fma_scalar_(X,Y,Z) _simd_f64x8_fma_(X,_simd_f64x8_fill_scalar_(Y),_simd_f64x8_fill_scalar_(Z))
//	#define _simd_f64x8_fma_scalar_instruction_set _simd_f64x8_fma_instruction_set
//#endif
//#ifdef _simd_f64x8_fma_scalar_
//	#define _simd_f64x8_fma_scalar(X,Y,Z) _simd_f64x8_fma_scalar_(X,Y,Z)
//	#define _simd_f64x8_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_fma_scalar_instruction_set>()
//#else
//	#define _simd_f64x8_fma_scalar(X,Y,Z) _simd_f64x8_fma_safe(X,_simd_f64x8_fill_scalar_safe(Y),_simd_f64x8_fill_scalar_safe(Z))
//	#define _simd_f64x8_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_f64x1_fma_safe
//	#define _simd_f64x1_fma_safe(X,Y,Z) std::fma(X,Y,Z)
//	#define _simd_f64x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_f64x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_fma_enabled() true
//#endif
//
//#define _simd_f64x16_fma_safe(X,Y,Z)_simd_f64x16_combine_safe(\
//	_simd_f64x8_fma_safe(_simd_f64x16_splitlo_safe(X), _simd_ f64x16_splitlo_safe(Y), _simd_ f64x16_splitlo_safe(Z)),\
//	_simd_f64x8_fma_safe(_simd_f64x16_splithi_safe(X), _simd_ f64x16_splithi_safe(Y), _simd_ f64x16_splithi_safe(Z)))
//#ifdef _simd_f64x16_fma_
//	#define _simd_f64x16_fma(X,Y,Z) _simd_f64x16_fma_(X,Y,Z)
//	#define _simd_f64x16_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_fma_instruction_set>()
//#elif defined(_simd_f64x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_f64x16 ANVIL_SIMD_CALL _simd_f64x16_fma(const register _simd_f64x16 x, const register _simd_f64x16 y, const register _simd_f64x16 z) {
//		union SIMDUnion { _simd_f64x16 v1; _simd_f64x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_f64x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x16_fma_enable() _simd_f64x32_fma_enable()
//#elif defined(_simd_f64x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_f64x16 ANVIL_SIMD_CALL _simd_f64x16_fma(const register _simd_f64x16 x, const register _simd_f64x16 y, const register _simd_f64x16 z) {
//		union SIMDUnion { _simd_f64x16 v1; _simd_f64x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_f64x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x16_fma_enable() _simd_f64x64_fma_enable()
//#else
//	#define _simd_f64x16_fma(X,Y,Z) _simd_f64x16_combine(\
//		_simd_f64x8_fma(_simd_f64x16_splitlo(X), _simd_f64x16_splitlo(Y), _simd_f64x16_splitlo(Z)),\
//		_simd_f64x8_fma(_simd_f64x16_splithi(X), _simd_f64x16_splithi(Y), _simd_f64x16_splithi(Z)))
//	#define _simd_f64x16_fma_enable() (_simd_f64x8_fma_enable() && _simd_f64x16_combine_enable() && _simd_f64x16_splitlo_enable()  && _simd_f64x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x16_fma_) && ! defined(_simd_f64x16_fma_scalar_)
//	#define _simd_f64x16_fma_scalar_(X,Y,Z) _simd_f64x16_fma_(X,_simd_f64x16_fill_scalar_(Y),_simd_f64x16_fill_scalar_(Z))
//	#define _simd_f64x16_fma_scalar_instruction_set _simd_f64x16_fma_instruction_set
//#endif
//#ifdef _simd_f64x16_fma_scalar_
//	#define _simd_f64x16_fma_scalar(X,Y,Z) _simd_f64x16_fma_scalar_(X,Y,Z)
//	#define _simd_f64x16_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_fma_scalar_instruction_set>()
//#else
//	#define _simd_f64x16_fma_scalar(X,Y,Z) _simd_f64x16_fma_safe(X,_simd_f64x16_fill_scalar_safe(Y),_simd_f64x16_fill_scalar_safe(Z))
//	#define _simd_f64x16_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_f64x1_fma_safe
//	#define _simd_f64x1_fma_safe(X,Y,Z) std::fma(X,Y,Z)
//	#define _simd_f64x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_f64x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_fma_enabled() true
//#endif
//
//#define _simd_f64x32_fma_safe(X,Y,Z)_simd_f64x32_combine_safe(\
//	_simd_f64x16_fma_safe(_simd_f64x32_splitlo_safe(X), _simd_ f64x32_splitlo_safe(Y), _simd_ f64x32_splitlo_safe(Z)),\
//	_simd_f64x16_fma_safe(_simd_f64x32_splithi_safe(X), _simd_ f64x32_splithi_safe(Y), _simd_ f64x32_splithi_safe(Z)))
//#ifdef _simd_f64x32_fma_
//	#define _simd_f64x32_fma(X,Y,Z) _simd_f64x32_fma_(X,Y,Z)
//	#define _simd_f64x32_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_fma_instruction_set>()
//#elif defined(_simd_f64x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_f64x32 ANVIL_SIMD_CALL _simd_f64x32_fma(const register _simd_f64x32 x, const register _simd_f64x32 y, const register _simd_f64x32 z) {
//		union SIMDUnion { _simd_f64x32 v1; _simd_f64x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_f64x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x32_fma_enable() _simd_f64x64_fma_enable()
//#else
//	#define _simd_f64x32_fma(X,Y,Z) _simd_f64x32_combine(\
//		_simd_f64x16_fma(_simd_f64x32_splitlo(X), _simd_f64x32_splitlo(Y), _simd_f64x32_splitlo(Z)),\
//		_simd_f64x16_fma(_simd_f64x32_splithi(X), _simd_f64x32_splithi(Y), _simd_f64x32_splithi(Z)))
//	#define _simd_f64x32_fma_enable() (_simd_f64x16_fma_enable() && _simd_f64x32_combine_enable() && _simd_f64x32_splitlo_enable()  && _simd_f64x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x32_fma_) && ! defined(_simd_f64x32_fma_scalar_)
//	#define _simd_f64x32_fma_scalar_(X,Y,Z) _simd_f64x32_fma_(X,_simd_f64x32_fill_scalar_(Y),_simd_f64x32_fill_scalar_(Z))
//	#define _simd_f64x32_fma_scalar_instruction_set _simd_f64x32_fma_instruction_set
//#endif
//#ifdef _simd_f64x32_fma_scalar_
//	#define _simd_f64x32_fma_scalar(X,Y,Z) _simd_f64x32_fma_scalar_(X,Y,Z)
//	#define _simd_f64x32_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_fma_scalar_instruction_set>()
//#else
//	#define _simd_f64x32_fma_scalar(X,Y,Z) _simd_f64x32_fma_safe(X,_simd_f64x32_fill_scalar_safe(Y),_simd_f64x32_fill_scalar_safe(Z))
//	#define _simd_f64x32_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_f64x1_fma_safe
//	#define _simd_f64x1_fma_safe(X,Y,Z) std::fma(X,Y,Z)
//	#define _simd_f64x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_f64x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_fma_enabled() true
//#endif
//
//#define _simd_f64x64_fma_safe(X,Y,Z)_simd_f64x64_combine_safe(\
//	_simd_f64x32_fma_safe(_simd_f64x64_splitlo_safe(X), _simd_ f64x64_splitlo_safe(Y), _simd_ f64x64_splitlo_safe(Z)),\
//	_simd_f64x32_fma_safe(_simd_f64x64_splithi_safe(X), _simd_ f64x64_splithi_safe(Y), _simd_ f64x64_splithi_safe(Z)))
//#ifdef _simd_f64x64_fma_
//	#define _simd_f64x64_fma(X,Y,Z) _simd_f64x64_fma_(X,Y,Z)
//	#define _simd_f64x64_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_fma_instruction_set>()
//#else
//	#define _simd_f64x64_fma(X,Y,Z) _simd_f64x64_combine(\
//		_simd_f64x32_fma(_simd_f64x64_splitlo(X), _simd_f64x64_splitlo(Y), _simd_f64x64_splitlo(Z)),\
//		_simd_f64x32_fma(_simd_f64x64_splithi(X), _simd_f64x64_splithi(Y), _simd_f64x64_splithi(Z)))
//	#define _simd_f64x64_fma_enable() (_simd_f64x32_fma_enable() && _simd_f64x64_combine_enable() && _simd_f64x64_splitlo_enable()  && _simd_f64x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x64_fma_) && ! defined(_simd_f64x64_fma_scalar_)
//	#define _simd_f64x64_fma_scalar_(X,Y,Z) _simd_f64x64_fma_(X,_simd_f64x64_fill_scalar_(Y),_simd_f64x64_fill_scalar_(Z))
//	#define _simd_f64x64_fma_scalar_instruction_set _simd_f64x64_fma_instruction_set
//#endif
//#ifdef _simd_f64x64_fma_scalar_
//	#define _simd_f64x64_fma_scalar(X,Y,Z) _simd_f64x64_fma_scalar_(X,Y,Z)
//	#define _simd_f64x64_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_fma_scalar_instruction_set>()
//#else
//	#define _simd_f64x64_fma_scalar(X,Y,Z) _simd_f64x64_fma_safe(X,_simd_f64x64_fill_scalar_safe(Y),_simd_f64x64_fill_scalar_safe(Z))
//	#define _simd_f64x64_fma_scalar_enabled() true
//#endif
//
//// -- f32 --
//
//#ifndef _simd_f32x1_fma_safe
//	#define _simd_f32x1_fma_safe(X,Y,Z) std::fma(X,Y,Z)
//	#define _simd_f32x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_f32x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_fma_enabled() true
//#endif
//
//#define _simd_f32x2_fma_safe(X,Y,Z)_simd_f32x2_combine_safe(\
//	_simd_f32x1_fma_safe(_simd_f32x2_splitlo_safe(X), _simd_ f32x2_splitlo_safe(Y), _simd_ f32x2_splitlo_safe(Z)),\
//	_simd_f32x1_fma_safe(_simd_f32x2_splithi_safe(X), _simd_ f32x2_splithi_safe(Y), _simd_ f32x2_splithi_safe(Z)))
//#ifdef _simd_f32x2_fma_
//	#define _simd_f32x2_fma(X,Y,Z) _simd_f32x2_fma_(X,Y,Z)
//	#define _simd_f32x2_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_fma_instruction_set>()
//#elif defined(_simd_f32x4_fma_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_fma(const register _simd_f32x2 x, const register _simd_f32x2 y, const register _simd_f32x2 z) {
//		union SIMDUnion { _simd_f32x2 v1; _simd_f32x4 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_f32x4_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x2_fma_enable() _simd_f32x4_fma_enable()
//#elif defined(_simd_f32x8_fma_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_fma(const register _simd_f32x2 x, const register _simd_f32x2 y, const register _simd_f32x2 z) {
//		union SIMDUnion { _simd_f32x2 v1; _simd_f32x8 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_f32x8_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x2_fma_enable() _simd_f32x8_fma_enable()
//#elif defined(_simd_f32x16_fma_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_fma(const register _simd_f32x2 x, const register _simd_f32x2 y, const register _simd_f32x2 z) {
//		union SIMDUnion { _simd_f32x2 v1; _simd_f32x16 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_f32x16_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x2_fma_enable() _simd_f32x16_fma_enable()
//#elif defined(_simd_f32x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_fma(const register _simd_f32x2 x, const register _simd_f32x2 y, const register _simd_f32x2 z) {
//		union SIMDUnion { _simd_f32x2 v1; _simd_f32x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_f32x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x2_fma_enable() _simd_f32x32_fma_enable()
//#elif defined(_simd_f32x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_fma(const register _simd_f32x2 x, const register _simd_f32x2 y, const register _simd_f32x2 z) {
//		union SIMDUnion { _simd_f32x2 v1; _simd_f32x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_f32x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x2_fma_enable() _simd_f32x64_fma_enable()
//#else
//	#define _simd_f32x2_fma(X,Y,Z) _simd_f32x2_combine(\
//		_simd_f32x1_fma(_simd_f32x2_splitlo(X), _simd_f32x2_splitlo(Y), _simd_f32x2_splitlo(Z)),\
//		_simd_f32x1_fma(_simd_f32x2_splithi(X), _simd_f32x2_splithi(Y), _simd_f32x2_splithi(Z)))
//	#define _simd_f32x2_fma_enable() (_simd_f32x1_fma_enable() && _simd_f32x2_combine_enable() && _simd_f32x2_splitlo_enable()  && _simd_f32x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x2_fma_) && ! defined(_simd_f32x2_fma_scalar_)
//	#define _simd_f32x2_fma_scalar_(X,Y,Z) _simd_f32x2_fma_(X,_simd_f32x2_fill_scalar_(Y),_simd_f32x2_fill_scalar_(Z))
//	#define _simd_f32x2_fma_scalar_instruction_set _simd_f32x2_fma_instruction_set
//#endif
//#ifdef _simd_f32x2_fma_scalar_
//	#define _simd_f32x2_fma_scalar(X,Y,Z) _simd_f32x2_fma_scalar_(X,Y,Z)
//	#define _simd_f32x2_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_fma_scalar_instruction_set>()
//#else
//	#define _simd_f32x2_fma_scalar(X,Y,Z) _simd_f32x2_fma_safe(X,_simd_f32x2_fill_scalar_safe(Y),_simd_f32x2_fill_scalar_safe(Z))
//	#define _simd_f32x2_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_f32x1_fma_safe
//	#define _simd_f32x1_fma_safe(X,Y,Z) std::fma(X,Y,Z)
//	#define _simd_f32x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_f32x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_fma_enabled() true
//#endif
//
//#define _simd_f32x4_fma_safe(X,Y,Z)_simd_f32x4_combine_safe(\
//	_simd_f32x2_fma_safe(_simd_f32x4_splitlo_safe(X), _simd_ f32x4_splitlo_safe(Y), _simd_ f32x4_splitlo_safe(Z)),\
//	_simd_f32x2_fma_safe(_simd_f32x4_splithi_safe(X), _simd_ f32x4_splithi_safe(Y), _simd_ f32x4_splithi_safe(Z)))
//#ifdef _simd_f32x4_fma_
//	#define _simd_f32x4_fma(X,Y,Z) _simd_f32x4_fma_(X,Y,Z)
//	#define _simd_f32x4_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_fma_instruction_set>()
//#elif defined(_simd_f32x8_fma_)
//	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_fma(const register _simd_f32x4 x, const register _simd_f32x4 y, const register _simd_f32x4 z) {
//		union SIMDUnion { _simd_f32x4 v1; _simd_f32x8 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_f32x8_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x4_fma_enable() _simd_f32x8_fma_enable()
//#elif defined(_simd_f32x16_fma_)
//	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_fma(const register _simd_f32x4 x, const register _simd_f32x4 y, const register _simd_f32x4 z) {
//		union SIMDUnion { _simd_f32x4 v1; _simd_f32x16 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_f32x16_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x4_fma_enable() _simd_f32x16_fma_enable()
//#elif defined(_simd_f32x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_fma(const register _simd_f32x4 x, const register _simd_f32x4 y, const register _simd_f32x4 z) {
//		union SIMDUnion { _simd_f32x4 v1; _simd_f32x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_f32x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x4_fma_enable() _simd_f32x32_fma_enable()
//#elif defined(_simd_f32x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_fma(const register _simd_f32x4 x, const register _simd_f32x4 y, const register _simd_f32x4 z) {
//		union SIMDUnion { _simd_f32x4 v1; _simd_f32x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_f32x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x4_fma_enable() _simd_f32x64_fma_enable()
//#else
//	#define _simd_f32x4_fma(X,Y,Z) _simd_f32x4_combine(\
//		_simd_f32x2_fma(_simd_f32x4_splitlo(X), _simd_f32x4_splitlo(Y), _simd_f32x4_splitlo(Z)),\
//		_simd_f32x2_fma(_simd_f32x4_splithi(X), _simd_f32x4_splithi(Y), _simd_f32x4_splithi(Z)))
//	#define _simd_f32x4_fma_enable() (_simd_f32x2_fma_enable() && _simd_f32x4_combine_enable() && _simd_f32x4_splitlo_enable()  && _simd_f32x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x4_fma_) && ! defined(_simd_f32x4_fma_scalar_)
//	#define _simd_f32x4_fma_scalar_(X,Y,Z) _simd_f32x4_fma_(X,_simd_f32x4_fill_scalar_(Y),_simd_f32x4_fill_scalar_(Z))
//	#define _simd_f32x4_fma_scalar_instruction_set _simd_f32x4_fma_instruction_set
//#endif
//#ifdef _simd_f32x4_fma_scalar_
//	#define _simd_f32x4_fma_scalar(X,Y,Z) _simd_f32x4_fma_scalar_(X,Y,Z)
//	#define _simd_f32x4_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_fma_scalar_instruction_set>()
//#else
//	#define _simd_f32x4_fma_scalar(X,Y,Z) _simd_f32x4_fma_safe(X,_simd_f32x4_fill_scalar_safe(Y),_simd_f32x4_fill_scalar_safe(Z))
//	#define _simd_f32x4_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_f32x1_fma_safe
//	#define _simd_f32x1_fma_safe(X,Y,Z) std::fma(X,Y,Z)
//	#define _simd_f32x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_f32x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_fma_enabled() true
//#endif
//
//#define _simd_f32x8_fma_safe(X,Y,Z)_simd_f32x8_combine_safe(\
//	_simd_f32x4_fma_safe(_simd_f32x8_splitlo_safe(X), _simd_ f32x8_splitlo_safe(Y), _simd_ f32x8_splitlo_safe(Z)),\
//	_simd_f32x4_fma_safe(_simd_f32x8_splithi_safe(X), _simd_ f32x8_splithi_safe(Y), _simd_ f32x8_splithi_safe(Z)))
//#ifdef _simd_f32x8_fma_
//	#define _simd_f32x8_fma(X,Y,Z) _simd_f32x8_fma_(X,Y,Z)
//	#define _simd_f32x8_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_fma_instruction_set>()
//#elif defined(_simd_f32x16_fma_)
//	static ANVIL_STRONG_INLINE _simd_f32x8 ANVIL_SIMD_CALL _simd_f32x8_fma(const register _simd_f32x8 x, const register _simd_f32x8 y, const register _simd_f32x8 z) {
//		union SIMDUnion { _simd_f32x8 v1; _simd_f32x16 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_f32x16_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x8_fma_enable() _simd_f32x16_fma_enable()
//#elif defined(_simd_f32x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_f32x8 ANVIL_SIMD_CALL _simd_f32x8_fma(const register _simd_f32x8 x, const register _simd_f32x8 y, const register _simd_f32x8 z) {
//		union SIMDUnion { _simd_f32x8 v1; _simd_f32x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_f32x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x8_fma_enable() _simd_f32x32_fma_enable()
//#elif defined(_simd_f32x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_f32x8 ANVIL_SIMD_CALL _simd_f32x8_fma(const register _simd_f32x8 x, const register _simd_f32x8 y, const register _simd_f32x8 z) {
//		union SIMDUnion { _simd_f32x8 v1; _simd_f32x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_f32x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x8_fma_enable() _simd_f32x64_fma_enable()
//#else
//	#define _simd_f32x8_fma(X,Y,Z) _simd_f32x8_combine(\
//		_simd_f32x4_fma(_simd_f32x8_splitlo(X), _simd_f32x8_splitlo(Y), _simd_f32x8_splitlo(Z)),\
//		_simd_f32x4_fma(_simd_f32x8_splithi(X), _simd_f32x8_splithi(Y), _simd_f32x8_splithi(Z)))
//	#define _simd_f32x8_fma_enable() (_simd_f32x4_fma_enable() && _simd_f32x8_combine_enable() && _simd_f32x8_splitlo_enable()  && _simd_f32x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x8_fma_) && ! defined(_simd_f32x8_fma_scalar_)
//	#define _simd_f32x8_fma_scalar_(X,Y,Z) _simd_f32x8_fma_(X,_simd_f32x8_fill_scalar_(Y),_simd_f32x8_fill_scalar_(Z))
//	#define _simd_f32x8_fma_scalar_instruction_set _simd_f32x8_fma_instruction_set
//#endif
//#ifdef _simd_f32x8_fma_scalar_
//	#define _simd_f32x8_fma_scalar(X,Y,Z) _simd_f32x8_fma_scalar_(X,Y,Z)
//	#define _simd_f32x8_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_fma_scalar_instruction_set>()
//#else
//	#define _simd_f32x8_fma_scalar(X,Y,Z) _simd_f32x8_fma_safe(X,_simd_f32x8_fill_scalar_safe(Y),_simd_f32x8_fill_scalar_safe(Z))
//	#define _simd_f32x8_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_f32x1_fma_safe
//	#define _simd_f32x1_fma_safe(X,Y,Z) std::fma(X,Y,Z)
//	#define _simd_f32x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_f32x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_fma_enabled() true
//#endif
//
//#define _simd_f32x16_fma_safe(X,Y,Z)_simd_f32x16_combine_safe(\
//	_simd_f32x8_fma_safe(_simd_f32x16_splitlo_safe(X), _simd_ f32x16_splitlo_safe(Y), _simd_ f32x16_splitlo_safe(Z)),\
//	_simd_f32x8_fma_safe(_simd_f32x16_splithi_safe(X), _simd_ f32x16_splithi_safe(Y), _simd_ f32x16_splithi_safe(Z)))
//#ifdef _simd_f32x16_fma_
//	#define _simd_f32x16_fma(X,Y,Z) _simd_f32x16_fma_(X,Y,Z)
//	#define _simd_f32x16_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_fma_instruction_set>()
//#elif defined(_simd_f32x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_f32x16 ANVIL_SIMD_CALL _simd_f32x16_fma(const register _simd_f32x16 x, const register _simd_f32x16 y, const register _simd_f32x16 z) {
//		union SIMDUnion { _simd_f32x16 v1; _simd_f32x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_f32x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x16_fma_enable() _simd_f32x32_fma_enable()
//#elif defined(_simd_f32x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_f32x16 ANVIL_SIMD_CALL _simd_f32x16_fma(const register _simd_f32x16 x, const register _simd_f32x16 y, const register _simd_f32x16 z) {
//		union SIMDUnion { _simd_f32x16 v1; _simd_f32x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_f32x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x16_fma_enable() _simd_f32x64_fma_enable()
//#else
//	#define _simd_f32x16_fma(X,Y,Z) _simd_f32x16_combine(\
//		_simd_f32x8_fma(_simd_f32x16_splitlo(X), _simd_f32x16_splitlo(Y), _simd_f32x16_splitlo(Z)),\
//		_simd_f32x8_fma(_simd_f32x16_splithi(X), _simd_f32x16_splithi(Y), _simd_f32x16_splithi(Z)))
//	#define _simd_f32x16_fma_enable() (_simd_f32x8_fma_enable() && _simd_f32x16_combine_enable() && _simd_f32x16_splitlo_enable()  && _simd_f32x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x16_fma_) && ! defined(_simd_f32x16_fma_scalar_)
//	#define _simd_f32x16_fma_scalar_(X,Y,Z) _simd_f32x16_fma_(X,_simd_f32x16_fill_scalar_(Y),_simd_f32x16_fill_scalar_(Z))
//	#define _simd_f32x16_fma_scalar_instruction_set _simd_f32x16_fma_instruction_set
//#endif
//#ifdef _simd_f32x16_fma_scalar_
//	#define _simd_f32x16_fma_scalar(X,Y,Z) _simd_f32x16_fma_scalar_(X,Y,Z)
//	#define _simd_f32x16_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_fma_scalar_instruction_set>()
//#else
//	#define _simd_f32x16_fma_scalar(X,Y,Z) _simd_f32x16_fma_safe(X,_simd_f32x16_fill_scalar_safe(Y),_simd_f32x16_fill_scalar_safe(Z))
//	#define _simd_f32x16_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_f32x1_fma_safe
//	#define _simd_f32x1_fma_safe(X,Y,Z) std::fma(X,Y,Z)
//	#define _simd_f32x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_f32x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_fma_enabled() true
//#endif
//
//#define _simd_f32x32_fma_safe(X,Y,Z)_simd_f32x32_combine_safe(\
//	_simd_f32x16_fma_safe(_simd_f32x32_splitlo_safe(X), _simd_ f32x32_splitlo_safe(Y), _simd_ f32x32_splitlo_safe(Z)),\
//	_simd_f32x16_fma_safe(_simd_f32x32_splithi_safe(X), _simd_ f32x32_splithi_safe(Y), _simd_ f32x32_splithi_safe(Z)))
//#ifdef _simd_f32x32_fma_
//	#define _simd_f32x32_fma(X,Y,Z) _simd_f32x32_fma_(X,Y,Z)
//	#define _simd_f32x32_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_fma_instruction_set>()
//#elif defined(_simd_f32x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_f32x32 ANVIL_SIMD_CALL _simd_f32x32_fma(const register _simd_f32x32 x, const register _simd_f32x32 y, const register _simd_f32x32 z) {
//		union SIMDUnion { _simd_f32x32 v1; _simd_f32x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_f32x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x32_fma_enable() _simd_f32x64_fma_enable()
//#else
//	#define _simd_f32x32_fma(X,Y,Z) _simd_f32x32_combine(\
//		_simd_f32x16_fma(_simd_f32x32_splitlo(X), _simd_f32x32_splitlo(Y), _simd_f32x32_splitlo(Z)),\
//		_simd_f32x16_fma(_simd_f32x32_splithi(X), _simd_f32x32_splithi(Y), _simd_f32x32_splithi(Z)))
//	#define _simd_f32x32_fma_enable() (_simd_f32x16_fma_enable() && _simd_f32x32_combine_enable() && _simd_f32x32_splitlo_enable()  && _simd_f32x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x32_fma_) && ! defined(_simd_f32x32_fma_scalar_)
//	#define _simd_f32x32_fma_scalar_(X,Y,Z) _simd_f32x32_fma_(X,_simd_f32x32_fill_scalar_(Y),_simd_f32x32_fill_scalar_(Z))
//	#define _simd_f32x32_fma_scalar_instruction_set _simd_f32x32_fma_instruction_set
//#endif
//#ifdef _simd_f32x32_fma_scalar_
//	#define _simd_f32x32_fma_scalar(X,Y,Z) _simd_f32x32_fma_scalar_(X,Y,Z)
//	#define _simd_f32x32_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_fma_scalar_instruction_set>()
//#else
//	#define _simd_f32x32_fma_scalar(X,Y,Z) _simd_f32x32_fma_safe(X,_simd_f32x32_fill_scalar_safe(Y),_simd_f32x32_fill_scalar_safe(Z))
//	#define _simd_f32x32_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_f32x1_fma_safe
//	#define _simd_f32x1_fma_safe(X,Y,Z) std::fma(X,Y,Z)
//	#define _simd_f32x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_f32x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_fma_enabled() true
//#endif
//
//#define _simd_f32x64_fma_safe(X,Y,Z)_simd_f32x64_combine_safe(\
//	_simd_f32x32_fma_safe(_simd_f32x64_splitlo_safe(X), _simd_ f32x64_splitlo_safe(Y), _simd_ f32x64_splitlo_safe(Z)),\
//	_simd_f32x32_fma_safe(_simd_f32x64_splithi_safe(X), _simd_ f32x64_splithi_safe(Y), _simd_ f32x64_splithi_safe(Z)))
//#ifdef _simd_f32x64_fma_
//	#define _simd_f32x64_fma(X,Y,Z) _simd_f32x64_fma_(X,Y,Z)
//	#define _simd_f32x64_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_fma_instruction_set>()
//#else
//	#define _simd_f32x64_fma(X,Y,Z) _simd_f32x64_combine(\
//		_simd_f32x32_fma(_simd_f32x64_splitlo(X), _simd_f32x64_splitlo(Y), _simd_f32x64_splitlo(Z)),\
//		_simd_f32x32_fma(_simd_f32x64_splithi(X), _simd_f32x64_splithi(Y), _simd_f32x64_splithi(Z)))
//	#define _simd_f32x64_fma_enable() (_simd_f32x32_fma_enable() && _simd_f32x64_combine_enable() && _simd_f32x64_splitlo_enable()  && _simd_f32x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x64_fma_) && ! defined(_simd_f32x64_fma_scalar_)
//	#define _simd_f32x64_fma_scalar_(X,Y,Z) _simd_f32x64_fma_(X,_simd_f32x64_fill_scalar_(Y),_simd_f32x64_fill_scalar_(Z))
//	#define _simd_f32x64_fma_scalar_instruction_set _simd_f32x64_fma_instruction_set
//#endif
//#ifdef _simd_f32x64_fma_scalar_
//	#define _simd_f32x64_fma_scalar(X,Y,Z) _simd_f32x64_fma_scalar_(X,Y,Z)
//	#define _simd_f32x64_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_fma_scalar_instruction_set>()
//#else
//	#define _simd_f32x64_fma_scalar(X,Y,Z) _simd_f32x64_fma_safe(X,_simd_f32x64_fill_scalar_safe(Y),_simd_f32x64_fill_scalar_safe(Z))
//	#define _simd_f32x64_fma_scalar_enabled() true
//#endif
//
//// -- s64 --
//
//#ifndef _simd_s64x1_fma_safe
//	#define _simd_s64x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_s64x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_s64x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_fma_enabled() true
//#endif
//
//#define _simd_s64x2_fma_safe(X,Y,Z)_simd_s64x2_combine_safe(\
//	_simd_s64x1_fma_safe(_simd_s64x2_splitlo_safe(X), _simd_ s64x2_splitlo_safe(Y), _simd_ s64x2_splitlo_safe(Z)),\
//	_simd_s64x1_fma_safe(_simd_s64x2_splithi_safe(X), _simd_ s64x2_splithi_safe(Y), _simd_ s64x2_splithi_safe(Z)))
//#ifdef _simd_s64x2_fma_
//	#define _simd_s64x2_fma(X,Y,Z) _simd_s64x2_fma_(X,Y,Z)
//	#define _simd_s64x2_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_fma_instruction_set>()
//#elif defined(_simd_s64x4_fma_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_fma(const register _simd_s64x2 x, const register _simd_s64x2 y, const register _simd_s64x2 z) {
//		union SIMDUnion { _simd_s64x2 v1; _simd_s64x4 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s64x4_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x2_fma_enable() _simd_s64x4_fma_enable()
//#elif defined(_simd_s64x8_fma_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_fma(const register _simd_s64x2 x, const register _simd_s64x2 y, const register _simd_s64x2 z) {
//		union SIMDUnion { _simd_s64x2 v1; _simd_s64x8 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s64x8_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x2_fma_enable() _simd_s64x8_fma_enable()
//#elif defined(_simd_s64x16_fma_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_fma(const register _simd_s64x2 x, const register _simd_s64x2 y, const register _simd_s64x2 z) {
//		union SIMDUnion { _simd_s64x2 v1; _simd_s64x16 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s64x16_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x2_fma_enable() _simd_s64x16_fma_enable()
//#elif defined(_simd_s64x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_fma(const register _simd_s64x2 x, const register _simd_s64x2 y, const register _simd_s64x2 z) {
//		union SIMDUnion { _simd_s64x2 v1; _simd_s64x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s64x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x2_fma_enable() _simd_s64x32_fma_enable()
//#elif defined(_simd_s64x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_fma(const register _simd_s64x2 x, const register _simd_s64x2 y, const register _simd_s64x2 z) {
//		union SIMDUnion { _simd_s64x2 v1; _simd_s64x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s64x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x2_fma_enable() _simd_s64x64_fma_enable()
//#else
//	#define _simd_s64x2_fma(X,Y,Z) _simd_s64x2_combine(\
//		_simd_s64x1_fma(_simd_s64x2_splitlo(X), _simd_s64x2_splitlo(Y), _simd_s64x2_splitlo(Z)),\
//		_simd_s64x1_fma(_simd_s64x2_splithi(X), _simd_s64x2_splithi(Y), _simd_s64x2_splithi(Z)))
//	#define _simd_s64x2_fma_enable() (_simd_s64x1_fma_enable() && _simd_s64x2_combine_enable() && _simd_s64x2_splitlo_enable()  && _simd_s64x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x2_fma_) && ! defined(_simd_s64x2_fma_scalar_)
//	#define _simd_s64x2_fma_scalar_(X,Y,Z) _simd_s64x2_fma_(X,_simd_s64x2_fill_scalar_(Y),_simd_s64x2_fill_scalar_(Z))
//	#define _simd_s64x2_fma_scalar_instruction_set _simd_s64x2_fma_instruction_set
//#endif
//#ifdef _simd_s64x2_fma_scalar_
//	#define _simd_s64x2_fma_scalar(X,Y,Z) _simd_s64x2_fma_scalar_(X,Y,Z)
//	#define _simd_s64x2_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_fma_scalar_instruction_set>()
//#else
//	#define _simd_s64x2_fma_scalar(X,Y,Z) _simd_s64x2_fma_safe(X,_simd_s64x2_fill_scalar_safe(Y),_simd_s64x2_fill_scalar_safe(Z))
//	#define _simd_s64x2_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_s64x1_fma_safe
//	#define _simd_s64x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_s64x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_s64x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_fma_enabled() true
//#endif
//
//#define _simd_s64x4_fma_safe(X,Y,Z)_simd_s64x4_combine_safe(\
//	_simd_s64x2_fma_safe(_simd_s64x4_splitlo_safe(X), _simd_ s64x4_splitlo_safe(Y), _simd_ s64x4_splitlo_safe(Z)),\
//	_simd_s64x2_fma_safe(_simd_s64x4_splithi_safe(X), _simd_ s64x4_splithi_safe(Y), _simd_ s64x4_splithi_safe(Z)))
//#ifdef _simd_s64x4_fma_
//	#define _simd_s64x4_fma(X,Y,Z) _simd_s64x4_fma_(X,Y,Z)
//	#define _simd_s64x4_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_fma_instruction_set>()
//#elif defined(_simd_s64x8_fma_)
//	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_fma(const register _simd_s64x4 x, const register _simd_s64x4 y, const register _simd_s64x4 z) {
//		union SIMDUnion { _simd_s64x4 v1; _simd_s64x8 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s64x8_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x4_fma_enable() _simd_s64x8_fma_enable()
//#elif defined(_simd_s64x16_fma_)
//	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_fma(const register _simd_s64x4 x, const register _simd_s64x4 y, const register _simd_s64x4 z) {
//		union SIMDUnion { _simd_s64x4 v1; _simd_s64x16 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s64x16_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x4_fma_enable() _simd_s64x16_fma_enable()
//#elif defined(_simd_s64x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_fma(const register _simd_s64x4 x, const register _simd_s64x4 y, const register _simd_s64x4 z) {
//		union SIMDUnion { _simd_s64x4 v1; _simd_s64x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s64x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x4_fma_enable() _simd_s64x32_fma_enable()
//#elif defined(_simd_s64x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_fma(const register _simd_s64x4 x, const register _simd_s64x4 y, const register _simd_s64x4 z) {
//		union SIMDUnion { _simd_s64x4 v1; _simd_s64x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s64x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x4_fma_enable() _simd_s64x64_fma_enable()
//#else
//	#define _simd_s64x4_fma(X,Y,Z) _simd_s64x4_combine(\
//		_simd_s64x2_fma(_simd_s64x4_splitlo(X), _simd_s64x4_splitlo(Y), _simd_s64x4_splitlo(Z)),\
//		_simd_s64x2_fma(_simd_s64x4_splithi(X), _simd_s64x4_splithi(Y), _simd_s64x4_splithi(Z)))
//	#define _simd_s64x4_fma_enable() (_simd_s64x2_fma_enable() && _simd_s64x4_combine_enable() && _simd_s64x4_splitlo_enable()  && _simd_s64x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x4_fma_) && ! defined(_simd_s64x4_fma_scalar_)
//	#define _simd_s64x4_fma_scalar_(X,Y,Z) _simd_s64x4_fma_(X,_simd_s64x4_fill_scalar_(Y),_simd_s64x4_fill_scalar_(Z))
//	#define _simd_s64x4_fma_scalar_instruction_set _simd_s64x4_fma_instruction_set
//#endif
//#ifdef _simd_s64x4_fma_scalar_
//	#define _simd_s64x4_fma_scalar(X,Y,Z) _simd_s64x4_fma_scalar_(X,Y,Z)
//	#define _simd_s64x4_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_fma_scalar_instruction_set>()
//#else
//	#define _simd_s64x4_fma_scalar(X,Y,Z) _simd_s64x4_fma_safe(X,_simd_s64x4_fill_scalar_safe(Y),_simd_s64x4_fill_scalar_safe(Z))
//	#define _simd_s64x4_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_s64x1_fma_safe
//	#define _simd_s64x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_s64x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_s64x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_fma_enabled() true
//#endif
//
//#define _simd_s64x8_fma_safe(X,Y,Z)_simd_s64x8_combine_safe(\
//	_simd_s64x4_fma_safe(_simd_s64x8_splitlo_safe(X), _simd_ s64x8_splitlo_safe(Y), _simd_ s64x8_splitlo_safe(Z)),\
//	_simd_s64x4_fma_safe(_simd_s64x8_splithi_safe(X), _simd_ s64x8_splithi_safe(Y), _simd_ s64x8_splithi_safe(Z)))
//#ifdef _simd_s64x8_fma_
//	#define _simd_s64x8_fma(X,Y,Z) _simd_s64x8_fma_(X,Y,Z)
//	#define _simd_s64x8_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_fma_instruction_set>()
//#elif defined(_simd_s64x16_fma_)
//	static ANVIL_STRONG_INLINE _simd_s64x8 ANVIL_SIMD_CALL _simd_s64x8_fma(const register _simd_s64x8 x, const register _simd_s64x8 y, const register _simd_s64x8 z) {
//		union SIMDUnion { _simd_s64x8 v1; _simd_s64x16 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s64x16_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x8_fma_enable() _simd_s64x16_fma_enable()
//#elif defined(_simd_s64x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_s64x8 ANVIL_SIMD_CALL _simd_s64x8_fma(const register _simd_s64x8 x, const register _simd_s64x8 y, const register _simd_s64x8 z) {
//		union SIMDUnion { _simd_s64x8 v1; _simd_s64x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s64x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x8_fma_enable() _simd_s64x32_fma_enable()
//#elif defined(_simd_s64x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_s64x8 ANVIL_SIMD_CALL _simd_s64x8_fma(const register _simd_s64x8 x, const register _simd_s64x8 y, const register _simd_s64x8 z) {
//		union SIMDUnion { _simd_s64x8 v1; _simd_s64x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s64x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x8_fma_enable() _simd_s64x64_fma_enable()
//#else
//	#define _simd_s64x8_fma(X,Y,Z) _simd_s64x8_combine(\
//		_simd_s64x4_fma(_simd_s64x8_splitlo(X), _simd_s64x8_splitlo(Y), _simd_s64x8_splitlo(Z)),\
//		_simd_s64x4_fma(_simd_s64x8_splithi(X), _simd_s64x8_splithi(Y), _simd_s64x8_splithi(Z)))
//	#define _simd_s64x8_fma_enable() (_simd_s64x4_fma_enable() && _simd_s64x8_combine_enable() && _simd_s64x8_splitlo_enable()  && _simd_s64x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x8_fma_) && ! defined(_simd_s64x8_fma_scalar_)
//	#define _simd_s64x8_fma_scalar_(X,Y,Z) _simd_s64x8_fma_(X,_simd_s64x8_fill_scalar_(Y),_simd_s64x8_fill_scalar_(Z))
//	#define _simd_s64x8_fma_scalar_instruction_set _simd_s64x8_fma_instruction_set
//#endif
//#ifdef _simd_s64x8_fma_scalar_
//	#define _simd_s64x8_fma_scalar(X,Y,Z) _simd_s64x8_fma_scalar_(X,Y,Z)
//	#define _simd_s64x8_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_fma_scalar_instruction_set>()
//#else
//	#define _simd_s64x8_fma_scalar(X,Y,Z) _simd_s64x8_fma_safe(X,_simd_s64x8_fill_scalar_safe(Y),_simd_s64x8_fill_scalar_safe(Z))
//	#define _simd_s64x8_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_s64x1_fma_safe
//	#define _simd_s64x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_s64x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_s64x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_fma_enabled() true
//#endif
//
//#define _simd_s64x16_fma_safe(X,Y,Z)_simd_s64x16_combine_safe(\
//	_simd_s64x8_fma_safe(_simd_s64x16_splitlo_safe(X), _simd_ s64x16_splitlo_safe(Y), _simd_ s64x16_splitlo_safe(Z)),\
//	_simd_s64x8_fma_safe(_simd_s64x16_splithi_safe(X), _simd_ s64x16_splithi_safe(Y), _simd_ s64x16_splithi_safe(Z)))
//#ifdef _simd_s64x16_fma_
//	#define _simd_s64x16_fma(X,Y,Z) _simd_s64x16_fma_(X,Y,Z)
//	#define _simd_s64x16_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_fma_instruction_set>()
//#elif defined(_simd_s64x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_s64x16 ANVIL_SIMD_CALL _simd_s64x16_fma(const register _simd_s64x16 x, const register _simd_s64x16 y, const register _simd_s64x16 z) {
//		union SIMDUnion { _simd_s64x16 v1; _simd_s64x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s64x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x16_fma_enable() _simd_s64x32_fma_enable()
//#elif defined(_simd_s64x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_s64x16 ANVIL_SIMD_CALL _simd_s64x16_fma(const register _simd_s64x16 x, const register _simd_s64x16 y, const register _simd_s64x16 z) {
//		union SIMDUnion { _simd_s64x16 v1; _simd_s64x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s64x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x16_fma_enable() _simd_s64x64_fma_enable()
//#else
//	#define _simd_s64x16_fma(X,Y,Z) _simd_s64x16_combine(\
//		_simd_s64x8_fma(_simd_s64x16_splitlo(X), _simd_s64x16_splitlo(Y), _simd_s64x16_splitlo(Z)),\
//		_simd_s64x8_fma(_simd_s64x16_splithi(X), _simd_s64x16_splithi(Y), _simd_s64x16_splithi(Z)))
//	#define _simd_s64x16_fma_enable() (_simd_s64x8_fma_enable() && _simd_s64x16_combine_enable() && _simd_s64x16_splitlo_enable()  && _simd_s64x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x16_fma_) && ! defined(_simd_s64x16_fma_scalar_)
//	#define _simd_s64x16_fma_scalar_(X,Y,Z) _simd_s64x16_fma_(X,_simd_s64x16_fill_scalar_(Y),_simd_s64x16_fill_scalar_(Z))
//	#define _simd_s64x16_fma_scalar_instruction_set _simd_s64x16_fma_instruction_set
//#endif
//#ifdef _simd_s64x16_fma_scalar_
//	#define _simd_s64x16_fma_scalar(X,Y,Z) _simd_s64x16_fma_scalar_(X,Y,Z)
//	#define _simd_s64x16_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_fma_scalar_instruction_set>()
//#else
//	#define _simd_s64x16_fma_scalar(X,Y,Z) _simd_s64x16_fma_safe(X,_simd_s64x16_fill_scalar_safe(Y),_simd_s64x16_fill_scalar_safe(Z))
//	#define _simd_s64x16_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_s64x1_fma_safe
//	#define _simd_s64x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_s64x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_s64x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_fma_enabled() true
//#endif
//
//#define _simd_s64x32_fma_safe(X,Y,Z)_simd_s64x32_combine_safe(\
//	_simd_s64x16_fma_safe(_simd_s64x32_splitlo_safe(X), _simd_ s64x32_splitlo_safe(Y), _simd_ s64x32_splitlo_safe(Z)),\
//	_simd_s64x16_fma_safe(_simd_s64x32_splithi_safe(X), _simd_ s64x32_splithi_safe(Y), _simd_ s64x32_splithi_safe(Z)))
//#ifdef _simd_s64x32_fma_
//	#define _simd_s64x32_fma(X,Y,Z) _simd_s64x32_fma_(X,Y,Z)
//	#define _simd_s64x32_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_fma_instruction_set>()
//#elif defined(_simd_s64x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_s64x32 ANVIL_SIMD_CALL _simd_s64x32_fma(const register _simd_s64x32 x, const register _simd_s64x32 y, const register _simd_s64x32 z) {
//		union SIMDUnion { _simd_s64x32 v1; _simd_s64x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s64x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x32_fma_enable() _simd_s64x64_fma_enable()
//#else
//	#define _simd_s64x32_fma(X,Y,Z) _simd_s64x32_combine(\
//		_simd_s64x16_fma(_simd_s64x32_splitlo(X), _simd_s64x32_splitlo(Y), _simd_s64x32_splitlo(Z)),\
//		_simd_s64x16_fma(_simd_s64x32_splithi(X), _simd_s64x32_splithi(Y), _simd_s64x32_splithi(Z)))
//	#define _simd_s64x32_fma_enable() (_simd_s64x16_fma_enable() && _simd_s64x32_combine_enable() && _simd_s64x32_splitlo_enable()  && _simd_s64x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x32_fma_) && ! defined(_simd_s64x32_fma_scalar_)
//	#define _simd_s64x32_fma_scalar_(X,Y,Z) _simd_s64x32_fma_(X,_simd_s64x32_fill_scalar_(Y),_simd_s64x32_fill_scalar_(Z))
//	#define _simd_s64x32_fma_scalar_instruction_set _simd_s64x32_fma_instruction_set
//#endif
//#ifdef _simd_s64x32_fma_scalar_
//	#define _simd_s64x32_fma_scalar(X,Y,Z) _simd_s64x32_fma_scalar_(X,Y,Z)
//	#define _simd_s64x32_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_fma_scalar_instruction_set>()
//#else
//	#define _simd_s64x32_fma_scalar(X,Y,Z) _simd_s64x32_fma_safe(X,_simd_s64x32_fill_scalar_safe(Y),_simd_s64x32_fill_scalar_safe(Z))
//	#define _simd_s64x32_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_s64x1_fma_safe
//	#define _simd_s64x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_s64x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_s64x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_fma_enabled() true
//#endif
//
//#define _simd_s64x64_fma_safe(X,Y,Z)_simd_s64x64_combine_safe(\
//	_simd_s64x32_fma_safe(_simd_s64x64_splitlo_safe(X), _simd_ s64x64_splitlo_safe(Y), _simd_ s64x64_splitlo_safe(Z)),\
//	_simd_s64x32_fma_safe(_simd_s64x64_splithi_safe(X), _simd_ s64x64_splithi_safe(Y), _simd_ s64x64_splithi_safe(Z)))
//#ifdef _simd_s64x64_fma_
//	#define _simd_s64x64_fma(X,Y,Z) _simd_s64x64_fma_(X,Y,Z)
//	#define _simd_s64x64_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_fma_instruction_set>()
//#else
//	#define _simd_s64x64_fma(X,Y,Z) _simd_s64x64_combine(\
//		_simd_s64x32_fma(_simd_s64x64_splitlo(X), _simd_s64x64_splitlo(Y), _simd_s64x64_splitlo(Z)),\
//		_simd_s64x32_fma(_simd_s64x64_splithi(X), _simd_s64x64_splithi(Y), _simd_s64x64_splithi(Z)))
//	#define _simd_s64x64_fma_enable() (_simd_s64x32_fma_enable() && _simd_s64x64_combine_enable() && _simd_s64x64_splitlo_enable()  && _simd_s64x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x64_fma_) && ! defined(_simd_s64x64_fma_scalar_)
//	#define _simd_s64x64_fma_scalar_(X,Y,Z) _simd_s64x64_fma_(X,_simd_s64x64_fill_scalar_(Y),_simd_s64x64_fill_scalar_(Z))
//	#define _simd_s64x64_fma_scalar_instruction_set _simd_s64x64_fma_instruction_set
//#endif
//#ifdef _simd_s64x64_fma_scalar_
//	#define _simd_s64x64_fma_scalar(X,Y,Z) _simd_s64x64_fma_scalar_(X,Y,Z)
//	#define _simd_s64x64_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_fma_scalar_instruction_set>()
//#else
//	#define _simd_s64x64_fma_scalar(X,Y,Z) _simd_s64x64_fma_safe(X,_simd_s64x64_fill_scalar_safe(Y),_simd_s64x64_fill_scalar_safe(Z))
//	#define _simd_s64x64_fma_scalar_enabled() true
//#endif
//
//// -- u64 --
//
//#ifndef _simd_u64x1_fma_safe
//	#define _simd_u64x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_u64x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_u64x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_fma_enabled() true
//#endif
//
//#define _simd_u64x2_fma_safe(X,Y,Z)_simd_u64x2_combine_safe(\
//	_simd_u64x1_fma_safe(_simd_u64x2_splitlo_safe(X), _simd_ u64x2_splitlo_safe(Y), _simd_ u64x2_splitlo_safe(Z)),\
//	_simd_u64x1_fma_safe(_simd_u64x2_splithi_safe(X), _simd_ u64x2_splithi_safe(Y), _simd_ u64x2_splithi_safe(Z)))
//#ifdef _simd_u64x2_fma_
//	#define _simd_u64x2_fma(X,Y,Z) _simd_u64x2_fma_(X,Y,Z)
//	#define _simd_u64x2_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_fma_instruction_set>()
//#elif defined(_simd_u64x4_fma_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_fma(const register _simd_u64x2 x, const register _simd_u64x2 y, const register _simd_u64x2 z) {
//		union SIMDUnion { _simd_u64x2 v1; _simd_u64x4 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u64x4_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x2_fma_enable() _simd_u64x4_fma_enable()
//#elif defined(_simd_u64x8_fma_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_fma(const register _simd_u64x2 x, const register _simd_u64x2 y, const register _simd_u64x2 z) {
//		union SIMDUnion { _simd_u64x2 v1; _simd_u64x8 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u64x8_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x2_fma_enable() _simd_u64x8_fma_enable()
//#elif defined(_simd_u64x16_fma_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_fma(const register _simd_u64x2 x, const register _simd_u64x2 y, const register _simd_u64x2 z) {
//		union SIMDUnion { _simd_u64x2 v1; _simd_u64x16 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u64x16_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x2_fma_enable() _simd_u64x16_fma_enable()
//#elif defined(_simd_u64x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_fma(const register _simd_u64x2 x, const register _simd_u64x2 y, const register _simd_u64x2 z) {
//		union SIMDUnion { _simd_u64x2 v1; _simd_u64x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u64x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x2_fma_enable() _simd_u64x32_fma_enable()
//#elif defined(_simd_u64x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_fma(const register _simd_u64x2 x, const register _simd_u64x2 y, const register _simd_u64x2 z) {
//		union SIMDUnion { _simd_u64x2 v1; _simd_u64x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u64x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x2_fma_enable() _simd_u64x64_fma_enable()
//#else
//	#define _simd_u64x2_fma(X,Y,Z) _simd_u64x2_combine(\
//		_simd_u64x1_fma(_simd_u64x2_splitlo(X), _simd_u64x2_splitlo(Y), _simd_u64x2_splitlo(Z)),\
//		_simd_u64x1_fma(_simd_u64x2_splithi(X), _simd_u64x2_splithi(Y), _simd_u64x2_splithi(Z)))
//	#define _simd_u64x2_fma_enable() (_simd_u64x1_fma_enable() && _simd_u64x2_combine_enable() && _simd_u64x2_splitlo_enable()  && _simd_u64x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x2_fma_) && ! defined(_simd_u64x2_fma_scalar_)
//	#define _simd_u64x2_fma_scalar_(X,Y,Z) _simd_u64x2_fma_(X,_simd_u64x2_fill_scalar_(Y),_simd_u64x2_fill_scalar_(Z))
//	#define _simd_u64x2_fma_scalar_instruction_set _simd_u64x2_fma_instruction_set
//#endif
//#ifdef _simd_u64x2_fma_scalar_
//	#define _simd_u64x2_fma_scalar(X,Y,Z) _simd_u64x2_fma_scalar_(X,Y,Z)
//	#define _simd_u64x2_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_fma_scalar_instruction_set>()
//#else
//	#define _simd_u64x2_fma_scalar(X,Y,Z) _simd_u64x2_fma_safe(X,_simd_u64x2_fill_scalar_safe(Y),_simd_u64x2_fill_scalar_safe(Z))
//	#define _simd_u64x2_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_u64x1_fma_safe
//	#define _simd_u64x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_u64x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_u64x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_fma_enabled() true
//#endif
//
//#define _simd_u64x4_fma_safe(X,Y,Z)_simd_u64x4_combine_safe(\
//	_simd_u64x2_fma_safe(_simd_u64x4_splitlo_safe(X), _simd_ u64x4_splitlo_safe(Y), _simd_ u64x4_splitlo_safe(Z)),\
//	_simd_u64x2_fma_safe(_simd_u64x4_splithi_safe(X), _simd_ u64x4_splithi_safe(Y), _simd_ u64x4_splithi_safe(Z)))
//#ifdef _simd_u64x4_fma_
//	#define _simd_u64x4_fma(X,Y,Z) _simd_u64x4_fma_(X,Y,Z)
//	#define _simd_u64x4_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_fma_instruction_set>()
//#elif defined(_simd_u64x8_fma_)
//	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_fma(const register _simd_u64x4 x, const register _simd_u64x4 y, const register _simd_u64x4 z) {
//		union SIMDUnion { _simd_u64x4 v1; _simd_u64x8 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u64x8_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x4_fma_enable() _simd_u64x8_fma_enable()
//#elif defined(_simd_u64x16_fma_)
//	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_fma(const register _simd_u64x4 x, const register _simd_u64x4 y, const register _simd_u64x4 z) {
//		union SIMDUnion { _simd_u64x4 v1; _simd_u64x16 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u64x16_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x4_fma_enable() _simd_u64x16_fma_enable()
//#elif defined(_simd_u64x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_fma(const register _simd_u64x4 x, const register _simd_u64x4 y, const register _simd_u64x4 z) {
//		union SIMDUnion { _simd_u64x4 v1; _simd_u64x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u64x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x4_fma_enable() _simd_u64x32_fma_enable()
//#elif defined(_simd_u64x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_fma(const register _simd_u64x4 x, const register _simd_u64x4 y, const register _simd_u64x4 z) {
//		union SIMDUnion { _simd_u64x4 v1; _simd_u64x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u64x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x4_fma_enable() _simd_u64x64_fma_enable()
//#else
//	#define _simd_u64x4_fma(X,Y,Z) _simd_u64x4_combine(\
//		_simd_u64x2_fma(_simd_u64x4_splitlo(X), _simd_u64x4_splitlo(Y), _simd_u64x4_splitlo(Z)),\
//		_simd_u64x2_fma(_simd_u64x4_splithi(X), _simd_u64x4_splithi(Y), _simd_u64x4_splithi(Z)))
//	#define _simd_u64x4_fma_enable() (_simd_u64x2_fma_enable() && _simd_u64x4_combine_enable() && _simd_u64x4_splitlo_enable()  && _simd_u64x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x4_fma_) && ! defined(_simd_u64x4_fma_scalar_)
//	#define _simd_u64x4_fma_scalar_(X,Y,Z) _simd_u64x4_fma_(X,_simd_u64x4_fill_scalar_(Y),_simd_u64x4_fill_scalar_(Z))
//	#define _simd_u64x4_fma_scalar_instruction_set _simd_u64x4_fma_instruction_set
//#endif
//#ifdef _simd_u64x4_fma_scalar_
//	#define _simd_u64x4_fma_scalar(X,Y,Z) _simd_u64x4_fma_scalar_(X,Y,Z)
//	#define _simd_u64x4_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_fma_scalar_instruction_set>()
//#else
//	#define _simd_u64x4_fma_scalar(X,Y,Z) _simd_u64x4_fma_safe(X,_simd_u64x4_fill_scalar_safe(Y),_simd_u64x4_fill_scalar_safe(Z))
//	#define _simd_u64x4_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_u64x1_fma_safe
//	#define _simd_u64x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_u64x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_u64x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_fma_enabled() true
//#endif
//
//#define _simd_u64x8_fma_safe(X,Y,Z)_simd_u64x8_combine_safe(\
//	_simd_u64x4_fma_safe(_simd_u64x8_splitlo_safe(X), _simd_ u64x8_splitlo_safe(Y), _simd_ u64x8_splitlo_safe(Z)),\
//	_simd_u64x4_fma_safe(_simd_u64x8_splithi_safe(X), _simd_ u64x8_splithi_safe(Y), _simd_ u64x8_splithi_safe(Z)))
//#ifdef _simd_u64x8_fma_
//	#define _simd_u64x8_fma(X,Y,Z) _simd_u64x8_fma_(X,Y,Z)
//	#define _simd_u64x8_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_fma_instruction_set>()
//#elif defined(_simd_u64x16_fma_)
//	static ANVIL_STRONG_INLINE _simd_u64x8 ANVIL_SIMD_CALL _simd_u64x8_fma(const register _simd_u64x8 x, const register _simd_u64x8 y, const register _simd_u64x8 z) {
//		union SIMDUnion { _simd_u64x8 v1; _simd_u64x16 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u64x16_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x8_fma_enable() _simd_u64x16_fma_enable()
//#elif defined(_simd_u64x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_u64x8 ANVIL_SIMD_CALL _simd_u64x8_fma(const register _simd_u64x8 x, const register _simd_u64x8 y, const register _simd_u64x8 z) {
//		union SIMDUnion { _simd_u64x8 v1; _simd_u64x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u64x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x8_fma_enable() _simd_u64x32_fma_enable()
//#elif defined(_simd_u64x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_u64x8 ANVIL_SIMD_CALL _simd_u64x8_fma(const register _simd_u64x8 x, const register _simd_u64x8 y, const register _simd_u64x8 z) {
//		union SIMDUnion { _simd_u64x8 v1; _simd_u64x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u64x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x8_fma_enable() _simd_u64x64_fma_enable()
//#else
//	#define _simd_u64x8_fma(X,Y,Z) _simd_u64x8_combine(\
//		_simd_u64x4_fma(_simd_u64x8_splitlo(X), _simd_u64x8_splitlo(Y), _simd_u64x8_splitlo(Z)),\
//		_simd_u64x4_fma(_simd_u64x8_splithi(X), _simd_u64x8_splithi(Y), _simd_u64x8_splithi(Z)))
//	#define _simd_u64x8_fma_enable() (_simd_u64x4_fma_enable() && _simd_u64x8_combine_enable() && _simd_u64x8_splitlo_enable()  && _simd_u64x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x8_fma_) && ! defined(_simd_u64x8_fma_scalar_)
//	#define _simd_u64x8_fma_scalar_(X,Y,Z) _simd_u64x8_fma_(X,_simd_u64x8_fill_scalar_(Y),_simd_u64x8_fill_scalar_(Z))
//	#define _simd_u64x8_fma_scalar_instruction_set _simd_u64x8_fma_instruction_set
//#endif
//#ifdef _simd_u64x8_fma_scalar_
//	#define _simd_u64x8_fma_scalar(X,Y,Z) _simd_u64x8_fma_scalar_(X,Y,Z)
//	#define _simd_u64x8_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_fma_scalar_instruction_set>()
//#else
//	#define _simd_u64x8_fma_scalar(X,Y,Z) _simd_u64x8_fma_safe(X,_simd_u64x8_fill_scalar_safe(Y),_simd_u64x8_fill_scalar_safe(Z))
//	#define _simd_u64x8_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_u64x1_fma_safe
//	#define _simd_u64x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_u64x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_u64x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_fma_enabled() true
//#endif
//
//#define _simd_u64x16_fma_safe(X,Y,Z)_simd_u64x16_combine_safe(\
//	_simd_u64x8_fma_safe(_simd_u64x16_splitlo_safe(X), _simd_ u64x16_splitlo_safe(Y), _simd_ u64x16_splitlo_safe(Z)),\
//	_simd_u64x8_fma_safe(_simd_u64x16_splithi_safe(X), _simd_ u64x16_splithi_safe(Y), _simd_ u64x16_splithi_safe(Z)))
//#ifdef _simd_u64x16_fma_
//	#define _simd_u64x16_fma(X,Y,Z) _simd_u64x16_fma_(X,Y,Z)
//	#define _simd_u64x16_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_fma_instruction_set>()
//#elif defined(_simd_u64x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_u64x16 ANVIL_SIMD_CALL _simd_u64x16_fma(const register _simd_u64x16 x, const register _simd_u64x16 y, const register _simd_u64x16 z) {
//		union SIMDUnion { _simd_u64x16 v1; _simd_u64x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u64x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x16_fma_enable() _simd_u64x32_fma_enable()
//#elif defined(_simd_u64x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_u64x16 ANVIL_SIMD_CALL _simd_u64x16_fma(const register _simd_u64x16 x, const register _simd_u64x16 y, const register _simd_u64x16 z) {
//		union SIMDUnion { _simd_u64x16 v1; _simd_u64x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u64x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x16_fma_enable() _simd_u64x64_fma_enable()
//#else
//	#define _simd_u64x16_fma(X,Y,Z) _simd_u64x16_combine(\
//		_simd_u64x8_fma(_simd_u64x16_splitlo(X), _simd_u64x16_splitlo(Y), _simd_u64x16_splitlo(Z)),\
//		_simd_u64x8_fma(_simd_u64x16_splithi(X), _simd_u64x16_splithi(Y), _simd_u64x16_splithi(Z)))
//	#define _simd_u64x16_fma_enable() (_simd_u64x8_fma_enable() && _simd_u64x16_combine_enable() && _simd_u64x16_splitlo_enable()  && _simd_u64x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x16_fma_) && ! defined(_simd_u64x16_fma_scalar_)
//	#define _simd_u64x16_fma_scalar_(X,Y,Z) _simd_u64x16_fma_(X,_simd_u64x16_fill_scalar_(Y),_simd_u64x16_fill_scalar_(Z))
//	#define _simd_u64x16_fma_scalar_instruction_set _simd_u64x16_fma_instruction_set
//#endif
//#ifdef _simd_u64x16_fma_scalar_
//	#define _simd_u64x16_fma_scalar(X,Y,Z) _simd_u64x16_fma_scalar_(X,Y,Z)
//	#define _simd_u64x16_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_fma_scalar_instruction_set>()
//#else
//	#define _simd_u64x16_fma_scalar(X,Y,Z) _simd_u64x16_fma_safe(X,_simd_u64x16_fill_scalar_safe(Y),_simd_u64x16_fill_scalar_safe(Z))
//	#define _simd_u64x16_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_u64x1_fma_safe
//	#define _simd_u64x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_u64x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_u64x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_fma_enabled() true
//#endif
//
//#define _simd_u64x32_fma_safe(X,Y,Z)_simd_u64x32_combine_safe(\
//	_simd_u64x16_fma_safe(_simd_u64x32_splitlo_safe(X), _simd_ u64x32_splitlo_safe(Y), _simd_ u64x32_splitlo_safe(Z)),\
//	_simd_u64x16_fma_safe(_simd_u64x32_splithi_safe(X), _simd_ u64x32_splithi_safe(Y), _simd_ u64x32_splithi_safe(Z)))
//#ifdef _simd_u64x32_fma_
//	#define _simd_u64x32_fma(X,Y,Z) _simd_u64x32_fma_(X,Y,Z)
//	#define _simd_u64x32_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_fma_instruction_set>()
//#elif defined(_simd_u64x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_u64x32 ANVIL_SIMD_CALL _simd_u64x32_fma(const register _simd_u64x32 x, const register _simd_u64x32 y, const register _simd_u64x32 z) {
//		union SIMDUnion { _simd_u64x32 v1; _simd_u64x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u64x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x32_fma_enable() _simd_u64x64_fma_enable()
//#else
//	#define _simd_u64x32_fma(X,Y,Z) _simd_u64x32_combine(\
//		_simd_u64x16_fma(_simd_u64x32_splitlo(X), _simd_u64x32_splitlo(Y), _simd_u64x32_splitlo(Z)),\
//		_simd_u64x16_fma(_simd_u64x32_splithi(X), _simd_u64x32_splithi(Y), _simd_u64x32_splithi(Z)))
//	#define _simd_u64x32_fma_enable() (_simd_u64x16_fma_enable() && _simd_u64x32_combine_enable() && _simd_u64x32_splitlo_enable()  && _simd_u64x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x32_fma_) && ! defined(_simd_u64x32_fma_scalar_)
//	#define _simd_u64x32_fma_scalar_(X,Y,Z) _simd_u64x32_fma_(X,_simd_u64x32_fill_scalar_(Y),_simd_u64x32_fill_scalar_(Z))
//	#define _simd_u64x32_fma_scalar_instruction_set _simd_u64x32_fma_instruction_set
//#endif
//#ifdef _simd_u64x32_fma_scalar_
//	#define _simd_u64x32_fma_scalar(X,Y,Z) _simd_u64x32_fma_scalar_(X,Y,Z)
//	#define _simd_u64x32_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_fma_scalar_instruction_set>()
//#else
//	#define _simd_u64x32_fma_scalar(X,Y,Z) _simd_u64x32_fma_safe(X,_simd_u64x32_fill_scalar_safe(Y),_simd_u64x32_fill_scalar_safe(Z))
//	#define _simd_u64x32_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_u64x1_fma_safe
//	#define _simd_u64x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_u64x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_u64x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_fma_enabled() true
//#endif
//
//#define _simd_u64x64_fma_safe(X,Y,Z)_simd_u64x64_combine_safe(\
//	_simd_u64x32_fma_safe(_simd_u64x64_splitlo_safe(X), _simd_ u64x64_splitlo_safe(Y), _simd_ u64x64_splitlo_safe(Z)),\
//	_simd_u64x32_fma_safe(_simd_u64x64_splithi_safe(X), _simd_ u64x64_splithi_safe(Y), _simd_ u64x64_splithi_safe(Z)))
//#ifdef _simd_u64x64_fma_
//	#define _simd_u64x64_fma(X,Y,Z) _simd_u64x64_fma_(X,Y,Z)
//	#define _simd_u64x64_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_fma_instruction_set>()
//#else
//	#define _simd_u64x64_fma(X,Y,Z) _simd_u64x64_combine(\
//		_simd_u64x32_fma(_simd_u64x64_splitlo(X), _simd_u64x64_splitlo(Y), _simd_u64x64_splitlo(Z)),\
//		_simd_u64x32_fma(_simd_u64x64_splithi(X), _simd_u64x64_splithi(Y), _simd_u64x64_splithi(Z)))
//	#define _simd_u64x64_fma_enable() (_simd_u64x32_fma_enable() && _simd_u64x64_combine_enable() && _simd_u64x64_splitlo_enable()  && _simd_u64x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x64_fma_) && ! defined(_simd_u64x64_fma_scalar_)
//	#define _simd_u64x64_fma_scalar_(X,Y,Z) _simd_u64x64_fma_(X,_simd_u64x64_fill_scalar_(Y),_simd_u64x64_fill_scalar_(Z))
//	#define _simd_u64x64_fma_scalar_instruction_set _simd_u64x64_fma_instruction_set
//#endif
//#ifdef _simd_u64x64_fma_scalar_
//	#define _simd_u64x64_fma_scalar(X,Y,Z) _simd_u64x64_fma_scalar_(X,Y,Z)
//	#define _simd_u64x64_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_fma_scalar_instruction_set>()
//#else
//	#define _simd_u64x64_fma_scalar(X,Y,Z) _simd_u64x64_fma_safe(X,_simd_u64x64_fill_scalar_safe(Y),_simd_u64x64_fill_scalar_safe(Z))
//	#define _simd_u64x64_fma_scalar_enabled() true
//#endif
//
//// -- s32 --
//
//#ifndef _simd_s32x1_fma_safe
//	#define _simd_s32x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_s32x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_s32x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_fma_enabled() true
//#endif
//
//#define _simd_s32x2_fma_safe(X,Y,Z)_simd_s32x2_combine_safe(\
//	_simd_s32x1_fma_safe(_simd_s32x2_splitlo_safe(X), _simd_ s32x2_splitlo_safe(Y), _simd_ s32x2_splitlo_safe(Z)),\
//	_simd_s32x1_fma_safe(_simd_s32x2_splithi_safe(X), _simd_ s32x2_splithi_safe(Y), _simd_ s32x2_splithi_safe(Z)))
//#ifdef _simd_s32x2_fma_
//	#define _simd_s32x2_fma(X,Y,Z) _simd_s32x2_fma_(X,Y,Z)
//	#define _simd_s32x2_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_fma_instruction_set>()
//#elif defined(_simd_s32x4_fma_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_fma(const register _simd_s32x2 x, const register _simd_s32x2 y, const register _simd_s32x2 z) {
//		union SIMDUnion { _simd_s32x2 v1; _simd_s32x4 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s32x4_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x2_fma_enable() _simd_s32x4_fma_enable()
//#elif defined(_simd_s32x8_fma_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_fma(const register _simd_s32x2 x, const register _simd_s32x2 y, const register _simd_s32x2 z) {
//		union SIMDUnion { _simd_s32x2 v1; _simd_s32x8 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s32x8_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x2_fma_enable() _simd_s32x8_fma_enable()
//#elif defined(_simd_s32x16_fma_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_fma(const register _simd_s32x2 x, const register _simd_s32x2 y, const register _simd_s32x2 z) {
//		union SIMDUnion { _simd_s32x2 v1; _simd_s32x16 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s32x16_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x2_fma_enable() _simd_s32x16_fma_enable()
//#elif defined(_simd_s32x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_fma(const register _simd_s32x2 x, const register _simd_s32x2 y, const register _simd_s32x2 z) {
//		union SIMDUnion { _simd_s32x2 v1; _simd_s32x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s32x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x2_fma_enable() _simd_s32x32_fma_enable()
//#elif defined(_simd_s32x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_fma(const register _simd_s32x2 x, const register _simd_s32x2 y, const register _simd_s32x2 z) {
//		union SIMDUnion { _simd_s32x2 v1; _simd_s32x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s32x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x2_fma_enable() _simd_s32x64_fma_enable()
//#else
//	#define _simd_s32x2_fma(X,Y,Z) _simd_s32x2_combine(\
//		_simd_s32x1_fma(_simd_s32x2_splitlo(X), _simd_s32x2_splitlo(Y), _simd_s32x2_splitlo(Z)),\
//		_simd_s32x1_fma(_simd_s32x2_splithi(X), _simd_s32x2_splithi(Y), _simd_s32x2_splithi(Z)))
//	#define _simd_s32x2_fma_enable() (_simd_s32x1_fma_enable() && _simd_s32x2_combine_enable() && _simd_s32x2_splitlo_enable()  && _simd_s32x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x2_fma_) && ! defined(_simd_s32x2_fma_scalar_)
//	#define _simd_s32x2_fma_scalar_(X,Y,Z) _simd_s32x2_fma_(X,_simd_s32x2_fill_scalar_(Y),_simd_s32x2_fill_scalar_(Z))
//	#define _simd_s32x2_fma_scalar_instruction_set _simd_s32x2_fma_instruction_set
//#endif
//#ifdef _simd_s32x2_fma_scalar_
//	#define _simd_s32x2_fma_scalar(X,Y,Z) _simd_s32x2_fma_scalar_(X,Y,Z)
//	#define _simd_s32x2_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_fma_scalar_instruction_set>()
//#else
//	#define _simd_s32x2_fma_scalar(X,Y,Z) _simd_s32x2_fma_safe(X,_simd_s32x2_fill_scalar_safe(Y),_simd_s32x2_fill_scalar_safe(Z))
//	#define _simd_s32x2_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_s32x1_fma_safe
//	#define _simd_s32x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_s32x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_s32x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_fma_enabled() true
//#endif
//
//#define _simd_s32x4_fma_safe(X,Y,Z)_simd_s32x4_combine_safe(\
//	_simd_s32x2_fma_safe(_simd_s32x4_splitlo_safe(X), _simd_ s32x4_splitlo_safe(Y), _simd_ s32x4_splitlo_safe(Z)),\
//	_simd_s32x2_fma_safe(_simd_s32x4_splithi_safe(X), _simd_ s32x4_splithi_safe(Y), _simd_ s32x4_splithi_safe(Z)))
//#ifdef _simd_s32x4_fma_
//	#define _simd_s32x4_fma(X,Y,Z) _simd_s32x4_fma_(X,Y,Z)
//	#define _simd_s32x4_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_fma_instruction_set>()
//#elif defined(_simd_s32x8_fma_)
//	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_fma(const register _simd_s32x4 x, const register _simd_s32x4 y, const register _simd_s32x4 z) {
//		union SIMDUnion { _simd_s32x4 v1; _simd_s32x8 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s32x8_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x4_fma_enable() _simd_s32x8_fma_enable()
//#elif defined(_simd_s32x16_fma_)
//	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_fma(const register _simd_s32x4 x, const register _simd_s32x4 y, const register _simd_s32x4 z) {
//		union SIMDUnion { _simd_s32x4 v1; _simd_s32x16 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s32x16_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x4_fma_enable() _simd_s32x16_fma_enable()
//#elif defined(_simd_s32x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_fma(const register _simd_s32x4 x, const register _simd_s32x4 y, const register _simd_s32x4 z) {
//		union SIMDUnion { _simd_s32x4 v1; _simd_s32x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s32x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x4_fma_enable() _simd_s32x32_fma_enable()
//#elif defined(_simd_s32x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_fma(const register _simd_s32x4 x, const register _simd_s32x4 y, const register _simd_s32x4 z) {
//		union SIMDUnion { _simd_s32x4 v1; _simd_s32x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s32x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x4_fma_enable() _simd_s32x64_fma_enable()
//#else
//	#define _simd_s32x4_fma(X,Y,Z) _simd_s32x4_combine(\
//		_simd_s32x2_fma(_simd_s32x4_splitlo(X), _simd_s32x4_splitlo(Y), _simd_s32x4_splitlo(Z)),\
//		_simd_s32x2_fma(_simd_s32x4_splithi(X), _simd_s32x4_splithi(Y), _simd_s32x4_splithi(Z)))
//	#define _simd_s32x4_fma_enable() (_simd_s32x2_fma_enable() && _simd_s32x4_combine_enable() && _simd_s32x4_splitlo_enable()  && _simd_s32x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x4_fma_) && ! defined(_simd_s32x4_fma_scalar_)
//	#define _simd_s32x4_fma_scalar_(X,Y,Z) _simd_s32x4_fma_(X,_simd_s32x4_fill_scalar_(Y),_simd_s32x4_fill_scalar_(Z))
//	#define _simd_s32x4_fma_scalar_instruction_set _simd_s32x4_fma_instruction_set
//#endif
//#ifdef _simd_s32x4_fma_scalar_
//	#define _simd_s32x4_fma_scalar(X,Y,Z) _simd_s32x4_fma_scalar_(X,Y,Z)
//	#define _simd_s32x4_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_fma_scalar_instruction_set>()
//#else
//	#define _simd_s32x4_fma_scalar(X,Y,Z) _simd_s32x4_fma_safe(X,_simd_s32x4_fill_scalar_safe(Y),_simd_s32x4_fill_scalar_safe(Z))
//	#define _simd_s32x4_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_s32x1_fma_safe
//	#define _simd_s32x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_s32x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_s32x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_fma_enabled() true
//#endif
//
//#define _simd_s32x8_fma_safe(X,Y,Z)_simd_s32x8_combine_safe(\
//	_simd_s32x4_fma_safe(_simd_s32x8_splitlo_safe(X), _simd_ s32x8_splitlo_safe(Y), _simd_ s32x8_splitlo_safe(Z)),\
//	_simd_s32x4_fma_safe(_simd_s32x8_splithi_safe(X), _simd_ s32x8_splithi_safe(Y), _simd_ s32x8_splithi_safe(Z)))
//#ifdef _simd_s32x8_fma_
//	#define _simd_s32x8_fma(X,Y,Z) _simd_s32x8_fma_(X,Y,Z)
//	#define _simd_s32x8_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_fma_instruction_set>()
//#elif defined(_simd_s32x16_fma_)
//	static ANVIL_STRONG_INLINE _simd_s32x8 ANVIL_SIMD_CALL _simd_s32x8_fma(const register _simd_s32x8 x, const register _simd_s32x8 y, const register _simd_s32x8 z) {
//		union SIMDUnion { _simd_s32x8 v1; _simd_s32x16 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s32x16_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x8_fma_enable() _simd_s32x16_fma_enable()
//#elif defined(_simd_s32x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_s32x8 ANVIL_SIMD_CALL _simd_s32x8_fma(const register _simd_s32x8 x, const register _simd_s32x8 y, const register _simd_s32x8 z) {
//		union SIMDUnion { _simd_s32x8 v1; _simd_s32x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s32x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x8_fma_enable() _simd_s32x32_fma_enable()
//#elif defined(_simd_s32x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_s32x8 ANVIL_SIMD_CALL _simd_s32x8_fma(const register _simd_s32x8 x, const register _simd_s32x8 y, const register _simd_s32x8 z) {
//		union SIMDUnion { _simd_s32x8 v1; _simd_s32x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s32x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x8_fma_enable() _simd_s32x64_fma_enable()
//#else
//	#define _simd_s32x8_fma(X,Y,Z) _simd_s32x8_combine(\
//		_simd_s32x4_fma(_simd_s32x8_splitlo(X), _simd_s32x8_splitlo(Y), _simd_s32x8_splitlo(Z)),\
//		_simd_s32x4_fma(_simd_s32x8_splithi(X), _simd_s32x8_splithi(Y), _simd_s32x8_splithi(Z)))
//	#define _simd_s32x8_fma_enable() (_simd_s32x4_fma_enable() && _simd_s32x8_combine_enable() && _simd_s32x8_splitlo_enable()  && _simd_s32x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x8_fma_) && ! defined(_simd_s32x8_fma_scalar_)
//	#define _simd_s32x8_fma_scalar_(X,Y,Z) _simd_s32x8_fma_(X,_simd_s32x8_fill_scalar_(Y),_simd_s32x8_fill_scalar_(Z))
//	#define _simd_s32x8_fma_scalar_instruction_set _simd_s32x8_fma_instruction_set
//#endif
//#ifdef _simd_s32x8_fma_scalar_
//	#define _simd_s32x8_fma_scalar(X,Y,Z) _simd_s32x8_fma_scalar_(X,Y,Z)
//	#define _simd_s32x8_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_fma_scalar_instruction_set>()
//#else
//	#define _simd_s32x8_fma_scalar(X,Y,Z) _simd_s32x8_fma_safe(X,_simd_s32x8_fill_scalar_safe(Y),_simd_s32x8_fill_scalar_safe(Z))
//	#define _simd_s32x8_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_s32x1_fma_safe
//	#define _simd_s32x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_s32x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_s32x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_fma_enabled() true
//#endif
//
//#define _simd_s32x16_fma_safe(X,Y,Z)_simd_s32x16_combine_safe(\
//	_simd_s32x8_fma_safe(_simd_s32x16_splitlo_safe(X), _simd_ s32x16_splitlo_safe(Y), _simd_ s32x16_splitlo_safe(Z)),\
//	_simd_s32x8_fma_safe(_simd_s32x16_splithi_safe(X), _simd_ s32x16_splithi_safe(Y), _simd_ s32x16_splithi_safe(Z)))
//#ifdef _simd_s32x16_fma_
//	#define _simd_s32x16_fma(X,Y,Z) _simd_s32x16_fma_(X,Y,Z)
//	#define _simd_s32x16_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_fma_instruction_set>()
//#elif defined(_simd_s32x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_s32x16 ANVIL_SIMD_CALL _simd_s32x16_fma(const register _simd_s32x16 x, const register _simd_s32x16 y, const register _simd_s32x16 z) {
//		union SIMDUnion { _simd_s32x16 v1; _simd_s32x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s32x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x16_fma_enable() _simd_s32x32_fma_enable()
//#elif defined(_simd_s32x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_s32x16 ANVIL_SIMD_CALL _simd_s32x16_fma(const register _simd_s32x16 x, const register _simd_s32x16 y, const register _simd_s32x16 z) {
//		union SIMDUnion { _simd_s32x16 v1; _simd_s32x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s32x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x16_fma_enable() _simd_s32x64_fma_enable()
//#else
//	#define _simd_s32x16_fma(X,Y,Z) _simd_s32x16_combine(\
//		_simd_s32x8_fma(_simd_s32x16_splitlo(X), _simd_s32x16_splitlo(Y), _simd_s32x16_splitlo(Z)),\
//		_simd_s32x8_fma(_simd_s32x16_splithi(X), _simd_s32x16_splithi(Y), _simd_s32x16_splithi(Z)))
//	#define _simd_s32x16_fma_enable() (_simd_s32x8_fma_enable() && _simd_s32x16_combine_enable() && _simd_s32x16_splitlo_enable()  && _simd_s32x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x16_fma_) && ! defined(_simd_s32x16_fma_scalar_)
//	#define _simd_s32x16_fma_scalar_(X,Y,Z) _simd_s32x16_fma_(X,_simd_s32x16_fill_scalar_(Y),_simd_s32x16_fill_scalar_(Z))
//	#define _simd_s32x16_fma_scalar_instruction_set _simd_s32x16_fma_instruction_set
//#endif
//#ifdef _simd_s32x16_fma_scalar_
//	#define _simd_s32x16_fma_scalar(X,Y,Z) _simd_s32x16_fma_scalar_(X,Y,Z)
//	#define _simd_s32x16_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_fma_scalar_instruction_set>()
//#else
//	#define _simd_s32x16_fma_scalar(X,Y,Z) _simd_s32x16_fma_safe(X,_simd_s32x16_fill_scalar_safe(Y),_simd_s32x16_fill_scalar_safe(Z))
//	#define _simd_s32x16_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_s32x1_fma_safe
//	#define _simd_s32x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_s32x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_s32x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_fma_enabled() true
//#endif
//
//#define _simd_s32x32_fma_safe(X,Y,Z)_simd_s32x32_combine_safe(\
//	_simd_s32x16_fma_safe(_simd_s32x32_splitlo_safe(X), _simd_ s32x32_splitlo_safe(Y), _simd_ s32x32_splitlo_safe(Z)),\
//	_simd_s32x16_fma_safe(_simd_s32x32_splithi_safe(X), _simd_ s32x32_splithi_safe(Y), _simd_ s32x32_splithi_safe(Z)))
//#ifdef _simd_s32x32_fma_
//	#define _simd_s32x32_fma(X,Y,Z) _simd_s32x32_fma_(X,Y,Z)
//	#define _simd_s32x32_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_fma_instruction_set>()
//#elif defined(_simd_s32x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_s32x32 ANVIL_SIMD_CALL _simd_s32x32_fma(const register _simd_s32x32 x, const register _simd_s32x32 y, const register _simd_s32x32 z) {
//		union SIMDUnion { _simd_s32x32 v1; _simd_s32x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s32x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x32_fma_enable() _simd_s32x64_fma_enable()
//#else
//	#define _simd_s32x32_fma(X,Y,Z) _simd_s32x32_combine(\
//		_simd_s32x16_fma(_simd_s32x32_splitlo(X), _simd_s32x32_splitlo(Y), _simd_s32x32_splitlo(Z)),\
//		_simd_s32x16_fma(_simd_s32x32_splithi(X), _simd_s32x32_splithi(Y), _simd_s32x32_splithi(Z)))
//	#define _simd_s32x32_fma_enable() (_simd_s32x16_fma_enable() && _simd_s32x32_combine_enable() && _simd_s32x32_splitlo_enable()  && _simd_s32x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x32_fma_) && ! defined(_simd_s32x32_fma_scalar_)
//	#define _simd_s32x32_fma_scalar_(X,Y,Z) _simd_s32x32_fma_(X,_simd_s32x32_fill_scalar_(Y),_simd_s32x32_fill_scalar_(Z))
//	#define _simd_s32x32_fma_scalar_instruction_set _simd_s32x32_fma_instruction_set
//#endif
//#ifdef _simd_s32x32_fma_scalar_
//	#define _simd_s32x32_fma_scalar(X,Y,Z) _simd_s32x32_fma_scalar_(X,Y,Z)
//	#define _simd_s32x32_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_fma_scalar_instruction_set>()
//#else
//	#define _simd_s32x32_fma_scalar(X,Y,Z) _simd_s32x32_fma_safe(X,_simd_s32x32_fill_scalar_safe(Y),_simd_s32x32_fill_scalar_safe(Z))
//	#define _simd_s32x32_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_s32x1_fma_safe
//	#define _simd_s32x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_s32x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_s32x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_fma_enabled() true
//#endif
//
//#define _simd_s32x64_fma_safe(X,Y,Z)_simd_s32x64_combine_safe(\
//	_simd_s32x32_fma_safe(_simd_s32x64_splitlo_safe(X), _simd_ s32x64_splitlo_safe(Y), _simd_ s32x64_splitlo_safe(Z)),\
//	_simd_s32x32_fma_safe(_simd_s32x64_splithi_safe(X), _simd_ s32x64_splithi_safe(Y), _simd_ s32x64_splithi_safe(Z)))
//#ifdef _simd_s32x64_fma_
//	#define _simd_s32x64_fma(X,Y,Z) _simd_s32x64_fma_(X,Y,Z)
//	#define _simd_s32x64_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_fma_instruction_set>()
//#else
//	#define _simd_s32x64_fma(X,Y,Z) _simd_s32x64_combine(\
//		_simd_s32x32_fma(_simd_s32x64_splitlo(X), _simd_s32x64_splitlo(Y), _simd_s32x64_splitlo(Z)),\
//		_simd_s32x32_fma(_simd_s32x64_splithi(X), _simd_s32x64_splithi(Y), _simd_s32x64_splithi(Z)))
//	#define _simd_s32x64_fma_enable() (_simd_s32x32_fma_enable() && _simd_s32x64_combine_enable() && _simd_s32x64_splitlo_enable()  && _simd_s32x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x64_fma_) && ! defined(_simd_s32x64_fma_scalar_)
//	#define _simd_s32x64_fma_scalar_(X,Y,Z) _simd_s32x64_fma_(X,_simd_s32x64_fill_scalar_(Y),_simd_s32x64_fill_scalar_(Z))
//	#define _simd_s32x64_fma_scalar_instruction_set _simd_s32x64_fma_instruction_set
//#endif
//#ifdef _simd_s32x64_fma_scalar_
//	#define _simd_s32x64_fma_scalar(X,Y,Z) _simd_s32x64_fma_scalar_(X,Y,Z)
//	#define _simd_s32x64_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_fma_scalar_instruction_set>()
//#else
//	#define _simd_s32x64_fma_scalar(X,Y,Z) _simd_s32x64_fma_safe(X,_simd_s32x64_fill_scalar_safe(Y),_simd_s32x64_fill_scalar_safe(Z))
//	#define _simd_s32x64_fma_scalar_enabled() true
//#endif
//
//// -- u32 --
//
//#ifndef _simd_u32x1_fma_safe
//	#define _simd_u32x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_u32x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_u32x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_fma_enabled() true
//#endif
//
//#define _simd_u32x2_fma_safe(X,Y,Z)_simd_u32x2_combine_safe(\
//	_simd_u32x1_fma_safe(_simd_u32x2_splitlo_safe(X), _simd_ u32x2_splitlo_safe(Y), _simd_ u32x2_splitlo_safe(Z)),\
//	_simd_u32x1_fma_safe(_simd_u32x2_splithi_safe(X), _simd_ u32x2_splithi_safe(Y), _simd_ u32x2_splithi_safe(Z)))
//#ifdef _simd_u32x2_fma_
//	#define _simd_u32x2_fma(X,Y,Z) _simd_u32x2_fma_(X,Y,Z)
//	#define _simd_u32x2_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_fma_instruction_set>()
//#elif defined(_simd_u32x4_fma_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_fma(const register _simd_u32x2 x, const register _simd_u32x2 y, const register _simd_u32x2 z) {
//		union SIMDUnion { _simd_u32x2 v1; _simd_u32x4 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u32x4_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x2_fma_enable() _simd_u32x4_fma_enable()
//#elif defined(_simd_u32x8_fma_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_fma(const register _simd_u32x2 x, const register _simd_u32x2 y, const register _simd_u32x2 z) {
//		union SIMDUnion { _simd_u32x2 v1; _simd_u32x8 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u32x8_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x2_fma_enable() _simd_u32x8_fma_enable()
//#elif defined(_simd_u32x16_fma_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_fma(const register _simd_u32x2 x, const register _simd_u32x2 y, const register _simd_u32x2 z) {
//		union SIMDUnion { _simd_u32x2 v1; _simd_u32x16 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u32x16_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x2_fma_enable() _simd_u32x16_fma_enable()
//#elif defined(_simd_u32x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_fma(const register _simd_u32x2 x, const register _simd_u32x2 y, const register _simd_u32x2 z) {
//		union SIMDUnion { _simd_u32x2 v1; _simd_u32x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u32x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x2_fma_enable() _simd_u32x32_fma_enable()
//#elif defined(_simd_u32x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_fma(const register _simd_u32x2 x, const register _simd_u32x2 y, const register _simd_u32x2 z) {
//		union SIMDUnion { _simd_u32x2 v1; _simd_u32x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u32x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x2_fma_enable() _simd_u32x64_fma_enable()
//#else
//	#define _simd_u32x2_fma(X,Y,Z) _simd_u32x2_combine(\
//		_simd_u32x1_fma(_simd_u32x2_splitlo(X), _simd_u32x2_splitlo(Y), _simd_u32x2_splitlo(Z)),\
//		_simd_u32x1_fma(_simd_u32x2_splithi(X), _simd_u32x2_splithi(Y), _simd_u32x2_splithi(Z)))
//	#define _simd_u32x2_fma_enable() (_simd_u32x1_fma_enable() && _simd_u32x2_combine_enable() && _simd_u32x2_splitlo_enable()  && _simd_u32x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x2_fma_) && ! defined(_simd_u32x2_fma_scalar_)
//	#define _simd_u32x2_fma_scalar_(X,Y,Z) _simd_u32x2_fma_(X,_simd_u32x2_fill_scalar_(Y),_simd_u32x2_fill_scalar_(Z))
//	#define _simd_u32x2_fma_scalar_instruction_set _simd_u32x2_fma_instruction_set
//#endif
//#ifdef _simd_u32x2_fma_scalar_
//	#define _simd_u32x2_fma_scalar(X,Y,Z) _simd_u32x2_fma_scalar_(X,Y,Z)
//	#define _simd_u32x2_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_fma_scalar_instruction_set>()
//#else
//	#define _simd_u32x2_fma_scalar(X,Y,Z) _simd_u32x2_fma_safe(X,_simd_u32x2_fill_scalar_safe(Y),_simd_u32x2_fill_scalar_safe(Z))
//	#define _simd_u32x2_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_u32x1_fma_safe
//	#define _simd_u32x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_u32x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_u32x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_fma_enabled() true
//#endif
//
//#define _simd_u32x4_fma_safe(X,Y,Z)_simd_u32x4_combine_safe(\
//	_simd_u32x2_fma_safe(_simd_u32x4_splitlo_safe(X), _simd_ u32x4_splitlo_safe(Y), _simd_ u32x4_splitlo_safe(Z)),\
//	_simd_u32x2_fma_safe(_simd_u32x4_splithi_safe(X), _simd_ u32x4_splithi_safe(Y), _simd_ u32x4_splithi_safe(Z)))
//#ifdef _simd_u32x4_fma_
//	#define _simd_u32x4_fma(X,Y,Z) _simd_u32x4_fma_(X,Y,Z)
//	#define _simd_u32x4_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_fma_instruction_set>()
//#elif defined(_simd_u32x8_fma_)
//	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_fma(const register _simd_u32x4 x, const register _simd_u32x4 y, const register _simd_u32x4 z) {
//		union SIMDUnion { _simd_u32x4 v1; _simd_u32x8 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u32x8_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x4_fma_enable() _simd_u32x8_fma_enable()
//#elif defined(_simd_u32x16_fma_)
//	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_fma(const register _simd_u32x4 x, const register _simd_u32x4 y, const register _simd_u32x4 z) {
//		union SIMDUnion { _simd_u32x4 v1; _simd_u32x16 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u32x16_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x4_fma_enable() _simd_u32x16_fma_enable()
//#elif defined(_simd_u32x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_fma(const register _simd_u32x4 x, const register _simd_u32x4 y, const register _simd_u32x4 z) {
//		union SIMDUnion { _simd_u32x4 v1; _simd_u32x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u32x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x4_fma_enable() _simd_u32x32_fma_enable()
//#elif defined(_simd_u32x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_fma(const register _simd_u32x4 x, const register _simd_u32x4 y, const register _simd_u32x4 z) {
//		union SIMDUnion { _simd_u32x4 v1; _simd_u32x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u32x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x4_fma_enable() _simd_u32x64_fma_enable()
//#else
//	#define _simd_u32x4_fma(X,Y,Z) _simd_u32x4_combine(\
//		_simd_u32x2_fma(_simd_u32x4_splitlo(X), _simd_u32x4_splitlo(Y), _simd_u32x4_splitlo(Z)),\
//		_simd_u32x2_fma(_simd_u32x4_splithi(X), _simd_u32x4_splithi(Y), _simd_u32x4_splithi(Z)))
//	#define _simd_u32x4_fma_enable() (_simd_u32x2_fma_enable() && _simd_u32x4_combine_enable() && _simd_u32x4_splitlo_enable()  && _simd_u32x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x4_fma_) && ! defined(_simd_u32x4_fma_scalar_)
//	#define _simd_u32x4_fma_scalar_(X,Y,Z) _simd_u32x4_fma_(X,_simd_u32x4_fill_scalar_(Y),_simd_u32x4_fill_scalar_(Z))
//	#define _simd_u32x4_fma_scalar_instruction_set _simd_u32x4_fma_instruction_set
//#endif
//#ifdef _simd_u32x4_fma_scalar_
//	#define _simd_u32x4_fma_scalar(X,Y,Z) _simd_u32x4_fma_scalar_(X,Y,Z)
//	#define _simd_u32x4_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_fma_scalar_instruction_set>()
//#else
//	#define _simd_u32x4_fma_scalar(X,Y,Z) _simd_u32x4_fma_safe(X,_simd_u32x4_fill_scalar_safe(Y),_simd_u32x4_fill_scalar_safe(Z))
//	#define _simd_u32x4_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_u32x1_fma_safe
//	#define _simd_u32x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_u32x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_u32x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_fma_enabled() true
//#endif
//
//#define _simd_u32x8_fma_safe(X,Y,Z)_simd_u32x8_combine_safe(\
//	_simd_u32x4_fma_safe(_simd_u32x8_splitlo_safe(X), _simd_ u32x8_splitlo_safe(Y), _simd_ u32x8_splitlo_safe(Z)),\
//	_simd_u32x4_fma_safe(_simd_u32x8_splithi_safe(X), _simd_ u32x8_splithi_safe(Y), _simd_ u32x8_splithi_safe(Z)))
//#ifdef _simd_u32x8_fma_
//	#define _simd_u32x8_fma(X,Y,Z) _simd_u32x8_fma_(X,Y,Z)
//	#define _simd_u32x8_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_fma_instruction_set>()
//#elif defined(_simd_u32x16_fma_)
//	static ANVIL_STRONG_INLINE _simd_u32x8 ANVIL_SIMD_CALL _simd_u32x8_fma(const register _simd_u32x8 x, const register _simd_u32x8 y, const register _simd_u32x8 z) {
//		union SIMDUnion { _simd_u32x8 v1; _simd_u32x16 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u32x16_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x8_fma_enable() _simd_u32x16_fma_enable()
//#elif defined(_simd_u32x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_u32x8 ANVIL_SIMD_CALL _simd_u32x8_fma(const register _simd_u32x8 x, const register _simd_u32x8 y, const register _simd_u32x8 z) {
//		union SIMDUnion { _simd_u32x8 v1; _simd_u32x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u32x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x8_fma_enable() _simd_u32x32_fma_enable()
//#elif defined(_simd_u32x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_u32x8 ANVIL_SIMD_CALL _simd_u32x8_fma(const register _simd_u32x8 x, const register _simd_u32x8 y, const register _simd_u32x8 z) {
//		union SIMDUnion { _simd_u32x8 v1; _simd_u32x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u32x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x8_fma_enable() _simd_u32x64_fma_enable()
//#else
//	#define _simd_u32x8_fma(X,Y,Z) _simd_u32x8_combine(\
//		_simd_u32x4_fma(_simd_u32x8_splitlo(X), _simd_u32x8_splitlo(Y), _simd_u32x8_splitlo(Z)),\
//		_simd_u32x4_fma(_simd_u32x8_splithi(X), _simd_u32x8_splithi(Y), _simd_u32x8_splithi(Z)))
//	#define _simd_u32x8_fma_enable() (_simd_u32x4_fma_enable() && _simd_u32x8_combine_enable() && _simd_u32x8_splitlo_enable()  && _simd_u32x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x8_fma_) && ! defined(_simd_u32x8_fma_scalar_)
//	#define _simd_u32x8_fma_scalar_(X,Y,Z) _simd_u32x8_fma_(X,_simd_u32x8_fill_scalar_(Y),_simd_u32x8_fill_scalar_(Z))
//	#define _simd_u32x8_fma_scalar_instruction_set _simd_u32x8_fma_instruction_set
//#endif
//#ifdef _simd_u32x8_fma_scalar_
//	#define _simd_u32x8_fma_scalar(X,Y,Z) _simd_u32x8_fma_scalar_(X,Y,Z)
//	#define _simd_u32x8_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_fma_scalar_instruction_set>()
//#else
//	#define _simd_u32x8_fma_scalar(X,Y,Z) _simd_u32x8_fma_safe(X,_simd_u32x8_fill_scalar_safe(Y),_simd_u32x8_fill_scalar_safe(Z))
//	#define _simd_u32x8_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_u32x1_fma_safe
//	#define _simd_u32x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_u32x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_u32x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_fma_enabled() true
//#endif
//
//#define _simd_u32x16_fma_safe(X,Y,Z)_simd_u32x16_combine_safe(\
//	_simd_u32x8_fma_safe(_simd_u32x16_splitlo_safe(X), _simd_ u32x16_splitlo_safe(Y), _simd_ u32x16_splitlo_safe(Z)),\
//	_simd_u32x8_fma_safe(_simd_u32x16_splithi_safe(X), _simd_ u32x16_splithi_safe(Y), _simd_ u32x16_splithi_safe(Z)))
//#ifdef _simd_u32x16_fma_
//	#define _simd_u32x16_fma(X,Y,Z) _simd_u32x16_fma_(X,Y,Z)
//	#define _simd_u32x16_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_fma_instruction_set>()
//#elif defined(_simd_u32x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_u32x16 ANVIL_SIMD_CALL _simd_u32x16_fma(const register _simd_u32x16 x, const register _simd_u32x16 y, const register _simd_u32x16 z) {
//		union SIMDUnion { _simd_u32x16 v1; _simd_u32x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u32x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x16_fma_enable() _simd_u32x32_fma_enable()
//#elif defined(_simd_u32x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_u32x16 ANVIL_SIMD_CALL _simd_u32x16_fma(const register _simd_u32x16 x, const register _simd_u32x16 y, const register _simd_u32x16 z) {
//		union SIMDUnion { _simd_u32x16 v1; _simd_u32x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u32x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x16_fma_enable() _simd_u32x64_fma_enable()
//#else
//	#define _simd_u32x16_fma(X,Y,Z) _simd_u32x16_combine(\
//		_simd_u32x8_fma(_simd_u32x16_splitlo(X), _simd_u32x16_splitlo(Y), _simd_u32x16_splitlo(Z)),\
//		_simd_u32x8_fma(_simd_u32x16_splithi(X), _simd_u32x16_splithi(Y), _simd_u32x16_splithi(Z)))
//	#define _simd_u32x16_fma_enable() (_simd_u32x8_fma_enable() && _simd_u32x16_combine_enable() && _simd_u32x16_splitlo_enable()  && _simd_u32x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x16_fma_) && ! defined(_simd_u32x16_fma_scalar_)
//	#define _simd_u32x16_fma_scalar_(X,Y,Z) _simd_u32x16_fma_(X,_simd_u32x16_fill_scalar_(Y),_simd_u32x16_fill_scalar_(Z))
//	#define _simd_u32x16_fma_scalar_instruction_set _simd_u32x16_fma_instruction_set
//#endif
//#ifdef _simd_u32x16_fma_scalar_
//	#define _simd_u32x16_fma_scalar(X,Y,Z) _simd_u32x16_fma_scalar_(X,Y,Z)
//	#define _simd_u32x16_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_fma_scalar_instruction_set>()
//#else
//	#define _simd_u32x16_fma_scalar(X,Y,Z) _simd_u32x16_fma_safe(X,_simd_u32x16_fill_scalar_safe(Y),_simd_u32x16_fill_scalar_safe(Z))
//	#define _simd_u32x16_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_u32x1_fma_safe
//	#define _simd_u32x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_u32x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_u32x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_fma_enabled() true
//#endif
//
//#define _simd_u32x32_fma_safe(X,Y,Z)_simd_u32x32_combine_safe(\
//	_simd_u32x16_fma_safe(_simd_u32x32_splitlo_safe(X), _simd_ u32x32_splitlo_safe(Y), _simd_ u32x32_splitlo_safe(Z)),\
//	_simd_u32x16_fma_safe(_simd_u32x32_splithi_safe(X), _simd_ u32x32_splithi_safe(Y), _simd_ u32x32_splithi_safe(Z)))
//#ifdef _simd_u32x32_fma_
//	#define _simd_u32x32_fma(X,Y,Z) _simd_u32x32_fma_(X,Y,Z)
//	#define _simd_u32x32_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_fma_instruction_set>()
//#elif defined(_simd_u32x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_u32x32 ANVIL_SIMD_CALL _simd_u32x32_fma(const register _simd_u32x32 x, const register _simd_u32x32 y, const register _simd_u32x32 z) {
//		union SIMDUnion { _simd_u32x32 v1; _simd_u32x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u32x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x32_fma_enable() _simd_u32x64_fma_enable()
//#else
//	#define _simd_u32x32_fma(X,Y,Z) _simd_u32x32_combine(\
//		_simd_u32x16_fma(_simd_u32x32_splitlo(X), _simd_u32x32_splitlo(Y), _simd_u32x32_splitlo(Z)),\
//		_simd_u32x16_fma(_simd_u32x32_splithi(X), _simd_u32x32_splithi(Y), _simd_u32x32_splithi(Z)))
//	#define _simd_u32x32_fma_enable() (_simd_u32x16_fma_enable() && _simd_u32x32_combine_enable() && _simd_u32x32_splitlo_enable()  && _simd_u32x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x32_fma_) && ! defined(_simd_u32x32_fma_scalar_)
//	#define _simd_u32x32_fma_scalar_(X,Y,Z) _simd_u32x32_fma_(X,_simd_u32x32_fill_scalar_(Y),_simd_u32x32_fill_scalar_(Z))
//	#define _simd_u32x32_fma_scalar_instruction_set _simd_u32x32_fma_instruction_set
//#endif
//#ifdef _simd_u32x32_fma_scalar_
//	#define _simd_u32x32_fma_scalar(X,Y,Z) _simd_u32x32_fma_scalar_(X,Y,Z)
//	#define _simd_u32x32_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_fma_scalar_instruction_set>()
//#else
//	#define _simd_u32x32_fma_scalar(X,Y,Z) _simd_u32x32_fma_safe(X,_simd_u32x32_fill_scalar_safe(Y),_simd_u32x32_fill_scalar_safe(Z))
//	#define _simd_u32x32_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_u32x1_fma_safe
//	#define _simd_u32x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_u32x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_u32x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_fma_enabled() true
//#endif
//
//#define _simd_u32x64_fma_safe(X,Y,Z)_simd_u32x64_combine_safe(\
//	_simd_u32x32_fma_safe(_simd_u32x64_splitlo_safe(X), _simd_ u32x64_splitlo_safe(Y), _simd_ u32x64_splitlo_safe(Z)),\
//	_simd_u32x32_fma_safe(_simd_u32x64_splithi_safe(X), _simd_ u32x64_splithi_safe(Y), _simd_ u32x64_splithi_safe(Z)))
//#ifdef _simd_u32x64_fma_
//	#define _simd_u32x64_fma(X,Y,Z) _simd_u32x64_fma_(X,Y,Z)
//	#define _simd_u32x64_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_fma_instruction_set>()
//#else
//	#define _simd_u32x64_fma(X,Y,Z) _simd_u32x64_combine(\
//		_simd_u32x32_fma(_simd_u32x64_splitlo(X), _simd_u32x64_splitlo(Y), _simd_u32x64_splitlo(Z)),\
//		_simd_u32x32_fma(_simd_u32x64_splithi(X), _simd_u32x64_splithi(Y), _simd_u32x64_splithi(Z)))
//	#define _simd_u32x64_fma_enable() (_simd_u32x32_fma_enable() && _simd_u32x64_combine_enable() && _simd_u32x64_splitlo_enable()  && _simd_u32x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x64_fma_) && ! defined(_simd_u32x64_fma_scalar_)
//	#define _simd_u32x64_fma_scalar_(X,Y,Z) _simd_u32x64_fma_(X,_simd_u32x64_fill_scalar_(Y),_simd_u32x64_fill_scalar_(Z))
//	#define _simd_u32x64_fma_scalar_instruction_set _simd_u32x64_fma_instruction_set
//#endif
//#ifdef _simd_u32x64_fma_scalar_
//	#define _simd_u32x64_fma_scalar(X,Y,Z) _simd_u32x64_fma_scalar_(X,Y,Z)
//	#define _simd_u32x64_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_fma_scalar_instruction_set>()
//#else
//	#define _simd_u32x64_fma_scalar(X,Y,Z) _simd_u32x64_fma_safe(X,_simd_u32x64_fill_scalar_safe(Y),_simd_u32x64_fill_scalar_safe(Z))
//	#define _simd_u32x64_fma_scalar_enabled() true
//#endif
//
//// -- s16 --
//
//#ifndef _simd_s16x1_fma_safe
//	#define _simd_s16x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_s16x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_s16x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_fma_enabled() true
//#endif
//
//#define _simd_s16x2_fma_safe(X,Y,Z)_simd_s16x2_combine_safe(\
//	_simd_s16x1_fma_safe(_simd_s16x2_splitlo_safe(X), _simd_ s16x2_splitlo_safe(Y), _simd_ s16x2_splitlo_safe(Z)),\
//	_simd_s16x1_fma_safe(_simd_s16x2_splithi_safe(X), _simd_ s16x2_splithi_safe(Y), _simd_ s16x2_splithi_safe(Z)))
//#ifdef _simd_s16x2_fma_
//	#define _simd_s16x2_fma(X,Y,Z) _simd_s16x2_fma_(X,Y,Z)
//	#define _simd_s16x2_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_fma_instruction_set>()
//#elif defined(_simd_s16x4_fma_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_fma(const register _simd_s16x2 x, const register _simd_s16x2 y, const register _simd_s16x2 z) {
//		union SIMDUnion { _simd_s16x2 v1; _simd_s16x4 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s16x4_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x2_fma_enable() _simd_s16x4_fma_enable()
//#elif defined(_simd_s16x8_fma_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_fma(const register _simd_s16x2 x, const register _simd_s16x2 y, const register _simd_s16x2 z) {
//		union SIMDUnion { _simd_s16x2 v1; _simd_s16x8 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s16x8_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x2_fma_enable() _simd_s16x8_fma_enable()
//#elif defined(_simd_s16x16_fma_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_fma(const register _simd_s16x2 x, const register _simd_s16x2 y, const register _simd_s16x2 z) {
//		union SIMDUnion { _simd_s16x2 v1; _simd_s16x16 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s16x16_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x2_fma_enable() _simd_s16x16_fma_enable()
//#elif defined(_simd_s16x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_fma(const register _simd_s16x2 x, const register _simd_s16x2 y, const register _simd_s16x2 z) {
//		union SIMDUnion { _simd_s16x2 v1; _simd_s16x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s16x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x2_fma_enable() _simd_s16x32_fma_enable()
//#elif defined(_simd_s16x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_fma(const register _simd_s16x2 x, const register _simd_s16x2 y, const register _simd_s16x2 z) {
//		union SIMDUnion { _simd_s16x2 v1; _simd_s16x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s16x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x2_fma_enable() _simd_s16x64_fma_enable()
//#else
//	#define _simd_s16x2_fma(X,Y,Z) _simd_s16x2_combine(\
//		_simd_s16x1_fma(_simd_s16x2_splitlo(X), _simd_s16x2_splitlo(Y), _simd_s16x2_splitlo(Z)),\
//		_simd_s16x1_fma(_simd_s16x2_splithi(X), _simd_s16x2_splithi(Y), _simd_s16x2_splithi(Z)))
//	#define _simd_s16x2_fma_enable() (_simd_s16x1_fma_enable() && _simd_s16x2_combine_enable() && _simd_s16x2_splitlo_enable()  && _simd_s16x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x2_fma_) && ! defined(_simd_s16x2_fma_scalar_)
//	#define _simd_s16x2_fma_scalar_(X,Y,Z) _simd_s16x2_fma_(X,_simd_s16x2_fill_scalar_(Y),_simd_s16x2_fill_scalar_(Z))
//	#define _simd_s16x2_fma_scalar_instruction_set _simd_s16x2_fma_instruction_set
//#endif
//#ifdef _simd_s16x2_fma_scalar_
//	#define _simd_s16x2_fma_scalar(X,Y,Z) _simd_s16x2_fma_scalar_(X,Y,Z)
//	#define _simd_s16x2_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_fma_scalar_instruction_set>()
//#else
//	#define _simd_s16x2_fma_scalar(X,Y,Z) _simd_s16x2_fma_safe(X,_simd_s16x2_fill_scalar_safe(Y),_simd_s16x2_fill_scalar_safe(Z))
//	#define _simd_s16x2_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_s16x1_fma_safe
//	#define _simd_s16x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_s16x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_s16x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_fma_enabled() true
//#endif
//
//#define _simd_s16x4_fma_safe(X,Y,Z)_simd_s16x4_combine_safe(\
//	_simd_s16x2_fma_safe(_simd_s16x4_splitlo_safe(X), _simd_ s16x4_splitlo_safe(Y), _simd_ s16x4_splitlo_safe(Z)),\
//	_simd_s16x2_fma_safe(_simd_s16x4_splithi_safe(X), _simd_ s16x4_splithi_safe(Y), _simd_ s16x4_splithi_safe(Z)))
//#ifdef _simd_s16x4_fma_
//	#define _simd_s16x4_fma(X,Y,Z) _simd_s16x4_fma_(X,Y,Z)
//	#define _simd_s16x4_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_fma_instruction_set>()
//#elif defined(_simd_s16x8_fma_)
//	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_fma(const register _simd_s16x4 x, const register _simd_s16x4 y, const register _simd_s16x4 z) {
//		union SIMDUnion { _simd_s16x4 v1; _simd_s16x8 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s16x8_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x4_fma_enable() _simd_s16x8_fma_enable()
//#elif defined(_simd_s16x16_fma_)
//	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_fma(const register _simd_s16x4 x, const register _simd_s16x4 y, const register _simd_s16x4 z) {
//		union SIMDUnion { _simd_s16x4 v1; _simd_s16x16 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s16x16_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x4_fma_enable() _simd_s16x16_fma_enable()
//#elif defined(_simd_s16x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_fma(const register _simd_s16x4 x, const register _simd_s16x4 y, const register _simd_s16x4 z) {
//		union SIMDUnion { _simd_s16x4 v1; _simd_s16x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s16x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x4_fma_enable() _simd_s16x32_fma_enable()
//#elif defined(_simd_s16x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_fma(const register _simd_s16x4 x, const register _simd_s16x4 y, const register _simd_s16x4 z) {
//		union SIMDUnion { _simd_s16x4 v1; _simd_s16x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s16x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x4_fma_enable() _simd_s16x64_fma_enable()
//#else
//	#define _simd_s16x4_fma(X,Y,Z) _simd_s16x4_combine(\
//		_simd_s16x2_fma(_simd_s16x4_splitlo(X), _simd_s16x4_splitlo(Y), _simd_s16x4_splitlo(Z)),\
//		_simd_s16x2_fma(_simd_s16x4_splithi(X), _simd_s16x4_splithi(Y), _simd_s16x4_splithi(Z)))
//	#define _simd_s16x4_fma_enable() (_simd_s16x2_fma_enable() && _simd_s16x4_combine_enable() && _simd_s16x4_splitlo_enable()  && _simd_s16x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x4_fma_) && ! defined(_simd_s16x4_fma_scalar_)
//	#define _simd_s16x4_fma_scalar_(X,Y,Z) _simd_s16x4_fma_(X,_simd_s16x4_fill_scalar_(Y),_simd_s16x4_fill_scalar_(Z))
//	#define _simd_s16x4_fma_scalar_instruction_set _simd_s16x4_fma_instruction_set
//#endif
//#ifdef _simd_s16x4_fma_scalar_
//	#define _simd_s16x4_fma_scalar(X,Y,Z) _simd_s16x4_fma_scalar_(X,Y,Z)
//	#define _simd_s16x4_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_fma_scalar_instruction_set>()
//#else
//	#define _simd_s16x4_fma_scalar(X,Y,Z) _simd_s16x4_fma_safe(X,_simd_s16x4_fill_scalar_safe(Y),_simd_s16x4_fill_scalar_safe(Z))
//	#define _simd_s16x4_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_s16x1_fma_safe
//	#define _simd_s16x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_s16x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_s16x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_fma_enabled() true
//#endif
//
//#define _simd_s16x8_fma_safe(X,Y,Z)_simd_s16x8_combine_safe(\
//	_simd_s16x4_fma_safe(_simd_s16x8_splitlo_safe(X), _simd_ s16x8_splitlo_safe(Y), _simd_ s16x8_splitlo_safe(Z)),\
//	_simd_s16x4_fma_safe(_simd_s16x8_splithi_safe(X), _simd_ s16x8_splithi_safe(Y), _simd_ s16x8_splithi_safe(Z)))
//#ifdef _simd_s16x8_fma_
//	#define _simd_s16x8_fma(X,Y,Z) _simd_s16x8_fma_(X,Y,Z)
//	#define _simd_s16x8_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_fma_instruction_set>()
//#elif defined(_simd_s16x16_fma_)
//	static ANVIL_STRONG_INLINE _simd_s16x8 ANVIL_SIMD_CALL _simd_s16x8_fma(const register _simd_s16x8 x, const register _simd_s16x8 y, const register _simd_s16x8 z) {
//		union SIMDUnion { _simd_s16x8 v1; _simd_s16x16 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s16x16_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x8_fma_enable() _simd_s16x16_fma_enable()
//#elif defined(_simd_s16x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_s16x8 ANVIL_SIMD_CALL _simd_s16x8_fma(const register _simd_s16x8 x, const register _simd_s16x8 y, const register _simd_s16x8 z) {
//		union SIMDUnion { _simd_s16x8 v1; _simd_s16x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s16x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x8_fma_enable() _simd_s16x32_fma_enable()
//#elif defined(_simd_s16x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_s16x8 ANVIL_SIMD_CALL _simd_s16x8_fma(const register _simd_s16x8 x, const register _simd_s16x8 y, const register _simd_s16x8 z) {
//		union SIMDUnion { _simd_s16x8 v1; _simd_s16x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s16x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x8_fma_enable() _simd_s16x64_fma_enable()
//#else
//	#define _simd_s16x8_fma(X,Y,Z) _simd_s16x8_combine(\
//		_simd_s16x4_fma(_simd_s16x8_splitlo(X), _simd_s16x8_splitlo(Y), _simd_s16x8_splitlo(Z)),\
//		_simd_s16x4_fma(_simd_s16x8_splithi(X), _simd_s16x8_splithi(Y), _simd_s16x8_splithi(Z)))
//	#define _simd_s16x8_fma_enable() (_simd_s16x4_fma_enable() && _simd_s16x8_combine_enable() && _simd_s16x8_splitlo_enable()  && _simd_s16x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x8_fma_) && ! defined(_simd_s16x8_fma_scalar_)
//	#define _simd_s16x8_fma_scalar_(X,Y,Z) _simd_s16x8_fma_(X,_simd_s16x8_fill_scalar_(Y),_simd_s16x8_fill_scalar_(Z))
//	#define _simd_s16x8_fma_scalar_instruction_set _simd_s16x8_fma_instruction_set
//#endif
//#ifdef _simd_s16x8_fma_scalar_
//	#define _simd_s16x8_fma_scalar(X,Y,Z) _simd_s16x8_fma_scalar_(X,Y,Z)
//	#define _simd_s16x8_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_fma_scalar_instruction_set>()
//#else
//	#define _simd_s16x8_fma_scalar(X,Y,Z) _simd_s16x8_fma_safe(X,_simd_s16x8_fill_scalar_safe(Y),_simd_s16x8_fill_scalar_safe(Z))
//	#define _simd_s16x8_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_s16x1_fma_safe
//	#define _simd_s16x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_s16x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_s16x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_fma_enabled() true
//#endif
//
//#define _simd_s16x16_fma_safe(X,Y,Z)_simd_s16x16_combine_safe(\
//	_simd_s16x8_fma_safe(_simd_s16x16_splitlo_safe(X), _simd_ s16x16_splitlo_safe(Y), _simd_ s16x16_splitlo_safe(Z)),\
//	_simd_s16x8_fma_safe(_simd_s16x16_splithi_safe(X), _simd_ s16x16_splithi_safe(Y), _simd_ s16x16_splithi_safe(Z)))
//#ifdef _simd_s16x16_fma_
//	#define _simd_s16x16_fma(X,Y,Z) _simd_s16x16_fma_(X,Y,Z)
//	#define _simd_s16x16_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_fma_instruction_set>()
//#elif defined(_simd_s16x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_s16x16 ANVIL_SIMD_CALL _simd_s16x16_fma(const register _simd_s16x16 x, const register _simd_s16x16 y, const register _simd_s16x16 z) {
//		union SIMDUnion { _simd_s16x16 v1; _simd_s16x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s16x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x16_fma_enable() _simd_s16x32_fma_enable()
//#elif defined(_simd_s16x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_s16x16 ANVIL_SIMD_CALL _simd_s16x16_fma(const register _simd_s16x16 x, const register _simd_s16x16 y, const register _simd_s16x16 z) {
//		union SIMDUnion { _simd_s16x16 v1; _simd_s16x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s16x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x16_fma_enable() _simd_s16x64_fma_enable()
//#else
//	#define _simd_s16x16_fma(X,Y,Z) _simd_s16x16_combine(\
//		_simd_s16x8_fma(_simd_s16x16_splitlo(X), _simd_s16x16_splitlo(Y), _simd_s16x16_splitlo(Z)),\
//		_simd_s16x8_fma(_simd_s16x16_splithi(X), _simd_s16x16_splithi(Y), _simd_s16x16_splithi(Z)))
//	#define _simd_s16x16_fma_enable() (_simd_s16x8_fma_enable() && _simd_s16x16_combine_enable() && _simd_s16x16_splitlo_enable()  && _simd_s16x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x16_fma_) && ! defined(_simd_s16x16_fma_scalar_)
//	#define _simd_s16x16_fma_scalar_(X,Y,Z) _simd_s16x16_fma_(X,_simd_s16x16_fill_scalar_(Y),_simd_s16x16_fill_scalar_(Z))
//	#define _simd_s16x16_fma_scalar_instruction_set _simd_s16x16_fma_instruction_set
//#endif
//#ifdef _simd_s16x16_fma_scalar_
//	#define _simd_s16x16_fma_scalar(X,Y,Z) _simd_s16x16_fma_scalar_(X,Y,Z)
//	#define _simd_s16x16_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_fma_scalar_instruction_set>()
//#else
//	#define _simd_s16x16_fma_scalar(X,Y,Z) _simd_s16x16_fma_safe(X,_simd_s16x16_fill_scalar_safe(Y),_simd_s16x16_fill_scalar_safe(Z))
//	#define _simd_s16x16_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_s16x1_fma_safe
//	#define _simd_s16x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_s16x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_s16x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_fma_enabled() true
//#endif
//
//#define _simd_s16x32_fma_safe(X,Y,Z)_simd_s16x32_combine_safe(\
//	_simd_s16x16_fma_safe(_simd_s16x32_splitlo_safe(X), _simd_ s16x32_splitlo_safe(Y), _simd_ s16x32_splitlo_safe(Z)),\
//	_simd_s16x16_fma_safe(_simd_s16x32_splithi_safe(X), _simd_ s16x32_splithi_safe(Y), _simd_ s16x32_splithi_safe(Z)))
//#ifdef _simd_s16x32_fma_
//	#define _simd_s16x32_fma(X,Y,Z) _simd_s16x32_fma_(X,Y,Z)
//	#define _simd_s16x32_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_fma_instruction_set>()
//#elif defined(_simd_s16x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_s16x32 ANVIL_SIMD_CALL _simd_s16x32_fma(const register _simd_s16x32 x, const register _simd_s16x32 y, const register _simd_s16x32 z) {
//		union SIMDUnion { _simd_s16x32 v1; _simd_s16x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s16x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x32_fma_enable() _simd_s16x64_fma_enable()
//#else
//	#define _simd_s16x32_fma(X,Y,Z) _simd_s16x32_combine(\
//		_simd_s16x16_fma(_simd_s16x32_splitlo(X), _simd_s16x32_splitlo(Y), _simd_s16x32_splitlo(Z)),\
//		_simd_s16x16_fma(_simd_s16x32_splithi(X), _simd_s16x32_splithi(Y), _simd_s16x32_splithi(Z)))
//	#define _simd_s16x32_fma_enable() (_simd_s16x16_fma_enable() && _simd_s16x32_combine_enable() && _simd_s16x32_splitlo_enable()  && _simd_s16x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x32_fma_) && ! defined(_simd_s16x32_fma_scalar_)
//	#define _simd_s16x32_fma_scalar_(X,Y,Z) _simd_s16x32_fma_(X,_simd_s16x32_fill_scalar_(Y),_simd_s16x32_fill_scalar_(Z))
//	#define _simd_s16x32_fma_scalar_instruction_set _simd_s16x32_fma_instruction_set
//#endif
//#ifdef _simd_s16x32_fma_scalar_
//	#define _simd_s16x32_fma_scalar(X,Y,Z) _simd_s16x32_fma_scalar_(X,Y,Z)
//	#define _simd_s16x32_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_fma_scalar_instruction_set>()
//#else
//	#define _simd_s16x32_fma_scalar(X,Y,Z) _simd_s16x32_fma_safe(X,_simd_s16x32_fill_scalar_safe(Y),_simd_s16x32_fill_scalar_safe(Z))
//	#define _simd_s16x32_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_s16x1_fma_safe
//	#define _simd_s16x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_s16x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_s16x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_fma_enabled() true
//#endif
//
//#define _simd_s16x64_fma_safe(X,Y,Z)_simd_s16x64_combine_safe(\
//	_simd_s16x32_fma_safe(_simd_s16x64_splitlo_safe(X), _simd_ s16x64_splitlo_safe(Y), _simd_ s16x64_splitlo_safe(Z)),\
//	_simd_s16x32_fma_safe(_simd_s16x64_splithi_safe(X), _simd_ s16x64_splithi_safe(Y), _simd_ s16x64_splithi_safe(Z)))
//#ifdef _simd_s16x64_fma_
//	#define _simd_s16x64_fma(X,Y,Z) _simd_s16x64_fma_(X,Y,Z)
//	#define _simd_s16x64_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_fma_instruction_set>()
//#else
//	#define _simd_s16x64_fma(X,Y,Z) _simd_s16x64_combine(\
//		_simd_s16x32_fma(_simd_s16x64_splitlo(X), _simd_s16x64_splitlo(Y), _simd_s16x64_splitlo(Z)),\
//		_simd_s16x32_fma(_simd_s16x64_splithi(X), _simd_s16x64_splithi(Y), _simd_s16x64_splithi(Z)))
//	#define _simd_s16x64_fma_enable() (_simd_s16x32_fma_enable() && _simd_s16x64_combine_enable() && _simd_s16x64_splitlo_enable()  && _simd_s16x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x64_fma_) && ! defined(_simd_s16x64_fma_scalar_)
//	#define _simd_s16x64_fma_scalar_(X,Y,Z) _simd_s16x64_fma_(X,_simd_s16x64_fill_scalar_(Y),_simd_s16x64_fill_scalar_(Z))
//	#define _simd_s16x64_fma_scalar_instruction_set _simd_s16x64_fma_instruction_set
//#endif
//#ifdef _simd_s16x64_fma_scalar_
//	#define _simd_s16x64_fma_scalar(X,Y,Z) _simd_s16x64_fma_scalar_(X,Y,Z)
//	#define _simd_s16x64_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_fma_scalar_instruction_set>()
//#else
//	#define _simd_s16x64_fma_scalar(X,Y,Z) _simd_s16x64_fma_safe(X,_simd_s16x64_fill_scalar_safe(Y),_simd_s16x64_fill_scalar_safe(Z))
//	#define _simd_s16x64_fma_scalar_enabled() true
//#endif
//
//// -- u16 --
//
//#ifndef _simd_u16x1_fma_safe
//	#define _simd_u16x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_u16x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_u16x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_fma_enabled() true
//#endif
//
//#define _simd_u16x2_fma_safe(X,Y,Z)_simd_u16x2_combine_safe(\
//	_simd_u16x1_fma_safe(_simd_u16x2_splitlo_safe(X), _simd_ u16x2_splitlo_safe(Y), _simd_ u16x2_splitlo_safe(Z)),\
//	_simd_u16x1_fma_safe(_simd_u16x2_splithi_safe(X), _simd_ u16x2_splithi_safe(Y), _simd_ u16x2_splithi_safe(Z)))
//#ifdef _simd_u16x2_fma_
//	#define _simd_u16x2_fma(X,Y,Z) _simd_u16x2_fma_(X,Y,Z)
//	#define _simd_u16x2_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_fma_instruction_set>()
//#elif defined(_simd_u16x4_fma_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_fma(const register _simd_u16x2 x, const register _simd_u16x2 y, const register _simd_u16x2 z) {
//		union SIMDUnion { _simd_u16x2 v1; _simd_u16x4 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u16x4_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x2_fma_enable() _simd_u16x4_fma_enable()
//#elif defined(_simd_u16x8_fma_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_fma(const register _simd_u16x2 x, const register _simd_u16x2 y, const register _simd_u16x2 z) {
//		union SIMDUnion { _simd_u16x2 v1; _simd_u16x8 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u16x8_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x2_fma_enable() _simd_u16x8_fma_enable()
//#elif defined(_simd_u16x16_fma_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_fma(const register _simd_u16x2 x, const register _simd_u16x2 y, const register _simd_u16x2 z) {
//		union SIMDUnion { _simd_u16x2 v1; _simd_u16x16 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u16x16_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x2_fma_enable() _simd_u16x16_fma_enable()
//#elif defined(_simd_u16x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_fma(const register _simd_u16x2 x, const register _simd_u16x2 y, const register _simd_u16x2 z) {
//		union SIMDUnion { _simd_u16x2 v1; _simd_u16x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u16x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x2_fma_enable() _simd_u16x32_fma_enable()
//#elif defined(_simd_u16x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_fma(const register _simd_u16x2 x, const register _simd_u16x2 y, const register _simd_u16x2 z) {
//		union SIMDUnion { _simd_u16x2 v1; _simd_u16x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u16x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x2_fma_enable() _simd_u16x64_fma_enable()
//#else
//	#define _simd_u16x2_fma(X,Y,Z) _simd_u16x2_combine(\
//		_simd_u16x1_fma(_simd_u16x2_splitlo(X), _simd_u16x2_splitlo(Y), _simd_u16x2_splitlo(Z)),\
//		_simd_u16x1_fma(_simd_u16x2_splithi(X), _simd_u16x2_splithi(Y), _simd_u16x2_splithi(Z)))
//	#define _simd_u16x2_fma_enable() (_simd_u16x1_fma_enable() && _simd_u16x2_combine_enable() && _simd_u16x2_splitlo_enable()  && _simd_u16x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x2_fma_) && ! defined(_simd_u16x2_fma_scalar_)
//	#define _simd_u16x2_fma_scalar_(X,Y,Z) _simd_u16x2_fma_(X,_simd_u16x2_fill_scalar_(Y),_simd_u16x2_fill_scalar_(Z))
//	#define _simd_u16x2_fma_scalar_instruction_set _simd_u16x2_fma_instruction_set
//#endif
//#ifdef _simd_u16x2_fma_scalar_
//	#define _simd_u16x2_fma_scalar(X,Y,Z) _simd_u16x2_fma_scalar_(X,Y,Z)
//	#define _simd_u16x2_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_fma_scalar_instruction_set>()
//#else
//	#define _simd_u16x2_fma_scalar(X,Y,Z) _simd_u16x2_fma_safe(X,_simd_u16x2_fill_scalar_safe(Y),_simd_u16x2_fill_scalar_safe(Z))
//	#define _simd_u16x2_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_u16x1_fma_safe
//	#define _simd_u16x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_u16x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_u16x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_fma_enabled() true
//#endif
//
//#define _simd_u16x4_fma_safe(X,Y,Z)_simd_u16x4_combine_safe(\
//	_simd_u16x2_fma_safe(_simd_u16x4_splitlo_safe(X), _simd_ u16x4_splitlo_safe(Y), _simd_ u16x4_splitlo_safe(Z)),\
//	_simd_u16x2_fma_safe(_simd_u16x4_splithi_safe(X), _simd_ u16x4_splithi_safe(Y), _simd_ u16x4_splithi_safe(Z)))
//#ifdef _simd_u16x4_fma_
//	#define _simd_u16x4_fma(X,Y,Z) _simd_u16x4_fma_(X,Y,Z)
//	#define _simd_u16x4_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_fma_instruction_set>()
//#elif defined(_simd_u16x8_fma_)
//	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_fma(const register _simd_u16x4 x, const register _simd_u16x4 y, const register _simd_u16x4 z) {
//		union SIMDUnion { _simd_u16x4 v1; _simd_u16x8 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u16x8_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x4_fma_enable() _simd_u16x8_fma_enable()
//#elif defined(_simd_u16x16_fma_)
//	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_fma(const register _simd_u16x4 x, const register _simd_u16x4 y, const register _simd_u16x4 z) {
//		union SIMDUnion { _simd_u16x4 v1; _simd_u16x16 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u16x16_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x4_fma_enable() _simd_u16x16_fma_enable()
//#elif defined(_simd_u16x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_fma(const register _simd_u16x4 x, const register _simd_u16x4 y, const register _simd_u16x4 z) {
//		union SIMDUnion { _simd_u16x4 v1; _simd_u16x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u16x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x4_fma_enable() _simd_u16x32_fma_enable()
//#elif defined(_simd_u16x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_fma(const register _simd_u16x4 x, const register _simd_u16x4 y, const register _simd_u16x4 z) {
//		union SIMDUnion { _simd_u16x4 v1; _simd_u16x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u16x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x4_fma_enable() _simd_u16x64_fma_enable()
//#else
//	#define _simd_u16x4_fma(X,Y,Z) _simd_u16x4_combine(\
//		_simd_u16x2_fma(_simd_u16x4_splitlo(X), _simd_u16x4_splitlo(Y), _simd_u16x4_splitlo(Z)),\
//		_simd_u16x2_fma(_simd_u16x4_splithi(X), _simd_u16x4_splithi(Y), _simd_u16x4_splithi(Z)))
//	#define _simd_u16x4_fma_enable() (_simd_u16x2_fma_enable() && _simd_u16x4_combine_enable() && _simd_u16x4_splitlo_enable()  && _simd_u16x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x4_fma_) && ! defined(_simd_u16x4_fma_scalar_)
//	#define _simd_u16x4_fma_scalar_(X,Y,Z) _simd_u16x4_fma_(X,_simd_u16x4_fill_scalar_(Y),_simd_u16x4_fill_scalar_(Z))
//	#define _simd_u16x4_fma_scalar_instruction_set _simd_u16x4_fma_instruction_set
//#endif
//#ifdef _simd_u16x4_fma_scalar_
//	#define _simd_u16x4_fma_scalar(X,Y,Z) _simd_u16x4_fma_scalar_(X,Y,Z)
//	#define _simd_u16x4_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_fma_scalar_instruction_set>()
//#else
//	#define _simd_u16x4_fma_scalar(X,Y,Z) _simd_u16x4_fma_safe(X,_simd_u16x4_fill_scalar_safe(Y),_simd_u16x4_fill_scalar_safe(Z))
//	#define _simd_u16x4_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_u16x1_fma_safe
//	#define _simd_u16x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_u16x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_u16x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_fma_enabled() true
//#endif
//
//#define _simd_u16x8_fma_safe(X,Y,Z)_simd_u16x8_combine_safe(\
//	_simd_u16x4_fma_safe(_simd_u16x8_splitlo_safe(X), _simd_ u16x8_splitlo_safe(Y), _simd_ u16x8_splitlo_safe(Z)),\
//	_simd_u16x4_fma_safe(_simd_u16x8_splithi_safe(X), _simd_ u16x8_splithi_safe(Y), _simd_ u16x8_splithi_safe(Z)))
//#ifdef _simd_u16x8_fma_
//	#define _simd_u16x8_fma(X,Y,Z) _simd_u16x8_fma_(X,Y,Z)
//	#define _simd_u16x8_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_fma_instruction_set>()
//#elif defined(_simd_u16x16_fma_)
//	static ANVIL_STRONG_INLINE _simd_u16x8 ANVIL_SIMD_CALL _simd_u16x8_fma(const register _simd_u16x8 x, const register _simd_u16x8 y, const register _simd_u16x8 z) {
//		union SIMDUnion { _simd_u16x8 v1; _simd_u16x16 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u16x16_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x8_fma_enable() _simd_u16x16_fma_enable()
//#elif defined(_simd_u16x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_u16x8 ANVIL_SIMD_CALL _simd_u16x8_fma(const register _simd_u16x8 x, const register _simd_u16x8 y, const register _simd_u16x8 z) {
//		union SIMDUnion { _simd_u16x8 v1; _simd_u16x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u16x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x8_fma_enable() _simd_u16x32_fma_enable()
//#elif defined(_simd_u16x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_u16x8 ANVIL_SIMD_CALL _simd_u16x8_fma(const register _simd_u16x8 x, const register _simd_u16x8 y, const register _simd_u16x8 z) {
//		union SIMDUnion { _simd_u16x8 v1; _simd_u16x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u16x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x8_fma_enable() _simd_u16x64_fma_enable()
//#else
//	#define _simd_u16x8_fma(X,Y,Z) _simd_u16x8_combine(\
//		_simd_u16x4_fma(_simd_u16x8_splitlo(X), _simd_u16x8_splitlo(Y), _simd_u16x8_splitlo(Z)),\
//		_simd_u16x4_fma(_simd_u16x8_splithi(X), _simd_u16x8_splithi(Y), _simd_u16x8_splithi(Z)))
//	#define _simd_u16x8_fma_enable() (_simd_u16x4_fma_enable() && _simd_u16x8_combine_enable() && _simd_u16x8_splitlo_enable()  && _simd_u16x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x8_fma_) && ! defined(_simd_u16x8_fma_scalar_)
//	#define _simd_u16x8_fma_scalar_(X,Y,Z) _simd_u16x8_fma_(X,_simd_u16x8_fill_scalar_(Y),_simd_u16x8_fill_scalar_(Z))
//	#define _simd_u16x8_fma_scalar_instruction_set _simd_u16x8_fma_instruction_set
//#endif
//#ifdef _simd_u16x8_fma_scalar_
//	#define _simd_u16x8_fma_scalar(X,Y,Z) _simd_u16x8_fma_scalar_(X,Y,Z)
//	#define _simd_u16x8_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_fma_scalar_instruction_set>()
//#else
//	#define _simd_u16x8_fma_scalar(X,Y,Z) _simd_u16x8_fma_safe(X,_simd_u16x8_fill_scalar_safe(Y),_simd_u16x8_fill_scalar_safe(Z))
//	#define _simd_u16x8_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_u16x1_fma_safe
//	#define _simd_u16x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_u16x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_u16x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_fma_enabled() true
//#endif
//
//#define _simd_u16x16_fma_safe(X,Y,Z)_simd_u16x16_combine_safe(\
//	_simd_u16x8_fma_safe(_simd_u16x16_splitlo_safe(X), _simd_ u16x16_splitlo_safe(Y), _simd_ u16x16_splitlo_safe(Z)),\
//	_simd_u16x8_fma_safe(_simd_u16x16_splithi_safe(X), _simd_ u16x16_splithi_safe(Y), _simd_ u16x16_splithi_safe(Z)))
//#ifdef _simd_u16x16_fma_
//	#define _simd_u16x16_fma(X,Y,Z) _simd_u16x16_fma_(X,Y,Z)
//	#define _simd_u16x16_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_fma_instruction_set>()
//#elif defined(_simd_u16x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_u16x16 ANVIL_SIMD_CALL _simd_u16x16_fma(const register _simd_u16x16 x, const register _simd_u16x16 y, const register _simd_u16x16 z) {
//		union SIMDUnion { _simd_u16x16 v1; _simd_u16x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u16x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x16_fma_enable() _simd_u16x32_fma_enable()
//#elif defined(_simd_u16x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_u16x16 ANVIL_SIMD_CALL _simd_u16x16_fma(const register _simd_u16x16 x, const register _simd_u16x16 y, const register _simd_u16x16 z) {
//		union SIMDUnion { _simd_u16x16 v1; _simd_u16x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u16x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x16_fma_enable() _simd_u16x64_fma_enable()
//#else
//	#define _simd_u16x16_fma(X,Y,Z) _simd_u16x16_combine(\
//		_simd_u16x8_fma(_simd_u16x16_splitlo(X), _simd_u16x16_splitlo(Y), _simd_u16x16_splitlo(Z)),\
//		_simd_u16x8_fma(_simd_u16x16_splithi(X), _simd_u16x16_splithi(Y), _simd_u16x16_splithi(Z)))
//	#define _simd_u16x16_fma_enable() (_simd_u16x8_fma_enable() && _simd_u16x16_combine_enable() && _simd_u16x16_splitlo_enable()  && _simd_u16x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x16_fma_) && ! defined(_simd_u16x16_fma_scalar_)
//	#define _simd_u16x16_fma_scalar_(X,Y,Z) _simd_u16x16_fma_(X,_simd_u16x16_fill_scalar_(Y),_simd_u16x16_fill_scalar_(Z))
//	#define _simd_u16x16_fma_scalar_instruction_set _simd_u16x16_fma_instruction_set
//#endif
//#ifdef _simd_u16x16_fma_scalar_
//	#define _simd_u16x16_fma_scalar(X,Y,Z) _simd_u16x16_fma_scalar_(X,Y,Z)
//	#define _simd_u16x16_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_fma_scalar_instruction_set>()
//#else
//	#define _simd_u16x16_fma_scalar(X,Y,Z) _simd_u16x16_fma_safe(X,_simd_u16x16_fill_scalar_safe(Y),_simd_u16x16_fill_scalar_safe(Z))
//	#define _simd_u16x16_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_u16x1_fma_safe
//	#define _simd_u16x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_u16x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_u16x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_fma_enabled() true
//#endif
//
//#define _simd_u16x32_fma_safe(X,Y,Z)_simd_u16x32_combine_safe(\
//	_simd_u16x16_fma_safe(_simd_u16x32_splitlo_safe(X), _simd_ u16x32_splitlo_safe(Y), _simd_ u16x32_splitlo_safe(Z)),\
//	_simd_u16x16_fma_safe(_simd_u16x32_splithi_safe(X), _simd_ u16x32_splithi_safe(Y), _simd_ u16x32_splithi_safe(Z)))
//#ifdef _simd_u16x32_fma_
//	#define _simd_u16x32_fma(X,Y,Z) _simd_u16x32_fma_(X,Y,Z)
//	#define _simd_u16x32_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_fma_instruction_set>()
//#elif defined(_simd_u16x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_u16x32 ANVIL_SIMD_CALL _simd_u16x32_fma(const register _simd_u16x32 x, const register _simd_u16x32 y, const register _simd_u16x32 z) {
//		union SIMDUnion { _simd_u16x32 v1; _simd_u16x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u16x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x32_fma_enable() _simd_u16x64_fma_enable()
//#else
//	#define _simd_u16x32_fma(X,Y,Z) _simd_u16x32_combine(\
//		_simd_u16x16_fma(_simd_u16x32_splitlo(X), _simd_u16x32_splitlo(Y), _simd_u16x32_splitlo(Z)),\
//		_simd_u16x16_fma(_simd_u16x32_splithi(X), _simd_u16x32_splithi(Y), _simd_u16x32_splithi(Z)))
//	#define _simd_u16x32_fma_enable() (_simd_u16x16_fma_enable() && _simd_u16x32_combine_enable() && _simd_u16x32_splitlo_enable()  && _simd_u16x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x32_fma_) && ! defined(_simd_u16x32_fma_scalar_)
//	#define _simd_u16x32_fma_scalar_(X,Y,Z) _simd_u16x32_fma_(X,_simd_u16x32_fill_scalar_(Y),_simd_u16x32_fill_scalar_(Z))
//	#define _simd_u16x32_fma_scalar_instruction_set _simd_u16x32_fma_instruction_set
//#endif
//#ifdef _simd_u16x32_fma_scalar_
//	#define _simd_u16x32_fma_scalar(X,Y,Z) _simd_u16x32_fma_scalar_(X,Y,Z)
//	#define _simd_u16x32_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_fma_scalar_instruction_set>()
//#else
//	#define _simd_u16x32_fma_scalar(X,Y,Z) _simd_u16x32_fma_safe(X,_simd_u16x32_fill_scalar_safe(Y),_simd_u16x32_fill_scalar_safe(Z))
//	#define _simd_u16x32_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_u16x1_fma_safe
//	#define _simd_u16x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_u16x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_u16x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_fma_enabled() true
//#endif
//
//#define _simd_u16x64_fma_safe(X,Y,Z)_simd_u16x64_combine_safe(\
//	_simd_u16x32_fma_safe(_simd_u16x64_splitlo_safe(X), _simd_ u16x64_splitlo_safe(Y), _simd_ u16x64_splitlo_safe(Z)),\
//	_simd_u16x32_fma_safe(_simd_u16x64_splithi_safe(X), _simd_ u16x64_splithi_safe(Y), _simd_ u16x64_splithi_safe(Z)))
//#ifdef _simd_u16x64_fma_
//	#define _simd_u16x64_fma(X,Y,Z) _simd_u16x64_fma_(X,Y,Z)
//	#define _simd_u16x64_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_fma_instruction_set>()
//#else
//	#define _simd_u16x64_fma(X,Y,Z) _simd_u16x64_combine(\
//		_simd_u16x32_fma(_simd_u16x64_splitlo(X), _simd_u16x64_splitlo(Y), _simd_u16x64_splitlo(Z)),\
//		_simd_u16x32_fma(_simd_u16x64_splithi(X), _simd_u16x64_splithi(Y), _simd_u16x64_splithi(Z)))
//	#define _simd_u16x64_fma_enable() (_simd_u16x32_fma_enable() && _simd_u16x64_combine_enable() && _simd_u16x64_splitlo_enable()  && _simd_u16x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x64_fma_) && ! defined(_simd_u16x64_fma_scalar_)
//	#define _simd_u16x64_fma_scalar_(X,Y,Z) _simd_u16x64_fma_(X,_simd_u16x64_fill_scalar_(Y),_simd_u16x64_fill_scalar_(Z))
//	#define _simd_u16x64_fma_scalar_instruction_set _simd_u16x64_fma_instruction_set
//#endif
//#ifdef _simd_u16x64_fma_scalar_
//	#define _simd_u16x64_fma_scalar(X,Y,Z) _simd_u16x64_fma_scalar_(X,Y,Z)
//	#define _simd_u16x64_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_fma_scalar_instruction_set>()
//#else
//	#define _simd_u16x64_fma_scalar(X,Y,Z) _simd_u16x64_fma_safe(X,_simd_u16x64_fill_scalar_safe(Y),_simd_u16x64_fill_scalar_safe(Z))
//	#define _simd_u16x64_fma_scalar_enabled() true
//#endif
//
//// -- s8 --
//
//#ifndef _simd_s8x1_fma_safe
//	#define _simd_s8x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_s8x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_s8x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_fma_enabled() true
//#endif
//
//#define _simd_s8x2_fma_safe(X,Y,Z)_simd_s8x2_combine_safe(\
//	_simd_s8x1_fma_safe(_simd_s8x2_splitlo_safe(X), _simd_ s8x2_splitlo_safe(Y), _simd_ s8x2_splitlo_safe(Z)),\
//	_simd_s8x1_fma_safe(_simd_s8x2_splithi_safe(X), _simd_ s8x2_splithi_safe(Y), _simd_ s8x2_splithi_safe(Z)))
//#ifdef _simd_s8x2_fma_
//	#define _simd_s8x2_fma(X,Y,Z) _simd_s8x2_fma_(X,Y,Z)
//	#define _simd_s8x2_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_fma_instruction_set>()
//#elif defined(_simd_s8x4_fma_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_fma(const register _simd_s8x2 x, const register _simd_s8x2 y, const register _simd_s8x2 z) {
//		union SIMDUnion { _simd_s8x2 v1; _simd_s8x4 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s8x4_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x2_fma_enable() _simd_s8x4_fma_enable()
//#elif defined(_simd_s8x8_fma_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_fma(const register _simd_s8x2 x, const register _simd_s8x2 y, const register _simd_s8x2 z) {
//		union SIMDUnion { _simd_s8x2 v1; _simd_s8x8 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s8x8_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x2_fma_enable() _simd_s8x8_fma_enable()
//#elif defined(_simd_s8x16_fma_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_fma(const register _simd_s8x2 x, const register _simd_s8x2 y, const register _simd_s8x2 z) {
//		union SIMDUnion { _simd_s8x2 v1; _simd_s8x16 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s8x16_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x2_fma_enable() _simd_s8x16_fma_enable()
//#elif defined(_simd_s8x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_fma(const register _simd_s8x2 x, const register _simd_s8x2 y, const register _simd_s8x2 z) {
//		union SIMDUnion { _simd_s8x2 v1; _simd_s8x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s8x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x2_fma_enable() _simd_s8x32_fma_enable()
//#elif defined(_simd_s8x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_fma(const register _simd_s8x2 x, const register _simd_s8x2 y, const register _simd_s8x2 z) {
//		union SIMDUnion { _simd_s8x2 v1; _simd_s8x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s8x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x2_fma_enable() _simd_s8x64_fma_enable()
//#else
//	#define _simd_s8x2_fma(X,Y,Z) _simd_s8x2_combine(\
//		_simd_s8x1_fma(_simd_s8x2_splitlo(X), _simd_s8x2_splitlo(Y), _simd_s8x2_splitlo(Z)),\
//		_simd_s8x1_fma(_simd_s8x2_splithi(X), _simd_s8x2_splithi(Y), _simd_s8x2_splithi(Z)))
//	#define _simd_s8x2_fma_enable() (_simd_s8x1_fma_enable() && _simd_s8x2_combine_enable() && _simd_s8x2_splitlo_enable()  && _simd_s8x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x2_fma_) && ! defined(_simd_s8x2_fma_scalar_)
//	#define _simd_s8x2_fma_scalar_(X,Y,Z) _simd_s8x2_fma_(X,_simd_s8x2_fill_scalar_(Y),_simd_s8x2_fill_scalar_(Z))
//	#define _simd_s8x2_fma_scalar_instruction_set _simd_s8x2_fma_instruction_set
//#endif
//#ifdef _simd_s8x2_fma_scalar_
//	#define _simd_s8x2_fma_scalar(X,Y,Z) _simd_s8x2_fma_scalar_(X,Y,Z)
//	#define _simd_s8x2_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_fma_scalar_instruction_set>()
//#else
//	#define _simd_s8x2_fma_scalar(X,Y,Z) _simd_s8x2_fma_safe(X,_simd_s8x2_fill_scalar_safe(Y),_simd_s8x2_fill_scalar_safe(Z))
//	#define _simd_s8x2_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_s8x1_fma_safe
//	#define _simd_s8x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_s8x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_s8x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_fma_enabled() true
//#endif
//
//#define _simd_s8x4_fma_safe(X,Y,Z)_simd_s8x4_combine_safe(\
//	_simd_s8x2_fma_safe(_simd_s8x4_splitlo_safe(X), _simd_ s8x4_splitlo_safe(Y), _simd_ s8x4_splitlo_safe(Z)),\
//	_simd_s8x2_fma_safe(_simd_s8x4_splithi_safe(X), _simd_ s8x4_splithi_safe(Y), _simd_ s8x4_splithi_safe(Z)))
//#ifdef _simd_s8x4_fma_
//	#define _simd_s8x4_fma(X,Y,Z) _simd_s8x4_fma_(X,Y,Z)
//	#define _simd_s8x4_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_fma_instruction_set>()
//#elif defined(_simd_s8x8_fma_)
//	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_fma(const register _simd_s8x4 x, const register _simd_s8x4 y, const register _simd_s8x4 z) {
//		union SIMDUnion { _simd_s8x4 v1; _simd_s8x8 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s8x8_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x4_fma_enable() _simd_s8x8_fma_enable()
//#elif defined(_simd_s8x16_fma_)
//	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_fma(const register _simd_s8x4 x, const register _simd_s8x4 y, const register _simd_s8x4 z) {
//		union SIMDUnion { _simd_s8x4 v1; _simd_s8x16 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s8x16_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x4_fma_enable() _simd_s8x16_fma_enable()
//#elif defined(_simd_s8x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_fma(const register _simd_s8x4 x, const register _simd_s8x4 y, const register _simd_s8x4 z) {
//		union SIMDUnion { _simd_s8x4 v1; _simd_s8x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s8x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x4_fma_enable() _simd_s8x32_fma_enable()
//#elif defined(_simd_s8x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_fma(const register _simd_s8x4 x, const register _simd_s8x4 y, const register _simd_s8x4 z) {
//		union SIMDUnion { _simd_s8x4 v1; _simd_s8x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s8x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x4_fma_enable() _simd_s8x64_fma_enable()
//#else
//	#define _simd_s8x4_fma(X,Y,Z) _simd_s8x4_combine(\
//		_simd_s8x2_fma(_simd_s8x4_splitlo(X), _simd_s8x4_splitlo(Y), _simd_s8x4_splitlo(Z)),\
//		_simd_s8x2_fma(_simd_s8x4_splithi(X), _simd_s8x4_splithi(Y), _simd_s8x4_splithi(Z)))
//	#define _simd_s8x4_fma_enable() (_simd_s8x2_fma_enable() && _simd_s8x4_combine_enable() && _simd_s8x4_splitlo_enable()  && _simd_s8x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x4_fma_) && ! defined(_simd_s8x4_fma_scalar_)
//	#define _simd_s8x4_fma_scalar_(X,Y,Z) _simd_s8x4_fma_(X,_simd_s8x4_fill_scalar_(Y),_simd_s8x4_fill_scalar_(Z))
//	#define _simd_s8x4_fma_scalar_instruction_set _simd_s8x4_fma_instruction_set
//#endif
//#ifdef _simd_s8x4_fma_scalar_
//	#define _simd_s8x4_fma_scalar(X,Y,Z) _simd_s8x4_fma_scalar_(X,Y,Z)
//	#define _simd_s8x4_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_fma_scalar_instruction_set>()
//#else
//	#define _simd_s8x4_fma_scalar(X,Y,Z) _simd_s8x4_fma_safe(X,_simd_s8x4_fill_scalar_safe(Y),_simd_s8x4_fill_scalar_safe(Z))
//	#define _simd_s8x4_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_s8x1_fma_safe
//	#define _simd_s8x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_s8x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_s8x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_fma_enabled() true
//#endif
//
//#define _simd_s8x8_fma_safe(X,Y,Z)_simd_s8x8_combine_safe(\
//	_simd_s8x4_fma_safe(_simd_s8x8_splitlo_safe(X), _simd_ s8x8_splitlo_safe(Y), _simd_ s8x8_splitlo_safe(Z)),\
//	_simd_s8x4_fma_safe(_simd_s8x8_splithi_safe(X), _simd_ s8x8_splithi_safe(Y), _simd_ s8x8_splithi_safe(Z)))
//#ifdef _simd_s8x8_fma_
//	#define _simd_s8x8_fma(X,Y,Z) _simd_s8x8_fma_(X,Y,Z)
//	#define _simd_s8x8_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_fma_instruction_set>()
//#elif defined(_simd_s8x16_fma_)
//	static ANVIL_STRONG_INLINE _simd_s8x8 ANVIL_SIMD_CALL _simd_s8x8_fma(const register _simd_s8x8 x, const register _simd_s8x8 y, const register _simd_s8x8 z) {
//		union SIMDUnion { _simd_s8x8 v1; _simd_s8x16 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s8x16_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x8_fma_enable() _simd_s8x16_fma_enable()
//#elif defined(_simd_s8x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_s8x8 ANVIL_SIMD_CALL _simd_s8x8_fma(const register _simd_s8x8 x, const register _simd_s8x8 y, const register _simd_s8x8 z) {
//		union SIMDUnion { _simd_s8x8 v1; _simd_s8x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s8x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x8_fma_enable() _simd_s8x32_fma_enable()
//#elif defined(_simd_s8x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_s8x8 ANVIL_SIMD_CALL _simd_s8x8_fma(const register _simd_s8x8 x, const register _simd_s8x8 y, const register _simd_s8x8 z) {
//		union SIMDUnion { _simd_s8x8 v1; _simd_s8x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s8x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x8_fma_enable() _simd_s8x64_fma_enable()
//#else
//	#define _simd_s8x8_fma(X,Y,Z) _simd_s8x8_combine(\
//		_simd_s8x4_fma(_simd_s8x8_splitlo(X), _simd_s8x8_splitlo(Y), _simd_s8x8_splitlo(Z)),\
//		_simd_s8x4_fma(_simd_s8x8_splithi(X), _simd_s8x8_splithi(Y), _simd_s8x8_splithi(Z)))
//	#define _simd_s8x8_fma_enable() (_simd_s8x4_fma_enable() && _simd_s8x8_combine_enable() && _simd_s8x8_splitlo_enable()  && _simd_s8x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x8_fma_) && ! defined(_simd_s8x8_fma_scalar_)
//	#define _simd_s8x8_fma_scalar_(X,Y,Z) _simd_s8x8_fma_(X,_simd_s8x8_fill_scalar_(Y),_simd_s8x8_fill_scalar_(Z))
//	#define _simd_s8x8_fma_scalar_instruction_set _simd_s8x8_fma_instruction_set
//#endif
//#ifdef _simd_s8x8_fma_scalar_
//	#define _simd_s8x8_fma_scalar(X,Y,Z) _simd_s8x8_fma_scalar_(X,Y,Z)
//	#define _simd_s8x8_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_fma_scalar_instruction_set>()
//#else
//	#define _simd_s8x8_fma_scalar(X,Y,Z) _simd_s8x8_fma_safe(X,_simd_s8x8_fill_scalar_safe(Y),_simd_s8x8_fill_scalar_safe(Z))
//	#define _simd_s8x8_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_s8x1_fma_safe
//	#define _simd_s8x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_s8x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_s8x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_fma_enabled() true
//#endif
//
//#define _simd_s8x16_fma_safe(X,Y,Z)_simd_s8x16_combine_safe(\
//	_simd_s8x8_fma_safe(_simd_s8x16_splitlo_safe(X), _simd_ s8x16_splitlo_safe(Y), _simd_ s8x16_splitlo_safe(Z)),\
//	_simd_s8x8_fma_safe(_simd_s8x16_splithi_safe(X), _simd_ s8x16_splithi_safe(Y), _simd_ s8x16_splithi_safe(Z)))
//#ifdef _simd_s8x16_fma_
//	#define _simd_s8x16_fma(X,Y,Z) _simd_s8x16_fma_(X,Y,Z)
//	#define _simd_s8x16_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_fma_instruction_set>()
//#elif defined(_simd_s8x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_s8x16 ANVIL_SIMD_CALL _simd_s8x16_fma(const register _simd_s8x16 x, const register _simd_s8x16 y, const register _simd_s8x16 z) {
//		union SIMDUnion { _simd_s8x16 v1; _simd_s8x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s8x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x16_fma_enable() _simd_s8x32_fma_enable()
//#elif defined(_simd_s8x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_s8x16 ANVIL_SIMD_CALL _simd_s8x16_fma(const register _simd_s8x16 x, const register _simd_s8x16 y, const register _simd_s8x16 z) {
//		union SIMDUnion { _simd_s8x16 v1; _simd_s8x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s8x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x16_fma_enable() _simd_s8x64_fma_enable()
//#else
//	#define _simd_s8x16_fma(X,Y,Z) _simd_s8x16_combine(\
//		_simd_s8x8_fma(_simd_s8x16_splitlo(X), _simd_s8x16_splitlo(Y), _simd_s8x16_splitlo(Z)),\
//		_simd_s8x8_fma(_simd_s8x16_splithi(X), _simd_s8x16_splithi(Y), _simd_s8x16_splithi(Z)))
//	#define _simd_s8x16_fma_enable() (_simd_s8x8_fma_enable() && _simd_s8x16_combine_enable() && _simd_s8x16_splitlo_enable()  && _simd_s8x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x16_fma_) && ! defined(_simd_s8x16_fma_scalar_)
//	#define _simd_s8x16_fma_scalar_(X,Y,Z) _simd_s8x16_fma_(X,_simd_s8x16_fill_scalar_(Y),_simd_s8x16_fill_scalar_(Z))
//	#define _simd_s8x16_fma_scalar_instruction_set _simd_s8x16_fma_instruction_set
//#endif
//#ifdef _simd_s8x16_fma_scalar_
//	#define _simd_s8x16_fma_scalar(X,Y,Z) _simd_s8x16_fma_scalar_(X,Y,Z)
//	#define _simd_s8x16_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_fma_scalar_instruction_set>()
//#else
//	#define _simd_s8x16_fma_scalar(X,Y,Z) _simd_s8x16_fma_safe(X,_simd_s8x16_fill_scalar_safe(Y),_simd_s8x16_fill_scalar_safe(Z))
//	#define _simd_s8x16_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_s8x1_fma_safe
//	#define _simd_s8x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_s8x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_s8x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_fma_enabled() true
//#endif
//
//#define _simd_s8x32_fma_safe(X,Y,Z)_simd_s8x32_combine_safe(\
//	_simd_s8x16_fma_safe(_simd_s8x32_splitlo_safe(X), _simd_ s8x32_splitlo_safe(Y), _simd_ s8x32_splitlo_safe(Z)),\
//	_simd_s8x16_fma_safe(_simd_s8x32_splithi_safe(X), _simd_ s8x32_splithi_safe(Y), _simd_ s8x32_splithi_safe(Z)))
//#ifdef _simd_s8x32_fma_
//	#define _simd_s8x32_fma(X,Y,Z) _simd_s8x32_fma_(X,Y,Z)
//	#define _simd_s8x32_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_fma_instruction_set>()
//#elif defined(_simd_s8x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_s8x32 ANVIL_SIMD_CALL _simd_s8x32_fma(const register _simd_s8x32 x, const register _simd_s8x32 y, const register _simd_s8x32 z) {
//		union SIMDUnion { _simd_s8x32 v1; _simd_s8x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_s8x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x32_fma_enable() _simd_s8x64_fma_enable()
//#else
//	#define _simd_s8x32_fma(X,Y,Z) _simd_s8x32_combine(\
//		_simd_s8x16_fma(_simd_s8x32_splitlo(X), _simd_s8x32_splitlo(Y), _simd_s8x32_splitlo(Z)),\
//		_simd_s8x16_fma(_simd_s8x32_splithi(X), _simd_s8x32_splithi(Y), _simd_s8x32_splithi(Z)))
//	#define _simd_s8x32_fma_enable() (_simd_s8x16_fma_enable() && _simd_s8x32_combine_enable() && _simd_s8x32_splitlo_enable()  && _simd_s8x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x32_fma_) && ! defined(_simd_s8x32_fma_scalar_)
//	#define _simd_s8x32_fma_scalar_(X,Y,Z) _simd_s8x32_fma_(X,_simd_s8x32_fill_scalar_(Y),_simd_s8x32_fill_scalar_(Z))
//	#define _simd_s8x32_fma_scalar_instruction_set _simd_s8x32_fma_instruction_set
//#endif
//#ifdef _simd_s8x32_fma_scalar_
//	#define _simd_s8x32_fma_scalar(X,Y,Z) _simd_s8x32_fma_scalar_(X,Y,Z)
//	#define _simd_s8x32_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_fma_scalar_instruction_set>()
//#else
//	#define _simd_s8x32_fma_scalar(X,Y,Z) _simd_s8x32_fma_safe(X,_simd_s8x32_fill_scalar_safe(Y),_simd_s8x32_fill_scalar_safe(Z))
//	#define _simd_s8x32_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_s8x1_fma_safe
//	#define _simd_s8x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_s8x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_s8x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_fma_enabled() true
//#endif
//
//#define _simd_s8x64_fma_safe(X,Y,Z)_simd_s8x64_combine_safe(\
//	_simd_s8x32_fma_safe(_simd_s8x64_splitlo_safe(X), _simd_ s8x64_splitlo_safe(Y), _simd_ s8x64_splitlo_safe(Z)),\
//	_simd_s8x32_fma_safe(_simd_s8x64_splithi_safe(X), _simd_ s8x64_splithi_safe(Y), _simd_ s8x64_splithi_safe(Z)))
//#ifdef _simd_s8x64_fma_
//	#define _simd_s8x64_fma(X,Y,Z) _simd_s8x64_fma_(X,Y,Z)
//	#define _simd_s8x64_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_fma_instruction_set>()
//#else
//	#define _simd_s8x64_fma(X,Y,Z) _simd_s8x64_combine(\
//		_simd_s8x32_fma(_simd_s8x64_splitlo(X), _simd_s8x64_splitlo(Y), _simd_s8x64_splitlo(Z)),\
//		_simd_s8x32_fma(_simd_s8x64_splithi(X), _simd_s8x64_splithi(Y), _simd_s8x64_splithi(Z)))
//	#define _simd_s8x64_fma_enable() (_simd_s8x32_fma_enable() && _simd_s8x64_combine_enable() && _simd_s8x64_splitlo_enable()  && _simd_s8x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x64_fma_) && ! defined(_simd_s8x64_fma_scalar_)
//	#define _simd_s8x64_fma_scalar_(X,Y,Z) _simd_s8x64_fma_(X,_simd_s8x64_fill_scalar_(Y),_simd_s8x64_fill_scalar_(Z))
//	#define _simd_s8x64_fma_scalar_instruction_set _simd_s8x64_fma_instruction_set
//#endif
//#ifdef _simd_s8x64_fma_scalar_
//	#define _simd_s8x64_fma_scalar(X,Y,Z) _simd_s8x64_fma_scalar_(X,Y,Z)
//	#define _simd_s8x64_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_fma_scalar_instruction_set>()
//#else
//	#define _simd_s8x64_fma_scalar(X,Y,Z) _simd_s8x64_fma_safe(X,_simd_s8x64_fill_scalar_safe(Y),_simd_s8x64_fill_scalar_safe(Z))
//	#define _simd_s8x64_fma_scalar_enabled() true
//#endif
//
//// -- u8 --
//
//#ifndef _simd_u8x1_fma_safe
//	#define _simd_u8x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_u8x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_u8x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_fma_enabled() true
//#endif
//
//#define _simd_u8x2_fma_safe(X,Y,Z)_simd_u8x2_combine_safe(\
//	_simd_u8x1_fma_safe(_simd_u8x2_splitlo_safe(X), _simd_ u8x2_splitlo_safe(Y), _simd_ u8x2_splitlo_safe(Z)),\
//	_simd_u8x1_fma_safe(_simd_u8x2_splithi_safe(X), _simd_ u8x2_splithi_safe(Y), _simd_ u8x2_splithi_safe(Z)))
//#ifdef _simd_u8x2_fma_
//	#define _simd_u8x2_fma(X,Y,Z) _simd_u8x2_fma_(X,Y,Z)
//	#define _simd_u8x2_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_fma_instruction_set>()
//#elif defined(_simd_u8x4_fma_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_fma(const register _simd_u8x2 x, const register _simd_u8x2 y, const register _simd_u8x2 z) {
//		union SIMDUnion { _simd_u8x2 v1; _simd_u8x4 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u8x4_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x2_fma_enable() _simd_u8x4_fma_enable()
//#elif defined(_simd_u8x8_fma_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_fma(const register _simd_u8x2 x, const register _simd_u8x2 y, const register _simd_u8x2 z) {
//		union SIMDUnion { _simd_u8x2 v1; _simd_u8x8 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u8x8_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x2_fma_enable() _simd_u8x8_fma_enable()
//#elif defined(_simd_u8x16_fma_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_fma(const register _simd_u8x2 x, const register _simd_u8x2 y, const register _simd_u8x2 z) {
//		union SIMDUnion { _simd_u8x2 v1; _simd_u8x16 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u8x16_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x2_fma_enable() _simd_u8x16_fma_enable()
//#elif defined(_simd_u8x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_fma(const register _simd_u8x2 x, const register _simd_u8x2 y, const register _simd_u8x2 z) {
//		union SIMDUnion { _simd_u8x2 v1; _simd_u8x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u8x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x2_fma_enable() _simd_u8x32_fma_enable()
//#elif defined(_simd_u8x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_fma(const register _simd_u8x2 x, const register _simd_u8x2 y, const register _simd_u8x2 z) {
//		union SIMDUnion { _simd_u8x2 v1; _simd_u8x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u8x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x2_fma_enable() _simd_u8x64_fma_enable()
//#else
//	#define _simd_u8x2_fma(X,Y,Z) _simd_u8x2_combine(\
//		_simd_u8x1_fma(_simd_u8x2_splitlo(X), _simd_u8x2_splitlo(Y), _simd_u8x2_splitlo(Z)),\
//		_simd_u8x1_fma(_simd_u8x2_splithi(X), _simd_u8x2_splithi(Y), _simd_u8x2_splithi(Z)))
//	#define _simd_u8x2_fma_enable() (_simd_u8x1_fma_enable() && _simd_u8x2_combine_enable() && _simd_u8x2_splitlo_enable()  && _simd_u8x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x2_fma_) && ! defined(_simd_u8x2_fma_scalar_)
//	#define _simd_u8x2_fma_scalar_(X,Y,Z) _simd_u8x2_fma_(X,_simd_u8x2_fill_scalar_(Y),_simd_u8x2_fill_scalar_(Z))
//	#define _simd_u8x2_fma_scalar_instruction_set _simd_u8x2_fma_instruction_set
//#endif
//#ifdef _simd_u8x2_fma_scalar_
//	#define _simd_u8x2_fma_scalar(X,Y,Z) _simd_u8x2_fma_scalar_(X,Y,Z)
//	#define _simd_u8x2_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_fma_scalar_instruction_set>()
//#else
//	#define _simd_u8x2_fma_scalar(X,Y,Z) _simd_u8x2_fma_safe(X,_simd_u8x2_fill_scalar_safe(Y),_simd_u8x2_fill_scalar_safe(Z))
//	#define _simd_u8x2_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_u8x1_fma_safe
//	#define _simd_u8x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_u8x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_u8x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_fma_enabled() true
//#endif
//
//#define _simd_u8x4_fma_safe(X,Y,Z)_simd_u8x4_combine_safe(\
//	_simd_u8x2_fma_safe(_simd_u8x4_splitlo_safe(X), _simd_ u8x4_splitlo_safe(Y), _simd_ u8x4_splitlo_safe(Z)),\
//	_simd_u8x2_fma_safe(_simd_u8x4_splithi_safe(X), _simd_ u8x4_splithi_safe(Y), _simd_ u8x4_splithi_safe(Z)))
//#ifdef _simd_u8x4_fma_
//	#define _simd_u8x4_fma(X,Y,Z) _simd_u8x4_fma_(X,Y,Z)
//	#define _simd_u8x4_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_fma_instruction_set>()
//#elif defined(_simd_u8x8_fma_)
//	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_fma(const register _simd_u8x4 x, const register _simd_u8x4 y, const register _simd_u8x4 z) {
//		union SIMDUnion { _simd_u8x4 v1; _simd_u8x8 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u8x8_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x4_fma_enable() _simd_u8x8_fma_enable()
//#elif defined(_simd_u8x16_fma_)
//	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_fma(const register _simd_u8x4 x, const register _simd_u8x4 y, const register _simd_u8x4 z) {
//		union SIMDUnion { _simd_u8x4 v1; _simd_u8x16 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u8x16_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x4_fma_enable() _simd_u8x16_fma_enable()
//#elif defined(_simd_u8x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_fma(const register _simd_u8x4 x, const register _simd_u8x4 y, const register _simd_u8x4 z) {
//		union SIMDUnion { _simd_u8x4 v1; _simd_u8x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u8x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x4_fma_enable() _simd_u8x32_fma_enable()
//#elif defined(_simd_u8x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_fma(const register _simd_u8x4 x, const register _simd_u8x4 y, const register _simd_u8x4 z) {
//		union SIMDUnion { _simd_u8x4 v1; _simd_u8x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u8x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x4_fma_enable() _simd_u8x64_fma_enable()
//#else
//	#define _simd_u8x4_fma(X,Y,Z) _simd_u8x4_combine(\
//		_simd_u8x2_fma(_simd_u8x4_splitlo(X), _simd_u8x4_splitlo(Y), _simd_u8x4_splitlo(Z)),\
//		_simd_u8x2_fma(_simd_u8x4_splithi(X), _simd_u8x4_splithi(Y), _simd_u8x4_splithi(Z)))
//	#define _simd_u8x4_fma_enable() (_simd_u8x2_fma_enable() && _simd_u8x4_combine_enable() && _simd_u8x4_splitlo_enable()  && _simd_u8x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x4_fma_) && ! defined(_simd_u8x4_fma_scalar_)
//	#define _simd_u8x4_fma_scalar_(X,Y,Z) _simd_u8x4_fma_(X,_simd_u8x4_fill_scalar_(Y),_simd_u8x4_fill_scalar_(Z))
//	#define _simd_u8x4_fma_scalar_instruction_set _simd_u8x4_fma_instruction_set
//#endif
//#ifdef _simd_u8x4_fma_scalar_
//	#define _simd_u8x4_fma_scalar(X,Y,Z) _simd_u8x4_fma_scalar_(X,Y,Z)
//	#define _simd_u8x4_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_fma_scalar_instruction_set>()
//#else
//	#define _simd_u8x4_fma_scalar(X,Y,Z) _simd_u8x4_fma_safe(X,_simd_u8x4_fill_scalar_safe(Y),_simd_u8x4_fill_scalar_safe(Z))
//	#define _simd_u8x4_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_u8x1_fma_safe
//	#define _simd_u8x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_u8x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_u8x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_fma_enabled() true
//#endif
//
//#define _simd_u8x8_fma_safe(X,Y,Z)_simd_u8x8_combine_safe(\
//	_simd_u8x4_fma_safe(_simd_u8x8_splitlo_safe(X), _simd_ u8x8_splitlo_safe(Y), _simd_ u8x8_splitlo_safe(Z)),\
//	_simd_u8x4_fma_safe(_simd_u8x8_splithi_safe(X), _simd_ u8x8_splithi_safe(Y), _simd_ u8x8_splithi_safe(Z)))
//#ifdef _simd_u8x8_fma_
//	#define _simd_u8x8_fma(X,Y,Z) _simd_u8x8_fma_(X,Y,Z)
//	#define _simd_u8x8_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_fma_instruction_set>()
//#elif defined(_simd_u8x16_fma_)
//	static ANVIL_STRONG_INLINE _simd_u8x8 ANVIL_SIMD_CALL _simd_u8x8_fma(const register _simd_u8x8 x, const register _simd_u8x8 y, const register _simd_u8x8 z) {
//		union SIMDUnion { _simd_u8x8 v1; _simd_u8x16 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u8x16_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x8_fma_enable() _simd_u8x16_fma_enable()
//#elif defined(_simd_u8x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_u8x8 ANVIL_SIMD_CALL _simd_u8x8_fma(const register _simd_u8x8 x, const register _simd_u8x8 y, const register _simd_u8x8 z) {
//		union SIMDUnion { _simd_u8x8 v1; _simd_u8x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u8x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x8_fma_enable() _simd_u8x32_fma_enable()
//#elif defined(_simd_u8x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_u8x8 ANVIL_SIMD_CALL _simd_u8x8_fma(const register _simd_u8x8 x, const register _simd_u8x8 y, const register _simd_u8x8 z) {
//		union SIMDUnion { _simd_u8x8 v1; _simd_u8x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u8x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x8_fma_enable() _simd_u8x64_fma_enable()
//#else
//	#define _simd_u8x8_fma(X,Y,Z) _simd_u8x8_combine(\
//		_simd_u8x4_fma(_simd_u8x8_splitlo(X), _simd_u8x8_splitlo(Y), _simd_u8x8_splitlo(Z)),\
//		_simd_u8x4_fma(_simd_u8x8_splithi(X), _simd_u8x8_splithi(Y), _simd_u8x8_splithi(Z)))
//	#define _simd_u8x8_fma_enable() (_simd_u8x4_fma_enable() && _simd_u8x8_combine_enable() && _simd_u8x8_splitlo_enable()  && _simd_u8x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x8_fma_) && ! defined(_simd_u8x8_fma_scalar_)
//	#define _simd_u8x8_fma_scalar_(X,Y,Z) _simd_u8x8_fma_(X,_simd_u8x8_fill_scalar_(Y),_simd_u8x8_fill_scalar_(Z))
//	#define _simd_u8x8_fma_scalar_instruction_set _simd_u8x8_fma_instruction_set
//#endif
//#ifdef _simd_u8x8_fma_scalar_
//	#define _simd_u8x8_fma_scalar(X,Y,Z) _simd_u8x8_fma_scalar_(X,Y,Z)
//	#define _simd_u8x8_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_fma_scalar_instruction_set>()
//#else
//	#define _simd_u8x8_fma_scalar(X,Y,Z) _simd_u8x8_fma_safe(X,_simd_u8x8_fill_scalar_safe(Y),_simd_u8x8_fill_scalar_safe(Z))
//	#define _simd_u8x8_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_u8x1_fma_safe
//	#define _simd_u8x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_u8x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_u8x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_fma_enabled() true
//#endif
//
//#define _simd_u8x16_fma_safe(X,Y,Z)_simd_u8x16_combine_safe(\
//	_simd_u8x8_fma_safe(_simd_u8x16_splitlo_safe(X), _simd_ u8x16_splitlo_safe(Y), _simd_ u8x16_splitlo_safe(Z)),\
//	_simd_u8x8_fma_safe(_simd_u8x16_splithi_safe(X), _simd_ u8x16_splithi_safe(Y), _simd_ u8x16_splithi_safe(Z)))
//#ifdef _simd_u8x16_fma_
//	#define _simd_u8x16_fma(X,Y,Z) _simd_u8x16_fma_(X,Y,Z)
//	#define _simd_u8x16_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_fma_instruction_set>()
//#elif defined(_simd_u8x32_fma_)
//	static ANVIL_STRONG_INLINE _simd_u8x16 ANVIL_SIMD_CALL _simd_u8x16_fma(const register _simd_u8x16 x, const register _simd_u8x16 y, const register _simd_u8x16 z) {
//		union SIMDUnion { _simd_u8x16 v1; _simd_u8x32 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u8x32_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x16_fma_enable() _simd_u8x32_fma_enable()
//#elif defined(_simd_u8x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_u8x16 ANVIL_SIMD_CALL _simd_u8x16_fma(const register _simd_u8x16 x, const register _simd_u8x16 y, const register _simd_u8x16 z) {
//		union SIMDUnion { _simd_u8x16 v1; _simd_u8x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u8x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x16_fma_enable() _simd_u8x64_fma_enable()
//#else
//	#define _simd_u8x16_fma(X,Y,Z) _simd_u8x16_combine(\
//		_simd_u8x8_fma(_simd_u8x16_splitlo(X), _simd_u8x16_splitlo(Y), _simd_u8x16_splitlo(Z)),\
//		_simd_u8x8_fma(_simd_u8x16_splithi(X), _simd_u8x16_splithi(Y), _simd_u8x16_splithi(Z)))
//	#define _simd_u8x16_fma_enable() (_simd_u8x8_fma_enable() && _simd_u8x16_combine_enable() && _simd_u8x16_splitlo_enable()  && _simd_u8x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x16_fma_) && ! defined(_simd_u8x16_fma_scalar_)
//	#define _simd_u8x16_fma_scalar_(X,Y,Z) _simd_u8x16_fma_(X,_simd_u8x16_fill_scalar_(Y),_simd_u8x16_fill_scalar_(Z))
//	#define _simd_u8x16_fma_scalar_instruction_set _simd_u8x16_fma_instruction_set
//#endif
//#ifdef _simd_u8x16_fma_scalar_
//	#define _simd_u8x16_fma_scalar(X,Y,Z) _simd_u8x16_fma_scalar_(X,Y,Z)
//	#define _simd_u8x16_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_fma_scalar_instruction_set>()
//#else
//	#define _simd_u8x16_fma_scalar(X,Y,Z) _simd_u8x16_fma_safe(X,_simd_u8x16_fill_scalar_safe(Y),_simd_u8x16_fill_scalar_safe(Z))
//	#define _simd_u8x16_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_u8x1_fma_safe
//	#define _simd_u8x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_u8x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_u8x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_fma_enabled() true
//#endif
//
//#define _simd_u8x32_fma_safe(X,Y,Z)_simd_u8x32_combine_safe(\
//	_simd_u8x16_fma_safe(_simd_u8x32_splitlo_safe(X), _simd_ u8x32_splitlo_safe(Y), _simd_ u8x32_splitlo_safe(Z)),\
//	_simd_u8x16_fma_safe(_simd_u8x32_splithi_safe(X), _simd_ u8x32_splithi_safe(Y), _simd_ u8x32_splithi_safe(Z)))
//#ifdef _simd_u8x32_fma_
//	#define _simd_u8x32_fma(X,Y,Z) _simd_u8x32_fma_(X,Y,Z)
//	#define _simd_u8x32_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_fma_instruction_set>()
//#elif defined(_simd_u8x64_fma_)
//	static ANVIL_STRONG_INLINE _simd_u8x32 ANVIL_SIMD_CALL _simd_u8x32_fma(const register _simd_u8x32 x, const register _simd_u8x32 y, const register _simd_u8x32 z) {
//		union SIMDUnion { _simd_u8x32 v1; _simd_u8x64 v2; };
//		SIMDUnion x_, y_, z_;
//		x_.v1 = x;
//		y_.v1 = y;
//		z_.v1 = z;
//		x_.v2 = _simd_u8x64_fma_(x_.v2, y_.v2, z_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x32_fma_enable() _simd_u8x64_fma_enable()
//#else
//	#define _simd_u8x32_fma(X,Y,Z) _simd_u8x32_combine(\
//		_simd_u8x16_fma(_simd_u8x32_splitlo(X), _simd_u8x32_splitlo(Y), _simd_u8x32_splitlo(Z)),\
//		_simd_u8x16_fma(_simd_u8x32_splithi(X), _simd_u8x32_splithi(Y), _simd_u8x32_splithi(Z)))
//	#define _simd_u8x32_fma_enable() (_simd_u8x16_fma_enable() && _simd_u8x32_combine_enable() && _simd_u8x32_splitlo_enable()  && _simd_u8x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x32_fma_) && ! defined(_simd_u8x32_fma_scalar_)
//	#define _simd_u8x32_fma_scalar_(X,Y,Z) _simd_u8x32_fma_(X,_simd_u8x32_fill_scalar_(Y),_simd_u8x32_fill_scalar_(Z))
//	#define _simd_u8x32_fma_scalar_instruction_set _simd_u8x32_fma_instruction_set
//#endif
//#ifdef _simd_u8x32_fma_scalar_
//	#define _simd_u8x32_fma_scalar(X,Y,Z) _simd_u8x32_fma_scalar_(X,Y,Z)
//	#define _simd_u8x32_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_fma_scalar_instruction_set>()
//#else
//	#define _simd_u8x32_fma_scalar(X,Y,Z) _simd_u8x32_fma_safe(X,_simd_u8x32_fill_scalar_safe(Y),_simd_u8x32_fill_scalar_safe(Z))
//	#define _simd_u8x32_fma_scalar_enabled() true
//#endif
//
//#ifndef _simd_u8x1_fma_safe
//	#define _simd_u8x1_fma_safe(X,Y,Z) (X * Y + Z)
//	#define _simd_u8x1_fma_(X,Y,Z) x1_fma_safe(X,Y,Z)
//	#define _simd_u8x1_fma_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_fma_enabled() true
//#endif
//
//#define _simd_u8x64_fma_safe(X,Y,Z)_simd_u8x64_combine_safe(\
//	_simd_u8x32_fma_safe(_simd_u8x64_splitlo_safe(X), _simd_ u8x64_splitlo_safe(Y), _simd_ u8x64_splitlo_safe(Z)),\
//	_simd_u8x32_fma_safe(_simd_u8x64_splithi_safe(X), _simd_ u8x64_splithi_safe(Y), _simd_ u8x64_splithi_safe(Z)))
//#ifdef _simd_u8x64_fma_
//	#define _simd_u8x64_fma(X,Y,Z) _simd_u8x64_fma_(X,Y,Z)
//	#define _simd_u8x64_fma_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_fma_instruction_set>()
//#else
//	#define _simd_u8x64_fma(X,Y,Z) _simd_u8x64_combine(\
//		_simd_u8x32_fma(_simd_u8x64_splitlo(X), _simd_u8x64_splitlo(Y), _simd_u8x64_splitlo(Z)),\
//		_simd_u8x32_fma(_simd_u8x64_splithi(X), _simd_u8x64_splithi(Y), _simd_u8x64_splithi(Z)))
//	#define _simd_u8x64_fma_enable() (_simd_u8x32_fma_enable() && _simd_u8x64_combine_enable() && _simd_u8x64_splitlo_enable()  && _simd_u8x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x64_fma_) && ! defined(_simd_u8x64_fma_scalar_)
//	#define _simd_u8x64_fma_scalar_(X,Y,Z) _simd_u8x64_fma_(X,_simd_u8x64_fill_scalar_(Y),_simd_u8x64_fill_scalar_(Z))
//	#define _simd_u8x64_fma_scalar_instruction_set _simd_u8x64_fma_instruction_set
//#endif
//#ifdef _simd_u8x64_fma_scalar_
//	#define _simd_u8x64_fma_scalar(X,Y,Z) _simd_u8x64_fma_scalar_(X,Y,Z)
//	#define _simd_u8x64_fma_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_fma_scalar_instruction_set>()
//#else
//	#define _simd_u8x64_fma_scalar(X,Y,Z) _simd_u8x64_fma_safe(X,_simd_u8x64_fill_scalar_safe(Y),_simd_u8x64_fill_scalar_safe(Z))
//	#define _simd_u8x64_fma_scalar_enabled() true
//#endif
//
