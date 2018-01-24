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

#include <cmath>
#include "anvil/core/Cpu.hpp"
#include "anvil/core/Keywords.hpp"

#if ANVIL_ARCHITECTURE == ANVIL_X86 || ANVIL_ARCHITECTURE == ANVIL_X64
	#define ANVIL_USE_INTEL_SIMD_INTRINSICS
	#include "immintrin.h"
#endif

namespace anvil { namespace simd {

	// Instruction set definitions

	enum InstructionSet {
		IS_NONE,
#ifdef ANVIL_USE_INTEL_SIMD_INTRINSICS
#if ANVIL_CPP_VER < 2011
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
#else
		IS_MMX     = _FEATURE_MMX,
		IS_SSE     = _FEATURE_SSE,
		IS_SSE_2   = _FEATURE_SSE2,
		IS_SSE_3   = _FEATURE_SSE3,
		IS_SSSE_3  = _FEATURE_SSSE3,
		IS_SSE_4_1 = _FEATURE_SSE4_1,
		IS_SSE_4_2 = _FEATURE_SSE4_2,
		IS_AVX     = _FEATURE_AVX,
		IS_FMA     = _FEATURE_FMA,
		IS_AVX_2   = _FEATURE_AVX2,
		IS_KNC     = _FEATURE_KNCNI,
		IS_AVX_512 = _FEATURE_AVX512F | _FEATURE_AVX512ER | _FEATURE_AVX512PF | _FEATURE_AVX512CD
#endif
#endif
	};

