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
#include "anvil/core/Popcount.hpp"
#include "anvil/core/LeadingZeroCount.hpp"

// Primitive Types

namespace anvil {

#define ANVIL_ENCODE_TYPE_ENUMERATION(TY, BY, CH) (TY | (BY << 3u) | (CH << 4u))

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
		ANVIL_16UX16 =	ANVIL_ENCODE_TYPE_ENUMERATION(0, 2, 15)
		,
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
		ANVIL_64FX16 =	ANVIL_ENCODE_TYPE_ENUMERATION(2, 3, 15)
	};

#undef ANVIL_ENCODE_TYPE_ENUMERATION

	/*!
	*	\class Type
	*	\brief Describes a primative numerical data type.
	*	\detail Data is binary compatible with anvil::EnumeratedType
	*	\author Adam Smith
	*	\date 2017
	*	\see EnumeratedType
	*/
	class Type {
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
		ANVIL_CONSTEXPR_FN Type(const EnumeratedType type) :
			_numeric_value(type)
		{}

		/*!
		*	\brief Create a new type.
		*	\detail Default type will be ANVIL_8UX1
		*/
		ANVIL_CONSTEXPR_FN Type() :
			Type(ANVIL_8UX1)
		{}

		/*!
		*	\brief Create a new type.
		*	\param type How the value is encoded.
		*	\param bytes The size of the value in bytes.
		*	\param channels The number of channels or dimensions.
		*/
		Type(const Representation type, const size_t bytes, const size_t channels = 1u) {
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
			ANVIL_RUNTIME_ASSERT(popcount(size) == 1 && size <= MAX_CHANNEL_BYTES, "anvil::Type::SetSizeInBytes : " + std::to_string(size) + " bytes is an invalid size (must be 1, 2, 4 or 8 bytes)");
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
			ANVIL_RUNTIME_ASSERT(channels >= MIN_CHANNELS && channels <= MAX_CHANNELS, "anvil::Type::SetNumberOfChannels : " + std::to_string(channels) + " is an invalid number of channels (must be 1-16)");
			_channels = channels - 1u;
		}

		/*!
		*	\brief Check if two types are equal.
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool operator==(const Type other) const throw() {
			return _numeric_value == other._numeric_value;
		}

		/*!
		*	\brief Check if two types are not equal.
		*/
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool operator!=(const Type other) const throw() {
			return _numeric_value != other._numeric_value;
		}
	};

	static_assert(sizeof(Type) == 1, "Excpected size of anvil::Type to be 1 byte");

	typedef Type ShortType;

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
#if ANVIL_F8_SUPPORT
		template<> struct _WideType<float8_t> { typedef float32_t type; };
#endif
#if ANVIL_F16_SUPPORT
		template<> struct _WideType<float16_t> { typedef float32_t type; };
#endif
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
#if ANVIL_F8_SUPPORT
			typedef float8_t float_t;
#endif
		};

		template<>
		struct ReinterpretType_<2u> {
			typedef uint16_t unsigned_t;
			typedef int16_t signed_t;
#if ANVIL_F16_SUPPORT
			typedef float16_t float_t;
#endif
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