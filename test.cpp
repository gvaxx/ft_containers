#include <list>
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <map>

int main()
{
	std::map<char,int> mapper;
	mapper['b'] = 10;
	mapper['c'] = 20;
	mapper['d'] = 30;
	std::map<char,int>::iterator beg = mapper.begin();
	std::map<char,int>::iterator en = mapper.end();
	beg++;
	beg++;
	std::map<char,int>::iterator itr = mapper.insert(beg, std::pair<char,int>('a', 0));
	std::map<char,int>::iterator b = mapper.begin();

	while (b != en)
	{
		std::cout << b->first << ' '  << b->second<< std::endl;
		b++;
	}
}