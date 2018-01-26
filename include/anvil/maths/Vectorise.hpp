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
			enum { OPTIMAL = OperationInfo<O, T>::size_max };
			typedef OperationImplementation<T, OPTIMAL, O> optimal_t;

			union simd_ptr {
				SIMDHelper<T, OPTIMAL>::simd_t* vo;
				DefaultSIMD<T, OPTIMAL>* vn;
				const T* s;
			};
			simd_ptr x, y, z, o;
			x.s = x_;
			y.s = y_;
			z.s = z_;
			o.s = o_;

			const size_t loop = s / OPTIMAL;
			const size_t remainder = s % OPTIMAL;

			if (optimal_t::optimised()) {
				for (size_t i = 0; i < loop; ++i) {
					o.vo[i] = optimal_t::execute_in(x.vo[i], y.vo[i], z.vo[i]);
				}
			} else {
				for (size_t i = 0; i < loop; ++i) {
					optimal_t::execute_nop(x.vn[i].elements, y.vn[i].elements, z.vn[i].elements, o.vn[i].elements);
				}
			}
			for (size_t i = 0; i < remainder; ++i) {
				o.vn[loop].elements[i] = OperationImplementation<T, 1, O>::execute(x.vn[loop].elements[i], y.vn[loop].elements[i], z.vn[loop].elements[i]);
			}
		}

		template<class T, Operation O>
		static void ANVIL_CALL dynamic_operation(const T* x_, const T* y_, T* o_, const size_t s) {
			enum { OPTIMAL = OperationInfo<O, T>::size_max };
			typedef OperationImplementation<T, OPTIMAL, O> optimal_t;

			union simd_ptr {
				SIMDHelper<T, OPTIMAL>::simd_t* vo;
				DefaultSIMD<T, OPTIMAL>* vn;
				const T* s;
			};
			simd_ptr x, y, o;
			x.s = x_;
			y.s = y_;
			o.s = o_;

			const size_t loop = s / OPTIMAL;
			const size_t remainder = s % OPTIMAL;

			if (optimal_t::optimised()) {
				for (size_t i = 0; i < loop; ++i) {
					o.vo[i] = optimal_t::execute_in(x.vo[i], y.vo[i]);
				}
			} else {
				for (size_t i = 0; i < loop; ++i) {
					optimal_t::execute_nop(x.vn[i].elements, y.vn[i].elements, o.vn[i].elements);
				}
			}
			for (size_t i = 0; i < remainder; ++i) {
				o.vn[loop].elements[i] = OperationImplementation<T, 1, O>::execute(x.vn[loop].elements[i], y.vn[loop].elements[i]);
			}
		}

		template<class T, Operation O>
		static void ANVIL_CALL dynamic_operation(const T* x_, T* o_, const size_t s) {
			enum { OPTIMAL = OperationInfo<O, T>::size_max };
			typedef OperationImplementation<T, OPTIMAL, O> optimal_t;

			union simd_ptr {
				SIMDHelper<T, OPTIMAL>::simd_t* vo;
				DefaultSIMD<T, OPTIMAL>* vn;
				const T* s;
			};
			simd_ptr x, o;
			x.s = x_;
			o.s = o_;

			const size_t loop = s / OPTIMAL;
			const size_t remainder = s % OPTIMAL;

			if (optimal_t::optimised()) {
				for (size_t i = 0; i < loop; ++i) {
					o.vo[i] = optimal_t::execute_in(x.vo[i]);
				}
			} else {
				for (size_t i = 0; i < loop; ++i) {
					optimal_t::execute_nop(x.vn[i].elements, o.vn[i].elements);
				}
			}
			for (size_t i = 0; i < remainder; ++i) {
				o.vn[loop].elements[i] = OperationImplementation<T, 1, O>::execute(x.vn[loop].elements[i]);
			}
		}
	}
}

#endif