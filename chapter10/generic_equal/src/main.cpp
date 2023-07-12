

#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>

bool is_rostor_equal(std::vector<std::string> &vec_str, std::list<const char *> &list_ch)
{
    return std::equal(vec_str.cbegin(), vec_str.cend(), list_ch.cbegin());
}

int main(int argc, char *argv[])
{
    std::vector<std::string> vec_str{"cpp", "primer", "hello"};
    std::list<const char *>list_ch{"cpp", "primer", "hello "};
    std::cout <<"compare vector<string> with list<char>: "  << is_rostor_equal(vec_str, list_ch) << std::endl;
    return 0;
}
