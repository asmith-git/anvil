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

	template<class T>
	static void vector_add(const T* a, const T* b, T* c, size_t a_length) throw() {
		enum { LENGTH = detail::OptimalVectorLength<T>::value };

		detail::VectorPtr<T, LENGTH> a_;
		detail::VectorPtr<T, LENGTH> b_;
		detail::VectorPtr<T, LENGTH> c_;

		a_.scalar = const_cast<T*>(a);
		b_.scalar = const_cast<T*>(b);
		c_.scalar = c;

		while (a_length >= LENGTH) {
			*c_.vector = *a_.vector + *b_.vector;
			++a_.vector;
			++b_.vector;
			++c_.vector;
			a_length -= LENGTH;
		}

		for (size_t i = 0; i < a_length; ++i) {
			*c_.scalar = *a_.scalar + *b_.scalar;
			++a_.scalar;
			++b_.scalar;
			++c_.scalar;
		}
	}
}

#endif