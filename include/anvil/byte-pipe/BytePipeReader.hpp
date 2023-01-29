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

#ifndef ANVIL_BYTEPIPE_READER_HPP
#define ANVIL_BYTEPIPE_READER_HPP

#include <vector>
#include <array>
#include <deque>
#include <list>
#include <map>
#include "anvil/byte-pipe/BytePipeCore.hpp"
#include "anvil/byte-pipe/BytePipeEndian.hpp"
#include "anvil/byte-pipe/BytePipeObjects.hpp"

namespace anvil { namespace BytePipe {

	/*!
		\author Adam Smtih
		\date September 2019
		\brief An input stream for binary data.
		\see OutputPipe
	*/
	class InputPipe {
	public:
		virtual ~InputPipe() {}
		virtual uint32_t ReadBytes(void* dst, const uint32_t bytes) = 0;
		virtual void ReadBytesFast(void* dst, const uint32_t bytes) { ReadBytes(dst, bytes); }
	};


	/*!
		\author Adam Smtih
		\date September 2019
		\brief Interface for serialising or deserialising data.
	*/
	class Parser {
	public:
		Parser() {

		}

		virtual ~Parser() {

		}

		// Basic functionality

		/*!
			\brief Called when the pipe is about to recieve data
			\details Use this function to initialise variables.
			OnPipeClose will be called when all data is revieved.
			\see OnPipeClose
		*/
		virtual void OnPipeOpen() = 0;

		/*!
			\brief Called after all data has been recieved.
			\details Use this function to clean up variables and free memory.
			\see OnPipeOpen
		*/
		virtual void OnPipeClose() = 0;

		/*!
			\brief Signal that the next value(s) are part of an array.
			\details OnArrayEnd must be called after all values in the array have been parsed.
			The values will be in sequential order, so that the first value is index 0, then index 1, ect.
			\param size The number of values in the array.
			\see OnArrayEnd
		*/
		virtual void OnArrayBegin(const uint32_t size) = 0;

		/*!
			\brief Signal that all values in an array have been parsed.
			\see OnArrayBegin
		*/
		virtual void OnArrayEnd() = 0;

		/*!
			\brief Signal that the next value(s) are part of an object.
			\details OnObjectEnd must be called after all values in the array have been parsed.
			The values are unordered, but OnComponentID must be called before each value to identify it.
			\param size The number of values in the object.
			\see OnArrayEnd
			\see OnComponentID
		*/
		virtual void OnObjectBegin(const uint32_t component_count) = 0;

		/*!
			\brief Signal that all values in an object have been parsed.
			\see OnObjectBegin
		*/
		virtual void OnObjectEnd() = 0;

		/*!
			\brief Specify which value is the next to be parsed.
			Any calls outside of a OnObjectBegin / OnObjectEnd pair should be igored.
			\param id The value's identifier.
			\see OnArrayEnd
			\see OnComponentID
		*/
		virtual void OnComponentID(const ComponentID id) = 0;

		virtual void OnComponentID(const char* str, const uint32_t size) = 0;

		ANVIL_STRONG_INLINE void OnComponentID(const char* id) { OnComponentID(id, static_cast<uint32_t>(strlen(id))); }
		ANVIL_STRONG_INLINE void OnComponentID(const std::string& id) { OnComponentID(id.c_str(), static_cast<uint32_t>(id.size())); }

		/*!
			\brief Handle a user defined binary structure.
			\details This allows the user to define their own POD (plain old data) structures, which can be 
			handled natively by pipes, this is faster than serialising the structure as an object.
			\param type A 24-bit ID code that describes which structure is being parsed.
			\param bytes The size of the structure in bytes.
			\param data A pointer to the structure.
		*/
		virtual void OnUserPOD(const uint32_t type, const uint32_t bytes, const void* data) = 0;

		/*!
			\brief Handle a null value
		*/
		virtual void OnNull() = 0;

		/*!
			\brief Handle a primitive value (64-bit floating point)
			\param value The value
		*/
		virtual void OnPrimitiveF64(const double value) = 0;

		/*!
			\brief Handle a string value
			\param value The string data, this may not zero-terminated
		*/
		virtual void OnPrimitiveString(const char* value, const uint32_t length) = 0;

