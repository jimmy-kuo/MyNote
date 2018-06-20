faiss 特性梳理
-------------
来自[faiss wiki](https://github.com/facebookresearch/faiss/wiki)及[官方文献](https://code.facebook.com/posts/1373769912645926/faiss-a-library-for-efficient-similarity-search/)

### 特点  
通过Faiss，我们引入了一个解决上述限制的库。其优点包括：

* Faiss提供了多种相似性搜索方法，涵盖广泛的使用权衡。
* Faiss针对内存使用和速度进行了优化。
* Faiss为最相关的索引方法提供了最先进的GPU实现。

> With Faiss, we introduce a library that addresses the limitations mentioned above. Among its advantages:
>
>* Faiss provides several similarity search methods that span a wide spectrum of usage trade-offs.
>* Faiss is optimized for memory usage and speed.
>* Faiss offers a state-of-the-art GPU implementation for the most relevant indexing methods.


### 指标
* 速度。
需要多长时间才能找到与查询最相似的10个（或其他数字）向量？希望比蛮力算法所需的时间少; 否则，索引的目的是什么？
* 内存使用情况。
该方法需要多少内存？比原始矢量多还是少？**Faiss支持仅从RAM中搜索**，因为磁盘数据库的速度要慢几个数量级。是的，即使是固态硬盘。
* 准确性。
返回的结果列表与蛮力搜索结果相匹配的程度如何？通过计算结果列表中最先返回真实最近邻居的查询数量（称为1-recall @ 1），或者通过测量在10中返回的10个最近邻居的平均部分，可以评估精度第一个结果（the “10-intersection” measure）。

>Speed. How long does it take to find the 10 (or some other number) most similar vectors to the query? Hopefully less time than the brute-force algorithm needs; otherwise, what’s the point of indexing?  
>
> Memory usage. How much RAM does the method require? More or less than the original vectors? Faiss supports searching only from RAM, as disk databases are orders of magnitude slower. Yes, even with SSDs.
>
>Accuracy. How well does the returned list of results match the brute-force search results? Accuracy can be evaluated by counting the number of queries for which the true nearest neighbor is returned first in the result list (a measure called 1-recall@1), or by measuring the average fraction of 10 nearest neighbors that are returned in the 10 first results (the “10-intersection” measure).

### 压缩矢量  
我们通常会评估固定内存使用情况下速度和精度之间的折衷。Faiss专注于**压缩原始矢量**的方法，因为它们是唯一可以扩展到数十亿矢量数据集的方法：每个矢量32字节占用大量内存，因此必须对10亿个矢量进行索引。

许多索引库存针对大约100万个向量而建，我们称之为小规模。例如，[nmslib](https://github.com/nmslib/nmslib)包含非常高效的算法。它比Faiss快，但需要更多的存储空间。

>We usually evaluate the trade-off between speed and accuracy for a fixed memory usage. Faiss focuses on methods that compress the original vectors, because they’re the only ones that scale to data sets of billions of vectors: 32 bytes per vector takes up a lot of memory when 1 billion vectors must be indexed.
>
>Many indexing libraries exist for around 1 million vectors, which we call small scale. For example, nmslib contains very efficient algorithms for this. It’s faster than Faiss but requires significantly more storage.

## 10亿 向量选择索引

为了评估，我们将内存使用限制为30 GB的RAM。这个内存约束指导我们选择索引方法和参数。在Faiss中，索引方法表示为一个字符串; 在这种情况下，**OPQ20_80，IMI2x14，PQ20**。

字符串表示应用于**向量的预处理步骤**（OPQ20_80），指示如何**分割数据**的选择机制（IMI2x14），以及指示**向量用产品量化器（PQ）编码的编码组件**（PQ20）生成20个字节的代码。因此，内存使用情况（包括开销）低于30 GB的RAM。

一旦选择索引类型，就可以开始索引。该算法处理10亿个矢量并将其放入索引。该索引可以存储在磁盘上或立即使用，并且索引的搜索,添加和删除操作可以间隔执行。

>For the sake of evaluation, we limit the memory usage to 30 GB of RAM. This memory constraint guides our choice of an indexing method and parameters. In Faiss, indexing methods are represented as a string; in this case, OPQ20_80,IMI2x14,PQ20.
>
>The string indicates a pre-processing step (OPQ20_80) to apply to the vectors, a selection mechanism (IMI2x14) indicating how the database should be partitioned, and an encoding component (PQ20) indicating that vectors are encoded with a product quantizer (PQ) that generates 20-byte codes. Therefore the memory usage, including overheads, is below 30 GB of RAM.
>
>We know this sounds a bit technical, and that’s why the Faiss documentation provides guidelines on how to choose the index best adapted to your needs.
>
>Once the index type is chosen, indexing can begin. The algorithm processes the 1 billion vectors and puts them into an index. The index can be stored on disk or used immediately, and searches and additions/removals to the index can be interleaved.

## GPUs

对于以前GPU的相似搜索实现，k选择（找到k最小或最大元素）一直是性能问题，因为典型的CPU算法（例如堆选择）不是GPU友好的。对于Faiss GPU，我们设计了文献中已知的最快小型k选择算法（k <= 1024）。所有中间状态完全保存在寄存器中，有助于提高速度。由峰值GPU内存带宽给出，它能够一次完成k个输入数据的选择，最高可达55％的峰值性能。因为它的状态只保留在寄存器文件中，所以它可以与其他内核融合，因此可以将其本身用于快速精确和近似的搜索算法。

高效的平铺策略和用于近似搜索的内核的实现受到了很多关注。多GPU支持由分片或复制数据提供; 一个不限于单个GPU上的可用内存。还提供了半精度浮点支持（float16），完整的float16计算支持在早期架构中提供的GPU和中间float16存储。我们发现编码向量为float16会产生加速，几乎不会损失精度。