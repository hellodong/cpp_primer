
## Templates and Generic Programming
模板是C++中泛型编程的基础。一个模板就是一个创建类或函数的蓝图或者说是公式。当使用一个vector这样的泛型类型，或者find这样的泛型函数时，我们提供足够的信息，将蓝图转换为特定的类或函数。这种转换发生在编译时。

### 定义模板
假定我们希望编写一个函数来比较两个值。在实际中，我们可能想要定义多个函数，每个函数比较一种给定类型的值。我们初次尝试可能定义多个重载函数:
```C++
int compare(const std::string &v1, const std::string &v2)
{
    if (v1 < v2) return -1;
    else if (v1 > v2) return 1;
    
    return 0;
}

int compare(const double &v1, const double &v2)
{
    if (v1 < v2) return -1;
    else if (v1 > v2) return 1;

    return 0;
}
```
这两个函数几乎是一样的，唯一的差异是参数的类型，函数体则完全一样。<br>
如果对每种希望比较的类型都不得不重复定义完全一样的函数体，是非常繁琐且容易出错的。

#### 函数模板 
我们可以定义一个通用的**函数模板(function template)**, 而不是为每个类型定义一个新函数。一个函数模板就是一个公式，可用来生成针对特定类型的函数版本。
```c++
template <typename T>
int compare(const T &v1, const T &v2)
{
    if (v1 < v2) return -1;
    else if (v1 > v2) return 1;

    return 0;
}
```
模板定义关键字template开始，后面跟一个**模板参数列表(template parameter list)**, 这是一个逗号分割的一个或多个模板参数(template parameter)的列表，用小于（<）和(>)包围起来。
- 在模板定义中，模板参数列表不能为空

模板参数表示在类或函数定义中用到的类型或值。当使用模板时，我们（隐式地或显示地）指定模板参数(template argument)， 将其绑定到模板参数上。<br>
我们的compare函数声明了一个名为T的类型参数。在compare中，我们用名字T表示一个类型。而T表示的实际类型在编译时根据compare的使用情况来确定

##### 实例化函数模板
当我们调用一个函数模板时，编译器用函数实参来为我们推断模板实参。即，当我们调用compare时，编译器使用实参的类型来确定绑定到模板参数类型。
```C++
std::cout << compare(1,0) << std::endl;  // T为int
```
编译器用推断出的模板参数来为我们实例化(instantiate)一个特定版本的函数。当编译器实例化一个模板时，他使用实际的模板实参代替对应的模板参数创建出模板的一个新“实例”。
```C++
// 实例化出int compare(const int &, const int &)
std::cout << compare(1, 0) << std::endl; // T为int

// 实例化出int compare(const std::vector<int> &, const std::vector<int> &)
std::vector<int> vec1{1,2,3}, vec2{4,5,6};
std::cout << compare(vec1, vec2) << std::endl;  // T为vector<int>
```
编译器会实例化出两个不同版本的compare。这些编译器生成的版本通常被称为模板的**实例(instantiation)**。

