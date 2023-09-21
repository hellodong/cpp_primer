

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

bool is_shorter(const std::string &s1, const std::string &s2)
{
	return s1.size() < s2.size();
}

void print_vector(std::vector<std::string> &vec_str)
{
	for(auto element =vec_str.cbegin();element != vec_str.cend();element++)
	{
		std::cout << *element <<" ";
	}
	std::cout <<std::endl;
	return;
}

int main(int argc, char *argv[])
{
	std::vector<std::string> vec_str{"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};
	std::sort(vec_str.begin(), vec_str.end());
	print_vector(vec_str);	

	std::stable_sort(vec_str.begin(), vec_str.end(), is_shorter);
	print_vector(vec_str);	

	return 0;
}
