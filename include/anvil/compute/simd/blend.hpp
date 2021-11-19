//Copyright 2021 Adam G. Smith
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

#ifndef ANVIL_COMPUTE_SIMD_BLEND_HPP
#define ANVIL_COMPUTE_SIMD_BLEND_HPP

#include <type_traits>
#include "anvil/compute/simd/And.hpp"
#include "anvil/compute/simd/Or.hpp"
#include "anvil/compute/simd/Xor.hpp"
#include "anvil/core/Bitset256.hpp"

namespace anvil { namespace detail {

	template<class T, size_t size>
	struct DefaultMasksC {
		enum {
			size_high = size / 2u,
			size_low = size - size_low
		};

		static inline void RuntimeMask(T* ifOne, const T* ifZero, uint64_t mask) {
			//for (size_t i = 0u; i < size; ++i) {
			//	if ((mask & 1ull) == 0ull) ifOne.data[i] = ifZero.data[i];
			//	mask >>= 1ull;
			//}

			DefaultMasksC<T, size_low>::RuntimeMask(ifOne, ifZero, mask);
			DefaultMasksC<T, size_high>::RuntimeMask(ifOne + size_low, ifZero + size_low, mask >> size_low);
		}

		template<uint64_t mask>
		static inline void CompiletimeMask(T* ifOne, const T* ifZero) {
			//RuntimeMask(ifOne, ifZero, mask);

			enum : uint64_t { mask2 = mask >> size_low };
			DefaultMasksC<T, size_low>::CompiletimeMask<mask>(ifOne, ifZero);
			DefaultMasksC<T, size_high>::CompiletimeMask<mask2>(ifOne + size_low, ifZero + size_low);
		}
	};

	template<class T>
	struct DefaultMasksC<T, 1u> {
		enum : uint64_t { max_mask = 1ull };

		static ANVIL_STRONG_INLINE void RuntimeMask(T* ifOne, const T* ifZero, uint64_t mask) {
			ANVIL_ASSUME(mask <= max_mask);
			if ((mask & 1ull) == 0ull) *ifOne = *ifZero;
		}

		template<uint64_t mask>
		static ANVIL_STRONG_INLINE void CompiletimeMask(T* ifOne, const T* ifZero) {
			if constexpr ((mask & 1ull) == 0ull) *ifOne = *ifZero;
		}
	};

	template<class T>
	struct DefaultMasksC<T, 2u> {
		enum : uint64_t { max_mask = (1ull << 2u) - 1ull };

		static ANVIL_STRONG_INLINE void RuntimeMask(T* ifOne, const T* ifZero, uint64_t mask) {
			ANVIL_ASSUME(mask <= max_mask);
			if ((mask & 1ull) == 0ull) ifOne[0u] = ifZero[0u];
			if ((mask & 2ull) == 0ull) ifOne[1u] = ifZero[1u];
		}

		template<uint64_t mask>
		static ANVIL_STRONG_INLINE void CompiletimeMask(T* ifOne, const T* ifZero) {
			if constexpr ((mask & 1ull) == 0ull) ifOne[0u] = ifZero[0u];
			if constexpr ((mask & 2ull) == 0ull) ifOne[1u] = ifZero[1u];
		}
	};

	template<class T>
	struct DefaultMasksC<T, 3u> {
		enum : uint64_t { max_mask = (1ull << 3u) - 1ull };

		static ANVIL_STRONG_INLINE void RuntimeMask(T* ifOne, const T* ifZero, uint64_t mask) {
			ANVIL_ASSUME(mask <= max_mask);
			if ((mask & 1ull) == 0ull) ifOne[0u] = ifZero[0u];
			if ((mask & 2ull) == 0ull) ifOne[1u] = ifZero[1u];
			if ((mask & 4ull) == 0ull) ifOne[2u] = ifZero[2u];
		}

