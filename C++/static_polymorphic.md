1. c++如何实现多态？https://blog.csdn.net/qq_41033011/article/details/107762289

​	多态指一个函数名实际对应了多个不同的函数，c++有静态多态和动态多态两种：

​	静态多态通过重载和模版实现，动态多态通过继承/虚函数实现

2. 如何实现重载：

   a. 解决函数命名问题

   ​	编译器将函数名统一改为：

   命名空间/类名长度 + 命名空间/类名(常量函数/Volatile函数时类名前加+K/V) + 函数名长度 + 函数名 + 各参数类型

   比如：

   ```c++
   class A
   {
   public:
       void func(int,double,long) const;
     	void func(int,double,long) volatile;
   };
   
   //对应函数名
   __ZNK1A4funcEidl
   __ZNV1A4funcEidl
   ```

   b. 调用匹配

   ​	匹配规则&顺序：找到匹配的最佳选择

>精准匹配：只做数组名到指针，函数名到函数指针，变量到常量的微小转换
>
>提升比配：整形提升，浮点型提升
>
>标准转化匹配：int到double，double到int，Derived\*到Base*，int到unsigned int
>
>省略号匹配

当编译器为函数调用找到同一选择优先级下的多条匹配函数则报错

3. 模版如何实现：

   a. 模版函数

   ​	编译器通过根据模版参数(typename, 变量值)编译出不同名的函数，调用则调用这些不同名的函数:

   在函数参数类型前增加：模板中的非类型值(如bool N：bn, int N: in) + 模板中的类型值  然后是其余的普通参数类型
   
   ```c++
   template<typename T,typename T2>
   void process(T data,T2 other,int a)
   {
       data++;
   }
   
   template<bool debug,typename T>
   void process(int a,T b)
   {
       if(debug)
           a++;
   }
   
   process(1,1,1); //函数名：__Z7processIiiEvT_T0_i
   process(1.0,1,1); //函数名： __Z7processIdiEvT_T0_i
   process<false>(0,1); //函数名： __Z7processILb0EiEviT0_
   ```
   
   b. 类模板
   
   ​	