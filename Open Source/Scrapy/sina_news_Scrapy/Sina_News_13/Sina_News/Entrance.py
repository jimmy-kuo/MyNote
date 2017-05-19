# -*- coding:utf-8 -*-
# time      :  2016年3月23日
# author   :  @`13
# func      :  主程序入口
from scrapy import cmdline

cmdline.execute("scrapy crawl Sina_News".split())