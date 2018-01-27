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
#include "anvil/Core/Cpu.hpp"
#include "anvil/Core/Constants.hpp"
#include "anvil/maths/Type.hpp"
#include "anvil/maths/Popcount.hpp"
#include "anvil/maths/Reflection.hpp"
#include "anvil/maths/Common.hpp"
#include "anvil/maths/SIMD.hpp"

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

#include "anvil/maths/SIMD.hpp"

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
	struct Vector {
		typedef T type;
		enum {
			size = S,
		};
		static_assert(size > 1, "Minimum vector size is 2");
		typedef Vector<type, size> this_t;
		typedef Vector<type, size / 2> half_t;
		typedef typename detail::VFloat<type>::type float_t;

		type elements[size];

		ANVIL_CALL Vector() {
			//simd::OperationDispatcher<type, size, simd::OP_FILL>::execute(elements);
		}

		Vector(const T x) {
			//simd::OperationDispatcher<type, size, simd::OP_FILL>::execute(x, elements);
		}

		Vector(const T x, const T y) {
			//simd::OperationDispatcher<type, size, simd::OP_FILL>::execute(x, y, elements);
		}

		Vector(const T x, const T y, const T z) {
			//simd::OperationDispatcher<type, size, simd::OP_FILL>::execute(x, y, z, elements);
		}

		Vector(const T x, const T y, const T z, const T w) {
			//simd::OperationDispatcher<type, size, simd::OP_FILL>::execute(x, y, z, w, elements);
		}

		ANVIL_STRONG_INLINE half_t& ANVIL_SIMD_CALL lowerHalf() throw() {
			return reinterpret_cast<half_t*>(this)[0];
		}

		ANVIL_STRONG_INLINE half_t& ANVIL_SIMD_CALL upperHalf() throw() {
			return reinterpret_cast<half_t*>(this)[1];
		}

		ANVIL_STRONG_INLINE half_t ANVIL_SIMD_CALL lowerHalf() const throw() {
			return reinterpret_cast<const half_t*>(this)[0];
		}

		ANVIL_STRONG_INLINE half_t ANVIL_SIMD_CALL upperHalf() const throw() {
			return reinterpret_cast<const half_t*>(this)[1];
		}

		explicit ANVIL_SIMD_CALL operator bool() const throw() {
			return !elementsEqual(static_cast<type>(0));
		}

		inline this_t ANVIL_SIMD_CALL operator!() const throw() {
			this_t tmp;
			for (size_t i = 0; i < size; ++i) tmp.elements[i] = !elements[i];
			return tmp;
		}

		ANVIL_STRONG_INLINE this_t ANVIL_SIMD_CALL operator~() const throw() {
			this_t tmp;
			simd::OperationDispatcher<T, S, simd::OP_NOT>::execute(elements, tmp.elements);
			return tmp;
		}

		ANVIL_STRONG_INLINE this_t& ANVIL_SIMD_CALL operator++() throw() {
			*this += static_cast<type>(1);
			return *this;
		}

		ANVIL_STRONG_INLINE this_t& ANVIL_SIMD_CALL operator--() throw() {
			*this -= static_cast<type>(1);
			return *this;
		}

		inline this_t ANVIL_SIMD_CALL operator++(int) throw() {
			const this_t tmp(*this);
			*this += static_cast<type>(1);
			return tmp;
		}

		inline this_t ANVIL_SIMD_CALL operator--(int) throw() {
			const this_t tmp(*this);
			*this -= static_cast<type>(1);
			return tmp;
		}

		ANVIL_STRONG_INLINE type ANVIL_SIMD_CALL operator[](const size_t aIndex) const throw() {
			return elements[aIndex];
		}

		ANVIL_STRONG_INLINE type& ANVIL_SIMD_CALL operator[](const size_t aIndex) throw() {
			return elements[aIndex];
		}

		ANVIL_STRONG_INLINE const type* ANVIL_SIMD_CALL begin() const throw() {
			return elements;
		}

		ANVIL_STRONG_INLINE type* ANVIL_SIMD_CALL begin() throw() {
			return elements;
		}

		ANVIL_STRONG_INLINE const type* ANVIL_SIMD_CALL end() const throw() {
			return elements + size;
		}

		ANVIL_STRONG_INLINE type* ANVIL_SIMD_CALL end() throw() {
			return elements + size;
		}

		//inline float_t ANVIL_CALL sumf() const throw() {
		//	typedef detail::VectorLoopInfo<type, size, detail::VOP_ADD> Info;
		//	if (Info::HALF_OPTIMISED) {
		//		return (lowerHalf() + upperHalf()).sumf();
		//	} else if (Info::OPTIMISED_SIZE) {
		//		const Vector<type, Info::OPTIMISED_SIZE>* ptr = reinterpret_cast<const Vector<type, Info::OPTIMISED_SIZE>*>(this);
		//		Vector<type, Info::OPTIMISED_SIZE> tmp = ptr[0];
		//		for (size_t i = 1; i < Info::OPTIMISED_LOOP; ++i) tmp += ptr[i];
		//		for (size_t i = 0; i < Info::OPTIMISED_REMAINDER; ++i) tmp[0] += ptr[Info::OPTIMISED_LOOP][i];
		//		return tmp.sumf();
		//	} else {
		//		type tmp = elements[0];
		//		for (size_t i = 1; i < size; ++i) tmp += elements[i];
		//		return tmp;
		//	}
		//}

		ANVIL_STRONG_INLINE bool ANVIL_SIMD_CALL elementsEqual(const T a_scalar) const throw() {
			return elements[0] == a_scalar ? elementsEqual() : false;
		}

		//inline bool ANVIL_CALL elementsEqual() const throw() {
		//	typedef detail::VectorLoopInfo<type, size, detail::VOP_EQ> Info;
		//	if (Info::HALF_OPTIMISED) {
		//		const half_t tmp = lowerHalf();
		//		return (lowerHalf() == upperHalf()).sumf() == static_cast<float_t>(half_t::size) && tmp.elementsEqual();
		//	} else if (Info::OPTIMISED_SIZE) {
		//		const Vector<type, Info::OPTIMISED_SIZE>* ptr = reinterpret_cast<const Vector<type, Info::OPTIMISED_SIZE>*>(this);
		//		const Vector<type, Info::OPTIMISED_SIZE> tmp = ptr[0];
		//		if (!tmp.elementsEqual()) return false;
		//		for (size_t i = 1; i < Info::OPTIMISED_LOOP; ++i) if((ptr[i] == tmp).sumf() != static_cast<float_t>(size)) return false;
		//		for (size_t i = 0; i < Info::OPTIMISED_REMAINDER; ++i) if(ptr[0][0] != ptr[Info::OPTIMISED_LOOP][i]) return false;
		//		return true;
		//	} else {
		//		for (size_t i = 0; i < size; ++i) if(elements[0] != elements[i]) return false;
		//		return true;
		//	}
		//}

		ANVIL_STRONG_INLINE float_t ANVIL_SIMD_CALL avgf() const throw() {
			return sumf() / static_cast<float_t>(size);
		}

		ANVIL_STRONG_INLINE type ANVIL_SIMD_CALL sum() const throw() {
			return static_cast<type>(sumf());
		}

		ANVIL_STRONG_INLINE type ANVIL_SIMD_CALL avg() const throw() {
			return static_cast<type>(avgf());
		}

		ANVIL_STRONG_INLINE size_t ANVIL_SIMD_CALL popcount() const throw() {
			return popcount<sizeof(type) * size>(this);
		}

		//inline type ANVIL_CALL min() const throw() {
		//	typedef detail::VectorLoopInfo<type, size, detail::VOP_MIN> Info;
		//	if (Info::HALF_OPTIMISED) {
		//		return anvil::min<half_t::type, half_t::size>(lowerHalf(), upperHalf()).min();
		//	} else if (Info::OPTIMISED_SIZE) {
		//		const Vector<type, Info::OPTIMISED_SIZE>* ptr = reinterpret_cast<const Vector<type, Info::OPTIMISED_SIZE>*>(this);
		//		Vector<type, Info::OPTIMISED_SIZE> tmp = ptr[0];
		//		for (size_t i = 1; i < Info::OPTIMISED_LOOP; ++i) anvil::min<type, Info::OPTIMISED_SIZE>(tmp, ptr[i]);
		//		for (size_t i = 0; i < Info::OPTIMISED_REMAINDER; ++i) tmp[0] = anvil::min(tmp[0], ptr[Info::OPTIMISED_LOOP][i]);
		//		return tmp.min();
		//	} else {
		//		type tmp = elements[0];
		//		for (size_t i = 1; i < size; ++i) tmp = anvil::min(tmp, elements[i]);
		//		return tmp;
		//	}
		//}

		//inline type ANVIL_CALL max() const throw() {
		//	typedef detail::VectorLoopInfo<type, size, detail::VOP_MAX> Info;
		//	if (Info::HALF_OPTIMISED) {
		//		return anvil::max<half_t::type, half_t::size>(lowerHalf(), upperHalf()).max();
		//	} else if (Info::OPTIMISED_SIZE) {
		//		const Vector<type, Info::OPTIMISED_SIZE>* ptr = reinterpret_cast<const Vector<type, Info::OPTIMISED_SIZE>*>(this);
		//		Vector<type, Info::OPTIMISED_SIZE> tmp = ptr[0];
		//		for (size_t i = 1; i < Info::OPTIMISED_LOOP; ++i) anvil::max<type, Info::OPTIMISED_SIZE>(tmp, ptr[i]);
		//		for (size_t i = 0; i < Info::OPTIMISED_REMAINDER; ++i) tmp[0] = anvil::max(tmp[0], ptr[Info::OPTIMISED_LOOP][i]);
		//		return tmp.max();
		//	} else {
		//		type tmp = elements[0];
		//		for (size_t i = 1; i < size; ++i) tmp = anvil::max(tmp, elements[i]);
		//		return tmp;
		//	}
		//}

		//inline float_t ANVIL_CALL dot(const this_t aOther) const throw() {
		//	if (std::is_same<float_t, type>::value) {
		//		float_t sum = static_cast<float_t>(0);
		//		for (size_t i = 0; i < size; ++i) sum = fma(elements[i], aOther.elements[i], sum);
		//		return sum;
		//	} else {
		//		Vector<float_t, size> a(*this);
		//		Vector<float_t, size> b(aOther);
		//		return a.dot(b);
		//	}
		//}

		//inline Vector<float_t, 3> ANVIL_CALL crossf(const this_t aOther) const throw() {
		//	Vector<float_t, 4> a, b, c, d;

		//	a[0] = static_cast<float_t>(elements[1]);
		//	a[1] = static_cast<float_t>(elements[2]);
		//	a[2] = static_cast<float_t>(elements[0]);
		//	a[3] = static_cast<float_t>(0.f);

		//	c[0] = static_cast<float_t>(elements[2]);
		//	c[1] = static_cast<float_t>(elements[0]);
		//	c[2] = static_cast<float_t>(elements[1]);
		//	c[3] = static_cast<float_t>(0.f);

		//	b[0] = static_cast<float_t>(aOther.elements[2]);
		//	b[1] = static_cast<float_t>(aOther.elements[0]);
		//	b[2] = static_cast<float_t>(aOther.elements[1]);
		//	b[3] = static_cast<float_t>(0.f);

		//	d[0] = static_cast<float_t>(aOther.elements[1]);
		//	d[1] = static_cast<float_t>(aOther.elements[2]);
		//	d[2] = static_cast<float_t>(aOther.elements[0]);
		//	d[3] = static_cast<float_t>(0.f);

		//	union {
		//		Vector<float_t, 4> v4;
		//		Vector<float_t, 3> v3;
		//	};
		//	v4 = anvil::fms<type, 4>(a, b, c * d);
		//	return v3;
		//}

		//inline Vector<T, 3> ANVIL_CALL cross(const this_t aOther) const throw() {
		//	return vector_cast<type, size>(crossf(aOther));
		//}

		//inline float_t ANVIL_CALL mag2f() const throw() {
		//	if (std::is_same<float_t, type>::value) {
		//		float_t sum = static_cast<float_t>(0);
		//		for (size_t i = 0; i < size; ++i) sum = fma(elements[i], elements[i], sum);
		//		return sum;
		//	} else {
		//		return Vector<float_t, size>(*this).mag2();
		//	}
		//}

		ANVIL_STRONG_INLINE float_t ANVIL_SIMD_CALL magf() const throw() {
			return sqrt(mag2f());
		}

		ANVIL_STRONG_INLINE type ANVIL_SIMD_CALL mag2() const throw() {
			return static_cast<type>(mag2f());
		}

		ANVIL_STRONG_INLINE type ANVIL_SIMD_CALL mag() const throw() {
			return static_cast<type>(magf());
		}

		inline Vector<float_t, size> ANVIL_SIMD_CALL normalisef() const throw() {
			Vector<float_t, size> tmp = static_cast<Vector<float_t, size>>(*this);
			tmp = tmp * tmp;
			tmp /= fill<float_t, size>(tmp.sumf());
			return tmp;
		}

		ANVIL_STRONG_INLINE this_t ANVIL_SIMD_CALL normalise() const throw() {
			return vector_cast<type, size>(normalisef());
		}

		template<class T2, size_t S2>
		Vector<type, S2> ANVIL_SIMD_CALL swizzle(const Vector<T2, S2> aOther) const throw() {
			Vector<type, S2> tmp;
			for (size_t i = 0; i < S2; ++i) tmp[i] = elements[static_cast<size_t>(aOther[i])];
			return tmp;
		}

		inline this_t ANVIL_SIMD_CALL sort() const throw() {
			this_t tmp(*this);
			std::sort(tmp.begin(), tmp.end());
			return tmp;
		}
	};

	// Vector Operators

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_SIMD_CALL operator+(const Vector<T, S> x, const Vector<T, S> y) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_ADD>::execute(x.elements, y.elements, tmp);
		return *reinterpret_cast<Vector<T,S>*>(tmp);
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_SIMD_CALL operator-(const Vector<T, S> x, const Vector<T, S> y) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_SUB>::execute(x.elements, y.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_SIMD_CALL operator*(const Vector<T, S> x, const Vector<T, S> y) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_MUL>::execute(x.elements, y.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_SIMD_CALL operator/(const Vector<T, S> x, const Vector<T, S> y) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_DIV>::execute(x.elements, y.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_SIMD_CALL operator&(const Vector<T, S> x, const Vector<T, S> y) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_AND>::execute(x.elements, y.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_SIMD_CALL operator|(const Vector<T, S> x, const Vector<T, S> y) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_OR>::execute(x.elements, y.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_SIMD_CALL operator^(const Vector<T, S> x, const Vector<T, S> y) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_XOR>::execute(x.elements, y.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_SIMD_CALL operator<<(const Vector<T, S> x, const Vector<T, S> y) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_LSHIFT>::execute(x.elements, y.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_SIMD_CALL operator>>(const Vector<T, S> x, const Vector<T, S> y) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_RSHIFT>::execute(x.elements, y.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_SIMD_CALL operator%(const Vector<T, S> x, const Vector<T, S> y) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_MOD>::execute(x.elements, y.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S>& ANVIL_SIMD_CALL operator+=(Vector<T, S>& x, const Vector<T, S> y) {
		simd::OperationDispatcher<T, S, simd::OP_ADD>::execute(x.elements, y.elements, x.elements);
		return x;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S>& ANVIL_SIMD_CALL operator-=(Vector<T, S>& x, const Vector<T, S> y) {
		simd::OperationDispatcher<T, S, simd::OP_SUB>::execute(x.elements, y.elements, x.elements);
		return x;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S>& ANVIL_SIMD_CALL operator*=(Vector<T, S>& x, const Vector<T, S> y) {
		simd::OperationDispatcher<T, S, simd::OP_MUL>::execute(x.elements, y.elements, x.elements);
		return x;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S>& ANVIL_SIMD_CALL operator/=(Vector<T, S>& x, const Vector<T, S> y) {
		simd::OperationDispatcher<T, S, simd::OP_DIV>::execute(x.elements, y.elements, x.elements);
		return x;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S>& ANVIL_SIMD_CALL operator&=(Vector<T, S>& x, const Vector<T, S> y) {
		simd::OperationDispatcher<T, S, simd::OP_AND>::execute(x.elements, y.elements, x.elements);
		return x;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S>& ANVIL_SIMD_CALL operator|=(Vector<T, S>& x, const Vector<T, S> y) {
		simd::OperationDispatcher<T, S, simd::OP_OR>::execute(x.elements, y.elements, x.elements);
		return x;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S>& ANVIL_SIMD_CALL operator^=(Vector<T, S>& x, const Vector<T, S> y) {
		simd::OperationDispatcher<T, S, simd::OP_XOR>::execute(x.elements, y.elements, x.elements);
		return x;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S>& ANVIL_SIMD_CALL operator<<=(Vector<T, S>& x, const Vector<T, S> y) {
		simd::OperationDispatcher<T, S, simd::OP_LSHIFT>::execute(x.elements, y.elements, x.elements);
		return x;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S>& ANVIL_SIMD_CALL operator>>=(Vector<T, S>& x, const Vector<T, S> y) {
		simd::OperationDispatcher<T, S, simd::OP_RSHIFT>::execute(x.elements, y.elements, x.elements);
		return x;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S>& ANVIL_SIMD_CALL operator%=(Vector<T, S>& x, const Vector<T, S> y) {
		simd::OperationDispatcher<T, S, simd::OP_MOD>::execute(x.elements, y.elements, x.elements);
		return x;
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_SIMD_CALL operator==(const Vector<T, S> x, const Vector<T, S> y) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_CMPEQ>::execute(x.elements, y.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_SIMD_CALL operator!=(const Vector<T, S> x, const Vector<T, S> y) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_CMPNE>::execute(x.elements, y.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_SIMD_CALL operator<(const Vector<T, S> x, const Vector<T, S> y) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_CMPLT>::execute(x.elements, y.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_SIMD_CALL operator>(const Vector<T, S> x, const Vector<T, S> y) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_CMPGT>::execute(x.elements, y.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_SIMD_CALL operator<=(const Vector<T, S> x, const Vector<T, S> y) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_CMPLE>::execute(x.elements, y.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	ANVIL_STRONG_INLINE Vector<T, S> ANVIL_SIMD_CALL operator>=(const Vector<T, S> x, const Vector<T, S> y) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_CMPGT>::execute(x.elements, y.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	// Vector functions

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_SIMD_CALL reflect(const Vector<T, S> x) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_REFLECT>::execute(x.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_SIMD_CALL fma(const Vector<T, S> x, const Vector<T, S> y, const Vector<T, S> z) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_FMA>::execute(x.elements, y.elements, z.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_SIMD_CALL fms(const Vector<T, S> x, const Vector<T, S> y, const Vector<T, S> z) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_FMS>::execute(x.elements, y.elements, z.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_SIMD_CALL dim(const Vector<T, S> x, const Vector<T, S> y) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_DIM>::execute(x.elements, y.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_SIMD_CALL atan2(const Vector<T, S> x, const Vector<T, S> y) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_ATAN2>::execute(x.elements, y.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_SIMD_CALL abs(const Vector<T, S> x) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_ABS>::execute(x.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_SIMD_CALL exp(const Vector<T, S> x) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_EXP>::execute(x.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_SIMD_CALL log(const Vector<T, S> x) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_LOG>::execute(x.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_SIMD_CALL log2(const Vector<T, S> x) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_LOG2>::execute(x.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_SIMD_CALL log10(const Vector<T, S> x) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_LOG10>::execute(x.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_SIMD_CALL ceil(const Vector<T, S> x) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_CEIL>::execute(x.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_SIMD_CALL floor(const Vector<T, S> x) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_FLOOR>::execute(x.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_SIMD_CALL round(const Vector<T, S> x) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_ROUND>::execute(x.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_SIMD_CALL sin(const Vector<T, S> x) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_SIN>::execute(x.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_SIMD_CALL cos(const Vector<T, S> x) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_COS>::execute(x.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_SIMD_CALL tan(const Vector<T, S> x) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_TAN>::execute(x.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_SIMD_CALL asin(const Vector<T, S> x) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_ASIN>::execute(x.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_SIMD_CALL acos(const Vector<T, S> x) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_ACOS>::execute(x.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_SIMD_CALL atan(const Vector<T, S> x) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_ATAN>::execute(x.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_SIMD_CALL sinh(const Vector<T, S> x) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_SINH>::execute(x.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_SIMD_CALL cosh(const Vector<T, S> x) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_COSH>::execute(x.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_SIMD_CALL tanh(const Vector<T, S> x) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_TANH>::execute(x.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_SIMD_CALL sqrt(const Vector<T, S> x) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_SQRT>::execute(x.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE Vector<size_t, S> ANVIL_SIMD_CALL cbrt(const Vector<T, S> x) {
		T tmp[S];
		simd::OperationDispatcher<T, S, simd::OP_CBRT>::execute(x.elements, tmp);
		return *reinterpret_cast<Vector<T, S>*>(tmp);
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE T ANVIL_SIMD_CALL avg(const Vector<T, S> x) {
		return simd::OperationDispatcher<T, S, simd::OP_AVG>::execute(x.elements);
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE T ANVIL_SIMD_CALL sum(const Vector<T, S> x) {
		return simd::OperationDispatcher<T, S, simd::OP_SUM>::execute(x.elements);
	}

	template<class T, size_t S>
	static ANVIL_STRONG_INLINE size_t ANVIL_SIMD_CALL popcount(const Vector<T, S> x) {
		return simd::OperationDispatcher<T, S, simd::OP_POPCN>::execute(x.elements);
	}

	// Vector helpers

	//template<class T, size_t S, size_t S2>
	//static inline Vector<T, S> vector_resize(const Vector<T, S2> aVec) {
	//	union {
	//		Vector<T, S2> a;
	//		Vector<T, S> b;
	//	};
	//	if(S > S2) memset(&b, 0, sizeof(T) * S);
	//	a = aVec;
	//	return b;
	//}

	//template<class T, size_t S, class T2>
	//static inline Vector<T, S> vector_cast(const Vector<T2, S> aVec) {
	//	Vector<T, S> tmp;
	//	for (size_t i = 0; i < S; ++i) tmp[i] = static_cast<T>(aVec[i]);
	//	return tmp;
	//}

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

template<class T, size_t S>
static std::ostream& operator<<(std::ostream& s, const anvil::Vector<T, S> x) {
	s << '[';
	for (size_t i = 0; i < S; ++i) {
		s << x.elements[i];
		if (i + 1 < S) s << ',' << ' ';
	}
	s << ']';
	return s;
}

template<class T, size_t S>
static std::istream& operator>>(std::istream& s, const anvil::Vector<T, S> x) {
	char buf;
	s >> buf;
	for (size_t i = 0; i < S; ++i) {
		s >> x.elements[i];
		if (i + 1 < S) s >> buf;
	}
	s >> buf;
	return s;
}

#endif