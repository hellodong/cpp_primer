
#ifndef _SALES_DATA_H_
#define _SALES_DATA_H_

#include <iostream>
#include <string>


class Sales_data{
    friend std::ostream & operator<<(std::ostream &os, const Sales_data &rhm);
    friend std::istream & operator>>(std::istream &is, Sales_data &rhm);
    friend Sales_data operator+(const Sales_data &lhm,const Sales_data &rhm);
public:
	Sales_data(std::string s, unsigned int cnt, double price):bookNo(s),units_sold(cnt),revenue(cnt * price) {}
	Sales_data():Sales_data("", 0,0.0) { }
	explicit Sales_data(std::string s):Sales_data(s,0,0.0) { }

	Sales_data &combine(const Sales_data &);
    	Sales_data &operator+=(const Sales_data &rhm);
private:
    std::string bookNo;
    unsigned int units_sold=0;
    double revenue = 0.0;
};

#endif

