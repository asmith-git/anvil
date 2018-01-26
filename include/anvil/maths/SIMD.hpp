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
#endif

namespace anvil { namespace simd {

	// Instruction set definitions

	enum InstructionSet : int16_t {
		IS_NONE,
#ifdef ANVIL_USE_INTEL_SIMD_INTRINSICS
		IS_MMX     = 1 << 0,
		IS_SSE     = 1 << 1,
		IS_SSE_2   = 1 << 2,
		IS_SSE_3   = 1 << 3,
		IS_SSSE_3  = 1 << 4,
		IS_SSE_4_1 = 1 << 5,
		IS_SSE_4_2 = 1 << 6,
		IS_AVX     = 1 << 7,
		IS_FMA     = 1 << 8,
		IS_AVX_2   = 1 << 9,
		IS_KNC     = 1 << 10,
		IS_AVX_512 = 1 << 11,
#endif
	};

	static bool ANVIL_CALL IsInstructionSetSupported_(InstructionSet aSet) {
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
		switch (aSet) {
		case IS_MMX:
			return data[0][EDX_] & (1 << 23);
		case IS_SSE:
			return data[0][EDX_] & (1 << 25);
		case IS_SSE_2:
			return data[0][EDX_] & (1 << 26);
		case IS_SSE_3:
			return data[0][ECX_] & (1 << 0);
		case IS_SSSE_3:
			return data[0][ECX_] & (1 << 9);
		case IS_SSE_4_1:
			return data[0][ECX_] & (1 << 19);
		case IS_SSE_4_2:
			return data[0][ECX_] & (1 << 20);
		case IS_AVX:
			return data[0][ECX_] & (1 << 28);
		case IS_FMA:
			return data[0][ECX_] & (1 << 12);
		case IS_AVX_2:
			return data[1][EBX_] & (1 << 5);
		case IS_KNC:
			return false; //! \todo Implement
		case IS_AVX_512:
			return (data[1][EBX_] & (1 << 16)) && (data[1][EBX_] & (1 << 26)) && (data[1][EBX_] & (1 << 27)) && (data[1][EBX_] & (1 << 28));
		}
#else
		return false;
#endif
	}


	static ANVIL_STRONG_INLINE bool ANVIL_CALL IsInstructionSetSupported(InstructionSet aSet) {
		static const bool g_enabled_sets =
#ifdef ANVIL_USE_INTEL_SIMD_INTRINSICS
			(IsInstructionSetSupported_(IS_MMX) ? IS_MMX : 0) |
			(IsInstructionSetSupported_(IS_SSE) ? IS_SSE : 0) |
			(IsInstructionSetSupported_(IS_SSE_2) ? IS_SSE_2 : 0) |
			(IsInstructionSetSupported_(IS_SSE_3) ? IS_SSE_3 : 0) |
			(IsInstructionSetSupported_(IS_SSSE_3) ? IS_SSSE_3 : 0) |
			(IsInstructionSetSupported_(IS_SSE_4_1) ? IS_SSE_4_1 : 0) |
			(IsInstructionSetSupported_(IS_SSE_4_2) ? IS_SSE_4_2 : 0) |
			(IsInstructionSetSupported_(IS_AVX) ? IS_AVX : 0) |
			(IsInstructionSetSupported_(IS_FMA) ? IS_FMA : 0) |
			(IsInstructionSetSupported_(IS_AVX_2) ? IS_AVX_2 : 0) |
			(IsInstructionSetSupported_(IS_KNC) ? IS_KNC : 0) |
			(IsInstructionSetSupported_(IS_AVX_512) ? IS_AVX_512 : 0);
#else
			0;
#endif
		return (g_enabled_sets & aSet) == aSet;
	}

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
	};

	// Data Helpers

	template<class T, size_t S>
	struct DefaultSIMD {
		T elements[S];
	};

	template<class T, size_t S>
	struct SIMDHelper {
		typedef DefaultSIMD<T, S> simd_t;
		static_assert(sizeof(simd_t) == (sizeof(T) * S), "simd_t size error");

		static simd_t ANVIL_CALL load(const T* x) {
			simd_t tmp;
			memcpy(tmp, x, sizeof(simd_t));
			return tmp;
		}

		static simd_t ANVIL_CALL fillu() {
			return simd_t();
		}

		static simd_t ANVIL_CALL fill0() {
			simd_t tmp;
			memset(&tmp, sizeof(T) * S);
			return tmp;
		}

		static simd_t ANVIL_CALL fill(T x) {
			simd_t tmp;
			for (size_t i = 0; i < S; ++i) tmp.elements[i] = x;
			return tmp;
		}

		static simd_t ANVIL_CALL set1(T x) {
			set4(x, static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));
		}

		static simd_t ANVIL_CALL set2(T x, T y) {
			set4(x, y, static_cast<T>(0), static_cast<T>(0));
		}

		static simd_t ANVIL_CALL set3(T x, T y, T z) {
			set4(x, y, z, static_cast<T>(0));
		}

		static simd_t ANVIL_CALL set4(T x, T y, T z, T w) {
			simd_t tmp = S > 3 ? load_0 : simd_t();
			tmp.elements[0] = x;
			if (S >= 2) tmp.elements[1] = y;
			if (S >= 3) tmp.elements[2] = z;
			if (S >= 4) tmp.elements[3] = w;
			return tmp;
		}

