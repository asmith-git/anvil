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

#include "anvil/ocl/Core.hpp"

namespace anvil { namespace ocl {
	class Device {
	private:
		cl_device_id mDevice;
		
		void* getInfo(cl_devide_info aName) const {
			enum { kBufferSize = 2048 };
			static uint8_t gBuffer[kBufferSize];
			cl_int error = clGetDeviceInfo(mDevice, aName, kBufferSize, gBuffer, nullptr);
			if(error != CL_SUCCESS) throwException("clGetDeviceInfo", error);
		}
	public:
		enum Type : cl_device_type {
			CPU = CL_DEVICE_TYPE_CPU,
			GPU = CL_DEVICE_TYPE_GPU,
			ACCELERATOR = CL_DEVICE_TYPE_ACCELERATOR,
			DEFAULT = CL_DEVICE_TYPE_DEFAULT,
			ALL = CL_DEVICE_TYPE_ALL,
		};
		
		Device() :
			mDevice(0) 
		{}
		
		Device(cl_device_id aPlatform) :
			mDevice(aPlatform) 
		{}
		
		#define ANVIL_CL_GET_INFO(type, name1, name2) type name1() const { return *reinterpret_cast<type*>(getInfo(name2)); }
		
		ANVIL_CL_GET_INFO(cl_uint,						addressBits,			    CL_DEVICE_ADDRESS_BITS);
		ANVIL_CL_GET_INFO(cl_bool,						available,				    CL_DEVICE_AVAILABLE);
		ANVIL_CL_GET_INFO(cl_bool,						compilerAvailable,		    CL_DEVICE_COMPILER_AVAILABLE);
		ANVIL_CL_GET_INFO(cl_bool,						littleEndian,			    CL_DEVICE_ENDIAN_LITTLE);
		ANVIL_CL_GET_INFO(cl_bool,						errorCorrection,		    CL_DEVICE_ERROR_CORRECTION_SUPPORT);
		ANVIL_CL_GET_INFO(cl_device_exec_capabilities,	executionCapabilities,	    CL_DEVICE_EXECUTION_CAPABILITIES);
		ANVIL_CL_GET_INFO(StringCast, 					extensions,			        CL_DEVICE_EXTENSIONS);
		ANVIL_CL_GET_INFO(cl_ulong,					    globalCacheSize,	        CL_DEVICE_GLOBAL_MEM_CACHE_SIZE);
		ANVIL_CL_GET_INFO(cl_device_mem_cache_type,	    globalCacheSize,	        CL_DEVICE_GLOBAL_MEM_CACHE_TYPE);
		ANVIL_CL_GET_INFO(cl_uint,						globalCacheLineSize,        CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE);
		ANVIL_CL_GET_INFO(cl_ulong,					    globalMemorySize,	        CL_DEVICE_GLOBAL_MEM_SIZE);
		ANVIL_CL_GET_INFO(cl_device_fp_config,			floatingPointConfiguration, CL_DEVICE_HALF_FP_CONFIG);
		ANVIL_CL_GET_INFO(cl_bool,						unifiedHostMemory,	        CL_DEVICE_HOST_UNIFIED_MEMORY);
		ANVIL_CL_GET_INFO(cl_bool,						imageSupport,		        CL_DEVICE_IMAGE_SUPPORT);
		ANVIL_CL_GET_INFO(size_t,						maxImageDepth,		        CL_DEVICE_IMAGE3D_MAX_DEPTH);
		ANVIL_CL_GET_INFO(size_t,						maxImageHeight,		        CL_DEVICE_IMAGE3D_MAX_HEIGHT);
		ANVIL_CL_GET_INFO(size_t,						maxImageWidth,		        CL_DEVICE_IMAGE3D_MAX_WIDTH);
		ANVIL_CL_GET_INFO(cl_ulong,					    localMemorySize,            CL_DEVICE_LOCAL_MEM_SIZE);
		ANVIL_CL_GET_INFO(cl_device_local_mem_type,	    localMemoryType,            CL_DEVICE_LOCAL_MEM_TYPE);
		
		//! \todo CL_DEVICE_DOUBLE_FP_CONFIG
		//! \todo CL_DEVICE_IMAGE2D_MAX_WIDTH
		//! \todo CL_DEVICE_IMAGE2D_MAX_HEIGHT
		//! \todo Other infos
		
		#undef ANVIL_CL_GET_INFO
	};
}}
