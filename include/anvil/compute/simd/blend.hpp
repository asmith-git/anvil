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

#include "anvil/compute/simd/And.hpp"
#include "anvil/compute/simd/Or.hpp"
#include "anvil/compute/simd/Xor.hpp"

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
		static ANVIL_STRONG_INLINE void RuntimeMask(T* ifOne, const T* ifZero, uint64_t mask) {
			if ((mask & 1ull) == 0ull) *ifOne = *ifZero;
		}

		template<uint64_t mask>
		static ANVIL_STRONG_INLINE void CompiletimeMask(T* ifOne, const T* ifZero) {
			if constexpr ((mask & 1ull) == 0ull) *ifOne = *ifZero;
		}
	};

	template<class T>
	struct DefaultMasksC<T, 2u> {
		static ANVIL_STRONG_INLINE void RuntimeMask(T* ifOne, const T* ifZero, uint64_t mask) {
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

		static ANVIL_STRONG_INLINE void RuntimeMask(T* ifOne, const T* ifZero, uint64_t mask) {
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
		enum : uint64_t { max_mask = 15ull };

		static ANVIL_STRONG_INLINE void RuntimeMask(T* ifOne, const T* ifZero, uint64_t mask) {
			mask &= max_mask;
			if (mask == max_mask) return;

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
		enum : uint64_t { max_mask = 255ull >> 3ull };

		static ANVIL_STRONG_INLINE void RuntimeMask(T* ifOne, const T* ifZero, uint64_t mask) {
			mask &= max_mask;
			if (mask == max_mask) return;

			if (mask == 0ull) {
				memcpy(ifOne, ifZero, sizeof(T) * 5u);
			} else {
				if ((mask & 1ull) == 0ull) ifOne[0u] = ifZero[0u];
				if ((mask & 2ull) == 0ull) ifOne[1u] = ifZero[1u];
				if ((mask & 4ull) == 0ull) ifOne[2u] = ifZero[2u];
				if ((mask & 8ull) == 0ull) ifOne[3u] = ifZero[3u];
				if ((mask & 16ull) == 0ull) ifOne[4u] = ifZero[4u];
			}
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
		enum : uint64_t { max_mask = 255ull >> 2ull };

		static ANVIL_STRONG_INLINE void RuntimeMask(T* ifOne, const T* ifZero, uint64_t mask) {
			mask &= max_mask;
			if (mask == max_mask) return;

			if (mask == 0ull) {
				memcpy(ifOne, ifZero, sizeof(T) * 6u);
			} else {
				if ((mask & 1ull) == 0ull) ifOne[0u] = ifZero[0u];
				if ((mask & 2ull) == 0ull) ifOne[1u] = ifZero[1u];
				if ((mask & 4ull) == 0ull) ifOne[2u] = ifZero[2u];
				if ((mask & 8ull) == 0ull) ifOne[3u] = ifZero[3u];
				if ((mask & 16ull) == 0ull) ifOne[4u] = ifZero[4u];
				if ((mask & 32ull) == 0ull) ifOne[5u] = ifZero[5u];
			}
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
		enum : uint64_t { max_mask = 255ull >> 1ull };

		static ANVIL_STRONG_INLINE void RuntimeMask(T* ifOne, const T* ifZero, uint64_t mask) {
			mask &= max_mask;
			if (mask == max_mask) return;

			if (mask == 0ull) {
				memcpy(ifOne, ifZero, sizeof(T) * 7u);
			} else {
				if ((mask & 1ull) == 0ull) ifOne[0u] = ifZero[0u];
				if ((mask & 2ull) == 0ull) ifOne[1u] = ifZero[1u];
				if ((mask & 4ull) == 0ull) ifOne[2u] = ifZero[2u];
				if ((mask & 8ull) == 0ull) ifOne[3u] = ifZero[3u];
				if ((mask & 16ull) == 0ull) ifOne[4u] = ifZero[4u];
				if ((mask & 32ull) == 0ull) ifOne[5u] = ifZero[5u];
				if ((mask & 64ull) == 0ull) ifOne[6u] = ifZero[6u];
			}
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
		enum : uint64_t { max_mask = 255ull };

		static ANVIL_STRONG_INLINE void RuntimeMask(T* ifOne, const T* ifZero, uint64_t mask) {
			mask &= max_mask;
			if (mask == max_mask) return;

			if (mask == 0ull) {
				memcpy(ifOne, ifZero, sizeof(T) * 8u);
			} else {
				if ((mask & 1ull) == 0ull) ifOne[0u] = ifZero[0u];
				if ((mask & 2ull) == 0ull) ifOne[1u] = ifZero[1u];
				if ((mask & 4ull) == 0ull) ifOne[2u] = ifZero[2u];
				if ((mask & 8ull) == 0ull) ifOne[3u] = ifZero[3u];
				if ((mask & 16ull) == 0ull) ifOne[4u] = ifZero[4u];
				if ((mask & 32ull) == 0ull) ifOne[5u] = ifZero[5u];
				if ((mask & 64ull) == 0ull) ifOne[6u] = ifZero[6u];
				if ((mask & 128ull) == 0ull) ifOne[7u] = ifZero[7u];
			}
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
			optimised = 0 
		};

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE void RuntimeMask(type& ifOne, const type& ifZero, const uint64_t mask) {
			DefaultMasksC<element_t, size>::RuntimeMask(reinterpret_cast<element_t*>(&ifOne), reinterpret_cast<const element_t*>(&ifZero), mask);
		}

		template<uint64_t instruction_set, uint64_t mask>
		static ANVIL_STRONG_INLINE void CompiletimeMask(type& ifOne, const type& ifZero) {
			DefaultMasksC<element_t, size>::CompiletimeMask<mask>(reinterpret_cast<element_t*>(&ifOne), reinterpret_cast<const element_t*>(&ifZero), mask);
		}
	};

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64

	template<>
	struct VectorBlendNative<__m128, float32_t> {
		typedef __m128 type;
		typedef UnsignedType<float32_t> element_t;
		enum { 
			optimised = 1,
			size = sizeof(type) / sizeof(element_t)
		};

		enum : uint64_t {
			max_mask = 15u
		};

		static ANVIL_STRONG_INLINE void RuntimeMaskAVX512VL(type& ifOne, const type ifZero, const uint64_t mask) {
			ifOne = _mm_mask_blend_ps(static_cast<__mmask8>(mask), ifZero, ifOne);
		}

		template<uint64_t mask>
		static ANVIL_STRONG_INLINE void CompileTimeSSE41(__m128& ifOne, const __m128 ifZero) {
			ifOne = _mm_blend_ps(ifZero, ifOne, static_cast<int>(mask));
		}

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE void RuntimeMask(type& ifOne, const type& ifZero, const uint64_t mask) {
			if constexpr ((instruction_set & ASM_AVX512VL) != 0ull) {
				RuntimeMaskAVX512VL(ifOne, ifZero, mask);
			} else {
				DefaultMasksC<element_t, size>::RuntimeMask(reinterpret_cast<element_t*>(&ifOne), reinterpret_cast<const element_t*>(&ifZero), mask);
			}
		}

		template<uint64_t instruction_set, uint64_t mask>
		static ANVIL_STRONG_INLINE void CompiletimeMask(type& ifOne, const type& ifZero) {
			if constexpr ((mask & max_mask) == max_mask) {
				ifOne = ifZero;
			} else if constexpr ((mask & max_mask) != 0ull) {
				if constexpr ((instruction_set & ASM_SSE41) != 0ull) {
					CompileTimeSSE41<mask>(ifOne, ifZero);
				} else {
					DefaultMasksC<element_t, size>::CompiletimeMask<mask>(reinterpret_cast<element_t*>(&ifOne), reinterpret_cast<const element_t*>(&ifZero));
				}
			}
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

		template<uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type RuntimeMask(type ifOne, const type& ifZero, uint64_t mask) throw() {
			if constexpr (NativeBlend::optimised) {
				NativeBlend::RuntimeMask<instruction_set>(ifOne.native, ifZero.native, mask);
			} else {
				ifOne.lower_half = VectorBlend<type::lower_t>::RuntimeMask<instruction_set>(ifOne.lower_half, ifOne.lower_half, mask);
				ifOne.upper_half = VectorBlend<type::upper_t>::RuntimeMask<instruction_set>(ifOne.upper_half, ifOne.upper_half, mask >> type::lower_size);
			}

			return ifOne;
		}

		template<uint64_t mask, uint64_t instruction_set>
		static ANVIL_STRONG_INLINE type CompiletimeMask(type ifOne, const type& ifZero) throw() {
			if constexpr (NativeBlend::optimised) {
				NativeBlend::CompiletimeMask<mask, instruction_set>(ifOne.native, ifZero.native);
			} else {
				enum : uint64_t { mask2 = mask >> type::lower_size };
				ifOne.lower_half = VectorBlend<type::lower_t>::CompiletimeMask<mask, instruction_set>(ifOne.lower_half, ifOne.lower_half);
				ifOne.upper_half = VectorBlend<type::upper_t>::CompiletimeMask<mask2, instruction_set>(ifOne.upper_half, ifOne.upper_half);
			}

			return ifOne;
		}
	};

#endif

}}

namespace anvil {

	template<uint64_t instruction_set = ASM_MINIMUM, class T>
	static ANVIL_STRONG_INLINE T VectorBlendRuntimeMask(const T& a, const T& b, const uint64_t mask) throw() {
		return detail::VectorBlend<T>::RuntimeMask<instruction_set>(a, b, mask);
	}

	template<uint64_t mask, uint64_t instruction_set = ASM_MINIMUM, class T>
	static ANVIL_STRONG_INLINE T VectorBlendCompiletimeMask(const T& a, const T& b) throw() {
		return detail::VectorBlend<T>::CompiletimeMask<mask, instruction_set>(a, b);
	}
}
#endif