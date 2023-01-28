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

#ifndef ANVIL_BYTEPIPE_OBJECTS_HPP
#define ANVIL_BYTEPIPE_OBJECTS_HPP

#include "anvil/byte-pipe/BytePipeCore.hpp"
#include <vector>
#include <array>
#include <map>
#include <list>
#include <sstream>
#include <deque>
#include <memory>

namespace anvil { namespace BytePipe {

	enum Type : uint8_t {
		TYPE_NULL,
		TYPE_C8,
		TYPE_U8,
		TYPE_U16,
		TYPE_U32,
		TYPE_U64,
		TYPE_S8,
		TYPE_S16,
		TYPE_S32,
		TYPE_S64,
		TYPE_F16,
		TYPE_F32,
		TYPE_F64,
		TYPE_STRING,
		TYPE_ARRAY,
		TYPE_OBJECT,
		TYPE_BOOL
	};

	static ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool IsUnsigned(const Type t) { return t >= TYPE_U8 && t <= TYPE_U64; }
	static ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool IsSigned(const Type t) { return t >= TYPE_S8 && t <= TYPE_S64; }
	static ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool IsIntegral(const Type t) { return t >= TYPE_U8 && t <= TYPE_S64; }
	static ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool IsFloatingPoint(const Type t) { return t >= TYPE_F16 && t <= TYPE_F64; }
	static ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool IsNumeric(const Type t) { return t >= TYPE_U8 && t <= TYPE_F64; }
	static ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool IsPrimitive(const Type t) { return (t >= TYPE_C8 && t <= TYPE_F64) || t == TYPE_BOOL; }

	typedef uint16_t ComponentID;

	enum half : uint16_t {};

	static size_t GetSizeOfPrimitiveType(const Type t) {
		static const uint8_t g_sizes[TYPE_BOOL + 1] = {
			0u,					//TYPE_NULL
			sizeof(char),		//TYPE_C8
			sizeof(uint8_t),	//TYPE_U8
			sizeof(uint16_t),	//TYPE_U16
			sizeof(uint32_t),	//TYPE_U32
			sizeof(uint64_t),	//TYPE_U64
			sizeof(int8_t),		//TYPE_S8
			sizeof(int16_t),	//TYPE_S16
			sizeof(int32_t),	//TYPE_S32
			sizeof(int64_t),	//TYPE_S64
			sizeof(half),		//TYPE_F16
			sizeof(float),		//TYPE_F32
			sizeof(double),		//TYPE_F64
			0u,					//TYPE_STRING
			0u,					//TYPE_ARRAY
			0u,					//TYPE_OBJECT
			sizeof(bool)		//TYPE_BOOL
		};

		return g_sizes[t];
	}


	template<class T>
	static ANVIL_CONSTEXPR_FN Type GetTypeID() {
		return TYPE_OBJECT; // Default
	}

	template<> static ANVIL_CONSTEXPR_FN Type GetTypeID<void>() { return TYPE_NULL; }
	template<> static ANVIL_CONSTEXPR_FN Type GetTypeID<char>() { return TYPE_C8; }
	template<> static ANVIL_CONSTEXPR_FN Type GetTypeID<bool>() { return TYPE_BOOL; }
	template<> static ANVIL_CONSTEXPR_FN Type GetTypeID<uint8_t>() { return TYPE_U8; }
	template<> static ANVIL_CONSTEXPR_FN Type GetTypeID<uint16_t>() { return TYPE_U16; }
	template<> static ANVIL_CONSTEXPR_FN Type GetTypeID<uint32_t>() { return TYPE_U32; }
	template<> static ANVIL_CONSTEXPR_FN Type GetTypeID<uint64_t>() { return TYPE_U64; }
	template<> static ANVIL_CONSTEXPR_FN Type GetTypeID<int8_t>() { return TYPE_S8; }
	template<> static ANVIL_CONSTEXPR_FN Type GetTypeID<int16_t>() { return TYPE_S16; }
	template<> static ANVIL_CONSTEXPR_FN Type GetTypeID<int32_t>() { return TYPE_S32; }
	template<> static ANVIL_CONSTEXPR_FN Type GetTypeID<int64_t>() { return TYPE_S64; }
	template<> static ANVIL_CONSTEXPR_FN Type GetTypeID<half>() { return TYPE_F16; }
	template<> static ANVIL_CONSTEXPR_FN Type GetTypeID<float>() { return TYPE_F32; }
	template<> static ANVIL_CONSTEXPR_FN Type GetTypeID<double>() { return TYPE_F64; }

