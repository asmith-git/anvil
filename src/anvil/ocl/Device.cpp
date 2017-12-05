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

namespace anvil { namespace ocl {

	enum { DEVICE_INFO_BUFFER_SIZE = 2048 };
	static uint8_t gDeviceInfoBuffer[DEVICE_INFO_BUFFER_SIZE];

	// Device

	ANVIL_CALL Device::Device() :
		mDevice(0)
	{}

	ANVIL_CALL Device::Device(cl_device_id aDevice) :
		mDevice(aDevice)
	{}

	void* ANVIL_CALL Device::getInfo(cl_device_info aName) const {
		const cl_int error = clGetDeviceInfo(mDevice, aName, DEVICE_INFO_BUFFER_SIZE, gDeviceInfoBuffer, nullptr);
		if (error != CL_SUCCESS) throwException("clGetDeviceInfo", error);
		return gDeviceInfoBuffer;
	}
}}