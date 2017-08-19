#!/usr/bin/env python
# encoding:utf-8

"""
    基于MySQL的数据库操作封装
=============================

author    :   @`13
version   :   2.0.a
time      :   2017.4.30

思路：尽可能保留错误参数
     根据不同的需求使用不同的执行方式
     根据执行状态来选择不同的日志记录模式
"""

import MySQLdb

from DB_model import Database_model

# connect status
_CONNECT_OK = 1
_CONNECT_FAILE = -1
_CONNECT_TIMEOUT = -4

# sql execute status
_SQL_OK = 1
_SQL_NO_STATUS = 0
_SQL_WARRING = -1
_SQL_ERROR = -2
_SQL_DEADLOCK = -3

# sql type
_QUERY_iterable = -1  # 不返回状态而生成一个迭代器
_QUERY = 0  # 返回状态和执行结果
_INSERT = 1  # 仅返回状态
_UPDATE = 2  # 仅返回状态
_DELETE = 3  # 仅返回状态


class MySQL(Database_model):
    """MySQL数据库操作类"""

    def __init__(self, HOST, USER, PASSWORD, PORT=3306, CHARSET="utf8mb4"):
        """数据库配置初始化"""
        super(MySQL, self).__init__()
        self._user = USER  # 用户名
        self._password = PASSWORD  # 密码
        self._port = PORT  # 端口
        self._serviceAddr = HOST  # 数据库地址
        self._charset = CHARSET  # 字符集
        self._connection = None  # 链接对象
        self._default_cursor = None  # 默认游标
        self._cursor = []  # 游标对象集合

    def create_new_cursor(self):
        """
        创建新的游标,并加入游标集
        要求在创建连接后使用
        :return 此次创建的游标号
        """
        __new_cursor = self._connection.cursor()
        self._cursor.append(__new_cursor)
        return len(self._cursor)

    def connect(self):
        """创建到数据库服务器的连接"""
        __status = _CONNECT_OK
        __error_massage = []
        try:
            self._connection = MySQLdb.Connection(
                host=self._serviceAddr,
                port=self._port,
                user=self._user,
                passwd=self._password,
                charset=self._charset,
                use_unicode=False)
            self._default_cursor = self._connection.cursor()
        except MySQLdb.Error as e:
            __status = _CONNECT_FAILE
            __error_massage = [e.args[0], e.args[1]]
            if not self._default_cursor:
                __status = _CONNECT_TIMEOUT
        return [__status, __error_massage]

    def disconnect(self):
        """关闭到数据库服务器的连接"""
        __status = _CONNECT_OK
        __error_massage = []
        try:
            self._default_cursor.close()
            if self._cursor:
                for cursor in self._cursor:
                    cursor.close()
            self._connection.close()

        except MySQLdb.Error as e:
            __status = _CONNECT_FAILE
            __error_massage = [e.args[0], e.args[1]]
        return [__status, __error_massage]

    def select_db(self, database_name):
        """选择使用的数据库[MySQL]"""
        return self._default_cursor.execute(
            """USE {db}""".format(db=database_name)
        )

    def commit(self):
        """提交事务"""
        __status = _SQL_OK
        __error_massage = []
        try:
            self._connection.commit()
        except MySQLdb.Error as e:
            __status = _SQL_ERROR
            __error_massage = [e.args[0], e.args[1]]
        return [__status, __error_massage]

    def rollback(self):
        """回滚事物"""
        __status = _SQL_OK
        __error_massage = []
        try:
            self._connection.rollback()
        except MySQLdb.Error as e:
            __status = _SQL_ERROR
            __error_massage = [e.args[0], e.args[1]]
        return [__status, __error_massage]

    def execute_sql(self, sql, sql_type=_QUERY, cursor_num=0, values=()):
        """
        执行SQL语句执行命令
        :param sql: SQL语句
        :param cursor_num: 执行命令的游标代号
        :param sql_type: SQL语句及返回结果类型
        :param values: SQL 参数列表
        :return: 返回执行的状态/错误信息[返回信息]
        """
        if sql_type == _QUERY_iterable:
            return self.execute_sql_Iterator(sql, cursor_num=cursor_num)

        __status = _SQL_NO_STATUS
        __error_massage = []
        __result = []

        if cursor_num == 0:
            __cursor = self._default_cursor
        else:
            __cursor = self._cursor[cursor_num - 1]

        try:
            if values:
                __cursor.execute(sql, values)
            else:
                __cursor.execute(sql)
            if sql_type == _QUERY:
                __result = __cursor.fetchall()
            __status = _SQL_OK
        except MySQLdb.Error as e:
            __status = _SQL_ERROR
            if e.args[0] == 2013 or e.args[0] == 2006:  # 数据库连接超时
                self.disconnect()  # 断开连接后重连 重新执行命令
                self.connect()
                self.execute_sql(sql, sql_type=sql_type)  # 使用默认游标重新执行 (递归方式?)
                # TODO 有没有更合适的解决方案？ 关于2006/2013错误 2017.5.31
                __status = _CONNECT_TIMEOUT
            elif e.args[0] == 1213 or e.args[0] == 1216 or e.args[0] == 1217:  # 死锁
                __status = _SQL_DEADLOCK
            elif str(e.args[1]).lower().find("warning") != -1:
                __status = _SQL_WARRING
            __error_massage = [e.args[0], e.args[1]]

        return [__result, [__status, __error_massage]]

    def execute_sql_Iterator(self, sql, pretchNum=10000, cursor_num=0):
        """generator模式的SQL语句执行"""
        __result = None
        __result_list = []
        Iterator_count = 0

        if cursor_num == 0:
            __cursor = self._default_cursor
        else:
            __cursor = self._cursor[cursor_num - 1]

        Resultnum = __cursor.execute(sql)
        for i in xrange(Resultnum):
            __result = __cursor.fetchone()
            __result_list.append(__result)
            Iterator_count += 1
            if Iterator_count == pretchNum:
                yield __result_list
                __result_list = []
                Iterator_count = 0
        yield __result_list  # 最后一次返回数据


if __name__ == '__main__':
    # Demo
    pass

    # #Base Func Test
    # #--------------
    # mysql = MySQL(HOST='172.29.152.249', USER='root', PASSWORD='platform')
    # mysql.connect()
    # print mysql.execute_sql("show databases", sql_type=_QUERY)
    # for info_list in mysql.execute_sql("show databases", sql_type=_QUERY_iterable):
    #     for info in info_list:
    #         print info
    # for info_list in mysql.execute_sql_Iterator("show databases", pretchNum=1):
    #     for info in info_list:
    #         print info
    # mysql.disconnect()

    # #new cursor test
    # #---------------
    # mysql = MySQL(HOST='172.29.152.249', USER='root', PASSWORD='platform')
    # mysql.connect()
    # print mysql.create_new_cursor()
    # print mysql.create_new_cursor()
    # print mysql.create_new_cursor()
    # print mysql.create_new_cursor()
    # print mysql.create_new_cursor()
    # for info_list in mysql.execute_sql_Iterator(
    #         "show databases",
    #         pretchNum=1,
    #         cursor_num=mysql.create_new_cursor()):
    #     for info in info_list:
    #         print info
    # for info_list in mysql.execute_sql("show databases", sql_type=_QUERY_iterable, cursor_num=0):
    #     for info in info_list:
    #         print info
    # mysql.disconnect()
