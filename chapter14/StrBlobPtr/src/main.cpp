

#include <iostream>

#include "strblob.h"
#include "strblobptr.h"


int main(int argc,char *argv[])
{
    StrBlob blob{"a", "an", "blob"};

    std::cout << blob.size() << ", back: "<< blob.back() << std::endl;
    //blob.push_back("foo");
    //StrBlobPtr ptr=blob.begin();
    StrBlobPtr ptr(blob);

    std::cout << ptr.deref() << std::endl;

    std::cout <<"pre ++: " << (++ptr).deref() << std::endl;
    std::cout <<"        " <<(++ptr).deref() << std::endl;
    ++ptr;

    std::cout << "pre --: " << (--ptr).deref() << std::endl;
    std::cout << "        " << (--ptr).deref() << std::endl;
    std::cout << "        " <<(--ptr).deref() << std::endl;

    std::cout << "post ++: " << (ptr++).deref() << std::endl;
    std::cout << "         " << (ptr++).deref() << std::endl;
    std::cout << "         " << (ptr++).deref() << std::endl;
    
    ptr--;
    std::cout << "post --: " << (ptr--).deref() << std::endl;
    std::cout << "         " << (ptr--).deref() << std::endl;
    //std::cout << "         " << (ptr--).deref() << std::endl;
    std::cout <<std::endl <<"reference *: "<<*ptr << std::endl;

    if (argc > 1)
    {
        StrBlob blob_input;
        for(int idx = 1;idx < argc;idx++)
        {
            blob_input.push_back(argv[idx]);
        }
        StrBlobPtr input_ptr(blob_input);

        std::cout << "Blob Input:"<< blob_input.size() <<" word(s)" <<std::endl;
        for (size_t idx = 0;idx < blob_input.size();idx++)
        {
            std::cout << "           " << *input_ptr << ": "<<(input_ptr++)->size() << std::endl;
        }
    }
#if 0
    std::cout << "pop back" << std::endl;
    blob.pop_back();
    std::cout << "back: " << blob.back() << std::endl;
#endif
    return 0;
}
