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

#include "anvil/core/CpuRuntime.hpp"
#include "anvil/compute/Vector.hpp"

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
			optimised = (size == 1u && std::is_fundemental<T>::value) ? 1u : 0u
		};

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

		template<uint64_t instruction_set, NativeUnsigned OP>
		static inline void Execute(native_t a, const native_t b, native_t& out) {
			for (size_t i = 0u; i < S; ++i) VectorArithNative<T, T>::Execute<instruction_set, OP>(a.data[i], b.data[i], out.data[i]);
		}
	};

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64

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

		template<NativeUnsigned OP>
		static inline void ExecuteC(const native_t& a, const native_t& b, native_t& out) {
			const T* const at = reinterpret_cast<const T*>(&a);
			const T* const bt = reinterpret_cast<const T*>(&b);
			const T* const outT = reinterpret_cast<const T*>(&out);

			for (size_t i = 0u; i < S; ++i) VectorArithNative<T, T>::Execute<0u, OP>(at[i], bt[i], outT[i]);
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
		static ANVIL_STRONG_INLINE T Execute(const native_t& a, const native_t& b, native_t& out) {
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

		template<NativeUnsigned OP>
		static inline void ExecuteC(const native_t& a, const native_t& b, native_t& out) {
			const T* const at = reinterpret_cast<const T*>(&a);
			const T* const bt = reinterpret_cast<const T*>(&b);
			const T* const outT = reinterpret_cast<const T*>(&out);

			for (size_t i = 0u; i < S; ++i) VectorArithNative<T, T>::Execute<0u, OP>(at[i], bt[i], outT[i]);
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
			if constexpr ((instruction_set & ASM_SSE2) != 0ull) {
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

		template<NativeUnsigned OP>
		static inline void ExecuteC(const native_t& a, const native_t& b, native_t& out) {
			const T* const at = reinterpret_cast<const T*>(&a);
			const T* const bt = reinterpret_cast<const T*>(&b);
			const T* const outT = reinterpret_cast<const T*>(&out);

			for (size_t i = 0u; i < S; ++i) VectorArithNative<T, T>::Execute<0u, OP>(at[i], bt[i], outT[i]);
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
				out = _mm_cmpeq_epi32(a, b);
				
			} else if constexpr (OP == ANVIL_VECTOR_ARITH_CMPNE) {
				out = _mm_cmpneq_epi32(a, b);
				
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

		template<uint64_t instruction_set, NativeUnsigned OP>
		static ANVIL_STRONG_INLINE void Execute(const native_t& a, const native_t& b, native_t& out) {
			if constexpr ((instruction_set & ASM_SSE2) != 0ull) {
				ExecuteSSE2<OP>(a, b, out);
			} else {
				ExecuteC<OP>(a, b, out);
			}
		}
	};
#endif

	template<class T>
	struct VectorAdd;

	// Scalar types

	template<>
	struct VectorAdd<uint8_t> {
		typedef uint8_t type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			return a + b;
		}
	};

	template<>
	struct VectorAdd<uint16_t> {
		typedef uint16_t type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			return a + b;
		}
	};

	template<>
	struct VectorAdd<uint32_t> {
		typedef uint32_t type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			return a + b;
		}
	};

	template<>
	struct VectorAdd<uint64_t> {
		typedef uint64_t type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			return a + b;
		}
	};

	template<>
	struct VectorAdd<int8_t> {
		typedef int8_t type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			return a + b;
		}
	};

	template<>
	struct VectorAdd<int16_t> {
		typedef int16_t type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			return a + b;
		}
	};

	template<>
	struct VectorAdd<int32_t> {
		typedef int32_t type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			return a + b;
		}
	};

	template<>
	struct VectorAdd<int64_t> {
		typedef int64_t type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			return a + b;
		}
	};

	template<>
	struct VectorAdd<float32_t> {
		typedef float32_t type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			return a + b;
		}
	};

	template<>
	struct VectorAdd<float64_t> {
		typedef float64_t type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, type b) throw() {
			return a + b;
		}
	};

	// Optimised vectors


