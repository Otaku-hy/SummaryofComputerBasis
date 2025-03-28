## 存储器

### 1. 存储器分类（主要以存取方式）*

1. 具体分类

   i. RAM随机存储器：任意存储单元数据可随机读写操作，需持续加电。一般作为cache和内存。分为：SRAM（快，小，不用刷新），DRAM（慢，大，要刷新），NVRAM（用于掉电时保护数据）

   ii. ROM只读存储器：一般只读不写，非电易失的。一般用于bios存放系统程序或驱动

   iii. SAM顺序存取存储器：只能顺序查找。如磁带

   iv. DAM直接存取存储器：先随机寻址小区域，在小区域内顺序查找。如磁盘

   v. CAM相连存储器：按存储内容查找。用于快速检索

2. 存储系统结构

   由于各种存储元件的速度，容量，造价各有优势，现代计算机使用一种层级存储来达到速度，容量，价格的平衡。具体为：Register$\leftarrow$Cache$\leftarrow$Memory$\leftarrow$辅助存储器

   设计时应遵循：包含性原则—内层数据是外层的副本；一致性原则—不同层次间信息一致

### 2. 主存储器*

1. 基本构成：存储体（由众多独立编址的存储单元构成）；寻址系统（包括MAR，译码器和驱动器—放大信号）；IO系统（包括MDR，读写电路）；控制电路

   如下图:
   
   ![](./images/memory_struct.png)
   
   对于寻址系统，一般有线选法和重合法两种：
   
   线选法将所有地址线送到一个译码器中，这样设计结构简单但需要的线路多
   
   重合法将地址线分为行地址和列地址，减少所需的器件用量(一般来说DRAM采用这种寻址系统，且行和列使用同一组引脚，由RAS行选信号和CAS列选信号控制)		

2. 性能指标

   i. 容量：字编址—存储元个数X存储字长(b)；字节编址—字节数(B)

   ii. 存取速度：存取时间MAT—一次读写操作的时间；MCT存取周期—两次存取操作的最小时间间隔

   iii. 带宽：每次存取的字/字节数*存取周期的倒数；即单位时间存取信息量

3. SRAM

   由6个晶体管构成的锁存器

   外特性符号：![](./images/sram_sign.png)

   *对于任意的逻辑符号，要在方框内标明型号容量和引端名；在方框外标明引脚线和信号名

4. DRAM

   由单晶体管和电容构成（需电容漏电要定期充电刷新）

   i. DRAM的再生：读取操作对于DRAM来说会放点，所以需要将读出的内容写回，称为***再生***

   ii. DRAM的刷新：

   ​	集中式刷新：在最大刷新时间间隔内，集中安排一段时间对每一行刷新

   ​	分散式刷新：在每次读写操作后，对一行进行刷新

   ​	异步式刷新：在最大刷新时间间隔内，将每一行的刷新分散在其内。需要额外计数器控制，但高效

   iii. 外特性符号：

   ![](./images/dram_sign.png)

   iv. 新型dram：FPM DRAM；EDO DRAM；SDRAM；DDR SDRAM

5. ROM

   类型：MROM一次直接写入；PROM一次写入，可自编程；EROM可多次写入；EEPROM电可擦除；Flash闪存

   外特性符号：

   ![](./images/rom_sign.png)

6. 存储器容量拓展以及与CPU连接

   i. 容量拓展：

   ​	a. 位拓展：多片存储的输出并成更多位的输出。需要将存储器的地址线，片选使能，读写控制分别并连起来；总字数=片数*单片字数

   ​	b. 字拓展：多片存储连接在一起扩充存储器字数，通过译码器多选1。需要将存储器的数据线和读写控制并连起来，同时地址线的低位送引脚，高位送译码器接各芯片的片选使能；总容量=片数*单片容量

   ​	c. 字位拓展：两种混用

   如图：

   ![](./images/dramc.png)

*注：该图为DRAM的容量扩展示意图。相比于SRAM和ROM，他多了用于异步刷新的刷新地址和相应的定时信号

​	ii. 存储器与CPU连接：

​		SRAM和ROM：CPU地址线地位连芯片高位连译码器；CPU数据线与存储器直接连接；CPU IO控制与芯片WE相连（ROM不用连）；CPU访存请求MREQ与译码器使能端相连

​		DRAM：通过DRAMC与CPU相连，包括：刷新地址计数器；地址多路选择器；刷新定时器；仲裁电路；地市发生器 （不重要）

### 3. 磁盘*

1. 磁记录方式（编码方式）：

   RZ：正脉冲1，负脉冲0，每写一次电流回0（导致磁盘面上存在未磁化区域）

   NRZ：正1，负0

   NRZ1：电流反向写1，方向不变0

   PM：位周期中心点，电流负->正1，电流正->负0

   FM：周期交界处电流反转，周期中心点若电流反转1，不变0

   MFM：同FM，但周期交界处电流不变，只有当连续写0才变

2. 磁记录指标：编码效率 位密度/反转次数

3. 磁盘地址：驱动器号+柱面号（磁道）+盘面号+扇区号

4. 磁盘技术指标：

   a. 容量：非格式化(所有容量)：硬盘数\*盘面数\*道密度*盘半径\*位密度\*磁道周长

   ​		格式化(实际可用)：硬盘数\*盘面数*磁道数\*扇区数\*扇区容量

   b. 记录密度：道密度：盘面上沿半径的单位长度磁道数：总磁道数=道密度*半径

   ​			位密度：磁道单位长度记录位数量：磁道容量=位密度*周长

   ​		**磁盘内外磁道容量一样大，所以内磁道位密度大

   c. 平均寻址时间=平均寻道时间+平均等待时间(0.5 * 1/转速)

   d. 数据传输率=磁道容量*转速

### 4. Cache *

1. CAM相联存储器

   结构：存储体，检索寄存器，屏蔽寄存器，数据寄存器，地址寄存器，匹配寄存器，比较电路，译码电路

   读写：写操作同RAM，需要地址，数据，WE；

   ​	读操作：在检索寄存器中设置要检索的数据值，屏蔽寄存器设置屏蔽码，以确定检索寄存器中哪几位作为检索key，通过比较电路比较出匹配的存储单元，并将匹配寄存器中相应的位置1（总共有多少个存储单元匹配寄存器就有多少位），最后根据优先排队电路确定最后读出的数据应该是哪个存储单元中的。

2. cache

   映射方式：|t位-group中找line|s位-找group|b位-找block内偏移|

   ​	全相连：只有1组，所有cacheline都在这一组中，所以任何block都可以在随意选择空闲line放置

   ​	直接连接：每个cacheline为一组，相当于每一个lock只能存在固定的line中

   ​	多路组相连：多个cacheline分为1组，在组内可以任意选择

   替换算法：

   ​	FIFO：先写入的cache先被替换

   ​	LRU：最近最长时间未被使用的cache换出

   ​	LFU：使用频率最低的cache换出