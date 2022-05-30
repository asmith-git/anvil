//Copyright 2019 Adam G. Smith
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

#include "anvil/byte-pipe/BytePipeObjects.hpp"

namespace anvil { namespace BytePipe {

	static ANVIL_CONSTEXPR_VAR const uint8_t g_type_sizes[] = {
		0u,	// TYPE_NULL,
		1u,	// TYPE_C8,
		1u,	// TYPE_U8,
		2u,	// TYPE_U16,
		4u,	// TYPE_U32,
		8u,	// TYPE_U64,
		1u,	// TYPE_S8,
		2u,	// TYPE_S16,
		4u,	// TYPE_S32,
		8u,	// TYPE_S64,
		2u,	// TYPE_F16,
		4u,	// TYPE_F32,
		8u,	// TYPE_F64,
		0u,	// TYPE_STRING,
		0u,	// TYPE_ARRAY,
		0u,	// TYPE_OBJECT,
		1u,	// TYPE_BOOL
	};

	template<class T>
	static inline uint64_t GetRaw(const T value) {
		union {
			uint64_t raw;
			T val;
		};
		if ANVIL_CONSTEXPR_VAR(sizeof(T) < sizeof(uint64_t)) raw = 0u;
		val = value;
		return raw;
	}

	template<>
	static inline uint64_t GetRaw< uint64_t>(const uint64_t value) {
		return value;
	}

	// PrimitiveValue

	bool PrimitiveValue::operator==(const PrimitiveValue& other) const {
		return type == other.type ? 
			memcmp(&u64, &other.u64, g_type_sizes[type]) == 0 : 
			operator double() == other.operator double();
	}

	bool PrimitiveValue::operator!=(const PrimitiveValue& other) const {
		return ! operator==(other);
	}

	PrimitiveValue::PrimitiveValue(Type type, uint64_t raw) :
		u64(raw),
		type(type)
	{}

	PrimitiveValue::PrimitiveValue() :
		PrimitiveValue(TYPE_NULL, 0u)
	{}

	PrimitiveValue::PrimitiveValue(bool value) :
		PrimitiveValue(GetTypeID<decltype(value)>(), GetRaw<decltype(value)>(value))
	{}

	PrimitiveValue::PrimitiveValue(char value) :
		PrimitiveValue(GetTypeID<decltype(value)>(), GetRaw<decltype(value)>(value))
	{}

	PrimitiveValue::PrimitiveValue(uint8_t value) :
		PrimitiveValue(GetTypeID<decltype(value)>(), GetRaw<decltype(value)>(value))
	{}

	PrimitiveValue::PrimitiveValue(uint16_t value) :
		PrimitiveValue(GetTypeID<decltype(value)>(), GetRaw<decltype(value)>(value))
	{}

	PrimitiveValue::PrimitiveValue(uint32_t value) :
		PrimitiveValue(GetTypeID<decltype(value)>(), GetRaw<decltype(value)>(value))
	{}

	PrimitiveValue::PrimitiveValue(uint64_t value) :
		PrimitiveValue(GetTypeID<decltype(value)>(), GetRaw<decltype(value)>(value))
	{}

	PrimitiveValue::PrimitiveValue(int8_t value) :
		PrimitiveValue(GetTypeID<decltype(value)>(), GetRaw<decltype(value)>(value))
	{}

	PrimitiveValue::PrimitiveValue(int16_t value) :
		PrimitiveValue(GetTypeID<decltype(value)>(), GetRaw<decltype(value)>(value))
	{}

	PrimitiveValue::PrimitiveValue(int32_t value) :
		PrimitiveValue(GetTypeID<decltype(value)>(), GetRaw<decltype(value)>(value))
	{}

	PrimitiveValue::PrimitiveValue(int64_t value) :
		PrimitiveValue(GetTypeID<decltype(value)>(), GetRaw<decltype(value)>(value))
	{}

	PrimitiveValue::PrimitiveValue(half value) :
		PrimitiveValue(GetTypeID<decltype(value)>(), GetRaw<decltype(value)>(value))
	{}

	PrimitiveValue::PrimitiveValue(float value) :
		PrimitiveValue(GetTypeID<decltype(value)>(), GetRaw<decltype(value)>(value))
	{}

	PrimitiveValue::PrimitiveValue(double value) :
		PrimitiveValue(GetTypeID<decltype(value)>(), GetRaw<decltype(value)>(value))
	{}

