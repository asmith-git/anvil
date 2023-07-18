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
		void (ArithmeticOperationsMultiChannel::* FixMask)(const uint8_t* src, uint8_t* dst, size_t count) const;

		inline size_t NewMaskSize(size_t count) const {
			return count * (_type.GetNumberOfChannels() + 1);
		}

		void FixMaskUnoptimised(const uint8_t* src, uint8_t* dst, size_t count) const {
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

		void FixMask1(const uint8_t* src, uint8_t* dst, size_t count) const {
			memcpy(dst, src, (count / 8) + ((count % 8) == 0 ? 0 : 1));
		}

		inline void CallOperation(
			const void* src, void* dst, size_t count,
			void(ArithmeticOperations::* Function)(const void* src, void* dst, size_t count) const
		) const {
			(_parent.*Function)(src, dst, count * _type.GetNumberOfChannels());;
		}

		void CallOperation(
			const void* src, void* dst, size_t count, const uint8_t* mask,
			void(ArithmeticOperations::* Function)(const void* src, void* dst, size_t count, const uint8_t* mask) const
		) const {
			const size_t channels = _type.GetNumberOfChannels();
			uint8_t* mask2 = static_cast<uint8_t*>(_malloca(NewMaskSize(count)));
			(this->*FixMask)(mask, mask2, count);

			(_parent.*Function)(src, dst, count * channels, mask2);

			_freea(mask2);
		}

		inline void CallOperation(
			const void* lhs, const void* rhs, void* dst, size_t count,
			void(ArithmeticOperations::* Function)(const void* lhs, const void* rhs, void* dst, size_t count) const
		) const {
			(_parent.*Function)(lhs, rhs, dst, count * _type.GetNumberOfChannels());
		}

		void CallOperation(
			const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask,
			void(ArithmeticOperations::* Function)(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const
		) const {
			const size_t channels = _type.GetNumberOfChannels();
			uint8_t* mask2 = static_cast<uint8_t*>(_malloca(NewMaskSize(count)));
			(this->*FixMask)(mask, mask2, count);

			(_parent.*Function)(lhs, rhs, dst, count * channels, mask2);

			_freea(mask2);
		}

		inline void CallOperation(
			const void* a, const void* b, const void* c, void* dst, size_t count,
			void(ArithmeticOperations::* Function)(const void* a, const void* b, const void* c, void* dst, size_t count) const
		) const {
			(_parent.*Function)(a, b, c, dst, count * _type.GetNumberOfChannels());;
		}

		void CallOperation(
			const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask,
			void(ArithmeticOperations::* Function)(const void* a, const void* b, const void* c, void* dst, size_t count, const uint8_t* mask) const
		) const {
			const size_t channels = _type.GetNumberOfChannels();
			uint8_t* mask2 = static_cast<uint8_t*>(_malloca(NewMaskSize(count)));
			(this->*FixMask)(mask, mask2, count);

			(_parent.*Function)(a, b, c, dst, count * channels, mask2);

			_freea(mask2);
		}

	public:
		ArithmeticOperationsMultiChannel(const Type type, ArithmeticOperations& parent) :
			ArithmeticOperations(type),
			_parent(parent)
		{
			switch (_type.GetNumberOfChannels()) {
			case 1u:
				FixMask = &ArithmeticOperationsMultiChannel::FixMask1;
				break;
			default:
				FixMask = &ArithmeticOperationsMultiChannel::FixMaskUnoptimised;
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
			_parent.MultiplyAdd(a, b, c, dst, count * _type.GetNumberOfChannels());
		}

		void MultiplyAddMask(const void* a, const void* b, const void* c2, void* dst, size_t count, const uint8_t* mask) const final {
			const size_t c = _type.GetNumberOfChannels();
			uint8_t* mask2 = static_cast<uint8_t*>(_malloca(NewMaskSize(count)));
			(this->*FixMask)(mask, mask2, count);
			_parent.MultiplyAddMask(a, b, c2, dst, count * c, mask2);
			_freea(mask2);
		}

		void MultiplySubtract(const void* a, const void* b, const void* c, void* dst, size_t count) const final {
			_parent.MultiplySubtract(a, b, c, dst, count * _type.GetNumberOfChannels());
		}

		void MultiplySubtractMask(const void* a, const void* b, const void* c2, void* dst, size_t count, const uint8_t* mask) const final {
			const size_t c = _type.GetNumberOfChannels();
			uint8_t* mask2 = static_cast<uint8_t*>(_malloca(NewMaskSize(count)));
			(this->*FixMask)(mask, mask2, count);
			_parent.MultiplySubtractMask(a, b, c2, dst, count * c, mask2);
			_freea(mask2);
		}

	};

}}}

#endif