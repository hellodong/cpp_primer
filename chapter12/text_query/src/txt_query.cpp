

#include<sstream>
#include "txt_query.h"
#include "query_rslt.h"

TxtQuery::TxtQuery(std::ifstream &ifile):v_file(new std::vector<std::string>())
{
    std::string txt;
    while(std::getline(ifile,txt))
    {
        v_file->push_back(txt);
        size_t n = v_file->size();
        std::istringstream line(txt);
        std::string word;
        while(line >> word)
        {
            auto &sptr_line = wm[word]; 
            if(!sptr_line)
            {
                sptr_line.reset(new std::set<Line_no>);
            }
            sptr_line->insert(n);
        }
    }
}

QueryRslt TxtQuery::query(const std::string &word) const
{
    auto tmp = wm.find(word);
    if(tmp != wm.end())
    {
        return QueryRslt(word, tmp->second, v_file);
    }
    return QueryRslt(word, nullptr, nullptr);
}

