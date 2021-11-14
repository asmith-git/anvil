#include <iostream>
#include <bitset>
#include "anvil/Core.hpp"
#include "anvil/Compute.hpp"

int main()
{
	anvil::Vector<float, 16> a;
	anvil::Vector<float, 16> b;
	anvil::Vector<float, 16> c;

	std::cin >> a[0u];
	std::cin >> b[0u];
	std::cin >> c[0u];

	for (size_t i = 1u; i < 16; ++i) {
		a[i] = a[0u];
		b[i] = b[0u];
		c[i] = c[0u];
	}

	//a += b;
	//a = anvil::VectorMultiplyAdd(a, b, c);
	//a = anvil::VectorAnd(a, b);
	a = a & b;

	std::cout << a[0u] << std::endl;

	//uint32_t val;
	//std::cin >> val;

	//std::bitset<32> a = val;
	//std::bitset<32> b = anvil::CountOnes(&val, 1);


	//std::cout << a << std::endl;
 //   std::cout << b << std::endl;
	system("pause");
}