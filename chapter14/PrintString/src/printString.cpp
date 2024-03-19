

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


class PrintString{
    public:
        PrintString(std::ostream &lhs = std::cout, char rhs = ' '):os(lhs), sep(rhs)
        {}
        std::ostream &operator()(std::string str) const
        {
            return os<< str << sep;
        }
    private:
        std::ostream &os;
        char sep;
};


int main(int argc, char *argv[])
{
    PrintString print;

    print("hello");

    std::cout << std::endl << std::endl;

    
    std::vector<std::string> vs;
    for(int idx = 1; idx < argc;idx++)
    {
        vs.push_back(argv[idx]); 
    }
    std::cout << "output "<< argc -1 << " word(s) :"<< std::endl;

    std::for_each(vs.begin(), vs.end(), PrintString(std::cout, '\n'));

    return 0;
}
