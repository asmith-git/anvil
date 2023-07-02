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

#ifndef ANVIL_LUTILS_BYTEPIPE_UDP_HPP
#define ANVIL_LUTILS_BYTEPIPE_UDP_HPP

#include "anvil/byte-pipe/BytePipeTCP.hpp"

namespace anvil { namespace BytePipe {

	typedef TCPPort UDPPort;

	class ANVIL_DLL_EXPORT UDPInputPipe final : public InputPipe {
	private:
#if ANVIL_OS == ANVIL_WINDOWS
		SOCKET _socket;
#endif
	public:
		UDPInputPipe(UDPPort listen_port);
		virtual ~UDPInputPipe();
		size_t ReadBytes(void* dst, const size_t bytes) final;
	};

	class ANVIL_DLL_EXPORT UDPOutputPipe final : public OutputPipe {
	private:
#if ANVIL_OS == ANVIL_WINDOWS
		SOCKET _socket;
		SOCKADDR_IN _address;
#endif
	public:
		UDPOutputPipe(IPAddress server_ip, UDPPort server_port);
		virtual ~UDPOutputPipe();
		size_t WriteBytes(const void* src, const size_t bytes) final;
		void Flush() final;
	};

}}

#endif
