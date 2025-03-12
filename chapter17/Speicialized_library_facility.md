## 标准库特殊设置
我们不能介绍所有标准库设置，但仍有一些标准库设施在很多应用中都是有用的:tuple、bitset、正则表达式以及随机数。我们还将介绍一些附件的IO库功能：格式控制、未格式化IO和随机访问。

### tuple类型
**tuple**是类似pair的模板。不同tuple类型的成员类型也不相同，但一个tuple可以有任意数量的成员。每个确定的tuple类型成员数目是固定的，但一个tuple类型的成员数目可以与另一个tuple类型不同。<br>
当我们希望将一些数据组合成单一对象，但又不想麻烦地定义一个新数据结构来表示这些数据时，tuple是非常有用的。下表列出了tuple支持的操作。tuple类型及其伴随类型和函数都定义在*tuple*头文件中。

<table>
    <tr>
        <th colspan="2"> <p style="text-align:center;">tuple支持的操作</p> </th>
    </tr>
    <tr>
        <td>tuple'<'T1, T2,...,Tn'>' t;</td>
        <td>t是一个tuple,成员数为n,第i个成员的类型为Ti。<br>
            所有成员都进行值初始化</td>
    </tr>
    <tr>
        <td>tuple'<'T1, T2,...,Tn'>' t(v1,v2,...,vn);</td>
        <td>t是一个tuple,成员类型为T1...Tn,每个成员用对应的初始值vi初始化。<br>此构造函数是explicit的</td>
    </tr>
    <tr>
        <td>make_tuple(v1,v2,...,vn)</td>
        <td>返回一个用给定初始化的tuple.tuple的类型从初始值类型推断</td>
    </tr>
    <tr>
        <td>t1 == t2<br>t1 != t2</td>
        <td>当两个tuple具有相同数量的成员且成员对应相等时，<br>
            两个tuple相等。这两个操作使用成员的==运算符来完成。<br>
            一旦发现某对成员不等，接下来的成员就不用比较了</td>
    </tr>
    <tr>
        <td>t1 > t2<br>t1 < t2</td>
        <td>tuple的关系运算符使用字典序，<br>
            两个tuple必须具有相同数量的成员。使用 '<'运算符比较t1的成员和t2中的对应成员</td>
    </tr>
    <tr>
        <td>t1 > t2<br>t1 < t2</td>
        <td>tuple的关系运算符使用字典序，<br>
            两个tuple必须具有相同数量的成员。使用 '<'运算符比较t1的成员和t2中的对应成员</td>
    </tr>
    <tr>
        <td>get'<'i'>'(t)</td>
        <td>返回t的第一个数据成员的引用：如果t是一个左值，结果是一个左值引用；<br>
            否则，结果是一个右值引用。tuple的所有成员都是public的</td>
    </tr>
    <tr>
        <td>tuple_size'<'tupleType'>'::value</td>
        <td>一个类模板，可以通过一个tuple类型来初始化。<br>它有一个名为value的public constexpr static数据成员，<br>类型为size_t，表示给定tuple类型中成员的数量<br>
            否则，结果是一个右值引用。tuple的所有成员都是public的</td>
    </tr>
    <tr>
        <td>tuple_element'<'i,tupleType'>'::type</td>
        <td>一个类模板，可以通过一个整型常量和一个tuple类型来初始化。<br>
            它有一个名为type的public成员，表示给定tuple类型中指定成员的类型</td>
    </tr>
</table>

#### 定义和初始化tuple
当我们定义一个tuple时，需要指出每个成员的类型:
```C++
tuple<size_t, size_t, size_t> threeElement;  // 三个成员都设置为0
tuple<std::string, std::vector<double>, int, std::list<int>> someVal("constants", {3.14, 2.718}, 42, {0,1,2,3,4,5,6});
```
我们创建一个tuple对象时，可以使用tuple的默认构造函数，它会对每个成员进行值初始化；也可以像本例中初始化someVal一样，为每个成员提供一个初始值。tuple的这个构造函数是explicit的，因此我们必须使用直接初始化语法：
```C++
tuple<size_t, size_t, size_t> threeElement = {1,2,3}; // 错误
tuple<size_t, size_t,size_t> threeElement{1,2,3};    // 正确
```
标准库定义了make_tuple函数，我们可以用它来生成tuple对象:
```C++
auto item = make_tuple("cpp primer", 3,  99.00);
```
make_tuple 函数使用初始值类型推断tuple的类型。在本例中，item是一个tuple,类型为tuple<const char *, int, double>。

