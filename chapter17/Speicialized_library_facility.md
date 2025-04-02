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
大小必须是一个常量表达式。这条语句定义bitvec为一个包含32位的bitset。就像vector包含未命名的元素一样，bitset中的二进制位也是未命名的，我们通过位置来访问它们。二进制的位置是从0开始编号的。因此，bitvec包含编号从0到31的32个二进制位。编号从0开始的二进制位为**低位(low-order)**,编号到31结束的二进制位被称为**高位(high-order)**。

<table>
    <tr>
        <th colspan="2"> <p style="text-align:center;"> 初始化bitset的方法 </p></th>
    </tr>
    <tr>
        <td>bitset<n> b;</td>
        <td>b有n位；每一位均为0.此构造函数是一个constexpr</td>
    </tr>
    <tr>
        <td>bitset<n> b(u);</td>
        <td>b是unsigned long long 值u的低n位拷贝。<br>
            if n > unsigned long long的大小，<br>
            则b中超出unsigned long long的高位置0。<br>
            此构造函数是一个constexpr</td>
    </tr>
    <tr>
        <td>bitset<n> b(s, pos, m, zero, one)</td>
        <td>b是string s从位置pos开始m个字符的拷贝。<br>
            s只能包含字符zero或one;如果包含任何其他字符，<br>
            构造函数会抛出invalid_argument异常。<br>
            字符在b中分别保存为zero和one。<br>
            pos默认为0，m默认为string::npos,<br>
            zero默认为'0', one默认为'1'</td>
    </tr>
    <tr>
        <td>bitset<n> b(cp, pos, m, zero, one)</td>
        <td>与上一个构造函数相同，但从cp指向的字符数组中拷贝字符。</td>
    </tr>
</table>

##### 用unsigned值初始化bitset
我们使用一个整型值来初始化bitset时，此值将被转换为unsigned long long类型并被当作位模式处理。bitse中二进制位将是此模式的一个副本。如果bitset的大小\>一个unsigned long long中的二进制位数，则剩余高位被置为0。如果bitset的大小\<一个unsigned long long 中的二进制位数，则只使用给定值中的低位，超出bitset大小的高位被丢弃：
```C++
// bitvec1比初始值小;初始值中的高位被丢弃
bitset<13> bitvec1(0xbeef);
// bitvec2比初始值大；它的高位被置为0
bitset<20> bitvec2(0xbeef);
bitset<128> bitvec3(~0ULL);
```

