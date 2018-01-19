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