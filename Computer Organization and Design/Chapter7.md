## 控制器

###  1. 控制器概览

1. 功能：提供定时信号，控制信号，响应中断

2. 组成：指令译码器，控制寄存器，时序信号产生器，CU

3. 设计方式：组合逻辑/微程序

4. 时序系统：

   机器周期：指令周期通常可以分为几个独立的步骤完成，每个独立步骤的时间为机器周期

   节拍电位（数据传送）：一个机器周期又可以执行多次数据传送操作，所以将机器周期划分为多个节拍电位，一个节拍的宽度传送一次数据，对应一个时钟周期

   节拍脉冲（同步控制信号）：一个节拍电位又可以包含多个节拍脉冲用于寄存器的写入，置位，复位的控制信号

5. 控制方式：

   同步控制：使用时序信号控制状态转移；可使用统一的时钟周期为一个机器周期

   异步控制：通过握手触发状态转移

   联合控制：结合；大部分固定，小部分应答

### 2. 组合逻辑控制器

1. 设计思想：由指令的操作码，当前机器周期，机器状态，节拍信号我们可以确定此时哪些控制信号需要发出，即$C_i=f(Im,Bj,Ml,Tk,Pn)$
2. 设计方法：将每个机器周期的操作分解为微操作序列；列出每个微操作对应的微命令；写出微命令的最简逻辑表达式；用电路(组合逻辑，PLA)实现控制单元

### 3. 微程序控制器

1. 设计思想：一条指令的执行过程中需要不同的**微命令**，把一段时间内（一个机器周期）内的微命令组织到一起，形成一条**微指令**，这样一条指令可以看做是包含多条微命令的**微程序**。

   这样我们只需要把所有指令的微程序使用存储器保存起来，这样执行时可以根据OPCode选择呢不同的微程序发送控制信号

2. CU组成：

   控存(存放微指令), $\mu$IR, 微地址选择逻辑, CMAR($\mu$PC)

3. 微指令结构 $\mu\mathrm{OP} + \mu\mathrm{Addr}$

   a. 分类：水平型：一条微指令中定义执行多个微操作的微命令

   ​		垂直型：一条微指令只包含一种微命令

   b. 微命令编码方式：

   1. 直接编码：

   $\mu\mathrm{OP}$字段每一位表示一个微命令，’0‘表示无效'1'表示有效

   2. 字段直接编码：

   由于有一些微命令不可以同时有效，有一些可以同时有效，把不能同时有效的微命令编成一个互斥组，这样可以使用更少的bit表示这些微命令中哪个有效

   3. 字段间接编码：

   在字段直接编码的基础上，规定一个字段的一些微命令需要另一些字段来表示

   4. 混合：

   直接编码+字段直接(间接)混合

   c. 微地址形成方式：

   1. 直接表示法：

      $\mu\mathrm{Addr}$字段直接给出后续微指令的地址

   2. 增量方式：

      $\mu\mathrm{PC}$增加计数功能，非条件转移形微指令只需$\mu\mathrm{OP}$字段，其下地址由PC+1给出

      条件转移形微指令有额外的条件选择和转移地址字段

   3. 增量和下地址结合方式：

      每一条微指令都具有条件选择和转移地址字段

   4. 断定方式：

      后续微地址由非测试地址字段和测试字段通过测试网络(微地址选择逻辑)给出

4. 微入口技术：解决进入相应的微程序段执行的问题(比如fetch完后进入add指令剩余段)

   使用功能转移方式，根据Opcode进行转移

