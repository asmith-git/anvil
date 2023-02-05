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
			helper.u8[0u] = src[0u];
			helper.u8[1u] = src[1u];
			helper.u8[2u] = src[2u];
			src += 3u;
			bytes_in -= 3u;

			dst[0u] = table[helper.u6_0];
			dst[1u] = table[helper.u6_1];
			dst[2u] = table[helper.u6_2];
			dst[3u] = table[helper.u6_3];

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

	void Base64::Decode(const char* src, size_t src_len, uint8_t* dst, size_t& bytes_out, const char* const table, char padding) {
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
			uint32_t i = 0u;
			for (i; i < 64; ++i) if (c == table[i]) break;
			return i;
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

}