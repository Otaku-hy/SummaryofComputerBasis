Miscellaneous:

1. NULL实际上是c语言宏，实际上为常量0，所以以NULL作为函数实参则相当于整数，为了解决这个问题使用nullptr，它的类型为nullptr_t可以implicit转化为任何指针

2. 完美转发

   动机：当我们需要函数转发变量时：
   
   ```c++
   template<typename T> void print(T & t){
       std::cout << "Lvalue ref" << std::endl;
   }
   template<typename T> void print(T && t){
       std::cout << "Rvalue ref" << std::endl;
   }
   template<typename T> void testForward(T && v){ 
   }
   ```
   
   在`testForward`中我们使用T &&接受变量，此时在`testForward`函数中v已是左值，后续的print调用只能匹配到T&的版本上，这显然是不行的，而如果我们使用std::move则会导致只能匹配到T&&版本，所以需要一种转发机制。
   
   **preliminary**：
   
   万能引用：使用T&&同时可以接受左值和右值，接受到左值时T转变为T&，右值时T转变为T

​	引用折叠：T& && -> T&；T& & -> T&；T&& &&->T&&

​	**完美转发**：完美转发 = 万能引用+引用折叠+forward函数

```c++
template<typename T> void testForward(T &&v)
{
	print(std::forward<T>(v))
}

template<typename T> 
constexpr T&& forward(typename std::remove_reference<T>::type& t) noexcept
{
    return static_cast<T&&>(t);
}
```

我们可以看到，forward使用左值引用接受一个对象，并根据其类型，把左值cast成相应的引用，并使用T&&作为返回类型确保返回正确

3. lambda表达式：

   ```c++
   [capture]<template params>(params) lambda_specifiers(return type) {body};
   ```

   lambda表达式在编译器来看就是把整个表达式翻译成一个匿名类，并重载了operator()函数。

   capture对应LambdaClass类的private成员

   params参数列表对应operator()的参数列表

   return-type对应operator()返回值

   body对应函数体

4. 重载重写隐藏区别：

   重载：同一个作用域下的同名不同状态的函数（参数，const，volatile）

   重写：派生类重新定义基类定义过的虚函数

   隐藏：一个作用域下个函数，或派生类的函数隐藏了其他作用域/基类(不能为virtual)的同名函数(不管是否参数不一致)



​	