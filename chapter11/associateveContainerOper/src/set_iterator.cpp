

#include <set>
#include <iterator>
#include <iostream>


int main(int argc, char *argv[])
{
    std::set<int> iset{1,2,3,4,5,6,7,8,9};
    std::set<int>::iterator set_it = iset.begin();
    std::set<int>::const_iterator set_cit = iset.cbegin();
    
    std::cout << *set_it<< std::endl;
    std::cout <<"const iterator " << *set_cit << std::endl;

	return 0;
}
