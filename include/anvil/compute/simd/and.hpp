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

#ifndef ANVIL_COMPUTE_SIMD_AND_HPP
#define ANVIL_COMPUTE_SIMD_AND_HPP

#include "anvil/core/CpuRuntime.hpp"
#include "anvil/compute/Vector.hpp"
#include "anvil/compute/simd/Blend.hpp"

namespace anvil { namespace detail {

	enum VectorBitwiseOp2 {
		VECTOR_BIT_OP_AND,
		VECTOR_BIT_OP_OR,
		VECTOR_BIT_OP_XOR,
	};

	template<NativeUnsigned OP, size_t BYTES>
	static ANVIL_STRONG_INLINE void VectorBitOpC(void* a, const void* b) {
		enum {
			words = BYTES / sizeof(NativeUnsigned),
			bytes = BYTES - (words * sizeof(NativeUnsigned))
		};

		union {
			NativeUnsigned* wa;
			uint8_t* ba;
			void* va;
		};

		union {
			const NativeUnsigned* wb;
			const uint8_t* bb;
			const void* vb;
		};

		va = a;
		vb = b;

		for (size_t i = 0u; i < words; ++i) {
			if constexpr (OP == VECTOR_BIT_OP_AND) {
				wa[i] &= wb[i];
			} else if constexpr (OP == VECTOR_BIT_OP_OR) {
				wa[i] |= wb[i];
			} else if constexpr (OP == VECTOR_BIT_OP_XOR) {
				wa[i] ^= wb[i];
			}
		}

		if constexpr (bytes > 0u) {
			wa += words;
			wb += words;

			for (size_t i = 0u; i < bytes; ++i) {
				if constexpr (OP == VECTOR_BIT_OP_AND) {
					ba[i] &= bb[i];
				} else if constexpr (OP == VECTOR_BIT_OP_OR) {
					ba[i] |= bb[i];
				} else if constexpr (OP == VECTOR_BIT_OP_XOR) {
					ba[i] ^= bb[i];
				}
			}
		}
	};

	template<class T>
	struct VectorBitOp {
		typedef T type;
		enum { optimised = 0 };
		enum : uint64_t { recommended_instruction_set = 0ull };

		template<uint64_t instruction_sets, NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute(type& a, const type& b) {
			VectorBitOpC<OP, sizeof(type)>(&a, &b);
		}
	};

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64

	template<>
	struct VectorBitOp<__m128> {
		typedef __m128 type;
		enum { optimised = 1 };
		enum : uint64_t { recommended_instruction_set = ASM_SSE };

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute_SSE(type& a, const type& b) {
			if constexpr (OP == VECTOR_BIT_OP_AND) {
				a = _mm_and_ps(a, b);
			} else if constexpr (OP == VECTOR_BIT_OP_OR) {
				a = _mm_or_ps(a, b);
			} else if constexpr (OP == VECTOR_BIT_OP_XOR) {
				a = _mm_xor_ps(a, b);
			}
		}

		template<uint64_t instruction_sets, NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute(type& a, const type& b) {
			if constexpr ((instruction_sets & ASM_SSE) != 0u) {
				Execute_SSE<OP>(a, b);
			} else {
				VectorBitOpC<OP, sizeof(type)>(&a, &b);
			}
		}
	};

	template<>
	struct VectorBitOp<__m128i> {
		typedef __m128i type;
		enum { optimised = 1 };
		enum : uint64_t { recommended_instruction_set = ASM_SSE2 };

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute_SSE2(type& a, const type& b) {
			if constexpr (OP == VECTOR_BIT_OP_AND) {
				a = _mm_and_si128(a);
			} else if constexpr (OP == VECTOR_BIT_OP_OR) {
				a = _mm_and_si128(a);
			} else if constexpr (OP == VECTOR_BIT_OP_XOR) {
				a = _mm_and_si128(a);
			}
		}

		template<uint64_t instruction_sets, NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute(type& a, const type& b) {
			if constexpr ((instruction_sets & ASM_SSE2) != 0u) {
				Execute_SSE2(a, b);
			} else {
				VectorBitOpC<OP, sizeof(type)>(&a, &b);
			}
		}
	};

	template<>
	struct VectorBitOp<__m128d> {
		typedef __m128d type;
		enum { optimised = 1 };
		enum : uint64_t { recommended_instruction_set = ASM_SSE2 };

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute_SSE2(type& a, const type& b) {
			if constexpr (OP == VECTOR_BIT_OP_AND) {
				a = _mm_and_pd(a);
			} else if constexpr (OP == VECTOR_BIT_OP_OR) {
				a = _mm_and_pd(a);
			} else if constexpr (OP == VECTOR_BIT_OP_XOR) {
				a = _mm_and_pd(a);
			}
		}

		template<uint64_t instruction_sets, NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute(type& a, const type& b) {
			if constexpr ((instruction_sets & ASM_SSE2) != 0u) {
				Execute_SSE2<OP>(a, b);
			} else {
				VectorBitOpC<OP, sizeof(type)>(&a, &b);
			}
		}
	};

	template<>
	struct VectorBitOp<__m256> {
		typedef __m256 type;
		enum { optimised = 1 };
		enum : uint64_t { recommended_instruction_set = ASM_AVX };

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute_SSE(void* a, const void* b) {
			__m128 xmm0 = _mm_loadu_ps(static_cast<float32_t*>(a));
			__m128 xmm1 = _mm_loadu_ps(static_cast<float32_t*>(a) + 4u);
			__m128 xmm2 = _mm_loadu_ps(static_cast<const float32_t*>(b));
			__m128 xmm3 = _mm_loadu_ps(static_cast<const float32_t*>(b) + 4u);
			if constexpr (OP == VECTOR_BIT_OP_AND) {
				xmm0 = _mm_and_ps(xmm0, xmm2);
				xmm1 = _mm_and_ps(xmm1, xmm3);
			} else if constexpr (OP == VECTOR_BIT_OP_OR) {
				xmm0 = _mm_or_ps(xmm0, xmm2);
				xmm1 = _mm_or_ps(xmm1, xmm3);
			} else if constexpr (OP == VECTOR_BIT_OP_XOR) {
				xmm0 = _mm_xor_ps(xmm0, xmm2);
				xmm1 = _mm_xor_ps(xmm1, xmm3);
			}

			_mm_storeu_ps(static_cast<float32_t*>(a), xmm0);
			_mm_storeu_ps(static_cast<float32_t*>(a) + 4u, xmm1);
		}

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute_AVX(type& a, const type& b) {
			if constexpr (OP == VECTOR_BIT_OP_AND) {
				a = _mm256_and_ps(a);
			} else if constexpr (OP == VECTOR_BIT_OP_OR) {
				a = _mm256_or_ps(a);
			} else if constexpr (OP == VECTOR_BIT_OP_XOR) {
				a = _mm256_xor_ps(a);
			}
		}

		template<uint64_t instruction_sets, NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute(type& a, const type& b) {
			if constexpr ((instruction_sets & ASM_AVX) != 0u) {
				Execute_AVX<OP>(a, b);
			} else if constexpr ((instruction_sets & ASM_SSE) != 0u) {
				Execute_SSE<OP>(&a, &b);
			} else {
				VectorBitOpC<OP, sizeof(type)>(&a, &b);
			}
		}
	};

	template<>
	struct VectorBitOp<__m256d> {
		typedef __m256d type;
		enum { optimised = 1 };
		enum : uint64_t { recommended_instruction_set = ASM_AVX };

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute_SSE2(void* a, const void* b) {
			__m128d xmm0 = _mm_loadu_pd(static_cast<float64_t*>(a));
			__m128d xmm1 = _mm_loadu_pd(static_cast<float64_t*>(a) + 2u);
			__m128d xmm2 = _mm_loadu_pd(static_cast<const float64_t*>(b));
			__m128d xmm3 = _mm_loadu_pd(static_cast<const float64_t*>(b) + 2u);
			if constexpr (OP == VECTOR_BIT_OP_AND) {
				xmm0 = _mm_and_pd(xmm0, xmm2);
				xmm1 = _mm_and_pd(xmm1, xmm3);
			} else if constexpr (OP == VECTOR_BIT_OP_OR) {
				xmm0 = _mm_or_pd(xmm0, xmm2);
				xmm1 = _mm_or_pd(xmm1, xmm3);
			} else if constexpr (OP == VECTOR_BIT_OP_XOR) {
				xmm0 = _mm_xor_pd(xmm0, xmm2);
				xmm1 = _mm_xor_pd(xmm1, xmm3);
			}

			_mm_storeu_pd(static_cast<float64_t*>(a), xmm0);
			_mm_storeu_pd(static_cast<float64_t*>(a) + 2u, xmm1);
		}

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute_AVX(type& a, const type& b) {
			if constexpr (OP == VECTOR_BIT_OP_AND) {
				a = _mm256_and_pd(a);
			} else if constexpr (OP == VECTOR_BIT_OP_OR) {
				a = _mm256_or_pd(a);
			} else if constexpr (OP == VECTOR_BIT_OP_XOR) {
				a = _mm256_xor_pd(a);
			}
		}

		template<uint64_t instruction_sets, NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute(type& a, const type& b) {
			if constexpr ((instruction_sets & ASM_AVX) != 0u) {
				Execute_AVX(a, b);
			} else if constexpr ((instruction_sets & ASM_SSE2) != 0u) {
				Execute_SSE2(&a, &b);
			} else {
				VectorBitOpC<OP, sizeof(type)>(&a, &b);
			}
		}
	};

	template<>
	struct VectorBitOp<__m256i> {
		typedef __m256i type;
		enum { optimised = 1 };
		enum : uint64_t { recommended_instruction_set = ASM_AVX };

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute_SSE2(void* a, const void* b) {
			__m128i xmm0 = _mm_loadu_si128(static_cast<__m128i*>(a));
			__m128i xmm1 = _mm_loadu_si128(static_cast<__m128i*>(a) + 1u);
			__m128i xmm2 = _mm_loadu_si128(static_cast<const __m128i*>(b));
			__m128i xmm3 = _mm_loadu_si128(static_cast<const __m128i*>(b) + 1u);
			if constexpr (OP == VECTOR_BIT_OP_AND) {
				xmm0 = _mm_and_si128(xmm0, xmm2);
				xmm1 = _mm_and_si128(xmm1, xmm3);
			} else if constexpr (OP == VECTOR_BIT_OP_OR) {
				xmm0 = _mm_or_si128(xmm0, xmm2);
				xmm1 = _mm_or_si128(xmm1, xmm3);
			} else if constexpr (OP == VECTOR_BIT_OP_XOR) {
				xmm0 = _mm_xor_si128(xmm0, xmm2);
				xmm1 = _mm_xor_si128(xmm1, xmm3);
			}

			_mm_storeu_pd(static_cast<__m128i*>(a), xmm0);
			_mm_storeu_pd(static_cast<__m128i*>(a) + 1u, xmm1);
		}

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute_AVX(type& a, const type& b) {
			if constexpr (OP == VECTOR_BIT_OP_AND) {
				a = _mm256_castps_si256(_mm256_and_si256(_mm256_castsi256_ps(a), _mm256_castsi256_ps(b)));
			} else if constexpr (OP == VECTOR_BIT_OP_OR) {
				a = _mm256_castps_si256(_mm256_or_si256(_mm256_castsi256_ps(a), _mm256_castsi256_ps(b)));
			} else if constexpr (OP == VECTOR_BIT_OP_XOR) {
				a = _mm256_castps_si256(_mm256_xor_si256(_mm256_castsi256_ps(a), _mm256_castsi256_ps(b)));
			}
		}

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute_AVX2(type& a, const type& b) {
			if constexpr (OP == VECTOR_BIT_OP_AND) {
				a = _mm256_and_si256(a, b);
			} else if constexpr (OP == VECTOR_BIT_OP_OR) {
				a = _mm256_or_si256(a, b);
			} else if constexpr (OP == VECTOR_BIT_OP_XOR) {
				a = _mm256_xor_si256(a, b);
			}
		}

		template<uint64_t instruction_sets, NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute(type& a, const type& b) {
			if constexpr ((instruction_sets & ASM_AVX2) != 0u) {
				Execute_AVX2<OP>(a, b);
			} else if constexpr ((instruction_sets & ASM_AVX) != 0u) {
				Execute_AVX<OP>(a, b);
			} else if constexpr ((instruction_sets & ASM_AVX) != 0u) {
				VectorBitOp<__m256>::Execute_AVX(reinterpret_cast<__m256&>(a), reinterpret_cast<const __m256&>(b));
			} else if constexpr ((instruction_sets & ASM_SSE2) != 0u) {
				Execute_SSE2<OP>(&a, &b);
			} else {
				VectorBitOpC<OP, sizeof(type)>(&a, &b);
			}
		}
	};

	template<>
	struct VectorBitOp<__m512> {
		typedef __m512 type;
		enum { optimised = 1 };
		enum : uint64_t { recommended_instruction_set = ASM_AVX512F };

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute_SSE(void* a, const void* b) {
			__m128 xmm0 = _mm_loadu_ps(static_cast<float32_t*>(a));
			__m128 xmm1 = _mm_loadu_ps(static_cast<float32_t*>(a) + 4u);
			__m128 xmm2 = _mm_loadu_ps(static_cast<float32_t*>(a) + 8u);
			__m128 xmm3 = _mm_loadu_ps(static_cast<float32_t*>(a) + 12u);
			__m128 xmm4 = _mm_loadu_ps(static_cast<const float32_t*>(b));
			__m128 xmm5 = _mm_loadu_ps(static_cast<const float32_t*>(b) + 4u);
			__m128 xmm6 = _mm_loadu_ps(static_cast<const float32_t*>(b) + 8u);
			__m128 xmm7 = _mm_loadu_ps(static_cast<const float32_t*>(b) + 12u);
			if constexpr (OP == VECTOR_BIT_OP_AND) {
				xmm0 = _mm_and_ps(xmm0, xmm4);
				xmm1 = _mm_and_ps(xmm1, xmm5);
				xmm2 = _mm_and_ps(xmm2, xmm6);
				xmm3 = _mm_and_ps(xmm3, xmm7);
			} else if constexpr (OP == VECTOR_BIT_OP_OR) {
				xmm0 = _mm_or_ps(xmm0, xmm4);
				xmm1 = _mm_or_ps(xmm1, xmm5);
				xmm2 = _mm_or_ps(xmm2, xmm6);
				xmm3 = _mm_or_ps(xmm3, xmm7);
			} else if constexpr (OP == VECTOR_BIT_OP_XOR) {
				xmm0 = _mm_xor_ps(xmm0, xmm4);
				xmm1 = _mm_xor_ps(xmm1, xmm5);
				xmm2 = _mm_xor_ps(xmm2, xmm6);
				xmm3 = _mm_xor_ps(xmm3, xmm7);
			}

			_mm_storeu_ps(static_cast<float32_t*>(a), xmm0);
			_mm_storeu_ps(static_cast<float32_t*>(a) + 4u, xmm1);
			_mm_storeu_ps(static_cast<float32_t*>(a) + 8u, xmm2);
			_mm_storeu_ps(static_cast<float32_t*>(a) + 1u, xmm3);
		}

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute_AVX(void* a, const void* b) {
			__m256 ymm0 = _mm256_loadu_ps(static_cast<float32_t*>(a));
			__m256 ymm1 = _mm256_loadu_ps(static_cast<float32_t*>(a) + 8u);
			__m256 ymm2 = _mm256_loadu_ps(static_cast<const float32_t*>(b));
			__m256 ymm3 = _mm256_loadu_ps(static_cast<const float32_t*>(b) + 8u);
			if constexpr (OP == VECTOR_BIT_OP_AND) {
				ymm0 = _mm_and_ps(ymm0, ymm2);
				ymm1 = _mm_and_ps(ymm1, ymm3);
			} else if constexpr (OP == VECTOR_BIT_OP_OR) {
				ymm0 = _mm256_or_ps(ymm0, ymm2);
				ymm1 = _mm256_or_ps(ymm1, ymm3);
			} else if constexpr (OP == VECTOR_BIT_OP_XOR) {
				ymm0 = _mm256_xor_ps(ymm0, ymm2);
				ymm1 = _mm256_xor_ps(ymm1, ymm3);
			}

			_mm256_storeu_ps(static_cast<float32_t*>(a), ymm0);
			_mm256_storeu_ps(static_cast<float32_t*>(a) + 8u, ymm1);
		}

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute_AVX512F(type& a, const type& b) {
			if constexpr (OP == VECTOR_BIT_OP_AND) {
				a = _mm512_and_ps(a, b);
			} else if constexpr (OP == VECTOR_BIT_OP_OR) {
				a = _mm512_or_ps(a, b);
			} else if constexpr (OP == VECTOR_BIT_OP_XOR) {
				a = _mm512_xor_ps(a, b);
			}
		}

		template<uint64_t instruction_sets, NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute(type& a, const type& b) {
			if constexpr ((instruction_sets & ASM_AVX512F) != 0u) {
				Execute_AVX512F<OP>(a, b);
			} else if constexpr ((instruction_sets & ASM_AVX) != 0u) {
				Execute_AVX<OP>(&a, &b);
			} else if constexpr ((instruction_sets & ASM_SSE) != 0u) {
				Execute_SSE<OP>(&a, &b);
			} else {
				VectorBitOpC<OP, sizeof(type)>(&a, &b);
			}
		}
	};

	template<>
	struct VectorBitOp<__m512d> {
		typedef __m512d type;
		enum { optimised = 1 };
		enum : uint64_t { recommended_instruction_set = ASM_AVX512F };

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute_SSE2(void* a, const void* b) {
			__m128d xmm0 = _mm_loadu_pd(static_cast<float64_t*>(a));
			__m128d xmm1 = _mm_loadu_pd(static_cast<float64_t*>(a) + 2u);
			__m128d xmm2 = _mm_loadu_pd(static_cast<float64_t*>(a) + 4u);
			__m128d xmm3 = _mm_loadu_pd(static_cast<float64_t*>(a) + 6u);
			__m128d xmm4 = _mm_loadu_pd(static_cast<const float64_t*>(b));
			__m128d xmm5 = _mm_loadu_pd(static_cast<const float64_t*>(b) + 2u);
			__m128d xmm6 = _mm_loadu_pd(static_cast<const float64_t*>(b) + 4u);
			__m128d xmm7 = _mm_loadu_pd(static_cast<const float64_t*>(b) + 6u);
			if constexpr (OP == VECTOR_BIT_OP_AND) {
				xmm0 = _mm_and_pd(xmm0, xmm4);
				xmm1 = _mm_and_pd(xmm1, xmm5);
				xmm2 = _mm_and_pd(xmm2, xmm6);
				xmm3 = _mm_and_pd(xmm3, xmm7);
			} else if constexpr (OP == VECTOR_BIT_OP_OR) {
				xmm0 = _mm_or_pd(xmm0, xmm4);
				xmm1 = _mm_or_pd(xmm1, xmm5);
				xmm2 = _mm_or_pd(xmm2, xmm6);
				xmm3 = _mm_or_pd(xmm3, xmm7);
			} else if constexpr (OP == VECTOR_BIT_OP_XOR) {
				xmm0 = _mm_xor_pd(xmm0, xmm4);
				xmm1 = _mm_xor_pd(xmm1, xmm5);
				xmm2 = _mm_xor_pd(xmm2, xmm6);
				xmm3 = _mm_xor_pd(xmm3, xmm7);
			}

			_mm_storeu_pd(static_cast<float32_t*>(a), xmm0);
			_mm_storeu_pd(static_cast<float32_t*>(a) + 2u, xmm1);
			_mm_storeu_pd(static_cast<float32_t*>(a) + 4u, xmm2);
			_mm_storeu_pd(static_cast<float32_t*>(a) + 6u, xmm3);
		}

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute_AVX(void* a, const void* b) {
			__m256d ymm0 = _mm256_loadu_pd(static_cast<float64_t*>(a));
			__m256d ymm1 = _mm256_loadu_pd(static_cast<float64_t*>(a) + 4u);
			__m256d ymm2 = _mm256_loadu_pd(static_cast<const float64_t*>(b));
			__m256d ymm3 = _mm256_loadu_pd(static_cast<const float64_t*>(b) + 4u);
			if constexpr (OP == VECTOR_BIT_OP_AND) {
				ymm0 = _mm_and_pd(ymm0, ymm2);
				ymm1 = _mm_and_pd(ymm1, ymm3);
			} else if constexpr (OP == VECTOR_BIT_OP_OR) {
				ymm0 = _mm256_or_pd(ymm0, ymm2);
				ymm1 = _mm256_or_pd(ymm1, ymm3);
			} else if constexpr (OP == VECTOR_BIT_OP_XOR) {
				ymm0 = _mm256_xor_pd(ymm0, ymm2);
				ymm1 = _mm256_xor_pd(ymm1, ymm3);
			}

			_mm256_storeu_ps(static_cast<float64_t*>(a), ymm0);
			_mm256_storeu_ps(static_cast<float64_t*>(a) + 4u, ymm1);
		}

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute_AVX512F(type& a, const type& b) {
			if constexpr (OP == VECTOR_BIT_OP_AND) {
				a = _mm512_and_pd(a, b);
			} else if constexpr (OP == VECTOR_BIT_OP_OR) {
				a = _mm512_or_pd(a, b);
			} else if constexpr (OP == VECTOR_BIT_OP_XOR) {
				a = _mm512_xor_pd(a, b);
			}
		}

		template<uint64_t instruction_sets, NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute(type& a, const type& b) {
			if constexpr ((instruction_sets & ASM_AVX512F) != 0u) {
				Execute_AVX512F<OP>(a, b);
			} else if constexpr ((instruction_sets & ASM_AVX) != 0u) {
				Execute_AVX<OP>(&a, &b);
			} else if constexpr ((instruction_sets & ASM_SSE2) != 0u) {
				Execute_SSE2<OP>(&a, &b);
			} else {
				VectorBitOpC<OP, sizeof(type)>(&a, &b);
			}
		}
	};

	template<>
	struct VectorBitOp<__m512i> {
		typedef __m512i type;
		enum { optimised = 1 };
		enum : uint64_t { recommended_instruction_set = ASM_AVX512F };

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute_SSE2(void* a, const void* b) {
			__m128i xmm0 = _mm_loadu_si128(static_cast<__m128i*>(a));
			__m128i xmm1 = _mm_loadu_si128(static_cast<__m128i*>(a) + 1u);
			__m128i xmm2 = _mm_loadu_si128(static_cast<__m128i*>(a) + 2u);
			__m128i xmm3 = _mm_loadu_si128(static_cast<__m128i*>(a) + 3u);
			__m128i xmm4 = _mm_loadu_si128(static_cast<const __m128i*>(b));
			__m128i xmm5 = _mm_loadu_si128(static_cast<const __m128i*>(b) + 1u);
			__m128i xmm6 = _mm_loadu_si128(static_cast<const __m128i*>(b) + 2u);
			__m128i xmm7 = _mm_loadu_si128(static_cast<const __m128i*>(b) + 3u);
			if constexpr (OP == VECTOR_BIT_OP_AND) {
				xmm0 = _mm_and_si128(xmm0, xmm4);
				xmm1 = _mm_and_si128(xmm1, xmm5);
				xmm2 = _mm_and_si128(xmm2, xmm6);
				xmm3 = _mm_and_si128(xmm3, xmm7);
			} else if constexpr (OP == VECTOR_BIT_OP_OR) {
				xmm0 = _mm_or_si128(xmm0, xmm4);
				xmm1 = _mm_or_si128(xmm1, xmm5);
				xmm2 = _mm_or_si128(xmm2, xmm6);
				xmm3 = _mm_or_si128(xmm3, xmm7);
			} else if constexpr (OP == VECTOR_BIT_OP_XOR) {
				xmm0 = _mm_xor_si128(xmm0, xmm4);
				xmm1 = _mm_xor_si128(xmm1, xmm5);
				xmm2 = _mm_xor_si128(xmm2, xmm6);
				xmm3 = _mm_xor_si128(xmm3, xmm7);
			}

			_mm_storeu_si128(static_cast<__m128i*>(a), xmm0);
			_mm_storeu_si128(static_cast<__m128i*>(a) + 1u, xmm1);
			_mm_storeu_si128(static_cast<__m128i*>(a) + 2u, xmm2);
			_mm_storeu_si128(static_cast<__m128i*>(a) + 3u, xmm3);
		}

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute_AVX2(void* a, const void* b) {
			__m256i ymm0 = _mm256_loadu_si256(static_cast<__m256i*>(a));
			__m256i ymm1 = _mm256_loadu_si256(static_cast<__m256i*>(a) + 1u);
			__m256i ymm2 = _mm256_loadu_si256(static_cast<const __m256i*>(b));
			__m256i ymm3 = _mm256_loadu_si256(static_cast<const __m256i*>(b) + 1u);
			if constexpr (OP == VECTOR_BIT_OP_AND) {
				ymm0 = _mm_and_si256(ymm0, ymm2);
				ymm1 = _mm_and_si256(ymm1, ymm3);
			} else if constexpr (OP == VECTOR_BIT_OP_OR) {
				ymm0 = _mm256_or_si256(ymm0, ymm2);
				ymm1 = _mm256_or_si256(ymm1, ymm3);
			} else if constexpr (OP == VECTOR_BIT_OP_XOR) {
				ymm0 = _mm256_xor_si256(ymm0, ymm2);
				ymm1 = _mm256_xor_si256(ymm1, ymm3);
			}

			_mm256_storeu_si256(static_cast<__m256i*>(a), ymm0);
			_mm256_storeu_si256(static_cast<__m256i*>(a) + 1u, ymm1);
		}

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute_AVX512BW(type& a, const type& b) {
			if constexpr (OP == VECTOR_BIT_OP_AND) {
				a = _mm512_and_si512(a, b);
			} else if constexpr (OP == VECTOR_BIT_OP_OR) {
				a = _mm512_or_si512(a, b);
			} else if constexpr (OP == VECTOR_BIT_OP_XOR) {
				a = _mm512_xor_si512(a, b);
			}
		}

