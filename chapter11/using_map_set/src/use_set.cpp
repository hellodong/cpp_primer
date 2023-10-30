

#include <map>
#include <set>
#include <fstream>
#include <iterator>
#include <string>
#include <iostream>


int main(int argc, char *argv[])
{
	std::ifstream file(argv[1]);
	std::istream_iterator<std::string> input(file), eof;
	std::map<std::string, size_t> word_count;
	std::set<std::string> exclud{"The","And", "But","Or",
				     "the","and", "but","or"};

	while (input != eof)
	{
		std::cout <<" " << *input;
		if (exclud.find(*input) != exclud.end())
		{
			word_count[*input]++;
		}
		input++;
	}
	std::cout << "\n" << std::endl;
	for (const auto &w:word_count)
	{
		std::cout << w.first << " occurs " << w.second << " times" << std::endl;
	}
	return 0;
}
