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
        <td>shared_ptr< T> sp</td>
        <td rowspan="2">空智能指针，指向类型为T的对象</td>
    </tr>
    <tr>
        <td>unique_ptr< T> up<td>
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
        <td>make_shared< T> (args)</td>
        <td rowspan="2">返回一个shared_ptr,指向一个动态分配类型为T的对象, <br>使用args初始化对象</td>
    </tr>
    <tr>
        <td>shared_ptr< T> p(q)</td>
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

#### shared_ptr和new结合使用
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
        <th colspan="2">定义和改变shared_ptr的其他方法</th>
    </tr>
    <tr>
        <td>shared_ptr < T> p(q)</td>
        <td>p管理内存指针q所指向的对象;q必须向new分配的内存，且能转化为T*类型</td>
    </tr>
    <tr>
        <td>shared_ptr< T> p(u)</td>
        <td>p从unique_ptr u那里接管了对象的所有权；将u置为空</td>
    </tr>
    <tr>
        <td>shared_ptr < T> p(q, d)</td>
        <td>p接管了内置指针q所指向的对象所有权。q必须能转换为T*类型。<br>p将使用可调用对象d来替代delete</td>
    </tr>
    <tr>
        <td>shared_ptr< T> p(p2,d)</td>
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

##### 不要混合使用普通指针和智能指针
考虑下面shared_ptr进行操作的函数:
```C++
// 在函数被调用时ptr被创建并初始化
void process(shared_ptr<int> ptr)
{
    //使用ptr
}  //ptr离开作用域，被销毁
```
process的参数是传值方式的，因此实参会被拷贝到ptr中。拷贝一个shared_ptr会递增引用计数，因此，在process运行过程中，引用计数至少为2。当process结束时，ptr的引用计数会递减，但不会变0。<br>
传递一个shared_ptr：
```C++
shared_ptr<int> p(new int(42)); // 引用计数为1
process(p);     // 拷贝p会递增它的引用计数；在process中引用计数值为2
int i = *p;     // 正确，引用计数为1
```
传递一个临时的shared_ptr,这个shared_ptr是用一个内置指针显式构造。但是，这样做很可能导致错误:
```C++
int *x(new int(1024)); //x是一个内置指针,不是智能指针
process(x);             // 错误，不能将int*转换为shared_ptr<int>
process(shared_ptr<int> (x));  // 合法，但执行完process 内存会被释放
int j = *x;             // 未定义行为, x是一个空悬指针
```
将一个shared_ptr绑定到一个普通指针时，我们就将内存管理交给了这个shared_ptr。一旦这样做了，我们就不能用内置指针访问shared_ptr所指向的内存了。

##### 不要使用get初始化另一个智能指针
智能指针定义名为get的函数，返回一个内置指针。将另一个智能指针绑定到get返回的指针是错误的：
```C++
shared_ptr<int> p(new int (42)); //智能指针引用计数为1
int *q = p.get();   
{
    shared_ptr <int> (q); //两个独立的shared_ptr指向相同的内存
}// 程序块结束，q被销毁，它指向的内存被释放
int foo = *p; //未定义：p指向的内存已经被释放了
```
本例中，p和q指向相同的内存。两个智能指针相互独立创建，因此各自引用计数都是1。当一个程序块中的智能指针销毁时，导致指向的内存被释放。从而p变成一个空悬指针，试图使用p时，行为未定义。当p被销毁时，这块内存会被第二次释放。

- 永远不要用get初始化另一个智能指针或者为另一个智能指针赋值

##### 其他shared_ptr操作
我们可以用reset将一个新的指针赋予一个shared_ptr:
```C++
p.reset(new int (1024));  //p 指向一个新对象
```
与赋值类似,reset会更新引用计数，可能会释放p指向的对象；reset与unique经常一起使用，控制多个shared_ptr共享对象:
```C++
if (!p.unique())
{
    p.reset(new string (*p)); //我们不是唯一用户；分配新的拷贝
}

*p += newVal;   //现在我们是唯一用户，可以改变对象的值。
```

