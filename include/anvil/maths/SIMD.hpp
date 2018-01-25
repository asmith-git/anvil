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

	enum InstructionSet {
		IS_NONE,
#ifdef ANVIL_USE_INTEL_SIMD_INTRINSICS
		IS_MMX,
		IS_SSE,
		IS_SSE_2,
		IS_SSE_3,
		IS_SSSE_3,
		IS_SSE_4_1,
		IS_SSE_4_2,
		IS_AVX,
		IS_FMA,
		IS_AVX_2,
		IS_KNC,
		IS_AVX_512
#endif
	};

	static ANVIL_STRONG_INLINE bool ANVIL_CALL IsInstructionSetSupported(InstructionSet aSet) {
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
		default:
			return false;
		}
#else
		return false;
#endif
	}

#ifdef ANVIL_USE_INTEL_SIMD_INTRINSICS
	static const bool ANVIL_USE_MMX        = IsInstructionSetSupported(IS_MMX);
	static const bool ANVIL_USE_SSE        = IsInstructionSetSupported(IS_SSE);
	static const bool ANVIL_USE_SSE_2      = IsInstructionSetSupported(IS_SSE_2);
	static const bool ANVIL_USE_SSE_3      = IsInstructionSetSupported(IS_SSE_3);
	static const bool ANVIL_USE_SSSE_3     = IsInstructionSetSupported(IS_SSSE_3);
	static const bool ANVIL_USE_SSE_4_1    = IsInstructionSetSupported(IS_SSE_4_1);
	static const bool ANVIL_USE_SSE_4_2    = IsInstructionSetSupported(IS_SSE_4_2);
	static const bool ANVIL_USE_AVX        = IsInstructionSetSupported(IS_AVX);
	static const bool ANVIL_USE_FMA        = IsInstructionSetSupported(IS_FMA);
	static const bool ANVIL_USE_AVX_2      = IsInstructionSetSupported(IS_AVX_2);
	static const bool ANVIL_USE_KNC        = IsInstructionSetSupported(IS_KNC);
	static const bool ANVIL_USE_AVX_512    = IsInstructionSetSupported(IS_AVX_512);
