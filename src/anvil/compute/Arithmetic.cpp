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

namespace anvil { namespace compute {

	// ArithmeticOperations 

	ArithmeticOperations* ArithmeticOperations::GetArithmeticOperations(Type type, uint64_t instruction_set) {
		type.SetNumberOfChannels(1u);

		//! \todo Implement optimisations for different instruction sets (SSE, AVX, AVX-512, ect)
		instruction_set = 0u;

		static details::ArithmeticOperationsCpp<uint8_t> u8;
		static details::ArithmeticOperationsCpp<uint16_t> u16;
		static details::ArithmeticOperationsCpp<uint32_t> u32;
		static details::ArithmeticOperationsCpp<uint64_t> u64;
		static details::ArithmeticOperationsCpp<int8_t> s8;
		static details::ArithmeticOperationsCpp<int16_t> s16;
		static details::ArithmeticOperationsCpp<int32_t> s32;
		static details::ArithmeticOperationsCpp<int64_t> s64;
#if ANVIL_F8_SUPPORT
		static details::ArithmeticOperationsCpp<float8_t> f8;
#endif
#if ANVIL_F16_SUPPORT
		static details::ArithmeticOperationsCpp<float16_t> f16;
#endif
		static details::ArithmeticOperationsCpp<float> f32;
		static details::ArithmeticOperationsCpp<double> f64;

		switch (type.GetEnumeratedType()) {
		case ANVIL_8UX1:
			return &u8;
		case ANVIL_16UX1:
			return &u16;
		case ANVIL_32UX1:
			return &u32;
		case ANVIL_64UX1:
			return &u64;
		case ANVIL_8SX1:
			return &s8;
		case ANVIL_16SX1:
			return &s16;
		case ANVIL_32SX1:
			return &s32;
		case ANVIL_64SX1:
			return &s64;
#if ANVIL_F8_SUPPORT
		case ANVIL_8FX1:
			return &f8;
#endif
#if ANVIL_F16_SUPPORT
		case ANVIL_16FX1:
			return &f16;
#endif
		case ANVIL_32FX1:
			return &f32;
		case ANVIL_64FX1:
			return &f64;
		}
	
		return nullptr;
	}

	ArithmeticOperations::ArithmeticOperations(Type type) :
		_type(type)
	{}

	ArithmeticOperations::~ArithmeticOperations() {

	}

	void ArithmeticOperations::Mask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) {
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

	void ArithmeticOperations::SqrtMask(const void* src, void* dst, size_t count, const uint8_t* mask) {
		Sqrt(src, dst, count);
		Mask(dst, src, dst, count, mask);
	}

	void ArithmeticOperations::CbrtMask(const void* src, void* dst, size_t count, const uint8_t* mask) {
		Cbrt(src, dst, count);
		Mask(dst, src, dst, count, mask);
	}

	void ArithmeticOperations::NotMask(const void* src, void* dst, size_t count, const uint8_t* mask) {
		Not(src, dst, count);
		Mask(dst, src, dst, count, mask);
	}

	void ArithmeticOperations::AddMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) {
		Add(lhs, rhs, dst, count);
		Mask(dst, lhs, dst, count, mask);
	}

	void ArithmeticOperations::SubtractMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) {
		Subtract(lhs, rhs, dst, count);
		Mask(dst, lhs, dst, count, mask);
	}

	void ArithmeticOperations::MultiplyMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) {
		Multiply(lhs, rhs, dst, count);
		Mask(dst, lhs, dst, count, mask);
	}

	void ArithmeticOperations::DivideMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) {
		Divide(lhs, rhs, dst, count);
		Mask(dst, lhs, dst, count, mask);
	}

	void ArithmeticOperations::AndMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) {
		And(lhs, rhs, dst, count);
		Mask(dst, lhs, dst, count, mask);
	}

	void ArithmeticOperations::OrMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) {
		Or(lhs, rhs, dst, count);
		Mask(dst, lhs, dst, count, mask);
	}

	void ArithmeticOperations::XorMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) {
		Xor(lhs, rhs, dst, count);
		Mask(dst, lhs, dst, count, mask);
	}

	void ArithmeticOperations::Nand(const void* lhs, const void* rhs, void* dst, size_t count) {
		And(lhs, rhs, dst, count);
		Not(dst, dst, count);
	}

	void ArithmeticOperations::NandMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) {
		Nand(lhs, rhs, dst, count);
		Mask(dst, lhs, dst, count, mask);
	}

	void ArithmeticOperations::Nor(const void* lhs, const void* rhs, void* dst, size_t count) {
		Or(lhs, rhs, dst, count);
		Not(dst, dst, count);
	}

	void ArithmeticOperations::NorMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) {
		Nor(lhs, rhs, dst, count);
		Mask(dst, lhs, dst, count, mask);
	}

	void ArithmeticOperations::Xnor(const void* lhs, const void* rhs, void* dst, size_t count) {
		And(lhs, rhs, dst, count);
		Not(dst, dst, count);
	}

	void ArithmeticOperations::XnorMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) {
		Xnor(lhs, rhs, dst, count);
		Mask(dst, lhs, dst, count, mask);
	}

	void ArithmeticOperations::MultiplyAdd(const void* a, const void* b, const void* c, void* dst, size_t count) {
		Multiply(a, b, dst, count);
		Add(dst, c, dst, count);
	}

	void ArithmeticOperations::MultiplyAddMask(const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask) {
		MultiplyAdd(a, b, c, dst, count);
		Mask(dst, a, dst, count, mask);
	}

	void ArithmeticOperations::MultiplySubtract(const void* a, const void* b, const void* c, void* dst, size_t count) {
		Multiply(a, b, dst, count);
		Subtract(dst, c, dst, count);
	}

	void ArithmeticOperations::SubtractAddMask(const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask) {
		MultiplySubtract(a, b, c, dst, count);
		Mask(dst, a, dst, count, mask);
	}


}}