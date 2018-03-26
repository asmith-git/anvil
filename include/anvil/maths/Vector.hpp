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
#include "anvil/Core/Keywords.hpp"

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

	static_assert(sizeof(VectorUnion) == (8 * 16), "VectorUnion different size than expected");

	namespace detail {

		enum {
			VEC_ADD
		};

		template<class T, size_t S, int F, class ENABLE = void>
		struct VectorOp2;

		template<class T, int F>
		struct VectorOp2<T, 8, F, typename std::enable_if<VectorOp2<T, 4, F>::optimised>::type> {
			enum { optimised = 1 };
			static ANVIL_STRONG_INLINE Vector<T, 8> implementation(const Vector<T, 8> a, const Vector<T, 8> b) throw() {
				union {
					Vector<T, 4> v4[2];
					Vector<T, 8> v8;
				} a2, b2;

				a2.v8 = a;
				b2.v8 = b;
				a2.v4[0] = VectorOp2<T, 4, F>::implementation(a2.v4[0], b2.v4[0]);
				a2.v4[1] = VectorOp2<T, 4, F>::implementation(a2.v4[1], b2.v4[1]);
				return a2.v8;
			}
		};

		template<class T, int F>
		struct VectorOp2<T, 16, F, typename std::enable_if<VectorOp2<T, 8, F>::optimised>::type> {
			enum { optimised = 1 };
			static ANVIL_STRONG_INLINE Vector<T, 16> implementation(const Vector<T, 16> a, const Vector<T, 16> b) throw() {
				union {
					Vector<T, 8> v8[2];
					Vector<T, 16> v16;
				} a2, b2;

				a2.v16 = a;
				b2.v16 = b;
				a2.v8[0] = VectorOp2<T, 8, F>::implementation(a2.v8[0], b2.v8[0]);
				a2.v8[1] = VectorOp2<T, 8, F>::implementation(a2.v8[1], b2.v8[1]);
				return a2.v16;
			}
		};

		template<class T, size_t S>
		struct VectorOp2<T, S, VEC_ADD> {
			enum { optimised = 0 };
			static ANVIL_STRONG_INLINE Vector<T, S> implementation(const Vector<T, S> a, const Vector<T, S> b) throw() {
				Vector<T, S> tmp;
				for (size_t i = 0; i < S; ++i) {
					tmp.elements[i] = a.elements[i] + b.elements[i];
				}
				return tmp;
			}
		};

		template<class T, int F>
		struct VectorOp2<T, 3, F, typename std::enable_if<VectorOp2<T, 4, F>::optimised>::type> {
			enum { optimised = 1 };
			static ANVIL_STRONG_INLINE Vector<T, 3> implementation(const Vector<T, 3> a, const Vector<T, 3> b) throw() {
				union {
					Vector<T, 4> v4;
					Vector<T, 3> v3;
				} a2, b2;

				a2.v3 = a;
				b2.v3 = b;
				a2.v4 = VectorOp2<T, 4, F>::implementation(a2.v4, b2.v4);
				return a2.v3;
			}
		};

		template<class T, int F>
		struct VectorOp2<T, 2, F, typename std::enable_if<VectorOp2<T, 4, F>::optimised>::type> {
			enum { optimised = 1 };
			static ANVIL_STRONG_INLINE Vector<T, 2> implementation(const Vector<T, 2> a, const Vector<T, 2> b) throw() {
				union {
					Vector<T, 4> v4;
					Vector<T, 2> v2;
				} a2, b2;

				a2.v2 = a;
				b2.v2 = b;
				a2.v4 = VectorOp2<T, 4, F>::implementation(a2.v4, b2.v4);
				return a2.v2;
			}
		};

#ifdef ANVIL_SSE
		template<>
		struct VectorOp2<float, 4, VEC_ADD> {
			enum { optimised = 1 };
			static ANVIL_STRONG_INLINE Vector<float, 4> implementation(const Vector<float, 4> a, const Vector<float, 4> b) throw() {
				Vector<float, 4> tmp;
				register __m128 xmm0 = _mm_load_ps(a.elements);
				const register __m128 xmm1 = _mm_load_ps(b.elements);
				xmm0 = _mm_add_ps(xmm0, xmm1);
				_mm_store_ps(tmp.elements, xmm0);
				return tmp;
			}
		};
#endif
	}
}

template<class T, size_t S>
anvil::Vector<T, S> operator+(const anvil::Vector<T, S> a, const anvil::Vector<T, S> b) {
	return anvil::detail::VectorOp2<T, S, anvil::detail::VEC_ADD>::implementation(a, b);
}

#endif