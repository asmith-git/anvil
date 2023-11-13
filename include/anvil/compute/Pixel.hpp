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
	template<size_t COUNT_8, size_t COUNT_16, size_t COUNT_32, size_t COUNT_64>
	struct _RawPixel {

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

		_RawPixel() {
			memset(GetData(), 0, sizeof(*this)); 
		}

		_RawPixel(uint8_t value) : _RawPixel() { Get<decltype(value)>() = value; }
		_RawPixel(int8_t value) : _RawPixel() { Get<decltype(value)>() = value; }
		_RawPixel(uint16_t value) : _RawPixel() { Get<decltype(value)>() = value; }
		_RawPixel(int16_t value) : _RawPixel() { Get<decltype(value)>() = value; }
		_RawPixel(uint32_t value) : _RawPixel() { Get<decltype(value)>() = value; }
		_RawPixel(int32_t value) : _RawPixel() { Get<decltype(value)>() = value; }
		_RawPixel(float32_t value) : _RawPixel() { Get<decltype(value)>() = value; }
		_RawPixel(uint64_t value) : _RawPixel() { Get<decltype(value)>() = value; }
		_RawPixel(int64_t value) : _RawPixel() { Get<decltype(value)>() = value; }
		_RawPixel(float64_t value) : _RawPixel() { Get<decltype(value)>() = value; }
#if ANVIL_F8_SUPPORT
		_RawPixel(float8_t value) : _RawPixel() { Get<decltype(value)>() = value; }
#endif
#if ANVIL_F16_SUPPORT
		_RawPixel(float16_t value) : _RawPixel() { Get<decltype(value)>() = value; }
#endif
		template<class T>
		_RawPixel(const T* data, size_t count) :
			_RawPixel()
		{
			enum { MAX_ELEMENTS = COUNT_8 / sizeof(T) };
			if (count > MAX_ELEMENTS) count = MAX_ELEMENTS;
			memcpy(GetData(), data, sizeof(T) * count);
		}

		template<class T>
		_RawPixel(const std::vector<T>& value) :
			_RawPixel(value.data(), value.size())
		{}

		template<class T, size_t S>
		_RawPixel(const std::array<T,S>& value) :
			_RawPixel(value.data(), S)
		{}

		template<class T = void>
		inline T* GetData()
		{
			return reinterpret_cast<T*>(&u8);
		}

		template<class T = void>
		inline const T* GetData() const
		{
			return reinterpret_cast<const T*>(&u8);
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

	template<>
	struct _RawPixel<1u, 1u, 1u, 1u> {

		union {
			uint8_t u8;
			int8_t s8;
			uint16_t u16;
			int16_t s16;
			uint32_t u32;
			int32_t s32;
			float32_t f32;
			uint64_t u64;
			int64_t s64;
			float64_t f64;
#if ANVIL_F8_SUPPORT
			float8_t f8;
#endif
#if ANVIL_F16_SUPPORT
			float16_t f16;
#endif
		};

		_RawPixel() :
			u64(0ull)
		{}

		_RawPixel(uint8_t value) : _RawPixel() { Get<decltype(value)>() = value; }
		_RawPixel(int8_t value) : _RawPixel() { Get<decltype(value)>() = value; }
		_RawPixel(uint16_t value) : _RawPixel() { Get<decltype(value)>() = value; }
		_RawPixel(int16_t value) : _RawPixel() { Get<decltype(value)>() = value; }
		_RawPixel(uint32_t value) : _RawPixel() { Get<decltype(value)>() = value; }
		_RawPixel(int32_t value) : _RawPixel() { Get<decltype(value)>() = value; }
		_RawPixel(float32_t value) : _RawPixel() { Get<decltype(value)>() = value; }
		_RawPixel(uint64_t value) : _RawPixel() { Get<decltype(value)>() = value; }
		_RawPixel(int64_t value) : _RawPixel() { Get<decltype(value)>() = value; }
		_RawPixel(float64_t value) : _RawPixel() { Get<decltype(value)>() = value; }
#if ANVIL_F8_SUPPORT
		_RawPixel(float8_t value) : _RawPixel() { Get<decltype(value)>() = value; }
#endif
#if ANVIL_F16_SUPPORT
		_RawPixel(float16_t value) : _RawPixel() { Get<decltype(value)>() = value; }
#endif
		template<class T>
		_RawPixel(const T* data, size_t count) :
			_RawPixel()
		{
			enum { MAX_ELEMENTS = 1u };
			if (count > MAX_ELEMENTS) count = MAX_ELEMENTS;
			memcpy(GetData(), data, sizeof(T) * count);
		}

		template<class T>
		_RawPixel(const std::vector<T>& value) :
			_RawPixel(value.data(), value.size())
		{}

		template<class T, size_t S>
		_RawPixel(const std::array<T, S>& value) :
			_RawPixel(value.data(), S)
		{}

		template<class T = void>
		inline T* GetData()
		{
			return reinterpret_cast<T*>(&u8);
		}

		template<class T = void>
		inline const T* GetData() const
		{
			return reinterpret_cast<const T*>(&u8);
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

	/*!
	*	\brief Alternate version of anvil::compute:Scalar / anvil::compute::Vector with simplified syntax
	*/
	template<size_t COUNT_8, size_t COUNT_16, size_t COUNT_32, size_t COUNT_64>
	struct _TypedPixel {
		_RawPixel<COUNT_8, COUNT_16, COUNT_32, COUNT_64> value;
		Type type;

		_TypedPixel() : 
			value(), 
			type(ANVIL_8UX1) 
		{}

		_TypedPixel(anvil::Type a_type) : 
			value(), 
			type(a_type) 
		{}

		_TypedPixel(uint8_t a_value) : value(a_value), type(EnumFromType<decltype(a_value)>::value) {}
		_TypedPixel(int8_t a_value) : value(a_value), type(EnumFromType<decltype(a_value)>::value) {}
		_TypedPixel(uint16_t a_value) : value(a_value), type(EnumFromType<decltype(a_value)>::value) {}
		_TypedPixel(int16_t a_value) : value(a_value), type(EnumFromType<decltype(a_value)>::value) {}
		_TypedPixel(uint32_t a_value) : value(a_value), type(EnumFromType<decltype(a_value)>::value) {}
		_TypedPixel(int32_t a_value) : value(a_value), type(EnumFromType<decltype(a_value)>::value) {}
		_TypedPixel(float32_t a_value) : value(a_value), type(EnumFromType<decltype(a_value)>::value) {}
		_TypedPixel(uint64_t a_value) : value(a_value), type(EnumFromType<decltype(a_value)>::value) {}
		_TypedPixel(int64_t a_value) : value(a_value), type(EnumFromType<decltype(a_value)>::value) {}
		_TypedPixel(float64_t a_value) : value(a_value), type(EnumFromType<decltype(a_value)>::value) {}
#if ANVIL_F8_SUPPORT
		_TypedPixel(float8_t a_value) : value(a_value), type(EnumFromType<decltype(a_value)>::value) {}
#endif
#if ANVIL_F16_SUPPORT
		_TypedPixel(float16_t a_value) : value(a_value), type(EnumFromType<decltype(a_value)>::value) {}
#endif

		template<class T>
		_TypedPixel(const T* data, size_t count) :
			value(data, count),
			type(EnumFromType<T>::value)
		{
			enum { MAX_ELEMENTS = COUNT_8 / sizeof(T) };
			if (count > MAX_ELEMENTS) count = MAX_ELEMENTS;
			type.SetNumberOfChannels(count);
		}

		template<class T>
		_TypedPixel(const std::vector<T>& value) :
			_TypedPixel(value.data(), value.size())
		{}

		template<class T, size_t S>
		_TypedPixel(const std::array<T, S>& value) :
			_TypedPixel(value.data(), S)
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

	typedef _RawPixel<1u, 1u, 1u, 1u> RawPixelScalar;
	typedef _RawPixel<anvil::Type::MAX_CHANNELS, anvil::Type::MAX_CHANNELS / 2, anvil::Type::MAX_CHANNELS / 4u, anvil::Type::MAX_CHANNELS / 8u> RawPixel;
	typedef _RawPixel<anvil::Type::MAX_CHANNELS, anvil::Type::MAX_CHANNELS, anvil::Type::MAX_CHANNELS, anvil::Type::MAX_CHANNELS> BigRawPixel;

	static_assert(sizeof(RawPixel) == anvil::Type::MAX_CHANNELS, "Size of RawPixel is different than expected");

	typedef _TypedPixel<1u, 1u, 1u, 1u> SmallTypedPixel;
	typedef _TypedPixel<anvil::Type::MAX_CHANNELS, anvil::Type::MAX_CHANNELS / 2, anvil::Type::MAX_CHANNELS / 4u, anvil::Type::MAX_CHANNELS / 8u> TypedPixel;
	typedef _TypedPixel<anvil::Type::MAX_CHANNELS, anvil::Type::MAX_CHANNELS, anvil::Type::MAX_CHANNELS, anvil::Type::MAX_CHANNELS> BigTypedPixel;

}}

#endif
