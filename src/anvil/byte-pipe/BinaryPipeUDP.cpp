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

#include "anvil/byte-pipe/BytePipeUDP.hpp"

namespace anvil { namespace BytePipe {
	enum
	{
		MAX_PACKET_SIZE = 9000
	};

#if ANVIL_OS == ANVIL_WINDOWS
	static void InitWinsock() {
		WSADATA wsaData;
		memset(&wsaData, 0, sizeof(WSADATA));
		WSAStartup(MAKEWORD(2, 2), &wsaData);
	}
#endif
	
	// UDPOutputPipe

	UDPOutputPipe::UDPOutputPipe(IPAddress server_ip, UDPPort server_port) {
#if ANVIL_OS == ANVIL_WINDOWS
		InitWinsock();

		_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (_socket == INVALID_SOCKET) throw std::runtime_error("UDPOutputPipe::UDPOutputPipe : Failed to create socket, WSA error code " + std::to_string(WSAGetLastError()));

		memset(&_address, 0, sizeof(_address));
		_address.sin_family = AF_INET;
		_address.sin_port = htons(server_port);
		_address.sin_addr.s_addr = inet_addr((std::to_string(server_ip.u8[0u]) + "." + std::to_string(server_ip.u8[1u]) + "." + std::to_string(server_ip.u8[2u]) + "." + std::to_string(server_ip.u8[3u])).c_str());

		//int32_t code;
		//
		//code = connect(_socket, (SOCKADDR *)&address, sizeof(address));
		//if (code != 0) {
		//	code = WSAGetLastError();
		//	closesocket(_socket);
		//	_socket = INVALID_SOCKET;
		//	throw std::runtime_error("UDPOutputPipe::UDPOutputPipe : Failed to connect to server, WSA error code " + std::to_string(code));
		//}
#endif
	}

	UDPOutputPipe::~UDPOutputPipe() {
#if ANVIL_OS == ANVIL_WINDOWS
		if (_socket != INVALID_SOCKET) {
			closesocket(_socket);
			_socket = INVALID_SOCKET;
		}
#endif
	}

#pragma warning( disable : 4100) // timeout_ms is not used
	std::future_status UDPOutputPipe::WriteBytesVirtual(const void* src, size_t& bytes, int timeout_ms)
	{
#if ANVIL_OS == ANVIL_WINDOWS
		int sent_bytes = sendto(_socket, static_cast<const char*>(src), static_cast<int>(bytes), 0, reinterpret_cast<SOCKADDR*>(&_address), sizeof(_address));
		if (sent_bytes == SOCKET_ERROR) goto TIMEOUT;//throw std::runtime_error("UDPOutputPipe::WriteBytes : Failed to send data, WSA error code " + std::to_string(WSAGetLastError()));
		bytes = static_cast<size_t>(sent_bytes);
		return std::future_status::ready;
	TIMEOUT:
#endif
		bytes = 0u;
		return std::future_status::timeout;
	}

	std::future_status UDPOutputPipe::FlushVirtual(int timeout_ms)
	{
		return std::future_status::ready;
	}

	// UDPInputPipe

	UDPInputPipe::UDPInputPipe(UDPPort listen_port) :
		_buffer(operator new(MAX_PACKET_SIZE))
	{
#if ANVIL_OS == ANVIL_WINDOWS
		InitWinsock();

		_socket = INVALID_SOCKET;

		_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (_socket == INVALID_SOCKET) {
			throw std::runtime_error("UDPInputPipe::UDPInputPipe : Failed to create socket, WSA error code " + std::to_string(WSAGetLastError()));
		}

		sockaddr_in address;
		memset(&address, 0, sizeof(address));
		address.sin_family = AF_INET;
		address.sin_port = htons(listen_port);
		address.sin_addr.s_addr = INADDR_ANY;

		int code = bind(_socket, reinterpret_cast<SOCKADDR*>(&address), sizeof(address));
		if (code == SOCKET_ERROR) {
			closesocket(_socket);
			_socket = INVALID_SOCKET;
			throw std::runtime_error("UDPInputPipe::UDPInputPipe : Failed to bind socket, WSA error code " + std::to_string(WSAGetLastError()));
		}
#endif
	}

	UDPInputPipe::~UDPInputPipe() {
#if ANVIL_OS == ANVIL_WINDOWS
		if (_socket != INVALID_SOCKET) {
			closesocket(_socket);
			_socket = INVALID_SOCKET;
		}
#endif
		operator delete(_buffer);
	}

	void* UDPInputPipe::ReadNextPacket(size_t& bytes)
	{
		if (bytes > MAX_PACKET_SIZE) bytes = MAX_PACKET_SIZE;
#if ANVIL_OS == ANVIL_WINDOWS
		int bytes_read = recv(_socket, static_cast<char*>(_buffer), static_cast<int32_t>(bytes), 0);
		if (bytes_read == SOCKET_ERROR) throw std::runtime_error("UDPInputPipe::ReadBytes : Failed to read data, WSA error code " + std::to_string(WSAGetLastError()));
		bytes = static_cast<size_t>(bytes_read);
		return _buffer;
#else
		bytes = 0u;
		return nullptr;
#endif
	}


}}