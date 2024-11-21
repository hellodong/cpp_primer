
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
```C++
compare("hi","mom");
```
编译器会使用字面常量的大小来替代N和M，从而实例化模板。记住，编译器会在一个字符串字面常量的末尾插入一个空字符为终结符，因此编译器会实例化如下版本：
```C++
int compare(const char (&p1)[3], const char (&p2)[4]);
```
一个非类型参数可以是一个整型，或者是一个指向对象或函数类型的指针或左值引用。绑定到非类型整型参数的实参必须是一个常量表达式