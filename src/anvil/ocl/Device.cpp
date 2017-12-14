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
#include "anvil/ocl/Context.hpp"

namespace anvil { namespace ocl {

	enum { DEVICE_INFO_BUFFER_SIZE = 2048 };
	static uint8_t gDeviceInfoBuffer[DEVICE_INFO_BUFFER_SIZE];

	// Device

	ANVIL_CALL Device::Device() throw() :
		Object(Handle::DEVICE)
	{}

	ANVIL_CALL Device::Device(Device&& aOther) throw() :
		Object(Handle::DEVICE)
	{
		swap(aOther);
	}

	ANVIL_CALL Device::~Device() throw() {
		if (mHandle.device) destroy();
	}

	Device& ANVIL_CALL Device::operator=(Device&& aOther) throw() {
		swap(aOther);
		return *this;
	}

	void ANVIL_CALL Device::swap(Device& aOther) throw() {
		std::swap(mHandle, aOther.mHandle);
	}

	bool ANVIL_CALL Device::destroy() throw() {
#ifdef CL_VERSION_1_2
		if (isSubDevice()) {
			cl_int error = clReleaseDevice(mHandle);
			if(error != CL_SUCCESS) return oclError("clReleaseDevice", error);
			onDestroy();
			mHandle.device = NULL;
			return true;
		}
		return true;
#else
		onDestroy();
		return true;
#endif
	}

	bool ANVIL_CALL Device::create(Handle aHandle) throw() {
		if (aHandle.type != Handle::DEVICE) return false;
		mHandle = aHandle;
		onCreate();
		return true;
	}

	std::vector<std::shared_ptr<Device>> ANVIL_CALL Device::partition(cl_uint aCount) throw() {
#ifdef CL_VERSION_1_2
		//! Options for other properies
		cl_device_partition_property properties[2];
		properties[0] = CL_DEVICE_PARTITION_EQUALLY ;
		properties[1] = 0;

		if (aCount > Platform::MAX_DEVICES) {
			oclError("clCreateSubDevices", CL_INVALID_DEVICE_PARTITION_COUNT, std::to_string(aCount).c_str());
			return std::vector<std::shared_ptr<Device>>();
		}
		cl_device_id deviceIDs[Platform::MAX_DEVICES];
		cl_uint error = clCreateSubDevices(mHandle, properties, aCount, deviceIDs, NULL);
		if (error != CL_SUCCESS){
			oclError("clCreateSubDevices", error, std::to_string(aCount).c_str());
			return std::vector<std::shared_ptr<Device>>();
		}

		std::vector<std::shared_ptr<Device>> devices(aCount, std::shared_ptr<Device>());
		for (cl_uint i = 0; i < aCount; ++i) {
			devices[i].swap(std::shared_ptr<Device>(new Device()));
			devices[i]->mHandle = deviceIDs[0];
			devices[i]->setExtraData(std::shared_ptr<int>(new int(i)));
		}
		return devices;
#else
		oclError("clCreateSubDevices", CL_DEVICE_PARTITION_FAILED, "OpenCL version does not support this operation");
		return std::vector<std::shared_ptr<Device>> ();
#endif
	}

	bool ANVIL_CALL Device::isSubDevice() const throw() {
#ifdef CL_VERSION_1_2
		return const_cast<Device*>(this)->getExtraData() ? true : false;
#else
		return false;
#endif
	}

	void* ANVIL_CALL Device::getInfo(cl_device_info aName) const {
		const cl_int error = clGetDeviceInfo(mHandle.device, aName, DEVICE_INFO_BUFFER_SIZE, gDeviceInfoBuffer, nullptr);
		if (error != CL_SUCCESS) oclError("clGetDeviceInfo", error, std::to_string(aName).c_str());
		return gDeviceInfoBuffer;
	}

	std::vector<std::shared_ptr<Device>> ANVIL_CALL Device::devices(Device::Type aType) {
		std::vector<std::shared_ptr<Device>> devices;
		const std::vector<Platform> platforms = Platform::platforms();
		for (Platform i : platforms) {
			std::vector<std::shared_ptr<Device>> devices2 = i.devices(aType);
			for (std::shared_ptr<Device> i : devices2) devices.push_back(i);
		}
		return devices;
	}

	cl_uint ANVIL_CALL Device::referenceCount() const throw() {
#ifdef CL_VERSION_1_2
		return mHandle.device ? const_cast<Device*>(this)->getExtraData().use_count() - 1 : 0;
#else
		return false;
#endif
	}

	Handle::Type ANVIL_CALL Device::type() const throw() {
		return Handle::DEVICE;
	}
}}