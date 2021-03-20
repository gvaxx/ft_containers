
#include "ft_vector.hpp"
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

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

template <class value >
bool check_vectors_size_and_value(ft::FtVector<value> a, std::vector<value> b)
{
	std::stringstream buffer;

	try
	{
		if (a.size() != b.size()) {
			buffer << "Vectors has different size\n" << "ft_vector: " << a.size() << std::endl << "   vector: " << b.size() << std::endl;
			throw buffer.str();
		}
		size_t size = a.size();
		size_t index = 0;
		while (index < size) {
			if (a[index] != b[index]) {
				buffer << "Vectors has different value at index " << index << std::endl << "ft_vector: " << a[index] << std::endl << "   vector: " << b[index] << std::endl;
				throw buffer.str();
			}
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
	buffer << "Vectors has different value " << std::endl << "ft_vector: " << a << std::endl << "   vector: " << b << std::endl;
	print_error(buffer.str());
	return false;
}

int main()
{
	ft::FtVector<long> a;
	std::vector<long> b;
	std::vector<long> c;
	srand(time(0));

	std::cout << "Empty							:";
	check_values(a.empty(), b.empty());
	for (int i = 0; i < 127; i++) {
		long r = rand() / 13;
		a.push_back(r);
		b.push_back(r);
		c.push_back(r / 3);
	}

	std::cout << "Erase value						:";
	a.erase(a.begin() + 2);
	b.erase(b.begin() + 2);
	check_vectors_size_and_value(a, b);


	std::cout << "Erase iterator						:";
	a.erase(a.begin() + 2, a.begin() + 6);
	b.erase(b.begin() + 2, b.begin() + 6);
	check_vectors_size_and_value(a, b);

	std::cout << "Push back						:";
	check_vectors_size_and_value(a, b);

	std::cout << "Front							:";
	check_values(a.front(), b.front());

	std::cout << "Back							:";
	check_values(a.back(), b.back());

	std::cout << "Pop back						:";
	check_vectors_size_and_value(a, b);

	std::cout << "Insert one item at pos first				:";
	long r = rand() / 13;
	a.insert(a.begin(), r);
	b.insert(b.begin(), r);

	a.insert(a.begin(), r);
	b.insert(b.begin(), r);

	a.insert(a.begin(), r);
	b.insert(b.begin(), r);
	check_vectors_size_and_value(a, b);

	std::cout << "Insert one item at last pos				:";
	r = rand() / 13;
	a.insert(a.end() - 1, r);
	b.insert(b.end() - 1, r);

	a.insert(a.end() - 1, r);
	b.insert(b.end() - 1, r);

	a.insert(a.end() - 1, r);
	b.insert(b.end() - 1, r);
	check_vectors_size_and_value(a, b);

	std::cout << "Insert some items at first pos				:";
	r = rand() / 13;
	a.insert(a.begin(), 10, r);
	b.insert(b.begin(), 10, r);

	check_vectors_size_and_value(a, b);

	std::cout << "Insert some items at end pos				:";
	r = rand() / 13;
	a.insert(a.begin(), 10, r);
	b.insert(b.begin(), 10, r);

	check_vectors_size_and_value(a, b);


	std::cout << "Insert some items from other vector at start pos	:";
	a.insert(a.begin(), c.begin(), c.begin() + 10);
	b.insert(b.begin(), c.begin(), c.begin() + 10);
	check_vectors_size_and_value(a, b);

	std::cout << "Insert some items from other vector at end pos		:";

	a.insert(a.end() - 11, c.begin(), c.begin() + 10);
	b.insert(b.end() - 11, c.begin(), c.begin() + 10);

	check_vectors_size_and_value(a, b);

	std::cout << "Reserve 2000						:";

	a.reserve(2000);
	b.reserve(2000);
	check_values(a.capacity(), b.capacity());

	std::cout << "vector[3]						:";
	check_values(a[3], b[3]);

	std::cout << "vector.at(8)						:";
	check_values(a.at(8), b.at(8));

	std::cout << "Clear							:";
	a.clear();
	b.clear();
	check_vectors_size_and_value(a, b);

	std::cout << "Max size						:";
	check_values(a.max_size(), b.max_size());

	std::cout << "Assign iterator						:";
	a.assign(c.begin(), c.begin() + 10);
	b.assign(c.begin(), c.begin() + 10);

	a.assign(c.begin() + 3, c.begin() + 5);
	b.assign(c.begin() + 3, c.begin() + 5);
	check_vectors_size_and_value(a, b);

	std::cout << "Assign value						:";
	r = rand() / 13;
	a.assign(154, r);
	b.assign(154, r);
	check_vectors_size_and_value(a, b);


	// std::cout << "   vector: ";
	// for (int i = 0; i < 5; i++)
	// 	std::cout << *(b.begin() + i) << std::endl;
	// std::cout << "(after insert)" << std::endl;
	
	// std::cout << "___________insert iter_________" << std::endl;

	// std::cout << "ft_vector: " << *(a.end() - 1) << std::endl;
	// std::cout << "   vector: " << *(a.end() - 1) << std::endl;

	// std::cout << "___________max size____________" << std::endl;

	// std::cout << "ft_vector: " << a.max_size() << std::endl;
	// std::cout << "   vector: " << b.max_size() << std::endl;

	// std::cout << a.max_size() << std::endl;
	// std::cout << a.max_size() << std::endl;
}