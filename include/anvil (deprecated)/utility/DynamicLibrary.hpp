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

#ifndef ANVIL_CORE_DYNAMIC_LIBRARY_HPP
#define ANVIL_CORE_DYNAMIC_LIBRARY_HPP

#include "anvil/core/OperatingSystem.hpp"
#include "anvil/core/Keywords.hpp"

namespace anvil {
	class DynamicLibrary {
	private:
		DynamicLibrary(DynamicLibrary&&) = delete;
		DynamicLibrary(const DynamicLibrary&) = delete;
		DynamicLibrary& operator=(DynamicLibrary&&) = delete;
		DynamicLibrary& operator=(const DynamicLibrary&) = delete;
	public :
		ANVIL_CALL DynamicLibrary() {}
		virtual ANVIL_CALL ~DynamicLibrary() throw() {}
		virtual bool ANVIL_CALL loadFromFile(const char*) throw() = 0;
		virtual bool ANVIL_CALL unload() throw() = 0;
		virtual void* ANVIL_CALL loadSymbol(const char*) const throw() = 0;
		virtual bool ANVIL_CALL isLoaded() const throw() = 0;

		ANVIL_STRONG_INLINE ANVIL_CALL operator bool() const throw() { return isLoaded(); }

		template<class R>
		ANVIL_STRONG_INLINE R(*loadFunction(const char* a_name) const throw())() {
			return static_cast<R(*)()>(loadSymbol(a_name));
		}

		template<class R, class ...PARAMS>
		ANVIL_STRONG_INLINE R(*loadFunction(const char* a_name) const throw())(PARAMS...)  {
			return static_cast<R(*)(PARAMS...)>(loadSymbol(a_name));
		}

		template<class T>
		ANVIL_STRONG_INLINE T* ANVIL_CALL loadVariable(const char* a_name) const throw() {
			return static_cast<T*>(loadSymbol(a_name));
		}
	};

#if ANVIL_OS == ANVIL_WINDOWS
	class WindowsDynamicLibrary : public DynamicLibrary {
	private:
		void* mModule;
	public:
		ANVIL_CALL WindowsDynamicLibrary() throw();
		ANVIL_CALL ~WindowsDynamicLibrary() throw();

		// Inherited from DynamicLibrary
		bool ANVIL_CALL loadFromFile(const char*) throw() override;
		bool ANVIL_CALL unload() throw() override;
		void* ANVIL_CALL loadSymbol(const char*) const throw() override;
		bool ANVIL_CALL isLoaded() const throw() override;
	};
#endif
}

#endif