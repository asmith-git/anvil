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
#include <future>
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
	class ANVIL_DLL_EXPORT InputPipe 
	{
	private:
		const void* _current_packet;				//!< Starting address of the current packet, null if there is no packet
		size_t _current_packet_size;		//!< The size of the current packet in bytes
		size_t _current_packet_bytes_read;	//!< How many bytes have been read from the current packet

		inline void PrepareNextPacket(const size_t bytes_requested)
		{
			if (_current_packet_bytes_read == _current_packet_size)
			{
				_current_packet = nullptr;
				_current_packet_bytes_read = 0u;
				_current_packet_size = bytes_requested;
				_current_packet = ReadNextPacket(_current_packet_size);
			}
		}

	protected:
		virtual void* ReadNextPacket(size_t& bytes) = 0;

	public:
		InputPipe(InputPipe&&) = delete;
		InputPipe(const InputPipe&) = delete;
		InputPipe& operator=(InputPipe&&) = delete;
		InputPipe& operator=(const InputPipe&) = delete;

		InputPipe();
		virtual ~InputPipe();

		/*!
		*	\brief Attempt to read bytes from the pipe
		*	\param bytes_requested The maximum number of bytes to read
		*	\param bytes_actual The number of bytes that were read from the pipe
		*	\return The bytes that were read from the pipe. This data is invalidated the next time ReadBytes or ReadBytesFromBuffer is called.
		*/
		inline const void* ReadBytesFromBuffer(const size_t bytes_requested, size_t& bytes_actual)
		{
			PrepareNextPacket(bytes_requested);

			const size_t offset = _current_packet_bytes_read;
			const size_t bytes_available = _current_packet_size - offset;
			bytes_actual = bytes_available > bytes_requested ? bytes_requested : bytes_available;
			_current_packet_bytes_read += bytes_actual;

			return static_cast<const uint8_t*>(_current_packet) + offset;
		}

		/*!
		*	\brief Attempt to read bytes from the pipe
		*	\param dst The address to write any bytes that can be read
		*	\param bytes The maximum number of bytes to read
		*	\return The number of bytes that were read from the pipe
		*/
		inline size_t ReadBytes(void* dst, const size_t bytes)
		{
			size_t bytes_read = 0u;
			const void* src = ReadBytesFromBuffer(bytes, bytes_read);
			memcpy(dst, src, bytes_read);
			return bytes_read;
		}

		std::future_status ForceReadBytes(void* dst, size_t bytes, size_t& bytes_actual, int timeout_ms = -1);

		/*!
		*	\brief Get how many bytes are immediately available for reading.
		*	\details More bytes may be available but will only be processed when ReadBytes or ReadBytesFromBuffer are called.
		*	\return The number of bytes
		*/
		inline size_t GetBufferSize() const
		{
			return _current_packet_size - _current_packet_bytes_read;
		}
	};

	/*!
		\author Adam Smtih
		\date September 2019
		\brief Interface for serialising or deserialising data.
	*/
	class ANVIL_DLL_EXPORT Parser 
	{
	public:
		Parser();
		virtual ~Parser();

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
		virtual void OnArrayBegin(const size_t size) = 0;

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
		virtual void OnObjectBegin(const size_t component_count) = 0;

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

		virtual void OnComponentID(const char* str, const size_t size) = 0;

		ANVIL_STRONG_INLINE void OnComponentID(const char* id) { OnComponentID(id, strlen(id)); }
		ANVIL_STRONG_INLINE void OnComponentID(const std::string& id) { OnComponentID(id.c_str(), id.size()); }

		/*!
			\brief Handle a user defined binary structure.
			\details This allows the user to define their own POD (plain old data) structures, which can be
			handled natively by pipes, this is faster than serialising the structure as an object.
			\param type A 24-bit ID code that describes which structure is being parsed.
			\param bytes The size of the structure in bytes.
			\param data A pointer to the structure.
		*/
		virtual void OnUserPOD(const PodType type, const size_t bytes, const void* data) = 0;

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
		virtual void OnPrimitiveString(const char* value, const size_t length) = 0;

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

#if ANVIL_F8_SUPPORT
		/*!
			\brief Handle a primitive value (8-bit floating point)
			\param value The value
		*/
		virtual void OnPrimitiveF8(const float8_t value) {
			OnPrimitiveF32(static_cast<float>(value));
		}
#endif

#if ANVIL_F16_SUPPORT
		/*!
			\brief Handle a primitive value (16-bit floating point)
			\param value The value
		*/
		virtual void OnPrimitiveF16(const float16_t value) {
			OnPrimitiveF32(static_cast<float>(value));
		}
#endif

		// Object Support

		void OnValue(const Value& value);
		void OnValue(const PrimitiveValue& value);

		// Array Optimisations

		/*!
			\brief Handle an array of primitive values (8-bit unsigned integers)
			\details This is the same as the following code, but is a special case that could be optimised :
			\code{.cpp}
			OnArrayBegin(size);
			for (size_t i = 0u; i < size; ++i) OnPrimitiveU8(src[i]);
			OnArrayEnd();
			\endcode
			\param src The address of the first value
			\param size The number of values in the array
		*/
		virtual void OnPrimitiveArrayU8(const uint8_t* src, const size_t size) {
			OnArrayBegin(size);
			for (size_t i = 0u; i < size; ++i) OnPrimitiveU8(src[i]);
			OnArrayEnd();
		}

		/*!
			\brief Handle an array of primitive values (16-bit unsigned integers)
			\details This is the same as the following code, but is a special case that could be optimised :
			\code{.cpp}
			OnArrayBegin(size);
			for (size_t i = 0u; i < size; ++i) OnPrimitiveU16(src[i]);
			OnArrayEnd();
			\endcode
			\param src The address of the first value
			\param size The number of values in the array
		*/
		virtual void OnPrimitiveArrayU16(const uint16_t* src, const size_t size) {
			OnArrayBegin(size);
			for (size_t i = 0u; i < size; ++i) OnPrimitiveU16(src[i]);
			OnArrayEnd();
		}

		/*!
			\brief Handle an array of primitive values (32-bit unsigned integers)
			\details This is the same as the following code, but is a special case that could be optimised :
			\code{.cpp}
			OnArrayBegin(size);
			for (size_t i = 0u; i < size; ++i) OnPrimitiveU32(src[i]);
			OnArrayEnd();
			\endcode
			\param src The address of the first value
			\param size The number of values in the array
		*/
		virtual void OnPrimitiveArrayU32(const uint32_t* src, const size_t size) {
			OnArrayBegin(size);
			for (size_t i = 0u; i < size; ++i) OnPrimitiveU32(src[i]);
			OnArrayEnd();
		}

		/*!
			\brief Handle an array of primitive values (64-bit unsigned integers)
			\details This is the same as the following code, but is a special case that could be optimised :
			\code{.cpp}
			OnArrayBegin(size);
			for (size_t i = 0u; i < size; ++i) OnPrimitiveU64(src[i]);
			OnArrayEnd();
			\endcode
			\param src The address of the first value
			\param size The number of values in the array
		*/
		virtual void OnPrimitiveArrayU64(const uint64_t* src, const size_t size) {
			OnArrayBegin(size);
			for (size_t i = 0u; i < size; ++i) OnPrimitiveU64(src[i]);
			OnArrayEnd();
		}

		/*!
			\brief Handle an array of primitive values (8-bit signed integers)
			\details This is the same as the following code, but is a special case that could be optimised :
			\code{.cpp}
			OnArrayBegin(size);
			for (size_t i = 0u; i < size; ++i) OnPrimitiveS8(src[i]);
			OnArrayEnd();
			\endcode
			\param src The address of the first value
			\param size The number of values in the array
		*/
		virtual void OnPrimitiveArrayS8(const int8_t* src, const size_t size) {
			OnArrayBegin(size);
			for (size_t i = 0u; i < size; ++i) OnPrimitiveS8(src[i]);
			OnArrayEnd();
		}

		/*!
			\brief Handle an array of primitive values (16-bit signed integers)
			\details This is the same as the following code, but is a special case that could be optimised :
			\code{.cpp}
			OnArrayBegin(size);
			for (size_t i = 0u; i < size; ++i) OnPrimitiveS16(src[i]);
			OnArrayEnd();
			\endcode
			\param src The address of the first value
			\param size The number of values in the array
		*/
		virtual void OnPrimitiveArrayS16(const int16_t* src, const size_t size) {
			OnArrayBegin(size);
			for (size_t i = 0u; i < size; ++i) OnPrimitiveS16(src[i]);
			OnArrayEnd();
		}

		/*!
			\brief Handle an array of primitive values (32-bit signed integers)
			\details This is the same as the following code, but is a special case that could be optimised :
			\code{.cpp}
			OnArrayBegin(size);
			for (size_t i = 0u; i < size; ++i) OnPrimitiveS32(src[i]);
			OnArrayEnd();
			\endcode
			\param src The address of the first value
			\param size The number of values in the array
		*/
		virtual void OnPrimitiveArrayS32(const int32_t* src, const size_t size) {
			OnArrayBegin(size);
			for (size_t i = 0u; i < size; ++i) OnPrimitiveS32(src[i]);
			OnArrayEnd();
		}

		/*!
			\brief Handle an array of primitive values (64-bit signed integers)
			\details This is the same as the following code, but is a special case that could be optimised :
			\code{.cpp}
			OnArrayBegin(size);
			for (size_t i = 0u; i < size; ++i) OnPrimitiveS64(src[i]);
			OnArrayEnd();
			\endcode
			\param src The address of the first value
			\param size The number of values in the array
		*/
		virtual void OnPrimitiveArrayS64(const int64_t* src, const size_t size) {
			OnArrayBegin(size);
			for (size_t i = 0u; i < size; ++i) OnPrimitiveS64(src[i]);
			OnArrayEnd();
		}

		/*!
			\brief Handle an array of primitive values (32-bit floating point)
			\details This is the same as the following code, but is a special case that could be optimised :
			\code{.cpp}
			OnArrayBegin(size);
			for (size_t i = 0u; i < size; ++i) OnPrimitiveF32(src[i]);
			OnArrayEnd();
			\endcode
			\param src The address of the first value
			\param size The number of values in the array
		*/
		virtual void OnPrimitiveArrayF32(const float* src, const size_t size) {
			OnArrayBegin(size);
			for (size_t i = 0u; i < size; ++i) OnPrimitiveF32(src[i]);
			OnArrayEnd();
		}

		/*!
			\brief Handle an array of primitive values (64-bit floating point)
			\details This is the same as the following code, but is a special case that could be optimised :
			\code{.cpp}
			OnArrayBegin(size);
			for (size_t i = 0u; i < size; ++i) OnPrimitiveF64(src[i]);
			OnArrayEnd();
			\endcode
			\param src The address of the first value
			\param size The number of values in the array
		*/
		virtual void OnPrimitiveArrayF64(const double* src, const size_t size) {
			OnArrayBegin(size);
			for (size_t i = 0u; i < size; ++i) OnPrimitiveF64(src[i]);
			OnArrayEnd();
		}

		/*!
			\brief Handle an array of primitive values (character)
			\details This is the same as the following code, but is a special case that could be optimised :
			\code{.cpp}
			OnArrayBegin(size);
			for (size_t i = 0u; i < size; ++i) OnPrimitiveC8(src[i]);
			OnArrayEnd();
			\endcode
			\param src The address of the first value
			\param size The number of values in the array
		*/
		virtual void OnPrimitiveArrayC8(const char* src, const size_t size) {
			OnArrayBegin(size);
			for (size_t i = 0u; i < size; ++i) OnPrimitiveC8(src[i]);
			OnArrayEnd();
		}

#if ANVIL_F8_SUPPORT
		/*!
			\brief Handle an array of primitive values (8-bit floating point)
			\details This is the same as the following code, but is a special case that could be optimised :
			\code{.cpp}
			OnArrayBegin(size);
			for (size_t i = 0u; i < size; ++i) OnPrimitiveF16(src[i]);
			OnArrayEnd();
			\endcode
			\param src The address of the first value
			\param size The number of values in the array
		*/
		virtual void OnPrimitiveArrayF8(const float8_t* src, const size_t size) {
			OnArrayBegin(size);
			for (size_t i = 0u; i < size; ++i) OnPrimitiveF8(src[i]);
			OnArrayEnd();
		}
#endif

#if ANVIL_F16_SUPPORT
		/*!
			\brief Handle an array of primitive values (16-bit floating point)
			\details This is the same as the following code, but is a special case that could be optimised :
			\code{.cpp}
			OnArrayBegin(size);
			for (size_t i = 0u; i < size; ++i) OnPrimitiveF16(src[i]);
			OnArrayEnd();
			\endcode
			\param src The address of the first value
			\param size The number of values in the array
		*/
		virtual void OnPrimitiveArrayF16(const float16_t* src, const size_t size) {
			OnArrayBegin(size);
			for (size_t i = 0u; i < size; ++i) OnPrimitiveF16(src[i]);
			OnArrayEnd();
		}
#endif

		/*!
			\brief Handle an array of primitive values (bool)
			\details This is the same as the following code, but is a special case that could be optimised :
			\code{.cpp}
			OnArrayBegin(size);
			for (size_t i = 0u; i < size; ++i) OnPrimitiveBool(src[i]);
			OnArrayEnd();
			\endcode
			\param src The address of the first value
			\param size The number of values in the array
		*/
		virtual void OnPrimitiveArrayBool(const bool* src, const size_t size) {
			OnArrayBegin(size);
			for (size_t i = 0u; i < size; ++i) OnPrimitiveBool(src[i]);
			OnArrayEnd();
		}

		// Template helpers

		template<class T>
		inline void OnPrimitive(const T value);

		template<class T>
		inline void OnPrimitiveArray(const T* values, const size_t size);

		// Object helper functions

		template<class T>
		ANVIL_STRONG_INLINE void OnPrimitive(const ComponentID component_id, const T value) {
			OnComponentID(component_id);
			OnPrimitive<T>(value);
		}

		template<class T>
		ANVIL_STRONG_INLINE void OnPrimitiveArray(const ComponentID component_id, const T* values, const size_t size) {
			OnComponentID(component_id);
			OnPrimitiveArray<T>(values, size);
		}

		// General helper

		ANVIL_STRONG_INLINE void OnArrayBegin(const ComponentID id, size_t size) {
			OnComponentID(id);
			OnArrayBegin(size);
		}

		ANVIL_STRONG_INLINE void OnArrayBegin(const std::string& id, size_t size) {
			OnComponentID(id);
			OnArrayBegin(size);
		}

		ANVIL_STRONG_INLINE void OnObjectBegin(const ComponentID id, size_t size) {
			OnComponentID(id);
			OnObjectBegin(size);
		}

		ANVIL_STRONG_INLINE void OnObjectBegin(const std::string& id, size_t size) {
			OnComponentID(id);
			OnObjectBegin(size);
		}

private:
		template<class T, class ...PARAMS>
		ANVIL_STRONG_INLINE void _EncodeImplement(const T& value, PARAMS... params) {
			OnValue(ValueEncoder<T>::Encode(value, params...));
		}
public:
		template<class T>
		inline void operator()(const T& value) {
			_EncodeImplement<T>(value);
		}

		template<class P1, class ...P2>
		ANVIL_STRONG_INLINE void operator()(const ComponentID first, const P1& second, P2... others) {
			OnComponentID(first);
			_EncodeImplement(second, others...);
		}

		template<class P1, class ...P2>
		ANVIL_STRONG_INLINE void operator()(const std::string& first, const P1& second, P2... others) {
			OnComponentID(first);
			_EncodeImplement(second, others...);
		}

		template<class P1, class ...P2>
		ANVIL_STRONG_INLINE void operator()(const char* first, const P1& second, P2... others) {
			OnComponentID(first);
			_EncodeImplement(second, others...);
		}

		template<class T, class P1, class ...P2>
		ANVIL_STRONG_INLINE void operator()(const T& first, const P1& second, P2... others) {
			typedef std::remove_reference<std::remove_const<T>::type>::type T2;
			if ANVIL_CONSTEXPR_FN(std::is_same<T2, ComponentID>::value || std::is_same<T2, std::string>::value || std::is_same<T2, char*>::value) {
				OnComponentID(first);
				_EncodeImplement(second, others...);
			} else {
				_EncodeImplement(first, second, others...);
			}
		}
	};

    template<> ANVIL_STRONG_INLINE void Parser::OnPrimitive<bool>(const bool value) { OnPrimitiveBool(value); }
    template<> ANVIL_STRONG_INLINE void Parser::OnPrimitiveArray<bool>(const bool* values, const size_t size) {  OnPrimitiveArrayBool(values, size); }
	template<> ANVIL_STRONG_INLINE void Parser::OnPrimitive<char>(const char value) { OnPrimitiveC8(value); }
    template<> ANVIL_STRONG_INLINE void Parser::OnPrimitiveArray<char>(const char* values, const size_t size) {  OnPrimitiveArrayC8(values, size); }
    template<> ANVIL_STRONG_INLINE void Parser::OnPrimitive<uint8_t>(const uint8_t value) { OnPrimitiveU8(value); }
    template<> ANVIL_STRONG_INLINE void Parser::OnPrimitiveArray<uint8_t>(const uint8_t* values, const size_t size) { OnPrimitiveArrayU8(values, size); }
    template<> ANVIL_STRONG_INLINE void Parser::OnPrimitive<uint16_t>(const uint16_t value) { OnPrimitiveU16(value); }
    template<> ANVIL_STRONG_INLINE void Parser::OnPrimitiveArray<uint16_t>(const uint16_t* values, const size_t size) { OnPrimitiveArrayU16(values, size); }
    template<> ANVIL_STRONG_INLINE void Parser::OnPrimitive<uint32_t>(const uint32_t value) { OnPrimitiveU32(value); }
    template<> ANVIL_STRONG_INLINE void Parser::OnPrimitiveArray<uint32_t>(const uint32_t* values, const size_t size) { OnPrimitiveArrayU32(values, size); }
    template<> ANVIL_STRONG_INLINE void Parser::OnPrimitive<uint64_t>(const uint64_t value) { OnPrimitiveU64(value); }
    template<> ANVIL_STRONG_INLINE void Parser::OnPrimitiveArray<uint64_t>(const uint64_t* values, const size_t size) { OnPrimitiveArrayU64(values, size); }
    template<> ANVIL_STRONG_INLINE void Parser::OnPrimitive<int8_t>(const int8_t value) { OnPrimitiveS8(value); }
    template<> ANVIL_STRONG_INLINE void Parser::OnPrimitiveArray<int8_t>(const int8_t* values, const size_t size) { OnPrimitiveArrayS8(values, size); }
    template<> ANVIL_STRONG_INLINE void Parser::OnPrimitive<int16_t>(const int16_t value) { OnPrimitiveS16(value); }
    template<> ANVIL_STRONG_INLINE void Parser::OnPrimitiveArray<int16_t>(const int16_t* values, const size_t size) { OnPrimitiveArrayS16(values, size); }
    template<> ANVIL_STRONG_INLINE void Parser::OnPrimitive<int32_t>(const int32_t value) { OnPrimitiveS32(value); }
    template<> ANVIL_STRONG_INLINE void Parser::OnPrimitiveArray<int32_t>(const int32_t* values, const size_t size) { OnPrimitiveArrayS32(values, size); }
    template<> ANVIL_STRONG_INLINE void Parser::OnPrimitive<int64_t>(const int64_t value) { OnPrimitiveS64(value); }
    template<> ANVIL_STRONG_INLINE void Parser::OnPrimitiveArray<int64_t>(const int64_t* values, const size_t size) { OnPrimitiveArrayS64(values, size); }
