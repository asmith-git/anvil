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

#ifndef ANVIL_COMPUTE_ARITHMETIC_MULTICHANNEL_HPP
#define ANVIL_COMPUTE_ARITHMETIC_MULTICHANNEL_HPP

#include "anvil/compute/Arithmetic.hpp"
#include "anvil/byte-pipe/BytePipeBits.hpp"
#include <cmath>

namespace anvil { namespace compute { namespace details {

	class ArithmeticOperationsMultiChannel final : public ArithmeticOperations {
	private:
		ArithmeticOperations& _parent;
		void (ArithmeticOperationsMultiChannel::* ExpandMask)(const uint8_t* src, uint8_t* dst, size_t count) const;

		inline size_t NewMaskSize(size_t count) const {
			return count * (_type.GetNumberOfChannels() + 1);
		}

		/*!	
		*	\brief Duplicate each bit in the mask for the number of channels
		*/
		void ExpandMaskUnoptimised(const uint8_t* src, uint8_t* dst, size_t count) const {
			BytePipe::BitOutputStream bitstream(dst);
			const size_t channels = _type.GetNumberOfChannels();

			while (count >= 8u) {
				uint32_t m = *src;
				bitstream.WriteBits(m & 1u ? UINT32_MAX : 0u, channels);
				bitstream.WriteBits(m & 2u ? UINT32_MAX : 0u, channels);
				bitstream.WriteBits(m & 4u ? UINT32_MAX : 0u, channels);
				bitstream.WriteBits(m & 8u ? UINT32_MAX : 0u, channels);
				bitstream.WriteBits(m & 16u ? UINT32_MAX : 0u, channels);
				bitstream.WriteBits(m & 32u ? UINT32_MAX : 0u, channels);
				bitstream.WriteBits(m & 64u ? UINT32_MAX : 0u, channels);
				bitstream.WriteBits(m & 128u ? UINT32_MAX : 0u, channels);
				count -= 8u;
				++src;
			}

			if (count > 0) {
				uint32_t m = *src;
				for (size_t i = 0u; i < count; ++i) {
					bitstream.WriteBits(m & 1u ? UINT32_MAX : 0u, channels);
					m >>= 1u;
				}
			}
		}

		void ExpandMask1(const uint8_t* src, uint8_t* dst, size_t count) const {
			memcpy(dst, src, (count / 8) + ((count % 8) == 0 ? 0 : 1));
		}

		inline void CallOperation(
			const void* src, void* dst, size_t count,
			void(ArithmeticOperations::* Function)(const void* src, void* dst, size_t count) const
		) const {
			// Call the parent function but with a higher count
			(_parent.*Function)(src, dst, count * _type.GetNumberOfChannels());;
		}

		void CallOperation(
			const void* src, void* dst, size_t count, const uint8_t* mask,
			void(ArithmeticOperations::* Function)(const void* src, void* dst, size_t count, const uint8_t* mask) const
		) const {
			// Expand the mask to the correct size
			const size_t channels = _type.GetNumberOfChannels();
			uint8_t* mask2 = static_cast<uint8_t*>(_malloca(NewMaskSize(count)));
			(this->*ExpandMask)(mask, mask2, count);

			// Call the parent function but with a higher count
			(_parent.*Function)(src, dst, count * channels, mask2);

			// Free any memory that might have been allocted for the mask
			_freea(mask2);
		}

		inline void CallOperation(
			const void* lhs, const void* rhs, void* dst, size_t count,
			void(ArithmeticOperations::* Function)(const void* lhs, const void* rhs, void* dst, size_t count) const
		) const {
			// Call the parent function but with a higher count
			(_parent.*Function)(lhs, rhs, dst, count * _type.GetNumberOfChannels());
		}

