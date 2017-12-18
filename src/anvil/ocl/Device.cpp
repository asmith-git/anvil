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
		const std::string info(
			aName == CL_DEVICE_ADDRESS_BITS ? "CL_DEVICE_ADDRESS_BITS" :
			aName == CL_DEVICE_AVAILABLE ? "CL_DEVICE_AVAILABLE" :
			aName == CL_DEVICE_COMPILER_AVAILABLE ? "CL_DEVICE_COMPILER_AVAILABLE" :
			aName == CL_DEVICE_DOUBLE_FP_CONFIG ? "CL_DEVICE_DOUBLE_FP_CONFIG" :
			aName == CL_DEVICE_ENDIAN_LITTLE ? "CL_DEVICE_ENDIAN_LITTLE" :
			aName == CL_DEVICE_ERROR_CORRECTION_SUPPORT ? "CL_DEVICE_ERROR_CORRECTION_SUPPORT" :
			aName == CL_DEVICE_EXECUTION_CAPABILITIES ? "CL_DEVICE_EXECUTION_CAPABILITIES" :
			aName == CL_DEVICE_EXTENSIONS ? "CL_DEVICE_EXTENSIONS" :
			aName == CL_DEVICE_GLOBAL_MEM_CACHE_SIZE ? "CL_DEVICE_GLOBAL_MEM_CACHE_SIZE" :
			aName == CL_DEVICE_GLOBAL_MEM_CACHE_TYPE ? "CL_DEVICE_GLOBAL_MEM_CACHE_TYPE" :
			aName == CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE ? "CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE" :
			aName == CL_DEVICE_GLOBAL_MEM_SIZE ? "CL_DEVICE_GLOBAL_MEM_SIZE" :
			//aName == CL_DEVICE_HALF_FP_CONFIG ? "CL_DEVICE_HALF_FP_CONFIG" :
			aName == CL_DEVICE_IMAGE_SUPPORT ? "CL_DEVICE_IMAGE_SUPPORT" :
			aName == CL_DEVICE_IMAGE2D_MAX_HEIGHT ? "CL_DEVICE_IMAGE2D_MAX_HEIGHT" :
			aName == CL_DEVICE_IMAGE2D_MAX_WIDTH ? "CL_DEVICE_IMAGE2D_MAX_WIDTH" :
			aName == CL_DEVICE_IMAGE3D_MAX_DEPTH ? "CL_DEVICE_IMAGE3D_MAX_DEPTH" :
			aName == CL_DEVICE_IMAGE3D_MAX_HEIGHT ? "CL_DEVICE_IMAGE3D_MAX_HEIGHT" :
			aName == CL_DEVICE_IMAGE3D_MAX_WIDTH ? "CL_DEVICE_IMAGE3D_MAX_WIDTH" :
			aName == CL_DEVICE_LOCAL_MEM_SIZE ? "CL_DEVICE_LOCAL_MEM_SIZE" :
			aName == CL_DEVICE_LOCAL_MEM_TYPE ? "CL_DEVICE_LOCAL_MEM_TYPE" :
			aName == CL_DEVICE_MAX_CLOCK_FREQUENCY ? "CL_DEVICE_MAX_CLOCK_FREQUENCY" :
			aName == CL_DEVICE_MAX_COMPUTE_UNITS ? "CL_DEVICE_MAX_COMPUTE_UNITS" :
			aName == CL_DEVICE_MAX_CONSTANT_ARGS ? "CL_DEVICE_MAX_CONSTANT_ARGS" :
			aName == CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE ? "CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE" :
			aName == CL_DEVICE_MAX_MEM_ALLOC_SIZE ? "CL_DEVICE_MAX_MEM_ALLOC_SIZE" :
			aName == CL_DEVICE_MAX_PARAMETER_SIZE ? "CL_DEVICE_MAX_PARAMETER_SIZE" :
			aName == CL_DEVICE_MAX_READ_IMAGE_ARGS ? "CL_DEVICE_MAX_READ_IMAGE_ARGS" :
			aName == CL_DEVICE_MAX_SAMPLERS ? "CL_DEVICE_MAX_SAMPLERS" :
			aName == CL_DEVICE_MAX_WORK_GROUP_SIZE ? "CL_DEVICE_MAX_WORK_GROUP_SIZE" :
			aName == CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS ? "CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS" :
			aName == CL_DEVICE_MAX_WORK_ITEM_SIZES ? "CL_DEVICE_MAX_WORK_ITEM_SIZES" :
			aName == CL_DEVICE_MAX_WRITE_IMAGE_ARGS ? "CL_DEVICE_MAX_WRITE_IMAGE_ARGS" :
			aName == CL_DEVICE_MEM_BASE_ADDR_ALIGN ? "CL_DEVICE_MEM_BASE_ADDR_ALIGN" :
			aName == CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE ? "CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE" :
			aName == CL_DEVICE_NAME ? "CL_DEVICE_NAME" :
			aName == CL_DEVICE_PLATFORM ? "CL_DEVICE_PLATFORM" :
			aName == CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR  ? "CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR" :
			aName == CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT ? "CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT" :
			aName == CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT ? "CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT" :
			aName == CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG ? "CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG" :
			aName == CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT ? "CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT" :
			aName == CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE ? "CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE" :
			aName == CL_DEVICE_PROFILE ? "CL_DEVICE_PROFILE" :
			aName == CL_DEVICE_PROFILING_TIMER_RESOLUTION ? "CL_DEVICE_PROFILING_TIMER_RESOLUTION" :
			aName == CL_DEVICE_QUEUE_PROPERTIES ? "CL_DEVICE_QUEUE_PROPERTIES" :
			aName == CL_DEVICE_SINGLE_FP_CONFIG ? "CL_DEVICE_SINGLE_FP_CONFIG" :
			aName == CL_DEVICE_TYPE ? "CL_DEVICE_TYPE" :
			aName == CL_DEVICE_VENDOR ? "CL_DEVICE_VENDOR" :
			aName == CL_DEVICE_VENDOR_ID ? "CL_DEVICE_VENDOR_ID" :
			aName == CL_DEVICE_VERSION ? "CL_DEVICE_VERSION" :
			aName == CL_DRIVER_VERSION ? "CL_DRIVER_VERSION" :
			std::to_string(aName).c_str());
		std::cerr << "clGetDeviceInfo (" << mHandle.device << ", " << info << ", " << DEVICE_INFO_BUFFER_SIZE << ", " <<
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