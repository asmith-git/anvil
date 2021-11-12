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

#ifndef ANVIL_SERIAL_VALUE_HPP
#define ANVIL_SERIAL_VALUE_HPP

#include <cstdint>
#include <vector>
#include <map>
#include <string>
#include "anvil/core/Keywords.hpp"

namespace anvil { namespace serial {

	typedef bool Boolean;
	typedef double Number;
	typedef void* Pointer;

	enum Type : int8_t {
		VALUE_NULL,
		VALUE_BOOLEAN,
		VALUE_NUMBER,
		VALUE_POINTER,
		VALUE_STRING,
		VALUE_ARRAY,
		VALUE_OBJECT
	};

	class Value {
	public:
		typedef std::string String;
		typedef std::vector<Value> Array;
		typedef std::map<std::string,Value> Object;
	private:
		union {
			void* mPointer;
			bool mBoolean;
			double mNumber;
		};
		Type mType;
	public:
		Value() throw();
		Value(Type) throw();
		Value(const Boolean) throw();
		Value(const Number) throw();
		Value(const Pointer) throw();
		Value(const char*) throw();
		Value(const String&) throw();
		Value(const Array&) throw();
		Value(const Object&) throw();
		Value(Value&&) throw();
		Value(const Value&) throw();
		~Value() throw();

		Value& operator=(Value&&) throw();
		Value& operator=(const Value&) throw();

		bool operator==(const Value&) const throw();
		bool operator!=(const Value&) const throw();

		void operator=(const Boolean) throw();
		void operator=(const Number) throw();
		void operator=(const Pointer) throw();
		void operator=(const char*) throw();
		void operator=(const String&) throw();
		void operator=(const Array&) throw();
		void operator=(const Object&) throw();

		operator Boolean&() throw();
		operator Number&() throw();
		operator Pointer&() throw();
		operator String&();
		operator Array&();
		operator Object&();

		operator Boolean() const throw();
		operator Number() const throw();
		operator Pointer() const throw();
		operator const String&() const;
		operator const Array&() const;
		operator const Object&() const;

		void swap(Value&) throw();

		Type getType() const throw();

		void setType(const Type) throw();
		void setNull() throw();
		Boolean& setBoolean() throw();
		Number& setNumber() throw();
		Pointer& setPointer() throw();
		String& setString() throw();
		Array& setArray() throw();
		Object& setObject() throw();
	};

	typedef Value::String String;
	typedef Value::Array Array;
	typedef Value::Object Object;
}}

#endif