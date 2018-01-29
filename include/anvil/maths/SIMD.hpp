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

#ifndef ANVIL_MATHS_SIMD_HPP
#define ANVIL_MATHS_SIMD_HPP

	//! \todo Specialise OP_CAST
	//! \todo Implement OP_POPCN
	//! \todo Implement OP_REFLECT

#include <cmath>
#include "anvil/core/Cpu.hpp"
#include "anvil/core/Keywords.hpp"

#if ANVIL_ARCHITECTURE == ANVIL_X86 || ANVIL_ARCHITECTURE == ANVIL_X64
	#define ANVIL_USE_INTEL_SIMD_INTRINSICS
	#include <immintrin.h>
	#include <intrin.h>

	#define ANVIL_SIMD_CALL __vectorcall 
#else
	#define ANVIL_SIMD_CALL ANVIL_CALL
#endif

namespace anvil { namespace simd {

	// Instruction set definitions

	enum InstructionSet : int16_t {
		IS_NONE,
#ifdef ANVIL_USE_INTEL_SIMD_INTRINSICS
		IS_MMX        = 1 << 0,
		IS_SSE        = 1 << 1,
		IS_SSE_2      = 1 << 2,
		IS_SSE_3      = 1 << 3,
		IS_SSSE_3     = 1 << 4,
		IS_SSE_4_1    = 1 << 5,
		IS_SSE_4_2    = 1 << 6,
		IS_AVX        = 1 << 7,
		IS_FMA        = 1 << 8,
		IS_AVX_2      = 1 << 9,
		IS_KNC        = 1 << 10,
		IS_AVX_512_F  = 1 << 11,
		IS_AVX_512_PF = 1 << 12,
		IS_AVX_512_ER = 1 << 13,
		IS_AVX_512_CD = 1 << 14,

		IS_AVX_512    = IS_AVX_512_F | IS_AVX_512_PF | IS_AVX_512_ER | IS_AVX_512_CD
#endif
	};
	namespace detail {
	static int16_t ANVIL_SIMD_CALL CheckInstructionSetSupport() {
		int16_t flags = 0;
	#ifdef ANVIL_USE_INTEL_SIMD_INTRINSICS
			int data[2][4];
			__cpuid(data[0], 0);
			const int ids = data[0][0];
			if (ids < 7) {
				if (ids < 1) {
					return false;
				}else {
					__cpuidex(data[0], 1, 0);
					memset(data[1], 0, sizeof(int) * 4);
				}
			}else {
				__cpuidex(data[0], 1, 0);
				__cpuidex(data[1], 7, 0);
			}
			enum {
				EAX_,
				EBX_,
				ECX_,
				EDX_
			};

			if (data[0][EDX_] & (1 << 23)) {
				flags |= IS_MMX;
			} if (data[0][EDX_] & (1 << 25)) {
				flags |= IS_SSE;
			} if (data[0][EDX_] & (1 << 26)) {
				flags |= IS_SSE_2;
			} if (data[0][ECX_] & (1 << 0)) {
				flags |= IS_SSE_3;
			} if (data[0][ECX_] & (1 << 9)) {
				flags |= IS_SSSE_3;
			} if (data[0][ECX_] & (1 << 19)) {
				flags |= IS_SSE_4_1;
			} if (data[0][ECX_] & (1 << 20)) {
				flags |= IS_SSE_4_2;
			} if (data[0][ECX_] & (1 << 28)) {
				flags |= IS_AVX;
			} if (data[0][EBX_] & (1 << 5)) {
				flags |= IS_AVX_2;
			} if (false) { //! \todo Implement
				flags |= IS_KNC;
			} if (data[1][EBX_] & (1 << 16)) {
				flags |= IS_AVX_512_F;
			} if (data[1][EBX_] & (1 << 26)) {
				flags |= IS_AVX_512_PF;
			} if (data[1][EBX_] & (1 << 27)) {
				flags |= IS_AVX_512_ER;
			} if (data[1][EBX_] & (1 << 28)) {
				flags |= IS_AVX_512_CD;
			}
	#endif
			return flags;
		}
	}


	static ANVIL_STRONG_INLINE bool ANVIL_SIMD_CALL IsInstructionSetSupported(InstructionSet aSet) {
		static const int64_t g_enabled_sets = detail::CheckInstructionSetSupport();
		return (g_enabled_sets & aSet) == aSet;
	}

	template<InstructionSet IS>
	static ANVIL_STRONG_INLINE bool IsInstructionSetSupported() {
		return IsInstructionSetSupported(IS);
	}

#if ANVIL_ARCHITECTURE == ANVIL_X86
	template<>
	ANVIL_CONSTEXPR_FN static ANVIL_STRONG_INLINE bool IsInstructionSetSupported<IS_MMX>() {
		return true;
	}
#endif

#if ANVIL_ARCHITECTURE == ANVIL_X64
	template<>
	ANVIL_CONSTEXPR_FN static ANVIL_STRONG_INLINE bool IsInstructionSetSupported<IS_MMX>() {
		return false;
	}

	template<>
	ANVIL_CONSTEXPR_FN static ANVIL_STRONG_INLINE bool IsInstructionSetSupported<IS_SSE>() {
		return true;
	}

	template<>
	ANVIL_CONSTEXPR_FN static ANVIL_STRONG_INLINE bool IsInstructionSetSupported<IS_SSE_2>() {
		return true;
	}
#endif

	// Operation definitions

	enum Operation : int64_t {
		// Misc operations
		OP_FILL    = 1i64 << 0i64,
		OP_CAST    = 1i64 << 1i64,
		OP_RESIZE  = 1i64 << 2i64,
		// 3 parameters
		OP_FMA     = 1i64 << 3i64,
		OP_FMS     = 1i64 << 4i64,
		// 2 parameters
		OP_ADD     = 1i64 << 5i64,
		OP_SUB     = 1i64 << 6i64,
		OP_MUL     = 1i64 << 7i64,
		OP_DIV     = 1i64 << 8i64,
		OP_MIN     = 1i64 << 9i64,
		OP_MAX     = 1i64 << 10i64,
		OP_AND     = 1i64 << 11i64,
		OP_OR      = 1i64 << 12i64,
		OP_XOR     = 1i64 << 13i64,
		OP_LSHIFT  = 1i64 << 14i64, 
		OP_RSHIFT  = 1i64 << 15i64, 
		OP_MOD     = 1i64 << 16i64, 
		OP_DIM     = 1i64 << 17i64, 
		OP_CMPEQ   = 1i64 << 18i64, 
		OP_CMPNE   = 1i64 << 19i64, 
		OP_CMPLT   = 1i64 << 20i64, 
		OP_CMPGT   = 1i64 << 21i64, 
		OP_CMPLE   = 1i64 << 22i64, 
		OP_CMPGE   = 1i64 << 23i64, 
		OP_ATAN2   = 1i64 << 24i64, 
		OP_REFLECT = 1i64 << 25i64,
		// 1 parameter
		OP_NOT     = 1i64 << 26i64, 
		OP_ABS     = 1i64 << 27i64, 
		OP_EXP     = 1i64 << 28i64, 
		OP_LOG     = 1i64 << 29i64, 
		OP_LOG2    = 1i64 << 30i64,
		OP_LOG10   = 1i64 << 31i64,
		OP_CEIL    = 1i64 << 32i64,
		OP_FLOOR   = 1i64 << 33i64, 
		OP_ROUND   = 1i64 << 34i64, 
		OP_SIN     = 1i64 << 35i64, 
		OP_COS     = 1i64 << 36i64, 
		OP_TAN     = 1i64 << 37i64, 
		OP_ASIN    = 1i64 << 38i64, 
		OP_ACOS    = 1i64 << 39i64, 
		OP_ATAN    = 1i64 << 40i64, 
		OP_COSH    = 1i64 << 41i64, 
		OP_SINH    = 1i64 << 42i64, 
		OP_TANH    = 1i64 << 43i64, 
		OP_SQRT    = 1i64 << 44i64, 
		OP_CBRT    = 1i64 << 45i64,
		// 1 Parameter, scalar output
		OP_AVG     = 1i64 << 46i64, 
		OP_SUM     = 1i64 << 47i64, 
		OP_POPCN   = 1i64 << 48i64
	};

	namespace detail {
		template<Operation O>
		struct OperationParams {
			enum { value = 0 };
		};

		template<Operation O, class T, size_t S>
		struct OperationInstructionSet {
			enum : int64_t { value = IS_NONE };
		};
		
		template<> struct OperationParams<OP_FILL>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_CAST>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_RESIZE>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_FMA>{ enum { value = 3 }; };
		template<> struct OperationParams<OP_FMS>{ enum { value = 3 }; };
		template<> struct OperationParams<OP_ADD>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_SUB>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_MUL>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_DIV>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_MIN>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_MAX>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_OR>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_LSHIFT>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_RSHIFT>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_MOD>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_DIM>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_CMPEQ>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_CMPNE>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_CMPLT>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_CMPGT>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_CMPLE>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_CMPGE>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_ATAN2>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_REFLECT>{ enum { value = 2 }; };
		template<> struct OperationParams<OP_NOT>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_ABS>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_EXP>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_LOG>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_LOG2>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_LOG10>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_CEIL>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_FLOOR>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_ROUND>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_SIN>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_COS>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_TAN>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_ASIN>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_ACOS>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_ATAN>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_COSH>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_SINH>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_TANH>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_SQRT>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_CBRT>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_AVG>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_SUM>{ enum { value = 1 }; };
		template<> struct OperationParams<OP_POPCN>{ enum { value = 1 }; };
	}

	template<Operation O, class T>
	struct OperationInfo {
		enum : int64_t { 
			instruction_set_64 = detail::OperationInstructionSet<O, T, 64>::value,
			instruction_set_32 = detail::OperationInstructionSet<O, T, 32>::value,
			instruction_set_16 = detail::OperationInstructionSet<O, T, 16>::value,
			instruction_set_8 = detail::OperationInstructionSet<O, T, 8>::value,
			instruction_set_4 = detail::OperationInstructionSet<O, T, 4>::value,
			instruction_set_2 = detail::OperationInstructionSet<O, T, 2>::value,
			instruction_set_max = 
				instruction_set_64 ? instruction_set_64 :
				instruction_set_32 ? instruction_set_32 :
				instruction_set_16 ? instruction_set_16 :
				instruction_set_8 ? instruction_set_8 :
				instruction_set_4 ? instruction_set_4 :
				IS_NONE
		};
		enum {
			params = detail::OperationParams<O>::value,
			size_max = 
				instruction_set_64 ? 64 :
				instruction_set_32 ? 32 :
				instruction_set_16 ? 16 :
				instruction_set_8 ? 8 :
				instruction_set_4 ? 4 :
				2
		};

