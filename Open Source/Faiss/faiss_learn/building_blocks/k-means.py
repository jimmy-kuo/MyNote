# encoding:utf-8

"""
faiss库 向量相似性搜索框架学习
k-means 聚类学习

author  :   h-j-13
time    :   2018-6-20
ref     :   https://github.com/facebookresearch/faiss/wiki/Faiss-building-blocks:-clustering,-PCA,-quantization
"""

import numpy
import faiss

numpy.random.seed(13)

# =============测试数据=============
x = numpy.random.random(size=(40000, 2)).astype('float32')
d = x.shape[1]

# =============k-means参数设置=============
ncentroids = 1024                                       # 聚类中心个数
niter = 20                                             # 迭代次数
verbose = True                                          # 冗长模式
d = x.shape[1]                                          # 维度
kmeans = faiss.Kmeans(d, ncentroids, niter, verbose)    # 设置 k-means参数
kmeans.train(x)                                         # 训练

# =============展示结果=============
print kmeans.centroids  # 质心
print kmeans.obj  # 在k-均值情况下的总平方误差

# =============Python Console=============
# 5个向量 1个质心
# WARNING clustering 5 points to 1 centroids: please provide at least 39 training points
# Clustering 5 points in 2D to 1 clusters, redo 1 times, 1 iterations
#   Preprocessing in 0.00 s
#   Iteration 0 (0.00 s, search 0.00 s): objective=18 imbalance=1.000 nsplit=0
# [[0. 0.]]
# [18.]
#
# 40k个向量 1024个质心
# Clustering 40000 points in 2D to 1024 clusters, redo 1 times, 20 iterations
#   Preprocessing in 0.00 s
#   Iteration 19 (1.82 s, search 1.81 s): objective=6.16961 imbalance=1.067 nsplit=0
# [[0.9323239  0.13240094]
#  [0.692283   0.8357934 ]
#  [0.42551664 0.24901141]
#  ...
#  [0.21829888 0.62564224]
#  [0.4876577  0.40471378]
#  [0.8280808  0.13379179]]
# [12.175712   8.012669   7.212405   6.873381   6.680459   6.554406
#   6.460877   6.393987   6.345799   6.307647   6.2765527  6.252333
#   6.233297   6.216073   6.20381    6.1939087  6.185918   6.1794233
#   6.1743884  6.16961  ]
#
