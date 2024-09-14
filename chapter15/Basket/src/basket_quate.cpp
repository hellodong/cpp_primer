

#include <iostream>

#include "basket_quate.h"




double print_total(std::ostream &os, const Quate &item, size_t n)
{
    double ret = item.net_price(n);
    os << item.isbn() << std::string(", sale:") << static_cast<unsigned long>(n) << std::string(", total due: ") << ret << std::endl;
    return ret;
}



bool Basket::compare(const std::shared_ptr<Quate> &lhs, const std::shared_ptr<Quate> &rhs)
{
    return lhs->isbn() < rhs->isbn();
}

double Basket::total_receipt(std::ostream &os) const
{
    double sum = 0.0;
    for(auto iter = items.cbegin();iter !=items.cend();iter = items.upper_bound(*iter))
    {
        sum += print_total(os, **iter, items.count(*iter));
    }
    os << std::string("Total Sale: ") << sum << std::endl;
    return sum;
}

