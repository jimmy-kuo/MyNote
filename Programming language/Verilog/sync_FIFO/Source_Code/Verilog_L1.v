/* Verilog 学习笔记 - 1 */

// @`13
// 2017年6月6日


/* 1.1 什么是Verilog HDL? */ 
//----------------------------------------------------------------------------------------------------------------------
// Verilog HDL (Hardware Description Language) 是一种硬件描述语言，可以在算法级、门级到开关级的多种抽象设计层次上对数字系统建模。
// 它可以描述设计的行为特性、数据流特性、结构组成以及包含响应监控和设计验证方面的时延和波形产生机制。此外，verilog提供了编程语言接口，
// 通过该接口用户可以在模拟、验证期间从外部访问设计，包括模拟的具体控制和运行。
// Verilog 不仅定义了语法，而且对每个语法结构都定义了清晰的模拟、仿真语义。因此，用这种语言编写的模型能够使用 Verilog 仿真器进行验证。 
// Verilog 从C语言中继承了多种操作符和结构，所以从结构上看两者有很多相似之处。
// Verilog HDL是你在开发 FPGA 、ASIC 时使用的语言，跟开发软件使用 C语言一个道理。


/* 1.2 Verilog的历史 */
//----------------------------------------------------------------------------------------------------------------------
// Verilog HDL是由GDA(Gateway Design Automation)公司的PhilMoorby在1983年末首创的，最初只设计了一个仿真与验证工具，之后又陆续开发了相关的故障模拟与时序分析工具。
// 1985年Moorby推出它的第三个商用仿真器Verilog-XL,获得了巨大的成功，从而使得 Verilog HDL 迅速得到推广应用。1989年CADENCE公司收购了GDA公司，使得 Verilog HDL成为了该公司的独家专利。
// 1990年CADENCE公司公开发表了Verilog HDL,并成立LVI组织以促进Verilog HDL成为IEEE标准，即IEEE Standard 1364-1995. 
// Verilog-1995后的版本是Verilog 2001，称作Verilog 2.0。
// SystemVerilog 是近几年发展起来的，称作 Verilog 3.0.
// 本书讲述的是Verilog-1995。对于大多数开发FPGA的人来说，掌握Verilog-1995是必须的，因为大部分已有设计都是基于Verilog 1995的。


/* 1.3 Verilog的主要描述能力 */
//----------------------------------------------------------------------------------------------------------------------
// Verilog 是最佳的寄存器传输级设计语言和门级描述语言，这是Verilog成功的根本。
// 下面列出的是 Verilog 硬件描述语言的主要能力（不耐烦的读者可以略过）：

// (1)基本逻辑门，
//     例如 and、
//     or 和 
//     nand 等都内置在语言中。 

// (2)用户定义原语（UDP）创建的灵活性。用户定义的原语既可以是组合逻辑原语，也可以是时序逻辑原语。 

// (3)开关级基本结构模型，例如 pmos 和 nmos 等也被内置在语言中。 

// (4)提供显式语言结构指定设计中的端口到端口的时延及路径时延和设计的时序检查。 

// (5)可采用三种不同方式或混合方式对设计建模。这些方式包括：
//     行为描述方式—使用过程化结构建模；
//     数据流方式—使用连续赋值语句方式建模；
//     结构化方式—使用门和模块实例语句描述建模。 

// (6)Verilog HDL 中有两类数据类型：
//     线网数据类型和寄存器数据类型。
//     线网类型表示构件间的物理连线，而寄存器类型表示抽象的数据存储元件。 

// (7)能够描述层次设计，可使用模块实例结构描述任何层次。 

// (8)设计的规模可以是任意的；语言不对设计的规模（大小）施加任何限制。 
// (9)Verilog HDL 不再是某些公司的专有语言而是 IEEE 标准。 
// (10)人和机器都可阅读 Verilog 语言，因此它可作为 EDA 的工具和设计者之间的交互语言。 
// (11)Verilog HDL 语言的描述能力能够通过使用编程语言接口（PLI）机制进一步扩展。PLI 是允许外部函数访问 Verilog 模块内信息、允许设计者与模拟器交互的例程集合。 
// (12)设计能够在多个层次上加以描述，从开关级、门级、寄存器传送级（RTL）到算法级，包括进程和队列级。 
// (13)能够使用内置开关级原语在开关级对设计完整建模。 
// (14)同一语言可用于生成模拟激励和指定测试的验证约束条件，例如输入值的指定。 
// (15)Verilog HDL 能够监控模拟验证的执行，即模拟验证执行过程中设计的值能够被监控和显示。这些值也能够用于与期望值比较，在不匹配的情况下，打印报告消息。 
// (16)在行为级描述中，Verilog HDL 不仅能够在 RTL 级上进行设计描述，而且能够在体系结构级描述及其算法级行为上进行设计描述。 
// (17)能够使用门和模块实例化语句在结构级进行结构描述。 
// (18)Verilog HDL 还具有内置逻辑函数，例如 
//     &（按位与）和 
//     |（按位或）。 