		template<size_t GS>
		static void get(simd_t x, T* y) {
			for (size_t i = 0; i < GS; ++i)  y[i] = x.elements[i];
		}
	};

	// Default Operation Implementation

	template<class T, size_t S, Operation O>
	struct OperationImplementation {

		static void ANVIL_CALL execute(const T* x_, const T* y_, T* o_) {
			enum {
				OPTIMAL = OperationInfo<O, T>::size_max,
				LOOP = S / OPTIMAL,
				REMAINDER = S % OPTIMAL
			};
			typedef OperationImplementation<T, OPTIMAL, O> optimal_t;
			union simd_ptr {
				SIMDHelper<T, OPTIMAL>::simd_t* vo;
				DefaultSIMD<T, OPTIMAL>* vn;
				const T* s;
			};
			simd_ptr x, y, o;
			x.s = x_;
			y.s = y_;
			o.s = o_;

			if (optimal_t::optimised()) {
				for (size_t i = 0; i < OPTIMAL; ++i) {
					o.vo[i] = optimal_t::execute_in(x.vo[i], y.vo[i]);
				}
			} else {
				for (size_t i = 0; i < OPTIMAL; ++i) {
					optimal_t::execute_nop(x.vn[i].elements, y.vn[i].elements, o.vn[i].elements);
				}
			}
			for (size_t i = 0; i < REMAINDER; ++i) {
				o.vn[LOOP].elements[i] = OperationImplementation<T, 1, O>::execute(x.vn[LOOP].elements[i], y.vn[LOOP].elements[i]);
			}
		}

		static ANVIL_STRONG_INLINE void ANVIL_CALL execute_op(const T* x, const T* y, T* o) {
			execute(x, y, o);
		}

		static ANVIL_STRONG_INLINE void ANVIL_CALL execute_nop(const T* x, const T* y, T* o) {
			execute(x, y, o);
		}

		static ANVIL_STRONG_INLINE bool ANVIL_CALL optimised() {
			return false;
		}
	};

	template<class T, Operation O>
	struct OperationImplementation<T,2,O> {
		enum { PARAMS = OperationParams<O>::value };

		template<size_t S = PARAMS>
		static inline void ANVIL_CALL execute(const T* x, const T* y, const T* z, T* o) {
			o[0] = OperationImplementation<T, 1, O>::execute(x[0], y[0], z[0]);
			o[1] = OperationImplementation<T, 1, O>::execute(x[1], y[1], z[1]);
		}

		template<size_t S = PARAMS>
		static inline void ANVIL_CALL execute(const T* x, const T* y, T* o) {
			o[0] = OperationImplementation<T, 1, O>::execute(x[0], y[0]);
			o[1] = OperationImplementation<T, 1, O>::execute(x[1], y[1]);
		}

		template<size_t S = PARAMS>
		static ANVIL_STRONG_INLINE void ANVIL_CALL execute(const T* x, T* o) {
			o[0] = OperationImplementation<T, 1, O>::execute(x[0]);
			o[1] = OperationImplementation<T, 1, O>::execute(x[1]);
		}

		template<size_t S = PARAMS>
		static ANVIL_STRONG_INLINE void ANVIL_CALL execute_op(const T* x, const T* y, const T* z, T* o) {
			execute(x, y, z, o);
		}

		template<size_t S = PARAMS>
		static ANVIL_STRONG_INLINE void ANVIL_CALL execute_op(const T* x, const T* y, T* o) {
			execute(x, y, o);
		}

		template<size_t S = PARAMS>
		static ANVIL_STRONG_INLINE void ANVIL_CALL execute_op(const T* x, T* o) {
			execute(x, o);
		}

		template<size_t S = PARAMS>
		static ANVIL_STRONG_INLINE void ANVIL_CALL execute_nop(const T* x, const T* y, const T* z, T* o) {
			execute(x, y, z, o);
		}

		template<size_t S = PARAMS>
		static ANVIL_STRONG_INLINE void ANVIL_CALL execute_nop(const T* x, const T* y, T* o) {
			execute(x, y, o);
		}

		template<size_t S = PARAMS>
		static ANVIL_STRONG_INLINE void ANVIL_CALL execute_nop(const T* x, T* o) {
			execute(x, o);
		}

		static ANVIL_STRONG_INLINE bool ANVIL_CALL optimised() {
			return false;
		}
	};

	template<class T, size_t S>
	struct OperationImplementation<T, S, OP_FILL> {
		static ANVIL_STRONG_INLINE void ANVIL_CALL execute(T* aOutput) {
			memset(aOutput, 0, sizeof(T) * S);
		}

		static void ANVIL_CALL execute(T x, T* o) {
			for (size_t i = 0; i < S; ++i) o[i] = x;
		}

		static void ANVIL_CALL execute(T x, T y, T* o) {
			if (S > 2) execute(o);
			o[0] = x;
			if (S > 1) o[1] = y;
		}

		static void ANVIL_CALL execute(T x, T y, T z, T* o) {
			if (S > 3) execute(o);
			o[0] = x;
			if (S > 1) o[1] = y;
			if (S > 2) o[2] = z;
		}

		static void ANVIL_CALL execute(T x, T y, T z, T w, T* o) {
			if (S > 4) execute(o);
			o[0] = x;
			if (S > 1) o[1] = y;
			if (S > 2) o[2] = z;
			if (S > 3) o[3] = w;
		}

		static ANVIL_STRONG_INLINE void ANVIL_CALL execute_op(T* o) {
			execute(o);
		}

		static ANVIL_STRONG_INLINE void ANVIL_CALL execute_op(T x, T* o) {
			execute(x, o);
		}

		static ANVIL_STRONG_INLINE void ANVIL_CALL execute_op(T x, T y, T* o) {
			execute(x, y, o);
		}

		static ANVIL_STRONG_INLINE void ANVIL_CALL execute_op(T x, T y, T z, T* o) {
			execute(x, y, z, o);
		}

		static ANVIL_STRONG_INLINE void  ANVIL_CALL execute_op(T x, T y, T z, T w, T* o) {
			execute(x, y, z, w, o);
		}

		static ANVIL_STRONG_INLINE void ANVIL_CALL execute_nop(T* o) {
			execute(o);
		}

		static ANVIL_STRONG_INLINE void ANVIL_CALL execute_nop(T x, T* o) {
			execute(x, o);
		}

		static ANVIL_STRONG_INLINE void ANVIL_CALL execute_nop(T x, T y, T* o) {
			execute(x, y, o);
		}

		static ANVIL_STRONG_INLINE void ANVIL_CALL execute_nop(T x, T y, T z, T* o) {
			execute(x, y, z, o);
		}

		static ANVIL_STRONG_INLINE void ANVIL_CALL execute_nop(T x, T y, T z, T w, T* o) {
			execute(x, y, z, w, o);
		}

		static ANVIL_STRONG_INLINE bool ANVIL_CALL optimised() {
			return false;
		}
	};

	template<class T, size_t S>
	struct OperationImplementation<T, S, OP_CAST> {
		template<class T2>
		static void ANVIL_CALL execute(const T2* x, T* y) {
			for (size_t i = 0; i < S; ++i) y[i] = static_cast<T>(x[i]);
		}
	};

	template<class T, size_t S>
	struct OperationImplementation<T, S, OP_RESIZE> {
		template<size_t S2>
		static void ANVIL_CALL execute(const T* x, T* y) {
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
	struct OperationImplementation<T, 1, O> {\
		static ANVIL_STRONG_INLINE T ANVIL_CALL execute(T x, T y, T z) {\
			return F(x, y, z);\
		}\
	};\

#define ANVIL_SIMD_IMPLEMENTATION_S_SS_1(O,F)\
	template<class T>\
	struct OperationImplementation<T, 1, O> {\
		static ANVIL_STRONG_INLINE T ANVIL_CALL execute(T x, T y) {\
			return F(x, y);\
		}\
	};\

#define ANVIL_SIMD_IMPLEMENTATION_S_SS_1_SPECIALISE(O,T,F)\
	template<>\
	struct OperationImplementation<T, 1, O> {\
		static ANVIL_STRONG_INLINE T ANVIL_CALL execute(T x, T y) {\
			return F(x, y);\
		}\
	};\

#define ANVIL_SIMD_IMPLEMENTATION_S_S_1(O,F)\
	template<class T>\
	struct OperationImplementation<T, 1, O> {\
		static ANVIL_STRONG_INLINE T ANVIL_CALL execute(T x) {\
			return F(x);\
		}\
	};\

#define ANVIL_SIMD_IMPLEMENTATION_S_S_1_SPECIALISE(O,T,F)\
	template<>\
	struct OperationImplementation<T, 1, O> {\
		static ANVIL_STRONG_INLINE T ANVIL_CALL execute(T x) {\
			return F(x);\
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

#ifdef ANVIL_USE_INTEL_SIMD_INTRINSICS


	template<>
	struct SIMDHelper<double, 2> {
		typedef __m128d simd_t;
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL load(const double* x) { _mm_load_pd(x); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fillu() { return _mm_undefined_pd(); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fill0() { return _mm_setzero_pd(); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fill(double x) { return _mm_set1_pd(x); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set1(double x) { return set2(x, 0.0); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set2(double x, double y) { return _mm_setr_pd(x, y); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set3(double x, double y, double z) { return set2(x, y); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set4(double x, double y, double z, double w) { return set2(x, y); }

		template<size_t GS>
		static void ANVIL_CALL get(simd_t x, double* y) {
			for (size_t i = 0; i < GS; ++i)  y[i] = x.m128d_f64[i];
		}
	};

	template<>
	struct SIMDHelper<int64_t, 2> {
		typedef __m128i simd_t;
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL load(const int64_t* x) { _mm_load_si128(reinterpret_cast<const __m128i*>(x)); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fillu() { return _mm_undefined_si128(); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fill0() { return _mm_setzero_si128(); }
#if ANVIL_CPP_VER < 2011
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fill(int64_t x) { return _mm_set_epi32(reinterpret_cast<const int32_t*>(&x)[0], reinterpret_cast<const int32_t*>(&x)[1], reinterpret_cast<const int32_t*>(&x)[0], reinterpret_cast<const int32_t*>(&x)[1]); }
#else
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fill(int64_t x) { _mm_set1_epi64x(x); }
#endif
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set1(int64_t x) { return set2(x, 0); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set2(int64_t x, int64_t y) { return _mm_set_epi32(reinterpret_cast<const int32_t*>(&x)[0], reinterpret_cast<const int32_t*>(&x)[1], reinterpret_cast<const int32_t*>(&y)[0], reinterpret_cast<const int32_t*>(&y)[1]); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set3(int64_t x, int64_t y, int64_t z) { return set2(x, y); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set4(int64_t x, int64_t y, int64_t z, int64_t w) { return set2(x, y); }

		template<size_t GS>
		static void ANVIL_CALL get(simd_t x, int64_t* y) {
			for (size_t i = 0; i < GS; ++i)  y[i] = x.m128i_i64[i];
		}
	};

	template<>
	struct SIMDHelper<uint64_t, 2> {
		typedef __m128i simd_t;
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL load(const uint64_t* x) { _mm_load_si128(reinterpret_cast<const __m128i*>(x)); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fillu() { return _mm_undefined_si128(); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fill0() { return _mm_setzero_si128(); }
#if ANVIL_CPP_VER < 2011
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fill(uint64_t x) { return _mm_set_epi32(reinterpret_cast<const int32_t*>(&x)[0], reinterpret_cast<const int32_t*>(&x)[1], reinterpret_cast<const int32_t*>(&x)[0], reinterpret_cast<const int32_t*>(&x)[1]); }
#else
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fill(uint64_t x) { _mm_set1_epi64x(x); }
#endif
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set1(uint64_t x) { return set2(x, 0); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set2(uint64_t x, uint64_t y) { return _mm_set_epi32(reinterpret_cast<const int32_t*>(&x)[0], reinterpret_cast<const int32_t*>(&x)[1], reinterpret_cast<const int32_t*>(&y)[0], reinterpret_cast<const int32_t*>(&y)[1]); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set3(uint64_t x, uint64_t y, uint64_t z) { return set2(x, y); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set4(uint64_t x, uint64_t y, uint64_t z, uint64_t w) { return set2(x, y); }

		template<size_t GS>
		static void ANVIL_CALL get(simd_t x, uint64_t* y) {
			for (size_t i = 0; i < GS; ++i)  y[i] = x.m128i_u64[i];
		}
	};

	template<>
	struct SIMDHelper<float, 4> {
		typedef __m128 simd_t;
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL load(const float* x) { _mm_load_ps(x); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fillu() { return _mm_undefined_ps(); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fill0() { return _mm_setzero_ps(); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fill(float x) { return _mm_set1_ps(x); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set1(float x) { set4(x, 0.f, 0.f, 0.f); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set2(float x, float y) { return set4(x, y, 0.f, 0.f); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set3(float x, float y, float z) { return set4(x, y, z, 0.f); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set4(float x, float y, float z, float w) { return _mm_setr_ps(x, y, z, w); }

		template<size_t GS>
		static void ANVIL_CALL get(simd_t x, float* y) {
			for (size_t i = 0; i < GS; ++i)  y[i] = x.m128_f32[i];
		}
	};

	template<>
	struct SIMDHelper<int32_t, 4> {
		typedef __m128i simd_t;
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL load(const int32_t* x) { _mm_load_si128(reinterpret_cast<const __m128i*>(x)); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fillu() { return _mm_undefined_si128(); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fill0() { return _mm_setzero_si128(); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fill(int32_t x) { return _mm_set1_epi32(x); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set1(int32_t x) { set4(x, 0, 0, 0); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set2(int32_t x, int32_t y) { return set4(x, y, 0, 0); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set3(int32_t x, int32_t y, int32_t z) { return set4(x, y, z, 0); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set4(int32_t x, int32_t y, int32_t z, int32_t w) { return _mm_setr_epi32(x, y, z, w); }

		template<size_t GS>
		static void ANVIL_CALL get(simd_t x, int32_t* y) {
			for (size_t i = 0; i < GS; ++i)  y[i] = x.m128i_i32[i];
		}
	};

	template<>
	struct SIMDHelper<uint32_t, 4> {
		typedef __m128i simd_t;
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL load(const uint32_t* x) { _mm_load_si128(reinterpret_cast<const __m128i*>(x)); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fillu() { return _mm_undefined_si128(); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fill0() { return _mm_setzero_si128(); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fill(uint32_t x) { return _mm_set1_epi32(x); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set1(uint32_t x) { set4(x, 0, 0, 0); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set2(uint32_t x, uint32_t y) { return set4(x, y, 0, 0); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set3(uint32_t x, uint32_t y, uint32_t z) { return set4(x, y, z, 0); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set4(uint32_t x, uint32_t y, uint32_t z, uint32_t w) { return _mm_setr_epi32(x, y, z, w); }

		template<size_t GS>
		static void ANVIL_CALL get(simd_t x, uint32_t* y) {
			for (size_t i = 0; i < GS; ++i)  y[i] = x.m128i_u32[i];
		}
	};

	template<>
	struct SIMDHelper<int16_t, 8> {
		typedef __m128i simd_t;
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL load(const int16_t* x) { _mm_load_si128(reinterpret_cast<const __m128i*>(x)); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fillu() { return _mm_undefined_si128(); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fill0() { return _mm_setzero_si128(); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fill(int16_t x) { return _mm_set1_epi16(x); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set1(int16_t x) { set4(x, 0, 0, 0); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set2(int16_t x, int16_t y) { return set4(x, y, 0, 0); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set3(int16_t x, int16_t y, int16_t z) { return set4(x, y, z, 0); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set4(int16_t x, int16_t y, int16_t z, int16_t w) { return _mm_setr_epi16(x, y, z, w, 0, 0, 0, 0); }

		template<size_t GS>
		static void ANVIL_CALL get(simd_t x, int16_t* y) {
			for (size_t i = 0; i < GS; ++i)  y[i] = x.m128i_i16[i];
		}
	};

	template<>
	struct SIMDHelper<uint16_t, 8> {
		typedef __m128i simd_t;
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL load(const uint16_t* x) { _mm_load_si128(reinterpret_cast<const __m128i*>(x)); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fillu() { return _mm_undefined_si128(); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fill0() { return _mm_setzero_si128(); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fill(uint16_t x) { return _mm_set1_epi16(x); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set1(uint16_t x) { set4(x, 0, 0, 0); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set2(uint16_t x, uint16_t y) { return set4(x, y, 0, 0); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set3(uint16_t x, uint16_t y, uint16_t z) { return set4(x, y, z, 0); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set4(uint16_t x, uint16_t y, uint16_t z, uint16_t w) { return _mm_setr_epi16(x, y, z, w, 0, 0, 0, 0); }

		template<size_t GS>
		static void ANVIL_CALL get(simd_t x, uint16_t* y) {
			for (size_t i = 0; i < GS; ++i)  y[i] = x.m128i_u16[i];
		}
	};

	template<>
	struct SIMDHelper<int8_t, 16> {
		typedef __m128i simd_t;
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL load(const int8_t* x) { _mm_load_si128(reinterpret_cast<const __m128i*>(x)); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fillu() { return _mm_undefined_si128(); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fill0() { return _mm_setzero_si128(); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fill(int8_t x) { return _mm_set1_epi8(x); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set1(int8_t x) { set4(x, 0, 0, 0); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set2(int8_t x, int8_t y) { return set4(x, y, 0, 0); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set3(int8_t x, int8_t y, int8_t z) { return set4(x, y, z, 0); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set4(int8_t x, int8_t y, int8_t z, int8_t w) { return _mm_setr_epi8(x, y, z, w, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); }

		template<size_t GS>
		static void ANVIL_CALL get(simd_t x, int8_t* y) {
			for (size_t i = 0; i < GS; ++i)  y[i] = x.m128i_i8[i];
		}
	};

	template<>
	struct SIMDHelper<uint8_t, 16> {
		typedef __m128i simd_t;
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL load(const uint8_t* x) { _mm_load_si128(reinterpret_cast<const __m128i*>(x)); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fillu() { return _mm_undefined_si128(); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fill0() { return _mm_setzero_si128(); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL fill(uint8_t x) { return _mm_set1_epi8(x); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set1(uint8_t x) { set4(x, 0, 0, 0); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set2(uint8_t x, uint8_t y) { return set4(x, y, 0, 0); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set3(uint8_t x, uint8_t y, uint8_t z) { return set4(x, y, z, 0); }
		static ANVIL_STRONG_INLINE simd_t ANVIL_CALL set4(uint8_t x, uint8_t y, uint8_t z, uint8_t w) { return _mm_setr_epi8(x, y, z, w, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); }

		template<size_t GS>
		static void ANVIL_CALL get(simd_t x, uint8_t* y) {
			for (size_t i = 0; i < GS; ++i)  y[i] = x.m128i_u8[i];
		}
	};

#define ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,OP_SIZE,SIZE,INSTRUCTION,UPLOAD,DOWNLOAD,FUNCTION1,FUNCTION2)\
	template<>\
	struct OperationImplementation<_simd_element_type, SIZE, OP> {\
		typedef SIMDHelper<_simd_element_type,OP_SIZE> helper_t;\
		typedef helper_t::simd_t simd_t;\
		static ANVIL_STRONG_INLINE bool ANVIL_CALL optimised() {\
			return IsInstructionSetSupported( IS_ ## INSTRUCTION );\
		}\
		static ANVIL_STRONG_INLINE _simd_type ANVIL_CALL execute_in(simd_t x, simd_t y) {\
			return FUNCTION1(x,y);\
		}\
		static ANVIL_STRONG_INLINE void ANVIL_CALL execute_op(const _simd_element_type* x, const _simd_element_type* y, _simd_element_type* o) {\
			helper_t::get<SIZE>(execute_in(UPLOAD(x), UPLOAD(y)), o);\
		}\
		static inline void ANVIL_CALL execute_nop(const _simd_element_type* x, const _simd_element_type* y, _simd_element_type* o) {\
			for (size_t i = 0; i < SIZE; ++i) o[i] = FUNCTION2(x[i], y[i]); \
		}\
		static inline void ANVIL_CALL execute(const _simd_element_type* x, const _simd_element_type* y, _simd_element_type* o) {\
			if(optimised()) {\
				execute_op(x,y,o);\
			} else {\
				execute_nop(x,y,o);\
			}\
		}\
	};

#define ANVIL_SIMD_IMPLEMENTATION_V_V(OP,OP_SIZE,SIZE,INSTRUCTION,UPLOAD,DOWNLOAD,FUNCTION1,FUNCTION2)\
	template<>\
	struct OperationImplementation<_simd_element_type, SIZE, OP> {\
		typedef SIMDHelper<_simd_element_type,OP_SIZE> helper_t;\
		typedef helper_t::simd_t simd_t;\
		static ANVIL_STRONG_INLINE bool ANVIL_CALL optimised() {\
			return IsInstructionSetSupported( IS_ ## INSTRUCTION );\
		}\
		static ANVIL_STRONG_INLINE _simd_type ANVIL_CALL execute_in(simd_t x) {\
			return FUNCTION1(x);\
		}\
		static ANVIL_STRONG_INLINE void ANVIL_CALL execute_op(const _simd_element_type* x, _simd_element_type* o) {\
			DOWNLOAD(o,execute_in(UPLOAD(x)));\
		}\
		static inline void ANVIL_CALL execute_nop(const _simd_element_type* x, _simd_element_type* o) {\
			for (size_t i = 0; i < SIZE; ++i) o[i] = FUNCTION2(x[i]); \
		}\
		static inline void ANVIL_CALL execute(const _simd_element_type* x, _simd_element_type* o) {\
			if(optimised()) {\
				execute_op(x,o);\
			} else {\
				execute_nop(x,o);\
			}\
		}\
	};

#define ANVIL_SIMD_SPECIALISE_FILL(SIZE,INSTRUCTION,DOWNLOAD,F0,F1,F2,F3,F4)\
	template<>\
	struct OperationImplementation<_simd_element_type, SIZE, OP_FILL> {\
		static ANVIL_STRONG_INLINE void ANVIL_CALL execute(_simd_element_type* o) {\
			if(optimised()) execute_op(o);\
			else execute_nop(o);\
		}\
		\
		static ANVIL_STRONG_INLINE void ANVIL_CALL execute(_simd_element_type x, _simd_element_type* o) {\
			if(optimised()) execute_op(x,o);\
			else execute_nop(x,o);\
		}\
		\
		static ANVIL_STRONG_INLINE void ANVIL_CALL execute(_simd_element_type x, _simd_element_type y, _simd_element_type* o) {\
			if(optimised()) execute_op(x,y,o);\
			else execute_nop(x,y,o);\
		}\
		\
		static ANVIL_STRONG_INLINE void ANVIL_CALL execute(_simd_element_type x, _simd_element_type y, _simd_element_type z, _simd_element_type* o) {\
			if(optimised()) execute_op(x,y,z,o);\
			else execute_nop(x,y,z,o);\
		}\
		\
		static ANVIL_STRONG_INLINE void ANVIL_CALL execute(_simd_element_type x, _simd_element_type y, _simd_element_type z, _simd_element_type w, _simd_element_type* o) {\
			if(optimised()) execute_op(x,y,z,w,o);\
			else execute_nop(x,y,z,w,o);\
		}\
		\
		static ANVIL_STRONG_INLINE void ANVIL_CALL execute_nop(_simd_element_type* o) {\
			memset(o, 0, sizeof(_simd_element_type) * SIZE);\
		}\
		\
		static ANVIL_STRONG_INLINE void ANVIL_CALL execute_nop(_simd_element_type x, _simd_element_type* o) {\
			for (size_t i = 0; i < SIZE; ++i) o[i] = x;\
		}\
		\
		static ANVIL_STRONG_INLINE void ANVIL_CALL execute_nop(_simd_element_type x, _simd_element_type y, _simd_element_type* o) {\
			if (SIZE > 2) execute_nop(o);\
			o[0] = x;\
			if (SIZE > 1) o[1] = y;\
		}\
		\
		static ANVIL_STRONG_INLINE void ANVIL_CALL execute_nop(_simd_element_type x, _simd_element_type y, _simd_element_type z, _simd_element_type* o) {\
			if (SIZE > 3) execute_nop(o);\
			o[0] = x;\
			if (SIZE > 1) o[1] = y;\
			if (SIZE > 2) o[2] = z;\
		}\
		\
		static ANVIL_STRONG_INLINE void  ANVIL_CALL execute_nop(_simd_element_type x, _simd_element_type y, _simd_element_type z, _simd_element_type w, _simd_element_type* o) {\
			if (SIZE > 4) execute_nop(o);\
			o[0] = x;\
			if (SIZE > 1) o[1] = y;\
			if (SIZE > 2) o[2] = z;\
			if (SIZE > 3) o[3] = w;\
		}\
		\
		static ANVIL_STRONG_INLINE void ANVIL_CALL execute_op(_simd_element_type* o) {\
			_simd_type tmp = F0();\
			DOWNLOAD(o,tmp);\
		}\
		\
		static ANVIL_STRONG_INLINE void ANVIL_CALL execute_op(_simd_element_type x, _simd_element_type* o) {\
			_simd_type tmp = F1(x);\
			DOWNLOAD(o,tmp);\
		}\
		\
		static ANVIL_STRONG_INLINE void ANVIL_CALL execute_op(_simd_element_type x, _simd_element_type y, _simd_element_type* o) {\
			_simd_type tmp = F2(x, y);\
			DOWNLOAD(o,tmp);\
		}\
		\
		static ANVIL_STRONG_INLINE void ANVIL_CALL execute_op(_simd_element_type x, _simd_element_type y, _simd_element_type z, _simd_element_type* o) {\
			_simd_type tmp = F3(x, y, z);\
			DOWNLOAD(o,tmp);\
		}\
		\
		static ANVIL_STRONG_INLINE void ANVIL_CALL execute_op(_simd_element_type x, _simd_element_type y, _simd_element_type z, _simd_element_type w, _simd_element_type* o) {\
			_simd_type tmp = F4(x, y, z, w);\
			DOWNLOAD(o,tmp);\
		}\
		\
		static ANVIL_STRONG_INLINE bool ANVIL_CALL optimised() {\
			return IsInstructionSetSupported( IS_ ## INSTRUCTION );\
		}\
	};

#define _simd_upload_16_16(X) _simd_load(X)
#define _simd_upload_16_15(X) _simd_set(X[0], X[1], X[2], X[3], X[4], X[5], X[6], X[7], X[8], X[9], X[10], X[11], X[12], X[13], X[14], 0)
#define _simd_upload_16_14(X) _simd_set(X[0], X[1], X[2], X[3], X[4], X[5], X[6], X[7], X[8], X[9], X[10], X[11], X[12], X[13], 0,     0)
#define _simd_upload_16_13(X) _simd_set(X[0], X[1], X[2], X[3], X[4], X[5], X[6], X[7], X[8], X[9], X[10], X[11], X[12], 0,     0,     0)
#define _simd_upload_16_12(X) _simd_set(X[0], X[1], X[2], X[3], X[4], X[5], X[6], X[7], X[8], X[9], X[10], X[11], 0,     0,     0,     0)
#define _simd_upload_16_11(X) _simd_set(X[0], X[1], X[2], X[3], X[4], X[5], X[6], X[7], X[8], X[9], X[10], 0,     0,     0,     0,     0)
#define _simd_upload_16_10(X) _simd_set(X[0], X[1], X[2], X[3], X[4], X[5], X[6], X[7], X[8], X[9], 0,     0,     0,     0,     0,     0)
#define _simd_upload_16_9(X)  _simd_set(X[0], X[1], X[2], X[3], X[4], X[5], X[6], X[7], X[8], 0,    0,     0,     0,     0,     0,     0)
#define _simd_upload_16_8(X)  _simd_set(X[0], X[1], X[2], X[3], X[4], X[5], X[6], X[7], 0,    0,    0,     0,     0,     0,     0,     0)
#define _simd_upload_16_7(X)  _simd_set(X[0], X[1], X[2], X[3], X[4], X[5], X[6], 0,    0,    0,    0,     0,     0,     0,     0,     0)
#define _simd_upload_16_6(X)  _simd_set(X[0], X[1], X[2], X[3], X[4], X[5], 0,    0,    0,    0,    0,     0,     0,     0,     0,     0)
#define _simd_upload_16_5(X)  _simd_set(X[0], X[1], X[2], X[3], X[4], 0,    0,    0,    0,    0,    0,     0,     0,     0,     0,     0)
#define _simd_upload_16_4(X)  _simd_set(X[0], X[1], X[2], X[3], 0,    0,    0,    0,    0,    0,    0,     0,     0,     0,     0,     0)
#define _simd_upload_16_3(X)  _simd_set(X[0], X[1], X[2], 0,    0,    0,    0,    0,    0,    0,    0,     0,     0,     0,     0,     0)
#define _simd_upload_16_2(X)  _simd_set(X[0], X[1], 0,    0,    0,    0,    0,    0,    0,    0,    0,     0,     0,     0,     0,     0)

#define _simd_upload_8_8(X) _simd_load(X)
#define _simd_upload_8_7(X) _simd_set(X[0], X[1], X[2], X[3], X[4], X[5], X[6], 0)
#define _simd_upload_8_6(X) _simd_set(X[0], X[1], X[2], X[3], X[4], X[5], 0,    0)
#define _simd_upload_8_5(X) _simd_set(X[0], X[1], X[2], X[3], X[4], 0,    0,    0)
#define _simd_upload_8_4(X) _simd_set(X[0], X[1], X[2], X[3], 0,    0,    0,    0)
#define _simd_upload_8_3(X) _simd_set(X[0], X[1], X[2], 0,    0,    0,    0,    0)
#define _simd_upload_8_2(X) _simd_set(X[0], X[1], 0,    0,    0,    0,    0,    0)

#define _simd_upload_4_4(X) _simd_load(X)
#define _simd_upload_4_3(X) _simd_set(X[0], X[1], X[2], 0)
#define _simd_upload_4_2(X) _simd_set(X[0], X[1], 0,    0)

#define _simd_upload_2_2(X) _simd_load(X)

#define _simd_download_n_16(X,Y) X[0] = _simd_data(Y)[0]; X[1] = _simd_data(Y)[1]; X[2] = _simd_data(Y)[2]; X[3] = _simd_data(Y)[3]; X[4] = _simd_data(Y)[4]; \
		X[5] = _simd_data(Y)[5]; X[6] = _simd_data(Y)[6]; X[7] = _simd_data(Y)[7]; X[8] = _simd_data(Y)[8]; X[9] = _simd_data(Y)[9]; X[10] = _simd_data(Y)[10]; \
		X[11] = _simd_data(Y)[11]; X[12] = _simd_data(Y)[12]; X[13] = _simd_data(Y)[13]; X[14] = _simd_data(Y)[14];  X[15] = _simd_data(Y)[15];
#define _simd_download_n_15(X,Y) X[0] = _simd_data(Y)[0]; X[1] = _simd_data(Y)[1]; X[2] = _simd_data(Y)[2]; X[3] = _simd_data(Y)[3]; X[4] = _simd_data(Y)[4]; \
		X[5] = _simd_data(Y)[5]; X[6] = _simd_data(Y)[6]; X[7] = _simd_data(Y)[7]; X[8] = _simd_data(Y)[8]; X[9] = _simd_data(Y)[9]; X[10] = _simd_data(Y)[10]; \
		X[11] = _simd_data(Y)[11]; X[12] = _simd_data(Y)[12]; X[13] = _simd_data(Y)[13]; X[14] = _simd_data(Y)[14];
#define _simd_download_n_14(X,Y) X[0] = _simd_data(Y)[0]; X[1] = _simd_data(Y)[1]; X[2] = _simd_data(Y)[2]; X[3] = _simd_data(Y)[3]; X[4] = _simd_data(Y)[4]; \
		X[5] = _simd_data(Y)[5]; X[6] = _simd_data(Y)[6]; X[7] = _simd_data(Y)[7]; X[8] = _simd_data(Y)[8]; X[9] = _simd_data(Y)[9]; X[10] = _simd_data(Y)[10]; \
		X[11] = _simd_data(Y)[11]; X[12] = _simd_data(Y)[12]; X[13] = _simd_data(Y)[13];
#define _simd_download_n_13(X,Y) X[0] = _simd_data(Y)[0]; X[1] = _simd_data(Y)[1]; X[2] = _simd_data(Y)[2]; X[3] = _simd_data(Y)[3]; X[4] = _simd_data(Y)[4]; \
		X[5] = _simd_data(Y)[5]; X[6] = _simd_data(Y)[6]; X[7] = _simd_data(Y)[7]; X[8] = _simd_data(Y)[8]; X[9] = _simd_data(Y)[9]; X[10] = _simd_data(Y)[10]; \
		X[11] = _simd_data(Y)[11]; X[12] = _simd_data(Y)[12];
#define _simd_download_n_12(X,Y) X[0] = _simd_data(Y)[0]; X[1] = _simd_data(Y)[1]; X[2] = _simd_data(Y)[2]; X[3] = _simd_data(Y)[3]; X[4] = _simd_data(Y)[4]; \
		X[5] = _simd_data(Y)[5]; X[6] = _simd_data(Y)[6]; X[7] = _simd_data(Y)[7]; X[8] = _simd_data(Y)[8]; X[9] = _simd_data(Y)[9]; X[10] = _simd_data(Y)[10]; \
		X[11] = _simd_data(Y)[11];
#define _simd_download_n_11(X,Y) X[0] = _simd_data(Y)[0]; X[1] = _simd_data(Y)[1]; X[2] = _simd_data(Y)[2]; X[3] = _simd_data(Y)[3]; X[4] = _simd_data(Y)[4]; \
		X[5] = _simd_data(Y)[5]; X[6] = _simd_data(Y)[6]; X[7] = _simd_data(Y)[7]; X[8] = _simd_data(Y)[8]; X[9] = _simd_data(Y)[9]; X[10] = _simd_data(Y)[10];
#define _simd_download_n_10(X,Y) X[0] = _simd_data(Y)[0]; X[1] = _simd_data(Y)[1]; X[2] = _simd_data(Y)[2]; X[3] = _simd_data(Y)[3]; X[4] = _simd_data(Y)[4]; \
		X[5] = _simd_data(Y)[5]; X[6] = _simd_data(Y)[6]; X[7] = _simd_data(Y)[7]; X[8] = _simd_data(Y)[8]; X[9] = _simd_data(Y)[9];
#define _simd_download_n_9(X,Y) X[0] = _simd_data(Y)[0]; X[1] = _simd_data(Y)[1]; X[2] = _simd_data(Y)[2]; X[3] = _simd_data(Y)[3]; X[4] = _simd_data(Y)[4]; \
		X[5] = _simd_data(Y)[5]; X[6] = _simd_data(Y)[6]; X[7] = _simd_data(Y)[7]; X[8] = _simd_data(Y)[8];
#define _simd_download_n_8(X,Y) X[0] = _simd_data(Y)[0]; X[1] = _simd_data(Y)[1]; X[2] = _simd_data(Y)[2]; X[3] = _simd_data(Y)[3]; X[4] = _simd_data(Y)[4]; \
		X[5] = _simd_data(Y)[5]; X[6] = _simd_data(Y)[6]; X[7] = _simd_data(Y)[7];
#define _simd_download_n_7(X,Y) X[0] = _simd_data(Y)[0]; X[1] = _simd_data(Y)[1]; X[2] = _simd_data(Y)[2]; X[3] = _simd_data(Y)[3]; X[4] = _simd_data(Y)[4]; \
		X[5] = _simd_data(Y)[5]; X[6] = _simd_data(Y)[6];
#define _simd_download_n_6(X,Y) X[0] = _simd_data(Y)[0]; X[1] = _simd_data(Y)[1]; X[2] = _simd_data(Y)[2]; X[3] = _simd_data(Y)[3]; X[4] = _simd_data(Y)[4]; \
		X[5] = _simd_data(Y)[5];
#define _simd_download_n_5(X,Y) X[0] = _simd_data(Y)[0]; X[1] = _simd_data(Y)[1]; X[2] = _simd_data(Y)[2]; X[3] = _simd_data(Y)[3]; X[4] = _simd_data(Y)[4];
#define _simd_download_n_4(X,Y) X[0] = _simd_data(Y)[0]; X[1] = _simd_data(Y)[1]; X[2] = _simd_data(Y)[2]; X[3] = _simd_data(Y)[3];
#define _simd_download_n_3(X,Y) X[0] = _simd_data(Y)[0]; X[1] = _simd_data(Y)[1]; X[2] = _simd_data(Y)[2];
#define _simd_download_n_2(X,Y) X[0] = _simd_data(Y)[0]; X[1] = _simd_data(Y)[1];

#define _simd_download_16_16(X,Y)*reinterpret_cast< _simd_type *>(X) = Y
#define _simd_download_8_8(X,Y)*reinterpret_cast< _simd_type *>(X) = Y
#define _simd_download_4_4(X,Y)*reinterpret_cast< _simd_type *>(X) = Y
#define _simd_download_2_2(X,Y)*reinterpret_cast< _simd_type *>(X) = Y

#define ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP,INSTRUCTION, FUNCTION1, FUNCTION2)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP, _simd_element_type, 16> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
	};}\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,16,INSTRUCTION, _simd_upload_16_16, _simd_download_16_16, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,15,INSTRUCTION, _simd_upload_16_15, _simd_download_n_15, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,14,INSTRUCTION, _simd_upload_16_14, _simd_download_n_14, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,13,INSTRUCTION, _simd_upload_16_13, _simd_download_n_13, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,12,INSTRUCTION, _simd_upload_16_12, _simd_download_n_12, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,11,INSTRUCTION, _simd_upload_16_11, _simd_download_n_11, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,10,INSTRUCTION, _simd_upload_16_10, _simd_download_n_10, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,9, INSTRUCTION, _simd_upload_16_9,  _simd_download_n_9,  FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,8, INSTRUCTION, _simd_upload_16_8,  _simd_download_n_8,  FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,7, INSTRUCTION, _simd_upload_16_7,  _simd_download_n_7,  FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,6, INSTRUCTION, _simd_upload_16_6,  _simd_download_n_6,  FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,5, INSTRUCTION, _simd_upload_16_5,  _simd_download_n_5,  FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,4, INSTRUCTION, _simd_upload_16_4,  _simd_download_n_4,  FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,3, INSTRUCTION, _simd_upload_16_3,  _simd_download_n_3,  FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,2, INSTRUCTION, _simd_upload_16_2,  _simd_download_n_2,  FUNCTION1, FUNCTION2)

#define ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP,INSTRUCTION, FUNCTION1, FUNCTION2)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP, _simd_element_type, 8> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
	};}\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,8,8,INSTRUCTION, _simd_upload_8_8, _simd_download_8_8, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,8,7,INSTRUCTION, _simd_upload_8_7, _simd_download_n_7, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,8,6,INSTRUCTION, _simd_upload_8_6, _simd_download_n_6, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,8,5,INSTRUCTION, _simd_upload_8_5, _simd_download_n_5, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,8,4,INSTRUCTION, _simd_upload_8_4, _simd_download_n_4, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,8,3,INSTRUCTION, _simd_upload_8_3, _simd_download_n_3, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,8,2,INSTRUCTION, _simd_upload_8_2, _simd_download_n_2, FUNCTION1, FUNCTION2)

#define ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP,INSTRUCTION, FUNCTION1, FUNCTION2)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP, _simd_element_type, 4> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
	};}\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,4,4,INSTRUCTION, _simd_upload_4_4, _simd_download_4_4, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,4,3,INSTRUCTION, _simd_upload_4_3, _simd_download_n_3, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,4,2,INSTRUCTION, _simd_upload_4_2, _simd_download_n_2, FUNCTION1, FUNCTION2)

#define ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP,INSTRUCTION, FUNCTION1, FUNCTION2)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP, _simd_element_type, 2> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
	};}\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,2,2,INSTRUCTION, _simd_upload_2_2, _simd_download_2_2, FUNCTION1, FUNCTION2)

#define ANVIL_SIMD_IMPLEMENTATION_V_V_16(OP,INSTRUCTION, FUNCTION1, FUNCTION2)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP, _simd_element_type, 16> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
	};}\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,16,INSTRUCTION, _simd_upload_16_16, _simd_download_16_16, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,15,INSTRUCTION, _simd_upload_16_15, _simd_download_n_15, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,14,INSTRUCTION, _simd_upload_16_14, _simd_download_n_14, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,13,INSTRUCTION, _simd_upload_16_13, _simd_download_n_13, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,12,INSTRUCTION, _simd_upload_16_12, _simd_download_n_12, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,11,INSTRUCTION, _simd_upload_16_11, _simd_download_n_11, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,10,INSTRUCTION, _simd_upload_16_10, _simd_download_n_10, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,9, INSTRUCTION, _simd_upload_16_9,  _simd_download_n_9,  FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,8, INSTRUCTION, _simd_upload_16_8,  _simd_download_n_8,  FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,7, INSTRUCTION, _simd_upload_16_7,  _simd_download_n_7,  FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,6, INSTRUCTION, _simd_upload_16_6,  _simd_download_n_6,  FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,5, INSTRUCTION, _simd_upload_16_5,  _simd_download_n_5,  FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,4, INSTRUCTION, _simd_upload_16_4,  _simd_download_n_4,  FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,3, INSTRUCTION, _simd_upload_16_3,  _simd_download_n_3,  FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,2, INSTRUCTION, _simd_upload_16_2,  _simd_download_n_2,  FUNCTION1, FUNCTION2)

#define ANVIL_SIMD_IMPLEMENTATION_V_V_8(OP,INSTRUCTION, FUNCTION1, FUNCTION2)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP, _simd_element_type, 8> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
	};}\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,8,8,INSTRUCTION, _simd_upload_8_8, _simd_download_8_8, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,8,7,INSTRUCTION, _simd_upload_8_7, _simd_download_n_7, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,8,6,INSTRUCTION, _simd_upload_8_6, _simd_download_n_6, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,8,5,INSTRUCTION, _simd_upload_8_5, _simd_download_n_5, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,8,4,INSTRUCTION, _simd_upload_8_4, _simd_download_n_4, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,8,3,INSTRUCTION, _simd_upload_8_3, _simd_download_n_3, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,8,2,INSTRUCTION, _simd_upload_8_2, _simd_download_n_2, FUNCTION1, FUNCTION2)

#define ANVIL_SIMD_IMPLEMENTATION_V_V_4(OP,INSTRUCTION, FUNCTION1, FUNCTION2)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP, _simd_element_type, 4> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
	};}\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,4,4,INSTRUCTION, _simd_upload_4_4, _simd_download_4_4, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,4,3,INSTRUCTION, _simd_upload_4_3, _simd_download_n_3, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,4,2,INSTRUCTION, _simd_upload_4_2, _simd_download_n_2, FUNCTION1, FUNCTION2)

#define ANVIL_SIMD_IMPLEMENTATION_V_V_2(OP,INSTRUCTION, FUNCTION1, FUNCTION2)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP, _simd_element_type, 2> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
	};}\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,2,2,INSTRUCTION, _simd_upload_2_2, _simd_download_2_2, FUNCTION1, FUNCTION2)

#define ANVIL_SIMD_SPECIALISE_FILL_16(INSTRUCTION)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP_FILL, _simd_element_type, 16> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
	};}\
	ANVIL_SIMD_SPECIALISE_FILL(16, SSE, _simd_download_16_16, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)\
	ANVIL_SIMD_SPECIALISE_FILL(15, SSE, _simd_download_n_15, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)\
	ANVIL_SIMD_SPECIALISE_FILL(14, SSE, _simd_download_n_14, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)\
	ANVIL_SIMD_SPECIALISE_FILL(13, SSE, _simd_download_n_13, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)\
	ANVIL_SIMD_SPECIALISE_FILL(12, SSE, _simd_download_n_12, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)\
	ANVIL_SIMD_SPECIALISE_FILL(11, SSE, _simd_download_n_11, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)\
	ANVIL_SIMD_SPECIALISE_FILL(10, SSE, _simd_download_n_10, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)\
	ANVIL_SIMD_SPECIALISE_FILL(9, SSE, _simd_download_n_9, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)\
	ANVIL_SIMD_SPECIALISE_FILL(8, SSE, _simd_download_n_8, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)\
	ANVIL_SIMD_SPECIALISE_FILL(7, SSE, _simd_download_n_7, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)\
	ANVIL_SIMD_SPECIALISE_FILL(6, SSE, _simd_download_n_6, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)\
	ANVIL_SIMD_SPECIALISE_FILL(5, SSE, _simd_download_n_5, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)\
	ANVIL_SIMD_SPECIALISE_FILL(4, SSE, _simd_download_n_4, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)\
	ANVIL_SIMD_SPECIALISE_FILL(3, SSE, _simd_download_n_3, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)\
	ANVIL_SIMD_SPECIALISE_FILL(2, SSE, _simd_download_n_2, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)

#define ANVIL_SIMD_SPECIALISE_FILL_8(INSTRUCTION)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP_FILL, _simd_element_type, 8> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
	};}\
	ANVIL_SIMD_SPECIALISE_FILL(8, SSE, _simd_download_8_8, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)\
	ANVIL_SIMD_SPECIALISE_FILL(7, SSE, _simd_download_n_7, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)\
	ANVIL_SIMD_SPECIALISE_FILL(6, SSE, _simd_download_n_6, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)\
	ANVIL_SIMD_SPECIALISE_FILL(5, SSE, _simd_download_n_5, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)\
	ANVIL_SIMD_SPECIALISE_FILL(4, SSE, _simd_download_n_4, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)\
	ANVIL_SIMD_SPECIALISE_FILL(3, SSE, _simd_download_n_3, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)\
	ANVIL_SIMD_SPECIALISE_FILL(2, SSE, _simd_download_n_2, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)

#define ANVIL_SIMD_SPECIALISE_FILL_4(INSTRUCTION)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP_FILL, _simd_element_type, 8> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
	};}\
	ANVIL_SIMD_SPECIALISE_FILL(4, SSE, _simd_download_4_4, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)\
	ANVIL_SIMD_SPECIALISE_FILL(3, SSE, _simd_download_n_3, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)\
	ANVIL_SIMD_SPECIALISE_FILL(2, SSE, _simd_download_n_2, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)

#define ANVIL_SIMD_SPECIALISE_FILL_2(INSTRUCTION)\
	namespace detail { template<>\
	struct OperationInstructionSet<OP_FILL, _simd_element_type, 2> {\
		enum : int64_t  { value = IS_## INSTRUCTION };\
	};}\
	ANVIL_SIMD_SPECIALISE_FILL(2, SSE, _simd_download_2_2, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)

#define _simd_round_ps(X) _mm_round_ps(X,_MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC)
#define _simd_round_pd(X) _mm_round_pd(X,_MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC)

#define _simd_element_type float
#define _simd_type __m128
#define _simd_data(X) X.m128_f32
#define _simd_load(X) _mm_load_ps(X)
#define _simd_set(X,Y,Z,W) _mm_set_ps(X,Y,Z,W)
#define _simd_fill_0() _mm_setzero_ps()
#define _simd_fill_1(X) _mm_set1_ps(X)
#define _simd_fill_2(X,Y) _mm_set_ps(X,Y,0.f,0.f)
#define _simd_fill_3(X,Y,Z) _mm_set_ps(X,Y,Z,0.f)
#define _simd_fill_4(X,Y,Z,W) _mm_set_ps(X,Y,Z,W)
	ANVIL_SIMD_SPECIALISE_FILL_4(SSE)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_ADD,   SSE,     _mm_add_ps,     ANVIL_SIMD_ADD)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_SUB,   SSE,     _mm_sub_ps,     ANVIL_SIMD_SUB)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_MUL,   SSE,     _mm_mul_ps,     ANVIL_SIMD_MUL)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_DIV,   SSE,     _mm_div_ps,     ANVIL_SIMD_DIV)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_AND,   SSE,     _mm_and_ps,     ANVIL_SIMD_AND_F)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_OR,    SSE,     _mm_or_ps,      ANVIL_SIMD_OR_F)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_XOR,   SSE,     _mm_xor_ps,     ANVIL_SIMD_XOR_F)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_MIN,   SSE,     _mm_min_ps,     std::min)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_MAX,   SSE,     _mm_max_ps,     std::max)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_CMPEQ, SSE,     _mm_cmpeq_ps,   ANVIL_SIMD_CMPEQ)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_CMPNE, SSE,     _mm_cmpneq_ps,  ANVIL_SIMD_CMPNE)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_CMPLT, SSE,     _mm_cmplt_ps,   ANVIL_SIMD_CMPLT)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_CMPGT, SSE,     _mm_cmpgt_ps,   ANVIL_SIMD_CMPGT)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_CMPLE, SSE,     _mm_cmple_ps,   ANVIL_SIMD_CMPLE)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_CMPGE, SSE,     _mm_cmpge_ps,   ANVIL_SIMD_CMPGE)
	ANVIL_SIMD_IMPLEMENTATION_V_V_4( OP_CEIL,  SSE_4_1, _mm_ceil_ps,    std::ceil)
	ANVIL_SIMD_IMPLEMENTATION_V_V_4( OP_FLOOR, SSE_4_1, _mm_floor_ps,   std::ceil)
	ANVIL_SIMD_IMPLEMENTATION_V_V_4( OP_ROUND, SSE_4_1, _simd_round_ps, std::round)
	ANVIL_SIMD_IMPLEMENTATION_V_V_4( OP_SQRT,  SSE,     _mm_sqrt_ps,    std::sqrt)
#undef _simd_element_type
#undef _simd_type
#undef _simd_data
#undef _simd_load
#undef _simd_set
#undef _simd_fill_0
#undef _simd_fill_1
#undef _simd_fill_2
#undef _simd_fill_3
#undef _simd_fill_4

#define _simd_element_type double
#define _simd_type __m128d
#define _simd_data(X) X.m128d_f64
#define _simd_load(X) _mm_load_pd(X)
#define _simd_set(X,Y) _mm_set_pd(X,Y)
#define _simd_fill_0() _mm_setzero_pd()
#define _simd_fill_1(X) _mm_set1_pd(X)
#define _simd_fill_2(X,Y) _mm_set_pd(X,Y)
#define _simd_fill_3(X,Y,Z) _mm_set_pd(X,Y)
#define _simd_fill_4(X,Y,Z,W) _mm_set_pd(X,Y)
	ANVIL_SIMD_SPECIALISE_FILL_2(SSE_2)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_ADD,   SSE_2,   _mm_add_pd,     ANVIL_SIMD_ADD)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_SUB,   SSE_2,   _mm_sub_pd,     ANVIL_SIMD_SUB)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_MUL,   SSE_2,   _mm_mul_pd,     ANVIL_SIMD_MUL)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_DIV,   SSE_2,   _mm_div_pd,     ANVIL_SIMD_DIV)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_AND,   SSE_2,   _mm_and_pd,     ANVIL_SIMD_AND_D)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_OR,    SSE_2,   _mm_or_pd,      ANVIL_SIMD_OR_D)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_XOR,   SSE_2,   _mm_xor_pd,     ANVIL_SIMD_XOR_D)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_MIN,   SSE_2,   _mm_min_pd,     std::min)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_MAX,   SSE_2,   _mm_max_pd,     std::max)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_CMPEQ, SSE_2,   _mm_cmpeq_pd,   ANVIL_SIMD_CMPEQ)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_CMPNE, SSE_2,   _mm_cmpneq_pd,  ANVIL_SIMD_CMPNE)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_CMPLT, SSE_2,   _mm_cmplt_pd,   ANVIL_SIMD_CMPLT)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_CMPGT, SSE_2,   _mm_cmpgt_pd,   ANVIL_SIMD_CMPGT)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_CMPLE, SSE_2,   _mm_cmple_pd,   ANVIL_SIMD_CMPLE)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_CMPGE, SSE_2,   _mm_cmpge_pd,   ANVIL_SIMD_CMPGE)
	ANVIL_SIMD_IMPLEMENTATION_V_V_2( OP_CEIL,  SSE_4_1, _mm_ceil_pd,    std::ceil)
	ANVIL_SIMD_IMPLEMENTATION_V_V_2( OP_FLOOR, SSE_4_1, _mm_floor_pd,   std::ceil)
	ANVIL_SIMD_IMPLEMENTATION_V_V_2( OP_ROUND, SSE_4_1, _simd_round_pd, std::round)
	ANVIL_SIMD_IMPLEMENTATION_V_V_2( OP_SQRT,  SSE_2,   _mm_sqrt_pd,    std::sqrt)
#undef _simd_element_type
#undef _simd_type
#undef _simd_data
#undef _simd_load
#undef _simd_set
#undef _simd_fill_0
#undef _simd_fill_1
#undef _simd_fill_2
#undef _simd_fill_3
#undef _simd_fill_4

#define _simd_element_type int64_t
#define _simd_type __m128i
#define _simd_data(X) X.m128i_i64
#define _simd_load(X) _mm_load_si128(reinterpret_cast<const _simd_type*>(X))
#define _simd_set(X,Y) _mm_set_epi32(reinterpret_cast<const int32_t*>(&X)[0],reinterpret_cast<const int32_t*>(&X)[1],reinterpret_cast<const int32_t*>(&Y)[0],reinterpret_cast<const int32_t*>(&Y)[1])
#define _simd_fill_0() _mm_setzero_si128()
#define _simd_fill_1(X) _mm_set_epi32(reinterpret_cast<const int32_t*>(&X)[0],reinterpret_cast<const int32_t*>(&X)[1], reinterpret_cast<const int32_t*>(&X)[0],reinterpret_cast<const int32_t*>(&X)[1])
#define _simd_fill_2(X,Y) _mm_set_epi32(reinterpret_cast<const int32_t*>(&X)[0],reinterpret_cast<const int32_t*>(&X)[1], reinterpret_cast<const int32_t*>(&Y)[0],reinterpret_cast<const int32_t*>(&Y)[1])
#define _simd_fill_3(X,Y,Z) _mm_set_epi32(reinterpret_cast<const int32_t*>(&X)[0],reinterpret_cast<const int32_t*>(&X)[1], reinterpret_cast<const int32_t*>(&Y)[0],reinterpret_cast<const int32_t*>(&Y)[1])
#define _simd_fill_4(X,Y,Z,W) _mm_set_epi32(reinterpret_cast<const int32_t*>(&X)[0],reinterpret_cast<const int32_t*>(&X)[1], reinterpret_cast<const int32_t*>(&Y)[0],reinterpret_cast<const int32_t*>(&Y)[1])
		ANVIL_SIMD_SPECIALISE_FILL_2(SSE_2)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_ADD, SSE_2, _mm_add_epi64, ANVIL_SIMD_ADD)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_SUB, SSE_2, _mm_sub_epi64, ANVIL_SIMD_SUB)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_AND, SSE_2, _mm_and_si128, ANVIL_SIMD_AND)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_OR,  SSE_2, _mm_or_si128,  ANVIL_SIMD_OR)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_XOR, SSE_2, _mm_xor_si128, ANVIL_SIMD_XOR)
#undef _simd_element_type
#undef _simd_type
#undef _simd_data
#undef _simd_load
#undef _simd_set
#undef _simd_fill_0
#undef _simd_fill_1
#undef _simd_fill_2
#undef _simd_fill_3
#undef _simd_fill_4

#define _simd_element_type uint64_t
#define _simd_type __m128i
#define _simd_data(X) X.m128i_u64
#define _simd_load(X) _mm_load_si128(reinterpret_cast<const _simd_type*>(X))
#define _simd_set(X,Y) _mm_set_epi32(reinterpret_cast<const int32_t*>(&X)[0],reinterpret_cast<const int32_t*>(&X)[1],reinterpret_cast<const int32_t*>(&Y)[0],reinterpret_cast<const int32_t*>(&Y)[1])
#define _simd_fill_0() _mm_setzero_si128()
#define _simd_fill_1(X) _mm_set_epi32(reinterpret_cast<const int32_t*>(&X)[0],reinterpret_cast<const int32_t*>(&X)[1], reinterpret_cast<const int32_t*>(&X)[0],reinterpret_cast<const int32_t*>(&X)[1])
#define _simd_fill_2(X,Y) _mm_set_epi32(reinterpret_cast<const int32_t*>(&X)[0],reinterpret_cast<const int32_t*>(&X)[1], reinterpret_cast<const int32_t*>(&Y)[0],reinterpret_cast<const int32_t*>(&Y)[1])
#define _simd_fill_3(X,Y,Z) _mm_set_epi32(reinterpret_cast<const int32_t*>(&X)[0],reinterpret_cast<const int32_t*>(&X)[1], reinterpret_cast<const int32_t*>(&Y)[0],reinterpret_cast<const int32_t*>(&Y)[1])
#define _simd_fill_4(X,Y,Z,W) _mm_set_epi32(reinterpret_cast<const int32_t*>(&X)[0],reinterpret_cast<const int32_t*>(&X)[1], reinterpret_cast<const int32_t*>(&Y)[0],reinterpret_cast<const int32_t*>(&Y)[1])
		ANVIL_SIMD_SPECIALISE_FILL_2(SSE_2)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_AND, SSE_2, _mm_and_si128, ANVIL_SIMD_AND)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_OR,  SSE_2, _mm_or_si128,  ANVIL_SIMD_OR)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP_XOR, SSE_2, _mm_xor_si128, ANVIL_SIMD_XOR)
#undef _simd_element_type
#undef _simd_type
#undef _simd_data
#undef _simd_load
#undef _simd_set
#undef _simd_fill_0
#undef _simd_fill_1
#undef _simd_fill_2
#undef _simd_fill_3
#undef _simd_fill_4

#define _simd_element_type int32_t
#define _simd_type __m128i
#define _simd_data(X) X.m128i_i32
#define _simd_load(X) _mm_load_si128(reinterpret_cast<const _simd_type*>(X))
#define _simd_set(X,Y,Z,W) _mm_set_epi32(X,Y,Z,W)
#define _simd_fill_0() _mm_setzero_si128()
#define _simd_fill_1(X) _mm_set1_epi32(X)
#define _simd_fill_2(X,Y) _mm_set_epi32(X,Y,0,0)
#define _simd_fill_3(X,Y,Z) _mm_set_epi32(X,Y,Z,0)
#define _simd_fill_4(X,Y,Z,W) _mm_set_epi32(X,Y,Z,W)
		ANVIL_SIMD_SPECIALISE_FILL_4(SSE_2)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_ADD,   SSE_2,   _mm_add_epi32,   ANVIL_SIMD_ADD)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_SUB,   SSE_2,   _mm_sub_epi32,   ANVIL_SIMD_SUB)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_MUL,   SSE_4_1, _mm_mullo_epi32, ANVIL_SIMD_SUB)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_AND,   SSE_2,   _mm_and_si128,   ANVIL_SIMD_AND)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_OR,    SSE_2,   _mm_or_si128,    ANVIL_SIMD_OR)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_XOR,   SSE_2,   _mm_xor_si128,   ANVIL_SIMD_XOR)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_MIN,   SSE_4_1, _mm_min_epi32,   std::min)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_MAX,   SSE_4_1, _mm_max_epi32,   std::max)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_CMPEQ, SSE_2,   _mm_cmpeq_epi32, ANVIL_SIMD_CMPEQ)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_CMPLT, SSE_2,   _mm_cmplt_epi32, ANVIL_SIMD_CMPLT)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_CMPGT, SSE_2,   _mm_cmpgt_epi32, ANVIL_SIMD_CMPGT)
		ANVIL_SIMD_IMPLEMENTATION_V_V_4( OP_ABS,   SSSE_3,  _mm_abs_epi32,   std::abs)
