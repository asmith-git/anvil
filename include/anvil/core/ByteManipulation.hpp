//Copyright 2024 Adam G. Smith
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

#ifndef ANVIL_BYTE_MANIPULATION_HPP
#define ANVIL_BYTE_MANIPULATION_HPP

#include "anvil/core/Keywords.hpp"

namespace anvil {

	// ---- ExtractByte ----

	template<size_t I>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint8_t ExtractByte(uint16_t value);

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint8_t ExtractByte<0u>(uint16_t value)
	{
		return static_cast<uint8_t>(value & 255u);
	}

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint8_t ExtractByte<1u>(uint16_t value)
	{
		return static_cast<uint8_t>(value >> 8u);
	}

	template<size_t I>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint8_t ExtractByte(uint32_t value);

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint8_t ExtractByte<0u>(uint32_t value)
	{
		return static_cast<uint8_t>(value & 255u);
	}

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint8_t ExtractByte<1u>(uint32_t value)
	{
		return static_cast<uint8_t>((value >> 8u) & 255u);
	}

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint8_t ExtractByte<2u>(uint32_t value)
	{
		return static_cast<uint8_t>((value >> 16u) & 255u);
	}

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint8_t ExtractByte<3u>(uint32_t value)
	{
		return static_cast<uint8_t>(value >> 24u);
	}

	template<size_t I>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint8_t ExtractByte(uint64_t value);

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint8_t ExtractByte<0u>(uint64_t value)
	{
		return static_cast<uint8_t>(value & 255ull);
	}

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint8_t ExtractByte<1u>(uint64_t value)
	{
		return static_cast<uint8_t>((value >> 8ull) & 255ull);
	}

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint8_t ExtractByte<2u>(uint64_t value)
	{
		return static_cast<uint8_t>((value >> 16ull) & 255ull);
	}

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint8_t ExtractByte<3u>(uint64_t value)
	{
		return static_cast<uint8_t>((value >> 24ull) & 255ull);
	}

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint8_t ExtractByte<4u>(uint64_t value)
	{
		return static_cast<uint8_t>((value >> 32ull) & 255ull);
	}

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint8_t ExtractByte<5u>(uint64_t value)
	{
		return static_cast<uint8_t>((value >> 40ull) & 255ull);
	}

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint8_t ExtractByte<6u>(uint64_t value)
	{
		return static_cast<uint8_t>((value >> 48ull) & 255ull);
	}

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint8_t ExtractByte<7u>(uint64_t value)
	{
		return static_cast<uint8_t>(value >> 56ull);
	}

	// ---- Signed Integers ----

	template<size_t I>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint8_t ExtractByte(int16_t value)
	{
		return ExtractByte<I>(*reinterpret_cast<uint16_t*>(&value));
	}

	template<size_t I>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint8_t ExtractByte(int32_t value)
	{
		return ExtractByte<I>(*reinterpret_cast<uint32_t*>(&value));
	}

	template<size_t I>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint8_t ExtractByte(int64_t value)
	{
		return ExtractByte<I>(*reinterpret_cast<uint64_t*>(&value));
	}

	// ---- InsertByte ----

	template<size_t I>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint16_t InsertByte(uint16_t value, uint8_t byte);

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint16_t InsertByte<0u>(uint16_t value, uint8_t byte)
	{
		enum { MASK = ~255u };
		value &= MASK;
		value |= static_cast<uint16_t>(byte);
		return value;
	}

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint16_t InsertByte<1u>(uint16_t value, uint8_t byte)
	{
		enum { MASK = ~(255u << 8u) };
		value &= MASK;
		value |= static_cast<uint16_t>(byte) << 8u;
		return value;
	}

	template<size_t I>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint32_t InsertByte(uint32_t value, uint8_t byte);

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint32_t InsertByte<0u>(uint32_t value, uint8_t byte)
	{
		enum : uint32_t { MASK = ~255u };
		value &= MASK;
		value |= static_cast<uint32_t>(byte);
		return value;
	}

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint32_t InsertByte<1u>(uint32_t value, uint8_t byte)
	{
		enum : uint32_t { MASK = ~(255u << 8u) };
		value &= MASK;
		value |= static_cast<uint32_t>(byte) << 8u;
		return value;
	}

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint32_t InsertByte<2u>(uint32_t value, uint8_t byte)
	{
		enum : uint32_t { MASK = ~(255u << 16u) };
		value &= MASK;
		value |= static_cast<uint32_t>(byte) << 16u;
		return value;
	}

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint32_t InsertByte<3u>(uint32_t value, uint8_t byte)
	{
		enum : uint32_t { MASK = ~(255u << 24u) };
		value &= MASK;
		value |= static_cast<uint32_t>(byte) << 24u;
		return value;
	}

