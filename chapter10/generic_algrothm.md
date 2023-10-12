####  back_inserter
**插入迭代器**是一种向容器中添加元素的迭代器。当我们通过一个插入迭代器赋值时，一个赋值号右侧值相等的元素被添加到容器中。

## 定制操作
很多算法还会比较输入序列的元素。标准库为这些算法提供了额外的版本，允许我们提供自定义操作来替代默认运算符.
### 介绍lambda
表示一个可调用的代码单元。可以理解一个未命名的内敛函数。一个lambda表达式如下:
```shell
[capture list] (parameter list) -> return type {function body}
```
- **capture list** 一个lambda 所在函数的中定义的局部变量
- 必须使用尾置返回 指定返回类型

可以忽略参数列表和返回类型，但必须包含捕获列表和函数体
```c
auto f=[] {return 0;};
```
lambda调用方式跟普通函数调用方式相同，都是使用调用运算符：
```c
cout << f() << endl; // print 0
```
忽略返回类型,lambda根据函数体中的代码推断出返回类型---> lambda 的函数体包含任何单一return 语句之外的内容，且未指定返回类型，则返回void。
#### 向lambda传递参数
实参与形参的类型必须匹配。但与普通函数不同，lambda不能有默认函数。因此调用的实参数目永远与形参数目相等
```c
[] (const string &a, const string &b) { return a.size() < b.size();}
```
#### 捕获变量
lambda 以一对[]开始，我们在其中提供一个以逗号分隔的名字列表，这些名字都是它所在函数中定义的。
```c
[sz] (const string &a) {return a.size() < sz}
```
我们可以使用for_each算法:
```c
for_each(wc, words.end(),
    [](const string &s) {cout << s << " ";});
```
捕获列表为空，因为我们只对lambda所在函数中定义的(非static)变量使用捕获列表。一个lambda可以直接使用定义在函数之外的名字。
此例中使用cout,但是cout 并不在捕获列表中，而是定义在头文件iostream中，因此只要for_each出现的作用域包含了头文件iostream,我们lambda就可以使用它.

#### 值捕获
与参数不同，被捕获的变量的值是在lambda创建时copy， 不是调用时copy.
```c
void fcnl()
{
    size_t v1 = 42;
    //将v1变量copy到名为f的可调用对象
    auto f = [v1] {return v1;};
    v1 = 0;
    std::cout << f(); // 输出为42， f保存了我们创建它时v1的拷贝
}
```
#### 引用捕获
```c++
void func2()
{
    size_t v1 = 42; // 局部变量
    //对象f2包含v1的引用
    auto f2 = [&v1]{return v1;};
    v1 = 0;
    std::cout << f2() << std::endl;// f2 输出为0; f2 保存了v1的引用
}
```
v1之前 **&** 指出v1应该以引用方式捕获。我们采用引用方式捕获一个变量，就必须确保被引用的对象在lambda执行的时候是存在的。我们可以从一个函数返回lambda。如果函数返回一个lambda,则函数不能返回一个局部变量的引用类似，lambda也不能包含引用捕获。

### 参数绑定
传递一个长度参数问题，使用一个新的名为**bind**的标准函数，定义在*functional*头文件中.调用bind的一般形式为:
```c
auto newCallable = std::bind(callable, arg_list)
```
- *nesCallable*, 一个可调用对象，理解成函数就好
- *arg_list*, 逗号分隔的参数列表，对应给定的callable的参数
- _1,_2 为**arg_list**传入参数，其在std::placeholders 命名空间: std::placeholders::_1, std::placeholders::_2
```cxx
int check_size(const std::string &str, int sz)
{
    return str.size() > sz;
}

auto wc = std::find_if(words.begin(), words.end(), std::bind(check_size, std::placeholders::_1, 4));
```
##### 绑定引用参数
如果我们希望传递给**bind**一个对象而不拷贝它，就必须使用**ref**函数， 其定义在functional头文件中
```CPP
std::ostream &print(std::ostream &os, std::string &str, char c)
{
    os << str << c ;
}

for_each(words.begin(), words.end(), std::bind(print, std::ref(std::cout), std::placeholders::_1, ' '));
```
函数*ref* 返回一个对象，包含给定的引用，此对象是可以拷贝的。还有一个**cref**, 生成一个保存const引用的类, 也定义在functional头文件中。

