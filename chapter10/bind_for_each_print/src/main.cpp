
#include <iostream>
#include <string>
#include <functional>
#include <algorithm>

#include "textDecode.h"

std::ostream &print(std::ostream &os, std::string &str, char c)
{
	return os << str << c;
}


int main(int argc, char *argv[])
{
	std::string path(argv[1]);

	TextDecode txtDecode(path);
	if (false == txtDecode.is_open())
	{
		std::cout << "can't open" << argv[1] << std::endl;
		return 0;
	}
	txtDecode.decode();
	txtDecode.dump();

	std::vector<std::string> words;
	txtDecode.copy(words);

	for_each(words.begin(), words.end(), std::bind(print, std::ref(std::cout), std::placeholders::_1, ' '));

	return 0;
}
