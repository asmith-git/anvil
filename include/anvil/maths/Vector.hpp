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

#include <iostream>
#include "anvil/maths/Type.hpp"
#include "anvil/maths/Popcount.hpp"
#include "anvil/maths/Reflection.hpp"
#include "anvil/maths/Common.hpp"

namespace anvil {

	namespace detail {
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

		Vector(const type aScalar) throw() {
			for (size_t i = 0; i < size; ++i) mData[i] = aScalar;
		}

		template<size_t S2 = 2, class ENABLE = typename std::enable_if<S2 == size>::type>
		Vector(const type a, const type b) throw() {
			mData[0] = a;
			mData[1] = b;
		}

		template<size_t S2 = 3, class ENABLE = typename std::enable_if<S3 == size>::type>
		Vector(const type a, const type b, const type c) throw() {
			mData[0] = a;
			mData[1] = b;
			mData[2] = c;
		}

		template<size_t S2 = 4, class ENABLE = typename std::enable_if<S2 == size>::type>
		Vector(const T a, const T b, const T c, const T d) throw() {
			mData[0] = a;
			mData[1] = b;
			mData[2] = c;
			mData[3] = d;
		}

		Vector(const T* aData, size_t aSize) throw() {
			const size_t s = aSize < size ? aSize : size;
			for (size_t i = 0; i < s; ++i) mData[i] = aData[i];
			if (aSize < size) memset(mData + aSize, 0, sizeof(type) * (size - aSize));
		}

		Vector(const array_t aOther) throw() {
			memcpy(mData, aOther, sizeof(type) * size);
		}

		template<class T2, size_t S2>
		explicit Vector(const Vector<T2, S2> aOther) throw() {
			enum {
				S3 = size < S2 ? size : S2
			};
			if (std::is_same<type, T2>::value) {
				memcpy(mData, &aOther, sizeof(type) * S3);
			} else {
				for (size_t i = 0; i < S3; ++i) mData[i] = static_cast<T>(aOther[i]);
			}
		}
		
		template<size_t SA, size_t SB, class ENABLE = typename std::enable_if<(SA + SB) == size>::type>
		Vector(const Vector<type, SA> a, const const Vector<type, SB> b) throw() {
			type* ptr = mData;
			size_t s1 = sizeof(type) * size;
			size_t s2 = std::min(s1, sizeof(type) * SA);
			memcpy(ptr, &a, s2);
			ptr += s2 / sizeof(type);
			s1 -= s2; 
			
			s2 = std::min(s1, sizeof(type) * SB);
			memcpy(ptr, &b, s2);
			ptr += s2 / sizeof(type);
			s1 = s1 > s2 ? s1 - s2 : 0;
			
			memset(ptr, 0, sizeof(type) * s1);
		}

