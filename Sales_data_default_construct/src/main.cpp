

#include "Sales_data.h"


int main(void)
{
    Sales_data total;
    Sales_data trans;

    total = trans;
    print(std::cout, total) << std::endl;

    read(std::cin, trans);
    total = trans;
    print(std::cout, total) << std::endl;

    return 0;
}