		/*!
			\brief Handle a primitive value (boolean)
			\param value The value
		*/
		virtual void OnPrimitiveBool(const bool value) = 0;

		/*!
			\brief Handle a primitive value (character)
			\param value The value
		*/
		virtual void OnPrimitiveC8(const char value) = 0;

		/*!
			\brief Handle a primitive value (64-bit unsigned integer)
			\param value The value
		*/
		virtual void OnPrimitiveU64(const uint64_t value) { 
			OnPrimitiveF64(static_cast<double>(value));
		}

		/*!
			\brief Handle a primitive value (64-bit signed integer)
			\param value The value
		*/
		virtual void OnPrimitiveS64(const int64_t value) { 
			OnPrimitiveF64(static_cast<double>(value));
		}

		/*!
			\brief Handle a primitive value (32-bit floating point)
			\param value The value
		*/
		virtual void OnPrimitiveF32(const float value) { 
			OnPrimitiveF64(value);
		}

		/*!
			\brief Handle a primitive value (8-bit unsigned integer)
			\param value The value
		*/
		virtual void OnPrimitiveU8(const uint8_t value) { 
			OnPrimitiveU64(value);
		}

		/*!
			\brief Handle a primitive value (16-bit unsigned integer)
			\param value The value
		*/
		virtual void OnPrimitiveU16(const uint16_t value) { 
			OnPrimitiveU64(value);
		}

		/*!
			\brief Handle a primitive value (32-bit unsigned integer)
			\param value The value
		*/
		virtual void OnPrimitiveU32(const uint32_t value) { 
			OnPrimitiveU64(value);
		}

		/*!
			\brief Handle a primitive value (8-bit signed integer)
			\param value The value
		*/
		virtual void OnPrimitiveS8(const int8_t value) { 
			OnPrimitiveS64(value);
		}

		/*!
			\brief Handle a primitive value (16-bit signed integer)
			\param value The value
		*/
		virtual void OnPrimitiveS16(const int16_t value) { 
			OnPrimitiveS64(value);
		}

		/*!
			\brief Handle a primitive value (32-bit signed integer)
			\param value The value
		*/
		virtual void OnPrimitiveS32(const int32_t value) { 
			OnPrimitiveS64(value); 
		}

		/*!
			\brief Handle a primitive value (16-bit floating point)
			\param value The value
		*/
		virtual void OnPrimitiveF16(const half value) { 
			OnPrimitiveF32(static_cast<float>(value));  //! \bug half to float conversion not implemented
		}

		// Object Support

		void OnValue(const Value& value);
		void OnValue(const PrimitiveValue& value);

		// Array Optimisations

		/*!
			\brief Handle an array of primitive values (8-bit unsigned integers)
			\details This is the same as the following code, but is a special case that could be optimised :
			\code{.cpp}
			OnArrayBegin(size);
			for (uint32_t i = 0u; i < size; ++i) OnPrimitiveU8(src[i]);
			OnArrayEnd();
			\endcode
			\param src The address of the first value
			\param size The number of values in the array
		*/
		virtual void OnPrimitiveArrayU8(const uint8_t* src, const uint32_t size) {
			OnArrayBegin(size);
			for (uint32_t i = 0u; i < size; ++i) OnPrimitiveU8(src[i]);
			OnArrayEnd();
		}

		/*!
			\brief Handle an array of primitive values (16-bit unsigned integers)
			\details This is the same as the following code, but is a special case that could be optimised :
			\code{.cpp}
			OnArrayBegin(size);
			for (uint32_t i = 0u; i < size; ++i) OnPrimitiveU16(src[i]);
			OnArrayEnd();
			\endcode
			\param src The address of the first value
			\param size The number of values in the array
		*/
		virtual void OnPrimitiveArrayU16(const uint16_t* src, const uint32_t size) {
			OnArrayBegin(size);
			for (uint32_t i = 0u; i < size; ++i) OnPrimitiveU16(src[i]);
			OnArrayEnd();
		}

