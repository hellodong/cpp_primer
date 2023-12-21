

#include <iostream>
#include <vector>
#include <string>
#include <memory>


void _uninitialized_copy_static_array(void)
{
    std::vector<int> ivec(1,4);
    int *dyn_arr = new int [ivec.size() * 2];

    std::uninitialized_copy(ivec.begin(), ivec.end(), dyn_arr);

    std::cout << "uninitiazed copy" << std::endl;

    for(int idx = 0;idx != ivec.size() * 2;idx++)
    {
        std::cout << dyn_arr[idx] << " ";
    }
    std::cout << std::endl;

    delete [] dyn_arr;
}

void _allocate_string_array(unsigned int _num)
{
    std::allocator<std::string> alloc;
    std::string *const p = alloc.allocate(_num);
    auto q = p;

    std::cout<<"allocate string:"<<std::endl;
    alloc.construct(q++);
    alloc.construct(q++, 3,'c');
    alloc.construct(q++, "c++ primer");

    for(int idx =0;idx < 3;idx++)
    {
        std::cout <<p[idx].size() <<","<<p[idx] << std::endl;
    }

    alloc.destroy(--q);
    alloc.destroy(--q);
    alloc.destroy(--q);

    alloc.deallocate(p, _num);
}

int main(int argc, char *argv[])
{
    _uninitialized_copy_static_array();

    _allocate_string_array(8);

    return 0;
}
