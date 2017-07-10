/* 同步 FIFO 16*16  */

// 一种2bit 16深度的 同步FIFO设计
// @`13
// 2017年6月6日
// 哈尔滨工业大学（威海） EDA课程设计

module fifo(clock,reset,read,write,fifo_in,fifo_out,fifo_empty,fifo_full);
    
    input clock,reset,read,write;       // 时钟，重置，读开关，写开关
    input [15:0]fifo_in;                // FIFO 数据输入 
    output[15:0]fifo_out;               // FIFO 数据输出
    output fifo_empty,fifo_full;        // 空标志,满标志

    reg [15:0]fifo_out;                         // 数据输出寄存器
    reg [15:0]ram[15:0];                        // 16深度 16宽度的RAM 寄存器
    reg [3:0]read_ptr,write_ptr,counter;        // 读指针，写指针，计数器 长度为4 2^4 = 16

    wire fifo_empty,fifo_full;          // 空标志,满标志
  
    always@(posedge clock)    // 时钟同步驱动
        if(reset)   // Reset 重置FIFO
            begin
                read_ptr = 0; 
                write_ptr = 0;
                counter = 0;
                fifo_out = 0;                    
            end
        else
            case({read,write})  // 相应读写开关
            2'b00:  //没有读写指令
                counter=counter;        
            2'b01:  //写指令，数据输入FIFO                           
            begin
                ram[write_ptr] = fifo_in;
                counter = counter+1;
                write_ptr = (write_ptr == 15)?0:write_ptr + 1;
            end
            2'b10: //读指令，数据读出FIFO
            begin
                fifo_out = ram[read_ptr];
                counter = counter - 1;
                read_ptr = (read_ptr == 15)?0:read_ptr + 1;
            end
            2'b11: //读写指令同时，数据可以直接输出
            begin
                if(counter == 0)
                    fifo_out = fifo_in;
                else
                begin
                    ram[write_ptr]=fifo_in;
                    fifo_out=ram[read_ptr];
                    write_ptr=(write_ptr==15)?0:write_ptr+1;
                    read_ptr=(read_ptr==15)?0:write_ptr+1;
                end
            end
        endcase
        
        assign fifo_empty = (counter == 0);    //标志位赋值 
        assign fifo_full = (counter == 15);
        
endmodule
