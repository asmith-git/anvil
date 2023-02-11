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

#include <vector>
#include <array>
#include <map>
#include <list>
#include <sstream>
#include <deque>
#include <memory>
#include "anvil/byte-pipe/BytePipeCore.hpp"
#include "anvil/core/LibDetect.hpp"
#if ANVIL_OPENCV_SUPPORT
#include <opencv2/opencv.hpp>
#endif

namespace anvil { namespace BytePipe {

	enum PodType : uint32_t {
		POD_OPENCV_IMAGE = 1u
	};

#if ANVIL_OPENCV_SUPPORT
	enum ImageFormat {
		IMAGE_BIN,
		IMAGE_JPEG,
		IMAGE_JPEG2000,
		IMAGE_BMP,
		IMAGE_PNG,
		IMAGE_TIFF,
		IMAGE_WEBP,
		IMAGE_EXR,
		IMAGE_HDR
	};
#endif

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
		TYPE_BOOL,
		TYPE_POD
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
		static const uint8_t g_sizes[TYPE_POD + 1] = {
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
			sizeof(bool),		//TYPE_BOOL
			0u					//TYPE_POD
		};

		return g_sizes[t];
	}


	template<class T>
	ANVIL_CONSTEXPR_FN Type GetTypeID() {
		return TYPE_OBJECT; // Default
	}

	template<> ANVIL_CONSTEXPR_FN Type GetTypeID<void>() { return TYPE_NULL; }
	template<> ANVIL_CONSTEXPR_FN Type GetTypeID<char>() { return TYPE_C8; }
	template<> ANVIL_CONSTEXPR_FN Type GetTypeID<bool>() { return TYPE_BOOL; }
	template<> ANVIL_CONSTEXPR_FN Type GetTypeID<uint8_t>() { return TYPE_U8; }
	template<> ANVIL_CONSTEXPR_FN Type GetTypeID<uint16_t>() { return TYPE_U16; }
	template<> ANVIL_CONSTEXPR_FN Type GetTypeID<uint32_t>() { return TYPE_U32; }
	template<> ANVIL_CONSTEXPR_FN Type GetTypeID<uint64_t>() { return TYPE_U64; }
	template<> ANVIL_CONSTEXPR_FN Type GetTypeID<int8_t>() { return TYPE_S8; }
	template<> ANVIL_CONSTEXPR_FN Type GetTypeID<int16_t>() { return TYPE_S16; }
	template<> ANVIL_CONSTEXPR_FN Type GetTypeID<int32_t>() { return TYPE_S32; }
	template<> ANVIL_CONSTEXPR_FN Type GetTypeID<int64_t>() { return TYPE_S64; }
	template<> ANVIL_CONSTEXPR_FN Type GetTypeID<half>() { return TYPE_F16; }
	template<> ANVIL_CONSTEXPR_FN Type GetTypeID<float>() { return TYPE_F32; }
	template<> ANVIL_CONSTEXPR_FN Type GetTypeID<double>() { return TYPE_F64; }

    template<class T>
    bool ANVIL_CONSTEXPR_FN IsPrimitiveType() { return (GetTypeID<T>() >= TYPE_C8 && GetTypeID<T>() <= TYPE_F64) || GetTypeID<T>() == TYPE_BOOL; }

	namespace details {
		template<class T>
		static ANVIL_STRONG_INLINE uint64_t PrimitiveValueGetRaw(const T value) {
			union {
				uint64_t raw;
				T val;
			};
			if ANVIL_CONSTEXPR_VAR(sizeof(T) < sizeof(uint64_t)) raw = 0u;
			val = value;
			return raw;
		}
	}

	struct ANVIL_DLL_EXPORT PrimitiveValue {
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

		ANVIL_STRONG_INLINE bool IsUnsigned() const { return BytePipe::IsUnsigned(type); }
		ANVIL_STRONG_INLINE bool IsSigned() const { return BytePipe::IsSigned(type); }
		ANVIL_STRONG_INLINE bool IsIntegral() const { return BytePipe::IsIntegral(type); }
		ANVIL_STRONG_INLINE bool IsFloatingPoint() const { return BytePipe::IsFloatingPoint(type); }
		ANVIL_STRONG_INLINE bool IsNumeric() const { return BytePipe::IsNumeric(type); }
		ANVIL_STRONG_INLINE bool IsPrimitive() const { return BytePipe::IsPrimitive(type); }

