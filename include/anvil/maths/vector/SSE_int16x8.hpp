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

#ifndef ANVIL_MATHS_VECTOR_SSE_INT16x8_HPP
#define ANVIL_MATHS_VECTOR_SSE_INT16x8_HPP


#ifdef ANVIL_SSE_4_1
#include <smmintrin.h>
#else
#include <emmintrin.h>
#endif

namespace anvil { namespace detail {

	template<>
	struct OptimisedVector<int16_t, 2> {
		typedef int16_t T;
		enum { S = 2, optimised = 1 };
		typedef __m128i type;

		static ANVIL_STRONG_INLINE type ANVIL_VECTOR_CALL load(const Vector<T, S> a) throw() {
			return _mm_set_epi16(0, 0, 0, 0, 0, 0, a.y, a.x);
		}

		static ANVIL_STRONG_INLINE Vector<T, S> ANVIL_VECTOR_CALL store(const register type aValue) throw() {
			union {
				type tmp;
				Vector<T, S> out;
			};
			_mm_store_si128(&tmp, aValue);
			return out;
		}
	};

	template<>
	struct OptimisedVector<int16_t, 3> {
		typedef int16_t T;
		enum { S = 3, optimised = 1 };
		typedef __m128i type;

		static ANVIL_STRONG_INLINE type ANVIL_VECTOR_CALL load(const Vector<T, S> a) throw() {
			return _mm_set_epi16(0, 0, 0, 0, 0, a.z, a.y, a.x);
		}

		static ANVIL_STRONG_INLINE Vector<T, S> ANVIL_VECTOR_CALL store(const register type aValue) throw() {
			union {
				type tmp;
				Vector<T, S> out;
			};
			_mm_store_si128(&tmp, aValue);
			return out;
		}
	};

	template<>
	struct OptimisedVector<int16_t, 4> {
		typedef int16_t T;
		enum { S = 4, optimised = 1 };
		typedef __m128i type;

		static ANVIL_STRONG_INLINE type ANVIL_VECTOR_CALL load(const Vector<T, S> a) throw() {
			return _mm_set_epi16(0, 0, 0, 0, a.w, a.z, a.y, a.x);
		}

		static ANVIL_STRONG_INLINE Vector<T, S> ANVIL_VECTOR_CALL store(const register type aValue) throw() {
			union {
				type tmp;
				Vector<T, S> out;
			};
			_mm_store_si128(&tmp, aValue);
			return out;
		}
	};

	template<>
	struct OptimisedVector<int16_t, 8> {
		typedef int16_t T;
		enum { S = 8, optimised = 1 };
		typedef __m128i type;

		static ANVIL_STRONG_INLINE type ANVIL_VECTOR_CALL load(const Vector<T, S> a) throw() {
			return _mm_load_si128(reinterpret_cast<const type*>(a.elements));
		}

		static ANVIL_STRONG_INLINE Vector<T, S> ANVIL_VECTOR_CALL store(const register type aValue) throw() {
			Vector<T, S> tmp;
			_mm_store_si128(reinterpret_cast<type*>(tmp.elements), aValue);
			return tmp;
		}
	};

#ifndef ANVIL_AVX_2
	template<>
	struct OptimisedVector<int16_t, 16> {
		typedef float T;
		enum { S = 16, optimised = 1 };
		typedef std::array<__m128i, 2> type;

		static ANVIL_STRONG_INLINE type ANVIL_VECTOR_CALL load(const Vector<T, S> aVector) throw() {
			type tmp;
			tmp[0] = _mm_load_si128(reinterpret_cast<const __m128i*>(aVector.elements));
			tmp[1] = _mm_load_si128(reinterpret_cast<const __m128i*>(aVector.elements + 8));
			return tmp;
		}