// (19)对高级编程语言结构，例如
//     条件语句、
//     情况语句和
//     循环语句，   语言中都可以使用。 

// (20)可以显式地对并发和定时进行建模。 
// (21)提供强有力的文件读写能力。 
// (22)语言在特定情况下是非确定性的，即在不同的模拟器上模型可以产生不同的结果；例如，事件队列上的事件顺序在标准中没有定义。


/* 2.1 Verilog-模块 */
// =====================================================
// 模块是Verilog 的基本描述单位，用于描述某个设计的功能或结构及其与其他模块通信的外部端口。
// 一个设计的结构可使用      开关级原语、      门级原语和       用户定义的原语方式描述; 
// 设计的数据流行为使用      连续赋值语句进行描述;         时序行为使用过程结构描述。
// 一个模块可以在另一个模块中使用。


// 一个模块的基本语法如下：
module module_name(port_list) ; 
// ...
endmodule
[/** 注意最后有个分号 */]


// 说明部分用于定义不同的项，例如模块描述中使用的寄存器和参数。语句定义设计的功能和结构。
// 说明部分和语句可以散布在模块中的任何地方；但是变量、寄存器、线网和参数等的说明部分必须在使用前出现。
// 为了使模块描述清晰和具有良好的可读性, 
// 最好将所有的说明部分放在语句前。本书中的所有实例都遵守这一规范。



// Demo 一个半加器电路的模块。
module HalfAdder (A, B, Sum, Carry) ; 

input A, B; //输入
output Sum, Carry;//输出

assign #2 Sum = A ^ B;//赋值
assign #5 Carry = A & B;//赋值

endmodule


// 模块的名字是  HalfAdder。
//     模块有4个端口: 
//         两个输入端口A和B，
//         两个输出端口Sum和Carry。
//     // 由于没有定义端口的位数, 所有端口大小都为1位；
//     // 同时, 由于没有各端口的数据类型说明, 这四个端口都是 [线网] 数据类型。
//     // 模块包含两条描述半加器数据流行为的连续赋值语句。
//     // 从这种意义上讲，这些语句在模块中出现的顺序无关紧要，这些语句是 [并发] 的。每条语句的执行顺序依赖于发生在变量A和B上的事件。

// 在模块中，可用下述方式描述一个设计：
// 1) 数据流方式;
// 2) 行为方式;
// 3) 结构方式;
// 4) 上述描述方式的混合。


/* 2.2 Verilog-时延 */
// ====================================================================
// Verilog HDL模型中的所有时延都根据时间单位定义。下面是带时延的连续赋值语句实例。

assign #2 Sum = A ^ B;
// # 2指2个时间单位。

// 使用编译指令将时间单位与物理时间相关联。这样的编译器指令需在模块描述前定义，
// 如下所示:
`timescale 1ns /100ps


// 此语句说明时延时间单位为1 ns    并且时间精度为100ps 
// (时间精度是指所有的时延必须被限定在0.1ns内)。
// 如果此编译器指令所在的模块包含上面的连续赋值语句, 
// #2 代表2ns。如果没有这样的编译器指令, 
// Verilog HDL 模拟器会指定一个缺省时间单位。IEEE Verilog HDL 1995 标准中没有规定缺省时间单位。

// 注意：这里讲的是IEEE Verilog 1995的语法，我们将在后文讲述IEEE Verilog 2001与1995的不同。


/* 2.3 Verilog-assign语句 */
// ====================================================================
// 本节讲述连续赋值语句。在连续赋值语句中，某个值被指派给线网变量。连续赋值语句的语法为: 

assign [delay] LHS_n e t = RHS_expression;

//右边表达式使用的 
[/* 操作数无论何时发生变化 , 右边表达式都重新计算 , */] 
//并且在指定的时延后变化值被赋予左边表达式的线网变量。时延定义了右边表达式操作数变化与赋值给左边表达式之间的持续时间。
[/* 如果没有定义时延值, 缺省时延为0。 */]


// DEMO2 解码器电路
`timescale 1ns/ 1ns  
module Decoder2x4 (A, B, EN, Z);

