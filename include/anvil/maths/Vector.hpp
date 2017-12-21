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

	namespace detail {
		template<class T>
		static ANVIL_STRONG_INLINE T vmax(T a, T b) {
			return a > b ? a : b;
		}

		template<>
		static ANVIL_STRONG_INLINE float vmax<float>(float a, float b) {
			return std::fmax(a, b);
		}

		template<>
		static ANVIL_STRONG_INLINE double vmax<double>(double a, double b) {
			return std::fmax(a, b);
		}

		template<class T>
		static ANVIL_STRONG_INLINE T vmin(T a, T b) {
			return a > b ? a : b;
		}

		template<>
		static ANVIL_STRONG_INLINE float vmin<float>(float a, float b) {
			return std::fmin(a, b);
		}

		template<>
		static ANVIL_STRONG_INLINE double vmin<double>(double a, double b) {
			return std::fmin(a, b);
		}

		template<class T>
		struct VFloat {
			typedef float type;
		};


		template<>
		struct VFloat<double> {
			typedef double type;
		};

	}

	template<class T, size_t S>
	class Vector {
	public:
		typedef T type;
		enum {
			size = S,
		};
		typedef Vector<type, size> this_t;
		typedef typename detail::VFloat<type>::type float_t;
		typedef type array_t[size];
	private:
		type mData[size];
	public:
		Vector() throw() {
			memset(mData, 0, sizeof(type) * size);
		}

		Vector(const T aScalar) throw() {
			for (size_t i = 0; i < size; ++i) mData[i] = aScalar;
		}

		Vector(const T a, const T b) throw() {
			mData[0] = a;
			mData[1] = b;
			if(size > 2) memset(mData + 2, 0, sizeof(type) * (size - 2));
		}

		Vector(const T a, const T b, const T c) throw() {
			mData[0] = a;
			mData[1] = b;
			mData[2] = c;
			if (size > 3) memset(mData + 3, 0, sizeof(type) * (size - 3));
		}

		Vector(const T a, const T b, const T c, const T d) throw() {
			mData[0] = a;
			mData[1] = b;
			mData[2] = c;
			mData[3] = d;
			if (size > 4) memset(mData + 4, 0, sizeof(type) * (size - 4));
		}

		Vector(const T* aData, size_t aSize) throw() {
			const size_t s = aSize < size ? aSize : size;
			for (size_t i = 0; i < s; ++i) mData[i] = aData[i];
			if (aSize < size) memset(mData + aSize, 0, sizeof(type) * (size - aSize));
		}

		Vector(const array_t aOther) throw() {
			memcpy(mData, aOther, sizeof(type) * size);
		}

		template<class T2>
		Vector(const Vector<T2, size> aOther) throw() {
			for (size_t i = 0; i < size; ++i) mData[i] = static_cast<T>(aOther[i]);
		}

		inline operator bool() const throw() {
			return sum() > static_cast<float32_t>(0.f);
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

		inline float_t sum() const throw() {
			float_t tmp = static_cast<float_t>(0);
			for (size_t i = 0; i < size; ++i) tmp += static_cast<float_t>(mData[i]);
			return tmp;
		}

		inline float_t avg() const throw() {
			return sum() / static_cast<float_t>(size);
		}

		inline type min() const throw() {
			type tmp = data[0];
			for (size_t i = 1; i < size; ++i) tmp = detail::vmin<type>(tmp, aOther.mData[i]);
			return tmp;
		}

		inline type max() const throw() {
			type tmp = data[0];
			for (size_t i = 1; i < size; ++i) tmp = detail::vmax<type>(tmp, aOther.mData[i]);
			return tmp;
		}

		inline float_t dot(const this_t aOther) const throw() {
			float_t sum = static_cast<float>(0);
			if (std::is_same<float_t, type>::value) {
				for (size_t i = 0; i < size; ++i) sum += std::fma(mData[i], aOther.mData[i], sum);
			} else {
				float_t a[size];
				float_t b[size];
				for (size_t i = 0; i < size; ++i) a[i] = static_cast<float_t>(mData[i]);
				for (size_t i = 0; i < size; ++i) b[i] = static_cast<float_t>(aOther.mData[i]);
				for (size_t i = 0; i < size; ++i) sum += std::fma(a[i], b[i], sum);
			}
			return sum;
		}

		template<class T2, size_t S2>
		Vector<type, S2> swizzle(const Vector<T2, S2> aOther) const throw() {
			Vector<type, S2> tmp;
			for (size_t i = 0; i < S2; ++i) tmp[i] = mData[static_cast<size_t>(aOther[i])];
			return tmp;
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