

#include <stdexcept>

#include "strblob.h"


StrBlob::StrBlob():data(std::make_shared<std::vector<std::string>>()) {}

StrBlob::StrBlob(std::initializer_list<std::string> il):data(std::make_shared<std::vector<std::string>>(il)) {}

void StrBlob::check(size_type idx,const std::string &msg) const
{
    if (idx >= data->size())
    {
        throw std::out_of_range(msg);
    }
}

void StrBlob::pop_back()
{
    check(0, "data is empty, pop error");
    return data->pop_back();
}

