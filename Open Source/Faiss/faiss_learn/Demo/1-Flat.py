# encoding:utf-8

# Copyright (c) 2015-present, Facebook, Inc.
# All rights reserved.
#
# This source code is licensed under the BSD+Patents license found in the
# LICENSE file in the root directory of this source tree.

# author    : Facebook
# translate : h-j-13

import numpy as np
d = 30                      # 向量维度
data_size = 10000                   # 测试数据大小
xb = np.random.random((data_size, d)).astype('float32')

import faiss
index = faiss.IndexFlatL2(d)        # 构建FlatL2索引
# index.train(xb)                   # FlatL2执行暴力搜索,无需训练
index.add(xb)                       # 向索引中添加向量

k = 4                               # k=4的 k临近搜索
D, I = index.search(xb[:5], k)      # 进行搜索
# 向量距离矩阵保存在变量D中,临近向量id保存在I中
