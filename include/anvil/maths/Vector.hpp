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

#ifdef ANVIL_AVX_512
	#define ANVIL_AVX2
	//#include ?
#endif

#ifdef ANVIL_AVX2
	#define ANVIL_AVX
	//#include <zmmintrin.h>
#endif

#ifdef ANVIL_AVX
	#define ANVIL_SSE4_2
	#define ANVIL_FMA
	#include <immintrin.h>
#endif

#ifdef ANVIL_SSE4_2
	#define ANVIL_SSE4_1
	#include <nmmintrin.h>
#endif

#ifdef ANVIL_SSE4_1
	#define ANVIL_SSE3
	#include <smmintrin.h>
#endif

#ifdef ANVIL_SSE3
	#define ANVIL_SSSE3
	#include <tmmintrin.h>
#endif

#ifdef ANVIL_SSSE3
	#define ANVIL_SSE2
	#include <pmmintrin.h>
#endif

#ifdef ANVIL_SSE2
	#define ANVIL_SSE
	#include <emmintrin.h>
#endif

#ifdef ANVIL_SSE
	#define ANVIL_MMX
	#include <xmmintrin.h>
#endif

#ifdef ANVIL_MMX
	#include <mmintrin.h>
#endif

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

		enum VectorOp {
			VOP_ADD,   VOP_SUB,    VOP_MUL,   VOP_DIV,
			VOP_MIN,   VOP_MAX,    VOP_LSH,   VOP_RSH,
			VOP_ABS,   VOP_FMA,    VOP_FMS,   VOP_AVG,
			VOP_SUM,   VOP_EQ,     VOP_NE,    VOP_LE,
			VOP_GE,    VOP_LT,     VOP_GT,    VOP_AND,
			VOP_OR,    VOP_XOR,    VOP_NOT,   VOP_SQRT,
			VOP_SIN,   VOP_COS,    VOP_TAN,   VOP_ASIN,
			VOP_ACOS,  VOP_ATAN,   VOP_PCN,   VOP_REF,
			VOP_MOD,   VOP_DIM,    VOP_EXP,   VOP_LOG,
			VOP_LOG2,  VOP_LOG10,  VOP_POW,   VOP_CBRT,
			VOP_HYPOT, VOP_ATAN2,  VOP_CONSH, VOP_SINH,
			VOP_TANH,  VOP_ACONSH, VOP_ASINH, VOP_ATANH, 
			VOP_CIEL,  VOP_FLOOR,  VOP_TRUNC, VOP_ROUND
		};

		template<class T, size_t S, VectorOp VOP>
		struct VopOptimised {
			enum { value = 0 };
		};

		template<class T, VectorOp VOP>
		struct OptimalVectorLength {
			enum {
				value =
				VopOptimised<T, 64, VOP>::value ? 64 :
				VopOptimised<T, 32, VOP>::value ? 32 :
				VopOptimised<T, 16, VOP>::value ? 16 :
				VopOptimised<T, 8, VOP>::value ? 8 :
				VopOptimised<T, 4, VOP>::value ? 4 :
				VopOptimised<T, 2, VOP>::value ? 2 :
				1
			};
		};

		template<class T, int S, VectorOp VOP>
		struct RoundVectorLength { 
			enum { 
				value = 
				VopOptimised<T, 2, VOP>::value && S <= 2 ? 2 :
				VopOptimised<T, 4, VOP>::value && S <= 4 ? 4 :
				VopOptimised<T, 8, VOP>::value && S <= 8 ? 8 :
				VopOptimised<T, 16, VOP>::value && S <= 16 ? 16 :
				VopOptimised<T, 32, VOP>::value && S <= 32 ? 32 :
				VopOptimised<T, 64, VOP>::value && S <= 64 ? 64 :
				S
			}; 
		};
	}

	template<class T = float, size_t S = detail::OptimalVectorLength<T>::value>
	class Vector {
	public:
		typedef T type;
		enum {
			size = S,
		};
		typedef Vector<type, size> this_t;
		typedef Vector<type, size / 2> half_t;
		typedef typename detail::VFloat<type>::type float_t;
		typedef type array_t[size];
	private:
		type mData[size];
	public:
		//ANVIL_CALL Vector() throw() {
		//	memset(mData, 0, sizeof(type) * size);
		//}

		//ANVIL_CALL Vector(const type aScalar) throw() {
		//	for (size_t i = 0; i < size; ++i) mData[i] = aScalar;
		//}

		//template<size_t S2 = 2, class ENABLE = typename std::enable_if<S2 == size>::type>
		//ANVIL_CALL Vector(const type a, const type b) throw() {
		//	mData[0] = a;
		//	mData[1] = b;
		//}

		//template<size_t S2 = 3, class ENABLE = typename std::enable_if<S3 == size>::type>
		//ANVIL_CALL Vector(const type a, const type b, const type c) throw() {
		//	mData[0] = a;
		//	mData[1] = b;
		//	mData[2] = c;
		//}

		//template<size_t S2 = 4, class ENABLE = typename std::enable_if<S2 == size>::type>
		//ANVIL_CALL Vector(const T a, const T b, const T c, const T d) throw() {
		//	mData[0] = a;
		//	mData[1] = b;
		//	mData[2] = c;
		//	mData[3] = d;
		//}

		//ANVIL_CALL Vector(const T* aData, size_t aSize) throw() {
		//	const size_t s = aSize < size ? aSize : size;
		//	for (size_t i = 0; i < s; ++i) mData[i] = aData[i];
		//	if (aSize < size) memset(mData + aSize, 0, sizeof(type) * (size - aSize));
		//}

		//ANVIL_CALL Vector(const array_t aOther) throw() {
		//	memcpy(mData, aOther, sizeof(type) * size);
		//}
		//
		//template<size_t SA, size_t SB, class ENABLE = typename std::enable_if<(SA + SB) == size>::type>
		//ANVIL_CALL Vector(const Vector<type, SA> a,  Vector<type, SB> b) throw() {
		//	type* ptr = mData;
		//	size_t s1 = sizeof(type) * size;
		//	size_t s2 = std::min(s1, sizeof(type) * SA);
		//	memcpy(ptr, &a, s2);
		//	ptr += s2 / sizeof(type);
		//	s1 -= s2; 
		//	
		//	s2 = std::min(s1, sizeof(type) * SB);
		//	memcpy(ptr, &b, s2);
		//	ptr += s2 / sizeof(type);
		//	s1 = s1 > s2 ? s1 - s2 : 0;
		//	
		//	memset(ptr, 0, sizeof(type) * s1);
		//}

		//template<size_t SA, size_t SB, size_t SC, class ENABLE = typename std::enable_if<(SA + SB + SC) == size>::type>
		//ANVIL_CALL Vector(const Vector<type, SA> a,  Vector<type, SB> b,  Vector<type, SC> c) throw() {
		//	type* ptr = mData;
		//	size_t s1 = sizeof(type) * size;
		//	size_t s2 = std::min(s1, sizeof(type) * SA);
		//	memcpy(ptr, &a, s2);
		//	ptr += s2 / sizeof(type);
		//	s1 -= s2;

		//	s2 = std::min(s1, sizeof(type) * SB);
		//	memcpy(ptr, &b, s2);
		//	ptr += s2 / sizeof(type);
		//	s1 -= s2;

		//	s2 = std::min(s1, sizeof(type) * SC);
		//	memcpy(ptr, &c, s2);
		//	ptr += s2 / sizeof(type);
		//	s1 -= s2;

		//	memset(ptr, 0, sizeof(type) * s1);
		//}

		ANVIL_STRONG_INLINE half_t& lowerHalf() throw() {
			return reinterpret_cast<half_t*>(this)[0];
		}

		ANVIL_STRONG_INLINE half_t& upperHalf() throw() {
			return reinterpret_cast<half_t*>(this)[1];
		}

		ANVIL_STRONG_INLINE half_t lowerHalf() const throw() {
			return reinterpret_cast<const half_t*>(this)[0];
		}

		ANVIL_STRONG_INLINE half_t upperHalf() const throw() {
			return reinterpret_cast<const half_t*>(this)[1];
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
			*this += fill<type, size>(static_cast<type>(1));
			return *this;
		}

		inline this_t& ANVIL_CALL operator--() throw() {
			*this -= fill<type, size>(static_cast<type>(1));
			return *this;
		}

		inline this_t ANVIL_CALL operator++(int) throw() {
			const this_t tmp(*this);
			*this += fill<type, size>(static_cast<type>(1));
			return tmp;
		}

		inline this_t ANVIL_CALL operator--(int) throw() {
			const this_t tmp(*this);
			*this -= fill<type, size>(static_cast<type>(1));
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
			enum { HALF_OPTIMISED = size > 2 && detail::VopOptimised<half_t::type, half_t::size, detail::VOP_ADD>::value };
			if (HALF_OPTIMISED) {
				return (lowerHalf() + upperHalf()).sumf();
			} else {
				type tmp = mData[0];
				for (size_t i = 1; i < size; ++i) tmp += mData[i];
				return tmp;
			}
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
			enum { HALF_OPTIMISED = size > 2 && detail::VopOptimised<half_t::type, half_t::size, detail::VOP_MIN>::value };
			if (HALF_OPTIMISED) {
				return anvil::min<half_t::type, half_t::size>(lowerHalf(), upperHalf()).min();
			} else {
				type tmp = mData[0];
				for (size_t i = 1; i < size; ++i) tmp = anvil::min(tmp, mData[i]);
				return tmp;
			}
		}

		inline type ANVIL_CALL max() const throw() {
			enum { HALF_OPTIMISED = size > 2 && detail::VopOptimised<half_t::type, half_t::size, detail::VOP_MAX>::value };
			if (HALF_OPTIMISED) {
				return anvil::max<half_t::type, half_t::size>(lowerHalf(), upperHalf()).max();
			} else {
				type tmp = mData[0];
				for (size_t i = 1; i < size; ++i) tmp = anvil::max(tmp, mData[i]);
				return tmp;
			}
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

	////

	namespace detail {
		template<class T, int S, VectorOp OP>
		union RoundedVector {
			Vector<T, S> unrounded;
			Vector<T, RoundVectorLength<T, S, OP>::value> rounded;
		};

		template<class T, size_t S>
		union VectorPtr {
			Vector<T, S>* vector;
			T* scalar;
		};
	}

#define ANVIL_VECTOR_OP_EQ(VOP,SYMBOL)\
	template<class T, size_t S>\
	Vector<T, S>& ANVIL_CALL operator ## SYMBOL(Vector<T, S>& a, const Vector<T, S> b) throw() {\
		enum { OPTIMAL = detail::OptimalVectorLength<T, VOP>::value };\
		if(OPTIMAL < S && OPTIMAL > 1){\
			enum {\
				LOOP1 = S / OPTIMAL,\
				LOOP2 = S % OPTIMAL\
				};\
			size_t a_length = S;\
			detail::VectorPtr<T, OPTIMAL> a_, b_;\
			\
			a_.scalar = reinterpret_cast<T*>(&a);\
			b_.scalar = const_cast<T*>(reinterpret_cast<const T*>(&b));\
			\
			for(int i = 0; i < LOOP1; ++i) {\
				a_.vector[i] SYMBOL b_.vector[i];\
			}\
			a_.vector += LOOP1;\
			b_.vector += LOOP1;\
			\
			for (int i = 0; i < LOOP2; ++i) {\
				a_.scalar[i] SYMBOL b_.scalar[i];\
			}\
		} else if(OPTIMAL > S) {\
			detail::RoundedVector<T, S, VOP> a_, b_;\
			memcpy(&a_, &a, sizeof(a));\
			memcpy(&b_, &b, sizeof(b));\
			a_.rounded SYMBOL b_.rounded;\
			a = a_.unrounded;\
		} else {\
			for (size_t i = 0; i < S; ++i) a[i] SYMBOL b[i];\
		}\
		return a;\
	}

#define ANVIL_VECTOR_OP(VOP, SYMBOL)\
	template<class T, size_t S>\
	Vector<T,S> ANVIL_CALL operator ## SYMBOL(const Vector<T,S> a, const Vector<T,S> b) throw() {\
		Vector<T, S> c;\
		enum { OPTIMAL = detail::OptimalVectorLength<T, VOP>::value };\
		if(OPTIMAL < S && OPTIMAL > 1){\
			enum {\
				LOOP1 = S / OPTIMAL,\
				LOOP2 = S % OPTIMAL\
			};\
			size_t a_length = S;\
			detail::VectorPtr<T, OPTIMAL> a_, b_, c_;\
			\
			a_.scalar = const_cast<T*>(reinterpret_cast<const T*>(&a));\
			b_.scalar = const_cast<T*>(reinterpret_cast<const T*>(&b));\
			c_.scalar = reinterpret_cast<T*>(&c);\
			\
			for(int i = 0; i < LOOP1; ++i) {\
				c_.vector[i] = a_.vector[i] SYMBOL b_.vector[i];\
			}\
			a_.vector += LOOP1;\
			b_.vector += LOOP1;\
			c_.vector += LOOP1;\
			\
			for (int i = 0; i < LOOP2; ++i) {\
				c_.scalar[i] = a_.scalar[i] SYMBOL b_.scalar[i];\
			}\
		} else if(OPTIMAL > S) {\
			detail::RoundedVector<T, S, VOP> a_, b_, c_;\
			memcpy(&a_, &a, sizeof(a));\
			memcpy(&b_, &b, sizeof(b));\
			c_.rounded = a_.rounded SYMBOL b_.rounded;\
			c = c_.unrounded;\
		} else {\
			for (size_t i = 0; i < S; ++i) c[i] = a[i] SYMBOL b[i];\
		}\
		return c;\
	}

	ANVIL_VECTOR_OP(detail::VOP_ADD, +)
	ANVIL_VECTOR_OP(detail::VOP_SUB, -)
	ANVIL_VECTOR_OP(detail::VOP_MUL, *)
	ANVIL_VECTOR_OP(detail::VOP_DIV, /)
	ANVIL_VECTOR_OP(detail::VOP_AND, &)
	ANVIL_VECTOR_OP(detail::VOP_OR , |)
	ANVIL_VECTOR_OP(detail::VOP_XOR, ^)

	ANVIL_VECTOR_OP_EQ(detail::VOP_ADD, +=)
	ANVIL_VECTOR_OP_EQ(detail::VOP_SUB, -=)
	ANVIL_VECTOR_OP_EQ(detail::VOP_MUL, *=)
	ANVIL_VECTOR_OP_EQ(detail::VOP_DIV, /=)
	ANVIL_VECTOR_OP_EQ(detail::VOP_AND, &=)
	ANVIL_VECTOR_OP_EQ(detail::VOP_OR , |=)
	ANVIL_VECTOR_OP_EQ(detail::VOP_XOR, ^=)

	ANVIL_VECTOR_OP(detail::VOP_EQ, ==)
	ANVIL_VECTOR_OP(detail::VOP_NE, !=)
	ANVIL_VECTOR_OP(detail::VOP_LT, <)
	ANVIL_VECTOR_OP(detail::VOP_GT, >)
	ANVIL_VECTOR_OP(detail::VOP_LE, <=)
	ANVIL_VECTOR_OP(detail::VOP_GE, >=)
	
	template<class T, size_t S>
	static inline Vector<T, S> ANVIL_CALL fill(const T a) {
		Vector<T, S> b;
		for (size_t i = 0; i < S; ++i) b[i] = a;
		return b;
	}

	template<class T, size_t S>
	static inline Vector<T, S> ANVIL_CALL fill(const T* a, size_t a_length) {
		Vector<T, S> b;
		for (size_t i = 0; i < a_length; ++i) b[i] = a[i];
		for (size_t i = a_length; i < S; ++i) b[i] = static_cast<T>(0);
		return b;
	}

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
	static inline Vector<T, S> ANVIL_CALL abs(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = abs(a[i]);
		return tmp;
	}

	template<class T, size_t S>
	static inline Vector<T, S> ANVIL_CALL mod(const Vector<T, S> a, const Vector<T, S> b) {
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
	static inline Vector<T, S> ANVIL_CALL fms(const Vector<T, S> a, const Vector<T, S> b, const Vector<T, S> c) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = fms(a[i], b[i], c[i]);
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

	// Instruction set optimisations

	namespace detail{

#ifdef ANVIL_MMX
		union Vec_F32_2 {
			Vector<float, 2> vector;
			__m64 intrinsic;
		};

		union Vec_S8_8 {
			Vector<int8_t, 8> vector;
			__m64 intrinsic;
		};

		union Vec_U8_8 {
			Vector<uint8_t, 8> vector;
			__m64 intrinsic;
		};

		union Vec_S16_4 {
			Vector<int16_t, 4> vector;
			__m64 intrinsic;
		};

		union Vec_U16_4 {
			Vector<uint16_t, 4> vector;
			__m64 intrinsic;
		};

		union Vec_S32_2 {
			Vector<int32_t, 2> vector;
			__m64 intrinsic;
		};

		union Vec_U32_2 {
			Vector<uint32_t, 2> vector;
			__m64 intrinsic;
		};
#endif
#ifdef ANVIL_SSE
		union Vec_F32_4 {
			Vector<float, 4> vector;
			__m128 intrinsic;
		};
#endif
#ifdef ANVIL_SSE2
		union Vec_S8_16 {
			Vector<int8_t, 16> vector;
			__m128i intrinsic;
		};

		union Vec_U8_16 {
			Vector<uint8_t, 16> vector;
			__m128i intrinsic;
		};

		union Vec_S16_8 {
			Vector<int16_t, 8> vector;
			__m128i intrinsic;
		};

		union Vec_U16_8 {
			Vector<uint16_t, 8> vector;
			__m128i intrinsic;
		};

		union Vec_S32_4 {
			Vector<int32_t, 4> vector;
			__m128i intrinsic;
		};

		union Vec_U32_4 {
			Vector<uint32_t, 4> vector;
			__m128i intrinsic;
		};

		union Vec_S64_2 {
			Vector<int64_t, 2> vector;
			__m128i intrinsic;
		};

		union Vec_U64_2 {
			Vector<uint64_t, 2> vector;
			__m128i intrinsic;
		};

		union Vec_F64_2 {
			Vector<double, 2> vector;
			__m128d intrinsic;
		};
#endif
#ifdef ANVIL_AVX
		union Vec_S8_32 {
			Vector<int8_t, 32> vector;
			__m256i intrinsic;
		};

		union Vec_U8_32 {
			Vector<uint8_t, 32> vector;
			__m256i intrinsic;
		};

		union Vec_S16_16 {
			Vector<int16_t, 16> vector;
			__m256i intrinsic;
		};

		union Vec_U16_16 {
			Vector<uint16_t, 16> vector;
			__m256i intrinsic;
		};

		union Vec_S32_8 {
			Vector<int32_t, 8> vector;
			__m256i intrinsic;
		};

		union Vec_U32_8 {
			Vector<uint32_t, 8> vector;
			__m256i intrinsic;
		};

		union Vec_S64_4 {
			Vector<int64_t, 4> vector;
			__m256i intrinsic;
		};

		union Vec_U64_4 {
			Vector<uint64_t, 4> vector;
			__m256i intrinsic;
		};

		union Vec_F32_8 {
			Vector<float, 8> vector;
			__m256 intrinsic;
		};

		union Vec_F64_4 {
			Vector<double, 4> vector;
			__m256d  intrinsic;
		};
#endif
#ifdef ANVIL_AVX_512
		union Vec_S8_64 {
			Vector<int8_t, 64> vector;
			__m512i intrinsic;
		};

		union Vec_U8_64 {
			Vector<uint8_t, 64> vector;
			__m512i intrinsic;
		};

		union Vec_S16_32 {
			Vector<int16_t, 32> vector;
			__m512i intrinsic;
		};

		union Vec_U16_32 {
			Vector<uint16_t, 32> vector;
			__m512i intrinsic;
		};

		union Vec_S32_16 {
			Vector<int32_t, 16> vector;
			__m512i intrinsic;
		};

		union Vec_U32_16 {
			Vector<uint32_t, 16> vector;
			__m512i intrinsic;
		};

		union Vec_S64_8 {
			Vector<int64_t, 8> vector;
			__m512i intrinsic;
		};

		union Vec_U64_8 {
			Vector<uint64_t, 8> vector;
			__m512i intrinsic;
		};

		union Vec_F32_16 {
			Vector<float, 16> vector;
			__m512 intrinsic;
		};

		union Vec_F64_8 {
			Vector<double, 8> vector;
			__m512d  intrinsic;
		};
#endif
	}

#define ANVIL_MARK_OPTIMISED(TYPE, CHANNELS, VOP) template<> struct detail::VopOptimised<TYPE, CHANNELS, VOP> { enum { value = 1 }; };

#define ANVIL_SPECIALISE_VECTOR_OP_CMP(VOP, TYPE,CHANNELS,SYMBOL,UNION,FUNCTION)\
	ANVIL_MARK_OPTIMISED(TYPE, CHANNELS, VOP)\
	template<>\
	inline Vector<TYPE, CHANNELS> ANVIL_CALL operator ## SYMBOL(const Vector<TYPE, CHANNELS> a, const Vector<TYPE, CHANNELS> b) throw() {\
		UNION a_, b_, c_;\
		a_.vector = a;\
		b_.vector = b;\
		c_.intrinsic = FUNCTION(a_.intrinsic, b_.intrinsic);\
		return c_.vector;\
	}

