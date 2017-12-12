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
#include "anvil/ocl/Device.hpp"
#include "anvil/ocl/Platform.hpp"

namespace anvil { namespace ocl {

	enum { DEVICE_INFO_BUFFER_SIZE = 2048 };
	static uint8_t gDeviceInfoBuffer[DEVICE_INFO_BUFFER_SIZE];

	// Device

	ANVIL_CALL Device::Device() :
		Object(DEVICE) 
	{}

	ANVIL_CALL Device::Device(cl_device_id aDevice) :
		Object(DEVICE) 
	{
		mHandle.device = aDevice;
	}

	bool ANVIL_CALL Device::destroy() throw() {
		return false;
	}

	bool ANVIL_CALL Device::create(Handle aHandle) throw() {
		if (aHandle.type != DEVICE) return false;
		mHandle = aHandle;
		return true;
	}

	void* ANVIL_CALL Device::getInfo(cl_device_info aName) const {
		const cl_int error = clGetDeviceInfo(mHandle.device, aName, DEVICE_INFO_BUFFER_SIZE, gDeviceInfoBuffer, nullptr);
		if (error != CL_SUCCESS) oclError("clGetDeviceInfo", error);
		return gDeviceInfoBuffer;
	}

	std::vector<Device> ANVIL_CALL Device::devices(Device::Type aType) {
		std::vector<Device> devices;
		const std::vector<Platform> platforms = Platform::platforms();
		for (Platform i : platforms) {
			std::vector<Device> devices2 = i.devices(aType);
			for (Device i : devices2) devices.push_back(i);
		}
		return devices;
	}
}}