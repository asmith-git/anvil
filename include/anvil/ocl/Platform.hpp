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

#ifndef ANVIL_OCL_PLATFORM_HPP
#define ANVIL_OCL_PLATFORM_HPP

#include "anvil/ocl/Device.hpp"

namespace anvil { namespace ocl {
	class Platform : public Object {
	private:
		void* ANVIL_CALL getInfo(cl_platform_info) const;
		ANVIL_CALL Platform(cl_platform_id) throw();
	protected:
		// Inherited from Object
		bool ANVIL_CALL retain() throw() override;
	public:
		enum {
			MAX_PLATFORMS = 16,
			MAX_DEVICES = 64
		};

		ANVIL_CALL Platform() throw();
		
		std::vector<std::shared_ptr<Device>> ANVIL_CALL devices(Device::Type aType = Device::ALL) const throw();
		static std::vector<Platform> ANVIL_CALL platforms() throw();


		#define ANVIL_CL_GET_INFO(type, ptr, name1, name2) inline type ANVIL_CALL name1() const { return ptr reinterpret_cast<type ptr>(getInfo(name2)); }

		ANVIL_CL_GET_INFO(const char*, , profile,      CL_PLATFORM_PROFILE);
		ANVIL_CL_GET_INFO(const char*, , version,      CL_PLATFORM_VERSION);
		ANVIL_CL_GET_INFO(const char*, , name,         CL_PLATFORM_NAME);
		ANVIL_CL_GET_INFO(const char*, , vendor,       CL_PLATFORM_VENDOR);
		ANVIL_CL_GET_INFO(const char*, , extensions,   CL_PLATFORM_EXTENSIONS);

		#undef ANVIL_CL_GET_INFO

		// Inherited from Object

		bool ANVIL_CALL destroy() throw() override;
		cl_uint ANVIL_CALL referenceCount() const throw() override;
		Handle::Type ANVIL_CALL type() const throw() override;
	};
}}

#endif