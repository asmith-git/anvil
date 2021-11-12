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

#ifndef ANVIL_CORE_REFLECTION_HPP
#define ANVIL_CORE_REFLECTION_HPP

#include <cstring>
#include "anvil/core/Keywords.hpp"

namespace anvil {
	namespace detail {
		uint8_t ANVIL_CALL reflect1(const uint8_t aValue) throw();
		uint16_t ANVIL_CALL reflect2(const uint16_t aValue) throw();
		uint32_t ANVIL_CALL reflect4(const uint32_t aValue) throw();
		uint64_t ANVIL_CALL reflect8(const uint64_t aValue) throw();
	}

	void ANVIL_CALL reflect(void*, const void*, size_t) throw();

	template<class T>
	T ANVIL_CALL reflect(const T aValue);

	template<>
	ANVIL_STRONG_INLINE uint8_t ANVIL_CALL reflect<uint8_t>(uint8_t aValue) throw() {
		return detail::reflect1(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE uint16_t ANVIL_CALL reflect<uint16_t>(uint16_t aValue) throw() {
		return detail::reflect2(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE uint32_t ANVIL_CALL reflect<uint32_t>(uint32_t aValue) throw() {
		return detail::reflect4(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE uint64_t ANVIL_CALL reflect<uint64_t>(uint64_t aValue) throw() {
		return detail::reflect8(aValue);
	}

	template<>
	ANVIL_STRONG_INLINE int8_t ANVIL_CALL reflect<int8_t>(int8_t aValue) throw() {
		uint8_t tmp;
		memcpy(&tmp, &aValue, sizeof(tmp));
		tmp = detail::reflect1(tmp);
		memcpy(&aValue, &tmp, sizeof(tmp));
		return aValue;
	}

	template<>
	ANVIL_STRONG_INLINE int16_t ANVIL_CALL reflect<int16_t>(int16_t aValue) throw() {
		uint16_t tmp;
		memcpy(&tmp, &aValue, sizeof(tmp));
		tmp = detail::reflect2(tmp);
		memcpy(&aValue, &tmp, sizeof(tmp));
		return aValue;
	}

	template<>
	ANVIL_STRONG_INLINE int32_t ANVIL_CALL reflect<int32_t>(int32_t aValue) throw() {
		uint32_t tmp;
		memcpy(&tmp, &aValue, sizeof(tmp));
		tmp = detail::reflect4(tmp);
		memcpy(&aValue, &tmp, sizeof(tmp));
		return aValue;
	}

	template<>
	ANVIL_STRONG_INLINE int64_t ANVIL_CALL reflect<int64_t>(int64_t aValue) throw() {
		uint64_t tmp;
		memcpy(&tmp, &aValue, sizeof(tmp));
		tmp = detail::reflect8(tmp);
		memcpy(&aValue, &tmp, sizeof(tmp));
		return aValue;
	}

	template<>
	ANVIL_STRONG_INLINE float32_t ANVIL_CALL reflect<float32_t>(float32_t aValue) throw() {
		uint32_t tmp;
		memcpy(&tmp, &aValue, sizeof(tmp));
		tmp = detail::reflect4(tmp);
		memcpy(&aValue, &tmp, sizeof(tmp));
		return aValue;
	}

	template<>
	ANVIL_STRONG_INLINE float64_t ANVIL_CALL reflect<float64_t>(float64_t aValue) throw() {
		uint64_t tmp;
		memcpy(&tmp, &aValue, sizeof(tmp));
		tmp = detail::reflect8(tmp);
		memcpy(&aValue, &tmp, sizeof(tmp));
		return aValue;
	}

	template<>
	ANVIL_STRONG_INLINE bool ANVIL_CALL reflect<bool>(bool aValue) throw() {
		uint8_t tmp;
		memcpy(&tmp, &aValue, sizeof(tmp));
		tmp = detail::reflect1(tmp);
		memcpy(&aValue, &tmp, sizeof(tmp));
		return aValue;
	}

}

#endif