##### 模板类型参数
我们的compare函数有一个模板类型参数(type parameter)。一般来说，我们可以将类型参数看作类型说明符，就像内置类型或类类型说明符一样。特别是，类型参数可以用来指定返回类型或函数的参数类型，以及在函数体内用于变量声明或类型转换:
```C++
template <typename T> T foo (T* p)
{
    T tmp = *p; //tmp 的类型将是指针p指向的类型

    return tmp;
}
```
类型参数前必须使用关键字class 或 typename.
```C++
// 错误: U之前必须加上class 或 typename
template <typename T,U>T calc (const T&, const U&)
```
在模板参数列表中，这两个关键字含义相同，可以互换使用。一个模板参数列表可以同时使用这两个关键字:
```C++
// 正确：在模板参数列表中，typename和class没有什么不同
template <typename T, class U> calc (const T&, const U&);
```
##### 非类型模板参数
除了定义类型参数，还可以在模板中定义**非类型参数(nontype parameter)**。一个非类型参数表示一个值而非一个类型。我们通过一个特定的类型名而非关键字class或typename指定非类型参数。<br>
当一个模板被实例化，非类型参数被一个用户提供的或编译器推断出的值所替代。这些值必须是常量表达式，从而允许编译器在编译时实例化模板。
```C++
template <unsigned N, unsigned M>
int compare(const char (&p1)[N], const char (&p2)[M])
{
    return strcmp(p1, p2);
}
```
当我们调用这个版本时compare时:
```C++`
compare("hi","mom");
```
编译器会使用字面常量的大小来替代N和M，从而实例化模板。记住，编译器会在一个字符串字面常量的末尾插入一个空字符为终结符，因此编译器会实例化如下版本：
```C++
int compare(const char (&p1)[3], const char (&p2)[4]);
```
一个非类型参数可以是一个整型，或者是一个指向对象或函数类型的指针或左值引用。绑定到非类型整型参数的实参必须是一个常量表达式

##### inline和constexpr函数模板
函数模板可以声明为inline或constexpr的，如同非模板函数一样。inline或constexpr说明符放在模板参数列表之后，返回类型之前:
```C++
//正确: inline 说明符跟在模板参数列表之后
template <typename T> inline T min (const T&, const T&);
```

##### 模板编译
当编译器遇到一个模板定义时，它并不生成代码。只有当我们实例化出模板的一个特定版本时，编译器才会生成代码。当我们使用(而不是定义)模板时，编译器才生成代码，这一特性影响了我们如何组织代码以及错误何时被检测到。<br>
通常，我们调用一个函数时，编译器只需要掌握函数的声明。类似，当我们使用一个类类型的对象时，类定义必须是可用的，但成员函数的定义不必出现。因此，我们将类定义和函数声明放在头文件中，而普通函数和类的成员函数定义放在源文件中。<br>
模板不同：为了生成一个实例化版本，编译器需要掌握函数模板或类模板成员函数定义。因此，与非模板代码不同，模板头文件通常既包括声明也包括定义。

##### 大多数编译错误在实例化期间报告
模板直到实例化时才会生成代码，这一特性影响了我们何时才会获知模板内代码的编译错误。通常，编译器会在三个阶段报告错误:
- 编译模板本身时，这个阶段，编译器通常不会发现很多错误。编译器可以检查语法错误，例如忘记分号或者变量名拼错等，但也就这么多了。
- 编译器遇到模板使用时。编译器仍然没有很多可检查的。对于函数模板调用，编译器通常检查实参数目是否正确。它能检查参数类型是否匹配。对于类模板，编译器可以检查用户是否提供了正确数目的模板实参，但也仅限于此了。
- 模板实例化，只有这个阶段才能发现类型相关错误。

#### 类模板
**类模板**(class template)是用来生成类的蓝图的。与函数模板的不同之处是，编译器不能为类模板推断模板参数类型。为了使用类模板，我们必须在模板名后的尖括号中提供额外信息--用来代替模板参数的模板实参列表。

##### 定义类模板
我们将实现StrBlob的模板版本。我们将此模板定义为Blob，意指它不再针对string.类似StrBlob，我们的模板会提供对元素的共享访问能力。与类不同，我们的模板可以用于更多类型的元素。<br>
类似函数模板，类模板以关键字template开始，后跟模板参数列表。在类模板的定义中，我们将模板参数当作替身，代替使用模板时用户需要提供类型或值:
```C++
template<typename T>
class Blob{
    public:
        typedef T value_type;
        typedef typename std::vector<T>::size_type size_type;
        Blob();
        Blob(std::initializer_list<T> il);
        size_type size() const {return data->size();}
        bool empty() const {return data->empty();}
        void push_back(const T tt){data->push_back(t);}
        void push_back(T &&t) {data->push_back(std::move(t));}
        void pop_back();
        T& back();
        T& operator[] (size_type i);
    private:
        std::shared_ptr<std::vector<T>> data;
        void check(size_type i, const std::string &msg) const;
};
```
我们的Blob模板有一个名为T的模板类型参数，用来表示Blob保存的元素类型。

##### 实例化模板
我们已经多次见到，当使用类模板时，我们必须提供额外信息。我们现在直到这些额外信息是**显式模板实参(explicit template argument)**列表，他们被绑定到模板参数。编译器使用这些模板实参来实例化出特定的类。
```C++
Blob<int> ia;
Blob<int> ia2={1,2,3,4};
```
从上面两个定义，编译器会实例化出一个与下面定义等价的类:
```C++
class Blob<int> 
{
public:
    typedef typename std::vector<int>size_type size_type;
    Blob();
    Blob(std::initializer_list<int> il);
    //...
    int &operator[](size_type i);
private:
    std::shared_ptr<std::vector<int>> data;
    void check(size_type i, const std::string &msg) const;
};
```
编译器从我们的Blob模板实例化出一个类时，它会重写Blob模板，将模板参数T的每个实例替换为给定的模板实参。对我们指定的每一种元素类型，编译器都生成一个不同的类:
```C++
//下面的定义实例化出两个不同的Blob类型
Blob<string> names;
Blob<double> prices;
```
这两个定义会实例化出两个不同的类。

- 一个类模板的每个实例都形成一个独立的类。类型Blob<std::string>与任何其他Blob类型都没有关联，也不会对任何其他Blob类型的成员有特殊访问权限。

##### 类模板成员函数
与其他任何类相同，我们既可以在类模板内部，也可以在类模板外部为其定义成员函数，且定义在类模板内的成员函数被隐式声明为内敛函数。<br>
类模板的成员函数本身是一个普通函数。但是类模板的每个实例都有其自己版本的成员函数。因此，类模板的成员函数具有和模板相同的模板参数。因而，定义在类模板之外的成员就必须以关键字template开始，后接类模板参数列表。<br>
与往常一样，当我们在类外定义成员时，必须说明成员属于哪个类。而且，从一个模板生成的类的名字中必须包含其模板实参。当我们定义一个成员函数时，必须说明成员属于哪个类。而且，从一个模板生成的类的名字中必须包含模板实参。当我们定义一个成员函数时，模板实参与模板形参相同。即，对于StrBlob的 一个给定的成员函数
```C++
ret-type StrBlob::member-name(parameter-list)
```
对应Blob的成员应该是这样:
```C++
template <typename T>
ret-type Blob<T>::member-name(parameter-list)
```

##### check和元素访问成员
定义check成员:
```C++
template<typename T>
void Blob<T>::check(size_type i, const std::string &msg) const
{
    if (i >= data->size())
    {
        throw std::out_of_range(msg);
    }
}
```
下标运算符和back函数用模板参数指出返回类型，其他未变：
```C++
template <typename T>
T& Blob<T>::back()
{
    check (0, "back on empty Blob");
    return data->back();
}
template <typename T>
T& Blob<T>::operator[](size_type i)
{
    check (i, "subscript out of range");
    return (*data)[i];
}
```
在原StrBlob类中，这些运算符返回string&。而模板版本则返回一个引用，指向用来实例化Blob的类型。<br>
pop_back函数与原StrBlob的成员几乎相同：
```C++
template <typename T> void Blob<T>::pop_back()
{
    check (0,"pop_back on empty Blob");
    data->pop_back();
}
```

##### Blob构造函数
与其他任何定义在类模板外的成员一样，构造函数定义要以模板参数开始:
```C++
template <typename T>
Blob<T>::Blob(): data(std::make_shared<std::vector<T>>) {}
```
这段代码在作用域Blob<T>中定义了名为Blob的成员函数。类似StrBlob默认构造函数(12.1.1节)， 此构造函数分配一个空vector,并将指向vector的指针保存在data中。类似，接受一个initializer_list参数的构造函数将其类型参数T作为initializer_list参数的元素类型:
```C++
template <typename T>
Blob<T>::Blob(std::initializer_list<T> il):data(std::make_shared<std::vector<T>>(il)) {}
```
在本样例中，我们用参数il来初始化此vector。为了使用该构造函数，我们必须传递给它一个initializer_list，其中元素必须与Blob的元素类型兼容：
```C++
Blob<std::string> articles = {"a", "an","the"};
```
这条语句中，构造函数的参数类型为initializer_list<string>。列表中的每个字符串常量隐式的转为一个string。

##### 类模板成员函数实例化
默认情况下，一个类模板成员函数只有当程序用到它时才进行实例化。例如:
```C++
// 实例化Blob<int>和接受initializer_list<int>的构造函数
Blob<int> squares = {0,1,2,3,4,5,6,7,8,9};
// 实例化Blob<int>::size() const
for (size_t i = 0;i != squares.size();i++)
{
    squares[i] = i*i; // 实例化Blob<int>::operator[](size_t)
}
```
实例化了Blob<int>类和它的三个成员函数：operator[]、size和接受initializer_list<int>的构造函数。<br>
如果一个成员函数没有被使用，则它不会被实例化。成员函数只有在被用到时才进行实例化，这一特性使得即使某种类型不能完全符合模板操作的要求，我们仍然能用到该类型实例化类。
- 默认情况下，对于一个实例化了的类模板，其成员只有在使用时才被实例化。

##### 在类代码内简化模板类名的使用
当我们使用一个类模板类型时必须提供模板实参，但这一规则有一个例外。在类模板自己作用域中，我们可以直接使用模板名而不提供实参:
```C++
// 若试图访问一个不存在的元素，BlobPtr抛出一个异常
template <typename T> class BlobPtr{
    public:
        BlobPtr():curr(0) {}
        BlobPtr(Blob<T> &a, size_t sz = 0):wptr(a.data), curr(sz) {}
        T& operator *() const 
        {
            auto p = check (curr, "deference past end");
            return (*p)[curr];// (*p)为本对象指向的vector
        }
        //递增和递减
        BlobPtr& operator++();// 前置运算符
        BlobPtr& operator--();
    private:
        //若检查成功，check返回一个指向vector的shared_ptr
        std::shared_ptr<std::vector<T>> check(std::size_t, const std::string &) const;
        // 保存一个weak_ptr，表示底层vector可能被销毁
        std::weak_ptr<std::vector<T>> wptr;
        std::size_t curr; //数组中当前位置
};
```
BlobPtr的前置递增和递减成员返回BlobPtr&,而不是BlobPtr<T>&。当我们处于一个类模板作用域中时，编译器处理模板自身引用时就好像我们已经提供了与模板参数匹配的实参一样。
```C++
BlobPtr<T>& operator++();
BlobPtr<T>& operator--();
```

##### 在类模板外使用类模板名
当我们在类模板外定义成员时，必须记住，我们并不在类的作用域中，直到遇到类名才表示进入类的作用域
```C++
template <typename T>
BlobPtr<T> BlobPtr<T>::operator++()
{
    // 此处无须检查；调用当前递增时会进行检查
    BlobPtr ret = *this;
    ++*this;
    return ret;   
}
```
由于返回类型位于类作用域外，我们必须指出返回类型是一个实例化BlobPtr,它所使用类型与类实例化所用类型一致。在函数体内，我们已经进入类作用域，因此在定义ret时无须重复模板实参。如果不提供模板实参，则编译器将假定我们使用类型与成员实例化所用类型一致。因此，ret的定义与如下代码等价:
```C++
BlobPtr<T> ret = *this;
```
- 在一个类模板的作用域内，我们可以直接使用模板名而不必指定模板实参。

##### 类模板和友元
当一个类包含一个友元声明时，类与友元各自是否是模板是相互无关的。如果一个类模板包含一个非模板友元，则友元被授权可以访问所有模板实例。如果友元自身是模板，类可以授权给所有友元模板实例，也可以只授权给特定实例。<br>
类模板与另一个(类或函数)模板间友好关系的最常见形式是建立对应实例及其友元间的友好关系。例如,Blob类应该将BlobPtr类和一个模板版本的Blob相等运算符定义为友元。<br>
为了引用(类或函数)模板的一个特定实例，我们必须首先声明模板自身。一个模板声明包括模板参数列表:
```C++
// 前置声明，在Blob中声明友元所需要的
template <typename> class BlobPtr;
template <typename> class Blob;
template <typename T> bool operator ==(const Blob<T>&, const Blob<T>&);
template <typename T> 
class Blob{
    //每个Blob实例将访问权限授予用相同类型实例化的BlobPtr和相等运算符
    friend class BlobPtr<T>;
    friend bool operator==<T>(const Blob<T>&, const Blob<T>&);
};
```
友元的声明用Blob的模板形参作为他们自己的模板实参。因此，友好关系被限定在用相同类型实例化的Blob与BlobPtr相等运算符之间：
```C++
Blob<char> ca; //BlobPtr<char>和operator==<char>都是本对象的友元
Blob<int> ia; //BlobPtr<int>和operator==<int>都是本对象的友元
```
BlobPtr<char>的成员可以访问ca(或任何其他Blob<char>对象)的非public部分，但ca对ia的Blob任何其他实例都没有特殊访问权限。<br>
<br>

一个类也可以将另外一个模板的每个实例都声明为自己的友元，或者限定特定的实例为友元:
```C++
//前置声明，在将模板的一个特定实例声明为友元时要用到
template <typename T> class Pal;

