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
