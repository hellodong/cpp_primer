

#include <iostream>
#include <fstream>
#include <iterator>

#include <stdlib.h>


int main(int argc, char *argv[])
{
	std::ofstream odd_ofstream(argv[1], std::ios::out | std::ios::trunc);
	std::ofstream even_ofstream(argv[2], std::ios::out | std::ios::trunc);
	std::ostream_iterator<int> odd_ostr(odd_ofstream, " "), even_ostr(even_ofstream, " ");

	int start_idx = atoi(argv[3]), len = atoi(argv[4]);
	len += start_idx;

	for(;start_idx < len;start_idx++)
	{
		if (start_idx % 2 == 1)
		{
			*odd_ostr++ = start_idx;
		}
		else
		{
			*even_ostr++ = start_idx;
		}
	}

	std::cout << "generate odd and even done." << std::endl;
	return 0;
}

