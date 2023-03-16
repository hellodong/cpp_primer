

#include "Sales_data.h"
#include <iostream>


int main(void)
{
    //只允许一步类型转换
    std::string null_book("cpp primer");
    Sales_data total("cpp primer", 1, 128.00);
    total.combine(null_book);
    std::cout << "sale out count: "<<total.units_sold << std::endl;

    //类型转换不是有效的
    Sales_data total2("effective cpp", 2, 54);
    total2.combine(std::cin);


    std::cout <<total2.bookNo <<" sale out count: "<<total.units_sold << std::endl;

    return 0;
}

