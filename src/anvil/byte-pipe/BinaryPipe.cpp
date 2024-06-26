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
#if ANVIL_OPENCV_SUPPORT
#include<opencv2/opencv.hpp>
#endif

namespace anvil { namespace BytePipe {

	//static float GetTimeMS() {
	//	static const uint64_t g_reference_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	//	return static_cast<float>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - g_reference_time) / 1000000.f;
	//}	
	
	static uint64_t GetTimeMSUint() {
		static const uint64_t g_reference_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		return static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - g_reference_time) / 1000000ull;
	}

	enum IDMode : uint8_t {
		ID_U16,
		ID_STR
	};

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
		SID_B,
		SID_F8
	};

	// Header definitions
#pragma pack(push, 1)
	struct PipeHeaderV1 {
		uint8_t version;
	};

	static_assert(sizeof(PipeHeaderV1) == 1, "Expected PipeHeaderV1 to be 1 byte");
	
	#pragma warning( disable : 4201) // Unnamed struct. Should be fine as layout is checked by static asserts
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

	static_assert(sizeof(PipeHeaderV2) == 2, "Expected PipeHeaderV2 to be 2 bytes");
	static_assert(offsetof(PipeHeaderV2, version) == 0, "Memory layout of PipeHeaderV2 is different than expected");

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

			union {
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
#if ANVIL_F8_SUPPORT
				float8_t f8;
#endif
#if ANVIL_F16_SUPPORT
				float16_t f16;
#endif
			} primitive_v1;

			struct {
				uint16_t extended_secondary_id;
				uint32_t bytes;
			} user_pod;
		};
	};

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
#if ANVIL_F8_SUPPORT
		float16_t f8;
#endif
#if ANVIL_F16_SUPPORT
        float16_t f16;
