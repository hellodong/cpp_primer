

#include "Sales_data.h"


//output
std::ostream & operator<<(std::ostream &os, const Sales_data &entry)
{
    os << "bookNo: " << entry.bookNo << ", units_sold:" << entry.units_sold << ", revenue" << entry.revenue;
    return os;
}

//input
std::istream & operator>>(std::istream &is, Sales_data &rhm)
{
    double price = 0;
    is >> rhm.bookNo >> rhm.units_sold >> price;
    rhm.revenue = rhm.units_sold * price;
    return is;
}

Sales_data operator+(const Sales_data &lhm, const Sales_data &rhm)
{
    Sales_data tmp(lhm);

    if (lhm.bookNo != rhm.bookNo)
    {
        return tmp;
    }

    tmp.units_sold += rhm.units_sold;
    tmp.revenue += rhm.revenue;
    return tmp;
}

Sales_data &Sales_data::operator+=(const Sales_data &rhm)
{
    if (bookNo != rhm.bookNo)
    {
        return *this;
    }

    units_sold += rhm.units_sold;
    revenue +=rhm.revenue;
    return *this;
}

Sales_data &Sales_data::combine(const Sales_data &item)
{
    if (bookNo != item.bookNo)
    {
        return *this;
    }
    units_sold += item.units_sold;
    revenue += item.revenue;

    return *this;
}

