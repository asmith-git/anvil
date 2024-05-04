//Copyright 2024 Adam G. Smith
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

#ifndef ANVIL_LUTILS_BYTEPIPE_BUILDER_HPP
#define ANVIL_LUTILS_BYTEPIPE_BUILDER_HPP

#include "anvil/byte-pipe/BytePipeRLE.hpp"
#include "anvil/byte-pipe/BytePipeHamming.hpp"
#include "anvil/byte-pipe/BytePipeSTL.hpp"
#include "anvil/byte-pipe/BytePipeTCP.hpp"
#include "anvil/byte-pipe/BytePipeUDP.hpp"

namespace anvil { namespace BytePipe {

	class ANVIL_DLL_EXPORT InputPipeBuilder
	{
	private:
		std::vector<std::shared_ptr<InputPipe>> _pipes;

		inline InputPipe& GetInputPipe()
		{
			if (_pipes.empty()) throw std::runtime_error("anvil::BytePipe::GetInputPipe : No source pipe specified");
			return *_pipes.back();
		}

	private:
		InputPipeBuilder();
		~InputPipeBuilder();

		std::shared_ptr<InputPipe> GetPipe();

		inline InputPipeBuilder& SetSourcePipe(const std::shared_ptr<InputPipe>& pipe)
		{
			if (!_pipes.empty()) throw std::runtime_error("anvil::BytePipe::InputPipeBuilder : Source pipe has already been set");
			_pipes.push_back(pipe);
			return *this;
		}

		inline InputPipeBuilder& IStreamPipe(std::istream& stream)
		{
			return SetSourcePipe(std::shared_ptr<InputPipe>(new BytePipe::IStreamPipe(stream)));
		}

		inline InputPipeBuilder& TCPServerPipe(TCPPort listen_port)
		{
			return SetSourcePipe(std::shared_ptr<InputPipe>(new BytePipe::TCPServerPipe(listen_port)));
		}

		inline InputPipeBuilder& TCPClientPipe(IPAddress server_ip, TCPPort server_port)
		{
			return SetSourcePipe(std::shared_ptr<InputPipe>(new BytePipe::TCPClientPipe(server_ip, server_port)));
		}

		inline InputPipeBuilder& UDPInputPipe(UDPPort listen_port)
		{
			return SetSourcePipe(std::shared_ptr<InputPipe>(new BytePipe::UDPInputPipe(listen_port)));
		}

		template<class LengthWord = uint16_t, class DataWord = uint8_t>
		inline InputPipeBuilder& RLEDecoderPipe(int timeout_ms = -1)
		{
			_pipes.push_back(std::shared_ptr<InputPipe>(new BytePipe::RLEDecoderPipe<LengthWord, DataWord>(GetInputPipe(), timeout_ms)));
			return *this;
		}

		inline InputPipeBuilder& RawHamming74InputPipe(int timeout_ms = -1)
		{
			_pipes.push_back(std::shared_ptr<InputPipe>(new BytePipe::RawHamming74InputPipe(GetInputPipe(), timeout_ms)));
			return *this;
		}

		inline InputPipeBuilder& Hamming74InputPipe(int timeout_ms = -1)
		{
			_pipes.push_back(std::shared_ptr<InputPipe>(new BytePipe::Hamming74InputPipe(GetInputPipe(), timeout_ms)));
			return *this;
		}

		inline InputPipeBuilder& RawHamming1511InputPipe(int timeout_ms = -1)
		{
			_pipes.push_back(std::shared_ptr<InputPipe>(new BytePipe::RawHamming1511InputPipe(GetInputPipe(), timeout_ms)));
			return *this;
		}

		inline InputPipeBuilder& Hamming1511InputPipe(int timeout_ms = -1)
		{
			_pipes.push_back(std::shared_ptr<InputPipe>(new BytePipe::Hamming1511InputPipe(GetInputPipe(), timeout_ms)));
			return *this;
		}

