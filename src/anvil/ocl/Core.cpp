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

#include "anvil/ocl/Core.hpp"

namespace anvil { namespace ocl {

	// Object

	ANVIL_CALL Object::Object() throw() {
		mHandle.context = NULL;
	}

	ANVIL_CALL Object::~Object() throw() {

	}

	Object::Handle ANVIL_CALL  Object::handle() const throw() {
		return mHandle;
	}

	ANVIL_CALL Object::operator bool() const throw() {
		return mHandle.context != NULL;
	}

}}