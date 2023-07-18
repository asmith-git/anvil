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

namespace anvil { namespace compute {

	// ArithmeticOperations 

	static ArithmeticOperations* g_arithmetic_op_u8 = new details::ArithmeticOperationsCpp<uint8_t>();
	static ArithmeticOperations* g_arithmetic_op_u16 = new details::ArithmeticOperationsCpp<uint16_t>();
	static ArithmeticOperations* g_arithmetic_op_u32 = new details::ArithmeticOperationsCpp<uint32_t>();
	static ArithmeticOperations* g_arithmetic_op_u64 = new details::ArithmeticOperationsCpp<uint64_t>();
	static ArithmeticOperations* g_arithmetic_op_s8 = new details::ArithmeticOperationsCpp<int8_t>();
	static ArithmeticOperations* g_arithmetic_op_s16 = new details::ArithmeticOperationsCpp<int16_t>();
	static ArithmeticOperations* g_arithmetic_op_s32 = new details::ArithmeticOperationsCpp<int32_t>();
	static ArithmeticOperations* g_arithmetic_op_s64 = new details::ArithmeticOperationsCpp<int64_t>();
#if ANVIL_F8_SUPPORT
	static ArithmeticOperations* g_arithmetic_op_f8 = new details::ArithmeticOperationsCpp<float8_t>();
#endif
#if ANVIL_F16_SUPPORT
	static ArithmeticOperations* g_arithmetic_op_f16 = new details::ArithmeticOperationsCpp<float16_t>();
#endif
	static ArithmeticOperations* g_arithmetic_op_f32 = new details::ArithmeticOperationsCpp<float>();
	static ArithmeticOperations* g_arithmetic_op_f64 = new details::ArithmeticOperationsCpp<double>();

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
	static ArithmeticOperations* g_arithmetic_op_f32_sse = new details::ArithmeticOperationsSseF32();
	static ArithmeticOperations* g_arithmetic_op_f32_sse41 = new details::ArithmeticOperationsSse4F32();
	static ArithmeticOperations* g_arithmetic_op_f32_fma3 = new details::ArithmeticOperationsFmaF32();
	static ArithmeticOperations* g_arithmetic_op_f32_avx512 = new details::ArithmeticOperationsAvx512F32();
#endif

	ArithmeticOperations* ArithmeticOperations::GetArithmeticOperations(Type type, uint64_t instruction_set) {
		//! \todo Implement optimisations for different instruction sets (SSE, AVX, AVX-512, ect)

		//! \bug g_arithmetic_op_f32, ect will be null if called from within the constructor of another ArithmeticOperations

		ArithmeticOperations* ops = nullptr;

		Type t1 = type;
		t1.SetNumberOfChannels(1u);
		switch (t1.GetEnumeratedType()) {
		case ANVIL_8UX1:
			ops = g_arithmetic_op_u8;
			break;
		case ANVIL_16UX1:
			ops = g_arithmetic_op_u16;
			break;
		case ANVIL_32UX1:
			ops = g_arithmetic_op_u32;
			break;
		case ANVIL_64UX1:
			ops = g_arithmetic_op_u64;
			break;
		case ANVIL_8SX1:
			ops = g_arithmetic_op_s8;
			break;
		case ANVIL_16SX1:
			ops = g_arithmetic_op_s16;
			break;
		case ANVIL_32SX1:
			ops = g_arithmetic_op_s32;
			break;
		case ANVIL_64SX1:
			ops = g_arithmetic_op_s64;
			break;
#if ANVIL_F8_SUPPORT
		case ANVIL_8FX1:
			ops = g_arithmetic_op_f8;
			break;
#endif
#if ANVIL_F16_SUPPORT
		case ANVIL_16FX1:
			ops = g_arithmetic_op_f16;
			break;
#endif
		case ANVIL_32FX1:
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
			enum { AVX512_FLAGS = ASM_AVX512F | ASM_AVX512VL };
			if ((instruction_set & AVX512_FLAGS) == AVX512_FLAGS) {
				ops = g_arithmetic_op_f32_avx512;
			} else if (instruction_set & ASM_FMA3) {
				ops = g_arithmetic_op_f32_fma3;
			} else if (instruction_set & ASM_SSE41) {
				ops = g_arithmetic_op_f32_sse41;
			} else if (instruction_set & ASM_SSE) {
				ops = g_arithmetic_op_f32_sse;
			} else
#endif
			ops = g_arithmetic_op_f32;
			break;
		case ANVIL_64FX1:
			ops = g_arithmetic_op_f64;
			break;
		}
	
		return ops == nullptr ? nullptr : type.GetNumberOfChannels() == 1u ? ops : ops->_multi_channel_implementation;
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
		_type(type),
		_multi_channel_implementation(this)
	{}

	ArithmeticOperations::~ArithmeticOperations() {

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

	void ArithmeticOperations::SqrtMask(const void* src, void* dst, size_t count, const uint8_t* mask) const {
		Sqrt(src, dst, count);
		Mask(dst, src, dst, count, mask);
	}

	void ArithmeticOperations::CbrtMask(const void* src, void* dst, size_t count, const uint8_t* mask) const {
		Cbrt(src, dst, count);
		Mask(dst, src, dst, count, mask);
	}

	void ArithmeticOperations::NotMask(const void* src, void* dst, size_t count, const uint8_t* mask) const {
		Not(src, dst, count);
		Mask(dst, src, dst, count, mask);
	}

	void ArithmeticOperations::AddMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
		Add(lhs, rhs, dst, count);
		Mask(dst, lhs, dst, count, mask);
	}

	void ArithmeticOperations::SubtractMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
		Subtract(lhs, rhs, dst, count);
		Mask(dst, lhs, dst, count, mask);
	}

