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

	static uint32_t GetLargness(const Type a) {
		static ANVIL_CONSTEXPR_VAR const uint8_t g_table[] = {
			0,//TYPE_NULL
			10,//TYPE_C8
			1,//TYPE_U8
			2,//TYPE_U16
			3,//TYPE_U32
			4,//TYPE_U64
			2,//TYPE_S8
			3,//TYPE_S16
			4,//TYPE_S32
			5,//TYPE_S64
			6,//TYPE_F16
			7,//TYPE_F32
			8,//TYPE_F64
			9,//TYPE_STRING
			10,//TYPE_ARRAY
			11,//TYPE_OBJECT
			12,//TYPE_BOOL
			13,//TYPE_POD
		};
		
		return g_table[a];
	}

	static bool OptimiseString(const std::string& str, PrimitiveValue& v) {
		const size_t s = str.size();

		if (s == 0u) {
			v.type == TYPE_NULL;
			return true;
		}

		if (s >= 20) return false; // Unlikely to be a number that we can parse without losing data

		// Check if number
		bool decimal_place_found = false;
		size_t i = 0u;
		if (str[0u] == '-') ++i;

		for (i; i < s; ++i) {
			char c = str[i];
			if (c < '0' || c > '0') {
				if (c == '.') {
					if (decimal_place_found) return false;
					decimal_place_found = true;
				} else {
					return false;
				}
			}
		}

		//!\todo Support scientific notation

		v = (std::stod(str));
		v.Optimise();
		return true;
	}

	static bool IsPrimitiveConvertable(const Type type) {
		if (type == TYPE_F16) return 0; //!< \bug F16 conversion not implemented
		return (type >= TYPE_U8 && type <= TYPE_F64) || type == TYPE_BOOL;
	}

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
	
	void PrimitiveValue::Optimise() {
		Type prev_type = TYPE_NULL;
		while (prev_type != type) {
			prev_type = type;

			switch (type) {
			case TYPE_U8:
				if (u8 == 0u) {
					b = false;
					type = TYPE_BOOL;
				} else if (u8 == 1u) {
					b = true;
					type = TYPE_BOOL;
				}
				break;
			case TYPE_U16:
				if (u16 <= UINT8_MAX) type = TYPE_U8;
				break;
			case TYPE_U32:
				if (u32 <= UINT16_MAX) type = TYPE_U16;
				break;
			case TYPE_U64:
				if (u64 <= UINT32_MAX) type = TYPE_U32;
				break;
			case TYPE_S8:
				if (s8 >= 0) type = TYPE_U8;
				break;
			case TYPE_S16:
				if (s16 >= 0) type = TYPE_U16;
				else if (s16 >= INT8_MIN && s16 <= INT8_MAX) type = TYPE_S8;
				break;
			case TYPE_S32:
				if (s32 >= 0) type = TYPE_U32;
				else if (s32 >= INT16_MIN && s32 <= INT16_MAX) type = TYPE_S16;
				break;
			case TYPE_S64:
				if (s64 >= 0) type = TYPE_U64;
				else if (s64 >= INT32_MIN && s64 <= INT32_MAX) type = TYPE_S32;
				break;
			case TYPE_F32:
				{
					int64_t tmp = static_cast<int64_t>(f32);
					if (static_cast<float>(tmp) == f32) {
						s64 = tmp;
						type = TYPE_S64;
					}
				}
				break;
			case TYPE_F64:
				{
					int64_t tmp = static_cast<int64_t>(f64);
					if (static_cast<double>(tmp) == f64) {
						s64 = tmp;
						type = TYPE_S64;
					}
				}
				break;
			}
		}
	}

	void PrimitiveValue::ConvertTo(Type t) {
		if (t == type) return;
		if (!IsPrimitiveConvertable(type)) throw std::runtime_error("PrimativeValue : Current type is not convertable");
		if (!IsPrimitiveConvertable(t)) throw std::runtime_error("PrimativeValue : Targer type is not convertable");

		const double tmp = static_cast<double>(*this);

		switch (t) {
		case TYPE_U8:
			u8 = static_cast<uint8_t>(*this);
			break;
		case TYPE_U16:
			u16 = static_cast<uint16_t>(*this);
			break;
		case TYPE_U32:
			u32 = static_cast<uint32_t>(*this);
			break;
		case TYPE_U64:
			u64 = static_cast<uint64_t>(*this);
			break;
		case TYPE_S8:
			s8 = static_cast<int8_t>(*this);
			break;
		case TYPE_S16:
			s16 = static_cast<int16_t>(*this);
			break;
		case TYPE_S32:
			s32 = static_cast<int32_t>(*this);
			break;
		case TYPE_S64:
			s64 = static_cast<int64_t>(*this);
			break;
		case TYPE_F16:
			f16 = static_cast<half>(*this);
			break;
		case TYPE_F32:
			f32 = static_cast<float>(*this);
			break;
		case TYPE_BOOL:
			b = static_cast<bool>(*this);
			break;
		}
		type = t;
	}

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

	// Value

	Value::Value() :
		_primitive(),
		_primitive_array_type(TYPE_NULL)
	{
		_primitive.u64 = 0u;
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

	Value::Value(const Type type) :
		Value()
	{
		switch (type) {
		case TYPE_C8:
			SetC8();
			break;
		case TYPE_U8:
			SetU8();
			break;
		case TYPE_U16:
			SetU16();
			break;
		case TYPE_U32:
			SetU32();
			break;
		case TYPE_U64:
			SetU64();
			break;
		case TYPE_S8:
			SetS8();
			break;
		case TYPE_S16:
			SetS16();
			break;
		case TYPE_S32:
			SetS32();
			break;
		case TYPE_S64:
			SetS64();
			break;
		case TYPE_F16:
			SetF16();
			break;
		case TYPE_F32:
			SetF32();
			break;
		case TYPE_F64:
			SetF64();
			break;
		case TYPE_STRING:
			SetString();
			break;
		case TYPE_ARRAY:
			SetArray();
			break;
		case TYPE_OBJECT:
			SetObject();
			break;
		case TYPE_BOOL:
			SetBool();
			break;
		case TYPE_POD:
			SetPod();
			break;
		}
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

	Value::Value(const char* string) :
		Value()
	{
		SetString() = string;
	}

	Value::Value(const std::string& string) :
		Value()
	{
		SetString() = string;
	}

	Value::Value(Pod&& value) :
		Value()
	{
		SetPod() = std::move(value);
	}

	Value::Value(const Pod& value) :
		Value()
	{
		SetPod() = value;
	}

#if ANVIL_OPENCV_SUPPORT
	Value::Value(const cv::Mat& img) :
		Value(Pod::CreatePODFromCVMat(img))
	{}
#endif

	Value::~Value() {
		SetNull();
	}

	Value& Value::operator=(const Value& other) {
		switch (other._primitive.type) {
		case TYPE_STRING:
			SetString(static_cast<std::string*>(other._primitive.ptr)->c_str());
			break;
		case TYPE_ARRAY:
			if(other._primitive_array_type == TYPE_NULL) {
				Array& myArray = SetArray();
				const Array& otherArray = *other.GetArray();
				myArray = otherArray;
			} else {
				PrimitiveArray& myArray = SetPrimitiveArray(other._primitive_array_type);
				const PrimitiveArray& otherArray = *other.GetPrimitiveArray();
				myArray = otherArray;
			}
			break;
		case TYPE_OBJECT:
			{
				Object& myObject = SetObject();
				const Object& otherObject = *other.GetObject();
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

	Value::Array& Value::GetArray() {
		if (_primitive.type == TYPE_ARRAY) {
			if (_primitive_array_type == TYPE_NULL) {
				return *static_cast<Array*>(_primitive.ptr);
			} else {
				return ConvertFromPrimitveArray();
			}
		} else {
			return SetArray();
		}
	}

	const Value::Array* Value::GetArray() const {
		if (_primitive.type == TYPE_ARRAY) {
			if (_primitive_array_type == TYPE_NULL) {
				return static_cast<const Array*>(_primitive.ptr);
			}
		}
		return nullptr;
	}

	Value::PrimitiveArray* Value::GetPrimitiveArray() {
		if (_primitive.type == TYPE_ARRAY) {
			if (_primitive_array_type != TYPE_NULL) {
				return static_cast<PrimitiveArray*>(_primitive.ptr);
			}
		}
		return nullptr;
	}

	const Value::PrimitiveArray* Value::GetPrimitiveArray() const {
		if (_primitive.type == TYPE_ARRAY) {
			if (_primitive_array_type != TYPE_NULL) {
				return static_cast<const PrimitiveArray*>(_primitive.ptr);
			}
		}
		return nullptr;
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
			// Try to add primative type
			try {
				PrimitiveValue v = value;
				v.ConvertTo(_primitive_array_type);

				size_t bytes = GetSizeOfPrimitiveType(_primitive_array_type);
				PrimitiveArray& primitive_array = *static_cast<PrimitiveArray*>(_primitive.ptr);

				size_t prev_size = primitive_array.size();
				primitive_array.resize(prev_size + bytes);
				memcpy(primitive_array.data() + prev_size, &v.u8, bytes);

				return nullptr;
			} catch (...) {}

			// Conver to value array
			ConvertFromPrimitveArray();
			return AddValue(value);
		}
	}

	Value::PrimitiveArray* Value::ConvertToPrimitveArray() {
		Array& myArray = *static_cast<Array*>(_primitive.ptr);

		const size_t s = myArray.size();
		if (s == 0u) return nullptr;

		// Try to optimise any string values
		for (Value& v : myArray) if (v.GetType() == TYPE_STRING) {
			v.Optimise();

			// If still a string then it can't be made into a primative
			if (v.GetType() == TYPE_STRING) return nullptr;
		}

		Type target_type = myArray[0u].GetType();
		try {

			// Check if all values are the same type
			Type largest_type = target_type;
			uint32_t score = GetLargness(target_type);
			bool same_type = true;

			for (size_t i = 1u; i < s; ++i) {
				const Type t2 = myArray[i].GetType();

				if (t2 != target_type) {
					same_type = false;
					uint32_t score2 = GetLargness(t2);
					if (score2 > score) {
						score = score2;
						target_type = t2;
					}
				}
			}


			// Convert to be the same type
			if (!same_type) {
				target_type = largest_type;

				for (Value& v : myArray) {
					v.ConvertTo(target_type);
				}
			}

		} catch (...) {
			return nullptr;
		}

		// Convert to primative array
		Value tmp;
		PrimitiveArray& primitive_array = tmp.SetPrimitiveArray(target_type);
		const size_t bytes = GetSizeOfPrimitiveType(target_type);
		primitive_array.resize(s * bytes);
		for (size_t i = 0; i < s; ++i) {
			memcpy(primitive_array.data() + i * bytes, &myArray[0]._primitive.u8, bytes);
		}
	}

	Value::Array& Value::ConvertFromPrimitveArray() {
		PrimitiveArray tmp = std::move(*static_cast<PrimitiveArray*>(_primitive.ptr));
		Value::Array& new_array = SetArray();

		switch (_primitive_array_type) {
		case TYPE_C8:
			ConvertToValueVector<char>(new_array, tmp);
			break;
		case TYPE_U8:
			ConvertToValueVector<uint8_t>(new_array, tmp);
			break;
		case TYPE_U16:
			ConvertToValueVector<uint16_t>(new_array, tmp);
			break;
		case TYPE_U32:
			ConvertToValueVector<uint32_t>(new_array, tmp);
			break;
		case TYPE_U64:
			ConvertToValueVector<uint64_t>(new_array, tmp);
			break;
		case TYPE_S8:
			ConvertToValueVector<int8_t>(new_array, tmp);
			break;
		case TYPE_S16:
			ConvertToValueVector<int16_t>(new_array, tmp);
			break;
		case TYPE_S32:
			ConvertToValueVector<int32_t>(new_array, tmp);
			break;
		case TYPE_S64:
			ConvertToValueVector<int64_t>(new_array, tmp);
			break;
		case TYPE_F16:
			ConvertToValueVector<half>(new_array, tmp);
			break;
		case TYPE_F32:
			ConvertToValueVector<float>(new_array, tmp);
			break;
		case TYPE_F64:
			ConvertToValueVector<double>(new_array, tmp);
			break;
		case TYPE_BOOL:
			ConvertToValueVector<bool>(new_array, tmp);
			break;
		}

		return new_array;
	}

	Value* Value::AddValue(Value&& value) {
		// Try to turn a string into a value
		if (value.GetType() == TYPE_STRING) value.Optimise();

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

	Value::Object& Value::GetObject() {
		if (_primitive.type != TYPE_OBJECT) return SetObject();
		return *static_cast<Object*>(_primitive.ptr);
	}

	const Value::Object* Value::GetObject() const {
		if (_primitive.type != TYPE_OBJECT) return nullptr;
		return static_cast<const Object*>(_primitive.ptr);
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

	std::string Value::GetComponentIDString(const size_t index) const {
		switch (_primitive.type) {
		case TYPE_OBJECT:
			{
				Object& myObject = *static_cast<Object*>(_primitive.ptr);
				if (index >= myObject.size()) throw std::runtime_error("Value::GetValue : Index out of bounds");
				auto i = myObject.begin();
				size_t j = index;
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
		if (_primitive.type <= TYPE_F64) {
			return _primitive;
		} else if(_primitive.type == TYPE_STRING) {
			PrimitiveValue tmp;
			if (OptimiseString(*static_cast<std::string*>(_primitive.ptr), tmp)) {
				return tmp;
			}
		}
		throw std::runtime_error("Value::GetPrimitiveValue : Value is not a numerical type");
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
			try {
				PrimitiveValue tmp;
				if (OptimiseString(*static_cast<std::string*>(_primitive.ptr), tmp)) {
					SetNull();
					_primitive = tmp;
				}
			} catch (...) {}
			break;
		case TYPE_ARRAY:
			{

				// Optimise the child values
				if (_primitive_array_type == TYPE_NULL) {
					ConvertToPrimitveArray();
				}

				//if (_primitive_array_type != TYPE_NULL) {
					//! \todo Optimise primative array
				//}
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

	void Value::ConvertTo(Type type) {
		if (type == GetType()) return;

		if (IsPrimitive()) {
			if (type == TYPE_STRING) {
				GetString();

			} else {
				_primitive.ConvertTo(type);
			}
		} else {
			throw std::runtime_error("Value::Convert : Cannot convert");
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