# encoding:utf-8

"""
faiss库 IndexFlatLSH(局部敏感性hash) 索引性能测试

author  :   h-j-13
time    :   2018-6-22
"""

import time
import numpy

import faiss
from recall_data import recall_data

# 基本参数
d = 300  # 向量维数
data_size = 10000  # 数据库大小
k = 50
nbits = 64          # 生成的hash值长度

# 生成测试数据
numpy.random.seed(13)
data = numpy.random.random(size=(data_size, d)).astype('float32')
test_data = recall_data

# 创建索引模型并添加向量
index = faiss.IndexLSH(d, nbits)
# LSH无需训练训

# 添加数据
start_time = time.time()
index.add(data)  # 添加索引可能会有一点慢
print "Add vector Used %.2f sec." % (time.time() - start_time)

start_time = time.time()
D, I = index.search(data[:50], k)  # 搜索每一个数据的的k临近向量

# 输出结果
print "Used %.2f ms" % ((time.time() - start_time) * 1000)
recall_1_count = 0
recall_50_count = 0
for (search_vec, test_vec) in zip(I, test_data):
    if test_vec[0] in search_vec:
        recall_1_count += 1
    recall_50_count += len(set(search_vec.tolist()) & set(test_vec))
print "recall1@50 = " + str(recall_1_count / (50.0))
print "recall50@50 = " + str(recall_50_count / (50.0 * 50.0))