class C { //C 是一个普通的非模板类
    friend class Pal<C>;   //用类C实例化的Pal是C的一个友元
    // Pal2的所有实例都是C的友元；这种情况无须前置声明
    template <typename T> friend class Pal2;
};
template <typename T>class C2 {  //C2本身是一个类模板
    // C2的每个实例将相同实例化的Pal声明为友元
    friend class Pal<T>; //Pal的模板声明必须在作用域之外
    // Pal2的所有实例都是C2的每个实例的友元，不需要前置声明
    template <typename X> friend class Pal2;
    // Pal3是一个非模板类，它是C2所有实例的友元
    friend class Pal3;  // 不需要Pal3的前置声明
};
```
为了让所有实例成为友元，友元声明中必须使用与类模板本身不同的模板参数。

##### 令模板自己的类型参数成为友元
在C++11标准中，我们可以将模板类型参数声明为友元:
```C++
template <typename Type> class Bar{
    friend Type;
};
```
此处我们将用来实例化Bar的类型声明为友元。因此，对于某个类型名为Foo,Foo将成为Bar<Foo>的友元，Sales_data将成为Bar<Sales_data>的友元，依次类推。<br>
虽然友元通常来说应该是一个类或是一个函数，但我们完全可以用一个内置类型来实例化Bar。这种与内置类型的友好关系是允许的，以便我们能用内置类型来实例化Bar这样的类。

##### 模板类型别名
类模板的一个实例定义了一个类类型，与任何其他类类型一样，我们可以定义一个typedef来引用实例化的类:
```C++
typedef Blob<std::string> StrBlob;
```
这条typedef语句允许我们运行在12.1.1节中编写的代码，而使用的却是用std::string实例化的模板版本Blob。由于模板不是一个类型，我们不能定义一个typedef引用一个模板。即，无法定义一个typedef引用Blob<T>。<br>
但是, C++11标准允许我们为类模板定义一个类型别名:
```C++
template <typename T> using twin = pair<T,T>;
twin<std::string> authors; // authors是一个pair<string, string>
twin<int> win_loss;        // win_loss是一个pair<int, int>
twin<double> area;         // area 是一个pari<double, double>
```
在这段代码中，我们将twin定义为成员类型相同的pair的别名。这样,twin的用户只需指定一次类型。<br>
当我们定义一个模板类型别名时，可以固定一个或多个模板参数：
```C++
template <typename T> using PartNo = pair<T, unsigned>;
PartNo<std::string> books;   // books是一个pair<std::string, unsigned>
PartNo<Vehicle> cars;        // cars是一个pair<Vehicle, unsigned>
PartNo<Student> kids;        // kids是一个pair<Student, unsigned>
```
这段代码中我们将PartNo定义为一族类型别名，这族类型是second成员为unsigned的pair。PartNo的用户需要指出pair的first成员类型，但不能指定second成员类型。

##### 类模板的static成员
与任何其他类相同，类模板可以声明为static成员:
```C++
template <typename T> class Foo{
    public:
        static std::size_t count() {return ctr;}
    private:
        static std::size_t ctr;
};
```
Foo是一个类模板，它有一个名为count的public static成员函数和一个名为ctr的private static数据成员。每个Foo的实例都有其自己的static成员实例。即，对任意给定类型X，都有一个Foo<X>::ctr和一个Foo<X>::count成员。所有Foo<X>类型的对象共享相同的ctr对象和count函数。例如：
```C++
//实例化static成员Foo<std::string>::ctr和Foo<std::string>::count
Foo<std::string> fs;
//所有三个对象共享相同的 Foo<int>::ctr和Foo<int>::count成员
Foo<int> f1, fi2, fi3;
```
模板类的每个static数据成员必须且仅有一个定义。但是，类模板的每个实例都有一个独有的static对象。因此，与定义模板的成员函数类似，我们将static数据成员也定义为模板:
```C++
template <typename T>
size_t Foo<T>::ctr = 0; //定义并初始化ctr
```
与类模板的其他成员类似，定义开始部分是模板参数列表，随后是我们定义的成员类型和名字。与往常一样，成员名包括成员的类名，对于从模板生成的类来说，类名包括模板实参。因此，当使用一个特定的模板实参类型实例化Foo时，将会为该类型实例化一个独立的ctr,并将其初始化为0。<br>
与非模板类的静态成员相同，我们可以通过类类型对象访问一个类模板的static成员，也可以使用作用域运算符直接访问成员。当然，为了通过类直接访问static成员，我们必须引用一个特定的实例:
```C++
Foo<int> fi;                //实例化Foo<int>类和static数据成员ctr
auto ct = Foo<int>::count();//实例化Foo<int>::count
ct = fi.count();            //使用Foo<int>::count
ct = Foo::count();          //错误: 使用哪个模板实例count?
```
类似任何其他成员函数,一个static成员函数只有在使用时才会实例化。

#### 模板参数
类似函数参数名字，一个模板参数名字也没什么内在含义。我们通常将类似参数命名为T，但实际上我们可以使用任何名字。

##### 模板参数与作用域
模板参数遵循普通作用域规则。一个模板参数名的可用范围是在其声明之后，至模板声明或定义结束之前。与任何其他名字一样，模板参数会隐藏外层作用域中声明的相同名字。但是，与大多数其他上下文不同，在模板内不能重用模板参数名:
```C++
typedef double A;
template <typename A, typename B> void f(A a, B b)
{
    A tmp = a;  // tmp的类型为模板参数A的类型，而非double
    double B;   // 错误：重声明模板参数B
}
```
正常名字隐藏规则决定了A的typedef被类型参数A隐藏。因此,tmp不是一个double,其类型是使用f时绑定到类型参数A的类型。由于我们不能重用模板参数名，声明名字为B的变量是错误的。<br>
由于参数名不能重用，所以一个模板参数名在一个特定模板参数列表中只能出现一次。

##### 模板声明
模板声明必须包含模板参数:
```C++
// 声明但不定义compare和Blob
template <typename T> int compare(const T&, const T&);
template <typename T> class Blob;
```
与函数参数相同，声明中的模板参数名字不必与定义中相同:
```C++
// 3个calc都指向相同的函数模板
template <typename T> T calc(const T&, const T&); // 声明
template <typename U> U calc(const U&, const U&); //声明
// 模板定义
template <typename Type>
Type calc(const Type& a, const Type& b) 
{
    /* ... */
}
```
当然，一个给定模板的每个声明和定义必须有相同数量和种类的参数。
##### 使用类的类型成员
我们用作用域运算符(::)访问static成员和类型成员。在普通(非模板)代码中，编译器掌握类的定义。因此，它知道通过作用域运算符访问的名字是类型还是static成员。例如，如果我们写下string::size_type，编译器有string的定义，从而知道size_type是一个类型。<br>
但对于模板代码就存在困难。例如，假定T是一个模板类型参数，当编译器遇到类似T::mem这样的代码时，它不会知道mem是一个类型成员还是一个static数据成员，直到实例化时才会知道。但是，为了处理模板，编译器必须知道名字是否表示一个类型。例如，T是一个类型参数名字，当编译器遇到如下形式语句时:
```C++
T::size_type * p;
```
需要知道我们是正在定义一个名为p的变量还是将一个名为size_type的static数据成员与名为p的变量相乘。<br>
默认情况下，C++语言假定通过作用域运算符访问的名字不是类型。因此，如果我们希望使用一个模板类型参数的类型成员，就必须显式告诉编译器该名字是一个类型。我们通过使用关键字typename来实现这一点:
```C++
template <typename T>
typename T::value_type top(const T& c)
{
    if (!c.empty())
    {
        return c.back();
    }
    else 
    {
        return typename T::value_type();
    }
}
```
我们的top函数期待一个容器类型实参，它使用typename指明其返回类型并在c中没有元素时生成一个初始化元素返回给调用者。

##### 默认模板实参
在C++11标准中，我们可以为函数和类模板提供**默认模板实参**(default template argument)。更早的C++标准只允许为类模板提供默认实参。<br>
我们重写compare,默认使用标准库的less函数对象模板:
```C++
// compare有一个默认模板实参less<T>和一个默认函数实参F()
template <typename T, typename F= less<T>>
int compare (const T &v1, const T &v2, F f= f())
{
    if (f(v1,v2))
    {
        return -1;
    }
    if (f(v2,v1))
    {
        return 1;
    }
    return 0;
}
```
我们为模板添加了第二个类型参数，名为F，表示可调用对象的类型；并定义了一个新的函数参数f,绑定到一个可调用对象上。<br>
我们为此模板参数提供了默认实参，并为其对应的函数参数也提供了默认实参。默认模板实参指出compare将使用标准库的less函数对象类，它是使用与compare一样的类型参数实例化。默认函数实参指出f将是类型F的一个默认初始化对象。<br>
当用户调用这个版本的compare时，可以提供自己的比较操作，但这并不是必需的:
```C++
bool i = compare(0, 42);  // 使用less; i 为 -1
// 结果依赖于item1和item2中的isbn
Sales_data item1(cin), item2(cin);
bool j = compare(item1, item2, compareIsbn);
```
第一个调用使用默认函数实参，即，类型less<T>的一个默认初始化对象。在此调用中，T为int,因此可调用对象类型为less<int>。compare的这个实例化版本将使用less<int>进行比较操作。<br>
第二个调用中，我们传递给compare三个实参:compareIsbn和两个Sales_data类型的对象。当传递给compare三个实参时，第三个实参的类型必须是一个可调用对象，该可调用对象的返回类型必须能转换为bool值，且接受的实参类型必须与compare的前两个实参类型兼容。与往常一样，模板参数的类型从它们对应的函数实参推断而来。在此调用中，T的类型被推断为Sales_data,F被推断为compareIsbn类型<br>
与函数默认实参一样，对于一个模板参数，只有当它右侧所有参数都有默认实参时，它才可以有默认实参。
##### 模板默认实参与类模板
无论何时使用一个类模板，我们都必须在模板名之后接上尖括号。尖括号指出类必须从一个模板实例化而来。特别是，如果一个类模板为其所有模板参数都提供了默认实参，且我们希望使用这些默认实参，就必须在模板名之后跟一个尖括号对:
```C++
template <class T= int> class Numbers{
    public:
        Numbers(T v=0):val(v) {}
    private:
        T val;
};
Numbers <double> lots_of_precision;
Numbers <> average_precision;        // 空<>表示我们希望使用默认类型
```
我们实例化了两个Numbers版本:average_precision是用int替代T实例化的;lots_of_precision使用double 替代T实例化得到的。

#### 成员模板
一个类(无论是普通类还是模板类)可以包含本身是模板的成员函数。这种成员成为**成员模板**(member template)。成员模板不能是虚函数。

##### 普通类的成员模板
作为普通类包含成员模板，我们定义一个类，类似unique_ptr所使用的默认删除其类型。类似默认删除器，我们的类将包含一个重载的函数调用运算符，它接受一个指针并对此指针执行delete。与默认删除器不同，我们的类还将在删除器被执行时打印一条信息。由于希望删除器适用于任何类型，所以我们将调用运算符定义为一个模板:
```C++
// 函数对象类，对给定指针执行delete
class DebugDelete{
    public:
        DebugDelete(std::ostream &s=std::cerr):os(s){}
        template <typename T> void operator()(T *p) const 
        { os << "deleting unique_ptr" << std:endl; delete p;}
    private:
        std::ostream &os;
};
```
与任何其他模板相同，成员模板也是以模板参数列表开始的。每个DebugDelete对象都有一个ostream成员，用于写入数据；还包含一个自身是模板的成员函数。我们可以用这个类替代delete：
```c++
double* p = new double;
DebugDelete d;          // 可像delete表达式一样使用的对象
d(p);                   // 调用DebugDelete::operator()(double *), 释放p
int *ip = new int;
DebugDelete()(ip);      //在一个临时DebugDelete对象上调用operator()(int *)
```
调用一个DebugDelete对象会delete其给定的指针，我们也可以将DebugDelete用作unique_ptr的删除器。为了重载unique_ptr的删除器，我们在尖括号内给出删除器类型，并提供一个这种类型的对象给unique_ptr的构造函数:
```C++
unique_ptr<int, DebugDelete> p (new int, DebugDelete());
unique_ptr<std::string, DebugDelete> sp (new std::string, DebugDelete());
```
在本例中，我们声明P的删除器类型为DebugDelete,并在p的构造函数中提供了该类型的一个未命名对象。<br>
unique_ptr的析构函数会调用DebugDelete的调用运算符。因此，无论何时unique_ptr的析构函数实例化时，DebugDelete的调用运算符都会实例化:因此，上述定义会这样实例化。
```C++
// DebugDelete成员模板实例化样例
void DebugDelete::operator() (int *p) const {delete p;}
void DebugDelete::operator() (std::string *sp) const {delete sp;}
```

##### 类模板成员模板
对于类模板，我们可以为其定义成员模板。在此情况下，类和成员各自有自己的、独立的模板参数。我们将为Blob类定义一个构造函数，它接受两个迭代器，表示要拷贝的元素范围。我们希望支持不同类型序列的迭代器，因此将构造函数定义为模板:
```C++
template <typename T> class Blob{
    template <typename It> Blob(It b, It e);
};
```
此构造函数有自己的模板类型参数It,作为它的两个函数参数类型。<br>
与类模板的普通函数成员不同，成员模板是函数模板。当我们在类模板外定义一个成员模板时，必须同时为类模板和成员模板提供模板参数列表。类模板的参数列表在前，后跟成员自己的模板参数列表:
```C++
template <typename T>   //类的类型参数
template <typename It>  //构造寒素的类型参数
   Blob<T>::Blob(It b, It e): data(std::make_shared<std::vector<T>>(b,e)){}