#endif

	// Operation definitions

	enum Operation {
		// Misc operations
		OP_FILL, OP_CAST, OP_RESIZE,
		// 3 parameters
		OP_FMA, OP_FMS,
		// 2 parameters
		OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_MIN, OP_MAX, OP_AND, OP_OR, OP_XOR, OP_LSHIFT, OP_RSHIFT, OP_MOD, 
		OP_DIM, OP_CMPEQ, OP_CMPNE, OP_CMPLT, OP_CMPGT, OP_CMPLE, OP_CMPGE, OP_ATAN2, OP_REFLECT,
		// 1 parameter
		OP_NOT, OP_ABS, OP_EXP, OP_LOG, OP_LOG2, OP_LOG10, OP_CEIL, OP_FLOOR, OP_ROUND, OP_SIN, OP_COS, 
		OP_TAN, OP_ASIN, OP_ACOS, OP_ATAN, OP_COSH, OP_SINH, OP_TANH, OP_SQRT, OP_CBRT,
		// 1 Parameter, scalar output
		OP_AVG, OP_SUM, OP_POPCN
	};

	template<Operation O, class T> struct OptimalOperationSize {
		enum { value = 2 };
	};

	template<Operation O>
	struct OperationParams {
		enum { value = 0 };
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

		static simd_t ANVIL_CALL setu() {
			return simd_t();
		}

		static simd_t ANVIL_CALL set0() {
			simd_t tmp;
			memset(&tmp, sizeof(T) * S);
			return tmp;
		}

		static simd_t ANVIL_CALL set1(T x) {
			simd_t tmp;
			for (size_t i = 0; i < S; ++i) tmp.elements[i] = x;
			return tmp;
		}

		static simd_t ANVIL_CALL set2(T x, T y) {
			simd_t tmp = S > 2 ? load_0 : simd_t();
			tmp.elements[0] = x;
			if (S >= 2) tmp.elements[1] = y;
			return tmp;
		}

		static simd_t ANVIL_CALL set3(T x, T y, T z) {
			simd_t tmp = S > 3 ? load_0 : simd_t();
			tmp.elements[0] = x;
			if (S >= 2) tmp.elements[1] = y;
			if (S >= 3) tmp.elements[2] = z;
			return tmp;
		}

		static simd_t ANVIL_CALL set4(T x, T y, T z, T w) {
			simd_t tmp = S > 3 ? load_0 : simd_t();
			tmp.elements[0] = x;
			if (S >= 2) tmp.elements[1] = y;
			if (S >= 3) tmp.elements[2] = z;
			if (S >= 4) tmp.elements[3] = w;
			return tmp;
		}
	};

	// Default Operation Implementation

	template<class T, size_t S, Operation O>
	struct OperationImplementation {
		enum { 
			PARAMS = OperationParams<O>::value,
			OPTIMAL = OptimalOperationSize<O,T>::value,
			LOOP = S / OPTIMAL,
			REMAINDER = S % OPTIMAL
		};

		typedef OperationImplementation<T, OPTIMAL, O> optimal_t;

		static void ANVIL_CALL execute(const T* x, const T* y, T* o) {
			if (optimal_t::optimised()) {
				for (size_t i = 0; i < LOOP; ++i) {
					optimal_t::execute_op(x, y, o);
					x += OPTIMAL;
					y += OPTIMAL;
					o += OPTIMAL;
				}
			} else {
				for (size_t i = 0; i < LOOP; ++i) {
					optimal_t::execute_nop(x, y, o);
					x += OPTIMAL;
					y += OPTIMAL;
					o += OPTIMAL;
				}
			}
			for (size_t i = 0; i < REMAINDER; ++i) {
				o[i] = OperationImplementation<T, 1, O>::execute(*x, *y);
				++x;
				++y;
				++o;
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

	#define ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,SIZE,INSTRUCTION,UPLOAD,DOWNLOAD,FUNCTION1,FUNCTION2)\
	template<>\
	struct OperationImplementation<_simd_element_type, SIZE, OP> {\
		typedef _simd_type simd_t;\
		static ANVIL_STRONG_INLINE bool ANVIL_CALL optimised() {\
			return ANVIL_USE_ ## INSTRUCTION;\
		}\
		static ANVIL_STRONG_INLINE _simd_type ANVIL_CALL execute_in(simd_t x, simd_t y) {\
			return FUNCTION1(x,y);\
		}\
		static ANVIL_STRONG_INLINE void ANVIL_CALL execute_op(const _simd_element_type* x, const _simd_element_type* y, _simd_element_type* o) {\
			DOWNLOAD(o,execute_in(UPLOAD(x), UPLOAD(y)));\
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

	#define ANVIL_SIMD_IMPLEMENTATION_V_V(OP,SIZE,INSTRUCTION,UPLOAD,DOWNLOAD,FUNCTION1,FUNCTION2)\
	template<>\
	struct OperationImplementation<_simd_element_type, SIZE, OP> {\
		typedef _simd_type simd_t;\
		static ANVIL_STRONG_INLINE bool ANVIL_CALL optimised() {\
			return ANVIL_USE_ ## INSTRUCTION;\
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
			return ANVIL_USE_ ## INSTRUCTION;\
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
	template<> struct OptimalOperationSize<OP,_simd_element_type> { enum { value = 16 }; };\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,16,INSTRUCTION, _simd_upload_16_16, _simd_download_16_16, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,15,INSTRUCTION, _simd_upload_16_15, _simd_download_n_15, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,14,INSTRUCTION, _simd_upload_16_14, _simd_download_n_14, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,13,INSTRUCTION, _simd_upload_16_13, _simd_download_n_13, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,12,INSTRUCTION, _simd_upload_16_12, _simd_download_n_12, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,11,INSTRUCTION, _simd_upload_16_11, _simd_download_n_11, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,10,INSTRUCTION, _simd_upload_16_10, _simd_download_n_10, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,9, INSTRUCTION, _simd_upload_16_9,  _simd_download_n_9,  FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,8, INSTRUCTION, _simd_upload_16_8,  _simd_download_n_8,  FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,7, INSTRUCTION, _simd_upload_16_7,  _simd_download_n_7,  FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,6, INSTRUCTION, _simd_upload_16_6,  _simd_download_n_6,  FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,5, INSTRUCTION, _simd_upload_16_5,  _simd_download_n_5,  FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,4, INSTRUCTION, _simd_upload_16_4,  _simd_download_n_4,  FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,3, INSTRUCTION, _simd_upload_16_3,  _simd_download_n_3,  FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,2, INSTRUCTION, _simd_upload_16_2,  _simd_download_n_2,  FUNCTION1, FUNCTION2)

#define ANVIL_SIMD_IMPLEMENTATION_V_VV_8(OP,INSTRUCTION, FUNCTION1, FUNCTION2)\
	template<> struct OptimalOperationSize<OP,_simd_element_type> { enum { value = 8 }; };\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,8,INSTRUCTION, _simd_upload_8_8, _simd_download_8_8, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,7,INSTRUCTION, _simd_upload_8_7, _simd_download_n_7, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,6,INSTRUCTION, _simd_upload_8_6, _simd_download_n_6, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,5,INSTRUCTION, _simd_upload_8_5, _simd_download_n_5, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,4,INSTRUCTION, _simd_upload_8_4, _simd_download_n_4, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,3,INSTRUCTION, _simd_upload_8_3, _simd_download_n_3, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,2,INSTRUCTION, _simd_upload_8_2, _simd_download_n_2, FUNCTION1, FUNCTION2)

#define ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP,INSTRUCTION, FUNCTION1, FUNCTION2)\
	template<> struct OptimalOperationSize<OP,_simd_element_type> { enum { value = 4 }; };\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,4,INSTRUCTION, _simd_upload_4_4, _simd_download_4_4, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,3,INSTRUCTION, _simd_upload_4_3, _simd_download_n_3, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,2,INSTRUCTION, _simd_upload_4_2, _simd_download_n_2, FUNCTION1, FUNCTION2)

#define ANVIL_SIMD_IMPLEMENTATION_V_VV_2(OP,INSTRUCTION, FUNCTION1, FUNCTION2)\
	template<> struct OptimalOperationSize<OP,_simd_element_type> { enum { value = 2 }; };\
	ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,2,INSTRUCTION, _simd_upload_2_2, _simd_download_2_2, FUNCTION1, FUNCTION2)

#define ANVIL_SIMD_IMPLEMENTATION_V_V_16(OP,INSTRUCTION, FUNCTION1, FUNCTION2)\
	template<> struct OptimalOperationSize<OP,_simd_element_type> { enum { value = 16 }; };\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,16,INSTRUCTION, _simd_upload_16_16, _simd_download_16_16, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,15,INSTRUCTION, _simd_upload_16_15, _simd_download_n_15, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,14,INSTRUCTION, _simd_upload_16_14, _simd_download_n_14, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,13,INSTRUCTION, _simd_upload_16_13, _simd_download_n_13, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,12,INSTRUCTION, _simd_upload_16_12, _simd_download_n_12, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,11,INSTRUCTION, _simd_upload_16_11, _simd_download_n_11, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,10,INSTRUCTION, _simd_upload_16_10, _simd_download_n_10, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,9, INSTRUCTION, _simd_upload_16_9,  _simd_download_n_9,  FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,8, INSTRUCTION, _simd_upload_16_8,  _simd_download_n_8,  FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,7, INSTRUCTION, _simd_upload_16_7,  _simd_download_n_7,  FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,6, INSTRUCTION, _simd_upload_16_6,  _simd_download_n_6,  FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,5, INSTRUCTION, _simd_upload_16_5,  _simd_download_n_5,  FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,4, INSTRUCTION, _simd_upload_16_4,  _simd_download_n_4,  FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,3, INSTRUCTION, _simd_upload_16_3,  _simd_download_n_3,  FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,2, INSTRUCTION, _simd_upload_16_2,  _simd_download_n_2,  FUNCTION1, FUNCTION2)

#define ANVIL_SIMD_IMPLEMENTATION_V_V_8(OP,INSTRUCTION, FUNCTION1, FUNCTION2)\
	template<> struct OptimalOperationSize<OP,_simd_element_type> { enum { value = 8 }; };\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,8,INSTRUCTION, _simd_upload_8_8, _simd_download_8_8, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,7,INSTRUCTION, _simd_upload_8_7, _simd_download_n_7, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,6,INSTRUCTION, _simd_upload_8_6, _simd_download_n_6, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,5,INSTRUCTION, _simd_upload_8_5, _simd_download_n_5, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,4,INSTRUCTION, _simd_upload_8_4, _simd_download_n_4, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,3,INSTRUCTION, _simd_upload_8_3, _simd_download_n_3, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,2,INSTRUCTION, _simd_upload_8_2, _simd_download_n_2, FUNCTION1, FUNCTION2)

#define ANVIL_SIMD_IMPLEMENTATION_V_V_4(OP,INSTRUCTION, FUNCTION1, FUNCTION2)\
	template<> struct OptimalOperationSize<OP,_simd_element_type> { enum { value = 4 }; };\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,4,INSTRUCTION, _simd_upload_4_4, _simd_download_4_4, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,3,INSTRUCTION, _simd_upload_4_3, _simd_download_n_3, FUNCTION1, FUNCTION2)\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,2,INSTRUCTION, _simd_upload_4_2, _simd_download_n_2, FUNCTION1, FUNCTION2)

