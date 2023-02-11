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

#ifndef ANVIL_RPC_SERVER_HPP
#define ANVIL_RPC_SERVER_HPP

#include "anvil/RPC/Method.hpp"
#include <mutex>

namespace anvil { namespace RPC {

	class MethodNotFoundError final : public std::runtime_error { public: MethodNotFoundError(const std::string& method_name) : std::runtime_error(method_name) {} };

	enum ErrorCode : int32_t {
		ERROR_INVALID_JSON = -32700,
		ERROR_INVALID_REQUEST = -32600,
		ERROR_METHOD_NOT_FOUND = -32601,
		ERROR_INVALID_PARAMS = -32602,
		ERROR_INTERNAL = -32603
	};

	class ANVIL_DLL_EXPORT Server {
	private:
		std::map<std::string, Method> _methods;
		mutable std::mutex _mutex;

		static BytePipe::Value CreateError(ErrorCode code, const std::string& message, int32_t id);
	public:
		Server();
		virtual ~Server();

		void AddMethod(const std::string& name, Method method);
		void RemoveMethod(const std::string& name);

		BytePipe::Value CallMethod(const std::string& name, const BytePipe::Value& params) const;
		BytePipe::Value ExecuteRequest(const BytePipe::Value& request) const;
	};
}}

#endif
