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
#if ANVIL_JSON_SUPPORT
		_json_stack.push_back(&_root);
		_next_id = 0;
#endif
	}

	JsonWriter::~JsonWriter() {

	}

	// Inherited from Parser

	void JsonWriter::OnPipeOpen() {
		// Reset object state
#if ANVIL_JSON_SUPPORT
		_json_stack.clear();
		_root = nlohmann::json::value_t::null;
		_json_stack.push_back(&_root);
#else
		_out.clear();
#endif
	}

	void JsonWriter::OnPipeClose() {
		// Do nothing
	}

	void JsonWriter::OnArrayBegin(const uint32_t size) {
#if ANVIL_JSON_SUPPORT
		_json_stack.push_back(&AddValue(nlohmann::json::value_t::array));
#else
		_out += '[';
#endif
	}

	void JsonWriter::OnArrayEnd() {
#if ANVIL_JSON_SUPPORT
		_json_stack.pop_back();
#else
		if (_out.back() == ',') _out.pop_back();
		_out += ']';
#endif
	}

	void JsonWriter::OnObjectBegin(const uint32_t component_count) {
#if ANVIL_JSON_SUPPORT
		_json_stack.push_back(&AddValue(nlohmann::json::value_t::object));
#else
		_out += '{';
#endif
	}

	void JsonWriter::OnObjectEnd() {
#if ANVIL_JSON_SUPPORT
		_json_stack.pop_back();
#else
		if (_out.back() == ',') _out.pop_back();
		_out += '}';
#endif
	}

	void JsonWriter::OnComponentID(const ComponentID id) {
#if ANVIL_JSON_SUPPORT
		_next_id = id;
#else
		_out += '"' + std::to_string(id) + "\":";
#endif
	}

#if ANVIL_JSON_SUPPORT
	nlohmann::json& JsonWriter::AddValue(nlohmann::json value) {
		nlohmann::json& parent = *_json_stack.back();
		if (parent.is_null()) {
			parent = value;
			return parent;

		} else if (parent.is_array()) {
			parent.push_back(value);
			return parent.back();

		} else if (parent.is_object()) {
			std::string id = std::to_string(_next_id);
			parent.emplace(id,value);
			return parent[id];

		} else {
			throw std::runtime_error("JsonWriter::AddValue : Invalid state");
		}
	}

	const nlohmann::json& JsonWriter::GetJSON() const {
		return _root;
	}

#else
	void JsonWriter::AddValue(const std::string& val) {
		_out += val;
		_out += ",";
	}

	void JsonWriter::AddValueC(const char* val) {
		_out += val;
		_out += ",";
	}

	const std::string& JsonWriter::GetJSON() const {
		if (_out.back() == ',') _out.pop_back();
		return _out;
	}
#endif

	void JsonWriter::OnUserPOD(const uint32_t type, const uint32_t bytes, const void* data) {
		// Format the POD as an object, a POD is identified by containg the member __ANVIL_POD with the value 123456789
#if ANVIL_JSON_SUPPORT
		nlohmann::json jvalue(nlohmann::json::value_t::object);
		jvalue["__ANVIL_POD"] =  "123456789";
		jvalue["type"] = type;

		std::string value;
#else
		std::string value = "{\"__ANVIL_POD\":123456789,\"type\":" + std::to_string(type) + ",\"data\":\"";
#endif

		// Store the binary data as hexidecimal
		char buffer[3u] = "??";
		for (uint32_t i = 0u; i < bytes; ++i) {
			ToHex(reinterpret_cast<const uint8_t*>(data)[i], buffer);
			value += buffer;
		};

		
		// Add the value
#if ANVIL_JSON_SUPPORT
		jvalue["data"] = value;
		AddValue(jvalue);
#else
		value += "\"}";
		AddValue(value);
#endif
	}

	void JsonWriter::OnNull() {
#if ANVIL_JSON_SUPPORT
		AddValue(nlohmann::json::value_t::null);
#else
		AddValueC("null");
#endif
	}

	void JsonWriter::OnPrimitiveF64(const double value) {
#if ANVIL_JSON_SUPPORT
		AddValue(value);
#else
		AddValue(std::to_string(value));
#endif
	}

	void JsonWriter::OnPrimitiveString(const char* value, const uint32_t length) {
		AddValue(std::string(value, value + length));
	}

	void JsonWriter::OnPrimitiveBool(const bool value) {
#if ANVIL_JSON_SUPPORT
		AddValue(value);
#else
		AddValueC(value ? "true" : "false");
#endif
	}

	void JsonWriter::OnPrimitiveC8(const char value) {
		OnPrimitiveString(&value, 1u);
	}

	void JsonWriter::OnPrimitiveU64(const uint64_t value) {
#if ANVIL_JSON_SUPPORT
		AddValue(value);
#else
		AddValue(std::to_string(value));
#endif
	}

	void JsonWriter::OnPrimitiveS64(const int64_t value) {
#if ANVIL_JSON_SUPPORT
		AddValue(value);
#else
		AddValue(std::to_string(value));
#endif
	}

	void JsonWriter::OnPrimitiveF32(const float value) {
#if ANVIL_JSON_SUPPORT
		AddValue(value);
#else
		AddValue(std::to_string(value));
#endif
	}

	void JsonWriter::OnPrimitiveU8(const uint8_t value) {
#if ANVIL_JSON_SUPPORT
		AddValue(value);
#else
		AddValue(std::to_string(value));
#endif
	}

	void JsonWriter::OnPrimitiveU16(const uint16_t value) {
#if ANVIL_JSON_SUPPORT
		AddValue(value);
#else
		AddValue(std::to_string(value));
#endif
	}

	void JsonWriter::OnPrimitiveU32(const uint32_t value) {
#if ANVIL_JSON_SUPPORT
		AddValue(value);
#else
		AddValue(std::to_string(value));
#endif
	}

	void JsonWriter::OnPrimitiveS8(const int8_t value) {
#if ANVIL_JSON_SUPPORT
		AddValue(value);
#else
		AddValue(std::to_string(value));
#endif
	}

	void JsonWriter::OnPrimitiveS16(const int16_t value) {
#if ANVIL_JSON_SUPPORT
		AddValue(value);
#else
		AddValue(std::to_string(value));
#endif
	}

	void JsonWriter::OnPrimitiveS32(const int32_t value) {
#if ANVIL_JSON_SUPPORT
		AddValue(value);
#else
		AddValue(std::to_string(value));
#endif
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
		return !node["__ANVIL_POD"].is_null();
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
				node["type"],
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
					throw std::runtime_error("anvil::ReadJSON : String component IDs are not implemented");
					//parser.OnComponentID(k);
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
				parser.OnPrimitiveString(str.c_str(), static_cast<uint32_t>(str.size()));
			}
		}
	}

#endif

}}