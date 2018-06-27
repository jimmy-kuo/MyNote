# encoding:utf-8

"""
Python 文件读写测试 - 基础IO接口

测试数据规模 2M5行, 每行300个float
author  : h-j-13
time    : 2018-06-26
"""

import time
import random
import numpy

# 生成测试数据
file_name_list = [
    "a.txt",
    "b.txt",
    "c.txt",
    "d.txt",
    "e.txt",
    "f.txt",
    "g.txt",
    "h.txt",
    "i.txt",
    "j.txt"
]

fcnt = 0
size = 10000
d = 300


def test_data():
    global fcnt, size, d
    for file_name in file_name_list:
        with open(file_name, "w") as f:
            ids = range(fcnt * size, (fcnt + 1) * size)
            vectors = numpy.random.random(size=(size, d))
            fcnt += 1
            for i, v in zip(ids, vectors):
                f.write(str(i) + " ")
                f.write(" ".join([str(vec) for vec in v]))
                f.write("\n")


if __name__ == '__main__':
    test_data()

    # import time
    #
    # s = time.time()                             # 二进制打开大约块 30.7%
    # with open("test_io.txt", "r") as f:         # rb     -    0.871999979019
    #     for i in f:                             # r      -    1.25699996948
    #         pass
    # print time.time() - s