##### 从一个string初始化bitset
我们可以从一个string或一个字符数组指针来初始化bitset。两种情况下，字符都直接表示位模式。与往常一样，当我们使用字符串表示数时，字符串中下标最小的字符对应高位，反之亦然：
```C++
bitset<32> bitvec4("1100"); // 2、3两位为1，剩余两位为0
```
如果string包含的字符数比bitset少，则bitset的高位被置为0。<br>
我们不必使用整个string来作为bitset的初始值，可以只用一个字串作为初始值:
```C++
string str("1111111111110000000011001101");
bitset<32> bitvec5(str, 5,4); // 从str[5] 开始的4个二进制位
bitset<32> bitvec6(str, str.size() - 4); // 使用最后四个字符
```
#### bitset操作
bitset操作定义了多种检测或设置一个或多个二进制位的方法。bitset类还支持位运算符。
<table>
    <tr>
        <th colspan="2"> <p style="text-align:center;"> bitset操作 </p></th>
    </tr>
    <tr> 
        <td>b.any()</td>
        <td>b中是否存在置位二进制位</td>
    </tr>
    <tr> 
        <td>b.all()</td>
        <td>b中所有位都置位了吗</td>
    </tr>
    <tr> 
        <td>b.none()</td>
        <td>b中不存在置位的二进制位</td>
    </tr>
    <tr> 
        <td>b.count()</td>
        <td>b中置位的位数</td>
    </tr>
    <tr> 
        <td>b.count()</td>
        <td>b中置位的位数</td>
    </tr>
    <tr> 
        <td>b.size()</td>
        <td>constexpr函数，返回b中的位数</td>
    </tr>
    <tr> 
        <td>b.test(pos)</td>
        <td>if pos 位置的bit 是set的, then 返回true, else false</td>
    </tr>
    <tr> 
        <td>b.set(pos,v)</td>
        <td colspan="2">将位置pos处的位设置为bool值v。v默认为true。<br>
            如果未传递实参，则将b中所有位置位</td>
    </tr>
    <tr> 
        <td>b.set()</td>
    </tr>
    <tr> 
        <td>b.reset(pos)</td>
        <td colspan="2">将位置pos处的位复位或将b中所有位复位</td>
    </tr>
    <tr> 
        <td>b.reset()</td>
    </tr>
    <tr> 
        <td>b.flip(pos)</td>
        <td colspan="2">将位置pos处的位复位或将b中所有位复位</td>
    </tr>
    <tr> 
        <td>b.flip()</td>
    </tr>
    <tr> 
        <td>b[pos]</td>
        <td>访问pos处的位</td>
    </tr>
    <tr> 
        <td>b.to_ulong()<br>b.to_ullong()</td>
        <td>返回一个unsigned long 或一个unsigned long long值，<br>
            其位模式与b相同。如果b中位模式不能放入指定的结果类型<br>
            抛出一个overflow_error异常</td>
    </tr>
    <tr> 
        <td>b.to_string(zero, one)</td>
        <td>返回一个string, 表示b中的位模式。<br>
          zero和one的默认值分别为0和1,表示b中的0和1</td>
    </tr>
    <tr> 
        <td>os << b</td>
        <td>将b中的二进制位打印为字符1和0，打印到流os</td>
    </tr>
    <tr> 
        <td>is >> b</td>
        <td>从is读取字符存入b。当下一个字符不是0或1时,<br>
            或是已经读入b.size()个位时，读取过程停止</td>
    </tr>
</table>

对每个函数，不接受参数的版本对整个集合执行给定的操作；接受一个位置参数的版本则对指定位执行操作:
```C++
std::bitset<32> bitvec(1U);
bool is_set = bitvec.any();
bool is_not_set = bitvec.none();
bool all_set = bitvec.all();     // false, 因为只有1位置位
size_t onBits = bitvec.count();  // 返回1
size_t sz = bitvec.size();       // 返回32
bitvec.flip();  // 翻转bitvec中的所有位
bitvec.reset(); // 将所有位复位
bitvec.set();   // 将所有位置位
```

当bitset对象的一个或多个位置位时，操作any返回true。相反，当所有位复位时，none总返回true。C++11引入了all操作，当所有位置位时返回true。操作count和size返回size_t类型的值，分别表示对象中置位的位数或总位数。函数size是一个constexpr函数，可以用在要求常量表达式的地方。<br>
成员flip、set、reset及test允许我们读写指定位置的位:
```C++
bitvec.flip(0);     // 翻转第一位
bitvec.set(bitvec.size() - 1); // 置位最后一位
bitvec.set(0, 0);    // 复位第一位
bitvec.reset(i);     // 复位第i位
bitvec.test(0);      // 返回false, 因为第一位是复位的
```

下标运算符对const属性进行了重载。const版本的下标运算符在指定位置置为时返回true，否则返回false。非const版本返回bitset定义的一个特殊类型，它允许我们操纵指定位的值:
```C++
bitvec[0] = 0;    // 将第一位复位
bitvec[31] = bitvec[0];
bitvec[0].flip();  // 翻转第一位
~bitvec[0];        // 等价操作，也是翻转第一位
bool b = bitvec[0];
```

##### 提取bitset的值
to_ulong和to_ullong操作都返回一个值，保存了与bitset对象相同的位模式。只有当bitset的大小\< 等于对应的大小(to_ulong为unsigned long, to_ullong为unsigned long long) 时，我们才能使用这两个操作:
```C++
unsigned long ulong = bitvec3.to_ulong();
std::cout << ulong << std::endl;
```

