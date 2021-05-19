#include "helper.hpp"
#include <map>

void vector_test();
void list_test();
void map_test();
void queue_test();
void stack_test();

int main()
{
	try {
		std::cout << "_______vector_______\n";
		vector_test();
		// std::cout << "_______list_________\n";
		// list_test();
		// std::cout << "_______map__________\n";
		// map_test();
		// std::cout << "_______queue________\n";
		// queue_test();
		// std::cout << "_______stack________\n";
		// stack_test(); 
	} catch(std::string err) {
		print_error(err);
	}

}