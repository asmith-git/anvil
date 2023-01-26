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

#include <cstddef>
#include "anvil/byte-pipe/BytePipeWriter.hpp"
#include "anvil/byte-pipe/BytePipeEndian.hpp"

namespace anvil { namespace BytePipe {

	enum PrimaryID : uint8_t {
		PID_NULL,
		PID_PRIMATIVE,
		PID_STRING,
		PID_ARRAY,
		PID_OBJECT,
		PID_USER_POD
	};

	enum SecondaryID : uint8_t {
		SID_NULL,
		SID_U8,
		SID_U16,
		SID_U32,
		SID_U64,
		SID_S8,
		SID_S16,
		SID_S32,
		SID_S64,
		SID_F32,
		SID_F64,
		SID_C8,
		SID_F16,
		SID_B
	};

	// Header definitions
#pragma pack(push, 1)
	struct PipeHeaderV1 {
		uint8_t version;
	};

	struct PipeHeaderV2 {
		uint8_t version;
		struct {
			uint8_t little_endian : 1u;
			uint8_t reserved_flag1 : 1u;
			uint8_t reserved_flag2 : 1u;
			uint8_t reserved_flag3 : 1u;
			uint8_t reserved_flag4 : 1u;
			uint8_t reserved_flag5 : 1u;
			uint8_t reserved_flag6 : 1u;
			uint8_t reserved_flag7 : 1u;
		};
	};

	struct ValueHeader {
		union {
			struct {
				uint8_t primary_id : 4;
				uint8_t secondary_id : 4;
			};
			uint8_t id_union;
		};
		union {
			struct {
				uint32_t size;
			} array_v1;

			struct {
				uint32_t components;
			} object_v1;

			struct {
				uint32_t length;
			} string_v1;

			union ValueHeaderPrimitive {
				bool b;
				uint8_t u8;
				uint16_t u16;
				uint32_t u32;
				uint64_t u64;
				int8_t s8;
				int16_t s16;
				int32_t s32;
				int64_t s64;
				float f32;
				double f64;
				char c8;
				half f16;
			} primitive_v1;

			struct {
				uint16_t extended_secondary_id;
				uint32_t bytes;
			} user_pod;
		};
	};
#pragma pack(pop)

	// Compile-time error checks

	static_assert(sizeof(PipeHeaderV1) == 1u, "PipeHeaderV1 was not packed correctly by compiler");
	static_assert(sizeof(PipeHeaderV2) == 2u, "PipeHeaderV2 was not packed correctly by compiler");
	static_assert(sizeof(ValueHeader) == 9u, "ValueHeader was not packed correctly by compiler");
	static_assert(sizeof(ValueHeader::user_pod) == 6u, "ValueHeader was not packed correctly by compiler");
	static_assert(offsetof(ValueHeader, primitive_v1.u8) == 1u, "ValueHeader was not packed correctly by compiler");

	// Helper functions

	namespace detail {
		static void CallOnPrimitiveU8(Parser& parser, const PrimitiveValue& header) {
			parser.OnPrimitiveU8(header.u8);
		}

		static void CallOnPrimitiveU16(Parser& parser, const PrimitiveValue& header) {
			parser.OnPrimitiveU16(header.u16);
		}

		static void CallOnPrimitiveU32(Parser& parser, const PrimitiveValue& header) {
			parser.OnPrimitiveU32(header.u32);
		}

		static void CallOnPrimitiveU64(Parser& parser, const PrimitiveValue& header) {
			parser.OnPrimitiveU64(header.u64);
		}

		static void CallOnPrimitiveS8(Parser& parser, const PrimitiveValue& header) {
			parser.OnPrimitiveS8(header.s8);
		}

		static void CallOnPrimitiveS16(Parser& parser, const PrimitiveValue& header) {
			parser.OnPrimitiveS16(header.s16);
		}

		static void CallOnPrimitiveS32(Parser& parser, const PrimitiveValue& header) {
			parser.OnPrimitiveS32(header.s32);
		}

		static void CallOnPrimitiveS64(Parser& parser, const PrimitiveValue& header) {
			parser.OnPrimitiveS64(header.s64);
		}

		static void CallOnPrimitiveF16(Parser& parser, const PrimitiveValue& header) {
			parser.OnPrimitiveF16(header.f16);
		}

		static void CallOnPrimitiveF32(Parser& parser, const PrimitiveValue& header) {
			parser.OnPrimitiveF32(header.f32);
		}

		static void CallOnPrimitiveF64(Parser& parser, const PrimitiveValue& header) {
			parser.OnPrimitiveF64(header.f64);
		}

		static void CallOnPrimitiveC8(Parser& parser, const PrimitiveValue& header) {
			parser.OnPrimitiveC8(header.c8);
		}

		static void CallOnNull(Parser& parser, const PrimitiveValue& header) {
			parser.OnNull();
		}

		static void CallOnPrimitiveB(Parser& parser, const PrimitiveValue& header) {
			parser.OnPrimitiveBool(header.b);
		}
	}

	template<class T, class U>
	static inline uint64_t GetRaw(const T value) {
		union {
			U raw;
			T val;
		};
		if ANVIL_CONSTEXPR_VAR(sizeof(T) < sizeof(U)) raw = 0u;
		val = value;
		return raw;
	}

	template<>
	static inline uint64_t GetRaw<uint64_t, uint64_t>(const uint64_t value) {
		return value;
	}

	template<>
	static inline uint64_t GetRaw<uint32_t, uint32_t>(const uint32_t value) {
		return value;
	}

	// Helper arrays

	static ANVIL_CONSTEXPR_VAR const uint8_t g_secondary_type_sizes[] = {
		0u, // SID_NULL
		1u, // SID_U8
		2u, // SID_U16
		4u, // SID_U32
		8u, // SID_U64
		1u, // SID_S8
		2u, // SID_S16
		4u, // SID_S32
		8u, // SID_S64
		4u, // SID_F32
		8u, // SID_F64
		1u, // SID_C8
		2u, // SID_F16,
		1u // SID_B
	};

