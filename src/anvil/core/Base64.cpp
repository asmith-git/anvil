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

#include "anvil/core/Base64.hpp"
#include "anvil/core/Keywords.hpp"

namespace anvil {

	static ANVIL_CONSTEXPR_VAR const char* const g_default_base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	static const ANVIL_CONSTEXPR_VAR uint8_t g_default_base64_reverse_table[] = { //!< Convert from ASCII to indices in g_default_base64_table
		0,      0,      0,      0,      0,      0,      0,      0,
		0,      0,      0,      0,      0,      0,      0,		0,
		0,      0,      0,      0,      0,      0,      0,      0,      
		0,      0,      0,      0,      0,      0,		0,      0,      
		0,      0,      0,      0,      0,      0,      0,      0,      
		0,      0,      0,      62,     0,		0,      0,      63,     
		52,     53,     54,     55,     56,     57,     58,     59,     
		60,     61,     0,      0,     0,       0,      0,      0,      
		0,      0,      1,      2,      3,      4,      5,      6,      
		7,      8,      9,     10,      11,     12,     13,     14,     
		15,     16,     17,     18,     19,     20,     21,     22,     
		23,     24,		25,      0,      0,      0,      0,      0,     
		0,      26,     27,     28,     29,     30,     31,     32,     
		33,		34,     35,     36,     37,     38,     39,     40,     
		41,     42,     43,     44,     45,     46,     47,     48,    
		49,     50,     51,     0,      0,      0,      0,      0,      
		0,      0,      0,      0,      0,      0,      0,		0,       
		0,      0,      0,      0,      0,      0,      0,      0,      
		0,      0,      0,      0,      0,      0,		0,      0,      
		0,      0,      0,      0,      0,      0,      0,      0,      
		0,      0,      0,      0,      0,		0,      0,		0,      
		0,      0,      0,      0,      0,      0,      0,      0,      
		0,      0,      0,      0,		0,      0,      0,      0,      
		0,      0,      0,      0,      0,      0,      0,      0,      
		0,      0,      0,		0,      0,      0,      0,      0,      
		0,      0,      0,      0,      0,      0,      0,      0,      
		0,      0,		0,      0,      0,      0,      0,      0,      
		0,      0,      0,      0,      0,      0,      0,      0,      
		0,		0,      0,     0,      0,      0,      0,      0,      
		0,      0,      0,      0,      0,      0,      0,      0,     
		0,      0,      0,      0,      0,      0,      0,      0,     
		0,      0,      0,      0,      0,      0,      0,		0
	};

	// Base64

	const char* const Base64::GetDefaultTable() {
		return g_default_base64_table;
	}

	union Bits {
		uint32_t u32;
		uint8_t u8[4];
		struct {
			uint32_t _0 : 6u;
			uint32_t _1 : 6u;
			uint32_t _2 : 6u;
			uint32_t _3 : 6u;
			uint32_t _4 : 6u;
		} u6;
	};

	static_assert(sizeof(Bits) == 4u, "Expected Base64::Encode::Bits to be 4 bytes");
	static_assert(offsetof(Bits, u32) == 0u, "Expected offset of Base64::Encode::Bits::u8 to be 0");
	static_assert(offsetof(Bits, u8) == 0u, "Expected offset of Base64::Encode::Bits::u8 to be 0");
	static_assert(offsetof(Bits, u6) == 0u, "Expected offset of Base64::Encode::Bits::u6 to be 0");

	void Base64::Encode(const uint8_t* src, size_t bytes_in, char* dst, size_t& dst_len, const char* const table, char padding) {
		dst_len = 0u;

		Bits bits;

		while (bytes_in >= 3u) {
			bits.u32 = 0u;
			bits.u8[0u] = src[2u];
			bits.u8[1u] = src[1u];
			bits.u8[2u] = src[0u];
			src += 3u;
			bytes_in -= 3u;

			dst[0u] = table[bits.u6._3];
			dst[1u] = table[bits.u6._2];
			dst[2u] = table[bits.u6._1];
			dst[3u] = table[bits.u6._0];
			dst += 4u;
			dst_len += 4u;
		}

		if (bytes_in >= 2u) {
			bits.u32 = 0u;
			bits.u8[0u] = src[1u];
			bits.u8[1u] = src[0u];
			src += 2u;
			bytes_in -= 2u;

			dst[0u] = table[bits.u6._3];
			dst[1u] = table[bits.u6._2];
			dst[2u] = table[bits.u6._1];
			dst[3u] = table[bits.u6._0];
			dst[4u] = padding;

			dst += 5u;
			dst_len += 5u;

		} else if (bytes_in >= 1u) {
			bits.u32 = 0u;
			bits.u8[0u] = src[0u];
			src += 1u;
			bytes_in -= 1u;

			dst[0u] = table[bits.u6._3];
			dst[1u] = table[bits.u6._2];
			dst[2u] = table[bits.u6._1];
			dst[3u] = table[bits.u6._0];
			dst[4u] = padding;
			dst[5u] = padding;

			dst += 6u;
			dst_len += 6u;
		}

		*dst = '\0';
	}

