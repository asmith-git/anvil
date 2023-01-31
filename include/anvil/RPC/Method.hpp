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

#ifndef ANVIL_RPC_METHOD_HPP
#define ANVIL_RPC_METHOD_HPP

#include <functional>
#include "anvil/byte-pipe/BytePipeObjects.hpp"

namespace anvil { namespace RPC {

	class InvalidMethodParamsError final : public std::runtime_error { public: InvalidMethodParamsError(const std::string& msg) : std::runtime_error(msg) {} };

	typedef std::function<BytePipe::Value(const BytePipe::Value& params)> Method;
}}

#endif
