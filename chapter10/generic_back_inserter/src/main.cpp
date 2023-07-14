

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

void print_vector_element(std::vector<int> &vec)
{
	for(auto element = vec.cbegin();element != vec.cend();element++)
	{
		std::cout<<" "<<*element;
	}
	std::cout << std::endl;
	return;
}

int main(int argc, char *argv[])
{
	std::vector<int> vec;

	std::cout << "vec size: " <<vec.size()<<std::endl;
	
	auto it = std::back_inserter(vec);
	*it = 1;

	std::cout << "back_inserter vec size:"<<vec.size()<< std::endl;
	print_vector_element(vec);

	std::fill_n(std::back_inserter(vec), 10, 0);
	std::cout <<"fill_n 10 element, now size: " <<vec.size()<<std::endl;
	print_vector_element(vec);

	return 0;
}
