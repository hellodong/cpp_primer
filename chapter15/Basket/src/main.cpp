
#include <iostream>

#include "basket_quate.h"

int main(int argc, char *argv[])
{
    Basket bskt;
    std::string book_name("cpp_primer");
    bskt.add_item(std::make_shared<Quate>(book_name, 128));
    book_name="effective_cpp";
    bskt.add_item(std::make_shared<Bulk_Quate>(book_name, 48, 3, 0.8));
    bskt.total_receipt(std::cout);

    return 0;
}
