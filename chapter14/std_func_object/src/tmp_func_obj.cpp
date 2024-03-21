
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>


int main(int argc, char *argv[])
{
    std::vector<std::string> svec;

    std::cout << "argc:  " << argc << std::endl;
    for (int idx = 1; idx < argc; idx++)
    {
        std::cout << argv[idx];
        if (idx % 8 == 0)
        {
            std::cout << "\n";
        }
        else
        {
            std::cout << " ";
        }
        svec.push_back(argv[idx]);
    }

    std::cout << std::endl << "sort svec: " << std::endl;

    std::sort (svec.begin(), svec.end(), std::greater<std::string>());

    for (auto iterate = svec.begin(); iterate != svec.end();iterate++)
    {
        std::cout << *iterate  << " ";
    }

    std::cout << std::endl;

    return 0;
}
