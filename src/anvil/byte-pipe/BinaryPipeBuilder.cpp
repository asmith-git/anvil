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

	public:
		BuiltOutputPipe(std::vector<std::shared_ptr<OutputPipe>>&& pipes) :
			_pipes(std::move(pipes))
		{

		}

		virtual ~BuiltOutputPipe()
		{

		}

		virtual size_t WriteBytes(const void* src, const size_t bytes)
		{
			return _pipes.back()->WriteBytes(src, bytes);
		}

		virtual void WriteBytes(const void** src, const size_t* bytes_requested, const size_t count, int timeout_ms)
		{
			_pipes.back()->WriteBytes(src, bytes_requested, count, timeout_ms);
		}

		virtual void Flush()
		{
			_pipes.back()->Flush();
		}

		virtual void WriteBytesFast(const void* src, size_t bytes, int timeout_ms) final
		{
			_pipes.back()->WriteBytesFast(src, bytes, timeout_ms);
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
