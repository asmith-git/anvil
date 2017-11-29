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

#ifndef ANVIL_MATHS_TYPE_HPP
#define ANVIL_MATHS_TYPE_HPP

#include <cstdint>

namespace anvil {
	enum Type : int8_t {
		MATH_8U,
		MATH_8S,
		MATH_16U,
		MATH_16S,
		MATH_32U,
		MATH_32S,
		MATH_64U,
		MATH_64S,
		MATH_32F,
		MATH_64F
	};

	static constexpr Type CreateType(Type aType, int aChannels) throw() {
		return static_cast<Type>(((aChannels - 1) << 4) | aType);
	}

	static constexpr Type GetType(Type aType) throw() {
		return static_cast<Type>(aType & 15);
	}

	static constexpr int GetChannels(Type aType) throw() {
		return (aType >> 4) + 1;
	}
}

#endif