		template<uint64_t mask>
		static ANVIL_STRONG_INLINE void CompiletimeMask(T* ifOne, const T* ifZero) {
			if constexpr ((mask & 1ull) == 0ull) ifOne[0u] = ifZero[0u];
			if constexpr ((mask & 2ull) == 0ull) ifOne[1u] = ifZero[1u];
			if constexpr ((mask & 4ull) == 0ull) ifOne[2u] = ifZero[2u];
		}
	};

	template<class T>
	struct DefaultMasksC<T, 4u> {
		enum : uint64_t { max_mask = (1ull << 4u) - 1ull };

		static ANVIL_STRONG_INLINE void RuntimeMask(T* ifOne, const T* ifZero, uint64_t mask) {
			ANVIL_ASSUME(mask <= max_mask);
			if ((mask & 1ull) == 0ull) ifOne[0u] = ifZero[0u];
			if ((mask & 2ull) == 0ull) ifOne[1u] = ifZero[1u];
			if ((mask & 4ull) == 0ull) ifOne[2u] = ifZero[2u];
			if ((mask & 8ull) == 0ull) ifOne[3u] = ifZero[3u];
		}

		template<uint64_t mask>
		static ANVIL_STRONG_INLINE void CompiletimeMask(T* ifOne, const T* ifZero) {
			if constexpr ((mask & 1ull) == 0ull) ifOne[0u] = ifZero[0u];
			if constexpr ((mask & 2ull) == 0ull) ifOne[1u] = ifZero[1u];
			if constexpr ((mask & 4ull) == 0ull) ifOne[2u] = ifZero[2u];
			if constexpr ((mask & 8ull) == 0ull) ifOne[3u] = ifZero[3u];
		}
	};

	template<class T>
	struct DefaultMasksC<T, 5u> {
		enum : uint64_t { max_mask = (1ull << 5u) - 1ull };

		static ANVIL_STRONG_INLINE void RuntimeMask(T* ifOne, const T* ifZero, uint64_t mask) {
			ANVIL_ASSUME(mask <= max_mask);
			if ((mask & 1ull) == 0ull) ifOne[0u] = ifZero[0u];
			if ((mask & 2ull) == 0ull) ifOne[1u] = ifZero[1u];
			if ((mask & 4ull) == 0ull) ifOne[2u] = ifZero[2u];
			if ((mask & 8ull) == 0ull) ifOne[3u] = ifZero[3u];
			if ((mask & 16ull) == 0ull) ifOne[4u] = ifZero[4u];
		}

		template<uint64_t mask>
		static ANVIL_STRONG_INLINE void CompiletimeMask(T* ifOne, const T* ifZero) {
			if constexpr ((mask & 1ull) == 0ull) ifOne[0u] = ifZero[0u];
			if constexpr ((mask & 2ull) == 0ull) ifOne[1u] = ifZero[1u];
			if constexpr ((mask & 4ull) == 0ull) ifOne[2u] = ifZero[2u];
			if constexpr ((mask & 8ull) == 0ull) ifOne[3u] = ifZero[3u];
			if constexpr ((mask & 16ull) == 0ull) ifOne[4u] = ifZero[4u];
		}
	};

	template<class T>
	struct DefaultMasksC<T, 6u> {
		enum : uint64_t { max_mask = (1ull << 6u) - 1ull };

		static ANVIL_STRONG_INLINE void RuntimeMask(T* ifOne, const T* ifZero, uint64_t mask) {
			ANVIL_ASSUME(mask <= max_mask);
			if ((mask & 1ull) == 0ull) ifOne[0u] = ifZero[0u];
			if ((mask & 2ull) == 0ull) ifOne[1u] = ifZero[1u];
			if ((mask & 4ull) == 0ull) ifOne[2u] = ifZero[2u];
			if ((mask & 8ull) == 0ull) ifOne[3u] = ifZero[3u];
			if ((mask & 16ull) == 0ull) ifOne[4u] = ifZero[4u];
			if ((mask & 32ull) == 0ull) ifOne[5u] = ifZero[5u];
		}

