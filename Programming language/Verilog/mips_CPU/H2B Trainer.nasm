            xor     $16     $16     $16        ; 7段数码管清零
            xor     $15     $15     $15        ; led寄存器清零 - 存储fail
            xor     $19     $19     $19        ; fail/pass 上限寄存器
            xor     $9      $9      $9         ; pass 计数器清零
            xor     $11     $11     $11        ; 分频时钟计数器清零
            xor     $12     $12     $12        ; 限时计数器清零
            xor     $17     $17     $17        ; 分频时钟计数器上限
            xor     $18     $18     $18        ; 限时计数器上限
            addi    $19     $19     3          ; pass/fail 上限为3
            addi    $17     $17     20         ; 分频时钟 约 0.5hz
            addi    $18     $18     25         ; 限时 10s
            addi    $16     $16     16242      ; 初始显示 3F72
CLOCK:      beq     $11     $17     ACTIVITY    
            addi    $11     $11     1           
            J                       CLOCK      
ACTIVITY:   xor     $11     $11     $11        ;  分频时钟计数器清零
            bne     $8      0       PRESS      ;  检测有无按键按下
            addi    $12     $12     1          ;  限时计数器 +1
            beq     $12     $18     FAIL       ;  检测是否超时
            J                       CLOCK
FAIL:       xor     $12     $12     $12        ;  限时计数器清零
            addi    $15     $15     1          ;  fail 计数器 +1
            beq     $15     $19     ENDF       ;  结束-失败
            J                       RANDOM     ;  生成新的随机数
RANDOM:     add     $16     $16     $16        ;  显示新随机数
            J                       CLOCK
PRESS:      xor     $12     $12     $12        ;  限时计数器清零
            beq     $14     $16     PASS       ;  检测拨键是否和显示相等
            J                       FAIL       ;  不相等 跳转到 FAIL
PASS:       addi    $9      $9      1          ;  pass寄存器 +1
            beq     $9      $19     ENDP       ;  通过
            J                       RANDOM     ;  生成新随机数
ENDF        xor     $16     $16     $16        ; 数码管 显示清零
            addi    $16     $16     65535      ; 数码管 显示FFFF
            xor     $15     $15     $15        ; 
            addi    $15     $15     7          ; 三个LED灯全亮
ENDP:       xor     $16     $16     $16        ; 数码管 显示清零
            addi    $16     $16     65535      ; 数码管 显示8888