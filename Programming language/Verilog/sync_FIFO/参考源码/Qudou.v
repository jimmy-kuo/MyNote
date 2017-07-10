module Qudou (
BJ_CLK,         //采集时钟，40Hz
RESET,          //系统复位信号低电平有效
BUTTON_IN,      //按键输入信号
BUTTON_OUT      //消抖后的输出信号
);

    input BJ_CLK;
    input RESET;
    input BUTTON_IN;
    
    output BUTTON_OUT;

    reg BUTTON_IN_Q, BUTTON_IN_2Q, BUTTON_IN_3Q;
    always @(posedge BJ_CLK or negedge RESET)
    begin
        if(~RESET)
            begin
            BUTTON_IN_Q <= 1'b1;
            BUTTON_IN_2Q <= 1'b1;
            BUTTON_IN_3Q <= 1'b1;
            end
        else
            begin   
            BUTTON_IN_Q <= BUTTON_IN;
            BUTTON_IN_2Q <= BUTTON_IN_Q;
            BUTTON_IN_3Q <= BUTTON_IN_2Q;
            end
    end

    wire BUTTON_OUT = BUTTON_IN_2Q | BUTTON_IN_3Q;

endmodule