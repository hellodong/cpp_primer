

#include "Sales_data.h"
#include <iostream>


int main(void)
{
    std::cout <<"sale_data_all(\"cpp primer\", 1, 128.00)" << std::endl;
    Sales_data sale_data_all("cpp primer", 1, 128.00);

    std::cout <<"=========================================================" << std::endl;

    std::cout <<"dft" << std::endl;
    Sales_data dft;

    std::cout <<"=========================================================" << std::endl;

    std::cout <<"sale_data_str(\"cpp primer\")" << std::endl;
    Sales_data sale_data_str("cpp primer");

    std::cout <<"=========================================================" << std::endl;

    std::cout <<"sale_data_cin(std::cin)" << std::endl;
    Sales_data sale_data_cin(std::cin);

    return 0;
}

