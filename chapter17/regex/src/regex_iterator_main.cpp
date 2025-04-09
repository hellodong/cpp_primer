

#include <regex>
#include <string>
#include <vector>
#include <iostream>

void regex_it_str(const std::string &str)
{
    std::string pattern("[^c]ei");
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    std::regex r(pattern, std::regex::icase);
    for (std::sregex_iterator it(str.begin(), str.end(), r), end_it; it != end_it;it++)
    {
        std::cout << it->str() << std::endl;
    }

}

#if 0
void regex_it_vec(const std::vector<std::string> &str)
{
    std::string pattern("[^c]ei");
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    std::regex r(pattern, std::regex::icase);
    for (std::sregex_iterator it(str.begin(), str.end(), r), end_it; it != end_it;it++)
    {
        std::cout << it->str() << std::endl;
    }
}
#endif

int main(int argc, char *argv[])
{
    std::string str("receipt freind theif receive");
    std::vector<std::string> vec_str={"receipt", "freind","theif","receive"};

    regex_it_str(str);


    return 0;
}
