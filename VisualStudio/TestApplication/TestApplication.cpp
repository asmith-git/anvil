#include <iostream>
#include <bitset>
#include <fstream>
#include <chrono>
#include "anvil/Core.hpp"
#include "anvil/Compute.hpp"
#include "anvil/BytePipe.hpp"
#include "anvil/byte-pipe/BytePipeJSON.hpp"
#include "anvil/Console.hpp"

static uint64_t CurrentTime() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
		).count();
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
		anvil::BytePipe::TCPInputPipe pipe(port);

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

		anvil::BytePipe::TCPOutputPipe pipe(ip, port);

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
		writer.OnObjectBegin(3);

		writer.OnComponentID("array_test");
		writer.OnArrayBegin(20);
			for (int i = 0; i < 20; ++i) writer.OnPrimitiveS32(i);
		writer.OnArrayEnd();

		writer.OnComponentID("old_object_test");
		writer.OnObjectBegin(4);
			writer.OnComponentID((anvil::BytePipe::ComponentID)0);
			writer.OnPrimitiveC8('A');
			writer.OnComponentID(1);
			writer.OnPrimitiveC8('B');
			writer.OnComponentID(2);
			writer.OnPrimitiveC8('C');
			writer.OnComponentID(3);
			writer.OnPrimitiveC8('D');
		writer.OnObjectEnd();

		writer.OnComponentID("new_object_test");
		writer.OnObjectBegin(4);
			writer.OnComponentID("first");
			writer.OnPrimitiveC8('A');
			writer.OnComponentID("second");
			writer.OnPrimitiveC8('B');
			writer.OnComponentID("third");
			writer.OnPrimitiveC8('C');
			writer.OnComponentID("fourth");
			writer.OnPrimitiveC8('D');
		writer.OnObjectEnd();

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
	JSONTest();
	XMLTest();
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
			in_test = static_cast<decltype(in_test)>(parser.GetValue());
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