	namespace details {
		template<class T>
		static inline uint64_t PrimitiveValueGetRaw(const T value) {
			union {
				uint64_t raw;
				T val;
			};
			if ANVIL_CONSTEXPR_VAR(sizeof(T) < sizeof(uint64_t)) raw = 0u;
			val = value;
			return raw;
		}
	}

	struct PrimitiveValue {
		union {
			void* ptr;
			bool b;
			char c8;
			uint8_t u8;
			uint16_t u16;
			uint32_t u32;
			uint64_t u64;
			int8_t s8;
			int16_t s16;
			int32_t s32;
			int64_t s64;
			half f16;
			float f32;
			double f64;
		};

		Type type;

		bool operator==(const PrimitiveValue& other) const;
		bool operator!=(const PrimitiveValue& other) const;

		/*!
			\param a_type The type of \a raw
			\param value The value
		*/
		PrimitiveValue(Type a_type, uint64_t value) :
			u64(value),
			type(a_type)
		{}

		PrimitiveValue() :
			PrimitiveValue(TYPE_NULL, 0u)
		{}

		PrimitiveValue(bool value) :
			PrimitiveValue(TYPE_BOOL, details::PrimitiveValueGetRaw<bool>(value))
		{}

		PrimitiveValue(char value) :
			PrimitiveValue(TYPE_C8, details::PrimitiveValueGetRaw<char>(value))
		{}

		PrimitiveValue(uint8_t value) :
			PrimitiveValue(TYPE_U8, details::PrimitiveValueGetRaw<uint8_t>(value))
		{}

		PrimitiveValue(uint16_t value) :
			PrimitiveValue(TYPE_U16, details::PrimitiveValueGetRaw<uint16_t>(value))
		{}

		PrimitiveValue(uint32_t value) :
			PrimitiveValue(TYPE_U32, details::PrimitiveValueGetRaw<uint32_t>(value))
		{}

		PrimitiveValue(uint64_t value) :
			PrimitiveValue(TYPE_U64, details::PrimitiveValueGetRaw<uint64_t>(value))
		{}

		PrimitiveValue(int8_t value) :
			PrimitiveValue(TYPE_S8, details::PrimitiveValueGetRaw<int8_t>(value))
		{}

		PrimitiveValue(int16_t value) :
			PrimitiveValue(TYPE_S16, details::PrimitiveValueGetRaw<int16_t>(value))
		{}

		PrimitiveValue(int32_t value) :
			PrimitiveValue(TYPE_S32, details::PrimitiveValueGetRaw<int32_t>(value))
		{}

		PrimitiveValue(int64_t value) :
			PrimitiveValue(TYPE_U64, details::PrimitiveValueGetRaw<int64_t>(value))
		{}

		PrimitiveValue(half value) :
			PrimitiveValue(TYPE_F16, details::PrimitiveValueGetRaw<half>(value))
		{}

		PrimitiveValue(float value) :
			PrimitiveValue(TYPE_F32, details::PrimitiveValueGetRaw<float>(value))
		{}

		PrimitiveValue(double value) :
			PrimitiveValue(TYPE_F64, details::PrimitiveValueGetRaw<double>(value))
		{}

		inline bool IsUnsigned() const { return BytePipe::IsUnsigned(type); }
		inline bool IsSigned() const { return BytePipe::IsSigned(type); }
		inline bool IsIntegral() const { return BytePipe::IsIntegral(type); }
		inline bool IsFloatingPoint() const { return BytePipe::IsFloatingPoint(type); }
		inline bool IsNumeric() const { return BytePipe::IsNumeric(type); }
		inline bool IsPrimitive() const { return BytePipe::IsPrimitive(type); }

