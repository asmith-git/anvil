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
		enum {
			VECTOR_LENGTH_SCALE = 2
		};

		template<class T> struct OptimalVectorLength;

		template<> struct OptimalVectorLength<int8_t> { enum   { value = 16 * VECTOR_LENGTH_SCALE }; };
		template<> struct OptimalVectorLength<uint8_t> { enum  { value = 16 * VECTOR_LENGTH_SCALE }; };
		template<> struct OptimalVectorLength<int16_t> { enum  { value = 8 * VECTOR_LENGTH_SCALE }; };
		template<> struct OptimalVectorLength<uint16_t> { enum { value = 8 * VECTOR_LENGTH_SCALE }; };
		template<> struct OptimalVectorLength<int32_t> { enum  { value = 4 * VECTOR_LENGTH_SCALE }; };
		template<> struct OptimalVectorLength<uint32_t> { enum { value = 4 * VECTOR_LENGTH_SCALE }; };
		template<> struct OptimalVectorLength<int64_t> { enum  { value = 2 * VECTOR_LENGTH_SCALE }; };
		template<> struct OptimalVectorLength<uint64_t> { enum { value = 2 * VECTOR_LENGTH_SCALE }; };
		template<> struct OptimalVectorLength<float> { enum    { value = 4 * VECTOR_LENGTH_SCALE }; };
		template<> struct OptimalVectorLength<double> { enum   { value = 2 * VECTOR_LENGTH_SCALE }; };

		template<class T, size_t S>
		union VectorPtr {
			Vector<T, S>* vector;
			T* scalar;
		};
	}

#define ANVIL_VECTORISE_VV(NAME, OPERATION)\
	template<class T>\
	static void NAME(T* ANVIL_RESTRICT a, const T* ANVIL_RESTRICT b, size_t a_length) throw() {\
		enum { LENGTH = detail::OptimalVectorLength<T>::value };\
		\
		detail::VectorPtr<T, LENGTH> a_;\
		detail::VectorPtr<T, LENGTH> b_;\
		detail::VectorPtr<T, LENGTH> c_;\
		\
		a_.scalar = a;\
		b_.scalar = const_cast<T*>(b);\
		\
		while (a_length >= LENGTH) {\
			OPERATION(*a_.vector, *b_.vector);\
			++a_.vector;\
			++b_.vector;\
			a_length -= LENGTH;\
		}\
		\
		for (size_t i = 0; i < a_length; ++i) {\
			OPERATION(*a_.scalar, *b_.scalar);\
			++a_.scalar;\
			++b_.scalar;\
		}\
	}

#define ANVIL_VECTORISE_VVV(NAME, OPERATION, OPERATION2)\
	ANVIL_VECTORISE_VV(NAME, OPERATION2)\
	template<class T>\
	static void NAME(const T* ANVIL_RESTRICT a, const T* ANVIL_RESTRICT b, T* ANVIL_RESTRICT c, size_t a_length) throw() {\
		enum { LENGTH = detail::OptimalVectorLength<T>::value };\
		\
		if (a == c) {\
			NAME<T>(c, b, a_length);\
			return;\
		}\
		\
		detail::VectorPtr<T, LENGTH> a_;\
		detail::VectorPtr<T, LENGTH> b_;\
		detail::VectorPtr<T, LENGTH> c_;\
		\
		a_.scalar = const_cast<T*>(a);\
		b_.scalar = const_cast<T*>(b);\
		c_.scalar = c;\
		\
		while (a_length >= LENGTH) {\
			*c_.vector = OPERATION(*a_.vector, *b_.vector);\
			++a_.vector;\
			++b_.vector;\
			++c_.vector;\
			a_length -= LENGTH;\
		}\
		\
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
ANVIL_VECTORISE_VVV(vector_add, ANVIL_VECTOR_OP, ANVIL_VECTOR_OP2)

#undef ANVIL_VECTOR_OP
#undef ANVIL_VECTOR_OP2
#define ANVIL_VECTOR_OP(X,Y) X - Y
#define ANVIL_VECTOR_OP2(X, Y) X -= Y
ANVIL_VECTORISE_VVV(vector_sub, ANVIL_VECTOR_OP, ANVIL_VECTOR_OP2)

#undef ANVIL_VECTOR_OP
#undef ANVIL_VECTOR_OP2
#define ANVIL_VECTOR_OP(X,Y) X * Y
#define ANVIL_VECTOR_OP2(X, Y) X *= Y
ANVIL_VECTORISE_VVV(vector_mul, ANVIL_VECTOR_OP, ANVIL_VECTOR_OP2)

#undef ANVIL_VECTOR_OP
#undef ANVIL_VECTOR_OP2
#define ANVIL_VECTOR_OP(X,Y) X / Y
#define ANVIL_VECTOR_OP2(X, Y) X /= Y
ANVIL_VECTORISE_VVV(vector_div, ANVIL_VECTOR_OP, ANVIL_VECTOR_OP2)

}

#endif