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

#ifndef ANVIL_COMPUTE_ARITHMETIC_SSE_F64_HPP
#define ANVIL_COMPUTE_ARITHMETIC_SSE_F64_HPP

#include "anvil/compute/details/ArithmeticCpp.hpp"

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
#include <immintrin.h>
#endif

namespace anvil { namespace compute { namespace details {

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64

	enum {
		F64_VLEN_1X = 4,
		//F64_VLEN_2X = F64_VLEN_1X * 2,
		F64_VLEN_4X = F64_VLEN_1X * 4
	};

	class ArithmeticOperationsSseF64 : public ArithmeticOperationsCpp<double> {
	protected:

		static ANVIL_STRONG_INLINE void ExpandMaskSSE(uint8_t mask, __m128d & a, __m128d& b, __m128d& c, __m128d& d) {
			const __m128i bitsa = _mm_set_epi64x(2, 1);
			const __m128i bitsb = _mm_set_epi64x(8, 4);
			const __m128i bitsc = _mm_set_epi64x(32, 16);
			const __m128i bitsd = _mm_set_epi64x(128, 64);
			const __m128i m = _mm_set1_epi64x(mask);
			a = _mm_castsi128_pd(_mm_cmpeq_epi32(_mm_and_si128(m, bitsa), bitsa));
			b = _mm_castsi128_pd(_mm_cmpeq_epi32(_mm_and_si128(m, bitsb), bitsb));
			c = _mm_castsi128_pd(_mm_cmpeq_epi32(_mm_and_si128(m, bitsc), bitsc));
			d = _mm_castsi128_pd(_mm_cmpeq_epi32(_mm_and_si128(m, bitsd), bitsd));
		}

		static ANVIL_STRONG_INLINE void MaskSSE(
			__m128d  lhsa, __m128d  lhsb, __m128d  lhsc, __m128d  lhsd,
			__m128d  rhsa, __m128d rhsb, __m128d  rhsc, __m128d  rhsd,
			uint8_t mask,
			__m128d& outa, __m128d& outb, __m128d& outc, __m128d& outd
		) {
			__m128d  maska, maskb, maskc, maskd;
			ExpandMaskSSE(mask, maska, maskb, maskc, maskd);

			lhsa = _mm_and_pd(lhsa, maska);
			lhsb = _mm_and_pd(lhsa, maskb);
			lhsc = _mm_and_pd(lhsa, maskc);
			lhsd = _mm_and_pd(lhsa, maskd);
			rhsa = _mm_andnot_pd(maska, rhsa);
			rhsb = _mm_andnot_pd(maskb, rhsb);
			rhsc = _mm_andnot_pd(maskc, rhsc);
			rhsd = _mm_andnot_pd(maskd, rhsd);
			outa = _mm_or_pd(lhsa, rhsa);
			outb = _mm_or_pd(lhsb, rhsb);
			outc = _mm_or_pd(lhsc, rhsc);
			outd = _mm_or_pd(lhsd, rhsd);
		}

		static ANVIL_STRONG_INLINE __m128d  HypotSSE(__m128d  a, __m128d  b) {
			a = _mm_mul_pd(a, a);
			b = _mm_mul_pd(b, b);
			a = _mm_add_pd(a, b);
			return _mm_sqrt_pd(a);
		}
	public:
		typedef double T;

		ArithmeticOperationsSseF64() :
			ArithmeticOperationsCpp()
		{}

		virtual ~ArithmeticOperationsSseF64() {

		}

		// 1 input

		virtual void Sqrt(const void* src, void* dst, size_t count) const {
			const T* src2 = static_cast<const T*>(src);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_1X) * F64_VLEN_1X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_1X) {
				__m128d  xmm0 = _mm_loadu_pd(src2 + i);
				xmm0 = _mm_sqrt_pd(xmm0);
				_mm_storeu_pd(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128d  xmm0 = _mm_load_sd(src2 + i);
				xmm0 = _mm_sqrt_sd(xmm0, xmm0);
				_mm_store_sd(dst2 + i, xmm0);
			}
		}

		virtual void Not(const void* src, void* dst, size_t count) const {
			const T* src2 = static_cast<const T*>(src);
			T* dst2 = static_cast<T*>(dst);
			__m128d  ones = _mm_setzero_pd();
			ones = _mm_cmpeq_pd(ones, ones);
			
			size_t aligned_size = (count / F64_VLEN_1X) * F64_VLEN_1X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_1X) {
				__m128d  xmm0 = _mm_loadu_pd(src2 + i);
				xmm0 = _mm_xor_pd(xmm0, ones);
				_mm_storeu_pd(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128d  xmm0 = _mm_load_sd(src2 + i);
				xmm0 = _mm_xor_pd(xmm0, ones);
				_mm_store_sd(dst2 + i, xmm0);
			}
		}

		// 2 inputs

		virtual void Mask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst); 

