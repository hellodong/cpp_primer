## Associative Container
[TOC]

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

 此程序与前程序不同在于，我们检查单词是否在指定集合中。find()调用返回一个迭代器，如果关键字在set集合中，迭代器指向关键字，否则find返回尾迭代器。
 
 [代码实现](./using_map_set/src/use_set.cpp)

### 关联容器概述
 关联容器不支持顺序容器的位置相关操作，push_front,push_back。关联容器的迭代器都是双向的。

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
### 关联容器操作
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
#### 访问元素
如果我们所关心的只不过是一个特定元素是否已在容器中，find是最佳选择。对于允许重复关键字的容器，count还会做更多的工作：如果元素在容器中，还会统计有多少个元素相同的关键字：
```C++
set<int> iset{0,1,2,3,4,5,6,7,8,9};
iset.find(1);  //返回一个迭代器，指向key == 1的元素
iset.find(11); // 返回一个迭代器，其值等于iset.end()
iset.count(1); // 返回1
iset.count(0); // 返回0
```
[代码实现](./associateveContainerOper/src/set_access_element.cpp)
<table>
    <tr>
        <th colspan="2">在一个关联容器中查找元素的操作</th>
    </tr>
    <tr>
        <td colspan="2">lower_bound和upper_bound不适用无序容器</td>
    </tr>
    <tr>
        <td colspan="2">下标和at操作只使用与非const和map,unordered_map</td>
    </tr>
    <tr>
        <td>c.find(k)</td>
        <td>返回一个迭代器，指向第一个关键字为k的元素，若k不在容器中，则返回尾后迭代器</td>
    </tr>
    <tr>
        <td>c.count(k)</td>
        <td>返回关键字等于k的元素的数量，对于不允许重复关键字的容器，返回值永远是0或者1</td>
    </tr>
    <tr>
        <td>c.lower_bound(k)</td>
        <td>返回一个迭代器，指向第一个关键字不小于k的元素</td>
    </tr>
    <tr>
        <td>c.upper_bound(k)</td>
        <td>返回一个迭代器，指向第一个关键字大于k的元素</td>
    </tr>
    <tr>
        <td>c.equal_range(k)</td>
        <td>返回一个迭代器pair,表示关键字等于k的元素范围。<br>若k不存在，pair的两个成员钧等于c.end()</td>
    </tr>
</table>
有时我们只想知道一个给定关键字是否在map中，不想改变map。这样就不能使用下标运算符来检查一个元素是否存在，因为如果关键字不存在的话，下标运算符会插入一个新元素。在这种情况下，应该使用find:

```C++
if (word_count.find("foobar") == word_count.end())
{
    cout << "foobar is not in the map" << endl;
}
```
[代码实现](./associateveContainerOper/src/map_find_instead_index.cpp)

##### 在multimap和multiset中查找元素
如果一个multimap和multiset中有多个元素具有给定关键字，则这些元素在容器中会相邻存放。打印一个特定作者所有著作，可以用三种方法解决这个问题。最直观用count和find:
```C++
string search_item("Stanley Lippman");
auto entries = authors.count(search_item);  // 元素的数量
auto iter = authors.find(search_item);      // 此作者第一本书
while(entries)
{
    cout << iter->second << endl;   // 打印书名
    entries--;
    iter++;                         // 迭代到下一本书
}
```
count确定此作者共有多少本书，调用find获得一个迭代器，指向第一个关键字为此作者的元素。如果count 返回0， 则循环一次也不执行。

我们可以用lower_bound和upper_bound来解决此问题。这两个操作都接受一个关键字，返回一个迭代器。如果关键字在容器中，lower_bound返回的迭代器指向第一个具有给定关键字的元素，而upper_bound返回的迭代器指向最后一个匹配给定关键字元素之后的位置。如果元素不在multimap中，lower_bound和upper_bound返回相等的迭代器===>相同关键字调用lower_bound和upper_bound得到一个具有该关键字元素的范围。

如果我们查找元素具有最大关键字，则此关键字的upper_bound返回尾后迭代器。如果关键字不存在，且大于容器中任何关键字，则lower_bound返回的也是尾后迭代器。

