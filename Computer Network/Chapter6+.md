6+

TCP协议

协议模型：支持面向连接的可靠字节流通讯



TCP段头：

4byte | source port 16bits | dst port 16btis |

4byte | seq number 32bits |

4byte | ack number 32bits 下一个期待字节|

4byte |TCP head length 4bits| CWR ECE 拥塞控制| URG紧急数据 | ACK确认号有效| PSH立即接受 | RST重置链接 | SYN 连接建立 | FIN 连接释放 | 窗口大小 16bits 流量控制 |

4byte |checksum 16bits | 紧急指针 16bits |

| 可选项 |



TCP连接建立：

三次握手：a. Client发送SYN=1 ACK=0 seq=x的TCP段 b. Sever接收后发送SYN=1 ACK=1 seq=y ack=x+1的段 c. Client发送SYN=0 ACK=1 seq=x+1 ack=y+1的常规数据包，此时连接建立

**注：TCP泛洪攻击：Client发送多个SYN=1连接请求占用资源但不完成后续动作

TCP连接释放：

四次挥手：a. Client发送FIN=1 ACK=1 seq=x ack=y的数据段表示准备释放连接

​		   b. Server发送ACK=1 seq=y ack=x+1的数据段，并进入关闭等待(期间不接受Client发送，但要把之前未传输的传输完)

​		c. 传输完成后Server发送FIN=1 ACK=1 seq=z ack=x+1的重复确认段表示数据传输完

​		d. 此时Client发送ACK=1 seq=x+1 ack=z+1并等待2MSL时间， 超时关闭连接

TCP滑动窗口(流量控制)：

发送方可通过接收方段中的window size调整自身的发送窗口

延迟确认：接收方可以等自身接收端口填满后在进行累积确认

Nagle：先发送第一次到达的数据字节，后续缓冲，知道前面发送被确认或者缓冲填满再发送

Clark：当发送窗口已经调整为0时，限制接收端只有在具备半空缓存或最大段长的空缓存时才向发出端发送窗口调整



TCP计时器管理：

prob：最佳的计时器时间？

solve：动态调整

​		RTT~n~ = $\alpha$RTT~n-1~ + (1-$\alpha$)M~n~

​		D~n~ = $\beta$D~n-1~ + (1-$\beta$)|RTT~n~ - M~n~|

​		next timeout = RTT~n~ + 4 * D~n~

** TCP有哪些计时器？1. 超时重传 2. 持续计时器(用于窗口探测，防止0size的死锁)

					3. 终止(2MSL关闭连接) 4. 保活计时器(查看另一端是否存在)



TCP拥塞控制

1. 确认时钟：ACK返回到发送端的速度反映了最慢链路的速度，据此控制发送端发送速度，避免拥塞
2. 慢速启动：设置初始拥塞窗口为1，每次发送数据ack后double，直到达到threshold值
3. 拥塞避免：达到threshold后，每次数据ack后窗口+1，若重传，threshold=size*0.5并重新慢速启动
4. 快重传：当收到3个接收方的重复确认，发送方进行快速重传
5. 快恢复：快重传触发后，threshold=size*0.5，size=threshold

**TCP CUBIC：由于大的延迟带宽乘积，使用关于最后一个重复确认以来的时间的立方函数确定拥塞窗口大小