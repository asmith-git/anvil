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
	};

	template<class T>
	class ArithmeticOperationsCpp final : public ArithmeticOperations {
	public:

		ArithmeticOperationsCpp() :
			ArithmeticOperations(EnumFromType<T>::value)
		{}

		virtual ~ArithmeticOperationsCpp() {

		}

		// 1 input

		void Sqrt(const void* src, void* dst, size_t count) final {
			const T* src2 = static_cast<const T*>(src);
			T* dst2 = static_cast<T*>(dst);
			for (size_t i = 0u; i < count; ++i) { dst2[i] = std::sqrt(src2[i]); }
		}

		void Cbrt(const void* src, void* dst, size_t count) final {
			const T* src2 = static_cast<const T*>(src);
			T* dst2 = static_cast<T*>(dst);
			for (size_t i = 0u; i < count; ++i) { dst2[i] = std::cbrt(src2[i]); }
		}


		void Not(const void* src, void* dst, size_t count) final {
			ArithOpBitwise<sizeof(T)>::Not(src, dst, count);
		}

		// 2 inputs

		void Mask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) final {
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

		void Add(const void* lhs, const void* rhs, void* dst, size_t count) final {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);
			for (size_t i = 0u; i < count; ++i) dst2[i] = lhs2[i] + rhs2[i];
		}

		void Subtract(const void* lhs, const void* rhs, void* dst, size_t count) final {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);
			for (size_t i = 0u; i < count; ++i) dst2[i] = lhs2[i] - rhs2[i];
		}

		void Multiply(const void* lhs, const void* rhs, void* dst, size_t count) final {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);
			for (size_t i = 0u; i < count; ++i) dst2[i] = lhs2[i] * rhs2[i];
		}

		void Divide(const void* lhs, const void* rhs, void* dst, size_t count) final {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);
			for (size_t i = 0u; i < count; ++i) dst2[i] = lhs2[i] / rhs2[i];
		}

		void And(const void* lhs, const void* rhs, void* dst, size_t count) final {
			ArithOpBitwise<sizeof(T)>::And(lhs, rhs, dst, count);
		}

		void Or(const void* lhs, const void* rhs, void* dst, size_t count) final {
			ArithOpBitwise<sizeof(T)>::Or(lhs, rhs, dst, count);
		}

		void Xor(const void* lhs, const void* rhs, void* dst, size_t count) final {
			ArithOpBitwise<sizeof(T)>::Xor(lhs, rhs, dst, count);
		}

		void Nand(const void* lhs, const void* rhs, void* dst, size_t count) final {
			ArithOpBitwise<sizeof(T)>::Nand(lhs, rhs, dst, count);
		}

		void Nor(const void* lhs, const void* rhs, void* dst, size_t count) final {
			ArithOpBitwise<sizeof(T)>::Nor(lhs, rhs, dst, count);
		}

		void Xnor(const void* lhs, const void* rhs, void* dst, size_t count) final {
			ArithOpBitwise<sizeof(T)>::Xnor(lhs, rhs, dst, count);
		}

		// 3 inputs

		void MultiplyAdd(const void* a, const void* b, const void* c, void* dst, size_t count) final {
			const T* a2 = static_cast<const T*>(a);
			const T* b2 = static_cast<const T*>(b);
			const T* c2 = static_cast<const T*>(c);
			T* dst2 = static_cast<T*>(dst);
			for (size_t i = 0u; i < count; ++i) dst2[i] = (a2[i] * b2[i]) + c2[i];
		}

		void MultiplySubtract(const void* a, const void* b, const void* c, void* dst, size_t count) final {
			const T* a2 = static_cast<const T*>(a);
			const T* b2 = static_cast<const T*>(b);
			const T* c2 = static_cast<const T*>(c);
			T* dst2 = static_cast<T*>(dst);
			for (size_t i = 0u; i < count; ++i) dst2[i] = (a2[i] * b2[i]) - c2[i];
		}

	};

}}}

#endif