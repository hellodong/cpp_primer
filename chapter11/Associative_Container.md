## Associative Container

 关联容器支持高效的关键字查找与访问.两个主要的关联容器，类型是**map**与**set**。标准库提供8个关联容器，体现在三个维度上:

- 每个容器或者是一个set, 或者是一个map
- 要求不重复关键字，或者允许重复关键字
- 按顺序保存元素或者，无序保存

 类型map与multimap定义在头文件map中。类型set与multiset定义在头文件set中。无序容器定义在头文件unordered_map与unordered_set中。

### 使用关联容器

##### 使用map

 如下例子是单词计数:

```CPP
        std::istream_iterator<std::string> input(file), eof;
        std::map<std::string, size_t> word_count;

        while (input != eof)
        {
                std::cout <<" " << *input;
                word_count[*input++]++;
        }
        std::cout << "\n" << std::endl;
        for (const auto &w:word_count)
        {
                std::cout << w.first << " occurs " << w.second << " times" << std::endl;
        }
```

 while 循环每次从输入流迭代器读入一个单词。每个单词对word_count进行下标操作。如果word还未在map中，下标运算会创建一个新元素，关键字为word,值为0。[代码实现](./using_map_set/src/use_map.cpp)

 读取完所有输入，for语句遍历map,打印每个单词和对应的计数值。从map中提取一个元素，会得到一个pair类型对象。简单来说pair是一个模板类型，保存两个名为first和second的数据成员。map所使用的pair用first成员保存关键字，用second保存对应值。

##### 使用set

```CPP
        std::map<std::string, size_t> word_count;
        std::set<std::string> exclud{"The","And", "But","Or",
                                     "the","and", "but","or"};

        while (input != eof)
        {
                std::cout <<" " << *input;
                if (exclud.find(*input) != exclud.end())
                {
                        word_count[*input]++;
                }
                input++;
        }

```

 此程序与前程序不同在于，我们检查单词是否在指定集合中。find()调用返回一个迭代器，如果关键字在set集合中，迭代器指向关键字，否则find返回尾迭代器。[代码实现](./using_map_set/src/use_set.cpp)

#### 定义关联容器

 一个map或set中的关键字必须是唯一的，对于一个给定的关键字，只能一个元素的关键字等于它。容器multimap和multiset没有此限制，它们允许多个元素具有相同的元素。

```cpp
 
    std::vector<int> ivec;
    for(std::vector<int>::size_type idx = 0;idx != 10;idx++ )
    {
        ivec.push_back(idx);
        ivec.push_back(idx);
    }

    std::set<int> iset(ivec.cbegin(), ivec.cend());
    std::multiset<int> multiset(ivec.cbegin(), ivec.cend());

    std::cout << "ivec size:" << ivec.size() << std::endl; // 输出 20
    std::cout << "iset size:" << iset.size() << std::endl; // 输出 10
    std::cout << "multiset size:" << multiset.size() << std::endl; // 输出20
```

 [代码实现](./unorder_set/src/main.cpp)

#### 关键字类型的要求

 关联容器对其关键字有一些要求。对于有序容器 --- map, multimap,set,multiset,关键字类型必须定义元素比较的方法。默认情况下，标准库使用关键字类型的<运算符比较两个关键字。在set类型中，关键字类型就是元素类型。在map类型中，关键字类型是元素的第一部分类型。

##### 有序容器的关键字类型

 可以提供自己定义的操作替代关键字上的< 运算符。所提供的操作必须在关键字类型上定义一个**严格弱序**， 可以将严格弱序看作“小于等于”。它必须具备如下基本性质:

* 两个关键字不同时“小于等于”对方；如果k1"小于等于"k2, 那么k2绝不能“小于等于”k1

##### 使用关键字类型的比较函数

 为了指定使用自定义的操作，必须在定义关联容器类型时提供操作的类型。自定义的操作类型必须在尖括号中紧跟着元素类型给出。[代码实现](./multiset_compare/src/)

 在尖括号中出现的每个类型，就仅仅是一个类型而已。当我们出现一个容器时，才会以构造函数参数的形式提供真正的比较操作。例如，我们不能直接定义一个Sales_data的multiset,因为Sales_data没有<运算符

#### pair类型

 **pair**的标准库类型定义在头文件 \<utility\>中

 pair 的数据成员是public的，两个成员分别命名为**first和second**。我们可以用普通的成员访问符号就可以访问它们.

```c++
 std::cout << w.first << " occurs " << w.second << std::endl;
```

 标准库定义了有限的几个pair操作

|                      |                                                                       |
| -------------------- | --------------------------------------------------------------------- |
| pair<T1,T2> p        | p是一个pair类型，<br>两个类型分别为T1和T2的成员都进行了值初始化           |
| pair<T1,T2> p(v1,v2) | p是一个成员类型为T1和T2的pair;<br>first和second成员分别用v1和v2进行初始化 |
| make_pair(v1, v2)    | 返回一个用v1和v2初始化的pair。<br>pair类型从v1和v2类型推断出来            |

