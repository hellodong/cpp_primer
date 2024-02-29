

#include <iostream>

#include "strblob.h"
#include "strblobptr.h"


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout <<"usage: "<< argv[0] << " <arg1> <arg2> ..." << std::endl;
        return -1;
    }

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

    return 0;
}
