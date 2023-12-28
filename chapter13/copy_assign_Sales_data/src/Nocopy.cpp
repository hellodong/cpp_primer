


#include <iostream>

struct NoCopy{
    NoCopy() = default;
    NoCopy(const NoCopy &) = delete;
    NoCopy& operator=(const NoCopy &) = delete;
    ~NoCopy() = default;
};

void handle_nocopy(struct NoCopy item)
{
    std::cout << __FUNCTION__ << " copy construct NoCopy" <<std::endl;
}

int main(int argc, char *argv[])
{
    struct NoCopy item;
    handle_nocopy(item);

    return 0;
}
