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

#include <array>
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
			uint8_t buffer[sizeof(Vector<T, size>)];
			Vector<T, size>& tmp = *reinterpret_cast<Vector<T, size>*>(buffer);
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
			uint8_t buffer[sizeof(Vector<T, size>)];
			Vector<T, size>& tmp = *reinterpret_cast<Vector<T, size>*>(buffer);
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

		template<class T, size_t S>
		struct OptimisedVector {
			typedef std::array<T, S> type;
			enum { optimised = 0 };


			static ANVIL_STRONG_INLINE type ANVIL_VECTOR_CALL load(const Vector<T, S> aVector) throw() {
				union {
					std::array<T, S> a;
					Vector<T, S> v;
				};

				v = aVector;
				return a;
			}

			static ANVIL_STRONG_INLINE Vector<T, S> ANVIL_VECTOR_CALL store(const register type aValue) throw() {
				union {
					std::array<T, S> a;
					Vector<T, S> v;
				};

				a = aValue;
				return v;
			}
		};

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
			VEC_ATANH,
			VEC_MIN,
			VEC_MAX,

			VEC_LOG,
			VEC_LOG2,
			VEC_LOG10,
			VEC_ABS,
			VEC_EXP,
			VEC_FLOOR,
			VEC_CEIL,
			VEC_ROUND,

			VEC_CMPEQ,
			VEC_CMPNE,
			VEC_CMPLT,
			VEC_CMPGT,
			VEC_CMPLE,
			VEC_CMPGE,

			VEC_MOD,
			VEC_ATAN2,
			VEC_POW,
			VEC_HYPOT,
		};

		template<class T, VectorOperationID ID, class T2 = T, size_t S = 1>
		struct PrimativeVectorOperation;

		template<class T>
		struct PrimativeVectorOperation<T, VEC_ADD> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a, const T b) {
				return a + b;
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_SUB> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a, const T b) {
				return a - b;
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_MUL> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a, const T b) {
				return a * b;
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_DIV> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a, const T b) {
				return a / b;
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_AND> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a, const T b) {
				return a & b;
			}
		};

		template<>
		struct PrimativeVectorOperation<float, VEC_AND> {
			static ANVIL_STRONG_INLINE float ANVIL_VECTOR_CALL implementation(const float a, const float b) {
				union {
					float f;
					uint32_t u;
				} a2, b2;
				a2.f = a;
				b2.f = b;
				a2.u &= b2.u;
				return a2.f;
			}
		};

		template<>
		struct PrimativeVectorOperation<double, VEC_AND> {
			static ANVIL_STRONG_INLINE double ANVIL_VECTOR_CALL implementation(const double a, const double b) {
				union {
					double f;
					uint64_t u;
				} a2, b2;
				a2.f = a;
				b2.f = b;
				a2.u &= b2.u;
				return a2.f;
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_OR> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a, const T b) {
				return a | b;
			}
		};

		template<>
		struct PrimativeVectorOperation<float, VEC_OR> {
			static ANVIL_STRONG_INLINE float ANVIL_VECTOR_CALL implementation(const float a, const float b) {
				union {
					float f;
					uint32_t u;
				} a2, b2;
				a2.f = a;
				b2.f = b;
				a2.u |= b2.u;
				return a2.f;
			}
		};

		template<>
		struct PrimativeVectorOperation<double, VEC_OR> {
			static ANVIL_STRONG_INLINE double ANVIL_VECTOR_CALL implementation(const double a, const double b) {
				union {
					double f;
					uint64_t u;
				} a2, b2;
				a2.f = a;
				b2.f = b;
				a2.u |= b2.u;
				return a2.f;
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_XOR> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a, const T b) {
				return a ^ b;
			}
		};

		template<>
		struct PrimativeVectorOperation<float, VEC_XOR> {
			static ANVIL_STRONG_INLINE float ANVIL_VECTOR_CALL implementation(const float a, const float b) {
				union {
					float f;
					uint32_t u;
				} a2, b2;
				a2.f = a;
				b2.f = b;
				a2.u ^= b2.u;
				return a2.f;
			}
		};

		template<>
		struct PrimativeVectorOperation<double, VEC_XOR> {
			static ANVIL_STRONG_INLINE double ANVIL_VECTOR_CALL implementation(const double a, const double b) {
				union {
					double f;
					uint64_t u;
				} a2, b2;
				a2.f = a;
				b2.f = b;
				a2.u ^= b2.u;
				return a2.f;
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_FMA> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a, const T b, const T c) {
				return (a * b) + c;
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_FMS> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a, const T b, const T c) {
				return (a * b) - c;
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_SQRT> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a) {
				return std::sqrt(a);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_CBRT> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a) {
				return std::cbrt(a);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_NOT> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a) {
				return ~a;
			}
		};

		template<>
		struct PrimativeVectorOperation<float, VEC_NOT> {
			static ANVIL_STRONG_INLINE float ANVIL_VECTOR_CALL implementation(const float a) {
				union {
					float f;
					uint32_t u;
				} a2;
				a2.f = a;
				a2.u = ~a2.u;
				return a2.f;
			}
		};

		template<>
		struct PrimativeVectorOperation<double, VEC_NOT> {
			static ANVIL_STRONG_INLINE double ANVIL_VECTOR_CALL implementation(const double a) {
				union {
					double f;
					uint64_t u;
				} a2;
				a2.f = a;
				a2.u = ~a2.u;
				return a2.f;
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_COS> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a) {
				return std::cos(a);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_SIN> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a) {
				return std::sin(a);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_TAN> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a) {
				return std::tan(a);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_ACOS> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a) {
				return std::acos(a);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_ASIN> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a) {
				return std::asin(a);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_ATAN> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a) {
				return std::atan(a);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_COSH> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a) {
				return std::cosh(a);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_SINH> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a) {
				return std::sinh(a);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_TANH> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a) {
				return std::tanh(a);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_ACOSH> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a) {
				return std::acosh(a);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_ASINH> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a) {
				return std::asinh(a);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_ATANH> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a) {
				return std::atanh(a);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_MIN> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a, const T b) {
				return std::min<T>(a,b);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_MAX> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a, const T b) {
				return std::max<T>(a, b);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_LOG> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a) {
				return std::log(a);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_LOG2> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a) {
				return std::log2(a);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_LOG10> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a) {
				return std::log10(a);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_ABS> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a) {
				return std::abs(a);
			}
		};

		template<>
		struct PrimativeVectorOperation<uint8_t, VEC_ABS> {
			static ANVIL_STRONG_INLINE uint8_t ANVIL_VECTOR_CALL implementation(const uint8_t a) {
				return a;
			}
		};

		template<>
		struct PrimativeVectorOperation<uint16_t, VEC_ABS> {
			static ANVIL_STRONG_INLINE uint16_t ANVIL_VECTOR_CALL implementation(const uint16_t a) {
				return a;
			}
		};

		template<>
		struct PrimativeVectorOperation<uint32_t, VEC_ABS> {
			static ANVIL_STRONG_INLINE uint32_t ANVIL_VECTOR_CALL implementation(const uint32_t a) {
				return a;
			}
		};

		template<>
		struct PrimativeVectorOperation<uint64_t, VEC_ABS> {
			static ANVIL_STRONG_INLINE uint64_t ANVIL_VECTOR_CALL implementation(const uint64_t a) {
				return a;
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_EXP> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a) {
				return std::exp(a);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_FLOOR> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a) {
				return a;
			}
		};

		template<>
		struct PrimativeVectorOperation<uint8_t, VEC_FLOOR> {
			static ANVIL_STRONG_INLINE float ANVIL_VECTOR_CALL implementation(const float a) {
				return std::floor(a);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_CEIL> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a) {
				return a;
			}
		};

		template<>
		struct PrimativeVectorOperation<uint8_t, VEC_CEIL> {
			static ANVIL_STRONG_INLINE float ANVIL_VECTOR_CALL implementation(const float a) {
				return std::ceil(a);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_ROUND> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a) {
				return a;
			}
		};

		template<>
		struct PrimativeVectorOperation<uint8_t, VEC_ROUND> {
			static ANVIL_STRONG_INLINE float ANVIL_VECTOR_CALL implementation(const float a) {
				return std::round(a);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_CMPEQ> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a, const T b) {
				return a == b ? 
					PrimativeVectorOperation<T,VEC_NOT>::implementation(static_cast<T>(0)) : 
					static_cast<T>(0);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_CMPNE> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a, const T b) {
				return a != b ?
					PrimativeVectorOperation<T, VEC_NOT>::implementation(static_cast<T>(0)) :
					static_cast<T>(0);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_CMPLT> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a, const T b) {
				return a < b ?
					PrimativeVectorOperation<T, VEC_NOT>::implementation(static_cast<T>(0)) :
					static_cast<T>(0);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_CMPGT> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a, const T b) {
				return a > b ?
					PrimativeVectorOperation<T, VEC_NOT>::implementation(static_cast<T>(0)) :
					static_cast<T>(0);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_CMPLE> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a, const T b) {
				return a <= b ?
					PrimativeVectorOperation<T, VEC_NOT>::implementation(static_cast<T>(0)) :
					static_cast<T>(0);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_CMPGE> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a, const T b) {
				return a >= b ?
					PrimativeVectorOperation<T, VEC_NOT>::implementation(static_cast<T>(0)) :
					static_cast<T>(0);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_MOD> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a, const T b) {
				return a % b;
			}
		};

		template<>
		struct PrimativeVectorOperation<float, VEC_MOD> {
			static ANVIL_STRONG_INLINE float ANVIL_VECTOR_CALL implementation(const float a, const float b) {
				return std::fmod(a, b);
			}
		};

		template<>
		struct PrimativeVectorOperation<double, VEC_MOD> {
			static ANVIL_STRONG_INLINE double ANVIL_VECTOR_CALL implementation(const double a, const double b) {
				return std::fmod(a, b);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_ATAN2> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a, const T b) {
				return std::atan2(a,b);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_POW> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a, const T b) {
				return std::pow(a, b);
			}
		};

		template<class T>
		struct PrimativeVectorOperation<T, VEC_HYPOT> {
			static ANVIL_STRONG_INLINE T ANVIL_VECTOR_CALL implementation(const T a, const T b) {
				return std::hypot(a, b);
			}
		};

