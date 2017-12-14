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

#ifndef ANVIL_OCL_DEVICE_HPP
#define ANVIL_OCL_DEVICE_HPP

#include <vector>
#include "anvil/ocl/Core.hpp"

namespace anvil { namespace ocl {

	//! \todo Sub-devices

	class Device : public Object {
	private:
		void* ANVIL_CALL getInfo(cl_device_info aName) const;

		ANVIL_CALL Device(cl_device_id);
	public:
		enum Type : cl_device_type {
			CPU = CL_DEVICE_TYPE_CPU,
			GPU = CL_DEVICE_TYPE_GPU,
			ACCELERATOR = CL_DEVICE_TYPE_ACCELERATOR,
			DEFAULT = CL_DEVICE_TYPE_DEFAULT,
			ALL = CL_DEVICE_TYPE_ALL,
		};
		
		ANVIL_CALL Device();
		static std::vector<Device> ANVIL_CALL devices(Device::Type aType = Device::ALL);
		
		struct WorkItemCount {
			size_t x;
			size_t y;
			size_t z;
		};

		#define ANVIL_CL_GET_INFO(type, ptr, name1, name2) inline type ANVIL_CALL name1() const { return ptr reinterpret_cast<type ptr>(getInfo(name2)); }
		
		ANVIL_CL_GET_INFO(cl_uint, *,						addressBits,			    CL_DEVICE_ADDRESS_BITS);
		ANVIL_CL_GET_INFO(cl_bool, *,						available,				    CL_DEVICE_AVAILABLE);
		ANVIL_CL_GET_INFO(cl_bool, *,						compilerAvailable,		    CL_DEVICE_COMPILER_AVAILABLE);
		ANVIL_CL_GET_INFO(cl_bool, *,						littleEndian,			    CL_DEVICE_ENDIAN_LITTLE);
		ANVIL_CL_GET_INFO(cl_bool, *,						errorCorrection,		    CL_DEVICE_ERROR_CORRECTION_SUPPORT);
		ANVIL_CL_GET_INFO(cl_device_exec_capabilities, *,   executionCapabilities,      CL_DEVICE_EXECUTION_CAPABILITIES);
		ANVIL_CL_GET_INFO(const char*, , 					extensions,			        CL_DEVICE_EXTENSIONS);
		ANVIL_CL_GET_INFO(cl_ulong, *,					    globalCacheSize,	        CL_DEVICE_GLOBAL_MEM_CACHE_SIZE);
		ANVIL_CL_GET_INFO(cl_device_mem_cache_type, *,	    globalCacheType,	        CL_DEVICE_GLOBAL_MEM_CACHE_TYPE);
		ANVIL_CL_GET_INFO(cl_uint, *,						globalCacheLineSize,        CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE);
		ANVIL_CL_GET_INFO(cl_ulong, *,					    globalMemorySize,	        CL_DEVICE_GLOBAL_MEM_SIZE);
		ANVIL_CL_GET_INFO(cl_bool, *,						unifiedHostMemory,	        CL_DEVICE_HOST_UNIFIED_MEMORY);
		ANVIL_CL_GET_INFO(cl_bool, *,						imageSupport,		        CL_DEVICE_IMAGE_SUPPORT);
		ANVIL_CL_GET_INFO(size_t, *,						maxImageHeight2D,		    CL_DEVICE_IMAGE2D_MAX_HEIGHT);
		ANVIL_CL_GET_INFO(size_t, *,						maxImageWidth2D,		    CL_DEVICE_IMAGE2D_MAX_WIDTH);
		ANVIL_CL_GET_INFO(size_t, *,						maxImageDepth3D,		    CL_DEVICE_IMAGE3D_MAX_DEPTH);
		ANVIL_CL_GET_INFO(size_t, *,						maxImageHeight3D,		    CL_DEVICE_IMAGE3D_MAX_HEIGHT);
		ANVIL_CL_GET_INFO(size_t, *,						maxImageWidth3D,		    CL_DEVICE_IMAGE3D_MAX_WIDTH);
		ANVIL_CL_GET_INFO(cl_ulong, *,                      localMemorySize,            CL_DEVICE_LOCAL_MEM_SIZE);
		ANVIL_CL_GET_INFO(cl_uint, *,                       maxClockFrequency,          CL_DEVICE_MAX_CLOCK_FREQUENCY);
		ANVIL_CL_GET_INFO(cl_uint, *, maxComputeUnits, CL_DEVICE_MAX_COMPUTE_UNITS);
		ANVIL_CL_GET_INFO(cl_uint, *, maxConstantArgs, CL_DEVICE_MAX_CONSTANT_ARGS);
		ANVIL_CL_GET_INFO(cl_ulong, *, maxConstantBufferSize, CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE);
		ANVIL_CL_GET_INFO(cl_ulong, *, maxMemAllocSize, CL_DEVICE_MAX_MEM_ALLOC_SIZE);
		ANVIL_CL_GET_INFO(size_t, *, maxParameterSize, CL_DEVICE_MAX_PARAMETER_SIZE);
		ANVIL_CL_GET_INFO(cl_uint, *, maxReadImageArgs, CL_DEVICE_MAX_READ_IMAGE_ARGS);
		ANVIL_CL_GET_INFO(cl_uint, *, maxSamplers, CL_DEVICE_MAX_SAMPLERS);
		ANVIL_CL_GET_INFO(size_t, *, maxWorkGroupSize, CL_DEVICE_MAX_WORK_GROUP_SIZE);
		ANVIL_CL_GET_INFO(cl_uint, *, maxWorkItemDimensions, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS);
		ANVIL_CL_GET_INFO(WorkItemCount, *, maxWorkItems, CL_DEVICE_MAX_WORK_ITEM_SIZES);
		ANVIL_CL_GET_INFO(cl_uint, *, maxWriteImageArgs, CL_DEVICE_MAX_WRITE_IMAGE_ARGS);
		ANVIL_CL_GET_INFO(cl_uint, *, memBaseAddressAlign, CL_DEVICE_MEM_BASE_ADDR_ALIGN);
		ANVIL_CL_GET_INFO(cl_uint, *, minDataTypeAlignmentSize, CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE);
		ANVIL_CL_GET_INFO(const char*, , name, CL_DEVICE_NAME);
		ANVIL_CL_GET_INFO(cl_uint, *, nativeVectorWidthChar, CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR);
		ANVIL_CL_GET_INFO(cl_uint, *, nativeVectorWidthSshort, CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT);
		ANVIL_CL_GET_INFO(cl_uint, *, nativeVectorWidthInt, CL_DEVICE_NATIVE_VECTOR_WIDTH_INT);
		ANVIL_CL_GET_INFO(cl_uint, *, nativeVectorWidthLong, CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG);
		ANVIL_CL_GET_INFO(cl_uint, *, nativeVectorWidthFloat, CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT);
		ANVIL_CL_GET_INFO(cl_uint, *, nativeVectorWidthDouble, CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE);
		ANVIL_CL_GET_INFO(cl_uint, *, nativeVectorWidthHalf, CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF);
		ANVIL_CL_GET_INFO(const char*, , cVersion, CL_DEVICE_OPENCL_C_VERSION);
		ANVIL_CL_GET_INFO(cl_platform_id, *, platform, CL_DEVICE_PLATFORM);
		ANVIL_CL_GET_INFO(cl_uint, *, preferedVectorWidthChar,    CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR);
		ANVIL_CL_GET_INFO(cl_uint, *, preferedVectorWidthSshort,  CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT);
		ANVIL_CL_GET_INFO(cl_uint, *, preferedVectorWidthInt,     CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT);
		ANVIL_CL_GET_INFO(cl_uint, *, preferedVectorWidthLong,    CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG);
		ANVIL_CL_GET_INFO(cl_uint, *, preferedVectorWidthFloat,   CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT);
		ANVIL_CL_GET_INFO(cl_uint, *, preferedVectorWidthDouble,  CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE);
		ANVIL_CL_GET_INFO(cl_uint, *, preferedVectorWidthHalf,    CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF);
		ANVIL_CL_GET_INFO(const char*, , profile, CL_DEVICE_PROFILE);
		ANVIL_CL_GET_INFO(size_t, *, profilingTimerResolution, CL_DEVICE_PROFILING_TIMER_RESOLUTION);
		ANVIL_CL_GET_INFO(Type, *, queueProperties, CL_DEVICE_QUEUE_PROPERTIES);
		ANVIL_CL_GET_INFO(cl_device_type, *, deviceType, CL_DEVICE_TYPE);
		ANVIL_CL_GET_INFO(const char*, , vendor, CL_DEVICE_VENDOR);
		ANVIL_CL_GET_INFO(cl_uint, *, vendorID, CL_DEVICE_VENDOR_ID);
		ANVIL_CL_GET_INFO(const char*, , version, CL_DEVICE_VERSION);
		ANVIL_CL_GET_INFO(const char*, , driverVersion, CL_DRIVER_VERSION);
		
		//! \todo CL_DEVICE_DOUBLE_FP_CONFIG, CL_DEVICE_HALF_FP_CONFIG
	
		#undef ANVIL_CL_GET_INFO

		// Inherited from Object

		bool ANVIL_CALL create(Handle) throw() override;
		bool ANVIL_CALL destroy() throw() override;
		cl_uint ANVIL_CALL referenceCount() const throw() override;
		Handle::Type ANVIL_CALL type() const throw() override;
	};
}}

#endif