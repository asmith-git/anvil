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

#ifndef ANVIL_MATHS_VECTOR_HPP
#define ANVIL_MATHS_VECTOR_HPP

#include <iostream>
#include "anvil/Core/Cpu.hpp"
#include "anvil/Core/Constants.hpp"
#include "anvil/maths/Type.hpp"
#include "anvil/maths/Popcount.hpp"
#include "anvil/maths/Reflection.hpp"
#include "anvil/maths/Common.hpp"
#include "anvil/maths/SIMD.hpp"

#ifdef ANVIL_AVX_512
	#define ANVIL_AVX2
	//#include ?
#endif

#ifdef ANVIL_AVX2
	#define ANVIL_AVX
	//#include <zmmintrin.h>
#endif

#ifdef ANVIL_AVX
	#define ANVIL_SSE4_2
	#define ANVIL_FMA
	#include <immintrin.h>
#endif

#ifdef ANVIL_SSE4_2
	#define ANVIL_SSE4_1
	#include <nmmintrin.h>
#endif

#ifdef ANVIL_SSE4_1
	#define ANVIL_SSE3
	#include <smmintrin.h>
#endif

#ifdef ANVIL_SSE3
	#define ANVIL_SSSE3
	#include <tmmintrin.h>
#endif

#ifdef ANVIL_SSSE3
	#define ANVIL_SSE2
	#include <pmmintrin.h>
#endif

#ifdef ANVIL_SSE2
	#define ANVIL_SSE
	#include <emmintrin.h>
#endif

#ifdef ANVIL_SSE
	#define ANVIL_MMX
	#include <xmmintrin.h>
#endif

#ifdef ANVIL_MMX
	#include <mmintrin.h>
#endif

#include "anvil/maths/SIMD.hpp"

namespace anvil {

	namespace detail {

		template<class T>
		struct VFloat {
			typedef float type;
		};

		template<>
		struct VFloat<double> {
			typedef double type;
		};

		enum VectorOp {
			VOP_ADD,   VOP_SUB,    VOP_MUL,   VOP_DIV,
			VOP_MIN,   VOP_MAX,    VOP_LSH,   VOP_RSH,
			VOP_ABS,   VOP_FMA,    VOP_FMS,   VOP_AVG,
			VOP_SUM,   VOP_EQ,     VOP_NE,    VOP_LE,
			VOP_GE,    VOP_LT,     VOP_GT,    VOP_AND,
			VOP_OR,    VOP_XOR,    VOP_NOT,   VOP_SQRT,
			VOP_SIN,   VOP_COS,    VOP_TAN,   VOP_ASIN,
			VOP_ACOS,  VOP_ATAN,   VOP_PCN,   VOP_REF,
			VOP_MOD,   VOP_DIM,    VOP_EXP,   VOP_LOG,
			VOP_LOG2,  VOP_LOG10,  VOP_POW,   VOP_CBRT,
			VOP_HYPOT, VOP_ATAN2,  VOP_COSH, VOP_SINH,
			VOP_TANH,  VOP_ACONSH, VOP_ASINH, VOP_ATANH, 
			VOP_CEIL,  VOP_FLOOR,  VOP_TRUNC, VOP_ROUND,
			VOP_FILL
		};

		template<size_t BYTES>
		struct DefaultIntrinsic {
			uint8_t data[BYTES];
		};

		template<class T, size_t S, class ENABLE = void>
		struct VecInfo {
			enum {
				size = S,
				has_intrinsic = 0
			};
			typedef T type;
			typedef DefaultIntrinsic<sizeof(T) * S> intrinsic_t;
		};

#define ANVIL_SPECIALISE_VEC_INFO(N,M,TYPE,INTRINSIC)\
		template<size_t SIZE>\
		struct VecInfo<TYPE, SIZE, typename std::enable_if<ConstantOperation<size_t, SIZE, N>::ge && ConstantOperation<size_t, SIZE, M>::le>::type> {\
			enum {\
				size = SIZE,\
				has_intrinsic = 1\
			};\
			typedef TYPE type;\
			typedef INTRINSIC intrinsic_t;\
		};

#if defined(ANVIL_MMX) && ANVIL_ARCHITECTURE_BITS <= 32
		ANVIL_SPECIALISE_VEC_INFO(1, 8, int8_t, __m64)
		ANVIL_SPECIALISE_VEC_INFO(1, 8, uint8_t, __m64)
		ANVIL_SPECIALISE_VEC_INFO(1, 4, int16_t, __m64)
		ANVIL_SPECIALISE_VEC_INFO(1, 4, uint16_t, __m64)
		ANVIL_SPECIALISE_VEC_INFO(1, 2, int32_t, __m64)
		ANVIL_SPECIALISE_VEC_INFO(1, 2, uint32_t, __m64)
		ANVIL_SPECIALISE_VEC_INFO(1, 2, float, __m64)

		#define ANVIL_VEC_INFO_LOW_8 9
		#define ANVIL_VEC_INFO_LOW_16 5
		#define ANVIL_VEC_INFO_LOW_32 3
		#define ANVIL_VEC_INFO_LOW_64 1
#endif
#if defined(ANVIL_SSE)
	#if ! defined ANVIL_VEC_INFO_LOW_8
		#define ANVIL_VEC_INFO_LOW_8 1
		#define ANVIL_VEC_INFO_LOW_16 1
		#define ANVIL_VEC_INFO_LOW_32 1
		#define ANVIL_VEC_INFO_LOW_64 1
	#endif
		ANVIL_SPECIALISE_VEC_INFO(ANVIL_VEC_INFO_LOW_32, 4, float, __m128)
#else
#endif
#if defined(ANVIL_SSE2)
		ANVIL_SPECIALISE_VEC_INFO(ANVIL_VEC_INFO_LOW_8, 16, int8_t,    __m128i)
		ANVIL_SPECIALISE_VEC_INFO(ANVIL_VEC_INFO_LOW_8, 16, uint8_t,   __m128i)
		ANVIL_SPECIALISE_VEC_INFO(ANVIL_VEC_INFO_LOW_16, 8, int16_t,   __m128i)
		ANVIL_SPECIALISE_VEC_INFO(ANVIL_VEC_INFO_LOW_16, 8, uint16_t,  __m128i)
		ANVIL_SPECIALISE_VEC_INFO(ANVIL_VEC_INFO_LOW_32, 4, int32_t,   __m128i)
		ANVIL_SPECIALISE_VEC_INFO(ANVIL_VEC_INFO_LOW_32, 4, uint32_t,  __m128i)
		ANVIL_SPECIALISE_VEC_INFO(ANVIL_VEC_INFO_LOW_64, 2, int64_t,   __m128i)
		ANVIL_SPECIALISE_VEC_INFO(ANVIL_VEC_INFO_LOW_64, 2, uint64_t,  __m128i)
		ANVIL_SPECIALISE_VEC_INFO(ANVIL_VEC_INFO_LOW_64, 2, float64_t, __m128d)

		#undef ANVIL_VEC_INFO_LOW_8
		#undef ANVIL_VEC_INFO_LOW_16
		#undef ANVIL_VEC_INFO_LOW_32
		#undef ANVIL_VEC_INFO_LOW_64
		#define ANVIL_VEC_INFO_LOW_8 17
		#define ANVIL_VEC_INFO_LOW_16 9
		#define ANVIL_VEC_INFO_LOW_32 5
		#define ANVIL_VEC_INFO_LOW_64 3
#endif
#if defined(ANVIL_AVX)
		ANVIL_SPECIALISE_VEC_INFO(ANVIL_VEC_INFO_LOW_8, 32, int8_t,    __m256i)
		ANVIL_SPECIALISE_VEC_INFO(ANVIL_VEC_INFO_LOW_8, 32, uint8_t,   __m256i)
		ANVIL_SPECIALISE_VEC_INFO(ANVIL_VEC_INFO_LOW_16, 16, int16_t,  __m256i)
		ANVIL_SPECIALISE_VEC_INFO(ANVIL_VEC_INFO_LOW_16, 16, uint16_t, __m256i)
		ANVIL_SPECIALISE_VEC_INFO(ANVIL_VEC_INFO_LOW_32, 8, int32_t,   __m256i)
		ANVIL_SPECIALISE_VEC_INFO(ANVIL_VEC_INFO_LOW_32, 8, uint32_t,  __m256i)
		ANVIL_SPECIALISE_VEC_INFO(ANVIL_VEC_INFO_LOW_64, 4, int64_t,   __m256i)
		ANVIL_SPECIALISE_VEC_INFO(ANVIL_VEC_INFO_LOW_64, 4, uint64_t,  __m256i)
		ANVIL_SPECIALISE_VEC_INFO(ANVIL_VEC_INFO_LOW_32, 8, float32_t, __m256)
		ANVIL_SPECIALISE_VEC_INFO(ANVIL_VEC_INFO_LOW_64, 4, float64_t, __m256d)

