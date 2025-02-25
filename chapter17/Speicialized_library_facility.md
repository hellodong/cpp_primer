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