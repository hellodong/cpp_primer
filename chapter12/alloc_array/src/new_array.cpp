

#include <iostream>
#include <string>
#include <memory>


int main(int argc, char *argv[])
{
    int *pia = new int[10]();
    std::cout << "allocate array[10] with default initialize"<< std::endl;

    for (int idx = 0;idx < 10;idx++)
    {
        std::cout <<pia[idx] <<" ";
    }
    std::cout << std::endl;

    int *pia2 = new int[10]{0, 1,2,3,4,5,6,7,8,9};
    std::cout << "allocate array[10] with intialazer"<<std::endl;
    for (int idx = 0;idx != 10; idx++)
    {
        std::cout << pia2[idx]<< " ";
    }
    std::cout << std::endl;

    std::string *psa2 = new std::string[10]();
    std::cout << "allocate string[10] with default initialize" << std::endl;
    for (int idx = 0;idx != 10; idx++)
    {
        std::cout << psa2[idx] << " ";
    }
    std::cout << std::endl;

    int *pia3 = new int[10]{0, 1,2,3,4,5};
    std::cout << "allocate array[10] with intialazer not full"<<std::endl;
    for (int idx = 0;idx != 10; idx++)
    {
        std::cout << pia3[idx]<< " ";
    }
    std::cout << std::endl;

    std::string *psa3 = new std::string[10] {"c++", "primer", std::string(3,'x')};
    std::cout << "allocate string[10] with initializer not full" << std::endl;
    for (int idx = 0;idx != 10;idx++)
    {
        std::cout << psa3[idx] <<" ";
    }
    std::cout << std::endl;


    return 0;
}
