#include <iostream>
#include <bitset>
#include "anvil/Core.hpp"
#include "anvil/Compute.hpp"

int main()
{
	{
		typedef anvil::Vector<float, 192> Vector;

		Vector a, b, c;
		anvil::Bitfield256 mask;

		a = anvil::VectorBlendRuntimeMask(b, c, mask);

	}
	system("pause");


	enum { size = 16 };
	anvil::Vector<float, size> a;
	anvil::Vector<float, size> b;
	anvil::Vector<float, size> c;

	//std::cin >> a[0u];
	//std::cin >> b[0u];
	//std::cin >> c[0u];

	//for (size_t i = 1u; i < size; ++i) {
	//	a[i] = a[0u];
	//	b[i] = b[0u];
	//	c[i] = c[0u];
	//}

	for (size_t i = 0u; i < size; ++i) {
		a[i] = rand();
		b[i] = rand();
		c[i] = rand();
	}

	//a += b;
	//a = anvil::VectorCmpEqtiplyAdd(a, b, c);
	//a = anvil::VectorAnd(a, b);
	//a = (a & b) | c;

	//enum : uint64_t { mask = 12345 };
	int mask = rand() & ((1 << size) - 1);
	a = anvil::VectorAnd(b, c, a, mask);
	//a = anvil::VectorAnd<mask>(b, c, a);
	//a = anvil::VectorAdd<mask>(b, c, b);
	//a = anvil::VectorNot(a,a, mask);

	std::cout << a[0u] << std::endl;

	//uint32_t val;
	//std::cin >> val;

	//std::bitset<size> a = val;
	//std::bitset<size> b = anvil::CountOnes(&val, 1);


	//std::cout << a << std::endl;
 //   std::cout << b << std::endl;
	system("pause");
}