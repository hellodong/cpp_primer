

#ifndef _WINDOW_MNG_H_
#define _WINDOW_MNG_H_


#include <vector>
#include <string>


class Screen;

class Window_mng{
    public:
        using ScreenIndex = std::vector<Screen>::size_type;       
        Window_mng();
        void clear(ScreenIndex);
        ScreenIndex addScreen(const Screen &s);
    private:
        std::vector<Screen> screens;
};

class Screen{
    friend void Window_mng::clear(ScreenIndex);
    public:
        using pos=std::string::size_type;
        Screen() = default;
        Screen(pos ht, pos wd, char c=' '):height(ht),width(wd),contents(ht * wd, c)
        {}
        Screen &set(char ch);
        Screen &set(pos r, pos c, char ch);
        Screen &display(std::ostream &os)
        {
            do_display(os);
            return *this;
        }
        const Screen &display(std::ostream &os) const
        {
            do_display(os);
            return *this;
        }
    private:
        pos cursor = 0;
        pos height = 0, width = 0;
        std::string contents;
        void do_display(std::ostream &os) const
        {
            os << contents;
        }
};


#endif
