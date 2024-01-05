
#include <string>
#include <iostream>



class HasPtr{
    public:
        friend std::ostream& print(std::ostream &os, const HasPtr &p);
        HasPtr(const std::string &s = std::string()):ps(new std::string(s)),i(0),use_count(new std::size_t(1)) {}
        HasPtr(const HasPtr &p):ps(p.ps), i(p.i),use_count(p.use_count) {
            ++*use_count;
        }
        HasPtr& operator=(const HasPtr &rhs);
        ~HasPtr()
        {
            if (--*use_count == 0)
            {
                delete ps;
                delete use_count;
            }
        }

    private:
        std::string *ps;
        int i;
        std::size_t *use_count;
};

std::ostream& print(std::ostream &os, const HasPtr &p)
{
    os << p.ps <<": "<< *p.ps<<", "<<p.i <<","<<*p.use_count << std::endl;
    return os;
}

HasPtr& HasPtr::operator=(const HasPtr &rhs)
{
    ++*rhs.use_count;
    if (--*use_count == 0)
    {
        delete ps;
        delete use_count;
    }
    i = rhs.i;
    ps = rhs.ps;
    use_count = rhs.use_count;
    return *this;
}

int main(int argc, char *argv[])
{
    HasPtr a("hihi");
    HasPtr b1(a);
    HasPtr b2(b1);

    print(std::cout , a);
    print(std::cout , b1);
    print(std::cout , b2);
    return 0;
}