		operator char() const;
		operator uint64_t() const;
		operator int64_t() const;
		operator half() const;
		operator double() const;

		ANVIL_STRONG_INLINE operator bool() const {
			return type == TYPE_BOOL ? b : (operator uintptr_t() > 0u);
		}

		ANVIL_STRONG_INLINE operator uint32_t() const {
			uint64_t tmp = type == TYPE_U32 ? u32 : operator uint64_t();
			if (tmp > UINT32_MAX) tmp = UINT32_MAX;
			return static_cast<uint32_t>(tmp);
		}

		ANVIL_STRONG_INLINE operator int32_t() const {
			int64_t tmp = type == TYPE_S32 ? s16 : operator int64_t();
			if (tmp > INT32_MAX) tmp = INT32_MAX;
			else if (tmp < INT32_MIN) tmp = INT32_MIN;
			return static_cast<int32_t>(tmp);
		}

		ANVIL_STRONG_INLINE operator uint8_t() const {
			uintptr_t tmp = type == TYPE_U8 ? u8 : operator uintptr_t();
			if (tmp > UINT8_MAX) tmp = UINT8_MAX;
			return static_cast<uint8_t>(tmp);
		}

		ANVIL_STRONG_INLINE operator uint16_t() const {
			uintptr_t tmp = type == TYPE_U16 ? u16 : operator uintptr_t();
			if (tmp > UINT16_MAX) tmp = UINT16_MAX;
			return static_cast<uint16_t>(tmp);
		}

		ANVIL_STRONG_INLINE operator int8_t() const {
			intptr_t tmp = type == TYPE_S8 ? s8 : operator intptr_t();
			if (tmp > INT8_MAX) tmp = INT8_MAX;
			else if (tmp < INT8_MIN) tmp = INT8_MIN;
			return static_cast<int8_t>(tmp);
		}

		ANVIL_STRONG_INLINE operator int16_t() const {
			intptr_t tmp = type == TYPE_S16 ? s16 : operator intptr_t();
			if (tmp > INT16_MAX) tmp = INT16_MAX;
			else if (tmp < INT16_MIN) tmp = INT16_MIN;
			return static_cast<int16_t>(tmp);
		}

		ANVIL_STRONG_INLINE operator float() const {
			return type == TYPE_F32 ? f32 : static_cast<float>(operator double());
		}

		/*!
			\brief Casts the value to the smallest type that can represent it without losing precision.
		*/
		void Optimise();

		bool ConvertTo(Type type);
	};

	template<class T>
	struct ValueEncoder;

	namespace detail {
		struct ANVIL_DLL_EXPORT Pod {
			std::vector<uint8_t> data;
			PodType type;


#if ANVIL_OPENCV_SUPPORT
			static cv::Mat CreateOpenCVMatFromPOD(const void* data, const size_t bytes);
			static Pod CreatePODFromCVMat(const cv::Mat& img, ImageFormat compression_format = IMAGE_BIN, float compression_quality = 100.f);
#endif
		};

		template<class T>
		struct ValueSetReturn {
			typedef T& type;
		};

		template<>
		struct ValueSetReturn<void> {
			typedef void type;
		};

		template<class T>
		struct ValueGetReturn {
			typedef T& type;
			typedef T const_type;
		};

		template<>
		struct ValueGetReturn<void> {
			typedef void type;
			typedef void const_type;
		};

		template<class T>
		struct ValueGetReturn<std::vector<T>> {
			typedef std::vector<T>* type;
			typedef const std::vector<T>* const_type;
		};

		template<class K, class V>
		struct ValueGetReturn<std::map<K,V>> {
			typedef std::map<K, V>* type;
			typedef const std::map<K, V>* const_type;
		};

		template<>
		struct ValueGetReturn<std::string> {
			typedef std::string* type;
			typedef const std::string* const_type;
		};

		template<>
		struct ValueGetReturn<Pod> {
			typedef Pod* type;
			typedef const Pod* const_type;
		};

	}

	class ANVIL_DLL_EXPORT Value {
	public:
		typedef void Null;
		typedef std::vector<Value> Array;
		typedef std::map<std::string, Value> Object;
		typedef std::vector<uint8_t> PrimitiveArray;