		/*!
			\brief Handle an array of primitive values (32-bit unsigned integers)
			\details This is the same as the following code, but is a special case that could be optimised :
			\code{.cpp}
			OnArrayBegin(size);
			for (uint32_t i = 0u; i < size; ++i) OnPrimitiveU32(src[i]);
			OnArrayEnd();
			\endcode
			\param src The address of the first value
			\param size The number of values in the array
		*/
		virtual void OnPrimitiveArrayU32(const uint32_t* src, const uint32_t size) {
			OnArrayBegin(size);
			for (uint32_t i = 0u; i < size; ++i) OnPrimitiveU32(src[i]);
			OnArrayEnd();
		}

		/*!
			\brief Handle an array of primitive values (64-bit unsigned integers)
			\details This is the same as the following code, but is a special case that could be optimised :
			\code{.cpp}
			OnArrayBegin(size);
			for (uint32_t i = 0u; i < size; ++i) OnPrimitiveU64(src[i]);
			OnArrayEnd();
			\endcode
			\param src The address of the first value
			\param size The number of values in the array
		*/
		virtual void OnPrimitiveArrayU64(const uint64_t* src, const uint32_t size) {
			OnArrayBegin(size);
			for (uint32_t i = 0u; i < size; ++i) OnPrimitiveU64(src[i]);
			OnArrayEnd();
		}

		/*!
			\brief Handle an array of primitive values (8-bit signed integers)
			\details This is the same as the following code, but is a special case that could be optimised :
			\code{.cpp}
			OnArrayBegin(size);
			for (uint32_t i = 0u; i < size; ++i) OnPrimitiveS8(src[i]);
			OnArrayEnd();
			\endcode
			\param src The address of the first value
			\param size The number of values in the array
		*/
		virtual void OnPrimitiveArrayS8(const int8_t* src, const uint32_t size) {
			OnArrayBegin(size);
			for (uint32_t i = 0u; i < size; ++i) OnPrimitiveS8(src[i]);
			OnArrayEnd();
		}

		/*!
			\brief Handle an array of primitive values (16-bit signed integers)
			\details This is the same as the following code, but is a special case that could be optimised :
			\code{.cpp}
			OnArrayBegin(size);
			for (uint32_t i = 0u; i < size; ++i) OnPrimitiveS16(src[i]);
			OnArrayEnd();
			\endcode
			\param src The address of the first value
			\param size The number of values in the array
		*/
		virtual void OnPrimitiveArrayS16(const int16_t* src, const uint32_t size) {
			OnArrayBegin(size);
			for (uint32_t i = 0u; i < size; ++i) OnPrimitiveS16(src[i]);
			OnArrayEnd();
		}

		/*!
			\brief Handle an array of primitive values (32-bit signed integers)
			\details This is the same as the following code, but is a special case that could be optimised :
			\code{.cpp}
			OnArrayBegin(size);
			for (uint32_t i = 0u; i < size; ++i) OnPrimitiveS32(src[i]);
			OnArrayEnd();
			\endcode
			\param src The address of the first value
			\param size The number of values in the array
		*/
		virtual void OnPrimitiveArrayS32(const int32_t* src, const uint32_t size) {
			OnArrayBegin(size);
			for (uint32_t i = 0u; i < size; ++i) OnPrimitiveS32(src[i]);
			OnArrayEnd();
		}

		/*!
			\brief Handle an array of primitive values (64-bit signed integers)
			\details This is the same as the following code, but is a special case that could be optimised :
			\code{.cpp}
			OnArrayBegin(size);
			for (uint32_t i = 0u; i < size; ++i) OnPrimitiveS64(src[i]);
			OnArrayEnd();
			\endcode
			\param src The address of the first value
			\param size The number of values in the array
		*/
		virtual void OnPrimitiveArrayS64(const int64_t* src, const uint32_t size) {
			OnArrayBegin(size);
			for (uint32_t i = 0u; i < size; ++i) OnPrimitiveS64(src[i]);
			OnArrayEnd();
		}

		/*!
			\brief Handle an array of primitive values (32-bit floating point)
			\details This is the same as the following code, but is a special case that could be optimised :
			\code{.cpp}
			OnArrayBegin(size);
			for (uint32_t i = 0u; i < size; ++i) OnPrimitiveF32(src[i]);
			OnArrayEnd();
			\endcode
			\param src The address of the first value
			\param size The number of values in the array
		*/
		virtual void OnPrimitiveArrayF32(const float* src, const uint32_t size) {
			OnArrayBegin(size);
			for (uint32_t i = 0u; i < size; ++i) OnPrimitiveF32(src[i]);
			OnArrayEnd();
		}

