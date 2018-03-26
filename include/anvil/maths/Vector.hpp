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
#include "anvil/Core/Keywords.hpp"

#ifdef ANVIL_SSE
#include <xmmintrin.h>
#endif

namespace anvil { namespace maths {
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

		ANVIL_STRONG_INLINE T& operator[](const size_t a_index) throw() {
			return elements[a_index];
		}

		ANVIL_STRONG_INLINE T operator[](const size_t a_index) const throw() {
			return elements[a_index];
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

		ANVIL_STRONG_INLINE type& operator[](const size_t a_index) throw() {
			return elements[a_index];
		}

		ANVIL_STRONG_INLINE type operator[](const size_t a_index) const throw() {
			return elements[a_index];
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

		ANVIL_STRONG_INLINE type& operator[](const size_t a_index) throw() {
			return elements[a_index];
		}

		ANVIL_STRONG_INLINE type operator[](const size_t a_index) const throw() {
			return elements[a_index];
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

		ANVIL_STRONG_INLINE type& operator[](const size_t a_index) throw() {
			return elements[a_index];
		}

		ANVIL_STRONG_INLINE type operator[](const size_t a_index) const throw() {
			return elements[a_index];
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

		ANVIL_STRONG_INLINE type& operator[](const size_t a_index) throw() {
			return elements[a_index];
		}

		ANVIL_STRONG_INLINE type operator[](const size_t a_index) const throw() {
			return elements[a_index];
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

	namespace detail {
		template<class T, size_t S>
		struct VectorWorkType {
			enum { 
				optimised = 0,
				alignment = 0
			};
			typedef Vector<T, S> type;

			static ANVIL_STRONG_INLINE type load(const Vector<T, S> a_value) throw() {
				return a_value;
			}

			static ANVIL_STRONG_INLINE Vector<T, S> store(const type a_value) throw() {
				return a_value;
			}
		};

		//template<class T>
		//struct VectorWorkType<T, 8> {
		//	enum {
		//		optimised = VectorWorkType<T, 4>::optimised
		//		alignment = VectorWorkType<T, 4>::alignment
		//	};
		//	
		//	struct type {
		//		typename VectorWorkType<T, 4>::type lo;
		//		typename VectorWorkType<T, 4>::type hi;
		//	};

		//	static ANVIL_STRONG_INLINE type load(const Vector<T, 8> a_value) throw() {
		//		union {
		//			const Vector<T, 8> v8;
		//			const Vector<T, 4> v4[2];
		//		} u;
		//		v8 = a_value;
		//		tmp.lo = VectorWorkType<T, 4>::load(u.v4[0]);
		//		tmp.hi = VectorWorkType<T, 4>::load(u.v4[1]);
		//		return tmp;
		//	}

		//	static ANVIL_STRONG_INLINE Vector<T, 8> store(const type a_value) throw() {
		//		union {
		//			const Vector<T, 8> v8;
		//			const Vector<T, 4> v4[2];
		//		} u;
		//		u.v4[0] = VectorWorkType<T, 4>::store(a_value.lo);
		//		u.v4[1] = VectorWorkType<T, 4>::store(a_value.hi);
		//		return u.v8;
		//	}
		//};

#ifdef ANVIL_SSE
		template<>
		struct VectorWorkType<float,4> {
			enum {
				optimised = 1,
				alignment = 16
			};
			typedef __m128 type;

			static ANVIL_STRONG_INLINE type load(const Vector<float, 4> a_value) throw() {
				return _mm_load_ps(a_value.elements);
			}

			static ANVIL_STRONG_INLINE Vector<float, 4> store(const type a_value) throw() {
				Vector<float, 4> tmp;
				_mm_store_ps(tmp.elements, a_value);
				return tmp;
			}
		};
#endif
	}
}}

#endif