		template<size_t S>
		struct LoopInfo {
			enum {
				size = 
					instruction_set_64 && S >= 64 ? 64 :
					instruction_set_32 && S >= 32 ? 32 :
					instruction_set_16 && S >= 16 ? 16 :
					instruction_set_8 && S >= 8 ? 8 :
					instruction_set_4 && S >= 4 ? 4 :
					S >= 2 ? 2 :
					1,
				loops = S / size,
				remainder = S % S
			};
			enum : int64_t {
				instruction_set =
					size == 64 ? instruction_set_64 :
					size == 32 ? instruction_set_32 :
					size == 16 ? instruction_set_16 :
					size == 8 ? instruction_set_8  :
					size == 4 ? instruction_set_4  :
					IS_NONE
			};
		};
	};

	// Data Helpers

	template<class T, size_t S>
	struct DefaultSIMD {
		T elements[S];
	};

	template<class T, size_t S>
	struct SIMDHelper {
		typedef DefaultSIMD<T, S> simd_t;
		//static_assert(sizeof(simd_t) == (sizeof(T) * S), "simd_t size error");

		static simd_t ANVIL_SIMD_CALL load(const T* x) {
			simd_t tmp;
			memcpy(tmp, x, sizeof(simd_t));
			return tmp;
		}

		static simd_t ANVIL_SIMD_CALL fillu() {
			return simd_t();
		}

		static simd_t ANVIL_SIMD_CALL fill0() {
			simd_t tmp;
			memset(&tmp, 0, sizeof(T) * S);
			return tmp;
		}

		static simd_t ANVIL_SIMD_CALL fill(const T x) {
			simd_t tmp;
			for (size_t i = 0; i < S; ++i) tmp.elements[i] = x;
			return tmp;
		}

		static ANVIL_STRONG_INLINE simd_t ANVIL_SIMD_CALL set1(const T x) {
			set4(x, static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));
		}

		static ANVIL_STRONG_INLINE simd_t ANVIL_SIMD_CALL set2(const T x, const T y) {
			set4(x, y, static_cast<T>(0), static_cast<T>(0));
		}

		static ANVIL_STRONG_INLINE simd_t ANVIL_SIMD_CALL set3(const T x, const T y, const T z) {
			set4(x, y, z, static_cast<T>(0));
		}

		static simd_t ANVIL_SIMD_CALL set4(const T x, const T y, const T z, const T w) {
			simd_t tmp = S > 3 ? load_0 : simd_t();
			tmp.elements[0] = x;
			if (S >= 2) tmp.elements[1] = y;
			if (S >= 3) tmp.elements[2] = z;
			if (S >= 4) tmp.elements[3] = w;
			return tmp;
		}

		template<size_t GS>
		static void ANVIL_SIMD_CALL get(const simd_t x, T* y) {
			typedef DefaultSIMD<T, GS> simd2_t;
			union {
				simd2_t s2;
				simd_t s;
			};
			s = x;
			*reinterpret_cast<simd2_t*>(y) = s2;
		}

		template<size_t GS>
		static ANVIL_STRONG_INLINE simd_t ANVIL_SIMD_CALL setn(const T* y) {
			typedef DefaultSIMD<T, GS> simd2_t;
			union {
				simd2_t s2;
				simd_t s;
			};
			s2 = *reinterpret_cast<const simd2_t*>(y);
			return s;
		}

		template<>
		static ANVIL_STRONG_INLINE simd_t ANVIL_SIMD_CALL setn<S>(const T* y) {
			return *reinterpret_cast<const simd_t*>(y);
		}
	};

