

#ifndef _VARIDICAL_TEMPT_
#define _VARIDICAL_TEMPT_


#include <iostream>

template <typename T>
std::ostream &_print(std::ostream &os, const T &t)
{
    return os << t << std::endl;
}

template <typename T, typename... Args>
std::ostream &_print(std::ostream &os, const T &t, const Args&... rest)
{
    os << t << ", ";
    return _print(os, rest...);
}

template <typename... Args>
std::ostream &print(std::ostream &os, const Args&... rest)
{
    os <<"type: " <<sizeof...(Args) <<", parameter: " << sizeof...(rest) << std::endl;
    return _print(os, rest...);
}


#endif
