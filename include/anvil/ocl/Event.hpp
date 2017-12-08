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

#ifndef ANVIL_OCL_EVENT_HPP
#define ANVIL_OCL_EVENT_HPP

#include <memory>
#include "anvil/ocl/Context.hpp"

namespace anvil { namespace ocl {

	class EventListener;
	
	struct ProfileInfo {
		cl_ulong queued;
		cl_ulong submit;
		cl_ulong start;
		cl_ulong end;
	};

	class Event {
	private:
		cl_event mEvent;

		Event(const Event&) = delete;
		Event& operator=(const Event&) = delete;
	public:
		enum CommandType : cl_command_type {
			NDRANGE_KERNEL = CL_COMMAND_NDRANGE_KERNEL,
			TASK = CL_COMMAND_TASK,
			NATIVE_KERNEL = CL_COMMAND_NATIVE_KERNEL,
			READ_BUFFER = CL_COMMAND_READ_BUFFER,
			WRITE_BUFFER = CL_COMMAND_WRITE_BUFFER,
			COPY_BUFFER = CL_COMMAND_COPY_BUFFER,
			READ_IMAGE = CL_COMMAND_READ_IMAGE,
			WRITE_IMAGE = CL_COMMAND_WRITE_IMAGE,
			COPY_IMAGE = CL_COMMAND_COPY_IMAGE,
			COPY_BUFFER_TO_IMAGE = CL_COMMAND_COPY_BUFFER_TO_IMAGE,
			COPY_IMAGE_TO_BUFFER = CL_COMMAND_COPY_IMAGE_TO_BUFFER,
			MAP_BUFFER = CL_COMMAND_MAP_BUFFER,
			MAP_IMAGE = CL_COMMAND_MAP_IMAGE,
			UNMAP_MEM_OBJECT = CL_COMMAND_UNMAP_MEM_OBJECT,
			MARKER = CL_COMMAND_MARKER,
			ACQUIRE_GL_OBJECTS = CL_COMMAND_ACQUIRE_GL_OBJECTS,
			RELEASE_GL_OBJECTS = CL_COMMAND_RELEASE_GL_OBJECTS,
			READ_BUFFER_RECT = CL_COMMAND_READ_BUFFER_RECT,
			WRITE_BUFFER_RECT = CL_COMMAND_WRITE_BUFFER_RECT,
			COPY_BUFFER_RECT = CL_COMMAND_COPY_BUFFER_RECT,
			USER = CL_COMMAND_USER,
		};

		enum Status : cl_int {
			COMPLETE = CL_COMPLETE,
			RUNNING = CL_RUNNING,
			SUBMITTED = CL_SUBMITTED,
			QUEUED = CL_QUEUED
		};

		ANVIL_CALL Event() throw();
		ANVIL_CALL Event(Event&&) throw();
		ANVIL_CALL ~Event() throw();

		Event& ANVIL_CALL operator=(Event&&) throw();
		ANVIL_CALL operator bool() const throw();

		bool ANVIL_CALL destroy() throw();

		bool ANVIL_CALL setListener(EventListener&) throw();
		bool ANVIL_CALL wait() throw();
		CommandType ANVIL_CALL type() const throw();
		Status ANVIL_CALL status() const throw();
		ProfileInfo ANVIL_CALL profileInfo() const throw();

		static bool ANVIL_CALL wait(const std::vector<Event>&) throw();
	};

	class EventListener {
	protected:
		virtual void onComplete() throw() = 0;
	public:
		friend Event;
		virtual ~EventListener() {}
	};
}}

#endif
