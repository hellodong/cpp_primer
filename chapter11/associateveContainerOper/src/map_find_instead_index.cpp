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
		word_count[*input++]++;
	}

	std::cout << "\n" << std::endl;

    for(auto map_it = word_count.begin();map_it != word_count.end();map_it++)
    {
        std::cout << map_it->first;
        std::cout << " " << map_it->second<< std::endl;
    }

    if (0 == word_count["foobar"])
    {
        std::cout << "word_count[foobar] is not in the map" << std::endl;
    }
    else
    {
        std::cout << "word_count[foobar] in map" << std::endl;
    }

    for(auto map_it = word_count.begin();map_it != word_count.end();map_it++)
    {
        std::cout << map_it->first;
        std::cout << " " << map_it->second<< std::endl;
    }
    word_count.erase("foobar");

    if (word_count.find("foobar") == word_count.end())
    {
        std::cout << "word_count.find(foobar) not found in the map" << std::endl;
    }

    for(auto map_it = word_count.begin();map_it != word_count.end();map_it++)
    {
        std::cout << map_it->first;
        std::cout << " " << map_it->second<< std::endl;
    }

	return 0;
}
