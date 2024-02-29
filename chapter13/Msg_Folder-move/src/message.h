


#ifndef _MESSAGE_H_
#define _MESSAGE_H_


#include <string>
#include <set>

class Folder;

class Message{
    friend class Folder;
    public:
        explicit Message(const std::string &s=""):content(s) {}
        Message(const Message &rhs);
        Message(Message &&m);
        Message& operator=(const Message &rhs);
        Message& operator=(Message &&rhs);
        ~Message();
        void save(Folder&);
        void remove(Folder&);
        void move_folders(Message *m);
        void print_folders();
    private:
        std::string content;
        std::set<Folder *> folders;
        void add2Folders(const Message &);
        void remove_from_folders();
};


#endif
