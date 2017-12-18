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
		Object(Handle::PLATFORM)
	{}

	ANVIL_CALL Platform::Platform(cl_platform_id aPlatform) throw() :
		Object(Handle::PLATFORM)
	{
		mHandle.platform = aPlatform;
	}

	bool ANVIL_CALL Platform::destroy() throw() {
		return false;
	}

	bool ANVIL_CALL Platform::retain() throw() {
		return true;
	}

	void* ANVIL_CALL Platform::getInfo(cl_platform_info aName) const throw() {
#ifdef ANVIL_LOG_OCL
		std::cerr << "clGetPlatformInfo (" << mHandle.platform << ", " << aName << ", " << PLATFORM_INFO_BUFFER_SIZE << ", " << 
			gPlatformInfoBuffer << ", " << (void*) nullptr << std::endl;
#endif
		const cl_int error = clGetPlatformInfo(mHandle.platform, aName, PLATFORM_INFO_BUFFER_SIZE, gPlatformInfoBuffer, nullptr);
		if (error != CL_SUCCESS) oclError("clGetDeviceInfo", error, std::to_string(aName).c_str());
		return gPlatformInfoBuffer;
	}

	std::vector<std::shared_ptr<Device>> ANVIL_CALL Platform::devices(Device::Type aType) const throw() {
		// Queury the number of devices
		cl_uint count = 0;
#ifdef ANVIL_LOG_OCL
		std::cerr << "clGetDeviceIDs (" << mHandle.platform << ", " << aType << ", " << 0 <<
			", " << "NULL" << ", " << (void*)&count << ")" << std::endl;
#endif
		cl_int error = clGetDeviceIDs(mHandle.platform, aType, 0, NULL, &count);
		if (error != CL_SUCCESS) {
			if(error != CL_DEVICE_NOT_FOUND) oclError("clGetDeviceIDs", error);
			return std::vector<std::shared_ptr<Device>>();
		}

		// Allocate storage for devices
		cl_device_id deviceIDS[MAX_DEVICES];

		// Get devices
#ifdef ANVIL_LOG_OCL
		std::cerr << "clGetDeviceIDs (" << mHandle.platform << ", " << aType << ", " << count <<
			", " << (void*)deviceIDS << ", " << "NULL" << ")" << std::endl;
#endif
		error = clGetDeviceIDs(mHandle.platform, aType, count, deviceIDS, NULL);
		if (error != CL_SUCCESS) {
			oclError("clGetDeviceIDs", error);
			return std::vector<std::shared_ptr<Device>>();
		}
		std::vector<std::shared_ptr<Device>> devices(count, std::shared_ptr<Device>());
		for (cl_uint i = 0; i < count; ++i) {
			devices[i].swap(std::shared_ptr<Device>(new Device()));
			devices[i]->create(deviceIDS[i]);
		}

		// Return devices
		return devices;
	}

	std::vector<Platform> ANVIL_CALL Platform::platforms() throw() {
		// Queury the number of platforms
		cl_uint count = 0;
#ifdef ANVIL_LOG_OCL
		std::cerr << "clGetPlatformIDs (" << 0 << ", " << "NULL" << ", " << (void*)&count << ")" << std::endl;
#endif
		cl_int error = clGetPlatformIDs(0, NULL, &count);
		if (error != CL_SUCCESS) {
			oclError("clGetPlatformIDs", error);
			return std::vector<Platform>();
		}
		if (count == 0) return std::vector<Platform>();

		// Allocate storage for platforms
		cl_platform_id platformIDs[MAX_PLATFORMS];

		// Get platforms
#ifdef ANVIL_LOG_OCL
		std::cerr << "clGetPlatformIDs (" << count << ", " << (void*)platformIDs << ", " << "NULL" << ")" << std::endl;
#endif
		error = clGetPlatformIDs(count, platformIDs, NULL);
		if (error != CL_SUCCESS) {
			oclError("clGetPlatformIDs", error);
			return std::vector<Platform>();
		}
		std::vector<Platform> platforms(count, Platform());
		for (cl_uint i = 0; i < count; ++i) platforms[i].mHandle.platform = platformIDs[i];
		
		// Return platforms
		return platforms;
	}

	cl_uint ANVIL_CALL Platform::referenceCount() const throw() {
		return 0;
	}

	Handle::Type ANVIL_CALL Platform::type() const throw() {
		return Handle::PLATFORM;
	}

}}