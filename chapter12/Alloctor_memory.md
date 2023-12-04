## Allocator memory

[TOC]

我们编写的程序所使用的对象都有着严格定义的生存期。全局对象在启动时分配，程序结束时销毁。局部对象，我们进入定义所在程序块时被创建，离开快时销毁。局部static对象在第一次使用前分配，程序结束时销毁。

动态分配的对象在生存期与它们在哪里创建是无关的，只有显示释放时，这些对象才会销毁。为了更安全地使用动态对象，标准库定义了两个智能指针。当一个对象应该被释放时，指向它的智能指针可以确保自动释放它。

静态内存用来保存局部static对象，类static数据成员以及定义在任何函数之外的变量。栈内存用来保存定义在函数内的非static对象。分配在静态或栈内存中的对象由编译器自动创建销毁。

除了静态内存和栈内存，每个程序还拥有一个内存池。这部分内存被称作自由空间(free store)或堆(heap)

### 动态内存与智能指针
动态内存的管理是通过一对运算符来完成：**new**,在动态内存中为对象分配空间并返回一个指向该对象的指针；**delete**，接受一个动态对象的指针，销毁该对象，并释放与之关联内存。

为了更容易(同时更安全)使用动态内存，新标准库(C++11)提供了两种智能指针类型。**shared_ptr**允许多个指针指向同一个对象；**unique_ptr** "独占"所指向的对象。**weak_ptr**伴随类，一种弱引用，指向shared_ptr所管理对象。这三种类型都定义在memory头文件中。

#### shared_ptr类

智能指针也是模板,当我们创建一个智能指针时，必须提供额外的信息----指针可以指向的类型，我们在尖括号内给出类型：
```C++
shared_ptr<string> p1;
shared_ptr<list<string>> p2;
```
默认初始化的智能指针保存着一个空指针。解引用一个智能指针返回它指向的对象：
```C++
// 如果p1不为空，检查它是否指向一个空string
if (p1 && p1.empty())
{
    *p1 = "hi"; // 如果p1指向空string, 解引用P1, 将一个新值赋给p1
}
```
[代码实现](./shared_ptr/src/shared_ptr.cpp)

shared_ptr和unique_ptr都支持的操作列表:
<table>
    <tr>
        <th colspan="2">shared_ptr和unique_ptr都支持的操作</th>
    </tr>
    <tr>
        <td>shared_ptr<T> sp</td>
        <td rowspan="2">空智能指针，指向类型为T的对象</td>
    </tr>
    <tr>
        <td>unique_ptr<T> up<td>
    </tr>
    <tr>
        <td>p</td>
        <td>将p用作一个条件判断，若p为一个对象，则为true</td>
    </tr>
    <tr>
        <td>*p</td>
        <td>解引用p, 获得它指向的对象</td>
    </tr>
    <tr>
        <td>p->mem</td>
        <td>等价于(*p).mem</td>
    </tr>
    <tr>
        <td>p.get()</td>
        <td>返回p中保存的指针，要小心使用，若智能指针释放了其对象，<br>返回指针所指向的对象也消失了</td>
    </tr>
    <tr>
        <td>swap(p,q)</td>
        <td rowspan="2">交换p和q中的指针</td>
    </tr>
    <tr>
        <td>p.swap(q)</td>
    </tr>
</table>

shared_ptr独有操作列表:
<table>
    <tr>
        <th colspan="2">shared_ptr独有操作<th>
    </tr>
    <tr>
        <td>make_shared<T> (args)</td>
        <td rowspan="2">返回一个shared_ptr,指向一个动态分配类型为T的对象, <br>使用args初始化对象</td>
    </tr>
    <tr>
        <td>shared_ptr<T> p(q)</td>
    </tr>
    <tr>
        <td>p = q</td>
        <td>p和q都是shared_ptr,所保存的指针必须能相互转换。<br>此操作会递减p的引用计数,递增q的引用计数；<br>若p的引用计数变为0，则将其管理的内存释放</td>
    </tr>
    <tr>
        <td>p.unique()</td>
        <td>若p.use_count()返回为1， 返回true;否则返回false</td>
    </tr>
    <tr>
        <td>p.use_count()</td>
        <td>返回与p共享对象智能指针数量；可能很慢，主要用于调式</td>
    </tr>
