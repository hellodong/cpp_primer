

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

    auto map_it = word_count.begin();
    std::cout << map_it->first;
    std::cout << "second: " << map_it->second;
	std::cout << std::endl;

    for(const auto map_ref:word_count)
    {
        std::cout << map_ref.first <<" : " << map_ref.second << std::endl;
    }

    std::cout << std::endl;
    //3 method insert
    word_count.insert({std::string("a"),1});
    word_count.insert(std::make_pair(("an"),2));
    //word_count.insert(std::map<std::string, size_t>(std::string("and"),3UL));
    word_count.insert(std::map<std::string, size_t>::value_type("And",4));
    for(const auto map_ref:word_count)
    {
        std::cout << map_ref.first <<" : " << map_ref.second << std::endl;
    }

    std::cout << std::endl;
	return 0;
}
