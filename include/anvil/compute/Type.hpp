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
#include "anvil/core/Keywords.hpp"

// Primative Types

namespace anvil {

#define ANVIL_HELPER(TY, BY, CH) (TY | (BY << 3u) | (CH << 5u))

	enum EnumeratedType : uint8_t {
		ANVIL_8UX1 =	ANVIL_HELPER(0, 0, 0),
		ANVIL_8UX2 =	ANVIL_HELPER(0, 0, 1),
		ANVIL_8UX3 =	ANVIL_HELPER(0, 0, 2),
		ANVIL_8UX4 =	ANVIL_HELPER(0, 0, 3),
		ANVIL_8UX5 =	ANVIL_HELPER(0, 0, 4),
		ANVIL_8UX6 =	ANVIL_HELPER(0, 0, 5),
		ANVIL_8UX7 =	ANVIL_HELPER(0, 0, 6),
		ANVIL_8UX8 =	ANVIL_HELPER(0, 0, 7),
		ANVIL_16UX1 =	ANVIL_HELPER(0, 1, 0),
		ANVIL_16UX2 =	ANVIL_HELPER(0, 1, 1),
		ANVIL_16UX3 =	ANVIL_HELPER(0, 1, 2),
		ANVIL_16UX4 =	ANVIL_HELPER(0, 1, 3),
		ANVIL_16UX5 =	ANVIL_HELPER(0, 1, 4),
		ANVIL_16UX6 =	ANVIL_HELPER(0, 1, 5),
		ANVIL_16UX7 =	ANVIL_HELPER(0, 1, 6),
		ANVIL_16UX8 =	ANVIL_HELPER(0, 1, 7),
		ANVIL_32UX1 =	ANVIL_HELPER(0, 2, 0),
		ANVIL_32UX2 =	ANVIL_HELPER(0, 2, 1),
		ANVIL_32UX3 =	ANVIL_HELPER(0, 2, 2),
		ANVIL_32UX4 =	ANVIL_HELPER(0, 2, 3),
		ANVIL_32UX5 =	ANVIL_HELPER(0, 2, 4),
		ANVIL_32UX6 =	ANVIL_HELPER(0, 2, 5),
		ANVIL_32UX7 =	ANVIL_HELPER(0, 2, 6),
		ANVIL_32UX8 =	ANVIL_HELPER(0, 2, 7),
		ANVIL_64UX1 =	ANVIL_HELPER(0, 3, 0),
		ANVIL_64UX2 =	ANVIL_HELPER(0, 3, 1),
		ANVIL_64UX3 =	ANVIL_HELPER(0, 3, 2),
		ANVIL_64UX4 =	ANVIL_HELPER(0, 3, 3),
		ANVIL_64UX5 =	ANVIL_HELPER(0, 3, 4),
		ANVIL_64UX6 =	ANVIL_HELPER(0, 3, 5),
		ANVIL_64UX7 =	ANVIL_HELPER(0, 3, 6),
		ANVIL_64UX8 =	ANVIL_HELPER(0, 3, 7),
		ANVIL_8SX1 =	ANVIL_HELPER(1, 0, 0),
		ANVIL_8SX2 =	ANVIL_HELPER(1, 0, 1),
		ANVIL_8SX3 =	ANVIL_HELPER(1, 0, 2),
		ANVIL_8SX4 =	ANVIL_HELPER(1, 0, 3),
		ANVIL_8SX5 =	ANVIL_HELPER(1, 0, 4),
		ANVIL_8SX6 =	ANVIL_HELPER(1, 0, 5),
		ANVIL_8SX7 =	ANVIL_HELPER(1, 0, 6),
		ANVIL_8SX8 =	ANVIL_HELPER(1, 0, 7),
		ANVIL_16SX1 =	ANVIL_HELPER(1, 1, 0),
		ANVIL_16SX2 =	ANVIL_HELPER(1, 1, 1),
		ANVIL_16SX3 =	ANVIL_HELPER(1, 1, 2),
		ANVIL_16SX4 =	ANVIL_HELPER(1, 1, 3),
		ANVIL_16SX5 =	ANVIL_HELPER(1, 1, 4),
		ANVIL_16SX6 =	ANVIL_HELPER(1, 1, 5),
		ANVIL_16SX7 =	ANVIL_HELPER(1, 1, 6),
		ANVIL_16SX8 =	ANVIL_HELPER(1, 1, 7),
		ANVIL_32SX1 =	ANVIL_HELPER(1, 2, 0),
		ANVIL_32SX2 =	ANVIL_HELPER(1, 2, 1),
		ANVIL_32SX3 =	ANVIL_HELPER(1, 2, 2),
		ANVIL_32SX4 =	ANVIL_HELPER(1, 2, 3),
		ANVIL_32SX5 =	ANVIL_HELPER(1, 2, 4),
		ANVIL_32SX6 =	ANVIL_HELPER(1, 2, 5),
		ANVIL_32SX7 =	ANVIL_HELPER(1, 2, 6),
		ANVIL_32SX8 =	ANVIL_HELPER(1, 2, 7),
		ANVIL_64SX1 =	ANVIL_HELPER(1, 3, 0),
		ANVIL_64SX2 =	ANVIL_HELPER(1, 3, 1),
		ANVIL_64SX3 =	ANVIL_HELPER(1, 3, 2),
		ANVIL_64SX4 =	ANVIL_HELPER(1, 3, 3),
		ANVIL_64SX5 =	ANVIL_HELPER(1, 3, 4),
		ANVIL_64SX6 =	ANVIL_HELPER(1, 3, 5),
		ANVIL_64SX7 =	ANVIL_HELPER(1, 3, 6),
		ANVIL_64SX8 =	ANVIL_HELPER(1, 3, 7),
		ANVIL_8FX1 =	ANVIL_HELPER(2, 0, 0),
		ANVIL_8FX2 =	ANVIL_HELPER(2, 0, 1),
		ANVIL_8FX3 =	ANVIL_HELPER(2, 0, 2),
		ANVIL_8FX4 =	ANVIL_HELPER(2, 0, 3),
		ANVIL_8FX5 =	ANVIL_HELPER(2, 0, 4),
		ANVIL_8FX6 =	ANVIL_HELPER(2, 0, 5),
		ANVIL_8FX7 =	ANVIL_HELPER(2, 0, 6),
		ANVIL_8FX8 =	ANVIL_HELPER(2, 0, 7),
		ANVIL_16FX1 =	ANVIL_HELPER(2, 1, 0),
		ANVIL_16FX2 =	ANVIL_HELPER(2, 1, 1),
		ANVIL_16FX3 =	ANVIL_HELPER(2, 1, 2),
		ANVIL_16FX4 =	ANVIL_HELPER(2, 1, 3),
		ANVIL_16FX5 =	ANVIL_HELPER(2, 1, 4),
		ANVIL_16FX6 =	ANVIL_HELPER(2, 1, 5),
		ANVIL_16FX7 =	ANVIL_HELPER(2, 1, 6),
		ANVIL_16FX8 =	ANVIL_HELPER(2, 1, 7),
		ANVIL_32FX1 =	ANVIL_HELPER(2, 2, 0),
		ANVIL_32FX2 =	ANVIL_HELPER(2, 2, 1),
		ANVIL_32FX3 =	ANVIL_HELPER(2, 2, 2),
		ANVIL_32FX4 =	ANVIL_HELPER(2, 2, 3),
		ANVIL_32FX5 =	ANVIL_HELPER(2, 2, 4),
		ANVIL_32FX6 =	ANVIL_HELPER(2, 2, 5),
		ANVIL_32FX7 =	ANVIL_HELPER(2, 2, 6),
		ANVIL_32FX8 =	ANVIL_HELPER(2, 2, 7),
		ANVIL_64FX1 =	ANVIL_HELPER(2, 3, 0),
		ANVIL_64FX2 =	ANVIL_HELPER(2, 3, 1),
		ANVIL_64FX3 =	ANVIL_HELPER(2, 3, 2),
		ANVIL_64FX4 =	ANVIL_HELPER(2, 3, 3),
		ANVIL_64FX5 =	ANVIL_HELPER(2, 3, 4),
		ANVIL_64FX6 =	ANVIL_HELPER(2, 3, 5),
		ANVIL_64FX7 =	ANVIL_HELPER(2, 3, 6),
		ANVIL_64FX8 =	ANVIL_HELPER(2, 3, 7)
	};

#undef ANVIL_HELPER

