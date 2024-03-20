## Overload operator and Conversion
使用运算符重载可以使我们的程序更易于编写和阅读。举个例子，因为在Sales_item类中定义了输入，输出和加法运算符，所以可以通过下述形式输出两个Sales_item的和:
```C++
std::cout << item1 + item2; // 输出两个Sales_item的和
```

### 基本概念

重载的运算符具有特殊名字：关键字operator和其后定义的运算符符号共同组成。重载运算符也包含返回类型、参数列表和函数体。<br>
重载运算符函数的参数数量与该运算符作用的运算符对象数量一样多。一元运算符有一个参数，二元运算符有两个。对于二元运算符来说，左侧运算对象传递给第一个参数，右侧运算对象传递给第二个参数。重载运算符不能还有默认实参<br>
运算符函数是成员函数，则它的第一个运算对象绑定到隐式的this指针上，因此，成员运算符函数(显示)参数数量比运算符的运算对象总数少一个。<br>
对于运算符函数来说，它或者是类的成员，或者至少含有一个类类型的成员:
```C++
// 错误: 不能定义int 重定义内置运算符
int operator+(int,int);
```
我们可以重置大多数（不是全部）运算符:
<table>
</table>

有四个符号(+,-,*,&)既是一元运算符也是二元运算符，所有这些运算符都能被重载，从参数的数量我们可以推断到底哪种运算符。

##### 直接调用一个重载的运算符函数
我们将运算符作用于类型正确的实参，从而以这种间接方式“调用”重载的运算符函数。然而，我们也能像调用普通函数一样直接调用运算符函数，先指定函数名字，然后传入数量正确、类型适当的实参:
```C++
data1 + data2;
operator+(data1, data2);
```

##### 某些运算符不应该被重载
逻辑与(&),逻辑或(|)和逗号(,)的运算符对象求值顺序无法保留下来。除此之外，&& 和||运算符重载版本也无法保留内置运算符的短路求值属性。不重载逗号运算符和取地址运算符。

##### 使用与内置类型一致的含义
重载运算符的返回类型通常情况下应该与其内置版本的返回类型兼容:逻辑运算符的关系运算符应该返回bool，算数运算符应该返回一个类类型的值，赋值运算符和复合运算符则应该返回左侧运算对象的一个引用

##### 赋值和复合运算符
赋值运算符的行为与复合版本类似:赋值之后，左侧运算符对象和右侧运算对象的值相等，并且运算符应该返回它左侧运算对象的一个引用，如果类含有算术运算符或位运算符，则最好也提供对应的符合赋值运算符。+=运算符的行为显然应该与其内置版本一致，先执行+，再执行=。

##### 选择作为成员或者非成员
当我们定义重载的运算时，必须首先决定是将其声明为类的成员函数还是声明为一个普通的非成员函数。在某些时候我们别无选择，因为有的运算符必须作为成员；另一些情况下，运算符作为普通函数比作为成员更好：
- 赋值(=)、下标（[]）、调用(())和成员箭头(->)运算符必须是成员
- 复合运算符一般来说是成员，但并非必须
- 递增、递减和解引用运算符，通常应该是成员
- 具有对称性的运算符可能转换任意一端的运算对象，例如算术、相等性、关系和位运算符，因此它们通常应该是普通的非成员函数

我们希望能在含有混合类型的表达式中使用对称性运算符。加法是对称的。如果我们想提供含有类对象的混合类型表达式，则运算符必须定义成非成员函数。当我们把运算符定义成成员 函数时，左侧运算对象必须是运算符所属类的一个对象:
```C++
string s = "world";
string t = s+ "!";      // 正确
string u = "hi" + s;    // 如果+是string的成员，产生错误
```
如果operator+是string的成员，则上面第一个加法等价s.operator+("!")。同样的，"hi"+s等价"hi".operator+(s)。显然"hi"的类型是const char *,内置类型根本没有成员函数。<br>
string 将+定义成普通非成员函数， "hi" + s等价于operator+("hi",s)。和任何其他函数调用一样，每个实参都能被转换成形参类型。唯一的要求是至少一个运算对象是类类型，并且两个运算对象都能准确无误转换成string。

### 输入输出运算符
IO标准库分别使用>>和<< 执行时输入和输出操作。这两个运算符来说，IO库定义了其读写内置类型的版本，而类则需要定义适合其对象的新版本以支持IO操作。

