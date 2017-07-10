/* --------------------------------------
哈尔滨工业大学(威海) - 计算机组成原理课程设计
MIPS.v

@`13
2017年7月7日
----------------------------------------- */

module top #(parameter WIDTH =32 )  
    (seg7,      // 7段数码管         $16  RAM[16][15:0] -> [seg4|seg3|seg2|seg1] [0:7] -> 带小数点的7段共阳数码管
    scan,       // 数码管选择        [0:3] -> 左-右 底电平点亮 循环点亮
    clk,        // 时钟
    button,     // 复位按键
    SW,         // 16 个拨键开关      $14 RAM2[14] [15:0] -> [SW16...SW1]    
    led,        // 16 个LED灯         $15 RAM2[15][15:0] -> LED16-LED1 
    btn);       // 5个 按键开关       $8 RAM2[8] 是否等于 0 
               
    output [7:0]seg7;
    output [15:0]led;
    output [3:0]scan;


    input clk;
    input [15:0]SW;
    input [4:0]btn;
    input button;

    reg clk1;		    // 分频时钟
    reg reset,reset1;   // 复位
    
    wire memread,memwrite;  // 读写信号
    wire [WIDTH-1:0] adr,writedata;     // 写地址，写数据
    wire [WIDTH-1:0] memdata;           // 读数据
    wire [WIDTH-1:0] rd3;  
    wire [WIDTH-1:0] ledrf;             // led灯寄存器         
    wire [3:0] scan;
    wire [7:0] seg7;
  
    reg count1=0;
    reg clk1=0;

    // 通过button 复位
    //always@(negedge button)
    //begin
    // ... RESERT
    //end

    // 同频时钟 clk1 上升沿与clk相反
    always @ (posedge clk)
    begin 
        if(count1==1)
            begin 
                clk1<=~clk1;
                count1<=0;
            end
        else
            begin 
                count1<=count1+1;
            end
    end

    /*always @ (posedge clk)
    begin 
        if(reset1==0)
            begin 
                clk1<=~clk1;
            end
    end*/

    
    //instantiate devices to be tested  需要仿真的cpu
    mips #(WIDTH) CPU(clk1,
                        reset,
                        memdata,
                        memread,
                        memwrite,
                        adr,
                        writedata,
                        rd3,
                        ledrf,
                        SW,
                        btn);

    //7段数码管显示
    seg7_display IO(clk1,
                    rd3,
                    seg7,
                    scan);
  
    //exmemory	存储器
    exmemory #(WIDTH) Memory(clk1,
                            reset,
                            memwrite,
                            adr,
                            writedata,
                            memdata);
  
    //initial
    initial
        begin
	        reset<=0;
	        // button<=1;
	        clk1<=0;
	        // #50;
	        //button<=0;
	        /* #500;
	        reset<=1;
	        #50
	        reset<=0;*/
	        //# 50;
            // reset <=0;
    end

    //generate clock
	//always
		//begin
			//clk <=1;
			//# 5; 
			//clk <=0;
			//# 5;
	//end
	
    /*always @(negedge clk)
		begin
			if(memwrite)
				if(adr==5&writedata==7)
					$display("Simulation completely successful");
				else
					$display("Simulation failed");
	end*/

    
endmodule

