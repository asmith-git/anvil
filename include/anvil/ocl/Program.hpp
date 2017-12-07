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
		cl_context mContext;
		cl_program mProgram;
		
		Program(const Program&) = delete;
		Program& operator=(const Program&) = delete;

		bool ANVIL_CALL build(const char*) throw();
	public:
		friend class Kernel;

		enum { MAX_DEVICES = 32 };

		typedef std::string Source;
		typedef std::vector<uint8_t> Binary;

		ANVIL_CALL Program() throw();
		ANVIL_CALL Program(Program&&) throw();
		ANVIL_CALL Program(Context&) throw();
		ANVIL_CALL ~Program() throw();

		Program& ANVIL_CALL operator=(Program&&) throw();
		void ANVIL_CALL swap(Program&) throw();

		bool ANVIL_CALL buildFromSource(const char*, const char* aOptions = NULL) throw();
		bool ANVIL_CALL buildFromSources(const char**, cl_uint, const char* aOptions = NULL) throw();
		bool ANVIL_CALL buildFromSource(const Source&, const char* aOptions = NULL) throw();
		bool ANVIL_CALL buildFromSources(const std::vector<Source>&, const char* aOptions = NULL) throw();
		bool ANVIL_CALL buildFromBinary(const void*, size_t, const char* aOptions = NULL) throw();
		bool ANVIL_CALL buildFromBinaries(const void**, const size_t*, size_t, const char* aOptions = NULL) throw();
		bool ANVIL_CALL buildFromBinary(const Binary&, const char* aOptions = NULL) throw();
		bool ANVIL_CALL buildFromBinaries(const std::vector<Binary>&, const char* aOptions = NULL) throw();

		Source source() const throw();
		std::vector<Binary> binaries() const throw();
	};
}}

#endif