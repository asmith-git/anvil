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
		uint8x1_t  u8x1;
		uint8x2_t  u8x2;
		uint8x3_t  u8x3;
		uint8x4_t  u8x4;
		uint8x8_t  u8x8;
		uint8x16_t u8x16;
		int8x1_t  s8x1;
		int8x2_t  s8x2;
		int8x3_t  s8x3;
		int8x4_t  s8x4;
		int8x8_t  s8x8;
		int8x16_t s8x16;
		uint16x1_t  u16x1;
		uint16x2_t  u16x2;
		uint16x3_t  u16x3;
		uint16x4_t  u16x4;
		uint16x8_t  u16x8;
		uint16x16_t u16x16;
		int16x1_t  s16x1;
		int16x2_t  s16x2;
		int16x3_t  s16x3;
		int16x4_t  s16x4;
		int16x8_t  s16x8;
		int16x16_t s16x16;
		uint32x1_t  u32x1;
		uint32x2_t  u32x2;
		uint32x3_t  u32x3;
		uint32x4_t  u32x4;
		uint32x8_t  u32x8;
		uint32x16_t u32x16;
		int32x1_t  s32x1;
		int32x2_t  s32x2;
		int32x3_t  s32x3;
		int32x4_t  s32x4;
		int32x8_t  s32x8;
		int32x16_t s32x16;
		uint64x1_t  u64x1;
		uint64x2_t  u64x2;
		uint64x3_t  u64x3;
		uint64x4_t  u64x4;
		uint64x8_t  u64x8;
		uint64x16_t u64x16;
		int64x1_t  s64x1;
		int64x2_t  s64x2;
		int64x3_t  s64x3;
		int64x4_t  s64x4;
		int64x8_t  s64x8;
		int64x16_t s64x16;
		float32x1_t  f32x1;
		float32x2_t  f32x2;
		float32x3_t  f32x3;
		float32x4_t  f32x4;
		float32x8_t  f32x8;
		float32x16_t f32x16;
		float64x1_t  f64x1;
		float64x2_t  f64x2;
		float64x3_t  f64x3;
		float64x4_t  f64x4;
		float64x8_t  f64x8;
		float64x16_t f64x16;
	};

	namespace detail {
		template<class T, size_t S>
		struct VectorWorkType_ {
			typedef Vector<T, S> type;
		};


		template<class T, size_t S>
		using VectorWorkType = typename VectorWorkType_<T, S>::type;
	}
}}

#endif