		/*!
			\brief Handle an array of primitive values (64-bit floating point)
			\details This is the same as the following code, but is a special case that could be optimised :
			\code{.cpp}
			OnArrayBegin(size);
			for (uint32_t i = 0u; i < size; ++i) OnPrimitiveF64(src[i]);
			OnArrayEnd();
			\endcode
			\param src The address of the first value
			\param size The number of values in the array
		*/
		virtual void OnPrimitiveArrayF64(const double* src, const uint32_t size) {
			OnArrayBegin(size);
			for (uint32_t i = 0u; i < size; ++i) OnPrimitiveF64(src[i]);
			OnArrayEnd();
		}

		/*!
			\brief Handle an array of primitive values (character)
			\details This is the same as the following code, but is a special case that could be optimised :
			\code{.cpp}
			OnArrayBegin(size);
			for (uint32_t i = 0u; i < size; ++i) OnPrimitiveC8(src[i]);
			OnArrayEnd();
			\endcode
			\param src The address of the first value
			\param size The number of values in the array
		*/
		virtual void OnPrimitiveArrayC8(const char* src, const uint32_t size) {
			OnArrayBegin(size);
			for (uint32_t i = 0u; i < size; ++i) OnPrimitiveC8(src[i]);
			OnArrayEnd();
		}

		/*!
			\brief Handle an array of primitive values (16-bit floating point)
			\details This is the same as the following code, but is a special case that could be optimised :
			\code{.cpp}
			OnArrayBegin(size);
			for (uint32_t i = 0u; i < size; ++i) OnPrimitiveF16(src[i]);
			OnArrayEnd();
			\endcode
			\param src The address of the first value
			\param size The number of values in the array
		*/
		virtual void OnPrimitiveArrayF16(const half* src, const uint32_t size) {
			OnArrayBegin(size);
			for (uint32_t i = 0u; i < size; ++i) OnPrimitiveF16(src[i]);
			OnArrayEnd();
		}

		/*!
			\brief Handle an array of primitive values (bool)
			\details This is the same as the following code, but is a special case that could be optimised :
			\code{.cpp}
			OnArrayBegin(size);
			for (uint32_t i = 0u; i < size; ++i) OnPrimitiveBool(src[i]);
			OnArrayEnd();
			\endcode
			\param src The address of the first value
			\param size The number of values in the array
		*/
		virtual void OnPrimitiveArrayBool(const bool* src, const uint32_t size) {
			OnArrayBegin(size);
			for (uint32_t i = 0u; i < size; ++i) OnPrimitiveBool(src[i]);
			OnArrayEnd();
		}

		// Template helpers

		template<class T>
		inline void OnPrimitive(const T value);

		template<class T>
		inline void OnPrimitiveArray(const T* values, const uint32_t size);

		template<>
		inline void OnPrimitive<bool>(const bool value) {
			OnPrimitiveBool(value);
		}

		template<>
		inline void OnPrimitiveArray<bool>(const bool* values, const uint32_t size) {
			OnPrimitiveArrayBool(values, size);
		}


		template<>
		inline void OnPrimitive<char>(const char value) {
			OnPrimitiveC8(value);
		}

		template<>
		inline void OnPrimitiveArray<char>(const char* values, const uint32_t size) {
			OnPrimitiveArrayC8(values, size);
		}

		template<>
		inline void OnPrimitive<uint8_t>(const uint8_t value) {
			OnPrimitiveU8(value);
		}

		template<>
		inline void OnPrimitiveArray<uint8_t>(const uint8_t* values, const uint32_t size) {
			OnPrimitiveArrayU8(values, size);
		}

		template<>
		inline void OnPrimitive<uint16_t>(const uint16_t value) {
			OnPrimitiveU16(value);
		}

		template<>
		inline void OnPrimitiveArray<uint16_t>(const uint16_t* values, const uint32_t size) {
			OnPrimitiveArrayU16(values, size);
		}

		template<>
		inline void OnPrimitive<uint32_t>(const uint32_t value) {
			OnPrimitiveU32(value);
		}

