## Object-orinted Program
&ensp;&ensp;&ensp;&ensp;面向对象程序涉及基于三个基本概念: 数据抽象、继承和动态绑定。在很多程序中都存在着一些相互关联但是有细微差别的概念。例如:书店中不同书籍的定价策略可能不同：有的书籍按原价销售，有的则按打折销售。

### OOP：概述
&ensp;&ensp;&ensp;&ensp;**面向对象程序设计**的核心思想是数据抽象、继承和动态绑定。*数据抽象*，将类的接口与实现分离；*继承*，定义相似的类型并对其相似关系建模；*动态绑定*，在一定程度上忽略相似类型区别，而以统一方式使用它们对象。

##### 继承
&ensp;&ensp;&ensp;&ensp;在层次关系的根部有一个**基类**，其他类直接或间接从基类继承而来，这些继承得到的类称为**派生类**。基类负责定义在层次关系中所有类共同拥有的成员，每个派生类定义各自特有成员。<br>
&ensp;&ensp;&ensp;&ensp;不同定价策略建模，我们定义一个名为Quote的类，并作为层次关系中的基类。Quote对象表示按原价销售的书籍。Quote派生出另一个名为Bulk_quote的类，表示打折销售书籍。
```C++
class Quote{
    public:
        std::string isbn() const;
        virtual double net_price(std::size_t n) const;
};
```
&ensp;&ensp;&ensp;&ensp;对于某些函数，基类希望它派生类各自定义适合自身的版本，此时基类就将这些函数声明成**虚函数(virtual function)**。<br>
&ensp;&ensp;派生类必须通过使用*类派生列表*明确指出它是从哪个基类继承而来，类派生列表的形式：首先一个冒号，后面紧跟逗号分隔的基类列表，其中每个基类前面可以有访问说明符:
```C++
class Bulk_quote: public Quote{
    public:
        double net_price(std::size_t ) const override;
}
```
&ensp;&ensp;&ensp;&ensp;因为Bulk_quote在它的派生列表中使用了public关键字，我们完全可以把Bulk_quote的对象当成Quote的对象来使用。<br>
&ensp;&ensp;&ensp;&ensp;派生类必须在其内部对所有重新定义的虚函数进行声明。派生类可以在这样的函数之前加virtual关键字，但并不是非得这么做。C++11新标准允许派生类显式注明他将使用哪个成员函数改写基类的虚函数，具体措施是在该函数的形参列表之后增加一个override关键字。

##### 动态绑定 
&ensp;&ensp;&ensp;&ensp;通过使用**动态绑定(dynamic binding)**, 我们能用同一段代码分别处理Quate和Bulk_quote对象。举个例子:

```c++
double print_total(ostream &os, const Quate &item, size_t n)
{
    double ret = item.net_price(n);
    return ret;
}

print_total(std::cout, basic, 20);
print_total(std::cout, bulk, 20);
```
&ensp;&ensp;&ensp;&ensp;第一个函数调用将Quate对象传入print_total, 因此执行的是Quate的版本。第二个函数调用，实参是Bulk_quote，因此执行的是Bulk_quote版本。在上述过程中函数的运行版本由实参决定，在运行时选择函数的版本，所以动态绑定有时又被称为**运行时绑定**

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
- 基类通常都应该定义一个虚析构函数，即使该函数不执行任何实际操作也是如此

##### 成员函数与继承
&ensp;&ensp;&ensp;&ensp;派生类可以继承其基类的成员，然而当遇到如**net_price**(虚函数)这样与类型相关的操作时，派生类必须对其重新定义。派生类需要对这些操作提供自己的重新定义 **覆盖(override)** 从基类继承而来的旧定义。

&ensp;&ensp;&ensp;&ensp;在C++语言中，基类必须将它的两种成员函数区分开来: 一种是**虚函数** 基类希望其派生类进行覆盖的函数；另一种是派生类直接继承而不改变的函数。当我们是用指针或引用调用虚函数时，该调用动态绑定：根据引用或指针所绑定的对象类型不同，该调用可能执行基类的版本，也可能执行某个派生类的版本。

&ensp;&ensp;&ensp;&ensp;基类通过在其成员函数的声明语句之前加上关键字virtual使得该函数执行动态绑定。任何构造函数之外的非静态函数都可以是虚函数。关键字virtual只能出现在类的声明中，而不能用于类外部的函数定义。如果基类把一个函数定义声明成虚函数，则该函数在派生类中也是隐式的虚函数。

&ensp;&ensp;&ensp;&ensp;成员函数没被声明成虚函数，则其解析过程发生在编译时而非运行时。

##### 访问控制与继承
&ensp;&ensp;&ensp;&ensp;派生类可以继承定义在基类中的成员，但是派生类成员函数不一定有权访问从基类继承而来的成员。派生类可以访问共有成员，而不能访问私有成员。有时基类希望它的派生类有权访问该成员，但同时禁止其他用户访问。我们用 **受保护的(protected)** 访问运算符说明这样的成员。

#### 定义派生类
&ensp;&ensp;&ensp;&ensp;派生类必须通过使用 **派生类列表(class derivation list)** 明确指出它是从哪个基类继承而来的。类派生列表的形式是： 首先是一个冒号，后面紧跟逗号分隔的基类列表，其中每个基类前面可以有以下三种访问说明符中的一个：public、protected 或者private。
&ensp;&ensp;&ensp;&ensp;派生类必须将其继承而来的成员函数中需要覆盖的那些重新声明，因此，我们的Bulk_quate类必须包含一个net_price成员:
```C++
class Bulk_Quate:public Quate
{
    public:
       Bulk_Quate() = default;
       Bulk_Quate(std::string &_isbn, double _price = 0.0, double _discount = 1):Quate(_isbn,_price), discount_(_discount) {}
       double net_price(std::size_t n) const override
       {
            return price_ * n * discount_;
       }
    private:
        double discount_;
};
```
&ensp;&ensp;&ensp;&ensp;如果一个派生类是public的，则基类的共有成员也是派生类接口的组成部分。此外，我们能将共有派生类的对象绑定到基类的引用或指针上。因为我们在派生类列表中使用了public，所以Bulk_quote的接口隐式地包含isbn函数。

