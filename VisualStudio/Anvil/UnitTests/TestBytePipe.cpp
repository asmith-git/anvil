#include "pch.h"
#include "CppUnitTest.h"
#include "anvil/Core.hpp"
#include "anvil/BytePipe.hpp"
#include <thread>
#include <vector>
#include <locale>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace anvil { namespace BytePipe {

	class DebugPipe final : public OutputPipe, public InputPipe {
	private:
		std::mutex _lock;
	public:
		std::deque<uint8_t> data;

		DebugPipe() {

		}

		virtual ~DebugPipe() {

		}

		void Flush() final {

		}
		
		size_t WriteBytes(const void* src, const size_t bytes) final {
			std::lock_guard<std::mutex> lock(_lock);
			const uint8_t* src8 = static_cast<const uint8_t*>(src); 
			
			for (size_t i = 0u; i < bytes; ++i) {
				data.push_back(src8[i]);
			}
			return bytes;
		}

		size_t ReadBytes(void* dst, const size_t bytes) final {
			if (bytes == 0u) return 0u;

			std::lock_guard<std::mutex> lock(_lock);
			if (bytes > data.size()) Assert::Fail(L"Tried to read more data than was written");

			size_t to_read = bytes;
			if (to_read > data.size()) to_read = data.size();
			uint8_t* dst8 = static_cast<uint8_t*>(dst);

			for (size_t i = 0u; i < to_read; ++i) {
				dst8[i] = data.front();
				data.pop_front();
			}

			return to_read;
		}
	};

	void WriteTest(anvil::BytePipe::OutputPipe& out, anvil::BytePipe::InputPipe& in, const void* src, size_t bytes, std::deque<uint8_t>& debug, bool split_writes, bool split_reads) {
		try {
			Assert::IsTrue(debug.empty(), L"Debug buffer started with data in it");

			// Break into random sized writes
			if(split_writes) {
				size_t bytes_left = bytes;
				const uint8_t* src8 = static_cast<const uint8_t*>(src);
				while (bytes_left) {
					size_t bytes_to_write = bytes_left < 10 ? bytes_left: rand() % bytes_left;
					out.WriteBytesFast(src8, bytes_to_write, 10000);
					bytes_left -= bytes_to_write;
					src8 += bytes_to_write;
				}
			} else {
				out.WriteBytesFast(src, bytes, 10000);
			}
			out.Flush();

			uint8_t* buffer = new uint8_t[bytes];

			// Break into random sized reads
			if(split_reads) {
				size_t bytes_left = bytes;
				uint8_t* buffer2 = buffer;
				while (bytes_left) {
					size_t bytes_to_write = bytes_left < 10 ? bytes_left : rand() % bytes_left;
					in.ReadBytesFast(buffer2, bytes_to_write, 10000);
					bytes_left -= bytes_to_write;
					buffer2 += bytes_to_write;
				}
			} else {
				in.ReadBytesFast(buffer, bytes, 10000);
			}

			Assert::IsTrue(debug.empty(), L"Data was left over in the buffer");
			Assert::IsTrue(std::memcmp(buffer, src, bytes) == 0, L"Memory read did not match what was written");

			delete[] buffer;

		} catch (std::exception& e) {
			Assert::Fail(std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>>().from_bytes(e.what()).c_str());
		} catch (...) {
			Assert::Fail(L"Caught something that wasn't a std::exception");
		}
	}

	void RandomWriteTest(anvil::BytePipe::OutputPipe& out, anvil::BytePipe::InputPipe& in, std::deque<uint8_t>& debug) {
		//WriteTest(out, in, nullptr, 0, debug, false, false);

		//{
		//	uint32_t buffer = 12345678u;
		//	WriteTest(out, in, &buffer, sizeof(buffer), debug, false, false);
		//}

		enum { MAX_TEST_LEN = 100000 };
		uint8_t rnd[MAX_TEST_LEN];
		for(uint8_t& r : rnd) r = (uint8_t)rand() % 255;

		uint8_t rle[MAX_TEST_LEN];
		memset(rle, 128, MAX_TEST_LEN);

		uint8_t non_rle[MAX_TEST_LEN];
		for (size_t j = 0u; j < MAX_TEST_LEN; ++j) rle[j] = (uint8_t)(j % 255);

		for (size_t i = 0; i < 4000; ++i) {
			size_t bytes = rand() % MAX_TEST_LEN;

			// Always RLE
			WriteTest(out, in, rle, bytes, debug, false, false);
			WriteTest(out, in, rle, bytes, debug, true, true);

			// NeverRLE
			WriteTest(out, in, non_rle, bytes, debug, false, false);
			WriteTest(out, in, non_rle, bytes, debug, true, true);

			// Random
			WriteTest(out, in, rnd, bytes, debug, false, false);
			WriteTest(out, in, rnd, bytes, debug, true, true);
		}
	}

	TEST_CLASS(DebugPipeTest)
	{
	public:
		TEST_METHOD(SanityCheck)
		{
			DebugPipe debug_pipe;

			RandomWriteTest(debug_pipe, debug_pipe, debug_pipe.data);
		}
	};

	TEST_CLASS(PacketPipe)
	{
	public:
		TEST_METHOD(BasicFixedSize)
		{
			{
				DebugPipe debug_pipe;

				PacketInputPipe in(debug_pipe);
				PacketOutputPipe out(debug_pipe, 1u, true);

				RandomWriteTest(out, in, debug_pipe.data);
			}
			{
				DebugPipe debug_pipe;

				PacketInputPipe in(debug_pipe);
				PacketOutputPipe out(debug_pipe, 111u, true);

				RandomWriteTest(out, in, debug_pipe.data);
			}
			{
				DebugPipe debug_pipe;

				PacketInputPipe in(debug_pipe);
				PacketOutputPipe out(debug_pipe, 1024u, true);

				RandomWriteTest(out, in, debug_pipe.data);
			}
			{
				DebugPipe debug_pipe;

				PacketInputPipe in(debug_pipe);
				PacketOutputPipe out(debug_pipe, 4096u, true);

				RandomWriteTest(out, in, debug_pipe.data);
			}
			{
				DebugPipe debug_pipe;

				PacketInputPipe in(debug_pipe);
				PacketOutputPipe out(debug_pipe, 1048576u, true);

				RandomWriteTest(out, in, debug_pipe.data);
			}
			{
				DebugPipe debug_pipe;

				PacketInputPipe in(debug_pipe);
				PacketOutputPipe out(debug_pipe, 1048576u * 10, true);

				RandomWriteTest(out, in, debug_pipe.data);
			}
		}
		TEST_METHOD(BasicVariableSize)
		{
			{
				DebugPipe debug_pipe;

				PacketInputPipe in(debug_pipe);
				PacketOutputPipe out(debug_pipe, 1u, false);

				RandomWriteTest(out, in, debug_pipe.data);
			}
			{
				DebugPipe debug_pipe;

				PacketInputPipe in(debug_pipe);
				PacketOutputPipe out(debug_pipe, 111u, false);

				RandomWriteTest(out, in, debug_pipe.data);
			}
			{
				DebugPipe debug_pipe;

				PacketInputPipe in(debug_pipe);
				PacketOutputPipe out(debug_pipe, 1024u, false);

				RandomWriteTest(out, in, debug_pipe.data);
			}
			{
				DebugPipe debug_pipe;

				PacketInputPipe in(debug_pipe);
				PacketOutputPipe out(debug_pipe, 4096u, false);

				RandomWriteTest(out, in, debug_pipe.data);
			}
			{
				DebugPipe debug_pipe;

				PacketInputPipe in(debug_pipe);
				PacketOutputPipe out(debug_pipe, 1048576u, false);

				RandomWriteTest(out, in, debug_pipe.data);
			}
			{
				DebugPipe debug_pipe;

				PacketInputPipe in(debug_pipe);
				PacketOutputPipe out(debug_pipe, 1048576u * 10, false);

				RandomWriteTest(out, in, debug_pipe.data);
			}
		}

		TEST_METHOD(NestedFixedSize)
		{
			{
				DebugPipe debug_pipe;

				PacketInputPipe in1(debug_pipe);
				PacketInputPipe in2(in1);
				PacketInputPipe in3(in2);
				PacketOutputPipe out1(debug_pipe, 1500, true);
				PacketOutputPipe out2(out1, 8000, true);
				PacketOutputPipe out3(out2, 2048, true);

				RandomWriteTest(out3, in3, debug_pipe.data);
			}
		}

		TEST_METHOD(NestedVariableSize)
		{
			{
				DebugPipe debug_pipe;

				PacketInputPipe in1(debug_pipe);
				PacketInputPipe in2(in1);
				PacketInputPipe in3(in2);
				PacketOutputPipe out1(debug_pipe, 1500, false);
				PacketOutputPipe out2(out1, 8000, false);
				PacketOutputPipe out3(out2, 2048, false);

				RandomWriteTest(out3, in3, debug_pipe.data);
			}
		}
	};

	TEST_CLASS(RLEPipe)
	{
	public:
		TEST_METHOD(Index8Word8)
		{
			{
				DebugPipe debug_pipe;

				typedef uint8_t RLEIndex;
				typedef uint8_t RLEWord;

				RLEDecoderPipe<RLEIndex, RLEWord> in(debug_pipe);
				RLEEncoderPipe<RLEIndex, RLEWord> out(debug_pipe);

				RandomWriteTest(out, in, debug_pipe.data);
			}
		}

		TEST_METHOD(Index16Word8)
		{
			{
				DebugPipe debug_pipe;

				typedef uint16_t RLEIndex;
				typedef uint8_t RLEWord;

				RLEDecoderPipe<RLEIndex, RLEWord> in(debug_pipe);
				RLEEncoderPipe<RLEIndex, RLEWord> out(debug_pipe);

				RandomWriteTest(out, in, debug_pipe.data);
			}
		}

		TEST_METHOD(Index8Word16)
		{
			{
				DebugPipe debug_pipe;

				typedef uint8_t RLEIndex;
				typedef uint16_t RLEWord;

				RLEDecoderPipe<RLEIndex, RLEWord> in(debug_pipe);
				RLEEncoderPipe<RLEIndex, RLEWord> out(debug_pipe);

				RandomWriteTest(out, in, debug_pipe.data);
			}
		}

		TEST_METHOD(Index16Word16)
		{
			{
				DebugPipe debug_pipe;

				typedef uint16_t RLEIndex;
				typedef uint16_t RLEWord;

				RLEDecoderPipe<RLEIndex, RLEWord> in(debug_pipe);
				RLEEncoderPipe<RLEIndex, RLEWord> out(debug_pipe);

				RandomWriteTest(out, in, debug_pipe.data);
			}
		}

		TEST_METHOD(Index8Word32)
		{
			{
				DebugPipe debug_pipe;

				typedef uint8_t RLEIndex;
				typedef uint32_t RLEWord;

				RLEDecoderPipe<RLEIndex, RLEWord> in(debug_pipe);
				RLEEncoderPipe<RLEIndex, RLEWord> out(debug_pipe);

				RandomWriteTest(out, in, debug_pipe.data);
			}
		}

		TEST_METHOD(Index16Word32)
		{
			{
				DebugPipe debug_pipe;

				typedef uint16_t RLEIndex;
				typedef uint32_t RLEWord;

				RLEDecoderPipe<RLEIndex, RLEWord> in(debug_pipe);
				RLEEncoderPipe<RLEIndex, RLEWord> out(debug_pipe);

				RandomWriteTest(out, in, debug_pipe.data);
			}
		}

		TEST_METHOD(Index8Word64)
		{
			{
				DebugPipe debug_pipe;

				typedef uint8_t RLEIndex;
				typedef uint64_t RLEWord;

				RLEDecoderPipe<RLEIndex, RLEWord> in(debug_pipe);
				RLEEncoderPipe<RLEIndex, RLEWord> out(debug_pipe);

				RandomWriteTest(out, in, debug_pipe.data);
			}
		}
		TEST_METHOD(Index16Word64)
		{
			{
				DebugPipe debug_pipe;

				typedef uint16_t RLEIndex;
				typedef uint64_t RLEWord;

				RLEDecoderPipe<RLEIndex, RLEWord> in(debug_pipe);
				RLEEncoderPipe<RLEIndex, RLEWord> out(debug_pipe);

				RandomWriteTest(out, in, debug_pipe.data);
			}
		}

		TEST_METHOD(Index32Word8)
		{
			{
				DebugPipe debug_pipe;

				typedef uint32_t RLEIndex;
				typedef uint8_t RLEWord;

				RLEDecoderPipe<RLEIndex, RLEWord> in(debug_pipe);
				RLEEncoderPipe<RLEIndex, RLEWord> out(debug_pipe);

				RandomWriteTest(out, in, debug_pipe.data);
			}
		}

		TEST_METHOD(Index32Word16)
		{
			{
				DebugPipe debug_pipe;

				typedef uint32_t RLEIndex;
				typedef uint16_t RLEWord;

				RLEDecoderPipe<RLEIndex, RLEWord> in(debug_pipe);
				RLEEncoderPipe<RLEIndex, RLEWord> out(debug_pipe);

				RandomWriteTest(out, in, debug_pipe.data);
			}
		}

		TEST_METHOD(Index32Word32)
		{
			{
				DebugPipe debug_pipe;

				typedef uint32_t RLEIndex;
				typedef uint32_t RLEWord;

				RLEDecoderPipe<RLEIndex, RLEWord> in(debug_pipe);
				RLEEncoderPipe<RLEIndex, RLEWord> out(debug_pipe);

				RandomWriteTest(out, in, debug_pipe.data);
			}
		}

		TEST_METHOD(Index32Word64)
		{
			{
				DebugPipe debug_pipe;

				typedef uint32_t RLEIndex;
				typedef uint64_t RLEWord;

				RLEDecoderPipe<RLEIndex, RLEWord> in(debug_pipe);
				RLEEncoderPipe<RLEIndex, RLEWord> out(debug_pipe);

				RandomWriteTest(out, in, debug_pipe.data);
			}
		}

		TEST_METHOD(Index64Word8)
		{
			{
				DebugPipe debug_pipe;

				typedef uint64_t RLEIndex;
				typedef uint8_t RLEWord;

				RLEDecoderPipe<RLEIndex, RLEWord> in(debug_pipe);
				RLEEncoderPipe<RLEIndex, RLEWord> out(debug_pipe);

				RandomWriteTest(out, in, debug_pipe.data);
			}
		}

		TEST_METHOD(Index64Word16)
		{
			{
				DebugPipe debug_pipe;

				typedef uint64_t RLEIndex;
				typedef uint16_t RLEWord;

				RLEDecoderPipe<RLEIndex, RLEWord> in(debug_pipe);
				RLEEncoderPipe<RLEIndex, RLEWord> out(debug_pipe);

				RandomWriteTest(out, in, debug_pipe.data);
			}
		}

		TEST_METHOD(Index64Word32)
		{
			{
				DebugPipe debug_pipe;

				typedef uint64_t RLEIndex;
				typedef uint32_t RLEWord;

				RLEDecoderPipe<RLEIndex, RLEWord> in(debug_pipe);
				RLEEncoderPipe<RLEIndex, RLEWord> out(debug_pipe);

				RandomWriteTest(out, in, debug_pipe.data);
			}
		}

		TEST_METHOD(Index64Word64)
		{
			{
				DebugPipe debug_pipe;

				typedef uint64_t RLEIndex;
				typedef uint64_t RLEWord;

				RLEDecoderPipe<RLEIndex, RLEWord> in(debug_pipe);
				RLEEncoderPipe<RLEIndex, RLEWord> out(debug_pipe);

				RandomWriteTest(out, in, debug_pipe.data);
			}
		}
	};
}}