		class ArrayWrapper {
		private:
			Value& _parent;
		public:
			ArrayWrapper(Value& parent);
			~ArrayWrapper();

			void resize(size_t);
			void reserve(size_t);
			size_t size() const;

			Value* push_back(const PrimitiveValue& value);
			Value* push_back(Value&& value);

			void pop_back();

			void clear();

			Value& operator[](size_t i);

			Value* set(size_t i, PrimitiveValue val);
			Value* set(size_t i, const Value& val);
			const Value* at(size_t i, PrimitiveValue& val) const;

			ANVIL_STRONG_INLINE Value& at(size_t i) { return operator[](i); }
			ANVIL_STRONG_INLINE Value& front() { return operator[](0u); }
			ANVIL_STRONG_INLINE Value& back() { return operator[](size() - 1u); }
			ANVIL_STRONG_INLINE bool empty() const { return size() == 0u; }

			ANVIL_STRONG_INLINE Array* GetArray(bool convert = false) { return convert ? _parent.ConvertFromPrimitveArray() : _parent.GetArray(); }
			ANVIL_STRONG_INLINE PrimitiveArray* GetPrimitiveArray(bool convert = false) { return convert ? _parent.ConvertToPrimitveArray() : _parent.GetPrimitiveArray(); }
		};

		typedef detail::Pod Pod;
	private:
		PrimitiveValue _primitive;
		Type _primitive_array_type;

		Array* ConvertFromPrimitveArray();
		PrimitiveArray* ConvertToPrimitveArray();		

		void SetNull();
		std::string& SetString(const char* value = nullptr);
		Array& SetArray();
		PrimitiveArray& SetPrimitiveArray(Type type);
		Pod& SetPod();
		Object& SetObject();

		Array* GetArray(bool convert = false);
		const Array* GetArray() const;

		PrimitiveArray* GetPrimitiveArray(bool convert = false);
		const PrimitiveArray* GetPrimitiveArray() const;

		Object* GetObject(bool convert = false);
		const Object* GetObject() const;

		bool IterpretAsString(std::string& str) const;
		std::string* GetString(bool convert = false);
		const std::string* GetString() const;

#if ANVIL_OPENCV_SUPPORT
		ANVIL_STRONG_INLINE Pod& SetImage() {
			Pod& pod = SetPod();
			pod.type = POD_OPENCV_IMAGE;
			return pod;
		}
#endif

		ANVIL_STRONG_INLINE Pod* GetPod() { return _primitive.type == TYPE_POD ? static_cast<Pod*>(_primitive.ptr) : nullptr; }
		ANVIL_STRONG_INLINE const Pod* GetPod() const { return _primitive.type == TYPE_POD ? static_cast<const Pod*>(_primitive.ptr) : nullptr; }

#if ANVIL_OPENCV_SUPPORT
		ANVIL_STRONG_INLINE cv::Mat GetImage() const {
			const Pod* pod = GetPod();
			if (pod == nullptr || pod->type != POD_OPENCV_IMAGE) throw std::runtime_error("Value::GetImage : Value is not an image");
			return Pod::CreateOpenCVMatFromPOD(pod->data.data(), pod->data.size());
		}
#endif
	public:
		Value();
		Value(Value&& other);
		Value(const Value& other);

		Value(const Type type);

		Value(bool value);
		Value(char value);
		Value(uint8_t value);
		Value(uint16_t value);
		Value(uint32_t value);
		Value(uint64_t value);
		Value(int8_t value);
		Value(int16_t value);
		Value(int32_t value);
		Value(int64_t value);
		Value(half value);
		Value(float value);
		Value(double value);

		Value(const char* string);
		Value(const std::string& string);

		Value(const PrimitiveValue& value);

		Value(Pod&& value);
		Value(const Pod& value);

#if ANVIL_OPENCV_SUPPORT
		Value(const cv::Mat& img);
#endif

		~Value();

		ANVIL_STRONG_INLINE Value& operator=(Value&& other) {
			Swap(other);
			return *this;
		}

		Value& operator=(const Value&);

		void Swap(Value&);

		void Resize(const size_t size);
		void Reserve(const size_t size);

