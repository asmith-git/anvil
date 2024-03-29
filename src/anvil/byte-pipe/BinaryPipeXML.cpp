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
#include "anvil/core/Base64.hpp"
#include "anvil/core/Hexadecimal.hpp"

namespace anvil { namespace BytePipe {

	XMLWriter::XMLWriter() :
		XMLWriter(true)
	{}

	XMLWriter::XMLWriter(bool indent) :
		_indent(indent)
	{}

	XMLWriter::~XMLWriter() {

	}

	// Inherited from Parser

	void XMLWriter::OnPipeOpen() {
		// Reset object state
		_next_id_str.clear();
		_node_names.clear();
		_str.clear();
	}

	void XMLWriter::OnPipeClose() {
		// Do nothing
	}
	
	std::string XMLWriter::GetNextNodeName(const char* default_name) {
		if (!_next_id_str.empty()) {
			std::string tmp = std::move(_next_id_str);
			_next_id_str.clear();
			return tmp;
		}
		return default_name;
	}
	
	#pragma warning( disable : 4100) // Size is not used, name is retained to improve code readability
	void XMLWriter::OnArrayBegin(const size_t size) {
		if(_indent) for (size_t i = 0; i < _node_names.size(); ++i) _str += '\t';
		std::string name = GetNextNodeName("array");
		_node_names.push_back(name);
		_str += '<' + name + " anvil_type='array'>";
		if (_indent) _str += '\n';
	}

	void XMLWriter::OnArrayEnd() {
		if (_indent) for (size_t i = 0; i < _node_names.size() - 1u; ++i) _str += '\t';
		_str += "</" + _node_names.back() + ">";
		if (_indent) _str += '\n';
		_node_names.pop_back();
	}

	void XMLWriter::OnObjectBegin(const size_t component_count) {
		if (_indent) for (size_t i = 0; i < _node_names.size(); ++i) _str += '\t';
		std::string name = GetNextNodeName("object");
		_node_names.push_back(name);
		_str += '<' + name + " anvil_type='object'>";
		if (_indent) _str += '\n';
	}

	void XMLWriter::OnObjectEnd() {
		if (_indent) for (size_t i = 0; i < _node_names.size() - 1u; ++i) _str += '\t';
		_str += "</" + _node_names.back() + ">";
		if (_indent) _str += '\n';
		_node_names.pop_back();
	}

	void XMLWriter::OnComponentID(const ComponentID id) {
		_next_id_str = std::to_string(id);
	}

	void XMLWriter::OnComponentID(const char* str, const size_t len) {
		_next_id_str = std::string(str, str + len);
	}


	void XMLWriter::AddNode(const std::string& name, const std::string& value, std::vector<std::pair<std::string, std::string>> attributes) {
		if (_indent) for (size_t i = 0; i < _node_names.size(); ++i) _str += '\t';

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

		if(_indent) _str += '\n';
	}

	const std::string& XMLWriter::GetXMLString() const {
		return _str;
	}

	void XMLWriter::OnUserPOD(const PodType type, const size_t bytes, const void* data) {
		// Store the binary data as Base64
		std::string value = Base64::Encode(reinterpret_cast<const uint8_t*>(data), bytes);

		// Add the value
		AddNode(GetNextNodeName("value"), value, { {"anvil_type", "pod"}, {"encoding", "Base64"}, {"pod_type", std::to_string(type) }
	});
	}

	void XMLWriter::OnNull() {
		AddNode(GetNextNodeName("value"), std::string(), { {"anvil_type", "null"} });
	}

	void XMLWriter::OnPrimitiveF64(const double value) {
		AddNode(GetNextNodeName("value"), std::to_string(value), { {"anvil_type", "float32"} });
	}

	void XMLWriter::OnPrimitiveString(const char* value, const size_t length) {
		AddNode(GetNextNodeName("value"), std::string(value, value + length), { {"anvil_type", "string"} });
	}

	void XMLWriter::OnPrimitiveBool(const bool value) {
		AddNode(GetNextNodeName("value"), std::string(value ? "true" : "false"), { {"anvil_type", "bool"} });
	}

	void XMLWriter::OnPrimitiveC8(const char value) {
		AddNode(GetNextNodeName("value"), std::string() + value, { {"anvil_type", "char"} });
	}