#define ANVIL_VECTOR_OP(ID)\
		template<class T, size_t S, class T2, size_t S2>\
		struct PrimativeVectorOperation<std::array<T,S>, ID, T2, S2> {\
			static std::array<T, S> ANVIL_VECTOR_CALL implementation(std::array<T, S> a) {\
				for(size_t i = 0; i < S; ++i) a[i] = PrimativeVectorOperation<T, ID>::implementation(a[i]);\
				return a;\
			}\
		};

		ANVIL_VECTOR_OP(VEC_SQRT)
		ANVIL_VECTOR_OP(VEC_CBRT)
		ANVIL_VECTOR_OP(VEC_NOT)
		ANVIL_VECTOR_OP(VEC_COS)
		ANVIL_VECTOR_OP(VEC_SIN)
		ANVIL_VECTOR_OP(VEC_TAN)
		ANVIL_VECTOR_OP(VEC_ACOS)
		ANVIL_VECTOR_OP(VEC_ASIN)
		ANVIL_VECTOR_OP(VEC_ATAN)
		ANVIL_VECTOR_OP(VEC_COSH)
		ANVIL_VECTOR_OP(VEC_SINH)
		ANVIL_VECTOR_OP(VEC_TANH)
		ANVIL_VECTOR_OP(VEC_ACOSH)
		ANVIL_VECTOR_OP(VEC_ASINH)
		ANVIL_VECTOR_OP(VEC_ATANH)
		ANVIL_VECTOR_OP(VEC_LOG)
		ANVIL_VECTOR_OP(VEC_LOG2)
		ANVIL_VECTOR_OP(VEC_LOG10)
		ANVIL_VECTOR_OP(VEC_ABS)
		ANVIL_VECTOR_OP(VEC_EXP)
		ANVIL_VECTOR_OP(VEC_FLOOR)
		ANVIL_VECTOR_OP(VEC_CEIL)
		ANVIL_VECTOR_OP(VEC_ROUND)