			size_t aligned_size = (count / F64_VLEN_4X) * F64_VLEN_4X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_4X) {
				__m128d  la = _mm_loadu_pd(lhs2 + i);
				__m128d	 lb = _mm_loadu_pd(lhs2 + i + F64_VLEN_1X);
				__m128d  lc = _mm_loadu_pd(lhs2 + i + F64_VLEN_1X * 2);
				__m128d  ld = _mm_loadu_pd(lhs2 + i + F64_VLEN_1X * 3);

				__m128d  ra = _mm_loadu_pd(rhs2 + i);
				__m128d	 rb = _mm_loadu_pd(rhs2 + i + F64_VLEN_1X);
				__m128d  rc = _mm_loadu_pd(rhs2 + i + F64_VLEN_1X * 2);
				__m128d  rd = _mm_loadu_pd(rhs2 + i + F64_VLEN_1X * 3);

				MaskSSE(la, lb, lc, ld, ra, rb, rc, rd, *mask, la, lb, lc, ld);

				_mm_storeu_pd(dst2 + i, la);
				_mm_storeu_pd(dst2 + i + F64_VLEN_1X, lb);
				_mm_storeu_pd(dst2 + i + F64_VLEN_1X * 2, lc);
				_mm_storeu_pd(dst2 + i + F64_VLEN_1X * 3, ld);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				T lhs_buffer[F64_VLEN_4X];
				T rhs_buffer[F64_VLEN_4X];
				T dst_buffer[F64_VLEN_4X];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Mask(lhs_buffer, rhs_buffer, dst_buffer, F64_VLEN_4X, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Add(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_1X) * F64_VLEN_1X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_1X) {
				__m128d  xmm0 = _mm_loadu_pd(lhs2 + i);
				__m128d  xmm1 = _mm_loadu_pd(rhs2 + i);
				xmm0 = _mm_add_pd(xmm0, xmm1);
				_mm_storeu_pd(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128d  xmm0 = _mm_load_sd(lhs2 + i);
				__m128d  xmm1 = _mm_load_sd(rhs2 + i);
				xmm0 = _mm_add_sd(xmm0, xmm1);
				_mm_store_sd(dst2 + i, xmm0);
			}
		}

		virtual void Subtract(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_1X) * F64_VLEN_1X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_1X) {
				__m128d  xmm0 = _mm_loadu_pd(lhs2 + i);
				__m128d  xmm1 = _mm_loadu_pd(rhs2 + i);
				xmm0 = _mm_sub_pd(xmm0, xmm1);
				_mm_storeu_pd(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128d  xmm0 = _mm_load_sd(lhs2 + i);
				__m128d  xmm1 = _mm_load_sd(rhs2 + i);
				xmm0 = _mm_sub_sd(xmm0, xmm1);
				_mm_store_sd(dst2 + i, xmm0);
			}
		}

