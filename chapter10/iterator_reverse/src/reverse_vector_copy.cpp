
#include <iostream>
#include <vector>
#include <list>
#include <functional>
#include <algorithm>



int main(int argc, char *argv[])
{
	std::vector<int> vec_int{1,2,3,4,5,6,7,8,9,10};

	std::vector<int>::reverse_iterator vec_crstart = vec_int.rbegin() + 3;
	std::vector<int>::reverse_iterator vec_crend = vec_int.rend() - 2;

	std::list<int> lst;
	for(;vec_crstart < vec_crend;vec_crstart++)
	{
		lst.push_back(*vec_crstart);
	}

	for(const auto list_ele:lst)
	{
		std::cout << list_ele << " ";
	}
	std::cout << std::endl;

	return 0;
}
