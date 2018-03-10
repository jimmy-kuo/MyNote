<!-- GFM-TOC -->
* [Python 之禅](#Python-之禅)
* [参数传递是值传递还是引用传递](#参数传递是值传递还是引用传递)
<!-- GFM-TOC -->

# Python 进阶 & 面试知识整理

## Python 之禅
> The Zen of Python, by Tim Peters
Beautiful is better than ugly.
Explicit is better than implicit.
Simple is better than complex.
Complex is better than complicated.
Flat is better than nested.
Sparse is better than dense.
Readability counts.
Special cases aren't special enough to break the rules.
Although practicality beats purity.
Errors should never pass silently.
Unless explicitly silenced.
In the face of ambiguity, refuse the temptation to guess.
There should be one-- and preferably only one --obvious way to do it.
Although that way may not be obvious at first unless you're Dutch.
Now is better than never.
Although never is often better than \*right\* now.
If the implementation is hard to explain, it's a bad idea.
If the implementation is easy to explain, it may be a good idea.
Namespaces are one honking great idea -- let's do more of those!

> Python之禅 by Tim Peters
优美胜于丑陋（Python 以编写优美的代码为目标）
明了胜于晦涩（优美的代码应当是明了的，命名规范，风格相似）
简洁胜于复杂（优美的代码应当是简洁的，不要有复杂的内部实现）
复杂胜于凌乱（如果复杂不可避免，那代码间也不能有难懂的关系，要保持接口简洁）
扁平胜于嵌套（优美的代码应当是扁平的，不能有太多的嵌套）
间隔胜于紧凑（优美的代码有适当的间隔，不要奢望一行代码解决问题）
可读性很重要（优美的代码是可读的）
即便假借特例的实用性之名，也不可违背这些规则（这些规则至高无上）
不要包容所有错误，除非你确定需要这样做（精准地捕获异常，不写 except:pass 风格的代码）
当存在多种可能，不要尝试去猜测
而是尽量找一种，最好是唯一一种明显的解决方案（如果不确定，就用穷举法）
虽然这并不容易，因为你不是 Python 之父（这里的 Dutch 是指 Guido ）
做也许好过不做，但不假思索就动手还不如不做（动手之前要细思量）
如果你无法向人描述你的方案，那肯定不是一个好方案；反之亦然（方案测评标准）
命名空间是一种绝妙的理念，我们应当多加利用（倡导与号召）

##  参数传递是值传递还是引用传递

### 引用传递
都是引用，对于不可改变的数据类型来说，不能改变，如果修改了，事实上是新建一个对象来对待。

## [Python的深拷贝与浅拷贝](https://www.cnblogs.com/wilber2013/p/4645353.html)

-   Python中对象的赋值都是进行对象引用（内存地址）传递
-   使用copy.copy()，可以进行对象的浅拷贝，**它复制了对象，但对于对象中的元素，依然使用原始的引用**.
-   如果需要复制一个容器对象，以及它里面的所有元素（包含元素的子元素），可以使用copy.deepcopy()进行深拷贝
-   **对于非容器类型（如数字、字符串、和其他'原子'类型的对象）没有被拷贝一说**
-   如果元祖变量只包含原子类型对象，则不能深拷贝

## [Python 的垃圾回收机制](https://www.cnblogs.com/pinganzi/p/6646742.html#_label0)

### 引用计数
python里每一个东西都是对象，它们的核心就是一个结构体：`PyObject`
```c
 typedef struct_object 
 { 
	 int ob_refcnt;
	 struct_typeobject *ob_type;
} PyObject;
```
PyObject是每个对象必有的内容，其中`ob_refcnt`就是做为引用计数。当一个对象有新的引用时，它的`ob_refcnt`就会增加，当引用它的对象被删除，它的`ob_refcnt`就会减少
```c
#define Py_INCREF(op)   ((op)->ob_refcnt++) //增加计数 
#define Py_DECREF(op)  //减少计数

if (--(op)->ob_refcnt != 0) ;  
else  __Py_Dealloc((PyObject *)(op))
```
**当引用计数为0时，该对象生命就结束了**。

引用计数机制的优点：
1.  简单
2.  实时性：一旦没有引用，内存就直接释放了。不用像其他机制等到特定时机。实时性还带来一个好处：处理回收内存的时间分摊到了平时。

引用计数机制的缺点：
1.  维护引用计数消耗资源
2.  循环引用
```python
list1 = []
list2 = []
list1.append(list2)
list2.append(list1)
```
list1与list2相互引用，**如果不存在其他对象对它们的引用，list1与list2的引用计数也仍然为1，所占用的内存永远无法被回收**，这将是致命的。  
对于如今的强大硬件，缺点1尚可接受，但是循环引用导致内存泄露，注定python还将引入新的回收机制。
(标记清除和分代收集)

### 基于零代算法的循环引用检测及垃圾回收机制
#### Python中的循环数据结构以及引用计数

我们知道在Python中，每个对象都保存了一个称为引用计数的整数值，来追踪到底有多少引用指向了这个对象。无论何时，如果我们程序中的一个变量或其他对象引用了目标对象，Python将会增加这个计数值，而当程序停止使用这个对象，则Python会减少这个计数值。一旦计数值被减到零，Python将会释放这个对象以及回收相关内存空间。

从六十年代开始，计算机科学界就面临了一个严重的理论问题，那就是针对引用计数这种算法来说，如果一个数据结构引用了它自身，即如果这个数据结构是一个循环数据结构，那么某些引用计数值是肯定无法变成零的。为了更好地理解这个问题，让我们举个例子。下面的代码展示了一些上周我们所用到的节点类：

![](https://upload-images.jianshu.io/upload_images/311496-f3b8a99b7a4aac48.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

  
我们有一个构造器(在Python中叫做 init )，在一个实例变量中存储一个单独的属性。在类定义之后我们创建两个节点，ABC以及DEF，在图中为左边的矩形框。两个节点的引用计数都被初始化为1，因为各有两个引用指向各个节点(n1和n2)。

现在，让我们在节点中定义两个附加的属性，next以及prev：

![](https://upload-images.jianshu.io/upload_images/311496-2646466e5aa4711d.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

  
跟Ruby不同的是，Python中你可以在代码运行的时候动态定义实例变量或对象属性。这看起来似乎有点像Ruby缺失了某些有趣的魔法。(声明下我不是一个Python程序员，所以可能会存在一些命名方面的错误)。我们设置 n1.next 指向 n2，同时设置 n2.prev 指回 n1。现在，我们的两个节点使用循环引用的方式构成了一个双端链表。同时请注意到 ABC 以及 DEF 的引用计数值已经增加到了2。这里有两个指针指向了每个节点：首先是 n1 以及 n2，其次就是 next 以及 prev。

现在，假定我们的程序不再使用这两个节点了，我们将 n1 和 n2 都设置为null(Python中是None)。

![](https://upload-images.jianshu.io/upload_images/311496-28ee4d77afde09b0.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

好了，Python会像往常一样将每个节点的引用计数减少到1。

#### 在Python中的零代(Generation Zero)

请注意在以上刚刚说到的例子中，我们以一个不是很常见的情况结尾：我们有一个“孤岛”或是一组未使用的、互相指向的对象，但是谁都没有外部引用。换句话说，我们的程序不再使用这些节点对象了，所以我们希望Python的垃圾回收机制能够足够智能去释放这些对象并回收它们占用的内存空间。但是这不可能，因为所有的引用计数都是1而不是0。Python的引用计数算法不能够处理互相指向自己的对象。

当然，上边举的是一个故意设计的例子，但是你的代码也许会在不经意间包含循环引用并且你并未意识到。事实上，当你的Python程序运行的时候它将会建立一定数量的“浮点数垃圾”，Python的GC不能够处理未使用的对象因为应用计数值不会到零。

这就是为什么Python要引入**Generational GC算法**的原因！正如Ruby使用一个链表(free list)来持续追踪未使用的、自由的对象一样，Python使用一种不同的链表来持续追踪活跃的对象。而不将其称之为“活跃列表”，Python的内部C代码将其称为零代(Generation Zero)。每次当你创建一个对象或其他什么值的时候，Python会将其加入零代链表：

![](https://upload-images.jianshu.io/upload_images/311496-7c9e91a54318d569.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

  
从上边可以看到当我们创建ABC节点的时候，Python将其加入零代链表。请注意到这并不是一个真正的列表，并不能直接在你的代码中访问，事实上这个链表是一个完全内部的Python运行时。  
相似的，当我们创建DEF节点的时候，Python将其加入同样的链表：

![](https://upload-images.jianshu.io/upload_images/311496-22b239ca5974128f.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

  现在零代包含了两个节点对象。(他还将包含Python创建的每个其他值，与一些Python自己使用的内部值。)


### 检测循环引用

随后，Python会循环遍历零代列表上的每个对象，检查列表中每个互相引用的对象，根据规则减掉其引用计数。在这个过程中，**Python会一个接一个的统计内部引用的数量以防过早地释放对象**。

为了便于理解，来看一个例子：

![](https://upload-images.jianshu.io/upload_images/311496-05e563a1ddcd9cd1.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

  
从上面可以看到 ABC 和 DEF 节点包含的引用数为1.有三个其他的对象同时存在于零代链表中，**蓝色的箭头指示了有一些对象正在被零代链表之外的其他对象所引用**。(接下来我们会看到，Python中同时存在另外两个分别被称为一代和二代的链表)。这些对象有着更高的引用计数因为它们正在被其他指针所指向着。

接下来你会看到Python的GC是如何处理零代链表的。

![](https://upload-images.jianshu.io/upload_images/311496-4da43891c8aaef04.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

  
**通过识别内部引用，Python能够减少许多零代链表对象的引用计数。**在上图的第一行中你能够看见ABC和DEF的引用计数已经变为零了，这意味着收集器可以释放它们并回收内存空间了。剩下的活跃的对象则被移动到一个新的链表：一代链表。

从某种意义上说，**Python的GC算法类似于Ruby所用的标记回收算法。周期性地从一个对象到另一个对象追踪引用以确定对象是否还是活跃的**，正在被程序所使用的，这正类似于Ruby的标记过程。

### Python中的GC阈值

Python什么时候会进行这个标记过程？随着你的程序运行，**Python解释器保持对新创建的对象，以及因为引用计数为零而被释放掉的对象的追踪。从理论上说，这两个值应该保持一致，因为程序新建的每个对象都应该最终被释放掉。**

当然，事实并非如此。因为循环引用的原因，并且因为你的程序使用了一些比其他对象存在时间更长的对象，从而被分配对象的计数值与被释放对象的计数值之间的差异在逐渐增长。**一旦这个差异累计超过某个阈值，则Python的收集机制就启动了**，并且触发上边所说到的零代算法，释放“**浮动的垃圾**”，并且将剩下的对象移动到一代列表。

随着时间的推移，程序所使用的对象逐渐从零代列表移动到一代列表。而Python对于一代列表中对象的处理遵循同样的方法，一旦被分配计数值与被释放计数值累计到达一定阈值，Python会将剩下的活跃对象移动到二代列表。

通过这种方法，你的代码所长期使用的对象，那些你的代码持续访问的活跃对象，会从零代链表转移到一代再转移到二代。通过不同的阈值设置，Python可以在不同的时间间隔处理这些对象。**Python处理零代最为频繁，其次是一代然后才是二代。**


### 弱代假说

来看看代垃圾回收算法的核心行为：垃圾回收器会更频繁的处理新对象。一个新的对象即是你的程序刚刚创建的，而一个来的对象则是经过了几个时间周期之后仍然存在的对象。Python会在当一个对象从零代移动到一代，或是从一代移动到二代的过程中提升(promote)这个对象。

为什么要这么做？这种算法的根源来自于弱代假说(weak generational hypothesis)。这个假说由两个观点构成：**首先是年轻的对象通常死得也快，而老对象则很有可能存活更长的时间。**

假定现在我用Python或是Ruby创建一个新对象：

![](https://upload-images.jianshu.io/upload_images/311496-c728624cf96e3248.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

  
根据假说，我的代码很可能仅仅会使用ABC很短的时间。这个对象也许仅仅只是一个方法中的中间结果，并且随着方法的返回这个对象就将变成垃圾了。大部分的新对象都是如此般地很快变成垃圾。然而，偶尔程序会创建一些很重要的，存活时间比较长的对象-例如web应用中的session变量或是配置项。

通过频繁的处理零代链表中的新对象，Python的垃圾收集器将把时间花在更有意义的地方：它处理那些很快就可能变成垃圾的新对象。同时只在很少的时候，当满足阈值的条件，收集器才回去处理那些老变量。

## del
删除元素
```python
>>> a = [1, "two", 3, "four"]
>>> del a[0]         #删除列表a中，下标为0的元素
>>> a
['two', 3, 'four']
>>> a.append("five")
>>> a.append(6)
>>> a
['two', 3, 'four', 'five', 6]
>>> del a[2:4]        #删除a从下标为2到4的元素，含头不含尾
>>> a
```

删除引用
```python
>>> x = 1
>>> del x
>>> x
Traceback (most recent call last):
File "<pyshell#6>", line 1, in <module>
x
NameError: name 'x' is not defined


>>> x = ['Hello','world']
>>> y = x
>>> y
['Hello', 'world']
>>> x
['Hello', 'world']
>>> del x
>>> x
Traceback (most recent call last):
File "<pyshell#12>", line 1, in <module>
x
NameError: name 'x' is not defined
>>> y
['Hello', 'world']
>>>
```
可以看到x和y指向同一个列表，但是删除x后，y并没有受到影响。del的是引用，而不是对象


## [Python 的元类 (metaclass)](http://blog.jobbole.com/21351/)

### 类也是对象
在理解元类之前，你需要先掌握Python中的类。Python中类的概念借鉴于[Smalltalk](https://en.wikipedia.org/wiki/Smalltalk)，这显得有些奇特。在大多数编程语言中，类就是一组用来描述如何生成一个对象的代码段。在Python中这一点仍然成立：

```python
>>>  class  ObjectCreator(object):
… 		pass
…
>>>  my_object  =  ObjectCreator()
>>>  print  my_object
<__main__.ObjectCreator object  at  0x8974f2c>
```

但是，Python中的类还远不止如此。**类同样也是一种对象**。是的，没错，就是对象。只要你使用关键字class，Python解释器在执行的时候就会创建一个对象。下面的代码段：

```python
>>> class ObjectCreator(object):
…       pass
…
```

将在内存中创建一个对象，名字就是ObjectCreator。**这个对象（类）自身拥有创建对象（类实例）的能力，而这就是为什么它是一个类的原因**。但是，**它的本质仍然是一个对象**，于是乎你可以对它做如下的操作：

1. 你可以将它赋值给一个变量
2. 你可以拷贝它
3. 你可以为它增加属性
4. 你可以将它作为函数参数进行传递

下面是示例：

```python
# 你可以打印一个类，因为它其实也是一个对象
>>> print ObjectCreator    
<class '__main__.ObjectCreator'>

# 你可以将类做为参数传给函数
>>> def echo(o):
…       print o
…
>>> echo(ObjectCreator)                
<class '__main__.ObjectCreator'>

#  你可以为类增加属性
>>> print hasattr(ObjectCreator, 'new_attribute')
Fasle
>>> ObjectCreator.new_attribute = 'foo' 
>>> print hasattr(ObjectCreator, 'new_attribute')
True
>>> print ObjectCreator.new_attribute
foo

# 你可以将类赋值给一个变量
>>> ObjectCreatorMirror = ObjectCreator 
>>> print ObjectCreatorMirror()
<__main__.ObjectCreator object at 0x8997b4c>
```

#### 动态地创建类

因为类也是对象，你可以在**运行时动态的创建它们，就像其他任何对象一样**。首先，你可以在函数中创建类，使用class关键字即可。


```python
>>> def choose_class(name):
…       if name == 'foo':
…           class Foo(object):
…               pass
…           return Foo     # 返回的是类，不是类的实例
…       else:
…           class Bar(object):
…               pass
…           return Bar
…
>>> MyClass = choose_class('foo')
>>> print MyClass              # 函数返回的是类，不是类的实例
<class '__main__'.Foo>
>>> print MyClass()            # 你可以通过这个类创建类实例，也就是对象
<__main__.Foo object at 0x89c6d4c>
```

但这还不够动态，因为你仍然需要自己编写整个类的代码。**由于类也是对象，所以它们必须是通过什么东西来生成的才对**。当你使用class关键字时，Python解释器自动创建这个对象。但就和Python中的大多数事情一样，Python仍然提供给你手动处理的方法。还记得内建函数type吗？这个古老但强大的函数能够让你知道一个对象的类型是什么，就像这样：

```python
>>> print type(1)
<type 'int'>
>>> print type("1")
<type 'str'>
>>> print type(ObjectCreator)
<type 'type'>
>>> print type(ObjectCreator())
<class '__main__.ObjectCreator'>
```

这里，**type有一种完全不同的能力，它也能动态的创建类。**
**type可以接受一个类的描述作为参数，然后返回一个类。**（我知道，根据传入参数的不同，同一个函数拥有两种完全不同的用法是一件很傻的事情，但这在Python中是为了保持向后兼容性）

type可以像这样工作：
```
type(类名,  父类的元组（针对继承的情况，可以为空），包含属性的字典（名称和值）)
```

比如下面的代码：
```python
>>> class MyShinyClass(object):
…       pass
```

可以手动像这样创建：
```python
>>> MyShinyClass = type('MyShinyClass', (), {})  # 返回一个类对象
>>> print MyShinyClass
<class '__main__.MyShinyClass'>
>>> print MyShinyClass()  #  创建一个该类的实例
<__main__.MyShinyClass object at 0x8997cec>
```

你会发现我们使用“MyShinyClass”作为类名，并且也可以把它当做一个变量来作为类的引用。类和变量是不同的，这里没有任何理由把事情弄的复杂。

type 接受一个字典来为类定义属性，因此:
```python
>>> class Foo(object):
…       bar = True
```

可以翻译为：
```python
>>>  Foo  =  type('Foo',  (),  {'bar':True})
```

并且可以将Foo当成一个普通的类一样使用：
```python
>>> print Foo
<class '__main__.Foo'>
>>> print Foo.bar
True
>>> f = Foo()
>>> print f
<__main__.Foo object at 0x8a9b84c>
>>> print f.bar
True
```

当然，你可以向这个类继承，所以，如下的代码：
```python
>>> class FooChild(Foo):
…       pass
```

就可以写成：
```python
>>> FooChild = type('FooChild', (Foo,),{})
>>> print FooChild
<class '__main__.FooChild'>
>>> print FooChild.bar   # bar属性是由Foo继承而来
True
```

最终你会希望为你的类增加方法。只需要定义一个有着恰当签名的函数并将其作为属性赋值就可以了。
```python
>>> def echo_bar(self):
…       print self.bar
…
>>> FooChild = type('FooChild', (Foo,), {'echo_bar': echo_bar})
>>> hasattr(Foo, 'echo_bar')
False
>>> hasattr(FooChild, 'echo_bar')
True
>>> my_foo = FooChild()
>>> my_foo.echo_bar()
True
```

你可以看到，在Python中，**类也是对象，你可以动态的创建类**。这就是当你使用关键字class时Python在幕后做的事情，**而这就是通过元类来实现的**。

### 到底什么是元类

**元类就是用来创建类的“东西”**。你创建类就是为了创建类的实例对象，不是吗？但是我们已经学习到了Python中的类也是对象。好吧，**元类就是用来创建这些类（对象）的**，**元类就是类的类**，你可以这样理解 为：

```python
MyClass = MetaClass()
MyObject = MyClass()
```

你已经看到了type可以让你像这样做：
```python
MyClass = type('MyClass', (), {})
```

这是因为**函数type实际上是一个元类**。type就是Python在背后用来创建所有类的元类。现在你想知道那为什么type会全部采用小写形式而不是Type呢？好吧，我猜这是为了和str保持一致性，**str是用来创建字符串对象的类，而int是用来创建整数对象的类。type就是创建类对象的类**。你可以通过检查\_\_class\_\_属性来看到这一点。Python中所有的东西，注意，我是指所有的东西——都是对象。这包括整数、字符串、函数以及类。**它们全部都是对象，而且它们都是从一个类创建而来**。

```python
>>> age = 35
>>> age.__class__
<type 'int'>
>>> name = 'bob'
>>> name.__class__
<type 'str'>
>>> def foo(): pass
>>>foo.__class__
<type 'function'>
>>> class Bar(object): pass
>>> b = Bar()
>>> b.__class__
<class '__main__.Bar'>
```

现在，对于任何一个\_\_class\_\_的\_\_class\_\_属性又是什么呢？
```python
>>> a.__class__.__class__
<type 'type'>
>>> age.__class__.__class__
<type 'type'>
>>> foo.__class__.__class__
<type 'type'>
>>> b.__class__.__class__
<type 'type'>
```

因此，**元类就是创建类这种对象的东西**。如果你喜欢的话，可以把元类称为“类工厂”（不要和工厂类搞混了:D） type就是Python的内建元类，当然了，你也可以创建自己的元类。

### \_\_metaclass\_\_ 属性

你可以在写一个类的时候为其添加\_\_metaclass\_\_属性。
```python
class Foo():
	__metaclass__ = something…
[…]
```

这里要额外注意(原文翻译有问题)：
**自定义元类不能从'object'继承**，metaclass是类的模板，所以必须从`type`类型派生。可以这么定义一个元类
```class foo(type)```，然后这么用 `class myfoo(metaclass=foo)`
全局\_\_metaclass\_\_ 只对旧式类有效。加上object作为参数就不对了。

如果你这么做了，**Python就会用元类来创建类Foo**。小心点，这里面有些技巧。你首先写下class Foo(object)，但是类对象Foo还没有在内存中创建。**Python会在类的定义中寻找\_\_metaclass\_\_属性，如果找到了，Python就会用它来创建类Foo，如果没有找到，就会用内建的type来创建这个类**。把下面这段话反复读几次。当你写如下代码时 :

```python
class Foo(Bar):
    pass
```

Python做了如下的操作：

Foo中有\_\_metaclass\_\_这个属性吗？如果是，Python会在内存中通过\_\_metaclass\_\_创建一个名字为Foo的类对象（我说的是类对象，请紧跟我的思路）。如果Python没有找到\_\_metaclass\_\_，它会继续在Bar（父类）中寻找\_\_metaclass\_\_属性，并尝试做和前面同样的操作。如果Python在任何父类中都找不到\_\_metaclass\_\_，它就会在模块层次中去寻找\_\_metaclass\_\_，并尝试做同样的操作。如果还是找不到\_\_metaclass\_\_,Python就会用内置的type来创建这个类对象。

现在的问题就是，你可以在\_\_metaclass\_\_中放置些什么代码呢？答案就是：**可以创建一个类的东西**。那么什么可以用来创建一个类呢？**type，或者任何使用到type或者子类化type的东东都可以**。

### 自定义元类

**元类的主要目的就是为了当创建类时能够自动地改变类**。通常，你会为API做这样的事情，你希望可以创建符合当前上下文的类。假想一个很傻的例子，你决定在你的模块里所有的类的属性都应该是大写形式。有好几种方法可以办到，但其中一种就是通过在模块级别设定\_\_metaclass\_\_。采用这种方法，这个模块中的所有类都会通过这个元类来创建，我们只需要告诉元类把所有的属性都改成大写形式就万事大吉了。

幸运的是，\_\_metaclass\_\_实际上可以被任意调用，它并不需要是一个正式的类（我知道，某些名字里带有‘class’的东西并不需要是一个class，画画图理解下，这很有帮助）。所以，我们这里就先以一个简单的函数作为例子开始。

```python
# 元类会自动将你通常传给‘type’的参数作为自己的参数传入
def upper_attr(future_class_name, future_class_parents, future_class_attr):
    '''返回一个类对象，将属性都转为大写形式'''
    #  选择所有不以'__'开头的属性
    attrs = ((name, value) for name, value in future_class_attr.items() if not name.startswith('__'))
    # 将它们转为大写形式
    uppercase_attr = dict((name.upper(), value) for name, value in attrs)

    # 通过'type'来做类对象的创建
    return type(future_class_name, future_class_parents, uppercase_attr)

__metaclass__ = upper_attr  #  这会作用到这个模块中的所有类

class Foo(object):
    # 我们也可以只在这里定义__metaclass__，这样就只会作用于这个类中
    bar = 'bip'

print hasattr(Foo, 'bar')
# 输出: False
print hasattr(Foo, 'BAR')
# 输出:True

f = Foo()
print f.BAR
# 输出:'bip'
```

现在让我们再做一次，这一次用一个真正的class来当做元类。
```python
# 请记住，'type'实际上是一个类，就像'str'和'int'一样
# 所以，你可以从type继承
class UpperAttrMetaClass(type):
    # __new__ 是在__init__之前被调用的特殊方法
    # __new__是用来创建对象并返回之的方法
    # 而__init__只是用来将传入的参数初始化给对象
    # 你很少用到__new__，除非你希望能够控制对象的创建
    # 这里，创建的对象是类，我们希望能够自定义它，所以我们这里改写__new__
    # 如果你希望的话，你也可以在__init__中做些事情
    # 还有一些高级的用法会涉及到改写__call__特殊方法，但是我们这里不用
    def __new__(upperattr_metaclass, future_class_name, future_class_parents, future_class_attr):
        attrs = ((name, value) for name, value in future_class_attr.items() if not name.startswith('__'))
        uppercase_attr = dict((name.upper(), value) for name, value in attrs)
        return type(future_class_name, future_class_parents, uppercase_attr)
```

但是，这种方式其实不是OOP。我们直接调用了type，而且我们没有改写父类的\_\_new\_\_方法。现在让我们这样去处理:

```python
class UpperAttrMetaclass(type):
    def __new__(upperattr_metaclass, future_class_name, future_class_parents, future_class_attr):
        attrs = ((name, value) for name, value in future_class_attr.items() if not name.startswith('__'))
        uppercase_attr = dict((name.upper(), value) for name, value in attrs)

        # 复用type.__new__方法
        # 这就是基本的OOP编程，没什么魔法
        return type.__new__(upperattr_metaclass, future_class_name, future_class_parents, uppercase_attr)
```

你可能已经注意到了有个额外的参数upperattr_metaclass，这并没有什么特别的。类方法的第一个参数总是表示当前的实例，就像在普通的类方法中的self参数一样。当然了，为了清晰起见，这里的名字我起的比较长。但是就像self一样，所有的参数都有它们的传统名称。因此，在真实的产品代码中一个元类应该是像这样的：

```python
class UpperAttrMetaclass(type):
    def __new__(cls, name, bases, dct):
        attrs = ((name, value) for name, value in dct.items() if not name.startswith('__')
        uppercase_attr  = dict((name.upper(), value) for name, value in attrs)
        return type.__new__(cls, name, bases, uppercase_attr)
```

如果使用super方法的话，我们还可以使它变得更清晰一些，这会缓解继承（是的，你可以拥有元类，从元类继承，从type继承）

```python
class UpperAttrMetaclass(type):
    def __new__(cls, name, bases, dct):
        attrs = ((name, value) for name, value in dct.items() if not name.startswith('__'))
        uppercase_attr = dict((name.upper(), value) for name, value in attrs)
        return super(UpperAttrMetaclass, cls).__new__(cls, name, bases, uppercase_attr)
```

就是这样，除此之外，关于元类真的没有别的可说的了。使用到元类的代码比较复杂，这背后的原因倒并不是因为元类本身，而是因为你通常会使用元类去做一些晦涩的事情，依赖于自省，控制继承等等。确实，用元类来搞些“黑暗魔法”是特别有用的，因而会搞出些复杂的东西来。但就元类本身而言，它们其实是很简单的：

1. 拦截类的创建
2. 修改类
3. 返回修改之后的类


**为什么要用metaclass类而不是函数?**

由于\_\_metaclass\_\_可以接受任何可调用的对象，那为何还要使用类呢，因为很显然使用类会更加复杂啊？这里有好几个原因：

1.  意图会更加清晰。当你读到UpperAttrMetaclass(type)时，你知道接下来要发生什么。
2.  你可以使用OOP编程。元类可以从元类中继承而来，改写父类的方法。元类甚至还可以使用元类。
3.  你可以把代码组织的更好。当你使用元类的时候肯定不会是像我上面举的这种简单场景，通常都是针对比较复杂的问题。将多个方法归总到一个类中会很有帮助，也会使得代码更容易阅读。
4. 你可以使用__new__, __init__以及__call__这样的特殊方法。它们能帮你处理不同的任务。就算通常你可以把所有的东西都在__new__里处理掉，有些人还是觉得用__init__更舒服些。
5. 哇哦，这东西的名字是metaclass，肯定非善类，我要小心！

**究竟为什么要使用元类？**

现在回到我们的大主题上来，究竟是为什么你会去使用这样一种容易出错且晦涩的特性？好吧，一般来说，你根本就用不上它：

>“元类就是深度的魔法，99%的用户应该根本不必为此操心。如果你想搞清楚究竟是否需要用到元类，那么你就不需要它。那些实际用到元类的人都非常清楚地知道他们需要做什么，而且根本不需要解释为什么要用元类。” —— Python界的领袖 Tim Peters

元类的主要用途是创建API。一个典型的例子是Django ORM。它允许你像这样定义：

```python
class Person(models.Model):
    name = models.CharField(max_length=30)
    age = models.IntegerField()
```

但是如果你像这样做的话：

```python
guy  =  Person(name='bob',  age='35')
print  guy.age
```

这并不会返回一个IntegerField对象，而是会返回一个int，甚至可以直接从数据库中取出数据。这是有可能的，因为models.Model定义了\_\_metaclass\_\_， 并且使用了一些魔法能够将你刚刚定义的简单的Person类转变成对数据库的一个复杂hook。Django框架将这些看起来很复杂的东西通过暴露出一个简单的使用元类的API将其化简，通过这个API重新创建代码，在背后完成真正的工作。

**结语**

首先，你知道了类其实是能够创建出类实例的对象。好吧，事实上，类本身也是实例，当然，它们是元类的实例。

```python
>>>class Foo(object): pass
>>> id(Foo)
142630324
```

**Python中的一切都是对象，它们要么是类的实例，要么是元类的实例**，**除了type。type实际上是它自己的元类**，在纯Python环境中这可不是你能够做到的，这是通过在实现层面耍一些小手段做到的。其次，元类是很复杂的。对于非常简单的类，你可能不希望通过使用元类来对类做修改。你可以通过其他两种技术来修改类：

1. 猴子补丁 （[Monkey patching](http://en.wikipedia.org/wiki/Monkey_patch)）
```python
class Foo(object):
    def bar(self):
        print 'Foo.bar' 
        
def bar(self):
    print 'Modified bar' Foo().bar()

Foo.bar = bar

Foo().bar()
```

2. 类装饰器（class decorators）


## Python 的新类和旧类















## Python 的 全局解释器锁 GIL（Global Interpreter Lock）

## Python 的编码

## Pythonic

翻转




## 上下文管理 with

## 匿名函数 lambda

```python
lambda x,y : x + y
```
常用与被Python 其他高级函数调用，`map()`，`filter()` etc...
## 高阶函数

## yield

## 装饰器
### class decorators
### 8个面试题https://zhuanlan.zhihu.com/p/30643045

### [单例模式的几种实现](https://github.com/PythonScientists/InterviewKeyOfPython/blob/master/Interview_Experience/Python%E9%9D%A2%E8%AF%95%E9%A2%98%E2%80%94%E2%80%94%E9%83%A8%E5%88%86%E4%B8%80#L845)

### 列表推导

### 字典推导？