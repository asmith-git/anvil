//Copyright 2023 Adam G. Smith
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

#include "anvil/compute/Arithmetic.hpp"
#include "anvil/compute/details/ArithmeticCpp.hpp"
#include "anvil/compute/details/ArithmeticSseF32.hpp"
#include "anvil/compute/details/ArithmeticF16.hpp"
#include <vector>
#include "anvil/compute/Image.hpp"

namespace anvil { namespace compute {

	// ArithmeticOperations

	struct StaticArithmeticOperations;

	static std::vector< StaticArithmeticOperations*> g_static_objects;

	struct StaticArithmeticOperations{

		ArithmeticOperations* channels[Type::MAX_CHANNELS];

		StaticArithmeticOperations(ArithmeticOperations* single_channel) {
			g_static_objects.push_back(this);

			channels[0u] = single_channel;

			Type type = single_channel->GetType();
			for (size_t i = 1u; i < Type::MAX_CHANNELS; ++i) {
				type.SetNumberOfChannels(i + 1);
				channels[i] = new details::ArithmeticOperationsMultiChannel(type, *single_channel);
			}
		}

		~StaticArithmeticOperations() {
			//! \bug Should really be erased from g_static_objects but this destructor should only be called at program termination anyway
		
			for (size_t i = 0u; i < Type::MAX_CHANNELS; ++i) {
				delete channels[i];
				channels[i] = nullptr;
			}
		}
	};

	static StaticArithmeticOperations g_arithmetic_op_u8(new details::ArithmeticOperationsCpp<uint8_t>());
	static StaticArithmeticOperations g_arithmetic_op_u16(new details::ArithmeticOperationsCpp<uint16_t>());
	static StaticArithmeticOperations g_arithmetic_op_u32(new details::ArithmeticOperationsCpp<uint32_t>());
	static StaticArithmeticOperations g_arithmetic_op_u64(new details::ArithmeticOperationsCpp<uint64_t>());
	static StaticArithmeticOperations g_arithmetic_op_s8(new details::ArithmeticOperationsCpp<int8_t>());
	static StaticArithmeticOperations g_arithmetic_op_s16(new details::ArithmeticOperationsCpp<int16_t>());
	static StaticArithmeticOperations g_arithmetic_op_s32(new details::ArithmeticOperationsCpp<int32_t>());
	static StaticArithmeticOperations g_arithmetic_op_s64(new details::ArithmeticOperationsCpp<int64_t>());
#if ANVIL_F8_SUPPORT
	static StaticArithmeticOperations g_arithmetic_op_f8(new details::ArithmeticOperationsCpp<float8_t>());
#endif
#if ANVIL_F16_SUPPORT
	static StaticArithmeticOperations g_arithmetic_op_f16(new details::ArithmeticOperationsCpp<float16_t>());
#endif
	static StaticArithmeticOperations g_arithmetic_op_f32(new details::ArithmeticOperationsCpp<float>());
	static StaticArithmeticOperations g_arithmetic_op_f64(new details::ArithmeticOperationsCpp<double>());

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
	static StaticArithmeticOperations g_arithmetic_op_f32_sse(new details::ArithmeticOperationsSseF32());
	static StaticArithmeticOperations g_arithmetic_op_f32_sse41(new details::ArithmeticOperationsSse4F32());
	static StaticArithmeticOperations g_arithmetic_op_f32_fma3(new details::ArithmeticOperationsFmaF32());
	static StaticArithmeticOperations g_arithmetic_op_f32_avx512(new details::ArithmeticOperationsAvx512F32());
#endif

	bool ArithmeticOperations::SetupStaticObjects() {
		static bool g_once = true;
		if (g_once) {
			g_once = false;

			for (StaticArithmeticOperations* static_obj : g_static_objects) {
				for (ArithmeticOperations* obj : static_obj->channels) {
					obj->Initialise();
				}
			}
		}

		return true;
	}

	static const bool g_arithmetic_operations_initialised = ArithmeticOperations::SetupStaticObjects(); //!< This variable doesn't do anything except making sure that ArithmeticOperations::SetupStaticObjects is called