input A, B, EN;
output [0 :3] Z;
wire Abar, Bbar;

assign #1 Abar = ~ A; // 语句1。
assign #1 Bbar = ~ B; // 语句2。
assign #2 Z[0] = ~ (Abar & Bbar & EN ) ; // 语句3。
assign #2 Z[1] = ~ (Abar & B & EN) ; // 语句4。
assign #2 Z[2] = ~ (A & Bbar & EN) ; // 语句5。
assign #2 Z[3] = ~ ( A & B & EN) ; // 语句6。

endmodule

// 解释
[预编译指令]
// 以反引号“ ` ”开始的第一条语句是编译器指令, 编译器指令` timescale 将模块中所有时延的单位设置为1 ns，时间精度为1 ns。
// 例如，在连续赋值语句中时延值# 1和# 2分别对应时延1ns和2ns。
[网线型数据类型]
// 模块Decoder2x4有3个输入端口和1个4位输出端口。线网类型说明了两个连线型变量 Abar 和 Bbar (连线类型是线网类型的一种)。此外，模块包含6个连续赋值语句。
// 当E N在第5 ns变化时,语句3、4、5和6执行。这是因为E N是这些连续赋值语句中右边表达式的操作数。Z[ 0 ]在第7 ns时被赋予新值0。当A在第15 ns变化时, 语句1、5和6执行。执行语句5和6不影响Z[ 0 ]和Z[ 1 ]的取值。执行语句5导致Z[ 2 ]值在第17 ns变为0。执行语句1导致A b a r在第16 ns被重新赋值。由于A b a r的改变，反过来又导致Z[ 0 ]值在第18 n s变为1。
// 请注意连续赋值语句是如何对电路的数据流行为建模的；这种建模方式是隐式而非显式的建模方式。
// 此外,
[连续赋值语句是并发执行的]
// 也就是说各语句的执行顺序与其在描述中出现的顺序无关。



/* 2.4 Verilog-initial语句 */
// ====================================================================
// initial语句：在仿真中只执行一次，用于初始化变量，描述一次性行为，在仿真时刻0开始执行。
// 下面是initial语句的示例：

