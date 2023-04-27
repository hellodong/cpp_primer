## chapter 7 类

### 定义抽象数据类型

#### 设计Sales_data类

Sales_data 接口包含以下操作:

- 一个isbn成员函数
- 一个combine成员函数,用于将一个Sales_data对象加到另一个对象上
- 一个名为add的函数,执行两个Sales_data对象的加法
- 一个名为add的函数,将数据从istream读入到Sales_data对象中
- 一个print函数，将Sales_data对象的值输出到ostream

```c
Sales_data total;
if (read(cin, total)){
    Sales_data trans;
    while(cin, trans) {
        if (total.isbn() == trans.isbn()){
            total.combine(trans);
        }else{
            print(cout, total) << endl;
            total = trans;
        }
    }
    print(cout, total) << endl;
}else {
    cerr << "No data ?" << endl;
}
```

#### 定义改进的Sales_data类

改进的Sales_data类如下所示:

```c
struct Sales_data {
    string isbn() const {return bookNo};
    Sales_data& combine(const Sales_data&);
    double avg_price() const;
    std::string bookNo;
    unsigned int units_sold = 0;
    double revenue = 0.0;
};
//非成员函数接口
Sales_data add();
ostream &print(ostream &os, const Sales_data &);
istream &read(istream &is, Sales_data &);
```

##### 引入this

成员函数通过一个名为this的额外隐式参数来访问调用它的那个对象，当我们调用一个成员函数时，用请求该函数的对象地址初始化this。例如：

```c
total.isbn()
```

编译器负责把total的地址传递给isbn的隐式形参this,可以等价地认为编译器将该调用重写成如下形式:

```c
Sales_data::isbn(&total)
```

在成员函数内部,我们可以直接使用调用该函数的对象成员，无须通过成员访问运算符来做到这一点，因为this所指的正式这个对象。任何对类成员的直接访问都被看作this的隐式引用。
对我们来说，this形参是隐式定义的。实际上，任何自定义为this的参数或变量的行为都是非法的。我们可以在成员函数体内部使用this,尽管没有必要，我们还是能把isbn定义成如下形式:

```c
string isbn() const {return this->bookNo;}
```

因为this的目的总是指向"这个"对象，所以this是一个**常量指针**, 我们不允许改变this中保存的地址。

##### 引入const成员函数

```c
string isbn() const {return bookNo};
```

这里const作用是修改隐式this指针的类型。默认情况下，this的类型是指向类类型非常量版本的常量指针--> this的类型是 `<class type>` *const。我们不能在一个常量对象上调用普通成员函数。
可以把上述函数体想象成如下形式:

```c
//下面代码是非法的：我们不能显示的定义自己的this指针
string Sales_data::isbn(const Sales_data *const this) {return this->isbn;}
```

因为this是指向常量的指针,所以常量成员函数不能改变调用它的对象的内容。

**常量对象，以及常量对象的引用或指针都只能调用常量成员函数**

##### 可变数据成员

一个**可变数据成员**永远不会是const,即使它是const对象的成员。一个const成员函数可以改变一个可变成员的的值。举个例子，我们给Screen添加一个名为access_ctr的可变成员

```c
class Screen{
    public:
        Screen() = default;
        void some_memb() const;
        int get_some_memb() const;
    private:
        mutable int access_ctr = 0; //可变数据成员用 mutable 修饰
};
Screen::Screen():access_ctr(0)
{}
void Screen::some_memb() const
{
    ++access_ctr;
}
void Screen::get_some_memb() const
{
    return access_ctr;
}
```

some_memb 是一个const成员函数，它仍然能够改变access_ctr的值。任何成员函数，包括const函数在内部都能改变可变数据成员的值。

#### 构造函数

- 构造函数的名字和类名相同
- 构造函数没有返回值
- 类可以有多个构造函数，和其他重载函数差不多
- 构造函数不能声明成const类型
  当我们创建一个const对象时，直到构造函数完成初始化，对象才能真正取得const属性。因此构造函数在const对象的构造过程中可以向其写值

##### 合成的默认构造函数

```c
Sales_data total;
Sales_data trans;
```

我们没有为这些对象提供初始值。类通过一个特殊的构造函数默认初始化过程，这个函数叫做**默认构造函数**。默认构造函数无须任何实参。

如果类没有显示定义构造函数，编译器就会隐式的定义一个默认构造函数 ----> **合成的默认构造函数**， 合成默认构造函数按照如下规则初始化类数据成员:

