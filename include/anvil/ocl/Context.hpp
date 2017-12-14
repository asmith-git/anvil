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

#ifndef ANVIL_OCL_CONTEXT_HPP
#define ANVIL_OCL_CONTEXT_HPP

#include <vector>
#include "anvil/ocl/Platform.hpp"

namespace anvil { namespace ocl {
	class Context : public Object {
	private:
		Context(Context&) = delete;
		Context& operator=(Context&) = delete;

		bool ANVIL_CALL create(cl_platform_id, cl_device_id*, size_t) throw();
	protected:
		virtual void ANVIL_CALL onError(const char*, const void*, size_t) throw();
	public:

		ANVIL_CALL Context() throw();
		ANVIL_CALL Context(Context&&) throw();
		ANVIL_CALL ~Context() throw();

		Context& ANVIL_CALL operator=(Context&&) throw();

		bool ANVIL_CALL create(Device&) throw();
		bool ANVIL_CALL create(Device*, size_t) throw();
		bool ANVIL_CALL create(std::vector<std::shared_ptr<Device>>&) throw();

		void ANVIL_CALL swap(Context&);

		std::vector<std::shared_ptr<Device>> ANVIL_CALL devices() const throw();

		// Inherited from Object

		bool ANVIL_CALL create(Handle) throw() override;
		bool ANVIL_CALL destroy() throw() override;
		cl_uint ANVIL_CALL referenceCount() const throw() override;
		Handle::Type ANVIL_CALL type() const throw() override;
	};
}}

#endif
