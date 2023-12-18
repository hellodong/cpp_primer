

#include <iostream>
#include <string>
#include <memory>
#include <new>

typedef int arrT[10];

void _unique_array(int _num)
{
    std::unique_ptr<int[]> up(new int [_num]());

    std::cout << "Unique_ptr manage up[" <<_num <<"]" <<std::endl;
    for(int idx = 0;idx != _num;idx++)
    {
        std::cout << up[idx] << " ";
    }
    std::cout << std::endl; 
}

void _shared_array(int _num)
{
    std::shared_ptr<int[]> sp(new int [_num](), [] (int *p){delete [] p;});
    std::cout << "Shared_ptr manage sp["<<_num<<"]" << std::endl;
    for (int idx = 0;idx < _num;idx++)
    {
        std::cout << sp[idx] << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    int *pia = new int[10]();
    std::cout << "allocate array[10] with default initialize"<< std::endl;

    for (int idx = 0;idx < 10;idx++)
    {
        std::cout <<pia[idx] <<" ";
    }
    delete [] pia;
    pia = nullptr;
    std::cout << std::endl;
    

    int *pa = new arrT;
    std::cout << "Allocate arrT" << std::endl;
    for (int idx = 0;idx != 10;idx++)
    {
        std::cout << pa[idx] << " ";
    }
    delete [] pa;
    pa = nullptr;
    std::cout << std::endl;

    int *pia2 = new int[10]{0, 1,2,3,4,5,6,7,8,9};
    std::cout << "allocate array[10] with intialazer"<<std::endl;
    for (int idx = 0;idx != 10; idx++)
    {
        std::cout << pia2[idx]<< " ";
    }
    delete [] pia2;
    pia2 = nullptr;
    std::cout << std::endl;

    std::string *psa2 = new std::string[10]();
    std::cout << "allocate string[10] with default initialize" << std::endl;
    for (int idx = 0;idx != 10; idx++)
    {
        std::cout << psa2[idx] << " ";
    }
    delete [] psa2;
    psa2 = nullptr;
    std::cout << std::endl;

    int *pia3 = new int[10]{0, 1,2,3,4,5};
    std::cout << "allocate array[10] with intialazer not full"<<std::endl;
    for (int idx = 0;idx != 10; idx++)
    {
        std::cout << pia3[idx]<< " ";
    }
    delete [] pia3;
    pia3 = nullptr;
    std::cout << std::endl;

    std::string *psa3 = new std::string[10] {"c++", "primer", std::string(3,'x')};
    std::cout << "allocate string[10] with initializer not full" << std::endl;
    for (int idx = 0;idx != 10;idx++)
    {
        std::cout << psa3[idx] <<" ";
    }
    //delete [] psa3;
    psa3 = nullptr;
    std::cout << std::endl;

    _unique_array(12);

    _shared_array(8);

    return 0;
}
