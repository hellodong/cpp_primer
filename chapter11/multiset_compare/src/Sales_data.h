
#ifndef _SALES_DATA_H_
#define _SALES_DATA_H_


#include <iostream>
#include <string>

class Sales_data
{
    public:
        Sales_data() = default;
        Sales_data(const std::string &s, unsigned int n, double p): bookNo(s),units_sold(n),price(p) 
        {}
        std::string bookname(void) const;
        void print(void) const;
    private:
        std::string bookNo;
        unsigned int units_sold = 0;
        double price;
};



#endif

