
#include <stdexcept>

#include "strblob.h"
#include "strblobptr.h"

StrBlobPtr::StrBlobPtr(StrBlob &a, std::size_t sz):wptr(a.data),curr(sz) 
{
}

std::shared_ptr<std::vector<std::string>> StrBlobPtr::check (std::size_t idx, const std::string &msg) const
{
    auto ret = wptr.lock();
    if(!ret)
    {
        throw std::runtime_error("unbound StrBlobPtr");
    }

    if(idx >= ret->size())
    {
        throw std::out_of_range(msg);
    }
    return ret;
}

StrBlobPtr& StrBlobPtr::incr()
{
    check(curr, "increament past end of StrBlobPtr");
    curr++;
    return *this;
}

StrBlobPtr &StrBlobPtr::operator++()
{
    check(curr, "increament past end of StrBlobPtr");
    ++curr;
    return *this;
}

StrBlobPtr &StrBlobPtr::operator--()
{
    --curr;
    check(curr, "decreament past begin of StrBlobPtr");
    return *this;
}

StrBlobPtr StrBlobPtr::operator++(int)
{
    StrBlobPtr ret(*this);
    ++*this;
    return ret;
}

StrBlobPtr StrBlobPtr::operator--(int)
{
    StrBlobPtr ret(*this);
    --*this;
    return ret;
}


std::string &StrBlobPtr::deref() const
{
    auto p = check(curr,"dereference past end");

    return (*p)[curr];
}