		operator char() const;
		operator uint64_t() const;
		operator int64_t() const;
		operator half() const;
		operator double() const;

		inline operator bool() const {
			return type == TYPE_BOOL ? b : (operator uintptr_t() > 0u);
		}

		inline operator uint32_t() const {
			uint64_t tmp = type == TYPE_U32 ? u32 : operator uint64_t();
			if (tmp > UINT32_MAX) tmp = UINT32_MAX;
			return static_cast<uint32_t>(tmp);
		}

		inline operator int32_t() const {
			int64_t tmp = type == TYPE_S32 ? s16 : operator int64_t();
			if (tmp > INT32_MAX) tmp = INT32_MAX;
			else if (tmp < INT32_MIN) tmp = INT32_MIN;
			return static_cast<int32_t>(tmp);
		}

		inline operator uint8_t() const {
			uintptr_t tmp = type == TYPE_U8 ? u8 : operator uintptr_t();
			if (tmp > UINT8_MAX) tmp = UINT8_MAX;
			return static_cast<uint8_t>(tmp);
		}

		inline operator uint16_t() const {
			uintptr_t tmp = type == TYPE_U16 ? u16 : operator uintptr_t();
			if (tmp > UINT16_MAX) tmp = UINT16_MAX;
			return static_cast<uint16_t>(tmp);
		}

		inline operator int8_t() const {
			intptr_t tmp = type == TYPE_S8 ? s8 : operator intptr_t();
			if (tmp > INT8_MAX) tmp = INT8_MAX;
			else if (tmp < INT8_MIN) tmp = INT8_MIN;
			return static_cast<int8_t>(tmp);
		}

		inline operator int16_t() const {
			intptr_t tmp = type == TYPE_S16 ? s16 : operator intptr_t();
			if (tmp > INT16_MAX) tmp = INT16_MAX;
			else if (tmp < INT16_MIN) tmp = INT16_MIN;
			return static_cast<int16_t>(tmp);
		}

		inline operator float() const {
			return type == TYPE_F32 ? f32 : static_cast<float>(operator double());
		}

		/*!
			\brief Casts the value to the smallest type that can represent it without losing precision.
		*/
		void Optimise();
	};

	class Value {
	private:
		typedef std::vector<Value> Array;
		typedef std::vector<uint8_t> PrimitiveArray;
		typedef std::map<std::string, Value> Object;
		PrimitiveValue _primitive;
		Type _primitive_array_type;

		void ConvertFromPrimitveArray();
	public:

		Value(Value&& other) :
			Value()
		{
			Swap(other);
		}

		Value(const Value& other) :
			Value()
		{
			*this = other;
		}

		Value() :
			_primitive(),
			_primitive_array_type(TYPE_NULL)
		{
			_primitive.u64 = 0u;
		}

		explicit Value(bool value) :
			_primitive(value),
			_primitive_array_type(TYPE_NULL)
		{}

		explicit Value(char value) :
			_primitive(value),
			_primitive_array_type(TYPE_NULL)
		{}

		explicit Value(uint8_t value) :
			_primitive(value),
			_primitive_array_type(TYPE_NULL)
		{}

		explicit Value(uint16_t value) :
			_primitive(value),
			_primitive_array_type(TYPE_NULL)
		{}

		explicit Value(uint32_t value) :
			_primitive(value),
			_primitive_array_type(TYPE_NULL)
		{}

		explicit Value(uint64_t value) :
			_primitive(value),
			_primitive_array_type(TYPE_NULL)
		{}

		explicit Value(int8_t value) :
			_primitive(value),
			_primitive_array_type(TYPE_NULL)
		{}

		explicit Value(int16_t value) :
			_primitive(value),
			_primitive_array_type(TYPE_NULL)
		{}

		explicit Value(int32_t value) :
			_primitive(value),
			_primitive_array_type(TYPE_NULL)
		{}

		explicit Value(int64_t value) :
			_primitive(value),
			_primitive_array_type(TYPE_NULL)
		{}