// 系统存储空间某一指定位置一直作为4个7段数码管的显示内容 同时同步到LED0~15
// [0:3]->seg7_0 [4:7]->seg7_1 [8:11]->seg_7_2  [12:15]->seg_7_3 
// t1 = rd3 = RAM2[16];
module seg7_display
    (clk,
    t1,
    seg7,
    scan);

    input clk;
    input [31:0]t1;

    output seg7;
    output scan;
   
    reg [4:0] data = 0;
    reg [3:0] scan ;
    reg [7:0] seg7 ;
    reg [1:0] cnt = 0;
    reg clk1khz = 0;
    reg [14:0] count1 = 0;

    always @ (posedge clk)
    begin 
        if(count1==25000)   // 1K hz 分频时钟
            begin 
                clk1khz<=~clk1khz;
                count1<=0;
            end
        else
            begin 
                count1<=count1+1;
            end
    end

    always @(posedge clk1khz)
    begin   // 数码管选段信号切换
        if(cnt == 3)
            begin cnt<=0;end
        else
            begin cnt<=cnt+1;end
    end

    always @ (cnt)
        begin
            case(cnt)
            2'b00:
                begin 
                    data[3:0] <= t1[3:0];
                    data[4] <= 0;
                    scan[3:0] <= 4'b1110;
                end
            2'b01:
                begin 
                    data[3:0]<=t1[7:4];
                    data[4]<=0;
                    scan[3:0]<=4'b1101;
                end
            2'b10:
                begin 
                    data[3:0]<=t1[11:8];
                    data[4]<=0;
                    scan[3:0]<=4'b1011;
                end
            2'b11:
                begin 
                    data[3:0]<=t1[15:12];
                    data[4]<=0;
                    scan[3:0]<=4'b0111;
                end
            default:
                begin 
                    data<=5'b0;
                    scan<=4'b1111;
                end
        endcase
    end
    
    always @(data)
    begin
    if(data[4])
        seg7[7:0]=8'b01111111;//-
    else
        case(data[3:0])  
            4'b0000:seg7[7:0]=8'b11000000;//0
            4'b0001:seg7[7:0]=8'b11111001;//1
            4'b0010:seg7[7:0]=8'b10100100;//2
            4'b0011:seg7[7:0]=8'b10110000;//3
            4'b0100:seg7[7:0]=8'b10011001;//4
            4'b0101:seg7[7:0]=8'b10010010;//5
            4'b0110:seg7[7:0]=8'b10000010;//6
            4'b0111:seg7[7:0]=8'b11111000;//7
            4'b1000:seg7[7:0]=8'b10000000;//8
            4'b1001:seg7[7:0]=8'b10010000;//9
            4'b1010:seg7[7:0]=8'b10001000;//a
            4'b1011:seg7[7:0]=8'b10000011;//b
            4'b1100:seg7[7:0]=8'b11000110;//c
            4'b1101:seg7[7:0]=8'b10100001;//d
            4'b1110:seg7[7:0]=8'b10000110;//e
            4'b1111:seg7[7:0]=8'b10001110;//f
            default:seg7[7:0]=8'b11111111;//11111111; 全灭
        endcase
    end
endmodule


// 2K * 32位 Memory
//external memory
module exmemory #(parameter WIDTH =32)
      (clk,
      reset,
      memwrite,
      adr,
      writedata,
      memdata);
      
    input clk;
    input reset;
    input memwrite;
    input [WIDTH-1:0] adr,writedata;
  
    output reg [WIDTH-1:0] memdata; // Memory OUT
    reg [31:0] RAM [2047:0];        // 2K * 32位 Memory
    
    wire [31:0] word;
    
    initial
	begin
        // $readmemh("Memory.dat",RAM);
	    RAM[0] <=32'b00000000000000000000000000000000;  
	end

    always @(posedge clk)
	if(memwrite)    // 写Memory
		RAM[adr] <= writedata;
                  
    assign word =RAM[adr];    // 始终指向当前adr所指向的内存地址
  
    always @(*)
	    memdata <=word;

endmodule

//mips
module mips #(parameter WIDTH=32) 
          (input clk,reset,
           input [WIDTH-1:0] memdata,
           output memread,memwrite,
           output [WIDTH-1:0] adr,writedata,rd3,rd4,
           input [15:0]SW,
           input [4:0]btn
           );
    
    wire [31:0] instr;//IR
    wire memtoreg,irwrite,iord,pcen,regwrite,regdst,zero;
    wire [1:0] alusrca,alusrcb,pcsource;
    wire [5:0] aluop;
    
    //CU
    controller cont(clk,reset,instr[31:26],instr[5:0],zero,memread,memwrite,
    memtoreg,iord,irwrite,pcen,regwrite,regdst,pcsource,alusrca,alusrcb,aluop);

    //datapath
    datapath #(WIDTH) dp(clk,reset,memdata,memtoreg,iord,pcen,regwrite,regdst,
    irwrite,alusrca,alusrcb,pcsource,aluop,zero,instr,adr,writedata,rd3,rd4,SW,btn);
  
