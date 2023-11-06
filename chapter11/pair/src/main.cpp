

#include <utility>
#include <string>
#include <vector>
#include <iostream>


int main(int argc, char *argv[])
{
    std::pair<int, std::string> once{123, "123"};
    std::pair<std::string, std::vector<int>> str2ivec;

    std::cout << once.first << "occurs" << once.second << std::endl;

    return 0;
}