#define ANVIL_SPECIALISE_VECTOR_OP_EQ(VOP, TYPE,CHANNELS,SYMBOL,UNION,FUNCTION)\
	template<>\
	inline Vector<TYPE, CHANNELS>& ANVIL_CALL operator ## SYMBOL ## =(Vector<TYPE, CHANNELS>& a, const Vector<TYPE, CHANNELS> b) throw() {\
		UNION a_, b_;\
		a_.vector = a;\
		b_.vector = b;\
		a_.intrinsic = FUNCTION(a_.intrinsic, b_.intrinsic);\
		return a = a_.vector;\
	}

#define ANVIL_SPECIALISE_VECTOR_FN_VV(VOP, TYPE,CHANNELS,NAME,UNION,FUNCTION)\
	ANVIL_MARK_OPTIMISED(TYPE, CHANNELS, VOP)\
	template<>\
	inline Vector<TYPE, CHANNELS> ANVIL_CALL NAME<TYPE, CHANNELS>(const Vector<TYPE, CHANNELS> a) {\
		UNION a_, b_;\
		a_.vector = a;\
		b_.intrinsic = FUNCTION(a_.intrinsic);\
		return b_.vector;\
	}

#define ANVIL_SPECIALISE_VECTOR_FN_VVV(VOP, TYPE,CHANNELS,NAME,UNION,FUNCTION)\
	ANVIL_MARK_OPTIMISED(TYPE, CHANNELS, VOP)\
	template<>\
	inline Vector<TYPE, CHANNELS> ANVIL_CALL NAME<TYPE, CHANNELS>(const Vector<TYPE, CHANNELS> a, const Vector<TYPE, CHANNELS> b) throw() {\
		UNION a_, b_, c_;\
		a_.vector = a;\
		b_.vector = b;\
		c_.intrinsic = FUNCTION(a_.intrinsic, b_.intrinsic);\
		return c_.vector;\
	}

