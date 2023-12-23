C++关键字

1. const关键字

   一般用来定义常量，const修饰的全局变量放在.rodata节，局部变量则在栈上分配内存空间。const还可以修饰指针和引用：

   ```c++
   const int* a; //(const int)*  指向常量的变量指针，其指向变量不可修改
   int* const a 	//(int *) const 指向变量的常量指针，指针不可指向其他变量
   ```

   其中(const int)*表示底层const；(int\*)const 表示顶层const

   const还可以修饰成员函数，const类对象只能调用const重载的函数，而非const对象优先使用非const重载的函数，无则加const匹配到const函数

2. static关键字

   使用static关键字可以生成静态变量、函数，变量会放在.bss,.data节中。编译器会为每个static变量/函数赋予一个独特的名字，使其对其他文件/类/函数不可见。

   static修饰的全局变量只有在本编译block中可视，其他block中不可视。static修饰的函数内局部变量指对这一个函数可见。static修饰的成员对这个类的所有对象共享

   **若想访问类静态成员，使用`类名::成员名`即可

3. extern关键字

   将一个全局变量/函数设置为弱符号，若其他编译block中存在同名强符号则会进行符号解析，修改相应符号表项。

   注：extern “C”表示编译器需要按c的命名规则翻译函数名，而不是c++

   ```c++
   extern "c" void func()  //译名：func_
   ```

4. explicit关键字

   标明一个类型转化函数，或单变量构造函数是显示的，不能隐式调用用于参数传递和函数返回值

5. constexpr关键字

   c++要求某些表达式的参数必须为编译期可确定的值：

   ```c++
   #include <iostream>
   
   template<bool B>
   void test()
   {
       if(B)
           std::cout << "true";
       else
           std::cout << "false";
   }
   
   bool ret()
   {
       return false;
   }
   
   int main()
   {
       test<ret()>();
   }
   ```

   这时，如果使用函数作为参数，则编译器报错。需要在函数前增加constexpr表示函数结果/表达式编译器即可确定，可以要求编译器进行优化

6. volatile关键字——防止编译器用寄存器优化变量访问

7. mutable关键字——即使对象const，mutable的成员依然可以修改

8. auto/decltype关键字

   当我们希望从表达式推断出变量类型，并以此表达式初始化变量时，使用auto

   auto会忽略掉表达式的引用和顶层const

   当我们只希望从表达式推断出变量类型，而不以此表达式初始化变量时，使用decltype

   decltype不会忽略表达式的引用和顶层const

   **注：

   ```c++
   int a; int* p=&a;
   decltype(a) d1 //int
   decltype((a)) d2 //int&    //括号表达式返回左值
   decltype(p) d3 //int*
   decltype(&a) d4 //int*			//取地址表达式返回指针
   decltype(*p) d5 //int&				//解引用表达式返回左值
   decltype(a=1) d6 //int&				//operator=返回左值
   ```

   同时，由于auto关键字要求有确定的初始值，所以不能用于函数参数传递，推断模版参数，数组定义等

9. inline关键字

   将函数在调用处内联展开：速度快(局部性)，但代码变臃肿

   \**现代c++ 编译器开启优化后会自动内联短函数，inline关键字可用于将**函数符号变为弱**

   **宏命令也可以做到函数的展开，宏在预处理阶段展开，而inline关键字在编译阶段展开。宏命令更多的是一种字符串匹配和替换。

   

   

   