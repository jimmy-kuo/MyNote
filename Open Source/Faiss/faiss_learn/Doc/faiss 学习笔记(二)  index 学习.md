## 前言
faiss 的索引种类很多, 并且可以嵌套使用. 不同的索引有不同的实现方式及试用条件,根据数据集的特性和运行机器的性能来选择合适的索引是进行开发的第一步

## faiss 核心组件
在了解深入了解索引之前, 我们需要直到 faiss是基于三个高效实现基本算法
* 聚类 Faiss提供了一个高效的k-means实现
* PCA降维算法
* PQ(ProductQuantizer)编码/解码

## 基础索引
![](https://upload-images.jianshu.io/upload_images/5617720-56b8280f2c78029b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

有关于基础索引所使用的参数及其含义, 请参考 官方wiki - [Faiss indexes](https://github.com/facebookresearch/faiss/wiki/Faiss-indexes)

#### 索引工厂模式

另外,faiss实现了一个索引工厂模式,可以通过字符串来灵活的创建索引,例如
```python
index = faiss.index_factory(d,"PCA32,IVF100,PQ8 ")
```
该字符串的含义如下
**使用PCA算法将向量降维到32维, 划分成100个nprobe (搜索空间), 通过PQ算法将每个向量压缩成8bit**

#### 为向量添加唯一ID
1. 对于支持 `add_with_ids()` 方法的index
```python
ids = list[] ...
ids = numpy.array(ids).astype('int')    # 转换成int型一维数组
index.add_with_ids(data,ids)
```
2. 对于不支持 `add_with_ids()` 的 index 借助 `IndexIDMap`
```python
ids = list[] ...
ids = numpy.array(ids).astype('int')    # 同上
index = ...
index2 = faiss.IndexIDMap（index）
index2.add_with_ids(data, ids)
D, I = index2.search(data[:50], k)      # 注意这里对索引的add 和 search
                                        # 都需要调用index2 来进行操作
                                        # 来获取向量正确的id 
```


## 如何选择合适的索引 

#### 1. 你需要确切的结果吗？
唯一可以保证精确结果的索引是`IndexFlatL2`。它为其他指标的结果提供了基准。它不会压缩矢量，但不会增加它们之上的开销。它不支持使用ids（`add_with_ids`方法）添加向量及向量的名称，所以如果需要的话`add_with_ids`，使用`"IDMap,Flat"`。该索引不需要训练,也没有额外的参数.
*在GPU上支持：是的*

#### 2. 内存是问题吗？

请记住，**所有的Faiss索引都将向量存储在RAM中**。以下内容认为，如果不需要准确的结果，RAM是限制因素，并且在内存约束条件下，我们将把精确度和速度进行折衷。

* 如果不： `"HNSWx"`

如果你有很多RAM或数据集很小，HNSW是最好的选择，它是一个非常快速和准确的指标。4 <= `x`<= 64是每个矢量的链接数量，越高越准确，但使用更多的RAM。速度 - 精度权衡是通过`efSearch`参数设置的。内存使用量为每个矢量（d * 4 + x * 2 * 4）个字节。
HNSW只支持顺序添加（不`add_with_ids`），所以在这里再次，`IDMap`如果需要前缀。HNSW不需要培训，也不支持从索引中移除向量。
*GPU支持：不支持*

* 如果有的话 `"...,Flat"`

`"..."`意味着必须预先执行数据集的聚类（请参阅下文）。聚类后​​，`"Flat"`只将矢量组织成桶，所以它不压缩它们，存储大小与原始数据集相同。速度和精度之间的权衡是通过`nprobe`参数设置的。
*在GPU上支持：是（但是请参阅下文，也必须支持聚类方法）*

* 如果相当重要的话 `"PCARx,...,SQ8"`

如果存储整个向量太昂贵，则执行两个操作：
*   一个PCA的维度`x`来减少维度
*   每个矢量分量的标量量化为1个字节。
因此总存储量是`x`每个向量的字节数。
*GPU支持：不支持*

* 如果非常重要的话 `"OPQx_y,...,PQx"`

`PQx`使用输出`x`字节码的产品量化器压缩矢量。`x`通常<= 64，对于较大的代码，SQ通常是准确和快速的。OPQ是向量的线性转换，使它们更容易压缩。`y`是这样一个维度：
*   `y`是`x`（必需）的倍数
*   `y` <= d，其中d是输入向量的维数（最好）
*   y <= 4 * x（优选）
*GPU支持：是（注意：OPQ转换是用软件完成的，但它不是性能关键）*

#### 3.数据集有多大？

这个问题用于填充索引工厂字符串（`...`上面）。数据集划分成多个空间，并在搜索时，只有一小部分空间被访问（`nprobe`）。聚类是在数据集向量的代表性样本上执行的，通常是数据集的样本。我们指出这个样本的最佳尺寸。

* 如果低于1M个矢量： `"...,IVFx,..."`

其中x是4 \* sqrt（N）到16 \* sqrt（N），N是数据集的大小。这只是用k-means对向量进行聚类。您需要30 *x和256* x的训练矢量（越多越好）
*GPU支持：是的*

* 如果1M - 10M： `"...,IMI2x10,..."`
（这里`x`是一个字母x，不是数字）
IMI还在训练矢量上执行具有2 ^ 10质心的k均值，但它在矢量的前半部分和后半部分独立地执行。这将簇的数量增加到2 ^（2 * 10）。您将需要大约64 * 2 ^ 10个训练载体。
*GPU支持：不支持*

* 如果10M - 100M： `"...,IMI2x12,..."`
同上，用12替换10。
*GPU支持：不支持*

* 如果100M-1B： `"...,IMI2x14,..."`
同上，用14替换10。
*GPU支持：不支持*

## 索引的特殊操作
#### 1.从索引重建向量

给定它们的ID，方法`reconstruct`并`reconstruct_n`从索引重建一个或多个向量。
用法示例：[test_index_composite.py](https://github.com/facebookresearch/faiss/blob/master/tests/test_index_composite.py#L35)
支持`IndexFlat`，`IndexIVFFlat`（`make_direct_map`先调用），`IndexIVFPQ`（相同）`IndexPreTransform`

#### 2. 从索引中删除元素

该方法`remove_ids`从索引中删除矢量的一个子集。它需要`IDSelector`为索引中的每个元素调用一个对象来决定是否应该删除它。`IDSelectorBatch`将为索引列表执行此操作。
注意，因为它传递了整个数据库，所以只有在需要删除大量向量时才有效。
例如：[test_index_composite.py](https://github.com/facebookresearch/faiss/blob/master/tests/test_index_composite.py#L25)
支持索引`IndexFlat`，`IndexIVFFlat`，`IndexIVFPQ`，`IDMap`。

#### 3.范围搜索

该方法`range_search`返回查询点周围半径范围内的所有矢量（与k最近的那个相反）。由于每个查询的结果列表大小不同，因此必须专门处理
支持：`IndexFlat`，`IndexIVFFlat`。

#### 4.分割和合并索引

方法：

*   `merge_from` 合并索引中的向量
*   `copy_subset_to` 将一个子集复制到另一个索引。用法示例：[在GPU上构建索引并在之后将它们移动到CPU](https://github.com/facebookresearch/faiss/blob/master/benchs/bench_gpu_1bn.py#L541)
这些函数仅适用于`IndexIVF`子类，因为它们主要用于大型索引。


## 线程和异步

#### 1.线程安全
Faiss CPU索引**对于并发搜索是线程安全的**，而其他操作不会更改索引。**多线程使用改变索引的函数需要实现互斥**。

Fais **GPU索引不是线程安全的，即使只读函数也是如此**。这是因为 StandardGpuResourcesGPU Faiss不是线程安全的。StandardGpuResources必须为每个主动运行GPU Faiss索引的线程创建单个对象。由单个CPU线程管理的多个GPU索引并共享相同StandardGpuResources（实际上应该，因为它们可以使用GPU内存的相同临时区域）。一个GpuResources对象可以支持多个设备，但只能从一个调用CPU线程中支持。多GPU Faiss在内部运行来自不同线程的不同GPU索引。

#### 2.内部线程

Faiss本身有多种不同的内部线程。对于CPU Faiss，**索引的三个基本操作（训练，添加，搜索）在内部是多线程的**。线程化是通过OpenMP和一个多线程的BLAS实现完成的，通常是MKL。Faiss不设置线程数量。可以通过环境变量`OMP_NUM_THREADS`或通过调用随时调整此数量`omp_set_num_threads (10)`。这个函数在Python中通过faiss可用。

对于`add`和`search`函数，查询或添加单个向量不是或仅部分是多线程的。

#### 3.搜索的性能

在批量查询向量时可以获得的最佳性能(QPS)。

如果查询是逐个提交的，那么它们将在调用线程中执行（目前所有索引都是这样的，未来它可能会发生变化）。所以多线程调用`search`单例查询也是相对高效的。

然而，**从多个线程调用批量查询的效率非常低，这会产生比核心更多的线程**。


## 参考文献

[Faiss building blocks: clustering, PCA, quantization](https://github.com/facebookresearch/faiss/wiki/Faiss-building-blocks:-clustering,-PCA,-quantization)
[Faiss indexes](https://github.com/facebookresearch/faiss/wiki/Faiss-indexes)
[Guidelines to choose an index](https://github.com/facebookresearch/faiss/wiki/Guidelines-to-choose-an-index)
[Special operations on indexes](https://github.com/facebookresearch/faiss/wiki/Special-operations-on-indexes)