	PrimitiveValue::operator bool() const {
		return operator double() > 0.0;
	}

	PrimitiveValue::operator char() const {
		if (type == TYPE_C8) {
			return c8;
		} else {
			intptr_t tmp = operator intptr_t();
			if (tmp > 9) tmp = 9;
			else if (tmp < 0) tmp = 0;
			return static_cast<char>('0' + tmp);
		}
	}

	PrimitiveValue::operator uint8_t() const {
		if (type == TYPE_U8) {
			return u8;
		} else {
			const uintptr_t tmp = operator uintptr_t();
			return tmp > UINT8_MAX ? UINT8_MAX : static_cast<uint8_t>(tmp);
		}
	}

	PrimitiveValue::operator uint16_t() const {
		if (type == TYPE_U16) {
			return u16;
		} else {
			const uintptr_t tmp = operator uintptr_t();
			return tmp > UINT16_MAX ? UINT16_MAX : static_cast<uint16_t>(tmp);
		}
	}

	PrimitiveValue::operator uint32_t() const {
		if (type == TYPE_U32) {
			return u32;
		} else {
			const uint64_t tmp = operator uint64_t();
			return tmp > UINT32_MAX ? UINT32_MAX : static_cast<uint32_t>(tmp);
		}
	}

	PrimitiveValue::operator uint64_t() const {
		if (type == TYPE_U64) {
			return u64;
		} else {
			const double tmp = operator double();
			return static_cast<uint64_t>(std::round(tmp));
		}
	}

	PrimitiveValue::operator int8_t() const {
		if (type == TYPE_S8) {
			return s8;
		} else {
			const intptr_t tmp = operator intptr_t();
			return tmp > INT8_MAX ? INT8_MAX : tmp < INT8_MIN ? INT8_MIN : static_cast<int8_t>(tmp);
		}
	}

	PrimitiveValue::operator int16_t() const {
		if (type == TYPE_S16) {
			return s16;
		} else {
			const intptr_t tmp = operator intptr_t();
			return tmp > INT16_MAX ? INT16_MAX : tmp < INT16_MIN ? INT16_MIN : static_cast<int16_t>(tmp);
		}
	}

	PrimitiveValue::operator int32_t() const {
		if (type == TYPE_S32) {
			return s32;
		} else {
			const int64_t tmp = operator int64_t();
			return tmp > INT32_MAX ? INT32_MAX : tmp < INT32_MIN ? INT32_MIN : static_cast<int32_t>(tmp);
		}
	}

	PrimitiveValue::operator int64_t() const {
		if (type == TYPE_S64) {
			return s64;
		} else {
			const double tmp = operator double();
			return static_cast<uint64_t>(std::round(tmp));
		}
	}

	PrimitiveValue::operator half() const {
		if (type == TYPE_F16) {
			return f16;
		} else {
			//! \bug f16 conversion is not implented
			throw std::runtime_error("PrimitiveValue::operator half : 16-bit floating point is not implemented");
		}
	}

	PrimitiveValue::operator float() const {
		if (type == TYPE_F32) {
			return f32;
		} else {
			return static_cast<float>(operator double());
		}
	}

	PrimitiveValue::operator double() const {
		switch (type) {
		case TYPE_NULL:
			return 0.f;
		case TYPE_C8:
			if(c8 >= '0' && c8 <= '9') return static_cast<double>(c8 - '0');
			goto ON_ERROR;
		case TYPE_U8:
			return static_cast<double>(u8);
		case TYPE_U16:
			return static_cast<double>(u16);
		case TYPE_U32:
			return static_cast<double>(u32);
		case TYPE_U64:
			return static_cast<double>(u64);
		case TYPE_S8:
			return static_cast<double>(s8);
		case TYPE_S16:
			return static_cast<double>(s16);
		case TYPE_S32:
			return static_cast<double>(s32);
		case TYPE_S64:
			return static_cast<double>(s64);
		case TYPE_F16:
			return static_cast<double>(f16);
		case TYPE_F32:
			return static_cast<double>(f32);
		case TYPE_F64:
			return static_cast<double>(f64);
		case TYPE_BOOL:
			return b ? 1.0 : 0.0;
		default:
ON_ERROR:
			throw std::runtime_error("PrimitiveValue::operator double : Type cannot be converted to double");
		}
	}

