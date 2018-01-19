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
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return a + b;
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a += b;
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_SUB> {
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return a - b;
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a -= b;
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_MUL> {
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return a * b;
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a *= b;
			}
		};
		
		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_DIV> {
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return a / b;
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a /= b;
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_AND> {
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return a & b;
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a &= b;
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_OR> {
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return a | b;
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a |= b;
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_XOR> {
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return a ^ b;
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a ^= b;
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_EQ> {
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return a == b;
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a = a == b;
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_NE> {
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return a != b;
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a = a != b;
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_LT> {
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return a < b;
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a = a < b;
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_GT> {
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return a > b;
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a = a > b;
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_LE> {
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return a <= b;
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a = a <= b;
			}
		};

		template<class T, size_t S>
		struct VopDispatch<T, S, VOP_GE> {
			ANVIL_STRONG_INLINE static Vector<T, S> call(const Vector<T, S> a, const Vector<T, S> b) throw() {
				return a >= b;
			}
			ANVIL_STRONG_INLINE static void call_assignment(Vector<T, S>& a, const Vector<T, S> b) throw() {
				a = a >= b;
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
#undef ANVIL_PAD_VECTOR
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
static inline void NAME ## _scalar(const T* a, const T* b, T* c, size_t a_size) throw() {\
	detail::vector_vsv<T, VEC_LEN, VOP>(a, b, c, a_size);\
}\

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

}

#endif