#### 智能指针与异常

使用智能指针，程序块过早结束，智能指针类也能确保在内存不需时将其释放:
```C++
void f()
{
    shared_ptr<int> sp(new int (1024));  // 分配一个对象
    // 过程中执行抛出异常，且在f中未捕获
}// 函数结束时shared_ptr自动释放内存
```
函数退出有两种可能，正常处理结束或者发生了异常，无论哪种情况，局部对象都会被销毁。<br>
与之相对，直接管理的内存发生异常时是不会释放的。使用内置指针管理内存，在new之后的对应的delete之前发生了异常，内存不会被释放:
```C++
void f()
{
    int *ip = new int(42);   //动态分配一个对象
    //这段代码throw exception,未在f中捕获
    delete ip;
}
```
在new和delete之间发生异常，且异常未在f中捕获，则内存永远无法释放。

##### 使用我们自己的释放操作
默认情况下，shared_ptr假定指向的是他们的动态内存。因此，当一个shared_ptr被销毁时，默认对它管理的指针进行delete操作。用shared_ptr来管理一个connection,我们必须首先定义一个函数来替代delete。这个删除器(deleter)函数必须能够对shared_ptr中保存的指针进行释放的操作：
```C++
void end_connection(connection *p)
{
    disconnect(p);
}

void f(detination &d)
{
    connection c= connect(&d);
    shared_ptr<connection> p (&c, end_connection);
    // 使用连接
    // 当f退出时，connection会被正确关闭，即使是异常退出
}
```
创建shared_ptr时，可以传递一个指向删除器函数的参数。当p被销毁时，它不会对保存的指针执行delete，而是调用end_connection。

**智能指针陷阱**

- 不适用相同内置指针初始化多个智能指针
- 不delete get()返回的指针
- 不使用get()初始化或reset另一个智能指针
- 如果使用get()返回的指针，记住当最后一个对应的智能指针销毁后，之前get()返回的指针就失效了
- 如果使用智能指针管理的资源不是new分配的内存，记住传递给它一个删除器

#### unique_ptr
**unique_ptr**与shared_ptr不同，某个时刻只能有一个unique_ptr指向一个给定对象。当unique_ptr对象销毁时，它所指向的对象也被销毁。当我们定义一个unique_ptr时，需要将其绑定到一个new返回的指针上,直接初始化:
```C++
    unique_ptr<int> p(new int(42));  // p指向一个值为42的int
```
unique_ptr不支持普通的拷贝和赋值操作：
```C++
unique_ptr<string> p1(new string("cpp primer"));
unique_ptr<string> p2(p1);  //错误，unique_ptr不支持拷贝
unique_ptr<string> p3;
p3 = p1;   //错误，unique_ptr不支持赋值
```
<table>
    <tr>
        <th colspan="2">unique_ptr操作</th>
    </tr>
    <tr>
        <td>unique_ptr< T> u1</td>
        <td>空unique_ptr 可以指向数据类型为T的对象；u1会使用delete来释放它的操作</td>
    </tr>
    <tr>
        <td>unique_ptr< T,D> u2</td>
        <td>u2会使用一个类型为D的可调用对象来释放它的指针</td>
    </tr>
    <tr>
        <td>unique_ptr< T,D> u(d)</td>
        <td>空unique_ptr,指向类型为T的对象，用类型为D的对象d替代delete</td>
    </tr>
    <tr>
        <td>u = nullptr</td>
        <td>释放u指向的对象，将u置为空</td>
    </tr>
    <tr>
        <td>u.release()</td>
        <td>释放u指向的对象，将u置为空</td>
    </tr>
    <tr>
        <td>u.reset()</td>
        <td>释放u指向的对象</td>
    </tr>
    <tr>
        <td>u.reset(p)</td>
        <td rowspan="2">如果提供了内置指针p,令u指向这个对象；否则将u置为空</td>
    </tr>
    <tr>
        <td>u.reset<nullptr></td>
    </tr>
</table>

