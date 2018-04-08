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

#ifndef ANVIL_MATHS_VECTOR_SSE_FLOAT32X4_HPP
#define ANVIL_MATHS_VECTOR_SSE_FLOAT32X4_HPP

#ifdef ANVIL_SSE_4_1
	#include <smmintrin.h>
#else
	#include <xmmintrin.h>
#endif

namespace anvil { namespace detail {

	template<>
	struct OptimisedVector<float, 2> {
		typedef float T;
		enum { S = 2, optimised = 1 };
		typedef __m128 type;

		static ANVIL_STRONG_INLINE type ANVIL_VECTOR_CALL load(const Vector<T, S> aVector) throw() {
			return _mm_set_ps(0.f, 0, aVector.y, aVector.x);
		}

		static ANVIL_STRONG_INLINE Vector<T, S> ANVIL_VECTOR_CALL store(const register type aValue) throw() {
			union {
				Vector<T, 4> tmp;
				Vector<T, S> out;
			};
			_mm_store_ps(tmp.elements, aValue);
			return out;
		}
	};

	template<>
	struct OptimisedVector<float, 3> {
		typedef float T;
		enum { S = 3, optimised = 1 };
		typedef __m128 type;

		static ANVIL_STRONG_INLINE type ANVIL_VECTOR_CALL load(const Vector<T, S> aVector) throw() {
			return _mm_set_ps(0.f, aVector.z, aVector.y, aVector.x);
		}

		static ANVIL_STRONG_INLINE Vector<T, S> ANVIL_VECTOR_CALL store(const register type aValue) throw() {
			union {
				Vector<T, 4> tmp;
				Vector<T, S> out;
			};
			_mm_store_ps(tmp.elements, aValue);
			return out;
		}
	};

	template<>
	struct OptimisedVector<float, 4> {
		typedef float T;
		enum { S = 4, optimised = 1 };
		typedef __m128 type;

		static ANVIL_STRONG_INLINE type ANVIL_VECTOR_CALL load(const Vector<T, S> aVector) throw() {
			return _mm_load_ps(aVector.elements);
		}

		static ANVIL_STRONG_INLINE Vector<T, S> ANVIL_VECTOR_CALL store(const register type aValue) throw() {
			Vector<T, S> tmp;
			_mm_store_ps(tmp.elements, aValue);
			return tmp;
		}
	};

#ifndef ANVIL_AVX
	template<>
	struct OptimisedVector<float, 8> {
		typedef float T;
		enum { S = 8, optimised = 1 };
		typedef std::array<__m128, 2> type;

		static ANVIL_STRONG_INLINE type ANVIL_VECTOR_CALL load(const Vector<T, S> aVector) throw() {
			type tmp;
			tmp[0] = _mm_load_ps(aVector.elements);
			tmp[1] = _mm_load_ps(aVector.elements + 4);
			return tmp;
		}

		static ANVIL_STRONG_INLINE Vector<T, S> ANVIL_VECTOR_CALL store(const register type aValue) throw() {
			Vector<T, S> tmp;
			_mm_store_ps(tmp.elements, aValue[0]);
			_mm_store_ps(tmp.elements + 4, aValue[1]);
			return tmp;
		}
	};

	template<>
	struct OptimisedVector<float, 16> {
		typedef float T;
		enum { S = 16, optimised = 1 };
		typedef std::array<__m128, 4> type;

		static ANVIL_STRONG_INLINE type ANVIL_VECTOR_CALL load(const Vector<T, S> aVector) throw() {
			type tmp;
			tmp[0] = _mm_load_ps(aVector.elements);
			tmp[1] = _mm_load_ps(aVector.elements + 4);
			tmp[2] = _mm_load_ps(aVector.elements + 8);
			tmp[3] = _mm_load_ps(aVector.elements + 12);
			return tmp;
		}

