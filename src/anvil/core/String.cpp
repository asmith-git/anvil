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

#include "anvil/core/String.hpp"

namespace anvil {
	enum {
		CASE_DIFFERENCE = 'a' - 'A'
	};

	bool ANVIL_CALL IsUpperCase(char aChar) throw() {
		return aChar >= 'A' && aChar <= 'Z';
	}

	bool ANVIL_CALL IsLowerCase(char aChar) throw() {
		return aChar >= 'a' && aChar <= 'z';
	}

	bool ANVIL_CALL IsLetter(char aChar) throw() {
		return IsUpperCase(aChar) || IsLowerCase(aChar);
	}

	bool ANVIL_CALL IsNumber(char aChar) throw() {
		return aChar >= '0' && aChar <= '9';
	}

	char ANVIL_CALL ToUpperCase(char aChar) throw() {
		return aChar - IsLowerCase(aChar) ? CASE_DIFFERENCE : 0;
	}

	char ANVIL_CALL ToLowerCase(char aChar) throw() {
		return aChar + IsUpperCase(aChar) ? CASE_DIFFERENCE : 0;
	}

	bool ANVIL_CALL IsUpperCase(const char* aString) throw() {
		while (*aString != '\0') {
			if (!IsUpperCase(aString)) return false;
			++aString;
		}
		return true;
	}

	bool ANVIL_CALL IsLowerCase(const char* aString) throw() {
		while (*aString != '\0') {
			if (!IsLowerCase(aString)) return false;
			++aString;
		}
		return true;
	}

	bool ANVIL_CALL IsLetter(const char* aString) throw() {
		while (*aString != '\0') {
			if (!IsLetter(aString)) return false;
			++aString;
		}
		return true;
	}

	bool ANVIL_CALL IsNumber(const char* aString) throw() {
		while (*aString != '\0') {
			if (!IsNumber(aString)) return false;
			++aString;
		}
		return true;
	}

	void ANVIL_CALL ToUpperCase(const char* aString, char* aOutput) throw() {
		while (*aString != '\0' && *aOutput != '\0') {
			*aOutput = ToUpperCase(*aString);
			++aString;
			++aOutput;
		}
	}

	void ANVIL_CALL ToLowerCase(const char* aString, char* aOutput) throw() {
		while (*aString != '\0' && *aOutput != '\0') {
			*aOutput = ToLowerCase(*aString);
			++aString;
			++aOutput;
		}
	}

	bool ANVIL_CALL IsUpperCase(const char* aString, size_t aSize) throw() {
		for (size_t i = 0; i < aSize; ++i) {
			if (!IsUpperCase(aString[i])) return false;
		}
		return true;
	}

	bool ANVIL_CALL IsLowerCase(const char* aString, size_t aSize) throw() {
		for (size_t i = 0; i < aSize; ++i) {
			if (!IsLowerCase(aString[i])) return false;
		}
		return true;
	}

	bool ANVIL_CALL IsLetter(const char* aString, size_t aSize) throw() {
		for (size_t i = 0; i < aSize; ++i) {
			if (!IsLetter(aString[i])) return false;
		}
		return true;
	}

	bool ANVIL_CALL IsNumber(const char* aString, size_t aSize) throw() {
		for (size_t i = 0; i < aSize; ++i) {
			if (!IsNumber(aString[i])) return false;
		}
		return true;
	}

	void ANVIL_CALL ToUpperCase(const char* aString, char* aOutput, size_t aSize) throw() {
		for (size_t i = 0; i < aSize; ++i) {
			aOutput[i] = ToUpperCase(aString[i]);
		}
	}

	void ANVIL_CALL ToLowerCase(const char* aString, char* aOutput, size_t aSize) throw() {
		for (size_t i = 0; i < aSize; ++i) {
			aOutput[i] = ToLowerCase(aString[i]);
		}
	}

}