	ArithmeticOperations* ArithmeticOperations::GetArithmeticOperations(Type type, uint64_t instruction_set) {
		//! \todo Implement optimisations for different instruction sets (SSE, AVX, AVX-512, ect)

		StaticArithmeticOperations* ops = nullptr;

		const size_t channels = type.GetNumberOfChannels();
		type.SetNumberOfChannels(1u);
		switch (type.GetEnumeratedType()) {
		case ANVIL_8UX1:
			ops = &g_arithmetic_op_u8;
			break;
		case ANVIL_16UX1:
			ops = &g_arithmetic_op_u16;
			break;
		case ANVIL_32UX1:
			ops = &g_arithmetic_op_u32;
			break;
		case ANVIL_64UX1:
			ops = &g_arithmetic_op_u64;
			break;
		case ANVIL_8SX1:
			ops = &g_arithmetic_op_s8;
			break;
		case ANVIL_16SX1:
			ops = &g_arithmetic_op_s16;
			break;
		case ANVIL_32SX1:
			ops = &g_arithmetic_op_s32;
			break;
		case ANVIL_64SX1:
			ops = &g_arithmetic_op_s64;
			break;
#if ANVIL_F8_SUPPORT
		case ANVIL_8FX1:
			ops = &g_arithmetic_op_f8;
			break;
#endif
#if ANVIL_F16_SUPPORT
		case ANVIL_16FX1:
			ops = &g_arithmetic_op_f16;
			break;
#endif
		case ANVIL_32FX1:
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
			enum { AVX512_FLAGS = ASM_AVX512F | ASM_AVX512VL };
			if ((instruction_set & AVX512_FLAGS) == AVX512_FLAGS) {
				ops = &g_arithmetic_op_f32_avx512;
			} else if (instruction_set & ASM_FMA3) {
				ops = &g_arithmetic_op_f32_fma3;
			} else if (instruction_set & ASM_SSE41) {
				ops =& g_arithmetic_op_f32_sse41;
			} else if (instruction_set & ASM_SSE2) {
				ops = &g_arithmetic_op_f32_sse;
			} else
#endif
			ops = &g_arithmetic_op_f32;
			break;
		case ANVIL_64FX1:
			ops = &g_arithmetic_op_f64;
			break;
		}

		if (ops == nullptr) return nullptr;
		return ops->channels[channels - 1u];
	}

	Type ArithmeticOperations::PreferedOutputType(Type input_type1, Type input_type2) {
		const size_t b1 = input_type1.GetSizeInBytes();
		const size_t b2 = input_type2.GetSizeInBytes();
		const Type::Representation r1 = input_type1.GetRepresentation();
		const Type::Representation r2 = input_type2.GetRepresentation();

		return Type(
			r1 == Type::TYPE_FLOATING_POINT || r2 == Type::TYPE_FLOATING_POINT ? Type::TYPE_FLOATING_POINT :
			r1 == Type::TYPE_SIGNED || r2 == Type::TYPE_SIGNED ? Type::TYPE_SIGNED :
			Type::TYPE_UNSIGNED,

			b1 == 1u && b2 == 1 ? 2u : std::max(b1, b2),

			std::max(input_type1.GetNumberOfChannels(), input_type2.GetNumberOfChannels())
		);
	}

	Type ArithmeticOperations::PreferedBitwiseOutputType(Type input_type1, Type input_type2) {
		const Type::Representation r1 = input_type1.GetRepresentation();
		const Type::Representation r2 = input_type2.GetRepresentation();

		return Type(
			r1 == Type::TYPE_FLOATING_POINT || r2 == Type::TYPE_FLOATING_POINT ? Type::TYPE_FLOATING_POINT :
			r1 == Type::TYPE_SIGNED || r2 == Type::TYPE_SIGNED ? Type::TYPE_SIGNED :
			Type::TYPE_UNSIGNED,

			std::max(input_type1.GetSizeInBytes(), input_type2.GetSizeInBytes()),
			std::max(input_type1.GetNumberOfChannels(), input_type2.GetNumberOfChannels())
		);
	}

