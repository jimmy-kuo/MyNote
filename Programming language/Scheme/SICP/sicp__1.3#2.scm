; SICP学习 
; @13
; 2017年06月08日18:28:20

;【let】

(define (let-example1 x)
    (+ (let ((x 3)
             (y (+ x 2)))
            (* x y))))
    
(let-example1 2)

; 用define表示同样的效果
(define (f x y)
    (define a (+ 1 (* x y)))
    (define b (- 1 y))
    (+ (* x a a)
       (* y b)
       (* a b)))
   
(f 3 4)

; 这种情况我们更愿意用let 而仅将define 用于【内部过程】

(define suqare
    (lambda (x) (* x x)))


;[练习 1.34]
(define (f g) (g 2))
;(f g) => (g 2)

(f suqare) ; 4
; (f suqare) => (suqare 2) => 4


(f (lambda (z) (* z (+ z 1))))
; ((lambda (z) (* z (+ z 1)) 2) => 6

(f (lambda (z) (* z (+ z 1)))) ; 6

; lambda 可以通过这种方式来调用
((lambda (x) (+ x 1)) 13) ;= 14

;【1.3.3 过程作为一般性的方法】

; (f f) > Error: 2 is not a function [f, (anon), (anon)]
;(f f) => (f 2) => (2 2) => 无限循环 2并不是函数 导致编译器报错



;【(display "1.3.3 过程作为一般性的方法")】

;[折半区间寻找方程的根]
(define (search f neg-point pos-point)
    (let ((midpoint (average neg-point pos-point)))
          (if (close-enough? neg-point pos-point)
              midpoint
              (let ((test-value (f midpoint)))
                (cond ((positive? test-value) (search f neg-point midpoint))
                      ((negative? test-value) (search f midpoint pos-point))
                      (else midpoint))))))

;search 很难使用 因为无法判断输入的两点之前是否有零点


; 改进 - 抛出错误

(define (half-interval-method f a b)
    (let ((a-value (f a))
          (b-value (f b)))
          (cond ((and (negative? a-value) (positive? b-value)) (search f a b))
                ((and (negative? b-value) (positive? a-value)) (search f b a))
                (else (Error "Value are not of opposite sign" a b)))))
            
; 使用 lamdba 来寻找函数 x^3 - 2x -3 = 0 在 1 2之间的零点
; (half-interval-method (lambda (x) (- (* x x x) (* 2 x) (* 2 3)))
;                       1.0
;                       2.0)

;【1.3.4 过程作为返回值 】

;[找出函数的不动点]

; f(x) f(f(x)) f(f(f(x))) f(...f(f(x)))  的值变化不大的时候 点x称为函数的不动点

(define tolerance 0.0001)

(define (fixed-point f first-guess)
    (define (close-enough? v1 v2)
        (< (abs(- v1 v2)) tolerance))
    (define (try guess)
        (let ((next (f guess)))
             (if (close-enough? guess next)
                 next
                 (try next))))
    (try first-guess))


(fixed-point cos 1.0)


; 平衡阻尼过程作为参数传递

; 定义平均值过程
(define average
    (lambda (x y) (/ (+ x y) 2)))

; 定义平衡阻尼过程 【返回平衡阻尼之后的过程】
(define (average-damp f)
    (lambda (x) (average x (f x))))

((average-damp (lambda (x) (+ 1 x))) 2)

; 1 平衡阻尼过程 接受lamdba 函数 (average-damp (lambda (x) ...)) 
; 2 此过程返回新的平衡阻尼值函数 (/ (+ (lambda (x) ...) x) 2 )
; 3 用此过程处理参数 得到返回值

















