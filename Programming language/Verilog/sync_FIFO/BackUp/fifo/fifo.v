/* 同步 FIFO 4*128  */

// 一种4bit 128深度的 同步FIFO设计
// @`13
// 2017年6月6日
// 哈尔滨工业大学（威海） EDA课程设计

// Final Ver 2017.6.13
// @`13


module fifo(clock, 	// 时钟信号		[默认使用50m Hz]
			reset,  // 重置信号		[低电平有效]
			read,   // 读信号		[低电平有效]	
			write,  // 写信号		[低电平有效]	
			fifo_in, 			// FIFO 4位数据输入  [使用 4位 拨动开关输入
			digitron_out, 		// 数码管输出		[使用 7位 共阳极数码管]
			digitron_select, 	// 数码管片选信号		 [低电平有效] 
			fifo_empty, 		// FIFO 空信号 	 	[高电平有效]
			fifo_full			// FIFO 满信号			[高电平有效]
			);

	parameter DEPTH = 128;  						// 128 深
	parameter DEPTH_BINARY = 7;  					// 深度的二进制位数
	parameter WIDTH = 4;							// 4bit宽
	parameter MAX_CONT = 7'b1111111;				// 计数器最大值127 [0~127]

	// LED 灯的二进制表示
	// 根据 《数字系统设计与Verilog DHL (6th Edition)》P153 所提供的7段数码管电路图
	// 基于共阳极方式
	/*
	——  a
	| | f b
	——  g
	| | e c
	——	d
	*/
	// Len_N = abcdefg

	// 使用一个七段数码管基于16进制显示 4bit 数据
	parameter 
		 digitron_0 = 7'b0000001,
		 digitron_1 = 7'b1001111,
		 digitron_2 = 7'b0010010,
		 digitron_3 = 7'b1111001,
		 digitron_4 = 7'b1001100,
		 digitron_5 = 7'b0100100,
		 digitron_6 = 7'b0100000,
		 digitron_7 = 7'b0001111,
		 digitron_8 = 7'b0000000,
		 digitron_9 = 7'b0000100,
		 digitron_a = 7'b0011000,
		 digitron_b = 7'b1100000,
		 digitron_c = 7'b0110001,
		 digitron_d = 7'b1000010,
		 digitron_e = 7'b1001111,
		 digitron_f = 7'b0110000;
	 
	 
    input clock,reset,read,write;       			// 时钟，重置，读开关，写开关
    input [WIDTH-1:0]fifo_in;    					// FIFO 数据输入

    output [6:0] digitron_out;            	   		// 数码管 FIFO 数据输出
    output fifo_empty,fifo_full;        			// 空标志,满标志
	output digitron_select;							// 数码管选择信号
	
	reg digitron_select;
	reg div;										// 驱动信号
	reg [23:0] clock_count;							// 时钟计数器
	reg [6:0] digitron_out;							// 数据输出寄存器
    reg [WIDTH-1:0]fifo_out;                    		// 数据输出寄存器
    reg [WIDTH-1:0]ram[DEPTH-1:0];              		// 128深度 8宽度的 RAM 寄存器
    reg [DEPTH_BINARY-1:0]read_ptr,write_ptr,counter; 	// 读指针，写指针，计数器 长度为2^7

    wire fifo_empty,fifo_full;      	    			// 空标志,满标志
	 
	initial                                                
		begin	// 初始化数据             
			counter = 0;
			read_ptr = 0;
			write_ptr = 0;
			fifo_out = 0;
			div = 0;
			clock_count = 0;
			digitron_out = digitron_8;
			digitron_select = 0;
		end              
	 
	always@(posedge clock)
		begin
			if(clock_count == 24'b111111111111111111111111)
				begin	// 驱动信号生成
				div =~ div;
				clock_count <= 0;
				end
			else
				begin	// 使用一个接近1HZ的驱动信号
				clock_count <= clock_count+1;
				end
		end
	
	always@(posedge clock) 
		begin	// 片选信号始终有效
			digitron_select <= 1'b0;
		end
	
	assign fifo_empty = (counter == 0);    					// 空标志位赋值 
    assign fifo_full = (counter == DEPTH-1);				// 满标志位赋值 
    
	always@(posedge div)    								// 时钟同步驱动
        if(reset)   										// Reset 重置FIFO
            begin
                read_ptr = 0; 
                write_ptr = 0;
                counter = 0;
				digitron_out = digitron_8;
				digitron_select = 0;                    
            end
        else
            case({read,write})  			// 相应读写开关
            2'b00:;  		//没有读写指令     
            2'b01:  		//写指令，数据输入FIFO                           
            begin
				if (counter < DEPTH - 1)	// 判断是否可写
					begin
						ram[write_ptr] = fifo_in;
						counter = counter + 1;
						write_ptr = (write_ptr == DEPTH-1)?0:write_ptr + 1;
					end
            end
            2'b10: 			//读指令，数据读出FIFO
            begin
				if (counter > 0)			// 判断是否可读
					begin
						fifo_out = ram[read_ptr];
						case(fifo_out)
							4'b0000 : digitron_out <= digitron_0;
							4'b0001 : digitron_out <= digitron_1;
							4'b0010 : digitron_out <= digitron_2;
							4'b0011 : digitron_out <= digitron_3;
							4'b0100 : digitron_out <= digitron_4;
							4'b0101 : digitron_out <= digitron_5;
							4'b0110 : digitron_out <= digitron_6;
							4'b0111 : digitron_out <= digitron_7;
							4'b1000 : digitron_out <= digitron_8;
							4'b1001 : digitron_out <= digitron_9;
							4'b1010 : digitron_out <= digitron_a;
							4'b1011 : digitron_out <= digitron_b;
							4'b1100 : digitron_out <= digitron_c;
							4'b1101 : digitron_out <= digitron_d;
							4'b1110 : digitron_out <= digitron_e;
							4'b1111 : digitron_out <= digitron_f;
						endcase
						counter = counter - 1;
						read_ptr = (read_ptr == DEPTH-1)?0:read_ptr + 1;
					end
						 
            end
            2'b11: 			//读写指令同时，数据可以直接输出
            begin
                if(counter == 0)
					begin
						fifo_out = fifo_in;	// 直接输出
						case(fifo_out)	// todo : 去除case的冗余代码 2017.6.13
							4'b0000 : digitron_out <= digitron_0;
							4'b0001 : digitron_out <= digitron_1;
							4'b0010 : digitron_out <= digitron_2;
							4'b0011 : digitron_out <= digitron_3;
							4'b0100 : digitron_out <= digitron_4;
							4'b0101 : digitron_out <= digitron_5;
							4'b0110 : digitron_out <= digitron_6;
							4'b0111 : digitron_out <= digitron_7;
							4'b1000 : digitron_out <= digitron_8;
							4'b1001 : digitron_out <= digitron_9;
							4'b1010 : digitron_out <= digitron_a;
							4'b1011 : digitron_out <= digitron_b;
							4'b1100 : digitron_out <= digitron_c;
							4'b1101 : digitron_out <= digitron_d;
							4'b1110 : digitron_out <= digitron_e;
							4'b1111 : digitron_out <= digitron_f;
						endcase
					end
                else
                begin
                    ram[write_ptr]=fifo_in;
                    fifo_out=ram[read_ptr];
					case(fifo_out)	// todo : 去除case的冗余代码 2017.6.13
						4'b0000 : digitron_out <= digitron_0;
						4'b0001 : digitron_out <= digitron_1;
						4'b0010 : digitron_out <= digitron_2;
						4'b0011 : digitron_out <= digitron_3;
						4'b0100 : digitron_out <= digitron_4;
						4'b0101 : digitron_out <= digitron_5;
						4'b0110 : digitron_out <= digitron_6;
						4'b0111 : digitron_out <= digitron_7;
						4'b1000 : digitron_out <= digitron_8;
						4'b1001 : digitron_out <= digitron_9;
						4'b1010 : digitron_out <= digitron_a;
						4'b1011 : digitron_out <= digitron_b;
						4'b1100 : digitron_out <= digitron_c;
						4'b1101 : digitron_out <= digitron_d;
						4'b1110 : digitron_out <= digitron_e;
						4'b1111 : digitron_out <= digitron_f;
					endcase
                    write_ptr=(write_ptr==DEPTH-1)?0:write_ptr+1;
                    read_ptr=(read_ptr==DEPTH-1)?0:write_ptr+1;
                end
            end
        endcase
        
endmodule


// 一种信号去抖电路

// module debouncing(
// BJ_CLK,         //采集时钟
// RESET,          //系统复位信号 [低电平有效]
// BUTTON_IN,      //按键输入信号
// BUTTON_OUT      //消抖后的输出信号
// );

//    	input BJ_CLK;
//    	input RESET;
//    	input BUTTON_IN;
   
//    	output BUTTON_OUT;

//    	reg BUTTON_IN_Q, BUTTON_IN_2Q, BUTTON_IN_3Q;

//    	always @(posedge BJ_CLK or negedge RESET)
// 	begin
// 		if(~RESET)
// 			begin
// 			BUTTON_IN_Q <= 1'b1;
// 			BUTTON_IN_2Q <= 1'b1;
// 			BUTTON_IN_3Q <= 1'b1;
// 			end
// 		else
// 			begin   
// 			BUTTON_IN_Q <= BUTTON_IN;
// 			BUTTON_IN_2Q <= BUTTON_IN_Q;
// 			BUTTON_IN_3Q <= BUTTON_IN_2Q;
// 			end
// 	end

//    wire BUTTON_OUT = BUTTON_IN_2Q | BUTTON_IN_3Q;

// endmodule
