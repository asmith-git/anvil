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
		DJB2_DEFAULT = 5381
	};

	// DJB2

	DJB2::DJB2() :
		_hash(DJB2_DEFAULT)
	{}

	DJB2::~DJB2() {

	}

	DJB2::hash_t DJB2::Hash(const void* src, size_t bytes) {
		const uint8_t* src8 = static_cast<const uint8_t*>(src);

		// Adapted from code found @ http://www.cse.yorku.ca/~oz/hash.html
		for (size_t i = 0u; i < bytes; ++i) {
			uint8_t c = src8[i];
			_hash = ((_hash << 5) + _hash) + c;
		}

		return _hash;
	}

	void DJB2::Reset() {
		_hash = DJB2_DEFAULT;
	}

	// DJB2a

	DJB2a::DJB2a() :
		DJB2()
	{}

	DJB2a::~DJB2a() {

	}

	DJB2a::hash_t DJB2a::Hash(const void* src, size_t bytes) {
		const uint8_t* src8 = static_cast<const uint8_t*>(src);

		// Adapted from code found @ http://www.cse.yorku.ca/~oz/hash.html
		for (size_t i = 0u; i < bytes; ++i) {
			uint8_t c = src8[i];
			_hash = (_hash * 33u) ^ c;
		}

		return _hash;
	}

}}