	class Type {
	private:
		union {
			struct {
				uint8_t _type : 2;		// { unsigned, signed, floating point}
				uint8_t _bytes : 3;		// { 1, 2, 4, 8 }
				uint8_t _channels : 3;	// channels - 1
			};
			uint8_t _numeric_value;
		};
	public:
		enum Interpretation {
			TYPE_UNSIGNED,
			TYPE_SIGNED,
			TYPE_FLOATING_POINT
		};

		ANVIL_CONSTEXPR_FN Type() :
			_numeric_value(ANVIL_8UX1)
		{}

		ANVIL_CONSTEXPR_FN Type(const EnumeratedType type) :
			_numeric_value(type)
		{}

		Type(const Interpretation type, const size_t bytes, const size_t channels = 1u) {
			SetInterpretation(type);
			SetSizeInBytes(bytes);
			SetNumberOfChannels(channels);
		}

		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN EnumeratedType GetEnumeratedType() const throw() {
			return static_cast<EnumeratedType>(_numeric_value);
		}

		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN Interpretation GetInterpretation() const throw() {
			return static_cast<Interpretation>(_type);
		}

		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool IsUnsigned() const throw() {
			return _type == TYPE_UNSIGNED;
		}

		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool IsSigned() const throw() {
			return _type == TYPE_SIGNED;
		}

		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool IsFloatingPoint() const throw() {
			return _type == TYPE_FLOATING_POINT;
		}

		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN size_t GetNumberOfChannels() const throw() {
			return _channels + 1u;
		}

		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN size_t GetPrimativeSizeInBytes() const throw() {
			//return std::pow(2u, _bytes);
			return 1u << _bytes;
		}

		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN size_t GetPrimativeSizeInBits() const throw() {
			return GetPrimativeSizeInBytes() * 8u;
		}

		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN size_t GetSizeInBytes() const throw() {
			return GetPrimativeSizeInBytes() * GetNumberOfChannels();
		}

		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN size_t GetSizeInBits() const throw() {
			return GetPrimativeSizeInBytes() * GetNumberOfChannels() * 8u;
		}

