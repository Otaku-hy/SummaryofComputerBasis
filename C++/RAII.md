RAII

1. 构造函数：

   a. 自定义构造函数构造函数：

   ​	自定义构造函数可以有任意个参数，类成员变量通过初始化表达式初始：

   ```c++
   Pig(std::string name,int weight = 100) : mName(name), mWeight(weight) {
       //构造函数剩余部分
   }
   ```

   **自定义构造函数存在一个隐式调用问题：

   ```c++
   Pig p = {"name",1};  //implicit Pig("name",1)
   Pig p = "a";		//implicit Pig("a",100)
   ```

   即若可以找到匹配的构造函数，编译器在这种使用{}的初始化列表或单变量的情况下，会隐式得调用构造函数。当然这样的隐式构造往往是我们不需要的，所以可以使用explicit关键字禁止隐式构造

   当然，{}这中初始话列表方式也有好处：

   1. 解决函数返回结构体的问题：

      ```c++
       Intersection intersect(Ray ray){
       	...
       	return {ray.origin,ray.dir,t,isHit};
       }  //可以使用{}直接构造要返回的结构，而无需再显示的构造新的结构体再赋值
      ```

   2. 解决复杂的函数参数：

      ```c++
      void func(std::tuple<int,float,std::string> arg,std::vector<int> arr){
      	...
      }
      int main(){
          func({1,1.0,"213"},{1,2,3,4,5});
      } //函数调用时可以使用{}构造复杂的参数
      ```

   b. 拷贝构造函数

   拷贝准则：除非是智能指针，其他所有c++类型的拷贝都为深拷贝

   默认copy为浅拷贝

   c. 移动构造函数

   左值右值？