#define ANVIL_SIMD_IMPLEMENTATION_V_V_2(OP,INSTRUCTION, FUNCTION1, FUNCTION2)\
	template<> struct OptimalOperationSize<OP,_simd_element_type> { enum { value = 2 }; };\
	ANVIL_SIMD_IMPLEMENTATION_V_V(OP,2,INSTRUCTION, _simd_upload_2_2, _simd_download_2_2, FUNCTION1, FUNCTION2)

#define ANVIL_SIMD_SPECIALISE_FILL_16(INSTRUCTION)\
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
	ANVIL_SIMD_SPECIALISE_FILL(8, SSE, _simd_download_8_8, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)\
	ANVIL_SIMD_SPECIALISE_FILL(7, SSE, _simd_download_n_7, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)\
	ANVIL_SIMD_SPECIALISE_FILL(6, SSE, _simd_download_n_6, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)\
	ANVIL_SIMD_SPECIALISE_FILL(5, SSE, _simd_download_n_5, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)\
	ANVIL_SIMD_SPECIALISE_FILL(4, SSE, _simd_download_n_4, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)\
	ANVIL_SIMD_SPECIALISE_FILL(3, SSE, _simd_download_n_3, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)\
	ANVIL_SIMD_SPECIALISE_FILL(2, SSE, _simd_download_n_2, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)

