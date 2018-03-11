Shell 学习笔记
-------------------
Shell 是一个用 C 语言编写的程序，它是用户使用 Linux 的桥梁。Shell 既是一种命令语言，又是一种程序设计语言。
Shell 是指一种应用程序，这个应用程序提供了一个界面，用户通过这个界面访问操作系统内核的服务。

## 第一个shell脚本
```shell
#!/bin/bash
echo "Hello World !" 
```

#!  是一个约定的标记，它告诉系统这个脚本需要什么解释器来执行，即使用哪一种 Shell。
echo 命令用于向窗口输出文本。

### 运行 Shell 脚本有两种方法：

**1、作为可执行程序**
将上面的代码保存为 test.sh，并 cd 到相应目录：
`chmod +x ./test.sh`  	使脚本具有执行权限  		
`./test.sh`  执行脚本		
注意，一定要写成  ./test.sh，而不是  **test.sh**，运行其它二进制的程序也一样，直接写 test.sh，linux 系统会去 PATH 里寻找有没有叫 test.sh 的，而只有 /bin, /sbin, /usr/bin，/usr/sbin 等在 PATH 里，你的当前目录通常不在 PATH 里，所以写成 test.sh 是会找不到命令的，要用 ./test.sh 告诉系统说，就在当前目录找。

**2、作为解释器参数**
这种运行方式是，直接运行解释器，其参数就是 shell 脚本的文件名，如：
`/bin/sh test.sh` 
`/bin/php test.php`
这种方式运行的脚本，不需要在第一行指定解释器信息，写了也没用。

## Shell 变量

定义变量时，变量名不加美元符号（$，PHP语言中变量需要），如：
```shell
your_name="runoob.com"
```
注意，变量名和等号之间不能有空格，这可能和你熟悉的所有编程语言都不一样。同时，变量名的命名须遵循如下规则：
-   命名只能使用英文字母，数字和下划线，首个字符不能以数字开头。
-   中间不能有空格，可以使用下划线（_）。
-   不能使用标点符号。
-   不能使用bash里的关键字（可用help命令查看保留关键字）。
```shell
for file in  `ls /etc`
```
以上语句将 /etc 下目录的文件名循环出来。

### 使用变量

使用一个定义过的变量，只要在变量名前面加美元符号即可，如：
```shell
your_name="qinjx" 
echo $your_name
echo ${your_name}
```
**变量名外面的花括号是可选的，加不加都行，加花括号是为了帮助解释器识别变量的边界**，比如下面这种情况：
```shell
for skill in  Ada  Coffe  Action  Java;  do echo "I am good at ${skill}Script"  done
```
如果不给skill变量加花括号，写成echo "I am good at \$skillScript"，解释器就会把\$skillScript当成一个变量（其值为空），代码执行结果就不是我们期望的样子了。

**推荐给所有变量加上花括号，这是个好的编程习惯**。

已定义的变量，可以被重新定义，如：
```shell
your_name="tom" 
echo $your_name
your_name="alibaba" 
echo $your_name
```
这样写是合法的，但注意，第二次赋值的时候不能写\$your_name="alibaba"，**使用变量的时候才加美元符**（$）。

### 只读变量

使用 `readonly` 命令可以将变量定义为只读变量，只读变量的值不能被改变。

下面的例子尝试更改只读变量，结果报错：
```shell
#!/bin/bash myUrl="http://www.w3cschool.cc"  
readonly myUrl
myUrl="http://www.runoob.com"
```
运行脚本，结果如下：
```shell
/bin/sh: NAME:  This variable is read only.
```

### 删除变量

使用 unset 命令可以删除变量。语法：
```shell
unset variable_name
```
变量被删除后不能再次使用。**unset 命令不能删除只读变量**。

### 变量类型

运行shell时，会同时存在三种变量：

-   **1) 局部变量**  局部变量在脚本或命令中定义，仅在当前shell实例中有效，其他shell启动的程序不能访问局部变量。
-   **2) 环境变量**  所有的程序，包括shell启动的程序，都能访问环境变量，有些程序需要环境变量来保证其正常运行。必要的时候shell脚本也可以定义环境变量。
-   **3) shell变量**  shell变量是由shell程序设置的特殊变量。shell变量中有一部分是环境变量，有一部分是局部变量，这些变量保证了shell的正常运行

