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

#include <cstdint>
#include <type_traits>
#include <iostream>
#include "anvil/core/Keywords.hpp"
#include "anvil/core/Cpu.hpp"

#if ANVIL_ARCHITECTURE == ANVIL_X86 || ANVIL_ARCHITECTURE == ANVIL_X64
#define ANVIL_VECTOR_CALL __vectorcall
#else
#define ANVIL_VECTOR_CALL ANVIL_CALL 
#endif

#ifdef ANVIL_SSE
#include <xmmintrin.h>
#endif

namespace anvil {
	template<class T, size_t S>
	struct Vector;

	template<class T>
	struct Vector<T, 2> {
		enum { size = 2 };
		typedef T type;

		union {
			struct {
				T s0, s1;
			};
			struct {
				T x, y;
			};
			T elements[size];
		};

		ANVIL_STRONG_INLINE T& ANVIL_VECTOR_CALL operator[](const size_t a_index) throw() {
			return elements[a_index];
		}

		ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL operator[](const size_t a_index) const throw() {
			return elements[a_index];
		}

		static ANVIL_STRONG_INLINE Vector<T, size> ANVIL_VECTOR_CALL zeros() throw() {
			Vector<T, size> tmp;
			tmp ^= tmp;
			return tmp;
		}

		static ANVIL_STRONG_INLINE Vector<T, size> ANVIL_VECTOR_CALL create(const T i0) throw() {
			Vector<T, size> tmp;
			tmp.x = i0;
			tmp.y = i0;
			return tmp;
		}

		static ANVIL_STRONG_INLINE Vector<T, size> ANVIL_VECTOR_CALL create(const T i0, const T i1) throw() {
			Vector<T, size> tmp;
			tmp.x = i0;
			tmp.y = i1;
			return tmp;
		}
	};

	template<class T>
	struct Vector<T, 3> {
		enum { size = 3 };
		typedef T type;

		union {
			struct {
				type s0, s1, s2;
			};
			struct {
				type x, y, z;
			};
			type elements[size];
		};

		ANVIL_STRONG_INLINE type& ANVIL_VECTOR_CALL operator[](const size_t a_index) throw() {
			return elements[a_index];
		}

		ANVIL_STRONG_INLINE type ANVIL_VECTOR_CALL operator[](const size_t a_index) const throw() {
			return elements[a_index];
		}

		static ANVIL_STRONG_INLINE Vector<T, size> ANVIL_VECTOR_CALL zeros() throw() {
			Vector<T, size> tmp;
			tmp ^= tmp;
			return tmp;
		}

		static ANVIL_STRONG_INLINE Vector<T, size> ANVIL_VECTOR_CALL create(const T a0) throw() {
			Vector<T, size> tmp;
			tmp.x = a0;
			tmp.y = a0;
			tmp.z = a0;
			return tmp;
		}

		static ANVIL_STRONG_INLINE Vector<T, size> ANVIL_VECTOR_CALL create(const T a0, const T a1, const T a2) throw() {
			Vector<T, size> tmp;
			tmp.x = a0;
			tmp.y = a1;
			tmp.z = a2;
			return tmp;
		}
	};


	template<class T>
	struct Vector<T, 4> {
		enum { size = 4 };
		typedef T type;

		union {
			struct {
				type s0, s1, s2, s3;
			};
			struct {
				type x, y, z, w;
			};
			type elements[size];
		};

		ANVIL_STRONG_INLINE type& ANVIL_VECTOR_CALL operator[](const size_t a_index) throw() {
			return elements[a_index];
		}

		ANVIL_STRONG_INLINE type ANVIL_VECTOR_CALL operator[](const size_t a_index) const throw() {
			return elements[a_index];
		}

		static ANVIL_STRONG_INLINE Vector<T, size> ANVIL_VECTOR_CALL zeros() throw() {
			Vector<T, size> tmp;
			tmp ^= tmp;
			return tmp;
		}

		static ANVIL_STRONG_INLINE Vector<T, size> ANVIL_VECTOR_CALL create(const T a0) throw() {
			Vector<T, size> tmp;
			tmp.x = a0;
			tmp.y = a0;
			tmp.z = a0;
			tmp.w = a0;
			return tmp;
		}

		static ANVIL_STRONG_INLINE Vector<T, size> ANVIL_VECTOR_CALL create(const T a0, const T a1, const T a2, const T a3) throw() {
			Vector<T, size> tmp;
			tmp.x = a0;
			tmp.y = a1;
			tmp.z = a2;
			tmp.w = a3;
			return tmp;
		}
	};

	template<class T>
	struct Vector<T, 8> {
		enum { size = 8 };
		typedef T type;

		union {
			struct {
				type s0, s1, s2, s3, s4, s5, s6, s7;
			};
			struct {
				type x, y, z, w;
			};
			type elements[size];
		};

		ANVIL_STRONG_INLINE type& ANVIL_VECTOR_CALL operator[](const size_t a_index) throw() {
			return elements[a_index];
		}

		ANVIL_STRONG_INLINE type ANVIL_VECTOR_CALL operator[](const size_t a_index) const throw() {
			return elements[a_index];
		}

		static ANVIL_STRONG_INLINE Vector<T, size> ANVIL_VECTOR_CALL zeros() throw() {
			Vector<T, size> tmp;
			tmp ^= tmp;
			return tmp;
		}

		static ANVIL_STRONG_INLINE Vector<T, size> ANVIL_VECTOR_CALL create(const T a0) throw() {
			Vector<T, size> tmp;
			tmp.s0 = a0;
			tmp.s1 = a0;
			tmp.s2 = a0;
			tmp.s3 = a0;
			tmp.s4 = a0;
			tmp.s5 = a0;
			tmp.s6 = a0;
			tmp.s7 = a0;
			return tmp;
		}

		static ANVIL_STRONG_INLINE Vector<T, size> ANVIL_VECTOR_CALL create(const T a0, const T a1, const T a2, const T a3, const T a4, const T a5, const T a6, const T a7) throw() {
			Vector<T, size> tmp;
			tmp.s0 = a0;
			tmp.s1 = a1;
			tmp.s2 = a2;
			tmp.s3 = a3;
			tmp.s4 = a4;
			tmp.s5 = a5;
			tmp.s6 = a6;
			tmp.s7 = a7;
			return tmp;
		}
	};

