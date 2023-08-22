#include "CppUnitTest.h"
#include "anvil/Core.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace anvil { namespace core {

	TEST_CLASS(CRC)
	{
	public:

		template<class CRC>
		static void TestCRC(typename CRC::checksum_t expected_result) {
			const char* src = "123456789";
			size_t bytes = static_cast<size_t>(strlen(src));
			typename CRC::checksum_t result = CRC::calculate(src, bytes);
			Assert::AreEqual(expected_result, result);
		}

		TEST_METHOD(crc_8)				{ TestCRC<anvil::crc_8>(0xF4); }
		TEST_METHOD(crc_8_darc)			{ TestCRC<anvil::crc_8_darc>(0x15); }
		TEST_METHOD(crc_8_i_code)		{ TestCRC<anvil::crc_8_i_code>(0x7E); }
		TEST_METHOD(crc_8_itu)			{ TestCRC<anvil::crc_8_itu>(0xA1); }
		TEST_METHOD(crc_8_maxim)		{ TestCRC<anvil::crc_8_maxim>(0xA1); }
		TEST_METHOD(crc_8_rohc)			{ TestCRC<anvil::crc_8_rohc>(0xD0); }
		TEST_METHOD(crc_8_wcdma)		{ TestCRC<anvil::crc_8_wcdma>(0x25); }
		TEST_METHOD(crc_16)				{ TestCRC<anvil::crc_16>(0xBB3D); }
		TEST_METHOD(crc_16_buypass)		{ TestCRC<anvil::crc_16_buypass>(0xFEE8); }
		TEST_METHOD(crc_16_dds_110)		{ TestCRC<anvil::crc_16_dds_110>(0x9ECF); }
		TEST_METHOD(crc_16_dect)		{ TestCRC<anvil::crc_16_dect>(0x007E); }
		TEST_METHOD(crc_16_dnp)			{ TestCRC<anvil::crc_16_dnp>(0xEA82); }
		TEST_METHOD(crc_16_en_13757)	{ TestCRC<anvil::crc_16_en_13757>(0xC2B7); }
		TEST_METHOD(crc_16_genibus)		{ TestCRC<anvil::crc_16_genibus>(0xD64E); }
		TEST_METHOD(crc_16_maxim)		{ TestCRC<anvil::crc_16_maxim>(0x44C2); }
		TEST_METHOD(crc_16_mcrf4xx)		{ TestCRC<anvil::crc_16_mcrf4xx>(0x6F91); }
		TEST_METHOD(crc_16_riello)		{ TestCRC<anvil::crc_16_riello>(0x63D0); }
		TEST_METHOD(crc_16_t10_dif)		{ TestCRC<anvil::crc_16_t10_dif>(0xD0DB); }
		TEST_METHOD(crc_16_teledisk)	{ TestCRC<anvil::crc_16_teledisk>(0x0FB3); }
		TEST_METHOD(crc_16_usb)			{ TestCRC<anvil::crc_16_usb>(0xB4C8); }
		TEST_METHOD(crc_x_25)			{ TestCRC<anvil::crc_x_25>(0x906E); }
		TEST_METHOD(crc_xmodem)			{ TestCRC<anvil::crc_xmodem>(0x31C3); }
		TEST_METHOD(crc_modbus)			{ TestCRC<anvil::crc_modbus>(0x4B37); }
		TEST_METHOD(crc_kermit)			{ TestCRC<anvil::crc_kermit>(0x2189); }
		TEST_METHOD(crc_ccitt_false)	{ TestCRC<anvil::crc_ccitt_false>(0x29B1); }
		TEST_METHOD(crc_aug_ccitt)		{ TestCRC<anvil::crc_aug_ccitt>(0xE5CC); }
		TEST_METHOD(crc_24)				{ TestCRC<anvil::crc_24>(0x21CF02); }
		TEST_METHOD(crc_24_flexray_a)	{ TestCRC<anvil::crc_24_flexray_a>(0x7979BD); }
		TEST_METHOD(crc_24_flexray_b)	{ TestCRC<anvil::crc_24_flexray_b>(0x1F23B8); }
		TEST_METHOD(crc_32)				{ TestCRC<anvil::crc_32>(0xCBF43926); }
		TEST_METHOD(crc_32_bzip2)		{ TestCRC<anvil::crc_32_bzip2>(0xFC891918); }
		TEST_METHOD(crc_32c)			{ TestCRC<anvil::crc_32c>(0xE3069283); }
		TEST_METHOD(crc_32d)			{ TestCRC<anvil::crc_32d>(0x87315576); }
		TEST_METHOD(crc_32_mpeg)		{ TestCRC<anvil::crc_32_mpeg>(0x0376E6E7); }
		TEST_METHOD(crc_posix)			{ TestCRC<anvil::crc_posix>(0x765E7680); }
		TEST_METHOD(crc_32q)			{ TestCRC<anvil::crc_32q>(0x3010BF7F); }
		TEST_METHOD(crc_jamcrc)			{ TestCRC<anvil::crc_jamcrc>(0x340BC6D9); }
		TEST_METHOD(crc_xfer)			{ TestCRC<anvil::crc_xfer>(0xBD0BE338); }
		TEST_METHOD(crc_64)				{ TestCRC<anvil::crc_64>(0x46A5A9388A5BEFFEll); }
		TEST_METHOD(crc_64_we)			{ TestCRC<anvil::crc_64_we>(0x62EC59E3F1A4F00All); }
		TEST_METHOD(crc_64_jones)		{ TestCRC<anvil::crc_64_jones>(0xCAA717168609F281ll); }

	};

}}
