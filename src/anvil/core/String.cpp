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

#include <cstring>
#ifdef ANVIL_SSE2
#include <emmintrin.h>
#endif
#include "anvil/core/String.hpp"

namespace anvil {
	enum {
		CASE_DIFFERENCE = 'a' - 'A'
	};

#ifdef ANVIL_SSE2
	static __m128i _mm_mul_epi8(__m128i a, __m128i b)
	{
		const __m128i x = _mm_mullo_epi16(a, b);
		const __m128i y = _mm_mullo_epi16(_mm_srli_epi16(a, 8), _mm_srli_epi16(b, 8));
		return _mm_or_si128(_mm_slli_epi16(y, 8), _mm_srli_epi16(_mm_slli_epi16(x, 8), 8));
	}
#endif

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
		return IsLowerCase(aChar) ? aChar - CASE_DIFFERENCE : aChar;
	}

	char ANVIL_CALL ToLowerCase(char aChar) throw() {
		return IsUpperCase(aChar) ? aChar + CASE_DIFFERENCE : aChar;
	}

	bool ANVIL_CALL IsUpperCase(const char* aString) throw() {
		while (*aString != '\0') {
			if (!IsUpperCase(*aString)) return false;
			++aString;
		}
		return true;
	}

	bool ANVIL_CALL IsLowerCase(const char* aString) throw() {
		while (*aString != '\0') {
			if (!IsLowerCase(*aString)) return false;
			++aString;
		}
		return true;
	}

	bool ANVIL_CALL IsLetter(const char* aString) throw() {
		while (*aString != '\0') {
			if (!IsLetter(*aString)) return false;
			++aString;
		}
		return true;
	}

	bool ANVIL_CALL IsNumber(const char* aString) throw() {
		while (*aString != '\0') {
			if (!IsNumber(*aString)) return false;
			++aString;
		}
		return true;
	}

	void ANVIL_CALL ToUpperCase(const char* aString, char* aOutput) throw() {
		while (*aString != '\0') {
			*aOutput = ToUpperCase(*aString);
			++aString;
			++aOutput;
		}
	}

	void ANVIL_CALL ToLowerCase(const char* aString, char* aOutput) throw() {
		while (*aString != '\0') {
			*aOutput = ToLowerCase(*aString);
			++aString;
			++aOutput;
		}
	}

	bool ANVIL_CALL IsUpperCase(const char* aString, size_t aSize) throw() {
#ifdef ANVIL_SSE2
		const __m128i low = _mm_set1_epi8('A');
		const __m128i high = _mm_set1_epi8('Z');

		const size_t loops = aSize >> 4;
		const size_t remainder = aSize & 15;
		for (size_t i = 0; i < loops; ++i) {
			const size_t j = i << 4;
			const __m128i in = _mm_load_si128(reinterpret_cast<const __m128i*>(aString + j));
			const __m128i tmp = _mm_or_si128(_mm_cmpgt_epi8(in, high), _mm_cmplt_epi8(in, low));
			if (tmp.m128i_i64[0] | tmp.m128i_i64[1]) return false;
		}
		aString += loops << 4;
		for (size_t i = 0; i < remainder; ++i) if (!IsUpperCase(aString[i])) return false;
		return true;
#else
		for (size_t i = 0; i < aSize; ++i) {
			if (!IsUpperCase(aString[i])) return false;
		}
		return true;
#endif
	}

	bool ANVIL_CALL IsLowerCase(const char* aString, size_t aSize) throw() {
#ifdef ANVIL_SSE2
		const __m128i low = _mm_set1_epi8('a');
		const __m128i high = _mm_set1_epi8('z');

		const size_t loops = aSize >> 4;
		const size_t remainder = aSize & 15;
		for (size_t i = 0; i < loops; ++i) {
			const size_t j = i << 4;
			const __m128i in = _mm_load_si128(reinterpret_cast<const __m128i*>(aString + j));
			const __m128i tmp = _mm_or_si128(_mm_cmpgt_epi8(in, high), _mm_cmplt_epi8(in, low));
			if (tmp.m128i_i64[0] | tmp.m128i_i64[1]) return false;
		}
		aString += loops << 4;
		for (size_t i = 0; i < remainder; ++i) if (!IsLowerCase(aString[i])) return false;
		return true;
#else
		for (size_t i = 0; i < aSize; ++i) {
			if (!IsLowerCase(aString[i])) return false;
		}
		return true;
#endif
	}

	bool ANVIL_CALL IsLetter(const char* aString, size_t aSize) throw() {
#ifdef ANVIL_SSE2
		const __m128i low1 = _mm_set1_epi8('a');
		const __m128i high1 = _mm_set1_epi8('z');
		const __m128i low2 = _mm_set1_epi8('A');
		const __m128i high2 = _mm_set1_epi8('Z');

		const size_t loops = aSize >> 4;
		const size_t remainder = aSize & 15;
		for (size_t i = 0; i < loops; ++i) {
			const size_t j = i << 4;
			const __m128i in = _mm_load_si128(reinterpret_cast<const __m128i*>(aString + j));
			const __m128i tmp1 = _mm_or_si128(_mm_cmpgt_epi8(in, high1), _mm_cmplt_epi8(in, low1));
			__m128i tmp2 = _mm_or_si128(_mm_cmpgt_epi8(in, high2), _mm_cmplt_epi8(in, low2));
			tmp2 = _mm_and_si128(tmp1, tmp2);
			if (tmp2.m128i_i64[0] | tmp2.m128i_i64[1]) return false;
	}
		aString += loops << 4;
		for (size_t i = 0; i < remainder; ++i) if (!IsNumber(aString[i])) return false;
		return true;
#else
		for (size_t i = 0; i < aSize; ++i) {
			if (!IsLetter(aString[i])) return false;
		}
		return true;
#endif
	}

	bool ANVIL_CALL IsNumber(const char* aString, size_t aSize) throw() {
#ifdef ANVIL_SSE2
		const __m128i low = _mm_set1_epi8('0');
		const __m128i high = _mm_set1_epi8('9');

		const size_t loops = aSize >> 4;
		const size_t remainder = aSize & 15;
		for (size_t i = 0; i < loops; ++i) {
			const size_t j = i << 4;
			const __m128i in = _mm_load_si128(reinterpret_cast<const __m128i*>(aString + j));
			const __m128i tmp = _mm_or_si128(_mm_cmpgt_epi8(in, high), _mm_cmplt_epi8(in, low));
			if(tmp.m128i_i64[0] | tmp.m128i_i64[1]) return false;
		}
		aString += loops << 4;
		for (size_t i = 0; i < remainder; ++i) if (!IsNumber(aString[i])) return false;
		return true;
#else
		for (size_t i = 0; i < aSize; ++i) {
			if (!IsNumber(aString[i])) return false;
		}
		return true;
#endif
	}

	void ANVIL_CALL ToUpperCase(const char* aString, char* aOutput, size_t aSize) throw() {
#ifdef ANVIL_SSE2
		const __m128i low = _mm_set1_epi8('a' - 1);
		const __m128i high = _mm_set1_epi8('z' + 1);
		const __m128i dif = _mm_set1_epi8(CASE_DIFFERENCE);

		const size_t loops = aSize >> 4;
		const size_t remainder = aSize & 15;
		for (size_t i = 0; i < loops; ++i) {
			const size_t j = i << 4;
			const __m128i in = _mm_load_si128(reinterpret_cast<const __m128i*>(aString + j));
			__m128i& out = *reinterpret_cast<__m128i*>(aOutput + j);
			out = _mm_add_epi8(in, _mm_mul_epi8(dif, _mm_and_si128(_mm_cmpgt_epi8(in, low), _mm_cmplt_epi8(in, high))));
		}
		const size_t j = loops << 4;
		__m128i in = _mm_load_si128(reinterpret_cast<const __m128i*>(aString + j));
		in = _mm_add_epi8(in, _mm_mul_epi8(dif, _mm_and_si128(_mm_cmpgt_epi8(in, low), _mm_cmplt_epi8(in, high))));
		memcpy(aOutput + j, &in, remainder);
#else
		for (size_t i = 0; i < aSize; ++i) {
			aOutput[i] = ToUpperCase(aString[i]);
		}
#endif
	}

	void ANVIL_CALL ToLowerCase(const char* aString, char* aOutput, size_t aSize) throw() {
#ifdef ANVIL_SSE2
		const __m128i low = _mm_set1_epi8('A' - 1);
		const __m128i high = _mm_set1_epi8('Z' + 1);
		const __m128i dif = _mm_set1_epi8(CASE_DIFFERENCE);

		const size_t loops = aSize >> 4;
		const size_t remainder = aSize & 15;
		for (size_t i = 0; i < loops; ++i) {
			const size_t j = i << 4;
			const __m128i in = _mm_load_si128(reinterpret_cast<const __m128i*>(aString + j));
			__m128i& out = *reinterpret_cast<__m128i*>(aOutput + j);
			out = _mm_sub_epi8(in, _mm_mul_epi8(dif, _mm_and_si128(_mm_cmpgt_epi8(in, low), _mm_cmplt_epi8(in, high))));
		}
		const size_t j = loops << 4;
		__m128i in = _mm_load_si128(reinterpret_cast<const __m128i*>(aString + j));
		in = _mm_sub_epi8(in, _mm_mul_epi8(dif, _mm_and_si128(_mm_cmpgt_epi8(in, low), _mm_cmplt_epi8(in, high))));
		memcpy(aOutput + j, &in, remainder);
#else
		for (size_t i = 0; i < aSize; ++i) {
			aOutput[i] = ToLowerCase(aString[i]);
		}
#endif
	}

}