

#include <string>
#include <iostream>

class Quate{
    public:
        Quate() = default;
        Quate(std::string &_isbn, double _price = 0.0):price_(_price), isbn_(_isbn) {}
        std::string isbn(void) const {return isbn_;}
        virtual double net_price(std::size_t n) const
        {
            return price_ * n;
        }

    protected:
        double price_;

    private:
        std::string isbn_;
};

class Disc_Quate:public Quate 
{
    public:
        Disc_Quate() = default;
        Disc_Quate(std::string &book, double price, std::size_t qty, double disc):Quate(book, price), quantity(qty), discount(disc) { }
        double net_price(std::size_t) const = 0;
        std::pair<std::size_t, double> discount_policy(void) { return {quantity, discount};}
    protected:
        std::size_t quantity;
        double discount;
};

class Bulk_Quate:public Disc_Quate
{
    public:
        using Disc_Quate::Disc_Quate;
        double net_price(std::size_t n) const override
        {
            return price_ * n * discount;
        }
};

int main(int argc, char *argv[])
{
    std::string isbn_("cpp_primer");

    Quate quate_(isbn_, 128);
    Bulk_Quate buld_quate_(isbn_, 128, 10, 0.8);

    std::cout << "ISBN: "<< quate_.isbn() << ", sale: " << 2<< ", total due:" <<quate_.net_price(2) << std::endl;
    std::cout << "ISBN: "<< buld_quate_.isbn() << ", sale: " << 2<< ", total due:" <<buld_quate_.net_price(2) << std::endl;
    std::cout <<"Discount policy: " << buld_quate_.discount_policy().first <<", " << buld_quate_.discount_policy().second << std::endl;

    return 0;
}

