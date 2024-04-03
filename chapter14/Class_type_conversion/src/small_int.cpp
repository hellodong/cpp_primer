

#include <iostream>

class SmallInt{
    public:
        SmallInt(int val = 0):value(val) {}
        operator int () const {return value;}
    private:
        int value;
};


int main(int argc, char *argv[])
{
    SmallInt si;

    si = 4;
    std::cout << si + 3 << std::endl;

    SmallInt sd = 3.14;

    std::cout << sd + 3.14 << std::endl;

    return 0;
}
