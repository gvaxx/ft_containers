#include "stack.hpp"
#include "helper.hpp"
#include <stack>
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>

template <class value >
bool check_values(value a, value b)
{
	if (a == b) {
		print_success();
		return true;
	}
	print_fail();
	std::stringstream buffer;
	buffer << "stacks has different value " << std::endl << "ft_stack: " << a << std::endl << "   stack: " << b << std::endl;
	print_error(buffer.str());
	return false;
}

void stack_test()
{
	ft::stack<long> a;
	std::stack<long> b;
	bool result;
	long r;

	std::cout << "Empty			:";
	check_values(a.empty(), b.empty());
	ft::stack<long> c;
	std::stack<long> d;
	ft::stack<long> e;
	std::stack<long> f;
	std::cout << "Push			:";
	for (int i = 0; i < 127; i++) {
		r = rand() / 13;
		a.push(r);
		b.push(r);
		c.push(r / 3);
		d.push(r / 3);
	}
	check_values(a.top(), b.top());
	std::cout << "Size			:";
	check_values(a.size(), b.size());
	std::cout << "Top			:";
	check_values(c.top(), d.top());

	std::cout << "Operator =		:";
	e = a;
	f = b;
	check_values(e.top(), f.top());
	std::cout << "Copy contructor		:";
	ft::stack<long> g(a);
	std::stack<long> h(b);
	check_values(g.top(), h.top());

	std::cout << "Operator ==		:";
	check_values(a == c, b == d);
	std::cout << "Operator !=		:";
	check_values(a != c, b != d);
	std::cout << "Operator <		:";
	check_values(a < c, b < d);
	std::cout << "Operator <=		:";
	check_values(a <= c, b <= d);
	std::cout << "Operator >		:";
	check_values(a > c, b > d);
	std::cout << "Operator >=		:";
	check_values(a >= c, b >= d);
	for (int i = 0; i < 3; i++) {
		a.pop();
		b.pop();
		c.pop();
		d.pop();
	}
	std::cout << "Pop			:";
	check_values(a.top(), b.top());
}
