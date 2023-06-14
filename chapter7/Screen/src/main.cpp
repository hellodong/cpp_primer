

#include <iostream>
#include "Screen.h"


int main(void)
{
    Screen screen(2,5,' ');
    screen.move(0,3).set('w');
    std::cout << screen.get()<<std::endl;

    return 0;
}