</table>

##### make_shared函数
最安全的分配和使用动态内存的方法是调用一个名为make_shared的标准库函数。此函数在动态内存中分配一个对象并初始化它，返回指向此对象的shared_ptr。与智能指针一样，make_shared也定义在memory中。<br> 当要用make_shared时，必须指定想要创建的对象类型:
```C++
// 指向一个值为42的int的shared_ptr
shared_ptr<int> p3= make_shared<int>(42);
// p4指向一个值为“9999999999”的string
shared_ptr<int> p4 = make_shared<sting>(10, '9');
// p5指向一个值初始化的int，即值为0
shared_ptr<int> p5 = make_shared<int> ();
```
常用auto定义一个对象保存make_shared结果：
```C++
// p6 指向一个动态分配的空 vector<string>
auto p6 = make_shared<vector<string>>();
```

##### shared_ptr的拷贝和控制
当进行拷贝或赋值操作时，每个shared_ptr都会记录多少个其他shared_ptr指向相同的对象:
```C++
    auto p = make_shared<int> (42); // p 指向的对象只有p一个引用者
    auto q(p); //p和q指向相同对象，此对象有两个引用者
```
可以认为每个shared_ptr都有一个关联计数器，通常称**引用计数**。何时拷贝一个shared_ptr，计数器都会递增。当我们给shared_ptr赋予一个新值或是shared_ptr被销毁时，计数器就会递减。一旦一个shared_ptr的计数器为0，就会自动释放自己所管理对象:
```C++
    auto r = make_shared<int> (42); // r指向的int只有一个引用者
    r=q; // 给r赋值，令它指向另一个地址
         // 递增q指向对象的引用计数
         // 递减r原来指向对象的引用计数
         // r原来指向对象已没有引用者，会自动释放
```
当指向一个对象的最后一个shared_ptr被销毁时，shared_ptr类会自动销毁。通过另一个特殊成员函数-- **析构函数(destructor)** 完成销毁工作。shared_ptr的析构函数会递减它所指向的对象的引用计数。如果引用计数变为0，shared_ptr析构函数就会销毁对象，并释放它占用的内存。

当动态对象不再被使用时，shared_ptr类会自动释放动态对象，这一特性使得动态内存的使用变得非常容易。我们可能返回一个函数，它返回一个shared_ptr，指向一个Foo类型的动态分配对象，对象是通过一个类型为T的参数进行初始化:
```C++
   // factory返回一个shared_ptr,指向一个动态分配的对象
   shared_ptr<Foo> factory(T arg)
   {
        return make_shared<Foo> (arg);
   }
```
可以确保它分配的对象会在恰当的时刻被释放。例如，下面的函数将factory返回的shared_ptr保存在局部变量中:
```C++
    void use_factory(T arg)
    {
        shared_ptr<Foo> p = facotry(arg);
    } // p 离开了作用域，它指向的内存会被自动释放掉
```
当p被销毁时，将递减其引用计数并检查它是否为0。如果有其他shared_ptr也指向这块内存，就不会释放掉:
```C++
    shared_ptr<Foo> used_factory(T arg)
    {
        shared_ptr<Foo> p = facotry(arg);
        return p; //当我们返回p时，引用计数进行了递增操作，p离开了作用域，但它指向的内存不会被释放掉
    }
```
对于一块内存，shared_ptr类保证只要有任何shared_ptr对象引用它，它就不会被释放掉。如果忘记了销毁程序不再需要shared_ptr，程序仍会正确执行，但会浪费内存。shared_ptr在无用之后仍然保留的可能，将shared_ptr存放在一个容器中，随后重排了容器，从而不再需要某些元素。

- 如果你将shared_ptr存放在一个容器中，不再需要全部元素，而只使用其中一部分，记得用erase删除不再需要的那些元素

##### 定义StrBlob类

[代码实现](./shared_ptr/src/strblob_impl.cpp)

