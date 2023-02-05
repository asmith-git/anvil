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

	union Base64Helper {
		uint32_t u32;
		uint8_t u8[4u];
		struct {
			uint32_t u6_0 : 6;
			uint32_t u6_1 : 6;
			uint32_t u6_2 : 6;
			uint32_t u6_3 : 6;
		};
	};

	// Base64

	const char* const Base64::GetDefaultTable() {
		return g_default_base64_table;
	}

	void Base64::Encode(const uint8_t* src, size_t bytes_in, char* dst, size_t& dst_len, const char* const table, char padding) {
		Base64Helper helper;
		helper.u32 = 0u;

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

		helper.u32 = 0u;
		if (bytes_in >= 2u) {
			helper.u8[0u] = src[0u];
			helper.u8[1u] = src[1u];
			src += 2u;
			bytes_in -= 2u;

			dst[0u] = table[helper.u6_0];
			dst[1u] = table[helper.u6_1];
			dst[2u] = table[helper.u6_2];
			dst[3u] = table[helper.u6_3];
			dst[4u] = padding;

			dst += 5u;
			dst_len += 5u;

		} else if (bytes_in >= 1u) {
			helper.u8[0u] = src[0u];
			src += 1u;
			bytes_in -= 1u;

			dst[0u] = table[helper.u6_0];
			dst[1u] = table[helper.u6_1];
			dst[2u] = table[helper.u6_2];
			dst[3u] = table[helper.u6_3];
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

	template<bool DEFAULT_TABLE>
	void Base64Decode(const char* src, size_t src_len, uint8_t* dst, size_t& bytes_out, const char* const table, char padding) {
		Base64Helper helper;
		helper.u32 = 0u;

		bytes_out = 0u;

		size_t padded_bytes = 0u;
		if (src[src_len - 1] == padding) ++padded_bytes;
		if (src[src_len - 2] == padding) ++padded_bytes;

		if (padded_bytes == 2u) {
			src_len -= 6u;

		} else if (padded_bytes == 1u) {
			src_len -= 5u;
		}

		const auto DecodeChar = [table](const char c)->uint32_t {
			if ANVIL_CONSTEXPR_FN(DEFAULT_TABLE) {
				if (c >= 'A' && c <= 'Z') return c - 'A';
				if (c >= 'a' && c <= 'z') return (c - 'a') + 26;
				if (c >= '0' && c <= '9') return (c - '0') + 52;
				else if (c == '+') return 62;
				return 63;
			} else {
				uint32_t i = 0u;
				for (i; i < 64; ++i) if (c == table[i]) break;
				return i;
			}
		};

		while (src_len >= 4u) {

			helper.u6_0 = DecodeChar(src[0u]);
			helper.u6_1 = DecodeChar(src[1u]);
			helper.u6_2 = DecodeChar(src[2u]);
			helper.u6_3 = DecodeChar(src[3u]);
			src += 4u;
			src_len -= 4u;

			dst[0u] = helper.u8[0u];
			dst[1u] = helper.u8[1u];
			dst[2u] = helper.u8[2u];
			dst += 3u;
			bytes_out += 3u;
		}

		if (padded_bytes > 0u) {

			helper.u6_0 = DecodeChar(src[0u]);
			helper.u6_1 = DecodeChar(src[1u]);
			helper.u6_2 = DecodeChar(src[2u]);
			helper.u6_3 = DecodeChar(src[3u]);
			src += 4u;
			src_len -= 4u;

			if (padded_bytes == 1u) {
				dst[0u] = helper.u8[0u];
				dst[1u] = helper.u8[1u];
				dst += 2u;
				bytes_out += 2u;

			} else if (padded_bytes == 2u) {
				dst[0u] = helper.u8[0u];
				dst += 1u;
				bytes_out += 1u;
			}
		}
	}

	void Base64::Decode(const char* src, size_t src_len, uint8_t* dst, size_t& bytes_out, const char* const table, char padding) {
		if (table == g_default_base64_table) {
			Base64Decode<true>(src, src_len, dst, bytes_out, table, padding);
		} else {
			Base64Decode<false>(src, src_len, dst, bytes_out, table, padding);
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