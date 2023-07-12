
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
	std::ofstream  fstm;
	std::string instr;
	fstm.open("./out.txt", std::fstream::out | std::fstream::app);
	while(std::cin >> instr )
	{
		fstm <<instr << std::endl;
	}
	fstm.clear();

	fstm.close();

	std::cout << "quit " << argv[0] << std::endl;
	return 0;
}
