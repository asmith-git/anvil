//Copyright 2017 Adam G. Smith
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

#ifndef ANVIL_SERIAL_PARSER_INI_HPP
#define ANVIL_SERIAL_PARSER_INI_HPP

#include "anvil/serial/Parser.hpp"

namespace anvil { namespace serial {

	class ParserIni : public Parser {
	private:
		char mComment;
		char mHierarchy;
		std::vector<String> mNameStack;

		void writeNull(std::ostream&, const String&);
		void writeBoolean(std::ostream&, const String&, const Boolean);
		void writeNumber(std::ostream&, const String&, const Number);
		void writePointer(std::ostream&, const String&, const Pointer);
		void writeString(std::ostream&, const String&, const String&);
		void writeArray(std::ostream&, const String&, const Array&);
		void writeObject(std::ostream&, const String&, const Object&);
		void writeValue(std::ostream&, const String&, const Value&);
	public:
		ParserIni() throw();
		ParserIni& setCommentDelimiter(char) throw();
		ParserIni& setHierarchyDelimiter(char) throw();

		// Inherited from Parser
		Value read(std::istream&) override;
		void write(std::ostream&, const Value&) override;
	};

}}

#endif