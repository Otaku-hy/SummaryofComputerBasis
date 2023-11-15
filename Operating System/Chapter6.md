1. 同步互斥概念：

​	同步：并发执行的进程在执行时需要一定的先后顺序

​	互斥：对临界资源的访问在同一时间只能允许一个进程

2. 临界区：

   访问临界资源(共享的数据结构变量)的代码段叫临界区

   解决临界区问题要求：

   	1. 互斥——同一时间只有一个进程在临界区执行
   	1. 进步(空闲让步)——当临界区空闲时，立即允许一个进程的访问
   	1. 有限等待——不会出现饥饿的情况

3. 互斥软件实现(Perterson算法)：

   在进入区设置"主动争取，主动谦让"，检查对方是否想进入、己方是否谦让

   code：

   ```c++
   global bool flag[2]   //争取：true表示想进入临界区
   global int turn				//表示现在应该是谁的该进入
     
   while(1)
   {
     	///进入区
     	flag[i] = true //主动争取
      	turn= 1-i //主动谦让
       while(turn == 1-i && flag[1-i]); //当对方想进入，己方谦让时循环等
     	///临界区
     	do something
     	///退出区 
     	flag[i] = false
   }
   ```

4. 互斥硬件实现：

   a. 中断屏蔽：在进入区关闭中断，使操作系统无法上下文切换，但在多核系统下不成			立

   b. test_and_set：

   ```c++
   bool test_and_set(bool* lock)
   {
   	bool old = *lock;
   	*lock = true;
   	return old;
   }
   
   while（test_and_set(&lock)）;
   
   do something
     
   lock = true
   ```

   确保只有当lock = false时才能进入临界区

   c. compare_and_swap：

   ```c++
   int compare_and_swap(int* lock,int expect,int new)
   {
   	int old = *lock;
   	if(old == expect)
   		*lock = new;
   	return old;
   }
   
   while(compare_and_swap(&lock,0,1));
   
   do something
     
   lock = 0
   ```

   当lock中存的希望值时才会赋予新值，否则不做任何操作，返回old值确保只有当lock=0时才能进入临界区

5. 互斥锁：

   封装原子操作为自旋锁，当有进程在临界区执行时其他进程需要**忙等待**

6. 信号量：

   semaphore{value,list}

   value表示资源数量，list表示等待资源的队列

   P/wait()操作：value--，根据剩余资源数量决定阻塞进程还是跳过

   V/signal()操作：value++，根据剩余资源数量决定通知阻塞进程还是跳过

7. 信号量实现进程同步/互斥原理：

   互斥：确定临界区，为每个临界区创建value=1的信号量，每个进程进入临界区前wait()，离开临界区signal()

   **相当于共享的资源为临界区且只有一个

   同步：分析具有“前-后”同步关系的事件，为每个事件建立value=0的信号量，在执行前操作的进程signal()，在执行后操作的进程wait()

   **相当于只有一个资源且一直被前操作进程占用，只用前操作进程释放了资源，后操作进程才能使用该资源

8. 经典案例：

   1. 生产者消费者模型
   2. 读者写者问题：第一类读写问题要求读者比写者优先级高
   3. 哲学家就餐问题

9. 管程：由于信号量机制复杂，将其封装为抽象数据结构

   ​	组成：共享数据；条件变量(信号量mini用于同步)；访问函数(互斥的函数，由编译器实现)

   

   