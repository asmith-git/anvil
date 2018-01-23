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

#ifdef ANVIL_AVX_512
	enum { ANVIL_USE_AVX_512 = 1 };
	//#include ?
	#define ANVIL_AVX2
#else
	enum { ANVIL_USE_AVX_512 = 0 };
#endif

#ifdef ANVIL_AVX2
	enum { ANVIL_USE_AVX2 = 1 };
	//#include <zmmintrin.h>
	#define ANVIL_AVX
#else
	enum { ANVIL_USE_AVX2 = 0 };
#endif

#ifdef ANVIL_AVX
	enum { ANVIL_USE_AVX = 1 };
#include <immintrin.h>
	#define ANVIL_SSE4_2
	#define ANVIL_FMA
#else
	enum { ANVIL_USE_AVX = 0 };
#endif

#ifdef ANVIL_FMA
	enum { ANVIL_USE_FMA = 1 };
#else
	enum { ANVIL_USE_FMA = 0 };
#endif

#ifdef ANVIL_SSE4_2
	enum { ANVIL_USE_SSS4_2 = 1 };
#include <nmmintrin.h>
	#define ANVIL_SSE4_1
#else
	enum { ANVIL_USE_SSS4_2 = 0 };
#endif

#ifdef ANVIL_SSE4_1
	enum { ANVIL_USE_SSS4_1 = 1 };
	#include <smmintrin.h>
	#define ANVIL_SSE3
#else
	enum { ANVIL_USE_SSS4_1 = 0 };
#endif

#ifdef ANVIL_SSE3
	enum { ANVIL_USE_SSE3 = 1 };
	#include <tmmintrin.h>
	#define ANVIL_SSSE3
#else
	enum { ANVIL_USE_SSE3 = 0 };
#endif

#ifdef ANVIL_SSSE3
	enum { ANVIL_USE_SSSE3 = 1 };
	#include <pmmintrin.h>
	#define ANVIL_SSE2
#else
	enum { ANVIL_USE_SSSE3 = 0 };
#endif

#ifdef ANVIL_SSE2
	enum { ANVIL_USE_SSE2 = 1 };
	#include <emmintrin.h>
	#define ANVIL_SSE
#else
	enum { ANVIL_USE_SSE2 = 0 };
#endif

#ifdef ANVIL_SSE
	enum { ANVIL_USE_SSE = 1 };
	#include <xmmintrin.h>
#if ANVIL_ARCHITECTURE_BITS <= 32
	#define ANVIL_MMX
#endif
#else
	enum { ANVIL_USE_SSE = 0 };
#endif

#ifdef ANVIL_MMX
	enum { ANVIL_USE_MMX = 1 };
	#include <mmintrin.h>
#else
	enum { ANVIL_USE_MMX = 0 };
#endif

namespace anvil {

	// ---- FILL ----

	template<class T, size_t S>
	struct Vector {
		T elements[S];
	};

	namespace vec {
		template<class T, size_t S>
		static ANVIL_CALL Vector<T, S> fill_0() {
			Vector<T, S> tmp;
			memset(&tmp, 0, sizeof(T) * S);
			return tmp;
		}

		template<class T, size_t S>
		static ANVIL_CALL Vector<T, S> fill(T x) {
			Vector<T, S> tmp;
			for (size_t i = 0; i < S; ++i) tmp.elements[i] = x;
			return tmp;
		}

		template<class T, size_t S>
		static ANVIL_CALL Vector<T, S> fill(T x, T y) {
			static_assert(S >= 2, "Vector must have at least 2 elements")
			Vector<T, S> tmp;
			tmp.elements[0] = x;
			tmp.elements[1] = y;
			for (size_t i = 2; i < S; ++i) tmp.elements[i] = static_cast<T>(0);
			return tmp;
		}

		template<class T, size_t S>
		static ANVIL_CALL Vector<T, S> fill(T x, T y, T z) {
			static_assert(S >= 3, "Vector must have at least 3 elements")
			Vector<T, S> tmp;
			tmp.elements[0] = x;
			tmp.elements[1] = y;
			tmp.elements[2] = z;
			for (size_t i = 3; i < S; ++i) tmp.elements[i] = static_cast<T>(0);
			return tmp;
		}

		template<class T, size_t S>
		static ANVIL_CALL Vector<T, S> fill(T x, T y, T z, T w) {
			static_assert(S >= 4, "Vector must have at least 3 elements")
			Vector<T, S> tmp;
			tmp.elements[0] = x;
			tmp.elements[1] = y;
			tmp.elements[2] = z;
			tmp.elements[3] = w;
			for (size_t i = 3; i < S; ++i) tmp.elements[i] = static_cast<T>(0);
			return tmp;
		}