	void PrimitiveValue::Optimise() {
		// Don't change characters
		if (type == TYPE_C8) return;

		// Boolean values are already optimal
		if (type == TYPE_BOOL) return;

		double val = operator double();

		// If the value is a boolean
		if (val == 1.0) {
			b = true;
			type = TYPE_BOOL;
		
		// If the value is a boolean
		} else if (val == 0.0) {
			b = false;
			type = TYPE_BOOL;

		} else if (std::round(val) == val) {
			// If value is unsigned
			if (val >= 0.0) {
				if (val <= static_cast<double>(UINT8_MAX)) {
					u8 = static_cast<uint8_t>(val);
					type = TYPE_U8;
				} else if (val > static_cast<double>(UINT16_MAX)) {
					u16 = static_cast<uint16_t>(val);
					type = TYPE_U16;
				} else if (val > static_cast<double>(UINT32_MAX)) {
					u32 = static_cast<uint32_t>(val);
					type = TYPE_U32;
				} else if (val > static_cast<double>(UINT64_MAX)) {
					u64 = static_cast<uint64_t>(val);
					type = TYPE_U64;
				} else {
					goto FLOATING_POINT;
				}

			// The value is signed
			} else {
				if (val > static_cast<double>(INT8_MIN)) {
					s8 = static_cast<int8_t>(val);
					type = TYPE_S8;
				} else if (val > static_cast<double>(INT16_MIN)) {
					s16 = static_cast<int16_t>(val);
					type = TYPE_S16;
				} else if (val > static_cast<double>(INT32_MIN)) {
					s32 = static_cast<int32_t>(val);
					type = TYPE_S32;
				} else if (val > static_cast<double>(INT64_MIN)) {
					s64 = static_cast<int64_t>(val);
					type = TYPE_S64;
				} else {
					goto FLOATING_POINT;
				}
			}

		// The value is floating point
		} else {
FLOATING_POINT:
			// If the value can be stored as 32-bit floating point without losing precision
			float tmp = static_cast<float>(val);
			if (static_cast<double>(tmp) == val) {
				f32 = tmp;
				type = TYPE_F32;
			} else {
				f64 = val;
				type = TYPE_F64;
			}
		}
	}

	// Value

	Value::Value() :
		_primitive_array_type(TYPE_NULL)
	{
		_primitive.u64 = 0u;
		_primitive.type = TYPE_NULL;
	}

	Value::~Value() {
		SetNull();
	}


	Value::Value(Value&& other) :
		Value()
	{
		Swap(other);
	}

	Value::Value(const Value& other) :
		Value() 
	{
		*this = other;
	}

	Value::Value(bool value) :
		_primitive(value),
		_primitive_array_type(TYPE_NULL)
	{}

	Value::Value(char value) :
		_primitive(value),
		_primitive_array_type(TYPE_NULL)
	{}

	Value::Value(uint8_t value) :
		_primitive(value),
		_primitive_array_type(TYPE_NULL)
	{}

	Value::Value(uint16_t value) :
		_primitive(value),
		_primitive_array_type(TYPE_NULL)
	{}

	Value::Value(uint32_t value) :
		_primitive(value),
		_primitive_array_type(TYPE_NULL)
	{}

	Value::Value(uint64_t value) :
		_primitive(value),
		_primitive_array_type(TYPE_NULL)
	{}

	Value::Value(int8_t value) :
		_primitive(value),
		_primitive_array_type(TYPE_NULL)
	{}

	Value::Value(int16_t value) :
		_primitive(value),
		_primitive_array_type(TYPE_NULL)
	{}

	Value::Value(int32_t value) :
		_primitive(value),
		_primitive_array_type(TYPE_NULL)
	{}

	Value::Value(int64_t value) :
		_primitive(value),
		_primitive_array_type(TYPE_NULL)
	{}

	Value::Value(half value) :
		_primitive(value),
		_primitive_array_type(TYPE_NULL)
	{}

	Value::Value(float value) :
		_primitive(value),
		_primitive_array_type(TYPE_NULL)
	{}

	Value::Value(double value) :
		_primitive(value),
		_primitive_array_type(TYPE_NULL)
	{}

	Value::Value(const PrimitiveValue& value) :
		_primitive(value),
		_primitive_array_type(TYPE_NULL)
	{}


	Value& Value::operator=(Value&& other) {
		Swap(other);
		return *this;
	}

