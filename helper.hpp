
#ifndef FT_HELPER
#define FT_HELPER
namespace ft
{
	template <class T>
	void swap_value(T & x, T & y)
	{
		T tmp = x;
		x = y;
		y = tmp;
	}

	template <class T>
	struct Node
	{
		Node	*prev;
		Node	*next;
		T		value;
	};
} // namespace ft

void print_error(std::string error_string)
{
	std::cerr << "\x1b[31m" << error_string << "\x1b[0m";
}

void print_success()
{
	std::cout << "\x1b[32m" << "[OK]" << "\x1b[0m" << std::endl;
}

void print_fail()
{
	std::cout << "\x1b[31m" << "[FAIL]" << "\x1b[0m" << std::endl;
}
#endif
