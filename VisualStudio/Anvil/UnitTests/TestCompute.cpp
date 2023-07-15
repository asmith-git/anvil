#include "pch.h"
#include "CppUnitTest.h"
#include "anvil/Core.hpp"
#include "anvil/compute/Type.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace anvil { namespace compute {


	TEST_CLASS(TestType)
	{
	public:
		TEST_METHOD(Enumerations)
		{
			for (size_t i = 0u; i < 256u; ++i) {
				anvil::EnumeratedType t = static_cast<anvil::EnumeratedType>(i);
				anvil::EnumeratedType t2 = anvil::Type(t).GetEnumeratedType();
				Assert::AreEqual((int)t,(int)t2);
			}
			
		}

		TEST_METHOD(Representation)
		{
			anvil::Type t;

			t.SetRepresentation(anvil::Type::TYPE_UNSIGNED);
			Assert::IsTrue(t.GetRepresentation() == anvil::Type::TYPE_UNSIGNED, L"TYPE_UNSIGNED");

			t.SetRepresentation(anvil::Type::TYPE_SIGNED);
			Assert::IsTrue(t.GetRepresentation() == anvil::Type::TYPE_SIGNED, L"TYPE_SIGNED");

			t.SetRepresentation(anvil::Type::TYPE_FLOATING_POINT);
			Assert::IsTrue(t.GetRepresentation() == anvil::Type::TYPE_FLOATING_POINT, L"TYPE_FLOATING_POINT");
		}

		TEST_METHOD(Channels)
		{
			anvil::Type t;

			t.SetNumberOfChannels(1u);
			Assert::AreEqual(t.GetNumberOfChannels(), (size_t) 1u);

			t.SetNumberOfChannels(2u);
			Assert::AreEqual(t.GetNumberOfChannels(), (size_t)2u);

			t.SetNumberOfChannels(4u);
			Assert::AreEqual(t.GetNumberOfChannels(), (size_t)4u);

			t.SetNumberOfChannels(8u);
			Assert::AreEqual(t.GetNumberOfChannels(), (size_t)8u);
		}
	};
}}