	Value& Value::operator=(const Value& other) {
		switch (other._primitive.type) {
		case TYPE_STRING:
			SetString(static_cast<std::string*>(other._primitive.ptr)->c_str());
			break;
		case TYPE_ARRAY:
			if(other._primitive_array_type == TYPE_NULL) {
				SetArray();
				Array& myArray = *static_cast<Array*>(_primitive.ptr);
				const Array& otherArray = *static_cast<Array*>(other._primitive.ptr);
				myArray = otherArray;
			} else {
				SetPrimitiveArray(other._primitive_array_type);
				PrimitiveArray& myArray = *static_cast<PrimitiveArray*>(_primitive.ptr);
				const PrimitiveArray& otherArray = *static_cast<PrimitiveArray*>(other._primitive.ptr);
				myArray = otherArray;
			}
			break;
		case TYPE_OBJECT:
			{
				SetObject();
				Object& myObject = *static_cast<Object*>(_primitive.ptr);
				const Object& otherObject = *static_cast<Object*>(other._primitive.ptr);
				myObject = otherObject;
			}
		break;
		default:
			SetNull();
			_primitive = other._primitive;
			break;
		}

		return *this;
	}

	void Value::Swap(Value& other) {
		std::swap(_primitive, other._primitive);
		std::swap(_primitive_array_type, other._primitive_array_type);
	}

	Type Value::GetType() const {
		return _primitive.type;
	}

	void Value::SetNull() {
		switch (_primitive.type) {
		case TYPE_STRING:
			delete static_cast<std::string*>(_primitive.ptr);
			break;
		case TYPE_ARRAY:
			if (_primitive_array_type == TYPE_NULL) {
				delete static_cast<Array*>(_primitive.ptr);
			} else {
				delete static_cast<PrimitiveArray*>(_primitive.ptr);
			}
			break;
		case TYPE_OBJECT:
			delete static_cast<Object*>(_primitive.ptr);
			break;
		}
		_primitive.u64 = 0u;
		_primitive.type = TYPE_NULL;
	}

	void Value::SetBool(const bool value) {
		SetNull();
		_primitive.b = value;
		_primitive.type = TYPE_BOOL;
	}

	void Value::SetC8(const char value) {
		SetNull();
		_primitive.c8 = value;
		_primitive.type = TYPE_C8;
	}

	void Value::SetU8(const uint8_t value) {
		SetNull();
		_primitive.u8 = value;
		_primitive.type = TYPE_U8;
	}

	void Value::SetU16(const uint16_t value) {
		SetNull();
		_primitive.u16 = value;
		_primitive.type = TYPE_U16;
	}

	void Value::SetU32(const uint32_t value) {
		SetNull();
		_primitive.u32 = value;
		_primitive.type = TYPE_U32;
	}

	void Value::SetU64(const uint64_t value) {
		SetNull();
		_primitive.u64 = value;
		_primitive.type = TYPE_U64;
	}

	void Value::SetS8(const int8_t value) {
		SetNull();
		_primitive.s8 = value;
		_primitive.type = TYPE_S8;
	}

	void Value::SetS16(const int16_t value) {
		SetNull();
		_primitive.s16 = value;
		_primitive.type = TYPE_S16;
	}

	void Value::SetS32(const int32_t value) {
		SetNull();
		_primitive.s32 = value;
		_primitive.type = TYPE_S32;
	}

	void Value::SetS64(const int64_t value) {
		SetNull();
		_primitive.s64 = value;
		_primitive.type = TYPE_S64;
	}

	void Value::SetF16(const half value) {
		SetNull();
		_primitive.f16 = value;
		_primitive.type = TYPE_F16;
	}

	void Value::SetF32(const float value) {
		SetNull();
		_primitive.f32 = value;
		_primitive.type = TYPE_F32;
	}

	void Value::SetF64(const double value) {
		SetNull();
		_primitive.f64 = value;
		_primitive.type = TYPE_F64;
	}

	void Value::SetString(const char* value) {
		if (_primitive.type == TYPE_STRING) {
			if (value == nullptr) {
				static_cast<std::string*>(_primitive.ptr)->clear();
			} else {
				*static_cast<std::string*>(_primitive.ptr) = value;
			}
		} else {
			SetNull();
			if (value == nullptr) {
				_primitive.ptr = new std::string();
			} else{
				_primitive.ptr = new std::string(value);
			}
			_primitive.type = TYPE_STRING;
		}
	}