##### 创建pair对象的函数

一个函数需要返回一个pair。在新标准下,我们可以对返回值进行列表初始化

```c++
std::pair<std::string, int> process (std::vector<std::string> &v)
{
    if (!v.empty())
    {
        return {v.back(), v.back().size()};  // 列表初始化
    }
    else
    {
        return std::pair<std::string, int>(); // 隐式构造返回值
    }
}
```

较早版本不允许用花括号包围的初始化来返回pair这种类型对象，必须显示返回：

```C++
 if (!v.empty())
    {
        return std::pair<std::string, int> (v.back(), v.back().size());  // 列表初始化
    }
```

或者还可以用make_pair 来生成pair对象，pair的类型来自make_pair的参数:

```C++
if (!v.empty())
{
    return make_pair(v.back(), v.back().size());
}
```
###关联容器操作
关联容器定义了下表类型，这些类型表示容器关键字和值的类型。

|||
|-|-|
|key_type|此容器类型的关键字类型|
|mapped_type|每个关键字关联的类型，只适用于map|
|value_type|对于set，与key_type相同 <br>对于map,为pair<const key_type, mapped_type>|

对于set类型，**key_type**和**value_type**是一样的;set中保存的值就是关键字。在一个map中，元素是关键字-值对，即每个元素是一个pair对象。由于我们不能改变一个元素的关键字，因此这些pair关键字部分是const的：
```C++
set<string>::value_type v1;     //v1是一个string
set<string>::key_type v2;       //v2是一个string
map<string,int>::value_type v3; //v3是一个pair<const string, int>
map<string, int>::key_type v4;  //v4是一个string
map<string, int>::mapped_type v5; //v5是一个int
```
我们使用作用域运算符提取一个类型的成员,例如: map<string, int>::key_type
#### 关联容器迭代器
解引用关联容器迭代器时，会得到一个类型为容器的value_type的值引用。对map而言，value_type是一个pair类型，first成员保存const的关键字，second成员保存值：
```C++
    auto map_it = word_count.begin();       // *map_it 是指向一个pair<std::sting, size_t> 对象的引用
    std::cout << map_it->first;             // 打印此元素的关键字
    std::cout << " " << map_it->second;     // 打印此元素的值
    map_it->first = "new key";              // 错误， 关键字是const的
    ++map_it->second;                       // 正确，我们可以通过迭代器改变元素  
```
[代码实现](./associateveContainerOper/src/map_iterator.cpp)
- 一个map的value_type是一个pair,我们可以改变pair的值，但不能改变关键字的值
##### set的迭代器是const的
set类型同时定义了iterator和const_iterator类型,但这两种类型都只允许只读访问set中的元素。一个set中的关键字也是const的。
```C++
std::set<int> iset{1,2,3,4,5,6,7};
std::set::iterator set_it = iset.begin();
if (set_it != iset.end())
{
    *set_it = 42;       //错误，set中的关键字是只读的
}
```
[代码实现](./associateveContainerOper/src/set_iterator.cpp)
##### 遍历关联容器
初始化迭代器map_it,指向word_count中的首元素。只要迭代器不等于end, 就打印当前元素并递增迭代器。解引用map_it来获得pair成员。
```C++
 auto map_it = word_count.begin();
 while(map_it != word_count.end())
 {
    std::cout << map_it->first;  // 解引用迭代器，打印关键字-值对
    std::cout << " " << map_it->second<< std::endl;
    map_it++; // 递增迭代器，移动到下一个元素
 }
```
[代码实现](./associateveContainerOper/src/traversal_map.cpp)

#### 添加元素
关联容器insert成员向容器添加一个元素或一个元素范围。map和set包含不重复关键字，插入一个已存在元素对容器没影响。
```C++
vector<int> ivec={2,4,6,8,10};
set<int>set2:
set2.insert(ivec.begin(), ivec.end());
set2.insert({1,2,3,4,5,6,7,8,9});
```
[代码实现](./associateveContainerOper/src/set_insert.cpp)

##### 向map添加元素
对一个map进行insert操作时，元素类型必须是pair。可以在insert参数列表中创建一个pair:
```C++
word_count.insert({word,1});
word_count.insert(std::make_pair(word,1));
word_count.insert(std::map<string, size_t>(word,1));
word_count.insert(std::map<string, size_t>::value_type(word,1));
```
[代码实现](./associateveContainerOper/src/map_insert.cpp)

