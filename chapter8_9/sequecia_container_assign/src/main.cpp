

#include <iostream>
#include <list>
#include <string>
#include <vector>


int main(int argc ,char *argv[])
{
	std::list <const char *> chList = {"hello", "world", "cpp"};
	std::vector<std::string> strVector;
	strVector.assign(chList.begin(), chList.end());
	for (auto start = strVector.cbegin(); start != strVector.cend();start++)
	{
		std::cout << *start << std::endl;
	}
	return 0;
}
