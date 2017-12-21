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
	static ANVIL_STRONG_INLINE const float abs<float>(const float a) {
		return std::abs(a);
	}

	template<>
	static ANVIL_STRONG_INLINE const double abs<double>(const double a) {
		return std::abs(a);
	}

	template<class T, size_t S>
	static inline const Vector<T, S> abs(const Vector<T, S> a) {
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
	static ANVIL_STRONG_INLINE float mod<float>(const float a, const float b) {
		return std::fmod(a,b);
	}

	template<>
	static ANVIL_STRONG_INLINE double mod<double>(const double a, const double b) {
		return std::fmod(a,b);
	}

	template<class T, size_t S>
	static inline const Vector<T, S> abs(const Vector<T, S> a, const Vector<T, S> b) {
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
	static ANVIL_STRONG_INLINE float fma<float>(const float a, const float b, const float c) {
		return std::fma(a, b, c);
	}

	template<>
	static ANVIL_STRONG_INLINE double fma<double>(const double a, const double b, const double c) {
		return std::fma(a, b, c);
	}

	template<class T, size_t S>
	static inline Vector<T, S> fma(const Vector<T, S> a, const Vector<T, S> b, const Vector<T, S> c) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = fma(a[i], b[i], c[i]);
		return tmp;
	}

	// max / fmax

	template<class T>
	static ANVIL_STRONG_INLINE T fmax(T a, T b) {
		return detail::vmax(a, b);
	}

	template<class T>
	static ANVIL_STRONG_INLINE T max(T a, T b) {
		return detail::vmax<T>(a, b);
	}

	template<class T, size_t S>
	static inline Vector<T, S> max(const Vector<T, S> a, const Vector<T, S> b) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = max(a[i], b[i]);
		return tmp;
	}

	// min / fmin

	template<class T>
	static ANVIL_STRONG_INLINE T fmin(T a, T b) {
		return detail::vmin(a, b);
	}

	template<class T>
	static ANVIL_STRONG_INLINE T min(T a, T b) {
		return detail::vmin<T>(a, b);
	}

	template<class T, size_t S>
	static inline Vector<T, S> min(const Vector<T, S> a, const Vector<T, S> b) {
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
	static ANVIL_STRONG_INLINE float dif<float>(const float a, const float b) {
		return std::fdim(a, b);
	}

	template<>
	static ANVIL_STRONG_INLINE double dif<double>(const double a, const double b) {
		return std::fdim(a, b);
	}

	template<class T, size_t S>
	static inline Vector<T, S> dif(const Vector<T, S> a, const Vector<T, S> b) {
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
	static ANVIL_STRONG_INLINE float exp<float>(const float a) {
		return std::exp(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double exp<double>(const double a) {
		return std::exp(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> exp(const Vector<T, S> a) {
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
	static ANVIL_STRONG_INLINE float log<float>(const float a) {
		return std::log(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double log<double>(const double a) {
		return std::log(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> log(const Vector<T, S> a) {
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
	static ANVIL_STRONG_INLINE float log2<float>(const float a) {
		return std::log2(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double log2<double>(const double a) {
		return std::log2(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> log2(const Vector<T, S> a) {
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
	static ANVIL_STRONG_INLINE float log10<float>(const float a) {
		return std::log10(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double log10<double>(const double a) {
		return std::log10(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> log10(const Vector<T, S> a) {
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
	static ANVIL_STRONG_INLINE float pow<float>(const float a, const float b) {
		return std::pow(a, b);
	}

	template<>
	static ANVIL_STRONG_INLINE double pow<double>(const double a, const double b) {
		return std::pow(a, b);
	}

	template<class T, size_t S>
	static inline Vector<T, S> pow(const Vector<T, S> a, const Vector<T, S> b) {
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
	static ANVIL_STRONG_INLINE float sqrt<float>(const float a) {
		return std::sqrt(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double sqrt<double>(const double a) {
		return std::sqrt(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> sqrt(const Vector<T, S> a) {
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
	static ANVIL_STRONG_INLINE float cbrt<float>(const float a) {
		return std::cbrt(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double cbrt<double>(const double a) {
		return std::cbrt(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> cbrt(const Vector<T, S> a) {
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
	static ANVIL_STRONG_INLINE float cbrt<float>(const float a) {
		return std::cbrt(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double cbrt<double>(const double a) {
		return std::cbrt(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> cbrt(const Vector<T, S> a) {
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
	static ANVIL_STRONG_INLINE float hypot<float>(const float a, const float b) {
		return std::hypot(a, b);
	}

	template<>
	static ANVIL_STRONG_INLINE double hypot<double>(const double a, const double b) {
		return std::hypot(a, b);
	}

	template<class T, size_t S>
	static inline Vector<T, S> hypot(const Vector<T, S> a, const Vector<T, S> b) {
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
	static ANVIL_STRONG_INLINE float sin<float>(const float a) {
		return std::sin(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double sin<double>(const double a) {
		return std::sin(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> sin(const Vector<T, S> a) {
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
	static ANVIL_STRONG_INLINE float cos<float>(const float a) {
		return std::cos(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double cos<double>(const double a) {
		return std::cos(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> cos(const Vector<T, S> a) {
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
	static ANVIL_STRONG_INLINE float tan<float>(const float a) {
		return std::tan(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double tan<double>(const double a) {
		return std::tan(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> tan(const Vector<T, S> a) {
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
	static ANVIL_STRONG_INLINE const float asin<float>(const float a) {
		return std::asin(a);
	}

	template<>
	static ANVIL_STRONG_INLINE const double asin<double>(const double a) {
		return std::asin(a);
	}

	template<class T, size_t S>
	static inline const Vector<T, S> asin(const Vector<T, S> a) {
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
	static ANVIL_STRONG_INLINE const float acos<float>(const float a) {
		return std::acos(a);
	}

	template<>
	static ANVIL_STRONG_INLINE const double acos<double>(const double a) {
		return std::acos(a);
	}

	template<class T, size_t S>
	static inline const Vector<T, S> acos(const Vector<T, S> a) {
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
	static ANVIL_STRONG_INLINE const float atan<float>(const float a) {
		return std::atan(a);
	}

	template<>
	static ANVIL_STRONG_INLINE const double atan<double>(const double a) {
		return std::atan(a);
	}

	template<class T, size_t S>
	static inline const Vector<T, S> atan(const Vector<T, S> a) {
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
	static ANVIL_STRONG_INLINE const float atan2<float>(const float a, const float b) {
		return std::atan2(a, b);
	}

	template<>
	static ANVIL_STRONG_INLINE const double atan2<double>(const double a, const double b) {
		return std::atan2(a, b);
	}

	template<class T, size_t S>
	static inline const Vector<T, S> atan2(const Vector<T, S> a, const Vector<T, S> b) {
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
	static ANVIL_STRONG_INLINE float sinh<float>(const float a) {
		return std::sinh(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double sinh<double>(const double a) {
		return std::sinh(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> sinh(const Vector<T, S> a) {
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
	static ANVIL_STRONG_INLINE float cosh<float>(const float a) {
		return std::cosh(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double cosh<double>(const double a) {
		return std::cosh(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> cosh(const Vector<T, S> a) {
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
	static ANVIL_STRONG_INLINE float tanh<float>(const float a) {
		return std::tanh(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double tanh<double>(const double a) {
		return std::tanh(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> tanh(const Vector<T, S> a) {
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
	static ANVIL_STRONG_INLINE const float asinh<float>(const float a) {
		return std::asinh(a);
	}

	template<>
	static ANVIL_STRONG_INLINE const double asinh<double>(const double a) {
		return std::asinh(a);
	}

	template<class T, size_t S>
	static inline const Vector<T, S> asinh(const Vector<T, S> a) {
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
	static ANVIL_STRONG_INLINE const float acosh<float>(const float a) {
		return std::acosh(a);
	}

	template<>
	static ANVIL_STRONG_INLINE const double acosh<double>(const double a) {
		return std::acosh(a);
	}

	template<class T, size_t S>
	static inline const Vector<T, S> acosh(const Vector<T, S> a) {
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
	static ANVIL_STRONG_INLINE const float atanh<float>(const float a) {
		return std::atanh(a);
	}

	template<>
	static ANVIL_STRONG_INLINE const double atanh<double>(const double a) {
		return std::atanh(a);
	}

	template<class T, size_t S>
	static inline const Vector<T, S> atanh(const Vector<T, S> a) {
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
	static ANVIL_STRONG_INLINE float ceil<float>(const float a) {
		return std::ceil(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double ceil<double>(const double a) {
		return std::ceil(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> ceil(const Vector<T, S> a) {
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
	static ANVIL_STRONG_INLINE float floor<float>(const float a) {
		return std::floor(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double floor<double>(const double a) {
		return std::floor(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> floor(const Vector<T, S> a) {
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
	static ANVIL_STRONG_INLINE float trunc<float>(const float a) {
		return std::trunc(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double trunc<double>(const double a) {
		return std::trunc(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> trunc(const Vector<T, S> a) {
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
	static ANVIL_STRONG_INLINE float round<float>(const float a) {
		return std::round(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double round<double>(const double a) {
		return std::round(a);
	}

	template<class T, size_t S>
	static inline Vector<T, S> round(const Vector<T, S> a) {
		Vector<T, S> tmp;
		for (size_t i = 0; i < S; ++i) tmp[i] = round(a[i]);
		return tmp;
	}
}

#endif