

#include <iostream>
#include <vector>
#include <set>

int main(int argc, char *argv[])
{
    std::set<int> iset;

    iset.insert({1,2,3,4,5,6});

    for(auto set_it=iset.begin();set_it !=iset.end();set_it++)
    {
        std::cout <<*set_it<< " ";
    }
    std::cout << std::endl;

    for (const auto set_it:iset)
    {
        std::cout << set_it<<" ";
    }

    std::cout << std::endl;
    return 0;
}
