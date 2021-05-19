#include "queue.hpp"
#include "helper.hpp"
#include <queue>
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>

template <class value >
void create_queue(ft::queue<value> *a, std::queue<value> *b, long r, long n)
{
	b->clear();
	for (long i = 0; i < n; i++)
		(*b).push_back(rand() / r);
	a->assign(b->begin(), b->end());
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
	buffer << "queues has different value " << std::endl << "ft_queue: " << a << std::endl << "   queue: " << b << std::endl;
	print_error(buffer.str());
	return false;
}

void queue_test()
{
	ft::queue<long> a;
	std::queue<long> b;
	bool result;
	long r;

	std::cout << "Empty			:";
	check_values(a.empty(), b.empty());
	ft::queue<long> c;
	std::queue<long> d;
	ft::queue<long> e;
	std::queue<long> f;
	std::cout << "Push			:";
	for (int i = 0; i < 127; i++) {
		r = rand() / 13;
		a.push(r);
		b.push(r);
		c.push(r / 3);
		d.push(r / 3);
	}
	check_values(a.front(), b.front());
	std::cout << "Size			:";
	check_values(a.size(), b.size());
	std::cout << "Front			:";
	check_values(a.front(), b.front());
	std::cout << "Back			:";
	check_values(c.back(), d.back());

	std::cout << "Operator =		:";
	e = a;
	f = b;
	check_values(e.front(), f.front());
	std::cout << "Copy contructor		:";
	ft::queue<long> g(a);
	std::queue<long> h(b);
	check_values(g.back(), h.back());

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
	check_values(a.front(), b.front());
}