	template<class T>
	struct Vector<T, 16> {
		enum { size = 16 };
		typedef T type;

		union {
			struct {
				type s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15;
			};
			struct {
				type x, y, z, w;
			};
			type elements[size];
		};

		ANVIL_STRONG_INLINE type& ANVIL_VECTOR_CALL operator[](const size_t a_index) throw() {
			return elements[a_index];
		}

		ANVIL_STRONG_INLINE type ANVIL_VECTOR_CALL operator[](const size_t a_index) const throw() {
			return elements[a_index];
		}

		static ANVIL_STRONG_INLINE Vector<T, size> ANVIL_VECTOR_CALL zeros() throw() {
			Vector<T, size> tmp;
			tmp ^= tmp;
			return tmp;
		}

		static ANVIL_STRONG_INLINE Vector<T, size> ANVIL_VECTOR_CALL create(const T a0) throw() {
			Vector<T, size> tmp;
			tmp.s0 = a0;
			tmp.s1 = a0;
			tmp.s2 = a0;
			tmp.s3 = a0;
			tmp.s4 = a0;
			tmp.s5 = a0;
			tmp.s6 = a0;
			tmp.s7 = a0;
			tmp.s8 = a0;
			tmp.s9 = a0;
			tmp.s10 = a0;
			tmp.s11 = a0;
			tmp.s12 = a0;
			tmp.s13 = a0;
			tmp.s14 = a0;
			tmp.s15 = a0;
			return tmp;
		}

		static ANVIL_STRONG_INLINE Vector<T, size> ANVIL_VECTOR_CALL create(const T a0, const T a1, const T a2, const T a3, const T a4, const T a5, const T a6, const T a7,
			const T a8, const T a9, const T a10, const T a11, const T a12, const T a13, const T a14, const T a15
		) throw() {
			Vector<T, size> tmp;
			tmp.s0 = a0;
			tmp.s1 = a1;
			tmp.s2 = a2;
			tmp.s3 = a3;
			tmp.s4 = a4;
			tmp.s5 = a5;
			tmp.s6 = a6;
			tmp.s7 = a7;
			tmp.s8 = a8;
			tmp.s9 = a9;
			tmp.s10 = a10;
			tmp.s11 = a11;
			tmp.s12 = a12;
			tmp.s13 = a13;
			tmp.s14 = a14;
			tmp.s15 = a15;
			return tmp;
		}
	};

	typedef uint8_t             uint8x1_t;
	typedef Vector<uint8_t, 2>  uint8x2_t;
	typedef Vector<uint8_t, 3>  uint8x3_t;
	typedef Vector<uint8_t, 4>  uint8x4_t;
	typedef Vector<uint8_t, 8>  uint8x8_t;
	typedef Vector<uint8_t, 16> uint8x16_t;

	typedef uint8_t            int8x1_t;
	typedef Vector<int8_t, 2>  int8x2_t;
	typedef Vector<int8_t, 3>  int8x3_t;
	typedef Vector<int8_t, 4>  int8x4_t;
	typedef Vector<int8_t, 8>  int8x8_t;
	typedef Vector<int8_t, 16> int8x16_t;

	typedef uint16_t             uint16x1_t;
	typedef Vector<uint16_t, 2>  uint16x2_t;
	typedef Vector<uint16_t, 3>  uint16x3_t;
	typedef Vector<uint16_t, 4>  uint16x4_t;
	typedef Vector<uint16_t, 8>  uint16x8_t;
	typedef Vector<uint16_t, 16> uint16x16_t;

	typedef uint16_t            int16x1_t;
	typedef Vector<int16_t, 2>  int16x2_t;
	typedef Vector<int16_t, 3>  int16x3_t;
	typedef Vector<int16_t, 4>  int16x4_t;
	typedef Vector<int16_t, 8>  int16x8_t;
	typedef Vector<int16_t, 16> int16x16_t;

	typedef uint32_t             uint32x1_t;
	typedef Vector<uint32_t, 2>  uint32x2_t;
	typedef Vector<uint32_t, 3>  uint32x3_t;
	typedef Vector<uint32_t, 4>  uint32x4_t;
	typedef Vector<uint32_t, 8>  uint32x8_t;
	typedef Vector<uint32_t, 16> uint32x16_t;

	typedef uint32_t            int32x1_t;
	typedef Vector<int32_t, 2>  int32x2_t;
	typedef Vector<int32_t, 3>  int32x3_t;
	typedef Vector<int32_t, 4>  int32x4_t;
	typedef Vector<int32_t, 8>  int32x8_t;
	typedef Vector<int32_t, 16> int32x16_t;

	typedef uint64_t             uint64x1_t;
	typedef Vector<uint64_t, 2>  uint64x2_t;
	typedef Vector<uint64_t, 3>  uint64x3_t;
	typedef Vector<uint64_t, 4>  uint64x4_t;
	typedef Vector<uint64_t, 8>  uint64x8_t;
	typedef Vector<uint64_t, 16> uint64x16_t;

	typedef uint64_t            int64x1_t;
	typedef Vector<int64_t, 2>  int64x2_t;
	typedef Vector<int64_t, 3>  int64x3_t;
	typedef Vector<int64_t, 4>  int64x4_t;
	typedef Vector<int64_t, 8>  int64x8_t;
	typedef Vector<int64_t, 16> int64x16_t;

	typedef float             float32x1_t;
	typedef Vector<float, 2>  float32x2_t;
	typedef Vector<float, 3>  float32x3_t;
	typedef Vector<float, 4>  float32x4_t;
	typedef Vector<float, 8>  float32x8_t;
	typedef Vector<float, 16> float32x16_t;

	typedef double             float64x1_t;
	typedef Vector<double, 2>  float64x2_t;
	typedef Vector<double, 3>  float64x3_t;
	typedef Vector<double, 4>  float64x4_t;
	typedef Vector<double, 8>  float64x8_t;
	typedef Vector<double, 16> float64x16_t;