		template<uint64_t instruction_sets, NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute(type& a, const type& b) {
			if constexpr ((instruction_sets & ASM_AVX512BW) != 0u) {
				Execute_AVX512BW<OP>(a, b);
			} else if constexpr ((instruction_sets & ASM_AVX512F) != 0u) {
				VectorBitOp<__m512>::Execute_AVX512F<OP>(reinterpret_cast<__m512&>(a), reinterpret_cast<const __m512&>(b));
			} else if constexpr ((instruction_sets & ASM_AVX2) != 0u) {
				Execute_AVX2<OP>(&a, &b);
			} else if constexpr ((instruction_sets & ASM_AVX) != 0u) {
				VectorBitOp<__m512>::Execute_AVX<OP>(&a, &b);
			} else if constexpr ((instruction_sets & ASM_SSE2) != 0u) {
				Execute_SSE2<OP>(&a, &b);
			} else {
				VectorBitOpC<OP, sizeof(type)>(&a, &b);
			}
		}
	};
#endif

	template<class T>
	struct VectorAnd {
		typedef T type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, const type& b) throw() {
			VectorBitOp<type>::Execute<instruction_set, VECTOR_BIT_OP_AND>(a, b);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type ExecuteRuntimeMask(type a, const type& b, const type& src, const uint64_t mask) throw() {
			return anvil::VectorBlendRuntimeMask<instruction_set>(Execute<instruction_set>(a, b), src, mask);
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type ExecuteRuntimeMask(type a, const type& b, const type& src, const Bitfield128 mask) throw() {
			return ExecuteRuntimeMask<instruction_set>(a, b, src, mask.low);
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type ExecuteRuntimeMask(type a, const type& b, const type& src, const Bitfield256 mask) throw() {
			return ExecuteRuntimeMask<instruction_set>(a, b, src, mask.low);
		}

		template<uint64_t mask, uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type ExecuteCompiletimeMask(type a, const type& b, const type& src) throw() {
			return anvil::VectorBlendRuntimeMask<mask, instruction_set>(Execute<instruction_set>(a, b), src);
		}
	};

	template<class T, size_t size>
	struct VectorAnd<detail::BasicVector<T, size>> {
		typedef detail::BasicVector<T, size> type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, const type& b) throw() {
			if constexpr (VectorBitOp<type::native_t>::optimised) {
				VectorBitOp<type::native_t>::Execute<instruction_set, VECTOR_BIT_OP_AND>(a.native, b.native);
			} else {
				a.lower_half = VectorAnd<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorAnd<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
			}

			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type ExecuteRuntimeMask(type a, const type& b, const type& src, const uint64_t mask) throw() {
			if constexpr (VectorBitOp<type::native_t>::optimised && (instruction_set & VectorBitOp<type::native_t>::recommended_instruction_set) != 0ull) {
				return anvil::VectorBlendRuntimeMask<instruction_set>(Execute<instruction_set>(a, b), src, mask);
			} else {
				a.lower_half = VectorAnd<type::lower_t>::ExecuteRuntimeMask<instruction_set>(a.lower_half, b.lower_half, src.lower_half, mask);
				a.upper_half = VectorAnd<type::upper_t>::ExecuteRuntimeMask<instruction_set>(a.upper_half, b.upper_half, src.upper_half, mask >> type::lower_size);
				return a;
			}
		}

		template<uint64_t mask, uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type ExecuteCompiletimeMask(type a, const type& b, const type& src) throw() {
			if constexpr (VectorBitOp<type::native_t>::optimised && (instruction_set & VectorBitOp<type::native_t>::recommended_instruction_set) != 0ull) {
				return anvil::VectorBlendCompiletimeMask<mask, instruction_set>(Execute<instruction_set>(a, b), src);
			} else {
				enum : uint64_t { mask1 = mask >> type::lower_size };
				a.lower_half = VectorAnd<type::lower_t>::ExecuteCompiletimeMask<mask, instruction_set>(a.lower_half, b.lower_half, src.lower_half);
				a.upper_half = VectorAnd<type::upper_t>::ExecuteCompiletimeMask<mask1, instruction_set>(a.upper_half, b.upper_half, src.upper_half);
				return a;
			}
		}
	};
}}

namespace anvil {

	template<uint64_t instruction_set = ASM_MINIMUM, class T>
	static inline T VectorAnd(const T& a, const T& b) throw() {
		return detail::VectorAnd<T>::Execute<instruction_set>(a, b);
	}

	// Run-time blend mask
	template<uint64_t instruction_set = ASM_MINIMUM, class T>
	static inline T VectorAnd(const T& a, const T& b, const T& src, const uint64_t mask) throw() {
		return detail::VectorAnd<T>::ExecuteRuntimeMask<instruction_set>(a, b, src, mask);
	}

