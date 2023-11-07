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
