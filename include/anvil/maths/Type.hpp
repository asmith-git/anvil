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

#ifndef ANVIL_8U
	#define ANVIL_8U  static_cast<anvil::Type>(0)
	#define ANVIL_8S  static_cast<anvil::Type>(1)
	#define ANVIL_16U static_cast<anvil::Type>(2)
	#define ANVIL_16S static_cast<anvil::Type>(3)
	#define ANVIL_32U static_cast<anvil::Type>(4)
	#define ANVIL_32S static_cast<anvil::Type>(5)
	#define ANVIL_64U static_cast<anvil::Type>(6)
	#define ANVIL_64S static_cast<anvil::Type>(7)
	#define ANVIL_32F static_cast<anvil::Type>(8)
	#define ANVIL_64F static_cast<anvil::Type>(9)
	#define ANVIL_8B  static_cast<anvil::Type>(10)
#endif

// Base Types

#define ANVIL_8UC1  anvil::CreateType(ANVIL_8U,  1);
#define ANVIL_8UC2  anvil::CreateType(ANVIL_8U,  2);
#define ANVIL_8UC3  anvil::CreateType(ANVIL_8U,  3);
#define ANVIL_8UC4  anvil::CreateType(ANVIL_8U,  4);
#define ANVIL_8SC1  anvil::CreateType(ANVIL_8S,  1);
#define ANVIL_8SC2  anvil::CreateType(ANVIL_8S,  2);
#define ANVIL_8SC3  anvil::CreateType(ANVIL_8S,  3);
#define ANVIL_8SC4  anvil::CreateType(ANVIL_8S,  4);
#define ANVIL_16UC1 anvil::CreateType(ANVIL_16U, 1);
#define ANVIL_16UC2 anvil::CreateType(ANVIL_16U, 2);
#define ANVIL_16UC3 anvil::CreateType(ANVIL_16U, 3);
#define ANVIL_16UC4 anvil::CreateType(ANVIL_16U, 4);
#define ANVIL_16SC1 anvil::CreateType(ANVIL_16S, 1);
#define ANVIL_16SC2 anvil::CreateType(ANVIL_16S, 2);
#define ANVIL_16SC3 anvil::CreateType(ANVIL_16S, 3);
#define ANVIL_16SC4 anvil::CreateType(ANVIL_16S, 4);
#define ANVIL_32UC1 anvil::CreateType(ANVIL_32U, 1);
#define ANVIL_32UC2 anvil::CreateType(ANVIL_32U, 2);
#define ANVIL_32UC3 anvil::CreateType(ANVIL_32U, 3);
#define ANVIL_32UC4 anvil::CreateType(ANVIL_32U, 4);
#define ANVIL_32SC1 anvil::CreateType(ANVIL_32S, 1);
#define ANVIL_32SC2 anvil::CreateType(ANVIL_32S, 2);
#define ANVIL_32SC3 anvil::CreateType(ANVIL_32S, 3);
#define ANVIL_32SC4 anvil::CreateType(ANVIL_32S, 4);
#define ANVIL_64UC1 anvil::CreateType(ANVIL_64U, 1);
#define ANVIL_64UC2 anvil::CreateType(ANVIL_64U, 2);
#define ANVIL_64UC3 anvil::CreateType(ANVIL_64U, 3);
#define ANVIL_64UC4 anvil::CreateType(ANVIL_64U, 4);
#define ANVIL_64SC1 anvil::CreateType(ANVIL_64S, 1);
#define ANVIL_64SC2 anvil::CreateType(ANVIL_64S, 2);
#define ANVIL_64SC3 anvil::CreateType(ANVIL_64S, 3);
#define ANVIL_64SC4 anvil::CreateType(ANVIL_64S, 4);
#define ANVIL_32FC1 anvil::CreateType(ANVIL_32F, 1);
#define ANVIL_32FC2 anvil::CreateType(ANVIL_32F, 2);
#define ANVIL_32FC3 anvil::CreateType(ANVIL_32F, 3);
#define ANVIL_32FC4 anvil::CreateType(ANVIL_32F, 4);
#define ANVIL_64FC1 anvil::CreateType(ANVIL_64F, 1);
#define ANVIL_64FC2 anvil::CreateType(ANVIL_64F, 2);
#define ANVIL_64FC3 anvil::CreateType(ANVIL_64F, 3);
#define ANVIL_64FC4 anvil::CreateType(ANVIL_64F, 4);
#define ANVIL_8BC1  anvil::CreateType(ANVIL_8B,  1);
#define ANVIL_8BC2  anvil::CreateType(ANVIL_8B,  2);
#define ANVIL_8BC3  anvil::CreateType(ANVIL_8B,  3);
#define ANVIL_8BC4  anvil::CreateType(ANVIL_8B,  4);

// SSE Types

#define ANVIL_8SC16 anvil::CreateType(ANVIL_8S,  16);
#define ANVIL_8SC8  anvil::CreateType(ANVIL_8S,  8);
#define ANVIL_16SC8 anvil::CreateType(ANVIL_16S, 8);

namespace anvil {
	enum Type : int16_t {

	};

	namespace detail {
		template<Type TYPE> struct TypeHelper;
		template<> struct TypeHelper<ANVIL_8U> { typedef uint8_t type; };
		template<> struct TypeHelper<ANVIL_8S> { typedef int8_t type; };
		template<> struct TypeHelper<ANVIL_16U> { typedef uint16_t type; };
		template<> struct TypeHelper<ANVIL_16S> { typedef int16_t type; };
		template<> struct TypeHelper<ANVIL_32U> { typedef uint32_t type; };
		template<> struct TypeHelper<ANVIL_32S> { typedef int32_t type; };
		template<> struct TypeHelper<ANVIL_64U> { typedef uint64_t type; };
		template<> struct TypeHelper<ANVIL_64S> { typedef int64_t type; };
		template<> struct TypeHelper<ANVIL_32F> { typedef float type; };
		template<> struct TypeHelper<ANVIL_64F> { typedef double type; };
		template<> struct TypeHelper<ANVIL_8B> { typedef bool type; };
	}

	static ANVIL_CONSTEXPR_FN Type CreateType(Type aType, int aChannels) throw() {
		return static_cast<Type>(((aChannels - 1) << 4) | aType);
	}

	static ANVIL_CONSTEXPR_FN Type GetPrimativeType(Type aType) throw() {
		return static_cast<Type>(aType & 15);
	}

	static ANVIL_CONSTEXPR_FN int GetChannels(Type aType) throw() {
		return (aType >> 4) + 1;
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

	template<Type TYPE>
	using Primative = typename detail::TypeHelper<GetPrimativeType(TYPE)>::type;
	
	template<Type TYPE>
	struct TypeInfo {
		typedef Primative<TYPE> type;
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