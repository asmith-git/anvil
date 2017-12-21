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

#ifndef ANVIL_MATHS_VECTOR_FUNCTIONS_HPP
#define ANVIL_MATHS_VECTOR_FUNCTIONS_HPP

#include "anvil/maths/Vector.hpp"

namespace anvil {
	// abs

	template<class T>
	static ANVIL_STRONG_INLINE T abs(T aValue) {
		return static_cast<T>(std::abs(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float abs<float>(float a) {
		return std::abs(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double abs<double>(double a) {
		return std::abs(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> abs(Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = abs(a[i]);
		return tmp;
	}

	// mod / fmod

	template<class T>
	static ANVIL_STRONG_INLINE T fmod(T a, T b) {
		return mod<T>(a, b);
	}

	template<class T>
	static ANVIL_STRONG_INLINE T mod(T a, T b) {
		return a % b;
	}

	template<>
	static ANVIL_STRONG_INLINE float mod<float>(float a, float b) {
		return std::fmod(a,b);
	}

	template<>
	static ANVIL_STRONG_INLINE double mod<double>(double a, double b) {
		return std::fmod(a,b);
	}

	template<class T, size_t S>
	static inline Vector<T, S> abs(Vector<T, S> a, Vector<T, S> b) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = mod(a[i], b[i]);
		return tmp;
	}

	// fma

	template<class T>
	static ANVIL_STRONG_INLINE T fma(T a, T b, T c) {
		return (a * b) + c;
	}

	template<>
	static ANVIL_STRONG_INLINE float fma<float>(float a, float b, float c) {
		return std::fma(a, b, c);
	}

	template<>
	static ANVIL_STRONG_INLINE double fma<double>(double a, double b, double c) {
		return std::fma(a, b, c);
	}

	template<class T, size_t S>
	static inline Vector<T, S> fma(Vector<T, S> a, Vector<T, S> b, Vector<T, S> c) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = fma(a[i], b[i], c[i]);
		return tmp;
	}

	// max / fmax

	template<class T>
	static ANVIL_STRONG_INLINE T fmax(T a, T b) {
		return max<T>(a, b);
	}

	template<class T>
	static ANVIL_STRONG_INLINE T max(T a, T b) {
		return a > b ? a : b;
	}

	template<>
	static ANVIL_STRONG_INLINE float max<float>(float a, float b) {
		return std::fmax(a, b);
	}

	template<>
	static ANVIL_STRONG_INLINE double max<double>(double a, double b) {
		return std::fmax(a, b);
	}

	template<class T, size_t S>
	static inline Vector<T, S> max(Vector<T, S> a, Vector<T, S> b) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = max(a[i], b[i]);
		return tmp;
	}

	// max / fmax

	template<class T>
	static ANVIL_STRONG_INLINE T fmin(T a, T b) {
		return min<T>(a, b);
	}

	template<class T>
	static ANVIL_STRONG_INLINE T min(T a, T b) {
		return a < b ? a : b;
	}

	template<>
	static ANVIL_STRONG_INLINE float min<float>(float a, float b) {
		return std::fmin(a, b);
	}

	template<>
	static ANVIL_STRONG_INLINE double min<double>(double a, double b) {
		return std::fmin(a, b);
	}

	template<class T, size_t S>
	static inline Vector<T, S> min(Vector<T, S> a, Vector<T, S> b) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = min(a[i], b[i]);
		return tmp;
	}

	// dif / fdim

	template<class T>
	static ANVIL_STRONG_INLINE T fdim(T a, T b) {
		return dif<T>(a, b);
	}

	template<class T>
	static ANVIL_STRONG_INLINE T dif(T a, T b) {
		return max<T>(a, b) - min<T>(a, b);
	}

	template<>
	static ANVIL_STRONG_INLINE float dif<float>(float a, float b) {
		return std::fdim(a, b);
	}

	template<>
	static ANVIL_STRONG_INLINE double dif<double>(double a, double b) {
		return std::fdim(a, b);
	}

	template<class T, size_t S>
	static inline Vector<T, S> dif(Vector<T, S> a, Vector<T, S> b) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = dif(a[i], b[i]);
		return tmp;
	}

	// exp

	template<class T>
	static ANVIL_STRONG_INLINE T exp(T aValue) {
		return static_cast<T>(std::exp(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float exp<float>(float a) {
		return std::exp(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double exp<double>(double a) {
		return std::exp(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> exp(Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = exp(a[i]);
		return tmp;
	}

	// exp

	template<class T>
	static ANVIL_STRONG_INLINE T log(T aValue) {
		return static_cast<T>(std::log(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float log<float>(float a) {
		return std::log(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double log<double>(double a) {
		return std::log(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> log(Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = log(a[i]);
		return tmp;
	}

	// log2

	template<class T>
	static ANVIL_STRONG_INLINE T log2(T aValue) {
		return static_cast<T>(std::log2(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float log2<float>(float a) {
		return std::log2(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double log2<double>(double a) {
		return std::log2(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> log2(Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = log2(a[i]);
		return tmp;
	}

	// log10

	template<class T>
	static ANVIL_STRONG_INLINE T log10(T aValue) {
		return static_cast<T>(std::log10(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float log10<float>(float a) {
		return std::log10(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double log10<double>(double a) {
		return std::log10(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> log10(Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = log10(a[i]);
		return tmp;
	}

	// pow

	template<class T>
	static ANVIL_STRONG_INLINE T pow(T a, T b) {
		return static_cast<T>(std::pow(static_cast<float>(a), static_cast<float>(b)));
	}

	template<>
	static ANVIL_STRONG_INLINE float pow<float>(float a, float b) {
		return std::pow(a, b);
	}

	template<>
	static ANVIL_STRONG_INLINE double pow<double>(double a, double b) {
		return std::pow(a, b);
	}

	template<class T, size_t S>
	static inline Vector<T, S> pow(Vector<T, S> a, Vector<T, S> b) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = pow(a[i], b[i]);
		return tmp;
	}

	// sqrt

	template<class T>
	static ANVIL_STRONG_INLINE T sqrt(T aValue) {
		return static_cast<T>(std::sqrt(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float sqrt<float>(float a) {
		return std::sqrt(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double sqrt<double>(double a) {
		return std::sqrt(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> sqrt(Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = sqrt(a[i]);
		return tmp;
	}

	// sqrt

	template<class T>
	static ANVIL_STRONG_INLINE T cbrt(T aValue) {
		return static_cast<T>(std::cbrt(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float cbrt<float>(float a) {
		return std::cbrt(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double cbrt<double>(double a) {
		return std::cbrt(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> cbrt(Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = cbrt(a[i]);
		return tmp;
	}

	// cbrt

	template<class T>
	static ANVIL_STRONG_INLINE T cbrt(T aValue) {
		return static_cast<T>(std::cbrt(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float cbrt<float>(float a) {
		return std::cbrt(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double cbrt<double>(double a) {
		return std::cbrt(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> cbrt(Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = cbrt(a[i]);
		return tmp;
	}

	// hypot

	template<class T>
	static ANVIL_STRONG_INLINE T hypot(T a, T b) {
		return static_cast<T>(std::hypot(static_cast<float>(a), static_cast<float>(b)));
	}

	template<>
	static ANVIL_STRONG_INLINE float hypot<float>(float a, float b) {
		return std::hypot(a, b);
	}

	template<>
	static ANVIL_STRONG_INLINE double hypot<double>(double a, double b) {
		return std::hypot(a, b);
	}

	template<class T, size_t S>
	static inline Vector<T, S> hypot(Vector<T, S> a, Vector<T, S> b) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = hypot(a[i], b[i]);
		return tmp;
	}

	// sin

	template<class T>
	static ANVIL_STRONG_INLINE T sin(T aValue) {
		return static_cast<T>(std::sin(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float sin<float>(float a) {
		return std::sin(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double sin<double>(double a) {
		return std::sin(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> sin(Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = sin(a[i]);
		return tmp;
	}

	// cos

	template<class T>
	static ANVIL_STRONG_INLINE T cos(T aValue) {
		return static_cast<T>(std::cos(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float cos<float>(float a) {
		return std::cos(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double cos<double>(double a) {
		return std::cos(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> cos(Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = cos(a[i]);
		return tmp;
	}

	// tan

	template<class T>
	static ANVIL_STRONG_INLINE T tan(T aValue) {
		return static_cast<T>(std::tan(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float tan<float>(float a) {
		return std::tan(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double tan<double>(double a) {
		return std::tan(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> tan(Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = tan(a[i]);
		return tmp;
	}

	// asin

	template<class T>
	static ANVIL_STRONG_INLINE T asin(T aValue) {
		return static_cast<T>(std::asin(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float asin<float>(float a) {
		return std::asin(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double asin<double>(double a) {
		return std::asin(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> asin(Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = asin(a[i]);
		return tmp;
	}

	// acos

	template<class T>
	static ANVIL_STRONG_INLINE T acos(T aValue) {
		return static_cast<T>(std::acos(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float acos<float>(float a) {
		return std::acos(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double acos<double>(double a) {
		return std::acos(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> acos(Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = acos(a[i]);
		return tmp;
	}

	// atan

	template<class T>
	static ANVIL_STRONG_INLINE T atan(T aValue) {
		return static_cast<T>(std::atan(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float atan<float>(float a) {
		return std::atan(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double atan<double>(double a) {
		return std::atan(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> atan(Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = atan(a[i]);
		return tmp;
	}

	// atan2

	template<class T>
	static ANVIL_STRONG_INLINE T atan2(T a, T b) {
		return static_cast<T>(std::atan2(static_cast<float>(a), static_cast<float>(b)));
	}

	template<>
	static ANVIL_STRONG_INLINE float atan2<float>(float a, float b) {
		return std::atan2(a, b);
	}

	template<>
	static ANVIL_STRONG_INLINE double atan2<double>(double a, double b) {
		return std::atan2(a, b);
	}

	template<class T, size_t S>
	static inline Vector<T, S> atan2(Vector<T, S> a, Vector<T, S> b) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = atan2(a[i], b[i]);
		return tmp;
	}

	// sinh

	template<class T>
	static ANVIL_STRONG_INLINE T sinh(T aValue) {
		return static_cast<T>(std::sinh(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float sinh<float>(float a) {
		return std::sinh(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double sinh<double>(double a) {
		return std::sinh(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> sinh(Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = sinh(a[i]);
		return tmp;
	}

	// cosh

	template<class T>
	static ANVIL_STRONG_INLINE T cosh(T aValue) {
		return static_cast<T>(std::cosh(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float cosh<float>(float a) {
		return std::cosh(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double cosh<double>(double a) {
		return std::cosh(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> cosh(Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = cosh(a[i]);
		return tmp;
	}

	// tanh

	template<class T>
	static ANVIL_STRONG_INLINE T tanh(T aValue) {
		return static_cast<T>(std::tanh(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float tanh<float>(float a) {
		return std::tanh(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double tanh<double>(double a) {
		return std::tanh(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> tanh(Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = tanh(a[i]);
		return tmp;
	}

	// asinh

	template<class T>
	static ANVIL_STRONG_INLINE T asinh(T aValue) {
		return static_cast<T>(std::asinh(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float asinh<float>(float a) {
		return std::asinh(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double asinh<double>(double a) {
		return std::asinh(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> asinh(Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = asinh(a[i]);
		return tmp;
	}

	// acosh

	template<class T>
	static ANVIL_STRONG_INLINE T acosh(T aValue) {
		return static_cast<T>(std::acosh(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float acosh<float>(float a) {
		return std::acosh(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double acosh<double>(double a) {
		return std::acosh(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> acosh(Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = acosh(a[i]);
		return tmp;
	}

	// atanh

	template<class T>
	static ANVIL_STRONG_INLINE T atanh(T aValue) {
		return static_cast<T>(std::atanh(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float atanh<float>(float a) {
		return std::atanh(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double atanh<double>(double a) {
		return std::atanh(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> atanh(Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = atanh(a[i]);
		return tmp;
	}

	// ceil

	template<class T>
	static ANVIL_STRONG_INLINE T ceil(T aValue) {
		return aValue;
	}

	template<>
	static ANVIL_STRONG_INLINE float ceil<float>(float a) {
		return std::ceil(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double ceil<double>(double a) {
		return std::ceil(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> ceil(Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = ceil(a[i]);
		return tmp;
	}

	// floor

	template<class T>
	static ANVIL_STRONG_INLINE T floor(T aValue) {
		return aValue;
	}

	template<>
	static ANVIL_STRONG_INLINE float floor<float>(float a) {
		return std::floor(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double floor<double>(double a) {
		return std::floor(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> floor(Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = floor(a[i]);
		return tmp;
	}

	// trunc

	template<class T>
	static ANVIL_STRONG_INLINE T trunc(T aValue) {
		return aValue;
	}

	template<>
	static ANVIL_STRONG_INLINE float trunc<float>(float a) {
		return std::trunc(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double trunc<double>(double a) {
		return std::trunc(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> trunc(Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = trunc(a[i]);
		return tmp;
	}

	// round

	template<class T>
	static ANVIL_STRONG_INLINE T round(T aValue) {
		return aValue;
	}

	template<>
	static ANVIL_STRONG_INLINE float round<float>(float a) {
		return std::round(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double round<double>(double a) {
		return std::round(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> round(Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = round(a[i]);
		return tmp;
	}
}

#endif