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

#ifndef CL_VERSION_1_2
	struct CommandQueueData {
		cl_context context;
		cl_device_id device;
	};
#endif

	// CommandQueue

	ANVIL_CALL CommandQueue::CommandQueue() throw() :
		Object(Handle::COMMAND_QUEUE)
	{}

	ANVIL_CALL CommandQueue::CommandQueue(CommandQueue&& aOther) throw() :
		Object(Handle::COMMAND_QUEUE)
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
#ifdef ANVIL_LOG_OCL
		std::cerr << "clCreateCommandQueueWithProperties (" << aContext.handle().context << ", " << aDevice.handle().device << ", " <<
			(void*) (aOutOfOrder || aProfiling ? &properties : NULL) <<
			&error << ")" << std::endl;
#endif
		mHandle.queue = clCreateCommandQueueWithProperties(
			aContext.mHandle.context,
			aDevice.mHandle.device,
			aOutOfOrder || aProfiling ? &properties : NULL,
			&error);
		if (error != CL_SUCCESS) return oclError("clCreateCommandQueueWithProperties", error);
#else
#ifdef ANVIL_LOG_OCL
		std::cerr << "clCreateCommandQueue (" << aContext.handle().context << ", " << aDevice.handle().device << ", " <<
			((aOutOfOrder ? CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE : 0) | (aProfiling ? CL_QUEUE_PROFILING_ENABLE : 0)) << ", " <<
			&error << ")" << std::endl;
#endif
		mHandle.queue = clCreateCommandQueue(
			aContext.handle(),
			aDevice.handle(),
			(aOutOfOrder ? CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE : 0) | (aProfiling ? CL_QUEUE_PROFILING_ENABLE : 0),
			&error);
		if (error != CL_SUCCESS) return oclError("clCreateCommandQueue", error);
#endif
		onCreate();
#ifndef CL_VERSION_1_2
		std::shared_ptr<CommandQueueData>data(new CommandQueueData());
		data->context = aContext.handle();
		data->device = aDevice.handle();
		setExtraData(data);