- 如果存在类内的初始值，用它来初始化成员
- 否则 默认初始化该成员

##### 某些类不能依赖于合成的默认构造函数

合成的默认构造函数只适合非常简单的类。对于一个普通类，必须定义它自己的默认构造函数，原因有三：

- 只有当类没有声明构造函数时，编译器才会自动生成默认构造函数
- 合成的默认构造函数可能执行错误的操作。比如有些值将是未定义的
- 有时候编译器不能为某些类合成默认构造函数

#### 拷贝、赋值和析构

类需要控制拷贝、赋值和销毁对象时发生的行为。如果我们不主动定义这些操作，编译器将替我们合成他们。一般来说，编译器生成的版本将对对象的每个成员执行拷贝、赋值和销毁操作。

对于某些类来说合成的版本无法正常工作。

### 访问控制与封装

在C++语言中，我们使用**访问说明符**加强类的封装性:

- 定义在**public**说明符后的成员在整个程序内可以被访问，
- 定义在**private**说明符后的成员可以被类的成员函数访问，但是不能被使用该类的代码访问，private部分封装了类的实现细节

定义的类的所有成员是public时，使用struct;反之，如果希望成员时private时，使用class。

#### 友元

类可以允许其他类或函数访问它的非共有成员，方法是另其他类或者函数成为它的友元(friend)

```c
class Sales_data
{
    friend std::ostream &print(std::ostream &, const Sales_data &);
    public:
        Sales_data() = default;
        Sales_data(const std::string &s, unsigned int n, double p): bookNo(s),units_sold(n),price(p)
        {}

    private:
        std::string bookNo;
        unsigned int units_sold = 0;
        double price;
};
std::ostream &print(std::ostream &, const Sales_data &);
```

#### 友元的声明

如果我们希望类的用户能够调用某个友元函数，那么我们就必须在友元声明之外再专门对函数进行一次声明。

### 类的其他特性

这些特性包括:

- 类型成员
- 类的成员
- 类成员的类内初始值
- 可变数据成员
- 内联成员函数
- 从成员函数返回*this

##### 另成员函数为内联函数

定义再类内部的成员函数是自动inline的，如：

```c
class Screen{
    public:
        using pos=std::string::size_type;
        Screen() = default;
        Screen(pos ht, pos wd, char c):height(ht),width(wd),contents(ht * wd, c)
        {}
        char get() const
        { 
            return contents[cursor];
        }

    private:
        pos cursor = 0;
        pos height = 0, width = 0;
        std::string contents;
};
```

因此Screen构造函数和返回光标所指字符的get函数默认是inline函数。同样的也能再类的外部用inline关键字修饰函数的定义:

```c
inline Screen &Screen::move(pos r, pos c)
{
    pos row = r * width;
    cursor = row + c;
    return *this;
}

char Screen::get(pos r, pos c) const
{
    pos row = r * width;
    return contents[row + c];
}
```

我们无需再声明和定义的地方同时说明为inline。不过, 最好只在类外部定义的地方说明inline,这样可以使类更容易理解。

##### 重载成员函数

成员函数也可以被重载,只要函数之间在参数的**数量和/或类型上**有所区别就行，如Screen类定义了两个版本的get函数

```c
Screen myscreen;
char ch = myscreen.get();  //调用Screen::get()
ch = myscreen.get(0,0);    //调用Screen::get(pos,pos)
```

##### 可变数据成员

在一个const成员函数内，可以通过在变量的声明中加入mutable关键就可以修改这个变量。一个可变数据成员永远不会是const，即使它是const对象的成员。因此，一个const成员函数可以改变一个可变成员的值。举个例子:

```c
class Screen{
    public:
        void some_member() const;
    private:
        mutable size_t access_ctn;
};

void Screen::some_member() const
{
    ++access_ctn;
}
```

#### 返回*this的成员函数

```c
class Screen{
    public:
        Screen &set(char ch);
        Screen &set(pos r, pos c, char ch);
        Screen &move(pos r, pos c);
    private:
        pos cursor = 0;
        pos height = 0, width = 0;
        std::string contents;
};

Screen &Screen::move(pos r, pos c)
{
    pos row = r * width;
    cursor = row + c;
    return *this;
}

Screen &Screen::set(char ch)
{
    contents[cursor] = ch;
    return *this;
}

Screen &Screen::set(pos r, pos c, char ch)
{
    contents[r*width + c] = ch;
    return *this;
}

```

