

#include "message.h"
#include "folder.h"

#include <iostream>


Message::Message(const Message &rhs):
    content(rhs.content), folders(rhs.folders)
{
    add2Folders(*this);
}

Message& Message::operator=(const Message &rhs)
{
    remove_from_folders();
    content = rhs.content;
    folders = rhs.folders;
    add2Folders(*this);
    return *this;
}

Message::~Message()
{
    remove_from_folders();
}

void Message::save(Folder &f)
{
    folders.insert(&f);
    f.addMsg(this);
}

void Message::remove(Folder &f)
{
    f.rmMsg(this);
    folders.erase(&f);
}

void Message::add2Folders(const Message &m)
{
    for(auto f:m.folders)
    {
        f->addMsg(this);
    }
}

void Message::remove_from_folders()
{
    for(auto f:folders)
    {
        f->rmMsg(this);
    }
}

void Message::print_folders()
{
    std::cout <<"Messages: " << content << ", used by following folders:\n" ;
    for (auto f:folders)
    {
        std::cout <<std::hex <<f<<std::endl;
    }
}