#undef _simd_element_type
#undef _simd_type
#undef _simd_data
#undef _simd_load
#undef _simd_set
#undef _simd_fill_0
#undef _simd_fill_1
#undef _simd_fill_2
#undef _simd_fill_3
#undef _simd_fill_4

#define _simd_element_type uint32_t
#define _simd_type __m128i
#define _simd_data(X) X.m128i_u32
#define _simd_load(X) _mm_load_si128(reinterpret_cast<const _simd_type*>(X))
#define _simd_set(X,Y,Z,W) _mm_set_epi32(value_cast<int32_t>(X), value_cast<int32_t>(Y), value_cast<int32_t>(Z), value_cast<int32_t>(W))
#define _simd_fill_0() _mm_setzero_si128()
#define _simd_fill_1(X) _mm_set1_epi32(value_cast<int32_t>(X))
#define _simd_fill_2(X,Y) _mm_set_epi32(value_cast<int32_t>(X),value_cast<int32_t>(Y),0,0)
#define _simd_fill_3(X,Y,Z) _mm_set_epi32(value_cast<int32_t>(X),value_cast<int32_t>(Y),value_cast<int32_t>(Z),0)
#define _simd_fill_4(X,Y,Z,W) _mm_set_epi32(value_cast<int32_t>(X),value_cast<int32_t>(Y),value_cast<int32_t>(Z),value_cast<int32_t>(W))
		ANVIL_SIMD_SPECIALISE_FILL_4(SSE_2)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_AND, SSE_2,   _mm_and_si128, ANVIL_SIMD_AND)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_OR,  SSE_2,   _mm_or_si128,  ANVIL_SIMD_OR)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_XOR, SSE_2,   _mm_xor_si128, ANVIL_SIMD_XOR)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_MIN, SSE_4_1, _mm_min_epu32, std::min)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_MAX, SSE_4_1, _mm_max_epu32, std::max)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_CMPEQ, SSE_2, _mm_cmpeq_epi32, ANVIL_SIMD_CMPEQ)
