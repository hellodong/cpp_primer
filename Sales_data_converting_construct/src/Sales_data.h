
#ifndef _SALES_DATA_H_
#define _SALES_DATA_H_

#include <iostream>
#include <string>


class Sales_data{
	friend std::ostream &print(std::ostream &os, const Sales_data &entry);
public:
	Sales_data(std::string s, unsigned int cnt, double price):bookNo(s),units_sold(cnt),revenue(cnt * price) {}
	Sales_data():Sales_data("", 0,0.0) { }
	Sales_data(std::string s):Sales_data(s,0,0.0) { }
	Sales_data(std::istream &is):Sales_data() 
	{
		read(is);
	}

	std::istream &read(std::istream &is);
    Sales_data &combine(const Sales_data &);

    std::string bookNo;
    unsigned int units_sold=0;
    double revenue = 0.0;
};

std::ostream &print(std::ostream &os, const Sales_data &entry);



#endif