#define ANVIL_SPECIALISE_VECTOR_FN_VVVV(VOP, TYPE,CHANNELS,NAME,UNION,FUNCTION)\
	ANVIL_MARK_OPTIMISED(TYPE, CHANNELS, VOP)\
	template<>\
	inline Vector<TYPE, CHANNELS> ANVIL_CALL NAME<TYPE, CHANNELS>(const Vector<TYPE, CHANNELS> a, const Vector<TYPE, CHANNELS> b, const Vector<TYPE, CHANNELS> c) throw() {\
		UNION a_, b_, c_, d_;\
		a_.vector = a;\
		b_.vector = b;\
		c_.vector = c;\
		d_.intrinsic = FUNCTION(a_.intrinsic, b_.intrinsic, c_.intrinsic);\
		return d_.vector;\
	}

#define ANVIL_SPECIALISE_VECTOR_OP(VOP, TYPE,CHANNELS,SYMBOL,UNION,FUNCTION)\
	ANVIL_SPECIALISE_VECTOR_OP_CMP(VOP, TYPE,CHANNELS,SYMBOL,UNION,FUNCTION)\
	ANVIL_SPECIALISE_VECTOR_OP_EQ(VOP, TYPE,CHANNELS,SYMBOL,UNION,FUNCTION)

