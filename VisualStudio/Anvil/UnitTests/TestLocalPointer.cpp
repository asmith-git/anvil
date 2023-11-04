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

			class DestructorTest {
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


		TEST_METHOD(VirtualDestruction)
		{
			int base_counter = 0;
			int child_counter = 0;

			class IDestructorTest {
			private:
				int& _base_counter;
			public:
				IDestructorTest(int& counter) :
					_base_counter(counter)
				{}

				virtual ~IDestructorTest() {
					++_base_counter;
				}
			};

			class DestructorTest final : IDestructorTest {
			private:
				int& _child_counter;
			public:
				DestructorTest(int& base_counter, int& child_counter) :
					IDestructorTest(base_counter),
					_child_counter(child_counter)
				{}

				virtual ~DestructorTest() {
					++_child_counter;
				}
			};

			base_counter = 0;
			child_counter = 0;
			for(int i = 0; i < 1000; ++i) {
				anvil::LocalPointer<IDestructorTest, sizeof(DestructorTest)> ptr;
				ptr.reset<DestructorTest>(std::ref<int>(base_counter), std::ref<int>(child_counter));
			}
			Assert::AreEqual(1000, base_counter, L"Base class destructor was not called the expected number of times");
			Assert::AreEqual(1000, child_counter, L"Child class destructor was not called the expected number of times");
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

		TEST_METHOD(Move)
		{
			{
				anvil::LocalPointer<std::string> a("a");
				anvil::LocalPointer<std::string> b("b");
				Assert::IsTrue(*a == "a", L"A string not allocated correctly");
				Assert::IsTrue(*b == "b", L"B string not allocated correctly");

				a = std::move(b);
				Assert::IsTrue(*a == "b", L"B string not moved correctly");
				Assert::IsTrue(b->empty(), L"Expected B string to be empty");
			}
		}
	};
}}
