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

namespace anvil {

	template<class T, size_t SIZE>
	class Vector {
	public:
		typedef T type;
		enum { 
			size = SIZE,
			upper_size = SIZE / 2,
			lower_size = size - upper_size
		};

		typedef Vector<T, lower_size> lower_t;
		typedef Vector<T, upper_size> upper_t;

	private:
		T _data[size];

	public:
		Vector() = default;
		~Vector() = default;

		Vector(const lower_t& low, const upper_t& upper) {
			SetLowerHalf(low);
			SetUpperHalf(upper);
		}

		ANVIL_STRONG_INLINE T& operator[](const size_t i) throw() {
			return _data[i];
		}

		ANVIL_STRONG_INLINE T operator[](const size_t i) const throw() {
			return _data[i];
		}

		ANVIL_STRONG_INLINE lower_t& GetLowerHalf() throw() {
			return *reinterpret_cast<lower_t*>(_data);
		}

		ANVIL_STRONG_INLINE const lower_t& GetLowerHalf() const throw() {
			return *reinterpret_cast<const lower_t*>(_data);
		}

		ANVIL_STRONG_INLINE upper_t& GetUpperHalf() throw() {
			return *reinterpret_cast<upper_t*>(_data + lower_size);
		}

		ANVIL_STRONG_INLINE const upper_t& GetUpperHalf() const throw() {
			return *reinterpret_cast<const upper_t*>(_data + lower_size);
		}

		ANVIL_STRONG_INLINE void SetLowerHalf(const lower_t& x) {
			lower_t& dst = GetLowerHalf();
			dst = x;
		}

		ANVIL_STRONG_INLINE void SetUpperHalf(const upper_t& x) {
			upper_t& dst = GetUpperHalf();
			dst = x;
		}
	};

	template<class T>
	class Vector<T, 1u> {
	public:
		typedef T type;
		enum {
			size = 1u,
			upper_size = 0u,
			lower_size = 1u
		};

		typedef Vector<T, 1u> lower_t;
		typedef Vector<T, 1u> upper_t;

	private:
		T _data[size];

	public:
		Vector() = default;
		~Vector() = default;

		Vector(const lower_t& low) {
			SetLowerHalf(low);
		}

		ANVIL_STRONG_INLINE T& operator[](const size_t i) throw() {
			return _data[i];
		}

		ANVIL_STRONG_INLINE T operator[](const size_t i) const throw() {
			return _data[i];
		}

		ANVIL_STRONG_INLINE lower_t& GetLowerHalf() throw() {
			return *reinterpret_cast<lower_t*>(_data);
		}

		ANVIL_STRONG_INLINE const lower_t& GetLowerHalf() const throw() {
			return *reinterpret_cast<const lower_t*>(_data);
		}

		ANVIL_STRONG_INLINE upper_t& GetUpperHalf() throw() {
			return GetLowerHalf();
		}

		ANVIL_STRONG_INLINE const upper_t& GetUpperHalf() const throw() {
			return GetLowerHalf();
		}

		ANVIL_STRONG_INLINE void SetLowerHalf(const lower_t& x) {
			lower_t& dst = GetLowerHalf();
			dst = x;
		}

		ANVIL_STRONG_INLINE void SetUpperHalf(const upper_t& x) {
			upper_t& dst = GetUpperHalf();
			dst = x;
		}
	};

}

#endif