##### 访问tuple的成员
一个tuple的类型成员数目是没有限制的。因此，tuple的成员都是未命名的。要访问一个tuple的成员，就要使用一个名为**get**的标准库函数。为了使用get,我们必须指定一个显式模板实参，它指出我们想要访问的第几个成员。我们传递给get一个tuple对象，它返回指定成员的引用:
```C++
auto book = get<0>(item);  // 返回item 的第一个成员
auto cnt = get<1>(item);   // 返回item 的第二个成员
auto price = get<2>(item)/cnt;  // 返回item的最后一个成员
get<2>(item) *=0.8;
```
尖括号中的值必须是一个整型常量表达式。与往常一样，我们从0开始计数，意味着get<0>是第一个成员。<br>
如果不知道一个tuple准确的类型细节信息，可以用两个辅助类模板查询tuple成员的数量和类型：
```C++
typedef decltype(item) trans;  // trans是item的类型
size_t sz = tuple_size<trans>::value; 

// cnt的类型与item中的第二个成员相同
tuple_element<1, trans>::type cnt = get<1>(item);  // cnt是一个int
```
为了使用tuple_size或tuple_element，我们需要知道一个tuple对象的类型。与往常一样，确定一个对象的类型的最简单方法就是使用decltype。在本例中，我们使用decltype来为item类型定义一个类型别名，用它来实例化两个模板。<br>
tuple_size有一个名为value的public static数据成员，它表示给定tuple中成员的数量。tuple_element模板除了一个tuple类型外，还接受一个索引值。它有一个名为type的public类型成员，表示给定tuple类型中指定成员的类型。类似get,tuple_element所使用的索引也是从0开始计数的。<br>

##### 关系和相等运算符
tuple的关系和相等运算符的行为类型容器的对应操作。这些运算符逐对比较左侧tuple和右侧tuple的成员。只有两个tuple具有相同数量的成员时，我们才可以比较它们。而且，为了使用tuple的相等或不等运算符，对每对成员使用==运算符必须都是合法的；为了使用关系运算符，对每对成员使用<必须都是合法的。例如：
```C++
tuple<std::string, std::string> duo("1", "2");
tuple<size_t, size_t> two_element(1,2);
bool b = (duo == two_element);   // 错误：不能比较size_t和string
tuple<size_t, size_t,size_t> three_element(1,2,3);
b = (two_element < three_element);  // 错误：成员数量不同
tuple<size_t, size_t> origin(0, 0);
b = (origin < two_element>);        // 正确: b为 true
```

- 由于tuple定义了< 和 == 运算符，我们可以将tuple序列传递给算法，并且可以在无序容器中将tuple作为关键字类型。

#### 使用tuple返回多个值
tuple的一个常见用途是从一个函数返回多个值。例如，我们的书店可能是多家连锁书店中的一家。每家书店都有一个销售记录文件，保存每本书近期的销售记录。我们可能希望在所有书店中查询某本书的销售情况。<br>
假定每家书店都有一个销售记录文件。每个文件都将每本书的所有销售记录存放在一起。进一步假定已有一个函数可以读取这些销售记录文件，为每个书店创建一个vector\<Sales_data\>,并将这些vector保存在vector的vector中:
```C++
std::vector<std::vector<Sales_data>> files;
```
我们编写一个函数，对于一本给定的书，在files中搜索出售过这本书的书店。对每家有匹配销售记录的书店，我们将创建一个tuple来保存这家书店的索引和两个迭代器。索引指出了书店在file中的位置，而两个迭代器则标记了给定书籍在此书店的vecotr\<Sales_data\>中第一条销售记录和最后一条销售记录之后的位置。

##### 返回tuple的函数
我们首先编写查找给定书籍的函数。此函数的参数是刚刚提到的vector的vector以及一个表示书名的string。我们的函数将返回一个tuple的vector，凡是销售了给定书籍的书店，都在vector中有对应的一项:
```C++
typedef std::tuple<std::vector<Sales_data>::size_type, 
                   std::vector<Sales_data>::const_iterator,
                   std::vector<Sales_data>::const_iterator> Matches;

std::vector<Matches> findBook(const std::vector<std::vector<Sales_data>> &files, const std::string &book)
{
    std::vector<Matches> ret; // 初始化为空vector
    for (auto it = files.cbegin(); it != files.cend();it++)
    {
        auto found = equal_range(it->cbegin(), it->cend(), book,compareIsbn);
        if (found.first != found.second)
        {
            ret.push_back(make_tuple(it - files.cbegin(), found.first, found.second));
        }
    }
    return ret;
}
```
for 循环遍历files中的元素，每个元素都是一个vector。在for循环内，我们调用一个名为equal_range的标准库算法，它的功能与关联容器的同名成员类似。equal_range的前两个实参是表示输入序列的迭代器，第三个参数是一个值。默认情况下，equal_range使用\运算符来比较元素。由于Sales_data没有\< 运算符，因此我们传递给它一个指向compareIsbn函数的指针。<br>
equal_range算法返回一个迭代器pair,表示元素的范围。如果未找到book,则两个迭代器相等，表示空范围。

### bitset类型
标准库定义了**bitset**类，使得位运算符的使用更为容易，并且能够能够处理超过最长整型类型大小的位集合。bitset类定义在头文件bitset中。

#### 定义和初始化bitset
bitset类是一个类模板，它类似array类，具有固定的大小。当我们定义一个bitset时，需要声明它包含多少个二进制位:
```C++
std::bitset<32> bitvec(1U);  // 32位;低位为1, 其他位为0
```