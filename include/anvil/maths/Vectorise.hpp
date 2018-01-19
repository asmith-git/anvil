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

#define ANVIL_VECTORISE_VS(VOP, NAME, OPERATION)\
	template<class T>\
	static void NAME(T* ANVIL_RESTRICT a, const T b, size_t a_length) throw() {\
		enum { LENGTH = detail::OptimalVectorLength<T, VOP>::value };\
		detail::VectorPtr<T, LENGTH> a_;\
		a_.scalar = a;\
		Vector<T,LENGTH> scalar;\
		for(int i = 0; i < LENGTH; ++i) scalar[i] = b;\
		if (LENGTH > 1) while (a_length >= LENGTH) {\
			OPERATION(*a_.vector, scalar);\
			++a_.vector;\
			a_length -= LENGTH;\
		}\
		for (size_t i = 0; i < a_length; ++i) {\
			OPERATION(*a_.scalar, b);\
			++a_.scalar;\
		}\
	}

#define ANVIL_VECTORISE_VV(VOP, NAME, OPERATION)\
	ANVIL_VECTORISE_VS(VOP, NAME, OPERATION)\
	template<class T>\
	static void NAME(T* ANVIL_RESTRICT a, const T* ANVIL_RESTRICT b, size_t a_length) throw() {\
		enum { LENGTH = detail::OptimalVectorLength<T, VOP>::value };\
		detail::VectorPtr<T, LENGTH> a_;\
		detail::VectorPtr<T, LENGTH> b_;\
		a_.scalar = a;\
		b_.scalar = const_cast<T*>(b);\
		if (LENGTH > 1) while (a_length >= LENGTH) {\
			OPERATION(*a_.vector, *b_.vector);\
			++a_.vector;\
			++b_.vector;\
			a_length -= LENGTH;\
		}\
		for (size_t i = 0; i < a_length; ++i) {\
			OPERATION(*a_.scalar, *b_.scalar);\
			++a_.scalar;\
			++b_.scalar;\
		}\
	}

#define ANVIL_VECTORISE_VSV(VOP, NAME, OPERATION)\
	template<class T>\
	static void NAME(const T* ANVIL_RESTRICT a, const T b, T* ANVIL_RESTRICT c, size_t a_length) throw() {\
		enum { LENGTH = detail::OptimalVectorLength<T, VOP>::value };\
		if (a == c) {\
			NAME<T>(c, b, a_length);\
			return;\
		}\
		detail::VectorPtr<T, LENGTH> a_;\
		detail::VectorPtr<T, LENGTH> c_;\
		a_.scalar = const_cast<T*>(a);\
		c_.scalar = c;\
		Vector<T,LENGTH> scalar;\
		for(int i = 0; i < LENGTH; ++i) scalar[i] = b;\
		if (LENGTH > 1) while (a_length >= LENGTH) {\
			*c_.vector = OPERATION(*a_.vector, scalar);\
			++a_.vector;\
			++c_.vector;\
			a_length -= LENGTH;\
		}\
		for (size_t i = 0; i < a_length; ++i) {\
			*c_.scalar = OPERATION(*a_.scalar, b);\
			++a_.scalar;\
			++c_.scalar;\
		}\
	}

#define ANVIL_VECTORISE_VVV(VOP, NAME, OPERATION, OPERATION2)\
	ANVIL_VECTORISE_VV(VOP, NAME, OPERATION2)\
	ANVIL_VECTORISE_VSV(VOP, NAME,OPERATION)\
	template<class T>\
	static void NAME(const T* ANVIL_RESTRICT a, const T* ANVIL_RESTRICT b, T* ANVIL_RESTRICT c, size_t a_length) throw() {\
		enum { LENGTH = detail::OptimalVectorLength<T, VOP>::value };\
		if (a == c) {\
			NAME<T>(c, b, a_length);\
			return;\
		}\
		detail::VectorPtr<T, LENGTH> a_;\
		detail::VectorPtr<T, LENGTH> b_;\
		detail::VectorPtr<T, LENGTH> c_;\
		a_.scalar = const_cast<T*>(a);\
		b_.scalar = const_cast<T*>(b);\
		c_.scalar = c;\
		if (LENGTH > 1) while (a_length >= LENGTH) {\
			*c_.vector = OPERATION(*a_.vector, *b_.vector);\
			++a_.vector;\
			++b_.vector;\
			++c_.vector;\
			a_length -= LENGTH;\
		}\
		for (size_t i = 0; i < a_length; ++i) {\
			*c_.scalar = OPERATION(*a_.scalar, *b_.scalar);\
			++a_.scalar;\
			++b_.scalar;\
			++c_.scalar;\
		}\
	}

#undef ANVIL_VECTOR_OP
#undef ANVIL_VECTOR_OP2
#define ANVIL_VECTOR_OP(X,Y) X + Y
#define ANVIL_VECTOR_OP2(X, Y) X += Y
ANVIL_VECTORISE_VVV(detail::VOP_ADD, vector_add, ANVIL_VECTOR_OP, ANVIL_VECTOR_OP2)