```
此例中，我们定义了一个类模板的成员，类模板有一个模板类型参数，命名为T。而成员自身是一个函数模板，它有一个名为It的类型参数。<br>

为了实例化一个类模板的成员模板，我们必须同时提供类和函数模板的实参。与往常一样，我们在哪个对象上调用成员模板，编译器就根据该对象的类型推断模板参数的实参。与普通函数模板相同，编译器通常根据传递给成员模板的函数实参来推断它的模板实参:
```C++
int ia[] = {0,1,2,3,4,5,6,7,8,9};
std::vector<long> vi = {0,1,2,3,4,5,6,7,8,9};
std::list<const char *> w={"now", "is", "the", "time"};
// 实例化Blob<int>类及其接受两个int*参数的构造函数
Blob<int> a1(begin(ia), end(ia));
// 实例化Blob<int>类的接受两个vector<long>::iterator参数构造函数
Blob<int> a2(vi.begin(), vi.end());
// 实例化Blob<int>类的接受两个vector<long>::iterator参数构造函数
Blob<std::string> a3(w.begin(), w.end());
```
当我们定义a1时，显示的指出编译器应该实例化一个int版本的Blob。构造函数自己的类型参数通过begin(ia)和end(ia)类型推断，结果为int*。因此，a1定义实例化如下版本:
```C++
Blob<int>::Blob(int *, int *);
```
a2的定义使用了已经实例化的Blob<int>类，并用vector<short>::iterator替换It实例化构造函数。a3的定义(显示地)实例化了一个string版本的Blob，并(隐式的)实例化了该类的成员模板构造函数，其模板参数被绑定到list<const char *>。

#### 控制实例化
当模板被使用时才会进行实例化这一特性意味着，相同实例可能出现在多个对象文件中。当两个或多个独立编译的源文件使用了相同的模板，并提供了相同模板参数时，每个文件中就都会有该模板的一个实例。<br>
在大系统中，在多个文件中实例化相同模板的额外开销可能非常严重。在C++11标准中，我们可以通过显示实例化(explicit instantiation)来避免这种开销。一个显式实例化有如下形式:
```C++
extern template declaration; // 实例化声明
template declaration;        // 实例化定义
```
*declaration*是一个类或函数声明，其中所有模板参数已被替换为模板实参。例如:
```C++
extern template class Blob<string>;             // 声明
template int compare(const int &, const int &); // 定义
```
当编译器遇到extern模板声明时，它不会在本文件中生成实例化代码。将一个实例化声明为extern就表示承诺在程序其他位置有该实例化的一个非extern声明。对于一个给定的实例化版本，可能有多个extern声明，但必须只有一个定义。<br>
由于编译器在使用一个模板时自动对其实例化，因此extern声明必须出现在任何使用此实例化版本的代码之前:
```C++
// 这些模板类型必须在程序其他位置进行实例化
extern template class Blob<string>;
extern template int compare<const int &, const int &>;
Blob<string> sa1, sa2;  // 实例化会出现在其他位置
// Blob<int>及其接受initializer_list的构造函数在本文件中实例化
Blob<int> a1 = {0,1,2,3,4,5,6,7,8,9};
Blob<int> a2(a1);  //拷贝构造函数在本文件中实例化
int i = compare(a1[0], a2[0]); // 实例化出现在其他位置
```
上面源文件的.o文件将包含Blob<int>的实例及其接受initializer_list参数的构造函数和拷贝构造函数实例。而compare<int>函数和Blob<string>类将不再本文件中进行实例化。这些模板的定义必须出现在程序的其他文件中:
```C++
// templateBuild.cpp
template int compare(const int &, const int &);
template class Blob<string>; // 实例化类模板的所有成员
```
当编译器遇到一个实例化定义时，它为其生成代码。因此，文件templateBuild.o将会包含compare的int实例化版本定义和Blob<string>类的定义。当我们编译此应用程序时，必须将templateBuild.o和上面的.o连接在一起。
- 对每个实例化声明，在程序中某个位置必须有其显式的实例化定义

一个类模板的实例化定义会实例化该模板的所有成员，包括内敛的成员函数。当编译器遇到一个实例化定义时，它不了解程序使用哪些成员函数。因此，与处理类模板的普通实例化不同，编译器会实例化该类的所有成员。即使我们不使用某个成员，它也会被实例化。因此，我们用来显示实例化一个类模板类型，必须能用于模板的所有成员。
- 一个类模板的实例化定义中，所有类型必须能用于模板的所有成员函数。

#### 效率与灵活性
对模板设计者所面对的设计选择，标准库智能指针类型给出一个很好的展示。shared_ptr和unique_ptr之间的明显不同是它们管理所保存的指针的策略 ----  前者给予我们共享指针所有权的能力;后者独占指针。这一差异对两个类功能来说是至关重要的。<br>
这两个类的另一个差异是它们允许用户重载默认删除器的方式。我们可以很容易地重载一个shared_ptr删除器，只要在创建或reset指针时传递给它一个可调用对象即可。与之相反，删除器地类型是一个unique_ptr对象地类型的一部分。用户必须在定义unique_ptr时以显示模板实参的形式提供删除器的类型。因此，对于unique_ptr的用户来说，提供自己的删除器就更为复杂。<br>
##### 在运行时绑定删除器
shared_ptr必须能直接访问其他删除器。即，删除器必须保存为一个指针或一个封装了指针的类(如function)。可以确定shared_ptr不是将删除器直接保存为一个成员，因为删除器的类型直到运行时才会知道。实际上，在一个shared_ptr的生存期中，我们可以随时改变其删除器的类型。我们可以使用一种类型的删除器构造一个shared_ptr，随后使用reset赋予此shared_ptr另一种类型的删除器。通常，类成员的类型在运行时是不能改变的。因此，不能直接保存删除器。<br>
为了考察删除器是如何正确工作的，让我们假定shared_ptr将它管理的指针保存在一个成员p中，且删除器是通过一个名为del的成员来访问的。则shared_ptr的析构函数必须包含类似下面语句:
```C++
del?del(p):delete p;  // del(p)需要运行时跳转到del的地址
```
由于删除器是间接保存的，调用del(p)需要一次运行时的跳转操作，转到del中保存的地址来执行对应代码。

##### 在编译时绑定删除器
unique_ptr有两个模板参数，一个表示它所管理的指针，另一个表示删除器的类型。由于删除器的类型是unique_ptr类型的一部分，因此删除器成员的类型在编译时知道的，从而删除器可以直接保存在unique_ptr对象中。<br>
unique_ptr的析构函数与shared_ptr的析构函数类似，也是对其保存的指针调用用户提供的删除器或执行delete:
```C++
// del在编译时绑定；直接调用实例化的删除器
del(p);  //无运行时额外开销
```
del的类型或者是默认删除器类型，或者是用户提供的类型。到底是哪种情况没有关系，执行的代码在编译时肯定会知道。通过在编译时绑定删除器，unique_ptr避免了间接调用删除器的运行时开销。通过在运行时绑定删除器，shared_ptr使用户重载删除器更为方便。

### 模板实参推断
对于函数模板，编译器利用调用中的函数实参确定其模板参数。从函数实参确定模板实参的过程被称为**模板实参推断(template argument deduction)**。在模板实参推断中，编译器使用函数调用中的实参类型寻找模板实参，用这些模板实参生成的函数版本与给定的函数调用最为匹配。

#### 类型转换与模板类型参数
与非模板函数一样，我们在一次调用中传递给函数模板的实参被用来初始化函数的形参。如果一个函数形参类型使用了模板类型参数，那么它采用特殊的初始化规则。只有很有限的几种类型转换会自动地应用于这些实参。编译器通常不是对实参进行类型转换，而是生成一个新地模板实例。<br>
与往常一样，顶层const无论是在形参中还是在实参中，都会被忽略。在其他类型转换中，能在调用中应用于函数模板地包括如下两项:
- const 转换： 可以将一个非const 对象的引用(或指针) 传递给一个const的引用(或指针)形参
- 数组或函数指针转换：如果函数形参不是引用类型，则可以对数组或函数类型的实参应用正常的指针转换。一个数组实参可以转为一个指向其首元素的指针。类似的，一个函数实参可以转换为一个该函数类型的指针。

其他类型转换，如算数转换、派生类向基类转换以及用户定义的转换，都不能应用于函数模板。作为一个例子，考虑对函数fobj和fref的调用。fobj函数拷贝它的参数，而fref的参数是引用类型:
```C++
template <typename T> T fobj(T,T);    // 实参被拷贝
template <typenmae T> T fref(const T&, const T&); // 引用
std::string s1("a value");
const std::string s2("another value");
fobj(s1,s2);    // 调用fobj(std::string, std::string); const被忽略
fref(s1,s2);    // 调用fref(const string&, const string &), 将s1转换为const是允许的
int a[10], b[42];
fobj(a,b);   // 调用f(int *, int *)
fref(a,b);   // 错误: 数组类型不匹配
```
在一对调用中，我们传递了一个string和一个const string。虽然这些类型不严格匹配，但两个调用都是合法的。在fobj调用中，实参被拷贝，因此原对象是否是const没有关系。在fref调用中，参数类型是const的引用。对于一个引用参数来说，转换const是允许的，因此这个调用也是合法的。<br>
在下一对调用中，我们传递了数组实参，两个数组大小不同，因此是不同类型。在fobj调用中，数组大小不同无关紧要。两个数组被转换为指针。fobj中的模板类型为int *。但是，fref调用时不合法的。如果形参是一个引用，则数组不会转换为指针。a和b的类型是不匹配的，因此调用是错误的。

- 将实参传递给带模板类型的函数形参时，能够自动应用的类型转换只有const转换及数组或函数到指针的转换。

#### 函数模板显示实参
在某些情况下，编译器无法推断出模板实参的类型。其他一些情况下，我们希望允许用户控制模板实例化。当函数返回类型与参数列表中任何类型都不相同时，这两种情况最常出现。

##### 指定显示模板实参
作为一个允许用户指定使用类型的例子，我们将定义一个名为sum的函数模板，它接受两个不同类型的参数。我们希望允许用户指定结果的类型。这样，用户就可以选择合适的精度。<br>
我们可以定义表示返回类型的第三个模板参数，从而允许用户控制返回类型:
```C++
// 编译器无法推断T1，它未出现在函数参数列表中
template <typename T1, typename T2, typename T3>
T1 sum(T2,T3);
```
在本例中，没有任何函数实参的类型可用来推断T1的类型。每次调用sum时调用这都必须为T1提供一个**显示模板实参**(explicit template argument)。<br>
我们提供显示模板实参的方式与定义类模板实例的方式相同。显示模板实参在尖括号中给出，位于函数名之后，实参列表之前:
```C++
// T1是显示指定的，T2和T3是从函数实参类型推断而来的
auto val3 = sum<long long>(i, lng); // long long sum(int, long)
```
此调用显示指定T1的类型。而T2和T3的类型则由编译器从i和lng的类型推断出来。<br>
显示模板实参按由左至右的顺序与对应的模板参数匹配: 第一个模板实参与第一个模板参数匹配，第二个实参与第二个参数匹配，以此类推。只有尾部(最右)参数的显示模板实参才可以忽略，而且前提是它们可以从函数参数推断出来。如果我们的sum函数按照如下形式编写:
```C++
// 糟糕的设计: 用户必须指定所有三个模板参数
template <typename T1, typename T2, typename T3>
T3 alternative_sum(T2, T1);
```
则我们总是必须为所有三个形参指定实参:
```C++
// 错误: 不能推断前几个模板参数
auto val3 = alternative_sum<long long>(i, lng);
// 正确: 显式指定了所有三个参数
auto val2 = alternative_sum<long long, int, long>(i, lng);
```
##### 正常类型转换应用于显式指定的实参
对于用普通类型定义的函数参数，允许进行正常的类型转换，出于同样的原因，对于模板类型参数已经是显式指定了的函数实参，也进行正常的类型转换：
```C++
long lng;
compare(lng, 1024);         // 错误： 模板参数不匹配
compare<long>(lng, 1024);   // 正确: 实例化compare(long, long)
compare<int>(lng, 1024);    // 正确: 实例化compare(int, int)
```
第一个调用是错误的，因为传递给compare的实参必须具有相同的类型。如果我们显式指定模板类型参数，就可以进行正常类型转换了。因此，调用compare<long>等价于调用一个接受两个const long&参数的函数。int类型的参数被自动转化为long。在第三个调用中，T被显式指定为int,因此lng被转换为int。

##### 尾置返回类型与类型转换
当我们希望用户确定返回类型时，用显式模板实参表示模板函数的返回类型是很有效的。但在其他情况下，要求显式指定模板实参会给用户增添额外负担，而且不会带来什么好处。例如，我们可能希望编写一个函数，接受表示序列的一对迭代器和返回序列中的一个元素引用:
```C++
template <typename It>
??? &fcn(It beg, It end)
{
    // 处理序列
    return *beg;    //返回序列中一个元素的引用
}
```
我们并不知道返回结果的准确类型，但知道所需类型是所处理的序列的元素类型:
```C++
vector<int> vi = {1,2,3,4,5};
Blob<string> ca = {"hi", "bye"};
auto &i = fcn(vi.begin(), vi.end());  // fcn 应该返回 int &
auto &s = fcn(ca.begin(), ca.end());  // fcn 应该返回 string &
```
此例中，我们知道函数应该返回\*beg,而且知道我们可以用decltype(\*beg)来获取此表达式的类型。但是，在编译器遇到函数的参数列表之前，beg都是不存在的。为了定义此函数，我们必须使用尾置返回类型。由于尾置返回出现在参数列表之后，它可以使用函数的参数：
```C++
template <typename It>
auto fcn(It beg, It end) ->decltype(*beg)
{
    // 处理序列
    return *beg;  // 返回序列中一个元素的引用
}
```
此例中我们通知编译器fcn的返回类型与解引用beg参数的结果类型相同。解引用运算符返回一个左值，因此通过decltype推断的类型为beg表示的元素的类型的引用。因此，如果对一个string序列调用fcn,返回类型将是string&。如果是int序列，则返回类型是int&。

##### 进行类型转换的标准库模板类
有时我们无法直接获得所需要的类型。例如，我们可能希望编写一个类似fcn的函数，但返回一个元素的值而非引用。在编写这个函数的过程中，我们面临一个问题:对于传递参数的类型，我们几乎一无所知。在此函数中，我们知道唯一可以使用的操作是迭代器操作，而所有迭代器操作都不会生成元素，只能生成元素的引用。<br>
为了获得元素类型，我们可以使用标准库的**类型转换**(type transformation)模板。这些模板定义在头文件type_traits中。这个头文件中的类通常用于所谓模板元程序设计。
类型转换模板在普通编程中也很有用。<br>
在本例中，我们可以使用remove_reference来获得元素类型。remove_reference模板有一个模板类型参数和一个名为type的(public)类型成员。如果我们用一个引用类型实例化remove_reference，则type将表示被引用的类型。例如，如果我们实例化remove_reference<int &>, 则type成员将是int。类似的，如果我们实例化remove_reference<string &>, 则type成员将是string, 依此类推。更一般的，给定一个迭代器beg:
```C++
remove_reference<decltype(*beg)>::type
```
将获得beg引用的元素的类型：decltype(*beg)返回元素类型的引用类型。remove_reference::type脱去引用，剩下元素类型本身。组合使用remove_reference、尾置返回及decltype,我们就可以在函数中返回元素值的拷贝:
```C++
  // 为了使用模板参数的成员，必须用typename
