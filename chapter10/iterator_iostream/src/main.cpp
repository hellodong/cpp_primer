
#include <iostream>
#include <fstream>
#include <iterator>
#include <functional>
#include <algorithm>
#include <vector>


std::ostream &print(std::ostream &os, std::string &str, char c)
{
	return os << str << c;
}


int main(int argc, char *argv[])
{
	std::ifstream number_fstream(argv[1]);
	std::istream_iterator<int> int_input(number_fstream), int_eof;
	std::ofstream odd_output("./odd.txt", std::ios::out|std::ios::trunc), even_output("./even.txt", std::ios::out|std::ios::trunc);
	std::ostream_iterator<int> odd_osteam(odd_output, " "), even_ostream(even_output, " ");
	while(int_input !=int_eof )
	{
		if (*int_input % 2 == 0)
		{
			*even_ostream++ = *int_input++; 
		}
		else
		{
			*odd_osteam++ = *int_input++;
		}
	}

	return 0;
}