		virtual void Multiply(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_1X) * F64_VLEN_1X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_1X) {
				__m128d  xmm0 = _mm_loadu_pd(lhs2 + i);
				__m128d  xmm1 = _mm_loadu_pd(rhs2 + i);
				xmm0 = _mm_mul_pd(xmm0, xmm1);
				_mm_storeu_pd(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128d  xmm0 = _mm_load_sd(lhs2 + i);
				__m128d  xmm1 = _mm_load_sd(rhs2 + i);
				xmm0 = _mm_mul_sd(xmm0, xmm1);
				_mm_store_sd(dst2 + i, xmm0);
			}
		}

		virtual void Divide(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_1X) * F64_VLEN_1X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_1X) {
				__m128d  xmm0 = _mm_loadu_pd(lhs2 + i);
				__m128d  xmm1 = _mm_loadu_pd(rhs2 + i);
				xmm0 = _mm_div_pd(xmm0, xmm1);
				_mm_storeu_pd(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128d  xmm0 = _mm_load_sd(lhs2 + i);
				__m128d  xmm1 = _mm_load_sd(rhs2 + i);
				xmm0 = _mm_div_sd(xmm0, xmm1);
				_mm_store_sd(dst2 + i, xmm0);
			}
		}

		virtual void And(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_1X) * F64_VLEN_1X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_1X) {
				__m128d  xmm0 = _mm_loadu_pd(lhs2 + i);
				__m128d  xmm1 = _mm_loadu_pd(rhs2 + i);
				xmm0 = _mm_and_pd(xmm0, xmm1);
				_mm_storeu_pd(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128d  xmm0 = _mm_load_sd(lhs2 + i);
				__m128d  xmm1 = _mm_load_sd(rhs2 + i);
				xmm0 = _mm_and_pd(xmm0, xmm1);
				_mm_store_sd(dst2 + i, xmm0);
			}
		}

		virtual void Or(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_1X) * F64_VLEN_1X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_1X) {
				__m128d  xmm0 = _mm_loadu_pd(lhs2 + i);
				__m128d  xmm1 = _mm_loadu_pd(rhs2 + i);
				xmm0 = _mm_or_pd(xmm0, xmm1);
				_mm_storeu_pd(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128d  xmm0 = _mm_load_sd(lhs2 + i);
				__m128d  xmm1 = _mm_load_sd(rhs2 + i);
				xmm0 = _mm_or_pd(xmm0, xmm1);
				_mm_store_sd(dst2 + i, xmm0);
			}
		}

		virtual void Xor(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_1X) * F64_VLEN_1X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_1X) {
				__m128d  xmm0 = _mm_loadu_pd(lhs2 + i);
				__m128d  xmm1 = _mm_loadu_pd(rhs2 + i);
				xmm0 = _mm_xor_pd(xmm0, xmm1);
				_mm_storeu_pd(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128d  xmm0 = _mm_load_sd(lhs2 + i);
				__m128d  xmm1 = _mm_load_sd(rhs2 + i);
				xmm0 = _mm_xor_pd(xmm0, xmm1);
				_mm_store_sd(dst2 + i, xmm0);
			}
		}

		virtual void Nand(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			__m128d  ones = _mm_setzero_pd();
			ones = _mm_cmpeq_pd(ones, ones);

			size_t aligned_size = (count / F64_VLEN_1X) * F64_VLEN_1X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_1X) {
				__m128d  xmm0 = _mm_loadu_pd(lhs2 + i);
				__m128d  xmm1 = _mm_loadu_pd(rhs2 + i);
				xmm0 = _mm_and_pd(xmm0, xmm1);
				xmm0 = _mm_xor_pd(xmm0, ones);
				_mm_storeu_pd(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128d  xmm0 = _mm_load_sd(lhs2 + i);
				__m128d  xmm1 = _mm_load_sd(rhs2 + i);
				xmm0 = _mm_and_pd(xmm0, xmm1);
				xmm0 = _mm_xor_pd(xmm0, ones);
				_mm_store_sd(dst2 + i, xmm0);
			}
		}

		virtual void Nor(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			__m128d  ones = _mm_setzero_pd();
			ones = _mm_cmpeq_pd(ones, ones);

			size_t aligned_size = (count / F64_VLEN_1X) * F64_VLEN_1X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_1X) {
				__m128d  xmm0 = _mm_loadu_pd(lhs2 + i);
				__m128d  xmm1 = _mm_loadu_pd(rhs2 + i);
				xmm0 = _mm_or_pd(xmm0, xmm1);
				xmm0 = _mm_xor_pd(xmm0, ones);
				_mm_storeu_pd(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128d  xmm0 = _mm_load_sd(lhs2 + i);
				__m128d  xmm1 = _mm_load_sd(rhs2 + i);
				xmm0 = _mm_or_pd(xmm0, xmm1);
				xmm0 = _mm_xor_pd(xmm0, ones);
				_mm_store_sd(dst2 + i, xmm0);
			}
		}

		virtual void Xnor(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			__m128d  ones = _mm_setzero_pd();
			ones = _mm_cmpeq_pd(ones, ones);

			size_t aligned_size = (count / F64_VLEN_1X) * F64_VLEN_1X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_1X) {
				__m128d  xmm0 = _mm_loadu_pd(lhs2 + i);
				__m128d  xmm1 = _mm_loadu_pd(rhs2 + i);
				xmm0 = _mm_xor_pd(xmm0, xmm1);
				xmm0 = _mm_xor_pd(xmm0, ones);
				_mm_storeu_pd(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128d  xmm0 = _mm_load_sd(lhs2 + i);
				__m128d  xmm1 = _mm_load_sd(rhs2 + i);
				xmm0 = _mm_xor_pd(xmm0, xmm1);
				xmm0 = _mm_xor_pd(xmm0, ones);
				_mm_store_sd(dst2 + i, xmm0);
			}
		}

		virtual void Hypotenuse(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_1X) * F64_VLEN_1X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_1X) {
				__m128d  xmm0 = _mm_loadu_pd(lhs2 + i);
				__m128d  xmm1 = _mm_loadu_pd(rhs2 + i);
				xmm0 = HypotSSE(xmm0, xmm1);
				_mm_storeu_pd(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128d  xmm0 = _mm_load_sd(lhs2 + i);
				__m128d  xmm1 = _mm_load_sd(rhs2 + i);
				xmm0 = HypotSSE(xmm0, xmm1);
				_mm_store_sd(dst2 + i, xmm0);
			}
		}

		virtual void Minimum(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_1X) * F64_VLEN_1X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_1X) {
				__m128d  xmm0 = _mm_loadu_pd(lhs2 + i);
				__m128d  xmm1 = _mm_loadu_pd(rhs2 + i);
				xmm0 = _mm_min_pd(xmm0, xmm1);
				_mm_storeu_pd(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128d  xmm0 = _mm_load_sd(lhs2 + i);
				__m128d  xmm1 = _mm_load_sd(rhs2 + i);
				xmm0 = _mm_min_sd(xmm0, xmm1);
				_mm_store_sd(dst2 + i, xmm0);
			}
		}

		virtual void Maximum(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_1X) * F64_VLEN_1X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_1X) {
				__m128d  xmm0 = _mm_loadu_pd(lhs2 + i);
				__m128d  xmm1 = _mm_loadu_pd(rhs2 + i);
				xmm0 = _mm_max_pd(xmm0, xmm1);
				_mm_storeu_pd(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128d  xmm0 = _mm_load_sd(lhs2 + i);
				__m128d  xmm1 = _mm_load_sd(rhs2 + i);
				xmm0 = _mm_max_sd(xmm0, xmm1);
				_mm_store_sd(dst2 + i, xmm0);
			}
		}

		// 3 inputs

		virtual void MultiplyAdd(const void* a, const void* b, const void* c, void* dst, size_t count) const {
			const T* a2 = static_cast<const T*>(a);
			const T* b2 = static_cast<const T*>(b);
			const T* c2 = static_cast<const T*>(c);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_1X) * F64_VLEN_1X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_1X) {
				__m128d  xmm0 = _mm_loadu_pd(a2 + i);
				__m128d  xmm1 = _mm_loadu_pd(b2 + i);
				__m128d  xmm2 = _mm_loadu_pd(c2 + i);
				xmm0 = _mm_mul_pd(xmm0, xmm1);
				xmm0 = _mm_add_pd(xmm0, xmm2);
				_mm_storeu_pd(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128d  xmm0 = _mm_load_sd(a2 + i);
				__m128d  xmm1 = _mm_load_sd(b2 + i);
				__m128d  xmm2 = _mm_load_sd(c2 + i);
				xmm0 = _mm_mul_sd(xmm0, xmm1);
				xmm0 = _mm_add_sd(xmm0, xmm2);
				_mm_store_sd(dst2 + i, xmm0);
			}
		}

		virtual void MultiplySubtract(const void* a, const void* b, const void* c, void* dst, size_t count) const {
			const T* a2 = static_cast<const T*>(a);
			const T* b2 = static_cast<const T*>(b);
			const T* c2 = static_cast<const T*>(c);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_1X) * F64_VLEN_1X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_1X) {
				__m128d  xmm0 = _mm_loadu_pd(a2 + i);
				__m128d  xmm1 = _mm_loadu_pd(b2 + i);
				__m128d  xmm2 = _mm_loadu_pd(c2 + i);
				xmm0 = _mm_mul_pd(xmm0, xmm1);
				xmm0 = _mm_sub_pd(xmm0, xmm2);
				_mm_storeu_pd(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128d  xmm0 = _mm_load_sd(a2 + i);
				__m128d  xmm1 = _mm_load_sd(b2 + i);
				__m128d  xmm2 = _mm_load_sd(c2 + i);
				xmm0 = _mm_mul_sd(xmm0, xmm1);
				xmm0 = _mm_sub_sd(xmm0, xmm2);
				_mm_store_sd(dst2 + i, xmm0);
			}
		}
	};

	class ArithmeticOperationsSse4F64 : public ArithmeticOperationsSseF64 {
	protected:

		static ANVIL_STRONG_INLINE void MaskSSE4(
			__m128d  lhsa, __m128d  lhsb, __m128d  lhsc, __m128d  lhsd,
			__m128d  rhsa, __m128d rhsb, __m128d  rhsc, __m128d  rhsd,
			uint8_t mask,
			__m128d& outa, __m128d& outb, __m128d& outc, __m128d& outd
		) {
			__m128d  maska, maskb, maskc, maskd;
			ExpandMaskSSE(mask, maska, maskb, maskc, maskd);

			outa = _mm_blendv_pd(rhsa, lhsa, maska);
			outb = _mm_blendv_pd(rhsb, lhsb, maskb);
			outc = _mm_blendv_pd(rhsc, lhsc, maskc);
			outd = _mm_blendv_pd(rhsd, lhsd, maskd);
		}

		template<int ROUNDING_MODE>
		static void RoundSSE4(const void* src, void* dst, size_t count) {
			const T* src2 = static_cast<const T*>(src);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_1X) * F64_VLEN_1X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_1X) {
				__m128d  xmm0 = _mm_loadu_pd(src2 + i);
				xmm0 = _mm_round_pd(xmm0, ROUNDING_MODE);
				_mm_storeu_pd(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128d  xmm0 = _mm_load_sd(src2 + i);
				xmm0 = _mm_round_pd(xmm0, ROUNDING_MODE);
				_mm_store_sd(dst2 + i, xmm0);
			}
		}
	public:
		ArithmeticOperationsSse4F64() :
			ArithmeticOperationsSseF64()
		{}

		virtual ~ArithmeticOperationsSse4F64() {

		}

		// 2 inputs

		virtual void Mask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst); 

			size_t aligned_size = (count / F64_VLEN_4X) * F64_VLEN_4X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_4X) {
				__m128d  la = _mm_loadu_pd(lhs2 + i);
				__m128d	 lb = _mm_loadu_pd(lhs2 + i + F64_VLEN_1X);
				__m128d  lc = _mm_loadu_pd(lhs2 + i + F64_VLEN_1X * 2);
				__m128d  ld = _mm_loadu_pd(lhs2 + i + F64_VLEN_1X * 3);

				__m128d  ra = _mm_loadu_pd(rhs2 + i);
				__m128d	 rb = _mm_loadu_pd(rhs2 + i + F64_VLEN_1X);
				__m128d  rc = _mm_loadu_pd(rhs2 + i + F64_VLEN_1X * 2);
				__m128d  rd = _mm_loadu_pd(rhs2 + i + F64_VLEN_1X * 3);

				MaskSSE4(la, lb, lc, ld, ra, rb, rc, rd, *mask, la, lb, lc, ld);

				_mm_storeu_pd(dst2 + i, la);
				_mm_storeu_pd(dst2 + i + F64_VLEN_1X, lb);
				_mm_storeu_pd(dst2 + i + F64_VLEN_1X * 2, lc);
				_mm_storeu_pd(dst2 + i + F64_VLEN_1X * 3, ld);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				T lhs_buffer[F64_VLEN_4X];
				T rhs_buffer[F64_VLEN_4X];
				T dst_buffer[F64_VLEN_4X];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Mask(lhs_buffer, rhs_buffer, dst_buffer, F64_VLEN_4X, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}
	};

	class ArithmeticOperationsFmaF64 : public ArithmeticOperationsSse4F64 {
	private:
		static ANVIL_STRONG_INLINE __m128d  HypotFMA(__m128d  a, __m128d  b) {
			a = _mm_mul_pd(a, a);
			b = _mm_fmadd_pd(b, b, a);
			return _mm_sqrt_pd(b);
		}
	public:
		ArithmeticOperationsFmaF64() :
			ArithmeticOperationsSse4F64()
		{}

		virtual ~ArithmeticOperationsFmaF64() {

		}

		// 2 inputs

		virtual void Hypotenuse(const void* lhs, const void* rhs, void* dst, size_t count) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_1X) * F64_VLEN_1X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_1X) {
				__m128d  xmm0 = _mm_loadu_pd(lhs2 + i);
				__m128d  xmm1 = _mm_loadu_pd(rhs2 + i);
				xmm0 = HypotFMA(xmm0, xmm1);
				_mm_storeu_pd(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128d  xmm0 = _mm_load_sd(lhs2 + i);
				__m128d  xmm1 = _mm_load_sd(rhs2 + i);
				xmm0 = HypotFMA(xmm0, xmm1);
				_mm_store_sd(dst2 + i, xmm0);
			}
		}

		// 3 inputs

		virtual void MultiplyAdd(const void* a, const void* b, const void* c, void* dst, size_t count) const {
			const T* a2 = static_cast<const T*>(a);
			const T* b2 = static_cast<const T*>(b);
			const T* c2 = static_cast<const T*>(c);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_1X) * F64_VLEN_1X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_1X) {
				__m128d  xmm0 = _mm_loadu_pd(a2 + i);
				__m128d  xmm1 = _mm_loadu_pd(b2 + i);
				__m128d  xmm2 = _mm_loadu_pd(c2 + i);
				xmm0 = _mm_fmadd_pd(xmm0, xmm1, xmm2);
				_mm_storeu_pd(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128d  xmm0 = _mm_load_sd(a2 + i);
				__m128d  xmm1 = _mm_load_sd(b2 + i);
				__m128d  xmm2 = _mm_load_sd(c2 + i);
				xmm0 = _mm_fmadd_sd(xmm0, xmm1, xmm2);
				_mm_store_sd(dst2 + i, xmm0);
			}
		}

		virtual void MultiplySubtract(const void* a, const void* b, const void* c, void* dst, size_t count) const {
			const T* a2 = static_cast<const T*>(a);
			const T* b2 = static_cast<const T*>(b);
			const T* c2 = static_cast<const T*>(c);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_1X) * F64_VLEN_1X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_1X) {
				__m128d  xmm0 = _mm_loadu_pd(a2 + i);
				__m128d  xmm1 = _mm_loadu_pd(b2 + i);
				__m128d  xmm2 = _mm_loadu_pd(c2 + i);
				xmm0 = _mm_fmsub_pd(xmm0, xmm1, xmm2);
				_mm_storeu_pd(dst2 + i, xmm0);
			}

			for (i; i < count; ++i) {
				__m128d  xmm0 = _mm_load_sd(a2 + i);
				__m128d  xmm1 = _mm_load_sd(b2 + i);
				__m128d  xmm2 = _mm_load_sd(c2 + i);
				xmm0 = _mm_fmsub_sd(xmm0, xmm1, xmm2);
				_mm_store_sd(dst2 + i, xmm0);
			}
		}

	};

	class ArithmeticOperationsAvx512F64 : public ArithmeticOperationsFmaF64 {
	private:
		template<int ROUNDING_MODE>
		static void RoundAVX512(const void* src, void* dst, size_t count, const uint8_t* mask) {
			const T* src2 = static_cast<const T*>(src);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_4X) * F64_VLEN_4X;
			size_t i = 0u;

			__m512d zeros = _mm512_setzero_pd();

			for (i; i < aligned_size; i += F64_VLEN_4X) {
				__m512d xmm0 = _mm512_loadu_pd(src2 + i);
				xmm0 = _mm512_add_round_pd(zeros, xmm0, ROUNDING_MODE);
				xmm0 = _mm512_mask_and_pd(xmm0, *mask, xmm0, xmm0);
				_mm512_storeu_pd(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				src2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				T src_buffer[F64_VLEN_4X];
				T dst_buffer[F64_VLEN_4X];
				memcpy(src_buffer, src2, sizeof(T) * count);
				RoundAVX512<ROUNDING_MODE>(src_buffer, dst_buffer, F64_VLEN_4X, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		static ANVIL_STRONG_INLINE __m512d HypotAVX512(__m512d src, __m512d a, __m512d b, __mmask8 mask) {
			a = _mm512_mul_pd(a, a);
			b = _mm512_fmadd_pd(b, b, a);
			return _mm512_mask_sqrt_pd(src, mask, b);
		}
	public:
		ArithmeticOperationsAvx512F64() :
			ArithmeticOperationsFmaF64()
		{}

		virtual ~ArithmeticOperationsAvx512F64() {

		}

		// 1 input

		virtual void Sqrt(const void* src, void* dst, size_t count, const uint8_t* mask) const {
			const T* src2 = static_cast<const T*>(src);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_4X) * F64_VLEN_4X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_4X) {
				__m512d xmm0 = _mm512_loadu_pd(src2 + i);
				xmm0 = _mm512_mask_sqrt_pd(xmm0, *mask, xmm0);
				_mm512_storeu_pd(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				src2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				T src_buffer[F64_VLEN_4X];
				T dst_buffer[F64_VLEN_4X];
				memcpy(src_buffer, src2, sizeof(T) * count);
				Sqrt(src_buffer, dst_buffer, F64_VLEN_4X, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Not(const void* src, void* dst, size_t count, const uint8_t* mask) const {
			const T* src2 = static_cast<const T*>(src);
			T* dst2 = static_cast<T*>(dst);

			__m512d ones = _mm512_castsi512_pd(_mm512_set1_epi32(-1));

			size_t aligned_size = (count / F64_VLEN_4X) * F64_VLEN_4X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_4X) {
				__m512d xmm0 = _mm512_loadu_pd(src2 + i);
				xmm0 = _mm512_mask_xor_pd(xmm0, *mask, xmm0, ones);
				_mm512_storeu_pd(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				src2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				T src_buffer[F64_VLEN_4X];
				T dst_buffer[F64_VLEN_4X];
				memcpy(src_buffer, src2, sizeof(T) * count);
				Not(src_buffer, dst_buffer, F64_VLEN_4X, mask);
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

			size_t aligned_size = (count / F64_VLEN_4X) * F64_VLEN_4X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_4X) {
				__m512d xmm0 = _mm512_loadu_pd(lhs2 + i);
				__m512d xmm2 = _mm512_loadu_pd(rhs2 + i);

				xmm0 = _mm512_mask_and_pd(xmm2, *mask, xmm0, xmm0);

				_mm512_storeu_pd(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				T lhs_buffer[F64_VLEN_4X];
				T rhs_buffer[F64_VLEN_4X];
				T dst_buffer[F64_VLEN_4X];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Mask(lhs_buffer, rhs_buffer, dst_buffer, F64_VLEN_4X, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Add(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_4X) * F64_VLEN_4X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_4X) {
				__m512d xmm0 = _mm512_loadu_pd(lhs2 + i);
				__m512d xmm2 = _mm512_loadu_pd(rhs2 + i);

				xmm0 = _mm512_mask_add_pd(xmm0, *mask, xmm0, xmm2);

				_mm512_storeu_pd(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				T lhs_buffer[F64_VLEN_4X];
				T rhs_buffer[F64_VLEN_4X];
				T dst_buffer[F64_VLEN_4X];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Add(lhs_buffer, rhs_buffer, dst_buffer, F64_VLEN_4X, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Subtract(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_4X) * F64_VLEN_4X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_4X) {
				__m512d xmm0 = _mm512_loadu_pd(lhs2 + i);
				__m512d xmm2 = _mm512_loadu_pd(rhs2 + i);

				xmm0 = _mm512_mask_sub_pd(xmm0, *mask, xmm0, xmm2);

				_mm512_storeu_pd(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				T lhs_buffer[F64_VLEN_4X];
				T rhs_buffer[F64_VLEN_4X];
				T dst_buffer[F64_VLEN_4X];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Subtract(lhs_buffer, rhs_buffer, dst_buffer, F64_VLEN_4X, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Multiply(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_4X) * F64_VLEN_4X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_4X) {
				__m512d xmm0 = _mm512_loadu_pd(lhs2 + i);
				__m512d xmm2 = _mm512_loadu_pd(rhs2 + i);

				xmm0 = _mm512_mask_mul_pd(xmm0, *mask, xmm0, xmm2);

				_mm512_storeu_pd(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				T lhs_buffer[F64_VLEN_4X];
				T rhs_buffer[F64_VLEN_4X];
				T dst_buffer[F64_VLEN_4X];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Multiply(lhs_buffer, rhs_buffer, dst_buffer, F64_VLEN_4X, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Divide(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_4X) * F64_VLEN_4X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_4X) {
				__m512d xmm0 = _mm512_loadu_pd(lhs2 + i);
				__m512d xmm2 = _mm512_loadu_pd(rhs2 + i);

				xmm0 = _mm512_mask_div_pd(xmm0, *mask, xmm0, xmm2);

				_mm512_storeu_pd(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				T lhs_buffer[F64_VLEN_4X];
				T rhs_buffer[F64_VLEN_4X];
				T dst_buffer[F64_VLEN_4X];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Divide(lhs_buffer, rhs_buffer, dst_buffer, F64_VLEN_4X, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void And(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_4X) * F64_VLEN_4X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_4X) {
				__m512d xmm0 = _mm512_loadu_pd(lhs2 + i);
				__m512d xmm2 = _mm512_loadu_pd(rhs2 + i);

				xmm0 = _mm512_mask_and_pd(xmm0, *mask, xmm0, xmm2);

				_mm512_storeu_pd(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				T lhs_buffer[F64_VLEN_4X];
				T rhs_buffer[F64_VLEN_4X];
				T dst_buffer[F64_VLEN_4X];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				And(lhs_buffer, rhs_buffer, dst_buffer, F64_VLEN_4X, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Or(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_4X) * F64_VLEN_4X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_4X) {
				__m512d xmm0 = _mm512_loadu_pd(lhs2 + i);
				__m512d xmm2 = _mm512_loadu_pd(rhs2 + i);

				xmm0 = _mm512_mask_or_pd(xmm0, *mask, xmm0, xmm2);

				_mm512_storeu_pd(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				T lhs_buffer[F64_VLEN_4X];
				T rhs_buffer[F64_VLEN_4X];
				T dst_buffer[F64_VLEN_4X];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Or(lhs_buffer, rhs_buffer, dst_buffer, F64_VLEN_4X, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Xor(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_4X) * F64_VLEN_4X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_4X) {
				__m512d xmm0 = _mm512_loadu_pd(lhs2 + i);
				__m512d xmm2 = _mm512_loadu_pd(rhs2 + i);

				xmm0 = _mm512_mask_xor_pd(xmm0, *mask, xmm0, xmm2);

				_mm512_storeu_pd(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				T lhs_buffer[F64_VLEN_4X];
				T rhs_buffer[F64_VLEN_4X];
				T dst_buffer[F64_VLEN_4X];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Xor(lhs_buffer, rhs_buffer, dst_buffer, F64_VLEN_4X, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Nand(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			__m512d ones = _mm512_castsi512_pd(_mm512_set1_epi32(-1));

			size_t aligned_size = (count / F64_VLEN_4X) * F64_VLEN_4X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_4X) {
				__m512d xmm0 = _mm512_loadu_pd(lhs2 + i);
				__m512d xmm2 = _mm512_loadu_pd(rhs2 + i);

				__mmask8 m = *mask;
				xmm0 = _mm512_mask_and_pd(xmm0, m, xmm0, xmm2);
				xmm0 = _mm512_mask_xor_pd(xmm0, m, xmm0, ones);

				_mm512_storeu_pd(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				T lhs_buffer[F64_VLEN_4X];
				T rhs_buffer[F64_VLEN_4X];
				T dst_buffer[F64_VLEN_4X];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Nand(lhs_buffer, rhs_buffer, dst_buffer, F64_VLEN_4X, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Nor(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			__m512d ones = _mm512_castsi512_pd(_mm512_set1_epi32(-1));

			size_t aligned_size = (count / F64_VLEN_4X) * F64_VLEN_4X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_4X) {
				__m512d xmm0 = _mm512_loadu_pd(lhs2 + i);
				__m512d xmm2 = _mm512_loadu_pd(rhs2 + i);

				__mmask8 m = *mask;
				xmm0 = _mm512_mask_or_pd(xmm0, m, xmm0, xmm2);
				xmm0 = _mm512_mask_xor_pd(xmm0, m, xmm0, ones);

				_mm512_storeu_pd(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				T lhs_buffer[F64_VLEN_4X];
				T rhs_buffer[F64_VLEN_4X];
				T dst_buffer[F64_VLEN_4X];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Nor(lhs_buffer, rhs_buffer, dst_buffer, F64_VLEN_4X, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Xnor(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			__m512d ones = _mm512_castsi512_pd(_mm512_set1_epi32(-1));

			size_t aligned_size = (count / F64_VLEN_4X) * F64_VLEN_4X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_4X) {
				__m512d xmm0 = _mm512_loadu_pd(lhs2 + i);
				__m512d xmm2 = _mm512_loadu_pd(rhs2 + i);

				__mmask8 m = *mask;
				xmm0 = _mm512_mask_xor_pd(xmm0, m, xmm0, xmm2);
				xmm0 = _mm512_mask_xor_pd(xmm0, m, xmm0, ones);

				_mm512_storeu_pd(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				T lhs_buffer[F64_VLEN_4X];
				T rhs_buffer[F64_VLEN_4X];
				T dst_buffer[F64_VLEN_4X];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Xnor(lhs_buffer, rhs_buffer, dst_buffer, F64_VLEN_4X, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Hypotenuse(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_4X) * F64_VLEN_4X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_4X) {
				__m512d xmm0 = _mm512_loadu_pd(lhs2 + i);
				__m512d xmm2 = _mm512_loadu_pd(rhs2 + i);

				xmm0 = HypotAVX512(xmm0, xmm0, xmm2, *mask);

				_mm512_storeu_pd(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				T lhs_buffer[F64_VLEN_4X];
				T rhs_buffer[F64_VLEN_4X];
				T dst_buffer[F64_VLEN_4X];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Hypotenuse(lhs_buffer, rhs_buffer, dst_buffer, F64_VLEN_4X, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Minimum(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_4X) * F64_VLEN_4X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_4X) {
				__m512d xmm0 = _mm512_loadu_pd(lhs2 + i);
				__m512d xmm2 = _mm512_loadu_pd(rhs2 + i);

				xmm0 = _mm512_mask_min_pd(xmm0, *mask, xmm0, xmm2);

				_mm512_storeu_pd(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				T lhs_buffer[F64_VLEN_4X];
				T rhs_buffer[F64_VLEN_4X];
				T dst_buffer[F64_VLEN_4X];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Minimum(lhs_buffer, rhs_buffer, dst_buffer, F64_VLEN_4X, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void Maximum(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
			const T* lhs2 = static_cast<const T*>(lhs);
			const T* rhs2 = static_cast<const T*>(rhs);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_4X) * F64_VLEN_4X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_4X) {
				__m512d xmm0 = _mm512_loadu_pd(lhs2 + i);
				__m512d xmm2 = _mm512_loadu_pd(rhs2 + i);

				xmm0 = _mm512_mask_max_pd(xmm0, *mask, xmm0, xmm2);

				_mm512_storeu_pd(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				lhs2 += aligned_size;
				rhs2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				T lhs_buffer[F64_VLEN_4X];
				T rhs_buffer[F64_VLEN_4X];
				T dst_buffer[F64_VLEN_4X];
				memcpy(lhs_buffer, lhs2, sizeof(T) * count);
				memcpy(rhs_buffer, rhs2, sizeof(T) * count);
				Maximum(lhs_buffer, rhs_buffer, dst_buffer, F64_VLEN_4X, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		// 3 inputs

		virtual void MultiplyAdd(const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask) const {
			const T* a2 = static_cast<const T*>(a);
			const T* b2 = static_cast<const T*>(b);
			const T* c2 = static_cast<const T*>(c);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_4X) * F64_VLEN_4X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_4X) {
				__m512d xmm0 = _mm512_loadu_pd(a2 + i);
				__m512d xmm1 = _mm512_loadu_pd(b2 + i);
				__m512d xmm2 = _mm512_loadu_pd(c2 + i);

#if ANVIL_COMPILER == ANVIL_MSVC
				// Visual studio doesn't support the 5th argument of _mm512_mask_fmadd_ps for some reason
				xmm1 = _mm512_fmadd_pd(xmm0, xmm1, xmm2);
				xmm0 = _mm512_mask_and_pd(xmm0, *mask, xmm1, xmm1);
#else
				xmm0 = _mm512_mask_fmadd_pd(xmm0, *mask, xmm0, xmm1, xmm2);
#endif


				_mm512_storeu_pd(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				a2 += aligned_size;
				b2 += aligned_size;
				c2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				T a_buffer[F64_VLEN_4X];
				T b_buffer[F64_VLEN_4X];
				T c_buffer[F64_VLEN_4X];
				T dst_buffer[F64_VLEN_4X];
				memcpy(a_buffer, a2, sizeof(T) * count);
				memcpy(b_buffer, b2, sizeof(T) * count);
				memcpy(c_buffer, c2, sizeof(T) * count);
				MultiplyAdd(a_buffer, b_buffer, c_buffer, dst_buffer, F64_VLEN_4X, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}

		virtual void MultiplySubtract(const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask) const {
			const T* a2 = static_cast<const T*>(a);
			const T* b2 = static_cast<const T*>(b);
			const T* c2 = static_cast<const T*>(c);
			T* dst2 = static_cast<T*>(dst);

			size_t aligned_size = (count / F64_VLEN_4X) * F64_VLEN_4X;
			size_t i = 0u;

			for (i; i < aligned_size; i += F64_VLEN_4X) {
				__m512d xmm0 = _mm512_loadu_pd(a2 + i);
				__m512d xmm1 = _mm512_loadu_pd(b2 + i);
				__m512d xmm2 = _mm512_loadu_pd(c2 + i);

#if ANVIL_COMPILER == ANVIL_MSVC
				// Visual studio doesn't support the 5th argument of _mm512_mask_fmsub_ps for some reason
				xmm1 = _mm512_fmsub_pd(xmm0, xmm1, xmm2);
				xmm0 = _mm512_mask_and_pd(xmm0, *mask, xmm1, xmm1);
#else
				xmm0 = _mm512_mask_fmsub_pd(xmm0, *mask, xmm0, xmm1, xmm2);
#endif

				_mm512_storeu_pd(dst2 + i, xmm0);
				++mask;
			}

			if (aligned_size != count) {
				a2 += aligned_size;
				b2 += aligned_size;
				c2 += aligned_size;
				dst2 += aligned_size;
				count -= aligned_size;

				T a_buffer[F64_VLEN_4X];
				T b_buffer[F64_VLEN_4X];
				T c_buffer[F64_VLEN_4X];
				T dst_buffer[F64_VLEN_4X];
				memcpy(a_buffer, a2, sizeof(T) * count);
				memcpy(b_buffer, b2, sizeof(T) * count);
				memcpy(c_buffer, c2, sizeof(T) * count);
				MultiplySubtract(a_buffer, b_buffer, c_buffer, dst_buffer, F64_VLEN_4X, mask);
				memcpy(dst, dst_buffer, sizeof(T) * count);
			}
		}
	};
#endif

}}}

#endif