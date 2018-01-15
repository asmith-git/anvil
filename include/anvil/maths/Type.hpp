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
#include <type_traits>
#include "anvil/core/Keywords.hpp"

// Primative Types

enum AnvilType : int16_t {
#ifdef ANVIL_OCV_COMPATIBILITY
	ANVIL_8U  = 0,
	ANVIL_8S  = 1,
	ANVIL_16U = 2,
	ANVIL_16S = 3,
	ANVIL_32U = -1,
	ANVIL_32S = 4,
	ANVIL_64U = -2,
	ANVIL_64S = -3,
	ANVIL_32F = 5,
	ANVIL_64F = 6,
	ANVIL_8B  = -4
#else
	ANVIL_8U  = 0
	ANVIL_8S  = 1
	ANVIL_16U = 2
	ANVIL_16S = 3
	ANVIL_32U = 4
	ANVIL_32S = 5
	ANVIL_64U = 6
	ANVIL_64S = 7
	ANVIL_32F = 8
	ANVIL_64F = 9
	ANVIL_8B  = 10
#endif
};
// Base Types

#define ANVIL_MAKETYPE(T,C) anvil::CreateType(T,C)

#define ANVIL_8UC1  ANVIL_MAKETYPE(ANVIL_8U,  1)
#define ANVIL_8UC2  ANVIL_MAKETYPE(ANVIL_8U,  2)
#define ANVIL_8UC3  ANVIL_MAKETYPE(ANVIL_8U,  3)
#define ANVIL_8UC4  ANVIL_MAKETYPE(ANVIL_8U,  4)
#define ANVIL_8SC1  ANVIL_MAKETYPE(ANVIL_8S,  1)
#define ANVIL_8SC2  ANVIL_MAKETYPE(ANVIL_8S,  2)
#define ANVIL_8SC3  ANVIL_MAKETYPE(ANVIL_8S,  3)
#define ANVIL_8SC4  ANVIL_MAKETYPE(ANVIL_8S,  4)
#define ANVIL_16UC1 ANVIL_MAKETYPE(ANVIL_16U, 1)
#define ANVIL_16UC2 ANVIL_MAKETYPE(ANVIL_16U, 2)
#define ANVIL_16UC3 ANVIL_MAKETYPE(ANVIL_16U, 3)
#define ANVIL_16UC4 ANVIL_MAKETYPE(ANVIL_16U, 4)
#define ANVIL_16SC1 ANVIL_MAKETYPE(ANVIL_16S, 1)
#define ANVIL_16SC2 ANVIL_MAKETYPE(ANVIL_16S, 2)
#define ANVIL_16SC3 ANVIL_MAKETYPE(ANVIL_16S, 3)
#define ANVIL_16SC4 ANVIL_MAKETYPE(ANVIL_16S, 4)
#define ANVIL_32UC1 ANVIL_MAKETYPE(ANVIL_32U, 1)
#define ANVIL_32UC2 ANVIL_MAKETYPE(ANVIL_32U, 2)
#define ANVIL_32UC3 ANVIL_MAKETYPE(ANVIL_32U, 3)
#define ANVIL_32UC4 ANVIL_MAKETYPE(ANVIL_32U, 4)
#define ANVIL_32SC1 ANVIL_MAKETYPE(ANVIL_32S, 1)
#define ANVIL_32SC2 ANVIL_MAKETYPE(ANVIL_32S, 2)
#define ANVIL_32SC3 ANVIL_MAKETYPE(ANVIL_32S, 3)
#define ANVIL_32SC4 ANVIL_MAKETYPE(ANVIL_32S, 4)
#define ANVIL_64UC1 ANVIL_MAKETYPE(ANVIL_64U, 1)
#define ANVIL_64UC2 ANVIL_MAKETYPE(ANVIL_64U, 2)
#define ANVIL_64UC3 ANVIL_MAKETYPE(ANVIL_64U, 3)
#define ANVIL_64UC4 ANVIL_MAKETYPE(ANVIL_64U, 4)
#define ANVIL_64SC1 ANVIL_MAKETYPE(ANVIL_64S, 1)
#define ANVIL_64SC2 ANVIL_MAKETYPE(ANVIL_64S, 2)
#define ANVIL_64SC3 ANVIL_MAKETYPE(ANVIL_64S, 3)
#define ANVIL_64SC4 ANVIL_MAKETYPE(ANVIL_64S, 4)
#define ANVIL_32FC1 ANVIL_MAKETYPE(ANVIL_32F, 1)
#define ANVIL_32FC2 ANVIL_MAKETYPE(ANVIL_32F, 2)
#define ANVIL_32FC3 ANVIL_MAKETYPE(ANVIL_32F, 3)
#define ANVIL_32FC4 ANVIL_MAKETYPE(ANVIL_32F, 4)
#define ANVIL_64FC1 ANVIL_MAKETYPE(ANVIL_64F, 1)
#define ANVIL_64FC2 ANVIL_MAKETYPE(ANVIL_64F, 2)
#define ANVIL_64FC3 ANVIL_MAKETYPE(ANVIL_64F, 3)
#define ANVIL_64FC4 ANVIL_MAKETYPE(ANVIL_64F, 4)
#define ANVIL_8BC1  ANVIL_MAKETYPE(ANVIL_8B,  1)
#define ANVIL_8BC2  ANVIL_MAKETYPE(ANVIL_8B,  2)
#define ANVIL_8BC3  ANVIL_MAKETYPE(ANVIL_8B,  3)
#define ANVIL_8BC4  ANVIL_MAKETYPE(ANVIL_8B,  4)

