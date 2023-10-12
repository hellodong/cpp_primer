
#include <iostream>
#include <functional>
#include <algorithm>

#include "textDecode.h"


int check_size(const std::string &str, int sz)
{
	return str.size() > sz;
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

	auto wc = std::find_if(words.begin(), words.end(), std::bind(check_size, std::placeholders::_1, 4));

	if (wc != words.end())
	{
		std::cout << *wc << std::endl;
	}
	else
	{
		std::cout << "not found > 4 size word" << std::endl;
	}

	return 0;
}
