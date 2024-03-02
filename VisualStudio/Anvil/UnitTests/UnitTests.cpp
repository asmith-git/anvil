#include "CppUnitTest.h"
#include "anvil/Core.hpp"
#include <thread>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace anvil { namespace core {

	void TestRange64Bitwise(const std::function<void(uint64_t)>& fn) {
		// Testing every 64-bit integer takes too long so approximate a range of different values

		// Zero
		fn(0);

		// All indidual bits
		{
			uint64_t bit = 1u;
			for (int i = 0; i < 64; ++i) {
				fn(i);
				bit <<= 1ull;
			}
		}

		// Different combinations of every 16-bit integer
		for (uint64_t i = 0u; i < UINT16_MAX; ++i) {
			uint64_t val = i;
			fn(val);

			fn(val << 8ull);
			fn(val << 16ull);
			fn(val << 24ull);
			fn(val << 32ull);

			val |= val << 16ull;
			fn(val);
			val |= val << 32ull;
			fn(val);
		}
	}

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

		TEST_METHOD(IsBSRImplementationSameAsCpp)
		{
			if (!ANVIL_HW_LZCNTA) Assert::Fail(L"CPU does not support BSR instruction");

			TestRange64Bitwise([this](uint64_t i)->void {
				uint64_t c;
				uint64_t hw;

				if (i <= UINT8_MAX) {
					c = anvil::detail::lzcount8_c((uint8_t)i);
					hw = anvil::detail::lzcount8_hwa((uint8_t)i);
					Assert::AreEqual(c, hw, std::wstring(L"uint8 : " + std::to_wstring(i)).c_str());
				}

				if (i <= UINT16_MAX) {
					c = anvil::detail::lzcount16_c((uint16_t)i);
					hw = anvil::detail::lzcount16_hwa((uint16_t)i);
					Assert::AreEqual(c, hw, std::wstring(L"uint16 : " + std::to_wstring(i)).c_str());
				}

				if (i <= UINT32_MAX) {
					c = anvil::detail::lzcount32_c((uint32_t)i);
					hw = anvil::detail::lzcount32_hwa((uint32_t)i);
					Assert::AreEqual(c, hw, std::wstring(L"uint32 : " + std::to_wstring(i)).c_str());
				}

				c = anvil::detail::lzcount64_c((uint64_t)i);
				hw = anvil::detail::lzcount64_hwa((uint64_t)i);
				Assert::AreEqual(c, hw, std::wstring(L"uint64 : " + std::to_wstring(i)).c_str());
			});
		}

		TEST_METHOD(IsLZCNTImplementationSameAsCpp)
		{
			if (!ANVIL_HW_LZCNTB) Assert::Fail(L"CPU does not support LZCNT instruction");

			TestRange64Bitwise([this](uint64_t i)->void {
				uint64_t c;
				uint64_t hw;

				if (i <= UINT8_MAX) {
					c = anvil::detail::lzcount8_c((uint8_t)i);
					hw = anvil::detail::lzcount8_hwb((uint8_t)i);
					Assert::AreEqual(c, hw, std::wstring(L"uint8 : " + std::to_wstring(i)).c_str());
				}

				if (i <= UINT16_MAX) {
					c = anvil::detail::lzcount16_c((uint16_t)i);
					hw = anvil::detail::lzcount16_hwb((uint16_t)i);
					Assert::AreEqual(c, hw, std::wstring(L"uint16 : " + std::to_wstring(i)).c_str());
				}

				if (i <= UINT32_MAX) {
					c = anvil::detail::lzcount32_c((uint32_t)i);
					hw = anvil::detail::lzcount32_hwb((uint32_t)i);
					Assert::AreEqual(c, hw, std::wstring(L"uint32 : " + std::to_wstring(i)).c_str());
				}

				c = anvil::detail::lzcount64_c((uint64_t)i);
				hw = anvil::detail::lzcount64_hwb((uint64_t)i);
				Assert::AreEqual(c, hw, std::wstring(L"uint64 : " + std::to_wstring(i)).c_str());
			});
		}

		TEST_METHOD(IsCPPImplementationSameAsSlowTest)
		{
			TestRange64Bitwise([this](uint64_t i)->void {

				if (i <= UINT32_MAX) {
					uint32_t c, test;
					c = anvil::detail::lzcount64_c((uint32_t)i);
					test = TestLZ((uint32_t)i);
					Assert::AreEqual(c, test, std::wstring(L"uint32 : " + std::to_wstring(i)).c_str());
				}
			});
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
		TEST_METHOD(IsBSRImplementationSameAsCpp)
		{
			if (!ANVIL_HW_TZCNTA) Assert::Fail(L"CPU does not support BSR instruction");

			TestRange64Bitwise([this](uint64_t i)->void {
				uint64_t c;
				uint64_t hw;

				if (i <= UINT8_MAX) {
					c = anvil::detail::tzcount8_c((uint8_t)i);
					hw = anvil::detail::tzcount8_hwa((uint8_t)i);
					Assert::AreEqual(c, hw, std::wstring(L"uint8 : " + std::to_wstring(i)).c_str());
				}

				if (i <= UINT16_MAX) {
					c = anvil::detail::tzcount16_c((uint16_t)i);
					hw = anvil::detail::tzcount16_hwa((uint16_t)i);
					Assert::AreEqual(c, hw, std::wstring(L"uint16 : " + std::to_wstring(i)).c_str());
				}

				if (i <= UINT32_MAX) {
					c = anvil::detail::tzcount32_c((uint32_t)i);
					hw = anvil::detail::tzcount32_hwa((uint32_t)i);
					Assert::AreEqual(c, hw, std::wstring(L"uint32 : " + std::to_wstring(i)).c_str());
				}

				c = anvil::detail::tzcount64_c((uint64_t)i);
				hw = anvil::detail::tzcount64_hwa((uint64_t)i);
				Assert::AreEqual(c, hw, std::wstring(L"uint64 : " + std::to_wstring(i)).c_str());
			});
		}

		TEST_METHOD(IsTZCNTImplementationSameAsCpp)
		{
			if (!ANVIL_HW_TZCNTB) Assert::Fail(L"CPU does not support TZCNT instruction");

			TestRange64Bitwise([this](uint64_t i)->void {
				uint64_t c;
				uint64_t hw;

				if (i <= UINT8_MAX) {
					c = anvil::detail::tzcount8_c((uint8_t)i);
					hw = anvil::detail::tzcount8_hwb((uint8_t)i);
					Assert::AreEqual(c, hw, std::wstring(L"uint8 : " + std::to_wstring(i)).c_str());
				}

				if (i <= UINT16_MAX) {
					c = anvil::detail::tzcount16_c((uint16_t)i);
					hw = anvil::detail::tzcount16_hwb((uint16_t)i);
					Assert::AreEqual(c, hw, std::wstring(L"uint16 : " + std::to_wstring(i)).c_str());
				}

				if (i <= UINT32_MAX) {
					c = anvil::detail::tzcount32_c((uint32_t)i);
					hw = anvil::detail::tzcount32_hwb((uint32_t)i);
					Assert::AreEqual(c, hw, std::wstring(L"uint32 : " + std::to_wstring(i)).c_str());
				}

				c = anvil::detail::tzcount64_c((uint64_t)i);
				hw = anvil::detail::tzcount64_hwb((uint64_t)i);
				Assert::AreEqual(c, hw, std::wstring(L"uint64 : " + std::to_wstring(i)).c_str());
			});
		}

		TEST_METHOD(IsCPPImplementationSameAsSlowTest)
		{
			TestRange64Bitwise([this](uint64_t i)->void {

				if (i <= UINT32_MAX) {
					uint32_t c, test;
					c = anvil::detail::tzcount64_c((uint32_t)i);
					test = TestTZ((uint32_t)i);
					Assert::AreEqual(c, test, std::wstring(L"uint32 : " + std::to_wstring(i)).c_str());
				}
			});
		}
	};

	TEST_CLASS(Reflect)
	{
	public:

		TEST_METHOD(IsCppSameAsSlow)
		{
			for (uint32_t i = 0u; i <= UINT8_MAX; ++i) {
				uint8_t a = anvil::detail::reflect_c((uint8_t)i);
				uint8_t b = anvil::reflect((uint8_t)i);
				Assert::AreEqual(a, b, std::wstring(L"uint8 : " + std::to_wstring(i)).c_str());
			}
		}

		TEST_METHOD(SameWhenReversed)
		{
			TestRange64Bitwise([this](uint64_t i)->void {
				if (i <= UINT8_MAX) {
					uint8_t a = anvil::reflect((uint8_t)i);
					uint8_t b = anvil::reflect(a);
					Assert::AreEqual((uint8_t)i, b, std::wstring(L"uint8 : " + std::to_wstring(i)).c_str());
				}

				if (i <= UINT16_MAX) {
					uint16_t a = anvil::reflect((uint16_t)i);
					uint16_t b = anvil::reflect(a);
					Assert::AreEqual((uint16_t)i, b, std::wstring(L"uint16 : " + std::to_wstring(i)).c_str());
				}

				if (i <= UINT32_MAX) {
					uint32_t a = anvil::reflect((uint32_t)i);
					uint32_t b = anvil::reflect(a);
					Assert::AreEqual((uint32_t)i, b, std::wstring(L"uint32 : " + std::to_wstring(i)).c_str());
				}
					
				uint64_t a = anvil::reflect((uint64_t)i);
				uint64_t b = anvil::reflect(a);
				Assert::AreEqual((uint64_t)i, b, std::wstring(L"uint64 : " + std::to_wstring(i)).c_str());
			});
		}

		TEST_METHOD(ConsistantPopcount)
		{
			TestRange64Bitwise([this](uint64_t i)->void {
				if (i <= UINT8_MAX) {
					uint8_t a = anvil::reflect((uint8_t)i);
					Assert::AreEqual(anvil::popcount(i), anvil::popcount(a), std::wstring(L"uint8 : " + std::to_wstring(i)).c_str());
				}

				if (i <= UINT16_MAX) {
					uint16_t a = anvil::reflect((uint16_t)i);
					Assert::AreEqual(anvil::popcount(i), anvil::popcount(a), std::wstring(L"uint16 : " + std::to_wstring(i)).c_str());
				}

				if (i <= UINT32_MAX) {
					uint32_t a = anvil::reflect((uint32_t)i);
					Assert::AreEqual(anvil::popcount(i), anvil::popcount(a), std::wstring(L"uint32 : " + std::to_wstring(i)).c_str());
				}
					
				uint64_t a = anvil::reflect((uint64_t)i);
				Assert::AreEqual(anvil::popcount(i), anvil::popcount(a), std::wstring(L"uint64 : " + std::to_wstring(i)).c_str());
			});
		}
	};

	TEST_CLASS(Popcount)
	{
	public:

		TEST_METHOD(IsCppImplementationSameAsTest)
		{
			if (!ANVIL_HW_POPCNT) Assert::Fail(L"CPU does not support BSR instruction");

			TestRange64Bitwise([this](uint64_t i)->void {
				size_t c;
				size_t hw;

				if (i <= UINT8_MAX) {
					c = anvil::detail::popcount_test((uint8_t)i);
					hw = anvil::detail::popcount_c((uint8_t)i);
					Assert::AreEqual(c, hw, std::wstring(L"uint8 : " + std::to_wstring(i)).c_str());
				}

				if (i <= UINT16_MAX) {
					c = anvil::detail::popcount_test((uint16_t)i);
					hw = anvil::detail::popcount_c((uint16_t)i);
					Assert::AreEqual(c, hw, std::wstring(L"uint16 : " + std::to_wstring(i)).c_str());
				}

				if (i <= UINT32_MAX) {
					c = anvil::detail::popcount_test((uint32_t)i);
					hw = anvil::detail::popcount_c((uint32_t)i);
					Assert::AreEqual(c, hw, std::wstring(L"uint32 : " + std::to_wstring(i)).c_str());
				}

				c = anvil::detail::popcount_test((uint64_t)i);
				hw = anvil::detail::popcount_c((uint64_t)i);
				Assert::AreEqual(c, hw, std::wstring(L"uint64 : " + std::to_wstring(i)).c_str());
				});
		}
		TEST_METHOD(IsHWImplementationSameAsCpp)
		{
			if (!ANVIL_HW_POPCNT) Assert::Fail(L"CPU does not support BSR instruction");

			TestRange64Bitwise([this](uint64_t i)->void {
				size_t c;
				size_t hw;

				if (i <= UINT8_MAX) {
					c = anvil::detail::popcount_c((uint8_t)i);
					hw = anvil::detail::popcount_hw((uint8_t)i);
					Assert::AreEqual(c, hw, std::wstring(L"uint8 : " + std::to_wstring(i)).c_str());
				}

				if (i <= UINT16_MAX) {
					c = anvil::detail::popcount_c((uint16_t)i);
					hw = anvil::detail::popcount_hw((uint16_t)i);
					Assert::AreEqual(c, hw, std::wstring(L"uint16 : " + std::to_wstring(i)).c_str());
				}

				if (i <= UINT32_MAX) {
					c = anvil::detail::popcount_c((uint32_t)i);
					hw = anvil::detail::popcount_hw((uint32_t)i);
					Assert::AreEqual(c, hw, std::wstring(L"uint32 : " + std::to_wstring(i)).c_str());
				}

				c = anvil::detail::popcount_c((uint64_t)i);
				hw = anvil::detail::popcount_hw((uint64_t)i);
				Assert::AreEqual(c, hw, std::wstring(L"uint64 : " + std::to_wstring(i)).c_str());
			});
		}

		TEST_METHOD(IsUint16SameAsUint8)
		{
			if (!ANVIL_HW_POPCNT) Assert::Fail(L"CPU does not support BSR instruction");

			for (uint64_t i = 0; i <= UINT8_MAX; ++i) {
				size_t a = anvil::detail::popcount_c((uint8_t)i);
				size_t b = anvil::detail::popcount_c((uint16_t)i);
				Assert::AreEqual(a, b, std::wstring(L"uint16 : " + std::to_wstring(i)).c_str());
			}
		}

		TEST_METHOD(IsUint32SameAsUint8)
		{
			if (!ANVIL_HW_POPCNT) Assert::Fail(L"CPU does not support BSR instruction");

			for (uint64_t i = 0; i <= UINT8_MAX; ++i) {
				size_t a = anvil::detail::popcount_c((uint8_t)i);
				size_t b = anvil::detail::popcount_c((uint32_t)i);
				Assert::AreEqual(a, b, std::wstring(L"uint32 : " + std::to_wstring(i)).c_str());
			}
		}

		TEST_METHOD(IsUint64SameAsUint8)
		{
			if (!ANVIL_HW_POPCNT) Assert::Fail(L"CPU does not support BSR instruction");

			for (uint64_t i = 0; i <= UINT8_MAX; ++i) {
				size_t a = anvil::detail::popcount_c((uint8_t)i);
				size_t b = anvil::detail::popcount_c((uint64_t)i);
				Assert::AreEqual(a, b, std::wstring(L"uint64 : " + std::to_wstring(i)).c_str());
			}
		}

		TEST_METHOD(General)
		{
			if (!ANVIL_HW_POPCNT) Assert::Fail(L"CPU does not support BSR instruction");


			Assert::AreEqual(anvil::detail::popcount_c((uint8_t)0u), (size_t)0u, 
				L"C++ implementation of 8-bit popcount does not handle 0 correctly"
			);

			Assert::AreEqual(anvil::detail::popcount_c((uint8_t)1u), (size_t)1u,
				L"C++ implementation of 8-bit popcount does not handle 1 correctly"
			);

			Assert::AreEqual(anvil::detail::popcount_c((uint8_t)2u), (size_t)1u,
				L"C++ implementation of 8-bit popcount does not handle 2 correctly"
			);

			Assert::AreEqual(anvil::detail::popcount_c((uint8_t)3u), (size_t)2u,
				L"C++ implementation of 8-bit popcount does not handle 3 correctly"
			);

			Assert::AreEqual(anvil::detail::popcount_c((uint8_t)255u), (size_t)8u,
				L"C++ implementation of 8-bit popcount does not handle 255 correctly"
			);
		}
	};

	TEST_CLASS(Base64)
	{
	public:
		TEST_METHOD(SameWhenReversed)
		{
			enum { MAX_DATA_SIZE = 4096 };
			uint8_t data_in[MAX_DATA_SIZE];
			uint8_t data_out[MAX_DATA_SIZE];
			for (int i = 0; i < 100000; ++i) {
				size_t data_size_in = rand() % MAX_DATA_SIZE;
				for (size_t j = 0; j < data_size_in; ++j) data_in[i] = static_cast<uint8_t>(rand() % UINT8_MAX);

				std::string tmp = anvil::Base64::Encode(data_in, data_size_in);
				size_t data_size_out = 0u;
				anvil::Base64::Decode(tmp.c_str(), tmp.size(), data_out, data_size_out);
				Assert::AreEqual(data_size_in, data_size_out, L"Decode size was different than what was encoded");
				Assert::IsTrue(memcmp(data_in, data_out, data_size_in) == 0, L"Decoded data was not the same as what was encoded");
			}
		}

		TEST_METHOD(Strings)
		{
			std::string src, encoded;

			src = "Many hands make light work.";
			encoded = anvil::Base64::Encode((const uint8_t*)src.c_str(), src.size());
			Assert::IsTrue(encoded == "TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu");
		}
	};

	TEST_CLASS(Hexadecimal)
	{
	public:
		TEST_METHOD(SameWhenReversed)
		{
			enum { MAX_DATA_SIZE = 4096 };
			uint8_t data_in[MAX_DATA_SIZE];
			uint8_t data_out[MAX_DATA_SIZE];
			for (int i = 0; i < 100000; ++i) {
				size_t data_size_in = rand() % MAX_DATA_SIZE;
				for (size_t j = 0; j < data_size_in; ++j) data_in[i] = static_cast<uint8_t>(rand() % UINT8_MAX);

				std::string tmp = anvil::Hexadecimal::Encode(data_in, data_size_in);
				size_t data_size_out = 0u;
				anvil::Hexadecimal::Decode(tmp.c_str(), tmp.size(), data_out, data_size_out);
				Assert::AreEqual(data_size_in, data_size_out, L"Decode size was different than what was encoded");
				Assert::IsTrue(memcmp(data_in, data_out, data_size_in) == 0, L"Decoded data was not the same as what was encoded");
			}
		}

		TEST_METHOD(AllUniqueBytes)
		{
			std::string encoded;
			uint8_t src_bin;

			const char* hex = "0123456789ABCDEF";
			src_bin = 0;
			for (int i = 0; i <= 15; ++i) {
				for (int j = 0; j <= 15; ++j) {
					std::string expected;
					expected += hex[i];
					expected += hex[j];
					encoded = anvil::Hexadecimal::Encode(&src_bin, 1);
					Assert::IsTrue(encoded == expected, std::to_wstring(src_bin).c_str());
					++src_bin;
				}
			}
		}
		TEST_METHOD(Strings)
		{
			std::string src, encoded;

			src = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
			encoded = anvil::Hexadecimal::Encode((const uint8_t*)src.c_str(), src.size());
			Assert::IsTrue(encoded == "303132333435363738396162636465666768696A6B6C6D6E6F707172737475767778797A4142434445464748494A4B4C4D4E4F505152535455565758595A");
		}
	};

}}
