
#include "Sales_data.h"

Sales_data::Sales_data() = default;

std::ostream &print(std::ostream &os, const Sales_data &entry)
{
    os << "bookNo " << entry.bookNo << " units_sold:" << entry.units_sold << "revenue" << entry.revenue;
    return os;
}

std::istream &read(std::istream &is, Sales_data &entry)
{
    double price = 0;
    is >> entry.bookNo >> entry.units_sold >> price; 
    if (entry.units_sold)
    {
        entry.revenue = entry.units_sold * price;
    }
    return is;
}