#undef _simd_element_type
#undef _simd_type
#undef _simd_data
#undef _simd_load
#undef _simd_set
#undef _simd_fill_0
#undef _simd_fill_1
#undef _simd_fill_2
#undef _simd_fill_3
#undef _simd_fill_4

#define _simd_element_type int16_t
#define _simd_type __m128i
#define _simd_data(X) X.m128i_i16
#define _simd_load(X) _mm_load_si128(reinterpret_cast<const _simd_type*>(X))
#define _simd_set(X,Y,Z,W, A,B,C,D) _mm_set_epi16(X,Y,Z,W, A,B,C,D)
#define _simd_fill_0() _mm_setzero_si128()
#define _simd_fill_1(X) _mm_set1_epi16(X)
#define _simd_fill_2(X,Y) _mm_set_epi16(X,Y,0,0,0,0,0,0)
#define _simd_fill_3(X,Y,Z) _mm_set_epi16(X,Y,Z,0,0,0,0,0)
#define _simd_fill_4(X,Y,Z,W) _mm_set_epi16(X,Y,Z,W,0,0,0,0)
	ANVIL_SIMD_SPECIALISE_FILL_8(SSE_2)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_ADD, SSE_2,   _mm_add_epi16,   ANVIL_SIMD_ADD)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_SUB, SSE_2,   _mm_sub_epi16,   ANVIL_SIMD_SUB)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_MUL, SSE_2,   _mm_mullo_epi16, ANVIL_SIMD_SUB)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_AND, SSE_2,   _mm_and_si128,   ANVIL_SIMD_AND)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_OR,  SSE_2,   _mm_or_si128,    ANVIL_SIMD_OR)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_XOR, SSE_2,   _mm_xor_si128,   ANVIL_SIMD_XOR)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_MAX, SSE_2,   _mm_max_epi16,   std::max)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_MIN, SSE_2,   _mm_min_epi16,   std::min)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_CMPEQ, SSE_2, _mm_cmpeq_epi16, ANVIL_SIMD_CMPEQ)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_CMPLT, SSE_2, _mm_cmplt_epi16, ANVIL_SIMD_CMPLT)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_CMPGT, SSE_2, _mm_cmpgt_epi16, ANVIL_SIMD_CMPGT)
	ANVIL_SIMD_IMPLEMENTATION_V_V_8( OP_ABS, SSSE_3,  _mm_abs_epi16,   std::abs)