template <typename It>
auto fcn2(It beg, It end) -> typename remove_reference<decltype(*beg)>::type
{
    return *beg;    // 返回序列中一个元素的拷贝
}
```
type 是一个类的成员，该类依赖于一个模板参数。因此，我们必须在返回类型的声明中使用typename来告知编译器，type表示一个参数:

<table>
    <tr>
        <th>对Mod<T>,其中Mod为</th>
        <th>若T为</th>
        <th>则Mod<T>::type为</th>
    </tr>
    <tr>
        <td>remove_reference</td>
        <td>X&或X&&<br>否则</td>
        <td>X<br>T</td>
    </tr>
    <tr>
        <td>add_const</td>
        <td>X&、const X 或函数<br>否则</td>
        <td>T<br>const T</td>
    </tr>
    <tr>
        <td>add_lvalue_reference</td>
        <td>X&<br>X&&<br>否则</td>
        <td>T<br>X&<br>T&</td>
    </tr>
    <tr>
        <td>add_rvalue_reference</td>
        <td>X&或X&&<br>否则</td>
        <td>T<br>T&&</td>
    </tr>
    <tr>
        <td>remove_pointer</td>
        <td>X&或X&&<br>否则</td>
        <td>X<br>T</td>
    </tr>
    <tr>
        <td>add_pointer</td>
        <td>X&或X&&<br>否则</td>
        <td>X*<br>T*</td>
    </tr>
</table>
每个模板都有一个名为type的public成员，表示一个类型。此类型与模板自身的模板类型参数相关，其关系如模板名所示。如果不可能转换模板参数，则type成员就是模板参数类型本身。例如，如果T是一个指针类型，则remove_pointer<T>::type是T指向的类型。如果T不是一个指针，则无须进行任何转换，从而type具有T相同的类型。

##### 函数指针和实参推断
当用一个函数模板初始化一个函数指针或为一个函数指针赋值时，编译器使用指针的类型来推断模板实参。假定我们有一个函数指针,它指向函数返回int,接受两个参数，每个参数都是指向const int的引用我们可以使用该指针指向compare的一个实例:
```C++
template <typename T>int compare(const T&, const T&);
int (*pf1)(const int &, const int &) = compare;
```
pf1中的参数类型决定了T的模板实参类型。在本例中，T的模板实参类型为int。指针pf1指向compare的int版本实例。如果不能从函数指针类型确定模板实参，则产生错误:
```C++
void func(int (*)(const string &, const string &));
void func(int (*)(const int&, const int&));
func(compare); // 错误： 使用compare的哪个实例
```
以上代码，通过func的参数类型无法确定模板实参唯一类型。对func调用可以实例化接受int的compare版本，也可以接受string版本。由于不能确定func的实参唯一实例化版本，此调用将编译失败。我们可以通过使用显式模板实参消除func调用的歧义:
```C++
func(compare<int>); //传递 compare(const int&, const int&);
```
此表达式调用func版本接受一个函数指针,该调用指向的函数接受两个const int& 参数。

- 参数是一个函数模板实例的地址时，程序上下文必须满足: 对每个模板参数，能唯一确定其类型或值

#### 模板实参推断和引用
为了理解如何从函数调用进行类型推断，考虑下面的例子:
```C++
template <typename T> void f(T &p);
```
函数参数p是一个模板类型参数T的引用，非常重要记住两点：编译器会应用整行的引用绑定规则;const是底层的，不是顶层的。

##### 从左值引用函数参数推断类型
当一个函数参数是模板类型参数的一个普通(左值)引用时(即，形如T&)，绑定规则告诉我们，只能传递给它一个左值(如，一个变量或一个返回引用类型的表达式)。实参可以是const类型，也可以不是。如果实参是const的，则T将被推断为const类型:
```C++
template <typename T> void f1(T&); // 实参必须是一个左值
f1(i);  // i是一个int;模板参数类型T是int
f1(ci); // ci是一个const int;模板参数T是const int
f1(5);  // 错误：传递给一个&参数的实参必须是一个左值
```
如果一个函数参数的类型是const T&, 正常绑定规则告诉我们可以传递给它任何类型的实参---- 一个对象(const或非const)、一个临时对象或是一个字面常量值。当函数参数本身是const时，T的类型推断结果不会是一个const类型。const已经是函数参数类型的一部分；因此，它不会是模板参数类型的一部分:
```C++
template <typename T> void f2(const T&);  // 可以接受一个右值
// f2中的参数是const &;实参中的const是无关的
// 在每个调用中，f2的函数参数都被推断为const int&
f2(i);      // i是一个int; 模板参数T是int
f2(ci);     // ci是一个const int,但模板参数T是int
f2(5);      // 一个const &参数可以绑定到一个右值;T是int
```

##### 从右值引用函数参数推断类型
当一个函数参数是一个右值引用(即，形如T&&)时，正常绑定规则告诉我们可以传递给它一个右值。当我们这样做时，类型推断过程类似普通左值引用函数参数的推断过程。推断出的T的类型是该右值实参的类型：
```C++
template <typename T> void f3(T&&)；
f3(42);     // 实参是一个int类型的右值；模板参数T是int
```

##### 引用折叠和右值引用参数
通常我们不能将一个右值引用绑定到一个左值上。但是C++语言在正常绑定规则之外定义了两个例外规则，允许这种绑定。<br>
第一个例外规则影响右值引用参数的推断如何进行。当我们将一个左值传递给函数的右值引用参数，且此右值引用指向模板类型参数(如T&&)时，编译器推断模板类型参数为实参的左值引用类型。因此，当我们调用f3(i)时，编译器推断T类型为int&,而非int。<br>
T 被推断为int &看起来好像意味着f3的函数参数应该是一个类型int&的右值引用。通常，我们不能(直接)定义一个引用的引用。但是，通过类型别名或通过模板类型参数间接定义是可以的。<br>
在这种情况下，我们可以使用第二个例外绑定规则：如果我们间接创建一个引用的引用，则这些引用形成了“折叠”。在所有情况下，引用会折叠成一个普通的左值引用类型。C++11标准中，折叠规则扩展到右值引用。只在一种特殊情况下引用会折叠成右值引用;右值引用的右值引用。即，对于一个给定类型X：
- X& &、X& &&和X&& & 都折叠成类型X&
- 类型X&& && 折叠成X&&

如果将引用折叠规则和右值引用的特殊类型推断规则组合在一起，则意味这我们可以对一个左值调用f3。当我们将一个左值传递给f3的函数参数时，编译器推断T为一个左值引用类型:
```C++
f3(i);  //实参是一个左值：模板参数T是int &
f3(ci); //实参是一个左值: 模板参数T是一个const int &
```
当一个模板参数T被推断为引用类型时，折叠规则告诉我们函数参数T&&折叠为一个左值引用类型。例如，f3(i)的实例化结果可能像下面这样:
```C++
  // 无效代码，只是用于演示目的
