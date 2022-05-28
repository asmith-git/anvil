#include <iostream>
#include <bitset>
#include <fstream>
#include "anvil/Core.hpp"
#include "anvil/Compute.hpp"
#include "anvil/BytePipe.hpp"
#include "anvil/byte-pipe/BytePipeJSON.hpp"

int main()
{
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
	{
		std::map<std::string, std::vector<int>> map_test;
		std::map<std::string, std::vector<int>> in_test;

		{
			std::ofstream ofile("D:\\Adam\\Documents\\GitHub\\anvil\\test.bin", std::ios::binary);
			anvil::BytePipe::OStreamPipe out_pipe(ofile);
			anvil::BytePipe::Writer writer(out_pipe);


			{
				std::vector<int>& tmp = map_test.emplace("even", std::vector<int>()).first->second;
				for (int i = 0; i <= 10; ++i) if ((i & 1) == 0) tmp.push_back(i);
			}

			{
				std::vector<int>& tmp = map_test.emplace("odd", std::vector<int>()).first->second;
				for (int i = 0; i <= 10; ++i) if ((i & 1) != 0) tmp.push_back(i);
			}

			writer.OnPipeOpen();
			writer(map_test);
			writer.OnPipeClose();
		}
		{
			std::ifstream ifile("D:\\Adam\\Documents\\GitHub\\anvil\\test.bin", std::ios::binary);
			anvil::BytePipe::IStreamPipe in_pipe(ifile);
			anvil::BytePipe::ValueParser parser;
			anvil::BytePipe::Reader reader(in_pipe);
			reader.Read(parser);

			in_test = static_cast<decltype(in_test)>(parser.GetValue());
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