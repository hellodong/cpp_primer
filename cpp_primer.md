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

### 构造函数
- 构造函数的名字和类名相同
- 构造函数没有返回值
- 类可以有多个构造函数，和其他重载函数差不多
- 构造函数不能声明成const类型
当我们创建一个const对象时，直到构造函数完成初始化，对象才能真正取得const属性。因此构造函数在const对象的构造过程中可以向其写值
