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
#include "anvil/core/Base64.hpp"
#include "anvil/core/Hexadecimal.hpp"

namespace anvil { namespace BytePipe {

	JsonWriter::JsonWriter() :
		JsonWriter(true)
	{}

	JsonWriter::JsonWriter(bool indent) :
		_depth(0u),
		_indent(indent)
	{}

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

	void JsonWriter::OnArrayBegin(const size_t size) {
		AddValue("[");
		++_depth;
	}

	void JsonWriter::OnArrayEnd() {
		if (_indent) {
			if (_out.size() > 2 && _out.substr(_out.size() - 2u, 2u) == ",\n") {
				_out.pop_back();
				_out.pop_back();
				_out += '\n';
			}
		} else {
			if (_out.back() == ',') _out.pop_back();
		}
		--_depth;
		AddValue("]");
	}

	void JsonWriter::OnObjectBegin(const size_t component_count) {
		AddValue("{");
		++_depth;
	}

	void JsonWriter::OnObjectEnd() {
		if (_indent) {
			if (_out.size() > 2 && _out.substr(_out.size() - 2u, 2u) == ",\n") {
				_out.pop_back();
				_out.pop_back();
				_out += '\n';
			}
		} else {
			if (_out.back() == ',') _out.pop_back();
		}
		--_depth;
		AddValue("}");
	}

	void JsonWriter::OnComponentID(const ComponentID id) {
		_next_id = std::to_string(id);
	}

	void JsonWriter::OnComponentID(const char* str, const size_t len) {
		_next_id = std::string(str, str + len);
	}

	void JsonWriter::AddValue(const std::string& val) {
		if(_indent) for (uint32_t i = 0u; i < _depth; ++i) _out += '\t';
		if (!_next_id.empty()) {
			_out += '"' + _next_id;
			_out += _indent ? "\" : " : "\":";
			_next_id.clear();
		}
		_out += val;
		if(val != "{" && val != "[") _out += ',';
		if (_indent) _out += '\n';
	}

	const std::string& JsonWriter::GetJSONString() const {
		if (_indent) {
			if (_out.size() > 2 && _out.substr(_out.size() - 2u, 2u) == ",\n") {
				_out.pop_back();
				_out.pop_back();
				_out += '\n';
			}
		} else {
			if (_out.back() == ',') _out.pop_back();
		}
		return _out;
	}

	void JsonWriter::OnUserPOD(const PodType type, const size_t bytes, const void* data) {
		// Format the POD as an object, a POD is identified by containg the member __ANVIL_POD with the value 123456789

		std::string value = "{\"anvil_pod_type\":" + std::to_string(type) + ",\"encoding\":\"Base64\",\"data\":\"";

		// Store the binary data as Base64
		value += Base64::Encode(reinterpret_cast<const uint8_t*>(data), bytes);
		
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

	void JsonWriter::OnPrimitiveString(const char* value, const size_t length) {
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
			const std::string& tmp = node["data"];

			auto encoding_it = node.find("encoding");
			std::string encoding = "Hex";
			if (encoding_it != node.end()) {
				encoding = static_cast<std::string>(encoding_it.value());
			}

			std::vector<uint8_t> data;
			if (encoding == "Base64") {
				data = Base64::Decode(tmp.c_str(), tmp.size());
			} else if (encoding == "Hex") {
				data = Hexadecimal::Decode(tmp.c_str(), tmp.size());
			} else {
				throw std::runtime_error("anvil::ReadJSON : Unknown POD encoding");
			}

			parser.OnUserPOD(
				node["anvil_pod_type"],
				data.size(),
				data.data()
			);

		} else if (node.is_array()) {
			// Interpret as array
			parser.OnArrayBegin(CountChildNodes(node));
			
			for (nlohmann::json::const_iterator i = node.begin(); i != node.end(); ++i) {
				ReadJSON(i.value(), parser);
			}
			parser.OnArrayEnd();

		} else if (node.is_object()) {
			// Interpret as object
			parser.OnObjectBegin(CountChildNodes(node));
			for (nlohmann::json::const_iterator i = node.begin(); i != node.end(); ++i) {
				std::string k = i.key();
				if (IsComponentID(k)) {
					parser.OnComponentID(std::stoi(k));
				} else {
					parser.OnComponentID(k.c_str(), k.size());
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
					parser.OnPrimitiveString(str.c_str(), str.size());
				}
			}
		}
	}

#endif

}}