

#include "folder.h"
#include "message.h"

#include <iostream>



Folder& Folder::operator=(Folder &rhs)
{
    for(auto m:messages)
    {
        m->remove(*this);
        rmMsg(m);
    }
    name = rhs.name;
    messages = rhs.messages;
    for (auto m:rhs.messages)
    {
        addMsg(m);
        m->save(rhs);
    }
    return *this;
}

Folder::~Folder()
{
    for(auto m:messages)
    {
        rmMsg(m);
    }
}

void Folder::addMsg(Message *m)
{
    messages.insert(m);
}

void Folder::rmMsg(Message *m)
{
    messages.erase(m);
}

void Folder::print()
{
    std::cout << name <<":\r\n";
    for(auto m:messages) {
        std::cout << std::hex << m << " content: "<< m->content <<std::oct <<std::endl;
    }
    std::cout << std::endl;
}

