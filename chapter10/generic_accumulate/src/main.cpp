

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <numeric>


int main(int argc, char *argv[])
{
	std::vector<int> vec {1,2,3,4,6,7,8,9};

	int sum = std::accumulate(vec.cbegin(), vec.cend(), 0);
	std::cout << "vec summary:" << sum << std::endl;

	std::list<std::string> list_str{"hello", " ", "world", "."};
	std::string new_string = std::accumulate(list_str.cbegin(), list_str.cend(), std::string(""));
	std::cout << "accumulate string:" << new_string << std::endl;

	return 0;
}
