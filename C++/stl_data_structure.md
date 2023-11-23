STL:

分类：顺序容器：vector，array，deque，list
	   关联容器：set，map
	   无序容器：unorderedmap

1. Vector：

   vector为堆区的一块连续的内存，由三个迭代器指针组成：start指向内存起始地址；finish指向数据结束地址的下一个位置；end_of_storage指向分配的内存空间的结束地址的下一个位置

   查找插入和删除：

   a. 查找：vector支持按下标随机存取，查找复杂度o(n)，有序为(logn)

   b. 插入：vector具有双倍扩容机制，当capacity无法满足需求时，使capacityx2并重新为vector分配空间，将原来的数据复制。而当capacity足够时直接在所需位置插入元素，并进行复制。所以复杂度：back最快，front最慢

   c. 删除：删除元素capacity不变，将删除位置后的数据前移。同插入back最快，front最慢

2. list：

   list分配堆中离散的空间，list中包含了一个指向链表中第一个节点的指针。每个节点包含数据，指向下一个节点和指向下一个节点的指针

   查找插入和删除：正常的链表方式，访问需顺序，不能无需访问。插入删除常数复杂度

3. set/map：

   preliminary——红黑树：

   红黑树是一种二叉平衡树，其插入，删除，查找的复杂都都为logn且比普通的二叉平衡树更容易调整。

   规则：是二叉平衡树+根叶节点黑+从同一节点出发到叶节点的所有路径黑节点数相同+无相连的红节点

   

   set和map的底层都是通过红黑树实现，所以为自动有序的结构。区别为set的value和key值为一个，而map的value值对应了自定义的vale值

4. hash