```C++
string search_item("Stanley Lippman");
//start和end 表示对应作者的元素范围
for(auto start=authors.lower_bound(search_item)，end = authors.upper_bound(search_item);start != end;start++)
{
    cout << beg->second << endl;
}
```
lower_bound的调用将start定位到第一个与search_item匹配的元素(如果存在)。如果容器中没有这样元素，start指向第一个关键字大于search_item的元素，有可能是尾后迭代器。upper_bound调用将end指向最后一个匹配指定关键字元素之后的元素。这两个操作并不报告关键字是否存在，它们的返回值可作为一个迭代器范围。我们可以通过递增beg来遍历这些元素。

- 如果lower_bound和upper_bound返回相同的迭代器，则给定关键字不在容器中.

直接调用equal_range。此函数接受一个关键字，返回一个迭代器pair。若关键字存在，则第一个迭代器指向第一个与关键字匹配的元素，第二个迭代器指向最后一个匹配元素之后的位置。若未找到匹配元素，两个迭代器都指向关键字可以插入的位置。
```C++
//pos保存迭代器对，表示与关键字匹配的元素范围
for (auto pos = authors.equal_range(search_item);pos.first != pos.second;pos.first++)
{
    cout << pos.first->second << ", ";
}
```
此pair的first成员与lower_bound返回的迭代器是一样的，second成员与upper_bound的返回值是一样的。

[代码实现](./associateveContainerOper/src/multimap_search.cpp)

#### 一个单词转换的map
展示map的创建，搜索以及遍历。<br>单词转换规则如下:
```txt
brb br right back
k okay?
y why
r are
u you
pic picture
18r later
```
原始文本如下:
```txt
where r u
y dont u send me a pic
k thk 18r
```
翻译后输出如下:
```txt
where are you
why dont you send me a picture
okay? thanks! later
```
程序将使用三个函数：
- word_transform 管理整个过程
- buildMap 读取转换规则文件 
- transform 接受一个string, 如果存在转换规则，返回转后的内容。

管理整个过程函数体：
```C++
    std::ifstream rule_file(argv[1]), text_file(argv[2]);
    std::map<std::string, std::string> trans_map;
    buildMap(rule_file, trans_map);                 // 转换规则获取
    std::string text;
    while(std::getline(text_file, text))            // 读取一行输入
    {
        std::istringstream istream(text);           // 读取每个单词
        std::string word;
        while(istream >> word)                      
        {
            std::cout << transform(word, trans_map) << " "; // 打印输出
        }
        std::cout << std::endl;
    }
```

函数首先调用buildMap生成单词转换map,将它保存在trans_map中。while循环使用getline一行一行读取输入文件。为了每行中获取单词，使用嵌套while循环，用一个istringstream来处理当前行中的每个单词。

buildMap读入给定文件，建立转换映射:
```C++
bool buildMap(std::ifstream &map_file, std::map<std::string, std::string>& trans_map)
{
    std::string key, value;     // 转换单词和转换后的内容
    // 读取第一个单词存入key中，行中剩余内容存入value
    while(map_file >> key && std::getline(map_file, value))
    {
        if (value.size() > 1)       // 检查是否有转换规则
        {
            if (value[value.size() - 1] == '\r')    // 如果尾后是个回车符，则pop尾后字符
            {
                value.pop_back();
            }
            trans_map[key] = value.substr(1);   // 跳过前导空格
        }
        else 
        {
            throw std::runtime_error("no rule for " + key);
        }
    }
    return true;
}
```
map_file中每一行对应一条规则。每条规则由一个单词和一个短语组成。我们用>>读取要转换的单词，存入key，后调用getline读取这一行中剩余内容存入value。但getline不会跳过前导空格，需要我们自己处理key和value之间的空格。同时还要注意value尾后字符是否是回车符号，如果存在则需要擦除尾后回车符。

我们使用下标符添加关键字-值对。我们隐含忽略了一个单词在转换文件中出现多次情况。如果真有单词出现多次情况，会将最后一个对应短语存入trans_map。

transform进行实际的转换工作，如果string在map中，transform返回相应的短语。否则，transform直接返回原string：
```C++
const std::string& transform(const std::string &str, const std::map <std::string, std::string> &trans_map)
{
    auto mapped = trans_map.find(str);
    if (mapped != trans_map.end())
    {
        return mapped->second;
    }
    return str;
}

```
首先调用find确定给定string是否存在map中。存在，find返回一个指向对应元素迭代器。否则，find返回尾后迭代器。如果存在，我们解引用迭代器，获得一个保存关键字和值的pair，返回成员second。

[代码实现](./associateveContainerOper/src/word_transfer.cpp)
