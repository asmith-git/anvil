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

/*
	Reflect reverses the order of bits
*/

#include "anvil/core/Keywords.hpp"

namespace anvil {
	namespace detail {
		uint32_t ANVIL_CALL reflect1(const uint32_t aValue) throw();
		uint32_t ANVIL_CALL reflect2(const uint32_t aValue) throw();
		uint32_t ANVIL_CALL reflect4(const uint32_t aValue) throw();
		uint64_t ANVIL_CALL reflect8(const uint64_t aValue) throw();
	}

	void ANVIL_CALL reflect(void*, const void*, size_t) throw();

	ANVIL_STRONG_INLINE uint8_t ANVIL_CALL reflect(uint8_t aValue) throw() {
		return detail::reflect1(aValue);
	}

	ANVIL_STRONG_INLINE uint16_t ANVIL_CALL reflect(uint16_t aValue) throw() {
		return detail::reflect2(aValue);
	}

	ANVIL_STRONG_INLINE uint32_t ANVIL_CALL reflect(uint32_t aValue) throw() {
		return detail::reflect4(aValue);
	}

	ANVIL_STRONG_INLINE uint64_t ANVIL_CALL reflect(uint64_t aValue) throw() {
		return detail::reflect8(aValue);
	}

	ANVIL_STRONG_INLINE int8_t ANVIL_CALL reflect(int8_t aValue) throw() {
		union {
			uint8_t u;
			int8_t s;
		};
		s = aValue;
		u = detail::reflect1(u);
		return s;
	}

	ANVIL_STRONG_INLINE int16_t ANVIL_CALL reflect(int16_t aValue) throw() {
		union {
			uint16_t u;
			int16_t s;
		};
		s = aValue;
		u = detail::reflect2(u);
		return s;
	}

	ANVIL_STRONG_INLINE int32_t ANVIL_CALL reflect(int32_t aValue) throw() {
		union {
			uint32_t u;
			int32_t s;
		};
		s = aValue;
		u = detail::reflect4(u);
		return s;
	}

	ANVIL_STRONG_INLINE int64_t ANVIL_CALL reflect(int64_t aValue) throw() {
		union {
			uint64_t u;
			int64_t s;
		};
		s = aValue;
		u = detail::reflect8(u);
		return s;
	}

}

#endif