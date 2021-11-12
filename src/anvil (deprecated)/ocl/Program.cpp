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
		Object(Handle::PROGRAM)
	{}

	ANVIL_CALL Program::Program(Context& aContext) throw() :
		Object(Handle::PROGRAM)
	{}

	ANVIL_CALL Program::Program(Program&& aOther) throw() :
		Object(Handle::PROGRAM)
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
#ifdef ANVIL_LOG_OCL
			std::cerr << getErrorName(error) << " <- clReleaseProgram (" << mHandle.program << ")" << std::endl;
#endif
			if (error != CL_SUCCESS) return oclError("clReleaseProgram", error);
			onDestroy();
			mHandle.program = NULL;
			return true;
		} else {
			return false;
		}
	}

	bool ANVIL_CALL Program::retain() throw() {
		if (mHandle.program) {
			cl_int error = clRetainProgram(mHandle.program);
#ifdef ANVIL_LOG_OCL
			std::cerr << getErrorName(error) << " <- clRetainProgram (" << mHandle.program << ")" << std::endl;
#endif
			return error == CL_SUCCESS ? true : oclError("clRetainProgram", error);
		}
		return false;
	}

	bool ANVIL_CALL Program::createFromSource(Context& aContext, const char* aSource, const char* aBuildOptions) throw() {
		return createFromSources(aContext, &aSource, 1, aBuildOptions);
	}

	bool ANVIL_CALL Program::createFromSources(Context& aContext, const char** aSources, cl_uint aCount, const char* aBuildOptions) throw() {
		if (mHandle.program) if (!destroy()) return false;

		cl_int error = CL_SUCCESS;
		mHandle.program = clCreateProgramWithSource(aContext.handle(), aCount, aSources, NULL, &error);
#ifdef ANVIL_LOG_OCL
		std::cerr << getErrorName(error) << " <- clCreateProgramWithSource (" << aContext.handle().context << ", " << aCount << ", " << aSources << ", " <<
			"NULL" << ", " << &error << ")" << std::endl;
#endif
		if (error != CL_SUCCESS) return oclError("clCreateProgramWithSource", error);

		std::vector<std::shared_ptr<Device>> devices = aContext.devices();
		const size_t deviceCount = devices.size();
		cl_device_id devicePtr[Platform::MAX_DEVICES];
		if (deviceCount != 0) for (size_t i = 0; i < deviceCount; ++i) devicePtr[i] = devices[i]->handle();

		return build(devicePtr, deviceCount, aBuildOptions);
	}

	bool ANVIL_CALL Program::createFromBinary(Context& aContext, const uint8_t* aBinary, size_t aLength) {
		const uint8_t* binaries[Platform::MAX_DEVICES];
		size_t lengths[Platform::MAX_DEVICES];
		const size_t count = aContext.devices().size();
		for (size_t i = 0; i < count; ++i) {
			binaries[i] = aBinary;
			lengths[i] = aLength;
		}
		return createFromBinaries(aContext, binaries, lengths, count);
	}

	bool ANVIL_CALL Program::createFromBinaries(Context& aContext, const uint8_t** aBinaries, const size_t* aLengths, size_t aCount) throw() {
		if (mHandle.program) if (!destroy()) return false;

		std::vector<std::shared_ptr<Device>> devices = aContext.devices();
		const cl_uint deviceCount = devices.size();
		if (deviceCount != aCount) return oclError("anvil::ocl::Program::createFromBinaries", CL_INVALID_DEVICE, "Binary and device count differ");
		cl_device_id devicePtr[Platform::MAX_DEVICES];
		cl_int binaryStatus[Platform::MAX_DEVICES];
		if (deviceCount != 0) for (cl_uint i = 0; i < deviceCount; ++i) devicePtr[i] = devices[i]->handle();

		cl_int error = CL_SUCCESS;
		mHandle.program = clCreateProgramWithBinary(aContext.handle(), deviceCount, devicePtr, aLengths, aBinaries, binaryStatus, &error);
#ifdef ANVIL_LOG_OCL
		std::cerr << getErrorName(error) << " <- clCreateProgramWithBinary (" << aContext.handle().context << ", " << deviceCount << ", " << devicePtr <<
			", " <<aLengths << ", " <<aBinaries << ", " <<binaryStatus << ", " <<&error << ")" << std::endl;
#endif
		if (error != CL_SUCCESS) {
			oclError("clCreateProgramWithBinary", error);
			for (cl_uint i = 0; i < deviceCount; ++i) {
				std::string msg = devices[i]->name();
				msg += " ";
				msg += binaryStatus[i] == CL_SUCCESS ? "CL_SUCCESS " : binaryStatus[i] == CL_INVALID_VALUE ? "CL_INVALID_VALUE " : "CL_INVALID_BINARY ";
				oclError("anvil::ocl::Program::createFromBinaries", error, msg.c_str());
			}
			return false;
		}
		return build(devicePtr, deviceCount, NULL);
	}

	bool ANVIL_CALL Program::build(const cl_device_id* aDevices, size_t aDeviceCount, const char* aOptions) throw() {
		cl_int error = clBuildProgram(mHandle.program, aDeviceCount, aDevices, aOptions, NULL, NULL);
#ifdef ANVIL_LOG_OCL
		std::cerr << getErrorName(error) << " <- clBuildProgram (" << mHandle.program << ", " << aDeviceCount << ", " << aDevices << ", " <<
			(void*) aOptions << ", " << "NULL" << ", " << "NULL" << ")" << std::endl;
#endif

		if (error != CL_SUCCESS) {
			oclError("clBuildProgram", error);
			if (error == CL_BUILD_PROGRAM_FAILURE) {
				std::string log;
				Handle h;
				h.type = Handle::DEVICE;
				for (size_t i = 0; i < aDeviceCount; ++i) {
					size_t logSize;
					error = clGetProgramBuildInfo(mHandle.program, aDevices[i], CL_PROGRAM_BUILD_LOG, 0, NULL, &logSize);
#ifdef ANVIL_LOG_OCL
					std::cerr << getErrorName(error) << " <- clGetProgramBuildInfo (" << mHandle.program << ", " << aDevices[i] << ", " << "CL_PROGRAM_BUILD_LOG" <<
						", " << 0 << ", " << "NULL" << ", " << &logSize << ")" << std::endl;
#endif
					if (error != CL_SUCCESS) oclError("clGetProgramBuildInfo", error, "CL_PROGRAM_BUILD_LOG");
					if (log.size() < logSize) log.resize(logSize, '?');

					error = clGetProgramBuildInfo(mHandle.program, aDevices[i], CL_PROGRAM_BUILD_LOG, logSize, const_cast<char*>(log.c_str()), NULL);
#ifdef ANVIL_LOG_OCL
					std::cerr << getErrorName(error) << " <- clGetProgramBuildInfo (" << mHandle.program << ", " << aDevices[i] << ", " << "CL_PROGRAM_BUILD_LOG" <<
						", " << logSize << ", " << (void*) const_cast<char*>(log.c_str()) << ", " << "NULL" << ")" << std::endl;
#endif
					h.device = aDevices[i];
					Device d;
					d.create(h);
					if (error != CL_SUCCESS) oclError("clGetProgramBuildInfo", error, "CL_PROGRAM_BUILD_LOG");
					else oclError("anvil::ocl::Program::build", CL_BUILD_PROGRAM_FAILURE, (d.name() + std::string(", ") + log).c_str());
				}
			}
			return false;
		}
		onCreate();
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

	bool ANVIL_CALL Program::create(Context& aContext, const Binary& aBinary) throw() {
		return createFromBinary(aContext, &aBinary[0], aBinary.size());
	}

	bool ANVIL_CALL Program::create(Context& aContext, const std::vector<Binary>& aBinaries) throw() {
		const uint8_t* binaries[Platform::MAX_DEVICES];
		size_t sizes[Platform::MAX_DEVICES];
		const size_t count = aBinaries.size();
		for (size_t i = 0; i < count; ++i) {
			binaries[i] = &aBinaries[i][0];
			sizes[i] = aBinaries[i].size();
		}
		return createFromBinaries(aContext, binaries, sizes, count);
	}

	Program::Source Program::source() const throw() {
		size_t size = 0;
		cl_int error = clGetProgramInfo(mHandle.program, CL_PROGRAM_SOURCE, 0, NULL, &size);
#ifdef ANVIL_LOG_OCL
		std::cerr << getErrorName(error) << " <- clGetProgramInfo (" << mHandle.program << ", " << "CL_PROGRAM_SOURCE" << ", " << 0 << ", " << "NULL" <<
			", " << &size << ")" << std::endl;
#endif
		if (error != CL_SUCCESS) {
			oclError("clGetProgramInfo", error, "CL_PROGRAM_SOURCE");
			return Source();
		}

		Source source(size, '?');
#ifdef ANVIL_LOG_OCL
		std::cerr << "clGetProgramInfo (" << mHandle.program << ", " << "CL_PROGRAM_SOURCE" << ", " << size << ", " << (void*)&source[0] << 
			", " << "NULL" << ")" << std::endl;
#endif
		error = clGetProgramInfo(mHandle.program, CL_PROGRAM_SOURCE, size, &source[0], NULL);
		if (error != CL_SUCCESS) {
			oclError("clGetProgramInfo", error, "CL_PROGRAM_SOURCE");
			return Source();
		}
		return source;
	}

	std::vector<Program::Binary> Program::binaries() const throw() {
		size_t sizes[Platform::MAX_DEVICES];

		size_t size = 0;
		cl_int error = clGetProgramInfo(mHandle.program, CL_PROGRAM_BINARY_SIZES, sizeof(size_t) * Platform::MAX_DEVICES, sizes, &size);
#ifdef ANVIL_LOG_OCL
		std::cerr << getErrorName(error) << " <- clGetProgramInfo (" << mHandle.program << ", " << "CL_PROGRAM_BINARY_SIZES" << ", " << sizeof(size_t) * Platform::MAX_DEVICES <<
			", " << sizes << ", " << &size << ")" << std::endl;
#endif
		if (error != CL_SUCCESS) {
			oclError("clGetProgramInfo", error, "CL_PROGRAM_BINARY_SIZES");
			return std::vector<Program::Binary>();
		}
		size /= sizeof(size_t);

		std::vector<Program::Binary> binaries(size, Binary());
		unsigned char** binary_ptrs = new unsigned char*[size];
		for (size_t i = 0; i < size; ++i) {
			binaries[i] = Binary(sizes[i], 0);
			binary_ptrs[i] = &binaries[i][0];
		}

		error = clGetProgramInfo(mHandle.program, CL_PROGRAM_BINARIES, size * sizeof(unsigned char*), binary_ptrs, NULL);
#ifdef ANVIL_LOG_OCL
		std::cerr << getErrorName(error) << " <- clGetProgramInfo (" << mHandle.program << ", " << "CL_PROGRAM_BINARIES" << ", " << size * sizeof(unsigned char*) <<
			", " << binary_ptrs << ", " << "NULL" << ")" << std::endl;
#endif
		if (error != CL_SUCCESS) {
			oclError("clGetProgramInfo", error, "CL_PROGRAM_BINARIES");
			delete[] binary_ptrs;
			return std::vector<Program::Binary>();
		}
		delete[] binary_ptrs;
		return binaries;
	}

	std::vector<std::shared_ptr<Device>> ANVIL_CALL Program::devices() const throw() {
		size_t count;

		cl_int error = clGetProgramInfo(mHandle.program, CL_PROGRAM_NUM_DEVICES, sizeof(size_t), &count, NULL);
#ifdef ANVIL_LOG_OCL
		std::cerr << getErrorName(error) << " <- clGetProgramInfo (" << mHandle.program << ", " << "CL_PROGRAM_NUM_DEVICES" << ", " << sizeof(size_t) <<
			", " << &count << ", " << "NULL" << ")" << std::endl;
#endif
		if (error != CL_SUCCESS) {
			oclError("clGetProgramInfo", error, "CL_PROGRAM_NUM_DEVICES");
			return std::vector<std::shared_ptr<Device>>();
		}
		if(count == 0) return  std::vector<std::shared_ptr<Device>>();

		cl_device_id deviceIDS[Platform::MAX_DEVICES];
		error = clGetProgramInfo(mHandle.program, CL_PROGRAM_DEVICES, sizeof(cl_device_id) * count, deviceIDS, NULL);
#ifdef ANVIL_LOG_OCL
		std::cerr << getErrorName(error) << " <- clGetProgramInfo (" << mHandle.program << ", " << "CL_PROGRAM_DEVICES" << ", " << sizeof(cl_device_id) * count <<
			", " << deviceIDS << ", " << "NULL" << ")" << std::endl;
#endif
		if (error != CL_SUCCESS) {
			oclError("clGetProgramInfo", error, "CL_PROGRAM_DEVICES");
			return std::vector<std::shared_ptr<Device>>();
		}
		std::vector<std::shared_ptr<Device>> devices(count, std::shared_ptr<Device>());
		for (size_t i = 0; i < count; ++i) {
			devices[i].swap(std::shared_ptr<Device>(new Device()));
			devices[i]->create(deviceIDS[i]);
		}
		return devices;
	}

	cl_uint ANVIL_CALL Program::referenceCount() const throw() {
		cl_uint count;
		cl_uint error = clGetProgramInfo(mHandle.program, CL_PROGRAM_REFERENCE_COUNT, sizeof(count), &count, NULL);
#ifdef ANVIL_LOG_OCL
		std::cerr << getErrorName(error) << " <- clGetProgramInfo (" << mHandle.program << ", " << "CL_PROGRAM_REFERENCE_COUNT" << ", " << sizeof(count) <<
			", " << &count << ", " << "NULL" << ")" << std::endl;
#endif
		if (error == CL_SUCCESS) return count;
		oclError("clGetProgramInfo", error, "CL_PROGRAM_REFERENCE_COUNT");
		return 0;
	}

	Context ANVIL_CALL Program::context() const throw() {
		Handle h;
		h.type = Handle::CONTEXT;
		Context tmp;
		cl_uint error = clGetProgramInfo(mHandle.program, CL_PROGRAM_CONTEXT, sizeof(cl_context), &h.context, NULL);
#ifdef ANVIL_LOG_OCL
		std::cerr << getErrorName(error) << " <- clGetProgramInfo (" << mHandle.program << ", " << "CL_PROGRAM_CONTEXT" << ", " << sizeof(cl_context) <<
			", " << &h.context << ", " << "NULL" << ")" << std::endl;
#endif
		if (error != CL_SUCCESS) oclError("clGetProgramInfo", error, "CL_PROGRAM_CONTEXT");
		if (h.context) tmp.Object::create(h);
		return std::move(tmp);
	}

	Handle::Type ANVIL_CALL Program::type() const throw() {
		return Handle::PROGRAM;
	}
}}