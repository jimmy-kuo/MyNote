# encoding:utf-8

"""
faiss库 向量相似性搜索框架学习
PCA 降维算法学习

author  :   h-j-13
time    :   2018-6-20
ref     :   https://github.com/facebookresearch/faiss/wiki/Faiss-building-blocks:-clustering,-PCA,-quantization
"""

import numpy
import faiss

numpy.random.seed(13)


# 通过PCA将40维的向量缩减为10维
# =============测试数据=============
mt = numpy.random.rand(1000, 40).astype('float32')
print mt[0]
mat = faiss.PCAMatrix(40, 10)                       # 40维缩减为10维
mat.train(mt)                                       # 训练模型
assert mat.is_trained
tr = mat.apply_py(mt)
# print this to show that the magnitude of tr's columns is decreasing
print tr[0]
# print (tr ** 2).sum(0)

# =============Python Console=============
# [7.7770239e-01 2.3754121e-01 8.2427853e-01 9.6574920e-01 9.7260112e-01
#  4.5344925e-01 6.0904247e-01 7.7552652e-01 6.4161336e-01 7.2201824e-01
#  3.5036523e-02 2.9844946e-01 5.8512490e-02 8.5706097e-01 3.7285402e-01
#  6.7984796e-01 2.5627995e-01 3.4758121e-01 9.4127702e-03 3.5833380e-01
#  9.4909418e-01 2.1789901e-01 3.1939137e-01 9.1777241e-01 3.1903666e-02
#  6.5084539e-02 6.2982899e-01 8.7381345e-01 8.7157320e-03 7.4657726e-01
#  8.1284118e-01 7.5717449e-02 6.5645534e-01 5.0926220e-01 4.7988340e-01
#  9.5557415e-01 1.2033570e-05 2.4697870e-01 7.1223265e-01 3.2458204e-01]
# [ 0.7001362   0.09906334  0.44689706  0.0343994  -0.58154356  0.08155185
#  -0.35151514  0.3204378   0.2542621  -0.09245522]