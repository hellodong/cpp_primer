
#include "Screen.h"


inline char Screen::get(pos c, pos r) const
{
    return contents[c * width + r];
}

Screen &Screen::move(pos r, pos c)
{
    pos row = r * width;
    cursor = row + c;
    return *this;
}


Screen &Screen::set(char ch)
{
    contents[cursor] = ch;
    return *this;
}

Screen &Screen::set(pos r, pos c, char ch)
{
    contents[r*width + c] = ch;
    return *this;
}