#undef ANVIL_VECTOR_OP

#define ANVIL_VECTOR_OP(ID)\
		template<class T, size_t S, class T2, size_t S2>\
		struct PrimativeVectorOperation<std::array<T,S>, ID, T2, S2> {\
			static std::array<T, S> ANVIL_VECTOR_CALL implementation(std::array<T, S> a, const std::array<T, S> b) {\
				for(size_t i = 0; i < S; ++i) a[i] = PrimativeVectorOperation<T, ID>::implementation(a[i], b[i]);\
				return a;\
			}\
		};

		ANVIL_VECTOR_OP(VEC_ADD)
		ANVIL_VECTOR_OP(VEC_SUB)
		ANVIL_VECTOR_OP(VEC_MUL)
		ANVIL_VECTOR_OP(VEC_DIV)
		ANVIL_VECTOR_OP(VEC_AND)
		ANVIL_VECTOR_OP(VEC_OR)
		ANVIL_VECTOR_OP(VEC_XOR)
		ANVIL_VECTOR_OP(VEC_MIN)
		ANVIL_VECTOR_OP(VEC_MAX)
		ANVIL_VECTOR_OP(VEC_CMPEQ)
		ANVIL_VECTOR_OP(VEC_CMPNE)
		ANVIL_VECTOR_OP(VEC_CMPLT)
		ANVIL_VECTOR_OP(VEC_CMPGT)
		ANVIL_VECTOR_OP(VEC_CMPLE)
		ANVIL_VECTOR_OP(VEC_CMPGE)
		ANVIL_VECTOR_OP(VEC_MOD)
		ANVIL_VECTOR_OP(VEC_ATAN2)
		ANVIL_VECTOR_OP(VEC_POW)
		ANVIL_VECTOR_OP(VEC_HYPOT)

