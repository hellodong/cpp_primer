

#ifndef _TXT_QUERY_H_
#define _TXT_QUERY_H_

#include <vector>
#include <string>
#include <set>
#include <map>
#include <memory>
#include <fstream>

class QueryRslt;

class TxtQuery{
    public:
        using Line_no = std::vector<std::string>::size_type;
        TxtQuery(std::ifstream &ifile);
        QueryRslt query(const std::string &) const;
    private:
        std::shared_ptr<std::vector<std::string>> v_file;
        std::map<std::string, std::shared_ptr<std::set<Line_no>>> wm;
};

#endif

