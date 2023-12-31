## 中央处理器

### 1. 相关概念

组成：ALU，RF，内部总线，中断系统，CU

功能：顺序，中断，操作，时间，数据

微操作*：如一条指令，可能需要需要运算，寄存器数据打入等不同的操作的结合。微操微，指一条指令执行过程中不可再分解的操作

微命令*：执行微操作所用到的控制信号称为微命令

###  2. RTL语言*

描述数据通路的传输的语言

所有微操作写在前面，微命令写在后面，中间用”;“隔开：
$$
\begin{align*}
&\mathrm{fetch~instruction}:\\
&\mathrm{MAR} = \mathrm{(PC)}; \mathrm{MARWr}=1\\
&\mathrm{PC} = \mathrm{(PC)} +1; \mathrm{PCWr}=1 \\
&\mathrm{IR} = \mathrm{M[MAR]}; \mathrm{MemR}=1 \\
\end{align*}
$$

### 3. 指令周期分解

一个指令周期可以分成多个机器周期：

取指令FI -> 指令译码ID -> 执行指令EX -> 存储器访问MA -> 数据写回WB

FI阶段：根据PC从mem中取出指令，放入IR，并修正PC为下一条指令地址

ID阶段: 将IR中的指令交给CU分析需要的信号，并读出相关的寄存器组的值放入暂存寄存器

EX阶段：根据不同指令执行ALU运算或者分支跳转所需的操作

MA阶段：根据不同指令需要访问Memory获得数据或写入数据

WB阶段：将MA结果或ALU运算结果写回至寄存器

### 4. 结构分类

1. 单周期CPU——每个指令周期只包含一个机器周期（以下均默认一个机器周期仅包含一个时钟周期）
2. 多周期CPU——每个指令周期包含多个(可以不同)机器周期
3. 流水CPU——每个指令包含多个(但固定个数)机器周期，且不同指令可以在数据通路行重叠执行

流水线：每条指令包含的机器周期数相同

​	FI，ID，EX，MA，WB (即使不进行操作也要进行该周期的寄存器写入)

​	每个机器周期包含的时钟周期相同

### 5. 不同类型CPU的数据通路

1. 单周期分散互连

   <img src="./images/截屏2023-12-31 16.58.57.png" alt="截屏2023-12-31 16.58.57" style="zoom:50%;" />

   各指令执行过程简述：

   FI阶段：Inst <- IM[PC]

   ​		Add1_B <- (PC) + 4

   add: ID: R_data1 <- RF[Inst[25-21]], R_data2 <- RF[Inst[20-16]], W_Reg <- Inst[15-11]; 		RegDst = 1

   ​	EX: ALU_A <- R_data1, ALU_B <- R_data2; ALUSrc = 0, ALUCtrl = 000

   ​	WB: W_data = ALU_C, PC <- (PC) + 4; memToReg = 0, RegWr = 1, Branch=0, jump=0	

   lw;sw;beq;j 单周期过于简单，后续不分析

2. 多周期分散互联

   <img src="./images/截屏2023-12-31 18.40.21.png" alt="截屏2023-12-31 18.40.21" style="zoom:50%;" />

   各指令执行过程简述：

   FI阶段：

   IR <- M[PC]; MemRd, IRWr, IroD=0

   PC <- (PC) + 4; ALuSrcA=0,ALUSrcB=01,ALUCtrl=+,PCSrc=00,PCWr

   ID阶段：

   A <- RF[IR(25-21)]

   B <- RF[IR(20-16)]

   ALUOut <- (PC) + SigExt(IR(15-0)<<2); ALUSrcA=0,ALUSrcB=11,ALUCtrl=+

   EX阶段：

   lw/sw: ALUOut <- (A) + SigExt(IR(15-0)); ALUSrcA=1,ALUSrcB=10,ALUCtrl=+

   add: ALUOut <- (A) op (B); ALUSrcA=1,ALUSrcB=00,ALUCtrl=op

   beq: Z<- (A) - (B), if(Z) PC <- (ALUOut); ALUSrcA=1,ALUSrcB=00, ALUCtrl=-,PCSrc=0,PCWrcCond=1

   j: PC <- PC[31-28] || IR[25-0] <<2; PCSrc=10,PCWr

   MA阶段：

   lw: MDR <- M[ALUOut]; MemRd, IorD=1

   sw: M[ALUOut] <- (B); MemWr, IorD=1

   add: RF[IR(15-11)] <- (ALUOut); MemtoReg=0, RegDst=1, RegWr

   WB阶段：

   lw: RF[IR(20-16)] <- (MDR); MemtoReg=1, RegDst=0, RegWr

