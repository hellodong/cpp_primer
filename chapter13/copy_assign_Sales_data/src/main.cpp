

#include "Sales_data.h"
#include <iostream>


int main(void)
{
    std::cout <<"sale_data_all(\"cpp primer\", 1, 128.00)" << std::endl;
    Sales_data sale_data_all("cpp primer", 1, 128.00);
    print(std::cout, sale_data_all);

    std::cout <<"\r\n=========================================================" << std::endl;
    std::cout <<"copy initialization" << std::endl;
    Sales_data copy_sales = sale_data_all;
    print(std::cout, copy_sales);

    std::cout <<"\r\n=========================================================" << std::endl;

    std::cout <<"operator copy assign " << std::endl;
    Sales_data copy_assign;
    copy_assign = sale_data_all;
    print(std::cout, copy_assign);

    return 0;
}

