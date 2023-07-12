

#include <iostream>
#include <vector>
#include <algorithm>

int main(int argc, char *argv[])
{
	std::vector<int> vec = {1,2,3,4,5,6,7};
	int val1 = 4, val2 = 10;

	auto rest = std::find (vec.cbegin(), vec.cend(), val1);
	if (rest != vec.cend())
	{
		std::cout << "find: " << val1 << std::endl;
	}
	else
	{
		std::cout << "can't find " << val1 << std::endl;
	}

	rest = std::find(vec.cbegin(), vec.cend(), val2);
	if (rest != vec.cend())
	{
		std::cout << "find:" << val2 << std::endl;
	}
	else
	{
		std::cout << "can't find " << val2 << std::endl;
	}

	int arr[10] = {8,9,10,11,12,13};
	auto rest1 = std::find(std::begin(arr), std::end(arr), val1);
	if (rest1 != std::end(arr))
	{
		std::cout << "find array element " << *rest1 << std::endl;
	}
	else
	{
		std::cout <<  "can't find array " << val1 << std::endl;
	}

	rest1 = std::find(std::begin(arr), std::end(arr), val2);

	if (rest1 != std::end(arr))
	{
		std::cout << "find array element " << *rest1 << std::endl;
	}
	else
	{
		std::cout <<  "can't find array " << val2 << std::endl;
	}

	return 0;
}
