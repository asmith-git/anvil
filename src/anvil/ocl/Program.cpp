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

	ANVIL_CALL Program::Program(Context& aContext) :
		mContext(aContext),
		mProgram(NULL),
		mState(INITIALISED)
	{}

	ANVIL_CALL Program::~Program() {
		if (mProgram) {
			clReleaseProgram(mProgram);
		}
	}

	void ANVIL_CALL Program::setSource(const char* aSource) {
		setSources(&aSource, 1);
	}

	void ANVIL_CALL Program::setSources(const char** aSources, cl_uint aCount) {
		if (mState != INITIALISED) {
			ANVIL_RUNTIME_ASSERT(false, "Program source has already been set");
			return;
		}

		cl_int error = CL_SUCCESS;
		mProgram = clCreateProgramWithSource(mContext.mContext, aCount, aSources, NULL, &error);
		mState = SOURCE_SET;
		if (error != CL_SUCCESS) oclError("clCreateProgramWithSource", error);
	}

	void ANVIL_CALL Program::setBinary(const unsigned char* aBinary, size_t aLength) {
		setBinaries(&aBinary, &aLength);
	}

	void ANVIL_CALL Program::setBinaries(const unsigned char** aBinaries, const size_t* aLengths) {
		if (mState != INITIALISED) {
			ANVIL_RUNTIME_ASSERT(false, "Program binary has already been set");
			return;
		}

		const std::vector<Device> devices = mContext.devices();
		const cl_uint deviceCount = devices.size();
		const cl_device_id* const devicePtr = deviceCount == 0 ? NULL : reinterpret_cast<const cl_device_id*>(&devices[0]);

		cl_int error = CL_SUCCESS;
		mProgram = clCreateProgramWithBinary(mContext.mContext, deviceCount, devicePtr, aLengths, aBinaries, NULL, &error);
		if (error != CL_SUCCESS) {
			oclError("clCreateProgramWithBinary", error);
			return;
		}
		mState = SOURCE_SET;
	}

	void ANVIL_CALL Program::build(const char* aOptions) {
		if (mState != SOURCE_SET) {
			ANVIL_RUNTIME_ASSERT(false, "Program binary has already been set");
			return;
		}

		const std::vector<Device> devices = mContext.devices();
		const cl_uint deviceCount = devices.size();
		const cl_device_id* const devicePtr = deviceCount == 0 ? NULL : reinterpret_cast<const cl_device_id*>(&devices[0]);

		cl_int error = clBuildProgram(mProgram, deviceCount, devicePtr, aOptions, [](cl_program, void*){}, NULL);
		if (error != CL_SUCCESS) {
			oclError("clBuildProgram", error);
			return;
		}
		mState = BUILT;
	}

}}