	void Value::SetArray() {
		if (_primitive.type == TYPE_ARRAY && !_primitive_array_type == TYPE_NULL) {
			static_cast<Array*>(_primitive.ptr)->clear();
		} else {
			SetNull();
			_primitive.ptr = new Array();
			_primitive.type = TYPE_ARRAY;
			_primitive_array_type = TYPE_NULL;
		}
	}

	void Value::SetPrimitiveArray(Type type) {
		if (_primitive.type == TYPE_ARRAY && !_primitive_array_type != TYPE_NULL) {
			static_cast<PrimitiveArray*>(_primitive.ptr)->clear();
		} else {
			SetNull();
			_primitive.ptr = new PrimitiveArray();
			_primitive.type = TYPE_ARRAY;
			_primitive_array_type = type;
		}
	}

	template<class T>
	static void AddValueTemplate(std::vector<uint8_t>& dst, const T value) {
		const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&value);
		for(size_t i = 0u; i < sizeof(T); ++i) dst.push_back(bytes[i]);
	}

	template<class T>
	static void ConvertToValueVector(std::vector<Value>& dst, const std::vector<uint8_t>& src) {
		size_t s = src.size() / sizeof(T);
		const T* src_ptr = reinterpret_cast<const T*>(src.data());
		for (size_t i = 0u; i < s; ++i) {
			Value v;
			if ANVIL_CONSTEXPR_FN(std::is_same<T, char>::value) v.SetC8(src_ptr[i]);
			else if ANVIL_CONSTEXPR_FN (std::is_same<T, uint8_t>::value) v.SetU8(src_ptr[i]);
			else if ANVIL_CONSTEXPR_FN(std::is_same<T, uint16_t>::value) v.SetU16(src_ptr[i]);
			else if ANVIL_CONSTEXPR_FN(std::is_same<T, uint32_t>::value) v.SetU32(src_ptr[i]);
			else if ANVIL_CONSTEXPR_FN(std::is_same<T, uint64_t>::value) v.SetU64(src_ptr[i]);
			else if ANVIL_CONSTEXPR_FN(std::is_same<T, int8_t>::value) v.SetS8(src_ptr[i]);
			else if ANVIL_CONSTEXPR_FN(std::is_same<T, int16_t>::value) v.SetS16(src_ptr[i]);
			else if ANVIL_CONSTEXPR_FN(std::is_same<T, int32_t>::value) v.SetS32(src_ptr[i]);
			else if ANVIL_CONSTEXPR_FN(std::is_same<T, int64_t>::value) v.SetS64(src_ptr[i]);
			else if ANVIL_CONSTEXPR_FN(std::is_same<T, half>::value) v.SetF16(src_ptr[i]);
			else if ANVIL_CONSTEXPR_FN(std::is_same<T, float>::value) v.SetS32(src_ptr[i]);
			else if ANVIL_CONSTEXPR_FN(std::is_same<T, double>::value) v.SetS64(src_ptr[i]);
			else if ANVIL_CONSTEXPR_FN(std::is_same<T, bool>::value) v.SetBool(src_ptr[i]);
			dst.push_back(std::move(v));
		}
	}

	void Value::AddValue(const PrimitiveValue& value) {
		if (_primitive.type != TYPE_ARRAY) throw std::runtime_error("Value::AddValue : Value is not an array");

		if (_primitive_array_type == TYPE_NULL) {
			static_cast<Array*>(_primitive.ptr)->push_back(std::move(Value(value)));

		} else {
			switch (_primitive_array_type) {
			case TYPE_C8:
				AddValueTemplate<char>(*static_cast<PrimitiveArray*>(_primitive.ptr), value);
				break;
			case TYPE_U8:
				AddValueTemplate<uint8_t>(*static_cast<PrimitiveArray*>(_primitive.ptr), value);
				break;
			case TYPE_U16:
				AddValueTemplate<uint16_t>(*static_cast<PrimitiveArray*>(_primitive.ptr), value);
				break;
			case TYPE_U32:
				AddValueTemplate<uint32_t>(*static_cast<PrimitiveArray*>(_primitive.ptr), value);
				break;
			case TYPE_U64:
				AddValueTemplate<uint64_t>(*static_cast<PrimitiveArray*>(_primitive.ptr), value);
				break;
			case TYPE_S8:
				AddValueTemplate<int8_t>(*static_cast<PrimitiveArray*>(_primitive.ptr), value);
				break;
			case TYPE_S16:
				AddValueTemplate<int16_t>(*static_cast<PrimitiveArray*>(_primitive.ptr), value);
				break;
			case TYPE_S32:
				AddValueTemplate<int32_t>(*static_cast<PrimitiveArray*>(_primitive.ptr), value);
				break;
			case TYPE_S64:
				AddValueTemplate<int64_t>(*static_cast<PrimitiveArray*>(_primitive.ptr), value);
				break;
			case TYPE_F16:
				AddValueTemplate<half>(*static_cast<PrimitiveArray*>(_primitive.ptr), value);
				break;
			case TYPE_F32:
				AddValueTemplate<float>(*static_cast<PrimitiveArray*>(_primitive.ptr), value);
				break;
			case TYPE_F64:
				AddValueTemplate<double>(*static_cast<PrimitiveArray*>(_primitive.ptr), value);
				break;
			case TYPE_BOOL:
				AddValueTemplate<bool>(*static_cast<PrimitiveArray*>(_primitive.ptr), value);
				break;
			}
		}
	}

