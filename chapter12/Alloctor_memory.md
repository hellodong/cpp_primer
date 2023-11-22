## Allocator memory

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