	static size_t CheckSize(const char* src, size_t src_len, char padding) {
		size_t padded_bytes = 0u;
		if (src[src_len - 1] == padding) ++padded_bytes;
		if (src[src_len - 2] == padding) ++padded_bytes;

		if (padded_bytes == 2u) {
			src_len -= 6u;

		} else if (padded_bytes == 1u) {
			src_len -= 5u;
		}	
		
		size_t s = (src_len / 4u) * 3u;
		if (padded_bytes == 2u) s += 1u;
		else if (padded_bytes == 1u) s += 2u;

		return s;
	}

	void Base64::Decode(const char* src, size_t src_len, uint8_t* dst, size_t& bytes_out, const char* const table, char padding) {
		uint8_t stack_table[256u];

		const uint8_t* reverse_table;
		if (table == g_default_base64_table) {
			reverse_table = g_default_base64_reverse_table;

		} else {
			// For each possible ASCII character
			for (size_t c = 0u; c < 256u; ++c) {
				// Look for the character in the table
				for (uint32_t j = 0; j < 64u; ++j) if (c == table[j]) {
					// Put the table index into the lookup table for this character
					stack_table[c] = static_cast<uint8_t>(j);
					goto NEXT_CHAR;
				}
				stack_table[c] = 0;
NEXT_CHAR:
				continue;
			}
			reverse_table = stack_table;
		}

		bytes_out = 0u;

		size_t padded_bytes = 0u;
		if (src[src_len - 1] == padding) ++padded_bytes;
		if (src[src_len - 2] == padding) ++padded_bytes;

		if (padded_bytes == 2u) {
			src_len -= 6u;

		} else if (padded_bytes == 1u) {
			src_len -= 5u;
		}

		Bits bits;

		while (src_len >= 4u) {

			bits.u32 = 0;
			bits.u6._3 = reverse_table[src[0u]];
			bits.u6._2 = reverse_table[src[1u]];
			bits.u6._1 = reverse_table[src[2u]];
			bits.u6._0 = reverse_table[src[3u]];

			src += 4u;
			src_len -= 4u;

			dst[2u] = bits.u8[0u];
			dst[1u] = bits.u8[1u];
			dst[0u] = bits.u8[2u];
			dst += 3u;
			bytes_out += 3u;
		}

		if (padded_bytes > 0u) {

			bits.u32 = 0;
			bits.u6._3 = reverse_table[src[0u]];
			bits.u6._2 = reverse_table[src[1u]];
			bits.u6._1 = reverse_table[src[2u]];
			bits.u6._0 = reverse_table[src[3u]];

			src += 4u;
			src_len -= 4u;

			if (padded_bytes == 1u) {
				dst[0u] = bits.u8[1u];
				dst[1u] = bits.u8[0u];
				dst += 2u;
				bytes_out += 2u;

			} else if (padded_bytes == 2u) {
				dst[0u] = bits.u8[0u];
				dst += 1u;
				bytes_out += 1u;
			}
		}
	}

	std::string Base64::Encode(const uint8_t* src, size_t bytes_in, const char* const table, char padding) {
		std::string tmp;
		tmp.resize((bytes_in / 3u) * 4u + 6u);
		size_t buf_len = 0u;
		Encode(src, bytes_in, const_cast<char*>(tmp.c_str()), buf_len, table, padding);
		while (tmp.size() > buf_len) tmp.pop_back(); //! \todo Calculate the size correctly so this isn't needed
		return tmp;
	}

	std::vector<uint8_t> Base64::Decode(const char* src, size_t src_len, const char* const table, char padding) {
		std::vector<uint8_t> tmp(CheckSize(src, src_len, padding));
		size_t bytes_out = 0u;
		Decode(src, src_len, tmp.data(), bytes_out, table, padding);
		return tmp;
	}

}