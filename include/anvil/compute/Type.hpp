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

#ifndef ANVIL_COMPUTE_TYPE_HPP
#define ANVIL_COMPUTE_TYPE_HPP

#include <cstdint>
#include <cmath>
#include <string>
#include "anvil/core/Keywords.hpp"
#include "anvil/core/Popcount.hpp"
#include "anvil/core/LeadingZeroCount.hpp"
#if ANVIL_OPENCV_SUPPORT
#include "opencv2/core/hal/interface.h"
#endif

// Primitive Types

namespace anvil {

#define ANVIL_ENCODE_TYPE_ENUMERATION(TY, BY, CH) (TY | (BY << 2u) | (CH << 4u))

	/*!
	*	\brief Types representable by anvil::Type in a compile time constant format.
	*/
	enum EnumeratedType : uint8_t {
		ANVIL_8UX1 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 0, 0),
		ANVIL_8UX2 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 0, 1),
		ANVIL_8UX3 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 0, 2),
		ANVIL_8UX4 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 0, 3),
		ANVIL_8UX5 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 0, 4),
		ANVIL_8UX6 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 0, 5),
		ANVIL_8UX7 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 0, 6),
		ANVIL_8UX8 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 0, 7),
		ANVIL_8UX9 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 0, 8),
		ANVIL_8UX10 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 0, 9),
		ANVIL_8UX11 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 0, 10),
		ANVIL_8UX12 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 0, 11),
		ANVIL_8UX13 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 0, 12),
		ANVIL_8UX14 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 0, 13),
		ANVIL_8UX15 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 0, 14),
		ANVIL_8UX16 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 0, 15),

		ANVIL_16UX1 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 1, 0),
		ANVIL_16UX2 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 1, 1),
		ANVIL_16UX3 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 1, 2),
		ANVIL_16UX4 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 1, 3),
		ANVIL_16UX5 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 1, 4),
		ANVIL_16UX6 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 1, 5),
		ANVIL_16UX7 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 1, 6),
		ANVIL_16UX8 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 1, 7),
		ANVIL_16UX9 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 2, 8),
		ANVIL_16UX10 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 2, 9),
		ANVIL_16UX11 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 2, 10),
		ANVIL_16UX12 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 2, 11),
		ANVIL_16UX13 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 2, 12),
		ANVIL_16UX14 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 2, 13),
		ANVIL_16UX15 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 2, 14),
		ANVIL_16UX16 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 2, 15),

		ANVIL_32UX1 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 2, 0),
		ANVIL_32UX2 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 2, 1),
		ANVIL_32UX3 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 2, 2),
		ANVIL_32UX4 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 2, 3),
		ANVIL_32UX5 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 2, 4),
		ANVIL_32UX6 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 2, 5),
		ANVIL_32UX7 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 2, 6),
		ANVIL_32UX8 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 2, 7),
		ANVIL_32UX9 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 3, 8),
		ANVIL_32UX10 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 3, 9),
		ANVIL_32UX11 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 3, 10),
		ANVIL_32UX12 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 3, 11),
		ANVIL_32UX13 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 3, 12),
		ANVIL_32UX14 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 3, 13),
		ANVIL_32UX15 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 3, 14),
		ANVIL_32UX16 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 3, 15),

		ANVIL_64UX1 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 3, 0),
		ANVIL_64UX2 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 3, 1),
		ANVIL_64UX3 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 3, 2),
		ANVIL_64UX4 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 3, 3),
		ANVIL_64UX5 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 3, 4),
		ANVIL_64UX6 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 3, 5),
		ANVIL_64UX7 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 3, 6),
		ANVIL_64UX8 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 3, 7),
		ANVIL_64UX9 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 3, 8),
		ANVIL_64UX10 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 3, 9),
		ANVIL_64UX11 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 3, 10),
		ANVIL_64UX12 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 3, 11),
		ANVIL_64UX13 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 3, 12),
		ANVIL_64UX14 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 3, 13),
		ANVIL_64UX15 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 3, 14),
		ANVIL_64UX16 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 3, 15),

		ANVIL_8SX1 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 0, 0),
		ANVIL_8SX2 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 0, 1),
		ANVIL_8SX3 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 0, 2),
		ANVIL_8SX4 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 0, 3),
		ANVIL_8SX5 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 0, 4),
		ANVIL_8SX6 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 0, 5),
		ANVIL_8SX7 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 0, 6),
		ANVIL_8SX8 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 0, 7),
		ANVIL_8SX9 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 0, 8),
		ANVIL_8SX10 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 0, 9),
		ANVIL_8SX11 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 0, 10),
		ANVIL_8SX12 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 0, 11),
		ANVIL_8SX13 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 0, 12),
		ANVIL_8SX14 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 0, 13),
		ANVIL_8SX15 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 0, 14),
		ANVIL_8SX16 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 0, 15),

		ANVIL_16SX1 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 1, 0),
		ANVIL_16SX2 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 1, 1),
		ANVIL_16SX3 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 1, 2),
		ANVIL_16SX4 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 1, 3),
		ANVIL_16SX5 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 1, 4),
		ANVIL_16SX6 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 1, 5),
		ANVIL_16SX7 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 1, 6),
		ANVIL_16SX8 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 1, 7),
		ANVIL_16SX9 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 1, 8),
		ANVIL_16SX10 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 1, 9),
		ANVIL_16SX11 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 1, 10),
		ANVIL_16SX12 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 1, 11),
		ANVIL_16SX13 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 1, 12),
		ANVIL_16SX14 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 1, 13),
		ANVIL_16SX15 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 1, 14),
		ANVIL_16SX16 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 1, 15),

		ANVIL_32SX1 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 2, 0),
		ANVIL_32SX2 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 2, 1),
		ANVIL_32SX3 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 2, 2),
		ANVIL_32SX4 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 2, 3),
		ANVIL_32SX5 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 2, 4),
		ANVIL_32SX6 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 2, 5),
		ANVIL_32SX7 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 2, 6),
		ANVIL_32SX8 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 2, 7),
		ANVIL_32SX9 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 2, 8),
		ANVIL_32SX10 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 2, 9),
		ANVIL_32SX11 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 2, 10),
		ANVIL_32SX12 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 2, 11),
		ANVIL_32SX13 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 2, 12),
		ANVIL_32SX14 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 2, 13),
		ANVIL_32SX15 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 2, 14),
		ANVIL_32SX16 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 2, 15),

		ANVIL_64SX1 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 3, 0),
		ANVIL_64SX2 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 3, 1),
		ANVIL_64SX3 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 3, 2),
		ANVIL_64SX4 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 3, 3),
		ANVIL_64SX5 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 3, 4),
		ANVIL_64SX6 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 3, 5),
		ANVIL_64SX7 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 3, 6),
		ANVIL_64SX8 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 3, 7),
		ANVIL_64SX9 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 3, 8),
		ANVIL_64SX10 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 3, 9),
		ANVIL_64SX11 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 3, 10),
		ANVIL_64SX12 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 3, 11),
		ANVIL_64SX13 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 3, 12),
		ANVIL_64SX14 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 3, 13),
		ANVIL_64SX15 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 3, 14),
		ANVIL_64SX16 =	ANVIL_ENCODE_TYPE_ENUMERATION(1, 3, 15),

		ANVIL_8FX1 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 0, 0),
		ANVIL_8FX2 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 0, 1),
		ANVIL_8FX3 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 0, 2),
		ANVIL_8FX4 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 0, 3),
		ANVIL_8FX5 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 0, 4),
		ANVIL_8FX6 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 0, 5),
		ANVIL_8FX7 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 0, 6),
		ANVIL_8FX8 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 0, 7),
		ANVIL_8FX9 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 0, 8),
		ANVIL_8FX10 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 0, 9),
		ANVIL_8FX11 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 0, 10),
		ANVIL_8FX12 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 0, 11),
		ANVIL_8FX13 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 0, 12),
		ANVIL_8FX14 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 0, 13),
		ANVIL_8FX15 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 0, 14),
		ANVIL_8FX16 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 0, 15),

		ANVIL_16FX1 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 1, 0),
		ANVIL_16FX2 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 1, 1),
		ANVIL_16FX3 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 1, 2),
		ANVIL_16FX4 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 1, 3),
		ANVIL_16FX5 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 1, 4),
		ANVIL_16FX6 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 1, 5),
		ANVIL_16FX7 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 1, 6),
		ANVIL_16FX8 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 1, 7),
		ANVIL_16FX9 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 1, 8),
		ANVIL_16FX10 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 1, 9),
		ANVIL_16FX11 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 1, 10),
		ANVIL_16FX12 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 1, 11),
		ANVIL_16FX13 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 1, 12),
		ANVIL_16FX14 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 1, 13),
		ANVIL_16FX15 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 1, 14),
		ANVIL_16FX16 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 1, 15),

		ANVIL_32FX1 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 2, 0),
		ANVIL_32FX2 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 2, 1),
		ANVIL_32FX3 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 2, 2),
		ANVIL_32FX4 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 2, 3),
		ANVIL_32FX5 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 2, 4),
		ANVIL_32FX6 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 2, 5),
		ANVIL_32FX7 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 2, 6),
		ANVIL_32FX8 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 2, 7),
		ANVIL_32FX9 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 2, 8),
		ANVIL_32FX10 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 2, 9),
		ANVIL_32FX11 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 2, 10),
		ANVIL_32FX12 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 2, 11),
		ANVIL_32FX13 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 2, 12),
		ANVIL_32FX14 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 2, 13),
		ANVIL_32FX15 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 2, 14),
		ANVIL_32FX16 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 2, 15),

		ANVIL_64FX1 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 3, 0),
		ANVIL_64FX2 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 3, 1),
		ANVIL_64FX3 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 3, 2),
		ANVIL_64FX4 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 3, 3),
		ANVIL_64FX5 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 3, 4),
		ANVIL_64FX6 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 3, 5),
		ANVIL_64FX7 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 3, 6),
		ANVIL_64FX8 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 3, 7),
		ANVIL_64FX9 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 3, 8),
		ANVIL_64FX10 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 3, 9),
		ANVIL_64FX11 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 3, 10),
		ANVIL_64FX12 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 3, 11),
		ANVIL_64FX13 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 3, 12),
		ANVIL_64FX14 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 3, 13),
		ANVIL_64FX15 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 3, 14),
		ANVIL_64FX16 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 3, 15),

		// C++ bool type
		ANVIL_8BX1 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 0, 0),
		ANVIL_8BX2 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 0, 1),
		ANVIL_8BX3 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 0, 2),
		ANVIL_8BX4 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 0, 3),
		ANVIL_8BX5 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 0, 4),
		ANVIL_8BX6 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 0, 5),
		ANVIL_8BX7 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 0, 6),
		ANVIL_8BX8 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 0, 7),
		ANVIL_8BX9 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 0, 8),
		ANVIL_8BX10 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 0, 9),
		ANVIL_8BX11 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 0, 10),
		ANVIL_8BX12 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 0, 11),
		ANVIL_8BX13 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 0, 12),
		ANVIL_8BX14 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 0, 13),
		ANVIL_8BX15 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 0, 14),
		ANVIL_8BX16 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 0, 15),

		// Single bit
		ANVIL_1BX1 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 1, 0),
		ANVIL_1BX2 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 1, 1),
		ANVIL_1BX3 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 1, 2),
		ANVIL_1BX4 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 1, 3),
		ANVIL_1BX5 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 1, 4),
		ANVIL_1BX6 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 1, 5),
		ANVIL_1BX7 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 1, 6),
		ANVIL_1BX8 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 1, 7),
		ANVIL_1BX9 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 1, 8),
		ANVIL_1BX10 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 1, 9),
		ANVIL_1BX11 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 1, 10),
		ANVIL_1BX12 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 1, 11),
		ANVIL_1BX13 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 1, 12),
		ANVIL_1BX14 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 1, 13),
		ANVIL_1BX15 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 1, 14),
		ANVIL_1BX16 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 1, 15),

		// C++ char type
		ANVIL_CX1 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 2, 0),
		ANVIL_CX2 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 2, 1),
		ANVIL_CX3 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 2, 2),
		ANVIL_CX4 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 2, 3),
		ANVIL_CX5 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 2, 4),
		ANVIL_CX6 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 2, 5),
		ANVIL_CX7 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 2, 6),
		ANVIL_CX8 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 2, 7),
		ANVIL_CX9 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 2, 8),
		ANVIL_CX10 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 2, 9),
		ANVIL_CX11 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 2, 10),
		ANVIL_CX12 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 2, 11),
		ANVIL_CX13 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 2, 12),
		ANVIL_CX14 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 2, 13),
		ANVIL_CX15 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 2, 14),
		ANVIL_CX16 = ANVIL_ENCODE_TYPE_ENUMERATION(3, 2, 15)
	};

	static_assert(sizeof(bool) == 1, "anvil : Expected bool to be 1 byte");

