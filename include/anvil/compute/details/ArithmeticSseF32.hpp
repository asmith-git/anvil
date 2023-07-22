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

#ifndef ANVIL_COMPUTE_ARITHMETIC_SSE_F32_HPP
#define ANVIL_COMPUTE_ARITHMETIC_SSE_F32_HPP

#include "anvil/compute/details/ArithmeticCpp.hpp"

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
#include <immintrin.h>
#endif

namespace anvil { namespace compute { namespace details {

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64

	class ArithmeticOperationsSseF32 : public ArithmeticOperationsCpp<float> {
	protected:

		static ANVIL_STRONG_INLINE void ExpandMaskSSE(uint8_t mask, __m128& lo, __m128& hi) {
			const __m128i bitslo = _mm_set_epi32(8, 4, 2, 1);
			const __m128i bitshi = _mm_set_epi32(128, 64, 32, 16);
			const __m128i m = _mm_set1_epi32(mask);
			lo = _mm_castsi128_ps(_mm_cmpeq_epi32(_mm_and_si128(m, bitslo), bitslo));
			hi = _mm_castsi128_ps(_mm_cmpeq_epi32(_mm_and_si128(m, bitshi), bitshi));
		}

		static ANVIL_STRONG_INLINE void MaskSSE(__m128 lhslo, __m128 lhshi, __m128 rhslo, __m128 rhshi, uint8_t mask, __m128& outlo, __m128& outhi) {
			__m128 masklo, maskhi;
			ExpandMaskSSE(mask, masklo, maskhi);

			lhslo = _mm_and_ps(lhslo, masklo);
			lhshi = _mm_and_ps(lhshi, maskhi);
			rhslo = _mm_andnot_ps(masklo, rhslo);
			rhshi = _mm_andnot_ps(maskhi, rhshi);
			outlo = _mm_or_ps(lhslo, rhslo);
			outhi = _mm_or_ps(rhslo, rhshi);
		}

		static ANVIL_STRONG_INLINE __m128 HypotSSE(__m128 a, __m128 b) {
			a = _mm_mul_ps(a, a);
			b = _mm_mul_ps(b, b);
			a = _mm_add_ps(a, b);
			return _mm_sqrt_ps(a);
		}
	public:
		typedef float T;

		ArithmeticOperationsSseF32() :
			ArithmeticOperationsCpp()
		{}

		virtual ~ArithmeticOperationsSseF32() {

		}

		// 1 input

		virtual void Sqrt(const void* src, void* dst, size_t count) const {
			const T* src2 = static_cast<const T*>(src);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 4u) * 4u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 4u) {
				__m128 xmm0 = _mm_loadu_ps(src2 + i);
				xmm0 = _mm_sqrt_ps(xmm0);
				_mm_storeu_ps(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128 xmm0 = _mm_load_ss(src2 + i);
				xmm0 = _mm_sqrt_ss(xmm0);
				_mm_store_ss(dst2 + i, xmm0);
			}
		}

