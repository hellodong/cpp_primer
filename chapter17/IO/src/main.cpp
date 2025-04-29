

#include <iostream>
#include <cmath>
#include <iomanip>

void bool_alpha(void)
{
    std::cout << "true: " << true << ", false: " << false << std::endl;
    std::cout << std::boolalpha <<"true: " << true << ", false: " << false << std::endl;
}

void showbase_func(void)
{
    std::cout << std::showbase;  // 打印整型值显示进制
    std::cout << "default: " << 20 << " "<< 1024<< std::endl;
    std::cout << "octal: " << std::oct << 20 << " " << 1024 << std::endl; 
    std::cout << "hex:" << std::hex << 20 << " " << 1024 << std::endl;
    std::cout << "decimal:" << std::dec << 20 << " " << 1024 << std::endl;
    std::cout << std::noshowbase; // 恢复流状态
}

void float_precision(void)
{
    std::cout << "precision: " << std::cout.precision() << ", value: " << sqrt(2.0) << std::endl;
    std::cout.precision(12);
    std::cout << "precision: " << std::cout.precision() << ", value: " << sqrt(2.0) << std::endl;
    std::cout << std::setprecision(4);
    std::cout <<"precision: " << std::cout.precision() << ", value:" << sqrt(2.0) << std::endl;
}

void float_scientific(void)
{
    std::cout << "scientific: " << std::scientific << 100 * sqrt(2.0) << std::endl;
    std::cout << "hexfloat: " << std::hexfloat << 100 * sqrt(2.0) << std::endl;
    std::cout << "fixed: " << std::fixed << 100 * sqrt(2.0) << std::endl;
    std::cout << "defaultfloat: " << std::defaultfloat << 100 * sqrt(2.0) << std::endl;
}

void setw_func(void)
{
    int i = -16;
    double d= 3.1415926;

    std::cout << "i: " << std::setw(12) << i << "next col" << '\n'
        << "d: " << std::setw(12) << d << "next col" << '\n';

    std::cout << std::left << "i: " << std::setw(12) << i << "next col" << '\n'
        << "d: " <<std::setw(12) << d <<"next col" << '\n';

    std::cout << std::right << "i: " <<std::setw(12) << i <<"next col" << '\n'
        << "d: " << std::setw(12) << d << "next col" << '\n';

    std::cout << std::internal << "i: " <<std::setw(12) << i <<"next col" << '\n'
        << "d: " << std::setw(12) << d << "next col" << '\n';

    std::cout << std::setfill('#') << "i: " <<std::setw(12) << i <<"next col" << '\n'
        << "d: " << std::setw(12) << d << "next col" << '\n';
}

void cin_noskipws(void)
{
    char ch;
    std::cin >> std::noskipws;
    while (std::cin >> ch)
    {
        std::cout << ch;
    }
}

int main(int argc, char *argv[])
{
    bool_alpha();
    showbase_func();
    //float_precision();
    float_scientific();
    setw_func();
    cin_noskipws();

    return 0;
}
