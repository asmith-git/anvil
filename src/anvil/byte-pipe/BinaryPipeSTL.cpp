//Copyright 2019 Adam G. Smith
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

#include "anvil/byte-pipe/BytePipeSTL.hpp"

namespace anvil { namespace BytePipe {
	// IStreamPipe
	
	IStreamPipe::IStreamPipe(std::istream& stream) :
		_stream(stream)
	{}

	IStreamPipe::~IStreamPipe() {

	}

	size_t IStreamPipe::ReadBytes(void* dst, const size_t bytes) {
		_stream.read(static_cast<char*>(dst), bytes);
		return static_cast<size_t>(_stream.gcount());
	}

	#pragma warning( disable : 4100) // timeout_ms is not used, name is retained to improve code readability
	void IStreamPipe::ReadBytesFast(void* dst, size_t bytes, int timeout_ms) {
		_stream.read(static_cast<char*>(dst), bytes);
	}


	// OStreamPipe

	OStreamPipe::OStreamPipe(std::ostream& stream) :
		_stream(stream)
	{}

	OStreamPipe::~OStreamPipe() {
		_stream.flush();
	}

	size_t OStreamPipe::WriteBytes(const void* src, const size_t bytes) {
		const auto pos = _stream.tellp();
		_stream.write(static_cast<const char*>(src), bytes);
		return static_cast<size_t>(_stream.tellp() - pos);
	}

	#pragma warning( disable : 4100) // timeout_ms is not used, name is retained to improve code readability
	void OStreamPipe::WriteBytesFast(const void* src, size_t bytes, int timeout_ms) {
		_stream.write(static_cast<const char*>(src), bytes);
	}

	void OStreamPipe::Flush() {
		_stream.flush();
	}

}}