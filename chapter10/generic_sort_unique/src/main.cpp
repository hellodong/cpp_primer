

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

void print_vector_str(std::vector<std::string> &str_line)
{
	for(auto element = str_line.cbegin();element != str_line.cend();element++)
	{
		std::cout << *element<<" ";
	}
	std::cout <<std::endl;
}

int main(int argc, char *argv[])
{
	std::vector<std::string> str_line{"the", "red", "fox", "jumpe", "over", "the", "slow", "red", "turtle"};
	print_vector_str(str_line);

	std::sort(str_line.begin(), str_line.end());	
	print_vector_str(str_line);

	auto end_unique = std::unique(str_line.begin(),str_line.end());
	print_vector_str(str_line);

	str_line.erase(end_unique, str_line.end());
	print_vector_str(str_line);

	return 0;
}