返回引用的函数是左值，意味着这些函数返回的是对象本身而非对象副本。把一系列操作连接在一条表达式:

```c
myScreen.move(4,0).set('#');
```

上述语句等价于:

```
myScreen.move(4,0);
myScreen.set('#');
```

##### 从const成员函数返回*this

我们继续添加一个名为display的操作，我们令display为一个const成员，此时，this将是一个指向const 的指针而*this 是const对象。我们不能把display嵌入到一组动作的序列中去:

```c
Screen myScreen;
// 如果display返回常量引用, 则调用set将引发错误
myScreen.display(cout).set('*');
```

即使myScreen是个非常量对象，则set的调用也无法通过编译。

- 一个const 成员函数如果以引用形式返回*this,那么它的返回类型将是常量引用

##### 基于const的重载

通过区分成员函数是否是const的，我们可以对其进行重载。因为非常量版本的函数对于常量对象是不可用的，所以我们只能在一个常量对象用const成员函数。另外，可以在非常量对象上调用常量版本或非常量版本，显然此时非常量版本是一个更好的匹配。

```c
class Screen{
    public:
        using pos=std::string::size_type;
        Screen() = default;
        Screen(pos ht, pos wd, char c=' '):height(ht),width(wd),contents(ht * wd, c)
        {}
        Screen &display(std::ostream &os)
        {
                do_display(os);
                return *this;
        }
        const Screen &display(std::ostream &os) const
        {
                do_display(os);
                return *this;
        }
    private:
        pos cursor = 0;
        pos height = 0, width = 0;
        std::string contents;
        void do_display(std::ostream &os) const
        {
                os << contents;
        }
};
```

当一个成员调用另一个成员时，this指针在其中隐式地传递。display调用do_display时，它的this指针隐式地传递给do_display。而当display的非常量函数调用do_display时，它的this指针将隐式的从指向非常量指针转换成常量指针。do_display完成后，display函数各自返回解引用this所得对象。
在非常量版本中,this指向一个非常量对象，因此display返回一个普通的(非常量)引用;而const 成员返回一个常量引用。

#### 类类型

对于两个类来说，即使他们的成员完全一样，这两个类也时两个不通的类型。

```c
class First {
    public:
    int getMem();
    private:
    int memi;
};

class Second {
    public:
    int getMem();
    private:
    int memi;
};

First obj1;
Second obj2 = obj1;         //错误：obj1和obj2的类型不同
```

- 即使两个类的成员列表完全一致，它们也是不同的类型。对于一个类来说，它的成员和其他任何类的成员都不是一回事

##### 类的声明

我们能仅仅声明类而暂时不定义它，被称为**前向声明(forward declaration)**。在它声明之后定义之前是**一个不完全类型(incomeplete type)**。
不完全类型只能在非常有限情况下使用：可以定义指向这种类型的指针或引用，也可以声明（但是不能定义）以不完全类型作为参数或返回类型的函数。

##### 友元再探

普通的成员函数能定义成友元。类还可以把其他类定义成友元，也可以把其他类的成员函数定义成友元。友元函数能定义在类内部，这样的函数是隐式内联的。

### 类的作用域

每个类都会定义它自己的作用域，在类的作用域之外，普通的数据和函数成员只能由对象、引用或者指针使用成员访问运算符。对于类类型成员则使用作用域运算符访问。

##### 作用域和定义在类外部的成员

1. 在类的外部，成员名字就被隐藏起来了。一旦遇到了类名，定义的剩余部分就在类的作用域之内了，这里的剩余部分包括参数*列表*和*函数体*(也包括类型)---->我们可以直接使用类的其他成员而无需再次授权了。

```c
void Window_mgr::clear(ScreenIndex idx)
{
    Screen &s = screens[idx];
    s.contents = string(s.height * s.width, ' ');
}
```

2. 成员函数定义在类的外部，返回类型中使用的名字位于类的作用域外，返回类型必须指明它是那个类的成员：

```c
class Window_mgr{
    public:
        ScreenIndex addScreen(const Screen&);
};

Window_mgr::ScreenIndex     //要想使用ScreenIndex作为返回类型，必须明确指定那个类型
Window_mgr::addScreen(const Screen &s)
{
    screens.push_back(s);
    return screens.size() - 1;
}
```