		template<uint64_t mask>
		static ANVIL_STRONG_INLINE void CompiletimeMask(T* ifOne, const T* ifZero) {
			if constexpr ((mask & 1ull) == 0ull) ifOne[0u] = ifZero[0u];
			if constexpr ((mask & 2ull) == 0ull) ifOne[1u] = ifZero[1u];
			if constexpr ((mask & 4ull) == 0ull) ifOne[2u] = ifZero[2u];
			if constexpr ((mask & 8ull) == 0ull) ifOne[3u] = ifZero[3u];
			if constexpr ((mask & 16ull) == 0ull) ifOne[4u] = ifZero[4u];
			if constexpr ((mask & 32ull) == 0ull) ifOne[5u] = ifZero[5u];
		}
	};

	template<class T>
	struct DefaultMasksC<T, 7u> {
		enum : uint64_t { max_mask = (1ull << 7u) - 1ull };

		static ANVIL_STRONG_INLINE void RuntimeMask(T* ifOne, const T* ifZero, uint64_t mask) {
			ANVIL_ASSUME(mask <= max_mask);
			if ((mask & 1ull) == 0ull) ifOne[0u] = ifZero[0u];
			if ((mask & 2ull) == 0ull) ifOne[1u] = ifZero[1u];
			if ((mask & 4ull) == 0ull) ifOne[2u] = ifZero[2u];
			if ((mask & 8ull) == 0ull) ifOne[3u] = ifZero[3u];
			if ((mask & 16ull) == 0ull) ifOne[4u] = ifZero[4u];
			if ((mask & 32ull) == 0ull) ifOne[5u] = ifZero[5u];
			if ((mask & 64ull) == 0ull) ifOne[6u] = ifZero[6u];
		}

		template<uint64_t mask>
		static ANVIL_STRONG_INLINE void CompiletimeMask(T* ifOne, const T* ifZero) {
			if constexpr ((mask & 1ull) == 0ull) ifOne[0u] = ifZero[0u];
			if constexpr ((mask & 2ull) == 0ull) ifOne[1u] = ifZero[1u];
			if constexpr ((mask & 4ull) == 0ull) ifOne[2u] = ifZero[2u];
			if constexpr ((mask & 8ull) == 0ull) ifOne[3u] = ifZero[3u];
			if constexpr ((mask & 16ull) == 0ull) ifOne[4u] = ifZero[4u];
			if constexpr ((mask & 32ull) == 0ull) ifOne[5u] = ifZero[5u];
			if constexpr ((mask & 64ull) == 0ull) ifOne[6u] = ifZero[6u];
		}
	};

	template<class T>
	struct DefaultMasksC<T, 8u> {
		enum : uint64_t { max_mask = (1ull << 8u) - 1ull };

		static ANVIL_STRONG_INLINE void RuntimeMask(T* ifOne, const T* ifZero, uint64_t mask) {
			ANVIL_ASSUME(mask <= max_mask);
			if ((mask & 1ull) == 0ull) ifOne[0u] = ifZero[0u];
			if ((mask & 2ull) == 0ull) ifOne[1u] = ifZero[1u];
			if ((mask & 4ull) == 0ull) ifOne[2u] = ifZero[2u];
			if ((mask & 8ull) == 0ull) ifOne[3u] = ifZero[3u];
			if ((mask & 16ull) == 0ull) ifOne[4u] = ifZero[4u];
			if ((mask & 32ull) == 0ull) ifOne[5u] = ifZero[5u];
			if ((mask & 64ull) == 0ull) ifOne[6u] = ifZero[6u];
			if ((mask & 128ull) == 0ull) ifOne[7u] = ifZero[7u];
		}

		template<uint64_t mask>
		static ANVIL_STRONG_INLINE void CompiletimeMask(T* ifOne, const T* ifZero) {
			if constexpr ((mask & 1ull) == 0ull) ifOne[0u] = ifZero[0u];
			if constexpr ((mask & 2ull) == 0ull) ifOne[1u] = ifZero[1u];
			if constexpr ((mask & 4ull) == 0ull) ifOne[2u] = ifZero[2u];
			if constexpr ((mask & 8ull) == 0ull) ifOne[3u] = ifZero[3u];
			if constexpr ((mask & 16ull) == 0ull) ifOne[4u] = ifZero[4u];
			if constexpr ((mask & 32ull) == 0ull) ifOne[5u] = ifZero[5u];
			if constexpr ((mask & 64ull) == 0ull) ifOne[6u] = ifZero[6u];
			if constexpr ((mask & 128ull) == 0ull) ifOne[7u] = ifZero[7u];
		}
	};

