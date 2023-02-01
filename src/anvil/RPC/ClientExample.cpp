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

#include "anvil/RPC/ClientExample.hpp"

namespace anvil { namespace RPC {

	// ClientJsonTCP

	ClientJsonTCP::ClientJsonTCP(BytePipe::IPAddress server_ip, BytePipe::TCPPort server_port) :
		_tcp(server_ip, server_port)
	{}

	ClientJsonTCP::~ClientJsonTCP() {

	}
	
	BytePipe::Value ClientJsonTCP::ReadFromServer() {
#if ANVIL_JSON_SUPPORT
		std::string str;
		char c = '?';
		while (true) {
			_tcp.ReadBytesFast(&c, 1u); //! \todo Optimise
			if (c == '\0') break;
			str += c;
		}
		nlohmann::json json;
		json = json.parse(str);

		BytePipe::ValueParser parser;
		parser.OnPipeOpen();

		BytePipe::ReadJSON(json, parser);

		BytePipe::Value value = parser.GetValue();
		parser.OnPipeClose();

		return value;
#else
		throw std::runtime_error("ClientJsonTCP::ReadDataFromServer : ANVIL_JSON_SUPPORT is false");
#endif
	}

	void ClientJsonTCP::SendToServer(const BytePipe::Value& request) {
		_json_writer.OnPipeOpen();
		_json_writer.OnValue(request);
		const std::string& json = _json_writer.GetJSONString();
		_tcp.WriteBytesFast(json.c_str(), json.size() + 1u);
		_json_writer.OnPipeClose();
		_tcp.Flush();
	}
}}