		ANVIL_STRONG_INLINE void SetSizeInBytes(const size_t size) {
			ANVIL_RUNTIME_ASSERT(size == 1u || size == 2u || size == 4u || size == 8u, "anvil::Type::SetSizeInBytes : Invalid size (must be 1, 2, 4 or 8 bytes)");
			switch (size) {
			case 1u:
				_bytes = 0u;
				break;
			case 2u:
				_bytes = 1u;
				break;
			case 3u:
				_bytes = 2u;
				break;
			case 4u:
				_bytes = 4u;
				break;
			};
		}

		ANVIL_STRONG_INLINE void SetInterpretation(const Interpretation type) {
			_type = type;
		}

		ANVIL_STRONG_INLINE void SetSizeInBits(const size_t size) {
			SetSizeInBytes(size / 8u);
		}

		ANVIL_STRONG_INLINE void SetNumberOfChannels(const size_t channels) {
			ANVIL_RUNTIME_ASSERT(channels > 0u && channels <= 8u, "anvil::Type::SetNumberOfChannels : Invalid number of channels (must be 1-8)");
			_channels = channels - 1u;
		}

		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool operator==(const Type other) const throw() {
			return _numeric_value == other._numeric_value;
		}

		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool operator!=(const Type other) const throw() {
			return _numeric_value != other._numeric_value;
		}
	};

	static_assert(sizeof(Type) == 1, "Excpected size of anvil::Type to be 1 byte");