endmodule

//CU
module controller(input clk,reset, 
                  input [5:0] op,
                  input [5:0] func,
                  input zero,
                  output reg memread,memwrite,memtoreg,iord,irwrite,
                  output pcen,
                  output reg regwrite,regdst,
                  output reg [1:0] pcsource,alusrca,alusrcb,
                  output reg[5:0] aluop);
    //state
    parameter FETCHS =4'b0000;
    parameter DECODES=4'b0001;
    parameter MTYPES =4'b0010;
    parameter ITYPES =4'b0011;
    parameter JRUMPS =4'b0100;
    parameter BEQS =4'b0101;
    parameter BLTZS =4'b0110;
    parameter BGTZS =4'b0111;
    parameter JUMPS =4'b1000;
    parameter ReadMS =4'b1001;
    parameter WriteMS=4'b1010;
    parameter IWriteToRegS=4'b1011;
    parameter RITYPES=4'b1100;
    parameter ROTYPES=4'b1101;
    parameter MWriteToRegS=4'b1110;
    parameter RWriteToRegS=4'b1111;

    //OP[5:0]
    parameter RType =6'b000000;
    parameter Bltzop =6'b000001;
    parameter Jop =6'b000010;
    parameter Beqop =6'b000100;
    parameter Bgtzop =6'b000111;
    parameter Addiop =6'b001000;
    parameter Addiuop =6'b001001;
    parameter Sltiop =6'b001010;
    parameter Adiop =6'b001100;
    parameter Oriop =6'b001101;
    parameter Xoriop =6'b001110;
    parameter Luiop =6'b001111;
    parameter Lwop =6'b100011;
    parameter Swop =6'b101011;

    //func
    parameter Func1 =6'b000000;
    parameter Func2 =6'b000010;
    parameter Func3 =6'b000011;
    parameter Func4 =6'b000100;
    parameter Func5 =6'b000111;
    parameter Func6 =6'b001000;
    parameter Func7 =6'b100000;
    parameter Func8 =6'b100001;
    parameter Func9 =6'b100010;
    parameter Func10 =6'b100011;
    parameter Func11 =6'b100110;
    parameter Func12 =6'b100100;
    parameter Func13 =6'b100101;
    parameter Func14 =6'b100111;
    parameter Func15 =6'b101010;
  
    reg [3:0] state,nextstate;
    reg pcwrite,pcwritecond;

    always @(posedge clk )
    begin
        if(reset)
            state <=FETCHS;
        else
            state <=nextstate;
    end
    
    always @(*)
    begin
        case(state)
            FETCHS : nextstate <=DECODES;
            DECODES: case(op)
                        RType:
                            case(func)
                                Func1: nextstate<=RITYPES;
                                Func2: nextstate<=RITYPES;
                                Func3: nextstate<=RITYPES;
                                Func4: nextstate<=ROTYPES;
                                Func5: nextstate<=ROTYPES;
                                Func6: nextstate<=JRUMPS;
                                Func7: nextstate<=ROTYPES;
                                Func8: nextstate<=ROTYPES;
                                Func9: nextstate<=ROTYPES;
                                Func10: nextstate<=ROTYPES;
                                Func11: nextstate<=ROTYPES;
                                Func12: nextstate<=ROTYPES;
                                Func13: nextstate<=ROTYPES;
                                Func14: nextstate<=ROTYPES;
                                Func15: nextstate<=ROTYPES;
                            endcase
                        Bltzop: nextstate <=BLTZS;
                        Jop: nextstate <=JUMPS;
                        Beqop: nextstate<=BEQS;
                        Bgtzop: nextstate<=BGTZS;
                        Addiop: nextstate<=ITYPES;
                        Addiuop: nextstate<=ITYPES;
                        Sltiop: nextstate<=ITYPES;
                        Adiop: nextstate<=ITYPES;
                        Oriop: nextstate<=ITYPES;
                        Xoriop: nextstate<=ITYPES;
                        Luiop: nextstate<=ITYPES;
                        Lwop: nextstate<=MTYPES;
                        Swop: nextstate<=MTYPES;
                        default:nextstate<=FETCHS;
                        endcase
                ITYPES: nextstate<=IWriteToRegS;
                RITYPES: nextstate<=RWriteToRegS;
                ROTYPES: nextstate<=RWriteToRegS;
                BLTZS: nextstate<=FETCHS;
                BEQS: nextstate<=FETCHS;
                BGTZS: nextstate<=FETCHS;
                JUMPS: nextstate<=FETCHS;
                JRUMPS: nextstate<=FETCHS;
                MTYPES: case(op)
                            Lwop:nextstate<=ReadMS;
                            Swop:nextstate<=WriteMS;
                        endcase
            ReadMS: nextstate<=MWriteToRegS;
            WriteMS: nextstate<=FETCHS;
            IWriteToRegS: nextstate<=FETCHS;
            MWriteToRegS: nextstate<=FETCHS;
            RWriteToRegS: nextstate<=FETCHS;
            default: nextstate<=FETCHS;
        endcase
    end

    always @(*)
    begin
        irwrite <= 0;
        pcwrite <= 0; 
        pcwritecond <= 0;
        regwrite <= 0; 
        regdst <= 0;
        memread <= 0; 
        memwrite <= 0;
        alusrca <= 2'b00; 
        alusrcb <= 2'b00; 
        aluop <= 6'b100000;
        pcsource <= 2'b00;
        iord <= 0; 
        memtoreg <= 0;

        case(state)
            FETCHS:
                begin
                    iord<=0;
                    irwrite<=1;
                    memread<=1;
                    memwrite<=0;
                    alusrca<=2'b00;
                    alusrcb<=2'b01;
                    pcsource<=2'b00;
                    pcwrite<=1;
                    aluop<=6'b100000;
                end
            DECODES:
                begin
                    aluop<=6'b100000;
                    alusrca<=2'b00;
                    alusrcb<=2'b11;
                end
            MTYPES:
                begin
                    alusrca<=2'b01;
                    alusrcb<=2'b11;
                    aluop<=6'b100000;
                end
            ITYPES:
                begin
                    alusrca<=2'b01;
                    alusrcb<=2'b11;
                    case(op)
                        Addiop:
                            aluop<=6'b100000;
                        Addiuop:
                            aluop<=6'b100001;
                        Sltiop:
                            aluop<=6'b101010;
                        Adiop:
                            aluop<=6'b100100;
                        Oriop:
                            aluop<=6'b100101;
                        Xoriop:
                            aluop<=6'b100110;
                        Luiop:
                            aluop<=6'b010001;
                    endcase
                end
            JRUMPS:
                begin
                    pcwrite<=1;
                    pcsource<=2'b11;
                end
            BEQS:
                begin
                    alusrca<=2'b01;
                    alusrcb<=2'b00;
                    aluop<=6'b100010;
                    pcsource<=2'b01;
                    pcwritecond<=1;
                end
            BLTZS:
                begin
                alusrca<=2'b01;
                alusrcb<=2'b00;
                aluop<=6'b000001;
                pcsource<=2'b01;
                pcwritecond<=1;
                pcwrite<=0;
                end
            BGTZS:
                begin
                    alusrca<=2'b01;
                    alusrcb<=2'b00;
                    aluop<=6'b001010;
                    pcsource<=2'b01;
                    pcwritecond<=1;
                    pcwrite<=0;
                end
            JUMPS:
                begin
                    pcwrite<=1;
                    pcsource<=2'b10;
                end
            ReadMS:
                begin
                    memread<=1;
                    iord<=1;
                end
            WriteMS:
                begin
                    memwrite<=1;
                    iord<=1;
                end
            IWriteToRegS:
                begin
                    memtoreg<=0;
                    regwrite<=1;
                    regdst<=0;
                end
            RITYPES:
                begin
                    alusrca<=2'b10;
                    alusrcb<=2'b00;
                    case(func)
                        Func1: aluop<=6'b000000;
                        Func2: aluop<=6'b000010;
                        Func3: aluop<=6'b000011;
                    endcase
                end
            ROTYPES:
                begin
                    alusrca<=2'b01;
                    alusrcb<=2'b00;
                    case(func)
                        Func4: aluop<=6'b000000;
                        Func5: aluop<=6'b000010;
                        Func7: aluop<=6'b100000;
                        Func8: aluop<=6'b100001;
                        Func9: aluop<=6'b100010;
                        Func10:aluop<=6'b100011;
                        Func11:aluop<=6'b100110;
                        Func12:aluop<=6'b100100;
                        Func13:aluop<=6'b100101;
                        Func14:aluop<=6'b100111;
                        Func15:aluop<=6'b101010;
                    endcase
                end
            MWriteToRegS:
                begin
                    regdst<=0;
                    regwrite<=1;
                    memtoreg<=1;
                end
            RWriteToRegS:
                begin
                    regdst<=1;
                    regwrite<=1;
                    memtoreg<=0;
                end
        endcase
    end

    assign pcen =pcwrite|(pcwritecond & zero);
