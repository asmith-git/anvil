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

namespace anvil 
{
	struct ANVIL_DLL_EXPORT Hexadecimal 
	{

		/*!
		*	\brief Convert a block of binary data to hexadecimal.
		*	\details Hexadecimal string will be ASCII using upper case letters.
		*	\param src The binary data to convert.
		*	\param bytes_in The number of bytes to convert.
		*	\param dst The hexideximal characters are output to this location.
		*	\param dst_len Input is the length of dst unless 0, in which case it is ignores. Returns the number of bytes written to dst.
		*/
		static void Encode(const uint8_t* src, size_t bytes_in, char* dst, size_t& dst_len);

		/*!
		*	\brief Convert a block of binary data to hexadecimal.
		*	\details Hexadecimal string will be ASCII using upper case letters.
		*	\param src The binary data to convert.
		*	\param bytes_in The number of bytes to convert.
		*	\param dst The hexideximal characters are output to this location.
		*/
		static void Encode(const uint8_t* src, size_t bytes_in, char* dst);

		/*!
		*	\brief Convert a string of hexadecimal characters to binary.
		*	\param src The string containing hexadecimal characters.
		*	\param src_len The number of hexadecimal characters in src, if 0 then strlen will be called.
		*	\param dst The binary data is output to this location
		*	\param bytes_out Returns the number of bytes written to dst.
		*/
		static void Decode(const char* src, size_t src_len, uint8_t* dst, size_t& bytes_out);

		/*!
		*	\brief Convert a string of hexadecimal characters to binary.
		*	\param src The string containing hexadecimal characters.
		*	\param src_len The number of hexadecimal characters in src, if 0 then strlen will be called.
		*	\param dst The binary data is output to this location
		*/
		static void Decode(const char* src, size_t src_len, uint8_t* dst);

		/*!
		*	\brief Convert a block of binary data to hexadecimal.
		*	\details Hexadecimal string will be ASCII using upper case letters.
		*	\param src The binary data to convert.
		*	\param bytes_in The number of bytes to convert.
		*	\return The hexadecimal string.
		*/
		static std::string Encode(const uint8_t* src, size_t bytes_in);

		/*!
		*	\brief Convert a string of hexadecimal characters to binary.
		*	\param src The string containing hexadecimal characters.
		*	\param src_len The number of hexadecimal characters in src, if 0 then strlen will be called.
		*	\return The binary data.
		*/
		static std::vector<uint8_t> Decode(const char* src, size_t src_len);
	};
}

#endif