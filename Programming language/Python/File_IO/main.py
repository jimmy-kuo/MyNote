# encoding:utf-8

"""
faiss库 - 海量高维域名相似度计算
author  :   h-j-13
time    :   2018-6-25
"""

import time
from multiprocessing import Process

import numpy
import faiss

import File_IO

D = 300
K = 50

INPUT_FILE_PATH = './data/'
OUTPUT_FILE_PATH = './result/'
OUTPUT_FILE_BASIC_NAME = 'faiss_kNN_'
FILE_NAME_LIST = File_IO.getAllFileName(INPUT_FILE_PATH)
INDEX_STR = "OPQ8_64,IVF2000,PQ8"
TRAIN_FILE_SIZE = 3

# todo - 多进程实现异步读取
READ_FILE_LOCK = True
WRITE_FILE_LOCK = True
ADD_VECTOR = None
ADD_VECTOR_IDS = None


def IndexInit(index_str="OPQ8_64,IVF100,PQ8", d=D):
    """生成并训练索引"""
    # 初始化索引
    global INPUT_FILE_PATH, FILE_NAME_LIST, TRAIN_FILE_SIZE
    index = faiss.index_factory(d, index_str)
    print File_IO.getLocalTimeStr(),
    print 'START - Index=' + index_str + ' k=' + str(K)

    # 获取训练数据
    for i in xrange(TRAIN_FILE_SIZE):
        if i == 0:  # 第一次读取,初始化矩阵
            ids, train_data = File_IO.readfile2ids_vec(INPUT_FILE_PATH + FILE_NAME_LIST[i])
        else:
            temp_ids, temp_data = File_IO.readfile2ids_vec(INPUT_FILE_PATH + FILE_NAME_LIST[i])
            ids = numpy.hstack((ids, temp_ids))
            del temp_ids  # 及时删除引用,自动进行GC
            train_data = numpy.vstack((train_data, temp_data))
            del temp_data

    print File_IO.getLocalTimeStr(),
    print '完成训练数据载入.'

    # 训练模型
    index.train(train_data)
    print File_IO.getLocalTimeStr(),
    print '完成训练.'

    # 载入训练数据
    index.add_with_ids(train_data, ids)
    del train_data
    del ids
    print File_IO.getLocalTimeStr(),
    print '训练数据添加至索引.'
    return index


def add_vectors(index):
    """向索引中添加向量"""
    global INPUT_FILE_PATH, FILE_NAME_LIST, TRAIN_FILE_SIZE
    for i in xrange(TRAIN_FILE_SIZE, len(FILE_NAME_LIST)):
        ids, train_data = File_IO.readfile2ids_vec(INPUT_FILE_PATH + FILE_NAME_LIST[i])
        index.add_with_ids(train_data, ids)
        print File_IO.getLocalTimeStr(),
        print FILE_NAME_LIST[i] + "向量数据添加完成"


def search_kNN(index):
    """搜索临近向量"""
    global INPUT_FILE_PATH, FILE_NAME_LIST, TRAIN_FILE_SIZE, OUTPUT_FILE_PATH, OUTPUT_FILE_BASIC_NAME
    global K
    for i in xrange(len(FILE_NAME_LIST)):
        ids, train_data = File_IO.readfile2ids_vec(INPUT_FILE_PATH + FILE_NAME_LIST[i])
        _, I = index.search(train_data, K)
        print File_IO.getLocalTimeStr(),
        print FILE_NAME_LIST[i] + "搜索完成"
        del train_data
        file_path = OUTPUT_FILE_PATH + OUTPUT_FILE_BASIC_NAME + str(i)
        File_IO.writeSearchResult(OUTPUT_FILE_PATH + OUTPUT_FILE_BASIC_NAME + str(i), ids, I)
        del ids
        del I
        print File_IO.getLocalTimeStr(),
        print FILE_NAME_LIST[i] + "中对应向量搜索结果写入" + file_path


def main():
    """主流程"""
    global INDEX_STR
    index = IndexInit(index_str=INDEX_STR)
    add_vectors(index)
    search_kNN(index)
    raw_input()


if __name__ == '__main__':
    main()
