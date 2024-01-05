

## 介质访问控制子层

### 1. 信道共享问题

1. motive：多用户可能共享使用相同的信道，如同时使用则可能发生碰撞，导致大家发送的frame均无效。因此需要对信道进行分配
2. 静态信道划分：FDM，CDM，TDM，无法解决突发流量的问题(每个user不用也会占据一定信道)
3. 动态划分：分为有冲突/无冲突/有限冲突

### 2. 多路访问协议

1. ALOHA

   Pure ALOHA：若想发送，直接发送，若冲突，随机重传

   Slot ALOPHA：将时间分为时间槽，只有一个时间槽开始时才能发送frame

2. CSMA载波侦听

   1-persistent：持续监听，若空闲立即发送信号

   Non-persistent：当信道忙，随机等待一段时间再次监听尝试

   p-persistent：同样分时间槽，信道空闲时p概率直接发送，1-p推迟到下一slot尝试监听并发送

   CSMA-CD：碰撞检测载波侦听，传输过程中持续监听，发生碰撞停止传输并等待随机事件再发送

3. 冲突避免

​	BitMap：N个冲突slot，所有站点在冲突时间内预约slot位置，传输时根据预约的站点的编号顺序发送

​	Token RIng：拥有令牌可发送，并把令牌传递给下一个站

​	二进制倒计数：竞争期内所有要使用信道的站从高到低发送自己的地址编号的每一位，若结果将这些编号位取或，站若看到 1 且自己发送 0 则放弃

4. 有限竞争协议

   将多个站点分组，组内竞争，组间无竞争

5. 无线LAN协议：MACA

   隐藏站问题：给B发，C也给B发，A，C无法相互感知

   暴露站问题：B给A发C可以感知，但对C给D发送数据无影响

   MACA：要发送数据是先发送RTS请求发送，接收方返回CTS允许发送

### 3. 以太网

1. 经典以太网：

​	a. 物理层：使用曼切斯特编码，所有线缆通过集线器连接在一起(需使用CSMA/CD协议)

​	b. MAC子层：帧格式：

​	|物理层添加8bytes前缀|目的MAC地址6byte(全1为广播)|源MAC地址6byte|

​	|类型/Length2byte|Data-0\~1500byte|

​	|Pad0\~46byte(链路层要求帧最小64，最大1518byte)|4byte CRC|

​	*why最小64byte？检测到冲突的最长时间，这样可以区分有效帧和垃圾帧（小于64即为垃圾帧）

​	c. MAC子层协议：

​	1-坚持CSMA/CD+二进制指数后退：若发生collision，设为第i次碰撞，则随机(0,2^i^)个时间槽后再次尝试，i=16为传输失败

2. 交换式以太网

   使用交换机而不是集线器实现数据的分发，不会产生冲突

3. 快速以太网：100BaseT 速度快十倍，线长减10倍200m

4. 千兆以太网：光线传输，200m，pad=512B

5. 万兆以太网：...

### 4. 无线LAN

1. mac子层协议：

   CSMA-CA

   准备发送前先进行随机Backoff，Backoff结束再次监听并发送

   发送时通过RTS和CTS预约信道，当其他准备发送的站点接受到RTS/CTS则停止Backoff计时，等信道再次空闲再继续完成计时

   使用ACK推断是否发生冲突，若冲突二进制指数backoff

2. 帧格式：

​	三个地址：根据来自AP还是发往AP填入不同数据

​	发往：AP,src,dst 来自：dst,AP,src

### 5. 蓝牙

​	主设备+从设备

### 6. RFID

### 7. 数据链路层交换

prob: 使用一个或多个交换机构成一个局域网？

1. 学习网桥

   a. 泛洪：当dst未知时向除发送端口的所有端口传送数据

   b. 后向学习：根据frame中得src在交换表中登记相应的MAC地址和port的对应

2. 生成树

   为提高网络健壮性，增加冗余路径，但是会广播风暴

   选择一个根，并生成生成树

### 8. VLAN

prob：希望对一个LAN下面的主机划分为不同的广播域

VLAN：路由器给每个端口一个VLAN标识符，并在传输时给数据包打上标签，使其只能在一个VLAN标签内传播

同时VLAN使用802.1Q frame给是，增加Tag字段






