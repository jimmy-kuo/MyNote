[利用verilog实现FIFO]
/* 摘自 http://lihaichuan.blog.51cto.com/498079/1307686 */

// 摘要：本文先介绍了一下关于FIFO的基本概念，工作原理，功能，同步与异步的分类等。
// 然后基于RAM实现了一个同步FIFO。该FIFO通过巧妙地应用地址位和状态位的结合实现对空、满标志位的控制。从而减小了设计的复杂度。

[关键词：FIFO，同步，仿真，quartus。]
#1. [FIFO简介]

// FIFO(FirstInputFirstOutput)一种先进先出的数据缓存器，
// 先进入的数据先从FIFO缓存器中读出，与RAM相比没有外部读写地址线,使用比较简单，
// 但只能顺序写入数据，顺序的读出数据，
// 不能像普通存储器那样可以由地址线决定读取或写入某个指定的地址。

#1.1 [FIFO的工作原理]

// 对于FIFO，读写指针都指向一个存储器的初始位置，每进行一次读写操作，相应的指针就递增一次，指向下一个存储器位置。
// 当指针移动到了存储器的最后一个位置时，它又重新跳回初始位置。在FIFO非满或非空的情况下，这个过程将随着读写控制信号的变化一直进行下去。
// 如果FIFO处于空的状态，下一个读动作将会导致向下溢(underflow)，一个无效的数据被读人；同样，对于一个满了的FIFO，进行写动作将会导致向上溢出(overflow)，一个有用的数据被新写入的数据覆盖。
// 这两种情况都属于误动作，因此需要设置满和空两个信号，对满信号置位表示FIFO处于满状态，对满信号复位表示FIFO非满，还有空间可以写入数据；对空信号置位表示FIFO处于空状态，对空信号复位表示FIFO非空，
// 还有有效的数据可以读出。
// FIFO设计的难点在于怎样判断FIFO的空/满状态。
// 为了保证数据正确的写入或读出，而不发生溢出或读空的状态出现，
// 必须保证FIFO在满的情况下，不能进行写操作。在空的状态下不能进行读操作。

#1.2 [FIFO的一些重要参数]

// FIFO的宽度：也就是英文资料里常看到的THEWIDTH，它指的是FIFO一次读写操作的数据位，就像MCU有8位和16位，ARM32位等等。
// FIFO的深度：THEDEEPTH，它指的是FIFO可以存储多少个N位的数据（如果宽度为N）。如一个8位的FIFO，若深度为8，它可以存储8个8位的数据，深度为12，就可以存储12个8位的数据。
// 满标志：FIFO已满或将要满时由FIFO的状态电路送出的一个信号，以阻止FIFO的写操作继续向FIFO中写数据而造成溢出（overflow）。
// 空标志：FIFO已空或将要空时由FIFO的状态电路送出的一个信号，以阻止FIFO的读操作继续从FIFO中读出数据而造成无效数据的读出（underflow）。
// 读指针：指向下一个读出地址。读完后自动加1。
// 写指针：指向下一个要写入的地址的，写完自动加1。
// FIFO读时钟：读操作所遵循的时钟，在每个时钟沿来临时读数据。
// FIFO写时钟：写操作所遵循的时钟，在每个时钟沿来临时写数据。

#1.3 [FIFO的功能]

// FIFO作为一种先进先出的缓存，适合于对连续的数据流进行缓存。可将数据储存集中起来。减少频繁的总线操作。减少CPU的负担。
// FIFO一般用于不同时钟域之间的数据传输。比如FIFO的一端是AD数据采集，另一端为PCI总线，那么在两个不同的时钟域间就可以采用FIFO来作为数据缓冲。
// 另外对于不同宽度的数据接口也可以用FIFO，例如单片机位8位数据输出，而DSP可能是16位数据输入，在单片机与DSP连接时就可以使用FIFO来达到数据匹配的目的。

#2. [FIFO的分类]

// 根均FIFO工作的时钟域，可以将FIFO分为同步FIFO和异步FIFO。同步FIFO是指读时钟和写时钟为同一个时钟。
// 在时钟沿来临时同时发生读写操作。异步FIFO是指读写时钟不一致，读写时钟是互相独立的。
// 对于异步FIFO一般有两种理解，一种是读写操作不使用时钟，而是直接采用wr_en(WriteEnabled)和rd_en(ReadEnabled)来进行控制；
// 另一种，是指在FPGA和ASIC设计中，异步FIFO具有两个时钟的双口FIFO,读些操作在各自的时钟延上进行，在两个不同时钟下，可以同时进行读或写。
// 异步FIFO在FPGA设计汇总占用的资源比同步FIFO大很多，所以尽量采用同步FIFO设计。
// 而当物理系统中存在多个时钟信号，并且需要在这几个时钟域之间传输数据的时候，寄存器会由于时钟信号的频率不匹配而产生数据丢失等情况，
// 这个时候需要用异步FIFO来进行缓存，保证数据能够正确传输。所以异步FIFO功能更强。所以，对于一些常用的嵌入式环境中，如ARM系统内绝大部分外设接口都是异步FIFO。
// 由于异步FIFO的实现复杂。本文将实现的为同步FIFO。

