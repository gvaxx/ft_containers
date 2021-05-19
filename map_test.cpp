
#include "map.hpp"
#include "helper.hpp"
#include <map>
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <utility> 

template <class key,class value >
void create_map(ft::map<key,value> *a, std::map<key,value> *b, long r, long n)
{
	b->clear();
	for (long i = 0; i < n; i++)
		(*b).push_back(rand() / r);
	a->assign(b->begin(), b->end());
}

template <class key,class value >
bool check_map_size_and_value(ft::map<key,value> *a, std::map<key,value> *b)
{
	std::stringstream buffer;
	try
	{
		if ((*a).size() != (*b).size()) {
			buffer << "Lists have different size\n" << "ft_map: " << (*a).size() << std::endl << "   map: " << (*b).size() << std::endl;
			throw buffer.str();
		}
		typename ft::map<key,value>::iterator ft_beg = (*a).begin();
		typename ft::map<key,value>::iterator ft_end = (*a).end();

		size_t index = 0;
		while (ft_beg != ft_end) {
			if ((*b)[(*ft_beg).first] != (*ft_beg).second) {
				buffer << "Lists have different value in key[" << (*ft_beg).first << std::endl << "ft_map: " << (*ft_beg).second << std::endl << "   map: " << (*b)[(*ft_beg).first] << std::endl;
				throw buffer.str();
			}
			ft_beg++;
			index++;
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
	buffer << "Containers has different value " << std::endl << "ft_container: " << a << std::endl << "   container: " << b << std::endl;
	print_error(buffer.str());
	return false;
}

template <class key, class value >
bool check_pair(std::pair<key, value> a, std::pair<key, value> b, bool is_print = false)
{
	if (a == b) {
		if (is_print)
			print_success();
		return true;
	}
	print_fail();
	std::stringstream buffer;
	buffer << "Maps have different value in key[" << a.first << std::endl << "ft_map: " << a.second << std::endl << "   map: " << b.second << std::endl;
	print_error(buffer.str());
	return false;
}

template <class key,class value >
void show_value(ft::map<key,value> a)
{
	typename ft::map<key,value>::iterator it = a.begin();
	while (it != a.end()) {
		std::cout << "[" << it->first << "] = " << it->second << std::endl;
		it++;
	}
}

template <class key,class value >
void show_value(std::map<key,value> a)
{
	typename std::map<key,value>::iterator it = a.begin();
	while (it != a.end()) {
		std::cout << "[" << it->first << "] = " << it->second << std::endl;
		it++;
	}
}

void map_test()
{
	srand(time(0));
	ft::map<char, long> a;
	std::map<char, long> b;
	bool result;
	long v;
	char k;
	std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

	ft::map<char, long> c;
	std::map<char, long> d;

	std::cout << "Check operator []	:";
	for (int i = 0; i < 30; i++) {
		k = alphabet[rand() % 52];
		v = rand() / 42;
		a[k] = v;
		b[k] = v;
	}
	check_map_size_and_value(&a, &b);
	std::cout << "Check operator =	:";
	c = a;
	d = b;
	check_map_size_and_value(&c, &d);
	c.clear();
	d.clear();
	std::cout << "Find			:";
	bool have_errors = false;
	for (int i = 0; i < 100; i++) {
		k = alphabet[rand() % 52];

		ft::map<char, long>::iterator ft_iterator = a.find(k);
		std::map<char, long>::iterator iterator = b.find(k);
		if (ft_iterator == a.end() || b.end() == b.find(k)) {
			if (ft_iterator == a.end() && b.end() == b.find(k))
				continue;
			have_errors = true;
			print_fail();
			std::stringstream buffer;
			buffer << "Maps return different end in key[" << k << "]" << std::endl;
			break;
		}
		else if (!check_pair(*ft_iterator, *iterator))
		{
			have_errors = true;
			break;
		}
	}
	if (have_errors == false)
		print_success();


	std::cout << "Count			:";
	k = alphabet[rand() % 52];
	check_values(a.count((*a.begin()).first), b.count((*b.begin()).first));
	std::cout << "Count 2			:";
	check_values(c.count(k), d.count(k));

	for (int i = 0; i < 3; i++) {
		v = rand() / 13;
		k = alphabet[rand() % 52];

		a.insert(a.begin(), std::make_pair(k, v));
		b.insert(b.begin(), std::make_pair(k, v));
		c.insert(c.end(), std::make_pair(k, v));
		d.insert(d.end(), std::make_pair(k, v));
	}
	
	std::cout << "Insert pair		:";
	check_map_size_and_value(&a, &b);

	std::cout << "Insert pair 2		:";
	check_map_size_and_value(&c, &d);

	std::cout << "Insert InputIterator	:";
	c.insert(a.begin(), a.end());
	d.insert(b.begin(), b.end());
	check_map_size_and_value(&c, &d);

	std::cout << "Operator ==		:";
	check_values(a == c, b == d);

	std::cout << "Operator !=		:";
	check_values(a != c, b != d);

	std::cout << "Operator <		:";
	check_values(a < c, b < d);

	std::cout << "Operator >		:";
	check_values(a > c, b > d);

	std::cout << "Operator <=		:";
	check_values(a > c, b > d);

	std::cout << "Operator >=		:";
	check_values(a > c, b > d);

	k = (*(++a.begin())).first;
	std::cout << "Lower_bound		:";
	ft::map<char, long>::iterator ft_lb = a.lower_bound(k);
	std::map<char, long>::iterator lb = b.lower_bound(k);
	check_pair((*ft_lb), (*lb), true);
	std::cout << "Upper_bound		:";
	ft::map<char, long>::iterator ft_ub = a.upper_bound(k);
	std::map<char, long>::iterator ub = b.upper_bound(k);
	check_pair((*ft_ub), (*ub), true);

	std::cout << "Equal_bound		:";
	std::pair<ft::map<char, long>::iterator, ft::map<char, long>::iterator> ft_eb = a.equal_range(k);
	std::pair<std::map<char, long>::iterator, std::map<char, long>::iterator> eb = b.equal_range(k);
	check_values(ft_lb == ft_eb.first && ft_ub == ft_eb.second, lb == eb.first && ub == eb.second);
	std::cout << "Erase			:";
	a.erase('a');
	b.erase('a');
	check_map_size_and_value(&a, &b);

	std::cout << "Swap			:";
	a.swap(c);
	b.swap(d);
	check_map_size_and_value(&a, &b);

	std::cout << "Erase 2			:";
	a.erase(++a.begin());
	b.erase(++b.begin());
	check_map_size_and_value(&a, &b);

	std::cout << "Erase from iterator	:";
	c.erase(c.begin(), --c.end());
	d.erase(d.begin(), --d.end());
	check_map_size_and_value(&c, &d);

	std::cout << "Clear			:";
	a.clear();
	b.clear();
	check_map_size_and_value(&a, &b);
}
