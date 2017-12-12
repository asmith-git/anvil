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

#include <iostream>
#include "anvil/ocl/Program.hpp"

namespace anvil { namespace ocl {

	// Program

	ANVIL_CALL Program::Program() throw() :
		Object(PROGRAM)
	{}

	ANVIL_CALL Program::Program(Context& aContext) throw() :
		Object(PROGRAM)
	{}

	ANVIL_CALL Program::Program(Program&& aOther) throw() :
		Object(PROGRAM) 
	{
		swap(aOther);
	}

	ANVIL_CALL Program::~Program() throw() {
		destroy();
	}

	Program& ANVIL_CALL Program::operator=(Program&& aOther) throw() {
		swap(aOther);
		return *this;
	}

	void ANVIL_CALL Program::swap(Program& aOther) throw() {
		std::swap(mHandle, aOther.mHandle);
	}

	bool ANVIL_CALL Program::destroy() throw() {
		if (mHandle.program) {
			cl_int error = clReleaseProgram(mHandle.program);
			if (error != CL_SUCCESS) return oclError("clReleaseProgram", error, false);
			mHandle.program = NULL;
			return true;
		}
		return false;
	}

	bool ANVIL_CALL Program::create(Handle aHandle) throw() {
		if (aHandle.type != PROGRAM) return false;
		if (mHandle.program != NULL) if (!destroy()) return false;
		if (aHandle.program) {
			mHandle = aHandle;
			cl_int error = clRetainProgram(mHandle.program);
			if (error != CL_SUCCESS) return oclError("clRetainProgram", error, false);
		}
		return true;
	}

	bool ANVIL_CALL Program::createFromSource(Context& aContext, const char* aSource, const char* aBuildOptions) throw() {
		return createFromSources(aContext, &aSource, 1, aBuildOptions);
	}

	bool ANVIL_CALL Program::createFromSources(Context& aContext, const char** aSources, cl_uint aCount, const char* aBuildOptions) throw() {
		if (mHandle.program) if (!destroy()) return false;

		cl_int error = CL_SUCCESS;
		mHandle.program = clCreateProgramWithSource(aContext.mHandle.context, aCount, aSources, NULL, &error);
		if (error != CL_SUCCESS) return oclError("clCreateProgramWithSource", error, false);

		std::vector<Device> devices = aContext.devices();
		const size_t deviceCount = devices.size();
		cl_device_id devicePtr[Platform::MAX_DEVICES];
		if (deviceCount != 0) for (size_t i = 0; i < deviceCount; ++i) devicePtr[i] = devices[i].mHandle.device;

		return build(devicePtr, deviceCount, aBuildOptions);
	}

	bool ANVIL_CALL Program::createFromBinary(Context& aContext, const void* aBinary, size_t aLength, const char* aBuildOptions) {
		const void* binaries[Platform::MAX_DEVICES];
		size_t lengths[Platform::MAX_DEVICES];
		const size_t count = aContext.devices().size();
		for (size_t i = 0; i < count; ++i) {
			binaries[i] = aBinary;
			lengths[i] = aLength;
		}
		return createFromBinaries(aContext, binaries, lengths, count, aBuildOptions);
	}

	bool ANVIL_CALL Program::createFromBinaries(Context& aContext, const void** aBinaries, const size_t* aLengths, size_t aCount, const char* aBuildOptions) throw() {
		if (mHandle.program) if (!destroy()) return false;

		std::vector<Device> devices = aContext.devices();
		const cl_uint deviceCount = devices.size();
		if (deviceCount != aCount) return oclError("(binary count)", CL_INVALID_DEVICE, false);
		if (aCount != deviceCount) return oclError("clCreateProgramWithBinary", CL_INVALID_VALUE, false);
		cl_device_id devicePtr[Platform::MAX_DEVICES];
		if (deviceCount != 0) for (cl_uint i = 0; i < deviceCount; ++i) devicePtr[i] = devices[i].mHandle.device;

		cl_int error = CL_SUCCESS;
		mHandle.program = clCreateProgramWithBinary(aContext.handle().context, deviceCount, devicePtr, aLengths, reinterpret_cast<const unsigned char**>(aBinaries), NULL, &error);
		if (error != CL_SUCCESS) return oclError("clCreateProgramWithBinary", error, false);
		return build(devicePtr, deviceCount, aBuildOptions);
	}