#### 重载输出运算符<<
输出运算符的第一个形参是一个非常量ostream对象的引用。之所以ostream是非常量，因为向流写入内容会改变其状态。第二个形参一般来说是一个常量的引用，该常量是我们想要打印的类类型。第二个形参是引用的原因是我们希望避免复制实参。为了与其他输出运算符保持一致，operator<< 一般要返回它的ostream形参。

##### Sales_data输出运算符
我们按照如下形式编写Sales_data的输出运算符:
```C++
std::ostream & operator<<(std::ostream &os, const Sales_data &entry)
{
    os << "bookNo: " << entry.bookNo << ", units_sold: " << entry.units_sold << ", revenue: " << entry.revenue;
    return os;
}
```
除了名字之外，这个函数与之前print函数完全一样。完成输出后，运算符返回刚刚使用的ostream的引用。

##### 输入输出运算符必须非成员函数
与iostream标准库兼容的输入输出运算符必须是普通非成员函数，而不能是类的成员函数。否则，它们的左侧运算对象将是我们的类的一个对象:
```C++
Sales_data data;
data << cout;   // 如果operator<<是Sales_data的成员
```
假设输入输出运算符是某个类的成员，则它们也必须是istream或ostream的成员。然而，这两个类属于标准库，并且我们无法给标准库中的类添加任何成员。因此，如果我们希望为类自定义IO运算符，则必须将其定义成非成员函数。当然，IO运算符通常需要读写类的非公有数据成员，所以IO运算符一般被声明为友元。

#### 重载输入运算符>>
通常情况下，输入运算符的第一个形参是运算符将要读取的流引用，第二个形参是将要读入到对象的引用。该运算符通常会返回某个给定流的引用。第二个形参必须是个非常量。 

##### Sales_data的输入运算符
我们将按照如下形式编写Sales_data的输入运算符:
```C++
std::istream & operator>>(std::istream &is, Sales_data &rhm)
{
    double price = 0;
    is >> rhm.bookNo >> rhm.units_sold >> price;
    if (is)
    {
        rhm.revenue = rhm.units_sold * price;
    }
    else 
    {
        rhm = Sales_data(); // 输入失败：对象被赋予默认状态
    }
    return is;
}
```
除了if语句之外，这个定义与之前read函数完全一样。if语句检查读取操作是否成功，如果发生了IO错误，则运算符将给定的对象重置为空Sales_data,这样可以确保对象处于正确的状态。

##### 输入时的错误
如果读取操作失败，则price的值将是未定义的。因此，在使用price前我们需要首先检查输入流的合法性，然后才能执行计算并将结果存入revenue。如果发生了错误，我们无须在意到底是哪部分输入失败，只要将一个新的默认初始化的Sales_data对象赋予item从而将其重置为空Sales_data就可以了。执行这样的赋值后，item的bookNo成员将是一个空string,revenue和units_sold。

##### 标识错误
一些输入运算符需要做更多数据验证工作。例如，我们的输入运算符可能需要检查bookNo是否符合规范的格式。在这样的例子中，即使从技术上来看IO是成功的，输入运算符也应该设置流的条件状态以标识出失败信息。通常情况下，输入运算符只设置failbit。

### 算术和关系运算符
通常情况下，我们把算术和关系运算符定义成非成员函数以允许对左侧或右侧的运算对象进行转换。因为这些运算符一般不需要改变运算对象的状态，所以形参都是常量的引用。<br>
算术运算符通常会计算它的两个运算对象并得到一个新值，这个值有别于任意一个运算对象，常常位于一个局部变量之内，操作完成后返回该局部变量的副本为其结果。如果定义了算术运算符，则一般也会定义一个对应的复合赋值运算符。此时，最有效的方式是使用复合赋值运算符来定义算术运算符:
```C++
Sales_data operator+(const Sales_data &lhm, const Sales_data &rhm)
{
    Sales_data sum(lhm);
    sum += rhm;
    return sum;
}

Sales_data& Sales_data::operator+=(const Sales_data &rhm)
{
    if (bookNo != rhm.bookNo)
    {
        return *this;
    }

    units_sold += rhm.units_sold;
    revenue +=rhm.revenue;
    return *this;
}
```
#### 相等运算符
C++中的类通过定义相等运算符来检验两个对象是否相等。它们会比较对象的每一个数据成员，只有当所有对应成员都相等时才认为两个对象相等。
```c++
bool operator==(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.bookNo == rhs.bookNo && lhs.units_sold == rhs.units_sold && lhs.revenue == rhs.revenue;
}

bool operator!=(const Sales_data &lhs, const Sales_data &rhs)
{
    return !(lhs == rhs);
}
```
从这些函数中体现出来的设计准则:
- 一个类含有判断两个对象是否相等的操作，则它显然应该把函数定义成operator==而非一个普通的命名函数：因为用户肯定希望能使用==比较对象
- 如果类定义了operator==, 则该运算符应该能判断一组给定的对象中是否含有重复数据
- 通常情况下，相等运算符应该具有传递性，换句话说，如果a==b和b==c都为真，则a==c应该为真
- 如果类定义了operator==,则这个类也应该定义operator!=。对于用户来说，当它们能使用==时肯定也希望能时候!=,反之亦然