	template<size_t I>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint64_t InsertByte(uint64_t value, uint8_t byte);

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint64_t InsertByte<0u>(uint64_t value, uint8_t byte)
	{
		enum : uint64_t { MASK = ~255ull };
		value &= MASK;
		value |= static_cast<uint64_t>(byte);
		return value;
	}

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint64_t InsertByte<1u>(uint64_t value, uint8_t byte)
	{
		enum : uint64_t { MASK = ~(255llu << 8ull) };
		value &= MASK;
		value |= static_cast<uint64_t>(byte) << 8ull;
		return value;
	}

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint64_t InsertByte<2u>(uint64_t value, uint8_t byte)
	{
		enum : uint64_t { MASK = ~(255llu << 16ull) };
		value &= MASK;
		value |= static_cast<uint64_t>(byte) << 16ull;
		return value;
	}

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint64_t InsertByte<3u>(uint64_t value, uint8_t byte)
	{
		enum : uint64_t { MASK = ~(255llu << 24ull) };
		value &= MASK;
		value |= static_cast<uint64_t>(byte) << 24ull;
		return value;
	}

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint64_t InsertByte<4u>(uint64_t value, uint8_t byte)
	{
		enum : uint64_t { MASK = ~(255llu << 32ull) };
		value &= MASK;
		value |= static_cast<uint64_t>(byte) << 32ull;
		return value;
	}

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint64_t InsertByte<5u>(uint64_t value, uint8_t byte)
	{
		enum : uint64_t { MASK = ~(255ull << 40ull) };
		value &= MASK;
		value |= static_cast<uint64_t>(byte) << 40ull;
		return value;
	}

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint64_t InsertByte<6u>(uint64_t value, uint8_t byte)
	{
		enum : uint64_t { MASK = ~(255ull << 48ull) };
		value &= MASK;
		value |= static_cast<uint64_t>(byte) << 48ull;
		return value;
	}

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint64_t InsertByte<7u>(uint64_t value, uint8_t byte)
	{
		enum : uint64_t { MASK = ~(255ull << 56ull) };
		value &= MASK;
		value |= static_cast<uint64_t>(byte) << 56ull;
		return value;
	}

	// ---- Signed Integers ----

	template<size_t I>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE int16_t InsertByte(int16_t value, uint8_t byte)
	{
		return InsertByte<I>(*reinterpret_cast<uint16_t*>(&value), byte);
	}

	template<size_t I>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE int32_t InsertByte(int32_t value, uint8_t byte)
	{
		return InsertByte<I>(*reinterpret_cast<uint32_t*>(&value), byte);
	}

	template<size_t I>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE int64_t InsertByte(int64_t value, uint8_t byte)
	{
		return InsertByte<I>(*reinterpret_cast<uint64_t*>(&value), byte);
	}

	// ---- ConcatenateBytes ----

	template<class T>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE T ConcatenateBytes(uint8_t a, uint8_t b);

	template<class T>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE T ConcatenateBytes(uint8_t a, uint8_t b, uint8_t c, uint8_t d);

	template<class T>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE T ConcatenateBytes(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e, uint8_t f, uint8_t g, uint8_t h);

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint16_t ConcatenateBytes<uint16_t>(uint8_t a, uint8_t b)
	{
		return static_cast<uint16_t>(a) | (static_cast<uint16_t>(b) << 8u);
	}

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint32_t ConcatenateBytes<uint32_t>(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
	{
		return static_cast<uint16_t>(a) | (static_cast<uint16_t>(b) << 8u) | (static_cast<uint16_t>(c) << 16u) | (static_cast<uint16_t>(d) << 24u);
	}

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE uint64_t ConcatenateBytes<uint64_t>(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e, uint8_t f, uint8_t g, uint8_t h)
	{
		uint64_t lo = ConcatenateBytes<uint32_t>(a, b, c, d);
		uint64_t hi = ConcatenateBytes<uint32_t>(e, f, g, h);
		return lo | (hi << 32ull);
	}

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE int16_t ConcatenateBytes<int16_t>(uint8_t a, uint8_t b)
	{
		return static_cast<int16_t>(a) | (static_cast<int16_t>(b) << 8);
	}

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE int32_t ConcatenateBytes<int32_t>(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
	{
		return static_cast<int16_t>(a) | (static_cast<int16_t>(b) << 8) | (static_cast<int16_t>(c) << 16) | (static_cast<int16_t>(d) << 24);
	}

	template<>
	ANVIL_CONSTEXPR_FN ANVIL_STRONG_INLINE int64_t ConcatenateBytes<int64_t>(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e, uint8_t f, uint8_t g, uint8_t h)
	{
		int64_t lo = ConcatenateBytes<int32_t>(a, b, c, d);
		int64_t hi = ConcatenateBytes<int32_t>(e, f, g, h);
		return lo | (hi << 32ll);
	}

}

#endif