		explicit Value(half value) :
			_primitive(value),
			_primitive_array_type(TYPE_NULL)
		{}

		explicit Value(float value) :
			_primitive(value),
			_primitive_array_type(TYPE_NULL)
		{}

		explicit Value(double value) :
			_primitive(value),
			_primitive_array_type(TYPE_NULL)
		{}

		explicit Value(const PrimitiveValue& value) :
			_primitive(value),
			_primitive_array_type(TYPE_NULL)
		{}

		~Value() {
			SetNull();
		}

		inline Value& operator=(Value&& other) {
			Swap(other);
			return *this;
		}

		Value& operator=(const Value&);

		void Swap(Value&);

		void Resize(const size_t size);
		void Reserve(const size_t size);

		inline Type GetType() const {
			return _primitive.type;
		}

		/*!
			\brief Set the value to be a null value.
			\details Previous value will be lost.
		*/
		void SetNull();

		/*!
			\brief Set the value to be a boolean.
			\details Previous value will be lost.
			\param value The value to copy.
		*/
		inline void SetBool(const bool value = false) {
			SetNull();
			_primitive = value;
		}

		/*!
			\brief Set the value to be a character.
			\details Previous value will be lost.
			\param value The value to copy.
		*/
		inline void SetC8(const char value = ' ') {
			SetNull();
			_primitive = value;
		}

		/*!
			\brief Set the value to be a 8-bit unsigned integer.
			\details Previous value will be lost.
			\param value The value to copy.
		*/
		inline void SetU8(const uint8_t value = 0u) {
			SetNull();
			_primitive = value;
		}

		/*!
			\brief Set the value to be a 16-bit unsigned integer.
			\details Previous value will be lost.
			\param value The value to copy.
		*/
		inline void SetU16(const uint16_t value = 0u) {
			SetNull();
			_primitive = value;
		}

		/*!
			\brief Set the value to be a 32-bit unsigned integer.
			\details Previous value will be lost.
			\param value The value to copy.
		*/
		inline void SetU32(const uint32_t value = 0u) {
			SetNull();
			_primitive = value;
		}

		/*!
			\brief Set the value to be a 64-bit unsigned integer.
			\details Previous value will be lost.
			\param value The value to copy.
		*/
		inline void SetU64(const uint64_t value = 0u) {
			SetNull();
			_primitive = value;
		}

		/*!
			\brief Set the value to be a 8-bit signed integer.
			\details Previous value will be lost.
			\param value The value to copy.
		*/
		inline void SetS8(const int8_t value = 0) {
			SetNull();
			_primitive = value;
		}

		/*!
			\brief Set the value to be a 16-bit signed integer.
			\details Previous value will be lost.
			\param value The value to copy.
		*/
		inline void SetS16(const int16_t value = 0) {
			SetNull();
			_primitive = value;
		}

		/*!
			\brief Set the value to be a 32-bit signed integer.
			\details Previous value will be lost.
			\param value The value to copy.
		*/
		inline void SetS32(const int32_t value = 0) {
			SetNull();
			_primitive = value;
		}

		/*!
			\brief Set the value to be a 64-bit signed integer.
			\details Previous value will be lost.
			\param value The value to copy.
		*/
		inline void SetS64(const int64_t value = 0) {
			SetNull();
			_primitive = value;
		}

		/*!
			\brief Set the value to be a 16-bit floating point.
			\details Previous value will be lost.
			\param value The value to copy.
		*/
		inline void SetF16(const half value = static_cast<half>(0)) {
			SetNull();
			_primitive = value;
		}

		/*!
			\brief Set the value to be a 32-bit floating point.
			\details Previous value will be lost.
			\param value The value to copy.
		*/
		inline void SetF32(const float value = 0.f) {
			SetNull();
			_primitive = value;
		}

		/*!
			\brief Set the value to be a 64-bit floating point.
			\details Previous value will be lost.
			\param value The value to copy.
		*/
		inline void SetF64(const double value = 0.0) {
			SetNull();
			_primitive = value;
		}