#### 关系运算符
定义了相等运算符的类常常(但不总是)包含关系运算符。特别是，因为关联容器和一些算法要用到小于运算符，所以定义operator<会比较有用。
- 定义顺序关系，令其与关联容器中对关键字的要求一致
- 如果类同时也含有==运算符的话，则定义一种关系令其与==保持一致。特别是，如果两个对象是!=的，那么一个对象应该<另外一个。

### 赋值运算符
之前介绍过拷贝赋值和移动赋值运算符，它们可以把类的一个对象赋值给类的另一个对象。此外类还可以定义其他赋值运算符以使用别的类型作为右侧运算对象。<br>
在拷贝赋值和移动赋值运算符之外，标准库vector类还定义了第三种赋值运算符，该运算符接受花括号内的元素列表作为参数:
```C++
std::vector<std::string> v;
v = {"a", "an",  "the"};
```
同样也可以把这个运算符添加到StrVec类中:
```C++
class StrVec{
    public:
        StrVec &operator=(std::initializer_list<std::string>);
};

StrVec &StrVec::operator=(std::initializer_list<std::string> il)
{
    auto newdata = alloc_n_copy(il.begin(), il.end());
    free();
    elements = newdata.first;
    first_free = cap = newdata.second;
    return *this;
}
```
为了与内置类型的赋值运算符保持一致，这个新的赋值运算符将返回其左侧运算对象的引用。

##### 复合赋值运算符
复合赋值运算符不非得是类的成员，不过我们还是倾向于把包括复合赋值在内的所有赋值运算都定义在类的内部。为了与内置类型的复合赋值保持一致，类中的复合赋值运算符也要返回其左侧运算对象的引用。Sales_data类中复合赋值运算符的定义:
```C++
Sales_data& Sales_data::operator+=(const Sales_data &rhm)
{
    if (bookNo != rhm.bookNo)
    {
        return *this;
    }

    units_sold += rhm.units_sold;
    revenue +=rhm.revenue;
    return *this;
}
```

### 下标运算符
标识容器的类通常可以通过元素在容器中的位置访问元素，这些类一般会定义下标运算符operator[]。
- 下标运算符必须是成员函数。

为了与下标的原始定义兼容，下标运算符通常以所访问元素的引用作为返回值，这样的好处是下标可以出现在赋值运算符任意一端。进一步，我们最好同时定义下标运算符的常量版本和非常量版本，当作用于一个常量对象时，下标运算符返回常量引用以确保我们不会给返回的对象赋值。<br>
我们按照如下形式定义StrVec的下标运算符:
```C++
class StrVec{
    public:
        std::string &operator[](size_t n)
        {
            return elements[n];
        }
        const std::string &operator[](size_t n) const
        {
            return elements[n];
        }
};
```
下标运算符返回的是元素的引用，当StrVec是非常量时，我们可以给元素赋值；当我们对常量取下标时，不能为其赋值:
```C++
const StrVec cvec = svec;
if (svec.size() && svec[0].empty())
{
    svec[0] = "zero";
    cvec[0] = "zip";        // 错误：对cvec下标返回的是常量引用
}
```

### 递增和递减运算符
在迭代器类中通常会实现递增运算符(++)和递减运算符(--),这两种运算符使得类可以在元素的序列中前后移动。C++语言并不要求递减和递增运算符必须是类的成员，但是因为它们改变的正好是所操作对象的状态，所以建议将其设定为成员函数。<br>
对于内置类型来说，递增和递减运算符既有前置版本也有后置。同样，我们也应该为类定义两个版本的递增和递减运算符。

