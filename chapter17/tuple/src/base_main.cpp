

#include <tuple>
#include <iostream>


int main(void)
{
    auto item = std::make_tuple("cpp_primer", 1, 128.00);
    auto book = std::get<0>(item);
    auto cnt = std::get<1>(item);
    auto price = std::get<2>(item);

    std::cout <<"book: " << book <<", count:" << cnt <<", price:" << price << std::endl;

    std::get<2>(item) *= 0.8;
    std::cout <<"discount 0.8, new price: " << std::get<2>(item) << std::endl;

    typedef decltype(item) Trans;
    size_t sz = std::tuple_size<Trans>::value;
    std::tuple_element<1, Trans>::type cnt1 = std::get<1>(item);

    std::cout <<"\nTrans tuple size: " << sz <<", 2rd element value: " << cnt1 << std::endl;

    return 0;
}

