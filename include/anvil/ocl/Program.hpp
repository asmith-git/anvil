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

	class Program : public Object {
	private:
		Program(const Program&) = delete;
		Program& operator=(const Program&) = delete;

		ANVIL_CALL Program(Context&) throw();
		bool ANVIL_CALL build(const cl_device_id*, size_t, const char*) throw();
	public:
		typedef std::string Source;
		typedef std::vector<uint8_t> Binary;

		ANVIL_CALL Program() throw();
		ANVIL_CALL Program(Program&&) throw();
		ANVIL_CALL ~Program() throw();

		Program& ANVIL_CALL operator=(Program&&) throw();
		void ANVIL_CALL swap(Program&) throw();

		Source ANVIL_CALL source() const throw();
		std::vector<Binary> ANVIL_CALL binaries() const throw();
		std::vector<Device> ANVIL_CALL devices() const throw();

		bool ANVIL_CALL createFromSource(Context&, const char*, const char* aOptions = NULL) throw();
		bool ANVIL_CALL createFromSources(Context&, const char**, cl_uint, const char* aOptions = NULL) throw();
		bool ANVIL_CALL createFromBinary(Context&, const uint8_t*, size_t) throw();
		bool ANVIL_CALL createFromBinaries(Context&, const uint8_t**, const size_t*, size_t) throw();
		bool ANVIL_CALL create(Context&, const Source&, const char* aOptions = NULL) throw();
		bool ANVIL_CALL create(Context&, const std::vector<Source>&, const char* aOptions = NULL) throw();
		bool ANVIL_CALL create(Context&, const Binary&) throw();
		bool ANVIL_CALL create(Context&, const std::vector<Binary>&) throw();

		// Inherited from Object

		bool ANVIL_CALL create(Handle) throw() override;
		bool ANVIL_CALL destroy() throw() override;
	};
}}

#endif