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
	class Platform {
	private:
		cl_plaform_id mPlatform;
	public:
		ANVIL_CALL Platform() :
			mPlatform(0) 
		{}
		
		ANVIL_CALL Platform(cl_plaform_id aPlatform) :
			mPlatform(aPlatform) 
		{}
		
		std::vector<Device> ANVIL_CALL getDevices(Type aType = kAll) {
			std::vector<Platform> devices;
			
			enum {kMaxDevices = 64}
			cl_plaform_id ids[kMaxDevices];
			cl_uint count = 0;
			cl_int error = clGetDeviceIDs(mPlatform, aType, kMaxDevices, ids, &count);
			if(error != CL_SUCCESS) throwException("clGetDeviceIDs", error);
			for(cl_uint i = 0; i < count; ++i) devices.push_back(Devices(ids[i]));
			
			return devices;
		}
		
		static std::vector<Platform> ANVIL_CALL getPlatforms() {
			std::vector<Platform> platforms;
			
			enum {kMaxPlatforms = 64}
			cl_plaform_id ids[kMaxPlatforms];
			cl_uint count = 0;
			cl_int error = clGetPlatformIDs(kMaxPlatforms, ids, &count);
			if(error != CL_SUCCESS) throwException("clGetPlatformIDs", error);
			for(cl_uint i = 0; i < count; ++i) platforms.push_back(Platform(ids[i]));
			
			return platforms;
		}
	};
}}