	template<class T>
	struct SIMDHelper<T,1> {
		typedef T simd_t;
		static ANVIL_STRONG_INLINE simd_t ANVIL_SIMD_CALL load(const T* x) { return x[0]; }
		static ANVIL_STRONG_INLINE simd_t ANVIL_SIMD_CALL fillu() { return simd_t(); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_SIMD_CALL fill0() { return static_cast<simd_t>(0); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_SIMD_CALL fill(const T x) { return x; }
		static ANVIL_STRONG_INLINE simd_t ANVIL_SIMD_CALL set1(const T x) { return x; }
		static ANVIL_STRONG_INLINE simd_t ANVIL_SIMD_CALL set2(const T x, const T y) { return x; }
		static ANVIL_STRONG_INLINE simd_t ANVIL_SIMD_CALL set3(const T x, const T y, const T z) { return x; }
		static ANVIL_STRONG_INLINE simd_t ANVIL_SIMD_CALL set4(const T x, const T y, const T z, const T w) { return x; }
		template<size_t GS> static ANVIL_STRONG_INLINE void ANVIL_SIMD_CALL get(simd_t x, T* y) { y[0] = x; }
		template<size_t GS> static ANVIL_STRONG_INLINE simd_t ANVIL_SIMD_CALL setn(const T* y) { return y[0]; }
	};

	// Default Operation Implementation

	template<class T, size_t S, Operation O, bool OPTIMISED = false>
	struct OperationImplementation {
		template<size_t P = 3>
		static void ANVIL_SIMD_CALL execute(const T* x, const T* y, const T* z, T* o) {
			for (size_t i = 0; i < S; ++i) o[i] = OperationImplementation<T, 1, O, false>::execute(x[i], y[i], z[i]);
		}

		template<size_t P = 2>
		static void ANVIL_SIMD_CALL execute(const T* x, const T* y, T* o) {
			for (size_t i = 0; i < S; ++i) o[i] = OperationImplementation<T, 1, O, false>::execute(x[i], y[i]);
		}

		template<size_t P = 1>
		static void ANVIL_SIMD_CALL execute(const T* x, T* o) {
			for (size_t i = 0; i < S; ++i) o[i] = OperationImplementation<T, 1, O, false>::execute(x[i]);
		}
	};

	template<class T, size_t S>
	struct OperationImplementation<T, S, OP_FILL, false> {
		static ANVIL_STRONG_INLINE void ANVIL_SIMD_CALL execute(T* aOutput) {
			memset(aOutput, 0, sizeof(T) * S);
		}

		static void ANVIL_SIMD_CALL execute(T x, T* o) {
			for (size_t i = 0; i < S; ++i) o[i] = x;
		}

		static void ANVIL_SIMD_CALL execute(T x, T y, T* o) {
			if (S > 2) execute(o);
			o[0] = x;
			if (S > 1) o[1] = y;
		}

		static void ANVIL_SIMD_CALL execute(T x, T y, T z, T* o) {
			if (S > 3) execute(o);
			o[0] = x;
			if (S > 1) o[1] = y;
			if (S > 2) o[2] = z;
		}

		static void ANVIL_SIMD_CALL execute(T x, T y, T z, T w, T* o) {
			if (S > 4) execute(o);
			o[0] = x;
			if (S > 1) o[1] = y;
			if (S > 2) o[2] = z;
			if (S > 3) o[3] = w;
		}
	};

	template<class T, size_t S>
	struct OperationImplementation<T, S, OP_CAST, false> {
		template<class T2>
		static void ANVIL_SIMD_CALL execute(const T2* x, T* y) {
			for (size_t i = 0; i < S; ++i) y[i] = static_cast<T>(x[i]);
		}
	};

	template<class T, size_t S>
	struct OperationImplementation<T, S, OP_RESIZE, false> {
		template<size_t S2>
		static void ANVIL_SIMD_CALL execute(const T* x, T* y) {
			if (S > S2) Operation<T, S, OP_FILL>::execute(y);
			enum {S3 = S > S2 ? S2 : S };
			for (size_t i = 0; i < S3; ++i) y[i] = x[i];
		}
	};

	template<class A, class B>
	static ANVIL_STRONG_INLINE A value_cast(B x) {
		union {
			A a;
			B b;
		};
		b = x;
		return a;
	}

#define ANVIL_SIMD_FMA(X,Y,Z) ((X * Y) + Z)
#define ANVIL_SIMD_FMS(X,Y,Z) ((X * Y) - Z)
#define ANVIL_SIMD_ADD(X,Y) (X + Y)
#define ANVIL_SIMD_SUB(X,Y) (X - Y)
#define ANVIL_SIMD_MUL(X,Y) (X * Y)
#define ANVIL_SIMD_DIV(X,Y) (X / Y)
#define ANVIL_SIMD_AND(X,Y) (X & Y)
#define ANVIL_SIMD_OR(X,Y) (X | Y)
#define ANVIL_SIMD_XOR(X,Y) (X ^ Y)
#define ANVIL_SIMD_AND_F(X,Y) value_cast<float>(value_cast<int32_t>(X) & value_cast<int32_t>(Y))
#define ANVIL_SIMD_OR_F(X,Y) value_cast<float>(value_cast<int32_t>(X) | value_cast<int32_t>(Y))
#define ANVIL_SIMD_XOR_F(X,Y) value_cast<float>(value_cast<int32_t>(X) ^ value_cast<int32_t>(Y))
#define ANVIL_SIMD_AND_D(X,Y) value_cast<double>(value_cast<int64_t>(X) & value_cast<int64_t>(Y))
#define ANVIL_SIMD_OR_D(X,Y) value_cast<double>(value_cast<int64_t>(X) | value_cast<int64_t>(Y))
#define ANVIL_SIMD_XOR_D(X,Y) value_cast<double>(value_cast<int64_t>(X) ^ value_cast<int64_t>(Y))
#define ANVIL_SIMD_LSHIFT(X,Y) (X << Y)
#define ANVIL_SIMD_RSHIFT(X,Y) (X >> Y)
#define ANVIL_SIMD_MOD(X,Y) (X % Y)
#define ANVIL_SIMD_CMPEQ(X,Y) (X == Y)
#define ANVIL_SIMD_CMPNE(X,Y) (X != Y)
#define ANVIL_SIMD_CMPLT(X,Y) (X < Y)
#define ANVIL_SIMD_CMPGT(X,Y) (X > Y)
#define ANVIL_SIMD_CMPLE(X,Y) (X <= Y)
#define ANVIL_SIMD_CMPGE(X,Y) (X >= Y)
#define ANVIL_SIMD_DIM(X,Y) (X > Y ? X - Y : 0)
#define ANVIL_SIMD_NOP2(X, Y) X
#define ANVIL_SIMD_NOT(X) (~X)
#define ANVIL_SIMD_NOP1(X) X

#define ANVIL_SIMD_IMPLEMENTATION_S_SSS_1(O,F)\
	template<class T>\
	struct OperationImplementation<T, 1, O, false> {\
		static ANVIL_STRONG_INLINE T ANVIL_SIMD_CALL execute(T x, T y, T z) {\
			return F(x, y, z);\
		}\
		static ANVIL_STRONG_INLINE T ANVIL_SIMD_CALL execute(const T* x, const T* y, const T* z, T* o) {\
			return *o = F(*x,*y,*z);\
		}\
	};\

#define ANVIL_SIMD_IMPLEMENTATION_S_SS_1(O,F)\
	template<class T>\
	struct OperationImplementation<T, 1, O, false> {\
		static ANVIL_STRONG_INLINE T ANVIL_SIMD_CALL execute(T x, T y) {\
			return F(x, y);\
		}\
		static ANVIL_STRONG_INLINE T ANVIL_SIMD_CALL execute(const T* x, const T* y, T* o) {\
			return *o = F(*x,*y);\
		}\
	};\

#define ANVIL_SIMD_IMPLEMENTATION_S_SS_1_SPECIALISE(O,T,F)\
	template<>\
	struct OperationImplementation<T, 1, O, false> {\
		static ANVIL_STRONG_INLINE T ANVIL_SIMD_CALL execute(T x, T y) {\
			return F(x, y);\
		}\
		static ANVIL_STRONG_INLINE T ANVIL_SIMD_CALL execute(const T* x, const T* y, T* o) {\
			return *o = F(*x,*y);\
		}\
	};\

#define ANVIL_SIMD_IMPLEMENTATION_S_S_1(O,F)\
	template<class T>\
	struct OperationImplementation<T, 1, O, false> {\
		static ANVIL_STRONG_INLINE T ANVIL_SIMD_CALL execute(T x) {\
			return F(x);\
		}\
		static ANVIL_STRONG_INLINE T ANVIL_SIMD_CALL execute(const T* x, T* o) {\
			return *o = F(*x);\
		}\
	};\

#define ANVIL_SIMD_IMPLEMENTATION_S_S_1_SPECIALISE(O,T,F)\
	template<>\
	struct OperationImplementation<T, 1, O, false> {\
		static ANVIL_STRONG_INLINE T ANVIL_SIMD_CALL execute(T x) {\
			return F(x);\
		}\
		static ANVIL_STRONG_INLINE T ANVIL_SIMD_CALL execute(const T* x, T* o) {\
			return *o = F(*x);\
		}\
	};\

	ANVIL_SIMD_IMPLEMENTATION_S_SSS_1(OP_FMA, ANVIL_SIMD_FMA)
	ANVIL_SIMD_IMPLEMENTATION_S_SSS_1(OP_FMS, ANVIL_SIMD_FMS)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1(OP_ADD, ANVIL_SIMD_ADD)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1(OP_SUB, ANVIL_SIMD_SUB)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1(OP_MUL, ANVIL_SIMD_MUL)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1(OP_DIV, ANVIL_SIMD_DIV)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1(OP_AND, ANVIL_SIMD_AND)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1(OP_MIN, std::min)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1(OP_MAX, std::max)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1_SPECIALISE(OP_AND, float, ANVIL_SIMD_AND_F)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1_SPECIALISE(OP_AND, double, ANVIL_SIMD_AND_D)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1(OP_OR, ANVIL_SIMD_OR)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1_SPECIALISE(OP_OR, float, ANVIL_SIMD_OR_F)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1_SPECIALISE(OP_OR, double, ANVIL_SIMD_OR_D)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1(OP_XOR, ANVIL_SIMD_XOR)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1_SPECIALISE(OP_XOR, float, ANVIL_SIMD_XOR_F)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1_SPECIALISE(OP_XOR, double, ANVIL_SIMD_XOR_D)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1(OP_LSHIFT, ANVIL_SIMD_LSHIFT)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1(OP_RSHIFT, ANVIL_SIMD_RSHIFT)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1_SPECIALISE(OP_LSHIFT, float, ANVIL_SIMD_NOP2)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1_SPECIALISE(OP_RSHIFT, double, ANVIL_SIMD_NOP2)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1(OP_MOD, ANVIL_SIMD_MOD)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1_SPECIALISE(OP_MOD, float, std::fmod)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1_SPECIALISE(OP_MOD, double, std::fmod)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1(OP_DIM, ANVIL_SIMD_DIM)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1_SPECIALISE(OP_DIM, float, std::fdim)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1_SPECIALISE(OP_DIM, double, std::fdim)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1(OP_CMPEQ, ANVIL_SIMD_CMPEQ)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1(OP_CMPNE, ANVIL_SIMD_CMPNE)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1(OP_CMPLT, ANVIL_SIMD_CMPLT)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1(OP_CMPGT, ANVIL_SIMD_CMPGT)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1(OP_CMPLE, ANVIL_SIMD_CMPLE)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1(OP_CMPGE, ANVIL_SIMD_CMPGE)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1(OP_ATAN2, std::atan2)
	ANVIL_SIMD_IMPLEMENTATION_S_SS_1(OP_REFLECT, reflect)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1(OP_NOT, ANVIL_SIMD_NOT)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1(OP_ABS, std::abs)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1_SPECIALISE(OP_ABS, float, std::fabs)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1_SPECIALISE(OP_ABS, double, std::fabs)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1_SPECIALISE(OP_ABS, uint64_t, ANVIL_SIMD_NOP1)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1_SPECIALISE(OP_ABS, uint32_t, ANVIL_SIMD_NOP1)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1_SPECIALISE(OP_ABS, uint16_t, ANVIL_SIMD_NOP1)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1_SPECIALISE(OP_ABS, uint8_t, ANVIL_SIMD_NOP1)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1(OP_EXP, std::exp)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1(OP_LOG, std::log)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1(OP_LOG2, std::log2)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1(OP_LOG10, std::log10)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1(OP_CEIL, ANVIL_SIMD_NOP1)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1_SPECIALISE(OP_CEIL, float, std::ceil)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1_SPECIALISE(OP_CEIL, double, std::ceil)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1(OP_FLOOR, ANVIL_SIMD_NOP1)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1_SPECIALISE(OP_FLOOR, float, std::floor)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1_SPECIALISE(OP_FLOOR, double, std::floor)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1(OP_ROUND, ANVIL_SIMD_NOP1)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1_SPECIALISE(OP_ROUND, float, std::round)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1_SPECIALISE(OP_ROUND, double, std::round)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1(OP_SIN, std::sin)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1(OP_COS, std::cos)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1(OP_TAN, std::tan)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1(OP_ASIN, std::asin)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1(OP_ACOS, std::acos)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1(OP_ATAN, std::atan)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1(OP_SINH, std::sinh)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1(OP_COSH, std::cosh)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1(OP_TANH, std::tanh)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1(OP_SQRT, std::sqrt)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1(OP_CBRT, std::cbrt)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1(OP_AVG, ANVIL_SIMD_NOP1)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1(OP_SUM, ANVIL_SIMD_NOP1)
	ANVIL_SIMD_IMPLEMENTATION_S_S_1(OP_POPCN, popcount)


	template<class T, size_t S, Operation O>
	struct OperationDispatcher {
		typedef typename SIMDHelper<T, S>::simd_t simd_t;
		typedef OperationInfo<O, T> info;

		enum {
			loop_64 = S / 64,
			loop_32 = S / 32,
			loop_16 = S / 16,
			loop_8 = S / 8,
			loop_4 = S / 4,
			loop_2 = S / 2,
			remainder_64 = S % 64,
			remainder_32 = S % 32,
			remainder_16 = S % 16,
			remainder_8 = S % 8,
			remainder_4 = S % 4,
			remainder_2 = S % 2,
		};

		template<size_t P = 3>
		static void ANVIL_SIMD_CALL execute(const T* x, const T* y, const T* z, T* o) {
			if (S >= 64 && info::instruction_set_64 != IS_NONE && IsInstructionSetSupported<static_cast<InstructionSet>(info::instruction_set_64)>()) {
				for (size_t i = 0; i < loop_64; ++i) {
					OperationImplementation<T, 64, O, false>::execute(x, y, z, o);
					x += 64;
					y += 64;
					z += 64;
					o += 64;
				}
				OperationDispatcher<T, remainder_64, O>::execute(x, y, z, o);
			} else if (S >= 32 && info::instruction_set_32 != IS_NONE && IsInstructionSetSupported<static_cast<InstructionSet>(info::instruction_set_32)>()) {
				for (size_t i = 0; i < loop_32; ++i) {
					OperationImplementation<T, 32, O, true>::execute(x, y, z, o);
					x += 32;
					y += 32;
					z += 32;
					o += 32;
				}
				OperationDispatcher<T, remainder_32, O>::execute(x, y, z, o);
			} else if (S >= 16 && info::instruction_set_16 != IS_NONE && IsInstructionSetSupported<static_cast<InstructionSet>(info::instruction_set_16)>()) {
				for (size_t i = 0; i < loop_16; ++i) {
					OperationImplementation<T, 16, O, true>::execute(x, y, z, o);
					x += 16;
					y += 16;
					z += 16;
					o += 16;
				}
				OperationDispatcher<T, remainder_16, O>::execute(x, y, z, o);
			} else if (S >= 8 && info::instruction_set_8 != IS_NONE && IsInstructionSetSupported<static_cast<InstructionSet>(info::instruction_set_8)>()) {
				for (size_t i = 0; i < loop_8; ++i) {
					OperationImplementation<T, 8, O, true>::execute(x, y, z, o);
					x += 8;
					y += 8;
					z += 8;
					o += 8;
				}
				OperationDispatcher<T, remainder_8, O>::execute(x, y, o);
			} else if (S >= 4 && info::instruction_set_4 != IS_NONE && IsInstructionSetSupported<static_cast<InstructionSet>(info::instruction_set_4)>()) {
				for (size_t i = 0; i < loop_4; ++i) {
					OperationImplementation<T, 4, O, true>::execute(x, y, z, o);
					x += 4;
					y += 4;
					z += 4;
					o += 4;
				}
				OperationImplementation<T, remainder_4, O, false>::execute(x, y, z, o);
			} else if (S >= 2 && info::instruction_set_2 != IS_NONE &&IsInstructionSetSupported<static_cast<InstructionSet>(info::instruction_set_2)>()) {
				for (size_t i = 0; i < loop_2; ++i) {
					OperationImplementation<T, 2, O, true>::execute(x, y, z, o);
					x += 2;
					y += 2;
					z += 2;
					o += 2;
				}
				OperationDispatcher<T, remainder_2, O>::execute(x, y, z, o);
			} else {
				OperationImplementation<T, S, O, false>::execute(x, y, z, o);
			}
		}

		template<size_t P = 2>
		static void ANVIL_SIMD_CALL execute(const T* x, const T* y, T* o) {
			if (S >= 64 && info::instruction_set_64 != IS_NONE && IsInstructionSetSupported<static_cast<InstructionSet>(info::instruction_set_64)>()) {
				for (size_t i = 0; i < loop_64; ++i) {
					OperationImplementation<T, 64, O, false>::execute(x, y, o);
					x += 64;
					y += 64;
					o += 64;
				}
				OperationDispatcher<T, remainder_64, O>::execute(x, y, o);
			} else if (S >= 32 && info::instruction_set_32 != IS_NONE && IsInstructionSetSupported<static_cast<InstructionSet>(info::instruction_set_32)>()) {
				for (size_t i = 0; i < loop_32; ++i) {
					OperationImplementation<T, 32, O, true>::execute(x, y, o);
					x += 32;
					y += 32;
					o += 32;
				}
				OperationDispatcher<T, remainder_32, O>::execute(x, y, o);
			} else if (S >= 16 && info::instruction_set_16 != IS_NONE && IsInstructionSetSupported<static_cast<InstructionSet>(info::instruction_set_16)>()) {
				for (size_t i = 0; i < loop_16; ++i) {
					OperationImplementation<T, 16, O, true>::execute(x, y, o);
					x += 16;
					y += 16;
					o += 16;
				}
				OperationDispatcher<T, remainder_16, O>::execute(x, y, o);
			} else if (S >= 8 && info::instruction_set_8 != IS_NONE && IsInstructionSetSupported<static_cast<InstructionSet>(info::instruction_set_8)>()) {
				for (size_t i = 0; i < loop_8; ++i) {
					OperationImplementation<T, 8, O, true>::execute(x, y, o);
					x += 8;
					y += 8;
					o += 8;
				}
				OperationDispatcher<T, remainder_8, O>::execute(x, y, o);
			} else if (S >= 4 && info::instruction_set_4 != IS_NONE && IsInstructionSetSupported<static_cast<InstructionSet>(info::instruction_set_4)>()) {
				for (size_t i = 0; i < loop_4; ++i) {
					OperationImplementation<T, 4, O, true>::execute(x, y, o);
					x += 4;
					y += 4;
					o += 4;
				}
				OperationImplementation<T, remainder_4, O, false>::execute(x, y, o);
			} else if (S >= 2 && info::instruction_set_2 != IS_NONE &&IsInstructionSetSupported<static_cast<InstructionSet>(info::instruction_set_2)>()) {
				for (size_t i = 0; i < loop_2; ++i) {
					OperationImplementation<T, 2, O, true>::execute(x, y, o);
					x += 2;
					y += 2;
					o += 2;
				}
				OperationDispatcher<T, remainder_2, O>::execute(x, y, o);
			} else {
				OperationImplementation<T, S, O, false>::execute(x, y, o);
			}
		}

		template<size_t P = 1>
		static void ANVIL_SIMD_CALL execute(const T* x, T* o) {
			if (S >= 64 && info::instruction_set_64 != IS_NONE && IsInstructionSetSupported<static_cast<InstructionSet>(info::instruction_set_64)>()) {
				for (size_t i = 0; i < loop_64; ++i) {
					OperationImplementation<T, 64, O, false>::execute(x, o);
					x += 64;
					o += 64;
				}
				OperationDispatcher<T, remainder_64, O>::execute(x, o);
			} else if (S >= 32 && info::instruction_set_32 != IS_NONE && IsInstructionSetSupported<static_cast<InstructionSet>(info::instruction_set_32)>()) {
				for (size_t i = 0; i < loop_32; ++i) {
					OperationImplementation<T, 32, O, true>::execute(x, o);
					x += 32;
					o += 32;
				}
				OperationDispatcher<T, remainder_32, O>::execute(x, o);
			} else if (S >= 16 && info::instruction_set_16 != IS_NONE && IsInstructionSetSupported<static_cast<InstructionSet>(info::instruction_set_16)>()) {
				for (size_t i = 0; i < loop_16; ++i) {
					OperationImplementation<T, 16, O, true>::execute(x, o);
					x += 16;
					o += 16;
				}
				OperationDispatcher<T, remainder_16, O>::execute(x, o);
			} else if (S >= 8 && info::instruction_set_8 != IS_NONE && IsInstructionSetSupported<static_cast<InstructionSet>(info::instruction_set_8)>()) {
				for (size_t i = 0; i < loop_8; ++i) {
					OperationImplementation<T, 8, O, true>::execute(x, o);
					x += 8;
					o += 8;
				}
				OperationDispatcher<T, remainder_8, O>::execute(x, o);
			} else if (S >= 4 && info::instruction_set_4 != IS_NONE && IsInstructionSetSupported<static_cast<InstructionSet>(info::instruction_set_4)>()) {
				for (size_t i = 0; i < loop_4; ++i) {
					OperationImplementation<T, 4, O, true>::execute(x, o);
					x += 4;
					o += 4;
				}
				OperationImplementation<T, remainder_4, O, false>::execute(x, o);
			} else if (S >= 2 && info::instruction_set_2 != IS_NONE &&IsInstructionSetSupported<static_cast<InstructionSet>(info::instruction_set_2)>()) {
				for (size_t i = 0; i < loop_2; ++i) {
					OperationImplementation<T, 2, O, true>::execute(x, o);
					x += 2;
					o += 2;
				}
				OperationDispatcher<T, remainder_2, O>::execute(x, o);
			} else {
				OperationImplementation<T, S, O, false>::execute(x, o);
			}
		}
	};

#ifdef ANVIL_USE_INTEL_SIMD_INTRINSICS

#define ANVIL_SIMD_HELPER()\
	template<>\
	struct SIMDHelper<_simd_scalar, _simd_size> {\
		typedef _simd_type simd_t;\
		static ANVIL_STRONG_INLINE simd_t ANVIL_SIMD_CALL load(const _simd_scalar* x) { _simd_load(x); }\
		static ANVIL_STRONG_INLINE simd_t ANVIL_SIMD_CALL fillu() { return _simd_fillu(); }\
		static ANVIL_STRONG_INLINE simd_t ANVIL_SIMD_CALL fill0() { return _simd_fill0(); }\
		static ANVIL_STRONG_INLINE simd_t ANVIL_SIMD_CALL fill(const register _simd_scalar x) { return _simd_set1(x); }\
		static ANVIL_STRONG_INLINE simd_t ANVIL_SIMD_CALL set1(const register _simd_scalar x) { return set4(x, 0, 0, 0); }\
		static ANVIL_STRONG_INLINE simd_t ANVIL_SIMD_CALL set2(const register _simd_scalar x, const register _simd_scalar y) { return set4(x, y, 0, 0); }\
		static ANVIL_STRONG_INLINE simd_t ANVIL_SIMD_CALL set3(const register _simd_scalar x, const register _simd_scalar y, const register _simd_scalar z) { return set4(x, y, z, 0); }\
		static ANVIL_STRONG_INLINE simd_t ANVIL_SIMD_CALL set4(const register _simd_scalar x, const register _simd_scalar y, const register _simd_scalar z, const register _simd_scalar w) { return _simd_set4(x, y, z, w); }\
		\
		template<size_t GS>\
		static void ANVIL_SIMD_CALL get(const register simd_t x, _simd_scalar* y) {\
			typedef DefaultSIMD<_simd_scalar, GS> simd2_t;\
			union {\
				simd2_t s2;\
				simd_t s;\
			};\
			s = x;\
			*reinterpret_cast<simd2_t*>(y) = s2;\
		}\
		\
		template<size_t GS>\
		static ANVIL_STRONG_INLINE simd_t ANVIL_SIMD_CALL setn(const _simd_scalar* y) {\
			typedef DefaultSIMD<_simd_scalar, GS> simd2_t;\
			union {\
				simd2_t s2;\
				simd_t s;\
			};\
			s2 = *reinterpret_cast<const simd2_t*>(y);\
			return s;\
		}\
		\
		template<>\
		static ANVIL_STRONG_INLINE simd_t ANVIL_SIMD_CALL setn<_simd_size>(const _simd_scalar* y) {\
			return *reinterpret_cast<const simd_t*>(y);\
		}\
	};

#define _simd_scalar double
#define _simd_type __m256d
#define _simd_size 4
#define _simd_fillu() _mm256_undefined_pd()
#define _simd_fill0() _mm256_setzero_pd()
#define _simd_load(X) _mm256_load_pd(X)
#define _simd_set1(X) _mm256_set1_pd(X)
#define _simd_set4(X,Y,Z,W) _mm256_setr_pd(X,Y,Z,W)
ANVIL_SIMD_HELPER()
#undef _simd_scalar
#undef _simd_type
#undef _simd_size
#undef _simd_fillu
#undef _simd_fill0
#undef _simd_type
#undef _simd_load
#undef _simd_set1
#undef _simd_set4

#define _simd_scalar double
#define _simd_type __m128d
#define _simd_size 2
#define _simd_fillu() _mm_undefined_pd()
#define _simd_fill0() _mm_setzero_pd()
#define _simd_load(X) _mm_load_pd(X)
#define _simd_set1(X) _mm_set1_pd(X)
#define _simd_set4(X,Y,Z,W) _mm_setr_pd(X,Y)
ANVIL_SIMD_HELPER()
#undef _simd_scalar
#undef _simd_type
#undef _simd_size
#undef _simd_fillu
#undef _simd_fill0
#undef _simd_load
#undef _simd_set1
#undef _simd_set4

#define _simd_scalar float
#define _simd_type __m256
#define _simd_size 8
#define _simd_fillu() _mm256_undefined_ps()
#define _simd_fill0() _mm256_setzero_ps()
#define _simd_load(X) _mm256_load_ps(X)
#define _simd_set1(X) _mm256_set1_ps(X)
#define _simd_set4(X,Y,Z,W) _mm256_setr_ps(X,Y,Z,W,0.f,0.f,0.f,0.f)
ANVIL_SIMD_HELPER()
#undef _simd_scalar
#undef _simd_type
#undef _simd_size
#undef _simd_fillu
#undef _simd_fill0
#undef _simd_type
#undef _simd_load
#undef _simd_set1
#undef _simd_set4

#define _simd_scalar float
#define _simd_type __m128
#define _simd_size 4
#define _simd_fillu() _mm_undefined_ps()
#define _simd_fill0() _mm_setzero_ps()
#define _simd_load(X) _mm_load_ps(X)
#define _simd_set1(X) _mm_set1_ps(X)
#define _simd_set4(X,Y,Z,W) _mm_setr_ps(X,Y,Z,W)
ANVIL_SIMD_HELPER()
#undef _simd_scalar
#undef _simd_type
#undef _simd_size
#undef _simd_fillu
#undef _simd_fill0
#undef _simd_load
#undef _simd_set1
#undef _simd_set4

#define _simd_scalar int64_t
#define _simd_type __m256i
#define _simd_size 4
#define _simd_fillu() _mm256_undefined_si256()
#define _simd_fill0() _mm256_setzero_si256()
#define _simd_load(X) _mm256_load_si256(reinterpret_cast<const _simd_type*>(X))
#if ANVIL_CPP_VER < 2011
	#define _simd_set1(X) _simd_type() //! \todo Implement
#else
	#define _simd_set1(X) _mm256_set1_epi64x(X)
#endif
#define _simd_set4(X,Y,Z,W) _mm256_set_epi64x(X,Y,Z,W)
ANVIL_SIMD_HELPER()
#undef _simd_scalar
#define _simd_scalar uint64_t
ANVIL_SIMD_HELPER()
#undef _simd_scalar
#undef _simd_type
#undef _simd_size
#undef _simd_fillu
#undef _simd_fill0
#undef _simd_type
#undef _simd_load
#undef _simd_set1
#undef _simd_set4

#define _simd_scalar int64_t
#define _simd_type __m128i
#define _simd_size 2
#define _simd_fillu() _mm_undefined_si128()
#define _simd_fill0() _mm_setzero_si128()
#define _simd_load(X) _mm_load_si128(reinterpret_cast<const _simd_type*>(X))
#if ANVIL_CPP_VER < 2011
	#define _simd_set1(X) _simd_type() //! \todo Implement
#else
	#define _simd_set1(X) _mm_set1_epi64x(X)
#endif
#define _simd_set4(X,Y,Z,W) _mm_set_epi64x(X,Y)
	ANVIL_SIMD_HELPER()
#undef _simd_scalar
#define _simd_scalar uint64_t
	ANVIL_SIMD_HELPER()
#undef _simd_scalar
#undef _simd_type
#undef _simd_size
#undef _simd_fillu
#undef _simd_fill0
#undef _simd_type
#undef _simd_load
#undef _simd_set1
#undef _simd_set4

#define _simd_scalar int32_t
#define _simd_type __m256i
#define _simd_size 8
#define _simd_fillu() _mm256_undefined_si256()
#define _simd_fill0() _mm256_setzero_si256()
#define _simd_load(X) _mm256_load_si256(reinterpret_cast<const _simd_type*>(X))
#define _simd_set1(X) _mm256_set1_epi32(X)
#define _simd_set4(X,Y,Z,W) _mm256_set_epi32(X,Y,Z,W,0,0,0,0)
	ANVIL_SIMD_HELPER()
#undef _simd_scalar
#define _simd_scalar uint32_t
	ANVIL_SIMD_HELPER()
#undef _simd_scalar
#undef _simd_type
#undef _simd_size
#undef _simd_fillu
#undef _simd_fill0
#undef _simd_type
#undef _simd_load
#undef _simd_set1
#undef _simd_set4

#define _simd_scalar int32_t
#define _simd_type __m128i
#define _simd_size 4
#define _simd_fillu() _mm_undefined_si128()
#define _simd_fill0() _mm_setzero_si128()
#define _simd_load(X) _mm_load_si128(reinterpret_cast<const _simd_type*>(X))
#define _simd_set1(X) _mm_set1_epi32(X)
#define _simd_set4(X,Y,Z,W) _mm_set_epi32(X,Y,X,W)
	ANVIL_SIMD_HELPER()
#undef _simd_scalar
#define _simd_scalar uint32_t
	ANVIL_SIMD_HELPER()
#undef _simd_scalar
#undef _simd_type
#undef _simd_size
#undef _simd_fillu
#undef _simd_fill0
#undef _simd_type
#undef _simd_load
#undef _simd_set1
#undef _simd_set4

#define _simd_scalar int16_t
#define _simd_type __m256i
#define _simd_size 16
#define _simd_fillu() _mm256_undefined_si256()
#define _simd_fill0() _mm256_setzero_si256()
#define _simd_load(X) _mm256_load_si256(reinterpret_cast<const _simd_type*>(X))
#define _simd_set1(X) _mm256_set1_epi16(X)
#define _simd_set4(X,Y,Z,W) _mm256_set_epi16(X,Y,Z,W,0,0,0,0,0,0,0,0,0,0,0,0)
	ANVIL_SIMD_HELPER()
#undef _simd_scalar
#define _simd_scalar uint16_t
	ANVIL_SIMD_HELPER()
#undef _simd_scalar
#undef _simd_type
#undef _simd_size
#undef _simd_fillu
#undef _simd_fill0
#undef _simd_type
#undef _simd_load
#undef _simd_set1
#undef _simd_set4

#define _simd_scalar int16_t
#define _simd_type __m128i
#define _simd_size 8
#define _simd_fillu() _mm_undefined_si128()
#define _simd_fill0() _mm_setzero_si128()
#define _simd_load(X) _mm_load_si128(reinterpret_cast<const _simd_type*>(X))
#define _simd_set1(X) _mm_set1_epi16(X)
#define _simd_set4(X,Y,Z,W) _mm_set_epi16(X,Y,X,W,0,0,0,0)
	ANVIL_SIMD_HELPER()
#undef _simd_scalar
#define _simd_scalar uint16_t
	ANVIL_SIMD_HELPER()
#undef _simd_scalar
#undef _simd_type
#undef _simd_size
#undef _simd_fillu
#undef _simd_fill0
#undef _simd_type
#undef _simd_load
#undef _simd_set1
#undef _simd_set4

#define _simd_scalar int8_t
#define _simd_type __m256i
#define _simd_size 32
#define _simd_fillu() _mm256_undefined_si256()
#define _simd_fill0() _mm256_setzero_si256()
#define _simd_load(X) _mm256_load_si256(reinterpret_cast<const _simd_type*>(X))
#define _simd_set1(X) _mm256_set1_epi8(X)
#define _simd_set4(X,Y,Z,W) _mm256_set_epi8(X,Y,Z,W,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
		ANVIL_SIMD_HELPER()
#undef _simd_scalar
#define _simd_scalar uint8_t
		ANVIL_SIMD_HELPER()
#undef _simd_scalar
#undef _simd_type
#undef _simd_size
#undef _simd_fillu
#undef _simd_fill0
#undef _simd_type
#undef _simd_load
#undef _simd_set1
#undef _simd_set4

#define _simd_scalar int8_t
#define _simd_type __m128i
#define _simd_size 16
#define _simd_fillu() _mm_undefined_si128()
#define _simd_fill0() _mm_setzero_si128()
#define _simd_load(X) _mm_load_si128(reinterpret_cast<const _simd_type*>(X))
#define _simd_set1(X) _mm_set1_epi8(X)
#define _simd_set4(X,Y,Z,W) _mm_set_epi8(X,Y,X,W,0,0,0,0,0,0,0,0,0,0,0,0)
		ANVIL_SIMD_HELPER()
#undef _simd_scalar
#define _simd_scalar uint8_t
		ANVIL_SIMD_HELPER()
#undef _simd_scalar
#undef _simd_type
#undef _simd_size
#undef _simd_fillu
#undef _simd_fill0
#undef _simd_type
#undef _simd_load
#undef _simd_set1
#undef _simd_set4

#define ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,OP_SIZE,SIZE,INSTRUCTION,FUNCTION1)\
	template<>\
	struct OperationImplementation<_simd_element_type, SIZE, OP, true> {\
		typedef SIMDHelper<_simd_element_type,OP_SIZE> helper_t;\
		typedef helper_t::simd_t simd_t;\
		typedef DefaultSIMD<_simd_element_type,SIZE> default_simd_t;\
		static ANVIL_STRONG_INLINE bool ANVIL_SIMD_CALL optimised() {\
			return IsInstructionSetSupported< IS_ ## INSTRUCTION >();\
		}\
		static ANVIL_STRONG_INLINE _simd_type ANVIL_SIMD_CALL execute(const register simd_t x, const register simd_t y) {\
			return FUNCTION1(x,y);\
		}\
		static ANVIL_STRONG_INLINE void ANVIL_SIMD_CALL execute(const register _simd_element_type* x, const register _simd_element_type* y, _simd_element_type* o) {\
			helper_t::get<SIZE>(execute(helper_t::setn<SIZE>(x),helper_t::setn<SIZE>(y)),o);\
		}\
	};

#define ANVIL_SIMD_IMPLEMENTATION_V_V(OP,OP_SIZE,SIZE,INSTRUCTION,FUNCTION1)\
	template<>\
	struct OperationImplementation<_simd_element_type, SIZE, OP, true> {\
		typedef SIMDHelper<_simd_element_type,OP_SIZE> helper_t;\
		typedef helper_t::simd_t simd_t;\
		static ANVIL_STRONG_INLINE bool ANVIL_SIMD_CALL optimised() {\
			return IsInstructionSetSupported< IS_ ## INSTRUCTION >();\
		}\
		static ANVIL_STRONG_INLINE _simd_type ANVIL_SIMD_CALL execute(const register simd_t x) {\
			return FUNCTION1(x);\
		}\
		static ANVIL_STRONG_INLINE void ANVIL_SIMD_CALL execute(const register _simd_element_type* x, _simd_element_type* o) {\
			helper_t::get<SIZE>(execute(helper_t::setn<SIZE>(x)),o);\
		}\
	};

#define ANVIL_SIMD_SPECIALISE_FILL(OP_SIZE,SIZE,INSTRUCTION)\
	template<>\
	struct OperationImplementation<_simd_element_type, SIZE, OP_FILL, true> {\
		typedef SIMDHelper<_simd_element_type,OP_SIZE> helper_t;\
		static ANVIL_STRONG_INLINE void ANVIL_SIMD_CALL execute(_simd_element_type* o) {\
			helper_t::get<SIZE>(helper_t::fill0(), o);\
		}\
		\
		static ANVIL_STRONG_INLINE void ANVIL_SIMD_CALL execute(const register _simd_element_type x, _simd_element_type* o) {\
			helper_t::get<SIZE>(helper_t::fill(x), o);\
		}\
		\
		static ANVIL_STRONG_INLINE void ANVIL_SIMD_CALL execute(const register _simd_element_type x, const register _simd_element_type y, _simd_element_type* o) {\
			helper_t::get<SIZE>(helper_t::set2(x,y), o);\
		}\
		\
		static ANVIL_STRONG_INLINE void ANVIL_SIMD_CALL execute(const register _simd_element_type x, const register _simd_element_type y, const register _simd_element_type z, _simd_element_type* o) {\
			helper_t::get<SIZE>(helper_t::set3(x,y,z), o);\
		}\
		\
		static ANVIL_STRONG_INLINE void ANVIL_SIMD_CALL execute(const register _simd_element_type x, const register _simd_element_type y, const register _simd_element_type z, const register _simd_element_type w, _simd_element_type* o) {\
			helper_t::get<SIZE>(helper_t::set4(x,y,z,w), o);\
		}\
	};

#define ANVIL_SIMD_IMPLEMENTATION_V_VV_16_TO_32(OP,INSTRUCTION, FUNCTION1)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP, _simd_element_type, 32> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
	};}\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,32,32,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,32,31,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,32,30,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,32,29,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,32,28,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,32,27,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,32,26,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,32,25, INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,32,24, INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,32,23, INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,32,22, INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,32,21, INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,32,20, INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,32,19,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,32,18,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,32,17,INSTRUCTION, FUNCTION1)