		template<>
		inline void OnPrimitiveArray<uint32_t>(const uint32_t* values, const uint32_t size) {
			OnPrimitiveArrayU32(values, size);
		}

		template<>
		inline void OnPrimitive<uint64_t>(const uint64_t value) {
			OnPrimitiveU64(value);
		}

		template<>
		inline void OnPrimitiveArray<uint64_t>(const uint64_t* values, const uint32_t size) {
			OnPrimitiveArrayU64(values, size);
		}

		template<>
		inline void OnPrimitive<int8_t>(const int8_t value) {
			OnPrimitiveS8(value);
		}

		template<>
		inline void OnPrimitiveArray<int8_t>(const int8_t* values, const uint32_t size) {
			OnPrimitiveArrayS8(values, size);
		}

		template<>
		inline void OnPrimitive<int16_t>(const int16_t value) {
			OnPrimitiveS16(value);
		}

		template<>
		inline void OnPrimitiveArray<int16_t>(const int16_t* values, const uint32_t size) {
			OnPrimitiveArrayS16(values, size);
		}

		template<>
		inline void OnPrimitive<int32_t>(const int32_t value) {
			OnPrimitiveS32(value);
		}

		template<>
		inline void OnPrimitiveArray<int32_t>(const int32_t* values, const uint32_t size) {
			OnPrimitiveArrayS32(values, size);
		}

		template<>
		inline void OnPrimitive<int64_t>(const int64_t value) {
			OnPrimitiveS64(value);
		}

		template<>
		inline void OnPrimitiveArray<int64_t>(const int64_t* values, const uint32_t size) {
			OnPrimitiveArrayS64(values, size);
		}

		template<>
		inline void OnPrimitive<half>(const half value) {
			OnPrimitiveF16(value);
		}

		template<>
		inline void OnPrimitiveArray<half>(const half* values, const uint32_t size) {
			OnPrimitiveArrayF16(values, size);
		}

		template<>
		inline void OnPrimitive<float>(const float value) {
			OnPrimitiveF32(value);
		}

		template<>
		inline void OnPrimitiveArray<float>(const float* values, const uint32_t size) {
			OnPrimitiveArrayF32(values, size);
		}

		template<>
		inline void OnPrimitive<double>(const double value) {
			OnPrimitiveF64(value);
		}

		template<>
		inline void OnPrimitiveArray<double>(const double* values, const uint32_t size) {
			OnPrimitiveArrayF64(values, size);
		}

		// Object helper functions

		template<class T>
		inline void OnPrimitive(const ComponentID component_id, const T value) {
			OnComponentID(component_id);
			OnPrimitive<T>(value);
		}

		template<class T>
		inline void OnPrimitiveArray(const ComponentID component_id, const T* values, const uint32_t size) {
			OnComponentID(component_id);
			OnPrimitiveArray<T>(values, size);
		}

		// General helper

		inline void operator()(const char*& value) { OnPrimitiveString(value, static_cast<uint32_t>(strlen(value))); }

		template<class T>
		inline void operator()(const T& value) = delete;

		template<> inline void operator()<uint8_t>(const uint8_t& value) { OnPrimitive<uint8_t>(value); }
		template<> inline void operator()<uint16_t>(const uint16_t& value) { OnPrimitive<uint16_t>(value); }
		template<> inline void operator()<uint32_t>(const uint32_t& value) { OnPrimitive<uint32_t>(value); }
		template<> inline void operator()<uint64_t>(const uint64_t& value) { OnPrimitive<uint64_t>(value); }
		template<> inline void operator()<int8_t>(const int8_t& value) { OnPrimitive<int8_t>(value); }
		template<> inline void operator()<int16_t>(const int16_t& value) { OnPrimitive<int16_t>(value); }
		template<> inline void operator()<int32_t>(const int32_t& value) { OnPrimitive<int32_t>(value); }
		template<> inline void operator()<int64_t>(const int64_t& value) { OnPrimitive<int64_t>(value); }
		template<> inline void operator()<half>(const half& value) { OnPrimitive<half>(value); }
		template<> inline void operator()<float>(const float& value) { OnPrimitive<float>(value); }
		template<> inline void operator()<double>(const double& value) { OnPrimitive<double>(value); }
		template<> inline void operator()<bool>(const bool& value) { OnPrimitive<bool>(value); }
		template<> inline void operator()<std::string>(const std::string& value) { OnPrimitiveString(value.c_str(), static_cast<uint32_t>(value.size())); }

