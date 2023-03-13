
#include "Sales_data.h"


std::ostream &print(std::ostream &os, const Sales_data &entry)
{
    os << "bookNo " << entry.bookNo << " units_sold:" << entry.units_sold << "revenue" << entry.revenue;
    return os;
}

std::istream &Sales_data::read(std::istream &is)
{
    double price = 0;
    is >> bookNo >> units_sold >> price; 
    if (units_sold)
    {
        revenue = units_sold * price;
    }
    return is;
}