	// Convert binary primitive type ID to value type
	static ANVIL_CONSTEXPR_VAR const Type g_sid_2_object_type[] = {
		TYPE_NULL, // SID_NULL
		TYPE_U8, // SID_U8
		TYPE_U16, // SID_U16
		TYPE_U32, // SID_U32
		TYPE_U64, // SID_U64
		TYPE_S8, // SID_S8
		TYPE_S16, // SID_S16
		TYPE_S32, // SID_S32
		TYPE_S64, // SID_S64
		TYPE_F32, // SID_F32
		TYPE_F32, // SID_F64
		TYPE_C8, // SID_C8
		TYPE_F16, // SID_F16,
		TYPE_BOOL // SID_B
	};

	// Convert Value type to binary primitive type ID
	static ANVIL_CONSTEXPR_VAR const SecondaryID g_object_type_2_sid[] = {
		SID_NULL, // TYPE_NULL
		SID_C8, // TYPE_C8
		SID_U8, // TYPE_U8
		SID_U16, // TYPE_U16
		SID_U32, // TYPE_U32
		SID_U64, // TYPE_U64
		SID_S8, // TYPE_S8
		SID_S16, // TYPE_S16
		SID_S32, // TYPE_S32
		SID_S64, // TYPE_S64
		SID_F16, // TYPE_F16
		SID_F32, // TYPE_F32
		SID_F64, // TYPE_F64
		static_cast<SecondaryID>(255), // TYPE_STRING
		static_cast<SecondaryID>(255), // TYPE_ARRAY
		static_cast<SecondaryID>(255), // TYPE_OBJECT
		SID_B, // TYPE_BOOL
	};

	typedef void(Parser::*PrimitiveArrayCallback)(const void* ptr, const uint32_t size);
	static ANVIL_CONSTEXPR_VAR const PrimitiveArrayCallback g_primitive_array_callbacks[] = {
		nullptr,														// SID_NULL
		reinterpret_cast<PrimitiveArrayCallback>(&Parser::OnPrimitiveArrayU8),	// SID_U8
		reinterpret_cast<PrimitiveArrayCallback>(&Parser::OnPrimitiveArrayU16),	// SID_U16
		reinterpret_cast<PrimitiveArrayCallback>(&Parser::OnPrimitiveArrayU32),	// SID_U32
		reinterpret_cast<PrimitiveArrayCallback>(&Parser::OnPrimitiveArrayU64),	// SID_U64
		reinterpret_cast<PrimitiveArrayCallback>(&Parser::OnPrimitiveArrayS8),	// SID_S8
		reinterpret_cast<PrimitiveArrayCallback>(&Parser::OnPrimitiveArrayS16),	// SID_S16
		reinterpret_cast<PrimitiveArrayCallback>(&Parser::OnPrimitiveArrayS32),	// SID_S32
		reinterpret_cast<PrimitiveArrayCallback>(&Parser::OnPrimitiveArrayS64),	// SID_S64
		reinterpret_cast<PrimitiveArrayCallback>(&Parser::OnPrimitiveArrayF32),	// SID_F32
		reinterpret_cast<PrimitiveArrayCallback>(&Parser::OnPrimitiveArrayF64),	// SID_F64
		reinterpret_cast<PrimitiveArrayCallback>(&Parser::OnPrimitiveArrayC8),	// SID_C8
		reinterpret_cast<PrimitiveArrayCallback>(&Parser::OnPrimitiveArrayF16),	// SID_F16
		reinterpret_cast<PrimitiveArrayCallback>(&Parser::OnPrimitiveArrayBool)	// SID_B
	};


	typedef void(*PrimitiveCallback)(Parser& parser, const PrimitiveValue& header);
	static ANVIL_CONSTEXPR_VAR const PrimitiveCallback g_primitive_callbacks[] = {
		detail::CallOnNull,			// SID_NULL
		detail::CallOnPrimitiveU8,	// SID_U8
		detail::CallOnPrimitiveU16,	// SID_U16
		detail::CallOnPrimitiveU32,	// SID_U32
		detail::CallOnPrimitiveU64,	// SID_U64
		detail::CallOnPrimitiveS8,	// SID_S8
		detail::CallOnPrimitiveS16,	// SID_S16
		detail::CallOnPrimitiveS32,	// SID_S32
		detail::CallOnPrimitiveS64,	// SID_S64
		detail::CallOnPrimitiveF32,	// SID_F32
		detail::CallOnPrimitiveF64,	// SID_F64
		detail::CallOnPrimitiveC8,	// SID_C8
		detail::CallOnPrimitiveF16,	// SID_F16
		detail::CallOnPrimitiveB	// SID_B
	};

	template<class T>
	static ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID();

	template<> static ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID<void>() { return SID_NULL; }
	template<> static ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID<char>() { return SID_C8; }
	template<> static ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID<bool>() { return SID_B; }
	template<> static ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID<uint8_t>() { return SID_U8; }
	template<> static ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID<uint16_t>() { return SID_U16; }
	template<> static ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID<uint32_t>() { return SID_U32; }
	template<> static ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID<uint64_t>() { return SID_U64; }
	template<> static ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID<int8_t>() { return SID_S8; }
	template<> static ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID<int16_t>() { return SID_S16; }
	template<> static ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID<int32_t>() { return SID_S32; }
	template<> static ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID<int64_t>() { return SID_S64; }
	template<> static ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID<half>() { return SID_F16; }
	template<> static ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID<float>() { return SID_F32; }
	template<> static ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID<double>() { return SID_F64; }

	// Writer

	Writer::Writer(OutputPipe& pipe, Version version, bool swap_byte_order) :
		_pipe(pipe),
		_default_state(STATE_CLOSED),
		_version(version),
		_swap_byte_order(swap_byte_order),
		_buffer_size(0)
	{
		// Check for invalid settings
		if (_version == VERSION_1 && GetEndianness() == ENDIAN_BIG) throw std::runtime_error("Writer::Writer : Writing to big endian requires version 2 or higher");
	}

