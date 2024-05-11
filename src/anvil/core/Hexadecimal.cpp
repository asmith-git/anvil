//Copyright 2023 Adam G. Smith
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

#include "anvil/core/Hexadecimal.hpp"
#include "anvil/core/Keywords.hpp"

namespace anvil 
{
	// ---- Utility Functions ----

	static char ToHex(uint32_t nybble) 
	{
		return static_cast<char>(nybble <= 9 ?
			'0' + nybble :
			'A' + (nybble - 10));
	}

	static inline void ToHex(uint32_t byte, char* out)
	{
		out[0u] = ToHex(byte >> 4u);
		out[1u] = ToHex(byte & 15u);
	}

	static uint32_t HexNybbleToBin(char hex)
	{
		if (hex >= '0' && hex <= '9')
		{
			return hex - '0';
		}
		else
		{
			const char sub = hex >= 'A' && hex <= 'Z' ? 'A' : 'a';
			return (hex - sub) + 10;
		}
	}

	// ---- Hexadecimal ----

	void Hexadecimal::Encode(const uint8_t* src, size_t bytes_in, char* dst, size_t& dst_len) 
	{
		// If no bytes to encode
		if (src == nullptr || bytes_in == 0u)
		{
			dst_len = 0u;
			return;
		}

		// Prevent a buffer overflow when writing to dst
		if (dst_len != 0u) bytes_in = std::min(bytes_in, dst_len / 2u);

		// Convert to hexadecimal
		for (size_t i = 0u; i < bytes_in; ++i) 
		{
			ToHex(src[i], dst);
			dst += 2u;
		}

		// Output the number of bytes written
		dst_len = bytes_in * 2u;
	}

	void Hexadecimal::Encode(const uint8_t* src, size_t bytes_in, char* dst)
	{
		size_t bytes_encoded = 0u;
		Encode(src, bytes_in, dst, bytes_encoded);
	}

	void Hexadecimal::Decode(const char* src, size_t src_len, uint8_t* dst, size_t& bytes_out) 
	{
		// Handle empty string
		if (src == nullptr)
		{
	NO_BYTES_OUT:
			bytes_out = 0u;
			return;
		}

		// Call strlen if required
		if (src_len == 0u) 
		{
			src_len = strlen(src);

			// If length is still zero then return
			if (src_len == 0u) goto NO_BYTES_OUT;
		}

		// Output the number of bytes that will be written
		bytes_out = src_len / 2u;

		// Convert from hexadecimal
		for (size_t i = 0u; i < bytes_out; ++i) 
		{
			*dst = static_cast<uint8_t>(HexNybbleToBin(src[1u]) | (HexNybbleToBin(src[0u]) << 4u));

			src += 2u;
			++dst;
		}
	}

	void Hexadecimal::Decode(const char* src, size_t src_len, uint8_t* dst)
	{
		size_t bytes_decoded = 0u;
		Decode(src, src_len, dst, bytes_decoded);
	}

	std::string Hexadecimal::Encode(const uint8_t* src, size_t bytes_in) 
	{
		// Allocate the string
		std::string tmp(bytes_in * 2u, ' ');

		// Do the conversion and return the result
		Encode(src, bytes_in, const_cast<char*>(tmp.c_str()));
		return tmp;
	}

	std::vector<uint8_t> Hexadecimal::Decode(const char* src, size_t src_len) 
	{
		// Allocate the outoput data
		std::vector<uint8_t> tmp(src_len / 2);

		// Do the conversion and return the result
		Decode(src, src_len, tmp.data());
		return tmp;
	}

}