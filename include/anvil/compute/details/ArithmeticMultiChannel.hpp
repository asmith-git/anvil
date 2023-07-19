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

		void SqrtMask(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::SqrtMask);
		}

		void Cbrt(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Cbrt);
		}

		void CbrtMask(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::CbrtMask);
		}

		void Not(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Not);
		}

		void NotMask(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::NotMask);
		}

		void Round(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Round);
		}

		void RoundMask(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::RoundMask);
		}

		void Floor(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Floor);
		}

		void FloorMask(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::FloorMask);
		}

		void Ceil(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Ceil);
		}

		void CeilMask(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::CeilMask);
		}

		void Cos(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Cos);
		}

		void CosMask(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::CosMask);
		}

		void Sin(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Sin);
		}

		void SinMask(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::SinMask);
		}

		void Tan(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Tan);
		}

		void TanMask(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::TanMask);
		}

		void Acos(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Acos);
		}

		void AcosMask(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::AcosMask);
		}

		void Asin(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Asin);
		}

		void AsinMask(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::AsinMask);
		}

		void Atan(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Atan);
		}

		void AtanMask(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::AtanMask);
		}

		void Cosh(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Cosh);
		}

		void CoshMask(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::CoshMask);
		}

		void Sinh(const void* src, void* dst, size_t count) const final{
			CallOperation(src, dst, count, &ArithmeticOperations::Sinh);
		}

		void SinhMask(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::SinhMask);
		}

		void Tanh(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Tanh);
		}

		void TanhMask(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::TanhMask);
		}

		void Acosh(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Acosh);
		}

		void AcoshMask(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::AcoshMask);
		}

		void Asinh(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Asinh);
		}

		void AsinhMask(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::AsinhMask);
		}

		void Atanh(const void* src, void* dst, size_t count) const final {
			CallOperation(src, dst, count, &ArithmeticOperations::Atanh);
		}

		void AtanhMask(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(src, dst, count, mask, &ArithmeticOperations::AtanhMask);
		}


		// 2 inputs

		void Mask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::Mask);
		}

		void Add(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			CallOperation(lhs, rhs, dst, count, &ArithmeticOperations::Add);
		}

		void AddMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::AddMask);
		}

		void Subtract(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			CallOperation(lhs, rhs, dst, count, &ArithmeticOperations::Subtract);
		}

		void SubtractMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::SubtractMask);
		}

		void Multiply(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			CallOperation(lhs, rhs, dst, count, &ArithmeticOperations::Multiply);
		}

		void MultiplyMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::MultiplyMask);
		}

		void Divide(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			CallOperation(lhs, rhs, dst, count, &ArithmeticOperations::Divide);
		}

		void DivideMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::DivideMask);
		}

		void And(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			CallOperation(lhs, rhs, dst, count, &ArithmeticOperations::And);
		}

		void AndMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::AndMask);
		}

		void Or(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			CallOperation(lhs, rhs, dst, count, &ArithmeticOperations::Or);
		}

		void OrMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::OrMask);
		}

		void Xor(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			CallOperation(lhs, rhs, dst, count, &ArithmeticOperations::Xor);
		}

		void XorMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::XorMask);
		}

		void Nand(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			CallOperation(lhs, rhs, dst, count, &ArithmeticOperations::Nand);
		}

		void NandMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::NandMask);
		}

		void Nor(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			CallOperation(lhs, rhs, dst, count, &ArithmeticOperations::Nor);
		}

		void NorMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::NorMask);
		}

		void Xnor(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			CallOperation(lhs, rhs, dst, count, &ArithmeticOperations::Xnor);
		}

		void XnorMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(lhs, rhs, dst, count, mask, &ArithmeticOperations::XnorMask);
		}

		// 3 inputs

		void MultiplyAdd(const void* a, const void* b, const void* c, void* dst, size_t count) const final {
			CallOperation(a, b, c, dst, count, &ArithmeticOperations::MultiplyAdd);
		}

		void MultiplyAddMask(const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(a, b, c, dst, count, mask, &ArithmeticOperations::MultiplyAddMask);
		}

		void MultiplySubtract(const void* a, const void* b, const void* c, void* dst, size_t count) const final {
			CallOperation(a, b, c, dst, count, &ArithmeticOperations::MultiplySubtract);
		}

		void MultiplySubtractMask(const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask) const final {
			CallOperation(a, b, c, dst, count, mask, &ArithmeticOperations::MultiplySubtractMask);
		}

	};

}}}

#endif