#ifdef ANVIL_MMX
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_EQ, int32_t, 2, ==, detail::Vec_S32_2, _mm_cmpeq_pi32)
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_GT, int32_t, 2, >, detail::Vec_S32_2, _mm_cmpgt_pi32)

	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_ADD, int16_t, 4, +, detail::Vec_S16_4, _mm_adds_pi16)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_SUB, int16_t, 4, -, detail::Vec_S16_4, _mm_subs_pi16)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_AND, int16_t, 4, &, detail::Vec_S16_4, _mm_and_si64)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_OR, int16_t, 4, |, detail::Vec_S16_4, _mm_or_si64)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_XOR, int16_t, 4, ^, detail::Vec_S16_4, _mm_xor_si64)
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_EQ, int16_t, 4, == , detail::Vec_S16_4, _mm_cmpeq_pi16)
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_GT, int16_t, 4, > , detail::Vec_S16_4, _mm_cmpgt_pi16)

	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_ADD, int8_t, 8, +, detail::Vec_S8_8, _mm_adds_pi8)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_SUB, int8_t, 8, -, detail::Vec_S8_8, _mm_subs_pi8)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_AND, int8_t, 8, &, detail::Vec_S8_8, _mm_and_si64)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_OR, int8_t, 8, | , detail::Vec_S8_8, _mm_or_si64)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_XOR, int8_t, 8, ^, detail::Vec_S8_8, _mm_xor_si64)
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_EQ, int8_t, 8, == , detail::Vec_S8_8, _mm_cmpeq_pi8)
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_GT, int8_t, 8, > , detail::Vec_S8_8, _mm_cmpgt_pi8)

	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_EQ, uint32_t, 2, == , detail::Vec_U32_2, _mm_cmpeq_pi32)

	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_ADD, uint16_t, 4, +, detail::Vec_U16_4, _mm_adds_pu16)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_SUB, uint16_t, 4, -, detail::Vec_U16_4, _mm_subs_pu16)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_AND, uint16_t, 4, &, detail::Vec_U16_4, _mm_and_si64)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_OR, uint16_t, 4, | , detail::Vec_U16_4, _mm_or_si64)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_XOR, uint16_t, 4, ^, detail::Vec_U16_4, _mm_xor_si64)
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_EQ, uint16_t, 4, == , detail::Vec_U16_4, _mm_cmpeq_pi16)

	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_ADD, uint8_t, 8, +, detail::Vec_U8_8, _mm_adds_pu8)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_SUB, uint8_t, 8, -, detail::Vec_U8_8, _mm_subs_pu8)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_AND, uint8_t, 8, &, detail::Vec_U8_8, _mm_and_si64)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_OR, uint8_t, 8, | , detail::Vec_U8_8, _mm_or_si64)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_XOR, uint8_t, 8, ^, detail::Vec_U8_8, _mm_xor_si64)
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_EQ, uint8_t, 8, == , detail::Vec_U8_8, _mm_cmpeq_pi8)
#endif
#ifdef ANVIL_SSE
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_ADD, float, 4, +, detail::Vec_F32_4, _mm_add_ps)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_SUB, float, 4, -, detail::Vec_F32_4, _mm_sub_ps)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_MUL, float, 4, *, detail::Vec_F32_4, _mm_mul_ps)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_DIV, float, 4, / , detail::Vec_F32_4, _mm_div_ps)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_AND, float, 4, &, detail::Vec_F32_4, _mm_and_ps)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_OR, float, 4, | , detail::Vec_F32_4, _mm_or_ps)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_XOR, float, 4, ^, detail::Vec_F32_4, _mm_xor_ps)
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_EQ, float, 4, == , detail::Vec_F32_4, _mm_cmpeq_ps)
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_NE, float, 4, != , detail::Vec_F32_4, _mm_cmpneq_ps)
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_GE, float, 4, >= , detail::Vec_F32_4, _mm_cmpge_ps)
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_LE, float, 4, <= , detail::Vec_F32_4, _mm_cmple_ps)
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_GT, float, 4, > , detail::Vec_F32_4, _mm_cmpgt_ps)
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_LT, float, 4, < , detail::Vec_F32_4, _mm_cmplt_ps)
	ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MAX, float, 4, max, detail::Vec_F32_4, _mm_max_ps)
	ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MIN, float, 4, min, detail::Vec_F32_4, _mm_min_ps)
	ANVIL_SPECIALISE_VECTOR_FN_VV(detail::VOP_SQRT, float, 4, sqrt, detail::Vec_F32_4, _mm_sqrt_ps)

	ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MAX, int16_t, 4, max, detail::Vec_S16_4, _mm_max_pi16)
	ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MIN, int16_t, 4, min, detail::Vec_S16_4, _mm_min_pi16)

	ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MAX, uint8_t, 8, max, detail::Vec_U8_8, _mm_max_pu8)
	ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MIN, uint8_t, 8, min, detail::Vec_U8_8, _mm_min_pu8)
