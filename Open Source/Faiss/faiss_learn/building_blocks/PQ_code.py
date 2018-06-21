# encoding:utf-8

"""
faiss库 向量相似性搜索框架学习
PQ 编码,解码

author  :   h-j-13
time    :   2018-6-20
ref     :   https://github.com/facebookresearch/faiss/wiki/Faiss-building-blocks:-clustering,-PCA,-quantization
"""

import numpy
import faiss

numpy.random.seed(13)


# =============测试数据=============
d = 32  # data dimension
cs = 4  # code size (bytes)

# train set
nt = 10000
xt = numpy.random.rand(nt, d).astype('float32')

# dataset to encode (could be same as train)
n = 20000
x = numpy.random.rand(n, d).astype('float32')

pq = faiss.ProductQuantizer(d, cs, 8)
pq.train(xt)

# encode                        # PQ 编码
codes = pq.compute_codes(x)

# decode                        # PQ 解码
x2 = pq.decode(codes)

# =============展示结果=============
# compute reconstruction error 计算复现误差
avg_relative_error = ((x - x2)**2).sum() / (x ** 2)
print avg_relative_error