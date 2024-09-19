
#ifndef _BASKET_QUATE_H_
#define _BASKET_QUATE_H_

#include <string>
#include <memory>
#include <set>

class Quate{
    public:
        Quate() = default;
        Quate(std::string &_isbn, double _price = 0.0):price_(_price), isbn_(_isbn) {}
        std::string isbn(void) const {return isbn_;}
        virtual double net_price(std::size_t n) const
        {
            return price_ * n;
        }
        virtual Quate *clone() const & { return new Quate(*this);}
        virtual Quate *clone() const && {return new Quate(std::move(*this));}

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

        Disc_Quate *clone() const & = 0;
        Disc_Quate *clone() const && = 0;
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
        Bulk_Quate * clone() const & {return new Bulk_Quate(*this);}
        Bulk_Quate * clone() const && {return new Bulk_Quate(std::move(*this));}
};

class Basket
{
    public:
        void add_item(const std::shared_ptr<Quate> &sale)
        {
            items.insert(sale);
        }
        void add_item(const Quate &sale)
        {
            items.insert(std::shared_ptr<Quate>(sale.clone()));
        }

        void add_item(Quate &&sale)
        {
            items.insert(std::shared_ptr<Quate>(std::move(sale).clone()));
        }
        double total_receipt(std::ostream &) const;
    private:
        static bool compare(const std::shared_ptr<Quate> &lhs, const std::shared_ptr<Quate> &rhs);
        std::multiset<std::shared_ptr<Quate>, decltype(compare) *> items{compare};
};

#endif //basket_quate.h