#define ANVIL_SIMD_SPECIALISE_FILL_4(INSTRUCTION)\
	ANVIL_SIMD_SPECIALISE_FILL(4, SSE, _simd_download_4_4, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)\
	ANVIL_SIMD_SPECIALISE_FILL(3, SSE, _simd_download_n_3, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)\
	ANVIL_SIMD_SPECIALISE_FILL(2, SSE, _simd_download_n_2, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)

#define ANVIL_SIMD_SPECIALISE_FILL_2(INSTRUCTION)\
	ANVIL_SIMD_SPECIALISE_FILL(2, SSE, _simd_download_2_2, _simd_fill_0, _simd_fill_1, _simd_fill_2, _simd_fill_3, _simd_fill_4)

#define _simd_round_ps(X) _mm_round_ps(X,_MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC)
#define _simd_round_pd(X) _mm_round_pd(X,_MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC)

template<>
struct SIMDHelper<double,2> {
	typedef __m128d simd_t;
	static ANVIL_STRONG_INLINE simd_t ANVIL_CALL load(const double* x) { _mm_load_pd(x); }
	static ANVIL_STRONG_INLINE simd_t setu() { return _mm_undefined_pd(); }
	static ANVIL_STRONG_INLINE simd_t set0() { return _mm_setzero_pd(); }
	static ANVIL_STRONG_INLINE simd_t set1(double x) { _mm_set1_pd(x); }
	static ANVIL_STRONG_INLINE simd_t set2(double x, double y) { return _mm_setr_pd(x, y); }
	static ANVIL_STRONG_INLINE simd_t set3(double x, double y, double z) { return set2(x, y); }
	static ANVIL_STRONG_INLINE simd_t set4(double x, double y, double z, double w) { return set2(x, y); }
};