大多数类都只继承自一个类，这种形式地继承称作单继承。

##### 派生类中的虚函数
&ensp;&ensp;&ensp;&ensp;派生类经常(但不总是)覆盖它继承的虚函数。如果派生类没有覆盖其基类中的某个虚函数，则该虚函数的行为类似于其他的普通成员，派生类会直接继承其在基类中的版本。派生类可以在它覆盖的函数前使用virtual关键字，但不是非得这么做。

&ensp;&ensp;&ensp;&ensp;C++11新标准允许派生类显示地注明它使用某个成员函数覆盖它继承的虚函数。具体做法是在形参列表后面、或者在const成员函数的const关键字后面、或者在引用成员函数的引用限定符后面添加一个关键字override。

##### 派生类对象及派生类向基类的类型转换
&ensp;&ensp;&ensp;&ensp;一个派生类对象包含多个组成部分：一个含有派生类自己定义(非静态)的成员的子对象，以及一个与该派生类继承的基类对应的子对象，如果有多个基类，那么这样的子对象也有多个。因此，一个Bulk_quote对象将包含四个数据元素：它从Quate继承而来的bookNO和price数据成员，以及Bulk_quote自己定义的min_qty和discount成员。
&ensp;&ensp;&ensp;&ensp;C++标准并没有明确规定派生类的对象在内存中如何分布，但是我们可以认为Bulk_quote的对象包含如下图所示两部分。

![](./images/derived_base_construct.png)

&ensp;&ensp;&ensp;&ensp;因为在派生类对象中含有与其基类对应的组成部分，所以我们能把派生类的对象当成基类对象来使用，而且我们也能将基类的指针或引用绑定到派生类对象中的基类部分上。
```C++
Quate item;             // 基类对象
Bulk_quote bulk;        // 派生类对象
Quate *p= &item;        // p指向Quate 对象
p = &bulk;              // p指向bulk的Quate部分
Quate &r = bulk;        // r绑定到bulk的Quate部分
```
&ensp;&ensp;&ensp;&ensp;这种转换通常称为派生类到基类的(derived-to-base)类型转换。和其他类型转换一样，编译器会隐式地执行派生类到基类地转换。这种隐式特性意味着我们可以把派生类对象或派生对象的引用用在需要基类引用的地方；同样的，我们也可以把派生类对象的指针用在需要基类指针的地方。

##### 派生类构造函数
&ensp;&ensp;&ensp;&ensp;尽管在派生类对象中含有从基类继承而来的成员，但是派生类并不能直接初始化这些成员。派生类也必须使用基类的构造函数来初始化它的基类部分。<br>
&ensp;&ensp;&ensp;&ensp;派生类对象的基类部分与派生类对象自己的数据成员都是在构造函数的初始化阶段执行初始化操作。例如接受四个参数的Bulk_quote构造函数:
```C++
class Bulk_Quate:public Quate
{
    public:
       Bulk_Quate() = default;
       Bulk_Quate(std::string &_isbn, double _price = 0.0, double _discount = 1):Quate(_isbn,_price), discount_(_discount) {}
      
    private:
        double discount_;
};
```
**Bulk_Quate** 函数将前两个参数传递给Quate的构造函数，由Quate的构造函数负责初始化Bulk_Quate的基类部分。当Quate构造函数结束后，我们构建的对象基类部分也就完成初始化了。接下来初始化由派生类直接定义的discount成员。最后运行Bulk_Quate构造函数体。<br>
除非我们特别指出，否则派生类对象的基类部分会像数据成员一样执行默认初始化。如果想使用其他的基类构造函数，我们需要以类名加圆括号内的实参列表形式为构造函数提供初始值。这些实参将帮助编译器决定到底应该选用哪个构造函数来初始化派生类对象的基类部分。

##### 派生类使用基类的成员
派生类可以访问基类的公有成员和受保护成员:
```C++
 double net_price(std::size_t n) const override
{
            return price_ * n * discount_;
}
```
 - 派生类对象不能直接初始化基类的成员

 ##### 继承与静态成员
 如果基类定义了一个静态成员，则整个继承体系中只存在该成员的唯一定义。
 ```C++
 class Base{
    public:
        static void statmem();
 };
 class Derived : public Base {
    void f(const Derived&);
 };
 ```
 静态成员遵循通用访问控制规则，基类中成员是private的，则派生类无权访问。静态成员可访问的，我们既能通过基类使用也能通过派生类使用它:
 ```C++
 void Derived::f(const Derived &derived_obj)
 {
    Base::statmem();        //正确，base定义了statmem()
    Derived::statmem();     //正确，Derived定义了statmem()
    derived_obj.statmem();  //通过Derived对象访问
    statmem();              //通过this对象访问
 }
 ```
 ##### 派生类的声明
 派生类的声明与其他类差别不大，声明中包含类名但是不包含它的派生类列表:
 ```C++
 class Bulk_quote:public Quote;  //错误，派生类列表不能出现在这里
 class Bulk_quote;               //正确，声明派生类的正确方式
 ```

 ##### 被用作基类的类
 我们想将某个类用作基类，则该类必须已经定义而非仅仅声明:
 ```C++
 class Quate;       //声明但未定义
 class Bulk_quote:public Quote {};  //错误: Quote必须被定义
 ```
 这个规定还有一层隐含的意思，一个类不能派生它本身。<br>
 一个类是基类，同时它也可以是一个派生类：
 ```C++
 class Base{};
 class D1:public Base {};
 class D2:public D1{};
 ```
 Base是D1的**直接基类(direct base)**, 是D2的**间接基类(indirect base)**。最终的派生类将包含它的直接基类的子对象以及每个间接基类的子对象。

 ##### 防止继承的发生

 有时我们会定义这样一种类，我们不希望其他类继承它。C++11新标准定义了一种防止继承发生的方法，在名后跟一个关键字final:
 ```C++
 class NoDerived final{};
 class Base {};
 class Last final: Base{};  //last不能作为基类
 class Bad: NoDerived {};   //错误，NoDerived是final的
 class Bad2: Last {};       //错误，Last是final的
 ```
