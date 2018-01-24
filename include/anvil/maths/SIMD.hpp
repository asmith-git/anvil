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

	static ANVIL_STRONG_INLINE bool IsInstructionSetSupported(InstructionSet aSet) {
#ifdef ANVIL_USE_INTEL_SIMD_INTRINSICS
#if ANVIL_CPP_VER < 2011
		//! \todo Better CPU feature detection on older compilers
		return aSet >= (ANVIL_ARCHITECTURE_BITS <= 32 ? IS_MMX : IS_SSE) && aSet <= IS_SSE_2;
#else
		return _may_i_use_cpu_feature(aSet);
#endif
#endif
	}

	// Operation definitions

	enum Operation {
		// Misc operations
		OP_FILL, OP_CAST,
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

	template<Operation O>
	struct OperationParams {
		enum { value = 0 };
	};

	template<> struct OperationParams<OP_FILL>{ enum { value = 1 }; };
	template<> struct OperationParams<OP_CAST>{ enum { value = 1 }; };
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
}}

#endif