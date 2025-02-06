

#ifndef _STRVEC_H_
#define _STRVEC_H_


#include <string>
#include <memory>


class StrVec {
    public:
        StrVec():elements(nullptr), first_free(nullptr), cap(nullptr){}
        StrVec(const StrVec &);
        StrVec &operator=(const StrVec &);
        ~StrVec();
        template<class... Args> void emplace_back(Args&&...);
        void push_back(const std::string &);
        void push_back(std::string &&s);
        size_t size() const {return first_free - elements;}
        size_t capacity() const {return cap - elements;}
        std::string *begin() const {return elements;}
        std::string *end() const {return first_free;}
    private:
        static std::allocator<std::string> alloc;
        void reallocate();
        void free();
        void chk_n_alloc() {if (size() == capacity()) reallocate();};
        std::pair<std::string *, std::string *> alloc_n_copy(const std::string *, const std::string *);
        std::string *elements;
        std::string *first_free;
        std::string *cap;
};

template<class... Args> inline void StrVec::emplace_back(Args&&...args)
{
    chk_n_alloc();
    alloc.construct(first_free++, std::forward<Args>(args)...);
}

#endif
