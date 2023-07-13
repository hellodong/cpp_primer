

#include <iostream>
#include <algorithm>
#include <vector>


void print_vector_int(std::vector<int> &vec)
{
	for(auto element = vec.cbegin();element != vec.cend();element++)
	{
		std::cout << " " << *element;
	}
	std::cout << std::endl;
}

int main(int argc, char *argv[])
{
	std::vector<int> vec{1,2,3,4,5};

	std::cout << "original vector: ";

	print_vector_int(vec);

	std::fill(vec.begin(), vec.end(), 0);

	std::cout << "fill 0 :";
	print_vector_int(vec);

	std::fill_n(vec.begin(),vec.size() ,1);

	std::cout << "fill_n size 1:";
	print_vector_int(vec);

	return 0;
}
