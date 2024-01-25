

#include <string>
#include <iostream>


class HasPtr{
    friend std::ostream& print(std::ostream &os, HasPtr &p);
    public:
        HasPtr(const std::string &s = std::string()): ps(new std::string(s)), i(0) {}
        HasPtr(const HasPtr &p):ps(new std::string(*p.ps)), i(p.i) {}
        HasPtr &operator=(const HasPtr &rhs);

        ~HasPtr()
        {
            delete ps;
        }

    private:
        std::string *ps;
        int i;
};

std::ostream& print(std::ostream &os, HasPtr &p)
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

int main(int argc,char *argv[])
{
    HasPtr a("haha");
    HasPtr b=a;
    HasPtr c;

    print(std::cout, a);
    print(std::cout, b);
    print(std::cout, c);
    c = a;
    print(std::cout, c);
    return 0;
}