#undef ANVIL_VECTOR_OP

#define ANVIL_VECTOR_OP(ID)\
		template<class T, size_t S, class T2, size_t S2>\
		struct PrimativeVectorOperation<std::array<T,S>, ID, T2, S2> {\
			static std::array<T, S> ANVIL_VECTOR_CALL implementation(std::array<T, S> a, const std::array<T, S> b, const std::array<T, S> c) {\
				for(size_t i = 0; i < S; ++i) a[i] = PrimativeVectorOperation<T, ID>::implementation(a[i], b[i], c[i]);\
				return a;\
			}\
		};

		ANVIL_VECTOR_OP(VEC_FMA)
		ANVIL_VECTOR_OP(VEC_FMS)

#undef ANVIL_VECTOR_OP
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

#define ANVIL_VECTOR_OP(ID, OP)\
template<class T, size_t S>\
ANVIL_STRONG_INLINE anvil::Vector<T, S> operator ## OP ## =(anvil::Vector<T, S>& a, const anvil::Vector<T, S> b) {\
	using namespace anvil::detail;\
	a = OptimisedVector<T, S>::store(\
		PrimativeVectorOperation<OptimisedVector<T, S>::type, ID, T, S>::implementation(\
			OptimisedVector<T,S>::load(a),\
			OptimisedVector<T, S>::load(b)\
		)\
	);\
	return a;\
}\
template<class T, size_t S>\
ANVIL_STRONG_INLINE typename anvil::Vector<T, S> operator ## OP (anvil::Vector<T, S> a, const anvil::Vector<T, S> b) {\
	a OP ## = b;\
	return a;\
}

ANVIL_VECTOR_OP(VEC_ADD, +)
ANVIL_VECTOR_OP(VEC_SUB, -)
ANVIL_VECTOR_OP(VEC_MUL, *)
ANVIL_VECTOR_OP(VEC_DIV, /)
ANVIL_VECTOR_OP(VEC_AND, &)
ANVIL_VECTOR_OP(VEC_OR, |)
ANVIL_VECTOR_OP(VEC_XOR, ^)
ANVIL_VECTOR_OP(VEC_MOD, %)

#undef ANVIL_VECTOR_OP

#define ANVIL_VECTOR_OP(ID, OP)\
template<class T, size_t S>\
ANVIL_STRONG_INLINE anvil::Vector<T, S> operator ## OP (anvil::Vector<T, S> a, const anvil::Vector<T, S> b) {\
	using namespace anvil::detail;\
	a = OptimisedVector<T, S>::store(\
		PrimativeVectorOperation<OptimisedVector<T, S>::type, ID, T, S>::implementation(\
			OptimisedVector<T,S>::load(a),\
			OptimisedVector<T, S>::load(b)\
		)\
	);\
	return a;\
}\

ANVIL_VECTOR_OP(VEC_CMPEQ, ==)
ANVIL_VECTOR_OP(VEC_CMPNE, !=)
ANVIL_VECTOR_OP(VEC_CMPLT, <)
ANVIL_VECTOR_OP(VEC_CMPGT, >)
ANVIL_VECTOR_OP(VEC_CMPLE, <=)
ANVIL_VECTOR_OP(VEC_CMPGT, >=)

#undef ANVIL_VECTOR_OP

#define ANVIL_VECTOR_OP(ID, OP)\
template<class T, size_t S>\
ANVIL_STRONG_INLINE anvil::Vector<T, S> operator ## OP (anvil::Vector<T, S> a) {\
	using namespace anvil::detail;\
	a = OptimisedVector<T, S>::store(\
		PrimativeVectorOperation<OptimisedVector<T, S>::type, ID, T, S>::implementation(\
			OptimisedVector<T,S>::load(a)\
		)\
	);\
	return a;\
}\

