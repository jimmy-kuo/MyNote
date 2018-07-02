# encoding:utf-8

"""
基于faiss的海量高维域名相似度计算
多进程队列通信的异步获取
author  :   h-j-13
time    :   2018-6-28
"""

import time
from multiprocessing import Process, Value, Queue

import numpy
import faiss

import File_IO_new as File_IO

# faiss相关设置
D = 300
K = 50
INDEX_STR = "OPQ20_80,IVF100,PQ20"
TRAIN_FILE_SIZE = 2

# 文件I/O设置
INPUT_FILE_PATH = './data/'
OUTPUT_FILE_PATH = './data/result_t/'
OUTPUT_FILE_BASIC_NAME = 'faiss_kNN_'
FILE_NAME_LIST = File_IO.getAllFileName(INPUT_FILE_PATH)
READ_FILE_NUM = 3  # 异步读取文件数目

# 进程通信变量
# 进程之间默认是不能共享全局变量的,需要通过 multiprocessing.value对象
FILE_IDS_VECTOR_QUEUE = Queue()
FILE_IDS_VECTOR_QUEUE_FOR_SEARCH = Queue()
FILE_WRITE_QUEUE = Queue()

START_RAED = Value("i", 0)
START_READ_FOR_SEARCH = Value("i", 0)
END_READ = Value("i", 0)
END_READ_FOR_SEARCH = Value("i", 0)
END_WRITE_FILE = Value("i", 0)
WRITE_FILE_PROCESS = None


def read_file_process(start_file_num=TRAIN_FILE_SIZE,
                      file_path=INPUT_FILE_PATH,
                      file_name_list=FILE_NAME_LIST, ):
    """
    读取文件轮询进程,数据通过全局变量/队列进行交互
    :param start_file_num:  开始读取的文件序号(前几个文件经过训练已经加载到索引中)
    :param file_path:       文件路径
    :param file_name_list:  文件名列表
    :param read_file_num:   一次性读取文件数量
    """
    global START_RAED, END_READ, FILE_IDS_VECTOR_QUEUE, READ_FILE_NUM

    while not START_RAED.value:  # 等待主进程信号
        time.sleep(1)

    for i in xrange(start_file_num, len(file_name_list)):

        while FILE_IDS_VECTOR_QUEUE.qsize() > READ_FILE_NUM:  # 控制队列大小
            time.sleep(1)

        file_name = file_name_list[i]
        ids, data = File_IO.readfile2ids_vec(file_path + file_name)
        FILE_IDS_VECTOR_QUEUE.put((ids, data))
        print File_IO.getLocalTimeStr(),
        print file_name + " 向量数据添加至队列"

    END_READ.value = 1  # 告知主进程处理结束
    return


def read_file_for_search_process(file_path=INPUT_FILE_PATH,
                                 file_name_list=FILE_NAME_LIST, ):
    """读取文件轮询进程,数据通过全局变量/队列进行交互(执行搜索时用)"""

    global START_READ_FOR_SEARCH, END_READ_FOR_SEARCH, FILE_IDS_VECTOR_QUEUE_FOR_SEARCH, READ_FILE_NUM

    while not START_READ_FOR_SEARCH.value:  # 等待主进程信号
        time.sleep(1)

    for file_name in file_name_list:
        # 控制队列大小
        while FILE_IDS_VECTOR_QUEUE_FOR_SEARCH.qsize() > READ_FILE_NUM:
            time.sleep(1)

        ids, data = File_IO.readfile2ids_vec(file_path + file_name)
        FILE_IDS_VECTOR_QUEUE_FOR_SEARCH.put((ids, data))
        print File_IO.getLocalTimeStr(),
        print file_name + " 向量数据添加至待搜索队列"

    # 向主进程回送读取完毕的信号
    END_READ_FOR_SEARCH.value = 1
    return


def write_file_process():
    """写入结果文件进程"""
    global FILE_WRITE_QUEUE, END_WRITE_FILE

    while not END_WRITE_FILE.value:
        if not FILE_WRITE_QUEUE.empty():
            (file_path, ids, I, D) = FILE_WRITE_QUEUE.get()
            File_IO.writeSearchResult(file_path, ids, I, D)
            print File_IO.getLocalTimeStr() + " wp完成了一轮向量搜索.结果写入 " + str(file_path)
        else:
            time.sleep(1)

    print File_IO.getLocalTimeStr() + " 结果队列中尚未处理数量:" + str(FILE_WRITE_QUEUE.qsize())

    # 最后将队列内的文件处理完
    while not FILE_WRITE_QUEUE.empty():
        (file_path, ids, I, D) = FILE_WRITE_QUEUE.get()
        File_IO.writeSearchResult(file_path, ids, I, D)
        print File_IO.getLocalTimeStr() + " wp完成了一次向量搜索.结果写入 " + str(file_path)

    return