		ANVIL_STRONG_INLINE Type GetType() const {
			return _primitive.type;
		}

		/*!
			\brief Set the value to be a boolean.
			\details Previous value will be lost.
			\return A reference to the set value
		*/
		template<class T>
		ANVIL_STRONG_INLINE typename detail::ValueSetReturn<T>::type Set();

		template<class T, class ...PARAMS>
		ANVIL_STRONG_INLINE typename detail::ValueSetReturn<T>::type Set(PARAMS ... params);

		template<class T>
		ANVIL_STRONG_INLINE typename detail::ValueGetReturn<T>::type Get();

		template<class T>
		ANVIL_STRONG_INLINE typename detail::ValueGetReturn<T>::const_type Get() const;

		ANVIL_STRONG_INLINE bool GetBool() const {
			if (IsPrimitive()) return _primitive;
			throw std::runtime_error("Value::GetBool : Value cannot be converted to boolean");
		}

		ANVIL_STRONG_INLINE char GetC8() const {
			if (IsPrimitive()) return _primitive;
			throw std::runtime_error("Value::GetC8 : Value cannot be converted to character");
		}

		ANVIL_STRONG_INLINE uint8_t GetU8() const {
			if (IsPrimitive()) return _primitive;
			throw std::runtime_error("Value::GetU8 : Value cannot be converted to 8-bit unsigned integer");
		}

		ANVIL_STRONG_INLINE uint16_t GetU16() const {
			if (IsPrimitive()) return _primitive;
			throw std::runtime_error("Value::GetU16 : Value cannot be converted to 16-bit unsigned integer");
		}

		ANVIL_STRONG_INLINE uint32_t GetU32() const {
			if (IsPrimitive()) return _primitive;
			throw std::runtime_error("Value::GetU32 : Value cannot be converted to 32-bit unsigned integer");
		}

		ANVIL_STRONG_INLINE uint64_t GetU64() const {
			if (IsPrimitive()) return _primitive;
			throw std::runtime_error("Value::GetU64 : Value cannot be converted to 64-bit unsigned integer");
		}

		ANVIL_STRONG_INLINE int8_t GetS8() const {
			if (IsPrimitive()) return _primitive;
			throw std::runtime_error("Value::GetS8 : Value cannot be converted to 8-bit signed integer");
		}

		ANVIL_STRONG_INLINE int16_t GetS16() const {
			if (IsPrimitive()) return _primitive;
			throw std::runtime_error("Value::GetS16 : Value cannot be converted to 16-bit signed integer");
		}

		ANVIL_STRONG_INLINE int32_t GetS32() const {
			if (IsPrimitive()) return _primitive;
			throw std::runtime_error("Value::GetS32 : Value cannot be converted to 32-bit signed integer");
		}

		ANVIL_STRONG_INLINE int64_t GetS64() const {
			if (IsPrimitive()) return _primitive;
			throw std::runtime_error("Value::GetS64 : Value cannot be converted to 64-bit signed integer");
		}

		ANVIL_STRONG_INLINE half GetF16() const {
			if (IsPrimitive()) return _primitive;
			throw std::runtime_error("Value::GetF16 : Value cannot be converted to 16-bit floating point");
		}

		ANVIL_STRONG_INLINE float GetF32() const {
			if (IsPrimitive()) return _primitive;
			throw std::runtime_error("Value::GetF32 : Value cannot be converted to 32-bit floating point");
		}

		ANVIL_STRONG_INLINE double GetF64() const {
			if (IsPrimitive()) return _primitive;
			throw std::runtime_error("Value::GetF64 : Value cannot be converted to 64-bit floating point");
		}

		/*!
			\brief Get component ID at a specific index.
			\details Throws an exception if the index is out of bounds.
			\param index The index of the member (eg. 0 = First member, 1 = second member, ect).
			\return The component ID.
		*/
		std::string GetComponentIDString(const size_t index) const;

		ANVIL_STRONG_INLINE ComponentID GetComponentID(const size_t index) const {
			return static_cast<ComponentID>(std::stoi(GetComponentIDString(index)));
		}

		/*!
			\brief Return the value as a primitive
			\detail Throws an exception if the type is not numerical.
		*/
		PrimitiveValue GetPrimitiveValue() const;