#endif
#ifdef ANVIL_SSE2
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_ADD, double, 2, +, detail::Vec_F64_2, _mm_add_pd)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_SUB, double, 2, -, detail::Vec_F64_2, _mm_sub_pd)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_MUL, double, 2, *, detail::Vec_F64_2, _mm_mul_pd)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_DIV, double, 2, / , detail::Vec_F64_2, _mm_div_pd)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_AND, double, 2, &, detail::Vec_F64_2, _mm_and_pd)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_OR, double, 2, | , detail::Vec_F64_2, _mm_or_pd)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_XOR, double, 2, ^, detail::Vec_F64_2, _mm_xor_pd)
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_EQ, double, 2, == , detail::Vec_F64_2, _mm_cmpeq_pd)
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_NE, double, 2, != , detail::Vec_F64_2, _mm_cmpneq_pd)
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_GE, double, 2, >= , detail::Vec_F64_2, _mm_cmpge_pd)
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_LE, double, 2, <= , detail::Vec_F64_2, _mm_cmple_pd)
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_GT, double, 2, > , detail::Vec_F64_2, _mm_cmpgt_pd)
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_LT, double, 2, <, detail::Vec_F64_2, _mm_cmplt_pd)
	ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MAX, double, 2, max, detail::Vec_F64_2, _mm_max_pd)
	ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MIN, double, 2, min, detail::Vec_F64_2, _mm_min_pd)
	ANVIL_SPECIALISE_VECTOR_FN_VV(detail::VOP_SQRT, double, 2, sqrt, detail::Vec_F64_2, _mm_sqrt_pd)

	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_ADD, int64_t, 2, +, detail::Vec_S64_2, _mm_add_epi64)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_SUB, int64_t, 2, -, detail::Vec_S64_2, _mm_sub_epi64)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_AND, int64_t, 2, &, detail::Vec_S64_2, _mm_and_si128)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_OR, int64_t, 2, | , detail::Vec_S64_2, _mm_or_si128)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_XOR, int64_t, 2, ^, detail::Vec_S64_2, _mm_xor_si128)

	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_ADD, int32_t, 4, +, detail::Vec_S32_4, _mm_add_epi32)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_SUB, int32_t, 4, -, detail::Vec_S32_4, _mm_sub_epi32)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_AND, int32_t, 4, &, detail::Vec_S32_4, _mm_and_si128)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_OR, int32_t, 4, | , detail::Vec_S32_4, _mm_or_si128)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_XOR, int32_t, 4, ^, detail::Vec_S32_4, _mm_xor_si128)
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_EQ, int32_t, 4, == , detail::Vec_S32_4, _mm_cmpeq_epi32)
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_GT, int32_t, 4, >, detail::Vec_S32_4, _mm_cmpgt_epi32)
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_LT, int32_t, 4, <, detail::Vec_S32_4, _mm_cmplt_epi32)

	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_ADD, int16_t, 8, +, detail::Vec_S16_8, _mm_adds_epi16)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_SUB, int16_t, 8, -, detail::Vec_S16_8, _mm_subs_epi16)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_AND, int16_t, 8, &, detail::Vec_S16_8, _mm_and_si128)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_OR, int16_t, 8, | , detail::Vec_S16_8, _mm_or_si128)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_XOR, int16_t, 8, ^, detail::Vec_S16_8, _mm_xor_si128)
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_EQ, int16_t, 8, == , detail::Vec_S16_8, _mm_cmpeq_epi16)
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_GT, int16_t, 8, >, detail::Vec_S16_8, _mm_cmpgt_epi16)
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_LT, int16_t, 8, <, detail::Vec_S16_8, _mm_cmplt_epi16)
	ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MAX, int16_t, 8, max, detail::Vec_S16_8, _mm_max_epi16)
	ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MIN, int16_t, 8, min, detail::Vec_S16_8, _mm_min_epi16)

	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_ADD, int8_t, 16, +, detail::Vec_S8_16, _mm_adds_epi8)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_SUB, int8_t, 16, -, detail::Vec_S8_16, _mm_subs_epi8)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_AND, int8_t, 16, &, detail::Vec_S8_16, _mm_and_si128)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_OR, int8_t, 16, | , detail::Vec_S8_16, _mm_or_si128)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_XOR, int8_t, 16, ^, detail::Vec_S8_16, _mm_xor_si128)
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_EQ, int8_t, 16, == , detail::Vec_S8_16, _mm_cmpeq_epi8)
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_GT, int8_t, 16, >, detail::Vec_S8_16, _mm_cmpgt_epi8)
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_LT , int8_t, 16, < , detail::Vec_S8_16, _mm_cmplt_epi8)

	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_AND, uint64_t, 2, &, detail::Vec_U64_2, _mm_and_si128)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_OR, uint64_t, 2, |, detail::Vec_U64_2, _mm_or_si128)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_XOR, uint64_t, 2, ^, detail::Vec_U64_2, _mm_xor_si128)

	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_EQ, uint32_t, 4, == , detail::Vec_U32_4, _mm_cmpeq_epi32)

	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_ADD, uint16_t, 8, +, detail::Vec_U16_8, _mm_adds_epu16)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_SUB, uint16_t, 8, -, detail::Vec_U16_8, _mm_subs_epu16)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_AND, uint16_t, 8, &, detail::Vec_U16_8, _mm_and_si128)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_OR, uint16_t, 8, |, detail::Vec_U16_8, _mm_and_si128)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_XOR, uint16_t, 8, ^, detail::Vec_U16_8, _mm_and_si128)
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_EQ, uint16_t, 8, == , detail::Vec_U16_8, _mm_cmpeq_epi16)

	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_ADD, uint8_t, 16, +, detail::Vec_U8_16, _mm_adds_epu8)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_SUB, uint8_t, 16, -, detail::Vec_U8_16, _mm_subs_epu8)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_AND, uint8_t, 16, &, detail::Vec_U8_16, _mm_and_si128)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_OR, uint8_t, 16, | , detail::Vec_U8_16, _mm_and_si128)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_XOR, uint8_t, 16, ^, detail::Vec_U8_16, _mm_and_si128)
	ANVIL_SPECIALISE_VECTOR_OP_CMP(detail::VOP_EQ, uint8_t, 16, ==, detail::Vec_U8_16, _mm_cmpeq_epi8)
	ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MAX, uint8_t, 16, max, detail::Vec_U8_16, _mm_max_epu8)
	ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MIN, uint8_t, 16, min, detail::Vec_U8_16, _mm_min_epu8)
