

#ifndef _FOLDER_H_
#define _FOLDER_H_

#include <string>
#include <set>

class Message;

class Folder{
    public:
        Folder(const std::string &s = ""):name(s) {}
        Folder(Folder &) = default;
        Folder& operator=(Folder &rhs);
        ~Folder();
        void addMsg(Message *);
        void rmMsg(Message *);
        void print(void);
    private:
        std::string name;
        std::set<Message *> messages;
};


#endif

