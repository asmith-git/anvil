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
			v.type = TYPE_NULL;
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

	bool PrimitiveValue::ConvertTo(Type t) {
		if (t == type) return true;
		if (!IsPrimitiveConvertable(type)) return false;
		if (!IsPrimitiveConvertable(t)) return false;

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

		return true;
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
		case TYPE_NULL:
			Set<Null>();
			break;
		case TYPE_C8:
			Set<char>();
			break;
		case TYPE_U8:
			Set<uint8_t>();
			break;
		case TYPE_U16:
			Set<uint16_t>();
			break;
		case TYPE_U32:
			Set<uint32_t>();
			break;
		case TYPE_U64:
			Set<uint64_t>();
			break;
		case TYPE_S8:
			Set<int8_t>();
			break;
		case TYPE_S16:
			Set<int16_t>();
			break;
		case TYPE_S32:
			Set<int32_t>();
			break;
		case TYPE_S64:
			Set<int64_t>();
			break;
		case TYPE_F16:
			Set<half>();
			break;
		case TYPE_F32:
			Set<float>();
			break;
		case TYPE_F64:
			Set<double>();
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
			Set<bool>();
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
				SetPod() = *other.GetPod();
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

	/*!
		\brief Try to interpret this value as a general array
		\param convert If true then conversion from primitive array will be attempted
		\return Nullptr if the value is not a general array or cannot be converted to a general array
	*/
	Value::Array* Value::GetArray(bool convert) {
		if (_primitive.type == TYPE_ARRAY) {
			if (_primitive_array_type == TYPE_NULL) {
				return static_cast<Array*>(_primitive.ptr);
			} else if(convert) {
				return ConvertFromPrimitveArray();
			}
		}

		return nullptr;
	}

	/*!
		\brief Try to interpret this value as a general array
		\return Nullptr if the value is not a general array
	*/
	const Value::Array* Value::GetArray() const {
		return _primitive.type == TYPE_ARRAY && _primitive_array_type == TYPE_NULL ? static_cast<const Array*>(_primitive.ptr) : nullptr;
	}

	/*!
		\brief Try to interpret this value as a primitive
		\param convert If true then conversion from general array will be attempted
		\return Nullptr if the value is not a primitive array or cannot be converted to a primitive array
	*/
	Value::PrimitiveArray* Value::GetPrimitiveArray(bool convert) {
		if (_primitive.type == TYPE_ARRAY) {
			if (_primitive_array_type != TYPE_NULL) {
				return static_cast<PrimitiveArray*>(_primitive.ptr);
			} else if(convert) {
				return ConvertToPrimitveArray();
			}
		}
		return nullptr;
	}

	/*!
		\brief Try to interpret this value as an array
		\return Nullptr if the value is not a primitve array
	*/
	const Value::PrimitiveArray* Value::GetPrimitiveArray() const {
		return _primitive.type == TYPE_ARRAY && _primitive_array_type != TYPE_NULL ? static_cast<const PrimitiveArray*>(_primitive.ptr) : nullptr;
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
			v.Set<T>() = src_ptr[i];
			dst.push_back(std::move(v));
		}
	}

	/*!
		\brief Attempt to convert a general array into a primitve array
		\return Nullptr if is this value is not an array, or the primitive array could not be converted
	*/
	Value::PrimitiveArray* Value::ConvertToPrimitveArray() {
		// Check if this is a valid general array
		if (_primitive.type != TYPE_ARRAY) return nullptr;
		if (_primitive_array_type != TYPE_NULL) return static_cast<PrimitiveArray*>(_primitive.ptr);

		// If the array is empty then there is no way of knowing what primitve type to use
		Array& myArray = *static_cast<Array*>(_primitive.ptr);
		const size_t s = myArray.size();
		if (s == 0u) return nullptr;

		// Try to optimise any string values into primitves
		for (Value& v : myArray) if (v.GetType() == TYPE_STRING) {
			v.Optimise();

			// If still a string then it can't be made into a primative
			if (v.GetType() == TYPE_STRING) return nullptr;
		}

		Type target_type = myArray[0u].GetType();

		// This loop performs two operations:
		//   1) Check if all values in the array are already the same type
		//   2) Find the largest data type in the array, which the others will be converted to
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


		// If the values are not the same type then try to conver them
		if (!same_type) {
			target_type = largest_type;

			for (Value& v : myArray) {
				if (!v.ConvertTo(target_type)) return nullptr;
			}
		}

		// Convert to primative array
		Value tmp;
		PrimitiveArray& primitive_array = tmp.SetPrimitiveArray(target_type);
		const size_t bytes = GetSizeOfPrimitiveType(target_type);
		primitive_array.resize(s * bytes);
		for (size_t i = 0; i < s; ++i) {
			memcpy(primitive_array.data() + i * bytes, &myArray[0]._primitive.u8, bytes);
		}

		// Set this value to the new array and return
		Swap(tmp);
		return &primitive_array;
	}

	/*!
		\brief Attempt to convert a primitive array into a general array
		\return Nullptr if is this value is not an array, or the primitive array could not be converted
	*/
	Value::Array* Value::ConvertFromPrimitveArray() {
		// Check if the conversion is possible
		if (_primitive.type != TYPE_ARRAY) return nullptr;
		if (_primitive_array_type == TYPE_NULL) return static_cast<Array*>(_primitive.ptr);

		// Set up the array memory
		PrimitiveArray tmp = std::move(*static_cast<PrimitiveArray*>(_primitive.ptr));
		Value::Array& new_array = SetArray();

		// Convert the data
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

		return &new_array;
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

	/*!
		\brief Try to interpret this value as an object
		\param convert If true then conversion from an array will be attempted
		\return Nullptr if the value is not an object or cannot be converted to an object
	*/
	Value::Object* Value::GetObject(bool convert) {
		if (_primitive.type != TYPE_OBJECT) {
			if (convert && _primitive.type == TYPE_ARRAY) {
				Value::PrimitiveArray* pa = GetPrimitiveArray();

				Value::Array* a;
				if (pa) a = ConvertFromPrimitveArray();
				else a = GetArray();

				if (a) {
					// Convert from array to object
					Value tmp;
					Object& obj = tmp.SetObject();
					size_t s = a->size();
					for (size_t i = 0u; i < s; ++i) {
						Value& v = obj.emplace(std::to_string(i), Value()).first->second;
						v.Swap(a->data()[i]);
					}
					
					Swap(tmp);
					return static_cast<Object*>(_primitive.ptr);
				}
			}
			return nullptr;
		}

		return static_cast<Object*>(_primitive.ptr);
	}

	/*!
		\brief Try to interpret this value as an object
		\return Nullptr if the value is not an object
	*/
	const Value::Object* Value::GetObject() const {
		return _primitive.type == TYPE_OBJECT ? static_cast<const Object*>(_primitive.ptr) : nullptr;
	}
	
	bool Value::IterpretAsString(std::string& str) const {
		if (_primitive.type == TYPE_STRING) {
			str = *static_cast<std::string*>(_primitive.ptr);
			return true;

		} else {
			switch (_primitive.type) {
			case TYPE_C8:
				str += _primitive.c8;
				return true;
			case TYPE_U8:
				str = std::to_string(_primitive.u8);
				return true;
			case TYPE_U16:
				str = std::to_string(_primitive.u16);
				return true;
			case TYPE_U32:
				str = std::to_string(_primitive.u32);
				return true;
			case TYPE_U64:
				str = std::to_string(_primitive.u64);
				return true;
			case TYPE_S8:
				str = std::to_string(_primitive.u8);
				return true;
			case TYPE_S16:
				str = std::to_string(_primitive.s16);
				return true;
			case TYPE_S32:
				str = std::to_string(_primitive.s32);
				return true;
			case TYPE_S64:
				str = std::to_string(_primitive.s64);
				return true;
			case TYPE_F16:
				str = std::to_string(Get<float>());
				return true;
			case TYPE_F32:
				str = std::to_string(_primitive.f32);
				return true;
			case TYPE_F64:
				str = std::to_string(_primitive.f64);
				return true;
			case TYPE_BOOL:
				str = _primitive.b ? "true" : "false";
				return true;
			}
		}
		return false;
	}

	/*!
		\brief Try to interpret this value as a string
		\param Nullptr if the value is not a string
	*/
	const std::string* Value::GetString() const {
		return _primitive.type == TYPE_STRING ? static_cast<std::string*>(_primitive.ptr) : nullptr;
	}

	/*!
		\brief Try to interpret this value as a string
		\param convert If true then conversion from primitive to string will be performed
		\param Nullptr if the value is not a string
	*/
	std::string* Value::GetString(bool convert) {
		if (_primitive.type != TYPE_STRING) {
			if (convert) {
				std::string tmp;
				if (IterpretAsString(tmp)) {
					std::string& new_string = SetString();
					new_string = std::move(tmp);
					return &new_string;
				}
			}
			return nullptr;
		}

		return static_cast<std::string*>(_primitive.ptr);
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

	bool Value::ConvertTo(Type type) {
		if (type == GetType()) return true;

		if (IsPrimitive()) {
			if (type == TYPE_STRING) {
				return GetString(true) != nullptr;

			} else {
				return _primitive.ConvertTo(type);
			}
		}

		return false;
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

	// ArrayWrapper

	Value::ArrayWrapper::ArrayWrapper(Value& parent) :
		_parent(parent)
	{}

	Value::ArrayWrapper::~ArrayWrapper() {

	}

	void Value::ArrayWrapper::resize(size_t s) {
		Array* a = _parent.GetArray();
		if (a) {
			a->resize(s);
			return;
		}

		PrimitiveArray* pa = _parent.GetPrimitiveArray();
		if (pa) {
			pa->resize(s * GetSizeOfPrimitiveType(_parent._primitive_array_type));
		}
		
	}

	void Value::ArrayWrapper::reserve(size_t s) {
		Array* a = _parent.GetArray();
		if (a) {
			a->reserve(s);
			return;
		}

		PrimitiveArray* pa = _parent.GetPrimitiveArray();
		if (pa) {
			pa->reserve(s * GetSizeOfPrimitiveType(_parent._primitive_array_type));
		}

	}

	size_t Value::ArrayWrapper::size() const {
		Array* a = _parent.GetArray();
		if (a) return a->size();

		PrimitiveArray* pa = _parent.GetPrimitiveArray();
		if (pa) return pa->size() / GetSizeOfPrimitiveType(_parent._primitive_array_type);

		return 0u;
	}

	/*!
		\brief Append a primitive value to the end of the array
		\detail May be converted to a general array if the value is not compatible with the array's primitive type
		\param value The value to add
		\param The addres of the added value, or nullptr if this is stil a primitive arary
	*/
	Value* Value::ArrayWrapper::push_back(const PrimitiveValue& value) {
		PrimitiveArray* pa = _parent.GetPrimitiveArray();
		Array* a = _parent.GetArray();

		if(pa) {
			// Try to add primative type

			PrimitiveValue v = value;
			if (v.ConvertTo(_parent._primitive_array_type)) {

				size_t bytes = GetSizeOfPrimitiveType(_parent._primitive_array_type);

				size_t prev_size = pa->size();
				pa->resize(prev_size + bytes);
				memcpy(pa->data() + prev_size, &v.u8, bytes);

				return nullptr;
			}

			// Convert to value array
			a = _parent.ConvertFromPrimitveArray();
		}
		
		if (a) {
			a->push_back(Value());
			Value& v = a->back();
			v = value;
			return &v;

		}

		throw std::runtime_error("Value::ArrayWrapper::push_back : Value is not an array, or value is not compatible");
	}

	/*!
		\brief Append a value to the end of the array
		\detail May be converted to a general array if the value is not primitive
		\param value The value to add
		\param The addres of the added value, or nullptr if this is still a primitive arary
	*/
	Value* Value::ArrayWrapper::push_back(Value&& value) {
		PrimitiveArray* pa = _parent.GetPrimitiveArray();
		if (pa) value.Optimise(); // Decrease probability of primitve array being converted to general array

		// Handle primitive data types in a way that is optimised for them
		if (value.IsPrimitive()) {
			return push_back(value._primitive);

		// General values
		} else {
			Array* a = _parent.GetArray();

			if (pa) a = _parent.ConvertFromPrimitveArray();

			if (a) {
				a->push_back(std::move(value));
				return &a->back();
			}
			
		}

		throw std::runtime_error("Value::ArrayWrapper::push_back : Value is not an array");
	}

	void Value::ArrayWrapper::pop_back() {
		Array* a = _parent.GetArray();
		if (a) { a->pop_back(); return; }

		PrimitiveArray* pa = _parent.GetPrimitiveArray();
		if (pa) {
			const size_t bytes = GetSizeOfPrimitiveType(_parent._primitive_array_type);
			for (size_t i = 0u; i < bytes; ++i) pa->pop_back();
		}
	}

	void Value::ArrayWrapper::clear() {
		Array* a = _parent.GetArray();
		if (a) { a->clear(); return; }

		PrimitiveArray* pa = _parent.GetPrimitiveArray();
		if (pa) pa->clear();
	}

	/*!
		\brief Get a reference to a value in the array
		\detail The array will be converted to general array if it is a primitive array
		\param i The index in the array
		\return The value
	*/
	Value& Value::ArrayWrapper::operator[](size_t i) {
		PrimitiveArray* pa = _parent.GetPrimitiveArray();
		if (pa) _parent.ConvertFromPrimitveArray();

		Array* a = _parent.GetArray();
		if (a) return a->operator[](i);

		throw std::runtime_error("Value::ArrayWrapper::operator[] : Value is not an array");
	}

	/*!
		\brief Attempt to write a primitive value to the array without converting the type of the array
		\detail Data may be lost in the conversion of the value to the array's type. If the value cannot be converted then the array will be converted to a general array.
		\param i The index to write to
		\param val The value to write
		\return A pointer to the value at the index requested, or nullptr if the array is a primitive array
	*/
	Value* Value::ArrayWrapper::set(size_t i, PrimitiveValue val) {
		PrimitiveArray* pa = _parent.GetPrimitiveArray();
		if (pa) {
			if (val.ConvertTo(_parent._primitive_array_type)) {
				const size_t bytes = GetSizeOfPrimitiveType(_parent._primitive_array_type);
				memcpy(pa->data() + bytes * i, &val.u64, bytes);
				return nullptr;
			}

			_parent.ConvertToPrimitveArray();
		}

		Array* a = _parent.GetArray();
		if (a) {
			Value& v = a->operator[](i);
			v = val;
			return &v;
		}

		throw std::runtime_error("Value::ArrayWrapper::set : Value is not an array");
	}

	/*!
		\brief Attempt to write a primitive value to the array without converting the type of the array
		\detail Data may be lost in the conversion of the value to the array's type. If the value cannot be converted then the array will be converted to a general array.
		\param i The index to write to
		\param val The value to write
		\return A pointer to the value at the index requested, or nullptr if the array is a primitive array
	*/
	Value* Value::ArrayWrapper::set(size_t i, const Value& val) {
		if (val.IsPrimitive()) return set(i, val._primitive);
		Value& tmp = operator[](i);
		tmp = val;
		return &tmp;
	}

	/*!
		\brief Attempt to read a value from the array without converting it's type
		\param i The index to read from
		\param val The primitive value that is read, set to null if the value is not primitive
		\return A pointer to the value at the index requested, or nullptr if the array is a primitive array
	*/
	const Value* Value::ArrayWrapper::at(size_t i, PrimitiveValue& val) const {
		PrimitiveArray* pa = _parent.GetPrimitiveArray();
		if (pa) {
			const size_t bytes = GetSizeOfPrimitiveType(_parent._primitive_array_type);
			memcpy(&val.u64, pa->data() + bytes * i, bytes);
			val.type = _parent._primitive_array_type;
			return nullptr;
		}

		Array* a = _parent.GetArray();
		if (a) {
			Value& v = a->operator[](i);
			if (v.IsPrimitive()) {
				val = v.GetPrimitiveValue();
			} else {
				val.type == TYPE_NULL;
			}
			return &v;
		}

		throw std::runtime_error("Value::ArrayWrapper::at : Value is not an array");
	}

}}