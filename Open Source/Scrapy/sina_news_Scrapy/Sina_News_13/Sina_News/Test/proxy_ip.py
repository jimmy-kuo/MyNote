# -*- coding:utf-8 -*-
# time      ：2016年3月16日
# author    ：@`13
# func      : 测试代理ip

import urllib
import socket
import time
import Queue
import threading

#超时设定
socket.setdefaulttimeout(3)

#测试ip方法
def test_ip(proxy_ip):
    """
    用于测试代理IP
    """


    ip = proxy_ip.strip("\n").split(":")
    proxy_host = "http://"+ip[0]+":"+ip[1]
    proxy_temp = {"http":proxy_host}
    proxys_ip=proxy_temp
    print str(proxys_ip)[17:-4]+"\t:",
    url = "http://news.sina.com.cn/"
    for i in range(5):
        try:
            start=time.time()
            urllib.urlopen(url,proxies=proxys_ip).read()
            end=time.time()
            t=str(end-start)
            print t[:7]+" | ",
        except Exception,error:
            print "15 | ",
            #print error
            continue
    print
#消费者
class test_data(threading.Thread):
    def __init__(self, work_queue):
        threading.Thread.__init__(self)     # 主类调用父类方法，必须在第一行
        self.work_queue = work_queue
    def run(self):
        while True:
            proxy_ip = self.work_queue.get() # 当队列为空时，会阻塞，直到有数据
            #print proxy_ip
            test_ip(proxy_ip)
# 生产者
class put_data(threading.Thread):
    def __init__(self, work_queue):
        threading.Thread.__init__(self)
        self.work_queue = work_queue
    def run(self):
        f = open("/home/houjie/Code/Python/test_proxy_ip/ip_lists.txt")
        ips=[]
        for line in f:
            ip = line[:-1]
            #print ip
            ips.append(ip)
        f.close()
        print len(ips)
        for ip in ips:
            #print ip
            self.work_queue.put(ip)
            time.sleep(0.05)
if __name__=="__main__":
    #队列设定
    work_queue = Queue.Queue(maxsize = 50)
    P = put_data(work_queue)
    P.daemon = True # 当主线程退出时子线程也退出
    P.start()
    C = test_data(work_queue)
    C.daemon = True # 当主线程退出时子线程也退出
    C.start()
    work_queue.join() # 主线程会停在这里，直到所有ip被get()，并且task_done()，因为没有调用task_done()，所在这里会一直阻塞，直到用户按^C