	Writer::Writer(OutputPipe& pipe, Version version) :
		Writer(pipe, version, false)
	{}

	Writer::Writer(OutputPipe& pipe) :
		Writer(pipe, VERSION_2)
	{}


	Writer::Writer(OutputPipe& pipe, Version version, Endianness endianness) :
		Writer(pipe, version, GetEndianness() != endianness)
	{}

	Writer::~Writer() {
		Write(nullptr, 0u); // Flush internal buffer
		_pipe.Flush();
	}

	Endianness Writer::GetEndianness() const {
		const Endianness e = BytePipe::GetEndianness();
		return _swap_byte_order ? (e == ENDIAN_LITTLE ? ENDIAN_BIG : ENDIAN_LITTLE) : e;
	}

	void Writer::Write(const void* src, const uint32_t bytes) {
		const auto WriteToPipe = [this](const void* src, const uint32_t bytes) {
#if ANVIL_CONTRACT_MODE == ANVIL_CONTRACT_IGNORE || ANVIL_CONTRACT_MODE == ANVIL_CONTRACT_ASSUME
			// Benchmarks showed it's about twice as fast to write to a std::ofstream without checking the number of bytes written
			// So if contracts are disabled then we wont check because the value isn't used
			_pipe.WriteBytesFast(src, bytes);
#else
			const uint32_t bytesWritten = _pipe.WriteBytes(src, bytes);
			ANVIL_CONTRACT(bytesWritten == bytes, "Failed to write to pipe");
#endif
		};

		const auto FlushBuffer = [this, &WriteToPipe]() {
			if (_buffer_size > 0u) {
				WriteToPipe(_buffer, _buffer_size);
				_buffer_size = 0u;
			}
		};

		if (src == nullptr) {
			FlushBuffer();

		} else if (bytes > BUFFER_SIZE) {
			FlushBuffer();
			WriteToPipe(src, bytes);

		} else {
			if (_buffer_size + bytes > BUFFER_SIZE) FlushBuffer();
			memcpy(_buffer + _buffer_size, src, bytes);
			_buffer_size += bytes;
		}
	}

	Writer::State Writer::GetCurrentState() const {
		return _state_stack.empty() ? _default_state : _state_stack.back();
	}

	void Writer::OnPipeOpen() {
		ANVIL_CONTRACT(_default_state == STATE_CLOSED, "BytePipe was already open");
		_default_state = STATE_NORMAL;

		union {
			PipeHeaderV1 header_v1;
			PipeHeaderV2 header_v2;
		};
		uint32_t size;

		header_v1.version = _version;
		if (_version > VERSION_1) {
			const Endianness e = GetEndianness();

			header_v2.little_endian = (_swap_byte_order ? e != ENDIAN_LITTLE : e == ENDIAN_LITTLE) ? 1u : 0u;
			header_v2.reserved_flag1 = 0u;
			header_v2.reserved_flag2 = 0u;
			header_v2.reserved_flag3 = 0u;
			header_v2.reserved_flag4 = 0u;
			header_v2.reserved_flag5 = 0u;
			header_v2.reserved_flag6 = 0u;
			header_v2.reserved_flag7 = 0u;
			size = sizeof(PipeHeaderV2);
		}else {
			size = sizeof(PipeHeaderV1);
		}
		Write(&header_v1.version, size);
	}

	void Writer::OnPipeClose() {
		ANVIL_CONTRACT(_default_state == STATE_NORMAL, "BytePipe was already closed");
		_default_state = STATE_CLOSED;

		uint8_t terminator = 0u;
		Write(&terminator, 1u);
	}

	void Writer::OnArrayBegin(const uint32_t size) {
		_state_stack.push_back(STATE_ARRAY);

		ValueHeader header;
		header.primary_id = PID_ARRAY;
		header.secondary_id = SID_NULL;
		header.array_v1.size = size;
		Write(&header, sizeof(ValueHeader::array_v1) + 1u);
	}

	void Writer::OnArrayEnd() {
		ANVIL_CONTRACT(GetCurrentState() == STATE_ARRAY, "BytePipe was not in array mode");
		_state_stack.pop_back();
	}

	void Writer::OnObjectBegin(const uint32_t components) {
		_state_stack.push_back(STATE_OBJECT);

		ValueHeader header;
		header.primary_id = PID_OBJECT;
		header.secondary_id = SID_NULL;
		header.object_v1.components = components;
		Write(&header, sizeof(ValueHeader::object_v1) + 1u);
	}

	void Writer::OnObjectEnd() {
		ANVIL_CONTRACT(GetCurrentState() == STATE_OBJECT, "BytePipe was not in object mode");
		_state_stack.pop_back();
	}

	void Writer::OnComponentID(const uint16_t id) {
		ANVIL_CONTRACT(GetCurrentState() == STATE_OBJECT, "BytePipe was not in object mode");
		Write(&id, 2u);
	}

	void Writer::OnNull() {
		ValueHeader header;
		header.primary_id = PID_PRIMATIVE;
		header.secondary_id = SID_NULL;
		Write(&header, 1u);
	}

	void Writer::_OnPrimitive32(uint32_t value, const uint8_t id) {
		const uint32_t bytes = g_secondary_type_sizes[id];
		ANVIL_ASSUME(bytes <= 4u);

		ValueHeader header;
		header.primary_id = PID_PRIMATIVE;
		header.secondary_id = id;
		header.primitive_v1.u32 = value;
		if (_swap_byte_order && bytes > 1u) {
			if (bytes == 2u) {
				header.primitive_v1.u16 = SwapByteOrder(header.primitive_v1.u16);
			} else if (bytes == 4u) {
				header.primitive_v1.u32 = SwapByteOrder(header.primitive_v1.u32);
			} else {
				throw std::runtime_error("Writer::_OnPrimitive32 : Cannot swap byte order");
			}
		}
		Write(&header, bytes + 1u);
	}

