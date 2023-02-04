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
	ANVIL_STRONG_INLINE T ANVIL_CALL abs(T a) {
	    if ANVIL_CONSTEXPR_FN (std::is_same<T,uint8_t>::value || std::is_same<T,uint16_t>::value || std::is_same<T,uint32_t>::value || std::is_same<T,uint64_t>::value) {
            return a;
	    } else if ANVIL_CONSTEXPR_FN (std::is_same<T,float>::value || std::is_same<T,double>::value) {
            return std::fabs(a);
	    } else {
            return std::abs(a);
	    }
	}

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL fabs(T a) {
		return anvil::abs<T>(a);
	}

	// mod / fmod

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL mod(T a, T b) {
	    if ANVIL_CONSTEXPR_FN (std::is_same<T,float>::value || std::is_same<T,double>::value) {
            return std::fmod(a,b);
	    } else {
            return a % b;
	    }
	}

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL fmod(T a, T b) {
		return mod(a, b);
	}

	// fma

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL fma(T a, T b, T c) {
	    if ANVIL_CONSTEXPR_FN (std::is_same<T,float>::value || std::is_same<T,double>::value) {
            return std::fma(a, b, c);
	    } else {
            return (a * b) + c;
	    }
	}

	// fms

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL fms(T a, T b, T c) {
		return (a * b) - c;
	}

	// max / fmax

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL max(T a, T b) {
		return std::max<T>(a, b);
	}

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL fmax(T a, T b) {
		return anvil::max(a, b);
	}

	// min / fmin

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL min(T a, T b) {
		return std::min<T>(a, b);
	}

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL fmin(T a, T b) {
		return anvil::min(a, b);
	}

	// dif / fdim

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL dim(T a, T b) {
	    if ANVIL_CONSTEXPR_FN (std::is_same<T,float>::value || std::is_same<T,double>::value) {
            return std::fdim(a, b);
	    } else {
            return a > b ? a - b : static_cast<T>(0);
	    }
	}

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL fdim(T a, T b) {
		return dim(a, b);
	}

	// exp

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL exp(T a) {
        if ANVIL_CONSTEXPR_FN (std::is_same<T,float>::value || std::is_same<T,double>::value) {
            return std::exp(a);
	    } else {
            return static_cast<T>(std::exp(static_cast<float32_t>(a)));
	    }
	}

	// log

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL log(T a) {
        if ANVIL_CONSTEXPR_FN (std::is_same<T,float>::value || std::is_same<T,double>::value) {
            return std::log(a);
	    } else {
            return static_cast<T>(std::log(static_cast<float32_t>(a)));
	    }
	}

	// log2

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL log2(T a) {
        if ANVIL_CONSTEXPR_FN (std::is_same<T,float>::value || std::is_same<T,double>::value) {
            return std::log2(a);
	    } else {
            return static_cast<T>(std::log2(static_cast<float32_t>(a)));
	    }
	}

	// log10

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL log10(T a) {
        if ANVIL_CONSTEXPR_FN (std::is_same<T,float>::value || std::is_same<T,double>::value) {
            return std::log10(a);
	    } else {
            return static_cast<T>(std::log10(static_cast<float32_t>(a)));
	    }
	}

	// pow

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL pow(T a, T b) {
        if ANVIL_CONSTEXPR_FN (std::is_same<T,float>::value || std::is_same<T,double>::value) {
            return std::pow(a, b);
	    } else {
            static_cast<T>(std::pow(static_cast<float32_t>(a), static_cast<float32_t>(b)));
	    }
	}

	// sqrt

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL sqrt(T a) {
        if ANVIL_CONSTEXPR_FN (std::is_same<T,float>::value || std::is_same<T,double>::value) {
            return std::sqrt(a);
	    } else {
            return static_cast<T>(std::sqrt(static_cast<float32_t>(a)));
	    }
	}

	// cbrt

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL cbrt(T a) {
        if ANVIL_CONSTEXPR_FN (std::is_same<T,float>::value || std::is_same<T,double>::value) {
            return std::cbrt(a);
	    } else {
            return static_cast<T>(std::cbrt(static_cast<float32_t>(a)));
	    }
	}

	// hypot

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL hypot(T a, T b) {
	    if ANVIL_CONSTEXPR_FN (std::is_same<T,float>::value || std::is_same<T,double>::value) {
            return std::hypot(a, b);
	    } else {
            static_cast<T>(std::hypot(static_cast<float32_t>(a), static_cast<float32_t>(b)));
	    }
	}

	// sin

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL sin(T a) {
        if ANVIL_CONSTEXPR_FN (std::is_same<T,float>::value || std::is_same<T,double>::value) {
            return std::sin(a);
	    } else {
            return static_cast<T>(std::sin(static_cast<float32_t>(a)));
	    }
	}

	// cos

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL cos(T a) {
        if ANVIL_CONSTEXPR_FN (std::is_same<T,float>::value || std::is_same<T,double>::value) {
            return std::cos(a);
	    } else {
            return static_cast<T>(std::cos(static_cast<float32_t>(a)));
	    }
	}

	// tan

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL tan(T a) {
        if ANVIL_CONSTEXPR_FN (std::is_same<T,float>::value || std::is_same<T,double>::value) {
            return std::tan(a);
	    } else {
            return static_cast<T>(std::tan(static_cast<float32_t>(a)));
	    }
	}

	// asin

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL asin(T a) {
        if ANVIL_CONSTEXPR_FN (std::is_same<T,float>::value || std::is_same<T,double>::value) {
            return std::asin(a);
	    } else {
            return static_cast<T>(std::asin(static_cast<float32_t>(a)));
	    }
	}

	// acos

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL acos(T a) {
        if ANVIL_CONSTEXPR_FN (std::is_same<T,float>::value || std::is_same<T,double>::value) {
            return std::acos(a);
	    } else {
            return static_cast<T>(std::acos(static_cast<float32_t>(a)));
	    }
	}

	// atan

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL atan(T a) {
        if ANVIL_CONSTEXPR_FN (std::is_same<T,float>::value || std::is_same<T,double>::value) {
            return std::atan(a);
	    } else {
            return static_cast<T>(std::atan(static_cast<float32_t>(a)));
	    }
	}

	// atan2

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL atan2(T a, T b) {
        if ANVIL_CONSTEXPR_FN (std::is_same<T,float>::value || std::is_same<T,double>::value) {
            return std::atan2(a, b);
	    } else {
            return static_cast<T>(std::atan2(static_cast<float32_t>(a), static_cast<float32_t>(b)));
	    };
	}

	// sinh

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL sinh(T a) {
        if ANVIL_CONSTEXPR_FN (std::is_same<T,float>::value || std::is_same<T,double>::value) {
            return std::sinh(a);
	    } else {
            return static_cast<T>(std::sinh(static_cast<float32_t>(a)));
	    }
	}

	// cosh

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL cosh(T a) {
        if ANVIL_CONSTEXPR_FN (std::is_same<T,float>::value || std::is_same<T,double>::value) {
            return std::cosh(a);
	    } else {
            return static_cast<T>(std::cosh(static_cast<float32_t>(a)));
	    }
	}

	// tanh

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL tanh(T a) {
        if ANVIL_CONSTEXPR_FN (std::is_same<T,float>::value || std::is_same<T,double>::value) {
            return std::tanh(a);
	    } else {
            return static_cast<T>(std::tanh(static_cast<float32_t>(a)));
	    }
	}

	// asinh

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL asinh(T a) {
        if ANVIL_CONSTEXPR_FN (std::is_same<T,float>::value || std::is_same<T,double>::value) {
            return std::asinh(a);
	    } else {
            return static_cast<T>(std::asinh(static_cast<float32_t>(a)));
	    }
	}

	// aacosh

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL acosh(T a) {
        if ANVIL_CONSTEXPR_FN (std::is_same<T,float>::value || std::is_same<T,double>::value) {
            return std::acosh(a);
	    } else {
            return static_cast<T>(std::acosh(static_cast<float32_t>(a)));
	    }
	}

	// atanh

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL atanh(T a) {
        if ANVIL_CONSTEXPR_FN (std::is_same<T,float>::value || std::is_same<T,double>::value) {
            return std::atanh(a);
	    } else {
            return static_cast<T>(std::atanh(static_cast<float32_t>(a)));
	    }
	}

	// ceil

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL ceil(T a) {
        if ANVIL_CONSTEXPR_FN (std::is_same<T,float>::value || std::is_same<T,double>::value) {
            return std::ceil(a);
	    } else {
            return a;
	    }
	}

	// floor

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL floor(T a) {
        if ANVIL_CONSTEXPR_FN (std::is_same<T,float>::value || std::is_same<T,double>::value) {
            return std::floor(a);
	    } else {
            return a;
	    }
	}

	// trunc

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL trunc(T a) {
        if ANVIL_CONSTEXPR_FN (std::is_same<T,float>::value || std::is_same<T,double>::value) {
            return std::trunc(a);
	    } else {
            return a;
	    }
	}

	// round

	template<class T>
	ANVIL_STRONG_INLINE T ANVIL_CALL round(T a) {
        if ANVIL_CONSTEXPR_FN (std::is_same<T,float>::value || std::is_same<T,double>::value) {
            return std::round(a);
	    } else {
            return a;
	    }
	}
}

#endif
