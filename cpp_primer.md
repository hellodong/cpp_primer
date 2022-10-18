### Charpter 6 函数

##### 函数声明

定义函数的源文件应该把含有函数声明的头文件包含进来，编译器负责验证函数定义和声明是否匹配.

##### 传引用参数

使用引用避免拷贝，如果无须改变引用形参的值，最好将其声明为常量引用
拷贝大的类类型对象或者容器对象比较低效，甚至有的类类型(包括IO类型在内)根本就不支持拷贝操作。当某种类型不支持拷贝操作时，函数只能通过引用形参访问该类型对象

##### const形参与实参

顶层const作用于对象本身:

```shell
const int ci = 42;   // 不能改变ci的值，const是顶层的
int i = ci;          // 正确，拷贝ci时，忽略了它的顶层const
int *const p = &i;   // const是顶层的，不能给p赋值 
```

###### 指针或引用形参与const

```shell
const int &r2 = 42; //正确
int &r4 = 42;   //错误：不能用字面值初始化一个非常量引用
```

**尽量使用常量引用**
把函数不会改变的形参定义成引用是一种比较常见的错误：

1) 这么做给调用者一种误导，函数可以修改它实参的值
2) 使用引用而非常量引用会极大限制函数所能接受的实参类型
   
我们不能把const对象、字面值或者需要类型转换的对象传递给普通的引用形参。以find_char函数为例，将它string类型形参定义成常量引用：

```c
string::size_type find_char (string &s, char c, string::size_type &occurs);
```

类似下面这样调用

```c
find_char("hello world", 'c', ctr);
```

将编译时发生错误.

##### 数组形参 
数组有两个性质，是不能拷贝数组和使用数组时会将其转换成指针。
###### 数组形参引用
形参可以时数组的引用，引用形参绑定到对应的实参上
```c
void print(int (&arr)[10])          // &arr 两端的括号不能少
{
    for (auto elem:arr)
    {
        cout <<elem << ednl;
    }
}

f(int &arr[10]) ;    //错误： 将arr声明成引用的数组
f(int (&arr)[10]);   //正确：arr 时具有10个整数的整型数组引用

int *matrix[10];       // 10个指针构成的数组
int (*matrix)[10];     // 指向含有10个整数的数组的指针 
```

#### 返回类型和return语句
##### 引用返回左值

```c
char &get_val(string &str, string::size_type ix)
{
    return str[ix];
}

int main(void)
{
    string s("a value");
    cout << s << endl;
    get_val(s, 0) = 'A';    //将 S[0] 值改为 A
    cout << s << endl;
}
```

#### 函数重载
如果同一作用域内的几个函数名字相同但形参列表不同，则称之为**重载**， 对于重载函数来说，它们应该在形参数量或形参类型上有所不同
```c
Record lookup(const Account &)
bool lookup(const Account &)        // 错误， 跟上一个函数相比只有返回类型不同
```
##### 重载和const 形参
一个拥有顶层const 的形参无法和另一个没有顶层const的形参区分开来：
```c
Record lookup(Phone);
Record lookup(const Phone);     // 重复申明了Record lookup(Phone)
```

#### 重载与作用域
如果我们在内层作用域中声明名字，它将隐藏外层作用域中声明的同名实体。在不同作用域中无法重载函数名。
```c
string read();
void print(const string &);
void print(double);
void fooBar(int val)
{
    bool read = false;
    string s = read(); // 错误， read 是一个bool, 而非函数
    void print(int);   // 新作用域，隐藏了之前的print
    print("value:");   // 错误 print (const stringg &) 被隐藏了
    print(val);        // 正确，当前print(int) 可见
    print(3.14);       // 正确， 调用print(int);print(double) 被隐藏掉了
}
```
把print(int) 和其他print 函数声明放到同一个作用域中， 针对不同的传入参数类型会有最佳匹配

#### 默认实参
调用含有默认实参的函数，可以包含该实参，也可以省略该实参。我们可以为一个或多个形参定义默认值，一旦某个形参被赋予了默认值，它后面的所有形参都必须有默认值.
```c

```
