
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
BlobPtr<T> BlobPtr<T>::operator++(int)
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
类模板与另一个(类或函数)模板间友好关系的最常见形式是建立对应实例及其友元间的友好关系。例如Blob类应该将BlobPtr类