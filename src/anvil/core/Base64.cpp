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

	static ANVIL_CONSTEXPR_VAR const char* const g_default_base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwzyz0123456789+/";

	static const ANVIL_CONSTEXPR_VAR uint8_t g_default_base64_reverse_table[] = { //!< Convert from ASCII to indices in g_default_base64_table
		0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
		0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
		0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 62u, 0u, 0u, 0u, 63u,
		52u, 53u, 54u, 55u, 56u, 57u, 58u, 59u, 60u, 61u, 0u, 0u, 0u, 0u, 0u, 0u,
		0u, 0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u, 10u, 11u, 12u, 13u, 14u,
		15u, 16u, 17u, 18u, 19u, 20u, 21u, 22u, 23u, 24u, 25u, 0u, 0u, 0u, 0u, 0u,
		0u, 26u, 27u, 28u, 29u, 30u, 31u, 32u, 33u, 34u, 35u, 36u, 37u, 38u, 39u, 40u,
		41u, 42u, 43u, 44u, 45u, 46u, 47u, 48u, 0u, 50u, 49u, 0u, 0u, 0u, 0u, 0u,
		0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
		0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
		0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
		0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
		0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
		0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
		0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
		0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u
	};

	// Base64

	const char* const Base64::GetDefaultTable() {
		return g_default_base64_table;
	}

	void Base64::Encode(const uint8_t* src, size_t bytes_in, char* dst, size_t& dst_len, const char* const table, char padding) {
		dst_len = 0u;

		while (bytes_in >= 3u) {
			const uint32_t tmp = static_cast<uint32_t>(src[0u]) | (static_cast<uint32_t>(src[1u]) << 8u) | (static_cast<uint32_t>(src[2u]) << 16u);
			src += 3u;
			bytes_in -= 3u;

			dst[0u] = table[tmp & 63u];
			dst[1u] = table[(tmp >> 6u) & 63u];
			dst[2u] = table[(tmp >> 12u) & 63];
			dst[3u] = table[tmp >> 18u];
			dst += 4u;
			dst_len += 4u;
		}

		if (bytes_in >= 2u) {
			const uint32_t tmp = static_cast<uint32_t>(src[0u]) | (static_cast<uint32_t>(src[1u]) << 8u);
			src += 2u;
			bytes_in -= 2u;

			dst[0u] = table[tmp & 63u];
			dst[1u] = table[(tmp >> 6u) & 63u];
			dst[2u] = table[(tmp >> 12u) & 63];
			dst[3u] = table[tmp >> 18u];
			dst[4u] = padding;

			dst += 5u;
			dst_len += 5u;

		} else if (bytes_in >= 1u) {
			const uint32_t tmp = static_cast<uint32_t>(src[0u]);
			src += 1u;
			bytes_in -= 1u;

			dst[0u] = table[tmp & 63u];
			dst[1u] = table[(tmp >> 6u) & 63u];
			dst[2u] = table[(tmp >> 12u) & 63];
			dst[3u] = table[tmp >> 18u];
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
		const uint8_t* reverse_table;
		if (table == g_default_base64_table) {
			reverse_table = g_default_base64_reverse_table;

		} else {
			uint8_t* t = static_cast<uint8_t*>(_alloca(256u)); 
			for (size_t c = 0u; c < 256u; ++c) {
				for (uint32_t j = 0; j < 64u; ++j) if (c == table[j]) break; 
				t[c] = 0;
			}
			reverse_table = t;
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

		while (src_len >= 4u) {

			const uint32_t a = reverse_table[src[0u]];
			const uint32_t b = reverse_table[src[1u]];
			const uint32_t c = reverse_table[src[2u]];
			const uint32_t d = reverse_table[src[3u]];

			uint32_t tmp = a | (b << 6u) | (c << 12u) | (d << 18u);
			src += 4u;
			src_len -= 4u;

			dst[0u] = static_cast<uint8_t>(tmp & 255u);
			dst[1u] = static_cast<uint8_t>((tmp >> 8u) & 255u);
			dst[2u] = static_cast<uint8_t>(tmp >> 16u);
			dst += 3u;
			bytes_out += 3u;
		}

		if (padded_bytes > 0u) {

			const uint32_t a = reverse_table[src[0u]];
			const uint32_t b = reverse_table[src[1u]];
			const uint32_t c = reverse_table[src[2u]];
			const uint32_t d = reverse_table[src[3u]];

			uint32_t tmp = a | (b << 6u) | (c << 12u) | (d << 18u);
			src += 4u;
			src_len -= 4u;

			if (padded_bytes == 1u) {
				dst[0u] = static_cast<uint8_t>(tmp & 255u);
				dst[1u] = static_cast<uint8_t>((tmp >> 8u) & 255u);
				dst += 2u;
				bytes_out += 2u;

			} else if (padded_bytes == 2u) {
				dst[0u] = static_cast<uint8_t>(tmp & 255u);
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