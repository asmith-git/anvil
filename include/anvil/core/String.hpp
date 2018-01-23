//Copyright 2017 Adam G. Smith
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

#ifndef ANVIL_CORE_STRING_HPP
#define ANVIL_CORE_STRING_HPP

#include "anvil/core/Keywords.hpp"

namespace anvil {
	bool ANVIL_CALL IsUpperCase(char) throw();
	bool ANVIL_CALL IsLowerCase(char) throw();
	bool ANVIL_CALL IsLetter(char) throw();
	bool ANVIL_CALL IsNumber(char) throw();
	char ANVIL_CALL ToUpperCase(char) throw();
	char ANVIL_CALL ToLowerCase(char) throw();

	bool ANVIL_CALL IsUpperCase(const char*) throw();
	bool ANVIL_CALL IsLowerCase(const char*) throw();
	bool ANVIL_CALL IsLetter(const char*) throw();
	bool ANVIL_CALL IsNumber(const char*) throw();
	void ANVIL_CALL ToUpperCase(const char*, char*) throw();
	void ANVIL_CALL ToLowerCase(const char*, char*) throw();

	bool ANVIL_CALL IsUpperCase(const char*, size_t) throw();
	bool ANVIL_CALL IsLowerCase(const char*, size_t) throw();
	bool ANVIL_CALL IsLetter(const char*, size_t) throw();
	bool ANVIL_CALL IsNumber(const char*, size_t) throw();
	void ANVIL_CALL ToUpperCase(const char*, char*, size_t) throw();
	void ANVIL_CALL ToLowerCase(const char*, char*, size_t) throw();
}

#endif