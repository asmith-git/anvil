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
		TEST_METHOD(DoesHWAccelerationHaveSameResultAsCpp)
		{
			if (!ANVIL_HW_LZCNT) Assert::Fail(L"CPU does not support HW LZCNT");

			size_t c, hw;
			for (uint64_t i = 0; i < UINT64_MAX; ++i) {
				if (i <= UINT8_MAX) {
					c = anvil::detail::lzcount8_c((uint8_t)i);
					hw = anvil::detail::lzcount8_hw((uint8_t)i);
					Assert::AreEqual(c, hw);
				}

				if (i <= UINT16_MAX) {
					c = anvil::detail::lzcount16_c((uint16_t)i);
					hw = anvil::detail::lzcount16_hw((uint16_t)i);
					Assert::AreEqual(c, hw);
				}

				if (i <= UINT32_MAX) {
					c = anvil::detail::lzcount32_c((uint32_t)i);
					hw = anvil::detail::lzcount32_hw((uint32_t)i);
					Assert::AreEqual(c, hw);
				}

				c = anvil::detail::lzcount64_c((uint64_t)i);
				hw = anvil::detail::lzcount64_hw((uint64_t)i);
				Assert::AreEqual(c, hw);
			}
		}

		TEST_METHOD(DoesCppHaveSameResultAsTestImplementation)
		{
			const auto TestFn = [this](uint64_t start, uint64_t end, uint64_t shift)->void {
				try {
					size_t c, test;
					for (uint64_t i = start; i < end; ++i) {
						uint64_t val = static_cast<uint64_t>(i) << shift;
						c = anvil::detail::lzcount64_c(val);
						test = TestLZ(val);
						Assert::AreEqual(c, test);
					}
				} catch (...) {
					Assert::AreEqual(0, 1);
				}
			};

			auto thread_count = std::thread::hardware_concurrency();
			std::vector<std::thread> threads;

			uint64_t offset = 0u;
			uint64_t block_size = UINT16_MAX / (uint64_t)thread_count;
			for (auto i = 0; i < thread_count; ++i) {
				threads.push_back(std::thread([offset, block_size,&TestFn]()->void {
					TestFn(offset, offset + block_size, 0);
					TestFn(offset, offset + block_size, 8);
					TestFn(offset, offset + block_size, 16);
					TestFn(offset, offset + block_size, 24);
					TestFn(offset, offset + block_size, 32);
					TestFn(offset, offset + block_size, 48);
					TestFn(offset, offset + block_size, 56);
				}));
				offset += block_size;
			}

			for (std::thread& t : threads) t.join();
		}
	};


	TEST_CLASS(TrailingZeroCount)
	{
	public:


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

		TEST_METHOD(DoesHWAccelerationHaveSameResultAsCpp)
		{
			if (!ANVIL_HW_TZCNT) Assert::Fail(L"CPU does not support HW LZCNT");

			size_t c, hw;
			for (uint64_t i = 0; i < UINT64_MAX; ++i) {
				if (i <= UINT8_MAX) {
					c = anvil::detail::tzcount8_c((uint8_t)i);
					hw = anvil::detail::tzcount8_hw((uint8_t)i);
					Assert::AreEqual(c, hw);
				}

				if (i <= UINT16_MAX) {
					c = anvil::detail::tzcount16_c((uint16_t)i);
					hw = anvil::detail::tzcount16_hw((uint16_t)i);
					Assert::AreEqual(c, hw);
				}

				if (i <= UINT32_MAX) {
					c = anvil::detail::tzcount32_c((uint32_t)i);
					hw = anvil::detail::tzcount32_hw((uint32_t)i);
					Assert::AreEqual(c, hw);
				}

				c = anvil::detail::tzcount64_c((uint64_t)i);
				hw = anvil::detail::tzcount64_hw((uint64_t)i);
				Assert::AreEqual(c, hw);
			}
		}

		TEST_METHOD(DoesCppHaveSameResultAsTestImplementation)
		{
			const auto TestFn = [this](uint64_t start, uint64_t end, uint64_t shift)->void {
				try {
					size_t c, test;
					for (uint64_t i = start; i < end; ++i) {
						uint64_t val = static_cast<uint64_t>(i) << shift;
						c = anvil::detail::lzcount64_c(val);
						test = TestTZ(val);
						Assert::AreEqual(c, test);
					}
				} catch (...) {
					Assert::AreEqual(0, 1);
				}
			};

			auto thread_count = std::thread::hardware_concurrency();
			std::vector<std::thread> threads;

			uint64_t offset = 0u;
			uint64_t block_size = UINT16_MAX / (uint64_t)thread_count;
			for (auto i = 0; i < thread_count; ++i) {
				threads.push_back(std::thread([offset, block_size,&TestFn]()->void {
					TestFn(offset, offset + block_size, 0);
					TestFn(offset, offset + block_size, 8);
					TestFn(offset, offset + block_size, 16);
					TestFn(offset, offset + block_size, 24);
					TestFn(offset, offset + block_size, 32);
					TestFn(offset, offset + block_size, 48);
					TestFn(offset, offset + block_size, 56);
				}));
				offset += block_size;
			}

			for (std::thread& t : threads) t.join();
		}
	};
}
