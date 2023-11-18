

#include <fstream>
#include <iterator>
#include <unordered_map>
#include <string>
#include <iostream>

int main(int argc ,char *argv[])
{
    std::ifstream input(argv[1]);
    std::istream_iterator<std::string>  istream(input), eof;

    std::unordered_map<std::string, size_t> word_count;
    while(istream != eof)
    {
        ++word_count[*istream++];
    }

    for(const auto &w:word_count)
    {
        std::cout << w.first << " occours " << w.second <<" times" << std::endl;
    }
    return 0;
}
