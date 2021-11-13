//Copyupper 2021 Adam G. Smith
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

#ifndef ANVIL_CORE_VECTOR_HPP
#define ANVIL_CORE_VECTOR_HPP

#include "anvil/core/Keywords.hpp"
#include "anvil/core/Assert.hpp"

namespace anvil {

	namespace detail {

		template<class T, size_t SIZE>
		class BasicVector;

		template<class T, size_t SIZE>
		struct VectorHalfType {
			typedef BasicVector<T, SIZE> type;
		};

		template<class T>
		struct VectorHalfType<T, 1u> {
			typedef T type;
		};
	}

	template<class T, size_t SIZE>
	using Vector = typename detail::VectorHalfType<T, SIZE>::type;

	namespace detail {

		template<class T, size_t SIZE>
		class BasicVector {
		public:
			typedef T type;
			enum { 
				size = SIZE,
				upper_size = SIZE / 2,
				lower_size = size - upper_size
			};

			typedef Vector<T, lower_size> lower_t;
			typedef Vector<T, upper_size> upper_t;

			union {
				struct {
					lower_t lower_half;
					upper_t upper_half;
				};
				T data[size];
			};

			BasicVector() = default;
			~BasicVector() = default;

			template<size_t S1, size_t S2>
			BasicVector(const Vector<T,S1>& a, const Vector<T, S2>& b) {
				static_assert((S1 + S2) == size, "anvil::BasicVector : Vector sizes must add upp");

				SetSubVector<S1>(a, 0u);
				SetSubVector<S2>(b, S1);
			}

			template<size_t S1, size_t S2, size_t S3>
			BasicVector(const Vector<T, S1>& a, const Vector<T, S2>& b, const Vector<T, S3>& c) {
				static_assert((S1 + S2 + S3) == size, "anvil::BasicVector : Vector sizes must add upp");

				SetSubVector<S1>(a, 0u);
				SetSubVector<S2>(b, S1);
				SetSubVector<S3>(c, S1 + S2);
			}

			template<size_t S1, size_t S2, size_t S3, size_t S4>
			BasicVector(const Vector<T, S1>& a, const Vector<T, S2>& b, const Vector<T, S3>& c, const Vector<T, S4>& d) {
				static_assert((S1 + S2 + S3 + S4) == size, "anvil::BasicVector : Vector sizes must add upp");

				SetSubVector<S1>(a, 0u);
				SetSubVector<S2>(b, S1);
				SetSubVector<S3>(c, S1 + S2);
				SetSubVector<S4>(c, S1 + S2 + S3);
			}

			template<size_t S1, size_t S2, size_t S3, size_t S4, size_t S5>
			BasicVector(const Vector<T, S1>& a, const Vector<T, S2>& b, const Vector<T, S3>& c, const Vector<T, S4>& d, const Vector<T, S5>& e) {
				static_assert((S1 + S2 + S3 + S4 + S5) == size, "anvil::BasicVector : Vector sizes must add upp");

				SetSubVector<S1>(a, 0u);
				SetSubVector<S2>(b, S1);
				SetSubVector<S3>(c, S1 + S2);
				SetSubVector<S4>(d, S1 + S2 + S3);
				SetSubVector<S5>(e, S1 + S2 + S3 + S4);
			}

			template<size_t S1, size_t S2, size_t S3, size_t S4, size_t S5, size_t S6>
			BasicVector(const Vector<T, S1>& a, const Vector<T, S2>& b, const Vector<T, S3>& c, const Vector<T, S4>& d, const Vector<T, S5>& e, const Vector<T, S6>& f) {
				static_assert((S1 + S2 + S3 + S4 + S5 + S6) == size, "anvil::BasicVector : Vector sizes must add upp");

				SetSubVector<S1>(a, 0u);
				SetSubVector<S2>(b, S1);
				SetSubVector<S3>(c, S1 + S2);
				SetSubVector<S4>(d, S1 + S2 + S3);
				SetSubVector<S5>(e, S1 + S2 + S3 + S4);
				SetSubVector<S6>(f, S1 + S2 + S3 + S4 + S5);
			}

