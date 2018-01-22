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
		static Vector<T, S> fill(T x) {
			Vector<T, S> tmp;
			for (size_t i = 0; i < S; ++i) tmp.elements[i] = aValue;
			return tmp;
		}

		template<class T, size_t S>
		static Vector<T, S> fill(T x, T y) {
			static_assert(S >= 2, "Vector must have at least 2 elements")
			Vector<T, S> tmp;
			tmp.elements[0] = x;
			tmp.elements[1] = y;
			for (size_t i = 2; i < S; ++i) tmp.elements[i] = static_cast<T>(0);
			return tmp;
		}

		template<class T, size_t S>
		static Vector<T, S> fill(T x, T y, T z) {
			static_assert(S >= 3, "Vector must have at least 3 elements")
			Vector<T, S> tmp;
			tmp.elements[0] = x;
			tmp.elements[1] = y;
			tmp.elements[2] = z;
			for (size_t i = 3; i < S; ++i) tmp.elements[i] = static_cast<T>(0);
			return tmp;
		}

		template<class T, size_t S>
		static Vector<T, S> fill(T x, T y, T z, T w) {
			static_assert(S >= 4, "Vector must have at least 3 elements")
				Vector<T, S> tmp;
			tmp.elements[0] = x;
			tmp.elements[1] = y;
			tmp.elements[2] = z;
			tmp.elements[3] = w;
			for (size_t i = 3; i < S; ++i) tmp.elements[i] = static_cast<T>(0);
			return tmp;
		}

#define ANVIL_VALUE_CAST(T,X) (*reinterpret_cast<T*>(&X))

#define ANVIL_SPECIALISE_VEC_FILL_XN(TYPE,TYPE2,SIZE,INTRINSIC,FUNCTION) \
		template<>\
		static ANVIL_STRONG_INLINE Vector<TYPE, SIZE> fill<TYPE, SIZE>(TYPE x) {\
			static_assert(sizeof(TYPE) == sizeof(TYPE2), "Types must be the same size");\
			union {\
				Vector<TYPE, SIZE> vector;\
				INTRINSIC intrinsic;\
			};\
			intrinsic = FUNCTION(ANVIL_VALUE_CAST(TYPE2, x));\
			return vector;\
		}

#define ANVIL_SPECIALISE_VEC_FILL_XY2(TYPE,TYPE2,SIZE,INTRINSIC,FUNCTION) \
		template<>\
		static ANVIL_STRONG_INLINE Vector<TYPE, SIZE> fill<TYPE, SIZE>(TYPE x, TYPE y) {\
			static_assert(sizeof(TYPE) == sizeof(TYPE2), "Types must be the same size");\
			union {\
				Vector<TYPE, SIZE> vector;\
				INTRINSIC intrinsic;\
			};\
			intrinsic = FUNCTION(ANVIL_VALUE_CAST(TYPE2, x), ANVIL_VALUE_CAST(TYPE2, y));\
			return vector;\
		}

#define ANVIL_SPECIALISE_VEC_FILL_XYZ3(TYPE,TYPE2,SIZE,INTRINSIC,FUNCTION) \
		template<>\
		static ANVIL_STRONG_INLINE Vector<TYPE, SIZE> fill<TYPE, SIZE>(TYPE x, TYPE y, TYPE z) {\
			static_assert(sizeof(TYPE) == sizeof(TYPE2), "Types must be the same size");\
			union {\
				Vector<TYPE, SIZE> vector;\
				INTRINSIC intrinsic;\
			};\
			intrinsic = FUNCTION(ANVIL_VALUE_CAST(TYPE2, x), ANVIL_VALUE_CAST(TYPE2, y), ANVIL_VALUE_CAST(TYPE2, z));\
			return vector;\
		}

