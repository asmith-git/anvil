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

#ifndef ANVIL_CORE_HEX_HPP
#define ANVIL_CORE_HEX_HPP

#include <cstdint>
#include <vector>
#include <string>

namespace anvil {
	struct Hexadecimal {
		static void Encode(const uint8_t* src, size_t bytes_in, char* dst, size_t& dst_len);
		static void Decode(const char* src, size_t src_len, uint8_t* dst, size_t& bytes_out);

		static std::string Encode(const uint8_t* src, size_t bytes_in);
		static std::vector<uint8_t> Decode(const char* src, size_t src_len);
	};
}

#endif