void f3<int&>(int & &&);   // 当T是int &时， 函数参数为int& &&
```
f3的函数参数是T&& 且T是int&, 因此T&&是int& &&,会折叠成int &。因此，即使f3的函数参数形式是一个右值引用(即,T&&), 此调用也会用一个左值引用类型(即，int&)实例化f3:
```C++
void f3<int&>(int &);   // 当T是int&时，函数参数折叠为int&
```
这两个规则导致了两个重要结果:
- 如果一个函数参数是一个指向模板类型参数的右值引用(如，T&&)，则它可以被绑定到一个左值；且
- 如果实参是一个左值，则推断出的模板实参类型将是一个左值引用，且函数参数将被实例化为一个左值引用参数(T&)

这两个规则暗示，我们可以将任意类型实参传递给T&&类型的函数参数。对于这种类型的参数，可以传递给它右值，而如我们刚刚看到，也可以传递给它左值。

- 如果一个函数参数是指向模板参数类型的右值引用(如，T&&)，则可以传递给它任意类型的实参。如果将一个左值传递给这样的参数，则函数参数被实例化为一个普通的左值引用(T&)。

##### 编写接受右值引用参数的模板函数
模板参数可以推断为一个引用类型，这一特性对模板内的代码可能有令人惊讶的影响:
```C++
template <typename T> void f3(T&& val)
{
    T t=val; //拷贝还是绑定一个引用？
    t = fcn(t);  // 赋值只改变t还是即改变t又改变val?
}
```
当我们对一个右值调用f3时，例如字面常量42，T为int。在此情况下，局部变量t的类型为int，且通过拷贝参数val的值被初始化。当我们对t赋值时，参数val保持不变。<br>
另一方面，当我们对一个左值i调用f3时，则T为int&。当我们定义并初始化局部变量t时，赋予它类型int&。因此，对t的初始化将其绑定到val。当我们对t赋值时，也同时改变了val的值。<br>
在实际中，右值引用通常用于两种情况：模板转发其实参或模板被重载。使用右值引用的函数模板进行重载:
```C++
template <typename T> void f(T&&);          // 绑定到非const右值
template <typename T> void f(const T&);     // 左值和const 右值
```
与非模板函数一样，第一个版本将绑定到可修改的右值，而第二个将绑定到左值或const右值。

#### 理解std::move
标准库move函数是使用右值引用的模板的一个例子。研究move是如何工作的可以帮助我们巩固对模板的理解和使用。<br>
虽然不能直接将一个右值引用绑定到一个左值上，但可以用move获得一个绑定到左值上的右值引用。move本质可以接受任何类型的实参。

##### std::move如何定义
标准库定义的move：
```C++
// 在返回类型和类型转换中用到typename
template <typename T>
typename remove_reference<T>::type&& move(T&& t)
{
    return static_cast<typename remove_reference<T>::type&&>(t);
}
```
move函数参数T&&是一个指向模板类型参数的右值引用。通过引用折叠，此参数可以与任何类型的实参匹配。特别是，我们既可以传递给move一个左值，也可以传递给它一个右值:
```C++
std::string s1("hi!"), s2;
s2 = std::move(std::string("bye!"));    //正确，从一个右值移动数据
s2 = std::move(s1);                     //正确: 但在赋值后，s1的值是不确定的
```
##### std::move 如何工作的
在第一个赋值中，传递给move的实参是string的构造函数的右值结果 ---- string("bye!")。如我们已经见到过的，当向一个右值引用函数传递一个右值时，有实参推断出的类型为被引用的类型。因此，在std::move(std::string("bye!"))中:

- 推断出T的类型为std::string。
- 因此，remove_reference用std::string进行实例化。
- remove_reference<std::string>的type成员是std::string。
- move的返回类型是std::string&&。
- move的函数参数t的类型是std::string&&。

这个调用实例化move<string>， 即函数:
```C++
std::string&& std::move(std::string&& t);
```
函数体返回static_cast<std::string&&>(t)。t的类型已经是std::string&&, 于是类型转换什么都不做。<br>
考虑第二个赋值，std::move(s1)。在此调用中，传递给move的实参是一个左值：

- 推断出T的类型为std::string&(std::string的引用，而非普通std::string)。
- remove_reference用std::string&实例化
- move的返回类型仍然是std::string&&。
- move的函数参数t实例化为std::string& &&, 会折叠为std::string&。

这个调用实例化move<std::string&>，即:
```C++
std::string& move(std::string &t);
```
这正是我们所寻求的---- 我们希望将一个右值引用绑定到一个左值。这个实例的函数体返回static_cast<std::string&&>(t)。在此情况下，t的类型为std::string&,static_cast将其转换为std::string&&。

##### 从一个左值static_cast到一个右值引用是允许的
通常情况下，static_cast只能用于其他合法的类型转换。但是 这里又有一条针对右值引用的特许规则: 虽然不能隐式地将一个左值转换为右值引用，但我们可以用static_cast显式地将一个左值转换为一个右值引用。<br>
对于操作右值引用的代码来说，将一个右值引用绑定到一个左值的特性允许他们截断左值。有时候，例如在我们的StrVec类的reallocate函数中，我们知道截断一个左值是安全的。一方面，通过允许进行这样的转换，C++语言认可了这种用法。另一方面，通过强制使用static_cast，C++语言试图阻止我们意外地进行转换。<br>
最后，虽然我们可以直接编写这种类型转换代码，但使用标准库move函数是容易得多地方式。而且，统一使用std::move使得我们在程序中查找潜在的截断左值的代码变得很容易。

#### 转发
某些函数需要将其一个或多个实参连同类型不变地转发给其他函数。在此情况下，我们需要保持被转发实参地所有性质，包括实参类型是否是const的以及实参是左值还是右值。<br>
作为一个例子，我们将编写一个函数，它接受一个可调用表达式和两个额外实参。我们的函数将调用给定的可调用对象，将两个额外参数逆序传递给它。下面是我们的翻转函数的初步模样：
```C++
// 接受一个可调用对象和另外两个参数的模板
// 对"翻转"的参数调用给定的可调用对象
// flib1是一个不完整的实现：顶层const和引用丢失了
template <typename F, typename T1, typename T2>
void flip1(F f, T1 t1, T2 t2)
{
    f(t2, t1);
}
```
这个函数一般情况下工作得很好，但当我们希望用它调用一个接受引用参数的函数时就会出现问题：
```C++
void f(int v1, int &v2)
{
    const <<v1 << " " << ++v2 << endl;
}
```
在这段代码中，f改变了绑定到v2的实参的值。但是，如果我们通过flib1调用f,f所作的改变就不会影响实参:
```C++
f(42, i);           // f改变了实参i
flib1(f, j, 42);    // 通过flip1调用f不会改变j
```
问题在于j被传递给flip1的参数t1。此参数是一个普通、非引用的类型int,而非int&。因此，这个flip1调用会实例化为
```C++
void flip1(void(*fcn)(int, int &), int t1, int t2);
```
j的值被拷贝到t1中。f中的引用参数被绑定到t1,而非j,从而其改变不会影响j。

##### 定义能保持类型信息的函数参数
为了通过翻转函数传递一个引用，我们需要重写函数，使其参数能保持给定实参的"左值性"。更进一步，可以想到我们也希望保持参数的const属性。<br>
通过将一个函数参数定义为一个指向模板类型参数的右值引用，我们可以保持其对应实参的所有类型消息。而使用引用参数(无论是左值还是右值)使得我们可以保持const属性，因为在引用类型中的const是底层的。如果我们将函数参数定义为T1&&和T2&&，通过引用折叠就可以保持翻转实参的左值/右值属性:
```C++
template <typename F, typename T1, typename T2>
void flip2(F f, T1 &&t1, T2 &&t2)
{
    f(t2, t1);
}
```
与较早版本一样，如果我们调用flip2（f,j,42),将传递给参数t1一个左值j。但是，在flip2中，推断出的T1的类型为int&,这意味着t1的类型会折叠为int&。由于是引用类型，t1被绑定到j上。当flip2调用f时，f中的引用参数v2被绑定到t1,也就是被绑定到j。当f递增v2时，它也同时改变了j的值。

- 如果一个函数参数是指向模板类型参数的右值引用(如T&&)，它对应的实参const属性和左值/右值属性将得到保持。

这个版本的flip2解决了一半问题。它对于接受一个左值引用的函数工作得很好，但不能用于接受右值引用参数的函数。例如:
```C++
void g(int &&i, int &j)
{
    std::cout << i <<" " << j <<std::endl;
}
```
如果我们试图通过flip2调用g,则参数t2将被传递给g的右值引用参数。即使我们传递一个右值给flip2:
```C++
flip2(g,i,42);  //错误: 不能从一个左值实例化int&&
```
传递给g的将是flip2中名为t2的参数。函数参数与其他任何变量一样，都是左值表达式。因此flip2中对g的调用将传递给g的右值引用参数一个左值。

##### 在调用中使用std::forward保持类型信息
我们可以使用一个名为forward的C++11标准库设施来传递flip2的参数，它能保持原始实参的类型。类似move,forward定义在头文件utility中。与move不同,forward必须通过显式模板实参来调用。forward返回该显式实参类型的右值引用。即，forward<T>的返回类型是T&&。<br>
通常情况下，我们使用forward传递那些定义为模板类型参数的右值引用的函数参数。通过其返回类型上的引用折叠，forward可以保持给定实参的左值/右值属性:
```C++
template <typename Type> intermediary(Type &&arg)
{
    finalFcn(std::forward<Type>(arg));
}
```
本例中我们使用Type作为forward的显式模板实参类型，它是从arg推断出来的。由于arg是一个模板类型参数的右值引用，Type将表示传递给arg的实参的所有类型信息。如果实参是一个右值，则Type是一个普通（非引用) 类型，forward<Type>将返回Type&&。如果实参是一个左值，则通过引用折叠,Type本身是一个左值引用类型。在此情况下，返回类型是一个指向左值引用类型的右值引用。再次对forward<Type>的返回类型进行引用折叠，将返回一个左值引用类型。

- 当用于一个指向替参数类型的右值引用函数参数(T&&)时，forward会保持实参类型的所有细节。

使用forward,我们可以再次重写翻转函数:
```C++
template <typename F, typename T1, typename T2>
void flip(F f, T1 &&t1, T2 &&t2)
{
    f(std::forward<T2>(t2), std::forward<T1>)(t1);
}
```
如果我们调用flip(g, i, 42)，i将以int &类型传递给g, 42将以int&&类型传递给g。

### 重载与模板
函数模板可以被另一个模板或一个普通非模板函数重载。与往常一样，名字相同的函数必须具有不同数量或类型的参数。<br>
如果涉及函数模板，则函数匹配规则会在以下几方面受到影响:
- 对于一个调用，其候选函数包括所有模板实参推断成功的函数模板实例。
- 候选的函数模板总是可行的，因为模板实参推断会排除任何不可行的模板。
- 与往常一样，可行函数(模板与非模板)按类型转换(如果对此调用需要的话)来排序。当然，可以用于函数模板调用的类型转换是非常有限的。
- 如果恰有一个函数提供比任何其他函数都更好的匹配，则选择此函数。但是，如果有多个函数提供同样好的匹配，则:
1. 如果同样好的函数中只有一个是非模板函数，则选择此函数。
2. 如果同样好的函数中没有非模板函数，而有多个函数模板，且其中一个模板比其他模板更特例化，则选择此模板。
3. 否则，此调用有歧义。

##### 编写重载函数
作为一个例子，我们将构造一组函数，它们在调试中可能很有用。我们将这些调试函数命名为debug_rep,每个函数都返回一个给定对象的std::string表示。我们首先编写此函数最通用版本，将它定义为一个模板，接受一个const对象的引用:
```C++
// 打印任何我们不能处理的类型
template <typename T> std::string debug_rep(const T &t)
{
    std::ostingstream ret;
    ret << t;               // 使用T的输出运算符打印t的一个表示形式
    return ret.str();       // 
}
```
接下来我们定义打印指针的debug_rep版本:
```c++
// 打印指针的值，后跟指针指向的对象。此函数不能用于char *;
template <typename T> std::string debug_rep(T *p)
{
    std::ostingstream ret;
    ret << "pointer: " << p;     // 打印指针本身的值
    if (p)
        ret << " " << debug_rep(*p);  // 打印p指向的值
    else 
        ret << " null pointer"; // 或指出p为空
    return ret.str();  // 返回ret绑定的string的一个副本
}
```
此版本生成一个string,包含指针本身的值和调用debug_rep获得的指针指向的值。注意此函数不能用于打印字符指针，因为IO库为char *值定义了一个<<版本，此版本假定指针表示一个空字符结尾的字符数组，并打印数组的内容而非地址值。<br>
可以这样使用这些函数:
```C++
std::string s("hi");
std::cout << debug_rep(s) << std::endl;
```
上面的调用只有第一个版本的debug_rep是可行的。 第二个debug_rep版本要求一个指针参数，但在此调用中我们传递的是一个非指针对象。因此编译器无法从一个非指针实参实例化一个期望指针类型参数的函数模板，因此实参推断失败。由于只有一个可行函数，所以此函数被调用。<br>
如果我们调用debug_rep 传入一个指针:
```C++
std::cout << debug_rep(&s) << std::endl;
```
两个函数都生成可行的实例：
- debug_rep(const std::string *&), 由第一个版本的debug_rep实例化而来，T被绑定到std::string *。
- debug_rep(const std::string *), 由第二个版本的debug_rep实例化而来，T被绑定到const std::string。

正常函数匹配无法区分这两个函数。我们可能觉得这个调用将是有歧义的。但是，根据重载函数模板的特殊规则，此调用被解析为debug_rep(T*),即，更特例化的版本。<br>
设计这条规则原因:没有它，将无法对一个const的指针调用指针版本的debug_rep。问题在于模板debug_rep(const T&)本质上可以用于任何类型，包括指针类型。此模板比debug_rep(T*)更通用，后者只能用于指针类型。没有这条规则，传递const的指针的调用永远是有歧义的。

##### 非模板和模板重载
定义一个普通非模板版本的debug_rep打印双引号包围的string：
```C++
std::string debug_rep(const std::string &s)
{
    return '"' + s + '"';
}
```
我们对一个string调用debug_rep时:
```C++
std::string s("hi");
std::cout << debug_rep(s) << std::endl; 
```
有两个同样好的可行函数:
- debug_rep<std::string>(const std::string &), 第一个模板，T被绑定到string*。
- debug_rep(const std::string &), 普通非模板函数.

本例中，两个函数具有相同的参数列表，因此显然两者提供同样好的匹配。但是，编译器会选择非模板版本。当存在多个同样好的函数模板时，编译器选择最特例化的版本，出于相同原因，一个非模板函数比一个函数模板更好。

##### 重载模板和类型转换
还有一种情况我们到目前为止尚未讨论：C风格字符串指针和字符串字面常量。现在有了一个接受string的debug_rep版本，我们可能期望一个传递字符串的调用会匹配这个版本。但是，考虑这个调用:
```C++
std::cout << debug_rep("hi world!") << std::endl;
```
本例中所有三个debug_rep版本都是可行的:
- debug_rep(const T&), T被绑到char[10]。
- debug_rep(T*), T被绑到const char。
- debug_rep(const std::string &), 要求从const char*到std::string的类型转换。

对给定实参来说，两个模板都提供精确匹配----第二个模板需要进行一次数组到指针的转换，对于函数匹配来说，这种转换被认为是精确匹配。非模板版本是可行的，但需要进行一次用户定义的类型转换，因此它没有精确匹配那么好，所以两个模板成为可能调用的函数。与之前一样，T*版本更加特例化，编译器会选择它。<br>
如果我们希望将字符指针按string处理，可以定义另外两个非模板重载版本:
```C++
// 将字符串指针转换为string, 并调用string版本的debug_reg
std::string debug_rep(char *p)
{
    return debug_rep(std::string(p));
}