	union VectorUnion {
		uint8x1_t  u8x1[16];
		uint8x2_t  u8x2[8];
		uint8x3_t  u8x3[5];
		uint8x4_t  u8x4[4];
		uint8x8_t  u8x8[2];
		uint8x16_t u8x16;
		int8x1_t  s8x1[16];
		int8x2_t  s8x2[8];
		int8x3_t  s8x3[5];
		int8x4_t  s8x4[4];
		int8x8_t  s8x8[2];
		int8x16_t s8x16;
		uint16x1_t  u16x1[16];
		uint16x2_t  u16x2[8];
		uint16x3_t  u16x3[5];
		uint16x4_t  u16x4[4];
		uint16x8_t  u16x8[2];
		uint16x16_t u16x16;
		int16x1_t  s16x1[16];
		int16x2_t  s16x2[8];
		int16x3_t  s16x3[5];
		int16x4_t  s16x4[4];
		int16x8_t  s16x8[2];
		int16x16_t s16x16;
		uint32x1_t  u32x1[16];
		uint32x2_t  u32x2[8];
		uint32x3_t  u32x3[5];
		uint32x4_t  u32x4[4];
		uint32x8_t  u32x8[2];
		uint32x16_t u32x16;
		int32x1_t  s32x1[16];
		int32x2_t  s32x2[8];
		int32x3_t  s32x3[5];
		int32x4_t  s32x4[4];
		int32x8_t  s32x8[2];
		int32x16_t s32x16;
		uint64x1_t  u64x1[16];
		uint64x2_t  u64x2[8];
		uint64x3_t  u64x3[5];
		uint64x4_t  u64x4[4];
		uint64x8_t  u64x8[2];
		uint64x16_t u64x16;
		int64x1_t  s64x1[16];
		int64x2_t  s64x2[8];
		int64x3_t  s64x3[5];
		int64x4_t  s64x4[4];
		int64x8_t  s64x8[2];
		int64x16_t s64x16;
		float32x1_t  f32x1[16];
		float32x2_t  f32x2[8];
		float32x3_t  f32x3[5];
		float32x4_t  f32x4[4];
		float32x8_t  f32x8[2];
		float32x16_t f32x16;
		float64x1_t  f64x1[16];
		float64x2_t  f64x2[8];
		float64x3_t  f64x3[5];
		float64x4_t  f64x4[4];
		float64x8_t  f64x8[2];
		float64x16_t f64x16;
	};

	static_assert(sizeof(VectorUnion) == (8 * 16), "VectorUnion different size than expected");

	namespace detail {
		template<class T>
		struct OptimisedVectorPair {
			T lo;
			T hi;
		};

		template<class T, size_t S>
		struct OptimisedVector {
			typedef Vector<T, S> type;
			enum {
				size = S,
				optimised = 0
			};

			static ANVIL_STRONG_INLINE type ANVIL_VECTOR_CALL load(const Vector<T, S> aVector) throw() {
				return aVector;
			}

			static ANVIL_STRONG_INLINE Vector<T, S> ANVIL_VECTOR_CALL store(const register type aValue) throw() {
				return aValue;
			}
		};

#ifdef ANVIL_SSE

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

		template<>
		struct OptimisedVector<float, 8> {
			typedef float T;
			enum { S = 8, optimised = 1 };
#ifdef ANVIL_AVX
			typedef __m256 type;

			static ANVIL_STRONG_INLINE type ANVIL_VECTOR_CALL load(const Vector<T, S> aVector) throw() {
				return _mm256_load_ps(aVector.elements);
			}

			static ANVIL_STRONG_INLINE Vector<T, S> ANVIL_VECTOR_CALL store(const register type aValue) throw() {
				Vector<T, S> tmp;
				_mm_store256_ps(tmp.elements, aValue);
				return tmp;
			}
#else
			typedef OptimisedVectorPair<__m128> type;

			static ANVIL_STRONG_INLINE type ANVIL_VECTOR_CALL load(const Vector<T, S> aVector) throw() {
				type tmp;
				tmp.lo = _mm_load_ps(aVector.elements);
				tmp.hi = _mm_load_ps(aVector.elements + 4);
				return tmp;
			}

			static ANVIL_STRONG_INLINE Vector<T, S> ANVIL_VECTOR_CALL store(const register type aValue) throw() {
				Vector<T, S> tmp;
				_mm_store_ps(tmp.elements, aValue.lo);
				_mm_store_ps(tmp.elements + 4, aValue.hi);
				return tmp;
			}
#endif
		};

		template<>
		struct OptimisedVector<float, 16> {
			typedef float T;
			enum { S = 16, optimised = 1 };
#ifdef ANVIL_AVX
			typedef OptimisedVectorPair<__m256> type;

			static ANVIL_STRONG_INLINE type ANVIL_VECTOR_CALL load(const Vector<T, S> aVector) throw() {
				type tmp;
				tmp.lo = _mm256_load_ps(aVector.elements);
				tmp.hi = _mm256_load_ps(aVector.elements + 8);
				return tmp;
			}

			static ANVIL_STRONG_INLINE Vector<T, S> ANVIL_VECTOR_CALL store(const register type aValue) throw() {
				Vector<T, S> tmp;
				_mm256_store_ps(tmp.elements, aValue.lo);
				_mm256_store_ps(tmp.elements + 8, aValue.hi);
				return tmp;
			}
#else
			typedef OptimisedVectorPair<OptimisedVectorPair<__m128>> type;

			static ANVIL_STRONG_INLINE type ANVIL_VECTOR_CALL load(const Vector<T, S> aVector) throw() {
				type tmp;
				tmp.lo.lo = _mm_load_ps(aVector.elements);
				tmp.lo.hi = _mm_load_ps(aVector.elements + 4);
				tmp.hi.lo = _mm_load_ps(aVector.elements + 8);
				tmp.hi.hi = _mm_load_ps(aVector.elements + 12);
				return tmp;
			}