#### 名字查找与类的作用域

**名字查找(name lookup)**:

- 在名字所在块中寻找其声明语句，只考虑在名字的使用之前出现的声明
- 如果没找到，继续查找外层作用域
- 如果最终没找到匹配的声明，则程序报错。
  类内部成员函数与上述规则有所区别。类的定义分两步处理:
- 首先，编译成员的声明
- 直到类全部可见后才编译函数体
  成员函数体直到整个类可见后才会被处理，所以它能使用类中定义的任何名字

##### 用于类成员声明的名字查找

声明中使用的名字，包括返回类型或者参数列表中使用的名字，都必须在使用前确保可见。

##### 类型名要特殊处理

内层作用域可以重新定义外层作用域中的名字，即使该名字已经在内层作用域中使用过。然后在类中，如果成员使用了外层作用域中的某个名字，而该名字代表一种类型，则类不能再之后重新定义该名字：

```c
typedef double Money;
class Account {
    public:
        Money balance() {return bal;}   //使用外层域中的Money
    private:
        typedef double Money;
        Money bal;                      //错误，不能宠幸定义Money
};
```

##### 成员定义中的普通块作用域的名字查找

成员函数中使用的名字按如下方式解析:

- 在成员函数内查找该名字的声明。只有函数使用之前出现的声明才被考虑。
- 如果在成员函数内没找到，则在类内继续查找，类的所有成员都可以考虑。
- 如果类内也没找到该名字的声明，在成员函数定义之前作用域内继续查找。

一般来说，不建议使用其他成员的名字作为某个成员函数的参数。我们在dummy_fcn函数中暂时违反以下这个约定:

```c
// 通常情况下不建议为参数和成员使用同样的名字
int height;     // 定义一个名字, 稍后再Screen中使用
class Screen {
    public:
        typedef std::string::size_type pos;
        void dummy_fcn(pos height)
        {
            cursor = width * height; //height 是形参
        }
    private:
    pos cursor = 0;
    pos height = 0,width = 0;
};
```

上述代码,height参数隐藏了同名的成员。如果想绕开上面的查找规则，将代码变为：

```c
void Screen::dummy_fcn(pos height)
{
    cursor = width * this->height;      //成员 height
    //另外一种写法
    cursor = width * Screen::height;    //成员height
}
```

##### 类作用域之后，在外围的作用域中查找

我们需要的是外层作用域中的名字，可以显示地通过作用域运算符来进行请求:

```c
void Screen::dummy_fcn(pos height)
{
    cursor = width * ::height;      //全局的height
}
```

*尽管外层的对象被隐藏了，但我们仍然可以用作用域运算符访问它。*

### 构造函数再探

#### 构造函数初始值列表

##### 构造函数的初始值有时必不可少

类的数据成员初始化和赋值是有差异的。成员是const 或者引用，必须将其初始化。当成员属于某种类类型，并且没有定义默认构造函数，也必须将其这个成员初始化。

```c
class ConstRef{
    public :
        ConstRef(int val);
    private:
        int i;
        const int ci;
        int &ri;
};
```

如果我们没有为他们提供构造函数初始值将引发错误：

```c
ConstRef::ConstRef(int val)
{
    i = val;    // 赋值
    ci = val;    // 错误：不能给const 赋值
    ri = i;    // 错误：ri 没有被初始化
}
```

我们初始化const或者引用类型的数据唯一机会就是通过构造函数初始值，正确方式如下:

```c
ConstRef::ConstRef(int val):i(val), ci(val),ri(i) 
{}
```

##### 成员初始化顺序

成员的初始化顺序与他们类定义中的顺序一致：第一个成员先被初始化，然后第二个，以此类推。构造函数初始化值列表中初始值的前后位置关系不会影响实际的初始化关系。
举个例子:

```c
class X {
    int i;
    int j;
    public:
        //未定义的：i在j之前就被初始化
        X(int val):j(val), i(j) {}
};
```

##### 委托构造函数

**委托构造函数**, 一个委托构造函数使用它所属类的其他构造函数执行它自己的初始化过程，或者说它把它自己的一些职责委托给了其他构造函数。

```c
class Sales_data {
    public:
        Sales_data(std::string s, unsigned int cnt, double price):bookNo(s),units_sold(cnt), revenue(cnt * prices) {}
        Sales_data():Sales_data("",0,0) {}
        Sales_data(std::string s): Sales_data(s, 0, 0) {}
        Sales_data(std::isstream &is):Sales_data()
            {read(is, *this);} 
};
```