		#undef ANVIL_VEC_INFO_LOW_8
		#undef ANVIL_VEC_INFO_LOW_16
		#undef ANVIL_VEC_INFO_LOW_32
		#undef ANVIL_VEC_INFO_LOW_64
		#define ANVIL_VEC_INFO_LOW_8 33
		#define ANVIL_VEC_INFO_LOW_16 17
		#define ANVIL_VEC_INFO_LOW_32 9
		#define ANVIL_VEC_INFO_LOW_64 5
#endif
#if defined(ANVIL_AVX_512)
		ANVIL_SPECIALISE_VEC_INFO(ANVIL_VEC_INFO_LOW_8, 64,  int8_t,    __m512i)
		ANVIL_SPECIALISE_VEC_INFO(ANVIL_VEC_INFO_LOW_8, 64,  uint8_t,   __m512i)
		ANVIL_SPECIALISE_VEC_INFO(ANVIL_VEC_INFO_LOW_16, 32, int16_t,   __m512i)
		ANVIL_SPECIALISE_VEC_INFO(ANVIL_VEC_INFO_LOW_16, 32, uint16_t,  __m512i)
		ANVIL_SPECIALISE_VEC_INFO(ANVIL_VEC_INFO_LOW_32, 16, int32_t,   __m512i)
		ANVIL_SPECIALISE_VEC_INFO(ANVIL_VEC_INFO_LOW_32, 16, uint32_t,  __m512i)
		ANVIL_SPECIALISE_VEC_INFO(ANVIL_VEC_INFO_LOW_64, 8,  int64_t,   __m512i)
		ANVIL_SPECIALISE_VEC_INFO(ANVIL_VEC_INFO_LOW_64, 8,  uint64_t,  __m512i)
		ANVIL_SPECIALISE_VEC_INFO(ANVIL_VEC_INFO_LOW_32, 16, float32_t, __m512)
		ANVIL_SPECIALISE_VEC_INFO(ANVIL_VEC_INFO_LOW_64, 8,  float64_t, __m512d)

		#undef ANVIL_VEC_INFO_LOW_8
		#undef ANVIL_VEC_INFO_LOW_16
		#undef ANVIL_VEC_INFO_LOW_32
		#undef ANVIL_VEC_INFO_LOW_64
		#define ANVIL_VEC_INFO_LOW_8 65
		#define ANVIL_VEC_INFO_LOW_16 33
		#define ANVIL_VEC_INFO_LOW_32 17
		#define ANVIL_VEC_INFO_LOW_64 9
#endif

		template<class INTRINSIC, class T, VectorOp VOP>
		struct VopInfo;

#define ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP,SYMBOL)\
		template<class INTRINSIC, class T>\
		struct VopInfo<INTRINSIC, T, VOP> {\
			enum { optimised = 0 };\
			static inline INTRINSIC execute(INTRINSIC a, INTRINSIC b) {\
				enum { LENGTH = sizeof(INTRINSIC) / sizeof(T) };\
				INTRINSIC c;\
				const T* const a_ = reinterpret_cast<const T*>(&a);\
				const T* const b_ = reinterpret_cast<const T*>(&b);\
				T* const c_ = reinterpret_cast<T*>(&c);\
				for (size_t i = 0; i < LENGTH; ++i) c_[i] = a_[i] SYMBOL b_[i];\
				return c;\
			}\
		};

	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_GT, > )
	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_LE, <= )
	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_GE, >= )

#define ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP,FUNCTION)\
		template<class INTRINSIC, class T>\
		struct VopInfo<INTRINSIC, T, VOP> {\
			enum { optimised = 0 };\
			static inline INTRINSIC execute(INTRINSIC a, INTRINSIC b) {\
				enum { LENGTH = sizeof(INTRINSIC) / sizeof(T) };\
				INTRINSIC c;\
				const T* const a_ = reinterpret_cast<const T*>(&a);\
				const T* const b_ = reinterpret_cast<const T*>(&b);\
				T* const c_ = reinterpret_cast<T*>(&c);\
				for (size_t i = 0; i < LENGTH; ++i) c_[i] = FUNCTION(a_[i], b_[i]);\
				return c;\
			}\
		};

	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_MIN, min)
	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_MAX, max)
	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_ATAN2, atan2)
	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_POW, pow)
	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_HYPOT, hypot)
	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_DIM, dim)

#define ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP,FUNCTION)\
		template<class INTRINSIC, class T>\
		struct VopInfo<INTRINSIC, T, VOP> {\
			enum { optimised = 0 };\
			static inline INTRINSIC execute(INTRINSIC a, INTRINSIC b, INTRINSIC c) {\
				enum { LENGTH = sizeof(INTRINSIC) / sizeof(T) };\
				INTRINSIC c;\
				const T* const a_ = reinterpret_cast<const T*>(&a);\
				const T* const b_ = reinterpret_cast<const T*>(&b);\
				T* const c_ = reinterpret_cast<T*>(&c);\
				for (size_t i = 0; i < LENGTH; ++i) c_[i] = FUNCTION(a_[i], b_[i], c_[i]);\
				return c;\
			}\
		};

	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_FMA, fma)
	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_FMS, fms)

#define ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP,FUNCTION)\
		template<class INTRINSIC, class T>\
		struct VopInfo<INTRINSIC, T, VOP> {\
			enum { optimised = 0 };\
			static inline INTRINSIC execute(INTRINSIC a) {\
				enum { LENGTH = sizeof(INTRINSIC) / sizeof(T) };\
				INTRINSIC c;\
				const T* const a_ = reinterpret_cast<const T*>(&a);\
				const T* const b_ = reinterpret_cast<const T*>(&b);\
				T* const c_ = reinterpret_cast<T*>(&c);\
				for (size_t i = 0; i < LENGTH; ++i) c_[i] = FUNCTION(a_[i]);\
				return c;\
			}\
		};

	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_NOT, not)
	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_SQRT, sqrt)
	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_CBRT, cbrt)
	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_SIN, sin)
	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_COS, cos)
	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_TAN, tan)
	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_ASIN, asin)
	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_ACOS, acos)
	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_ATAN, atan)
	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_SINH, sinh)
	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_COSH, cosh)
	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_TANH, tanh)
	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_PCN, popcount)
	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_REF, reflect)
	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_EXP, exp)
	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_LOG, log)
	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_LOG2, log2)
	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_LOG10, log10)
	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_CEIL, ceil)
	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_FLOOR, floor)
	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_TRUNC, trunc)
	ANVIL_SPECIALISE_DEFAULT_VOP_INFO(VOP_ROUND, round)

		//TODO VOP_SUM, VOP_AVG, VOP_FILL

#define ANVIL_SPECIALISE_VOP_INFO_VVV(VOP,TYPE,INTRINSIC,FUNCTION)\
		template<>\
		struct VopInfo<INTRINSIC, TYPE, VOP> {\
			enum { optimised = 1 };\
			static ANVIL_STRONG_INLINE INTRINSIC execute(INTRINSIC a, INTRINSIC b) {\
				return FUNCTION(a, b);\
			}\
		};

#define ANVIL_SPECIALISE_VOP_INFO_VV(VOP,TYPE,INTRINSIC,FUNCTION)\
		template<>\
		struct VopInfo<INTRINSIC, TYPE, VOP> {\
			enum { optimised = 1 };\
			static ANVIL_STRONG_INLINE INTRINSIC execute(INTRINSIC a) {\
				return FUNCTION(a);\
			}\
		};

#define ANVIL_SPECIALISE_VOP_INFO_VS(VOP,TYPE,INTRINSIC,FUNCTION)\
		template<>\
		struct VopInfo<INTRINSIC, TYPE, VOP> {\
			enum { optimised = 1 };\
			static ANVIL_STRONG_INLINE INTRINSIC execute(TYPE a) {\
				return FUNCTION(a);\
			}\
		};

#define ANVIL_SPECIALISE_VOP_INFO_SV(VOP,TYPE,INTRINSIC,FUNCTION)\
		template<>\
		struct VopInfo<INTRINSIC, TYPE, VOP> {\
			enum { optimised = 1 };\
			static ANVIL_STRONG_INLINE TYPE execute(INTRINSIC a) {\
				return FUNCTION(a);\
			}\
		};

#define ANVIL_SPECIALISE_VOP_INFO_VVVV(VOP,TYPE,INTRINSIC,FUNCTION)\
		template<>\
		struct VopInfo<INTRINSIC, TYPE, VOP> {\
			enum { optimised = 1 };\
			static ANVIL_STRONG_INLINE INTRINSIC execute(INTRINSIC a, INTRINSIC b, INTRINSIC c) {\
				return FUNCTION(a, b, c);\
			}\
		};

