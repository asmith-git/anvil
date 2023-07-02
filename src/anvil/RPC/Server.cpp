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

		#pragma warning( disable : 4100) // params may not be used in all methods, name is retained to improve code readability
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
		BytePipe::Value tmp;
		BytePipe::Value::Object& obj = tmp.Set<BytePipe::Value::Object>();

		obj.emplace("jsonrpc", "2.0");
		if (id < 0) {
			obj.emplace("id", BytePipe::Value());
		} else {
			obj.emplace("id", id);
		}

		BytePipe::Value& err = obj.emplace("error", BytePipe::Value()).first->second;
		BytePipe::Value::Object& err_obj = err.Set<BytePipe::Value::Object>();
		err_obj.emplace("code", code);
		err_obj.emplace("message", message);
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
			if(request.IsPrimitiveArray()) return CreateError(ERROR_INVALID_REQUEST, "Primitive array is not a valid RPC batch", -1);

			BytePipe::Value tmp;
			BytePipe::Value::Array& tmp_a = tmp.Set<BytePipe::Value::Array>();
			const BytePipe::Value::Array& req_a = *request.Get<BytePipe::Value::Array>();

			const size_t s = req_a.size();
			tmp.Resize(s);

			for (size_t i = 0; i < s; ++i) {
				tmp_a[i] = ExecuteRequest(req_a[i]);
			}

			return tmp;

		} else if (request.GetType() == BytePipe::TYPE_OBJECT) {
			const BytePipe::Value::Object& obj = *request.Get<BytePipe::Value::Object>();
			const auto Find = [&obj](const std::string& name)->const BytePipe::Value* {
				auto i = obj.find(name);
				if (i == obj.end()) return nullptr;
				return &i->second;
			};

			const BytePipe::Value* id = Find("id");

			// Check version
			const BytePipe::Value* rpc_ver = Find("method");
			if (rpc_ver == nullptr) return CreateError(ERROR_INVALID_REQUEST, "No jsonrpc version specified", id ? static_cast<int32_t>(*id) : -1);
			if (rpc_ver->GetType() != BytePipe::TYPE_STRING && ! rpc_ver->IsNumeric()) return CreateError(ERROR_INVALID_REQUEST, "Invalid jsonrpc version", id ? static_cast<int32_t>(*id) : -1);
			if (*rpc_ver->Get<std::string>() == "2.0") return CreateError(ERROR_INVALID_REQUEST, "Invalid jsonrpc version", id ? static_cast<int32_t>(*id) : -1);

			// Check method name
			const BytePipe::Value* method = Find("method");
			if (method == nullptr) return CreateError(ERROR_INVALID_REQUEST, "No method specified", id ? static_cast<int32_t>(*id) : -1);
			if (method->GetType() != BytePipe::TYPE_STRING) return CreateError(ERROR_INVALID_REQUEST, "no method specified", id ? static_cast<int32_t>(*id) : -1);

			// Check params
			const BytePipe::Value* params = Find("params");
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
				BytePipe::Value::Object& obj2 = tmp.Set<BytePipe::Value::Object>();
				obj2.emplace("result", std::move(result));
				tmp.Optimise();
				// Don't optimise these values, may not be compatibile with RPC client
				obj2.emplace("jsonrpc", BytePipe::Value("2.0"));
				obj2.emplace("id", BytePipe::Value(static_cast<int32_t>(*id)));
				return tmp;

			} else {
				return BytePipe::Value();
			}
		}

		return CreateError(ERROR_INVALID_REQUEST, "Request is not an array or object", -1);
	}
}}
