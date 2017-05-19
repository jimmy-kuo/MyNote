# -*- coding:utf-8 -*-
# time      :  2016年3月22日
# author   : @`13
# func      : 数据库操作

"""
数据库存储模块

MySQL版本         ：5.6
Python模块        ：MySQLdb
"""

import MySQLdb
import sys
import random
import ConfigParser
import threading
import logging
import os

#  日志记录在当前目录下
sys.path.append('./')
reload(sys)
sys.setdefaultencoding('utf8')
FILE = os.getcwd()
logging.basicConfig(level=logging.DEBUG,
                    format='%(asctime)s:%(filename)s   [line:%(lineno)d]   %(levelname)s  %(message)s',
                    datefmt='%a, %d %b %Y %H:%M:%S',
                    filename = os.path.join(FILE,'DB_log'),
                    filemode='w')

# 读取文件
conf = ConfigParser.ConfigParser()
conf.read("Sina_news.conf")

#conf.get("DB", "DB_HOST")

class DataBase :
    """
    数据库操作类
    """

    # 数据库初始化
    def __init__(self):
        """
        数据库初始化
        """

        self.host = '127.0.0.1'
        self.user = 'root'
        self.passwd = ''
        self.charset = 'utf8'
        self.db_lock = threading.Lock()         # 数据库操作锁

    # 执行连接数据库操作
    def get_connect(self):
        """
        链接数据库
        """

        if self.db_lock.acquire():
            try:
                self.conn = MySQLdb.Connection(
                    host = self.host, user = self.user, passwd = self.passwd, charset = self.charset)
            except MySQLdb.Error, e:
                logging.error('get_connect error_info: %d: %s' % (e.args[0], e.args[1]))

            self.cursor = self.conn.cursor()
            if not self.cursor:
                raise(NameError, "Connect failure")

            # # 设置编码
            # try:
            #     self.cursor.execute('SET character_set_connection=utf8, character_set_results=utf8, character_set_client=utf8')
            # except MySQLdb.Error, e:
            #     print str(datetime.datetime.now()).split(".")[0], "ERROR %d: %s" % (e.args[0], e.args[1])
            self.db_lock.release()

    # 关闭数据库链接
    def db_close(self):
        """
        关闭数据库
        """
        if self.db_lock.acquire():
            try:
                self.conn.close()
            except MySQLdb.Error, e:
                logging.error('db_close error_info: %d: %s' % (e.args[0], e.args[1]))
            self.db_lock.release()

    #　提交更改
    def db_commit(self):
        """
        提交事务
        """

        if self.db_lock.acquire():
            try:
                self.conn.commit()
            except MySQLdb.Error, e:
                logging.error('db_commit error_info: %d: %s' % (e.args[0], e.args[1]))
            self.db_lock.release()


    def db_insert_data(self,news_dict):
        """
        将数据保存到数据库
        """

        tablename=self.get_table_name()
        id = news_dict['id']
        sql = """SELECT COUNT(*) FROM %s """%(tablename)
        sql = sql + "WHERE id = %s"%(id)

        # print sql

        #简单判断数据库中是否有此条记录
        self.cursor.execute(sql)
        bool=self.cursor.fetchall()
        #print bool[0][0]

        if bool[0][0]==1:
            self.db_update(news_dict)

        else :
            self.db_insert(news_dict)


    # 数据库数据插入
    # @param  news_dict 新闻信息字典
    def db_insert(self, news_dict):
        """
        插入新数据
        """

        id = news_dict['id']
        title = news_dict['title']
        long_title = news_dict['long_title']
        source = news_dict['source']
        url = news_dict['url']
        pub_date = news_dict['pub_date']
        article_date = news_dict['article_date']
        qreply = news_dict['qreply']
        total = news_dict['total']
        shows = news_dict['show']
        praise = news_dict['praise']
        dispraise = news_dict['dispraise']
        news = news_dict['news']
        details = news_dict['details']
        flag = news_dict['flag']

        table_name = self.get_table_name()

        sql = """INSERT INTO %s""" % table_name
        sql = sql + """(id,title,long_title,source,url,pub_date,article_date,qreply,total,praise,dispraise,news,details,shows,flag)"""
        sql = sql + " VALUES ('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')"\
                    %(id,title,long_title,source,url,pub_date,article_date,qreply,total,praise,dispraise,news,details,shows,flag)
        #print sql

        self.__execute__(sql)

    # 新闻数据更新(评论情况)
    # @param  news_dict 新闻信息字典
    def db_update(self, news_dict):
        """
        更新原有数据
        """

        id = news_dict['id']

        qreply = news_dict['qreply']
        total = news_dict['total']
        shows = news_dict['show']
        praise = news_dict['praise']
        dispraise = news_dict['dispraise']

        table_name = self.get_table_name()

        sql = """UPDATE %s SET """ % table_name
        sql = sql + """qreply = '%s',total = '%s',shows = '%s',praise = '%s',dispraise = '%s'"""%(qreply,total,shows,praise,dispraise)
        sql = sql + """WHERE id = '%s'"""%(id)

        #print sql

        self.__execute__(sql)

    # 执行sql语句
    # @param sql sql语句
    # @param values 插入或更新的值
    def __execute__(self, sql):
        result = None
        if self.db_lock.acquire():
            try:
                self.cursor.execute(sql)
                result = self.cursor.fetchall()
            except MySQLdb.Error, e:
                if e.args[0] == 2013 or e.args[0] == 2006: # 数据库连接出错，重连
                    self.db_lock.release()
                    self.get_connect()
                    logging.info('数据库重新连接')
                    result = self.__execute__(sql) # 重新执行
                    self.db_lock.acquire()
                else:
                    logging.error('db_execute error_info: %d: %s' % (e.args[0], e.args[1]))
            self.db_lock.release()

        return result if result else None


    # 获取操作存入的表名
    def get_table_name(self):

            return 'sina_news.sina_news'

if __name__ == '__main__':

    db = DataBase()
    db.get_connect()

    id=random.randrange(0, 1022221, 2)

    news_dict={
    "id"            :id,        #ID
    "title"         :'test',        #标题
    "long_title"    :'long-test',        #完整标题
    "source"        :'来源',        #来源
    "url"           :'新闻链接',        #新闻链接
    "pub_date"      :'1995-7-5 11:11:11',        #新闻发布时间
    "article_date"  :'1995-7-5',        #文章发布时间
    "qreply"        :'1231',        #快速回复数目
    "total"         :'12221',        #总体回复数目
    "show"          :'2222',        #
    "praise"        :'32223',        #喜欢数
    "dispraise"     :'42224',        #不喜欢数目
    "news"          :'222213',        #新闻内容
    "details"       :'123123',        #完整新闻内容 图片以链接的形式保存在文本中
    "flag"          :1000       #标记位
    }

    db.db_insert_data(news_dict)

    db.db_close()
