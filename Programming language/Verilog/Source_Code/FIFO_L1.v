/******************************************************
A fifo controller verilog description.
******************************************************/
module fifo(datain, rd, wr, rst, clk, dataout, full, empty);

input [7:0] datain;
input rd, wr, rst, clk;

output [7:0] dataout;
output full, empty;

wire [7:0] dataout;

reg full_in, empty_in;
reg [7:0] mem [15:0];
reg [3:0] rp, wp;//其实是一个循环读写的过程,4位二进制数刚好16个状态，也即指示16个深度

assign full = full_in;
assign empty = empty_in;

// memory read out
assign dataout = mem[rp];

// memory write in
always@(posedge clk) begin
    if(wr && ~full_in) mem[wp]<=datain;
end

// memory write pointer increment
always@(posedge clk or negedge rst) begin
    if(!rst) wp<=0;
    else begin
      if(wr && ~full_in) wp<= wp+1'b1;
    end
end

// memory read pointer increment
always@(posedge clk or negedge rst)begin
    if(!rst) rp <= 0;
    else begin
      if(rd && ~empty_in) rp <= rp + 1'b1;
    end
end

// Full signal generate
always@(posedge clk or negedge rst) begin
    if(!rst) full_in <= 1'b0;
    else begin
      if( (~rd && wr)&&((wp==rp-1)||(rp==4'h0&&wp==4'hf)))
          full_in <= 1'b1;
      else if(full_in && rd) full_in <= 1'b0;
    end
end

// Empty signal generate
always@(posedge clk or negedge rst) begin
    if(!rst) empty_in <= 1'b1;
    else begin
      if((rd&&~wr)&&(rp==wp-1 || (rp==4'hf&&wp==4'h0)))
        empty_in<=1'b1;
      else if(empty_in && wr) empty_in<=1'b0;
    end
end
endmodule 

[同步FIFO]

// 同步FIFO相对简单，但稍微复杂点儿的就是full和empty信号的产生，有两种方法上述代码是常用的，但不很容易理解，
// 解释下，FIFO先入先出，可知读写地址都是从零开始递增，这样才能满足先写进的将来会被先读出来。对于同步FIFO来说，时钟是同一个，
// 如果同时读写，那么FIFO永远都不会满。因为当写指针到FIFO尽头时，会继续从零地址开始写（假设零地址的数据已经被读出，当然就可以覆盖了），如此循环往复。那么到底

[空满标志如何产生：]
// 最直观的一种情况，对于full来说，假如一直写，都还没读，此时当wrp=FIFO深度时，应该产生满标志，如果继续写，就会覆盖还未读出的数据，从而使数据失效。
// 对于empty来说，假如wrp=0，而rdp=FIFO深度时，应该产生空标志，如果继续读。就会从零地址开始读，而零地址要么是以前的数据要么是空的，所以…
// 第二种情况：wrp与rdp之间差值为1，rdp-wrp=1时如果没有读，继续写的话会发生数据覆盖；wrp-rdp=1时如果没有写继续读，会读出错误数据。
// 这就是程序中标志位表达形式的原因。

[还有一种简单的方法产生空满标志：]
// 并不用读写地址判定FIFO是否空满。设计一个计数器，该计数器(pt_cnt)用于指示当前周期中FIFO中数据的个数。由于FIFO中最多只有16个数据，因此采用5位计数器来指示FIFO中数据个数。具体计算如下：
// 复位的时候，pt_cnt=0；
// 如果wr_en和rd_en同时有效的时候，pt_cnt不加也不减；表示同时对FIFO进行读写操作的时候，FIFO中的数据个数不变。
// 如果wr_en有效且full=0，则pt_cont+1;表示写操作且FIFO未满时候，FIFO中的数据个数增加了1；
// 如果rd_en有效且empty=0，则pt_cont-1; 表示读操作且FIFO未满时候，FIFO中的数据个数减少了1；
// 如果pt_cnt=0的时候，表示FIFO空，需要设置empty=1;如果pt_cnt=16的时候，表示FIFO现在已经满，需要设置full=1。

该模块的程序：
module flag_gen(clk,rst,full,emptyp,wr_en,rd_en);
input clk,rst;
input rd_en;
input wr_en;
output full,emptyp;
reg full,emptyp;
reg[4:0]count;
parameter max_count=5'b01111;
always @ (posedge clk or negedge rst)
begin
  if(!rst)
   count<=0;
  else
   begin
   case({wr_en,rd_en})
   2'b00:count<=count;
   2'b01:
       if(count!==5'b00000)
       count<=count-1;
   2'b10:
       if(count!== max_count)   
        count<=count+1;
   2'b11:count<=count;
   endcase
   end
end
always @(count)
begin
   if(count==5'b00000)
    emptyp<=1;
   else
    emptyp<=0;
end
always @(count)
begin
   if(count== max_count)
   full<=1;
   else
   full<=0;                                 
end
endmodule