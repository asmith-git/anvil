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
#include "anvil/ocl/Buffer.hpp"
#include "anvil/ocl/CommandQueue.hpp"

namespace anvil { namespace ocl {

	// CommandQueue

	ANVIL_CALL CommandQueue::CommandQueue() throw() {

	}

	ANVIL_CALL CommandQueue::CommandQueue(CommandQueue&& aOther) throw() {
		swap(aOther);
	}

	ANVIL_CALL CommandQueue::~CommandQueue() throw() {
		destroy();
	}
	
	CommandQueue& ANVIL_CALL CommandQueue::operator=(CommandQueue&& aOther) throw() {
		swap(aOther);
		return *this;
	}

	void ANVIL_CALL CommandQueue::swap(CommandQueue& aOther) throw() {
		std::swap(mHandle, aOther.mHandle);
	}

	bool CommandQueue::create(Context& aContext, Device& aDevice, bool aOutOfOrder, bool aProfiling) throw() {
		if (mHandle.queue) if (!destroy()) return false;

		cl_int error = CL_SUCCESS;
#ifdef CL_VERSION_2_0
		cl_queue_properties properties = (aOutOfOrder ? CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE : 0) | (aProfiling ? CL_QUEUE_PROFILING_ENABLE : 0);
		mHandle.queue = clCreateCommandQueueWithProperties(
			aDevice.mHandle.context,
			aDevice.mHandle.device,
			aOutOfOrder || aProfiling ? &properties : NULL,
			&error);
		if (error != CL_SUCCESS) return oclError("clCreateCommandQueueWithProperties", error, false);
#else
		mHandle.queue = clCreateCommandQueue(
			aDevice.mHandle.context,
			aDevice.mHandle.device,
			(aOutOfOrder ? CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE : 0) | (aProfiling ? CL_QUEUE_PROFILING_ENABLE : 0),
			&error);
		if (error != CL_SUCCESS) return oclError("clCreateCommandQueue", error, false);
#endif
		return true;
	}

	bool CommandQueue::destroy() throw() {
		if (mHandle.queue) {
			finish();
			cl_int error = clReleaseCommandQueue(mHandle.queue);
			if (error != CL_SUCCESS) return oclError("clReleaseCommandQueue", error, false);
			mHandle.queue = NULL;
			return true;
		}
		return false;
	}

	bool ANVIL_CALL CommandQueue::flush() throw() {
		cl_int error = clFlush(mHandle.queue);
		return error == CL_SUCCESS ? true : oclError("clFlush", error, false);
	}

	bool ANVIL_CALL CommandQueue::finish() throw() {
		cl_int error = clFinish(mHandle.queue);
		return error == CL_SUCCESS ? true : oclError("clFinish", error, false);
	}

#ifndef CL_VERSION_1_2
	bool ANVIL_CALL CommandQueue::barrier() throw() {
		cl_int error = clEnqueueBarrier(mHandle.queue);
		return error == CL_SUCCESS ? true : oclError("clEnqueueBarrier", error, false);
	}

	Event ANVIL_CALL CommandQueue::pushMarker() throw() {
		Event event;
		cl_event& event_ref = event.handle().event;
		cl_int error = clEnqueueMarker(mHandle.queue, &event_ref);
		if (error != CL_SUCCESS) {
			oclError("clEnqueueMarker", error);
			return Event();
		}
		return Event(event);
	}
#endif
}}