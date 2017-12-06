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
		mEvent(NULL)
	{}

	ANVIL_CALL Event::Event(Context& aContext)  throw() :
		mEvent(NULL)
	{
		cl_int error = CL_SUCCESS;
		mEvent = clCreateUserEvent(aContext.mContext, &error);
		if (error != CL_SUCCESS) {
			mEvent = NULL;
			oclError("clCreateUserEvent ", error);
		}
	}

	ANVIL_CALL Event::Event(cl_context aContext)  throw() :
		mEvent(NULL)
	{
		cl_int error = CL_SUCCESS;
		mEvent = clCreateUserEvent(aContext, &error);
		if (error != CL_SUCCESS) {
			mEvent = NULL;
			oclError("clCreateUserEvent ", error);
		}
	}

	ANVIL_CALL Event::Event(Event&& aOther) throw() :
		mEvent(NULL)
	{
		std::swap(mEvent, aOther.mEvent);
	}

	ANVIL_CALL Event::~Event() throw() {
		if (mEvent) {
			cl_int error = clReleaseEvent(mEvent);
			mEvent = NULL;
			if (error != CL_SUCCESS) oclError("clReleaseEvent ", error);
		}
	}

	Event& ANVIL_CALL Event::operator=(Event&& aOther) throw() {
		std::swap(mEvent, aOther.mEvent);
		return *this;
	}

	void ANVIL_CALL Event::wait() throw() {
		if (! mEvent) return;
		cl_int error = clWaitForEvents(1, &mEvent);
		if (error != CL_SUCCESS) oclError("clWaitForEvents ", error);
	}

}}