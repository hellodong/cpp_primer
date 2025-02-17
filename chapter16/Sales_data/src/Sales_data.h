
#ifndef _SALES_DATA_H_
#define _SALES_DATA_H_

#include <iostream>
#include <string>
#include <functional>

//template <class T> class std::hash;

//template<> struct std::hash<Sales_data>;

class Sales_data{
    friend std::ostream & operator<<(std::ostream &os, const Sales_data &rhm);
    friend std::istream & operator>>(std::istream &is, Sales_data &rhm);
    friend Sales_data operator+(const Sales_data &lhm,const Sales_data &rhm);
    friend bool operator==(const Sales_data &lhs, const Sales_data &rhs);
    friend bool operator !=(const Sales_data &lhs, const Sales_data &rhs);
    friend class std::hash<Sales_data>;
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

namespace std{
    template<> struct hash<Sales_data>
    {
        typedef size_t result_type;
        typedef Sales_data argument_type;
        size_t operator()(const Sales_data &s) const;
    };
    size_t hash<Sales_data>::operator()(const Sales_data &s) const
    {
        return hash<std::string>()(s.bookNo) ^ hash<unsigned int>()(s.units_sold) ^ hash<double>()(s.revenue);
    }
}


#endif

