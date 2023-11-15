

#include <set>
#include <iostream>

int main(int argc, char *argv[])
{
    std::set<int> iset{0,1,2,3,4,5,6,7,8,9};
    
    std::cout << *iset.find(1) << std::endl;
    if (iset.find(10) == iset.end())
    {
        std::cout <<"oops:" << 10 << " not found" << std::endl;
    }
    else
    {
        std::cout << *iset.find(10) << std::endl;
    }
    std::cout << iset.count(1) << std::endl;
    std::cout << iset.count(10) << std::endl;
    return 0;
}
