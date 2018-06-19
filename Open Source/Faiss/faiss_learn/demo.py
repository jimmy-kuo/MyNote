# encoding:utf-8

"""
faiss库 向量相似性搜索框架学习
搜索每一个向量的k临近向量

author  :   h-j-13
time    :   2018-6-19
ref     :   https://github.com/facebookresearch/faiss/blob/dd6c9ebf2da3123e055ffdc99f9b597e8b97de04/tutorial/python/1-Flat.py
"""

import time
import numpy

import faiss

# 基本参数
d = 300  # dimension
data_size = 10000  # database size
k = 50

# 生成测试数据
numpy.random.seed(13)
data = numpy.random.random(size=(data_size, d)).astype('float32')
# data[:, 0] += numpy.arange(data_size) / 1000.  # numpy中特殊写法,给每个向量第一维 + 0.0..1 ~ 0.9..9

print str(data_size) + " 个 " + str(d) + " 维向量,每个向量的 k=" + str(k) + "临近搜索"
start = time.time()

# 创建索引模型并添加向量
index = faiss.IndexFlatL2(d)  # 创建 d 维的 FlatL2 索引
# print(index.is_trained)       # 该索引是否训练过
# print(index.ntotal)           # 索引容量
index.add(data)  # 将数据添加进索引
D, I = index.search(data, k)  # 搜索每一个数据的的k临近向量

# 输出结果
print "Used %.2f sec." % (time.time() - start)
# print D
print I

# --------------result------------------
# (k = 50, d=30000, [0~1], 1CPU, 1G)
# n = 1000      0.03 sec.
# n = 10000     1.22 sec.
# n = 100000    104.21 sec.
# n = 250000    640.89 sec.
# n = 350000    1256.30 sec.
# n = 1000000   MemoryError X
