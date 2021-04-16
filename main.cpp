
#include <list>
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>

bool list_test();
int main()
{
	srand(time(0));
	// vector_test();
	while(list_test());
	// std::list<long> b(10, 13);
	// std::cout << b.size() << std::endl;
	// b.assign(++b.begin(), b.end());
	// std::cout << b.size() << std::endl;
}