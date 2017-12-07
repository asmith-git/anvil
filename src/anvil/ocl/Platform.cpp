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
		std::vector<Device> devices;

		enum { kMaxDevices = 64 };
		cl_device_id ids[kMaxDevices];
		cl_uint count = 0;
		cl_int error = clGetDeviceIDs(mPlatform, aType, kMaxDevices, ids, &count);
		if (error == CL_DEVICE_NOT_FOUND) count = 0;
		else if (error != CL_SUCCESS) oclError("clGetDeviceIDs", error);
		for (cl_uint i = 0; i < count; ++i) devices.push_back(Device(ids[i]));

		return devices;
	}

	std::vector<Platform> ANVIL_CALL Platform::platforms() throw() {
		std::vector<Platform> platforms;

		enum { kMaxPlatforms = 64 };
		cl_platform_id ids[kMaxPlatforms];
		cl_uint count = 0;
		cl_int error = clGetPlatformIDs(kMaxPlatforms, ids, &count);
		if (error != CL_SUCCESS) oclError("clGetPlatformIDs", error);
		for (cl_uint i = 0; i < count; ++i) platforms.push_back(Platform(ids[i]));

		return platforms;
	}

}}