		namespace detail {
			template<class T, class T2>
			static ANVIL_STRONG_INLINE T ANVIL_CALL value_cast(T2 aValue) {
				union {
					T v1;
					T2 v2;
				};
				v1 = aValue;
				return v2;
			}
		}

#define ANVIL_VALUE_CAST(T,X) detail::value_cast<T>(X)

#define ANVIL_SPECIALISE_VEC_FILL_0(TYPE,SIZE,INTRINSIC,FUNCTION) \
		template<>\
		static ANVIL_STRONG_INLINE Vector<TYPE, SIZE> ANVIL_CALL fill_0<TYPE, SIZE>() {\
			union {\
				Vector<TYPE, SIZE> vector;\
				INTRINSIC intrinsic;\
			};\
			intrinsic = FUNCTION();\
			return vector;\
		}

#define ANVIL_SPECIALISE_VEC_FILL_XN(TYPE,TYPE2,SIZE,INTRINSIC,FUNCTION) \
		template<>\
		static ANVIL_STRONG_INLINE Vector<TYPE, SIZE> ANVIL_CALL fill<TYPE, SIZE>(TYPE x) {\
			static_assert(sizeof(TYPE) == sizeof(TYPE2), "Types must be the same size");\
			union {\
				Vector<TYPE, SIZE> vector;\
				INTRINSIC intrinsic;\
			};\
			intrinsic = FUNCTION(ANVIL_VALUE_CAST(TYPE2, x));\
			return vector;\
		}

#define ANVIL_SPECIALISE_VEC_FILL_XY(TYPE,TYPE2,SIZE,INTRINSIC,FUNCTION) \
		template<>\
		static ANVIL_STRONG_INLINE Vector<TYPE, SIZE> ANVIL_CALL fill<TYPE, SIZE>(TYPE x, TYPE y) {\
			static_assert(sizeof(TYPE) == sizeof(TYPE2), "Types must be the same size");\
			union {\
				Vector<TYPE, SIZE> vector;\
				INTRINSIC intrinsic;\
			};\
			intrinsic = FUNCTION(ANVIL_VALUE_CAST(TYPE2, x), ANVIL_VALUE_CAST(TYPE2, y));\
			return vector;\
		}

#define ANVIL_SPECIALISE_VEC_FILL_XYZ(TYPE,TYPE2,SIZE,INTRINSIC,FUNCTION) \
		template<>\
		static ANVIL_STRONG_INLINE Vector<TYPE, SIZE> ANVIL_CALL fill<TYPE, SIZE>(TYPE x, TYPE y, TYPE z) {\
			static_assert(sizeof(TYPE) == sizeof(TYPE2), "Types must be the same size");\
			union {\
				Vector<TYPE, SIZE> vector;\
				INTRINSIC intrinsic;\
			};\
			intrinsic = FUNCTION(ANVIL_VALUE_CAST(TYPE2, x), ANVIL_VALUE_CAST(TYPE2, y), ANVIL_VALUE_CAST(TYPE2, z));\
			return vector;\
		}

#define ANVIL_SPECIALISE_VEC_FILL_XYZW(TYPE,TYPE2,SIZE,INTRINSIC,FUNCTION) \
		template<>\
		static ANVIL_STRONG_INLINE Vector<TYPE, SIZE> ANVIL_CALL fill<TYPE, SIZE>(TYPE x, TYPE y, TYPE z, TYPE w) {\
			static_assert(sizeof(TYPE) == sizeof(TYPE2), "Types must be the same size");\
			union {\
				Vector<TYPE, SIZE> vector;\
				INTRINSIC intrinsic;\
			};\
			intrinsic = FUNCTION(ANVIL_VALUE_CAST(TYPE2, x), ANVIL_VALUE_CAST(TYPE2, y),ANVIL_VALUE_CAST(TYPE2, z),ANVIL_VALUE_CAST(TYPE2, w));\
			return vector;\
		}

#define ANVIL_SPECIALISE_VEC_FILL_XY4(TYPE,TYPE2,SIZE,INTRINSIC,FUNCTION) \
		template<>\
		static ANVIL_STRONG_INLINE Vector<TYPE, SIZE> ANVIL_CALL fill<TYPE, SIZE>(TYPE x, TYPE y) {\
			static_assert(sizeof(TYPE) == sizeof(TYPE2), "Types must be the same size");\
			union {\
				Vector<TYPE, SIZE> vector;\
				INTRINSIC intrinsic;\
			};\
			intrinsic = FUNCTION(ANVIL_VALUE_CAST(TYPE2, x), ANVIL_VALUE_CAST(TYPE2, y), static_cast<TYPE2>(0), static_cast<TYPE2>(0));\
			return vector;\
		}

#define ANVIL_SPECIALISE_VEC_FILL_XYZ4(TYPE,TYPE2,SIZE,INTRINSIC,FUNCTION) \
		template<>\
		static ANVIL_STRONG_INLINE Vector<TYPE, SIZE> ANVIL_CALL fill<TYPE, SIZE>(TYPE x, TYPE y, TYPE z) {\
			static_assert(sizeof(TYPE) == sizeof(TYPE2), "Types must be the same size");\
			union {\
				Vector<TYPE, SIZE> vector;\
				INTRINSIC intrinsic;\
			};\
			intrinsic = FUNCTION(ANVIL_VALUE_CAST(TYPE2, x), ANVIL_VALUE_CAST(TYPE2, y), ANVIL_VALUE_CAST(TYPE2, z), static_cast<TYPE2>(0));\
			return vector;\
		}

#define ANVIL_SPECIALISE_VEC_FILL_XYZW4(TYPE,TYPE2,SIZE,INTRINSIC,FUNCTION) \
		template<>\
		static ANVIL_STRONG_INLINE Vector<TYPE, SIZE> ANVIL_CALL fill<TYPE, SIZE>(TYPE x, TYPE y, TYPE z, TYPE w) {\
			static_assert(sizeof(TYPE) == sizeof(TYPE2), "Types must be the same size");\
			union {\
				Vector<TYPE, SIZE> vector;\
				INTRINSIC intrinsic;\
			};\
			intrinsic = FUNCTION(ANVIL_VALUE_CAST(TYPE2, x), ANVIL_VALUE_CAST(TYPE2, y), ANVIL_VALUE_CAST(TYPE2, z), ANVIL_VALUE_CAST(TYPE2, w));\
			return vector;\
		}

#define ANVIL_SPECIALISE_VEC_FILL_XY8(TYPE,TYPE2,SIZE,INTRINSIC,FUNCTION) \
		template<>\
		static ANVIL_STRONG_INLINE Vector<TYPE, SIZE> ANVIL_CALL fill<TYPE, SIZE>(TYPE x, TYPE y) {\
			static_assert(sizeof(TYPE) == sizeof(TYPE2), "Types must be the same size");\
			union {\
				Vector<TYPE, SIZE> vector;\
				INTRINSIC intrinsic;\
			};\
			intrinsic = FUNCTION(ANVIL_VALUE_CAST(TYPE2, x), ANVIL_VALUE_CAST(TYPE2, y), static_cast<TYPE2>(0), static_cast<TYPE2>(0),\
				static_cast<TYPE2>(0), static_cast<TYPE2>(0), static_cast<TYPE2>(0), static_cast<TYPE2>(0));\
			return vector;\
		}

#define ANVIL_SPECIALISE_VEC_FILL_XYZ8(TYPE,TYPE2,SIZE,INTRINSIC,FUNCTION) \
		template<>\
		static ANVIL_STRONG_INLINE Vector<TYPE, SIZE> ANVIL_CALL fill<TYPE, SIZE>(TYPE x, TYPE y, TYPE z) {\
			static_assert(sizeof(TYPE) == sizeof(TYPE2), "Types must be the same size");\
			union {\
				Vector<TYPE, SIZE> vector;\
				INTRINSIC intrinsic;\
			};\
			intrinsic = FUNCTION(ANVIL_VALUE_CAST(TYPE2, x), ANVIL_VALUE_CAST(TYPE2, y), ANVIL_VALUE_CAST(TYPE2, z), static_cast<TYPE2>(0),\
				static_cast<TYPE2>(0), static_cast<TYPE2>(0), static_cast<TYPE2>(0), static_cast<TYPE2>(0));\
			return vector;\
		}

#define ANVIL_SPECIALISE_VEC_FILL_XYZW8(TYPE,TYPE2,SIZE,INTRINSIC,FUNCTION) \
		template<>\
		static ANVIL_STRONG_INLINE Vector<TYPE, SIZE> ANVIL_CALL fill<TYPE, SIZE>(TYPE x, TYPE y, TYPE z, TYPE w) {\
			static_assert(sizeof(TYPE) == sizeof(TYPE2), "Types must be the same size");\
			union {\
				Vector<TYPE, SIZE> vector;\
				INTRINSIC intrinsic;\
			};\
			intrinsic = FUNCTION(ANVIL_VALUE_CAST(TYPE2, x), ANVIL_VALUE_CAST(TYPE2, y), ANVIL_VALUE_CAST(TYPE2, z), ANVIL_VALUE_CAST(TYPE2, w),\
				static_cast<TYPE2>(0), static_cast<TYPE2>(0), static_cast<TYPE2>(0), static_cast<TYPE2>(0));\
			return vector;\
		}

#define ANVIL_SPECIALISE_VEC_FILL_XY16(TYPE,TYPE2,SIZE,INTRINSIC,FUNCTION) \
		template<>\
		static ANVIL_STRONG_INLINE Vector<TYPE, SIZE> ANVIL_CALL fill<TYPE, SIZE>(TYPE x, TYPE y) {\
			static_assert(sizeof(TYPE) == sizeof(TYPE2), "Types must be the same size");\
			union {\
				Vector<TYPE, SIZE> vector;\
				INTRINSIC intrinsic;\
			};\
			intrinsic = FUNCTION(ANVIL_VALUE_CAST(TYPE2, x), ANVIL_VALUE_CAST(TYPE2, y), static_cast<TYPE2>(0), static_cast<TYPE2>(0),\
				static_cast<TYPE2>(0), static_cast<TYPE2>(0), static_cast<TYPE2>(0), static_cast<TYPE2>(0),\
				static_cast<TYPE2>(0), static_cast<TYPE2>(0), static_cast<TYPE2>(0), static_cast<TYPE2>(0),\
				static_cast<TYPE2>(0), static_cast<TYPE2>(0), static_cast<TYPE2>(0), static_cast<TYPE2>(0));\
			return vector;\
		}

#define ANVIL_SPECIALISE_VEC_FILL_XYZ16(TYPE,TYPE2,SIZE,INTRINSIC,FUNCTION) \
		template<>\
		static ANVIL_STRONG_INLINE Vector<TYPE, SIZE> ANVIL_CALL fill<TYPE, SIZE>(TYPE x, TYPE y, TYPE z) {\
			static_assert(sizeof(TYPE) == sizeof(TYPE2), "Types must be the same size");\
			union {\
				Vector<TYPE, SIZE> vector;\
				INTRINSIC intrinsic;\
			};\
			intrinsic = FUNCTION(ANVIL_VALUE_CAST(TYPE2, x), ANVIL_VALUE_CAST(TYPE2, y), ANVIL_VALUE_CAST(TYPE2, z), static_cast<TYPE2>(0),\
				static_cast<TYPE2>(0), static_cast<TYPE2>(0), static_cast<TYPE2>(0), static_cast<TYPE2>(0),\
				static_cast<TYPE2>(0), static_cast<TYPE2>(0), static_cast<TYPE2>(0), static_cast<TYPE2>(0),\
				static_cast<TYPE2>(0), static_cast<TYPE2>(0), static_cast<TYPE2>(0), static_cast<TYPE2>(0));\
			return vector;\
		}

#define ANVIL_SPECIALISE_VEC_FILL_XYZW16(TYPE,TYPE2,SIZE,INTRINSIC,FUNCTION) \
		template<>\
		static ANVIL_STRONG_INLINE Vector<TYPE, SIZE> ANVIL_CALL fill<TYPE, SIZE>(TYPE x, TYPE y, TYPE z, TYPE w) {\
			static_assert(sizeof(TYPE) == sizeof(TYPE2), "Types must be the same size");\
			union {\
				Vector<TYPE, SIZE> vector;\
				INTRINSIC intrinsic;\
			};\
			intrinsic = FUNCTION(ANVIL_VALUE_CAST(TYPE2, x), ANVIL_VALUE_CAST(TYPE2, y), ANVIL_VALUE_CAST(TYPE2, z), ANVIL_VALUE_CAST(TYPE2, w),\
				static_cast<TYPE2>(0), static_cast<TYPE2>(0), static_cast<TYPE2>(0), static_cast<TYPE2>(0),\
				static_cast<TYPE2>(0), static_cast<TYPE2>(0), static_cast<TYPE2>(0), static_cast<TYPE2>(0),\
				static_cast<TYPE2>(0), static_cast<TYPE2>(0), static_cast<TYPE2>(0), static_cast<TYPE2>(0));\
			return vector;\
		}

#define ANVIL_SPECIALISE_VEC_FILL_2(TYPE, TYPE2, INTRINSIC, FUNCTION1, FUNCTION2, FUNCTIONZ)\
		ANVIL_SPECIALISE_VEC_FILL_0(TYPE,2,INTRINSIC,FUNCTIONZ)\
		ANVIL_SPECIALISE_VEC_FILL_XN( TYPE, TYPE2, 2, INTRINSIC, FUNCTION1)\
		ANVIL_SPECIALISE_VEC_FILL_XY(TYPE, TYPE2, 2, INTRINSIC, FUNCTION2)

#define ANVIL_SPECIALISE_VEC_FILL_4(TYPE, TYPE2, INTRINSIC, FUNCTION1, FUNCTION2, FUNCTIONZ)\
		ANVIL_SPECIALISE_VEC_FILL_0(TYPE,4,INTRINSIC,FUNCTIONZ)\
		ANVIL_SPECIALISE_VEC_FILL_0(TYPE,3,INTRINSIC,FUNCTIONZ)\
		ANVIL_SPECIALISE_VEC_FILL_0(TYPE,2,INTRINSIC,FUNCTIONZ)\
		ANVIL_SPECIALISE_VEC_FILL_XN(   TYPE, TYPE2, 4, INTRINSIC, FUNCTION1)\
		ANVIL_SPECIALISE_VEC_FILL_XN(   TYPE, TYPE2, 3, INTRINSIC, FUNCTION1)\
		ANVIL_SPECIALISE_VEC_FILL_XN(   TYPE, TYPE2, 2, INTRINSIC, FUNCTION1)\
		ANVIL_SPECIALISE_VEC_FILL_XY4(  TYPE, TYPE2, 4, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XY4(  TYPE, TYPE2, 3, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XY4(  TYPE, TYPE2, 2, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZ4( TYPE, TYPE2, 4, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZ4( TYPE, TYPE2, 3, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZW4(TYPE, TYPE2, 4, INTRINSIC, FUNCTION2)

#define ANVIL_SPECIALISE_VEC_FILL_8(TYPE, TYPE2, INTRINSIC, FUNCTION1, FUNCTION2, FUNCTIONZ)\
		ANVIL_SPECIALISE_VEC_FILL_0(TYPE,8,INTRINSIC,FUNCTIONZ)\
		ANVIL_SPECIALISE_VEC_FILL_0(TYPE,7,INTRINSIC,FUNCTIONZ)\
		ANVIL_SPECIALISE_VEC_FILL_0(TYPE,6,INTRINSIC,FUNCTIONZ)\
		ANVIL_SPECIALISE_VEC_FILL_0(TYPE,5,INTRINSIC,FUNCTIONZ)\
		ANVIL_SPECIALISE_VEC_FILL_0(TYPE,4,INTRINSIC,FUNCTIONZ)\
		ANVIL_SPECIALISE_VEC_FILL_0(TYPE,3,INTRINSIC,FUNCTIONZ)\
		ANVIL_SPECIALISE_VEC_FILL_0(TYPE,2,INTRINSIC,FUNCTIONZ)\
		ANVIL_SPECIALISE_VEC_FILL_XN(   TYPE, TYPE2, 8, INTRINSIC, FUNCTION1)\
		ANVIL_SPECIALISE_VEC_FILL_XN(   TYPE, TYPE2, 7, INTRINSIC, FUNCTION1)\
		ANVIL_SPECIALISE_VEC_FILL_XN(   TYPE, TYPE2, 6, INTRINSIC, FUNCTION1)\
		ANVIL_SPECIALISE_VEC_FILL_XN(   TYPE, TYPE2, 5, INTRINSIC, FUNCTION1)\
		ANVIL_SPECIALISE_VEC_FILL_XN(   TYPE, TYPE2, 4, INTRINSIC, FUNCTION1)\
		ANVIL_SPECIALISE_VEC_FILL_XN(   TYPE, TYPE2, 3, INTRINSIC, FUNCTION1)\
		ANVIL_SPECIALISE_VEC_FILL_XN(   TYPE, TYPE2, 2, INTRINSIC, FUNCTION1)\
		ANVIL_SPECIALISE_VEC_FILL_XY8(  TYPE, TYPE2, 8, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XY8(  TYPE, TYPE2, 7, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XY8(  TYPE, TYPE2, 6, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XY8(  TYPE, TYPE2, 5, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XY8(  TYPE, TYPE2, 4, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XY8(  TYPE, TYPE2, 3, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZ8( TYPE, TYPE2, 2, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZ8( TYPE, TYPE2, 8, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZ8( TYPE, TYPE2, 7, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZ8( TYPE, TYPE2, 6, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZ8( TYPE, TYPE2, 5, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZ8( TYPE, TYPE2, 4, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZ8( TYPE, TYPE2, 3, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZW8(TYPE, TYPE2, 8, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZW8(TYPE, TYPE2, 7, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZW8(TYPE, TYPE2, 6, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZW8(TYPE, TYPE2, 5, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZW8(TYPE, TYPE2, 4, INTRINSIC, FUNCTION2)

#define ANVIL_SPECIALISE_VEC_FILL_16(TYPE, TYPE2, INTRINSIC, FUNCTION1, FUNCTION2, FUNCTIONZ)\
		ANVIL_SPECIALISE_VEC_FILL_0(TYPE,16,INTRINSIC,FUNCTIONZ)\
		ANVIL_SPECIALISE_VEC_FILL_0(TYPE,15,INTRINSIC,FUNCTIONZ)\
		ANVIL_SPECIALISE_VEC_FILL_0(TYPE,14,INTRINSIC,FUNCTIONZ)\
		ANVIL_SPECIALISE_VEC_FILL_0(TYPE,13,INTRINSIC,FUNCTIONZ)\
		ANVIL_SPECIALISE_VEC_FILL_0(TYPE,12,INTRINSIC,FUNCTIONZ)\
		ANVIL_SPECIALISE_VEC_FILL_0(TYPE,10,INTRINSIC,FUNCTIONZ)\
		ANVIL_SPECIALISE_VEC_FILL_0(TYPE,9 ,INTRINSIC,FUNCTIONZ)\
		ANVIL_SPECIALISE_VEC_FILL_0(TYPE,8 ,INTRINSIC,FUNCTIONZ)\
		ANVIL_SPECIALISE_VEC_FILL_0(TYPE,7 ,INTRINSIC,FUNCTIONZ)\
		ANVIL_SPECIALISE_VEC_FILL_0(TYPE,6 ,INTRINSIC,FUNCTIONZ)\
		ANVIL_SPECIALISE_VEC_FILL_0(TYPE,5 ,INTRINSIC,FUNCTIONZ)\
		ANVIL_SPECIALISE_VEC_FILL_0(TYPE,4 ,INTRINSIC,FUNCTIONZ)\
		ANVIL_SPECIALISE_VEC_FILL_0(TYPE,3 ,INTRINSIC,FUNCTIONZ)\
		ANVIL_SPECIALISE_VEC_FILL_0(TYPE,2 ,INTRINSIC,FUNCTIONZ)\
		ANVIL_SPECIALISE_VEC_FILL_XN(    TYPE, TYPE2, 16, INTRINSIC, FUNCTION1)\
		ANVIL_SPECIALISE_VEC_FILL_XN(    TYPE, TYPE2, 15, INTRINSIC, FUNCTION1)\
		ANVIL_SPECIALISE_VEC_FILL_XN(    TYPE, TYPE2, 14, INTRINSIC, FUNCTION1)\
		ANVIL_SPECIALISE_VEC_FILL_XN(    TYPE, TYPE2, 13, INTRINSIC, FUNCTION1)\
		ANVIL_SPECIALISE_VEC_FILL_XN(    TYPE, TYPE2, 12, INTRINSIC, FUNCTION1)\
		ANVIL_SPECIALISE_VEC_FILL_XN(    TYPE, TYPE2, 11, INTRINSIC, FUNCTION1)\
		ANVIL_SPECIALISE_VEC_FILL_XN(    TYPE, TYPE2, 10, INTRINSIC, FUNCTION1)\
		ANVIL_SPECIALISE_VEC_FILL_XN(    TYPE, TYPE2, 9,  INTRINSIC, FUNCTION1)\
		ANVIL_SPECIALISE_VEC_FILL_XN(    TYPE, TYPE2, 8,  INTRINSIC, FUNCTION1)\
		ANVIL_SPECIALISE_VEC_FILL_XN(    TYPE, TYPE2, 7,  INTRINSIC, FUNCTION1)\
		ANVIL_SPECIALISE_VEC_FILL_XN(    TYPE, TYPE2, 6,  INTRINSIC, FUNCTION1)\
		ANVIL_SPECIALISE_VEC_FILL_XN(    TYPE, TYPE2, 5,  INTRINSIC, FUNCTION1)\
		ANVIL_SPECIALISE_VEC_FILL_XN(    TYPE, TYPE2, 4,  INTRINSIC, FUNCTION1)\
		ANVIL_SPECIALISE_VEC_FILL_XN(    TYPE, TYPE2, 3,  INTRINSIC, FUNCTION1)\
		ANVIL_SPECIALISE_VEC_FILL_XN(    TYPE, TYPE2, 2,  INTRINSIC, FUNCTION1)\
		ANVIL_SPECIALISE_VEC_FILL_XY16(  TYPE, TYPE2, 16, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XY16(  TYPE, TYPE2, 15, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XY16(  TYPE, TYPE2, 14, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XY16(  TYPE, TYPE2, 13, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XY16(  TYPE, TYPE2, 12, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XY16(  TYPE, TYPE2, 11, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XY16(  TYPE, TYPE2, 10, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XY16(  TYPE, TYPE2, 9,  INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XY16(  TYPE, TYPE2, 8,  INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XY16(  TYPE, TYPE2, 7,  INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XY16(  TYPE, TYPE2, 6,  INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XY16(  TYPE, TYPE2, 5,  INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XY16(  TYPE, TYPE2, 4,  INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XY16(  TYPE, TYPE2, 3,  INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZ16( TYPE, TYPE2, 2,  INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZ16( TYPE, TYPE2, 16, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZ16( TYPE, TYPE2, 15, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZ16( TYPE, TYPE2, 14, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZ16( TYPE, TYPE2, 13, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZ16( TYPE, TYPE2, 12, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZ16( TYPE, TYPE2, 11, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZ16( TYPE, TYPE2, 10, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZ16( TYPE, TYPE2, 9,  INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZ16( TYPE, TYPE2, 8,  INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZ16( TYPE, TYPE2, 7,  INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZ16( TYPE, TYPE2, 6,  INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZ16( TYPE, TYPE2, 5,  INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZ16( TYPE, TYPE2, 4,  INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZ16( TYPE, TYPE2, 3,  INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZW16(TYPE, TYPE2, 16, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZW16(TYPE, TYPE2, 15, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZW16(TYPE, TYPE2, 14, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZW16(TYPE, TYPE2, 13, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZW16(TYPE, TYPE2, 12, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZW16(TYPE, TYPE2, 11, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZW16(TYPE, TYPE2, 10, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZW16(TYPE, TYPE2, 9,  INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZW16(TYPE, TYPE2, 8,  INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZW16(TYPE, TYPE2, 7,  INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZW16(TYPE, TYPE2, 6,  INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZW16(TYPE, TYPE2, 5,  INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZW16(TYPE, TYPE2, 4,  INTRINSIC, FUNCTION2)

#ifdef ANVIL_SSE
		ANVIL_SPECIALISE_VEC_FILL_4(float, float, __m128, _mm_set1_ps, _mm_set_ps, _mm_setzero_ps)
#endif

#ifdef ANVIL_SSE2
		ANVIL_SPECIALISE_VEC_FILL_2(double,   double,   __m128d, _mm_set1_pd,     _mm_set_pd,     _mm_setzero_pd)
		ANVIL_SPECIALISE_VEC_FILL_2(int64_t,  int64_t,  __m128i, _mm_set1_epi64x, _mm_set_epi64x, _mm_setzero_si128)
		ANVIL_SPECIALISE_VEC_FILL_2(uint64_t, uint64_t, __m128i, _mm_set1_epi64x, _mm_set_epi64x, _mm_setzero_si128)
		ANVIL_SPECIALISE_VEC_FILL_4(int32_t,  int32_t,  __m128i, _mm_set1_epi32,  _mm_set_epi32,  _mm_setzero_si128)
		ANVIL_SPECIALISE_VEC_FILL_4(uint32_t, int32_t,  __m128i, _mm_set1_epi32,  _mm_set_epi32,  _mm_setzero_si128)
		ANVIL_SPECIALISE_VEC_FILL_8(int16_t,  int16_t,  __m128i, _mm_set1_epi16,  _mm_set_epi16,  _mm_setzero_si128)
		ANVIL_SPECIALISE_VEC_FILL_8(uint16_t, int16_t,  __m128i, _mm_set1_epi16,  _mm_set_epi16,  _mm_setzero_si128)
		ANVIL_SPECIALISE_VEC_FILL_16(int8_t,  int8_t,   __m128i, _mm_set1_epi8,   _mm_set_epi8,   _mm_setzero_si128)
		ANVIL_SPECIALISE_VEC_FILL_16(uint8_t, int8_t,   __m128i, _mm_set1_epi8,   _mm_set_epi8,   _mm_setzero_si128)
#endif

		// ---- CAST ----

		template<class T, size_t S, class T2>
		static ANVIL_CALL Vector<T, S> cast(Vector<T2,S> x) {
			Vector<T, S> tmp;
			for (size_t i = 0; i < S; ++i) tmp.elements[i] = static_cast<T>(x.elements[i]);
			return tmp;
		}

#define ANVIL_SPECIALISE_VEC_CAST(TYPE,TYPE2,SIZE,INTRINSIC,INTRINSIC2,FUNCTION) \
		template<>\
		static ANVIL_CALL Vector<TYPE, SIZE> cast<TYPE,SIZE,TYPE2>(Vector<TYPE2, SIZE> x) {\
			union {\
				Vector<TYPE, SIZE> v1;\
				Vector<TYPE2, SIZE> v2;\
				INTRINSIC i1;\
				INTRINSIC2 i2;\
			};\
			v2 = x;\
			i1 = FUNCTION(i2);\
			return v1;\
		}

#define ANVIL_SPECIALISE_VEC_CAST2(TYPE,ITYPE,TYPE2,SIZE) \
		template<>\
		static ANVIL_CALL ANVIL_STRONG_INLINE Vector<TYPE, SIZE> cast<TYPE,SIZE,TYPE2>(Vector<TYPE2, SIZE> x) {\
			return cast<TYPE,SIZE,ITYPE>(cast<ITYPE,SIZE,TYPE2>(x));\
		}

#ifdef ANVIL_SSE2
		ANVIL_SPECIALISE_VEC_CAST(double, int32_t, 2, __m128d, __m128i, _mm_cvtepi32_pd)
		ANVIL_SPECIALISE_VEC_CAST(float,  int32_t, 4, __m128, __m128i,  _mm_cvtepi32_ps)
		ANVIL_SPECIALISE_VEC_CAST(int32_t, double, 2, __m128i, __m128d, _mm_cvtpd_epi32)
		ANVIL_SPECIALISE_VEC_CAST(int32_t, float,  4, __m128i, __m128,  _mm_cvtps_epi32)
		ANVIL_SPECIALISE_VEC_CAST(double,  float,  2, __m128d, __m128,  _mm_cvtps_pd)
		ANVIL_SPECIALISE_VEC_CAST(float,   double, 2, __m128, __m128d,  _mm_cvtpd_ps)
#endif

#ifdef ANVIL_SSE4_1
		ANVIL_SPECIALISE_VEC_CAST(int64_t, int32_t,  2, __m128i, __m128i, _mm_cvtepi32_epi64)
		ANVIL_SPECIALISE_VEC_CAST(int32_t, int16_t,  4, __m128i, __m128i, _mm_cvtepi16_epi32)
		ANVIL_SPECIALISE_VEC_CAST(int64_t, int16_t,  2, __m128i, __m128i, _mm_cvtepi16_epi64)
		ANVIL_SPECIALISE_VEC_CAST(int32_t, int16_t,  8, __m128i, __m128i, _mm_cvtepi8_epi16)
		ANVIL_SPECIALISE_VEC_CAST(int32_t, int8_t,   4, __m128i, __m128i, _mm_cvtepi8_epi32)
		ANVIL_SPECIALISE_VEC_CAST(int64_t, int8_t,   2, __m128i, __m128i, _mm_cvtepi8_epi64)
		ANVIL_SPECIALISE_VEC_CAST(int64_t, uint32_t, 2, __m128i, __m128i, _mm_cvtepu32_epi64)
		ANVIL_SPECIALISE_VEC_CAST(int64_t, uint16_t, 2, __m128i, __m128i, _mm_cvtepu16_epi64)
		ANVIL_SPECIALISE_VEC_CAST(int32_t, uint16_t, 4, __m128i, __m128i, _mm_cvtepu16_epi32)
		ANVIL_SPECIALISE_VEC_CAST(int64_t, uint8_t,  2, __m128i, __m128i, _mm_cvtepu8_epi64)
		ANVIL_SPECIALISE_VEC_CAST(int32_t, uint8_t,  4, __m128i, __m128i, _mm_cvtepu8_epi32)
		ANVIL_SPECIALISE_VEC_CAST(int32_t, uint8_t,  8, __m128i, __m128i, _mm_cvtepu8_epi16)

		ANVIL_SPECIALISE_VEC_CAST2(float,    int32_t, int64_t,  2)
		ANVIL_SPECIALISE_VEC_CAST2(double,   int32_t, int64_t,  2)
		ANVIL_SPECIALISE_VEC_CAST2(float,    int32_t, uint32_t, 2)
		ANVIL_SPECIALISE_VEC_CAST2(double,   int32_t, uint32_t, 4)
		ANVIL_SPECIALISE_VEC_CAST2(float,    int32_t, uint16_t, 2)
		ANVIL_SPECIALISE_VEC_CAST2(double,   int32_t, uint16_t, 4)
		ANVIL_SPECIALISE_VEC_CAST2(float,    int32_t, uint8_t,  2)
		ANVIL_SPECIALISE_VEC_CAST2(double,   int32_t, uint8_t,  4)
		ANVIL_SPECIALISE_VEC_CAST2(int64_t,  int32_t, float,    2)
		ANVIL_SPECIALISE_VEC_CAST2(int64_t,  int32_t, double,   2)
		ANVIL_SPECIALISE_VEC_CAST2(uint32_t, int32_t, float,    2)
		ANVIL_SPECIALISE_VEC_CAST2(uint32_t, int32_t, double,   4)
		ANVIL_SPECIALISE_VEC_CAST2(uint16_t, int32_t, float,    2)
		ANVIL_SPECIALISE_VEC_CAST2(uint16_t, int32_t, double,   4)
		ANVIL_SPECIALISE_VEC_CAST2(uint8_t,  int32_t, float,    2)
		ANVIL_SPECIALISE_VEC_CAST2(uint8_t,  int32_t, double,   4)
#endif

		// ---- RESIZE ----

		template<class T, size_t S, size_t S2>
		static ANVIL_CALL Vector<T, S> resize(Vector<T,S2> x) {
			union {
				Vector<T,S> v1;
				Vector<T, S2> v2;
			};
			if (S > S2) v1 = fill<T, S>(0);
			v2 = x;
			return v2;
		}

		// ---- ADD, SUB, MUL, DIV, MIN, MAX, CMPEQ, CMPNE, CMPLT, CMPGT, CMPLE, CMPGE, AND, OR, XOR ----

		enum VectorOperationID {
			VOP_add,
			VOP_sub,
			VOP_mul,
			VOP_div,
			VOP_min,
			VOP_max,
			VOP_cmpeq,
			VOP_cmpne,
			VOP_cmplt,
			VOP_cmpgt,
			VOP_cmple,
			VOP_cmpge,
			VOP_and,
			VOP_or,
			VOP_xor,

			VOP_abs,
			VOP_sqrt,
			VOP_cbrt,
			VOP_not,
			VOP_ceil,
			VOP_floor
		};

		template<VectorOperationID>
		struct VectorOperationArgs {
			enum { value = 2 };
		};

		template<class T, VectorOperationID>
		struct VectorOperationWidth {
			enum { value = 4 };
		};

		template<class T, size_t S, VectorOperationID VOP, size_t ARGS = VectorOperationArgs<VOP>::value>
		struct VectorOperation;

		template<class T, size_t S, VectorOperationID VOP>
		struct VectorOperation<T,S,VOP,2> {
			static Vector<T, S> ANVIL_CALL execute(Vector<T, S> x, Vector<T, S> y) {
				enum {
					W = VectorOperationWidth<T,VOP>::value,
					LOOPS = S / W,
					REMAINDER = S % W
				};

				Vector<T, S> tmp;
				const Vector<T, W>* a = reinterpret_cast<const Vector<T, W>*>(&x);
				const Vector<T, W>* b = reinterpret_cast<const Vector<T, W>*>(&y);
				Vector<T, W>* t = reinterpret_cast<Vector<T, W>*>(&tmp);

				for (size_t i = 0; i < LOOPS; ++i) t[i] = VectorOperation<T, W, VOP>::execute(a[i], b[i]);
				for (size_t i = 0; i < REMAINDER; ++i) t[LOOPS].elements[i] = VectorOperation<T, 1, VOP>::execute(a[LOOPS].elements[i], b[LOOPS].elements[i]);

				return tmp;
			}
		};

		template<class T, VectorOperationID VOP>
		struct VectorOperation<T, 2, VOP,2> {
			static inline Vector<T, 2> ANVIL_CALL execute(Vector<T,2> x, Vector<T, 2> y) {
				Vector<T, 2> tmp;
				tmp.elements[0] = VectorOperation<T, 1, VOP>::execute(x.elements[0], y.elements[0]);
				tmp.elements[1] = VectorOperation<T, 1, VOP>::execute(x.elements[1], y.elements[1]);
				return tmp;
			}
		};

		template<class T, VectorOperationID VOP>
		struct VectorOperation<T, 3, VOP, 2> {
			static inline Vector<T, 3> ANVIL_CALL execute(Vector<T, 3> x, Vector<T, 3> y) {
				Vector<T, 3> tmp;
				tmp.elements[0] = VectorOperation<T, 1, VOP>::execute(x.elements[0], y.elements[0]);
				tmp.elements[1] = VectorOperation<T, 1, VOP>::execute(x.elements[1], y.elements[1]);
				tmp.elements[2] = VectorOperation<T, 1, VOP>::execute(x.elements[2], y.elements[2]);
				return tmp;
			}
		};

		template<class T, VectorOperationID VOP>
		struct VectorOperation<T, 4, VOP, 2> {
			static inline Vector<T, 4> ANVIL_CALL execute(Vector<T, 4> x, Vector<T, 4> y) {
				Vector<T, 4> tmp;
				tmp.elements[0] = VectorOperation<T, 1, VOP>::execute(x.elements[0], y.elements[0]);
				tmp.elements[1] = VectorOperation<T, 1, VOP>::execute(x.elements[1], y.elements[1]);
				tmp.elements[2] = VectorOperation<T, 1, VOP>::execute(x.elements[2], y.elements[2]);
				tmp.elements[3] = VectorOperation<T, 1, VOP>::execute(x.elements[3], y.elements[3]);
				return tmp;
			}
		};

		template<class T>
		struct VectorOperation<T,1,VOP_add, 2> {
			static ANVIL_STRONG_INLINE T ANVIL_CALL execute(T x, T y) {
				return x + y;
			}
		}; 

		template<class T>
		struct VectorOperation<T, 1, VOP_sub, 2> {
			static ANVIL_STRONG_INLINE T ANVIL_CALL execute(T x, T y) {
				return x - y;
			}
		};

		template<class T>
		struct VectorOperation<T, 1, VOP_mul, 2> {
			static ANVIL_STRONG_INLINE T ANVIL_CALL execute(T x, T y) {
				return x * y;
			}
		};

		template<class T>
		struct div {
			static ANVIL_STRONG_INLINE T ANVIL_CALL execute(T x, T y) {
				return x / y;
			}
		};

		template<class T>
		struct VectorOperation<T, 1, VOP_min, 2> {
			static ANVIL_STRONG_INLINE T ANVIL_CALL execute(T x, T y) {
				return std::min<T>(x, y);
			}
		};

		template<class T>
		struct VectorOperation<T, 1, VOP_max, 2> {
			static ANVIL_STRONG_INLINE Vector<T, 1> ANVIL_CALL execute(Vector<T, 1> x, Vector<T, 1> y) {
				return std::max<T>(x, y);
			}
		};

		template<class T>
		struct VectorOperation<T, 1, VOP_cmpeq, 2> {
			static ANVIL_STRONG_INLINE Vector<T, 1> ANVIL_CALL execute(Vector<T, 1> x, Vector<T, 1> y) {
				return static_cast<T>(x == y);
			}
		};

		template<class T>
		struct VectorOperation<T, 1, VOP_cmpne, 2> {
			static ANVIL_STRONG_INLINE Vector<T, 1> ANVIL_CALL execute(Vector<T, 1> x, Vector<T, 1> y) {
				return static_cast<T>(x != y);
			}
		};

		template<class T>
		struct VectorOperation<T, 1, VOP_cmplt, 2> {
			static ANVIL_STRONG_INLINE Vector<T, 1> ANVIL_CALL execute(Vector<T, 1> x, Vector<T, 1> y) {
				return static_cast<T>(x < y);
			}
		};

		template<class T>
		struct VectorOperation<T, 1, VOP_cmpgt, 2> {
			static ANVIL_STRONG_INLINE Vector<T, 1> ANVIL_CALL execute(Vector<T, 1> x, Vector<T, 1> y) {
				return static_cast<T>(x > y);
			}
		};

		template<class T>
		struct VectorOperation<T, 1, VOP_cmple, 2> {
			static ANVIL_STRONG_INLINE Vector<T, 1> ANVIL_CALL execute(Vector<T, 1> x, Vector<T, 1> y) {
				return static_cast<T>(x <= y);
			}
		};

		template<class T>
		struct VectorOperation<T, 1, VOP_cmpge, 2> {
			static ANVIL_STRONG_INLINE Vector<T, 1> ANVIL_CALL execute(Vector<T, 1> x, Vector<T, 1> y) {
				return static_cast<T>(x >= y);
			}
		};

		template<class T>
		struct VectorOperation<T, 1, VOP_and, 2> {
			static ANVIL_STRONG_INLINE Vector<T, 1> ANVIL_CALL execute(Vector<T, 1> x, Vector<T, 1> y) {
				return x & y;
			}
		};

		template<>
		struct VectorOperation<double, 1, VOP_and, 2> {
			static ANVIL_STRONG_INLINE double ANVIL_CALL execute(double x, double y) {
				union Union{
					double f;
					uint64_t i;
				};
				Union a, b;
				a.f = x;
				b.f = y;
				a.i = a.i & b.i;
				return a.f;
			}
		};

		template<>
		struct VectorOperation<float, 1, VOP_and, 2> {
			static ANVIL_STRONG_INLINE float ANVIL_CALL execute(float x, float y) {
				union Union {
					float f;
					uint32_t i;
				};
				Union a, b;
				a.f = x;
				b.f = y;
				a.i = a.i & b.i;
				return a.f;
			}
		};

		template<class T>
		struct VectorOperation<T, 1, VOP_or, 2> {
			static ANVIL_STRONG_INLINE Vector<T, 1> ANVIL_CALL execute(Vector<T, 1> x, Vector<T, 1> y) {
				return x | y;
			}
		};

		template<>
		struct VectorOperation<double, 1, VOP_or, 2> {
			static ANVIL_STRONG_INLINE double ANVIL_CALL execute(double x, double y) {
				union Union {
					double f;
					uint64_t i;
				};
				Union a, b;
				a.f = x;
				b.f = y;
				a.i = a.i | b.i;
				return a.f;
			}
		};

		template<>
		struct VectorOperation<float, 1, VOP_or, 2> {
			static ANVIL_STRONG_INLINE float ANVIL_CALL execute(float x, float y) {
				union Union {
					float f;
					uint32_t i;
				};
				Union a, b;
				a.f = x;
				b.f = y;
				a.i = a.i | b.i;
				return a.f;
			}
		};

		template<class T>
		struct VectorOperation<T, 1, VOP_xor, 2> {
			static ANVIL_STRONG_INLINE Vector<T, 1> ANVIL_CALL execute(Vector<T, 1> x, Vector<T, 1> y) {
				return x ^ y;
			}
		};

		template<>
		struct VectorOperation<double, 1, VOP_xor, 2> {
			static ANVIL_STRONG_INLINE double ANVIL_CALL execute(double x, double y) {
				union Union {
					double f;
					uint64_t i;
				};
				Union a, b;
				a.f = x;
				b.f = y;
				a.i = a.i ^ b.i;
				return a.f;
			}
		};

		template<>
		struct VectorOperation<float, 1, VOP_xor, 2> {
			static ANVIL_STRONG_INLINE float ANVIL_CALL execute(float x, float y) {
				union Union {
					float f;
					uint32_t i;
				};
				Union a, b;
				a.f = x;
				b.f = y;
				a.i = a.i ^ b.i;
				return a.f;
			}
		};

#define ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,SIZE,SIZE2,INTRINSIC,FUNCTION,ZERO_FLAG) \
		template<>\
		struct VectorOperation<TYPE,SIZE,VOP_ ## NAME ,2> {\
			static ANVIL_STRONG_INLINE Vector<TYPE, SIZE> ANVIL_CALL execute(Vector<TYPE, SIZE> x, Vector<TYPE, SIZE> y) {\
				union IntrinsicUnion {\
					Vector<TYPE,SIZE> v;\
					Vector<TYPE,SIZE2> v2;\
					INTRINSIC i;\
				};\
				IntrinsicUnion x_, y_;\
				if (ZERO_FLAG) {\
					x_.v2 = fill_0<TYPE,SIZE2>();\
					y_.v2 = fill_0<TYPE,SIZE2>();\
				}\
				x_.v = x;\
				y_.v = y;\
				x_.i = FUNCTION(x_.i, y_.i);\
				return x_.v;\
			}\
		};

#define ANVIL_SPECIALISE_VEC_VVV2(NAME,TYPE,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,2,2,INTRINSIC,FUNCTION,false)

#define ANVIL_SPECIALISE_VEC_VVV4(NAME,TYPE,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,4,4,INTRINSIC,FUNCTION,false)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,3,4,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,2,4,INTRINSIC,FUNCTION,ZERO_FLAG)

#define ANVIL_SPECIALISE_VEC_VVV8(NAME,TYPE,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,8,8,INTRINSIC,FUNCTION,false)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,7,8,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,6,8,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,5,8,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,4,8,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,3,8,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,2,8,INTRINSIC,FUNCTION,ZERO_FLAG)

#define ANVIL_SPECIALISE_VEC_VVV16(NAME,TYPE,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,16,16,INTRINSIC,FUNCTION,false)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,15,16,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,14,16,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,13,16,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,12,16,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,11,16,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,10,16,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,9,16,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,8,16,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,7,16,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,6,16,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,5,16,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,4,16,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,3,16,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,2,16,INTRINSIC,FUNCTION,ZERO_FLAG)

#ifdef ANVIL_SSE
	ANVIL_SPECIALISE_VEC_VVV4(add,   float, __m128, _mm_add_ps,    false)
	ANVIL_SPECIALISE_VEC_VVV4(sub,   float, __m128, _mm_sub_ps,    false)
	ANVIL_SPECIALISE_VEC_VVV4(mul,   float, __m128, _mm_mul_ps,    false)
	ANVIL_SPECIALISE_VEC_VVV4(div,   float, __m128, _mm_div_ps,    false)
	ANVIL_SPECIALISE_VEC_VVV4(min,   float, __m128, _mm_min_ps,    false)
	ANVIL_SPECIALISE_VEC_VVV4(max,   float, __m128, _mm_max_ps,    false)
	ANVIL_SPECIALISE_VEC_VVV4(cmpeq, float, __m128, _mm_cmpeq_ps,  false)
	ANVIL_SPECIALISE_VEC_VVV4(cmpne, float, __m128, _mm_cmpneq_ps, false)
	ANVIL_SPECIALISE_VEC_VVV4(cmplt, float, __m128, _mm_cmplt_ps,  false)
	ANVIL_SPECIALISE_VEC_VVV4(cmpgt, float, __m128, _mm_cmpgt_ps,  false)
	ANVIL_SPECIALISE_VEC_VVV4(cmple, float, __m128, _mm_cmple_ps,  false)
	ANVIL_SPECIALISE_VEC_VVV4(cmpge, float, __m128, _mm_cmpge_ps,  false)
	ANVIL_SPECIALISE_VEC_VVV4(and,   float, __m128, _mm_and_ps,    false)
	ANVIL_SPECIALISE_VEC_VVV4(or,    float, __m128, _mm_or_ps,     false)
	ANVIL_SPECIALISE_VEC_VVV4(xor,   float, __m128, _mm_xor_ps,    false)
#endif
		
#ifdef ANVIL_SSE2
	ANVIL_SPECIALISE_VEC_VVV2(add,   double, __m128d, _mm_add_pd,    false)
	ANVIL_SPECIALISE_VEC_VVV2(sub,   double, __m128d, _mm_sub_pd,    false)
	ANVIL_SPECIALISE_VEC_VVV2(mul,   double, __m128d, _mm_mul_pd,    false)
	ANVIL_SPECIALISE_VEC_VVV2(div,   double, __m128d, _mm_div_pd,    false)
	ANVIL_SPECIALISE_VEC_VVV2(min,   double, __m128d, _mm_min_pd,    false)
	ANVIL_SPECIALISE_VEC_VVV2(max,   double, __m128d, _mm_max_pd,    false)
	ANVIL_SPECIALISE_VEC_VVV2(cmpeq, double, __m128d, _mm_cmpeq_pd,  false)
	ANVIL_SPECIALISE_VEC_VVV2(cmpne, double, __m128d, _mm_cmpneq_pd, false)
	ANVIL_SPECIALISE_VEC_VVV2(cmplt, double, __m128d, _mm_cmplt_pd,  false)
	ANVIL_SPECIALISE_VEC_VVV2(cmpgt, double, __m128d, _mm_cmpgt_pd,  false)
	ANVIL_SPECIALISE_VEC_VVV2(cmple, double, __m128d, _mm_cmple_pd,  false)
	ANVIL_SPECIALISE_VEC_VVV2(cmpge, double, __m128d, _mm_cmpge_pd,  false)
	ANVIL_SPECIALISE_VEC_VVV2(and,   double, __m128d, _mm_and_pd,    false)
	ANVIL_SPECIALISE_VEC_VVV2(or,    double, __m128d, _mm_or_pd,     false)
	ANVIL_SPECIALISE_VEC_VVV2(xor,   double, __m128d, _mm_xor_pd,    false)

	ANVIL_SPECIALISE_VEC_VVV2(add, int64_t, __m128i, _mm_add_epi64, false)
	ANVIL_SPECIALISE_VEC_VVV2(sub, int64_t, __m128i, _mm_sub_epi64, false)
	ANVIL_SPECIALISE_VEC_VVV2(and, int64_t, __m128i, _mm_and_si128, false)
	ANVIL_SPECIALISE_VEC_VVV2(or,  int64_t, __m128i, _mm_or_si128,  false)
	ANVIL_SPECIALISE_VEC_VVV2(xor, int64_t, __m128i, _mm_xor_si128, false)

	ANVIL_SPECIALISE_VEC_VVV2(add, uint64_t, __m128i, _mm_add_epi64, false)
	ANVIL_SPECIALISE_VEC_VVV2(sub, uint64_t, __m128i, _mm_sub_epi64, false)
	ANVIL_SPECIALISE_VEC_VVV2(and, uint64_t, __m128i, _mm_and_si128, false)
	ANVIL_SPECIALISE_VEC_VVV2(or,  uint64_t, __m128i, _mm_or_si128,  false)
	ANVIL_SPECIALISE_VEC_VVV2(xor, uint64_t, __m128i, _mm_xor_si128, false)

	ANVIL_SPECIALISE_VEC_VVV4(add,   int32_t, __m128i, _mm_add_epi32,   false)
	ANVIL_SPECIALISE_VEC_VVV4(sub,   int32_t, __m128i, _mm_sub_epi32,   false)
	ANVIL_SPECIALISE_VEC_VVV4(cmpeq, int32_t, __m128i, _mm_cmpeq_epi32, false)
	ANVIL_SPECIALISE_VEC_VVV4(cmplt, int32_t, __m128i, _mm_cmplt_epi32, false)
	ANVIL_SPECIALISE_VEC_VVV4(cmpgt, int32_t, __m128i, _mm_cmpgt_epi32, false)
	ANVIL_SPECIALISE_VEC_VVV4(and,   int32_t, __m128i, _mm_and_si128,   false)
	ANVIL_SPECIALISE_VEC_VVV4(or,    int32_t, __m128i, _mm_or_si128,    false)
	ANVIL_SPECIALISE_VEC_VVV4(xor,   int32_t, __m128i, _mm_xor_si128,   false)
		
	ANVIL_SPECIALISE_VEC_VVV4(add,   uint32_t, __m128i, _mm_add_epi32,   false)
	ANVIL_SPECIALISE_VEC_VVV4(sub,   uint32_t, __m128i, _mm_sub_epi32,   false)
	ANVIL_SPECIALISE_VEC_VVV4(mul,   uint32_t, __m128i, _mm_mul_epu32,   false)
	ANVIL_SPECIALISE_VEC_VVV4(cmpeq, uint32_t, __m128i, _mm_cmpeq_epi32, false)
	ANVIL_SPECIALISE_VEC_VVV4(and,   uint32_t, __m128i, _mm_and_si128,   false)
	ANVIL_SPECIALISE_VEC_VVV4(or,    uint32_t, __m128i, _mm_or_si128,    false)
	ANVIL_SPECIALISE_VEC_VVV4(xor,   uint32_t, __m128i, _mm_xor_si128,   false)

	ANVIL_SPECIALISE_VEC_VVV8(add,   int16_t, __m128i, _mm_add_epi16,   false)
	ANVIL_SPECIALISE_VEC_VVV8(sub,   int16_t, __m128i, _mm_sub_epi16,   false)
	ANVIL_SPECIALISE_VEC_VVV8(mul,   int16_t, __m128i, _mm_mullo_epi16, false)
	ANVIL_SPECIALISE_VEC_VVV8(min,   int16_t, __m128i, _mm_min_epi16,   false)
	ANVIL_SPECIALISE_VEC_VVV8(max,   int16_t, __m128i, _mm_max_epi16,   false)
	ANVIL_SPECIALISE_VEC_VVV8(cmpeq, int16_t, __m128i, _mm_cmpeq_epi16, false)
	ANVIL_SPECIALISE_VEC_VVV8(cmplt, int16_t, __m128i, _mm_cmplt_epi16, false)
	ANVIL_SPECIALISE_VEC_VVV8(cmpgt, int16_t, __m128i, _mm_cmpgt_epi16, false)
	ANVIL_SPECIALISE_VEC_VVV8(and,   int16_t, __m128i, _mm_and_si128,   false)
	ANVIL_SPECIALISE_VEC_VVV8(or,    int16_t, __m128i, _mm_or_si128,    false)
	ANVIL_SPECIALISE_VEC_VVV8(xor,   int16_t, __m128i, _mm_xor_si128,   false)

	ANVIL_SPECIALISE_VEC_VVV8(add,   uint16_t, __m128i, _mm_adds_epu16,  false)
	ANVIL_SPECIALISE_VEC_VVV8(sub,   uint16_t, __m128i, _mm_subs_epu16,  false)
	ANVIL_SPECIALISE_VEC_VVV8(cmpeq, uint16_t, __m128i, _mm_cmpeq_epi16, false)
	ANVIL_SPECIALISE_VEC_VVV8(and,   uint16_t, __m128i, _mm_and_si128,   false)
	ANVIL_SPECIALISE_VEC_VVV8(or,    uint16_t, __m128i, _mm_or_si128,    false)
	ANVIL_SPECIALISE_VEC_VVV8(xor,   uint16_t, __m128i, _mm_xor_si128,   false)


	static inline __m128i _mm_mul_epi8(__m128i a, __m128i b) {
		const __m128i x = _mm_mullo_epi16(a, b);
		const __m128i y = _mm_mullo_epi16(_mm_srli_epi16(a, 8), _mm_srli_epi16(b, 8));
		return _mm_or_si128(_mm_slli_epi16(y, 8), _mm_srli_epi16(_mm_slli_epi16(x, 8), 8));
	}

	ANVIL_SPECIALISE_VEC_VVV16(add,   int8_t, __m128i, _mm_add_epi8,    false)
	ANVIL_SPECIALISE_VEC_VVV16(sub,   int8_t, __m128i, _mm_sub_epi8,    false)
	ANVIL_SPECIALISE_VEC_VVV16(mul,   int8_t, __m128i, _mm_mul_epi8,    false)
	ANVIL_SPECIALISE_VEC_VVV16(cmpeq, int8_t, __m128i, _mm_cmpeq_epi16, false)
	ANVIL_SPECIALISE_VEC_VVV16(cmplt, int8_t, __m128i, _mm_cmplt_epi16, false)
	ANVIL_SPECIALISE_VEC_VVV16(cmpgt, int8_t, __m128i, _mm_cmpgt_epi16, false)
	ANVIL_SPECIALISE_VEC_VVV16(and,   int8_t, __m128i, _mm_and_si128,   false)
	ANVIL_SPECIALISE_VEC_VVV16(or,    int8_t, __m128i, _mm_or_si128,    false)
	ANVIL_SPECIALISE_VEC_VVV16(xor,   int8_t, __m128i, _mm_xor_si128,   false)

	ANVIL_SPECIALISE_VEC_VVV16(add,   uint8_t, __m128i, _mm_adds_epi8,   false)
	ANVIL_SPECIALISE_VEC_VVV16(sub,   uint8_t, __m128i, _mm_subs_epi8,   false)
	ANVIL_SPECIALISE_VEC_VVV16(min,   uint8_t, __m128i, _mm_min_epu8,    false)
	ANVIL_SPECIALISE_VEC_VVV16(max,   uint8_t, __m128i, _mm_max_epu8,    false)
	ANVIL_SPECIALISE_VEC_VVV16(cmpeq, uint8_t, __m128i, _mm_cmpeq_epi16, false)
	ANVIL_SPECIALISE_VEC_VVV16(cmplt, uint8_t, __m128i, _mm_cmplt_epi16, false)
	ANVIL_SPECIALISE_VEC_VVV16(cmpgt, uint8_t, __m128i, _mm_cmpgt_epi16, false)
	ANVIL_SPECIALISE_VEC_VVV16(and,   uint8_t, __m128i, _mm_and_si128,   false)
	ANVIL_SPECIALISE_VEC_VVV16(or,    uint8_t, __m128i, _mm_or_si128,    false)
	ANVIL_SPECIALISE_VEC_VVV16(xor,   uint8_t, __m128i, _mm_xor_si128,   false)
#endif

#ifdef ANVIL_SSE4_1
	ANVIL_SPECIALISE_VEC_VVV4(min, int32_t, __m128i, _mm_min_epi32, false)
	ANVIL_SPECIALISE_VEC_VVV4(max, int32_t, __m128i, _mm_max_epi32, false)

	ANVIL_SPECIALISE_VEC_VVV4(min, uint32_t, __m128i, _mm_min_epu32, false)
	ANVIL_SPECIALISE_VEC_VVV4(max, uint32_t, __m128i, _mm_max_epu32, false)

	ANVIL_SPECIALISE_VEC_VVV8(min, uint16_t, __m128i, _mm_min_epu16, false)
	ANVIL_SPECIALISE_VEC_VVV8(max, uint16_t, __m128i, _mm_max_epu16, false)

	ANVIL_SPECIALISE_VEC_VVV16(min, int8_t, __m128i, _mm_min_epi8, false)
	ANVIL_SPECIALISE_VEC_VVV16(max, int8_t, __m128i, _mm_max_epi8, false)
#endif

	// ---- ABS, SQRT, CBRT, NOT, CEIL, FLOOR ----

	template<> struct VectorOperationArgs<VOP_abs> { enum { value = 1 }; };
	template<> struct VectorOperationArgs<VOP_sqrt> { enum { value = 1 }; };
	template<> struct VectorOperationArgs<VOP_cbrt> { enum { value = 1 }; };
	template<> struct VectorOperationArgs<VOP_not> { enum { value = 1 }; };
	template<> struct VectorOperationArgs<VOP_ceil> { enum { value = 1 }; };
	template<> struct VectorOperationArgs<VOP_floor> { enum { value = 1 }; };

	template<class T, size_t S, VectorOperationID VOP>
	struct VectorOperation<T, S, VOP, 1> {
		static Vector<T, S> ANVIL_CALL execute(Vector<T, S> x) {
			enum {
				W = VectorOperationWidth<T, VOP>::value,
				LOOPS = S / W,
				REMAINDER = S % W
			};

			Vector<T, S> tmp;
			const Vector<T, W>* a = reinterpret_cast<const Vector<T, W>*>(&x);
			Vector<T, W>* t = reinterpret_cast<Vector<T, W>*>(&tmp);

			for (size_t i = 0; i < LOOPS; ++i) t[i] = VectorOperation<T, W, VOP>::execute(a[i]);
			for (size_t i = 0; i < REMAINDER; ++i) t[LOOPS].elements[i] = VectorOperation<T, 1, VOP>::execute(a[LOOPS].elements[i]);

			return tmp;
		}
	};

	template<class T, VectorOperationID VOP>
	struct VectorOperation<T, 2, VOP, 1> {
		static inline Vector<T, 2> ANVIL_CALL execute(Vector<T, 2> x) {
			Vector<T, 2> tmp;
			tmp.elements[0] = VectorOperation<T, 1, VOP>::execute(x.elements[0]);
			tmp.elements[1] = VectorOperation<T, 1, VOP>::execute(x.elements[1]);
			return tmp;
		}
	};

	template<class T, VectorOperationID VOP>
	struct VectorOperation<T, 3, VOP, 1> {
		static inline Vector<T, 3> ANVIL_CALL execute(Vector<T, 3> x) {
			Vector<T, 3> tmp;
			tmp.elements[0] = VectorOperation<T, 1, VOP>::execute(x.elements[0]);
			tmp.elements[1] = VectorOperation<T, 1, VOP>::execute(x.elements[1]);
			tmp.elements[2] = VectorOperation<T, 1, VOP>::execute(x.elements[2]);
			return tmp;
		}
	};

	template<class T, VectorOperationID VOP>
	struct VectorOperation<T, 4, VOP, 1> {
		static inline Vector<T, 4> ANVIL_CALL execute(Vector<T, 4> x) {
			Vector<T, 4> tmp;
			tmp.elements[0] = VectorOperation<T, 1, VOP>::execute(x.elements[0]);
			tmp.elements[1] = VectorOperation<T, 1, VOP>::execute(x.elements[1]);
			tmp.elements[2] = VectorOperation<T, 1, VOP>::execute(x.elements[2]);
			tmp.elements[3] = VectorOperation<T, 1, VOP>::execute(x.elements[3]);
			return tmp;
		}
	};

	template<class T>
	struct VectorOperation<T, 1, VOP_abs, 1> {
		static ANVIL_STRONG_INLINE T ANVIL_CALL execute(T x) { return std::abs(x); }
	};

	template<>
	struct VectorOperation<int64_t, 1, VOP_abs, 1> {
		static ANVIL_STRONG_INLINE int64_t ANVIL_CALL execute(int64_t x) { return x * x < 0 ? -1 : 1; }
	};

	template<>
	struct VectorOperation<int32_t, 1, VOP_abs, 1> {
		static ANVIL_STRONG_INLINE int32_t ANVIL_CALL execute(int32_t x) { return x * x < 0 ? -1 : 1; }
	};

	template<>
	struct VectorOperation<int16_t, 1, VOP_abs, 1> {
		static ANVIL_STRONG_INLINE int16_t ANVIL_CALL execute(int16_t x) { return x * x < 0 ? -1 : 1; }
	};

	template<>
	struct VectorOperation<int8_t, 1, VOP_abs, 1> {
		static ANVIL_STRONG_INLINE int8_t ANVIL_CALL execute(int8_t x) { return x * x < 0 ? -1 : 1; }
	};

	template<>
	struct VectorOperation<uint64_t, 1, VOP_abs, 1> {
		static ANVIL_STRONG_INLINE uint64_t ANVIL_CALL execute(uint64_t x) { return x; }
	};

	template<>
	struct VectorOperation<uint32_t, 1, VOP_abs, 1> {
		static ANVIL_STRONG_INLINE uint32_t ANVIL_CALL execute(uint32_t x) { return x; }
	};

	template<>
	struct VectorOperation<uint16_t, 1, VOP_abs, 1> {
		static ANVIL_STRONG_INLINE uint16_t ANVIL_CALL execute(uint16_t x) { return x; }
	};

	template<>
	struct VectorOperation<uint8_t, 1, VOP_abs, 1> {
		static ANVIL_STRONG_INLINE uint8_t ANVIL_CALL execute(uint8_t x) { return x; }
	};

	template<class T>
	struct VectorOperation<T, 1, VOP_sqrt, 1> {
		static ANVIL_STRONG_INLINE T ANVIL_CALL execute(T x) { return std::sqrt(x); }
	};

	template<class T>
	struct VectorOperation<T, 1, VOP_cbrt, 1> {
		static ANVIL_STRONG_INLINE T ANVIL_CALL execute(T x) { return std::cbrt(x); }
	};

	template<class T>
	struct VectorOperation<T, 1, VOP_not, 1> {
		static ANVIL_STRONG_INLINE T ANVIL_CALL execute(T x) { return ~ x; }
	};

	template<>
	struct VectorOperation<float, 1, VOP_not, 1> {
		static ANVIL_STRONG_INLINE float ANVIL_CALL execute(float x) { 
			union {
				float f;
				uint32_t i;
			};
			f = x;
			i = ~i;
			return f;
		}
	};

	template<>
	struct VectorOperation<double, 1, VOP_not, 1> {
		static ANVIL_STRONG_INLINE double ANVIL_CALL execute(double x) {
			union {
				double f;
				uint64_t i;
			};
			f = x;
			i = ~i;
			return f;
		}
	};

	template<class T>
	struct VectorOperation<T, 1, VOP_ceil, 1> {
		static ANVIL_STRONG_INLINE T ANVIL_CALL execute(T x) { return x; }
	};

	template<>
	struct VectorOperation<float, 1, VOP_ceil, 1> {
		static ANVIL_STRONG_INLINE float ANVIL_CALL execute(float x) { return std::ceil(x); }
	};

	template<>
	struct VectorOperation<double, 1, VOP_ceil, 1> {
		static ANVIL_STRONG_INLINE double ANVIL_CALL execute(double x) { return std::ceil(x); }
	};

	template<class T>
	struct VectorOperation<T, 1, VOP_floor, 1> {
		static ANVIL_STRONG_INLINE T ANVIL_CALL execute(T x) { return x; }
	};

	template<>
	struct VectorOperation<float, 1, VOP_floor, 1> {
		static ANVIL_STRONG_INLINE float ANVIL_CALL execute(float x) { return std::floor(x); }
	};

	template<>
	struct VectorOperation<double, 1, VOP_floor, 1> {
		static ANVIL_STRONG_INLINE double ANVIL_CALL execute(double x) { return std::floor(x); }
	};

#define ANVIL_SPECIALISE_VEC_VV_(NAME,TYPE,SIZE,SIZE2,INTRINSIC,FUNCTION,ZERO_FLAG) \
	template<>\
	struct VectorOperation<TYPE,SIZE, VOP_ ## NAME ,1> {\
		static ANVIL_STRONG_INLINE Vector<TYPE, SIZE> ANVIL_CALL execute(Vector<TYPE, SIZE> x) {\
			union {\
				Vector<TYPE,SIZE> v;\
				Vector<TYPE,SIZE2> v2;\
				INTRINSIC i;\
			};\
			if (ZERO_FLAG) v2 = fill_0<TYPE, SIZE2>(); \
			v = x;\
			i = FUNCTION(i);\
			return v;\
		}\
	};

#define ANVIL_SPECIALISE_VEC_VV2(NAME,TYPE,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VV_(NAME,TYPE,2,2,INTRINSIC,FUNCTION,false)

#define ANVIL_SPECIALISE_VEC_VV4(NAME,TYPE,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VV_(NAME,TYPE,4,4,INTRINSIC,FUNCTION,false)\
	ANVIL_SPECIALISE_VEC_VV_(NAME,TYPE,3,4,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VV_(NAME,TYPE,2,4,INTRINSIC,FUNCTION,ZERO_FLAG)

#define ANVIL_SPECIALISE_VEC_VV8(NAME,TYPE,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VV_(NAME,TYPE,8,8,INTRINSIC,FUNCTION,false)\
	ANVIL_SPECIALISE_VEC_VV_(NAME,TYPE,7,8,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VV_(NAME,TYPE,6,8,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VV_(NAME,TYPE,5,8,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VV_(NAME,TYPE,4,8,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VV_(NAME,TYPE,3,8,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VV_(NAME,TYPE,2,8,INTRINSIC,FUNCTION,ZERO_FLAG)

#define ANVIL_SPECIALISE_VEC_VV16(NAME,TYPE,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VV_(NAME,TYPE,16,16,INTRINSIC,FUNCTION,false)\
	ANVIL_SPECIALISE_VEC_VV_(NAME,TYPE,15,16,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VV_(NAME,TYPE,14,16,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VV_(NAME,TYPE,13,16,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VV_(NAME,TYPE,12,16,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VV_(NAME,TYPE,11,16,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VV_(NAME,TYPE,10,16,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VV_(NAME,TYPE,9,16,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VV_(NAME,TYPE,8,16,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VV_(NAME,TYPE,7,16,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VV_(NAME,TYPE,6,16,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VV_(NAME,TYPE,5,16,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VV_(NAME,TYPE,4,16,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VV_(NAME,TYPE,3,16,INTRINSIC,FUNCTION,ZERO_FLAG)\
	ANVIL_SPECIALISE_VEC_VV_(NAME,TYPE,2,16,INTRINSIC,FUNCTION,ZERO_FLAG)

#ifdef ANVIL_SSE
	ANVIL_SPECIALISE_VEC_VV4(sqrt, float, __m128, _mm_sqrt_ps, false)
#endif

#ifdef ANVIL_SSE2
	ANVIL_SPECIALISE_VEC_VV2(sqrt, double, __m128d, _mm_sqrt_pd, false)
#endif

#ifdef ANVIL_SSE3
	ANVIL_SPECIALISE_VEC_VV4( abs, int32_t, __m128i, _mm_abs_epi32, false)
	ANVIL_SPECIALISE_VEC_VV8( abs, int16_t, __m128i, _mm_abs_epi16, false)
	ANVIL_SPECIALISE_VEC_VV16(abs, int8_t,  __m128i, _mm_abs_epi8,  false)
#endif

#ifdef ANVIL_SSE4_1
	ANVIL_SPECIALISE_VEC_VV2(ceil,  double, __m128d, _mm_ceil_pd,  false)
	ANVIL_SPECIALISE_VEC_VV2(floor, double, __m128d, _mm_floor_pd, false)

	ANVIL_SPECIALISE_VEC_VV4(ceil,  float, __m128, _mm_ceil_ps,  false)
	ANVIL_SPECIALISE_VEC_VV4(floor, float, __m128, _mm_floor_ps, false)
#endif

	}
}
#endif