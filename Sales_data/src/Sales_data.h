
#ifndef _SALES_DATA_H_
#define _SALES_DATA_H_

#include <iostream>
#include <string>


struct Sales_data{
    std::string bookNo;
    unsigned int units_sold=0;
    double revenue = 0.0;
};

std::ostream &print(std::ostream &os, const Sales_data &entry);

std::istream &read(std::istream &is, Sales_data &entry);


#endif