#endif
#ifdef ANVIL_SSSE3
	ANVIL_SPECIALISE_VECTOR_FN_VV(detail::VOP_ABS, int32_t, 4, abs, detail::Vec_S32_4, _mm_abs_epi32)

	ANVIL_SPECIALISE_VECTOR_FN_VV(detail::VOP_ABS, int16_t, 8, abs, detail::Vec_S16_8, _mm_abs_epi16)

	ANVIL_SPECIALISE_VECTOR_FN_VV(detail::VOP_ABS, int8_t, 16, abs, detail::Vec_S8_16, _mm_abs_epi8)

	ANVIL_SPECIALISE_VECTOR_FN_VV(detail::VOP_ABS, int32_t, 2, abs, detail::Vec_S32_2, _mm_abs_pi32)

	ANVIL_SPECIALISE_VECTOR_FN_VV(detail::VOP_ABS, int16_t, 4, abs, detail::Vec_S16_4, _mm_abs_pi16)

	ANVIL_SPECIALISE_VECTOR_FN_VV(detail::VOP_ABS, int8_t, 8, abs, detail::Vec_S8_8, _mm_abs_pi8)
#endif
#ifdef ANVIL_SSE4_1
	ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MAX, int32_t, 4, max, detail::Vec_S32_4, _mm_max_epi32)
	ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MIN, int32_t, 4, min, detail::Vec_S32_4, _mm_min_epi32)

	ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MAX, int8_t, 16, max, detail::Vec_S8_16, _mm_max_epi8)
	ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MIN, int8_t, 16, min, detail::Vec_S8_16, _mm_min_epi8)

	ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MAX, uint32_t, 4, max, detail::Vec_U32_4, _mm_max_epu32)
	ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MIN, uint32_t, 4, min, detail::Vec_U32_4, _mm_min_epu32)

	ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MAX, uint16_t, 8, max, detail::Vec_U16_8, _mm_max_epu16)
	ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MIN, uint16_t, 8, min, detail::Vec_U16_8, _mm_min_epu16)