通过调用release或reset将指针所有权从一个(非const)unique_ptr转移给另一个unique_ptr:
```C++
unique_ptr<string> p2(p1.release()) ;// release将p1置空，同时给p2直接用p1返回的内置指针直接初始化
unique_ptr<string> p3(new string("TEXT"));
p2.reset(p3.release()); // reset释放了p2原来指向的内存,p3将所有权转交给了P2
```
调用release会切断unique_ptr和它原来管理的对象间的联系。release返回的指针通常被用来初始化智能指针。如果我们不用另一个智能指针管理release返回的指针，我们就要负责资源的释放：
```C++
p2.release();           //错误：p2不会释放内存，而且我们丢失了指针
auto p = p2.release();  //正确，但我们必须delete p;
```
##### 传递unique_ptr参数和返回unique_ptr

我们可以拷贝或赋值一个将要被销毁的unique_ptr。最常见的例子就是函数返回一个unique_ptr:
```C++
unique_ptr<int> clone (int p)
{
    return unique_ptr<int> (new int(p)); // 正确: 从int *创建一个unique_ptr<int>
}

unique_ptr<int> clone(int p)
{
    unique_ptr<int> ret(new int(p));

    return ret;     //正确: 返回一个局部对象的拷贝
}

```
编译器直到要返回的对象将要被销毁。在此情况下，编译器执行一种特殊的“拷贝”。

##### 向unique_ptr传递删除器
unique_ptr默认情况下用delete释放它指向的对象。unique_ptr管理删除器方式与shared_ptr不同。重载一个unique_ptr中的删除器会影响到unique_ptr类型以及如何构造该类型对象。在创建或reset一个unique_ptr类型对象时，必须提供一个指定类型的可调用对象（删除器）:
```C++
// p指向一个类型为objT的对象，并使用一个类型为delT对象释放objT对象，调用一个名为fcn的delT类型对象
unique_ptr< objT, delT> p (new objT, fcn);
```
一个更具体的例子，重写连接函数，用unique_ptr替代shared_ptr:
```C++
void f(destination &d)
{
    connection c=connect(&d);
    unique_ptr<connection, decltype(end_connection) *> p(&c, end_connection);
    /*
        使用连接
    */
    当f退出时(及时异常退出)connection会被正确关闭
}
```

#### weak_ptr
*weak_ptr*是一种不控制所指向对象生命周期的智能指针，它指向shared_ptr管理的对象。weak_ptr绑定到shared_ptr不会改变该shared_ptr的引用计数，shared_ptr被销毁，对象也还会被销毁。
<table>
<tr>
    <th colspan="2">weak_ptr</th>
<tr>
<tr>
    <td>weak_ptr< T> w</td>
    <td>空weak_ptr可以指向类型为T的对象</td>
</tr>
<tr>
    <td>weak_ptr<T> wp(sp)</td>
    <td>与shared_ptr sp指向相同对象的weak_ptr。T必须能转换为sp指向的类型</td>
</tr>
<tr>
    <td>w = p</td>
    <td>p可以是一个shared_ptr也可以是weak_ptr。赋值后w与p共享对象</td>
</tr>
<tr>
    <td>w.reset()</td>
    <td>将w置为空</td>
</tr>
<tr>
    <td>w.use_count()</td>
    <td>与w共享对象的shared_ptr数量</td>
</tr>
<tr>
    <td>w.expired()</td>
    <td>若use_count为0则返回true,否则返回false</td>
</tr>
<tr>
    <td>w.lock()</td>
    <td>如果expired返回true，返回一个空shared_ptr;否则返回一个指向w的对象shared_ptr</td>
</tr>
</table>

