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

#include <cmath>
#include <algorithm>

namespace anvil {

	// abs

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL fabs(T aValue) {
		return anvil::abs(aValue);
	}

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL abs(T aValue) {
		return std::abs(a);
	}

	template<>
	static ANVIL_STRONG_INLINE uint8_t ANVIL_CALL abs<uint8_t>(const uint8_t a) {
		return a;
	}

	template<>
	static ANVIL_STRONG_INLINE uint16_t ANVIL_CALL abs<uint16_t>(const uint16_t a) {
		return a;
	}

	template<>
	static ANVIL_STRONG_INLINE uint32_t ANVIL_CALL abs<uint32_t>(const uint32_t a) {
		return a;
	}

	template<>
	static ANVIL_STRONG_INLINE uint64_t ANVIL_CALL abs<uint64_t>(const uint64_t a) {
		return a;
	}

	template<>
	static ANVIL_STRONG_INLINE float ANVIL_CALL abs<float>(const float a) {
		return std::fabs(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double ANVIL_CALL abs<double>(const double a) {
		return std::fabs(a);
	}

	// mod / fmod

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL fmod(T a, T b) {
		return mod(a, b);
	}

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL mod(T a, T b) {
		return a % b;
	}

	template<>
	static ANVIL_STRONG_INLINE float ANVIL_CALL mod<float>(const float a, const float b) {
		return std::fmod(a,b);
	}

	template<>
	static ANVIL_STRONG_INLINE double ANVIL_CALL mod<double>(const double a, const double b) {
		return std::fmod(a,b);
	}

	// fma

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL fma(T a, T b, T c) {
		return (a * b) + c;
	}

	template<>
	static ANVIL_STRONG_INLINE float ANVIL_CALL fma<float>(const float a, const float b, const float c) {
		return std::fma(a, b, c);
	}

	template<>
	static ANVIL_STRONG_INLINE double ANVIL_CALL fma<double>(const double a, const double b, const double c) {
		return std::fma(a, b, c);
	}

	// max / fmax

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL fmax(T a, T b) {
		return anvil::max(a, b);
	}

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL max(T a, T b) {
		return std::max<T>(a, b);
	}

	// min / fmin

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL fmin(T a, T b) {
		return anvil::min(a, b);
	}

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL min(T a, T b) {
		return std::min<T>(a, b);
	}

	// dif / fdim

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL fdim(T a, T b) {
		return dim(a, b);
	}

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL dim(T a, T b) {
		return a > b ? a - b : static_cast<T>(0);
	}

	template<>
	static ANVIL_STRONG_INLINE float ANVIL_CALL dim<float>(const float a, const float b) {
		return std::fdim(a, b);
	}

	template<>
	static ANVIL_STRONG_INLINE double ANVIL_CALL dim<double>(const double a, const double b) {
		return std::fdim(a, b);
	}

	// exp

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL exp(T aValue) {
		return static_cast<T>(std::exp(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float ANVIL_CALL exp<float>(const float a) {
		return std::exp(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double ANVIL_CALL exp<double>(const double a) {
		return std::exp(a);
	}

	// exp

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL log(T aValue) {
		return static_cast<T>(std::log(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float ANVIL_CALL log<float>(const float a) {
		return std::log(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double ANVIL_CALL log<double>(const double a) {
		return std::log(a);
	}

	// log2

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL log2(T aValue) {
		return static_cast<T>(std::log2(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float ANVIL_CALL log2<float>(const float a) {
		return std::log2(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double ANVIL_CALL log2<double>(const double a) {
		return std::log2(a);
	}

	// log10

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL log10(T aValue) {
		return static_cast<T>(std::log10(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float ANVIL_CALL log10<float>(const float a) {
		return std::log10(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double ANVIL_CALL log10<double>(const double a) {
		return std::log10(a);
	}

	// pow

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL pow(T a, T b) {
		return static_cast<T>(std::pow(static_cast<float>(a), static_cast<float>(b)));
	}

	template<>
	static ANVIL_STRONG_INLINE float ANVIL_CALL pow<float>(const float a, const float b) {
		return std::pow(a, b);
	}

	template<>
	static ANVIL_STRONG_INLINE double ANVIL_CALL pow<double>(const double a, const double b) {
		return std::pow(a, b);
	}

	// sqrt

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL sqrt(T aValue) {
		return static_cast<T>(std::sqrt(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float ANVIL_CALL sqrt<float>(const float a) {
		return std::sqrt(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double ANVIL_CALL sqrt<double>(const double a) {
		return std::sqrt(a);
	}

	// cbrt

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL cbrt(T aValue) {
		return static_cast<T>(std::cbrt(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float ANVIL_CALL cbrt<float>(const float a) {
		return std::cbrt(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double ANVIL_CALL cbrt<double>(const double a) {
		return std::cbrt(a);
	}

	// hypot

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL hypot(T a, T b) {
		return static_cast<T>(std::hypot(static_cast<float>(a), static_cast<float>(b)));
	}

	template<>
	static ANVIL_STRONG_INLINE float ANVIL_CALL hypot<float>(const float a, const float b) {
		return std::hypot(a, b);
	}

	template<>
	static ANVIL_STRONG_INLINE double ANVIL_CALL hypot<double>(const double a, const double b) {
		return std::hypot(a, b);
	}

	// sin

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL sin(T aValue) {
		return static_cast<T>(std::sin(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float ANVIL_CALL sin<float>(const float a) {
		return std::sin(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double ANVIL_CALL sin<double>(const double a) {
		return std::sin(a);
	}

	// cos

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL cos(T aValue) {
		return static_cast<T>(std::cos(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float ANVIL_CALL cos<float>(const float a) {
		return std::cos(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double ANVIL_CALL cos<double>(const double a) {
		return std::cos(a);
	}

	// tan

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL tan(T aValue) {
		return static_cast<T>(std::tan(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float ANVIL_CALL tan<float>(const float a) {
		return std::tan(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double ANVIL_CALL tan<double>(const double a) {
		return std::tan(a);
	}

	// asin

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL asin(T aValue) {
		return static_cast<T>(std::asin(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float ANVIL_CALL asin<float>(const float a) {
		return std::asin(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double ANVIL_CALL asin<double>(const double a) {
		return std::asin(a);
	}

	// acos

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL acos(T aValue) {
		return static_cast<T>(std::acos(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float ANVIL_CALL acos<float>(const float a) {
		return std::acos(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double ANVIL_CALL acos<double>(const double a) {
		return std::acos(a);
	}

	// atan

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL atan(T aValue) {
		return static_cast<T>(std::atan(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float ANVIL_CALL atan<float>(const float a) {
		return std::atan(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double ANVIL_CALL atan<double>(const double a) {
		return std::atan(a);
	}

	// atan2

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL atan2(T a, T b) {
		return static_cast<T>(std::atan2(static_cast<float>(a), static_cast<float>(b)));
	}

	template<>
	static ANVIL_STRONG_INLINE float ANVIL_CALL atan2<float>(const float a, const float b) {
		return std::atan2(a, b);
	}

	template<>
	static ANVIL_STRONG_INLINE double ANVIL_CALL atan2<double>(const double a, const double b) {
		return std::atan2(a, b);
	}

	// sinh

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL sinh(T aValue) {
		return static_cast<T>(std::sinh(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float ANVIL_CALL sinh<float>(const float a) {
		return std::sinh(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double ANVIL_CALL sinh<double>(const double a) {
		return std::sinh(a);
	}

	// cosh

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL cosh(T aValue) {
		return static_cast<T>(std::cosh(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float ANVIL_CALL cosh<float>(const float a) {
		return std::cosh(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double ANVIL_CALL cosh<double>(const double a) {
		return std::cosh(a);
	}

	// tanh

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL tanh(T aValue) {
		return static_cast<T>(std::tanh(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float ANVIL_CALL tanh<float>(const float a) {
		return std::tanh(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double ANVIL_CALL tanh<double>(const double a) {
		return std::tanh(a);
	}

	// asinh

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL asinh(T aValue) {
		return static_cast<T>(std::asinh(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float ANVIL_CALL asinh<float>(const float a) {
		return std::asinh(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double ANVIL_CALL asinh<double>(const double a) {
		return std::asinh(a);
	}

	// acosh

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL acosh(T aValue) {
		return static_cast<T>(std::acosh(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float ANVIL_CALL acosh<float>(const float a) {
		return std::acosh(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double ANVIL_CALL acosh<double>(const double a) {
		return std::acosh(a);
	}

	// atanh

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL atanh(T aValue) {
		return static_cast<T>(std::atanh(static_cast<float>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float ANVIL_CALL atanh<float>(const float a) {
		return std::atanh(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double ANVIL_CALL atanh<double>(const double a) {
		return std::atanh(a);
	}

	// ceil

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL ceil(T aValue) {
		return aValue;
	}

	template<>
	static ANVIL_STRONG_INLINE float ANVIL_CALL ceil<float>(const float a) {
		return std::ceil(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double ANVIL_CALL ceil<double>(const double a) {
		return std::ceil(a);
	}

	// floor

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL floor(T aValue) {
		return aValue;
	}

	template<>
	static ANVIL_STRONG_INLINE float ANVIL_CALL floor<float>(const float a) {
		return std::floor(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double ANVIL_CALL floor<double>(const double a) {
		return std::floor(a);
	}

	// trunc

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL trunc(T aValue) {
		return aValue;
	}

	template<>
	static ANVIL_STRONG_INLINE float ANVIL_CALL trunc<float>(const float a) {
		return std::trunc(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double ANVIL_CALL trunc<double>(const double a) {
		return std::trunc(a);
	}

	// round

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL round(T aValue) {
		return aValue;
	}

	template<>
	static ANVIL_STRONG_INLINE float ANVIL_CALL round<float>(const float a) {
		return std::round(a);
	}

	template<>
	static ANVIL_STRONG_INLINE double ANVIL_CALL round<double>(const double a) {
		return std::round(a);
	}
}

#endif