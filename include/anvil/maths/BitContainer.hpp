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

#ifndef ANVIL_MATHS_BIT_CONTAINER_HPP
#define ANVIL_MATHS_BIT_CONTAINER_HPP

#include <cstdint>
#include "anvil/core/Constants.hpp"
#include "anvil/maths/vector.hpp"

namespace anvil {
	//template<int BITS, class ENABLE = void>
	//struct BitContainer;

	//template<int BITS>
	//struct BitContainer<BITS, typename std::enable_if<
	//	ConstantOperation<int, BITS, 0>::gt && ConstantOperation<int, BITS, 8>::le
	//>::type> {
	//	typename uint8_t type;
	//};

	//template<int BITS>
	//struct BitContainer<BITS, typename std::enable_if<
	//	ConstantOperation<int, BITS, 8>::gt && ConstantOperation<int, BITS, 16>::le
	//>::type> {
	//	typename uint16_t type;
	//};

	//template<int BITS>
	//struct BitContainer<BITS, typename std::enable_if<
	//	ConstantOperation<int, BITS, 16>::gt && ConstantOperation<int, BITS, 32>::le
	//>::type> {
	//	typename uint32_t type;
	//};

	//template<int BITS>
	//struct BitContainer<BITS, typename std::enable_if<
	//	ConstantOperation<int, BITS, 32>::gt && ConstantOperation<int, BITS, 64>::le
	//>::type> {
	//	typename uint64_t type;
	//};
}

#endif