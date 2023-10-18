
#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#include <algorithm>
#include <functional>


std::ostream &print(std::ostream &os, int &val, char c=' ')
{
	return os << val << c;
}


int main(int argc, char *argv[])
{
	std::vector<int> vec1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::vector<int> vec2;

	std::copy(vec1.cbegin(), vec1.cend(), std::inserter(vec2, vec2.begin()));
	std::cout <<"\nvec2 inserter:";
	for_each(vec2.begin(), vec2.end(), std::bind(print, std::ref(std::cout), std::placeholders::_1, ' '));

	std::list<int> lst3;
	std::copy(vec1.cbegin(), vec1.cend(), std::front_inserter(lst3));
	std::cout <<"\nlist front_insert:";
	for_each(lst3.begin(), lst3.end(), std::bind(print, std::ref(std::cout), std::placeholders::_1, ' '));

	std::list<int> lst4;
	std::copy(vec1.cbegin(), vec1.cend(), std::back_inserter(lst4));
	std::cout <<"\nlist back_insert:";
	for_each(lst4.begin(), lst4.end(), std::bind(print, std::ref(std::cout), std::placeholders::_1, ' '));

	return 0;
}