		/*!
			\brief Casts the value to the smallest type that can represent it without losing precision.
		*/
		void Optimise();

		bool ConvertTo(Type type);

		// Helpers

		ANVIL_STRONG_INLINE bool IsUnsigned() const { return _primitive.IsUnsigned(); }
		ANVIL_STRONG_INLINE bool IsSigned() const { return _primitive.IsSigned(); }
		ANVIL_STRONG_INLINE bool IsIntegral() const { return _primitive.IsIntegral(); }
		ANVIL_STRONG_INLINE bool IsFloatingPoint() const { return _primitive.IsFloatingPoint(); }
		ANVIL_STRONG_INLINE bool IsNumeric() const { return _primitive.IsNumeric(); }
		ANVIL_STRONG_INLINE bool IsPrimitive() const { return _primitive.IsPrimitive(); }
		ANVIL_STRONG_INLINE bool IsNull() const { return GetType() == TYPE_NULL; }
		ANVIL_STRONG_INLINE bool IsArray() const { return GetType() == TYPE_ARRAY; }
		ANVIL_STRONG_INLINE bool IsObject() const { return GetType() == TYPE_OBJECT; }
		ANVIL_STRONG_INLINE bool IsPod() const { return GetType() == TYPE_POD; }

#if ANVIL_OPENCV_SUPPORT
		ANVIL_STRONG_INLINE bool IsImage() const { return IsPod() && GetPod()->type == POD_OPENCV_IMAGE;}
#endif

		ANVIL_STRONG_INLINE bool IsPrimitiveArray() const { return _primitive_array_type != TYPE_BOOL && GetType() == TYPE_ARRAY; }
		ANVIL_STRONG_INLINE Type GetPrimitiveArrayType() const { return _primitive_array_type; }

		explicit ANVIL_STRONG_INLINE operator bool() const { return GetBool(); }
		explicit ANVIL_STRONG_INLINE operator char() const { return GetC8(); }
		explicit ANVIL_STRONG_INLINE operator uint8_t() const { return GetU8(); }
		explicit ANVIL_STRONG_INLINE operator uint16_t() const { return GetU16(); }
		explicit ANVIL_STRONG_INLINE operator uint32_t() const { return GetU32(); }
		explicit ANVIL_STRONG_INLINE operator uint64_t() const { return GetU64(); }
		explicit ANVIL_STRONG_INLINE operator int8_t() const { return GetS8(); }
		explicit ANVIL_STRONG_INLINE operator int16_t() const { return GetS16(); }
		explicit ANVIL_STRONG_INLINE operator int32_t() const { return GetS32(); }
		explicit ANVIL_STRONG_INLINE operator int64_t() const { return GetS64(); }
		explicit ANVIL_STRONG_INLINE operator half() const { return GetF16(); }
		explicit ANVIL_STRONG_INLINE operator float() const { return GetF32(); }
		explicit ANVIL_STRONG_INLINE operator double() const { return GetF64(); }

#if ANVIL_OPENCV_SUPPORT
		explicit ANVIL_STRONG_INLINE operator cv::Mat() const { return GetImage(); }
#endif
	};

	namespace detail {

#if ANVIL_OPENCV_SUPPORT
		template<>
		struct ValueSetReturn<cv::Mat> {
			typedef Value::Pod& type;
		};
#endif

	}

	template<>
	ANVIL_STRONG_INLINE bool& Value::Set<bool>() {
		SetNull();
		_primitive.type = GetTypeID<bool>();
		return _primitive.b;
	}

	template<>
	ANVIL_STRONG_INLINE bool Value::Get<bool>() const {
		return GetBool();
	}

	template<>
	ANVIL_STRONG_INLINE bool& Value::Get<bool>() {
		typedef bool T;
		return Set<T>() = const_cast<const Value*>(this)->Get<T>();
	}

	template<>
	ANVIL_STRONG_INLINE char& Value::Set<char>() {
		SetNull();
		_primitive.type = GetTypeID<char>();
		return _primitive.c8;
	}

	template<>
	ANVIL_STRONG_INLINE char Value::Get<char>() const {
		return GetC8();
	}

	template<>
	ANVIL_STRONG_INLINE char& Value::Get<char>() {
		typedef char T;
		return Set<T>() = const_cast<const Value*>(this)->Get<T>();
	}

