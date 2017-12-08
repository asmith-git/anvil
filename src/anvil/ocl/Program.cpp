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
		mProgram(NULL)
	{}

	ANVIL_CALL Program::Program(Context& aContext) throw() :
		mProgram(NULL)
	{}

	ANVIL_CALL Program::Program(Program&& aOther) throw() :
		mProgram(NULL)
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

	ANVIL_CALL Program::operator bool() const throw() {
		return mProgram != NULL;
	}

	void ANVIL_CALL Program::swap(Program& aOther) throw() {
		std::swap(mProgram, aOther.mProgram);
	}

	bool ANVIL_CALL Program::destroy() throw() {
		if (mProgram) {
			cl_int error = clReleaseProgram(mProgram);
			if (error != CL_SUCCESS) return oclError("clReleaseProgram", error, false);
			mProgram = NULL;
			return true;
		}
		return false;
	}

	bool ANVIL_CALL Program::createFromSource(Context& aContext, const char* aSource, const char* aBuildOptions) throw() {
		const char* sources[MAX_DEVICES];
		const size_t count = aContext.devices().size();
		for (size_t i = 0; i < count; ++i) sources[i] = aSource;
		return createFromSources(aContext, sources, count, aBuildOptions);
	}

	bool ANVIL_CALL Program::createFromSources(Context& aContext, const char** aSources, cl_uint aCount, const char* aBuildOptions) throw() {
		if (mProgram) if (!destroy()) return false;

		cl_int error = CL_SUCCESS;
		mProgram = clCreateProgramWithSource(reinterpret_cast<cl_context&>(aContext), aCount, aSources, NULL, &error);
		if (error != CL_SUCCESS) return oclError("clCreateProgramWithSource", error, false);
		return build(aContext.devices(), aBuildOptions);
	}

	bool ANVIL_CALL Program::createFromBinary(Context& aContext, const void* aBinary, size_t aLength, const char* aBuildOptions) {
		const void* binaries[MAX_DEVICES];
		size_t lengths[MAX_DEVICES];
		const size_t count = aContext.devices().size();
		for (size_t i = 0; i < count; ++i) {
			binaries[i] = aBinary;
			lengths[i] = aLength;
		}
		return createFromBinaries(aContext, binaries, lengths, count, aBuildOptions);
	}

	bool ANVIL_CALL Program::createFromBinaries(Context& aContext, const void** aBinaries, const size_t* aLengths, size_t aCount, const char* aBuildOptions) throw() {
		if (mProgram) if (!destroy()) return false;

		const std::vector<Device> devices = aContext.devices();
		const cl_uint deviceCount = devices.size();
		if (aCount != deviceCount) return oclError("clCreateProgramWithBinary", CL_INVALID_VALUE, false);
		const cl_device_id* const devicePtr = deviceCount == 0 ? NULL : reinterpret_cast<const cl_device_id*>(&devices[0]);

		cl_int error = CL_SUCCESS;
		mProgram = clCreateProgramWithBinary(reinterpret_cast<cl_context&>(aContext), deviceCount, devicePtr, aLengths, reinterpret_cast<const unsigned char**>(aBinaries), NULL, &error);
		if (error != CL_SUCCESS) return oclError("clCreateProgramWithBinary", error, false);
		return build(devices, aBuildOptions);
	}

	bool ANVIL_CALL Program::build(const std::vector<Device>& aDevices, const char* aOptions) throw() {
		const cl_uint deviceCount = aDevices.size();
		const cl_device_id* const devicePtr = deviceCount == 0 ? NULL : reinterpret_cast<const cl_device_id*>(&aDevices[0]);

		cl_int error = clBuildProgram(mProgram, deviceCount, devicePtr, aOptions, [](cl_program, void*){}, NULL);
		return error == CL_SUCCESS ? true : oclError("clBuildProgram", error, false);
	}
	
	bool ANVIL_CALL Program::create(Context& aContext, const Source& aSource, const char* aBuildOptions) throw() {
		return createFromSource(aContext, aSource.c_str(), aBuildOptions);
	}

	bool ANVIL_CALL Program::create(Context& aContext, const std::vector<Source>& aSources, const char* aBuildOptions) throw() {
		const char* sources[MAX_DEVICES];
		const size_t count = aSources.size();
		for (size_t i = 0; i < count; ++i) sources[i] = aSources[i].c_str();
		return createFromSources(aContext, sources, count, aBuildOptions);
	}

	bool ANVIL_CALL Program::create(Context& aContext, const Binary& aBinary, const char* aBuildOptions) throw() {
		return createFromBinary(aContext, &aBinary[0], aBinary.size(), aBuildOptions);
	}

	bool ANVIL_CALL Program::create(Context& aContext, const std::vector<Binary>& aBinaries, const char* aBuildOptions) throw() {
		const void* binaries[MAX_DEVICES];
		size_t sizes[MAX_DEVICES];
		const size_t count = aBinaries.size();
		for (size_t i = 0; i < count; ++i) {
			binaries[i] = &aBinaries[i];
			sizes[i] = aBinaries[i].size();
		}
		return createFromBinaries(aContext, binaries, sizes, count, aBuildOptions);
	}

	Program::Source Program::source() const throw() {
		size_t size = 0;
		cl_int error = clGetProgramInfo(mProgram, CL_PROGRAM_SOURCE, 0, NULL, &size);
		if (error != CL_SUCCESS) {
			oclError("clGetProgramInfo", error);
			return Source();
		}

		Source source(size, '?');
		error = clGetProgramInfo(mProgram, CL_PROGRAM_SOURCE, size, &source[0], NULL);
		if (error != CL_SUCCESS) {
			oclError("clGetProgramInfo", error);
			return Source();
		}
		return source;
	}

	std::vector<Program::Binary> Program::binaries() const throw() {
		size_t sizes[MAX_DEVICES];

		size_t size = 0;
		cl_int error = clGetProgramInfo(mProgram, CL_PROGRAM_BINARY_SIZES, sizeof(size_t) * MAX_DEVICES, sizes, &size);
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
		error = clGetProgramInfo(mProgram, CL_PROGRAM_BINARIES, size * sizeof(unsigned char*), binary_ptrs, NULL);
		if (error != CL_SUCCESS) {
			oclError("clGetProgramInfo", error);
			delete[] binary_ptrs;
			return std::vector<Program::Binary>();
		}
		delete[] binary_ptrs;
		return binaries;
	}

}}