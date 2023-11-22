

#include <memory>
#include <iostream>


int main(int argc, char *argv[])
{
    std::shared_ptr<int> p1;

    if (p1)
    {
        *p1 = 42;
        std::cout << *p1 << std::endl;
    }
    return 0;
}