			static ANVIL_STRONG_INLINE Vector<T, S> ANVIL_VECTOR_CALL store(const register type aValue) throw() {
				Vector<T, S> tmp;
				_mm_store_ps(tmp.elements, aValue.lo.lo);
				_mm_store_ps(tmp.elements + 4, aValue.lo.hi);
				_mm_store_ps(tmp.elements + 8, aValue.hi.lo);
				_mm_store_ps(tmp.elements + 12, aValue.hi.hi);
				return tmp;
			}
#endif
		};
#endif
		enum VectorOperationID {
			VEC_ADD,
			VEC_SUB,
			VEC_MUL,
			VEC_DIV,
			VEC_AND,
			VEC_OR,
			VEC_XOR,
			VEC_FMA,
			VEC_FMS,
			VEC_SQRT,
			VEC_CBRT,
			VEC_NOT,
			VEC_COS,
			VEC_SIN,
			VEC_TAN,
			VEC_ACOS,
			VEC_ASIN,
			VEC_ATAN,
			VEC_COSH,
			VEC_SINH,
			VEC_TANH,
			VEC_ACOSH,
			VEC_ASINH,
			VEC_ATANH
		};

		template<class T, VectorOperationID ID, size_t P>
		struct VectorOperation;

		template<class T, VectorOperationID ID>
		struct VectorOperation<OptimisedVectorPair<T>, ID, 1> {
			static ANVIL_STRONG_INLINE OptimisedVectorPair<T> ANVIL_VECTOR_CALL implementation(const OptimisedVectorPair<T> a) {
				OptimisedVectorPair<T> tmp;
				tmp.lo = VectorOperation<T, ID, 1>::implementation(a.lo);
				tmp.hi = VectorOperation<T, ID, 1>::implementation(a.hi);
				return tmp;
			}
		};

		template<class T, VectorOperationID ID>
		struct VectorOperation<OptimisedVectorPair<T>, ID, 2> {
			static ANVIL_STRONG_INLINE OptimisedVectorPair<T> ANVIL_VECTOR_CALL implementation(const OptimisedVectorPair<T> a, const OptimisedVectorPair<T> b) {
				OptimisedVectorPair<T> tmp;
				tmp.lo = VectorOperation<T, ID, 2>::implementation(a.lo, b.lo);
				tmp.hi = VectorOperation<T, ID, 2>::implementation(a.hi, b.hi);
				return tmp;
			}
		};

		template<class T, VectorOperationID ID>
		struct VectorOperation<OptimisedVectorPair<T>, ID, 3> {
			static ANVIL_STRONG_INLINE OptimisedVectorPair<T> ANVIL_VECTOR_CALL implementation(const OptimisedVectorPair<T> a, const OptimisedVectorPair<T> b, const OptimisedVectorPair<T> c) {
				OptimisedVectorPair<T> tmp;
				tmp.lo = VectorOperation<T, ID, 3>::implementation(a.lo, b.lo, c.lo);
				tmp.hi = VectorOperation<T, ID, 3>::implementation(a.hi, b.hi, c.hi);
				return tmp;
			}
		};

		template<class T, size_t S>
		struct VectorOperation<Vector<T, S>, VEC_ADD, 2> {
			static ANVIL_STRONG_INLINE Vector<T, S> ANVIL_VECTOR_CALL implementation(const Vector<T, S> a, const Vector<T, S> b) {
				Vector<T, S> tmp;
				for (size_t i = 0; i < S; ++i) tmp.elements[i] = a.elements[i] + b.elements[i];
				return tmp;
			}
		};

		template<class T, size_t S>
		struct VectorOperation<Vector<T, S>, VEC_SUB, 2> {
			static ANVIL_STRONG_INLINE Vector<T, S> ANVIL_VECTOR_CALL implementation(const Vector<T, S> a, const Vector<T, S> b) {
				Vector<T, S> tmp;
				for (size_t i = 0; i < S; ++i) tmp.elements[i] = a.elements[i] - b.elements[i];
				return tmp;
			}
		};

		template<class T, size_t S>
		struct VectorOperation<Vector<T, S>, VEC_MUL, 2> {
			static ANVIL_STRONG_INLINE Vector<T, S> ANVIL_VECTOR_CALL implementation(const Vector<T, S> a, const Vector<T, S> b) {
				Vector<T, S> tmp;
				for (size_t i = 0; i < S; ++i) tmp.elements[i] = a.elements[i] * b.elements[i];
				return tmp;
			}
		};

		template<class T, size_t S>
		struct VectorOperation<Vector<T, S>, VEC_DIV, 2> {
			static ANVIL_STRONG_INLINE Vector<T, S> ANVIL_VECTOR_CALL implementation(const Vector<T, S> a, const Vector<T, S> b) {
				Vector<T, S> tmp;
				for (size_t i = 0; i < S; ++i) tmp.elements[i] = a.elements[i] / b.elements[i];
				return tmp;
			}
		};

		template<class T, size_t S>
		struct VectorOperation<Vector<T, S>, VEC_AND, 2> {
			static ANVIL_STRONG_INLINE Vector<T, S> ANVIL_VECTOR_CALL implementation(const Vector<T, S> a, const Vector<T, S> b) {
				Vector<T, S> tmp;
				for (size_t i = 0; i < S; ++i) tmp.elements[i] = a.elements[i] & b.elements[i];
				return tmp;
			}
		};

		template<class T, size_t S>
		struct VectorOperation<Vector<T, S>, VEC_OR, 2> {
			static ANVIL_STRONG_INLINE Vector<T, S> ANVIL_VECTOR_CALL implementation(const Vector<T, S> a, const Vector<T, S> b) {
				Vector<T, S> tmp;
				for (size_t i = 0; i < S; ++i) tmp.elements[i] = a.elements[i] | b.elements[i];
				return tmp;
			}
		};