#### 类型转换与继承
存在继承关系的类：我们可以将基类的指针或引用绑定到派生类对象上。例如，我们可以将Quate&指向一个Bulk_quote对象，也可以把一个Bulk_quote的对象地址赋给一个Quote*。当使用基类的引用（或指针）时，实际上我们并不清楚该引用（或指针）所绑定对象的真实类型。该对象可能是基类的对象，也可能是派生类的对象。

##### 静态类型与动态类型
当我们使用存在继承关系的类型时，必须将一个变量或其他表达式的**静态类型(static type)**与该表达式表示对象的**动态类型(dynamic type)**区分开来。表达式的静态类型在编译时总是已知的，它是变量声明时的类型或表达式生成的类型：动态类型则是变量或表达式表示的内存中对象的类型。动态类型直到运行时才可知。
```C++
double ret = item.net_price(n);
```
我们知道item的静态类型是Quote&, 它的动态类型依赖于item绑定的实参，动态类型直到运行时调用该函数时才会知道。如果我们传递一个Bulk_quote对象给print_total，则item的静态类型将与它的动态类型不一致。如前所述，item的静态类型是Quote&,而在此例中它的动态类型则是Bulk_quote。

##### 不存在从基类向派生类的隐式类型转换
之所以存在派生类向基类的类型转换是因为每个派生类对象包含一个基类部分，而基类的引用或指针可以绑定到该基类部分上。一个基类的对象既可以独立形式存在，也可以作为派生类对象一部分存在。如果基类对象不是派生类对象一部分，则它只有基类定义的成员，而不含有派生类定义的成员。不存在从基类向派生类的自动类型转换:
```C++
Quote base;
Bulk_quote* bulkp= &base;
Bulk_quote& bulkRef = base;
```
还有一种情况显得有点特别，即使一个基类指针或引用绑定在一个派生类对象上，我们也不能执行从基类向派生类的转换:
```C++
Bulk_quote bulk;
Quote *basep = &bulk;           //正确： 动态类型是Bulk_quote
Quote_quote *bulkp = basep;     //错误：不能将基类转换成派生类
```
编译器在编译时无法确定某个特定的转换在运行时是否安全，这是因为编译器只能通过检查指针或引用的静态类型来推断该转换是否合法。如果在基类中还有一个或多个虚函数，我们可以使用dynamic_cast请求一个类型转换，该转换的安全检查将在运行时执行。同样，如果我们已知某个类型向派生类的转换是安全的，则我们可以使用static_cast来强制覆盖掉编译器的检查工作。

##### 在对象之间不存在类型转换
派生类向基类的自动类型转换只对指针或引用类型有效，在派生类类型和基类类型之间不存在这样的转换。很多时候，我们确实希望将派生类对象转换成它的基类类型，但是这种转换的实际发生过程往往与我们期望有所差别。

当我们初始化或赋值一个类类型的对象时，实际上是调用某个函数。执行初始化时，我们调用构造函数；执行赋值操作时，我们调用赋值运算符。 这些成员接受引用作为参数，所以派生类向基类的转换允许我们给基类拷贝/移动操作传递一个派生类对象。这些操作不是虚函数。当我们给基类的构造函数传递一个派生类对象时，实际运行的构造函数是基类定义的那个，该构造函数只能处理基类自己的成员。类似，我们将一个派生类对象赋值给一个基类对象，则实际运行赋值运算符也是基类定义中那个，该运算符同样只能处理基类自己的成员。

我们书店类使用了合成版本的拷贝和赋值操作，现在我们只需要知道合成版本会像其他类一样逐成员执行拷贝或赋值操作：
```C++
Bulk_quote bulk;        // 派生类对象
Quote item(bulk);       // 调用Quote::Quote(const Quote&) 构造函数
item = bulk;            // 调用Quote::operator=(const Quote&)
```
当构造item时，运行Quote的拷贝构造函数。该函数只能处理bookNo和price两个成员，它负责bulk中Quote部分的成员，同时忽略掉bulk中Bulk_quote部分成员。类似，对于将Bulk赋值给item的操作来说，只有bulk中Quote部分的成员被赋值给item。

### 虚函数
如前所述，在C++语言中，当我们使用基类引用或指针调用一个虚函数时会执行动态绑定。因为我们直到运行时才能知道到底调用了哪个版本虚函数，所以所有虚函数都必须有定义。

##### 对虚函数的调用可能在运行时才被解析
当某个虚函数通过指针或引用调用时，编译器产生的代码直到运行时才能被确定应该调用哪个版本的函数。被调用的函数是与绑定到指针或引用上的对象的动态类型相匹配的那一个。必须要搞清楚一点，动态绑定只有当我们通过指针或引用调用虚函数才会发生。
当我们通过一个具有普通类型（非引用非指针）的表达式调用虚函数时，在编译时就会将调用的版本确定下来。

##### 派生类中的虚函数
当我们在派生类中覆盖了某个虚函数时，可以再一次使用virtual关键字指出该函数的性质。然而这么做并非必须，因为一旦某个函数被声明成虚函数，则在所有派生类中它都是虚函数。<br>
一个派生类的函数如果覆盖了某个继承而来的虚函数，则它的形参类型必须与被它覆盖的基类函数完全一致。同样，派生类中虚函数的返回类型也必须与基类函数匹配。该规则存在一个例外，当类的虚函数返回类型是类本身的指针或引用时，上诉规则无效。

