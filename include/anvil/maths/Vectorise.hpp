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
		static void ANVIL_CALL dynamic_operation(const T* x_, const T* y_, const T* z_, T* o_, const size_t s) {
			enum { OPTIMAL = OptimalOperationSize<O, T>::value };
			typedef OperationImplementation<T, OPTIMAL, O> optimal_t;
			typedef DefaultSIMD<T, OPTIMAL> optimal_simd_t;

			const optimal_simd_t* const x = reinterpret_cast<const optimal_simd_t*>(x_);
			const optimal_simd_t* const y = reinterpret_cast<const optimal_simd_t*>(y_);
			const optimal_simd_t* const z = reinterpret_cast<const optimal_simd_t*>(z_);
			optimal_simd_t* const o = reinterpret_cast<optimal_simd_t*>(o_);

			const size_t loop = s / OPTIMAL;
			const size_t remainder = s % OPTIMAL;

			if (optimal_t::optimised()) {
				for (size_t i = 0; i < loop; ++i) {
					optimal_t::execute_op(x[i].elements, y[i].elements, z[i].elements, o[i].elements);
				}
			} else {
				for (size_t i = 0; i < loop; ++i) {
					optimal_t::execute_nop(x[i].elements, y[i].elements, z[i].elements, o[i].elements);
				}
			}
			for (size_t i = 0; i < remainder; ++i) {
				o[loop].elements[i] = OperationImplementation<T, 1, O>::execute(x[loop].elements[i], y[loop].elements[i], z[loop].elements[i]);
			}
		}

		template<class T, Operation O>
		static void ANVIL_CALL dynamic_operation(const T* x_, const T* y_, T* o_, const size_t s) {
			enum { OPTIMAL = OptimalOperationSize<O, T>::value };
			typedef OperationImplementation<T, OPTIMAL, O> optimal_t;
			typedef DefaultSIMD<T, OPTIMAL> optimal_simd_t;

			const optimal_simd_t* const x = reinterpret_cast<const optimal_simd_t*>(x_);
			const optimal_simd_t* const y = reinterpret_cast<const optimal_simd_t*>(y_);
			optimal_simd_t* const o = reinterpret_cast<optimal_simd_t*>(o_);

			const size_t loop = s / OPTIMAL;
			const size_t remainder = s % OPTIMAL;

			if (optimal_t::optimised()) {
				for (size_t i = 0; i < loop; ++i) {
					optimal_t::execute_op(x[i].elements, y[i].elements, o[i].elements);
				}
			} else {
				for (size_t i = 0; i < loop; ++i) {
					optimal_t::execute_nop(x[i].elements, y[i].elements, o[i].elements);
				}
			}
			for (size_t i = 0; i < remainder; ++i) {
				o[loop].elements[i] = OperationImplementation<T, 1, O>::execute(x[loop].elements[i], y[loop].elements[i]);
			}
		}

		template<class T, Operation O>
		static void ANVIL_CALL dynamic_operation(const T* x_, T* o_, const size_t s) {
			enum { OPTIMAL = OptimalOperationSize<O, T>::value };
			typedef OperationImplementation<T, OPTIMAL, O> optimal_t;
			typedef DefaultSIMD<T, OPTIMAL> optimal_simd_t;

			const optimal_simd_t* const x = reinterpret_cast<const optimal_simd_t*>(x_);
			optimal_simd_t* const o = reinterpret_cast<optimal_simd_t*>(o_);

			const size_t loop = s / OPTIMAL;
			const size_t remainder = s % OPTIMAL;

			if (optimal_t::optimised()) {
				for (size_t i = 0; i < loop; ++i) {
					optimal_t::execute_op(x[i].elements, o[i].elements);
				}
			} else {
				for (size_t i = 0; i < loop; ++i) {
					optimal_t::execute_nop(x[i].elements, o[i].elements);
				}
			}
			for (size_t i = 0; i < remainder; ++i) {
				o[loop].elements[i] = OperationImplementation<T, 1, O>::execute(x[loop].elements[i]);
			}
		}
	}
}

#endif