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

	bool ANVIL_CALL Device::retain() throw() {
		if (mHandle.event && isSubDevice()) {
#ifdef CL_VERSION_1_2
#ifdef ANVIL_LOG_OCL
			std::cerr << "clRetainDevice (" << mHandle.device << ")" << std::endl;
#endif
			cl_int error = clRetainDevice(mHandle.device);
			return error == CL_SUCCESS ? true : oclError("clRetainDevice", error);
#endif
		}
		return false;
	}

	std::vector<std::shared_ptr<Device>> ANVIL_CALL Device::partitionWithProperties(const intptr_t* aProperties, cl_uint aCount) throw() {
#ifdef CL_VERSION_1_2
		if (aCount > Platform::MAX_DEVICES) {
			oclError("clCreateSubDevices", CL_INVALID_DEVICE_PARTITION_COUNT, std::to_string(aCount).c_str());
			return std::vector<std::shared_ptr<Device>>();
		}
		cl_device_id deviceIDs[Platform::MAX_DEVICES];
#ifdef ANVIL_LOG_OCL
		std::cerr << "clCreateSubDevices (" <<
			mHandle.device << ", " <<
			aProperties << ", " <<
			(aProperties[0] == CL_DEVICE_PARTITION_BY_AFFINITY_DOMAIN ? Platform::MAX_DEVICES : aCount) << ", " <<
			deviceIDs << ", " <<
			(void*) (aProperties[0] == CL_DEVICE_PARTITION_BY_AFFINITY_DOMAIN ? &aCount : NULL) << ")" << std::endl;
#endif
		cl_uint error = clCreateSubDevices(
			mHandle, 
			aProperties, 
			aProperties[0] == CL_DEVICE_PARTITION_BY_AFFINITY_DOMAIN ? Platform::MAX_DEVICES : aCount, 
			deviceIDs,
			aProperties[0] == CL_DEVICE_PARTITION_BY_AFFINITY_DOMAIN ? &aCount : NULL);
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
		return std::vector<std::shared_ptr<Device>>();
#endif
	}

	std::vector<std::shared_ptr<Device>> ANVIL_CALL Device::partition(cl_uint aCount) throw() {
#ifdef CL_VERSION_1_2
		cl_device_partition_property properties[2];
		properties[0] = CL_DEVICE_PARTITION_EQUALLY;
		properties[1] = 0;
#else
		intptr_t* properties = NULL;
#endif
		return partitionWithProperties(properties, aCount);
	}


	std::vector<std::shared_ptr<Device>> ANVIL_CALL Device::partition(const cl_uint* aUnits, cl_uint aCount) throw() {
#ifdef CL_VERSION_1_2
		cl_device_partition_property properties[Platform::MAX_DEVICES];
		properties[0] = CL_DEVICE_PARTITION_BY_COUNTS;
		for (cl_uint i = 0; i < aCount; ++i) properties[i] = aUnits[i];
		properties[aCount] = CL_DEVICE_PARTITION_BY_COUNTS_LIST_END;
		properties[aCount + 1] = 0;
#else
		intptr_t* properties = NULL;
#endif
		return partitionWithProperties(properties, aCount);

	}

	std::vector<std::shared_ptr<Device>> ANVIL_CALL Device::partition(AffinityDomain aDomain) throw() {
#ifdef CL_VERSION_1_2
		cl_device_partition_property properties[3];
		properties[0] = CL_DEVICE_PARTITION_BY_AFFINITY_DOMAIN;
		properties[1] = aDomain;
		properties[2] = 0;
#else
		intptr_t* properties = NULL;
#endif
		return partitionWithProperties(properties, 0);

	}

	std::vector<std::shared_ptr<Device>> ANVIL_CALL Device::partition(const std::vector<cl_uint>& aUnits) throw() {
		return aUnits.empty() ? std::vector<std::shared_ptr<Device>>() : partition(&aUnits[0], aUnits.size());
	}

	bool ANVIL_CALL Device::isSubDevice() const throw() {
#ifdef CL_VERSION_1_2
		return const_cast<Device*>(this)->getExtraData() ? true : false;
#else
		return false;
#endif
	}

	Device ANVIL_CALL Device::getParentDevice() throw() {
		Handle handle(Handle::DEVICE);
#ifdef CL_VERSION_1_2
#ifdef ANVIL_LOG_OCL
		std::cerr << "clGetDeviceInfo (" << mHandle.device << ", " << "CL_DEVICE_PARENT_DEVICE" << ", " << sizeof(cl_device_id) << 
			", " << &handle.device << ", " << "NULL" << ")" << std::endl;
#endif
		const cl_int error = clGetDeviceInfo(mHandle.device, CL_DEVICE_PARENT_DEVICE, sizeof(cl_device_id), &handle.device, NULL);
		if (error != CL_SUCCESS) oclError("clGetDeviceInfo", error, "CL_DEVICE_PARENT_DEVICE");
#endif
		Device device;
		device.create(handle);
		return std::move(device);
	}

	void* ANVIL_CALL Device::getInfo(cl_device_info aName) const throw() {
#ifdef ANVIL_LOG_OCL
		std::cerr << "clGetDeviceInfo (" << mHandle.device << ", " << aName << ", " << DEVICE_INFO_BUFFER_SIZE << ", " << 
			gDeviceInfoBuffer << ", " << "NULL" << ")" << std::endl;
#endif
		const cl_int error = clGetDeviceInfo(mHandle.device, aName, DEVICE_INFO_BUFFER_SIZE, gDeviceInfoBuffer, NULL);
		if (error != CL_SUCCESS) oclError("clGetDeviceInfo", error, std::to_string(aName).c_str());
		return gDeviceInfoBuffer;
	}

	std::vector<std::shared_ptr<Device>> ANVIL_CALL Device::devices(Device::Type aType) throw() {
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