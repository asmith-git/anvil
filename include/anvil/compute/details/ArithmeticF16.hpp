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

#ifndef ANVIL_COMPUTE_ARITHMETIC_F16_HPP
#define ANVIL_COMPUTE_ARITHMETIC_F16_HPP

#include "anvil/compute/details/ArithmeticCpp.hpp"

#if ANVIL_F16_SUPPORT
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
	#include <immintrin.h>
#endif

namespace anvil { namespace compute { namespace details {

	class ArithmeticOperationsFP16 final : public ArithmeticOperationsCpp<float16_t> {
	private:

		void CallConversionFP16(
			const void* src, void* dst, size_t count,
			void(ArithmeticOperations::* Function)(const void* src, void* dst, size_t count) const
		) const {
			void* buffer = _malloca(sizeof(float) * count);
			_ConvertToF32((float16_t*)src, (float*)buffer, count); 
			(_f32->*Function)(buffer, dst, count);
			_freea(buffer);
		}

		static void ConvertToF32_Cpp(const float16_t* src, float* dst, const size_t size) {
			for (size_t i = 0u; i < size; ++i) dst[i] = static_cast<float>(src[i]);
		}

		static void ConvertToF16_Cpp(const float* src, float16_t* dst, const size_t size) {
			for (size_t i = 0u; i < size; ++i) dst[i] = static_cast<float16_t>(src[i]);
		}

		static void ConvertToF32_FP16(const float16_t* src, float* dst, const size_t size) {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
			size_t aligned_size = (size / 16) * 16;
			for (size_t i = 0u; i < aligned_size; i += 16) {
				__m128i xmm0 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(src + i));
				__m256 xmm1 = _mm256_cvtph_ps(xmm0);
				_mm256_storeu_ps(dst + i, xmm1);
			}

			src -= aligned_size;
			dst += aligned_size;
#endif
			ConvertToF32_Cpp(src, dst, size);
		}

		static void ConvertToF16_FP16(const float* src, float16_t* dst, const size_t size) {
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
			size_t aligned_size = (size / 16) * 16;
			for (size_t i = 0u; i < aligned_size; i += 16) {
				__m256 xmm0 = _mm256_loadu_ps(src + i);
				__m128i xmm1 = _mm256_cvtps_ph(xmm0, _MM_FROUND_TO_NEAREST_INT);
				_mm_storeu_si128(reinterpret_cast<__m128i*>(dst + i), xmm1);
			}

			src -= aligned_size;
			dst += aligned_size;

			src -= aligned_size;
			dst += aligned_size;
#endif
			ConvertToF16_Cpp(src, dst, size);
		}
		void (*_ConvertToF32)(const float16_t* src, float* dst, const size_t size);
		void (*_ConvertToF16)(const float* src, float16_t* dst, const size_t size);
		ArithmeticOperations* _u16;
		ArithmeticOperations* _f32;

		void CallOperation(
			const void* src, void* dst, size_t count,
			void(ArithmeticOperations::* Function)(const void* src, void* dst, size_t count) const
		) const {
			float* buffer_a = static_cast<float*>(_malloca(sizeof(float) * count));
			ANVIL_RUNTIME_ASSERT(buffer_a != nullptr, "anvil::compute::details::ArithmeticOperationsCpp<float16_t>::Call1Input : Failed to allocate memory");
			(*_ConvertToF32)(static_cast<const float16_t*>(src), buffer_a, count);

			(_f32->*Function)(buffer_a, buffer_a, count);

			(*_ConvertToF16)(buffer_a, static_cast<float16_t*>(dst), count);
			_freea(buffer_a);
		}

		void CallOperation(
			const void* src, void* dst, size_t count, const uint8_t* mask,
			void(ArithmeticOperations::* Function)(const void* src, void* dst, size_t count, const uint8_t* mask) const
		) const {
			float* buffer_a = static_cast<float*>(_malloca(sizeof(float) * count));
			ANVIL_RUNTIME_ASSERT(buffer_a != nullptr, "anvil::compute::details::ArithmeticOperationsCpp<float16_t>::Call1Input : Failed to allocate memory");
			(*_ConvertToF32)(static_cast<const float16_t*>(src), buffer_a, count);

			(_f32->*Function)(buffer_a, buffer_a, count, mask);

			(*_ConvertToF16)(buffer_a, static_cast<float16_t*>(dst), count);
			_freea(buffer_a);
		}