#undef ANVIL_ENCODE_TYPE_ENUMERATION

	/*!
	*	\class FastShortType
	*	\brief Describes a primative numerical data type.
	*	\detail Data is binary compatible with anvil::EnumeratedType
	*	\author Adam Smith
	*	\date 2017
	*	\see EnumeratedType
	*/
	class FastShortType 
	{
	private:
		#pragma warning( disable : 4201) // Unnamed struct. Should be fine as layout is checked by static asserts
		union {
			struct {
				uint8_t _type : 2;		//!< Determines if this type is unsigned, signed or floating point. \see Representation
				uint8_t _bytes : 2;		//!< The size of a single channel or dimension in bytes. This is encoded as : 0 = 1 byte, 1 = 2 bytes,  3 = 4 bytes, 4 = 8 bytes.
				uint8_t _channels : 4;	//!< The number of channels or dimensions - 1.
			};
			uint8_t _numeric_value;
		};
	public:
		enum {
			MIN_CHANNEL_BYTES = 1,	//!< The minimum size of a single channel or dimension in bytes.
			MAX_CHANNEL_BYTES = 8,	//!< The maximum size of a single channel or dimension in bytes.
			MIN_CHANNELS = 1,		//!< The minimum size of a single channel or dimension in bytes.
			MAX_CHANNELS = 1 << 4,	//!< The minimum size of a single channel or dimension in bytes.
		};

		/*!
		*	\brief Determines how the value is encoded in the type.
		*/
		enum Representation {
			TYPE_UNSIGNED,			//!< The type is an unsigned integer.
			TYPE_SIGNED,			//!< The type is a signed integer.
			TYPE_FLOATING_POINT		//!< The type is floating point.
		};

		/*!
		*	\brief Create a new type.
		*	\param type The type this should be.
		*/
		ANVIL_CONSTEXPR_FN FastShortType(const EnumeratedType type) :
			_numeric_value(type)
		{}

		/*!
		*	\brief Create a new type.
		*	\detail Default type will be ANVIL_8UX1
		*/
		ANVIL_CONSTEXPR_FN FastShortType() :
			FastShortType(ANVIL_8UX1)
		{}

		/*!
		*	\brief Create a new type.
		*	\param type How the value is encoded.
		*	\param bytes The size of the value in bytes.
		*	\param channels The number of channels or dimensions.
		*/
		FastShortType(const Representation type, const size_t bytes, const size_t channels = 1u) {
			SetRepresentation(type);
			SetSizeInBytes(bytes);
			SetNumberOfChannels(channels);
		}

		/*!
		*	\brief Get the enumeration for this type.
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN EnumeratedType GetEnumeratedType() const throw() {
			return static_cast<EnumeratedType>(_numeric_value);
		}

		/*!
		*	\brief Get representation method for this type.
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN Representation GetRepresentation() const throw() {
			return static_cast<Representation>(_type);
		}

		/*!
		*	\brief Return true if this type is an unsigned integer.
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool IsUnsigned() const throw() {
			return _type == TYPE_UNSIGNED;
		}

		/*!
		*	\brief Return true if this type is a signed integer.
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool IsSigned() const throw() {
			return _type == TYPE_SIGNED;
		}

		/*!
		*	\brief Return true if this type is floating point.
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool IsFloatingPoint() const throw() {
			return _type == TYPE_FLOATING_POINT;
		}

		/*!
		*	\brief Return the number of channels or dimensions.
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN size_t GetNumberOfChannels() const throw() {
			return _channels + 1u;
		}

		/*!
		*	\brief Return the size of a single channel or dimension in bytes.
		*	\see Type::GetSizeInBytes
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN size_t GetPrimitiveSizeInBytes() const throw() {
			//return std::pow(2u, _bytes);
			return static_cast<size_t>(1u) << static_cast<size_t>(_bytes);
		}

		/*!
		*	\brief Return the size of a single channel or dimension in bits.
		*	\see Type::GetSizeInBits
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN size_t GetPrimitiveSizeInBits() const throw() {
			return GetPrimitiveSizeInBytes() * 8u;
		}

		/*!
		*	\brief Return the size of the type in bytes.
		*	\see Type::GetPrimitiveSizeInBytes
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN size_t GetSizeInBytes() const throw() {
			return GetPrimitiveSizeInBytes() * GetNumberOfChannels();
		}

		/*!
		*	\brief Return the size of the type in bits.
		*	\see Type::GetPrimitiveSizeInBits
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN size_t GetSizeInBits() const throw() {
			return GetSizeInBytes() * 8u;
		}

		/*!
		*	\brief Set the size of a single channel or dimension in bytes.
		*	\param size The number of bytes. Must be either 1, 2, 4 or 8.
		*/
		ANVIL_STRONG_INLINE void SetSizeInBytes(const size_t size) {
			ANVIL_RUNTIME_ASSERT(popcount(size) == 1 && size <= MAX_CHANNEL_BYTES, "anvil::FastShortType::SetSizeInBytes : " + std::to_string(size) + " bytes is an invalid size (must be 1, 2, 4 or 8 bytes)");
			_bytes = lzcount(size);
		}

		/*!
		*	\brief Set the size of a single channel or dimension in bits.
		*	\param size The number of bytes. Must be either 8, 16, 32 or 64.
		*/
		ANVIL_STRONG_INLINE void SetSizeInBits(const size_t size) {
			SetSizeInBytes(size / 8u);
		}

		/*!
		*	\brief Set how a value is encoded in this type.
		*	\param type The representation method.
		*/
		ANVIL_STRONG_INLINE void SetRepresentation(const Representation type) {
			_type = type;
		}

		/*!
		*	\brief Set the number of channels or dimensions.
		*	\param channel The number of channels or dimensions. Must be between 1 and 8.
		*/
		ANVIL_STRONG_INLINE void SetNumberOfChannels(const size_t channels) {
			ANVIL_RUNTIME_ASSERT(channels >= MIN_CHANNELS && channels <= MAX_CHANNELS, "anvil::FastShortType::SetNumberOfChannels : " + std::to_string(channels) + " is an invalid number of channels (must be 1-16)");
			_channels = channels - 1u;
		}

		/*!
		*	\brief Check if two types are equal.
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool operator==(const FastShortType other) const throw() {
			return _numeric_value == other._numeric_value;
		}

		/*!
		*	\brief Check if two types are not equal.
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool operator!=(const FastShortType other) const throw() {
			return _numeric_value != other._numeric_value;
		}

#if ANVIL_OPENCV_SUPPORT
		static inline EnumeratedType FromOpenCVType(int t) {

			static_assert(CV_8U == 0, "anvil::FastShortType : Expected CV_8U to be 0");
			static_assert(CV_8S == 1, "anvil::FastShortType : Expected CV_8S to be 1");
			static_assert(CV_16U == 2, "anvil::FastShortType : Expected CV_16U to be 2");
			static_assert(CV_16S == 3, "anvil::FastShortType : Expected CV_16S to be 3");
			static_assert(CV_32S == 4, "anvil::FastShortType : Expected CV_32S to be 4");
			static_assert(CV_32F == 5, "anvil::FastShortType : Expected CV_32F to be 5");
			static_assert(CV_64F == 6, "anvil::FastShortType : Expected CV_64F to be 6");
#ifdef CV_16F
			static_assert(CV_16F == 7, "anvil::FastShortType : Expected CV_16F to be 7");
#endif
			static ANVIL_ALIGN(64) ANVIL_CONSTEXPR_VAR const EnumeratedType g_ocv_types[] = {
				ANVIL_8UX1,
				ANVIL_8SX1,
				ANVIL_16UX1,
				ANVIL_16SX1,
				ANVIL_32SX1,
				ANVIL_32FX1,
				ANVIL_64FX1,
				ANVIL_16FX1
			};

			FastShortType anvil_type(g_ocv_types[t & CV_MAT_DEPTH_MASK]);
			anvil_type.SetNumberOfChannels(static_cast<size_t>((t >> CV_CN_SHIFT) + 1));
			return anvil_type.GetEnumeratedType();
		}

		static int ToOpenCVType(EnumeratedType type_enum) {

			static ANVIL_ALIGN(64) ANVIL_CONSTEXPR_VAR const int8_t g_ocv_types[3][4] = {
				{ CV_8U, CV_16U, -1, -1 },
				{ CV_8S, CV_16S, CV_32S, -1 },
#ifdef CV_16F
				{ -1, CV_16F, CV_32F, CV_64F }
#else
				{ -1, -1, CV_32F, CV_64F }
#endif
			};

			FastShortType anvil_type(type_enum);
			const int cv_type = g_ocv_types[anvil_type._type][anvil_type._bytes];
			if(cv_type == -1) throw std::runtime_error("anvil::Type::ToOpenCVType : Data type is not supported by OpenCV");

			const size_t channels = anvil_type.GetNumberOfChannels();
			if(channels > 4u) throw std::runtime_error("anvil::Type::ToOpenCVType : OpenCV only supports up to 4 channels");
			return CV_MAKE_TYPE(cv_type, static_cast<int>(channels));
		}

		ANVIL_STRONG_INLINE int GetOpenCVType() const {
			return ToOpenCVType(GetEnumeratedType());
		}
#endif
	};

	static_assert(sizeof(FastShortType) == 1, "Excpected size of anvil::FastShortType to be 1 byte");


	/*!
	*	\class Type
	*	\brief Describes a primative numerical data type.
	*	\detail Data is binary compatible with anvil::EnumeratedType
	*	\author Adam Smith
	*	\date 2017
	*	\see EnumeratedType
	*/
	class ExtendedShortType
	{
	public:
		enum {
			MIN_CHANNEL_BYTES = 1,	//!< The minimum size of a single channel or dimension in bytes.
			MAX_CHANNEL_BYTES = 8,	//!< The maximum size of a single channel or dimension in bytes.
			MIN_CHANNELS = 1,		//!< The minimum size of a single channel or dimension in bytes.
			MAX_CHANNELS = 1 << 4,	//!< The minimum size of a single channel or dimension in bytes.
		};

		/*!
		*	\brief Determines how the value is encoded in the type.
		*/
		enum Representation {
			TYPE_UNSIGNED,			//!< The type is an unsigned integer.
			TYPE_SIGNED,			//!< The type is a signed integer.
			TYPE_FLOATING_POINT,	//!< The type is floating point.
			TYPE_BOOLEAN,			//!< The type is boolean. (C++ bool type or a single bit).
			TYPE_CHAR,				//!< The type is character (C++ char type).
		};

	private:
		enum {
			EXTENDTED_TYPE = 3
		};

		enum ExtendedMode {
			EXTENDED_MODE_BOOLEAN = 0u,	//!< C++ bool type.
			EXTENDED_MODE_BIT = 1u,		//!< Single bit.
			EXTENDED_MODE_CHAR = 2u,	//!< C++ char type.
			EXTENDED_MODE_UNUSED = 3u	//!< Unused type.
		};

#pragma warning( disable : 4201) // Unnamed struct. Should be fine as layout is checked by static asserts
		union {
			struct {
				uint8_t _type : 2;		//!< Determines if this type is unsigned, signed or floating point. \see Representation. A value of 3 indicated a special extended type.
				uint8_t _bytes : 2;		//!< The size of a single channel or dimension in bytes. This is encoded as : 0 = 1 byte, 1 = 2 bytes,  3 = 4 bytes, 4 = 8 bytes. In extended mode this specifies both the size and representation using ExtendedMode
				uint8_t _channels : 4;	//!< The number of channels or dimensions - 1.
			};
			uint8_t _numeric_value;
		};

		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_VAR bool IsExtendedMode() const throw()
		{
			return _type == EXTENDTED_TYPE;
		}

		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_VAR ExtendedMode GetExtendedMode() const throw()
		{
			return static_cast<ExtendedMode>(_bytes);
		}

		ANVIL_STRONG_INLINE void SetExtendedMode(const ExtendedMode mode) throw()
		{
			_type = EXTENDTED_TYPE;
			_bytes = static_cast<uint8_t>(mode);
		}

	public:

		/*!
		*	\brief Create a new type.
		*	\param type The type this should be.
		*/
		ANVIL_CONSTEXPR_FN ExtendedShortType(const EnumeratedType type) :
			_numeric_value(type)
		{}

		/*!
		*	\brief Create a new type.
		*	\detail Default type will be ANVIL_8UX1
		*/
		ANVIL_CONSTEXPR_FN ExtendedShortType() :
			ExtendedShortType(ANVIL_8UX1)
		{}

		/*!
		*	\brief Create a new type.
		*	\param type How the value is encoded.
		*	\param bytes The size of the value in bytes.
		*	\param channels The number of channels or dimensions.
		*/
		ExtendedShortType(const Representation type, const size_t bytes, const size_t channels = 1u) 
		{
			SetRepresentation(type);
			SetSizeInBytes(bytes);
			SetNumberOfChannels(channels);
		}

		/*!
		*	\brief Get the enumeration for this type.
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN EnumeratedType GetEnumeratedType() const throw() {
			return static_cast<EnumeratedType>(_numeric_value);
		}

		/*!
		*	\brief Get representation method for this type.
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN Representation GetRepresentation() const throw() {
			if (IsExtendedMode())
			{
				return GetExtendedMode() == EXTENDED_MODE_CHAR ? TYPE_CHAR : TYPE_BOOLEAN;
			}
			else
			{
				return static_cast<Representation>(_type);
			}
		}

		/*!
		*	\brief Return true if this type is a single bit
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool IsBit() const throw() {
			return IsExtendedMode() && GetEnumeratedType() == EXTENDED_MODE_BIT;
		}

		/*!
		*	\brief Return true if this type is a boolean (C++ bool type)
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool IsBoolean() const throw() {
			return IsExtendedMode() && GetEnumeratedType() == EXTENDED_MODE_BOOLEAN;
		}

		/*!
		*	\brief Return true if this type is a char (C++ char type)
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool IsChar () const throw() {
			return IsExtendedMode() && GetEnumeratedType() == EXTENDED_MODE_CHAR;
		}

		/*!
		*	\brief Return true if this type is an unsigned integer.
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool IsUnsigned() const throw() {
			return _type == TYPE_UNSIGNED;
		}

		/*!
		*	\brief Return true if this type is a signed integer.
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool IsSigned() const throw() {
			return _type == TYPE_SIGNED;
		}

		/*!
		*	\brief Return true if this type is floating point.
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool IsFloatingPoint() const throw() {
			return _type == TYPE_FLOATING_POINT;
		}

		/*!
		*	\brief Return the number of channels or dimensions.
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN size_t GetNumberOfChannels() const throw() {
			return _channels + 1u;
		}

		/*!
		*	\brief Return the size of a single channel or dimension in bytes.
		*	\see Type::GetSizeInBytes
		*/
		ANVIL_STRONG_INLINE size_t GetPrimitiveSizeInBytes() const throw() {
			if (IsExtendedMode())
			{
				static ANVIL_CONSTEXPR_VAR const uint8_t g_size_in_bytes[] =
				{
					sizeof(bool),
					1u, //! \bug Size of bit rounded up to 1 byte
					sizeof(char)
				};
				return g_size_in_bytes[GetExtendedMode()];
			}
			else
			{
				//return std::pow(2u, _bytes);
				return static_cast<size_t>(1u) << static_cast<size_t>(_bytes);
			}
		}

		/*!
		*	\brief Return the size of a single channel or dimension in bits.
		*	\see Type::GetSizeInBits
		*/
		ANVIL_STRONG_INLINE  size_t GetPrimitiveSizeInBits() const throw() {
			if (IsExtendedMode())
			{
				static ANVIL_CONSTEXPR_VAR const uint8_t g_size_in_bits[] =
				{
					sizeof(bool) * 8u,
					1u,
					sizeof(char) * 8u
				};
				return g_size_in_bits[GetExtendedMode()];
			}
			else
			{
				return GetPrimitiveSizeInBytes() * 8u;
			}
		}

		/*!
		*	\brief Return the size of the type in bits.
		*	\see Type::GetPrimitiveSizeInBits
		*/
		ANVIL_STRONG_INLINE size_t GetSizeInBits() const throw() {
			return GetPrimitiveSizeInBits() * GetNumberOfChannels();
		}

		/*!
		*	\brief Return the size of the type in bytes.
		*	\see Type::GetPrimitiveSizeInBytes
		*/
		ANVIL_STRONG_INLINE size_t GetSizeInBytes() const throw() {
			const size_t size_bits = GetSizeInBits();
			return (size_bits / 8u) + ((size_bits % 8u) == 0u ? 0u : 1u);
		}

		/*!
		*	\brief Set the size of a single channel or dimension in bits.
		*	\param size The number of bytes. Must be either 8, 16, 32 or 64.
		*/
		ANVIL_STRONG_INLINE void SetSizeInBits(const size_t size) {
			if (IsExtendedMode())
			{
				ANVIL_RUNTIME_ASSERT(GetExtendedMode() != EXTENDED_MODE_CHAR, "anvil::ExtendedShortType::SetSizeInBits : Cannot set size of char");
				SetExtendedMode(size == 1u ? EXTENDED_MODE_BIT : EXTENDED_MODE_BOOLEAN);
			}
			else
			{
				const size_t size_bytes = size / 8u;
				ANVIL_RUNTIME_ASSERT(popcount(size_bytes) == 1 && size_bytes <= MAX_CHANNEL_BYTES, "anvil::ExtendedShortType::SetSizeInBits : " + std::to_string(size_bytes) + " bytes is an invalid size (must be 1, 2, 4 or 8 bytes)");
				_bytes = lzcount(size_bytes);
			}
		}

		/*!
		*	\brief Set the size of a single channel or dimension in bytes.
		*	\param size The number of bytes. Must be either 1, 2, 4 or 8.
		*/
		ANVIL_STRONG_INLINE void SetSizeInBytes(const size_t size) {
			SetSizeInBits(size * 8u);
		}

		/*!
		*	\brief Set how a value is encoded in this type.
		*	\param type The representation method.
		*/
		ANVIL_STRONG_INLINE void SetRepresentation(const Representation type) {
			if (type <= TYPE_FLOATING_POINT)
			{
				_type = type;
			}
			else
			{
				SetExtendedMode(type == TYPE_CHAR ? EXTENDED_MODE_CHAR : EXTENDED_MODE_BOOLEAN);
			}
		}

		/*!
		*	\brief Set the number of channels or dimensions.
		*	\param channel The number of channels or dimensions. Must be between 1 and 8.
		*/
		ANVIL_STRONG_INLINE void SetNumberOfChannels(const size_t channels) {
			ANVIL_RUNTIME_ASSERT(channels >= MIN_CHANNELS && channels <= MAX_CHANNELS, "anvil::ExtendedShortType::SetNumberOfChannels : " + std::to_string(channels) + " is an invalid number of channels (must be 1-16)");
			_channels = channels - 1u;
		}

		/*!
		*	\brief Check if two types are equal.
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool operator==(const ExtendedShortType other) const throw() {
			return _numeric_value == other._numeric_value;
		}

		/*!
		*	\brief Check if two types are not equal.
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool operator!=(const ExtendedShortType other) const throw() {
			return _numeric_value != other._numeric_value;
		}

#if ANVIL_OPENCV_SUPPORT
		static inline EnumeratedType FromOpenCVType(int t) {

			static_assert(CV_8U == 0, "anvil::ExtendedShortType : Expected CV_8U to be 0");
			static_assert(CV_8S == 1, "anvil::ExtendedShortType : Expected CV_8S to be 1");
			static_assert(CV_16U == 2, "anvil::ExtendedShortType : Expected CV_16U to be 2");
			static_assert(CV_16S == 3, "anvil::ExtendedShortType : Expected CV_16S to be 3");
			static_assert(CV_32S == 4, "anvil::ExtendedShortType : Expected CV_32S to be 4");
			static_assert(CV_32F == 5, "anvil::ExtendedShortType : Expected CV_32F to be 5");
			static_assert(CV_64F == 6, "anvil::ExtendedShortType : Expected CV_64F to be 6");
#ifdef CV_16F
			static_assert(CV_16F == 7, "anvil::ExtendedShortType : Expected CV_16F to be 7");
#endif
			static ANVIL_ALIGN(64) ANVIL_CONSTEXPR_VAR const EnumeratedType g_ocv_types[] = {
				ANVIL_8UX1,
				ANVIL_8SX1,
				ANVIL_16UX1,
				ANVIL_16SX1,
				ANVIL_32SX1,
				ANVIL_32FX1,
				ANVIL_64FX1,
				ANVIL_16FX1
			};

			ExtendedShortType anvil_type(g_ocv_types[t & CV_MAT_DEPTH_MASK]);
			anvil_type.SetNumberOfChannels(static_cast<size_t>((t >> CV_CN_SHIFT) + 1));
			return anvil_type.GetEnumeratedType();
		}

		static int ToOpenCVType(EnumeratedType type_enum) {
			ExtendedShortType basic_type(type_enum);
			if (basic_type.IsExtendedMode())
			{
				//! \todo Optimise
				const ExtendedMode mode = basic_type.GetExtendedMode();

				switch (mode)
				{
				case EXTENDED_MODE_BOOLEAN:
					return ToOpenCVType(static_cast<EnumeratedType>(FastShortType(FastShortType::TYPE_UNSIGNED, 1u, basic_type.GetNumberOfChannels()).GetEnumeratedType()));
				case EXTENDED_MODE_BIT:
					return ToOpenCVType(static_cast<EnumeratedType>(FastShortType(FastShortType::TYPE_UNSIGNED, 1u, basic_type.GetNumberOfChannels() / 8u).GetEnumeratedType()));
				case EXTENDED_MODE_CHAR:
					return ToOpenCVType(static_cast<EnumeratedType>(FastShortType(FastShortType::TYPE_SIGNED, sizeof(char), basic_type.GetNumberOfChannels()).GetEnumeratedType()));
				};
				
				throw std::runtime_error("anvil::ExtendedShortType::ToOpenCVType : Corrupted exented type");
			}
			else
			{
				static ANVIL_ALIGN(64) ANVIL_CONSTEXPR_VAR const int8_t g_ocv_types[3][4] = {
					{ CV_8U, CV_16U, -1, -1 },
					{ CV_8S, CV_16S, CV_32S, -1 },
	#ifdef CV_16F
					{ -1, CV_16F, CV_32F, CV_64F }
	#else
					{ -1, -1, CV_32F, CV_64F }
	#endif
				};

				ExtendedShortType anvil_type(type_enum);
				const int cv_type = g_ocv_types[anvil_type._type][anvil_type._bytes];
				if (cv_type == -1) throw std::runtime_error("anvil::ExtendedShortType::ToOpenCVType : Data type is not supported by OpenCV");

				const size_t channels = anvil_type.GetNumberOfChannels();
				if (channels > 4u) throw std::runtime_error("anvil::ExtendedShortType::ToOpenCVType : OpenCV only supports up to 4 channels");
				return CV_MAKE_TYPE(cv_type, static_cast<int>(channels));
			}
		}

		ANVIL_STRONG_INLINE int GetOpenCVType() const {
			return ToOpenCVType(GetEnumeratedType());
		}
#endif
	};

	static_assert(sizeof(ExtendedShortType) == 1, "Excpected size of anvil::ExtendedShortType to be 1 byte");

	typedef ExtendedShortType Type;
	typedef ExtendedShortType ShortType;

	/*!
	*	\class LongType
	*	\brief Same as anvil::Type but supports a wider range of values.
	*	\author Adam Smith
	*	\date July 2023
	*	\see EnumeratedType
	*/
	class LongType {
	private:
		#pragma warning( disable : 4201) // Unnamed struct. Should be fine as layout is checked by static asserts
		union {
			struct {
				uint16_t _type : 2;		//!< Determines if this type is unsigned, signed or floating point. \see Representation
				uint16_t _bytes : 5;	//!< The size of a single channel or dimension in bytes - 1.
				uint16_t _channels : 9;	//!< The number of channels or dimensions - 1.
			};
			uint16_t _numeric_value;
		};
	public:
		enum {
			MIN_CHANNEL_BYTES = 1,		//!< The minimum size of a single channel or dimension in bytes.
			MAX_CHANNEL_BYTES = 1 << 5,	//!< The maximum size of a single channel or dimension in bytes.
			MIN_CHANNELS = 1,			//!< The minimum size of a single channel or dimension in bytes.
			MAX_CHANNELS = 1 << 9,		//!< The minimum size of a single channel or dimension in bytes.
		};

		/*!
		*	\brief Determines how the value is encoded in the type.
		*/
		typedef Type::Representation Representation;

		/*!
		*	\brief Create a new type.
		*	\param type The type this should be.
		*/
		 LongType(const ShortType type) :
			_numeric_value(0u)
		{
			 SetRepresentation(type.GetRepresentation());
			 SetSizeInBytes(type.GetPrimitiveSizeInBytes());
			 SetNumberOfChannels(type.GetNumberOfChannels());
		}

		/*!
		*	\brief Create a new type.
		*	\param type The type this should be.
		*/
		LongType(const EnumeratedType type) :
			LongType(ShortType(type))
		{}

		/*!
		*	\brief Create a new type.
		*	\detail Default type will be ANVIL_8UX1
		*/
		LongType() :
			LongType(ANVIL_8UX1)
		{}

		/*!
		*	\brief Create a new type.
		*	\param type How the value is encoded.
		*	\param bytes The size of the value in bytes.
		*	\param channels The number of channels or dimensions.
		*/
		LongType(const Representation type, const size_t bytes, const size_t channels = 1u) {
			SetRepresentation(type);
			SetSizeInBytes(bytes);
			SetNumberOfChannels(channels);
		}

		/*!
		*	\brief Check if this type can be represented by anvil::type.
		*/
		bool IsShortTypeCompatible() const throw() {
			if(GetNumberOfChannels() > Type::MAX_CHANNELS) return false;
			size_t bytes = GetPrimitiveSizeInBytes();
			if (bytes > Type::MAX_CHANNELS || popcount(bytes) != 1) return false;
			return true;
		}

		/*!
		*	\brief Get the enumeration for this type.
		*	\details Will throw exception if type cannot be represented by anvil::Type.
		*/
		ANVIL_STRONG_INLINE ShortType GetShortType() const {
			return ShortType(GetRepresentation(), GetPrimitiveSizeInBytes(), GetNumberOfChannels());
		}

		/*!
		*	\brief Get the enumeration for this type.
		*	\details Will throw exception if type cannot be represented by anvil::Type.
		*/
		ANVIL_STRONG_INLINE EnumeratedType GetEnumeratedType() const {
			return GetShortType().GetEnumeratedType();
		}

		/*!
		*	\brief Get representation method for this type.
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN Representation GetRepresentation() const throw() {
			return static_cast<Representation>(_type);
		}

		/*!
		*	\brief Return true if this type is an unsigned integer.
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool IsUnsigned() const throw() {
			return _type == Type::TYPE_UNSIGNED;
		}

		/*!
		*	\brief Return true if this type is a signed integer.
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool IsSigned() const throw() {
			return _type == Type::TYPE_SIGNED;
		}

		/*!
		*	\brief Return true if this type is floating point.
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool IsFloatingPoint() const throw() {
			return _type == Type::TYPE_FLOATING_POINT;
		}

		/*!
		*	\brief Return the number of channels or dimensions.
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN size_t GetNumberOfChannels() const throw() {
			return _channels + 1u;
		}

		/*!
		*	\brief Return the size of a single channel or dimension in bytes.
		*	\see Type::GetSizeInBytes
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN size_t GetPrimitiveSizeInBytes() const throw() {
			return _bytes + 1u;
		}

		/*!
		*	\brief Return the size of a single channel or dimension in bits.
		*	\see Type::GetSizeInBits
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN size_t GetPrimitiveSizeInBits() const throw() {
			return GetPrimitiveSizeInBytes() * 8u;
		}

		/*!
		*	\brief Return the size of the type in bytes.
		*	\see Type::GetPrimitiveSizeInBytes
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN size_t GetSizeInBytes() const throw() {
			return GetPrimitiveSizeInBytes() * GetNumberOfChannels();
		}

		/*!
		*	\brief Return the size of the type in bits.
		*	\see Type::GetPrimitiveSizeInBits
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN size_t GetSizeInBits() const throw() {
			return GetSizeInBytes() * 8u;
		}

		/*!
		*	\brief Set the size of a single channel or dimension in bytes.
		*	\param size The number of bytes. Must be either 1, 2, 4 or 8.
		*/
		ANVIL_STRONG_INLINE void SetSizeInBytes(const size_t size) {
			ANVIL_RUNTIME_ASSERT(size >= MIN_CHANNEL_BYTES && size <= MAX_CHANNEL_BYTES, "anvil::LongType::SetSizeInBytes : " + std::to_string(size) + " bytes is an invalid size (must be 1 - 32)");
			_bytes = static_cast<uint16_t>(size - 1u);
		}

		/*!
		*	\brief Set the size of a single channel or dimension in bits.
		*	\param size The number of bytes. Must be either 8, 16, 32 or 64.
		*/
		ANVIL_STRONG_INLINE void SetSizeInBits(const size_t size) {
			SetSizeInBytes(size / 8u);
		}

		/*!
		*	\brief Set how a value is encoded in this type.
		*	\param type The representation method.
		*/
		ANVIL_STRONG_INLINE void SetRepresentation(const Representation type) {
			_type = type;
		}

		/*!
		*	\brief Set the number of channels or dimensions.
		*	\param channel The number of channels or dimensions. Must be between 1 and 8.
		*/
		ANVIL_STRONG_INLINE void SetNumberOfChannels(const size_t channels) {
			ANVIL_RUNTIME_ASSERT(channels >= MIN_CHANNELS && channels <= MAX_CHANNELS, "anvil::SetNumberOfChannels::SetNumberOfChannels : " + std::to_string(channels) + " is an invalid number of channels (must be 1-512)");
			_channels = channels - 1u;
		}

		/*!
		*	\brief Check if two types are equal.
		*/
		ANVIL_STRONG_INLINE bool operator==(const LongType other) const throw() {
			return _numeric_value == other._numeric_value;
		}

		/*!
		*	\brief Check if two types are not equal.
		*/
		ANVIL_STRONG_INLINE bool operator!=(const LongType other) const throw() {
			return _numeric_value != other._numeric_value;
		}

#if ANVIL_OPENCV_SUPPORT
		ANVIL_STRONG_INLINE int GetOpenCVType() const {
			return ShortType::ToOpenCVType(GetEnumeratedType());
		}
#endif
	};

	static_assert(sizeof(LongType) == 2, "Excpected size of anvil::LongType to be 1 byte");

	template<class T> struct EnumFromType;
	template<> struct EnumFromType<uint8_t> { static ANVIL_CONSTEXPR_VAR const EnumeratedType value = ANVIL_8UX1; };
	template<> struct EnumFromType<uint16_t> { static ANVIL_CONSTEXPR_VAR const EnumeratedType value = ANVIL_16UX1; };
	template<> struct EnumFromType<uint32_t> { static ANVIL_CONSTEXPR_VAR const EnumeratedType value = ANVIL_32UX1; };
	template<> struct EnumFromType<uint64_t> { static ANVIL_CONSTEXPR_VAR const EnumeratedType value = ANVIL_64UX1; };
	template<> struct EnumFromType<int8_t> { static ANVIL_CONSTEXPR_VAR const EnumeratedType value = ANVIL_8SX1; };
	template<> struct EnumFromType<int16_t> { static ANVIL_CONSTEXPR_VAR const EnumeratedType value = ANVIL_16SX1; };
	template<> struct EnumFromType<int32_t> { static ANVIL_CONSTEXPR_VAR const EnumeratedType value = ANVIL_32SX1; };
	template<> struct EnumFromType<int64_t> { static ANVIL_CONSTEXPR_VAR const EnumeratedType value = ANVIL_64SX1; };
#if ANVIL_F8_SUPPORT
	template<> struct EnumFromType<float8_t> { static ANVIL_CONSTEXPR_VAR const EnumeratedType value = ANVIL_8FX1; };
#endif
#if ANVIL_F16_SUPPORT
	template<> struct EnumFromType<float16_t> { static ANVIL_CONSTEXPR_VAR const EnumeratedType value = ANVIL_16FX1; };
#endif
	template<> struct EnumFromType<float32_t> { static ANVIL_CONSTEXPR_VAR const EnumeratedType value = ANVIL_32FX1; };
	template<> struct EnumFromType<float64_t> { static ANVIL_CONSTEXPR_VAR const EnumeratedType value = ANVIL_64FX1; };

}

#endif