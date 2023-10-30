
#include "Sales_data.h"

std::string Sales_data::bookname(void) const
{
    return bookNo;
}

void Sales_data::print(void) const
{
    std::cout << "book No: " << bookNo <<" sold: " << units_sold <<" price: " << price << std::endl;
}