		template<class T, size_t S>
		struct VectorOperation<Vector<T, S>, VEC_XOR, 2> {
			static ANVIL_STRONG_INLINE Vector<T, S> ANVIL_VECTOR_CALL implementation(const Vector<T, S> a, const Vector<T, S> b) {
				Vector<T, S> tmp;
				for (size_t i = 0; i < S; ++i) tmp.elements[i] = a.elements[i] ^ b.elements[i];
				return tmp;
			}
		};

		template<class T, size_t S>
		struct VectorOperation<Vector<T, S>, VEC_FMA, 3> {
			static ANVIL_STRONG_INLINE Vector<T, S> ANVIL_VECTOR_CALL implementation(const Vector<T, S> a, const Vector<T, S> b, const Vector<T, S> c) {
				Vector<T, S> tmp;
				for (size_t i = 0; i < S; ++i) tmp.elements[i] = (a.elements[i] * b.elements[i]) + c.elements[i];
				return tmp;
			}
		};

		template<class T, size_t S>
		struct VectorOperation<Vector<T, S>, VEC_FMS, 3> {
			static ANVIL_STRONG_INLINE Vector<T, S> ANVIL_VECTOR_CALL implementation(const Vector<T, S> a, const Vector<T, S> b, const Vector<T, S> c) {
				Vector<T, S> tmp;
				for (size_t i = 0; i < S; ++i) tmp.elements[i] = (a.elements[i] * b.elements[i]) - c.elements[i];
				return tmp;
			}
		};

		template<class T, size_t S>
		struct VectorOperation<Vector<T, S>, VEC_SQRT, 1> {
			static ANVIL_STRONG_INLINE Vector<T, S> ANVIL_VECTOR_CALL implementation(const Vector<T, S> a) {
				Vector<T, S> tmp;
				for (size_t i = 0; i < S; ++i) tmp.elements[i] = std::sqrt(a.elements[i]);
				return tmp;
			}
		};

#define ANVIL_VECTOR_OPERATOR(ID, FN)\
		template<class T, size_t S>\
		struct VectorOperation<Vector<T, S>, ID, 1> {\
			static ANVIL_STRONG_INLINE Vector<T, S> ANVIL_VECTOR_CALL implementation(const Vector<T, S> a) {\
				Vector<T, S> tmp;\
				for (size_t i = 0; i < S; ++i) tmp.elements[i] = FN(a.elements[i]);\
				return tmp;\
			}\
		};

		ANVIL_VECTOR_OPERATOR(VEC_CBRT, std::cbrt)
		ANVIL_VECTOR_OPERATOR(VEC_COS, std::cos)
		ANVIL_VECTOR_OPERATOR(VEC_SIN, std::sin)
		ANVIL_VECTOR_OPERATOR(VEC_TAN, std::tan)
		ANVIL_VECTOR_OPERATOR(VEC_ACOS, std::acos)
		ANVIL_VECTOR_OPERATOR(VEC_ASIN, std::asin)
		ANVIL_VECTOR_OPERATOR(VEC_ATAN, std::atan)
		ANVIL_VECTOR_OPERATOR(VEC_COSH, std::cosh)
		ANVIL_VECTOR_OPERATOR(VEC_SINH, std::sinh)
		ANVIL_VECTOR_OPERATOR(VEC_TANH, std::tanh)
		ANVIL_VECTOR_OPERATOR(VEC_ACOSH, std::acosh)
		ANVIL_VECTOR_OPERATOR(VEC_ASINH, std::asinh)
		ANVIL_VECTOR_OPERATOR(VEC_ATANH, std::atanh)
		#define ANVIL_VECTOR_NOT(X) ~X
		ANVIL_VECTOR_OPERATOR(VEC_NOT, ANVIL_VECTOR_NOT)
		#undef ANVIL_VECTOR_NOT

#undef ANVIL_VECTOR_OPERATOR

#ifdef ANVIL_SSE
		template<>
		struct VectorOperation<__m128, VEC_ADD, 2> {
			static ANVIL_STRONG_INLINE __m128 ANVIL_VECTOR_CALL implementation(const __m128 a, const __m128 b) {
				return _mm_add_ps(a, b);
			}
		};

		template<>
		struct VectorOperation<__m128, VEC_SUB, 2> {
			static ANVIL_STRONG_INLINE __m128 ANVIL_VECTOR_CALL implementation(const __m128 a, const __m128 b) {
				return _mm_sub_ps(a, b);
			}
		};

		template<>
		struct VectorOperation<__m128, VEC_MUL, 2> {
			static ANVIL_STRONG_INLINE __m128 ANVIL_VECTOR_CALL implementation(const __m128 a, const __m128 b) {
				return _mm_mul_ps(a, b);
			}
		};

		template<>
		struct VectorOperation<__m128, VEC_DIV, 2> {
			static ANVIL_STRONG_INLINE __m128 ANVIL_VECTOR_CALL implementation(const __m128 a, const __m128 b) {
				return _mm_div_ps(a, b);
			}
		};

		template<>
		struct VectorOperation<__m128, VEC_AND, 2> {
			static ANVIL_STRONG_INLINE __m128 ANVIL_VECTOR_CALL implementation(const __m128 a, const __m128 b) {
				return _mm_and_ps(a, b);
			}
		};

		template<>
		struct VectorOperation<__m128, VEC_OR, 2> {
			static ANVIL_STRONG_INLINE __m128 ANVIL_VECTOR_CALL implementation(const __m128 a, const __m128 b) {
				return _mm_or_ps(a, b);
			}
		};

		template<>
		struct VectorOperation<__m128, VEC_XOR, 2> {
			static ANVIL_STRONG_INLINE __m128 ANVIL_VECTOR_CALL implementation(const __m128 a, const __m128 b) {
				return _mm_xor_ps(a, b);
			}
		};

		template<>
		struct VectorOperation<__m128, VEC_FMA, 3> {
			static ANVIL_STRONG_INLINE __m128 ANVIL_VECTOR_CALL implementation(const __m128 a, const __m128 b, const __m128 c) {
#ifdef ANVIL_FMA
				return _mm_fmadd_ps(a, b, c);
#else
				return _mm_add_ps(_mm_mul_ps(a, b), c);
#endif
			}
		};