##### final和override说明符
派生类如果定义了一个函数与基类中虚函数的名字相同但是形参列表不同，这仍然是合法行为。编译器将认为新定义的这个函数与基类中原有的函数是相互独立的。这时，派生类函数并没有覆盖掉基类中的版本。就实际编程习惯而言，这种声明往往意味着发生了错误。<br>
要想调试并发现这样的错误显然是非常困难的。在C++11新标准中我们可以使用**override** 关键字来说明派生类中的虚函数。如果我们使用override标记了某个函数，但该函数并没有覆盖已存在虚函数，此时编译器将报错：
```C++
struct B{
    virtual void f1(int) const;
    virtual void f2();
    void f3();
};

struct D1: B{
    void f1(int) const override;    //正确： f1与基类中f1匹配
    void f2(int) override;          //错误： B没有形如f2(int)的函数
    void f3() override;             //错误：f3不是虚函数
    void f4() override;             //错误：B没有名为f4的函数
};
```
只有虚函数才能被覆盖，所以编译器会拒绝D1的f3。类似，f4的声明也会发生错误，因为B中根本就没有名为f4的函数。<br>
我们还能把某个函数指定为**final**,如果我们已经把函数定义为final了，则之后任何尝试覆盖该函数操作都将引发错误:
```C++
struct D2: B{
    void f1(int) const final;   //不允许后续其他类覆盖f1(int)
};
struct D3: D2{
    void f2();          //正确：覆盖从间接基类B继承而来的f2
    void f1(int) const;//错误：D2已经将f2声明成final了
};
```
final和override说明符出现在形参列表以及尾置返回类型之后。

##### 虚函数与默认实参
虚函数也可以拥有默认实参。如果某次函数使用了默认实参，则该实参值由本次调用静态类型决定。换句话说，如果我们通过基类的引用或指针调用函数，则使用基类中定义的默认实参，即使实际运行的是派生类中函数模板也是如此。

##### 回避虚函数机制
在某些情况下，我们希望对虚函数的调用不要进行动态绑定，而是强迫执行虚函数某个特定版本。使用作用域运算可以实现这一目的:
```C++
double undiscounted = baseP->Quate::net_price(42);
```
该调用在编译时完成。<br>什么时候我们需要回避虚函数默认机制呢？通常是当一个派生类的虚函数调用它覆盖的基类虚函数版本时。

### 抽象基类
我们定义一个新的名为Disc_quote的类支持不同的折扣策略，其中Disc_quote负责保存购买量的值和折扣值。其他的表示某种特定策略的类(如Bulk_quote)将分别继承自Disc_quote,每个派生类通过定义自己的net_price函数来实现各自的折扣策略。
##### 纯虚函数
Disc_quote类表示的是一本打折书籍的通用概念，而非某种具体的折扣策略。<br>我们将net_price定义成**纯虚(pure virtual)函数**从而令程序实现我们的设计意图，这样做可以清晰明了告诉用于当前这个net_price函数是没有实际意义的。和普通虚函数不一样，一个纯虚函数无须定义。我们通过在函数体位置书写=0就可以将一个虚函数说明为纯虚函数。其中，=0只能出现在类内部的虚函数声明语句出:
```C++
class Disc_quote: public Quote{
    public:
        Disc_quote() = default;
        Disc_quote(const std::string &book, double price, std::size_t qty, double disc):Quote(book, price), quantity(qty), discount(disc) {}
        double net_price(std::size_t) const = 0;
    protected:
        std::size_t quantity = 0;
        double discount = 0.0;
};
```

##### 含有纯虚函数的类是抽象基类
含有纯虚函数的类是抽象基类(abstract base class)。抽象基类负责定义接口，而后续的其他类可以覆盖该接口。我们不能(直接)创建一个抽象基类对象。
```C++
Disc_quote discounted;      //错误： 不能定义Disc_quote的对象
Bulk_quote bulk;            //正确： Bulk_quote中没有纯虚函数
```
Disc_quote 的派生类必须给出自己的net_price定义，否则他们仍将是抽象基类。

##### 派生类构造函数只初始化它的直接基类
```C++
class Bulk_quote : public Disc_quote {
    public:
        Bulk_quote() = default;
        Bulk_quote(const std::string &book, double price, std::size_t qty, double disc):Disc_quote(book, price, qty, disc) {}
        double net_price(std::size_t) const override;
};
```
这个版本的Bulk_quote的直接基类是Disc_quote, 间接基类是Quote。每个Bulk_quote对象包含三个子对象:一个(空的)Bulk_quote部分、一个Disc_quote子对象和一个Quote子对象。<br>

### 访问控制与继承
每个类分别控制其成员对于派生类来说是否**可访问(accessible)**。
##### 受保护的成员
一个类使用protected关键字来声明那些它希望与派生类分享但不想被其他公共访问使用的成员：
- 和私有成员类似，受保护的成员对于类的用户来说是不可访问的
- 和公有成员类似，受保护的成员对于派生类和友元来说是可访问的
- 派生类成员或友元只能通过派生类对象访问基类受保护成员。派生类对于一个基类对象受保护成员没有任何访问特权。

理解最后一条，如下例子：
```C++
class Base {
    protected:
        int prot_element;       // protected成员
};

class Sneaky:public Base {
    friend void clobber(Sneaky &);      //能访问Sneaky::prot_element
    friend void clobber(Base &);        //不能访问Base::prot_mem
    int j;                              //j默认是private
};

// 正确：clobber能访问Sneaky对象的private和protected成员
void clobber(Sneaky &s) {s.j = s.prot_mem = 0;}
// 错误：clobber不能访问Base的protected成员
void clobber(Base &b) {b.prot_mem = 0;}
```

