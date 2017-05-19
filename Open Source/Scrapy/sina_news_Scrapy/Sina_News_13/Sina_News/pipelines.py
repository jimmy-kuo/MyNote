# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: http://doc.scrapy.org/en/latest/topics/item-pipeline.html

import sys

from Sina_News.DB_operation import DB_storage
from Sina_News.data_analysis import API_analysis

#处理编码问题
reload(sys)
sys.setdefaultencoding( "utf-8" )

class SinaNewsPipeline(object):


    def process_item(self, item, spider):


        db = DB_storage.DataBase()
        db.get_connect()

        news_dict_list_str=item['news_dict_list_str']
        dict_list= API_analysis.deal_API(news_dict_list_str)

        for dict in dict_list:
            db.db_insert_data(dict)

        db.db_insert_data()
        db.db_close()

