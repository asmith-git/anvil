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

#ifndef ANVIL_MATHS_BIT_ARRAY_HPP
#define ANVIL_MATHS_BIT_ARRAY_HPP

#include <cstdint>
#include "anvil/core/Keywords.hpp"

namespace anvil {
	bool ANVIL_CALL checkBit(const void*, size_t) throw();
	void ANVIL_CALL setBit(void*, size_t) throw();
	void ANVIL_CALL clearBit(void*, size_t) throw();
	void ANVIL_CALL flipBit(void*, size_t) throw();
	bool ANVIL_CALL checkBits(const void*, size_t, size_t) throw();
	void ANVIL_CALL setBits(void*, size_t, size_t) throw();
	void ANVIL_CALL clearBits(void*, size_t, size_t) throw();
	void ANVIL_CALL flipBits(void*, size_t, size_t) throw();
	void ANVIL_CALL copyBits(void*, size_t, const void*, size_t, size_t) throw();
}

#endif