#define ANVIL_SIMD_IMPLEMENTATION_V_VV_8_TO_16(OP,INSTRUCTION, FUNCTION1)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP, _simd_element_type, 16> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
	};}\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,16,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,15,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,14,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,13,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,12,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,11,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,10,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,9, INSTRUCTION, FUNCTION1)

#define ANVIL_SIMD_IMPLEMENTATION_V_VV_4_TO_8(OP,INSTRUCTION, FUNCTION1)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP, _simd_element_type, 8> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
		};}\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,8,8,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,8,7,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,8,6,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,8,5,INSTRUCTION, FUNCTION1)

#define ANVIL_SIMD_IMPLEMENTATION_V_VV_2_TO_4(OP,INSTRUCTION, FUNCTION1)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP, _simd_element_type, 4> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
				};}\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,4,4,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,4,3,INSTRUCTION, FUNCTION1)



#define ANVIL_SIMD_IMPLEMENTATION_V_V_16_TO_32(OP,INSTRUCTION, FUNCTION1)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP, _simd_element_type, 32> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
	};}\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,32,32,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,32,31,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,32,30,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,32,29,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,32,28,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,32,27,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,32,26,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,32,25, INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,32,24, INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,32,23, INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,32,22, INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,32,21, INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,32,20, INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,32,19,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,32,18,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,32,17,INSTRUCTION, FUNCTION1)