#if defined(ANVIL_SSE) && ANVIL_ARCHITECTURE_BITS <= 32
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_EQ, int32_t, __m64, _mm_cmpeq_pi32)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_GT, int32_t, __m64, _mm_cmpgt_pi32)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_AND, int32_t, __m64, _mm_and_si64)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_OR,  int32_t, __m64, _mm_or_si64)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_XOR, int32_t, __m64, _mm_xor_si64)

		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_ADD, int16_t, __m64, _mm_add_pi16)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_SUB, int16_t, __m64, _mm_sub_pi16)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_AND, int16_t, __m64, _mm_and_si64)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_OR,  int16_t, __m64, _mm_or_si64)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_XOR, int16_t, __m64, _mm_xor_si64)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_EQ,  int16_t,  __m64, _mm_cmpeq_pi16)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_GT,  int16_t,  __m64, _mm_cmpgt_pi16)

		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_ADD, int8_t, __m64, _mm_add_pi8)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_SUB, int8_t, __m64, _mm_sub_pi8)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_AND, int8_t, __m64, _mm_and_si64)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_OR,  int8_t, __m64, _mm_or_si64)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_XOR, int8_t, __m64, _mm_xor_si64)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_EQ,  int8_t,  __m64, _mm_cmpeq_pi8)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_GT,  int8_t,  __m64, _mm_cmpgt_pi8)
		
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_EQ,  uint32_t,  __m64, _mm_cmpeq_pi32)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_AND, uint32_t, __m64, _mm_and_si64)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_OR,  uint32_t, __m64, _mm_or_si64)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_XOR, uint32_t, __m64, _mm_xor_si64)

		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_ADD, uint16_t, __m64, _mm_adds_pu16)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_SUB, uint16_t, __m64, _mm_subs_pu16)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_AND, uint16_t, __m64, _mm_and_si64)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_OR,  uint16_t, __m64, _mm_or_si64)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_XOR, uint16_t, __m64, _mm_xor_si64)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_EQ,  uint16_t,  __m64, _mm_cmpeq_pi16)

		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_ADD, uint8_t, __m64, _mm_adds_pu8)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_SUB, uint8_t, __m64, _mm_subs_pu8)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_AND, uint8_t, __m64, _mm_and_si64)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_OR,  uint8_t, __m64, _mm_or_si64)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_XOR, uint8_t, __m64, _mm_xor_si64)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_EQ,  uint8_t, __m64, _mm_cmpeq_pi8)

		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_AND, float, __m64, _mm_and_si64)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_OR,  float, __m64, _mm_or_si64)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_XOR, float, __m64, _mm_xor_si64)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_EQ,  float, __m64, _mm_cmpeq_pi32)
#endif
#if defined(ANVIL_SSE)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_ADD, float, __m128, _mm_add_ps)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_SUB, float, __m128, _mm_sub_ps)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MUL, float, __m128, _mm_mul_ps)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_DIV, float, __m128, _mm_div_ps)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_AND, float, __m128, _mm_and_ps)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_OR,  float, __m128, _mm_or_ps)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_XOR, float, __m128, _mm_xor_ps)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_EQ,  float, __m128, _mm_cmpeq_ps)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_NE,  float, __m128, _mm_cmpneq_ps)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_GE,  float, __m128, _mm_cmpge_ps)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_LE,  float, __m128, _mm_cmple_ps)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_GT,  float, __m128, _mm_cmpgt_ps)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_LT,  float, __m128, _mm_cmplt_ps)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MIN, float, __m128, _mm_min_ps)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MAX, float, __m128, _mm_max_ps)
		ANVIL_SPECIALISE_VOP_INFO_VV(VOP_SQRT, float, __m128, _mm_sqrt_ps)
		ANVIL_SPECIALISE_VOP_INFO_VS(VOP_FILL, float, __m128, _mm_set1_ps)
#if ANVIL_ARCHITECTURE_BITS <= 32
		//! \todo casts
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MAX, int16_t, __m64, _mm_max_pi16)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MIN, int16_t, __m64, _mm_min_pi16)

		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MAX, uint8_t, __m64, _mm_max_pu8)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MIN, uint8_t, __m64, _mm_min_pu8)
#endif
#endif
#ifdef ANVIL_SSE2
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_ADD, double, __m128d, _mm_add_pd)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_SUB, double, __m128d, _mm_sub_pd)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MUL, double, __m128d, _mm_mul_pd)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_DIV, double, __m128d, _mm_div_pd)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_AND, double, __m128d, _mm_and_pd)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_OR,  double, __m128d, _mm_or_pd)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_XOR, double, __m128d, _mm_xor_pd)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_EQ,  double, __m128d, _mm_cmpeq_pd)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_NE,  double, __m128d, _mm_cmpneq_pd)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_GE,  double, __m128d, _mm_cmpge_pd)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_LE,  double, __m128d, _mm_cmple_pd)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_GT,  double, __m128d, _mm_cmpgt_pd)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_LT,  double, __m128d, _mm_cmplt_pd)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MIN, double, __m128d, _mm_min_pd)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MAX, double, __m128d, _mm_max_pd)
		ANVIL_SPECIALISE_VOP_INFO_VV(VOP_SQRT, double, __m128d, _mm_sqrt_pd)
		ANVIL_SPECIALISE_VOP_INFO_VS(VOP_FILL, double, __m128d, _mm_set1_pd)

		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_ADD, int64_t, __m128i, _mm_add_epi64)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_SUB, int64_t, __m128i, _mm_sub_epi64)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_AND, int64_t, __m128i, _mm_and_si128)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_OR,  int64_t, __m128i, _mm_or_si128)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_XOR, int64_t, __m128i, _mm_xor_si128)
		//ANVIL_SPECIALISE_VOP_INFO_VS(VOP_FILL, int64_t, __m128i, _mm_set1_epi64x)

		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_ADD, int32_t, __m128i, _mm_add_epi32)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_SUB, int32_t, __m128i, _mm_sub_epi32)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_AND, int32_t, __m128i, _mm_and_si128)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_OR,  int32_t, __m128i, _mm_or_si128)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_XOR, int32_t, __m128i, _mm_xor_si128)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_EQ,  int32_t, __m128i, _mm_cmpeq_epi32)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_GT,  int32_t, __m128i, _mm_cmpgt_epi32)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_LT,  int32_t, __m128i, _mm_cmplt_epi32)
		ANVIL_SPECIALISE_VOP_INFO_VS(VOP_FILL, int32_t, __m128i, _mm_set1_epi32)

		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_ADD, int16_t, __m128i, _mm_add_epi16)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_SUB, int16_t, __m128i, _mm_sub_epi16)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_AND, int16_t, __m128i, _mm_and_si128)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_OR,  int16_t, __m128i, _mm_or_si128)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_XOR, int16_t, __m128i, _mm_xor_si128)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_EQ,  int16_t, __m128i, _mm_cmpeq_epi16)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_GT,  int16_t, __m128i, _mm_cmpgt_epi16)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_LT,  int16_t, __m128i, _mm_cmplt_epi16)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MIN, int16_t, __m128i, _mm_min_epi16)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MAX, int16_t, __m128i, _mm_max_epi16)
		ANVIL_SPECIALISE_VOP_INFO_VS(VOP_FILL, int16_t, __m128i, _mm_set1_epi16)

		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_ADD, int8_t, __m128i, _mm_add_epi8)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_SUB, int8_t, __m128i, _mm_sub_epi8)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_AND, int8_t, __m128i, _mm_and_si128)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_OR,  int8_t, __m128i, _mm_or_si128)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_XOR, int8_t, __m128i, _mm_xor_si128)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_EQ,  int8_t, __m128i, _mm_cmpeq_epi8)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_GT,  int8_t, __m128i, _mm_cmpgt_epi8)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_LT,  int8_t, __m128i, _mm_cmplt_epi8)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MIN, int8_t, __m128i, _mm_min_epi8)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MAX, int8_t, __m128i, _mm_max_epi8)
		ANVIL_SPECIALISE_VOP_INFO_VS(VOP_FILL, int8_t, __m128i, _mm_set1_epi8)

		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_AND, uint64_t, __m128i, _mm_and_si128)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_OR,  uint64_t, __m128i, _mm_or_si128)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_XOR, uint64_t, __m128i, _mm_xor_si128)
		//ANVIL_SPECIALISE_VOP_INFO_VS(VOP_FILL, uint64_t, __m128i, _mm_set1_epi64x)

		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_AND, uint32_t, __m128i, _mm_and_si128)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_OR,  uint32_t, __m128i, _mm_or_si128)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_XOR, uint32_t, __m128i, _mm_xor_si128)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_EQ,  uint32_t, __m128i, _mm_cmpeq_epi32)
		ANVIL_SPECIALISE_VOP_INFO_VS(VOP_FILL, uint32_t, __m128i, _mm_set1_epi32)
			
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_ADD, uint16_t, __m128i, _mm_adds_epu16)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_SUB, uint16_t, __m128i, _mm_subs_epu16)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_AND, uint16_t, __m128i, _mm_and_si128)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_OR,  uint16_t, __m128i, _mm_or_si128)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_XOR, uint16_t, __m128i, _mm_xor_si128)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_EQ,  uint16_t, __m128i, _mm_cmpeq_epi16)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MIN, uint16_t, __m128i, _mm_min_epu16)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MAX, uint16_t, __m128i, _mm_max_epu16)
		ANVIL_SPECIALISE_VOP_INFO_VS(VOP_FILL, uint16_t, __m128i, _mm_set1_epi16)
			
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_ADD, uint8_t, __m128i, _mm_adds_epu8)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_SUB, uint8_t, __m128i, _mm_subs_epu8)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_AND, uint8_t, __m128i, _mm_and_si128)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_OR,  uint8_t, __m128i, _mm_or_si128)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_XOR, uint8_t, __m128i, _mm_xor_si128)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_EQ,  uint8_t, __m128i, _mm_cmpeq_epi8)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MIN, uint8_t, __m128i, _mm_min_epu8)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MAX, uint8_t, __m128i, _mm_max_epu8)
		ANVIL_SPECIALISE_VOP_INFO_VS(VOP_FILL, uint8_t, __m128i, _mm_set1_epi8)

		//! \todo casts