template<>
struct SIMDHelper<int64_t, 2> {
	typedef __m128i simd_t;
	static ANVIL_STRONG_INLINE simd_t ANVIL_CALL load(const int64_t* x) { _mm_load_si128(reinterpret_cast<const __m128i*>(x)); }
	static ANVIL_STRONG_INLINE simd_t setu() { return _mm_undefined_si128(); }
	static ANVIL_STRONG_INLINE simd_t set0() { return _mm_setzero_si128(); }
	static ANVIL_STRONG_INLINE simd_t set1(int64_t x) { _mm_set1_epi64x(x); }
	static ANVIL_STRONG_INLINE simd_t set2(int64_t x, int64_t y) { return _mm_set_epi32(reinterpret_cast<const int32_t*>(&x)[0], reinterpret_cast<const int32_t*>(&x)[1], reinterpret_cast<const int32_t*>(&y)[0], reinterpret_cast<const int32_t*>(&y)[1]); }
	static ANVIL_STRONG_INLINE simd_t set3(int64_t x, int64_t y, int64_t z) { return set2(x, y); }
	static ANVIL_STRONG_INLINE simd_t set4(int64_t x, int64_t y, int64_t z, int64_t w) { return set2(x, y); }
};

template<>
struct SIMDHelper<uint64_t, 2> {
	typedef __m128i simd_t;
	static ANVIL_STRONG_INLINE simd_t ANVIL_CALL load(const uint64_t* x) { _mm_load_si128(reinterpret_cast<const __m128i*>(x)); }
	static ANVIL_STRONG_INLINE simd_t setu() { return _mm_undefined_si128(); }
	static ANVIL_STRONG_INLINE simd_t set0() { return _mm_setzero_si128(); }
	static ANVIL_STRONG_INLINE simd_t set1(uint64_t x) { _mm_set1_epi64x(x); }
	static ANVIL_STRONG_INLINE simd_t set2(uint64_t x, uint64_t y) { return _mm_set_epi32(reinterpret_cast<const int32_t*>(&x)[0], reinterpret_cast<const int32_t*>(&x)[1], reinterpret_cast<const int32_t*>(&y)[0], reinterpret_cast<const int32_t*>(&y)[1]); }
	static ANVIL_STRONG_INLINE simd_t set3(uint64_t x, uint64_t y, uint64_t z) { return set2(x, y); }
	static ANVIL_STRONG_INLINE simd_t set4(uint64_t x, uint64_t y, uint64_t z, uint64_t w) { return set2(x, y); }
};