#define ANVIL_SPECIALISE_VEC_FILL_XYZ4(TYPE,TYPE2,SIZE,INTRINSIC,FUNCTION) \
		template<>\
		static ANVIL_STRONG_INLINE Vector<TYPE, SIZE> fill<TYPE, SIZE>(TYPE x, TYPE y, TYPE z, TYPE w) {\
			static_assert(sizeof(TYPE) == sizeof(TYPE2), "Types must be the same size");\
			union {\
				Vector<TYPE, SIZE> vector;\
				INTRINSIC intrinsic;\
			};\
			intrinsic = FUNCTION(ANVIL_VALUE_CAST(TYPE2, x), ANVIL_VALUE_CAST(TYPE2, y));\
			return vector;\
		}

#define ANVIL_SPECIALISE_VEC_FILL_XY4(TYPE,TYPE2,SIZE,INTRINSIC,FUNCTION) \
		template<>\
		static ANVIL_STRONG_INLINE Vector<TYPE, SIZE> fill<TYPE, SIZE>(TYPE x, TYPE y) {\
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
		static ANVIL_STRONG_INLINE Vector<TYPE, SIZE> fill<TYPE, SIZE>(TYPE x, TYPE y, TYPE z) {\
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
		static ANVIL_STRONG_INLINE Vector<TYPE, SIZE> fill<TYPE, SIZE>(TYPE x, TYPE y, TYPE z, TYPE w) {\
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
		static ANVIL_STRONG_INLINE Vector<TYPE, SIZE> fill<TYPE, SIZE>(TYPE x, TYPE y) {\
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
		static ANVIL_STRONG_INLINE Vector<TYPE, SIZE> fill<TYPE, SIZE>(TYPE x, TYPE y, TYPE z) {\
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
		static ANVIL_STRONG_INLINE Vector<TYPE, SIZE> fill<TYPE, SIZE>(TYPE x, TYPE y, TYPE z, TYPE w) {\
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
		static ANVIL_STRONG_INLINE Vector<TYPE, SIZE> fill<TYPE, SIZE>(TYPE x, TYPE y) {\
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
		static ANVIL_STRONG_INLINE Vector<TYPE, SIZE> fill<TYPE, SIZE>(TYPE x, TYPE y, TYPE z) {\
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
		static ANVIL_STRONG_INLINE Vector<TYPE, SIZE> fill<TYPE, SIZE>(TYPE x, TYPE y, TYPE z, TYPE w) {\
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

#define ANVIL_SPECIALISE_VEC_FILL_2(TYPE, TYPE2, INTRINSIC, FUNCTION1, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XN( TYPE, TYPE2, 2, INTRINSIC, FUNCTION1)\
		ANVIL_SPECIALISE_VEC_FILL_XY2(TYPE, TYPE2, 2, INTRINSIC, FUNCTION2)

#define ANVIL_SPECIALISE_VEC_FILL_4(TYPE, TYPE2, INTRINSIC, FUNCTION1, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XN(   TYPE, TYPE2, 4, INTRINSIC, FUNCTION1)\
		ANVIL_SPECIALISE_VEC_FILL_XN(   TYPE, TYPE2, 3, INTRINSIC, FUNCTION1)\
		ANVIL_SPECIALISE_VEC_FILL_XN(   TYPE, TYPE2, 2, INTRINSIC, FUNCTION1)\
		ANVIL_SPECIALISE_VEC_FILL_XY4(  TYPE, TYPE2, 4, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XY4(  TYPE, TYPE2, 3, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XY4(  TYPE, TYPE2, 2, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZ4( TYPE, TYPE2, 4, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZ4( TYPE, TYPE2, 3, INTRINSIC, FUNCTION2)\
		ANVIL_SPECIALISE_VEC_FILL_XYZW4(TYPE, TYPE2, 4, INTRINSIC, FUNCTION2)

#define ANVIL_SPECIALISE_VEC_FILL_8(TYPE, TYPE2, INTRINSIC, FUNCTION1, FUNCTION2)\
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

#define ANVIL_SPECIALISE_VEC_FILL_16(TYPE, TYPE2, INTRINSIC, FUNCTION1, FUNCTION2)\
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
		ANVIL_SPECIALISE_VEC_FILL_4(float, float, __m128, _mm_set1_ps, _mm_set_ps)
#endif

#ifdef ANVIL_SSE2
		ANVIL_SPECIALISE_VEC_FILL_2(double,   double,   __m128d, _mm_set1_pd,     _mm_set_pd)
		ANVIL_SPECIALISE_VEC_FILL_2(int64_t,  int64_t,  __m128i, _mm_set1_epi64x, _mm_set_epi64x)
		ANVIL_SPECIALISE_VEC_FILL_2(uint64_t, uint64_t, __m128i, _mm_set1_epi64x, _mm_set_epi64x)
		ANVIL_SPECIALISE_VEC_FILL_4(int32_t,  int32_t,  __m128i, _mm_set1_epi32,  _mm_set_epi32)
		ANVIL_SPECIALISE_VEC_FILL_4(uint32_t, int32_t,  __m128i, _mm_set1_epi32,  _mm_set_epi32)
		ANVIL_SPECIALISE_VEC_FILL_8(int16_t,  int16_t,  __m128i, _mm_set1_epi16,  _mm_set_epi16)
		ANVIL_SPECIALISE_VEC_FILL_8(uint16_t, int16_t,  __m128i, _mm_set1_epi16,  _mm_set_epi16)
		ANVIL_SPECIALISE_VEC_FILL_16(int8_t,  int8_t,   __m128i, _mm_set1_epi8,   _mm_set_epi8)
		ANVIL_SPECIALISE_VEC_FILL_16(uint8_t, int8_t,   __m128i, _mm_set1_epi8,   _mm_set_epi8)
#endif

		// ---- ADD, SUB, MUL, DIV ----

		template<class T, size_t S>
		static Vector<T, S> add(Vector<T, S> x, Vector<T, S> y) {
			Vector<T, S> tmp;
			for (size_t i = 0; i < S; ++i) tmp.elements[i] = x.elements[i] + y.elements[i];
			return tmp;
		}

		template<class T, size_t S>
		static Vector<T, S> sub(Vector<T, S> x, Vector<T, S> y) {
			Vector<T, S> tmp;
			for (size_t i = 0; i < S; ++i) tmp.elements[i] = x.elements[i] - y.elements[i];
			return tmp;
		}

		template<class T, size_t S>
		static Vector<T, S> mul(Vector<T, S> x, Vector<T, S> y) {
			Vector<T, S> tmp;
			for (size_t i = 0; i < S; ++i) tmp.elements[i] = x.elements[i] * y.elements[i];
			return tmp;
		}

		template<class T, size_t S>
		static Vector<T, S> div(Vector<T, S> x, Vector<T, S> y) {
			Vector<T, S> tmp;
			for (size_t i = 0; i < S; ++i) tmp.elements[i] = x.elements[i] / y.elements[i];
			return tmp;
		}

#define ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,SIZE,INTRINSIC,FUNCTION) \
		template<>\
		static ANVIL_STRONG_INLINE Vector<TYPE, SIZE> NAME <TYPE,SIZE>(Vector<TYPE, SIZE> x, Vector<TYPE, SIZE> y) {\
			union {\
				Vector<TYPE, SIZE> xv;\
				INTRINSIC xi;\
			};\
			union {\
				Vector<TYPE, SIZE> yv;\
				INTRINSIC yi;\
			};\
			union {\
				Vector<TYPE, SIZE> rv;\
				INTRINSIC ri;\
			};\
			xv = x;\
			yv = y;\
			ri = FUNCTION(xi, yi);\
			return rv;\
		}

#define ANVIL_SPECIALISE_VEC_VVV2(NAME,TYPE,INTRINSIC,FUNCTION)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,2,INTRINSIC,FUNCTION)

#define ANVIL_SPECIALISE_VEC_VVV4(NAME,TYPE,INTRINSIC,FUNCTION)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,4,INTRINSIC,FUNCTION)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,3,INTRINSIC,FUNCTION)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,2,INTRINSIC,FUNCTION)

#define ANVIL_SPECIALISE_VEC_VVV8(NAME,TYPE,INTRINSIC,FUNCTION)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,8,INTRINSIC,FUNCTION)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,7,INTRINSIC,FUNCTION)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,6,INTRINSIC,FUNCTION)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,5,INTRINSIC,FUNCTION)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,4,INTRINSIC,FUNCTION)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,3,INTRINSIC,FUNCTION)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,2,INTRINSIC,FUNCTION)

#define ANVIL_SPECIALISE_VEC_VVV16(NAME,TYPE,INTRINSIC,FUNCTION)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,16,INTRINSIC,FUNCTION)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,15,INTRINSIC,FUNCTION)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,14,INTRINSIC,FUNCTION)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,13,INTRINSIC,FUNCTION)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,12,INTRINSIC,FUNCTION)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,11,INTRINSIC,FUNCTION)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,10,INTRINSIC,FUNCTION)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,9,INTRINSIC,FUNCTION)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,8,INTRINSIC,FUNCTION)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,7,INTRINSIC,FUNCTION)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,6,INTRINSIC,FUNCTION)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,5,INTRINSIC,FUNCTION)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,4,INTRINSIC,FUNCTION)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,3,INTRINSIC,FUNCTION)\
	ANVIL_SPECIALISE_VEC_VVV_(NAME,TYPE,2,INTRINSIC,FUNCTION)

#ifdef ANVIL_SSE
	ANVIL_SPECIALISE_VEC_VVV4(add, float, __m128, _mm_add_ps)
	ANVIL_SPECIALISE_VEC_VVV4(sub, float, __m128, _mm_sub_ps)
	ANVIL_SPECIALISE_VEC_VVV4(mul, float, __m128, _mm_mul_ps)
	ANVIL_SPECIALISE_VEC_VVV4(div, float, __m128, _mm_div_ps)
#endif

#ifdef ANVIL_SSE2
		ANVIL_SPECIALISE_VEC_VVV2(add, double, __m128d, _mm_add_pd)
		ANVIL_SPECIALISE_VEC_VVV2(sub, double, __m128d, _mm_sub_pd)
		ANVIL_SPECIALISE_VEC_VVV2(mul, double, __m128d, _mm_mul_pd)
		ANVIL_SPECIALISE_VEC_VVV2(div, double, __m128d, _mm_div_pd)

		ANVIL_SPECIALISE_VEC_VVV2(add, int64_t, __m128i, _mm_add_epi64)
		ANVIL_SPECIALISE_VEC_VVV2(sub, int64_t, __m128i, _mm_sub_epi64)

		ANVIL_SPECIALISE_VEC_VVV4(add, int32_t, __m128i, _mm_add_epi32)
		ANVIL_SPECIALISE_VEC_VVV4(sub, int32_t, __m128i, _mm_sub_epi32)

		ANVIL_SPECIALISE_VEC_VVV4(mul, uint32_t, __m128i, _mm_mul_epu32)

		ANVIL_SPECIALISE_VEC_VVV8(add, int16_t, __m128i, _mm_add_epi16)
		ANVIL_SPECIALISE_VEC_VVV8(sub, int16_t, __m128i, _mm_sub_epi16)

		ANVIL_SPECIALISE_VEC_VVV8(add, uint16_t, __m128i, _mm_adds_epu16)
		ANVIL_SPECIALISE_VEC_VVV8(sub, uint16_t, __m128i, _mm_subs_epu16)

		ANVIL_SPECIALISE_VEC_VVV16(add, int8_t, __m128i, _mm_add_epi8)
		ANVIL_SPECIALISE_VEC_VVV16(sub, int8_t, __m128i, _mm_sub_epi8)

		ANVIL_SPECIALISE_VEC_VVV16(add, uint8_t, __m128i, _mm_adds_epi8)
		ANVIL_SPECIALISE_VEC_VVV16(sub, uint8_t, __m128i, _mm_subs_epi8)
#endif

	}
}
#endif