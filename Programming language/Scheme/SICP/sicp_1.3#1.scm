; SICP学习 
; @13
; 2017年6月8日16:26:38


;【 1.3 用高阶函数做抽象】


; [1.3.1 过程[函数]作为参数]
; 函数式编程

(define (sum term a next b)
    (if (> a b)
        0
        (+ (term a)
          (sum term (next a) next b))))
       
(define (cube x) (* x x x))

(define (inc n) (+ n 1))

(define (sum-cubes a b)
    (sum cube a inc b))

(sum-cubes 1 2)

; [1.3.2 用lamdba构造过程]
; 创建过程与define 完全一样 【只是不提供过程名字】
; 匿名函数

(lambda (x) (+ x 1))

;[错误示范]
; (define (add-1 x)
;     (lambda (x) (x + 1) ))

; (add-1 13)
;[x] 这样是无法使用lamdba的

;【lamdba 与 define 关系】

(define (plus4 x) (+ 4 x))
(plus4 13)

(define plus-4
    (lambda (x) (+ x 4)))

(plus-4 1 )

;λ 演算


; [用let创建局部变量]

; 计算 f(x,y) = x(1+xy)^2 + y(1-y) + (1+xy)(1-y)

; 可表述为
; a = 1 + xy
; b = 1 - y
; f(x,y) = xa^2 + yb + ab


(define (f x y)
    ; 过程内定义开始
    (define (f-helper a b)
        (+ (* x a a)
           (* y b)
           (* a b)))
    ; 过程内定义结束
    
    ; 过程
    (f-helper (+ 1 (* x y)) (- 1 y)))

(f 1 1)


(define (f x y)
    (; 先定义一个过程内匿名过程 lamdba(a b)
        (lambda (a b) 
            (+  (* x a a)
                (* y b)
                (* a b)))
        ; 使用如下两个参数 (1+xy) (y-1) 调用过程lamdba 作为过程 f 的值    
        (+ 1 (* x y)) (- 1 y) 
    )
)
    
(f 1 1)


; 在过程内调用lamdba的方式如下

; [1 传递参数给匿名函数lamdba]
(define (add-13-2 x)
    (
        (lambda (x) (+ x 13))
        
        (+ x 2))
)
    
(add-13-2 1)

; [2 过程即为匿名函数]
(define plus-4
    (lambda (x) (+ x 4)))

; 【let】 语法

; (let ((<ver1 <exp1>)
;       (<ver2 <exp2>)
;       ...
;       (<vern> <expn>))
;     <body>)
; 作用域为 <body>


(define (let-example x)
    (+ (let((x 3))          ; (let ((<ver1 <exp1>))
        (+ x (* x 10)))     ; <body>)
    x))

(let-example 5)

















