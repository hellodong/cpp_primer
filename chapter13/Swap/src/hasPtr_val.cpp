

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>


class HasPtr{
    friend std::ostream& print(std::ostream &os, const HasPtr &p);
    friend bool operator< (const HasPtr &rhs, const HasPtr &lhs);
    friend void swap(HasPtr &rhs, HasPtr &lhs);
    public:
        HasPtr(const std::string &s = std::string()): ps(new std::string(s)), i(0) 
            {}
        HasPtr(const HasPtr &p):ps(new std::string(*p.ps)), i(p.i)
            {}
        HasPtr &operator=(const HasPtr &rhs);

        ~HasPtr()
        {
            delete ps;
        }
        void swap(HasPtr &lhs);

    private:
        std::string *ps;
        int i;
};

std::ostream& print(std::ostream &os,const HasPtr &p)
{
    os << "ps: " << *p.ps <<", i: " << p.i <<std::endl;
    return os;
}

HasPtr& HasPtr::operator=(const HasPtr &rhs)
{
    auto newp = new std::string(*rhs.ps);
    delete ps;
    ps = newp;
    i = rhs.i;

    return *this;
}

bool operator< (const HasPtr &rhs, const HasPtr &lhs)
{
    return *rhs.ps < *lhs.ps;
}

void swap(HasPtr &rhs, HasPtr &lhs)
{
    rhs.swap(lhs);
    std::cout << "person swap\n";
}

void HasPtr::swap(HasPtr &lhs)
{
    using std::swap;
    swap(ps, lhs.ps);
    swap(i,lhs.i);
}

namespace std{
    template <>
        void swap(HasPtr &rhs, HasPtr &lhs)
        {
            rhs.swap(lhs);
            cout << "special swap" << endl;
        }
};

int main(int argc,char *argv[])
{
    HasPtr a("haha");
    HasPtr b;

    print(std::cout, a);
    print(std::cout, b);

    a.swap(b);

    print(std::cout, a);
    print(std::cout, b);

    std::vector<HasPtr> vec;
    vec.push_back(HasPtr("a"));
    vec.push_back(HasPtr("c"));
    vec.push_back(HasPtr("ba"));
    vec.push_back(HasPtr("1"));

    for(const auto &tmp:vec) {
        print(std::cout, tmp);
    }

    sort(vec.begin(),vec.end());

    std::cout << "sort vecotr" << std::endl;
    for(const auto &tmp:vec) {
        print(std::cout, tmp);
    }

    return 0;
}