		static ANVIL_STRONG_INLINE Vector<T, S> ANVIL_VECTOR_CALL store(const register type aValue) throw() {
			Vector<T, S> tmp;
			_mm_store_si128(reinterpret_cast<__m128i*>(tmp.elements), aValue[0]);
			_mm_store_si128(reinterpret_cast<__m128i*>(tmp.elements + 8), aValue[1]);
			return tmp;
		}
	};
#endif

#define ANVIL_VECTOR_OP1(ID, FN)\
	template<>\
	struct PrimativeVectorOperation<__m128i, ID, int16_t, 8> {\
		static ANVIL_STRONG_INLINE __m128i ANVIL_VECTOR_CALL implementation(const register __m128i a) {\
			return FN(a);\
		}\
	};

#define ANVIL_VECTOR_OP2(ID)\
	template<>\
	struct PrimativeVectorOperation<__m128i, ID, int16_t, 8> {\
		static inline __m128i ANVIL_VECTOR_CALL implementation(const register __m128i a) {\
			ANVIL_ALIGN(16) int16_t buffer_a[8];\
			_mm_store_si128(reinterpret_cast<__m128i*>(buffer_a), a);\
			buffer_a[0] = PrimativeVectorOperation<int16_t, ID, int16_t, 1>::implementation(buffer_a[0]);\
			buffer_a[1] = PrimativeVectorOperation<int16_t, ID, int16_t, 1>::implementation(buffer_a[1]);\
			buffer_a[2] = PrimativeVectorOperation<int16_t, ID, int16_t, 1>::implementation(buffer_a[2]);\
			buffer_a[3] = PrimativeVectorOperation<int16_t, ID, int16_t, 1>::implementation(buffer_a[3]);\
			buffer_a[4] = PrimativeVectorOperation<int16_t, ID, int16_t, 1>::implementation(buffer_a[4]);\
			buffer_a[5] = PrimativeVectorOperation<int16_t, ID, int16_t, 1>::implementation(buffer_a[5]);\
			buffer_a[6] = PrimativeVectorOperation<int16_t, ID, int16_t, 1>::implementation(buffer_a[6]);\
			buffer_a[7] = PrimativeVectorOperation<int16_t, ID, int16_t, 1>::implementation(buffer_a[7]);\
			return _mm_load_si128(reinterpret_cast<__m128i*>(buffer_a));\
		}\
	};

static ANVIL_STRONG_INLINE __m128i ANVIL_VECTOR_CALL _mm_not_epi16(const register __m128i a) throw() {
	return _mm_xor_si128(a, _mm_cmpeq_epi16(a, a));
}

static ANVIL_STRONG_INLINE __m128i ANVIL_VECTOR_CALL _mm_return_epi16(const register __m128i a) throw() {
	return a;
}

ANVIL_VECTOR_OP1(VEC_NOT, _mm_not_epi16)
ANVIL_VECTOR_OP1(VEC_FLOOR, _mm_return_epi16)
ANVIL_VECTOR_OP1(VEC_CEIL, _mm_return_epi16)
ANVIL_VECTOR_OP1(VEC_ROUND, _mm_return_epi16)

#ifdef ANVIL_SSSE_3
	ANVIL_VECTOR_OP1(VEC_ABS, _mm_abs_epi16)
#endif

ANVIL_VECTOR_OP2(VEC_SQRT) //! \todo Decompse to 4x float32x4 sqrt
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
ANVIL_VECTOR_OP2(VEC_EXP)
#ifndef ANVIL_SSSE_3
	ANVIL_VECTOR_OP2(VEC_ABS)
#endif

#undef ANVIL_VECTOR_OP1
#undef ANVIL_VECTOR_OP2

#define ANVIL_VECTOR_OP1(ID, FN)\
	template<>\
	struct PrimativeVectorOperation<__m128i, ID, int16_t, 8> {\
		static ANVIL_STRONG_INLINE __m128i ANVIL_VECTOR_CALL implementation(const register __m128i a, const register __m128i b) {\
			return FN(a, b);\
		}\
	};

#define ANVIL_VECTOR_OP2(ID)\
	template<>\
	struct PrimativeVectorOperation<__m128i, ID, int16_t, 8> {\
		static inline __m128i ANVIL_VECTOR_CALL implementation(const register __m128i a, const register __m128i b) {\
			ANVIL_ALIGN(16) int16_t buffer_a[8];\
			ANVIL_ALIGN(16) int16_t buffer_b[8];\
			_mm_store_si128(reinterpret_cast<__m128i*>(buffer_a), a);\
			_mm_store_si128(reinterpret_cast<__m128i*>(buffer_b), b);\
			buffer_a[0] = PrimativeVectorOperation<int16_t, ID, int16_t, 1>::implementation(buffer_a[0], buffer_b[0]);\
			buffer_a[1] = PrimativeVectorOperation<int16_t, ID, int16_t, 1>::implementation(buffer_a[1], buffer_b[1]);\
			buffer_a[2] = PrimativeVectorOperation<int16_t, ID, int16_t, 1>::implementation(buffer_a[2], buffer_b[2]);\
			buffer_a[3] = PrimativeVectorOperation<int16_t, ID, int16_t, 1>::implementation(buffer_a[3], buffer_b[3]);\
			buffer_a[4] = PrimativeVectorOperation<int16_t, ID, int16_t, 1>::implementation(buffer_a[4], buffer_b[4]);\
			buffer_a[5] = PrimativeVectorOperation<int16_t, ID, int16_t, 1>::implementation(buffer_a[5], buffer_b[5]);\
			buffer_a[6] = PrimativeVectorOperation<int16_t, ID, int16_t, 1>::implementation(buffer_a[6], buffer_b[6]);\
			buffer_a[7] = PrimativeVectorOperation<int16_t, ID, int16_t, 1>::implementation(buffer_a[7], buffer_b[7]);\
			return _mm_load_si128(reinterpret_cast<__m128i*>(buffer_a));\
		}\
	};

static ANVIL_STRONG_INLINE __m128i ANVIL_VECTOR_CALL _mm_mul_epi16(const register __m128i a, const register __m128i b) throw() {
	const register __m128i xmm0 = _mm_mullo_epi16(a, b);
	const register __m128i xmm1 = _mm_mullo_epi16(_mm_srli_epi16(a, 8), _mm_srli_epi16(b, 8));
	return _mm_or_si128(_mm_slli_epi16(xmm1, 8), _mm_srli_epi16(_mm_slli_epi16(xmm0, 8), 8));
}

static ANVIL_STRONG_INLINE __m128i ANVIL_VECTOR_CALL _mm_cmpneq_epi16(const register __m128i a, const register __m128i b) throw() {
	return _mm_not_epi16(_mm_cmpeq_epi16(a, b));
}

static ANVIL_STRONG_INLINE __m128i ANVIL_VECTOR_CALL _mm_cmple_epi16(const register __m128i a, const register __m128i b) throw() {
	return _mm_not_epi16(_mm_cmpgt_epi16(a, b));
}

static ANVIL_STRONG_INLINE __m128i ANVIL_VECTOR_CALL _mm_cmpge_epi16(const register __m128i a, const register __m128i b) throw() {
	return _mm_not_epi16(_mm_cmplt_epi16(a, b));
}


ANVIL_VECTOR_OP1(VEC_ADD, _mm_adds_epi16)
ANVIL_VECTOR_OP1(VEC_SUB, _mm_subs_epi16)
ANVIL_VECTOR_OP1(VEC_MUL, _mm_mul_epi16)
#ifdef ANVIL_SSE_4_1
	ANVIL_VECTOR_OP1(VEC_MIN, _mm_min_epi16)
	ANVIL_VECTOR_OP1(VEC_MAX, _mm_max_epi16)
#endif
ANVIL_VECTOR_OP1(VEC_AND, _mm_and_si128)
ANVIL_VECTOR_OP1(VEC_OR, _mm_or_si128)
ANVIL_VECTOR_OP1(VEC_XOR, _mm_xor_si128)
ANVIL_VECTOR_OP1(VEC_CMPEQ, _mm_cmpeq_epi16)
ANVIL_VECTOR_OP1(VEC_CMPNE, _mm_cmpneq_epi16)
ANVIL_VECTOR_OP1(VEC_CMPLT, _mm_cmplt_epi16)
ANVIL_VECTOR_OP1(VEC_CMPGT, _mm_cmpgt_epi16)
ANVIL_VECTOR_OP1(VEC_CMPLE, _mm_cmple_epi16)
ANVIL_VECTOR_OP1(VEC_CMPGE, _mm_cmpge_epi16)

ANVIL_VECTOR_OP2(VEC_DIV)
ANVIL_VECTOR_OP2(VEC_MOD)
ANVIL_VECTOR_OP2(VEC_ATAN2)
ANVIL_VECTOR_OP2(VEC_POW)
ANVIL_VECTOR_OP2(VEC_HYPOT)
#ifdef ANVIL_SSE_4_1
	ANVIL_VECTOR_OP2(VEC_MIN)
	ANVIL_VECTOR_OP2(VEC_MAX)
#endif

#undef ANVIL_VECTOR_OP1
#undef ANVIL_VECTOR_OP2

#define ANVIL_VECTOR_OP1(ID, FN)\
	template<>\
	struct PrimativeVectorOperation<__m128i, ID, int16_t, 8> {\
		static ANVIL_STRONG_INLINE __m128i ANVIL_VECTOR_CALL implementation(const register __m128i a, const register __m128i b, const register __m128i c) {\
			return FN(a, b, c);\
		}\
	};

#define ANVIL_VECTOR_OP2(ID)\
	template<>\
	struct PrimativeVectorOperation<__m128i, ID, int16_t, 8> {\
		static inline __m128i ANVIL_VECTOR_CALL implementation(const register __m128i a, const register __m128i b, const register __m128i c) {\
			ANVIL_ALIGN(16) int16_t buffer_a[8];\
			ANVIL_ALIGN(16) int16_t buffer_b[8];\
			ANVIL_ALIGN(16) int16_t buffer_c[8];\
			_mm_store_si128(reinterpret_cast<__m128i*>(buffer_a), a);\
			_mm_store_si128(reinterpret_cast<__m128i*>(buffer_b), b);\
			_mm_store_si128(reinterpret_cast<__m128i*>(buffer_c), c);\
			buffer_a[0] = PrimativeVectorOperation<int16_t, ID, int16_t, 1>::implementation(buffer_a[0], buffer_b[0], buffer_c[0]);\
			buffer_a[1] = PrimativeVectorOperation<int16_t, ID, int16_t, 1>::implementation(buffer_a[1], buffer_b[1], buffer_c[1]);\
			buffer_a[2] = PrimativeVectorOperation<int16_t, ID, int16_t, 1>::implementation(buffer_a[2], buffer_b[2], buffer_c[2]);\
			buffer_a[3] = PrimativeVectorOperation<int16_t, ID, int16_t, 1>::implementation(buffer_a[3], buffer_b[3], buffer_c[3]);\
			buffer_a[4] = PrimativeVectorOperation<int16_t, ID, int16_t, 1>::implementation(buffer_a[4], buffer_b[4], buffer_c[4]);\
			buffer_a[5] = PrimativeVectorOperation<int16_t, ID, int16_t, 1>::implementation(buffer_a[5], buffer_b[5], buffer_c[5]);\
			buffer_a[6] = PrimativeVectorOperation<int16_t, ID, int16_t, 1>::implementation(buffer_a[6], buffer_b[6], buffer_c[6]);\
			buffer_a[7] = PrimativeVectorOperation<int16_t, ID, int16_t, 1>::implementation(buffer_a[7], buffer_b[7], buffer_c[7]);\
			return _mm_load_si128(reinterpret_cast<__m128i*>(buffer_a));\
		}\
	};

static ANVIL_STRONG_INLINE __m128i ANVIL_VECTOR_CALL _mm_fmadd_epi16(const register __m128i a, const register __m128i b, const register __m128i c) throw() {
	return _mm_adds_epi16(_mm_mul_epi16(a, b), c);
}

static ANVIL_STRONG_INLINE __m128i ANVIL_VECTOR_CALL _mm_fmsub_epi16(const register __m128i a, const register __m128i b, const register __m128i c) throw() {
	return _mm_subs_epi16(_mm_mul_epi16(a, b), c);
}

ANVIL_VECTOR_OP1(VEC_FMA, _mm_fmadd_epi16)
ANVIL_VECTOR_OP1(VEC_FMS, _mm_fmsub_epi16)

#undef ANVIL_VECTOR_OP1
#undef ANVIL_VECTOR_OP2
}}

#endif