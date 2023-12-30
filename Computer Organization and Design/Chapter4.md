## 总线&IO

### 1. 总线

1. 结构：片内总线/系统总线(数据线+地址线+控制线)/通信总线

2. 总线仲裁*：集中仲裁方式：由总线控制器进行所有总线请求的分配管理

   流程：主设备发出BR；若多个主设备都BR，总线控制器判优按一定优先级决定哪个设备使用总线，并发送BG；获得总线控制权的设备开始传输数据

   a. 链式查询：固定优先级链，BG从控制器发向最近的主模块，当其不使用时将BG向后传递，直到一个发出BR的模块，截断该BG信号，并发送BS告知控制器当前有设备使用总线

   pros&cons：结构简单易于扩充；但有设备故障时无法正确运作，无法修改优先级，低优先级饥饿问题

   b. 计时器定时查询：不使用BG而使用设备地址信号，查询时计时器将计数值作为设备地址发送给各个模块，模块地址若匹配则发送BS。如不，计数值+1，继续向下查询直到匹配

   pros&cons：优先级灵活，电路故障不影响；但增加控制线，控制过程复杂

   c. 独立请求：每个模块专门的BR和BG和控制器相连，控制器内部设置一个排队电路进行判优，然后向优先级高的模块发送BG

   pros&cons：响应速度块；但是控制线更过，硬件开销大

3. 总线通讯*

   a. 同步通讯：使用统一的时钟信号控制数据传输的过程

   ​	pros&cons：控制简单；但当各部件速度相距较大时，为保证数据的传送正确，必须以最慢的设备设置时钟信号

   b. 异步通讯：模块间使用应答的方式建立联系，不许使用统一同步信号

    1. 不互锁：发送信号一段时间自动撤销，数据信号一段时间也自动撤销

       **导致传输可靠性差

    2. 半互锁：当发送端接受到了数据后才撤销require信号，数据信号则一段时间自动撤销

    3. 全互锁：双放均需要来自另一端的ACK才会撤销信号(e.g. 接收到data/已撤销req)

       **可靠性高

4. 总线性能指标

   总线传输周期：进行一次总线操作的时间，通常为多时钟周期

   总线时钟周期：机器时钟周期

   总线工作频率,时钟频率：一秒内时钟翻转频率

   总线宽度：数据线位数

   总线带宽：总线宽度*总线工作频率

   数据传输率：单位时间内总线实际传输的数据位数

### 2. IO

1. IO设备：

   a. 键盘

   ![image-20231229222027056](C:\Users\zhy\AppData\Roaming\Typora\typora-user-images\image-20231229222027056.png)

使用计数器循环扫描键开关矩阵中的每一个键位是否按下，按下后数时器停止+1，并将计数值发送给ROM，取出该键对应的ASCII码传送给CPU

​	b. 显示器——字符显示器

![image-20231229222655963](C:\Users\zhy\AppData\Roaming\Typora\typora-user-images\image-20231229222655963.png)

显存中(VRAM)，存放(width,height)大小的buffer，其中每个位置存放字符的ASCII码，

字符发生器中(ROM)，存放每一个字符的点阵信息，可根据ASCII码和一个行号读出一个字符的点阵的第n行的显示位，并送至移位寄存器

点震荡器产生时钟信号；

点计数器负责字符中每一行中的当前显示点的计数，当一个字符的行满时通知字计数器切换下一个字符；

字计数器负责当前显示的一行中的第几个字符，满时通知行计数器切换下一行，控制水平同步和回扫；

行计数器负责字符矩阵显示到哪一行的计数，满时通知排计数器切换到下一排的字符，控制行间隔；

排计数器负责当前显示的是显存中第几排的字符的计数，控制垂直同步和回扫

2. IO接口

   编址：对于IO接口的数据，控制，状态寄存器可使用独立编址或统一编址(和内存使用一个地址空间)

   接口与设备数据传送方式：并行，串行

   IO控制方式：

   1) 轮询：启动IO后程序不停访问IO接口的状态寄存器直到ready

   2) 中断：接口ready后向CPU发送中断请求，并处理数据

      处理过程：中断请求(接口设置INTR，CPU可以MASK接口的INTR)->中断判优(判优电路选择相应哪个INTR)->中断响应(关中断，保存PC，获得中断程序入口)->中断服务(保护现场，中断处理，恢复现场)->中断返回(弹出PC，开中断)

      **多重中断：增加保存现场后开中断，恢复现场前关中断。同时使用屏蔽字设置不同类型中断的中断处理优先级(非判优优先级)，使只有高优先级的中断才能打断当前中断

   3) DMA：由DMA完成大块连续数据的IO控制和管理

      工作过程：预处理：发送DMA参数(读位置，写位置，大小)

      ​		    数据传送：通过周期窃取完成主存和DMA的数据交换

      ​		    后处理：向CPU发送中断请求

      交换方式：停止CPU访问：DMA需要访问主存时，停止CPU访存

      ​		    交替访问：将CPU周期分为DMA访存和CPU访存两部分

      ​		    周期窃取：当IO设备需要访存时，挪用几个存取周期

      