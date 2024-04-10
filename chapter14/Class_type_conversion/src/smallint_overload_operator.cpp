

#include <iostream>


class SmallInt;

SmallInt operator+(const SmallInt &lhs, const SmallInt &rhs);

class SmallInt
{
    friend SmallInt operator+(const SmallInt &lhs, const SmallInt &rhs);
    public:
        SmallInt(int val = 0):value(val) {}
        operator int () const {return value;}
    private:
        int value;
};

SmallInt operator+(const SmallInt &lhs, const SmallInt &rhs)
{
    return SmallInt(lhs.value + rhs.value);
}


int main(int argc, char *argv[])
{
    SmallInt s1, s2;
    SmallInt s3 = s1 + s2;
    int ival = s1 + s2;


    std::cout << s3 << std::endl;

    std::cout << ival << std::endl;

    return 0;
}