	template<class NATIVE, class T>
	struct VectorBlendNative {
		typedef NATIVE type;
		typedef UnsignedType<T> element_t;
		enum { 
			size = sizeof(NATIVE) / sizeof(T),
			optimised = std::is_fundamental<type>::value ? 1u : 0u
		};

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE void RuntimeMask(type& ifOne, const type& ifZero, const uint64_t mask) {
			DefaultMasksC<element_t, size>::RuntimeMask(reinterpret_cast<element_t*>(&ifOne), reinterpret_cast<const element_t*>(&ifZero), mask);
		}

		template<uint64_t mask, uint64_t instruction_set>
		static ANVIL_STRONG_INLINE void CompiletimeMask(type& ifOne, const type& ifZero) {
			DefaultMasksC<element_t, size>::CompiletimeMask<mask>(reinterpret_cast<element_t*>(&ifOne), reinterpret_cast<const element_t*>(&ifZero), mask);
		}
	};

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64

	template<class T, size_t BYTES>
	struct VectorBlendMaskNative;

	template<>
	struct VectorBlendMaskNative<__m128i, 4u> {
		typedef __m128i type;

		static ANVIL_STRONG_INLINE type Execute(uint64_t mask) {
			const int32_t a = mask & 1u ? -1 : 0;
			const int32_t b = mask & 2u ? -1 : 0;
			const int32_t c = mask & 4u ? -1 : 0;
			const int32_t d = mask & 8u ? -1 : 0;
			return _mm_set_epi32(d, c, b, a);
		}
	};

	template<>
	struct VectorBlendMaskNative<__m128, 4u> {
		typedef __m128 type;

		static ANVIL_STRONG_INLINE type Execute(uint64_t mask) {
			return _mm_castsi128_ps(VectorBlendMaskNative<__m128i, 4u>::Execute(mask));
		}
	};

	template<>
	struct VectorBlendNative<__m128, float32_t> {
		typedef __m128 type;
		typedef UnsignedType<float32_t> element_t;
		enum { 
			optimised = 1,
			size = sizeof(type) / sizeof(element_t)
		};

		enum : uint64_t {
			max_mask = (1ull << size) - 1ull
		};

		static ANVIL_STRONG_INLINE void RuntimeMaskAVX512VL(type& ifOne, const type ifZero, const uint64_t mask) {
			ANVIL_ASSUME(mask <= max_mask);
			ifOne = _mm_mask_blend_ps(static_cast<__mmask8>(mask), ifZero, ifOne);
		}

		static ANVIL_STRONG_INLINE void RuntimeMaskSSE2(type& ifOne, type ifZero, const uint64_t mask) {
			ANVIL_ASSUME(mask <= max_mask);
			const type m = VectorBlendMaskNative<type, size>::Execute(mask);
			ifOne = _mm_and_ps(ifOne, m);
			ifZero = _mm_andnot_ps(m, ifZero);
			ifOne = _mm_or_ps(ifOne, ifZero);
		}

		static ANVIL_STRONG_INLINE void RuntimeMaskSSE41(type& ifOne, const type ifZero, const uint64_t mask) {
			ANVIL_ASSUME(mask <= max_mask);
			ifOne = _mm_blendv_ps(ifZero, ifOne, VectorBlendMaskNative<type, size>::Execute(mask));
		}

