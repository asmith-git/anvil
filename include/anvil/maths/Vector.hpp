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

#ifndef ANVIL_MATHS_VECTOR_HPP
#define ANVIL_MATHS_VECTOR_HPP

#include <cmath>
#include "anvil/maths/Type.hpp"
#include "anvil/maths/Popcount.hpp"

namespace anvil {
	template<class T, size_t S>
	class Vector {
	public:
		typedef T type;
		enum {
			size = S,
		};
		typedef Vector<type, size> this_t;
	private:
		type mData[size];
	public:
		Vector() throw() {
			for (size_t i = 0; i < size; ++i) mData[i] = static_cast<type>(0);
		}

		Vector(const T aScalar) throw() {
			for (size_t i = 0; i < size; ++i) mData[i] = aScalar;
		}

		Vector(const T* aData) throw() {
			for (size_t i = 0; i < size; ++i) mData[i] = aData[i];
		}

		template<class T2>
		Vector(const Vector<T2, size> aOther) throw() {
			for (size_t i = 0; i < size; ++i) mData[i] = static_cast<T>(aOther[i]);
		}

		inline operator bool() const throw() {
			return sum() > static_cast<type>(0);
		}

		inline this_t operator!() const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = !mData[i];
			return tmp;
		}

		template<class T2 = type>
		inline typename std::enable_if<std::is_integral<T2>::value, this_t>::type operator~() const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = ~mData[i];
			return tmp;
		}

		inline this_t operator%(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = static_cast<type>(mData[i] % aOther.mData[i]);
			return tmp;
		}

		inline this_t operator==(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = static_cast<type>(mData[i] == aOther.mData[i]);
			return tmp;
		}

		inline this_t operator!=(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = static_cast<type>(mData[i] != aOther.mData[i]);
			return tmp;
		}

		inline this_t operator<(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = static_cast<type>(mData[i] < aOther.mData[i]);
			return tmp;
		}

		inline this_t operator>(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = static_cast<type>(mData[i] > aOther.mData[i]);
			return tmp;
		}

		inline this_t operator<=(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = static_cast<type>(mData[i] <= aOther.mData[i]);
			return tmp;
		}

		inline this_t operator>=(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = static_cast<type>(mData[i] >= aOther.mData[i]);
			return tmp;
		}

		inline this_t operator+(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = mData[i] + aOther.mData[i];
			return tmp;
		}

		inline this_t operator-(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = mData[i] - aOther.mData[i];
			return tmp;
		}

		inline this_t operator*(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = mData[i] * aOther.mData[i];
			return tmp;
		}

		inline this_t operator/(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = mData[i] / aOther.mData[i];
			return tmp;
		}

		template<class T2 = type>
		inline typename std::enable_if<std::is_integral<T2>::value, this_t>::type operator&(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = mData[i] & aOther.mData[i];
			return tmp;
		}

		template<class T2 = type>
		inline typename std::enable_if<std::is_integral<T2>::value, this_t>::type operator|(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = mData[i] | aOther.mData[i];
			return tmp;
		}

		template<class T2 = type>
		inline typename std::enable_if<std::is_integral<T2>::value, this_t>::type operator^(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = mData[i] ^ aOther.mData[i];
			return tmp;
		}

		template<class T2 = type>
		inline typename std::enable_if<std::is_integral<T2>::value, this_t>::type operator<<(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = mData[i] << aOther.mData[i];
			return tmp;
		}

		template<class T2 = type>
		inline typename std::enable_if<std::is_integral<T2>::value, this_t>::type operator>>(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = mData[i] >> aOther.mData[i];
			return tmp;
		}

		inline this_t& operator+=(const this_t aOther) throw() {
			for (size_t i = 0; i < size; ++i) mData[i] += aOther.mData[i];
			return *this;
		}

		inline this_t& operator-=(const this_t aOther) throw() {
			for (size_t i = 0; i < size; ++i) mData[i] -= aOther.mData[i];
			return *this;
		}

		inline this_t& operator*=(const this_t aOther) throw() {
			for (size_t i = 0; i < size; ++i) mData[i] *= aOther.mData[i];
			return *this;
		}

		inline this_t& operator/=(const this_t aOther) throw() {
			for (size_t i = 0; i < size; ++i) mData[i] /= aOther.mData[i];
			return *this;
		}

		template<class T2 = type>
		inline typename std::enable_if<std::is_integral<T2>::value, this_t&>::type operator&=(const this_t aOther) throw() {
			for (size_t i = 0; i < size; ++i) mData[i] &= aOther.mData[i];
			return *this;
		}

		template<class T2 = type>
		inline typename std::enable_if<std::is_integral<T2>::value, this_t&>::type operator|=(const this_t aOther) throw() {
			for (size_t i = 0; i < size; ++i) mData[i] |= aOther.mData[i];
			return *this;
		}

		template<class T2 = type>
		inline typename std::enable_if<std::is_integral<T2>::value, this_t&>::type operator^=(const this_t aOther) throw() {
			for (size_t i = 0; i < size; ++i) mData[i] ^= aOther.mData[i];
			return *this;
		}

		template<class T2 = type>
		inline typename std::enable_if<std::is_integral<T2>::value, this_t&>::type operator<<=(const this_t aOther) throw() {
			for (size_t i = 0; i < size; ++i) mData[i] <<= aOther.mData[i];
			return *this;
		}

		template<class T2 = type>
		inline typename std::enable_if<std::is_integral<T2>::value, this_t&>::type operator>>=(const this_t aOther) throw() {
			for (size_t i = 0; i < size; ++i) mData[i] >>= aOther.mData[i];
			return *this;
		}

		inline type operator[](const size_t aIndex) const throw() {
			return mData[aIndex];
		}

		inline type& operator[](const size_t aIndex) throw() {
			return mData[aIndex];
		}

		inline const type* begin() const throw() {
			return mData;
		}

		inline type* begin() throw() {
			return mData;
		}

		inline const type* end() const throw() {
			return mData + size;
		}

		inline type* end() throw() {
			return mData + size;
		}

		inline type sum() const throw() {
			type tmp = static_cast<type>(0);
			for (size_t i = 0; i < size; ++i) tmp += mData[i];
			return tmp;
		}

		inline type avg() const throw() {
			return sum() / static_cast<type>(size);
		}

		inline this_t min(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = std::min<type>(mData[i], aOther.mData[i]);
			return tmp;
		}

		inline this_t max(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = std::min<type>(mData[i], aOther.mData[i]);
			return tmp;
		}

		inline type min() const throw() {
			type tmp = data[0];
			for (size_t i = 1; i < size; ++i) tmp = std::min<type>(tmp, aOther.mData[i]);
			return tmp;
		}

		inline type max() const throw() {
			type tmp = data[0];
			for (size_t i = 1; i < size; ++i) tmp = std::type<type>(tmp, aOther.mData[i]);
			return tmp;
		}

		inline this_t cos() const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = static_cast<T>(std::cos(static_cast<double>(mData[i])));
			return tmp;
		}

		inline this_t sin() const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = static_cast<T>(std::sin(static_cast<double>(mData[i])));
			return tmp;
		}

		inline this_t tan() const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = static_cast<T>(std::tan(static_cast<double>(mData[i])));
			return tmp;
		}

		inline this_t acos() const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = static_cast<T>(std::acos(static_cast<double>(mData[i])));
			return tmp;
		}

		inline this_t asin() const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = static_cast<T>(std::acos(static_cast<double>(mData[i])));
			return tmp;
		}

		inline this_t atan() const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = static_cast<T>(std::acos(static_cast<double>(mData[i])));
			return tmp;
		}

		inline this_t atan2(const Vector<double, size> aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = static_cast<T>(std::atan2(static_cast<double>(mData[i]), aOther[i]));
			return tmp;
		}

		inline this_t exp() const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = static_cast<T>(std::exp(static_cast<double>(mData[i])));
			return tmp;
		}

		inline this_t log() const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = static_cast<T>(std::log(static_cast<double>(mData[i])));
			return tmp;
		}

		inline this_t log10() const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = static_cast<T>(std::log10(static_cast<double>(mData[i])));
			return tmp;
		}

		inline this_t pow(const Vector<double, size> aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = static_cast<T>(std::pow(static_cast<double>(mData[i]), aOther[i]));
			return tmp;
		}

		inline this_t sqrt() const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = static_cast<T>(std::sqrt(static_cast<double>(mData[i])));
			return tmp;
		}

		inline this_t cbrt() const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = static_cast<T>(std::cbrt(static_cast<double>(mData[i])));
			return tmp;
		}

		template<class T2 = type>
		inline typename std::enable_if<std::is_floating_point<T2>::value, this_t>::type ceil() const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = static_cast<T>(std::ceil(static_cast<double>(mData[i])));
			return tmp;
		}

		template<class T2 = type>
		inline typename std::enable_if<!std::is_floating_point<T2>::value, this_t>::type ceil() const throw() {
			return *this;
		}

		template<class T2 = type>
		inline typename std::enable_if<std::is_floating_point<T2>::value, this_t>::type floor() const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = static_cast<T>(std::floor(static_cast<double>(mData[i])));
			return tmp;
		}

		template<class T2 = type>
		inline typename std::enable_if<!std::is_floating_point<T2>::value, this_t>::type floor() const throw() {
			return *this;
		}

		template<class T2 = type>
		inline typename std::enable_if<std::is_floating_point<T2>::value, this_t>::type round() const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = static_cast<T>(std::round(static_cast<double>(mData[i])));
			return tmp;
		}

		template<class T2 = type>
		inline typename std::enable_if<!std::is_floating_point<T2>::value, this_t>::type round() const throw() {
			return *this;
		}

		template<class T2 = type>
		inline typename std::enable_if<!std::is_unsigned<T2>::value, this_t>::type abs() const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = static_cast<T>(std::abs(static_cast<double>(mData[i])));
			return tmp;
		}

		template<class T2 = type>
		inline typename std::enable_if<std::is_unsigned<T2>::value, this_t>::type abs() const throw() {
			return *this;
		}	
		
		inline Vector<size_t, size> popcount() const throw() {
			Vector<size, size_t> tmp;
			for (size_t i = 0; i < size; ++i) tmp[i] = popcount(mData + i, sizeof(type));
			return *this;
		}
	};

	template<Type TYPE>
	using AnvilVector = Vector<typename TypeFromEnum<GetPrimativeType(TYPE)>::type, GetChannels(TYPE)>;

	typedef Vector<uint8_t, 2> Vector8UC2;
	typedef Vector<uint8_t, 3> Vector8UC3;
	typedef Vector<uint8_t, 4> Vector8UC4;
	typedef Vector<uint8_t, 8> Vector8UC8;
	typedef Vector<uint8_t, 16> Vector8UC16;

	typedef Vector<uint16_t, 2> Vector16UC2;
	typedef Vector<uint16_t, 3> Vector16UC3;
	typedef Vector<uint16_t, 4> Vector16UC4;
	typedef Vector<uint16_t, 8> Vector16UC8;

	typedef Vector<uint32_t, 2> Vector32UC2;
	typedef Vector<uint32_t, 3> Vector32UC3;
	typedef Vector<uint32_t, 4> Vector32UC4;

	typedef Vector<uint64_t, 2> Vecto64UC2;
	typedef Vector<uint64_t, 3> Vecto64UC3;
	typedef Vector<uint64_t, 4> Vecto64UC4;

	typedef Vector<int8_t, 2> Vector8SC2;
	typedef Vector<int8_t, 3> Vector8SC3;
	typedef Vector<int8_t, 4> Vector8SC4;
	typedef Vector<int8_t, 8> Vector8SC8;
	typedef Vector<int8_t, 16> Vector8SC16;

	typedef Vector<int16_t, 2> Vector16SC2;
	typedef Vector<int16_t, 3> Vector16SC3;
	typedef Vector<int16_t, 4> Vector16SC4;
	typedef Vector<int16_t, 8> Vector16SC8;

	typedef Vector<int32_t, 2> Vector32SC2;
	typedef Vector<int32_t, 3> Vector32SC3;
	typedef Vector<int32_t, 4> Vector32SC4;

	typedef Vector<int64_t, 2> Vecto64SC2;
	typedef Vector<int64_t, 3> Vecto64SC3;
	typedef Vector<int64_t, 4> Vecto64SC4;

	typedef Vector<float, 2> Vector32FC2;
	typedef Vector<float, 3> Vector32FC3;
	typedef Vector<float, 4> Vector32FC4;

	typedef Vector<double, 2> Vector64FC2;
	typedef Vector<double, 3> Vector64FC3;
	typedef Vector<double, 4> Vector64FC4;
}

#endif