		template<>
		struct VectorOperation<__m128, VEC_FMS, 3> {
			static ANVIL_STRONG_INLINE __m128 ANVIL_VECTOR_CALL implementation(const __m128 a, const __m128 b, const __m128 c) {
#ifdef ANVIL_FMA
				return _mm_fmsub_ps(a, b, c);
#else
				return _mm_sub_ps(_mm_mul_ps(a, b), c);
#endif
			}
		};

		template<>
		struct VectorOperation<__m128, VEC_SQRT, 1> {
			static ANVIL_STRONG_INLINE __m128 ANVIL_VECTOR_CALL implementation(const __m128 a) {
				return _mm_sqrt_ps(a);
			}
		};

		template<>
		struct VectorOperation<__m128, VEC_NOT, 1> {
			static ANVIL_STRONG_INLINE __m128 ANVIL_VECTOR_CALL implementation(const __m128 a) {
				return _mm_xor_ps(a, _mm_cmpeq_ps(a, a));
			}
		};

#define ANVIL_VECTOR_OPERATOR(ID, FN)\
		template<>\
		struct VectorOperation<__m128, ID, 1> {\
			static ANVIL_STRONG_INLINE __m128 ANVIL_VECTOR_CALL implementation(const __m128 a) {\
				ANVIL_ALIGN(16) float buffer[4];\
				_mm_store_ps(buffer, a);\
				buffer[0] = FN(buffer[0]);\
				buffer[1] = FN(buffer[1]);\
				buffer[2] = FN(buffer[2]);\
				buffer[3] = FN(buffer[3]);\
				return _mm_load_ps(buffer);\
			}\
		};

		ANVIL_VECTOR_OPERATOR(VEC_CBRT, std::cbrt)
		ANVIL_VECTOR_OPERATOR(VEC_COS, std::cos)
		ANVIL_VECTOR_OPERATOR(VEC_SIN, std::sin)
		ANVIL_VECTOR_OPERATOR(VEC_TAN, std::tan)
		ANVIL_VECTOR_OPERATOR(VEC_ACOS, std::acos)
		ANVIL_VECTOR_OPERATOR(VEC_ASIN, std::asin)
		ANVIL_VECTOR_OPERATOR(VEC_ATAN, std::atan)
		ANVIL_VECTOR_OPERATOR(VEC_COSH, std::cosh)
		ANVIL_VECTOR_OPERATOR(VEC_SINH, std::sinh)
		ANVIL_VECTOR_OPERATOR(VEC_TANH, std::tanh)
		ANVIL_VECTOR_OPERATOR(VEC_ACOSH, std::acosh)
		ANVIL_VECTOR_OPERATOR(VEC_ASINH, std::asinh)
		ANVIL_VECTOR_OPERATOR(VEC_ATANH, std::atanh)

#undef ANVIL_VECTOR_OPERATOR
#endif

#ifdef ANVIL_AVX
		template<>
		struct VectorOperation<__m256, VEC_ADD, 2> {
			static ANVIL_STRONG_INLINE __m128 ANVIL_VECTOR_CALL implementation(const __m256 a, const __m256 b) {
				return _mm256_add_ps(a, b);
			}
		};

		template<>
		struct VectorOperation<__m256, VEC_FMA, 3> {
			static ANVIL_STRONG_INLINE __m256 ANVIL_VECTOR_CALL implementation(const __m256 a, const __m256 b, const __m256 c) {
#ifdef ANVIL_FMA
				return _mm256_fmadd_ps(a, b, c);
#else
				return _mm256_add_ps(_mm256_mul_ps(a, b), c);
#endif
			}
		};

		template<>
		struct VectorOperation<__m256, VEC_FMS, 3> {
			static ANVIL_STRONG_INLINE __m256 ANVIL_VECTOR_CALL implementation(const __m256 a, const __m256 b, const __m256 c) {
#ifdef ANVIL_FMA
				return _mm256_fmsub_ps(a, b, c);
#else
				return _mm256_sub_ps(_mm256_mul_ps(a, b), c);
#endif
			}
		};

		template<>
		struct VectorOperation<__m256, VEC_SQRT, 1> {
			static ANVIL_STRONG_INLINE __m256 ANVIL_VECTOR_CALL implementation(const __m256 a) {
				return _mm256_sqrt_ps(a);
			}
		};

		template<>
		struct VectorOperation<__m256, VEC_NOT, 1> {
			static ANVIL_STRONG_INLINE __m256 ANVIL_VECTOR_CALL implementation(const __m256 a) {
				return _mm256_xor_ps(a, _mm256_cmpeq_ps(a, a));
			}
		};

#define ANVIL_VECTOR_OPERATOR(ID, FN)\
		template<>\
		struct VectorOperation<__m256, ID, 1> {\
			static ANVIL_STRONG_INLINE __m256 ANVIL_VECTOR_CALL implementation(const __m256 a) {\
				ANVIL_ALIGN(16) float buffer[8];\
				_mm256_store_ps(buffer, a);\
				buffer[0] = FN(buffer[0]);\
				buffer[1] = FN(buffer[1]);\
				buffer[2] = FN(buffer[2]);\
				buffer[3] = FN(buffer[3]);\
				buffer[4] = FN(buffer[4]);\
				buffer[5] = FN(buffer[5]);\
				buffer[6] = FN(buffer[6]);\
				buffer[7] = FN(buffer[7]);\
				return _mm256_load_ps(buffer);\
			}\
		};

