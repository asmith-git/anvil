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

#ifndef ANVIL_RPC_CLIENT_HPP
#define ANVIL_RPC_CLIENT_HPP

#include <condition_variable>
#include "anvil/RPC/Server.hpp"

namespace anvil { namespace RPC {

	class Client {
	private:
		std::condition_variable _response_given;
		int32_t _next_id;
	protected:
		virtual void SendToServer(const BytePipe::Value& request) = 0;
		virtual BytePipe::Value ReadFromServer() = 0;
	public:
		Client();
		virtual ~Client();

		BytePipe::Value SendRequest(const std::string& method, const BytePipe::Value& params);
		void SendNotifcation(const std::string& method, const BytePipe::Value& params);

		// Built-in requests

		inline bool HasExtension(const std::string& ext) { return SendRequest("Anvil.HasExtension", ext).GetBool(); }
		inline bool HasGSL() { return  HasExtension("GSL"); }
		inline bool HasXML() { return HasExtension("XML"); }
		inline bool HasJSON() { return HasExtension("JSON"); }
		inline bool HasOpenCV() { return HasExtension("OpenCV"); }
		inline std::string GetOpenCVVersion() { return *SendRequest("Anvil.OpenCV.GetVersion", BytePipe::Value()).Get<std::string>(); }
		inline uint32_t GetVersion() { return SendRequest("Anvil.RPC.GetVersion", BytePipe::Value()).GetU32(); }
		inline int32_t GetCPUArch() { return SendRequest("Anvil.CPU.GetArch", BytePipe::Value()).GetS32(); }
		inline size_t GetCPUBits() { return SendRequest("Anvil.CPU.GetBits", BytePipe::Value()).GetU32(); }
		inline InstructionSets GetInstructionSets() { return static_cast<InstructionSets>(SendRequest("Anvil.CPU.GetInstructionSets", BytePipe::Value()).GetU64()); }
		inline int32_t GetOS() { return SendRequest("Anvil.OS.GetVersion", BytePipe::Value()).GetS32(); }
	};
}}

#endif
