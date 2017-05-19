# -*- coding:utf-8 -*-
# time      : 2016年3月23日
# author   : @zaixiahanli
# func      : 获得链接内的内容

from bs4 import BeautifulSoup
import re
import urllib2
import xml
import sys

# reload(sys)
# sys.setdefaultencoding('utf-8')

# f1=open(r'D:/chun.txt','a')
# f2=open(r'D:/za.txt','a')

def deal_link_news(link):
    """
    获取url中的新闻主体
    @ return url中新网的主题内容 <type 'str'>
    """
    #  伪造头部
    headers = {'User-Agent':'Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US; rv:1.9.1.6) Gecko/20091201 Firefox/5.5.6'}
    #  尝试连接
    req = urllib2.Request(url = link,
                                       headers = headers)
    #  读取内容
    content = urllib2.urlopen(req).read()
    #  创建beautiful对象
    soup=BeautifulSoup(str(content),"lxml")
    #  寻找含有p与img标签的内容
    trs=soup.findAll(["img","p"])
    #获得纯文本文件
    p=soup.find_all('p')
    paragraphs = ''
    for x in p:
        print str(x)
        paragraphs = paragraphs + (str(x))
    # 返回新闻主体内容字符串
    return paragraphs
    
if __name__=="__name__":
    deal_link_news('http://sinanews.sina.cn/sharenews.shtml?id=fxqnsty4894836-comos-finance-cms')