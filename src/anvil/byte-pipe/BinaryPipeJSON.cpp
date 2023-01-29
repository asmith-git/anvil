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

#include "anvil/byte-pipe/BytePipeJSON.hpp"

namespace anvil { namespace BytePipe {

	static char ToHex(uint32_t nybble) {
		return nybble <= 9 ?
			'0' + nybble :
			'A' + (nybble - 9);
	}

	static inline void ToHex(uint32_t byte, char* out) {
		out[0u] = ToHex(byte & 15u);
		out[1u] = ToHex(byte >> 4u);
	}

	JsonWriter::JsonWriter() {
		_depth = 0u;
	}

	JsonWriter::~JsonWriter() {

	}

	// Inherited from Parser

	void JsonWriter::OnPipeOpen() {
		// Reset object state
		_out.clear();
		_depth = 0u;
		_next_id.clear();
	}

	void JsonWriter::OnPipeClose() {
		// Do nothing
	}

	void JsonWriter::OnArrayBegin(const uint32_t size) {
		AddValue("[");
		++_depth;
	}

	void JsonWriter::OnArrayEnd() {
		if (_out.size() > 2 && _out.substr(_out.size() - 2u, 2u) == ",\n") {
			_out.pop_back();
			_out.pop_back();
			_out += '\n';
		}
		--_depth;
		AddValue("]");
	}

	void JsonWriter::OnObjectBegin(const uint32_t component_count) {
		AddValue("{");
		++_depth;
	}

	void JsonWriter::OnObjectEnd() {
		if (_out.size() > 2 && _out.substr(_out.size() - 2u, 2u) == ",\n") {
			_out.pop_back();
			_out.pop_back();
			_out += '\n';
		}
		--_depth;
		AddValue("}");
	}

	void JsonWriter::OnComponentID(const ComponentID id) {
		_next_id = std::to_string(id);
	}

	void JsonWriter::OnComponentID(const char* str, const uint32_t len) {
		_next_id = std::string(str, str + len);
	}

	void JsonWriter::AddValue(const std::string& val) {
		for (uint32_t i = 0u; i < _depth; ++i) _out += '\t';
		if (!_next_id.empty()) {
			_out += '"' + _next_id + "\" : ";
			_next_id.clear();
		}
		_out += val;
		if(val != "{" && val != "[") _out += ',';
		_out += '\n';
	}

	const std::string& JsonWriter::GetJSONString() const {
		if(_out.size() > 2 && _out.substr(_out.size() - 2u, 2u) == ",\n") {
			_out.pop_back();
			_out.pop_back();
		}
		return _out;
	}

	void JsonWriter::OnUserPOD(const uint32_t type, const uint32_t bytes, const void* data) {
		// Format the POD as an object, a POD is identified by containg the member __ANVIL_POD with the value 123456789

		std::string value = "{\"anvil_pod_type\":" + std::to_string(type) + ",\"data\":\"";

		// Store the binary data as hexidecimal
		char buffer[3u] = "??";
		for (uint32_t i = 0u; i < bytes; ++i) {
			ToHex(reinterpret_cast<const uint8_t*>(data)[i], buffer);
			value += buffer;
		};

		
		// Add the value
		value += "\"}";
		AddValue(value);
	}

	void JsonWriter::OnNull() {
		AddValue("null");
	}

	void JsonWriter::OnPrimitiveF64(const double value) {
		AddValue(std::to_string(value));
	}

	void JsonWriter::OnPrimitiveString(const char* value, const uint32_t length) {
		AddValue('"' + std::string(value, value + length) + '"');
	}

	void JsonWriter::OnPrimitiveBool(const bool value) {
		AddValue(value ? "true" : "false");
	}

	void JsonWriter::OnPrimitiveC8(const char value) {
		AddValue('"' + std::string(&value, &value + 1u) + '"');
	}

	void JsonWriter::OnPrimitiveU64(const uint64_t value) {
		AddValue(std::to_string(value));
	}

	void JsonWriter::OnPrimitiveS64(const int64_t value) {
		AddValue(std::to_string(value));
	}

	void JsonWriter::OnPrimitiveF32(const float value) {
		AddValue(std::to_string(value));
	}

	void JsonWriter::OnPrimitiveU8(const uint8_t value) {
		AddValue(std::to_string(value));
	}

