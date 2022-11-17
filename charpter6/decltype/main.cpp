

#include <iostream>

int odd[] = {1,3,5,7,9};
int even[] = {0,2,4,6,8};

decltype(odd) *arrPtr(int i)
{
    return i % 2 ? &odd:&even;
}

int main(void)
{
    std::cout << "odd " << odd << " even " << even << std::endl;
    std::cout << "1 --> " << arrPtr(1) << " 2 -->" << arrPtr(2) << std::endl;
    return 0;
}