		void CallOperation(
			const void* lhs, const void* rhs, void* dst, size_t count, 
			void(ArithmeticOperations::*Function)(const void* lhs, const void* rhs, void* dst, size_t count) const
		) const {
			float* buffer_a = static_cast<float*>(_malloca(sizeof(float) * count * 2));
			ANVIL_RUNTIME_ASSERT(buffer_a != nullptr, "anvil::compute::details::ArithmeticOperationsCpp<float16_t>::Call2Inputs : Failed to allocate memory");
			float* buffer_b = buffer_a + count;
			(*_ConvertToF32)(static_cast<const float16_t*>(lhs), buffer_a, count);
			(*_ConvertToF32)(static_cast<const float16_t*>(rhs), buffer_b, count);

			(_f32->*Function)(buffer_a, buffer_b, buffer_a, count);

			(*_ConvertToF16)(buffer_a, static_cast<float16_t*>(dst), count);
			_freea(buffer_a);
		}

		void CallOperation(
			const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask,
			void(ArithmeticOperations::* Function)(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const
		) const {
			float* buffer_a = static_cast<float*>(_malloca(sizeof(float) * count * 2));
			ANVIL_RUNTIME_ASSERT(buffer_a != nullptr, "anvil::compute::details::ArithmeticOperationsCpp<float16_t>::Call2Inputs : Failed to allocate memory");
			float* buffer_b = buffer_a + count;
			(*_ConvertToF32)(static_cast<const float16_t*>(lhs), buffer_a, count);
			(*_ConvertToF32)(static_cast<const float16_t*>(rhs), buffer_b, count);

			(_f32->*Function)(buffer_a, buffer_b, buffer_a, count, mask);

			(*_ConvertToF16)(buffer_a, static_cast<float16_t*>(dst), count);
			_freea(buffer_a);
		}

		void CallOperation(
			const void* a, const void* b, const void* c, void* dst, size_t count,
			void(ArithmeticOperations::* Function)(const void* a, const void* b, const void* c, void* dst, size_t count) const
		) const {
			float* buffer_a = static_cast<float*>(_malloca(sizeof(float) * count * 3));
			ANVIL_RUNTIME_ASSERT(buffer_a != nullptr, "anvil::compute::details::ArithmeticOperationsCpp<float16_t>::Call3Inputs : Failed to allocate memory");
			float* buffer_b = buffer_a + count;
			float* buffer_c = buffer_b + count;
			(*_ConvertToF32)(static_cast<const float16_t*>(a), buffer_a, count);
			(*_ConvertToF32)(static_cast<const float16_t*>(b), buffer_b, count);
			(*_ConvertToF32)(static_cast<const float16_t*>(c), buffer_c, count);

			(_f32->*Function)(buffer_a, buffer_b, buffer_c, buffer_a, count);

			(*_ConvertToF16)(buffer_a, static_cast<float16_t*>(dst), count);
			_freea(buffer_a);
		}

		void CallOperation(
			const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask,
			void(ArithmeticOperations::* Function)(const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask) const
		) const {
			float* buffer_a = static_cast<float*>(_malloca(sizeof(float) * count * 3));
			ANVIL_RUNTIME_ASSERT(buffer_a != nullptr, "anvil::compute::details::ArithmeticOperationsCpp<float16_t>::Call3Inputs : Failed to allocate memory");
			float* buffer_b = buffer_a + count;
			float* buffer_c = buffer_b + count;
			(*_ConvertToF32)(static_cast<const float16_t*>(a), buffer_a, count);
			(*_ConvertToF32)(static_cast<const float16_t*>(b), buffer_b, count);
			(*_ConvertToF32)(static_cast<const float16_t*>(c), buffer_c, count);

			(_f32->*Function)(buffer_a, buffer_b, buffer_c, buffer_a, count, mask);

			(*_ConvertToF16)(buffer_a, static_cast<float16_t*>(dst), count);
			_freea(buffer_a);
		}
	public:
		typedef float16_t T;

		ArithmeticOperationsFP16() :
			ArithmeticOperationsCpp()
		{
			_ConvertToF32 = &ConvertToF32_Cpp;
			_ConvertToF16 = &ConvertToF16_Cpp;

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
			if (SupportedInstructionSets & ASM_F16C) {
				_ConvertToF32 = &ConvertToF32_FP16;
				_ConvertToF16 = &ConvertToF16_FP16;
			}
#endif
		}

		virtual ~ArithmeticOperationsFP16() {

		}

		virtual void Initialise() {
			ArithmeticOperationsCpp::Initialise();
			_u16 = GetArithmeticOperations(ANVIL_16UX1);
			_f32 = GetArithmeticOperations(ANVIL_32FX1);
		}

		ANVIL_STRONG_INLINE void ConvertF32ToF16(const void* src, void* dst, size_t count) const {
			_ConvertToF16((float*)src, (float16_t*)dst, count);
		}

		// 1 input

		void ConvertToU8(const void* src, void* dst, size_t count) const final {
			CallConversionFP16(src, dst, count, &ArithmeticOperations::ConvertToU8);
		}

		void ConvertToU16(const void* src, void* dst, size_t count) const final {
			CallConversionFP16(src, dst, count, &ArithmeticOperations::ConvertToU16);
		}

		void ConvertToU32(const void* src, void* dst, size_t count) const final {
			CallConversionFP16(src, dst, count, &ArithmeticOperations::ConvertToU32);
		}

		void ConvertToU64(const void* src, void* dst, size_t count) const final {
			CallConversionFP16(src, dst, count, &ArithmeticOperations::ConvertToU64);
		}

		void ConvertToS8(const void* src, void* dst, size_t count) const final {
			CallConversionFP16(src, dst, count, &ArithmeticOperations::ConvertToS8);
		}

		void ConvertToS16(const void* src, void* dst, size_t count) const final {
			CallConversionFP16(src, dst, count, &ArithmeticOperations::ConvertToS16);
		}

		void ConvertToS32(const void* src, void* dst, size_t count) const final {
			CallConversionFP16(src, dst, count, &ArithmeticOperations::ConvertToS32);
		}

		void ConvertToS64(const void* src, void* dst, size_t count) const final {
			CallConversionFP16(src, dst, count, &ArithmeticOperations::ConvertToS64);
		}

#if ANVIL_F8_SUPPORT
		void ConvertToF8(const void* src, void* dst, size_t count) const final {
			CallConversionFP16(src, dst, count, &ArithmeticOperations::ConvertToF8);
		}
#endif

#if ANVIL_F16_SUPPORT
		void ConvertToF16(const void* src, void* dst, size_t count) const final {
			memcpy(dst, src, sizeof(float16_t) * count);
		}
#endif
		void ConvertToF32(const void* src, void* dst, size_t count) const final {
			CallConversionFP16(src, dst, count, &ArithmeticOperations::ConvertToF32);
		}

		void ConvertToF64(const void* src, void* dst, size_t count) const final {
			CallConversionFP16(src, dst, count, &ArithmeticOperations::ConvertToF64);
		}

		void Sqrt(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Sqrt);
		}