#define ANVIL_SIMD_IMPLEMENTATION_V_V_8_TO_16(OP,INSTRUCTION, FUNCTION1)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP, _simd_element_type, 16> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
	};}\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,16,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,15,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,14,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,13,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,12,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,11,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,10,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,9, INSTRUCTION, FUNCTION1)

#define ANVIL_SIMD_IMPLEMENTATION_V_V_4_TO_8(OP,INSTRUCTION, FUNCTION1)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP, _simd_element_type, 8> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
	};}\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,8,8,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,8,7,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,8,6,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,8,5,INSTRUCTION, FUNCTION1)

#define ANVIL_SIMD_IMPLEMENTATION_V_V_2_TO_4(OP,INSTRUCTION, FUNCTION1)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP, _simd_element_type, 4> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
	};}\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,4,4,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,4,3,INSTRUCTION, FUNCTION1)

#define ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP,INSTRUCTION, FUNCTION1)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP, _simd_element_type, 16> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
	};}\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,16,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,15,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,14,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,13,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,12,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,11,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,10,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,9, INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,8, INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,7, INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,6, INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,5, INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,4, INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,3, INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,2, INSTRUCTION, FUNCTION1)

#define ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP,INSTRUCTION, FUNCTION1)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP, _simd_element_type, 8> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
	};}\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,8,8,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,8,7,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,8,6,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,8,5,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,8,4,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,8,3,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,8,2,INSTRUCTION, FUNCTION1)

