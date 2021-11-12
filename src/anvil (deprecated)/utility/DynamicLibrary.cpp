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

#include "anvil/utility/DynamicLibrary.hpp"

#if ANVIL_OS == ANVIL_WINDOWS
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

namespace anvil {
#if ANVIL_OS == ANVIL_WINDOWS
	// WindowsDynamicLibrary

	ANVIL_CALL WindowsDynamicLibrary::WindowsDynamicLibrary() throw() :
		mModule(NULL)
	{}

	ANVIL_CALL WindowsDynamicLibrary::~WindowsDynamicLibrary() throw() {
		unload();
	}

	bool ANVIL_CALL WindowsDynamicLibrary::loadFromFile(const char* a_path) throw() {
		if (isLoaded()) return false;
		mModule = LoadLibraryA(a_path);
		return mModule != NULL;
	}

	bool ANVIL_CALL WindowsDynamicLibrary::unload() throw() {
		if (!isLoaded()) return false;
		const bool tmp = FreeLibrary(static_cast<HMODULE>(mModule)) != 0;
		mModule = NULL;
		return tmp;
	}

	void* ANVIL_CALL WindowsDynamicLibrary::loadSymbol(const char* a_name) const throw() {
		if (!isLoaded()) return nullptr;
		return GetProcAddress(static_cast<HMODULE>(mModule), a_name);
	}

	bool ANVIL_CALL WindowsDynamicLibrary::isLoaded() const throw() {
		return mModule != NULL;
	}

#endif
}