	ANVIL_VECTOR_OPERATOR(VEC_CBRT, std::cbrt)
	ANVIL_VECTOR_OPERATOR(VEC_COS, std::cos)
	ANVIL_VECTOR_OPERATOR(VEC_SIN, std::sin)
	ANVIL_VECTOR_OPERATOR(VEC_TAN, std::tan)
	ANVIL_VECTOR_OPERATOR(VEC_ACOS, std::acos)
	ANVIL_VECTOR_OPERATOR(VEC_ASIN, std::asin)
	ANVIL_VECTOR_OPERATOR(VEC_ATAN, std::atan)
	ANVIL_VECTOR_OPERATOR(VEC_COSH, std::cosh)
	ANVIL_VECTOR_OPERATOR(VEC_SINH, std::sinh)
	ANVIL_VECTOR_OPERATOR(VEC_TANH, std::tanh)
	ANVIL_VECTOR_OPERATOR(VEC_ACOSH, std::acosh)
	ANVIL_VECTOR_OPERATOR(VEC_ASINH, std::asinh)
	ANVIL_VECTOR_OPERATOR(VEC_ATANH, std::atanh)

#undef ANVIL_VECTOR_OPERATOR
#endif
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE anvil::Vector<T, S> fma(const anvil::Vector<T, S> a, const anvil::Vector<T, S> b, const anvil::Vector<T, S> c) {
		typedef anvil::detail::OptimisedVector<T, S> OpVec;
		typedef typename OpVec::type type;

		return OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_FMA, 3>::implementation(OpVec::load(a), OpVec::load(b), OpVec::load(c)));
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE anvil::Vector<T, S> fms(const anvil::Vector<T, S> a, const anvil::Vector<T, S> b, const anvil::Vector<T, S> c) {
		typedef anvil::detail::OptimisedVector<T, S> OpVec;
		typedef typename OpVec::type type;

		return OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_FMS, 3>::implementation(OpVec::load(a), OpVec::load(b), OpVec::load(c)));
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE anvil::Vector<T, S> sqrt(const anvil::Vector<T, S> a) {
		typedef anvil::detail::OptimisedVector<T, S> OpVec;
		typedef typename OpVec::type type;

		return OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_SQRT, 1>::implementation(OpVec::load(a)));
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE anvil::Vector<T, S> cbrt(const anvil::Vector<T, S> a) {
		typedef anvil::detail::OptimisedVector<T, S> OpVec;
		typedef typename OpVec::type type;

		return OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_CBRT, 1>::implementation(OpVec::load(a)));
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE anvil::Vector<T, S> not(const anvil::Vector<T, S> a) {
		typedef anvil::detail::OptimisedVector<T, S> OpVec;
		typedef typename OpVec::type type;

		return OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_NOT, 1>::implementation(OpVec::load(a)));
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE anvil::Vector<T, S> cos(const anvil::Vector<T, S> a) {
		typedef anvil::detail::OptimisedVector<T, S> OpVec;
		typedef typename OpVec::type type;

		return OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_COS, 1>::implementation(OpVec::load(a)));
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE anvil::Vector<T, S> sin(const anvil::Vector<T, S> a) {
		typedef anvil::detail::OptimisedVector<T, S> OpVec;
		typedef typename OpVec::type type;

		return OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_SIN, 1>::implementation(OpVec::load(a)));
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE anvil::Vector<T, S> tan(const anvil::Vector<T, S> a) {
		typedef anvil::detail::OptimisedVector<T, S> OpVec;
		typedef typename OpVec::type type;

		return OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_TAN, 1>::implementation(OpVec::load(a)));
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE anvil::Vector<T, S> acos(const anvil::Vector<T, S> a) {
		typedef anvil::detail::OptimisedVector<T, S> OpVec;
		typedef typename OpVec::type type;

		return OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_ACOS, 1>::implementation(OpVec::load(a)));
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE anvil::Vector<T, S> asin(const anvil::Vector<T, S> a) {
		typedef anvil::detail::OptimisedVector<T, S> OpVec;
		typedef typename OpVec::type type;

		return OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_ASIN, 1>::implementation(OpVec::load(a)));
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE anvil::Vector<T, S> atan(const anvil::Vector<T, S> a) {
		typedef anvil::detail::OptimisedVector<T, S> OpVec;
		typedef typename OpVec::type type;

		return OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_ATAN, 1>::implementation(OpVec::load(a)));
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE anvil::Vector<T, S> cosh(const anvil::Vector<T, S> a) {
		typedef anvil::detail::OptimisedVector<T, S> OpVec;
		typedef typename OpVec::type type;

		return OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_COSH, 1>::implementation(OpVec::load(a)));
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE anvil::Vector<T, S> sinh(const anvil::Vector<T, S> a) {
		typedef anvil::detail::OptimisedVector<T, S> OpVec;
		typedef typename OpVec::type type;

		return OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_SINH, 1>::implementation(OpVec::load(a)));
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE anvil::Vector<T, S> tanh(const anvil::Vector<T, S> a) {
		typedef anvil::detail::OptimisedVector<T, S> OpVec;
		typedef typename OpVec::type type;

		return OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_TANH, 1>::implementation(OpVec::load(a)));
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE anvil::Vector<T, S> acosh(const anvil::Vector<T, S> a) {
		typedef anvil::detail::OptimisedVector<T, S> OpVec;
		typedef typename OpVec::type type;

		return OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_ACOSH, 1>::implementation(OpVec::load(a)));
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE anvil::Vector<T, S> asinh(const anvil::Vector<T, S> a) {
		typedef anvil::detail::OptimisedVector<T, S> OpVec;
		typedef typename OpVec::type type;

		return OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_ASINH, 1>::implementation(OpVec::load(a)));
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE anvil::Vector<T, S> atanh(const anvil::Vector<T, S> a) {
		typedef anvil::detail::OptimisedVector<T, S> OpVec;
		typedef typename OpVec::type type;

		return OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_ATANH, 1>::implementation(OpVec::load(a)));
	}
}

template<class T, size_t S>
std::ostream& operator<<(std::ostream& aStream, const anvil::Vector<T, S> aVector) {
	aStream << '[';
	for (size_t i = 0; i < S; ++i){
		aStream << aVector[i];
		if (i + 1 < S) aStream << ',';
	}
	aStream << ']';
	return aStream;
}

template<class T, size_t S>
std::istream& operator>>(std::istream& aStream, const anvil::Vector<T, S> aVector) {
	char buf;
	aStream.read(&buf, 1);
	for (size_t i = 0; i < S; ++i) {
		aStream >> aVector[i];
		if (i + 1 < S) aStream.read(&buf, 1);
	}
	aStream.read(&buf, 1);
	return aStream;
}

