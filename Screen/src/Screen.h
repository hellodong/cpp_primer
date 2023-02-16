
#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <string>


class Screen{
    public:
        using pos=std::string::size_type;
        Screen() = default;
        Screen(pos ht, pos wd, char c):height(ht),width(wd),contents(ht * wd, c)
        {}
        char get() const
        { return contents[cursor];}
        inline char get(pos r, pos c) const;
        Screen &move(pos r, pos c);
    private:
        pos cursor = 0;
        pos height = 0, width = 0;
        std::string contents;
};


#endif