#define ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP,INSTRUCTION, FUNCTION1)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP, _simd_element_type, 4> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
	};}\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,4,4,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,4,3,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,4,2,INSTRUCTION, FUNCTION1)

#define ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP,INSTRUCTION, FUNCTION1)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP, _simd_element_type, 2> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
	};}\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,2,2,INSTRUCTION, FUNCTION1)

#define ANVIL_SIMD_IMPLEMENTATION_V_V_16(OP,INSTRUCTION, FUNCTION1)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP, _simd_element_type, 16> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
	};}\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,16,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,15,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,14,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,13,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,12,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,11,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,10,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,9, INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,8, INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,7, INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,6, INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,5, INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,4, INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,3, INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,2, INSTRUCTION, FUNCTION1)

#define ANVIL_SIMD_IMPLEMENTATION_V_V_8(OP,INSTRUCTION, FUNCTION1)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP, _simd_element_type, 8> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
	};}\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,8,8,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,8,7,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,8,6,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,8,5,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,8,4,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,8,3,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,8,2,INSTRUCTION, FUNCTION1)

#define ANVIL_SIMD_IMPLEMENTATION_V_V_4(OP,INSTRUCTION, FUNCTION1)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP, _simd_element_type, 4> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
	};}\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,4,4,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,4,3,INSTRUCTION, FUNCTION1)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,4,2,INSTRUCTION, FUNCTION1)

#define ANVIL_SIMD_IMPLEMENTATION_V_V_2(OP,INSTRUCTION, FUNCTION1)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP, _simd_element_type, 2> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
	};}\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,2,2,INSTRUCTION, FUNCTION1)

#define ANVIL_SIMD_SPECIALISE_FILL_16(INSTRUCTION)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP_FILL, _simd_element_type, 16> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
	};}\
	ANVIL_SIMD_SPECIALISE_FILL(16,16, INSTRUCTION)\
	ANVIL_SIMD_SPECIALISE_FILL(16,15, INSTRUCTION)\
	ANVIL_SIMD_SPECIALISE_FILL(16,14, INSTRUCTION)\
	ANVIL_SIMD_SPECIALISE_FILL(16,13, INSTRUCTION)\
	ANVIL_SIMD_SPECIALISE_FILL(16,12, INSTRUCTION)\
	ANVIL_SIMD_SPECIALISE_FILL(16,11, INSTRUCTION)\
	ANVIL_SIMD_SPECIALISE_FILL(16,10, INSTRUCTION)\
	ANVIL_SIMD_SPECIALISE_FILL(16,9, INSTRUCTION)\
	ANVIL_SIMD_SPECIALISE_FILL(16,8, INSTRUCTION)\
	ANVIL_SIMD_SPECIALISE_FILL(16,7, INSTRUCTION)\
	ANVIL_SIMD_SPECIALISE_FILL(16,6, INSTRUCTION)\
	ANVIL_SIMD_SPECIALISE_FILL(16,5, INSTRUCTION)\
	ANVIL_SIMD_SPECIALISE_FILL(16,4, INSTRUCTION)\
	ANVIL_SIMD_SPECIALISE_FILL(16,3, INSTRUCTION)\
	ANVIL_SIMD_SPECIALISE_FILL(16,2, INSTRUCTION)

#define ANVIL_SIMD_SPECIALISE_FILL_8(INSTRUCTION)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP_FILL, _simd_element_type, 8> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
	};}\
	ANVIL_SIMD_SPECIALISE_FILL(8,8, INSTRUCTION)\
	ANVIL_SIMD_SPECIALISE_FILL(8,7, INSTRUCTION)\
	ANVIL_SIMD_SPECIALISE_FILL(8,6, INSTRUCTION)\
	ANVIL_SIMD_SPECIALISE_FILL(8,5, INSTRUCTION)\
	ANVIL_SIMD_SPECIALISE_FILL(8,4, INSTRUCTION)\
	ANVIL_SIMD_SPECIALISE_FILL(8,3, INSTRUCTION)\
	ANVIL_SIMD_SPECIALISE_FILL(8,2, INSTRUCTION)

#define ANVIL_SIMD_SPECIALISE_FILL_4(INSTRUCTION)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP_FILL, _simd_element_type, 8> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
	};}\
	ANVIL_SIMD_SPECIALISE_FILL(4,4, INSTRUCTION)\
	ANVIL_SIMD_SPECIALISE_FILL(4,3, INSTRUCTION)\
	ANVIL_SIMD_SPECIALISE_FILL(4,2, INSTRUCTION)

#define ANVIL_SIMD_SPECIALISE_FILL_2(INSTRUCTION)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP_FILL, _simd_element_type, 2> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
	};}\
	ANVIL_SIMD_SPECIALISE_FILL(2,2, SSE)