ANVIL_VECTOR_OP(VEC_NOT, ~)

#undef ANVIL_VECTOR_OP

namespace anvil {

#define ANVIL_VECTOR_OP(ID, NAME)\
	template<class T, size_t S>\
	ANVIL_STRONG_INLINE anvil::Vector<T, S> NAME(anvil::Vector<T, S> a) {\
		using namespace anvil::detail;\
		a = OptimisedVector<T, S>::store(\
			PrimativeVectorOperation<OptimisedVector<T, S>::type, ID, T, S>::implementation(\
				OptimisedVector<T,S>::load(a)\
			)\
		);\
		return a;\
	}\

	ANVIL_VECTOR_OP(VEC_SQRT, sqrt)
	ANVIL_VECTOR_OP(VEC_CBRT, cbrt)
	ANVIL_VECTOR_OP(VEC_COS, cos)
	ANVIL_VECTOR_OP(VEC_SIN, sin)
	ANVIL_VECTOR_OP(VEC_TAN, tan)
	ANVIL_VECTOR_OP(VEC_ACOS, acos)
	ANVIL_VECTOR_OP(VEC_ASIN, asin)
	ANVIL_VECTOR_OP(VEC_ATAN, atan)
	ANVIL_VECTOR_OP(VEC_COSH, cosh)
	ANVIL_VECTOR_OP(VEC_SINH, sinh)
	ANVIL_VECTOR_OP(VEC_TANH, tanh)
	ANVIL_VECTOR_OP(VEC_ACOSH, acosh)
	ANVIL_VECTOR_OP(VEC_ASINH, asinh)
	ANVIL_VECTOR_OP(VEC_ATANH, atanh)
	ANVIL_VECTOR_OP(VEC_LOG, log)
	ANVIL_VECTOR_OP(VEC_LOG2, log2)
	ANVIL_VECTOR_OP(VEC_LOG10, log10)
	ANVIL_VECTOR_OP(VEC_ABS, abs)
	ANVIL_VECTOR_OP(VEC_EXP, exp)
	ANVIL_VECTOR_OP(VEC_FLOOR, floor)
	ANVIL_VECTOR_OP(VEC_CEIL, ceil)
	ANVIL_VECTOR_OP(VEC_ROUND, round)

#undef ANVIL_VECTOR_OP

#define ANVIL_VECTOR_OP(ID, NAME)\
	template<class T, size_t S>\
	ANVIL_STRONG_INLINE anvil::Vector<T, S> NAME(anvil::Vector<T, S> a, const anvil::Vector<T, S> b) {\
		using namespace anvil::detail;\
		a = OptimisedVector<T, S>::store(\
			PrimativeVectorOperation<OptimisedVector<T, S>::type, ID, T, S>::implementation(\
				OptimisedVector<T,S>::load(a),\
				OptimisedVector<T, S>::load(b)\
			)\
		);\
		return a;\
	}\

	ANVIL_VECTOR_OP(VEC_MIN, min)
	ANVIL_VECTOR_OP(VEC_MAX, max)
	ANVIL_VECTOR_OP(VEC_ATAN2, atan2)
	ANVIL_VECTOR_OP(VEC_POW, pow)
	ANVIL_VECTOR_OP(VEC_HYPOT, hypot2)

#undef ANVIL_VECTOR_OP

#define ANVIL_VECTOR_OP(ID, NAME)\
	template<class T, size_t S>\
	ANVIL_STRONG_INLINE anvil::Vector<T, S> NAME(anvil::Vector<T, S> a, const anvil::Vector<T, S> b, const anvil::Vector<T, S> c) {\
		using namespace anvil::detail;\
		a = OptimisedVector<T, S>::store(\
			PrimativeVectorOperation<OptimisedVector<T, S>::type, ID, T, S>::implementation(\
				OptimisedVector<T,S>::load(a),\
				OptimisedVector<T, S>::load(b),\
				OptimisedVector<T, S>::load(c)\
			)\
		);\
		return a;\
	}\

	ANVIL_VECTOR_OP(VEC_FMA, fma)
	ANVIL_VECTOR_OP(VEC_FMS, fms)

#undef ANVIL_VECTOR_OP
}

#ifdef ANVIL_SSE
#include "anvil/maths/vector/SSE_float32x4.hpp"
#endif

#endif