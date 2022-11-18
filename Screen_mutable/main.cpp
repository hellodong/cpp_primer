

#include <iostream>

#include "Screen.h"


int main(void)
{
    Screen entry;
    std::cout << "1 " << entry.get_some_memb() << std::endl;
    entry.some_memb();
    std::cout << "2 " << entry.get_some_memb() << std::endl;
    return 0;
}