		void CallOperation(
			const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask,
			void(ArithmeticOperations::* Function)(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const
		) const {
			// Expand the mask to the correct size
			const size_t channels = _type.GetNumberOfChannels();
			uint8_t* mask2 = static_cast<uint8_t*>(_malloca(NewMaskSize(count)));
			(this->*ExpandMask)(mask, mask2, count);

			// Call the parent function but with a higher count
			(_parent.*Function)(lhs, rhs, dst, count * channels, mask2);

			// Free any memory that might have been allocted for the mask
			_freea(mask2);
		}

		inline void CallOperation(
			const void* a, const void* b, const void* c, void* dst, size_t count,
			void(ArithmeticOperations::* Function)(const void* a, const void* b, const void* c, void* dst, size_t count) const
		) const {
			// Call the parent function but with a higher count
			(_parent.*Function)(a, b, c, dst, count * _type.GetNumberOfChannels());;
		}

		void CallOperation(
			const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask,
			void(ArithmeticOperations::* Function)(const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask) const
		) const {
			// Expand the mask to the correct size
			const size_t channels = _type.GetNumberOfChannels();
			uint8_t* mask2 = static_cast<uint8_t*>(_malloca(NewMaskSize(count)));
			(this->*ExpandMask)(mask, mask2, count);

			// Call the parent function but with a higher count
			(_parent.*Function)(a, b, c, dst, count * channels, mask2);

			// Free any memory that might have been allocted for the mask
			_freea(mask2);
		}

	public:
		ArithmeticOperationsMultiChannel(const Type type, ArithmeticOperations& parent) :
			ArithmeticOperations(type),
			_parent(parent)
		{
			switch (_type.GetNumberOfChannels()) {
			case 1u:
				ExpandMask = &ArithmeticOperationsMultiChannel::ExpandMask1;
				break;
			default:
				ExpandMask = &ArithmeticOperationsMultiChannel::ExpandMaskUnoptimised;
				break;
			}
		}

		virtual ~ArithmeticOperationsMultiChannel() {

		}

		// 1 input

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

		void Round(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Round);
		}

		void Floor(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Floor);
		}

		void Floor(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Floor);
		}

		void Ceil(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Ceil);
		}

		void Ceil(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Ceil);
		}

		void Cos(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Cos);
		}

		void Cos(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Cos);
		}

		void Sin(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Sin);
		}

		void Sin(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Sin);
		}

		void Tan(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Tan);
		}

		void Tan(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Tan);
		}

		void Acos(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Acos);
		}

		void Acos(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Acos);
		}

		void Asin(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Asin);
		}

		void Asin(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Asin);
		}

		void Atan(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Atan);
		}

		void Atan(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Atan);
		}

		void Cosh(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Cosh);
		}

		void Cosh(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Cosh);
		}

		void Sinh(const void* src, void* dst, size_t count) const final{
			CallOperation(src, dst, count, &ArithmeticOperations::Sinh);
		}

		void Sinh(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Sinh);
		}

		void Tanh(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Tanh);
		}

		void Tanh(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Tanh);
		}

		void Acosh(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Acosh);
		}

		void Acosh(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Acosh);
		}

		void Asinh(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Asinh);
		}

		void Asinh(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Asinh);
		}

		void Atanh(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Atanh);
		}

		void Atanh(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::Atanh);
		}

		void Abs(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Abs);
		}

		void Abs(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
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
			CallOperation(lhs, rhs, dst, count, &ArithmeticOperations::And);
		}

		void And(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::And);
		}

		void Or(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			CallOperation(lhs, rhs, dst, count, &ArithmeticOperations::Or);
		}

		void Or(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::Or);
		}

		void Xor(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			CallOperation(lhs, rhs, dst, count, &ArithmeticOperations::Xor);
		}

		void Xor(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::Xor);
		}

		void Nand(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			CallOperation(lhs, rhs, dst, count, &ArithmeticOperations::Nand);
		}

		void Nand(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::Nand);
		}

		void Nor(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			CallOperation(lhs, rhs, dst, count, &ArithmeticOperations::Nor);
		}

		void Nor(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::Nor);
		}

		void Xnor(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			CallOperation(lhs, rhs, dst, count, &ArithmeticOperations::Xnor);
		}

		void Xnor(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::Xnor);
		}

		void Power(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			CallOperation(lhs, rhs, dst, count, &ArithmeticOperations::Power);
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