	// Compile-time blend mask
	template<uint64_t mask, uint64_t instruction_set = ASM_MINIMUM, class T>
	static inline T VectorAnd(const T& a, const T& b, const T& src) throw() {
		return detail::VectorAnd<T>::ExecuteCompiletimeMask<mask, instruction_set>(a, b, src);
	}
}


template<class T, size_t size>
ANVIL_STRONG_INLINE anvil::detail::BasicVector<T, size> operator&(const anvil::detail::BasicVector<T, size>& a, const anvil::detail::BasicVector<T, size>& b) throw() {
	return anvil::VectorAnd<anvil::ASM_MINIMUM, anvil::detail::BasicVector<T, size>>(a, b);
}

#endif

//// -- f64 --
//
//#ifndef _simd_f64x1_and_safe
//	#define _simd_f64x1_and_safe(X,Y) X
//	#define _simd_f64x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_f64x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_and_enabled() true
//#endif
//
//#define _simd_f64x2_and_safe(X,Y)_simd_f64x2_combine_safe(\
//	_simd_f64x1_and_safe(_simd_f64x2_splitlo_safe(X), _simd_ f64x2_splitlo_safe(Y)),\
//	_simd_f64x1_and_safe(_simd_f64x2_splithi_safe(X), _simd_ f64x2_splithi_safe(Y)))
//#ifdef _simd_f64x2_and_
//	#define _simd_f64x2_and(X,Y) _simd_f64x2_and_(X, Y)
//	#define _simd_f64x2_and_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_and_instruction_set>()
//#elif defined(_simd_f64x4_and_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_and(const register _simd_f64x2 x, const register _simd_f64x2 y) {
//		union SIMDUnion { _simd_f64x2 v1; _simd_f64x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x4_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x2_and_enable() _simd_f64x4_and_enable()
//#elif defined(_simd_f64x8_and_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_and(const register _simd_f64x2 x, const register _simd_f64x2 y) {
//		union SIMDUnion { _simd_f64x2 v1; _simd_f64x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x8_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x2_and_enable() _simd_f64x8_and_enable()
//#elif defined(_simd_f64x16_and_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_and(const register _simd_f64x2 x, const register _simd_f64x2 y) {
//		union SIMDUnion { _simd_f64x2 v1; _simd_f64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x16_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x2_and_enable() _simd_f64x16_and_enable()
//#elif defined(_simd_f64x32_and_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_and(const register _simd_f64x2 x, const register _simd_f64x2 y) {
//		union SIMDUnion { _simd_f64x2 v1; _simd_f64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x2_and_enable() _simd_f64x32_and_enable()
//#elif defined(_simd_f64x64_and_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_and(const register _simd_f64x2 x, const register _simd_f64x2 y) {
//		union SIMDUnion { _simd_f64x2 v1; _simd_f64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x2_and_enable() _simd_f64x64_and_enable()
//#else
//	#define _simd_f64x2_and(X,Y) _simd_f64x2_combine(\
//		_simd_f64x1_and(_simd_f64x2_splitlo(X), _simd_f64x2_splitlo(Y)),\
//		_simd_f64x1_and(_simd_f64x2_splithi(X), _simd_f64x2_splithi(Y)))
//	#define _simd_f64x2_and_enable() (_simd_f64x1_and_enable() && _simd_f64x2_combine_enable() && _simd_f64x2_splitlo_enable()  && _simd_f64x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x2_and_) && ! defined(_simd_f64x2_and_scalar_)
//	#define _simd_f64x2_and_scalar_(X,Y) _simd_f64x2_and_(X,_simd_f64x2_fill_scalar_(Y))
//	#define _simd_f64x2_and_scalar_instruction_set _simd_f64x2_and_instruction_set
//#endif
//#ifdef _simd_f64x2_and_scalar_
//	#define _simd_f64x2_and_scalar(X,Y) _simd_f64x2_and_scalar_(X,Y)
//	#define _simd_f64x2_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_and_scalar_instruction_set>()
//#else
//	#define _simd_f64x2_and_scalar(X,Y) _simd_f64x2_and_safe(X,_simd_f64x2_fill_scalar_safe(Y))
//	#define _simd_f64x2_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_f64x1_and_safe
//	#define _simd_f64x1_and_safe(X,Y) X
//	#define _simd_f64x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_f64x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_and_enabled() true
//#endif
//
//#define _simd_f64x4_and_safe(X,Y)_simd_f64x4_combine_safe(\
//	_simd_f64x2_and_safe(_simd_f64x4_splitlo_safe(X), _simd_ f64x4_splitlo_safe(Y)),\
//	_simd_f64x2_and_safe(_simd_f64x4_splithi_safe(X), _simd_ f64x4_splithi_safe(Y)))
//#ifdef _simd_f64x4_and_
//	#define _simd_f64x4_and(X,Y) _simd_f64x4_and_(X, Y)
//	#define _simd_f64x4_and_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_and_instruction_set>()
//#elif defined(_simd_f64x8_and_)
//	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_and(const register _simd_f64x4 x, const register _simd_f64x4 y) {
//		union SIMDUnion { _simd_f64x4 v1; _simd_f64x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x8_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x4_and_enable() _simd_f64x8_and_enable()
//#elif defined(_simd_f64x16_and_)
//	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_and(const register _simd_f64x4 x, const register _simd_f64x4 y) {
//		union SIMDUnion { _simd_f64x4 v1; _simd_f64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x16_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x4_and_enable() _simd_f64x16_and_enable()
//#elif defined(_simd_f64x32_and_)
//	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_and(const register _simd_f64x4 x, const register _simd_f64x4 y) {
//		union SIMDUnion { _simd_f64x4 v1; _simd_f64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x4_and_enable() _simd_f64x32_and_enable()
//#elif defined(_simd_f64x64_and_)
//	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_and(const register _simd_f64x4 x, const register _simd_f64x4 y) {
//		union SIMDUnion { _simd_f64x4 v1; _simd_f64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x4_and_enable() _simd_f64x64_and_enable()
//#else
//	#define _simd_f64x4_and(X,Y) _simd_f64x4_combine(\
//		_simd_f64x2_and(_simd_f64x4_splitlo(X), _simd_f64x4_splitlo(Y)),\
//		_simd_f64x2_and(_simd_f64x4_splithi(X), _simd_f64x4_splithi(Y)))
//	#define _simd_f64x4_and_enable() (_simd_f64x2_and_enable() && _simd_f64x4_combine_enable() && _simd_f64x4_splitlo_enable()  && _simd_f64x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x4_and_) && ! defined(_simd_f64x4_and_scalar_)
//	#define _simd_f64x4_and_scalar_(X,Y) _simd_f64x4_and_(X,_simd_f64x4_fill_scalar_(Y))
//	#define _simd_f64x4_and_scalar_instruction_set _simd_f64x4_and_instruction_set
//#endif
//#ifdef _simd_f64x4_and_scalar_
//	#define _simd_f64x4_and_scalar(X,Y) _simd_f64x4_and_scalar_(X,Y)
//	#define _simd_f64x4_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_and_scalar_instruction_set>()
//#else
//	#define _simd_f64x4_and_scalar(X,Y) _simd_f64x4_and_safe(X,_simd_f64x4_fill_scalar_safe(Y))
//	#define _simd_f64x4_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_f64x1_and_safe
//	#define _simd_f64x1_and_safe(X,Y) X
//	#define _simd_f64x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_f64x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_and_enabled() true
//#endif
//
//#define _simd_f64x8_and_safe(X,Y)_simd_f64x8_combine_safe(\
//	_simd_f64x4_and_safe(_simd_f64x8_splitlo_safe(X), _simd_ f64x8_splitlo_safe(Y)),\
//	_simd_f64x4_and_safe(_simd_f64x8_splithi_safe(X), _simd_ f64x8_splithi_safe(Y)))
//#ifdef _simd_f64x8_and_
//	#define _simd_f64x8_and(X,Y) _simd_f64x8_and_(X, Y)
//	#define _simd_f64x8_and_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_and_instruction_set>()
//#elif defined(_simd_f64x16_and_)
//	static ANVIL_STRONG_INLINE _simd_f64x8 ANVIL_SIMD_CALL _simd_f64x8_and(const register _simd_f64x8 x, const register _simd_f64x8 y) {
//		union SIMDUnion { _simd_f64x8 v1; _simd_f64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x16_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x8_and_enable() _simd_f64x16_and_enable()
//#elif defined(_simd_f64x32_and_)
//	static ANVIL_STRONG_INLINE _simd_f64x8 ANVIL_SIMD_CALL _simd_f64x8_and(const register _simd_f64x8 x, const register _simd_f64x8 y) {
//		union SIMDUnion { _simd_f64x8 v1; _simd_f64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x8_and_enable() _simd_f64x32_and_enable()
//#elif defined(_simd_f64x64_and_)
//	static ANVIL_STRONG_INLINE _simd_f64x8 ANVIL_SIMD_CALL _simd_f64x8_and(const register _simd_f64x8 x, const register _simd_f64x8 y) {
//		union SIMDUnion { _simd_f64x8 v1; _simd_f64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x8_and_enable() _simd_f64x64_and_enable()
//#else
//	#define _simd_f64x8_and(X,Y) _simd_f64x8_combine(\
//		_simd_f64x4_and(_simd_f64x8_splitlo(X), _simd_f64x8_splitlo(Y)),\
//		_simd_f64x4_and(_simd_f64x8_splithi(X), _simd_f64x8_splithi(Y)))
//	#define _simd_f64x8_and_enable() (_simd_f64x4_and_enable() && _simd_f64x8_combine_enable() && _simd_f64x8_splitlo_enable()  && _simd_f64x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x8_and_) && ! defined(_simd_f64x8_and_scalar_)
//	#define _simd_f64x8_and_scalar_(X,Y) _simd_f64x8_and_(X,_simd_f64x8_fill_scalar_(Y))
//	#define _simd_f64x8_and_scalar_instruction_set _simd_f64x8_and_instruction_set
//#endif
//#ifdef _simd_f64x8_and_scalar_
//	#define _simd_f64x8_and_scalar(X,Y) _simd_f64x8_and_scalar_(X,Y)
//	#define _simd_f64x8_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_and_scalar_instruction_set>()
//#else
//	#define _simd_f64x8_and_scalar(X,Y) _simd_f64x8_and_safe(X,_simd_f64x8_fill_scalar_safe(Y))
//	#define _simd_f64x8_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_f64x1_and_safe
//	#define _simd_f64x1_and_safe(X,Y) X
//	#define _simd_f64x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_f64x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_and_enabled() true
//#endif
//
//#define _simd_f64x16_and_safe(X,Y)_simd_f64x16_combine_safe(\
//	_simd_f64x8_and_safe(_simd_f64x16_splitlo_safe(X), _simd_ f64x16_splitlo_safe(Y)),\
//	_simd_f64x8_and_safe(_simd_f64x16_splithi_safe(X), _simd_ f64x16_splithi_safe(Y)))
//#ifdef _simd_f64x16_and_
//	#define _simd_f64x16_and(X,Y) _simd_f64x16_and_(X, Y)
//	#define _simd_f64x16_and_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_and_instruction_set>()
//#elif defined(_simd_f64x32_and_)
//	static ANVIL_STRONG_INLINE _simd_f64x16 ANVIL_SIMD_CALL _simd_f64x16_and(const register _simd_f64x16 x, const register _simd_f64x16 y) {
//		union SIMDUnion { _simd_f64x16 v1; _simd_f64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x16_and_enable() _simd_f64x32_and_enable()
//#elif defined(_simd_f64x64_and_)
//	static ANVIL_STRONG_INLINE _simd_f64x16 ANVIL_SIMD_CALL _simd_f64x16_and(const register _simd_f64x16 x, const register _simd_f64x16 y) {
//		union SIMDUnion { _simd_f64x16 v1; _simd_f64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x16_and_enable() _simd_f64x64_and_enable()
//#else
//	#define _simd_f64x16_and(X,Y) _simd_f64x16_combine(\
//		_simd_f64x8_and(_simd_f64x16_splitlo(X), _simd_f64x16_splitlo(Y)),\
//		_simd_f64x8_and(_simd_f64x16_splithi(X), _simd_f64x16_splithi(Y)))
//	#define _simd_f64x16_and_enable() (_simd_f64x8_and_enable() && _simd_f64x16_combine_enable() && _simd_f64x16_splitlo_enable()  && _simd_f64x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x16_and_) && ! defined(_simd_f64x16_and_scalar_)
//	#define _simd_f64x16_and_scalar_(X,Y) _simd_f64x16_and_(X,_simd_f64x16_fill_scalar_(Y))
//	#define _simd_f64x16_and_scalar_instruction_set _simd_f64x16_and_instruction_set
//#endif
//#ifdef _simd_f64x16_and_scalar_
//	#define _simd_f64x16_and_scalar(X,Y) _simd_f64x16_and_scalar_(X,Y)
//	#define _simd_f64x16_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_and_scalar_instruction_set>()
//#else
//	#define _simd_f64x16_and_scalar(X,Y) _simd_f64x16_and_safe(X,_simd_f64x16_fill_scalar_safe(Y))
//	#define _simd_f64x16_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_f64x1_and_safe
//	#define _simd_f64x1_and_safe(X,Y) X
//	#define _simd_f64x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_f64x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_and_enabled() true
//#endif
//
//#define _simd_f64x32_and_safe(X,Y)_simd_f64x32_combine_safe(\
//	_simd_f64x16_and_safe(_simd_f64x32_splitlo_safe(X), _simd_ f64x32_splitlo_safe(Y)),\
//	_simd_f64x16_and_safe(_simd_f64x32_splithi_safe(X), _simd_ f64x32_splithi_safe(Y)))
//#ifdef _simd_f64x32_and_
//	#define _simd_f64x32_and(X,Y) _simd_f64x32_and_(X, Y)
//	#define _simd_f64x32_and_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_and_instruction_set>()
//#elif defined(_simd_f64x64_and_)
//	static ANVIL_STRONG_INLINE _simd_f64x32 ANVIL_SIMD_CALL _simd_f64x32_and(const register _simd_f64x32 x, const register _simd_f64x32 y) {
//		union SIMDUnion { _simd_f64x32 v1; _simd_f64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x32_and_enable() _simd_f64x64_and_enable()
//#else
//	#define _simd_f64x32_and(X,Y) _simd_f64x32_combine(\
//		_simd_f64x16_and(_simd_f64x32_splitlo(X), _simd_f64x32_splitlo(Y)),\
//		_simd_f64x16_and(_simd_f64x32_splithi(X), _simd_f64x32_splithi(Y)))
//	#define _simd_f64x32_and_enable() (_simd_f64x16_and_enable() && _simd_f64x32_combine_enable() && _simd_f64x32_splitlo_enable()  && _simd_f64x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x32_and_) && ! defined(_simd_f64x32_and_scalar_)
//	#define _simd_f64x32_and_scalar_(X,Y) _simd_f64x32_and_(X,_simd_f64x32_fill_scalar_(Y))
//	#define _simd_f64x32_and_scalar_instruction_set _simd_f64x32_and_instruction_set
//#endif
//#ifdef _simd_f64x32_and_scalar_
//	#define _simd_f64x32_and_scalar(X,Y) _simd_f64x32_and_scalar_(X,Y)
//	#define _simd_f64x32_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_and_scalar_instruction_set>()
//#else
//	#define _simd_f64x32_and_scalar(X,Y) _simd_f64x32_and_safe(X,_simd_f64x32_fill_scalar_safe(Y))
//	#define _simd_f64x32_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_f64x1_and_safe
//	#define _simd_f64x1_and_safe(X,Y) X
//	#define _simd_f64x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_f64x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_and_enabled() true
//#endif
//
//#define _simd_f64x64_and_safe(X,Y)_simd_f64x64_combine_safe(\
//	_simd_f64x32_and_safe(_simd_f64x64_splitlo_safe(X), _simd_ f64x64_splitlo_safe(Y)),\
//	_simd_f64x32_and_safe(_simd_f64x64_splithi_safe(X), _simd_ f64x64_splithi_safe(Y)))
//#ifdef _simd_f64x64_and_
//	#define _simd_f64x64_and(X,Y) _simd_f64x64_and_(X, Y)
//	#define _simd_f64x64_and_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_and_instruction_set>()
//#else
//	#define _simd_f64x64_and(X,Y) _simd_f64x64_combine(\
//		_simd_f64x32_and(_simd_f64x64_splitlo(X), _simd_f64x64_splitlo(Y)),\
//		_simd_f64x32_and(_simd_f64x64_splithi(X), _simd_f64x64_splithi(Y)))
//	#define _simd_f64x64_and_enable() (_simd_f64x32_and_enable() && _simd_f64x64_combine_enable() && _simd_f64x64_splitlo_enable()  && _simd_f64x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x64_and_) && ! defined(_simd_f64x64_and_scalar_)
//	#define _simd_f64x64_and_scalar_(X,Y) _simd_f64x64_and_(X,_simd_f64x64_fill_scalar_(Y))
//	#define _simd_f64x64_and_scalar_instruction_set _simd_f64x64_and_instruction_set
//#endif
//#ifdef _simd_f64x64_and_scalar_
//	#define _simd_f64x64_and_scalar(X,Y) _simd_f64x64_and_scalar_(X,Y)
//	#define _simd_f64x64_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_and_scalar_instruction_set>()
//#else
//	#define _simd_f64x64_and_scalar(X,Y) _simd_f64x64_and_safe(X,_simd_f64x64_fill_scalar_safe(Y))
//	#define _simd_f64x64_and_scalar_enabled() true
//#endif
//
//// -- f32 --
//
//#ifndef _simd_f32x1_and_safe
//	#define _simd_f32x1_and_safe(X,Y) X
//	#define _simd_f32x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_f32x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_and_enabled() true
//#endif
//
//#define _simd_f32x2_and_safe(X,Y)_simd_f32x2_combine_safe(\
//	_simd_f32x1_and_safe(_simd_f32x2_splitlo_safe(X), _simd_ f32x2_splitlo_safe(Y)),\
//	_simd_f32x1_and_safe(_simd_f32x2_splithi_safe(X), _simd_ f32x2_splithi_safe(Y)))
//#ifdef _simd_f32x2_and_
//	#define _simd_f32x2_and(X,Y) _simd_f32x2_and_(X, Y)
//	#define _simd_f32x2_and_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_and_instruction_set>()
//#elif defined(_simd_f32x4_and_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_and(const register _simd_f32x2 x, const register _simd_f32x2 y) {
//		union SIMDUnion { _simd_f32x2 v1; _simd_f32x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x4_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x2_and_enable() _simd_f32x4_and_enable()
//#elif defined(_simd_f32x8_and_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_and(const register _simd_f32x2 x, const register _simd_f32x2 y) {
//		union SIMDUnion { _simd_f32x2 v1; _simd_f32x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x8_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x2_and_enable() _simd_f32x8_and_enable()
//#elif defined(_simd_f32x16_and_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_and(const register _simd_f32x2 x, const register _simd_f32x2 y) {
//		union SIMDUnion { _simd_f32x2 v1; _simd_f32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x16_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x2_and_enable() _simd_f32x16_and_enable()
//#elif defined(_simd_f32x32_and_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_and(const register _simd_f32x2 x, const register _simd_f32x2 y) {
//		union SIMDUnion { _simd_f32x2 v1; _simd_f32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x2_and_enable() _simd_f32x32_and_enable()
//#elif defined(_simd_f32x64_and_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_and(const register _simd_f32x2 x, const register _simd_f32x2 y) {
//		union SIMDUnion { _simd_f32x2 v1; _simd_f32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x2_and_enable() _simd_f32x64_and_enable()
//#else
//	#define _simd_f32x2_and(X,Y) _simd_f32x2_combine(\
//		_simd_f32x1_and(_simd_f32x2_splitlo(X), _simd_f32x2_splitlo(Y)),\
//		_simd_f32x1_and(_simd_f32x2_splithi(X), _simd_f32x2_splithi(Y)))
//	#define _simd_f32x2_and_enable() (_simd_f32x1_and_enable() && _simd_f32x2_combine_enable() && _simd_f32x2_splitlo_enable()  && _simd_f32x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x2_and_) && ! defined(_simd_f32x2_and_scalar_)
//	#define _simd_f32x2_and_scalar_(X,Y) _simd_f32x2_and_(X,_simd_f32x2_fill_scalar_(Y))
//	#define _simd_f32x2_and_scalar_instruction_set _simd_f32x2_and_instruction_set
//#endif
//#ifdef _simd_f32x2_and_scalar_
//	#define _simd_f32x2_and_scalar(X,Y) _simd_f32x2_and_scalar_(X,Y)
//	#define _simd_f32x2_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_and_scalar_instruction_set>()
//#else
//	#define _simd_f32x2_and_scalar(X,Y) _simd_f32x2_and_safe(X,_simd_f32x2_fill_scalar_safe(Y))
//	#define _simd_f32x2_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_f32x1_and_safe
//	#define _simd_f32x1_and_safe(X,Y) X
//	#define _simd_f32x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_f32x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_and_enabled() true
//#endif
//
//#define _simd_f32x4_and_safe(X,Y)_simd_f32x4_combine_safe(\
//	_simd_f32x2_and_safe(_simd_f32x4_splitlo_safe(X), _simd_ f32x4_splitlo_safe(Y)),\
//	_simd_f32x2_and_safe(_simd_f32x4_splithi_safe(X), _simd_ f32x4_splithi_safe(Y)))
//#ifdef _simd_f32x4_and_
//	#define _simd_f32x4_and(X,Y) _simd_f32x4_and_(X, Y)
//	#define _simd_f32x4_and_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_and_instruction_set>()
//#elif defined(_simd_f32x8_and_)
//	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_and(const register _simd_f32x4 x, const register _simd_f32x4 y) {
//		union SIMDUnion { _simd_f32x4 v1; _simd_f32x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x8_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x4_and_enable() _simd_f32x8_and_enable()
//#elif defined(_simd_f32x16_and_)
//	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_and(const register _simd_f32x4 x, const register _simd_f32x4 y) {
//		union SIMDUnion { _simd_f32x4 v1; _simd_f32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x16_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x4_and_enable() _simd_f32x16_and_enable()
//#elif defined(_simd_f32x32_and_)
//	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_and(const register _simd_f32x4 x, const register _simd_f32x4 y) {
//		union SIMDUnion { _simd_f32x4 v1; _simd_f32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x4_and_enable() _simd_f32x32_and_enable()
//#elif defined(_simd_f32x64_and_)
//	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_and(const register _simd_f32x4 x, const register _simd_f32x4 y) {
//		union SIMDUnion { _simd_f32x4 v1; _simd_f32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x4_and_enable() _simd_f32x64_and_enable()
//#else
//	#define _simd_f32x4_and(X,Y) _simd_f32x4_combine(\
//		_simd_f32x2_and(_simd_f32x4_splitlo(X), _simd_f32x4_splitlo(Y)),\
//		_simd_f32x2_and(_simd_f32x4_splithi(X), _simd_f32x4_splithi(Y)))
//	#define _simd_f32x4_and_enable() (_simd_f32x2_and_enable() && _simd_f32x4_combine_enable() && _simd_f32x4_splitlo_enable()  && _simd_f32x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x4_and_) && ! defined(_simd_f32x4_and_scalar_)
//	#define _simd_f32x4_and_scalar_(X,Y) _simd_f32x4_and_(X,_simd_f32x4_fill_scalar_(Y))
//	#define _simd_f32x4_and_scalar_instruction_set _simd_f32x4_and_instruction_set
//#endif
//#ifdef _simd_f32x4_and_scalar_
//	#define _simd_f32x4_and_scalar(X,Y) _simd_f32x4_and_scalar_(X,Y)
//	#define _simd_f32x4_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_and_scalar_instruction_set>()
//#else
//	#define _simd_f32x4_and_scalar(X,Y) _simd_f32x4_and_safe(X,_simd_f32x4_fill_scalar_safe(Y))
//	#define _simd_f32x4_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_f32x1_and_safe
//	#define _simd_f32x1_and_safe(X,Y) X
//	#define _simd_f32x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_f32x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_and_enabled() true
//#endif
//
//#define _simd_f32x8_and_safe(X,Y)_simd_f32x8_combine_safe(\
//	_simd_f32x4_and_safe(_simd_f32x8_splitlo_safe(X), _simd_ f32x8_splitlo_safe(Y)),\
//	_simd_f32x4_and_safe(_simd_f32x8_splithi_safe(X), _simd_ f32x8_splithi_safe(Y)))
//#ifdef _simd_f32x8_and_
//	#define _simd_f32x8_and(X,Y) _simd_f32x8_and_(X, Y)
//	#define _simd_f32x8_and_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_and_instruction_set>()
//#elif defined(_simd_f32x16_and_)
//	static ANVIL_STRONG_INLINE _simd_f32x8 ANVIL_SIMD_CALL _simd_f32x8_and(const register _simd_f32x8 x, const register _simd_f32x8 y) {
//		union SIMDUnion { _simd_f32x8 v1; _simd_f32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x16_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x8_and_enable() _simd_f32x16_and_enable()
//#elif defined(_simd_f32x32_and_)
//	static ANVIL_STRONG_INLINE _simd_f32x8 ANVIL_SIMD_CALL _simd_f32x8_and(const register _simd_f32x8 x, const register _simd_f32x8 y) {
//		union SIMDUnion { _simd_f32x8 v1; _simd_f32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x8_and_enable() _simd_f32x32_and_enable()
//#elif defined(_simd_f32x64_and_)
//	static ANVIL_STRONG_INLINE _simd_f32x8 ANVIL_SIMD_CALL _simd_f32x8_and(const register _simd_f32x8 x, const register _simd_f32x8 y) {
//		union SIMDUnion { _simd_f32x8 v1; _simd_f32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x8_and_enable() _simd_f32x64_and_enable()
//#else
//	#define _simd_f32x8_and(X,Y) _simd_f32x8_combine(\
//		_simd_f32x4_and(_simd_f32x8_splitlo(X), _simd_f32x8_splitlo(Y)),\
//		_simd_f32x4_and(_simd_f32x8_splithi(X), _simd_f32x8_splithi(Y)))
//	#define _simd_f32x8_and_enable() (_simd_f32x4_and_enable() && _simd_f32x8_combine_enable() && _simd_f32x8_splitlo_enable()  && _simd_f32x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x8_and_) && ! defined(_simd_f32x8_and_scalar_)
//	#define _simd_f32x8_and_scalar_(X,Y) _simd_f32x8_and_(X,_simd_f32x8_fill_scalar_(Y))
//	#define _simd_f32x8_and_scalar_instruction_set _simd_f32x8_and_instruction_set
//#endif
//#ifdef _simd_f32x8_and_scalar_
//	#define _simd_f32x8_and_scalar(X,Y) _simd_f32x8_and_scalar_(X,Y)
//	#define _simd_f32x8_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_and_scalar_instruction_set>()
//#else
//	#define _simd_f32x8_and_scalar(X,Y) _simd_f32x8_and_safe(X,_simd_f32x8_fill_scalar_safe(Y))
//	#define _simd_f32x8_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_f32x1_and_safe
//	#define _simd_f32x1_and_safe(X,Y) X
//	#define _simd_f32x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_f32x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_and_enabled() true
//#endif
//
//#define _simd_f32x16_and_safe(X,Y)_simd_f32x16_combine_safe(\
//	_simd_f32x8_and_safe(_simd_f32x16_splitlo_safe(X), _simd_ f32x16_splitlo_safe(Y)),\
//	_simd_f32x8_and_safe(_simd_f32x16_splithi_safe(X), _simd_ f32x16_splithi_safe(Y)))
//#ifdef _simd_f32x16_and_
//	#define _simd_f32x16_and(X,Y) _simd_f32x16_and_(X, Y)
//	#define _simd_f32x16_and_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_and_instruction_set>()
//#elif defined(_simd_f32x32_and_)
//	static ANVIL_STRONG_INLINE _simd_f32x16 ANVIL_SIMD_CALL _simd_f32x16_and(const register _simd_f32x16 x, const register _simd_f32x16 y) {
//		union SIMDUnion { _simd_f32x16 v1; _simd_f32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x16_and_enable() _simd_f32x32_and_enable()
//#elif defined(_simd_f32x64_and_)
//	static ANVIL_STRONG_INLINE _simd_f32x16 ANVIL_SIMD_CALL _simd_f32x16_and(const register _simd_f32x16 x, const register _simd_f32x16 y) {
//		union SIMDUnion { _simd_f32x16 v1; _simd_f32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x16_and_enable() _simd_f32x64_and_enable()
//#else
//	#define _simd_f32x16_and(X,Y) _simd_f32x16_combine(\
//		_simd_f32x8_and(_simd_f32x16_splitlo(X), _simd_f32x16_splitlo(Y)),\
//		_simd_f32x8_and(_simd_f32x16_splithi(X), _simd_f32x16_splithi(Y)))
//	#define _simd_f32x16_and_enable() (_simd_f32x8_and_enable() && _simd_f32x16_combine_enable() && _simd_f32x16_splitlo_enable()  && _simd_f32x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x16_and_) && ! defined(_simd_f32x16_and_scalar_)
//	#define _simd_f32x16_and_scalar_(X,Y) _simd_f32x16_and_(X,_simd_f32x16_fill_scalar_(Y))
//	#define _simd_f32x16_and_scalar_instruction_set _simd_f32x16_and_instruction_set
//#endif
//#ifdef _simd_f32x16_and_scalar_
//	#define _simd_f32x16_and_scalar(X,Y) _simd_f32x16_and_scalar_(X,Y)
//	#define _simd_f32x16_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_and_scalar_instruction_set>()
//#else
//	#define _simd_f32x16_and_scalar(X,Y) _simd_f32x16_and_safe(X,_simd_f32x16_fill_scalar_safe(Y))
//	#define _simd_f32x16_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_f32x1_and_safe
//	#define _simd_f32x1_and_safe(X,Y) X
//	#define _simd_f32x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_f32x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_and_enabled() true
//#endif
//
//#define _simd_f32x32_and_safe(X,Y)_simd_f32x32_combine_safe(\
//	_simd_f32x16_and_safe(_simd_f32x32_splitlo_safe(X), _simd_ f32x32_splitlo_safe(Y)),\
//	_simd_f32x16_and_safe(_simd_f32x32_splithi_safe(X), _simd_ f32x32_splithi_safe(Y)))
//#ifdef _simd_f32x32_and_
//	#define _simd_f32x32_and(X,Y) _simd_f32x32_and_(X, Y)
//	#define _simd_f32x32_and_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_and_instruction_set>()
//#elif defined(_simd_f32x64_and_)
//	static ANVIL_STRONG_INLINE _simd_f32x32 ANVIL_SIMD_CALL _simd_f32x32_and(const register _simd_f32x32 x, const register _simd_f32x32 y) {
//		union SIMDUnion { _simd_f32x32 v1; _simd_f32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x32_and_enable() _simd_f32x64_and_enable()
//#else
//	#define _simd_f32x32_and(X,Y) _simd_f32x32_combine(\
//		_simd_f32x16_and(_simd_f32x32_splitlo(X), _simd_f32x32_splitlo(Y)),\
//		_simd_f32x16_and(_simd_f32x32_splithi(X), _simd_f32x32_splithi(Y)))
//	#define _simd_f32x32_and_enable() (_simd_f32x16_and_enable() && _simd_f32x32_combine_enable() && _simd_f32x32_splitlo_enable()  && _simd_f32x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x32_and_) && ! defined(_simd_f32x32_and_scalar_)
//	#define _simd_f32x32_and_scalar_(X,Y) _simd_f32x32_and_(X,_simd_f32x32_fill_scalar_(Y))
//	#define _simd_f32x32_and_scalar_instruction_set _simd_f32x32_and_instruction_set
//#endif
//#ifdef _simd_f32x32_and_scalar_
//	#define _simd_f32x32_and_scalar(X,Y) _simd_f32x32_and_scalar_(X,Y)
//	#define _simd_f32x32_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_and_scalar_instruction_set>()
//#else
//	#define _simd_f32x32_and_scalar(X,Y) _simd_f32x32_and_safe(X,_simd_f32x32_fill_scalar_safe(Y))
//	#define _simd_f32x32_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_f32x1_and_safe
//	#define _simd_f32x1_and_safe(X,Y) X
//	#define _simd_f32x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_f32x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_and_enabled() true
//#endif
//
//#define _simd_f32x64_and_safe(X,Y)_simd_f32x64_combine_safe(\
//	_simd_f32x32_and_safe(_simd_f32x64_splitlo_safe(X), _simd_ f32x64_splitlo_safe(Y)),\
//	_simd_f32x32_and_safe(_simd_f32x64_splithi_safe(X), _simd_ f32x64_splithi_safe(Y)))
//#ifdef _simd_f32x64_and_
//	#define _simd_f32x64_and(X,Y) _simd_f32x64_and_(X, Y)
//	#define _simd_f32x64_and_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_and_instruction_set>()
//#else
//	#define _simd_f32x64_and(X,Y) _simd_f32x64_combine(\
//		_simd_f32x32_and(_simd_f32x64_splitlo(X), _simd_f32x64_splitlo(Y)),\
//		_simd_f32x32_and(_simd_f32x64_splithi(X), _simd_f32x64_splithi(Y)))
//	#define _simd_f32x64_and_enable() (_simd_f32x32_and_enable() && _simd_f32x64_combine_enable() && _simd_f32x64_splitlo_enable()  && _simd_f32x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x64_and_) && ! defined(_simd_f32x64_and_scalar_)
//	#define _simd_f32x64_and_scalar_(X,Y) _simd_f32x64_and_(X,_simd_f32x64_fill_scalar_(Y))
//	#define _simd_f32x64_and_scalar_instruction_set _simd_f32x64_and_instruction_set
//#endif
//#ifdef _simd_f32x64_and_scalar_
//	#define _simd_f32x64_and_scalar(X,Y) _simd_f32x64_and_scalar_(X,Y)
//	#define _simd_f32x64_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_and_scalar_instruction_set>()
//#else
//	#define _simd_f32x64_and_scalar(X,Y) _simd_f32x64_and_safe(X,_simd_f32x64_fill_scalar_safe(Y))
//	#define _simd_f32x64_and_scalar_enabled() true
//#endif
//
//// -- s64 --
//
//#ifndef _simd_s64x1_and_safe
//	#define _simd_s64x1_and_safe(X,Y) (X & Y)
//	#define _simd_s64x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_s64x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_and_enabled() true
//#endif
//
//#define _simd_s64x2_and_safe(X,Y)_simd_s64x2_combine_safe(\
//	_simd_s64x1_and_safe(_simd_s64x2_splitlo_safe(X), _simd_ s64x2_splitlo_safe(Y)),\
//	_simd_s64x1_and_safe(_simd_s64x2_splithi_safe(X), _simd_ s64x2_splithi_safe(Y)))
//#ifdef _simd_s64x2_and_
//	#define _simd_s64x2_and(X,Y) _simd_s64x2_and_(X, Y)
//	#define _simd_s64x2_and_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_and_instruction_set>()
//#elif defined(_simd_s64x4_and_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_and(const register _simd_s64x2 x, const register _simd_s64x2 y) {
//		union SIMDUnion { _simd_s64x2 v1; _simd_s64x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x4_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x2_and_enable() _simd_s64x4_and_enable()
//#elif defined(_simd_s64x8_and_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_and(const register _simd_s64x2 x, const register _simd_s64x2 y) {
//		union SIMDUnion { _simd_s64x2 v1; _simd_s64x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x8_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x2_and_enable() _simd_s64x8_and_enable()
//#elif defined(_simd_s64x16_and_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_and(const register _simd_s64x2 x, const register _simd_s64x2 y) {
//		union SIMDUnion { _simd_s64x2 v1; _simd_s64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x16_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x2_and_enable() _simd_s64x16_and_enable()
//#elif defined(_simd_s64x32_and_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_and(const register _simd_s64x2 x, const register _simd_s64x2 y) {
//		union SIMDUnion { _simd_s64x2 v1; _simd_s64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x2_and_enable() _simd_s64x32_and_enable()
//#elif defined(_simd_s64x64_and_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_and(const register _simd_s64x2 x, const register _simd_s64x2 y) {
//		union SIMDUnion { _simd_s64x2 v1; _simd_s64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x2_and_enable() _simd_s64x64_and_enable()
//#else
//	#define _simd_s64x2_and(X,Y) _simd_s64x2_combine(\
//		_simd_s64x1_and(_simd_s64x2_splitlo(X), _simd_s64x2_splitlo(Y)),\
//		_simd_s64x1_and(_simd_s64x2_splithi(X), _simd_s64x2_splithi(Y)))
//	#define _simd_s64x2_and_enable() (_simd_s64x1_and_enable() && _simd_s64x2_combine_enable() && _simd_s64x2_splitlo_enable()  && _simd_s64x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x2_and_) && ! defined(_simd_s64x2_and_scalar_)
//	#define _simd_s64x2_and_scalar_(X,Y) _simd_s64x2_and_(X,_simd_s64x2_fill_scalar_(Y))
//	#define _simd_s64x2_and_scalar_instruction_set _simd_s64x2_and_instruction_set
//#endif
//#ifdef _simd_s64x2_and_scalar_
//	#define _simd_s64x2_and_scalar(X,Y) _simd_s64x2_and_scalar_(X,Y)
//	#define _simd_s64x2_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_and_scalar_instruction_set>()
//#else
//	#define _simd_s64x2_and_scalar(X,Y) _simd_s64x2_and_safe(X,_simd_s64x2_fill_scalar_safe(Y))
//	#define _simd_s64x2_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_s64x1_and_safe
//	#define _simd_s64x1_and_safe(X,Y) (X & Y)
//	#define _simd_s64x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_s64x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_and_enabled() true
//#endif
//
//#define _simd_s64x4_and_safe(X,Y)_simd_s64x4_combine_safe(\
//	_simd_s64x2_and_safe(_simd_s64x4_splitlo_safe(X), _simd_ s64x4_splitlo_safe(Y)),\
//	_simd_s64x2_and_safe(_simd_s64x4_splithi_safe(X), _simd_ s64x4_splithi_safe(Y)))
//#ifdef _simd_s64x4_and_
//	#define _simd_s64x4_and(X,Y) _simd_s64x4_and_(X, Y)
//	#define _simd_s64x4_and_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_and_instruction_set>()
//#elif defined(_simd_s64x8_and_)
//	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_and(const register _simd_s64x4 x, const register _simd_s64x4 y) {
//		union SIMDUnion { _simd_s64x4 v1; _simd_s64x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x8_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x4_and_enable() _simd_s64x8_and_enable()
//#elif defined(_simd_s64x16_and_)
//	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_and(const register _simd_s64x4 x, const register _simd_s64x4 y) {
//		union SIMDUnion { _simd_s64x4 v1; _simd_s64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x16_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x4_and_enable() _simd_s64x16_and_enable()
//#elif defined(_simd_s64x32_and_)
//	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_and(const register _simd_s64x4 x, const register _simd_s64x4 y) {
//		union SIMDUnion { _simd_s64x4 v1; _simd_s64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x4_and_enable() _simd_s64x32_and_enable()
//#elif defined(_simd_s64x64_and_)
//	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_and(const register _simd_s64x4 x, const register _simd_s64x4 y) {
//		union SIMDUnion { _simd_s64x4 v1; _simd_s64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x4_and_enable() _simd_s64x64_and_enable()
//#else
//	#define _simd_s64x4_and(X,Y) _simd_s64x4_combine(\
//		_simd_s64x2_and(_simd_s64x4_splitlo(X), _simd_s64x4_splitlo(Y)),\
//		_simd_s64x2_and(_simd_s64x4_splithi(X), _simd_s64x4_splithi(Y)))
//	#define _simd_s64x4_and_enable() (_simd_s64x2_and_enable() && _simd_s64x4_combine_enable() && _simd_s64x4_splitlo_enable()  && _simd_s64x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x4_and_) && ! defined(_simd_s64x4_and_scalar_)
//	#define _simd_s64x4_and_scalar_(X,Y) _simd_s64x4_and_(X,_simd_s64x4_fill_scalar_(Y))
//	#define _simd_s64x4_and_scalar_instruction_set _simd_s64x4_and_instruction_set
//#endif
//#ifdef _simd_s64x4_and_scalar_
//	#define _simd_s64x4_and_scalar(X,Y) _simd_s64x4_and_scalar_(X,Y)
//	#define _simd_s64x4_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_and_scalar_instruction_set>()
//#else
//	#define _simd_s64x4_and_scalar(X,Y) _simd_s64x4_and_safe(X,_simd_s64x4_fill_scalar_safe(Y))
//	#define _simd_s64x4_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_s64x1_and_safe
//	#define _simd_s64x1_and_safe(X,Y) (X & Y)
//	#define _simd_s64x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_s64x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_and_enabled() true
//#endif
//
//#define _simd_s64x8_and_safe(X,Y)_simd_s64x8_combine_safe(\
//	_simd_s64x4_and_safe(_simd_s64x8_splitlo_safe(X), _simd_ s64x8_splitlo_safe(Y)),\
//	_simd_s64x4_and_safe(_simd_s64x8_splithi_safe(X), _simd_ s64x8_splithi_safe(Y)))
//#ifdef _simd_s64x8_and_
//	#define _simd_s64x8_and(X,Y) _simd_s64x8_and_(X, Y)
//	#define _simd_s64x8_and_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_and_instruction_set>()
//#elif defined(_simd_s64x16_and_)
//	static ANVIL_STRONG_INLINE _simd_s64x8 ANVIL_SIMD_CALL _simd_s64x8_and(const register _simd_s64x8 x, const register _simd_s64x8 y) {
//		union SIMDUnion { _simd_s64x8 v1; _simd_s64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x16_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x8_and_enable() _simd_s64x16_and_enable()
//#elif defined(_simd_s64x32_and_)
//	static ANVIL_STRONG_INLINE _simd_s64x8 ANVIL_SIMD_CALL _simd_s64x8_and(const register _simd_s64x8 x, const register _simd_s64x8 y) {
//		union SIMDUnion { _simd_s64x8 v1; _simd_s64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x8_and_enable() _simd_s64x32_and_enable()
//#elif defined(_simd_s64x64_and_)
//	static ANVIL_STRONG_INLINE _simd_s64x8 ANVIL_SIMD_CALL _simd_s64x8_and(const register _simd_s64x8 x, const register _simd_s64x8 y) {
//		union SIMDUnion { _simd_s64x8 v1; _simd_s64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x8_and_enable() _simd_s64x64_and_enable()
//#else
//	#define _simd_s64x8_and(X,Y) _simd_s64x8_combine(\
//		_simd_s64x4_and(_simd_s64x8_splitlo(X), _simd_s64x8_splitlo(Y)),\
//		_simd_s64x4_and(_simd_s64x8_splithi(X), _simd_s64x8_splithi(Y)))
//	#define _simd_s64x8_and_enable() (_simd_s64x4_and_enable() && _simd_s64x8_combine_enable() && _simd_s64x8_splitlo_enable()  && _simd_s64x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x8_and_) && ! defined(_simd_s64x8_and_scalar_)
//	#define _simd_s64x8_and_scalar_(X,Y) _simd_s64x8_and_(X,_simd_s64x8_fill_scalar_(Y))
//	#define _simd_s64x8_and_scalar_instruction_set _simd_s64x8_and_instruction_set
//#endif
//#ifdef _simd_s64x8_and_scalar_
//	#define _simd_s64x8_and_scalar(X,Y) _simd_s64x8_and_scalar_(X,Y)
//	#define _simd_s64x8_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_and_scalar_instruction_set>()
//#else
//	#define _simd_s64x8_and_scalar(X,Y) _simd_s64x8_and_safe(X,_simd_s64x8_fill_scalar_safe(Y))
//	#define _simd_s64x8_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_s64x1_and_safe
//	#define _simd_s64x1_and_safe(X,Y) (X & Y)
//	#define _simd_s64x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_s64x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_and_enabled() true
//#endif
//
//#define _simd_s64x16_and_safe(X,Y)_simd_s64x16_combine_safe(\
//	_simd_s64x8_and_safe(_simd_s64x16_splitlo_safe(X), _simd_ s64x16_splitlo_safe(Y)),\
//	_simd_s64x8_and_safe(_simd_s64x16_splithi_safe(X), _simd_ s64x16_splithi_safe(Y)))
//#ifdef _simd_s64x16_and_
//	#define _simd_s64x16_and(X,Y) _simd_s64x16_and_(X, Y)
//	#define _simd_s64x16_and_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_and_instruction_set>()
//#elif defined(_simd_s64x32_and_)
//	static ANVIL_STRONG_INLINE _simd_s64x16 ANVIL_SIMD_CALL _simd_s64x16_and(const register _simd_s64x16 x, const register _simd_s64x16 y) {
//		union SIMDUnion { _simd_s64x16 v1; _simd_s64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x16_and_enable() _simd_s64x32_and_enable()
//#elif defined(_simd_s64x64_and_)
//	static ANVIL_STRONG_INLINE _simd_s64x16 ANVIL_SIMD_CALL _simd_s64x16_and(const register _simd_s64x16 x, const register _simd_s64x16 y) {
//		union SIMDUnion { _simd_s64x16 v1; _simd_s64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x16_and_enable() _simd_s64x64_and_enable()
//#else
//	#define _simd_s64x16_and(X,Y) _simd_s64x16_combine(\
//		_simd_s64x8_and(_simd_s64x16_splitlo(X), _simd_s64x16_splitlo(Y)),\
//		_simd_s64x8_and(_simd_s64x16_splithi(X), _simd_s64x16_splithi(Y)))
//	#define _simd_s64x16_and_enable() (_simd_s64x8_and_enable() && _simd_s64x16_combine_enable() && _simd_s64x16_splitlo_enable()  && _simd_s64x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x16_and_) && ! defined(_simd_s64x16_and_scalar_)
//	#define _simd_s64x16_and_scalar_(X,Y) _simd_s64x16_and_(X,_simd_s64x16_fill_scalar_(Y))
//	#define _simd_s64x16_and_scalar_instruction_set _simd_s64x16_and_instruction_set
//#endif
//#ifdef _simd_s64x16_and_scalar_
//	#define _simd_s64x16_and_scalar(X,Y) _simd_s64x16_and_scalar_(X,Y)
//	#define _simd_s64x16_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_and_scalar_instruction_set>()
//#else
//	#define _simd_s64x16_and_scalar(X,Y) _simd_s64x16_and_safe(X,_simd_s64x16_fill_scalar_safe(Y))
//	#define _simd_s64x16_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_s64x1_and_safe
//	#define _simd_s64x1_and_safe(X,Y) (X & Y)
//	#define _simd_s64x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_s64x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_and_enabled() true
//#endif
//
//#define _simd_s64x32_and_safe(X,Y)_simd_s64x32_combine_safe(\
//	_simd_s64x16_and_safe(_simd_s64x32_splitlo_safe(X), _simd_ s64x32_splitlo_safe(Y)),\
//	_simd_s64x16_and_safe(_simd_s64x32_splithi_safe(X), _simd_ s64x32_splithi_safe(Y)))
//#ifdef _simd_s64x32_and_
//	#define _simd_s64x32_and(X,Y) _simd_s64x32_and_(X, Y)
//	#define _simd_s64x32_and_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_and_instruction_set>()
//#elif defined(_simd_s64x64_and_)
//	static ANVIL_STRONG_INLINE _simd_s64x32 ANVIL_SIMD_CALL _simd_s64x32_and(const register _simd_s64x32 x, const register _simd_s64x32 y) {
//		union SIMDUnion { _simd_s64x32 v1; _simd_s64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x32_and_enable() _simd_s64x64_and_enable()
//#else
//	#define _simd_s64x32_and(X,Y) _simd_s64x32_combine(\
//		_simd_s64x16_and(_simd_s64x32_splitlo(X), _simd_s64x32_splitlo(Y)),\
//		_simd_s64x16_and(_simd_s64x32_splithi(X), _simd_s64x32_splithi(Y)))
//	#define _simd_s64x32_and_enable() (_simd_s64x16_and_enable() && _simd_s64x32_combine_enable() && _simd_s64x32_splitlo_enable()  && _simd_s64x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x32_and_) && ! defined(_simd_s64x32_and_scalar_)
//	#define _simd_s64x32_and_scalar_(X,Y) _simd_s64x32_and_(X,_simd_s64x32_fill_scalar_(Y))
//	#define _simd_s64x32_and_scalar_instruction_set _simd_s64x32_and_instruction_set
//#endif
//#ifdef _simd_s64x32_and_scalar_
//	#define _simd_s64x32_and_scalar(X,Y) _simd_s64x32_and_scalar_(X,Y)
//	#define _simd_s64x32_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_and_scalar_instruction_set>()
//#else
//	#define _simd_s64x32_and_scalar(X,Y) _simd_s64x32_and_safe(X,_simd_s64x32_fill_scalar_safe(Y))
//	#define _simd_s64x32_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_s64x1_and_safe
//	#define _simd_s64x1_and_safe(X,Y) (X & Y)
//	#define _simd_s64x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_s64x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_and_enabled() true
//#endif
//
//#define _simd_s64x64_and_safe(X,Y)_simd_s64x64_combine_safe(\
//	_simd_s64x32_and_safe(_simd_s64x64_splitlo_safe(X), _simd_ s64x64_splitlo_safe(Y)),\
//	_simd_s64x32_and_safe(_simd_s64x64_splithi_safe(X), _simd_ s64x64_splithi_safe(Y)))
//#ifdef _simd_s64x64_and_
//	#define _simd_s64x64_and(X,Y) _simd_s64x64_and_(X, Y)
//	#define _simd_s64x64_and_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_and_instruction_set>()
//#else
//	#define _simd_s64x64_and(X,Y) _simd_s64x64_combine(\
//		_simd_s64x32_and(_simd_s64x64_splitlo(X), _simd_s64x64_splitlo(Y)),\
//		_simd_s64x32_and(_simd_s64x64_splithi(X), _simd_s64x64_splithi(Y)))
//	#define _simd_s64x64_and_enable() (_simd_s64x32_and_enable() && _simd_s64x64_combine_enable() && _simd_s64x64_splitlo_enable()  && _simd_s64x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x64_and_) && ! defined(_simd_s64x64_and_scalar_)
//	#define _simd_s64x64_and_scalar_(X,Y) _simd_s64x64_and_(X,_simd_s64x64_fill_scalar_(Y))
//	#define _simd_s64x64_and_scalar_instruction_set _simd_s64x64_and_instruction_set
//#endif
//#ifdef _simd_s64x64_and_scalar_
//	#define _simd_s64x64_and_scalar(X,Y) _simd_s64x64_and_scalar_(X,Y)
//	#define _simd_s64x64_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_and_scalar_instruction_set>()
//#else
//	#define _simd_s64x64_and_scalar(X,Y) _simd_s64x64_and_safe(X,_simd_s64x64_fill_scalar_safe(Y))
//	#define _simd_s64x64_and_scalar_enabled() true
//#endif
//
//// -- u64 --
//
//#ifndef _simd_u64x1_and_safe
//	#define _simd_u64x1_and_safe(X,Y) (X & Y)
//	#define _simd_u64x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_u64x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_and_enabled() true
//#endif
//
//#define _simd_u64x2_and_safe(X,Y)_simd_u64x2_combine_safe(\
//	_simd_u64x1_and_safe(_simd_u64x2_splitlo_safe(X), _simd_ u64x2_splitlo_safe(Y)),\
//	_simd_u64x1_and_safe(_simd_u64x2_splithi_safe(X), _simd_ u64x2_splithi_safe(Y)))
//#ifdef _simd_u64x2_and_
//	#define _simd_u64x2_and(X,Y) _simd_u64x2_and_(X, Y)
//	#define _simd_u64x2_and_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_and_instruction_set>()
//#elif defined(_simd_u64x4_and_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_and(const register _simd_u64x2 x, const register _simd_u64x2 y) {
//		union SIMDUnion { _simd_u64x2 v1; _simd_u64x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x4_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x2_and_enable() _simd_u64x4_and_enable()
//#elif defined(_simd_u64x8_and_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_and(const register _simd_u64x2 x, const register _simd_u64x2 y) {
//		union SIMDUnion { _simd_u64x2 v1; _simd_u64x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x8_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x2_and_enable() _simd_u64x8_and_enable()
//#elif defined(_simd_u64x16_and_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_and(const register _simd_u64x2 x, const register _simd_u64x2 y) {
//		union SIMDUnion { _simd_u64x2 v1; _simd_u64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x16_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x2_and_enable() _simd_u64x16_and_enable()
//#elif defined(_simd_u64x32_and_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_and(const register _simd_u64x2 x, const register _simd_u64x2 y) {
//		union SIMDUnion { _simd_u64x2 v1; _simd_u64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x2_and_enable() _simd_u64x32_and_enable()
//#elif defined(_simd_u64x64_and_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_and(const register _simd_u64x2 x, const register _simd_u64x2 y) {
//		union SIMDUnion { _simd_u64x2 v1; _simd_u64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x2_and_enable() _simd_u64x64_and_enable()
//#else
//	#define _simd_u64x2_and(X,Y) _simd_u64x2_combine(\
//		_simd_u64x1_and(_simd_u64x2_splitlo(X), _simd_u64x2_splitlo(Y)),\
//		_simd_u64x1_and(_simd_u64x2_splithi(X), _simd_u64x2_splithi(Y)))
//	#define _simd_u64x2_and_enable() (_simd_u64x1_and_enable() && _simd_u64x2_combine_enable() && _simd_u64x2_splitlo_enable()  && _simd_u64x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x2_and_) && ! defined(_simd_u64x2_and_scalar_)
//	#define _simd_u64x2_and_scalar_(X,Y) _simd_u64x2_and_(X,_simd_u64x2_fill_scalar_(Y))
//	#define _simd_u64x2_and_scalar_instruction_set _simd_u64x2_and_instruction_set
//#endif
//#ifdef _simd_u64x2_and_scalar_
//	#define _simd_u64x2_and_scalar(X,Y) _simd_u64x2_and_scalar_(X,Y)
//	#define _simd_u64x2_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_and_scalar_instruction_set>()
//#else
//	#define _simd_u64x2_and_scalar(X,Y) _simd_u64x2_and_safe(X,_simd_u64x2_fill_scalar_safe(Y))
//	#define _simd_u64x2_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_u64x1_and_safe
//	#define _simd_u64x1_and_safe(X,Y) (X & Y)
//	#define _simd_u64x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_u64x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_and_enabled() true
//#endif
//
//#define _simd_u64x4_and_safe(X,Y)_simd_u64x4_combine_safe(\
//	_simd_u64x2_and_safe(_simd_u64x4_splitlo_safe(X), _simd_ u64x4_splitlo_safe(Y)),\
//	_simd_u64x2_and_safe(_simd_u64x4_splithi_safe(X), _simd_ u64x4_splithi_safe(Y)))
//#ifdef _simd_u64x4_and_
//	#define _simd_u64x4_and(X,Y) _simd_u64x4_and_(X, Y)
//	#define _simd_u64x4_and_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_and_instruction_set>()
//#elif defined(_simd_u64x8_and_)
//	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_and(const register _simd_u64x4 x, const register _simd_u64x4 y) {
//		union SIMDUnion { _simd_u64x4 v1; _simd_u64x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x8_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x4_and_enable() _simd_u64x8_and_enable()
//#elif defined(_simd_u64x16_and_)
//	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_and(const register _simd_u64x4 x, const register _simd_u64x4 y) {
//		union SIMDUnion { _simd_u64x4 v1; _simd_u64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x16_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x4_and_enable() _simd_u64x16_and_enable()
//#elif defined(_simd_u64x32_and_)
//	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_and(const register _simd_u64x4 x, const register _simd_u64x4 y) {
//		union SIMDUnion { _simd_u64x4 v1; _simd_u64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x4_and_enable() _simd_u64x32_and_enable()
//#elif defined(_simd_u64x64_and_)
//	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_and(const register _simd_u64x4 x, const register _simd_u64x4 y) {
//		union SIMDUnion { _simd_u64x4 v1; _simd_u64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x4_and_enable() _simd_u64x64_and_enable()
//#else
//	#define _simd_u64x4_and(X,Y) _simd_u64x4_combine(\
//		_simd_u64x2_and(_simd_u64x4_splitlo(X), _simd_u64x4_splitlo(Y)),\
//		_simd_u64x2_and(_simd_u64x4_splithi(X), _simd_u64x4_splithi(Y)))
//	#define _simd_u64x4_and_enable() (_simd_u64x2_and_enable() && _simd_u64x4_combine_enable() && _simd_u64x4_splitlo_enable()  && _simd_u64x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x4_and_) && ! defined(_simd_u64x4_and_scalar_)
//	#define _simd_u64x4_and_scalar_(X,Y) _simd_u64x4_and_(X,_simd_u64x4_fill_scalar_(Y))
//	#define _simd_u64x4_and_scalar_instruction_set _simd_u64x4_and_instruction_set
//#endif
//#ifdef _simd_u64x4_and_scalar_
//	#define _simd_u64x4_and_scalar(X,Y) _simd_u64x4_and_scalar_(X,Y)
//	#define _simd_u64x4_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_and_scalar_instruction_set>()
//#else
//	#define _simd_u64x4_and_scalar(X,Y) _simd_u64x4_and_safe(X,_simd_u64x4_fill_scalar_safe(Y))
//	#define _simd_u64x4_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_u64x1_and_safe
//	#define _simd_u64x1_and_safe(X,Y) (X & Y)
//	#define _simd_u64x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_u64x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_and_enabled() true
//#endif
//
//#define _simd_u64x8_and_safe(X,Y)_simd_u64x8_combine_safe(\
//	_simd_u64x4_and_safe(_simd_u64x8_splitlo_safe(X), _simd_ u64x8_splitlo_safe(Y)),\
//	_simd_u64x4_and_safe(_simd_u64x8_splithi_safe(X), _simd_ u64x8_splithi_safe(Y)))
//#ifdef _simd_u64x8_and_
//	#define _simd_u64x8_and(X,Y) _simd_u64x8_and_(X, Y)
//	#define _simd_u64x8_and_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_and_instruction_set>()
//#elif defined(_simd_u64x16_and_)
//	static ANVIL_STRONG_INLINE _simd_u64x8 ANVIL_SIMD_CALL _simd_u64x8_and(const register _simd_u64x8 x, const register _simd_u64x8 y) {
//		union SIMDUnion { _simd_u64x8 v1; _simd_u64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x16_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x8_and_enable() _simd_u64x16_and_enable()
//#elif defined(_simd_u64x32_and_)
//	static ANVIL_STRONG_INLINE _simd_u64x8 ANVIL_SIMD_CALL _simd_u64x8_and(const register _simd_u64x8 x, const register _simd_u64x8 y) {
//		union SIMDUnion { _simd_u64x8 v1; _simd_u64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x8_and_enable() _simd_u64x32_and_enable()
//#elif defined(_simd_u64x64_and_)
//	static ANVIL_STRONG_INLINE _simd_u64x8 ANVIL_SIMD_CALL _simd_u64x8_and(const register _simd_u64x8 x, const register _simd_u64x8 y) {
//		union SIMDUnion { _simd_u64x8 v1; _simd_u64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x8_and_enable() _simd_u64x64_and_enable()
//#else
//	#define _simd_u64x8_and(X,Y) _simd_u64x8_combine(\
//		_simd_u64x4_and(_simd_u64x8_splitlo(X), _simd_u64x8_splitlo(Y)),\
//		_simd_u64x4_and(_simd_u64x8_splithi(X), _simd_u64x8_splithi(Y)))
//	#define _simd_u64x8_and_enable() (_simd_u64x4_and_enable() && _simd_u64x8_combine_enable() && _simd_u64x8_splitlo_enable()  && _simd_u64x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x8_and_) && ! defined(_simd_u64x8_and_scalar_)
//	#define _simd_u64x8_and_scalar_(X,Y) _simd_u64x8_and_(X,_simd_u64x8_fill_scalar_(Y))
//	#define _simd_u64x8_and_scalar_instruction_set _simd_u64x8_and_instruction_set
//#endif
//#ifdef _simd_u64x8_and_scalar_
//	#define _simd_u64x8_and_scalar(X,Y) _simd_u64x8_and_scalar_(X,Y)
//	#define _simd_u64x8_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_and_scalar_instruction_set>()
//#else
//	#define _simd_u64x8_and_scalar(X,Y) _simd_u64x8_and_safe(X,_simd_u64x8_fill_scalar_safe(Y))
//	#define _simd_u64x8_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_u64x1_and_safe
//	#define _simd_u64x1_and_safe(X,Y) (X & Y)
//	#define _simd_u64x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_u64x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_and_enabled() true
//#endif
//
//#define _simd_u64x16_and_safe(X,Y)_simd_u64x16_combine_safe(\
//	_simd_u64x8_and_safe(_simd_u64x16_splitlo_safe(X), _simd_ u64x16_splitlo_safe(Y)),\
//	_simd_u64x8_and_safe(_simd_u64x16_splithi_safe(X), _simd_ u64x16_splithi_safe(Y)))
//#ifdef _simd_u64x16_and_
//	#define _simd_u64x16_and(X,Y) _simd_u64x16_and_(X, Y)
//	#define _simd_u64x16_and_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_and_instruction_set>()
//#elif defined(_simd_u64x32_and_)
//	static ANVIL_STRONG_INLINE _simd_u64x16 ANVIL_SIMD_CALL _simd_u64x16_and(const register _simd_u64x16 x, const register _simd_u64x16 y) {
//		union SIMDUnion { _simd_u64x16 v1; _simd_u64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x16_and_enable() _simd_u64x32_and_enable()
//#elif defined(_simd_u64x64_and_)
//	static ANVIL_STRONG_INLINE _simd_u64x16 ANVIL_SIMD_CALL _simd_u64x16_and(const register _simd_u64x16 x, const register _simd_u64x16 y) {
//		union SIMDUnion { _simd_u64x16 v1; _simd_u64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x16_and_enable() _simd_u64x64_and_enable()
//#else
//	#define _simd_u64x16_and(X,Y) _simd_u64x16_combine(\
//		_simd_u64x8_and(_simd_u64x16_splitlo(X), _simd_u64x16_splitlo(Y)),\
//		_simd_u64x8_and(_simd_u64x16_splithi(X), _simd_u64x16_splithi(Y)))
//	#define _simd_u64x16_and_enable() (_simd_u64x8_and_enable() && _simd_u64x16_combine_enable() && _simd_u64x16_splitlo_enable()  && _simd_u64x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x16_and_) && ! defined(_simd_u64x16_and_scalar_)
//	#define _simd_u64x16_and_scalar_(X,Y) _simd_u64x16_and_(X,_simd_u64x16_fill_scalar_(Y))
//	#define _simd_u64x16_and_scalar_instruction_set _simd_u64x16_and_instruction_set
//#endif
//#ifdef _simd_u64x16_and_scalar_
//	#define _simd_u64x16_and_scalar(X,Y) _simd_u64x16_and_scalar_(X,Y)
//	#define _simd_u64x16_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_and_scalar_instruction_set>()
//#else
//	#define _simd_u64x16_and_scalar(X,Y) _simd_u64x16_and_safe(X,_simd_u64x16_fill_scalar_safe(Y))
//	#define _simd_u64x16_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_u64x1_and_safe
//	#define _simd_u64x1_and_safe(X,Y) (X & Y)
//	#define _simd_u64x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_u64x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_and_enabled() true
//#endif
//
//#define _simd_u64x32_and_safe(X,Y)_simd_u64x32_combine_safe(\
//	_simd_u64x16_and_safe(_simd_u64x32_splitlo_safe(X), _simd_ u64x32_splitlo_safe(Y)),\
//	_simd_u64x16_and_safe(_simd_u64x32_splithi_safe(X), _simd_ u64x32_splithi_safe(Y)))
//#ifdef _simd_u64x32_and_
//	#define _simd_u64x32_and(X,Y) _simd_u64x32_and_(X, Y)
//	#define _simd_u64x32_and_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_and_instruction_set>()
//#elif defined(_simd_u64x64_and_)
//	static ANVIL_STRONG_INLINE _simd_u64x32 ANVIL_SIMD_CALL _simd_u64x32_and(const register _simd_u64x32 x, const register _simd_u64x32 y) {
//		union SIMDUnion { _simd_u64x32 v1; _simd_u64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x32_and_enable() _simd_u64x64_and_enable()
//#else
//	#define _simd_u64x32_and(X,Y) _simd_u64x32_combine(\
//		_simd_u64x16_and(_simd_u64x32_splitlo(X), _simd_u64x32_splitlo(Y)),\
//		_simd_u64x16_and(_simd_u64x32_splithi(X), _simd_u64x32_splithi(Y)))
//	#define _simd_u64x32_and_enable() (_simd_u64x16_and_enable() && _simd_u64x32_combine_enable() && _simd_u64x32_splitlo_enable()  && _simd_u64x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x32_and_) && ! defined(_simd_u64x32_and_scalar_)
//	#define _simd_u64x32_and_scalar_(X,Y) _simd_u64x32_and_(X,_simd_u64x32_fill_scalar_(Y))
//	#define _simd_u64x32_and_scalar_instruction_set _simd_u64x32_and_instruction_set
//#endif
//#ifdef _simd_u64x32_and_scalar_
//	#define _simd_u64x32_and_scalar(X,Y) _simd_u64x32_and_scalar_(X,Y)
//	#define _simd_u64x32_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_and_scalar_instruction_set>()
//#else
//	#define _simd_u64x32_and_scalar(X,Y) _simd_u64x32_and_safe(X,_simd_u64x32_fill_scalar_safe(Y))
//	#define _simd_u64x32_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_u64x1_and_safe
//	#define _simd_u64x1_and_safe(X,Y) (X & Y)
//	#define _simd_u64x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_u64x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_and_enabled() true
//#endif
//
//#define _simd_u64x64_and_safe(X,Y)_simd_u64x64_combine_safe(\
//	_simd_u64x32_and_safe(_simd_u64x64_splitlo_safe(X), _simd_ u64x64_splitlo_safe(Y)),\
//	_simd_u64x32_and_safe(_simd_u64x64_splithi_safe(X), _simd_ u64x64_splithi_safe(Y)))
//#ifdef _simd_u64x64_and_
//	#define _simd_u64x64_and(X,Y) _simd_u64x64_and_(X, Y)
//	#define _simd_u64x64_and_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_and_instruction_set>()
//#else
//	#define _simd_u64x64_and(X,Y) _simd_u64x64_combine(\
//		_simd_u64x32_and(_simd_u64x64_splitlo(X), _simd_u64x64_splitlo(Y)),\
//		_simd_u64x32_and(_simd_u64x64_splithi(X), _simd_u64x64_splithi(Y)))
//	#define _simd_u64x64_and_enable() (_simd_u64x32_and_enable() && _simd_u64x64_combine_enable() && _simd_u64x64_splitlo_enable()  && _simd_u64x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x64_and_) && ! defined(_simd_u64x64_and_scalar_)
//	#define _simd_u64x64_and_scalar_(X,Y) _simd_u64x64_and_(X,_simd_u64x64_fill_scalar_(Y))
//	#define _simd_u64x64_and_scalar_instruction_set _simd_u64x64_and_instruction_set
//#endif
//#ifdef _simd_u64x64_and_scalar_
//	#define _simd_u64x64_and_scalar(X,Y) _simd_u64x64_and_scalar_(X,Y)
//	#define _simd_u64x64_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_and_scalar_instruction_set>()
//#else
//	#define _simd_u64x64_and_scalar(X,Y) _simd_u64x64_and_safe(X,_simd_u64x64_fill_scalar_safe(Y))
//	#define _simd_u64x64_and_scalar_enabled() true
//#endif
//
//// -- s32 --
//
//#ifndef _simd_s32x1_and_safe
//	#define _simd_s32x1_and_safe(X,Y) (X & Y)
//	#define _simd_s32x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_s32x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_and_enabled() true
//#endif
//
//#define _simd_s32x2_and_safe(X,Y)_simd_s32x2_combine_safe(\
//	_simd_s32x1_and_safe(_simd_s32x2_splitlo_safe(X), _simd_ s32x2_splitlo_safe(Y)),\
//	_simd_s32x1_and_safe(_simd_s32x2_splithi_safe(X), _simd_ s32x2_splithi_safe(Y)))
//#ifdef _simd_s32x2_and_
//	#define _simd_s32x2_and(X,Y) _simd_s32x2_and_(X, Y)
//	#define _simd_s32x2_and_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_and_instruction_set>()
//#elif defined(_simd_s32x4_and_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_and(const register _simd_s32x2 x, const register _simd_s32x2 y) {
//		union SIMDUnion { _simd_s32x2 v1; _simd_s32x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x4_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x2_and_enable() _simd_s32x4_and_enable()
//#elif defined(_simd_s32x8_and_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_and(const register _simd_s32x2 x, const register _simd_s32x2 y) {
//		union SIMDUnion { _simd_s32x2 v1; _simd_s32x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x8_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x2_and_enable() _simd_s32x8_and_enable()
//#elif defined(_simd_s32x16_and_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_and(const register _simd_s32x2 x, const register _simd_s32x2 y) {
//		union SIMDUnion { _simd_s32x2 v1; _simd_s32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x16_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x2_and_enable() _simd_s32x16_and_enable()
//#elif defined(_simd_s32x32_and_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_and(const register _simd_s32x2 x, const register _simd_s32x2 y) {
//		union SIMDUnion { _simd_s32x2 v1; _simd_s32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x2_and_enable() _simd_s32x32_and_enable()
//#elif defined(_simd_s32x64_and_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_and(const register _simd_s32x2 x, const register _simd_s32x2 y) {
//		union SIMDUnion { _simd_s32x2 v1; _simd_s32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x2_and_enable() _simd_s32x64_and_enable()
//#else
//	#define _simd_s32x2_and(X,Y) _simd_s32x2_combine(\
//		_simd_s32x1_and(_simd_s32x2_splitlo(X), _simd_s32x2_splitlo(Y)),\
//		_simd_s32x1_and(_simd_s32x2_splithi(X), _simd_s32x2_splithi(Y)))
//	#define _simd_s32x2_and_enable() (_simd_s32x1_and_enable() && _simd_s32x2_combine_enable() && _simd_s32x2_splitlo_enable()  && _simd_s32x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x2_and_) && ! defined(_simd_s32x2_and_scalar_)
//	#define _simd_s32x2_and_scalar_(X,Y) _simd_s32x2_and_(X,_simd_s32x2_fill_scalar_(Y))
//	#define _simd_s32x2_and_scalar_instruction_set _simd_s32x2_and_instruction_set
//#endif
//#ifdef _simd_s32x2_and_scalar_
//	#define _simd_s32x2_and_scalar(X,Y) _simd_s32x2_and_scalar_(X,Y)
//	#define _simd_s32x2_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_and_scalar_instruction_set>()
//#else
//	#define _simd_s32x2_and_scalar(X,Y) _simd_s32x2_and_safe(X,_simd_s32x2_fill_scalar_safe(Y))
//	#define _simd_s32x2_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_s32x1_and_safe
//	#define _simd_s32x1_and_safe(X,Y) (X & Y)
//	#define _simd_s32x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_s32x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_and_enabled() true
//#endif
//
//#define _simd_s32x4_and_safe(X,Y)_simd_s32x4_combine_safe(\
//	_simd_s32x2_and_safe(_simd_s32x4_splitlo_safe(X), _simd_ s32x4_splitlo_safe(Y)),\
//	_simd_s32x2_and_safe(_simd_s32x4_splithi_safe(X), _simd_ s32x4_splithi_safe(Y)))
//#ifdef _simd_s32x4_and_
//	#define _simd_s32x4_and(X,Y) _simd_s32x4_and_(X, Y)
//	#define _simd_s32x4_and_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_and_instruction_set>()
//#elif defined(_simd_s32x8_and_)
//	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_and(const register _simd_s32x4 x, const register _simd_s32x4 y) {
//		union SIMDUnion { _simd_s32x4 v1; _simd_s32x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x8_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x4_and_enable() _simd_s32x8_and_enable()
//#elif defined(_simd_s32x16_and_)
//	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_and(const register _simd_s32x4 x, const register _simd_s32x4 y) {
//		union SIMDUnion { _simd_s32x4 v1; _simd_s32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x16_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x4_and_enable() _simd_s32x16_and_enable()
//#elif defined(_simd_s32x32_and_)
//	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_and(const register _simd_s32x4 x, const register _simd_s32x4 y) {
//		union SIMDUnion { _simd_s32x4 v1; _simd_s32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x4_and_enable() _simd_s32x32_and_enable()
//#elif defined(_simd_s32x64_and_)
//	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_and(const register _simd_s32x4 x, const register _simd_s32x4 y) {
//		union SIMDUnion { _simd_s32x4 v1; _simd_s32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x4_and_enable() _simd_s32x64_and_enable()
//#else
//	#define _simd_s32x4_and(X,Y) _simd_s32x4_combine(\
//		_simd_s32x2_and(_simd_s32x4_splitlo(X), _simd_s32x4_splitlo(Y)),\
//		_simd_s32x2_and(_simd_s32x4_splithi(X), _simd_s32x4_splithi(Y)))
//	#define _simd_s32x4_and_enable() (_simd_s32x2_and_enable() && _simd_s32x4_combine_enable() && _simd_s32x4_splitlo_enable()  && _simd_s32x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x4_and_) && ! defined(_simd_s32x4_and_scalar_)
//	#define _simd_s32x4_and_scalar_(X,Y) _simd_s32x4_and_(X,_simd_s32x4_fill_scalar_(Y))
//	#define _simd_s32x4_and_scalar_instruction_set _simd_s32x4_and_instruction_set
//#endif
//#ifdef _simd_s32x4_and_scalar_
//	#define _simd_s32x4_and_scalar(X,Y) _simd_s32x4_and_scalar_(X,Y)
//	#define _simd_s32x4_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_and_scalar_instruction_set>()
//#else
//	#define _simd_s32x4_and_scalar(X,Y) _simd_s32x4_and_safe(X,_simd_s32x4_fill_scalar_safe(Y))
//	#define _simd_s32x4_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_s32x1_and_safe
//	#define _simd_s32x1_and_safe(X,Y) (X & Y)
//	#define _simd_s32x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_s32x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_and_enabled() true
//#endif
//
//#define _simd_s32x8_and_safe(X,Y)_simd_s32x8_combine_safe(\
//	_simd_s32x4_and_safe(_simd_s32x8_splitlo_safe(X), _simd_ s32x8_splitlo_safe(Y)),\
//	_simd_s32x4_and_safe(_simd_s32x8_splithi_safe(X), _simd_ s32x8_splithi_safe(Y)))
//#ifdef _simd_s32x8_and_
//	#define _simd_s32x8_and(X,Y) _simd_s32x8_and_(X, Y)
//	#define _simd_s32x8_and_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_and_instruction_set>()
//#elif defined(_simd_s32x16_and_)
//	static ANVIL_STRONG_INLINE _simd_s32x8 ANVIL_SIMD_CALL _simd_s32x8_and(const register _simd_s32x8 x, const register _simd_s32x8 y) {
//		union SIMDUnion { _simd_s32x8 v1; _simd_s32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x16_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x8_and_enable() _simd_s32x16_and_enable()
//#elif defined(_simd_s32x32_and_)
//	static ANVIL_STRONG_INLINE _simd_s32x8 ANVIL_SIMD_CALL _simd_s32x8_and(const register _simd_s32x8 x, const register _simd_s32x8 y) {
//		union SIMDUnion { _simd_s32x8 v1; _simd_s32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x8_and_enable() _simd_s32x32_and_enable()
//#elif defined(_simd_s32x64_and_)
//	static ANVIL_STRONG_INLINE _simd_s32x8 ANVIL_SIMD_CALL _simd_s32x8_and(const register _simd_s32x8 x, const register _simd_s32x8 y) {
//		union SIMDUnion { _simd_s32x8 v1; _simd_s32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x8_and_enable() _simd_s32x64_and_enable()
//#else
//	#define _simd_s32x8_and(X,Y) _simd_s32x8_combine(\
//		_simd_s32x4_and(_simd_s32x8_splitlo(X), _simd_s32x8_splitlo(Y)),\
//		_simd_s32x4_and(_simd_s32x8_splithi(X), _simd_s32x8_splithi(Y)))
//	#define _simd_s32x8_and_enable() (_simd_s32x4_and_enable() && _simd_s32x8_combine_enable() && _simd_s32x8_splitlo_enable()  && _simd_s32x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x8_and_) && ! defined(_simd_s32x8_and_scalar_)
//	#define _simd_s32x8_and_scalar_(X,Y) _simd_s32x8_and_(X,_simd_s32x8_fill_scalar_(Y))
//	#define _simd_s32x8_and_scalar_instruction_set _simd_s32x8_and_instruction_set
//#endif
//#ifdef _simd_s32x8_and_scalar_
//	#define _simd_s32x8_and_scalar(X,Y) _simd_s32x8_and_scalar_(X,Y)
//	#define _simd_s32x8_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_and_scalar_instruction_set>()
//#else
//	#define _simd_s32x8_and_scalar(X,Y) _simd_s32x8_and_safe(X,_simd_s32x8_fill_scalar_safe(Y))
//	#define _simd_s32x8_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_s32x1_and_safe
//	#define _simd_s32x1_and_safe(X,Y) (X & Y)
//	#define _simd_s32x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_s32x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_and_enabled() true
//#endif
//
//#define _simd_s32x16_and_safe(X,Y)_simd_s32x16_combine_safe(\
//	_simd_s32x8_and_safe(_simd_s32x16_splitlo_safe(X), _simd_ s32x16_splitlo_safe(Y)),\
//	_simd_s32x8_and_safe(_simd_s32x16_splithi_safe(X), _simd_ s32x16_splithi_safe(Y)))
//#ifdef _simd_s32x16_and_
//	#define _simd_s32x16_and(X,Y) _simd_s32x16_and_(X, Y)
//	#define _simd_s32x16_and_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_and_instruction_set>()
//#elif defined(_simd_s32x32_and_)
//	static ANVIL_STRONG_INLINE _simd_s32x16 ANVIL_SIMD_CALL _simd_s32x16_and(const register _simd_s32x16 x, const register _simd_s32x16 y) {
//		union SIMDUnion { _simd_s32x16 v1; _simd_s32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x16_and_enable() _simd_s32x32_and_enable()
//#elif defined(_simd_s32x64_and_)
//	static ANVIL_STRONG_INLINE _simd_s32x16 ANVIL_SIMD_CALL _simd_s32x16_and(const register _simd_s32x16 x, const register _simd_s32x16 y) {
//		union SIMDUnion { _simd_s32x16 v1; _simd_s32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x16_and_enable() _simd_s32x64_and_enable()
//#else
//	#define _simd_s32x16_and(X,Y) _simd_s32x16_combine(\
//		_simd_s32x8_and(_simd_s32x16_splitlo(X), _simd_s32x16_splitlo(Y)),\
//		_simd_s32x8_and(_simd_s32x16_splithi(X), _simd_s32x16_splithi(Y)))
//	#define _simd_s32x16_and_enable() (_simd_s32x8_and_enable() && _simd_s32x16_combine_enable() && _simd_s32x16_splitlo_enable()  && _simd_s32x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x16_and_) && ! defined(_simd_s32x16_and_scalar_)
//	#define _simd_s32x16_and_scalar_(X,Y) _simd_s32x16_and_(X,_simd_s32x16_fill_scalar_(Y))
//	#define _simd_s32x16_and_scalar_instruction_set _simd_s32x16_and_instruction_set
//#endif
//#ifdef _simd_s32x16_and_scalar_
//	#define _simd_s32x16_and_scalar(X,Y) _simd_s32x16_and_scalar_(X,Y)
//	#define _simd_s32x16_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_and_scalar_instruction_set>()
//#else
//	#define _simd_s32x16_and_scalar(X,Y) _simd_s32x16_and_safe(X,_simd_s32x16_fill_scalar_safe(Y))
//	#define _simd_s32x16_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_s32x1_and_safe
//	#define _simd_s32x1_and_safe(X,Y) (X & Y)
//	#define _simd_s32x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_s32x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_and_enabled() true
//#endif
//
//#define _simd_s32x32_and_safe(X,Y)_simd_s32x32_combine_safe(\
//	_simd_s32x16_and_safe(_simd_s32x32_splitlo_safe(X), _simd_ s32x32_splitlo_safe(Y)),\
//	_simd_s32x16_and_safe(_simd_s32x32_splithi_safe(X), _simd_ s32x32_splithi_safe(Y)))
//#ifdef _simd_s32x32_and_
//	#define _simd_s32x32_and(X,Y) _simd_s32x32_and_(X, Y)
//	#define _simd_s32x32_and_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_and_instruction_set>()
//#elif defined(_simd_s32x64_and_)
//	static ANVIL_STRONG_INLINE _simd_s32x32 ANVIL_SIMD_CALL _simd_s32x32_and(const register _simd_s32x32 x, const register _simd_s32x32 y) {
//		union SIMDUnion { _simd_s32x32 v1; _simd_s32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x32_and_enable() _simd_s32x64_and_enable()
//#else
//	#define _simd_s32x32_and(X,Y) _simd_s32x32_combine(\
//		_simd_s32x16_and(_simd_s32x32_splitlo(X), _simd_s32x32_splitlo(Y)),\
//		_simd_s32x16_and(_simd_s32x32_splithi(X), _simd_s32x32_splithi(Y)))
//	#define _simd_s32x32_and_enable() (_simd_s32x16_and_enable() && _simd_s32x32_combine_enable() && _simd_s32x32_splitlo_enable()  && _simd_s32x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x32_and_) && ! defined(_simd_s32x32_and_scalar_)
//	#define _simd_s32x32_and_scalar_(X,Y) _simd_s32x32_and_(X,_simd_s32x32_fill_scalar_(Y))
//	#define _simd_s32x32_and_scalar_instruction_set _simd_s32x32_and_instruction_set
//#endif
//#ifdef _simd_s32x32_and_scalar_
//	#define _simd_s32x32_and_scalar(X,Y) _simd_s32x32_and_scalar_(X,Y)
//	#define _simd_s32x32_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_and_scalar_instruction_set>()
//#else
//	#define _simd_s32x32_and_scalar(X,Y) _simd_s32x32_and_safe(X,_simd_s32x32_fill_scalar_safe(Y))
//	#define _simd_s32x32_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_s32x1_and_safe
//	#define _simd_s32x1_and_safe(X,Y) (X & Y)
//	#define _simd_s32x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_s32x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_and_enabled() true
//#endif
//
//#define _simd_s32x64_and_safe(X,Y)_simd_s32x64_combine_safe(\
//	_simd_s32x32_and_safe(_simd_s32x64_splitlo_safe(X), _simd_ s32x64_splitlo_safe(Y)),\
//	_simd_s32x32_and_safe(_simd_s32x64_splithi_safe(X), _simd_ s32x64_splithi_safe(Y)))
//#ifdef _simd_s32x64_and_
//	#define _simd_s32x64_and(X,Y) _simd_s32x64_and_(X, Y)
//	#define _simd_s32x64_and_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_and_instruction_set>()
//#else
//	#define _simd_s32x64_and(X,Y) _simd_s32x64_combine(\
//		_simd_s32x32_and(_simd_s32x64_splitlo(X), _simd_s32x64_splitlo(Y)),\
//		_simd_s32x32_and(_simd_s32x64_splithi(X), _simd_s32x64_splithi(Y)))
//	#define _simd_s32x64_and_enable() (_simd_s32x32_and_enable() && _simd_s32x64_combine_enable() && _simd_s32x64_splitlo_enable()  && _simd_s32x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x64_and_) && ! defined(_simd_s32x64_and_scalar_)
//	#define _simd_s32x64_and_scalar_(X,Y) _simd_s32x64_and_(X,_simd_s32x64_fill_scalar_(Y))
//	#define _simd_s32x64_and_scalar_instruction_set _simd_s32x64_and_instruction_set
//#endif
//#ifdef _simd_s32x64_and_scalar_
//	#define _simd_s32x64_and_scalar(X,Y) _simd_s32x64_and_scalar_(X,Y)
//	#define _simd_s32x64_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_and_scalar_instruction_set>()
//#else
//	#define _simd_s32x64_and_scalar(X,Y) _simd_s32x64_and_safe(X,_simd_s32x64_fill_scalar_safe(Y))
//	#define _simd_s32x64_and_scalar_enabled() true
//#endif
//
//// -- u32 --
//
//#ifndef _simd_u32x1_and_safe
//	#define _simd_u32x1_and_safe(X,Y) (X & Y)
//	#define _simd_u32x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_u32x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_and_enabled() true
//#endif
//
//#define _simd_u32x2_and_safe(X,Y)_simd_u32x2_combine_safe(\
//	_simd_u32x1_and_safe(_simd_u32x2_splitlo_safe(X), _simd_ u32x2_splitlo_safe(Y)),\
//	_simd_u32x1_and_safe(_simd_u32x2_splithi_safe(X), _simd_ u32x2_splithi_safe(Y)))
//#ifdef _simd_u32x2_and_
//	#define _simd_u32x2_and(X,Y) _simd_u32x2_and_(X, Y)
//	#define _simd_u32x2_and_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_and_instruction_set>()
//#elif defined(_simd_u32x4_and_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_and(const register _simd_u32x2 x, const register _simd_u32x2 y) {
//		union SIMDUnion { _simd_u32x2 v1; _simd_u32x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x4_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x2_and_enable() _simd_u32x4_and_enable()
//#elif defined(_simd_u32x8_and_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_and(const register _simd_u32x2 x, const register _simd_u32x2 y) {
//		union SIMDUnion { _simd_u32x2 v1; _simd_u32x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x8_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x2_and_enable() _simd_u32x8_and_enable()
//#elif defined(_simd_u32x16_and_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_and(const register _simd_u32x2 x, const register _simd_u32x2 y) {
//		union SIMDUnion { _simd_u32x2 v1; _simd_u32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x16_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x2_and_enable() _simd_u32x16_and_enable()
//#elif defined(_simd_u32x32_and_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_and(const register _simd_u32x2 x, const register _simd_u32x2 y) {
//		union SIMDUnion { _simd_u32x2 v1; _simd_u32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x2_and_enable() _simd_u32x32_and_enable()
//#elif defined(_simd_u32x64_and_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_and(const register _simd_u32x2 x, const register _simd_u32x2 y) {
//		union SIMDUnion { _simd_u32x2 v1; _simd_u32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x2_and_enable() _simd_u32x64_and_enable()
//#else
//	#define _simd_u32x2_and(X,Y) _simd_u32x2_combine(\
//		_simd_u32x1_and(_simd_u32x2_splitlo(X), _simd_u32x2_splitlo(Y)),\
//		_simd_u32x1_and(_simd_u32x2_splithi(X), _simd_u32x2_splithi(Y)))
//	#define _simd_u32x2_and_enable() (_simd_u32x1_and_enable() && _simd_u32x2_combine_enable() && _simd_u32x2_splitlo_enable()  && _simd_u32x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x2_and_) && ! defined(_simd_u32x2_and_scalar_)
//	#define _simd_u32x2_and_scalar_(X,Y) _simd_u32x2_and_(X,_simd_u32x2_fill_scalar_(Y))
//	#define _simd_u32x2_and_scalar_instruction_set _simd_u32x2_and_instruction_set
//#endif
//#ifdef _simd_u32x2_and_scalar_
//	#define _simd_u32x2_and_scalar(X,Y) _simd_u32x2_and_scalar_(X,Y)
//	#define _simd_u32x2_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_and_scalar_instruction_set>()
//#else
//	#define _simd_u32x2_and_scalar(X,Y) _simd_u32x2_and_safe(X,_simd_u32x2_fill_scalar_safe(Y))
//	#define _simd_u32x2_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_u32x1_and_safe
//	#define _simd_u32x1_and_safe(X,Y) (X & Y)
//	#define _simd_u32x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_u32x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_and_enabled() true
//#endif
//
//#define _simd_u32x4_and_safe(X,Y)_simd_u32x4_combine_safe(\
//	_simd_u32x2_and_safe(_simd_u32x4_splitlo_safe(X), _simd_ u32x4_splitlo_safe(Y)),\
//	_simd_u32x2_and_safe(_simd_u32x4_splithi_safe(X), _simd_ u32x4_splithi_safe(Y)))
//#ifdef _simd_u32x4_and_
//	#define _simd_u32x4_and(X,Y) _simd_u32x4_and_(X, Y)
//	#define _simd_u32x4_and_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_and_instruction_set>()
//#elif defined(_simd_u32x8_and_)
//	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_and(const register _simd_u32x4 x, const register _simd_u32x4 y) {
//		union SIMDUnion { _simd_u32x4 v1; _simd_u32x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x8_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x4_and_enable() _simd_u32x8_and_enable()
//#elif defined(_simd_u32x16_and_)
//	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_and(const register _simd_u32x4 x, const register _simd_u32x4 y) {
//		union SIMDUnion { _simd_u32x4 v1; _simd_u32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x16_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x4_and_enable() _simd_u32x16_and_enable()
//#elif defined(_simd_u32x32_and_)
//	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_and(const register _simd_u32x4 x, const register _simd_u32x4 y) {
//		union SIMDUnion { _simd_u32x4 v1; _simd_u32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x4_and_enable() _simd_u32x32_and_enable()
//#elif defined(_simd_u32x64_and_)
//	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_and(const register _simd_u32x4 x, const register _simd_u32x4 y) {
//		union SIMDUnion { _simd_u32x4 v1; _simd_u32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x4_and_enable() _simd_u32x64_and_enable()
//#else
//	#define _simd_u32x4_and(X,Y) _simd_u32x4_combine(\
//		_simd_u32x2_and(_simd_u32x4_splitlo(X), _simd_u32x4_splitlo(Y)),\
//		_simd_u32x2_and(_simd_u32x4_splithi(X), _simd_u32x4_splithi(Y)))
//	#define _simd_u32x4_and_enable() (_simd_u32x2_and_enable() && _simd_u32x4_combine_enable() && _simd_u32x4_splitlo_enable()  && _simd_u32x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x4_and_) && ! defined(_simd_u32x4_and_scalar_)
//	#define _simd_u32x4_and_scalar_(X,Y) _simd_u32x4_and_(X,_simd_u32x4_fill_scalar_(Y))
//	#define _simd_u32x4_and_scalar_instruction_set _simd_u32x4_and_instruction_set
//#endif
//#ifdef _simd_u32x4_and_scalar_
//	#define _simd_u32x4_and_scalar(X,Y) _simd_u32x4_and_scalar_(X,Y)
//	#define _simd_u32x4_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_and_scalar_instruction_set>()
//#else
//	#define _simd_u32x4_and_scalar(X,Y) _simd_u32x4_and_safe(X,_simd_u32x4_fill_scalar_safe(Y))
//	#define _simd_u32x4_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_u32x1_and_safe
//	#define _simd_u32x1_and_safe(X,Y) (X & Y)
//	#define _simd_u32x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_u32x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_and_enabled() true
//#endif
//
//#define _simd_u32x8_and_safe(X,Y)_simd_u32x8_combine_safe(\
//	_simd_u32x4_and_safe(_simd_u32x8_splitlo_safe(X), _simd_ u32x8_splitlo_safe(Y)),\
//	_simd_u32x4_and_safe(_simd_u32x8_splithi_safe(X), _simd_ u32x8_splithi_safe(Y)))
//#ifdef _simd_u32x8_and_
//	#define _simd_u32x8_and(X,Y) _simd_u32x8_and_(X, Y)
//	#define _simd_u32x8_and_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_and_instruction_set>()
//#elif defined(_simd_u32x16_and_)
//	static ANVIL_STRONG_INLINE _simd_u32x8 ANVIL_SIMD_CALL _simd_u32x8_and(const register _simd_u32x8 x, const register _simd_u32x8 y) {
//		union SIMDUnion { _simd_u32x8 v1; _simd_u32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x16_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x8_and_enable() _simd_u32x16_and_enable()
//#elif defined(_simd_u32x32_and_)
//	static ANVIL_STRONG_INLINE _simd_u32x8 ANVIL_SIMD_CALL _simd_u32x8_and(const register _simd_u32x8 x, const register _simd_u32x8 y) {
//		union SIMDUnion { _simd_u32x8 v1; _simd_u32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x8_and_enable() _simd_u32x32_and_enable()
//#elif defined(_simd_u32x64_and_)
//	static ANVIL_STRONG_INLINE _simd_u32x8 ANVIL_SIMD_CALL _simd_u32x8_and(const register _simd_u32x8 x, const register _simd_u32x8 y) {
//		union SIMDUnion { _simd_u32x8 v1; _simd_u32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x8_and_enable() _simd_u32x64_and_enable()
//#else
//	#define _simd_u32x8_and(X,Y) _simd_u32x8_combine(\
//		_simd_u32x4_and(_simd_u32x8_splitlo(X), _simd_u32x8_splitlo(Y)),\
//		_simd_u32x4_and(_simd_u32x8_splithi(X), _simd_u32x8_splithi(Y)))
//	#define _simd_u32x8_and_enable() (_simd_u32x4_and_enable() && _simd_u32x8_combine_enable() && _simd_u32x8_splitlo_enable()  && _simd_u32x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x8_and_) && ! defined(_simd_u32x8_and_scalar_)
//	#define _simd_u32x8_and_scalar_(X,Y) _simd_u32x8_and_(X,_simd_u32x8_fill_scalar_(Y))
//	#define _simd_u32x8_and_scalar_instruction_set _simd_u32x8_and_instruction_set
//#endif
//#ifdef _simd_u32x8_and_scalar_
//	#define _simd_u32x8_and_scalar(X,Y) _simd_u32x8_and_scalar_(X,Y)
//	#define _simd_u32x8_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_and_scalar_instruction_set>()
//#else
//	#define _simd_u32x8_and_scalar(X,Y) _simd_u32x8_and_safe(X,_simd_u32x8_fill_scalar_safe(Y))
//	#define _simd_u32x8_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_u32x1_and_safe
//	#define _simd_u32x1_and_safe(X,Y) (X & Y)
//	#define _simd_u32x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_u32x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_and_enabled() true
//#endif
//
//#define _simd_u32x16_and_safe(X,Y)_simd_u32x16_combine_safe(\
//	_simd_u32x8_and_safe(_simd_u32x16_splitlo_safe(X), _simd_ u32x16_splitlo_safe(Y)),\
//	_simd_u32x8_and_safe(_simd_u32x16_splithi_safe(X), _simd_ u32x16_splithi_safe(Y)))
//#ifdef _simd_u32x16_and_
//	#define _simd_u32x16_and(X,Y) _simd_u32x16_and_(X, Y)
//	#define _simd_u32x16_and_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_and_instruction_set>()
//#elif defined(_simd_u32x32_and_)
//	static ANVIL_STRONG_INLINE _simd_u32x16 ANVIL_SIMD_CALL _simd_u32x16_and(const register _simd_u32x16 x, const register _simd_u32x16 y) {
//		union SIMDUnion { _simd_u32x16 v1; _simd_u32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x16_and_enable() _simd_u32x32_and_enable()
//#elif defined(_simd_u32x64_and_)
//	static ANVIL_STRONG_INLINE _simd_u32x16 ANVIL_SIMD_CALL _simd_u32x16_and(const register _simd_u32x16 x, const register _simd_u32x16 y) {
//		union SIMDUnion { _simd_u32x16 v1; _simd_u32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x16_and_enable() _simd_u32x64_and_enable()
//#else
//	#define _simd_u32x16_and(X,Y) _simd_u32x16_combine(\
//		_simd_u32x8_and(_simd_u32x16_splitlo(X), _simd_u32x16_splitlo(Y)),\
//		_simd_u32x8_and(_simd_u32x16_splithi(X), _simd_u32x16_splithi(Y)))
//	#define _simd_u32x16_and_enable() (_simd_u32x8_and_enable() && _simd_u32x16_combine_enable() && _simd_u32x16_splitlo_enable()  && _simd_u32x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x16_and_) && ! defined(_simd_u32x16_and_scalar_)
//	#define _simd_u32x16_and_scalar_(X,Y) _simd_u32x16_and_(X,_simd_u32x16_fill_scalar_(Y))
//	#define _simd_u32x16_and_scalar_instruction_set _simd_u32x16_and_instruction_set
//#endif
//#ifdef _simd_u32x16_and_scalar_
//	#define _simd_u32x16_and_scalar(X,Y) _simd_u32x16_and_scalar_(X,Y)
//	#define _simd_u32x16_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_and_scalar_instruction_set>()
//#else
//	#define _simd_u32x16_and_scalar(X,Y) _simd_u32x16_and_safe(X,_simd_u32x16_fill_scalar_safe(Y))
//	#define _simd_u32x16_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_u32x1_and_safe
//	#define _simd_u32x1_and_safe(X,Y) (X & Y)
//	#define _simd_u32x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_u32x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_and_enabled() true
//#endif
//
//#define _simd_u32x32_and_safe(X,Y)_simd_u32x32_combine_safe(\
//	_simd_u32x16_and_safe(_simd_u32x32_splitlo_safe(X), _simd_ u32x32_splitlo_safe(Y)),\
//	_simd_u32x16_and_safe(_simd_u32x32_splithi_safe(X), _simd_ u32x32_splithi_safe(Y)))
//#ifdef _simd_u32x32_and_
//	#define _simd_u32x32_and(X,Y) _simd_u32x32_and_(X, Y)
//	#define _simd_u32x32_and_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_and_instruction_set>()
//#elif defined(_simd_u32x64_and_)
//	static ANVIL_STRONG_INLINE _simd_u32x32 ANVIL_SIMD_CALL _simd_u32x32_and(const register _simd_u32x32 x, const register _simd_u32x32 y) {
//		union SIMDUnion { _simd_u32x32 v1; _simd_u32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x32_and_enable() _simd_u32x64_and_enable()
//#else
//	#define _simd_u32x32_and(X,Y) _simd_u32x32_combine(\
//		_simd_u32x16_and(_simd_u32x32_splitlo(X), _simd_u32x32_splitlo(Y)),\
//		_simd_u32x16_and(_simd_u32x32_splithi(X), _simd_u32x32_splithi(Y)))
//	#define _simd_u32x32_and_enable() (_simd_u32x16_and_enable() && _simd_u32x32_combine_enable() && _simd_u32x32_splitlo_enable()  && _simd_u32x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x32_and_) && ! defined(_simd_u32x32_and_scalar_)
//	#define _simd_u32x32_and_scalar_(X,Y) _simd_u32x32_and_(X,_simd_u32x32_fill_scalar_(Y))
//	#define _simd_u32x32_and_scalar_instruction_set _simd_u32x32_and_instruction_set
//#endif
//#ifdef _simd_u32x32_and_scalar_
//	#define _simd_u32x32_and_scalar(X,Y) _simd_u32x32_and_scalar_(X,Y)
//	#define _simd_u32x32_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_and_scalar_instruction_set>()
//#else
//	#define _simd_u32x32_and_scalar(X,Y) _simd_u32x32_and_safe(X,_simd_u32x32_fill_scalar_safe(Y))
//	#define _simd_u32x32_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_u32x1_and_safe
//	#define _simd_u32x1_and_safe(X,Y) (X & Y)
//	#define _simd_u32x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_u32x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_and_enabled() true
//#endif
//
//#define _simd_u32x64_and_safe(X,Y)_simd_u32x64_combine_safe(\
//	_simd_u32x32_and_safe(_simd_u32x64_splitlo_safe(X), _simd_ u32x64_splitlo_safe(Y)),\
//	_simd_u32x32_and_safe(_simd_u32x64_splithi_safe(X), _simd_ u32x64_splithi_safe(Y)))
//#ifdef _simd_u32x64_and_
//	#define _simd_u32x64_and(X,Y) _simd_u32x64_and_(X, Y)
//	#define _simd_u32x64_and_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_and_instruction_set>()
//#else
//	#define _simd_u32x64_and(X,Y) _simd_u32x64_combine(\
//		_simd_u32x32_and(_simd_u32x64_splitlo(X), _simd_u32x64_splitlo(Y)),\
//		_simd_u32x32_and(_simd_u32x64_splithi(X), _simd_u32x64_splithi(Y)))
//	#define _simd_u32x64_and_enable() (_simd_u32x32_and_enable() && _simd_u32x64_combine_enable() && _simd_u32x64_splitlo_enable()  && _simd_u32x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x64_and_) && ! defined(_simd_u32x64_and_scalar_)
//	#define _simd_u32x64_and_scalar_(X,Y) _simd_u32x64_and_(X,_simd_u32x64_fill_scalar_(Y))
//	#define _simd_u32x64_and_scalar_instruction_set _simd_u32x64_and_instruction_set
//#endif
//#ifdef _simd_u32x64_and_scalar_
//	#define _simd_u32x64_and_scalar(X,Y) _simd_u32x64_and_scalar_(X,Y)
//	#define _simd_u32x64_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_and_scalar_instruction_set>()
//#else
//	#define _simd_u32x64_and_scalar(X,Y) _simd_u32x64_and_safe(X,_simd_u32x64_fill_scalar_safe(Y))
//	#define _simd_u32x64_and_scalar_enabled() true
//#endif
//
//// -- s16 --
//
//#ifndef _simd_s16x1_and_safe
//	#define _simd_s16x1_and_safe(X,Y) (X & Y)
//	#define _simd_s16x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_s16x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_and_enabled() true
//#endif
//
//#define _simd_s16x2_and_safe(X,Y)_simd_s16x2_combine_safe(\
//	_simd_s16x1_and_safe(_simd_s16x2_splitlo_safe(X), _simd_ s16x2_splitlo_safe(Y)),\
//	_simd_s16x1_and_safe(_simd_s16x2_splithi_safe(X), _simd_ s16x2_splithi_safe(Y)))
//#ifdef _simd_s16x2_and_
//	#define _simd_s16x2_and(X,Y) _simd_s16x2_and_(X, Y)
//	#define _simd_s16x2_and_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_and_instruction_set>()
//#elif defined(_simd_s16x4_and_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_and(const register _simd_s16x2 x, const register _simd_s16x2 y) {
//		union SIMDUnion { _simd_s16x2 v1; _simd_s16x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x4_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x2_and_enable() _simd_s16x4_and_enable()
//#elif defined(_simd_s16x8_and_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_and(const register _simd_s16x2 x, const register _simd_s16x2 y) {
//		union SIMDUnion { _simd_s16x2 v1; _simd_s16x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x8_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x2_and_enable() _simd_s16x8_and_enable()
//#elif defined(_simd_s16x16_and_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_and(const register _simd_s16x2 x, const register _simd_s16x2 y) {
//		union SIMDUnion { _simd_s16x2 v1; _simd_s16x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x16_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x2_and_enable() _simd_s16x16_and_enable()
//#elif defined(_simd_s16x32_and_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_and(const register _simd_s16x2 x, const register _simd_s16x2 y) {
//		union SIMDUnion { _simd_s16x2 v1; _simd_s16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x2_and_enable() _simd_s16x32_and_enable()
//#elif defined(_simd_s16x64_and_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_and(const register _simd_s16x2 x, const register _simd_s16x2 y) {
//		union SIMDUnion { _simd_s16x2 v1; _simd_s16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x2_and_enable() _simd_s16x64_and_enable()
//#else
//	#define _simd_s16x2_and(X,Y) _simd_s16x2_combine(\
//		_simd_s16x1_and(_simd_s16x2_splitlo(X), _simd_s16x2_splitlo(Y)),\
//		_simd_s16x1_and(_simd_s16x2_splithi(X), _simd_s16x2_splithi(Y)))
//	#define _simd_s16x2_and_enable() (_simd_s16x1_and_enable() && _simd_s16x2_combine_enable() && _simd_s16x2_splitlo_enable()  && _simd_s16x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x2_and_) && ! defined(_simd_s16x2_and_scalar_)
//	#define _simd_s16x2_and_scalar_(X,Y) _simd_s16x2_and_(X,_simd_s16x2_fill_scalar_(Y))
//	#define _simd_s16x2_and_scalar_instruction_set _simd_s16x2_and_instruction_set
//#endif
//#ifdef _simd_s16x2_and_scalar_
//	#define _simd_s16x2_and_scalar(X,Y) _simd_s16x2_and_scalar_(X,Y)
//	#define _simd_s16x2_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_and_scalar_instruction_set>()
//#else
//	#define _simd_s16x2_and_scalar(X,Y) _simd_s16x2_and_safe(X,_simd_s16x2_fill_scalar_safe(Y))
//	#define _simd_s16x2_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_s16x1_and_safe
//	#define _simd_s16x1_and_safe(X,Y) (X & Y)
//	#define _simd_s16x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_s16x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_and_enabled() true
//#endif
//
//#define _simd_s16x4_and_safe(X,Y)_simd_s16x4_combine_safe(\
//	_simd_s16x2_and_safe(_simd_s16x4_splitlo_safe(X), _simd_ s16x4_splitlo_safe(Y)),\
//	_simd_s16x2_and_safe(_simd_s16x4_splithi_safe(X), _simd_ s16x4_splithi_safe(Y)))
//#ifdef _simd_s16x4_and_
//	#define _simd_s16x4_and(X,Y) _simd_s16x4_and_(X, Y)
//	#define _simd_s16x4_and_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_and_instruction_set>()
//#elif defined(_simd_s16x8_and_)
//	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_and(const register _simd_s16x4 x, const register _simd_s16x4 y) {
//		union SIMDUnion { _simd_s16x4 v1; _simd_s16x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x8_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x4_and_enable() _simd_s16x8_and_enable()
//#elif defined(_simd_s16x16_and_)
//	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_and(const register _simd_s16x4 x, const register _simd_s16x4 y) {
//		union SIMDUnion { _simd_s16x4 v1; _simd_s16x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x16_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x4_and_enable() _simd_s16x16_and_enable()
//#elif defined(_simd_s16x32_and_)
//	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_and(const register _simd_s16x4 x, const register _simd_s16x4 y) {
//		union SIMDUnion { _simd_s16x4 v1; _simd_s16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x4_and_enable() _simd_s16x32_and_enable()
//#elif defined(_simd_s16x64_and_)
//	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_and(const register _simd_s16x4 x, const register _simd_s16x4 y) {
//		union SIMDUnion { _simd_s16x4 v1; _simd_s16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x4_and_enable() _simd_s16x64_and_enable()
//#else
//	#define _simd_s16x4_and(X,Y) _simd_s16x4_combine(\
//		_simd_s16x2_and(_simd_s16x4_splitlo(X), _simd_s16x4_splitlo(Y)),\
//		_simd_s16x2_and(_simd_s16x4_splithi(X), _simd_s16x4_splithi(Y)))
//	#define _simd_s16x4_and_enable() (_simd_s16x2_and_enable() && _simd_s16x4_combine_enable() && _simd_s16x4_splitlo_enable()  && _simd_s16x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x4_and_) && ! defined(_simd_s16x4_and_scalar_)
//	#define _simd_s16x4_and_scalar_(X,Y) _simd_s16x4_and_(X,_simd_s16x4_fill_scalar_(Y))
//	#define _simd_s16x4_and_scalar_instruction_set _simd_s16x4_and_instruction_set
//#endif
//#ifdef _simd_s16x4_and_scalar_
//	#define _simd_s16x4_and_scalar(X,Y) _simd_s16x4_and_scalar_(X,Y)
//	#define _simd_s16x4_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_and_scalar_instruction_set>()
//#else
//	#define _simd_s16x4_and_scalar(X,Y) _simd_s16x4_and_safe(X,_simd_s16x4_fill_scalar_safe(Y))
//	#define _simd_s16x4_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_s16x1_and_safe
//	#define _simd_s16x1_and_safe(X,Y) (X & Y)
//	#define _simd_s16x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_s16x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_and_enabled() true
//#endif
//
//#define _simd_s16x8_and_safe(X,Y)_simd_s16x8_combine_safe(\
//	_simd_s16x4_and_safe(_simd_s16x8_splitlo_safe(X), _simd_ s16x8_splitlo_safe(Y)),\
//	_simd_s16x4_and_safe(_simd_s16x8_splithi_safe(X), _simd_ s16x8_splithi_safe(Y)))
//#ifdef _simd_s16x8_and_
//	#define _simd_s16x8_and(X,Y) _simd_s16x8_and_(X, Y)
//	#define _simd_s16x8_and_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_and_instruction_set>()
//#elif defined(_simd_s16x16_and_)
//	static ANVIL_STRONG_INLINE _simd_s16x8 ANVIL_SIMD_CALL _simd_s16x8_and(const register _simd_s16x8 x, const register _simd_s16x8 y) {
//		union SIMDUnion { _simd_s16x8 v1; _simd_s16x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x16_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x8_and_enable() _simd_s16x16_and_enable()
//#elif defined(_simd_s16x32_and_)
//	static ANVIL_STRONG_INLINE _simd_s16x8 ANVIL_SIMD_CALL _simd_s16x8_and(const register _simd_s16x8 x, const register _simd_s16x8 y) {
//		union SIMDUnion { _simd_s16x8 v1; _simd_s16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x8_and_enable() _simd_s16x32_and_enable()
//#elif defined(_simd_s16x64_and_)
//	static ANVIL_STRONG_INLINE _simd_s16x8 ANVIL_SIMD_CALL _simd_s16x8_and(const register _simd_s16x8 x, const register _simd_s16x8 y) {
//		union SIMDUnion { _simd_s16x8 v1; _simd_s16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x8_and_enable() _simd_s16x64_and_enable()
//#else
//	#define _simd_s16x8_and(X,Y) _simd_s16x8_combine(\
//		_simd_s16x4_and(_simd_s16x8_splitlo(X), _simd_s16x8_splitlo(Y)),\
//		_simd_s16x4_and(_simd_s16x8_splithi(X), _simd_s16x8_splithi(Y)))
//	#define _simd_s16x8_and_enable() (_simd_s16x4_and_enable() && _simd_s16x8_combine_enable() && _simd_s16x8_splitlo_enable()  && _simd_s16x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x8_and_) && ! defined(_simd_s16x8_and_scalar_)
//	#define _simd_s16x8_and_scalar_(X,Y) _simd_s16x8_and_(X,_simd_s16x8_fill_scalar_(Y))
//	#define _simd_s16x8_and_scalar_instruction_set _simd_s16x8_and_instruction_set
//#endif
//#ifdef _simd_s16x8_and_scalar_
//	#define _simd_s16x8_and_scalar(X,Y) _simd_s16x8_and_scalar_(X,Y)
//	#define _simd_s16x8_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_and_scalar_instruction_set>()
//#else
//	#define _simd_s16x8_and_scalar(X,Y) _simd_s16x8_and_safe(X,_simd_s16x8_fill_scalar_safe(Y))
//	#define _simd_s16x8_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_s16x1_and_safe
//	#define _simd_s16x1_and_safe(X,Y) (X & Y)
//	#define _simd_s16x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_s16x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_and_enabled() true
//#endif
//
//#define _simd_s16x16_and_safe(X,Y)_simd_s16x16_combine_safe(\
//	_simd_s16x8_and_safe(_simd_s16x16_splitlo_safe(X), _simd_ s16x16_splitlo_safe(Y)),\
//	_simd_s16x8_and_safe(_simd_s16x16_splithi_safe(X), _simd_ s16x16_splithi_safe(Y)))
//#ifdef _simd_s16x16_and_
//	#define _simd_s16x16_and(X,Y) _simd_s16x16_and_(X, Y)
//	#define _simd_s16x16_and_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_and_instruction_set>()
//#elif defined(_simd_s16x32_and_)
//	static ANVIL_STRONG_INLINE _simd_s16x16 ANVIL_SIMD_CALL _simd_s16x16_and(const register _simd_s16x16 x, const register _simd_s16x16 y) {
//		union SIMDUnion { _simd_s16x16 v1; _simd_s16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x16_and_enable() _simd_s16x32_and_enable()
//#elif defined(_simd_s16x64_and_)
//	static ANVIL_STRONG_INLINE _simd_s16x16 ANVIL_SIMD_CALL _simd_s16x16_and(const register _simd_s16x16 x, const register _simd_s16x16 y) {
//		union SIMDUnion { _simd_s16x16 v1; _simd_s16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x16_and_enable() _simd_s16x64_and_enable()
//#else
//	#define _simd_s16x16_and(X,Y) _simd_s16x16_combine(\
//		_simd_s16x8_and(_simd_s16x16_splitlo(X), _simd_s16x16_splitlo(Y)),\
//		_simd_s16x8_and(_simd_s16x16_splithi(X), _simd_s16x16_splithi(Y)))
//	#define _simd_s16x16_and_enable() (_simd_s16x8_and_enable() && _simd_s16x16_combine_enable() && _simd_s16x16_splitlo_enable()  && _simd_s16x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x16_and_) && ! defined(_simd_s16x16_and_scalar_)
//	#define _simd_s16x16_and_scalar_(X,Y) _simd_s16x16_and_(X,_simd_s16x16_fill_scalar_(Y))
//	#define _simd_s16x16_and_scalar_instruction_set _simd_s16x16_and_instruction_set
//#endif
//#ifdef _simd_s16x16_and_scalar_
//	#define _simd_s16x16_and_scalar(X,Y) _simd_s16x16_and_scalar_(X,Y)
//	#define _simd_s16x16_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_and_scalar_instruction_set>()
//#else
//	#define _simd_s16x16_and_scalar(X,Y) _simd_s16x16_and_safe(X,_simd_s16x16_fill_scalar_safe(Y))
//	#define _simd_s16x16_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_s16x1_and_safe
//	#define _simd_s16x1_and_safe(X,Y) (X & Y)
//	#define _simd_s16x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_s16x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_and_enabled() true
//#endif
//
//#define _simd_s16x32_and_safe(X,Y)_simd_s16x32_combine_safe(\
//	_simd_s16x16_and_safe(_simd_s16x32_splitlo_safe(X), _simd_ s16x32_splitlo_safe(Y)),\
//	_simd_s16x16_and_safe(_simd_s16x32_splithi_safe(X), _simd_ s16x32_splithi_safe(Y)))
//#ifdef _simd_s16x32_and_
//	#define _simd_s16x32_and(X,Y) _simd_s16x32_and_(X, Y)
//	#define _simd_s16x32_and_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_and_instruction_set>()
//#elif defined(_simd_s16x64_and_)
//	static ANVIL_STRONG_INLINE _simd_s16x32 ANVIL_SIMD_CALL _simd_s16x32_and(const register _simd_s16x32 x, const register _simd_s16x32 y) {
//		union SIMDUnion { _simd_s16x32 v1; _simd_s16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x32_and_enable() _simd_s16x64_and_enable()
//#else
//	#define _simd_s16x32_and(X,Y) _simd_s16x32_combine(\
//		_simd_s16x16_and(_simd_s16x32_splitlo(X), _simd_s16x32_splitlo(Y)),\
//		_simd_s16x16_and(_simd_s16x32_splithi(X), _simd_s16x32_splithi(Y)))
//	#define _simd_s16x32_and_enable() (_simd_s16x16_and_enable() && _simd_s16x32_combine_enable() && _simd_s16x32_splitlo_enable()  && _simd_s16x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x32_and_) && ! defined(_simd_s16x32_and_scalar_)
//	#define _simd_s16x32_and_scalar_(X,Y) _simd_s16x32_and_(X,_simd_s16x32_fill_scalar_(Y))
//	#define _simd_s16x32_and_scalar_instruction_set _simd_s16x32_and_instruction_set
//#endif
//#ifdef _simd_s16x32_and_scalar_
//	#define _simd_s16x32_and_scalar(X,Y) _simd_s16x32_and_scalar_(X,Y)
//	#define _simd_s16x32_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_and_scalar_instruction_set>()
//#else
//	#define _simd_s16x32_and_scalar(X,Y) _simd_s16x32_and_safe(X,_simd_s16x32_fill_scalar_safe(Y))
//	#define _simd_s16x32_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_s16x1_and_safe
//	#define _simd_s16x1_and_safe(X,Y) (X & Y)
//	#define _simd_s16x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_s16x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_and_enabled() true
//#endif
//
//#define _simd_s16x64_and_safe(X,Y)_simd_s16x64_combine_safe(\
//	_simd_s16x32_and_safe(_simd_s16x64_splitlo_safe(X), _simd_ s16x64_splitlo_safe(Y)),\
//	_simd_s16x32_and_safe(_simd_s16x64_splithi_safe(X), _simd_ s16x64_splithi_safe(Y)))
//#ifdef _simd_s16x64_and_
//	#define _simd_s16x64_and(X,Y) _simd_s16x64_and_(X, Y)
//	#define _simd_s16x64_and_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_and_instruction_set>()
//#else
//	#define _simd_s16x64_and(X,Y) _simd_s16x64_combine(\
//		_simd_s16x32_and(_simd_s16x64_splitlo(X), _simd_s16x64_splitlo(Y)),\
//		_simd_s16x32_and(_simd_s16x64_splithi(X), _simd_s16x64_splithi(Y)))
//	#define _simd_s16x64_and_enable() (_simd_s16x32_and_enable() && _simd_s16x64_combine_enable() && _simd_s16x64_splitlo_enable()  && _simd_s16x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x64_and_) && ! defined(_simd_s16x64_and_scalar_)
//	#define _simd_s16x64_and_scalar_(X,Y) _simd_s16x64_and_(X,_simd_s16x64_fill_scalar_(Y))
//	#define _simd_s16x64_and_scalar_instruction_set _simd_s16x64_and_instruction_set
//#endif
//#ifdef _simd_s16x64_and_scalar_
//	#define _simd_s16x64_and_scalar(X,Y) _simd_s16x64_and_scalar_(X,Y)
//	#define _simd_s16x64_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_and_scalar_instruction_set>()
//#else
//	#define _simd_s16x64_and_scalar(X,Y) _simd_s16x64_and_safe(X,_simd_s16x64_fill_scalar_safe(Y))
//	#define _simd_s16x64_and_scalar_enabled() true
//#endif
//
//// -- u16 --
//
//#ifndef _simd_u16x1_and_safe
//	#define _simd_u16x1_and_safe(X,Y) (X & Y)
//	#define _simd_u16x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_u16x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_and_enabled() true
//#endif
//
//#define _simd_u16x2_and_safe(X,Y)_simd_u16x2_combine_safe(\
//	_simd_u16x1_and_safe(_simd_u16x2_splitlo_safe(X), _simd_ u16x2_splitlo_safe(Y)),\
//	_simd_u16x1_and_safe(_simd_u16x2_splithi_safe(X), _simd_ u16x2_splithi_safe(Y)))
//#ifdef _simd_u16x2_and_
//	#define _simd_u16x2_and(X,Y) _simd_u16x2_and_(X, Y)
//	#define _simd_u16x2_and_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_and_instruction_set>()
//#elif defined(_simd_u16x4_and_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_and(const register _simd_u16x2 x, const register _simd_u16x2 y) {
//		union SIMDUnion { _simd_u16x2 v1; _simd_u16x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x4_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x2_and_enable() _simd_u16x4_and_enable()
//#elif defined(_simd_u16x8_and_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_and(const register _simd_u16x2 x, const register _simd_u16x2 y) {
//		union SIMDUnion { _simd_u16x2 v1; _simd_u16x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x8_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x2_and_enable() _simd_u16x8_and_enable()
//#elif defined(_simd_u16x16_and_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_and(const register _simd_u16x2 x, const register _simd_u16x2 y) {
//		union SIMDUnion { _simd_u16x2 v1; _simd_u16x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x16_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x2_and_enable() _simd_u16x16_and_enable()
//#elif defined(_simd_u16x32_and_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_and(const register _simd_u16x2 x, const register _simd_u16x2 y) {
//		union SIMDUnion { _simd_u16x2 v1; _simd_u16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x2_and_enable() _simd_u16x32_and_enable()
//#elif defined(_simd_u16x64_and_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_and(const register _simd_u16x2 x, const register _simd_u16x2 y) {
//		union SIMDUnion { _simd_u16x2 v1; _simd_u16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x2_and_enable() _simd_u16x64_and_enable()
//#else
//	#define _simd_u16x2_and(X,Y) _simd_u16x2_combine(\
//		_simd_u16x1_and(_simd_u16x2_splitlo(X), _simd_u16x2_splitlo(Y)),\
//		_simd_u16x1_and(_simd_u16x2_splithi(X), _simd_u16x2_splithi(Y)))
//	#define _simd_u16x2_and_enable() (_simd_u16x1_and_enable() && _simd_u16x2_combine_enable() && _simd_u16x2_splitlo_enable()  && _simd_u16x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x2_and_) && ! defined(_simd_u16x2_and_scalar_)
//	#define _simd_u16x2_and_scalar_(X,Y) _simd_u16x2_and_(X,_simd_u16x2_fill_scalar_(Y))
//	#define _simd_u16x2_and_scalar_instruction_set _simd_u16x2_and_instruction_set
//#endif
//#ifdef _simd_u16x2_and_scalar_
//	#define _simd_u16x2_and_scalar(X,Y) _simd_u16x2_and_scalar_(X,Y)
//	#define _simd_u16x2_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_and_scalar_instruction_set>()
//#else
//	#define _simd_u16x2_and_scalar(X,Y) _simd_u16x2_and_safe(X,_simd_u16x2_fill_scalar_safe(Y))
//	#define _simd_u16x2_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_u16x1_and_safe
//	#define _simd_u16x1_and_safe(X,Y) (X & Y)
//	#define _simd_u16x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_u16x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_and_enabled() true
//#endif
//
//#define _simd_u16x4_and_safe(X,Y)_simd_u16x4_combine_safe(\
//	_simd_u16x2_and_safe(_simd_u16x4_splitlo_safe(X), _simd_ u16x4_splitlo_safe(Y)),\
//	_simd_u16x2_and_safe(_simd_u16x4_splithi_safe(X), _simd_ u16x4_splithi_safe(Y)))
//#ifdef _simd_u16x4_and_
//	#define _simd_u16x4_and(X,Y) _simd_u16x4_and_(X, Y)
//	#define _simd_u16x4_and_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_and_instruction_set>()
//#elif defined(_simd_u16x8_and_)
//	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_and(const register _simd_u16x4 x, const register _simd_u16x4 y) {
//		union SIMDUnion { _simd_u16x4 v1; _simd_u16x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x8_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x4_and_enable() _simd_u16x8_and_enable()
//#elif defined(_simd_u16x16_and_)
//	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_and(const register _simd_u16x4 x, const register _simd_u16x4 y) {
//		union SIMDUnion { _simd_u16x4 v1; _simd_u16x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x16_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x4_and_enable() _simd_u16x16_and_enable()
//#elif defined(_simd_u16x32_and_)
//	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_and(const register _simd_u16x4 x, const register _simd_u16x4 y) {
//		union SIMDUnion { _simd_u16x4 v1; _simd_u16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x4_and_enable() _simd_u16x32_and_enable()
//#elif defined(_simd_u16x64_and_)
//	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_and(const register _simd_u16x4 x, const register _simd_u16x4 y) {
//		union SIMDUnion { _simd_u16x4 v1; _simd_u16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x4_and_enable() _simd_u16x64_and_enable()
//#else
//	#define _simd_u16x4_and(X,Y) _simd_u16x4_combine(\
//		_simd_u16x2_and(_simd_u16x4_splitlo(X), _simd_u16x4_splitlo(Y)),\
//		_simd_u16x2_and(_simd_u16x4_splithi(X), _simd_u16x4_splithi(Y)))
//	#define _simd_u16x4_and_enable() (_simd_u16x2_and_enable() && _simd_u16x4_combine_enable() && _simd_u16x4_splitlo_enable()  && _simd_u16x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x4_and_) && ! defined(_simd_u16x4_and_scalar_)
//	#define _simd_u16x4_and_scalar_(X,Y) _simd_u16x4_and_(X,_simd_u16x4_fill_scalar_(Y))
//	#define _simd_u16x4_and_scalar_instruction_set _simd_u16x4_and_instruction_set
//#endif
//#ifdef _simd_u16x4_and_scalar_
//	#define _simd_u16x4_and_scalar(X,Y) _simd_u16x4_and_scalar_(X,Y)
//	#define _simd_u16x4_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_and_scalar_instruction_set>()
//#else
//	#define _simd_u16x4_and_scalar(X,Y) _simd_u16x4_and_safe(X,_simd_u16x4_fill_scalar_safe(Y))
//	#define _simd_u16x4_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_u16x1_and_safe
//	#define _simd_u16x1_and_safe(X,Y) (X & Y)
//	#define _simd_u16x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_u16x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_and_enabled() true
//#endif
//
//#define _simd_u16x8_and_safe(X,Y)_simd_u16x8_combine_safe(\
//	_simd_u16x4_and_safe(_simd_u16x8_splitlo_safe(X), _simd_ u16x8_splitlo_safe(Y)),\
//	_simd_u16x4_and_safe(_simd_u16x8_splithi_safe(X), _simd_ u16x8_splithi_safe(Y)))
//#ifdef _simd_u16x8_and_
//	#define _simd_u16x8_and(X,Y) _simd_u16x8_and_(X, Y)
//	#define _simd_u16x8_and_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_and_instruction_set>()
//#elif defined(_simd_u16x16_and_)
//	static ANVIL_STRONG_INLINE _simd_u16x8 ANVIL_SIMD_CALL _simd_u16x8_and(const register _simd_u16x8 x, const register _simd_u16x8 y) {
//		union SIMDUnion { _simd_u16x8 v1; _simd_u16x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x16_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x8_and_enable() _simd_u16x16_and_enable()
//#elif defined(_simd_u16x32_and_)
//	static ANVIL_STRONG_INLINE _simd_u16x8 ANVIL_SIMD_CALL _simd_u16x8_and(const register _simd_u16x8 x, const register _simd_u16x8 y) {
//		union SIMDUnion { _simd_u16x8 v1; _simd_u16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x8_and_enable() _simd_u16x32_and_enable()
//#elif defined(_simd_u16x64_and_)
//	static ANVIL_STRONG_INLINE _simd_u16x8 ANVIL_SIMD_CALL _simd_u16x8_and(const register _simd_u16x8 x, const register _simd_u16x8 y) {
//		union SIMDUnion { _simd_u16x8 v1; _simd_u16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x8_and_enable() _simd_u16x64_and_enable()
//#else
//	#define _simd_u16x8_and(X,Y) _simd_u16x8_combine(\
//		_simd_u16x4_and(_simd_u16x8_splitlo(X), _simd_u16x8_splitlo(Y)),\
//		_simd_u16x4_and(_simd_u16x8_splithi(X), _simd_u16x8_splithi(Y)))
//	#define _simd_u16x8_and_enable() (_simd_u16x4_and_enable() && _simd_u16x8_combine_enable() && _simd_u16x8_splitlo_enable()  && _simd_u16x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x8_and_) && ! defined(_simd_u16x8_and_scalar_)
//	#define _simd_u16x8_and_scalar_(X,Y) _simd_u16x8_and_(X,_simd_u16x8_fill_scalar_(Y))
//	#define _simd_u16x8_and_scalar_instruction_set _simd_u16x8_and_instruction_set
//#endif
//#ifdef _simd_u16x8_and_scalar_
//	#define _simd_u16x8_and_scalar(X,Y) _simd_u16x8_and_scalar_(X,Y)
//	#define _simd_u16x8_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_and_scalar_instruction_set>()
//#else
//	#define _simd_u16x8_and_scalar(X,Y) _simd_u16x8_and_safe(X,_simd_u16x8_fill_scalar_safe(Y))
//	#define _simd_u16x8_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_u16x1_and_safe
//	#define _simd_u16x1_and_safe(X,Y) (X & Y)
//	#define _simd_u16x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_u16x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_and_enabled() true
//#endif
//
//#define _simd_u16x16_and_safe(X,Y)_simd_u16x16_combine_safe(\
//	_simd_u16x8_and_safe(_simd_u16x16_splitlo_safe(X), _simd_ u16x16_splitlo_safe(Y)),\
//	_simd_u16x8_and_safe(_simd_u16x16_splithi_safe(X), _simd_ u16x16_splithi_safe(Y)))
//#ifdef _simd_u16x16_and_
//	#define _simd_u16x16_and(X,Y) _simd_u16x16_and_(X, Y)
//	#define _simd_u16x16_and_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_and_instruction_set>()
//#elif defined(_simd_u16x32_and_)
//	static ANVIL_STRONG_INLINE _simd_u16x16 ANVIL_SIMD_CALL _simd_u16x16_and(const register _simd_u16x16 x, const register _simd_u16x16 y) {
//		union SIMDUnion { _simd_u16x16 v1; _simd_u16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x16_and_enable() _simd_u16x32_and_enable()
//#elif defined(_simd_u16x64_and_)
//	static ANVIL_STRONG_INLINE _simd_u16x16 ANVIL_SIMD_CALL _simd_u16x16_and(const register _simd_u16x16 x, const register _simd_u16x16 y) {
//		union SIMDUnion { _simd_u16x16 v1; _simd_u16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x16_and_enable() _simd_u16x64_and_enable()
//#else
//	#define _simd_u16x16_and(X,Y) _simd_u16x16_combine(\
//		_simd_u16x8_and(_simd_u16x16_splitlo(X), _simd_u16x16_splitlo(Y)),\
//		_simd_u16x8_and(_simd_u16x16_splithi(X), _simd_u16x16_splithi(Y)))
//	#define _simd_u16x16_and_enable() (_simd_u16x8_and_enable() && _simd_u16x16_combine_enable() && _simd_u16x16_splitlo_enable()  && _simd_u16x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x16_and_) && ! defined(_simd_u16x16_and_scalar_)
//	#define _simd_u16x16_and_scalar_(X,Y) _simd_u16x16_and_(X,_simd_u16x16_fill_scalar_(Y))
//	#define _simd_u16x16_and_scalar_instruction_set _simd_u16x16_and_instruction_set
//#endif
//#ifdef _simd_u16x16_and_scalar_
//	#define _simd_u16x16_and_scalar(X,Y) _simd_u16x16_and_scalar_(X,Y)
//	#define _simd_u16x16_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_and_scalar_instruction_set>()
//#else
//	#define _simd_u16x16_and_scalar(X,Y) _simd_u16x16_and_safe(X,_simd_u16x16_fill_scalar_safe(Y))
//	#define _simd_u16x16_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_u16x1_and_safe
//	#define _simd_u16x1_and_safe(X,Y) (X & Y)
//	#define _simd_u16x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_u16x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_and_enabled() true
//#endif
//
//#define _simd_u16x32_and_safe(X,Y)_simd_u16x32_combine_safe(\
//	_simd_u16x16_and_safe(_simd_u16x32_splitlo_safe(X), _simd_ u16x32_splitlo_safe(Y)),\
//	_simd_u16x16_and_safe(_simd_u16x32_splithi_safe(X), _simd_ u16x32_splithi_safe(Y)))
//#ifdef _simd_u16x32_and_
//	#define _simd_u16x32_and(X,Y) _simd_u16x32_and_(X, Y)
//	#define _simd_u16x32_and_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_and_instruction_set>()
//#elif defined(_simd_u16x64_and_)
//	static ANVIL_STRONG_INLINE _simd_u16x32 ANVIL_SIMD_CALL _simd_u16x32_and(const register _simd_u16x32 x, const register _simd_u16x32 y) {
//		union SIMDUnion { _simd_u16x32 v1; _simd_u16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x32_and_enable() _simd_u16x64_and_enable()
//#else
//	#define _simd_u16x32_and(X,Y) _simd_u16x32_combine(\
//		_simd_u16x16_and(_simd_u16x32_splitlo(X), _simd_u16x32_splitlo(Y)),\
//		_simd_u16x16_and(_simd_u16x32_splithi(X), _simd_u16x32_splithi(Y)))
//	#define _simd_u16x32_and_enable() (_simd_u16x16_and_enable() && _simd_u16x32_combine_enable() && _simd_u16x32_splitlo_enable()  && _simd_u16x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x32_and_) && ! defined(_simd_u16x32_and_scalar_)
//	#define _simd_u16x32_and_scalar_(X,Y) _simd_u16x32_and_(X,_simd_u16x32_fill_scalar_(Y))
//	#define _simd_u16x32_and_scalar_instruction_set _simd_u16x32_and_instruction_set
//#endif
//#ifdef _simd_u16x32_and_scalar_
//	#define _simd_u16x32_and_scalar(X,Y) _simd_u16x32_and_scalar_(X,Y)
//	#define _simd_u16x32_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_and_scalar_instruction_set>()
//#else
//	#define _simd_u16x32_and_scalar(X,Y) _simd_u16x32_and_safe(X,_simd_u16x32_fill_scalar_safe(Y))
//	#define _simd_u16x32_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_u16x1_and_safe
//	#define _simd_u16x1_and_safe(X,Y) (X & Y)
//	#define _simd_u16x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_u16x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_and_enabled() true
//#endif
//
//#define _simd_u16x64_and_safe(X,Y)_simd_u16x64_combine_safe(\
//	_simd_u16x32_and_safe(_simd_u16x64_splitlo_safe(X), _simd_ u16x64_splitlo_safe(Y)),\
//	_simd_u16x32_and_safe(_simd_u16x64_splithi_safe(X), _simd_ u16x64_splithi_safe(Y)))
//#ifdef _simd_u16x64_and_
//	#define _simd_u16x64_and(X,Y) _simd_u16x64_and_(X, Y)
//	#define _simd_u16x64_and_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_and_instruction_set>()
//#else
//	#define _simd_u16x64_and(X,Y) _simd_u16x64_combine(\
//		_simd_u16x32_and(_simd_u16x64_splitlo(X), _simd_u16x64_splitlo(Y)),\
//		_simd_u16x32_and(_simd_u16x64_splithi(X), _simd_u16x64_splithi(Y)))
//	#define _simd_u16x64_and_enable() (_simd_u16x32_and_enable() && _simd_u16x64_combine_enable() && _simd_u16x64_splitlo_enable()  && _simd_u16x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x64_and_) && ! defined(_simd_u16x64_and_scalar_)
//	#define _simd_u16x64_and_scalar_(X,Y) _simd_u16x64_and_(X,_simd_u16x64_fill_scalar_(Y))
//	#define _simd_u16x64_and_scalar_instruction_set _simd_u16x64_and_instruction_set
//#endif
//#ifdef _simd_u16x64_and_scalar_
//	#define _simd_u16x64_and_scalar(X,Y) _simd_u16x64_and_scalar_(X,Y)
//	#define _simd_u16x64_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_and_scalar_instruction_set>()
//#else
//	#define _simd_u16x64_and_scalar(X,Y) _simd_u16x64_and_safe(X,_simd_u16x64_fill_scalar_safe(Y))
//	#define _simd_u16x64_and_scalar_enabled() true
//#endif
//
//// -- s8 --
//
//#ifndef _simd_s8x1_and_safe
//	#define _simd_s8x1_and_safe(X,Y) (X & Y)
//	#define _simd_s8x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_s8x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_and_enabled() true
//#endif
//
//#define _simd_s8x2_and_safe(X,Y)_simd_s8x2_combine_safe(\
//	_simd_s8x1_and_safe(_simd_s8x2_splitlo_safe(X), _simd_ s8x2_splitlo_safe(Y)),\
//	_simd_s8x1_and_safe(_simd_s8x2_splithi_safe(X), _simd_ s8x2_splithi_safe(Y)))
//#ifdef _simd_s8x2_and_
//	#define _simd_s8x2_and(X,Y) _simd_s8x2_and_(X, Y)
//	#define _simd_s8x2_and_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_and_instruction_set>()
//#elif defined(_simd_s8x4_and_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_and(const register _simd_s8x2 x, const register _simd_s8x2 y) {
//		union SIMDUnion { _simd_s8x2 v1; _simd_s8x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x4_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x2_and_enable() _simd_s8x4_and_enable()
//#elif defined(_simd_s8x8_and_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_and(const register _simd_s8x2 x, const register _simd_s8x2 y) {
//		union SIMDUnion { _simd_s8x2 v1; _simd_s8x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x8_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x2_and_enable() _simd_s8x8_and_enable()
//#elif defined(_simd_s8x16_and_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_and(const register _simd_s8x2 x, const register _simd_s8x2 y) {
//		union SIMDUnion { _simd_s8x2 v1; _simd_s8x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x16_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x2_and_enable() _simd_s8x16_and_enable()
//#elif defined(_simd_s8x32_and_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_and(const register _simd_s8x2 x, const register _simd_s8x2 y) {
//		union SIMDUnion { _simd_s8x2 v1; _simd_s8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x2_and_enable() _simd_s8x32_and_enable()
//#elif defined(_simd_s8x64_and_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_and(const register _simd_s8x2 x, const register _simd_s8x2 y) {
//		union SIMDUnion { _simd_s8x2 v1; _simd_s8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x2_and_enable() _simd_s8x64_and_enable()
//#else
//	#define _simd_s8x2_and(X,Y) _simd_s8x2_combine(\
//		_simd_s8x1_and(_simd_s8x2_splitlo(X), _simd_s8x2_splitlo(Y)),\
//		_simd_s8x1_and(_simd_s8x2_splithi(X), _simd_s8x2_splithi(Y)))
//	#define _simd_s8x2_and_enable() (_simd_s8x1_and_enable() && _simd_s8x2_combine_enable() && _simd_s8x2_splitlo_enable()  && _simd_s8x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x2_and_) && ! defined(_simd_s8x2_and_scalar_)
//	#define _simd_s8x2_and_scalar_(X,Y) _simd_s8x2_and_(X,_simd_s8x2_fill_scalar_(Y))
//	#define _simd_s8x2_and_scalar_instruction_set _simd_s8x2_and_instruction_set
//#endif
//#ifdef _simd_s8x2_and_scalar_
//	#define _simd_s8x2_and_scalar(X,Y) _simd_s8x2_and_scalar_(X,Y)
//	#define _simd_s8x2_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_and_scalar_instruction_set>()
//#else
//	#define _simd_s8x2_and_scalar(X,Y) _simd_s8x2_and_safe(X,_simd_s8x2_fill_scalar_safe(Y))
//	#define _simd_s8x2_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_s8x1_and_safe
//	#define _simd_s8x1_and_safe(X,Y) (X & Y)
//	#define _simd_s8x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_s8x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_and_enabled() true
//#endif
//
//#define _simd_s8x4_and_safe(X,Y)_simd_s8x4_combine_safe(\
//	_simd_s8x2_and_safe(_simd_s8x4_splitlo_safe(X), _simd_ s8x4_splitlo_safe(Y)),\
//	_simd_s8x2_and_safe(_simd_s8x4_splithi_safe(X), _simd_ s8x4_splithi_safe(Y)))
//#ifdef _simd_s8x4_and_
//	#define _simd_s8x4_and(X,Y) _simd_s8x4_and_(X, Y)
//	#define _simd_s8x4_and_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_and_instruction_set>()
//#elif defined(_simd_s8x8_and_)
//	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_and(const register _simd_s8x4 x, const register _simd_s8x4 y) {
//		union SIMDUnion { _simd_s8x4 v1; _simd_s8x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x8_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x4_and_enable() _simd_s8x8_and_enable()
//#elif defined(_simd_s8x16_and_)
//	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_and(const register _simd_s8x4 x, const register _simd_s8x4 y) {
//		union SIMDUnion { _simd_s8x4 v1; _simd_s8x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x16_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x4_and_enable() _simd_s8x16_and_enable()
//#elif defined(_simd_s8x32_and_)
//	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_and(const register _simd_s8x4 x, const register _simd_s8x4 y) {
//		union SIMDUnion { _simd_s8x4 v1; _simd_s8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x4_and_enable() _simd_s8x32_and_enable()
//#elif defined(_simd_s8x64_and_)
//	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_and(const register _simd_s8x4 x, const register _simd_s8x4 y) {
//		union SIMDUnion { _simd_s8x4 v1; _simd_s8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x4_and_enable() _simd_s8x64_and_enable()
//#else
//	#define _simd_s8x4_and(X,Y) _simd_s8x4_combine(\
//		_simd_s8x2_and(_simd_s8x4_splitlo(X), _simd_s8x4_splitlo(Y)),\
//		_simd_s8x2_and(_simd_s8x4_splithi(X), _simd_s8x4_splithi(Y)))
//	#define _simd_s8x4_and_enable() (_simd_s8x2_and_enable() && _simd_s8x4_combine_enable() && _simd_s8x4_splitlo_enable()  && _simd_s8x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x4_and_) && ! defined(_simd_s8x4_and_scalar_)
//	#define _simd_s8x4_and_scalar_(X,Y) _simd_s8x4_and_(X,_simd_s8x4_fill_scalar_(Y))
//	#define _simd_s8x4_and_scalar_instruction_set _simd_s8x4_and_instruction_set
//#endif
//#ifdef _simd_s8x4_and_scalar_
//	#define _simd_s8x4_and_scalar(X,Y) _simd_s8x4_and_scalar_(X,Y)
//	#define _simd_s8x4_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_and_scalar_instruction_set>()
//#else
//	#define _simd_s8x4_and_scalar(X,Y) _simd_s8x4_and_safe(X,_simd_s8x4_fill_scalar_safe(Y))
//	#define _simd_s8x4_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_s8x1_and_safe
//	#define _simd_s8x1_and_safe(X,Y) (X & Y)
//	#define _simd_s8x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_s8x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_and_enabled() true
//#endif
//
//#define _simd_s8x8_and_safe(X,Y)_simd_s8x8_combine_safe(\
//	_simd_s8x4_and_safe(_simd_s8x8_splitlo_safe(X), _simd_ s8x8_splitlo_safe(Y)),\
//	_simd_s8x4_and_safe(_simd_s8x8_splithi_safe(X), _simd_ s8x8_splithi_safe(Y)))
//#ifdef _simd_s8x8_and_
//	#define _simd_s8x8_and(X,Y) _simd_s8x8_and_(X, Y)
//	#define _simd_s8x8_and_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_and_instruction_set>()
//#elif defined(_simd_s8x16_and_)
//	static ANVIL_STRONG_INLINE _simd_s8x8 ANVIL_SIMD_CALL _simd_s8x8_and(const register _simd_s8x8 x, const register _simd_s8x8 y) {
//		union SIMDUnion { _simd_s8x8 v1; _simd_s8x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x16_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x8_and_enable() _simd_s8x16_and_enable()
//#elif defined(_simd_s8x32_and_)
//	static ANVIL_STRONG_INLINE _simd_s8x8 ANVIL_SIMD_CALL _simd_s8x8_and(const register _simd_s8x8 x, const register _simd_s8x8 y) {
//		union SIMDUnion { _simd_s8x8 v1; _simd_s8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x8_and_enable() _simd_s8x32_and_enable()
//#elif defined(_simd_s8x64_and_)
//	static ANVIL_STRONG_INLINE _simd_s8x8 ANVIL_SIMD_CALL _simd_s8x8_and(const register _simd_s8x8 x, const register _simd_s8x8 y) {
//		union SIMDUnion { _simd_s8x8 v1; _simd_s8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x8_and_enable() _simd_s8x64_and_enable()
//#else
//	#define _simd_s8x8_and(X,Y) _simd_s8x8_combine(\
//		_simd_s8x4_and(_simd_s8x8_splitlo(X), _simd_s8x8_splitlo(Y)),\
//		_simd_s8x4_and(_simd_s8x8_splithi(X), _simd_s8x8_splithi(Y)))
//	#define _simd_s8x8_and_enable() (_simd_s8x4_and_enable() && _simd_s8x8_combine_enable() && _simd_s8x8_splitlo_enable()  && _simd_s8x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x8_and_) && ! defined(_simd_s8x8_and_scalar_)
//	#define _simd_s8x8_and_scalar_(X,Y) _simd_s8x8_and_(X,_simd_s8x8_fill_scalar_(Y))
//	#define _simd_s8x8_and_scalar_instruction_set _simd_s8x8_and_instruction_set
//#endif
//#ifdef _simd_s8x8_and_scalar_
//	#define _simd_s8x8_and_scalar(X,Y) _simd_s8x8_and_scalar_(X,Y)
//	#define _simd_s8x8_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_and_scalar_instruction_set>()
//#else
//	#define _simd_s8x8_and_scalar(X,Y) _simd_s8x8_and_safe(X,_simd_s8x8_fill_scalar_safe(Y))
//	#define _simd_s8x8_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_s8x1_and_safe
//	#define _simd_s8x1_and_safe(X,Y) (X & Y)
//	#define _simd_s8x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_s8x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_and_enabled() true
//#endif
//
//#define _simd_s8x16_and_safe(X,Y)_simd_s8x16_combine_safe(\
//	_simd_s8x8_and_safe(_simd_s8x16_splitlo_safe(X), _simd_ s8x16_splitlo_safe(Y)),\
//	_simd_s8x8_and_safe(_simd_s8x16_splithi_safe(X), _simd_ s8x16_splithi_safe(Y)))
//#ifdef _simd_s8x16_and_
//	#define _simd_s8x16_and(X,Y) _simd_s8x16_and_(X, Y)
//	#define _simd_s8x16_and_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_and_instruction_set>()
//#elif defined(_simd_s8x32_and_)
//	static ANVIL_STRONG_INLINE _simd_s8x16 ANVIL_SIMD_CALL _simd_s8x16_and(const register _simd_s8x16 x, const register _simd_s8x16 y) {
//		union SIMDUnion { _simd_s8x16 v1; _simd_s8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x16_and_enable() _simd_s8x32_and_enable()
//#elif defined(_simd_s8x64_and_)
//	static ANVIL_STRONG_INLINE _simd_s8x16 ANVIL_SIMD_CALL _simd_s8x16_and(const register _simd_s8x16 x, const register _simd_s8x16 y) {
//		union SIMDUnion { _simd_s8x16 v1; _simd_s8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x16_and_enable() _simd_s8x64_and_enable()
//#else
//	#define _simd_s8x16_and(X,Y) _simd_s8x16_combine(\
//		_simd_s8x8_and(_simd_s8x16_splitlo(X), _simd_s8x16_splitlo(Y)),\
//		_simd_s8x8_and(_simd_s8x16_splithi(X), _simd_s8x16_splithi(Y)))
//	#define _simd_s8x16_and_enable() (_simd_s8x8_and_enable() && _simd_s8x16_combine_enable() && _simd_s8x16_splitlo_enable()  && _simd_s8x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x16_and_) && ! defined(_simd_s8x16_and_scalar_)
//	#define _simd_s8x16_and_scalar_(X,Y) _simd_s8x16_and_(X,_simd_s8x16_fill_scalar_(Y))
//	#define _simd_s8x16_and_scalar_instruction_set _simd_s8x16_and_instruction_set
//#endif
//#ifdef _simd_s8x16_and_scalar_
//	#define _simd_s8x16_and_scalar(X,Y) _simd_s8x16_and_scalar_(X,Y)
//	#define _simd_s8x16_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_and_scalar_instruction_set>()
//#else
//	#define _simd_s8x16_and_scalar(X,Y) _simd_s8x16_and_safe(X,_simd_s8x16_fill_scalar_safe(Y))
//	#define _simd_s8x16_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_s8x1_and_safe
//	#define _simd_s8x1_and_safe(X,Y) (X & Y)
//	#define _simd_s8x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_s8x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_and_enabled() true
//#endif
//
//#define _simd_s8x32_and_safe(X,Y)_simd_s8x32_combine_safe(\
//	_simd_s8x16_and_safe(_simd_s8x32_splitlo_safe(X), _simd_ s8x32_splitlo_safe(Y)),\
//	_simd_s8x16_and_safe(_simd_s8x32_splithi_safe(X), _simd_ s8x32_splithi_safe(Y)))
//#ifdef _simd_s8x32_and_
//	#define _simd_s8x32_and(X,Y) _simd_s8x32_and_(X, Y)
//	#define _simd_s8x32_and_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_and_instruction_set>()
//#elif defined(_simd_s8x64_and_)
//	static ANVIL_STRONG_INLINE _simd_s8x32 ANVIL_SIMD_CALL _simd_s8x32_and(const register _simd_s8x32 x, const register _simd_s8x32 y) {
//		union SIMDUnion { _simd_s8x32 v1; _simd_s8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x32_and_enable() _simd_s8x64_and_enable()
//#else
//	#define _simd_s8x32_and(X,Y) _simd_s8x32_combine(\
//		_simd_s8x16_and(_simd_s8x32_splitlo(X), _simd_s8x32_splitlo(Y)),\
//		_simd_s8x16_and(_simd_s8x32_splithi(X), _simd_s8x32_splithi(Y)))
//	#define _simd_s8x32_and_enable() (_simd_s8x16_and_enable() && _simd_s8x32_combine_enable() && _simd_s8x32_splitlo_enable()  && _simd_s8x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x32_and_) && ! defined(_simd_s8x32_and_scalar_)
//	#define _simd_s8x32_and_scalar_(X,Y) _simd_s8x32_and_(X,_simd_s8x32_fill_scalar_(Y))
//	#define _simd_s8x32_and_scalar_instruction_set _simd_s8x32_and_instruction_set
//#endif
//#ifdef _simd_s8x32_and_scalar_
//	#define _simd_s8x32_and_scalar(X,Y) _simd_s8x32_and_scalar_(X,Y)
//	#define _simd_s8x32_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_and_scalar_instruction_set>()
//#else
//	#define _simd_s8x32_and_scalar(X,Y) _simd_s8x32_and_safe(X,_simd_s8x32_fill_scalar_safe(Y))
//	#define _simd_s8x32_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_s8x1_and_safe
//	#define _simd_s8x1_and_safe(X,Y) (X & Y)
//	#define _simd_s8x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_s8x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_and_enabled() true
//#endif
//
//#define _simd_s8x64_and_safe(X,Y)_simd_s8x64_combine_safe(\
//	_simd_s8x32_and_safe(_simd_s8x64_splitlo_safe(X), _simd_ s8x64_splitlo_safe(Y)),\
//	_simd_s8x32_and_safe(_simd_s8x64_splithi_safe(X), _simd_ s8x64_splithi_safe(Y)))
//#ifdef _simd_s8x64_and_
//	#define _simd_s8x64_and(X,Y) _simd_s8x64_and_(X, Y)
//	#define _simd_s8x64_and_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_and_instruction_set>()
//#else
//	#define _simd_s8x64_and(X,Y) _simd_s8x64_combine(\
//		_simd_s8x32_and(_simd_s8x64_splitlo(X), _simd_s8x64_splitlo(Y)),\
//		_simd_s8x32_and(_simd_s8x64_splithi(X), _simd_s8x64_splithi(Y)))
//	#define _simd_s8x64_and_enable() (_simd_s8x32_and_enable() && _simd_s8x64_combine_enable() && _simd_s8x64_splitlo_enable()  && _simd_s8x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x64_and_) && ! defined(_simd_s8x64_and_scalar_)
//	#define _simd_s8x64_and_scalar_(X,Y) _simd_s8x64_and_(X,_simd_s8x64_fill_scalar_(Y))
//	#define _simd_s8x64_and_scalar_instruction_set _simd_s8x64_and_instruction_set
//#endif
//#ifdef _simd_s8x64_and_scalar_
//	#define _simd_s8x64_and_scalar(X,Y) _simd_s8x64_and_scalar_(X,Y)
//	#define _simd_s8x64_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_and_scalar_instruction_set>()
//#else
//	#define _simd_s8x64_and_scalar(X,Y) _simd_s8x64_and_safe(X,_simd_s8x64_fill_scalar_safe(Y))
//	#define _simd_s8x64_and_scalar_enabled() true
//#endif
//
//// -- u8 --
//
//#ifndef _simd_u8x1_and_safe
//	#define _simd_u8x1_and_safe(X,Y) (X & Y)
//	#define _simd_u8x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_u8x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_and_enabled() true
//#endif
//
//#define _simd_u8x2_and_safe(X,Y)_simd_u8x2_combine_safe(\
//	_simd_u8x1_and_safe(_simd_u8x2_splitlo_safe(X), _simd_ u8x2_splitlo_safe(Y)),\
//	_simd_u8x1_and_safe(_simd_u8x2_splithi_safe(X), _simd_ u8x2_splithi_safe(Y)))
//#ifdef _simd_u8x2_and_
//	#define _simd_u8x2_and(X,Y) _simd_u8x2_and_(X, Y)
//	#define _simd_u8x2_and_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_and_instruction_set>()
//#elif defined(_simd_u8x4_and_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_and(const register _simd_u8x2 x, const register _simd_u8x2 y) {
//		union SIMDUnion { _simd_u8x2 v1; _simd_u8x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x4_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x2_and_enable() _simd_u8x4_and_enable()
//#elif defined(_simd_u8x8_and_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_and(const register _simd_u8x2 x, const register _simd_u8x2 y) {
//		union SIMDUnion { _simd_u8x2 v1; _simd_u8x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x8_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x2_and_enable() _simd_u8x8_and_enable()
//#elif defined(_simd_u8x16_and_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_and(const register _simd_u8x2 x, const register _simd_u8x2 y) {
//		union SIMDUnion { _simd_u8x2 v1; _simd_u8x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x16_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x2_and_enable() _simd_u8x16_and_enable()
//#elif defined(_simd_u8x32_and_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_and(const register _simd_u8x2 x, const register _simd_u8x2 y) {
//		union SIMDUnion { _simd_u8x2 v1; _simd_u8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x2_and_enable() _simd_u8x32_and_enable()
//#elif defined(_simd_u8x64_and_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_and(const register _simd_u8x2 x, const register _simd_u8x2 y) {
//		union SIMDUnion { _simd_u8x2 v1; _simd_u8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x2_and_enable() _simd_u8x64_and_enable()
//#else
//	#define _simd_u8x2_and(X,Y) _simd_u8x2_combine(\
//		_simd_u8x1_and(_simd_u8x2_splitlo(X), _simd_u8x2_splitlo(Y)),\
//		_simd_u8x1_and(_simd_u8x2_splithi(X), _simd_u8x2_splithi(Y)))
//	#define _simd_u8x2_and_enable() (_simd_u8x1_and_enable() && _simd_u8x2_combine_enable() && _simd_u8x2_splitlo_enable()  && _simd_u8x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x2_and_) && ! defined(_simd_u8x2_and_scalar_)
//	#define _simd_u8x2_and_scalar_(X,Y) _simd_u8x2_and_(X,_simd_u8x2_fill_scalar_(Y))
//	#define _simd_u8x2_and_scalar_instruction_set _simd_u8x2_and_instruction_set
//#endif
//#ifdef _simd_u8x2_and_scalar_
//	#define _simd_u8x2_and_scalar(X,Y) _simd_u8x2_and_scalar_(X,Y)
//	#define _simd_u8x2_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_and_scalar_instruction_set>()
//#else
//	#define _simd_u8x2_and_scalar(X,Y) _simd_u8x2_and_safe(X,_simd_u8x2_fill_scalar_safe(Y))
//	#define _simd_u8x2_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_u8x1_and_safe
//	#define _simd_u8x1_and_safe(X,Y) (X & Y)
//	#define _simd_u8x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_u8x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_and_enabled() true
//#endif
//
//#define _simd_u8x4_and_safe(X,Y)_simd_u8x4_combine_safe(\
//	_simd_u8x2_and_safe(_simd_u8x4_splitlo_safe(X), _simd_ u8x4_splitlo_safe(Y)),\
//	_simd_u8x2_and_safe(_simd_u8x4_splithi_safe(X), _simd_ u8x4_splithi_safe(Y)))
//#ifdef _simd_u8x4_and_
//	#define _simd_u8x4_and(X,Y) _simd_u8x4_and_(X, Y)
//	#define _simd_u8x4_and_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_and_instruction_set>()
//#elif defined(_simd_u8x8_and_)
//	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_and(const register _simd_u8x4 x, const register _simd_u8x4 y) {
//		union SIMDUnion { _simd_u8x4 v1; _simd_u8x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x8_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x4_and_enable() _simd_u8x8_and_enable()
//#elif defined(_simd_u8x16_and_)
//	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_and(const register _simd_u8x4 x, const register _simd_u8x4 y) {
//		union SIMDUnion { _simd_u8x4 v1; _simd_u8x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x16_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x4_and_enable() _simd_u8x16_and_enable()
//#elif defined(_simd_u8x32_and_)
//	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_and(const register _simd_u8x4 x, const register _simd_u8x4 y) {
//		union SIMDUnion { _simd_u8x4 v1; _simd_u8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x4_and_enable() _simd_u8x32_and_enable()
//#elif defined(_simd_u8x64_and_)
//	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_and(const register _simd_u8x4 x, const register _simd_u8x4 y) {
//		union SIMDUnion { _simd_u8x4 v1; _simd_u8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x4_and_enable() _simd_u8x64_and_enable()
//#else
//	#define _simd_u8x4_and(X,Y) _simd_u8x4_combine(\
//		_simd_u8x2_and(_simd_u8x4_splitlo(X), _simd_u8x4_splitlo(Y)),\
//		_simd_u8x2_and(_simd_u8x4_splithi(X), _simd_u8x4_splithi(Y)))
//	#define _simd_u8x4_and_enable() (_simd_u8x2_and_enable() && _simd_u8x4_combine_enable() && _simd_u8x4_splitlo_enable()  && _simd_u8x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x4_and_) && ! defined(_simd_u8x4_and_scalar_)
//	#define _simd_u8x4_and_scalar_(X,Y) _simd_u8x4_and_(X,_simd_u8x4_fill_scalar_(Y))
//	#define _simd_u8x4_and_scalar_instruction_set _simd_u8x4_and_instruction_set
//#endif
//#ifdef _simd_u8x4_and_scalar_
//	#define _simd_u8x4_and_scalar(X,Y) _simd_u8x4_and_scalar_(X,Y)
//	#define _simd_u8x4_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_and_scalar_instruction_set>()
//#else
//	#define _simd_u8x4_and_scalar(X,Y) _simd_u8x4_and_safe(X,_simd_u8x4_fill_scalar_safe(Y))
//	#define _simd_u8x4_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_u8x1_and_safe
//	#define _simd_u8x1_and_safe(X,Y) (X & Y)
//	#define _simd_u8x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_u8x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_and_enabled() true
//#endif
//
//#define _simd_u8x8_and_safe(X,Y)_simd_u8x8_combine_safe(\
//	_simd_u8x4_and_safe(_simd_u8x8_splitlo_safe(X), _simd_ u8x8_splitlo_safe(Y)),\
//	_simd_u8x4_and_safe(_simd_u8x8_splithi_safe(X), _simd_ u8x8_splithi_safe(Y)))
//#ifdef _simd_u8x8_and_
//	#define _simd_u8x8_and(X,Y) _simd_u8x8_and_(X, Y)
//	#define _simd_u8x8_and_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_and_instruction_set>()
//#elif defined(_simd_u8x16_and_)
//	static ANVIL_STRONG_INLINE _simd_u8x8 ANVIL_SIMD_CALL _simd_u8x8_and(const register _simd_u8x8 x, const register _simd_u8x8 y) {
//		union SIMDUnion { _simd_u8x8 v1; _simd_u8x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x16_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x8_and_enable() _simd_u8x16_and_enable()
//#elif defined(_simd_u8x32_and_)
//	static ANVIL_STRONG_INLINE _simd_u8x8 ANVIL_SIMD_CALL _simd_u8x8_and(const register _simd_u8x8 x, const register _simd_u8x8 y) {
//		union SIMDUnion { _simd_u8x8 v1; _simd_u8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x8_and_enable() _simd_u8x32_and_enable()
//#elif defined(_simd_u8x64_and_)
//	static ANVIL_STRONG_INLINE _simd_u8x8 ANVIL_SIMD_CALL _simd_u8x8_and(const register _simd_u8x8 x, const register _simd_u8x8 y) {
//		union SIMDUnion { _simd_u8x8 v1; _simd_u8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x8_and_enable() _simd_u8x64_and_enable()
//#else
//	#define _simd_u8x8_and(X,Y) _simd_u8x8_combine(\
//		_simd_u8x4_and(_simd_u8x8_splitlo(X), _simd_u8x8_splitlo(Y)),\
//		_simd_u8x4_and(_simd_u8x8_splithi(X), _simd_u8x8_splithi(Y)))
//	#define _simd_u8x8_and_enable() (_simd_u8x4_and_enable() && _simd_u8x8_combine_enable() && _simd_u8x8_splitlo_enable()  && _simd_u8x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x8_and_) && ! defined(_simd_u8x8_and_scalar_)
//	#define _simd_u8x8_and_scalar_(X,Y) _simd_u8x8_and_(X,_simd_u8x8_fill_scalar_(Y))
//	#define _simd_u8x8_and_scalar_instruction_set _simd_u8x8_and_instruction_set
//#endif
//#ifdef _simd_u8x8_and_scalar_
//	#define _simd_u8x8_and_scalar(X,Y) _simd_u8x8_and_scalar_(X,Y)
//	#define _simd_u8x8_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_and_scalar_instruction_set>()
//#else
//	#define _simd_u8x8_and_scalar(X,Y) _simd_u8x8_and_safe(X,_simd_u8x8_fill_scalar_safe(Y))
//	#define _simd_u8x8_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_u8x1_and_safe
//	#define _simd_u8x1_and_safe(X,Y) (X & Y)
//	#define _simd_u8x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_u8x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_and_enabled() true
//#endif
//
//#define _simd_u8x16_and_safe(X,Y)_simd_u8x16_combine_safe(\
//	_simd_u8x8_and_safe(_simd_u8x16_splitlo_safe(X), _simd_ u8x16_splitlo_safe(Y)),\
//	_simd_u8x8_and_safe(_simd_u8x16_splithi_safe(X), _simd_ u8x16_splithi_safe(Y)))
//#ifdef _simd_u8x16_and_
//	#define _simd_u8x16_and(X,Y) _simd_u8x16_and_(X, Y)
//	#define _simd_u8x16_and_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_and_instruction_set>()
//#elif defined(_simd_u8x32_and_)
//	static ANVIL_STRONG_INLINE _simd_u8x16 ANVIL_SIMD_CALL _simd_u8x16_and(const register _simd_u8x16 x, const register _simd_u8x16 y) {
//		union SIMDUnion { _simd_u8x16 v1; _simd_u8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x32_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x16_and_enable() _simd_u8x32_and_enable()
//#elif defined(_simd_u8x64_and_)
//	static ANVIL_STRONG_INLINE _simd_u8x16 ANVIL_SIMD_CALL _simd_u8x16_and(const register _simd_u8x16 x, const register _simd_u8x16 y) {
//		union SIMDUnion { _simd_u8x16 v1; _simd_u8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x16_and_enable() _simd_u8x64_and_enable()
//#else
//	#define _simd_u8x16_and(X,Y) _simd_u8x16_combine(\
//		_simd_u8x8_and(_simd_u8x16_splitlo(X), _simd_u8x16_splitlo(Y)),\
//		_simd_u8x8_and(_simd_u8x16_splithi(X), _simd_u8x16_splithi(Y)))
//	#define _simd_u8x16_and_enable() (_simd_u8x8_and_enable() && _simd_u8x16_combine_enable() && _simd_u8x16_splitlo_enable()  && _simd_u8x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x16_and_) && ! defined(_simd_u8x16_and_scalar_)
//	#define _simd_u8x16_and_scalar_(X,Y) _simd_u8x16_and_(X,_simd_u8x16_fill_scalar_(Y))
//	#define _simd_u8x16_and_scalar_instruction_set _simd_u8x16_and_instruction_set
//#endif
//#ifdef _simd_u8x16_and_scalar_
//	#define _simd_u8x16_and_scalar(X,Y) _simd_u8x16_and_scalar_(X,Y)
//	#define _simd_u8x16_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_and_scalar_instruction_set>()
//#else
//	#define _simd_u8x16_and_scalar(X,Y) _simd_u8x16_and_safe(X,_simd_u8x16_fill_scalar_safe(Y))
//	#define _simd_u8x16_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_u8x1_and_safe
//	#define _simd_u8x1_and_safe(X,Y) (X & Y)
//	#define _simd_u8x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_u8x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_and_enabled() true
//#endif
//
//#define _simd_u8x32_and_safe(X,Y)_simd_u8x32_combine_safe(\
//	_simd_u8x16_and_safe(_simd_u8x32_splitlo_safe(X), _simd_ u8x32_splitlo_safe(Y)),\
//	_simd_u8x16_and_safe(_simd_u8x32_splithi_safe(X), _simd_ u8x32_splithi_safe(Y)))
//#ifdef _simd_u8x32_and_
//	#define _simd_u8x32_and(X,Y) _simd_u8x32_and_(X, Y)
//	#define _simd_u8x32_and_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_and_instruction_set>()
//#elif defined(_simd_u8x64_and_)
//	static ANVIL_STRONG_INLINE _simd_u8x32 ANVIL_SIMD_CALL _simd_u8x32_and(const register _simd_u8x32 x, const register _simd_u8x32 y) {
//		union SIMDUnion { _simd_u8x32 v1; _simd_u8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x64_and_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x32_and_enable() _simd_u8x64_and_enable()
//#else
//	#define _simd_u8x32_and(X,Y) _simd_u8x32_combine(\
//		_simd_u8x16_and(_simd_u8x32_splitlo(X), _simd_u8x32_splitlo(Y)),\
//		_simd_u8x16_and(_simd_u8x32_splithi(X), _simd_u8x32_splithi(Y)))
//	#define _simd_u8x32_and_enable() (_simd_u8x16_and_enable() && _simd_u8x32_combine_enable() && _simd_u8x32_splitlo_enable()  && _simd_u8x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x32_and_) && ! defined(_simd_u8x32_and_scalar_)
//	#define _simd_u8x32_and_scalar_(X,Y) _simd_u8x32_and_(X,_simd_u8x32_fill_scalar_(Y))
//	#define _simd_u8x32_and_scalar_instruction_set _simd_u8x32_and_instruction_set
//#endif
//#ifdef _simd_u8x32_and_scalar_
//	#define _simd_u8x32_and_scalar(X,Y) _simd_u8x32_and_scalar_(X,Y)
//	#define _simd_u8x32_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_and_scalar_instruction_set>()
//#else
//	#define _simd_u8x32_and_scalar(X,Y) _simd_u8x32_and_safe(X,_simd_u8x32_fill_scalar_safe(Y))
//	#define _simd_u8x32_and_scalar_enabled() true
//#endif
//
//#ifndef _simd_u8x1_and_safe
//	#define _simd_u8x1_and_safe(X,Y) (X & Y)
//	#define _simd_u8x1_and_(X,Y) x1_and_safe(X,Y)
//	#define _simd_u8x1_and_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_and_enabled() true
//#endif
//
//#define _simd_u8x64_and_safe(X,Y)_simd_u8x64_combine_safe(\
//	_simd_u8x32_and_safe(_simd_u8x64_splitlo_safe(X), _simd_ u8x64_splitlo_safe(Y)),\
//	_simd_u8x32_and_safe(_simd_u8x64_splithi_safe(X), _simd_ u8x64_splithi_safe(Y)))
//#ifdef _simd_u8x64_and_
//	#define _simd_u8x64_and(X,Y) _simd_u8x64_and_(X, Y)
//	#define _simd_u8x64_and_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_and_instruction_set>()
//#else
//	#define _simd_u8x64_and(X,Y) _simd_u8x64_combine(\
//		_simd_u8x32_and(_simd_u8x64_splitlo(X), _simd_u8x64_splitlo(Y)),\
//		_simd_u8x32_and(_simd_u8x64_splithi(X), _simd_u8x64_splithi(Y)))
//	#define _simd_u8x64_and_enable() (_simd_u8x32_and_enable() && _simd_u8x64_combine_enable() && _simd_u8x64_splitlo_enable()  && _simd_u8x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x64_and_) && ! defined(_simd_u8x64_and_scalar_)
//	#define _simd_u8x64_and_scalar_(X,Y) _simd_u8x64_and_(X,_simd_u8x64_fill_scalar_(Y))
//	#define _simd_u8x64_and_scalar_instruction_set _simd_u8x64_and_instruction_set
//#endif
//#ifdef _simd_u8x64_and_scalar_
//	#define _simd_u8x64_and_scalar(X,Y) _simd_u8x64_and_scalar_(X,Y)
//	#define _simd_u8x64_and_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_and_scalar_instruction_set>()
//#else
//	#define _simd_u8x64_and_scalar(X,Y) _simd_u8x64_and_safe(X,_simd_u8x64_fill_scalar_safe(Y))
//	#define _simd_u8x64_and_scalar_enabled() true
//#endif
//
