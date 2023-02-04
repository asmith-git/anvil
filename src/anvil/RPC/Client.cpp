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

#include "anvil/RPC/Client.hpp"

namespace anvil { namespace RPC {

	// Client

	Client::Client() :
		_next_id(0)
	{}

	Client::~Client() {

	}

	BytePipe::Value Client::SendRequest(const std::string& method, const BytePipe::Value& params) {
		int32_t id = _next_id;
		if (_next_id == INT32_MAX) _next_id = 0;
		else ++_next_id;

		{
			BytePipe::Value request;
			BytePipe::Value::Object& obj = request.Set<BytePipe::Value::Object>();
			obj.emplace("method", BytePipe::Value(method));
			obj.emplace("params", BytePipe::Value(params));
			request.Optimise();
			// Don't optimise these values, may not be compatible with RPC server
			obj.emplace("jsonrpc", BytePipe::Value("2.0"));
			obj.emplace("id", BytePipe::Value(_next_id)); 
			SendToServer(request);
		}

		// Wait for response
		BytePipe::Value response = ReadFromServer();

		BytePipe::Value* error = response.GetValue2("error");
		if (error) {
			std::string msg;

			BytePipe::Value* message = error->GetValue2("message");
			if (message) {
				msg = message->GetString();
			} else {
				msg = "null";
			}

			BytePipe::Value* code = error->GetValue2("code");
			if (code && code->IsNumeric()) {
				msg = "JSON RPC error code " + std::to_string(code->GetS32()) + " : '" + msg + "'";
			}

			throw std::runtime_error(msg);
		}

		BytePipe::Value* result = response.GetValue2("result");
		if (result) {
			return std::move(*result);
		}

		throw std::runtime_error("No result from server");
	}

	void Client::SendNotifcation(const std::string& method, const BytePipe::Value& params) {
		BytePipe::Value request(BytePipe::TYPE_OBJECT);
		request.AddValue("jsonrpc", BytePipe::Value("2.0"));
		request.AddValue("method", BytePipe::Value(method));
		request.AddValue("params", BytePipe::Value(params));

		request.Optimise();
		SendToServer(request);
	}
}}