		template<uint64_t mask>
		static ANVIL_STRONG_INLINE void CompileTimeSSE(__m128& ifOne, const __m128 ifZero) {
			enum : uint64_t { mask1 = mask & max_mask };

			if constexpr (mask1 == 1ull) {
				ifOne = _mm_move_ss(ifZero, ifOne);
			} else if constexpr (mask1 == 3ull) {
				ifOne = _mm_shuffle_ps(ifOne, ifZero, _MM_SHUFFLE(3, 2, 1, 0));
			} else if constexpr (mask1 == (3ull << 2ull)) {
				ifOne = _mm_shuffle_ps(ifZero, ifOne, _MM_SHUFFLE(3, 2, 1, 0));
			} else {
				DefaultMasksC<element_t, size>::CompiletimeMask<mask1>(reinterpret_cast<element_t*>(&ifOne), reinterpret_cast<const element_t*>(&ifZero));
			}

		}

		template<uint64_t mask>
		static ANVIL_STRONG_INLINE void CompileTimeSSE41(__m128& ifOne, const __m128 ifZero) {
			enum : uint64_t { mask1 = mask & max_mask };
			ifOne = _mm_blend_ps(ifZero, ifOne, static_cast<int>(mask1));
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE void RuntimeMask(type& ifOne, const type& ifZero, const uint64_t mask) {
			if constexpr ((instruction_set & ASM_AVX512VL) != 0ull) {
				RuntimeMaskAVX512VL(ifOne, ifZero, mask);
			} else if constexpr ((instruction_set & ASM_SSE41) != 0ull) {
				RuntimeMaskSSE41(ifOne, ifZero, mask);
			} else if constexpr ((instruction_set & ASM_SSE2) != 0ull) {
				RuntimeMaskSSE2(ifOne, ifZero, mask);
			} else {
				DefaultMasksC<element_t, size>::RuntimeMask(reinterpret_cast<element_t*>(&ifOne), reinterpret_cast<const element_t*>(&ifZero), mask);
			}
		}

		template<uint64_t mask, uint64_t instruction_set>
		static ANVIL_STRONG_INLINE void CompiletimeMask(type& ifOne, const type& ifZero) {
			if constexpr ((instruction_set & ASM_SSE41) != 0ull) {
				CompileTimeSSE41<mask>(ifOne, ifZero);
			} else if constexpr ((instruction_set & ASM_SSE) != 0ull) {
				CompileTimeSSE41<mask>(ifOne, ifZero);
			} else {
				//DefaultMasksC<element_t, size>::CompiletimeMask<mask>(reinterpret_cast<element_t*>(&ifOne), reinterpret_cast<const element_t*>(&ifZero));
				RuntimeMask<instruction_set>(ifOne, ifZero, mask);
			}
		}
	};

	template<>
	struct VectorBlendNative<__m128i, int32_t> {
		typedef __m128i type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE void RuntimeMask(type& ifOne, const type& ifZero, const uint64_t mask) {
			VectorBlendNative<__m128, float32_t>::RuntimeMask<instruction_set>(
				reinterpret_cast<__m128&>(ifOne),
				reinterpret_cast<const __m128&>(ifZero),
				mask
			);
		}

		template<uint64_t mask, uint64_t instruction_set>
		static ANVIL_STRONG_INLINE void CompiletimeMask(type& ifOne, const type& ifZero) {
			VectorBlendNative<__m128, float32_t>::CompiletimeMask<mask, instruction_set>(
				reinterpret_cast<__m128&>(ifOne),
				reinterpret_cast<const __m128&>(ifZero)
			);
		}
	};

	template<>
	struct VectorBlendNative<__m128i, uint32_t> {
		typedef __m128i type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE void RuntimeMask(type& ifOne, const type& ifZero, const uint64_t mask) {
			VectorBlendNative<__m128, float32_t>::RuntimeMask<instruction_set>(
				reinterpret_cast<__m128&>(ifOne),
				reinterpret_cast<const __m128&>(ifZero),
				mask
			);
		}

		template<uint64_t mask, uint64_t instruction_set>
		static ANVIL_STRONG_INLINE void CompiletimeMask(type& ifOne, const type& ifZero) {
			VectorBlendNative<__m128, float32_t>::CompiletimeMask<mask, instruction_set>(
				reinterpret_cast<__m128&>(ifOne),
				reinterpret_cast<const __m128&>(ifZero)
			);
		}
	};