#endif
		return true;
	}

	bool CommandQueue::destroy() throw() {
		if (mHandle.queue) {
			finish();
#ifdef ANVIL_LOG_OCL
			std::cerr << "clReleaseCommandQueue (" << mHandle.queue << ")" << std::endl;
#endif
			cl_int error = clReleaseCommandQueue(mHandle.queue);
			if (error != CL_SUCCESS) return oclError("clReleaseCommandQueue", error);
			onDestroy();
			mHandle.queue = NULL;
			return true;
		}
		return false;
	}

	bool ANVIL_CALL CommandQueue::create(Handle aHandle) throw() {
		if (aHandle.type != Handle::COMMAND_QUEUE) return false;
		if (mHandle.queue != NULL) if (!destroy()) return false;
		if (aHandle.queue) {
			mHandle = aHandle;
#ifdef ANVIL_LOG_OCL
			std::cerr << "clRetainCommandQueue (" << mHandle.queue << ")" << std::endl;
#endif
			cl_int error = clRetainCommandQueue(mHandle.queue);
			if (error != CL_SUCCESS) return oclError("clRetainCommandQueue", error);
			onCreate();
		}
		return true;
	}

	bool ANVIL_CALL CommandQueue::flush() throw() {
#ifdef ANVIL_LOG_OCL
		std::cerr << "clFlush (" << mHandle.queue << ")" << std::endl;
#endif
		cl_int error = clFlush(mHandle.queue);
		return error == CL_SUCCESS ? true : oclError("clFlush", error);
	}

	bool ANVIL_CALL CommandQueue::finish() throw() {
#ifdef ANVIL_LOG_OCL
		std::cerr << "clFinish (" << mHandle.queue << ")" << std::endl;
#endif
		cl_int error = clFinish(mHandle.queue);
		return error == CL_SUCCESS ? true : oclError("clFinish", error);
	}

	Event ANVIL_CALL CommandQueue::barrier() throw() {
#ifdef CL_VERSION_1_2
		Handle handle(Handle::EVENT);
#ifdef ANVIL_LOG_OCL
		std::cerr << "clEnqueueBarrierWithWaitList (" << mHandle.queue << ", " << 0 << ", " << "NULL" << ", " << &handle.event << ")" << std::endl;
#endif
		cl_int error = clEnqueueBarrierWithWaitList(mHandle.queue, 0, NULL, &handle.event);
		if (error != CL_SUCCESS) {
			oclError("clEnqueueBarrierWithWaitList", error);
			return Event();
		}
		Event event;
		event.create(handle);
		return event;
#else
#ifdef ANVIL_LOG_OCL
		std::cerr << "clEnqueueBarrier (" << mHandle.queue << ")" << std::endl;
#endif
		cl_int error = clEnqueueBarrier(mHandle.queue);
		if(error != CL_SUCCESS )oclError("clEnqueueBarrier", error);
		return Event();
#endif
	}

	Event ANVIL_CALL CommandQueue::pushMarker() throw() {
		Handle handle(Handle::EVENT);
#ifdef CL_VERSION_1_2
#ifdef ANVIL_LOG_OCL
		std::cerr << "clEnqueueMarkerWithWaitList (" << mHandle.queue << ", " << 0 << ", " << "NULL" << ", " << &handle.event << ")" << std::endl;
#endif
		cl_int error = clEnqueueMarkerWithWaitList(mHandle.queue, 0, NULL, &handle.event);
		if (error != CL_SUCCESS) {
			oclError("clEnqueueMarkerWithWaitList", error);
			return Event();
		}
#else
#ifdef ANVIL_LOG_OCL
		std::cerr << "clEnqueueMarker (" << mHandle.queue << ", " << &handle.event << ")" << std::endl;
#endif
		cl_int error = clEnqueueMarker(mHandle.queue, &handle.event);
		if (error != CL_SUCCESS) {
			oclError("clEnqueueMarker", error);
			return Event();
		}
#endif
		Event event;
		event.create(handle);
		return event;
	}

	cl_uint ANVIL_CALL CommandQueue::referenceCount() const throw() {
		if (mHandle.queue == NULL) return 0;
#ifdef CL_VERSION_1_2
		cl_uint count;
#ifdef ANVIL_LOG_OCL
		std::cerr << "clGetCommandQueueInfo (" << mHandle.queue << ", " << "CL_QUEUE_REFERENCE_COUNT" << ", " << sizeof(count) << 
			", " << &count << ", " << "NULL" << ")" << std::endl;
#endif
		cl_uint error = clGetCommandQueueInfo(mHandle.queue, CL_QUEUE_REFERENCE_COUNT, sizeof(count), &count, NULL);
		if (error == CL_SUCCESS) return count;
		oclError("clGetCommandQueueInfo", error, "CL_QUEUE_REFERENCE_COUNT");
		return 0;
#else
		return const_cast<CommandQueue*>(this)->getExtraData().use_count() - 1;
#endif
	}

	Context ANVIL_CALL CommandQueue::context() const throw() {
		Handle h(Handle::CONTEXT);
		Context tmp;
#ifdef CL_VERSION_1_2
#ifdef ANVIL_LOG_OCL
		std::cerr << "clGetCommandQueueInfo (" << mHandle.queue << ", " << "CL_QUEUE_CONTEXT" << ", " << sizeof(cl_context) <<
			", " << &h.context << ", " << "NULL" << ")" << std::endl;
#endif
		cl_uint error = clGetCommandQueueInfo(mHandle.queue, CL_QUEUE_CONTEXT, sizeof(cl_context), &h.context, NULL);
		if (error != CL_SUCCESS) oclError("clGetCommandQueueInfo", error, "CL_QUEUE_CONTEXT");
#else
		std::shared_ptr<CommandQueueData> data = std::static_pointer_cast<CommandQueueData>(const_cast<CommandQueue*>(this)->getExtraData());
		h.context = data ? data->context : NULL;
#endif
		if(h.context) tmp.create(h);
		return std::move(tmp);
	}

	Device ANVIL_CALL CommandQueue::device() const throw() {
		Handle h(Handle::DEVICE);
		Device tmp;
#ifdef CL_VERSION_1_2
#ifdef ANVIL_LOG_OCL
		std::cerr << "clGetCommandQueueInfo (" << mHandle.queue << ", " << "CL_QUEUE_DEVICE" << ", " << sizeof(cl_device_id) <<
			", " << &h.context << ", " << "NULL" << ")" << std::endl;
#endif
		cl_uint error = clGetCommandQueueInfo(mHandle.queue, CL_QUEUE_DEVICE, sizeof(cl_device_id), &h.device, NULL);
		if (error != CL_SUCCESS) oclError("clGetCommandQueueInfo", error, "CL_QUEUE_DEVICE");
#else
		std::shared_ptr<CommandQueueData> data = std::static_pointer_cast<CommandQueueData>(const_cast<CommandQueue*>(this)->getExtraData());
		h.device = data ? data->device : NULL;
#endif
		if (h.device) tmp.create(h);
		return std::move(tmp);
	}

	Handle::Type ANVIL_CALL CommandQueue::type() const throw() {
		return Handle::COMMAND_QUEUE;
	}
}}