#endif
#ifdef ANVIL_AVX
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_ADD, double, 4, +, detail::Vec_F64_4, _mm256_add_pd)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_SUB, double, 4, -, detail::Vec_F64_4, _mm256_sub_pd)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_MUL, double, 4, *, detail::Vec_F64_4, _mm256_mul_pd)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_DIV, double, 4, /, detail::Vec_F64_4, _mm256_div_pd)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_AND, double, 4, &, detail::Vec_F64_4, _mm256_and_pd)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_OR , double, 4, |, detail::Vec_F64_4, _mm256_or_pd)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_XOR, double, 4, ^, detail::Vec_F64_4, _mm256_xor_pd)
	ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MAX, double, 4, max, detail::Vec_F64_4, _mm256_max_pd)
	ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MIN, double, 4, min, detail::Vec_F64_4, _mm256_min_pd)
	ANVIL_SPECIALISE_VECTOR_FN_VV(detail::VOP_SQRT, double, 4, sqrt, detail::Vec_F64_4, _mm256_sqrt_pd)

	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_ADD, float, 8, +, detail::Vec_F32_8, _mm256_add_ps)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_SUB, float, 8, -, detail::Vec_F32_8, _mm256_sub_ps)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_MUL, float, 8, *, detail::Vec_F32_8, _mm256_mul_ps)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_DIV, float, 8, / , detail::Vec_F32_8, _mm256_div_ps)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_AND, float, 8, &, detail::Vec_F32_8, _mm256_and_ps)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_OR, float, 8, | , detail::Vec_F32_8, _mm256_or_ps)
	ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_XOR, float, 8, ^, detail::Vec_F32_8, _mm256_xor_ps)
	ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MIN, float, 8, max, detail::Vec_F32_8, _mm256_max_ps)
	ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MAX, float, 8, min, detail::Vec_F32_8, _mm256_min_ps)
	ANVIL_SPECIALISE_VECTOR_FN_VV(detail::VOP_SQRT, float, 8, sqrt, detail::Vec_F32_8, _mm256_sqrt_ps)

	//! \todo Support _mm_cmp_pd and _mm_cmp_ps
#endif
#ifdef ANVIL_FMA
	ANVIL_SPECIALISE_VECTOR_FN_VVVV(detail::VOP_FMA, double, 4, fma, detail::Vec_F64_4, _mm256_fmadd_pd)
	ANVIL_SPECIALISE_VECTOR_FN_VVVV(detail::VOP_FMS, double, 4, fms, detail::Vec_F64_4, _mm256_fmsub_pd)

	ANVIL_SPECIALISE_VECTOR_FN_VVVV(detail::VOP_FMA, float, 8, fma, detail::Vec_F32_8, _mm256_fmadd_ps)
	ANVIL_SPECIALISE_VECTOR_FN_VVVV(detail::VOP_FMS, float, 8, fms, detail::Vec_F32_8, _mm256_fmsub_ps)

	ANVIL_SPECIALISE_VECTOR_FN_VVVV(detail::VOP_FMA, double, 2, fma, detail::Vec_F64_2, _mm_fmadd_pd)
	ANVIL_SPECIALISE_VECTOR_FN_VVVV(detail::VOP_FMS, double, 2, fms, detail::Vec_F64_2, _mm_fmsub_pd)

	ANVIL_SPECIALISE_VECTOR_FN_VVVV(detail::VOP_FMA, float, 4, fma, detail::Vec_F32_4, _mm_fmadd_ps)
	ANVIL_SPECIALISE_VECTOR_FN_VVVV(detail::VOP_FMS, float, 4, fms, detail::Vec_F32_4, _mm_fmsub_ps)
#endif
#ifdef ANVIL_AVX2
		//ANVIL_SPECIALISE_VECTOR_FN_VV(detail::VOP_ABS, int64_t, 4, abs, detail::Vec_S64_4, _mm256_abs_epi64)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_ADD, int64_t, 4, +, detail::Vec_S64_4, _mm256_add_epi64)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_SUB, int64_t, 4, -, detail::Vec_S64_4, _mm256_sub_epi64)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_AND, int64_t, 4, &, detail::Vec_S64_4, _mm256_and_si256)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_OR, int64_t, 4, | , detail::Vec_S64_4, _mm256_or_si256)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_XOR, int64_t, 4, ^, detail::Vec_S64_4, _mm256_xor_si256)

		ANVIL_SPECIALISE_VECTOR_FN_VV(detail::VOP_ABS, int32_t, 8, abs, detail::Vec_S32_8, _mm256_abs_epi32)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_ADD, int32_t, 8, +, detail::Vec_S32_8, _mm256_add_epi32)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_SUB, int32_t, 8, -, detail::Vec_S32_8, _mm256_sub_epi32)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_AND, int32_t, 8, &, detail::Vec_S32_8, _mm256_and_si256)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_OR, int32_t, 8, | , detail::Vec_S32_8, _mm256_or_si256)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_XOR, int32_t, 8, ^, detail::Vec_S32_8, _mm256_xor_si256)
		ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MAX, int32_t, 8, max, detail::Vec_S32_8, _mm256_max_epi32)
		ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MIN, int32_t, 8, min, detail::Vec_S32_8, _mm256_min_epi32)

		ANVIL_SPECIALISE_VECTOR_FN_VV(detail::VOP_ABS, int16_t, 16, abs, detail::Vec_S16_16, _mm256_abs_epi16)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_ADD, int16_t, 16, +, detail::Vec_S16_16, _mm256_add_epi16)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_SUB, int16_t, 16, -, detail::Vec_S16_16, _mm256_sub_epi16)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_AND, int16_t, 16, &, detail::Vec_S16_16, _mm256_and_si256)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_OR, int16_t, 16, | , detail::Vec_S16_16, _mm256_or_si256)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_XOR, int16_t, 16, ^, detail::Vec_S16_16, _mm256_xor_si256)
		ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MAX, int16_t, 16, max, detail::Vec_S16_16, _mm256_max_epi16)
		ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MIN, int16_t, 16, min, detail::Vec_S16_16, _mm256_min_epi16)

		ANVIL_SPECIALISE_VECTOR_FN_VV(detail::VOP_ABS, int8_t, 32, abs, detail::Vec_S8_32, _mm256_abs_epi8)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_ADD, int8_t, 32, +, detail::Vec_S8_32, _mm256_add_epi8)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_SUB, int8_t, 32, -, detail::Vec_S8_32, _mm256_sub_epi8)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_AND, int8_t, 32, &, detail::Vec_S8_32, _mm256_and_si256)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_OR, int8_t, 32, | , detail::Vec_S8_32, _mm256_or_si256)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_XOR, int8_t, 32, ^, detail::Vec_S8_32, _mm256_xor_si256)
		ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MAX, int8_t, 32, max, detail::Vec_S8_32, _mm256_max_epi8)
		ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MIN, int8_t, 32, min, detail::Vec_S8_32, _mm256_min_epi8)


		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_AND, uint64_t, 4, &, detail::Vec_U64_4, _mm256_and_si256)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_OR, uint64_t, 4, | , detail::Vec_U64_4, _mm256_or_si256)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_XOR, uint64_t, 4, ^, detail::Vec_U64_4, _mm256_xor_si256)

		//ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_ADD, uint32_t, 8, +, detail::Vec_U32_8, _mm256_adds_epu32)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_AND, uint32_t, 8, &, detail::Vec_U32_8, _mm256_and_si256)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_OR, uint32_t, 8, | , detail::Vec_U32_8, _mm256_or_si256)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_XOR, uint32_t, 8, ^, detail::Vec_U32_8, _mm256_xor_si256)
		ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MAX, uint32_t, 8, max, detail::Vec_U32_8, _mm256_max_epu32)
		ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MIN, uint32_t, 8, min, detail::Vec_U32_8, _mm256_min_epu32)

		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_ADD, uint16_t, 16, +, detail::Vec_U16_16, _mm256_adds_epu16)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_SUB, uint16_t, 16, -, detail::Vec_U16_16, _mm256_subs_epu16)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_AND, uint16_t, 16, &, detail::Vec_U16_16, _mm256_and_si256)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_OR, uint16_t, 16, | , detail::Vec_U16_16, _mm256_or_si256)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_XOR, uint16_t, 16, ^, detail::Vec_U16_16, _mm256_xor_si256)
		ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MAX, uint16_t, 16, max, detail::Vec_U16_16, _mm256_max_epu16)
		ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MIN, uint16_t, 16, min, detail::Vec_U16_16, _mm256_min_epu16)

		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_ADD, uint8_t, 32, +, detail::Vec_U8_32, _mm256_adds_epu8)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_SUB, uint8_t, 32, -, detail::Vec_U8_32, _mm256_subs_epu8)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_AND, uint8_t, 32, &, detail::Vec_U8_32, _mm256_and_si256)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_OR, uint8_t, 32, | , detail::Vec_U8_32, _mm256_or_si256)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_XOR, uint8_t, 32, ^, detail::Vec_U8_32, _mm256_xor_si256)
		ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MAX, uint8_t, 32, max, detail::Vec_U8_32, _mm256_max_epu8)
		ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MIN, uint8_t, 32, min, detail::Vec_U8_32, _mm256_min_epu8)
		//! \todo _mm256_avg_epu8, _mm256_avg_epu16
