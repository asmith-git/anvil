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

	// PrimitiveValue

	bool PrimitiveValue::operator==(const PrimitiveValue& other) const {
		return type == other.type ? 
			memcmp(&u64, &other.u64, g_type_sizes[type]) == 0 : 
			operator double() == other.operator double();
	}

	bool PrimitiveValue::operator!=(const PrimitiveValue& other) const {
		return ! operator==(other);
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

	PrimitiveValue::operator uint64_t() const {
		switch (type) {
		case TYPE_C8:
			if (c8 >= '0' && c8 <= '9') return static_cast<uint64_t>(c8 - '0');
			throw std::runtime_error("PrimitiveValue::operator uint64_t : Character cannot be converted to number");
		case TYPE_U8:
			return u8;
		case TYPE_U16:
			return u16;
		case TYPE_U32:
			return u32;
		case TYPE_S8:
			return s8 < 0 ? 0 : static_cast<uint64_t>(s8);
		case TYPE_S16:
			return s16 < 0 ? 0 : static_cast<uint64_t>(s16);
		case TYPE_S32:
			return s32 < 0 ? 0 : static_cast<uint64_t>(s32);
		case TYPE_S64:
			return s64 < 0 ? 0 : static_cast<uint64_t>(s64);
		case TYPE_F32:
			return f32 < 0.f ? 0 : static_cast<uint64_t>(std::round(f32));
		case TYPE_F64:
			return f64 < 0.0 ? 0 : static_cast<uint64_t>(std::round(f64));
		case TYPE_BOOL:
			return b ? 1 : 0;
		default:
			return static_cast<uint64_t>(std::round(operator double()));
		}
	}

	PrimitiveValue::operator int64_t() const {
		switch (type) {
		case TYPE_C8:
			if (c8 >= '0' && c8 <= '9') return static_cast<int64_t>(c8 - '0');
			throw std::runtime_error("PrimitiveValue::operator int64_t : Value cannot be converted to number");
		case TYPE_U8:
			return u8;
		case TYPE_U16:
			return u16;
		case TYPE_U32:
			return u32;
		case TYPE_U64:
			return u64;
		case TYPE_S8:
			return s8 < 0 ? 0 : static_cast<uint64_t>(s8);
		case TYPE_S16:
			return s16 < 0 ? 0 : static_cast<uint64_t>(s16);
		case TYPE_S32:
			return s32 < 0 ? 0 : static_cast<uint64_t>(s32);
		case TYPE_F32:
			return f32 < 0.f ? 0 : static_cast<uint64_t>(std::round(f32));
		case TYPE_F64:
			return f64 < 0.0 ? 0 : static_cast<uint64_t>(std::round(f64));
		case TYPE_BOOL:
			return b ? 1 : 0;
		default:
			return static_cast<uint64_t>(std::round(operator double()));
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

	PrimitiveValue::operator double() const {
		switch (type) {
		case TYPE_NULL:
			return 0.f;
		case TYPE_C8:
			if(c8 >= '0' && c8 <= '9') return static_cast<double>(c8 - '0');
			break;
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
		}

		throw std::runtime_error("PrimitiveValue::operator double : Type cannot be converted to double");
	}

	void PrimitiveValue::Optimise() {
		// Don't change characters
		if (type == TYPE_C8) return;

		// Boolean values are already optimal
		if (type == TYPE_BOOL) return;

		double val = operator double();

		// If the value is a boolean
		if (val == 1.0) {
			u8 = 1;
			type = TYPE_U8;
		
		// If the value is a boolean
		} else if (val == 0.0) {
			u8 = 0;
			type = TYPE_U8;

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
		case TYPE_POD:
			{
				SetPod() = other.GetPod();
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
		case TYPE_POD:
			delete static_cast<Pod*>(_primitive.ptr);
			break;
		}
		_primitive.u64 = 0u;
		_primitive.type = TYPE_NULL;
	}

	std::string& Value::SetString(const char* value) {
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

		return *static_cast<std::string*>(_primitive.ptr);
	}

	Value::Pod& Value::SetPod() {
		if (_primitive.type == TYPE_POD) {
			static_cast<Pod*>(_primitive.ptr)->data.clear();
		} else {
			SetNull();
			_primitive.ptr = new Pod();
			_primitive.type = TYPE_POD;
		}

		return *static_cast<Pod*>(_primitive.ptr);
	}

	Value::Array& Value::SetArray() {
		if (_primitive.type == TYPE_ARRAY && !_primitive_array_type == TYPE_NULL) {
			static_cast<Array*>(_primitive.ptr)->clear();
		} else {
			SetNull();
			_primitive.ptr = new Array();
			_primitive.type = TYPE_ARRAY;
			_primitive_array_type = TYPE_NULL;
		}

		return *static_cast<Array*>(_primitive.ptr);
	}

	Value::PrimitiveArray& Value::SetPrimitiveArray(Type type) {
		if (_primitive.type == TYPE_ARRAY && !_primitive_array_type != TYPE_NULL) {
			static_cast<PrimitiveArray*>(_primitive.ptr)->clear();
		} else {
			SetNull();
			_primitive.ptr = new PrimitiveArray();
			_primitive.type = TYPE_ARRAY;
			_primitive_array_type = type;
		}
		return *static_cast<PrimitiveArray*>(_primitive.ptr);
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
			if ANVIL_CONSTEXPR_FN(std::is_same<T, char>::value) v.SetC8(static_cast<char>(src_ptr[i]));
			else if ANVIL_CONSTEXPR_FN (std::is_same<T, uint8_t>::value) v.SetU8(static_cast<uint8_t>(src_ptr[i]));
			else if ANVIL_CONSTEXPR_FN(std::is_same<T, uint16_t>::value) v.SetU16(static_cast<uint16_t>(src_ptr[i]));
			else if ANVIL_CONSTEXPR_FN(std::is_same<T, uint32_t>::value) v.SetU32(static_cast<uint32_t>(src_ptr[i]));
			else if ANVIL_CONSTEXPR_FN(std::is_same<T, uint64_t>::value) v.SetU64(static_cast<uint64_t>(src_ptr[i]));
			else if ANVIL_CONSTEXPR_FN(std::is_same<T, int8_t>::value) v.SetS8(static_cast<int8_t>(src_ptr[i]));
			else if ANVIL_CONSTEXPR_FN(std::is_same<T, int16_t>::value) v.SetS16(static_cast<int16_t>(src_ptr[i]));
			else if ANVIL_CONSTEXPR_FN(std::is_same<T, int32_t>::value) v.SetS32(static_cast<int32_t>(src_ptr[i]));
			else if ANVIL_CONSTEXPR_FN(std::is_same<T, int64_t>::value) v.SetS64(static_cast<int64_t>(src_ptr[i]));
			else if ANVIL_CONSTEXPR_FN(std::is_same<T, half>::value) v.SetF16(static_cast<half>(src_ptr[i]));
			else if ANVIL_CONSTEXPR_FN(std::is_same<T, float>::value) v.SetS32(static_cast<int32_t>(src_ptr[i]));
			else if ANVIL_CONSTEXPR_FN(std::is_same<T, double>::value) v.SetS64(static_cast<int64_t>(src_ptr[i]));
			else if ANVIL_CONSTEXPR_FN(std::is_same<T, bool>::value) v.SetBool(static_cast<bool>(src_ptr[i]));
			dst.push_back(std::move(v));
		}
	}

	Value* Value::AddValue(const PrimitiveValue& value) {
		if (_primitive.type != TYPE_ARRAY) throw std::runtime_error("Value::AddValue : Value is not an array");

		if (_primitive_array_type == TYPE_NULL) {
			static_cast<Array*>(_primitive.ptr)->push_back(std::move(Value(value)));
			return &static_cast<Array*>(_primitive.ptr)->back();

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
			default:
				ConvertFromPrimitveArray();
				return AddValue(value);
				break;
			}

			return nullptr;
		}
	}

	void Value::ConvertFromPrimitveArray() {
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
	}

	Value* Value::AddValue(Value&& value) {
		// Handle primitive data types in a way that is optimised for them
		if (value.IsPrimitive()) {
			return AddValue(value._primitive);

		// Complex values
		} else {
			if (_primitive.type != TYPE_ARRAY) throw std::runtime_error("Value::AddValue : Value is not an array");
			if (_primitive_array_type != TYPE_NULL) ConvertFromPrimitveArray();
			static_cast<Array*>(_primitive.ptr)->push_back(std::move(value));
			return &static_cast<Array*>(_primitive.ptr)->back();
		}
	}

	Value::Object& Value::SetObject() {
		// If the value is already an object then clear it
		if (_primitive.type == TYPE_OBJECT) {
			static_cast<Object*>(_primitive.ptr)->clear();

		// Otherwise allocate a new object
		} else {
			SetNull();
			_primitive.ptr = new Object();
			_primitive.type = TYPE_OBJECT;
		}

		return *static_cast<Object*>(_primitive.ptr);
	}

	std::string Value::GetString() const {
		if (_primitive.type == TYPE_STRING) {
			return *static_cast<std::string*>(_primitive.ptr);
		} else {
			char buffer[64];
			if (_primitive.type == TYPE_C8) {
				buffer[0u] = GetC8();
				buffer[1u] = '\0';

			} else if (IsUnsigned()) {
				sprintf(buffer, "%u", GetU32());

			} else if (IsSigned()) {
				sprintf(buffer, "%i", GetS32());

			} else {
				sprintf(buffer, "%f", GetF64());
			}

			return buffer;
		}
	}

	std::string& Value::GetString() {
		if (_primitive.type != TYPE_STRING) SetString() = std::move(const_cast<Value*>(this)->GetString());
		return *static_cast<std::string*>(_primitive.ptr);
	}

	const Value::Pod& Value::GetPod() const {
		if (_primitive.type != TYPE_POD) throw std::runtime_error("Value::GetPod : Value is not a POD");
		return *static_cast<const Pod*>(_primitive.ptr);
	}

	Value::Pod& Value::GetPod() {
		if (_primitive.type != TYPE_POD) throw std::runtime_error("Value::GetPod : Value is not a POD");
		return *static_cast<Pod*>(_primitive.ptr);
	}

	Value* Value::GetValue2(const size_t index) throw() {
		switch (_primitive.type) {
		case TYPE_ARRAY:
			{
				if (_primitive_array_type == TYPE_NULL) {
					Array& myArray = *static_cast<Array*>(_primitive.ptr);
					if (index >= myArray.size()) return nullptr;
					return &myArray[index];
				} else {
					PrimitiveArray& myArray = *static_cast<PrimitiveArray*>(_primitive.ptr);
					if (index >= GetSize()) return nullptr;

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

					return &g_tmp_value;
				}
			}
		case TYPE_OBJECT:
			return GetValue2(std::to_string(index));
		default:
			return nullptr;
		}
	}

	Value* Value::GetValue2(const std::string& index) throw() {
		switch (_primitive.type) {
		case TYPE_OBJECT:
			{
				Object& myObject = *static_cast<Object*>(_primitive.ptr);
				auto i = myObject.find(index);
				if (i == myObject.end()) return nullptr;
				return &i->second;
			}
			break;
		default:
			return nullptr;
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
					--j;
				}
				return static_cast<ComponentID>(std::stoi(i->first));
			}
			break;
		default:
			throw std::runtime_error("Value::GetValue : Value is not an array or object");
		}
	}

	std::string Value::GetComponentIDString(const uint32_t index) const {
		switch (_primitive.type) {
		case TYPE_OBJECT:
			{
				Object& myObject = *static_cast<Object*>(_primitive.ptr);
				if (index >= myObject.size()) throw std::runtime_error("Value::GetValue : Index out of bounds");
				auto i = myObject.begin();
				uint32_t j = index;
				while (j != 0u) {
					++i;
					--j;
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

	void Value::Resize(const size_t size) {
		if(_primitive.type != TYPE_ARRAY) throw std::runtime_error("Value::Resize : Value is not an array");

		if (_primitive_array_type == TYPE_NULL) {
			static_cast<Array*>(_primitive.ptr)->resize(size);
		} else {
			static_cast<PrimitiveArray*>(_primitive.ptr)->resize(size * GetSizeOfPrimitiveType(_primitive_array_type));
		}
	}

	void Value::Reserve(const size_t size) {
		if(_primitive.type != TYPE_ARRAY) throw std::runtime_error("Value::Reserve : Value is not an array");

		if (_primitive_array_type == TYPE_NULL) {
			static_cast<Array*>(_primitive.ptr)->reserve(size);
		} else {
			static_cast<PrimitiveArray*>(_primitive.ptr)->reserve(size * GetSizeOfPrimitiveType(_primitive_array_type));
		}
	}

}}