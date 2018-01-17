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
		ANVIL_CALL Vector() throw() {
			memset(mData, 0, sizeof(type) * size);
		}

		ANVIL_CALL Vector(const type aScalar) throw() {
			for (size_t i = 0; i < size; ++i) mData[i] = aScalar;
		}

		template<size_t S2 = 2, class ENABLE = typename std::enable_if<S2 == size>::type>
		ANVIL_CALL Vector(const type a, const type b) throw() {
			mData[0] = a;
			mData[1] = b;
		}

		template<size_t S2 = 3, class ENABLE = typename std::enable_if<S3 == size>::type>
		ANVIL_CALL Vector(const type a, const type b, const type c) throw() {
			mData[0] = a;
			mData[1] = b;
			mData[2] = c;
		}

		template<size_t S2 = 4, class ENABLE = typename std::enable_if<S2 == size>::type>
		ANVIL_CALL Vector(const T a, const T b, const T c, const T d) throw() {
			mData[0] = a;
			mData[1] = b;
			mData[2] = c;
			mData[3] = d;
		}

		ANVIL_CALL Vector(const T* aData, size_t aSize) throw() {
			const size_t s = aSize < size ? aSize : size;
			for (size_t i = 0; i < s; ++i) mData[i] = aData[i];
			if (aSize < size) memset(mData + aSize, 0, sizeof(type) * (size - aSize));
		}

		ANVIL_CALL Vector(const array_t aOther) throw() {
			memcpy(mData, aOther, sizeof(type) * size);
		}
		
		template<size_t SA, size_t SB, class ENABLE = typename std::enable_if<(SA + SB) == size>::type>
		ANVIL_CALL Vector(const Vector<type, SA> a,  Vector<type, SB> b) throw() {
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
		ANVIL_CALL Vector(const Vector<type, SA> a,  Vector<type, SB> b,  Vector<type, SC> c) throw() {
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

		template<class T2, size_t S2>
		explicit ANVIL_CALL operator Vector<T2, S2>() const throw() {
			enum { S3 = size < S2 ? size : S2 };

			Vector<T2, S2> tmp;
			if (std::is_same<type, T2>::value) {
				memcpy(&tmp, this, sizeof(type) * S3);
			} else {
				for (size_t i = 0; i < S3; ++i) tmp[i] = static_cast<T2>(mData[i]);
			}
			return tmp;
		}

		explicit ANVIL_CALL operator bool() const throw() {
			this_t tmp;
			return memcmp(this, &tmp, sizeof(this_t)) != 0;
		}

		inline this_t ANVIL_CALL operator!() const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = !mData[i];
			return tmp;
		}

		template<class T2 = type>
		inline typename std::enable_if<std::is_integral<T2>::value, this_t>::type ANVIL_CALL operator~() const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = ~mData[i];
			return tmp;
		}

		inline this_t ANVIL_CALL operator%(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = mod<type>(mData[i], aOther.mData[i]);
			return tmp;
		}

		inline this_t ANVIL_CALL operator==(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = static_cast<type>(mData[i] == aOther.mData[i]);
			return tmp;
		}

		inline this_t ANVIL_CALL operator!=(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = static_cast<type>(mData[i] != aOther.mData[i]);
			return tmp;
		}

		inline this_t ANVIL_CALL operator<(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = static_cast<type>(mData[i] < aOther.mData[i]);
			return tmp;
		}

		inline this_t ANVIL_CALL operator>(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = static_cast<type>(mData[i] > aOther.mData[i]);
			return tmp;
		}

		inline this_t ANVIL_CALL operator<=(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = static_cast<type>(mData[i] <= aOther.mData[i]);
			return tmp;
		}

		inline this_t ANVIL_CALL operator>=(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = static_cast<type>(mData[i] >= aOther.mData[i]);
			return tmp;
		}

		inline this_t ANVIL_CALL operator+(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = mData[i] + aOther.mData[i];
			return tmp;
		}

		inline this_t ANVIL_CALL operator-(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = mData[i] - aOther.mData[i];
			return tmp;
		}

		inline this_t ANVIL_CALL operator*(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = mData[i] * aOther.mData[i];
			return tmp;
		}

		inline this_t ANVIL_CALL operator/(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = mData[i] / aOther.mData[i];
			return tmp;
		}

		template<class T2 = type>
		inline typename std::enable_if<std::is_integral<T2>::value, this_t>::type ANVIL_CALL operator&(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = mData[i] & aOther.mData[i];
			return tmp;
		}

		template<class T2 = type>
		inline typename std::enable_if<std::is_integral<T2>::value, this_t>::type ANVIL_CALL operator|(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = mData[i] | aOther.mData[i];
			return tmp;
		}

		template<class T2 = type>
		inline typename std::enable_if<std::is_integral<T2>::value, this_t>::type ANVIL_CALL operator^(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = mData[i] ^ aOther.mData[i];
			return tmp;
		}

		template<class T2 = type>
		inline typename std::enable_if<std::is_integral<T2>::value, this_t>::type ANVIL_CALL operator<<(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = mData[i] << aOther.mData[i];
			return tmp;
		}

		template<class T2 = type>
		inline typename std::enable_if<std::is_integral<T2>::value, this_t>::type ANVIL_CALL operator>>(const this_t aOther) const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.mData[i] = mData[i] >> aOther.mData[i];
			return tmp;
		}

		inline this_t& ANVIL_CALL operator+=(const this_t aOther) throw() {
			for (size_t i = 0; i < size; ++i) mData[i] += aOther.mData[i];
			return *this;
		}

		inline this_t& ANVIL_CALL operator-=(const this_t aOther) throw() {
			for (size_t i = 0; i < size; ++i) mData[i] -= aOther.mData[i];
			return *this;
		}

		inline this_t& ANVIL_CALL operator*=(const this_t aOther) throw() {
			for (size_t i = 0; i < size; ++i) mData[i] *= aOther.mData[i];
			return *this;
		}

		inline this_t& ANVIL_CALL operator/=(const this_t aOther) throw() {
			for (size_t i = 0; i < size; ++i) mData[i] /= aOther.mData[i];
			return *this;
		}

		template<class T2 = type>
		inline typename std::enable_if<std::is_integral<T2>::value, this_t&>::type ANVIL_CALL operator&=(const this_t aOther) throw() {
			for (size_t i = 0; i < size; ++i) mData[i] &= aOther.mData[i];
			return *this;
		}

		template<class T2 = type>
		inline typename std::enable_if<std::is_integral<T2>::value, this_t&>::type ANVIL_CALL operator|=(const this_t aOther) throw() {
			for (size_t i = 0; i < size; ++i) mData[i] |= aOther.mData[i];
			return *this;
		}

		template<class T2 = type>
		inline typename std::enable_if<std::is_integral<T2>::value, this_t&>::type ANVIL_CALL operator^=(const this_t aOther) throw() {
			for (size_t i = 0; i < size; ++i) mData[i] ^= aOther.mData[i];
			return *this;
		}

		template<class T2 = type>
		inline typename std::enable_if<std::is_integral<T2>::value, this_t&>::type ANVIL_CALL operator<<=(const this_t aOther) throw() {
			for (size_t i = 0; i < size; ++i) mData[i] <<= aOther.mData[i];
			return *this;
		}

		template<class T2 = type>
		inline typename std::enable_if<std::is_integral<T2>::value, this_t&>::type ANVIL_CALL operator>>=(const this_t aOther) throw() {
			for (size_t i = 0; i < size; ++i) mData[i] >>= aOther.mData[i];
			return *this;
		}

		inline this_t& ANVIL_CALL operator++() throw() {
			this_t tmp(*this);
			for (size_t i = 0; i < size; ++i) ++tmp.mData[i];
			return *this;
		}

		inline this_t& ANVIL_CALL operator--() throw() {
			this_t tmp(*this);
			for (size_t i = 0; i < size; ++i) ++tmp.mData[i];
			return *this;
		}

		inline this_t ANVIL_CALL operator++(int) throw() {
			const this_t tmp(*this);
			for (size_t i = 0; i < size; ++i) ++mData[i];
			return tmp;
		}

		inline this_t ANVIL_CALL operator--(int) throw() {
			const this_t tmp(*this);
			for (size_t i = 0; i < size; ++i) ++mData[i];
			return tmp;
		}

		inline type ANVIL_CALL operator[](const size_t aIndex) const throw() {
			return mData[aIndex];
		}

		inline type& ANVIL_CALL operator[](const size_t aIndex) throw() {
			return mData[aIndex];
		}

		inline const type* ANVIL_CALL begin() const throw() {
			return mData;
		}

		inline type* ANVIL_CALL begin() throw() {
			return mData;
		}

		inline const type* ANVIL_CALL end() const throw() {
			return mData + size;
		}

		inline type* ANVIL_CALL end() throw() {
			return mData + size;
		}

		inline float_t ANVIL_CALL sumf() const throw() {
			float_t tmp = static_cast<float_t>(0);
			for (size_t i = 0; i < size; ++i) tmp += static_cast<float_t>(mData[i]);
			return tmp;
		}

		inline float_t ANVIL_CALL avgf() const throw() {
			return sumf() / static_cast<float_t>(size);
		}

		inline type ANVIL_CALL sum() const throw() {
			return static_cast<type>(sumf());
		}

		inline type ANVIL_CALL avg() const throw() {
			return static_cast<type>(avgf());
		}

		inline type ANVIL_CALL min() const throw() {
			type tmp = mData[0];
			for (size_t i = 1; i < size; ++i) tmp = anvil::min(tmp, mData[i]);
			return tmp;
		}

		inline type ANVIL_CALL max() const throw() {
			type tmp = mData[0];
			for (size_t i = 1; i < size; ++i) tmp = anvil::max(tmp, mData[i]);
			return tmp;
		}

		inline float_t ANVIL_CALL dot(const this_t aOther) const throw() {
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
		inline typename std::enable_if<S2 == 3, this_t>::type ANVIL_CALL cross(const this_t aOther) const throw() {
			const type tmp[3] = {
				(mData[1] * aOther.mData[2]) - (mData[2] * aOther.mData[1]),
				(mData[2] * aOther.mData[0]) - (mData[0] * aOther.mData[2]),
				(mData[0] * aOther.mData[1]) - (mData[1] * aOther.mData[0])
			};
			return this_t(tmp);
		}

		inline float_t ANVIL_CALL mag2f() const throw() {
			if (std::is_same<float_t, type>::value) {
				float_t sum = static_cast<float_t>(0);
				for (size_t i = 0; i < size; ++i) sum = fma(mData[i], mData[i], sum);
				return sum;
			} else {
				return Vector<float_t, size>(*this).mag2();
			}
		}

		inline float_t ANVIL_CALL magf() const throw() {
			return sqrt(mag2f());
		}

		inline type ANVIL_CALL mag2() const throw() {
			return static_cast<type>(mag2f());
		}

		inline type ANVIL_CALL mag() const throw() {
			return static_cast<type>(magf());
		}

		inline Vector<float_t, size> ANVIL_CALL normalisef() const throw() {
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

		inline this_t ANVIL_CALL normalise() const throw() {
			return this_t(normalisef());
		}

		template<class T2, size_t S2>
		Vector<type, S2> ANVIL_CALL swizzle(const Vector<T2, S2> aOther) const throw() {
			Vector<type, S2> tmp;
			for (size_t i = 0; i < S2; ++i) tmp[i] = mData[static_cast<size_t>(aOther[i])];
			return tmp;
		}
	};

	template<class T, size_t S>
	std::ostream& ANVIL_CALL operator<<(std::ostream& aStream, Vector<T, S> aValue) {
		aStream << '[';
		for (size_t i = 0; i < S - 1; ++i) aStream << aValue[i] << ',';
		aStream << aValue[S - 1];
		aStream << ']';
		return aStream;
	}

	template<class T, size_t S>
	std::istream& ANVIL_CALL operator>>(std::istream& aStream, Vector<T, S>& aValue) {
		char buf;
		aStream >> buf;
		for (size_t i = 0; i < S - 1; ++i) aStream >> aValue[i] >> buf;
		aStream >> aValue[S - 1];
		aStream >> buf;
		return aStream;
	}

	template<class T, size_t S>
	inline Vector<T, S> ANVIL_CALL operator+(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) + b;
	}

	template<class T, size_t S>
	inline Vector<T, S> ANVIL_CALL operator-(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) - b;
	}

	template<class T, size_t S>
	inline Vector<T, S> ANVIL_CALL operator*(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) * b;
	}

	template<class T, size_t S>
	inline Vector<T, S> ANVIL_CALL operator/(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) / b;
	}

	template<class T, size_t S>
	inline Vector<T, S> ANVIL_CALL operator&(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) & b;
	}

	template<class T, size_t S>
	inline Vector<T, S> ANVIL_CALL operator|(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) | b;
	}

	template<class T, size_t S>
	inline Vector<T, S> ANVIL_CALL operator^(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) ^ b;
	}

	template<class T, size_t S>
	inline Vector<T, S> ANVIL_CALL operator&&(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) && b;
	}

	template<class T, size_t S>
	inline Vector<T, S> ANVIL_CALL operator||(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) ^ b;
	}

	template<class T, size_t S>
	inline Vector<T, S> ANVIL_CALL operator==(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) == b;
	}

	template<class T, size_t S>
	inline Vector<T, S> ANVIL_CALL operator!=(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) != b;
	}

	template<class T, size_t S>
	inline Vector<T, S> ANVIL_CALL operator<(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) < b;
	}

	template<class T, size_t S>
	inline Vector<T, S> ANVIL_CALL operator>(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) > b;
	}

	template<class T, size_t S>
	inline Vector<T, S> ANVIL_CALL operator<=(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) <= b;
	}

	template<class T, size_t S>
	inline Vector<T, S> ANVIL_CALL operator>=(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) >= b;
	}

	template<class T, size_t S>
	inline Vector<T, S> ANVIL_CALL operator<<(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) << b;
	}

	template<class T, size_t S>
	inline Vector<T, S> ANVIL_CALL operator>>(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) >> b;
	}

	template<class T, size_t S>
	inline Vector<T, S> ANVIL_CALL operator%(const T a, const Vector<T, S> b) {
		return Vector<T, S>(a) % b;
	}

	template<class T, size_t S>
	struct Widen<Vector<T,S>> {
		typedef Vector<typename Widen<T>::type, S> type;
	};

	template<class T, size_t S>
	using VectorP4 = Vector<T, (S + 3) & (~3)>;

	template<Type TYPE>
	using AnvilVector = Vector<typename TypeFromEnum<GetPrimativeType(TYPE)>::type, GetChannels(TYPE)>;

	typedef Vector<signed char, 2> char2;
	typedef Vector<signed char, 3> char3;
	typedef Vector<signed char, 4> char4;
	typedef Vector<unsigned char, 2> uchar2;
	typedef Vector<unsigned char, 3> uchar3;
	typedef Vector<unsigned char, 4> uchar4;
	typedef Vector<short, 2> short2;
	typedef Vector<short, 3> short3;
	typedef Vector<short, 4> short4;
	typedef Vector<unsigned short, 2> ushort2;
	typedef Vector<unsigned short, 3> ushort3;
	typedef Vector<unsigned short, 4> ushort4;
	typedef Vector<int, 2> int2;
	typedef Vector<int, 3> int3;
	typedef Vector<int, 4> int4;
	typedef Vector<unsigned int, 2> uint2;
	typedef Vector<unsigned int, 3> uint3;
	typedef Vector<unsigned int, 4> uint4;
	typedef Vector<float, 2> float2;
	typedef Vector<float, 3> float3;
	typedef Vector<float, 4> float4;
	typedef Vector<double, 2> double2;
	typedef Vector<double, 3> double3;
	typedef Vector<double, 4> double4;

	typedef Vector<uint8_t, 2>  uint8_2;
	typedef Vector<uint8_t, 3>  uint8_3;
	typedef Vector<uint8_t, 4>  uint8_4;
	typedef Vector<uint8_t, 8>  uint8_8;
	typedef Vector<uint8_t, 16> uint8_16;
	typedef Vector<uint8_t, 32> uint8_32;
	typedef Vector<uint8_t, 64> uint8_64;

	typedef Vector<int8_t, 2>  int8_2;
	typedef Vector<int8_t, 3>  int8_3;
	typedef Vector<int8_t, 4>  int8_4;
	typedef Vector<int8_t, 8>  int8_8;
	typedef Vector<int8_t, 16> int8_16;
	typedef Vector<int8_t, 32> int8_32;
	typedef Vector<int8_t, 64> int8_64;

	typedef Vector<uint16_t, 2>  uint16_2;
	typedef Vector<uint16_t, 3>  uint16_3;
	typedef Vector<uint16_t, 4>  uint16_4;
	typedef Vector<uint16_t, 8>  uint16_8;
	typedef Vector<uint16_t, 16> uint16_16;
	typedef Vector<uint16_t, 32> uint16_32;
	typedef Vector<uint16_t, 64> uint16_64;

	typedef Vector<int16_t, 2>  int16_2;
	typedef Vector<int16_t, 3>  int16_3;
	typedef Vector<int16_t, 4>  int16_4;
	typedef Vector<int16_t, 8>  int16_8;
	typedef Vector<int16_t, 16> int16_16;
	typedef Vector<int16_t, 32> int16_32;
	typedef Vector<int16_t, 64> int16_64;

	typedef Vector<uint32_t, 2>  uint32_2;
	typedef Vector<uint32_t, 3>  uint32_3;
	typedef Vector<uint32_t, 4>  uint32_4;
	typedef Vector<uint32_t, 8>  uint32_8;
	typedef Vector<uint32_t, 16> uint32_16;
	typedef Vector<uint32_t, 32> uint32_32;
	typedef Vector<uint32_t, 64> uint32_64;

	typedef Vector<int32_t, 2>  int32_2;
	typedef Vector<int32_t, 3>  int32_3;
	typedef Vector<int32_t, 4>  int32_4;
	typedef Vector<int32_t, 8>  int32_8;
	typedef Vector<int32_t, 16> int32_16;
	typedef Vector<int32_t, 32> int32_32;
	typedef Vector<int32_t, 64> int32_64;

	typedef Vector<uint64_t, 2>  uint64_2;
	typedef Vector<uint64_t, 3>  uint64_3;
	typedef Vector<uint64_t, 4>  uint64_4;
	typedef Vector<uint64_t, 8>  uint64_8;
	typedef Vector<uint64_t, 16> uint64_16;
	typedef Vector<uint64_t, 32> uint64_32;
	typedef Vector<uint64_t, 64> uint64_64;

	typedef Vector<int64_t, 2>  int64_2;
	typedef Vector<int64_t, 3>  int64_3;
	typedef Vector<int64_t, 4>  int64_4;
	typedef Vector<int64_t, 8>  int64_8;
	typedef Vector<int64_t, 16> int64_16;
	typedef Vector<int64_t, 32> int64_32;
	typedef Vector<int64_t, 64> int64_64;

	typedef Vector<float32_t, 2>  float32_2;
	typedef Vector<float32_t, 3>  float32_3;
	typedef Vector<float32_t, 4>  float32_4;
	typedef Vector<float32_t, 8>  float32_8;
	typedef Vector<float32_t, 16> float32_16;
	typedef Vector<float32_t, 32> float32_32;
	typedef Vector<float32_t, 64> float32_64;

	typedef Vector<float64_t, 2>  float64_2;
	typedef Vector<float64_t, 3>  float64_3;
	typedef Vector<float64_t, 4>  float64_4;
	typedef Vector<float64_t, 8>  float64_8;
	typedef Vector<float64_t, 16> float64_16;
	typedef Vector<float64_t, 32> float64_32;
	typedef Vector<float64_t, 64> float64_64;

	// Popcount.hpp overloads

	template<class T, size_t S>
	static inline Vector<size_t, S> ANVIL_CALL popcount(const Vector<T, S> a) {
		Vector<size_t, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = popcount(a[i]);
		return tmp;
	}

	// Reflection.hpp reflect

	template<class T, size_t S>
	static inline Vector<size_t, S> ANVIL_CALL reflect(const Vector<T, S> a) {
		Vector<size_t, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = reflect(a[i]);
		return tmp;
	}

	// Common.hpp overloads

	template<class T, size_t S>
	static inline const Vector<T, S> ANVIL_CALL abs(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = abs(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline const Vector<T, S> ANVIL_CALL mod(const Vector<T, S> a, const Vector<T, S> b) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = mod(a[i], b[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> ANVIL_CALL fma(const Vector<T, S> a, const Vector<T, S> b, const Vector<T, S> c) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = fma(a[i], b[i], c[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> ANVIL_CALL max(const Vector<T, S> a, const Vector<T, S> b) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = max(a[i], b[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> ANVIL_CALL min(const Vector<T, S> a, const Vector<T, S> b) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = min(a[i], b[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> ANVIL_CALL dim(const Vector<T, S> a, const Vector<T, S> b) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = dim(a[i], b[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> ANVIL_CALL exp(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = exp(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> ANVIL_CALL log(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = log(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> ANVIL_CALL log2(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = log2(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> ANVIL_CALL log10(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = log10(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> ANVIL_CALL pow(const Vector<T, S> a, const Vector<T, S> b) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = pow(a[i], b[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> ANVIL_CALL sqrt(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = sqrt(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> ANVIL_CALL cbrt(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = cbrt(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> ANVIL_CALL hypot(const Vector<T, S> a, const Vector<T, S> b) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = hypot(a[i], b[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> ANVIL_CALL sin(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = sin(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> ANVIL_CALL cos(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = cos(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> ANVIL_CALL tan(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = tan(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline const Vector<T, S> ANVIL_CALL asin(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = asin(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline const Vector<T, S> ANVIL_CALL acos(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = acos(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline const Vector<T, S> ANVIL_CALL atan(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = atan(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline const Vector<T, S> ANVIL_CALL atan2(const Vector<T, S> a, const Vector<T, S> b) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = atan2(a[i], b[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> ANVIL_CALL sinh(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = sinh(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> ANVIL_CALL cosh(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = cosh(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> ANVIL_CALL tanh(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = tanh(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline const Vector<T, S> ANVIL_CALL asinh(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = asinh(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline const Vector<T, S> ANVIL_CALL acosh(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = acosh(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline const Vector<T, S> ANVIL_CALL atanh(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = atanh(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> ANVIL_CALL ceil(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = ceil(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> ANVIL_CALL floor(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = floor(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> ANVIL_CALL trunc(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = trunc(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> ANVIL_CALL round(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = round(a[i]);
		return tmp;
	}
}

#endif