	template<>
	ANVIL_STRONG_INLINE uint8_t& Value::Set<uint8_t>() {
		SetNull();
		_primitive.type = GetTypeID<uint8_t>();
		return _primitive.u8;
	}

	template<>
	ANVIL_STRONG_INLINE uint8_t Value::Get<uint8_t>() const {
		return GetU8();
	}

	template<>
	ANVIL_STRONG_INLINE uint8_t& Value::Get<uint8_t>() {
		typedef uint8_t T;
		return Set<T>() = const_cast<const Value*>(this)->Get<T>();
	}

	template<>
	ANVIL_STRONG_INLINE uint16_t& Value::Set<uint16_t>() {
		SetNull();
		_primitive.type = GetTypeID<uint16_t>();
		return _primitive.u16;
	}

	template<>
	ANVIL_STRONG_INLINE uint16_t Value::Get<uint16_t>() const {
		return GetU16();
	}

	template<>
	ANVIL_STRONG_INLINE uint16_t& Value::Get<uint16_t>() {
		typedef uint16_t T;
		return Set<T>() = const_cast<const Value*>(this)->Get<T>();
	}

	template<>
	ANVIL_STRONG_INLINE uint32_t& Value::Set<uint32_t>() {
		SetNull();
		_primitive.type = GetTypeID<uint32_t>();
		return _primitive.u32;
	}

	template<>
	ANVIL_STRONG_INLINE uint32_t Value::Get<uint32_t>() const {
		return GetU32();
	}

	template<>
	ANVIL_STRONG_INLINE uint32_t& Value::Get<uint32_t>() {
		typedef uint32_t T;
		return Set<T>() = const_cast<const Value*>(this)->Get<T>();
	}

	template<>
	ANVIL_STRONG_INLINE uint64_t& Value::Set<uint64_t>() {
		SetNull();
		_primitive.type = GetTypeID<uint64_t>();
		return _primitive.u64;
	}

	template<>
	ANVIL_STRONG_INLINE uint64_t Value::Get<uint64_t>() const {
		return GetU64();
	}

	template<>
	ANVIL_STRONG_INLINE uint64_t& Value::Get<uint64_t>() {
		typedef uint64_t T;
		return Set<T>() = const_cast<const Value*>(this)->Get<T>();
	}

	template<>
	ANVIL_STRONG_INLINE int8_t& Value::Set<int8_t>() {
		SetNull();
		_primitive.type = GetTypeID<int8_t>();
		return _primitive.s8;
	}

	template<>
	ANVIL_STRONG_INLINE int8_t Value::Get<int8_t>() const {
		return GetS8();
	}

	template<>
	ANVIL_STRONG_INLINE int8_t& Value::Get<int8_t>() {
		typedef int8_t T;
		return Set<T>() = const_cast<const Value*>(this)->Get<T>();
	}

	template<>
	ANVIL_STRONG_INLINE int16_t& Value::Set<int16_t>() {
		SetNull();
		_primitive.type = GetTypeID<int16_t>();
		return _primitive.s16;
	}

	template<>
	ANVIL_STRONG_INLINE int16_t Value::Get<int16_t>() const {
		return GetS16();
	}

	template<>
	ANVIL_STRONG_INLINE int16_t& Value::Get<int16_t>() {
		typedef int16_t T;
		return Set<T>() = const_cast<const Value*>(this)->Get<T>();
	}

	template<>
	ANVIL_STRONG_INLINE int32_t& Value::Set<int32_t>() {
		SetNull();
		_primitive.type = GetTypeID<int32_t>();
		return _primitive.s32;
	}

	template<>
	ANVIL_STRONG_INLINE int32_t Value::Get<int32_t>() const {
		return GetS32();
	}

	template<>
	ANVIL_STRONG_INLINE int32_t& Value::Get<int32_t>() {
		typedef int32_t T;
		return Set<T>() = const_cast<const Value*>(this)->Get<T>();
	}

	template<>
	ANVIL_STRONG_INLINE int64_t& Value::Set<int64_t>() {
		SetNull();
		_primitive.type = GetTypeID<int64_t>();
		return _primitive.s64;
	}

	template<>
	ANVIL_STRONG_INLINE int64_t Value::Get<int64_t>() const {
		return GetS64();
	}