template<class T, size_t S>
ANVIL_STRONG_INLINE anvil::Vector<T, S> operator+(const anvil::Vector<T, S> a, const anvil::Vector<T, S> b) {
	typedef anvil::detail::OptimisedVector<T, S> OpVec;
	typedef typename OpVec::type type;

	return OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_ADD, 2>::implementation(OpVec::load(a), OpVec::load(b)));
}

template<class T, size_t S>
ANVIL_STRONG_INLINE anvil::Vector<T, S>& operator+=(anvil::Vector<T, S>& a, const anvil::Vector<T, S> b) {
	typedef anvil::detail::OptimisedVector<T, S> OpVec;
	typedef typename OpVec::type type;

	a = OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_ADD, 2>::implementation(OpVec::load(a), OpVec::load(b)));
	return a;
}

template<class T, size_t S>
ANVIL_STRONG_INLINE anvil::Vector<T, S> operator-(const anvil::Vector<T, S> a, const anvil::Vector<T, S> b) {
	typedef anvil::detail::OptimisedVector<T, S> OpVec;
	typedef typename OpVec::type type;

	return OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_SUB, 2>::implementation(OpVec::load(a), OpVec::load(b)));
}

template<class T, size_t S>
ANVIL_STRONG_INLINE anvil::Vector<T, S>& operator-=(anvil::Vector<T, S>& a, const anvil::Vector<T, S> b) {
	typedef anvil::detail::OptimisedVector<T, S> OpVec;
	typedef typename OpVec::type type;

	a = OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_SUB, 2>::implementation(OpVec::load(a), OpVec::load(b)));
	return a;
}

template<class T, size_t S>
ANVIL_STRONG_INLINE anvil::Vector<T, S> operator*(const anvil::Vector<T, S> a, const anvil::Vector<T, S> b) {
	typedef anvil::detail::OptimisedVector<T, S> OpVec;
	typedef typename OpVec::type type;

	return OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_MUL, 2>::implementation(OpVec::load(a), OpVec::load(b)));
}

template<class T, size_t S>
ANVIL_STRONG_INLINE anvil::Vector<T, S>& operator*=(anvil::Vector<T, S>& a, const anvil::Vector<T, S> b) {
	typedef anvil::detail::OptimisedVector<T, S> OpVec;
	typedef typename OpVec::type type;

	a = OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_MUL, 2>::implementation(OpVec::load(a), OpVec::load(b)));
	return a;
}

template<class T, size_t S>
ANVIL_STRONG_INLINE anvil::Vector<T, S> operator/(const anvil::Vector<T, S> a, const anvil::Vector<T, S> b) {
	typedef anvil::detail::OptimisedVector<T, S> OpVec;
	typedef typename OpVec::type type;

	return OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_DIV, 2>::implementation(OpVec::load(a), OpVec::load(b)));
}

template<class T, size_t S>
ANVIL_STRONG_INLINE anvil::Vector<T, S>& operator/=(anvil::Vector<T, S>& a, const anvil::Vector<T, S> b) {
	typedef anvil::detail::OptimisedVector<T, S> OpVec;
	typedef typename OpVec::type type;

	a = OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_DIV, 2>::implementation(OpVec::load(a), OpVec::load(b)));
	return a;
}

template<class T, size_t S>
ANVIL_STRONG_INLINE anvil::Vector<T, S> operator&(const anvil::Vector<T, S> a, const anvil::Vector<T, S> b) {
	typedef anvil::detail::OptimisedVector<T, S> OpVec;
	typedef typename OpVec::type type;

	return OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_AND, 2>::implementation(OpVec::load(a), OpVec::load(b)));
}

template<class T, size_t S>
ANVIL_STRONG_INLINE anvil::Vector<T, S>& operator&=(anvil::Vector<T, S>& a, const anvil::Vector<T, S> b) {
	typedef anvil::detail::OptimisedVector<T, S> OpVec;
	typedef typename OpVec::type type;

	a = OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_AND, 2>::implementation(OpVec::load(a), OpVec::load(b)));
	return a;
}

template<class T, size_t S>
ANVIL_STRONG_INLINE anvil::Vector<T, S> operator|(const anvil::Vector<T, S> a, const anvil::Vector<T, S> b) {
	typedef anvil::detail::OptimisedVector<T, S> OpVec;
	typedef typename OpVec::type type;

	return OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_OR, 2>::implementation(OpVec::load(a), OpVec::load(b)));
}

template<class T, size_t S>
ANVIL_STRONG_INLINE anvil::Vector<T, S>& operator|=(anvil::Vector<T, S>& a, const anvil::Vector<T, S> b) {
	typedef anvil::detail::OptimisedVector<T, S> OpVec;
	typedef typename OpVec::type type;

	a = OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_OR, 2>::implementation(OpVec::load(a), OpVec::load(b)));
	return a;
}

template<class T, size_t S>
ANVIL_STRONG_INLINE anvil::Vector<T, S> operator^(const anvil::Vector<T, S> a, const anvil::Vector<T, S> b) {
	typedef anvil::detail::OptimisedVector<T, S> OpVec;
	typedef typename OpVec::type type;

	return OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_XOR, 2>::implementation(OpVec::load(a), OpVec::load(b)));
}

template<class T, size_t S>
ANVIL_STRONG_INLINE anvil::Vector<T, S>& operator^=(anvil::Vector<T, S>& a, const anvil::Vector<T, S> b) {
	typedef anvil::detail::OptimisedVector<T, S> OpVec;
	typedef typename OpVec::type type;

	a = OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_XOR, 2>::implementation(OpVec::load(a), OpVec::load(b)));
	return a;
}

template<class T, size_t S>
ANVIL_STRONG_INLINE anvil::Vector<T, S>& operator~(const anvil::Vector<T, S> a) {
	typedef anvil::detail::OptimisedVector<T, S> OpVec;
	typedef typename OpVec::type type;

	return OpVec::store(anvil::detail::VectorOperation<type, anvil::detail::VEC_NOT, 1>::implementation(OpVec::load(a)));
}

#endif