			template<size_t S1, size_t S2, size_t S3, size_t S4, size_t S5, size_t S6, size_t S7>
			BasicVector(const Vector<T, S1>& a, const Vector<T, S2>& b, const Vector<T, S3>& c, const Vector<T, S4>& d, const Vector<T, S5>& e, const Vector<T, S6>& f, const Vector<T, S7>& g) {
				static_assert((S1 + S2 + S3 + S4 + S5 + S6 + S7) == size, "anvil::BasicVector : Vector sizes must add upp");

				SetSubVector<S1>(a, 0u);
				SetSubVector<S2>(b, S1);
				SetSubVector<S3>(c, S1 + S2);
				SetSubVector<S4>(d, S1 + S2 + S3);
				SetSubVector<S5>(e, S1 + S2 + S3 + S4);
				SetSubVector<S6>(f, S1 + S2 + S3 + S4 + S5);
				SetSubVector<S7>(g, S1 + S2 + S3 + S4 + S5 + S6);
			}

			template<size_t S1, size_t S2, size_t S3, size_t S4, size_t S5, size_t S6, size_t S7, size_t S8>
			BasicVector(const Vector<T, S1>& a, const Vector<T, S2>& b, const Vector<T, S3>& c, const Vector<T, S4>& d, const Vector<T, S5>& e, const Vector<T, S6>& f, const Vector<T, S7>& g, const Vector<T, S8>& h) {
				static_assert((S1 + S2 + S3 + S4 + S5 + S6 + S7 + S8) == size, "anvil::BasicVector : Vector sizes must add upp");

				SetSubVector<S1>(a, 0u);
				SetSubVector<S2>(b, S1);
				SetSubVector<S3>(c, S1 + S2);
				SetSubVector<S4>(d, S1 + S2 + S3);
				SetSubVector<S5>(e, S1 + S2 + S3 + S4);
				SetSubVector<S6>(f, S1 + S2 + S3 + S4 + S5);
				SetSubVector<S7>(g, S1 + S2 + S3 + S4 + S5 + S6);
				SetSubVector<S8>(h, S1 + S2 + S3 + S4 + S5 + S6 + S7);
			}

			ANVIL_STRONG_INLINE T& operator[](const size_t i) throw() {
				return data[i];
			}

			ANVIL_STRONG_INLINE T operator[](const size_t i) const throw() {
				return data[i];
			}

			template<size_t SIZE2>
			ANVIL_STRONG_INLINE Vector<type, SIZE2>& GetSubVector(size_t offset) throw() {
				ANVIL_ASSUME(SIZE2 + offset <= size);
				return *reinterpret_cast<Vector<type, SIZE2>*>(data + offset);
			}

			template<size_t SIZE2>
			ANVIL_STRONG_INLINE const Vector<type, SIZE2>& GetSubVector(size_t offset) const throw() {
				ANVIL_ASSUME(SIZE2 + offset <= size);
				return *reinterpret_cast<const Vector<type, SIZE2>*>(data + offset);
			}

			template<size_t SIZE2>
			ANVIL_STRONG_INLINE void SetSubVector(const Vector<type, SIZE2>& x, size_t offset) {
				ANVIL_ASSUME(SIZE2 + offset <= size);
				Vector<type, SIZE2>& dst = GetSubVector(offset);
				dst = x;
			}

			inline Vector<T, size>& operator+=(const Vector<T, size>& other) throw() {
				lower_half += other.lower_half;
				upper_half += other.upper_half;
				return *this;
			}

			inline Vector<T, size>& operator-=(const Vector<T, size>& other) throw() {
				lower_half -= other.lower_half;
				upper_half -= other.upper_half;
				return *this;
			}

			inline Vector<T, size>& operator*=(const Vector<T, size>& other) throw() {
				lower_half *= other.lower_half;
				upper_half *= other.upper_half;
				return *this;
			}

			inline Vector<T, size>& operator/=(const Vector<T, size>& other) throw() {
				lower_half /= other.lower_half;
				upper_half /= other.upper_half;
				return *this;
			}

			inline Vector<T, size> operator+(const Vector<T, size>& other) const throw() {
				return Vector<T, size>(lower_half + other.lower_half, upper_half + other.upper_half);
			}

			inline Vector<T, size> operator-(const Vector<T, size>& other) const throw() {
				return Vector<T, size>(lower_half - other.lower_half, upper_half - other.upper_half);
			}

			inline Vector<T, size> operator*(const Vector<T, size>& other) const throw() {
				return Vector<T, size>(lower_half * other.lower_half, upper_half * other.upper_half);
			}

			inline Vector<T, size> operator/(const Vector<T, size>& other) const throw() {
				return Vector<T, size>(lower_half / other.lower_half, upper_half / other.upper_half);
			}
		};
	}



}

#endif
