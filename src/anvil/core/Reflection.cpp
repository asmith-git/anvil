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

#include "anvil/core/Reflection.hpp"

namespace anvil {

	void ANVIL_CALL reflect(void* aDst, const void* aSrc, size_t aBytes) throw() {
		const uint8_t* src = static_cast<const uint8_t*>(aSrc);
		const uint8_t* const end = src + aBytes;
		uint8_t* dst = static_cast<uint8_t*>(aDst) + aBytes - 1;
		while(src != end) {
			*dst = reflect(*src);
			++src;
			--dst;
		}
	}

}