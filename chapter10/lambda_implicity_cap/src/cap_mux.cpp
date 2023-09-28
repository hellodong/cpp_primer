

#include <iostream>
#include <string>
#include <fstream>
#include <vector>


int main(int argc, char *argv[])
{
	std::string temp_input;
	std::fstream input(argv[1], std::ios::in);
    if (!input.is_open())
    {
	    std::cout << "open " << argv[1] << " error"<<std::endl;
	    return -1;
    }
    while(!input.eof())
    {
	  temp_input = input.get();
	  std::cout << temp_input <<"   ";
    }
    std::cout << std::endl;
    return 0;
}
