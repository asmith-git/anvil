#include "pch.h"
#include "CppUnitTest.h"
#include "anvil/Core.hpp"
#include "anvil/compute/Type.hpp"
#include <locale>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace anvil { namespace compute {


	TEST_CLASS(TestShortType)
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
			anvil::Type t, ref;

			t.SetRepresentation(anvil::Type::TYPE_UNSIGNED);
			Assert::IsTrue(t.GetRepresentation() == anvil::Type::TYPE_UNSIGNED, L"TYPE_UNSIGNED");
			Assert::IsTrue(ref.GetNumberOfChannels() == t.GetNumberOfChannels(), L"Channel count was corrupted");
			Assert::IsTrue(ref.GetPrimitiveSizeInBytes() == t.GetPrimitiveSizeInBytes(), L"Byte count was corrupted");

			t.SetRepresentation(anvil::Type::TYPE_SIGNED);
			Assert::IsTrue(t.GetRepresentation() == anvil::Type::TYPE_SIGNED, L"TYPE_SIGNED");
			Assert::IsTrue(ref.GetNumberOfChannels() == t.GetNumberOfChannels(), L"Channel count was corrupted");
			Assert::IsTrue(ref.GetPrimitiveSizeInBytes() == t.GetPrimitiveSizeInBytes(), L"Byte count was corrupted");

			t.SetRepresentation(anvil::Type::TYPE_FLOATING_POINT);
			Assert::IsTrue(t.GetRepresentation() == anvil::Type::TYPE_FLOATING_POINT, L"TYPE_FLOATING_POINT");
			Assert::IsTrue(ref.GetNumberOfChannels() == t.GetNumberOfChannels(), L"Channel count was corrupted");
			Assert::IsTrue(ref.GetPrimitiveSizeInBytes() == t.GetPrimitiveSizeInBytes(), L"Byte count was corrupted");
		}
		TEST_METHOD(Channels)
		{
			anvil::Type t, ref;

			t.SetNumberOfChannels(1u);
			Assert::AreEqual((size_t)1u, t.GetNumberOfChannels());
			Assert::IsTrue(ref.GetRepresentation() == t.GetRepresentation(), L"Representation was corrupted");
			Assert::IsTrue(ref.GetPrimitiveSizeInBytes() == t.GetPrimitiveSizeInBytes(), L"Byte count was corrupted");

			t.SetNumberOfChannels(2u);
			Assert::AreEqual((size_t)2u, t.GetNumberOfChannels());
			Assert::IsTrue(ref.GetRepresentation() == t.GetRepresentation(), L"Representation was corrupted");
			Assert::IsTrue(ref.GetPrimitiveSizeInBytes() == t.GetPrimitiveSizeInBytes(), L"Byte count was corrupted");

			t.SetNumberOfChannels(4u);
			Assert::AreEqual((size_t)4u, t.GetNumberOfChannels());
			Assert::IsTrue(ref.GetRepresentation() == t.GetRepresentation(), L"Representation was corrupted");
			Assert::IsTrue(ref.GetPrimitiveSizeInBytes() == t.GetPrimitiveSizeInBytes(), L"Byte count was corrupted");

			t.SetNumberOfChannels(8u);
			Assert::AreEqual((size_t)8u, t.GetNumberOfChannels());
			Assert::IsTrue(ref.GetRepresentation() == t.GetRepresentation(), L"Representation was corrupted");
			Assert::IsTrue(ref.GetPrimitiveSizeInBytes() == t.GetPrimitiveSizeInBytes(), L"Byte count was corrupted");
		}

		TEST_METHOD(Bytes)
		{
			anvil::Type t, ref;

			t.SetSizeInBytes(1u);
			Assert::AreEqual((size_t)1u, t.GetPrimitiveSizeInBytes());
			Assert::IsTrue(ref.GetRepresentation() == t.GetRepresentation(), L"Representation was corrupted");
			Assert::IsTrue(ref.GetNumberOfChannels() == t.GetNumberOfChannels(), L"Channel count was corrupted");

			t.SetSizeInBytes(2u);
			Assert::AreEqual((size_t)2u, t.GetPrimitiveSizeInBytes());
			Assert::IsTrue(ref.GetRepresentation() == t.GetRepresentation(), L"Representation was corrupted");
			Assert::IsTrue(ref.GetNumberOfChannels() == t.GetNumberOfChannels(), L"Channel count was corrupted");

			t.SetSizeInBytes(4u);
			Assert::AreEqual((size_t)4u, t.GetPrimitiveSizeInBytes());
			Assert::IsTrue(ref.GetRepresentation() == t.GetRepresentation(), L"Representation was corrupted");
			Assert::IsTrue(ref.GetNumberOfChannels() == t.GetNumberOfChannels(), L"Channel count was corrupted");

			t.SetSizeInBytes(8u);
			Assert::AreEqual((size_t)8u, t.GetPrimitiveSizeInBytes());
			Assert::IsTrue(ref.GetRepresentation() == t.GetRepresentation(), L"Representation was corrupted");
			Assert::IsTrue(ref.GetNumberOfChannels() == t.GetNumberOfChannels(), L"Channel count was corrupted");
		}

		TEST_METHOD(Bits)
		{
			anvil::Type t, ref;

			t.SetSizeInBytes(1u);
			Assert::AreEqual((size_t)8u, t.GetPrimitiveSizeInBits());
			Assert::IsTrue(ref.GetRepresentation() == t.GetRepresentation(), L"Representation was corrupted");
			Assert::IsTrue(ref.GetNumberOfChannels() == t.GetNumberOfChannels(), L"Channel count was corrupted");

			t.SetSizeInBytes(2u);
			Assert::AreEqual((size_t)16u, t.GetPrimitiveSizeInBits());
			Assert::IsTrue(ref.GetRepresentation() == t.GetRepresentation(), L"Representation was corrupted");
			Assert::IsTrue(ref.GetNumberOfChannels() == t.GetNumberOfChannels(), L"Channel count was corrupted");

			t.SetSizeInBytes(4u);
			Assert::AreEqual((size_t)32u, t.GetPrimitiveSizeInBits());
			Assert::IsTrue(ref.GetRepresentation() == t.GetRepresentation(), L"Representation was corrupted");
			Assert::IsTrue(ref.GetNumberOfChannels() == t.GetNumberOfChannels(), L"Channel count was corrupted");

			t.SetSizeInBytes(8u);
			Assert::AreEqual((size_t)64u, t.GetPrimitiveSizeInBits());
			Assert::IsTrue(ref.GetRepresentation() == t.GetRepresentation(), L"Representation was corrupted");
			Assert::IsTrue(ref.GetNumberOfChannels() == t.GetNumberOfChannels(), L"Channel count was corrupted");
		}
	}; 
	
	TEST_CLASS(TestLongType)
	{
	public:
		TEST_METHOD(Enumerations)
		{
			try {
				for (size_t i = 0u; i < 256u; ++i) {
					anvil::EnumeratedType t = static_cast<anvil::EnumeratedType>(i);
					anvil::EnumeratedType t2 = anvil::LongType(t).GetEnumeratedType();
					Assert::AreEqual((int)t, (int)t2);
				}
			}
			catch (std::exception& e) {
				Assert::Fail(std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>>().from_bytes(e.what()).c_str());
			}

		}

		TEST_METHOD(Representation)
		{
			anvil::LongType t, ref;

			t.SetRepresentation(anvil::Type::TYPE_UNSIGNED);
			Assert::IsTrue(t.GetRepresentation() == anvil::Type::TYPE_UNSIGNED, L"TYPE_UNSIGNED");
			Assert::IsTrue(ref.GetNumberOfChannels() == t.GetNumberOfChannels(), L"Channel count was corrupted");
			Assert::IsTrue(ref.GetPrimitiveSizeInBytes() == t.GetPrimitiveSizeInBytes(), L"Byte count was corrupted");

			t.SetRepresentation(anvil::Type::TYPE_SIGNED);
			Assert::IsTrue(t.GetRepresentation() == anvil::Type::TYPE_SIGNED, L"TYPE_SIGNED");
			Assert::IsTrue(ref.GetNumberOfChannels() == t.GetNumberOfChannels(), L"Channel count was corrupted");
			Assert::IsTrue(ref.GetPrimitiveSizeInBytes() == t.GetPrimitiveSizeInBytes(), L"Byte count was corrupted");

			t.SetRepresentation(anvil::Type::TYPE_FLOATING_POINT);
			Assert::IsTrue(t.GetRepresentation() == anvil::Type::TYPE_FLOATING_POINT, L"TYPE_FLOATING_POINT");
			Assert::IsTrue(ref.GetNumberOfChannels() == t.GetNumberOfChannels(), L"Channel count was corrupted");
			Assert::IsTrue(ref.GetPrimitiveSizeInBytes() == t.GetPrimitiveSizeInBytes(), L"Byte count was corrupted");
		}

		TEST_METHOD(Channels)
		{
			anvil::LongType t, ref;

			for (size_t i = anvil::LongType::MIN_CHANNELS; i < anvil::LongType::MAX_CHANNELS; ++i) {
				t.SetNumberOfChannels(i);
				Assert::AreEqual(i, t.GetNumberOfChannels());
				Assert::IsTrue(ref.GetRepresentation() == t.GetRepresentation(), L"Representation was corrupted");
				Assert::IsTrue(ref.GetPrimitiveSizeInBytes() == t.GetPrimitiveSizeInBytes(), L"Byte count was corrupted");
			}
		}

		TEST_METHOD(Bytes)
		{
			anvil::LongType t, ref;

			for (size_t i = anvil::LongType::MIN_CHANNEL_BYTES; i < anvil::LongType::MAX_CHANNEL_BYTES; ++i) {
				t.SetSizeInBytes(i);
				Assert::AreEqual(i, t.GetPrimitiveSizeInBytes());
				Assert::IsTrue(ref.GetRepresentation() == t.GetRepresentation(), L"Representation was corrupted");
				Assert::IsTrue(ref.GetNumberOfChannels() == t.GetNumberOfChannels(), L"Channel count was corrupted");
			}
		}

		TEST_METHOD(Bits)
		{
			anvil::LongType t, ref;

			for (size_t i = anvil::LongType::MIN_CHANNEL_BYTES; i < anvil::LongType::MIN_CHANNEL_BYTES; ++i) {
				t.SetSizeInBytes(i);
				Assert::AreEqual(i * 8u, t.GetPrimitiveSizeInBits());
				Assert::IsTrue(ref.GetRepresentation() == t.GetRepresentation(), L"Representation was corrupted");
				Assert::IsTrue(ref.GetNumberOfChannels() == t.GetNumberOfChannels(), L"Channel count was corrupted");
			}
		}
	};
}}
