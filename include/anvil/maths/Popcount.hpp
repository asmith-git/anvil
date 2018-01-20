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

#ifndef ANVIL_MATHS_POPCOUNT_HPP
#define ANVIL_MATHS_POPCOUNT_HPP

#include <cstdint>
#include <cstring>
#include "anvil/core/Keywords.hpp"

namespace anvil {
	namespace detail {
		size_t ANVIL_CALL popcount8(const uint8_t aValue) throw();
		size_t ANVIL_CALL popcount16(const uint16_t aValue) throw();
		size_t ANVIL_CALL popcount32(const uint32_t aValue) throw();
		size_t ANVIL_CALL popcount64(const uint64_t aValue) throw();
	}
	size_t ANVIL_CALL popcount(const void*, size_t) throw();

	template<class T>
	size_t ANVIL_CALL popcount(const T aValue);

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<uint8_t>(uint8_t aValue) throw() {
		return detail::popcount8(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<uint16_t>(uint16_t aValue) throw() {
		return detail::popcount16(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<uint32_t>(uint32_t aValue) throw() {
		return detail::popcount32(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<uint64_t>(uint64_t aValue) throw() {
		return detail::popcount64(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<int8_t>(int8_t aValue) throw() {
		union {
			uint8_t u;
			int8_t s;
		};
		s = aValue;
		return detail::popcount8(u);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<int16_t>(int16_t aValue) throw() {
		union {
			uint16_t u;
			int16_t s;
		};
		s = aValue;
		return detail::popcount16(u);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<int32_t>(int32_t aValue) throw() {
		union {
			uint32_t u;
			int32_t s;
		};
		s = aValue;
		return detail::popcount32(u);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<int64_t>(int64_t aValue) throw() {
		union {
			uint64_t u;
			int64_t s;
		};
		s = aValue;
		return detail::popcount64(u);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<float32_t>(float32_t aValue) throw() {
		union {
			uint32_t u;
			float32_t s;
		};
		static_assert(sizeof(float32_t) == sizeof(uint32_t), "Expected 4 byte floats");
		s = aValue;
		return detail::popcount32(u);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<float64_t>(float64_t aValue) throw() {
		union {
			uint64_t u;
			float64_t s;
		};
		static_assert(sizeof(float64_t) == sizeof(uint64_t), "Expected 8 byte doubles");
		s = aValue;
		return detail::popcount64(u);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<bool>(bool aValue) throw() {
		union {
			uint8_t u;
			bool s;
		};
		static_assert(sizeof(bool) == sizeof(uint8_t), "Expected 1 byte bools");
		s = aValue;
		return detail::popcount8(u);
	}

	template<size_t BYTES>
	size_t ANVIL_CALL popcount(const void* const aValue) throw() {
		enum {
			LOOP = BYTES / sizeof(uint32_t),
			REMAINDER = BYTES % sizeof(uint32_t)
		};
		const uint32_t* const ptr32 = static_cast<const uint32_t*>(aValue);
		size_t tmp = 0;
		for (size_t i = 0; i < LOOP; ++i) tmp += detail::popcount32(ptr32[i]);
		if (REMAINDER) {
			uint32_t buffer = 0;
			memcpy(&buffer, ptr32 + LOOP, REMAINDER);
			tmp += detail::popcount32(buffer);
		}
		return tmp;
	}
}

#endif