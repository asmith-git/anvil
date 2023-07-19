//Copyright 2023 Adam G. Smith
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

#ifndef ANVIL_COMPUTE_ARITHMETIC_CPP_HPP
#define ANVIL_COMPUTE_ARITHMETIC_CPP_HPP

#include "anvil/compute/Arithmetic.hpp"
#include "anvil/compute/details/ArithmeticMultiChannel.hpp"
#include <cmath>

namespace anvil { namespace compute { namespace details {

	template<size_t BYTES> struct ArithOpBitwiseType;

	template<> struct ArithOpBitwiseType<1u> { typedef uint8_t type; };
	template<> struct ArithOpBitwiseType<2u> { typedef uint16_t type; };
	template<> struct ArithOpBitwiseType<4u> { typedef uint32_t type; };
	template<> struct ArithOpBitwiseType<8u> { typedef uint64_t type; };

	template<size_t BYTES>
	class ArithOpBitwise {
	public:
		typedef typename ArithOpBitwiseType<BYTES>::type T;

		static void Not(const void* src, void* dst, size_t count) {
			const T* src2 = static_cast<const T*>(src);
			T* dst2 = static_cast<T*>(dst);
			for (size_t i = 0u; i < count; ++i) dst2[i] = ~src2[i];
		}

		static void And(const void* lhs, const void* rhs, void* dst, size_t count) {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);
			for (size_t i = 0u; i < count; ++i) dst2[i] = lhs2[i] & rhs2[i];
		}

		static void Or(const void* lhs, const void* rhs, void* dst, size_t count) {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);
			for (size_t i = 0u; i < count; ++i) dst2[i] = lhs2[i] | rhs2[i];
		}

		static void Xor(const void* lhs, const void* rhs, void* dst, size_t count) {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);
			for (size_t i = 0u; i < count; ++i) dst2[i] = lhs2[i] ^ rhs2[i];
		}

