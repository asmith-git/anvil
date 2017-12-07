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
		if (mProgram) {
			cl_int error = clReleaseProgram(mProgram);
			if (error != CL_SUCCESS) oclError("clReleaseProgram", error);
		}
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

	Program ANVIL_CALL Program::buildFromSource(Context& aContext, const char* aSource, const char* aBuildOptions) throw() {
		const char* sources[MAX_DEVICES];
		const size_t count = aContext.devices().size();
		for (size_t i = 0; i < count; ++i) sources[i] = aSource;
		return buildFromSources(aContext, sources, count, aBuildOptions);
	}

	Program ANVIL_CALL Program::buildFromSources(Context& aContext, const char** aSources, cl_uint aCount, const char* aBuildOptions) throw() {
		cl_int error = CL_SUCCESS;
		Program program;
		program.mProgram = clCreateProgramWithSource(aContext.mContext, aCount, aSources, NULL, &error);
		if (error != CL_SUCCESS) {
			oclError("clCreateProgramWithSource", error);
			return Program();
		}
		return program.build(aContext.devices(), aBuildOptions) ? std::move(program) : Program();
	}

	Program ANVIL_CALL Program::buildFromBinary(Context& aContext, const void* aBinary, size_t aLength, const char* aBuildOptions) {
		const void* binaries[MAX_DEVICES];
		size_t lengths[MAX_DEVICES];
		const size_t count = aContext.devices().size();
		for (size_t i = 0; i < count; ++i) {
			binaries[i] = aBinary;
			lengths[i] = aLength;
		}
		return buildFromBinaries(aContext, binaries, lengths, count, aBuildOptions);
	}

	Program ANVIL_CALL Program::buildFromBinaries(Context& aContext, const void** aBinaries, const size_t* aLengths, size_t aCount, const char* aBuildOptions) throw() {
		const std::vector<Device> devices = aContext.devices();
		const cl_uint deviceCount = devices.size();
		if (aCount != deviceCount) {
			oclError("clCreateProgramWithBinary", CL_INVALID_VALUE);
			return Program();
		}
		const cl_device_id* const devicePtr = deviceCount == 0 ? NULL : reinterpret_cast<const cl_device_id*>(&devices[0]);

		cl_int error = CL_SUCCESS;
		Program program;
		program.mProgram = clCreateProgramWithBinary(aContext.mContext, deviceCount, devicePtr, aLengths, reinterpret_cast<const unsigned char**>(aBinaries), NULL, &error);
		if (error != CL_SUCCESS) {
			oclError("clCreateProgramWithBinary", error);
			return Program();
		}
		return program.build(devices, aBuildOptions) ? std::move(program) : Program();
	}

	bool ANVIL_CALL Program::build(const std::vector<Device>& aDevices, const char* aOptions) throw() {
		const cl_uint deviceCount = aDevices.size();
		const cl_device_id* const devicePtr = deviceCount == 0 ? NULL : reinterpret_cast<const cl_device_id*>(&aDevices[0]);

		cl_int error = clBuildProgram(mProgram, deviceCount, devicePtr, aOptions, [](cl_program, void*){}, NULL);
		if (error != CL_SUCCESS) {
			oclError("clBuildProgram", error);
			return false;
		}
		return true;
	}
	
	Program ANVIL_CALL Program::buildFromSource(Context& aContext, const Source& aSource, const char* aBuildOptions) throw() {
		return buildFromSource(aContext, aSource.c_str(), aBuildOptions);
	}

	Program ANVIL_CALL Program::buildFromSources(Context& aContext, const std::vector<Source>& aSources, const char* aBuildOptions) throw() {
		const char* sources[MAX_DEVICES];
		const size_t count = aSources.size();
		for (size_t i = 0; i < count; ++i) sources[i] = aSources[i].c_str();
		return buildFromSources(aContext, sources, count, aBuildOptions);
	}

	Program ANVIL_CALL Program::buildFromBinary(Context& aContext, const Binary& aBinary, const char* aBuildOptions) throw() {
		return buildFromBinary(aContext, &aBinary[0], aBinary.size(), aBuildOptions);
	}

	Program ANVIL_CALL Program::buildFromBinaries(Context& aContext, const std::vector<Binary>& aBinaries, const char* aBuildOptions) throw() {
		const void* binaries[MAX_DEVICES];
		size_t sizes[MAX_DEVICES];
		const size_t count = aBinaries.size();
		for (size_t i = 0; i < count; ++i) {
			binaries[i] = &aBinaries[i];
			sizes[i] = aBinaries[i].size();
		}
		return buildFromBinaries(aContext, binaries, sizes, count, aBuildOptions);
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