#define _simd_round_ps(X) _mm_round_ps(X,_MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC)
#define _simd_round_pd(X) _mm_round_pd(X,_MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC)
#define _simd256_round_ps(X) _mm256_round_ps(X,_MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC)
#define _simd256_round_pd(X) _mm256_round_pd(X,_MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC)
#define _simd256_cmpeq_ps(X,Y) _mm256_cmp_ps (X,Y,_CMP_EQ_OQ)
#define _simd256_cmpneq_ps(X,Y) _mm256_cmp_ps (X,Y,_CMP_NEQ_OQ)
#define _simd256_cmplt_ps(X,Y) _mm256_cmp_ps (X,Y,_CMP_LT_OQ)
#define _simd256_cmpgt_ps(X,Y) _mm256_cmp_ps (X,Y,_CMP_GT_OQ)
#define _simd256_cmple_ps(X,Y) _mm256_cmp_ps (X,Y,_CMP_LE_OQ)
#define _simd256_cmpge_ps(X,Y) _mm256_cmp_ps (X,Y,_CMP_GE_OQ)
#define _simd256_cmpeq_pd(X,Y) _mm256_cmp_pd (X,Y,_CMP_EQ_OQ)
#define _simd256_cmpneq_pd(X,Y) _mm256_cmp_pd (X,Y,_CMP_NEQ_OQ)
#define _simd256_cmplt_pd(X,Y) _mm256_cmp_pd (X,Y,_CMP_LT_OQ)
#define _simd256_cmpgt_pd(X,Y) _mm256_cmp_pd (X,Y,_CMP_GT_OQ)
#define _simd256_cmple_pd(X,Y) _mm256_cmp_pd (X,Y,_CMP_LE_OQ)
#define _simd256_cmpge_pd(X,Y) _mm256_cmp_pd (X,Y,_CMP_GE_OQ)

#define _simd_element_type float
#define _simd_type __m128
	ANVIL_SIMD_SPECIALISE_FILL_4(SSE)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_ADD,   SSE,     _mm_add_ps)    
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_SUB,   SSE,     _mm_sub_ps)     
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_MUL,   SSE,     _mm_mul_ps)     
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_DIV,   SSE,     _mm_div_ps)     
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_AND,   SSE,     _mm_and_ps)     
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_OR,    SSE,     _mm_or_ps)      
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_XOR,   SSE,     _mm_xor_ps)     
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_MIN,   SSE,     _mm_min_ps)     
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_MAX,   SSE,     _mm_max_ps)     
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_CMPEQ, SSE,     _mm_cmpeq_ps)   
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_CMPNE, SSE,     _mm_cmpneq_ps)  
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_CMPLT, SSE,     _mm_cmplt_ps)   
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_CMPGT, SSE,     _mm_cmpgt_ps)   
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_CMPLE, SSE,     _mm_cmple_ps)   
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_CMPGE, SSE,     _mm_cmpge_ps)   
	ANVIL_SIMD_IMPLEMENTATION_V_V_4( OP_CEIL,  SSE_4_1, _mm_ceil_ps)    
	ANVIL_SIMD_IMPLEMENTATION_V_V_4( OP_FLOOR, SSE_4_1, _mm_floor_ps)   
	ANVIL_SIMD_IMPLEMENTATION_V_V_4( OP_ROUND, SSE_4_1, _simd_round_ps) 
	ANVIL_SIMD_IMPLEMENTATION_V_V_4( OP_SQRT,  SSE,     _mm_sqrt_ps)    
#undef _simd_element_type
#undef _simd_type

#define _simd_element_type float
#define _simd_type __m256
	//ANVIL_SIMD_SPECIALISE_FILL_4(SSE)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4_TO_8(OP_ADD,   AVX, _mm256_add_ps)     
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4_TO_8(OP_SUB,   AVX, _mm256_sub_ps)     
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4_TO_8(OP_MUL,   AVX, _mm256_mul_ps)     
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4_TO_8(OP_DIV,   AVX, _mm256_div_ps)     
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4_TO_8(OP_AND,   AVX, _mm256_and_ps)     
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4_TO_8(OP_OR,    AVX, _mm256_or_ps)      
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4_TO_8(OP_XOR,   AVX, _mm256_xor_ps)     
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4_TO_8(OP_MIN,   AVX, _mm256_min_ps)     
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4_TO_8(OP_MAX,   AVX, _mm256_max_ps)     
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4_TO_8(OP_CMPEQ, AVX, _simd256_cmpeq_ps) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4_TO_8(OP_CMPNE, AVX, _simd256_cmpneq_ps)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4_TO_8(OP_CMPLT, AVX, _simd256_cmplt_ps) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4_TO_8(OP_CMPGT, AVX, _simd256_cmpgt_ps) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4_TO_8(OP_CMPLE, AVX, _simd256_cmple_ps) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4_TO_8(OP_CMPGE, AVX, _simd256_cmpge_ps) 
	ANVIL_SIMD_IMPLEMENTATION_V_V_4_TO_8( OP_CEIL,  AVX, _mm256_ceil_ps)    
	ANVIL_SIMD_IMPLEMENTATION_V_V_4_TO_8( OP_FLOOR, AVX, _mm256_floor_ps)   
	ANVIL_SIMD_IMPLEMENTATION_V_V_4_TO_8( OP_ROUND, AVX, _simd256_round_ps) 
	ANVIL_SIMD_IMPLEMENTATION_V_V_4_TO_8( OP_SQRT,  AVX, _mm256_sqrt_ps)    
#undef _simd_element_type
#undef _simd_type

#define _simd_element_type double
#define _simd_type __m128d
	ANVIL_SIMD_SPECIALISE_FILL_2(SSE_2)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_ADD,   SSE_2,   _mm_add_pd)     
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_SUB,   SSE_2,   _mm_sub_pd)     
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_MUL,   SSE_2,   _mm_mul_pd)     
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_DIV,   SSE_2,   _mm_div_pd)     
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_AND,   SSE_2,   _mm_and_pd)     
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_OR,    SSE_2,   _mm_or_pd)      
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_XOR,   SSE_2,   _mm_xor_pd)     
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_MIN,   SSE_2,   _mm_min_pd)     
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_MAX,   SSE_2,   _mm_max_pd)     
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_CMPEQ, SSE_2,   _mm_cmpeq_pd)   
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_CMPNE, SSE_2,   _mm_cmpneq_pd)  
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_CMPLT, SSE_2,   _mm_cmplt_pd)   
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_CMPGT, SSE_2,   _mm_cmpgt_pd)   
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_CMPLE, SSE_2,   _mm_cmple_pd)   
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_CMPGE, SSE_2,   _mm_cmpge_pd)   
	ANVIL_SIMD_IMPLEMENTATION_V_V_2( OP_CEIL,  SSE_4_1, _mm_ceil_pd)    
	ANVIL_SIMD_IMPLEMENTATION_V_V_2( OP_FLOOR, SSE_4_1, _mm_floor_pd)   
	ANVIL_SIMD_IMPLEMENTATION_V_V_2( OP_ROUND, SSE_4_1, _simd_round_pd) 
	ANVIL_SIMD_IMPLEMENTATION_V_V_2( OP_SQRT,  SSE_2,   _mm_sqrt_pd)    
#undef _simd_element_type
#undef _simd_type

#define _simd_element_type double
#define _simd_type __m256d
	//ANVIL_SIMD_SPECIALISE_FILL_4(SSE)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2_TO_4(OP_ADD,   AVX, _mm256_add_pd)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2_TO_4(OP_SUB,   AVX, _mm256_sub_pd)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2_TO_4(OP_MUL,   AVX, _mm256_mul_pd)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2_TO_4(OP_DIV,   AVX, _mm256_div_pd)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2_TO_4(OP_AND,   AVX, _mm256_and_pd)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2_TO_4(OP_OR,    AVX, _mm256_or_pd) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2_TO_4(OP_XOR,   AVX, _mm256_xor_pd)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2_TO_4(OP_MIN,   AVX, _mm256_min_pd)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2_TO_4(OP_MAX,   AVX, _mm256_max_pd)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2_TO_4(OP_CMPEQ, AVX, _simd256_cmpeq_pd)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2_TO_4(OP_CMPNE, AVX, _simd256_cmpneq_pd)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2_TO_4(OP_CMPLT, AVX, _simd256_cmplt_pd) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2_TO_4(OP_CMPGT, AVX, _simd256_cmpgt_pd) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2_TO_4(OP_CMPLE, AVX, _simd256_cmple_pd) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2_TO_4(OP_CMPGE, AVX, _simd256_cmpge_pd) 
	ANVIL_SIMD_IMPLEMENTATION_V_V_2_TO_4(OP_CEIL,   AVX, _mm256_ceil_pd)
	ANVIL_SIMD_IMPLEMENTATION_V_V_2_TO_4(OP_FLOOR,  AVX, _mm256_floor_pd)
	ANVIL_SIMD_IMPLEMENTATION_V_V_2_TO_4(OP_ROUND,  AVX, _simd256_round_pd)
	ANVIL_SIMD_IMPLEMENTATION_V_V_2_TO_4(OP_SQRT,   AVX, _mm256_sqrt_pd)
#undef _simd_element_type
#undef _simd_type

#define _simd_element_type int64_t
#define _simd_type __m128i
	ANVIL_SIMD_SPECIALISE_FILL_2(SSE_2)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_ADD, SSE_2, _mm_add_epi64)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_SUB, SSE_2, _mm_sub_epi64)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_AND, SSE_2, _mm_and_si128)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_OR,  SSE_2, _mm_or_si128) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_XOR, SSE_2, _mm_xor_si128)
#undef _simd_element_type
#undef _simd_type

#define _simd_element_type int64_t
#define _simd_type __m256i
	//ANVIL_SIMD_SPECIALISE_FILL_2(SSE_2)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2_TO_4(OP_ADD, AVX_2, _mm256_add_epi64)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2_TO_4(OP_SUB, AVX,   _mm256_sub_epi64)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2_TO_4(OP_AND, AVX,   _mm256_and_si256)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2_TO_4(OP_OR,  AVX,   _mm256_or_si256) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2_TO_4(OP_XOR, AVX,   _mm256_xor_si256)
	ANVIL_SIMD_IMPLEMENTATION_V_V_2_TO_4( OP_ABS, AVX_2, _mm256_abs_epi32)
#undef _simd_element_type
#undef _simd_type

#define _simd_element_type uint64_t
#define _simd_type __m128i
	ANVIL_SIMD_SPECIALISE_FILL_2(SSE_2)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_AND, SSE_2, _mm_and_si128)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_OR,  SSE_2, _mm_or_si128) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_XOR, SSE_2, _mm_xor_si128)
#undef _simd_element_type
#undef _simd_type

