## Overload operator and Class-type conversion
使用运算符重载可以使我们的程序更易于编写和阅读。举个例子，因为在Sales_item类中定义了输入，输出和加法运算符，所以可以通过下述形式输出两个Sales_item的和:
```C++
std::cout << item1 + item 2; // 输出两个Sales_item的和
```