#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING 
#include "CppUnitTest.h"
#include "anvil/core/LocalPointer.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace anvil { namespace core {

	TEST_CLASS(localPointerTest)
	{
	public:
		TEST_METHOD(Integer)
		{
			{
				anvil::LocalPointer<int32_t> ptr;
				ptr.reset();
				*ptr = 123456;
				Assert::AreEqual(123456, *ptr, L"Reset with no parameters failed");
			}

			{
				anvil::LocalPointer<int32_t> ptr;
				ptr.reset<int32_t>(123456);
				Assert::AreEqual(123456, *ptr, L"Reset with parameters failed");
			}

			{
				anvil::LocalPointer<int32_t> ptr(123456);
				Assert::AreEqual(123456, *ptr, L"Allocation constructor failed");
			}
		}
		TEST_METHOD(Destruction)
		{
			int counter = 0;

			class DestructorTest
			{
			public:
				int& counter;

				DestructorTest(int& a_counter) :
					counter(a_counter)
				{}

				~DestructorTest() {
					++counter;
				}
			};

			counter = 0;
			{
				anvil::LocalPointer<DestructorTest> ptr(std::ref<int>(counter));
			}
			Assert::AreEqual(1, counter, L"Destructor was not called");

			counter = 0;
			{
				anvil::LocalPointer<DestructorTest> ptr1(std::ref<int>(counter));
				anvil::LocalPointer<DestructorTest> ptr2(std::ref<int>(counter));
				anvil::LocalPointer<DestructorTest> ptr3(std::ref<int>(counter));
				anvil::LocalPointer<DestructorTest> ptr4(std::ref<int>(counter));
			}
			Assert::AreEqual(4, counter, L"Destructor was not called the expected number of times (block)");

			counter = 0;
			for(int i = 0; i < 1000; ++i){
				anvil::LocalPointer<DestructorTest>(std::ref<int>(counter));
			}
			Assert::AreEqual(1000, counter, L"Destructor was not called the expected number of times (for loop)");
		}
		TEST_METHOD(ReleaseMovable)
		{
			{
				anvil::LocalPointer<std::string> tmp("test");
				Assert::IsTrue(*tmp == "test", L"String not allocated correctly");
				std::string str = tmp.release();
				Assert::IsTrue(str == "test", L"String not allocated correctly");
			}
		}
		TEST_METHOD(ReleaseUnmovable)
		{
			class Unmovable {
			public:
				Unmovable(Unmovable&&) = delete;
				Unmovable(const Unmovable&) = delete;
				Unmovable& operator=(Unmovable&&) = delete;
				Unmovable& operator=(const Unmovable&) = delete;
				Unmovable() = default;
			};

			{
				anvil::LocalPointer<Unmovable> tmp;
				tmp.reset<Unmovable>();
				tmp.release();
			}
		}
	};
}}