	void Value::AddValue(Value&& value) {
		// Handle primitive data types in a way that is optimised for them
		if (value.IsPrimitiveType()) {
			AddValue(value._primitive);

		// Complex values
		} else {

			if (_primitive.type != TYPE_ARRAY) throw std::runtime_error("Value::AddValue : Value is not an array");

			if (_primitive_array_type == TYPE_NULL) {
ADD_VALUE_NORMAL:
				static_cast<Array*>(_primitive.ptr)->push_back(std::move(value));

			} else {
				// Convert to a regular array
				PrimitiveArray tmp = std::move(*static_cast<PrimitiveArray*>(_primitive.ptr));
				SetArray();

				switch (_primitive_array_type) {
				case TYPE_C8:
					ConvertToValueVector<char>(*static_cast<Array*>(_primitive.ptr), tmp);
					break;
				case TYPE_U8:
					ConvertToValueVector<uint8_t>(*static_cast<Array*>(_primitive.ptr), tmp);
					break;
				case TYPE_U16:
					ConvertToValueVector<uint16_t>(*static_cast<Array*>(_primitive.ptr), tmp);
					break;
				case TYPE_U32:
					ConvertToValueVector<uint32_t>(*static_cast<Array*>(_primitive.ptr), tmp);
					break;
				case TYPE_U64:
					ConvertToValueVector<uint64_t>(*static_cast<Array*>(_primitive.ptr), tmp);
					break;
				case TYPE_S8:
					ConvertToValueVector<int8_t>(*static_cast<Array*>(_primitive.ptr), tmp);
					break;
				case TYPE_S16:
					ConvertToValueVector<int16_t>(*static_cast<Array*>(_primitive.ptr), tmp);
					break;
				case TYPE_S32:
					ConvertToValueVector<int32_t>(*static_cast<Array*>(_primitive.ptr), tmp);
					break;
				case TYPE_S64:
					ConvertToValueVector<int64_t>(*static_cast<Array*>(_primitive.ptr), tmp);
					break;
				case TYPE_F16:
					ConvertToValueVector<half>(*static_cast<Array*>(_primitive.ptr), tmp);
					break;
				case TYPE_F32:
					ConvertToValueVector<float>(*static_cast<Array*>(_primitive.ptr), tmp);
					break;
				case TYPE_F64:
					ConvertToValueVector<double>(*static_cast<Array*>(_primitive.ptr), tmp);
					break;
				case TYPE_BOOL:
					ConvertToValueVector<bool>(*static_cast<Array*>(_primitive.ptr), tmp);
					break;
				}

				// Add the value
				goto ADD_VALUE_NORMAL;
			}
		}
	}

	void Value::SetObject() {
		if (_primitive.type == TYPE_OBJECT) {
			static_cast<Object*>(_primitive.ptr)->clear();
		} else {
			SetNull();
			_primitive.ptr = new Object();
			_primitive.type = TYPE_OBJECT;
		}
	}

	void Value::AddValue(const ComponentID id, Value&& value) {
		if (_primitive.type != TYPE_OBJECT) throw std::runtime_error("Value::AddValue : Value is not an object");
		static_cast<Object*>(_primitive.ptr)->emplace(id, std::move(value));
	}

