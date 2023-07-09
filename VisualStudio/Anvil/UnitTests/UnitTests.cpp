#include "pch.h"
#include "CppUnitTest.h"
#include "anvil/Core.hpp"
#include <thread>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{

	TEST_CLASS(LeadingZeroCount)
	{
	public:
		size_t TestLZ(uint64_t val) {
			if (val == 0u) return 64;

			size_t result = 0u;
			for(int i = 0; i < 64; ++i) {
				if (val & 1ull) break;
				val >>= 1ull;
				if (val == 0u) throw std::runtime_error("Value somehow made to be zero");
				if (result > 64) throw std::runtime_error("Somehow checked more than 64 bits");
				++result;
			}

			return result;
		}
		
		TEST_METHOD(DoesCPPHandleZero)
		{
			uint64_t val = 0u;

			size_t result = anvil::detail::lzcount8_c((uint8_t) val);
			Assert::AreEqual(result, (size_t) 8);

			result = anvil::detail::lzcount16_c((uint16_t)val);
			Assert::AreEqual(result, (size_t)16);

			result = anvil::detail::lzcount32_c((uint32_t)val);
			Assert::AreEqual(result, (size_t)32);

			result = anvil::detail::lzcount64_c((uint64_t)val);
			Assert::AreEqual(result, (size_t)64);
		}

		void TestRange(const std::function<void(uint64_t)>& fn, uint64_t min, uint64_t max) {
			uint64_t range = max - min;
			if (range < UINT16_MAX) {
				for (uint64_t i = min; i <= max; ++i) fn(i);
			} else {
				for (uint64_t i = 0u; i < UINT16_MAX; ++i) {
					uint64_t val = i + min;
					fn(val);
					val <<= 4;
					if(val < max) fn(val);
					val <<= 4;
					if (val < max) fn(val);
					val <<= 4;
					if (val < max) fn(val);
					val <<= 4;
					if (val < max) fn(val);
					val <<= 4;
					if (val < max) fn(val);
					val <<= 4;
					if (val < max) fn(val);
					val <<= 4;
					if (val < max) fn(val);
					val <<= 4;
					if (val < max) fn(val);
				}
			}
		}

		void TestRange(const std::function<void(uint64_t)>& fn) {
			TestRange(fn, 0u, UINT64_MAX);
		}

		TEST_METHOD(DoesCPPHandleAnyIndividualBit)
		{
			uint64_t val = 1u;
			size_t correct = 0u;
			size_t result;

			for (size_t i = 0u; i < 63; ++i) {
				if (val <= UINT8_MAX) {
					result = anvil::detail::lzcount8_c((uint8_t)val);
					Assert::AreEqual(result, correct);
				}

				if (val <= UINT16_MAX) {
					result = anvil::detail::lzcount16_c((uint16_t)val);
					Assert::AreEqual(result, correct);
				}

				if (val <= UINT32_MAX) {
					result = anvil::detail::lzcount32_c((uint32_t)val);
					Assert::AreEqual(result, correct);
				}

				result = anvil::detail::lzcount64_c((uint64_t)val);
				Assert::AreEqual(result, correct);

				val <<= 1ull;
				++correct;
			}
		}
		TEST_METHOD(DoesHWAccelerationAHaveSameResultAsCpp)
		{
			if (!ANVIL_HW_LZCNTA) Assert::Fail(L"CPU does not support HW LZCNT (A Implementation)");

			TestRange([this](uint64_t i)->void {
				uint64_t c;
				uint64_t hw;

				if (i <= UINT8_MAX) {
					c = anvil::detail::lzcount8_c((uint8_t)i);
					hw = anvil::detail::lzcount8_hwa((uint8_t)i);
					Assert::AreEqual(c, hw);
				}

				if (i <= UINT16_MAX) {
					c = anvil::detail::lzcount16_c((uint16_t)i);
					hw = anvil::detail::lzcount16_hwa((uint16_t)i);
					Assert::AreEqual(c, hw);
				}

				if (i <= UINT32_MAX) {
					c = anvil::detail::lzcount32_c((uint32_t)i);
					hw = anvil::detail::lzcount32_hwa((uint32_t)i);
					Assert::AreEqual(c, hw);
				}

				c = anvil::detail::lzcount64_c((uint64_t)i);
				hw = anvil::detail::lzcount64_hwa((uint64_t)i);
				Assert::AreEqual(c, hw);
			});
		}

		TEST_METHOD(DoesHWAccelerationBHaveSameResultAsCpp)
		{
			if (!ANVIL_HW_LZCNTB) Assert::Fail(L"CPU does not support HW LZCNT (B Implementation)");

			TestRange([this](uint64_t i)->void {
				uint64_t c;
				uint64_t hw;

				if (i <= UINT8_MAX) {
					c = anvil::detail::lzcount8_c((uint8_t)i);
					hw = anvil::detail::lzcount8_hwb((uint8_t)i);
					Assert::AreEqual(c, hw);
				}

				if (i <= UINT16_MAX) {
					c = anvil::detail::lzcount16_c((uint16_t)i);
					hw = anvil::detail::lzcount16_hwb((uint16_t)i);
					Assert::AreEqual(c, hw);
				}

				if (i <= UINT32_MAX) {
					c = anvil::detail::lzcount32_c((uint32_t)i);
					hw = anvil::detail::lzcount32_hwb((uint32_t)i);
					Assert::AreEqual(c, hw);
				}

				c = anvil::detail::lzcount64_c((uint64_t)i);
				hw = anvil::detail::lzcount64_hwb((uint64_t)i);
				Assert::AreEqual(c, hw);
			});
		}

		TEST_METHOD(DoesCppHaveSameResultAsTestImplementation)
		{
			TestRange([this](uint64_t i)->void {

				if (i <= UINT32_MAX) {
					uint32_t c, test;
					c = anvil::detail::lzcount32_c((uint32_t)i);
					test = TestLZ((uint32_t)i);
					Assert::AreEqual(c, test);
				}
			});
		}
	};


	TEST_CLASS(TrailingZeroCount)
	{
	public:

		void TestRange(const std::function<void(uint64_t)>& fn, uint64_t min, uint64_t max) {
			uint64_t range = max - min;
			if (range < UINT16_MAX) {
				for (uint64_t i = min; i <= max; ++i) fn(i);
			} else {
				for (uint64_t i = 0u; i < UINT16_MAX; ++i) {
					uint64_t val = i + min;
					fn(val);
					val <<= 4;
					if (val < max) fn(val);
					val <<= 4;
					if (val < max) fn(val);
					val <<= 4;
					if (val < max) fn(val);
					val <<= 4;
					if (val < max) fn(val);
					val <<= 4;
					if (val < max) fn(val);
					val <<= 4;
					if (val < max) fn(val);
					val <<= 4;
					if (val < max) fn(val);
					val <<= 4;
					if (val < max) fn(val);
				}
			}
		}

		void TestRange(const std::function<void(uint64_t)>& fn) {
			TestRange(fn, 0u, UINT64_MAX - 1ull);
		}


		size_t TestTZ(uint64_t val) {
			enum : uint64_t {
				FLAG = 1ull << 63ull
			};

			if (val == 0u) return 64;

			size_t result = 0u;
			for (int i = 0; i < 64; ++i) {
				if (val & FLAG) break;
				val <<= 1ull;
				if (val == 0u) throw std::runtime_error("Value somehow made to be zero");
				if (result > 64) throw std::runtime_error("Somehow checked more than 64 bits");
				++result;
			}

			return result;
		}
		TEST_METHOD(DoesCppHandleZero)
		{
			uint64_t val = 0u;

			size_t result = anvil::detail::lzcount8_c((uint8_t) val);
			Assert::AreEqual(result, (size_t) 8);

			result = anvil::detail::lzcount16_c((uint16_t)val);
			Assert::AreEqual(result, (size_t)16);

			result = anvil::detail::lzcount32_c((uint32_t)val);
			Assert::AreEqual(result, (size_t)32);

			result = anvil::detail::lzcount64_c((uint64_t)val);
			Assert::AreEqual(result, (size_t)64);
		}

		TEST_METHOD(DoesCppBitHandleAnyIndividualBit_8)
		{
			uint64_t val = 1u;
			size_t correct = 7u;
			size_t result;

			for (size_t i = 0u; i < 8; ++i) {
				result = anvil::detail::tzcount8_c((uint8_t)val);
				Assert::AreEqual(result, correct);

				val <<= 1ull;
				--correct;
			}
		}
		TEST_METHOD(DoesCppBitHandleAnyIndividualBit_16)
		{
			uint64_t val = 1u;
			size_t correct = 15u;
			size_t result;

			for (size_t i = 0u; i < 16; ++i) {
				result = anvil::detail::tzcount16_c((uint16_t)val);
				Assert::AreEqual(result, correct);

				val <<= 1ull;
				--correct;
			}
		}

		TEST_METHOD(DoesCppBitHandleAnyIndividualBit_32)
		{
			uint64_t val = 1u;
			size_t correct = 31u;
			size_t result;

			for (size_t i = 0u; i < 32; ++i) {
				result = anvil::detail::tzcount32_c((uint32_t)val);
				Assert::AreEqual(result, correct);

				val <<= 1ull;
				--correct;
			}
		}

		TEST_METHOD(DoesCppBitHandleAnyIndividualBit_64)
		{
			uint64_t val = 1u;
			size_t correct = 63u;
			size_t result;

			for (size_t i = 0u; i < 64; ++i) {
				result = anvil::detail::tzcount64_c((uint64_t)val);
				Assert::AreEqual(result, correct);

				val <<= 1ull;
				--correct;
			}
		}

		TEST_METHOD(DoesHWAccelerationAHaveSameResultAsCpp)
		{
			if (!ANVIL_HW_TZCNTA) Assert::Fail(L"CPU does not support HW LZCNT (A implementation)");

			TestRange([this](uint64_t i)->void {
				uint64_t c;
				uint64_t hw;

				if (i <= UINT8_MAX) {
					c = anvil::detail::tzcount8_c((uint8_t)i);
					hw = anvil::detail::tzcount8_hwa((uint8_t)i);
					Assert::AreEqual(c, hw);
				}

				if (i <= UINT16_MAX) {
					c = anvil::detail::tzcount16_c((uint16_t)i);
					hw = anvil::detail::tzcount16_hwa((uint16_t)i);
					Assert::AreEqual(c, hw);
				}

				if (i <= UINT32_MAX) {
					c = anvil::detail::tzcount32_c((uint32_t)i);
					hw = anvil::detail::tzcount32_hwa((uint32_t)i);
					Assert::AreEqual(c, hw);
				}

				c = anvil::detail::tzcount64_c((uint64_t)i);
				hw = anvil::detail::tzcount64_hwa((uint64_t)i);
				Assert::AreEqual(c, hw);
			});
		}

		TEST_METHOD(DoesHWAccelerationBHaveSameResultAsCpp)
		{
			if (!ANVIL_HW_TZCNTB) Assert::Fail(L"CPU does not support HW LZCNT (B implementation)");

			TestRange([this](uint64_t i)->void {
				uint64_t c;
				uint64_t hw;

				if (i <= UINT8_MAX) {
					c = anvil::detail::tzcount8_c((uint8_t)i);
					hw = anvil::detail::tzcount8_hwb((uint8_t)i);
					Assert::AreEqual(c, hw);
				}

				if (i <= UINT16_MAX) {
					c = anvil::detail::tzcount16_c((uint16_t)i);
					hw = anvil::detail::tzcount16_hwb((uint16_t)i);
					Assert::AreEqual(c, hw);
				}

				if (i <= UINT32_MAX) {
					c = anvil::detail::tzcount32_c((uint32_t)i);
					hw = anvil::detail::tzcount32_hwb((uint32_t)i);
					Assert::AreEqual(c, hw);
				}

				c = anvil::detail::tzcount64_c((uint64_t)i);
				hw = anvil::detail::tzcount64_hwb((uint64_t)i);
				Assert::AreEqual(c, hw);
			});
		}

		TEST_METHOD(DoesCppHaveSameResultAsTestImplementation)
		{
			TestRange([this](uint64_t i)->void {

				if (i <= UINT32_MAX) {
					uint32_t c, test;
					c = anvil::detail::tzcount32_c((uint32_t)i);
					test = TestTZ((uint32_t)i);
					Assert::AreEqual(c, test);
				}
			});
		}
	};
}