template<>
struct SIMDHelper<float,4> {
	typedef __m128 simd_t;
	static ANVIL_STRONG_INLINE simd_t ANVIL_CALL load(const float* x) { _mm_load_ps(x); }
	static ANVIL_STRONG_INLINE simd_t setu() { return _mm_undefined_ps(); }
	static ANVIL_STRONG_INLINE simd_t set0() { return _mm_setzero_ps(); }
	static ANVIL_STRONG_INLINE simd_t set1(float x) { _mm_set1_ps(x); }
	static ANVIL_STRONG_INLINE simd_t set2(float x, float y) { return _mm_setr_ps(x, y, 0.f, 0.f); }
	static ANVIL_STRONG_INLINE simd_t set3(float x, float y, float z) { return _mm_setr_ps(x, y, z, 0.f); }
	static ANVIL_STRONG_INLINE simd_t set4(float x, float y, float z, float w) { return _mm_setr_ps(x, y, z, w); }
};

template<>
struct SIMDHelper<int32_t, 4> {
	typedef __m128i simd_t;
	static ANVIL_STRONG_INLINE simd_t ANVIL_CALL load(const int32_t* x) { _mm_load_si128(reinterpret_cast<const __m128i*>(x)); }
	static ANVIL_STRONG_INLINE simd_t setu() { return _mm_undefined_si128(); }
	static ANVIL_STRONG_INLINE simd_t set0() { return _mm_setzero_si128(); }
	static ANVIL_STRONG_INLINE simd_t set1(int32_t x) { _mm_set1_epi32(x); }
	static ANVIL_STRONG_INLINE simd_t set2(int32_t x, int32_t y) { return _mm_setr_epi32(x, y, 0, 0); }
	static ANVIL_STRONG_INLINE simd_t set3(int32_t x, int32_t y, int32_t z) { return _mm_setr_epi32(x, y, z, 0); }
	static ANVIL_STRONG_INLINE simd_t set4(int32_t x, int32_t y, int32_t z, int32_t w) { return _mm_setr_epi32(x, y, z, w); }
};

template<>
struct SIMDHelper<uint32_t, 4> {
	typedef __m128i simd_t;
	static ANVIL_STRONG_INLINE simd_t ANVIL_CALL load(const uint32_t* x) { _mm_load_si128(reinterpret_cast<const __m128i*>(x)); }
	static ANVIL_STRONG_INLINE simd_t setu() { return _mm_undefined_si128(); }
	static ANVIL_STRONG_INLINE simd_t set0() { return _mm_setzero_si128(); }
	static ANVIL_STRONG_INLINE simd_t set1(uint32_t x) { _mm_set1_epi32(x); }
	static ANVIL_STRONG_INLINE simd_t set2(uint32_t x, uint32_t y) { return _mm_setr_epi32(x, y, 0, 0); }
	static ANVIL_STRONG_INLINE simd_t set3(uint32_t x, uint32_t y, uint32_t z) { return _mm_setr_epi32(x, y, z, 0); }
	static ANVIL_STRONG_INLINE simd_t set4(uint32_t x, uint32_t y, uint32_t z, uint32_t w) { return _mm_setr_epi32(x, y, z, w); }
};

template<>
struct SIMDHelper<int16_t, 8> {
	typedef __m128i simd_t;
	static ANVIL_STRONG_INLINE simd_t ANVIL_CALL load(const int16_t* x) { _mm_load_si128(reinterpret_cast<const __m128i*>(x)); }
	static ANVIL_STRONG_INLINE simd_t setu() { return _mm_undefined_si128(); }
	static ANVIL_STRONG_INLINE simd_t set0() { return _mm_setzero_si128(); }
	static ANVIL_STRONG_INLINE simd_t set1(int16_t x) { _mm_set1_epi16(x); }
	static ANVIL_STRONG_INLINE simd_t set2(int16_t x, int16_t y) { return _mm_setr_epi16(x, y, 0, 0, 0, 0, 0, 0); }
	static ANVIL_STRONG_INLINE simd_t set3(int16_t x, int16_t y, int16_t z) { return _mm_setr_epi16(x, y, z, 0, 0, 0, 0, 0); }
	static ANVIL_STRONG_INLINE simd_t set4(int16_t x, int16_t y, int16_t z, int16_t w) { return _mm_setr_epi16(x, y, z, w, 0, 0, 0, 0); }
};