	bool Value::GetBool() const {
		if (IsPrimitiveType()) return _primitive;
		throw std::runtime_error("Value::GetBool : Value cannot be converted to boolean");
	}

	char Value::GetC8() const {
		if (IsPrimitiveType()) return _primitive;
		throw std::runtime_error("Value::GetC8 : Value cannot be converted to character");
	}

	uint8_t Value::GetU8() const {
		if (IsPrimitiveType()) return _primitive;
		throw std::runtime_error("Value::GetU8 : Value cannot be converted to 8-bit unsigned integer");
	}

	uint16_t Value::GetU16() const {
		if (IsPrimitiveType()) return _primitive;
		throw std::runtime_error("Value::GetU16 : Value cannot be converted to 16-bit unsigned integer");
	}

	uint32_t Value::GetU32() const {
		if (IsPrimitiveType()) return _primitive;
		throw std::runtime_error("Value::GetU32 : Value cannot be converted to 32-bit unsigned integer");
	}

	uint64_t Value::GetU64() const {
		if (IsPrimitiveType()) return _primitive;
		throw std::runtime_error("Value::GetU64 : Value cannot be converted to 64-bit unsigned integer");
	}

	int8_t Value::GetS8() const {
		if (IsPrimitiveType()) return _primitive;
		throw std::runtime_error("Value::GetS8 : Value cannot be converted to 8-bit signed integer");
	}

	int16_t Value::GetS16() const {
		if (IsPrimitiveType()) return _primitive;
		throw std::runtime_error("Value::GetS16 : Value cannot be converted to 16-bit signed integer");
	}

	int32_t Value::GetS32() const {
		if (IsPrimitiveType()) return _primitive;
		throw std::runtime_error("Value::GetS32 : Value cannot be converted to 32-bit signed integer");
	}

	int64_t Value::GetS64() const {
		if (IsPrimitiveType()) return _primitive;
		throw std::runtime_error("Value::GetS64 : Value cannot be converted to 64-bit signed integer");
	}

	half Value::GetF16() const {
		if (IsPrimitiveType()) return _primitive;
		throw std::runtime_error("Value::GetF16 : Value cannot be converted to 16-bit floating point");
	}

	float Value::GetF32() const {
		if (IsPrimitiveType()) return _primitive;
		throw std::runtime_error("Value::GetF32 : Value cannot be converted to 32-bit floating point");
	}

	double Value::GetF64() const {
		if (IsPrimitiveType()) return _primitive;
		throw std::runtime_error("Value::GetF64 : Value cannot be converted to 64-bit floating point");
	}

	const char* Value::GetString() {
		if (_primitive.type != TYPE_STRING) {
			char buffer[64];
			if (_primitive.type == TYPE_C8) {
				buffer[0u] = GetC8();
				buffer[1u] = '\0';
			} else {
				const double f64 = GetF64();
				sprintf(buffer, "%f", f64);
			}
			SetString(buffer);
		}
		return static_cast<std::string*>(_primitive.ptr)->c_str();
	}

