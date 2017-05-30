; Scheme 学习
; @`13
; 2017年05月30日


;快速注释 ctrl+/


; 基础运算
;-------------------
;(+ 1 3) 
; => 4

;(- 1 3)
; => -2

;(+ 1 3 7 2)
; => 13

;(* 2 3 4)
;=> 24

;(/ 24 2 3)
; => 4

; 取倒数
;(/ 2) 
;=> 0.5

; 精确值
;(/ 22 3)
; 22/3(define s "hello,world")

;(exact->inexact (/ 10 3))
; 精确值 -> 浮点数

; 变量 方法 函数 hello,world
;--------------------------

; (define s "hello,world")
; s

; (define t 2.5)
; t

; (define f (lambda () "Hello World"))
; (f)
; => "Hello World"

; (define hello
;     (lambda (name)
;         (string-append "Hello " name "!")
;     )
; )

; (hello "13")
; => "Hello 13!"


; (define (hello name)
;         (string-append "Hello " name "!"))
; (hello "13")
; 同上


; 条件 语法
;(if condition ture_action false_action)


; (define (abs input)
;         (if (< input 0) (- input) input))
; (abs 100)
; (abs -100)


; 也许你已经猜到了，Scheme 的布尔逻辑也是遵循函数式的，最常用的就是 and 和 or 两种了。和常见 C 系语言类似的是，and 和 or 都会将参数从左到右取值，一旦遇到满足停止条件的值就会停止。但是和传统 C 系语言不同，布尔逻辑的函数返回的不一定就是 #t 或者 #f，而有可能是输入值，这和很多脚本语言的行为是比较一致的：and 会返回最后一个非 #f 的值，而 or 则返回第一个非 #f 的值：


; #f
; false
; #t
; true

; (and #f 0)
;=>  #f

;(and 1 2 "Hello")
;=> "Hello"

; (or #f 0)
; => 0

;(and 0 1)
;0 也是 真

; (or #f #f #f)
; => #f

; 在很多时候，Scheme 中的 and 和 or 并不全是用来做条件的组合，而是用来简化一些代码的写法，以及为了顺次执行一些代码的。比如说下面的函数在三个输入都为正数的情况下返回它们的乘积，可以想象和对比一下在指令式编程中同样功能的实现。

; (define (pro3and a b c)
;     (and (positive? a)
;         (positive? b)
;         (positive? c)
;         (* a b c)
;     )
; )

; (pro3and 2 3 4)
; => 24

; (pro3and 2 3 -4)
; => #f

; 除了 if 之外，在 C 系语言里另一种常见的条件分支语句是 switch。Scheme 里对应的函数是 cond。cond 接受多个二元列表作为输入，从上至下依次判断列表的第一项是否满足，如果满足则返回第二项的求值结果并结束，否则一直继续到最后的 else：


; (cond
;   (predicate_1 clauses_1)
;   (predicate_2 clauses_2)
;     ......
;   (predicate_n clauses_n)
;   (else        clauses_else))


; (define (t1 x)
;     (+ x 3)
;     )
; (t1 2)

; (define t2 
;     (lambda(x)
;         (+ x 1)
;     )
; )
; (t2 3)

; (define t3 
;     (lambda (input_number)
;         (if (> input_number 2) (+ input_number 1) input_number)
;     )

; )
; (t3 4)

; (define balance 
;     (lambda(x)  
;     (cond ((> x 10) (- x 10))  
;           ((> x 0) (+ x 1))  
;           ((< x -10) (+ (- x) 1))  
;           (else (- x)))))

; (balance 100) 


; (define t4
;     (lambda (input_number)
;         (cond
;             ((> input_number 1) 10)
;             ((< input_number 1) 20)
;             (else #f)
;         )
;     )
; )

; (t4 1)
; (t4 2)
; (t4 0)
; (t4 "1")

; 在新版的 Scheme 中，标准里加入了更多的流程控制的函数，它们包括 begin，when 和 unless 等。

; begin 将顺次执行一系列语句：
; when 当条件满足时执行一系列代码，而 unless 在条件不满足时执行一系列代码。这些改动可以看出一些现代脚本语言的特色，但是新的标准据说也在 Scheme 社区造成了不小争论。虽然结合使用 if，and 和 or 肯定是可以写出等效的代码的，但是这些额外的分支控制语句确实增加了语言的便利性。

; (define (foo)
;   (begin
;     (display "hello")
;     (newline)
;     (display "world")
;   )
; )

; (foo)

;循环 do

; (do ((i 0 (+ i 1))) ; 初始值和 step 条件
;           ((> i 4))       ; 停止条件，取值为 #f 时停止
;         (display i)       ; 循环主体 (命令)
;       )
 
 
; (do ((i 0 (+ i 2)))
;     ((> i 50))
;     (begin
;         (display i)
;         (newline)
;     )
; )

; 唯一要解释的是这里的条件是停止条件，而不是我们习惯的进入循环主体的条件。
  
  
; 递归

; (define (count n)
;           (and (display (- 4 n))
;               (if (= n 0) #t (count (- n 1)))
;           )
;       )
; (count 5)

; 列表和递归

; 也许你会说，用递归的方式看起来一点也不简单，甚至代码要比上面的 do 的版本更难理解。现在看来确实是这样的，那是因为我们还没有接触 Scheme 里一些很独特的概念，cons cell 和 list。我们在上面介绍 define 的时候曾经提到过，cons cell 的 car 和 cdr。结合这个数据结构，Scheme 里的递归就会变得非常好用。

; 那么什么是 cons cell 呢？其实没有什么特别的，cons cell 就是一种数据结构，它对应了内存的两个地址，每个地址指向一个值。


; (cons 1 2)
; (car (cons 1 2)) ---1 
; (cdr (cons 1 2)) ---2 

; linked list
; (cons 3 (cons 1 2))
; => (3 1 . 2)



; 有一种特殊的 cons cell 链，其最后一个 cons cell 的 cdr 为空列表 '()，这类数据结构就是 Scheme 中的列表。
; 对于列表，我们有一种更简单的创建方式，就是类似 '(1 2 3) 这样。对于列表来说，它的 cdr 值是一个子列表：



; '(1 2 3)
; (car '(1 2 3))
; (cdr '(1 2 3))
; (cdr (cdr '(1 2 3)))
; (cdr (cdr (cdr '(1 2 3))))



; 而循环其实质就是对一列数据进行处理的过程，结合 Scheme 列表的特性，我们意识到如果把列表运用在递归中的话，car 就是遍历的当前项，而 cdr 就是下一次递归的输入。Scheme 和递归调用可以说能配合得天衣无缝。

; 比如我们定义一个将列表中的所有数都加上 1 的函数的话，可以这么处理：

; (define (ins_ls ls)
;     (if (null? ls)
;       '()
;       (cons (+ (car ls) 1) (ins_ls (cdr ls)))
;     )
; )

; (ins_ls '(1 2 3 4 5))



; 尾递归
; (define (ins_ls ls)
;     (ins_ls_interal ls '()))

; (define (ins_ls_interal ls ls0)
;     (if (null? ls)
;         ls0
;         (ins_ls_interal (cdr ls) (cons ( + (car ls) 1) ls0))))

; (define (rev_ls ls)
;   (rev_ls_internal ls '()))

; (define (rev_ls_internal ls ls0)
;   (if (null? ls)
;       ls0
;       (rev_ls_internal (cdr ls) (cons (car ls) ls0))))

; (rev_ls (ins_ls '(1 2 3 4 5)))


; 函数式
; 上面介绍了 Scheme 的最基本的赋值，分支和循环。可以说用这些东西就能够写出一些基本的程序了。一开始会比较难理解 (特别是递归)，但是相信随着深入下去和习惯以后就会好很多。到现在为止，除了在定义函数时，其实我们还没有直接触碰到 Scheme 的函数式特性。在 Scheme 里函数是一等公民，我们可以将一个函数作为参数传给另外的函数并进行调用，这就是高阶函数。

; 一个最简单的例子是排序的时候我们可以将一个返回布尔值的函数作为排序规则：

; 1 ]=> (sort '(7883 9099 6729 2828 7754 4179 5340 2644 2958 2239) <)

; ;Value 13: (2239 2644 2828 2958 4179 5340 6729 7754 7883 9099)
; 更甚于我们可以使用一个匿名函数来控制这个排序，比如按照模 100 之后的大小 (也就是数字的后两位) 进行排序：

; 1 ]=> (sort '(7883 9099 6729 2828 7754 4179 5340 2644 2958 2239)
;       (lambda (x y) (< (modulo x 100) (modulo y 100))))

; ;Value 14: (2828 6729 2239 5340 2644 7754 2958 4179 7883 9099)
; 类似这样的特性在一些 modern 的语言里并不算罕见，但是要知道 Scheme 可是有些年头的东西了。类似的还有 map，filter 等。比如上面的 list 加 1 的例子，用 map 函数就可以非常简单地实现：

; (map (lambda (x) (+ x 1)) '(1 2 3 4 5))

; ;=> (2 3 4 5 6)

https://onevcat.com/2015/05/scheme/

