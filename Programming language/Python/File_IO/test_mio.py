# encoding:utf-8

"""
faiss库 - 海量高维域名相似度计算(多进程异步IO测试版)
author  :   h-j-13
time    :   2018-6-25
"""

import time
from multiprocessing import Process, Value, Queue

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

# 进程之间默认是不能共享全局变量的
READ_FILE_LOCK = Value("i", 0)
WRITE_FILE_LOCK = Value("i", 0)
FILE_IDS_VECTOR_QUEUE = Queue()
START_RAED = Value("i", 0)
END_READ = Value("i", 0)
START_READ_FOR_SEARCH = Value("i", 0)
READ_FILE_NUM = 1


def ReadFileProcess(start_file_num=TRAIN_FILE_SIZE,
                    file_path=INPUT_FILE_PATH,
                    file_name_list=FILE_NAME_LIST,
                    read_file_num=1):
    """
    读取文件轮询进程,数据通过全局变量/队列进行交互
    :param start_file_num:  开始读取的文件序号(前几个文件经过训练已经加载到索引中)
    :param file_path:       文件路径
    :param file_name_list:  文件名列表
    :param read_file_num:   一次性读取文件数量
    :return:
    """
    global START_RAED, END_READ, READ_FILE_LOCK, FILE_IDS_VECTOR_QUEUE

    while not START_RAED.value:  # 等待主进程信号
        time.sleep(10)
        print File_IO.getLocalTimeStr()

    for i in xrange(start_file_num, len(file_name_list), read_file_num):
        print i
        while not READ_FILE_LOCK.value:  # 等待主进程信号
            time.sleep(10)
            print 'wait READ_FILE_LOCK'
        need2read = file_name_list[i:i + read_file_num]

        if need2read:  # 本次需要读取的文件列表
            for file_name in need2read:
                ids, data = File_IO.readfile2ids_vec(file_path + file_name)
                FILE_IDS_VECTOR_QUEUE.put((ids, data))
                print File_IO.getLocalTimeStr(),
                print file_name + "向量数据添加至队列"
        else:
            END_READ.value = 1

        READ_FILE_LOCK.value = 0  # 向主进程回送读取完毕的信号
    END_READ.value = 1


def IndexInit(index_str="OPQ8_64,IVF100,PQ8", d=D):
    """初始化,生成并训练索引"""
    global INPUT_FILE_PATH, FILE_NAME_LIST, TRAIN_FILE_SIZE
    global START_RAED, READ_FILE_LOCK

    # 初始化I/O进程
    rfp = Process(target=ReadFileProcess, name='ReadFiledata')
    rfp.start()
    # 初始化索引
    index = faiss.index_factory(d, index_str)
    print File_IO.getLocalTimeStr(),
    print 'START - Index=' + index_str + ' k=' + str(K)

    # 获取训练数据
    for fn in xrange(TRAIN_FILE_SIZE):
        if fn == 0:  # 第一次读取,初始化矩阵
            ids, train_data = File_IO.readfile2ids_vec(INPUT_FILE_PATH + FILE_NAME_LIST[fn])
        else:
            temp_ids, temp_data = File_IO.readfile2ids_vec(INPUT_FILE_PATH + FILE_NAME_LIST[fn])
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

    # 同时通知I/O进程开始读写数据
    START_RAED.value = 1
    READ_FILE_LOCK.value = 1

    # 载入训练数据
    index.add_with_ids(train_data, ids)
    del train_data
    del ids
    print File_IO.getLocalTimeStr(),
    print '训练数据添加至索引.'
    return index


def add_vectors(index):
    """向索引中添加向量"""
    global END_READ, READ_FILE_LOCK, FILE_IDS_VECTOR_QUEUE

    # 当读写进程都写完成并把数据从队列里全部取出时,添加向量过程结束
    while not (END_READ.value and FILE_IDS_VECTOR_QUEUE.empty()):
        while READ_FILE_LOCK.value:
            time.sleep(10)  # 等待I/O进程读取完毕的信号

        ids_list = []
        vec_list = []
        # 一次性将队列里的所有数据取出
        while not FILE_IDS_VECTOR_QUEUE.empty():
            ids_t, vec_t = FILE_IDS_VECTOR_QUEUE.get()
            ids_list.append(ids_t)
            vec_list.append(vec_t)

        READ_FILE_LOCK.value = 1  # 通知读写进程开始下一轮读取

        for vec, ids in zip(ids_list, vec_list):  # 将数据从队列里取出并添加至索引
            index.add_with_ids(vec, ids)
            print File_IO.getLocalTimeStr() + "向量数据添加..."


def search_kNN(index):
    """搜索临近向量"""
    print index.index.ntotal
    raw_input()
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
