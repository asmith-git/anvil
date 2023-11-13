//Copyupper 2023 Adam G. Smith
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

#ifndef ANVIL_COMPUTE_PIXEL_HPP
#define ANVIL_COMPUTE_PIXEL_HPP

#include "anvil/compute/Type.hpp"
#include <vector>
#include <array>

namespace anvil { namespace compute {

	/*!
	*	\brief Alternate version of anvil::compute:Scalar / anvil::compute::Vector with simplified syntax
	*/
	struct RawPixel {
		enum {
			COUNT_8 = anvil::Type::MAX_CHANNELS,	//!< Maximum number of 8-bit values
			COUNT_16 = COUNT_8 / 2,					//!< Maximum number of 16-bit values
			COUNT_32 = COUNT_8 / 4,					//!< Maximum number of 32-bit values
			COUNT_64 = COUNT_8 / 8,					//!< Maximum number of 64-bit values
		};

		union {
			uint8_t u8[COUNT_8];
			int8_t s8[COUNT_8];
			uint16_t u16[COUNT_16];
			int16_t s16[COUNT_16];
			uint32_t u32[COUNT_32];
			int32_t s32[COUNT_32];
			float32_t f32[COUNT_32];
			uint64_t u64[COUNT_64];
			int64_t s64[COUNT_64];
			float64_t f64[COUNT_64];
#if ANVIL_F8_SUPPORT
			float8_t f8[COUNT_8];
#endif
#if ANVIL_F16_SUPPORT
			float16_t f16[COUNT_16];
#endif
		};

		RawPixel() {
			memset(GetData(), 0, COUNT_8); 
		}

		RawPixel(uint8_t value) : RawPixel() { Get<decltype(value)>() = value; }
		RawPixel(int8_t value) : RawPixel() { Get<decltype(value)>() = value; }
		RawPixel(uint16_t value) : RawPixel() { Get<decltype(value)>() = value; }
		RawPixel(int16_t value) : RawPixel() { Get<decltype(value)>() = value; }
		RawPixel(uint32_t value) : RawPixel() { Get<decltype(value)>() = value; }
		RawPixel(int32_t value) : RawPixel() { Get<decltype(value)>() = value; }
		RawPixel(float32_t value) : RawPixel() { Get<decltype(value)>() = value; }
		RawPixel(uint64_t value) : RawPixel() { Get<decltype(value)>() = value; }
		RawPixel(int64_t value) : RawPixel() { Get<decltype(value)>() = value; }
		RawPixel(float64_t value) : RawPixel() { Get<decltype(value)>() = value; }
#if ANVIL_F8_SUPPORT
		RawPixel(float8_t value) : RawPixel() { Get<decltype(value)>() = value; }
#endif
#if ANVIL_F16_SUPPORT
		RawPixel(float16_t value) : RawPixel() { Get<decltype(value)>() = value; }
#endif
		template<class T>
		RawPixel(const T* data, size_t count) :
			RawPixel()
		{
			enum { MAX_ELEMENTS = COUNT_8 / sizeof(T) };
			if (count > MAX_ELEMENTS) count = MAX_ELEMENTS;
			memcpy(GetData(), data, sizeof(T) * count);
		}

		template<class T>
		RawPixel(const std::vector<T>& value) :
			RawPixel(value.data(), value.size())
		{}

		template<class T, size_t S>
		RawPixel(const std::array<T,S>& value) :
			RawPixel(value.data(), S)
		{}

		template<class T = void>
		inline T* GetData()
		{
			return reinterpret_cast<T*>(u8);
		}

		template<class T = void>
		inline const T* GetData() const
		{
			return reinterpret_cast<const T*>(u8);
		}

		template<class T>
		inline T& Get()
		{
			return *GetData<T>();
		}

		template<class T>
		inline const T& Get() const
		{
			return *GetData<T>();
		}

		template<class T>
		inline T& Get(size_t i)
		{
			return GetData<T>()[i];
		}

		template<class T>
		inline const T& Get(size_t i) const
		{
			return GetData<T>()[i];
		}

		template<class T>
		inline operator T& ()
		{
			return Get<T>();
		}

		template<class T>
		inline operator const T& () const
		{
			return Get<T>();
		}
	};

	static_assert(sizeof(RawPixel) == anvil::Type::MAX_CHANNELS, "Size of RawPixel is different than expected");

	/*!
	*	\brief Alternate version of anvil::compute:Scalar / anvil::compute::Vector with simplified syntax
	*/
	struct TypedPixel {
		RawPixel value;
		Type type;

		TypedPixel() : 
			value(), 
			type(ANVIL_8UX1) 
		{}

		TypedPixel(anvil::Type a_type) : 
			value(), 
			type(a_type) 
		{}

		TypedPixel(uint8_t a_value) : value(a_value), type(EnumFromType<decltype(a_value)>::value) {}
		TypedPixel(int8_t a_value) : value(a_value), type(EnumFromType<decltype(a_value)>::value) {}
		TypedPixel(uint16_t a_value) : value(a_value), type(EnumFromType<decltype(a_value)>::value) {}
		TypedPixel(int16_t a_value) : value(a_value), type(EnumFromType<decltype(a_value)>::value) {}
		TypedPixel(uint32_t a_value) : value(a_value), type(EnumFromType<decltype(a_value)>::value) {}
		TypedPixel(int32_t a_value) : value(a_value), type(EnumFromType<decltype(a_value)>::value) {}
		TypedPixel(float32_t a_value) : value(a_value), type(EnumFromType<decltype(a_value)>::value) {}
		TypedPixel(uint64_t a_value) : value(a_value), type(EnumFromType<decltype(a_value)>::value) {}
		TypedPixel(int64_t a_value) : value(a_value), type(EnumFromType<decltype(a_value)>::value) {}
		TypedPixel(float64_t a_value) : value(a_value), type(EnumFromType<decltype(a_value)>::value) {}
#if ANVIL_F8_SUPPORT
		TypedPixel(float8_t a_value) : value(a_value), type(EnumFromType<decltype(a_value)>::value) {}
#endif
#if ANVIL_F16_SUPPORT
		TypedPixel(float16_t a_value) : value(a_value), type(EnumFromType<decltype(a_value)>::value) {}
#endif

		template<class T>
		TypedPixel(const T* data, size_t count) :
			value(data, count),
			type(EnumFromType<T>::value)
		{
			enum { MAX_ELEMENTS = RawPixel::COUNT_8 / sizeof(T) };
			if (count > MAX_ELEMENTS) count = MAX_ELEMENTS;
			type.SetNumberOfChannels(count);
		}

		template<class T>
		TypedPixel(const std::vector<T>& value) :
			TypedPixel(value.data(), value.size())
		{}

		template<class T, size_t S>
		TypedPixel(const std::array<T, S>& value) :
			TypedPixel(value.data(), S)
		{}

		template<class T>
		inline operator T& ()
		{
			return value.Get<T>();
		}

		template<class T>
		inline operator const T& () const
		{
			return value.Get<T>();
		}
	};


}}

#endif