#define _simd_element_type uint64_t
#define _simd_type __m256i
	//ANVIL_SIMD_SPECIALISE_FILL_2(SSE_2)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2_TO_4(OP_AND, AVX, _mm256_and_si256)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2_TO_4(OP_OR,  AVX, _mm256_or_si256) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2_TO_4(OP_XOR, AVX, _mm256_xor_si256)
#undef _simd_element_type
#undef _simd_type

#define _simd_element_type int32_t
#define _simd_type __m128i
	ANVIL_SIMD_SPECIALISE_FILL_4(SSE_2)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_ADD,   SSE_2,   _mm_add_epi32)  
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_SUB,   SSE_2,   _mm_sub_epi32)  
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_MUL,   SSE_4_1, _mm_mullo_epi32)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_AND,   SSE_2,   _mm_and_si128)  
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_OR,    SSE_2,   _mm_or_si128)   
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_XOR,   SSE_2,   _mm_xor_si128)  
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_MIN,   SSE_4_1, _mm_min_epi32)  
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_MAX,   SSE_4_1, _mm_max_epi32)  
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_CMPEQ, SSE_2,   _mm_cmpeq_epi32)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_CMPLT, SSE_2,   _mm_cmplt_epi32)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_CMPGT, SSE_2,   _mm_cmpgt_epi32)
	ANVIL_SIMD_IMPLEMENTATION_V_V_4( OP_ABS,   SSSE_3,  _mm_abs_epi32)  
#undef _simd_element_type
#undef _simd_type

#define _simd_element_type int32_t
#define _simd_type __m256i
	//ANVIL_SIMD_SPECIALISE_FILL_4(SSE_2)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4_TO_8(OP_ADD,   AVX_2, _mm256_add_epi32) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4_TO_8(OP_SUB,   AVX,   _mm256_sub_epi32) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4_TO_8(OP_AND,   AVX,   _mm256_and_si256) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4_TO_8(OP_OR,    AVX,   _mm256_or_si256)  
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4_TO_8(OP_XOR,   AVX,   _mm256_xor_si256) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4_TO_8(OP_MIN,   AVX_2, _mm256_min_epi32) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4_TO_8(OP_MAX,   AVX_2, _mm256_max_epi32) 
	ANVIL_SIMD_IMPLEMENTATION_V_V_4_TO_8( OP_ABS,   AVX_2, _mm256_abs_epi32) 
#undef _simd_element_type
#undef _simd_type

#define _simd_element_type uint32_t
#define _simd_type __m128i
	ANVIL_SIMD_SPECIALISE_FILL_4(SSE_2)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_AND, SSE_2,   _mm_and_si128) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_OR,  SSE_2,   _mm_or_si128)  
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_XOR, SSE_2,   _mm_xor_si128) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_MIN, SSE_4_1, _mm_min_epu32) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_MAX, SSE_4_1, _mm_max_epu32) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_CMPEQ, SSE_2, _mm_cmpeq_epi32)
#undef _simd_element_type
#undef _simd_type

#define _simd_element_type uint32_t
#define _simd_type __m256i
	//ANVIL_SIMD_SPECIALISE_FILL_4(SSE_2)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4_TO_8(OP_AND,   AVX,   _mm256_and_si256)  
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4_TO_8(OP_OR,    AVX,   _mm256_or_si256)   
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4_TO_8(OP_XOR,   AVX,   _mm256_xor_si256)  
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4_TO_8(OP_MIN,   AVX_2, _mm256_min_epu32)  
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4_TO_8(OP_MAX,   AVX_2, _mm256_max_epu32)  
#undef _simd_element_type
#undef _simd_type

#define _simd_element_type int16_t
#define _simd_type __m128i
	ANVIL_SIMD_SPECIALISE_FILL_8(SSE_2)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_ADD, SSE_2,   _mm_add_epi16)   
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_SUB, SSE_2,   _mm_sub_epi16)   
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_MUL, SSE_2,   _mm_mullo_epi16) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_AND, SSE_2,   _mm_and_si128)   
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_OR,  SSE_2,   _mm_or_si128)    
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_XOR, SSE_2,   _mm_xor_si128)   
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_MAX, SSE_2,   _mm_max_epi16)   
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_MIN, SSE_2,   _mm_min_epi16)   
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_CMPEQ, SSE_2, _mm_cmpeq_epi16) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_CMPLT, SSE_2, _mm_cmplt_epi16) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_CMPGT, SSE_2, _mm_cmpgt_epi16) 
	ANVIL_SIMD_IMPLEMENTATION_V_V_8( OP_ABS, SSSE_3,  _mm_abs_epi16)   
#undef _simd_element_type
#undef _simd_type

#define _simd_element_type int16_t
#define _simd_type __m256i
	//ANVIL_SIMD_SPECIALISE_FILL_8(SSE_2)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8_TO_16(OP_ADD,   AVX_2, _mm256_add_epi16) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8_TO_16(OP_SUB,   AVX_2, _mm256_sub_epi16) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8_TO_16(OP_MUL,   AVX_2, _mm256_mullo_epi16)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8_TO_16(OP_AND,   AVX,   _mm256_and_si256) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8_TO_16(OP_OR,    AVX,   _mm256_or_si256)  
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8_TO_16(OP_XOR,   AVX,   _mm256_xor_si256) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8_TO_16(OP_MAX,   AVX_2, _mm256_max_epi16) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8_TO_16(OP_MIN,   AVX_2, _mm256_min_epi16) 
	ANVIL_SIMD_IMPLEMENTATION_V_V_8_TO_16( OP_ABS,   AVX_2, _mm256_abs_epi16) 
#undef _simd_element_type
#undef _simd_type

#define _simd_element_type uint16_t
#define _simd_type __m128i
	ANVIL_SIMD_SPECIALISE_FILL_8(SSE_2)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_ADD,   SSE_2,   _mm_adds_epu16) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_SUB,   SSE_2,   _mm_subs_epu16) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_AND,   SSE_2,   _mm_and_si128)  
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_OR,    SSE_2,   _mm_or_si128)   
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_XOR,   SSE_2,   _mm_xor_si128)  
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_CMPEQ, SSE_2,   _mm_cmpeq_epi16)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_MIN,   SSE_4_1, _mm_min_epu16)  
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_MAX,   SSE_4_1, _mm_max_epu16)  
#undef _simd_element_type
#undef _simd_type

#define _simd_element_type uint16_t
#define _simd_type __m256i
	//ANVIL_SIMD_SPECIALISE_FILL_8(SSE_2)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8_TO_16(OP_ADD,   AVX_2, _mm256_adds_epu16)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8_TO_16(OP_SUB,   AVX_2, _mm256_subs_epu16)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8_TO_16(OP_AND,   AVX,   _mm256_and_si256) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8_TO_16(OP_OR,    AVX,   _mm256_or_si256)  
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8_TO_16(OP_XOR,   AVX,   _mm256_xor_si256) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8_TO_16(OP_MAX,   AVX_2, _mm256_max_epu16) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8_TO_16(OP_MIN,   AVX_2, _mm256_min_epu16) 
#undef _simd_element_type
#undef _simd_type

#define _simd_element_type int8_t
#define _simd_type __m128i
	ANVIL_SIMD_SPECIALISE_FILL_16(SSE_2)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_ADD,   SSE_2,   _mm_adds_epi8)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_SUB,   SSE_2,   _mm_subs_epi8) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_AND,   SSE_2,   _mm_and_si128) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_OR,    SSE_2,   _mm_or_si128)  
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_XOR,   SSE_2,   _mm_xor_si128) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_MIN,   SSE_4_1, _mm_min_epi8)  
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_MAX,   SSE_4_1, _mm_max_epi8)  
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_CMPEQ, SSE_2,   _mm_cmpeq_epi8)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_CMPLT, SSE_2,   _mm_cmplt_epi8)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_CMPGT, SSE_2,   _mm_cmpgt_epi8)
	ANVIL_SIMD_IMPLEMENTATION_V_V_16( OP_ABS,   SSSE_3,  _mm_abs_epi8)  
#undef _simd_element_type
#undef _simd_type

#define _simd_element_type int8_t
#define _simd_type __m256i
	//ANVIL_SIMD_SPECIALISE_FILL_16(SSE_2)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16_TO_32(OP_ADD, AVX_2, _mm256_adds_epi8)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16_TO_32(OP_SUB, AVX_2, _mm256_subs_epi8)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16_TO_32(OP_AND, AVX,   _mm256_and_si256)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16_TO_32(OP_OR,  AVX,   _mm256_or_si256) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16_TO_32(OP_XOR, AVX,   _mm256_xor_si256)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16_TO_32(OP_MIN, AVX_2, _mm256_min_epi8) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16_TO_32(OP_MAX, AVX_2, _mm256_max_epi8)  
	ANVIL_SIMD_IMPLEMENTATION_V_V_16_TO_32(OP_ABS,  AVX_2, _mm256_abs_epi8)  
#undef _simd_element_type
#undef _simd_type

#define _simd_element_type uint8_t
#define _simd_type __m128i
	ANVIL_SIMD_SPECIALISE_FILL_16(SSE_2)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_ADD,   SSE_2, _mm_adds_epu8)  
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_SUB,   SSE_2, _mm_subs_epu8)  
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_AND,   SSE_2, _mm_and_si128)  
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_OR,    SSE_2, _mm_or_si128)   
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_XOR,   SSE_2, _mm_xor_si128)  
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_CMPEQ, SSE_2, _mm_cmpeq_epi8) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_MAX,   SSE_2, _mm_max_epu8)   
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_MIN,   SSE_2, _mm_min_epu8)   
#undef _simd_element_type
#undef _simd_type

#define _simd_element_type uint8_t
#define _simd_type __m256i
	//ANVIL_SIMD_SPECIALISE_FILL_16(SSE_2)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16_TO_32(OP_ADD, AVX_2, _mm256_adds_epu8) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16_TO_32(OP_SUB, AVX_2, _mm256_subs_epu8) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16_TO_32(OP_AND, AVX,   _mm256_and_si256) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16_TO_32(OP_OR,  AVX,   _mm256_or_si256)  
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16_TO_32(OP_XOR, AVX,   _mm256_xor_si256) 
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16_TO_32(OP_MIN, AVX_2, _mm256_min_epu8)  
	ANVIL_SIMD_IMPLEMENTATION_V_VV_16_TO_32(OP_MAX, AVX_2, _mm256_max_epu8)  
#undef _simd_element_type
#undef _simd_type

#endif
}}

#endif