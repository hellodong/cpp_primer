

#include "Sales_data.h"
#include <iostream>


int main(void)
{
    // 显示转换
    Sales_data item1("cpp_primer", 1, 128.00);
    item1.combine(Sales_data("cpp primer"));
    std::cout << item1 << std::endl;

    //Sales_data item2("effective cpp", 2, 54);
    Sales_data item2;
    std::cin >> item2;
    std::cout << item2 << std::endl;

    std::cout << item1 + item2 << std::endl; 

    item1 += item2;

    std::cout << item1 + item2 << std::endl; 

    return 0;
}