		/*!
			\brief Set the value to be a string.
			\details Previous value will be lost.
			\param value The value to copy, nullptr results in an empty string.
		*/
		void SetString(const char* value = nullptr);

		/*!
			\brief Set the value to be an array.
			\details Previous value will be lost.
		*/
		void SetArray();
		/*!
			\brief Same as SetArray but the array can only contain one primitive type
		*/
		void SetPrimitiveArray(Type type);

		/*!
			\brief Append a value to the end of the array.
			\details Throws exception is value is not an array.
			\param value The value to add.
		*/
		void AddValue(Value&& value);

		/*!
			\brief Append a value to the end of the array.
			\details Throws exception is value is not an array.
			\param value The value to add.
		*/
		void AddValue(const PrimitiveValue& value);

		/*!
			\brief Set the value to be an object.
			\details Previous value will be lost.
		*/
		void SetObject();

		/*!
			\brief Add a member value to an object.
			\details Throws exception is value is not an object.
			If the component ID already exists the previous value will be overwritten.
			\param id The component ID of the value.
			\param value The value to add.
		*/
		inline void AddValue(const ComponentID id, Value&& value) {
			if (_primitive.type != TYPE_OBJECT) throw std::runtime_error("Value::AddValue : Value is not an object");
			static_cast<Object*>(_primitive.ptr)->emplace(std::to_string(id), std::move(value));
		}

		inline void AddValue(const std::string& id, Value&& value) {
			if (_primitive.type != TYPE_OBJECT) throw std::runtime_error("Value::AddValue : Value is not an object");
			static_cast<Object*>(_primitive.ptr)->emplace(id, std::move(value));
		}

		inline bool GetBool() const {
			if (IsPrimitive()) return _primitive;
			throw std::runtime_error("Value::GetBool : Value cannot be converted to boolean");
		}

		inline char GetC8() const {
			if (IsPrimitive()) return _primitive;
			throw std::runtime_error("Value::GetC8 : Value cannot be converted to character");
		}

		inline uint8_t GetU8() const {
			if (IsPrimitive()) return _primitive;
			throw std::runtime_error("Value::GetU8 : Value cannot be converted to 8-bit unsigned integer");
		}

		inline uint16_t GetU16() const {
			if (IsPrimitive()) return _primitive;
			throw std::runtime_error("Value::GetU16 : Value cannot be converted to 16-bit unsigned integer");
		}

		inline uint32_t GetU32() const {
			if (IsPrimitive()) return _primitive;
			throw std::runtime_error("Value::GetU32 : Value cannot be converted to 32-bit unsigned integer");
		}

		inline uint64_t GetU64() const {
			if (IsPrimitive()) return _primitive;
			throw std::runtime_error("Value::GetU64 : Value cannot be converted to 64-bit unsigned integer");
		}

		inline int8_t GetS8() const {
			if (IsPrimitive()) return _primitive;
			throw std::runtime_error("Value::GetS8 : Value cannot be converted to 8-bit signed integer");
		}

		inline int16_t GetS16() const {
			if (IsPrimitive()) return _primitive;
			throw std::runtime_error("Value::GetS16 : Value cannot be converted to 16-bit signed integer");
		}

		inline int32_t GetS32() const {
			if (IsPrimitive()) return _primitive;
			throw std::runtime_error("Value::GetS32 : Value cannot be converted to 32-bit signed integer");
		}

		inline int64_t GetS64() const {
			if (IsPrimitive()) return _primitive;
			throw std::runtime_error("Value::GetS64 : Value cannot be converted to 64-bit signed integer");
		}

		inline half GetF16() const {
			if (IsPrimitive()) return _primitive;
			throw std::runtime_error("Value::GetF16 : Value cannot be converted to 16-bit floating point");
		}

		inline float GetF32() const {
			if (IsPrimitive()) return _primitive;
			throw std::runtime_error("Value::GetF32 : Value cannot be converted to 32-bit floating point");
		}

		inline double GetF64() const {
			if (IsPrimitive()) return _primitive;
			throw std::runtime_error("Value::GetF64 : Value cannot be converted to 64-bit floating point");
		}