	////

	template<class T>
	struct VectorBlend {
		typedef T type;

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type RuntimeMask(type ifOne, const type& ifZero, uint64_t mask) throw() {
			VectorBlendNative<type, type>::RuntimeMask<instruction_set>(ifOne, ifZero, mask);
			return ifOne;
		}

		template<uint64_t mask, uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type CompiletimeMask(type ifOne, const type& ifZero) throw() {
			VectorBlendNative<type, type>::CompiletimeMask<mask, instruction_set>(ifOne, ifZero);
			return ifOne;
		}
	};

	template<class T, size_t size>
	struct VectorBlend<detail::BasicVector<T, size>> {
		typedef detail::BasicVector<T, size> type;
		typedef VectorBlendNative<typename type::native_t, typename type::type> NativeBlend;

		enum : uint64_t {
			max_mask = size >= 64ull ? UINT64_MAX : (1ull << static_cast<uint64_t>(size)) - 1ull,
			lower_max_mask = (1ull << static_cast<uint64_t>(type::lower_size)) - 1ull,
			upper_max_mask = (1ull << static_cast<uint64_t>(type::upper_size)) - 1ull
		};

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type RuntimeMask(type ifOne, const type& ifZero, uint64_t mask) throw() {

			if constexpr (NativeBlend::optimised) {
				if constexpr (max_mask != UINT64_MAX) mask &= max_mask;
				NativeBlend::RuntimeMask<instruction_set>(ifOne.native, ifZero.native, mask);
			} else {
				const uint64_t lower_mask = mask; // & lower_max_mask;
				const uint64_t upper_mask = (mask >> static_cast<uint64_t>(type::lower_size)); // & upper_max_mask;

				ifOne.lower_half = VectorBlend<type::lower_t>::RuntimeMask<instruction_set>(ifOne.lower_half, ifOne.lower_half, lower_mask);
				ifOne.upper_half = VectorBlend<type::upper_t>::RuntimeMask<instruction_set>(ifOne.upper_half, ifOne.upper_half, upper_mask);
			}

			return ifOne;
		}

		template<uint64_t mask, uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type CompiletimeMask(type ifOne, const type& ifZero) throw() {
			enum : uint64_t {
				mask1 = mask & max_mask,
				lower_mask = mask1 & lower_max_mask,
				upper_mask = (mask1 >> type::lower_size) & upper_max_mask
			};

			if constexpr (mask1 == max_mask) {
				return ifOne;

			} else if constexpr (mask1 == 0ull) {
				return ifZero;

			} else {
				if constexpr (NativeBlend::optimised) {
					NativeBlend::CompiletimeMask<mask1, instruction_set>(ifOne.native, ifZero.native);
				} else {
					if constexpr (lower_mask == lower_max_mask) {
						// Do nothing
					} else if constexpr (lower_mask == 0ull) {
						ifOne.lower_half = ifZero.lower_half;
					} else {
						ifOne.lower_half = VectorBlend<type::lower_t>::CompiletimeMask<lower_mask, instruction_set>(ifOne.lower_half, ifOne.lower_half);
					}

					if constexpr (upper_mask == upper_max_mask) {
						// Do nothing
					} else if constexpr (upper_mask == 0ull) {
						ifOne.upper_half = ifZero.upper_half;
					} else {
						ifOne.upper_half = VectorBlend<type::upper_t>::CompiletimeMask<upper_mask, instruction_set>(ifOne.upper_half, ifOne.upper_half);
					}
				}

				return ifOne;
			}
		}
	};

#endif

}}

namespace anvil {

	template<uint64_t instruction_set = ASM_MINIMUM, class T>
	static inline T VectorBlendRuntimeMask(const T& a, const T& b, const uint64_t mask) throw() {
		return detail::VectorBlend<T>::RuntimeMask<instruction_set>(a, b, mask);
	}

	template<uint64_t mask, uint64_t instruction_set = ASM_MINIMUM, class T>
	static inline T VectorBlendCompiletimeMask(const T& a, const T& b) throw() {
		return detail::VectorBlend<T>::CompiletimeMask<mask, instruction_set>(a, b);
	}