		template<size_t SA, size_t SB, size_t SC, class ENABLE = typename std::enable_if<(SA + SB + SC) == size>::type>
		Vector(const Vector<type, SA> a, const const Vector<type, SB> b, const const Vector<type, SC> c) throw() {
			type* ptr = mData;
			size_t s1 = sizeof(type) * size;
			size_t s2 = std::min(s1, sizeof(type) * SA);
			memcpy(ptr, &a, s2);
			ptr += s2 / sizeof(type);
			s1 -= s2;

			s2 = std::min(s1, sizeof(type) * SB);
			memcpy(ptr, &b, s2);
			ptr += s2 / sizeof(type);
			s1 -= s2;

			s2 = std::min(s1, sizeof(type) * SC);
			memcpy(ptr, &c, s2);
			ptr += s2 / sizeof(type);
			s1 -= s2;

			memset(ptr, 0, sizeof(type) * s1);
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
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = mod<type>(mData[i], aOther.mData[i]);
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

		inline this_t& operator++() throw() {
			this_t tmp(*this);
			for (size_t i = 0; i < size; ++i) ++tmp.mData[i];
			return *this;
		}

		inline this_t& operator--() throw() {
			this_t tmp(*this);
			for (size_t i = 0; i < size; ++i) ++tmp.mData[i];
			return *this;
		}

		inline this_t operator++(int) throw() {
			const this_t tmp(*this);
			for (size_t i = 0; i < size; ++i) ++mData[i];
			return tmp;
		}

		inline this_t operator--(int) throw() {
			const this_t tmp(*this);
			for (size_t i = 0; i < size; ++i) ++mData[i];
			return tmp;
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
			type tmp = mData[0];
			for (size_t i = 1; i < size; ++i) tmp = anvil::min(tmp, mData[i]);
			return tmp;
		}

		inline type max() const throw() {
			type tmp = mData[0];
			for (size_t i = 1; i < size; ++i) tmp = anvil::max(tmp, mData[i]);
			return tmp;
		}

		inline float_t dot(const this_t aOther) const throw() {
			if (std::is_same<float_t, type>::value) {
				float_t sum = static_cast<float_t>(0);
				for (size_t i = 0; i < size; ++i) sum = fma(mData[i], aOther.mData[i], sum);
				return sum;
			} else {
				Vector<float_t, size> a(*this);
				Vector<float_t, size> b(aOther);
				return a.dot(b);
			}
		}

		template<size_t S2 = size>
		inline typename std::enable_if<S2 == 3, this_t>::type cross(const this_t aOther) const throw() {
			const type tmp[3] = {
				(mData[1] * aOther.mData[2]) - (mData[2] * aOther.mData[1]),
				(mData[2] * aOther.mData[0]) - (mData[0] * aOther.mData[2]),
				(mData[0] * aOther.mData[1]) - (mData[1] * aOther.mData[0])
			};
			return this_t(tmp);
		}

		inline float_t mag2() const throw() {
			if (std::is_same<float_t, type>::value) {
				float_t sum = static_cast<float_t>(0);
				for (size_t i = 0; i < size; ++i) sum = fma(mData[i], mData[i], sum);
				return sum;
			} else {
				return Vector<float_t, size>(*this).mag2();
			}
		}

		inline float_t mag() const throw() {
			return sqrt(mag2());
		}

		inline Vector<float_t, size> normalisef() const throw() {
			if (std::is_same<float_t, type>::value) {
				float_t mag = static_cast<float_t>(0);
				Vector<float_t, size> tmp;
				for (size_t i = 0; i < size; ++i) {
					tmp[i] = mData[i] * mData[i];
					mag += tmp[i];
				}
				tmp /= mag;
				return tmp;
			} else {
				return Vector<float_t, size>(*this).normalisef();
			}
		}

		inline this_t normalise() const throw() {
			return this_t(normalisef());
		}

		template<class T2, size_t S2>
		Vector<type, S2> swizzle(const Vector<T2, S2> aOther) const throw() {
			Vector<type, S2> tmp;
			for (size_t i = 0; i < S2; ++i) tmp[i] = mData[static_cast<size_t>(aOther[i])];
			return tmp;
		}
	};

	template<class T, size_t S>
	std::ostream& operator<<(std::ostream& aStream, Vector<T, S> aValue) {
		aStream << '[';
		for (size_t i = 0; i < S - 1; ++i) aStream << aValue[i] << ',';
		aStream << aValue[S - 1];
		aStream << ']';
		return aStream;
	}

	template<class T, size_t S>
	std::istream& operator>>(std::istream& aStream, Vector<T, S>& aValue) {
		char buf;
		aStream >> buf;
		for (size_t i = 0; i < S - 1; ++i) aStream >> aValue[i] >> buf;
		aStream >> aValue[S - 1];
		aStream >> buf;
		return aStream;
	}

	template<class T, size_t S>
	inline Vector<T, S> operator+(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) + b;
	}

