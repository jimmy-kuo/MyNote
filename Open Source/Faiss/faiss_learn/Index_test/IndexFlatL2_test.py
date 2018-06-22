# encoding:utf-8

"""
faiss库 IndexFlatL2 索引性能测试

author  :   h-j-13
time    :   2018-6-22
"""

import time
import numpy

import faiss
from recall_data import recall_data

# 基本参数
d = 300                 # 向量维数
data_size = 10000       # 数据库大小
k = 50

# 生成测试数据
numpy.random.seed(13)
data = numpy.random.random(size=(data_size, d)).astype('float32')
# data[:, 0] += numpy.arange(data_size) / 1000.  # numpy中特殊写法,给每个向量第一维 + 0.0..1 ~ 0.9..9

# 创建索引模型并添加向量
index = faiss.IndexFlatL2(d)                    # 创建 d 维的 FlatL2 索引
# print(index.is_trained)                       # 该索引是否训练过
# print(index.ntotal)                           # 索引容量
start_time = time.time()
index.add(data)                                 # 将数据添加进索引
print "Add vector Used %.2f sec." % (time.time() - start_time)

start_time = time.time()
D, I = index.search(data[:50], k)               # 搜索每一个数据的的k临近向量
# 输出结果
print "Used %.2f ms" % ((time.time() - start_time)*1000)
# print D
with open("123.data","w") as f:
    f.writelines(str(I.tolist()))
