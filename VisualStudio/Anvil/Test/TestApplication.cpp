#include <iostream>
#include <bitset>
#include <fstream>
#include <chrono>
#include "anvil/Core.hpp"
//#include "anvil/Compute.hpp"
#include "anvil/BytePipe.hpp"
#include "anvil/byte-pipe/BytePipeJSON.hpp"
#include "anvil/Console.hpp"
#include "anvil/RPC.hpp"
#include "anvil/Scheduling.hpp"
#include "anvil/Compute.hpp"

static uint64_t CurrentTime() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
		).count();
}

class DebugPipe : public anvil::BytePipe::InputPipe, public anvil::BytePipe::OutputPipe {
private:
	std::mutex _lock;
public:
	std::deque<uint8_t> buffer;
	size_t bytes_written;
	size_t bytes_read;

	DebugPipe() {
		bytes_written = 0;
		bytes_read = 0;
	}

	virtual ~DebugPipe() {

	}

	size_t ReadBytes(void* dst, const size_t bytes) final {
		if (bytes == 0u) return 0u;

		std::lock_guard<std::mutex> lock(_lock);
		if (bytes > buffer.size()) throw std::runtime_error("Tried to read more data than was written");

		size_t to_read = buffer.size();
		if (to_read > bytes) to_read = bytes;
		for (size_t i = 0u; i < to_read; ++i) {
			static_cast<uint8_t*>(dst)[i] = buffer.front();
			buffer.pop_front();
		}
		bytes_read += to_read;
		return to_read;
	}

	size_t WriteBytes(const void* src, const size_t bytes) final {
		std::lock_guard<std::mutex> lock(_lock);
		for (size_t i = 0u; i < bytes; ++i) buffer.push_back(static_cast<const uint8_t*>(src)[i]);
		bytes_written += bytes;
		return bytes;
	}

	void Flush() final {

	}
};

void SchedulerTest() {
	using namespace anvil;

	class QuadTreeTask : public Task {
	public:
		enum {
			SQUARE_MODE = 0
		};
		std::atomic_uint32_t* counter;
		int8_t* data;
		size_t data_w;
		size_t data_h;
		size_t my_x;
		size_t my_y;
		size_t my_w;
		size_t my_h;

	private:
		bool ShouldSplit() const {
			if (SQUARE_MODE) {
				if (my_w <= 1u || my_h <= 1u) return false;
				if (my_w & 1u || my_h & 1u) return false;
			} else {
				if (my_h < 4u) return false;
				if ((my_h % 4) != 0) return false;
			}
			//if (GetScheduler().GetSleepingThreadCount() == 0u) return false;
			//if (GetNestingDepth() >= 6) return false;
			//if (std::pow(4, GetNestingDepth()) >= GetScheduler().GetSleepingThreadCount()) return false;
			if (std::pow(4, GetNestingDepth()) >= GetScheduler().GetThreadCount()) return false;

			return true;
		}

	protected:

		void OnExecution() final {
			try {
				if (ShouldSplit()) {
					QuadTreeTask children[4u];
					for (QuadTreeTask& c : children) {
						c.counter = counter;
						c.data = data;
						c.data_w = data_w;
						c.data_h = data_h;
						if (SQUARE_MODE) {
							c.my_w = my_w / 2;
							c.my_h = my_h / 2;
						} else {
							c.my_w = my_w;
							c.my_h = my_h / 4;
						}
						c.my_x = my_x;
						c.my_y = my_y;
					}

					if (SQUARE_MODE) {
						children[1].my_x += children[1].my_w;
						children[2].my_y += children[2].my_h;
						children[3].my_x += children[3].my_w;
						children[3].my_y += children[3].my_h;
					} else {
						children[1].my_y += children[1].my_h;
						children[2].my_y += children[2].my_h * 2;
						children[3].my_y += children[3].my_h * 3;
					}

					GetScheduler().Schedule(children, 4u);

					for (QuadTreeTask& c : children) c.Wait();

				}
				else {
					const size_t end_x = my_x + my_w;
					const size_t end_y = my_y + my_h;
					for (size_t y = my_y; y < end_y; ++y) {
						for (size_t x = my_x; x < end_x; ++x) {
							if (data[y * data_w + x] & 1)++*counter;
						}
					}
				}
			} catch (std::exception& e) {
				std::cerr << e.what() << std::endl;
			} catch (...) {
				std::cerr << "Unspecified error" << std::endl;
			}
		}

	public:

		QuadTreeTask() :
			counter(nullptr),
			data(nullptr),
			data_w(0u),
			data_h(0u),
			my_x(0u),
			my_y(0u),
			my_w(0u),
			my_h(0u)
		{}

		virtual ~QuadTreeTask() {

		}
	};

	{
		Console console;
		ExampleSchedulerMultiThreaded scheduler(8u);
		//scheduler.SetExecutionOnTaskWait(false);
		//ExampleSchedulerSingleThreaded scheduler;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		{
			std::atomic_uint32_t counter = 0u;
			enum { size = 1024 * 18 };
			int8_t* data = new int8_t[size * size];

			uint32_t real_counter = 0u;
			{
				int8_t tmp = 0;
				for (size_t i = 0u; i < (size * size); ++i) {
					//tmp = rand() % INT8_MAX;
					if (tmp & 1) ++real_counter;
					data[i] = tmp++;
				}
			}

			uint64_t t1 = 0u;

			std::thread console_thread([&]()->void{
				SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);

				const auto pos = console.GetCursorLocation();
				while (true) {
					console.SetCursorLocation(pos);
					console.ClearLine();
					console.Print("Real count : \t\t" + std::to_string(real_counter) + '\n');
					console.ClearLine();
					console.Print("Tasks counted : \t" + std::to_string(counter) + '\n');
					console.ClearLine();
					uint64_t t2 = CurrentTime();
					console.Print("Time : " + std::to_string(t2 - t1) + " ms\n");
					console.EndLine();
					console.ClearLine();

					for (size_t i = 0u; i < scheduler.GetThreadCount(); ++i) {
						Scheduler::ThreadDebugData* debug_data = scheduler.GetDebugDataForThread(i);
						console.Print("Thread[" + std::to_string(i) + "] : ");
						if (debug_data->enabled == 0u) {
							console.Print("disabled " + std::to_string(debug_data->tasks_executing), CONSOLE_RED_LIGHT);
						}
						else if (debug_data->sleeping) {
							console.Print("sleeping " + std::to_string(debug_data->tasks_executing), CONSOLE_YELLOW_LIGHT);
						}
						else {
							console.Print("executing " + std::to_string(debug_data->tasks_executing), CONSOLE_GREEN_LIGHT);
						}
						console.EndLine();
						console.ClearLine();
					}
					std::this_thread::sleep_for(std::chrono::milliseconds(15));
				}
			});

			while(true) {
				t1 = CurrentTime();
				counter = 0u;

				QuadTreeTask root;
				root.counter = &counter;
				root.data_w = size;
				root.data_h = size;
				root.my_x = 0u;
				root.my_y = 0u;
				root.my_w = root.data_w;
				root.my_h = root.data_h;
				root.data = data;

				scheduler.Schedule(root);

				std::this_thread::sleep_for(std::chrono::milliseconds(300));
				root.Wait();
				std::this_thread::sleep_for(std::chrono::milliseconds(300));

				if (counter != real_counter)
					throw std::runtime_error("Tasks did not execute correctly");
			}
		}
	}

	system("pause");
}

