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
		const auto Find = [](const BytePipe::Value& v, const std::string& name)->const BytePipe::Value* {
			const BytePipe::Value::Object* obj = v.Get<BytePipe::Value::Object>();
			if (obj) {
				auto i = obj->find(name);
				if (i != obj->end())return &i->second;
			}
			
			return nullptr;
		};

		const BytePipe::Value* error = Find(response,"error");
		if (error) {
			std::string msg;

			const BytePipe::Value* message = Find(error,"message");
			msg = "null";
			if (message) {
				const std::string* str = message->Get<std::string>();
				if (str) msg = *str;
			}

			const BytePipe::Value* code = Find(error, "code");
			if (code && code->IsNumeric()) {
				msg = "JSON RPC error code " + std::to_string(code->GetS32()) + " : '" + msg + "'";
			}

			throw std::runtime_error(msg);
		}

		const BytePipe::Value* result = Find(response,"result");
		if (result) {
			return std::move(*result);
		}

		throw std::runtime_error("No result from server");
	}

	void Client::SendNotifcation(const std::string& method, const BytePipe::Value& params) {
		BytePipe::Value request;
		BytePipe::Value::Object& obj = request.Set<BytePipe::Value::Object>();
		obj.emplace("method", method);
		obj.emplace("params", params);
		request.Optimise();
		// Don't optimise these values, may not be compatible with RPC server
		obj.emplace("jsonrpc", "2.0");
		SendToServer(request);
	}
}}
