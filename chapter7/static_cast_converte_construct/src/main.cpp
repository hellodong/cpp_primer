

#include <vector>
#include <iostream>

int vectorstring_size(const std::vector<char> &vector_str)
{
    return vector_str.size();
}

int main(int argc, char *argv[])
{
    // 下面的隐式转换式错误的，vector不支持隐式转换
    //std::cout << "size" << vectorstring_size(10) << std::endl;

    std::cout << "size " << vectorstring_size(static_cast<std::vector<char>>(10)) << std::endl;
    return 0;
}
