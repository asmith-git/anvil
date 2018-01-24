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

namespace anvil { namespace simd {
	enum InstructionSet {
		NOT_SUPPORTED,
#if ANVIL_ARCHITECTURE == ANVIL_X86 || ANVIL_ARCHITECTURE == ANVIL_X64
		MMX,
		SSE,
		SSE_2,
		SSE_3,
		SSSE_3,
		SSE_4_1,
		SSE_4_2,
		AVX,
		FMA,
		AVX_2,
		KNC,
		AVX_512
#endif
	};

	enum Operation {
		// Misc Operations
		FILL, CAST,
		// 3 parameters
		FMA, FMS,
		// 2 parameters
		ADD, SUB, MUL, DIV, MIN, MAX, AND, OR, XOR, LSHIFT, RSHIFT, MOD, DIM,
		CMPEQ, CMPNE, CMPLT, CMPGT, CMPLE, CMPGE, ATAN2, REFLECT,
		// 1 parameter
		NOT, ABS, EXP, LOG, LOG2, LOG10, CEIL, FLOOR, ROUND, SIN, COS, TAN,
		ASIN, ACOS, ATAN, COSH, SINH, TANH, SQRT, CBRT,
		// 1 Parameter, scalar output
		AVG, SUM, POPCN
	};

	template<Operation O, class T, size_t S> struct OperationSupport {
		enum { value = NOT_SUPPORTED };
	};

	template<Operation O>
	struct OperationParams {
		enum { value = 0 };
	};

	template<> struct OperationParams<FILL>{ enum { value = 1 }; };
	template<> struct OperationParams<CAST>{ enum { value = 1 }; };
	template<> struct OperationParams<FMA>{ enum { value = 3 }; };
	template<> struct OperationParams<FMS>{ enum { value = 3 }; };
	template<> struct OperationParams<ADD>{ enum { value = 2 }; };
	template<> struct OperationParams<SUB>{ enum { value = 2 }; };
	template<> struct OperationParams<MUL>{ enum { value = 2 }; };
	template<> struct OperationParams<DIV>{ enum { value = 2 }; };
	template<> struct OperationParams<MIN>{ enum { value = 2 }; };
	template<> struct OperationParams<MAX>{ enum { value = 2 }; };
	template<> struct OperationParams<OR>{ enum { value = 2 }; };
	template<> struct OperationParams<LSHIFT>{ enum { value = 2 }; };
	template<> struct OperationParams<RSHIFT>{ enum { value = 2 }; };
	template<> struct OperationParams<RSHIFT>{ enum { value = 2 }; };
	template<> struct OperationParams<MOD>{ enum { value = 2 }; };
	template<> struct OperationParams<DIM>{ enum { value = 2 }; };
	template<> struct OperationParams<CMPEQ>{ enum { value = 2 }; };
	template<> struct OperationParams<CMPNE>{ enum { value = 2 }; };
	template<> struct OperationParams<CMPLT>{ enum { value = 2 }; };
	template<> struct OperationParams<CMPGT>{ enum { value = 2 }; };
	template<> struct OperationParams<CMPLE>{ enum { value = 2 }; };
	template<> struct OperationParams<CMPGE>{ enum { value = 2 }; };
	template<> struct OperationParams<ATAN2>{ enum { value = 2 }; };
	template<> struct OperationParams<REFLECT>{ enum { value = 2 }; };
	template<> struct OperationParams<NOT>{ enum { value = 1 }; };
	template<> struct OperationParams<ABS>{ enum { value = 1 }; };
	template<> struct OperationParams<EXP>{ enum { value = 1 }; };
	template<> struct OperationParams<LOG>{ enum { value = 1 }; };
	template<> struct OperationParams<LOG2>{ enum { value = 1 }; };
	template<> struct OperationParams<LOG10>{ enum { value = 1 }; };
	template<> struct OperationParams<CEIL>{ enum { value = 1 }; };
	template<> struct OperationParams<FLOOR>{ enum { value = 1 }; };
	template<> struct OperationParams<ROUND>{ enum { value = 1 }; };
	template<> struct OperationParams<SIN>{ enum { value = 1 }; };
	template<> struct OperationParams<COS>{ enum { value = 1 }; };
	template<> struct OperationParams<TAN>{ enum { value = 1 }; };
	template<> struct OperationParams<ASIN>{ enum { value = 1 }; };
	template<> struct OperationParams<ACOS>{ enum { value = 1 }; };
	template<> struct OperationParams<ACOS>{ enum { value = 1 }; };
	template<> struct OperationParams<ATAN>{ enum { value = 1 }; };
	template<> struct OperationParams<COSH>{ enum { value = 1 }; };
	template<> struct OperationParams<SINH>{ enum { value = 1 }; };
	template<> struct OperationParams<TANH>{ enum { value = 1 }; };
	template<> struct OperationParams<SQRT>{ enum { value = 1 }; };
	template<> struct OperationParams<CBRT>{ enum { value = 1 }; };
	template<> struct OperationParams<AVG>{ enum { value = 1 }; };
	template<> struct OperationParams<SUM>{ enum { value = 1 }; };
	template<> struct OperationParams<POPCN>{ enum { value = 1 }; };
}}

#endif