##### 公有、私有和受保护继承
某个类对其继承而来的成员访问权限受两个因素影响：一是在基类中该成员访问说明符，二是在派生类的派生列表的访问说明符。考虑如下继承关系:
```C++
class Base{
    public:
        void base_pub_mem();     //public 成员
    protected:
        int base_prot_mem;       //protected 成员
    private:
        char base_priv_mem;      //private 成员
};

struct Pub_Derv:public Base{
    //正确：派生类能访问protected成员
    int f() {return base_prot_mem;}
    //错误:private成员对于派生类来说是不可访问的
    char g() {return base_priv_mem;};
};

struct Pirv_Dev: private Base{
    //private不影响派生类的访问权限
    int f1() const {return base_prot_mem;}
};
```
派生类访问说明符对于派生类的成员(及友元)能否访问其直接基类的成员没什么影响。对基类成员的访问权限只与基类中的访问说明符有关。Pub_Derv和Priv_Derv都能访问受保护的成员prot_mem,同时它们都不能访问私有成员priv_mem。<br>
派生类访问说明符的目的是控制派生类用户（包括派生类的派生类在内）对于基类成员访问权限：
```C++
Pub_Derv d1;            //继承自Base的成员是public的
Priv_Derv d2;           //继承自Base的成员是private的
d1.base_pub_mem();      //正确:base_pub_mem在派生类中是public的
d2.base_pub_mem();      //错误:base_pub_mem在派生类中是private的
```
Pub_Derv和Priv_Derv都继承了base_pub_mem函数。如果继承是public的，则成员将遵循其原有访问说明符，此时d1可以调用base_pub_mem函数。在Priv_Derv中，base的成员是private，因此类用户不能调用base_pub_mem。<br>
派生类访问说明符还可以控制继承自派生类的新类访问权限：
```C++
struct Derived_from_public:public Pub_Derv{
    // 正确： Base::base_prot_mem在Pub_Derv中仍然是protected的
    int use_base() {return base_prot_mem;}
};
struct Derived_from_Private:public Priv_Derv{
    // 错误：Base::prot_mem在Priv_Derv中是private的
    int use_base() {return base_prot_mem;}
};
```
Pub_Derv的派生类之所以能访问Base的base_prot_mem成员是因为该成员在Pub_Derv中仍然是受保护的。相反，Priv_Derv的派生类无法执行类的访问，对于它们来说，Priv_Derv继承自Base的所有成员都是私有的。<br>
假设我们之前还定义了一个名为Prot_Derv的类，它采用protected继承，则Base的所有公有成员在新定义的类中都是受保护的。Prot_Derv的用户不能访问base_pub_mem，但是Prot_Derv的成员和友元可以访问那些继承而来的成员。

##### 派生类向基类转换的可访问性
派生类向基类的转换是否可访问由使用该转换的代码决定，同时派生类的派生访问说明符也会有影响。假定D继承自B：
- 只有当D public继承B时，用户代码才能使用派生类向基类的转换；如果D继承B的方式是受保护的或者私有的，则用户代码不能使用该转换
- 不论D以什么方式继承B，D的成员函数和友元都能使用派生类向基类的转换：派生类向其直接基类的类型转换对于派生类的成员和友元来说永远是可访问的
- 如果D继承B的方式是公有的或者受保护的，则D的派生类成员和友元可以使用D向B的类型转换；反之，如果D继承B的方式是私有的，则不能使用。

##### 友元与继承
友元关系不能传递，友元关系同样也不能继承。基类的友元在访问派生类成员时不具有特殊性，类似。派生类友元也不能随意访问基类成员：
```C++
class Base {
    friend class Pal;   //Pal在访问Base的派生类时不具有特殊性
};

class Pal{
    public:
        int f(base b) {return b.base_prot_mem;}     //正确：Pal是Base的友元
        int f2(Sneaky s) {return s.j;}              //错误：Pal不是Sneaky的友元
        int f3(Senaky s) {return s.base_prot_mem;}      //正确： Pal是Base的友元
};
```
如前所述，每个类负责控制自己的成员访问权限，因此尽管看起来有点儿奇怪，但f3确实是正确的。Pal是Base的友元，所以Pal能够访问Base对象的成员，这种可访问性包括了Base对象内嵌在其派生类对象中的情况。<br>
当一个类将另一个类声明为友元时，这种友元关系只对做出声明的类有效。对于原来那个类来说，其友元基类或派生类不具有特殊访问能力：
```C++
calss D2: public Pal {
    public:
        int mem(Base b)
        {
            return b.base_prot_mem;     //错误： 友元关系不能继承
        }
};
```
- 不能继承友元关系；每个类负责控制各自成员访问权限。

##### 改变个别成员的可访问性
有时我们需要改变派生类继承的某个名字的访问级别，通过使用using声明可以达到这一目的：
```C++
class Base {
    public:
        std::size_t size() const {return n;}
    protected:
        std::size_t n;
};

class Derived: private Base{
    public:
        using Base::size;
    protected:
        using Base::n;
};
```
因为Derived使用了私有继承，所以继承而来的成员size和n是Derived的私有成员。然而，我们使用using声明语句改变了这些成员的可访问性。改变之后，Derived的用户将可以使用size成员，而Derived的派生类将能使用n。<br>
通过在类的内部使用using声明语句，我们可以将该类的直接或间接基类中任何可访问成员标记出来。using声明语句中名字的访问权限由该using声明语句之前的访问说明符来决定。也就是说，如果一条using声明语句出现在类的private部分，则该名字只能被类的成员和友元访问；如果using声明语句位于public部分，则类的所有用户都能访问它；如果using声明语句位于protected部分，则该名字对于成员、友元和派生类是可访问的。

##### 默认的继承保护继承
我们曾介绍使用struct和class关键字定义的类具有不同默认访问说明符。类似，默认派生运算符定义派生类所用关键字来决定。默认情况下，使用class关键字定义的派生类是私有继承的;而使用struct关键字定义的派生类是公有继承的。<br>
struct和class唯一的差别就是默认成员访问说明符以及默认派生访问说明符；除此之外，再无其他不同之处。