#### 直接管理内存
**new** 分配内存,**delete** 释放new分配的内存。相对于智能指针,这两个运算符管理内存非常容易出错，而且它们不能依赖类对象拷贝，赋值和销毁操作的任何默认定义。
##### 使用new动态分配和初始化对象
在自由空间分配的内存是无名的,因此new无法为其分配的对象命名，而是返回一个指向该对象的指针：
```C++
int *pi = new int; //pi 指向一个动态分配的、未初始化的无名对象
```
默认情况下，动态分配的对象是默认初始化的。意味着内置类型或组合类型对象的值是未定义的，而类类型对象用默认构造函数进行初始化:
```C++
string *ps = new string; // 初始化空string
int *pi = new int; // pi 指向一个未初始化的int
```
我们可以直接使用初始化方式初始化一个动态分配的对象。可以使用花括号，在新标准下也可以使用列表初始化(使用花括号):
```C++
int *pi = new int(1024); // pi 指向的对象值为1024
string *ps = new string(10, '9'); // *ps 为“9999999999”

vector<int> *pv = new vector<int> {0,1,2,3,4,5,6,7}; 
```
也可以对对象进行值初始化,只需要在类型名之后跟一对空括号:
```C++
string *ps1 = new string;  //默认初始化为空string
string *ps = new string(); // 值初始化为空string
int *pi = new int;         // 默认初始化; *pi 值未定义
int *pi1 = new int();      // 值初始化，*pi1为0
```
定义了自己的构造函数的类类型，要求值初始化是没有意义的；对象都会通过默认构造函数来初始化。对于内置类型：值初始化的内置类型对象有着良好定义的值，而默认初始化对象的值则是未定义的。

提供了一个括号包围的初始化器，就可以使用auto从此初始化器来推断我们想要分配的对象的类型：
```C++
auto p1 = new auto(obj);    //p 指向一个与obj类型相同的对象，该对象用obj进行初始化
auto p2 = new auto{a,b,c};  // 错误：括号中只能有单个初始化器
```
只有当括号中仅有单一初始化器才可以使用auto。p1的类型是指针，指向obj自动推断出类型。新分配的对象用obj进行初始化。<br>
用new分配的const对象是合法的:
```C++
//分配并初始化一个const int
const int *pi = new const int(1024);
//分配并默认初始化一个空的const string
const string *ps = new const string;
```
[代码实现](./shared_ptr/src/new_delete.cpp)<br>
类似其他const对象，动态分配的const对象必须进行初始化。对于一个定义了默认构造函数类类型，其const动态对象可以隐式初始化，其他类型必须就必须显式初始化。

##### 内存耗尽
默认情况下，如果new不能分配所要求的内存空间，它会抛出一个类型为bad_alloc的异常。我们也可以使用new的方式来阻止它抛出异常:
```C++
int *p1 = new int;              //如果分配失败，new抛出std::bad_alloc
int *p2 = new (nothrow) int;    //如果分配失败，返回一个空指针
```
这种形式的new称为定位new,定位new允许我们向new传递额外的参数。此例中，我们传递给它一个由标准库定义的名为nothrow的对象，意图是告诉它不能抛出异常。这种形式的new不能分配所需内存时，会返回一个空指针。**bad_alloc** 和**nothrow** 都定义在new头文件中。