void EncodeOptimise() {
	enum {s = 4096 * 1024 };
	uint8_t* src = new uint8_t[s];
	char* dst = new char[s * 1.5];

	size_t src_out;
	size_t dst_out;

	uint64_t t = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	anvil::Base64::Encode(src, s, dst, dst_out);
	uint64_t t2 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	anvil::Base64::Decode(dst, dst_out, src, src_out);

	uint64_t t3 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	std::cout  << "Encode : " << static_cast<double>(t2 - t) / 1000.0 << std::endl;
	std::cout << "Decode : " << static_cast<double>(t3 - t2) / 1000.0 << std::endl;

	delete[] src;
	delete[] dst;
}

static void Base64Test() {
	const char* src = "hello base64!";
	size_t src_len = strlen(src);
	std::cout << src << std::endl;

	size_t b64_len;
	char base64[512];
	anvil::Base64::Encode(reinterpret_cast<const uint8_t*>(src), src_len, base64, b64_len);
	std::cout << base64 << std::endl;

	size_t decode_len;
	char decode[512];
	anvil::Base64::Decode(base64, b64_len, reinterpret_cast<uint8_t*>(decode), decode_len);
	decode[decode_len] = '\0';
	std::cout << decode << std::endl;
}

static void RPCTest() {
	using namespace anvil;

	RPC::Server server;
	RPC::ServerJsonTCP server_connect(server, 1234);

	server.AddMethod("echo", [](const BytePipe::Value& value)->BytePipe::Value {
		return value;
	});

	BytePipe::IPAddress ip;
	ip.u8[0u] = 127;
	ip.u8[1u] = 0;
	ip.u8[2u] = 0;
	ip.u8[3u] = 1;
	RPC::ClientJsonTCP client(ip, 1234);

	std::cout << *client.SendRequest("echo", BytePipe::Value("hello RPC")).Get<std::string>() << std::endl;
}

static void UDPTest() {

	int port = 1234;

	std::thread server([port]()->void {
		anvil::BytePipe::UDPInputPipe pipe(port);

		for (int i = 0; i < 100; ++i) {
			int j = 0;
			pipe.ReadBytesFast(&j, sizeof(j));
			std::cout << j << std::endl;
		}
	});

	std::thread client([port]()->void {
		anvil::BytePipe::IPAddress ip;
		ip.u8[0] = 127;
		ip.u8[1] = 0;
		ip.u8[2] = 0;
		ip.u8[3] = 1;

		anvil::BytePipe::UDPOutputPipe pipe(ip, port);

		for (int i = 0; i < 100; ++i) {
			pipe.WriteBytesFast(&i, sizeof(i));
		}
	});

	client.join();
	server.join();
}

