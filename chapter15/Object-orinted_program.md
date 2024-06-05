## Object-orinted Program
面向对象程序涉及基于三个基本概念: 数据抽象、继承和动态绑定。在很多程序中都存在着一些相互关联但是有细微差别的概念。例如:书店中不同书籍的定价策略可能不同：有的书籍按原价销售，有的则按打折销售。

### OOP：概述
**面向对象程序设计**的核心思想是数据抽象、继承和动态绑定。*数据抽象*，将类的接口与实现分离；*继承*，定义相似的类型并对其相似关系建模；*动态绑定*，在一定程度上忽略相似类型区别，而以统一方式使用它们对象。

##### 继承
在层次关系的根部有一个**基类**，其他类直接或间接从基类继承而来，这些继承得到的类称为**派生类**。基类负责定义在层次关系中所有类共同拥有的成员，每个派生类定义各自特有成员。<br>
不同定价策略建模，我们定义一个名为Quote的类，并作为层次关系中的基类。Quote对象表示按原价销售的书籍。Quote派生出另一个名为Bulk_quote的类，表示打折销售书籍。
```C++
class Quote{
    public:
        std::string isbn() const;
        virtual double net_price(std::size_t n) const;
};
```
对于某些函数，基类希望它派生类各自定义适合自身的版本，此时基类就将这些函数声明成**虚函数(virtual function)**。<br>
派生类必须通过使用*类派生列表*明确指出它是从哪个基类继承而来，类派生列表的形式：首先一个冒号，后面紧跟逗号分隔的基类列表，其中每个基类前面可以有访问说明符:
```C++
class Bulk_quote: public Quote{
    public:
        double net_price(std::size_t ) const override;
}
```
因为Bulk_quote在它的派生列表中使用了public关键字，我们完全可以把Bulk_quote的对象当成Quote的对象来使用。<br>
派生类必须在其内部对所有重新定义的虚函数进行声明。派生类可以在这样的函数之前加virtual关键字，但并不是非得这么做。C++11新标准允许派生类显式注明他将使用哪个成员函数改写基类的虚函数，具体措施是在该函数的形参列表之后增加一个override关键字。

##### 动态绑定 
通过使用**动态绑定(dynamic binding)**, 我们能用同一段代码分别处理Quate和Bulk_quote对象。举个例子:

```c++
double print_total(ostream &os, const Quate &item, size_t n)
{
    double ret = item.net_price(n);
    return ret;
}

print_total(std::cout, basic, 20);
print_total(std::cout, bulk, 20);
```
第一个函数调用将Quate对象传入print_total, 因此执行的是Quate的版本。第二个函数调用，实参是Bulk_quote，因此执行的是Bulk_quote版本。在上述过程中函数的运行版本由实参决定，在运行时选择函数的版本，所以动态绑定有时又被称为**运行时绑定**

### 定义基类和派生类
#### 定义基类
完成Quate类的定义:
```C++
class Quate{
    public:
        Quate() = default;
        Quate(std::string &_isbn, double _price = 0.0):price_(_price), isbn_(_isbn) {}
        std::string isbn(void) const {return isbn_;}
        virtual double net_price(std::size_t n) const
        {
            return price_ * n;
        }

        virtual ~Quate() = default; //对析构函数进行动态绑定

    protected:
        double price_;

    private:
        std::string isbn_;
};

```
作为继承关系中根节点的类通常会定义一个虚析构函数。

##### 成员函数与继承


##### 动态绑定
在C++语言中，我们使用基类的引用(或指针)调用一个虚函数时将发生动态绑定

### 定义基类和派生类


