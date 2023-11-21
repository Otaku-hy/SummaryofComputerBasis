1. static_cast

   static_cast可以完成C++内置基本类型的转换基类派生类的相互转化，也可以把void*指针转化为其他类型指针。但是static_cast并不进行安全检查，所以必须自行确保这些转化的正确性。

   **static_cast不能作用于有底层const的引用/指针上

2. const_cast

   只能用于改变运算对象的底层const属性(增加或消去)

   **其他所有转换函数均不能转换const，同时const_cast也不能执行其他的转化工作

3. reinterpret_cast

   重新解释对象的二进制数据

4. dynamic_cast

   用于多态类型对象的指针和引用的转换：基类->子类；子类->基类；多重继承下 非最下方子类->兄弟类

   原理：

   ```c++
   Derived* pd = dynamic_cast<Derived*>(pb);
   ```

   Derived的type_info在编译器会生成，pb所指向对象的type_info通过vptr访问虚表获得。比较通过pb所指向的对象的type_info是否能转化为<>内给定的type_info。如能则进行转化，返回Derived*，否则返回bad_typeid

   typeid运算符：

   ​	typeid(e)运算符返回一个继承type_info类型的常量引用对象，e可以是任何表达式或类型名

   ​	对于引用类型，typeid直接返回引用的对象的类型，对于指针，typeid返回P+类型名，对于常量指针，返回PK+类型名

   type_info类型：

   ​	成员函数：1==    2!=    3name()

   **dynamic和static的区别：

   1. dynamic_cast可以将一个多态虚基类转换成子类或邻近兄弟类，但是static_cast不能。因为static不会对它的操作对象进行检查类型
   2. dynamic_cast无法对void*进行转换，因为需要虚表的类型信息
   3. 无法作用在有顶层const的对象上