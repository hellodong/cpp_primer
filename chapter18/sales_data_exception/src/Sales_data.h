
#ifndef _SALES_DATA_H_
#define _SALES_DATA_H_

#include <iostream>
#include <string>
#include <stdexcept>
#include <functional>

class Sales_data{
    friend std::ostream & operator<<(std::ostream &os, const Sales_data &rhm);
    friend std::istream & operator>>(std::istream &is, Sales_data &rhm);
    friend Sales_data operator+(const Sales_data &lhm,const Sales_data &rhm);
    friend bool operator==(const Sales_data &lhs, const Sales_data &rhs);
    friend bool operator !=(const Sales_data &lhs, const Sales_data &rhs);
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

class out_of_stock : public std::runtime_error 
{
public:
    explicit out_of_stock(const std::string& s) :std::runtime_error(s) {}
};

class isbn_mismatch :public std::logic_error
{
public:
    explicit isbn_mismatch(const std::string& s) :std::logic_error(s) {}
    isbn_mismatch(const std::string& s, const std::string& lhs, const std::string& rhs) : std::logic_error(s), left(lhs), right(rhs) {}
    const std::string left, right;
};

#endif

