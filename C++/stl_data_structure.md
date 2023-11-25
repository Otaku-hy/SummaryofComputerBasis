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

   哈希表是一种基于数组的支持快速查找的数据结构，通过将key转化为index（通过hash function），hash table允许直接访问数据。

   但是由于hash table大小有限，即使是无冲突的hash function也不能保证可以在数组大小的范围内使得所有数据映射出的index都不同，所以还需要解决hash conflict的方法：

   a. **开放地址法**：寻找其他位置存放conflict数据

   ​	linear probing：顺序向下找到第一个空闲的位置存放数据

   ​	square probing: 每次向下移动$i^2$，找到空闲位置

   ​	double hashing: 使用另一个hash function作为移动步长的选择函数

   ​	**注：为了使double hashing得出的步长可以遍历整个table，需要表长是个质数

   b. **链表法**：将每个hash entry设置为链表，在链表中查找元素是否出现

   **Graphcis常用方法：结合linear probling & double hashing & list

   ​	插入：首先第一个hash function对应了一个大的hash entry，这个entry实际上还是一个数组。接着secondary hash function生成关于个这个数据的checksum，遍历数组找出未存储数据的位置i将该数据存入，并且checksum[i] = hash(data)

   ​	查找：用first hash function找到entry，接着循环遍历entry数组，根据secondary hash确定这些数组中每一项所存储的数据的hash value(使用checksum存储的）是否和我们要查找的一致，如一致则返回

   ​		