		virtual void Sqrt(const void* src, void* dst, size_t count, const uint8_t* mask) const {
			const T* src2 = static_cast<const T*>(src);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(src2 + i);
				__m128 xmm1 = _mm_loadu_ps(src2 + i + 4);

				__m128 xmm2 = _mm_sqrt_ps(xmm0);
				__m128 xmm3 = _mm_sqrt_ps(xmm1);

				MaskSSE(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				src2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float src_buffer[8u];
				float dst_buffer[8u];
				memcpy(src_buffer, src2, sizeof(T) * count);
				Sqrt(src_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Not(const void* src, void* dst, size_t count) const {
			const T* src2 = static_cast<const T*>(src);
			T* dst2 = static_cast<T*>(dst);
			__m128 ones = _mm_setzero_ps();
			ones = _mm_cmpeq_ps(ones, ones);
			
			size_t aligned_size = (count / 4u) * 4u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 4u) {
				__m128 xmm0 = _mm_loadu_ps(src2 + i);
				xmm0 = _mm_xor_ps(xmm0, ones);
				_mm_storeu_ps(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128 xmm0 = _mm_load_ss(src2 + i);
				xmm0 = _mm_xor_ps(xmm0, ones);
				_mm_store_ss(dst2 + i, xmm0);
			}
		}

		virtual void Not(const void* src, void* dst, size_t count, const uint8_t* mask) const {
			const T* src2 = static_cast<const T*>(src);
			T* dst2 = static_cast<T*>(dst);

			__m128 ones = _mm_setzero_ps();
			ones = _mm_cmpeq_ps(ones, ones);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(src2 + i);
				__m128 xmm1 = _mm_loadu_ps(src2 + i + 4);

				__m128 xmm2 = _mm_xor_ps(xmm0, ones);
				__m128 xmm3 = _mm_xor_ps(xmm1, ones);

				MaskSSE(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				src2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float src_buffer[8u];
				float dst_buffer[8u];
				memcpy(src_buffer, src2, sizeof(T) * count);
				Not(src_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		// 2 inputs

		virtual void Mask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst); 

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(lhs2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(rhs2 + i);
				__m128 xmm3 = _mm_loadu_ps(rhs2 + i + 4);

				MaskSSE(xmm0, xmm1, xmm2, xmm3, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Mask(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Add(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 4u) * 4u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 4u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(rhs2 + i);
				xmm0 = _mm_add_ps(xmm0, xmm1);
				_mm_storeu_ps(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128 xmm0 = _mm_load_ss(lhs2 + i);
				__m128 xmm1 = _mm_load_ss(rhs2 + i);
				xmm0 = _mm_add_ss(xmm0, xmm1);
				_mm_store_ss(dst2 + i, xmm0);
			}
		}

		virtual void Add(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(lhs2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(rhs2 + i);
				__m128 xmm3 = _mm_loadu_ps(rhs2 + i + 4);

				xmm2 = _mm_add_ps(xmm0, xmm2);
				xmm3 = _mm_add_ps(xmm1, xmm3);

				MaskSSE(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Add(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Subtract(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 4u) * 4u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 4u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(rhs2 + i);
				xmm0 = _mm_sub_ps(xmm0, xmm1);
				_mm_storeu_ps(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128 xmm0 = _mm_load_ss(lhs2 + i);
				__m128 xmm1 = _mm_load_ss(rhs2 + i);
				xmm0 = _mm_sub_ss(xmm0, xmm1);
				_mm_store_ss(dst2 + i, xmm0);
			}
		}

		virtual void Subtract(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(lhs2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(rhs2 + i);
				__m128 xmm3 = _mm_loadu_ps(rhs2 + i + 4);

				xmm2 = _mm_sub_ps(xmm0, xmm2);
				xmm3 = _mm_sub_ps(xmm1, xmm3);

				MaskSSE(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Subtract(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Multiply(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 4u) * 4u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 4u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(rhs2 + i);
				xmm0 = _mm_mul_ps(xmm0, xmm1);
				_mm_storeu_ps(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128 xmm0 = _mm_load_ss(lhs2 + i);
				__m128 xmm1 = _mm_load_ss(rhs2 + i);
				xmm0 = _mm_mul_ss(xmm0, xmm1);
				_mm_store_ss(dst2 + i, xmm0);
			}
		}

		virtual void Multiply(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(lhs2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(rhs2 + i);
				__m128 xmm3 = _mm_loadu_ps(rhs2 + i + 4);

				xmm2 = _mm_mul_ps(xmm0, xmm2);
				xmm3 = _mm_mul_ps(xmm1, xmm3); 
				
				MaskSSE(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Multiply(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Divide(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 4u) * 4u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 4u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(rhs2 + i);
				xmm0 = _mm_div_ps(xmm0, xmm1);
				_mm_storeu_ps(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128 xmm0 = _mm_load_ss(lhs2 + i);
				__m128 xmm1 = _mm_load_ss(rhs2 + i);
				xmm0 = _mm_div_ss(xmm0, xmm1);
				_mm_store_ss(dst2 + i, xmm0);
			}
		}

		virtual void Divide(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(lhs2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(rhs2 + i);
				__m128 xmm3 = _mm_loadu_ps(rhs2 + i + 4);

				xmm2 = _mm_div_ps(xmm0, xmm2);
				xmm3 = _mm_div_ps(xmm1, xmm3);

				MaskSSE(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Divide(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void And(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 4u) * 4u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 4u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(rhs2 + i);
				xmm0 = _mm_and_ps(xmm0, xmm1);
				_mm_storeu_ps(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128 xmm0 = _mm_load_ss(lhs2 + i);
				__m128 xmm1 = _mm_load_ss(rhs2 + i);
				xmm0 = _mm_and_ps(xmm0, xmm1);
				_mm_store_ss(dst2 + i, xmm0);
			}
		}

		virtual void And(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(lhs2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(rhs2 + i);
				__m128 xmm3 = _mm_loadu_ps(rhs2 + i + 4);

				xmm2 = _mm_and_ps(xmm0, xmm2);
				xmm3 = _mm_and_ps(xmm1, xmm3);

				MaskSSE(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				And(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Or(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 4u) * 4u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 4u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(rhs2 + i);
				xmm0 = _mm_or_ps(xmm0, xmm1);
				_mm_storeu_ps(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128 xmm0 = _mm_load_ss(lhs2 + i);
				__m128 xmm1 = _mm_load_ss(rhs2 + i);
				xmm0 = _mm_or_ps(xmm0, xmm1);
				_mm_store_ss(dst2 + i, xmm0);
			}
		}

		virtual void Or(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(lhs2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(rhs2 + i);
				__m128 xmm3 = _mm_loadu_ps(rhs2 + i + 4);

				xmm2 = _mm_or_ps(xmm0, xmm2);
				xmm3 = _mm_or_ps(xmm1, xmm3);

				MaskSSE(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Or(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Xor(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 4u) * 4u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 4u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(rhs2 + i);
				xmm0 = _mm_xor_ps(xmm0, xmm1);
				_mm_storeu_ps(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128 xmm0 = _mm_load_ss(lhs2 + i);
				__m128 xmm1 = _mm_load_ss(rhs2 + i);
				xmm0 = _mm_xor_ps(xmm0, xmm1);
				_mm_store_ss(dst2 + i, xmm0);
			}
		}

		virtual void Xor(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(lhs2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(rhs2 + i);
				__m128 xmm3 = _mm_loadu_ps(rhs2 + i + 4);

				xmm2 = _mm_xor_ps(xmm0, xmm2);
				xmm3 = _mm_xor_ps(xmm1, xmm3);

				MaskSSE(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Xor(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Nand(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			__m128 ones = _mm_setzero_ps();
			ones = _mm_cmpeq_ps(ones, ones);

			size_t aligned_size = (count / 4u) * 4u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 4u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(rhs2 + i);
				xmm0 = _mm_and_ps(xmm0, xmm1);
				xmm0 = _mm_xor_ps(xmm0, ones);
				_mm_storeu_ps(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128 xmm0 = _mm_load_ss(lhs2 + i);
				__m128 xmm1 = _mm_load_ss(rhs2 + i);
				xmm0 = _mm_and_ps(xmm0, xmm1);
				xmm0 = _mm_xor_ps(xmm0, ones);
				_mm_store_ss(dst2 + i, xmm0);
			}
		}

		virtual void Nand(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			__m128 ones = _mm_setzero_ps();
			ones = _mm_cmpeq_ps(ones, ones);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(lhs2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(rhs2 + i);
				__m128 xmm3 = _mm_loadu_ps(rhs2 + i + 4);

				xmm2 = _mm_and_ps(xmm0, xmm2);
				xmm3 = _mm_and_ps(xmm1, xmm3);
				xmm2 = _mm_xor_ps(xmm2, ones);
				xmm3 = _mm_xor_ps(xmm3, ones);

				MaskSSE(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Nand(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Nor(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			__m128 ones = _mm_setzero_ps();
			ones = _mm_cmpeq_ps(ones, ones);

			size_t aligned_size = (count / 4u) * 4u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 4u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(rhs2 + i);
				xmm0 = _mm_or_ps(xmm0, xmm1);
				xmm0 = _mm_xor_ps(xmm0, ones);
				_mm_storeu_ps(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128 xmm0 = _mm_load_ss(lhs2 + i);
				__m128 xmm1 = _mm_load_ss(rhs2 + i);
				xmm0 = _mm_or_ps(xmm0, xmm1);
				xmm0 = _mm_xor_ps(xmm0, ones);
				_mm_store_ss(dst2 + i, xmm0);
			}
		}

		virtual void Nor(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			__m128 ones = _mm_setzero_ps();
			ones = _mm_cmpeq_ps(ones, ones);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(lhs2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(rhs2 + i);
				__m128 xmm3 = _mm_loadu_ps(rhs2 + i + 4);

				xmm2 = _mm_or_ps(xmm0, xmm2);
				xmm3 = _mm_or_ps(xmm1, xmm3);
				xmm2 = _mm_xor_ps(xmm2, ones);
				xmm3 = _mm_xor_ps(xmm3, ones);

				MaskSSE(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Nor(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Xnor(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			__m128 ones = _mm_setzero_ps();
			ones = _mm_cmpeq_ps(ones, ones);

			size_t aligned_size = (count / 4u) * 4u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 4u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(rhs2 + i);
				xmm0 = _mm_xor_ps(xmm0, xmm1);
				xmm0 = _mm_xor_ps(xmm0, ones);
				_mm_storeu_ps(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128 xmm0 = _mm_load_ss(lhs2 + i);
				__m128 xmm1 = _mm_load_ss(rhs2 + i);
				xmm0 = _mm_xor_ps(xmm0, xmm1);
				xmm0 = _mm_xor_ps(xmm0, ones);
				_mm_store_ss(dst2 + i, xmm0);
			}
		}

		virtual void Xnor(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			__m128 ones = _mm_setzero_ps();
			ones = _mm_cmpeq_ps(ones, ones);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(lhs2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(rhs2 + i);
				__m128 xmm3 = _mm_loadu_ps(rhs2 + i + 4);

				xmm2 = _mm_xor_ps(xmm0, xmm2);
				xmm3 = _mm_xor_ps(xmm1, xmm3);
				xmm2 = _mm_xor_ps(xmm2, ones);
				xmm3 = _mm_xor_ps(xmm3, ones);

				MaskSSE(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Xnor(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Hypotenuse(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 4u) * 4u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 4u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(rhs2 + i);
				xmm0 = HypotSSE(xmm0, xmm1);
				_mm_storeu_ps(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128 xmm0 = _mm_load_ss(lhs2 + i);
				__m128 xmm1 = _mm_load_ss(rhs2 + i);
				xmm0 = HypotSSE(xmm0, xmm1);
				_mm_store_ss(dst2 + i, xmm0);
			}
		}

		virtual void Hypotenuse(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(lhs2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(rhs2 + i);
				__m128 xmm3 = _mm_loadu_ps(rhs2 + i + 4);

				xmm2 = HypotSSE(xmm0, xmm2);
				xmm3 = HypotSSE(xmm1, xmm3);

				MaskSSE(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Hypotenuse(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Minimum(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 4u) * 4u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 4u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(rhs2 + i);
				xmm0 = _mm_min_ps(xmm0, xmm1);
				_mm_storeu_ps(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128 xmm0 = _mm_load_ss(lhs2 + i);
				__m128 xmm1 = _mm_load_ss(rhs2 + i);
				xmm0 = _mm_min_ss(xmm0, xmm1);
				_mm_store_ss(dst2 + i, xmm0);
			}
		}

		virtual void Minimum(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(lhs2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(rhs2 + i);
				__m128 xmm3 = _mm_loadu_ps(rhs2 + i + 4);

				xmm2 = _mm_min_ps(xmm0, xmm2);
				xmm3 = _mm_min_ps(xmm1, xmm3);

				MaskSSE(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Minimum(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Maximum(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 4u) * 4u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 4u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(rhs2 + i);
				xmm0 = _mm_max_ps(xmm0, xmm1);
				_mm_storeu_ps(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128 xmm0 = _mm_load_ss(lhs2 + i);
				__m128 xmm1 = _mm_load_ss(rhs2 + i);
				xmm0 = _mm_max_ss(xmm0, xmm1);
				_mm_store_ss(dst2 + i, xmm0);
			}
		}

		virtual void Maximum(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(lhs2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(rhs2 + i);
				__m128 xmm3 = _mm_loadu_ps(rhs2 + i + 4);

				xmm2 = _mm_max_ps(xmm0, xmm2);
				xmm3 = _mm_max_ps(xmm1, xmm3);

				MaskSSE(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Maximum(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		// 3 inputs

		virtual void MultiplyAdd(const void* a, const void* b, const void* c, void* dst, size_t count) const {
			const T* a2 = static_cast<const T*>(a);
			const T* b2 = static_cast<const T*>(b);
			const T* c2 = static_cast<const T*>(c);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 4u) * 4u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 4u) {
				__m128 xmm0 = _mm_loadu_ps(a2 + i);
				__m128 xmm1 = _mm_loadu_ps(b2 + i);
				__m128 xmm2 = _mm_loadu_ps(c2 + i);
				xmm0 = _mm_mul_ps(xmm0, xmm1);
				xmm0 = _mm_add_ps(xmm0, xmm2);
				_mm_storeu_ps(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128 xmm0 = _mm_load_ss(a2 + i);
				__m128 xmm1 = _mm_load_ss(b2 + i);
				__m128 xmm2 = _mm_load_ss(c2 + i);
				xmm0 = _mm_mul_ss(xmm0, xmm1);
				xmm0 = _mm_add_ss(xmm0, xmm2);
				_mm_store_ss(dst2 + i, xmm0);
			}
		}

		virtual void MultiplyAdd(const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask) const {
			const T* a2 = static_cast<const T*>(a);
			const T* b2 = static_cast<const T*>(b);
			const T* c2 = static_cast<const T*>(c);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(a2 + i);
				__m128 xmm1 = _mm_loadu_ps(a2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(b2 + i);
				__m128 xmm3 = _mm_loadu_ps(b2 + i + 4);

				xmm2 = _mm_mul_ps(xmm0, xmm2);
				xmm3 = _mm_mul_ps(xmm1, xmm3);
				xmm2 = _mm_add_ps(xmm0, _mm_loadu_ps(c2 + i));
				xmm3 = _mm_add_ps(xmm1, _mm_loadu_ps(c2 + i + 4));

				MaskSSE(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				a2 += aligned_size;
				b2 += aligned_size;
				c2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float a_buffer[8u];
				float b_buffer[8u];
				float c_buffer[8u];
				float dst_buffer[8u];
				memcpy(a_buffer, a2, sizeof(T) * count);
				memcpy(b_buffer, b2, sizeof(T) * count);
				memcpy(c_buffer, c2, sizeof(T) * count);
				MultiplyAdd(a_buffer, b_buffer, c_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void MultiplySubtract(const void* a, const void* b, const void* c, void* dst, size_t count) const {
			const T* a2 = static_cast<const T*>(a);
			const T* b2 = static_cast<const T*>(b);
			const T* c2 = static_cast<const T*>(c);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 4u) * 4u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 4u) {
				__m128 xmm0 = _mm_loadu_ps(a2 + i);
				__m128 xmm1 = _mm_loadu_ps(b2 + i);
				__m128 xmm2 = _mm_loadu_ps(c2 + i);
				xmm0 = _mm_mul_ps(xmm0, xmm1);
				xmm0 = _mm_sub_ps(xmm0, xmm2);
				_mm_storeu_ps(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128 xmm0 = _mm_load_ss(a2 + i);
				__m128 xmm1 = _mm_load_ss(b2 + i);
				__m128 xmm2 = _mm_load_ss(c2 + i);
				xmm0 = _mm_mul_ss(xmm0, xmm1);
				xmm0 = _mm_sub_ss(xmm0, xmm2);
				_mm_store_ss(dst2 + i, xmm0);
			}
		}

		virtual void MultiplySubtract(const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask) const {
			const T* a2 = static_cast<const T*>(a);
			const T* b2 = static_cast<const T*>(b);
			const T* c2 = static_cast<const T*>(c);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(a2 + i);
				__m128 xmm1 = _mm_loadu_ps(a2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(b2 + i);
				__m128 xmm3 = _mm_loadu_ps(b2 + i + 4);

				xmm2 = _mm_mul_ps(xmm0, xmm2);
				xmm3 = _mm_mul_ps(xmm1, xmm3);
				xmm2 = _mm_sub_ps(xmm0, _mm_loadu_ps(c2 + i));
				xmm3 = _mm_sub_ps(xmm1, _mm_loadu_ps(c2 + i + 4));

				MaskSSE(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				a2 += aligned_size;
				b2 += aligned_size;
				c2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float a_buffer[8u];
				float b_buffer[8u];
				float c_buffer[8u];
				float dst_buffer[8u];
				memcpy(a_buffer, a2, sizeof(T) * count);
				memcpy(b_buffer, b2, sizeof(T) * count);
				memcpy(c_buffer, c2, sizeof(T) * count);
				MultiplySubtract(a_buffer, b_buffer, c_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}
	};

	class ArithmeticOperationsSse4F32 : public ArithmeticOperationsSseF32 {
	protected:

		static ANVIL_STRONG_INLINE void MaskSSE4(__m128 lhslo, __m128 lhshi, __m128 rhslo, __m128 rhshi, uint8_t mask, __m128& outlo, __m128& outhi) {
			__m128 masklo, maskhi;
			ExpandMaskSSE(mask, masklo, maskhi);

			outlo = _mm_blendv_ps(rhslo, lhslo, masklo);
			outhi = _mm_blendv_ps(rhshi, lhshi, maskhi);
		}

		template<int ROUNDING_MODE>
		static void RoundSSE4(const void* src, void* dst, size_t count) {
			const T* src2 = static_cast<const T*>(src);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 4u) * 4u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 4u) {
				__m128 xmm0 = _mm_loadu_ps(src2 + i);
				xmm0 = _mm_round_ps(xmm0, ROUNDING_MODE);
				_mm_storeu_ps(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128 xmm0 = _mm_load_ss(src2 + i);
				xmm0 = _mm_round_ps(xmm0, ROUNDING_MODE);
				_mm_store_ss(dst2 + i, xmm0);
			}
		}

		template<int ROUNDING_MODE>
		static void RoundSSE4(const void* src, void* dst, size_t count, const uint8_t* mask) {
			const T* src2 = static_cast<const T*>(src);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(src2 + i);
				__m128 xmm1 = _mm_loadu_ps(src2 + i + 4);

				__m128 xmm2 = _mm_round_ps(xmm0, ROUNDING_MODE);
				__m128 xmm3 = _mm_round_ps(xmm1, ROUNDING_MODE);

				MaskSSE4(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				src2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float src_buffer[8u];
				float dst_buffer[8u];
				memcpy(src_buffer, src2, sizeof(T) * count);
				RoundSSE4<ROUNDING_MODE>(src_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}
	public:
		ArithmeticOperationsSse4F32() :
			ArithmeticOperationsSseF32()
		{}

		virtual ~ArithmeticOperationsSse4F32() {

		}

		// 1 input

		virtual void Sqrt(const void* src, void* dst, size_t count, const uint8_t* mask) const {
			const T* src2 = static_cast<const T*>(src);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(src2 + i);
				__m128 xmm1 = _mm_loadu_ps(src2 + i + 4);

				__m128 xmm2 = _mm_sqrt_ps(xmm0);
				__m128 xmm3 = _mm_sqrt_ps(xmm1);

				MaskSSE4(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				src2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float src_buffer[8u];
				float dst_buffer[8u];
				memcpy(src_buffer, src2, sizeof(T) * count);
				Sqrt(src_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Not(const void* src, void* dst, size_t count, const uint8_t* mask) const {
			const T* src2 = static_cast<const T*>(src);
			T* dst2 = static_cast<T*>(dst);

			__m128 ones = _mm_setzero_ps();
			ones = _mm_cmpeq_ps(ones, ones);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(src2 + i);
				__m128 xmm1 = _mm_loadu_ps(src2 + i + 4);

				__m128 xmm2 = _mm_xor_ps(xmm0, ones);
				__m128 xmm3 = _mm_xor_ps(xmm1, ones);

				MaskSSE4(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				src2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float src_buffer[8u];
				float dst_buffer[8u];
				memcpy(src_buffer, src2, sizeof(T) * count);
				Not(src_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Round(const void* src, void* dst, size_t count) const {
			RoundSSE4<_MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC>(src, dst, count);
		}

		virtual void Round(const void* src, void* dst, size_t count, const uint8_t* mask) const {
			RoundSSE4<_MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC>(src, dst, count, mask);
		}

		virtual void Floor(const void* src, void* dst, size_t count) const {
			RoundSSE4<_MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC>(src, dst, count);
		}

		virtual void Floor(const void* src, void* dst, size_t count, const uint8_t* mask) const {
			RoundSSE4<_MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC>(src, dst, count, mask);
		}

		virtual void Ceil(const void* src, void* dst, size_t count) const {
			RoundSSE4<_MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC>(src, dst, count);
		}

		virtual void Ceil(const void* src, void* dst, size_t count, const uint8_t* mask) const {
			RoundSSE4<_MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC>(src, dst, count, mask);
		}

		// 2 inputs

		virtual void Mask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {

			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(lhs2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(rhs2 + i);
				__m128 xmm3 = _mm_loadu_ps(rhs2 + i + 4);

				MaskSSE4(xmm0, xmm1, xmm2, xmm3, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Mask(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Add(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(lhs2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(rhs2 + i);
				__m128 xmm3 = _mm_loadu_ps(rhs2 + i + 4);

				xmm2 = _mm_add_ps(xmm0, xmm2);
				xmm3 = _mm_add_ps(xmm1, xmm3);

				MaskSSE4(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Add(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Subtract(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(lhs2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(rhs2 + i);
				__m128 xmm3 = _mm_loadu_ps(rhs2 + i + 4);

				xmm2 = _mm_sub_ps(xmm0, xmm2);
				xmm3 = _mm_sub_ps(xmm1, xmm3);

				MaskSSE4(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Subtract(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Multiply(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(lhs2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(rhs2 + i);
				__m128 xmm3 = _mm_loadu_ps(rhs2 + i + 4);

				xmm2 = _mm_mul_ps(xmm0, xmm2);
				xmm3 = _mm_mul_ps(xmm1, xmm3);

				MaskSSE4(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Multiply(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Divide(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(lhs2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(rhs2 + i);
				__m128 xmm3 = _mm_loadu_ps(rhs2 + i + 4);

				xmm2 = _mm_div_ps(xmm0, xmm2);
				xmm3 = _mm_div_ps(xmm1, xmm3);

				MaskSSE4(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Divide(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void And(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(lhs2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(rhs2 + i);
				__m128 xmm3 = _mm_loadu_ps(rhs2 + i + 4);

				xmm2 = _mm_and_ps(xmm0, xmm2);
				xmm3 = _mm_and_ps(xmm1, xmm3);

				MaskSSE4(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				And(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Or(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(lhs2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(rhs2 + i);
				__m128 xmm3 = _mm_loadu_ps(rhs2 + i + 4);

				xmm2 = _mm_or_ps(xmm0, xmm2);
				xmm3 = _mm_or_ps(xmm1, xmm3);

				MaskSSE4(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Or(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Xor(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(lhs2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(rhs2 + i);
				__m128 xmm3 = _mm_loadu_ps(rhs2 + i + 4);

				xmm2 = _mm_xor_ps(xmm0, xmm2);
				xmm3 = _mm_xor_ps(xmm1, xmm3);

				MaskSSE4(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Xor(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Nand(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			__m128 ones = _mm_setzero_ps();
			ones = _mm_cmpeq_ps(ones, ones);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(lhs2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(rhs2 + i);
				__m128 xmm3 = _mm_loadu_ps(rhs2 + i + 4);

				xmm2 = _mm_and_ps(xmm0, xmm2);
				xmm3 = _mm_and_ps(xmm1, xmm3);
				xmm2 = _mm_xor_ps(xmm2, ones);
				xmm3 = _mm_xor_ps(xmm3, ones);

				MaskSSE4(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Nand(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Nor(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			__m128 ones = _mm_setzero_ps();
			ones = _mm_cmpeq_ps(ones, ones);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(lhs2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(rhs2 + i);
				__m128 xmm3 = _mm_loadu_ps(rhs2 + i + 4);

				xmm2 = _mm_or_ps(xmm0, xmm2);
				xmm3 = _mm_or_ps(xmm1, xmm3);
				xmm2 = _mm_xor_ps(xmm2, ones);
				xmm3 = _mm_xor_ps(xmm3, ones);

				MaskSSE4(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Nor(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Xnor(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			__m128 ones = _mm_setzero_ps();
			ones = _mm_cmpeq_ps(ones, ones);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(lhs2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(rhs2 + i);
				__m128 xmm3 = _mm_loadu_ps(rhs2 + i + 4);

				xmm2 = _mm_xor_ps(xmm0, xmm2);
				xmm3 = _mm_xor_ps(xmm1, xmm3);
				xmm2 = _mm_xor_ps(xmm2, ones);
				xmm3 = _mm_xor_ps(xmm3, ones);

				MaskSSE4(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Xnor(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Hypotenuse(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(lhs2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(rhs2 + i);
				__m128 xmm3 = _mm_loadu_ps(rhs2 + i + 4);

				xmm2 = HypotSSE(xmm0, xmm2);
				xmm3 = HypotSSE(xmm1, xmm3);

				MaskSSE4(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Hypotenuse(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}
		
		virtual void Minimum(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(lhs2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(rhs2 + i);
				__m128 xmm3 = _mm_loadu_ps(rhs2 + i + 4);

				xmm2 = _mm_min_ps(xmm0, xmm2);
				xmm3 = _mm_min_ps(xmm1, xmm3);

				MaskSSE4(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Minimum(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Maximum(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(lhs2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(rhs2 + i);
				__m128 xmm3 = _mm_loadu_ps(rhs2 + i + 4);

				xmm2 = _mm_max_ps(xmm0, xmm2);
				xmm3 = _mm_max_ps(xmm1, xmm3);

				MaskSSE4(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Maximum(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}


		// 3 inputs

		virtual void MultiplyAdd(const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask) const {
			const T* a2 = static_cast<const T*>(a);
			const T* b2 = static_cast<const T*>(b);
			const T* c2 = static_cast<const T*>(c);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(a2 + i);
				__m128 xmm1 = _mm_loadu_ps(a2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(b2 + i);
				__m128 xmm3 = _mm_loadu_ps(b2 + i + 4);

				xmm2 = _mm_mul_ps(xmm0, xmm2);
				xmm3 = _mm_mul_ps(xmm1, xmm3);
				xmm2 = _mm_add_ps(xmm0, _mm_loadu_ps(c2 + i));
				xmm3 = _mm_add_ps(xmm1, _mm_loadu_ps(c2 + i + 4));

				MaskSSE4(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				a2 += aligned_size;
				b2 += aligned_size;
				c2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float a_buffer[8u];
				float b_buffer[8u];
				float c_buffer[8u];
				float dst_buffer[8u];
				memcpy(a_buffer, a2, sizeof(T) * count);
				memcpy(b_buffer, b2, sizeof(T) * count);
				memcpy(c_buffer, c2, sizeof(T) * count);
				MultiplyAdd(a_buffer, b_buffer, c_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void MultiplySubtract(const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask) const {
			const T* a2 = static_cast<const T*>(a);
			const T* b2 = static_cast<const T*>(b);
			const T* c2 = static_cast<const T*>(c);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(a2 + i);
				__m128 xmm1 = _mm_loadu_ps(a2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(b2 + i);
				__m128 xmm3 = _mm_loadu_ps(b2 + i + 4);

				xmm2 = _mm_mul_ps(xmm0, xmm2);
				xmm3 = _mm_mul_ps(xmm1, xmm3);
				xmm2 = _mm_sub_ps(xmm0, _mm_loadu_ps(c2 + i));
				xmm3 = _mm_sub_ps(xmm1, _mm_loadu_ps(c2 + i + 4));

				MaskSSE4(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				a2 += aligned_size;
				b2 += aligned_size;
				c2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float a_buffer[8u];
				float b_buffer[8u];
				float c_buffer[8u];
				float dst_buffer[8u];
				memcpy(a_buffer, a2, sizeof(T) * count);
				memcpy(b_buffer, b2, sizeof(T) * count);
				memcpy(c_buffer, c2, sizeof(T) * count);
				MultiplySubtract(a_buffer, b_buffer, c_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}
	};

	class ArithmeticOperationsFmaF32 : public ArithmeticOperationsSse4F32 {
	private:
		static ANVIL_STRONG_INLINE __m128 HypotFMA(__m128 a, __m128 b) {
			a = _mm_mul_ps(a, a);
			b = _mm_fmadd_ps(b, b, a);
			return _mm_sqrt_ps(b);
		}
	public:
		ArithmeticOperationsFmaF32() :
			ArithmeticOperationsSse4F32()
		{}

		virtual ~ArithmeticOperationsFmaF32() {

		}

		// 2 inputs

		virtual void Hypotenuse(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 4u) * 4u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 4u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(rhs2 + i);
				xmm0 = HypotFMA(xmm0, xmm1);
				_mm_storeu_ps(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128 xmm0 = _mm_load_ss(lhs2 + i);
				__m128 xmm1 = _mm_load_ss(rhs2 + i);
				xmm0 = HypotFMA(xmm0, xmm1);
				_mm_store_ss(dst2 + i, xmm0);
			}
		}

		virtual void Hypotenuse(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(lhs2 + i);
				__m128 xmm1 = _mm_loadu_ps(lhs2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(rhs2 + i);
				__m128 xmm3 = _mm_loadu_ps(rhs2 + i + 4);

				xmm2 = HypotFMA(xmm0, xmm2);
				xmm3 = HypotFMA(xmm1, xmm3);

				MaskSSE4(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Hypotenuse(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}


		// 3 inputs

		virtual void MultiplyAdd(const void* a, const void* b, const void* c, void* dst, size_t count) const {
			const T* a2 = static_cast<const T*>(a);
			const T* b2 = static_cast<const T*>(b);
			const T* c2 = static_cast<const T*>(c);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 4u) * 4u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 4u) {
				__m128 xmm0 = _mm_loadu_ps(a2 + i);
				__m128 xmm1 = _mm_loadu_ps(b2 + i);
				__m128 xmm2 = _mm_loadu_ps(c2 + i);
				xmm0 = _mm_fmadd_ps(xmm0, xmm1, xmm2);
				_mm_storeu_ps(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128 xmm0 = _mm_load_ss(a2 + i);
				__m128 xmm1 = _mm_load_ss(b2 + i);
				__m128 xmm2 = _mm_load_ss(c2 + i);
				xmm0 = _mm_fmadd_ss(xmm0, xmm1, xmm2);
				_mm_store_ss(dst2 + i, xmm0);
			}
		}

		virtual void MultiplyAdd(const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask) const {
			const T* a2 = static_cast<const T*>(a);
			const T* b2 = static_cast<const T*>(b);
			const T* c2 = static_cast<const T*>(c);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(a2 + i);
				__m128 xmm1 = _mm_loadu_ps(a2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(b2 + i);
				__m128 xmm3 = _mm_loadu_ps(b2 + i + 4);

				xmm2 = _mm_fmadd_ps(xmm0, xmm2, _mm_loadu_ps(c2 + i));
				xmm3 = _mm_fmadd_ps(xmm1, xmm3, _mm_loadu_ps(c2 + i + 4));

				MaskSSE4(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				a2 += aligned_size;
				b2 += aligned_size;
				c2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float a_buffer[8u];
				float b_buffer[8u];
				float c_buffer[8u];
				float dst_buffer[8u];
				memcpy(a_buffer, a2, sizeof(T) * count);
				memcpy(b_buffer, b2, sizeof(T) * count);
				memcpy(c_buffer, c2, sizeof(T) * count);
				MultiplyAdd(a_buffer, b_buffer, c_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void MultiplySubtract(const void* a, const void* b, const void* c, void* dst, size_t count) const {
			const T* a2 = static_cast<const T*>(a);
			const T* b2 = static_cast<const T*>(b);
			const T* c2 = static_cast<const T*>(c);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 4u) * 4u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 4u) {
				__m128 xmm0 = _mm_loadu_ps(a2 + i);
				__m128 xmm1 = _mm_loadu_ps(b2 + i);
				__m128 xmm2 = _mm_loadu_ps(c2 + i);
				xmm0 = _mm_fmsub_ps(xmm0, xmm1, xmm2);
				_mm_storeu_ps(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128 xmm0 = _mm_load_ss(a2 + i);
				__m128 xmm1 = _mm_load_ss(b2 + i);
				__m128 xmm2 = _mm_load_ss(c2 + i);
				xmm0 = _mm_fmsub_ss(xmm0, xmm1, xmm2);
				_mm_store_ss(dst2 + i, xmm0);
			}
		}

		virtual void MultiplySubtract(const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask) const {
			const T* a2 = static_cast<const T*>(a);
			const T* b2 = static_cast<const T*>(b);
			const T* c2 = static_cast<const T*>(c);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m128 xmm0 = _mm_loadu_ps(a2 + i);
				__m128 xmm1 = _mm_loadu_ps(a2 + i + 4);
				__m128 xmm2 = _mm_loadu_ps(b2 + i);
				__m128 xmm3 = _mm_loadu_ps(b2 + i + 4);

				xmm2 = _mm_fmsub_ps(xmm0, xmm2, _mm_loadu_ps(c2 + i));
				xmm3 = _mm_fmsub_ps(xmm1, xmm3, _mm_loadu_ps(c2 + i + 4));

				MaskSSE4(xmm2, xmm3, xmm0, xmm1, *mask, xmm0, xmm1);

				_mm_storeu_ps(dst2 + i, xmm0);
				_mm_storeu_ps(dst2 + i + 4, xmm1);
				++mask;
			}

			if (aligned_size != count) {
				a2 += aligned_size;
				b2 += aligned_size;
				c2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float a_buffer[8u];
				float b_buffer[8u];
				float c_buffer[8u];
				float dst_buffer[8u];
				memcpy(a_buffer, a2, sizeof(T) * count);
				memcpy(b_buffer, b2, sizeof(T) * count);
				memcpy(c_buffer, c2, sizeof(T) * count);
				MultiplySubtract(a_buffer, b_buffer, c_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}
	};

	class ArithmeticOperationsAvx512F32 : public ArithmeticOperationsFmaF32 {
	private:
		template<int ROUNDING_MODE>
		static void RoundAVX512(const void* src, void* dst, size_t count, const uint8_t* mask) {
			const T* src2 = static_cast<const T*>(src);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m256 xmm0 = _mm256_loadu_ps(src2 + i);
				xmm0 = _mm256_round_ps(xmm0, ROUNDING_MODE);
				xmm0 = _mm256_mask_and_ps(xmm0, *mask, xmm0, xmm0);
				_mm256_storeu_ps(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				src2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float src_buffer[8u];
				float dst_buffer[8u];
				memcpy(src_buffer, src2, sizeof(T) * count);
				RoundAVX512<ROUNDING_MODE>(src_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		static ANVIL_STRONG_INLINE __m256 HypotAVX512(__m256 a, __m256 b, __mmask8 mask) {
			a = _mm256_mul_ps(a, a);
			b = _mm256_fmadd_ps(b, b, a);
			return _mm256_mask_sqrt_ps(a, mask, b);
		}
	public:
		ArithmeticOperationsAvx512F32() :
			ArithmeticOperationsFmaF32()
		{}

		virtual ~ArithmeticOperationsAvx512F32() {

		}

		// 1 input

		virtual void Sqrt(const void* src, void* dst, size_t count, const uint8_t* mask) const {
			const T* src2 = static_cast<const T*>(src);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m256 xmm0 = _mm256_loadu_ps(src2 + i);
				xmm0 = _mm256_mask_sqrt_ps(xmm0, *mask, xmm0);
				_mm256_storeu_ps(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				src2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float src_buffer[8u];
				float dst_buffer[8u];
				memcpy(src_buffer, src2, sizeof(T) * count);
				Sqrt(src_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Not(const void* src, void* dst, size_t count, const uint8_t* mask) const {
			const T* src2 = static_cast<const T*>(src);
			T* dst2 = static_cast<T*>(dst);

			__m256 ones = _mm256_setzero_ps();
			ones = _mm256_cmp_ps(ones, ones, _CMP_EQ_OQ);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m256 xmm0 = _mm256_loadu_ps(src2 + i);
				xmm0 = _mm256_mask_xor_ps(xmm0, *mask, xmm0, ones);
				_mm256_storeu_ps(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				src2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float src_buffer[8u];
				float dst_buffer[8u];
				memcpy(src_buffer, src2, sizeof(T) * count);
				Not(src_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Round(const void* src, void* dst, size_t count, const uint8_t* mask) const {
			RoundAVX512<_MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC>(src, dst, count, mask);
		}

		virtual void Floor(const void* src, void* dst, size_t count, const uint8_t* mask) const {
			RoundAVX512<_MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC>(src, dst, count, mask);
		}

		virtual void RCeil(const void* src, void* dst, size_t count, const uint8_t* mask) const {
			RoundAVX512<_MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC>(src, dst, count, mask);
		}

		// 2 inputs

		virtual void Mask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {

			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m256 xmm0 = _mm256_loadu_ps(lhs2 + i);
				__m256 xmm2 = _mm256_loadu_ps(rhs2 + i);

				xmm0 = _mm256_mask_and_ps(xmm2, *mask, xmm0, xmm0);

				_mm256_storeu_ps(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Mask(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Add(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m256 xmm0 = _mm256_loadu_ps(lhs2 + i);
				__m256 xmm2 = _mm256_loadu_ps(rhs2 + i);

				xmm0 = _mm256_mask_add_ps(xmm0, *mask, xmm0, xmm2);

				_mm256_storeu_ps(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Add(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Subtract(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m256 xmm0 = _mm256_loadu_ps(lhs2 + i);
				__m256 xmm2 = _mm256_loadu_ps(rhs2 + i);

				xmm0 = _mm256_mask_sub_ps(xmm0, *mask, xmm0, xmm2);

				_mm256_storeu_ps(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Subtract(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Multiply(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m256 xmm0 = _mm256_loadu_ps(lhs2 + i);
				__m256 xmm2 = _mm256_loadu_ps(rhs2 + i);

				xmm0 = _mm256_mask_mul_ps(xmm0, *mask, xmm0, xmm2);

				_mm256_storeu_ps(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Multiply(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Divide(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m256 xmm0 = _mm256_loadu_ps(lhs2 + i);
				__m256 xmm2 = _mm256_loadu_ps(rhs2 + i);

				xmm0 = _mm256_mask_div_ps(xmm0, *mask, xmm0, xmm2);

				_mm256_storeu_ps(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Divide(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void And(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m256 xmm0 = _mm256_loadu_ps(lhs2 + i);
				__m256 xmm2 = _mm256_loadu_ps(rhs2 + i);

				xmm0 = _mm256_mask_and_ps(xmm0, *mask, xmm0, xmm2);

				_mm256_storeu_ps(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				And(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Or(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m256 xmm0 = _mm256_loadu_ps(lhs2 + i);
				__m256 xmm2 = _mm256_loadu_ps(rhs2 + i);

				xmm0 = _mm256_mask_or_ps(xmm0, *mask, xmm0, xmm2);

				_mm256_storeu_ps(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Or(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Xor(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m256 xmm0 = _mm256_loadu_ps(lhs2 + i);
				__m256 xmm2 = _mm256_loadu_ps(rhs2 + i);

				xmm0 = _mm256_mask_xor_ps(xmm0, *mask, xmm0, xmm2);

				_mm256_storeu_ps(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Xor(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Nand(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			__m256 ones = _mm256_setzero_ps();
			ones = _mm256_cmp_ps(ones, ones, _CMP_EQ_OQ);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m256 xmm0 = _mm256_loadu_ps(lhs2 + i);
				__m256 xmm2 = _mm256_loadu_ps(rhs2 + i);

				__mmask8 m = *mask;
				xmm0 = _mm256_mask_and_ps(xmm0, m, xmm0, xmm2);
				xmm0 = _mm256_mask_xor_ps(xmm0, m, xmm0, ones);

				_mm256_storeu_ps(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Nand(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Nor(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			__m256 ones = _mm256_setzero_ps();
			ones = _mm256_cmp_ps(ones, ones, _CMP_EQ_OQ);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m256 xmm0 = _mm256_loadu_ps(lhs2 + i);
				__m256 xmm2 = _mm256_loadu_ps(rhs2 + i);

				__mmask8 m = *mask;
				xmm0 = _mm256_mask_or_ps(xmm0, m, xmm0, xmm2);
				xmm0 = _mm256_mask_xor_ps(xmm0, m, xmm0, ones);

				_mm256_storeu_ps(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Nor(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Xnor(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			__m256 ones = _mm256_setzero_ps();
			ones = _mm256_cmp_ps(ones, ones, _CMP_EQ_OQ);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m256 xmm0 = _mm256_loadu_ps(lhs2 + i);
				__m256 xmm2 = _mm256_loadu_ps(rhs2 + i);

				__mmask8 m = *mask;
				xmm0 = _mm256_mask_xor_ps(xmm0, m, xmm0, xmm2);
				xmm0 = _mm256_mask_xor_ps(xmm0, m, xmm0, ones);

				_mm256_storeu_ps(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Xnor(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Hypotenuse(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m256 xmm0 = _mm256_loadu_ps(lhs2 + i);
				__m256 xmm2 = _mm256_loadu_ps(rhs2 + i);

				xmm0 = HypotAVX512(xmm0, xmm2, *mask);

				_mm256_storeu_ps(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Hypotenuse(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Minimum(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m256 xmm0 = _mm256_loadu_ps(lhs2 + i);
				__m256 xmm2 = _mm256_loadu_ps(rhs2 + i);

				xmm0 = _mm256_mask_min_ps(xmm0, *mask, xmm0, xmm2);

				_mm256_storeu_ps(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Minimum(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Maximum(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m256 xmm0 = _mm256_loadu_ps(lhs2 + i);
				__m256 xmm2 = _mm256_loadu_ps(rhs2 + i);

				xmm0 = _mm256_mask_max_ps(xmm0, *mask, xmm0, xmm2);

				_mm256_storeu_ps(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float lhs_buffer[8u];
				float rhs_buffer[8u];
				float dst_buffer[8u];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Maximum(lhs_buffer, rhs_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		// 3 inputs

		virtual void MultiplyAdd(const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask) const {
			const T* a2 = static_cast<const T*>(a);
			const T* b2 = static_cast<const T*>(b);
			const T* c2 = static_cast<const T*>(c);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m256 xmm0 = _mm256_loadu_ps(a2 + i);
				__m256 xmm1 = _mm256_loadu_ps(b2 + i);
				__m256 xmm2 = _mm256_loadu_ps(c2 + i);

#if ANVIL_COMPILER == ANVIL_MSVC
				// Visual studio doesn't support the 5th argument of _mm256_mask_fmadd_ps for some reason
				xmm1 = _mm256_fmadd_ps(xmm0, xmm1, xmm2);
				xmm0 = _mm256_mask_and_ps(xmm0, *mask, xmm1, xmm1);
#else
				xmm0 = _mm256_mask_fmadd_ps(xmm0, *mask, xmm0, xmm1, xmm2);
#endif


				_mm256_storeu_ps(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				a2 += aligned_size;
				b2 += aligned_size;
				c2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float a_buffer[8u];
				float b_buffer[8u];
				float c_buffer[8u];
				float dst_buffer[8u];
				memcpy(a_buffer, a2, sizeof(T) * count);
				memcpy(b_buffer, b2, sizeof(T) * count);
				memcpy(c_buffer, c2, sizeof(T) * count);
				MultiplyAdd(a_buffer, b_buffer, c_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void MultiplySubtract(const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask) const {
			const T* a2 = static_cast<const T*>(a);
			const T* b2 = static_cast<const T*>(b);
			const T* c2 = static_cast<const T*>(c);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / 8u) * 8u;
			size_t i = 0u;

			for (i; i < aligned_size; i += 8u) {
				__m256 xmm0 = _mm256_loadu_ps(a2 + i);
				__m256 xmm1 = _mm256_loadu_ps(b2 + i);
				__m256 xmm2 = _mm256_loadu_ps(c2 + i);

#if ANVIL_COMPILER == ANVIL_MSVC
				// Visual studio doesn't support the 5th argument of _mm256_mask_fmsub_ps for some reason
				xmm1 = _mm256_fmsub_ps(xmm0, xmm1, xmm2);
				xmm0 = _mm256_mask_and_ps(xmm0, *mask, xmm1, xmm1);
#else
				xmm0 = _mm256_mask_fmsub_ps(xmm0, *mask, xmm0, xmm1, xmm2);
#endif

				_mm256_storeu_ps(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				a2 += aligned_size;
				b2 += aligned_size;
				c2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				float a_buffer[8u];
				float b_buffer[8u];
				float c_buffer[8u];
				float dst_buffer[8u];
				memcpy(a_buffer, a2, sizeof(T) * count);
				memcpy(b_buffer, b2, sizeof(T) * count);
				memcpy(c_buffer, c2, sizeof(T) * count);
				MultiplySubtract(a_buffer, b_buffer, c_buffer, dst_buffer, 8u, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}
	};
#endif

}}}

#endif