#undef _simd_element_type
#undef _simd_type
#undef _simd_data
#undef _simd_load
#undef _simd_set
#undef _simd_fill_0
#undef _simd_fill_1
#undef _simd_fill_2
#undef _simd_fill_3
#undef _simd_fill_4

#define _simd_element_type uint16_t
#define _simd_type __m128i
#define _simd_data(X) X.m128i_u16
#define _simd_load(X) _mm_load_si128(reinterpret_cast<const _simd_type*>(X))
#define _simd_set(X,Y,Z,W, A,B,C,D) _mm_set_epi16(X,Y,Z,W, A,B,C,D)
#define _simd_fill_0() _mm_setzero_si128()
#define _simd_fill_1(X) _mm_set1_epi16(value_cast<int16_t>(X))
#define _simd_fill_2(X,Y) _mm_set_epi16(value_cast<int16_t>(X),value_cast<int16_t>(Y),0,0,0,0,0,0)
#define _simd_fill_3(X,Y,Z) _mm_set_epi16(value_cast<int16_t>(X),value_cast<int16_t>(Y),value_cast<int16_t>(Z),0,0,0,0,0)
#define _simd_fill_4(X,Y,Z,W) _mm_set_epi16(value_cast<int16_t>(X),value_cast<int16_t>(Y),value_cast<int16_t>(Z),value_cast<int16_t>(W),0,0,0,0)
	ANVIL_SIMD_SPECIALISE_FILL_8(SSE_2)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_ADD,   SSE_2,   _mm_adds_epu16, ANVIL_SIMD_ADD)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_SUB,   SSE_2,   _mm_subs_epu16, ANVIL_SIMD_SUB)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_AND,   SSE_2,   _mm_and_si128,  ANVIL_SIMD_AND)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_OR,    SSE_2,   _mm_or_si128,   ANVIL_SIMD_OR)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_XOR,   SSE_2,   _mm_xor_si128,  ANVIL_SIMD_XOR)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_CMPEQ, SSE_2, _mm_cmpeq_epi16, ANVIL_SIMD_CMPEQ)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_MIN,   SSE_4_1, _mm_min_epu16,  std::min)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP_MAX,   SSE_4_1, _mm_max_epu16,  std::max)
