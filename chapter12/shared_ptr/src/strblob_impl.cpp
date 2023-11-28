

#include <iostream>
#include "strblob.h"


int main(int argc, char *argv[])
{
    StrBlob blob{"a", "an", "blob"};

    std::cout << blob.size() << ", back: "<< blob.back() << std::endl;

    blob.push_back("foo");

    std::cout << blob.size() <<", back: "<< blob.back() << std::endl;

    std::cout << "pop back" << std::endl;
    blob.pop_back();
    std::cout << "back: " << blob.back() << std::endl;

    std::cout << "pop all element" << std::endl;

    while(blob.size())
    {
        blob.pop_back();
    }
    blob.pop_back();

    return 0;
}
