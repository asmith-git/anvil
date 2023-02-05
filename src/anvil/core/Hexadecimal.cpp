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

namespace anvil {

	static char ToHex(uint32_t nybble) {
		return nybble <= 9 ?
			'0' + nybble :
			'A' + (nybble - 10);
	}

	static inline void ToHex(uint32_t byte, char* out) {
		out[0u] = ToHex(byte & 15u);
		out[1u] = ToHex(byte >> 4u);
	}

	static uint32_t HexNybbleToBin(char hex) {
		if (hex >= '0' && hex <= '9') {
			return hex - '0';
		} else if (hex >= 'A' && hex <= 'Z') {
			return (hex - 'A') + 10;
		} else {
			return (hex - 'a') + 10;
		}
	}

	// Hexadecimal

	void Hexadecimal::Encode(const uint8_t* src, size_t bytes_in, char* dst, size_t& dst_len) {
		for (size_t i = 0u; i < bytes_in; ++i) {
			ToHex(src[i], dst);
			dst += 2u;
		}
		dst_len = bytes_in * 2u;
	}

	void Hexadecimal::Decode(const char* src, size_t src_len, uint8_t* dst, size_t& bytes_out) {
		bytes_out = src_len / 2u;
		for (size_t i = 0u; i < bytes_out; ++i) {
			*dst = static_cast<uint32_t>(HexNybbleToBin(src[0u]) | (HexNybbleToBin(src[1u]) << 4u));

			src += 2u;
			++dst;
		}
	}

	std::string Hexadecimal::Encode(const uint8_t* src, size_t bytes_in) {
		char* buf = static_cast<char*>(_alloca(bytes_in * 2));
		size_t buf_len = 0u;
		Encode(src, bytes_in, buf, buf_len);
		return std::string(buf, buf + buf_len);
	}

	std::vector<uint8_t> Hexadecimal::Decode(const char* src, size_t src_len) {
		std::vector<uint8_t> tmp(src_len / 2);
		size_t bytes_out = 0u;
		Decode(src, src_len, tmp.data(), bytes_out);
		return tmp;
	}

}