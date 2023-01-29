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

#ifndef ANVIL_LUTILS_BYTEPIPE_XML_HPP
#define ANVIL_LUTILS_BYTEPIPE_XML_HPP

#include <vector>
#include <string>
#include "anvil/core/LibDetect.hpp"

#if ANVIL_XML_SUPPORT
#include <rapidxml.hpp>
#endif

#include "anvil/byte-pipe/BytePipeReader.hpp"

namespace anvil { namespace BytePipe {

#if ANVIL_XML_SUPPORT

	void ReadXML(const rapidxml::xml_node<>& node, Parser& parser);

#endif

	/*!
		\author Adam Smith
		\date March 2023
		\brief Converts a BytePipe serialisation into a XML string
	*/
	class XMLWriter final : public Parser {
	private:
		std::vector<std::string> _node_names;
		std::string _str;
		std::string _next_id_str;
		void AddNode(const std::string& name, const std::string& value, std::vector<std::pair<std::string,std::string>> attribute);

		std::string GetNextNodeName(const char* default_name);
	public:
		XMLWriter();
		virtual ~XMLWriter();

		const std::string& GetXMLString() const;

		// Inherited from Parser

		void OnPipeOpen() final;
		void OnPipeClose() final;
		void OnArrayBegin(const uint32_t size) final;
		void OnArrayEnd() final;
		void OnObjectBegin(const uint32_t component_count) final;
		void OnObjectEnd() final;
		void OnComponentID(const ComponentID id)  final;
		void OnComponentID(const char* str, const uint32_t size)  final;
		void OnUserPOD(const uint32_t type, const uint32_t bytes, const void* data) final;
		void OnNull() final;
		void OnPrimitiveF64(const double value) final;
		void OnPrimitiveString(const char* value, const uint32_t length) final;
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
	};
}}

#endif
