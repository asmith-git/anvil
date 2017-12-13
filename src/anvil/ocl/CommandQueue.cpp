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

	struct CommandQueueData {
		cl_uint reference_count;
	};

	// CommandQueue

	ANVIL_CALL CommandQueue::CommandQueue() throw() :
		Object(COMMAND_QUEUE) 
	{}

	ANVIL_CALL CommandQueue::CommandQueue(CommandQueue&& aOther) throw() :
		Object(COMMAND_QUEUE) 
	{
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
			aContext.mHandle.context,
			aDevice.mHandle.device,
			aOutOfOrder || aProfiling ? &properties : NULL,
			&error);
		if (error != CL_SUCCESS) return oclError("clCreateCommandQueueWithProperties", error);
#else
		mHandle.queue = clCreateCommandQueue(
			aContext.mHandle.context,
			aDevice.mHandle.device,
			(aOutOfOrder ? CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE : 0) | (aProfiling ? CL_QUEUE_PROFILING_ENABLE : 0),
			&error);
		if (error != CL_SUCCESS) return oclError("clCreateCommandQueue", error);
#endif
		CommandQueueData* const data = new CommandQueueData();
		data->reference_count = 1;
		associateData(mHandle, data);
		return true;
	}

	bool CommandQueue::destroy() throw() {
		if (mHandle.queue) {
			finish();
			cl_int error = clReleaseCommandQueue(mHandle.queue);
			if (error != CL_SUCCESS) return oclError("clReleaseCommandQueue", error);
			CommandQueueData* const data = static_cast<CommandQueueData*>(getAssociatedData(mHandle));
			if (data) {
				if (--data->reference_count == 0) {
					disassociateData(mHandle);
					delete data;
				}
			}
			mHandle.queue = NULL;
			return true;
		}
		return false;
	}

	bool ANVIL_CALL CommandQueue::create(Handle aHandle) throw() {
		if (aHandle.type != COMMAND_QUEUE) return false;
		if (mHandle.queue != NULL) if (!destroy()) return false;
		if (aHandle.queue) {
			mHandle = aHandle;
			cl_int error = clRetainCommandQueue(mHandle.queue);
			if (error != CL_SUCCESS) return oclError("clRetainCommandQueue", error);
		}
		CommandQueueData* const data = static_cast<CommandQueueData*>(getAssociatedData(mHandle));
		if (data) ++data->reference_count;
		return true;
	}

	bool ANVIL_CALL CommandQueue::flush() throw() {
		cl_int error = clFlush(mHandle.queue);
		return error == CL_SUCCESS ? true : oclError("clFlush", error);
	}

	bool ANVIL_CALL CommandQueue::finish() throw() {
		cl_int error = clFinish(mHandle.queue);
		return error == CL_SUCCESS ? true : oclError("clFinish", error);
	}

	Event ANVIL_CALL CommandQueue::barrier() throw() {
#ifdef CL_VERSION_1_2
		Event event;
		cl_event& event_ref = event.mHandle.event;
		cl_int error = clEnqueueBarrierWithWaitList(mHandle.queue, 0, NULL, &event_ref);
		if (error != CL_SUCCESS) {
			oclError("clEnqueueBarrierWithWaitList", error);
			return Event();
		}
		return event;
#else
		cl_int error = clEnqueueBarrier(mHandle.queue);
		if(error != CL_SUCCESS )oclError("clEnqueueBarrier", error);
		return Event();
#endif
	}

	Event ANVIL_CALL CommandQueue::pushMarker() throw() {
		Event event;
		cl_event& event_ref = event.mHandle.event;
#ifdef CL_VERSION_1_2
		cl_int error = clEnqueueMarkerWithWaitList(mHandle.queue, 0, NULL, &event_ref);
		if (error != CL_SUCCESS) {
			oclError("clEnqueueMarkerWithWaitList", error);
			return Event();
		}
#else
		cl_int error = clEnqueueMarker(mHandle.queue, &event_ref);
		if (error != CL_SUCCESS) {
			oclError("clEnqueueMarker", error);
			return Event();
		}
#endif
		return event;
	}

	cl_uint ANVIL_CALL CommandQueue::referenceCount() const throw() {
		CommandQueueData* const data = static_cast<CommandQueueData*>(getAssociatedData(mHandle));
		return data ? data->reference_count : 0;
	}
}}