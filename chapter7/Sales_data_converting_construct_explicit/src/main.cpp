

#include "Sales_data.h"
#include <iostream>


int main(void)
{
    // 显示转换
    Sales_data item1("cpp primer", 1, 128.00);
    item1.combine(Sales_data("cpp primer"));
    std::cout << "sale out count: "<<item1.units_sold << std::endl;

    //static_cast强转换
    Sales_data item2("effective cpp", 2, 54);
    item2.combine(static_cast<Sales_data>(std::cin));
    std::cout <<item2.bookNo <<" sale out count: "<<item2.units_sold << std::endl;

    return 0;
}