#3. [同步FIFO的实现]

// FIFO存储器的实现目前主要是分为基于移位寄存器的类型和基于RAM的类型。本文要实现的是基于RAM的FIFO寄存器。

#3.1 [用verilog实现RAM]

// 本文编写了一个具有通用性的RAM的verilog代码。通过预编译宏定义RAM的深度和宽度为16和8，所以最后实现的是一个168的RAM。

`define DEL 1//用于检查输出的延迟
`define RAM_WIDTH 8//Ram的宽度
`define RAM_DEPTH 16//Ram的深度
`define ADDR_SZ 4//所需要的地址线位数

module ram16X8(clk,dataIn,dataOut,addr,wrN,oe);
    //inout[`RAM_WIDTH-1:0]data;
    input [`RAM_WIDTH-1:0]dataIn;//数据线
    input clk;
    input [`ADDR_SZ-1:0]addr;//地址线
    input wrN;//写选择线
    input oe;//允许输出线

    output [`RAM_WIDTH-1:0]dataOut;
    wire [`RAM_WIDTH-1:0]dataIn,dataOut;
    wire [`ADDR_SZ-1:0]addr;
    wire wrN,oe;
    //RAM
    reg[`RAM_WIDTH-1:0]mem[`RAM_DEPTH-1:0];
    assign#`DELdataOut=oe?`RAM_WIDTH'bz:mem[addr];
    always@(posedgeclk)begin
    if(!wrN)
    mem[addr]=dataIn;
    end
endmodule

// 值得注意的一点是，在输出数据到数据线时，
[必须要有个延时（代码中的DEL）。]
// 这是因为硬件对输出允许线的判断本来就有个时间，如果没有这个延时，则容易使得系统出错。

#3.2 [FIFO具体实现]

#3.2.1 [基本实现思路]

// 空/满标志的产生是FIFO的核心部分。如何正确设计此部分的逻辑,直接影响到FIFO的性能。
// 本文所应用的方法是分别将读、写地址寄存器扩展一位,将最高位设置为状态位,其余低位作为地址位,指针由地址位以及状态位组成。
// 巧妙地应用地址位和状态位的结合实现对空、满标志位的控制。当读写指针的地址位和状态位全部吻合的时候,读写指针经历了相同次数的循环移动,
// 也就是说,FIFO处于空状态(图1(a));如果读写指针的地址位相同而状态位相反,写指针比读指针多循环一次,标志FIFO处于满状态(图1(b))。
// 在synFIFO的实现中，这两个读写地址寄存器分别是wr_cntr,rd_cntr。

#3.2.2 [FIFO外部接口]

// 同步FIFO的对外接口包括时钟，清零，读请求，写请求，数据输入总线，数据输出总线，空以及满信号。下面分别对同步FIFO的对外接口信号作一描述：
// 1．时钟，输入，用于同步FIFO的读和写，上升沿有效；
// 2．清零，输入，异步清零信号，低电平有效，该信号有效时，FIFO被清空；
// 3．写请求，输入，低电平有效，该信号有效时，表明外部电路请求向FIFO写入数据；
// 4．读请求，输入，低电平有效，该信号有效时，表明外部电路请求从FIFO中读取数据；
// 5．数据输入总线，输入，当写信号有效时，数据输入总线上的数据被写入到FIFO中；
// 6．数据输出总线，输出，当读信号有效时，数据从FIFO中被读出并放到数据输出总线上；
// 7．空，输出，高电平有效，当该信号有效时，表明FIFO中没有任何数据，全部为空；
// 8．满，输出，高电平有效，当该信号有效时，表明FIFO已经满了，没有空间可用来存贮数据。
// 以上的八种外接接口分别对应synFIFO模块代码中的clk，rstN，wrN，rdN，dataIn，dataOut，empty,full。
// 3.2.3synFIFO代码

//FIFORAM
module synFIFO(dataIn,dataOut,clk,rstN,wrN,rdN,empty,full);
    input   [7:0]dataIn;
    input   clk,rstN,wrN,rdN;
    output  empty,full;
    output[7:0]dataOut;
    reg[4:0]wr_cntr,rd_cntr;
    wire[3:0]addr;
    /*调用ram16X8模块，当wrN为低平有效且full为0时才写，而rdN为低平有效且empy为0时才读*/
    ram16X8ram(.clk(clk),.dataIn(dataIn),.dataOut(dataOut),.addr(addr),.wrN(wrN||full),.oe(rdN||empty));
    always@(posedgeclkornegedgerstN)
    if(!rstN)wr_cntr<=0;
        else if(!wrN&&!full)wr_cntr<=wr_cntr+1;
            always@(posedgeclkornegedgerstN)
if(!rstN)rd_cntr<=0;
elseif(!rdN&&!empty)rd_cntr<=rd_cntr+1;
assignaddr=wrN?rd_cntr[3:0]:wr_cntr[3:0];
assignempty=(wr_cntr[3:0]==rd_cntr[3:0])&&!(wr_cntr[4]^rd_cntr[4]);
assignfull=(wr_cntr[3:0]==rd_cntr[3:0])&&(wr_cntr[4]^rd_cntr[4]);
endmodule
#4. [Quartus仿真]