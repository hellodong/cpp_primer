
#include "Sales_data.h"


std::ostream &print(std::ostream &os, const Sales_data &data)
{
    os <<"bookNo:"<< data.bookNo << ", sold:" << data.units_sold << ", price:" << data.price << std::endl;
    return os;
}
