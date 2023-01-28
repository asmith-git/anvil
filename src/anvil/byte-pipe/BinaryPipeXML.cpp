//Copyright 2021 Adam G. Smith
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

#include "anvil/byte-pipe/BytePipeXML.hpp"

namespace anvil { namespace BytePipe {

#if ANVIL_XML_SUPPORT
	static char ToHex(uint32_t nybble) {
		return nybble <= 9 ?
			'0' + nybble :
			'A' + (nybble - 9);
	}

	static inline void ToHex(uint32_t byte, char* out) {
		out[0u] = ToHex(byte & 15u);
		out[1u] = ToHex(byte >> 4u);
	}

	XMLWriter::XMLWriter() {
		_depth = 0;
		_next_id = 0;
	}

	XMLWriter::~XMLWriter() {

	}

	// Inherited from Parser

	void XMLWriter::OnPipeOpen() {
		// Reset object state
		_depth = 0;
		_str.clear();
	}

	void XMLWriter::OnPipeClose() {
		// Do nothing
	}

	void XMLWriter::OnArrayBegin(const uint32_t size) {
		for (size_t i = 0; i < _depth; ++i) _str += '\t';
		_str += "<anvil_array>\n";
		++_depth;
	}

	void XMLWriter::OnArrayEnd() {
		for (size_t i = 0; i < _depth; ++i) _str += '\t';
		_str += "</anvil_array>\n";
		--_depth;
	}

	void XMLWriter::OnObjectBegin(const uint32_t component_count) {
		for (size_t i = 0; i < _depth; ++i) _str += '\t';
		_str += "<anvil_object>\n";
		++_depth;
	}

	void XMLWriter::OnObjectEnd() {
		for (size_t i = 0; i < _depth; ++i) _str += '\t';
		_str += "<anvil_object>\n";
		--_depth;
	}

	void XMLWriter::OnComponentID(const ComponentID id) {
		_next_id = id;
	}


	void XMLWriter::AddNode(const std::string& name, const std::string& value, std::vector<std::pair<std::string, std::string>> attributes) {
		for (size_t i = 0; i < _depth; ++i) _str += '\t';

		_str += '<';
		_str += name;
		for (const auto& i : attributes) {
			_str += ' ';
			_str += i.first;
			_str += "='";
			_str += i.second;
			_str += "'";
		}
		_str += '>';

		_str += value;

		_str += "</";
		_str += name;
		_str += '>';

		_str += '\n';
	}

	const std::string& XMLWriter::GetXMLString() const {
		return _str;
	}

	void XMLWriter::OnUserPOD(const uint32_t type, const uint32_t bytes, const void* data) {
		// Store the binary data as hexidecimal
		std::string value;
		char buffer[3u] = "??";
		for (uint32_t i = 0u; i < bytes; ++i) {
			ToHex(reinterpret_cast<const uint8_t*>(data)[i], buffer);
			value += buffer;
		};

		// Add the value
		AddNode("anvil_pod", value, { {"type", std::to_string(type)} });
	}

	void XMLWriter::OnNull() {
		AddNode("anvil_value", std::string(), { {"type", "null"} });
	}

	void XMLWriter::OnPrimitiveF64(const double value) {
		AddNode("anvil_value", std::to_string(value), { {"type", "float32"} });
	}

	void XMLWriter::OnPrimitiveString(const char* value, const uint32_t length) {
		AddNode("anvil_value", std::string(value, value + length), { {"type", "string"} });
	}

	void XMLWriter::OnPrimitiveBool(const bool value) {
		AddNode("anvil_value", std::string(value ? "true" : "false"), { {"type", "bool"} });
	}

	void XMLWriter::OnPrimitiveC8(const char value) {
		AddNode("anvil_value", std::to_string(value), { {"type", "char"} });
	}

	void XMLWriter::OnPrimitiveU64(const uint64_t value) {
		AddNode("anvil_value", std::to_string(value), { {"type", "uint64"} });
	}

	void XMLWriter::OnPrimitiveS64(const int64_t value) {
		AddNode("anvil_value", std::to_string(value), { {"type", "int64"} });
	}

	void XMLWriter::OnPrimitiveF32(const float value) {
		AddNode("anvil_value", std::to_string(value), { {"type", "float32"} });
	}

	void XMLWriter::OnPrimitiveU8(const uint8_t value) {
		AddNode("anvil_value", std::to_string(value), { {"type", "uint8"} });
	}

	void XMLWriter::OnPrimitiveU16(const uint16_t value) {
		AddNode("anvil_value", std::to_string(value), { {"type", "uint16"} });
	}

	void XMLWriter::OnPrimitiveU32(const uint32_t value) {
		AddNode("anvil_value", std::to_string(value), { {"type", "uint32"} });
	}

	void XMLWriter::OnPrimitiveS8(const int8_t value) {
		AddNode("anvil_value", std::to_string(value), { {"type", "int8"} });
	}

	void XMLWriter::OnPrimitiveS16(const int16_t value) {
		AddNode("anvil_value", std::to_string(value), { {"type", "int16"} });
	}

	void XMLWriter::OnPrimitiveS32(const int32_t value) {
		AddNode("anvil_value", std::to_string(value), {{"type", "int32"}});
	}
#endif

}}