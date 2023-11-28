

#include <memory>
#include <iostream>


void shared_ptr_destroy(std::shared_ptr<int> &ival)
{
    std::shared_ptr<int> p = std::make_shared<int> (42);
    auto q(p);
    std::cout << *q << std::endl;
    ival = p;
}

int main(int argc, char *argv[])
{
    std::shared_ptr<int> p1;

    if (p1)
    {
        *p1 = 42;
        std::cout << *p1 << std::endl;
    }

    std::shared_ptr<int> p;
    shared_ptr_destroy(p);
    std::cout << "p: "  << *p << std::endl;
    return 0;
}

