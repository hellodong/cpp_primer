

#include <iostream>

#include "strblob.h"
//#include "strblobptr.h"


int main(int argc,char *argv[])
{
    StrBlob blob{"a", "an", "blob"};

    std::cout << blob.size() << ", back: "<< blob.back() << std::endl;
    //blob.push_back("foo");
    StrBlobPtr ptr=blob.begin();

    std::cout << ptr.deref() << std::endl;

    ptr.incr();
    std::cout << ptr.deref() << std::endl;

    ptr.incr();
    std::cout << ptr.deref() << std::endl;

    ptr.incr();
    std::cout << ptr.deref() << std::endl;

#if 0
    std::cout << "pop back" << std::endl;
    blob.pop_back();
    std::cout << "back: " << blob.back() << std::endl;
#endif


    return 0;
}
