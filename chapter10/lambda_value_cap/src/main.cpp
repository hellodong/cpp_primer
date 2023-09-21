

#include <iostream>


int main(int argc, char *argv[])
{
	int input_val = 0;
	//when create lambda, value of input_val pass to lambda
	auto f=[input_val](void) {return input_val;};
	std::cin >> input_val;
	std::cout << f() << std::endl; // cout is 0, f save the input_val when we create lambda
	return 0;
}
