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

#include "anvil/RPC/Server.hpp"

namespace anvil { namespace RPC {

	// Server

	Server::Server() {

		AddMethod("Anvil.RPC.GetVersion", [](const BytePipe::Value& params)->BytePipe::Value {
			return 1;
		});

		AddMethod("Anvil.HasExtension", [](const BytePipe::Value& params)->BytePipe::Value {
			if (params.GetType() == BytePipe::TYPE_STRING) {
				const std::string& str = *params.Get<std::string>();
				if (str == "GSL") return static_cast<bool>(ANVIL_GSL_SUPPORT);
				if (str == "OpenCV") return static_cast<bool>(ANVIL_OPENCV_SUPPORT);
				if (str == "XML") return static_cast<bool>(ANVIL_XML_SUPPORT);
				if (str == "JSON") return static_cast<bool>(ANVIL_JSON_SUPPORT);
			}
			
			return false;
		});

		AddMethod("Anvil.OS.GetVersion", [](const BytePipe::Value& params)->BytePipe::Value {
			return ANVIL_OS;
		});

		AddMethod("Anvil.CPU.GetArch", [](const BytePipe::Value& params)->BytePipe::Value {
			return ANVIL_CPU_ARCHITECTURE;
		});

		AddMethod("Anvil.CPU.GetGetBits", [](const BytePipe::Value& params)->BytePipe::Value {
			return ANVIL_CPU_ARCHITECTURE_BITS;
		});

		AddMethod("Anvil.CPU.GetInstructionSets", [](const BytePipe::Value& params)->BytePipe::Value {
			return SupportedInstructionSets;
		});

#if ANVIL_OPENCV_SUPPORT
		AddMethod("Anvil.OpenCV.GetVersion", [](const BytePipe::Value& params)->BytePipe::Value {
			return CV_VERSION;
		});
#endif

	}

	Server::~Server() {

	}

	void Server::AddMethod(const std::string& name, Method method) {
		std::lock_guard<std::mutex> lock(_mutex);
		_methods.emplace(name, method);
	}

	void Server::RemoveMethod(const std::string& name) {
		std::lock_guard<std::mutex> lock(_mutex);
		auto i = _methods.find(name);
		if (i != _methods.end()) _methods.erase(i);
	}

	BytePipe::Value Server::CreateError(ErrorCode code, const std::string& message, int32_t id) {
		BytePipe::Value tmp(BytePipe::TYPE_OBJECT);
		tmp.AddValue("jsonrpc", BytePipe::Value("2.0"));
		if (id < 0) {
			tmp.AddValue("id", BytePipe::Value());
		} else {
			tmp.AddValue("id", BytePipe::Value(id));
		}

		BytePipe::Value& error = tmp.AddValue("error", BytePipe::Value(BytePipe::TYPE_OBJECT));
		error.AddValue("code", BytePipe::Value(code));
		error.AddValue("message", BytePipe::Value(message));

		return tmp;
	}

	BytePipe::Value Server::CallMethod(const std::string& name, const BytePipe::Value& params) const {
		const Method* method = nullptr;
		{
			std::lock_guard<std::mutex> lock(_mutex);
			auto i = _methods.find(name);
			if (i == _methods.end()) throw MethodNotFoundError(name);
			method = &i->second;
		}

		return (*method)(params);
	}

	BytePipe::Value Server::ExecuteRequest(const BytePipe::Value& request) const {
		if (request.GetType() == BytePipe::TYPE_ARRAY) {
			// Batch call
			BytePipe::Value tmp(BytePipe::TYPE_ARRAY);
			const size_t s = request.GetSize();
			tmp.Resize(s);
			for (size_t i = 0; i < s; ++i) {
				tmp[i] = ExecuteRequest(request[i]);
			}
			return tmp;

		} else if (request.GetType() == BytePipe::TYPE_OBJECT) {
			BytePipe::Value* id = const_cast<BytePipe::Value&>(request).GetValue2("id");

			// Check version
			BytePipe::Value* rpc_ver = const_cast<BytePipe::Value&>(request).GetValue2("method");
			if (rpc_ver == nullptr) return CreateError(ERROR_INVALID_REQUEST, "No jsonrpc version specified", id ? static_cast<int32_t>(*id) : -1);
			if (rpc_ver->GetType() != BytePipe::TYPE_STRING && ! rpc_ver->IsNumeric()) return CreateError(ERROR_INVALID_REQUEST, "Invalid jsonrpc version", id ? static_cast<int32_t>(*id) : -1);
			if (*rpc_ver->Get<std::string>() == "2.0") return CreateError(ERROR_INVALID_REQUEST, "Invalid jsonrpc version", id ? static_cast<int32_t>(*id) : -1);

			// Check method name
			BytePipe::Value* method = const_cast<BytePipe::Value&>(request).GetValue2("method");
			if (method == nullptr) return CreateError(ERROR_INVALID_REQUEST, "No method specified", id ? static_cast<int32_t>(*id) : -1);
			if (method->GetType() != BytePipe::TYPE_STRING) return CreateError(ERROR_INVALID_REQUEST, "no method specified", id ? static_cast<int32_t>(*id) : -1);

			// Check params
			BytePipe::Value* params = const_cast<BytePipe::Value&>(request).GetValue2("params");
			if (method == nullptr) return CreateError(ERROR_INVALID_REQUEST, "No params specified", id ? static_cast<int32_t>(*id) : -1);

			BytePipe::Value result;
			try {
				result = CallMethod(*method->Get<std::string>(), *params);

			} catch (InvalidMethodParamsError& e) {
				return CreateError(ERROR_INVALID_PARAMS, e.what(), id ? static_cast<int32_t>(*id) : -1);

			} catch (MethodNotFoundError& e) {
				return CreateError(ERROR_METHOD_NOT_FOUND, e.what(), id ? static_cast<int32_t>(*id) : -1);

			} catch (std::exception& e) {
				return CreateError(ERROR_INTERNAL, e.what(), id ? static_cast<int32_t>(*id) : -1);

			} catch (...) {
				return CreateError(ERROR_INTERNAL, "Unknown error", id ? static_cast<int32_t>(*id) : -1);

			}

			if (id) {
				BytePipe::Value tmp;
				BytePipe::Value::Object& obj = tmp.Set<BytePipe::Value::Object>();
				obj.emplace("result", std::move(result));
				tmp.Optimise();
				// Don't optimise these values, may not be compatibile with RPC client
				obj.emplace("jsonrpc", BytePipe::Value("2.0"));
				obj.emplace("id", BytePipe::Value(static_cast<int32_t>(*id)));
				return tmp;

			} else {
				return BytePipe::Value();
			}
		}

		return CreateError(ERROR_INVALID_REQUEST, "Request is not an array or object", -1);
	}
}}