	ArithmeticOperations::ArithmeticOperations(Type type) :
		_type(type)
	{}

	ArithmeticOperations::~ArithmeticOperations() {

	}
	
	void ArithmeticOperations::Initialise() {
		// Doesn't do anything in the base class
	}

	void ArithmeticOperations::Mask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
		const size_t bytes = _type.GetSizeInBytes();

		const uint8_t* lhs8 = static_cast<const uint8_t*>(lhs);
		const uint8_t* rhs8 = static_cast<const uint8_t*>(rhs);
		uint8_t* dst8 = static_cast<uint8_t*>(dst);

		while (count >= 8u) {
			count -= 8u;

			const uint8_t m = *mask;
			++mask;

			memcpy(dst8, m & 1u ? lhs8 : rhs8, bytes);
			lhs8 += bytes;
			rhs8 += bytes;
			dst8 += bytes;

			memcpy(dst8, m & 2u ? lhs8 : rhs8, bytes);
			lhs8 += bytes;
			rhs8 += bytes;
			dst8 += bytes;

			memcpy(dst8, m & 4u ? lhs8 : rhs8, bytes);
			lhs8 += bytes;
			rhs8 += bytes;
			dst8 += bytes;

			memcpy(dst8, m & 8u ? lhs8 : rhs8, bytes);
			lhs8 += bytes;
			rhs8 += bytes;
			dst8 += bytes;

			memcpy(dst8, m & 16u ? lhs8 : rhs8, bytes);
			lhs8 += bytes;
			rhs8 += bytes;
			dst8 += bytes;

			memcpy(dst8, m & 32u ? lhs8 : rhs8, bytes);
			lhs8 += bytes;
			rhs8 += bytes;
			dst8 += bytes;

			memcpy(dst8, m & 64u ? lhs8 : rhs8, bytes);
			lhs8 += bytes;
			rhs8 += bytes;
			dst8 += bytes;

			memcpy(dst8, m & 128u ? lhs8 : rhs8, bytes);
			lhs8 += bytes;
			rhs8 += bytes;
			dst8 += bytes;
		}

		uint8_t m = *mask;
		for (size_t i = 0; i < count; ++i) {
			memcpy(dst8, m & 1u ? lhs8 : rhs8, bytes);
			lhs8 += bytes;
			rhs8 += bytes;
			dst8 += bytes;

			m >>= 1u;
		}
	}

	void ArithmeticOperations::CallDefaultMaskedOperation(
		const void* src, void* dst, size_t count, const uint8_t* mask,
		void(ArithmeticOperations::* Function)(const void* src, void* dst, size_t count) const
	) const {
		if (src == dst) {
			void* buffer = _malloca(_type.GetSizeInBytes() * count);
			ANVIL_RUNTIME_ASSERT(buffer != nullptr, "Anvil::ArithmeticOperations::CallDefaultMaskedOperation : Failed to allocate buffer for masked operation");
			(this->*Function)(src, buffer, count);
			Mask(buffer, src, dst, count, mask);
			_freea(buffer);
		} else {
			(this->*Function)(src, dst, count);
			Mask(dst, src, dst, count, mask);
		}
	}

	void ArithmeticOperations::CallDefaultMaskedOperation(
		const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask,
		void(ArithmeticOperations::* Function)(const void* lhs, const void* rhs, void* dst, size_t count) const
	) const {
		if (lhs == dst) {
			void* buffer = _malloca(_type.GetSizeInBytes() * count);
			ANVIL_RUNTIME_ASSERT(buffer != nullptr, "Anvil::ArithmeticOperations::CallDefaultMaskedOperation : Failed to allocate buffer for masked operation");
			(this->*Function)(lhs, rhs, buffer, count);
			Mask(buffer, lhs, dst, count, mask);
			_freea(buffer);
		} else {
			(this->*Function)(lhs, rhs, dst, count);
			Mask(dst, lhs, dst, count, mask);
		}
	}