// SSE Types

#define ANVIL_8SC16 ANVIL_MAKETYPE(ANVIL_8S,  16)
#define ANVIL_8SC8  ANVIL_MAKETYPE(ANVIL_8S,  8)
#define ANVIL_16SC8 ANVIL_MAKETYPE(ANVIL_16S, 8)

namespace anvil {
	typedef AnvilType Type;

	namespace detail {
		enum {
#ifdef ANVIL_OCV_COMPATIBILITY
			CHANNEL_SHIFT = 3,
			MAX_DEPTH = 1 << CHANNEL_SHIFT,
			DEPTH_MASK = MAX_DEPTH - 1
#else
			CHANNEL_SHIFT = 4,
			DEPTH_MASK = 15
#endif
		};
	}

	static ANVIL_CONSTEXPR_FN Type CreateType(Type aType, int aChannels) throw() {
#ifdef ANVIL_OCV_COMPATIBILITY
		return static_cast<Type>((aType & detail::DEPTH_MASK) + (((aChannels)-1) << detail::CHANNEL_SHIFT));
#else
		return static_cast<Type>(((aChannels - 1) << detail::CHANNEL_SHIFT) | aType);
#endif
	}

	static ANVIL_CONSTEXPR_FN Type GetPrimativeType(Type aType) throw() {
#ifdef ANVIL_OCV_COMPATIBILITY
		return static_cast<Type>(aType & detail::DEPTH_MASK);
#else
		return static_cast<Type>(aType & detail::DEPTH_MASK);
#endif
	}

	static ANVIL_CONSTEXPR_FN int GetChannels(Type aType) throw() {
#ifdef ANVIL_OCV_COMPATIBILITY
		return ((aType & (~detail::DEPTH_MASK)) >> detail::CHANNEL_SHIFT) + 1;
#else
		return (aType >> detail::CHANNEL_SHIFT) + 1;
#endif
	}

	static ANVIL_CONSTEXPR_FN Type GetWidePrimativeType(Type aType) throw() {
			return 
				aType == ANVIL_8U || aType == ANVIL_8S ? ANVIL_16S :
				aType == ANVIL_16U || aType == ANVIL_16S ? ANVIL_32S :
				aType == ANVIL_32U ? ANVIL_64S :
				aType;
	}

	static ANVIL_CONSTEXPR_FN Type GetWideType(Type aType) throw() {
		return CreateType(
			GetWidePrimativeType(GetPrimativeType(aType)),
			GetChannels(aType));
	}

	namespace detail {
		static ANVIL_CONSTEXPR_FN size_t SizeOfPrimative(Type aType) throw() {
			return
				aType == ANVIL_8U || aType == ANVIL_8S || aType == ANVIL_8B ? 1 :
				aType == ANVIL_16U || aType == ANVIL_16S ? 2 :
				aType == ANVIL_32U || aType == ANVIL_32S || aType == ANVIL_32F ? 4 :
				aType == ANVIL_64U || aType == ANVIL_64S || aType == ANVIL_64F ? 8 :
				0;
		}
	}

	static ANVIL_CONSTEXPR_FN size_t SizeOf(Type aType) throw() {
		return detail::SizeOfPrimative(GetPrimativeType(aType)) * GetChannels(aType);
	}

	static ANVIL_CONSTEXPR_FN size_t WidthOf(Type aType) throw() {
		return detail::SizeOfPrimative(GetPrimativeType(aType)) << 3;
	}

