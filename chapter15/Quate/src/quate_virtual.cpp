

#include <string>
#include <iostream>

class Quate{
    public:
        Quate() = default;
        Quate(std::string &_isbn, double _price = 0.0):price_(_price), isbn_(_isbn) {}
        std::string isbn(void) const {return isbn_;}
        virtual double net_price(std::size_t n = 1) const
        {
            return price_ * n;
        }

        virtual ~Quate() = default; //对析构函数进行动态绑定

    protected:
        double price_;

    private:
        std::string isbn_;
};

int main(int argc, char *argv[])
{
    std::string isbn_("cpp_primer");

    Quate quate_(isbn_, 128);

    std::cout << "ISBN: "<< quate_.isbn() << ", sale: " << 2<< ", total due:" <<quate_.net_price(2) << std::endl;
    std::cout << "ISBN: "<< quate_.isbn() << ", sale: " << "default"<< ", total due:" <<quate_.net_price() << std::endl;

    return 0;
}
