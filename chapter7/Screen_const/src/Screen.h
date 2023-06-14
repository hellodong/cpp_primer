
#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <string>


class Screen{
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
