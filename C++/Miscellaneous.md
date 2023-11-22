Miscellaneous:

1. NULL实际上是c语言宏，实际上为常量0，所以以NULL作为函数实参则相当于整数，为了解决这个问题使用nullptr，它的类型为nullptr_t可以implicit转化为任何指针

2. 完美转发

   