#include <iostream>
#include <bitset>
#include "anvil/Core.hpp"

int main()
{
	anvil::Vector<float, 7u> a;
	anvil::Vector<float, 4u>& b = a.lower_half;
	anvil::Vector<float, 2>& b2 = b.lower_half;
	float& b3 = b2.lower_half;
	anvil::Vector<float, 3u>& c = a.upper_half;
	anvil::Vector<float, 7u> d(b, c);

	//uint32_t val;
	//std::cin >> val;

	//std::bitset<32> a = val;
	//std::bitset<32> b = anvil::CountOnes(&val, 1);


	//std::cout << a << std::endl;
 //   std::cout << b << std::endl;
	system("pause");
}