		const char* GetString();

		/*!
			\brief Get a child value of an array or object.
			\details Throws an exception if the index is out of bounds or the component ID doesn't exist.
			\param index The index in an array or the componend ID of an object.
			\return The value at the location.
		*/
		Value& GetValue(const size_t index);
		Value& GetValue(const std::string& index);

		/*!
			\brief Return the base address of an array of primitive values
			\details Returns null if the value isn't a promative array
		*/
		void* GetPrimitiveArray();

		/*!
			\brief Get component ID at a specific index.
			\details Throws an exception if the index is out of bounds.
			\param index The index of the member (eg. 0 = First member, 1 = second member, ect).
			\return The component ID.
		*/
		ComponentID GetComponentID(const uint32_t index) const;
		std::string GetComponentIDString(const uint32_t index) const;

		/*!
			\brief Return the value as a primitive
			\detail Throws an exception if the type is not numerical.
		*/
		PrimitiveValue GetPrimitiveValue() const;

		/*!
			\brief Get the number of child values in an array or object.
			\detail Zero will be returned if the value is not an array or object.
		*/
		size_t GetSize() const;

		/*!
			\brief Casts the value to the smallest type that can represent it without losing precision.
		*/
		void Optimise();

		// Helpers

		inline bool IsUnsigned() const { return _primitive.IsUnsigned(); }
		inline bool IsSigned() const { return _primitive.IsSigned(); }
		inline bool IsIntegral() const { return _primitive.IsIntegral(); }
		inline bool IsFloatingPoint() const { return _primitive.IsFloatingPoint(); }
		inline bool IsNumeric() const { return _primitive.IsNumeric(); }
		inline bool IsPrimitive() const { return _primitive.IsPrimitive(); }

		inline bool IsPrimitiveArray() const {
			return _primitive_array_type != TYPE_BOOL && GetType() == TYPE_ARRAY;
		}

		inline Type GetPrimitiveArrayType() const {
			return _primitive_array_type;
		}

		inline Value& operator[] (const size_t i) {
			return GetValue(i);
		}

		inline const Value& operator[] (const size_t i) const{
			return const_cast<Value*>(this)->GetValue(i);
		}

		explicit inline operator bool() const {
			return GetBool();
		}

		explicit inline operator char() const {
			return GetC8();
		}

		explicit inline operator uint8_t() const {
			return GetU8();
		}

		explicit inline operator uint16_t() const {
			return GetU16();
		}

		explicit inline operator uint32_t() const {
			return GetU32();
		}

		explicit inline operator uint64_t() const {
			return GetU64();
		}

		explicit inline operator int8_t() const {
			return GetS8();
		}

		explicit inline operator int16_t() const {
			return GetS16();
		}

		explicit inline operator int32_t() const {
			return GetS32();
		}

		explicit inline operator int64_t() const {
			return GetS64();
		}

		explicit inline operator half() const {
			return GetF16();
		}

		explicit inline operator float() const {
			return GetF32();
		}

		explicit inline operator double() const {
			return GetF64();
		}

		explicit inline operator std::string() const {
			return const_cast<Value*>(this)->GetString();
		}

		explicit Value(const std::string& value) :
			Value()
		{
			SetString(value.c_str());
		}

		template<class T>
		explicit inline operator std::vector<T>() const {
			const size_t s = GetSize();
			std::vector<T> tmp(s);
			if (IsPrimitiveArray() && GetPrimitiveArrayType() == BytePipe::GetTypeID<T>()) {
				const void* src = const_cast<Value*>(this)->GetPrimitiveArray();
				memcpy(tmp.data(), src, sizeof(T) * s);
			} else {
				for (size_t i = 0u; i < s; ++i) tmp[i] = static_cast<T>(operator[](i));
			}
			return tmp;
		}

