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

	template<>
	class ArithmeticOperationsCpp<float16_t> final : public ArithmeticOperations {
	private:

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
		void (*ConvertToF32)(const float16_t* src, float* dst, const size_t size);
		void (*ConvertToF16)(const float* src, float16_t* dst, const size_t size);
		ArithmeticOperations* _u16;
		ArithmeticOperations* _f32;

		void CallF32Operation(
			const void* src, void* dst, size_t count,
			void(ArithmeticOperations::* Function)(const void* src, void* dst, size_t count) const
		) const {
			float* buffer_a = static_cast<float*>(_malloca(sizeof(T) * count));
			ANVIL_RUNTIME_ASSERT(buffer_a != nullptr, "anvil::compute::details::ArithmeticOperationsCpp<float16_t>::Call1Input : Failed to allocate memory");
			(*ConvertToF32)(static_cast<const float16_t*>(src), buffer_a, count);

			(_f32->*Function)(buffer_a, buffer_a, count);

			(*ConvertToF16)(buffer_a, static_cast<float16_t*>(dst), count);
			_freea(buffer_a);
		}

		void CallF32Operation(
			const void* src, void* dst, size_t count, const uint8_t* mask,
			void(ArithmeticOperations::* Function)(const void* src, void* dst, size_t count, const uint8_t* mask) const
		) const {
			float* buffer_a = static_cast<float*>(_malloca(sizeof(T) * count));
			ANVIL_RUNTIME_ASSERT(buffer_a != nullptr, "anvil::compute::details::ArithmeticOperationsCpp<float16_t>::Call1Input : Failed to allocate memory");
			(*ConvertToF32)(static_cast<const float16_t*>(src), buffer_a, count);

			(_f32->*Function)(buffer_a, buffer_a, count, mask);

			(*ConvertToF16)(buffer_a, static_cast<float16_t*>(dst), count);
			_freea(buffer_a);
		}

		void CallF32Operation(
			const void* lhs, const void* rhs, void* dst, size_t count, 
			void(ArithmeticOperations::*Function)(const void* lhs, const void* rhs, void* dst, size_t count) const
		) const {
			float* buffer_a = static_cast<float*>(_malloca(sizeof(T) * count * 2));
			ANVIL_RUNTIME_ASSERT(buffer_a != nullptr, "anvil::compute::details::ArithmeticOperationsCpp<float16_t>::Call2Inputs : Failed to allocate memory");
			float* buffer_b = buffer_a + count;
			(*ConvertToF32)(static_cast<const float16_t*>(lhs), buffer_a, count);
			(*ConvertToF32)(static_cast<const float16_t*>(rhs), buffer_b, count);

			(_f32->*Function)(buffer_a, buffer_b, buffer_a, count);

			(*ConvertToF16)(buffer_a, static_cast<float16_t*>(dst), count);
			_freea(buffer_a);
		}

		void CallF32Operation(
			const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask,
			void(ArithmeticOperations::* Function)(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const
		) const {
			float* buffer_a = static_cast<float*>(_malloca(sizeof(T) * count * 2));
			ANVIL_RUNTIME_ASSERT(buffer_a != nullptr, "anvil::compute::details::ArithmeticOperationsCpp<float16_t>::Call2Inputs : Failed to allocate memory");
			float* buffer_b = buffer_a + count;
			(*ConvertToF32)(static_cast<const float16_t*>(lhs), buffer_a, count);
			(*ConvertToF32)(static_cast<const float16_t*>(rhs), buffer_b, count);

			(_f32->*Function)(buffer_a, buffer_b, buffer_a, count, mask);

			(*ConvertToF16)(buffer_a, static_cast<float16_t*>(dst), count);
			_freea(buffer_a);
		}

		void CallF32Operation(
			const void* a, const void* b, const void* c, void* dst, size_t count,
			void(ArithmeticOperations::* Function)(const void* a, const void* b, const void* c, void* dst, size_t count) const
		) const {
			float* buffer_a = static_cast<float*>(_malloca(sizeof(T) * count * 3));
			ANVIL_RUNTIME_ASSERT(buffer_a != nullptr, "anvil::compute::details::ArithmeticOperationsCpp<float16_t>::Call3Inputs : Failed to allocate memory");
			float* buffer_b = buffer_a + count;
			float* buffer_c = buffer_b + count;
			(*ConvertToF32)(static_cast<const float16_t*>(a), buffer_a, count);
			(*ConvertToF32)(static_cast<const float16_t*>(b), buffer_b, count);
			(*ConvertToF32)(static_cast<const float16_t*>(c), buffer_c, count);

			(_f32->*Function)(buffer_a, buffer_b, buffer_c, buffer_a, count);

			(*ConvertToF16)(buffer_a, static_cast<float16_t*>(dst), count);
			_freea(buffer_a);
		}

		void CallF32Operation(
			const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask,
			void(ArithmeticOperations::* Function)(const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask) const
		) const {
			float* buffer_a = static_cast<float*>(_malloca(sizeof(T) * count * 3));
			ANVIL_RUNTIME_ASSERT(buffer_a != nullptr, "anvil::compute::details::ArithmeticOperationsCpp<float16_t>::Call3Inputs : Failed to allocate memory");
			float* buffer_b = buffer_a + count;
			float* buffer_c = buffer_b + count;
			(*ConvertToF32)(static_cast<const float16_t*>(a), buffer_a, count);
			(*ConvertToF32)(static_cast<const float16_t*>(b), buffer_b, count);
			(*ConvertToF32)(static_cast<const float16_t*>(c), buffer_c, count);

			(_f32->*Function)(buffer_a, buffer_b, buffer_c, buffer_a, count, mask);

			(*ConvertToF16)(buffer_a, static_cast<float16_t*>(dst), count);
			_freea(buffer_a);
		}
	public:
		typedef float16_t T;

		ArithmeticOperationsCpp() :
			ArithmeticOperations(EnumFromType<T>::value)
		{
			ConvertToF32 = &ConvertToF32_Cpp;
			ConvertToF16 = &ConvertToF16_Cpp;

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
			if (SupportedInstructionSets & ASM_F16C) {
				ConvertToF32 = &ConvertToF32_FP16;
				ConvertToF16 = &ConvertToF16_FP16;
			}
#endif
		}

		virtual ~ArithmeticOperationsCpp() {

		}

		virtual void Initialise() {
			ArithmeticOperations::Initialise();
			_u16 = GetArithmeticOperations(ANVIL_16UX1);
			_f32 = GetArithmeticOperations(ANVIL_32FX1);
		}

		// 1 input

		void Sqrt(const void* src, void* dst, size_t count) const final {
			CallF32Operation(src, dst, count, &ArithmeticOperations::Sqrt);
		}

		void SqrtMask(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallF32Operation(src, dst, count, mask, &ArithmeticOperations::SqrtMask);
		}

		void Cbrt(const void* src, void* dst, size_t count) const final {
			CallF32Operation(src, dst, count, &ArithmeticOperations::Cbrt);
		}

		void CbrtMask(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallF32Operation(src, dst, count, mask, &ArithmeticOperations::CbrtMask);
		}

		void Not(const void* src, void* dst, size_t count) const final {
			CallF32Operation(src, dst, count, &ArithmeticOperations::Not);
		}

		void NotMask(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallF32Operation(src, dst, count, mask, &ArithmeticOperations::NotMask);
		}

		// 2 inputs

		void Mask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			CallF32Operation(lhs, rhs, dst, count, mask, &ArithmeticOperations::Mask);
		}

		void Add(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			CallF32Operation(lhs, rhs, dst, count, &ArithmeticOperations::Add);
		}

		void AddMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			CallF32Operation(lhs, rhs, dst, count, mask, &ArithmeticOperations::AddMask);
		}

		void Subtract(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			CallF32Operation(lhs, rhs, dst, count, &ArithmeticOperations::Subtract);
		}

		void SubtractMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			CallF32Operation(lhs, rhs, dst, count, mask, &ArithmeticOperations::SubtractMask);
		}

		void Multiply(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			CallF32Operation(lhs, rhs, dst, count, &ArithmeticOperations::Multiply);
		}

		void MultiplyMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			CallF32Operation(lhs, rhs, dst, count, mask, &ArithmeticOperations::MultiplyMask);
		}

		void Divide(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			CallF32Operation(lhs, rhs, dst, count, &ArithmeticOperations::Divide);
		}

		void DivideMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			CallF32Operation(lhs, rhs, dst, count, mask, &ArithmeticOperations::DivideMask);
		}

		void And(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			_u16->And(lhs, rhs, dst, count);
		}

		void AndMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			_u16->AndMask(lhs, rhs, dst, count, mask);
		}

		void Or(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			_u16->Or(lhs, rhs, dst, count);
		}

		void OrMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			_u16->OrMask(lhs, rhs, dst, count, mask);
		}

		void Xor(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			_u16->Xor(lhs, rhs, dst, count);
		}

		void XorMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			_u16->XorMask(lhs, rhs, dst, count, mask);
		}

		void Nand(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			_u16->Nand(lhs, rhs, dst, count);
		}

		void NandMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			_u16->NandMask(lhs, rhs, dst, count, mask);
		}

		void Nor(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			_u16->Nor(lhs, rhs, dst, count);
		}

		void NorMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			_u16->NorMask(lhs, rhs, dst, count, mask);
		}

		void Xnor(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			_u16->Xnor(lhs, rhs, dst, count);
		}

		void XnorMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			_u16->XnorMask(lhs, rhs, dst, count, mask);
		}

		// 3 inputs

		void MultiplyAdd(const void* a, const void* b, const void* c, void* dst, size_t count) const final {
			CallF32Operation(a, b, c, dst, count, &ArithmeticOperations::MultiplyAdd);
		}

		void MultiplyAddMask(const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask) const final {
			CallF32Operation(a, b, c, dst, count, mask, &ArithmeticOperations::MultiplyAddMask);
		}

		void MultiplySubtract(const void* a, const void* b, const void* c, void* dst, size_t count) const final {
			CallF32Operation(a, b, c, dst, count, &ArithmeticOperations::MultiplySubtract);
		}

		void MultiplySubtractMask(const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask) const final {
			CallF32Operation(a, b, c, dst, count, mask, &ArithmeticOperations::MultiplySubtractMask);
		}

	};

}}}

#endif

#endif