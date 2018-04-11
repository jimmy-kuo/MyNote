## 1. 前言
列表是Python中**最基本的数据结构**。类似于数据结构中的**广义表**[[?]](https://blog.csdn.net/qq_15037231/article/details/52318594)。
列表是最常用的Python数据类型，它可以作为一个方括号内的逗号分隔值出现。创建一个列表，只要把逗号分隔的不同的数据项使用方括号括起来即可
```python
list1 = [1, 2, 3]
```
**列表的数据项不需要具有相同的类型**,甚至另一个列表也可以是列表的一个数据项
```python
list2 = ['a', 'b', [1, 2, 3] ]
list3 = [1, 2, list1]
```
## 2. 使用
列表都可以进行的操作包括**索引**，**切片**，**添加**，**删除**，**检查成员**，**复制、排序、扩展**等操作。
如果你还不熟悉Python的列表 >>> [Python 列表(List) | 菜鸟教程](http://www.runoob.com/python/python-lists.html) 

### list常见方法
2.1 count()
统计列表中某一项出现的次数
```
>>> list1 = [1,2,3]
>>> list1.count(2)
1
```

2.2 append()
向列表末尾添加一个object
```python
>>> list1 = [1,2,3]
>>> list1.append(4)
>>> list1
[1, 2, 3, 4]
```

2.3 index()
获取某一个object在list中第一次出现的下标, 当不存在该object时会报错,产生一个`ValueError`异常
```python
>>> list1.index(4)
3

>>> list1.index(-1)
Traceback (most recent call last):
  File "<input>", line 1, in <module>
ValueError: -1 is not in list

# 检查某一范围内是否有某object,有则返回该object的下标
>>>
```
2.4 sort()
对列表内元素按照一定规则排序
```python
# 默认升序
>>> list2 = [1,3,5,2,4,6]
>>> list2.sort()
>>> list2
[1, 2, 3, 4, 5, 6]

# 通过sort()方法生成降序
>>> list2.sort(reverse=True)
>>> list2
[6, 5, 4, 3, 2, 1]

# 自定义排序方法 (根据字符的ascii码大小排序
>>> list3 = ['a', 'b', 'C', '0', 'A']
>>> list3.sort(cmp=lambda x, y: 1 if ord(x) >= ord(y) else -1)
>>> list3
['0', 'A', 'C', 'a', 'b']
```

**值得一提的是** 这里的底层所使用的排序方法python中比较常见的timsort(可以视为归并排序的改进版本,对于较小的数据块采用插入排序. 然后合并每个有序部分,是一个**平均时间复杂度为O(nlogn)**,**空间复杂度O(n)** 的**稳定**排序算法)

更多有关Timsort的内容 >>> [Timsort原理介绍](https://blog.csdn.net/yangzhongblog/article/details/8184707)
Python有关list排序的官方文档 [listsort](http://svn.python.org/projects/python/trunk/Objects/listsort.txt)

2.5 extend()
扩展列表,将extend中可迭代对象的每一个元素依次放入之前列表的后方
```python
>>> list1
[1, 2, 3, 4]
>>> list2
[6, 5, 4, 3, 2, 1]
>>> list1.extend(list2)
>>> list1
[1, 2, 3, 4, 6, 5, 4, 3, 2, 1]
```

2.6 insert()
在列表指定位置插入元素
```python
>>> list1 = [1,2,3]
>>> list1.insert(0,-1)
>>> list1
[-1, 1, 2, 3]
>>> list1.insert(1,10)
>>> list1
[-1, 10, 1, 2, 3]
```

2.7 pop()
弹出列表指定位置的元素,并且返回这个元素
```
>>> list1 = [1,2,3]
>>> list1.pop()
3
>>> list1
[1, 2]
>>> list1.pop(1)
2
>>> list1
[1]

```

2.8 remove()
移除列表**第一次**出现的某个object
```python
>>> list1 = [1,2,3,3,4,5]
>>> list1.remove(3)
>>> list1
[1, 2, 3, 4, 5]
```

2.9 reverse()
反序一个列表
```python
>>> list1 = [1,2,3,4,5]
>>> list1.reverse()
>>> list1
[5, 4, 3, 2, 1]
```

2.10 in
检测一个object是否在列表中
```python
>>> list1 = [1,2,3]
>>> 1 in list1
True
>>> 0 in list1
False
```


2.11 max(), min()
获取列表中元素的最大,最小值
```python
>>> list1
[1, 2, 3]
>>> min(list1)
1
>>> max(list1)
3
```

2.12 len()
获取列表长度(列表中若有嵌套列表,不论其多长也只会被计算为1)
```python
>>> list2 = [1,2,[1,2,3,4,5]]
>>> len(list2)
3
```
len() 其实是一个比较神奇的方法,它是由Cpython直接调用python对象结构体中的计数变量所得到的结果.速度非常快 时间复杂度是O(1)

## 3. 分析
Python官方文档中写道
> Internally, a list is represented as an array; 
the largest costs come from growing beyond the current allocation size (because everything must move), or from inserting or deleting somewhere near the beginning (because everything after that must move). If you need to add/remove at both ends, consider using a collections.deque instead.

简单翻译一下:
list内部是通过**数组实现**的,
其最大的时间开销在于:
1. 长度超过了默认的最大长度,需要扩展长度的时候(原列表的每一项都要被移动)
2. 在列表靠近开始的地方进行插入或者删除操作.(插入或者删除位置之后的每一项元素都要被移动)
如果你需要频繁的插入或者删除头尾部分的元素,考虑去使用 `collections.deque` (双端队列) 代替

list各个方法的时间复杂度
![list各个方法的时间复杂度](https://upload-images.jianshu.io/upload_images/5617720-c7e5345d13eba8c8.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

可以看到在尾部插入,获取和修改元素 时间复杂度都是O(1)
而在其他部分插入元素,删除都是O(n),比较符合数组的时间复杂度特征

## 底层实现
最后我们关心一下list的底层实现方式,就可以更好的理解列表之前所分析的各个方法的时间复杂度.
由于Python最主流的解释器还是CPython,下面介绍一下CPython的内部实现.

### 3.1 列表对象的 C 语言结构体
Cpython 中的列表实现类似于下面的 C 结构体。ob_item 是指向列表对象的指针数组。allocated 是申请内存的槽的个数。
```c
typedef struct {
    PyObject_VAR_HEAD
    PyObject **ob_item;
    Py_ssize_t allocated;
} PyListObject;
```
### 3.2 列表初始化
看看初始化一个空列表的时候发生了什么，例如：l = []。
```c
arguments: size of the list = 0
returns: list object = []
PyListNew:
    nbytes = size * size of global Python object = 0
    allocate new list object
    allocate list of pointers (ob_item) of size nbytes = 0
    clear ob_item
    set list's allocated var to 0 = 0 slots
    return list object
```
要分清列表大小和分配的槽大小，这很重要。列表的大小和 len(l) 的大小相同。分配槽的大小是指已经在内存中分配了的槽空间数。**通常分配的槽的大小要大于列表大小**，这是为了避免每次列表添加元素的时候都调用分配内存的函数。下面会具体介绍。

### 3.3 Append 操作
向列表添加一个整数：l.append(1) 时发生了什么？调用了底层的 C 函数 app1()。
```c
arguments: list object, new element
returns: 0 if OK, -1 if not
app1:
    n = size of list
    call list_resize() to resize the list to size n+1 = 0 + 1 = 1
    list[n] = list[0] = new element
    return 0
```
下面是 list_resize() 函数。它会多申请一些内存，避免频繁调用 list_resize() 函数。列表的增长模式为：0，4，8，16，25，35，46，58，72，88……

```c
arguments: list object, new size
returns: 0 if OK, -1 if not
list_resize:
    new_allocated = (newsize >> 3) + (newsize < 9 ? 3 : 6) = 3
    new_allocated += newsize = 3 + 1 = 4
    resize ob_item (list of pointers) to size new_allocated
    return 0
```
现在分配了 4 个用来装列表元素的槽空间，并且第一个空间中为整数 1。如下图显示 l[0] 指向我们新添加的整数对象。虚线的方框表示已经分配但没有使用的槽空间。

列表**追加元素**操作的平均复杂度为 O(1)。

![](http://upload-images.jianshu.io/upload_images/5617720-27d428333c201ed1.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

继续添加新的元素：l.append(2)。调用 list_resize 函数，参数为 n+1 = 2， 但是因为已经申请了 4 个槽空间，所以不需要再申请内存空间。再添加两个整数的情况也是一样的：l.append(3)，l.append(4)。下图显示了我们现在的情况。

![](http://upload-images.jianshu.io/upload_images/5617720-76ac0a9dd5841b22.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 3.4 Insert 操作
在列表偏移量 1 的位置插入新元素，整数 5：l.insert(1,5)，内部调用ins1() 函数。
```c
arguments: list object, where, new element
returns: 0 if OK, -1 if not
ins1:
    resize list to size n+1 = 5 -> 4 more slots will be allocated
    starting at the last element up to the offset where, right shift each element 
    set new element at offset where
    return 0
```
![](https://upload-images.jianshu.io/upload_images/5617720-0341e78cf5f3a78f.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

虚线的方框依旧表示已经分配但没有使用的槽空间。现在分配了 8 个槽空间，但是列表的大小却只是 5。

列表插入操作的平均复杂度为 O(n)。

### 3.5 Pop 操作

取出列表最后一个元素 即l.pop()，调用了 listpop() 函数。在 listpop() 函数中会调用 list_resize 函数，**如果取出元素后列表的大小小于分配的槽空间数的一半**，将会缩减列表的大小。
```c
arguments: list object
returns: element popped
listpop:
    if list empty:
        return null
    resize list with size 5 - 1 = 4. 4 is not less than 8/2 so no shrinkage
    set list object size to 4
    return last element
```
列表 pop 操作(pop-last)的平均复杂度为 O(1) 。

![](https://upload-images.jianshu.io/upload_images/5617720-56fd8af9f155b227.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

可以看到 pop 操作后槽空间 4 依然指向原先的整数对象，但是最为关键的是现在列表的大小已经变为 4。

继续 pop 一个元素。在 list_resize() 函数中，size – 1 = 4 – 1 = 3 已经小于所分配的槽空间大小的一半，所以缩减分配的槽空间为 6，同时现在列表的大小为 3。

可以看到槽空间 3 和 4 依然指向原先的整数，但是现在列表的大小已经变为 3。

![](https://upload-images.jianshu.io/upload_images/5617720-b70831846cdb3e9a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 3.6 Remove 操作
Python 的列表对象有个方法，删除指定的元素： l.remove(5)。底层调用 listremove() 函数。
```c
arguments: list object, element to remove
returns none if OK, null if not
listremove:
    loop through each list element:
        if correct element:
            slice list between element's slot and element's slot + 1
            return none
    return null
```

为了做列表的切片并且删除元素，调用了 list_ass_slice() 函数，它的实现方法比较有趣。我们在删除列表位置 1 的元素 5 的时候，低位的偏移量为 1 同时高位的偏移量为 2.

```c
arguments: list object, low offset, high offset
returns: 0 if OK
list_ass_slice:
    copy integer 5 to recycle list to dereference it
    shift elements from slot 2 to slot 1
    resize list to 5 slots
    return 0
```
列表 remove 操作的复杂度为 O(n)。

![](https://upload-images.jianshu.io/upload_images/5617720-e92fb679a7d367b3.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

## 参考文献
[TimeComplexity](https://wiki.python.org/moin/TimeComplexity)
[listsort](http://svn.python.org/projects/python/trunk/Objects/listsort.txt)
[Python 列表(List)](http://www.runoob.com/python/python-lists.html)
[深入 Python 列表的内部实现](http://python.jobbole.com/82549/)
[Python列表：初学者应该懂得操作和内部实现](https://mp.weixin.qq.com/s/IkFak4iYYqW7u61P7eu22g)