	void XMLWriter::OnPrimitiveU64(const uint64_t value) {
		AddNode(GetNextNodeName("value"), std::to_string(value), { {"anvil_type", "uint64"} });
	}

	void XMLWriter::OnPrimitiveS64(const int64_t value) {
		AddNode(GetNextNodeName("value"), std::to_string(value), { {"anvil_type", "int64"} });
	}

	void XMLWriter::OnPrimitiveF32(const float value) {
		AddNode(GetNextNodeName("value"), std::to_string(value), { {"anvil_type", "float32"} });
	}

	void XMLWriter::OnPrimitiveU8(const uint8_t value) {
		AddNode(GetNextNodeName("value"), std::to_string(value), { {"anvil_type", "uint8"} });
	}

	void XMLWriter::OnPrimitiveU16(const uint16_t value) {
		AddNode(GetNextNodeName("value"), std::to_string(value), { {"anvil_type", "uint16"} });
	}

	void XMLWriter::OnPrimitiveU32(const uint32_t value) {
		AddNode(GetNextNodeName("value"), std::to_string(value), { {"anvil_type", "uint32"} });
	}

	void XMLWriter::OnPrimitiveS8(const int8_t value) {
		AddNode(GetNextNodeName("value"), std::to_string(value), { {"anvil_type", "int8"} });
	}

	void XMLWriter::OnPrimitiveS16(const int16_t value) {
		AddNode(GetNextNodeName("value"), std::to_string(value), { {"anvil_type", "int16"} });
	}

	void XMLWriter::OnPrimitiveS32(const int32_t value) {
		AddNode(GetNextNodeName("value"), std::to_string(value), {{"anvil_type", "int32"}});
	}

#if ANVIL_XML_SUPPORT
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

	//static rapidxml::xml_node<>* FindChildNode(const rapidxml::xml_node<>& node, const std::string& name) {
	//	rapidxml::xml_node<>* tmp = node.first_node();
	//	while (tmp) {
	//		if (tmp->name() == name) return tmp;
	//		tmp = tmp->next_sibling();
	//	}
	//	return nullptr;
	//}

	template<class T>
	static T ReadPrimitive(const rapidxml::xml_node<>& node) {
		if ANVIL_CONSTEXPR_FN (std::is_same<bool, T>::value) {
			if (strcmp(node.value(), "true") == 0) return true;
			if (strcmp(node.value(), "false") == 0) return false;
		}

		std::stringstream ss(node.value());
		T tmp;
		ss >> tmp;
		return tmp;
	}

	static bool IsComponentID(const std::string& str) {
		for (char c : str) if (c < '0' || c > '9') return false;
		return true;
	}