		void Sqrt(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Sqrt);
		}

		void Cbrt(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Cbrt);
		}

		void Cbrt(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Cbrt);
		}

		void Not(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Not);
		}

		void Not(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Not);
		}

		void Round(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Round);
		}

		void Floor(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Floor);
		}

		void Ceil(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Ceil);
		}

		virtual void Cos(const void* src, void* dst, size_t count) const {
			CallOperation(src, dst, count, &ArithmeticOperations::Cos);
		}

		virtual void Sin(const void* src, void* dst, size_t count) const {
			CallOperation(src, dst, count, &ArithmeticOperations::Sin);
		}

		virtual void Tan(const void* src, void* dst, size_t count) const {
			CallOperation(src, dst, count, &ArithmeticOperations::Tan);
		}

		virtual void Acos(const void* src, void* dst, size_t count) const {
			CallOperation(src, dst, count, &ArithmeticOperations::Acos);
		}

		virtual void Asin(const void* src, void* dst, size_t count) const {
			CallOperation(src, dst, count, &ArithmeticOperations::Asin);
		}

		virtual void Atan(const void* src, void* dst, size_t count) const {
			CallOperation(src, dst, count, &ArithmeticOperations::Atan);
		}

		virtual void Cosh(const void* src, void* dst, size_t count) const {
			CallOperation(src, dst, count, &ArithmeticOperations::Cosh);
		}

		virtual void Sinh(const void* src, void* dst, size_t count) const {
			CallOperation(src, dst, count, &ArithmeticOperations::Sinh);
		}

		virtual void Tanh(const void* src, void* dst, size_t count) const {
			CallOperation(src, dst, count, &ArithmeticOperations::Tanh);
		}

		virtual void Acosh(const void* src, void* dst, size_t count) const {
			CallOperation(src, dst, count, &ArithmeticOperations::Acosh);
		}

		virtual void Asinh(const void* src, void* dst, size_t count) const {
			CallOperation(src, dst, count, &ArithmeticOperations::Asinh);
		}

		virtual void Atanh(const void* src, void* dst, size_t count) const {
			CallOperation(src, dst, count, &ArithmeticOperations::Atanh);
		}

		virtual void Abs(const void* src, void* dst, size_t count) const {
			CallOperation(src, dst, count, &ArithmeticOperations::Abs);
		}

		void Round(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Round);
		}

		void Floor(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Floor);
		}

		void Ceil(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Ceil);
		}

		virtual void Cos(const void* src, void* dst, size_t count, const uint8_t* mask) const {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Cos);
		}

		virtual void Sin(const void* src, void* dst, size_t count, const uint8_t* mask) const {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Sin);
		}

		virtual void Tan(const void* src, void* dst, size_t count, const uint8_t* mask) const {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Tan);
		}

		virtual void Acos(const void* src, void* dst, size_t count, const uint8_t* mask) const {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Acos);
		}

		virtual void Asin(const void* src, void* dst, size_t count, const uint8_t* mask) const {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Asin);
		}

		virtual void Atan(const void* src, void* dst, size_t count, const uint8_t* mask) const {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Atan);
		}

		virtual void Cosh(const void* src, void* dst, size_t count, const uint8_t* mask) const {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Cosh);
		}

		virtual void Sinh(const void* src, void* dst, size_t count, const uint8_t* mask) const {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Sinh);
		}

		virtual void Tanh(const void* src, void* dst, size_t count, const uint8_t* mask) const {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Tanh);
		}

		virtual void Acosh(const void* src, void* dst, size_t count, const uint8_t* mask) const {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Acosh);
		}

		virtual void Asinh(const void* src, void* dst, size_t count, const uint8_t* mask) const {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Asinh);
		}

		virtual void Atanh(const void* src, void* dst, size_t count, const uint8_t* mask) const {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Atanh);
		}

		virtual void Abs(const void* src, void* dst, size_t count, const uint8_t* mask) const {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Abs);
		}


		// 2 inputs

		void Mask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::Mask);
		}

		void Add(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			CallOperation(lhs, rhs, dst, count, &ArithmeticOperations::Add);
		}

		void Add(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::Add);
		}

		void Subtract(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			CallOperation(lhs, rhs, dst, count, &ArithmeticOperations::Subtract);
		}

		void Subtract(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::Subtract);
		}

		void Multiply(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			CallOperation(lhs, rhs, dst, count, &ArithmeticOperations::Multiply);
		}

		void Multiply(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::Multiply);
		}

		void Divide(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			CallOperation(lhs, rhs, dst, count, &ArithmeticOperations::Divide);
		}

		void Divide(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::Divide);
		}

		void And(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			_u16->And(lhs, rhs, dst, count);
		}

		void And(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			_u16->And(lhs, rhs, dst, count, mask);
		}

		void Or(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			_u16->Or(lhs, rhs, dst, count);
		}

		void Or(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			_u16->Or(lhs, rhs, dst, count, mask);
		}

		void Xor(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			_u16->Xor(lhs, rhs, dst, count);
		}

		void Xor(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			_u16->Xor(lhs, rhs, dst, count, mask);
		}

		void Nand(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			_u16->Nand(lhs, rhs, dst, count);
		}

		void Nand(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			_u16->Nand(lhs, rhs, dst, count, mask);
		}

		void Nor(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			_u16->Nor(lhs, rhs, dst, count);
		}

		void Nor(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			_u16->Nor(lhs, rhs, dst, count, mask);
		}

		void Xnor(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			_u16->Xnor(lhs, rhs, dst, count);
		}

		void Xnor(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			_u16->Xnor(lhs, rhs, dst, count, mask);
		}

		void Power(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			CallOperation(lhs, rhs, dst, count, &ArithmeticOperations::Power);
		}

		void Hypotenuse(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			CallOperation(lhs, rhs, dst, count, &ArithmeticOperations::Hypotenuse);
		}

		void Minimum(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			CallOperation(lhs, rhs, dst, count, &ArithmeticOperations::Minimum);
		}

		void Maximum(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			CallOperation(lhs, rhs, dst, count, &ArithmeticOperations::Maximum);
		}

		// 3 inputs

		void MultiplyAdd(const void* a, const void* b, const void* c, void* dst, size_t count) const final {
			CallOperation(a, b, c, dst, count, &ArithmeticOperations::MultiplyAdd);
		}

		void MultiplyAdd(const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(a, b, c, dst, count, mask, &ArithmeticOperations::MultiplyAdd);
		}

		void MultiplySubtract(const void* a, const void* b, const void* c, void* dst, size_t count) const final {
			CallOperation(a, b, c, dst, count, &ArithmeticOperations::MultiplySubtract);
		}

		void MultiplySubtract(const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(a, b, c, dst, count, mask, &ArithmeticOperations::MultiplySubtract);
		}

	};

}}}

#endif

#endif