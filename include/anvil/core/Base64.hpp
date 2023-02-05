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

#ifndef ANVIL_CORE_BASE64_HPP
#define ANVIL_CORE_BASE64_HPP

#include <cstdint>

namespace anvil {
	struct Base64 {
		static const char* const GetDefaultTable();

		static void Encode(const uint8_t* src, size_t bytes_in, char* dst, size_t& dst_len, const char* const table = GetDefaultTable(), char padding = '=');
		static void Decode(const char* src, size_t src_len, uint8_t* dst, size_t& bytes_out, const char* const table = GetDefaultTable(), char padding = '=');
	};
}

#endif