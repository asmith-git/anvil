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

#ifndef ANVIL_COMPUTE_SIMD_ADD_HPP
#define ANVIL_COMPUTE_SIMD_ADD_HPP

#include <type_traits>
#include "anvil/compute/simd/Blend.hpp"

namespace anvil { namespace detail {

	enum {
		ANVIL_VECTOR_ARITH_ADD,
		ANVIL_VECTOR_ARITH_ADDS,
		ANVIL_VECTOR_ARITH_SUB,
		ANVIL_VECTOR_ARITH_SUBS,
		ANVIL_VECTOR_ARITH_MUL,
		ANVIL_VECTOR_ARITH_DIV,
		ANVIL_VECTOR_ARITH_LSH,
		ANVIL_VECTOR_ARITH_RSH,
		ANVIL_VECTOR_ARITH_CMPEQ,
		ANVIL_VECTOR_ARITH_CMPNE,
		ANVIL_VECTOR_ARITH_CMPLT,
		ANVIL_VECTOR_ARITH_CMPGT,
		ANVIL_VECTOR_ARITH_CMPLE,
		ANVIL_VECTOR_ARITH_CMPGE
	};

	template<class native_t, class T>
	struct VectorArithNative {
		typedef WideType<T> WT;
		typedef UnsignedType<T> UT;

		enum {
			size = sizeof(native_t) / sizeof(T),
			optimised = (size == 1u && std::is_fundamental<T>::value) ? 1u : 0u
		};

		enum : uint64_t { recommended_instruction_set = 0ull };

		template<uint64_t instruction_set, NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute(const native_t a, const native_t b, native_t& out) {
			static ANVIL_CONSTEXPR_VAR const WT gMin = static_cast<WT>(std::numeric_limits<T>::min());
			static ANVIL_CONSTEXPR_VAR const WT gMax = static_cast<WT>(std::numeric_limits<T>::max());
			static ANVIL_CONSTEXPR_VAR const UT gOnes = static_cast<UT>(std::numeric_limits<UT>::max());

			if constexpr (OP == ANVIL_VECTOR_ARITH_ADD) {
				out = a + b;

			} else if constexpr (OP == ANVIL_VECTOR_ARITH_ADDS) {
				WT aw = static_cast<WT>(a);
				WT bw = static_cast<WT>(b);
				aw += bw;
				if (aw < gMin) aw = gMin;
				else if (aw > gMax) aw = gMax;
				out = static_cast<T>(aw);

			} else if constexpr (OP == ANVIL_VECTOR_ARITH_SUB) {
				out = a - b;

			} else if constexpr (OP == ANVIL_VECTOR_ARITH_SUBS) {
				WT aw = static_cast<WT>(a);
				WT bw = static_cast<WT>(b);
				aw -= bw;
				if (aw < gMin) aw = gMin;
				else if (aw > gMax) aw = gMax;
				out = static_cast<T>(aw);

			} else if constexpr (OP == ANVIL_VECTOR_ARITH_MUL) {
				out = a * b;

			} else if constexpr (OP == ANVIL_VECTOR_ARITH_DIV) {
				out = a / b;

			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPLE) {
				VectorArithNative<native_t, T>::Execute<instruction_set, ANVIL_VECTOR_ARITH_CMPLT>(b, a, out);

			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPGE) {
				VectorArithNative<native_t, T>::Execute<instruction_set, ANVIL_VECTOR_ARITH_CMPGT>(b, a, out);

			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPLT) {
				union { UT u; T t; };
				u = a < b ? gOnes : 0u;
				out = t;

			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPGT) {
				union { UT u; T t; };
				u = a > b ? gOnes : 0u;
				out = t;

			} else {
				if constexpr (std::is_unsigned<T>::value) {

					if constexpr (OP == ANVIL_VECTOR_ARITH_LSH) {
						out = a << b;

					} else if constexpr (OP == ANVIL_VECTOR_ARITH_RSH) {
						out = a >> b;

					} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPEQ) {
						out = a == b ? gOnes : 0u;

					} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPNE) {
						out = a != b ? gOnes : 0u;
					}

				} else {
					union { UT au; T at; };
					union { UT bu; T bt; };
					at = a;
					bt = b;

					VectorArithNative<native_t, UT>::Execute<instruction_set, OP>(au, bu, au);
					out = at;
				}
			}
		}
	};

	template<class T, size_t S>
	struct VectorArithNative<detail::UnoptimisedNativeType<T, S>, T> {
		typedef detail::UnoptimisedNativeType<T, S> native_t;
		typedef WideType<T> WT;
		typedef UnsignedType<T> UT;

		enum {
			size = S,
			optimised = 0
		};

		enum : uint64_t { recommended_instruction_set = 0ull };

		template<uint64_t instruction_set, NativeUnsigned OP>
		static inline void Execute(native_t a, const native_t b, native_t& out) {
			for (size_t i = 0u; i < S; ++i) VectorArithNative<T, T>::Execute<instruction_set, OP>(a.data[i], b.data[i], out.data[i]);
		}
	};

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64

	// 128-bit SSE registers

	template<>
	struct VectorArithNative<__m128, float> {
		typedef __m128 native_t;
		typedef float T;
		typedef WideType<T> WT;
		typedef UnsignedType<T> UT;

		enum {
			size = sizeof(native_t) / sizeof(T),
			optimised = 1u
		};

		enum : uint64_t { recommended_instruction_set = ASM_SSE };

		template<NativeUnsigned OP>
		static inline void ExecuteC(const native_t& a, const native_t& b, native_t& out) {
			const T* const at = reinterpret_cast<const T*>(&a);
			const T* const bt = reinterpret_cast<const T*>(&b);
			const T* const outT = reinterpret_cast<const T*>(&out);

			for (size_t i = 0u; i < size; ++i) VectorArithNative<T, T>::Execute<0u, OP>(at[i], bt[i], outT[i]);
		}

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void ExecuteSSE(const native_t& a, const native_t& b, native_t& out) {
			if constexpr (OP == ANVIL_VECTOR_ARITH_ADD || OP == ANVIL_VECTOR_ARITH_ADDS) {
				out = _mm_add_ps(a, b);

			} else if constexpr (OP == ANVIL_VECTOR_ARITH_SUB || OP == ANVIL_VECTOR_ARITH_SUBS) {
				out = _mm_sub_ps(a, b);

			} else if constexpr (OP == ANVIL_VECTOR_ARITH_MUL) {
				out = _mm_mul_ps(a, b);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_DIV) {
				out = _mm_div_ps(a, b);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPEQ) {
				out = _mm_cmpeq_ps(a, b);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPNE) {
				out = _mm_cmpneq_ps(a, b);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPLT) {
				out = _mm_cmplt_ps(a, b);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPGT) {
				out = _mm_cmpgt_ps(a, b);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPLE) {
				out = _mm_cmple_ps(a, b);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPGE) {
				out = _mm_cmpge_ps(a, b);

			} else {
				ExecuteC<OP>(a, b, out);

			}
		}

		template<uint64_t instruction_set, NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute(const native_t& a, const native_t& b, native_t& out) {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together

			if constexpr ((instruction_set & ASM_SSE) != 0ull) {
				ExecuteSSE<OP>(a, b, out);
			} else {
				ExecuteC<OP>(a, b, out);
			}
		}
	};

	template<>
	struct VectorArithNative<__m128d, double> {
		typedef __m128d native_t;
		typedef double T;
		typedef WideType<T> WT;
		typedef UnsignedType<T> UT;

		enum {
			size = sizeof(native_t) / sizeof(T),
			optimised = 1u
		};

		enum : uint64_t { recommended_instruction_set = ASM_SSE2 };

		template<NativeUnsigned OP>
		static inline void ExecuteC(const native_t& a, const native_t& b, native_t& out) {
			const T* const at = reinterpret_cast<const T*>(&a);
			const T* const bt = reinterpret_cast<const T*>(&b);
			const T* const outT = reinterpret_cast<const T*>(&out);

			for (size_t i = 0u; i < size; ++i) VectorArithNative<T, T>::Execute<0u, OP>(at[i], bt[i], outT[i]);
		}

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void ExecuteSSE2(const native_t& a, const native_t& b, native_t& out) {
			if constexpr (OP == ANVIL_VECTOR_ARITH_ADD || OP == ANVIL_VECTOR_ARITH_ADDS) {
				out = _mm_add_pd(a, b);

			} else if constexpr (OP == ANVIL_VECTOR_ARITH_SUB || OP == ANVIL_VECTOR_ARITH_SUBS) {
				out = _mm_sub_pd(a, b);

			} else if constexpr (OP == ANVIL_VECTOR_ARITH_MUL) {
				out = _mm_mul_pd(a, b);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_DIV) {
				out = _mm_div_pd(a, b);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPEQ) {
				out = _mm_cmpeq_pd(a, b);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPNE) {
				out = _mm_cmpneq_pd(a, b);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPLT) {
				out = _mm_cmplt_pd(a, b);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPGT) {
				out = _mm_cmpgt_pd(a, b);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPLE) {
				out = _mm_cmple_pd(a, b);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPGE) {
				out = _mm_cmpge_pd(a, b);

			} else {
				ExecuteC<OP>(a, b, out);

			}
		}

		template<uint64_t instruction_set, NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute(const native_t& a, const native_t& b, native_t& out) {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together

			if constexpr ((instruction_set & ASM_SSE2) != 0ull) {
				ExecuteSSE2<OP>(a, b, out);
			} else {
				ExecuteC<OP>(a, b, out);
			}
		}
	};

	template<>
	struct VectorArithNative<__m128i, int32_t> {
		typedef __m128i native_t;
		typedef int32_t T;
		typedef WideType<T> WT;
		typedef UnsignedType<T> UT;

		enum {
			size = sizeof(native_t) / sizeof(T),
			optimised = 1u
		};

		enum : uint64_t { recommended_instruction_set = ASM_SSE2 };

		template<NativeUnsigned OP>
		static inline void ExecuteC(const native_t& a, const native_t& b, native_t& out) {
			const T* const at = reinterpret_cast<const T*>(&a);
			const T* const bt = reinterpret_cast<const T*>(&b);
			const T* const outT = reinterpret_cast<const T*>(&out);

			for (size_t i = 0u; i < size; ++i) VectorArithNative<T, T>::Execute<0u, OP>(at[i], bt[i], outT[i]);
		}

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void ExecuteSSE2(const native_t& a, const native_t& b, native_t& out) {
			if constexpr (OP == ANVIL_VECTOR_ARITH_ADD || ANVIL_VECTOR_ARITH_ADDS) {
				out = _mm_add_epi32(a, b);

			} else if constexpr (OP == ANVIL_VECTOR_ARITH_SUB || ANVIL_VECTOR_ARITH_SUBS) {
				out = _mm_sub_epi16(a, b);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPEQ) {
				out = _mm_cmpeq_epi32(a, b);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPNE) {
				out = _mm_cmpeq_epi32(a, b);

				// bitwise not
				out = _mm_xor_si128(out, _mm_cmpeq_epi32(a, a));
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPLT) {
				out = _mm_cmplt_epi32(a, b);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPGT) {
				out = _mm_cmpgt_epi32(a, b);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPLE) {
				out = _mm_cmpgt_epi32(b, a);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPGE) {
				out = _mm_cmplt_epi32(b, a);

			} else {
				ExecuteC<OP>(a, b, out);

			}
		}

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void ExecuteSSE41(const native_t& a, const native_t& b, native_t& out) {
			if constexpr (OP == ANVIL_VECTOR_ARITH_MUL) {
				out = _mm_mullo_epi32(a, b);
				
			} else {
				ExecuteSSE2<OP>(a, b, out);

			}
		}

		template<uint64_t instruction_set, NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute(const native_t& a, const native_t& b, native_t& out) {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together

			if constexpr ((instruction_set & ASM_SSE41) != 0ull) {
				ExecuteSSE41<OP>(a, b, out);
			} else if constexpr ((instruction_set & ASM_SSE2) != 0ull) {
				ExecuteSSE2<OP>(a, b, out);
			} else {
				ExecuteC<OP>(a, b, out);
			}
		}
	};

	template<>
	struct VectorArithNative<__m128i, uint32_t> {
		typedef __m128i native_t;
		typedef uint32_t T;
		typedef WideType<T> WT;
		typedef UnsignedType<T> UT;

		enum {
			size = sizeof(native_t) / sizeof(T),
			optimised = 1u
		};

		enum : uint64_t { recommended_instruction_set = ASM_SSE2 };

		template<NativeUnsigned OP>
		static inline void ExecuteC(const native_t& a, const native_t& b, native_t& out) {
			const T* const at = reinterpret_cast<const T*>(&a);
			const T* const bt = reinterpret_cast<const T*>(&b);
			const T* const outT = reinterpret_cast<const T*>(&out);

			for (size_t i = 0u; i < size; ++i) VectorArithNative<T, T>::Execute<0u, OP>(at[i], bt[i], outT[i]);
		}

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void ExecuteSSE2(const native_t& a, const native_t& b, native_t& out) {
			if constexpr (OP == ANVIL_VECTOR_ARITH_ADD || OP == ANVIL_VECTOR_ARITH_SUB || OP == ANVIL_VECTOR_ARITH_CMPEQ || OP == ANVIL_VECTOR_ARITH_CMPNE) {
				VectorArithNative<native_t, int32_t>::ExecuteSSE2(a, b, out);

			} else {
				ExecuteC<OP>(a, b, out);

			}
		}

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void ExecuteAVX512BW(const native_t& a, const native_t& b, native_t& out) {
			if constexpr (OP == ANVIL_VECTOR_ARITH_CMPLT) {
				return _mm_mask_blend_epi16(_mm_cmplt_epu32_mask(a, b), b, a);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPGT) {
				return _mm_mask_blend_epi16(_mm_cmpgt_epu32_mask(a, b), b, a);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPLE) {
				return _mm_mask_blend_epi16(_mm_cmple_epu32_mask(a, b), b, a);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPGE) {
				return _mm_mask_blend_epi16(_mm_cmpge_epu32_mask(a, b), b, a);

			} else {
				ExecuteSSE2<OP>(a, b, out);

			}
		}

		template<uint64_t instruction_set, NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute(const native_t& a, const native_t& b, native_t& out) {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together

			if constexpr ((instruction_set & ASM_AVX512BW) != 0ull && (instruction_set & ASM_AVX512VL) != 0ull) {
				ExecuteAVX512BW<OP>(a, b, out);
			}  else if constexpr ((instruction_set & ASM_SSE2) != 0ull) {
				ExecuteSSE2<OP>(a, b, out);
			} else {
				ExecuteC<OP>(a, b, out);
			}
		}
	};

	template<>
	struct VectorArithNative<__m128i, int16_t> {
		typedef __m128i native_t;
		typedef int16_t T;
		typedef WideType<T> WT;
		typedef UnsignedType<T> UT;

		enum {
			size = sizeof(native_t) / sizeof(T),
			optimised = 1u
		};

		enum : uint64_t { recommended_instruction_set = ASM_SSE2 };

		template<NativeUnsigned OP>
		static inline void ExecuteC(const native_t& a, const native_t& b, native_t& out) {
			const T* const at = reinterpret_cast<const T*>(&a);
			const T* const bt = reinterpret_cast<const T*>(&b);
			const T* const outT = reinterpret_cast<const T*>(&out);

			for (size_t i = 0u; i < size; ++i) VectorArithNative<T, T>::Execute<0u, OP>(at[i], bt[i], outT[i]);
		}

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void ExecuteSSE2(const native_t& a, const native_t& b, native_t& out) {
			if constexpr (OP == ANVIL_VECTOR_ARITH_ADD) {
				out = _mm_add_epi16(a, b);

			} else if constexpr (OP == ANVIL_VECTOR_ARITH_ADDS) {
				out = _mm_adds_epi16(a, b);

			} else if constexpr (OP == ANVIL_VECTOR_ARITH_SUB) {
				out = _mm_sub_epi16(a, b);

			} else if constexpr (OP == ANVIL_VECTOR_ARITH_SUBS) {
				out = _mm_subs_epi16(a, b);

			} else if constexpr (OP == ANVIL_VECTOR_ARITH_MUL) {
				out = _mm_mullo_epi16(a, b);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPEQ) {
				out = _mm_cmpeq_epi16(a, b);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPNE) {
				out = _mm_cmpeq_epi16(a, b);

				// bitwise not
				out = _mm_xor_si128(out, _mm_cmpeq_epi16(a, a));
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPLT) {
				out = _mm_cmplt_epi16(a, b);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPGT) {
				out = _mm_cmpgt_epi16(a, b);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPLE) {
				out = _mm_cmpgt_epi16(b, a);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPGE) {
				out = _mm_cmplt_epi16(b, a);

			} else {
				ExecuteC<OP>(a, b, out);

			}
		}

		template<uint64_t instruction_set, NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute(const native_t& a, const native_t& b, native_t& out) {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together

			if constexpr ((instruction_set & ASM_SSE2) != 0ull) {
				ExecuteSSE2<OP>(a, b, out);
			} else {
				ExecuteC<OP>(a, b, out);
			}
		}
	};

	template<>
	struct VectorArithNative<__m128i, uint16_t> {
		typedef __m128i native_t;
		typedef uint16_t T;
		typedef WideType<T> WT;
		typedef UnsignedType<T> UT;

		enum {
			size = sizeof(native_t) / sizeof(T),
			optimised = 1u
		};

		enum : uint64_t { recommended_instruction_set = ASM_SSE2 };

		template<NativeUnsigned OP>
		static inline void ExecuteC(const native_t& a, const native_t& b, native_t& out) {
			const T* const at = reinterpret_cast<const T*>(&a);
			const T* const bt = reinterpret_cast<const T*>(&b);
			const T* const outT = reinterpret_cast<const T*>(&out);

			for (size_t i = 0u; i < size; ++i) VectorArithNative<T, T>::Execute<0u, OP>(at[i], bt[i], outT[i]);
		}

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void ExecuteSSE2(const native_t& a, const native_t& b, native_t& out) {
			if constexpr (OP == ANVIL_VECTOR_ARITH_ADDS) {
				out = _mm_adds_epu16(a, b);

			} else if constexpr (OP == ANVIL_VECTOR_ARITH_SUB || OP == ANVIL_VECTOR_ARITH_SUBS) {
				out = _mm_subs_epu16(a, b);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_ADD || OP == ANVIL_VECTOR_ARITH_CMPEQ || OP == ANVIL_VECTOR_ARITH_CMPNE) {
				VectorArithNative<native_t, int16_t>::ExecuteSSE2(a, b, out);

			} else {
				ExecuteC<OP>(a, b, out);

			}
		}

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void ExecuteAVX512BW(const native_t& a, const native_t& b, native_t& out) {
			if constexpr (OP == ANVIL_VECTOR_ARITH_CMPLT) {
				return _mm_mask_blend_epi16(_mm_cmplt_epu16_mask(a, b), b, a);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPGT) {
				return _mm_mask_blend_epi16(_mm_cmpgt_epu16_mask(a, b), b, a);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPLE) {
				return _mm_mask_blend_epi16(_mm_cmple_epu16_mask(a, b), b, a);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPGE) {
				return _mm_mask_blend_epi16(_mm_cmpge_epu16_mask(a, b), b, a);

			} else {
				ExecuteSSE2<OP>(a, b, out);

			}
		}

		template<uint64_t instruction_set, NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute(const native_t& a, const native_t& b, native_t& out) {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together

			if constexpr ((instruction_set & ASM_AVX512BW) != 0ull && (instruction_set & ASM_AVX512VL) != 0ull) {
				ExecuteAVX512BW<OP>(a, b, out);
			}  else if constexpr ((instruction_set & ASM_SSE2) != 0ull) {
				ExecuteSSE2<OP>(a, b, out);
			} else {
				ExecuteC<OP>(a, b, out);
			}
		}
	};

	template<>
	struct VectorArithNative<__m128i, int8_t> {
		typedef __m128i native_t;
		typedef int8_t T;
		typedef WideType<T> WT;
		typedef UnsignedType<T> UT;

		enum {
			size = sizeof(native_t) / sizeof(T),
			optimised = 1u
		};

		enum : uint64_t { recommended_instruction_set = ASM_SSE2 };

		template<NativeUnsigned OP>
		static inline void ExecuteC(const native_t& a, const native_t& b, native_t& out) {
			const T* const at = reinterpret_cast<const T*>(&a);
			const T* const bt = reinterpret_cast<const T*>(&b);
			const T* const outT = reinterpret_cast<const T*>(&out);

			for (size_t i = 0u; i < size; ++i) VectorArithNative<T, T>::Execute<0u, OP>(at[i], bt[i], outT[i]);
		}

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void ExecuteSSE2(const native_t& a, const native_t& b, native_t& out) {
			if constexpr (OP == ANVIL_VECTOR_ARITH_ADD) {
				out = _mm_add_epi8(a, b);

			} else if constexpr (OP == ANVIL_VECTOR_ARITH_ADDS) {
				out = _mm_adds_epi8(a, b);

			} else if constexpr (OP == ANVIL_VECTOR_ARITH_SUB) {
				out = _mm_sub_epi8(a, b);

			} else if constexpr (OP == ANVIL_VECTOR_ARITH_SUBS) {
				out = _mm_subs_epi8(a, b);

			//} else if constexpr (OP == ANVIL_VECTOR_ARITH_MUL) {
				//! \todo Convert to int16 and multiply
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPEQ) {
				out = _mm_cmpeq_epi8(a, b);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPNE) {
				out = _mm_cmpeq_epi8(a, b);

				// bitwise not
				out = _mm_xor_si128(out, _mm_cmpeq_epi8(a, a));
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPLT) {
				out = _mm_cmplt_epi8(a, b);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPGT) {
				out = _mm_cmpgt_epi8(a, b);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPLE) {
				out = _mm_cmpgt_epi8(b, a);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPGE) {
				out = _mm_cmplt_epi8(b, a);

			} else {
				ExecuteC<OP>(a, b, out);

			}
		}

		template<uint64_t instruction_set, NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute(const native_t& a, const native_t& b, native_t& out) {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together

			if constexpr ((instruction_set & ASM_SSE2) != 0ull) {
				ExecuteSSE2<OP>(a, b, out);
			} else {
				ExecuteC<OP>(a, b, out);
			}
		}
	};

	template<>
	struct VectorArithNative<__m128i, uint8_t> {
		typedef __m128i native_t;
		typedef uint8_t T;
		typedef WideType<T> WT;
		typedef UnsignedType<T> UT;

		enum {
			size = sizeof(native_t) / sizeof(T),
			optimised = 1u
		};

		enum : uint64_t { recommended_instruction_set = ASM_SSE2 };

		template<NativeUnsigned OP>
		static inline void ExecuteC(const native_t& a, const native_t& b, native_t& out) {
			const T* const at = reinterpret_cast<const T*>(&a);
			const T* const bt = reinterpret_cast<const T*>(&b);
			const T* const outT = reinterpret_cast<const T*>(&out);

			for (size_t i = 0u; i < size; ++i) VectorArithNative<T, T>::Execute<0u, OP>(at[i], bt[i], outT[i]);
		}

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void ExecuteSSE2(const native_t& a, const native_t& b, native_t& out) {
			if constexpr (OP == ANVIL_VECTOR_ARITH_ADDS) {
				out = _mm_adds_epu8(a, b);

			} else if constexpr (OP == ANVIL_VECTOR_ARITH_SUB || OP == ANVIL_VECTOR_ARITH_SUBS) {
				out = _mm_subs_epu8(a, b);

			//} else if constexpr (OP == ANVIL_VECTOR_ARITH_MUL) {
				//! \todo Convert to int16 and multiply
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_ADD || OP == ANVIL_VECTOR_ARITH_CMPEQ || OP == ANVIL_VECTOR_ARITH_CMPNE) {
				VectorArithNative<native_t, int8_t>::ExecuteSSE2(a, b, out);

			} else {
				ExecuteC<OP>(a, b, out);

			}
		}

		template<NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void ExecuteAVX512BW(const native_t& a, const native_t& b, native_t& out) {
			if constexpr (OP == ANVIL_VECTOR_ARITH_CMPLT) {
				return _mm_mask_blend_epi8(_mm_cmplt_epu8_mask(a, b), b, a);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPGT) {
				return _mm_mask_blend_epi8(_mm_cmpgt_epu8_mask(a, b), b, a);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPLE) {
				return _mm_mask_blend_epi8(_mm_cmple_epu8_mask(a, b), b, a);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPGE) {
				return _mm_mask_blend_epi8(_mm_cmpge_epu8_mask(a, b), b, a);

			} else {
				ExecuteSSE2<OP>(a, b, out);

			}
		}

		template<uint64_t instruction_set, NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute(const native_t& a, const native_t& b, native_t& out) {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together

			if constexpr ((instruction_set & ASM_AVX512BW) != 0ull && (instruction_set & ASM_AVX512VL) != 0ull) {
				ExecuteAVX512BW<OP>(a, b, out);
			}  else if constexpr ((instruction_set & ASM_SSE2) != 0ull) {
				ExecuteSSE2<OP>(a, b, out);
			} else {
				ExecuteC<OP>(a, b, out);
			}
		}
	};

	// 256-bit AVX registers

	// 512-bit AVX 512 registers

