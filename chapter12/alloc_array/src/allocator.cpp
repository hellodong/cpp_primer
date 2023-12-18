

#include <iostream>
#include <vector>
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

int main(int argc, char *argv[])
{
    _uninitialized_copy_static_array();
    return 0;
}