##### bitset的IO运算符
输入运算符从一个输入流读取字符，保存到一个临时的string对象中。直到读取的字符达到对应bitset的大小时，或是遇到不是1或0的字符时，或是遇到文件尾或输入错误时，读取过程才停止。随即用临时string对象来初始化bitset。如果读取的字符数小于bitset的大小，则与往常一样，高位将被置为0。
```C++
bitset <16> bits;
std::cin >> bits;  // 从cin 读取最多16个0或1
std::cout << "bits: " << bits << std::endl;
```

##### 使用bitset
用bitset代替unsigned long 表示30个学生的测验结果:
```C++
unsigned long quizA = 0; 
quizA |= 1UL << 27;   // 第27个学生通过测验
status = quizA & (1UL << 27);  // 检查第27个学生是否通过了测验
quizA &= ~(1UL << 27);          // 第27个学生未通过测验
// 使用标准库类bitset完成等价工作
std::bitset<30> quizB;
quizB.set(27);
status = quizB[27];
quizB.reset(27);
``` 

### 正则表达式
**正则表达式(regular expression)** 是一种描述字符序列的方法，是一种极其强大的计算工具。重点介绍如何使用C++正则表达式库(RE库)，它是C++11标准库的一部分。RE库定义在头文件regex中，包含多个组件。
<table>
    <tr>
        <th colspan="2"> <p style="text-align:center;"> 正则表达式库组件 </p></th>
    </tr>
    <tr> 
        <td>regex</td>
        <td>表示一个正则表达式的类</td>
    </tr>
    <tr> 
        <td>regex_match</td>
        <td>将一个字符序列与一个正则表达式匹配</td>
    </tr>
    <tr> 
        <td>regex_search</td>
        <td>寻找第一个与正则表达式匹配的子序列</td>
    </tr>
    <tr> 
        <td>regex_replace</td>
        <td>使用给定格式替换一个正则表达式</td>
    </tr>
    <tr> 
        <td>sregex_iterator</td>
        <td>迭代器适配器，调用regex_search遍历一个string中所有匹配的子串</td>
    </tr>
    <tr> 
        <td>smatch</td>
        <td>容器类，保存在string中搜索的结果</td>
    </tr>
    <tr> 
        <td>ssub_match</td>
        <td>string中匹配的子表达式的结果</td>
    </tr>
</table>

regex 类表示一个正则表达式。除了初始化和赋值之外，regex还支持其他一些操作。<br>
函数regex_match和regex_search确定一个给定字符序列和一个给定regex是否匹配。如果整个整个输入序列与表达式匹配，则regex_match函数返回true;如果输入序列中一个子串与表达式匹配，则regex_search函数返回true。还有一个regex_replace函数。<br>
下标列出了regex的函数参数。这些函数都返回bool值，且都被重载了: 其中一个版本接受一个类型为smatch的附件参数。如果匹配成功，这些函数将成功匹配的相关信息保存在给定的smatch对象中。
```C++
                regex_search和regex_match的参数

(seq, m, r, mft)        在字符序列seq中查找regex对象r中的正则表达式。    
(seq, r, mft)           seq可以是一个string、表示范围的一对迭代器以及一个指向空
                        字符结尾的字符数组指针
                        m是一个match对象，用来保存匹配结果的相关细节。m和seq必须具有兼容类型
                        mft是一个可选的regex_constants::match_flag_tpe值
```
#### 使用正则表达式库
我们从一个非常简单例子开始:
```C++
string pattern("[^c]ei");
pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
regex r(pattern);               
smatch rets;
string test_str = "receipt freind theif receive";
if (regex_search(test_str, results, r))
{
    std::cout << rets.str() << std::endl; 
}
```
我们定义一个string来保存希望查找的正则表达式。正则表达式[^c]表明我们希望匹配任意不是'c'的字符，而[^c]ei指出我们想要匹配这种字符后接ei的字符串。此模式描述的字符串恰好包含三个字符。我们想要包含此模式的单词的完整内容。<br>
这个正则表达式包含零个或多个字母后接我们的三字母模式，然后再接零个或多个额外字母。默认情况下，regex使用的正则表达式语言是ECMAScript。在ECMAScript中，模式[[:alpha:]] 匹配任意字母，符合+和*分别表示我们希望"零个，一个或多个”匹配。<br>
将正则表达式存入pattern后，我们用它来初始化一个名为r的regex对象。接下来我们定义一个string，用来测试正则表达式。我们将test_str初始化为与模式匹配的单词和不匹配的单词。我们还定义了一个名为rets和smatch对象，它将被传递给regex_search。如果找到匹配字串，rets将会保存匹配位置的细节信息。<br>
接下来我们调用了regex_search。如果它找到匹配字串，就返回true。我们用resultes的str成员打印test_str中与模式匹配的部分。函数regex_search在输入序列中只要找到一个匹配字串就会停止查找。因此，程序的输出将是
```C++
freind
```

