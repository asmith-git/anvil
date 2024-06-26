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
		_stream(stream),
		_buffer(nullptr),
		_buffer_size(0u)
	{

	}

	IStreamPipe::~IStreamPipe() 
	{
		if (_buffer) operator delete(_buffer);
	}

	void* IStreamPipe::ReadNextPacket(size_t& bytes)
	{
		if (_buffer_size < bytes)
		{
			if (_buffer) operator delete(_buffer);
			_buffer = operator new(bytes);
			_buffer_size = bytes;

			if (_buffer == nullptr)
			{
				bytes = 0u;
				_buffer_size = 0u;
				return nullptr;
			}
		}

		_stream.read(static_cast<char*>(_buffer), bytes);
		bytes = static_cast<size_t>(_stream.gcount());
		return _buffer;
	}


	// OStreamPipe

	OStreamPipe::OStreamPipe(std::ostream& stream) :
		_stream(stream)
	{

	}

	OStreamPipe::~OStreamPipe() 
	{
		_stream.flush();
	}

	#pragma warning( disable : 4100) // timeout_ms is not used
	std::future_status OStreamPipe::WriteBytesVirtual(const void* src, size_t& bytes, int timeout_ms)
	{
		const auto pos = _stream.tellp();
		_stream.write(static_cast<const char*>(src), bytes);
		bytes = static_cast<size_t>(_stream.tellp() - pos);
		return std::future_status::ready;
	}

	std::future_status OStreamPipe::FlushVirtual(int timeout_ms) 
	{
		_stream.flush();
		return std::future_status::ready;
	}



}}