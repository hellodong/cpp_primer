

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

    std::cout << "bucket count " << word_count.bucket_count() << std::endl;

    for(size_t idx = 0;idx < word_count.bucket_count();idx++)
    {
        for (auto w = word_count.cbegin(idx);w != word_count.cend(idx);w++)
        {
            std::cout << w->first << std::endl;
        }
    }
    return 0;
}
