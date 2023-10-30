

#include <set>
#include <vector>
#include <iostream>


int main(int argc, char *argv[])
{
    std::vector<int> ivec;
    for(std::vector<int>::size_type idx = 0;idx != 10;idx++ )
    {
        ivec.push_back(idx);
        ivec.push_back(idx);
    }

    std::set<int> iset(ivec.cbegin(), ivec.cend());
    std::multiset<int> multiset(ivec.cbegin(), ivec.cend());

    std::cout << "ivec size:" << ivec.size() << std::endl;
    std::cout << "iset size:" << iset.size() << std::endl;
    std::cout << "multiset size:" << multiset.size() << std::endl;

	return 0;
}
