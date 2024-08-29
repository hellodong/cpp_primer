

#include <string>
#include <iostream>

class Quate{
    public:
        Quate() = default;
        Quate(std::string &_isbn, double _price = 0.0):price_(_price), isbn_(_isbn) {}
        std::string isbn(void) const {return isbn_;}
        virtual double net_price(std::size_t n = 0) const
        {
            return price_ * n;
        }

    protected:
        double price_;

    private:
        std::string isbn_;
};

class Bulk_Quate:public Quate
{
    public:
       Bulk_Quate() = default;
       Bulk_Quate(std::string &_isbn, double _price = 0.0, double _discount = 1):Quate(_isbn,_price), discount_(_discount) {}
       double net_price(std::size_t n = 2) const override
       {
            return price_ * n * discount_;
       }
    private:
        double discount_;
};

void bulkQuate2quate2bulkQquate(void)
{
    std::string isbn("cpp primer");
    Bulk_Quate bulk(isbn, 98, 0.8);
    Quate *base = &bulk;
    Bulk_Quate *bulkp = dynamic_cast<Bulk_Quate *>(base);
    std::cout << bulkp->net_price(1) << std::endl;
}

void based_virtual_method_involved_with_dft(Quate &baseRef)
{
    std::cout << baseRef.net_price() << std::endl;
}

int main(int argc, char *argv[])
{
    std::string isbn_("cpp_primer");

    Quate quate_(isbn_, 128);
    Bulk_Quate buld_quate_(isbn_, 128, 0.8);

    std::cout << "ISBN: "<< quate_.isbn() << ", sale: " << 2<< ", total due:" <<quate_.net_price(2) << std::endl;
    std::cout << "ISBN: "<< buld_quate_.isbn() << ", sale: " << 2<< ", total due:" <<buld_quate_.net_price(2) << std::endl;

    std::cout << "Quate default net_price: " << std::endl;
    based_virtual_method_involved_with_dft(quate_);

    std::cout << "Bulk_Quate default net_price: " << std::endl;
    based_virtual_method_involved_with_dft(quate_);
    return 0;
}