		template<class T>
		inline void operator()(const std::vector<T>& value) {
			OnArrayBegin(static_cast<uint32_t>(value.size()));
			for(const T& val : value) operator()(val);
			OnArrayEnd();
		}

		template<> inline void operator()(const std::vector<uint8_t>& value) { OnPrimitiveArray<uint8_t>(value.data(), static_cast<uint32_t>(value.size())); }
		template<> inline void operator()(const std::vector<uint16_t>& value) { OnPrimitiveArray<uint16_t>(value.data(), static_cast<uint32_t>(value.size())); }
		template<> inline void operator()(const std::vector<uint32_t>& value) { OnPrimitiveArray<uint32_t>(value.data(), static_cast<uint32_t>(value.size())); }
		template<> inline void operator()(const std::vector<uint64_t>& value) { OnPrimitiveArray<uint64_t>(value.data(), static_cast<uint32_t>(value.size())); }
		template<> inline void operator()(const std::vector<int8_t>& value) { OnPrimitiveArray<int8_t>(value.data(), static_cast<uint32_t>(value.size())); }
		template<> inline void operator()(const std::vector<int16_t>& value) { OnPrimitiveArray<int16_t>(value.data(), static_cast<uint32_t>(value.size())); }
		template<> inline void operator()(const std::vector<int32_t>& value) { OnPrimitiveArray<int32_t>(value.data(), static_cast<uint32_t>(value.size())); }
		template<> inline void operator()(const std::vector<int64_t>& value) { OnPrimitiveArray<int64_t>(value.data(), static_cast<uint32_t>(value.size())); }
		template<> inline void operator()(const std::vector<half>& value) { OnPrimitiveArray<half>(value.data(), static_cast<uint32_t>(value.size())); }
		template<> inline void operator()(const std::vector<float>& value) { OnPrimitiveArray<float>(value.data(), static_cast<uint32_t>(value.size())); }
		template<> inline void operator()(const std::vector<double>& value) { OnPrimitiveArray<double>(value.data(), static_cast<uint32_t>(value.size())); }

		template<class T, uint32_t S>
		inline void operator()(const std::array<T, S>& value) {
			OnArrayBegin(S);
			for (const T& val : value) operator()(val);
			OnArrayEnd();
		}

		template<uint32_t S> inline void operator()(const std::array<uint8_t, S>& value) { OnPrimitiveArray<uint8_t>(value.data(), S); }
		template<uint32_t S> inline void operator()(const std::array<uint16_t, S>& value) { OnPrimitiveArray<uint16_t>(value.data(), S); }
		template<uint32_t S> inline void operator()(const std::array<uint32_t, S>& value) { OnPrimitiveArray<uint32_t>(value.data(), S); }
		template<uint32_t S> inline void operator()(const std::array<uint64_t, S>& value) { OnPrimitiveArray<uint64_t>(value.data(), S); }
		template<uint32_t S> inline void operator()(const std::array<int8_t, S>& value) { OnPrimitiveArray<int8_t>(value.data(), S); }
		template<uint32_t S> inline void operator()(const std::array<int16_t, S>& value) { OnPrimitiveArray<int16_t>(value.data(), S); }
		template<uint32_t S> inline void operator()(const std::array<int32_t, S>& value) { OnPrimitiveArray<int32_t>(value.data(), S); }
		template<uint32_t S> inline void operator()(const std::array<int64_t, S>& value) { OnPrimitiveArray<int64_t>(value.data(), S); }
		template<uint32_t S> inline void operator()(const std::array<half, S>& value) { OnPrimitiveArray<half>(value.data(), S); }
		template<uint32_t S> inline void operator()(const std::array<float, S>& value) { OnPrimitiveArray<float>(value.data(), S); }
		template<uint32_t S> inline void operator()(const std::array<double, S>& value) { OnPrimitiveArray<double>(value.data(), S); }

