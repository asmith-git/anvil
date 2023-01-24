//Copyright 2023 Adam G. Smith
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

#ifndef ANVIL_LUTILS_BYTEPIPE_TCP_HPP
#define ANVIL_LUTILS_BYTEPIPE_TCP_HPP

#include <iostream>
#include "anvil/core/OperatingSystem.hpp"
#include "anvil/byte-pipe/BytePipeReader.hpp"
#include "anvil/byte-pipe/BytePipeWriter.hpp"

#if ANVIL_OS == ANVIL_WINDOWS
	#define NO_MINMAX
	#define WIN32_MEAN_AND_LEAN
	#include <windows.h>
#endif

namespace anvil { namespace BytePipe {

	union IPAddress {
		uint32_t u32;
		uint32_t u8[4u];
	};

	typedef uint16_t TCPPort;

	class TCPClientInputPipe final : public InputPipe {
	private:

	public:
		TCPClientInputPipe(IPAddress server_ip, TCPPort server_port);
		virtual ~TCPClientInputPipe();
		uint32_t ReadBytes(void* dst, const uint32_t bytes) final;
		void ReadBytesFast(void* dst, const uint32_t bytes) final;
	};

	class TCPServerInputPipe final : public InputPipe {
	private:

	public:
		TCPServerInputPipe(std::istream& stream);
		virtual ~TCPServerInputPipe();
		uint32_t ReadBytes(void* dst, const uint32_t bytes) final;
		void ReadBytesFast(void* dst, const uint32_t bytes) final;
	};

	class TcpClientOutputPipe final : public OutputPipe {
	private:
#if ANVIL_OS == ANVIL_WINDOWS
		SOCKET _socket;
#endif
	public:
		TcpClientOutputPipe(IPAddress server_ip, TCPPort server_port);
		virtual ~TcpClientOutputPipe();
		uint32_t WriteBytes(const void* src, const uint32_t bytes) final;
		void WriteBytesFast(const void* src, const uint32_t bytes) final;
		void Flush() final;
	};

	class TcpServerOutputPipe final : public OutputPipe {
	private:
	public:
		TcpServerOutputPipe();
		virtual ~TcpServerOutputPipe();
		uint32_t WriteBytes(const void* src, const uint32_t bytes) final;
		void WriteBytesFast(const void* src, const uint32_t bytes) final;
		void Flush() final;
	};

}}

#endif