	Value& Value::GetValue(const uint32_t index) {
		switch (_primitive.type) {
		case TYPE_ARRAY:
			{
				if (_primitive_array_type == TYPE_NULL) {
					Array& myArray = *static_cast<Array*>(_primitive.ptr);
					if (index >= myArray.size()) throw std::runtime_error("Value::GetValue : Index out of bounds");
					return myArray[index];
				} else {
					PrimitiveArray& myArray = *static_cast<PrimitiveArray*>(_primitive.ptr);
					if (index >= GetSize()) throw std::runtime_error("Value::GetValue : Index out of bounds");

					thread_local Value g_tmp_value;

					switch (_primitive_array_type) {
					case TYPE_C8:
						g_tmp_value.SetC8(reinterpret_cast<const char*>(myArray.data())[index]);
						break;
					case TYPE_U8:
						g_tmp_value.SetU8(reinterpret_cast<const uint8_t*>(myArray.data())[index]);
						break;
					case TYPE_U16:
						g_tmp_value.SetU16(reinterpret_cast<const uint16_t*>(myArray.data())[index]);
						break;
					case TYPE_U32:
						g_tmp_value.SetU32(reinterpret_cast<const uint32_t*>(myArray.data())[index]);
						break;
					case TYPE_U64:
						g_tmp_value.SetU64(reinterpret_cast<const uint64_t*>(myArray.data())[index]);
						break;
					case TYPE_S8:
						g_tmp_value.SetS8(reinterpret_cast<const int8_t*>(myArray.data())[index]);
						break;
					case TYPE_S16:
						g_tmp_value.SetS16(reinterpret_cast<const int16_t*>(myArray.data())[index]);
						break;
					case TYPE_S32:
						g_tmp_value.SetS32(reinterpret_cast<const int32_t*>(myArray.data())[index]);
						break;
					case TYPE_S64:
						g_tmp_value.SetS64(reinterpret_cast<const int64_t*>(myArray.data())[index]);
						break;
					case TYPE_F16:
						g_tmp_value.SetF16(reinterpret_cast<const half*>(myArray.data())[index]);
						break;
					case TYPE_F32:
						g_tmp_value.SetF32(reinterpret_cast<const float*>(myArray.data())[index]);
						break;
					case TYPE_F64:
						g_tmp_value.SetF64(reinterpret_cast<const double*>(myArray.data())[index]);
						break;
					case TYPE_BOOL:
						g_tmp_value.SetBool(reinterpret_cast<const bool*>(myArray.data())[index]);
						break;
					}

					return g_tmp_value;
				}
			}
		case TYPE_OBJECT:
			{
				Object& myObject = *static_cast<Object*>(_primitive.ptr);
				auto i = myObject.find(index);
				if (i == myObject.end()) throw std::runtime_error("Value::GetValue : No member object with component ID");
				return i->second;
			}
			break;
		default:
			throw std::runtime_error("Value::GetValue : Value is not an array or object");
		}
	}


	void* Value::GetPrimitiveArray() {
		return _primitive.type == TYPE_ARRAY ? (
				_primitive_array_type == TYPE_NULL ? 
					static_cast<void*>(static_cast<Array*>(_primitive.ptr)->data()) :
					static_cast<void*>(static_cast<PrimitiveArray*>(_primitive.ptr)->data())
			) : nullptr;
	}

	ComponentID Value::GetComponentID(const uint32_t index) const {
		switch (_primitive.type) {
		case TYPE_OBJECT:
			{
				Object& myObject = *static_cast<Object*>(_primitive.ptr);
				if (index >= myObject.size()) throw std::runtime_error("Value::GetValue : Index out of bounds");
				auto i = myObject.begin();
				uint32_t j = index;
				while (j != 0u) {
					++i;
				}
				return i->first;
			}
			break;
		default:
			throw std::runtime_error("Value::GetValue : Value is not an array or object");
		}
	}

	PrimitiveValue Value::GetPrimitiveValue() const {
		switch (_primitive.type) {
		case TYPE_STRING:
		case TYPE_ARRAY:
		case TYPE_OBJECT:
			throw std::runtime_error("Value::GetPrimitiveValue : Value is not a numerical type");
			break;
		default:
			return _primitive;
		}
	}

	size_t Value::GetSize() const {
		return _primitive.type == TYPE_ARRAY ? (
			_primitive_array_type == TYPE_NULL ? 
				static_cast<Array*>(_primitive.ptr)->size() : 
				(static_cast<PrimitiveArray*>(_primitive.ptr)->size() / GetSizeOfPrimitiveType(_primitive_array_type))
			) :
			_primitive.type == TYPE_OBJECT ? static_cast<Object*>(_primitive.ptr)->size() :
			0u;
	}

	void Value::Optimise() {
		switch (_primitive.type) {
		case TYPE_STRING:
			{
				std::string& str = *static_cast<std::string*>(_primitive.ptr);
				const size_t size = str.size();

				// If the string is empty then it can be null value
				if (size == 0u) {
					SetNull();

				// If the string is only one character then it can be primitive character
				} else if (size == 1u) {
					SetC8(str[0u]);
				}
			}
			break;
		case TYPE_ARRAY:
			{
				// Optimise the child values
				if (_primitive_array_type == TYPE_NULL) {
					Array& myArray = *static_cast<Array*>(_primitive.ptr);
					for (Value& i : myArray) i.Optimise();
				}

				//! \todo If all of the values are primitives try to make them the same type
			}
			break;
		case TYPE_OBJECT:
			{
			// Optimise the child values
				Object& myObject = *static_cast<Object*>(_primitive.ptr);
				for (auto& i : myObject) i.second.Optimise();
			}
			break;
		default:
			_primitive.Optimise();
			break;
		}
	}

}}