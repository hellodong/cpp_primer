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
 
