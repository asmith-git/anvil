#include <iostream>
#include <bitset>
#include "anvil/Core.hpp"
#include "anvil/Compute.hpp"

int main()
{
	anvil::Vector<float, 64> a;
	anvil::Vector<float, 64> b;

	a.lower_half += b.lower_half;
	//a.upper_half -= b.upper_half;

	//uint32_t val;
	//std::cin >> val;

	//std::bitset<32> a = val;
	//std::bitset<32> b = anvil::CountOnes(&val, 1);


	//std::cout << a << std::endl;
 //   std::cout << b << std::endl;
	system("pause");
}