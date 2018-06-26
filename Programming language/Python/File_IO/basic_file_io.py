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
size = 50000
d = 300

for file_name in file_name_list:
    with open(file_name, "w") as f:
        ids = range(fcnt * size, (fcnt + 1) * size)
        vectors = numpy.random.random(size=(size, d))
        fcnt += 1
        for i, v in zip(ids, vectors):
            f.write(str(i)+" ")
            f.write(" ".join([str(vec) for vec in v]))
            f.write("\n")


exit(-1)
# start_time = time.time()
# numpy.random.seed(13)
# data = numpy.random.random(size=(250000, 50))
# write_buff = []
# for i in data:
#     i.tolist()
# f = open("a.txt","w")
# f.writelines()
# exit(-2)


# 转换数据格式
start_time = time.time()
write_buff = []
for vectors_id, vectors in zip(ids, data):
    write_buff.extend([str(vectors_id) + " " + str(v) + "\n" for v in vectors])

print "%.2f" % (time.time() - start_time)

start_time = time.time()

f = open("test_io.txt", "w")
f.writelines(write_buff)
# f.writelines(data)
# f.write(" ".join(map(str, vector.tolist())))
f.close()

print "%.2f" % (time.time() - start_time)