	void Writer::_OnPrimitive64(uint64_t value, const uint8_t id) {
		const uint32_t bytes = g_secondary_type_sizes[id];
		ANVIL_ASSUME(bytes <= 8u);

		ValueHeader header;
		header.primary_id = PID_PRIMATIVE;
		header.secondary_id = id;
		header.primitive_v1.u64 = value;
		if (_swap_byte_order && bytes > 1u) {
			if (bytes == 2u) {
				header.primitive_v1.u16 = SwapByteOrder(header.primitive_v1.u16);
			} else if (bytes == 4u) {
				header.primitive_v1.u32 = SwapByteOrder(header.primitive_v1.u32);
			} else if (bytes == 8u) {
				header.primitive_v1.u64 = SwapByteOrder(header.primitive_v1.u64);
			} else {
				throw std::runtime_error("Writer::_OnPrimitive64 : Cannot swap byte order");
			}
		}
		Write(&header, bytes + 1u);
	}

	void Writer::OnPrimitiveBool(const bool value) {
		typedef std::remove_const<decltype(value)>::type T;
		_OnPrimitive32(static_cast<uint32_t>(GetRaw<T, uint32_t>(value)), GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveU8(const uint8_t value) {
		typedef std::remove_const<decltype(value)>::type T;
		_OnPrimitive32(static_cast<uint32_t>(GetRaw<T, uint32_t>(value)), GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveU16(const uint16_t value) {
		typedef std::remove_const<decltype(value)>::type T;
		_OnPrimitive32(static_cast<uint32_t>(GetRaw<T, uint32_t>(value)), GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveU32(const uint32_t value) {
		typedef std::remove_const<decltype(value)>::type T;
		_OnPrimitive32(static_cast<uint32_t>(GetRaw<T, uint32_t>(value)), GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveU64(const uint64_t value) {
		typedef std::remove_const<decltype(value)>::type T;
		_OnPrimitive64(GetRaw<T, uint64_t>(value), GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveS8(const int8_t value) {
		typedef std::remove_const<decltype(value)>::type T;
		_OnPrimitive32(static_cast<uint32_t>(GetRaw<T, uint32_t>(value)), GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveS16(const int16_t value) {
		typedef std::remove_const<decltype(value)>::type T;
		_OnPrimitive32(static_cast<uint32_t>(GetRaw<T, uint32_t>(value)), GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveS32(const int32_t value) {
		typedef std::remove_const<decltype(value)>::type T;
		_OnPrimitive32(static_cast<uint32_t>(GetRaw<T, uint32_t>(value)), GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveS64(const int64_t value) {
		typedef std::remove_const<decltype(value)>::type T;
		_OnPrimitive64(GetRaw<T, uint64_t>(value), GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveF32(const float value) {
		typedef std::remove_const<decltype(value)>::type T;
		_OnPrimitive32(static_cast<uint32_t>(GetRaw<T, uint32_t>(value)), GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveF64(const double value) {
		typedef std::remove_const<decltype(value)>::type T;
		_OnPrimitive64(GetRaw<T, uint64_t>(value), GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveC8(const char value) {
		typedef std::remove_const<decltype(value)>::type T;
		_OnPrimitive32(static_cast<uint32_t>(GetRaw<T, uint32_t>(value)), GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveF16(const half value) {
		typedef std::remove_const<decltype(value)>::type T;
		_OnPrimitive32(static_cast<uint32_t>(GetRaw<T, uint32_t>(value)), GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveString(const char* value, const uint32_t length) {
		ValueHeader header;
		header.primary_id = PID_STRING;
		header.secondary_id = SID_C8;
		header.string_v1.length = length;
		Write(&header, sizeof(ValueHeader::string_v1) + 1u);
		Write(value, length);
	}

	void Writer::_OnPrimitiveArray(const void* ptr, const uint32_t size, const uint8_t id) {
		ValueHeader header;
		header.primary_id = PID_ARRAY;
		header.secondary_id = id;
		header.array_v1.size = size;
		Write(&header, sizeof(ValueHeader::array_v1) + 1u);
		const uint32_t element_bytes = g_secondary_type_sizes[id];
		ANVIL_ASSUME(element_bytes <= 8u);
		if (_swap_byte_order && element_bytes > 1u) {
			// Allocate temporary storage
			void* buffer = _alloca(size * element_bytes);

			// Copy and swap byte order
			if (element_bytes == 2u) {
				typedef uint16_t T;
				T* buffer2 = static_cast<T*>(buffer);
				for (uint32_t i = 0u; i < size; ++i) buffer2[i] = SwapByteOrder(static_cast<const T*>(ptr)[i]);
			} else if (element_bytes == 4u) {
				typedef uint32_t T;
				T* buffer2 = static_cast<T*>(buffer);
				for (uint32_t i = 0u; i < size; ++i) buffer2[i] = SwapByteOrder(static_cast<const T*>(ptr)[i]);
			} else if (element_bytes == 8u) {
				typedef uint64_t T;
				T* buffer2 = static_cast<T*>(buffer);
				for (uint32_t i = 0u; i < size; ++i) buffer2[i] = SwapByteOrder(static_cast<const T*>(ptr)[i]);
			} else {
				throw std::runtime_error("Writer::_OnPrimitiveArray : Cannot swap byte order");
			}

			// Write the swapped bytes
			Write(buffer, size * element_bytes);
		} else {
			Write(ptr, size * element_bytes);
		}
	}

	void Writer::OnPrimitiveArrayBool(const bool* ptr, const uint32_t size) {
		typedef std::remove_const<std::remove_pointer<decltype(ptr)>::type>::type T;
		_OnPrimitiveArray(ptr, size, GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveArrayU8(const uint8_t* ptr, const uint32_t size) {
		typedef std::remove_const<std::remove_pointer<decltype(ptr)>::type>::type T;
		_OnPrimitiveArray(ptr, size, GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveArrayU16(const uint16_t* ptr, const uint32_t size) {
		typedef std::remove_const<std::remove_pointer<decltype(ptr)>::type>::type T;
		_OnPrimitiveArray(ptr, size, GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveArrayU32(const uint32_t* ptr, const uint32_t size) {
		typedef std::remove_const<std::remove_pointer<decltype(ptr)>::type>::type T;
		_OnPrimitiveArray(ptr, size, GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveArrayU64(const uint64_t* ptr, const uint32_t size) {
		typedef std::remove_const<std::remove_pointer<decltype(ptr)>::type>::type T;
		_OnPrimitiveArray(ptr, size, GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveArrayS8(const int8_t* ptr, const uint32_t size) {
		typedef std::remove_const<std::remove_pointer<decltype(ptr)>::type>::type T;
		_OnPrimitiveArray(ptr, size, GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveArrayS16(const int16_t* ptr, const uint32_t size) {
		typedef std::remove_const<std::remove_pointer<decltype(ptr)>::type>::type T;
		_OnPrimitiveArray(ptr, size, GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveArrayS32(const int32_t* ptr, const uint32_t size) {
		typedef std::remove_const<std::remove_pointer<decltype(ptr)>::type>::type T;
		_OnPrimitiveArray(ptr, size, GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveArrayS64(const int64_t* ptr, const uint32_t size) {
		typedef std::remove_const<std::remove_pointer<decltype(ptr)>::type>::type T;
		_OnPrimitiveArray(ptr, size, GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveArrayF32(const float* ptr, const uint32_t size) {
		typedef std::remove_const<std::remove_pointer<decltype(ptr)>::type>::type T;
		_OnPrimitiveArray(ptr, size, GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveArrayF64(const double* ptr, const uint32_t size) {
		typedef std::remove_const<std::remove_pointer<decltype(ptr)>::type>::type T;
		_OnPrimitiveArray(ptr, size, GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveArrayC8(const char* ptr, const uint32_t size) {
		typedef std::remove_const<std::remove_pointer<decltype(ptr)>::type>::type T;
		_OnPrimitiveArray(ptr, size, GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveArrayF16(const half* ptr, const uint32_t size) {
		typedef std::remove_const<std::remove_pointer<decltype(ptr)>::type>::type T;
		_OnPrimitiveArray(ptr, size, GetSecondaryID<T>());
	}

	void Writer::OnUserPOD(const uint32_t type, const uint32_t bytes, const void* data) {
		ANVIL_CONTRACT(type <= 1048575u, "Type must be <= 1048575u");
		ValueHeader header;
		header.primary_id = PID_USER_POD;
		header.secondary_id = type & 15u;
		header.user_pod.extended_secondary_id = static_cast<uint16_t>(type >> 4u);
		header.user_pod.bytes = bytes;
		Write(&header, sizeof(ValueHeader::user_pod) + 1u);
		Write(data, bytes);
	}

	// Reader

	class ReadHelper {
	private:
		enum { BUFFER_SIZE = 1024 * 8 };
		uint8_t _buffer[BUFFER_SIZE];
		uint8_t* _buffer_head;
		InputPipe& _pipe;
		Parser& _parser;
		void* _mem;
		uint32_t _mem_bytes;
		uint32_t _buffer_size;
		bool _swap_byte_order;

		inline void ReadFromPipeRaw(void* dst, const uint32_t bytes) {
#if ANVIL_CONTRACT_MODE == ANVIL_CONTRACT_IGNORE || ANVIL_CONTRACT_MODE == ANVIL_CONTRACT_ASSUME
			_pipe.ReadBytesFast(dst, bytes);
#else
			const uint32_t bytesRead = _pipe.ReadBytes(dst, bytes);
			ANVIL_CONTRACT(bytesRead == bytes, "Failed to read from pipe");
#endif
		}

		inline void ReadFromPipeBuffered(void* dst, uint32_t bytes) {
			// If there is no data in the buffer
			if (_buffer_size == 0u) {
READ_FROM_PIPE:

				if(bytes >= BUFFER_SIZE) {
					// Read directly into the output
					ReadFromPipeRaw(dst, bytes);
				} else {
					// Read from the pipe into the buffer
					_buffer_size = _pipe.ReadBytes(_buffer, BUFFER_SIZE);
					_buffer_head = _buffer;
					goto READ_FROM_BUFFER;
				}
			} else {
READ_FROM_BUFFER:
				// Read any bytes that are in the buffer
				uint32_t bytes_to_read = bytes;
				if (bytes > _buffer_size) bytes_to_read = _buffer_size;

				memcpy(dst, _buffer_head, bytes_to_read);

				bytes -= bytes_to_read;
				_buffer_head += bytes_to_read;
				_buffer_size -= bytes_to_read;

				dst = static_cast<uint8_t*>(dst) + bytes_to_read;
				if (bytes > 0u) goto READ_FROM_PIPE;
			}
		}

		void* AllocateMemory(const uint32_t bytes) {
			if (_mem_bytes < bytes) {
				if (_mem) operator delete(_mem);
				_mem = operator new(bytes);
				ANVIL_CONTRACT(_mem != nullptr, "Failed to allocate memory");
			}
			return _mem;
		}

		void ReadObject() {
			const uint32_t size = header.object_v1.components;
			_parser.OnObjectBegin(size);
			uint16_t component_id;
			for (uint32_t i = 0u; i < size; ++i) {
				ReadFromPipeBuffered(&component_id, sizeof(component_id));
				_parser.OnComponentID(component_id);
				ReadFromPipeBuffered(&header, 1u);
				ReadGeneric();
			}
			_parser.OnObjectEnd();
		}

		inline void ReadPrimitive() {
			const uint32_t id = header.primary_id;

			// Read primitive value
			const uint32_t bytes = g_secondary_type_sizes[id];
			if(bytes > 0u) ReadFromPipeBuffered(&header.primitive_v1, g_secondary_type_sizes[id]);

			if (_swap_byte_order && bytes > 1u) {
				if (bytes == 2u) {
					header.primitive_v1.u16 = SwapByteOrder(header.primitive_v1.u16);
				} else if (bytes == 4u) {
					header.primitive_v1.u32 = SwapByteOrder(header.primitive_v1.u32);
				} else if (bytes == 8u) {
					header.primitive_v1.u64 = SwapByteOrder(header.primitive_v1.u64);
				} else {
					throw std::runtime_error("ReadHelper::ReadPrimitive : Cannot swap byte order");
				}
			}

			// Output the value
			PrimitiveValue tmp(g_sid_2_object_type[id], header.primitive_v1.u64);
			_parser.OnValue(tmp);
		}

		void ReadGeneric() {
			switch (header.primary_id) {
			case PID_NULL:
				_parser.OnNull();
				break;
			case PID_STRING:
				ANVIL_CONTRACT(header.secondary_id == SID_C8, "String subtype was not char");
				ReadFromPipeBuffered(&header.string_v1, sizeof(header.string_v1));
				{
					const uint32_t len = header.string_v1.length;
					char* const buffer = static_cast<char*>(AllocateMemory(len + 1u));
					ReadFromPipeBuffered(buffer, len);
					buffer[len] = '\0';
					_parser.OnPrimitiveString(buffer, len);
				}
				break;
			case PID_ARRAY:
				ReadFromPipeBuffered(&header.array_v1, sizeof(header.array_v1));
				ReadArray();
				break;
			case PID_OBJECT:
				ReadFromPipeBuffered(&header.object_v1, sizeof(header.object_v1));
				ReadObject();
				break;
			case PID_USER_POD:
				{
					// Construct the user POD ID number
					uint32_t id = header.user_pod.extended_secondary_id;
					id <<= 4u;
					id |= header.secondary_id;

					// Read the POD from the input pipe
					void* mem = AllocateMemory(header.user_pod.bytes);
					ReadFromPipeBuffered(mem, header.user_pod.bytes);
					//! \bug Doesn't know how to swap the byte order of a POD

					// Output the POD
					_parser.OnUserPOD(id, header.user_pod.bytes, mem);
				}
				break;
			default:
				ReadPrimitive();
				break;
			}
		}

		void ReadArray() {
			const uint32_t id = header.secondary_id;
			// If the array contains generic values
			if (id == SID_NULL) {
				const uint32_t size = header.array_v1.size;
				_parser.OnArrayBegin(size);
				for (uint32_t i = 0u; i < size; ++i) {
					ReadFromPipeBuffered(&header, 1u);
					ReadGeneric();
				}
				_parser.OnArrayEnd();

			// The array contains primitives of the same type
			} else {
				ANVIL_CONTRACT(id <= SID_B, "Unknown secondary type ID");

				const uint32_t size = header.array_v1.size;
				const uint32_t element_bytes = g_secondary_type_sizes[id];
				const uint32_t bytes = element_bytes * size;
				void* buffer = buffer = AllocateMemory(bytes);
				ReadFromPipeBuffered(buffer, bytes);
				if (_swap_byte_order && element_bytes > 1u) {
					if (bytes == 2u) {
						typedef uint16_t T;
						T* buffer2 = static_cast<T*>(buffer);
						for (uint32_t i = 0u; i < size; ++i) buffer2[i] = SwapByteOrder(buffer2[i]);
					} else if (bytes == 4u) {
						typedef uint32_t T;
						T* buffer2 = static_cast<T*>(buffer);
						for (uint32_t i = 0u; i < size; ++i) buffer2[i] = SwapByteOrder(buffer2[i]);
					} else if (bytes == 8u) {
						typedef uint64_t T;
						T* buffer2 = static_cast<T*>(buffer);
						for (uint32_t i = 0u; i < size; ++i) buffer2[i] = SwapByteOrder(buffer2[i]);
					} else {
						throw std::runtime_error("ReadHelper::ReadArray : Cannot swap byte order");
					}
				}
				(_parser.*g_primitive_array_callbacks[id])(buffer, size);
			}
		}
	public:
		ValueHeader header;

		ReadHelper(InputPipe& pipe, Parser& parser, Version version, const bool swap_byte_order) :
			_pipe(pipe),
			_parser(parser),
			_mem(nullptr),
			_mem_bytes(0u),
			_swap_byte_order(swap_byte_order),
			_buffer_size(0u)
		{}

		~ReadHelper() {
			if (_mem) operator delete(_mem);
		}

		void Read() {
			// Continue with read
			ReadFromPipeBuffered(&header.id_union, 1u);
			while (header.id_union != PID_NULL) {
				ReadGeneric();
				ReadFromPipeBuffered(&header.id_union, 1u);
			}
		}
	};

	Reader::Reader(InputPipe& pipe) :
		_pipe(pipe)
	{}

	Reader::~Reader() {

	}

	void Reader::Read(Parser& dst) {
		// Read the version from the header
		union {
			PipeHeaderV1 header_v1;
			PipeHeaderV2 header_v2;
		};
		_pipe.ReadBytesFast(&header_v1, sizeof(PipeHeaderV1));

		// Check for unsupported version
		if (header_v1.version > VERSION_2) throw std::runtime_error("Reader::Read : BytePipe version not supported");

		// Read additional header data
		bool swap_byte_order;
		const Endianness e = GetEndianness();
		if (header_v1.version == VERSION_1) {
			// Version 1 only supports little endian
			swap_byte_order = e != ENDIAN_LITTLE;
		} else {
			// Read the version 2 header info
			_pipe.ReadBytesFast(reinterpret_cast<uint8_t*>(&header_v2) + sizeof(PipeHeaderV1), sizeof(PipeHeaderV2) - sizeof(PipeHeaderV1));
			swap_byte_order = e != (header_v2.little_endian ? ENDIAN_LITTLE : ENDIAN_BIG);

			// These header options are not defined yet
			if(header_v2.reserved_flag1 || header_v2.reserved_flag2 || header_v2.reserved_flag3 || header_v2.reserved_flag4 || header_v2.reserved_flag5 ||
				header_v2.reserved_flag5 || header_v2.reserved_flag6 || header_v2.reserved_flag7)
				throw std::runtime_error("Reader::Read : BytePipe version not supported");
		}


		// Select correct reader for pipe version
		ReadHelper helper(_pipe, dst, static_cast<Version>(header_v1.version), swap_byte_order);
		helper.Read();
	}

	// ValueParser

	ValueParser::ValueParser() {
		
	}

	ValueParser::~ValueParser() {
		
	}

	Value& ValueParser::GetValue() {
		return _root;
	}

	void ValueParser::OnPipeOpen() {
		_value_stack.clear();
		_root.SetNull();
	}

	void ValueParser::OnPipeClose() {
		_value_stack.clear();
		_root.SetNull();
	}

	void ValueParser::OnArrayBegin(const uint32_t size) {
		Value& val = NextValue();
		val.SetArray();
		_value_stack.push_back(&val);
	}

	void ValueParser::OnArrayEnd() {
		_value_stack.pop_back();
	}

	void ValueParser::OnObjectBegin(const uint32_t component_count) {
		Value& val = NextValue();
		val.SetObject();
		_value_stack.push_back(&val);
	}

	void ValueParser::OnObjectEnd() {
		_value_stack.pop_back();
	}

	void ValueParser::OnComponentID(const ComponentID id) {
		_component_id = id;
	}

	void ValueParser::OnUserPOD(const uint32_t type, const uint32_t bytes, const void* data) {
		throw std::runtime_error("ValueParser::OnUserPOD : Pods not supported");
	}

	void ValueParser::OnNull() {
		NextValue().SetNull();
	}

	void ValueParser::OnPrimitiveF64(const double value) {
		NextValue().SetF64(value);
	}

	void ValueParser::OnPrimitiveString(const char* value, const uint32_t length) {
		// Zero terminate string
		char* str = static_cast<char*>(operator new(length + 1));
		memcpy(str, value, length);
		str[length] = '\0';

		try {
			Value& val = NextValue();
			val.SetString(str);
		} catch (...) {
			operator delete(str);
			std::rethrow_exception(std::current_exception());
		}
		operator delete(str);
	}

	void ValueParser::OnPrimitiveC8(const char value) {
		NextValue().SetC8(value);
	}

	void ValueParser::OnPrimitiveU64(const uint64_t value) {
		NextValue().SetU64(value);
	}

	void ValueParser::OnPrimitiveS64(const int64_t value) {
		NextValue().SetS64(value);
	}

	void ValueParser::OnPrimitiveF32(const float value) {
		NextValue().SetF32(value);
	}

	void ValueParser::OnPrimitiveU8(const uint8_t value) {
		NextValue().SetU8(value);
	}

	void ValueParser::OnPrimitiveU16(const uint16_t value) {
		NextValue().SetU16(value);
	}

	void ValueParser::OnPrimitiveU32(const uint32_t value) {
		NextValue().SetU32(value);
	}

	void ValueParser::OnPrimitiveS8(const int8_t value) {
		NextValue().SetS8(value);
	}

	void ValueParser::OnPrimitiveS16(const int16_t value) {
		NextValue().SetS16(value);
	}

	void ValueParser::OnPrimitiveS32(const int32_t value) {
		NextValue().SetS32(value);
	}

	void ValueParser::OnPrimitiveF16(const half value) {
		NextValue().SetF16(value);
	}

	void ValueParser::OnPrimitiveBool(const bool value) {
		NextValue().SetBool(value);
	}

	void ValueParser::OnPrimitiveArrayC8(const char* src, const uint32_t size) {
		Value& v = NextValue();
		v.SetPrimitiveArray(TYPE_C8);

		//! \todo optimise
		for (uint32_t i = 0u; i < size; ++i) {
			v.AddValue(src[i]);
		}
	}

	void ValueParser::OnPrimitiveArrayBool(const bool* src, const uint32_t size) {
		Value& v = NextValue();
		v.SetPrimitiveArray(TYPE_BOOL);

		//! \todo optimise
		for (uint32_t i = 0u; i < size; ++i) {
			v.AddValue(src[i]);
		}
	}

	void ValueParser::OnPrimitiveArrayU8(const uint8_t* src, const uint32_t size) {
		Value& v = NextValue();
		v.SetPrimitiveArray(TYPE_U8);

		//! \todo optimise
		for (uint32_t i = 0u; i < size; ++i) {
			v.AddValue(src[i]);
		}
	}

	void ValueParser::OnPrimitiveArrayU16(const uint16_t* src, const uint32_t size) {
		Value& v = NextValue();
		v.SetPrimitiveArray(TYPE_U16);

		//! \todo optimise
		for (uint32_t i = 0u; i < size; ++i) {
			v.AddValue(src[i]);
		}
	}

	void ValueParser::OnPrimitiveArrayU32(const uint32_t* src, const uint32_t size) {
		Value& v = NextValue();
		v.SetPrimitiveArray(TYPE_U32);

		//! \todo optimise
		for (uint32_t i = 0u; i < size; ++i) {
			v.AddValue(src[i]);
		}
	}

	void ValueParser::OnPrimitiveArrayU64(const uint64_t* src, const uint32_t size) {
		Value& v = NextValue();
		v.SetPrimitiveArray(TYPE_U64);

		//! \todo optimise
		for (uint32_t i = 0u; i < size; ++i) {
			v.AddValue(src[i]);
		}
	}

	void ValueParser::OnPrimitiveArrayS8(const int8_t* src, const uint32_t size) {
		Value& v = NextValue();
		v.SetPrimitiveArray(TYPE_S8);

		//! \todo optimise
		for (uint32_t i = 0u; i < size; ++i) {
			v.AddValue(src[i]);
		}
	}

	void ValueParser::OnPrimitiveArrayS16(const int16_t* src, const uint32_t size) {
		Value& v = NextValue();
		v.SetPrimitiveArray(TYPE_S16);

		//! \todo optimise
		for (uint32_t i = 0u; i < size; ++i) {
			v.AddValue(src[i]);
		}
	}

	void ValueParser::OnPrimitiveArrayS32(const int32_t* src, const uint32_t size) {
		Value& v = NextValue();
		v.SetPrimitiveArray(TYPE_S32);

		//! \todo optimise
		for (uint32_t i = 0u; i < size; ++i) {
			v.AddValue(src[i]);
		}
	}

	void ValueParser::OnPrimitiveArrayS64(const int64_t* src, const uint32_t size) {
		Value& v = NextValue();
		v.SetPrimitiveArray(TYPE_S64);

		//! \todo optimise
		for (uint32_t i = 0u; i < size; ++i) {
			v.AddValue(src[i]);
		}
	}

	void ValueParser::OnPrimitiveArrayF16(const half* src, const uint32_t size) {
		Value& v = NextValue();
		v.SetPrimitiveArray(TYPE_F16);

		//! \todo optimise
		for (uint32_t i = 0u; i < size; ++i) {
			v.AddValue(src[i]);
		}
	}

	void ValueParser::OnPrimitiveArrayF32(const float* src, const uint32_t size) {
		Value& v = NextValue();
		v.SetPrimitiveArray(TYPE_F32);

		//! \todo optimise
		for (uint32_t i = 0u; i < size; ++i) {
			v.AddValue(src[i]);
		}
	}

	void ValueParser::OnPrimitiveArrayF64(const double* src, const uint32_t size) {
		Value& v = NextValue();
		v.SetPrimitiveArray(TYPE_F64);

		//! \todo optimise
		for (uint32_t i = 0u; i < size; ++i) {
			v.AddValue(src[i]);
		}
	}


	Value& ValueParser::CurrentValue() {
		return _value_stack.empty() ? _root : *_value_stack.back();
	}

	Value& ValueParser::NextValue() {
		Value& val = CurrentValue();
		switch (val.GetType()) {
		case TYPE_ARRAY:
			{
				Value tmp;
				val.AddValue(std::move(tmp));
				return val.GetValue(val.GetSize() - 1);
			}
			break;
		case TYPE_OBJECT:
			{
				Value tmp;
				val.AddValue(_component_id, std::move(tmp));
				return val.GetValue(_component_id);
			}
			break;
		default:
			return val;
		}
	}

	// Parser

	void Parser::OnValue(const Value& value) {
		switch (value.GetType()) {
		case TYPE_STRING:
			{
				const char* str = const_cast<Value&>(value).GetString();
				OnPrimitiveString(str, static_cast<uint32_t>(strlen(str)));
			}
			break;
		case TYPE_ARRAY:
			{
				const uint32_t size = static_cast<uint32_t>(value.GetSize());
				if (value.IsPrimitiveArray()) {
					switch (value.GetPrimitiveArrayType()) {
					case TYPE_C8:
						OnPrimitiveArrayC8(static_cast<const char*>(const_cast<Value&>(value).GetPrimitiveArray()), size);
						break;
					case TYPE_U8:
						OnPrimitiveArrayU8(static_cast<const uint8_t*>(const_cast<Value&>(value).GetPrimitiveArray()), size);
						break;
					case TYPE_U16:
						OnPrimitiveArrayU16(static_cast<const uint16_t*>(const_cast<Value&>(value).GetPrimitiveArray()), size);
						break;
					case TYPE_U32:
						OnPrimitiveArrayU32(static_cast<const uint32_t*>(const_cast<Value&>(value).GetPrimitiveArray()), size);
						break;
					case TYPE_U64:
						OnPrimitiveArrayU64(static_cast<const uint64_t*>(const_cast<Value&>(value).GetPrimitiveArray()), size);
						break;
					case TYPE_S8:
						OnPrimitiveArrayS8(static_cast<const int8_t*>(const_cast<Value&>(value).GetPrimitiveArray()), size);
						break;
					case TYPE_S16:
						OnPrimitiveArrayS16(static_cast<const int16_t*>(const_cast<Value&>(value).GetPrimitiveArray()), size);
						break;
					case TYPE_S32:
						OnPrimitiveArrayS32(static_cast<const int32_t*>(const_cast<Value&>(value).GetPrimitiveArray()), size);
						break;
					case TYPE_S64:
						OnPrimitiveArrayS64(static_cast<const int64_t*>(const_cast<Value&>(value).GetPrimitiveArray()), size);
						break;
					case TYPE_F16:
						OnPrimitiveArrayF16(static_cast<const half*>(const_cast<Value&>(value).GetPrimitiveArray()), size);
						break;
					case TYPE_F32:
						OnPrimitiveArrayF32(static_cast<const float*>(const_cast<Value&>(value).GetPrimitiveArray()), size);
						break;
					case TYPE_F64:
						OnPrimitiveArrayF64(static_cast<const double*>(const_cast<Value&>(value).GetPrimitiveArray()), size);
						break;
					case TYPE_BOOL:
						OnPrimitiveArrayBool(static_cast<const bool*>(const_cast<Value&>(value).GetPrimitiveArray()), size);
						break;
					}
				} else {
					OnArrayBegin(size);
					for (size_t i = 0u; i < size; ++i) {
						OnValue(const_cast<Value&>(value).GetValue(i));
					}
					OnArrayEnd();
				}
			}
			break;
		case TYPE_OBJECT:
			{
				const uint32_t size = static_cast<uint32_t>(value.GetSize());
				OnObjectBegin(size);
				for (uint32_t i = 0u; i < size; ++i) {
					const ComponentID id = value.GetComponentID(i);
					OnComponentID(id);
					OnValue(const_cast<Value&>(value).GetValue(id));
				}
				OnObjectEnd();
			}
			break;
		default:
			OnValue(value.GetPrimitiveValue());
			break;
		}
	}

	void Parser::OnValue(const PrimitiveValue& value) {
		const SecondaryID id = g_object_type_2_sid[value.type];
		ANVIL_CONTRACT(id <= SID_B, "PrimitiveCallbackHelper : Unknown primitive type");
		g_primitive_callbacks[id](*this, value);
	}

}}