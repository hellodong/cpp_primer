

#include <iostream>
#include <vector>
#include <memory>


int main(int argc, char *argv[])
{
    std::vector<int> ivec(1,4);
    int *dyn_arr = new int [ivec.size() * 2];

    std::uninitialized_copy(ivec.begin(), ivec.end(), dyn_arr);

#if 0
    std::allocator<int> a;
    int* p = a.allocate(ivec.size() * 2);
    int *q = p;
    for(q = p;q != p + 42;q++)
    {
        std::cout << *q << " " << std::endl;
    }
    a.deallocate(p, 42);
#endif
    return 0;
}