	static ANVIL_STRONG_INLINE bool ANVIL_CALL IsInstructionSetSupported(InstructionSet aSet) {
#ifdef ANVIL_USE_INTEL_SIMD_INTRINSICS
#if ANVIL_CPP_VER < 2011
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
		return _may_i_use_cpu_feature(aSet);
#endif
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

	template<Operation O, class T, size_t S> struct OperationSupport {
		enum { value = IS_NONE };
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

	// Default Operation Implementation

	template<class T, size_t S, Operation O>
	struct OperationImplementation {
		enum { 
			PARAMS = OperationParams<O>::value,
			OPTIMAL = OptimalOperationSize<O,T>::value,
			LOOP = S / OPTIMAL,
			REMAINDER = S % OPTIMAL,
		};

		static void ANVIL_CALL execute(const void* x, const void* y, void* o) {
			const T* const a = static_cast<const T*>(x);
			const T* const b = static_cast<const T*>(y);
			T* const o_ = static_cast<T*>(o);
			size_t offset = 0;
			for (size_t i = 0; i < LOOP; ++i) {
				OperationImplementation<T, OPTIMAL, O>::execute(a + offset, b + offset, o_ + offset);
				offset += OPTIMAL;
			}
			for (size_t i = 0; i < REMAINDER; ++i) {
				o_[i] = OperationImplementation<T, 1, O>::execute(a[offset + i], b[offset + i]);
			}
		}
	};

	template<class T, Operation O>
	struct OperationImplementation<T,2,O> {
		enum { PARAMS = OperationParams<O>::value };

		template<size_t S = PARAMS>
		static inline void ANVIL_CALL execute(const void* x, const void* y, const void* z, void* o) {
			const T* const a = static_cast<const T*>(x);
			const T* const b = static_cast<const T*>(y);
			const T* const c = static_cast<const T*>(z);
			T* const o_ = static_cast<T*>(o);
			o_[0] = OperationImplementation<T, 1, O>::execute(a[0], b[0], c[0]);
			o_[1] = OperationImplementation<T, 1, O>::execute(a[1], b[1], c[1]);
		}

		template<size_t S = PARAMS>
		static inline void ANVIL_CALL execute(const void* x, const void* y, void* o) {
			const T* const a = static_cast<const T*>(x);
			const T* const b = static_cast<const T*>(y);
			T* const o_ = static_cast<T*>(o);
			o_[0] = OperationImplementation<T, 1, O>::execute(a[0], b[0]);
			o_[1] = OperationImplementation<T, 1, O>::execute(a[1], b[1]);
		}

		template<size_t S = PARAMS>
		static ANVIL_STRONG_INLINE void ANVIL_CALL execute(const void* x, void* o) {
			const T* const a = static_cast<const T*>(x);
			T* const o_ = static_cast<T*>(o);
			o_[0] = OperationImplementation<T, 1, O>::execute(a[0]);
			o_[1] = OperationImplementation<T, 1, O>::execute(a[1]);
		}
	};

	template<class T, size_t S>
	struct OperationImplementation<T, S, OP_FILL> {
		static ANVIL_STRONG_INLINE void ANVIL_CALL execute(void* aOutput) {
			memset(aOutput, 0, sizeof(T) * S);
		}

		static void ANVIL_CALL execute(T x, void* aOutput) {
			T* const out = static_cast<T*>(aOutput);
			for (size_t i = 0; i < S; ++i) out[i] = x;
		}

		static ANVIL_CALL void execute(T x, T y, void* aOutput) {
			if (S > 2) execute(aOutput);
			T* const out = static_cast<T*>(aOutput);
			out[0] = x;
			if (S > 1) out[1] = y;
		}

		static ANVIL_CALL void execute(T x, T y, T z, void* aOutput) {
			if (S > 3) execute(aOutput);
			T* const out = static_cast<T*>(aOutput);
			out[0] = x;
			if (S > 1) out[1] = y;
			if (S > 2) out[2] = z;
		}

		static ANVIL_CALL void execute(T x, T y, T z, T w, void* aOutput) {
			if (S > 4) execute(aOutput);
			T* const out = static_cast<T*>(aOutput);
			out[0] = x;
			if (S > 1) out[1] = y;
			if (S > 2) out[2] = z;
			if (S > 3) out[3] = w;
		}
	};

	template<class T, size_t S>
	struct OperationImplementation<T, S, OP_CAST> {
		template<class T2>
		static void ANVIL_CALL execute(const void* x, void* y) {
			const T2* const a = static_cast<const T2*>(x);
			T* const b = static_cast<T*>(y);
			for (size_t i = 0; i < S; ++i) b[i] = static_cast<T>(a[i]);
		}
	};

	template<class T, size_t S>
	struct OperationImplementation<T, S, OP_RESIZE> {
		template<size_t S2>
		static void ANVIL_CALL execute(const void* x, void* y) {
			if (S > S2) Operation<T, S, OP_FILL>::execute(y);
			const T* const a = static_cast<const T*>(x);
			T* const b = static_cast<T*>(y);
			enum {S3 = S > S2 ? S2 : S };
			for (size_t i = 0; i < S3; ++i) b[i] = a[i];
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
#if defined(ANVIL_USE_INTEL_SIMD_INTRINSICS) && ANVIL_CPP_VER >= 2011
#define ANVIL_SIMD_AND_F(X,Y) _castu32_f32(_castf32_u32 (X) & _castf32_u32 (Y))
#define ANVIL_SIMD_OR_F(X,Y) _castu32_f32(_castf32_u32 (X) | _castf32_u32 (Y))
#define ANVIL_SIMD_XOR_F(X,Y) _castu32_f32(_castf32_u32 (X) ^ _castf32_u32 (Y))
#define ANVIL_SIMD_AND_D(X,Y) _castu64_f64(_castf64_u64 (X) & _castf64_u64 (Y))
#define ANVIL_SIMD_OR_D(X,Y) _castu64_f64(_castf64_u64 (X) | _castf64_u64 (Y))
#define ANVIL_SIMD_XOR_D(X,Y) _castu64_f64(_castf64_u64 (X) ^ _castf64_u64(Y))
#else
#define ANVIL_SIMD_AND_F(X,Y) value_cast<float>(value_cast<int32_t>(X) & value_cast<int32_t>(Y))
#define ANVIL_SIMD_OR_F(X,Y) value_cast<float>(value_cast<int32_t>(X) | value_cast<int32_t>(Y))
#define ANVIL_SIMD_XOR_F(X,Y) value_cast<float>(value_cast<int32_t>(X) ^ value_cast<int32_t>(Y))
#define ANVIL_SIMD_AND_D(X,Y) value_cast<double>(value_cast<int64_t>(X) & value_cast<int64_t>(Y))
#define ANVIL_SIMD_OR_D(X,Y) value_cast<double>(value_cast<int64_t>(X) | value_cast<int64_t>(Y))
#define ANVIL_SIMD_XOR_D(X,Y) value_cast<double>(value_cast<int64_t>(X) ^ value_cast<int64_t>(Y))
#endif
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

	#define ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,TYPE,SIZE,INSTRUCTION,INTRINSIC,FUNCTION,FUNCTION2)\
	template<>\
	struct OperationImplementation<TYPE, SIZE, OP> {\
		static inline void ANVIL_CALL execute(const void* x, const void* y, void* o) {\
			struct vec_t { TYPE data[SIZE]; };\
			const vec_t* const xv = static_cast<const vec_t*>(x);\
			const vec_t* const yv = static_cast<const vec_t*>(y);\
			vec_t* const ov = static_cast<vec_t*>(o);\
			if(ANVIL_USE_ ## INSTRUCTION) {\
				union Union {\
					vec_t v;\
					INTRINSIC i;\
				};\
				Union a, b;\
				a.v = *xv;\
				b.v = *yv;\
				a.i = FUNCTION(a.i, b.i);\
				*ov = a.v;\
			} else {\
				for(size_t i = 0; i < SIZE; ++i) ov->data[i] = FUNCTION2(xv->data[i], yv->data[i]);\
			}\
		}\
	};

	#define ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP,TYPE,INSTRUCTION,INTRINSIC,FUNCTION, FUNCTION2)\
		template<> struct OptimalOperationSize<OP,TYPE> { enum { value = 4 }; };\
		ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,TYPE,4,INSTRUCTION,INTRINSIC, FUNCTION, FUNCTION2)\
		ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,TYPE,3,INSTRUCTION,INTRINSIC, FUNCTION, FUNCTION2)\
		ANVIL_SIMD_IMPLEMENTATION_V_VV(OP,TYPE,2,INSTRUCTION,INTRINSIC, FUNCTION, FUNCTION2)

	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_ADD, float, SSE, __m128, _mm_add_ps, ANVIL_SIMD_ADD)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_SUB, float, SSE, __m128, _mm_sub_ps, ANVIL_SIMD_SUB)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_MUL, float, SSE, __m128, _mm_mul_ps, ANVIL_SIMD_MUL)
	ANVIL_SIMD_IMPLEMENTATION_V_VV_4(OP_DIV, float, SSE, __m128, _mm_div_ps, ANVIL_SIMD_DIV)

#endif
}}

#endif