		static void Nand(const void* lhs, const void* rhs, void* dst, size_t count) {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);
			for (size_t i = 0u; i < count; ++i) dst2[i] = ~(lhs2[i] & rhs2[i]);
		}

		static void Nor(const void* lhs, const void* rhs, void* dst, size_t count) {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);
			for (size_t i = 0u; i < count; ++i) dst2[i] = ~(lhs2[i] | rhs2[i]);
		}

		static void Xnor(const void* lhs, const void* rhs, void* dst, size_t count) {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);
			for (size_t i = 0u; i < count; ++i) dst2[i] = ~(lhs2[i] ^ rhs2[i]);
		}

		static void Mask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			while (count >= 8u) {
				const size_t m = *mask;
				++mask;

				dst2[0u] = (m & 1u ? lhs2 : rhs2)[0u];
				dst2[1u] = (m & 2u ? lhs2 : rhs2)[1u];
				dst2[2u] = (m & 4u ? lhs2 : rhs2)[2u];
				dst2[3u] = (m & 8u ? lhs2 : rhs2)[3u];
				dst2[4u] = (m & 16u ? lhs2 : rhs2)[4u];
				dst2[5u] = (m & 32u ? lhs2 : rhs2)[5u];
				dst2[6u] = (m & 64u ? lhs2 : rhs2)[6u];
				dst2[7u] = (m & 128u ? lhs2 : rhs2)[7u];

				lhs2 -= 8u;
				rhs2 -= 8u;
				dst2 -= 8u;
			}

			size_t m = *mask;
			for (size_t i = 0u; i < count; ++i) {
				dst2[i] = (m & 1u ? lhs2 : rhs2)[i];
				m >>= 1u;
			}
		}
	};

	template<class T>
	class ArithmeticOperationsCpp : public ArithmeticOperations {
	private:
		template<bool APPLY_TO_INTEGER>
		static void CallCMathOperation(const void* src, void* dst, size_t count, float(*f32)(float), double(*f64)(double)) {
			const T* src2 = static_cast<const T*>(src);
			T* dst2 = static_cast<T*>(dst);

			if ANVIL_CONSTEXPR_VAR (std::is_integral<T>::value) {
				if ANVIL_CONSTEXPR_VAR(APPLY_TO_INTEGER) {
					for (size_t i = 0u; i < count; ++i) {
						dst2[i] = static_cast<T>(std::round(f32(static_cast<float>(src2[i]))));
					}
				} else {
					memcpy(dst, src, sizeof(T) * count);
				}
			} else if ANVIL_CONSTEXPR_VAR(std::is_same<T, double>::value) {
				for (size_t i = 0u; i < count; ++i) {
					dst2[i] = f64(src2[i]);
				}
			} else {
				for (size_t i = 0u; i < count; ++i) {
					dst2[i] = static_cast<T>(f32(static_cast<float>(src2[i])));
				}
			}
		}
	public:

		ArithmeticOperationsCpp() :
			ArithmeticOperations(EnumFromType<T>::value)
		{}

		virtual ~ArithmeticOperationsCpp() {

		}

		// 1 input

		virtual void Sqrt(const void* src, void* dst, size_t count) const {
			CallCMathOperation<true>(src, dst, count, &std::sqrtf, &std::sqrt);
		}

		virtual void Cbrt(const void* src, void* dst, size_t count) const {
			CallCMathOperation<true>(src, dst, count, &std::cbrtf, &std::cbrt);
		}


		virtual void Not(const void* src, void* dst, size_t count) const {
			ArithOpBitwise<sizeof(T)>::Not(src, dst, count);
		}
		
		virtual void Round(const void* src, void* dst, size_t count) const {
			CallCMathOperation<false>(src, dst, count, &std::roundf, &std::round);
		}

		virtual void Floor(const void* src, void* dst, size_t count) const {
			CallCMathOperation<false>(src, dst, count, &std::floorf, &std::floor);
		}

		virtual void Ceil(const void* src, void* dst, size_t count) const {
			CallCMathOperation<false>(src, dst, count, &std::ceilf, &std::ceil);
		}

		virtual void Cos(const void* src, void* dst, size_t count) const {
			CallCMathOperation<true>(src, dst, count, &std::cosf, &std::cos);
		}

		virtual void Sin(const void* src, void* dst, size_t count) const {
			CallCMathOperation<true>(src, dst, count, &std::sinf, &std::sin);
		}

		virtual void Tan(const void* src, void* dst, size_t count) const {
			CallCMathOperation<true>(src, dst, count, &std::tanf, &std::tan);
		}

		virtual void Acos(const void* src, void* dst, size_t count) const {
			CallCMathOperation<true>(src, dst, count, &std::acosf, &std::acos);
		}

		virtual void Asin(const void* src, void* dst, size_t count) const {
			CallCMathOperation<true>(src, dst, count, &std::asinf, &std::asin);
		}

		virtual void Atan(const void* src, void* dst, size_t count) const {
			CallCMathOperation<true>(src, dst, count, &std::atanf, &std::atan);
		}

		virtual void Cosh(const void* src, void* dst, size_t count) const {
			CallCMathOperation<true>(src, dst, count, &std::coshf, &std::cosh);
		}

		virtual void Sinh(const void* src, void* dst, size_t count) const {
			CallCMathOperation<true>(src, dst, count, &std::sinhf, &std::sinh);
		}

		virtual void Tanh(const void* src, void* dst, size_t count) const {
			CallCMathOperation<true>(src, dst, count, &std::tanhf, &std::tanh);
		}

		virtual void Acosh(const void* src, void* dst, size_t count) const {
			CallCMathOperation<true>(src, dst, count, &std::acoshf, &std::acosh);
		}

		virtual void Asinh(const void* src, void* dst, size_t count) const {
			CallCMathOperation<true>(src, dst, count, &std::asinhf, &std::asinh);
		}

		virtual void Atanh(const void* src, void* dst, size_t count) const {
			CallCMathOperation<true>(src, dst, count, &std::atanhf, &std::atanh);
		}

		virtual void Abs(const void* src, void* dst, size_t count) const {
			const T* src2 = static_cast<const T*>(src);
			T* dst2 = static_cast<T*>(dst);

			if ANVIL_CONSTEXPR_VAR (std::is_integral<T>::value) {
				if ANVIL_CONSTEXPR_VAR(std::is_signed<T>::value) {
					for (size_t i = 0u; i < count; ++i) {
						dst2[i] = static_cast<T>(std::abs(src2[i]));
					}
				} else {
					memcpy(dst, src, sizeof(T) * count);
				}
			} else if ANVIL_CONSTEXPR_VAR(std::is_same<T, double>::value) {
				for (size_t i = 0u; i < count; ++i) {
					dst2[i] = fabs(src2[i]);
				}
			} else {
				for (size_t i = 0u; i < count; ++i) {
					dst2[i] = static_cast<T>(fabsf(static_cast<float>(src2[i])));
				}
			}
		}


		// 2 inputs

		virtual void Mask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			ArithOpBitwise<sizeof(T)>::Mask(lhs, rhs, dst, count, mask);
		}

		virtual void Add(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);
			for (size_t i = 0u; i < count; ++i) dst2[i] = lhs2[i] + rhs2[i];
		}

		virtual void Subtract(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);
			for (size_t i = 0u; i < count; ++i) dst2[i] = lhs2[i] - rhs2[i];
		}

		virtual void Multiply(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);
			for (size_t i = 0u; i < count; ++i) dst2[i] = lhs2[i] * rhs2[i];
		}

		virtual void Divide(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);
			for (size_t i = 0u; i < count; ++i) dst2[i] = lhs2[i] / rhs2[i];
		}

		virtual void And(const void* lhs, const void* rhs, void* dst, size_t count) const {
			ArithOpBitwise<sizeof(T)>::And(lhs, rhs, dst, count);
		}

		virtual void Or(const void* lhs, const void* rhs, void* dst, size_t count) const {
			ArithOpBitwise<sizeof(T)>::Or(lhs, rhs, dst, count);
		}

		virtual void Xor(const void* lhs, const void* rhs, void* dst, size_t count) const {
			ArithOpBitwise<sizeof(T)>::Xor(lhs, rhs, dst, count);
		}

		virtual void Nand(const void* lhs, const void* rhs, void* dst, size_t count) const {
			ArithOpBitwise<sizeof(T)>::Nand(lhs, rhs, dst, count);
		}

		virtual void Nor(const void* lhs, const void* rhs, void* dst, size_t count) const {
			ArithOpBitwise<sizeof(T)>::Nor(lhs, rhs, dst, count);
		}

		virtual void Xnor(const void* lhs, const void* rhs, void* dst, size_t count) const {
			ArithOpBitwise<sizeof(T)>::Xnor(lhs, rhs, dst, count);
		}

		// 3 inputs

		virtual void MultiplyAdd(const void* a, const void* b, const void* c, void* dst, size_t count) const {
			const T* a2 = static_cast<const T*>(a);
			const T* b2 = static_cast<const T*>(b);
			const T* c2 = static_cast<const T*>(c);
			T* dst2 = static_cast<T*>(dst);
			for (size_t i = 0u; i < count; ++i) dst2[i] = (a2[i] * b2[i]) + c2[i];
		}

		virtual void MultiplySubtract(const void* a, const void* b, const void* c, void* dst, size_t count) const {
			const T* a2 = static_cast<const T*>(a);
			const T* b2 = static_cast<const T*>(b);
			const T* c2 = static_cast<const T*>(c);
			T* dst2 = static_cast<T*>(dst);
			for (size_t i = 0u; i < count; ++i) dst2[i] = (a2[i] * b2[i]) - c2[i];
		}

	};

}}}

#endif