

#include <iostream>
#include <fstream>

#include "txt_query.h"
#include "query_rslt.h"

void print(QueryRslt qr)
{
    if (qr.lines)
    {
        std::cout << qr.sout << " occurs " << qr.lines->size() <<" time(s):" << std::endl;
        for (auto line : *qr.lines)
        {
            std::cout << line <<": " << *(qr.v_file->cbegin() + line -1) << std::endl;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "please input " << argv[0] << " <txt file>" << std::endl;
        return -1;
    }
    std::ifstream ifile(argv[1]);
    if (!ifile.is_open())
    {
        std::cout <<"can't open " << argv[1] << std::endl;
        return -1;
    }

    TxtQuery txt(ifile); 

    while(true)
    {
        std::cout << "please input what look for:" <<std::endl;
        std::string word;
        if(std::cin >> word)
        {
            if (word == "q")
            {
                std::cout << "quit this process" << std::endl;
                break;
            }

            print(txt.query(word));
        }
    }
    return 0;
}
