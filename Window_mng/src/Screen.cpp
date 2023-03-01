

#include "Window_mng.h"


Screen &Screen::set(char ch)
{
    contents[cursor] = ch;
    return *this;
}

Screen &Screen::set(pos r, pos c, char ch)
{
    contents[r * width + c] = ch;
    return *this;
}

void Window_mng::clear(ScreenIndex idx)
{
    Screen &s = screens[idx];
    s.contents = std::string(s.height * s.width, ' ');
}

