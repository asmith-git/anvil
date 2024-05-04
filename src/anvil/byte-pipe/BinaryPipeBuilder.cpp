//Copyright 2019 Adam G. Smith
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

#include "anvil/byte-pipe/BytePipeBuilder.hpp"

namespace anvil { namespace BytePipe {

	class ANVIL_DLL_EXPORT BuiltInputPipe final : public InputPipe
	{
	private:
		std::vector<std::shared_ptr<InputPipe>> _pipes;

	protected:
		virtual void* ReadNextPacket(size_t& bytes) final
		{
			return const_cast<void*>(_pipes.back()->ReadBytesFromBuffer(bytes, bytes));
		}

	public:
		BuiltInputPipe(std::vector<std::shared_ptr<InputPipe>>&& pipes) :
			_pipes(std::move(pipes))
		{

		}

		virtual ~BuiltInputPipe()
		{

		}
	};

	class ANVIL_DLL_EXPORT BuiltOutputPipe final : public OutputPipe
	{
	private:
		std::vector<std::shared_ptr<OutputPipe>> _pipes;

	protected:
		virtual std::future_status WriteBytesVirtual(const void* src, size_t& bytes, int timeout_ms) final 
		{
			return _pipes.back()->WriteBytes(src, bytes, timeout_ms);
		}

		virtual std::future_status FlushVirtual(int timeout_ms) final
		{
			return _pipes.back()->Flush(timeout_ms);
		}

	public:
		BuiltOutputPipe(std::vector<std::shared_ptr<OutputPipe>>&& pipes) :
			_pipes(std::move(pipes))
		{

		}

		virtual ~BuiltOutputPipe()
		{

		}
	};

	// ---- InputPipeBuilder ----
	
	InputPipeBuilder::InputPipeBuilder()
	{

	}

	InputPipeBuilder::~InputPipeBuilder()
	{

	}

	std::shared_ptr<InputPipe> InputPipeBuilder::GetPipe()
	{
		return std::shared_ptr<InputPipe>(new BuiltInputPipe(std::move(_pipes)));
	}

	// ---- OutputPipeBuilder ----

	OutputPipeBuilder::OutputPipeBuilder()
	{

	}

	OutputPipeBuilder::~OutputPipeBuilder()
	{

	}

	std::shared_ptr<OutputPipe> OutputPipeBuilder::GetPipe()
	{
		return std::shared_ptr<OutputPipe>(new BuiltOutputPipe(std::move(_pipes)));
	}

}}
