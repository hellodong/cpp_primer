

#ifndef _STRBLOB_H_
#define _STRBLOB_H_

#include <string>
#include <vector>
#include <memory>


class StrBlobPtr;

class StrBlob
{
    public:
        friend class StrBlobPtr;
        using size_type = std::vector<std::string>::size_type;
        StrBlob();
        StrBlob(std::initializer_list<std::string> il);

        void pop_back();

        size_type size() const { return data->size();}
        void push_back(const std::string &str) 
        {
            data->push_back(str);
        }
        std::string &back() const {return data->back();}

        StrBlobPtr begin();
        StrBlobPtr end();
    private:
        std::shared_ptr<std::vector<std::string>> data;
        void check(size_type idx,const std::string &msg) const;

};

#endif
