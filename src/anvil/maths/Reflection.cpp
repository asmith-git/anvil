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
	ANVIL_CONSTEXPR_VAR const uint8_t gReflectionLookup[256]{
		0,128,64,192,32,160,96,224,16,144,80,208,48,176,112,240,
		8,136,72,200,40,168,104,232,24,152,88,216,56,184,120,248,
		4,132,68,196,36,164,100,228,20,148,84,212,52,180,116,244,
		12,140,76,204,44,172,108,236,28,156,92,220,60,188,124,252,
		2,130,66,194,34,162,98,226,18,146,82,210,50,178,114,242,
		10,138,74,202,42,170,106,234,26,154,90,218,58,186,122,250,
		6,134,70,198,38,166,102,230,22,150,86,214,54,182,118,246,
		14,142,78,206,46,174,110,238,30,158,94,222,62,190,126,254,
		1,129,65,193,33,161,97,225,17,145,81,209,49,177,113,241,
		9,137,73,201,41,169,105,233,25,153,89,217,57,185,121,249,
		5,133,69,197,37,165,101,229,21,149,85,213,53,181,117,245,
		13,141,77,205,45,173,109,237,29,157,93,221,61,189,125,253,
		3,131,67,195,35,163,99,227,19,147,83,211,51,179,115,243,
		11,139,75,203,43,171,107,235,27,155,91,219,59,187,123,251,
		7,135,71,199,39,167,103,231,23,151,87,215,55,183,119,247,
		15,143,79,207,47,175,111,239,31,159,95,223,63,191,127,255
	};

	uint8_t ANVIL_CALL reflect(const uint8_t aValue) throw() {
		return gReflectionLookup[aValue];
	}

	uint16_t ANVIL_CALL reflect(const uint16_t aValue) throw() {
		const uint8_t* const src = reinterpret_cast<const uint8_t*>(&aValue);
		const uint8_t dst[2] = {
			gReflectionLookup[src[1]],
			gReflectionLookup[src[0]]
		};
		return *reinterpret_cast<const uint16_t*>(dst);
	}

	uint32_t ANVIL_CALL reflect(const uint32_t aValue) throw() {
		const uint8_t* const src = reinterpret_cast<const uint8_t*>(&aValue);
		const uint8_t dst[4] = {
			gReflectionLookup[src[3]],
			gReflectionLookup[src[2]],
			gReflectionLookup[src[1]],
			gReflectionLookup[src[0]]
		};
		return *reinterpret_cast<const uint32_t*>(dst);
	}

	uint64_t ANVIL_CALL reflect(const uint64_t aValue) throw() {
		const uint8_t* const src = reinterpret_cast<const uint8_t*>(&aValue);
		const uint8_t dst[8] = {
			gReflectionLookup[src[7]],
			gReflectionLookup[src[6]],
			gReflectionLookup[src[5]],
			gReflectionLookup[src[4]],
			gReflectionLookup[src[3]],
			gReflectionLookup[src[2]],
			gReflectionLookup[src[1]],
			gReflectionLookup[src[0]]
		};
		return *reinterpret_cast<const uint64_t*>(dst);
	}

	int8_t ANVIL_CALL reflect(const int8_t aValue) throw() {
		const uint8_t* const src = reinterpret_cast<const uint8_t*>(&aValue);
		const uint8_t dst = gReflectionLookup[*src];
		return *reinterpret_cast<const int8_t*>(dst);
	}

	int16_t ANVIL_CALL reflect(const int16_t aValue) throw() {
		const uint8_t* const src = reinterpret_cast<const uint8_t*>(&aValue);
		const uint8_t dst[2] = {
			gReflectionLookup[src[1]],
			gReflectionLookup[src[0]]
		};
		return *reinterpret_cast<const int16_t*>(dst);
	}

	int32_t ANVIL_CALL reflect(const int32_t aValue) throw() {
		const uint8_t* const src = reinterpret_cast<const uint8_t*>(&aValue);
		const uint8_t dst[4] = {
			gReflectionLookup[src[3]],
			gReflectionLookup[src[2]],
			gReflectionLookup[src[1]],
			gReflectionLookup[src[0]]
		};
		return *reinterpret_cast<const int32_t*>(dst);
	}

	int64_t ANVIL_CALL reflect(const int64_t aValue) throw() {
		const uint8_t* const src = reinterpret_cast<const uint8_t*>(&aValue);
		const uint8_t dst[8] = {
			gReflectionLookup[src[7]],
			gReflectionLookup[src[6]],
			gReflectionLookup[src[5]],
			gReflectionLookup[src[4]],
			gReflectionLookup[src[3]],
			gReflectionLookup[src[2]],
			gReflectionLookup[src[1]],
			gReflectionLookup[src[0]]
		};
		return *reinterpret_cast<const int64_t*>(dst);
	}

	void ANVIL_CALL reflect(const void* aSrc, void* aDst, size_t aBytes) throw() {
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