`timescale 1ns/1ns 

module Test(Pop,Pid);

output Pop,Pid;
reg Pop,Pid;

initial

begin
Pop = 0;//语句1。
Pid = 0;//语句2。
Pop = #5 1;//语句3。
Pid = #3 1;//语句4。
Pop = #6 0;//语句5。
Pid = #2 0;//语句6。
end

endmodule


[nitial语句包含一个顺序过程。]
// 这一顺序过程在0ns时开始执行，并且在顺序过程中
[所有语句全部执行完毕后,initial语句永远挂起。]
// 这一顺序过程包含带有定义语句内时延的分组过程赋值的实例。语句1和2在0ns时执行。第三条语句也在0时刻执行,
// 导致Pop在第5ns时被赋值。语句4在第5ns执行,并且Pid在第8ns被赋值。
// 同样，Pop在14ns被赋值0，Pid在第16ns被赋值0。第6条语句执行后，initial语句永远被挂起。第8章将更详细地讲解initial语句。


/* 2.5 Verilog-always语句 */
// ====================================================================
[always语句总是循环执行],
// 或者说此语句重复执行。只有
[只有 寄存器类型数据(REG) 能够在这种语句中被赋值]。
// 寄存器类型数据在被赋新值前保持原有值不变。
// 所有的初始化语句和always语句在0时刻并发执行。


// DEMO 1位全加器电路
module FA_Seq(A,B,Cin,Sum,Cou)t;

input A,B,Cin;
output Sum,Cout;
reg Sum,Cout;
reg T1,T2,T3;

always @(A or B or Cin)
begin
Sum = (A^B)^Cin;
T1 = A&Cin;
T2 = B&Cin;
T3 = A&B;

Cout=(T1|T2)|T3;
end 

endmodule


// 模块FA_Seq有三个输入和两个输出。由于Sum、Cout、T1、T2和T3在always语句中被赋值,它们被说明为reg类型(reg是寄存器数据类型的一种)。
[always语句中有一个与事件控制(紧跟在字符@后面的表达式)]。
// 这意味着只要A、B或Cin上发生事件，即A、B或Cin之一的值发生变化，顺序过程就执行。

[相关联的顺序过程(begin-end对)。]
// 在顺序过程中的语句顺序执行，并且在顺序过程执行结束后被挂起。顺序过程执行完成后，always语句再次等待A、B或Cin上发生的事件。
// 在顺序过程中出现的语句是过程赋值模块化的实例。模块化过程赋值在下一条语句执行前完成执行。过程赋值可以有一个可选的时延。

[时延可以细分为两种类型]:
    // 1)语句间时延: 这是时延语句执行的时延。
    // 2)语句内时延: 这是右边表达式数值计算与左边表达式赋值间的时延。

// 下面是语句间时延的示例：

Sum = (A^B)^Cin; 
#4 T1 = A&Cin;
// 在第二条语句中的时延规定赋值延迟4个时间单位执行。就是说，在第一条语句执行后等待4个时间单位，然后执行第二条语句。

// 下面是语句内时延的示例。

Sum=  #3 (A^B)^Cin;
// 这个赋值中的时延意味着首先计算右边表达式的值,等待3个时间单位，然后赋值给Sum。


/* 2.6 Verilog的结构化描述形式(???) */
// ===============================

// 在VerilogHDL中可使用如下方式描述结构:
// 1)内置门原语(在门级)；
// 2)开关级原语(在晶体管级)；
// 3)用户定义的原语(在门级)；
// 4)模块实例(创建层次结构)。

// 在这一实例中，模块包含门的实例语句，也就是说包含内置门xor、and和or的实例语句。门实例由线网类型变量S1、T1、T2和T3互连。由于没有指定的顺序,门实例语句可以以任何顺序出现；图中显示了纯结构；xor、and和or是内置门原语；X1、X2、A1等是实例名称。紧跟在每个门后的信号列表是它的互连；列表中的第一个是门输出，余下的是输入。例如，S1与xor门实例X1的输出连接，而A和B与实例X1的输入连接。


// 4位全加器的结构描述形式。
module FourBitFA(FA,FB,FCin,FSum,FCout); 

parameter SIZE=4;

input [SIZE:1]FA,FB;
output [SIZE:1]FSum
input FCin;
input FCout;

wire [1:SIZE－1]FTemp;

FA_Str

FA1(.A(FA[1]),.B(FB[1]),.Cin(FCin),.Sum(FSum[1]),.Cout(FTemp[2])),
FA2(.A(FA[2]),.B(FB[2]),.Cin(FTemp[1]),.Sum(FSum[2]),.Cout(FTemp[2])),
FA3(FA[3],FB[3],FTemp[2],FSum[3],FTemp[3],
FA4(FA[4],FB[4],FTemp[3],FSum[4],FCout);

endmodule


//在这一实例中，模块实例用于建模4位全加器。在模块实例语句中，端口可以与名称或位置关联。前两个实例FA1和FA2使用命名关联方式，也就是说，
// 端口的名称和它连接的线网被显式描述
[（每一个的形式都为“.port_name(net_name)）]
// 最后两个实例语句，实例FA3和FA4使用位置关联方式将端口与线网关联。这里关联的顺序很重要，
// 例如，在实例FA4中，第一个FA[4]与FA_Str的端口A连接，第二个FB[4]与FA_Str的端口B连接，余下的由此类推。



/* 2.7 Verilog-混合设计描述方式 */
// ===============================

// 在模块中，结构的和行为的结构可以自由混合。也
// 就是说，模块描述中可以包含
//     实例化的门、
//     模块实例化语句、
//     连续赋值语句  
//     以及always语句和initial语句的混合。
// 它们之间可以相互包含。来自always语句和initial语句
[切记只有寄存器类型数据可以在这两种语句中赋值]
//的值能够驱动门或开关，而来自于门或连续赋值语句（只能驱动线网）的值能够反过来用于触发always语句和initial语句。

// DEMO 混合设计方式的1位全加器实例。

module FA_Mix (A, B, Cin, Sum, Cout); 

input A,B, Cin;
output Sum, Cout;

reg Cout;
reg T1, T2, T3;

wire S1;
xor X1(S1, A, B); // 门实例语句。

always @( A or B or Cin ) 

begin 
T1 = A & Cin;
T2 = B & Cin;
T3 = A & B;
Cout = (T1| T2) | T3;
end

assign Sum = S1 ^ Cin; // 连续赋值语句。

endmodule


// 只要A或B上有事件发生，门实例语句即被执行。只要A、B或Cin上有事件发生，
// 就执行always 语句，并且只要S1或Cin上有事件发生，就执行连续赋值语句。


/* 2.8 Verilog-设计模拟 */
// =========================================
 
// Verilog HDL不仅提供描述设计的能力，而且提供对激励、控制、存储响应和设计验证的建模能力。
// 激励和控制可用初始化语句产生。验证运行过程中的响应可以作为“变化时保存”或作为选通的数据存储。
// 最后，设计验证可以通过在初始化语句中写入相应的语句自动与期望的响应值比较完成。

// 下面是测试模块Top的例子。该例子测试2 . 3节中讲到的FA Seq模块。

`timescale 1 ns/1 ns 

