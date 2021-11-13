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

	template<class T, size_t SIZE>
	class Vector;

	namespace detail {
		template<class T, size_t SIZE>
		struct VectorHalfType {
			typedef Vector<T, SIZE> type;
		};

		template<class T>
		struct VectorHalfType<T, 1u> {
			typedef T type;
		};
	}

	template<class T, size_t SIZE>
	class Vector {
	public:
		typedef T type;
		enum { 
			size = SIZE,
			upper_size = SIZE / 2,
			lower_size = size - upper_size
		};

		typedef typename detail::VectorHalfType<T, lower_size>::type lower_t;
		typedef typename detail::VectorHalfType<T, upper_size>::type upper_t;

		union {
			struct {
				lower_t lower_half;
				upper_t upper_half;
			};
			T data[size];
		};

		Vector() = default;
		~Vector() = default;

		Vector(const lower_t& low, const upper_t& upper) :
			lower_half(low),
			upper_half(upper)
		{}

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

		ANVIL_STRONG_INLINE Vector<T, size>& operator+=(const Vector<T, size>& other) throw() {
			lower_half += other.lower_half;
			upper_half += other.upper_half;
			return *this;
		}

		ANVIL_STRONG_INLINE Vector<T, size>& operator-=(const Vector<T, size>& other) throw() {
			lower_half -= other.lower_half;
			upper_half -= other.upper_half;
			return *this;
		}

		ANVIL_STRONG_INLINE Vector<T, size>& operator*=(const Vector<T, size>& other) throw() {
			lower_half *= other.lower_half;
			upper_half *= other.upper_half;
			return *this;
		}

		ANVIL_STRONG_INLINE Vector<T, size>& operator/=(const Vector<T, size>& other) throw() {
			lower_half /= other.lower_half;
			upper_half /= other.upper_half;
			return *this;
		}

		ANVIL_STRONG_INLINE Vector<T, size> operator+(const Vector<T, size>& other) const throw() {
			return Vector<T, size>(lower_half + other.lower_half, upper_half + other.upper_half);
		}

		ANVIL_STRONG_INLINE Vector<T, size> operator-(const Vector<T, size>& other) const throw() {
			return Vector<T, size>(lower_half - other.lower_half, upper_half - other.upper_half);
		}

		ANVIL_STRONG_INLINE Vector<T, size> operator*(const Vector<T, size>& other) const throw() {
			return Vector<T, size>(lower_half * other.lower_half, upper_half * other.upper_half);
		}

		ANVIL_STRONG_INLINE Vector<T, size> operator/(const Vector<T, size>& other) const throw() {
			return Vector<T, size>(lower_half / other.lower_half, upper_half / other.upper_half);
		}
	};

}

#endif
