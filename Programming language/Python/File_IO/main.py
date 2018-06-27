# encoding:utf-8

"""
faiss库 - 海量高维域名相似度计算
author  :   h-j-13
time    :   2018-6-25
"""

import time
from multiprocessing import Process, Value, Queue

import numpy
import faiss

import File_IO

# faiss相关设置
D = 300
K = 50
INDEX_STR = "OPQ8_64,IVF100,PQ8"
TRAIN_FILE_SIZE = 3

# 文件I/O设置
INPUT_FILE_PATH = './data/'
OUTPUT_FILE_PATH = './result/'
OUTPUT_FILE_BASIC_NAME = 'faiss_kNN_'
FILE_NAME_LIST = File_IO.getAllFileName(INPUT_FILE_PATH)
READ_FILE_NUM = 2  # 每次读取的文件数目

# 进程通信变量
# 进程之间默认是不能共享全局变量的,需要通过 multiprocessing.value对象
FILE_IDS_VECTOR_QUEUE = Queue()
FILE_IDS_VECTOR_QUEUE_FOR_SEARCH = Queue()
READ_FILE_LOCK = Value("i", 0)
READ_FILE_LOCK_FOR_SEARCH = Value("i", 0)
START_RAED = Value("i", 0)
START_READ_FOR_SEARCH = Value("i", 0)
END_READ = Value("i", 0)
END_READ_FOR_SEARCH = Value("i", 0)


def read_file_process(start_file_num=TRAIN_FILE_SIZE,
                      file_path=INPUT_FILE_PATH,
                      file_name_list=FILE_NAME_LIST,
                      read_file_num=READ_FILE_NUM):
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
        time.sleep(1)

    for i in xrange(start_file_num, len(file_name_list), read_file_num):

        while not READ_FILE_LOCK.value:  # 等待主进程信号
            time.sleep(1)

        need2read = file_name_list[i:i + read_file_num]
        if need2read:  # 本次需要读取的文件列表
            for file_name in need2read:
                ids, data = File_IO.readfile2ids_vec(file_path + file_name)
                FILE_IDS_VECTOR_QUEUE.put((ids, data))
                print File_IO.getLocalTimeStr(),
                print file_name + " 向量数据添加至队列"

        else:
            END_READ.value = 1

        READ_FILE_LOCK.value = 0  # 向主进程回送读取完毕的信号

    READ_FILE_LOCK.value = 0
    END_READ.value = 1

    return


def read_file_for_search_process(file_path=INPUT_FILE_PATH,
                                 file_name_list=FILE_NAME_LIST,
                                 read_file_num=READ_FILE_NUM):
    """读取文件轮询进程,数据通过全局变量/队列进行交互(执行搜索时用)"""

    global START_READ_FOR_SEARCH, END_READ_FOR_SEARCH, \
        READ_FILE_LOCK_FOR_SEARCH, FILE_IDS_VECTOR_QUEUE_FOR_SEARCH

    while not START_READ_FOR_SEARCH.value:  # 等待主进程信号
        time.sleep(1)

    for i in xrange(0, len(file_name_list), read_file_num):

        while not READ_FILE_LOCK_FOR_SEARCH.value:  # 等待主进程信号
            time.sleep(1)

        need2read = file_name_list[i:i + read_file_num]
        if need2read:  # 本次需要读取的文件列表
            for file_name in need2read:
                ids, data = File_IO.readfile2ids_vec(file_path + file_name)
                FILE_IDS_VECTOR_QUEUE_FOR_SEARCH.put((ids, data))
                print File_IO.getLocalTimeStr(),
                print file_name + " 向量数据添加至待搜索队列"

        else:
            END_READ_FOR_SEARCH.value = 1

        READ_FILE_LOCK_FOR_SEARCH.value = 0  # 向主进程回送读取完毕的信号

    READ_FILE_LOCK_FOR_SEARCH.value = 0
    END_READ_FOR_SEARCH.value = 1

    return


def IndexInit(index_str="OPQ8_64,IVF100,PQ8", d=D):
    """初始化,生成并训练索引"""
    global INPUT_FILE_PATH, FILE_NAME_LIST, TRAIN_FILE_SIZE
    global START_RAED, READ_FILE_LOCK

    # 初始化I/O进程
    rfp = Process(target=read_file_process, name='ReadFiledata')
    rfp.start()
    rfpfs = Process(target=read_file_for_search_process, name='ReadFiledataForSearch')
    rfpfs.start()
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
    print "训练数据添加至索引, 训练用数据量:" + str(index.ntotal)
    return index


