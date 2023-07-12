

#include <string>
#include <iostream>


int main(int argc, char *argv[])
{
	const char ch[] = "hello world!!!";
	std::string str="hello world";

	std::string s1(ch, 5);
	std::string s2(str, 5);
	std::cout << "s1 " << s1 << std::endl;
	std::cout << "s2 " << s2 << std::endl;

	return 0;
}
