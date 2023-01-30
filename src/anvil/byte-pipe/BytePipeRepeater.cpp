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

#include "anvil/byte-pipe/BytePipeRepeater.hpp"

namespace anvil { namespace BytePipe {

	// Repeater

	Repeater::Repeater() {

	}

	Repeater::~Repeater() {

	}

	void Repeater::AddParser(Parser& parser) {
		auto end = _parsers.end();
		auto i = std::find(_parsers.begin(), end, &parser);
		if (i != end) return;
		_parsers.push_back(&parser);
	}

	void Repeater::Remove(const Parser& parser) {
		auto end = _parsers.end();
		auto i = std::find(_parsers.begin(), end, &parser);
		if (i != end) _parsers.erase(i);
	}

	void Repeater::OnPipeOpen() {
		for (Parser* parser : _parsers) parser->OnPipeOpen();
	}

	void Repeater::OnPipeClose() {
		for (Parser* parser : _parsers) parser->OnPipeClose();
	}

	void Repeater::OnArrayBegin(const uint32_t size) {
		for (Parser* parser : _parsers) parser->OnArrayBegin(size);
	}

	void Repeater::OnArrayEnd() {
		for (Parser* parser : _parsers) parser->OnArrayEnd();
	}

	void Repeater::OnObjectBegin(const uint32_t component_count) {
		for (Parser* parser : _parsers) parser->OnObjectBegin(component_count);
	}

	void Repeater::OnObjectEnd() {
		for (Parser* parser : _parsers) parser->OnObjectEnd();
	}

	void Repeater::OnComponentID(const ComponentID id) {
		for (Parser* parser : _parsers) parser->OnComponentID(id);
	}

	void Repeater::OnComponentID(const char* str, const uint32_t size) {
		for (Parser* parser : _parsers) parser->OnComponentID(str, size);
	}

	void Repeater::OnUserPOD(const PodType type, const uint32_t bytes, const void* data) {
		for (Parser* parser : _parsers) parser->OnUserPOD(type, bytes, data);
	}

	void Repeater::OnNull() {
		for (Parser* parser : _parsers) parser->OnNull();
	}

	void Repeater::OnPrimitiveF64(const double value) {
		for (Parser* parser : _parsers) parser->OnPrimitiveF64(value);
	}

	void Repeater::OnPrimitiveString(const char* value, const uint32_t length) {
		for (Parser* parser : _parsers) parser->OnPrimitiveString(value, length);
	}

	void Repeater::OnPrimitiveBool(const bool value) {
		for (Parser* parser : _parsers) parser->OnPrimitiveBool(value);
	}

	void Repeater::OnPrimitiveC8(const char value) {
		for (Parser* parser : _parsers) parser->OnPrimitiveC8(value);
	}

	void Repeater::OnPrimitiveU64(const uint64_t value) {
		for (Parser* parser : _parsers) parser->OnPrimitiveU64(value);
	}

	void Repeater::OnPrimitiveS64(const int64_t value) {
		for (Parser* parser : _parsers) parser->OnPrimitiveS64(value);
	}

	void Repeater::OnPrimitiveF32(const float value) {
		for (Parser* parser : _parsers) parser->OnPrimitiveF32(value);
	}

	void Repeater::OnPrimitiveU8(const uint8_t value) {
		for (Parser* parser : _parsers) parser->OnPrimitiveU8(value);
	}

	void Repeater::OnPrimitiveU16(const uint16_t value) {
		for (Parser* parser : _parsers) parser->OnPrimitiveU16(value);
	}

	void Repeater::OnPrimitiveU32(const uint32_t value) {
		for (Parser* parser : _parsers) parser->OnPrimitiveU32(value);
	}

	void Repeater::OnPrimitiveS8(const int8_t value) {
		for (Parser* parser : _parsers) parser->OnPrimitiveS8(value);
	}

	void Repeater::OnPrimitiveS16(const int16_t value) {
		for (Parser* parser : _parsers) parser->OnPrimitiveS16(value);
	}

	void Repeater::OnPrimitiveS32(const int32_t value) {
		for (Parser* parser : _parsers) parser->OnPrimitiveS32(value);
	}

	void Repeater::OnPrimitiveF16(const half value) {
		for (Parser* parser : _parsers) parser->OnPrimitiveF16(value);
	}

	void Repeater::OnPrimitiveArrayU8(const uint8_t* src, const uint32_t size) {
		for (Parser* parser : _parsers) parser->OnPrimitiveArrayU8(src, size);
	}

	void Repeater::OnPrimitiveArrayU16(const uint16_t* src, const uint32_t size) {
		for (Parser* parser : _parsers) parser->OnPrimitiveArrayU16(src, size);
	}

	void Repeater::OnPrimitiveArrayU32(const uint32_t* src, const uint32_t size) {
		for (Parser* parser : _parsers) parser->OnPrimitiveArrayU32(src, size);
	}

	void Repeater::OnPrimitiveArrayU64(const uint64_t* src, const uint32_t size) {
		for (Parser* parser : _parsers) parser->OnPrimitiveArrayU64(src, size);
	}

	void Repeater::OnPrimitiveArrayS8(const int8_t* src, const uint32_t size) {
		for (Parser* parser : _parsers) parser->OnPrimitiveArrayS8(src, size);
	}

	void Repeater::OnPrimitiveArrayS16(const int16_t* src, const uint32_t size) {
		for (Parser* parser : _parsers) parser->OnPrimitiveArrayS16(src, size);
	}

	void Repeater::OnPrimitiveArrayS32(const int32_t* src, const uint32_t size) {
		for (Parser* parser : _parsers) parser->OnPrimitiveArrayS32(src, size);
	}

	void Repeater::OnPrimitiveArrayS64(const int64_t* src, const uint32_t size) {
		for (Parser* parser : _parsers) parser->OnPrimitiveArrayS64(src, size);
	}

	void Repeater::OnPrimitiveArrayF32(const float* src, const uint32_t size) {
		for (Parser* parser : _parsers) parser->OnPrimitiveArrayF32(src, size);
	}

	void Repeater::OnPrimitiveArrayF64(const double* src, const uint32_t size) {
		for (Parser* parser : _parsers) parser->OnPrimitiveArrayF64(src, size);
	}

	void Repeater::OnPrimitiveArrayC8(const char* src, const uint32_t size) {
		for (Parser* parser : _parsers) parser->OnPrimitiveArrayC8(src, size);
	}

	void Repeater::OnPrimitiveArrayF16(const half* src, const uint32_t size) {
		for (Parser* parser : _parsers) parser->OnPrimitiveArrayF16(src, size);
	}

	void Repeater::OnPrimitiveArrayBool(const bool* src, const uint32_t size) {
		for(Parser* parser : _parsers) parser->OnPrimitiveArrayBool(src, size);
	}

}}