#endif
#if defined(ANVIL_SSSE3)
		ANVIL_SPECIALISE_VOP_INFO_VV(VOP_ABS, int32_t, __m128i, _mm_abs_epi32)
		ANVIL_SPECIALISE_VOP_INFO_VV(VOP_ABS, int16_t, __m128i, _mm_abs_epi16)
		ANVIL_SPECIALISE_VOP_INFO_VV(VOP_ABS, int8_t, __m128i, _mm_abs_epi8)

#if ANVIL_ARCHITECTURE_BITS == 32
		ANVIL_SPECIALISE_VOP_INFO_VV(VOP_ABS, int32_t, __m64, _mm_abs_pi32)
		ANVIL_SPECIALISE_VOP_INFO_VV(VOP_ABS, int16_t, __m64, _mm_abs_pi16)
		ANVIL_SPECIALISE_VOP_INFO_VV(VOP_ABS, int8_t, __m64, _mm_abs_pi8)
#endif
#endif
#if defined(ANVIL_SSE4_1)
	ANVIL_SPECIALISE_VOP_INFO_VV(VOP_CEIL, double, __m128d, _mm_ceil_pd)
	ANVIL_SPECIALISE_VOP_INFO_VV(VOP_FLOOR, double, __m128d, _mm_floor_pd)

	ANVIL_SPECIALISE_VOP_INFO_VV(VOP_CEIL, float, __m128, _mm_ceil_ps)
	ANVIL_SPECIALISE_VOP_INFO_VV(VOP_FLOOR, float, __m128, _mm_floor_ps)

	ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MAX, int32_t, __m128i, _mm_max_epi32)
	ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MIN, int32_t, __m128i, _mm_min_epi32)

	//ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MAX, int8_t, __m128i, _mm_max_epi8)
	//ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MIN, int8_t, __m128i, _mm_min_epi8)

	ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MAX, uint32_t, __m128i, _mm_max_epu32)
	ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MIN, uint32_t, __m128i, _mm_min_epu32)

	//ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MAX, uint16_t, __m128i, _mm_max_epu16)
	//ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MIN, uint16_t, __m128i, _mm_min_epu16)
#endif
#if defined(ANVIL_AVX)
	ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_ADD,  double, __m256d, _mm256_add_pd)
	ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_SUB,  double, __m256d, _mm256_sub_pd)
	ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MUL,  double, __m256d, _mm256_mul_pd)
	ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_DIV,  double, __m256d, _mm256_div_pd)
	ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_AND,  double, __m256d, _mm256_and_pd)
	ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_OR ,  double, __m256d, _mm256_or_pd)
	ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_XOR,  double, __m256d, _mm256_xor_pd)
	ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MAX,  double, __m256d, _mm256_max_pd)
	ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MIN,  double, __m256d, _mm256_min_pd)
	ANVIL_SPECIALISE_VOP_INFO_VV(VOP_SQRT,  double, __m256d, _mm256_sqrt_pd)
	ANVIL_SPECIALISE_VOP_INFO_VS(VOP_FILL,  double, __m256d, _mm256_set1_pd)
	ANVIL_SPECIALISE_VOP_INFO_VV(VOP_CEIL,  double, __m256d, _mm256_ceil_pd)
	ANVIL_SPECIALISE_VOP_INFO_VV(VOP_FLOOR, double, __m256d, _mm256_floor_pd)

	ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_ADD,  float, __m256, _mm256_add_ps)
	ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_SUB,  float, __m256, _mm256_sub_ps)
	ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MUL,  float, __m256, _mm256_mul_ps)
	ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_DIV,  float, __m256, _mm256_div_ps)
	ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_AND,  float, __m256, _mm256_and_ps)
	ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_OR,   float, __m256, _mm256_or_ps)
	ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_XOR,  float, __m256, _mm256_xor_ps)
	ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MIN,  float, __m256, _mm256_max_ps)
	ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MAX,  float, __m256, _mm256_min_ps)
	ANVIL_SPECIALISE_VOP_INFO_VV(VOP_SQRT,  float, __m256, _mm256_sqrt_ps)
	ANVIL_SPECIALISE_VOP_INFO_VS(VOP_FILL,  float, __m256, _mm256_set1_ps)
	ANVIL_SPECIALISE_VOP_INFO_VV(VOP_CEIL,  float, __m256, _mm256_ceil_ps)
	ANVIL_SPECIALISE_VOP_INFO_VV(VOP_FLOOR, float, __m256, _mm256_floor_ps)

	ANVIL_SPECIALISE_VOP_INFO_VS(VOP_FILL, int64_t,  __m256i, _mm256_set1_epi64x)
	ANVIL_SPECIALISE_VOP_INFO_VS(VOP_FILL, int32_t,  __m256i, _mm256_set1_epi32)
	ANVIL_SPECIALISE_VOP_INFO_VS(VOP_FILL, int16_t,  __m256i, _mm256_set1_epi16)
	ANVIL_SPECIALISE_VOP_INFO_VS(VOP_FILL, int8_t,   __m256i, _mm256_set1_epi8)
	ANVIL_SPECIALISE_VOP_INFO_VS(VOP_FILL, uint64_t, __m256i, _mm256_set1_epi64x)
	ANVIL_SPECIALISE_VOP_INFO_VS(VOP_FILL, uint32_t, __m256i, _mm256_set1_epi32)
	ANVIL_SPECIALISE_VOP_INFO_VS(VOP_FILL, uint16_t, __m256i, _mm256_set1_epi16)
	ANVIL_SPECIALISE_VOP_INFO_VS(VOP_FILL, uint8_t,  __m256i, _mm256_set1_epi8)

	//! \todo Support _mm_cmp_pd and _mm_cmp_ps, casts
#endif
#if defined(ANVIL_FMA)
	ANVIL_SPECIALISE_VOP_INFO_VVVV(VOP_FMA, double, __m256d, _mm256_fmadd_pd)
	ANVIL_SPECIALISE_VOP_INFO_VVVV(VOP_FMS, double, __m256d, _mm256_fmsub_pd)

	ANVIL_SPECIALISE_VOP_INFO_VVVV(VOP_FMA, float, __m256, _mm256_fmadd_ps)
	ANVIL_SPECIALISE_VOP_INFO_VVVV(VOP_FMS, float, __m256, _mm256_fmsub_ps)

	ANVIL_SPECIALISE_VOP_INFO_VVVV(VOP_FMA, double, __m128d, _mm_fmadd_pd)
	ANVIL_SPECIALISE_VOP_INFO_VVVV(VOP_FMS, double, __m128d, _mm_fmsub_pd)

	ANVIL_SPECIALISE_VOP_INFO_VVVV(VOP_FMA, float, __m128, _mm_fmadd_ps)
	ANVIL_SPECIALISE_VOP_INFO_VVVV(VOP_FMS, float, __m128, _mm_fmsub_ps)
#endif
#if defined(ANVIL_AVX2)
#if ANVIL_ARCHITECTURE_BITS == 32
		//ANVIL_SPECIALISE_VOP_INFO_VV(VOP_ABS, int64_t, __m256i, _mm256_abs_epi64)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_ADD, int64_t, __m256i, _mm256_add_epi64)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_SUB, int64_t, __m256i, _mm256_sub_epi64)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_AND, int64_t, __m256i, _mm256_and_si256)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_OR,  int64_t, __m256i, _mm256_or_si256)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_XOR, int64_t, __m256i, _mm256_xor_si256)

		ANVIL_SPECIALISE_VOP_INFO_VV(VOP_ABS, int32_t, __m256i, _mm256_abs_epi32)