##### 定义前置递增/递减运算符
我们在StrBlobPtr类中定义它们:
```C++
class StrBlobPtr{
    public:
        // 递增和递减运算符
        StrBlobPtr &operator++();   // 前置运算符
        StrBlobPtr &operator--();
};

// 前置版本: 返回递增/递减对象引用
StrBlobPtr &StrBlobPtr::operator++()
{
    // 如果curr已经指向了容器的尾后位置，则无法递增它
    check(curr, "increament past end of StrBlobPtr");
    ++curr;         // 墙curr在当前状态下向前移动一个元素
    return *this;
}

StrBlobPtr &StrBlobPtr::operator--()
{
    // curr是0，则继续递减它将产生一个无效下标
    --curr;             //curr在当前状态下向后移动一个元素
    check(curr, "decreament past begin of StrBlobPtr");
    return *this;
}

```

##### 区分前置和后置运算符
同时定义前置和后置运算符，必须首先解决一个问题，普通的重载形式无法区分这两钟情况。前置和后置版本使用的是同一个符号,意味着其重载版本所用的名字将是相同的，并且运算对象的数量和类型也是相同的。<br>
为了解决这个问题，后置版本接受一个额外的（不被使用的)int类型形参。当我们使用后置运算符时，编译器为这个形参提供一个值为0的实参。尽管从语法上来说后置函数可以使用这个额外的形参，但是在实际过程中通常不会这么做。这个形参的唯一作用就是区分前置版本和后置版本的函数，而不是真的要在实现后置版本时参与运算。
```C++
class StrBlobPtr{
    public:
        StrBlobPtr operator++(int); //后置运算符
        StrBlobPtr operator--(int);
};

// 后置版本: 递增/递减对象的值，但是返回原值
StrBlobPtr StrBlobPtr::operator++(int)
{
    StrBlobPtr ret(*this);  // 记录当前的值
    ++*this;                // 向前移动一个元素，前置++需要检查递增的有效性
    return ret;
}

StrBlobPtr StrBlobPtr::operator--(int)
{
    StrBlobPtr ret(*this);
    --*this;
    return ret;
}
```
- 为了与内置版本保持一致，后置运算符应该返回对象的原值，返回的形式是一个值而非引用

### 成员访问运算符
在迭代器类和智能指针类中常常用到解引用(*)和箭头运算符(->)。我们以如下形式向StrBlobPtr类添加这两种运算符:
```C++
class StrBlobPtr{
    public:
        std::string &operator*() const
        {
           auto p = check(curr, "dereference past end");
           return (*p)[curr];       // *p 是对象所指的vector
        }
        std::string *operator->() const
        {
            return &this->operator*();
        }
};
```
- 箭头运算符必须是类的成员。解引用运算符通常也是类的成员，尽管并非必须如此

我们将这两个运算符定义成const成员，获取一个元素并不会改变StrBlobPtr对象状态。同时它们的返回值分别是非常亮string的引用或指针，因为一个StrBlobPtr只能绑定到非常量的StrBlob对象。
```C++
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout <<"usage: "<< argv[0] << " <arg1> <arg2> ..." << std::endl;
        return -1;
    }

    StrBlob blob_input;
    for(int idx = 1;idx < argc;idx++)
    {
        blob_input.push_back(argv[idx]);
    }
    StrBlobPtr input_ptr(blob_input); // input_ptr指向blob_input中的vector

    std::cout << "Blob Input:"<< blob_input.size() <<" word(s)" <<std::endl;
    for (size_t idx = 0;idx < blob_input.size();idx++)
    {
        std::cout << "           " << *input_ptr;   //打印blob_input中vector元素值
        std::cout << ": "<<(input_ptr++)->size() << std::endl;  //打印blob_input中元素值大小，并累加1
    }

    return 0;
}
```
##### 对箭头运算符返回值的限定
我们能令operator*完成任何我们指定的操作。我们可以让operator*返回一个固定值42，或者打印对象的容器，以及其他。箭头运算符则不是这样，它永远不能丢掉成员访问这个最基本的含义。当我们重载箭头时，可以改变的是箭头从哪个对象当中获取成员，而箭头获取成员这一事实则永远不变。<br>
对于形如point->mem的表达式来说，point必须是指向类的指针或是一个重载operator->的类对象。根据point类型的不同，point->mem分别等价:
```C++
(*point).mem;   //point是一个内置的指针类型
point.operator()->mem; //point是类的一个对象
```
point->mem的执行过程如下:
1. point是指针,则我们应用内置的箭头运算符，等价 (*point).mem。首先解引用指针，然后从所得的对象中获取指定成员。所指point的类没有名为mem的成员，程序会发生错误
2. point是定义了operator->的类的一个对象，则我们使用point.operator->()的结果来获取mem。其中，如果该结果是一个指针，执行第一步；如果该结果还有重载的operator->(),则重复当前步骤

