

#include <iostream>


int main(int argc, char *argv[])
{
	auto f=[](void) {return 42;};

	std::cout << f() << std::endl;
	return 0;
}
