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

#include <cstdint>
#include "anvil/ocl/Platform.hpp"

namespace anvil { namespace ocl {


	enum { PLATFORM_INFO_BUFFER_SIZE = 2048 };
	static uint8_t gPlatformInfoBuffer[PLATFORM_INFO_BUFFER_SIZE];

	// Platform

	ANVIL_CALL Platform::Platform() throw() :
		mPlatform(NULL)
	{}

	ANVIL_CALL Platform::Platform(cl_platform_id aPlatform) throw() :
		mPlatform(aPlatform)
	{}

	ANVIL_CALL Platform::operator bool() const throw() {
		return mPlatform != NULL;
	}

	void* ANVIL_CALL Platform::getInfo(cl_platform_info aName) const throw() {
		const cl_int error = clGetPlatformInfo(mPlatform, aName, PLATFORM_INFO_BUFFER_SIZE, gPlatformInfoBuffer, nullptr);
		if (error != CL_SUCCESS) oclError("clGetDeviceInfo", error);
		return gPlatformInfoBuffer;
	}

	std::vector<Device> ANVIL_CALL Platform::devices(Device::Type aType) const throw() {
		// Queury the number of devices
		cl_uint count = 0;
		cl_int error = clGetDeviceIDs(mPlatform, aType, 0, NULL, &count);
		if (error != CL_SUCCESS) {
			if(error != CL_DEVICE_NOT_FOUND) oclError("clGetDeviceIDs", error);
			return std::vector<Device>();
		}

		// Allocate storage for devices
		std::vector<Device> devices(count, Device());

		// Get devices
		error = clGetDeviceIDs(mPlatform, aType, count, reinterpret_cast<cl_device_id*>(&devices[0]), &count);
		if (error != CL_SUCCESS) {
			oclError("clGetDeviceIDs", error);
			return std::vector<Device>();
		}

		// Return devices
		return devices;
	}

	std::vector<Platform> ANVIL_CALL Platform::platforms() throw() {
		// Queury the number of platforms
		cl_uint count = 0;
		cl_int error = clGetPlatformIDs(0, NULL, &count);
		if (error != CL_SUCCESS) {
			oclError("clGetPlatformIDs", error);
			return std::vector<Platform>();
		}

		// Allocate storage for platforms
		std::vector<Platform> platforms(count, Platform());

		// Get platforms
		error = clGetPlatformIDs(count, reinterpret_cast<cl_platform_id*>(&platforms[0]), &count);
		if (error != CL_SUCCESS) {
			oclError("clGetPlatformIDs", error);
			return std::vector<Platform>();
		}
		
		// Return platforms
		return platforms;
	}

}}