	template<class T> struct EnumFromType;
	template<> struct EnumFromType<uint8_t> { static ANVIL_CONSTEXPR_VAR const EnumeratedType value = ANVIL_8UX1; };
	template<> struct EnumFromType<uint16_t> { static ANVIL_CONSTEXPR_VAR const EnumeratedType value = ANVIL_16UX1; };
	template<> struct EnumFromType<uint32_t> { static ANVIL_CONSTEXPR_VAR const EnumeratedType value = ANVIL_32UX1; };
	template<> struct EnumFromType<uint64_t> { static ANVIL_CONSTEXPR_VAR const EnumeratedType value = ANVIL_64UX1; };
	template<> struct EnumFromType<int8_t> { static ANVIL_CONSTEXPR_VAR const EnumeratedType value = ANVIL_8SX1; };
	template<> struct EnumFromType<int16_t> { static ANVIL_CONSTEXPR_VAR const EnumeratedType value = ANVIL_16SX1; };
	template<> struct EnumFromType<int32_t> { static ANVIL_CONSTEXPR_VAR const EnumeratedType value = ANVIL_32SX1; };
	template<> struct EnumFromType<int64_t> { static ANVIL_CONSTEXPR_VAR const EnumeratedType value = ANVIL_64SX1; };
	//template<> struct EnumFromType<float8_t> { static ANVIL_CONSTEXPR_VAR const EnumeratedType value = ANVIL_8FX1; };
	//template<> struct EnumFromType<float16_t> { static ANVIL_CONSTEXPR_VAR const EnumeratedType value = ANVIL_16FX1; };
	template<> struct EnumFromType<float32_t> { static ANVIL_CONSTEXPR_VAR const EnumeratedType value = ANVIL_32FX1; };
	template<> struct EnumFromType<float64_t> { static ANVIL_CONSTEXPR_VAR const EnumeratedType value = ANVIL_64FX1; };

	namespace detail {
		template<class T>
		struct _WideType;

		template<> struct _WideType<uint8_t> { typedef int16_t type; };
		template<> struct _WideType<int8_t> { typedef int16_t type; };
		template<> struct _WideType<uint16_t> { typedef int32_t type; };
		template<> struct _WideType<int16_t> { typedef int32_t type; };
		template<> struct _WideType<uint32_t> { typedef int64_t type; };
		template<> struct _WideType<int32_t> { typedef int32_t type; };
		template<> struct _WideType<uint64_t> { typedef int64_t type; };
		template<> struct _WideType<int64_t> { typedef int64_t type; };
		//template<> struct _WideType<float8_t> { typedef float32_t type; };
		//template<> struct _WideType<float16_t> { typedef float32_t type; };
		template<> struct _WideType<float32_t> { typedef float32_t type; };
		template<> struct _WideType<float64_t> { typedef float64_t type; };
	}

	template<class T>
	using WideType = typename detail::_WideType<T>::type;

	namespace detail {
		template<size_t BYTES>
		struct ReinterpretType_;

		template<>
		struct ReinterpretType_<1u> {
			typedef uint8_t unsigned_t;
			typedef int8_t signed_t;
			//typedef float8_t float_t;
		};

		template<>
		struct ReinterpretType_<2u> {
			typedef uint16_t unsigned_t;
			typedef int16_t signed_t;
			//typedef float16_t float_t;
		};

		template<>
		struct ReinterpretType_<4u> {
			typedef uint32_t unsigned_t;
			typedef int32_t signed_t;
			typedef float32_t float_t;
		};

		template<>
		struct ReinterpretType_<8u> {
			typedef uint64_t unsigned_t;
			typedef int64_t signed_t;
			typedef float64_t float_t;
		};
	}

	template<class T>
	using UnsignedType = typename detail::ReinterpretType_<sizeof(T)>::unsigned_t;

	template<class T>
	using SignedType = typename detail::ReinterpretType_<sizeof(T)>::signed_t;

	template<class T>
	using FloatType = typename detail::ReinterpretType_<sizeof(T)>::float_t;
}

#endif