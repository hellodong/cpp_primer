

#include "strVec.h"


std::allocator<std::string> StrVec::alloc;

StrVec::StrVec(const StrVec &s)
{
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec &StrVec::operator=(const StrVec &rhs)
{
    auto newdata = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = newdata.first;
    first_free = cap = newdata.second;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const StrVec &sv)
{
    os << "capasity: " << sv.capacity() <<" , size:" << sv.size() <<std::endl;
    for(auto tmp=sv.elements; tmp != sv.first_free;tmp++)
    {
        os << *tmp <<" ";
    }
    os << std::endl;

    return os;
}

StrVec &StrVec::operator=(std::initializer_list<std::string> il)
{
    auto newdata = alloc_n_copy(il.begin(), il.end());
    free();
    elements = newdata.first;
    first_free = cap = newdata.second;
    return *this;
}

StrVec::~StrVec()
{
    free();
}

void StrVec::push_back(const std::string &s)
{
    chk_n_alloc();
    alloc.construct(first_free++, s);
}

std::pair<std::string *, std::string *> StrVec::alloc_n_copy(const std::string *bgn, const std::string *end_ptr)
{
    auto data = alloc.allocate(end_ptr - bgn);
    return {data, std::uninitialized_copy(bgn, end_ptr, data)};
}

void StrVec::reallocate()
{
    auto newcap = size() ? 2 * size():1;
    auto newdata = alloc.allocate(newcap);
    auto dest = newdata;
    auto elem = elements;
    for (size_t idx = 0;idx != size();++idx)
    {
        alloc.construct(dest++, std::move(*elem++));
    }
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + newcap;
}

void StrVec::free()
{
    if (nullptr != elements)
    {
        for (auto p = first_free;p != elements;)
        {
            alloc.destroy(--p);
        }
        alloc.deallocate(elements, cap - elements);
    }
}

