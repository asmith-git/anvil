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

#include "anvil/serial/Value.hpp"

namespace anvil { namespace serial {
	// Value

	Value::Value() throw() :
		mType(VALUE_NULL)
	{}

	Value::Value(Type aType) throw() :
		mType(VALUE_NULL)
	{
		setType(aType);
	}

	Value::Value(const Boolean aValue) throw() :
		mBoolean(aValue),
		mType(VALUE_BOOLEAN)
	{}

	Value::Value(const Number aValue) throw() :
		mNumber(aValue),
		mType(VALUE_NUMBER)
	{}

	Value::Value(const Pointer aValue) throw() :
		mPointer(aValue),
		mType(VALUE_POINTER)
	{}

	Value::Value(const char* aValue) throw() :
		mPointer(new String(aValue)),
		mType(VALUE_STRING)
	{}

	Value::Value(const String& aValue) throw() :
		mPointer(new String(aValue)),
		mType(VALUE_STRING)
	{}

	Value::Value(const Array& aValue) throw() :
		mPointer(new Array(aValue)),
		mType(VALUE_ARRAY)
	{}

	Value::Value(const Object& aValue) throw() :
		mPointer(new Object(aValue)),
		mType(VALUE_OBJECT)
	{}

	Value::Value(Value&& aOther) throw() :
		mType(VALUE_NULL)
	{
		swap(aOther);
	}

	Value::Value(const Value& aOther) throw() :
		mType(VALUE_NULL)
	{
		operator=(aOther);
	}

	Value::~Value() throw() {
		setNull();
	}

	Value& Value::operator=(Value&& aOther) throw() {
		swap(aOther);
		return *this;
	}

	Value& Value::operator=(const Value& aOther) throw() {
		setNull();
		switch (aOther.mType) {
		case VALUE_BOOLEAN:
			mBoolean = aOther.mBoolean;
			mType = VALUE_BOOLEAN;
			break;
		case VALUE_NUMBER:
			mNumber = aOther.mNumber;
			mType = VALUE_NUMBER;
			break;
		case VALUE_POINTER:
			mPointer = aOther.mPointer;
			mType = VALUE_POINTER;
			break;
		case VALUE_STRING:
			mPointer = new String(*static_cast<const String*>(aOther.mPointer));
			mType = VALUE_STRING;
			break;
		case VALUE_ARRAY:
			mPointer = new Array(*static_cast<const Array*>(aOther.mPointer));
			mType = VALUE_ARRAY;
			break;
		case VALUE_OBJECT:
			mPointer = new Object(*static_cast<const Object*>(aOther.mPointer));
			mType = VALUE_OBJECT;
			break;
		default:
			mType = VALUE_NULL;
			break;
		}
		return *this;
	}

	bool Value::operator==(const Value& aOther) const throw() {
		if (mType != aOther.mType) return false;
		switch (aOther.mType) {
		case VALUE_BOOLEAN:
			return mBoolean == aOther.mBoolean;
		case VALUE_NUMBER:
			return mNumber == aOther.mNumber;
		case VALUE_POINTER:
			return mPointer == aOther.mPointer;
		case VALUE_STRING:
			return *static_cast<const String*>(mPointer) == *static_cast<const String*>(aOther.mPointer);
		case VALUE_ARRAY:
			return *static_cast<const Array*>(mPointer) == *static_cast<const Array*>(aOther.mPointer);
		case VALUE_OBJECT:
			return *static_cast<const Object*>(mPointer) == *static_cast<const Object*>(aOther.mPointer);
		default:
			return true;
		}
	}

	bool Value::operator!=(const Value& aOther) const throw() {
		return !operator==(aOther);
	}

	void Value::operator=(const Boolean aValue) throw() {
		setBoolean() = aValue;
	}

	void Value::operator=(const Number aValue) throw() {
		setNumber() = aValue;
	}

	void Value::operator=(const Pointer aValue) throw() {
		setPointer() = aValue;
	}

	void Value::operator=(const char* aValue) throw() {
		setString() = aValue;
	}

	void Value::operator=(const String& aValue) throw() {
		setString() = aValue;
	}

	void Value::operator=(const Array& aValue) throw() {
		setArray() = aValue;
	}

	void Value::operator=(const Object& aValue) throw() {
		setObject() = aValue;
	}

	Value::operator Boolean&() throw() {
		switch (mType) {
		case VALUE_BOOLEAN:
			return mBoolean;
		case VALUE_NUMBER:
			mType = VALUE_BOOLEAN;
			return mBoolean = mNumber >= 1.f;
			//! \todo Convert string to boolean
			//case VALUE_STRING:
			//	break;
		default:
			break;
		}
		throw std::runtime_error("Value cannot be converted to boolean");
	}