#endif

	template<NativeUnsigned OP, class T>
	struct VectorArith {
		typedef T type;
		typedef T native_t;
		typedef VectorArithNative<native_t, T> Implementation;

		template<uint64_t instruction_set>
		static constexpr inline size_t GetOptimisedSize() throw() {
			return 1u;
		}

		template<uint64_t instruction_set>
		static inline type Execute(const type& a, const type& b) throw() {
			type tmp;
			Implementation::Execute<instruction_set, OP>(a.native, b.native, tmp.native);
			return tmp;
		}

		template<uint64_t instruction_set>
		static inline type ExecuteRuntimeMask(const type& a, const type& b, const type& src, const uint64_t mask) throw() {
			type tmp;
			Implementation::Execute<instruction_set, OP>(a.native, b.native, tmp.native);
			return anvil::VectorBlendRuntimeMask<instruction_set>(tmp, src, mask);
		}

		template<uint64_t instruction_set>
		static inline type ExecuteRuntimeMask(const type& a, const type& b, const type& src, const Bitfield128 mask) throw() {
			return ExecuteRuntimeMask<instruction_set>(a, b, src, mask.low);
		}

		template<uint64_t instruction_set>
		static inline type ExecuteRuntimeMask(const type& a, const type& b, const type& src, const Bitfield256 mask) throw() {
			return ExecuteRuntimeMask<instruction_set>(a, b, src, mask.low);
		}

		template<uint64_t mask, uint64_t instruction_set>
		static inline type ExecuteCompiletimeMask(const type& a, const type& b, const type& src) throw() {
			type tmp;
			Implementation::Execute<instruction_set, OP>(a.native, b.native, tmp.native);
			return anvil::VectorBlendCompiletimeMask<mask, instruction_set>(tmp, src);
		}
	};



	template<NativeUnsigned OP, class T, size_t S>
	struct VectorArith<OP, detail::BasicVector<T,S>> {
		typedef detail::BasicVector<T, S> type;
		typedef typename detail::BasicVector<T, S>::native_t native_t;
		typedef VectorArithNative<native_t, T> Implementation;
		typedef typename type::lower_t lower_t;
		typedef typename type::upper_t upper_t;

		template<uint64_t instruction_set>
		static constexpr inline size_t GetOptimisedSize() throw() {
			if constexpr (Implementation::optimised && (instruction_set & Implementation::recommended_instruction_set) == Implementation::recommended_instruction_set) {
				return S;
			} else {

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
				return 
					(instruction_set & ASM_AVX512F) ? 64u / sizeof(T) :
					(instruction_set & ASM_AVX2) ? 32u / sizeof(T) :
					(instruction_set & ASM_SSE2) ? 16u / sizeof(T) :
					1u;
#else
				return 4u;
#endif
			}
		}

		template<uint64_t instruction_set>
		static inline type Execute(const type& a, const type& b) throw() {
			if constexpr (Implementation::optimised && (instruction_set & Implementation::recommended_instruction_set) == Implementation::recommended_instruction_set) {
				type tmp;
				Implementation::Execute<instruction_set, OP>(a.native, b.native, tmp.native);
				return tmp;
			} else {
				//return type(
				//	VectorArith<OP, lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half),
				//	VectorArith<OP, upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half)
				//);

				type tmp;

				enum {
					optimised_size = GetOptimisedSize<instruction_set>(),
					loop_size = S / optimised_size,
					remainder_size = S - (optimised_size * loop_size)
				};

				typedef Vector<T, optimised_size> OptimisedType;
				typedef Vector<T, remainder_size> RemainderType;

				union Ptr {
					T* element;
					OptimisedType* optimised;
					RemainderType* remainder;
				};

				Ptr aPtr, bPtr, tmpPtr;

				aPtr.element = const_cast<T*>(a.data);
				bPtr.element = const_cast<T*>(b.data);
				tmpPtr.element = tmp.data;

				for (size_t i = 0u; i < loop_size; ++i) tmpPtr.optimised[i] = VectorArith<OP, OptimisedType>::Execute<instruction_set>(aPtr.optimised[i], bPtr.optimised[i]);

				if constexpr (remainder_size > 0u) {
					aPtr.optimised += loop_size;
					bPtr.optimised += loop_size;
					tmpPtr.optimised += loop_size;

					*tmpPtr.remainder = VectorArith<OP, RemainderType>::Execute<instruction_set>(*aPtr.remainder, *bPtr.remainder);
				}

				return tmp;
			}
		}

		template<uint64_t instruction_set>
		static inline type ExecuteRuntimeMask(const type& a, const type& b, const type& src, uint64_t mask) throw() {
			if constexpr (Implementation::optimised && (instruction_set & Implementation::recommended_instruction_set) == Implementation::recommended_instruction_set) {
				type tmp;
				Implementation::Execute<instruction_set, OP>(a.native, b.native, tmp.native);
				return anvil::VectorBlendRuntimeMask<instruction_set>(tmp, src, mask);
			} else {
				//return type(
				//	VectorArith<OP, lower_t>::ExecuteRuntimeMask<instruction_set>(a.lower_half, b.lower_half, src.lower_half, mask),
				//	VectorArith<OP, upper_t>::ExecuteRuntimeMask<instruction_set>(a.upper_half, b.upper_half, src.upper_half, mask >> type::lower_size)
				//);

				type tmp;

				enum {
					optimised_size = GetOptimisedSize<instruction_set>(),
					loop_size = S / optimised_size,
					remainder_size = S - (optimised_size * loop_size)
				};

				typedef Vector<T, optimised_size> OptimisedType;
				typedef Vector<T, remainder_size> RemainderType;

				union Ptr {
					T* element;
					OptimisedType* optimised;
					RemainderType* remainder;
				};

				Ptr aPtr, bPtr, srcPtr, tmpPtr;

				aPtr.element = const_cast<T*>(a.data);
				bPtr.element = const_cast<T*>(b.data);
				srcPtr.element = const_cast<T*>(src.data);
				tmpPtr.element = tmp.data;

				for (size_t i = 0u; i < loop_size; ++i) {
					tmpPtr.optimised[i] = VectorArith<OP, OptimisedType>::ExecuteRuntimeMask<instruction_set>(aPtr.optimised[i], bPtr.optimised[i], srcPtr.optimised[i], mask);
					mask >>= optimised_size;
				}

				if constexpr (remainder_size > 0u) {
					aPtr.optimised += loop_size;
					bPtr.optimised += loop_size;
					srcPtr.optimised += loop_size;
					tmpPtr.optimised += loop_size;

					*tmpPtr.remainder = VectorArith<OP, RemainderType>::ExecuteRuntimeMask<instruction_set>(*aPtr.remainder, *bPtr.remainder, *srcPtr.remainder, mask);
				}

				return tmp;
			}
		}

		template<uint64_t instruction_set>
		static inline type ExecuteRuntimeMask(const type& a, const type& b, const type& src, const Bitfield128 mask) throw() {
			if constexpr (S <= 64u) {
				return ExecuteRuntimeMask<instruction_set>(a, b, src, mask.low);
			} else if constexpr (S == 128u) {
				return  detail::BasicVector<T, S>(
					VectorArith<OP, type::lower_t>::ExecuteRuntimeMask<instruction_set>(a.lower_half, b.lower_half, src.lower_half, mask.low),
					VectorArith<OP, type::upper_t>::ExecuteRuntimeMask<instruction_set>(a.upper_half, b.upper_half, src.upper_half, mask.high)
				);
			} else {
				enum { S2 = S - 64u };

				detail::BasicVector<T, S> tmp;
				const detail::BasicVector<T, 64u>& aLow = *reinterpret_cast<const detail::BasicVector<T, 64u>*>(a.data);
				const detail::BasicVector<T, 64u>& bLow = *reinterpret_cast<const detail::BasicVector<T, 64u>*>(b.data);
				const detail::BasicVector<T, 64u>& srcLow = *reinterpret_cast<const detail::BasicVector<T, 64u>*>(src.data);
				detail::BasicVector<T, 64u>& tmpLow = *reinterpret_cast<detail::BasicVector<T, 64u>*>(tmp.data);
				const detail::BasicVector<T, S2>& aHigh = *reinterpret_cast<const detail::BasicVector<T, S2>*>(a.data + 64u);
				const detail::BasicVector<T, S2>& bHigh = *reinterpret_cast<const detail::BasicVector<T, S2>*>(b.data + 64u);
				const detail::BasicVector<T, S2>& srcHigh = *reinterpret_cast<const detail::BasicVector<T, S2>*>(src.data + 64u);
				detail::BasicVector<T, S2>& tmpHigh = *reinterpret_cast<detail::BasicVector<T, S2>*>(tmp.data + 64u);

				tmpLow = VectorArith<OP, detail::BasicVector<T, 64u>>::ExecuteRuntimeMask<instruction_set>(aLow, bLow, srcLow, mask.low);
				tmpHigh = VectorArith<OP, detail::BasicVector<T, S2>>::ExecuteRuntimeMask<instruction_set>(aHigh, bHigh, srcHigh, mask.high);
				return tmp;
			}
		}

		template<uint64_t instruction_set>
		static inline type ExecuteRuntimeMask(const type& a, const type& b, const type& src, const Bitfield256 mask) throw() {
			if constexpr (S <= 128u) {
				return ExecuteRuntimeMask<instruction_set>(a, b, src, mask.low);
			} else if constexpr (S == 256u) {
				return  detail::BasicVector<T, S>(
					VectorArith<OP, type::lower_t>::ExecuteRuntimeMask<instruction_set>(a.lower_half, b.lower_half, src.lower_half, mask.low),
					VectorArith<OP, type::upper_t>::ExecuteRuntimeMask<instruction_set>(a.upper_half, b.upper_half, src.upper_half, mask.high)
				);
			} else {
				enum { S2 = S - 128u };

				detail::BasicVector<T, S> tmp;
				const detail::BasicVector<T, 128u>& aLow = *reinterpret_cast<const detail::BasicVector<T, 128u>*>(a.data);
				const detail::BasicVector<T, 128u>& bLow = *reinterpret_cast<const detail::BasicVector<T, 128u>*>(b.data);
				const detail::BasicVector<T, 128u>& srcLow = *reinterpret_cast<const detail::BasicVector<T, 128u>*>(src.data);
				detail::BasicVector<T, 128u>& tmpLow = *reinterpret_cast<detail::BasicVector<T, 128u>*>(tmp.data);
				const detail::BasicVector<T, S2>& aHigh = *reinterpret_cast<const detail::BasicVector<T, S2>*>(a.data + 128u);
				const detail::BasicVector<T, S2>& bHigh = *reinterpret_cast<const detail::BasicVector<T, S2>*>(b.data + 128u);
				const detail::BasicVector<T, S2>& srcHigh = *reinterpret_cast<const detail::BasicVector<T, S2>*>(src.data + 128u);
				detail::BasicVector<T, S2>& tmpHigh = *reinterpret_cast<detail::BasicVector<T, S2>*>(tmp.data + 128u);

				tmpLow = VectorArith<OP, detail::BasicVector<T, 128u>>::ExecuteRuntimeMask<instruction_set>(aLow, bLow, srcLow, mask.low);
				tmpHigh = VectorArith<OP, detail::BasicVector<T, S2>>::ExecuteRuntimeMask<instruction_set>(aHigh, bHigh, srcHigh, mask.high);
				return tmp;
			}
		}

		template<uint64_t mask, uint64_t instruction_set>
		static inline type ExecuteCompiletimeMask(const type& a, const type& b, const type& src) throw() {
			if constexpr (Implementation::optimised && (instruction_set & Implementation::recommended_instruction_set) == Implementation::recommended_instruction_set) {
				type tmp;
				Implementation::Execute<instruction_set, OP>(a.native, b.native, tmp.native);
				return anvil::VectorBlendCompiletimeMask<mask, instruction_set>(tmp, src);
			} else {
				enum : uint64_t { mask1 = mask >> type::lower_size };
				return type(
					VectorArith<OP, lower_t>::ExecuteCompiletimeMask<mask, instruction_set>(a.lower_half, b.lower_half, src.lower_half),
					VectorArith<OP, upper_t>::ExecuteCompiletimeMask<mask1, instruction_set>(a.upper_half, b.upper_half, src.upper_half)
				);
			}
		}
	};

	template<class T>
	using VectorAdd = VectorArith<ANVIL_VECTOR_ARITH_ADD, T>;

	template<class T>
	using VectorAdds = VectorArith<ANVIL_VECTOR_ARITH_ADDS, T>;
}}

namespace anvil {

	template<uint64_t instruction_set = ASM_MINIMUM, class T>
	static inline T VectorAdd(const T& a, const T& b) throw() {
		return detail::VectorAdd<T>::Execute<instruction_set>(a, b);
	}

	template<uint64_t instruction_set = ASM_MINIMUM, class T>
	static inline T VectorAdd(const T& a, const T& b, const T& src, const uint64_t mask) throw() {
		return detail::VectorAdd<T>::ExecuteRuntimeMask<instruction_set>(a, b, src, mask);
	}

	template<uint64_t instruction_set = ASM_MINIMUM, class T>
	static inline T VectorAdd(const T& a, const T& b, const T& src, const Bitfield128 mask) throw() {
		return detail::VectorAdd<T>::ExecuteRuntimeMask<instruction_set>(a, b, src, mask);
	}

	template<uint64_t instruction_set = ASM_MINIMUM, class T>
	static inline T VectorAdd(const T& a, const T& b, const T& src, const Bitfield256 mask) throw() {
		return detail::VectorAdd<T>::ExecuteRuntimeMask<instruction_set>(a, b, src, mask);
	}

	template<uint64_t mask, uint64_t instruction_set = ASM_MINIMUM, class T>
	static inline T VectorAdd(const T& a, const T& b, const T& src) throw() {
		return detail::VectorAdds<T>::ExecuteCompiletimeMask<mask, instruction_set>(a, b, src);
	}

	template<uint64_t instruction_set = ASM_MINIMUM, class T>
	static inline T VectorAdds(const T& a, const T& b) throw() {
		return detail::VectorAdds<T>::Execute<instruction_set>(a, b);
	}

	template<uint64_t instruction_set = ASM_MINIMUM, class T>
	static inline T VectorAdds(const T& a, const T& b, const T& src, const uint64_t mask) throw() {
		return detail::VectorAdds<T>::ExecuteRuntimeMask<instruction_set>(a, b, src, mask);
	}

	template<uint64_t instruction_set = ASM_MINIMUM, class T>
	static inline T VectorAdds(const T& a, const T& b, const T& src, const Bitfield128 mask) throw() {
		return detail::VectorAdds<T>::ExecuteRuntimeMask<instruction_set>(a, b, src, mask);
	}

	template<uint64_t instruction_set = ASM_MINIMUM, class T>
	static inline T VectorAdds(const T& a, const T& b, const T& src, const Bitfield256 mask) throw() {
		return detail::VectorAdds<T>::ExecuteRuntimeMask<instruction_set>(a, b, src, mask);
	}

	template<uint64_t mask, uint64_t instruction_set = ASM_MINIMUM, class T>
	static inline T VectorAdds(const T& a, const T& b, const T& src) throw() {
		return detail::VectorAdds<T>::ExecuteCompiletimeMask<mask, instruction_set>(a, b, src);
	}
}


template<class T, size_t size>
ANVIL_STRONG_INLINE anvil::detail::BasicVector<T, size> operator+(const anvil::detail::BasicVector<T, size>& a, const anvil::detail::BasicVector<T, size>& b) throw() {
	return anvil::VectorAdd<anvil::ASM_MINIMUM, anvil::detail::BasicVector<T, size>>(a, b);
}

#endif

