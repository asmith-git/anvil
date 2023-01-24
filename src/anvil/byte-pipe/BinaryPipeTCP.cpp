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

#include "anvil/byte-pipe/BytePipeTCP.hpp"

namespace anvil { namespace BytePipe {

#if ANVIL_OS == ANVIL_WINDOWS
	static void InitWinsock() {
		WSADATA wsaData;
		memset(&wsaData, 0, sizeof(WSADATA));
		WSAStartup(MAKEWORD(2, 2), &wsaData);
	}
#endif
	
	TcpClientOutputPipe::TcpClientOutputPipe(IPAddress server_ip, TCPPort server_port) {
#if ANVIL_OS == ANVIL_WINDOWS
		InitWinsock();

		_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (_socket == INVALID_SOCKET) throw std::runtime_error("TcpClientOutputPipe::TcpClientOutputPipe : Failed to create socket, WSA error code " + std::to_string(WSAGetLastError()));

		SOCKADDR_IN server;
		memset(&server, 0, sizeof(SOCKADDR_IN));
		server.sin_family = AF_INET;
		server.sin_port = htons(server_port);
		server.sin_addr.s_addr = inet_addr((std::to_string(server_ip.u8[0u]) + "." + std::to_string(server_ip.u8[1u]) + "." + std::to_string(server_ip.u8[2u]) + "." + std::to_string(server_ip.u8[3u])).c_str());

		int32_t code = connect(_socket, (SOCKADDR *)&server, sizeof(server));
		if (code != 0) {
			closesocket(_socket);
			_socket = INVALID_SOCKET;
			throw std::runtime_error("TcpClientOutputPipe::TcpClientOutputPipe : Failed to connect to server");
		}
#endif
	}

	TcpClientOutputPipe::~TcpClientOutputPipe() {

	}

	uint32_t TcpClientOutputPipe::WriteBytes(const void* src, const uint32_t bytes) {
		int sent_bytes = send(_socket, static_cast<const char*>(src), static_cast<int>(bytes), 0);
		if (sent_bytes == SOCKET_ERROR) throw std::runtime_error("TcpClientOutputPipe::WriteBytes : Failed to send data, WSA error code " + std::to_string(WSAGetLastError()));
		return static_cast<uint32_t>(sent_bytes);
	}

	void TcpClientOutputPipe::WriteBytesFast(const void* src, const uint32_t bytes) {
		const uint8_t* src2 = static_cast<const uint8_t*>(src);
		uint32_t remaining_bytes = bytes;
		while (remaining_bytes > 0) {
			const uint32_t tmp = WriteBytes(src2, remaining_bytes);
			remaining_bytes -= tmp;
			src2 += tmp;
		}
	}

	void TcpClientOutputPipe::Flush() {
		
	}

}}