#if ANVIL_F8_SUPPORT
	template<> ANVIL_STRONG_INLINE void Parser::OnPrimitive<float8_t>(const float8_t value) { OnPrimitiveF8(value); }
	template<> ANVIL_STRONG_INLINE void Parser::OnPrimitiveArray<float8_t>(const float8_t* values, const size_t size) { OnPrimitiveArrayF8(values, size); }
#endif
#if ANVIL_F16_SUPPORT
    template<> ANVIL_STRONG_INLINE void Parser::OnPrimitive<float16_t>(const float16_t value) { OnPrimitiveF16(value); }
    template<> ANVIL_STRONG_INLINE void Parser::OnPrimitiveArray<float16_t>(const float16_t* values, const size_t size) { OnPrimitiveArrayF16(values, size); }
#endif
    template<> ANVIL_STRONG_INLINE void Parser::OnPrimitive<float>(const float value) { OnPrimitiveF32(value); }
    template<> ANVIL_STRONG_INLINE void Parser::OnPrimitiveArray<float>(const float* values, const size_t size) { OnPrimitiveArrayF32(values, size); }
    template<> ANVIL_STRONG_INLINE void Parser::OnPrimitive<double>(const double value) { OnPrimitiveF64(value); }
    template<> ANVIL_STRONG_INLINE void Parser::OnPrimitiveArray<double>(const double* values, const size_t size) { OnPrimitiveArrayF64(values, size); }

    template<> ANVIL_STRONG_INLINE void Parser::_EncodeImplement<bool>(const bool& value) { OnPrimitive<bool>(value); }
    template<> ANVIL_STRONG_INLINE void Parser::_EncodeImplement<char>(const char& value) { OnPrimitive<char>(value); }
    template<> ANVIL_STRONG_INLINE void Parser::_EncodeImplement<uint8_t>(const uint8_t& value) { OnPrimitive<uint8_t>(value); }
    template<> ANVIL_STRONG_INLINE void Parser::_EncodeImplement<uint16_t>(const uint16_t& value) { OnPrimitive<uint16_t>(value); }
    template<> ANVIL_STRONG_INLINE void Parser::_EncodeImplement<uint32_t>(const uint32_t& value) { OnPrimitive<uint32_t>(value); }
    template<> ANVIL_STRONG_INLINE void Parser::_EncodeImplement<uint64_t>(const uint64_t& value) { OnPrimitive<uint64_t>(value); }
    template<> ANVIL_STRONG_INLINE void Parser::_EncodeImplement<int8_t>(const int8_t& value) { OnPrimitive<int8_t>(value); }
    template<> ANVIL_STRONG_INLINE void Parser::_EncodeImplement<int16_t>(const int16_t& value) { OnPrimitive<int16_t>(value); }
    template<> ANVIL_STRONG_INLINE void Parser::_EncodeImplement<int32_t>(const int32_t& value) { OnPrimitive<int32_t>(value); }
    template<> ANVIL_STRONG_INLINE void Parser::_EncodeImplement<int64_t>(const int64_t& value) { OnPrimitive<int64_t>(value); }