#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64

	template<>
	struct VectorAdd<detail::BasicVector<float32_t, 4u>> {
		typedef detail::BasicVector<float32_t, 4u> type;

		static ANVIL_STRONG_INLINE type Execute_SSE(type a, const type& b) throw() {
			a.native = _mm_add_ps(a.native, b.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(const type& a, const type& b) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_SSE) != 0ull) {
				return Execute_SSE(a, b);
			} else {
				a.lower_half = VectorAdd<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorAdd<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
				return a;
			}
		}
	};

	template<>
	struct VectorAdd<detail::BasicVector<float32_t, 8u>> {
		typedef detail::BasicVector<float32_t, 8u> type;

		static ANVIL_STRONG_INLINE type Execute_AVX(type a, const type& b) throw() {
			a.native = _mm256_add_ps(a.native, b.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, const type& b) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_AVX) != 0ull) {
				return Execute_AVX(a, b);
			} else {
				a.lower_half = VectorAdd<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorAdd<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
				return a;
			}
		}
	};

	template<>
	struct VectorAdd<detail::BasicVector<float32_t, 16u>> {
		typedef detail::BasicVector<float32_t, 16u> type;

		static ANVIL_STRONG_INLINE type Execute_AVX512F(type a, const type& b) throw() {
			a.native = _mm512_add_ps(a.native, b.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, const type& b) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_AVX512F) != 0ull) {
				return Execute_AVX512F(a, b);
			} else {
				a.lower_half = VectorAdd<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorAdd<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
				return a;
			}
		}
	};

	template<>
	struct VectorAdd<detail::BasicVector<float64_t, 2u>> {
		typedef detail::BasicVector<float64_t, 2u> type;

		static ANVIL_STRONG_INLINE type Execute_SSE2(type a, const type& b) throw() {
			a.native = _mm_add_pd(a.native, b.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(const type& a, const type& b) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_SSE2) != 0ull) {
				return Execute_SSE2(a, b);
			} else {
				a.lower_half = VectorAdd<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorAdd<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
				return a;
			}
		}
	};

	template<>
	struct VectorAdd<detail::BasicVector<float64_t, 4u>> {
		typedef detail::BasicVector<float64_t, 4u> type;

		static ANVIL_STRONG_INLINE type Execute_AVX(type a, const type& b) throw() {
			a.native = _mm256_add_pd(a.native, b.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, const type& b) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_AVX) != 0ull) {
				return Execute_AVX(a, b);
			} else {
				a.lower_half = VectorAdd<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorAdd<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
				return a;
			}
		}
	};

	template<>
	struct VectorAdd<detail::BasicVector<float64_t, 8u>> {
		typedef detail::BasicVector<float64_t, 8u> type;

		static ANVIL_STRONG_INLINE type Execute_AVX512F(type a, const type& b) throw() {
			a.native = _mm512_add_pd(a.native, b.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, const type& b) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_AVX512F) != 0ull) {
				return Execute_AVX512F(a, b);
			} else {
				a.lower_half = VectorAdd<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorAdd<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
				return a;
			}
		}
	};

	template<>
	struct VectorAdd<detail::BasicVector<int8_t, 16u>> {
		typedef detail::BasicVector<int8_t, 16u> type;

		static ANVIL_STRONG_INLINE type Execute_SSE2(type a, const type& b) throw() {
			a.native = _mm_adds_epi8(a.native, b.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(const type& a, const type& b) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_SSE2) != 0ull) {
				return Execute_SSE2(a, b);
			} else {
				a.lower_half = VectorAdd<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorAdd<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
				return a;
			}
		}
	};

	template<>
	struct VectorAdd<detail::BasicVector<int8_t, 32u>> {
		typedef detail::BasicVector<int8_t, 32u> type;

		static ANVIL_STRONG_INLINE type Execute_AVX2(type a, const type& b) throw() {
			a.native = _mm256_adds_epi8(a.native, b.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(const type& a, const type& b) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_AVX2) != 0ull) {
				return Execute_AVX2(a, b);
			} else {
				a.lower_half = VectorAdd<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorAdd<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
				return a;
			}
		}
	};

	template<>
	struct VectorAdd<detail::BasicVector<int8_t, 64u>> {
		typedef detail::BasicVector<int8_t, 64u> type;

		static ANVIL_STRONG_INLINE type Execute_AVX512BW(type a, const type& b) throw() {
			a.native = _mm512_adds_epi8(a.native, b.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(const type& a, const type& b) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_AVX512BW) != 0ull) {
				return Execute_AVX512BW(a, b);
			} else {
				a.lower_half = VectorAdd<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorAdd<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
				return a;
			}
		}
	};

	template<>
	struct VectorAdd<detail::BasicVector<int16_t, 8u>> {
		typedef detail::BasicVector<int16_t, 8u> type;

		static ANVIL_STRONG_INLINE type Execute_SSE2(type a, const type& b) throw() {
			a.native = _mm_adds_epi16(a.native, b.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(const type& a, const type& b) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_SSE2) != 0ull) {
				return Execute_SSE2(a, b);
			} else {
				a.lower_half = VectorAdd<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorAdd<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
				return a;
			}
		}
	};

	template<>
	struct VectorAdd<detail::BasicVector<int16_t, 16u>> {
		typedef detail::BasicVector<int16_t, 16u> type;

		static ANVIL_STRONG_INLINE type Execute_AVX2(type a, const type& b) throw() {
			a.native = _mm256_adds_epi16(a.native, b.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(const type& a, const type& b) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_AVX2) != 0ull) {
				return Execute_AVX2(a, b);
			} else {
				a.lower_half = VectorAdd<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorAdd<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
				return a;
			}
		}
	};

	template<>
	struct VectorAdd<detail::BasicVector<int16_t, 32u>> {
		typedef detail::BasicVector<int16_t, 32u> type;

		static ANVIL_STRONG_INLINE type Execute_AVX512BW(type a, const type& b) throw() {
			a.native = _mm512_adds_epi16(a.native, b.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(const type& a, const type& b) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_AVX512BW) != 0ull) {
				return Execute_AVX512BW(a, b);
			} else {
				a.lower_half = VectorAdd<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorAdd<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
				return a;
			}
		}
	};

	template<>
	struct VectorAdd<detail::BasicVector<int32_t, 4u>> {
		typedef detail::BasicVector<int32_t, 4u> type;

		static ANVIL_STRONG_INLINE type Execute_SSE2(type a, const type& b) throw() {
			a.native = _mm_add_epi32(a.native, b.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(const type& a, const type& b) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_SSE2) != 0ull) {
				return Execute_SSE2(a, b);
			} else {
				a.lower_half = VectorAdd<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorAdd<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
				return a;
			}
		}
	};

	template<>
	struct VectorAdd<detail::BasicVector<int32_t, 8u>> {
		typedef detail::BasicVector<int32_t, 8u> type;

		static ANVIL_STRONG_INLINE type Execute_AVX2(type a, const type& b) throw() {
			a.native = _mm256_add_epi32(a.native, b.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(const type& a, const type& b) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_AVX2) != 0ull) {
				return Execute_AVX2(a, b);
			} else {
				a.lower_half = VectorAdd<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorAdd<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
				return a;
			}
		}
	};

	template<>
	struct VectorAdd<detail::BasicVector<int32_t, 16u>> {
		typedef detail::BasicVector<int32_t, 16u> type;

		static ANVIL_STRONG_INLINE type Execute_AVX512BW(type a, const type& b) throw() {
			a.native = _mm512_add_epi32(a.native, b.native);
			return a;
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(const type& a, const type& b) throw() {
			// There is a bug in Visual Studio where it will change which instruction sets the code will compile with
			// even when its disabled behind a compile-time check, so it needs to be implemented in seperate functions
			// that will be inlined together
			if constexpr ((instruction_set & ASM_AVX512BW) != 0ull) {
				return Execute_AVX512BW(a, b);
			} else {
				a.lower_half = VectorAdd<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
				a.upper_half = VectorAdd<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
				return a;
			}
		}
	};

#endif

	// Unoptimised vectors

	template<class T, size_t size>
	struct VectorAdd<detail::BasicVector<T, size>> {
		typedef detail::BasicVector<T, size> type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type Execute(type a, const type& b) throw() {
			a.lower_half = VectorAdd<type::lower_t>::Execute<instruction_set>(a.lower_half, b.lower_half);
			a.upper_half = VectorAdd<type::upper_t>::Execute<instruction_set>(a.upper_half, b.upper_half);
			return a;
		}
	};
}}

namespace anvil {

	template<uint64_t instruction_set = ASM_MINIMUM, class T>
	static inline T VectorAdd(const T& a, const T& b) throw() {
		return detail::VectorAdd<T>::Execute<instruction_set>(a, b);
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
