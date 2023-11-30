

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <memory>
#include <new>


   
std::vector<int>* _new_input_int(const std::string &path)
{
    std::ifstream file(path);
    std::istream_iterator<int> input(file), eof;

    std::vector<int> *pv = new std::vector<int>;

    while (input != eof)
    {
        //std::cout <<*input << " ";
        pv->push_back(*input++);
    }
    std::cout << std::endl;
    return pv; 
}

std::shared_ptr<std::vector<int>> _shared_intput_int(const std::string &path)
{
    std::ifstream file(path);
    std::istream_iterator<int> input(file), eof;

    std::shared_ptr<std::vector<int>> spv = std::make_shared<std::vector<int>>();

    while (input != eof)
    {
        //std::cout <<*input << " ";
        spv->push_back(*input++);
    }
    std::cout << std::endl;
    return spv; 

}


void _new_vector_print(std::vector<int> *pv) 
{
    std::cout << "new vecotr<int> output: " << std::endl;
    for(auto it=pv->cbegin();it != pv->cend();it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void _shared_vector_print(std::shared_ptr<std::vector<int>> spv) 
{
    std::cout << "shared_ptr vecotr<int> output: " << std::endl;
    for(auto it=spv->cbegin();it != spv->cend();it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << argv[0] << " <file>" << std::endl;
        return -1;
    }
    
    std::string path(argv[1]);

    std::cout << "new vector<int>*pv from " << path <<std::endl;

    auto pv = _new_input_int(path);
    _new_vector_print(pv);
    delete pv;

    auto spv = _shared_intput_int(path);
    _shared_vector_print(spv);

    return 0;
}