##### 指定regex对象的选项
当我们定义一个regex或是对一个regex调用assign为其赋值时，可以指定一些标志来影响regex如何操作。默认情况下ECMAScript标志被设置，从而regex会使用ECMA-262规范，这也是很多web浏览器所使用的正则表达式语言。

<table>
    <tr>
        <th colspan="2"> <p style="text-align:center;">regex选项</p> </th>
    </tr>
    <tr>
        <td>regex r(re)<br>regex r(re,f)</td>
        <td>re 表示一个正则表达式，可以是一个string、一个表示字符范围的迭代器对、<br>一个指向空字符结尾的字符数组指针、一个字符指针和一个计数器<br>或是一个花括号包围的字符列表。f是指出对象如何处理的标志。f通过下面列出的值来设置。<br>如未指定f,其默认为ECMAScript
        </td>
    </tr>
    <tr>
        <td>r1 = re</td>
        <td>将r1中的正则表达式替换为re。re表示一个正则表达式，<br>可以是另一个regex对象、一个string、一个指向空字符结尾的字符数组指针<br>或是一个花括号包围的字符列表</td>
    </tr>
    <tr>
        <td>r1.assign(re,f)</td>
        <td>与使用赋值运算符(=)效果相同</td>
    </tr>
    <tr>
        <td>r.mark_count()</td>
        <td>r中子表达式的数目</td>
    </tr>
    <tr>
        <td>r.flags()</td>
        <td>返回r的标志集</td>
    </tr>
    <tr>
        <th colspan="2">构造函数和赋值操作可能抛出类型为regex_error的异常</th>
    </tr>
    <th colspan="2"> <p style="text-align:center;"> 定义regex时指定的标志 </p> </th>
    <tr>
        <td>icase</td>
        <td>忽略大小写</td>
    </tr>
    <tr>
        <td>nosubs</td>
        <td>不保存匹配的子表达式</td>
    </tr>
    <tr>
        <td>optimize</td>
        <td>执行速度优于构造速度</td>
    </tr>
    <tr>
        <td>ECMAScript</td>
        <td>使用ECMA-262语法</td>
    </tr>
    <tr>
        <td>basic</td>
        <td>使用POSIX基本的正则表达式</td>
    </tr>
    <tr>
        <td>extended</td>
        <td>使用POSIX扩展的正则表达式</td>
    </tr>
    <tr>
        <td>awk</td>
        <td>使用POSIX版本的awk语法</td>
    </tr>
    <tr>
        <td>grep</td>
        <td>使用POSIX版本的grep语法</td>
    </tr>
    <tr>
        <td>egrep</td>
        <td>使用POSIX版本的egrep语法</td>
    </tr>
</table>

