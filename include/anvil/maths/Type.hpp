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
		ANVIL_8U,
		ANVIL_8S,
		ANVIL_16U,
		ANVIL_16S,
		ANVIL_32U,
		ANVIL_32S,
		ANVIL_64U,
		ANVIL_64S,
		ANVIL_32F,
		ANVIL_64F
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

	#define ANVIL_8UC1 anvil::CreateType(anvil::ANVIL_8U, 1)
	#define ANVIL_8UC2 anvil::CreateType(anvil::ANVIL_8U, 2)
	#define ANVIL_8UC3 anvil::CreateType(anvil::ANVIL_8U, 3)
	#define ANVIL_8UC4 anvil::CreateType(anvil::ANVIL_8U, 4)
	#define ANVIL_8SC1 anvil::CreateType(anvil::ANVIL_8S, 1)
	#define ANVIL_8SC2 anvil::CreateType(anvil::ANVIL_8S, 2)
	#define ANVIL_8SC3 anvil::CreateType(anvil::ANVIL_8S, 3)
	#define ANVIL_8SC4 anvil::CreateType(anvil::ANVIL_8S, 4)
	#define ANVIL_16UC1 anvil::CreateType(anvil::ANVIL_16U, 1)
	#define ANVIL_16UC2 anvil::CreateType(anvil::ANVIL_16U, 2)
	#define ANVIL_16UC3 anvil::CreateType(anvil::ANVIL_16U, 3)
	#define ANVIL_16UC4 anvil::CreateType(anvil::ANVIL_16U, 4)
	#define ANVIL_16SC1 anvil::CreateType(anvil::ANVIL_16S, 1)
	#define ANVIL_16SC2 anvil::CreateType(anvil::ANVIL_16S, 2)
	#define ANVIL_16SC3 anvil::CreateType(anvil::ANVIL_16S, 3)
	#define ANVIL_16SC4 anvil::CreateType(anvil::ANVIL_16S, 4)
	#define ANVIL_32UC1 anvil::CreateType(anvil::ANVIL_32U, 1)
	#define ANVIL_32UC2 anvil::CreateType(anvil::ANVIL_32U, 2)
	#define ANVIL_32UC3 anvil::CreateType(anvil::ANVIL_32U, 3)
	#define ANVIL_32UC4 anvil::CreateType(anvil::ANVIL_32U, 4)
	#define ANVIL_32SC1 anvil::CreateType(anvil::ANVIL_32S, 1)
	#define ANVIL_32SC2 anvil::CreateType(anvil::ANVIL_32S, 2)
	#define ANVIL_32SC3 anvil::CreateType(anvil::ANVIL_32S, 3)
	#define ANVIL_32SC4 anvil::CreateType(anvil::ANVIL_32S, 4)
	#define ANVIL_64UC1 anvil::CreateType(anvil::ANVIL_64U, 1)
	#define ANVIL_64UC2 anvil::CreateType(anvil::ANVIL_64U, 2)
	#define ANVIL_64UC3 anvil::CreateType(anvil::ANVIL_64U, 3)
	#define ANVIL_64UC4 anvil::CreateType(anvil::ANVIL_64U, 4)
	#define ANVIL_64SC1 anvil::CreateType(anvil::ANVIL_64S, 1)
	#define ANVIL_64SC2 anvil::CreateType(anvil::ANVIL_64S, 2)
	#define ANVIL_64SC3 anvil::CreateType(anvil::ANVIL_64S, 3)
	#define ANVIL_64SC4 anvil::CreateType(anvil::ANVIL_64S, 4)
	#define ANVIL_32FC1 anvil::CreateType(anvil::ANVIL_32F, 1)
	#define ANVIL_32FC2 anvil::CreateType(anvil::ANVIL_32F, 2)
	#define ANVIL_32FC3 anvil::CreateType(anvil::ANVIL_32F, 3)
	#define ANVIL_32FC4 anvil::CreateType(anvil::ANVIL_32F, 4)
	#define ANVIL_64FC1 anvil::CreateType(anvil::ANVIL_64F, 1)
	#define ANVIL_64FC2 anvil::CreateType(anvil::ANVIL_64F, 2)
	#define ANVIL_64FC3 anvil::CreateType(anvil::ANVIL_64F, 3)
	#define ANVIL_64FC4 anvil::CreateType(anvil::ANVIL_64F, 4)
}

#endif