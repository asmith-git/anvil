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

#include "anvil/maths/Reflection.hpp"

namespace anvil {
	bool ANVIL_CALL checkBit(const void* aBits, size_t aOffset) throw() {
		return reinterpret_cast<const uint8_t*>(aBits)[aOffset >> 3] & (1 << (aOffset & 7));
	}

	void ANVIL_CALL setBit(void* aBits, size_t aOffset) throw() {
		reinterpret_cast<uint8_t*>(aBits)[aOffset >> 3] |= (1 << (aOffset & 7));
	}

	void ANVIL_CALL clearBit(void* aBits, size_t aOffset) throw() {
		reinterpret_cast<uint8_t*>(aBits)[aOffset >> 3] &= ~(1 << (aOffset & 7));
	}

	void ANVIL_CALL flipBit(void* aBits, size_t aOffset) throw() {
		uint8_t* const byte = reinterpret_cast<uint8_t*>(aBits) + (aOffset >> 3);
		const uint8_t mask = 1 << (aOffset & 7);
		*byte = *byte & mask ? *byte & ~mask : *byte | mask;
	}
}