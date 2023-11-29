

#include <iostream>
#include <string>
#include <vector>


void __new_no_arg(void)
{
    int *pi = new int;
    std::string *ps = new std::string;

    std::cout << "\r\nnew without arg:" << std::endl;
    std::cout << "new int " << *pi << std::endl;
    std::cout << "new string " << *ps << std::endl;

    delete pi;
    delete ps;
}

void __new_with_arg(int ival)
{
    int *pi = new int(ival);
    std::string *ps = new std::string(ival,'*');
    std::vector<int> *pv = new std::vector<int> {0,1,2,3,4,5,6,7,8};

    std::cout << "\r\nnew with arg:" << std::endl;
    std::cout << "new int " << *pi << std::endl;
    std::cout << "new string " << *ps << std::endl;
    std::cout << "new vector " << pv->size() << std::endl;

    delete pi;
    delete ps;
    delete pv;
}

void __new_init_value(void)
{
    int *pi1 = new int;
    int *pi2 = new int();
    std::string *ps1 = new std::string;
    std::string *ps2 = new std::string();

    std::cout << "\r\n new init value:" << std::endl;
    std::cout << "new int pi1 " << *pi1 <<std::endl;
    std::cout << "new int pi2(init value)" << *pi2 << std::endl;
    std::cout << "new int ps1 " << *ps1 << std::endl;
    std::cout << "new int ps2(init value)" << *ps2 << std::endl;

    delete pi1;
    delete pi2;
    delete ps1;
    delete ps2;
}

void __new_auto(void)
{
    auto *p1 = new auto(1);
    auto *p2 = new auto("******");

    std::cout << "\r\nnew auto:" << std::endl;
    std::cout <<"new auto p1 " << *p1 << std::endl;
    std::cout << "new auto p2 " << *p2 << std::endl;

    delete p1;
    delete p2;
}

void __new_const(void)
{
    const int *pi = new const int(1);
    const std::string *ps = new const std::string;

    std::cout << "\r\nnew const:" << std::endl;
    std::cout << "new const pi " << *pi << std::endl;
    std::cout << "new const ps" << *ps << std::endl;

    delete pi;
    delete ps;
}

int main(int argc, char *argv[])
{
    __new_with_arg(9);
    __new_init_value();
    __new_no_arg();
    __new_auto();
    __new_const();

    return 0;
}
