

#include "textDecode.h"

int main(int argc, char *argv[])
{
	TextDecode file(argv[1]);
	
	file.decode();	
	return 0;
}
