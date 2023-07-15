

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

void print_arr(int *arr, int len) 
{
	for(int idx = 0;idx != len;idx++)
	{
		std::cout << arr[idx]<<" ";
	}
	std::cout << std::endl;

	return;
}

void print_vector(std::vector<int> &vec)
{
	for(std::vector<int>::iterator element=vec.begin(); element != vec.end();element++)
	{
		std::cout << *element<<" ";
	}
	std::cout << std::endl;
}

int main(int argc, char *argv[])
{
	int arr1[10] = {0,1,2,3,4,5,6,7,8,0};
	int arr2[10];
	std::vector<int> vec;

	std::copy(std::begin(arr1), std::end(arr1), std::begin(arr2));

	std::cout << "arr2 copy from arr1:" << std::endl;
	print_arr(arr2, 10);

	std::replace(std::begin(arr1), std::end(arr1), 0, 10);
	std::cout << "arr1, 10 instead of 0: " << std::endl;
	print_arr(arr1, 10);

	std::replace_copy(std::begin(arr1), std::end(arr1), std::back_inserter(vec), 10, 11);
	print_vector(vec);

	return 0;
}
