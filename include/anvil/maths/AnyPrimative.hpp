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

#ifndef ANVIL_MATHS_ANY_PRIMATIVE_HPP
#define ANVIL_MATHS_ANY_PRIMATIVE_HPP

#include "anvil/core/Keywords.hpp"
#include "anvil/maths/Type.hpp"

namespace anvil {
	
	/*!
		\brief Container class for primative values
		\detail Supports the following types :
		<ul>
			<li>ANVIL_8U</li>
			<li>ANVIL_8S</li>
			<li>ANVIL_16U</li>
			<li>ANVIL_16S</li>
			<li>ANVIL_32U</li>
			<li>ANVIL_32S</li>
			<li>ANVIL_64U</li>
			<li>ANVIL_64S</li>
			<li>ANVIL_32F</li>
			<li>ANVIL_64F</li>
		</ul>
	*/
	union PrimativeValue {
		uint8_t u8;		//!< Unsigned 8 bit value.
		uint16_t u16;	//!< Unsigned 16 bit value.
		uint32_t u32;	//!< Unsigned 32 bit value.
		uint64_t u64;	//!< Unsigned 64 bit value.
		int8_t s8;		//!< Signed 8 bit value.
		int16_t s16;	//!< Signed 16 bit value.
		int32_t s32;	//!< Signed 32 bit value.
		int64_t s64;	//!< Signed 64 bit value.
		float f32;		//!< Single precision floating point value.
		double f64;		//!< Double precision floating point value.
	};

	/*!
		\brief Dispatch a function call based on a primative type.
		\tparam FU8 Functor type if aType is ANVIL_8U.
		\tparam FU16 Functor type if aType is ANVIL_16U.
		\tparam FU32 Functor type if aType is ANVIL_32U.
		\tparam FU64 Functor type if aType is ANVIL_64U.
		\tparam FS8 Functor type if aType is ANVIL_8S.
		\tparam FS16 Functor type if aType is ANVIL_16S.
		\tparam FS32 Functor type if aType is ANVIL_32S.
		\tparam FS64 Functor type if aType is ANVIL_64S.
		\tparam FF32 Functor type if aType is ANVIL_32F.
		\tparam FF64 Functor type if aType is ANVIL_64F.
		\param aPrimative The container for the primative value.
		\param aType The type contained in aType.
		\param fu8 Functor to call if aType is ANVIL_8U.
		\param fu16 Functor to call if aType is ANVIL_16U.
		\param fu32 Functor to call if aType is ANVIL_32U.
		\param fu64 Functor to call if aType is ANVIL_64U.
		\param fs8 Functor to call if aType is ANVIL_8S.
		\param fs16 Functor to call if aType is ANVIL_16S.
		\param fs32 Functor to call if aType is ANVIL_32S.
		\param fs64 Functor to call if aType is ANVIL_64S.
		\param ff32 Functor to call if aType is ANVIL_32F.
		\param ff64 Functor to call if aType is ANVIL_64F.
		\return True if one of the functors was called, otherwise false (aType is not a primative type).
	*/
	template<class FU8, class FU16, class FU32, class FU64, 
		class FS8, class FS16, class FS32, class FS64, 
		class FF32, class FF64>
	static inline bool ANVIL_CALL dispatchByType(PrimativeValue aPrimative, Type aType, 
	FU8 fu8,  FU16 fu16,  FU32 fu32,  FU64 fu64,  
	FS8 fs8,  FS16 fs16,  FS32 fs32,  FS64 fs64, 
	FF32 ff32,  FF64 ff64) {
		bool returnValue = true;
		switch(aType) {
		case ANVIL_8U:
			fu8(aPrimative.u8);
			break;
		case ANVIL_8S:
			fs8(aPrimative.s8);
			break;
		case ANVIL_16U:
			fu16(aPrimative.u16);
			break;
		case ANVIL_16S:
			fs16(aPrimative.s16);
			break;
		case ANVIL_32U:
			fu32(aPrimative.u32);
			break;
		case ANVIL_32S:
			fs32(aPrimative.s32);
			break;
		case ANVIL_64U:
			fu64(aPrimative.u64);
			break;
		case ANVIL_64S:
			fs64(aPrimative.s64));
			break;
		case ANVIL_32F:
			ff32(aPrimative.f32);
			break;
		case ANVIL_64F:
			ff64(aPrimative.f64);
			break;
		default:
			returnValue = false;
			break;
		}
		return returnValue;
	}
}