- 重载的箭头运算符必须返回类的指针或自定义了箭头运算符的某个类的对象

### 函数调用运算符
如果类重载了函数调用运算符，则我们可以像使用函数一样使用该类的对象。如下例子，absInt的struct含有一个运算符，该运算符负责返回其参数的绝对值:
```C++
struct absInt{
    int operator(int val) const {
        return val < 0: -val? val;
    }
};

int i = -42;
absInt absObj;
int ui = absObj(i);
```
即使absObj只是一个对象而非函数，我们也能调用该对象。调用对象实际上是在运行重载的调用运算符。在此例中，该运算符接受一个int值并返回其绝对值。如果类定义了调用运算符，则该类的对象称作**函数对象**

##### 含有状态的函数对象类
函数对象类除了operator()之外也可以包含其他成员。举个例子，我们将定义一个打印string实参内容的类:
```C++
class PrintString{
    public:
        PrintString(std::ostream &lhs = std::cout, char rhs = ' '):os(lhs), sep(rhs)
        {}
        std::ostream &operator()(std::string str) const
        {
            return os<< str << sep;
        }
    private:
        std::ostream &os;
        char sep;
};

```
当定义PrintString对象时，对于分隔符及输出流既可以使用默认值也可以提供我们自己的值:
```C++
PrintString print;
print("hello");
```
可以使用标准库for_each算法和我们自己的PrintString类来打印容器的内容:
```C++
std::vector<std::string> vs;
for(int idx = 1; idx < argc;idx++)
{
    vs.push_back(argv[idx]);
}
std::cout << "output "<< argc -1 << " word(s) :"<< std::endl;

std::for_each(vs.begin(), vs.end(), PrintString(std::cout, '\n'));
```
for_each的第三个参数是类型PrintString的一个临时对象。

#### lambda是函数对象
上述PrintString对象作为调用for_each的实参类似于我们之前编写的lambda表达式程序。当我们编写了一个lambda后，编译器将该表达式翻译成一个未命名类的未命名对象。在lambda表达式产生的一个重载的函数调用运算符。默认情况下lambda不能改变它捕获的变量，由lambda产生的类当中的函数调用运算符是一个const成员函数。

##### 表示lambda及相应铺货行为的类
当一个lambda表达式通过引用捕获变量时，由程序负责确保lambda执行时引用所引的对象确实存在。因此，编译器可以直接使用该引用而无须在lambda产生的类中将其存贮为数据成员<br>
通过值捕获的变量被拷贝到lambda中。lambda产生的类必须为每个值捕获的变量建立对应的数据成员，同时创建构造函数，令其使用捕获的变量的值来初始化数据成员。<br>
lambda表达式产生的类不含默认构造函数、赋值运算符及默认析构函数；它是否含有默认的拷贝/移动构造函数通常要视捕获的数据成员而定。

#### 标准库定义的函数对象
标准库定义了一组表示算术运算符、关系运算符和逻辑运算符的类，每个类分别定义了一个执行命名操作的调用运算符。plus类定义一对运算对象执行+的操作;modulus定义了一个调用运算符执行二元%操作;equal_to类执行==。

| 算术 | 关系 | 逻辑 |
|--|--|--|
| plus\<Type\> | equal_to\<Type\>| logical_and\<Type\> |
| minus\<Type\> | not_equal_to\<Type\> | logical_or\<Type\> |
| multiplies\<Type\> | greater\<Type\> | logical_not\<Type\> |
| divides\<Type\> | greater_equal\<Type\> |  |
| modules\<Type\> | less\<Type\> | |
| negate\<Type\> | less_equal\<Type\> | |

[代码实现](./std_func_object/src/std_func_obj.cpp)