static void TCPTest() {

	int port = 1234;

	DebugPipe debugpipe;

	std::thread server([port, &debugpipe]()->void {
		std::unique_ptr<anvil::BytePipe::InputPipe>ipacketpipe1(new anvil::BytePipe::PacketInputPipe(debugpipe));
		std::unique_ptr<anvil::BytePipe::InputPipe>ipacketpipe2(new anvil::BytePipe::PacketInputPipe(*ipacketpipe1));

		//anvil::BytePipe::TCPServerPipe itcppipe(port);
		//anvil::BytePipe::PacketInputPipe ipacketpipe1(debugpipe);
		//anvil::BytePipe::PacketInputPipe ipacketpipe2(ipacketpipe1);
		//anvil::BytePipe::RLEDecoderPipe<> rlepipe(ipacketpipe2);
		anvil::BytePipe::InputPipe& ipipe = *ipacketpipe2;

		//ipacketpipe1->debug_name = "PacketPipe 1";
		//ipacketpipe2->debug_name = "PacketPipe 2";

		int count = 0;
		ipipe.ReadBytesFast(&count, sizeof(count));

		for (int i = 0; i < count; ++i) {
			int val = 0;
			ipipe.ReadBytesFast(&val, sizeof(val));
			std::cout << ("Server reading " + std::to_string(val) + "\n");
		}
	});

	std::thread client([port, &debugpipe]()->void {
		anvil::BytePipe::IPAddress ip;
		ip.u8[0] = 127;
		ip.u8[1] = 0;
		ip.u8[2] = 0;
		ip.u8[3] = 1;

		//anvil::BytePipe::TCPClientPipe otcppipe(ip, port);
		anvil::BytePipe::PacketOutputPipe opacketpipe1(debugpipe, 500, true);
		anvil::BytePipe::PacketOutputPipe opacketpipe2(opacketpipe1, 1000, true);
		//anvil::BytePipe::RLEEncoderPipe<> orlepipe(packetpipe2);

		anvil::BytePipe::OutputPipe& opipe = opacketpipe2;

		int count = 2000;
		opipe.WriteBytesFast(&count, sizeof(count));

		for (int i = 0; i < count; ++i) {
			int val = i;
			std::cout << ("Client writing " + std::to_string(val) + "\n");
			opipe.WriteBytesFast(&val, sizeof(val));
		}
		opipe.Flush();
	});

	client.join();
	server.join();
}

