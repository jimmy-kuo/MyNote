; SICP学习 
; @13
; 2017年6月8日15:24:52

;联系 1.2017年6月8日15

;递归

(define (f n)
    (if (< n 3) n
        (+  (f (- n 1)) 
            (* 2 (f (- n 2))) 
            (* 3 (f (- n 3)))
        )))

; (f 4)

;迭代

; f(0) = 0
; f(1) = 1
; f(2) = 2
; f(3) = 3

; f(n) = f(n-1) + f(n-2) + f(n-3) | n>3

; (define (f n) 
;     (f-iter 2 1 0 0 n))
    
(define (f-iter a b c i n)
    (if (= i n)
            c
            (f-iter (+ a (* 2 b) (* 3 c))   ; new a
                    a                       ; new b
                    b                       ; new c
                    (+ i 1)
                    n)))

; (f 4)


;【 1.3 用高阶函数做抽象】


; 1.3.1 过程[函数]作为参数

(define (sum term a next b)
    (if (> a b)
        0
        (+ (term a)
           (sum term (next a) next b))))
       
(define (cube x) (* x x x))

(define (inc n) (+ n 1))

(define (sum-cubes a b)
    (sum cube a inc b))

; (sum-cubes 1 10)











































(f 4)