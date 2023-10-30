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
 while 循环每次从输入流迭代器读入一个单词。每个单词对word_count进行下标操作。如果word还未在map中，下标运算会创建一个新元素，关键字为word,值为0。

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
 #### 关键字类型的要求
 关联容器对其关键字有一些要求。对于有序容器 --- map, multimap,set,multiset,关键字类型必须定义元素比较的方法。默认情况下，标准库使用关键字类型的<运算符比较两个关键字。在set类型中，关键字类型就是元素类型。在map类型中，关键字类型是元素的第一部分类型。

 ##### 有序容器的关键字类型
 可以提供自己定义的操作替代关键字上的< 运算符。所提供的操作必须在关键字类型上定义一个**严格弱序**， 可以将严格弱序看作“小于等于”。它必须具备如下基本性质:
 
 - 两个关键字不同同时“小于等于”对方；如果k1"小于等于"k2, 那么k2绝不能“小于等于”k1

 ##### 使用关键字类型的比较函数
 为了指定使用自定义的操作，必须在定义关联容器类型时提供操作的类型。自定义的操作类型必须在尖括号中紧跟着元素类型给出。

 

