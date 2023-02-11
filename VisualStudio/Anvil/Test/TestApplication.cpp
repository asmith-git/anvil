#include <iostream>
#include <bitset>
#include <fstream>
#include <chrono>
#include "anvil/Core.hpp"
#include "anvil/Compute.hpp"
#include "anvil/BytePipe.hpp"
#include "anvil/byte-pipe/BytePipeJSON.hpp"
#include "anvil/Console.hpp"
#include "anvil/RPC.hpp"
#include "anvil/Scheduling.hpp"

static uint64_t CurrentTime() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
		).count();
}

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
				if (my_h <= 4u) return false;
			}
			//if (GetScheduler().GetSleepingThreadCount() == 0u) return false;
			//if (GetNestingDepth() >= 2) return false;
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

				root.Wait();

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

	std::thread server([port]()->void {
		anvil::BytePipe::TCPServerPipe pipe(port);

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

		anvil::BytePipe::TCPClientPipe pipe(ip, port);

		for (int i = 0; i < 100; ++i) {
			pipe.WriteBytesFast(&i, sizeof(i));
		}
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

int main()
{
	SchedulerTest();
	return 0;

	Base64Test();
	EncodeOptimise();
	return 0;

	Base64Test();
	JSONTest();
	XMLTest();
	RPCTest();
	return 0;

	//UDPTest();
	//return 0;

	//TCPTest();
	//return 0;

	ConsoleTest();
	return 0;

	std::cout << "HW LZCNT : " << ANVIL_HW_LZCNT << std::endl;

	for (uint32_t i = 0; i < 100; ++i) {
		uint32_t x = i;

		std::cout << x << "\t" << anvil::detail::lzcount32_hw((uint32_t)x) << "\t" << anvil::detail::lzcount32_c((uint32_t)x) << std::endl;
	}

	std::cout << "HW TZCNT : " << ANVIL_HW_TZCNT << std::endl;

	for (uint32_t i = 0; i < 100; ++i) {
		uint32_t x = i;

		std::cout << x << "\t" << anvil::detail::tzcount32_hw((uint32_t)x) << "\t" << anvil::detail::tzcount32_c((uint32_t)x) << std::endl;
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