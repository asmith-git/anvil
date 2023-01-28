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
		_next_id = -1;
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

		if (_next_id >= 0) {
			_str += "component_id='";
			_str += std::to_string(_next_id);
			_str += "'";
			_next_id = 0;
		}

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

	// Reading

	static size_t CountAttributes(const rapidxml::xml_node<>& node) {
		rapidxml::xml_attribute<>* tmp = node.first_attribute();
		size_t count = 0u;
		while (tmp) {
			++count;
			tmp = tmp->next_attribute();
		}
		return count;
	}

	static size_t CountChildNodes(const rapidxml::xml_node<>& node) {
		rapidxml::xml_node<>* tmp = node.first_node();
		size_t count = 0u;
		while (tmp) {
			++count;
			tmp = tmp->next_sibling();
		}
		return count;
	}

	static rapidxml::xml_attribute<>* FindAttribute(const rapidxml::xml_node<>& node, const std::string& name) {
		rapidxml::xml_attribute<>* tmp = node.first_attribute();
		while (tmp) {
			if (tmp->name() == name) return tmp;
			tmp = tmp->next_attribute();
		}
		return nullptr;
	}

	static rapidxml::xml_node<>* FindChildNode(const rapidxml::xml_node<>& node, const std::string& name) {
		rapidxml::xml_node<>* tmp = node.first_node();
		while (tmp) {
			if (tmp->name() == name) return tmp;
			tmp = tmp->next_sibling();
		}
		return nullptr;
	}

	template<class T>
	static T ReadPrimative(const rapidxml::xml_node<>& node) {
		if ANVIL_CONSTEXPR_FN (std::is_same<bool, T>::value) {
			if (strcmp(node.value(), "true") == 0) return true;
			if (strcmp(node.value(), "false") == 0) return false;
		}

		std::stringstream ss(node.value());
		T tmp;
		ss >> tmp;
		return tmp;
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

	static bool IsComponentID(const std::string& str) {
		for (char c : str) if (c < '0' || c > '9') return false;
		return true;
	}

	void ReadXML(const rapidxml::xml_node<>& node, Parser& parser) {
		if (strcmp(node.name(),"anvil_pod") == 0) {
			// Interpret as pod
			uint32_t bytes = node.value_size() / 2;
			uint8_t* buffer = static_cast<uint8_t*>(_alloca(bytes));

			ConvertHexToBin(node.value(), bytes, buffer);

			parser.OnUserPOD(
				std::stoi(FindAttribute(node, "type")->value()),
				bytes,
				buffer
			);

		} else if (strcmp(node.name(), "anvil_array") == 0) {
			// Interpret as array
			parser.OnArrayBegin(static_cast<uint32_t>(CountChildNodes(node)));
			rapidxml::xml_node<>* tmp = node.first_node();
			while (tmp) {
				ReadXML(*tmp, parser);
				tmp = tmp->next_sibling();
			}
			parser.OnArrayEnd();

		} else if (strcmp(node.name(), "anvil_object") == 0) {
			// Interpret as object
			parser.OnObjectBegin(static_cast<uint32_t>(CountChildNodes(node)));
			rapidxml::xml_node<>* tmp = node.first_node();
			while (tmp) {
				parser.OnComponentID(std::stoi(FindAttribute(node, "component_id")->value()));
				ReadXML(*tmp, parser);
				tmp = tmp->next_sibling();
			}
			parser.OnObjectEnd();

		}  else if (strcmp(node.name(), "anvil_value") == 0) {
			// Interpret as primative value
			rapidxml::xml_attribute<>* type = FindAttribute(node, "type");
			if (type) {
				if (strcmp(node.value(), "uint8") == 0) {
					parser.OnPrimitiveU8(ReadPrimative<uint8_t>(node));
					return;
				} else if (strcmp(node.value(), "uint16") == 0) {
					parser.OnPrimitiveU16(ReadPrimative<uint16_t>(node));
					return;
				} else if (strcmp(node.value(), "uint32") == 0) {
					parser.OnPrimitiveU32(ReadPrimative<uint32_t>(node));
					return;
				} else if (strcmp(node.value(), "uint64") == 0) {
					parser.OnPrimitiveU64(ReadPrimative<uint64_t>(node));
					return;
				} else if (strcmp(node.value(), "int8") == 0) {
					parser.OnPrimitiveS8(ReadPrimative<int8_t>(node));
					return;
				} else if (strcmp(node.value(), "int16") == 0) {
					parser.OnPrimitiveS16(ReadPrimative<int16_t>(node));
					return;
				} else if (strcmp(node.value(), "int32") == 0) {
					parser.OnPrimitiveS32(ReadPrimative<int32_t>(node));
					return;
				} else if (strcmp(node.value(), "int64") == 0) {
					parser.OnPrimitiveS64(ReadPrimative<int64_t>(node));
					return;
				} else if (strcmp(node.value(), "float32") == 0) {
					parser.OnPrimitiveF32(ReadPrimative<float>(node));
					return;
				} else if (strcmp(node.value(), "float32") == 0) {
					parser.OnPrimitiveF64(ReadPrimative<double>(node));
					return;
				} else if (strcmp(node.value(), "bool") == 0) {
					parser.OnPrimitiveBool(ReadPrimative<bool>(node));
					return;
				} else if (strcmp(node.value(), "char") == 0) {
					parser.OnPrimitiveC8(ReadPrimative<char>(node));
					return;
				} else if (strcmp(node.value(), "null") == 0) {
					parser.OnNull();
					return;
				}
			}
			parser.OnPrimitiveString(node.value(), node.value_size());

		} else  {
			// Node not formatted as expected, but try to interpret it anyway
			size_t attribute_count = CountAttributes(node);
			size_t node_count = CountChildNodes(node);
			std::string value = node.value();

			if (attribute_count > 0 || node_count > 0) {
				if (!value.empty()) throw std::runtime_error("anvil::ReadXML : Failed to inteprpet XML data");

				parser.OnObjectBegin(static_cast<uint32_t>(attribute_count + node_count));

				{
					rapidxml::xml_attribute<>* tmp = node.first_attribute();
					while (tmp) {
						std::string id = tmp->name();
						if (IsComponentID(id)) {
							parser.OnComponentID(std::stoi(id));
						} else {
							//parser.OnComponentID(id);
							throw std::runtime_error("anvil::ReadCML : String component IDs are not implemented");
						}
						parser.OnPrimitiveString(tmp->value(), tmp->value_size());
						tmp = tmp->next_attribute();
					}
				}

				{
					rapidxml::xml_node<>* tmp = node.first_node();
					size_t count = 0u;
					while (tmp) {
						std::string id = tmp->name();
						if (IsComponentID(id)) {
							parser.OnComponentID(std::stoi(id));
						} else {
							//parser.OnComponentID(id);
							throw std::runtime_error("anvil::ReadCML : String component IDs are not implemented");
						}
						ReadXML(*tmp, parser);
						tmp = tmp->next_sibling();
					}
				}

				parser.OnObjectEnd();

			} else if (value.empty()) {
				parser.OnNull();

			} else {
				parser.OnPrimitiveString(node.value(), node.value_size());
			}
		}
	}

#endif

}}