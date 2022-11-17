

#include <iostream>

class Init
{
    public:
        Init(void)
        {
            std::cout <<"Init" << std::endl;
        }
        ~Init()
        {
            std::cout <<"De Init" << std::endl;
        }
};

class Sharp:public Init
{
    public:
        Sharp(void)
        {
            std::cout <<"init Sharp" << std::endl;
        }
        ~Sharp()
        {
            std::cout << "De Sharp" << std::endl;
        }
        virtual void draw(void) = 0;
};

class Other
{
    public:
        Other(void)
        {
            std::cout << "this is other" << std::endl;
        }
        ~Other()
        {
            std::cout << "De other" << std::endl;
        }
};

class Rec: public Sharp
{
    public:
        Rec(void)
        {
            std::cout << "init Rec" << std::endl;
        }
        ~Rec()
        {
            std::cout << "De Rec" << std::endl;
        }

        virtual void draw (void)
        {
            std::cout << "draw Rec" << std::endl;
        }

    private:
        Other other_data;
};

int main(void)
{
    Rec rec;
    rec.draw();
    return 0;
}

