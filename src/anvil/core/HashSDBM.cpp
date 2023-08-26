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

#include "anvil/core/Hash.hpp"

namespace anvil { namespace hash {
	
	enum {
		SDBM_DEFAULT = 0
	};

	// SDBM

	SDBM::SDBM() :
		_hash(SDBM_DEFAULT)
	{}

	SDBM::~SDBM() {

	}

	SDBM::hash_t SDBM::Hash(const void* src, size_t bytes) {
		const uint8_t* src8 = static_cast<const uint8_t*>(src);

		// Adapted from code found @ http://www.cse.yorku.ca/~oz/hash.html
		for (size_t i = 0u; i < bytes; ++i) {
			uint8_t c = src8[i];
			_hash = _hash * 65599u + c;
		}

		return _hash;
	}

	void SDBM::Reset() {
		_hash = SDBM_DEFAULT;
	}

	// FastSDBM

	FastSDBM::FastSDBM() :
		SDBM()
	{}

	FastSDBM::~FastSDBM() {

	}

	FastSDBM::hash_t FastSDBM::Hash(const void* src, size_t bytes) {
		const uint8_t* src8 = static_cast<const uint8_t*>(src);

		// Adapted from code found @ http://www.cse.yorku.ca/~oz/hash.html
		for (size_t i = 0u; i < bytes; ++i) {
			uint8_t c = src8[i];
			_hash = c + (_hash << 6u) + (_hash << 16u) - _hash;
		}

		return _hash;
	}

}}