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
#include <cmath>

namespace anvil { namespace compute { namespace details {

	class ArithmeticOperationsMultiChannel final : public ArithmeticOperations {
	private:
		ArithmeticOperations& _parent;
		void (ArithmeticOperationsMultiChannel::* FixMask)(const uint8_t* src, uint8_t* dst, size_t count) const;

		size_t NewMaskSize(size_t count) const {
			return count * (_type.GetNumberOfChannels() + 1);
		}

		void FixMask1(const uint8_t* src, uint8_t* dst, size_t count) const {
			memcpy(dst, src, (count / 8) + ((count % 8) == 0 ? 0 : 1));
		}

		void FixMask2(const uint8_t* src, uint8_t* dst, size_t count) const {
			//! \todo Optimise
			while (count >= 8u) {
				uint8_t m = *src;
				uint16_t m2 = 0u;

				m2 |= m & 1u ? 3u : 0u;
				m2 |= m & 2u ? (3u << 2u) : 0u;
				m2 |= m & 4u ? (3u << 4u) : 0u;
				m2 |= m & 8u ? (3u << 6u) : 0u;
				m2 |= m & 16u ? (3u << 8u) : 0u;
				m2 |= m & 32u ? (3u << 10u) : 0u;
				m2 |= m & 64u ? (3u << 12u) : 0u;
				m2 |= m & 128u ? (3u << 14u) : 0u;

				*reinterpret_cast<uint16_t*>(dst) = m2;

				src += 1u;
				dst += 2u;
				count -= 8u;
			}
			
			if (count > 0u) {
				uint8_t m = *src;
				uint16_t m2 = 0u;

				m2 |= m & 1u ? 3u : 0u;
				m2 |= m & 2u ? (3u << 2u) : 0u;
				m2 |= m & 4u ? (3u << 4u) : 0u;
				m2 |= m & 8u ? (3u << 6u) : 0u;
				m2 |= m & 16u ? (3u << 8u) : 0u;
				m2 |= m & 32u ? (3u << 10u) : 0u;
				m2 |= m & 64u ? (3u << 12u) : 0u;
				m2 |= m & 128u ? (3u << 14u) : 0u;

				*reinterpret_cast<uint16_t*>(dst) = m2;
			}
		}

		void FixMask4(const uint8_t* src, uint8_t* dst, size_t count) const {
			FixMask2(src, dst, count);
			FixMask2(src, dst, count * 2);
		}

		void FixMask8(const uint8_t* src, uint8_t* dst, size_t count) const {
			FixMask4(src, dst, count);
			FixMask4(src, dst, count * 2);
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
			case 2u:
				FixMask = &ArithmeticOperationsMultiChannel::FixMask2;
				break;
			case 4u:
				FixMask = &ArithmeticOperationsMultiChannel::FixMask4;
				break;
			case 8u:
				FixMask = &ArithmeticOperationsMultiChannel::FixMask8;
				break;
			default:
				FixMask = nullptr;
				//! \todo Implement masks for non power of 2 masks
				//throw std::runtime_error("anvil::compute::ArithmeticOperationsMultiChannel : Unsupported channel count");
				break;
			}
		}

		virtual ~ArithmeticOperationsMultiChannel() {

		}

		// 1 input

		void Sqrt(const void* src, void* dst, size_t count) const final {
			_parent.Sqrt(src, dst, count * _type.GetNumberOfChannels());
		}

		void SqrtMask(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			const size_t c = _type.GetNumberOfChannels();
			uint8_t* mask2 = static_cast<uint8_t*>(_malloca(NewMaskSize(count)));
			(this->*FixMask)(mask, mask2, count);
			_parent.SqrtMask(src, dst, count * c, mask2);
			_freea(mask2);
		}

		void Cbrt(const void* src, void* dst, size_t count) const final {
			_parent.Cbrt(src, dst, count * _type.GetNumberOfChannels());
		}

		void CbrtMask(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			const size_t c = _type.GetNumberOfChannels();
			uint8_t* mask2 = static_cast<uint8_t*>(_malloca(NewMaskSize(count)));
			(this->*FixMask)(mask, mask2, count);
			_parent.CbrtMask(src, dst, count * c, mask2);
			_freea(mask2);
		}

		void Not(const void* src, void* dst, size_t count) const final {
			_parent.Not(src, dst, count * _type.GetNumberOfChannels());
		}

		void NotMask(const void* src, void* dst, size_t count, const uint8_t* mask) const final {
			const size_t c = _type.GetNumberOfChannels();
			uint8_t* mask2 = static_cast<uint8_t*>(_malloca(NewMaskSize(count)));
			(this->*FixMask)(mask, mask2, count);
			_parent.NotMask(src, dst, count * c, mask2);
			_freea(mask2);
		}

		// 2 inputs