作为一个例子，我们可以用icase标志查找具有特定扩展名的文件名。大多数操作系统都是按大小写无关的方式识别扩展名。
```C++
// 一个或多个字母或数字字符后接一个‘.’再接“cpp” 或“cxx”或“cc”
regex r("[[:alnum:]]+\\.(cpp|cxx|cc)", regex::icase);
smatch resultes;
string filename;
while(std::cin >> filename)
{
    if (regex_search(filename, resultes, r))
    {
        std::cout << resultes.str() << std::endl; 
    }
}
```

##### 使用正则表达式时的错误
正则表达式是在运行时，当一个regex对象被初始化或被赋予一个新模式时，才被编译的。我们用这种语言编写的正则表达式也可能有错误。

- 一个正则表达式的语法是否正确是在运行时解析的

如果我们编写的正则表达式存在错误，则在运行时标准库会抛出一个类型为**regex_error**的异常。regex_error有一个what函数描述发生了 什么错误。regex_error还有一个名为code()函数，返回某个错误类型对应的数值编码。

```C++
try{
    regex r("[[:alnum:]+\\.(cpp|cxx|cc)", regex::icase);
}catch(regex_error e) 
{
    std::cout <<e.what() << "\r\nCode:" << e.code() << std::endl;
}
```

<table>
    <tr>
        <th colspan="2"> <p style="text-align:center;">正则表达式错误类型</p> </th>
    </tr>
    <tr>
        <td>error_collate</td>
        <td>无效元素校对</td>
    </tr>
    <tr>
        <td>error_ctype</td>
        <td>无效字符</td>
    </tr>
    <tr>
        <td>error_escape</td>
        <td>无效转义字符或无效尾置转义</td>
    </tr>
    <tr>
        <td>error_complexity</td>
        <td>匹配过于复杂</td>
    </tr>
    <tr>
        <td>error_stack</td>
        <td>栈空间不足，无法处理匹配</td>
    </tr>
</table>

##### 正则表达式类和输入序列类型
我们可以搜索多种类型的输入序列。输入可以是普通char数据或wchar_t数据，字符可以保存在标准库string中或是char数组中(宽字符版本，wstring或wchar_t数组中)。RE为这些不同的输入序列类型都定义了对应的类型。<br>
regex类保存类型char的正则表达式。标准库还定义了一个wregex类保存类型wchar_t，其操作与regex完全相同。两者唯一差别是wregex的初始值须使用wchar_t而不是char。<br>

- smatch 表示string类型的输入类型
- cmatch 表示字符数组序列
- wsmatch 表示宽字符串(wstring)输入
- wcmatch 表示宽字符数组

我们使用的RE库类型必须与输入序列类型匹配，例如:
```C++
regex r("[[:alnum;]]+\\.(cpp|cxx|cc$)", regex::icase);
smatch results; // 将匹配string输入序列，而不是char *
if (regex_search("regexbase.cpp", results, r)) // 错误：输入为char*
{
    std::cout << results.str() << std::endl;
}
```
上面代码会编译失败，因为match参数的类型与输入序列的类型不匹配。如果我们希望搜索一个字符数组，就必须使用cmatch对象：
```C++
regex r("[[:alnum;]]+\\.(cpp|cxx|cc$)", regex::icase);
cmatch results; // 将匹配输入字符数组输入序列
if (regex_search("regexbase.cpp", results, r))
{
    std::cout << results.str() << std::endl;
}
```

<table>
    <tr>
        <th colspan="2"> <p style="text-align:center;">正则表达式库类</p> </th>
    </tr>
    <tr>
        <td>输入序列类型</td>
        <td>使用正则表达式类</td>
    </tr>
    <tr>
        <td>string</td>
        <td>regex、smatch、ssub_match和sregex_iterator</td>
    </tr>
    <tr>
        <td>const char *</td>
        <td>regex、cmatch、csub_match和cregex_iterator</td>
    </tr>
    <tr>
        <td>wstring</td>
        <td>wregex、wsmatch、wssub_match和wsregex_iterator</td>
    </tr>
    <tr>
        <td>const wchar_t</td>
        <td>wregex、wcmatch、wcsub_match和wcregex_iterator</td>
    </tr>
</table>