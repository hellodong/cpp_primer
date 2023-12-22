

#ifndef _QUERY_RSLT_H_
#define _QUERY_RSLT_H_

#include <string>
#include <vector>
#include <memory>
#include <set>

class QueryRslt {
    friend void print(QueryRslt qr);
    public:
        using Line_no = std::vector<std::string>::size_type;
        QueryRslt(std::string word, 
                  std::shared_ptr<std::set<Line_no>> line, 
                  std::shared_ptr<std::vector<std::string>> f):sout(word), lines(line),v_file(f)
        {}
    private:
        std::string sout;
        std::shared_ptr<std::set<Line_no>> lines;
        std::shared_ptr<std::vector<std::string>> v_file;
};

#endif

