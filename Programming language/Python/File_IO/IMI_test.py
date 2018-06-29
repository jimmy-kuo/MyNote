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
d = 300                 # 向量维数
data_size = 10000    # 数据库大小
k = 50

# 构建索引
index = faiss.index_factory(d, "OPQ8_64,IMI2x8,PQ8")

# 生成测试数据
numpy.random.seed(13)

for i in xrange(25):
    data = numpy.random.random(size=(data_size, d)).astype('float32')
    print 'Test data gen compelete!'
    # 　训练数据
    start_time = time.time()
    index.train(data)
    print "Train Index Used %.2f sec." % (time.time() - start_time)

    # 添加数据
    start_time = time.time()
    index.add(data)
    print "Add vector Used %.2f sec." % (time.time() - start_time)
    print index.ntotal



# 搜索
for i in xrange(25):
    data = numpy.random.random(size=(data_size, d)).astype('float32')
    start_time = time.time()
    D, I = index.search(data, k)  # 搜索
    print I[:-12]
    print "Search Used %.2f sec - all vector" % ((time.time() - start_time))