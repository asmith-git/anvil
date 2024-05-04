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

#ifndef ANVILBYTEPIPE_WRITER_HPP
#define ANVILBYTEPIPE_WRITER_HPP

#include <vector>
#include "anvil/byte-pipe/BytePipeReader.hpp"

namespace anvil { namespace BytePipe {

	/*!
		\author Adam Smtih
		\date September 2019
		\brief An output stream for binary data.
		\see InputPipe
	*/
	class ANVIL_DLL_EXPORT OutputPipe 
	{
	private:
		enum { SMALL_BUFFER_LENGTH = 512 };
		uint8_t _small_buffer[SMALL_BUFFER_LENGTH];
		size_t _small_buffer_size;

		std::future_status FlushSmallBuffer(int timeout_ms);

	protected:
		virtual std::future_status WriteBytesVirtual(const void* src, size_t& bytes, int timeout_ms) = 0;
		virtual std::future_status FlushVirtual(int timeout_ms) = 0;

	public:

		OutputPipe();
		virtual ~OutputPipe();

		std::future_status WriteBytes(const void* src, size_t& bytes, int timeout_ms);

		inline void WriteBytes(const void* src, size_t& bytes)
		{
			if (WriteBytes(src, bytes, -1) != std::future_status::ready) throw std::runtime_error("OutputPipe::WriteBytesNew : Timed-out when timeout was set to -1");
		}

		inline std::future_status Flush(int timeout_ms = -1)
		{
			if (FlushSmallBuffer(timeout_ms) == std::future_status::timeout) return std::future_status::timeout;
			if (FlushVirtual(timeout_ms) == std::future_status::timeout) return std::future_status::timeout;
			return std::future_status::ready;
		}
	};

	/*!
		\author Adam Smtih
		\date September 2019
		\brief Writes binary serialised data into an OutputPipe
		\see Reader
	*/
	class ANVIL_DLL_EXPORT Writer final : public Parser 
	{
	private:
		Writer(Writer&&) = delete;
		Writer(const Writer&) = delete;
		Writer& operator=(Writer&&) = delete;
		Writer& operator=(const Writer&) = delete;

		enum State : uint8_t 
		{
			STATE_CLOSED,
			STATE_NORMAL,
			STATE_ARRAY,
			STATE_OBJECT
		};

		enum { BUFFER_SIZE = 128 };
		uint8_t _buffer[BUFFER_SIZE];
		uint8_t _buffer_size;
		OutputPipe& _pipe;
		std::vector<State> _state_stack;
		State _default_state;
		Version _version;
		bool _swap_byte_order;

		State GetCurrentState() const;
		void Write(const void* src, const size_t bytes);
		void _OnPrimitive32(uint32_t value, const uint8_t id);
		void _OnPrimitive64(uint64_t value, const uint8_t id);
		void _OnPrimitiveArray(const void* ptr, const size_t size, const uint8_t id);

		Writer(OutputPipe& pipe, Version version, bool swap_byte_order);

	public:
		Writer(OutputPipe& pipe);
		Writer(OutputPipe& pipe, Version version);
		Writer(OutputPipe& pipe, Version version, Endianness endianness);
		virtual ~Writer();

		Endianness GetEndianness() const;

		// Inherited from Parser

		void OnPipeOpen() final;
		void OnPipeClose() final;
		void OnArrayBegin(const size_t size)  final;
		void OnArrayEnd() final;
		void OnObjectBegin(const size_t component_count) final;
		void OnObjectEnd() final;
		void OnComponentID(const uint16_t id) final;
		void OnComponentID(const char* str, const size_t size) final;
		void OnNull() final;
		void OnPrimitiveF64(const double value) final;
		void OnPrimitiveString(const char* value, const size_t length) final;
		void OnPrimitiveU64(const uint64_t value) final;
		void OnPrimitiveS64(const int64_t value) final;
		void OnPrimitiveF32(const float value) final;
		void OnPrimitiveU8(const uint8_t value) final;
		void OnPrimitiveU16(const uint16_t value) final;
		void OnPrimitiveU32(const uint32_t value) final;
		void OnPrimitiveS8(const int8_t value) final;
		void OnPrimitiveS16(const int16_t value) final;
		void OnPrimitiveS32(const int32_t value) final;
		void OnPrimitiveC8(const char value) final;
#if ANVIL_F8_SUPPORT
		void OnPrimitiveF8(const float8_t value) final;
#endif
#if ANVIL_F16_SUPPORT
		void OnPrimitiveF16(const float16_t value) final;
#endif
		void OnPrimitiveBool(const bool value) final;

		void OnPrimitiveArrayU8(const uint8_t* src, const size_t size) final;
		void OnPrimitiveArrayU16(const uint16_t* src, const size_t size) final;
		void OnPrimitiveArrayU32(const uint32_t* src, const size_t size) final;
		void OnPrimitiveArrayU64(const uint64_t* src, const size_t size) final;
		void OnPrimitiveArrayS8(const int8_t* src, const size_t size) final;
		void OnPrimitiveArrayS16(const int16_t* src, const size_t size) final;
		void OnPrimitiveArrayS32(const int32_t* src, const size_t size) final;
		void OnPrimitiveArrayS64(const int64_t* src, const size_t size) final;
		void OnPrimitiveArrayF32(const float* src, const size_t size) final;
		void OnPrimitiveArrayF64(const double* src, const size_t size) final;
		void OnPrimitiveArrayC8(const char* src, const size_t size) final;
#if ANVIL_F8_SUPPORT
		void OnPrimitiveArrayF16(const float8_t* src, const size_t size) final;
#endif
#if ANVIL_F16_SUPPORT
		void OnPrimitiveArrayF16(const float16_t* src, const size_t size) final;
#endif
		void OnPrimitiveArrayBool(const bool* src, const size_t size) final;

		void OnUserPOD(const PodType type, const size_t bytes, const void* data) final;
	};

}}

#endif
