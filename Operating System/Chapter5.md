1. 进程调度基本概念：

   按某种算法选择一个进程分配CPU资源

2. 调度方式：

   a. 短期调度：从就绪队列中取出进程PCB分配CPU资源

   ​	内存-> CPU 高频发生

   b. 中期调度：当内存资源紧张时，选择部分进程换出(挂起)/换入到磁盘

   ​	内存-> 外存 中频发生

   c. 长期调度：从后备队列中选择作业调入内存就绪队列并创建进程

   ​	外村-> 内存 低频发生

3. 调度时机：

   主动：进程终止，进程等待IO

   被动：出现中断，其他高优先级进程就绪，分配时间片用完

4. 调度方式：

   非抢占式调度：只在进程主动放弃时调度

   抢占式调度：由操作系统剥夺CPU使用权

5. 调度算法：

   FCFS：先来先服务，非抢占式

   ​	pros&cons: 公平调度，但对短作业不利

   SJF：最短作业优先，可抢占/非抢占

   ​	pros&cons: 平均等待短，但会导致长作业的**饥饿**

   ​	**注：对于进程调度来说，无法知道一个所需的执行时间，所以无法			实现SJF，从而只能通过猜测近似SJF

   ​		预测方法：下一次的预测与当前CPU执行长度(第n次)和以前的长度相关
   $$
   \tau_{n+1} = \alpha t_n + (1-\alpha)\tau_n
   $$
   优先级调度：高优先级的优先，可抢占/非抢占

   ​	pros&cons: 使紧急任务先执行，但会导致饥饿（解决：进程老化）

   RR：时间片轮转，抢占式调度

   ​	pros&cons: 使每个进程公平执行，但需要频繁切换导致额外开销。			     时间片太小上下文切换占比大，时间片大则退化为FCFS

   多级队列：将就绪队列分为多个不同的队列，每个进程固定属于一个队列。队列间和内分别可使用不同的调度算法

   多级反馈队列：允许进程在队列间迁移，队列间使用优先级，队列内RR

   ​	pros&cons: 结合所有调度方式的优点，但可能饥饿—老化

6. 具体案例——实时系统调度：需要抢占调度

   软实时系统—需要关键进程优于其他进程，使用抢占式优先级调度

   硬实时系统：

   ​	单速率调度RMS：周期短的进程优先级高，固定优先级

   ​	最早截止期限EDF：截止时间早的优先级高，优先级动态分配

7. 算法评估：

   1. 确定性模型：使用特定序列计算性能
   2. Little公式：$n = \lambda \times W $  队列平均长度 = 平均到达率 x 平均等待时间

   