module Top; // 一个模块可以有一个空的端口列表。

reg PA, PB, PCi;
wire PCo, PSum;

// 正在测试的实例化模块：

FA_Seq F1(PA, PB, PCi, PSum, PC)o; // 定位。

initial

begin:  ONLY_ONCE

reg [3:0] Pal;
// 需要4位, Pal才能取值8。

for (Pal = 0; Pal < 8; Pal = Pal + 1)

begin
{PA, PB, PCi} = Pal;

#5 $display("PA, PB, PCi = %b% b% "b, PA, PB, PCi,PCo, PSum=%b%b ”, PCo, PSum) ;
end

end

endmodule


// 在测试模块描述中使用位置关联方式将模块实例语句中的信号与模块中的端口相连接。
// 也就是说，PA连接到模块FA Seq的端口A，P B连接到模块FA S e q的端口B，依此类推。
// 注意初始化语句中使用了一个f o r循环语句，在PA、P B和P C i上产生波形。for 循环中的第一条赋值语句用于表示合并的目标。自右向左，右端各相应的位赋给左端的参数。
// 初始化语句还包含有一个预先定义好的系统任务。系统任务$d i s p l a y将输入以特定的格式打印输出。
// 系统任务$ d i s p l a y调用中的时延控制规定$d i s p l a y任务在5个时间单位后执行。
// 这5个时间单位基本上代表了逻辑处理时间。即是输入向量的加载至观察到模块在测试条件下输出之间的延迟时间。
// 这一模型中还有另外一个细微差别。P a l在初始化语句内被局部定义。
// 为完成这一功能，初始化语句中的顺序过程（ b e g i n - e n d）必须标记。
// 在这种情况下, ONLY O N C E是顺序过程标记。如果在顺序过程内没有局部声明的变量，就不需要该标记。测试模块产生的波形如图2 - 7显示。下面是测试模块产生的输出。


// DEMO 交叉连接的与非门
// 验证与非门交叉连接构成的R S F F模块的测试模块如图2 - 8所示。

`timescale 10ns / 1ns 

module RSFF (Q, Qbar, R, S) ;

output Q, Qbar;
input R, S;

nand #1 (Q, R, Qbar) ;
nand #1 (Qbar, S, Q,) ;

// 在门实例语句中，实例名称是可选的。

endmodule

module Test;

reg TS, TR;

wire TQ, TQb;

// 测试模块的实例语句：

RS_FF NSTA ( .Q(T Q), .S(T S), .R(T R), .Q b a r(T Q b));

//采用端口名相关联的连接方式。

// 加载激励：

initial

begin:

TR = 0;
TS = 0;

#5 TS = 1;
#5 TS = 0;

TR = 1;

#5 TS = 1;

TR = 0;

#5 TS = 0;
#5 TR = 1;

end

//输出显示：

initial

$monitor("At time %t ," , $ t i m e,"TR = %b, TS=%b, TQ=%b, TQb= %b"T,R , TS, TQ, TQ)b ;

endmodule

RS_FF模块描述了设计的结构。在门实例语句中使用门时延；例
如，第一个实例语句中的门时延为1个时间单位。该门时延意味着如果R或Qbar假定在T时刻变化，Q将在T+ 1时刻获得计算结果值。
模块Te s t是一个测试模块。测试模块中的R S F F用实例语句说明其端口用端口名关联方式连接。
在这一模块中有两条初始化语句。第一个初始化语句只简单地产生T S和T R上的波形。这一初始化语句包含带有语句间时延的程序块过程赋值语句。
第二条初始化语句调用系统任务$m o n i t o r。这一系统任务调用的功能是只要参数表中指定的变量值发生变化就打印指定的字符串。
















