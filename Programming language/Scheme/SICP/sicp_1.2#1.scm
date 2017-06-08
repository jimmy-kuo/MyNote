; Scheme L2
; For <SCIP>
; @`13
; 2017年6月7日


;1.1.7 牛顿法求平方根

(define (square x)
    (* x x))

(define (average x y)
    (/ (+ x y) 2))

(define (imporve guess x)
    (average guess (/ x guess)))

(define (good-enough? guess x)
    (< (abs(- (square guess) x)) 0.001))

; (define (sqrt-iter guess x)
;     (if (good-enough? guess x)
;     guess
;     (sqrt-iter(imporve guess x)
;                 x)))
            
; (define (sqrt x)
;     (sqrt-iter 1.0 x))

; (sqrt 2)



;改进if
(define (new-if predicate then-clause else-clause)
    (cond (predicate then-clause)
          (else else-clause)))
      
; (define (sqrt-iter guess x)
;     (new-if (good-enough? guess x)
;     guess
;     (sqrt-iter(imporve guess x)
;                 x)))
            
; (define (sqrt x)
;     (sqrt-iter 1.0 x))

; (sqrt 2)         
; 使用 new-if 后 程序会无线循环递归

;原因如下

; 由于之前在网上查找过关于sicp1.5习题的解答, 所以看到sicp1.6就想到了是Applicative order 和 Normal order之间的问题
; new-if是scheme定义的过程, 计算时采用的是【应用序(Applicative order)】
; if是scheme中的基本运算符, 计算时采用的是【正则序(Normal order)】
; 根据应用序和正则序的定义, 【new-if会一直展开else-clause, 造成栈溢出】
; 而if则当predicate为false时, 才去展开else-clause, 可以进行递归运算
; 由此让我联想到SICP中文版中讲Applicative order 和 Normal order时说过的一句话:
; 正则序是特别有价值的工具.
; 而if就是最好的例子, 有了if的正则序计算, 递归就得以实现.

(new-if (> 2 3) (display "first") (display "end"))
;endfirst>


(new-if (< 2 3) (display "first") (display "end"))
;endfirst>

;而且总是先求后一个表达式的值