	void ArithmeticOperations::MultiplyMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
		Multiply(lhs, rhs, dst, count);
		Mask(dst, lhs, dst, count, mask);
	}

	void ArithmeticOperations::DivideMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
		Divide(lhs, rhs, dst, count);
		Mask(dst, lhs, dst, count, mask);
	}

	void ArithmeticOperations::AndMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
		And(lhs, rhs, dst, count);
		Mask(dst, lhs, dst, count, mask);
	}

	void ArithmeticOperations::OrMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
		Or(lhs, rhs, dst, count);
		Mask(dst, lhs, dst, count, mask);
	}

	void ArithmeticOperations::XorMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
		Xor(lhs, rhs, dst, count);
		Mask(dst, lhs, dst, count, mask);
	}

	void ArithmeticOperations::Nand(const void* lhs, const void* rhs, void* dst, size_t count) const {
		And(lhs, rhs, dst, count);
		Not(dst, dst, count);
	}

	void ArithmeticOperations::NandMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
		Nand(lhs, rhs, dst, count);
		Mask(dst, lhs, dst, count, mask);
	}

	void ArithmeticOperations::Nor(const void* lhs, const void* rhs, void* dst, size_t count) const {
		Or(lhs, rhs, dst, count);
		Not(dst, dst, count);
	}

	void ArithmeticOperations::NorMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
		Nor(lhs, rhs, dst, count);
		Mask(dst, lhs, dst, count, mask);
	}

	void ArithmeticOperations::Xnor(const void* lhs, const void* rhs, void* dst, size_t count) const {
		And(lhs, rhs, dst, count);
		Not(dst, dst, count);
	}

	void ArithmeticOperations::XnorMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const {
		Xnor(lhs, rhs, dst, count);
		Mask(dst, lhs, dst, count, mask);
	}

	void ArithmeticOperations::MultiplyAdd(const void* a, const void* b, const void* c, void* dst, size_t count) const {
		Multiply(a, b, dst, count);
		Add(dst, c, dst, count);
	}

	void ArithmeticOperations::MultiplyAddMask(const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask) const {
		MultiplyAdd(a, b, c, dst, count);
		Mask(dst, a, dst, count, mask);
	}

	void ArithmeticOperations::MultiplySubtract(const void* a, const void* b, const void* c, void* dst, size_t count) const {
		Multiply(a, b, dst, count);
		Subtract(dst, c, dst, count);
	}

	void ArithmeticOperations::MultiplySubtractMask(const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask) const {
		MultiplySubtract(a, b, c, dst, count);
		Mask(dst, a, dst, count, mask);
	}


}}