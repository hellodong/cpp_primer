

#include <iostream>
#include <string>

char &get_value(std::string &str, std::string::size_type idx)
{
	return str[idx];
}

int main(int argc, char *argv[])
{
	std::string str("a word");
	std::cout << str<< std::endl;
	get_value(str, 0) = 'A';
	std::cout << str<<std::endl;
	return 0;
}
