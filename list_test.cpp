#include "list.hpp"
#include "helper.hpp"
#include <list>
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>

template <class value >
void create_list(ft::list<value> *a, std::list<value> *b, long r, long n)
{
	b->clear();
	for (long i = 0; i < n; i++)
		(*b).push_back(rand() / r);
	a->assign(b->begin(), b->end());
}

template <class value >
bool check_list_size_and_value(ft::list<value> *a, std::list<value> *b)
{
	std::stringstream buffer;
	try
	{
		if ((*a).size() != (*b).size()) {
			buffer << "Lists have different size\n" << "ft_list: " << (*a).size() << std::endl << "   list: " << (*b).size() << std::endl;
			throw buffer.str();
		}
		typename ft::list<value>::iterator ft_beg = (*a).begin();
		typename ft::list<value>::iterator ft_end = (*a).end();

		typename std::list<value>::iterator beg = (*b).begin();
		typename std::list<value>::iterator end = (*b).end();
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
template <class value >
void show_value(ft::list<value> a)
{
	typename ft::list<value>::iterator it = a.begin();
	while (it != a.end())
		std::cout << *(it++) << std::endl;
}

template <class value >
void show_value(std::list<value> a)
{
	typename std::list<value>::iterator it = a.begin();
	while (it != a.end())
		std::cout << *(it++) << std::endl;
}

bool list_test()
{
	ft::list<long> a;
	std::list<long> b;
	bool result;

	create_list(&a, &b, rand() % 50 + 1, rand() % 200 + 1);
	result = check_list_size_and_value(&a, &b);
	if (!result) {
		show_value(a);
		show_value(b);
	}
	return result;

/*
	std::cout << "Check create with default value	:";
	check_list_size_and_value(&a, &b);
	ft::list<long> c;
	std::list<long> d;
	for (int i = 0; i < 127; i++) {
		r = rand() / 13;
		a.push_back(r);
		b.push_back(r);
		c.push_front(r / 3);
		d.push_front(r / 3);
	}
	std::cout << "Operator ==	:";
	check_values(a == c, b == d);
	std::cout << "Operator !=	:";
	check_values(a != c, b != d);
	std::cout << "Operator <	:";
	check_values(a < c, b < d);
	std::cout << "Operator <=	:";
	check_values(a <= c, b <= d);
	std::cout << "Operator >	:";
	check_values(a > c, b > d);
	std::cout << "Operator >=	:";
	check_values(a >= c, b >= d);
	std::cout << "Check for early full lists	:";
	check_list_size_and_value(&a, &b);
	std::cout << "Check for early empty lists	:";
	check_list_size_and_value(&c, &d);
	for (int i = 0; i < 3; i++) {
		a.pop_back();
		b.pop_back();
		c.pop_front();
		d.pop_front();
	}
	std::cout << "Pop back			:";
	check_list_size_and_value(&a, &b);
	std::cout << "Pop front			:";
	check_list_size_and_value(&c, &d);

	std::cout << "Front				:";
	check_values(a.front(), b.front());
	std::cout << "Back				:";
	check_values(c.back(), d.back());
	for (int i = 0; i < 3; i++) {
		r = rand() / 13;
		a.insert(a.begin(), r);
		b.insert(b.begin(), r);
		c.insert(c.end(), r);
		d.insert(d.end(), r);
	}

	std::cout << "Check for early full lists	:";
	check_list_size_and_value(&a, &b);
	std::cout << "Check for early empty lists	:";
	check_list_size_and_value(&c, &d);
	std::cout << "Check for early full lists	:";
	a.insert(++a.begin(), i, t);
	b.insert(++b.begin(), i, t);
	check_list_size_and_value(&a, &b);

	std::cout << "Check for early full lists	:";
	c.insert(++c.begin(), c.begin(), c.end());
	d.insert(++d.begin(), d.begin(), d.end());

	check_list_size_and_value(&c, &d);

	std::cout << "Remove				:";
	a.remove(130);
	b.remove(130);
	check_list_size_and_value(&a, &b);

	std::cout << "Resize less			:";
	a.resize(50);
	b.resize(50);
	check_list_size_and_value(&a, &b);

	std::cout << "Resize more			:";
	r = rand()/21;
	a.resize(100, r);
	b.resize(100, r);
	check_list_size_and_value(&a, &b);
	std::cout << "Merge				:";
	a.merge(c);
	b.merge(d);
	check_list_size_and_value(&a, &b);
	std::cout << "Reverse				:";
	a.reverse();
	b.reverse();
	check_list_size_and_value(&a, &b);
	std::cout << "Sort				:";
	a.sort();
	b.sort();
	check_list_size_and_value(&a, &b);
	std::cout << "Swap				:";
	a.swap(c);
	b.swap(d);
	check_list_size_and_value(&a, &b);
	std::cout << "Unique				:";
	a.unique();
	b.unique();
	check_list_size_and_value(&a, &b);
	std::cout << "Splice all			:";
	a.splice(++a.begin(), c);
	b.splice(++b.begin(), d);
	check_list_size_and_value(&a, &b);
	std::cout << "Erase				:";
	a.erase(++a.begin());
	b.erase(++b.begin());
	check_list_size_and_value(&a, &b);
	std::cout << "Erase some iterator		:";
	c.erase(c.begin(), c.end());
	d.erase(d.begin(), d.end());
	check_list_size_and_value(&c, &d); */
}