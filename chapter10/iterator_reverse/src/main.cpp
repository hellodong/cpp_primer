
#include <iostream>
#include <functional>
#include <algorithm>

#include "textDecode.h"


int main(int argc, char *argv[])
{
	std::string path(argv[1]);
	std::vector<std::string> words;
	TextDecode txtDecode(path, &words);
	
	txtDecode.dump();

	auto str_rstart = words.begin()->crbegin();
	auto str_rend = words.begin()->crend();

	auto rcomma = std::find(str_rstart, str_rend,',');
	std::cout << std::string(str_rend.base(), rcomma.base() - 1) << std::endl;
	std::cout << std::string(rcomma.base(), words.begin()->cend()) << std::endl;

	return 0;
}
