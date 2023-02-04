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

#ifndef ANVIL_RPC_SERVER_EXAMPLE_HPP
#define ANVIL_RPC_SERVER_EXAMPLE_HPP

#include <atomic>
#include <thread>
#include "anvil/RPC/Server.hpp"
#include "anvil/byte-pipe/BytePipeWriter.hpp"
#include "anvil/byte-pipe/BytePipeReader.hpp"
#include "anvil/byte-pipe/BytePipeTCP.hpp"
#include "anvil/byte-pipe/BytePipeJSON.hpp"

namespace anvil { namespace RPC {

	class ServerConnection {
	private:
		Server& _server;
		std::thread _thread;
		std::atomic_int32_t _signal;
	protected:
		virtual void ReadDataFromClient(BytePipe::Parser& parser) = 0;
		virtual void SendDataToClient(const BytePipe::Value& response) = 0;
	public:
		ServerConnection(Server& server);
		virtual ~ServerConnection();
	};

	class ServerJsonTCP final : public ServerConnection {
	private:
		std::unique_ptr<BytePipe::TCPServerPipe> _tcp;
		BytePipe::JsonWriter _json_writer;
		BytePipe::TCPPort _port;
	protected:
		void ReadDataFromClient(BytePipe::Parser& parser) final;
		void SendDataToClient(const BytePipe::Value& response) final;
	public:
		ServerJsonTCP(Server& server, BytePipe::TCPPort server_port);
		virtual ~ServerJsonTCP();
	};
}}

#endif
