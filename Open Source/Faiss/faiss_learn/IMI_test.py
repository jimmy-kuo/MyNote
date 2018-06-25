# encoding:utf-8

"""
faiss库 - 海量高维域名相似度计算
author  :   h-j-13
time    :   2018-6-25
"""

import time
import numpy
import faiss

# 基本参数
d = 300  # 向量维数
data_size = 100000  # 数据库大小
k = 50

# 构建索引
index = faiss.index_factory(d, "OPQ8_64,IVF2000,PQ8")

# 生成测试数据
numpy.random.seed(13)

data = numpy.random.random(size=(data_size, d)).astype('float32')

# 　训练数据
start_time = time.time()
index.train(data)
print "Train Index Used %.2f sec." % (time.time() - start_time)

for i in xrange(250):
    # 添加数据
    data = numpy.random.random(size=(data_size, d)).astype('float32')
    start_time = time.time()
    index.add(data)
    print "Add vector Used %.2f sec." % (time.time() - start_time)
    print index.ntotal

for i in xrange(250):
    # 搜索
    if i < 10:
        index.nprobe = 1
        print 1,
    elif 10 <= i < 30:
        index.nprobe = 5
        print 5,
    else:
        index.nprobe = 20
        print 20,
    data = numpy.random.random(size=(data_size, d)).astype('float32')
    start_time = time.time()
    D, I = index.search(data, k)  # 搜索
    print "Search Used %.2f sec - all vector" % ((time.time() - start_time))
    print I[0]
