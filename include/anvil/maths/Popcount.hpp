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
		size_t ANVIL_CALL popcount1(const uint8_t aValue) throw();
		size_t ANVIL_CALL popcount2(const uint16_t aValue) throw();
		size_t ANVIL_CALL popcount4(const uint32_t aValue) throw();
		size_t ANVIL_CALL popcount8(const uint64_t aValue) throw();
	}
	size_t ANVIL_CALL popcount(const void*, size_t) throw();

	template<class T>
	size_t ANVIL_CALL popcount(const T aValue);

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<uint8_t>(uint8_t aValue) throw() {
		return detail::popcount1(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<uint16_t>(uint16_t aValue) throw() {
		return detail::popcount2(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<uint32_t>(uint32_t aValue) throw() {
		return detail::popcount4(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<uint64_t>(uint64_t aValue) throw() {
		return detail::popcount8(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<int8_t>(int8_t aValue) throw() {
		uint8_t tmp;
		memcpy(&tmp, &aValue, sizeof(tmp));
		return detail::popcount1(tmp);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<int16_t>(int16_t aValue) throw() {
		uint16_t tmp;
		memcpy(&tmp, &aValue, sizeof(tmp));
		return detail::popcount2(tmp);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<int32_t>(int32_t aValue) throw() {
		uint32_t tmp;
		memcpy(&tmp, &aValue, sizeof(tmp));
		return detail::popcount4(tmp);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<int64_t>(int64_t aValue) throw() {
		uint64_t tmp;
		memcpy(&tmp, &aValue, sizeof(tmp));
		return detail::popcount8(tmp);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<float32_t>(float32_t aValue) throw() {
		uint32_t tmp;
		memcpy(&tmp, &aValue, sizeof(tmp));
		return detail::popcount4(tmp);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<float64_t>(float64_t aValue) throw() {
		uint64_t tmp;
		memcpy(&tmp, &aValue, sizeof(tmp));
		return detail::popcount8(tmp);
	}

	template<>
	ANVIL_STRONG_INLINE size_t ANVIL_CALL popcount<bool>(bool aValue) throw() {
		uint8_t tmp;
		memcpy(&tmp, &aValue, sizeof(tmp));
		return detail::popcount1(tmp);
	}
}

#endif