### 继承中的类作用域
每个类定义自己的作用域，在这个作用域内我们定义类的成员。当存在继承关系时，派生类的作用域嵌套在其基类作用域内。如果一个名字在派生类作用域内无法正确解析，则编译器将继续在外层基类作用域寻找该名字定义。<br>
恰恰因为类作用域有这种继承嵌套关系，所以派生类才能像使用自己成员一样使用基类成员：
```C++
Bulk_quote bulk;
std::cout << bulk.isbn()<< std::endl;
```
名字isbn的解析将按照下述过程所示：

- 因为我们通过Bulk_quote的对象调用isbn的，所以首先在Bulk_quote中查找，这一步没有找到名字isbn。
- 因为Bulk_quote是Disc_quote的派生类，所以Disc_quote中查找，仍然找不到
- 因为Disc_quote是Quote的派生类，接着找Quote;此时找到isbn，我们使用isbn最终解析为Quote的isbn。

##### 在编译时进行名字查找
一个对象、引用或指针的静态类型决定了该对象的哪些成员是可见的。即使静态类型与动态类型可能不一致(当使用基类的引用或指针时会发生这种情况)，但是我们能使用哪些成员仍然时由静态类型决定的。举个例子，我们可以给Disc_quote添加一个新成员，该成员返回一个存有最小（或最大）数量及折扣价格的pair：
```C++
class Disc_quote:public Quote{
    public:
        std::pair<size_t, double> discount_policy() const
        {
            return {quantity, discount};
        }
};
```
我们只能通过Disc_quote及其派生类对象、引用或指针使用discount_policy:
```C++
Bulk_quote bulk;
Bulk_quote *bulkP = &bulk;      //静态类型与动态类型不一致
Quote *itemP = &bulk;           //静态类型与动态类型不一致
bulkP->discount_policy();       //正确：bulkP的类型是Bulk_quote*
itemP->discount_policy();       //错误: itemP的类型是Quote*
```
尽管bulk中确实含有一个名为discount_policy的成员，但是该成员对于itemP确是不可见的。itemP的类型是Quote的指针，意味着对discount_policy的搜索将从Quote开始。显然Quote不包含名为discount_policy的成员，所以我们无法通过Quote的对象、引用或指针调用discount_policy。

##### 名字冲突与继承
派生类也能重用定义在其直接基类或间接基类中的名字，此时定义在内层作用域(派生类)名字将隐藏定义在外层作用域(基类)名字:
```C++
struct Base {
    Base(): mem(0) {}
    protected:
        int mem;
};

struct Derived: Base{
    Derived(int i):mem(i) {}        // 用i初始化Derived::mem, Base::mem 进行默认初始化
    int get_mem() {return mem;}     // 返回Derived::mem
    protected:
        int mem;                    //隐藏基类中的mem
};
```
get_mem中mem引用解析结果是定义在Derived中的名字。

- 派生类成员将隐藏同名基类成员

我们可以通过作用域运算符来使用一个被隐藏的基类成员:
```C++
struct Derived:Base{
    int get_base_mem() {return Base::mem;}
};
```
作用域运算符将覆盖掉原有的查找规则，并指示编译器从Base类作用域开始查找mem。

##### 名字查找先于类型检查
声明在内层作用域的函数并不会重载声明在外层作用域的函数。因此，定义派生类函数也不会重载其基类中的成员。和其他作用域一样，如果派生类的成员与基类某个成员同名，则派生类将在其作用域内隐藏该基类成员。即使派生类成员和基类成员形参列表不一致，基类成员也仍然会被隐藏掉:
```C++
struct Base {
    int memfcn();
};
struct Derived:Base 
{
    int memfcn(int);
};
Derived d; Base b;
b.memfcn();                 //调用Base::memfcn
d.memfcn(10);               //调用Derived::memfcn
d.memfcn();                 //错误: 参数列表为空的memfcn被隐藏了
d.Base::memfcn();           //正确：调用Base::memfcn
```

##### 虚函数与作用域
我们现在可以理解为什么基类与派生类中的虚函数必须有相同形参列表了。假如基类与派生类的虚函数接受的实参不同，则我们就无法通过基类的引用或指针调用派生类虚函数了：
```C++
class Base{
    public:
        virtual int fcn();
};
class D1:public Base{
    public:
        int fcn(int);           // 形参列表与Base中的fcn不一致
        virtual void f2();      // 是一个新的虚函数，在Base中不存在
};
class D2:public D1{
    public:
        int fcn(int);   //是一个非虚函数，隐藏了D1::fcn(int)
        int fcn();      //覆盖了Base的虚函数fcn
        void f2();      //覆盖了D1的虚函数f2
};
```
##### 覆盖重载函数
成员函数无论是否是虚函数都能被重载。派生类可以覆盖重载函数的0个或多个实例。如果派生类希望所有重载版本对于它来说都是可见的，那么它就要覆盖所有版本，或者一个也不覆盖。<br>
为重载的成员提供一条using声明语句，这样我们就无须覆盖基类中每一个重载版本了。using声明语句指定一个名字而不指定形参列表，所以一条基类成员函数的using声明语句就可以把该函数的所有重载实例添加到派生类作用域中。此时，派生类只需要定义其特有函数就可以了，无须为继承而来的其他函数重新定义。

### 构造函数与拷贝控制
如果一个类(基类或派生类)没有定义拷贝控制操作，则编译器将为它合成一个版本。当然，这个合成版本也可以定义成被删除函数。

