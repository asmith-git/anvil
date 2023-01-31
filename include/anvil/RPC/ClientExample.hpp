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

#ifndef ANVIL_RPC_CLIENT_EXAMPLE_HPP
#define ANVIL_RPC_CLIENT_EXAMPLE_HPP

#include <atomic>
#include "anvil/RPC/Client.hpp"
#include "anvil/byte-pipe/BytePipeWriter.hpp"
#include "anvil/byte-pipe/BytePipeReader.hpp"
#include "anvil/byte-pipe/BytePipeTCP.hpp"
#include "anvil/byte-pipe/BytePipeJSON.hpp"

namespace anvil { namespace RPC {

	class ClientHelper : public Client {
	private:
		std::thread _read_thread;
		std::atomic_int32_t _signal;
	protected:
		virtual void ReadDataFromServer(BytePipe::Parser& parser) = 0;
	public:
		ClientHelper();
		virtual ~ClientHelper();
	};

	class ClientJsonTCP final : public ClientHelper {
	private:
		BytePipe::TCPClientPipe _tcp;
		BytePipe::JsonWriter _json_writer;
	protected:
		void ReadDataFromServer(BytePipe::Parser& parser) final;
		void SendToServer(const BytePipe::Value& request) final;
	public:
		ClientJsonTCP(BytePipe::IPAddress server_ip, BytePipe::TCPPort server_port);
		virtual ~ClientJsonTCP();
	};
}}

#endif
