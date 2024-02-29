

#ifndef _STRBLOBPTR_H_
#define _STRBLOBPTR_H_

#include <vector>
#include <string>
#include <memory>

class StrBlob;

class StrBlobPtr{
    public:
        StrBlobPtr():curr(0) {};
        StrBlobPtr(StrBlob &a, std::size_t sz = 0);
        StrBlobPtr &operator++();
        StrBlobPtr &operator--();
        StrBlobPtr operator++(int);
        StrBlobPtr operator--(int);
        std::string &operator*() const
        {
           auto p = check(curr, "dereference past end");
           return (*p)[curr];
        }
        std::string *operator->() const
        {
            return &this->operator*();
        }
        StrBlobPtr &incr();
        std::string &deref() const;
    private:
        std::shared_ptr<std::vector<std::string>> check (std::size_t, const std::string &) const;
        std::weak_ptr<std::vector<std::string>> wptr;
        std::size_t curr;
};

#endif

