

#include "Sales_data.h"
#include <set>

typedef bool (*fnc)(const Sales_data &lhs, const Sales_data &rhs);

bool compareBookno(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.bookname() < rhs.bookname();
}


int main(int argc, char *argv[])
{
    std::multiset<Sales_data, decltype(compareBookno) *>bookstore(compareBookno);
    //std::multiset<Sales_data, fnc>bookstore(compareBookno);

    bookstore.insert(Sales_data("cpp primmer", 1, 128.00));
    bookstore.insert(Sales_data("cpp primmer", 2, 96.00));
    bookstore.insert(Sales_data("effective cpp", 1, 56.00));
    bookstore.insert(Sales_data("effective cpp", 10, 40.00));

    for(const auto &book:bookstore)
    {
        book.print();
    }

    return 0;
}