#undef ANVIL_VECTOR_OP
#undef ANVIL_VECTOR_OP2
#define ANVIL_VECTOR_OP(X,Y) X - Y
#define ANVIL_VECTOR_OP2(X, Y) X -= Y
ANVIL_VECTORISE_VVV(detail::VOP_SUB, vector_sub, ANVIL_VECTOR_OP, ANVIL_VECTOR_OP2)

#undef ANVIL_VECTOR_OP
#undef ANVIL_VECTOR_OP2
#define ANVIL_VECTOR_OP(X,Y) X * Y
#define ANVIL_VECTOR_OP2(X, Y) X *= Y
ANVIL_VECTORISE_VVV(detail::VOP_MUL, vector_mul, ANVIL_VECTOR_OP, ANVIL_VECTOR_OP2)

#undef ANVIL_VECTOR_OP
#undef ANVIL_VECTOR_OP2
#define ANVIL_VECTOR_OP(X,Y) X / Y
#define ANVIL_VECTOR_OP2(X, Y) X /= Y
ANVIL_VECTORISE_VVV(detail::VOP_DIV, vector_div, ANVIL_VECTOR_OP, ANVIL_VECTOR_OP2)

#undef ANVIL_VECTOR_OP
#undef ANVIL_VECTOR_OP2
#define ANVIL_VECTOR_OP(X,Y) X & Y
#define ANVIL_VECTOR_OP2(X, Y) X &= Y
ANVIL_VECTORISE_VVV(detail::VOP_AND, vector_and, ANVIL_VECTOR_OP, ANVIL_VECTOR_OP2)

#undef ANVIL_VECTOR_OP
#undef ANVIL_VECTOR_OP2
#define ANVIL_VECTOR_OP(X,Y) X | Y
#define ANVIL_VECTOR_OP2(X, Y) X |= Y
ANVIL_VECTORISE_VVV(detail::VOP_OR, vector_or, ANVIL_VECTOR_OP, ANVIL_VECTOR_OP2)

#undef ANVIL_VECTOR_OP
#undef ANVIL_VECTOR_OP2
#define ANVIL_VECTOR_OP(X,Y) X ^ Y
#define ANVIL_VECTOR_OP2(X, Y) X ^= Y
ANVIL_VECTORISE_VVV(detail::VOP_XOR, vector_xor, ANVIL_VECTOR_OP, ANVIL_VECTOR_OP2)

#undef ANVIL_VECTOR_OP
#undef ANVIL_VECTOR_OP2
#define ANVIL_VECTOR_OP(X,Y) X == Y
#define ANVIL_VECTOR_OP2(X, Y) X = X == Y
ANVIL_VECTORISE_VVV(detail::VOP_EQ, vector_eq, ANVIL_VECTOR_OP, ANVIL_VECTOR_OP2)

#undef ANVIL_VECTOR_OP
#undef ANVIL_VECTOR_OP2
#define ANVIL_VECTOR_OP(X,Y) X != Y
#define ANVIL_VECTOR_OP2(X, Y) X = X != Y
ANVIL_VECTORISE_VVV(detail::VOP_NE, vector_ne, ANVIL_VECTOR_OP, ANVIL_VECTOR_OP2)

#undef ANVIL_VECTOR_OP
#undef ANVIL_VECTOR_OP2
#define ANVIL_VECTOR_OP(X,Y) X < Y
#define ANVIL_VECTOR_OP2(X, Y) X = X < Y
ANVIL_VECTORISE_VVV(detail::VOP_LT, vector_lt, ANVIL_VECTOR_OP, ANVIL_VECTOR_OP2)

#undef ANVIL_VECTOR_OP
#undef ANVIL_VECTOR_OP2
#define ANVIL_VECTOR_OP(X,Y) X > Y
#define ANVIL_VECTOR_OP2(X, Y) X = X > Y
ANVIL_VECTORISE_VVV(detail::VOP_GT, vector_gt, ANVIL_VECTOR_OP, ANVIL_VECTOR_OP2)

#undef ANVIL_VECTOR_OP
#undef ANVIL_VECTOR_OP2
#define ANVIL_VECTOR_OP(X,Y) X <= Y
#define ANVIL_VECTOR_OP2(X, Y) X = X <= Y
ANVIL_VECTORISE_VVV(detail::VOP_LE, vector_le, ANVIL_VECTOR_OP, ANVIL_VECTOR_OP2)

#undef ANVIL_VECTOR_OP
#undef ANVIL_VECTOR_OP2
#define ANVIL_VECTOR_OP(X,Y) X >= Y
#define ANVIL_VECTOR_OP2(X, Y) X = X >= Y
ANVIL_VECTORISE_VVV(detail::VOP_GE, vector_ge, ANVIL_VECTOR_OP, ANVIL_VECTOR_OP2)

}

#endif