	bool ANVIL_CALL Program::build(const cl_device_id* aDevices, size_t aDeviceCount, const char* aOptions) throw() {
		cl_int error = clBuildProgram(mHandle.program, aDeviceCount, aDevices, aOptions, NULL, NULL);

		if (error != CL_SUCCESS) {
			oclError("clBuildProgram", error);
			if (error == CL_BUILD_PROGRAM_FAILURE) {
				enum { ERROR_LOG_SIZE = 1024 };
				char log[ERROR_LOG_SIZE];
				for (size_t i = 0; i < aDeviceCount; ++i) {
					error = clGetProgramBuildInfo(mHandle.program, aDevices[i], CL_PROGRAM_BUILD_LOG, ERROR_LOG_SIZE, log, NULL);
					std::cerr << "Error log : " << log << std::endl;
					if (error != CL_SUCCESS) oclError("clGetProgramBuildInfo", error);
				}
			}
			return false;
		}

		return true;
	}
	
	bool ANVIL_CALL Program::create(Context& aContext, const Source& aSource, const char* aBuildOptions) throw() {
		return createFromSource(aContext, aSource.c_str(), aBuildOptions);
	}

	bool ANVIL_CALL Program::create(Context& aContext, const std::vector<Source>& aSources, const char* aBuildOptions) throw() {
		const char* sources[Platform::MAX_DEVICES];
		const size_t count = aSources.size();
		for (size_t i = 0; i < count; ++i) sources[i] = aSources[i].c_str();
		return createFromSources(aContext, sources, count, aBuildOptions);
	}

	bool ANVIL_CALL Program::create(Context& aContext, const Binary& aBinary, const char* aBuildOptions) throw() {
		return createFromBinary(aContext, &aBinary[0], aBinary.size(), aBuildOptions);
	}

	bool ANVIL_CALL Program::create(Context& aContext, const std::vector<Binary>& aBinaries, const char* aBuildOptions) throw() {
		const void* binaries[Platform::MAX_DEVICES];
		size_t sizes[Platform::MAX_DEVICES];
		const size_t count = aBinaries.size();
		for (size_t i = 0; i < count; ++i) {
			binaries[i] = &aBinaries[i];
			sizes[i] = aBinaries[i].size();
		}
		return createFromBinaries(aContext, binaries, sizes, count, aBuildOptions);
	}

	Program::Source Program::source() const throw() {
		size_t size = 0;
		cl_int error = clGetProgramInfo(mHandle.program, CL_PROGRAM_SOURCE, 0, NULL, &size);
		if (error != CL_SUCCESS) {
			oclError("clGetProgramInfo", error);
			return Source();
		}

		Source source(size, '?');
		error = clGetProgramInfo(mHandle.program, CL_PROGRAM_SOURCE, size, &source[0], NULL);
		if (error != CL_SUCCESS) {
			oclError("clGetProgramInfo", error);
			return Source();
		}
		return source;
	}

	std::vector<Program::Binary> Program::binaries() const throw() {
		size_t sizes[Platform::MAX_DEVICES];

		size_t size = 0;
		cl_int error = clGetProgramInfo(mHandle.program, CL_PROGRAM_BINARY_SIZES, sizeof(size_t) * Platform::MAX_DEVICES, sizes, &size);
		if (error != CL_SUCCESS) {
			oclError("clGetProgramInfo", error);
			return std::vector<Program::Binary>();
		}
		size /= sizeof(size_t);

		std::vector<Program::Binary> binaries(size, Binary());
		unsigned char** binary_ptrs = new unsigned char*[size];
		for (size_t i = 0; i < size; ++i) {
			binaries[i] = Binary(sizes[i], 0);
			binary_ptrs[i] = &binaries[i][0];
		}

		Source source(size, '?');
		error = clGetProgramInfo(mHandle.program, CL_PROGRAM_BINARIES, size * sizeof(unsigned char*), binary_ptrs, NULL);
		if (error != CL_SUCCESS) {
			oclError("clGetProgramInfo", error);
			delete[] binary_ptrs;
			return std::vector<Program::Binary>();
		}
		delete[] binary_ptrs;
		return binaries;
	}

	std::vector<Device> ANVIL_CALL Program::devices() const throw() {
		size_t count;
		cl_int error = clGetProgramInfo(mHandle.program, CL_PROGRAM_NUM_DEVICES, sizeof(size_t), &count, NULL);
		if (error != CL_SUCCESS) {
			oclError("clGetProgramInfo", error);
			return std::vector<Device>();
		}
		if(count == 0) return  std::vector<Device>();

		cl_device_id deviceIDS[Platform::MAX_DEVICES];
		error = clGetProgramInfo(mHandle.program, CL_PROGRAM_NUM_DEVICES, sizeof(cl_device_id) * count, deviceIDS, NULL);
		if (error != CL_SUCCESS) {
			oclError("clGetProgramInfo", error);
			return std::vector<Device>();
		}
		std::vector<Device> devices(count, Device());
		for (size_t i = 0; i < count; ++i) devices[i].mHandle.device = deviceIDS[i];
		return devices;
	}

}}