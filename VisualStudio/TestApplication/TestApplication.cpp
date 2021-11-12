#include <iostream>
#include <bitset>
#include "anvil/Core.hpp"

int main()
{
	uint32_t val;
	std::cin >> val;

	std::bitset<32> a = val;
	std::bitset<32> b = anvil::reflect(val);


	std::cout << a << std::endl;
    std::cout << b << std::endl;
	system("pause");
}