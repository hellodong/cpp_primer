

#include <iostream>
#include "Screen.h"


int main(void)
{
    Screen screen(2,5,' ');
    const Screen blank(2,5);

    screen.set('#').display(std::cout);
    std::cout << std::endl;
    blank.display(std::cout);
    std::cout << std::endl;

    return 0;
}