	Value::operator Number&() throw() {
		switch (mType) {
		case VALUE_BOOLEAN:
			mType = VALUE_NUMBER;
			return mNumber = mBoolean ? 1.0 : 0.0;
		case VALUE_NUMBER:
			return mNumber;
		//! \todo Convert string to number
		//case VALUE_STRING:
		//	break;
		default:
			break;
		}
		throw std::runtime_error("Value cannot be converted to number");
	}

	Value::operator Pointer&() throw() {
		if (mType != VALUE_POINTER) throw std::runtime_error("Value cannot be converted to array");
		throw std::runtime_error("Value cannot be converted to pointer");
	}

	Value::operator String&() {
		switch (mType) {
		case VALUE_BOOLEAN:
			mType = VALUE_STRING;
			return setString() = mBoolean ? "true" : "false";
		//! \todo Convert number to string
		//case VALUE_NUMBER:
		//	break;
		case VALUE_STRING:
			return *static_cast<String*>(mPointer);
		default:
			break;
		}
		throw std::runtime_error("Value cannot be converted to string");
	}

	Value::operator Array&() {
		if (mType != VALUE_ARRAY) throw std::runtime_error("Value cannot be converted to array");
		return *static_cast<Array*>(mPointer);
	}

	Value::operator Object&() {
		if (mType != VALUE_OBJECT) throw std::runtime_error("Value cannot be converted to object");
		return *static_cast<Object*>(mPointer);
	}


	Value::operator Boolean() const throw() {
		return const_cast<Value*>(this)->operator anvil::serial::Boolean&();
	}

	Value::operator Number() const throw() {
		return const_cast<Value*>(this)->operator anvil::serial::Number&();
	}

	Value::operator Pointer() const throw() {
		return const_cast<Value*>(this)->operator anvil::serial::Pointer&();
	}

	Value::operator const String&() const {
		return const_cast<Value*>(this)->operator anvil::serial::String&();
	}

	Value::operator const Array&() const {
		return const_cast<Value*>(this)->operator anvil::serial::Array&();
	}

	Value::operator const Object&() const {
		return const_cast<Value*>(this)->operator anvil::serial::Object&();
	}

	void Value::swap(Value& a_other) throw() {
		uint8_t buffer[sizeof(Value)];
		memcpy(buffer, this, sizeof(Value));
		memcpy(this, &a_other, sizeof(Value));
		memcpy(&a_other, buffer, sizeof(Value));
	}

	Type Value::getType() const throw() {
		return mType;
	}

	void Value::setType(const Type aType) throw() {
		setNull();
		switch (aType) {
		case VALUE_BOOLEAN:
			setBoolean();
			break;
		case VALUE_NUMBER:
			setNumber();
			break;
		case VALUE_POINTER:
			setPointer();
			break;
		case VALUE_STRING:
			setString();
			break;
		case VALUE_ARRAY:
			setArray();
			break;
		case VALUE_OBJECT:
			setObject();
			break;
		default:
			break;
		}
	}

	void Value::setNull() throw() {
		switch (mType) {
		case VALUE_STRING:
			delete static_cast<const String*>(mPointer);
			break;
		case VALUE_ARRAY:
			delete static_cast<const Array*>(mPointer);
			break;
		case VALUE_OBJECT:
			delete static_cast<const Object*>(mPointer);
			break;
		default:
			break;
		}
		mType = VALUE_NULL;
	}

	Boolean& Value::setBoolean() throw() {
		setNull();
		mType = VALUE_BOOLEAN;
		return mBoolean;
	}

	Number& Value::setNumber() throw() {
		setNull();
		mType = VALUE_NUMBER;
		return mNumber;
	}

	Pointer& Value::setPointer() throw() {
		setNull();
		mType = VALUE_POINTER;
		return mPointer;
	}

	String& Value::setString() throw() {
		if (mType != VALUE_STRING) {
			setNull();
			mPointer = new String();
			mType = VALUE_STRING;
		}
		return *static_cast<String*>(mPointer);
	}

	Array& Value::setArray() throw() {
		if (mType != VALUE_ARRAY) {
			setNull();
			mPointer = new Array();
			mType = VALUE_ARRAY;
		}
		return *static_cast<Array*>(mPointer);
	}

	Object& Value::setObject() throw() {
		if (mType != VALUE_OBJECT) {
			setNull();
			mPointer = new Object();
			mType = VALUE_OBJECT;
		}
		return *static_cast<Object*>(mPointer);
	}

}}