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

#include "anvil/RPC/ServerExample.hpp"

namespace anvil { namespace RPC {

	// ClientExample

	ServerConnection::ServerConnection(Server& server) :
		_server(server),
		_signal(0)
	{
		_thread = std::thread([this]()->void {
			while (_signal == 0u) {
				try {
					BytePipe::ValueParser parser;
					parser.OnPipeOpen();

					ReadDataFromClient(parser);

					BytePipe::Value response = _server.ExecuteRequest(parser.GetValue());
					parser.OnPipeClose();

					if (response.GetType() != BytePipe::TYPE_NULL) SendDataToClient(response);
				} catch (...) {

				}
			}
		});
	}

	ServerConnection::~ServerConnection() {
		_signal = 1;
		_thread.join();
	}

	// ServerJsonTCP

	ServerJsonTCP::ServerJsonTCP(Server& server, BytePipe::TCPPort server_port) :
		ServerConnection(server),
		_port(server_port)
	{}

	ServerJsonTCP::~ServerJsonTCP() {

	}

	void ServerJsonTCP::ReadDataFromClient(BytePipe::Parser& parser) {
#if ANVIL_JSON_SUPPORT
		if (!_tcp) _tcp.reset(new BytePipe::TCPServerPipe(_port));

		std::string str;
		char c = '?';
		while (true) {
			_tcp->ReadBytesFast(&c, 1u); //! \todo Optimise
			if (c == '\0') break;
			str += c;
		}
		nlohmann::json json;
		json = json.parse(str);
		BytePipe::ReadJSON(json, parser);
#else
		throw std::runtime_error("ClientJsonTCP::ReadDataFromServer : ANVIL_JSON_SUPPORT is false");
#endif
	}

	void ServerJsonTCP::SendDataToClient(const BytePipe::Value& response) {
		_json_writer.OnPipeOpen();
		_json_writer.OnValue(response);
		const std::string& json = _json_writer.GetJSONString();
		_tcp->WriteBytesFast(json.c_str(), json.size() + 1u);
		_json_writer.OnPipeClose();
		_tcp->Flush();
	}
}}