##### 释放动态内存
我们通过**delete**将动态内存归回给系统。delete表达式接受一个指针，指向我们想要释放的对象:
```C++
delete p; // p 必须指向一个动态分配对象或是一个空指针
```
我们传递给delete的指针必须指向动态分配的内存，或者一个空指针。释放一块并非new分配的内存，或者将相同的指针释放多次，行为是未定义的:
```C++
int i, *pi1 = &i, *pi2 = nullptr;
double *pd = new double(3.01), *pd2 = pd;
delete i;       // 错误，i不是一个指针
delete pi1;     // 未定义：pi1指向一个局部变量 
delete pi2;     // 正确，释放一个空指针总是没错的
delete pd;      // 正确
delete pd2;     // 未定义: pd2指向的内存已经被释放了
```
虽然一个const对象的值不能被改变，但它本身是可以被销毁的:
```C++
const int *pci = new const int();
delete pci; // 正确：释放一个const对象
```
##### 动态对象的生命周期
对于一个内置指针管理的动态对象，直到被显式释放之前它都是存在的。
```C++
// factory返回一个指针，指向一个动态分配的对象
Foo *factory(T arg)
{
    return new Foo(arg);   // 调用者释放此内存
}
```
记得在use_factory中释放内存:
```C++
void use_factory(T arg)
{
    Foo *p = factory(arg);
    /*
        使用p
    */
    delete p;   //记得释放内存，我们已经不需要它了
}
```
当我们delete一个指针后，指针值就变为无效了 --- **空悬指针**,指向一块曾经保存数据对象但现在已经失效的内存的指针。有一种方法可以避免空悬指针问题：在指针即将离开其作用域之前释放掉所关联内存， 在delete之后将nullptr赋予指针。<br>
动态内存的基本问题可能是多个指针指向相同的内存。在delete内存之后重置指针的方法只对这个指针有效，对其他任何仍指向(已释放的)内存的指针是没有作用的。
```C++
int *p = new int(42);
auto p = q;         // p 和 q指向相同的内存
delete p            // p 和 q均变为无效
p = nullptr;        // 指出p不再绑定到任何对象
```
本例中p和q指向相同的动态分配对象。我们delete此内存，p置为nullpt。但是重置p对q没有任何作用，释放p所指向的内存时，q也变为无效了。实际系统中查找指向相同内存的所有指针是异常困难的。<br>
练习12.6， 12.7 [代码实现](./shared_ptr/src/new_shared_ptr_vector.cpp)

##### shared_ptr和new结合使用
我们可以用new返回的指针来初始化智能指针：
```C++
shared_ptr<double> p1;                  
shared_ptr<double> p2(new double(1.01));    // p2 指向一个值为42的int
```
接受指针参数的智能指针构造函数是explicit的。因此我们不能将一个内置指针隐式转换为一个智能指针，必须使用直接初始化形式来初始化一个智能指针:
```C++
shared_ptr<int> p1= new int ();     // 错误：必须使用直接初始化
shared_ptr<int> p2(new int(1024));  // 正确：使用了直接初始化形式
```
一个返回shared_ptr的函数不能在其返回语句中隐式转换一个普通指针：
```C++
shared_ptr<int> clone(int p)
{
    return new int (p);     //错误：隐式转换为shared_ptr<int>
}
```
我们必须将shared_ptr显式绑定到一个想要返回的指针上:
```C++
shared_ptr<int> clone (int p)
{
    return shared_ptr<int> (new int (p)); // 正确：显式地用int*创建shared_ptr<int>
}
```
一个用来初始化智能指针的普通指针必须指向动态内存，因为智能指针默认使用delete释放它所关联的对象。
<table>
    <tr>
        <th rospan="2">定义和改变shared_ptr的其他方法</th>
    </tr>
    <tr>
        <td>shared_ptr<T> p(q)</td>
        <td>p管理内存指针q所指向的对象;q必须向new分配的内存，且能转化为T*类型</td>
    </tr>
    <tr>
        <td>shared_ptr<T> p(u)</td>
        <td>p从unique_ptr u那里接管了对象的所有权；将u置为空</td>
    </tr>
    <tr>
        <td>shared_ptr<T> p(q, d)</td>
        <td>p接管了内置指针q所指向的对象所有权。q必须能转换为T*类型。<br>p将使用可调用对象d来替代delete</td>
    </tr>
    <tr>
        <td>shared_ptr<T> p(p2,d)</td>
        <td>p是shared_ptr p2的拷贝，唯一的区别是p将用可调用对象d来替代delete</td>
    </tr>
    <tr>
        <td>p.reset()</td>
        <td rowspan="3">若p是唯一指向其对象的shared_ptr,reset会释放此对象。<br>若传递了可选的参数内置指针q,会令p指向q,否则会将p置为空。<br>若还传递了参数d,将会调用d而不是delete来释放q</td>
    </tr>
    <tr>
        <td>p.reset(q)</td>
    </tr>
    <tr>
        <td>p.reset(q, d)</td>
    </tr>
</table>
