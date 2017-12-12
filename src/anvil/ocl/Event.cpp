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

#include "anvil/ocl/Event.hpp"

namespace anvil { namespace ocl {

	// Event

	ANVIL_CALL Event::Event() :
		Object(EVENT) 
	{}

	ANVIL_CALL Event::Event(Event&& aOther) throw() :
		Object(EVENT)
	{
		swap(aOther);
	}

	ANVIL_CALL Event::~Event() throw() {
		destroy();
	}

	Event& ANVIL_CALL Event::operator=(Event&& aOther) throw() {
		swap(aOther);
		return *this;
	}

	void ANVIL_CALL Event::swap(Event& aOther) throw() {
		std::swap(mHandle, aOther.mHandle);
	}

	bool ANVIL_CALL Event::destroy() throw() {
		if (mHandle.event) {
			cl_int error = clReleaseEvent(mHandle.event);
			if (error != CL_SUCCESS) return oclError("clReleaseEvent", error);
			mHandle.event = NULL;
			return true;
		}
		return false;
	}

	bool ANVIL_CALL Event::create(Handle aHandle) throw() {
		if (aHandle.type != EVENT) return false;
		if (mHandle.event != NULL) if (!destroy()) return false;
		if (aHandle.event) {
			mHandle = aHandle;
			cl_int error = clRetainEvent(mHandle.event);
			if (error != CL_SUCCESS) return oclError("clRetainEvent", error);
		}
		return true;
	}

	bool ANVIL_CALL Event::wait() throw() {
		if (!mHandle.event) return oclError("clWaitForEvents ", CL_INVALID_VALUE);
		cl_int error = clWaitForEvents(1, &mHandle.event);
		if (error != CL_SUCCESS) return oclError("clWaitForEvents ", error);
		return true;
	}

	bool ANVIL_CALL Event::wait(const std::vector<Event>& aEvents) throw() {
		const size_t count = aEvents.size();
		if (count == 0) return oclError("clWaitForEvents ", CL_INVALID_VALUE);
		cl_int error = clWaitForEvents(count, &aEvents[0].mHandle.event);
		if (error != CL_SUCCESS) return oclError("clWaitForEvents ", error);
		return true;
	}

	Event::CommandType ANVIL_CALL Event::type() const throw() {
		cl_command_type type;
		cl_int error = clGetEventInfo(mHandle.event, CL_EVENT_COMMAND_TYPE, sizeof(cl_command_type), &type, NULL);
		if (error != CL_SUCCESS) return static_cast<Event::CommandType>(oclError("clGetEventInfo ", error, "CL_EVENT_COMMAND_TYPE"));
		return static_cast<Event::CommandType>(type);
	}

	Event::Status ANVIL_CALL Event::status() const throw() {
		cl_int type;
		cl_int error = clGetEventInfo(mHandle.event, CL_EVENT_COMMAND_EXECUTION_STATUS, sizeof(cl_int), &type, NULL);
		if (error != CL_SUCCESS) return static_cast<Event::Status>(oclError("clGetEventInfo ", error, "CL_EVENT_COMMAND_EXECUTION_STATUS"));
		return static_cast<Event::Status>(type);
	}

	bool ANVIL_CALL Event::setListener(EventListener& aListener) throw() {
		cl_int error = clSetEventCallback(
			mHandle.event,
			CL_COMPLETE,
			[](cl_event aEvent, cl_int, void* aListener) { 
				static_cast<EventListener*>(aListener)->onComplete();
			},
			&aListener);
		if (error != CL_SUCCESS) return static_cast<Event::Status>(oclError("clSetEventCallback ", error));
		return true;
	}


	ProfileInfo ANVIL_CALL Event::profileInfo() const throw() {
		ProfileInfo info = {0, 0, 0, 0};
		cl_int error;
		error = clGetEventProfilingInfo(mHandle.event, CL_PROFILING_COMMAND_QUEUED, sizeof(cl_ulong), &info.queued, NULL);
		if (error != CL_SUCCESS) oclError("clGetEventProfilingInfo ", error, "CL_PROFILING_COMMAND_QUEUED");
		error = clGetEventProfilingInfo(mHandle.event, CL_PROFILING_COMMAND_SUBMIT, sizeof(cl_ulong), &info.submit, NULL);
		if (error != CL_SUCCESS) oclError("clGetEventProfilingInfo ", error, "CL_PROFILING_COMMAND_SUBMIT");
		error = clGetEventProfilingInfo(mHandle.event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &info.start, NULL);
		if (error != CL_SUCCESS) oclError("clGetEventProfilingInfo ", error, "CL_PROFILING_COMMAND_START");
		error = clGetEventProfilingInfo(mHandle.event, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &info.end, NULL);
		if (error != CL_SUCCESS) oclError("clGetEventProfilingInfo ", error, "CL_PROFILING_COMMAND_END");
		return info;
	}

}}