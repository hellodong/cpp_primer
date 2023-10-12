
#include <iostream>
#include <functional>
#include <algorithm>

#include "textDecode.h"

std::ostream &print(std::ostream &os, std::string &str, char c)
{
	return os << str << c;
}


int main(int argc, char *argv[])
{
	class TextDecode txtDecode(argv[1]);
	std::vector<std::string> words;
	if (!txtDecode.is_open())
	{
		std::cout << "can't open" << argv[1] << std::endl;
		return 0;
	}
	txtDecode.decode();
	txtDecode.dump();
	txtDecode.copy(words);

	std::for_each(words.begin(), words.end(), std::bind(print, std::ref(std::cout), std::placeholders::_1, ' '));

	return 0;
}