		void Mask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			_parent.Mask(lhs, rhs, dst, count * _type.GetNumberOfChannels(), mask);
		}

		void Add(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			_parent.Add(lhs, rhs, dst, count * _type.GetNumberOfChannels());
		}

		void AddMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			const size_t c = _type.GetNumberOfChannels();
			uint8_t* mask2 = static_cast<uint8_t*>(_malloca(NewMaskSize(count)));
			(this->*FixMask)(mask, mask2, count);
			_parent.AddMask(lhs, rhs, dst, count * c, mask2);
			_freea(mask2);
		}

		void Subtract(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			_parent.Subtract(lhs, rhs, dst, count * _type.GetNumberOfChannels());
		}

		void SubtractMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			const size_t c = _type.GetNumberOfChannels();
			uint8_t* mask2 = static_cast<uint8_t*>(_malloca(NewMaskSize(count)));
			(this->*FixMask)(mask, mask2, count);
			_parent.SubtractMask(lhs, rhs, dst, count * c, mask2);
			_freea(mask2);
		}

		void Multiply(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			_parent.Multiply(lhs, rhs, dst, count * _type.GetNumberOfChannels());
		}

		void MultiplyMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			const size_t c = _type.GetNumberOfChannels();
			uint8_t* mask2 = static_cast<uint8_t*>(_malloca(NewMaskSize(count)));
			(this->*FixMask)(mask, mask2, count);
			_parent.MultiplyMask(lhs, rhs, dst, count * c, mask2);
			_freea(mask2);
		}

		void Divide(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			_parent.Divide(lhs, rhs, dst, count * _type.GetNumberOfChannels());
		}

		void DivideMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			const size_t c = _type.GetNumberOfChannels();
			uint8_t* mask2 = static_cast<uint8_t*>(_malloca(NewMaskSize(count)));
			(this->*FixMask)(mask, mask2, count);
			_parent.DivideMask(lhs, rhs, dst, count * c, mask2);
			_freea(mask2);
		}

		void And(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			_parent.And(lhs, rhs, dst, count * _type.GetNumberOfChannels());
		}

		void AndMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			const size_t c = _type.GetNumberOfChannels();
			uint8_t* mask2 = static_cast<uint8_t*>(_malloca(NewMaskSize(count)));
			(this->*FixMask)(mask, mask2, count);
			_parent.AndMask(lhs, rhs, dst, count * c, mask2);
			_freea(mask2);
		}

		void Or(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			_parent.Or(lhs, rhs, dst, count * _type.GetNumberOfChannels());
		}

		void OrMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			const size_t c = _type.GetNumberOfChannels();
			uint8_t* mask2 = static_cast<uint8_t*>(_malloca(NewMaskSize(count)));
			(this->*FixMask)(mask, mask2, count);
			_parent.OrMask(lhs, rhs, dst, count * c, mask2);
			_freea(mask2);
		}

		void Xor(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			_parent.Xor(lhs, rhs, dst, count * _type.GetNumberOfChannels());
		}

		void XorMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			const size_t c = _type.GetNumberOfChannels();
			uint8_t* mask2 = static_cast<uint8_t*>(_malloca(NewMaskSize(count)));
			(this->*FixMask)(mask, mask2, count);
			_parent.XorMask(lhs, rhs, dst, count * c, mask2);
			_freea(mask2);
		}

		void Nand(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			_parent.Nand(lhs, rhs, dst, count * _type.GetNumberOfChannels());
		}

		void NandMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			const size_t c = _type.GetNumberOfChannels();
			uint8_t* mask2 = static_cast<uint8_t*>(_malloca(NewMaskSize(count)));
			(this->*FixMask)(mask, mask2, count);
			_parent.NandMask(lhs, rhs, dst, count * c, mask2);
			_freea(mask2);
		}

		void Nor(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			_parent.Nor(lhs, rhs, dst, count * _type.GetNumberOfChannels());
		}

		void NorMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			const size_t c = _type.GetNumberOfChannels();
			uint8_t* mask2 = static_cast<uint8_t*>(_malloca(NewMaskSize(count)));
			(this->*FixMask)(mask, mask2, count);
			_parent.NorMask(lhs, rhs, dst, count * c, mask2);
			_freea(mask2);
		}

		void Xnor(const void* lhs, const void* rhs, void* dst, size_t count) const final {
			_parent.Xnor(lhs, rhs, dst, count * _type.GetNumberOfChannels());
		}

		void XnorMask(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const final {
			const size_t c = _type.GetNumberOfChannels();
			uint8_t* mask2 = static_cast<uint8_t*>(_malloca(NewMaskSize(count)));
			(this->*FixMask)(mask, mask2, count);
			_parent.XnorMask(lhs, rhs, dst, count * c, mask2);
			_freea(mask2);
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