

#include <vector>
#include <string>

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

Window_mng::Window_mng():screens{Screen(20,50)}
{}

void Window_mng::clear(ScreenIndex idx)
{
    Screen &s = screens[idx];
    s.contents = std::string(s.height * s.width, ' ');
}

Window_mng::ScreenIndex Window_mng::addScreen(const Screen &s)
{
    screens.push_back(s);
    return screens.size() - 1;
}

