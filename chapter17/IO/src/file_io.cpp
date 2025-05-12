

#include <iostream>
#include <string>
#include <fstream>


int main(int argc, char *argv[])
{
    std::fstream in_out("copy.out", std::fstream::ate | std::fstream::in | std::fstream::out);
    if (!in_out)
    {
        std::cout << "Unable to open file. " << std::endl;
        return EXIT_FAILURE;
    }

    auto end_mark =  in_out.tellg();
    in_out.seekg(0, std::fstream::beg);
    size_t cnt = 0;
    std::string line_str;
    while(in_out && in_out.tellg() != end_mark && std::getline(in_out, line_str))
    {
        cnt +=line_str.size() + 1;
        auto mark = in_out.tellg();
        in_out.seekp(0, std::fstream::end);
        in_out << cnt;
        in_out << " ";
        in_out.seekg(mark);
    }
    in_out.seekp(0, std::fstream::end);
    in_out << std::endl;
    return 0;
}