def add_vectors(index):
    """向索引中添加向量"""
    global END_READ, READ_FILE_LOCK, FILE_IDS_VECTOR_QUEUE

    # 当读写进程都写完成并把数据从队列里全部取出时,添加向量过程结束
    while not END_READ.value:
        while READ_FILE_LOCK.value:
            time.sleep(1)  # 等待I/O进程读取完毕的信号

        ids_list = []
        vec_list = []

        while not FILE_IDS_VECTOR_QUEUE.empty():
            (ids_t, vec_t) = FILE_IDS_VECTOR_QUEUE.get()
            if len(ids_t):  # 处理异常
                ids_list.append(ids_t)
                vec_list.append(vec_t)

        READ_FILE_LOCK.value = 1  # 通知读写进程开始下一轮读取

        for ids, vec in zip(ids_list, vec_list):  # 将数据从队列里取出并添加至索引
            index.add_with_ids(vec, ids)
            print File_IO.getLocalTimeStr() + " 向量数据添加..."

    # 若队列里还有数据,则将其取完
    while not FILE_IDS_VECTOR_QUEUE.empty():
        (ids, vec) = FILE_IDS_VECTOR_QUEUE.get()

        if len(vec):
            index.add_with_ids(vec, ids)

    # 同时通知I/O进程开始准备搜索用数据
    global START_READ_FOR_SEARCH, READ_FILE_LOCK_FOR_SEARCH
    START_READ_FOR_SEARCH.value = 1
    READ_FILE_LOCK_FOR_SEARCH.value = 1


def search_kNN(index):
    """搜索临近向量"""
    global OUTPUT_FILE_PATH, OUTPUT_FILE_BASIC_NAME
    global FILE_IDS_VECTOR_QUEUE_FOR_SEARCH, READ_FILE_LOCK_FOR_SEARCH, END_READ_FOR_SEARCH
    global K

    print File_IO.getLocalTimeStr() + " 开始执行搜索,目前索引中向量数量:" + str(index.ntotal)

    fcnt = 0
    # 当读写进程都写完成并把数据从队列里全部取出时,添加向量过程结束
    while not END_READ_FOR_SEARCH.value:
        while READ_FILE_LOCK_FOR_SEARCH.value:
            time.sleep(1)  # 等待I/O进程读取完毕的信号

        ids_list = []
        vec_list = []

        # 读取出本轮需要搜索的向量
        while not FILE_IDS_VECTOR_QUEUE_FOR_SEARCH.empty():
            (ids_t, vec_t) = FILE_IDS_VECTOR_QUEUE_FOR_SEARCH.get()
            if len(ids_t):  # 处理异常
                ids_list.append(ids_t)
                vec_list.append(vec_t)

        READ_FILE_LOCK_FOR_SEARCH.value = 1  # 通知读写进程开始下一轮读取

        for ids_t, vec_t in zip(ids_list, vec_list):  # 将数据从队列里取出并添加至索引
            # 搜索
            _, I = index.search(vec_t, K)
            # 将结果写入文件
            file_path = OUTPUT_FILE_PATH + OUTPUT_FILE_BASIC_NAME + str(fcnt)
            fcnt += 1
            File_IO.writeSearchResult(file_path, ids_t, I)
            print File_IO.getLocalTimeStr() + " 完成了一轮向量搜索.结果写入 " + str(file_path)

    # 若队列里还有数据,则将其取完
    while not FILE_IDS_VECTOR_QUEUE_FOR_SEARCH.empty():
        (ids_t, vec_t) = FILE_IDS_VECTOR_QUEUE_FOR_SEARCH.get()
        if len(ids_t):  # 处理异常
            _, I = index.search(vec_t, K)
            file_path = OUTPUT_FILE_PATH + OUTPUT_FILE_BASIC_NAME + str(fcnt)
            fcnt += 1
            File_IO.writeSearchResult(file_path, ids_t, I)
            print File_IO.getLocalTimeStr() + " 完成了一次向量搜索.结果写入 " + str(file_path)


def main():
    """主流程"""
    global INDEX_STR
    index = IndexInit(index_str=INDEX_STR)
    add_vectors(index)
    search_kNN(index)
    raw_input()


if __name__ == '__main__':
    main()