	template<uint64_t instruction_set = ASM_MINIMUM, class T, size_t S>
	static inline detail::BasicVector<T, S> VectorBlendRuntimeMask(const detail::BasicVector<T, S>& a, const detail::BasicVector<T, S>& b, const Bitfield128 mask) throw() {
		if constexpr (S <= 64u) {
			return VectorBlendRuntimeMask<instruction_set>(a, b, mask.low);
		} else if constexpr (S == 128u) {
			return  detail::BasicVector<T, S>(
				VectorBlendRuntimeMask<instruction_set>(a.lower_half, b.lower_half, mask.low),
				VectorBlendRuntimeMask<instruction_set>(a.upper_half, b.upper_half, mask.high)
			);
		} else {
			enum { S2 = S - 64u };

			detail::BasicVector<T, S> tmp;
			const detail::BasicVector<T, 64u>& aLow = *reinterpret_cast<const detail::BasicVector<T, 64u>*>(a.data);
			const detail::BasicVector<T, 64u>& bLow = *reinterpret_cast<const detail::BasicVector<T, 64u>*>(b.data);
			detail::BasicVector<T, 64u>& tmpLow = *reinterpret_cast<detail::BasicVector<T, 64u>*>(tmp.data);
			const detail::BasicVector<T, S2>& aHigh = *reinterpret_cast<const detail::BasicVector<T, S2>*>(a.data + 64u);
			const detail::BasicVector<T, S2>& bHigh = *reinterpret_cast<const detail::BasicVector<T, S2>*>(b.data + 64u);
			detail::BasicVector<T, S2>& tmpHigh = *reinterpret_cast<detail::BasicVector<T, S2>*>(tmp.data + 64u);

			tmpLow = VectorBlendRuntimeMask<instruction_set>(aLow, bLow, mask.low);
			tmpHigh = VectorBlendRuntimeMask<instruction_set>(aHigh, bHigh, mask.high);
			return tmp;
		}
	}

	template<uint64_t instruction_set = ASM_MINIMUM, class T, size_t S>
	static inline detail::BasicVector<T, S> VectorBlendRuntimeMask(const detail::BasicVector<T, S>& a, const detail::BasicVector<T, S>& b, const Bitfield256 mask) throw() {
		if constexpr (S <= 128u) {
			return VectorBlendRuntimeMask<instruction_set>(a, b, mask.low);
		} else if constexpr (S == 256u) {
			return  detail::BasicVector<T, S>(
				VectorBlendRuntimeMask<instruction_set>(a.lower_half, b.lower_half, mask.low),
				VectorBlendRuntimeMask<instruction_set>(a.upper_half, b.upper_half, mask.high)
			);
		} else {
			enum { S2 = S - 128u };

			detail::BasicVector<T, S> tmp;
			const detail::BasicVector<T, 128u>& aLow = *reinterpret_cast<const detail::BasicVector<T, 128u>*>(a.data);
			const detail::BasicVector<T, 128u>& bLow = *reinterpret_cast<const detail::BasicVector<T, 128u>*>(b.data);
			detail::BasicVector<T, 128u>& tmpLow = *reinterpret_cast<detail::BasicVector<T, 128u>*>(tmp.data);
			const detail::BasicVector<T, S2>& aHigh = *reinterpret_cast<const detail::BasicVector<T, S2>*>(a.data + 128u);
			const detail::BasicVector<T, S2>& bHigh = *reinterpret_cast<const detail::BasicVector<T, S2>*>(b.data + 128u);
			detail::BasicVector<T, S2>& tmpHigh = *reinterpret_cast<detail::BasicVector<T, S2>*>(tmp.data + 128u);

			tmpLow = VectorBlendRuntimeMask<instruction_set>(aLow, bLow, mask.low);
			tmpHigh = VectorBlendRuntimeMask<instruction_set>(aHigh, bHigh, mask.high);
			return tmp;
		}
	}
}
#endif