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

#ifndef ANVIL_MATHS_REFLECTION_HPP
#define ANVIL_MATHS_REFLECTION_HPP

#include <cstdint>
#include "anvil/core/Keywords.hpp"

namespace anvil {

	uint8_t ANVIL_CALL reflect(const uint8_t aValue) throw();
	uint16_t ANVIL_CALL reflect(const uint16_t aValue) throw();
	uint32_t ANVIL_CALL reflect(const uint32_t aValue) throw();
	uint64_t ANVIL_CALL reflect(const uint64_t aValue) throw();
	int8_t ANVIL_CALL reflect(const int8_t aValue) throw();
	int16_t ANVIL_CALL reflect(const int16_t aValue) throw();
	int32_t ANVIL_CALL reflect(const int32_t aValue) throw();
	int64_t ANVIL_CALL reflect(const int64_t aValue) throw();
	void ANVIL_CALL reflect(const void*, void*, size_t) throw();

}

#endif