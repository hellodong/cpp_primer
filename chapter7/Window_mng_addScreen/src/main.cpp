

#include <iostream>

#include "Window_mng.h"


int main(void)
{
    Window_mng window;
    Screen s;

    window.clear(0);

    std::cout << window.addScreen(s)<<std::endl;

    return 0;
}
