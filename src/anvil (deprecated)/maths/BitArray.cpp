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

#include "anvil/maths/BitArray.hpp"

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

	template<class F32, class F8, class F1>
	bool ANVIL_CALL forBits(void* aBits, size_t aOffset, size_t aCount, F32 aF32, F8 aF8, F1 aF1) throw() {
		//! \todo Check for bugs
		const size_t baseIndex = aOffset >> 3;
		uint8_t* base = reinterpret_cast<uint8_t*>(aBits) + baseIndex;
		const size_t misalignment = aOffset & 7;
		if (misalignment) {
			for (size_t i = 0; i < misalignment; ++i) {
				if(aF1(*base, misalignment + i)) return true;
			}

			return checkBits(base + 1, aOffset - misalignment, aCount - misalignment);
		}
		else {
			while (aCount >= 32) {
				if (aF32(*reinterpret_cast<uint32_t*>(base))) return true;
				base += 4;
				aCount -= 32;
			}

			while (aCount >= 8) {
				if (aF8(*base)) return true;
				++base;
				aCount -= 8;
			}

			uint8_t mask = 1;
			for (size_t i = 0; i < aCount; ++i) {
				if (aF1(*base, i)) return true;
				mask <<= 1;
			}

			return false;
		}
	}

	bool ANVIL_CALL checkBits(const void* aBits, size_t aOffset, size_t aCount) throw() {
		return forBits(const_cast<void*>(aBits), aOffset, aCount,
			[](const uint32_t aValue)->bool {
				return aValue != 0;
			},
			[](const uint8_t aValue)->bool {
				return aValue != 0;
			},
			[](const uint8_t aValue, size_t aIndex)->bool {
				return aValue != 0;
			}
		);
	}

	void ANVIL_CALL setBits(void* aBits, size_t aOffset, size_t aCount) throw() {
		forBits(aBits, aOffset, aCount,
			[](uint32_t& aValue)->bool {
				aValue = UINT32_MAX;
				return false;
			},
			[](uint8_t& aValue)->bool {
				aValue = UINT8_MAX;
				return false;
			},
			[](uint8_t& aValue, size_t aIndex)->bool {
				aValue |= 1 << aIndex;
				return false;
			}
		);
	}

	void ANVIL_CALL clearBits(void* aBits, size_t aOffset, size_t aCount) throw() {
		forBits(aBits, aOffset, aCount,
			[](uint32_t& aValue)->bool {
				aValue = 0;
				return false;
			},
			[](uint8_t& aValue)->bool {
				aValue = 0;
				return false;
			},
			[](uint8_t& aValue, size_t aIndex)->bool {
				aValue &= ~(1 << aIndex);
				return false;
			}
		);
	}

	void ANVIL_CALL flipBits(void* aBits, size_t aOffset, size_t aCount) throw() {
		forBits(aBits, aOffset, aCount,
			[](uint32_t& aValue)->bool {
				//! \todo Optimise
				uint32_t mask = 1;
				for (int i = 0; i < 8; ++i) {
					if (aValue & mask) {
						aValue &= ~mask;
					} else {
						aValue |= mask;
					}
					mask <<= 1;
					return false;
				}
			},
			[](uint8_t& aValue)->bool {
				//! \todo Optimise
				uint8_t mask = 1;
				for (int i = 0; i < 8; ++i) {
					if (aValue & mask) {
						aValue &= ~mask;
					} else {
						aValue |= mask;
					}
					mask <<= 1;
					return false;
				}
			},
			[](uint8_t& aValue, size_t aIndex)->bool {
				const uint8_t mask = 1 << aIndex;
				if (aValue & mask) {
					aValue &= ~mask;
				} else {
					aValue |= mask;
				}
				return false;
			}
		);
	}

	void ANVIL_CALL copyBits(void* aDst, size_t aDstOffset, const void* aSrc, size_t aSrcOffset, size_t aCount) throw() {
		uint8_t* const dst = static_cast<uint8_t*>(aDst);
		const uint8_t* const src = static_cast<const uint8_t*>(aSrc);

		if (aDstOffset) {
			//! \todo Implement
		} else {
			forBits(const_cast<void*>(aSrc), aSrcOffset, aCount,
				[dst, src](uint32_t& aValue)->bool {
					const size_t offset = reinterpret_cast<uint8_t*>(&aValue) - src;
					reinterpret_cast<uint32_t*>(dst)[offset] = aValue;
					return false;
				},
				[dst, src](uint8_t& aValue)->bool {
					const size_t offset = reinterpret_cast<uint8_t*>(&aValue) - src;
					dst[offset] = aValue;
					return false;
				},
				[dst, src](uint8_t& aValue, size_t aIndex)->bool {
					const size_t offset = reinterpret_cast<uint8_t*>(&aValue) - src;
					const uint8_t mask = 1 << aIndex;
					dst[offset] &= ~mask;
					dst[offset] |= aValue & mask;
					return false;
				}
			);
		}
	}
}