


#include "message.h"
#include "folder.h"

int main(int argc, char *argv[])
{
    Message m1("hi");
    Folder f1("Inbox");
    m1.save(f1);

    f1.print();

    Message m2(m1);
    Folder f2(f1);
    f1.print();
    f2.print();

    Message m3;
    m3 = m2;
    f1.print();
    f2.print();

    m2=m2;
    f2.print();

    return 0;
}
