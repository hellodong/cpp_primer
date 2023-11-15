

#include <map>
#include <fstream>
#include <iterator>
#include <string>
#include <iostream>


int main(int argc, char *argv[])
{
	std::ifstream file(argv[1]);
	std::istream_iterator<std::string> input(file), eof;
	std::map<std::string, size_t> word_count;

	while (input != eof)
	{
		std::cout <<" " << *input;
		auto ret = word_count.insert({*input, 1});
        if (!ret.second)
        {
            ++ret.first->second;
        }
        input++;
	}

	std::cout << "\n" << std::endl;

    for (auto map_ref:word_count)
    {
        std::cout << map_ref.first <<" second:" << map_ref.second << std::endl;
    }
	return 0;
}
