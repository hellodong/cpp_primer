

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

StrVec::~StrVec()
{
    free();
}

void StrVec::push_back(const std::string &s)
{
    chk_n_alloc();
    alloc.construct(first_free++, s);
}

void StrVec::push_back(std::string &&s)
{
    chk_n_alloc();
    alloc.construct(first_free++, std::move(s));
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

    auto last = uninitialized_copy(make_move_iterator(begin()), 
                                   make_move_iterator(end()),
                                   newdata);
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

