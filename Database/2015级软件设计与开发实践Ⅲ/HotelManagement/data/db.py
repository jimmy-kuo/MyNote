#!/usr/bin/env python
# encoding:utf-8

"""
客房管理系统 - 数据库操作封装

哈尔滨工业大学(威海) 2018
软件设计开发实践 III

author    :   @`13
time      :   2018.8.20
"""

import pymysql

HOST = "118.126.104.182"
PASSWD = "19950705"
DB = "HotelManagement"


class DataBase:
    """MySQL数据库操作类"""

    def __init__(self):
        """数据库配置初始化"""
        global HOST, PASSWD, DB
        self.host = HOST
        self.port = 3306
        self.user = "root"
        self.passwd = PASSWD
        self.charset = "utf8mb4"  # 以后统一使用数据库默认编码
        self.db_name = DB
        self.timezone = "+8:00"
        # 链接对象
        self.conn = None
        self.cursor = None
        self.SSCursor = None

    def __enter__(self):
        self.db_connect()
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        # 异常的 type、value 和 traceback
        if exc_val:
            print("DB Context Error:" + str(exc_val) + ":" + str(exc_tb))
        self.db_close()

    def db_connect(self):
        """连接数据库"""
        try:
            self.conn = pymysql.Connection(
                host=self.host,
                port=self.port,
                user=self.user,
                passwd=self.passwd,
                charset=self.charset,
                db=self.db_name,
                use_unicode=False,
                connect_timeout=2880000)
        except pymysql.Error, e:
            print('Connect Error:' + str(e))
        self.cursor = self.conn.cursor()
        self.SSCursor = self.conn.cursor(pymysql.cursors.SSCursor)
        if not self.cursor:
            raise (NameError, "Connect Failure")

    def db_close(self):
        """关闭数据库"""
        try:
            self.cursor.close()
            self.SSCursor.close()
            self.conn.close()
        except pymysql.Error as e:
            print("Connect Error:" + str(e))

    def db_commit(self):
        """提交事务"""
        try:
            self.conn.commit()
        except pymysql.Error as e:
            print("Commit Error:" + str(e))

    def execute_sql_value(self, sql, value):
        """
        执行带values集的sql语句
        :param sql: sql语句
        :param value: 结果值
        """
        try:
            self.cursor.execute(sql, value)
        except pymysql.Error, e:
            if e.args[0] == 2013 or e.args[0] == 2006:  # 数据库连接出错，重连
                self.db_close()
                self.db_connect()
                self.db_commit()
                print("execute |sql(value) - time out,reconnect")
                self.cursor.execute(sql, value)
            else:
                print("execute |sql(value) - Error:" + str(e))
                print("SQL : " + sql)

    def execute_no_result(self, sql):
        """
        执行SQL语句,不获取查询结果,而获取执行语句的结果
        :param sql: SQL语句
        """
        try:
            return self.cursor.execute(sql)
        except pymysql.Error, e:
            if e.args[0] == 2013 or e.args[0] == 2006:  # 数据库连接出错，重连
                self.db_close()
                self.db_connect()
                self.db_commit()
                print("execute |sql(no result) - time out,reconnect")
                self.cursor.execute(sql)
            else:
                print("execute |sql(no result) - Error:" + str(e))
                print("SQL : " + sql)

    def execute(self, sql):
        """
        执行SQL语句
        :param sql: SQL语句
        :return: 获取SQL执行并取回的结果
        """
        result = None
        try:
            self.cursor.execute(sql)
            result = self.cursor.fetchall()
        except pymysql.Error, e:
            if e.args[0] == 2013 or e.args[0] == 2006:  # 数据库连接出错，重连
                self.db_close()
                self.db_connect()
                self.db_commit()
                print("execute |sql - time out,reconnect")
                print("execute |sql - Error 2006/2013 :" + str(e))
                print("sql = " + str(sql))
                result = self.execute(sql)  # 重新执行
            else:
                print("execute |sql - Error:" + str(e))
                print('SQL : ' + sql)
        return result

    def execute_Iterator(self, sql, pretchNum=1000):
        """
        执行SQL语句(转化为迭代器)
        :param sql: SQL语句
        :param pretchNum: 每次迭代数目
        :return: 迭代器
        """
        __iterator_count = 0
        __result = None
        __result_list = []
        try:
            Resultnum = self.cursor.execute(sql)
            for i in range(Resultnum):
                __result = self.cursor.fetchone()
                __result_list.append(__result)
                __iterator_count += 1
                if __iterator_count == pretchNum:
                    yield __result_list
                    __result_list = []
                    __iterator_count = 0
            yield __result_list  # 最后一次返回数据
        except pymysql.Error, e:
            print('execute_Iterator error:' + str(e))
            print('SQL : ' + sql)

    def execute_many(self, sql, params):
        """
        批量执行SQL语句
        :param sql: sql语句(含有%s)
        :param params: 对应的参数列表[(参数1,参数2..参数n)(参数1,参数2..参数n)...(参数1,参数2..参数n)]
        :return: affected_rows
        """
        affected_rows = 0
        try:
            self.cursor.executemany(sql, params)
            affected_rows = self.cursor.rowcount
        except pymysql.Error, e:
            if e.args[0] == 2013 or e.args[0] == 2006:  # 数据库连接出错，重连
                self.db_close()
                self.db_connect()
                self.db_commit()
                print("execute |sql - time out,reconnect")
                print("execute |sql - Error 2006/2013 :" + str(e))
                print("sql = " + str(sql))
                self.execute_many(sql, params)  # 重新执行
            else:
                print("execute many|sql - Error:" + str(e))
                print('SQL : ' + sql)
                return -1
        return affected_rows

    def execute_SScursor(self, sql):
        """使用pymysql SSCursor类实现逐条取回
        请不要使用此方法来进行增、删、改操作()
        最好在with[上下文管理器内使用]"""
        # sql不要带 ';'
        # 有可能会发生 2014, "Commands out of sync; you can't run this command now"
        # 详见 [MySQL-python: Commands out of sync](https://blog.xupeng.me/2012/03/13/mysql-python-commands-out-of-sync/)
        sql = sql.strip(';')
        # 只能执行单行语句
        if len(sql.split(';')) >= 2:
            return []
        try:
            self.SSCursor.execute(sql)
            return self.SSCursor
        except pymysql.Error, e:
            print("execute SScursor |sql - Error:" + str(e))
            print('SQL : ' + sql)
            return []


if __name__ == '__main__':
    # Demo
    with DataBase() as db:
        # Demo for execute
        # ------------------------------
        print db.execute("show tables")

        # Demo for execute_Iterator
        # ------------------------------
        for results in db.execute_Iterator("""SHOW TABLES;"""):
            for result in results:
                print result

        # Demo for execute_SScursor
        # ------------------------------
        for i in db.execute_SScursor("show tables;"):
            print i