#undef _simd_element_type
#undef _simd_type
#undef _simd_data
#undef _simd_load
#undef _simd_set
#undef _simd_fill_0
#undef _simd_fill_1
#undef _simd_fill_2
#undef _simd_fill_3
#undef _simd_fill_4

#define _simd_element_type int8_t
#define _simd_type __m128i
#define _simd_data(X) X.m128i_i8
#define _simd_load(X) _mm_load_si128(reinterpret_cast<const _simd_type*>(X))
#define _simd_set(X,Y,Z,W, A,B,C,D, E,F,G,H, I,J,L,M) _mm_set_epi8(X,Y,Z,W, A,B,C,D, E,F,G,H, I,J,L,M)
#define _simd_fill_0() _mm_setzero_si128()
#define _simd_fill_1(X) _mm_set1_epi8(X)
#define _simd_fill_2(X,Y) _mm_set_epi8(X,Y,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
#define _simd_fill_3(X,Y,Z) _mm_set_epi8(X,Y,Z,0,0,0,0,0,0,0,0,0,0,0,0,0)
#define _simd_fill_4(X,Y,Z,W) _mm_set_epi8(X,Y,Z,W,0,0,0,0,0,0,0,0,0,0,0,0)
		ANVIL_SIMD_SPECIALISE_FILL_16(SSE_2)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_ADD,   SSE_2,   _mm_adds_epi8,  ANVIL_SIMD_ADD)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_SUB,   SSE_2,   _mm_subs_epi8,  ANVIL_SIMD_SUB)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_AND,   SSE_2,   _mm_and_si128,  ANVIL_SIMD_AND)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_OR,    SSE_2,   _mm_or_si128,   ANVIL_SIMD_OR)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_XOR,   SSE_2,   _mm_xor_si128,  ANVIL_SIMD_XOR)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_MIN,   SSE_4_1, _mm_min_epi8,   std::min)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_MAX,   SSE_4_1, _mm_max_epi8,   std::max)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_CMPEQ, SSE_2,   _mm_cmpeq_epi8, ANVIL_SIMD_CMPEQ)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_CMPLT, SSE_2,   _mm_cmplt_epi8, ANVIL_SIMD_CMPLT)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_CMPGT, SSE_2,   _mm_cmpgt_epi8, ANVIL_SIMD_CMPGT)
		ANVIL_SIMD_IMPLEMENTATION_V_V_16( OP_ABS,   SSSE_3,  _mm_abs_epi8,   std::abs)
