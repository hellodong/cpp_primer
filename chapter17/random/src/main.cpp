
#include <random>
#include <iostream>


void generate_basic_random(size_t sz)
{
    std::default_random_engine e;
    for (size_t idx = 0;idx < 10;idx++)
    {
        std::cout << e() << " "; 
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    generate_basic_random(10);
    return 0;
}
