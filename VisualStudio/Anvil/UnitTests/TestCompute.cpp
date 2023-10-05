#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING 
#include "CppUnitTest.h"
#include "anvil/Core.hpp"
#include "anvil/compute.hpp"
#include <locale>
#include <bitset>
#include <sstream>
#include <iomanip>

#define STR2WSTR(str) std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>>().from_bytes(str)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace anvil { namespace compute {


	TEST_CLASS(OCV)
	{
	public:

		TEST_METHOD(Type)
		{
			Assert::AreEqual((int)CV_8UC1, (int)anvil::Type(anvil::Type::FromOpenCVType(CV_8UC1)).GetOpenCVType(), L"CV_8UC1 has wrong type");
			Assert::AreEqual((int)CV_8SC1, (int)anvil::Type(anvil::Type::FromOpenCVType(CV_8SC1)).GetOpenCVType(), L"CV_8SC1 has wrong type");
			Assert::AreEqual((int)CV_16SC1, (int)anvil::Type(anvil::Type::FromOpenCVType(CV_16SC1)).GetOpenCVType(), L"CV_16SC1 has wrong type");
			Assert::AreEqual((int)CV_16UC1, (int)anvil::Type(anvil::Type::FromOpenCVType(CV_16UC1)).GetOpenCVType(), L"CV_16UC1 has wrong type");
			Assert::AreEqual((int)CV_32SC1, (int)anvil::Type(anvil::Type::FromOpenCVType(CV_32SC1)).GetOpenCVType(), L"CV_32SC1 has wrong type");
			Assert::AreEqual((int)CV_32FC1, (int)anvil::Type(anvil::Type::FromOpenCVType(CV_32FC1)).GetOpenCVType(), L"CV_32FC1 has wrong type");
			Assert::AreEqual((int)CV_64FC1, (int)anvil::Type(anvil::Type::FromOpenCVType(CV_64FC1)).GetOpenCVType(), L"CV_64FC1 has wrong type");

			Assert::AreEqual((int)CV_8UC2, (int)anvil::Type(anvil::Type::FromOpenCVType(CV_8UC2)).GetOpenCVType(), L"CV_8UC2 has wrong type");
			Assert::AreEqual((int)CV_8SC2, (int)anvil::Type(anvil::Type::FromOpenCVType(CV_8SC2)).GetOpenCVType(), L"CV_8SC2 has wrong type");
			Assert::AreEqual((int)CV_16SC2, (int)anvil::Type(anvil::Type::FromOpenCVType(CV_16SC2)).GetOpenCVType(), L"CV_16SC2 has wrong type");
			Assert::AreEqual((int)CV_16UC2, (int)anvil::Type(anvil::Type::FromOpenCVType(CV_16UC2)).GetOpenCVType(), L"CV_16UC2 has wrong type");
			Assert::AreEqual((int)CV_32SC2, (int)anvil::Type(anvil::Type::FromOpenCVType(CV_32SC2)).GetOpenCVType(), L"CV_32SC2 has wrong type");
			Assert::AreEqual((int)CV_32FC2, (int)anvil::Type(anvil::Type::FromOpenCVType(CV_32FC2)).GetOpenCVType(), L"CV_32FC2 has wrong type");
			Assert::AreEqual((int)CV_64FC2, (int)anvil::Type(anvil::Type::FromOpenCVType(CV_64FC2)).GetOpenCVType(), L"CV_64FC2 has wrong type");

			Assert::AreEqual((int)CV_8UC3, (int)anvil::Type(anvil::Type::FromOpenCVType(CV_8UC3)).GetOpenCVType(), L"CV_8UC3 has wrong type");
			Assert::AreEqual((int)CV_8SC3, (int)anvil::Type(anvil::Type::FromOpenCVType(CV_8SC3)).GetOpenCVType(), L"CV_8SC3 has wrong type");
			Assert::AreEqual((int)CV_16SC3, (int)anvil::Type(anvil::Type::FromOpenCVType(CV_16SC3)).GetOpenCVType(), L"CV_16SC3 has wrong type");
			Assert::AreEqual((int)CV_16UC3, (int)anvil::Type(anvil::Type::FromOpenCVType(CV_16UC3)).GetOpenCVType(), L"CV_16UC3 has wrong type");
			Assert::AreEqual((int)CV_32SC3, (int)anvil::Type(anvil::Type::FromOpenCVType(CV_32SC3)).GetOpenCVType(), L"CV_32SC3 has wrong type");
			Assert::AreEqual((int)CV_32FC3, (int)anvil::Type(anvil::Type::FromOpenCVType(CV_32FC3)).GetOpenCVType(), L"CV_32FC3 has wrong type");
			Assert::AreEqual((int)CV_64FC3, (int)anvil::Type(anvil::Type::FromOpenCVType(CV_64FC3)).GetOpenCVType(), L"CV_64FC3 has wrong type");

			Assert::AreEqual((int)CV_8UC4, (int)anvil::Type(anvil::Type::FromOpenCVType(CV_8UC4)).GetOpenCVType(), L"CV_8UC4 has wrong type");
			Assert::AreEqual((int)CV_8SC4, (int)anvil::Type(anvil::Type::FromOpenCVType(CV_8SC4)).GetOpenCVType(), L"CV_8SC4 has wrong type");
			Assert::AreEqual((int)CV_16SC4, (int)anvil::Type(anvil::Type::FromOpenCVType(CV_16SC4)).GetOpenCVType(), L"CV_16SC4 has wrong type");
			Assert::AreEqual((int)CV_16UC4, (int)anvil::Type(anvil::Type::FromOpenCVType(CV_16UC4)).GetOpenCVType(), L"CV_16UC4 has wrong type");
			Assert::AreEqual((int)CV_32SC4, (int)anvil::Type(anvil::Type::FromOpenCVType(CV_32SC4)).GetOpenCVType(), L"CV_32SC4 has wrong type");
			Assert::AreEqual((int)CV_32FC4, (int)anvil::Type(anvil::Type::FromOpenCVType(CV_32FC4)).GetOpenCVType(), L"CV_32FC4 has wrong type");
			Assert::AreEqual((int)CV_64FC4, (int)anvil::Type(anvil::Type::FromOpenCVType(CV_64FC4)).GetOpenCVType(), L"CV_64FC4 has wrong type");
		}
	};


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
				FillImage(r, Vector(0, r.GetType()));
				Image g = img.GetChannel(1);
				FillImage(g, Vector(1, g.GetType()));
				Image b = img.GetChannel(2);
				FillImage(b, Vector(2, b.GetType()));
				Image a = img.GetChannel(3);
				FillImage(a, Vector(3, a.GetType()));

				Assert::AreEqual(img.GetData(), r.GetData(), L"R image data should start at the same location as the RGBA source image");
				Assert::AreEqual(static_cast<uint8_t*>(r.GetData()) + 1, static_cast<uint8_t*>(g.GetData()), L"G image data should start at R + 1");
				Assert::AreEqual(static_cast<uint8_t*>(r.GetData()) + 2, static_cast<uint8_t*>(b.GetData()), L"B image data should start at R + 2");
				Assert::AreEqual(static_cast<uint8_t*>(r.GetData()) + 3, static_cast<uint8_t*>(a.GetData()), L"A image data should start at R + 3");

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
				Assert::Fail(STR2WSTR(e.what()).c_str());
			}
		}	

		TEST_METHOD(EqualsOperator)
		{
			try {
				// Create a random image
				Image a(ANVIL_8UX1, 64, 64);
				Image b(ANVIL_8UX1, 64, 64);
				size_t s = 64 * 64;
				{
					uint8_t* adata = (uint8_t*)a.GetData();
					uint8_t* bdata = (uint8_t*)b.GetData();
					for (size_t i = 0u; i < s; ++i) {
						adata[i] = rand() % 256;
						bdata[i] = adata[i];
					}
				}

				Assert::IsTrue(a == b, L"Comparing two equal images returned false");

				FillImage(b, Vector(0, b.GetType()));

				Assert::IsFalse(a == b, L"Comparing two different images return true");

			} catch (std::runtime_error& e) {
				Assert::Fail(STR2WSTR(e.what()).c_str());
			}
		}
		TEST_METHOD(Transpose)
		{
			try {
				// Create a random image
				Image a(ANVIL_8UX1, 64, 64);
				size_t s = 64 * 64;
				{
					uint8_t* data = (uint8_t*) a.GetData();
					for (size_t i = 0u; i < s; ++i) data[i] = rand() % 256;
				}

				// Check that the transposed image is correct
				Image b = a.Transpose();
				for (size_t y = 0; y < 64; ++y) {
					for (size_t x = 0; x < 64; ++x) {
						Vector a_pixel, b_pixel;
						a.ReadPixel(x, y, a_pixel);
						b.ReadPixel(y, x, b_pixel);
						Assert::IsTrue(a_pixel == b_pixel, L"Pixel value in transposed image was not as expected");
					}
				}

				// Check if transposing it back produces an identical image to the original
				b = b.Transpose();
				Assert::IsTrue(a == b, L"Double transposed image is not equal the the original");
			} catch (std::runtime_error& e) {
				Assert::Fail(STR2WSTR(e.what()).c_str());
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
		float RoundFloat(float x, int n)
		{
			std::stringstream ss;
			ss << std::scientific << std::setprecision(n - 1) << x;
			return stod(ss.str());
		}

		template<class T>
		static std::wstring GetTestOperationName(ArithmeticOperations& op, const std::wstring fn_name) {
			return STR2WSTR(typeid(op).name())+ L"::" + std::wstring(fn_name) + L" (" + STR2WSTR(typeid(T).name()) + L") : ";
		}

		template<class T, size_t SIZE>
		void TestOperation(
			T a_val, T expected_result,
			ArithmeticOperations* operations,

			void(ArithmeticOperations::* unmasked_operation)(const void* src, void* dst, size_t count) const,
			void(ArithmeticOperations::* masked_operation)(const void* src, void* dst, size_t count, const uint8_t* mask) const,
			const wchar_t* name
		) {
			T a[SIZE];
			T out[SIZE];

			for (T& val : a) val = a_val;

			std::wstring test_name = GetTestOperationName<T>(*operations, name);

			if (unmasked_operation) {
				(operations->*unmasked_operation)(a, out, SIZE);
				for (uint32_t i = 0u; i < SIZE; ++i) {
					Assert::AreEqual(
						RoundFloat(expected_result, 3),
						RoundFloat(out[i], 3),
						(test_name + L"Output value was wrong").c_str()
					);
				}
				memset(out, 0, sizeof(out));
			}

			if (masked_operation) {
				for (uint32_t m = 0u; m < 16u; ++m) {
					(operations->*masked_operation)(a, out, SIZE, reinterpret_cast<uint8_t*>(&m));
					uint32_t flag = 1u;
					for (uint32_t i = 0u; i < SIZE; ++i) {
						Assert::AreEqual(
							RoundFloat((m & flag ? expected_result : a_val), 3),
							RoundFloat(out[i], 3),
							(test_name + L"Mask output was wrong. Mask = " + STR2WSTR(std::bitset<SIZE>(m).to_string()) + L" Index = " + std::to_wstring(i)).c_str()
						);
						flag <<= 1u;
					}
					memset(out, 0, sizeof(out));
				}
			}
		}

		template<class T, size_t SIZE>
		void TestOperation(
			T a_val, T b_val, T expected_result,
			ArithmeticOperations* operations,

			void(ArithmeticOperations::* unmasked_operation)(const void* lhs, const void* rhs, void* dst, size_t count) const,
			void(ArithmeticOperations::* masked_operation)(const void* lhs, const void* rhs, void* dst, size_t count, const uint8_t* mask) const,
			const wchar_t* name
		) {
			T a[SIZE];
			T b[SIZE];
			T out[SIZE];

			for (T& val : a) val = a_val;
			for (T& val : b) val = b_val;

			std::wstring test_name = GetTestOperationName<T>(*operations, name);

			if (unmasked_operation) {
				(operations->*unmasked_operation)(a, b, out, SIZE);
				for (uint32_t i = 0u; i < SIZE; ++i) {
					Assert::AreEqual(
						RoundFloat(expected_result, 3),
						RoundFloat(out[i], 3),
						(test_name + L"Output value was wrong").c_str()
					);
				}
				memset(out, 0, sizeof(out));
			}

			if (masked_operation) {
				for (uint32_t m = 0u; m < 16u; ++m) {
					(operations->*masked_operation)(a, b, out, SIZE, reinterpret_cast<uint8_t*>(&m));
					uint32_t flag = 1u;
					for (uint32_t i = 0u; i < SIZE; ++i) {
						Assert::AreEqual(
							RoundFloat((m & flag ? expected_result : a_val), 3),
							RoundFloat(out[i],3),
							(test_name + L"Mask output was wrong. Mask = " + STR2WSTR(std::bitset<SIZE>(m).to_string()) + L" Index = " + std::to_wstring(i)).c_str()
						);
						flag <<= 1u;
					}
					memset(out, 0, sizeof(out));
				}
			}
		}

		template<class T, size_t SIZE = 4u>
		void _TestMasking(ArithmeticOperations* operations) {
			try {
				// Test doesnt work on mask because it returns the rhs on 0
				//TestOperation<T, SIZE>(
				//	1.f, 2.f, 1.f,
				//	operations,
				//	nullptr,
				//	&ArithmeticOperations::Mask,
				//	L"Mask"
				//);

				TestOperation<T, SIZE>(
					1.5f, 2.f,
					operations,
					&ArithmeticOperations::Round,
					&ArithmeticOperations::Round,
					L"Round"
				);

				TestOperation<T, SIZE>(
					1.5f, 1.f,
					operations,
					&ArithmeticOperations::Floor,
					&ArithmeticOperations::Floor,
					L"Floor"
				);

				TestOperation<T, SIZE>(
					1.3f, 2.f,
					operations,
					&ArithmeticOperations::Ceil,
					&ArithmeticOperations::Ceil,
					L"Ceil"
				);

				TestOperation<T, SIZE>(
					500.f, std::sqrtf(500.f),
					operations,
					&ArithmeticOperations::Sqrt,
					&ArithmeticOperations::Sqrt,
					L"Sqrt"
				);

				TestOperation<T, SIZE>(
					500.f, std::cbrtf(500.f),
					operations,
					&ArithmeticOperations::Cbrt,
					&ArithmeticOperations::Cbrt,
					L"Cbrt"
				);

				TestOperation<T, SIZE>(
					1.f, 2.f, 1.f + 2.f,
					operations,
					&ArithmeticOperations::Add,
					&ArithmeticOperations::Add,
					L"Add"
				);

				TestOperation<T, SIZE>(
					4.f, 1.f, 4.f - 1.f,
					operations,
					&ArithmeticOperations::Subtract,
					&ArithmeticOperations::Subtract,
					L"Subtract"
				);

				TestOperation<T, SIZE>(
					3.f, 2.f, 3.f * 2.f,
					operations,
					&ArithmeticOperations::Multiply,
					&ArithmeticOperations::Multiply,
					L"Multiply"
				);

				TestOperation<T, SIZE>(
					6.f, 2.f, 6.f / 2.f,
					operations,
					&ArithmeticOperations::Divide,
					&ArithmeticOperations::Divide,
					L"Divide"
				);

				TestOperation<T, SIZE>(
					6.f, 2.f, 2.f,
					operations,
					&ArithmeticOperations::Minimum,
					&ArithmeticOperations::Minimum,
					L"Minimum"
				);

				TestOperation<T, SIZE>(
					6.f, 2.f, 6.f,
					operations,
					&ArithmeticOperations::Maximum,
					&ArithmeticOperations::Maximum,
					L"Maximum"
				);

				TestOperation<T, SIZE>(
					6.f, 2.f, std::hypotf(6.f, 2.f),
					operations,
					&ArithmeticOperations::Hypotenuse,
					&ArithmeticOperations::Hypotenuse,
					L"Hypotenuse"
				);
			
			} catch (std::exception& e) {
				Assert::Fail(STR2WSTR(e.what()).c_str());
			}
		}

		void TestMasking(uint64_t instruction_set) {
			ArithmeticOperations* operations = nullptr;
				
			operations = ArithmeticOperations::GetArithmeticOperations(ANVIL_64FX1, instruction_set);
			Assert::IsNotNull(operations, L"No operations implementation detected (F64)");
			_TestMasking<double>(operations);

			operations = ArithmeticOperations::GetArithmeticOperations(ANVIL_32FX1, instruction_set);
			Assert::IsNotNull(operations, L"No operations implementation detected (F32)");
			_TestMasking<float>(operations);

			operations = ArithmeticOperations::GetArithmeticOperations(ANVIL_16FX1, instruction_set);
			Assert::IsNotNull(operations, L"No operations implementation detected (F16)");
			_TestMasking<float16_t>(operations);
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
