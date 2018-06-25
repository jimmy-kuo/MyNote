# encoding:utf-8

"""
faiss库 - add with ids 方法学习
(为变量添加别名 - ID映射)
author  :   h-j-13
time    :   2018-6-25

总结
------
1. 对于支持 add_with_ids()方法的index

ids = list[]
ids = numpy.array(ids).astype('int')    # 转换成int型一维数组
index.add_with_ids(data,ids)

2. 对于不支持 add_with_ids()的 index 借助 IndexIDMap

ids = list[]
ids = numpy.array(ids).astype('int')    # 同上
index = ...
index2 = faiss.IndexIDMap（index）
index2.add_with_ids(data, ids)
D, I = index2.search(data[:50], k)      # 注意这里对索引的add 和 search
                                        # 都需要调用index2 来进行操作
                                        # 来获取向量正确的id
"""

import time
import numpy
import faiss

# 基本参数
d = 300  # 向量维数
data_size = 10000  # 数据库大小
k = 50
nlist = 100  # 分割成单元格数

# 生成测试数据
numpy.random.seed(13)
data = numpy.random.random(size=(data_size, d)).astype('float32')
ids = [i for i in xrange(30000, 40000)]
ids = numpy.array(ids).astype('int')

# 构建索引
index = faiss.IndexFlatL2(d)
index2 = faiss.IndexIDMap(index)
# 添加数据
start_time = time.time()
index2.add_with_ids(data, ids)  # 添加索引可能会有一点慢
print "Add vector Used %.2f sec." % (time.time() - start_time)

# 搜索
start_time = time.time()
D, I = index2.search(data[:50], k)  # 搜索
print "nprobe=1 search Used %.2f ms" % ((time.time() - start_time) * 1000)
print I[-5:]