3. 多周期单总线

   <img src="./images/截屏2023-12-31 19.07.04.png" alt="截屏2023-12-31 19.07.04" style="zoom:50%;" />

   各指令执行过程简述：

   FI阶段：

   clk1: MAR <- (PC), A <- (PC); PCOe~L~, PCOe~H~, AWr, MARWr

   clk2: IR <- M[MAR]; MemOe, MemRd, IRWr

   clk3: B <- 4; ExtSel=10, BWr, ImmOe~L~, ImmOe~H~

   clk4: PC <- (PC) + 4; PCWr, ALUOe, ALUCtrl=+

   ID阶段:

   clk5: A <- RF[IR[25-21]]; RegSel=00,RegOe,AWr

   EX/MA/WB阶段：

   lw:

   clk6: B <- SigExt(IR(15-0)); ExtSel=00, BWr, ImmOe~H~, ImmOe~L~

   clk7: MAR <- (A) + (B), ALUCtril=+, ALUOe, MARWr

   clk8: RF[IR(20-16)] <- M[MAR]; MemRd, MemOe,RegSel=01, RegWr

   sw: 

   clk6: B <- SigExt(IR(15-0)); ExtSel=00, BWr, ImmOe~H~, ImmOe~L~

   clk7: MAR <- (A) + (B), ALUCtril=+, ALUOe, MARWr

   clk8: MDR <- (RF[IR(20-16)]); MDRSrc=0, MDRWr, RegOe, RegSel=01

   clk9: M[MAR] <- MDR; MemWr

   add:

   clk6: B <- (RF[IR(20-16)]; RegOe, RegSel=01, BWr

   clk7: RF[IR(15-11)] <- (A) op (B); ALUCtrl=op, ALUOe, RegWr, RegSel= 10

   beq:

   clk6: B <- (RF[IR(20-16)]); RegOe, RegSel=01, BWr

   clk7: Z <- (A) - (B) if Z==0 end else A <- (PC); ALUCtrl=-,PCOe~H~, PCOe~L~,AWr

   clk8: B <- SigExt(IR(15-0)<<2); BWr, ExtSel=01, ImmOe~L~,ImmOe~H~

   clk9: PC <- (A) + (B); ALUOe, PCWr, ALUCtrl=+

   j:

   clk6: PC <- PC[31-28] || IR[25-0] <<2; PCWr, ExtSel=11, ImmOe~L~,ImmOe~H~

4. 多周期双/三总线

   <img src="./images/截屏2023-12-31 19.40.39.png" alt="截屏2023-12-31 19.40.39" style="zoom:50%;" />

   各指令执行过程简述：

   FI阶段：

   Clk1: MAR <- (PC); PCOe, GOe, Dir=1, MARWr

   clk2: IR <- M[MAR]; MemOe, MemRd, IRWr

   clk3: A <- (PC) + 4; ALUCtrl=+, ImmIe, Extsel=10, PCOe, AWr

   clk4: PC <- (A); AOe, PCWr, PCSrc=1

   ID/EX/MA/WB阶段：

   lw:

   clk5: A <- (RF[IR(25-21)] + SigExt(IR(15-0)); ImmOe, ExtSel=00, Reg1Oe, AWr, ALUCtrl=+

   clk6: MAR <- (A); AOe, MARWr

   clk7: R[IR(20-16)] <- M[MAR]; GOe, Dir=1, MemOe, MemRd, RegWr

   sw:

   clk5: A <- (RF[IR(25-21)] + SigExt(IR(15-0)); ImmOe, ExtSel=00, Reg1Oe, AWr, ALUCtrl=+

   clk6: MAR <- (A); AOe, MARWr

   clk7: MDR<- RF[IR(20-16)]; GOe, Dir=0,Reg2Oe,MDRSrc=0,MDRWr

   Clk8: M[MAR] <- (MDR); MemWr

   add:

   clk5: A <- (RF[IR(25-21)) op (RF[IR(20-16)]); AWr, ALUCtrl=op, Reg1Oe, Reg2Oe

   clk6: RF[IR(15-11)] <- (A); AWr, RegWr

   beq:

   clk5: Z <- (RF[IR(25-21)) op (RF[IR(20-16)]) if Z==0 end; AWr, ALUCtrl=op, Reg1Oe, Reg2Oe

   clk6: A <- (PC) + SigExt(IR(15-0) << 2); AWr, ImmOe, PCOe, ExtSel=01, ALUCtrl=+

   clk7: PC <- (A); PCSrc=1, PCWr, AOe

   j:

   clk5: PC <- PC[31-28] || IR[25-0] <<2; ExtSel=11, ImmOe, PCSrc=0, PCWr

   <img src="./images/截屏2023-12-31 20.02.33.png" alt="截屏2023-12-31 20.02.33" style="zoom:50%;" />

   三总线不再做具体分析

5. 流水CPU

   a. 原理：将指令执行过程划分为不同阶段(FI,ID,EX,MA,WB)每个阶段沿用不同的数据通路资源，多个在不同阶段执行的指令可以同时出现在数据通路中

   b. 流水线冒险：

   结构冒险：由于指令间争夺一个无法共享访问的硬件造成

   数据冒险：不同指令的资源利用存在顺序关系，必须前一条写回后一条才能操作

   控制冒险：条件转移会导致后续可能不会执行的指令进入流水线，故执行无效

   c. 流水线性能：

   ​	吞吐率：单位时间内完成的指令数

   ​	加速比：与非流水线的执行速度比

   ​	效率：流水线执行n个任务非流水的总占用的时间和流水化后的占用时间比（排空时间和建立时间）

   <img src="./images/截屏2023-12-31 20.22.07.png" alt="截屏2023-12-31 20.22.07" style="zoom:50%;" />

### 5. 性能指标

CPI每条指令的时钟周期数

平均CPI：指令系统的平均每条指令CPI：$\frac{\sum(指令数量_i\cdot \mathrm{CPI}_i )}{总指令数}$

