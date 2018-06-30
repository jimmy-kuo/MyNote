# encoding:utf-8

"""
faiss库 IndexFlatIP(点积) 索引性能测试

author  :   h-j-13
time    :   2018-6-22
"""

import time
import numpy

import faiss
from recall_data import *

# 基本参数
d = 300

# 向量维数
data_size = 100000  # 数据库大小
k = 10

test_size = 50

# 生成测试数据
numpy.random.seed(13)
data = numpy.random.random(size=(data_size, d)).astype('float32')

# 创建索引模型并添加向量
index = faiss.index_factory(d, "PCAR256,IVF300,SQ8")
index.train(data)
print "Train index complete!"
start_time = time.time()
index.add(data)  # 将数据添加进索引
print "Add vector Used %.2f sec." % (time.time() - start_time)

start_time = time.time()
_, I = index.search(data[:test_size], k)  # 搜索每一个数据的的k临近向量
print "Used %.2f ms per vec" % ((time.time() - start_time) * 1000 / test_size)

r1count = 0
r50count = 0
r100count = 0
r500count = 0
r1000count = 0

for (search_vec, v50, v100, v500, v1000) in zip(I, r50, r100, r500, r1000):
    if search_vec[0] == v50[0]:
        r1count += 1
    r50count += len(set(search_vec.tolist()) & set(v50))
    r100count += len(set(search_vec.tolist()) & set(v100))
    r500count += len(set(search_vec.tolist()) & set(v500))
    r1000count += len(set(search_vec.tolist()) & set(v1000))

print "recall1@1 = " + str(r1count / float(test_size))
print "recall%d@50 = " % k + str(r50count / float(test_size))
print "recall%d@100 = " % k + str(r100count / float(test_size))
print "recall%d@500 = " % k + str(r500count / float(test_size))
print "recall%d@1000 = " % k + str(r1000count / float(test_size))