template<>
struct SIMDHelper<uint16_t, 8> {
	typedef __m128i simd_t;
	static ANVIL_STRONG_INLINE simd_t ANVIL_CALL load(const uint16_t* x) { _mm_load_si128(reinterpret_cast<const __m128i*>(x)); }
	static ANVIL_STRONG_INLINE simd_t setu() { return _mm_undefined_si128(); }
	static ANVIL_STRONG_INLINE simd_t set0() { return _mm_setzero_si128(); }
	static ANVIL_STRONG_INLINE simd_t set1(uint16_t x) { _mm_set1_epi16(x); }
	static ANVIL_STRONG_INLINE simd_t set2(uint16_t x, uint16_t y) { return _mm_setr_epi16(x, y, 0, 0, 0, 0, 0, 0); }
	static ANVIL_STRONG_INLINE simd_t set3(uint16_t x, uint16_t y, uint16_t z) { return _mm_setr_epi16(x, y, z, 0, 0, 0, 0, 0); }
	static ANVIL_STRONG_INLINE simd_t set4(uint16_t x, uint16_t y, uint16_t z, uint16_t w) { return _mm_setr_epi16(x, y, z, w, 0, 0, 0, 0); }
};

template<>
struct SIMDHelper<int8_t, 16> {
	typedef __m128i simd_t;
	static ANVIL_STRONG_INLINE simd_t ANVIL_CALL load(const int8_t* x) { _mm_load_si128(reinterpret_cast<const __m128i*>(x)); }
	static ANVIL_STRONG_INLINE simd_t setu() { return _mm_undefined_si128(); }
	static ANVIL_STRONG_INLINE simd_t set0() { return _mm_setzero_si128(); }
	static ANVIL_STRONG_INLINE simd_t set1(int8_t x) { _mm_set1_epi8(x); }
	static ANVIL_STRONG_INLINE simd_t set2(int8_t x, int8_t y) { return _mm_setr_epi8(x, y, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); }
	static ANVIL_STRONG_INLINE simd_t set3(int8_t x, int8_t y, int8_t z) { return _mm_setr_epi8(x, y, z, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); }
	static ANVIL_STRONG_INLINE simd_t set4(int8_t x, int8_t y, int8_t z, int8_t w) { return _mm_setr_epi8(x, y, z, w, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); }
};

template<>
struct SIMDHelper<uint8_t, 16> {
	typedef __m128i simd_t;
	static ANVIL_STRONG_INLINE simd_t ANVIL_CALL load(const uint8_t* x) { _mm_load_si128(reinterpret_cast<const __m128i*>(x)); }
	static ANVIL_STRONG_INLINE simd_t setu() { return _mm_undefined_si128(); }
	static ANVIL_STRONG_INLINE simd_t set0() { return _mm_setzero_si128(); }
	static ANVIL_STRONG_INLINE simd_t set1(uint8_t x) { _mm_set1_epi8(x); }
	static ANVIL_STRONG_INLINE simd_t set2(uint8_t x, uint8_t y) { return _mm_setr_epi8(x, y, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); }
	static ANVIL_STRONG_INLINE simd_t set3(uint8_t x, uint8_t y, uint8_t z) { return _mm_setr_epi8(x, y, z, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); }
	static ANVIL_STRONG_INLINE simd_t set4(uint8_t x, uint8_t y, uint8_t z, uint8_t w) { return _mm_setr_epi8(x, y, z, w, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); }
};

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