#endif
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
		
		#pragma warning( disable : 4100) // Header is not used, name is retained to improve code readability
		static void CallOnNull(Parser& parser, const PrimitiveValue& header) {
			parser.OnNull();
		}

		static void CallOnPrimitiveB(Parser& parser, const PrimitiveValue& header) {
			parser.OnPrimitiveBool(header.b);
		}
	}

	template<class T, class U>
	ANVIL_STRONG_INLINE uint64_t GetRaw(const T value) {
		union {
			U raw;
			T val;
		};
		if ANVIL_CONSTEXPR_VAR(sizeof(T) < sizeof(U)) raw = 0u;
		val = value;
		return raw;
	}

	template<>
	ANVIL_STRONG_INLINE uint64_t GetRaw<uint64_t, uint64_t>(const uint64_t value) {
		return value;
	}

	template<>
	ANVIL_STRONG_INLINE uint64_t GetRaw<uint32_t, uint32_t>(const uint32_t value) {
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

	typedef void(Parser::*PrimitiveArrayCallback)(const void* ptr, const size_t size);
	typedef void(*PrimitiveCallback)(Parser& parser, const PrimitiveValue& header);

#if ANVIL_COMPILER == ANVIL_MSVC

	ANVIL_STRONG_INLINE PrimitiveArrayCallback GetPrimitiveArrayCallback(const SecondaryID id) {
		static ANVIL_CONSTEXPR_VAR const PrimitiveArrayCallback g_primitive_array_callbacks[] = {
			nullptr,						// SID_NULL
			(PrimitiveArrayCallback)(&Parser::OnPrimitiveArrayU8),	// SID_U8
			(PrimitiveArrayCallback)(&Parser::OnPrimitiveArrayU16),	// SID_U16
			(PrimitiveArrayCallback)(&Parser::OnPrimitiveArrayU32),	// SID_U32
			(PrimitiveArrayCallback)(&Parser::OnPrimitiveArrayU64),	// SID_U64
			(PrimitiveArrayCallback)(&Parser::OnPrimitiveArrayS8),	// SID_S8
			(PrimitiveArrayCallback)(&Parser::OnPrimitiveArrayS16),	// SID_S16
			(PrimitiveArrayCallback)(&Parser::OnPrimitiveArrayS32),	// SID_S32
			(PrimitiveArrayCallback)(&Parser::OnPrimitiveArrayS64),	// SID_S64
			(PrimitiveArrayCallback)(&Parser::OnPrimitiveArrayF32),	// SID_F32
			(PrimitiveArrayCallback)(&Parser::OnPrimitiveArrayF64),	// SID_F64
			(PrimitiveArrayCallback)(&Parser::OnPrimitiveArrayC8),	// SID_C8
			(PrimitiveArrayCallback)(&Parser::OnPrimitiveArrayF16),	// SID_F16
			(PrimitiveArrayCallback)(&Parser::OnPrimitiveArrayBool)	// SID_B
		};

		return g_primitive_array_callbacks[id];
	}

#else
	PrimitiveArrayCallback GetPrimitiveArrayCallback(const SecondaryID id) {
		switch (id) {
		case SID_U8: return reinterpret_cast<PrimitiveArrayCallback>(&Parser::OnPrimitiveArrayU8);	// SID_U8
		case SID_U16: return reinterpret_cast<PrimitiveArrayCallback>(&Parser::OnPrimitiveArrayU16);	// SID_U16
		case SID_U32: return reinterpret_cast<PrimitiveArrayCallback>(&Parser::OnPrimitiveArrayU32);	// SID_U32
		case SID_U64: return reinterpret_cast<PrimitiveArrayCallback>(&Parser::OnPrimitiveArrayU64);	// SID_U64
		case SID_S8: return reinterpret_cast<PrimitiveArrayCallback>(&Parser::OnPrimitiveArrayS8);	// SID_S8
		case SID_S16: return reinterpret_cast<PrimitiveArrayCallback>(&Parser::OnPrimitiveArrayS16);	// SID_S16
		case SID_S32: return reinterpret_cast<PrimitiveArrayCallback>(&Parser::OnPrimitiveArrayS32);	// SID_S32
		case SID_S64: return reinterpret_cast<PrimitiveArrayCallback>(&Parser::OnPrimitiveArrayS64);	// SID_S64
		case SID_F32: return reinterpret_cast<PrimitiveArrayCallback>(&Parser::OnPrimitiveArrayF32);	// SID_F32
		case SID_F64: return reinterpret_cast<PrimitiveArrayCallback>(&Parser::OnPrimitiveArrayF64);	// SID_F64
		case SID_C8: return reinterpret_cast<PrimitiveArrayCallback>(&Parser::OnPrimitiveArrayC8);	// SID_C8
		case SID_F16: return reinterpret_cast<PrimitiveArrayCallback>(&Parser::OnPrimitiveArrayF16);	// SID_F16
		case SID_B: return reinterpret_cast<PrimitiveArrayCallback>(&Parser::OnPrimitiveArrayBool);	// SID_B
		default: return nullptr;
		}
	}
#endif


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
	ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID();

	template<> ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID<void>() { return SID_NULL; }
	template<> ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID<char>() { return SID_C8; }
	template<> ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID<bool>() { return SID_B; }
	template<> ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID<uint8_t>() { return SID_U8; }
	template<> ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID<uint16_t>() { return SID_U16; }
	template<> ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID<uint32_t>() { return SID_U32; }
	template<> ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID<uint64_t>() { return SID_U64; }
	template<> ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID<int8_t>() { return SID_S8; }
	template<> ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID<int16_t>() { return SID_S16; }
	template<> ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID<int32_t>() { return SID_S32; }
	template<> ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID<int64_t>() { return SID_S64; }
#if ANVIL_F8_SUPPORT
	template<> ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID<float8_t>() { return SID_F8; }
#endif
#if ANVIL_F16_SUPPORT
	template<> ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID<float16_t>() { return SID_F16; }
#endif
	template<> ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID<float>() { return SID_F32; }
	template<> ANVIL_CONSTEXPR_FN SecondaryID GetSecondaryID<double>() { return SID_F64; }

	// Writer

	Writer::Writer(OutputPipe& pipe, Version version, bool swap_byte_order) :
		_pipe(pipe),
		_default_state(STATE_CLOSED),
		_version(version),
		_swap_byte_order(swap_byte_order),
		_buffer_size(0)
	{
		memset(_buffer, 0, sizeof(_buffer));

		// Check for invalid settings
		if (_version == VERSION_1 && GetEndianness() == ENDIAN_BIG) throw std::runtime_error("Writer::Writer : Writing to big endian requires version 2 or higher");
	}

	Writer::Writer(OutputPipe& pipe, Version version) :
		Writer(pipe, version, false)
	{}

	Writer::Writer(OutputPipe& pipe) :
		Writer(pipe, VERSION_3)
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

	void Writer::Write(const void* src, const size_t bytes) {
		const auto WriteToPipe = [this](const void* src, const size_t bytes) {
#if ANVIL_CONTRACT_MODE == ANVIL_CONTRACT_IGNORE || ANVIL_CONTRACT_MODE == ANVIL_CONTRACT_ASSUME
			// Benchmarks showed it's about twice as fast to write to a std::ofstream without checking the number of bytes written
			// So if contracts are disabled then we wont check because the value isn't used
			_pipe.WriteBytesFast(src, bytes);
#else
			size_t bytesWritten = bytes;
			_pipe.WriteBytes(src, bytesWritten);
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
			_buffer_size += static_cast<uint8_t>(bytes);
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

	void Writer::OnArrayBegin(const size_t size) {
		_state_stack.push_back(STATE_ARRAY);

		ValueHeader header;
		header.primary_id = PID_ARRAY;
		header.secondary_id = SID_NULL;
		header.array_v1.size = static_cast<uint32_t>(size);
		Write(&header, sizeof(ValueHeader::array_v1) + 1u);
	}

	void Writer::OnArrayEnd() {
		ANVIL_CONTRACT(GetCurrentState() == STATE_ARRAY, "BytePipe was not in array mode");
		_state_stack.pop_back();
	}

	void Writer::OnObjectBegin(const size_t components) {
		_state_stack.push_back(STATE_OBJECT);

		ValueHeader header;
		header.primary_id = PID_OBJECT;
		header.secondary_id = SID_NULL;
		header.object_v1.components = static_cast<uint32_t>(components);
		Write(&header, sizeof(ValueHeader::object_v1) + 1u);
	}

	void Writer::OnObjectEnd() {
		ANVIL_CONTRACT(GetCurrentState() == STATE_OBJECT, "BytePipe was not in object mode");
		_state_stack.pop_back();
	}

	void Writer::OnComponentID(const uint16_t id) {
		ANVIL_CONTRACT(GetCurrentState() == STATE_OBJECT, "BytePipe was not in object mode");
		IDMode mode = ID_U16;
		Write(&mode, 1u);
		Write(&id, 2u);
	}

	void Writer::OnComponentID(const char* str, const size_t size) {
		ANVIL_CONTRACT(GetCurrentState() == STATE_OBJECT, "BytePipe was not in object mode");
		IDMode mode = ID_STR;
		Write(&mode, 1u);
		OnPrimitiveString(str, size);
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
		const size_t bytes = g_secondary_type_sizes[id];
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

#if ANVIL_F8_SUPPORT
	void Writer::OnPrimitiveF8(const float8_t value) {
		typedef std::remove_const<decltype(value)>::type T;
		_OnPrimitive32(static_cast<uint32_t>(GetRaw<T, uint32_t>(value)), GetSecondaryID<T>());
	}
#endif

#if ANVIL_F16_SUPPORT
	void Writer::OnPrimitiveF16(const float16_t value) {
		typedef std::remove_const<decltype(value)>::type T;
		_OnPrimitive32(static_cast<uint32_t>(GetRaw<T, uint32_t>(value)), GetSecondaryID<T>());
	}
#endif

	void Writer::OnPrimitiveString(const char* value, const size_t length) {
		ValueHeader header;
		header.primary_id = PID_STRING;
		header.secondary_id = SID_C8;
		header.string_v1.length = static_cast<uint32_t>(length);
		Write(&header, sizeof(ValueHeader::string_v1) + 1u);
		Write(value, length);
	}

	void Writer::_OnPrimitiveArray(const void* ptr, const size_t size, const uint8_t id) {
		ValueHeader header;
		header.primary_id = PID_ARRAY;
		header.secondary_id = id;
		header.array_v1.size = static_cast<uint32_t>(size);
		Write(&header, sizeof(ValueHeader::array_v1) + 1u);
		const uint32_t element_bytes = g_secondary_type_sizes[id];
		ANVIL_ASSUME(element_bytes <= 8u);
		if (_swap_byte_order && element_bytes > 1u) {
			// Allocate temporary storage
			void* buffer = _malloca(size * element_bytes);
			ANVIL_RUNTIME_ASSERT(buffer != nullptr, "Writer::_OnPrimitiveArray : Failed to allocate buffer");

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
			_freea(buffer);
		} else {
			Write(ptr, size * element_bytes);
		}
	}

	void Writer::OnPrimitiveArrayBool(const bool* ptr, const size_t size) {
		typedef std::remove_const<std::remove_pointer<decltype(ptr)>::type>::type T;
		_OnPrimitiveArray(ptr, size, GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveArrayU8(const uint8_t* ptr, const size_t size) {
		typedef std::remove_const<std::remove_pointer<decltype(ptr)>::type>::type T;
		_OnPrimitiveArray(ptr, size, GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveArrayU16(const uint16_t* ptr, const size_t size) {
		typedef std::remove_const<std::remove_pointer<decltype(ptr)>::type>::type T;
		_OnPrimitiveArray(ptr, size, GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveArrayU32(const uint32_t* ptr, const size_t size) {
		typedef std::remove_const<std::remove_pointer<decltype(ptr)>::type>::type T;
		_OnPrimitiveArray(ptr, size, GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveArrayU64(const uint64_t* ptr, const size_t size) {
		typedef std::remove_const<std::remove_pointer<decltype(ptr)>::type>::type T;
		_OnPrimitiveArray(ptr, size, GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveArrayS8(const int8_t* ptr, const size_t size) {
		typedef std::remove_const<std::remove_pointer<decltype(ptr)>::type>::type T;
		_OnPrimitiveArray(ptr, size, GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveArrayS16(const int16_t* ptr, const size_t size) {
		typedef std::remove_const<std::remove_pointer<decltype(ptr)>::type>::type T;
		_OnPrimitiveArray(ptr, size, GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveArrayS32(const int32_t* ptr, const size_t size) {
		typedef std::remove_const<std::remove_pointer<decltype(ptr)>::type>::type T;
		_OnPrimitiveArray(ptr, size, GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveArrayS64(const int64_t* ptr, const size_t size) {
		typedef std::remove_const<std::remove_pointer<decltype(ptr)>::type>::type T;
		_OnPrimitiveArray(ptr, size, GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveArrayF32(const float* ptr, const size_t size) {
		typedef std::remove_const<std::remove_pointer<decltype(ptr)>::type>::type T;
		_OnPrimitiveArray(ptr, size, GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveArrayF64(const double* ptr, const size_t size) {
		typedef std::remove_const<std::remove_pointer<decltype(ptr)>::type>::type T;
		_OnPrimitiveArray(ptr, size, GetSecondaryID<T>());
	}

	void Writer::OnPrimitiveArrayC8(const char* ptr, const size_t size) {
		typedef std::remove_const<std::remove_pointer<decltype(ptr)>::type>::type T;
		_OnPrimitiveArray(ptr, size, GetSecondaryID<T>());
	}

#if ANVIL_F8_SUPPORT
	void Writer::OnPrimitiveArrayF8(const float8_t * ptr, const size_t size) {
		typedef std::remove_const<std::remove_pointer<decltype(ptr)>::type>::type T;
		_OnPrimitiveArray(ptr, size, GetSecondaryID<T>());
	}
#endif

#if ANVIL_F16_SUPPORT
	void Writer::OnPrimitiveArrayF16(const float16_t* ptr, const size_t size) {
		typedef std::remove_const<std::remove_pointer<decltype(ptr)>::type>::type T;
		_OnPrimitiveArray(ptr, size, GetSecondaryID<T>());
	}
#endif

	void Writer::OnUserPOD(const PodType type, const size_t bytes, const void* data) {
		ANVIL_CONTRACT(type <= 1048575u, "Type must be <= 1048575u");
		ValueHeader header;
		header.primary_id = PID_USER_POD;
		header.secondary_id = type & 15u;
		header.user_pod.extended_secondary_id = static_cast<uint16_t>(type >> 4u);
		header.user_pod.bytes = static_cast<uint32_t>(bytes);
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
		Version _version;
		bool _swap_byte_order;

		inline void ReadFromPipeRaw(void* dst, const uint32_t bytes) {
#if ANVIL_CONTRACT_MODE == ANVIL_CONTRACT_IGNORE || ANVIL_CONTRACT_MODE == ANVIL_CONTRACT_ASSUME
			_pipe.ForceReadBytes(dst, bytes, 10000);
#else
			const size_t bytesRead = _pipe.ReadBytes(dst, bytes);
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
					_buffer_size = static_cast<uint32_t>(_pipe.ReadBytes(_buffer, BUFFER_SIZE));
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

		char* ReadString(uint32_t& len) {
			ANVIL_CONTRACT(header.secondary_id == SID_C8, "String subtype was not char");
			ReadFromPipeBuffered(&header.string_v1, sizeof(header.string_v1));

			len = header.string_v1.length;
			char* const buffer = static_cast<char*>(AllocateMemory(len + 1u));
			ReadFromPipeBuffered(buffer, len);
			buffer[len] = '\0';
			return buffer;
		}

		void ReadObject(Version version) {
			const uint32_t size = header.object_v1.components;
			_parser.OnObjectBegin(size);
			uint16_t component_id;
			for (uint32_t i = 0u; i < size; ++i) {
				if (version >= VERSION_3) {
					IDMode mode = ID_U16;
					ReadFromPipeBuffered(&mode, 1u);
					if (mode == ID_U16) {
						goto OLD_COMPONENT_ID;

					} else if (mode == PID_STRING) {
						uint32_t len;
						char* buffer = ReadString(len);
						_parser.OnComponentID(buffer, len);

					} else {
						throw std::runtime_error("ReadHelper::ReadObject : Invalid component ID format");
					}

				} else {
OLD_COMPONENT_ID:
					ReadFromPipeBuffered(&component_id, sizeof(component_id));
					_parser.OnComponentID(component_id);
				}
				ReadFromPipeBuffered(&header, 1u);
				ReadGeneric(version);
			}
			_parser.OnObjectEnd();
		}

		inline void ReadPrimitive(Version version) {
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

		void ReadGeneric(Version version) {
			switch (header.primary_id) {
			case PID_NULL:
				_parser.OnNull();
				break;
			case PID_STRING:
				{
					uint32_t len;
					char* buffer = ReadString(len);
					_parser.OnPrimitiveString(buffer, len);
				};
				break;
			case PID_ARRAY:
				ReadFromPipeBuffered(&header.array_v1, sizeof(header.array_v1));
				ReadArray(version);
				break;
			case PID_OBJECT:
				ReadFromPipeBuffered(&header.object_v1, sizeof(header.object_v1));
				ReadObject(version);
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
					_parser.OnUserPOD(static_cast<PodType>(id), header.user_pod.bytes, mem);
				}
				break;
			default:
				ReadPrimitive(version);
				break;
			}
		}

		void ReadArray(Version version) {
			const uint32_t id = header.secondary_id;
			// If the array contains generic values
			if (id == SID_NULL) {
				const uint32_t size = header.array_v1.size;
				_parser.OnArrayBegin(size);
				for (uint32_t i = 0u; i < size; ++i) {
					ReadFromPipeBuffered(&header, 1u);
					ReadGeneric(version);
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
				(_parser.*GetPrimitiveArrayCallback(static_cast<SecondaryID>(id)))(buffer, size);
			}
		}
	public:
		ValueHeader header;

		ReadHelper(InputPipe& pipe, Parser& parser, Version version, const bool swap_byte_order) :
			header(),
			_pipe(pipe),
			_parser(parser),
			_mem(nullptr),
			_mem_bytes(0u),
			_swap_byte_order(swap_byte_order),
			_buffer_size(0u),
			_version(version),
			_buffer_head(nullptr)
		{
			memset(_buffer, 0, sizeof(_buffer));
		}

		~ReadHelper() {
			if (_mem) operator delete(_mem);
		}

		void Read() {
			// Continue with read
			ReadFromPipeBuffered(&header.id_union, 1u);
			while (header.id_union != PID_NULL) {
				ReadGeneric(_version);
				ReadFromPipeBuffered(&header.id_union, 1u);
			}
		}
	};

	Reader::Reader(InputPipe& pipe) :
		_pipe(pipe)
	{}

	Reader::~Reader() {

	}

	void Reader::Read(Parser& dst) 
	{
		size_t throwaway = 0u;

		// Read the version from the header
		union {
			PipeHeaderV1 header_v1;
			PipeHeaderV2 header_v2;
		};
		if (_pipe.ForceReadBytes(&header_v1, sizeof(PipeHeaderV1), throwaway, 10000) == std::future_status::timeout) throw std::runtime_error("Reader::Read : Timed-out reading version number");

		// Check for unsupported version
		if (header_v1.version > VERSION_3) throw std::runtime_error("Reader::Read : BytePipe version not supported");

		// Read additional header data
		bool swap_byte_order;
		const Endianness e = GetEndianness();
		if (header_v1.version == VERSION_1) {
			// Version 1 only supports little endian
			swap_byte_order = e != ENDIAN_LITTLE;
		} else {
			// Read the version 2 header info
			if(_pipe.ForceReadBytes(reinterpret_cast<uint8_t*>(&header_v2) + sizeof(PipeHeaderV1), sizeof(PipeHeaderV2) - sizeof(PipeHeaderV1), throwaway, 10000) == std::future_status::timeout) throw std::runtime_error("Reader::Read : Timed-out reading V2 header");
			swap_byte_order = e != (header_v2.little_endian ? ENDIAN_LITTLE : ENDIAN_BIG);

			// These header options are not defined yet
			if(header_v2.reserved_flag1 || header_v2.reserved_flag2 || header_v2.reserved_flag3 || header_v2.reserved_flag4 || 
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
		_root.Set<Value::Null>();
	}

	void ValueParser::OnPipeClose() {
		_value_stack.clear();
		_root.Set<Value::Null>();
	}

	void ValueParser::OnArrayBegin(const size_t size) {
		Value& val = NextValue();
		val.Set<Value::Array>();
		_value_stack.push_back(&val);
	}

	void ValueParser::OnArrayEnd() {
		_value_stack.pop_back();
	}

	void ValueParser::OnObjectBegin(const size_t component_count) {
		Value& val = NextValue();
		val.Set<Value::Object>();
		_value_stack.push_back(&val);
	}

	void ValueParser::OnObjectEnd() {
		_value_stack.pop_back();
	}

	void ValueParser::OnComponentID(const ComponentID id) {
		std::string str = std::to_string(id);
		OnComponentID(str.c_str(), str.size());
	}

	void ValueParser::OnComponentID(const char* str, size_t size) {
		_component_id_str = std::string(str, str + size);
	}

	void ValueParser::OnUserPOD(const PodType type, const size_t bytes, const void* data) {
		Value::Pod& pod = NextValue().Set<Value::Pod>();
		pod.type = type;
		pod.data = std::move(std::vector<uint8_t>(static_cast<const uint8_t*>(data), static_cast<const uint8_t*>(data) + bytes));
	}

	void ValueParser::OnNull() {
		NextValue().Set<Value::Null>();
	}

	void ValueParser::OnPrimitiveF64(const double value) {
		NextValue().Set<double>() = value;
	}

	void ValueParser::OnPrimitiveString(const char* value, const size_t length) {
		// Zero terminate string
		char* str = static_cast<char*>(operator new(length + 1));
		memcpy(str, value, length);
		str[length] = '\0';

		try {
			Value& val = NextValue();
			val.Set<std::string>() = str;
		} catch (...) {
			operator delete(str);
			std::rethrow_exception(std::current_exception());
		}
		operator delete(str);
	}

	void ValueParser::OnPrimitiveC8(const char value) {
		NextValue().Set<char>() = value;
	}

	void ValueParser::OnPrimitiveU64(const uint64_t value) {
		NextValue().Set<uint64_t>() = value;
	}

	void ValueParser::OnPrimitiveS64(const int64_t value) {
		NextValue().Set<int64_t>() = value;
	}

	void ValueParser::OnPrimitiveF32(const float value) {
		NextValue().Set<float>() = value;
	}

	void ValueParser::OnPrimitiveU8(const uint8_t value) {
		NextValue().Set<uint8_t>() = value;
	}

	void ValueParser::OnPrimitiveU16(const uint16_t value) {
		NextValue().Set<uint16_t>() = value;
	}

	void ValueParser::OnPrimitiveU32(const uint32_t value) {
		NextValue().Set<uint32_t>() = value;
	}

	void ValueParser::OnPrimitiveS8(const int8_t value) {
		NextValue().Set<int8_t>() = value;
	}

	void ValueParser::OnPrimitiveS16(const int16_t value) {
		NextValue().Set<int16_t>() = value;
	}

	void ValueParser::OnPrimitiveS32(const int32_t value) {
		NextValue().Set<int32_t>() = value;
	}

#if ANVIL_F8_SUPPORT
	void ValueParser::OnPrimitiveF8(const float8_t value) {
		NextValue().Set<float8_t>() = value;
	}
#endif

#if ANVIL_F16_SUPPORT
	void ValueParser::OnPrimitiveF16(const float16_t value) {
		NextValue().Set<float16_t>() = value;
	}
#endif

	void ValueParser::OnPrimitiveBool(const bool value) {
		NextValue().Set<bool>() = value;
	}

	static void CopyToPrimitiveArray(const void* src, const size_t size, const size_t bytes, Value::PrimitiveArray& primative_array) {
		const size_t total_bytes = bytes * size;
		primative_array.resize(total_bytes);
		memcpy(primative_array.data(), src, total_bytes);
	}

	void ValueParser::OnPrimitiveArrayC8(const char* src, const size_t size) {
		CopyToPrimitiveArray(src, size, sizeof(char), NextValue().Set<Value::PrimitiveArray>(TYPE_C8));
	}

	void ValueParser::OnPrimitiveArrayBool(const bool* src, const size_t size) {
		CopyToPrimitiveArray(src, size, sizeof(bool), NextValue().Set<Value::PrimitiveArray>(TYPE_BOOL));
	}

	void ValueParser::OnPrimitiveArrayU8(const uint8_t* src, const size_t size) {
		CopyToPrimitiveArray(src, size, sizeof(uint8_t), NextValue().Set<Value::PrimitiveArray>(TYPE_U8));
	}

	void ValueParser::OnPrimitiveArrayU16(const uint16_t* src, const size_t size) {
		CopyToPrimitiveArray(src, size, sizeof(uint16_t), NextValue().Set<Value::PrimitiveArray>(TYPE_U16));
	}

	void ValueParser::OnPrimitiveArrayU32(const uint32_t* src, const size_t size) {
		CopyToPrimitiveArray(src, size, sizeof(uint32_t), NextValue().Set<Value::PrimitiveArray>(TYPE_U32));
	}

	void ValueParser::OnPrimitiveArrayU64(const uint64_t* src, const size_t size) {
		CopyToPrimitiveArray(src, size, sizeof(uint64_t), NextValue().Set<Value::PrimitiveArray>(TYPE_U64));
	}

	void ValueParser::OnPrimitiveArrayS8(const int8_t* src, const size_t size) {
		CopyToPrimitiveArray(src, size, sizeof(int8_t), NextValue().Set<Value::PrimitiveArray>(TYPE_S8));
	}

	void ValueParser::OnPrimitiveArrayS16(const int16_t* src, const size_t size) {
		CopyToPrimitiveArray(src, size, sizeof(int16_t), NextValue().Set<Value::PrimitiveArray>(TYPE_S16));
	}

	void ValueParser::OnPrimitiveArrayS32(const int32_t* src, const size_t size) {
		CopyToPrimitiveArray(src, size, sizeof(int32_t), NextValue().Set<Value::PrimitiveArray>(TYPE_S32));
	}

	void ValueParser::OnPrimitiveArrayS64(const int64_t* src, const size_t size) {
		CopyToPrimitiveArray(src, size, sizeof(int64_t), NextValue().Set<Value::PrimitiveArray>(TYPE_S64));
	}

#if ANVIL_F8_SUPPORT
	void ValueParser::OnPrimitiveArrayF8(const float8_t* src, const size_t size) {
		CopyToPrimitiveArray(src, size, sizeof(float8_t), NextValue().Set<Value::PrimitiveArray>(TYPE_F8));
	}
#endif

#if ANVIL_F16_SUPPORT
	void ValueParser::OnPrimitiveArrayF16(const float16_t* src, const size_t size) {
		CopyToPrimitiveArray(src, size, sizeof(float16_t), NextValue().Set<Value::PrimitiveArray>(TYPE_F16));
	}
#endif

	void ValueParser::OnPrimitiveArrayF32(const float* src, const size_t size) {
		CopyToPrimitiveArray(src, size, sizeof(float), NextValue().Set<Value::PrimitiveArray>(TYPE_F32));
	}

	void ValueParser::OnPrimitiveArrayF64(const double* src, const size_t size) {
		CopyToPrimitiveArray(src, size, sizeof(double), NextValue().Set<Value::PrimitiveArray>(TYPE_F64));
	}

	Value& ValueParser::CurrentValue() {
		return _value_stack.empty() ? _root : *_value_stack.back();
	}

	Value& ValueParser::NextValue() {
		Value& val = CurrentValue();
		switch (val.GetType()) {
		case TYPE_ARRAY:
			{
				Value* v = Value::ArrayWrapper(val).push_back(Value());
				if (!v) throw std::runtime_error("ValueParser::NextValue : Failed to convert from primitve array");
				return *v;
			}
			break;
		case TYPE_OBJECT:
			{
				Value::Object& obj = *val.Get<Value::Object>();
				Value* v = &obj.emplace(_component_id_str, Value()).first->second;
				_component_id_str.clear();
				return *v;
			}
			break;
		default:
			return val;
		}
	}

	// Parser

	Parser::Parser() {

	}

	Parser::~Parser() {

	}


	struct ImageHeader {
		uint32_t width;
		uint32_t height;
		uint8_t compression_format;
		uint8_t type;
	};

	static_assert(sizeof(ImageHeader) == 12, "anvil/BytePipeParser.cpp : Expected ImageHeader to be 12 bytes");

	compute::Image Value::Pod::CreateImageFromPOD(const void* data, const size_t bytes) {
		const ImageHeader* header = static_cast<const ImageHeader*>(data);

		if (header->compression_format == IMAGE_BIN) {
			return compute::Image(
				const_cast<uint8_t*>(static_cast<const uint8_t*>(data) + sizeof(ImageHeader)),
				static_cast<EnumeratedType>(header->type), header->width, header->height).DeepCopy();
		} else {
#if ANVIL_OPENCV_SUPPORT
			const uint8_t* img_data = static_cast<const uint8_t*>(data) + sizeof(ImageHeader);
			std::vector<uint8_t> tmp(img_data, img_data + (bytes - sizeof(ImageHeader)));
			return cv::imdecode(tmp, 0);
#else
			throw std::runtime_error("anvil::BytePipe::Value::Pod::CreateImageFromPod : OpenCV is required for image compression");
#endif
		}
	}

	Value::Pod Value::Pod::CreatePODFromImage(const compute::Image& value_in, ImageFormat compression_format, float quality) {
		compute::Image buffer_image;
		const compute::Image* value = &value_in;
		if (!value_in.IsContiguous()) {
			buffer_image = value_in.DeepCopy();
			value = &buffer_image;
		}

		Value::Pod pod;
		pod.type = POD_IMAGE;

		ImageHeader header;
		header.width = static_cast<uint32_t>(value->GetWidth());
		header.height = static_cast<uint32_t>(value->GetHeight());
		header.type = static_cast<uint16_t>(value->GetType().GetEnumeratedType());
		header.compression_format = static_cast<uint8_t>(compression_format);

		if (compression_format == IMAGE_BIN) {
			uint32_t bytes = static_cast<uint32_t>(value->GetType().GetSizeInBytes());
			bytes *= header.width * header.height;
			bytes += sizeof(ImageHeader);

			pod.data.resize(bytes);
			void* data = pod.data.data();
			memcpy(data, &header, sizeof(ImageHeader));
			memcpy(static_cast<uint8_t*>(data) + sizeof(ImageHeader), value->GetData(), bytes - sizeof(ImageHeader));
		} else {
#if ANVIL_OPENCV_SUPPORT
			std::vector<uint8_t> tmp;

			cv::Mat mat = *const_cast<compute::Image*>(value);

			switch (compression_format) {
			case IMAGE_JPEG:
				cv::imencode(".jpg", mat, tmp, { cv::IMWRITE_JPEG_QUALITY , static_cast<int>(std::round(quality)) });
				break;
			case IMAGE_JPEG2000:
				cv::imencode(".jp2", mat, tmp, { cv::IMWRITE_JPEG2000_COMPRESSION_X1000, static_cast<int>(std::round(quality * 10.f)) });
				break;
			case IMAGE_BMP:
				cv::imencode(".bmp", mat, tmp);
				break;
			case IMAGE_PNG:
				cv::imencode(".jpg", mat, tmp/*, { cv::IMWRITE_PNG_COMPRESSION , static_cast<int>(std::round(quality / 100.f) * 9.f) }*/);
				break;
			case IMAGE_TIFF:
				cv::imencode(".tiff", mat, tmp);
				break;
			case IMAGE_WEBP:
				cv::imencode(".webp", mat, tmp);
				break;
			case IMAGE_EXR:
				cv::imencode(".exr", mat, tmp);
				break;
			case IMAGE_HDR:
				cv::imencode(".hdr", mat, tmp);
				break;
			}

			size_t bytes = sizeof(ImageHeader) + tmp.size();

			pod.data.resize(bytes);
			void* data = pod.data.data();
			memcpy(data, &header, sizeof(ImageHeader));
			memcpy(static_cast<uint8_t*>(data) + sizeof(ImageHeader), tmp.data(), bytes - sizeof(ImageHeader));
#else
			throw std::runtime_error("anvil::BytePipe::Value::Pod::CreatePODFromImage : OpenCV is required for image compression");
#endif
		}

		return pod;
	}

	void Parser::OnValue(const Value& value) {
		switch (value.GetType()) {
		case TYPE_STRING:
			{
				const std::string& str = *value.Get<std::string>();
				OnPrimitiveString(str.c_str(), str.size());
			}
			break;
		case TYPE_ARRAY:
			{
				const Value::PrimitiveArray* pa = value.Get<Value::PrimitiveArray>();
				if (pa) {
					const size_t size = pa->size();
					switch (value.GetPrimitiveArrayType()) {
					case TYPE_C8:
						OnPrimitiveArrayC8(reinterpret_cast<const char*>(const_cast<Value&>(value).Get<Value::PrimitiveArray>()->data()), size);
						break;
					case TYPE_U8:
						OnPrimitiveArrayU8(reinterpret_cast<const uint8_t*>(pa->data()), size);
						break;
					case TYPE_U16:
						OnPrimitiveArrayU16(reinterpret_cast<const uint16_t*>(pa->data()), size);
						break;
					case TYPE_U32:
						OnPrimitiveArrayU32(reinterpret_cast<const uint32_t*>(pa->data()), size);
						break;
					case TYPE_U64:
						OnPrimitiveArrayU64(reinterpret_cast<const uint64_t*>(pa->data()), size);
						break;
					case TYPE_S8:
						OnPrimitiveArrayS8(reinterpret_cast<const int8_t*>(pa->data()), size);
						break;
					case TYPE_S16:
						OnPrimitiveArrayS16(reinterpret_cast<const int16_t*>(pa->data()), size);
						break;
					case TYPE_S32:
						OnPrimitiveArrayS32(reinterpret_cast<const int32_t*>(pa->data()), size);
						break;
					case TYPE_S64:
						OnPrimitiveArrayS64(reinterpret_cast<const int64_t*>(pa->data()), size);
						break;
#if ANVIL_F8_SUPPORT
					case TYPE_F8:
						OnPrimitiveArrayF8(reinterpret_cast<const float8_t*>(pa->data()), size);
						break;
#endif
#if ANVIL_F16_SUPPORT
					case TYPE_F16:
						OnPrimitiveArrayF16(reinterpret_cast<const float16_t*>(pa->data()), size);
						break;
#endif
					case TYPE_F32:
						OnPrimitiveArrayF32(reinterpret_cast<const float*>(pa->data()), size);
						break;
					case TYPE_F64:
						OnPrimitiveArrayF64(reinterpret_cast<const double*>(pa->data()), size);
						break;
					case TYPE_BOOL:
						OnPrimitiveArrayBool(reinterpret_cast<const bool*>(pa->data()), size);
						break;
					}
				} else {
					const Value::Array* a = value.Get<Value::Array>();
					const size_t size = a->size();
					OnArrayBegin(size);
					for (size_t i = 0u; i < size; ++i) {
						OnValue(a->operator[](i));
					}
					OnArrayEnd();
				}
			}
			break;
		case TYPE_OBJECT:
			{
				const Value::Object& obj = *value.Get<Value::Object>();
				const uint32_t size = static_cast<uint32_t>(obj.size());
				OnObjectBegin(size);
				for (auto& i : obj) {
					OnComponentID(i.first);
					OnValue(i.second);
				}
				OnObjectEnd();
			}
			break;
		case TYPE_POD:
			{
				const Value::Pod& pod = *value.Get<Value::Pod>();
				OnUserPOD(pod.type, pod.data.size(), pod.data.data());
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
	
	// InputPipe


	InputPipe::InputPipe() :
		_current_packet(nullptr),
		_current_packet_size(0u),
		_current_packet_bytes_read(0u)
	{

	}

	InputPipe::~InputPipe() 
	{

	}

	/*!
	*	\brief Read an exact ammount of data from the pipe.
	*	\details Use of this function is no longer recommended. Throws exception on time-out. Timing out will leave the data in an undefined state as the number of bytes read will not be recorded.
	*	\param dst The address to write any bytes that can be read
	*	\param bytes The number of bytes to read
		\param bytes_actual The number of bytes that were read from the pipe before a timeout
	*	\param timout_ms The number of milliseconds before the read times-out. A value of -1 will force it to never time out.
	*/
	std::future_status InputPipe::ForceReadBytes(void* dst, size_t bytes, size_t& bytes_actual, int timeout_ms)
	{
		const uint64_t t = timeout_ms == -1 ? 0u : GetTimeMSUint();
		bytes_actual = 0u;

		while (bytes > 0u) 
		{
			const size_t bytes_read = ReadBytes(dst, bytes);
			bytes -= bytes_read;
			dst = static_cast<uint8_t*>(dst) + bytes_read;
			bytes_actual += bytes_read;

			if (bytes > 0u && timeout_ms >= 0) 
			{
				const uint64_t t2 = GetTimeMSUint();
				if (static_cast<int>(t2 - t) > timeout_ms) return std::future_status::timeout;
			}

		}

		return std::future_status::ready;
	}

	// OutputPipe

	OutputPipe::OutputPipe() :
		_small_buffer_size(0u)
	{

	}

	OutputPipe::~OutputPipe() 
	{
		
	}

	std::future_status OutputPipe::FlushSmallBuffer(int timeout_ms)
	{
		if (_small_buffer_size > 0u)
		{
			size_t bytes_written = _small_buffer_size;
			if (WriteBytesVirtual(_small_buffer, bytes_written, timeout_ms) == std::future_status::timeout || bytes_written != _small_buffer_size)
			{
				memcpy(_small_buffer, static_cast<uint8_t*>(_small_buffer) + bytes_written, _small_buffer_size - bytes_written);
				_small_buffer_size = bytes_written;
				return std::future_status::timeout;
			}
			_small_buffer_size = 0u;
		}
		return std::future_status::ready;
	}

	std::future_status OutputPipe::WriteBytes(const void* src, size_t& bytes, int timeout_ms)
	{
		if (bytes > SMALL_BUFFER_LENGTH)
		{
			if(FlushSmallBuffer(timeout_ms) == std::future_status::timeout) return std::future_status::timeout;
			if (WriteBytesVirtual(src, bytes, timeout_ms) == std::future_status::timeout) return std::future_status::timeout;
		}
		else
		{
			if (bytes + _small_buffer_size > SMALL_BUFFER_LENGTH)
			{
				if (FlushSmallBuffer(timeout_ms) == std::future_status::timeout) return std::future_status::timeout;
			}
			memcpy(static_cast<uint8_t*>(_small_buffer) + _small_buffer_size, src, bytes);
			_small_buffer_size += bytes;
		}
		return std::future_status::ready;
	}
	
	///*!
	//*	\brief Write an exact ammount of data from the pipe.
	//*	\details Use of this function is no longer recommended. Throws exception on time-out. Timing out will leave the data in an undefined state as the number of bytes writeen will not be recorded.
	//*	\param src The address of the bytes to write
	//*	\param bytes The number of bytes to write
	//*	\param timout_ms The number of milliseconds before the write times-out. A value of -1 will force it to never time out.
	//*/
	//void OutputPipe::WriteBytesFast(const void* src, size_t bytes, int timeout_ms) {
	//	const uint64_t t = GetTimeMSUint();

	//	while (bytes > 0u) {
	//		size_t bytes_written = WriteBytes(src, bytes);

	//		bytes -= bytes_written;
	//		src = static_cast<const uint8_t*>(src) + bytes_written;

	//		if (bytes > 0u && timeout_ms >= 0) {
	//			const uint64_t t2 = GetTimeMSUint();
	//			if (static_cast<int>(t2 - t) > timeout_ms) throw std::runtime_error("OutputPipe::WriteBytesFast : Read timed-out");
	//		}
	//	}
	//}

}}
