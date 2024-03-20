
#include <iostream>
#include <functional>


int main(int argc, char *argv[])
{
    std::plus<int> intAdd;
    std::negate<int> intNegate;

    std::cout << "1 + 3: " << intAdd(1,3) << std::endl;
    std::cout << "negate (1+3): " << intNegate(intAdd(1,3)) << std::endl;

    return 0;
}