		static ANVIL_STRONG_INLINE Vector<T, S> ANVIL_VECTOR_CALL store(const register type aValue) throw() {
			Vector<T, S> tmp;
			_mm_store_ps(tmp.elements, aValue[0]);
			_mm_store_ps(tmp.elements + 4, aValue[1]);
			_mm_store_ps(tmp.elements + 8, aValue[2]);
			_mm_store_ps(tmp.elements + 12, aValue[3]);
			return tmp;
		}
	};
#endif

#define ANVIL_VECTOR_OP1(ID, FN)\
	template<>\
	struct PrimativeVectorOperation<__m128, ID, float, 4> {\
		static ANVIL_STRONG_INLINE __m128 ANVIL_VECTOR_CALL implementation(const register __m128 a) {\
			return FN(a);\
		}\
	};

#define ANVIL_VECTOR_OP2(ID)\
	template<>\
	struct PrimativeVectorOperation<__m128, ID, float, 4> {\
		static ANVIL_STRONG_INLINE __m128 ANVIL_VECTOR_CALL implementation(const register __m128 a) {\
			ANVIL_ALIGN(16) float buffer_a[4];\
			_mm_store_ps(buffer_a, a);\
			buffer_a[0] = PrimativeVectorOperation<float, ID, float, 1>::implementation(buffer_a[0]);\
			buffer_a[1] = PrimativeVectorOperation<float, ID, float, 1>::implementation(buffer_a[1]);\
			buffer_a[2] = PrimativeVectorOperation<float, ID, float, 1>::implementation(buffer_a[2]);\
			buffer_a[3] = PrimativeVectorOperation<float, ID, float, 1>::implementation(buffer_a[3]);\
			return _mm_load_ps(buffer_a);\
		}\
	};

#define ANVIL_VECTOR_NOT(A) _mm_xor_ps(A, _mm_cmpeq_ps(A,A))

ANVIL_VECTOR_OP1(VEC_SQRT, _mm_sqrt_ps)
ANVIL_VECTOR_OP1(VEC_NOT, ANVIL_VECTOR_NOT)

#ifdef ANVIL_SSE_4_1
	#define ANVIL_VECTOR_ROUND(A) _mm_round_ps(A, (_MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC))
	ANVIL_VECTOR_OP1(VEC_FLOOR, _mm_floor_ps)
	ANVIL_VECTOR_OP1(VEC_CEIL, _mm_ceil_ps)
	ANVIL_VECTOR_OP1(VEC_ROUND, ANVIL_VECTOR_ROUND)
	#undef ANVIL_VECTOR_ROUND
#endif

ANVIL_VECTOR_OP2(VEC_CBRT)
ANVIL_VECTOR_OP2(VEC_COS)
ANVIL_VECTOR_OP2(VEC_SIN)
ANVIL_VECTOR_OP2(VEC_TAN)
ANVIL_VECTOR_OP2(VEC_ACOS)
ANVIL_VECTOR_OP2(VEC_ASIN)
ANVIL_VECTOR_OP2(VEC_ATAN)
ANVIL_VECTOR_OP2(VEC_COSH)
ANVIL_VECTOR_OP2(VEC_SINH)
ANVIL_VECTOR_OP2(VEC_TANH)
ANVIL_VECTOR_OP2(VEC_ACOSH)
ANVIL_VECTOR_OP2(VEC_ASINH)
ANVIL_VECTOR_OP2(VEC_ATANH)
ANVIL_VECTOR_OP2(VEC_LOG)
ANVIL_VECTOR_OP2(VEC_LOG2)
ANVIL_VECTOR_OP2(VEC_LOG10)
ANVIL_VECTOR_OP2(VEC_ABS)
ANVIL_VECTOR_OP2(VEC_EXP)
#ifndef ANVIL_SSE_4_1
	ANVIL_VECTOR_OP2(VEC_FLOOR)
	ANVIL_VECTOR_OP2(VEC_CEIL)
	ANVIL_VECTOR_OP2(VEC_ROUND)
#endif

#undef ANVIL_VECTOR_NOT
#undef ANVIL_VECTOR_OP1
#undef ANVIL_VECTOR_OP2

#define ANVIL_VECTOR_OP1(ID, FN)\
	template<>\
	struct PrimativeVectorOperation<__m128, ID, float, 4> {\
		static ANVIL_STRONG_INLINE __m128 ANVIL_VECTOR_CALL implementation(const register __m128 a, const register __m128 b) {\
			return FN(a, b);\
		}\
	};

#define ANVIL_VECTOR_OP2(ID)\
	template<>\
	struct PrimativeVectorOperation<__m128, ID, float, 4> {\
		static ANVIL_STRONG_INLINE __m128 ANVIL_VECTOR_CALL implementation(const register __m128 a, const register __m128 b) {\
			ANVIL_ALIGN(16) float buffer_a[4];\
			ANVIL_ALIGN(16) float buffer_b[4];\
			_mm_store_ps(buffer_a, a);\
			_mm_store_ps(buffer_b, b);\
			buffer_a[0] = PrimativeVectorOperation<float, ID, float, 1>::implementation(buffer_a[0], buffer_b[0]);\
			buffer_a[1] = PrimativeVectorOperation<float, ID, float, 1>::implementation(buffer_a[1], buffer_b[1]);\
			buffer_a[2] = PrimativeVectorOperation<float, ID, float, 1>::implementation(buffer_a[2], buffer_b[2]);\
			buffer_a[3] = PrimativeVectorOperation<float, ID, float, 1>::implementation(buffer_a[3], buffer_b[3]);\
			return _mm_load_ps(buffer_a);\
		}\
	};


ANVIL_VECTOR_OP1(VEC_ADD, _mm_add_ps)
ANVIL_VECTOR_OP1(VEC_SUB, _mm_sub_ps)
ANVIL_VECTOR_OP1(VEC_MUL, _mm_mul_ps)
ANVIL_VECTOR_OP1(VEC_DIV, _mm_div_ps)
ANVIL_VECTOR_OP1(VEC_MIN, _mm_min_ps)
ANVIL_VECTOR_OP1(VEC_MAX, _mm_max_ps)
ANVIL_VECTOR_OP1(VEC_AND, _mm_and_ps)
ANVIL_VECTOR_OP1(VEC_OR, _mm_or_ps)
ANVIL_VECTOR_OP1(VEC_XOR, _mm_xor_ps)
ANVIL_VECTOR_OP1(VEC_CMPEQ, _mm_cmpeq_ps)
ANVIL_VECTOR_OP1(VEC_CMPNE, _mm_cmpneq_ps)
ANVIL_VECTOR_OP1(VEC_CMPLT, _mm_cmplt_ps)
ANVIL_VECTOR_OP1(VEC_CMPGT, _mm_cmpgt_ps)
ANVIL_VECTOR_OP1(VEC_CMPLE, _mm_cmple_ps)
ANVIL_VECTOR_OP1(VEC_CMPGE, _mm_cmpge_ps)

ANVIL_VECTOR_OP2(VEC_MOD)
ANVIL_VECTOR_OP2(VEC_ATAN2)
ANVIL_VECTOR_OP2(VEC_POW)
ANVIL_VECTOR_OP2(VEC_HYPOT)

#undef ANVIL_VECTOR_OP1
#undef ANVIL_VECTOR_OP2

#define ANVIL_VECTOR_OP1(ID, FN)\
	template<>\
	struct PrimativeVectorOperation<__m128, ID, float, 4> {\
		static ANVIL_STRONG_INLINE __m128 ANVIL_VECTOR_CALL implementation(const register __m128 a, const register __m128 b, const register __m128 c) {\
			return FN(a, b, c);\
		}\
	};

#define ANVIL_VECTOR_OP2(ID)\
	template<>\
	struct PrimativeVectorOperation<__m128, ID, float, 4> {\
		static ANVIL_STRONG_INLINE __m128 ANVIL_VECTOR_CALL implementation(const register __m128 a, const register __m128 b, const register __m128 c) {\
			ANVIL_ALIGN(16) float buffer_a[4];\
			ANVIL_ALIGN(16) float buffer_b[4];\
			ANVIL_ALIGN(16) float buffer_c[4];\
			_mm_store_ps(buffer_a, a);\
			_mm_store_ps(buffer_b, b);\
			_mm_store_ps(buffer_c, c);\
			buffer_a[0] = PrimativeVectorOperation<float, ID, float, 1>::implementation(buffer_a[0], buffer_b[0], buffer_c[0]);\
			buffer_a[1] = PrimativeVectorOperation<float, ID, float, 1>::implementation(buffer_a[1], buffer_b[1], buffer_c[1]);\
			buffer_a[2] = PrimativeVectorOperation<float, ID, float, 1>::implementation(buffer_a[2], buffer_b[2], buffer_c[2]);\
			buffer_a[3] = PrimativeVectorOperation<float, ID, float, 1>::implementation(buffer_a[3], buffer_b[3], buffer_c[3]);\
			return _mm_load_ps(buffer_a);\
		}\
	};

#ifdef ANVIL_FMA
	#define ANVIL_VECTOR_FMA(A,B,C) _mm_fmadd_ps(A,B,C)
	#define ANVIL_VECTOR_FMS(A,B,C) _mm_fmadd_ps(A,B,C)
#else
	#define ANVIL_VECTOR_FMA(A,B,C) _mm_add_ps(_mm_mul_ps(A,B),C)
	#define ANVIL_VECTOR_FMS(A,B,C) _mm_sub_ps(_mm_mul_ps(A,B),C)
#endif
		ANVIL_VECTOR_OP1(VEC_FMA, ANVIL_VECTOR_FMA)
		ANVIL_VECTOR_OP1(VEC_FMS, ANVIL_VECTOR_FMS)

#undef ANVIL_VECTOR_FMA
#undef ANVIL_VECTOR_FMS
#undef ANVIL_VECTOR_OP1
#undef ANVIL_VECTOR_OP2
}}

#endif