#### 虚析构函数
继承关系对基类拷贝控制最直接的影响是基类通常应该定义一个虚析构函数，这样我们就能动态分配继承体系中的对象了。<br>
如前所述，我们delete一个动态分配的对象指针时将执行析构函数。如果该指针指向继承体系中某个类型，则有可能出现指针的静态类型与被删除对象动态类型不符情况。例如，我们delete一个Quote *类型指针，则该指针可能实际指向了一个Bulk_quote类型对象。编译器必须清楚它应该执行的是Bulk_quote的析构函数。和其他函数一样，我们通过在基类中将析构函数定义成虚函数确保执行正确的析构函数：
```C++
class Quote{
    public:
        virtual ~Quote() = default;  //动态绑定析构函数
};
```
和其他虚函数一样，析构函数的虚属性也会被继承。因此，无论Quote的派生类使用合成的析构函数还是定义自己的析构函数，都将是虚析构函数。只要基类的析构函数是虚函数，就能确保当我们delete基类指针时将运行正确的析构函数版本：
```C++
Quote *itemP = new Quote;   //静态类型与动态类型一致
delete itemp;               //调用Quote的析构函数
itemP = new Bulk_quote;     //静态类型与动态类型不一致
delete itemP;               //调用Bulk_quote的析构函数
```

- 如果基类的析构函数不是虚函数，则delete一个指向派生类对象的基类指针将产生未定义行为

之前我们介绍过一条经验准则，如果一个类需要析构函数，那么它也需要拷贝和赋值操作。基类的析构函数并不遵循上述准则，它是一个重要例外。一个基类总是需要析构函数，而且它能将析构函数设定为虚函数。

##### 虚析构函数将阻止合成移动操作
如果一个类定义了析构函数，即使它通过=default的形式使用了合成版本，编译器也不会为这个类合成移动操作。

#### 合成拷贝控制与继承
基类或派生类的合成拷贝控制成员行为与其他合成构造函数、赋值运算符或析构函数类似：他们对类本身的成员依次进行初始化、赋值或销毁操作。此外，这些合成的成员还负责使用直接基类中对应的操作对一个对象的直接基类部分进行初始化、赋值或销毁操作。例如:
- 合成的Bulk_quote默认构造函数运行Disc_quote默认构造函数，后者又运行Quote的默认构造函数
- Quote的默认构造函数将bookNo成员默认初始化为空字符串，同时使用类内初始值将price初始化为0
- Quote的构造函数完成后，继续执行Disc_quote的构造函数，它使用类内初始值初始化qty和discount。
- Disc_quote的构造函数完成后，继续执行Bulk_quote的构造函数，但是它什么具体工作也不做

在我们的Quote继承体系中，所有类都是用合成的析构函数。其中，派生类隐式的使用而基类通过将其虚析构函数定义成=default而显示的使用。一如既往，合成的析构函数体是空的，其隐式的析构部分负责销毁类成员。对于派生类析构函数来说，它除了销毁派生类自己的成员外，还负责销毁派生类直接基类；该直接基类又销毁它自己的直接基类，以此类推直至继承链的顶端。<br>
如前所述，Quote因为定义了析构函数而不能拥有合成的移动操作，因此当我们移动Quote对象时实际使用的是合成的拷贝操作。如我们即将看到那样，Quote没有移动操作意味这它的派生类没有。

##### 派生类中删除的拷贝控制与基类的关系
基类或派生类也能出于同样的原因将其合成的默认构造函数或者任何一个拷贝控制成员定义成被删除的函数。此外，某些定义基类的方式也可能导致有的派生类成员成为被删除的函数:
 - 如果基类中的默认构造函数、拷贝构造函数、拷贝赋值运算符或析构函数是被删除的函数或者不可访问，则派生类中对应的成员将是被删除的，编译器不能使用基类成员执行派生类对象基类部分的构造、赋值和销毁操作
 - 如果基类中一个不可访问的或删除掉的析构函数，则派生类中合成的默认和拷贝构造函数将是被删除的，编译器无法销毁派生类对象的基类部分。
 - 和过去一样，编译器不会合成一个删除掉的移动操作。当我们使用=default请求一个移动操作时，如果基类中对应操作时删除的或不可访问的，那么派生类中该函数将是被删除的，派生类对象基类部分不可移动。同样，如果基类的析构函数是删除的或不可访问的，则派生类移动构造函数也将是被删除的。

 举个例子，对于下面基类B来说:
 ```C++
 class B{
    public:
        B();
        B(const B&) = delete;
 };
  
class D: public B{
    //没有声明任何构造函数
};

D d;                //正确：D的合成默认构造函数使用B的默认构造函数
D d2(d);            //错误：D的合成拷贝构造函数是被删除的
D d3(std::move(d)); //错误：隐式使用D的被删除的拷贝构造函数
 ```
 基类B含有一个可访问默认构造函数和一个显示删除拷贝构造函数。因为我们定义了拷贝构造函数，所以编译器将不会为B合成一个移动构造函数。我们既不能移动也不能拷贝B的对象。如果B的派生类希望它自己的对象能被移动和拷贝，则派生类需要自定义相应版本的构造函数。当然，在这一过程中派生类还必须考虑如何移动或拷贝基本部分成员。在实际编程过程中，如果在基类中没有默认、拷贝或移动构造函数，则一般情况下派生类也不会定义相应操作。

 ##### 移动操作与继承
 如前所述，大多数基类都会定义一个虚析构函数。因此默认情况下，基类通常不含有合成的移动操作，而且在它的派生类中也没有合成的移动操作。<br>
 基类缺少移动操作会阻止派生类拥有自己的合成移动操作，所以当我们确实需要执行移动操作时应该首先在基类中定义。我们的Quote可以使用合成的版本，不过前提是Quote必须显示地定义这些成员。一旦Quote定义了自己地移动操作，那么它必须同时显示地定义拷贝操作：
 ```C++
 class Quote {
    public:
        Quote() = default;
        Quote(const Quote &) = default;     //对成员依次拷贝
        Quote(Quote&&) = default;           //对成员依次拷贝
        Quote &operator=(const Quote &) = default;  //拷贝赋值
        Quote &operator=(Quote &&) = default;       //移动赋值
        virtual ~Quote() = default;
 };
 ```
 上面地定义，我们就能对Quote的对象逐成员分别进行拷贝、移动、赋值和销毁。除非Quote的派生类中含有排斥移动的成员，否则将自动获得合成的移动操作。

