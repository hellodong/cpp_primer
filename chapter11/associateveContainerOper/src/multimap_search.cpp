

#include <map>
#include <iostream>
#include <string>


void lower_upper_iter(const std::multimap<std::string, std::string>& authors, const std::string &rhs);
void equal_range_iter(const std::multimap<std::string, std::string>& authors, const std::string &rhs);
void traveral(const std::multimap<std::string, std::string>& books);

int main(int argc, char *argv[])
{
    std::multimap<std::string, std::string> authors;

    authors.insert({"Stanley Lippman", "C++ Primer"});
    authors.insert({"Stanley Lippman", "Essential C++"});
    authors.insert({"Stanley Lippman", "Inside C++ Object Model"});
    authors.insert({"Scott Meyers", "Effective C++"});
    authors.insert({"Richard Stevens", "Advance Program Unix Environment"});
    authors.insert({"Richard Stevens","Unix Network Program"});
    
    auto entries = authors.count("Stanley Lippman");
    auto iter = authors.find("Stanley Lippman");
    std::cout << "Stanley Lippman: " ; 
    while(entries)
    {
        std::cout << iter->second << ", ";
        entries--;
        iter++;
    }
    std::cout << std::endl << "search by map.count and map.find" << std::endl;

    lower_upper_iter(authors, "Stanley Lippman");
    equal_range_iter(authors, "Richard Stevens");
    traveral(authors);

    return 0;
}

void lower_upper_iter(const std::multimap<std::string, std::string>& authors, const std::string &rhs)
{
    auto iter = authors.lower_bound(rhs);
    auto iter_end = authors.upper_bound(rhs);

    std::cout <<std::endl << rhs <<": "; 
    for(;iter != iter_end;iter++)
    {
        std::cout << iter->second << ", ";
    }

    std::cout << std::endl << "search by map.lower_bound and map.upper_bound" << std::endl;
}

void equal_range_iter(const std::multimap<std::string, std::string>& authors, const std::string &rhs)
{
    std::cout<< std::endl << rhs <<": "; 
    for(auto pos = authors.equal_range(rhs);pos.first != pos.second;pos.first++)
    {
        std::cout << pos.first->second << ", ";
    }
    std::cout << std::endl << "search by map.equal_range" << std::endl;
}

void traveral(const std::multimap<std::string, std::string>& books)
{
    std::cout << std::endl << "List all books and author" << std::endl;
    for(auto iter=books.cbegin();iter != books.cend();iter++)
    {
        std::cout << iter->first <<": "<<iter->second << std::endl;
    }
}

