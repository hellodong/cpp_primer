

#include "Sales_data.h"


int main(int argc, char *argv[])
{
    Sales_data data("1234567890", 1, 11.11);

    print(std::cout, data);
    return 0;
}