#endif
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_ADD, int32_t, __m256i, _mm256_add_epi32)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_SUB, int32_t, __m256i, _mm256_sub_epi32)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_AND, int32_t, __m256i, _mm256_and_si256)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_OR,  int32_t, __m256i, _mm256_or_si256)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_XOR, int32_t, __m256i, _mm256_xor_si256)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MAX, int32_t, __m256i, _mm256_max_epi32)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MIN, int32_t, __m256i, _mm256_min_epi32)

		ANVIL_SPECIALISE_VOP_INFO_VV(VOP_ABS,  int16_t, __m256i, _mm256_abs_epi16)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_ADD, int16_t, __m256i, _mm256_add_epi16)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_SUB, int16_t, __m256i, _mm256_sub_epi16)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_AND, int16_t, __m256i, _mm256_and_si256)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_OR,  int16_t, __m256i, _mm256_or_si256)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_XOR, int16_t, __m256i, _mm256_xor_si256)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MAX, int16_t, __m256i, _mm256_max_epi16)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MIN, int16_t, __m256i, _mm256_min_epi16)

		ANVIL_SPECIALISE_VOP_INFO_VV(VOP_ABS,  int8_t, __m256i, _mm256_abs_epi8)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_ADD, int8_t, __m256i, _mm256_add_epi8)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_SUB, int8_t, __m256i, _mm256_sub_epi8)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_AND, int8_t, __m256i, _mm256_and_si256)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_OR,  int8_t, __m256i, _mm256_or_si256)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_XOR, int8_t, __m256i, _mm256_xor_si256)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MAX, int8_t, __m256i, _mm256_max_epi8)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MIN, int8_t, __m256i, _mm256_min_epi8)

#if ANVIL_ARCHITECTURE_BITS == 32
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_AND, uint64_t,__m256i, _mm256_and_si256)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_OR,  uint64_t,__m256i, _mm256_or_si256)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_XOR, uint64_t,__m256i, _mm256_xor_si256)
#endif

		//ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_ADD, uint32_t, __m256i, _mm256_adds_epu32)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_AND, uint32_t, __m256i, _mm256_and_si256)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_OR,  uint32_t, __m256i, _mm256_or_si256)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_XOR, uint32_t, __m256i, _mm256_xor_si256)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MAX, uint32_t, __m256i, _mm256_max_epu32)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MIN, uint32_t, __m256i, _mm256_min_epu32)

		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_ADD, uint16_t, __m256i, _mm256_adds_epu16)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_SUB, uint16_t, __m256i, _mm256_subs_epu16)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_AND, uint16_t, __m256i, _mm256_and_si256)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_OR,  uint16_t, __m256i, _mm256_or_si256)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_XOR, uint16_t, __m256i, _mm256_xor_si256)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MAX, uint16_t, __m256i, _mm256_max_epu16)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MIN, uint16_t, __m256i, _mm256_min_epu16)

		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_ADD, uint8_t, __m256i, _mm256_adds_epu8)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_SUB, uint8_t, __m256i, _mm256_subs_epu8)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_AND, uint8_t, __m256i, _mm256_and_si256)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_OR,  uint8_t, __m256i, _mm256_or_si256)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_XOR, uint8_t, __m256i, _mm256_xor_si256)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MAX, uint8_t, __m256i, _mm256_max_epu8)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MIN, uint8_t, __m256i, _mm256_min_epu8)
		//! \todo _mm256_avg_epu8, _mm256_avg_epu16
#endif
#ifdef ANVIL_AVX_512
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_ADD, double, __m512d, _mm512_add_pd)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_SUB, double, __m512d, _mm512_sub_pd)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MUL, double, __m512d, _mm512_mul_pd)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_DIV, double, __m512d, _mm512_div_pd)
		ANVIL_SPECIALISE_VOP_INFO_VV(VOP_SQRT, double, __m512d, _mm512_sqrt_pd)
		ANVIL_SPECIALISE_VOP_INFO_VV(VOP_ABS,  double, __m512d, _mm512_abs_pd)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MAX, double, __m512d, _mm512_max_pd)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MIN, double, __m512d, _mm512_min_pd)

		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_ADD, float, __m512, _mm512_add_ps)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_SUB, float, __m512, _mm512_sub_ps)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MUL, float, __m512, _mm512_mul_ps)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_DIV, float, __m512, _mm512_div_ps)
		ANVIL_SPECIALISE_VOP_INFO_VV(VOP_SQRT, float, __m512, _mm512_sqrt_ps)
		ANVIL_SPECIALISE_VOP_INFO_VV(VOP_ABS,  float, __m512, _mm512_abs_ps)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MAX, float, __m512, _mm512_max_ps)
		ANVIL_SPECIALISE_VOP_INFO_VVV(VOP_MIN, float, __m512, _mm512_min_ps)