		inline InputPipeBuilder& PacketInputPipe(int timeout_ms = -1)
		{
			_pipes.push_back(std::shared_ptr<InputPipe>(new BytePipe::PacketInputPipe(GetInputPipe(), timeout_ms)));
			return *this;
		}
	};


	class ANVIL_DLL_EXPORT OutputPipeBuilder
	{
	private:
		std::vector<std::shared_ptr<OutputPipe>> _pipes;

		inline OutputPipe& GetOutputPipe()
		{
			if (_pipes.empty()) throw std::runtime_error("anvil::BytePipe::GetOutputPipe : No Destination pipe specified");
			return *_pipes.back();
		}

	private:
		OutputPipeBuilder();
		~OutputPipeBuilder();

		std::shared_ptr<OutputPipe> GetPipe();

		inline OutputPipeBuilder& SetDestinationPipe(const std::shared_ptr<OutputPipe>& pipe)
		{
			if (!_pipes.empty()) throw std::runtime_error("anvil::BytePipe::OutputPipeBuilder : Destination pipe has already been set");
			_pipes.push_back(pipe);
			return *this;
		}

		inline OutputPipeBuilder& IStreamPipe(std::ostream& stream)
		{
			return SetDestinationPipe(std::shared_ptr<OutputPipe>(new BytePipe::OStreamPipe(stream)));
		}

		inline OutputPipeBuilder& TCPServerPipe(TCPPort listen_port)
		{
			return SetDestinationPipe(std::shared_ptr<OutputPipe>(new BytePipe::TCPServerPipe(listen_port)));
		}

		inline OutputPipeBuilder& TCPClientPipe(IPAddress server_ip, TCPPort server_port)
		{
			return SetDestinationPipe(std::shared_ptr<OutputPipe>(new BytePipe::TCPClientPipe(server_ip, server_port)));
		}

		inline OutputPipeBuilder& UDPOutputPipe(IPAddress server_ip, UDPPort server_port)
		{
			return SetDestinationPipe(std::shared_ptr<OutputPipe>(new BytePipe::UDPOutputPipe(server_ip, server_port)));
		}

		template<class LengthWord = uint16_t, class DataWord = uint8_t>
		inline OutputPipeBuilder& RLEDecoderPipe()
		{
			_pipes.push_back(std::shared_ptr<OutputPipe>(new BytePipe::RLEEncoderPipe<LengthWord, DataWord>(GetOutputPipe())));
			return *this;
		}

		inline OutputPipeBuilder& RawHamming74OutputPipe(int timeout_ms = -1)
		{
			_pipes.push_back(std::shared_ptr<OutputPipe>(new BytePipe::RawHamming74OutputPipe(GetOutputPipe(), timeout_ms)));
			return *this;
		}

		inline OutputPipeBuilder& Hamming74OutputPipe(int timeout_ms = -1)
		{
			_pipes.push_back(std::shared_ptr<OutputPipe>(new BytePipe::Hamming74OutputPipe(GetOutputPipe(), timeout_ms)));
			return *this;
		}

		inline OutputPipeBuilder& RawHamming1511OutputPipe(int timeout_ms = -1)
		{
			_pipes.push_back(std::shared_ptr<OutputPipe>(new BytePipe::RawHamming1511OutputPipe(GetOutputPipe(), timeout_ms)));
			return *this;
		}

		inline OutputPipeBuilder& Hamming1511OutputPipe(int timeout_ms = -1)
		{
			_pipes.push_back(std::shared_ptr<OutputPipe>(new BytePipe::Hamming1511OutputPipe(GetOutputPipe(), timeout_ms)));
			return *this;
		}

		inline OutputPipeBuilder& PacketOutputPipe(const size_t packet_size, bool fixed_size_packets = true)
		{
			_pipes.push_back(std::shared_ptr<OutputPipe>(new BytePipe::PacketOutputPipe(GetOutputPipe(), packet_size, fixed_size_packets)));
			return *this;
		}
	};


}}

#endif