#if ANVIL_F8_SUPPORT
	template<> ANVIL_STRONG_INLINE void Parser::_EncodeImplement<float8_t>(const float8_t& value) { OnPrimitive<float8_t>(value); }
#endif
#if ANVIL_F16_SUPPORT
    template<> ANVIL_STRONG_INLINE void Parser::_EncodeImplement<float16_t>(const float16_t& value) { OnPrimitive<float16_t>(value); }
#endif
    template<> ANVIL_STRONG_INLINE void Parser::_EncodeImplement<float>(const float& value) { OnPrimitive<float>(value); }
    template<> ANVIL_STRONG_INLINE void Parser::_EncodeImplement<double>(const double& value) { OnPrimitive<double>(value); }
    template<> ANVIL_STRONG_INLINE void Parser::_EncodeImplement<std::string>(const std::string& value) { OnPrimitiveString(value.c_str(), value.size()); }
    template<> ANVIL_STRONG_INLINE void Parser::_EncodeImplement<Value>(const Value& value) { OnValue(value); }

	/*!
		\author Adam Smtih
		\date ??? 2019
		\brief Reads binary serialised data from an InputPipe and outputs it into a Parser
		\see Writer
	*/
	class ANVIL_DLL_EXPORT Reader {
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
	class ANVIL_DLL_EXPORT ValueParser final : public Parser {
	private:
		Value _root;
		std::vector<Value*> _value_stack;
		std::string _component_id_str;

		Value& CurrentValue();
		Value& NextValue();
	public:
		ValueParser();
		virtual ~ValueParser();

		Value& GetValue();

		void OnPipeOpen() final;
		void OnPipeClose() final;
		void OnArrayBegin(const size_t size) final;
		void OnArrayEnd() final;
		void OnObjectBegin(const size_t component_count) final;
		void OnObjectEnd() final;
		void OnComponentID(const ComponentID id)  final;
		void OnComponentID(const char* str, const size_t size)  final;
		void OnUserPOD(const PodType type, const size_t bytes, const void* data) final;
		void OnNull() final;
		void OnPrimitiveF64(const double value) final;
		void OnPrimitiveString(const char* value, const size_t length) final;
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
#if ANVIL_F8_SUPPORT
		void OnPrimitiveF8(const float8_t value) final;
#endif
#if ANVIL_F16_SUPPORT
		void OnPrimitiveF16(const float16_t value) final;
#endif

		void OnPrimitiveArrayC8(const char* src, const size_t size) final;
		void OnPrimitiveArrayBool (const bool* src, const size_t size) final;
		void OnPrimitiveArrayU8(const uint8_t* src, const size_t size) final;
		void OnPrimitiveArrayU16(const uint16_t* src, const size_t size) final;
		void OnPrimitiveArrayU32(const uint32_t* src, const size_t size) final;
		void OnPrimitiveArrayU64(const uint64_t* src, const size_t size) final;
		void OnPrimitiveArrayS8(const int8_t* src, const size_t size) final;
		void OnPrimitiveArrayS16(const int16_t* src, const size_t size) final;
		void OnPrimitiveArrayS32(const int32_t* src, const size_t size) final;
		void OnPrimitiveArrayS64(const int64_t* src, const size_t size) final;
#if ANVIL_F8_SUPPORT
		void OnPrimitiveArrayF8(const float8_t* src, const size_t size) final;
#endif
#if ANVIL_F16_SUPPORT
		void OnPrimitiveArrayF16(const float16_t* src, const size_t size) final;
#endif
		void OnPrimitiveArrayF32(const float* src, const size_t size) final;
		void OnPrimitiveArrayF64(const double* src, const size_t size) final;
	};

}}

#endif
