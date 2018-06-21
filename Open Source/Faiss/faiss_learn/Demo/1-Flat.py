# encoding:utf-8

# Copyright (c) 2015-present, Facebook, Inc.
# All rights reserved.
#
# This source code is licensed under the BSD+Patents license found in the
# LICENSE file in the root directory of this source tree.

# author    : Facebook
# translate : h-j-13

import numpy as np

d = 3                               # 向量维度
nb = 100000                         # 向量集大小
nq = 10000                          # 查询次数
np.random.seed(1234)                # 随机种子,使结果可复现
xb = np.random.random((nb, d)).astype('float32')
xb[:, 0] += np.arange(nb) / 1000.   # 每一项增加了一个等差数列的对应项数
xq = np.random.random((nq, d)).astype('float32')
xq[:, 0] += np.arange(nq) / 1000.

import faiss
index = faiss.IndexFlatL2(d)        # 构建FlatL2索引
print(index.is_trained)
index.add(xb)                       # 向索引中添加向量
print(index.ntotal)

k = 4                               # k=4的 k临近搜索
D, I = index.search(xb[:5], k)      # 测试
print(I)
print(D)
D, I = index.search(xq, k)          # 执行搜索
print(I[:5])                        # 最初五次查询的结果
print(I[-5:])                       # 最后五次查询的结果