	template<class T, size_t S>
	inline Vector<T, S> operator-(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) - b;
	}

	template<class T, size_t S>
	inline Vector<T, S> operator*(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) * b;
	}

	template<class T, size_t S>
	inline Vector<T, S> operator/(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) / b;
	}

	template<class T, size_t S>
	inline Vector<T, S> operator&(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) & b;
	}

	template<class T, size_t S>
	inline Vector<T, S> operator|(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) | b;
	}

	template<class T, size_t S>
	inline Vector<T, S> operator^(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) ^ b;
	}

	template<class T, size_t S>
	inline Vector<T, S> operator&&(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) && b;
	}

	template<class T, size_t S>
	inline Vector<T, S> operator||(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) ^ b;
	}

	template<class T, size_t S>
	inline Vector<T, S> operator==(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) == b;
	}

	template<class T, size_t S>
	inline Vector<T, S> operator!=(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) != b;
	}

	template<class T, size_t S>
	inline Vector<T, S> operator<(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) < b;
	}

	template<class T, size_t S>
	inline Vector<T, S> operator>(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) > b;
	}

	template<class T, size_t S>
	inline Vector<T, S> operator<=(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) <= b;
	}

	template<class T, size_t S>
	inline Vector<T, S> operator>=(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) >= b;
	}

	template<class T, size_t S>
	inline Vector<T, S> operator<<(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) << b;
	}

	template<class T, size_t S>
	inline Vector<T, S> operator>>(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) >> b;
	}

	template<class T, size_t S>
	inline Vector<T, S> operator%(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) % b;
	}

	template<Type TYPE>
	using AnvilVector = Vector<typename TypeFromEnum<GetPrimativeType(TYPE)>::type, GetChannels(TYPE)>;

	typedef Vector<uint8_t, 2> Vector8UC2;
	typedef Vector<uint8_t, 3> Vector8UC3;
	typedef Vector<uint8_t, 4> Vector8UC4;
	typedef Vector<uint8_t, 8> Vector8UC8;
	typedef Vector<uint8_t, 16> Vector8UC16;
	typedef Vector<uint8_t, 32> Vector8UC32;
	typedef Vector<uint8_t, 64> Vector8UC64;

	typedef Vector<int8_t, 2> Vector8SC2;
	typedef Vector<int8_t, 3> Vector8SC3;
	typedef Vector<int8_t, 4> Vector8SC4;
	typedef Vector<int8_t, 8> Vector8SC8;
	typedef Vector<int8_t, 16> Vector8SC16;
	typedef Vector<int8_t, 32> Vector8SC32;
	typedef Vector<int8_t, 64> Vector8SC64;

	typedef Vector<uint16_t, 2> Vector16UC2;
	typedef Vector<uint16_t, 3> Vector16UC3;
	typedef Vector<uint16_t, 4> Vector16UC4;
	typedef Vector<uint16_t, 8> Vector16UC8;
	typedef Vector<uint16_t, 16> Vector16UC16;
	typedef Vector<uint16_t, 32> Vector16UC32;
	typedef Vector<uint16_t, 64> Vector16UC64;

	typedef Vector<int16_t, 2> Vector16SC2;
	typedef Vector<int16_t, 3> Vector16SC3;
	typedef Vector<int16_t, 4> Vector16SC4;
	typedef Vector<int16_t, 8> Vector16SC8;
	typedef Vector<int16_t, 16> Vector16SC16;
	typedef Vector<int16_t, 32> Vector16SC32;
	typedef Vector<int16_t, 64> Vector16SC64;

	typedef Vector<uint32_t, 2> Vector32UC2;
	typedef Vector<uint32_t, 3> Vector32UC3;
	typedef Vector<uint32_t, 4> Vector32UC4;
	typedef Vector<uint32_t, 8> Vector32UC8;
	typedef Vector<uint32_t, 16> Vector32UC16;
	typedef Vector<uint32_t, 32> Vector32UC32;
	typedef Vector<uint32_t, 64> Vector32UC64;

	typedef Vector<int32_t, 2> Vector32SC2;
	typedef Vector<int32_t, 3> Vector32SC3;
	typedef Vector<int32_t, 4> Vector32SC4;
	typedef Vector<int32_t, 8> Vector32SC8;
	typedef Vector<int32_t, 16> Vector32SC16;
	typedef Vector<int32_t, 32> Vector32SC32;
	typedef Vector<int32_t, 64> Vector32SC64;

	typedef Vector<uint64_t, 2> Vector64UC2;
	typedef Vector<uint64_t, 3> Vector64UC3;
	typedef Vector<uint64_t, 4> Vector64UC4;
	typedef Vector<uint64_t, 8> Vector64UC8;
	typedef Vector<uint64_t, 16> Vector64UC16;
	typedef Vector<uint64_t, 32> Vector64UC32;
	typedef Vector<uint64_t, 64> Vector64UC64;

	typedef Vector<int64_t, 2> Vector64SC2;
	typedef Vector<int64_t, 3> Vector64SC3;
	typedef Vector<int64_t, 4> Vector64SC4;
	typedef Vector<int64_t, 8> Vector64SC8;
	typedef Vector<int64_t, 16> Vector64SC16;
	typedef Vector<int64_t, 32> Vector64SC32;
	typedef Vector<int64_t, 64> Vector64SC64;

	typedef Vector<float32_t, 2> Vector32FC2;
	typedef Vector<float32_t, 3> Vector32FC3;
	typedef Vector<float32_t, 4> Vector32FC4;
	typedef Vector<float32_t, 8> Vector32FC8;
	typedef Vector<float32_t, 16> Vector32FC16;
	typedef Vector<float32_t, 32> Vector32FC32;
	typedef Vector<float32_t, 64> Vector32FC64;

	typedef Vector<float64_t, 2> Vector64FC2;
	typedef Vector<float64_t, 3> Vector64FC3;
	typedef Vector<float64_t, 4> Vector64FC4;
	typedef Vector<float64_t, 8> Vector64FC8;
	typedef Vector<float64_t, 16> Vector64FC16;
	typedef Vector<float64_t, 32> Vector64FC32;
	typedef Vector<float64_t, 64> Vector64FC64;

	// Popcount.hpp overloads

	template<class T, size_t S>
	static inline Vector<size_t, S> popcount(const Vector<T, S> a) {
		Vector<size_t, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = popcount(a[i]);
		return tmp;
	}

	// Reflection.hpp reflect

	template<class T, size_t S>
	static inline Vector<size_t, S> reflect(const Vector<T, S> a) {
		Vector<size_t, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = reflect(a[i]);
		return tmp;
	}

	// Common.hpp overloads

	template<class T, size_t S>
	static inline const Vector<T, S> abs(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = abs(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline const Vector<T, S> abs(const Vector<T, S> a, const Vector<T, S> b) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = mod(a[i], b[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> fma(const Vector<T, S> a, const Vector<T, S> b, const Vector<T, S> c) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = fma(a[i], b[i], c[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> max(const Vector<T, S> a, const Vector<T, S> b) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = max(a[i], b[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> min(const Vector<T, S> a, const Vector<T, S> b) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = min(a[i], b[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> dif(const Vector<T, S> a, const Vector<T, S> b) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = dif(a[i], b[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> exp(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = exp(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> log(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = log(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> log2(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = log2(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> log10(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = log10(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> pow(const Vector<T, S> a, const Vector<T, S> b) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = pow(a[i], b[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> sqrt(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = sqrt(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> cbrt(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = cbrt(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> hypot(const Vector<T, S> a, const Vector<T, S> b) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = hypot(a[i], b[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> sin(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = sin(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> cos(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = cos(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> tan(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = tan(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline const Vector<T, S> asin(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = asin(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline const Vector<T, S> acos(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = acos(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline const Vector<T, S> atan(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = atan(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline const Vector<T, S> atan2(const Vector<T, S> a, const Vector<T, S> b) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = atan2(a[i], b[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> sinh(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = sinh(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> cosh(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = cosh(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> tanh(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = tanh(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline const Vector<T, S> asinh(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = asinh(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline const Vector<T, S> acosh(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = acosh(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline const Vector<T, S> atanh(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = atanh(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> ceil(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = ceil(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> floor(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = floor(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> trunc(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = trunc(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> round(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = round(a[i]);
		return tmp;
	}
}

#endif