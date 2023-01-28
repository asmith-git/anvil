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
	
	// TCPClientOutputPipe

	TCPClientOutputPipe::TCPClientOutputPipe(IPAddress server_ip, TCPPort server_port) {
#if ANVIL_OS == ANVIL_WINDOWS
		InitWinsock();

		_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (_socket == INVALID_SOCKET) throw std::runtime_error("TCPClientOutputPipe::TCPClientOutputPipe : Failed to create socket, WSA error code " + std::to_string(WSAGetLastError()));

		SOCKADDR_IN address;
		memset(&address, 0, sizeof(address));
		address.sin_family = AF_INET;
		address.sin_port = htons(server_port);
		address.sin_addr.s_addr = inet_addr((std::to_string(server_ip.u8[0u]) + "." + std::to_string(server_ip.u8[1u]) + "." + std::to_string(server_ip.u8[2u]) + "." + std::to_string(server_ip.u8[3u])).c_str());

		int32_t code;
		
		code = connect(_socket, (SOCKADDR *)&address, sizeof(address));
		if (code != 0) {
			code = WSAGetLastError();
			closesocket(_socket);
			_socket = INVALID_SOCKET;
			throw std::runtime_error("TCPClientOutputPipe::TCPClientOutputPipe : Failed to connect to server, WSA error code " + std::to_string(code));
		}
#endif
	}

	TCPClientOutputPipe::~TCPClientOutputPipe() {
#if ANVIL_OS == ANVIL_WINDOWS
		if (_socket != INVALID_SOCKET) {
			closesocket(_socket);
			_socket = INVALID_SOCKET;
		}
#endif
	}

	uint32_t TCPClientOutputPipe::WriteBytes(const void* src, const uint32_t bytes) {
#if ANVIL_OS == ANVIL_WINDOWS
		int sent_bytes = send(_socket, static_cast<const char*>(src), static_cast<int>(bytes), 0);
		if (sent_bytes == SOCKET_ERROR) throw std::runtime_error("TCPClientOutputPipe::WriteBytes : Failed to send data, WSA error code " + std::to_string(WSAGetLastError()));
		return static_cast<uint32_t>(sent_bytes);
#else
		return 0;
#endif
	}

	void TCPClientOutputPipe::WriteBytesFast(const void* src, const uint32_t bytes) {
		const uint8_t* src2 = static_cast<const uint8_t*>(src);
		uint32_t remaining_bytes = bytes;

		while (remaining_bytes > 0) {
			const uint32_t tmp = WriteBytes(src2, remaining_bytes);
			remaining_bytes -= tmp;
			src2 += tmp;
		}
	}

	void TCPClientOutputPipe::Flush() {
		
	}

	// TCPServerInputPipe

	TCPServerInputPipe::TCPServerInputPipe(TCPPort listen_port) {
#if ANVIL_OS == ANVIL_WINDOWS
		InitWinsock();

		_socket = INVALID_SOCKET;

		SOCKET listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (listen_socket == INVALID_SOCKET) {
			throw std::runtime_error("TCPServerInputPipe::TCPServerInputPipe : Failed to create socket, WSA error code " + std::to_string(WSAGetLastError()));
		}

		sockaddr_in address;
		memset(&address, 0, sizeof(address));
		address.sin_family = AF_INET;
		address.sin_port = htons(listen_port);
		address.sin_addr.s_addr = INADDR_ANY;

		int code = bind(listen_socket, reinterpret_cast<SOCKADDR*>(&address), sizeof(address));
		if (code == SOCKET_ERROR) {
			closesocket(listen_socket);
			throw std::runtime_error("TCPServerInputPipe::TCPServerInputPipe : Failed to bind socket, WSA error code " + std::to_string(WSAGetLastError()));
		}

		code = listen(listen_socket, SOMAXCONN);
		if (code == SOCKET_ERROR) {
			printf("listen failed with error: %d\n", WSAGetLastError());
			closesocket(listen_socket);
			throw std::runtime_error("TCPServerInputPipe::TCPServerInputPipe : Failed to listen on socket, WSA error code " + std::to_string(WSAGetLastError()));
		}

		_socket = accept(listen_socket, NULL, NULL);
		if (_socket == INVALID_SOCKET) {
			closesocket(listen_socket);
			throw std::runtime_error("TCPServerInputPipe::TCPServerInputPipe : Failed to accept socket, WSA error code " + std::to_string(WSAGetLastError()));
		}

		closesocket(listen_socket);
#endif
	}

	TCPServerInputPipe::~TCPServerInputPipe() {
#if ANVIL_OS == ANVIL_WINDOWS
		if (_socket != INVALID_SOCKET) {
			closesocket(_socket);
			_socket = INVALID_SOCKET;
		}
#endif
	}

	uint32_t TCPServerInputPipe::ReadBytes(void* dst, const uint32_t bytes) {
#if ANVIL_OS == ANVIL_WINDOWS
		int bytes_read = recv(_socket, static_cast<char*>(dst), static_cast<int32_t>(bytes), 0);
		if (bytes_read == SOCKET_ERROR) throw std::runtime_error("TCPServerInputPipe::ReadBytes : Failed to read data, WSA error code " + std::to_string(WSAGetLastError()));
		return static_cast<uint32_t>(bytes_read);
#else
		return 0;
#endif
	}

	void TCPServerInputPipe::ReadBytesFast(void* dst, const uint32_t bytes) {
		uint8_t* dst2 = static_cast<uint8_t*>(dst);
		uint32_t remaining_bytes = bytes;

		while (remaining_bytes > 0) {
			const uint32_t tmp = ReadBytes(dst, remaining_bytes);
			remaining_bytes -= tmp;
			dst2 += tmp;
		}
	}


}}