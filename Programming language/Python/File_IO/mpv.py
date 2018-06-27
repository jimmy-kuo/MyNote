# encoding:utf-8

"""
多进程共享变量学习
author  :   h-j-13
time    :   2018-6-27
"""

import multiprocessing


def func(num):
    s = num.get()
    print s


if __name__ == "__main__":
    num = multiprocessing.Queue() #("d", 10.0)  # d表示数值,主进程与子进程共享这个value。（主进程与子进程都是用的同一个value）
    num.put(1)
    num.put(2)
    num.put(3)
    print num.qsize()

    p = multiprocessing.Process(target=func, args=(num,))
    p.start()
    p.join()

    print num.qsize()