		template<class T>
		Value(const std::vector<T>& value) :
			Value()
		{
			if ANVIL_CONSTEXPR_FN (BytePipe::IsPrimitive(BytePipe::GetTypeID<T>())) {
				SetPrimitiveArray(BytePipe::GetTypeID<T>());
				const size_t s = value.size();
				Resize(s);
				memcpy(GetPrimitiveArray(), value.data(), sizeof(T) * s);
			} else {
				SetArray();
				for (T& tmp : value) AddValue(tmp);
			}
		}

		template<class T>
		explicit inline operator std::list<T>() const {
			const size_t s = GetSize();
			std::list<T> tmp;
			for (size_t i = 0u; i < s; ++i) tmp.push_back(static_cast<T>(operator[](i)));
			return tmp;
		}

		template<class T>
		explicit Value(const std::list<T>& value) :
			Value()
		{
			if ANVIL_CONSTEXPR_FN (BytePipe::IsPrimitive(BytePipe::GetTypeID<T>())) {
				SetPrimitiveArray(BytePipe::GetTypeID<T>());
			} else {
				SetArray();
			}
			for (T& tmp : value) AddValue(tmp);
		}

		template<class T>
		explicit inline operator std::deque<T>() const {
			const size_t s = GetSize();
			std::deque<T> tmp(s);
			for (size_t i = 0u; i < s; ++i) tmp[i] = static_cast<T>(operator[](i));
			return tmp;
		}

		template<class T>
		explicit Value(const std::deque<T>& value) :
			Value()
		{
			if ANVIL_CONSTEXPR_FN (BytePipe::IsPrimitive(BytePipe::GetTypeID<T>())) {
				SetPrimitiveArray(BytePipe::GetTypeID<T>());
			} else {
				SetArray();
			}
			for (T& tmp : value) AddValue(tmp);
		}

		template<class T, size_t S>
		explicit inline operator std::array<T, S>() const {
			std::array<T,S> tmp;			
			
			if (IsPrimitiveArray() && GetPrimitiveArrayType() == BytePipe::GetTypeID<T>()) {
				const void* src = const_cast<Value*>(this)->GetPrimitiveArray();
				memcpy(tmp.data(), src, sizeof(T) * S);
			} else {
				for (size_t i = 0u; i < S; ++i) tmp[i] = static_cast<T>(operator[](i));
			}
			return tmp;
		}

		template<class T, size_t S>
		explicit Value(const std::array<T, S>& value) :
			Value()
		{
			if ANVIL_CONSTEXPR_FN (BytePipe::IsPrimitive(BytePipe::GetTypeID<T>())) {
				SetPrimitiveArray(BytePipe::GetTypeID<T>());
				const size_t s = value.size();
				Resize(s);
				memcpy(GetPrimitiveArray(), value.data(), sizeof(T) * s);
			} else {
				SetArray();
				for (T& tmp : value) AddValue(tmp);
			}
		}

		template<class K, class V>
		explicit inline operator std::map<K, V>() const {
			const Value& keys = operator[](0);
			const Value& values = operator[](1);

			std::map<K, V> tmp;

			const size_t s = keys.GetSize();
			for (size_t i = 0u; i < s; ++i) {
				tmp.emplace(
					static_cast<K>(keys[i]),
					static_cast<V>(values[i])
				);
			}
			return tmp;
		}

		template<class K, class V>
		explicit Value(const std::map<K, V >& value) :
			Value()
		{
			Value keys;
			Value values;
			
			if ANVIL_CONSTEXPR_FN (BytePipe::IsPrimitive(BytePipe::GetTypeID<K>())) {
				keys.SetPrimitiveArray(BytePipe::GetTypeID<K>());
			} else {
				keys.SetArray();
			}
			
			if ANVIL_CONSTEXPR_FN (BytePipe::IsPrimitive(BytePipe::GetTypeID<V>())) {
				values.SetPrimitiveArray(BytePipe::GetTypeID<V>());
			} else {
				values.SetArray();
			}

			for (const std::pair<K, V>& tmp : value) {
				keys.AddValue(tmp.first);
				values.AddValue(tmp.second);
			}

			SetArray();
			AddValue(std::move(keys));
			AddValue(std::move(values));
		}
	};

}}

#endif
