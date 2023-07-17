#include "pch.h"
#include "CppUnitTest.h"
#include "anvil/Core.hpp"
#include "anvil/compute.hpp"
#include <locale>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace anvil { namespace compute {

	TEST_CLASS(TestImage)
	{
	public:
		void FillImage(Image& img, Vector value) {
			size_t w = img.GetHeight();
			size_t h = img.GetHeight();
			for (size_t y = 0u; y < h; ++y) {
				for (size_t x = 0u; x < w; ++x) {
					img.WritePixel(x, y, value);
				}
			}
		}

		TEST_METHOD(RowAddress)
		{
			try {

				Image img;
				img.Allocate(ANVIL_8UX4, 512, 512);
				Assert::IsTrue(img.IsContiguous(), L"Allocated memory was not contiguous");

				uint32_t* tmp = (uint32_t*)img.GetData();
				size_t w = img.GetHeight();
				size_t h = img.GetHeight();
				for (size_t y = 0u; y < h; ++y) {
					Assert::IsTrue(tmp == img.GetRowAddress(y), L"Calculated the wrong address");
					tmp += w;
				}

			}
			catch (std::exception& e) {
				Assert::Fail(std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>>().from_bytes(e.what()).c_str());
			}
		}
		TEST_METHOD(PixelAddress)
		{
			try {

				Image img;
				img.Allocate(ANVIL_8UX4, 512, 512);
				Assert::IsTrue(img.IsContiguous(), L"Allocated memory was not contiguous");

				uint32_t* tmp = (uint32_t*)img.GetData();
				size_t w = img.GetHeight();
				size_t h = img.GetHeight();
				for (size_t y = 0u; y < h; ++y) {
					for (size_t x = 0u; x < w; ++x) {
						Assert::IsTrue(tmp == img.GetPixelAddress(x, y), L"Calculated the wrong address");
						++tmp;
					}
				}

			}
			catch (std::exception& e) {
				Assert::Fail(std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>>().from_bytes(e.what()).c_str());
			}
		}
		TEST_METHOD(Roi)
		{
				try {

				Image img;
				img.Allocate(ANVIL_8UX1, 64, 64);
				FillImage(img, Vector(128, img.GetType()));

				Image roi = img.GetRoi(16, 16, 32, 32);
				FillImage(roi, Vector(255, img.GetType()));

				size_t roix, roiy;
				roi.GetRoiPosition(roix, roiy);
				Assert::AreEqual((size_t)16, roix, L"ROI has wrong X position");
				Assert::AreEqual((size_t)16, roiy, L"ROI has wrong Y position");

				size_t imgw = img.GetWidth();
				size_t imgh = img.GetHeight();
				size_t roiw = roi.GetWidth();
				size_t roih = roi.GetHeight();
				Assert::AreEqual((size_t) 32, roiw, L"ROI has wrong width");
				Assert::AreEqual((size_t) 32, roih, L"ROI has wrong height");
				Assert::AreEqual((int)img.GetType().GetEnumeratedType(), (int)roi.GetType().GetEnumeratedType(), L"ROI has wrong type");

				for (size_t y = 0u; y < roih; ++y) {
					for (size_t x = 0u; x < roiw; ++x) {
						uint8_t tmp;
						roi.ReadPixel(x, y, tmp);
						Assert::AreEqual((uint8_t)255, tmp, (L"ROI  contained a pixel with a wrong value (before copy) " + std::to_wstring(x) + L"," + std::to_wstring(y)).c_str());
					}
				}

				for (size_t y = 0u; y < imgh; ++y) { 
					for (size_t x = 0u; x < imgw; ++x) {
						uint8_t tmp;
						img.ReadPixel(x, y, tmp);
						if (x >= roix && x < roix + roih && y >= roiy && y < roiy + roih) {
							Assert::AreEqual((uint8_t)255, tmp, (L"Inside ROI contained a pixel with a wrong value (before copy) " + std::to_wstring(x) + L"," + std::to_wstring(y)).c_str());
						} else {
							Assert::AreEqual((uint8_t)128, tmp, (L"Outside ROI contained a pixel with a wrong value (before copy) " + std::to_wstring(x) + L"," + std::to_wstring(y)).c_str());
						}
					}
				}

				roi = roi.DeepCopy();

				for (size_t y = 0u; y < roih; ++y) {
					for (size_t x = 0u; x < roiw; ++x) {
						uint8_t tmp;
						roi.ReadPixel(x, y, tmp);
						Assert::AreEqual((uint8_t)255, tmp, (L"ROI  contained a pixel with a wrong value (after copy)" + std::to_wstring(x) + L"," + std::to_wstring(y)).c_str());
					}
				}

			} catch (std::exception& e) {
				Assert::Fail(std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>>().from_bytes(e.what()).c_str());
			}
		}

		TEST_METHOD(ChannelPixelStep)
		{
			try {

				Image img;
				img.Allocate(ANVIL_8UX4, 64, 64);
				FillImage(img, Vector(128, img.GetType()));

				Image r = img.GetChannel(0);
				FillImage(r, Vector(0, img.GetType()));
				Image g = img.GetChannel(1);
				FillImage(g, Vector(1, img.GetType()));
				Image b = img.GetChannel(2);
				FillImage(b, Vector(2, img.GetType()));
				Image a = img.GetChannel(3);
				FillImage(a, Vector(3, img.GetType()));

				{
					// Check channels in the correct order
					uint8_t* tmp = (uint8_t*)img.GetData();
					Assert::AreEqual((uint8_t)0, tmp[0], L"R channel contained a pixel with a wrong value (order check)");
					Assert::AreEqual((uint8_t)1, tmp[1], L"G channel contained a pixel with a wrong value (order check)");
					Assert::AreEqual((uint8_t)2, tmp[2], L"B channel contained a pixel with a wrong value (order check)");
					Assert::AreEqual((uint8_t)3, tmp[3], L"A channel contained a pixel with a wrong value (order check)");
				}

				size_t w = r.GetWidth();
				size_t h = r.GetHeight();
				size_t s = w * h;
				Assert::AreEqual(img.GetWidth(), w, L"R channel has wrong width");
				Assert::AreEqual(img.GetHeight(), w, L"R channel has wrong height");
				Assert::AreEqual((int)ANVIL_8UX1, (int)r.GetType().GetEnumeratedType(), L"R channel has wrong type");

				for (size_t y = 0u; y < h; ++y) for (size_t x = 0u; x < w; ++x) {
					uint8_t tmp;
					r.ReadPixel(x, y, tmp);
					Assert::AreEqual((uint8_t)0, tmp, L"R channel contained a pixel with a wrong value (before copy)");
				}

				for (size_t y = 0u; y < h; ++y) for (size_t x = 0u; x < w; ++x) {
					uint8_t tmp;
					g.ReadPixel(x, y, tmp);
					Assert::AreEqual((uint8_t)1, tmp, L"G channel contained a pixel with a wrong value (before copy)");
				}

				for (size_t y = 0u; y < h; ++y) for (size_t x = 0u; x < w; ++x) {
					uint8_t tmp;
					b.ReadPixel(x, y, tmp);
					Assert::AreEqual((uint8_t)2, tmp, L"B channel contained a pixel with a wrong value (before copy)");
				}

				for (size_t y = 0u; y < h; ++y) for (size_t x = 0u; x < w; ++x) {
					uint8_t tmp;
					a.ReadPixel(x, y, tmp);
					Assert::AreEqual((uint8_t)3, tmp, L"A channel contained a pixel with a wrong value (before copy)");
				}

				r = r.DeepCopy();
				g = g.DeepCopy();
				b = b.DeepCopy();
				a = a.DeepCopy();

				uint8_t* tmp;

				tmp = (uint8_t*) r.GetData();
				for (size_t i = 0u; i < s; ++i) Assert::AreEqual((uint8_t)0, tmp[i], L"R channel contained a pixel with a wrong value (after copy)");

				tmp = (uint8_t*)g.GetData();
				for (size_t i = 0u; i < s; ++i) Assert::AreEqual((uint8_t)1, tmp[i], L"G channel contained a pixel with a wrong value (after copy)");

				tmp = (uint8_t*)b.GetData();
				for (size_t i = 0u; i < s; ++i) Assert::AreEqual((uint8_t)2, tmp[i], L"B channel contained a pixel with a wrong value (after copy)");

				tmp = (uint8_t*)a.GetData();
				for (size_t i = 0u; i < s; ++i) Assert::AreEqual((uint8_t)3, tmp[i], L"A channel contained a pixel with a wrong value (after copy)");

			} catch (std::exception& e) {
				Assert::Fail(std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>>().from_bytes(e.what()).c_str());
			}
		}
	};

	TEST_CLASS(TestShortType)
	{
	public:

		TEST_METHOD(EnumerationConstants) {
			Assert::AreEqual((int)Type::TYPE_UNSIGNED, (int)Type(ANVIL_8UX1).GetRepresentation(),L"Representation is wrong");
			Assert::AreEqual((int)Type::TYPE_UNSIGNED, (int)Type(ANVIL_16UX1).GetRepresentation(), L"Representation is wrong");
			Assert::AreEqual((int)Type::TYPE_UNSIGNED, (int)Type(ANVIL_32UX1).GetRepresentation(), L"Representation is wrong");
			Assert::AreEqual((int)Type::TYPE_UNSIGNED, (int)Type(ANVIL_64UX1).GetRepresentation(), L"Representation is wrong");
			Assert::AreEqual((int)Type::TYPE_SIGNED, (int)Type(ANVIL_8SX1).GetRepresentation(), L"Representation is wrong");
			Assert::AreEqual((int)Type::TYPE_SIGNED, (int)Type(ANVIL_16SX1).GetRepresentation(), L"Representation is wrong");
			Assert::AreEqual((int)Type::TYPE_SIGNED, (int)Type(ANVIL_32SX1).GetRepresentation(), L"Representation is wrong");
			Assert::AreEqual((int)Type::TYPE_SIGNED, (int)Type(ANVIL_64SX1).GetRepresentation(), L"Representation is wrong");
			Assert::AreEqual((int)Type::TYPE_FLOATING_POINT, (int)Type(ANVIL_8FX1).GetRepresentation(), L"Representation is wrong");
			Assert::AreEqual((int)Type::TYPE_FLOATING_POINT, (int)Type(ANVIL_16FX1).GetRepresentation(), L"Representation is wrong");
			Assert::AreEqual((int)Type::TYPE_FLOATING_POINT, (int)Type(ANVIL_32FX1).GetRepresentation(), L"Representation is wrong");
			Assert::AreEqual((int)Type::TYPE_FLOATING_POINT, (int)Type(ANVIL_64FX1).GetRepresentation(), L"Representation is wrong");

			Assert::AreEqual((int)1, (int)Type(ANVIL_8UX1).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)1, (int)Type(ANVIL_16UX1).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)1, (int)Type(ANVIL_32UX1).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)1, (int)Type(ANVIL_64UX1).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)1, (int)Type(ANVIL_8SX1).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)1, (int)Type(ANVIL_16SX1).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)1, (int)Type(ANVIL_32SX1).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)1, (int)Type(ANVIL_64SX1).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)1, (int)Type(ANVIL_8FX1).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)1, (int)Type(ANVIL_16FX1).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)1, (int)Type(ANVIL_32FX1).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)1, (int)Type(ANVIL_64FX1).GetNumberOfChannels(), L"Number of channels is wrong");

			Assert::AreEqual((int)1, (int)Type(ANVIL_8UX1).GetSizeInBytes(), L"Size in bytes is wrong");
			Assert::AreEqual((int)2, (int)Type(ANVIL_16UX1).GetSizeInBytes(), L"Size in bytes is wrong");
			Assert::AreEqual((int)4, (int)Type(ANVIL_32UX1).GetSizeInBytes(), L"Size in bytes is wrong");
			Assert::AreEqual((int)8, (int)Type(ANVIL_64UX1).GetSizeInBytes(), L"Size in bytes is wrong");
			Assert::AreEqual((int)1, (int)Type(ANVIL_8SX1).GetSizeInBytes(), L"Size in bytes is wrong");
			Assert::AreEqual((int)2, (int)Type(ANVIL_16SX1).GetSizeInBytes(), L"Size in bytes is wrong");
			Assert::AreEqual((int)4, (int)Type(ANVIL_32SX1).GetSizeInBytes(), L"Size in bytes is wrong");
			Assert::AreEqual((int)8, (int)Type(ANVIL_64SX1).GetSizeInBytes(), L"Size in bytes is wrong");
			Assert::AreEqual((int)1, (int)Type(ANVIL_8FX1).GetSizeInBytes(), L"Size in bytes is wrong");
			Assert::AreEqual((int)2, (int)Type(ANVIL_16FX1).GetSizeInBytes(), L"Size in bytes is wrong");
			Assert::AreEqual((int)4, (int)Type(ANVIL_32FX1).GetSizeInBytes(), L"Size in bytes is wrong");
			Assert::AreEqual((int)8, (int)Type(ANVIL_64FX1).GetSizeInBytes(), L"Size in bytes is wrong");

			Assert::AreEqual((int)2, (int)Type(ANVIL_8UX2).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)3, (int)Type(ANVIL_8UX3).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)4, (int)Type(ANVIL_8UX4).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)5, (int)Type(ANVIL_8UX5).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)6, (int)Type(ANVIL_8UX6).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)7, (int)Type(ANVIL_8UX7).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)8, (int)Type(ANVIL_8UX8).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)9, (int)Type(ANVIL_8UX9).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)10, (int)Type(ANVIL_8UX10).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)11, (int)Type(ANVIL_8UX11).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)12, (int)Type(ANVIL_8UX12).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)13, (int)Type(ANVIL_8UX13).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)14, (int)Type(ANVIL_8UX14).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)15, (int)Type(ANVIL_8UX15).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)16, (int)Type(ANVIL_8UX16).GetNumberOfChannels(), L"Number of channels is wrong");
		}
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

		TEST_METHOD(OpenCV) 
		{
#if ANVIL_OPENCV_SUPPORT
			int values[] = {
				CV_8U, CV_8UC1, CV_8UC2, CV_8UC3, CV_8UC4,
				CV_16U, CV_16UC1, CV_16UC2, CV_16UC3, CV_16UC4,
				CV_8S, CV_8SC1, CV_8SC2, CV_8SC3, CV_8SC4,
				CV_16S, CV_16SC1, CV_16SC2, CV_16SC3, CV_16SC4,
				CV_32S, CV_32SC1, CV_32SC2, CV_32SC3, CV_32SC4,
				CV_16F, CV_16FC1, CV_16FC2, CV_16FC3, CV_16FC4,
				CV_32F, CV_32FC1, CV_32FC2, CV_32FC3, CV_32FC4,
				CV_64F, CV_64FC1, CV_64FC2, CV_64FC3, CV_64FC4
			};

			try {
				for(int i : values) {
					Assert::AreEqual(i, anvil::Type::ToOpenCVType(anvil::Type::FromOpenCVType(i)));
				}
			} catch (std::exception& e) {
				Assert::Fail(std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>>().from_bytes(e.what()).c_str());
			}
#else
			Assert::Fail(L"OpenCV was not detected");
#endif
		}
	}; 
	
	TEST_CLASS(TestLongType)
	{
	public:
		TEST_METHOD(EnumerationConstants) {
			Assert::AreEqual((int)Type::TYPE_UNSIGNED, (int)LongType(ANVIL_8UX1).GetRepresentation(), L"Representation is wrong");
			Assert::AreEqual((int)Type::TYPE_UNSIGNED, (int)LongType(ANVIL_16UX1).GetRepresentation(), L"Representation is wrong");
			Assert::AreEqual((int)Type::TYPE_UNSIGNED, (int)LongType(ANVIL_32UX1).GetRepresentation(), L"Representation is wrong");
			Assert::AreEqual((int)Type::TYPE_UNSIGNED, (int)LongType(ANVIL_64UX1).GetRepresentation(), L"Representation is wrong");
			Assert::AreEqual((int)Type::TYPE_SIGNED, (int)LongType(ANVIL_8SX1).GetRepresentation(), L"Representation is wrong");
			Assert::AreEqual((int)Type::TYPE_SIGNED, (int)LongType(ANVIL_16SX1).GetRepresentation(), L"Representation is wrong");
			Assert::AreEqual((int)Type::TYPE_SIGNED, (int)LongType(ANVIL_32SX1).GetRepresentation(), L"Representation is wrong");
			Assert::AreEqual((int)Type::TYPE_SIGNED, (int)LongType(ANVIL_64SX1).GetRepresentation(), L"Representation is wrong");
			Assert::AreEqual((int)Type::TYPE_FLOATING_POINT, (int)LongType(ANVIL_8FX1).GetRepresentation(), L"Representation is wrong");
			Assert::AreEqual((int)Type::TYPE_FLOATING_POINT, (int)LongType(ANVIL_16FX1).GetRepresentation(), L"Representation is wrong");
			Assert::AreEqual((int)Type::TYPE_FLOATING_POINT, (int)LongType(ANVIL_32FX1).GetRepresentation(), L"Representation is wrong");
			Assert::AreEqual((int)Type::TYPE_FLOATING_POINT, (int)LongType(ANVIL_64FX1).GetRepresentation(), L"Representation is wrong");

			Assert::AreEqual((int)1, (int)LongType(ANVIL_8UX1).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)1, (int)LongType(ANVIL_16UX1).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)1, (int)LongType(ANVIL_32UX1).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)1, (int)LongType(ANVIL_64UX1).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)1, (int)LongType(ANVIL_8SX1).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)1, (int)LongType(ANVIL_16SX1).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)1, (int)LongType(ANVIL_32SX1).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)1, (int)LongType(ANVIL_64SX1).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)1, (int)LongType(ANVIL_8FX1).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)1, (int)LongType(ANVIL_16FX1).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)1, (int)LongType(ANVIL_32FX1).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)1, (int)LongType(ANVIL_64FX1).GetNumberOfChannels(), L"Number of channels is wrong");

			Assert::AreEqual((int)1, (int)LongType(ANVIL_8UX1).GetSizeInBytes(), L"Size in bytes is wrong");
			Assert::AreEqual((int)2, (int)LongType(ANVIL_16UX1).GetSizeInBytes(), L"Size in bytes is wrong");
			Assert::AreEqual((int)4, (int)LongType(ANVIL_32UX1).GetSizeInBytes(), L"Size in bytes is wrong");
			Assert::AreEqual((int)8, (int)LongType(ANVIL_64UX1).GetSizeInBytes(), L"Size in bytes is wrong");
			Assert::AreEqual((int)1, (int)LongType(ANVIL_8SX1).GetSizeInBytes(), L"Size in bytes is wrong");
			Assert::AreEqual((int)2, (int)LongType(ANVIL_16SX1).GetSizeInBytes(), L"Size in bytes is wrong");
			Assert::AreEqual((int)4, (int)LongType(ANVIL_32SX1).GetSizeInBytes(), L"Size in bytes is wrong");
			Assert::AreEqual((int)8, (int)LongType(ANVIL_64SX1).GetSizeInBytes(), L"Size in bytes is wrong");
			Assert::AreEqual((int)1, (int)LongType(ANVIL_8FX1).GetSizeInBytes(), L"Size in bytes is wrong");
			Assert::AreEqual((int)2, (int)LongType(ANVIL_16FX1).GetSizeInBytes(), L"Size in bytes is wrong");
			Assert::AreEqual((int)4, (int)LongType(ANVIL_32FX1).GetSizeInBytes(), L"Size in bytes is wrong");
			Assert::AreEqual((int)8, (int)LongType(ANVIL_64FX1).GetSizeInBytes(), L"Size in bytes is wrong");

			Assert::AreEqual((int)2, (int)LongType(ANVIL_8UX2).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)3, (int)LongType(ANVIL_8UX3).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)4, (int)LongType(ANVIL_8UX4).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)5, (int)LongType(ANVIL_8UX5).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)6, (int)LongType(ANVIL_8UX6).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)7, (int)LongType(ANVIL_8UX7).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)8, (int)LongType(ANVIL_8UX8).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)9, (int)LongType(ANVIL_8UX9).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)10, (int)LongType(ANVIL_8UX10).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)11, (int)LongType(ANVIL_8UX1).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)12, (int)LongType(ANVIL_8UX12).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)13, (int)LongType(ANVIL_8UX13).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)14, (int)LongType(ANVIL_8UX14).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)15, (int)LongType(ANVIL_8UX15).GetNumberOfChannels(), L"Number of channels is wrong");
			Assert::AreEqual((int)16, (int)LongType(ANVIL_8UX16).GetNumberOfChannels(), L"Number of channels is wrong");
		}
		TEST_METHOD(Enumerations)
		{
			try {
				for (size_t i = 0u; i < 256u; ++i) {
					anvil::EnumeratedType t = static_cast<anvil::EnumeratedType>(i);
					anvil::EnumeratedType t2 = anvil::LongType(t).GetEnumeratedType();
					Assert::AreEqual((int)t, (int)t2);
				}
			} catch (std::exception& e) {
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


	TEST_CLASS(ArithmeticF32)
	{
	public:
		void TestMasking(uint64_t instruction_set) {
			try {
				ArithmeticOperations* operations = ArithmeticOperations::GetArithmeticOperations(ANVIL_32FX1, instruction_set);
				Assert::IsNotNull(operations, L"No operations implementation detected");

				float a[4];
				float b[4];
				float c[4];
				uint8_t mask;

				for (float& val : a) val = 1.f;
				for (float& val : b) val = 0.f;

				mask = 0u;
				operations->Mask(a, b, c, 4u, &mask);
				for (float val : c) Assert::AreEqual(0.f, val, L"Mask with all zeros failed");

				mask = 15u;
				operations->Mask(a, b, c, 4u, &mask);
				for (float val : c) Assert::AreEqual(1.f, val, L"Mask with all ones failed");

				mask = 1u | 4u;
				operations->Mask(a, b, c, 4u, &mask);
				Assert::AreEqual(1.f, c[0u], L"Mask 1010 failed");
				Assert::AreEqual(0.f, c[1u], L"Mask 1010 failed");
				Assert::AreEqual(1.f, c[2u], L"Mask 1010 failed");
				Assert::AreEqual(0.f, c[3u], L"Mask 1010 failed");

				for (float& val : a) val = 0.f;
				for (float& val : b) val = 1.f;
				mask = 1u | 4u;
				operations->AddMask(a, b, c, 4u, &mask);
				Assert::AreEqual(1.f, c[0u], L"AddMask 1010 failed");
				Assert::AreEqual(0.f, c[1u], L"AddMask 1010 failed");
				Assert::AreEqual(1.f, c[2u], L"AddMask 1010 failed");
				Assert::AreEqual(0.f, c[3u], L"AddMask 1010 failed");

				for (float& val : a) val = 3.f;
				for (float& val : b) val = 1.f;
				mask = 1u | 4u;
				operations->SubtractMask(a, b, c, 4u, &mask);
				Assert::AreEqual(2.f, c[0u], L"SubtractMask 1010 failed");
				Assert::AreEqual(3.f, c[1u], L"SubtractMask 1010 failed");
				Assert::AreEqual(2.f, c[2u], L"SubtractMask 1010 failed");
				Assert::AreEqual(3.f, c[3u], L"SubtractMask 1010 failed");

				for (float& val : a) val = 3.f;
				for (float& val : b) val = 2.f;
				mask = 1u | 4u;
				operations->MultiplyMask(a, b, c, 4u, &mask);
				Assert::AreEqual(6.f, c[0u], L"MultiplyMask 1010 failed");
				Assert::AreEqual(3.f, c[1u], L"MultiplyMask 1010 failed");
				Assert::AreEqual(6.f, c[2u], L"MultiplyMask 1010 failed");
				Assert::AreEqual(3.f, c[3u], L"MultiplyMask 1010 failed");

				for (float& val : a) val = 6.f;
				for (float& val : b) val = 2.f;
				mask = 1u | 4u;
				operations->DivideMask(a, b, c, 4u, &mask);
				Assert::AreEqual(3.f, c[0u], L"DivideMask 1010 failed");
				Assert::AreEqual(6.f, c[1u], L"DivideMask 1010 failed");
				Assert::AreEqual(3.f, c[2u], L"DivideMask 1010 failed");
				Assert::AreEqual(6.f, c[3u], L"DivideMask 1010 failed");
			
			} catch (std::exception& e) {
				Assert::Fail(std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>>().from_bytes(e.what()).c_str());
			}
		}



		TEST_METHOD(MaskCpp)
		{
			TestMasking(0u);
		}

		TEST_METHOD(MaskSSE)
		{
			enum { IS = ASM_SSE | ASM_SSE2};
			Assert::IsTrue((SupportedInstructionSets& IS) == IS, L"CPU does not support SSE instruction set");
			TestMasking(IS);

		}

		TEST_METHOD(MaskSSE4)
		{
			enum { IS = ASM_SSE | ASM_SSE2 | ASM_SSE41 };
			Assert::IsTrue((SupportedInstructionSets & IS) == IS, L"CPU does not support SSE 4.1 instruction set");
			TestMasking(IS);
		}

		TEST_METHOD(MaskFMA3)
		{
			enum { IS = ASM_SSE41 | ASM_FMA3 };
			Assert::IsTrue((SupportedInstructionSets & IS) == IS, L"CPU does not support FMA3 instruction set");
			TestMasking(IS);
		}

		TEST_METHOD(MaskAVX512)
		{
			enum { IS = ASM_AVX512F | ASM_AVX512VL };
			Assert::IsTrue((SupportedInstructionSets & IS) == IS, L"CPU does not support AVX-512F/VL instruction set");
			TestMasking(IS);
		}
	};
}}
