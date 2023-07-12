

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>


int main(int argc, char *argv[])
{
	std::vector<int> vec={1,2,3,4,5,6,7,8,9,10,2,1,3,2};
	int cnt = std::count(vec.cbegin(), vec.cend(), 2);
	std::cout << "value 2,cnt:" << cnt << std::endl;

	std::list<std::string> list_str{"hello", "world", "cpp", "primer"};
	int cnt_dup = std::count(list_str.cbegin(), list_str.cend(), std::string("world"));
	std::cout << "string \"world\", cnt:" << cnt_dup << std::endl;
	return 0;
}
