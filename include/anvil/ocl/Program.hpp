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

#ifndef ANVIL_OCL_PPOGRAM_HPP
#define ANVIL_OCL_PPOGRAM_HPP

#include <cstdint>
#include "anvil/ocl/Context.hpp"

namespace anvil { namespace ocl {

	class Program {
	private:
		enum State : uint8_t {
			INITIALISED,
			SOURCE_SET,
			BUILT
		};
		const Context& mContext;
		cl_program mProgram;
		State mState;
		
		Program(Program&&) = delete;
		Program(const Program&) = delete;
		Program& operator=(Program&&) = delete;
		Program& operator=(const Program&) = delete;
	public:
		friend class Kernel;

		ANVIL_CALL Program(const Context&);
		ANVIL_CALL ~Program();

		void ANVIL_CALL setSource(const char*);
		void ANVIL_CALL setSources(const char**, cl_uint);
		void ANVIL_CALL setBinary(const unsigned char*, size_t);
		void ANVIL_CALL setBinaries(const unsigned char**, const size_t*);
		void ANVIL_CALL build(const char*);
	};
}}

#endif