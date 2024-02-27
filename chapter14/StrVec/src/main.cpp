

#include "strVec.h"

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
    std::cout <<"sv:     "<< sv;

    StrVec sv2(sv);
    std::cout << "sv2:    "<< sv2;

    StrVec sv3;
    sv3 = sv;
    std::cout <<"sv3:    " <<sv3;

    StrVec sv4;
    sv4 = {"first", "second", "third"};
    std::cout <<"sv4:    " <<sv4;

    std::cout <<"sv4[0]: " << sv4[0] << std::endl;
    std::cout << "sv4[1]: " << sv4[1] << std::endl;
    std::cout << "sv4[2]: " << sv4[2] << std::endl;

    return 0;
}