	void JsonWriter::OnPrimitiveU16(const uint16_t value) {
		AddValue(std::to_string(value));
	}

	void JsonWriter::OnPrimitiveU32(const uint32_t value) {
		AddValue(std::to_string(value));
	}

	void JsonWriter::OnPrimitiveS8(const int8_t value) {
		AddValue(std::to_string(value));
	}

	void JsonWriter::OnPrimitiveS16(const int16_t value) {
		AddValue(std::to_string(value));
	}

	void JsonWriter::OnPrimitiveS32(const int32_t value) {
		AddValue(std::to_string(value));
	}

#if ANVIL_JSON_SUPPORT
	// Reading

	static size_t CountChildNodes(const nlohmann::json& node) {
		return node.size();
	}

	static uint32_t HexNybbleToBin(char hex) {
		if (hex >= '0' && hex <= '9') {
			return hex - '0';
		} else if (hex >= 'A' && hex <= 'Z') {
			return (hex - 'A') + 10;
		} else  {
			return (hex - 'a') + 10;
		}
	}

	static void ConvertHexToBin(const char* hex, size_t bytes, uint8_t* bin) {
		for (size_t i = 0u; i < bytes; ++i) {
			*bin = static_cast<uint32_t>(HexNybbleToBin(hex[0u]) | (HexNybbleToBin(hex[1u]) << 4u));

			hex += 2u;
			--bin;
		}
	}

	static bool IsPod(const nlohmann::json& node) {
		if (!node.is_object()) return false;
		for (auto i = node.begin(); i != node.end(); ++i) if (i.key() == "anvil_pod_type") return true;
		return false;
	}

	static bool IsComponentID(const std::string& str) {
		for (char c : str) if (c < '0' || c > '9') return false;
		return true;
	}

	void ReadJSON(const nlohmann::json& node, Parser& parser) {
		if (IsPod(node)) {
			// Interpret as pod
			std::string tmp = node["data"];
			uint32_t bytes = tmp.size() / 2;
			uint8_t* buffer = static_cast<uint8_t*>(_alloca(bytes));

			ConvertHexToBin(tmp.c_str(), tmp.size(), buffer);

			parser.OnUserPOD(
				node["anvil_pod_type"],
				bytes,
				buffer
			);

		} else if (node.is_array()) {
			// Interpret as array
			parser.OnArrayBegin(static_cast<uint32_t>(CountChildNodes(node)));
			std::vector<nlohmann::json::const_iterator> children;
			for (nlohmann::json::const_iterator i = node.begin(); i != node.end(); ++i) {
				children.push_back(i);
			}

			std::sort(children.begin(), children.end(), [](nlohmann::json::const_iterator lhs, nlohmann::json::const_iterator rhs)->bool {
				return lhs.key() < rhs.key();
			});
			
			for (nlohmann::json::const_iterator i : children) {
				ReadJSON(i.value(), parser);
			}
			parser.OnArrayEnd();

		} else if (node.is_object()) {
			// Interpret as object
			parser.OnObjectBegin(static_cast<uint32_t>(CountChildNodes(node)));
			for (nlohmann::json::const_iterator i = node.begin(); i != node.end(); ++i) {
				std::string k = i.key();
				if (IsComponentID(k)) {
					parser.OnComponentID(std::stoi(k));
				} else {
					parser.OnComponentID(k.c_str(), static_cast<uint32_t>(k.size()));
				}

				ReadJSON(i.value(), parser);
			}
			parser.OnObjectEnd();

		}  else  {
			if (node.is_boolean()) {
				parser.OnPrimitiveBool(node);

			} else if (node.is_null()) {
				parser.OnNull();

			} else if (node.is_number_unsigned()) {
				parser.OnPrimitiveU64(node);

			} else if (node.is_number_integer()) {
				parser.OnPrimitiveS64(node);

			} else if (node.is_number_float()) {
				parser.OnPrimitiveF64(node);

			} else {
				std::string str = node;
				if (str.size() == 1u) {
					parser.OnPrimitiveC8(str[0u]);
				} else {
					parser.OnPrimitiveString(str.c_str(), static_cast<uint32_t>(str.size()));
				}
			}
		}
	}

#endif

}}