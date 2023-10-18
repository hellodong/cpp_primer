
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
	std::string path(argv[1]);
	std::vector<std::string> words;
	TextDecode txtDecode(path, &words);
	
	txtDecode.dump();

	for_each(words.begin(), words.end(), std::bind(print, std::ref(std::cout), std::placeholders::_1, ' '));

	return 0;
}
