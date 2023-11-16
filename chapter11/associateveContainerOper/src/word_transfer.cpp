
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

bool buildMap(std::ifstream &map_file, std::map<std::string, std::string>& trans_map);
const std::string& transform(const std::string &str, const std::map <std::string, std::string> &trans_map);

int main(int argc, char *argv[])
{
    std::ifstream rule_file(argv[1]), text_file(argv[2]);
    std::map<std::string, std::string> trans_map;
    buildMap(rule_file, trans_map);   
    std::string text;
    while(std::getline(text_file, text))
    {
        std::istringstream istream(text);
        std::string word;
        while(istream >> word)
        {
            std::cout << transform(word, trans_map) << " ";
        }
        std::cout << std::endl;
    }
}

bool buildMap(std::ifstream &map_file, std::map<std::string, std::string>& trans_map)
{
    std::string key, value;
    while(map_file >> key && std::getline(map_file, value))
    {
        if (value.size() > 1)
        {
            size_t len = value.length();
            trans_map[key] = value.substr(1, len - 2);   // 去掉前导空格
        }
        else 
        {
            throw std::runtime_error("no rule for " + key);
        }
    }
    return true;
}

const std::string& transform(const std::string &str, const std::map <std::string, std::string> &trans_map)
{
    auto mapped = trans_map.find(str);
    if (mapped != trans_map.end())
    {
        return mapped->second;
    }
    return str;
}