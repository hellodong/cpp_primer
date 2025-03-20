

#include <bitset>
#include <string>
#include <iostream>


void bitset_cin(void)
{
    std::cout << "input 0/1 string:" << std::endl;
    std::bitset<30>  bitvec;
    std::cin >> bitvec;
    std::cout << bitvec << std::endl;
    std::cout << bitvec.to_ulong() << std::endl;
}

int  main(int argc, char *argv[])
{
    std::bitset<32> bitvec1;
    std::bitset<16> bitvec2(0xbeef);

    std::cout << bitvec1 << std::endl;
    std::cout << bitvec2 << std::endl;

    std::string str("11111100000011001101");
    std::bitset<8> bitvec3(str, 12, 6);

    std::cout <<"bitvec3:"<< bitvec3 << std::endl;

    std::bitset<8> bitvec4(str, str.size() - 4); 
    std::cout <<"bitvec4:"<< bitvec4 << std::endl; 
    std::cout <<"bitvec4[1]: "<< bitvec4[1]<<", bitvec4[0]: "<< bitvec4[0] << std::endl; 

    bitset_cin(); 
    return 0; 
}
