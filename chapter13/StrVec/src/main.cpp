

#include "strVec.h"
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "please input more parameter"<< std::endl;
        return 0;
    }
    StrVec sv;

    for(int idx = 1; idx < argc;idx++)
    {
        sv.push_back(argv[idx]);
    }

    return 0;
}
