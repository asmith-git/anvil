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

#include "anvil/maths/SIMD.hpp"

namespace anvil {
	namespace simd {
		template<class T, Operation O>
		static void ANVIL_CALL dynamic_operation(const T* x, const T* y, const T* z, T* o, const size_t s) {
			enum { OPTIMAL = OptimalOperationSize<O, T>::value };
			typedef OperationImplementation<T, OPTIMAL, O> optimal_t;

			const size_t loop = s / OPTIMAL;
			const size_t remainder = s % OPTIMAL;

			if (optimal_t::optimised()) {
				for (size_t i = 0; i < loop; ++i) {
					optimal_t::execute_op(x, y, z, o);
					x += OPTIMAL;
					y += OPTIMAL;
					z += OPTIMAL;
					o += OPTIMAL;
				}
			} else {
				for (size_t i = 0; i < loop; ++i) {
					optimal_t::execute_nop(x, y, z, o);
					x += OPTIMAL;
					y += OPTIMAL;
					z += OPTIMAL;
					o += OPTIMAL;
				}
			}
			for (size_t i = 0; i < remainder; ++i) {
				o[i] = OperationImplementation<T, 1, O>::execute(*x, *y, *z);
				++x;
				++y;
				++z;
				++o;
			}
		}

		template<class T, Operation O>
		static void ANVIL_CALL dynamic_operation(const T* x, const T* y, T* o, const size_t s) {
			enum { OPTIMAL = OptimalOperationSize<O, T>::value };
			typedef OperationImplementation<T, OPTIMAL, O> optimal_t;

			const size_t loop = s / OPTIMAL;
			const size_t remainder = s % OPTIMAL;

			if (optimal_t::optimised()) {
				for (size_t i = 0; i < loop; ++i) {
					optimal_t::execute_op(x, y, o);
					x += OPTIMAL;
					y += OPTIMAL;
					o += OPTIMAL;
				}
			} else {
				for (size_t i = 0; i < loop; ++i) {
					optimal_t::execute_nop(x, y, o);
					x += OPTIMAL;
					y += OPTIMAL;
					o += OPTIMAL;
				}
			}
			for (size_t i = 0; i < remainder; ++i) {
				o[i] = OperationImplementation<T, 1, O>::execute(*x, *y);
				++x;
				++y;
				++o;
			}
		}

		template<class T, Operation O>
		static void ANVIL_CALL dynamic_operation(const T* x, T* o, const size_t s) {
			enum { OPTIMAL = OptimalOperationSize<O, T>::value };
			typedef OperationImplementation<T, OPTIMAL, O> optimal_t;

			const size_t loop = s / OPTIMAL;
			const size_t remainder = s % OPTIMAL;

			if (optimal_t::optimised()) {
				for (size_t i = 0; i < loop; ++i) {
					optimal_t::execute_op(x, o);
					x += OPTIMAL;
					o += OPTIMAL;
				}
			} else {
				for (size_t i = 0; i < loop; ++i) {
					optimal_t::execute_nop(x, o);
					x += OPTIMAL;
					o += OPTIMAL;
				}
			}
			for (size_t i = 0; i < remainder; ++i) {
				o[i] = OperationImplementation<T, 1, O>::execute(*x);
				++x;
				++o;
			}
		}
	}
}

#endif