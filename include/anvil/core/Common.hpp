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
#include "anvil/core/Keywords.hpp"

namespace anvil {

	// abs

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL abs(T a) {
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
	static ANVIL_STRONG_INLINE float32_t ANVIL_CALL abs<float32_t>(const float32_t a) {
		return std::fabs(a);
	}

	template<>
	static ANVIL_STRONG_INLINE float64_t ANVIL_CALL abs<float64_t>(const float64_t a) {
		return std::fabs(a);
	}

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL fabs(T a) {
		return anvil::abs(a);
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
	static ANVIL_STRONG_INLINE float32_t ANVIL_CALL mod<float32_t>(const float32_t a, const float32_t b) {
		return std::fmod(a,b);
	}

	template<>
	static ANVIL_STRONG_INLINE float64_t ANVIL_CALL mod<float64_t>(const float64_t a, const float64_t b) {
		return std::fmod(a,b);
	}

	// fma

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL fma(T a, T b, T c) {
		return (a * b) + c;
	}

	template<>
	static ANVIL_STRONG_INLINE float32_t ANVIL_CALL fma<float32_t>(const float32_t a, const float32_t b, const float32_t c) {
		return std::fma(a, b, c);
	}

	template<>
	static ANVIL_STRONG_INLINE float64_t ANVIL_CALL fma<float64_t>(const float64_t a, const float64_t b, const float64_t c) {
		return std::fma(a, b, c);
	}

	// fms

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL fms(T a, T b, T c) {
		return (a * b) - c;
	}

	// max / fmax

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL max(T a, T b) {
		return std::max<T>(a, b);
	}

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL fmax(T a, T b) {
		return anvil::max(a, b);
	}

	// min / fmin

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL min(T a, T b) {
		return std::min<T>(a, b);
	}

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL fmin(T a, T b) {
		return anvil::min(a, b);
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
	static ANVIL_STRONG_INLINE float32_t ANVIL_CALL dim<float32_t>(const float32_t a, const float32_t b) {
		return std::fdim(a, b);
	}

	template<>
	static ANVIL_STRONG_INLINE float64_t ANVIL_CALL dim<float64_t>(const float64_t a, const float64_t b) {
		return std::fdim(a, b);
	}

	// exp

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL exp(T a) {
		return static_cast<T>(std::exp(static_cast<float32_t>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float32_t ANVIL_CALL exp<float32_t>(const float32_t a) {
		return std::exp(a);
	}

	template<>
	static ANVIL_STRONG_INLINE float64_t ANVIL_CALL exp<float64_t>(const float64_t a) {
		return std::exp(a);
	}

	// log

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL log(T a) {
		return static_cast<T>(std::log(static_cast<float32_t>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float32_t ANVIL_CALL log<float32_t>(const float32_t a) {
		return std::log(a);
	}

	template<>
	static ANVIL_STRONG_INLINE float64_t ANVIL_CALL log<float64_t>(const float64_t a) {
		return std::log(a);
	}

	// log2

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL log2(T a) {
		return static_cast<T>(std::log2(static_cast<float32_t>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float32_t ANVIL_CALL log2<float32_t>(const float32_t a) {
		return std::log2(a);
	}

	template<>
	static ANVIL_STRONG_INLINE float64_t ANVIL_CALL log2<float64_t>(const float64_t a) {
		return std::log2(a);
	}

	// log10

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL log10(T a) {
		return static_cast<T>(std::log10(static_cast<float32_t>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float32_t ANVIL_CALL log10<float32_t>(const float32_t a) {
		return std::log10(a);
	}

	template<>
	static ANVIL_STRONG_INLINE float64_t ANVIL_CALL log10<float64_t>(const float64_t a) {
		return std::log10(a);
	}

	// pow

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL pow(T a, T b) {
		return static_cast<T>(std::pow(static_cast<float32_t>(a), static_cast<float32_t>(b)));
	}

	template<>
	static ANVIL_STRONG_INLINE float32_t ANVIL_CALL pow<float32_t>(const float32_t a, const float32_t b) {
		return std::pow(a, b);
	}

	template<>
	static ANVIL_STRONG_INLINE float64_t ANVIL_CALL pow<float64_t>(const float64_t a, const float64_t b) {
		return std::pow(a, b);
	}

	// sqrt

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL sqrt(T a) {
		return static_cast<T>(std::sqrt(static_cast<float32_t>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float32_t ANVIL_CALL sqrt<float32_t>(const float32_t a) {
		return std::sqrt(a);
	}

	template<>
	static ANVIL_STRONG_INLINE float64_t ANVIL_CALL sqrt<float64_t>(const float64_t a) {
		return std::sqrt(a);
	}

	// cbrt

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL cbrt(T a) {
		return static_cast<T>(std::cbrt(static_cast<float32_t>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float32_t ANVIL_CALL cbrt<float32_t>(const float32_t a) {
		return std::cbrt(a);
	}

	template<>
	static ANVIL_STRONG_INLINE float64_t ANVIL_CALL cbrt<float64_t>(const float64_t a) {
		return std::cbrt(a);
	}

	// hypot

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL hypot(T a, T b) {
		return static_cast<T>(std::hypot(static_cast<float32_t>(a), static_cast<float32_t>(b)));
	}

	template<>
	static ANVIL_STRONG_INLINE float32_t ANVIL_CALL hypot<float32_t>(const float32_t a, const float32_t b) {
		return std::hypot(a, b);
	}

	template<>
	static ANVIL_STRONG_INLINE float64_t ANVIL_CALL hypot<float64_t>(const float64_t a, const float64_t b) {
		return std::hypot(a, b);
	}

	// sin

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL sin(T a) {
		return static_cast<T>(std::sin(static_cast<float32_t>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float32_t ANVIL_CALL sin<float32_t>(const float32_t a) {
		return std::sin(a);
	}

	template<>
	static ANVIL_STRONG_INLINE float64_t ANVIL_CALL sin<float64_t>(const float64_t a) {
		return std::sin(a);
	}

	// cos

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL cos(T a) {
		return static_cast<T>(std::cos(static_cast<float32_t>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float32_t ANVIL_CALL cos<float32_t>(const float32_t a) {
		return std::cos(a);
	}

	template<>
	static ANVIL_STRONG_INLINE float64_t ANVIL_CALL cos<float64_t>(const float64_t a) {
		return std::cos(a);
	}

	// tan

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL tan(T a) {
		return static_cast<T>(std::tan(static_cast<float32_t>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float32_t ANVIL_CALL tan<float32_t>(const float32_t a) {
		return std::tan(a);
	}

	template<>
	static ANVIL_STRONG_INLINE float64_t ANVIL_CALL tan<float64_t>(const float64_t a) {
		return std::tan(a);
	}

	// asin

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL asin(T a) {
		return static_cast<T>(std::asin(static_cast<float32_t>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float32_t ANVIL_CALL asin<float32_t>(const float32_t a) {
		return std::asin(a);
	}

	template<>
	static ANVIL_STRONG_INLINE float64_t ANVIL_CALL asin<float64_t>(const float64_t a) {
		return std::asin(a);
	}

	// acos

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL acos(T a) {
		return static_cast<T>(std::acos(static_cast<float32_t>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float32_t ANVIL_CALL acos<float32_t>(const float32_t a) {
		return std::acos(a);
	}

	template<>
	static ANVIL_STRONG_INLINE float64_t ANVIL_CALL acos<float64_t>(const float64_t a) {
		return std::acos(a);
	}

	// atan

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL atan(T a) {
		return static_cast<T>(std::atan(static_cast<float32_t>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float32_t ANVIL_CALL atan<float32_t>(const float32_t a) {
		return std::atan(a);
	}

	template<>
	static ANVIL_STRONG_INLINE float64_t ANVIL_CALL atan<float64_t>(const float64_t a) {
		return std::atan(a);
	}

	// atan2

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL atan2(T a, T b) {
		return static_cast<T>(std::atan2(static_cast<float32_t>(a), static_cast<float32_t>(b)));
	}

	template<>
	static ANVIL_STRONG_INLINE float32_t ANVIL_CALL atan2<float32_t>(const float32_t a, const float32_t b) {
		return std::atan2(a, b);
	}

	template<>
	static ANVIL_STRONG_INLINE float64_t ANVIL_CALL atan2<float64_t>(const float64_t a, const float64_t b) {
		return std::atan2(a, b);
	}

	// sinh

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL sinh(T a) {
		return static_cast<T>(std::sinh(static_cast<float32_t>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float32_t ANVIL_CALL sinh<float32_t>(const float32_t a) {
		return std::sinh(a);
	}

	template<>
	static ANVIL_STRONG_INLINE float64_t ANVIL_CALL sinh<float64_t>(const float64_t a) {
		return std::sinh(a);
	}

	// cosh

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL cosh(T a) {
		return static_cast<T>(std::cosh(static_cast<float32_t>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float32_t ANVIL_CALL cosh<float32_t>(const float32_t a) {
		return std::cosh(a);
	}

	template<>
	static ANVIL_STRONG_INLINE float64_t ANVIL_CALL cosh<float64_t>(const float64_t a) {
		return std::cosh(a);
	}

	// tanh

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL tanh(T a) {
		return static_cast<T>(std::tanh(static_cast<float32_t>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float32_t ANVIL_CALL tanh<float32_t>(const float32_t a) {
		return std::tanh(a);
	}

	template<>
	static ANVIL_STRONG_INLINE float64_t ANVIL_CALL tanh<float64_t>(const float64_t a) {
		return std::tanh(a);
	}

	// asinh

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL asinh(T a) {
		return static_cast<T>(std::asinh(static_cast<float32_t>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float32_t ANVIL_CALL asinh<float32_t>(const float32_t a) {
		return std::asinh(a);
	}

	template<>
	static ANVIL_STRONG_INLINE float64_t ANVIL_CALL asinh<float64_t>(const float64_t a) {
		return std::asinh(a);
	}

	// acosh

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL acosh(T a) {
		return static_cast<T>(std::acosh(static_cast<float32_t>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float32_t ANVIL_CALL acosh<float32_t>(const float32_t a) {
		return std::acosh(a);
	}

	template<>
	static ANVIL_STRONG_INLINE float64_t ANVIL_CALL acosh<float64_t>(const float64_t a) {
		return std::acosh(a);
	}

	// atanh

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL atanh(T a) {
		return static_cast<T>(std::atanh(static_cast<float32_t>(a)));
	}

	template<>
	static ANVIL_STRONG_INLINE float32_t ANVIL_CALL atanh<float32_t>(const float32_t a) {
		return std::atanh(a);
	}

	template<>
	static ANVIL_STRONG_INLINE float64_t ANVIL_CALL atanh<float64_t>(const float64_t a) {
		return std::atanh(a);
	}

	// ceil

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL ceil(T a) {
		return a;
	}

	template<>
	static ANVIL_STRONG_INLINE float32_t ANVIL_CALL ceil<float32_t>(const float32_t a) {
		return std::ceil(a);
	}

	template<>
	static ANVIL_STRONG_INLINE float64_t ANVIL_CALL ceil<float64_t>(const float64_t a) {
		return std::ceil(a);
	}

	// floor

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL floor(T a) {
		return a;
	}

	template<>
	static ANVIL_STRONG_INLINE float32_t ANVIL_CALL floor<float32_t>(const float32_t a) {
		return std::floor(a);
	}

	template<>
	static ANVIL_STRONG_INLINE float64_t ANVIL_CALL floor<float64_t>(const float64_t a) {
		return std::floor(a);
	}

	// trunc

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL trunc(T a) {
		return a;
	}

	template<>
	static ANVIL_STRONG_INLINE float32_t ANVIL_CALL trunc<float32_t>(const float32_t a) {
		return std::trunc(a);
	}

	template<>
	static ANVIL_STRONG_INLINE float64_t ANVIL_CALL trunc<float64_t>(const float64_t a) {
		return std::trunc(a);
	}

	// round

	template<class T>
	static ANVIL_STRONG_INLINE T ANVIL_CALL round(T a) {
		return a;
	}

	template<>
	static ANVIL_STRONG_INLINE float32_t ANVIL_CALL round<float32_t>(const float32_t a) {
		return std::round(a);
	}

	template<>
	static ANVIL_STRONG_INLINE float64_t ANVIL_CALL round<float64_t>(const float64_t a) {
		return std::round(a);
	}
}

#endif