#undef _simd_element_type
#undef _simd_type
#undef _simd_data
#undef _simd_load
#undef _simd_set
#undef _simd_fill_0
#undef _simd_fill_1
#undef _simd_fill_2
#undef _simd_fill_3
#undef _simd_fill_4

#define _simd_element_type uint8_t
#define _simd_type __m128i
#define _simd_data(X) X.m128i_u8
#define _simd_load(X) _mm_load_si128(reinterpret_cast<const _simd_type*>(X))
#define _simd_set(X,Y,Z,W, A,B,C,D, E,F,G,H, I,J,L,M) _mm_set_epi8(X,Y,Z,W, A,B,C,D, E,F,G,H, I,J,L,M)
#define _simd_fill_0() _mm_setzero_si128()
#define _simd_fill_1(X) _mm_set1_epi8(value_cast<int8_t>(X))
#define _simd_fill_2(X,Y) _mm_set_epi8(value_cast<int8_t>(X),value_cast<int8_t>(Y),0,0,0,0,0,0,0,0,0,0,0,0,0,0)
#define _simd_fill_3(X,Y,Z) _mm_set_epi8(value_cast<int8_t>(X),value_cast<int8_t>(Y),value_cast<int8_t>(Z),0,0,0,0,0,0,0,0,0,0,0,0,0)
#define _simd_fill_4(X,Y,Z,W) _mm_set_epi8(value_cast<int8_t>(X),value_cast<int8_t>(Y),value_cast<int8_t>(Z),value_cast<int8_t>(W),0,0,0,0,0,0,0,0,0,0,0,0)
		ANVIL_SIMD_SPECIALISE_FILL_16(SSE_2)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_ADD,   SSE_2, _mm_adds_epu8,  ANVIL_SIMD_ADD)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_SUB,   SSE_2, _mm_subs_epu8,  ANVIL_SIMD_SUB)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_AND,   SSE_2, _mm_and_si128,  ANVIL_SIMD_AND)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_OR,    SSE_2, _mm_or_si128,   ANVIL_SIMD_OR)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_XOR,   SSE_2, _mm_xor_si128,  ANVIL_SIMD_XOR)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_CMPEQ, SSE_2, _mm_cmpeq_epi8, ANVIL_SIMD_CMPEQ)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_MAX,   SSE_2, _mm_max_epu8,   std::max)
		ANVIL_SIMD_IMPLEMENTATION_V_VV_16(OP_MIN,   SSE_2, _mm_min_epu8,   std::min)
#undef _simd_element_type
#undef _simd_type
#undef _simd_data
#undef _simd_load
#undef _simd_set
#undef _simd_fill_0
#undef _simd_fill_1
#undef _simd_fill_2
#undef _simd_fill_3
#undef _simd_fill_4

#endif
}}

#endif