假如函数体包含这些代码的话，将先执行这些代码，然后控制权才会交还给委托者.

##### 隐式的类类型转换
构造函数只接受一个实参，则它实际上定义了一个转为此类类型的隐式转换机制----->**转换构造函数**。在Sales_data类中，接受string的构造函数和接受istream的构造函数分别定义了从这两种类型向Sales_data隐式转换的规则。
```c
string null_book = "cpp primer";
// 构造一个零时的Sales_data对象
// 该对象的units_sold 和 revenue等于0, bookNo等于null_book
// Sales_data &Sales_data::combine(const Sales_data &rh)
item.combine(null_book);
```
我们用一个string实参调用了Sales_data的combine成员。编译器用给定的string自动创建了一个Sales_data对象。新生成的这个Sales_data对象传递给combine.
###### 只允许一类类型转换
编译器只会自动地执行异步类型转换。例如下面的代码隐式地使用了两种转换规则，所以它是错误地:
```
//1) 把"cpp primer" 转换成string
//2) 把这个(临时地)string转换成Sales_data
item.combine("cpp primer");
```
我们可以显示地把字符串转换成string或者Sales_data对象:
```c
// 正确： 显示地转换成string,隐式地转换成Sales_data
item.combine(string("cpp primer"));
// 正确: 隐式地转换成string, 显示地转换成Sales_data
item.combine(Sales_data("cpp primer"));
```
###### 类类型转换不是总有效
```c
// 使用istream构造函数创建一个函数传递给combine
item.combine(cin);
```
这段代码隐式地把cin转换成Sales_data,这个转换执行了接受一个istream的Sales_data构造函数。该构造函数通过读取标准输入创建了一个Sales_data对象，随后将得到的对象传递给combine。Sales_data对象是个临时量，一旦combine完成我们不能再访问他了。
###### 抑制构造函数定义的隐式转换
我们通过构造函数声明为**explicit**加以阻止:
```c
class Sales_data{
    public:
        Sales_data() = default;
        Sales_data(const std::string &s, unsigned n , double p):bookNo(s), units_sold(n),revenue(p*n) {}
        explicit Sales_data(const std::string &s):bookNo(s) {}
        explicit Sales_data(std::istream &is);
};
```
没有任何构造函数能用于隐式创建Sales_data对象，下面的两种用法无法通过编译:
```c
item.combine(null_book);  //错误：string 构造函数时explicit的
item.combine(cin);        //错误： istream 构造函数时explicit的
```
关键字explicit只对一个实参的构造函数有效。多个实参的构造函数不能用于执行隐式转换，所以无须将这些构造函数指定为explicit的，只能在类内声明构造函数时使用explicit关键字，在类外部定义时不应重复定义。
```c
// 错误： explicit关键字只允许出现在类内的构造函数声明出
explicit Sales_data::Sales_data(std::istream &is)
{
    read(is, *this);
}
```
###### explicit 构造函数只能用于直接初始化
当我们用explicit关键字声明构造函数时，它将只能以直接初始化的形式使用。而且，编译器将不会在自动转换过程中使用该构造函数:
```c
Sales_data item1(null_book);    // 正确: 直接初始化
Sales_data item2 = null_book;   // 错误：不能将explicit构造函数用于拷贝形式的初始化过程
```
###### 为转换显示地使用构造函数
编译器不会将explicit地构造函数用于隐式地转换过程，但是我们可以使用这样地构造函数显示强制进行转换：
```c
// 正确: 实参是一个显示构造地Sales_data对象
item.combine(Sales_data(null_book));
// 正确: static_cast可以使用explicit构造函数
item.combine(static_cast<Sales_data>(cin))
```
第一个调用中，我们直接使用Sales_data构造函数，该调用通过接受string地构造函数创建一个临时地Sales_data对象。第二个调用中，我们使用static_cast 执行了显示地而非隐式地转换。
##### 聚合类
聚合类使得用户可以直接访问其成员，并且具有特殊地初始化语法形式。聚合类满足以下条件:
- 所有成员都是public
- 没有定义任何构造函数
- 没有类内初始值
- 没有基类，也没有virtual函数








例如下面是个聚合类:
```c
struct Data{
    int ival;
    string s;
}
```
11111
