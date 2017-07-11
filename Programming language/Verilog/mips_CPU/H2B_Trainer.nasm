            xor     $16     $16     $16        
            xor     $15     $15     $15        
            xor     $19     $19     $19        
            xor     $9      $9      $9         
            xor     $11     $11     $11        
            xor     $12     $12     $12        
            xor     $17     $17     $17        
            xor     $18     $18     $18       
            addi    $19     $19     3          
            addi    $17     $17     10         
            addi    $18     $18     25         
            addi    $16     $16     1      
CLOCK:      beq     $11     $17     ACTIVITY    
            addi    $11     $11     1           
            J                       CLOCK      
ACTIVITY:   xor     $11     $11     $11        
            beq     $8      $0      NEXT
       	    J                       PRESS      
NEXT:       addi    $12     $12     1          
            beq     $12     $18     FAIL       
            J                       CLOCK
FAIL:       xor     $12     $12     $12        
            addi    $15     $15     1          
            beq     $15     $19     ENDF       
            J                       RANDOM     
RANDOM:     add     $16     $16     $16 
            addi    $16     $16     3         
            J                       CLOCK
PRESS:      xor     $12     $12     $12        
            beq     $14     $16     PASS      
            J                       FAIL     
PASS:       addi    $9      $9      1          
            beq     $9      $19     ENDP       
            J                       RANDOM     
ENDF:       xor     $16     $16     $16        
            addi    $16     $16     65535      
            xor     $15     $15     $15        
            addi    $15     $15     4 
            J                       END        
ENDP:       xor     $16     $16     $16        
            addi    $16     $16     34952
            J                       END     
END:        xor     $0      $0      $0 
            J                       END
