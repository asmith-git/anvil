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

		ANVIL_STRONG_INLINE T& ANVIL_VECTOR_CALL  operator[](const size_t a_index) throw() {
			return elements[a_index];
		}

		ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL  operator[](const size_t a_index) const throw() {
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

		ANVIL_STRONG_INLINE type& ANVIL_VECTOR_CALL  operator[](const size_t a_index) throw() {
			return elements[a_index];
		}

		ANVIL_STRONG_INLINE type ANVIL_VECTOR_CALL  operator[](const size_t a_index) const throw() {
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

		ANVIL_STRONG_INLINE type& ANVIL_VECTOR_CALL  operator[](const size_t a_index) throw() {
			return elements[a_index];
		}

		ANVIL_STRONG_INLINE type ANVIL_VECTOR_CALL  operator[](const size_t a_index) const throw() {
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

		ANVIL_STRONG_INLINE type& ANVIL_VECTOR_CALL  operator[](const size_t a_index) throw() {
			return elements[a_index];
		}

		ANVIL_STRONG_INLINE type ANVIL_VECTOR_CALL  operator[](const size_t a_index) const throw() {
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

		ANVIL_STRONG_INLINE type& ANVIL_VECTOR_CALL  operator[](const size_t a_index) throw() {
			return elements[a_index];
		}

		ANVIL_STRONG_INLINE type ANVIL_VECTOR_CALL  operator[](const size_t a_index) const throw() {
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
			VEC_ADD,
			VEC_SUB,
			VEC_MUL,
			VEC_DIV,
			VEC_AND,
			VEC_OR,
			VEC_XOR
		};

		template<class T, int F>
		struct VectorOp2_;

		template<class T, int F>
		struct VectorOp2 {
			enum {
				optimised = VectorOp2_<T,F>::optimised,
				alignment = VectorOp2_<T,F>::alignment
			};

			static void ANVIL_VECTOR_CALL implementation(const float* a, const float* b, float* c, size_t a_count) throw() {
				const intptr_t a_align(reinterpret_cast<intptr_t>(a) & (alignment-1));
				const intptr_t b_align(reinterpret_cast<intptr_t>(b) & (alignment-1));
				const intptr_t c_align(reinterpret_cast<intptr_t>(c) & (alignment-1));

				if (a_align == b_align && a_align == c_align) {
					for (size_t i = 0; i < a_align; ++i) {
						c[i] = a[i] + b[i];
					}

					a_count -= a_align;

					const size_t loops = a_count >> 3;
					size_t remainder = a_count & 7;
					const float* const loop_end = a + loops;

					while (a != loop_end) {
						VectorOp2_<T, F>::implementation8(a, b, c);
						a += 8;
						b += 8;
						c += 8;
					}

					if (remainder >= 4) {
						remainder -= 4;
						VectorOp2_<T, F>::implementation4(a, b, c);
						a += 4;
						b += 4;
						c += 4;
					}
				} else {
					const size_t loops = a_count >> 3;
					const size_t remainder = a_count & 7;
					const float* const loop_end = a + loops;

					while (a != loop_end) {
						VectorOp2_<T, F>::implementation8u(a, b, c);
						a += 8;
						b += 8;
						c += 8;
					}

					if (remainder >= 4) {
						remainder -= 4;
						VectorOp2_<T, F>::implementation4u(a, b, c);
						a += 4;
						b += 4;
						c += 4;
					}
				}

				for (size_t i = 0; i < remainder; ++i) {
					c[i] = a[i] + b[i];
				}
			}

			static ANVIL_STRONG_INLINE Vector<T, 16> ANVIL_VECTOR_CALL implementation(const Vector<T, 16> a, const Vector<T, 16> b) throw() {
				Vector<T, 16> tmp;
				VectorOp2_<T,F>::implementation8(a.elements, b.elements, tmp.elements);
				VectorOp2_<T,F>::implementation8(a.elements + 8, b.elements + 8, tmp.elements + 8);
				return tmp;
			}

			static ANVIL_STRONG_INLINE Vector<T, 8> ANVIL_VECTOR_CALL implementation(const Vector<T, 8> a, const Vector<T, 8> b) throw() {
				Vector<T, 8> tmp;
				VectorOp2_<T, F>::implementation8(a.elements, b.elements, tmp.elements);
				return tmp;
			}

			static ANVIL_STRONG_INLINE Vector<T, 4> ANVIL_VECTOR_CALL implementation(const Vector<T, 4> a, const Vector<T, 4> b) throw() {
				Vector<T, 4> tmp;
				VectorOp2_<T, F>::implementation4(a.elements, b.elements, tmp.elements);
				return tmp;
			}

			static ANVIL_STRONG_INLINE Vector<T, 3> ANVIL_VECTOR_CALL implementation(const Vector<T, 3> a, const Vector<T, 3> b) throw() {
				union {
					Vector<T, 4> native;
					Vector<T, 3> in;
				} a2, b2;
				a2.in = a;
				b2.in = b;
				VectorOp2_<T, F>::implementation4(a2.native.elements, b2.native.elements, a2.native.elements);
				return a2.in;
			}

			static ANVIL_STRONG_INLINE Vector<T, 2> ANVIL_VECTOR_CALL implementation(const Vector<T, 2> a, const Vector<T, 2> b) throw() {
				union {
					Vector<T, 4> native;
					Vector<T, 2> in;
				} a2, b2;
				VectorOp2_<T, F>::implementation4(a2.native.elements, b2.native.elements, a2.native.elements);
				return a2.in;
			}
		};

		template<class T>
		struct VectorOp2_<T, VEC_ADD> {
			enum {
				optimised = 0,
				alignment = 0
			};

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation4u(const T* const a, const T* b, T* const c) throw() {
				c[0] = a[0] + b[0];
				c[1] = a[1] + b[1];
				c[2] = a[2] + b[2];
				c[3] = a[3] + b[3];
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8u(const T* const a, const T* b, T* const c) throw() {
				implementation4u(a, b, c);
				implementation4u(a + 4, b + 4, c + 4);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8(const T* const a, const T* b, T* const c) throw() {
				implementation4u(a, b, c);
				implementation4u(a + 4, b + 4, c + 4);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation4(const T* const a, const T* b, T* const c) throw() {
				implementation4u(a, b, c);
			}
		};

		template<class T>
		struct VectorOp2_<T, VEC_SUB> {
			enum {
				optimised = 0,
				alignment = 0
			};

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation4u(const T* const a, const T* b, T* const c) throw() {
				c[0] = a[0] - b[0];
				c[1] = a[1] - b[1];
				c[2] = a[2] - b[2];
				c[3] = a[3] - b[3];
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8u(const T* const a, const T* b, T* const c) throw() {
				implementation4u(a, b, c);
				implementation4u(a + 4, b + 4, c + 4);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8(const T* const a, const T* b, T* const c) throw() {
				implementation4u(a, b, c);
				implementation4u(a + 4, b + 4, c + 4);
			}

			static ANVIL_STRONG_INLINE void implementation4(const T* const a, const T* b, T* const c) throw() {
				implementation4u(a, b, c);
			}
		};

		template<class T>
		struct VectorOp2_<T, VEC_MUL> {
			enum {
				optimised = 0,
				alignment = 0
			};

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation4u(const T* const a, const T* b, T* const c) throw() {
				c[0] = a[0] * b[0];
				c[1] = a[1] * b[1];
				c[2] = a[2] * b[2];
				c[3] = a[3] * b[3];
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8u(const T* const a, const T* b, T* const c) throw() {
				implementation4u(a, b, c);
				implementation4u(a + 4, b + 4, c + 4);
			}

			static ANVIL_STRONG_INLINE void implementation8(const T* const a, const T* b, T* const c) throw() {
				implementation4u(a, b, c);
				implementation4u(a + 4, b + 4, c + 4);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation4(const T* const a, const T* b, T* const c) throw() {
				implementation4u(a, b, c);
			}
		};

		template<class T>
		struct VectorOp2_<T, VEC_DIV> {
			enum {
				optimised = 0,
				alignment = 0
			};

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation4u(const T* const a, const T* b, T* const c) throw() {
				c[0] = a[0] / b[0];
				c[1] = a[1] / b[1];
				c[2] = a[2] / b[2];
				c[3] = a[3] / b[3];
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8u(const T* const a, const T* b, T* const c) throw() {
				implementation4u(a, b, c);
				implementation4u(a + 4, b + 4, c + 4);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8(const T* const a, const T* b, T* const c) throw() {
				implementation4u(a, b, c);
				implementation4u(a + 4, b + 4, c + 4);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation4(const T* const a, const T* b, T* const c) throw() {
				implementation4u(a, b, c);
			}
		};

		template<class T>
		struct VectorOp2_<T, VEC_AND> {
			enum {
				optimised = 0,
				alignment = 0
			};

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation4u(const T* const a, const T* b, T* const c) throw() {
				c[0] = a[0] & b[0];
				c[1] = a[1] & b[1];
				c[2] = a[2] & b[2];
				c[3] = a[3] & b[3];
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8u(const T* const a, const T* b, T* const c) throw() {
				implementation4u(a, b, c);
				implementation4u(a + 4, b + 4, c + 4);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8(const T* const a, const T* b, T* const c) throw() {
				implementation4u(a, b, c);
				implementation4u(a + 4, b + 4, c + 4);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation4(const T* const a, const T* b, T* const c) throw() {
				implementation4u(a, b, c);
			}
		};

		template<class T>
		struct VectorOp2_<T, VEC_OR> {
			enum {
				optimised = 0,
				alignment = 0
			};

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation4u(const T* const a, const T* b, T* const c) throw() {
				c[0] = a[0] | b[0];
				c[1] = a[1] | b[1];
				c[2] = a[2] | b[2];
				c[3] = a[3] | b[3];
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8u(const T* const a, const T* b, T* const c) throw() {
				implementation4u(a, b, c);
				implementation4u(a + 4, b + 4, c + 4);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8(const T* const a, const T* b, T* const c) throw() {
				implementation4u(a, b, c);
				implementation4u(a + 4, b + 4, c + 4);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation4(const T* const a, const T* b, T* const c) throw() {
				implementation4u(a, b, c);
			}
		};

		template<class T>
		struct VectorOp2_<T, VEC_XOR> {
			enum {
				optimised = 0,
				alignment = 0
			};

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation4u(const T* const a, const T* b, T* const c) throw() {
				c[0] = a[0] ^ b[0];
				c[1] = a[1] ^ b[1];
				c[2] = a[2] ^ b[2];
				c[3] = a[3] ^ b[3];
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8u(const T* const a, const T* b, T* const c) throw() {
				implementation4u(a, b, c);
				implementation4u(a + 4, b + 4, c + 4);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8(const T* const a, const T* b, T* const c) throw() {
				implementation4u(a, b, c);
				implementation4u(a + 4, b + 4, c + 4);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation4(const T* const a, const T* b, T* const c) throw() {
				implementation4u(a, b, c);
			}
		};

#ifdef ANVIL_SSE
		template<>
		struct VectorOp2_<float, VEC_ADD> {
#ifdef ANVIL_AVX
			enum {
				optimised = 1,
				alignment = 32
			};

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8(const float* const a, const float* b, float* const c) throw() {
				register __m256 xmm0 = _mm256_load_ps(a);
				register __m256 xmm1 = _mm256_load_ps(b);
				xmm0 = _mm256_add_ps(xmm0, xmm1);
				_mm256_store_ps(c, xmm0);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8u(const float* const a, const float* b, float* const c) throw() {
				register __m256 xmm0 = _mm256_loadu_ps(a);
				register __m256 xmm1 = _mm256_loadu_ps(b);
				xmm0 = _mm256_add_ps(xmm0, xmm1);
				_mm256_storeu_ps(c, xmm0);
			}
#else
			enum {
				optimised = 1,
				alignment = 16
			};

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8(const float* const a, const float* b, float* const c) throw() {
				register __m128 xmm0 = _mm_load_ps(a);
				const register __m128 xmm1 = _mm_load_ps(b);
				xmm0 = _mm_add_ps(xmm0, xmm1);
				_mm_store_ps(c, xmm0);
				register __m128 xmm2 = _mm_load_ps(a + 4);
				const register __m128 xmm3 = _mm_load_ps(b + 4);
				xmm2 = _mm_add_ps(xmm2, xmm3);
				_mm_store_ps(c + 4, xmm2);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8u(const float* const a, const float* b, float* const c) throw() {
				register __m128 xmm0 = _mm_loadu_ps(a);
				const register __m128 xmm1 = _mm_loadu_ps(b);
				xmm0 = _mm_add_ps(xmm0, xmm1);
				_mm_storeu_ps(c, xmm0);
				register __m128 xmm2 = _mm_loadu_ps(a + 4);
				const register __m128 xmm3 = _mm_loadu_ps(b + 4);
				xmm2 = _mm_add_ps(xmm2, xmm3);
				_mm_storeu_ps(c + 4, xmm2);
			}
#endif
			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation4(const float* const a, const float* b, float* const c) throw() {
				register __m128 xmm0 = _mm_load_ps(a);
				const register __m128 xmm1 = _mm_load_ps(b);
				xmm0 = _mm_add_ps(xmm0, xmm1);
				_mm_store_ps(c, xmm0);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation4u(const float* const a, const float* b, float* const c) throw() {
				register __m128 xmm0 = _mm_loadu_ps(a);
				const register __m128 xmm1 = _mm_loadu_ps(b);
				xmm0 = _mm_add_ps(xmm0, xmm1);
				_mm_storeu_ps(c, xmm0);
			}
		};

		template<>
		struct VectorOp2_<float, VEC_SUB> {
#ifdef ANVIL_AVX
			enum {
				optimised = 1,
				alignment = 32
			};

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8(const float* const a, const float* b, float* const c) throw() {
				register __m256 xmm0 = _mm256_load_ps(a);
				register __m256 xmm1 = _mm256_load_ps(b);
				xmm0 = _mm256_sub_ps(xmm0, xmm1);
				_mm256_store_ps(c, xmm0);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8u(const float* const a, const float* b, float* const c) throw() {
				register __m256 xmm0 = _mm256_loadu_ps(a);
				register __m256 xmm1 = _mm256_loadu_ps(b);
				xmm0 = _mm256_sub_ps(xmm0, xmm1);
				_mm256_storeu_ps(c, xmm0);
			}
#else
			enum {
				optimised = 1,
				alignment = 16
			};

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8(const float* const a, const float* b, float* const c) throw() {
				register __m128 xmm0 = _mm_load_ps(a);
				const register __m128 xmm1 = _mm_load_ps(b);
				xmm0 = _mm_sub_ps(xmm0, xmm1);
				_mm_store_ps(c, xmm0);
				register __m128 xmm2 = _mm_load_ps(a + 4);
				const register __m128 xmm3 = _mm_load_ps(b + 4);
				xmm2 = _mm_sub_ps(xmm2, xmm3);
				_mm_store_ps(c + 4, xmm2);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8u(const float* const a, const float* b, float* const c) throw() {
				register __m128 xmm0 = _mm_loadu_ps(a);
				const register __m128 xmm1 = _mm_loadu_ps(b);
				xmm0 = _mm_sub_ps(xmm0, xmm1);
				_mm_storeu_ps(c, xmm0);
				register __m128 xmm2 = _mm_loadu_ps(a + 4);
				const register __m128 xmm3 = _mm_loadu_ps(b + 4);
				xmm2 = _mm_sub_ps(xmm2, xmm3);
				_mm_storeu_ps(c + 4, xmm2);
			}
#endif
			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation4(const float* const a, const float* b, float* const c) throw() {
				register __m128 xmm0 = _mm_load_ps(a);
				const register __m128 xmm1 = _mm_load_ps(b);
				xmm0 = _mm_sub_ps(xmm0, xmm1);
				_mm_store_ps(c, xmm0);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation4u(const float* const a, const float* b, float* const c) throw() {
				register __m128 xmm0 = _mm_loadu_ps(a);
				const register __m128 xmm1 = _mm_loadu_ps(b);
				xmm0 = _mm_sub_ps(xmm0, xmm1);
				_mm_storeu_ps(c, xmm0);
			}
		};


		template<>
		struct VectorOp2_<float, VEC_MUL> {
#ifdef ANVIL_AVX
			enum {
				optimised = 1,
				alignment = 32
			};

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8(const float* const a, const float* b, float* const c) throw() {
				register __m256 xmm0 = _mm256_load_ps(a);
				register __m256 xmm1 = _mm256_load_ps(b);
				xmm0 = _mm256_mul_ps(xmm0, xmm1);
				_mm256_store_ps(c, xmm0);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8u(const float* const a, const float* b, float* const c) throw() {
				register __m256 xmm0 = _mm256_loadu_ps(a);
				register __m256 xmm1 = _mm256_loadu_ps(b);
				xmm0 = _mm256_mul_ps(xmm0, xmm1);
				_mm256_storeu_ps(c, xmm0);
			}
#else
			enum {
				optimised = 1,
				alignment = 16
			};

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8(const float* const a, const float* b, float* const c) throw() {
				register __m128 xmm0 = _mm_load_ps(a);
				const register __m128 xmm1 = _mm_load_ps(b);
				xmm0 = _mm_mul_ps(xmm0, xmm1);
				_mm_store_ps(c, xmm0);
				register __m128 xmm2 = _mm_load_ps(a + 4);
				const register __m128 xmm3 = _mm_load_ps(b + 4);
				xmm2 = _mm_mul_ps(xmm2, xmm3);
				_mm_store_ps(c + 4, xmm2);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8u(const float* const a, const float* b, float* const c) throw() {
				register __m128 xmm0 = _mm_loadu_ps(a);
				const register __m128 xmm1 = _mm_loadu_ps(b);
				xmm0 = _mm_mul_ps(xmm0, xmm1);
				_mm_storeu_ps(c, xmm0);
				register __m128 xmm2 = _mm_loadu_ps(a + 4);
				const register __m128 xmm3 = _mm_loadu_ps(b + 4);
				xmm2 = _mm_mul_ps(xmm2, xmm3);
				_mm_storeu_ps(c + 4, xmm2);
			}
#endif
			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation4(const float* const a, const float* b, float* const c) throw() {
				register __m128 xmm0 = _mm_load_ps(a);
				const register __m128 xmm1 = _mm_load_ps(b);
				xmm0 = _mm_mul_ps(xmm0, xmm1);
				_mm_store_ps(c, xmm0);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation4u(const float* const a, const float* b, float* const c) throw() {
				register __m128 xmm0 = _mm_loadu_ps(a);
				const register __m128 xmm1 = _mm_loadu_ps(b);
				xmm0 = _mm_mul_ps(xmm0, xmm1);
				_mm_storeu_ps(c, xmm0);
			}
		};

		template<>
		struct VectorOp2_<float, VEC_DIV> {
#ifdef ANVIL_AVX
			enum {
				optimised = 1,
				alignment = 32
			};

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8(const float* const a, const float* b, float* const c) throw() {
				register __m256 xmm0 = _mm256_load_ps(a);
				register __m256 xmm1 = _mm256_load_ps(b);
				xmm0 = _mm256_div_ps(xmm0, xmm1);
				_mm256_store_ps(c, xmm0);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8u(const float* const a, const float* b, float* const c) throw() {
				register __m256 xmm0 = _mm256_loadu_ps(a);
				register __m256 xmm1 = _mm256_loadu_ps(b);
				xmm0 = _mm256_div_ps(xmm0, xmm1);
				_mm256_storeu_ps(c, xmm0);
			}
#else
			enum {
				optimised = 1,
				alignment = 16
			};

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8(const float* const a, const float* b, float* const c) throw() {
				register __m128 xmm0 = _mm_load_ps(a);
				const register __m128 xmm1 = _mm_load_ps(b);
				xmm0 = _mm_div_ps(xmm0, xmm1);
				_mm_store_ps(c, xmm0);
				register __m128 xmm2 = _mm_load_ps(a + 4);
				const register __m128 xmm3 = _mm_load_ps(b + 4);
				xmm2 = _mm_div_ps(xmm2, xmm3);
				_mm_store_ps(c + 4, xmm2);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8u(const float* const a, const float* b, float* const c) throw() {
				register __m128 xmm0 = _mm_loadu_ps(a);
				const register __m128 xmm1 = _mm_loadu_ps(b);
				xmm0 = _mm_div_ps(xmm0, xmm1);
				_mm_storeu_ps(c, xmm0);
				register __m128 xmm2 = _mm_loadu_ps(a + 4);
				const register __m128 xmm3 = _mm_loadu_ps(b + 4);
				xmm2 = _mm_div_ps(xmm2, xmm3);
				_mm_storeu_ps(c + 4, xmm2);
			}
#endif
			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation4(const float* const a, const float* b, float* const c) throw() {
				register __m128 xmm0 = _mm_load_ps(a);
				const register __m128 xmm1 = _mm_load_ps(b);
				xmm0 = _mm_div_ps(xmm0, xmm1);
				_mm_store_ps(c, xmm0);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation4u(const float* const a, const float* b, float* const c) throw() {
				register __m128 xmm0 = _mm_loadu_ps(a);
				const register __m128 xmm1 = _mm_loadu_ps(b);
				xmm0 = _mm_div_ps(xmm0, xmm1);
				_mm_storeu_ps(c, xmm0);
			}
		};

		template<>
		struct VectorOp2_<float, VEC_AND> {
#ifdef ANVIL_AVX
			enum {
				optimised = 1,
				alignment = 32
			};

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8(const float* const a, const float* b, float* const c) throw() {
				register __m256 xmm0 = _mm256_load_ps(a);
				register __m256 xmm1 = _mm256_load_ps(b);
				xmm0 = _mm256_and_ps(xmm0, xmm1);
				_mm256_store_ps(c, xmm0);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8u(const float* const a, const float* b, float* const c) throw() {
				register __m256 xmm0 = _mm256_loadu_ps(a);
				register __m256 xmm1 = _mm256_loadu_ps(b);
				xmm0 = _mm256_and_ps(xmm0, xmm1);
				_mm256_storeu_ps(c, xmm0);
			}
#else
			enum {
				optimised = 1,
				alignment = 16
			};

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8(const float* const a, const float* b, float* const c) throw() {
				register __m128 xmm0 = _mm_load_ps(a);
				const register __m128 xmm1 = _mm_load_ps(b);
				xmm0 = _mm_and_ps(xmm0, xmm1);
				_mm_store_ps(c, xmm0);
				register __m128 xmm2 = _mm_load_ps(a + 4);
				const register __m128 xmm3 = _mm_load_ps(b + 4);
				xmm2 = _mm_and_ps(xmm2, xmm3);
				_mm_store_ps(c + 4, xmm2);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8u(const float* const a, const float* b, float* const c) throw() {
				register __m128 xmm0 = _mm_loadu_ps(a);
				const register __m128 xmm1 = _mm_loadu_ps(b);
				xmm0 = _mm_and_ps(xmm0, xmm1);
				_mm_storeu_ps(c, xmm0);
				register __m128 xmm2 = _mm_loadu_ps(a + 4);
				const register __m128 xmm3 = _mm_loadu_ps(b + 4);
				xmm2 = _mm_and_ps(xmm2, xmm3);
				_mm_storeu_ps(c + 4, xmm2);
			}
#endif
			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation4(const float* const a, const float* b, float* const c) throw() {
				register __m128 xmm0 = _mm_load_ps(a);
				const register __m128 xmm1 = _mm_load_ps(b);
				xmm0 = _mm_and_ps(xmm0, xmm1);
				_mm_store_ps(c, xmm0);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation4u(const float* const a, const float* b, float* const c) throw() {
				register __m128 xmm0 = _mm_loadu_ps(a);
				const register __m128 xmm1 = _mm_loadu_ps(b);
				xmm0 = _mm_and_ps(xmm0, xmm1);
				_mm_storeu_ps(c, xmm0);
			}
		};

		template<>
		struct VectorOp2_<float, VEC_OR> {
#ifdef ANVIL_AVX
			enum {
				optimised = 1,
				alignment = 32
			};

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8(const float* const a, const float* b, float* const c) throw() {
				register __m256 xmm0 = _mm256_load_ps(a);
				register __m256 xmm1 = _mm256_load_ps(b);
				xmm0 = _mm256_or_ps(xmm0, xmm1);
				_mm256_store_ps(c, xmm0);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8u(const float* const a, const float* b, float* const c) throw() {
				register __m256 xmm0 = _mm256_loadu_ps(a);
				register __m256 xmm1 = _mm256_loadu_ps(b);
				xmm0 = _mm256_or_ps(xmm0, xmm1);
				_mm256_storeu_ps(c, xmm0);
			}
#else
			enum {
				optimised = 1,
				alignment = 16
			};

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8(const float* const a, const float* b, float* const c) throw() {
				register __m128 xmm0 = _mm_load_ps(a);
				const register __m128 xmm1 = _mm_load_ps(b);
				xmm0 = _mm_or_ps(xmm0, xmm1);
				_mm_store_ps(c, xmm0);
				register __m128 xmm2 = _mm_load_ps(a + 4);
				const register __m128 xmm3 = _mm_load_ps(b + 4);
				xmm2 = _mm_or_ps(xmm2, xmm3);
				_mm_store_ps(c + 4, xmm2);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8u(const float* const a, const float* b, float* const c) throw() {
				register __m128 xmm0 = _mm_loadu_ps(a);
				const register __m128 xmm1 = _mm_loadu_ps(b);
				xmm0 = _mm_or_ps(xmm0, xmm1);
				_mm_storeu_ps(c, xmm0);
				register __m128 xmm2 = _mm_loadu_ps(a + 4);
				const register __m128 xmm3 = _mm_loadu_ps(b + 4);
				xmm2 = _mm_or_ps(xmm2, xmm3);
				_mm_storeu_ps(c + 4, xmm2);
			}
#endif
			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation4(const float* const a, const float* b, float* const c) throw() {
				register __m128 xmm0 = _mm_load_ps(a);
				const register __m128 xmm1 = _mm_load_ps(b);
				xmm0 = _mm_or_ps(xmm0, xmm1);
				_mm_store_ps(c, xmm0);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation4u(const float* const a, const float* b, float* const c) throw() {
				register __m128 xmm0 = _mm_loadu_ps(a);
				const register __m128 xmm1 = _mm_loadu_ps(b);
				xmm0 = _mm_or_ps(xmm0, xmm1);
				_mm_storeu_ps(c, xmm0);
			}
		};

		template<>
		struct VectorOp2_<float, VEC_XOR> {
#ifdef ANVIL_AVX
			enum {
				optimised = 1,
				alignment = 32
			};

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8(const float* const a, const float* b, float* const c) throw() {
				register __m256 xmm0 = _mm256_load_ps(a);
				register __m256 xmm1 = _mm256_load_ps(b);
				xmm0 = _mm256_xor_ps(xmm0, xmm1);
				_mm256_store_ps(c, xmm0);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8u(const float* const a, const float* b, float* const c) throw() {
				register __m256 xmm0 = _mm256_loadu_ps(a);
				register __m256 xmm1 = _mm256_loadu_ps(b);
				xmm0 = _mm256_xor_ps(xmm0, xmm1);
				_mm256_storeu_ps(c, xmm0);
			}
#else
			enum {
				optimised = 1,
				alignment = 16
			};

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8(const float* const a, const float* b, float* const c) throw() {
				register __m128 xmm0 = _mm_load_ps(a);
				const register __m128 xmm1 = _mm_load_ps(b);
				xmm0 = _mm_xor_ps(xmm0, xmm1);
				_mm_store_ps(c, xmm0);
				register __m128 xmm2 = _mm_load_ps(a + 4);
				const register __m128 xmm3 = _mm_load_ps(b + 4);
				xmm2 = _mm_xor_ps(xmm2, xmm3);
				_mm_store_ps(c + 4, xmm2);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation8u(const float* const a, const float* b, float* const c) throw() {
				register __m128 xmm0 = _mm_loadu_ps(a);
				const register __m128 xmm1 = _mm_loadu_ps(b);
				xmm0 = _mm_xor_ps(xmm0, xmm1);
				_mm_storeu_ps(c, xmm0);
				register __m128 xmm2 = _mm_loadu_ps(a + 4);
				const register __m128 xmm3 = _mm_loadu_ps(b + 4);
				xmm2 = _mm_xor_ps(xmm2, xmm3);
				_mm_storeu_ps(c + 4, xmm2);
			}
#endif
			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation4(const float* const a, const float* b, float* const c) throw() {
				register __m128 xmm0 = _mm_load_ps(a);
				const register __m128 xmm1 = _mm_load_ps(b);
				xmm0 = _mm_xor_ps(xmm0, xmm1);
				_mm_store_ps(c, xmm0);
			}

			static ANVIL_STRONG_INLINE void ANVIL_VECTOR_CALL implementation4u(const float* const a, const float* b, float* const c) throw() {
				register __m128 xmm0 = _mm_loadu_ps(a);
				const register __m128 xmm1 = _mm_loadu_ps(b);
				xmm0 = _mm_xor_ps(xmm0, xmm1);
				_mm_storeu_ps(c, xmm0);
			}
		};
#endif
	}
}

template<class T, size_t S>
ANVIL_STRONG_INLINE anvil::Vector<T, S> operator+(const anvil::Vector<T, S> a, const anvil::Vector<T, S> b) {
	return anvil::detail::VectorOp2<T, anvil::detail::VEC_ADD>::implementation(a, b);
}

template<class T, size_t S>
ANVIL_STRONG_INLINE anvil::Vector<T, S>& operator+=(anvil::Vector<T, S>& a, const anvil::Vector<T, S> b) {
	a = anvil::detail::VectorOp2<T, anvil::detail::VEC_ADD>::implementation(a, b);
	return a;
}

template<class T, size_t S>
ANVIL_STRONG_INLINE anvil::Vector<T, S> operator-(const anvil::Vector<T, S> a, const anvil::Vector<T, S> b) {
	return anvil::detail::VectorOp2<T, anvil::detail::VEC_SUB>::implementation(a, b);
}

template<class T, size_t S>
ANVIL_STRONG_INLINE anvil::Vector<T, S>& operator-=(anvil::Vector<T, S>& a, const anvil::Vector<T, S> b) {
	a = anvil::detail::VectorOp2<T, anvil::detail::VEC_SUB>::implementation(a, b);
	return a;
}

template<class T, size_t S>
ANVIL_STRONG_INLINE anvil::Vector<T, S> operator*(const anvil::Vector<T, S> a, const anvil::Vector<T, S> b) {
	return anvil::detail::VectorOp2<T, anvil::detail::VEC_MUL>::implementation(a, b);
}

template<class T, size_t S>
ANVIL_STRONG_INLINE anvil::Vector<T, S>& operator*=(anvil::Vector<T, S>& a, const anvil::Vector<T, S> b) {
	a = anvil::detail::VectorOp2<T, anvil::detail::VEC_MUL>::implementation(a, b);
	return a;
}

template<class T, size_t S>
ANVIL_STRONG_INLINE anvil::Vector<T, S> operator/(const anvil::Vector<T, S> a, const anvil::Vector<T, S> b) {
	return anvil::detail::VectorOp2<T, anvil::detail::VEC_DIV>::implementation(a, b);
}

template<class T, size_t S>
ANVIL_STRONG_INLINE anvil::Vector<T, S>& operator/=(anvil::Vector<T, S>& a, const anvil::Vector<T, S> b) {
	a = anvil::detail::VectorOp2<T, anvil::detail::VEC_DIV>::implementation(a, b);
	return a;
}

template<class T, size_t S>
ANVIL_STRONG_INLINE anvil::Vector<T, S> operator&(const anvil::Vector<T, S> a, const anvil::Vector<T, S> b) {
	return anvil::detail::VectorOp2<T, anvil::detail::VEC_AND>::implementation(a, b);
}

template<class T, size_t S>
ANVIL_STRONG_INLINE anvil::Vector<T, S>& operator&=(anvil::Vector<T, S>& a, const anvil::Vector<T, S> b) {
	a = anvil::detail::VectorOp2<T, anvil::detail::VEC_AND>::implementation(a, b);
	return a;
}

template<class T, size_t S>
ANVIL_STRONG_INLINE anvil::Vector<T, S> operator|(const anvil::Vector<T, S> a, const anvil::Vector<T, S> b) {
	return anvil::detail::VectorOp2<T, anvil::detail::VEC_OR>::implementation(a, b);
}

template<class T, size_t S>
ANVIL_STRONG_INLINE anvil::Vector<T, S>& operator|=(anvil::Vector<T, S>& a, const anvil::Vector<T, S> b) {
	a = anvil::detail::VectorOp2<T, anvil::detail::VEC_OR>::implementation(a, b);
	return a;
}

template<class T, size_t S>
ANVIL_STRONG_INLINE anvil::Vector<T, S> operator^(const anvil::Vector<T, S> a, const anvil::Vector<T, S> b) {
	return anvil::detail::VectorOp2<T, anvil::detail::VEC_XOR>::implementation(a, b);
}

template<class T, size_t S>
ANVIL_STRONG_INLINE anvil::Vector<T, S>& operator^=(anvil::Vector<T, S>& a, const anvil::Vector<T, S> b) {
	a = anvil::detail::VectorOp2<T, anvil::detail::VEC_XOR>::implementation(a, b);
	return a;
}

#endif