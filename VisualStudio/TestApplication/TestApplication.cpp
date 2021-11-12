#include <iostream>
#include "anvil/Core.hpp"

int main()
{
	uint32_t val;
	std::cin >> val;
    std::cout << anvil::reflect(val) << std::endl;
	system("pause");
}