## Shell 字符串

字符串是shell编程中最常用最有用的数据类型（除了数字和字符串，也没啥其它类型好用了），字符串可以用单引号，也可以用双引号，也可以不用引号。单双引号的区别跟PHP类似。

### 单引号
```shell
str='this is a string'
```
单引号字符串的限制：
-   **单引号里的任何字符都会原样输出，单引号字符串中的变量是无效的**；
-   单引号字串中不能出现单引号（对单引号使用转义符后也不行）。

### 双引号
```shell
your_name='qinjx'
str="Hello, I know your are \"$your_name\"! \n"
```
双引号的优点：
-   双引号里可以有变量
-   双引号里可以出现转义字符

### 拼接字符串
```shell
your_name="qinjx"
greeting="hello, "$your_name" !"
greeting_1="hello, ${your_name} !"
echo $greeting $greeting_1
```
### 获取字符串长度
```shell
string="abcd"
echo ${#string} #输出 4
```

### 提取子字符串
以下实例从字符串第  **2**  个字符开始截取  **4**  个字符：
```shell
string="runoob is a great site"
echo ${string:1:4} # 输出 unoo
```

### 查找子字符串

查找字符 "**i**  或  **s**" 的位置：`
```shell
string="runoob is a great company"
echo `expr index "$string" is`  # 输出 8
```
**注意：**  以上脚本中 "`" 是反引号，而不是单引号 "'"，不要看错了哦。

## Shell 数组

bash支持一维数组（**不支持多维数组**），并且没有限定数组的大小。        
类似与C语言，数组元素的下标由0开始编号。获取数组中的元素要利用下标，下标可以是整数或算术表达式，其值应大于或等于0。     

### 定义数组

在Shell中，用括号来表示数组，数组元素用"空格"符号分割开。定义数组的一般形式为：
```shell
数组名=(值1  值2  ...  值n)
```
例如：
```shell
array_name=(value0 value1 value2 value3)
```
或者
```shell
array_name=( value0
value1
value2
value3 )
```
还可以单独定义数组的各个分量：
```shell
array_name[0]=value0
array_name[1]=value1
array_name[n]=valuen
```
可以不使用连续的下标，而且下标的范围没有限制。

### 读取数组

读取数组元素值的一般格式是：
```shell
${数组名[下标]}
```
例如：
```shell
valuen=${array_name[n]}
```
使用@符号可以获取数组中的所有元素，例如：
```shell
echo ${array_name[@]}
```
### 获取数组的长度

获取数组长度的方法与获取字符串长度的方法相同，例如：
```shell
# 取得数组元素的个数
length=${#array_name[@]}
# 或者
length=${#array_name[*]}
# 取得数组单个元素的长度
lengthn=${#array_name[n]}
```

## Shell 注释
以"#"开头的行就是注释，会被解释器忽略。


#### 如果在开发过程中，遇到大段的代码需要临时注释起来，过一会儿又取消注释，怎么办呢？
每一行加个#符号太费力了，可以把这一段要注释的代码用一对花括号括起来，定义成一个函数，没有地方调用这个函数，这块代码就不会执行，达到了和注释一样的效果。

## Shell 传递参数
我们可以在执行 Shell 脚本时，向脚本传递参数，脚本内获取参数的格式为：$n。n 代表一个数字，1 为执行脚本的第一个参数，2 为执行脚本的第二个参数，以此类推……