//// -- f64 --
//
//#ifndef _simd_f64x1_add_safe
//	#define _simd_f64x1_add_safe(X,Y) (X + Y)
//	#define _simd_f64x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_f64x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_add_enabled() true
//#endif
//
//#define _simd_f64x2_add_safe(X,Y)_simd_f64x2_combine_safe(\
//	_simd_f64x1_add_safe(_simd_f64x2_splitlo_safe(X), _simd_ f64x2_splitlo_safe(Y)),\
//	_simd_f64x1_add_safe(_simd_f64x2_splithi_safe(X), _simd_ f64x2_splithi_safe(Y)))
//#ifdef _simd_f64x2_add_
//	#define _simd_f64x2_add(X,Y) _simd_f64x2_add_(X, Y)
//	#define _simd_f64x2_add_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_add_instruction_set>()
//#elif defined(_simd_f64x4_add_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_add(const register _simd_f64x2 x, const register _simd_f64x2 y) {
//		union SIMDUnion { _simd_f64x2 v1; _simd_f64x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x4_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x2_add_enable() _simd_f64x4_add_enable()
//#elif defined(_simd_f64x8_add_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_add(const register _simd_f64x2 x, const register _simd_f64x2 y) {
//		union SIMDUnion { _simd_f64x2 v1; _simd_f64x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x8_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x2_add_enable() _simd_f64x8_add_enable()
//#elif defined(_simd_f64x16_add_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_add(const register _simd_f64x2 x, const register _simd_f64x2 y) {
//		union SIMDUnion { _simd_f64x2 v1; _simd_f64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x16_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x2_add_enable() _simd_f64x16_add_enable()
//#elif defined(_simd_f64x32_add_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_add(const register _simd_f64x2 x, const register _simd_f64x2 y) {
//		union SIMDUnion { _simd_f64x2 v1; _simd_f64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x2_add_enable() _simd_f64x32_add_enable()
//#elif defined(_simd_f64x64_add_)
//	static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_add(const register _simd_f64x2 x, const register _simd_f64x2 y) {
//		union SIMDUnion { _simd_f64x2 v1; _simd_f64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x2_add_enable() _simd_f64x64_add_enable()
//#else
//	#define _simd_f64x2_add(X,Y) _simd_f64x2_combine(\
//		_simd_f64x1_add(_simd_f64x2_splitlo(X), _simd_f64x2_splitlo(Y)),\
//		_simd_f64x1_add(_simd_f64x2_splithi(X), _simd_f64x2_splithi(Y)))
//	#define _simd_f64x2_add_enable() (_simd_f64x1_add_enable() && _simd_f64x2_combine_enable() && _simd_f64x2_splitlo_enable()  && _simd_f64x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x2_add_) && ! defined(_simd_f64x2_add_scalar_)
//	#define _simd_f64x2_add_scalar_(X,Y) _simd_f64x2_add_(X,_simd_f64x2_fill_scalar_(Y))
//	#define _simd_f64x2_add_scalar_instruction_set _simd_f64x2_add_instruction_set
//#endif
//#ifdef _simd_f64x2_add_scalar_
//	#define _simd_f64x2_add_scalar(X,Y) _simd_f64x2_add_scalar_(X,Y)
//	#define _simd_f64x2_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_add_scalar_instruction_set>()
//#else
//	#define _simd_f64x2_add_scalar(X,Y) _simd_f64x2_add_safe(X,_simd_f64x2_fill_scalar_safe(Y))
//	#define _simd_f64x2_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_f64x1_add_safe
//	#define _simd_f64x1_add_safe(X,Y) (X + Y)
//	#define _simd_f64x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_f64x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_add_enabled() true
//#endif
//
//#define _simd_f64x4_add_safe(X,Y)_simd_f64x4_combine_safe(\
//	_simd_f64x2_add_safe(_simd_f64x4_splitlo_safe(X), _simd_ f64x4_splitlo_safe(Y)),\
//	_simd_f64x2_add_safe(_simd_f64x4_splithi_safe(X), _simd_ f64x4_splithi_safe(Y)))
//#ifdef _simd_f64x4_add_
//	#define _simd_f64x4_add(X,Y) _simd_f64x4_add_(X, Y)
//	#define _simd_f64x4_add_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_add_instruction_set>()
//#elif defined(_simd_f64x8_add_)
//	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_add(const register _simd_f64x4 x, const register _simd_f64x4 y) {
//		union SIMDUnion { _simd_f64x4 v1; _simd_f64x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x8_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x4_add_enable() _simd_f64x8_add_enable()
//#elif defined(_simd_f64x16_add_)
//	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_add(const register _simd_f64x4 x, const register _simd_f64x4 y) {
//		union SIMDUnion { _simd_f64x4 v1; _simd_f64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x16_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x4_add_enable() _simd_f64x16_add_enable()
//#elif defined(_simd_f64x32_add_)
//	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_add(const register _simd_f64x4 x, const register _simd_f64x4 y) {
//		union SIMDUnion { _simd_f64x4 v1; _simd_f64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x4_add_enable() _simd_f64x32_add_enable()
//#elif defined(_simd_f64x64_add_)
//	static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_add(const register _simd_f64x4 x, const register _simd_f64x4 y) {
//		union SIMDUnion { _simd_f64x4 v1; _simd_f64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x4_add_enable() _simd_f64x64_add_enable()
//#else
//	#define _simd_f64x4_add(X,Y) _simd_f64x4_combine(\
//		_simd_f64x2_add(_simd_f64x4_splitlo(X), _simd_f64x4_splitlo(Y)),\
//		_simd_f64x2_add(_simd_f64x4_splithi(X), _simd_f64x4_splithi(Y)))
//	#define _simd_f64x4_add_enable() (_simd_f64x2_add_enable() && _simd_f64x4_combine_enable() && _simd_f64x4_splitlo_enable()  && _simd_f64x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x4_add_) && ! defined(_simd_f64x4_add_scalar_)
//	#define _simd_f64x4_add_scalar_(X,Y) _simd_f64x4_add_(X,_simd_f64x4_fill_scalar_(Y))
//	#define _simd_f64x4_add_scalar_instruction_set _simd_f64x4_add_instruction_set
//#endif
//#ifdef _simd_f64x4_add_scalar_
//	#define _simd_f64x4_add_scalar(X,Y) _simd_f64x4_add_scalar_(X,Y)
//	#define _simd_f64x4_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_add_scalar_instruction_set>()
//#else
//	#define _simd_f64x4_add_scalar(X,Y) _simd_f64x4_add_safe(X,_simd_f64x4_fill_scalar_safe(Y))
//	#define _simd_f64x4_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_f64x1_add_safe
//	#define _simd_f64x1_add_safe(X,Y) (X + Y)
//	#define _simd_f64x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_f64x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_add_enabled() true
//#endif
//
//#define _simd_f64x8_add_safe(X,Y)_simd_f64x8_combine_safe(\
//	_simd_f64x4_add_safe(_simd_f64x8_splitlo_safe(X), _simd_ f64x8_splitlo_safe(Y)),\
//	_simd_f64x4_add_safe(_simd_f64x8_splithi_safe(X), _simd_ f64x8_splithi_safe(Y)))
//#ifdef _simd_f64x8_add_
//	#define _simd_f64x8_add(X,Y) _simd_f64x8_add_(X, Y)
//	#define _simd_f64x8_add_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_add_instruction_set>()
//#elif defined(_simd_f64x16_add_)
//	static ANVIL_STRONG_INLINE _simd_f64x8 ANVIL_SIMD_CALL _simd_f64x8_add(const register _simd_f64x8 x, const register _simd_f64x8 y) {
//		union SIMDUnion { _simd_f64x8 v1; _simd_f64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x16_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x8_add_enable() _simd_f64x16_add_enable()
//#elif defined(_simd_f64x32_add_)
//	static ANVIL_STRONG_INLINE _simd_f64x8 ANVIL_SIMD_CALL _simd_f64x8_add(const register _simd_f64x8 x, const register _simd_f64x8 y) {
//		union SIMDUnion { _simd_f64x8 v1; _simd_f64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x8_add_enable() _simd_f64x32_add_enable()
//#elif defined(_simd_f64x64_add_)
//	static ANVIL_STRONG_INLINE _simd_f64x8 ANVIL_SIMD_CALL _simd_f64x8_add(const register _simd_f64x8 x, const register _simd_f64x8 y) {
//		union SIMDUnion { _simd_f64x8 v1; _simd_f64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x8_add_enable() _simd_f64x64_add_enable()
//#else
//	#define _simd_f64x8_add(X,Y) _simd_f64x8_combine(\
//		_simd_f64x4_add(_simd_f64x8_splitlo(X), _simd_f64x8_splitlo(Y)),\
//		_simd_f64x4_add(_simd_f64x8_splithi(X), _simd_f64x8_splithi(Y)))
//	#define _simd_f64x8_add_enable() (_simd_f64x4_add_enable() && _simd_f64x8_combine_enable() && _simd_f64x8_splitlo_enable()  && _simd_f64x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x8_add_) && ! defined(_simd_f64x8_add_scalar_)
//	#define _simd_f64x8_add_scalar_(X,Y) _simd_f64x8_add_(X,_simd_f64x8_fill_scalar_(Y))
//	#define _simd_f64x8_add_scalar_instruction_set _simd_f64x8_add_instruction_set
//#endif
//#ifdef _simd_f64x8_add_scalar_
//	#define _simd_f64x8_add_scalar(X,Y) _simd_f64x8_add_scalar_(X,Y)
//	#define _simd_f64x8_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_add_scalar_instruction_set>()
//#else
//	#define _simd_f64x8_add_scalar(X,Y) _simd_f64x8_add_safe(X,_simd_f64x8_fill_scalar_safe(Y))
//	#define _simd_f64x8_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_f64x1_add_safe
//	#define _simd_f64x1_add_safe(X,Y) (X + Y)
//	#define _simd_f64x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_f64x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_add_enabled() true
//#endif
//
//#define _simd_f64x16_add_safe(X,Y)_simd_f64x16_combine_safe(\
//	_simd_f64x8_add_safe(_simd_f64x16_splitlo_safe(X), _simd_ f64x16_splitlo_safe(Y)),\
//	_simd_f64x8_add_safe(_simd_f64x16_splithi_safe(X), _simd_ f64x16_splithi_safe(Y)))
//#ifdef _simd_f64x16_add_
//	#define _simd_f64x16_add(X,Y) _simd_f64x16_add_(X, Y)
//	#define _simd_f64x16_add_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_add_instruction_set>()
//#elif defined(_simd_f64x32_add_)
//	static ANVIL_STRONG_INLINE _simd_f64x16 ANVIL_SIMD_CALL _simd_f64x16_add(const register _simd_f64x16 x, const register _simd_f64x16 y) {
//		union SIMDUnion { _simd_f64x16 v1; _simd_f64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x16_add_enable() _simd_f64x32_add_enable()
//#elif defined(_simd_f64x64_add_)
//	static ANVIL_STRONG_INLINE _simd_f64x16 ANVIL_SIMD_CALL _simd_f64x16_add(const register _simd_f64x16 x, const register _simd_f64x16 y) {
//		union SIMDUnion { _simd_f64x16 v1; _simd_f64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x16_add_enable() _simd_f64x64_add_enable()
//#else
//	#define _simd_f64x16_add(X,Y) _simd_f64x16_combine(\
//		_simd_f64x8_add(_simd_f64x16_splitlo(X), _simd_f64x16_splitlo(Y)),\
//		_simd_f64x8_add(_simd_f64x16_splithi(X), _simd_f64x16_splithi(Y)))
//	#define _simd_f64x16_add_enable() (_simd_f64x8_add_enable() && _simd_f64x16_combine_enable() && _simd_f64x16_splitlo_enable()  && _simd_f64x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x16_add_) && ! defined(_simd_f64x16_add_scalar_)
//	#define _simd_f64x16_add_scalar_(X,Y) _simd_f64x16_add_(X,_simd_f64x16_fill_scalar_(Y))
//	#define _simd_f64x16_add_scalar_instruction_set _simd_f64x16_add_instruction_set
//#endif
//#ifdef _simd_f64x16_add_scalar_
//	#define _simd_f64x16_add_scalar(X,Y) _simd_f64x16_add_scalar_(X,Y)
//	#define _simd_f64x16_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_add_scalar_instruction_set>()
//#else
//	#define _simd_f64x16_add_scalar(X,Y) _simd_f64x16_add_safe(X,_simd_f64x16_fill_scalar_safe(Y))
//	#define _simd_f64x16_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_f64x1_add_safe
//	#define _simd_f64x1_add_safe(X,Y) (X + Y)
//	#define _simd_f64x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_f64x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_add_enabled() true
//#endif
//
//#define _simd_f64x32_add_safe(X,Y)_simd_f64x32_combine_safe(\
//	_simd_f64x16_add_safe(_simd_f64x32_splitlo_safe(X), _simd_ f64x32_splitlo_safe(Y)),\
//	_simd_f64x16_add_safe(_simd_f64x32_splithi_safe(X), _simd_ f64x32_splithi_safe(Y)))
//#ifdef _simd_f64x32_add_
//	#define _simd_f64x32_add(X,Y) _simd_f64x32_add_(X, Y)
//	#define _simd_f64x32_add_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_add_instruction_set>()
//#elif defined(_simd_f64x64_add_)
//	static ANVIL_STRONG_INLINE _simd_f64x32 ANVIL_SIMD_CALL _simd_f64x32_add(const register _simd_f64x32 x, const register _simd_f64x32 y) {
//		union SIMDUnion { _simd_f64x32 v1; _simd_f64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f64x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f64x32_add_enable() _simd_f64x64_add_enable()
//#else
//	#define _simd_f64x32_add(X,Y) _simd_f64x32_combine(\
//		_simd_f64x16_add(_simd_f64x32_splitlo(X), _simd_f64x32_splitlo(Y)),\
//		_simd_f64x16_add(_simd_f64x32_splithi(X), _simd_f64x32_splithi(Y)))
//	#define _simd_f64x32_add_enable() (_simd_f64x16_add_enable() && _simd_f64x32_combine_enable() && _simd_f64x32_splitlo_enable()  && _simd_f64x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x32_add_) && ! defined(_simd_f64x32_add_scalar_)
//	#define _simd_f64x32_add_scalar_(X,Y) _simd_f64x32_add_(X,_simd_f64x32_fill_scalar_(Y))
//	#define _simd_f64x32_add_scalar_instruction_set _simd_f64x32_add_instruction_set
//#endif
//#ifdef _simd_f64x32_add_scalar_
//	#define _simd_f64x32_add_scalar(X,Y) _simd_f64x32_add_scalar_(X,Y)
//	#define _simd_f64x32_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_add_scalar_instruction_set>()
//#else
//	#define _simd_f64x32_add_scalar(X,Y) _simd_f64x32_add_safe(X,_simd_f64x32_fill_scalar_safe(Y))
//	#define _simd_f64x32_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_f64x1_add_safe
//	#define _simd_f64x1_add_safe(X,Y) (X + Y)
//	#define _simd_f64x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_f64x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f64x1_add_enabled() true
//#endif
//
//#define _simd_f64x64_add_safe(X,Y)_simd_f64x64_combine_safe(\
//	_simd_f64x32_add_safe(_simd_f64x64_splitlo_safe(X), _simd_ f64x64_splitlo_safe(Y)),\
//	_simd_f64x32_add_safe(_simd_f64x64_splithi_safe(X), _simd_ f64x64_splithi_safe(Y)))
//#ifdef _simd_f64x64_add_
//	#define _simd_f64x64_add(X,Y) _simd_f64x64_add_(X, Y)
//	#define _simd_f64x64_add_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_add_instruction_set>()
//#else
//	#define _simd_f64x64_add(X,Y) _simd_f64x64_combine(\
//		_simd_f64x32_add(_simd_f64x64_splitlo(X), _simd_f64x64_splitlo(Y)),\
//		_simd_f64x32_add(_simd_f64x64_splithi(X), _simd_f64x64_splithi(Y)))
//	#define _simd_f64x64_add_enable() (_simd_f64x32_add_enable() && _simd_f64x64_combine_enable() && _simd_f64x64_splitlo_enable()  && _simd_f64x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_f64x64_add_) && ! defined(_simd_f64x64_add_scalar_)
//	#define _simd_f64x64_add_scalar_(X,Y) _simd_f64x64_add_(X,_simd_f64x64_fill_scalar_(Y))
//	#define _simd_f64x64_add_scalar_instruction_set _simd_f64x64_add_instruction_set
//#endif
//#ifdef _simd_f64x64_add_scalar_
//	#define _simd_f64x64_add_scalar(X,Y) _simd_f64x64_add_scalar_(X,Y)
//	#define _simd_f64x64_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_add_scalar_instruction_set>()
//#else
//	#define _simd_f64x64_add_scalar(X,Y) _simd_f64x64_add_safe(X,_simd_f64x64_fill_scalar_safe(Y))
//	#define _simd_f64x64_add_scalar_enabled() true
//#endif
//
//// -- f32 --
//
//#ifndef _simd_f32x1_add_safe
//	#define _simd_f32x1_add_safe(X,Y) (X + Y)
//	#define _simd_f32x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_f32x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_add_enabled() true
//#endif
//
//#define _simd_f32x2_add_safe(X,Y)_simd_f32x2_combine_safe(\
//	_simd_f32x1_add_safe(_simd_f32x2_splitlo_safe(X), _simd_ f32x2_splitlo_safe(Y)),\
//	_simd_f32x1_add_safe(_simd_f32x2_splithi_safe(X), _simd_ f32x2_splithi_safe(Y)))
//#ifdef _simd_f32x2_add_
//	#define _simd_f32x2_add(X,Y) _simd_f32x2_add_(X, Y)
//	#define _simd_f32x2_add_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_add_instruction_set>()
//#elif defined(_simd_f32x4_add_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_add(const register _simd_f32x2 x, const register _simd_f32x2 y) {
//		union SIMDUnion { _simd_f32x2 v1; _simd_f32x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x4_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x2_add_enable() _simd_f32x4_add_enable()
//#elif defined(_simd_f32x8_add_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_add(const register _simd_f32x2 x, const register _simd_f32x2 y) {
//		union SIMDUnion { _simd_f32x2 v1; _simd_f32x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x8_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x2_add_enable() _simd_f32x8_add_enable()
//#elif defined(_simd_f32x16_add_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_add(const register _simd_f32x2 x, const register _simd_f32x2 y) {
//		union SIMDUnion { _simd_f32x2 v1; _simd_f32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x16_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x2_add_enable() _simd_f32x16_add_enable()
//#elif defined(_simd_f32x32_add_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_add(const register _simd_f32x2 x, const register _simd_f32x2 y) {
//		union SIMDUnion { _simd_f32x2 v1; _simd_f32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x2_add_enable() _simd_f32x32_add_enable()
//#elif defined(_simd_f32x64_add_)
//	static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_add(const register _simd_f32x2 x, const register _simd_f32x2 y) {
//		union SIMDUnion { _simd_f32x2 v1; _simd_f32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x2_add_enable() _simd_f32x64_add_enable()
//#else
//	#define _simd_f32x2_add(X,Y) _simd_f32x2_combine(\
//		_simd_f32x1_add(_simd_f32x2_splitlo(X), _simd_f32x2_splitlo(Y)),\
//		_simd_f32x1_add(_simd_f32x2_splithi(X), _simd_f32x2_splithi(Y)))
//	#define _simd_f32x2_add_enable() (_simd_f32x1_add_enable() && _simd_f32x2_combine_enable() && _simd_f32x2_splitlo_enable()  && _simd_f32x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x2_add_) && ! defined(_simd_f32x2_add_scalar_)
//	#define _simd_f32x2_add_scalar_(X,Y) _simd_f32x2_add_(X,_simd_f32x2_fill_scalar_(Y))
//	#define _simd_f32x2_add_scalar_instruction_set _simd_f32x2_add_instruction_set
//#endif
//#ifdef _simd_f32x2_add_scalar_
//	#define _simd_f32x2_add_scalar(X,Y) _simd_f32x2_add_scalar_(X,Y)
//	#define _simd_f32x2_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_add_scalar_instruction_set>()
//#else
//	#define _simd_f32x2_add_scalar(X,Y) _simd_f32x2_add_safe(X,_simd_f32x2_fill_scalar_safe(Y))
//	#define _simd_f32x2_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_f32x1_add_safe
//	#define _simd_f32x1_add_safe(X,Y) (X + Y)
//	#define _simd_f32x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_f32x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_add_enabled() true
//#endif
//
//#define _simd_f32x4_add_safe(X,Y)_simd_f32x4_combine_safe(\
//	_simd_f32x2_add_safe(_simd_f32x4_splitlo_safe(X), _simd_ f32x4_splitlo_safe(Y)),\
//	_simd_f32x2_add_safe(_simd_f32x4_splithi_safe(X), _simd_ f32x4_splithi_safe(Y)))
//#ifdef _simd_f32x4_add_
//	#define _simd_f32x4_add(X,Y) _simd_f32x4_add_(X, Y)
//	#define _simd_f32x4_add_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_add_instruction_set>()
//#elif defined(_simd_f32x8_add_)
//	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_add(const register _simd_f32x4 x, const register _simd_f32x4 y) {
//		union SIMDUnion { _simd_f32x4 v1; _simd_f32x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x8_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x4_add_enable() _simd_f32x8_add_enable()
//#elif defined(_simd_f32x16_add_)
//	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_add(const register _simd_f32x4 x, const register _simd_f32x4 y) {
//		union SIMDUnion { _simd_f32x4 v1; _simd_f32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x16_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x4_add_enable() _simd_f32x16_add_enable()
//#elif defined(_simd_f32x32_add_)
//	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_add(const register _simd_f32x4 x, const register _simd_f32x4 y) {
//		union SIMDUnion { _simd_f32x4 v1; _simd_f32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x4_add_enable() _simd_f32x32_add_enable()
//#elif defined(_simd_f32x64_add_)
//	static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_add(const register _simd_f32x4 x, const register _simd_f32x4 y) {
//		union SIMDUnion { _simd_f32x4 v1; _simd_f32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x4_add_enable() _simd_f32x64_add_enable()
//#else
//	#define _simd_f32x4_add(X,Y) _simd_f32x4_combine(\
//		_simd_f32x2_add(_simd_f32x4_splitlo(X), _simd_f32x4_splitlo(Y)),\
//		_simd_f32x2_add(_simd_f32x4_splithi(X), _simd_f32x4_splithi(Y)))
//	#define _simd_f32x4_add_enable() (_simd_f32x2_add_enable() && _simd_f32x4_combine_enable() && _simd_f32x4_splitlo_enable()  && _simd_f32x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x4_add_) && ! defined(_simd_f32x4_add_scalar_)
//	#define _simd_f32x4_add_scalar_(X,Y) _simd_f32x4_add_(X,_simd_f32x4_fill_scalar_(Y))
//	#define _simd_f32x4_add_scalar_instruction_set _simd_f32x4_add_instruction_set
//#endif
//#ifdef _simd_f32x4_add_scalar_
//	#define _simd_f32x4_add_scalar(X,Y) _simd_f32x4_add_scalar_(X,Y)
//	#define _simd_f32x4_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_add_scalar_instruction_set>()
//#else
//	#define _simd_f32x4_add_scalar(X,Y) _simd_f32x4_add_safe(X,_simd_f32x4_fill_scalar_safe(Y))
//	#define _simd_f32x4_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_f32x1_add_safe
//	#define _simd_f32x1_add_safe(X,Y) (X + Y)
//	#define _simd_f32x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_f32x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_add_enabled() true
//#endif
//
//#define _simd_f32x8_add_safe(X,Y)_simd_f32x8_combine_safe(\
//	_simd_f32x4_add_safe(_simd_f32x8_splitlo_safe(X), _simd_ f32x8_splitlo_safe(Y)),\
//	_simd_f32x4_add_safe(_simd_f32x8_splithi_safe(X), _simd_ f32x8_splithi_safe(Y)))
//#ifdef _simd_f32x8_add_
//	#define _simd_f32x8_add(X,Y) _simd_f32x8_add_(X, Y)
//	#define _simd_f32x8_add_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_add_instruction_set>()
//#elif defined(_simd_f32x16_add_)
//	static ANVIL_STRONG_INLINE _simd_f32x8 ANVIL_SIMD_CALL _simd_f32x8_add(const register _simd_f32x8 x, const register _simd_f32x8 y) {
//		union SIMDUnion { _simd_f32x8 v1; _simd_f32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x16_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x8_add_enable() _simd_f32x16_add_enable()
//#elif defined(_simd_f32x32_add_)
//	static ANVIL_STRONG_INLINE _simd_f32x8 ANVIL_SIMD_CALL _simd_f32x8_add(const register _simd_f32x8 x, const register _simd_f32x8 y) {
//		union SIMDUnion { _simd_f32x8 v1; _simd_f32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x8_add_enable() _simd_f32x32_add_enable()
//#elif defined(_simd_f32x64_add_)
//	static ANVIL_STRONG_INLINE _simd_f32x8 ANVIL_SIMD_CALL _simd_f32x8_add(const register _simd_f32x8 x, const register _simd_f32x8 y) {
//		union SIMDUnion { _simd_f32x8 v1; _simd_f32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x8_add_enable() _simd_f32x64_add_enable()
//#else
//	#define _simd_f32x8_add(X,Y) _simd_f32x8_combine(\
//		_simd_f32x4_add(_simd_f32x8_splitlo(X), _simd_f32x8_splitlo(Y)),\
//		_simd_f32x4_add(_simd_f32x8_splithi(X), _simd_f32x8_splithi(Y)))
//	#define _simd_f32x8_add_enable() (_simd_f32x4_add_enable() && _simd_f32x8_combine_enable() && _simd_f32x8_splitlo_enable()  && _simd_f32x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x8_add_) && ! defined(_simd_f32x8_add_scalar_)
//	#define _simd_f32x8_add_scalar_(X,Y) _simd_f32x8_add_(X,_simd_f32x8_fill_scalar_(Y))
//	#define _simd_f32x8_add_scalar_instruction_set _simd_f32x8_add_instruction_set
//#endif
//#ifdef _simd_f32x8_add_scalar_
//	#define _simd_f32x8_add_scalar(X,Y) _simd_f32x8_add_scalar_(X,Y)
//	#define _simd_f32x8_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_add_scalar_instruction_set>()
//#else
//	#define _simd_f32x8_add_scalar(X,Y) _simd_f32x8_add_safe(X,_simd_f32x8_fill_scalar_safe(Y))
//	#define _simd_f32x8_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_f32x1_add_safe
//	#define _simd_f32x1_add_safe(X,Y) (X + Y)
//	#define _simd_f32x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_f32x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_add_enabled() true
//#endif
//
//#define _simd_f32x16_add_safe(X,Y)_simd_f32x16_combine_safe(\
//	_simd_f32x8_add_safe(_simd_f32x16_splitlo_safe(X), _simd_ f32x16_splitlo_safe(Y)),\
//	_simd_f32x8_add_safe(_simd_f32x16_splithi_safe(X), _simd_ f32x16_splithi_safe(Y)))
//#ifdef _simd_f32x16_add_
//	#define _simd_f32x16_add(X,Y) _simd_f32x16_add_(X, Y)
//	#define _simd_f32x16_add_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_add_instruction_set>()
//#elif defined(_simd_f32x32_add_)
//	static ANVIL_STRONG_INLINE _simd_f32x16 ANVIL_SIMD_CALL _simd_f32x16_add(const register _simd_f32x16 x, const register _simd_f32x16 y) {
//		union SIMDUnion { _simd_f32x16 v1; _simd_f32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x16_add_enable() _simd_f32x32_add_enable()
//#elif defined(_simd_f32x64_add_)
//	static ANVIL_STRONG_INLINE _simd_f32x16 ANVIL_SIMD_CALL _simd_f32x16_add(const register _simd_f32x16 x, const register _simd_f32x16 y) {
//		union SIMDUnion { _simd_f32x16 v1; _simd_f32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x16_add_enable() _simd_f32x64_add_enable()
//#else
//	#define _simd_f32x16_add(X,Y) _simd_f32x16_combine(\
//		_simd_f32x8_add(_simd_f32x16_splitlo(X), _simd_f32x16_splitlo(Y)),\
//		_simd_f32x8_add(_simd_f32x16_splithi(X), _simd_f32x16_splithi(Y)))
//	#define _simd_f32x16_add_enable() (_simd_f32x8_add_enable() && _simd_f32x16_combine_enable() && _simd_f32x16_splitlo_enable()  && _simd_f32x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x16_add_) && ! defined(_simd_f32x16_add_scalar_)
//	#define _simd_f32x16_add_scalar_(X,Y) _simd_f32x16_add_(X,_simd_f32x16_fill_scalar_(Y))
//	#define _simd_f32x16_add_scalar_instruction_set _simd_f32x16_add_instruction_set
//#endif
//#ifdef _simd_f32x16_add_scalar_
//	#define _simd_f32x16_add_scalar(X,Y) _simd_f32x16_add_scalar_(X,Y)
//	#define _simd_f32x16_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_add_scalar_instruction_set>()
//#else
//	#define _simd_f32x16_add_scalar(X,Y) _simd_f32x16_add_safe(X,_simd_f32x16_fill_scalar_safe(Y))
//	#define _simd_f32x16_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_f32x1_add_safe
//	#define _simd_f32x1_add_safe(X,Y) (X + Y)
//	#define _simd_f32x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_f32x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_add_enabled() true
//#endif
//
//#define _simd_f32x32_add_safe(X,Y)_simd_f32x32_combine_safe(\
//	_simd_f32x16_add_safe(_simd_f32x32_splitlo_safe(X), _simd_ f32x32_splitlo_safe(Y)),\
//	_simd_f32x16_add_safe(_simd_f32x32_splithi_safe(X), _simd_ f32x32_splithi_safe(Y)))
//#ifdef _simd_f32x32_add_
//	#define _simd_f32x32_add(X,Y) _simd_f32x32_add_(X, Y)
//	#define _simd_f32x32_add_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_add_instruction_set>()
//#elif defined(_simd_f32x64_add_)
//	static ANVIL_STRONG_INLINE _simd_f32x32 ANVIL_SIMD_CALL _simd_f32x32_add(const register _simd_f32x32 x, const register _simd_f32x32 y) {
//		union SIMDUnion { _simd_f32x32 v1; _simd_f32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_f32x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_f32x32_add_enable() _simd_f32x64_add_enable()
//#else
//	#define _simd_f32x32_add(X,Y) _simd_f32x32_combine(\
//		_simd_f32x16_add(_simd_f32x32_splitlo(X), _simd_f32x32_splitlo(Y)),\
//		_simd_f32x16_add(_simd_f32x32_splithi(X), _simd_f32x32_splithi(Y)))
//	#define _simd_f32x32_add_enable() (_simd_f32x16_add_enable() && _simd_f32x32_combine_enable() && _simd_f32x32_splitlo_enable()  && _simd_f32x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x32_add_) && ! defined(_simd_f32x32_add_scalar_)
//	#define _simd_f32x32_add_scalar_(X,Y) _simd_f32x32_add_(X,_simd_f32x32_fill_scalar_(Y))
//	#define _simd_f32x32_add_scalar_instruction_set _simd_f32x32_add_instruction_set
//#endif
//#ifdef _simd_f32x32_add_scalar_
//	#define _simd_f32x32_add_scalar(X,Y) _simd_f32x32_add_scalar_(X,Y)
//	#define _simd_f32x32_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_add_scalar_instruction_set>()
//#else
//	#define _simd_f32x32_add_scalar(X,Y) _simd_f32x32_add_safe(X,_simd_f32x32_fill_scalar_safe(Y))
//	#define _simd_f32x32_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_f32x1_add_safe
//	#define _simd_f32x1_add_safe(X,Y) (X + Y)
//	#define _simd_f32x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_f32x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_f32x1_add_enabled() true
//#endif
//
//#define _simd_f32x64_add_safe(X,Y)_simd_f32x64_combine_safe(\
//	_simd_f32x32_add_safe(_simd_f32x64_splitlo_safe(X), _simd_ f32x64_splitlo_safe(Y)),\
//	_simd_f32x32_add_safe(_simd_f32x64_splithi_safe(X), _simd_ f32x64_splithi_safe(Y)))
//#ifdef _simd_f32x64_add_
//	#define _simd_f32x64_add(X,Y) _simd_f32x64_add_(X, Y)
//	#define _simd_f32x64_add_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_add_instruction_set>()
//#else
//	#define _simd_f32x64_add(X,Y) _simd_f32x64_combine(\
//		_simd_f32x32_add(_simd_f32x64_splitlo(X), _simd_f32x64_splitlo(Y)),\
//		_simd_f32x32_add(_simd_f32x64_splithi(X), _simd_f32x64_splithi(Y)))
//	#define _simd_f32x64_add_enable() (_simd_f32x32_add_enable() && _simd_f32x64_combine_enable() && _simd_f32x64_splitlo_enable()  && _simd_f32x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_f32x64_add_) && ! defined(_simd_f32x64_add_scalar_)
//	#define _simd_f32x64_add_scalar_(X,Y) _simd_f32x64_add_(X,_simd_f32x64_fill_scalar_(Y))
//	#define _simd_f32x64_add_scalar_instruction_set _simd_f32x64_add_instruction_set
//#endif
//#ifdef _simd_f32x64_add_scalar_
//	#define _simd_f32x64_add_scalar(X,Y) _simd_f32x64_add_scalar_(X,Y)
//	#define _simd_f32x64_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_add_scalar_instruction_set>()
//#else
//	#define _simd_f32x64_add_scalar(X,Y) _simd_f32x64_add_safe(X,_simd_f32x64_fill_scalar_safe(Y))
//	#define _simd_f32x64_add_scalar_enabled() true
//#endif
//
//// -- s64 --
//
//#ifndef _simd_s64x1_add_safe
//	#define _simd_s64x1_add_safe(X,Y) (X + Y)
//	#define _simd_s64x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_s64x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_add_enabled() true
//#endif
//
//#define _simd_s64x2_add_safe(X,Y)_simd_s64x2_combine_safe(\
//	_simd_s64x1_add_safe(_simd_s64x2_splitlo_safe(X), _simd_ s64x2_splitlo_safe(Y)),\
//	_simd_s64x1_add_safe(_simd_s64x2_splithi_safe(X), _simd_ s64x2_splithi_safe(Y)))
//#ifdef _simd_s64x2_add_
//	#define _simd_s64x2_add(X,Y) _simd_s64x2_add_(X, Y)
//	#define _simd_s64x2_add_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_add_instruction_set>()
//#elif defined(_simd_s64x4_add_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_add(const register _simd_s64x2 x, const register _simd_s64x2 y) {
//		union SIMDUnion { _simd_s64x2 v1; _simd_s64x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x4_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x2_add_enable() _simd_s64x4_add_enable()
//#elif defined(_simd_s64x8_add_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_add(const register _simd_s64x2 x, const register _simd_s64x2 y) {
//		union SIMDUnion { _simd_s64x2 v1; _simd_s64x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x8_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x2_add_enable() _simd_s64x8_add_enable()
//#elif defined(_simd_s64x16_add_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_add(const register _simd_s64x2 x, const register _simd_s64x2 y) {
//		union SIMDUnion { _simd_s64x2 v1; _simd_s64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x16_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x2_add_enable() _simd_s64x16_add_enable()
//#elif defined(_simd_s64x32_add_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_add(const register _simd_s64x2 x, const register _simd_s64x2 y) {
//		union SIMDUnion { _simd_s64x2 v1; _simd_s64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x2_add_enable() _simd_s64x32_add_enable()
//#elif defined(_simd_s64x64_add_)
//	static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_add(const register _simd_s64x2 x, const register _simd_s64x2 y) {
//		union SIMDUnion { _simd_s64x2 v1; _simd_s64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x2_add_enable() _simd_s64x64_add_enable()
//#else
//	#define _simd_s64x2_add(X,Y) _simd_s64x2_combine(\
//		_simd_s64x1_add(_simd_s64x2_splitlo(X), _simd_s64x2_splitlo(Y)),\
//		_simd_s64x1_add(_simd_s64x2_splithi(X), _simd_s64x2_splithi(Y)))
//	#define _simd_s64x2_add_enable() (_simd_s64x1_add_enable() && _simd_s64x2_combine_enable() && _simd_s64x2_splitlo_enable()  && _simd_s64x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x2_add_) && ! defined(_simd_s64x2_add_scalar_)
//	#define _simd_s64x2_add_scalar_(X,Y) _simd_s64x2_add_(X,_simd_s64x2_fill_scalar_(Y))
//	#define _simd_s64x2_add_scalar_instruction_set _simd_s64x2_add_instruction_set
//#endif
//#ifdef _simd_s64x2_add_scalar_
//	#define _simd_s64x2_add_scalar(X,Y) _simd_s64x2_add_scalar_(X,Y)
//	#define _simd_s64x2_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_add_scalar_instruction_set>()
//#else
//	#define _simd_s64x2_add_scalar(X,Y) _simd_s64x2_add_safe(X,_simd_s64x2_fill_scalar_safe(Y))
//	#define _simd_s64x2_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_s64x1_add_safe
//	#define _simd_s64x1_add_safe(X,Y) (X + Y)
//	#define _simd_s64x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_s64x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_add_enabled() true
//#endif
//
//#define _simd_s64x4_add_safe(X,Y)_simd_s64x4_combine_safe(\
//	_simd_s64x2_add_safe(_simd_s64x4_splitlo_safe(X), _simd_ s64x4_splitlo_safe(Y)),\
//	_simd_s64x2_add_safe(_simd_s64x4_splithi_safe(X), _simd_ s64x4_splithi_safe(Y)))
//#ifdef _simd_s64x4_add_
//	#define _simd_s64x4_add(X,Y) _simd_s64x4_add_(X, Y)
//	#define _simd_s64x4_add_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_add_instruction_set>()
//#elif defined(_simd_s64x8_add_)
//	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_add(const register _simd_s64x4 x, const register _simd_s64x4 y) {
//		union SIMDUnion { _simd_s64x4 v1; _simd_s64x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x8_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x4_add_enable() _simd_s64x8_add_enable()
//#elif defined(_simd_s64x16_add_)
//	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_add(const register _simd_s64x4 x, const register _simd_s64x4 y) {
//		union SIMDUnion { _simd_s64x4 v1; _simd_s64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x16_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x4_add_enable() _simd_s64x16_add_enable()
//#elif defined(_simd_s64x32_add_)
//	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_add(const register _simd_s64x4 x, const register _simd_s64x4 y) {
//		union SIMDUnion { _simd_s64x4 v1; _simd_s64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x4_add_enable() _simd_s64x32_add_enable()
//#elif defined(_simd_s64x64_add_)
//	static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_add(const register _simd_s64x4 x, const register _simd_s64x4 y) {
//		union SIMDUnion { _simd_s64x4 v1; _simd_s64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x4_add_enable() _simd_s64x64_add_enable()
//#else
//	#define _simd_s64x4_add(X,Y) _simd_s64x4_combine(\
//		_simd_s64x2_add(_simd_s64x4_splitlo(X), _simd_s64x4_splitlo(Y)),\
//		_simd_s64x2_add(_simd_s64x4_splithi(X), _simd_s64x4_splithi(Y)))
//	#define _simd_s64x4_add_enable() (_simd_s64x2_add_enable() && _simd_s64x4_combine_enable() && _simd_s64x4_splitlo_enable()  && _simd_s64x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x4_add_) && ! defined(_simd_s64x4_add_scalar_)
//	#define _simd_s64x4_add_scalar_(X,Y) _simd_s64x4_add_(X,_simd_s64x4_fill_scalar_(Y))
//	#define _simd_s64x4_add_scalar_instruction_set _simd_s64x4_add_instruction_set
//#endif
//#ifdef _simd_s64x4_add_scalar_
//	#define _simd_s64x4_add_scalar(X,Y) _simd_s64x4_add_scalar_(X,Y)
//	#define _simd_s64x4_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_add_scalar_instruction_set>()
//#else
//	#define _simd_s64x4_add_scalar(X,Y) _simd_s64x4_add_safe(X,_simd_s64x4_fill_scalar_safe(Y))
//	#define _simd_s64x4_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_s64x1_add_safe
//	#define _simd_s64x1_add_safe(X,Y) (X + Y)
//	#define _simd_s64x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_s64x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_add_enabled() true
//#endif
//
//#define _simd_s64x8_add_safe(X,Y)_simd_s64x8_combine_safe(\
//	_simd_s64x4_add_safe(_simd_s64x8_splitlo_safe(X), _simd_ s64x8_splitlo_safe(Y)),\
//	_simd_s64x4_add_safe(_simd_s64x8_splithi_safe(X), _simd_ s64x8_splithi_safe(Y)))
//#ifdef _simd_s64x8_add_
//	#define _simd_s64x8_add(X,Y) _simd_s64x8_add_(X, Y)
//	#define _simd_s64x8_add_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_add_instruction_set>()
//#elif defined(_simd_s64x16_add_)
//	static ANVIL_STRONG_INLINE _simd_s64x8 ANVIL_SIMD_CALL _simd_s64x8_add(const register _simd_s64x8 x, const register _simd_s64x8 y) {
//		union SIMDUnion { _simd_s64x8 v1; _simd_s64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x16_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x8_add_enable() _simd_s64x16_add_enable()
//#elif defined(_simd_s64x32_add_)
//	static ANVIL_STRONG_INLINE _simd_s64x8 ANVIL_SIMD_CALL _simd_s64x8_add(const register _simd_s64x8 x, const register _simd_s64x8 y) {
//		union SIMDUnion { _simd_s64x8 v1; _simd_s64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x8_add_enable() _simd_s64x32_add_enable()
//#elif defined(_simd_s64x64_add_)
//	static ANVIL_STRONG_INLINE _simd_s64x8 ANVIL_SIMD_CALL _simd_s64x8_add(const register _simd_s64x8 x, const register _simd_s64x8 y) {
//		union SIMDUnion { _simd_s64x8 v1; _simd_s64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x8_add_enable() _simd_s64x64_add_enable()
//#else
//	#define _simd_s64x8_add(X,Y) _simd_s64x8_combine(\
//		_simd_s64x4_add(_simd_s64x8_splitlo(X), _simd_s64x8_splitlo(Y)),\
//		_simd_s64x4_add(_simd_s64x8_splithi(X), _simd_s64x8_splithi(Y)))
//	#define _simd_s64x8_add_enable() (_simd_s64x4_add_enable() && _simd_s64x8_combine_enable() && _simd_s64x8_splitlo_enable()  && _simd_s64x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x8_add_) && ! defined(_simd_s64x8_add_scalar_)
//	#define _simd_s64x8_add_scalar_(X,Y) _simd_s64x8_add_(X,_simd_s64x8_fill_scalar_(Y))
//	#define _simd_s64x8_add_scalar_instruction_set _simd_s64x8_add_instruction_set
//#endif
//#ifdef _simd_s64x8_add_scalar_
//	#define _simd_s64x8_add_scalar(X,Y) _simd_s64x8_add_scalar_(X,Y)
//	#define _simd_s64x8_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_add_scalar_instruction_set>()
//#else
//	#define _simd_s64x8_add_scalar(X,Y) _simd_s64x8_add_safe(X,_simd_s64x8_fill_scalar_safe(Y))
//	#define _simd_s64x8_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_s64x1_add_safe
//	#define _simd_s64x1_add_safe(X,Y) (X + Y)
//	#define _simd_s64x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_s64x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_add_enabled() true
//#endif
//
//#define _simd_s64x16_add_safe(X,Y)_simd_s64x16_combine_safe(\
//	_simd_s64x8_add_safe(_simd_s64x16_splitlo_safe(X), _simd_ s64x16_splitlo_safe(Y)),\
//	_simd_s64x8_add_safe(_simd_s64x16_splithi_safe(X), _simd_ s64x16_splithi_safe(Y)))
//#ifdef _simd_s64x16_add_
//	#define _simd_s64x16_add(X,Y) _simd_s64x16_add_(X, Y)
//	#define _simd_s64x16_add_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_add_instruction_set>()
//#elif defined(_simd_s64x32_add_)
//	static ANVIL_STRONG_INLINE _simd_s64x16 ANVIL_SIMD_CALL _simd_s64x16_add(const register _simd_s64x16 x, const register _simd_s64x16 y) {
//		union SIMDUnion { _simd_s64x16 v1; _simd_s64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x16_add_enable() _simd_s64x32_add_enable()
//#elif defined(_simd_s64x64_add_)
//	static ANVIL_STRONG_INLINE _simd_s64x16 ANVIL_SIMD_CALL _simd_s64x16_add(const register _simd_s64x16 x, const register _simd_s64x16 y) {
//		union SIMDUnion { _simd_s64x16 v1; _simd_s64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x16_add_enable() _simd_s64x64_add_enable()
//#else
//	#define _simd_s64x16_add(X,Y) _simd_s64x16_combine(\
//		_simd_s64x8_add(_simd_s64x16_splitlo(X), _simd_s64x16_splitlo(Y)),\
//		_simd_s64x8_add(_simd_s64x16_splithi(X), _simd_s64x16_splithi(Y)))
//	#define _simd_s64x16_add_enable() (_simd_s64x8_add_enable() && _simd_s64x16_combine_enable() && _simd_s64x16_splitlo_enable()  && _simd_s64x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x16_add_) && ! defined(_simd_s64x16_add_scalar_)
//	#define _simd_s64x16_add_scalar_(X,Y) _simd_s64x16_add_(X,_simd_s64x16_fill_scalar_(Y))
//	#define _simd_s64x16_add_scalar_instruction_set _simd_s64x16_add_instruction_set
//#endif
//#ifdef _simd_s64x16_add_scalar_
//	#define _simd_s64x16_add_scalar(X,Y) _simd_s64x16_add_scalar_(X,Y)
//	#define _simd_s64x16_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_add_scalar_instruction_set>()
//#else
//	#define _simd_s64x16_add_scalar(X,Y) _simd_s64x16_add_safe(X,_simd_s64x16_fill_scalar_safe(Y))
//	#define _simd_s64x16_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_s64x1_add_safe
//	#define _simd_s64x1_add_safe(X,Y) (X + Y)
//	#define _simd_s64x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_s64x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_add_enabled() true
//#endif
//
//#define _simd_s64x32_add_safe(X,Y)_simd_s64x32_combine_safe(\
//	_simd_s64x16_add_safe(_simd_s64x32_splitlo_safe(X), _simd_ s64x32_splitlo_safe(Y)),\
//	_simd_s64x16_add_safe(_simd_s64x32_splithi_safe(X), _simd_ s64x32_splithi_safe(Y)))
//#ifdef _simd_s64x32_add_
//	#define _simd_s64x32_add(X,Y) _simd_s64x32_add_(X, Y)
//	#define _simd_s64x32_add_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_add_instruction_set>()
//#elif defined(_simd_s64x64_add_)
//	static ANVIL_STRONG_INLINE _simd_s64x32 ANVIL_SIMD_CALL _simd_s64x32_add(const register _simd_s64x32 x, const register _simd_s64x32 y) {
//		union SIMDUnion { _simd_s64x32 v1; _simd_s64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s64x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s64x32_add_enable() _simd_s64x64_add_enable()
//#else
//	#define _simd_s64x32_add(X,Y) _simd_s64x32_combine(\
//		_simd_s64x16_add(_simd_s64x32_splitlo(X), _simd_s64x32_splitlo(Y)),\
//		_simd_s64x16_add(_simd_s64x32_splithi(X), _simd_s64x32_splithi(Y)))
//	#define _simd_s64x32_add_enable() (_simd_s64x16_add_enable() && _simd_s64x32_combine_enable() && _simd_s64x32_splitlo_enable()  && _simd_s64x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x32_add_) && ! defined(_simd_s64x32_add_scalar_)
//	#define _simd_s64x32_add_scalar_(X,Y) _simd_s64x32_add_(X,_simd_s64x32_fill_scalar_(Y))
//	#define _simd_s64x32_add_scalar_instruction_set _simd_s64x32_add_instruction_set
//#endif
//#ifdef _simd_s64x32_add_scalar_
//	#define _simd_s64x32_add_scalar(X,Y) _simd_s64x32_add_scalar_(X,Y)
//	#define _simd_s64x32_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_add_scalar_instruction_set>()
//#else
//	#define _simd_s64x32_add_scalar(X,Y) _simd_s64x32_add_safe(X,_simd_s64x32_fill_scalar_safe(Y))
//	#define _simd_s64x32_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_s64x1_add_safe
//	#define _simd_s64x1_add_safe(X,Y) (X + Y)
//	#define _simd_s64x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_s64x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s64x1_add_enabled() true
//#endif
//
//#define _simd_s64x64_add_safe(X,Y)_simd_s64x64_combine_safe(\
//	_simd_s64x32_add_safe(_simd_s64x64_splitlo_safe(X), _simd_ s64x64_splitlo_safe(Y)),\
//	_simd_s64x32_add_safe(_simd_s64x64_splithi_safe(X), _simd_ s64x64_splithi_safe(Y)))
//#ifdef _simd_s64x64_add_
//	#define _simd_s64x64_add(X,Y) _simd_s64x64_add_(X, Y)
//	#define _simd_s64x64_add_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_add_instruction_set>()
//#else
//	#define _simd_s64x64_add(X,Y) _simd_s64x64_combine(\
//		_simd_s64x32_add(_simd_s64x64_splitlo(X), _simd_s64x64_splitlo(Y)),\
//		_simd_s64x32_add(_simd_s64x64_splithi(X), _simd_s64x64_splithi(Y)))
//	#define _simd_s64x64_add_enable() (_simd_s64x32_add_enable() && _simd_s64x64_combine_enable() && _simd_s64x64_splitlo_enable()  && _simd_s64x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_s64x64_add_) && ! defined(_simd_s64x64_add_scalar_)
//	#define _simd_s64x64_add_scalar_(X,Y) _simd_s64x64_add_(X,_simd_s64x64_fill_scalar_(Y))
//	#define _simd_s64x64_add_scalar_instruction_set _simd_s64x64_add_instruction_set
//#endif
//#ifdef _simd_s64x64_add_scalar_
//	#define _simd_s64x64_add_scalar(X,Y) _simd_s64x64_add_scalar_(X,Y)
//	#define _simd_s64x64_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_add_scalar_instruction_set>()
//#else
//	#define _simd_s64x64_add_scalar(X,Y) _simd_s64x64_add_safe(X,_simd_s64x64_fill_scalar_safe(Y))
//	#define _simd_s64x64_add_scalar_enabled() true
//#endif
//
//// -- u64 --
//
//#ifndef _simd_u64x1_add_safe
//	#define _simd_u64x1_add_safe(X,Y) (X + Y)
//	#define _simd_u64x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_u64x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_add_enabled() true
//#endif
//
//#define _simd_u64x2_add_safe(X,Y)_simd_u64x2_combine_safe(\
//	_simd_u64x1_add_safe(_simd_u64x2_splitlo_safe(X), _simd_ u64x2_splitlo_safe(Y)),\
//	_simd_u64x1_add_safe(_simd_u64x2_splithi_safe(X), _simd_ u64x2_splithi_safe(Y)))
//#ifdef _simd_u64x2_add_
//	#define _simd_u64x2_add(X,Y) _simd_u64x2_add_(X, Y)
//	#define _simd_u64x2_add_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_add_instruction_set>()
//#elif defined(_simd_u64x4_add_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_add(const register _simd_u64x2 x, const register _simd_u64x2 y) {
//		union SIMDUnion { _simd_u64x2 v1; _simd_u64x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x4_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x2_add_enable() _simd_u64x4_add_enable()
//#elif defined(_simd_u64x8_add_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_add(const register _simd_u64x2 x, const register _simd_u64x2 y) {
//		union SIMDUnion { _simd_u64x2 v1; _simd_u64x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x8_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x2_add_enable() _simd_u64x8_add_enable()
//#elif defined(_simd_u64x16_add_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_add(const register _simd_u64x2 x, const register _simd_u64x2 y) {
//		union SIMDUnion { _simd_u64x2 v1; _simd_u64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x16_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x2_add_enable() _simd_u64x16_add_enable()
//#elif defined(_simd_u64x32_add_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_add(const register _simd_u64x2 x, const register _simd_u64x2 y) {
//		union SIMDUnion { _simd_u64x2 v1; _simd_u64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x2_add_enable() _simd_u64x32_add_enable()
//#elif defined(_simd_u64x64_add_)
//	static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_add(const register _simd_u64x2 x, const register _simd_u64x2 y) {
//		union SIMDUnion { _simd_u64x2 v1; _simd_u64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x2_add_enable() _simd_u64x64_add_enable()
//#else
//	#define _simd_u64x2_add(X,Y) _simd_u64x2_combine(\
//		_simd_u64x1_add(_simd_u64x2_splitlo(X), _simd_u64x2_splitlo(Y)),\
//		_simd_u64x1_add(_simd_u64x2_splithi(X), _simd_u64x2_splithi(Y)))
//	#define _simd_u64x2_add_enable() (_simd_u64x1_add_enable() && _simd_u64x2_combine_enable() && _simd_u64x2_splitlo_enable()  && _simd_u64x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x2_add_) && ! defined(_simd_u64x2_add_scalar_)
//	#define _simd_u64x2_add_scalar_(X,Y) _simd_u64x2_add_(X,_simd_u64x2_fill_scalar_(Y))
//	#define _simd_u64x2_add_scalar_instruction_set _simd_u64x2_add_instruction_set
//#endif
//#ifdef _simd_u64x2_add_scalar_
//	#define _simd_u64x2_add_scalar(X,Y) _simd_u64x2_add_scalar_(X,Y)
//	#define _simd_u64x2_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_add_scalar_instruction_set>()
//#else
//	#define _simd_u64x2_add_scalar(X,Y) _simd_u64x2_add_safe(X,_simd_u64x2_fill_scalar_safe(Y))
//	#define _simd_u64x2_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_u64x1_add_safe
//	#define _simd_u64x1_add_safe(X,Y) (X + Y)
//	#define _simd_u64x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_u64x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_add_enabled() true
//#endif
//
//#define _simd_u64x4_add_safe(X,Y)_simd_u64x4_combine_safe(\
//	_simd_u64x2_add_safe(_simd_u64x4_splitlo_safe(X), _simd_ u64x4_splitlo_safe(Y)),\
//	_simd_u64x2_add_safe(_simd_u64x4_splithi_safe(X), _simd_ u64x4_splithi_safe(Y)))
//#ifdef _simd_u64x4_add_
//	#define _simd_u64x4_add(X,Y) _simd_u64x4_add_(X, Y)
//	#define _simd_u64x4_add_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_add_instruction_set>()
//#elif defined(_simd_u64x8_add_)
//	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_add(const register _simd_u64x4 x, const register _simd_u64x4 y) {
//		union SIMDUnion { _simd_u64x4 v1; _simd_u64x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x8_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x4_add_enable() _simd_u64x8_add_enable()
//#elif defined(_simd_u64x16_add_)
//	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_add(const register _simd_u64x4 x, const register _simd_u64x4 y) {
//		union SIMDUnion { _simd_u64x4 v1; _simd_u64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x16_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x4_add_enable() _simd_u64x16_add_enable()
//#elif defined(_simd_u64x32_add_)
//	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_add(const register _simd_u64x4 x, const register _simd_u64x4 y) {
//		union SIMDUnion { _simd_u64x4 v1; _simd_u64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x4_add_enable() _simd_u64x32_add_enable()
//#elif defined(_simd_u64x64_add_)
//	static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_add(const register _simd_u64x4 x, const register _simd_u64x4 y) {
//		union SIMDUnion { _simd_u64x4 v1; _simd_u64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x4_add_enable() _simd_u64x64_add_enable()
//#else
//	#define _simd_u64x4_add(X,Y) _simd_u64x4_combine(\
//		_simd_u64x2_add(_simd_u64x4_splitlo(X), _simd_u64x4_splitlo(Y)),\
//		_simd_u64x2_add(_simd_u64x4_splithi(X), _simd_u64x4_splithi(Y)))
//	#define _simd_u64x4_add_enable() (_simd_u64x2_add_enable() && _simd_u64x4_combine_enable() && _simd_u64x4_splitlo_enable()  && _simd_u64x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x4_add_) && ! defined(_simd_u64x4_add_scalar_)
//	#define _simd_u64x4_add_scalar_(X,Y) _simd_u64x4_add_(X,_simd_u64x4_fill_scalar_(Y))
//	#define _simd_u64x4_add_scalar_instruction_set _simd_u64x4_add_instruction_set
//#endif
//#ifdef _simd_u64x4_add_scalar_
//	#define _simd_u64x4_add_scalar(X,Y) _simd_u64x4_add_scalar_(X,Y)
//	#define _simd_u64x4_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_add_scalar_instruction_set>()
//#else
//	#define _simd_u64x4_add_scalar(X,Y) _simd_u64x4_add_safe(X,_simd_u64x4_fill_scalar_safe(Y))
//	#define _simd_u64x4_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_u64x1_add_safe
//	#define _simd_u64x1_add_safe(X,Y) (X + Y)
//	#define _simd_u64x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_u64x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_add_enabled() true
//#endif
//
//#define _simd_u64x8_add_safe(X,Y)_simd_u64x8_combine_safe(\
//	_simd_u64x4_add_safe(_simd_u64x8_splitlo_safe(X), _simd_ u64x8_splitlo_safe(Y)),\
//	_simd_u64x4_add_safe(_simd_u64x8_splithi_safe(X), _simd_ u64x8_splithi_safe(Y)))
//#ifdef _simd_u64x8_add_
//	#define _simd_u64x8_add(X,Y) _simd_u64x8_add_(X, Y)
//	#define _simd_u64x8_add_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_add_instruction_set>()
//#elif defined(_simd_u64x16_add_)
//	static ANVIL_STRONG_INLINE _simd_u64x8 ANVIL_SIMD_CALL _simd_u64x8_add(const register _simd_u64x8 x, const register _simd_u64x8 y) {
//		union SIMDUnion { _simd_u64x8 v1; _simd_u64x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x16_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x8_add_enable() _simd_u64x16_add_enable()
//#elif defined(_simd_u64x32_add_)
//	static ANVIL_STRONG_INLINE _simd_u64x8 ANVIL_SIMD_CALL _simd_u64x8_add(const register _simd_u64x8 x, const register _simd_u64x8 y) {
//		union SIMDUnion { _simd_u64x8 v1; _simd_u64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x8_add_enable() _simd_u64x32_add_enable()
//#elif defined(_simd_u64x64_add_)
//	static ANVIL_STRONG_INLINE _simd_u64x8 ANVIL_SIMD_CALL _simd_u64x8_add(const register _simd_u64x8 x, const register _simd_u64x8 y) {
//		union SIMDUnion { _simd_u64x8 v1; _simd_u64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x8_add_enable() _simd_u64x64_add_enable()
//#else
//	#define _simd_u64x8_add(X,Y) _simd_u64x8_combine(\
//		_simd_u64x4_add(_simd_u64x8_splitlo(X), _simd_u64x8_splitlo(Y)),\
//		_simd_u64x4_add(_simd_u64x8_splithi(X), _simd_u64x8_splithi(Y)))
//	#define _simd_u64x8_add_enable() (_simd_u64x4_add_enable() && _simd_u64x8_combine_enable() && _simd_u64x8_splitlo_enable()  && _simd_u64x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x8_add_) && ! defined(_simd_u64x8_add_scalar_)
//	#define _simd_u64x8_add_scalar_(X,Y) _simd_u64x8_add_(X,_simd_u64x8_fill_scalar_(Y))
//	#define _simd_u64x8_add_scalar_instruction_set _simd_u64x8_add_instruction_set
//#endif
//#ifdef _simd_u64x8_add_scalar_
//	#define _simd_u64x8_add_scalar(X,Y) _simd_u64x8_add_scalar_(X,Y)
//	#define _simd_u64x8_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_add_scalar_instruction_set>()
//#else
//	#define _simd_u64x8_add_scalar(X,Y) _simd_u64x8_add_safe(X,_simd_u64x8_fill_scalar_safe(Y))
//	#define _simd_u64x8_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_u64x1_add_safe
//	#define _simd_u64x1_add_safe(X,Y) (X + Y)
//	#define _simd_u64x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_u64x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_add_enabled() true
//#endif
//
//#define _simd_u64x16_add_safe(X,Y)_simd_u64x16_combine_safe(\
//	_simd_u64x8_add_safe(_simd_u64x16_splitlo_safe(X), _simd_ u64x16_splitlo_safe(Y)),\
//	_simd_u64x8_add_safe(_simd_u64x16_splithi_safe(X), _simd_ u64x16_splithi_safe(Y)))
//#ifdef _simd_u64x16_add_
//	#define _simd_u64x16_add(X,Y) _simd_u64x16_add_(X, Y)
//	#define _simd_u64x16_add_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_add_instruction_set>()
//#elif defined(_simd_u64x32_add_)
//	static ANVIL_STRONG_INLINE _simd_u64x16 ANVIL_SIMD_CALL _simd_u64x16_add(const register _simd_u64x16 x, const register _simd_u64x16 y) {
//		union SIMDUnion { _simd_u64x16 v1; _simd_u64x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x16_add_enable() _simd_u64x32_add_enable()
//#elif defined(_simd_u64x64_add_)
//	static ANVIL_STRONG_INLINE _simd_u64x16 ANVIL_SIMD_CALL _simd_u64x16_add(const register _simd_u64x16 x, const register _simd_u64x16 y) {
//		union SIMDUnion { _simd_u64x16 v1; _simd_u64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x16_add_enable() _simd_u64x64_add_enable()
//#else
//	#define _simd_u64x16_add(X,Y) _simd_u64x16_combine(\
//		_simd_u64x8_add(_simd_u64x16_splitlo(X), _simd_u64x16_splitlo(Y)),\
//		_simd_u64x8_add(_simd_u64x16_splithi(X), _simd_u64x16_splithi(Y)))
//	#define _simd_u64x16_add_enable() (_simd_u64x8_add_enable() && _simd_u64x16_combine_enable() && _simd_u64x16_splitlo_enable()  && _simd_u64x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x16_add_) && ! defined(_simd_u64x16_add_scalar_)
//	#define _simd_u64x16_add_scalar_(X,Y) _simd_u64x16_add_(X,_simd_u64x16_fill_scalar_(Y))
//	#define _simd_u64x16_add_scalar_instruction_set _simd_u64x16_add_instruction_set
//#endif
//#ifdef _simd_u64x16_add_scalar_
//	#define _simd_u64x16_add_scalar(X,Y) _simd_u64x16_add_scalar_(X,Y)
//	#define _simd_u64x16_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_add_scalar_instruction_set>()
//#else
//	#define _simd_u64x16_add_scalar(X,Y) _simd_u64x16_add_safe(X,_simd_u64x16_fill_scalar_safe(Y))
//	#define _simd_u64x16_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_u64x1_add_safe
//	#define _simd_u64x1_add_safe(X,Y) (X + Y)
//	#define _simd_u64x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_u64x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_add_enabled() true
//#endif
//
//#define _simd_u64x32_add_safe(X,Y)_simd_u64x32_combine_safe(\
//	_simd_u64x16_add_safe(_simd_u64x32_splitlo_safe(X), _simd_ u64x32_splitlo_safe(Y)),\
//	_simd_u64x16_add_safe(_simd_u64x32_splithi_safe(X), _simd_ u64x32_splithi_safe(Y)))
//#ifdef _simd_u64x32_add_
//	#define _simd_u64x32_add(X,Y) _simd_u64x32_add_(X, Y)
//	#define _simd_u64x32_add_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_add_instruction_set>()
//#elif defined(_simd_u64x64_add_)
//	static ANVIL_STRONG_INLINE _simd_u64x32 ANVIL_SIMD_CALL _simd_u64x32_add(const register _simd_u64x32 x, const register _simd_u64x32 y) {
//		union SIMDUnion { _simd_u64x32 v1; _simd_u64x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u64x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u64x32_add_enable() _simd_u64x64_add_enable()
//#else
//	#define _simd_u64x32_add(X,Y) _simd_u64x32_combine(\
//		_simd_u64x16_add(_simd_u64x32_splitlo(X), _simd_u64x32_splitlo(Y)),\
//		_simd_u64x16_add(_simd_u64x32_splithi(X), _simd_u64x32_splithi(Y)))
//	#define _simd_u64x32_add_enable() (_simd_u64x16_add_enable() && _simd_u64x32_combine_enable() && _simd_u64x32_splitlo_enable()  && _simd_u64x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x32_add_) && ! defined(_simd_u64x32_add_scalar_)
//	#define _simd_u64x32_add_scalar_(X,Y) _simd_u64x32_add_(X,_simd_u64x32_fill_scalar_(Y))
//	#define _simd_u64x32_add_scalar_instruction_set _simd_u64x32_add_instruction_set
//#endif
//#ifdef _simd_u64x32_add_scalar_
//	#define _simd_u64x32_add_scalar(X,Y) _simd_u64x32_add_scalar_(X,Y)
//	#define _simd_u64x32_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_add_scalar_instruction_set>()
//#else
//	#define _simd_u64x32_add_scalar(X,Y) _simd_u64x32_add_safe(X,_simd_u64x32_fill_scalar_safe(Y))
//	#define _simd_u64x32_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_u64x1_add_safe
//	#define _simd_u64x1_add_safe(X,Y) (X + Y)
//	#define _simd_u64x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_u64x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u64x1_add_enabled() true
//#endif
//
//#define _simd_u64x64_add_safe(X,Y)_simd_u64x64_combine_safe(\
//	_simd_u64x32_add_safe(_simd_u64x64_splitlo_safe(X), _simd_ u64x64_splitlo_safe(Y)),\
//	_simd_u64x32_add_safe(_simd_u64x64_splithi_safe(X), _simd_ u64x64_splithi_safe(Y)))
//#ifdef _simd_u64x64_add_
//	#define _simd_u64x64_add(X,Y) _simd_u64x64_add_(X, Y)
//	#define _simd_u64x64_add_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_add_instruction_set>()
//#else
//	#define _simd_u64x64_add(X,Y) _simd_u64x64_combine(\
//		_simd_u64x32_add(_simd_u64x64_splitlo(X), _simd_u64x64_splitlo(Y)),\
//		_simd_u64x32_add(_simd_u64x64_splithi(X), _simd_u64x64_splithi(Y)))
//	#define _simd_u64x64_add_enable() (_simd_u64x32_add_enable() && _simd_u64x64_combine_enable() && _simd_u64x64_splitlo_enable()  && _simd_u64x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_u64x64_add_) && ! defined(_simd_u64x64_add_scalar_)
//	#define _simd_u64x64_add_scalar_(X,Y) _simd_u64x64_add_(X,_simd_u64x64_fill_scalar_(Y))
//	#define _simd_u64x64_add_scalar_instruction_set _simd_u64x64_add_instruction_set
//#endif
//#ifdef _simd_u64x64_add_scalar_
//	#define _simd_u64x64_add_scalar(X,Y) _simd_u64x64_add_scalar_(X,Y)
//	#define _simd_u64x64_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_add_scalar_instruction_set>()
//#else
//	#define _simd_u64x64_add_scalar(X,Y) _simd_u64x64_add_safe(X,_simd_u64x64_fill_scalar_safe(Y))
//	#define _simd_u64x64_add_scalar_enabled() true
//#endif
//
//// -- s32 --
//
//#ifndef _simd_s32x1_add_safe
//	#define _simd_s32x1_add_safe(X,Y) (X + Y)
//	#define _simd_s32x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_s32x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_add_enabled() true
//#endif
//
//#define _simd_s32x2_add_safe(X,Y)_simd_s32x2_combine_safe(\
//	_simd_s32x1_add_safe(_simd_s32x2_splitlo_safe(X), _simd_ s32x2_splitlo_safe(Y)),\
//	_simd_s32x1_add_safe(_simd_s32x2_splithi_safe(X), _simd_ s32x2_splithi_safe(Y)))
//#ifdef _simd_s32x2_add_
//	#define _simd_s32x2_add(X,Y) _simd_s32x2_add_(X, Y)
//	#define _simd_s32x2_add_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_add_instruction_set>()
//#elif defined(_simd_s32x4_add_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_add(const register _simd_s32x2 x, const register _simd_s32x2 y) {
//		union SIMDUnion { _simd_s32x2 v1; _simd_s32x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x4_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x2_add_enable() _simd_s32x4_add_enable()
//#elif defined(_simd_s32x8_add_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_add(const register _simd_s32x2 x, const register _simd_s32x2 y) {
//		union SIMDUnion { _simd_s32x2 v1; _simd_s32x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x8_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x2_add_enable() _simd_s32x8_add_enable()
//#elif defined(_simd_s32x16_add_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_add(const register _simd_s32x2 x, const register _simd_s32x2 y) {
//		union SIMDUnion { _simd_s32x2 v1; _simd_s32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x16_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x2_add_enable() _simd_s32x16_add_enable()
//#elif defined(_simd_s32x32_add_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_add(const register _simd_s32x2 x, const register _simd_s32x2 y) {
//		union SIMDUnion { _simd_s32x2 v1; _simd_s32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x2_add_enable() _simd_s32x32_add_enable()
//#elif defined(_simd_s32x64_add_)
//	static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_add(const register _simd_s32x2 x, const register _simd_s32x2 y) {
//		union SIMDUnion { _simd_s32x2 v1; _simd_s32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x2_add_enable() _simd_s32x64_add_enable()
//#else
//	#define _simd_s32x2_add(X,Y) _simd_s32x2_combine(\
//		_simd_s32x1_add(_simd_s32x2_splitlo(X), _simd_s32x2_splitlo(Y)),\
//		_simd_s32x1_add(_simd_s32x2_splithi(X), _simd_s32x2_splithi(Y)))
//	#define _simd_s32x2_add_enable() (_simd_s32x1_add_enable() && _simd_s32x2_combine_enable() && _simd_s32x2_splitlo_enable()  && _simd_s32x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x2_add_) && ! defined(_simd_s32x2_add_scalar_)
//	#define _simd_s32x2_add_scalar_(X,Y) _simd_s32x2_add_(X,_simd_s32x2_fill_scalar_(Y))
//	#define _simd_s32x2_add_scalar_instruction_set _simd_s32x2_add_instruction_set
//#endif
//#ifdef _simd_s32x2_add_scalar_
//	#define _simd_s32x2_add_scalar(X,Y) _simd_s32x2_add_scalar_(X,Y)
//	#define _simd_s32x2_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_add_scalar_instruction_set>()
//#else
//	#define _simd_s32x2_add_scalar(X,Y) _simd_s32x2_add_safe(X,_simd_s32x2_fill_scalar_safe(Y))
//	#define _simd_s32x2_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_s32x1_add_safe
//	#define _simd_s32x1_add_safe(X,Y) (X + Y)
//	#define _simd_s32x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_s32x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_add_enabled() true
//#endif
//
//#define _simd_s32x4_add_safe(X,Y)_simd_s32x4_combine_safe(\
//	_simd_s32x2_add_safe(_simd_s32x4_splitlo_safe(X), _simd_ s32x4_splitlo_safe(Y)),\
//	_simd_s32x2_add_safe(_simd_s32x4_splithi_safe(X), _simd_ s32x4_splithi_safe(Y)))
//#ifdef _simd_s32x4_add_
//	#define _simd_s32x4_add(X,Y) _simd_s32x4_add_(X, Y)
//	#define _simd_s32x4_add_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_add_instruction_set>()
//#elif defined(_simd_s32x8_add_)
//	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_add(const register _simd_s32x4 x, const register _simd_s32x4 y) {
//		union SIMDUnion { _simd_s32x4 v1; _simd_s32x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x8_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x4_add_enable() _simd_s32x8_add_enable()
//#elif defined(_simd_s32x16_add_)
//	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_add(const register _simd_s32x4 x, const register _simd_s32x4 y) {
//		union SIMDUnion { _simd_s32x4 v1; _simd_s32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x16_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x4_add_enable() _simd_s32x16_add_enable()
//#elif defined(_simd_s32x32_add_)
//	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_add(const register _simd_s32x4 x, const register _simd_s32x4 y) {
//		union SIMDUnion { _simd_s32x4 v1; _simd_s32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x4_add_enable() _simd_s32x32_add_enable()
//#elif defined(_simd_s32x64_add_)
//	static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_add(const register _simd_s32x4 x, const register _simd_s32x4 y) {
//		union SIMDUnion { _simd_s32x4 v1; _simd_s32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x4_add_enable() _simd_s32x64_add_enable()
//#else
//	#define _simd_s32x4_add(X,Y) _simd_s32x4_combine(\
//		_simd_s32x2_add(_simd_s32x4_splitlo(X), _simd_s32x4_splitlo(Y)),\
//		_simd_s32x2_add(_simd_s32x4_splithi(X), _simd_s32x4_splithi(Y)))
//	#define _simd_s32x4_add_enable() (_simd_s32x2_add_enable() && _simd_s32x4_combine_enable() && _simd_s32x4_splitlo_enable()  && _simd_s32x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x4_add_) && ! defined(_simd_s32x4_add_scalar_)
//	#define _simd_s32x4_add_scalar_(X,Y) _simd_s32x4_add_(X,_simd_s32x4_fill_scalar_(Y))
//	#define _simd_s32x4_add_scalar_instruction_set _simd_s32x4_add_instruction_set
//#endif
//#ifdef _simd_s32x4_add_scalar_
//	#define _simd_s32x4_add_scalar(X,Y) _simd_s32x4_add_scalar_(X,Y)
//	#define _simd_s32x4_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_add_scalar_instruction_set>()
//#else
//	#define _simd_s32x4_add_scalar(X,Y) _simd_s32x4_add_safe(X,_simd_s32x4_fill_scalar_safe(Y))
//	#define _simd_s32x4_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_s32x1_add_safe
//	#define _simd_s32x1_add_safe(X,Y) (X + Y)
//	#define _simd_s32x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_s32x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_add_enabled() true
//#endif
//
//#define _simd_s32x8_add_safe(X,Y)_simd_s32x8_combine_safe(\
//	_simd_s32x4_add_safe(_simd_s32x8_splitlo_safe(X), _simd_ s32x8_splitlo_safe(Y)),\
//	_simd_s32x4_add_safe(_simd_s32x8_splithi_safe(X), _simd_ s32x8_splithi_safe(Y)))
//#ifdef _simd_s32x8_add_
//	#define _simd_s32x8_add(X,Y) _simd_s32x8_add_(X, Y)
//	#define _simd_s32x8_add_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_add_instruction_set>()
//#elif defined(_simd_s32x16_add_)
//	static ANVIL_STRONG_INLINE _simd_s32x8 ANVIL_SIMD_CALL _simd_s32x8_add(const register _simd_s32x8 x, const register _simd_s32x8 y) {
//		union SIMDUnion { _simd_s32x8 v1; _simd_s32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x16_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x8_add_enable() _simd_s32x16_add_enable()
//#elif defined(_simd_s32x32_add_)
//	static ANVIL_STRONG_INLINE _simd_s32x8 ANVIL_SIMD_CALL _simd_s32x8_add(const register _simd_s32x8 x, const register _simd_s32x8 y) {
//		union SIMDUnion { _simd_s32x8 v1; _simd_s32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x8_add_enable() _simd_s32x32_add_enable()
//#elif defined(_simd_s32x64_add_)
//	static ANVIL_STRONG_INLINE _simd_s32x8 ANVIL_SIMD_CALL _simd_s32x8_add(const register _simd_s32x8 x, const register _simd_s32x8 y) {
//		union SIMDUnion { _simd_s32x8 v1; _simd_s32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x8_add_enable() _simd_s32x64_add_enable()
//#else
//	#define _simd_s32x8_add(X,Y) _simd_s32x8_combine(\
//		_simd_s32x4_add(_simd_s32x8_splitlo(X), _simd_s32x8_splitlo(Y)),\
//		_simd_s32x4_add(_simd_s32x8_splithi(X), _simd_s32x8_splithi(Y)))
//	#define _simd_s32x8_add_enable() (_simd_s32x4_add_enable() && _simd_s32x8_combine_enable() && _simd_s32x8_splitlo_enable()  && _simd_s32x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x8_add_) && ! defined(_simd_s32x8_add_scalar_)
//	#define _simd_s32x8_add_scalar_(X,Y) _simd_s32x8_add_(X,_simd_s32x8_fill_scalar_(Y))
//	#define _simd_s32x8_add_scalar_instruction_set _simd_s32x8_add_instruction_set
//#endif
//#ifdef _simd_s32x8_add_scalar_
//	#define _simd_s32x8_add_scalar(X,Y) _simd_s32x8_add_scalar_(X,Y)
//	#define _simd_s32x8_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_add_scalar_instruction_set>()
//#else
//	#define _simd_s32x8_add_scalar(X,Y) _simd_s32x8_add_safe(X,_simd_s32x8_fill_scalar_safe(Y))
//	#define _simd_s32x8_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_s32x1_add_safe
//	#define _simd_s32x1_add_safe(X,Y) (X + Y)
//	#define _simd_s32x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_s32x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_add_enabled() true
//#endif
//
//#define _simd_s32x16_add_safe(X,Y)_simd_s32x16_combine_safe(\
//	_simd_s32x8_add_safe(_simd_s32x16_splitlo_safe(X), _simd_ s32x16_splitlo_safe(Y)),\
//	_simd_s32x8_add_safe(_simd_s32x16_splithi_safe(X), _simd_ s32x16_splithi_safe(Y)))
//#ifdef _simd_s32x16_add_
//	#define _simd_s32x16_add(X,Y) _simd_s32x16_add_(X, Y)
//	#define _simd_s32x16_add_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_add_instruction_set>()
//#elif defined(_simd_s32x32_add_)
//	static ANVIL_STRONG_INLINE _simd_s32x16 ANVIL_SIMD_CALL _simd_s32x16_add(const register _simd_s32x16 x, const register _simd_s32x16 y) {
//		union SIMDUnion { _simd_s32x16 v1; _simd_s32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x16_add_enable() _simd_s32x32_add_enable()
//#elif defined(_simd_s32x64_add_)
//	static ANVIL_STRONG_INLINE _simd_s32x16 ANVIL_SIMD_CALL _simd_s32x16_add(const register _simd_s32x16 x, const register _simd_s32x16 y) {
//		union SIMDUnion { _simd_s32x16 v1; _simd_s32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x16_add_enable() _simd_s32x64_add_enable()
//#else
//	#define _simd_s32x16_add(X,Y) _simd_s32x16_combine(\
//		_simd_s32x8_add(_simd_s32x16_splitlo(X), _simd_s32x16_splitlo(Y)),\
//		_simd_s32x8_add(_simd_s32x16_splithi(X), _simd_s32x16_splithi(Y)))
//	#define _simd_s32x16_add_enable() (_simd_s32x8_add_enable() && _simd_s32x16_combine_enable() && _simd_s32x16_splitlo_enable()  && _simd_s32x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x16_add_) && ! defined(_simd_s32x16_add_scalar_)
//	#define _simd_s32x16_add_scalar_(X,Y) _simd_s32x16_add_(X,_simd_s32x16_fill_scalar_(Y))
//	#define _simd_s32x16_add_scalar_instruction_set _simd_s32x16_add_instruction_set
//#endif
//#ifdef _simd_s32x16_add_scalar_
//	#define _simd_s32x16_add_scalar(X,Y) _simd_s32x16_add_scalar_(X,Y)
//	#define _simd_s32x16_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_add_scalar_instruction_set>()
//#else
//	#define _simd_s32x16_add_scalar(X,Y) _simd_s32x16_add_safe(X,_simd_s32x16_fill_scalar_safe(Y))
//	#define _simd_s32x16_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_s32x1_add_safe
//	#define _simd_s32x1_add_safe(X,Y) (X + Y)
//	#define _simd_s32x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_s32x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_add_enabled() true
//#endif
//
//#define _simd_s32x32_add_safe(X,Y)_simd_s32x32_combine_safe(\
//	_simd_s32x16_add_safe(_simd_s32x32_splitlo_safe(X), _simd_ s32x32_splitlo_safe(Y)),\
//	_simd_s32x16_add_safe(_simd_s32x32_splithi_safe(X), _simd_ s32x32_splithi_safe(Y)))
//#ifdef _simd_s32x32_add_
//	#define _simd_s32x32_add(X,Y) _simd_s32x32_add_(X, Y)
//	#define _simd_s32x32_add_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_add_instruction_set>()
//#elif defined(_simd_s32x64_add_)
//	static ANVIL_STRONG_INLINE _simd_s32x32 ANVIL_SIMD_CALL _simd_s32x32_add(const register _simd_s32x32 x, const register _simd_s32x32 y) {
//		union SIMDUnion { _simd_s32x32 v1; _simd_s32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s32x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s32x32_add_enable() _simd_s32x64_add_enable()
//#else
//	#define _simd_s32x32_add(X,Y) _simd_s32x32_combine(\
//		_simd_s32x16_add(_simd_s32x32_splitlo(X), _simd_s32x32_splitlo(Y)),\
//		_simd_s32x16_add(_simd_s32x32_splithi(X), _simd_s32x32_splithi(Y)))
//	#define _simd_s32x32_add_enable() (_simd_s32x16_add_enable() && _simd_s32x32_combine_enable() && _simd_s32x32_splitlo_enable()  && _simd_s32x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x32_add_) && ! defined(_simd_s32x32_add_scalar_)
//	#define _simd_s32x32_add_scalar_(X,Y) _simd_s32x32_add_(X,_simd_s32x32_fill_scalar_(Y))
//	#define _simd_s32x32_add_scalar_instruction_set _simd_s32x32_add_instruction_set
//#endif
//#ifdef _simd_s32x32_add_scalar_
//	#define _simd_s32x32_add_scalar(X,Y) _simd_s32x32_add_scalar_(X,Y)
//	#define _simd_s32x32_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_add_scalar_instruction_set>()
//#else
//	#define _simd_s32x32_add_scalar(X,Y) _simd_s32x32_add_safe(X,_simd_s32x32_fill_scalar_safe(Y))
//	#define _simd_s32x32_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_s32x1_add_safe
//	#define _simd_s32x1_add_safe(X,Y) (X + Y)
//	#define _simd_s32x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_s32x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s32x1_add_enabled() true
//#endif
//
//#define _simd_s32x64_add_safe(X,Y)_simd_s32x64_combine_safe(\
//	_simd_s32x32_add_safe(_simd_s32x64_splitlo_safe(X), _simd_ s32x64_splitlo_safe(Y)),\
//	_simd_s32x32_add_safe(_simd_s32x64_splithi_safe(X), _simd_ s32x64_splithi_safe(Y)))
//#ifdef _simd_s32x64_add_
//	#define _simd_s32x64_add(X,Y) _simd_s32x64_add_(X, Y)
//	#define _simd_s32x64_add_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_add_instruction_set>()
//#else
//	#define _simd_s32x64_add(X,Y) _simd_s32x64_combine(\
//		_simd_s32x32_add(_simd_s32x64_splitlo(X), _simd_s32x64_splitlo(Y)),\
//		_simd_s32x32_add(_simd_s32x64_splithi(X), _simd_s32x64_splithi(Y)))
//	#define _simd_s32x64_add_enable() (_simd_s32x32_add_enable() && _simd_s32x64_combine_enable() && _simd_s32x64_splitlo_enable()  && _simd_s32x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_s32x64_add_) && ! defined(_simd_s32x64_add_scalar_)
//	#define _simd_s32x64_add_scalar_(X,Y) _simd_s32x64_add_(X,_simd_s32x64_fill_scalar_(Y))
//	#define _simd_s32x64_add_scalar_instruction_set _simd_s32x64_add_instruction_set
//#endif
//#ifdef _simd_s32x64_add_scalar_
//	#define _simd_s32x64_add_scalar(X,Y) _simd_s32x64_add_scalar_(X,Y)
//	#define _simd_s32x64_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_add_scalar_instruction_set>()
//#else
//	#define _simd_s32x64_add_scalar(X,Y) _simd_s32x64_add_safe(X,_simd_s32x64_fill_scalar_safe(Y))
//	#define _simd_s32x64_add_scalar_enabled() true
//#endif
//
//// -- u32 --
//
//#ifndef _simd_u32x1_add_safe
//	#define _simd_u32x1_add_safe(X,Y) (X + Y)
//	#define _simd_u32x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_u32x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_add_enabled() true
//#endif
//
//#define _simd_u32x2_add_safe(X,Y)_simd_u32x2_combine_safe(\
//	_simd_u32x1_add_safe(_simd_u32x2_splitlo_safe(X), _simd_ u32x2_splitlo_safe(Y)),\
//	_simd_u32x1_add_safe(_simd_u32x2_splithi_safe(X), _simd_ u32x2_splithi_safe(Y)))
//#ifdef _simd_u32x2_add_
//	#define _simd_u32x2_add(X,Y) _simd_u32x2_add_(X, Y)
//	#define _simd_u32x2_add_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_add_instruction_set>()
//#elif defined(_simd_u32x4_add_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_add(const register _simd_u32x2 x, const register _simd_u32x2 y) {
//		union SIMDUnion { _simd_u32x2 v1; _simd_u32x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x4_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x2_add_enable() _simd_u32x4_add_enable()
//#elif defined(_simd_u32x8_add_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_add(const register _simd_u32x2 x, const register _simd_u32x2 y) {
//		union SIMDUnion { _simd_u32x2 v1; _simd_u32x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x8_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x2_add_enable() _simd_u32x8_add_enable()
//#elif defined(_simd_u32x16_add_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_add(const register _simd_u32x2 x, const register _simd_u32x2 y) {
//		union SIMDUnion { _simd_u32x2 v1; _simd_u32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x16_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x2_add_enable() _simd_u32x16_add_enable()
//#elif defined(_simd_u32x32_add_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_add(const register _simd_u32x2 x, const register _simd_u32x2 y) {
//		union SIMDUnion { _simd_u32x2 v1; _simd_u32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x2_add_enable() _simd_u32x32_add_enable()
//#elif defined(_simd_u32x64_add_)
//	static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_add(const register _simd_u32x2 x, const register _simd_u32x2 y) {
//		union SIMDUnion { _simd_u32x2 v1; _simd_u32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x2_add_enable() _simd_u32x64_add_enable()
//#else
//	#define _simd_u32x2_add(X,Y) _simd_u32x2_combine(\
//		_simd_u32x1_add(_simd_u32x2_splitlo(X), _simd_u32x2_splitlo(Y)),\
//		_simd_u32x1_add(_simd_u32x2_splithi(X), _simd_u32x2_splithi(Y)))
//	#define _simd_u32x2_add_enable() (_simd_u32x1_add_enable() && _simd_u32x2_combine_enable() && _simd_u32x2_splitlo_enable()  && _simd_u32x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x2_add_) && ! defined(_simd_u32x2_add_scalar_)
//	#define _simd_u32x2_add_scalar_(X,Y) _simd_u32x2_add_(X,_simd_u32x2_fill_scalar_(Y))
//	#define _simd_u32x2_add_scalar_instruction_set _simd_u32x2_add_instruction_set
//#endif
//#ifdef _simd_u32x2_add_scalar_
//	#define _simd_u32x2_add_scalar(X,Y) _simd_u32x2_add_scalar_(X,Y)
//	#define _simd_u32x2_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_add_scalar_instruction_set>()
//#else
//	#define _simd_u32x2_add_scalar(X,Y) _simd_u32x2_add_safe(X,_simd_u32x2_fill_scalar_safe(Y))
//	#define _simd_u32x2_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_u32x1_add_safe
//	#define _simd_u32x1_add_safe(X,Y) (X + Y)
//	#define _simd_u32x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_u32x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_add_enabled() true
//#endif
//
//#define _simd_u32x4_add_safe(X,Y)_simd_u32x4_combine_safe(\
//	_simd_u32x2_add_safe(_simd_u32x4_splitlo_safe(X), _simd_ u32x4_splitlo_safe(Y)),\
//	_simd_u32x2_add_safe(_simd_u32x4_splithi_safe(X), _simd_ u32x4_splithi_safe(Y)))
//#ifdef _simd_u32x4_add_
//	#define _simd_u32x4_add(X,Y) _simd_u32x4_add_(X, Y)
//	#define _simd_u32x4_add_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_add_instruction_set>()
//#elif defined(_simd_u32x8_add_)
//	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_add(const register _simd_u32x4 x, const register _simd_u32x4 y) {
//		union SIMDUnion { _simd_u32x4 v1; _simd_u32x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x8_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x4_add_enable() _simd_u32x8_add_enable()
//#elif defined(_simd_u32x16_add_)
//	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_add(const register _simd_u32x4 x, const register _simd_u32x4 y) {
//		union SIMDUnion { _simd_u32x4 v1; _simd_u32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x16_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x4_add_enable() _simd_u32x16_add_enable()
//#elif defined(_simd_u32x32_add_)
//	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_add(const register _simd_u32x4 x, const register _simd_u32x4 y) {
//		union SIMDUnion { _simd_u32x4 v1; _simd_u32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x4_add_enable() _simd_u32x32_add_enable()
//#elif defined(_simd_u32x64_add_)
//	static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_add(const register _simd_u32x4 x, const register _simd_u32x4 y) {
//		union SIMDUnion { _simd_u32x4 v1; _simd_u32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x4_add_enable() _simd_u32x64_add_enable()
//#else
//	#define _simd_u32x4_add(X,Y) _simd_u32x4_combine(\
//		_simd_u32x2_add(_simd_u32x4_splitlo(X), _simd_u32x4_splitlo(Y)),\
//		_simd_u32x2_add(_simd_u32x4_splithi(X), _simd_u32x4_splithi(Y)))
//	#define _simd_u32x4_add_enable() (_simd_u32x2_add_enable() && _simd_u32x4_combine_enable() && _simd_u32x4_splitlo_enable()  && _simd_u32x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x4_add_) && ! defined(_simd_u32x4_add_scalar_)
//	#define _simd_u32x4_add_scalar_(X,Y) _simd_u32x4_add_(X,_simd_u32x4_fill_scalar_(Y))
//	#define _simd_u32x4_add_scalar_instruction_set _simd_u32x4_add_instruction_set
//#endif
//#ifdef _simd_u32x4_add_scalar_
//	#define _simd_u32x4_add_scalar(X,Y) _simd_u32x4_add_scalar_(X,Y)
//	#define _simd_u32x4_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_add_scalar_instruction_set>()
//#else
//	#define _simd_u32x4_add_scalar(X,Y) _simd_u32x4_add_safe(X,_simd_u32x4_fill_scalar_safe(Y))
//	#define _simd_u32x4_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_u32x1_add_safe
//	#define _simd_u32x1_add_safe(X,Y) (X + Y)
//	#define _simd_u32x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_u32x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_add_enabled() true
//#endif
//
//#define _simd_u32x8_add_safe(X,Y)_simd_u32x8_combine_safe(\
//	_simd_u32x4_add_safe(_simd_u32x8_splitlo_safe(X), _simd_ u32x8_splitlo_safe(Y)),\
//	_simd_u32x4_add_safe(_simd_u32x8_splithi_safe(X), _simd_ u32x8_splithi_safe(Y)))
//#ifdef _simd_u32x8_add_
//	#define _simd_u32x8_add(X,Y) _simd_u32x8_add_(X, Y)
//	#define _simd_u32x8_add_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_add_instruction_set>()
//#elif defined(_simd_u32x16_add_)
//	static ANVIL_STRONG_INLINE _simd_u32x8 ANVIL_SIMD_CALL _simd_u32x8_add(const register _simd_u32x8 x, const register _simd_u32x8 y) {
//		union SIMDUnion { _simd_u32x8 v1; _simd_u32x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x16_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x8_add_enable() _simd_u32x16_add_enable()
//#elif defined(_simd_u32x32_add_)
//	static ANVIL_STRONG_INLINE _simd_u32x8 ANVIL_SIMD_CALL _simd_u32x8_add(const register _simd_u32x8 x, const register _simd_u32x8 y) {
//		union SIMDUnion { _simd_u32x8 v1; _simd_u32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x8_add_enable() _simd_u32x32_add_enable()
//#elif defined(_simd_u32x64_add_)
//	static ANVIL_STRONG_INLINE _simd_u32x8 ANVIL_SIMD_CALL _simd_u32x8_add(const register _simd_u32x8 x, const register _simd_u32x8 y) {
//		union SIMDUnion { _simd_u32x8 v1; _simd_u32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x8_add_enable() _simd_u32x64_add_enable()
//#else
//	#define _simd_u32x8_add(X,Y) _simd_u32x8_combine(\
//		_simd_u32x4_add(_simd_u32x8_splitlo(X), _simd_u32x8_splitlo(Y)),\
//		_simd_u32x4_add(_simd_u32x8_splithi(X), _simd_u32x8_splithi(Y)))
//	#define _simd_u32x8_add_enable() (_simd_u32x4_add_enable() && _simd_u32x8_combine_enable() && _simd_u32x8_splitlo_enable()  && _simd_u32x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x8_add_) && ! defined(_simd_u32x8_add_scalar_)
//	#define _simd_u32x8_add_scalar_(X,Y) _simd_u32x8_add_(X,_simd_u32x8_fill_scalar_(Y))
//	#define _simd_u32x8_add_scalar_instruction_set _simd_u32x8_add_instruction_set
//#endif
//#ifdef _simd_u32x8_add_scalar_
//	#define _simd_u32x8_add_scalar(X,Y) _simd_u32x8_add_scalar_(X,Y)
//	#define _simd_u32x8_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_add_scalar_instruction_set>()
//#else
//	#define _simd_u32x8_add_scalar(X,Y) _simd_u32x8_add_safe(X,_simd_u32x8_fill_scalar_safe(Y))
//	#define _simd_u32x8_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_u32x1_add_safe
//	#define _simd_u32x1_add_safe(X,Y) (X + Y)
//	#define _simd_u32x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_u32x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_add_enabled() true
//#endif
//
//#define _simd_u32x16_add_safe(X,Y)_simd_u32x16_combine_safe(\
//	_simd_u32x8_add_safe(_simd_u32x16_splitlo_safe(X), _simd_ u32x16_splitlo_safe(Y)),\
//	_simd_u32x8_add_safe(_simd_u32x16_splithi_safe(X), _simd_ u32x16_splithi_safe(Y)))
//#ifdef _simd_u32x16_add_
//	#define _simd_u32x16_add(X,Y) _simd_u32x16_add_(X, Y)
//	#define _simd_u32x16_add_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_add_instruction_set>()
//#elif defined(_simd_u32x32_add_)
//	static ANVIL_STRONG_INLINE _simd_u32x16 ANVIL_SIMD_CALL _simd_u32x16_add(const register _simd_u32x16 x, const register _simd_u32x16 y) {
//		union SIMDUnion { _simd_u32x16 v1; _simd_u32x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x16_add_enable() _simd_u32x32_add_enable()
//#elif defined(_simd_u32x64_add_)
//	static ANVIL_STRONG_INLINE _simd_u32x16 ANVIL_SIMD_CALL _simd_u32x16_add(const register _simd_u32x16 x, const register _simd_u32x16 y) {
//		union SIMDUnion { _simd_u32x16 v1; _simd_u32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x16_add_enable() _simd_u32x64_add_enable()
//#else
//	#define _simd_u32x16_add(X,Y) _simd_u32x16_combine(\
//		_simd_u32x8_add(_simd_u32x16_splitlo(X), _simd_u32x16_splitlo(Y)),\
//		_simd_u32x8_add(_simd_u32x16_splithi(X), _simd_u32x16_splithi(Y)))
//	#define _simd_u32x16_add_enable() (_simd_u32x8_add_enable() && _simd_u32x16_combine_enable() && _simd_u32x16_splitlo_enable()  && _simd_u32x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x16_add_) && ! defined(_simd_u32x16_add_scalar_)
//	#define _simd_u32x16_add_scalar_(X,Y) _simd_u32x16_add_(X,_simd_u32x16_fill_scalar_(Y))
//	#define _simd_u32x16_add_scalar_instruction_set _simd_u32x16_add_instruction_set
//#endif
//#ifdef _simd_u32x16_add_scalar_
//	#define _simd_u32x16_add_scalar(X,Y) _simd_u32x16_add_scalar_(X,Y)
//	#define _simd_u32x16_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_add_scalar_instruction_set>()
//#else
//	#define _simd_u32x16_add_scalar(X,Y) _simd_u32x16_add_safe(X,_simd_u32x16_fill_scalar_safe(Y))
//	#define _simd_u32x16_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_u32x1_add_safe
//	#define _simd_u32x1_add_safe(X,Y) (X + Y)
//	#define _simd_u32x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_u32x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_add_enabled() true
//#endif
//
//#define _simd_u32x32_add_safe(X,Y)_simd_u32x32_combine_safe(\
//	_simd_u32x16_add_safe(_simd_u32x32_splitlo_safe(X), _simd_ u32x32_splitlo_safe(Y)),\
//	_simd_u32x16_add_safe(_simd_u32x32_splithi_safe(X), _simd_ u32x32_splithi_safe(Y)))
//#ifdef _simd_u32x32_add_
//	#define _simd_u32x32_add(X,Y) _simd_u32x32_add_(X, Y)
//	#define _simd_u32x32_add_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_add_instruction_set>()
//#elif defined(_simd_u32x64_add_)
//	static ANVIL_STRONG_INLINE _simd_u32x32 ANVIL_SIMD_CALL _simd_u32x32_add(const register _simd_u32x32 x, const register _simd_u32x32 y) {
//		union SIMDUnion { _simd_u32x32 v1; _simd_u32x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u32x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u32x32_add_enable() _simd_u32x64_add_enable()
//#else
//	#define _simd_u32x32_add(X,Y) _simd_u32x32_combine(\
//		_simd_u32x16_add(_simd_u32x32_splitlo(X), _simd_u32x32_splitlo(Y)),\
//		_simd_u32x16_add(_simd_u32x32_splithi(X), _simd_u32x32_splithi(Y)))
//	#define _simd_u32x32_add_enable() (_simd_u32x16_add_enable() && _simd_u32x32_combine_enable() && _simd_u32x32_splitlo_enable()  && _simd_u32x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x32_add_) && ! defined(_simd_u32x32_add_scalar_)
//	#define _simd_u32x32_add_scalar_(X,Y) _simd_u32x32_add_(X,_simd_u32x32_fill_scalar_(Y))
//	#define _simd_u32x32_add_scalar_instruction_set _simd_u32x32_add_instruction_set
//#endif
//#ifdef _simd_u32x32_add_scalar_
//	#define _simd_u32x32_add_scalar(X,Y) _simd_u32x32_add_scalar_(X,Y)
//	#define _simd_u32x32_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_add_scalar_instruction_set>()
//#else
//	#define _simd_u32x32_add_scalar(X,Y) _simd_u32x32_add_safe(X,_simd_u32x32_fill_scalar_safe(Y))
//	#define _simd_u32x32_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_u32x1_add_safe
//	#define _simd_u32x1_add_safe(X,Y) (X + Y)
//	#define _simd_u32x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_u32x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u32x1_add_enabled() true
//#endif
//
//#define _simd_u32x64_add_safe(X,Y)_simd_u32x64_combine_safe(\
//	_simd_u32x32_add_safe(_simd_u32x64_splitlo_safe(X), _simd_ u32x64_splitlo_safe(Y)),\
//	_simd_u32x32_add_safe(_simd_u32x64_splithi_safe(X), _simd_ u32x64_splithi_safe(Y)))
//#ifdef _simd_u32x64_add_
//	#define _simd_u32x64_add(X,Y) _simd_u32x64_add_(X, Y)
//	#define _simd_u32x64_add_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_add_instruction_set>()
//#else
//	#define _simd_u32x64_add(X,Y) _simd_u32x64_combine(\
//		_simd_u32x32_add(_simd_u32x64_splitlo(X), _simd_u32x64_splitlo(Y)),\
//		_simd_u32x32_add(_simd_u32x64_splithi(X), _simd_u32x64_splithi(Y)))
//	#define _simd_u32x64_add_enable() (_simd_u32x32_add_enable() && _simd_u32x64_combine_enable() && _simd_u32x64_splitlo_enable()  && _simd_u32x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_u32x64_add_) && ! defined(_simd_u32x64_add_scalar_)
//	#define _simd_u32x64_add_scalar_(X,Y) _simd_u32x64_add_(X,_simd_u32x64_fill_scalar_(Y))
//	#define _simd_u32x64_add_scalar_instruction_set _simd_u32x64_add_instruction_set
//#endif
//#ifdef _simd_u32x64_add_scalar_
//	#define _simd_u32x64_add_scalar(X,Y) _simd_u32x64_add_scalar_(X,Y)
//	#define _simd_u32x64_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_add_scalar_instruction_set>()
//#else
//	#define _simd_u32x64_add_scalar(X,Y) _simd_u32x64_add_safe(X,_simd_u32x64_fill_scalar_safe(Y))
//	#define _simd_u32x64_add_scalar_enabled() true
//#endif
//
//// -- s16 --
//
//#ifndef _simd_s16x1_add_safe
//	#define _simd_s16x1_add_safe(X,Y) (X + Y)
//	#define _simd_s16x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_s16x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_add_enabled() true
//#endif
//
//#define _simd_s16x2_add_safe(X,Y)_simd_s16x2_combine_safe(\
//	_simd_s16x1_add_safe(_simd_s16x2_splitlo_safe(X), _simd_ s16x2_splitlo_safe(Y)),\
//	_simd_s16x1_add_safe(_simd_s16x2_splithi_safe(X), _simd_ s16x2_splithi_safe(Y)))
//#ifdef _simd_s16x2_add_
//	#define _simd_s16x2_add(X,Y) _simd_s16x2_add_(X, Y)
//	#define _simd_s16x2_add_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_add_instruction_set>()
//#elif defined(_simd_s16x4_add_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_add(const register _simd_s16x2 x, const register _simd_s16x2 y) {
//		union SIMDUnion { _simd_s16x2 v1; _simd_s16x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x4_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x2_add_enable() _simd_s16x4_add_enable()
//#elif defined(_simd_s16x8_add_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_add(const register _simd_s16x2 x, const register _simd_s16x2 y) {
//		union SIMDUnion { _simd_s16x2 v1; _simd_s16x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x8_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x2_add_enable() _simd_s16x8_add_enable()
//#elif defined(_simd_s16x16_add_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_add(const register _simd_s16x2 x, const register _simd_s16x2 y) {
//		union SIMDUnion { _simd_s16x2 v1; _simd_s16x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x16_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x2_add_enable() _simd_s16x16_add_enable()
//#elif defined(_simd_s16x32_add_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_add(const register _simd_s16x2 x, const register _simd_s16x2 y) {
//		union SIMDUnion { _simd_s16x2 v1; _simd_s16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x2_add_enable() _simd_s16x32_add_enable()
//#elif defined(_simd_s16x64_add_)
//	static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_add(const register _simd_s16x2 x, const register _simd_s16x2 y) {
//		union SIMDUnion { _simd_s16x2 v1; _simd_s16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x2_add_enable() _simd_s16x64_add_enable()
//#else
//	#define _simd_s16x2_add(X,Y) _simd_s16x2_combine(\
//		_simd_s16x1_add(_simd_s16x2_splitlo(X), _simd_s16x2_splitlo(Y)),\
//		_simd_s16x1_add(_simd_s16x2_splithi(X), _simd_s16x2_splithi(Y)))
//	#define _simd_s16x2_add_enable() (_simd_s16x1_add_enable() && _simd_s16x2_combine_enable() && _simd_s16x2_splitlo_enable()  && _simd_s16x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x2_add_) && ! defined(_simd_s16x2_add_scalar_)
//	#define _simd_s16x2_add_scalar_(X,Y) _simd_s16x2_add_(X,_simd_s16x2_fill_scalar_(Y))
//	#define _simd_s16x2_add_scalar_instruction_set _simd_s16x2_add_instruction_set
//#endif
//#ifdef _simd_s16x2_add_scalar_
//	#define _simd_s16x2_add_scalar(X,Y) _simd_s16x2_add_scalar_(X,Y)
//	#define _simd_s16x2_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_add_scalar_instruction_set>()
//#else
//	#define _simd_s16x2_add_scalar(X,Y) _simd_s16x2_add_safe(X,_simd_s16x2_fill_scalar_safe(Y))
//	#define _simd_s16x2_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_s16x1_add_safe
//	#define _simd_s16x1_add_safe(X,Y) (X + Y)
//	#define _simd_s16x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_s16x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_add_enabled() true
//#endif
//
//#define _simd_s16x4_add_safe(X,Y)_simd_s16x4_combine_safe(\
//	_simd_s16x2_add_safe(_simd_s16x4_splitlo_safe(X), _simd_ s16x4_splitlo_safe(Y)),\
//	_simd_s16x2_add_safe(_simd_s16x4_splithi_safe(X), _simd_ s16x4_splithi_safe(Y)))
//#ifdef _simd_s16x4_add_
//	#define _simd_s16x4_add(X,Y) _simd_s16x4_add_(X, Y)
//	#define _simd_s16x4_add_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_add_instruction_set>()
//#elif defined(_simd_s16x8_add_)
//	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_add(const register _simd_s16x4 x, const register _simd_s16x4 y) {
//		union SIMDUnion { _simd_s16x4 v1; _simd_s16x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x8_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x4_add_enable() _simd_s16x8_add_enable()
//#elif defined(_simd_s16x16_add_)
//	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_add(const register _simd_s16x4 x, const register _simd_s16x4 y) {
//		union SIMDUnion { _simd_s16x4 v1; _simd_s16x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x16_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x4_add_enable() _simd_s16x16_add_enable()
//#elif defined(_simd_s16x32_add_)
//	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_add(const register _simd_s16x4 x, const register _simd_s16x4 y) {
//		union SIMDUnion { _simd_s16x4 v1; _simd_s16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x4_add_enable() _simd_s16x32_add_enable()
//#elif defined(_simd_s16x64_add_)
//	static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_add(const register _simd_s16x4 x, const register _simd_s16x4 y) {
//		union SIMDUnion { _simd_s16x4 v1; _simd_s16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x4_add_enable() _simd_s16x64_add_enable()
//#else
//	#define _simd_s16x4_add(X,Y) _simd_s16x4_combine(\
//		_simd_s16x2_add(_simd_s16x4_splitlo(X), _simd_s16x4_splitlo(Y)),\
//		_simd_s16x2_add(_simd_s16x4_splithi(X), _simd_s16x4_splithi(Y)))
//	#define _simd_s16x4_add_enable() (_simd_s16x2_add_enable() && _simd_s16x4_combine_enable() && _simd_s16x4_splitlo_enable()  && _simd_s16x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x4_add_) && ! defined(_simd_s16x4_add_scalar_)
//	#define _simd_s16x4_add_scalar_(X,Y) _simd_s16x4_add_(X,_simd_s16x4_fill_scalar_(Y))
//	#define _simd_s16x4_add_scalar_instruction_set _simd_s16x4_add_instruction_set
//#endif
//#ifdef _simd_s16x4_add_scalar_
//	#define _simd_s16x4_add_scalar(X,Y) _simd_s16x4_add_scalar_(X,Y)
//	#define _simd_s16x4_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_add_scalar_instruction_set>()
//#else
//	#define _simd_s16x4_add_scalar(X,Y) _simd_s16x4_add_safe(X,_simd_s16x4_fill_scalar_safe(Y))
//	#define _simd_s16x4_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_s16x1_add_safe
//	#define _simd_s16x1_add_safe(X,Y) (X + Y)
//	#define _simd_s16x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_s16x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_add_enabled() true
//#endif
//
//#define _simd_s16x8_add_safe(X,Y)_simd_s16x8_combine_safe(\
//	_simd_s16x4_add_safe(_simd_s16x8_splitlo_safe(X), _simd_ s16x8_splitlo_safe(Y)),\
//	_simd_s16x4_add_safe(_simd_s16x8_splithi_safe(X), _simd_ s16x8_splithi_safe(Y)))
//#ifdef _simd_s16x8_add_
//	#define _simd_s16x8_add(X,Y) _simd_s16x8_add_(X, Y)
//	#define _simd_s16x8_add_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_add_instruction_set>()
//#elif defined(_simd_s16x16_add_)
//	static ANVIL_STRONG_INLINE _simd_s16x8 ANVIL_SIMD_CALL _simd_s16x8_add(const register _simd_s16x8 x, const register _simd_s16x8 y) {
//		union SIMDUnion { _simd_s16x8 v1; _simd_s16x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x16_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x8_add_enable() _simd_s16x16_add_enable()
//#elif defined(_simd_s16x32_add_)
//	static ANVIL_STRONG_INLINE _simd_s16x8 ANVIL_SIMD_CALL _simd_s16x8_add(const register _simd_s16x8 x, const register _simd_s16x8 y) {
//		union SIMDUnion { _simd_s16x8 v1; _simd_s16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x8_add_enable() _simd_s16x32_add_enable()
//#elif defined(_simd_s16x64_add_)
//	static ANVIL_STRONG_INLINE _simd_s16x8 ANVIL_SIMD_CALL _simd_s16x8_add(const register _simd_s16x8 x, const register _simd_s16x8 y) {
//		union SIMDUnion { _simd_s16x8 v1; _simd_s16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x8_add_enable() _simd_s16x64_add_enable()
//#else
//	#define _simd_s16x8_add(X,Y) _simd_s16x8_combine(\
//		_simd_s16x4_add(_simd_s16x8_splitlo(X), _simd_s16x8_splitlo(Y)),\
//		_simd_s16x4_add(_simd_s16x8_splithi(X), _simd_s16x8_splithi(Y)))
//	#define _simd_s16x8_add_enable() (_simd_s16x4_add_enable() && _simd_s16x8_combine_enable() && _simd_s16x8_splitlo_enable()  && _simd_s16x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x8_add_) && ! defined(_simd_s16x8_add_scalar_)
//	#define _simd_s16x8_add_scalar_(X,Y) _simd_s16x8_add_(X,_simd_s16x8_fill_scalar_(Y))
//	#define _simd_s16x8_add_scalar_instruction_set _simd_s16x8_add_instruction_set
//#endif
//#ifdef _simd_s16x8_add_scalar_
//	#define _simd_s16x8_add_scalar(X,Y) _simd_s16x8_add_scalar_(X,Y)
//	#define _simd_s16x8_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_add_scalar_instruction_set>()
//#else
//	#define _simd_s16x8_add_scalar(X,Y) _simd_s16x8_add_safe(X,_simd_s16x8_fill_scalar_safe(Y))
//	#define _simd_s16x8_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_s16x1_add_safe
//	#define _simd_s16x1_add_safe(X,Y) (X + Y)
//	#define _simd_s16x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_s16x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_add_enabled() true
//#endif
//
//#define _simd_s16x16_add_safe(X,Y)_simd_s16x16_combine_safe(\
//	_simd_s16x8_add_safe(_simd_s16x16_splitlo_safe(X), _simd_ s16x16_splitlo_safe(Y)),\
//	_simd_s16x8_add_safe(_simd_s16x16_splithi_safe(X), _simd_ s16x16_splithi_safe(Y)))
//#ifdef _simd_s16x16_add_
//	#define _simd_s16x16_add(X,Y) _simd_s16x16_add_(X, Y)
//	#define _simd_s16x16_add_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_add_instruction_set>()
//#elif defined(_simd_s16x32_add_)
//	static ANVIL_STRONG_INLINE _simd_s16x16 ANVIL_SIMD_CALL _simd_s16x16_add(const register _simd_s16x16 x, const register _simd_s16x16 y) {
//		union SIMDUnion { _simd_s16x16 v1; _simd_s16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x16_add_enable() _simd_s16x32_add_enable()
//#elif defined(_simd_s16x64_add_)
//	static ANVIL_STRONG_INLINE _simd_s16x16 ANVIL_SIMD_CALL _simd_s16x16_add(const register _simd_s16x16 x, const register _simd_s16x16 y) {
//		union SIMDUnion { _simd_s16x16 v1; _simd_s16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x16_add_enable() _simd_s16x64_add_enable()
//#else
//	#define _simd_s16x16_add(X,Y) _simd_s16x16_combine(\
//		_simd_s16x8_add(_simd_s16x16_splitlo(X), _simd_s16x16_splitlo(Y)),\
//		_simd_s16x8_add(_simd_s16x16_splithi(X), _simd_s16x16_splithi(Y)))
//	#define _simd_s16x16_add_enable() (_simd_s16x8_add_enable() && _simd_s16x16_combine_enable() && _simd_s16x16_splitlo_enable()  && _simd_s16x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x16_add_) && ! defined(_simd_s16x16_add_scalar_)
//	#define _simd_s16x16_add_scalar_(X,Y) _simd_s16x16_add_(X,_simd_s16x16_fill_scalar_(Y))
//	#define _simd_s16x16_add_scalar_instruction_set _simd_s16x16_add_instruction_set
//#endif
//#ifdef _simd_s16x16_add_scalar_
//	#define _simd_s16x16_add_scalar(X,Y) _simd_s16x16_add_scalar_(X,Y)
//	#define _simd_s16x16_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_add_scalar_instruction_set>()
//#else
//	#define _simd_s16x16_add_scalar(X,Y) _simd_s16x16_add_safe(X,_simd_s16x16_fill_scalar_safe(Y))
//	#define _simd_s16x16_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_s16x1_add_safe
//	#define _simd_s16x1_add_safe(X,Y) (X + Y)
//	#define _simd_s16x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_s16x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_add_enabled() true
//#endif
//
//#define _simd_s16x32_add_safe(X,Y)_simd_s16x32_combine_safe(\
//	_simd_s16x16_add_safe(_simd_s16x32_splitlo_safe(X), _simd_ s16x32_splitlo_safe(Y)),\
//	_simd_s16x16_add_safe(_simd_s16x32_splithi_safe(X), _simd_ s16x32_splithi_safe(Y)))
//#ifdef _simd_s16x32_add_
//	#define _simd_s16x32_add(X,Y) _simd_s16x32_add_(X, Y)
//	#define _simd_s16x32_add_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_add_instruction_set>()
//#elif defined(_simd_s16x64_add_)
//	static ANVIL_STRONG_INLINE _simd_s16x32 ANVIL_SIMD_CALL _simd_s16x32_add(const register _simd_s16x32 x, const register _simd_s16x32 y) {
//		union SIMDUnion { _simd_s16x32 v1; _simd_s16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s16x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s16x32_add_enable() _simd_s16x64_add_enable()
//#else
//	#define _simd_s16x32_add(X,Y) _simd_s16x32_combine(\
//		_simd_s16x16_add(_simd_s16x32_splitlo(X), _simd_s16x32_splitlo(Y)),\
//		_simd_s16x16_add(_simd_s16x32_splithi(X), _simd_s16x32_splithi(Y)))
//	#define _simd_s16x32_add_enable() (_simd_s16x16_add_enable() && _simd_s16x32_combine_enable() && _simd_s16x32_splitlo_enable()  && _simd_s16x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x32_add_) && ! defined(_simd_s16x32_add_scalar_)
//	#define _simd_s16x32_add_scalar_(X,Y) _simd_s16x32_add_(X,_simd_s16x32_fill_scalar_(Y))
//	#define _simd_s16x32_add_scalar_instruction_set _simd_s16x32_add_instruction_set
//#endif
//#ifdef _simd_s16x32_add_scalar_
//	#define _simd_s16x32_add_scalar(X,Y) _simd_s16x32_add_scalar_(X,Y)
//	#define _simd_s16x32_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_add_scalar_instruction_set>()
//#else
//	#define _simd_s16x32_add_scalar(X,Y) _simd_s16x32_add_safe(X,_simd_s16x32_fill_scalar_safe(Y))
//	#define _simd_s16x32_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_s16x1_add_safe
//	#define _simd_s16x1_add_safe(X,Y) (X + Y)
//	#define _simd_s16x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_s16x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s16x1_add_enabled() true
//#endif
//
//#define _simd_s16x64_add_safe(X,Y)_simd_s16x64_combine_safe(\
//	_simd_s16x32_add_safe(_simd_s16x64_splitlo_safe(X), _simd_ s16x64_splitlo_safe(Y)),\
//	_simd_s16x32_add_safe(_simd_s16x64_splithi_safe(X), _simd_ s16x64_splithi_safe(Y)))
//#ifdef _simd_s16x64_add_
//	#define _simd_s16x64_add(X,Y) _simd_s16x64_add_(X, Y)
//	#define _simd_s16x64_add_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_add_instruction_set>()
//#else
//	#define _simd_s16x64_add(X,Y) _simd_s16x64_combine(\
//		_simd_s16x32_add(_simd_s16x64_splitlo(X), _simd_s16x64_splitlo(Y)),\
//		_simd_s16x32_add(_simd_s16x64_splithi(X), _simd_s16x64_splithi(Y)))
//	#define _simd_s16x64_add_enable() (_simd_s16x32_add_enable() && _simd_s16x64_combine_enable() && _simd_s16x64_splitlo_enable()  && _simd_s16x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_s16x64_add_) && ! defined(_simd_s16x64_add_scalar_)
//	#define _simd_s16x64_add_scalar_(X,Y) _simd_s16x64_add_(X,_simd_s16x64_fill_scalar_(Y))
//	#define _simd_s16x64_add_scalar_instruction_set _simd_s16x64_add_instruction_set
//#endif
//#ifdef _simd_s16x64_add_scalar_
//	#define _simd_s16x64_add_scalar(X,Y) _simd_s16x64_add_scalar_(X,Y)
//	#define _simd_s16x64_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_add_scalar_instruction_set>()
//#else
//	#define _simd_s16x64_add_scalar(X,Y) _simd_s16x64_add_safe(X,_simd_s16x64_fill_scalar_safe(Y))
//	#define _simd_s16x64_add_scalar_enabled() true
//#endif
//
//// -- u16 --
//
//#ifndef _simd_u16x1_add_safe
//	#define _simd_u16x1_add_safe(X,Y) (X + Y)
//	#define _simd_u16x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_u16x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_add_enabled() true
//#endif
//
//#define _simd_u16x2_add_safe(X,Y)_simd_u16x2_combine_safe(\
//	_simd_u16x1_add_safe(_simd_u16x2_splitlo_safe(X), _simd_ u16x2_splitlo_safe(Y)),\
//	_simd_u16x1_add_safe(_simd_u16x2_splithi_safe(X), _simd_ u16x2_splithi_safe(Y)))
//#ifdef _simd_u16x2_add_
//	#define _simd_u16x2_add(X,Y) _simd_u16x2_add_(X, Y)
//	#define _simd_u16x2_add_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_add_instruction_set>()
//#elif defined(_simd_u16x4_add_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_add(const register _simd_u16x2 x, const register _simd_u16x2 y) {
//		union SIMDUnion { _simd_u16x2 v1; _simd_u16x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x4_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x2_add_enable() _simd_u16x4_add_enable()
//#elif defined(_simd_u16x8_add_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_add(const register _simd_u16x2 x, const register _simd_u16x2 y) {
//		union SIMDUnion { _simd_u16x2 v1; _simd_u16x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x8_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x2_add_enable() _simd_u16x8_add_enable()
//#elif defined(_simd_u16x16_add_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_add(const register _simd_u16x2 x, const register _simd_u16x2 y) {
//		union SIMDUnion { _simd_u16x2 v1; _simd_u16x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x16_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x2_add_enable() _simd_u16x16_add_enable()
//#elif defined(_simd_u16x32_add_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_add(const register _simd_u16x2 x, const register _simd_u16x2 y) {
//		union SIMDUnion { _simd_u16x2 v1; _simd_u16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x2_add_enable() _simd_u16x32_add_enable()
//#elif defined(_simd_u16x64_add_)
//	static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_add(const register _simd_u16x2 x, const register _simd_u16x2 y) {
//		union SIMDUnion { _simd_u16x2 v1; _simd_u16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x2_add_enable() _simd_u16x64_add_enable()
//#else
//	#define _simd_u16x2_add(X,Y) _simd_u16x2_combine(\
//		_simd_u16x1_add(_simd_u16x2_splitlo(X), _simd_u16x2_splitlo(Y)),\
//		_simd_u16x1_add(_simd_u16x2_splithi(X), _simd_u16x2_splithi(Y)))
//	#define _simd_u16x2_add_enable() (_simd_u16x1_add_enable() && _simd_u16x2_combine_enable() && _simd_u16x2_splitlo_enable()  && _simd_u16x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x2_add_) && ! defined(_simd_u16x2_add_scalar_)
//	#define _simd_u16x2_add_scalar_(X,Y) _simd_u16x2_add_(X,_simd_u16x2_fill_scalar_(Y))
//	#define _simd_u16x2_add_scalar_instruction_set _simd_u16x2_add_instruction_set
//#endif
//#ifdef _simd_u16x2_add_scalar_
//	#define _simd_u16x2_add_scalar(X,Y) _simd_u16x2_add_scalar_(X,Y)
//	#define _simd_u16x2_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_add_scalar_instruction_set>()
//#else
//	#define _simd_u16x2_add_scalar(X,Y) _simd_u16x2_add_safe(X,_simd_u16x2_fill_scalar_safe(Y))
//	#define _simd_u16x2_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_u16x1_add_safe
//	#define _simd_u16x1_add_safe(X,Y) (X + Y)
//	#define _simd_u16x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_u16x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_add_enabled() true
//#endif
//
//#define _simd_u16x4_add_safe(X,Y)_simd_u16x4_combine_safe(\
//	_simd_u16x2_add_safe(_simd_u16x4_splitlo_safe(X), _simd_ u16x4_splitlo_safe(Y)),\
//	_simd_u16x2_add_safe(_simd_u16x4_splithi_safe(X), _simd_ u16x4_splithi_safe(Y)))
//#ifdef _simd_u16x4_add_
//	#define _simd_u16x4_add(X,Y) _simd_u16x4_add_(X, Y)
//	#define _simd_u16x4_add_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_add_instruction_set>()
//#elif defined(_simd_u16x8_add_)
//	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_add(const register _simd_u16x4 x, const register _simd_u16x4 y) {
//		union SIMDUnion { _simd_u16x4 v1; _simd_u16x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x8_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x4_add_enable() _simd_u16x8_add_enable()
//#elif defined(_simd_u16x16_add_)
//	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_add(const register _simd_u16x4 x, const register _simd_u16x4 y) {
//		union SIMDUnion { _simd_u16x4 v1; _simd_u16x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x16_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x4_add_enable() _simd_u16x16_add_enable()
//#elif defined(_simd_u16x32_add_)
//	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_add(const register _simd_u16x4 x, const register _simd_u16x4 y) {
//		union SIMDUnion { _simd_u16x4 v1; _simd_u16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x4_add_enable() _simd_u16x32_add_enable()
//#elif defined(_simd_u16x64_add_)
//	static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_add(const register _simd_u16x4 x, const register _simd_u16x4 y) {
//		union SIMDUnion { _simd_u16x4 v1; _simd_u16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x4_add_enable() _simd_u16x64_add_enable()
//#else
//	#define _simd_u16x4_add(X,Y) _simd_u16x4_combine(\
//		_simd_u16x2_add(_simd_u16x4_splitlo(X), _simd_u16x4_splitlo(Y)),\
//		_simd_u16x2_add(_simd_u16x4_splithi(X), _simd_u16x4_splithi(Y)))
//	#define _simd_u16x4_add_enable() (_simd_u16x2_add_enable() && _simd_u16x4_combine_enable() && _simd_u16x4_splitlo_enable()  && _simd_u16x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x4_add_) && ! defined(_simd_u16x4_add_scalar_)
//	#define _simd_u16x4_add_scalar_(X,Y) _simd_u16x4_add_(X,_simd_u16x4_fill_scalar_(Y))
//	#define _simd_u16x4_add_scalar_instruction_set _simd_u16x4_add_instruction_set
//#endif
//#ifdef _simd_u16x4_add_scalar_
//	#define _simd_u16x4_add_scalar(X,Y) _simd_u16x4_add_scalar_(X,Y)
//	#define _simd_u16x4_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_add_scalar_instruction_set>()
//#else
//	#define _simd_u16x4_add_scalar(X,Y) _simd_u16x4_add_safe(X,_simd_u16x4_fill_scalar_safe(Y))
//	#define _simd_u16x4_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_u16x1_add_safe
//	#define _simd_u16x1_add_safe(X,Y) (X + Y)
//	#define _simd_u16x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_u16x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_add_enabled() true
//#endif
//
//#define _simd_u16x8_add_safe(X,Y)_simd_u16x8_combine_safe(\
//	_simd_u16x4_add_safe(_simd_u16x8_splitlo_safe(X), _simd_ u16x8_splitlo_safe(Y)),\
//	_simd_u16x4_add_safe(_simd_u16x8_splithi_safe(X), _simd_ u16x8_splithi_safe(Y)))
//#ifdef _simd_u16x8_add_
//	#define _simd_u16x8_add(X,Y) _simd_u16x8_add_(X, Y)
//	#define _simd_u16x8_add_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_add_instruction_set>()
//#elif defined(_simd_u16x16_add_)
//	static ANVIL_STRONG_INLINE _simd_u16x8 ANVIL_SIMD_CALL _simd_u16x8_add(const register _simd_u16x8 x, const register _simd_u16x8 y) {
//		union SIMDUnion { _simd_u16x8 v1; _simd_u16x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x16_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x8_add_enable() _simd_u16x16_add_enable()
//#elif defined(_simd_u16x32_add_)
//	static ANVIL_STRONG_INLINE _simd_u16x8 ANVIL_SIMD_CALL _simd_u16x8_add(const register _simd_u16x8 x, const register _simd_u16x8 y) {
//		union SIMDUnion { _simd_u16x8 v1; _simd_u16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x8_add_enable() _simd_u16x32_add_enable()
//#elif defined(_simd_u16x64_add_)
//	static ANVIL_STRONG_INLINE _simd_u16x8 ANVIL_SIMD_CALL _simd_u16x8_add(const register _simd_u16x8 x, const register _simd_u16x8 y) {
//		union SIMDUnion { _simd_u16x8 v1; _simd_u16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x8_add_enable() _simd_u16x64_add_enable()
//#else
//	#define _simd_u16x8_add(X,Y) _simd_u16x8_combine(\
//		_simd_u16x4_add(_simd_u16x8_splitlo(X), _simd_u16x8_splitlo(Y)),\
//		_simd_u16x4_add(_simd_u16x8_splithi(X), _simd_u16x8_splithi(Y)))
//	#define _simd_u16x8_add_enable() (_simd_u16x4_add_enable() && _simd_u16x8_combine_enable() && _simd_u16x8_splitlo_enable()  && _simd_u16x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x8_add_) && ! defined(_simd_u16x8_add_scalar_)
//	#define _simd_u16x8_add_scalar_(X,Y) _simd_u16x8_add_(X,_simd_u16x8_fill_scalar_(Y))
//	#define _simd_u16x8_add_scalar_instruction_set _simd_u16x8_add_instruction_set
//#endif
//#ifdef _simd_u16x8_add_scalar_
//	#define _simd_u16x8_add_scalar(X,Y) _simd_u16x8_add_scalar_(X,Y)
//	#define _simd_u16x8_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_add_scalar_instruction_set>()
//#else
//	#define _simd_u16x8_add_scalar(X,Y) _simd_u16x8_add_safe(X,_simd_u16x8_fill_scalar_safe(Y))
//	#define _simd_u16x8_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_u16x1_add_safe
//	#define _simd_u16x1_add_safe(X,Y) (X + Y)
//	#define _simd_u16x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_u16x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_add_enabled() true
//#endif
//
//#define _simd_u16x16_add_safe(X,Y)_simd_u16x16_combine_safe(\
//	_simd_u16x8_add_safe(_simd_u16x16_splitlo_safe(X), _simd_ u16x16_splitlo_safe(Y)),\
//	_simd_u16x8_add_safe(_simd_u16x16_splithi_safe(X), _simd_ u16x16_splithi_safe(Y)))
//#ifdef _simd_u16x16_add_
//	#define _simd_u16x16_add(X,Y) _simd_u16x16_add_(X, Y)
//	#define _simd_u16x16_add_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_add_instruction_set>()
//#elif defined(_simd_u16x32_add_)
//	static ANVIL_STRONG_INLINE _simd_u16x16 ANVIL_SIMD_CALL _simd_u16x16_add(const register _simd_u16x16 x, const register _simd_u16x16 y) {
//		union SIMDUnion { _simd_u16x16 v1; _simd_u16x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x16_add_enable() _simd_u16x32_add_enable()
//#elif defined(_simd_u16x64_add_)
//	static ANVIL_STRONG_INLINE _simd_u16x16 ANVIL_SIMD_CALL _simd_u16x16_add(const register _simd_u16x16 x, const register _simd_u16x16 y) {
//		union SIMDUnion { _simd_u16x16 v1; _simd_u16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x16_add_enable() _simd_u16x64_add_enable()
//#else
//	#define _simd_u16x16_add(X,Y) _simd_u16x16_combine(\
//		_simd_u16x8_add(_simd_u16x16_splitlo(X), _simd_u16x16_splitlo(Y)),\
//		_simd_u16x8_add(_simd_u16x16_splithi(X), _simd_u16x16_splithi(Y)))
//	#define _simd_u16x16_add_enable() (_simd_u16x8_add_enable() && _simd_u16x16_combine_enable() && _simd_u16x16_splitlo_enable()  && _simd_u16x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x16_add_) && ! defined(_simd_u16x16_add_scalar_)
//	#define _simd_u16x16_add_scalar_(X,Y) _simd_u16x16_add_(X,_simd_u16x16_fill_scalar_(Y))
//	#define _simd_u16x16_add_scalar_instruction_set _simd_u16x16_add_instruction_set
//#endif
//#ifdef _simd_u16x16_add_scalar_
//	#define _simd_u16x16_add_scalar(X,Y) _simd_u16x16_add_scalar_(X,Y)
//	#define _simd_u16x16_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_add_scalar_instruction_set>()
//#else
//	#define _simd_u16x16_add_scalar(X,Y) _simd_u16x16_add_safe(X,_simd_u16x16_fill_scalar_safe(Y))
//	#define _simd_u16x16_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_u16x1_add_safe
//	#define _simd_u16x1_add_safe(X,Y) (X + Y)
//	#define _simd_u16x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_u16x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_add_enabled() true
//#endif
//
//#define _simd_u16x32_add_safe(X,Y)_simd_u16x32_combine_safe(\
//	_simd_u16x16_add_safe(_simd_u16x32_splitlo_safe(X), _simd_ u16x32_splitlo_safe(Y)),\
//	_simd_u16x16_add_safe(_simd_u16x32_splithi_safe(X), _simd_ u16x32_splithi_safe(Y)))
//#ifdef _simd_u16x32_add_
//	#define _simd_u16x32_add(X,Y) _simd_u16x32_add_(X, Y)
//	#define _simd_u16x32_add_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_add_instruction_set>()
//#elif defined(_simd_u16x64_add_)
//	static ANVIL_STRONG_INLINE _simd_u16x32 ANVIL_SIMD_CALL _simd_u16x32_add(const register _simd_u16x32 x, const register _simd_u16x32 y) {
//		union SIMDUnion { _simd_u16x32 v1; _simd_u16x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u16x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u16x32_add_enable() _simd_u16x64_add_enable()
//#else
//	#define _simd_u16x32_add(X,Y) _simd_u16x32_combine(\
//		_simd_u16x16_add(_simd_u16x32_splitlo(X), _simd_u16x32_splitlo(Y)),\
//		_simd_u16x16_add(_simd_u16x32_splithi(X), _simd_u16x32_splithi(Y)))
//	#define _simd_u16x32_add_enable() (_simd_u16x16_add_enable() && _simd_u16x32_combine_enable() && _simd_u16x32_splitlo_enable()  && _simd_u16x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x32_add_) && ! defined(_simd_u16x32_add_scalar_)
//	#define _simd_u16x32_add_scalar_(X,Y) _simd_u16x32_add_(X,_simd_u16x32_fill_scalar_(Y))
//	#define _simd_u16x32_add_scalar_instruction_set _simd_u16x32_add_instruction_set
//#endif
//#ifdef _simd_u16x32_add_scalar_
//	#define _simd_u16x32_add_scalar(X,Y) _simd_u16x32_add_scalar_(X,Y)
//	#define _simd_u16x32_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_add_scalar_instruction_set>()
//#else
//	#define _simd_u16x32_add_scalar(X,Y) _simd_u16x32_add_safe(X,_simd_u16x32_fill_scalar_safe(Y))
//	#define _simd_u16x32_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_u16x1_add_safe
//	#define _simd_u16x1_add_safe(X,Y) (X + Y)
//	#define _simd_u16x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_u16x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u16x1_add_enabled() true
//#endif
//
//#define _simd_u16x64_add_safe(X,Y)_simd_u16x64_combine_safe(\
//	_simd_u16x32_add_safe(_simd_u16x64_splitlo_safe(X), _simd_ u16x64_splitlo_safe(Y)),\
//	_simd_u16x32_add_safe(_simd_u16x64_splithi_safe(X), _simd_ u16x64_splithi_safe(Y)))
//#ifdef _simd_u16x64_add_
//	#define _simd_u16x64_add(X,Y) _simd_u16x64_add_(X, Y)
//	#define _simd_u16x64_add_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_add_instruction_set>()
//#else
//	#define _simd_u16x64_add(X,Y) _simd_u16x64_combine(\
//		_simd_u16x32_add(_simd_u16x64_splitlo(X), _simd_u16x64_splitlo(Y)),\
//		_simd_u16x32_add(_simd_u16x64_splithi(X), _simd_u16x64_splithi(Y)))
//	#define _simd_u16x64_add_enable() (_simd_u16x32_add_enable() && _simd_u16x64_combine_enable() && _simd_u16x64_splitlo_enable()  && _simd_u16x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_u16x64_add_) && ! defined(_simd_u16x64_add_scalar_)
//	#define _simd_u16x64_add_scalar_(X,Y) _simd_u16x64_add_(X,_simd_u16x64_fill_scalar_(Y))
//	#define _simd_u16x64_add_scalar_instruction_set _simd_u16x64_add_instruction_set
//#endif
//#ifdef _simd_u16x64_add_scalar_
//	#define _simd_u16x64_add_scalar(X,Y) _simd_u16x64_add_scalar_(X,Y)
//	#define _simd_u16x64_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_add_scalar_instruction_set>()
//#else
//	#define _simd_u16x64_add_scalar(X,Y) _simd_u16x64_add_safe(X,_simd_u16x64_fill_scalar_safe(Y))
//	#define _simd_u16x64_add_scalar_enabled() true
//#endif
//
//// -- s8 --
//
//#ifndef _simd_s8x1_add_safe
//	#define _simd_s8x1_add_safe(X,Y) (X + Y)
//	#define _simd_s8x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_s8x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_add_enabled() true
//#endif
//
//#define _simd_s8x2_add_safe(X,Y)_simd_s8x2_combine_safe(\
//	_simd_s8x1_add_safe(_simd_s8x2_splitlo_safe(X), _simd_ s8x2_splitlo_safe(Y)),\
//	_simd_s8x1_add_safe(_simd_s8x2_splithi_safe(X), _simd_ s8x2_splithi_safe(Y)))
//#ifdef _simd_s8x2_add_
//	#define _simd_s8x2_add(X,Y) _simd_s8x2_add_(X, Y)
//	#define _simd_s8x2_add_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_add_instruction_set>()
//#elif defined(_simd_s8x4_add_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_add(const register _simd_s8x2 x, const register _simd_s8x2 y) {
//		union SIMDUnion { _simd_s8x2 v1; _simd_s8x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x4_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x2_add_enable() _simd_s8x4_add_enable()
//#elif defined(_simd_s8x8_add_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_add(const register _simd_s8x2 x, const register _simd_s8x2 y) {
//		union SIMDUnion { _simd_s8x2 v1; _simd_s8x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x8_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x2_add_enable() _simd_s8x8_add_enable()
//#elif defined(_simd_s8x16_add_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_add(const register _simd_s8x2 x, const register _simd_s8x2 y) {
//		union SIMDUnion { _simd_s8x2 v1; _simd_s8x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x16_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x2_add_enable() _simd_s8x16_add_enable()
//#elif defined(_simd_s8x32_add_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_add(const register _simd_s8x2 x, const register _simd_s8x2 y) {
//		union SIMDUnion { _simd_s8x2 v1; _simd_s8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x2_add_enable() _simd_s8x32_add_enable()
//#elif defined(_simd_s8x64_add_)
//	static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_add(const register _simd_s8x2 x, const register _simd_s8x2 y) {
//		union SIMDUnion { _simd_s8x2 v1; _simd_s8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x2_add_enable() _simd_s8x64_add_enable()
//#else
//	#define _simd_s8x2_add(X,Y) _simd_s8x2_combine(\
//		_simd_s8x1_add(_simd_s8x2_splitlo(X), _simd_s8x2_splitlo(Y)),\
//		_simd_s8x1_add(_simd_s8x2_splithi(X), _simd_s8x2_splithi(Y)))
//	#define _simd_s8x2_add_enable() (_simd_s8x1_add_enable() && _simd_s8x2_combine_enable() && _simd_s8x2_splitlo_enable()  && _simd_s8x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x2_add_) && ! defined(_simd_s8x2_add_scalar_)
//	#define _simd_s8x2_add_scalar_(X,Y) _simd_s8x2_add_(X,_simd_s8x2_fill_scalar_(Y))
//	#define _simd_s8x2_add_scalar_instruction_set _simd_s8x2_add_instruction_set
//#endif
//#ifdef _simd_s8x2_add_scalar_
//	#define _simd_s8x2_add_scalar(X,Y) _simd_s8x2_add_scalar_(X,Y)
//	#define _simd_s8x2_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_add_scalar_instruction_set>()
//#else
//	#define _simd_s8x2_add_scalar(X,Y) _simd_s8x2_add_safe(X,_simd_s8x2_fill_scalar_safe(Y))
//	#define _simd_s8x2_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_s8x1_add_safe
//	#define _simd_s8x1_add_safe(X,Y) (X + Y)
//	#define _simd_s8x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_s8x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_add_enabled() true
//#endif
//
//#define _simd_s8x4_add_safe(X,Y)_simd_s8x4_combine_safe(\
//	_simd_s8x2_add_safe(_simd_s8x4_splitlo_safe(X), _simd_ s8x4_splitlo_safe(Y)),\
//	_simd_s8x2_add_safe(_simd_s8x4_splithi_safe(X), _simd_ s8x4_splithi_safe(Y)))
//#ifdef _simd_s8x4_add_
//	#define _simd_s8x4_add(X,Y) _simd_s8x4_add_(X, Y)
//	#define _simd_s8x4_add_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_add_instruction_set>()
//#elif defined(_simd_s8x8_add_)
//	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_add(const register _simd_s8x4 x, const register _simd_s8x4 y) {
//		union SIMDUnion { _simd_s8x4 v1; _simd_s8x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x8_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x4_add_enable() _simd_s8x8_add_enable()
//#elif defined(_simd_s8x16_add_)
//	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_add(const register _simd_s8x4 x, const register _simd_s8x4 y) {
//		union SIMDUnion { _simd_s8x4 v1; _simd_s8x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x16_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x4_add_enable() _simd_s8x16_add_enable()
//#elif defined(_simd_s8x32_add_)
//	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_add(const register _simd_s8x4 x, const register _simd_s8x4 y) {
//		union SIMDUnion { _simd_s8x4 v1; _simd_s8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x4_add_enable() _simd_s8x32_add_enable()
//#elif defined(_simd_s8x64_add_)
//	static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_add(const register _simd_s8x4 x, const register _simd_s8x4 y) {
//		union SIMDUnion { _simd_s8x4 v1; _simd_s8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x4_add_enable() _simd_s8x64_add_enable()
//#else
//	#define _simd_s8x4_add(X,Y) _simd_s8x4_combine(\
//		_simd_s8x2_add(_simd_s8x4_splitlo(X), _simd_s8x4_splitlo(Y)),\
//		_simd_s8x2_add(_simd_s8x4_splithi(X), _simd_s8x4_splithi(Y)))
//	#define _simd_s8x4_add_enable() (_simd_s8x2_add_enable() && _simd_s8x4_combine_enable() && _simd_s8x4_splitlo_enable()  && _simd_s8x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x4_add_) && ! defined(_simd_s8x4_add_scalar_)
//	#define _simd_s8x4_add_scalar_(X,Y) _simd_s8x4_add_(X,_simd_s8x4_fill_scalar_(Y))
//	#define _simd_s8x4_add_scalar_instruction_set _simd_s8x4_add_instruction_set
//#endif
//#ifdef _simd_s8x4_add_scalar_
//	#define _simd_s8x4_add_scalar(X,Y) _simd_s8x4_add_scalar_(X,Y)
//	#define _simd_s8x4_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_add_scalar_instruction_set>()
//#else
//	#define _simd_s8x4_add_scalar(X,Y) _simd_s8x4_add_safe(X,_simd_s8x4_fill_scalar_safe(Y))
//	#define _simd_s8x4_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_s8x1_add_safe
//	#define _simd_s8x1_add_safe(X,Y) (X + Y)
//	#define _simd_s8x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_s8x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_add_enabled() true
//#endif
//
//#define _simd_s8x8_add_safe(X,Y)_simd_s8x8_combine_safe(\
//	_simd_s8x4_add_safe(_simd_s8x8_splitlo_safe(X), _simd_ s8x8_splitlo_safe(Y)),\
//	_simd_s8x4_add_safe(_simd_s8x8_splithi_safe(X), _simd_ s8x8_splithi_safe(Y)))
//#ifdef _simd_s8x8_add_
//	#define _simd_s8x8_add(X,Y) _simd_s8x8_add_(X, Y)
//	#define _simd_s8x8_add_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_add_instruction_set>()
//#elif defined(_simd_s8x16_add_)
//	static ANVIL_STRONG_INLINE _simd_s8x8 ANVIL_SIMD_CALL _simd_s8x8_add(const register _simd_s8x8 x, const register _simd_s8x8 y) {
//		union SIMDUnion { _simd_s8x8 v1; _simd_s8x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x16_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x8_add_enable() _simd_s8x16_add_enable()
//#elif defined(_simd_s8x32_add_)
//	static ANVIL_STRONG_INLINE _simd_s8x8 ANVIL_SIMD_CALL _simd_s8x8_add(const register _simd_s8x8 x, const register _simd_s8x8 y) {
//		union SIMDUnion { _simd_s8x8 v1; _simd_s8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x8_add_enable() _simd_s8x32_add_enable()
//#elif defined(_simd_s8x64_add_)
//	static ANVIL_STRONG_INLINE _simd_s8x8 ANVIL_SIMD_CALL _simd_s8x8_add(const register _simd_s8x8 x, const register _simd_s8x8 y) {
//		union SIMDUnion { _simd_s8x8 v1; _simd_s8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x8_add_enable() _simd_s8x64_add_enable()
//#else
//	#define _simd_s8x8_add(X,Y) _simd_s8x8_combine(\
//		_simd_s8x4_add(_simd_s8x8_splitlo(X), _simd_s8x8_splitlo(Y)),\
//		_simd_s8x4_add(_simd_s8x8_splithi(X), _simd_s8x8_splithi(Y)))
//	#define _simd_s8x8_add_enable() (_simd_s8x4_add_enable() && _simd_s8x8_combine_enable() && _simd_s8x8_splitlo_enable()  && _simd_s8x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x8_add_) && ! defined(_simd_s8x8_add_scalar_)
//	#define _simd_s8x8_add_scalar_(X,Y) _simd_s8x8_add_(X,_simd_s8x8_fill_scalar_(Y))
//	#define _simd_s8x8_add_scalar_instruction_set _simd_s8x8_add_instruction_set
//#endif
//#ifdef _simd_s8x8_add_scalar_
//	#define _simd_s8x8_add_scalar(X,Y) _simd_s8x8_add_scalar_(X,Y)
//	#define _simd_s8x8_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_add_scalar_instruction_set>()
//#else
//	#define _simd_s8x8_add_scalar(X,Y) _simd_s8x8_add_safe(X,_simd_s8x8_fill_scalar_safe(Y))
//	#define _simd_s8x8_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_s8x1_add_safe
//	#define _simd_s8x1_add_safe(X,Y) (X + Y)
//	#define _simd_s8x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_s8x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_add_enabled() true
//#endif
//
//#define _simd_s8x16_add_safe(X,Y)_simd_s8x16_combine_safe(\
//	_simd_s8x8_add_safe(_simd_s8x16_splitlo_safe(X), _simd_ s8x16_splitlo_safe(Y)),\
//	_simd_s8x8_add_safe(_simd_s8x16_splithi_safe(X), _simd_ s8x16_splithi_safe(Y)))
//#ifdef _simd_s8x16_add_
//	#define _simd_s8x16_add(X,Y) _simd_s8x16_add_(X, Y)
//	#define _simd_s8x16_add_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_add_instruction_set>()
//#elif defined(_simd_s8x32_add_)
//	static ANVIL_STRONG_INLINE _simd_s8x16 ANVIL_SIMD_CALL _simd_s8x16_add(const register _simd_s8x16 x, const register _simd_s8x16 y) {
//		union SIMDUnion { _simd_s8x16 v1; _simd_s8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x16_add_enable() _simd_s8x32_add_enable()
//#elif defined(_simd_s8x64_add_)
//	static ANVIL_STRONG_INLINE _simd_s8x16 ANVIL_SIMD_CALL _simd_s8x16_add(const register _simd_s8x16 x, const register _simd_s8x16 y) {
//		union SIMDUnion { _simd_s8x16 v1; _simd_s8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x16_add_enable() _simd_s8x64_add_enable()
//#else
//	#define _simd_s8x16_add(X,Y) _simd_s8x16_combine(\
//		_simd_s8x8_add(_simd_s8x16_splitlo(X), _simd_s8x16_splitlo(Y)),\
//		_simd_s8x8_add(_simd_s8x16_splithi(X), _simd_s8x16_splithi(Y)))
//	#define _simd_s8x16_add_enable() (_simd_s8x8_add_enable() && _simd_s8x16_combine_enable() && _simd_s8x16_splitlo_enable()  && _simd_s8x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x16_add_) && ! defined(_simd_s8x16_add_scalar_)
//	#define _simd_s8x16_add_scalar_(X,Y) _simd_s8x16_add_(X,_simd_s8x16_fill_scalar_(Y))
//	#define _simd_s8x16_add_scalar_instruction_set _simd_s8x16_add_instruction_set
//#endif
//#ifdef _simd_s8x16_add_scalar_
//	#define _simd_s8x16_add_scalar(X,Y) _simd_s8x16_add_scalar_(X,Y)
//	#define _simd_s8x16_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_add_scalar_instruction_set>()
//#else
//	#define _simd_s8x16_add_scalar(X,Y) _simd_s8x16_add_safe(X,_simd_s8x16_fill_scalar_safe(Y))
//	#define _simd_s8x16_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_s8x1_add_safe
//	#define _simd_s8x1_add_safe(X,Y) (X + Y)
//	#define _simd_s8x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_s8x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_add_enabled() true
//#endif
//
//#define _simd_s8x32_add_safe(X,Y)_simd_s8x32_combine_safe(\
//	_simd_s8x16_add_safe(_simd_s8x32_splitlo_safe(X), _simd_ s8x32_splitlo_safe(Y)),\
//	_simd_s8x16_add_safe(_simd_s8x32_splithi_safe(X), _simd_ s8x32_splithi_safe(Y)))
//#ifdef _simd_s8x32_add_
//	#define _simd_s8x32_add(X,Y) _simd_s8x32_add_(X, Y)
//	#define _simd_s8x32_add_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_add_instruction_set>()
//#elif defined(_simd_s8x64_add_)
//	static ANVIL_STRONG_INLINE _simd_s8x32 ANVIL_SIMD_CALL _simd_s8x32_add(const register _simd_s8x32 x, const register _simd_s8x32 y) {
//		union SIMDUnion { _simd_s8x32 v1; _simd_s8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_s8x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_s8x32_add_enable() _simd_s8x64_add_enable()
//#else
//	#define _simd_s8x32_add(X,Y) _simd_s8x32_combine(\
//		_simd_s8x16_add(_simd_s8x32_splitlo(X), _simd_s8x32_splitlo(Y)),\
//		_simd_s8x16_add(_simd_s8x32_splithi(X), _simd_s8x32_splithi(Y)))
//	#define _simd_s8x32_add_enable() (_simd_s8x16_add_enable() && _simd_s8x32_combine_enable() && _simd_s8x32_splitlo_enable()  && _simd_s8x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x32_add_) && ! defined(_simd_s8x32_add_scalar_)
//	#define _simd_s8x32_add_scalar_(X,Y) _simd_s8x32_add_(X,_simd_s8x32_fill_scalar_(Y))
//	#define _simd_s8x32_add_scalar_instruction_set _simd_s8x32_add_instruction_set
//#endif
//#ifdef _simd_s8x32_add_scalar_
//	#define _simd_s8x32_add_scalar(X,Y) _simd_s8x32_add_scalar_(X,Y)
//	#define _simd_s8x32_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_add_scalar_instruction_set>()
//#else
//	#define _simd_s8x32_add_scalar(X,Y) _simd_s8x32_add_safe(X,_simd_s8x32_fill_scalar_safe(Y))
//	#define _simd_s8x32_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_s8x1_add_safe
//	#define _simd_s8x1_add_safe(X,Y) (X + Y)
//	#define _simd_s8x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_s8x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_s8x1_add_enabled() true
//#endif
//
//#define _simd_s8x64_add_safe(X,Y)_simd_s8x64_combine_safe(\
//	_simd_s8x32_add_safe(_simd_s8x64_splitlo_safe(X), _simd_ s8x64_splitlo_safe(Y)),\
//	_simd_s8x32_add_safe(_simd_s8x64_splithi_safe(X), _simd_ s8x64_splithi_safe(Y)))
//#ifdef _simd_s8x64_add_
//	#define _simd_s8x64_add(X,Y) _simd_s8x64_add_(X, Y)
//	#define _simd_s8x64_add_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_add_instruction_set>()
//#else
//	#define _simd_s8x64_add(X,Y) _simd_s8x64_combine(\
//		_simd_s8x32_add(_simd_s8x64_splitlo(X), _simd_s8x64_splitlo(Y)),\
//		_simd_s8x32_add(_simd_s8x64_splithi(X), _simd_s8x64_splithi(Y)))
//	#define _simd_s8x64_add_enable() (_simd_s8x32_add_enable() && _simd_s8x64_combine_enable() && _simd_s8x64_splitlo_enable()  && _simd_s8x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_s8x64_add_) && ! defined(_simd_s8x64_add_scalar_)
//	#define _simd_s8x64_add_scalar_(X,Y) _simd_s8x64_add_(X,_simd_s8x64_fill_scalar_(Y))
//	#define _simd_s8x64_add_scalar_instruction_set _simd_s8x64_add_instruction_set
//#endif
//#ifdef _simd_s8x64_add_scalar_
//	#define _simd_s8x64_add_scalar(X,Y) _simd_s8x64_add_scalar_(X,Y)
//	#define _simd_s8x64_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_add_scalar_instruction_set>()
//#else
//	#define _simd_s8x64_add_scalar(X,Y) _simd_s8x64_add_safe(X,_simd_s8x64_fill_scalar_safe(Y))
//	#define _simd_s8x64_add_scalar_enabled() true
//#endif
//
//// -- u8 --
//
//#ifndef _simd_u8x1_add_safe
//	#define _simd_u8x1_add_safe(X,Y) (X + Y)
//	#define _simd_u8x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_u8x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_add_enabled() true
//#endif
//
//#define _simd_u8x2_add_safe(X,Y)_simd_u8x2_combine_safe(\
//	_simd_u8x1_add_safe(_simd_u8x2_splitlo_safe(X), _simd_ u8x2_splitlo_safe(Y)),\
//	_simd_u8x1_add_safe(_simd_u8x2_splithi_safe(X), _simd_ u8x2_splithi_safe(Y)))
//#ifdef _simd_u8x2_add_
//	#define _simd_u8x2_add(X,Y) _simd_u8x2_add_(X, Y)
//	#define _simd_u8x2_add_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_add_instruction_set>()
//#elif defined(_simd_u8x4_add_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_add(const register _simd_u8x2 x, const register _simd_u8x2 y) {
//		union SIMDUnion { _simd_u8x2 v1; _simd_u8x4 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x4_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x2_add_enable() _simd_u8x4_add_enable()
//#elif defined(_simd_u8x8_add_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_add(const register _simd_u8x2 x, const register _simd_u8x2 y) {
//		union SIMDUnion { _simd_u8x2 v1; _simd_u8x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x8_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x2_add_enable() _simd_u8x8_add_enable()
//#elif defined(_simd_u8x16_add_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_add(const register _simd_u8x2 x, const register _simd_u8x2 y) {
//		union SIMDUnion { _simd_u8x2 v1; _simd_u8x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x16_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x2_add_enable() _simd_u8x16_add_enable()
//#elif defined(_simd_u8x32_add_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_add(const register _simd_u8x2 x, const register _simd_u8x2 y) {
//		union SIMDUnion { _simd_u8x2 v1; _simd_u8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x2_add_enable() _simd_u8x32_add_enable()
//#elif defined(_simd_u8x64_add_)
//	static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_add(const register _simd_u8x2 x, const register _simd_u8x2 y) {
//		union SIMDUnion { _simd_u8x2 v1; _simd_u8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x2_add_enable() _simd_u8x64_add_enable()
//#else
//	#define _simd_u8x2_add(X,Y) _simd_u8x2_combine(\
//		_simd_u8x1_add(_simd_u8x2_splitlo(X), _simd_u8x2_splitlo(Y)),\
//		_simd_u8x1_add(_simd_u8x2_splithi(X), _simd_u8x2_splithi(Y)))
//	#define _simd_u8x2_add_enable() (_simd_u8x1_add_enable() && _simd_u8x2_combine_enable() && _simd_u8x2_splitlo_enable()  && _simd_u8x2_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x2_add_) && ! defined(_simd_u8x2_add_scalar_)
//	#define _simd_u8x2_add_scalar_(X,Y) _simd_u8x2_add_(X,_simd_u8x2_fill_scalar_(Y))
//	#define _simd_u8x2_add_scalar_instruction_set _simd_u8x2_add_instruction_set
//#endif
//#ifdef _simd_u8x2_add_scalar_
//	#define _simd_u8x2_add_scalar(X,Y) _simd_u8x2_add_scalar_(X,Y)
//	#define _simd_u8x2_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_add_scalar_instruction_set>()
//#else
//	#define _simd_u8x2_add_scalar(X,Y) _simd_u8x2_add_safe(X,_simd_u8x2_fill_scalar_safe(Y))
//	#define _simd_u8x2_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_u8x1_add_safe
//	#define _simd_u8x1_add_safe(X,Y) (X + Y)
//	#define _simd_u8x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_u8x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_add_enabled() true
//#endif
//
//#define _simd_u8x4_add_safe(X,Y)_simd_u8x4_combine_safe(\
//	_simd_u8x2_add_safe(_simd_u8x4_splitlo_safe(X), _simd_ u8x4_splitlo_safe(Y)),\
//	_simd_u8x2_add_safe(_simd_u8x4_splithi_safe(X), _simd_ u8x4_splithi_safe(Y)))
//#ifdef _simd_u8x4_add_
//	#define _simd_u8x4_add(X,Y) _simd_u8x4_add_(X, Y)
//	#define _simd_u8x4_add_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_add_instruction_set>()
//#elif defined(_simd_u8x8_add_)
//	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_add(const register _simd_u8x4 x, const register _simd_u8x4 y) {
//		union SIMDUnion { _simd_u8x4 v1; _simd_u8x8 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x8_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x4_add_enable() _simd_u8x8_add_enable()
//#elif defined(_simd_u8x16_add_)
//	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_add(const register _simd_u8x4 x, const register _simd_u8x4 y) {
//		union SIMDUnion { _simd_u8x4 v1; _simd_u8x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x16_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x4_add_enable() _simd_u8x16_add_enable()
//#elif defined(_simd_u8x32_add_)
//	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_add(const register _simd_u8x4 x, const register _simd_u8x4 y) {
//		union SIMDUnion { _simd_u8x4 v1; _simd_u8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x4_add_enable() _simd_u8x32_add_enable()
//#elif defined(_simd_u8x64_add_)
//	static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_add(const register _simd_u8x4 x, const register _simd_u8x4 y) {
//		union SIMDUnion { _simd_u8x4 v1; _simd_u8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x4_add_enable() _simd_u8x64_add_enable()
//#else
//	#define _simd_u8x4_add(X,Y) _simd_u8x4_combine(\
//		_simd_u8x2_add(_simd_u8x4_splitlo(X), _simd_u8x4_splitlo(Y)),\
//		_simd_u8x2_add(_simd_u8x4_splithi(X), _simd_u8x4_splithi(Y)))
//	#define _simd_u8x4_add_enable() (_simd_u8x2_add_enable() && _simd_u8x4_combine_enable() && _simd_u8x4_splitlo_enable()  && _simd_u8x4_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x4_add_) && ! defined(_simd_u8x4_add_scalar_)
//	#define _simd_u8x4_add_scalar_(X,Y) _simd_u8x4_add_(X,_simd_u8x4_fill_scalar_(Y))
//	#define _simd_u8x4_add_scalar_instruction_set _simd_u8x4_add_instruction_set
//#endif
//#ifdef _simd_u8x4_add_scalar_
//	#define _simd_u8x4_add_scalar(X,Y) _simd_u8x4_add_scalar_(X,Y)
//	#define _simd_u8x4_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_add_scalar_instruction_set>()
//#else
//	#define _simd_u8x4_add_scalar(X,Y) _simd_u8x4_add_safe(X,_simd_u8x4_fill_scalar_safe(Y))
//	#define _simd_u8x4_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_u8x1_add_safe
//	#define _simd_u8x1_add_safe(X,Y) (X + Y)
//	#define _simd_u8x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_u8x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_add_enabled() true
//#endif
//
//#define _simd_u8x8_add_safe(X,Y)_simd_u8x8_combine_safe(\
//	_simd_u8x4_add_safe(_simd_u8x8_splitlo_safe(X), _simd_ u8x8_splitlo_safe(Y)),\
//	_simd_u8x4_add_safe(_simd_u8x8_splithi_safe(X), _simd_ u8x8_splithi_safe(Y)))
//#ifdef _simd_u8x8_add_
//	#define _simd_u8x8_add(X,Y) _simd_u8x8_add_(X, Y)
//	#define _simd_u8x8_add_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_add_instruction_set>()
//#elif defined(_simd_u8x16_add_)
//	static ANVIL_STRONG_INLINE _simd_u8x8 ANVIL_SIMD_CALL _simd_u8x8_add(const register _simd_u8x8 x, const register _simd_u8x8 y) {
//		union SIMDUnion { _simd_u8x8 v1; _simd_u8x16 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x16_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x8_add_enable() _simd_u8x16_add_enable()
//#elif defined(_simd_u8x32_add_)
//	static ANVIL_STRONG_INLINE _simd_u8x8 ANVIL_SIMD_CALL _simd_u8x8_add(const register _simd_u8x8 x, const register _simd_u8x8 y) {
//		union SIMDUnion { _simd_u8x8 v1; _simd_u8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x8_add_enable() _simd_u8x32_add_enable()
//#elif defined(_simd_u8x64_add_)
//	static ANVIL_STRONG_INLINE _simd_u8x8 ANVIL_SIMD_CALL _simd_u8x8_add(const register _simd_u8x8 x, const register _simd_u8x8 y) {
//		union SIMDUnion { _simd_u8x8 v1; _simd_u8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x8_add_enable() _simd_u8x64_add_enable()
//#else
//	#define _simd_u8x8_add(X,Y) _simd_u8x8_combine(\
//		_simd_u8x4_add(_simd_u8x8_splitlo(X), _simd_u8x8_splitlo(Y)),\
//		_simd_u8x4_add(_simd_u8x8_splithi(X), _simd_u8x8_splithi(Y)))
//	#define _simd_u8x8_add_enable() (_simd_u8x4_add_enable() && _simd_u8x8_combine_enable() && _simd_u8x8_splitlo_enable()  && _simd_u8x8_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x8_add_) && ! defined(_simd_u8x8_add_scalar_)
//	#define _simd_u8x8_add_scalar_(X,Y) _simd_u8x8_add_(X,_simd_u8x8_fill_scalar_(Y))
//	#define _simd_u8x8_add_scalar_instruction_set _simd_u8x8_add_instruction_set
//#endif
//#ifdef _simd_u8x8_add_scalar_
//	#define _simd_u8x8_add_scalar(X,Y) _simd_u8x8_add_scalar_(X,Y)
//	#define _simd_u8x8_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_add_scalar_instruction_set>()
//#else
//	#define _simd_u8x8_add_scalar(X,Y) _simd_u8x8_add_safe(X,_simd_u8x8_fill_scalar_safe(Y))
//	#define _simd_u8x8_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_u8x1_add_safe
//	#define _simd_u8x1_add_safe(X,Y) (X + Y)
//	#define _simd_u8x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_u8x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_add_enabled() true
//#endif
//
//#define _simd_u8x16_add_safe(X,Y)_simd_u8x16_combine_safe(\
//	_simd_u8x8_add_safe(_simd_u8x16_splitlo_safe(X), _simd_ u8x16_splitlo_safe(Y)),\
//	_simd_u8x8_add_safe(_simd_u8x16_splithi_safe(X), _simd_ u8x16_splithi_safe(Y)))
//#ifdef _simd_u8x16_add_
//	#define _simd_u8x16_add(X,Y) _simd_u8x16_add_(X, Y)
//	#define _simd_u8x16_add_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_add_instruction_set>()
//#elif defined(_simd_u8x32_add_)
//	static ANVIL_STRONG_INLINE _simd_u8x16 ANVIL_SIMD_CALL _simd_u8x16_add(const register _simd_u8x16 x, const register _simd_u8x16 y) {
//		union SIMDUnion { _simd_u8x16 v1; _simd_u8x32 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x32_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x16_add_enable() _simd_u8x32_add_enable()
//#elif defined(_simd_u8x64_add_)
//	static ANVIL_STRONG_INLINE _simd_u8x16 ANVIL_SIMD_CALL _simd_u8x16_add(const register _simd_u8x16 x, const register _simd_u8x16 y) {
//		union SIMDUnion { _simd_u8x16 v1; _simd_u8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x16_add_enable() _simd_u8x64_add_enable()
//#else
//	#define _simd_u8x16_add(X,Y) _simd_u8x16_combine(\
//		_simd_u8x8_add(_simd_u8x16_splitlo(X), _simd_u8x16_splitlo(Y)),\
//		_simd_u8x8_add(_simd_u8x16_splithi(X), _simd_u8x16_splithi(Y)))
//	#define _simd_u8x16_add_enable() (_simd_u8x8_add_enable() && _simd_u8x16_combine_enable() && _simd_u8x16_splitlo_enable()  && _simd_u8x16_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x16_add_) && ! defined(_simd_u8x16_add_scalar_)
//	#define _simd_u8x16_add_scalar_(X,Y) _simd_u8x16_add_(X,_simd_u8x16_fill_scalar_(Y))
//	#define _simd_u8x16_add_scalar_instruction_set _simd_u8x16_add_instruction_set
//#endif
//#ifdef _simd_u8x16_add_scalar_
//	#define _simd_u8x16_add_scalar(X,Y) _simd_u8x16_add_scalar_(X,Y)
//	#define _simd_u8x16_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_add_scalar_instruction_set>()
//#else
//	#define _simd_u8x16_add_scalar(X,Y) _simd_u8x16_add_safe(X,_simd_u8x16_fill_scalar_safe(Y))
//	#define _simd_u8x16_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_u8x1_add_safe
//	#define _simd_u8x1_add_safe(X,Y) (X + Y)
//	#define _simd_u8x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_u8x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_add_enabled() true
//#endif
//
//#define _simd_u8x32_add_safe(X,Y)_simd_u8x32_combine_safe(\
//	_simd_u8x16_add_safe(_simd_u8x32_splitlo_safe(X), _simd_ u8x32_splitlo_safe(Y)),\
//	_simd_u8x16_add_safe(_simd_u8x32_splithi_safe(X), _simd_ u8x32_splithi_safe(Y)))
//#ifdef _simd_u8x32_add_
//	#define _simd_u8x32_add(X,Y) _simd_u8x32_add_(X, Y)
//	#define _simd_u8x32_add_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_add_instruction_set>()
//#elif defined(_simd_u8x64_add_)
//	static ANVIL_STRONG_INLINE _simd_u8x32 ANVIL_SIMD_CALL _simd_u8x32_add(const register _simd_u8x32 x, const register _simd_u8x32 y) {
//		union SIMDUnion { _simd_u8x32 v1; _simd_u8x64 v2; };
//		SIMDUnion x_, y_;
//		x_.v1 = x;
//		y_.v1 = y;
//		x_.v2 = _simd_u8x64_add_(x_.v2, y_.v2);
//		return x_.v1;
//	}
//	#define _simd_u8x32_add_enable() _simd_u8x64_add_enable()
//#else
//	#define _simd_u8x32_add(X,Y) _simd_u8x32_combine(\
//		_simd_u8x16_add(_simd_u8x32_splitlo(X), _simd_u8x32_splitlo(Y)),\
//		_simd_u8x16_add(_simd_u8x32_splithi(X), _simd_u8x32_splithi(Y)))
//	#define _simd_u8x32_add_enable() (_simd_u8x16_add_enable() && _simd_u8x32_combine_enable() && _simd_u8x32_splitlo_enable()  && _simd_u8x32_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x32_add_) && ! defined(_simd_u8x32_add_scalar_)
//	#define _simd_u8x32_add_scalar_(X,Y) _simd_u8x32_add_(X,_simd_u8x32_fill_scalar_(Y))
//	#define _simd_u8x32_add_scalar_instruction_set _simd_u8x32_add_instruction_set
//#endif
//#ifdef _simd_u8x32_add_scalar_
//	#define _simd_u8x32_add_scalar(X,Y) _simd_u8x32_add_scalar_(X,Y)
//	#define _simd_u8x32_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_add_scalar_instruction_set>()
//#else
//	#define _simd_u8x32_add_scalar(X,Y) _simd_u8x32_add_safe(X,_simd_u8x32_fill_scalar_safe(Y))
//	#define _simd_u8x32_add_scalar_enabled() true
//#endif
//
//#ifndef _simd_u8x1_add_safe
//	#define _simd_u8x1_add_safe(X,Y) (X + Y)
//	#define _simd_u8x1_add_(X,Y) x1_add_safe(X,Y)
//	#define _simd_u8x1_add_instruction_set() anvil::simd::IS_NONE
//	#define _simd_u8x1_add_enabled() true
//#endif
//
//#define _simd_u8x64_add_safe(X,Y)_simd_u8x64_combine_safe(\
//	_simd_u8x32_add_safe(_simd_u8x64_splitlo_safe(X), _simd_ u8x64_splitlo_safe(Y)),\
//	_simd_u8x32_add_safe(_simd_u8x64_splithi_safe(X), _simd_ u8x64_splithi_safe(Y)))
//#ifdef _simd_u8x64_add_
//	#define _simd_u8x64_add(X,Y) _simd_u8x64_add_(X, Y)
//	#define _simd_u8x64_add_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_add_instruction_set>()
//#else
//	#define _simd_u8x64_add(X,Y) _simd_u8x64_combine(\
//		_simd_u8x32_add(_simd_u8x64_splitlo(X), _simd_u8x64_splitlo(Y)),\
//		_simd_u8x32_add(_simd_u8x64_splithi(X), _simd_u8x64_splithi(Y)))
//	#define _simd_u8x64_add_enable() (_simd_u8x32_add_enable() && _simd_u8x64_combine_enable() && _simd_u8x64_splitlo_enable()  && _simd_u8x64_splithi_enable())
//#endif
//
//
//#if defined(_simd_u8x64_add_) && ! defined(_simd_u8x64_add_scalar_)
//	#define _simd_u8x64_add_scalar_(X,Y) _simd_u8x64_add_(X,_simd_u8x64_fill_scalar_(Y))
//	#define _simd_u8x64_add_scalar_instruction_set _simd_u8x64_add_instruction_set
//#endif
//#ifdef _simd_u8x64_add_scalar_
//	#define _simd_u8x64_add_scalar(X,Y) _simd_u8x64_add_scalar_(X,Y)
//	#define _simd_u8x64_add_scalar_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_add_scalar_instruction_set>()
//#else
//	#define _simd_u8x64_add_scalar(X,Y) _simd_u8x64_add_safe(X,_simd_u8x64_fill_scalar_safe(Y))
//	#define _simd_u8x64_add_scalar_enabled() true
//#endif
//
