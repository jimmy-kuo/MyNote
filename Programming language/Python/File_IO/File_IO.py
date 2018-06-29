# encoding:utf-8

"""
Python 文件读写测试 - 基础IO接口 + numpy

每行 1 个 int id , 300 个 float
author  : h-j-13
time    : 2018-06-26
"""

# note : 未优化时候 7 - min

import os
import time
import numpy
import datetime


def getLocalTimeStr():
    """获取本地时间字符串 'YY-MM-DD HH:mm:ss' """
    return str(datetime.datetime.now()).split('.')[0]


def getAllFileName(path, file_type='.txt'):
    """返回某路径下所有文件名称组成的列表(不做递归获取)"""
    file_name_list = []
    for file_name in os.listdir(path):
        if file_name.find(file_type) != -1 or file_type == '':
            file_name_list.append(file_name)
    return file_name_list


def readfile2ids_vec(file_path):
    """读取目标路径下的文档,并转换为矩阵及每行id"""
    ids = []
    vec = []
    # 使用 for line in f(文件描述符) 遍历文件,内部自身缓冲I/O
    # ref : https://stackoverflow.com/questions/8009882/how-to-a-read-large-file-line-by-line-in-python/8010133#8010133
    with open(file_path, "rb") as f:
        for line in f:
            try:
                v_id, v = line.split(" ", 1)
                ids.append(int(v_id))
                vec.append(map(float, v.strip().split(" ")))
            except Exception as e:
                print str(e)
    # list 2 matrix
    ids = numpy.array(ids).astype('int')
    vec = numpy.array(vec).astype('float32')
    return ids, vec


def readfile2vec(file_path):
    """读取目标路径下的文档,并转换为矩阵"""
    vec = []
    with open(file_path, "rb") as f:
        for line in f:
            try:
                _, v = line.split(" ", 1)
                vec.append(map(float, v.strip().split(" ")))
            except Exception as e:
                print str(e)
    # list 2 matrix
    vec = numpy.array(vec).astype('float32')
    return vec


def writeSearchResult(file_path, ids, I, D):
    """写入搜索结果至指定文件夹下"""
    write_buff = []
    with open(file_path, 'wb') as f:
        for vectors_id, vectors, distances in zip(ids, I, D):
            write_buff.extend(
                [str(vectors_id) + " " + str(v) + " " + str(d) + "\n" for v, d in zip(vectors, distances)])
        f.writelines(write_buff)


if __name__ == '__main__':
    open("./result/1.txt", 'w')
    # print getAllFileName('./data/')
    #
    # import time
    #
    # s = time.time()
    # readfile2ids_vec("./data/a.txt")
    # print "Used %.2f sec." % (time.time() - s)
