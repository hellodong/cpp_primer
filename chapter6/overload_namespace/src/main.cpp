

#include <iostream>

void print(const std::string &strval)
{
    std::cout<<"print string " << strval << std::endl;
}

void print(int ival)
{
    std::cout<<"print int value " << ival << std::endl;
}

void print(double dval)
{
    std::cout << "print double value" << dval << std::endl;
}

int main(void)
{
    print("Value: ");
    print(45);
    print(3.14);
    return 0;
}
