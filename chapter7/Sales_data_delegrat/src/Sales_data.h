
#ifndef _SALES_DATA_H_
#define _SALES_DATA_H_

#include <iostream>
#include <string>


class Sales_data{
	friend std::ostream &print(std::ostream &os, const Sales_data &entry);
public:
	Sales_data(std::string s, unsigned int cnt, double price):bookNo(s),units_sold(cnt),revenue(cnt * price) { std::cout << "three parameters" << std::endl;}
	Sales_data():Sales_data("", 0,0.0) { std::cout << "default" << std::endl;}
	Sales_data(std::string s):Sales_data(s,0,0.0) { std::cout << "only string parameter" << std::endl;}
	Sales_data(std::istream &is):Sales_data() 
	{
		std::cout << "cin input three parameters" << std::endl;
		read(is);
	}
	std::istream &read(std::istream &is);
private:
    std::string bookNo;
    unsigned int units_sold=0;
    double revenue = 0.0;
};

std::ostream &print(std::ostream &os, const Sales_data &entry);



#endif