std::string debug_rep(const char *p)
{
    return debug_rep(std::string(p));
}
```

##### 缺少声明可能导致程序行为异常
值得注意的是，为了使char *版本的debug_rep正确工作，在定义此版本时，debug_rep(const std::string&)的声明必须在作用域中。否则，就可能调用错误的debug_rep版本:
```C++
template <typename T>std::string debug_rep(const T &t);
template <typename T>std::string debug_rep(T *p);
// 为了使debug_rep(char *)的定义正确工作，下面的声明必须在作用域中
std::string debug_rep(const std::string &);
std::string debug_rep(char *p)
{
    // 如果接受一个const string &的版本声明不在作用域中
    // 返回语句将调用debug_rep(const T&)的T实例化为string的版本
    return debug_rep(std::string(p));
}
```
如果使用了一个忘记声明的函数，代码将编译失败。但对于重载函数模板的函数而言，则不是这样。如果编译器可以从模板实例化出于调用匹配的版本，则缺少的声明就不重要了。在本例中，如果忘记了声明接受std::string参数的debug_rep版本，编译器会默认实例化const T&的模板版本。

- 在定义任何函数之前，记得声明所有重载的函数版本。这样就不必担心编译器由于未遇到你希望调用的函数而实例化一个并非你所需的版本。

### 可变参数模板
一个**可变参数模板**(variadic template) 就是一个接受可变数目参数的模板函数或模板类。可变数目的参数被称为**参数包**(parameter packet)。存在两种参数包:**模板参数包**(template parameter packet)，表示零个或多个模板参数:**函数参数包**(function parameter packet),表示零个或多个函数参数。<br>
我们用一个省略号来指出一个模板参数或函数参数表示一个包。在一个模板参数列表中，class...或typename... 指出接下来的参数表示零个或多个类型的列表:一个类型名后面跟一个省略号表示零个或多个给定类型的非类型参数列表。在函数参数列表中，如果一个参数的类型是一个模板参数包，则此参数也是一个函数参数包。例如:
```C++
// Args 是一个模板参数包；rest是一个函数参数包
// Args 表示零个或多个模板类型参数
// rest 表示零个或多个函数参数
template <typename T, typename... Args>
void foo(const T &t, const Args& ... rest);
```
声明foo是一个可变参数函数模板，它有一个名为T的类型参数，和一个名为Args的模板参数包。这个包表示零个或多个额外的类型参数。foo的函数参数列表包含一个const &类型的参数，指向T的类型，还包含一个名为rest的函数参数包，此包表示零个或多个函数参数。<br>
与往常一样，编译器从函数的实参推断模板参数类型。对于一个可变参数模板，编译器还会推断包中参数的数目。例如，给定下面的调用:
```C++
int i = 0;double d= 3.14; string s = "how now brown cow";
foo(i, s, 42, d);   // 包中有三个参数
foo(s, 42, "hi");   // 包中有两个参数
foo(d, s);          // 包中有一个参数
foo("hi");          // 空包
```
编译器会为foo实例化出四个不同的版本:
```C++
void foo(const int&, const std::string &, const int &, const double &);
void foo(const std::string &, const int &, const char [3]&);
void foo(const double &, const string &);
void foo(const char[3]&);
```
每个实例中，T的类型都是从第一个实参的类型推断出来的。剩下的实参提供函数额外实参的数目和类型。

##### sizeof...运算符
我们需要知道包中有多少元素时，可以使用sizeof...运算符。类似sizeof, sizeof...也返回一个常量表达式，而且不会对其实参求值:
```C++
template <typename ...Args> void g(Args ... args)
{
    std::cout << sizeof...(Args) << std::endl;  // 类型参数的数目
    std::cout << sizeof...(args) << std::endl;  // 函数参数的数目
}
```

#### 编写可变参数函数模板
我们可以使用一个initializer_list 来定义一个可接受可变数目实参的函数。但是，所有实参必须具有相同的类型(或它们的类型可以转换为同一个公共类型)。当我们既不知道想要处理的实参的数目也不知道它们的类型时，可变参数函数是很有用的。作为一个例子，我们将定义一个函数，它类似较早的error_msg函数，差别仅在于新函数实参的类型也是可变的。我们首先定义一个名为print的函数，它在一个给定流上打印给定实参列表的内容。<br>
可变参数函数通常是递归的。第一步调用处理包中的第一个实参，然后用剩余实参调用自身。我们的print函数也是这样的模式，每次递归调用将第二个实参打印到第一个实参表示的流中。为了终止递归，我们还需要定义一个非可变参数的print函数，它接受一个流和一个对象:
```C++
// 用来终止递归并打印最后一个元素的函数
// 此函数必须在可变参数版本的print定义之前声明
template <typename T>
std::ostream &print(std::ostream &os, const T &t)
{
    return os << t; // 包中最后一个元素之后不打印分隔符
}
// 包中除了最后一个元素之外的其他元素都会调用这个版本的print
template <typename T, typename... Args>
std::ostream &print(ostream &os, const T &t, const Args&... rest)
{
    os << t << ", ";            // 打印第一个实参 
    return print(os, rest...);  // 递归调用，打印其他实参
}
```
第一个版本的print负责终止递归并打印初始调用中的最后一个实参。第二个版本的print是可变参数版本，它打印绑定到t的实参，并调用自身来打印函数参数包中的剩余值。这段程序的关键部分是可变参数函数中对print的调用:
```C++
return print(os, reset...);     // 递归调用，打印其他实参
```
我们的可变参数版本的print函数接受三个参数，一个ostream&, 一个const T&和一个参数包。而此调用只传递了两个实参。其结果是rest中的第一个实参被绑定到t，剩余实参形成下一个print调用的参数包。因此，每个调用中，包中的每一个实参被移除，成为绑定到t的实参。即，给定:
```C++
print(std::cout, i, s, 42);   // 包中有两个参数
```
递归执行如下:
<table>
    <tr>
        <th>调用</th>
        <th>t</th>
        <th>rest...</th>
    </tr>
    <tr>
        <td>print(std::cout, i, s, 42)</td>
        <td>i</td>
        <td>s, 42</td>
    </tr>
    <tr>
        <td>print(std::cout, s, 42)</td>
        <td>i</td>
        <td>s, 42</td>
    </tr>
    <tr>
        <td>print(std::cout, 42)</td>
        <td>call 非可变参数print</td>
        <td></td>
    </tr>
</table>
前两个调用只能与可变参数版本的print匹配，非可变参数版本是不可行的，因为这俩个调用分别传递四个和三个实参，而非可变参数print只接受两个实参。<br>
对于最后一次递归调用print(cout, 42), 两个版本都是可行的。这个调用传递两个实参，第一个实参类型为ostream &。因此，可变参数版本的print可以实例化为只接受两个参数:一个是ostream&参数，另一个是const T&参数。两个函数提供同样好的匹配。但是，非可变参数模板比可变参数模板更特例化，因此编译器选择非可变参数版本。

- 当定义可变参数版本的print时，非可变参数版本的声明必须在作用域中。否则，可变参数版本会无线递归。

#### 包扩展
对于一个参数包，除了获取其大小外，我们能对它做的唯一事情就是**扩展**(expand)它。扩展一个包时，我们还要提供用于每个扩展元素的**模式**(pattern)。扩展一个包就是将它分解为构成的元素，对每个元素应用模式，获得扩展后的列表。我们通过在模式右边放一个省略号(...)来触发扩展操作。<br>
我们的print函数包含两个扩展:
```C++
template <typename T, typename... Args>
std::ostream &
print(ostream &os, const T &t, const Args&... rest)  // 扩展Args
{
    os << t << ", ";            
    return print(os, rest...);  // 扩展rest
}
```
第一个扩展操作扩展模板参数包，为print生成函数参数列表。第二个扩展操作出现在对print的调用中。此模式为print调用生成实参列表。<br>
对Args的扩展中，编译器将模式const Args&应用到模板参数包Args中的每个元素。因此，此模式的扩展结果是一个逗号分隔的零个或多个类型的列表，每个类型都形如const type &。例如:
```C++
print (std::cout, i, s, 42); // 包中有两个参数
```
最后两个实参的类型和模式一起确定了尾置参数的类型。此调用被实例化为:
```C++
std::ostream &
print(std::ostream &, const int &, const std::string &, const int &);
```
第二个扩展发生在对print的(递归)调用中。在此情况下，模式是函数参数包的名字(即rest)。此模式扩展出一个由包中元素组成的、逗号分隔的列表。因此，这个调用等价:
```C++
print(os, s, 42);
```

##### 理解包扩展
print中的函数参数包扩展仅仅将包扩展为其构成元素，C++语言还允许更复杂的扩展模式。