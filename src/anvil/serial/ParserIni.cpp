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

#include "anvil/serial/ParserIni.hpp"

namespace anvil { namespace serial {

	const std::string g_ini_default = "__ini_default";

	// ParserIni

	ParserIni::ParserIni() throw() :
		mComment('#'),
		mHierarchy('.')
	{}

	ParserIni& ParserIni::setCommentDelimiter(char aChar) throw() {
		mComment = aChar;
		return *this;
	}

	ParserIni& ParserIni::setHierarchyDelimiter(char aChar) throw() {
		mHierarchy = aChar;
		return *this;
	}

	Value ParserIni::read(std::istream&) {

	}

	void ParserIni::writeNull(std::ostream& aStream, const String& aName) {
		aStream << aName << "=null" << std::endl;
	};

	void ParserIni::writeBoolean(std::ostream& aStream, const String& aName, const Boolean aValue) {
		aStream << aName << "=" << aValue << std::endl;
	};

	void ParserIni::writeNumber(std::ostream& aStream, const String& aName, const Number aValue) {
		aStream << aName << "=" << aValue << std::endl;
	};

	void ParserIni::writePointer(std::ostream& aStream, const String& aName, const Pointer aValue) {
		aStream << aName << "=" << aValue << std::endl;
	};

	void ParserIni::writeString(std::ostream& aStream, const String& aName, const String& aValue) {
		aStream << aName << "=" << aValue << std::endl;
	};

	void ParserIni::writeArray(std::ostream& aStream, const String& aName, const Array& aValue) {
		aStream << '[';
		for (const String& i : mNameStack) {
			aStream << i << mHierarchy;
		}
		aStream << aName;
		mNameStack.push_back(aName);
		aStream << ']' << std::endl;
		const size_t s = aValue.size();
		for (size_t i = 0; i < s; ++i) {
			writeValue(aStream, std::to_string(i), aValue[i]);
		}
		mNameStack.pop_back();
	};

	void ParserIni::writeObject(std::ostream& aStream, const String& aName, const Object& aValue) {
		aStream << '[';
		for (const String& i : mNameStack) {
			aStream << i << mHierarchy;
		}
		aStream << aName;
		mNameStack.push_back(aName);
		aStream << ']' << std::endl;
		for (const auto& i : aValue) {
			writeValue(aStream, i.first, i.second);
		}
		mNameStack.pop_back();
	};

	void ParserIni::writeValue(std::ostream& aStream, const String& aName, const Value& aValue) {
		switch (aValue.getType()) {
		case VALUE_NULL:
			writeNull(aStream, aName);
			break;
		case VALUE_BOOLEAN:
			writeBoolean(aStream, aName, aValue);
			break;
		case VALUE_NUMBER:
			writeNumber(aStream, aName, aValue);
			break;
		case VALUE_POINTER:
			writePointer(aStream, aName, aValue);
			break;
		case VALUE_STRING:
			writeString(aStream, aName, aValue);
			break;
		case VALUE_ARRAY:
			writeArray(aStream, aName, aValue);
			break;
		case VALUE_OBJECT:
			writeObject(aStream, aName, aValue);
			break;
		default:
			throw std::runtime_error("Type not recognised by ini parser");
		}
	};

	void ParserIni::write(std::ostream& aStream, const Value& aValue) {
		const Object& root = aValue;

		// Write root properties
		{
			auto i = root.find(g_ini_default);
		}

		// Write remaining values
		for (const auto& i : root) {
			if (i.first == g_ini_default) continue;
			writeValue(aStream, i.first, i.second);
		}
	}

}}