#endif
#ifdef ANVIL_AVX_512
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_ADD, double, 8, +, detail::Vec_F64_8, _mm512_add_pd)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_SUB, double, 8, -, detail::Vec_F64_8, _mm512_sub_pd)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_MUL, double, 8, *, detail::Vec_F64_8, _mm512_mul_pd)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_DIV, double, 8, /, detail::Vec_F64_8, _mm512_div_pd)
		ANVIL_SPECIALISE_VECTOR_FN_VV(detail::VOP_SQRT, double, 8, sqrt, detail::Vec_F64_8, _mm512_sqrt_pd)
		ANVIL_SPECIALISE_VECTOR_FN_VV(detail::VOP_ABS, double, 8, abs, detail::Vec_F64_8, _mm512_abs_pd)
		ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MAX, double, 8, max, detail::Vec_F64_8, _mm512_max_pd)
		ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MIN, double, 8, min, detail::Vec_F64_8, _mm512_min_pd)

		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_ADD, float, 16, +, detail::Vec_F32_16, _mm512_add_ps)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_SUB, float, 16, -, detail::Vec_F32_16, _mm512_sub_ps)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_MUL, float, 16, *, detail::Vec_F32_16, _mm512_mul_ps)
		ANVIL_SPECIALISE_VECTOR_OP(detail::VOP_DIV, float, 16, /, detail::Vec_F32_16, _mm512_div_ps)
		ANVIL_SPECIALISE_VECTOR_FN_VV(detail::VOP_DIV, float, 16, sqrt, detail::Vec_F32_16, _mm512_sqrt_ps)
		ANVIL_SPECIALISE_VECTOR_FN_VV(detail::VOP_ABS, float, 16, abs, detail::Vec_F32_16, _mm512_abs_ps)
		ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MAX, float, 16, max, detail::Vec_F32_16, _mm512_max_ps)
		ANVIL_SPECIALISE_VECTOR_FN_VVV(detail::VOP_MIN, float, 16, min, detail::Vec_F32_16, _mm512_min_ps)
#endif

#undef ANVIL_SPECIALISE_VECTOR_OP_CMP
#undef ANVIL_SPECIALISE_VECTOR_OP_EQ
#undef ANVIL_SPECIALISE_VECTOR_OP
#undef ANVIL_SPECIALISE_VECTOR_FN_VV
#undef ANVIL_SPECIALISE_VECTOR_FN_VVV
#undef ANVIL_SPECIALISE_VECTOR_FN_VVVV

	////

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
		return fill<T,S>(a) + b;
	}

	template<class T, size_t S>
	inline Vector<T, S> ANVIL_CALL operator-(const T a, const Vector<T, S> b) {
		return fill<T, S>(a) - b;
	}

	template<class T, size_t S>
	inline Vector<T, S> ANVIL_CALL operator*(const T a, const Vector<T, S> b) {
		return fill<T,S>(a) * b;
	}

	template<class T, size_t S>
	inline Vector<T, S> ANVIL_CALL operator/(const T a, const Vector<T, S> b) {
		return fill<T,S>(a) / b;
	}

	template<class T, size_t S>
	inline Vector<T, S> ANVIL_CALL operator&(const T a, const Vector<T, S> b) {
		return fill<T,S>(a) & b;
	}

	template<class T, size_t S>
	inline Vector<T, S> ANVIL_CALL operator|(const T a, const Vector<T, S> b) {
		return fill<T,S>(a) | b;
	}

	template<class T, size_t S>
	inline Vector<T, S> ANVIL_CALL operator^(const T a, const Vector<T, S> b) {
		return fill<T,S>(a) ^ b;
	}

	template<class T, size_t S>
	inline Vector<T, S> ANVIL_CALL operator&&(const T a, const Vector<T, S> b) {
		return fill<T,S>(a) && b;
	}

	template<class T, size_t S>
	inline Vector<T, S> ANVIL_CALL operator||(const T a, const Vector<T, S> b) {
		return fill<T,S>(a) || b;
	}

	template<class T, size_t S>
	inline Vector<T, S> ANVIL_CALL operator<<(const T a, const Vector<T, S> b) {
		return fill<T,S>(a) << b;
	}

	template<class T, size_t S>
	inline Vector<T, S> ANVIL_CALL operator>>(const T a, const Vector<T, S> b) {
		return fill<T,S>(a) >> b;
	}

	template<class T, size_t S>
	inline Vector<T, S> ANVIL_CALL operator%(const T a, const Vector<T, S> b) {
		return fill<T,S>(a) % b;
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
}

#endif