	template<Type TYPE> struct TypeFromEnum;
	template<> struct TypeFromEnum<ANVIL_8U>  { typedef uint8_t type; };
	template<> struct TypeFromEnum<ANVIL_8S>  { typedef int8_t type; };
	template<> struct TypeFromEnum<ANVIL_16U> { typedef uint16_t type; };
	template<> struct TypeFromEnum<ANVIL_16S> { typedef int16_t type; };
	template<> struct TypeFromEnum<ANVIL_32U> { typedef uint32_t type; };
	template<> struct TypeFromEnum<ANVIL_32S> { typedef int32_t type; };
	template<> struct TypeFromEnum<ANVIL_64U> { typedef uint64_t type; };
	template<> struct TypeFromEnum<ANVIL_64S> { typedef int64_t type; };
	template<> struct TypeFromEnum<ANVIL_32F> { typedef float type; };
	template<> struct TypeFromEnum<ANVIL_64F> { typedef double type; };
	template<> struct TypeFromEnum<ANVIL_8B>  { typedef bool type; };

	template<class T> struct EnumFromType;
	template<> struct EnumFromType<uint8_t>  { static ANVIL_CONSTEXPR_VAR const Type value = ANVIL_8U; };
	template<> struct EnumFromType<int8_t>   { static ANVIL_CONSTEXPR_VAR const Type value = ANVIL_8S; };
	template<> struct EnumFromType<uint16_t> { static ANVIL_CONSTEXPR_VAR const Type value = ANVIL_16U; };
	template<> struct EnumFromType<int16_t>  { static ANVIL_CONSTEXPR_VAR const Type value = ANVIL_16S; };
	template<> struct EnumFromType<uint32_t> { static ANVIL_CONSTEXPR_VAR const Type value = ANVIL_32U; };
	template<> struct EnumFromType<int32_t>  { static ANVIL_CONSTEXPR_VAR const Type value = ANVIL_32S; };
	template<> struct EnumFromType<uint64_t> { static ANVIL_CONSTEXPR_VAR const Type value = ANVIL_64U; };
	template<> struct EnumFromType<int64_t>  { static ANVIL_CONSTEXPR_VAR const Type value = ANVIL_64S; };
	template<> struct EnumFromType<float>    { static ANVIL_CONSTEXPR_VAR const Type value = ANVIL_32F; };
	template<> struct EnumFromType<double>   { static ANVIL_CONSTEXPR_VAR const Type value = ANVIL_64F; };
	template<> struct EnumFromType<bool>     { static ANVIL_CONSTEXPR_VAR const Type value = ANVIL_8B; };
	
	template<Type TYPE>
	struct TypeInfo {
		typedef TypeFromEnum<TYPE> type;
		enum {
			channels = GetChannels(TYPE),
			size = sizeof(type),
			is_unsigned = std::is_unsigned<type>::value,
			is_signed = std::is_signed<type>::value,
			is_float = std::is_floating_point<type>::value
		};
	};

	struct TypeInfoRuntime {
		uint16_t channels : 8;
		uint16_t size : 3;
		uint16_t is_unsigned : 1;
		uint16_t is_signed : 1;
		uint16_t is_float : 1;

		TypeInfoRuntime() throw() :
			channels(0),
			size(0),
			is_unsigned(0),
			is_signed(0),
			is_float(0)
		{}

		TypeInfoRuntime(int aChannels, int aSize, int aUnsigned, int aSigned, int aFloat) throw() :
			channels(aChannels),
			size(aSize),
			is_unsigned(aUnsigned),
			is_signed(aSigned),
			is_float(aFloat)
		{}
	};

	static TypeInfoRuntime GetTypeInfo(Type aType) throw() {
		switch (GetPrimativeType(aType)) {
			case ANVIL_8U :
				return { GetChannels(aType), 1, 1, 0, 0 };
			case ANVIL_8S :
				return { GetChannels(aType), 1, 0, 1, 0 };
			case ANVIL_16U :
				return { GetChannels(aType), 2, 1, 0, 0 };
			case ANVIL_16S :
				return { GetChannels(aType), 2, 0, 1, 0 };
			case ANVIL_32U :
				return { GetChannels(aType), 4, 1, 0, 0 };
			case ANVIL_32S :
				return { GetChannels(aType), 4, 0, 1, 0 };
			case ANVIL_64U :
				return { GetChannels(aType), 8, 1, 0, 0 };
			case ANVIL_64S :
				return { GetChannels(aType), 8, 0, 1, 0 };
			case ANVIL_32F :
				return { GetChannels(aType), 4, 0, 0, 1 };
			case ANVIL_64F :
				return { GetChannels(aType), 8, 0, 0, 1 };
			case ANVIL_8B :
				return { GetChannels(aType), 8, 0, 0, 0 };
			default:
				return TypeInfoRuntime();
		}
	}
}

#endif