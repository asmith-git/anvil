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
	union PrimativeValueStoreage {
		uint8_t u8;		//!< Unsigned 8 bit value.
		uint16_t u16;	//!< Unsigned 16 bit value.
		uint32_t u32;	//!< Unsigned 32 bit value.
		uint64_t u64;	//!< Unsigned 64 bit value.
		int8_t s8;		//!< Signed 8 bit value.
		int16_t s16;	//!< Signed 16 bit value.
		int32_t s32;	//!< Signed 32 bit value.
		int64_t s64;	//!< Signed 64 bit value.
		float32_t f32;	//!< Single precision floating point value.
		float64_t f64;	//!< Double precision floating point value.
		bool b8;	    //!< Boolean value.

		ANVIL_CALL PrimativeValueStoreage() throw() : u64(0) {}
		ANVIL_CALL PrimativeValueStoreage(uint8_t aValue) throw() : u8(aValue) {}
		ANVIL_CALL PrimativeValueStoreage(uint16_t aValue) throw() : u16(aValue) {}
		ANVIL_CALL PrimativeValueStoreage(uint32_t aValue) throw() : u32(aValue) {}
		ANVIL_CALL PrimativeValueStoreage(uint64_t aValue) throw() : u64(aValue) {}
		ANVIL_CALL PrimativeValueStoreage(int8_t aValue) throw() : s8(aValue) {}
		ANVIL_CALL PrimativeValueStoreage(int16_t aValue) throw() : s16(aValue) {}
		ANVIL_CALL PrimativeValueStoreage(int32_t aValue) throw() : s32(aValue) {}
		ANVIL_CALL PrimativeValueStoreage(int64_t aValue) throw() : s64(aValue) {}
		ANVIL_CALL PrimativeValueStoreage(float32_t aValue) throw() : f32(aValue) {}
		ANVIL_CALL PrimativeValueStoreage(float64_t aValue) throw() : f64(aValue) {}
		ANVIL_CALL PrimativeValueStoreage(bool aValue) throw() : b8(aValue) {}
	};

	class PrimativeValue {
	private:
		template<class T>
		ANVIL_CONSTEXPR_FN T ANVIL_CALL as() const throw() {
			return
				type == ANVIL_8U ? static_cast<T>(value.u8) :
				type == ANVIL_8S ? static_cast<T>(value.s8) :
				type == ANVIL_16U ? static_cast<T>(value.u16) :
				type == ANVIL_16S ? static_cast<T>(value.s16) :
				type == ANVIL_32U ? static_cast<T>(value.u32) :
				type == ANVIL_32S ? static_cast<T>(value.s32) :
				type == ANVIL_64U ? static_cast<T>(value.u64) :
				type == ANVIL_64S ? static_cast<T>(value.s64) :
				type == ANVIL_32F ? static_cast<T>(value.f32) :
				type == ANVIL_64F ? static_cast<T>(value.f64) :
				type == ANVIL_8B ? static_cast<T>(value.b8) :
				static_cast<T>(0);
		}
	public:
		PrimativeValueStoreage value;
		Type type;

		ANVIL_CONSTEXPR_CLA ANVIL_CALL PrimativeValue() throw();
		ANVIL_CONSTEXPR_CLA ANVIL_CALL PrimativeValue(uint8_t aValue) throw();
		ANVIL_CONSTEXPR_CLA ANVIL_CALL PrimativeValue(uint16_t aValue) throw();
		ANVIL_CONSTEXPR_CLA ANVIL_CALL PrimativeValue(uint32_t aValue) throw();
		ANVIL_CONSTEXPR_CLA ANVIL_CALL PrimativeValue(uint64_t aValue) throw();
		ANVIL_CONSTEXPR_CLA ANVIL_CALL PrimativeValue(int8_t aValue) throw();
		ANVIL_CONSTEXPR_CLA ANVIL_CALL PrimativeValue(int16_t aValue) throw();
		ANVIL_CONSTEXPR_CLA ANVIL_CALL PrimativeValue(int32_t aValue) throw();
		ANVIL_CONSTEXPR_CLA ANVIL_CALL PrimativeValue(int64_t aValue) throw();
		ANVIL_CONSTEXPR_CLA ANVIL_CALL PrimativeValue(float32_t aValue) throw();
		ANVIL_CONSTEXPR_CLA ANVIL_CALL PrimativeValue(float64_t aValue) throw();
		ANVIL_CONSTEXPR_CLA ANVIL_CALL PrimativeValue(bool aValue) throw();
		
		template<class T>
		ANVIL_CALL PrimativeValue(Type aType, T aValue) throw() :
			type(aType),
			value()
		{
			switch (aType) {
			case ANVIL_8U:
				value.u8 = static_cast<uint8_t>(aValue);
				break;
			case ANVIL_8S:
				value.s8 = static_cast<int8_t>(aValue);
				break;
			case ANVIL_16U:
				value.u16 = static_cast<uint16_t>(aValue);
				break;
			case ANVIL_16S:
				value.s16 = static_cast<int16_t>(aValue);
				break;
			case ANVIL_32U:
				value.u32 = static_cast<uint32_t>(aValue);
				break;
			case ANVIL_32S:
				value.s32 = static_cast<int32_t>(aValue);
				break;
			case ANVIL_64U:
				value.u64 = static_cast<uint64_t>(aValue);
				break;
			case ANVIL_64S:
				value.s64 = static_cast<int64_t>(aValue);
				break;
			case ANVIL_32F:
				value.f32 = static_cast<float32_t>(aValue);
				break;
			case ANVIL_64F:
				value.f64 = static_cast<float64_t>(aValue);
				break;
			case ANVIL_8B:
				value.b8 = static_cast<bool>(aValue);
				break;
			}
		}

		explicit ANVIL_CONSTEXPR_FN ANVIL_CALL operator uint8_t() const throw() { return as<uint8_t>(); }
		explicit ANVIL_CONSTEXPR_FN ANVIL_CALL operator uint16_t() const throw() { return as<uint16_t>(); }
		explicit ANVIL_CONSTEXPR_FN ANVIL_CALL operator uint32_t() const throw() { return as<uint32_t>(); }
		explicit ANVIL_CONSTEXPR_FN ANVIL_CALL operator uint64_t() const throw() { return as<uint64_t>(); }
		explicit ANVIL_CONSTEXPR_FN ANVIL_CALL operator int8_t() const throw() { return as<int8_t>(); }
		explicit ANVIL_CONSTEXPR_FN ANVIL_CALL operator int16_t() const throw() { return as<int16_t>(); }
		explicit ANVIL_CONSTEXPR_FN ANVIL_CALL operator int32_t() const throw() { return as<int32_t>(); }
		explicit ANVIL_CONSTEXPR_FN ANVIL_CALL operator int64_t() const throw() { return as<int64_t>(); }
		explicit ANVIL_CONSTEXPR_FN ANVIL_CALL operator float32_t() const throw() { return as<float32_t>(); }
		explicit ANVIL_CONSTEXPR_FN ANVIL_CALL operator float64_t() const throw() { return as<float64_t>(); }
		explicit ANVIL_CONSTEXPR_FN ANVIL_CALL operator bool() const throw() { return as<bool>(); }
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
	static inline bool ANVIL_CALL dispatchByType(PrimativeValue aPrimative, 
	FU8 fu8,  FU16 fu16,  FU32 fu32,  FU64 fu64,  
	FS8 fs8,  FS16 fs16,  FS32 fs32,  FS64 fs64, 
	FF32 ff32,  FF64 ff64) {
		bool returnValue = true;
		switch(aPrimative.type) {
		case ANVIL_8U:
			fu8(aPrimative.value.u8);
			break;
		case ANVIL_8S:
			fs8(aPrimative.value.s8);
			break;
		case ANVIL_16U:
			fu16(aPrimative.value.u16);
			break;
		case ANVIL_16S:
			fs16(aPrimative.value.s16);
			break;
		case ANVIL_32U:
			fu32(aPrimative.value.u32);
			break;
		case ANVIL_32S:
			fs32(aPrimative.value.s32);
			break;
		case ANVIL_64U:
			fu64(aPrimative.value.u64);
			break;
		case ANVIL_64S:
			fs64(aPrimative.value.s64);
			break;
		case ANVIL_32F:
			ff32(aPrimative.value.f32);
			break;
		case ANVIL_64F:
			ff64(aPrimative.value.f64);
			break;
		default:
			returnValue = false;
			break;
		}
		return returnValue;
	}
}

#endif