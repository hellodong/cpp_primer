
#include <regex>
#include <string>
#include <iostream>


void regex_basic(void)
{
    std::regex r("[[:alnum:]]+\\.(cpp|cxx|cc)", std::regex::icase);
    std::smatch resultes;
    std::string filename;
    while(std::cin >> filename && filename != "q")
    {
        if (std::regex_search(filename, resultes, r))
        {
            std::cout << resultes.str() << std::endl; 
        }
    }
    std::cout <<"quit regex_basic mode" << std::endl;
}

int regex_error(void)
{
    std::regex r;
    try{
        std::regex re("[[:alnum:]+\\.(cpp|cxx|cc)", std::regex::icase);
        r = re;
    } catch(std::regex_error e)
    {
        std::cout << e.what() << "\r\nCode:" << e.code() << std::endl;
        return -(e.code());
    }
    std::smatch resultes;
    std::string filename;
    while(std::cin >> filename && filename != "q")
    {
        if (std::regex_search(filename, resultes, r))
        {
            std::cout << resultes.str() << std::endl; 
        }
    }
    std::cout <<"quit regex_basic mode" << std::endl;
    return 0;
}


int main(int argc, char *argv[])
{
    regex_basic();
    regex_error();
    return 0;
}

