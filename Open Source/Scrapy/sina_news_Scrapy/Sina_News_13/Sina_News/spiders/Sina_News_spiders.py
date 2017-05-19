# -*- coding:utf-8 -*-
# time      ：2016年3月23日
# author    ：@`13
# func      : 爬虫核心模块

# 自写函数库
from Sina_News.data_analysis import API_analysis
# Python标准包
import time
import sys
sys.path.append('./')
#Scapy库
from scrapy.contrib.spiders import CrawlSpider
from scrapy.http import Request

REQ_TIME_INTERVAL = 3

#API列表
api_list=
[
           'http://api.sina.cn/sinago/list.json?channel=news_toutiao',
          'http://api.sina.cn/sinago/list.json?channel=news_tuijian',
          'http://api.sina.cn/sinago/list.json?channel=news_auto',
          'http://api.sina.cn/sinago/list.json?channel=news_ent',
          'http://api.sina.cn/sinago/list.json?channel=news_sports',
          'http://api.sina.cn/sinago/list.json?channel=news_finance',
          'http://api.sina.cn/sinago/list.json?channel=news_tech',
          'http://api.sina.cn/sinago/list.json?channel=news_funny',
          'http://api.sina.cn/sinago/list.json?channel=hdpic_toutiao',
          'http://api.sina.cn/sinago/list.json?channel=hdpic_funny',
          'http://api.sina.cn/sinago/list.json?channel=hdpic_pretty',
          'http://api.sina.cn/sinago/list.json?channel=hdpic_story',
]

class SinaNews(CrawlSpider):
    """
    继承CrawlSpider的新闻内容获取类
    """
    def __init__(self):
        self.name = "Sina_News"
        self.redis_key = 'Sina_News:start_urls'
        start_urls = ['http://api.sina.cn/sinago/list.json?channel=news_toutiao']
        url = 'http://api.sina.cn/sinago/list.json?channel=news_toutiao'

    def parse(self,response):
        pass
        #print response.body.decode('unicode-escape')
        # 获取内容，并完成存贮过程。
        news_dict_list_str = response.body.decode('unicode-escape')
        news_dict_list_str=news_dict_list_str
        API_analysis.deal_API(news_dict_list_str)
        while(1):
            for url in api_list:
                time.sleep(REQ_TIME_INTERVAL5)
                yield Request(url, callback=self.parse)
            return
