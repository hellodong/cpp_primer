

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

int main(int argc, char *argv[])
{
    bool_alpha();
    showbase_func();
    float_precision();

    return 0;
}