static void ConsoleTest() {
	using namespace anvil;

	Console test;
	test.Print("Black text\n", CONSOLE_BLACK);
	test.Print("D. Grey text\n", CONSOLE_GREY_DARK);
	test.Print("L. Grey text\n", CONSOLE_GREY_LIGHT);
	test.Print("White text\n", CONSOLE_WHITE);
	test.Print("L. Blue text\n", CONSOLE_BLUE_LIGHT);
	test.Print("L. Green text\n", CONSOLE_GREEN_LIGHT);
	test.Print("L. Cyan text\n", CONSOLE_CYAN_LIGHT);
	test.Print("L. Red text\n", CONSOLE_RED_LIGHT);
	test.Print("L. Magenta text\n", CONSOLE_MAGENTA_LIGHT);
	test.Print("L. Yellow text\n", CONSOLE_YELLOW_LIGHT);
	test.Print("D. Blue text\n", CONSOLE_BLUE_DARK);
	test.Print("D. Green text\n", CONSOLE_GREEN_DARK);
	test.Print("D. Cyan text\n", CONSOLE_CYAN_DARK);
	test.Print("D. Red text\n", CONSOLE_RED_DARK);
	test.Print("D. Magenta text\n", CONSOLE_MAGENTA_DARK);
	test.Print("D. Yellow text\n", CONSOLE_YELLOW_DARK);
	test.Print("Black background\n", CONSOLE_BLACK, CONSOLE_BLACK);
	test.Print("D. Grey background\n", CONSOLE_BLACK, CONSOLE_GREY_DARK);
	test.Print("L. Grey background\n", CONSOLE_BLACK, CONSOLE_GREY_LIGHT);
	test.Print("White background\n", CONSOLE_BLACK, CONSOLE_WHITE);
	test.Print("L. Blue background\n", CONSOLE_BLACK, CONSOLE_BLUE_LIGHT);
	test.Print("L. Green background\n", CONSOLE_BLACK, CONSOLE_GREEN_LIGHT);
	test.Print("L. Cyan background\n", CONSOLE_BLACK, CONSOLE_CYAN_LIGHT);
	test.Print("L. Red background\n", CONSOLE_BLACK, CONSOLE_RED_LIGHT);
	test.Print("L. Magenta background\n", CONSOLE_BLACK, CONSOLE_MAGENTA_LIGHT);
	test.Print("L. Yellow background\n", CONSOLE_BLACK, CONSOLE_YELLOW_LIGHT);
	test.Print("D. Blue background\n", CONSOLE_BLACK, CONSOLE_BLUE_DARK);
	test.Print("D. Green background\n", CONSOLE_BLACK, CONSOLE_GREEN_DARK);
	test.Print("D. Cyan background\n", CONSOLE_BLACK, CONSOLE_CYAN_DARK);
	test.Print("D. Red background\n", CONSOLE_BLACK, CONSOLE_RED_DARK);
	test.Print("D. Magenta background\n", CONSOLE_BLACK, CONSOLE_MAGENTA_DARK);
	test.Print("D. Yellow background\n", CONSOLE_BLACK, CONSOLE_YELLOW_DARK);

	std::this_thread::sleep_for(std::chrono::milliseconds(300));
	{
		test.Clear();
		float progress = 0.f;
		std::thread test_thread([&progress]()->void {
			while (progress < 100.f) {
				progress += 0.1f;
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
		});
		test.ProgressBar(progress);
		test_thread.join();
	}

	auto state = test.SaveState();
	test.Clear();
	test.LoadState(state);

	std::vector<std::string> choices = {"abc", "123", "hello world"};

	test.Clear();
	std::string msg = choices[test.InputChoice("Select a test message", choices)];
	//std::string msg = test.InputString("Enter a message");

	test.Print(msg, CONSOLE_BLACK);
	test.Print(msg, CONSOLE_GREY_DARK);
	test.Print(msg, CONSOLE_GREY_LIGHT);
	test.Print(msg, CONSOLE_WHITE);
	test.Print(msg, CONSOLE_BLUE_LIGHT);
	test.Print(msg, CONSOLE_GREEN_LIGHT);
	test.Print(msg, CONSOLE_CYAN_LIGHT);
	test.Print(msg, CONSOLE_RED_LIGHT);
	test.Print(msg, CONSOLE_MAGENTA_LIGHT);
	test.Print(msg, CONSOLE_YELLOW_LIGHT);
	test.Print(msg, CONSOLE_BLUE_DARK);
	test.Print(msg, CONSOLE_GREEN_DARK);
	test.Print(msg, CONSOLE_CYAN_DARK);
	test.Print(msg, CONSOLE_RED_DARK);
	test.Print(msg, CONSOLE_MAGENTA_DARK);
	test.Print(msg, CONSOLE_YELLOW_DARK);
	test.Print(msg, CONSOLE_BLACK, CONSOLE_BLACK);
	test.Print(msg, CONSOLE_BLACK, CONSOLE_GREY_DARK);
	test.Print(msg, CONSOLE_BLACK, CONSOLE_GREY_LIGHT);
	test.Print(msg, CONSOLE_BLACK, CONSOLE_WHITE);
	test.Print(msg, CONSOLE_BLACK, CONSOLE_BLUE_LIGHT);
	test.Print(msg, CONSOLE_BLACK, CONSOLE_GREEN_LIGHT);
	test.Print(msg, CONSOLE_BLACK, CONSOLE_CYAN_LIGHT);
	test.Print(msg, CONSOLE_BLACK, CONSOLE_RED_LIGHT);
	test.Print(msg, CONSOLE_BLACK, CONSOLE_MAGENTA_LIGHT);
	test.Print(msg, CONSOLE_BLACK, CONSOLE_YELLOW_LIGHT);
	test.Print(msg, CONSOLE_BLACK, CONSOLE_BLUE_DARK);
	test.Print(msg, CONSOLE_BLACK, CONSOLE_GREEN_DARK);
	test.Print(msg, CONSOLE_BLACK, CONSOLE_CYAN_DARK);
	test.Print(msg, CONSOLE_BLACK, CONSOLE_RED_DARK);
	test.Print(msg, CONSOLE_BLACK, CONSOLE_MAGENTA_DARK);
	test.Print(msg, CONSOLE_BLACK, CONSOLE_YELLOW_DARK);

	system("pause");
}

void PopulateBytePipeTest(anvil::BytePipe::Parser& writer) {
	writer.OnPipeOpen();
		writer.OnObjectBegin(4);

		writer.OnArrayBegin("array_test", 20);
			for (int i = 0; i < 20; ++i) writer(i);
		writer.OnArrayEnd();

		writer.OnObjectBegin("old_object_test", 4);
			writer((anvil::BytePipe::ComponentID)0, 'A');
			writer((anvil::BytePipe::ComponentID)1, 'B');
			writer((anvil::BytePipe::ComponentID)2, 'C');
			writer((anvil::BytePipe::ComponentID)3, 'D');
		writer.OnObjectEnd();

		writer.OnObjectBegin("new_object_test", 4);
			writer("first", 'A');
			writer("second", 'B');
			writer("third", 'C');
			writer("fourth", 'D');
		writer.OnObjectEnd();

		{
			cv::Mat tmp;
			tmp.create(cv::Size(256, 256), CV_8UC4);
			for (int32_t y = 0u; y < tmp.rows; ++y) for (int32_t x = 0u; x < tmp.cols; ++x) {
				uint8_t* dst = static_cast<uint8_t*>(tmp.data) + (y * tmp.cols + x) * 4;
				dst[0] = rand();
				dst[1] = rand();
				dst[2] = rand();
				dst[3] = 255;
			}
			writer("image", tmp, anvil::BytePipe::IMAGE_JPEG, 90.f);
		}

	writer.OnObjectEnd();
	writer.OnPipeClose();
}

void JSONTest() {
	using namespace anvil::BytePipe;

	JsonWriter writer;

	PopulateBytePipeTest(writer);

	{
		std::ofstream file("D:\\Adam\\Documents\\GitHub\\anvil\\AnvilTest.json");
		file << writer.GetJSONString();
	}

	std::thread display([]()->void { system("notepad D:\\Adam\\Documents\\GitHub\\anvil\\AnvilTest.json"); });
	display.detach();

	{
		std::string xml_src;
		{
			std::ifstream file("D:\\Adam\\Documents\\GitHub\\anvil\\AnvilTest.json");
			while (!file.eof()) {
				std::string line;
				std::getline(file, line);
				xml_src += line + '\n';
			}
		}

		nlohmann::json node;
		node = node.parse(xml_src);
		writer.OnPipeClose();
		writer.OnPipeOpen();
		ReadJSON(node, writer);

		std::ofstream file("D:\\Adam\\Documents\\GitHub\\anvil\\AnvilTest2.json");
		file << writer.GetJSONString();
	}

	std::thread display2([]()->void { system("notepad D:\\Adam\\Documents\\GitHub\\anvil\\AnvilTest2.json"); });
	display2.detach();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}


void XMLTest() {
	using namespace anvil::BytePipe;

	XMLWriter writer;
	PopulateBytePipeTest(writer);

	{
		std::ofstream file("D:\\Adam\\Documents\\GitHub\\anvil\\AnvilTest.xml");
		file << writer.GetXMLString();
	}

	std::thread display([]()->void { system("notepad D:\\Adam\\Documents\\GitHub\\anvil\\AnvilTest.xml"); });
	display.detach();

	{
		std::string xml_src;
		{
			std::ifstream file("D:\\Adam\\Documents\\GitHub\\anvil\\AnvilTest.xml");
			while (!file.eof()) {
				std::string line;
				std::getline(file, line);
				xml_src += line + '\n';
			}
		}

		rapidxml::xml_document<> doc;
		doc.parse<0>(const_cast<char*>(xml_src.c_str()));
		rapidxml::xml_node<>* node = doc.first_node();
		writer.OnPipeClose();
		writer.OnPipeOpen();
		ReadXML(*node, writer);

		std::ofstream file("D:\\Adam\\Documents\\GitHub\\anvil\\AnvilTest2.xml");
		file << writer.GetXMLString();
	}

	std::thread display2([]()->void { system("notepad D:\\Adam\\Documents\\GitHub\\anvil\\AnvilTest2.xml");});
	display2.detach();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void LZCNTTestA() {
	
	for (uint32_t i = 0; i < UINT16_MAX; ++i) {
		uint32_t c = anvil::detail::lzcount32_c(i);
		uint32_t a = anvil::detail::lzcount32_hwa(i);
		if(a != c) std::cout << "Value = " << i << " C++ says " << c << " BSR says " << a << std::endl;
	}
}

void TZCNTTestA() {

	for (uint32_t i = 0; i < UINT16_MAX; ++i) {
		uint32_t c = anvil::detail::tzcount32_c(i);
		uint32_t a = anvil::detail::tzcount32_hwa(i);
		if (a != c) std::cout << "Value = " << i << " C++ says " << c << " BSR says " << a << std::endl;
	}
}

void ReflectTest() {
	for (uint32_t i = 0; i <= UINT8_MAX; ++i) {
		uint8_t a = anvil::reflect((uint8_t)i);
		uint8_t b = anvil::reflect((uint8_t)a);
		if (b != i) std::cout << "Value = " << std::bitset<8>(i) << " A = " << std::bitset<8>(a) << " B = " << std::bitset<8>(b) << std::endl;
	}

	for (uint32_t i = 0; i <= UINT16_MAX; ++i) {
		uint16_t a = anvil::reflect((uint16_t)i);
		uint16_t b = anvil::reflect((uint16_t)a);
		if (b != i) std::cout << "Value = " << std::bitset<16>(i) << " A = " << std::bitset<16>(a) << " B = " << std::bitset<16>(b) << std::endl;
	}

	for (uint32_t i = 0; i <= UINT16_MAX; ++i) {
		uint32_t a = anvil::reflect((uint32_t)i);
		uint32_t b = anvil::reflect((uint32_t)a);
		if (b != i) std::cout << "Value = " << std::bitset<32>(i) << " A = " << std::bitset<32>(a) << " B = " << std::bitset<32>(b) << std::endl;
	}

	for (uint32_t i = 0; i <= UINT16_MAX; ++i) {
		uint64_t a = anvil::reflect((uint64_t)i);
		uint64_t b = anvil::reflect((uint64_t)a);
		if (b != i) std::cout << "Value = " << std::bitset<64>(i) << " A = " << std::bitset<64>(a) << " B = " << std::bitset<64>(b) << std::endl;
	}
}

void PopcountTest() {
	for (uint32_t i = 0; i <= UINT8_MAX; ++i) {
		std::cout << "Value = " << std::bitset<8>(i) << " Popcount = " << anvil::popcount((uint8_t)i) << std::endl;
	}
}

void Base64Test2() {
	std::string src, encoded;
	uint8_t src_bin;

	src = "Many hands make light work.";
	encoded = anvil::Base64::Encode((const uint8_t*)src.c_str(), src.size());

	const char* correct = "TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu";
	for (size_t i = 0; i < encoded.size(); ++i) {
		char a = encoded[i];
		char b = correct[i];
		if (a != b) 
			throw 0;
	}

	auto decoded = anvil::Base64::Decode(encoded.c_str(), encoded.size());
	if (memcmp(src.c_str(), decoded.data(), src.size()) != 0)
		throw 0;
	//if(i != 0) throw 0;
}

void RLETest2() {
	auto  WriteTest = [](anvil::BytePipe::OutputPipe & out, anvil::BytePipe::InputPipe & in, const void* src, size_t bytes, DebugPipe& debug_buffer, bool split_writes, bool split_reads)->void {
		try {
			if(! debug_buffer.buffer.empty())
				throw L"Buffer is not empty";

			//anvil::BytePipe::g_debug_rle = bytes == 6306;
			//if (anvil::BytePipe::g_debug_rle) {
			//	std::cout << "\x1B[2J\x1B[H";
			//	std::cout << "---------------START-TEST---------------" << std::endl;
			//}

			debug_buffer.bytes_read = 0;
			debug_buffer.bytes_written = 0;

			// Break into random sized writes
			if(split_writes) {
				size_t bytes_left = bytes;
				const uint8_t* src8 = static_cast<const uint8_t*>(src);
				while (bytes_left) {
					size_t bytes_to_write = bytes_left < 10 ? bytes_left : rand() % bytes_left;
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
			if (split_reads) {
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

			if (!debug_buffer.buffer.empty())
				throw L"Buffer is not empty";

			if (debug_buffer.bytes_read != debug_buffer.bytes_written)
				throw L"Number of bytes written does not match bytes read";

			if(!std::memcmp(buffer, src, bytes) == 0) 
				throw L"Memory read did not match what was written";

			delete[] buffer;

		}
		catch (std::exception& e) {
			std::cerr << e.what() << std::endl;
			throw e;
		}
		catch (...) {
			throw L"Caught something that wasn't a std::exception";
		}
	};

	auto RandomWriteTest = [&WriteTest](anvil::BytePipe::OutputPipe& out, anvil::BytePipe::InputPipe& in, DebugPipe& debug_buffer)->void {
		//{
		//	size_t bytes = 4604;
		//	uint8_t* data = bytes == 0u ? nullptr : new uint8_t[bytes];
		//	//memset(data, 128, bytes);
		//	for (size_t j = 0u; j < bytes; ++j) data[j] = (uint8_t)rand() % 255;

		//	WriteTest(out, in, data, bytes, debug_buffer);

		//	if (data) delete[] data;
		//}
		//return;

		//WriteTest(out, in, nullptr, 0, debug_buffer);

		//{
		//	uint32_t buffer = 12345678u;
		//	WriteTest(out, in, &buffer, sizeof(buffer), debug_buffer);
		//}

		for (size_t i = 0; i < 200; ++i) {
			size_t bytes = rand() % 10000;
			uint8_t* data = bytes == 0u ? nullptr : new uint8_t[bytes]; 

			// Always RLE
			memset(data, 128, bytes);
			WriteTest(out, in, data, bytes, debug_buffer, false, false);
			WriteTest(out, in, data, bytes, debug_buffer, true, true);

			// Never RLE
			for (size_t j = 0u; j < bytes; ++j) data[j] = (uint8_t)j % 256;
			WriteTest(out, in, data, bytes, debug_buffer, false, false);
			WriteTest(out, in, data, bytes, debug_buffer, true, true);

			// Random
			for (size_t j = 0u; j < bytes; ++j) data[j] = (uint8_t)rand() % 256;
			WriteTest(out, in, data, bytes, debug_buffer, false, false);
			WriteTest(out, in, data, bytes, debug_buffer, true, true);

			if (data) delete[] data;
		}
	};

	{
		DebugPipe debug_pipe;
		typedef uint8_t RLEIndex;
		typedef uint8_t RLEWord;
		anvil::BytePipe::RLEDecoderPipe<RLEIndex, RLEWord> in(debug_pipe);
		anvil::BytePipe::RLEEncoderPipe<RLEIndex, RLEWord> out(debug_pipe);

		RandomWriteTest(out, in, debug_pipe);
	}

	{
		DebugPipe debug_pipe;
		typedef uint8_t RLEIndex;
		typedef uint16_t RLEWord;
		anvil::BytePipe::RLEDecoderPipe<RLEIndex, RLEWord> in(debug_pipe);
		anvil::BytePipe::RLEEncoderPipe<RLEIndex, RLEWord> out(debug_pipe);

		RandomWriteTest(out, in, debug_pipe);
	}

	{
		DebugPipe debug_pipe;
		typedef uint8_t RLEIndex;
		typedef uint32_t RLEWord;
		anvil::BytePipe::RLEDecoderPipe<RLEIndex, RLEWord> in(debug_pipe);
		anvil::BytePipe::RLEEncoderPipe<RLEIndex, RLEWord> out(debug_pipe);

		RandomWriteTest(out, in, debug_pipe);
	}

	{
		DebugPipe debug_pipe;
		typedef uint8_t RLEIndex;
		typedef uint64_t RLEWord;
		anvil::BytePipe::RLEDecoderPipe<RLEIndex, RLEWord> in(debug_pipe);
		anvil::BytePipe::RLEEncoderPipe<RLEIndex, RLEWord> out(debug_pipe);

		RandomWriteTest(out, in, debug_pipe);
	}

	{
		DebugPipe debug_pipe;
		typedef uint16_t RLEIndex;
		typedef uint8_t RLEWord;
		anvil::BytePipe::RLEDecoderPipe<RLEIndex, RLEWord> in(debug_pipe);
		anvil::BytePipe::RLEEncoderPipe<RLEIndex, RLEWord> out(debug_pipe);

		RandomWriteTest(out, in, debug_pipe);
	}

	{
		DebugPipe debug_pipe;
		typedef uint16_t RLEIndex;
		typedef uint16_t RLEWord;
		anvil::BytePipe::RLEDecoderPipe<RLEIndex, RLEWord> in(debug_pipe);
		anvil::BytePipe::RLEEncoderPipe<RLEIndex, RLEWord> out(debug_pipe);

		RandomWriteTest(out, in, debug_pipe);
	}

	{
		DebugPipe debug_pipe;
		typedef uint16_t RLEIndex;
		typedef uint32_t RLEWord;
		anvil::BytePipe::RLEDecoderPipe<RLEIndex, RLEWord> in(debug_pipe);
		anvil::BytePipe::RLEEncoderPipe<RLEIndex, RLEWord> out(debug_pipe);

		RandomWriteTest(out, in, debug_pipe);
	}

	{
		DebugPipe debug_pipe;
		typedef uint16_t RLEIndex;
		typedef uint64_t RLEWord;
		anvil::BytePipe::RLEDecoderPipe<RLEIndex, RLEWord> in(debug_pipe);
		anvil::BytePipe::RLEEncoderPipe<RLEIndex, RLEWord> out(debug_pipe);

		RandomWriteTest(out, in, debug_pipe);
	}

	{
		DebugPipe debug_pipe;
		typedef uint64_t RLEIndex;
		typedef uint8_t RLEWord;
		anvil::BytePipe::RLEDecoderPipe<RLEIndex, RLEWord> in(debug_pipe);
		anvil::BytePipe::RLEEncoderPipe<RLEIndex, RLEWord> out(debug_pipe);

		RandomWriteTest(out, in, debug_pipe);
	}

	//enum { SIZE = 512 };
	//uint8_t buffer[SIZE];
	////memset(buffer, 128, SIZE);
	//for (int i = 0; i < SIZE; ++i) buffer[i] = i % 255;

	//out.WriteBytesFast(buffer, SIZE);
	//out.Flush();

	//uint8_t read_buffer[SIZE];
	//in.ReadBytesFast(read_buffer, SIZE);

	//if (memcmp(buffer, read_buffer, SIZE) != 0)
	//	throw 0;

	return;
}

void FillImage(anvil::compute::Image& img, anvil::compute::Vector value) {
	size_t w = img.GetHeight();
	size_t h = img.GetHeight();
	for (size_t y = 0u; y < h; ++y) {
		for (size_t x = 0u; x < w; ++x) {
			img.WritePixel(x, y, value);
		}
	}
}

void ImageRoiTest() {
	try {
		using namespace anvil::compute;

		Image img;
		img.Allocate(anvil::ANVIL_8UX4, 64, 64);
		volatile uint8_t* img_dat = (uint8_t*)img.GetData();
		FillImage(img, Vector(128, img.GetType()));


		Image r = img.GetChannel(0);
		FillImage(r, Vector(0, img.GetType()));
		Image g = img.GetChannel(1);
		FillImage(g, Vector(1, img.GetType()));
		Image b = img.GetChannel(2);
		FillImage(b, Vector(2, img.GetType()));
		Image a = img.GetChannel(3);
		FillImage(a, Vector(3, img.GetType()));

		size_t w = r.GetWidth();
		size_t h = r.GetHeight();
		size_t s = w * h;
		ANVIL_RUNTIME_ASSERT(img.GetWidth()== w, "R channel has wrong width");
		ANVIL_RUNTIME_ASSERT(img.GetHeight()== w, "R channel has wrong width");
		ANVIL_RUNTIME_ASSERT((int)anvil::ANVIL_8UX1== (int)r.GetType().GetEnumeratedType(), "R channel has wrong type");

		for (size_t y = 0u; y < h; ++y) for (size_t x = 0u; x < w; ++x) {
			uint8_t tmp;
			r.ReadPixel(x, y, tmp);
			ANVIL_RUNTIME_ASSERT((uint8_t)0 == tmp, "R channel contained a pixel with a wrong value (before copy)");
		}

		for (size_t y = 0u; y < h; ++y) for (size_t x = 0u; x < w; ++x) {
			uint8_t tmp;
			g.ReadPixel(x, y, tmp);
			ANVIL_RUNTIME_ASSERT((uint8_t)1 == tmp, "G channel contained a pixel with a wrong value (before copy)");
		}

		for (size_t y = 0u; y < h; ++y) for (size_t x = 0u; x < w; ++x) {
			uint8_t tmp;
			b.ReadPixel(x, y, tmp);
			ANVIL_RUNTIME_ASSERT((uint8_t)2 == tmp, "B channel contained a pixel with a wrong value (before copy)");
		}

		for (size_t y = 0u; y < h; ++y) for (size_t x = 0u; x < w; ++x) {
			uint8_t tmp;
			a.ReadPixel(x, y, tmp);
			ANVIL_RUNTIME_ASSERT((uint8_t)3 == tmp, "A channel contained a pixel with a wrong value (before copy)");
		}

		r = r.DeepCopy();
		g = g.DeepCopy();
		b = b.DeepCopy();
		a = a.DeepCopy();

		uint8_t* tmp;

		tmp = (uint8_t*)r.GetData();
		for (size_t i = 0u; i < s; ++i) ANVIL_RUNTIME_ASSERT((uint8_t)0 == tmp[i], "R channel contained a pixel with a wrong value (after copy) " + std::to_string(i));

		tmp = (uint8_t*)g.GetData();
		for (size_t i = 0u; i < s; ++i) ANVIL_RUNTIME_ASSERT((uint8_t)1 == tmp[i], "G channel contained a pixel with a wrong value (after copy) " + std::to_string(i));

		tmp = (uint8_t*)b.GetData();
		for (size_t i = 0u; i < s; ++i) ANVIL_RUNTIME_ASSERT((uint8_t)2 == tmp[i], "B channel contained a pixel with a wrong value (after copy) " + std::to_string(i));

		tmp = (uint8_t*)a.GetData();
		for (size_t i = 0u; i < s; ++i) ANVIL_RUNTIME_ASSERT((uint8_t)3 == tmp[i], "A channel contained a pixel with a wrong value (after copy) " + std::to_string(i));

	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		throw e;
	}

	return;
}

#pragma optimize("", off)
void ArithmeticMaskTest() {
	using namespace anvil::compute;

	ArithmeticOperations* operations = ArithmeticOperations::GetArithmeticOperations(anvil::ANVIL_32FX1, 0u);

	float a[4];
	float b[4];
	float c[4];
	uint8_t mask;

	for (float& val : a) val = 1.f;
	for (float& val : b) val = 2.f;

	mask = 0u;
	operations->Mask(a, b, c, 4u, &mask);
}

int main()
{
	ArithmeticMaskTest();
	return 0;

	ImageRoiTest();
	return 0;

	RLETest2();
	return 0;

	Base64Test2();
	return 0;

	//PopcountTest();
	ReflectTest();
	return 0;

	//TZCNTTestA();
	//LZCNTTestA();
	//return 0;

	//SchedulerTest();
	//return 0;

	//Base64Test();
	//EncodeOptimise();
	//return 0;

	//Base64Test();
	//JSONTest();
	//XMLTest();
	//RPCTest();
	//return 0;

	//UDPTest();
	//return 0;

	TCPTest();
	return 0;

	ConsoleTest();
	return 0;

	std::cout << "HW LZCNT : " << ANVIL_HW_LZCNTB << std::endl;

	for (uint32_t i = 0; i < 100; ++i) {
		uint32_t x = i;

		std::cout << x << "\t" << anvil::detail::lzcount32_hwb((uint32_t)x) << "\t" << anvil::detail::lzcount32_c((uint32_t)x) << std::endl;
	}

	std::cout << "HW TZCNT : " << ANVIL_HW_TZCNTB << std::endl;

	for (uint32_t i = 0; i < 100; ++i) {
		uint32_t x = i;

		std::cout << x << "\t" << anvil::detail::tzcount32_hwb((uint32_t)x) << "\t" << anvil::detail::tzcount32_c((uint32_t)x) << std::endl;
	}

	//for (uint32_t i = 0; i < 10000; ++i) {
	//	uint32_t x = rand();

	//	std::cout << x << "\t" << anvil::lzcount((uint32_t) x) << "\t" << anvil::lzcount_c((uint32_t)x) << std::endl;
	//}

	system("pause");

	//{
	//	anvil::BytePipe::JsonWriter out_pipe;

	//	std::map<std::string, std::vector<int>> map_test;

	//	{
	//		std::vector<int>& tmp = map_test.emplace("even", std::vector<int>()).first->second;
	//		for (int i = 0; i <= 10; ++i) if ((i & 1) == 0) tmp.push_back(i);
	//	}

	//	{
	//		std::vector<int>& tmp = map_test.emplace("odd", std::vector<int>()).first->second;
	//		for (int i = 0; i <= 10; ++i) if ((i & 1) != 0) tmp.push_back(i);
	//	}

	//	out_pipe(map_test);

	//	std::cout << out_pipe.GetJSON() << std::endl;
	//}
	std::vector<std::map<std::string, std::vector<int>>> map_test;
	std::vector<std::map<std::string, std::vector<int>>> in_test;
	{

		{
			std::ofstream ofile("D:\\Adam\\Documents\\GitHub\\anvil\\test.bin", std::ios::binary);
			anvil::BytePipe::OStreamPipe out_pipe(ofile);
			anvil::BytePipe::Writer writer(out_pipe);


			for (int j = 0; j < 1000; ++j) {
				map_test.push_back(std::map<std::string, std::vector<int>>());
				std::map<std::string, std::vector<int>>& map = map_test.back();

				{

					std::vector<int>& tmp = map.emplace("even", std::vector<int>()).first->second;
					for (int i = 0; i <= 1000; ++i) if ((i & 1) == 0) tmp.push_back(i);
				}

				{
					std::vector<int>& tmp = map.emplace("odd", std::vector<int>()).first->second;
					for (int i = 0; i <= 1000; ++i) if ((i & 1) != 0) tmp.push_back(i);
				}
			}

			const uint64_t t = CurrentTime();
			writer.OnPipeOpen();
			writer(map_test);
			writer.OnPipeClose();
			std::cout << "Write : " << (CurrentTime() - t) << " ms" << std::endl;
		}
		{
			std::ifstream ifile("D:\\Adam\\Documents\\GitHub\\anvil\\test.bin", std::ios::binary);
			
			uint64_t t = CurrentTime();
			anvil::BytePipe::IStreamPipe in_pipe(ifile);
			anvil::BytePipe::ValueParser parser;
			anvil::BytePipe::Reader reader(in_pipe);
			reader.Read(parser);
			std::cout << "Read : " << (CurrentTime() - t) << " ms" << std::endl;

			t = CurrentTime();
			in_test = anvil::BytePipe::ValueEncoder<decltype(in_test)>::Decode(parser.GetValue());
			std::cout << "Parse : " << (CurrentTime() - t) << " ms" << std::endl;
		}
	}

	system("pause");

	return 0;

	//{
	//	enum { size = 192 };
	//	typedef anvil::Vector<float, size> Vector;

	//	Vector a, b, c;
	//	anvil::Bitfield256 mask;


	//	for (size_t i = 0u; i < size; ++i) {
	//		a[i] = rand();
	//		b[i] = rand();
	//		c[i] = rand();
	//	}
	//	mask.low.low = rand();
	//	mask.low.high = rand();
	//	mask.high.low = rand();
	//	mask.high.high = rand();

	//	a = anvil::VectorAdd(b, c, a, mask);

	//}
	//system("pause");


	//enum { size = 16 };
	//anvil::Vector<float, size> a;
	//anvil::Vector<float, size> b;
	//anvil::Vector<float, size> c;

	////std::cin >> a[0u];
	////std::cin >> b[0u];
	////std::cin >> c[0u];

	////for (size_t i = 1u; i < size; ++i) {
	////	a[i] = a[0u];
	////	b[i] = b[0u];
	////	c[i] = c[0u];
	////}

	//for (size_t i = 0u; i < size; ++i) {
	//	a[i] = rand();
	//	b[i] = rand();
	//	c[i] = rand();
	//}

	////a += b;
	////a = anvil::VectorCmpEqtiplyAdd(a, b, c);
	////a = anvil::VectorAnd(a, b);
	////a = (a & b) | c;

	////enum : uint64_t { mask = 12345 };
	//int mask = rand() & ((1 << size) - 1);
	//a = anvil::VectorAnd(b, c, a, mask);
	////a = anvil::VectorAnd<mask>(b, c, a);
	////a = anvil::VectorAdd<mask>(b, c, b);
	////a = anvil::VectorNot(a,a, mask);

	//std::cout << a[0u] << std::endl;

	////uint32_t val;
	////std::cin >> val;

	////std::bitset<size> a = val;
	////std::bitset<size> b = anvil::CountOnes(&val, 1);


	////std::cout << a << std::endl;
 ////   std::cout << b << std::endl;
	//system("pause");
}