		template<class T>
		inline void operator()(const std::list<T>& value) {
			OnArrayBegin(value.size());
			for (const T& val : value) operator()(val);
			OnArrayEnd();
		}

		template<class T>
		inline void operator()(const std::deque<T>& value) {
			OnArrayBegin(value.size());
			for (const T& val : value) operator()(val);
			OnArrayEnd();
		}

		template<class K, class T>
		inline void operator()(const std::map<K, T>& value) {
			const uint32_t s = static_cast<uint32_t>(value.size());

			OnArrayBegin(2);

			// Keys
			OnArrayBegin(s);
			for (const auto& v : value) operator()(v.first);
			OnArrayEnd();

			// Values
			OnArrayBegin(s);
			for (const auto& v : value) operator()(v.second);
			OnArrayEnd();

			OnArrayEnd();
		}

	};

	/*!
		\author Adam Smtih
		\date ??? 2019
		\brief Reads binary serialised data from an InputPipe and outputs it into a Parser
		\see Writer
	*/
	class Reader {
	private:
		Reader(Reader&&) = delete;
		Reader(const Reader&) = delete;
		Reader& operator=(Reader&&) = delete;
		Reader& operator=(const Reader&) = delete;

		InputPipe& _pipe;

	public:
		Reader(InputPipe& pipe);
		virtual ~Reader();

		void Read(Parser& dst);
	};

	/*!
		\author Adam Smtih
		\date March 2021
		\brief Converts data into DOM (document object model) style format.
	*/
	class ValueParser final : public Parser {
	private:
		Value _root;
		std::vector<Value*> _value_stack;
		std::string _component_id_str;
		ComponentID _component_id;

		Value& CurrentValue();
		Value& NextValue();
	public:
		ValueParser();
		virtual ~ValueParser();

		Value& GetValue();

		void OnPipeOpen() final;
		void OnPipeClose() final;
		void OnArrayBegin(const uint32_t size) final;
		void OnArrayEnd() final;
		void OnObjectBegin(const uint32_t component_count) final;
		void OnObjectEnd() final;
		void OnComponentID(const ComponentID id)  final;
		void OnComponentID(const char* str, const uint32_t size)  final;
		void OnUserPOD(const uint32_t type, const uint32_t bytes, const void* data) final;
		void OnNull() final;
		void OnPrimitiveF64(const double value) final; 
		void OnPrimitiveString(const char* value, const uint32_t length) final;
		void OnPrimitiveBool(const bool value) final;
		void OnPrimitiveC8(const char value) final;
		void OnPrimitiveU64(const uint64_t value) final;
		void OnPrimitiveS64(const int64_t value) final;
		void OnPrimitiveF32(const float value) final;
		void OnPrimitiveU8(const uint8_t value) final;
		void OnPrimitiveU16(const uint16_t value) final;
		void OnPrimitiveU32(const uint32_t value) final;
		void OnPrimitiveS8(const int8_t value) final;
		void OnPrimitiveS16(const int16_t value) final;
		void OnPrimitiveS32(const int32_t value) final;
		void OnPrimitiveF16(const half value) final;

		void OnPrimitiveArrayC8(const char* src, const uint32_t size) final;
		void OnPrimitiveArrayBool (const bool* src, const uint32_t size) final;
		void OnPrimitiveArrayU8(const uint8_t* src, const uint32_t size) final;
		void OnPrimitiveArrayU16(const uint16_t* src, const uint32_t size) final;
		void OnPrimitiveArrayU32(const uint32_t* src, const uint32_t size) final;
		void OnPrimitiveArrayU64(const uint64_t* src, const uint32_t size) final;
		void OnPrimitiveArrayS8(const int8_t* src, const uint32_t size) final;
		void OnPrimitiveArrayS16(const int16_t* src, const uint32_t size) final;
		void OnPrimitiveArrayS32(const int32_t* src, const uint32_t size) final;
		void OnPrimitiveArrayS64(const int64_t* src, const uint32_t size) final;
		void OnPrimitiveArrayF16(const half* src, const uint32_t size) final;
		void OnPrimitiveArrayF32(const float* src, const uint32_t size) final;
		void OnPrimitiveArrayF64(const double* src, const uint32_t size) final;
	};

}}

#endif