#endif
		template<class T, size_t S, VectorOp VOP>
		struct VopOptimised {
			enum { value = 0 };
		};

		template<class T, VectorOp VOP>
		struct OptimalVectorLength {
			enum {
				value =
				VopOptimised<T, 64, VOP>::value ? 64 :
				VopOptimised<T, 32, VOP>::value ? 32 :
				VopOptimised<T, 16, VOP>::value ? 16 :
				VopOptimised<T, 8, VOP>::value ? 8 :
				VopOptimised<T, 4, VOP>::value ? 4 :
				VopOptimised<T, 2, VOP>::value ? 2 :
				1
			};
		};

		template<class T, int S, VectorOp VOP>
		struct RoundVectorLength { 
			enum { 
				value = 
				VopOptimised<T, 2, VOP>::value && S <= 2 ? 2 :
				VopOptimised<T, 4, VOP>::value && S <= 4 ? 4 :
				VopOptimised<T, 8, VOP>::value && S <= 8 ? 8 :
				VopOptimised<T, 16, VOP>::value && S <= 16 ? 16 :
				VopOptimised<T, 32, VOP>::value && S <= 32 ? 32 :
				VopOptimised<T, 64, VOP>::value && S <= 64 ? 64 :
				S
			}; 
		};

		template<class T, int S, VectorOp VOP>
		struct VectorLoopInfo {
			enum {
				HALF_OPTIMISED = S > 2 && VopOptimised<T, S/2, VOP>::value,    //!< If the operation is optimised at half the vector's size

				ROUND_UP_SIZE = RoundVectorLength<T,S,VOP>::value > S ? RoundVectorLength<T,S,VOP>::value : 0,

				_OPTIMISED_4 = S > 4 && VopOptimised<T, 4, VOP>::value,       //!< If the operaton is optimised at size 4 and vector size is larger
				_OPTIMISED_8 = S > 8 && VopOptimised<T, 8, VOP>::value,      //!< If the operaton is optimised at size 8 and vector size is larger
				_OPTIMISED_16 = S > 16 && VopOptimised<T, 16, VOP>::value,    //!< If the operaton is optimised at size 16 and vector size is larger
				_OPTIMISED_32 = S > 32 && VopOptimised<T, 32, VOP>::value,    //!< If the operaton is optimised at size 32 and vector size is larger
				_OPTIMISED_64 = S > 64 && VopOptimised<T, 64, VOP>::value,   //!< If the operaton is optimised at size 64 and vector size is larger
				
				OPTIMISED_SIZE =
					_OPTIMISED_64 ? 64 :
					_OPTIMISED_32 ? 32 :
					_OPTIMISED_16 ? 16 :
					_OPTIMISED_8 ? 8 :
					_OPTIMISED_4 ? 4 :
					0,                                                         //!< The largest optimised size that is smaller than half this vector

				OPTIMISED_LOOP = OPTIMISED_SIZE == 0 ? 0 : S / (OPTIMISED_SIZE == 0 ? 1 : OPTIMISED_SIZE),     //!< The number of loops iterations with OPTIMISED_SIZE vectors
				OPTIMISED_REMAINDER = OPTIMISED_SIZE == 0 ? 0 : S % (OPTIMISED_SIZE == 0 ? 1 : OPTIMISED_SIZE) //!< The number of loops iterations with trailing scalar values
			};
		};
	}

	template<class T = float, size_t S = detail::OptimalVectorLength<T>::value>
	struct Vector {
		typedef T type;
		enum {
			size = S,
		};
		static_assert(size > 1, "Minimum vector size is 2");
		typedef Vector<type, size> this_t;
		typedef Vector<type, size / 2> half_t;
		typedef typename detail::VFloat<type>::type float_t;

		type elements[size];

		ANVIL_CALL Vector() {
			simd::OperationImplementation<type, size, simd::OP_FILL>::execute(elements);
		}

		ANVIL_CALL Vector(T x) {
			simd::OperationImplementation<type, size, simd::OP_FILL>::execute(x, elements);
		}

		ANVIL_CALL Vector(T x, T y) {
			simd::OperationImplementation<type, size, simd::OP_FILL>::execute(x, y, elements);
		}

		ANVIL_CALL Vector(T x, T y, T z) {
			simd::OperationImplementation<type, size, simd::OP_FILL>::execute(x, y, z, elements);
		}

		ANVIL_CALL Vector(T x, T y, T z, T w) {
			simd::OperationImplementation<type, size, simd::OP_FILL>::execute(x, y, z, w, elements);
		}

		ANVIL_STRONG_INLINE half_t& ANVIL_CALL lowerHalf() throw() {
			return reinterpret_cast<half_t*>(this)[0];
		}

		ANVIL_STRONG_INLINE half_t& ANVIL_CALL upperHalf() throw() {
			return reinterpret_cast<half_t*>(this)[1];
		}

		ANVIL_STRONG_INLINE half_t ANVIL_CALL lowerHalf() const throw() {
			return reinterpret_cast<const half_t*>(this)[0];
		}

		ANVIL_STRONG_INLINE half_t ANVIL_CALL upperHalf() const throw() {
			return reinterpret_cast<const half_t*>(this)[1];
		}

		explicit ANVIL_CALL operator bool() const throw() {
			return !elementsEqual(static_cast<type>(0));
		}

		inline this_t ANVIL_CALL operator!() const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.elements[i] = !elements[i];
			return tmp;
		}

		ANVIL_STRONG_INLINE this_t ANVIL_CALL operator~() const throw() {
			this_t tmp;
			simd::OperationImplementation<T, S, simd::OP_NOT>::execute(elements, tmp.elements);
			return tmp;
		}

		ANVIL_STRONG_INLINE this_t& ANVIL_CALL operator++() throw() {
			*this += static_cast<type>(1);
			return *this;
		}

		ANVIL_STRONG_INLINE this_t& ANVIL_CALL operator--() throw() {
			*this -= static_cast<type>(1);
			return *this;
		}

		inline this_t ANVIL_CALL operator++(int) throw() {
			const this_t tmp(*this);
			*this += static_cast<type>(1);
			return tmp;
		}

		inline this_t ANVIL_CALL operator--(int) throw() {
			const this_t tmp(*this);
			*this -= static_cast<type>(1);
			return tmp;
		}

		ANVIL_STRONG_INLINE type ANVIL_CALL operator[](const size_t aIndex) const throw() {
			return elements[aIndex];
		}

		ANVIL_STRONG_INLINE type& ANVIL_CALL operator[](const size_t aIndex) throw() {
			return elements[aIndex];
		}

		ANVIL_STRONG_INLINE const type* ANVIL_CALL begin() const throw() {
			return elements;
		}

		ANVIL_STRONG_INLINE type* ANVIL_CALL begin() throw() {
			return elements;
		}

		ANVIL_STRONG_INLINE const type* ANVIL_CALL end() const throw() {
			return elements + size;
		}

		ANVIL_STRONG_INLINE type* ANVIL_CALL end() throw() {
			return elements + size;
		}

		//inline float_t ANVIL_CALL sumf() const throw() {
		//	typedef detail::VectorLoopInfo<type, size, detail::VOP_ADD> Info;
		//	if (Info::HALF_OPTIMISED) {
		//		return (lowerHalf() + upperHalf()).sumf();
		//	} else if (Info::OPTIMISED_SIZE) {
		//		const Vector<type, Info::OPTIMISED_SIZE>* ptr = reinterpret_cast<const Vector<type, Info::OPTIMISED_SIZE>*>(this);
		//		Vector<type, Info::OPTIMISED_SIZE> tmp = ptr[0];
		//		for (size_t i = 1; i < Info::OPTIMISED_LOOP; ++i) tmp += ptr[i];
		//		for (size_t i = 0; i < Info::OPTIMISED_REMAINDER; ++i) tmp[0] += ptr[Info::OPTIMISED_LOOP][i];
		//		return tmp.sumf();
		//	} else {
		//		type tmp = elements[0];
		//		for (size_t i = 1; i < size; ++i) tmp += elements[i];
		//		return tmp;
		//	}
		//}

		ANVIL_STRONG_INLINE bool ANVIL_CALL elementsEqual(const T a_scalar) const throw() {
			return elements[0] == a_scalar ? elementsEqual() : false;
		}

		//inline bool ANVIL_CALL elementsEqual() const throw() {
		//	typedef detail::VectorLoopInfo<type, size, detail::VOP_EQ> Info;
		//	if (Info::HALF_OPTIMISED) {
		//		const half_t tmp = lowerHalf();
		//		return (lowerHalf() == upperHalf()).sumf() == static_cast<float_t>(half_t::size) && tmp.elementsEqual();
		//	} else if (Info::OPTIMISED_SIZE) {
		//		const Vector<type, Info::OPTIMISED_SIZE>* ptr = reinterpret_cast<const Vector<type, Info::OPTIMISED_SIZE>*>(this);
		//		const Vector<type, Info::OPTIMISED_SIZE> tmp = ptr[0];
		//		if (!tmp.elementsEqual()) return false;
		//		for (size_t i = 1; i < Info::OPTIMISED_LOOP; ++i) if((ptr[i] == tmp).sumf() != static_cast<float_t>(size)) return false;
		//		for (size_t i = 0; i < Info::OPTIMISED_REMAINDER; ++i) if(ptr[0][0] != ptr[Info::OPTIMISED_LOOP][i]) return false;
		//		return true;
		//	} else {
		//		for (size_t i = 0; i < size; ++i) if(elements[0] != elements[i]) return false;
		//		return true;
		//	}
		//}

		ANVIL_STRONG_INLINE float_t ANVIL_CALL avgf() const throw() {
			return sumf() / static_cast<float_t>(size);
		}

		ANVIL_STRONG_INLINE type ANVIL_CALL sum() const throw() {
			return static_cast<type>(sumf());
		}

		ANVIL_STRONG_INLINE type ANVIL_CALL avg() const throw() {
			return static_cast<type>(avgf());
		}

		ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount() const throw() {
			return popcount<sizeof(type) * size>(this);
		}

		//inline type ANVIL_CALL min() const throw() {
		//	typedef detail::VectorLoopInfo<type, size, detail::VOP_MIN> Info;
		//	if (Info::HALF_OPTIMISED) {
		//		return anvil::min<half_t::type, half_t::size>(lowerHalf(), upperHalf()).min();
		//	} else if (Info::OPTIMISED_SIZE) {
		//		const Vector<type, Info::OPTIMISED_SIZE>* ptr = reinterpret_cast<const Vector<type, Info::OPTIMISED_SIZE>*>(this);
		//		Vector<type, Info::OPTIMISED_SIZE> tmp = ptr[0];
		//		for (size_t i = 1; i < Info::OPTIMISED_LOOP; ++i) anvil::min<type, Info::OPTIMISED_SIZE>(tmp, ptr[i]);
		//		for (size_t i = 0; i < Info::OPTIMISED_REMAINDER; ++i) tmp[0] = anvil::min(tmp[0], ptr[Info::OPTIMISED_LOOP][i]);
		//		return tmp.min();
		//	} else {
		//		type tmp = elements[0];
		//		for (size_t i = 1; i < size; ++i) tmp = anvil::min(tmp, elements[i]);
		//		return tmp;
		//	}
		//}

		//inline type ANVIL_CALL max() const throw() {
		//	typedef detail::VectorLoopInfo<type, size, detail::VOP_MAX> Info;
		//	if (Info::HALF_OPTIMISED) {
		//		return anvil::max<half_t::type, half_t::size>(lowerHalf(), upperHalf()).max();
		//	} else if (Info::OPTIMISED_SIZE) {
		//		const Vector<type, Info::OPTIMISED_SIZE>* ptr = reinterpret_cast<const Vector<type, Info::OPTIMISED_SIZE>*>(this);
		//		Vector<type, Info::OPTIMISED_SIZE> tmp = ptr[0];
		//		for (size_t i = 1; i < Info::OPTIMISED_LOOP; ++i) anvil::max<type, Info::OPTIMISED_SIZE>(tmp, ptr[i]);
		//		for (size_t i = 0; i < Info::OPTIMISED_REMAINDER; ++i) tmp[0] = anvil::max(tmp[0], ptr[Info::OPTIMISED_LOOP][i]);
		//		return tmp.max();
		//	} else {
		//		type tmp = elements[0];
		//		for (size_t i = 1; i < size; ++i) tmp = anvil::max(tmp, elements[i]);
		//		return tmp;
		//	}
		//}

		//inline float_t ANVIL_CALL dot(const this_t aOther) const throw() {
		//	if (std::is_same<float_t, type>::value) {
		//		float_t sum = static_cast<float_t>(0);
		//		for (size_t i = 0; i < size; ++i) sum = fma(elements[i], aOther.elements[i], sum);
		//		return sum;
		//	} else {
		//		Vector<float_t, size> a(*this);
		//		Vector<float_t, size> b(aOther);
		//		return a.dot(b);
		//	}
		//}

		//inline Vector<float_t, 3> ANVIL_CALL crossf(const this_t aOther) const throw() {
		//	Vector<float_t, 4> a, b, c, d;

		//	a[0] = static_cast<float_t>(elements[1]);
		//	a[1] = static_cast<float_t>(elements[2]);
		//	a[2] = static_cast<float_t>(elements[0]);
		//	a[3] = static_cast<float_t>(0.f);

		//	c[0] = static_cast<float_t>(elements[2]);
		//	c[1] = static_cast<float_t>(elements[0]);
		//	c[2] = static_cast<float_t>(elements[1]);
		//	c[3] = static_cast<float_t>(0.f);

		//	b[0] = static_cast<float_t>(aOther.elements[2]);
		//	b[1] = static_cast<float_t>(aOther.elements[0]);
		//	b[2] = static_cast<float_t>(aOther.elements[1]);
		//	b[3] = static_cast<float_t>(0.f);

		//	d[0] = static_cast<float_t>(aOther.elements[1]);
		//	d[1] = static_cast<float_t>(aOther.elements[2]);
		//	d[2] = static_cast<float_t>(aOther.elements[0]);
		//	d[3] = static_cast<float_t>(0.f);

		//	union {
		//		Vector<float_t, 4> v4;
		//		Vector<float_t, 3> v3;
		//	};
		//	v4 = anvil::fms<type, 4>(a, b, c * d);
		//	return v3;
		//}

		//inline Vector<T, 3> ANVIL_CALL cross(const this_t aOther) const throw() {
		//	return vector_cast<type, size>(crossf(aOther));
		//}

		//inline float_t ANVIL_CALL mag2f() const throw() {
		//	if (std::is_same<float_t, type>::value) {
		//		float_t sum = static_cast<float_t>(0);
		//		for (size_t i = 0; i < size; ++i) sum = fma(elements[i], elements[i], sum);
		//		return sum;
		//	} else {
		//		return Vector<float_t, size>(*this).mag2();
		//	}
		//}

		ANVIL_STRONG_INLINE float_t ANVIL_CALL magf() const throw() {
			return sqrt(mag2f());
		}

		ANVIL_STRONG_INLINE type ANVIL_CALL mag2() const throw() {
			return static_cast<type>(mag2f());
		}

		ANVIL_STRONG_INLINE type ANVIL_CALL mag() const throw() {
			return static_cast<type>(magf());
		}

		inline Vector<float_t, size> ANVIL_CALL normalisef() const throw() {
			Vector<float_t, size> tmp = static_cast<Vector<float_t, size>>(*this);
			tmp = tmp * tmp;
			tmp /= fill<float_t, size>(tmp.sumf());
			return tmp;
		}

		ANVIL_STRONG_INLINE this_t ANVIL_CALL normalise() const throw() {
			return vector_cast<type, size>(normalisef());
		}

		template<class T2, size_t S2>
		Vector<type, S2> ANVIL_CALL swizzle(const Vector<T2, S2> aOther) const throw() {
			Vector<type, S2> tmp;
			for (size_t i = 0; i < S2; ++i) tmp[i] = elements[static_cast<size_t>(aOther[i])];
			return tmp;
		}

		inline this_t ANVIL_CALL sort() const throw() {
			this_t tmp(*this);
			std::sort(tmp.begin(), tmp.end());
			return tmp;
		}
	};

	// Vector Operators

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_CALL operator+(const Vector<T, S> x, const Vector<T, S> y) {
		Vector<T, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_ADD>::execute(x.elements, y.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_CALL operator-(const Vector<T, S> x, const Vector<T, S> y) {
		Vector<T, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_SUB>::execute(x.elements, y.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_CALL operator*(const Vector<T, S> x, const Vector<T, S> y) {
		Vector<T, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_MUL>::execute(x.elements, y.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_CALL operator/(const Vector<T, S> x, const Vector<T, S> y) {
		Vector<T, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_DIV>::execute(x.elements, y.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_CALL operator&(const Vector<T, S> x, const Vector<T, S> y) {
		Vector<T, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_AND>::execute(x.elements, y.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_CALL operator|(const Vector<T, S> x, const Vector<T, S> y) {
		Vector<T, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_OR>::execute(x.elements, y.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_CALL operator^(const Vector<T, S> x, const Vector<T, S> y) {
		Vector<T, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_XOR>::execute(x.elements, y.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_CALL operator<<(const Vector<T, S> x, const Vector<T, S> y) {
		Vector<T, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_LSHIFT>::execute(x.elements, y.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_CALL operator>>(const Vector<T, S> x, const Vector<T, S> y) {
		Vector<T, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_RSHIFT>::execute(x.elements, y.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_CALL operator%(const Vector<T, S> x, const Vector<T, S> y) {
		Vector<T, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_MOD>::execute(x.elements, y.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S>& ANVIL_CALL operator+=(Vector<T, S>& x, const Vector<T, S> y) {
		simd::OperationImplementation<T, S, simd::OP_ADD>::execute(x.elements, y.elements, x.elements);
		return x;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S>& ANVIL_CALL operator-=(Vector<T, S>& x, const Vector<T, S> y) {
		simd::OperationImplementation<T, S, simd::OP_SUB>::execute(x.elements, y.elements, x.elements);
		return x;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S>& ANVIL_CALL operator*=(Vector<T, S>& x, const Vector<T, S> y) {
		simd::OperationImplementation<T, S, simd::OP_MUL>::execute(x.elements, y.elements, x.elements);
		return x;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S>& ANVIL_CALL operator/=(Vector<T, S>& x, const Vector<T, S> y) {
		simd::OperationImplementation<T, S, simd::OP_DIV>::execute(x.elements, y.elements, x.elements);
		return x;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S>& ANVIL_CALL operator&=(Vector<T, S>& x, const Vector<T, S> y) {
		simd::OperationImplementation<T, S, simd::OP_AND>::execute(x.elements, y.elements, x.elements);
		return x;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S>& ANVIL_CALL operator|=(Vector<T, S>& x, const Vector<T, S> y) {
		simd::OperationImplementation<T, S, simd::OP_OR>::execute(x.elements, y.elements, x.elements);
		return x;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S>& ANVIL_CALL operator^=(Vector<T, S>& x, const Vector<T, S> y) {
		simd::OperationImplementation<T, S, simd::OP_XOR>::execute(x.elements, y.elements, x.elements);
		return x;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S>& ANVIL_CALL operator<<=(Vector<T, S>& x, const Vector<T, S> y) {
		simd::OperationImplementation<T, S, simd::OP_LSHIFT>::execute(x.elements, y.elements, x.elements);
		return x;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S>& ANVIL_CALL operator>>=(Vector<T, S>& x, const Vector<T, S> y) {
		simd::OperationImplementation<T, S, simd::OP_RSHIFT>::execute(x.elements, y.elements, x.elements);
		return x;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S>& ANVIL_CALL operator%=(Vector<T, S>& x, const Vector<T, S> y) {
		simd::OperationImplementation<T, S, simd::OP_MOD>::execute(x.elements, y.elements, x.elements);
		return x;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_CALL operator==(const Vector<T, S> x, const Vector<T, S> y) {
		Vector<T, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_CMPEQ>::execute(x.elements, y.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_CALL operator!=(const Vector<T, S> x, const Vector<T, S> y) {
		Vector<T, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_CMPNE>::execute(x.elements, y.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_CALL operator<(const Vector<T, S> x, const Vector<T, S> y) {
		Vector<T, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_CMPLT>::execute(x.elements, y.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_CALL operator>(const Vector<T, S> x, const Vector<T, S> y) {
		Vector<T, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_CMPGT>::execute(x.elements, y.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_CALL operator<=(const Vector<T, S> x, const Vector<T, S> y) {
		Vector<T, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_CMPLE>::execute(x.elements, y.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_CALL operator>=(const Vector<T, S> x, const Vector<T, S> y) {
		Vector<T, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_CMPGT>::execute(x.elements, y.elements, tmp.elements);
		return tmp;
	}

	// Vector functions

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_CALL reflect(const Vector<T, S> x) {
		Vector<size_t, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_REFLECT>::execute(x.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_CALL fma(const Vector<T, S> x, const Vector<T, S> y, const Vector<T, S> z) {
		Vector<size_t, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_FMA>::execute(x.elements, y.elements, z.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_CALL fms(const Vector<T, S> x, const Vector<T, S> y, const Vector<T, S> z) {
		Vector<size_t, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_FMS>::execute(x.elements, y.elements, z.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_CALL dim(const Vector<T, S> x, const Vector<T, S> y) {
		Vector<size_t, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_DIM>::execute(x.elements, y.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_CALL atan2(const Vector<T, S> x, const Vector<T, S> y) {
		Vector<size_t, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_ATAN2>::execute(x.elements, y.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_CALL abs(const Vector<T, S> x) {
		Vector<size_t, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_ABS>::execute(x.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_CALL exp(const Vector<T, S> x) {
		Vector<size_t, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_EXP>::execute(x.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_CALL log(const Vector<T, S> x) {
		Vector<size_t, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_LOG>::execute(x.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_CALL log2(const Vector<T, S> x) {
		Vector<size_t, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_LOG2>::execute(x.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_CALL log10(const Vector<T, S> x) {
		Vector<size_t, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_LOG10>::execute(x.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_CALL ceil(const Vector<T, S> x) {
		Vector<size_t, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_CEIL>::execute(x.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_CALL floor(const Vector<T, S> x) {
		Vector<size_t, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_FLOOR>::execute(x.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_CALL round(const Vector<T, S> x) {
		Vector<size_t, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_ROUND>::execute(x.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_CALL sin(const Vector<T, S> x) {
		Vector<size_t, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_SIN>::execute(x.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_CALL cos(const Vector<T, S> x) {
		Vector<size_t, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_COS>::execute(x.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_CALL tan(const Vector<T, S> x) {
		Vector<size_t, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_TAN>::execute(x.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_CALL asin(const Vector<T, S> x) {
		Vector<size_t, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_ASIN>::execute(x.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_CALL acos(const Vector<T, S> x) {
		Vector<size_t, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_ACOS>::execute(x.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_CALL atan(const Vector<T, S> x) {
		Vector<size_t, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_ATAN>::execute(x.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_CALL sinh(const Vector<T, S> x) {
		Vector<size_t, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_SINH>::execute(x.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_CALL cosh(const Vector<T, S> x) {
		Vector<size_t, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_COSH>::execute(x.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_CALL tanh(const Vector<T, S> x) {
		Vector<size_t, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_TANH>::execute(x.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_CALL sqrt(const Vector<T, S> x) {
		Vector<size_t, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_SQRT>::execute(x.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_CALL cbrt(const Vector<T, S> x) {
		Vector<size_t, S> tmp;
		simd::OperationImplementation<T, S, simd::OP_CBRT>::execute(x.elements, tmp.elements);
		return tmp;
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE T ANVIL_CALL avg(const Vector<T, S> x) {
		return simd::OperationImplementation<T, S, simd::OP_AVG>::execute(x.elements, tmp.elements);
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE T ANVIL_CALL sum(const Vector<T, S> x) {
		return simd::OperationImplementation<T, S, simd::OP_SUM>::execute(x.elements, tmp.elements);
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount(const Vector<T, S> x) {
		return simd::OperationImplementation<T, S, simd::OP_POPCN>::execute(x.elements);
	}

	// Vector helpers

	//template<class T, size_t S, size_t S2>
	//static inline Vector<T, S> vector_resize(const Vector<T, S2> aVec) {
	//	union {
	//		Vector<T, S2> a;
	//		Vector<T, S> b;
	//	};
	//	if(S > S2) memset(&b, 0, sizeof(T) * S);
	//	a = aVec;
	//	return b;
	//}

	//template<class T, size_t S, class T2>
	//static inline Vector<T, S> vector_cast(const Vector<T2, S> aVec) {
	//	Vector<T, S> tmp;
	//	for (size_t i = 0; i < S; ++i) tmp[i] = static_cast<T>(aVec[i]);
	//	return tmp;
	//}

	template<class T, size_t S>
	struct Widen<Vector<T,S>> {
		typedef Vector<typename Widen<T>::type, S> type;
	};

	template<class T, size_t S>
	using VectorP4 = Vector<T, (S + 3) & (~3)>;

	template<Type TYPE>
	using AnvilVector = Vector<typename TypeFromEnum<GetPrimativeType(TYPE)>::type, GetChannels(TYPE)>;

	typedef Vector<signed char, 2> char2;
	typedef Vector<signed char, 3> char3;
	typedef Vector<signed char, 4> char4;
	typedef Vector<unsigned char, 2> uchar2;
	typedef Vector<unsigned char, 3> uchar3;
	typedef Vector<unsigned char, 4> uchar4;
	typedef Vector<short, 2> short2;
	typedef Vector<short, 3> short3;
	typedef Vector<short, 4> short4;
	typedef Vector<unsigned short, 2> ushort2;
	typedef Vector<unsigned short, 3> ushort3;
	typedef Vector<unsigned short, 4> ushort4;
	typedef Vector<int, 2> int2;
	typedef Vector<int, 3> int3;
	typedef Vector<int, 4> int4;
	typedef Vector<unsigned int, 2> uint2;
	typedef Vector<unsigned int, 3> uint3;
	typedef Vector<unsigned int, 4> uint4;
	typedef Vector<float, 2> float2;
	typedef Vector<float, 3> float3;
	typedef Vector<float, 4> float4;
	typedef Vector<double, 2> double2;
	typedef Vector<double, 3> double3;
	typedef Vector<double, 4> double4;

	typedef Vector<uint8_t, 2>  uint8_2;
	typedef Vector<uint8_t, 3>  uint8_3;
	typedef Vector<uint8_t, 4>  uint8_4;
	typedef Vector<uint8_t, 8>  uint8_8;
	typedef Vector<uint8_t, 16> uint8_16;
	typedef Vector<uint8_t, 32> uint8_32;
	typedef Vector<uint8_t, 64> uint8_64;

	typedef Vector<int8_t, 2>  int8_2;
	typedef Vector<int8_t, 3>  int8_3;
	typedef Vector<int8_t, 4>  int8_4;
	typedef Vector<int8_t, 8>  int8_8;
	typedef Vector<int8_t, 16> int8_16;
	typedef Vector<int8_t, 32> int8_32;
	typedef Vector<int8_t, 64> int8_64;

	typedef Vector<uint16_t, 2>  uint16_2;
	typedef Vector<uint16_t, 3>  uint16_3;
	typedef Vector<uint16_t, 4>  uint16_4;
	typedef Vector<uint16_t, 8>  uint16_8;
	typedef Vector<uint16_t, 16> uint16_16;
	typedef Vector<uint16_t, 32> uint16_32;
	typedef Vector<uint16_t, 64> uint16_64;

	typedef Vector<int16_t, 2>  int16_2;
	typedef Vector<int16_t, 3>  int16_3;
	typedef Vector<int16_t, 4>  int16_4;
	typedef Vector<int16_t, 8>  int16_8;
	typedef Vector<int16_t, 16> int16_16;
	typedef Vector<int16_t, 32> int16_32;
	typedef Vector<int16_t, 64> int16_64;

	typedef Vector<uint32_t, 2>  uint32_2;
	typedef Vector<uint32_t, 3>  uint32_3;
	typedef Vector<uint32_t, 4>  uint32_4;
	typedef Vector<uint32_t, 8>  uint32_8;
	typedef Vector<uint32_t, 16> uint32_16;
	typedef Vector<uint32_t, 32> uint32_32;
	typedef Vector<uint32_t, 64> uint32_64;

	typedef Vector<int32_t, 2>  int32_2;
	typedef Vector<int32_t, 3>  int32_3;
	typedef Vector<int32_t, 4>  int32_4;
	typedef Vector<int32_t, 8>  int32_8;
	typedef Vector<int32_t, 16> int32_16;
	typedef Vector<int32_t, 32> int32_32;
	typedef Vector<int32_t, 64> int32_64;

	typedef Vector<uint64_t, 2>  uint64_2;
	typedef Vector<uint64_t, 3>  uint64_3;
	typedef Vector<uint64_t, 4>  uint64_4;
	typedef Vector<uint64_t, 8>  uint64_8;
	typedef Vector<uint64_t, 16> uint64_16;
	typedef Vector<uint64_t, 32> uint64_32;
	typedef Vector<uint64_t, 64> uint64_64;

	typedef Vector<int64_t, 2>  int64_2;
	typedef Vector<int64_t, 3>  int64_3;
	typedef Vector<int64_t, 4>  int64_4;
	typedef Vector<int64_t, 8>  int64_8;
	typedef Vector<int64_t, 16> int64_16;
	typedef Vector<int64_t, 32> int64_32;
	typedef Vector<int64_t, 64> int64_64;

	typedef Vector<float32_t, 2>  float32_2;
	typedef Vector<float32_t, 3>  float32_3;
	typedef Vector<float32_t, 4>  float32_4;
	typedef Vector<float32_t, 8>  float32_8;
	typedef Vector<float32_t, 16> float32_16;
	typedef Vector<float32_t, 32> float32_32;
	typedef Vector<float32_t, 64> float32_64;

	typedef Vector<float64_t, 2>  float64_2;
	typedef Vector<float64_t, 3>  float64_3;
	typedef Vector<float64_t, 4>  float64_4;
	typedef Vector<float64_t, 8>  float64_8;
	typedef Vector<float64_t, 16> float64_16;
	typedef Vector<float64_t, 32> float64_32;
	typedef Vector<float64_t, 64> float64_64;
}

template<class T, size_t S>
static std::ostream& operator<<(std::ostream& s, const anvil::Vector<T, S> x) {
	s << '[';
	for (size_t i = 0; i < S; ++i) {
		s << x.elements[i];
		if (i + 1 < S) s << ',' << ' ';
	}
	s << ']';
	return s;
}

template<class T, size_t S>
static std::istream& operator>>(std::istream& s, const anvil::Vector<T, S> x) {
	char buf;
	s >> buf;
	for (size_t i = 0; i < S; ++i) {
		s >> x.elements[i];
		if (i + 1 < S) s >> buf;
	}
	s >> buf;
	return s;
}

#endif