当我们创建一个weak_ptr时，要用一个shared_ptr来初始化它：
```C++
auto sp = make_shared<int> (42);
weak_ptr<int> wp(sp);       // wp弱共享p;p的引用计数未改变
```
创建wp不会改变p的引用计数；wp指向的对象可能被释放掉。由于对象可能不存在，我们不能使用weak_ptr直接访问对象，必须调用lock，此函数检查weak_ptr指向的对象是否仍存在。如果存在，lock返回一个指向共享对象的shared_ptr：
```C++
if(shared_ptr<int> sp = wp.lock())  //如果sp不为空则条件成立
{
    // 在if中，sp与wp共享对象
}
```
### 动态数组
C++语言和标准库提供了两种一次分配一个对象数组的方法。C++语言定义了另一种new表达式语法，可以分配并初始化一个对象数组。标准库包含一个名为allocator的类，允许我们将分配和初始化分离.

#### new和数组
new分配要求数量的对象并返回指向第一个对象的指针:
```C++
int *pia = new int [get_size()]; //pia指向第一个int
```
也可以用一个表示数组类型的类型别名来分配一个数组，new表达式就不需要方括号了:
```C++
typedef int arrT[42];   // arrT表示42个int的数组类型
in *p = new arrT;       //分配一个42个int的数组；p指向第一个int
```

##### 分配一个数组得到一个元素类型指针
虽然我们称new T[] 分配的内存为"动态数组"，用new分配的一个数组，我们并未得到一个数组类型的对象，而是得到一个数组元素类型的指针。new返回的是一个元素类型的指针,因此不能对动态数组调用begin或end。

##### 初始化动态分配的数组
默认情况下，new分配的对象，不管是单个还是多个分配，都是默认初始化的。可以对数组中元素进行初始化，方式是在大小后跟一对空括号:
```C++
int *pia = new int[10];           // 10 个未初始化的int
int *pia2 = new int[10]();        // 10个值初始化为0的int
string *psa = new string[10];     // 10个空string
string *psa2 = new string[10]();  // 10个空string
```
在C++11中,我们还可以提供一个元素初始化器的花括号:
```C++
// 10个int分别用列表中对应的初始化器初始化
int *pia3 = new int[10] {0,1,2,3,4,5,6,7,8,9};
string *psa3 = new string[10]{"an", "primer", string(3,'+')};
```

初始化器会用来初始化动态数组中开始部分的元素。如果初始化器小于元素数目，剩余进行值初始化。如果初始化器大于元素数目，new表达式失败，不会分配任何内存。在本例中，new会抛出一个类型为bad_array_new_length的异常。类似bad_alloc,此类型定义在头文件new中。

##### 动态分配一个空数组是合法的
我们不能创建一个大小为0的静态数组，但当n=0,调用new[n]是合法的:
```C++
char arr[0];    //错误：不能定义长度为0的数组
char *cp = new cahr[0]; //正确，但是cp不能解引用
```
对于零长度的指针来说，此指针就像尾后指针一样，我们可以像用尾后迭代器一样使用这个指针。

##### 释放动态数组
释放动态数组，我们使用一种特殊形式的delete ---- 在指针前加上一个空括号对:
```C++
delete p;       // p 必须指向一个动态分配的对象或为空
delete [] pa;   // pa必须指向一个动态分配的数组或为空
```
销毁pa指向的数组中的元素，并释放对应内存。数组中元素按逆序销毁，最后一个元素首先被销毁，然后倒数第二个，以此类推。当我们释放一个指向数组的指针时，空括号是必须的：它指示编译器此指针指向一个对象数组的第一个元素。如果我们delete一个指向数组的指针时忽略了方括号，其行为是未定义的。<br>
当我们使用类型别名定义一个数组类型时，在new表达式中不适用[],即使这样，在释放一个数组指针式也必须使用方括号:
```C++
typedef int attrT[42];  // attrT是42个int的数组类型的别名
int *p = new attrT;     // 分配一个42个int的数组；p 指向第一个元素
delete [] p;            // 方括号是必须的，因为我们当初分配的是一个数组
```