	template<>
	ANVIL_STRONG_INLINE int64_t& Value::Get<int64_t>() {
		typedef int64_t T;
		return Set<T>() = const_cast<const Value*>(this)->Get<T>();
	}

	template<>
	ANVIL_STRONG_INLINE half& Value::Set<half>() {
		SetNull();
		_primitive.type = GetTypeID<half>();
		return _primitive.f16;
	}

	template<>
	ANVIL_STRONG_INLINE half Value::Get<half>() const {
		return GetF16();
	}

	template<>
	ANVIL_STRONG_INLINE half& Value::Get<half>() {
		typedef half T;
		return Set<T>() = const_cast<const Value*>(this)->Get<T>();
	}

	template<>
	ANVIL_STRONG_INLINE float& Value::Set<float>() {
		SetNull();
		_primitive.type = GetTypeID<float>();
		return _primitive.f32;
	}

	template<>
	ANVIL_STRONG_INLINE float Value::Get<float>() const {
		return GetF32();
	}

	template<>
	ANVIL_STRONG_INLINE float& Value::Get<float>() {
		typedef float T;
		return Set<T>() = const_cast<const Value*>(this)->Get<T>();
	}

	template<>
	ANVIL_STRONG_INLINE double& Value::Set<double>() {
		SetNull();
		_primitive.type = GetTypeID<double>();
		return _primitive.f64;
	}

	template<>
	ANVIL_STRONG_INLINE double Value::Get<double>() const {
		return GetF64();
	}

	template<>
	ANVIL_STRONG_INLINE double& Value::Get<double>() {
		typedef double T;
		return Set<T>() = const_cast<const Value*>(this)->Get<T>();
	}

	template<>
	ANVIL_STRONG_INLINE std::string& Value::Set<std::string>() {
		return SetString();
	}

	template<>
	ANVIL_STRONG_INLINE const std::string* Value::Get<std::string>() const {
		return GetString();
	}

	template<>
	ANVIL_STRONG_INLINE std::string* Value::Get<std::string>() {
		return GetString(true);
	}

	template<>
	ANVIL_STRONG_INLINE Value::Object& Value::Set<Value::Object>() {
		return SetObject();
	}

	template<>
	ANVIL_STRONG_INLINE const Value::Object* Value::Get<Value::Object>() const {
		return GetObject();
	}

	template<>
	ANVIL_STRONG_INLINE Value::Object* Value::Get<Value::Object>() {
		return GetObject(false);
	}

	template<>
	ANVIL_STRONG_INLINE Value::Array& Value::Set<Value::Array>() {
		return SetArray();
	}

	template<>
	ANVIL_STRONG_INLINE const Value::Array* Value::Get<Value::Array>() const {
		return GetArray();
	}

	template<>
	ANVIL_STRONG_INLINE Value::Array* Value::Get<Value::Array>() {
		return GetArray(false);
	}

	template<>
	ANVIL_STRONG_INLINE Value::PrimitiveArray& Value::Set<Value::PrimitiveArray, Type>(Type type) {
		return SetPrimitiveArray(type);
	}

	template<>
	ANVIL_STRONG_INLINE const Value::PrimitiveArray* Value::Get<Value::PrimitiveArray>() const {
		return GetPrimitiveArray();
	}

	template<>
	ANVIL_STRONG_INLINE Value::PrimitiveArray* Value::Get<Value::PrimitiveArray>() {
		return GetPrimitiveArray(false);
	}

	template<>
	ANVIL_STRONG_INLINE Value::Pod& Value::Set<Value::Pod>() {
		return SetPod();
	}

	template<>
	ANVIL_STRONG_INLINE const Value::Pod* Value::Get<Value::Pod>() const {
		return GetPod();
	}

	template<>
	ANVIL_STRONG_INLINE Value::Pod* Value::Get<Value::Pod>() {
		return GetPod();
	}

	template<>
	ANVIL_STRONG_INLINE void Value::Set<Value::Null>() {
		return SetNull();
	}

#if ANVIL_OPENCV_SUPPORT
	template<>
	ANVIL_STRONG_INLINE Value::Pod& Value::Set<cv::Mat>() {
		return SetImage();
	}
#endif

}}

#endif
