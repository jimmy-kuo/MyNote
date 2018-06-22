# encoding:utf-8

"""
faiss库 IndexIVFFlat 索引性能测试

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
nlist = 100  # 分割成单元格数

# 生成测试数据
numpy.random.seed(13)
data = numpy.random.random(size=(data_size, d)).astype('float32')
test_data = recall_data

# 构建索引
quantizer = faiss.IndexFlatL2(d)
index = faiss.IndexIVFFlat(quantizer, d, nlist, faiss.METRIC_L2)

# 　训练数据
start_time = time.time()
assert not index.is_trained
index.train(data)
assert index.is_trained
print "Train Index Used %.2f sec." % (time.time() - start_time)

# 添加数据
start_time = time.time()
index.add(data)  # 添加索引可能会有一点慢
print "Add vector Used %.2f sec." % (time.time() - start_time)

# 搜索
start_time = time.time()
D, I = index.search(data[:50], k)  # 搜索
print "nprobe=1 search Used %.2f ms" % ((time.time() - start_time) * 1000)
recall_1_count = 0
recall_50_count = 0
for (search_vec, test_vec) in zip(I, test_data):
    if test_vec[0] in search_vec:
        recall_1_count += 1
    recall_50_count += len(set(search_vec.tolist()) & set(test_vec))
print "recall1@50 = " + str(recall_1_count / (50.0))
print "recall50@50 = " + str(recall_50_count / (50.0 * 50.0))

index.nprobe = 5  # 默认 nprobe 是1 ,可以设置的大一些试试

start_time = time.time()
D, I = index.search(data[:50], k)  # 搜索
print "nprobe=5 search Used %.2f ms" % ((time.time() - start_time) * 1000)
recall_1_count = 0
recall_50_count = 0
for (search_vec, test_vec) in zip(I, test_data):
    if test_vec[0] in search_vec:
        recall_1_count += 1
    recall_50_count += len(set(search_vec.tolist()) & set(test_vec))
print "recall1@50 = " + str(recall_1_count / (50.0))
print "recall50@50 = " + str(recall_50_count / (50.0 * 50.0))

index.nprobe = 10
start_time = time.time()
D, I = index.search(data[:50], k)  # 搜索
print "nprobe=10 search Used %.2f ms" % ((time.time() - start_time) * 1000)
recall_1_count = 0
recall_50_count = 0
for (search_vec, test_vec) in zip(I, test_data):
    if test_vec[0] in search_vec:
        recall_1_count += 1
    recall_50_count += len(set(search_vec.tolist()) & set(test_vec))
print "recall1@50 = " + str(recall_1_count / (50.0))
print "recall50@50 = " + str(recall_50_count / (50.0 * 50.0))

index.nprobe = 50
start_time = time.time()
D, I = index.search(data[:50], k)  # 搜索
print "nprobe=50 search Used %.2f ms" % ((time.time() - start_time) * 1000)
recall_1_count = 0
recall_50_count = 0
for (search_vec, test_vec) in zip(I, test_data):
    if test_vec[0] in search_vec:
        recall_1_count += 1
    recall_50_count += len(set(search_vec.tolist()) & set(test_vec))
print "recall1@50 = " + str(recall_1_count / (50.0))
print "recall50@50 = " + str(recall_50_count / (50.0 * 50.0))