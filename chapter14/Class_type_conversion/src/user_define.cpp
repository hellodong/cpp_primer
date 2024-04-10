

#include <iostream>

struct A {
    A(int _v):val(_v){}
    operator int () const {return val;}
    private:
        int val;
};

struct E{
    E(double _v):val(_v) {}
    operator double() const {return val;}
    private:
        double val;
};


void main_ip(const A &val)
{
    int _ival = val;
    std::cout << _ival << std::endl;
}

void main_ip(const E &val)
{
    double _dval = val;
    std::cout << _dval << std::endl;
}

int main(int argc, char *argv[])
{
    main_ip(A(10));
    //main_ip(10);

    return 0;
}
