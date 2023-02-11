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

#ifndef ANVIL_BYTEPIPE_REPEATER_HPP
#define ANVIL_BYTEPIPE_REPEATER_HPP

#include "anvil/byte-pipe/BytePipeReader.hpp"

namespace anvil { namespace BytePipe {

	/*!
		\author Adam Smtih
		\date September 2023
		\brief Duplicates data to multiple parsers
	*/
	class ANVIL_DLL_EXPORT Repeater final : public Parser {
	private:
		std::vector<Parser*> _parsers;
	public:
		Repeater();
		virtual ~Repeater();

		void AddParser(Parser&);
		void Remove(const Parser&);

		// Inherited from Parser

		void OnPipeOpen() final;
		void OnPipeClose() final;
		void OnArrayBegin(const size_t size) final;
		void OnArrayEnd() final;
		void OnObjectBegin(const size_t component_count) final;
		void OnObjectEnd() final;
		void OnComponentID(const ComponentID id) final;
		void OnComponentID(const char* str, const size_t size) final;
		void OnUserPOD(const PodType type, const size_t bytes, const void* data) final;
		void OnNull() final;
		void OnPrimitiveF64(const double value) final;
		void OnPrimitiveString(const char* value, const size_t length) final;
		void OnPrimitiveBool(const bool value) final;
		void OnPrimitiveC8(const char value) final;
		void OnPrimitiveU64(const uint64_t value) final;
		void OnPrimitiveS64(const int64_t value) final;
		void OnPrimitiveF32(const float value) final;
		void OnPrimitiveU8(const uint8_t value) final;
		void OnPrimitiveU16(const uint16_t value) final;
		void OnPrimitiveU32(const uint32_t value) final;
		void OnPrimitiveS8(const int8_t value) final;
		void OnPrimitiveS16(const int16_t value) final;
		void OnPrimitiveS32(const int32_t value) final;
		void OnPrimitiveF16(const half value) final;
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
		void OnPrimitiveArrayF16(const half* src, const size_t size) final;
		void OnPrimitiveArrayBool(const bool* src, const size_t size) final;
	};

}}

#endif