#### 派生类的拷贝控制成员
派生类构造函数在其初始化阶段中不但要初始化派生类自己的成员，还负责初始化派生类对象的基类部分。因此，派生类的拷贝和移动构造函数在拷贝和移动自自有成员同时，也要拷贝和移动基类部分成员。类似，派生类赋值运算符也必须为其基类部分成员赋值。<br>
构造函数及赋值运算符不同，析构函数只负责销毁派生类自己分配的资源。对象的成员是被隐式销毁的；类似的，派生类对象基类部分也是自动销毁的。

##### 定义派生类的拷贝或移动构造函数
当为派生类定义拷贝或移动构造函数时，我们通常使用对应的基类构造函数初始化对象的基类部分：
```C++
class Base{};
class D:public Base{
    //默认情况下，基类的默认构造函数初始化对象的基类部分
    //要想使用拷贝或移动构造函数，我们必须在构造函数初始值列表中显示地调用构造函数
    D(const D& d):Base(d)           // 拷贝基类成员
    D(D&& d):Base(std::move(d))     // 移动基类成员
};
```
初始值Base(d)将一个D对象传递给基类构造函数。尽管从道理上来说，Base可以包含一个参数类型为D地构造函数，但是在实际编程过程中通常不会这么做。相反，Base(d)一般会匹配Base拷贝构造函数。D类型对象d将被绑定的那个到该构造函数的Base&形参上。Base拷贝构造函数负责将d的基类部分拷贝给要创建的对象。假如我们没有提供基类的初始值的话:
```C++
// D 找个拷贝构造函数很可能不正确定义
// 基类部分被默认初始化，而非拷贝
D(const D& d)   //成员初始值，但是没有提供基类初始值
{/*   */}
```
在上面例子中，Base的默认构造函数将被用来初始化D对象的基类部分。假定D的构造函数从d中拷贝了派生类成员，则这个新构建对象的配置将非常奇怪：它的base成员被赋予默认值，而D成员值则是从其他对象拷贝而来。

##### 派生类赋值运算符
与拷贝和移动构造函数一样，派生类的赋值运算符也必须显式地为基类部分赋值:
```C++
// Base::operator=(const Base &) 不会自动调用
D &D::operator=(const D &rhs)
{
    Base::operator=(rhs);   //为基类部分赋值
    //按照过去方式为派生类成员赋值
    return *this;
}
```
上面运算符首先显示调用基类赋值运算符，令其为派生类对象基类部分赋值。基类运算符正确处理自赋值情况，如果赋值命令是正确地，则基类运算符将释放掉左侧运算符对象的基类部分旧值，然后利用rhs为其赋新值。随后，我们继续进行其他为派生类成员赋值的工作。<br>
无论基类构造函数或赋值运算符是自定义版本还是合成版本，派生类对应操作都能使用它们。

##### 派生类析构函数
在析构函数执行完成后，对象成员会被隐式销毁。类似的，对象的基类部分也是隐式销毁的。因此，和构造函数及赋值运算符不同，派生类析构函数只负责销毁由派生类自己分配的资源：
```C++
class D: public Base{
    public:
        // Base::~Base被自动调用执行
        ~D() {}
};
```
对象销毁的顺序正好与其创建的顺序相反：派生类析构函数首先执行，然后是其基类析构函数，依次类推。

#### 继承的构造函数
在C++11标准中，派生类能够重用其直接基类定义的构造函数。一个类只初始化它的直接基类，出于同样的原因，一个类也只继承其直接基类的构造函数。类不能继承默认、拷贝和移动构造函数。<br>
派生类继承基类构造函数时提供了一条注明了基类名的using声明语句。我们可以重新定义Bulk_quote类，令其继承Disc_quote类的构造函数:
```C++
class Bulk_quote:public Disc_quote{
    public:
        using Disc_quote::Disc_quote;       //继承Disc_quote的构造函数
        double net_price(std::size_t) const;
};
```
通常情况下，using声明语句只是令某个名字在当前作用域内可见。而当作用于构造函数时，using声明语句将令编译器产生代码。对于基类的每个构造函数，编译器都生成一个与之对应的派生类构造函数。换句话说，对于基类的每个构造函数，编译器都在派生类中生成一个形参列表完全相同的构造函数:
```C++
derived(parameters):base(args){}
```
- args, 将派生类构造函数形参传递给基类构造函数

在我们的Bulk_quote类中，继承的构造函数等价于:
```C++
Bulk_quote(const std::string &book, double price, std::size_t qty, double disc):Disc_quote(book, price, qty, disc) {}
```
如果派生类含有自己的数据成员，则这些成员将被默认初始化

##### 继承的构造函数特点
和普通成员using声明不一样，一个构造函数的using声明不会改变该构造函数的访问级别。例如，不管using声明出现在哪儿，基类的私有构造函数在派生类中还是一个私有构造函数。<br>
一个using声明语句不能指定explicit或constexpr。如果基类的构造函数时explicit或者constexpr,则继承的构造函数也拥有相同的属性。<br>
当一个基类构造函数含有默认实参时，这些实参并不会被继承。相反，派生类将获得多个继承的构造函数，其中每个构造函数分别省略掉一个含有默认实参的形参。<br>
如果基类含有几个构造函数，则除了两个例外情况，大多数时候派生类会继承所有这些构造函数。如果派生类定义的构造函数与基类的构造函数具有相同的参数列表，则该构造函数将不会被继承。定义在派生类中的构造函数将替换继承而来的构造函数。第二个例外是默认、拷贝和移动构造函数不会被继承。这些构造函数按照正常规则被合成。继承的构造函数不会被作为用户定义的构造函数来使用，因此，如果一个类只含有继承的构造函数，则它也将拥有一个合成的默认构造函数。