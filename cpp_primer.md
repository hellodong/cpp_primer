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
这里const作用是修改隐式this指针的类型。默认情况下，this的类型是指向类类型非常量版本的常量指针--> this的类型是 <class type> *const。我们不能在一个常量对象上调用普通成员函数。
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

### 友元再探
普通的成员函数能定义成友元。类还可以把其他类定义成友元，也可以把其他类的成员函数定义成友元。友元函数能定义在类内部，这样的函数是隐式内联的。