<table>
    <tr>
        <th colspan="2" align="left">关联容器inset操作</th>
    </tr>
    <tr>
        <td>c.insert(v)</td>
        <td rowspan="2">v是value_type的类型对象;args是用来构造一个元素<br>只有当元素关键字不在c中才插入。</td>
    </tr>
    <tr>
        <td>c.emplace(args)</td>
    </tr>
    <tr>
        <td>c.insert(b,e)</td>
        <td rowspan="2"> b和e是迭代器，表示一个c::value_type类型值的范围；<br>il是这种值的花括号列表。return void</td>
    </tr>
    <tr>
        <td>c.insert(il)</td>
    </tr>
    <tr>
        <td>c.insert(p,v)</td>
        <td rowspan="2">类似insert(v),但将迭代器p作为一个提示，指出从哪里开始搜索新元素应该存储的位置。<br>返回一个迭代器，指向具有给定关键字的元素</td>
    </tr>
    <tr>
        <td>c.emplace(p,args)</td>
    </tr>
</table>

##### 检测insert的返回值
添加单一元素的insert和emplace版本返回一个pair,告诉我们插入操作是否成功。pair的first成员是一个迭代器，指向具有给定关键字的元素;second成员是一个bool值，指出插入元素是否执行成功。作为一个例子，我们用insert重写单词计数程序:
```C++
// 统计每个单词在输入中出现次数
map<string, size_t> word_count;
string word;
while(cin >> word)
{
    auto ret = word_count.insert({word, 1});
    if (!ret.second)
    {
        ++ret.first->second;
    }
}
```
##### 删除元素
关联容器定义了三个版本erase, 通过传递erase一个迭代器或迭代器对来删除一个元素或一个元素范围。这两个版本erase与对应顺序容器操作非常相似：指定元素被删除，返回void。

关联容器提供额外的erase操作，接受一个key_type参数。此版本删除所有匹配给定关键字元素，返回实际删除元素的数量。我们用此版本打印结果之前从word_count中删除特定单词：
```C++
// 删除一个关键字，返回删除元素数量
if (word_counte.erase(removal_word))
{
    cout << "OK:" << removal_word << " removed" << endl;
}
else
{
    cout << "oops: " << removal_word << " not found" << endl;
}
```
对于保存不重复关键字的容器，erase的返回值总是0或1。若返回值为0，则表明想要删除的元素并不在容器中。
<table>
    <tr> 
        <th colspan="2" align="left"> 从关联容器删除元素 </th> 
    </tr>
    <tr>
        <td>c.erase(k)</td> 
        <td>从c中删除每个关键字为k的元素。返回一个size_type值，指出删除的元素数量</td>
    </tr>
        <td>c.erase(p)</td>
        <td>从c中删除迭代器p指定的元素。p必须指向c中一个真实元素，不能等于c.end()。<br>返回一个指向p之后元素的迭代器，若p指向c中尾元素，则返回c.end()</td>
    <tr>
        <td>c.erase(b,e)</td>
        <td>删除迭代器对b和e所表示的范围中的元素。返回e</td>
    </tr>
</table>

#### map的下标操作
**map**和**unordered_map**容器提供了下标运算符和一个对应的at函数。**set**类型不支持下标，因为"set"中没有与关键字相关联的"值"。我们不能对multimap和unordered_multimap进行下标操作，因为这些容器中可能有多值与一个关键字相关联

map下标运算接受一个索引，获取与此关键字相关联的值。与其他下标运算符不同的是，如果关键字不在map中，会为它创建一个元素并插入到map中，关联值将进行初始化
```C++
map<string, size_t> word_count; //map 为空
word_count["Anna"] = 1;//插入一个关键字为Anna的元素，关联值进行值初始化；然后将1赋值
```
进行如下操作:
- 在word_count中搜索关键字为Anna的元素，未找到
- 将一个新的关键字-值对插入到word_count中。关键字是一个const string,保存Anna.值进行初始化，本例中意味值为0
- 提取出新插入的元素，并将值1赋予它

由于下标运算符可能插入一个新元素，我们只可以对非const的map进行下标操作。
<table>
    <tr>
        <th colspan="2" align="left">map和unordered_map下标操作</th>
    </tr>
    <tr>
        <td>c[k]</td>
        <td>返回关键字为k的元素；如果k不在c中，添加一个关键字为k的元素，对其初始化</td>
    </tr>
    <tr>
        <td>c.at(k)</td>
        <td>访问关键字为k的元素，带参数检查；若k不在c中，抛出一个out_of_range异常</td>
    </tr>
</table>

##### 使用下标操作的返回值
map的下标运算符与我们用过的其他下标运算符的另一个不同之处是返回类型。map进行下标操作时，会获得一个mapped_type对象；当解引用一个map迭代器时，会得到一个value_type对象。

与其他下标运算不同的是，map的下标运算返回一个左值。返回的左值，我们既可以读也可以写元素:
```C++
cout << word_count["Anna"]; // 用Anna作为下标提取元素，输出为1
++word_count["Anna"];       // 提取元素，增1
cout << word_count["Anna"]; // 提取元素并打印，输出为2
```