endmodule

//datapath
module datapath #(parameter WIDTH =32 )
        (input clk,reset,
        input [WIDTH-1:0] memdata,
        input memtoreg,iord,pcen,regwrite,regdst,irwrite,
        input [1:0] alusrca,alusrcb,pcsource,
        input [5:0] aluop,
        output zero,
        output [31:0] instr,
        output [WIDTH-1:0] adr,writedata,rd3,rd4,
        input [15:0]SW,
        input [4:0]btn);

    parameter CONST_ZERO = 32'b0;
    parameter CONST_ONE = 32'b1;
    wire [4:0] ra1,ra2,wa;//
    wire [WIDTH-1:0] pc,nextpc,md,rd1,rd2,wd,a,src1,src2,aluresult,aluout;
    wire [31:0] jp1;
  
    assign jp1 ={6'b000000,instr[25:0]};
    wire [31:0] ta1,ta2;

    assign ta1 ={27'b0,instr[10:6]};
    assign ta2 ={16'b0,instr[15:0]};
    assign ra1 =instr[25:21];
    assign ra2 =instr[20:16];

    mux2 regmux(instr[20:16],instr[15:11],regdst,wa);
    flopen #(32) ir(clk,irwrite,memdata,instr);
    //datapath
    flopenr #(WIDTH) pcreg(clk,reset,pcen,nextpc,pc);
    flop #(WIDTH) mdr(clk,memdata,md);
    flop #(WIDTH) areg(clk,rd1,a);
    flop #(WIDTH) wrd(clk,rd2,writedata);
    flop #(WIDTH) res(clk,aluresult,aluout);
    mux2 #(WIDTH) adrmux(pc,aluout,iord,adr);
    mux4 #(WIDTH) src1mux(pc,a,ta1,ta2,alusrca,src1);
    mux4 #(WIDTH) src2mux(writedata,CONST_ONE,ta1,ta2,alusrcb,src2);
    mux4 #(WIDTH) pcmux(aluresult,aluout,jp1,rd1,pcsource,nextpc);
    mux2 #(WIDTH) wdmux(aluout,md,memtoreg,wd);
    regfile #(WIDTH) rf(clk,reset,regwrite,ra1,ra2,wa,wd,rd1,rd2,rd3,rd4,SW,btn);
    alu #(WIDTH) alunit(src1,src2,aluop,aluresult);
    zerodetect #(WIDTH) zd(aluresult,zero);
endmodule


//ALU 
module alu #(parameter WIDTH=32)
      (input [WIDTH-1:0] a,b,
       input [5:0] aluop,
       output reg [WIDTH-1:0] result);

    wire [30:0] b2;
    assign b2=a[30:0];
    wire [WIDTH-1:0] sum,slt,shamt;

    always @(*)
        begin
            case(aluop)
                6'b000000: result<=(b<<a);
                6'b000010: result<=(b>>a);
                6'b000011: result<=(b>>>a);
                6'b001000: result<= 32'b0;
                6'b100000: result<=(a+b);
                6'b100001: result<=(a+b);
                6'b100010: result<=(a-b);
                6'b100011: result<=(a-b);
                6'b100110: result<=(a^b);
                6'b100100: result<=(a&b);
                6'b100101: result<=(a|b);
                6'b100111: result<=~(a&b);
                6'b101010: result<=(a<b? 1:0);
                6'b000001: //Bltz
		            begin
			            result<=(a<0 ? 0:1);
		            end
                6'b001010: //Bgtz
                    begin
                        result<=(a>0 ? 0:1);
                    end
	            6'b010001: result<=((b<<16)& 32'b11111111111111110000000000000000);//LUI
            endcase
        end
endmodule

// 2^5(32) 个 32 位寄存器
//regfile
module regfile #(parameter WIDTH=32,REGBITS=5)
      (input clk,
      input reset,
      input regwrite,
      input [REGBITS-1:0] ra1,ra2,wa,
      input [WIDTH-1:0] wd,
      output [WIDTH-1:0] rd1,rd2,rd3,rd4,
            input [15:0]SW,
            input [4:0]btn);

    reg [WIDTH-1:0] RAM2 [(1<<REGBITS)-1:0];
    
    initial
    begin
        //$readmemh("regfile.dat",RAM);
	    RAM2[0] <=32'b00000000000000000000000000000000;
        RAM2[15] <=32'b00000000000000000000000000000000;    // 默认灯全灭
        RAM2[16] <=32'b00000000000000000000000000000000;    // 默认显示0000
    end

    always @(posedge clk)
        begin
            if(btn[1]==1) RAM2[8]=8;
            else if(btn[0]==1)  RAM2[8]=16;
            else if(btn[2]==1)  RAM2[8]=4;
            else if(btn[3]==1)  RAM2[8]=2;
            else if(btn[4]==1)  RAM2[8]=1;
            else    RAM2[8]=0;
            //RAM2[8]=btn[4:0];
            RAM2[14][15:0]=SW[15:0];
            if(regwrite)
                RAM2[wa]<=wd;
        end

    assign rd1 = ra1 ? RAM2[ra1]:0;     // $zero
    assign rd2 = ra2 ? RAM2[ra2]:0;
    assign rd3 = RAM2[16];      // seg7
    assign rd4 = RAM2[15];      // led
    
endmodule

//zerodetect  
module zerodetect #(parameter WIDTH=32)
    (input [WIDTH-1:0] a,
    output y);

    assign y= (a==0);

endmodule

//flop 
module flop #(parameter WIDTH =32)
    (input clk,
     input [WIDTH-1:0] d,
     output reg [WIDTH-1:0] q);

    always @(posedge clk)
        q<=d;

endmodule

//flopen
module flopen #(parameter WIDTH =32)
   (input clk,en,
    input [WIDTH-1:0] d,
    output reg [WIDTH-1:0] q);
    
    always @(posedge clk)
        if(en)
            q<=d;

endmodule

//flopenr
module flopenr #(parameter WIDTH =32)
    (input clk,reset,en,
     input [WIDTH-1:0] d,
     output reg [WIDTH-1:0] q);
    
    always @(posedge clk)
        if(reset)
            q<=0;
        else
            if(en)
                q<=d;

endmodule

//mux2
module mux2 #(parameter WIDTH =32)
    (input [WIDTH-1:0] d0,d1,
     input s,
     output [WIDTH-1:0] y);
 
    assign y= s ? d1:d0;

endmodule

//mux4
module mux4 #(parameter WIDTH =32)
    (input [WIDTH-1:0] d0,d1,d2,d3,
     input [1:0] s,
     output reg [WIDTH-1:0] y);
    
    always @(*)
        case(s)
            2'b00: y<= d0;
            2'b01: y<= d1;
            2'b10: y<= d2;
            2'b11: y<= d3;
        endcase

endmodule
