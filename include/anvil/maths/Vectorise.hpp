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

#ifndef ANVIL_MATHS_VECTORISE_HPP
#define ANVIL_MATHS_VECTORISE_HPP

#include "anvil/maths/Vector.hpp"

namespace anvil {

	namespace detail {
		template<class T, size_t S, VectorOp VOP>
		struct VopDispatch;
		
		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_ADD> {
			enum { params = 2 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return a + b;
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a += b;
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_SUB> {
			enum { params = 2 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return a - b;
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a -= b;
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_MUL> {
			enum { params = 2 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return a * b;
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a *= b;
			}
		};
		
		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_DIV> {
			enum { params = 2 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return a / b;
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a /= b;
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_AND> {
			enum { params = 2 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return a & b;
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a &= b;
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_OR> {
			enum { params = 2 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return a | b;
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a |= b;
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_XOR> {
			enum { params = 2 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return a ^ b;
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a ^= b;
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_EQ> {
			enum { params = 2 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return a == b;
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a = a == b;
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_NE> {
			enum { params = 2 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return a != b;
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a = a != b;
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_LT> {
			enum { params = 2 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return a < b;
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a = a < b;
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_GT> {
			enum { params = 2 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return a > b;
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a = a > b;
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_LE> {
			enum { params = 2 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return a <= b;
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a = a <= b;
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_GE> {
			enum { params = 2 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return a >= b;
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a = a >= b;
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_MIN> {
			enum { params = 2 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return min<T,S>(a, b);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a = min<T, S>(a, b);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_MAX> {
			enum { params = 2 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return max<T, S>(a, b);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a = max<T, S>(a, b);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_POW> {
			enum { params = 2 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return pow<T, S>(a, b);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a = pow<T, S>(a, b);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_HYPOT> {
			enum { params = 2 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return hypot<T, S>(a, b);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a = hypot<T, S>(a, b);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_MOD> {
			enum { params = 2 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return mod<T, S>(a, b);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a = mod<T, S>(a, b);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_DIM> {
			enum { params = 2 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return dim<T, S>(a, b);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a = dim<T, S>(a, b);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_ATAN2> {
			enum { params = 2 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return atan2<T, S>(a, b);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a = atan2<T, S>(a, b);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_REF> {
			enum { params = 1 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a) throw() {
				return reflect<T, S>(a);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a) throw() {
				a = reflect<T, S>(a);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_PCN> {
			enum { params = 1 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a) throw() {
				return popcount<T, S>(a);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a) throw() {
				a = popcount<T, S>(a);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_EXP> {
			enum { params = 1 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a) throw() {
				return exp<T, S>(a);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a) throw() {
				a = exp<T, S>(a);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_ABS> {
			enum { params = 1 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a) throw() {
				return abs<T, S>(a);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a) throw() {
				a = abs<T, S>(a);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_LOG> {
			enum { params = 1 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a) throw() {
				return log<T, S>(a);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a) throw() {
				a = log<T, S>(a);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_LOG2> {
			enum { params = 1 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a) throw() {
				return log2<T, S>(a);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a) throw() {
				a = log2<T, S>(a);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_LOG10> {
			enum { params = 1 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a) throw() {
				return log10<T, S>(a);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a) throw() {
				a = log10<T, S>(a);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_SQRT> {
			enum { params = 1 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a) throw() {
				return sqrt<T, S>(a);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a) throw() {
				a = sqrt<T, S>(a);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_CBRT> {
			enum { params = 1 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a) throw() {
				return cbrt<T, S>(a);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a) throw() {
				a = cbrt<T, S>(a);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_NOT> {
			enum { params = 1 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a) throw() {
				return not<T, S>(a);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a) throw() {
				a = not<T, S>(a);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_COS> {
			enum { params = 1 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a) throw() {
				return cos<T, S>(a);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a) throw() {
				a = cos<T, S>(a);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_SIN> {
			enum { params = 1 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a) throw() {
				return sin<T, S>(a);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a) throw() {
				a = sin<T, S>(a);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_TAN> {
			enum { params = 1 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a) throw() {
				return tan<T, S>(a);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a) throw() {
				a = tan<T, S>(a);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_ACOS> {
			enum { params = 1 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a) throw() {
				return acos<T, S>(a);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a) throw() {
				a = acos<T, S>(a);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_ASIN> {
			enum { params = 1 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a) throw() {
				return asin<T, S>(a);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a) throw() {
				a = asin<T, S>(a);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_ATAN> {
			enum { params = 1 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a) throw() {
				return atan<T, S>(a);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a) throw() {
				a = atan<T, S>(a);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_COSH> {
			enum { params = 1 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a) throw() {
				return cosh<T, S>(a);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a) throw() {
				a = cosh<T, S>(a);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_SINH> {
			enum { params = 1 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a) throw() {
				return sinh<T, S>(a);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a) throw() {
				a = sinh<T, S>(a);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_TANH> {
			enum { params = 1 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a) throw() {
				return tanh<T, S>(a);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a) throw() {
				a = tanh<T, S>(a);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_CEIL> {
			enum { params = 1 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a) throw() {
				return ceil<T, S>(a);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a) throw() {
				a = ceil<T, S>(a);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_FLOOR> {
			enum { params = 1 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a) throw() {
				return floor<T, S>(a);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a) throw() {
				a = floor<T, S>(a);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_TRUNC> {
			enum { params = 1 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a) throw() {
				return trunc<T, S>(a);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a) throw() {
				a = trunc<T, S>(a);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_ROUND> {
			enum { params = 1 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a) throw() {
				return round<T, S>(a);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a) throw() {
				a = round<T, S>(a);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_FMA> {
			enum { params = 3 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b, const Vector<T, S> c) throw() {
				return fma<T, S>(a, b, c);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b, const Vector<T, S> c) throw() {
				a = fma<T, S>(a, b, c);
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_FMS> {
			enum { params = 3 };
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b, const Vector<T, S> c) throw() {
				return fms<T, S>(a, b, c);
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b, const Vector<T, S> c) throw() {
				a = fms<T, S>(a, b, c);
			}
		};

		template<class T, size_t VEC_LEN, VectorOp VOP>
		static void vector_vsv_(const T* a, const T* b, T* c, size_t a_size) throw() {
			typedef Vector<T, VEC_LEN> Vec;
			typedef Vector<T, 1> Sca;
			typedef VopDispatch<T, VEC_LEN, VOP> VopVec;
			typedef VopDispatch<T, 1, VOP> VopSca;

			const size_t loop = a_size / VEC_LEN;
			const size_t remainder = a_size % VEC_LEN;
			if (remainder != 0) return; //! \todo Handle trailing elements

			const Vec* const aVec = reinterpret_cast<const Vec*>(a);
			const Vec bVec = *reinterpret_cast<const Vec*>(b);
			Vec* const cVec = reinterpret_cast<Vec*>(c);

			if (c == a) {
				for (size_t i = 0; i < loop; ++i) VopVec::call_assignment(cVec[i], bVec);
				//for (size_t i = 0; i < remainder; ++i) VopSca::call_assignment(cSca[i], bSca);
			} else {
				for (size_t i = 0; i < loop; ++i) cVec[i] = VopVec::call(aVec[i], bVec);
				//for (size_t i = 0; i < remainder; ++i) cSca[i] = VopSca::call(aSca[i], bSca);
			}
		}

		template<class T, size_t VEC_LEN, VectorOp VOP>
		static void vector_vsv(const T* a, const T* b, T* c, size_t a_size) throw() {
			if (VEC_LEN == 1) {
				vector_vsv<T, VOP>(a, *b, c, a_size);
			} else {
				enum {
					LEN_2 = VEC_LEN * 2,
					LEN_4 = VEC_LEN * 4,
					LEN_8 = VEC_LEN * 8,
					LEN_16 = VEC_LEN * 16,
					BYTES = sizeof(T) * VEC_LEN
				};
				if (VopOptimised<T, LEN_16, VOP>::value && (a_size % 16) == 0) {
					T buffer[LEN_16];
					memcpy(buffer, b, BYTES);
					memcpy(buffer + VEC_LEN, b, BYTES);
					memcpy(buffer + (VEC_LEN * 2), b, BYTES);
					memcpy(buffer + (VEC_LEN * 3), b, BYTES);
					memcpy(buffer + (VEC_LEN * 4), b, BYTES);
					memcpy(buffer + (VEC_LEN * 5), b, BYTES);
					memcpy(buffer + (VEC_LEN * 6), b, BYTES);
					memcpy(buffer + (VEC_LEN * 7), b, BYTES);
					memcpy(buffer + (VEC_LEN * 8), b, BYTES);
					memcpy(buffer + (VEC_LEN * 9), b, BYTES);
					memcpy(buffer + (VEC_LEN * 10), b, BYTES);
					memcpy(buffer + (VEC_LEN * 11), b, BYTES);
					memcpy(buffer + (VEC_LEN * 12), b, BYTES);
					memcpy(buffer + (VEC_LEN * 13), b, BYTES);
					memcpy(buffer + (VEC_LEN * 14), b, BYTES);
					memcpy(buffer + (VEC_LEN * 15), b, BYTES);
					vector_vsv_<T, LEN_16, VOP>(a, buffer, c, a_size);
				} else if (VopOptimised<T, LEN_8, VOP>::value && (a_size % 8) == 0) {
					T buffer[LEN_8];
					memcpy(buffer, b, BYTES);
					memcpy(buffer + VEC_LEN, b, BYTES);
					memcpy(buffer + (VEC_LEN * 2), b, BYTES);
					memcpy(buffer + (VEC_LEN * 3), b, BYTES);
					memcpy(buffer + (VEC_LEN * 4), b, BYTES);
					memcpy(buffer + (VEC_LEN * 5), b, BYTES);
					memcpy(buffer + (VEC_LEN * 6), b, BYTES);
					memcpy(buffer + (VEC_LEN * 7), b, BYTES);
					vector_vsv_<T, LEN_8, VOP>(a, buffer, c, a_size);
				} else if (VopOptimised<T, LEN_4, VOP>::value && (a_size % 4) == 0) {
					T buffer[LEN_4];
					memcpy(buffer, b, BYTES);
					memcpy(buffer + VEC_LEN, b, BYTES);
					memcpy(buffer + (VEC_LEN * 2), b, BYTES);
					memcpy(buffer + (VEC_LEN * 3), b, BYTES);
					vector_vsv_<T, LEN_4, VOP>(a, buffer, c, a_size);
				} else if (VopOptimised<T, LEN_2, VOP>::value && (a_size % 2) == 0) {
					T buffer[LEN_2];
					memcpy(buffer, b, BYTES);
					memcpy(buffer + VEC_LEN, b, BYTES);
					vector_vsv_<T, LEN_2, VOP>(a, buffer, c, a_size);
				} else {
					vector_vsv_<T, VEC_LEN, VOP>(a, b, c, a_size);
				}
			}
		}

		template<class T, VectorOp VOP>
		static void vector_vsv(const T* a, T b, T* c, size_t a_size) throw() {
			enum { LENGTH = detail::OptimalVectorLength<T, VOP>::value };
			typedef Vector<T, LENGTH> Vec;
			typedef Vector<T, 1> Sca;
			typedef VopDispatch<T, LENGTH, VOP> VopVec;
			typedef VopDispatch<T, 1, VOP> VopSca;

			const size_t loop = a_size / LENGTH;
			const size_t remainder = a_size % LENGTH;

			const Vec* const aVec = reinterpret_cast<const Vec*>(a);
			const Vec bVec = fill<T, LENGTH>(b);
			Vec* const cVec = reinterpret_cast<Vec*>(c);

			const Sca* const aSca = reinterpret_cast<const Sca*>(aVec + loop);
			const Sca bSca = fill<T, 1>(b);
			Sca* const cSca = reinterpret_cast<Sca*>(cVec + loop);

			if (c == a) {
				for (size_t i = 0; i < loop; ++i) VopVec::call_assignment(cVec[i], bVec);
				for (size_t i = 0; i < remainder; ++i) VopSca::call_assignment(cSca[i], bSca);
			} else {
				for (size_t i = 0; i < loop; ++i) cVec[i] = VopVec::call(aVec[i], bVec);
				for (size_t i = 0; i < remainder; ++i) cSca[i] = VopSca::call(aSca[i], bSca);
			}
		}

		template<class T, VectorOp VOP>
		static void vector_vvv(const T* a, const T* b, T* c, size_t a_size) throw() {
			enum { LENGTH = detail::OptimalVectorLength<T, VOP>::value };
			typedef Vector<T, LENGTH> Vec;
			typedef Vector<T, 1> Sca;
			typedef VopDispatch<T, LENGTH, VOP> VopVec;
			typedef VopDispatch<T, 1, VOP> VopSca;

			const size_t loop = a_size / LENGTH;
			const size_t remainder = a_size % LENGTH;

			const Vec* const aVec = reinterpret_cast<const Vec*>(a);
			const Vec* const bVec = reinterpret_cast<const Vec*>(b);
			Vec* const cVec = reinterpret_cast<Vec*>(c);

			const Sca* const aSca = reinterpret_cast<const Sca*>(aVec + loop);
			const Sca* const bSca = reinterpret_cast<const Sca*>(bVec + loop);
			Sca* const cSca = reinterpret_cast<Sca*>(cVec + loop);

			if (c == a) {
				for (size_t i = 0; i < loop; ++i) VopVec::call_assignment(cVec[i], bVec[i]);
				for (size_t i = 0; i < remainder; ++i) VopSca::call_assignment(cSca[i], bSca[i]);
			} else {
				for (size_t i = 0; i < loop; ++i) cVec[i] = VopVec::call(aVec[i], bVec[i]);
				for (size_t i = 0; i < remainder; ++i) cSca[i] = VopSca::call(aSca[i], bSca[i]);
			}
		}

		template<class T, VectorOp VOP>
		static void vector_vv(const T* a, T* b, size_t a_size) throw() {
			enum { LENGTH = detail::OptimalVectorLength<T, VOP>::value };
			typedef Vector<T, LENGTH> Vec;
			typedef Vector<T, 1> Sca;
			typedef VopDispatch<T, LENGTH, VOP> VopVec;
			typedef VopDispatch<T, 1, VOP> VopSca;

			const size_t loop = a_size / LENGTH;
			const size_t remainder = a_size % LENGTH;

			const Vec* const aVec = reinterpret_cast<const Vec*>(a);
			Vec* const bVec = reinterpret_cast<Vec*>(b);

			const Sca* const aSca = reinterpret_cast<const Sca*>(aVec + loop);
			Sca* const bSca = reinterpret_cast<Sca*>(bVec + loop);

			if (b == a) {
				for (size_t i = 0; i < loop; ++i) VopVec::call_assignment(bVec[i]);
				for (size_t i = 0; i < remainder; ++i) VopSca::call_assignment(bSca[i]);
			} else {
				for (size_t i = 0; i < loop; ++i) bVec[i] = VopVec::call(aVec[i]);
				for (size_t i = 0; i < remainder; ++i) bSca[i] = VopSca::call(aSca[i]);
			}
		}
	}

#define ANVIL_VECTORISE_VVV(VOP, NAME)\
template<class T>\
static inline void NAME(const T* a, const T* b, T* c, size_t a_size) throw() {\
	detail::vector_vvv<T, VOP>(a, b, c, a_size);\
}\
template<class T>\
static inline void NAME(const T* a, const T b, T* c, size_t a_size) throw() {\
	detail::vector_vsv<T, VOP>(a, b, c, a_size);\
}\
template<class T, size_t VEC_LEN>\
static inline void NAME(const T* a, const T* b, T* c, size_t a_size) throw() {\
	detail::vector_vsv<T, VEC_LEN, VOP>(a, b, c, a_size);\
}\

#define ANVIL_VECTORISE_VV(VOP, NAME)\
template<class T>\
static inline void NAME(const T* a, T* b, size_t a_size) throw() {\
	detail::vector_vv<T, VOP>(a, b, a_size);\
}

ANVIL_VECTORISE_VVV(detail::VOP_ADD, vector_add)
ANVIL_VECTORISE_VVV(detail::VOP_SUB, vector_sub)
ANVIL_VECTORISE_VVV(detail::VOP_MUL, vector_mul)
ANVIL_VECTORISE_VVV(detail::VOP_DIV, vector_div)
ANVIL_VECTORISE_VVV(detail::VOP_AND, vector_and)
ANVIL_VECTORISE_VVV(detail::VOP_OR, vector_or)
ANVIL_VECTORISE_VVV(detail::VOP_XOR, vector_xor)
ANVIL_VECTORISE_VVV(detail::VOP_EQ, vector_eq)
ANVIL_VECTORISE_VVV(detail::VOP_NE, vector_ne)
ANVIL_VECTORISE_VVV(detail::VOP_LT, vector_lt)
ANVIL_VECTORISE_VVV(detail::VOP_GT, vector_gt)
ANVIL_VECTORISE_VVV(detail::VOP_LE, vector_le)
ANVIL_VECTORISE_VVV(detail::VOP_GE, vector_ge)
ANVIL_VECTORISE_VVV(detail::VOP_MIN, vector_min)
ANVIL_VECTORISE_VVV(detail::VOP_MAX, vector_max)
ANVIL_VECTORISE_VVV(detail::VOP_ATAN2, vector_atan2)
ANVIL_VECTORISE_VVV(detail::VOP_DIM, vector_dim)
ANVIL_VECTORISE_VVV(detail::VOP_MOD, vector_mod)
ANVIL_VECTORISE_VVV(detail::VOP_HYPOT, vector_hypot)
ANVIL_VECTORISE_VVV(detail::VOP_POW, vector_pow)

ANVIL_VECTORISE_VV(detail::VOP_PCN, vector_popcount)
ANVIL_VECTORISE_VV(detail::VOP_REF, vector_reflect)
ANVIL_VECTORISE_VV(detail::VOP_ABS, vector_abs)
ANVIL_VECTORISE_VV(detail::VOP_NOT, vector_not)
ANVIL_VECTORISE_VV(detail::VOP_TRUNC, vector_trunc)
ANVIL_VECTORISE_VV(detail::VOP_FLOOR, vector_floor)
ANVIL_VECTORISE_VV(detail::VOP_CEIL, vector_ceil)
ANVIL_VECTORISE_VV(detail::VOP_ROUND, vector_round)
ANVIL_VECTORISE_VV(detail::VOP_SQRT, vector_sqrt)
ANVIL_VECTORISE_VV(detail::VOP_CBRT, vector_cbrt)
ANVIL_VECTORISE_VV(detail::VOP_EXP, vector_exp)
ANVIL_VECTORISE_VV(detail::VOP_LOG, vector_log)
ANVIL_VECTORISE_VV(detail::VOP_LOG2, vector_log2)
ANVIL_VECTORISE_VV(detail::VOP_LOG10, vector_log10)
ANVIL_VECTORISE_VV(detail::VOP_COS, vector_cos)
ANVIL_VECTORISE_VV(detail::VOP_SIN, vector_sin)
ANVIL_VECTORISE_VV(detail::VOP_TAN, vector_tan)
ANVIL_VECTORISE_VV(detail::VOP_ACOS, vector_acos)
ANVIL_VECTORISE_VV(detail::VOP_ASIN, vector_asin)
ANVIL_VECTORISE_VV(detail::VOP_ATAN, vector_aton)
ANVIL_VECTORISE_VV(detail::VOP_COSH, vector_cosh)
ANVIL_VECTORISE_VV(detail::VOP_SINH, vector_sinh)
ANVIL_VECTORISE_VV(detail::VOP_TANH, vector_tanh)

}

#endif