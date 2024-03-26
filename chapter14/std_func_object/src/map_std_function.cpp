

#include <iostream>
#include <functional>
#include <string>
#include <map>

struct Divide
{
    int operator() (int i, int j)
    {
        return i / j;
    }
};

int add(int i, int j)
{
    return i+j;
}

void usage (void)
{
    std::cout << " +/-/x/% arg1 arg2" << std::endl;
}

int main(int argc, char *argv[])
{
    auto mode = [](int i, int j) {return i % j;};
    std::map<std::string, std::function<int (int, int)>> binops = {
        {"+", add},
        {"-", std::minus<int>()},
        {"/", Divide()},
        {"*", [](int i, int j){return i * j;}},
        {"%", mode}
    };

#if 0
    if (argc < 4)
    {
        usage();
        return -1;
    }
#endif

    std::cout <<"10 + 5 = " << binops["+"](10, 5) << std::endl;
    std::cout <<"10 - 5 = " << binops["-"](10,5) << std::endl;
    std::cout <<"10 x 5 = " << binops["*"](10,5) << std::endl;
    std::cout <<"10 / 5 = " << binops["/"](10,5) << std::endl;
    std::cout <<"10 % 5 = " << binops["%"](10,5) << std::endl;

    return 0;
}