def IndexInit(index_str="OPQ8_64,IVF100,PQ8", d=D):
    """初始化,生成并训练索引"""
    global INPUT_FILE_PATH, FILE_NAME_LIST, TRAIN_FILE_SIZE
    global START_RAED, WRITE_FILE_PROCESS

    # 初始化I/O进程
    rfp = Process(target=read_file_process, name='ReadFiledata')
    rfp.start()
    rfpfs = Process(target=read_file_for_search_process, name='ReadFiledataForSearch')
    rfpfs.start()
    WRITE_FILE_PROCESS = Process(target=write_file_process, name='WriteFile')
    WRITE_FILE_PROCESS.start()
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

    # 载入训练数据
    index.add_with_ids(train_data, ids)
    del train_data
    del ids
    print File_IO.getLocalTimeStr(),
    print "训练数据添加至索引, 训练用数据量:" + str(index.ntotal)
    return index


def add_vectors(index):
    """向索引中添加向量"""
    global END_READ, START_READ_FOR_SEARCH, FILE_IDS_VECTOR_QUEUE

    # 当读写进程都写完成并把数据从队列里全部取出时,添加向量过程结束
    while not END_READ.value:
        if not FILE_IDS_VECTOR_QUEUE.empty():
            (ids, vec) = FILE_IDS_VECTOR_QUEUE.get()
            if len(ids):
                index.add_with_ids(vec, ids)
                print File_IO.getLocalTimeStr() + " 向量数据添加..."
        else:
            time.sleep(1)

    # 同时通知I/O进程开始准备搜索用数据
    START_READ_FOR_SEARCH.value = 1

    # 若队列里还有数据,则将其取完
    print File_IO.getLocalTimeStr() + " 添加队列中尚未处理数量:" + str(FILE_IDS_VECTOR_QUEUE.qsize())
    while not FILE_IDS_VECTOR_QUEUE.empty():
        (ids, vec) = FILE_IDS_VECTOR_QUEUE.get()
        if len(vec):
            index.add_with_ids(vec, ids)
            print File_IO.getLocalTimeStr() + " 向量数据添加."


def search_kNN(index):
    """搜索临近向量"""
    global OUTPUT_FILE_PATH, OUTPUT_FILE_BASIC_NAME, END_WRITE_FILE, FILE_WRITE_QUEUE, WRITE_FILE_PROCESS
    global FILE_IDS_VECTOR_QUEUE_FOR_SEARCH, END_READ_FOR_SEARCH
    global K

    print File_IO.getLocalTimeStr() + " 开始执行搜索,目前索引中向量数量:" + str(index.ntotal)

    fcnt = 0
    while (not END_READ_FOR_SEARCH.value) or (not FILE_IDS_VECTOR_QUEUE_FOR_SEARCH.empty()):
        if not FILE_IDS_VECTOR_QUEUE_FOR_SEARCH.empty():
            (ids, vec) = FILE_IDS_VECTOR_QUEUE_FOR_SEARCH.get()
            if len(ids):  # 搜索
                D, I = index.search(vec, K)
                # 将结果添加进写入进程
                file_path = OUTPUT_FILE_PATH + OUTPUT_FILE_BASIC_NAME + str(fcnt)
                fcnt += 1

                # 避免在队列里积累太多向量
                while FILE_WRITE_QUEUE.qsize() > READ_FILE_NUM:
                    time.sleep(1)

                FILE_WRITE_QUEUE.put((file_path, ids, I, D))

        else:
            time.sleep(1)

    END_WRITE_FILE.value = 1
    WRITE_FILE_PROCESS.join()


def main():
    """主流程"""
    global INDEX_STR
    index = IndexInit(index_str=INDEX_STR)
    add_vectors(index)
    search_kNN(index)
    print File_IO.getLocalTimeStr() + " Finish"


if __name__ == '__main__':
    main()

    # 提升了大约38%