##### 智能指针和动态数组
标准库提供了一个可以管理new分配的数组的unique_ptr版本。用一个unique_ptr管理动态数组，我们必须在对象类型后跟一对空方括号:
```C++
// up指向一个包含10个未初始化int的数组
unique_ptr<int[]> up(new int[10]);
up.release();   //自动用delete[]销毁其指针
```
由于up指向一个数组，当up销毁它管理的指针时，会自动使用delete[]。<br>
当一个unique_ptr指向一个数组时，我们不能使用点和箭头成员运算符。unique_ptr指向的时一个数组而不是单对象，因此点和箭头运算符是无意义的。当unique_ptr指向一个数组时，我们可以使用下标运算符来访问数组中的元素。<br>
[代码实现](./alloc_array/src/new_array.cpp)

<table>
    <tr>
        <th colspan="2"> 指向数组的unique_ptr</th>
    </tr>
    <tr>
        <td colspan="2">指向数组的unique_ptr不支持成员访问运算符。其他unique_ptr操作运算不变</td>
    </tr>
    <tr>
        <td>unique_ptr< T[]>u</td>
        <td>u可以指向一个动态分配的数组，元素类型为T</td>
    </tr>
    <tr>
        <td>unique_ptr< T[]>u(p)</td>
        <td>u指向内置指针p所指向的动态分配的数组。p必须能转换为类型T*</td>
    </tr>
    <tr>
        <td>u[i]</td>
        <td>返回u拥有的数组中位置i处对象</td>
    </tr>
</table>

C++11中,shared_ptr不直接支持管理动态数组

#### allocate 类
new和delete有一些灵活性上的局限性，new将内存分配和对象的构造组合在了一起，delete将对象析构和内存释放组合在一起。当分配一大块内存时，我们通常计划在这块内存上按需构造对象，我们希望将内存分配和对象构造分离。<br>
标准库**allocator**类定义在头文件memory中，帮助我们将内存分配和对象构造分离开。allocator是一个模板,我们必须指明这个allocator可以分配的对象类型:
```C++
allocator<string> alloc;            // 可以分配string的allocator对象
auto const p = alloc.allocate(n);   // 分配n个未初始化的string
```

<table>
<tr>
    <th colspan="2">allocator类及其算法</th>
</tr>
<tr>
    <td>allocator< T> a</td>
    <td>定义一个名为a的allocator对象，它可以为类型为T的对象分配内存</td>
</tr>
<tr>
    <td>a.allocator(n)</td>
    <td>分配一段原始的、未构造的内存，保存n个类型为T的对象</td>
</tr>
<tr>
    <td>a.deallocate(p,n)</td>
    <td>释放从T*指针p中地址开始的内存，这块内存保存了n个类型为T的对象;<br>p必须是由allocate返回的指针,且n必须是p创建时所要求的大小.</td>
</tr>
<tr>
    <td>a.construct(p,args)</td>
    <td>p必须是一个类型为T*的指针,指向一块原始内存:arg被传递给类型为T的构造函数</td>
</tr>
<tr>
    <td>a.destroy(p)</td>
    <td>p为T*类型的指针,此算法对p指向的对象执行析构函数</td>
</tr>
</table>

##### allocator分配未构造的内存
allocator分配的内存是未构造的(unconstructed)。在C++11标准中，construct成员函数接受一个指针和零个或多个额外参数，在给定位置构造一个元素，额外参数用来初始化对象。这些额外参数必须是构造的对象类型相匹配的初始化器:
```C++
auto q = p;      
alloc.construct(q++);       // *q为空字符串
alloc.construct(q++,3,'c'); // *q为ccc
alloc.construct(q++,"c++ primer");  // *q为 c++ primer
```
当我们用完对象后，必须对每个构造元素调用destroy来销毁他们：
```C++
while (q != p)
    alloc.destroy(--q);
```
一旦元素被销毁后，就可以重新使用这部分内存保存其他string,也可以将其归还给系统。释放内存通过调用deallocate完成:
```C++
alloc.deallocate(p,n);
```
我们传递给deallocate的指针不能为空，必须指向由allocate分配的内存。传递给deallocate的大小参数必须调用allocated分配内存时提供的大小参数具有一样的值。<br>
[代码实现](./alloc_array/src/allocator.cpp)

### 使用标注库:文本查询程序
 [代码实现](./text_query/CMakeLists.txt)