实例
以下实例我们向脚本传递三个参数，并分别输出，其中 $0 为执行的文件名：
```shell
#!/bin/bash
echo "Shell 传递参数实例！";
echo "执行的文件名：$0";
echo "第一个参数为：$1";
echo "第二个参数为：$2";
echo "第三个参数为：$3";
```
为脚本设置可执行权限，并执行脚本，输出结果如下所示：
```shell
$ chmod +x test.sh 
$ ./test.sh 1 2 3
Shell 传递参数实例！
执行的文件名：./test.sh
第一个参数为：1
第二个参数为：2
第三个参数为：3
```
另外，还有几个特殊字符用来处理参数：      
![image.png](https://upload-images.jianshu.io/upload_images/5617720-479c0f8ea5b4f986.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

##  Shell 基本运算符
原生bash不支持简单的数学运算，但是可以通过其他命令来实现，例如 awk 和 expr，expr 最常用。
expr 是一款表达式计算工具，使用它能完成表达式的求值操作。
例如，两个数相加(**注意使用的是反引号 ` 而不是单引号 '**)：
```shell
#!/bin/bash

val=`expr 2 + 2`
echo "两数之和为 : $val"
```
### 算术运算符
下表列出了常用的算术运算符，假定变量 a 为 10，变量 b 为 20：        
![image.png](https://upload-images.jianshu.io/upload_images/5617720-7f4bd1f68def3776.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 关系运算符
![image.png](https://upload-images.jianshu.io/upload_images/5617720-a49ff7ec0cef1a93.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

## Shell 流程控制

### if else
```shell
if condition1
then
    command1
elif condition2 
then 
    command2
else
    commandN
fi
```

### for 循环
```shell
for var in item1 item2 ... itemN
do
    command1
    command2
    ...
    commandN
done
```

### while 语句
```shell
while condition
do
    command
done
```

### break命令
break命令允许跳出所有循环（终止执行后面的所有循环）。

### continue
continue命令与break命令类似，只有一点差别，它不会跳出所有循环，仅仅跳出当前循环。

## Shell 函数

linux shell 可以用户定义函数，然后在shell脚本中可以随便调用。
shell中函数的定义格式如下：
```shell
[ function ] funname [()]

{

    action;

    [return int;]

}
```


### 带有return
```shell
#!/bin/bash
# author:菜鸟教程
# url:www.runoob.com

funWithReturn(){
    echo "这个函数会对输入的两个数字进行相加运算..."
    echo "输入第一个数字: "
    read aNum
    echo "输入第二个数字: "
    read anotherNum
    echo "两个数字分别为 $aNum 和 $anotherNum !"
    return $(($aNum+$anotherNum))
}
funWithReturn
echo "输入的两个数字之和为 $? !"
```
运行输出
```
这个函数会对输入的两个数字进行相加运算...
输入第一个数字: 
1
输入第二个数字: 
2
两个数字分别为 1 和 2 !
输入的两个数字之和为 3 !
```
函数返回值在调用该函数后通过 \$? 来获得。

注意：所有函数在使用前必须定义。这意味着必须将函数放在脚本开始部分，直至shell解释器首次发现它时，才可以使用。调用函数仅使用其函数名即可。

### 获取参数
```shell
#!/bin/bash
# author:菜鸟教程
# url:www.runoob.com

funWithParam(){
    echo "第一个参数为 $1 !"
    echo "第二个参数为 $2 !"
    echo "第十个参数为 $10 !"
    echo "第十个参数为 ${10} !"
    echo "第十一个参数为 ${11} !"
    echo "参数总数有 $# 个!"
    echo "作为一个字符串输出所有参数 $* !"
}
funWithParam 1 2 3 4 5 6 7 8 9 34 73
```
注意，\$10 不能获取第十个参数，获取第十个参数需要\${10}。当n>=10时，需要使用\${n}来获取参数。

输出
```shell
第一个参数为 1 !
第二个参数为 2 !
第十个参数为 10 !
第十个参数为 34 !
第十一个参数为 73 !
参数总数有 11 个!
作为一个字符串输出所有参数 1 2 3 4 5 6 7 8 9 34 73 !
```

## Shell 输入/输出重定向

大多数 UNIX 系统命令从你的终端接受输入并将所产生的输出发送回​​到您的终端。一个命令通常从一个叫标准输入的地方读取输入，默认情况下，这恰好是你的终端。同样，一个命令通常将其输出写入到标准输出，默认情况下，这也是你的终端。

重定向命令列表如下：  
![image.png](https://upload-images.jianshu.io/upload_images/5617720-36c1b0e98b5e6ba7.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