	void ReadXML(const rapidxml::xml_node<>& node, Parser& parser) {
		rapidxml::xml_attribute<>* anvil_type = FindAttribute(node, "anvil_type");

		if (anvil_type) {
			const char* anvil_type_str = anvil_type->value();
			if (strcmp(anvil_type_str, "pod") == 0) {
				// Interpret as pod

				const rapidxml::xml_attribute<>* encoding_it = FindAttribute(node, "encoding");
				std::string encoding = "Hex";
				if (encoding_it) {
					encoding = static_cast<std::string>(encoding_it->value());
				}

				std::vector<uint8_t> data;
				if (encoding == "Base64") {
					data = Base64::Decode(node.value(), node.value_size());
				} else if (encoding == "Hex") {
					data = Hexadecimal::Decode(node.value(), node.value_size());
				} else {
					throw std::runtime_error("anvil::ReadXML : Unknown POD encoding");
				}

				parser.OnUserPOD(
					static_cast<PodType>(std::stoi(FindAttribute(node, "pod_type")->value())),
					data.size(),
					data.data()
				);
				return;

			} else if (strcmp(anvil_type_str, "array") == 0) {
				// Interpret as array
				parser.OnArrayBegin(CountChildNodes(node));
				rapidxml::xml_node<>* tmp = node.first_node();
				while (tmp) {
					ReadXML(*tmp, parser);
					tmp = tmp->next_sibling();
				}
				parser.OnArrayEnd();
				return;

			} else if (strcmp(anvil_type_str, "object") == 0) {
				// Interpret as object
				parser.OnObjectBegin(CountChildNodes(node));
				rapidxml::xml_node<>* tmp = node.first_node();
				while (tmp) {
					std::string id = tmp->name();
					if (IsComponentID(id)) {
						parser.OnComponentID(static_cast<ComponentID>(std::stoi(id)));
					} else {
						parser.OnComponentID(id);
					}
					ReadXML(*tmp, parser);
					tmp = tmp->next_sibling();
				}
				parser.OnObjectEnd();
				return;

			} else if (strcmp(anvil_type_str, "uint8") == 0) {
				parser.OnPrimitiveU8(ReadPrimitive<uint8_t>(node));
				return;

			} else if (strcmp(anvil_type_str, "uint16") == 0) {
				parser.OnPrimitiveU16(ReadPrimitive<uint16_t>(node));
				return;

			} else if (strcmp(anvil_type_str, "uint32") == 0) {
				parser.OnPrimitiveU32(ReadPrimitive<uint32_t>(node));
				return;

			} else if (strcmp(anvil_type_str, "uint64") == 0 || strcmp(anvil_type_str, "uint") == 0) {
				parser.OnPrimitiveU64(ReadPrimitive<uint64_t>(node));
				return;

			} else if (strcmp(anvil_type_str, "int8") == 0) {
				parser.OnPrimitiveS8(ReadPrimitive<int8_t>(node));
				return;

			} else if (strcmp(anvil_type_str, "int16") == 0) {
				parser.OnPrimitiveS16(ReadPrimitive<int16_t>(node));
				return;

			} else if (strcmp(anvil_type_str, "int32") == 0) {
				parser.OnPrimitiveS32(ReadPrimitive<int32_t>(node));
				return;

			} else if (strcmp(anvil_type_str, "int64") == 0 || strcmp(anvil_type_str, "int") == 0) {
				parser.OnPrimitiveS64(ReadPrimitive<int64_t>(node));
				return;

			} else if (strcmp(anvil_type_str, "float32") == 0) {
				parser.OnPrimitiveF32(ReadPrimitive<float>(node));
				return;

			} else if (strcmp(anvil_type_str, "float64") == 0 || strcmp(anvil_type_str, "float") == 0) {
				parser.OnPrimitiveF64(ReadPrimitive<double>(node));
				return;

			} else if (strcmp(anvil_type_str, "bool") == 0 || strcmp(anvil_type_str, "boolean") == 0) {
				parser.OnPrimitiveBool(ReadPrimitive<bool>(node));
				return;

			} else if (strcmp(anvil_type_str, "char") == 0) {
				parser.OnPrimitiveC8(ReadPrimitive<char>(node));
				return;

			} else if (strcmp(anvil_type_str, "null") == 0) {
				parser.OnNull();
				return;

			} else if (strcmp(anvil_type_str, "string") == 0) {
				parser.OnPrimitiveString(node.value(), node.value_size());
				return;

			} else {
				// Node not formatted as expected, but try to interpret it anyway
				size_t attribute_count = CountAttributes(node);
				size_t node_count = CountChildNodes(node);
				std::string value = node.value();

				if (attribute_count > 0 || node_count > 0) {
					if (!value.empty()) throw std::runtime_error("anvil::ReadXML : Failed to inteprpet XML data");

					parser.OnObjectBegin(attribute_count + node_count);

					{
						rapidxml::xml_attribute<>* tmp = node.first_attribute();
						while (tmp) {
							std::string id = tmp->name();
							if (IsComponentID(id)) {
								const size_t idint = std::stoi(id);
								ANVIL_RUNTIME_ASSERT(idint <= std::numeric_limits<ComponentID>::max(), "anvil::ReadXML : Component ID is too large");
								parser.OnComponentID(static_cast<ComponentID>(idint));
							} else {
								parser.OnComponentID(id.c_str(), id.size());
							}
							parser.OnPrimitiveString(tmp->value(), tmp->value_size());
							tmp = tmp->next_attribute();
						}
					}

					{
						rapidxml::xml_node<>* tmp = node.first_node();
						while (tmp) {
							std::string id = tmp->name();
							if (IsComponentID(id)) {
								const size_t idint = std::stoi(id);
								ANVIL_RUNTIME_ASSERT(idint <= std::numeric_limits<ComponentID>::max(), "anvil::ReadXML : Component ID is too large");
								parser.OnComponentID(static_cast<ComponentID>(idint));
							} else {
								parser.OnComponentID(id.c_str(), id.size());
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
	}

#endif

}}