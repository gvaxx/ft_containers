
#include "list.hpp"
#include "helper.hpp"
#include <list>
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>

void vector_test();

template <class value >
bool check_list_size_and_value(ft::list<value> a, std::list<value> b)
{
	std::stringstream buffer;
	try
	{
		if (a.size() != b.size()) {
			buffer << "Lists have different size\n" << "ft_list: " << a.size() << std::endl << "   list: " << b.size() << std::endl;
			throw buffer.str();
		}
		typename ft::list<value>::iterator ft_beg = a.begin();
		typename ft::list<value>::iterator ft_end = a.end();

		typename std::list<value>::iterator beg = b.begin();
		typename std::list<value>::iterator end = b.end();
		size_t index = 0;
		while (ft_beg != ft_end || beg != end) {
			if (*ft_beg != *beg) {
				buffer << "Lists have different value in node " << index << std::endl << "ft_list: " << *ft_beg << std::endl << "   list: " << *beg << std::endl;
				throw buffer.str();
			}
			ft_beg++;
			beg++;
			index++;
		}
		if (ft_beg != ft_end || beg != end) {
			buffer << "Lists have length" << std::endl;
			throw buffer.str();
		}
	}
	catch(std::string err)
	{
		print_fail();
		print_error(err);
		return false;
	}
	print_success();
	return true;
}

template <class value >
bool check_values(value a, value b)
{
	if (a == b) {
		print_success();
		return true;
	}
	print_fail();
	std::stringstream buffer;
	buffer << "Lists has different value " << std::endl << "ft_list: " << a << std::endl << "   list: " << b << std::endl;
	print_error(buffer.str());
	return false;
}

void list_test()
{
	size_t i = 100;
	long t = 130;
	long r;
	ft::list<long> a(i, t);
	std::list<long> b(i, t);
	std::cout << "Check create with default value	:";
	check_list_size_and_value(a, b);
	ft::list<long> c;
	std::list<long> d;

	std::cout << "Empty				:";
	check_values(c.empty(), d.empty());
	for (int i = 0; i < 127; i++) {
		r = rand() / 13;
		a.push_back(r);
		b.push_back(r);
		c.push_front(r / 3);
		d.push_front(r / 3);
	}
	std::cout << "Check for early full lists	:";
	check_list_size_and_value(a, b);
	std::cout << "Check for early empty lists	:";
	check_list_size_and_value(c, d);
	for (int i = 0; i < 3; i++) {
		a.pop_back();
		b.pop_back();
		c.pop_front();
		d.pop_front();
	}
	std::cout << "Pop back			:";
	check_list_size_and_value(a, b);
	std::cout << "Pop front			:";
	check_list_size_and_value(c, d);

	std::cout << "Front				:";
	check_values(a.front(), b.front());
	std::cout << "Back				:";
	check_values(c.back(), d.back());
}

int main()
{
	srand(time(0));
	// vector_test();
	list_test();
	// std::list<long> b;
	// std::cout << b.size() << std::endl;
	// std::cout << (b.begin() == b.end()) << std::endl;
	// std::cout << *(b.begin()) << std::endl;
	// b.insert(b.end(), 5);
	// std::cout << b.size() << std::endl;
	// std::cout << *(b.begin()) << std::endl;
}