	void ArithmeticOperations::CallDefaultMaskedOperation(
		const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask,
		void(ArithmeticOperations::* Function)(const void* a, const void* b, const void* c, void* dst, size_t count) const
	) const {
		if (a == dst) {
			void* buffer = _malloca(_type.GetSizeInBytes() * count);
			ANVIL_RUNTIME_ASSERT(buffer != nullptr, "Anvil::ArithmeticOperations::CallDefaultMaskedOperation : Failed to allocate buffer for masked operation");
			(this->*Function)(a, b, c, buffer, count);
			Mask(buffer, a, dst, count, mask);
			_freea(buffer);
		} else {
			(this->*Function)(a, b, c, dst, count);
			Mask(dst, a, dst, count, mask);
		}
	}

	void ArithmeticOperations::Sqrt(const void* src, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(src, dst, count, mask, &ArithmeticOperations::Sqrt);
	}

	void ArithmeticOperations::Cbrt(const void* src, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(src, dst, count, mask, &ArithmeticOperations::Cbrt);
	}

	void ArithmeticOperations::Not(const void* src, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(src, dst, count, mask, &ArithmeticOperations::Not);
	}

	void ArithmeticOperations::Add(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::Add);
	}

	void ArithmeticOperations::Subtract(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::Subtract);
	}

	void ArithmeticOperations::Multiply(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::Multiply);
	}

	void ArithmeticOperations::Divide(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::Divide);
	}

	void ArithmeticOperations::And(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::And);
	}

	void ArithmeticOperations::Or(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::Or);
	}

	void ArithmeticOperations::Xor(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::Xor);
	}

	void ArithmeticOperations::Nand(const void* lhs, const void* rhs, void* dst, size_t count) const {
		And(lhs, rhs, dst, count);
		Not(dst, dst, count);
	}

	void ArithmeticOperations::Nand(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::Nand);
	}

	void ArithmeticOperations::Nor(const void* lhs, const void* rhs, void* dst, size_t count) const {
		Or(lhs, rhs, dst, count);
		Not(dst, dst, count);
	}

	void ArithmeticOperations::Nor(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::Nor);
	}

	void ArithmeticOperations::Xnor(const void* lhs, const void* rhs, void* dst, size_t count) const {
		And(lhs, rhs, dst, count);
		Not(dst, dst, count);
	}

	void ArithmeticOperations::Xnor(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::Xnor);
	}

	void ArithmeticOperations::MultiplyAdd(const void* a, const void* b, const void* c, void* dst, size_t count) const {
		Multiply(a, b, dst, count);
		Add(dst, c, dst, count);
	}

	void ArithmeticOperations::MultiplyAdd(const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(a, b, c, dst, count, mask, &ArithmeticOperations::MultiplyAdd);
	}

	void ArithmeticOperations::MultiplySubtract(const void* a, const void* b, const void* c, void* dst, size_t count) const {
		Multiply(a, b, dst, count);
		Subtract(dst, c, dst, count);
	}

	void ArithmeticOperations::MultiplySubtract(const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(a, b, c, dst, count, mask, &ArithmeticOperations::MultiplySubtract);
	}

	void ArithmeticOperations::Round(const void* src, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(src, dst, count, mask, &ArithmeticOperations::Round);
	}

	void ArithmeticOperations::Floor(const void* src, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(src, dst, count, mask, &ArithmeticOperations::Floor);
	}


	void ArithmeticOperations::Ceil(const void* src, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(src, dst, count, mask, &ArithmeticOperations::Ceil);
	}

	void ArithmeticOperations::Cos(const void* src, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(src, dst, count, mask, &ArithmeticOperations::Cos);
	}

	void ArithmeticOperations::Sin(const void* src, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(src, dst, count, mask, &ArithmeticOperations::Sin);
	}

	void ArithmeticOperations::Tan(const void* src, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(src, dst, count, mask, &ArithmeticOperations::Tan);
	}

	void ArithmeticOperations::Acos(const void* src, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(src, dst, count, mask, &ArithmeticOperations::Acos);
	}

	void ArithmeticOperations::Asin(const void* src, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(src, dst, count, mask, &ArithmeticOperations::Asin);
	}

	void ArithmeticOperations::Atan(const void* src, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(src, dst, count, mask, &ArithmeticOperations::Atan);
	}

	void ArithmeticOperations::Cosh(const void* src, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(src, dst, count, mask, &ArithmeticOperations::Cosh);
	}

	void ArithmeticOperations::Sinh(const void* src, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(src, dst, count, mask, &ArithmeticOperations::Sinh);
	}

	void ArithmeticOperations::Tanh(const void* src, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(src, dst, count, mask, &ArithmeticOperations::Tanh);
	}

	void ArithmeticOperations::Acosh(const void* src, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(src, dst, count, mask, &ArithmeticOperations::Acosh);
	}

	void ArithmeticOperations::Asinh(const void* src, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(src, dst, count, mask, &ArithmeticOperations::Asinh);
	}

	void ArithmeticOperations::Atanh(const void* src, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(src, dst, count, mask, &ArithmeticOperations::Atanh);
	}

	void ArithmeticOperations::Abs(const void* src, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(src, dst, count, mask, &ArithmeticOperations::Abs);
	}

	void ArithmeticOperations::Power(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::Power);
	}

	void ArithmeticOperations::Hypotenuse(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::Hypotenuse);
	}

	void ArithmeticOperations::Minimum(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::Minimum);
	}

	void ArithmeticOperations::Maximum(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
		CallDefaultMaskedOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::Maximum);
	}
	
	////

	#pragma warning( disable : 4100) // is_bitwise is not used, Currently not needed for single input operations
	void ArithmeticOperations::CallOperation(
		const TypedScalar& src, TypedScalar& dst,
		void(ArithmeticOperations::* Function)(const void* src, void* dst, size_t count) const,
		uint64_t instruction_set, bool is_bitwise
	) const {
		const Type type = src.GetType();
		dst.ForceSetType(type);
		(GetArithmeticOperations(type, instruction_set)->*Function)(src.GetData(), dst.GetData(), 1u);
	}
	
	#pragma warning( disable : 4100) // is_bitwise is not used, Currently not needed for single input operations
	void ArithmeticOperations::CallOperation(
		const Vector& src, Vector& dst,
		void(ArithmeticOperations::* Function)(const void* src, void* dst, size_t count) const,
		uint64_t instruction_set, bool is_bitwise
	) const {
		const Type type = src.GetType();
		dst.ForceSetType(type);
		(GetArithmeticOperations(src.GetType(), instruction_set)->*Function)(src.GetData(), dst.GetData(), 1u);
	}
	
	#pragma warning( disable : 4100) // is_bitwise is not used, Currently not needed for single input operations
	void ArithmeticOperations::CallOperation(
		const Image& src, Image& dst,
		void(ArithmeticOperations::* Function)(const void* src, void* dst, size_t count) const,
		uint64_t instruction_set, bool is_bitwise
	) const {
		const Type type = src.GetType();
		const size_t w = src.GetWidth();
		const size_t h = src.GetHeight();
		dst.Allocate(type, w, h);
		(GetArithmeticOperations(src.GetType(), instruction_set)->*Function)(src.GetData(), dst.GetData(), w * h);
	}
	
	#pragma warning( disable : 4100) // is_bitwise is not used, Currently not needed for single input operations
	void ArithmeticOperations::CallOperation(
		const TypedScalar& src, TypedScalar& dst, const uint8_t* mask,
		void(ArithmeticOperations::* Function)(const void* src, void* dst, size_t count, const uint8_t* mask) const,
		uint64_t instruction_set, bool is_bitwise
	) const {
		const Type type = src.GetType();
		dst.ForceSetType(type);
		(GetArithmeticOperations(type, instruction_set)->*Function)(src.GetData(), dst.GetData(), 1u, mask);
	}
	
	#pragma warning( disable : 4100) // is_bitwise is not used, Currently not needed for single input operations
	void ArithmeticOperations::CallOperation(
		const Vector& src, Vector& dst, const uint8_t* mask,
		void(ArithmeticOperations::* Function)(const void* src, void* dst, size_t count, const uint8_t* mask) const,
		uint64_t instruction_set, bool is_bitwise
	) const {
		const Type type = src.GetType();
		dst.ForceSetType(type);
		(GetArithmeticOperations(src.GetType(), instruction_set)->*Function)(src.GetData(), dst.GetData(), 1u, mask);
	}
	
	#pragma warning( disable : 4100) // is_bitwise is not used, Currently not needed for single input operations
	void ArithmeticOperations::CallOperation(
		const Image& src, Image& dst, const uint8_t* mask,
		void(ArithmeticOperations::* Function)(const void* src, void* dst, size_t count, const uint8_t* mask) const,
		uint64_t instruction_set, bool is_bitwise
	) const {
		const Type type = src.GetType();
		const size_t w = src.GetWidth();
		const size_t h = src.GetHeight();
		dst.Allocate(type, w, h);
		(GetArithmeticOperations(src.GetType(), instruction_set)->*Function)(src.GetData(), dst.GetData(),  w * h, mask);
	}

	////

	void ArithmeticOperations::CallOperation(
		const TypedScalar& a, const TypedScalar& b, TypedScalar& dst,
		void(ArithmeticOperations::* Function)(const void* a, const void* b, void* dst, size_t count) const,
		uint64_t instruction_set, bool is_bitwise
	) const {
		const Type t1 = a.GetType();
		const Type t2 = b.GetType();
		const Type type = is_bitwise ? PreferedBitwiseOutputType(t1, t2) : PreferedOutputType(t1, t2);
		dst.ForceSetType(type);
		(GetArithmeticOperations(type, instruction_set)->*Function)(a.ConvertTo(type).GetData(), b.ConvertTo(type).GetData(), dst.GetData(), 1u);
	}

	void ArithmeticOperations::CallOperation(
		const Vector& a, const Vector& b, Vector& dst,
		void(ArithmeticOperations::* Function)(const void* a, const void* b, void* dst, size_t count) const,
		uint64_t instruction_set, bool is_bitwise
	) const {
		const Type t1 = a.GetType();
		const Type t2 = b.GetType();
		const Type type = is_bitwise ? PreferedBitwiseOutputType(t1, t2) : PreferedOutputType(t1, t2);
		dst.ForceSetType(type);
		(GetArithmeticOperations(type, instruction_set)->*Function)(a.ConvertTo(type).GetData(), b.ConvertTo(type).GetData(), dst.GetData(), 1u);
	}

	void ArithmeticOperations::CallOperation(
		const Image& a, const Image& b, Image& dst,
		void(ArithmeticOperations::* Function)(const void* a, const void* b, void* dst, size_t count) const,
		uint64_t instruction_set, bool is_bitwise
	) const {
		const Type t1 = a.GetType();
		const Type t2 = b.GetType();
		const Type type = is_bitwise ? PreferedBitwiseOutputType(t1, t2) : PreferedOutputType(t1, t2);
		const size_t w = a.GetWidth();
		const size_t h = a.GetHeight();
		ANVIL_DEBUG_ASSERT(w == b.GetWidth() && h == b.GetHeight(), "ArithmeticOperations::CallOperation : Input images must be same size");
		dst.Allocate(type, w, h);
		(GetArithmeticOperations(type, instruction_set)->*Function)(
			const_cast<Image&>(a).ConvertTo(type).GetData(), 
			const_cast<Image&>(b).ConvertTo(type).GetData(), 
			dst.GetData(), w * h
		);
	}

	void ArithmeticOperations::CallOperation(
		const TypedScalar& a, const TypedScalar& b, TypedScalar& dst, const uint8_t* mask,
		void(ArithmeticOperations::* Function)(const void* a, const void* b, void* dst, size_t count, const uint8_t* mask) const,
		uint64_t instruction_set, bool is_bitwise
	) const {
		const Type t1 = a.GetType();
		const Type t2 = b.GetType();
		const Type type = is_bitwise ? PreferedBitwiseOutputType(t1, t2) : PreferedOutputType(t1, t2);
		dst.ForceSetType(type);
		(GetArithmeticOperations(type, instruction_set)->*Function)(a.ConvertTo(type).GetData(), b.ConvertTo(type).GetData(), dst.GetData(), 1u, mask);
	}

	void ArithmeticOperations::CallOperation(
		const Vector& a, const Vector& b, Vector& dst, const uint8_t* mask,
		void(ArithmeticOperations::* Function)(const void* a, const void* b, void* dst, size_t count, const uint8_t* mask) const,
		uint64_t instruction_set, bool is_bitwise
	) const {
		const Type t1 = a.GetType();
		const Type t2 = b.GetType();
		const Type type = is_bitwise ? PreferedBitwiseOutputType(t1, t2) : PreferedOutputType(t1, t2);
		dst.ForceSetType(type);
		(GetArithmeticOperations(type, instruction_set)->*Function)(a.ConvertTo(type).GetData(), b.ConvertTo(type).GetData(), dst.GetData(), 1u, mask);
	}

	void ArithmeticOperations::CallOperation(
		const Image& a, const Image& b, Image& dst, const uint8_t* mask,
		void(ArithmeticOperations::* Function)(const void* a, const void* b, void* dst, size_t count, const uint8_t* mask) const,
		uint64_t instruction_set, bool is_bitwise
	) const {
		const Type t1 = a.GetType();
		const Type t2 = b.GetType();
		const Type type = is_bitwise ? PreferedBitwiseOutputType(t1, t2) : PreferedOutputType(t1, t2);
		const size_t w = a.GetWidth();
		const size_t h = a.GetHeight();
		ANVIL_DEBUG_ASSERT(w == b.GetWidth() && h == b.GetHeight(), "ArithmeticOperations::CallOperation : Input images must be same size");
		dst.Allocate(type, w, h);
		(GetArithmeticOperations(type, instruction_set)->*Function)(
			const_cast<Image&>(a).ConvertTo(type).GetData(), 
			const_cast<Image&>(b).ConvertTo(type).GetData(), 
			dst.GetData(), w * h, mask
		);
	}



	////

	void ArithmeticOperations::CallOperation(
		const TypedScalar& a, const TypedScalar& b, const TypedScalar& c, TypedScalar& dst,
		void(ArithmeticOperations::* Function)(const void* a, const void* b, const void* c, void* dst, size_t count) const,
		uint64_t instruction_set, bool is_bitwise
	) const {
		const Type t1 = a.GetType();
		const Type t2 = b.GetType();
		const Type t3 = c.GetType();
		const Type type = is_bitwise ? PreferedBitwiseOutputType(PreferedBitwiseOutputType(t1, t2), t3) : PreferedOutputType(PreferedOutputType(t1, t2), t3);
		dst.ForceSetType(type);
		(GetArithmeticOperations(type, instruction_set)->*Function)(a.ConvertTo(type).GetData(), b.ConvertTo(type).GetData(), c.ConvertTo(type).GetData(), dst.GetData(), 1u);
	}

	void ArithmeticOperations::CallOperation(
		const Vector& a, const Vector& b, const Vector& c, Vector& dst,
		void(ArithmeticOperations::* Function)(const void* a, const void* b, const void* c, void* dst, size_t count) const,
		uint64_t instruction_set, bool is_bitwise
	) const {
		const Type t1 = a.GetType();
		const Type t2 = b.GetType();
		const Type t3 = c.GetType();
		const Type type = is_bitwise ? PreferedBitwiseOutputType(PreferedBitwiseOutputType(t1, t2), t3) : PreferedOutputType(PreferedOutputType(t1, t2), t3);
		dst.ForceSetType(type);
		(GetArithmeticOperations(type, instruction_set)->*Function)(a.ConvertTo(type).GetData(), b.ConvertTo(type).GetData(), c.ConvertTo(type).GetData(), dst.GetData(), 1u);
	}

	void ArithmeticOperations::CallOperation(
		const Image& a, const Image& b, const Image& c, Image& dst,
		void(ArithmeticOperations::* Function)(const void* a, const void* b, const void* c, void* dst, size_t count) const,
		uint64_t instruction_set, bool is_bitwise
	) const {
		const Type t1 = a.GetType();
		const Type t2 = b.GetType();
		const Type t3 = c.GetType();
		const Type type = is_bitwise ? PreferedBitwiseOutputType(PreferedBitwiseOutputType(t1, t2), t3) : PreferedOutputType(PreferedOutputType(t1, t2), t3);
		const size_t w = a.GetWidth();
		const size_t h = a.GetHeight();
		ANVIL_DEBUG_ASSERT(w == b.GetWidth() && h == b.GetHeight(), "ArithmeticOperations::CallOperation : Input images must be same size");
		dst.Allocate(type, w, h);
		(GetArithmeticOperations(type, instruction_set)->*Function)(
			const_cast<Image&>(a).ConvertTo(type).GetData(), 
			const_cast<Image&>(b).ConvertTo(type).GetData(), 
			const_cast<Image&>(c).ConvertTo(type).GetData(), 
			dst.GetData(), w * h
		);
	}

	void ArithmeticOperations::CallOperation(
		const TypedScalar& a, const TypedScalar& b, const TypedScalar& c, TypedScalar& dst, const uint8_t* mask,
		void(ArithmeticOperations::* Function)(const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask) const,
		uint64_t instruction_set, bool is_bitwise
	) const {
		const Type t1 = a.GetType();
		const Type t2 = b.GetType();
		const Type t3 = c.GetType();
		const Type type = is_bitwise ? PreferedBitwiseOutputType(PreferedBitwiseOutputType(t1, t2), t3) : PreferedOutputType(PreferedOutputType(t1, t2), t3);
		dst.ForceSetType(type);
		(GetArithmeticOperations(type, instruction_set)->*Function)(a.ConvertTo(type).GetData(), b.ConvertTo(type).GetData(), c.ConvertTo(type).GetData(), dst.GetData(), 1u, mask);
	}

	void ArithmeticOperations::CallOperation(
		const Vector& a, const Vector& b, const Vector& c, Vector& dst, const uint8_t* mask,
		void(ArithmeticOperations::* Function)(const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask) const,
		uint64_t instruction_set, bool is_bitwise
	) const {
		const Type t1 = a.GetType();
		const Type t2 = b.GetType();
		const Type t3 = c.GetType();
		const Type type = is_bitwise ? PreferedBitwiseOutputType(PreferedBitwiseOutputType(t1, t2), t3) : PreferedOutputType(PreferedOutputType(t1, t2), t3);
		dst.ForceSetType(type);
		(GetArithmeticOperations(type, instruction_set)->*Function)(a.ConvertTo(type).GetData(), b.ConvertTo(type).GetData(), c.ConvertTo(type).GetData(), dst.GetData(), 1u, mask);
	}

	void ArithmeticOperations::CallOperation(
		const Image& a, const Image& b, const Image& c, Image& dst, const uint8_t* mask,
		void(ArithmeticOperations::* Function)(const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask) const,
		uint64_t instruction_set, bool is_bitwise
	) const {
		const Type t1 = a.GetType();
		const Type t2 = b.GetType();
		const Type t3 = c.GetType();
		const Type type = is_bitwise ? PreferedBitwiseOutputType(PreferedBitwiseOutputType(t1, t2), t3) : PreferedOutputType(PreferedOutputType(t1, t2), t3);
		const size_t w = a.GetWidth();
		const size_t h = a.GetHeight();
		ANVIL_DEBUG_ASSERT(w == b.GetWidth() && h == b.GetHeight(), "ArithmeticOperations::CallOperation : Input images must be same size");
		dst.Allocate(type, w, h);
		(GetArithmeticOperations(type, instruction_set)->*Function)(
			const_cast<Image&>(a).ConvertTo(type).GetData(), 
			const_cast<Image&>(b).ConvertTo(type).GetData(),
			const_cast<Image&>(c).ConvertTo(type).GetData(),
			dst.GetData(),
			w * h,
			mask
		);
	}

	////


}}