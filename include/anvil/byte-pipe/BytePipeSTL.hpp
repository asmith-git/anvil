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

#ifndef ANVIL_LUTILS_BYTEPIPE_STL_HPP
#define ANVIL_LUTILS_BYTEPIPE_STL_HPP

#include <iostream>
#include "anvil/byte-pipe/BytePipeReader.hpp"
#include "anvil/byte-pipe/BytePipeWriter.hpp"

namespace anvil { namespace BytePipe {

	class ANVIL_DLL_EXPORT IStreamPipe final : public InputPipe {
	private:
		std::istream& _stream;
		void* _buffer;
		size_t _buffer_size;
	protected:
		virtual void* ReadNextPacket(size_t& bytes) final;
	public:
		IStreamPipe(std::istream& stream);
		virtual ~IStreamPipe();
	};

	class ANVIL_DLL_EXPORT OStreamPipe final : public OutputPipe {
	private:
		std::ostream& _stream;

	protected:
		virtual std::future_status WriteBytesVirtual(const void* src, size_t& bytes, int timeout_ms) final;
		virtual std::future_status FlushVirtual(int timeout_ms) final;

	public:
		OStreamPipe(std::ostream& stream);
		virtual ~OStreamPipe();
	};

}}

#endif
